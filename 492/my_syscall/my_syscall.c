#include <linux/syscalls.h>
#include <linux/kernel.h>
#include <linux/uaccess.h>

SYSCALL_DEFINE1(yyagnik_syscall, char* __user, user_string){
    long num_replacments = 0;
    char destination[32]; 
    if (user_string == NULL || strnlen(user_string, 32) > 32){
        return -1;
    }
    else{
        if (copy_from_user(destination, user_string, strnlen(user_string, 32)) != 0){
            return -EFAULT;
        }
        
        printk(KERN_ALERT "before: %s\n", user_string);
        for (int i = 0; i < strnlen(user_string, 32); i++){
            if (user_string[i] == 'a' || user_string[i] == 'e' || user_string[i] == 'i' || user_string[i] == 'o' || user_string[i] == 'u' || user_string[i] == 'y'){
                destination[i] = 'Y';
                num_replacments++;
            }
        }
        destination[strnlen(user_string, 32)] = "\0";
        printk(KERN_ALERT "after: %s", user_string);
        if (copy_to_user(user_string, destination, strnlen(user_string, 32)) != 0){
            return -EFAULT;
        }
    }
    return num_replacments;

}
