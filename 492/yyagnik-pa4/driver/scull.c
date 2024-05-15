/*
 * scull.c -- the bare scull char module
 *
 * Copyright (C) 2001 Alessandro Rubini and Jonathan Corbet
 * Copyright (C) 2001 O'Reilly & Associates
 *
 * The source code in this file can be freely used, adapted,
 * and redistributed in source or binary form, so long as an
 * acknowledgment appears in derived source files.  The citation
 * should list that the code comes from the book "Linux Device
 * Drivers" by Alessandro Rubini and Jonathan Corbet, published
 * by O'Reilly & Associates.   No warranty is attached;
 * we cannot take responsibility for errors or fitness for use.
 *
 */

#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/init.h>

#include <linux/kernel.h>	/* printk() */
#include <linux/slab.h>		/* kmalloc() */
#include <linux/fs.h>		/* everything... */
#include <linux/errno.h>	/* error codes */
#include <linux/types.h>	/* size_t */
#include <linux/cdev.h>

#include <linux/uaccess.h>	/* copy_*_user */
#include <linux/types.h> 
#include <linux/list.h> // This allows me to use all of the inbuilt kernel linked list commands
#include "scull.h"		/* local definitions */


struct task_node {
    pid_t pid;
    pid_t tgid;
    struct list_head head;
};

/*
 * Our parameters which can be set at load time.
 */

static int scull_major =   SCULL_MAJOR;
static int scull_minor =   0;
static int scull_quantum = SCULL_QUANTUM;

module_param(scull_major, int, S_IRUGO);
module_param(scull_minor, int, S_IRUGO);
module_param(scull_quantum, int, S_IRUGO);

MODULE_AUTHOR("yyagnik");
MODULE_LICENSE("Dual BSD/GPL");

static struct cdev scull_cdev;		/* Char device structure */

struct task_node* curr_positon; // make the node for current positon because when you loop 

//struct task_node* new_task_node = NULL; // Make the linked list

struct list_head tasks;
LIST_HEAD(tasks);

struct task_node* new_task_node = NULL; // Make the link list and set it to null at the start

static DEFINE_MUTEX(mutex_task_adding);
static DEFINE_MUTEX(mutex_task_removing);

/*
 * Open and close
 */

static int scull_open(struct inode *inode, struct file *filp)
{
	printk(KERN_INFO "scull open\n");
	return 0;          /* success */
}

static int scull_release(struct inode *inode, struct file *filp)
{
	printk(KERN_INFO "scull close\n");
	return 0;
}


void add_task(pid_t pid, pid_t tgid) {
	mutex_lock(&mutex_task_adding);
	// The args of list_for_each_entry(position, head, member)  
	list_for_each_entry(curr_positon, &tasks, head){
		if ((curr_positon->pid == current->pid) && (curr_positon->tgid == current->tgid)){ // we add this case to make sure that there are no dupicates in the linked list
			mutex_unlock(&mutex_task_adding);
			return;
		}
	}

	new_task_node = kmalloc(sizeof(struct task_info), GFP_KERNEL); // You might have to move this after the loop
	if (!new_task_node) {
        printk(KERN_ERR "Failed to allocate memory for new node\n");
        return;
    }


	new_task_node->pid = current->pid;
	new_task_node->tgid = current->tgid;


	/*
	This is some extra error checking
    
	*/
	// If there is a killed problem then the 4 lines after this are fucked
    // new_task_node->pid = current.pid;
    // new_task_node->tgid = current.tgid;
    INIT_LIST_HEAD(&new_task_node->head);
	// Adding nodes to another list whcih we will later use to remove the tasks
    list_add_tail(&new_task_node->head, &tasks); // Reason I used the tail function was to implement this as a queue

	mutex_unlock(&mutex_task_adding);
}


/*
 * The ioctl() implementation
 */

static long scull_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
	int err = 0, tmp;
	int retval = 0;
	struct task_info curr_task;

	/*
	 * extract the type and number bitfields, and don't decode
	 * wrong cmds: return ENOTTY (inappropriate ioctl) before access_ok()
	*/
	if (_IOC_TYPE(cmd) != SCULL_IOC_MAGIC) return -ENOTTY;
	if (_IOC_NR(cmd) > SCULL_IOC_MAXNR) return -ENOTTY;

	err = !access_ok((void __user *)arg, _IOC_SIZE(cmd));
	if (err) return -EFAULT;

	switch(cmd) {

	case SCULL_IOCRESET:
		scull_quantum = SCULL_QUANTUM;
		break;
        
	case SCULL_IOCSQUANTUM: /* Set: arg points to the value */
		retval = __get_user(scull_quantum, (int __user *)arg);
		break;

	case SCULL_IOCTQUANTUM: /* Tell: arg is the value */
		scull_quantum = arg;
		break;

	case SCULL_IOCGQUANTUM: /* Get: arg is pointer to result */
		retval = __put_user(scull_quantum, (int __user *)arg);
		break;

	case SCULL_IOCQQUANTUM: /* Query: return it (it's positive) */
		return scull_quantum;

	case SCULL_IOCXQUANTUM: /* eXchange: use arg as pointer */
		tmp = scull_quantum;
		retval = __get_user(scull_quantum, (int __user *)arg);
		if (retval == 0)
			retval = __put_user(tmp, (int __user *)arg);
		break;

	case SCULL_IOCHQUANTUM: /* sHift: like Tell + Query */
		tmp = scull_quantum;
		scull_quantum = arg;
		return tmp;
	
	// Added a case for SCULL_IOCIQUANTUM 
	case SCULL_IOCIQUANTUM:
		curr_task.__state  = current->__state;
		curr_task.cpu  = current->thread_info.cpu;
		curr_task.prio  = current->prio;
		curr_task.pid  = current->pid;
		curr_task.tgid  = current->tgid;
		curr_task.nvcsw  = current->nvcsw;
		curr_task.nivcsw  = current->nivcsw;

		retval = copy_to_user((struct task_info *)arg, &curr_task, sizeof(struct task_info));

		
		add_task(curr_task.pid, curr_task.tgid);
		break;
		
	default:  /* redundant, as cmd was checked against MAXNR */
		return -ENOTTY;
	}
	return retval;
}

struct file_operations scull_fops = {
	.owner =    THIS_MODULE,
	.unlocked_ioctl = scull_ioctl,
	.open =     scull_open,
	.release =  scull_release,
};

/*
 * Finally, the module stuff
 */

/*
 * The cleanup function is used to handle initialization failures as well.
 * Thefore, it must be careful to work correctly even if some of the items
 * have not been initialized
 */
void scull_cleanup_module(void)
{
	int task_num = 1; // The first task is task 1
	struct task_node* curr_node;

	dev_t devno = MKDEV(scull_major, scull_minor);
	/* Get rid of the char dev entry */
	cdev_del(&scull_cdev);

	/* cleanup_module is never called if registering failed */
	unregister_chrdev_region(devno, 1);

	// The args of list_for_each_entry(position, head, member)  
	list_for_each_entry(curr_node, &tasks, head){ // We have to loop through the linked list and print out each task 
		printk(KERN_INFO "Task %d: PID %d; TGID %d\n", task_num, curr_node->pid, curr_node->tgid);
		task_num = task_num + 1;
	}
	mutex_lock(&mutex_task_removing);

	list_for_each_entry(curr_node, &tasks, head){
		kfree(curr_node); // We have to free all the space that we created for the nodes that we made in kmalloc
	}

	mutex_unlock(&mutex_task_removing);
}

int scull_init_module(void)
{
	int result;
	dev_t dev = 0;

	/*
	 * Get a range of minor numbers to work with, asking for a dynamic
	 * major unless directed otherwise at load time.
	 */
	if (scull_major) {
		dev = MKDEV(scull_major, scull_minor);
		result = register_chrdev_region(dev, 1, "scull");
	} else {
		result = alloc_chrdev_region(&dev, scull_minor, 1, "scull");
		scull_major = MAJOR(dev);
	}
	if (result < 0) {
		printk(KERN_WARNING "scull: can't get major %d\n", scull_major);
		return result;
	}

	cdev_init(&scull_cdev, &scull_fops);
	scull_cdev.owner = THIS_MODULE;
	result = cdev_add (&scull_cdev, dev, 1);
	/* Fail gracefully if need be */
	if (result) {
		printk(KERN_NOTICE "Error %d adding scull character device", result);
		goto fail;
	}

	return 0; /* succeed */

  fail:
	scull_cleanup_module();
	return result;
}

module_init(scull_init_module);
module_exit(scull_cleanup_module);
