/*
** =============================================================================
** Copyright (c) 2016  Texas Instruments Inc.
**
** This program is free software; you can redistribute it and/or modify it under
** the terms of the GNU General Public License as published by the Free Software
** Foundation; version 2.
**
** This program is distributed in the hope that it will be useful, but WITHOUT
** ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
** FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
**
** File:
**     tas2557-misc.h
**
** Description:
**     header file for tas2557-misc.c
**
** =============================================================================
*/

#ifndef _TAS2557_MISC_H
#define _TAS2557_MISC_H

#define	FW_NAME_SIZE			64
#define	FW_DESCRIPTION_SIZE		256
#define	PROGRAM_BUF_SIZE		(5 + FW_NAME_SIZE + FW_DESCRIPTION_SIZE)
#define	CONFIGURATION_BUF_SIZE	(8 + FW_NAME_SIZE + FW_DESCRIPTION_SIZE)

#define	TIAUDIO_CMD_REG_WITE			1
#define	TIAUDIO_CMD_REG_READ			2
#define	TIAUDIO_CMD_DEBUG_ON			3
#define	TIAUDIO_CMD_PROGRAM			4
#define	TIAUDIO_CMD_CONFIGURATION		5
#define	TIAUDIO_CMD_FW_TIMESTAMP		6
#define	TIAUDIO_CMD_CALIBRATION			7
#define	TIAUDIO_CMD_SAMPLERATE			8
#define	TIAUDIO_CMD_BITRATE			9
#define	TIAUDIO_CMD_DACVOLUME			10
#define	TIAUDIO_CMD_SPEAKER			11
#define	TIAUDIO_CMD_FW_RELOAD			12
#define	TIAUDIO_CMD_AGC				13

#define	TAS2557_MAGIC_NUMBER	0x3537	/* '2557' */

#define	SMARTPA_SPK_DAC_VOLUME				_IOWR(TAS2557_MAGIC_NUMBER, 1, unsigned long)
#define	SMARTPA_SPK_POWER_ON				_IOWR(TAS2557_MAGIC_NUMBER, 2, unsigned long)
#define	SMARTPA_SPK_POWER_OFF				_IOWR(TAS2557_MAGIC_NUMBER, 3, unsigned long)
#define	SMARTPA_SPK_SWITCH_PROGRAM			_IOWR(TAS2557_MAGIC_NUMBER, 4, unsigned long)
#define	SMARTPA_SPK_SWITCH_CONFIGURATION	_IOWR(TAS2557_MAGIC_NUMBER, 5, unsigned long)
#define	SMARTPA_SPK_SWITCH_CALIBRATION		_IOWR(TAS2557_MAGIC_NUMBER, 6, unsigned long)
#define	SMARTPA_SPK_SET_SAMPLERATE			_IOWR(TAS2557_MAGIC_NUMBER, 7, unsigned long)
#define	SMARTPA_SPK_SET_BITRATE				_IOWR(TAS2557_MAGIC_NUMBER, 8, unsigned long)

enum tas2557_configuration {
	TAS2557_CONFIG_MUSIC = 0,
	TAS2557_CONFIG_RINGTONE,
	TAS2557_CONFIG_RINGTONE_HS_SPK,
	TAS2557_CONFIG_LOWPOWER,
	TAS2557_CONFIG_MMI_SPK,
	TAS2557_CONFIG_LOW_TEMP,
	TAS2557_CONFIG_CALIBRATION_CONFIG,
	TAS2557_CONFIG_INCALL_WB = 10,
	TAS2557_CONFIG_VOIP,
	TAS2557_CONFIG_SMARTPA_SENCE_MAX,
};

enum low_temreture_enum {
	LOW_TEMP_STATE_DEFAULT = 0,
	LOW_TEMP_STATE_IN_STAGE1,
	LOW_TEMP_STATE_IN_STAGE2,
	LOW_TEMP_STATE_OUT,
};

#define LOW_TEMP_STATE_IN_TEMP -7
#define LOW_TEMP_STATE_OUT_TEMP -5
#define LOW_TEMP_STATE_STATE1_VOLTAGE 3800000
#define LOW_TEMP_STATE_STATE2_VOLTAGE 3750000

int tas2557_register_misc(struct tas2557_priv *pTAS2557);
int tas2557_deregister_misc(struct tas2557_priv *pTAS2557);

#endif /* _TAS2557_MISC_H */
