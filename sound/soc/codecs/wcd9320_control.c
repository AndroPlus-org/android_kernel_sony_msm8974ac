/* 
 * WCD9320 Taiko Audio Codec Control
 * 
 * Author: Ji Huang <cocafehj@gmail.com> (cocafe@xda-developers.com)
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include <linux/module.h>
#include <linux/kobject.h>
#include <sound/soc.h>
#include <linux/mfd/wcd9xxx/wcd9320_registers.h>
#include "wcd9320_control.h"

#define TAIKO_CONTROL_VERSION			"r02"

struct snd_soc_codec *wcd9320_codec;

int  uhqa_mode = 1;

bool hplanagain_con = false;
bool hpranagain_con = false;
bool hpldiggain_con = false;
bool hprdiggain_con = false;
bool spkdiggain_con = true;
bool spkdrv_ena = true;

bool hpwidget = false;
bool spkwidget = false;

u32 hplanagain = 0x20;
u32 hpranagain = 0x20;
u32 hpldiggain = 0x08;
u32 hprdiggain = 0x08;
u32 spkdiggain = 0x02;

static ssize_t version_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
	return sprintf(buf, "WCD9320 Taiko Control, (cocafe), version: %s\n", TAIKO_CONTROL_VERSION);
}

static ssize_t version_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count)
{
	return count;
}
static struct kobj_attribute version_interface = __ATTR(version, 0644, version_show, version_store);

static ssize_t hplana_gain_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
	u32 vol = taiko_read(wcd9320_codec, TAIKO_A_RX_HPH_L_GAIN) & TAIKO_HPH_VOL_MASK;
	u32 usr = hplanagain & TAIKO_HPH_VOL_MASK;

	sprintf(buf,   "Status: %s\n", hplanagain_con ? "on" : "off");
	sprintf(buf, "%sRegister: %d (%#04x %#04x)\n", buf, vol, vol, taiko_read(wcd9320_codec, TAIKO_A_RX_HPH_L_GAIN));
	sprintf(buf, "%sUser: %d (%#04x %#04x)\n", buf, usr, usr, hplanagain);

	return strlen(buf);
}

static ssize_t hplana_gain_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count)
{
	u32 usr;

	if (sysfs_streq(buf, "on")) {
		hplanagain_con = true;

		if (hpwidget)
			taiko_write(wcd9320_codec, TAIKO_A_RX_HPH_L_GAIN, hplanagain);

		return count;
	}

	if (sysfs_streq(buf, "off")) {
		hplanagain_con = false;

		taiko_write(wcd9320_codec, 
			TAIKO_A_RX_HPH_L_GAIN, 
			TAIKO_A_RX_HPH_L_GAIN_DEF);

		return count;
	}

	if (sscanf(buf, "reg=%x", &usr)) {
		taiko_write(wcd9320_codec, TAIKO_A_RX_HPH_L_GAIN, usr);

		return count;
	}

	if (sscanf(buf, "%u", &usr)) {
		if (usr > TAIKO_HPH_VOL_MASK)
			return -EINVAL;

		hplanagain = usr | TAIKO_HPH_GAIN_ENABLE;

		if (hpwidget && hplanagain_con)
			taiko_write(wcd9320_codec, TAIKO_A_RX_HPH_L_GAIN, hplanagain);

		return count;
	}

	return count;
}
static struct kobj_attribute hplana_gain_interface = __ATTR(hplana_gain, 0644, hplana_gain_show, hplana_gain_store);

static ssize_t hprana_gain_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
	u32 vol = taiko_read(wcd9320_codec, TAIKO_A_RX_HPH_R_GAIN) & TAIKO_HPH_VOL_MASK;
	u32 usr = hpranagain & TAIKO_HPH_VOL_MASK;

	sprintf(buf,   "Status: %s\n", hpranagain_con ? "on" : "off");
	sprintf(buf, "%sRegister: %d (%#04x %#04x)\n", buf, vol, vol, taiko_read(wcd9320_codec, TAIKO_A_RX_HPH_R_GAIN));
	sprintf(buf, "%sUser: %d (%#04x %#04x)\n", buf, usr, usr, hpranagain);

	return strlen(buf);
}

static ssize_t hprana_gain_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count)
{
	u32 usr;

	if (sysfs_streq(buf, "on")) {
		hpranagain_con = true;

		if (hpwidget)
			taiko_write(wcd9320_codec, TAIKO_A_RX_HPH_R_GAIN, hpranagain);

		return count;
	}

	if (sysfs_streq(buf, "off")) {
		hpranagain_con = false;

		taiko_write(wcd9320_codec, 
			TAIKO_A_RX_HPH_R_GAIN, 
			TAIKO_A_RX_HPH_R_GAIN_DEF);

		return count;
	}

	if (sscanf(buf, "reg=%x", &usr)) {
		taiko_write(wcd9320_codec, TAIKO_A_RX_HPH_R_GAIN, usr);

		return count;
	}

	if (sscanf(buf, "%u", &usr)) {
		if (usr > TAIKO_HPH_VOL_MASK)
			return -EINVAL;

		hpranagain = usr | TAIKO_HPH_GAIN_ENABLE;

		if (hpwidget && hpranagain_con)
			taiko_write(wcd9320_codec, TAIKO_A_RX_HPH_R_GAIN, hpranagain);

		return count;
	}

	return count;
}
static struct kobj_attribute hprana_gain_interface = __ATTR(hprana_gain, 0644, hprana_gain_show, hprana_gain_store);

#define _RX_VOL_CONTROL(_file, _uval, _con, _reg, _wdg)			\
static ssize_t _file##_show(struct kobject *kobj, 			\
	struct kobj_attribute *attr, char *buf)				\
{									\
	u32 reg = taiko_read(wcd9320_codec, _reg);			\
	u32 usr = _uval;						\
									\
	sprintf(buf,   "Status: %s\n", _con ? "on" : "off");		\
	sprintf(buf, "%sRegister: %d (%#04x)\n", buf, reg, reg);	\
	sprintf(buf, "%sUser: %d (%#04x)\n", buf, usr, usr);		\
									\
	return strlen(buf);						\
}									\
									\
static ssize_t _file##_store(struct kobject *kobj, 			\
	struct kobj_attribute *attr, const char *buf, size_t count)	\
{									\
	u32 usr;							\
									\
	if (sysfs_streq(buf, "on")) {					\
		_con = true;						\
									\
		if (_wdg)						\
			taiko_write(wcd9320_codec, _reg, _uval);	\
									\
		return count;						\
	}								\
									\
	if (sysfs_streq(buf, "off")) {					\
		_con = false;						\
									\
		taiko_write(wcd9320_codec, 				\
			_reg, 						\
			_reg##_DEF);					\
									\
		return count;						\
	}								\
									\
	if (sscanf(buf, "reg=%x", &usr)) {				\
		taiko_write(wcd9320_codec, _reg, usr);			\
									\
		return count;						\
	}								\
									\
	if (sscanf(buf, "%d", &usr)) {					\
		if (usr > TAIKO_A_CDC_RXX_VOL_MASK)			\
			return -EINVAL;					\
									\
		_uval = usr;						\
									\
		if (_wdg && _con)					\
			taiko_write(wcd9320_codec, _reg, _uval);	\
									\
		return count;						\
	}								\
									\
	return count;							\
}									\
static struct kobj_attribute _file##_interface = 			\
	__ATTR(_file, 0644, _file##_show, _file##_store);

_RX_VOL_CONTROL(hpldig_gain, hpldiggain, hpldiggain_con, TAIKO_A_CDC_RX1_VOL_CTL_B2_CTL, hpwidget);
_RX_VOL_CONTROL(hprdig_gain, hprdiggain, hprdiggain_con, TAIKO_A_CDC_RX2_VOL_CTL_B2_CTL, hpwidget);
_RX_VOL_CONTROL(spkdig_gain, spkdiggain, spkdiggain_con, TAIKO_A_CDC_RX7_VOL_CTL_B2_CTL, spkwidget);

static ssize_t spkdrv_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
	sprintf(buf, "Speaker Driver: %s\n", spkdrv_ena ? "on" : "off");

	return strlen(buf);
}

static ssize_t spkdrv_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count)
{
	if (sysfs_streq(buf, "on")) {
		spkdrv_ena = true;

		if (spkwidget)
			taiko_write(wcd9320_codec,
				TAIKO_A_SPKR_DRV_EN,
				TAIKO_A_SPKR_DRV_EN_DEF);

		return count;
	}

	if (sysfs_streq(buf, "off")) {
		spkdrv_ena = false;

		if (spkwidget)
			taiko_write(wcd9320_codec,
				TAIKO_A_SPKR_DRV_EN,
				TAIKO_A_SPKR_DRV_EN__POR);

		return count;
	}

	return count;
}
static struct kobj_attribute spkdrv_interface = __ATTR(spkdrv, 0644, spkdrv_show, spkdrv_store);

#define _BIAS_CONTROL_(_file, _string, _reg, _por)			\
static ssize_t _file##_show(struct kobject *kobj, 			\
	struct kobj_attribute *attr, char *buf)				\
{									\
	u32 regval = taiko_read(wcd9320_codec, _reg);			\
									\
	sprintf(buf, "%s: %d%% (%#04x:%#04x)\n",			\
			_string,					\
			regval * 100 / _por,				\
			regval,						\
			_por);						\
									\
	return strlen(buf);						\
}									\
									\
static ssize_t _file##_store(struct kobject *kobj, 			\
	struct kobj_attribute *attr, const char *buf, size_t count)	\
{									\
	u32 per;							\
	u32 regval;							\
									\
	if (!sscanf(buf, "%u", &per))					\
		return -EINVAL;						\
									\
	if (per < 0)							\
		return -EINVAL;						\
									\
	regval = (u32)(_por * per / 100);				\
									\
	if (regval > 0xff)						\
		regval = 0xff;						\
									\
	taiko_write(wcd9320_codec, _reg, regval);			\
									\
	return count;							\
}									\
static struct kobj_attribute _file##_interface = 			\
	__ATTR(_file, 0644, _file##_show, _file##_store);

_BIAS_CONTROL_(hpdac_bias,   "Headphone DAC PowerBias", 
		TAIKO_A_RX_HPH_BIAS_PA,  TAIKO_A_RX_HPH_BIAS_PA__POR);
_BIAS_CONTROL_(hpldo_bias,   "Headphone LDO PowerBias", 
		TAIKO_A_RX_HPH_BIAS_LDO, TAIKO_A_RX_HPH_BIAS_LDO__POR);
_BIAS_CONTROL_(eardac_bias,  "Earpiece DAC PowerBias", 
		TAIKO_A_RX_EAR_BIAS_PA,  TAIKO_A_RX_EAR_BIAS_PA__POR);
_BIAS_CONTROL_(linedac_bias, "LineOut DAC PowerBias", 
		TAIKO_A_RX_LINE_BIAS_PA, TAIKO_A_RX_LINE_BIAS_PA__POR);
_BIAS_CONTROL_(spkdac_bias,  "Speaker DAC PowerBias", 
		TAIKO_A_SPKR_DRV_BIAS_PA, TAIKO_A_SPKR_DRV_BIAS_PA__POR);

static ssize_t hph_uhqa_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
	sprintf(buf, "Ultra High Quality Audio Mode: %s\n", uhqa_mode ? "on" : "off");

	return strlen(buf);
}

static ssize_t hph_uhqa_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count)
{
	if (sysfs_streq(buf, "on")) {
		/*
		 * Need to restart HPH to trigger dapm events to update ClassH state
		 */
		uhqa_mode = 1;

		if (hpwidget) {
			taiko_write(wcd9320_codec, TAIKO_A_RX_HPH_L_PA_CTL, 0x48);
			taiko_write(wcd9320_codec, TAIKO_A_RX_HPH_R_PA_CTL, 0x48);
			taiko_write(wcd9320_codec, TAIKO_A_RX_HPH_BIAS_PA,  0xAA);
			snd_soc_update_bits(wcd9320_codec, TAIKO_A_RX_HPH_CHOP_CTL, 0x20, 0x00);
		}

		return count;
	}

	if (sysfs_streq(buf, "off")) {
		uhqa_mode = 0;

		taiko_write(wcd9320_codec, TAIKO_A_RX_HPH_L_PA_CTL, 0x40);
		taiko_write(wcd9320_codec, TAIKO_A_RX_HPH_R_PA_CTL, 0x40);
		taiko_write(wcd9320_codec, TAIKO_A_RX_HPH_BIAS_PA,  0x55);
		snd_soc_update_bits(wcd9320_codec, TAIKO_A_RX_HPH_CHOP_CTL, 0x20, 0x20);

		return count;
	}

	return -EINVAL;
}
static struct kobj_attribute hph_uhqa_interface = __ATTR(hph_uhqa, 0644, hph_uhqa_show, hph_uhqa_store);

static struct attribute *taiko_control_attrs[] = {
	&version_interface.attr,
	&hplana_gain_interface.attr,
	&hprana_gain_interface.attr,
	&hpldig_gain_interface.attr,
	&hprdig_gain_interface.attr,
	&spkdig_gain_interface.attr,
	&spkdrv_interface.attr,
	&hpdac_bias_interface.attr,
	&hpldo_bias_interface.attr,
	&eardac_bias_interface.attr,
	&linedac_bias_interface.attr,
	&spkdac_bias_interface.attr,
	&hph_uhqa_interface.attr,
	NULL,
};

static struct attribute_group taiko_control_interface_group = {
	.attrs = taiko_control_attrs,
};

static struct attribute *taiko_debug_attrs[] = {
	NULL,
};

static struct attribute_group taiko_debug_interface_group = {
	.attrs = taiko_debug_attrs,
	.name  = "debug",
};

static struct kobject *taiko_control_kobject;

static int __init taiko_control_init(void)
{
	int ret;

	taiko_control_kobject = kobject_create_and_add("wcd9320", kernel_kobj);
	if (!taiko_control_kobject) {
		pr_err("Taiko Control: Failed to create kobject interface\n");
	}
	ret = sysfs_create_group(taiko_control_kobject, &taiko_control_interface_group);
	if (ret) {
		kobject_put(taiko_control_kobject);
	}

	ret = sysfs_create_group(taiko_control_kobject, &taiko_debug_interface_group);
	if (ret) {
		pr_err("Taiko Control: Failed to create debug sysfs group\n");
	}

	return ret;
}

static void __exit taiko_control_exit(void)
{
	kobject_put(taiko_control_kobject);

	return;
}

module_init(taiko_control_init);
module_exit(taiko_control_exit);

MODULE_DESCRIPTION("Taiko codec controller");
MODULE_AUTHOR("Ji Huang (cocafe)");
MODULE_LICENSE("GPL v2");
