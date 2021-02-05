#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/cdev.h>
#include <scull.h>

MODULE_LICENSE("Dual BSD/GPL");

module_param(scull_major, int, S_IRUGO);
module_param(scull_minor, int, S_IRGUO);
module_param(scull_nr_devs, int, S_IRGUO);


// Implementation of the `file_operations` struct in `linux/fs.h`.
// Each field is a pointer to function, unsupported operations are left to NULL.
struct file_operations scull_fops = {
    .owner   = THIS_MODULE,
    .llseek  = scull_llseek,
    .read    = scull_read,
    .write   = scull_write,
    .ioctl   = scull_ioctl,
    .open    = scull_open,
    .release = scull_release,
}

static void scull_setup_cdev(struct scull_dev *dev, int index)
{
    int err, devno = MKDEV(scull_major, scull_minor + index);

    cdev_init(&dev->cdev, &scull_fops);
    dev->cdev.owner = THIS_MODULE;
    dev->cdev.ops = &scull_fops;
    err = cdev_add(&dev->cdev, devno, 1);

    if (err)
        printk(KERN_NOTICE, "Error %d adding scull %d", err, index)
}

static int scull_init(void) 
{
    printk(KERN_ALERT, "initialize scull\n");

    if (scull_major) {
        dev = MKDEV(scull_major, scull_minor);
        result = register_chrdev_region(dev, scull_nr_devs, "scull");
    } else {
        result = alloc_chrdev_region(&dev, scull_minor, scull_nr_devs, "scull");
        scull_major = MAJOR(dev);
    }
    if (result < 0) {
        printk(KERN_WARNING "scull: can't get major %d\n", scull_major)
    }
    
    // cdev_add enables the driver for the kernel
    // this should be added only add the end of the init function.
    return 0;
}

static void scull_exit(void)
{
    printk(KERN_ALERT, "exit scull\n")
    // cdev_del on the hand should only be called if the kernel does not access the drive
    // anymore.
}
