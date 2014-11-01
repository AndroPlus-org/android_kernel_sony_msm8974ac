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

int taiko_write(struct snd_soc_codec *codec, unsigned int reg,
	unsigned int value);
unsigned int taiko_read(struct snd_soc_codec *codec,
				unsigned int reg);

extern struct snd_soc_codec *wcd9320_codec;

extern bool hplanagain_con;
extern bool hpranagain_con;
extern bool hpldiggain_con;
extern bool hprdiggain_con;
extern bool spkdiggain_con;
extern bool spkdrv_ena;
extern int  uhqa_mode;

extern bool hpwidget;
extern bool spkwidget;

extern u32 hplanagain;
extern u32 hpranagain;
extern u32 hpldiggain;
extern u32 hprdiggain;
extern u32 spkdiggain;

#define TAIKO_HPH_VOL_MASK			0x1F
#define TAIKO_HPH_GAIN_ENABLE			BIT(5)
#define TAIKO_A_RX_HPH_L_GAIN_DEF		0x25
#define TAIKO_A_RX_HPH_R_GAIN_DEF		0x25

#define TAIKO_A_CDC_RXX_VOL_MASK		0x7F
#define TAIKO_A_CDC_RXX_VOL_CTL_DISABLE		BIT(7)
#define TAIKO_A_CDC_RX1_VOL_CTL_B2_CTL_DEF	0xFE
#define TAIKO_A_CDC_RX2_VOL_CTL_B2_CTL_DEF	0xFE
#define TAIKO_A_CDC_RX7_VOL_CTL_B2_CTL_DEF	0xFF

#define TAIKO_A_SPKR_DRV_EN_DEF			0xEF
