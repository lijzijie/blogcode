#include <linux/module.h>
#include <linux/init.h>
#include <linux/platform_device.h>
#include <linux/gpio.h>
#include <linux/delay.h>
#include <linux/regulator/consumer.h>
#include <sound/soc.h>
#include <sound/jack.h>
 
 
static  char mybuf[100]="123";
//cat命令时,将会调用该函数
static ssize_t show_my_device(struct device *dev,
                              struct device_attribute *attr, char *buf)        
{
    return sprintf(buf, "%s\n", mybuf);
}
 
//echo命令时,将会调用该函数
static ssize_t set_my_device(struct device *dev,
                             struct device_attribute *attr,
                             const char *buf, size_t len)        
{
    sprintf(mybuf, "%s", buf);
    return len;
}
//定义一个名字为my_device_test的设备属性文件
static DEVICE_ATTR(my_device_test, S_IWUSR|S_IRUSR, show_my_device, set_my_device);
 
struct file_operations mytest_ops={
    .owner  = THIS_MODULE,
};
 
static int major;
static struct class *cls;
static int mytest_init(void)
{
    struct device *mydev;
    major=register_chrdev(0,"mytest", &mytest_ops);
    cls=class_create(THIS_MODULE, "mytest_class");
    //创建mytest_device设备
    mydev = device_create(cls, 0, MKDEV(major,0),NULL,"mytest_device");    
    
    //在mytest_device设备目录下创建一个my_device_test属性文件
    if(sysfs_create_file(&(mydev->kobj), &dev_attr_my_device_test.attr)) {
        return -1;
    }
    
    return 0;
}
 
static void mytest_exit(void)
{
    device_destroy(cls, MKDEV(major,0));
    class_destroy(cls);
    unregister_chrdev(major, "mytest");
}
 
module_init(mytest_init);
module_exit(mytest_exit);
MODULE_LICENSE("GPL");