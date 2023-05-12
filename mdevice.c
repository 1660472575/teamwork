// 编写一个应用程序，在应用程序执行之前，挂在设备
#include <linux/module.h> 
#include <linux/init.h> 
#include <linux/platform_device.h> 

#define DRIVER_NAME "hello_ctl" 

MODULE_LICENSE("Dual BSD/GPL"); 
MODULE_AUTHOR("TOPEET"); 

static void leds_release(struct device *dev) 
{ 
    printk("leds_release"); 
} 
struct platform_device platform_device_hello = 
{ 
    .name = "module_device_init", 
    .id = -1, 
    .dev = { .release = leds_release, }, 
}; 
static int hello_init(void) 
{ 
    printk(KERN_EMERG "module device init success !\n"); 
    platform_device_register(&platform_device_hello); 
    return 0; 
}
static void hello_exit(void) { 
    printk(KERN_EMERG "module device exit success \n"); 
    platform_device_unregister(&platform_device_hello); 
} 
//1、 入口函数module_nint 
module_init(hello_init); 
module_exit(hello_exit);