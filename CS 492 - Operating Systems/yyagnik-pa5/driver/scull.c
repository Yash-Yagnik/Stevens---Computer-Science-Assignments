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

#include <linux/kernel.h>	
#include <linux/slab.h>		
#include <linux/fs.h>		
#include <linux/errno.h>	
#include <linux/types.h>
#include <linux/cdev.h>
#include <linux/mutex.h>

#include <linux/uaccess.h>	
#include <linux/semaphore.h>

#include "scull.h"


// How to run
// sudo chmod 245 /proc/devices
// sudo insmod ../driver/scull.ko scull_fifo_size=10 scull_fifo_elemsz=3 // Loading in the scull module
// sudo chmod o+rw /dev/scull

static int scull_major =   SCULL_MAJOR;
static int scull_minor =   0;
static int scull_fifo_elemsz = SCULL_FIFO_ELEMSZ_DEFAULT; 
static int scull_fifo_size   = SCULL_FIFO_SIZE_DEFAULT;   

char* message_queue; // This is an array that will be accessed by both the consumer and producer
char* start; // Left pointer for reading 
char* end; // Right pointer for writing

module_param(scull_major, int, S_IRUGO);
module_param(scull_minor, int, S_IRUGO);
module_param(scull_fifo_size, int, S_IRUGO);
module_param(scull_fifo_elemsz, int, S_IRUGO);

MODULE_AUTHOR("yyagnik");
MODULE_LICENSE("Dual BSD/GPL");



static struct cdev scull_cdev;		/* Char device structure */
static DEFINE_MUTEX(scull_mutex);    // Define a mutex lock
struct semaphore railroad;
struct semaphore n;

// TO-DO: Make a semaphore

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

/*
 * Read and Write
 */

static ssize_t scull_read(struct file *filp, char __user *buf, size_t count, loff_t *f_pos){
	// The reason there is a deadlock is beacause of the both will sleep forever case you need to add a semaphore
	ssize_t retval = 0;
	
    
	int semaRet = down_interruptible(&railroad); // Initialize and Lock the semaphore 
	if (semaRet != 0) {
		return -EFAULT;
	}
	int mutexRet = mutex_lock_interruptible(&scull_mutex); // Lock the mutex
	if (mutexRet != 0) {
		up(&railroad);
		return -EFAULT;
	}
	size_t availableBytes = *start;
    size_t copying_n_bytes = min(count, availableBytes);
	printk(KERN_INFO "%ld", copying_n_bytes);
	


    // Copy data to user space with copy_to_user
	start += sizeof(size_t);
    if (copy_to_user(buf, start, copying_n_bytes) != 0) { // You have to do all the mutex and semaphore stuf bc if there is an error 
		up(&railroad); // unlock the semaphore
		mutex_unlock(&scull_mutex); // unlock the mutex 
        return -EFAULT; // Error copying data to user space
    }

    // Update pointers and return the number of bytes read 
    start += copying_n_bytes;
    retval = copying_n_bytes;
	up(&n);
	mutex_unlock(&scull_mutex);
    printk(KERN_INFO "scull read %zd bytes\n", retval);

    return retval;
}


static ssize_t scull_write(struct file *filp, const char __user *buf, size_t count, loff_t *f_pos)
{
	ssize_t retval = 0;

	int semaphore_ret = down_interruptible(&n); // Initialize and Lock the semaphore 
	if (semaphore_ret != 0) {
		return -EFAULT;
	}
	int mutex_Ret = mutex_lock_interruptible(&scull_mutex); // Lock the mutex
	if (mutex_Ret != 0) {
		up(&n);
		return -EFAULT;
	}
    size_t space_available = scull_fifo_elemsz; // space available in the buffer

    size_t copying_n_bytes = min(count, space_available); // number of bytes to copy

    // Copy data from user space with copy_from_user
	*end = copying_n_bytes;
	end += sizeof(size_t);
    if (copy_from_user(end, buf, copying_n_bytes) != 0) {
		mutex_unlock(&scull_mutex);
		up(&n);
        return -EFAULT; // Error copying data from user space
    }

    // Update pointers and return the number of bytes written 
    end += copying_n_bytes;
    retval = copying_n_bytes;
	up(&railroad); // Unlock the semaphore
	mutex_unlock(&scull_mutex); // unlock the mutex 
    printk(KERN_INFO "scull write %zd bytes\n", retval);

    return retval;
}


/*
 * The ioctl() implementation
 */
static long scull_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{

	int err = 0;
	int retval = 0;
    
	/*
	 * extract the type and number bitfields, and don't decode
	 * wrong cmds: return ENOTTY (inappropriate ioctl) before access_ok()
	 */
	if (_IOC_TYPE(cmd) != SCULL_IOC_MAGIC) return -ENOTTY;
	if (_IOC_NR(cmd) > SCULL_IOC_MAXNR) return -ENOTTY;

	err = !access_ok((void __user *)arg, _IOC_SIZE(cmd));
	if (err) return -EFAULT;

	switch(cmd) {
	case SCULL_IOCGETELEMSZ:
		return scull_fifo_elemsz;

	default:  /* redundant, as cmd was checked against MAXNR */
		return -ENOTTY;
	}
	return retval;

}

struct file_operations scull_fops = {
	.owner 		= THIS_MODULE,
	.unlocked_ioctl = scull_ioctl,
	.open 		= scull_open,
	.release	= scull_release,
	.read 		= scull_read,
	.write 		= scull_write,
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
	dev_t devno = MKDEV(scull_major, scull_minor);

	/* TODO: free FIFO safely here */

	/* Get rid of the char dev entry */
	cdev_del(&scull_cdev);

	/* cleanup_module is never called if registering failed */
	unregister_chrdev_region(devno, 1);

	kfree(message_queue);
}

int scull_init_module(void)
{
	int result;
	dev_t dev = 0;
	sema_init(&railroad, 0);
	sema_init(&n, scull_fifo_size);

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

	/* TODO: allocate FIFO correctly here */
	message_queue = (kmalloc(scull_fifo_size * (sizeof(size_t) + scull_fifo_elemsz), GFP_KERNEL));
	start = message_queue;
	end = message_queue;
	if (!message_queue){
		result = -ENOMEM;
		goto fail;
	}
	printk(KERN_INFO "scull: FIFO SIZE=%u, ELEMSZ=%u\n", scull_fifo_size, scull_fifo_elemsz);

	return 0; /* succeed */

  fail:
	scull_cleanup_module();
	return result;
}

module_init(scull_init_module);
module_exit(scull_cleanup_module);
