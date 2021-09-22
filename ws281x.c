/* SPDX-License-Identifier: GPL-2.0 */
/* Copyright 2021 Stefan Misik.  All rights reserved. */

#include <linux/list.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/platform_device.h>
#include <linux/miscdevice.h>
#include <linux/of_device.h>

#define DEV_NAME "ws281x"
#define OUT_CNT 2

struct led_out
{
	struct list_head queue;

	char devname[64];
	struct miscdevice miscdev;
};

struct led_file;

struct led_buffer
{
	struct list_head queue;
	struct led_file * owner;

	size_t capacity;
	size_t length;
	char data[0];
};

struct led_file
{
	int led_out;
	struct led_buffer * my_buffer;
	bool buffer_is_enqueued;
};


static struct led_out all_led_outs[OUT_CNT];

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

static int ws281x_probe(struct platform_device *pdev)
{
	int out_n;
    int retval = 0;

	for (out_n = 0; out_n != OUT_CNT; ++out_n)
	{
		struct led_out * cur_out = &all_led_outs[out_n];
		INIT_LIST_HEAD(&cur_out->queue);

		snprintf(cur_out->devname, sizeof(cur_out->devname),
				DEV_NAME "%i", out_n);
		// just to be sure
		cur_out->devname[sizeof(cur_out->devname) - 1] = '\0';

		cur_out->miscdev.minor = MISC_DYNAMIC_MINOR;
		cur_out->miscdev.name = cur_out->devname;
		cur_out->miscdev.fops = &ws281x_fops;
		retval = misc_register(&cur_out->miscdev);
		if (0 != retval)
		{
			pr_err("Could not register the misc device '%s'.\n",
					cur_out->devname);
			goto error;
		}
	}

    return 0;

    error:
	// Deregister all already registered devices
	while (0 != out_n)
	{
		--out_n;
		misc_deregister(&all_led_outs[out_n].miscdev);
	}
	return retval;
}

static int ws281x_remove(struct platform_device *pdev)
{
	int out_n;

	for (out_n = 0; out_n != OUT_CNT; ++out_n)
	{
		struct led_out * cur_out = &all_led_outs[out_n];

		// TODO Clean-up enqueued buffers

		misc_deregister(&cur_out->miscdev);
	}

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
