#include <linux/module.h>
#include <linux/init.h>
#include <linux/platform_device.h>
#include <linux/gpio.h>
#include <linux/delay.h>
#include <linux/regulator/consumer.h>
#include <sound/soc.h>
#include <sound/jack.h>
#include <linux/poll.h>

static  char mybuf[100]="123";
static DECLARE_WAIT_QUEUE_HEAD(wait_queue);
unsigned int condition = 0;

// cat命令时,将会调用该函数
static ssize_t show_my_device(struct device *dev,
                              struct device_attribute *attr, char *buf)
{
    printk("device is read. \n");
    return sprintf(buf, "%s\n", mybuf);
}

//echo命令时,将会调用该函数
static ssize_t set_my_device(struct device *dev,
                             struct device_attribute *attr,
                             const char *buf, size_t len)
{
    printk("device is writed. \n");
    //从睡眠队列中唤醒
    wake_up(&wait_queue);
    condition = 1;
    return len;
}


static int open (struct inode *inode, struct file *file)
{
    printk("device is opened. \n");
    return 0;
}

unsigned int demo_poll(struct file * filep, struct poll_table_struct * table)
{
    unsigned int mask = 0;
    // 将wq添加table列表当中
    poll_wait(filep, &wait_queue, table);

	if(condition)
		mask = POLLIN;
	condition = 0;
	return mask;
}

// 定义一个名字为my_device_test的设备属性文件
static DEVICE_ATTR(my_device_test, S_IWUSR|S_IRUSR, show_my_device, set_my_device);

struct file_operations mytest_ops={
    .owner  = THIS_MODULE,
    .poll   = demo_poll,
    .open   = open,
};

static int major;
static struct class *cls;
static int mytest_init(void)
{
    struct device *mydev;
    major=register_chrdev(0, "mytest", &mytest_ops);
    cls=class_create(THIS_MODULE, "mytest_class");

    //创建mytest_device设备
    mydev = device_create(cls, 0, MKDEV(major, 0), NULL, "mytest_device");
    printk("driver init ^_^");

    //在mytest_device设备目录下创建一个my_device_test属性文件
    if(sysfs_create_file(&(mydev->kobj), &dev_attr_my_device_test.attr)) {
        return -1;
    }

    return 0;
}

static void mytest_exit(void)
{
    device_destroy(cls, MKDEV(major, 0));
    class_destroy(cls);
    unregister_chrdev(major, "mytest");
    printk("driver exit ^@^");
}

module_init(mytest_init);
module_exit(mytest_exit);
MODULE_LICENSE("GPL");
