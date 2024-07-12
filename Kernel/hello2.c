
#include <linux/module.h> 
#include <linux/kernel.h>

MODULE_LICENSE ("GPL"); 
MODULE_AUTHOR ("DucLH");
MODULE_DESCRIPTION("This is hello module 2");
MODULE_VERSION("1.0.0");

extern int a1;
int init_module(void)
{
    printk (KERN_INFO "Hello 2. al = %d.\n", a1);
    return 0;
}

void cleanup_module(void)
{
    printk (KERN_INFO "Bye 2.\n");
}