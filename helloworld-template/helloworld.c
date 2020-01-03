#include <linux/module.h>
#include <linux/init.h>
#include <linux/device.h>
#include <linux/fs.h>
#include <linux/errno.h>
#include <linux/uaccess.h>
#include <linux/time.h>

#include "helloworld.h"

#define THIS_DESCRIPTION "https://github.com/zta0724/helloworld-module.git"
#define THIS_AUTHOR "zta0724 <zta0724@qq.com>"
#define THIS_VERSION "0.0.1"
#define THIS_LICENSE "Dual MIT/GPL"

MODULE_DESCRIPTION(THIS_DESCRIPTION);
MODULE_AUTHOR(THIS_AUTHOR);
MODULE_VERSION(THIS_VERSION);
MODULE_LICENSE(THIS_LICENSE);

static int s_major_number = 0;
static struct class *s_helloworld_class = NULL;
static struct device *s_helloworld_device = NULL;
static const char *CLASS_NAME = "helloworld_class";
static const char *DEVICE_NAME = "helloworld";

static int helloworld_open(struct inode *inode, struct file *file);
static int helloworld_release(struct inode *inode, struct file *file);
static ssize_t helloworld_read(struct file *file, char __user *buf, size_t len, loff_t *ppos);
static ssize_t helloworld_write(struct file *file, const char __user *buf, size_t len, loff_t *ppos);
static int helloworld_flush(struct file *file, fl_owner_t id);
static loff_t helloworld_llseek(struct file *file, loff_t offset, int whence);
static int helloworld_mmap(struct file *file, struct vm_area_struct *vma);
static int helloworld_fsync(struct file *file, loff_t start, loff_t end, int datasync);
static long helloworld_unlocked_ioctl(struct file *file, unsigned int cmd, unsigned long arg);
static long helloworld_compat_ioctl(struct file *file, unsigned int cmd, unsigned long arg);

static int onHelp(void);
static int onReset(void);
static int onDescription(unsigned long to, int toSize);
static int onAuthor(unsigned long to, int toSize);
static int onVersion(unsigned long to, int toSize);
static int onLicense(unsigned long to, int toSize);
static int onVerboseStatus(unsigned long to, int toSize);
static int onVerboseEnable(unsigned long from, int fromSize);
static int onToken(unsigned long buf, int len);

static int s_verbose_status = STATUS_OFF;

static struct TOKEN_S s_token_context = {
    .dir = DIR_READ,
    .key = "zta0724",
    .salt = "zta0724@qq.com"
};

//compat_ioctl:   32bit application call 64bit kernel
//unlocked_ioctl: 32bit application call 32bit kernel
//unlocked_ioctl: 64bit application call 32bit kernel
//unlocked_ioctl: 64bit application call 64bit kernel
static const struct file_operations s_helloworld_fops = {
    .owner             = THIS_MODULE,
    .open              = helloworld_open,
    .release           = helloworld_release,
    .mmap              = helloworld_mmap,
    .read              = helloworld_read,
    .write             = helloworld_write,
    .flush             = helloworld_flush,
    .fsync             = helloworld_fsync,
    .llseek            = helloworld_llseek,
    .compat_ioctl      = helloworld_compat_ioctl,
    .unlocked_ioctl    = helloworld_unlocked_ioctl,
};

static int __init helloworld_init(void)
{
    printk(KERN_INFO "[HELLOWORLD] Start initialization.\n");

    //@major: major device number or 0 for dynamic allocation
    //If @major == 0 this functions will dynamically allocate a major and return its number.
    //If @major  > 0 this function will attempt to reserve a device with the given major number and will return zero on success.
    s_major_number = register_chrdev(0, DEVICE_NAME, &s_helloworld_fops);
    if (0 > s_major_number)
    {
        printk(KERN_WARNING "[HELLOWORLD] DeviceName:[/dev/%s] register failed. MajorNumber: %d\n", DEVICE_NAME, s_major_number);
        return s_major_number;
    }

    printk(KERN_INFO "[HELLOWORLD] DeviceName: [/dev/%s] registered successed. MajorNumber: %d\n", DEVICE_NAME, s_major_number);

    s_helloworld_class = class_create(THIS_MODULE, CLASS_NAME);
    if (IS_ERR(s_helloworld_class))
    {
        printk(KERN_WARNING "[HELLOWORLD] ClassName: [%s] create failed.\n", CLASS_NAME);
        unregister_chrdev(s_major_number, DEVICE_NAME);
        return PTR_ERR(s_helloworld_class);
    }

    printk(KERN_INFO "[HELLOWORLD] ClassName: [%s] created successed.\n", CLASS_NAME);

    s_helloworld_device = device_create(s_helloworld_class, NULL, MKDEV(s_major_number, 0), NULL, DEVICE_NAME);
    if (IS_ERR(s_helloworld_device))
    {
        printk(KERN_WARNING "[HELLOWORLD] DeviceName: [%s] create failed.\n", DEVICE_NAME);
        class_destroy(s_helloworld_class);
        unregister_chrdev(s_major_number, DEVICE_NAME);
        return PTR_ERR(s_helloworld_device);
    }

    printk(KERN_INFO "[HELLOWORLD] DeviceName: [%s] created successed.\n", DEVICE_NAME);

    return 0;
}

static void __exit helloworld_exit(void)
{
    printk(KERN_INFO "[HELLOWORLD] Start cleaning module.\n");
    device_destroy(s_helloworld_class, MKDEV(s_major_number, 0));
    class_destroy(s_helloworld_class);
    unregister_chrdev(s_major_number, DEVICE_NAME);
    printk(KERN_INFO "[HELLOWORLD] Cleaned up successfully.\n");
}

static int helloworld_open(struct inode *inode, struct file *file)
{
    printk(KERN_INFO "[HELLOWORLD] open.\n");
    return 0;
}

static int helloworld_release(struct inode *inode, struct file *file)
{
    printk(KERN_INFO "[HELLOWORLD] release.\n");
    return 0;
}

static ssize_t helloworld_read(struct file *file, char __user *buf, size_t len, loff_t *ppos)
{
    printk(KERN_INFO "[HELLOWORLD] read.\n");
    return 0;
}

static ssize_t helloworld_write(struct file *file, const char __user *buf, size_t len, loff_t *ppos)
{
    printk(KERN_INFO "[HELLOWORLD] write.\n");
    return 0;
}

static int helloworld_flush(struct file *file, fl_owner_t id)
{
    printk(KERN_INFO "[HELLOWORLD] flush.\n");
    return 0;
}

static loff_t helloworld_llseek(struct file *file, loff_t offset, int whence)
{
    printk(KERN_INFO "[HELLOWORLD] llseek.\n");
    return 0;
}

static int helloworld_mmap(struct file *file, struct vm_area_struct *vma)
{
    printk(KERN_INFO "[HELLOWORLD] mmap.\n");
    return 0;
}

static int helloworld_fsync(struct file *file, loff_t start, loff_t end, int datasync)
{
    printk(KERN_INFO "[HELLOWORLD] fsync.\n");
    return 0;
}

static long helloworld_unlocked_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
    int ret = 0;
    int err = 0;
    int size = _IOC_SIZE(cmd);

    printk(KERN_INFO "[HELLOWORLD] ioctl. CMD code: 0x%x\n", cmd);

    if (HELLOWORLD_IOC_MAGIC != _IOC_TYPE(cmd))
    {
        printk(KERN_WARNING "[HELLOWORLD] Invalid TYPE.\n");
        return -ENOTTY;
    }

    if (HELLOWORLD_IOC_MAXNR <= _IOC_NR(cmd))
    {
        printk(KERN_WARNING "[HELLOWORLD] Invalid NR.\n");
        return -ENOTTY;
    }

    if (_IOC_READ & _IOC_DIR(cmd))
    {
        printk(KERN_INFO "[HELLOWORLD] DIR is R.\n");

        // 返回1: 可以访问
        // 返回0: 不可以访问
        // 当方向是读时,说明是从设备读数据到用户空间,因此要检测用户空间的指针是否可写
        err = !access_ok(VERIFY_WRITE, (void __user *)arg, size);
    }
    else if (_IOC_WRITE & _IOC_DIR(cmd))
    {
        printk(KERN_INFO "[HELLOWORLD] DIR is W.\n");

        // 当方向是写时,说明是从用户空间往设备中写数据,因此要检测用户空间的指针是否可读
        err = !access_ok(VERIFY_READ, (void __user *)arg, size);
    }
    else if ((_IOC_READ|_IOC_WRITE) & _IOC_DIR(cmd))
    {
        printk(KERN_INFO "[HELLOWORLD] DIR is RW.\n");

        err = !access_ok(VERIFY_WRITE, (void __user *)arg, size);
        if (err)
        {
            printk(KERN_WARNING "[HELLOWORLD] Invalid W DIR.\n");
            return -EFAULT;
        }

        err = !access_ok(VERIFY_READ, (void __user *)arg, size);
        if (err)
        {
            printk(KERN_WARNING "[HELLOWORLD] Invalid R DIR.\n");
            return -EFAULT;
        }

        // Reset
        err = 0;
    }

    if (err)
    {
        printk(KERN_WARNING "[HELLOWORLD] Invalid DIR.\n");
        return -EFAULT;
    }

    switch (cmd)
    {
    case HELLOWORLD_IOC_HELP:
        printk(KERN_INFO "[HELLOWORLD] HELP.\n");
        ret = onHelp();
        break;
    case HELLOWORLD_IOC_RESET:
        printk(KERN_INFO "[HELLOWORLD] RESET.\n");
        ret = onReset();
        break;
    case HELLOWORLD_IOR_DESCRIPTION:
        printk(KERN_INFO "[HELLOWORLD] DESCRIPTION.\n");
        ret = onDescription(arg, size);
        break;
    case HELLOWORLD_IOR_AUTHOR:
        printk(KERN_INFO "[HELLOWORLD] AUTHOR.\n");
        ret = onAuthor(arg, size);
        break;
    case HELLOWORLD_IOR_VERSION:
        printk(KERN_INFO "[HELLOWORLD] VERSION.\n");
        ret = onVersion(arg, size);
        break;
    case HELLOWORLD_IOR_LICENSE:
        printk(KERN_INFO "[HELLOWORLD] LICENSE.\n");
        ret = onLicense(arg, size);
        break;
    case HELLOWORLD_IOR_VERBOSE_STATUS:
        printk(KERN_INFO "[HELLOWORLD] VERBOSE_STATUS.\n");
        ret = onVerboseStatus(arg, size);
        break;
    case HELLOWORLD_IOW_VERBOSE_ENABLE:
        printk(KERN_INFO "[HELLOWORLD] VERBOSE_ENABLE.\n");
        ret = onVerboseEnable(arg, size);
        break;
    case HELLOWORLD_IOWR_TOKEN:
        printk(KERN_INFO "[HELLOWORLD] TOKEN.\n");
        ret = onToken(arg, size);
        break;
    default:
        printk(KERN_WARNING "[HELLOWORLD] Unknown CMD code: [0x%x]\n", cmd);
        return -EINVAL;
    }

    return ret;
}

static long helloworld_compat_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
    printk(KERN_INFO "[HELLOWORLD] compat_ioctl.\n");
    return helloworld_unlocked_ioctl(file, cmd, arg);
}

static int onHelp(void)
{
    printk(KERN_INFO "[HELLOWORLD] Description: %s\n", THIS_DESCRIPTION);
    printk(KERN_INFO "[HELLOWORLD] Author: %s\n", THIS_AUTHOR);
    printk(KERN_INFO "[HELLOWORLD] Version: %s\n", THIS_VERSION);
    printk(KERN_INFO "[HELLOWORLD] License: %s\n", THIS_LICENSE);

    return 0;
}

static int onReset(void)
{
    s_verbose_status = STATUS_OFF;

    return 0;
}

static int onDescription(unsigned long to, int toSize)
{
    int fromSize = sizeof(THIS_DESCRIPTION);
    if (toSize < fromSize)
    {
        printk(KERN_WARNING "[HELLOWORLD] Get Description: Out of memory. toSize: %d, fromSize: %d\n", toSize, fromSize);
        return -ENOMEM;
    }

    //  static inline long copy_to_user(void __user *to, const void *from, unsigned long n);
    return copy_to_user((void __user *)to, (const void *)(THIS_DESCRIPTION), fromSize);
}

static int onAuthor(unsigned long to, int toSize)
{
    int fromSize = sizeof(THIS_AUTHOR);
    if (toSize < fromSize)
    {
        printk(KERN_WARNING "[HELLOWORLD] Get Author: Out of memory. toSize: %d, fromSize: %d\n", toSize, fromSize);
        return -ENOMEM;
    }

    return copy_to_user((void __user *)to, (const void *)(THIS_AUTHOR), fromSize);
}

static int onVersion(unsigned long to, int toSize)
{
    int fromSize = sizeof(THIS_VERSION);
    if (toSize < fromSize)
    {
        printk(KERN_WARNING "[HELLOWORLD] Get Version: Out of memory. toSize: %d, fromSize: %d\n", toSize, fromSize);
        return -ENOMEM;
    }

    return copy_to_user((void __user *)to, (const void *)(THIS_VERSION), fromSize);
}

static int onLicense(unsigned long to, int toSize)
{
    int fromSize = sizeof(THIS_LICENSE);
    if (toSize < fromSize)
    {
        printk(KERN_WARNING "[HELLOWORLD] Get License: Out of memory. toSize: %d, fromSize: %d\n", toSize, fromSize);
        return -ENOMEM;
    }

    return copy_to_user((void __user *)to, (const void *)(THIS_LICENSE), fromSize);
}

static int onVerboseStatus(unsigned long to, int toSize)
{
    int fromSize = sizeof(s_verbose_status);
    if (toSize != fromSize)
    {
        printk(KERN_WARNING "[HELLOWORLD] Get VerboseStatus: Invalid argument. toSize: %d, fromSize: %d\n", toSize, fromSize);
        return -EINVAL;
    }

    return copy_to_user((void __user *)to, (const void *)(&s_verbose_status), fromSize);
}

static int onVerboseEnable(unsigned long from, int fromSize)
{
    int verboseStatus = 0;
    int toSize = sizeof(verboseStatus);
    if (toSize != fromSize)
    {
        printk(KERN_WARNING "[HELLOWORLD] Set VerboseEnable: Invalid argument. toSize: %d, fromSize: %d\n", toSize, fromSize);
        return -EINVAL;
    }

    // static inline long copy_from_user(void *to, const void __user * from, unsigned long n)
    copy_from_user((void *)(&verboseStatus), (const void __user *)from, fromSize);

    if (verboseStatus != s_verbose_status)
    {
        if ((STATUS_ON != verboseStatus) && (STATUS_OFF != verboseStatus))
        {
            printk(KERN_WARNING "[HELLOWORLD] Set VerboseEnable: Invalid argument. fromVerboseStatus: %d\n", verboseStatus);
            return -EINVAL;
        }

        s_verbose_status = verboseStatus;
    }

    return 0;
}

static int onToken(unsigned long buf, int len)
{
    struct TOKEN_S tokenContext;

    copy_from_user((void *)(&tokenContext), (const void __user *)buf, len);

    if (DIR_READ == tokenContext.dir)
    {
        return copy_to_user((void __user *)buf, (const void *)(&s_token_context), len);
    }
    else if (DIR_WRITE == tokenContext.dir)
    {
        return copy_from_user((void *)(&s_token_context), (const void __user *)buf, len);
    }
    else
    {
        printk(KERN_WARNING "[HELLOWORLD] Unknown Token DIR: %d\n", tokenContext.dir);
        return -EINVAL;
    }

    return 0;
}

module_init(helloworld_init);
module_exit(helloworld_exit);
