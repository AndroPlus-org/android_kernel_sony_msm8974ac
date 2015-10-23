/* arch/arm/mach-msm/board-sony_shinano-wifi.c
 *
 * Copyright (C) 2013 Sony Mobile Communications Inc.
 * Copyright (C) 2013 LGE, Inc
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include <asm/gpio.h>
#include <asm/mach/mmc.h>
#include <linux/qpnp/pin.h>
#include <linux/regulator/consumer.h>
#include <linux/skbuff.h>
#include <linux/wlan_plat.h>

#include <mach/board-sony_shinano-wifi.h>

static int shinano_wifi_cd;
static void (*wifi_status_cb)(int card_present, void *dev_id);
static void *wifi_status_cb_devid;
static struct regulator *wifi_batfet;
static int batfet_ena;

#define WIFI_POWER_PMIC_GPIO 18
#define WIFI_IRQ_GPIO 67

/* These definitions need to be aligned with bcmdhd */
#define ESCAN_BUF_SIZE (64 * 1024) /* for WIPHY_ESCAN0 */
#define WLAN_MEM_ARRAY_SENTINEL \
		(sizeof(wlan_mem_array)/sizeof(wlan_mem_array[0]))

#define WLAN_STATIC_SKB (WLAN_MEM_ARRAY_SENTINEL+1)

#if defined(CONFIG_64BIT)
#define WLAN_DHD_INFO_BUF_SIZE                        (24 * 1024)
#define WLAN_STATIC_DHD_WLFC_INFO_SIZE                (64 * 1024)
#define WLAN_STATIC_DHD_WLFC_HANGER_SIZE              (128 * 1024)
#else
#define WLAN_DHD_INFO_BUF_SIZE                        (16 * 1024)
#define WLAN_STATIC_DHD_WLFC_INFO_SIZE                (24 * 1024)
#define WLAN_STATIC_DHD_WLFC_HANGER_SIZE              (64 * 1024)
#endif /* CONFIG_64BIT */

#define SIZE_ORDER(x) ((1 << x) * PAGE_SIZE)

/* These definitions are copied from bcmdhd */
#define DHD_SKB_HDRSIZE 336
#define DHD_SKB_1PAGE_BUFSIZE ((PAGE_SIZE * 1) - DHD_SKB_HDRSIZE)
#define DHD_SKB_2PAGE_BUFSIZE ((PAGE_SIZE * 2) - DHD_SKB_HDRSIZE)
#define DHD_SKB_4PAGE_BUFSIZE ((PAGE_SIZE * 4) - DHD_SKB_HDRSIZE)

#define WLAN_SKB_BUF_NUM 17 /* 8 for 1PAGE, 8 for 2PAGE, 1 for 4PAGE */

static struct sk_buff *wlan_static_skb[WLAN_SKB_BUF_NUM];

struct wlan_mem_prealloc {
	void *mem_ptr;
	unsigned long size;
};

static struct wlan_mem_prealloc wlan_mem_array[] = {
	{NULL, (SIZE_ORDER(2))}, /* for PROT  (0) */
	{NULL, (SIZE_ORDER(2))}, /* for RXBUF (1) */
	{NULL, (SIZE_ORDER(4))}, /* for DATABUF (2) */
	{NULL, (SIZE_ORDER(2))}, /* for osl (3) */
	{NULL, (0)}, /* (4) */
	{NULL, ESCAN_BUF_SIZE},  /* wlan_static_scan (5) */
	{NULL, (0)}, /* (6) */
	{NULL, WLAN_DHD_INFO_BUF_SIZE}, /* dhd_info (7) */
	{NULL, WLAN_STATIC_DHD_WLFC_INFO_SIZE}, /* WLFC_HANGER_INFO (8) */
	{NULL, (0)}, /* (9) */
	{NULL, (0)}, /* (10) */
	{NULL, (0)}, /* (11) */
	{NULL, WLAN_STATIC_DHD_WLFC_HANGER_SIZE}, /* WLFC_HANGER_SIZE (12) */
};


static int shinano_wifi_init_mem(void)
{
	int i;
	for (i = 0; i < WLAN_SKB_BUF_NUM; i++)
		wlan_static_skb[i] = NULL;

	for (i = 0; i < 8; i++) {
		wlan_static_skb[i] = dev_alloc_skb(DHD_SKB_1PAGE_BUFSIZE);
		if (!wlan_static_skb[i])
			goto err_skb_alloc;
	}

	for (; i < 16; i++) {
		wlan_static_skb[i] = dev_alloc_skb(DHD_SKB_2PAGE_BUFSIZE);
		if (!wlan_static_skb[i])
			goto err_skb_alloc;
	}

	wlan_static_skb[i] = dev_alloc_skb(DHD_SKB_4PAGE_BUFSIZE);
	if (!wlan_static_skb[i])
		goto err_skb_alloc;

	for (i = 0; i < WLAN_MEM_ARRAY_SENTINEL; i++) {
		wlan_mem_array[i].mem_ptr =
			kmalloc(wlan_mem_array[i].size, GFP_KERNEL);
		if (!wlan_mem_array[i].mem_ptr)
			goto err_mem_alloc;
	}

	return 0;

err_mem_alloc:
	printk(KERN_ERR "%s: failed to allocate mem_alloc\n", __func__);
	for (i--; i >= 0; i--) {
		kfree(wlan_mem_array[i].mem_ptr);
		wlan_mem_array[i].mem_ptr = NULL;
	}

	i = WLAN_SKB_BUF_NUM;
err_skb_alloc:
	printk(KERN_ERR "%s: failed to allocate skb_alloc\n", __func__);
	for (i--; i >= 0; i--) {
		dev_kfree_skb(wlan_static_skb[i]);
		wlan_static_skb[i] = NULL;
	}

	return -ENOMEM;
}

static void *shinano_wifi_mem_prealloc(int section, unsigned long size)
{
	if (section == WLAN_STATIC_SKB) {
		printk(KERN_INFO "prealloc returning skb, section:%d size:%lu\n",
			section, size);
		return wlan_static_skb;
	}

	if ((section < 0) || (section >= WLAN_MEM_ARRAY_SENTINEL)) {
		printk(KERN_ERR "prealloc returning null %d %lu\n",
			section, size);
		return NULL;
	}

	if (size > wlan_mem_array[section].size) {
		printk(KERN_ERR
			"prealloc too small. Section:%d Size req:%lu Current size:%lu\n",
			section, size, wlan_mem_array[section].size);
		BUG();
		return NULL;
	}

	printk(KERN_INFO "prealloc section %d, requested size: %lu, got size:%lu\n",
			section, size, wlan_mem_array[section].size);
	return wlan_mem_array[section].mem_ptr;
}

int shinano_wifi_set_power(int on)
{
	int gpio = qpnp_pin_map("pm8941-gpio", WIFI_POWER_PMIC_GPIO);
	if (!wifi_batfet) {
		wifi_batfet = regulator_get(NULL, "batfet");
		if (IS_ERR_OR_NULL(wifi_batfet)) {
			printk(KERN_ERR "unable to get batfet reg. rc=%d\n",
				PTR_RET(wifi_batfet));
			wifi_batfet = NULL;
		}
	}
	if (on) {
		if (!batfet_ena && wifi_batfet) {
			regulator_enable(wifi_batfet);
			batfet_ena = 1;
		}
	}
	gpio_set_value(gpio, on);
	if (!on) {
		if (batfet_ena && wifi_batfet) {
			regulator_disable(wifi_batfet);
			batfet_ena = 0;
		}
	}
	return 0;
}

int shinano_wifi_set_carddetect(int val)
{
	shinano_wifi_cd = val;
	if (wifi_status_cb)
		wifi_status_cb(val, wifi_status_cb_devid);
	else
		printk(KERN_WARNING "%s: Nobody to notify\n", __func__);
	return 0;
}

static struct resource shinano_wifi_resources[] = {
	[0] = {
		.name	= "bcmdhd_wlan_irq",
		.flags	= IORESOURCE_IRQ | IORESOURCE_IRQ_HIGHLEVEL |
			  IORESOURCE_IRQ_SHAREABLE,
	},
};

struct wifi_platform_data shinano_wifi_control = {
	.set_power	= shinano_wifi_set_power,
	.set_carddetect	= shinano_wifi_set_carddetect,
	.mem_prealloc	= shinano_wifi_mem_prealloc,
};

static struct platform_device shinano_wifi = {
	.name		= "bcmdhd_wlan",
	.id		= -1,
	.num_resources	= ARRAY_SIZE(shinano_wifi_resources),
	.resource	= shinano_wifi_resources,
	.dev		= {
		.platform_data = &shinano_wifi_control,
	},
};

static int __init shinano_wifi_init(void)
{
	if (shinano_wifi_init_mem())
		return -ENOMEM;
	shinano_wifi.resource->start = gpio_to_irq(WIFI_IRQ_GPIO);
	shinano_wifi.resource->end = gpio_to_irq(WIFI_IRQ_GPIO);
	platform_device_register(&shinano_wifi);
	return 0;
}

device_initcall(shinano_wifi_init);

int shinano_wifi_status_register(
			void (*callback)(int card_present, void *dev_id),
			void *dev_id)
{
	if (wifi_status_cb)
		return -EAGAIN;
	wifi_status_cb = callback;
	wifi_status_cb_devid = dev_id;
	return 0;
}

unsigned int shinano_wifi_status(struct device *dev)
{
	return shinano_wifi_cd;
}
