test.c 驱动模块的代码 Makefile编译
poll_driver.c 是上层C程序代码，用gcc编译

挂载 sudo insmod test.ko
设备挂载的位置  /dev/mytest_device
debug节点的位置 /sys/class/mytest_class/mytest_device/my_device_test

监听的是/dev/mytest_device
cat和echo的是/sys/class/mytest_class/mytest_device/my_device_test


