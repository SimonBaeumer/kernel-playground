### Installation

```
$ cd modules/hello
$ make
$ sudo insmod hello.ko
$ sudo rmmod hello
```

Display logs with `tail -f /var/log/syslog`

### Notes

 - Functions starting with `__` are generally a low level component and should be used with caution.
 - Kernel has no floating point arithmetic.
 - Kernel stack is 2*PAGE_SIZE big (x86_64 page size is 4K), functions share this stack with the entire kernel-space. Larger structures are allocated dynamically at runtime.
