#include <linux/module.h>
#include <linux/init.h>

MODULE_LICENSE("Dual MIT/GPL");
MODULE_VERSION("0.0.1");
MODULE_AUTHOR("zta0724 <zta0724@qq.com>");
MODULE_DESCRIPTION("https://github.com/zta0724/helloworld-module.git");

static int __init helloworld_init(void)
{
    printk(KERN_INFO "[HELLOWORLD] init.\n");
    return 0;
}

static void __exit helloworld_exit(void)
{
    printk(KERN_INFO "[HELLOWORLD] exit.\n");
}

module_init(helloworld_init);
module_exit(helloworld_exit);
