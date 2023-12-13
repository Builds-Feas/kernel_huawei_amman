/*
 * drivers/display/hisi/backlight/lp8556.c
 *
 * lp8556 driver reffer to lcd
 *
 *
 * This package is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#include <libfdt.h>
#include <platform/mt_i2c.h>
#include <platform/mt_gpio.h>
#include "lm3697.h"
#include "lcd_kit_common.h"
#include "lcd_kit_bl.h"


extern void *g_fdt;

static struct lm3697_backlight_information lm3697_bl_info = {0};
static bool lm3697_init_status = false;
static bool lm3697_checked = false;

static char *lm3697_dts_string[LM3697_RW_REG_MAX] = {
	"lm3697_reg_sink_output_config",
	"lm3697_reg_ramp_on_off_l",
	"lm3697_reg_ramp_on_off_r",
	"lm3697_reg_ramp_time",
	"lm3697_reg_ramp_time_config",
	"lm3697_reg_brightness_config",
	"lm3697_reg_full_scale_current_setting_a",
	"lm3697_reg_full_scale_current_setting_b",
	"lm3697_reg_current_sink_feedback_enable",
	"lm3697_reg_boost_control",
	"lm3697_reg_auto_frequency_threshold",
	"lm3697_reg_pwm_config",
	"lm3697_reg_brightness_lsb_a",
	"lm3697_reg_brightness_msb_a",
	"lm3697_reg_brightness_lsb_b",
	"lm3697_reg_brightness_msb_b",
	"lm3697_reg_bank_enable",
	"lm3697_reg_open_faults",
	"lm3697_reg_short_faults",
	"lm3697_reg_fault_enable",
};

static unsigned char lm3697_reg_addr[LM3697_RW_REG_MAX] = {
	LM3697_REG_SINK_OUTPUT_CONFIG,
	LM3697_REG_RAMP_ON_OFF_L,
	LM3697_REG_RAMP_ON_OFF_R,
	LM3697_REG_RAMP_TIME,
	LM3697_REG_RAMP_TIME_CONFIG,
	LM3697_REG_BRIGHTNESS_CONFIG,
	LM3697_REG_FULL_SCALE_CURRENT_SETTING_A,
	LM3697_REG_FULL_SCALE_CURRENT_SETTING_B,
	LM3697_REG_CURRENT_SINK_FEEDBACK_ENABLE,
	LM3697_REG_BOOST_CONTROL,
	LM3697_REG_AUTO_FREQUENCY_THRESHOLD,
	LM3697_REG_PWM_CONFIG,
	LM3697_REG_BRIGHTNESS_LSB_A,
	LM3697_REG_BRIGHTNESS_MSB_A,
	LM3697_REG_BRIGHTNESS_LSB_B,
	LM3697_REG_BRIGHTNESS_MSB_B,
	LM3697_REG_BANK_ENABLE,
	LM3697_REG_OPEN_FAULTS,
	LM3697_REG_SHORT_FAULTS,
	LM3697_REG_FAULT_ENABLE,
};

static int lm3697_i2c_read_u8(unsigned char addr, unsigned char *dataBuffer)
{
	int ret = 0;
	unsigned char len = 0;
	struct mt_i2c_t lm3697_i2c = {0};
	*dataBuffer = addr;

	lm3697_i2c.id = lm3697_bl_info.lm3697_i2c_bus_id;
	lm3697_i2c.addr = LM3697_SLAV_ADDR;
	lm3697_i2c.mode = ST_MODE;
	lm3697_i2c.speed = 100;
	len = 1;

	ret = i2c_write_read(&lm3697_i2c, dataBuffer, len, len);
	if (0 != ret)
	{
		LCD_KIT_ERR("%s: i2c_read  failed! reg is 0x%x ret: %d\n", __func__, addr, ret);
	}
	return ret;
}

static int lm3697_i2c_write_u8(unsigned char addr, unsigned char value)
{
	int ret = 0;
	unsigned char write_data[2] = {0};
	unsigned char len = 0;
	struct mt_i2c_t lm3697_i2c = {0};

	write_data[0] = addr;
	write_data[1] = value;

	lm3697_i2c.id = lm3697_bl_info.lm3697_i2c_bus_id;
	lm3697_i2c.addr = LM3697_SLAV_ADDR;
	lm3697_i2c.mode = ST_MODE;
	lm3697_i2c.speed = 100;
	len = 2;

	ret = i2c_write(&lm3697_i2c, write_data, len);
	if (0 != ret)
	{
		LCD_KIT_ERR("%s: i2c_write  failed! reg is  0x%x ret: %d\n", __func__, addr, ret);
	}
	return ret;
}

static int lm3697_parse_dts(void)
{
	int ret = 0;
	int i = 0;

	LCD_KIT_INFO("lm3697_parse_dts +!\n");

	for (i = 0;i < LM3697_RW_REG_MAX; i++ ) {
		ret = lcd_kit_parse_get_u32_default(DTS_COMP_LM3697, lm3697_dts_string[i], &lm3697_bl_info.lm3697_reg[i], 0);
		if (ret < 0) {
			lm3697_bl_info.lm3697_reg[i] = 0xffff;
			LCD_KIT_INFO("can not find %s dts\n", lm3697_dts_string[i]);
		} else {
			LCD_KIT_INFO("get %s value = 0x%x\n", lm3697_dts_string[i],lm3697_bl_info.lm3697_reg[i]);
		}
	}

	return ret;
}

static int lm3697_config_register(void)
{
	int ret = 0;
	int i = 0;
	for(i = 0;i < LM3697_RW_REG_MAX;i++) {
		if (lm3697_bl_info.lm3697_reg[i] != 0xffff) {
			ret = lm3697_i2c_write_u8(lm3697_reg_addr[i], (u8)lm3697_bl_info.lm3697_reg[i]);
			if (ret < 0) {
				LCD_KIT_ERR("write lm3697 backlight config register 0x%x failed\n",lm3697_reg_addr[i]);
				goto exit;
			}
		}
	}
exit:
	return ret;
}

static void lm3697_enable(void)
{
	int ret = 0;

	if(lm3697_bl_info.lm3697_hw_en)
	{
		mt_set_gpio_mode(lm3697_bl_info.lm3697_hw_en_gpio, GPIO_MODE_00);
		mt_set_gpio_dir(lm3697_bl_info.lm3697_hw_en_gpio, GPIO_DIR_OUT);
		mt_set_gpio_out(lm3697_bl_info.lm3697_hw_en_gpio, GPIO_OUT_ONE);
		if(lm3697_bl_info.bl_on_lk_mdelay)
		{
			mdelay(lm3697_bl_info.bl_on_lk_mdelay);
		}
	}
	ret = lm3697_config_register();
	if (ret < 0) {
		LCD_KIT_ERR("lm3697 config register failed\n");
		return;
	}
	lm3697_init_status = true;
}

static void lm3697_disable(void)
{
	if(lm3697_bl_info.lm3697_hw_en)
	{
	    mt_set_gpio_out(lm3697_bl_info.lm3697_hw_en_gpio, GPIO_OUT_ZERO);
	}
	lm3697_init_status = false;
}

static int lm3697_set_backlight(uint32_t bl_level)
{
	static int last_bl_level = 0;
	int bl_msb = 0;
	int bl_lsb = 0;
	int ret = 0;

	/*first set backlight, enable lm3697*/
	if (false == lm3697_init_status && bl_level > 0) {
		lm3697_enable();
	}

	/*set backlight level*/
	ret = lm3697_i2c_write_u8((unsigned char)(lm3697_bl_info.lm3697_level_lsb_reg), LM3697_REG_BRIGHTNESS_LSB_B_BRIGHTNESS[bl_level]);
	if (ret < 0) {
		LCD_KIT_ERR("write lm3697 backlight level lsb:0x%x failed\n", bl_lsb);
	}
	ret = lm3697_i2c_write_u8((unsigned char)(lm3697_bl_info.lm3697_level_msb_reg), LM3697_REG_BRIGHTNESS_MSB_B_BRIGHTNESS[bl_level]);
	if (ret < 0) {
		LCD_KIT_ERR("write lm3697 backlight level msb:0x%x failed\n", bl_msb);
	}

	/*if set backlight level 0, disable lm3697*/
	if (true == lm3697_init_status && 0 == bl_level) {
		lm3697_disable();
	}

	return ret;
}

static void lm3697_set_backlight_status (char *compname, char *status)
{
	int ret = 0;
	int offset = 0;

	if (!compname) {
		LCD_KIT_ERR("type is NULL!\n");
		return;
	}

	offset = fdt_node_offset_by_compatible(g_fdt, 0, compname);
	if (offset < 0) {
		LCD_KIT_ERR("Could not find panel node, change fb dts failed\n");
		return;
	}

	ret = fdt_setprop_string(g_fdt, offset, (const char*)"status", (const void*)status);
	if (ret) {
		LCD_KIT_ERR("Cannot update lcd panel type(errno=%d)!\n", ret);
		return;
	}

	LCD_KIT_INFO("lm3697_set_backlight_status OK!\n");
	return;
}

static struct lcd_kit_bl_ops bl_ops = {
	.set_backlight = lm3697_set_backlight,
};

static int lm3697_device_verify(void)
{
	int ret = 0;
	unsigned char vendor_id = 0;
	if(lm3697_bl_info.lm3697_hw_en)
	{
		mt_set_gpio_mode(lm3697_bl_info.lm3697_hw_en_gpio, GPIO_MODE_00);
		mt_set_gpio_dir(lm3697_bl_info.lm3697_hw_en_gpio, GPIO_DIR_OUT);
		mt_set_gpio_out(lm3697_bl_info.lm3697_hw_en_gpio, GPIO_OUT_ONE);
		if(lm3697_bl_info.bl_on_lk_mdelay)
		{
			mdelay(lm3697_bl_info.bl_on_lk_mdelay);
		}
	}

	ret = lm3697_i2c_read_u8(LM3697_REG_DEV_ID, &vendor_id);
	if (ret < 0) {
		LCD_KIT_INFO("no lm3697 device, read vendor id failed\n");
		goto error_exit;
	}
	if(vendor_id != LM3697_VENDOR_ID)
	{
		LCD_KIT_INFO("no lm3697 device, vendor id is not right\n");
		goto error_exit;
	}
	if(lm3697_bl_info.lm3697_hw_en)
	{
		mt_set_gpio_out(lm3697_bl_info.lm3697_hw_en_gpio, GPIO_OUT_ZERO);
	}

	return 0;
error_exit:
	if(lm3697_bl_info.lm3697_hw_en)
	{
		mt_set_gpio_out(lm3697_bl_info.lm3697_hw_en_gpio, GPIO_OUT_ZERO);
	}
	return -1;
}


int lm3697_backlight_ic_recognize(void)
{
	int ret = 0;
	if (lm3697_checked) {
		LCD_KIT_INFO("lm3697 already check ,not again setting\n");
		return ret;
	}
	ret = lm3697_device_verify();
	if (ret < 0) {
		lm3697_set_backlight_status(DTS_COMP_LM3697,"disabled");
		LCD_KIT_ERR("lm3697 is not right backlight ics\n");
	}
	else{
		lm3697_parse_dts();
		lcd_kit_bl_register(&bl_ops);
		lm3697_set_backlight_status(DTS_COMP_LM3697,"okay");
		LCD_KIT_INFO("lm3697 is right backlight ic\n");
	}
	lm3697_checked = true;
	return ret;
}

int lm3697_init(void)
{
	int ret = 0;

	ret = lcd_kit_parse_get_u32_default(DTS_COMP_LM3697, LM3697_SUPPORT, &lm3697_bl_info.lm3697_support, 0);
	if (ret < 0 || !lm3697_bl_info.lm3697_support) {
		LCD_KIT_ERR("not support lm3697!\n");
		return 0;
	}
	lm3697_set_backlight_status(DTS_COMP_LM3697,"disabled");
	/*register bl ops*/
	lcd_kit_backlight_recognize_register(lm3697_backlight_ic_recognize);
	ret = lcd_kit_parse_get_u32_default(DTS_COMP_LM3697, LM3697_I2C_BUS_ID, &lm3697_bl_info.lm3697_i2c_bus_id, 0);
	if (ret < 0) {
		lm3697_bl_info.lm3697_i2c_bus_id = 0;
		return 0;
	}
	ret = lcd_kit_parse_get_u32_default(DTS_COMP_LM3697, LM3697_HW_ENABLE, &lm3697_bl_info.lm3697_hw_en, 0);
	if (ret < 0) {
		LCD_KIT_ERR("parse dts lm3697_hw_enable fail!\n");
		lm3697_bl_info.lm3697_hw_en = 0;
		return 0;
	}
	if(lm3697_bl_info.lm3697_hw_en)
	{
		ret = lcd_kit_parse_get_u32_default(DTS_COMP_LM3697, LM3697_HW_EN_GPIO, &lm3697_bl_info.lm3697_hw_en_gpio, 0);
		if (ret < 0) {
			LCD_KIT_ERR("parse dts lm3697_hw_en_gpio fail!\n");
			lm3697_bl_info.lm3697_hw_en_gpio = 0;
			return 0;
		}
		ret = lcd_kit_parse_get_u32_default(DTS_COMP_LM3697, LM3697_HW_EN_DELAY, &lm3697_bl_info.bl_on_lk_mdelay, 0);
		if (ret < 0) {
			LCD_KIT_ERR("parse dts bl_on_lk_mdelay fail!\n");
			lm3697_bl_info.bl_on_lk_mdelay = 0;
			return 0;
		}
	}

    ret = lcd_kit_parse_get_u32_default(DTS_COMP_LM3697, LM3697_BACKLIGHT_CONFIG_LSB_REG_ADDR, &lm3697_bl_info.lm3697_level_lsb_reg, 0);
    if (ret < 0) {
        LCD_KIT_ERR("parse dts lm3697_backlight_config_lsb_reg_addr fail!\n");
        lm3697_bl_info.lm3697_level_lsb_reg = LM3697_REG_BRIGHTNESS_LSB_B;
    }
    ret = lcd_kit_parse_get_u32_default(DTS_COMP_LM3697, LM3697_BACKLIGHT_CONFIG_MSB_REG_ADDR, &lm3697_bl_info.lm3697_level_msb_reg, 0);
    if (ret < 0) {
        LCD_KIT_ERR("parse dts lm3697_backlight_config_msb_reg_addr fail!\n");
        lm3697_bl_info.lm3697_level_msb_reg = LM3697_REG_BRIGHTNESS_MSB_B;
    }

	LCD_KIT_INFO("[%s]:lm3697 is support!\n", __FUNCTION__);
	return 0;
}
