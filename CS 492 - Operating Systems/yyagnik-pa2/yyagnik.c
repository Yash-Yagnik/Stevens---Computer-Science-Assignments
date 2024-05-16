#include <linux/module.h>
#include <linux/init.h>
static int hello_init(void){
    printk(KERN_ALERT "Hello World from Yash Yagnik (yyagnik)\n");
    return 0;
}
static void hello_exit(void){
    printk(KERN_ALERT "PID is %i and program name is \"%s\"" "\n", current->pid, current->comm);
}
module_init(hello_init);
module_exit(hello_exit);
MODULE_LICENSE("Dual BSD/GPL");