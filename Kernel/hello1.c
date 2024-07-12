#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("DucLH");
MODULE_DESCRIPTION("This is hello module 1");
MODULE_VERSION("1.0.0");

int a1 = 0;
EXPORT_SYMBOL(a1);

int init_module(void)
{
    printk(KERN_INFO "Hello 1.\n");
    int a1 = 100;
    return 0;
}

void cleanup_module(void)
{
    printk(KERN_INFO "Bye 1.\n");
}