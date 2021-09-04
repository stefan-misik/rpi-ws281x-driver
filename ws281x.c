/* SPDX-License-Identifier: GPL-2.0 */
/* Copyright 2021 Stefan Misik.  All rights reserved. */

#include <linux/module.h>
#include <linux/fs.h>
#include <linux/platform_device.h>
#include <linux/miscdevice.h>
#include <linux/of_device.h>

#define DEV_NAME "ws281x"

static int ws281x_open(struct inode *inode, struct file *file)
{
    return 0;
}

static int ws281x_close(struct inode *inode, struct file *file)
{
    return 0;
}

static long ws281x_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
    return 0;
}

static const struct file_operations ws281x_fops = {
    .owner = THIS_MODULE,
    .open = ws281x_open,
    .release= ws281x_close,
    .unlocked_ioctl = ws281x_ioctl,
};

static struct miscdevice ws281x_miscdev= {
    .minor = MISC_DYNAMIC_MINOR,
    .name = DEV_NAME,
    .fops = &ws281x_fops,
};

static int ws281x_probe(struct platform_device *pdev)
{
    int retval;
    retval = misc_register(&ws281x_miscdev);

    if (0 != retval)
    {
        pr_err("Could not register the misc device " DEV_NAME ".\n");
        return retval;
    }

    pr_info(DEV_NAME ": got minor %i.\n", ws281x_miscdev.minor);
    return 0;
}

static int ws281x_remove(struct platform_device *pdev)
{
    misc_deregister(&ws281x_miscdev);
    pr_info(DEV_NAME ": removed.\n");
    return 0;
}

static const struct of_device_id ws281x_of_ids[] = {
    { .compatible = "leds," DEV_NAME,},
    { },
};
MODULE_DEVICE_TABLE(of, ws281x_of_ids);

static struct platform_driver ws281x_platform_driver = {
    .probe = ws281x_probe,
    .remove = ws281x_remove,
    .driver = {
        .name = DEV_NAME,
        .of_match_table = ws281x_of_ids,
        .owner = THIS_MODULE,
    }
};

module_platform_driver(ws281x_platform_driver);

MODULE_AUTHOR("Stefan Misik");
MODULE_DESCRIPTION("Linux kernel driver for controlling WS281x LEDs");
MODULE_LICENSE("GPL");
