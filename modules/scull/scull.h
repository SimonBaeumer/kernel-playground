#ifndef SCULL_MAJOR
#define SCULL_MAJOR 0
#endif

#ifndef SCULL_NR_DEVS
#define SCULL_NR_DEVS 4
#endif

#ifndef SCULL_P_NR_DEVS
#define SCULL_P_NR_DEVS 4
#endif

extern int scull_major;
extern int scull_nr_devs;

/* scull device structure */
struct scull_dev {
    struct scull_qset *data; /* pointer to first quantum set */
    int quantum;             /* the current quantum size */
    int qset;                /* the curret array size */
    unsigned long size;      /* amount of data stored here */
    unsigned int access_key; /* used by sculluid and scullpriv */
    struct semaphore sem;    /* mutual exclusion semaphore */
    struct cdev cdev;        /* char device strcuture */
}
