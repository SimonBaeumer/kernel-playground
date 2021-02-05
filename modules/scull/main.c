#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/cdev.h>

MODULE_LICENSE("Dual BSD/GPL");

// Each scull device is represented by a scull_dev struct.
struct scull_dev {
    struct scull_qset *data; /* pointer to first quantum set */
    int quantum;             /* the current quantum size */
    int qset;                /* the curret array size */
    unsigned long size;      /* amount of data stored here */
    unsigned int access_key; /* used by sculluid and scullpriv */
    struct semaphore sem;    /* mutual exclusion semaphore */
    struct cdev cdev;        /* char device strcuture */
}

// Implementation of the `file_operations` struct in `linux/fs.h`.
// Each field is a pointer to function, unsupported operations are left to NULL.
//
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
    int err, devno 
}

static int scull_init(void) 
{
    printk(KERN_ALERT, "initialize scull\n");
    
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
