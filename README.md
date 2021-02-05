### Installation

```
$ cd modules/hello
$ make
$ sudo insmod hello.ko howmany=10 whom="Mars"
$ sudo rmmod hello
```

Display logs with `tail -f /var/log/syslog`

### Notes

 - Functions starting with `__` are generally a low level component and should be used with caution.
 - Kernel has no floating point arithmetic.
 - Kernel stack is 2*PAGE_SIZE big (x86_64 page size is 4K), functions share this stack with the entire kernel-space. Larger structures are allocated dynamically at runtime.
 - `Documentation/Change` lists all requirments for building a linux kernel
 - system calls are prefixed with `sys_´
 - export symbols with `EXPORT_SYMBOL(name)` or `EXPORT_SYMBOL_GPL(name)`
 - add a metadata to the module, i.e. `MODULE_LICENSE("GPL")`, `MODULE_AUTHOR("simon")`, `MODULE_VERSION()`, `MODULE_DESCRIPTION()` and `MODULE_ALIAS()`
 - to allocate RAM use `kmalloc` and `kfree` from `linux/slab.h` 

#### Drivers

 - register a new device `int register_chardev_region(dev_t first, unsigned int count, char *name);`
   - dynamic allocation `int alloc_chrdev_region(dev_t *dev, unsinged int firstminor, unsigned int count, char *name)`
   - unregister `void unregister_chrdev_region(dev_t first, unsinged int count)`
   - statically assigned devices numers in `Documentation/admin-guide/devices.txt`
