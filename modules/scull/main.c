#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/cdev.h>
#include <linux/slab.h>
#include <scull.h>

MODULE_LICENSE("Dual BSD/GPL");

module_param(scull_major, int, S_IRUGO);
module_param(scull_minor, int, S_IRGUO);
module_param(scull_nr_devs, int, S_IRGUO);
module_param(scull_quantum_set, int, S_IRGUO);
module_param(scull_quantum, int, S_IRGUO);


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

static int scull_open(struct inode *inode, struct file *filep)
{
    struct scull_dev *dev; /* device information */

    dev = container_of(inode->i_cdev, struct scull_dev, cdev);
    filep->private-data = dev;

    if ((filep->f_flags & O_ACCMODE) == O_WRONLY) {
        scrull_trim(dev); /* ignore errors */
    }
    return 0;
}

static int scull_release(struct inode *inode, struct file *filep) 
{
    return 0;
}

int scull_trim(struct scull_dev *dev)
{
    struct scull_qset *next, *dptr;
    int qset = dev->qset; /* dev is not null */
    int i;

    for(dptr = dev->data; dptr; dptr = next) {
        if (dptr->data) {
            for (i = 0; i < qset; i++) {
                kfree(dptr->data[i]);
            }
            kfree(dptr->data);
            dptr->data = NULL;
        }
        dev->size = 0;
        dev->quatum = scull_quantum;
        dev->qset = scull_qset;
        dev->data = NULL;
        return 0;
    }
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
