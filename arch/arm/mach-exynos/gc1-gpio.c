/*
 *  linux/arch/arm/mach-exynos/midas-gpio.c
 *
 * Copyright (c) 2010 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com/
 *
 * EXYNOS - GPIO setting in set board
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/gpio.h>
#include <linux/serial_core.h>
#include <plat/devs.h>
#include <plat/gpio-cfg.h>
#include <plat/regs-serial.h>
#include <mach/gpio-midas.h>
#include <plat/cpu.h>
#include <mach/pmu.h>

struct gpio_init_data {
	uint num;
	uint cfg;
	uint val;
	uint pud;
	uint drv;
};

/*
 * GC1 GPIO Init Table
 */
static struct gpio_init_data m0_init_gpios[] = {

	{EXYNOS4_GPD0(0), S3C_GPIO_OUTPUT, S3C_GPIO_SETPIN_ZERO,
		S3C_GPIO_PULL_NONE, S5P_GPIO_DRVSTR_LV1}, /* VIB */
	{EXYNOS4_GPD0(2), S3C_GPIO_INPUT, S3C_GPIO_SETPIN_NONE,
		S3C_GPIO_PULL_NONE, S5P_GPIO_DRVSTR_LV1},
	{EXYNOS4_GPD0(3), S3C_GPIO_INPUT, S3C_GPIO_SETPIN_NONE,
		S3C_GPIO_PULL_NONE, S5P_GPIO_DRVSTR_LV1},

	{EXYNOS4_GPD1(2), S3C_GPIO_INPUT, S3C_GPIO_SETPIN_NONE,
		S3C_GPIO_PULL_NONE, S5P_GPIO_DRVSTR_LV1}, /* GSENSE_SDA_1.8V */
	{EXYNOS4_GPD1(3), S3C_GPIO_INPUT, S3C_GPIO_SETPIN_NONE,
		S3C_GPIO_PULL_NONE, S5P_GPIO_DRVSTR_LV1}, /* GSENSE_SCL_1.8V */

	{EXYNOS4_GPX0(1), S3C_GPIO_INPUT, S3C_GPIO_SETPIN_NONE,
		S3C_GPIO_PULL_DOWN, S5P_GPIO_DRVSTR_LV1}, /* NC */
	{EXYNOS4_GPX0(2), S3C_GPIO_INPUT, S3C_GPIO_SETPIN_NONE,
		S3C_GPIO_PULL_NONE, S5P_GPIO_DRVSTR_LV1}, /* PS_ALS_INT */
	{EXYNOS4_GPX0(3), S3C_GPIO_INPUT, S3C_GPIO_SETPIN_NONE,
		S3C_GPIO_PULL_NONE, S5P_GPIO_DRVSTR_LV1},
	{EXYNOS4_GPX0(4), S3C_GPIO_INPUT, S3C_GPIO_SETPIN_NONE,
		S3C_GPIO_PULL_NONE, S5P_GPIO_DRVSTR_LV1},
#if defined(CONFIG_MACH_GC1_USA_VZW)
	{EXYNOS4_GPX0(5), S3C_GPIO_INPUT, S3C_GPIO_SETPIN_NONE,
		S3C_GPIO_PULL_NONE, S5P_GPIO_DRVSTR_LV1}, /* NC */
#else
	{EXYNOS4_GPX0(5), S3C_GPIO_INPUT, S3C_GPIO_SETPIN_NONE,
		S3C_GPIO_PULL_DOWN, S5P_GPIO_DRVSTR_LV1}, /* NC */
#endif
	{EXYNOS4_GPX0(6), S3C_GPIO_INPUT, S3C_GPIO_SETPIN_NONE,
		S3C_GPIO_PULL_DOWN, S5P_GPIO_DRVSTR_LV1}, /* NC */
	{EXYNOS4_GPX0(7), S3C_GPIO_SFN(0xF), S3C_GPIO_SETPIN_NONE,
		S3C_GPIO_PULL_NONE, S5P_GPIO_DRVSTR_LV1}, /* AP_PMIC_IRQ */

	{EXYNOS4_GPX1(3), S3C_GPIO_INPUT, S3C_GPIO_SETPIN_NONE,
		S3C_GPIO_PULL_DOWN, S5P_GPIO_DRVSTR_LV1}, /* NC */
	{EXYNOS4_GPX1(4), S3C_GPIO_INPUT, S3C_GPIO_SETPIN_NONE,
		S3C_GPIO_PULL_NONE, S5P_GPIO_DRVSTR_LV1}, /* TELE_KEY_F */

	{EXYNOS4_GPX2(0), S3C_GPIO_INPUT, S3C_GPIO_SETPIN_NONE,
		S3C_GPIO_PULL_NONE, S5P_GPIO_DRVSTR_LV1}, /* KEY_S1 */
	{EXYNOS4_GPX2(1), S3C_GPIO_INPUT, S3C_GPIO_SETPIN_NONE,
		S3C_GPIO_PULL_NONE, S5P_GPIO_DRVSTR_LV1}, /* KEY_S2 */
	{EXYNOS4_GPX2(2), S3C_GPIO_INPUT, S3C_GPIO_SETPIN_NONE,
		S3C_GPIO_PULL_NONE, S5P_GPIO_DRVSTR_LV1}, /* TELE_KEY */
	{EXYNOS4_GPX2(3), S3C_GPIO_INPUT, S3C_GPIO_SETPIN_NONE,
		S3C_GPIO_PULL_NONE, S5P_GPIO_DRVSTR_LV1}, /* FUEL_ALERT */
	{EXYNOS4_GPX2(6), S3C_GPIO_INPUT, S3C_GPIO_SETPIN_NONE,
		S3C_GPIO_PULL_NONE, S5P_GPIO_DRVSTR_LV1}, /* BT_HOST_WAKEUP */

	{EXYNOS4_GPX3(1), S3C_GPIO_INPUT, S3C_GPIO_SETPIN_NONE,
		S3C_GPIO_PULL_NONE, S5P_GPIO_DRVSTR_LV1}, /* BT_WAKE */
	{EXYNOS4_GPX3(3), S3C_GPIO_INPUT, S3C_GPIO_SETPIN_NONE,
		S3C_GPIO_PULL_NONE, S5P_GPIO_DRVSTR_LV1}, /* WIDE_KEY */
	{EXYNOS4_GPX3(4), S3C_GPIO_INPUT, S3C_GPIO_SETPIN_NONE,
		S3C_GPIO_PULL_NONE, S5P_GPIO_DRVSTR_LV1}, /* T_FLASH_DETECT */

	{EXYNOS4_GPK3(1), S3C_GPIO_INPUT, S3C_GPIO_SETPIN_NONE,
		S3C_GPIO_PULL_NONE, S5P_GPIO_DRVSTR_LV1}, /* WLAN_SDIO_CMD */
	{EXYNOS4_GPK3(3), S3C_GPIO_INPUT, S3C_GPIO_SETPIN_NONE,
		S3C_GPIO_PULL_NONE, S5P_GPIO_DRVSTR_LV1}, /* WLAN_SDIO_D(0) */
	{EXYNOS4_GPK3(4), S3C_GPIO_INPUT, S3C_GPIO_SETPIN_NONE,
		S3C_GPIO_PULL_NONE, S5P_GPIO_DRVSTR_LV1}, /* WLAN_SDIO_D(1) */
	{EXYNOS4_GPK3(5), S3C_GPIO_INPUT, S3C_GPIO_SETPIN_NONE,
		S3C_GPIO_PULL_NONE, S5P_GPIO_DRVSTR_LV1}, /* WLAN_SDIO_D(2) */
	{EXYNOS4_GPK3(6), S3C_GPIO_INPUT, S3C_GPIO_SETPIN_NONE,
		S3C_GPIO_PULL_NONE, S5P_GPIO_DRVSTR_LV1}, /* WLAN_SDIO_D(3) */

	{EXYNOS4_GPY0(0), S3C_GPIO_INPUT, S3C_GPIO_SETPIN_NONE,
		S3C_GPIO_PULL_DOWN, S5P_GPIO_DRVSTR_LV1}, /* NC */
	{EXYNOS4_GPY0(1), S3C_GPIO_INPUT, S3C_GPIO_SETPIN_NONE,
		S3C_GPIO_PULL_DOWN, S5P_GPIO_DRVSTR_LV1}, /* NC */
	{EXYNOS4_GPY0(2), S3C_GPIO_INPUT, S3C_GPIO_SETPIN_NONE,
		S3C_GPIO_PULL_DOWN, S5P_GPIO_DRVSTR_LV1}, /* NC */
	{EXYNOS4_GPY0(3), S3C_GPIO_INPUT, S3C_GPIO_SETPIN_NONE,
		S3C_GPIO_PULL_DOWN, S5P_GPIO_DRVSTR_LV1}, /* NC */
	{EXYNOS4_GPY0(4), S3C_GPIO_INPUT, S3C_GPIO_SETPIN_NONE,
		S3C_GPIO_PULL_DOWN, S5P_GPIO_DRVSTR_LV1}, /* NC */
	{EXYNOS4_GPY0(5), S3C_GPIO_INPUT, S3C_GPIO_SETPIN_NONE,
		S3C_GPIO_PULL_DOWN, S5P_GPIO_DRVSTR_LV1}, /* NC */

	{EXYNOS4_GPY1(0), S3C_GPIO_INPUT, S3C_GPIO_SETPIN_NONE,
		S3C_GPIO_PULL_DOWN, S5P_GPIO_DRVSTR_LV1}, /* NC */
	{EXYNOS4_GPY1(1), S3C_GPIO_INPUT, S3C_GPIO_SETPIN_NONE,
		S3C_GPIO_PULL_DOWN, S5P_GPIO_DRVSTR_LV1}, /* NC */
	{EXYNOS4_GPY1(2), S3C_GPIO_INPUT, S3C_GPIO_SETPIN_NONE,
		S3C_GPIO_PULL_DOWN, S5P_GPIO_DRVSTR_LV1}, /* NC */
	{EXYNOS4_GPY1(3), S3C_GPIO_INPUT, S3C_GPIO_SETPIN_NONE,
		S3C_GPIO_PULL_DOWN, S5P_GPIO_DRVSTR_LV1}, /* NC */

	{EXYNOS4_GPY2(1), S3C_GPIO_INPUT, S3C_GPIO_SETPIN_NONE,
		S3C_GPIO_PULL_DOWN, S5P_GPIO_DRVSTR_LV1}, /* NC */
	{EXYNOS4_GPY2(2), S3C_GPIO_INPUT, S3C_GPIO_SETPIN_NONE,
		S3C_GPIO_PULL_DOWN, S5P_GPIO_DRVSTR_LV1}, /* NC */
	{EXYNOS4_GPY2(3), S3C_GPIO_INPUT, S3C_GPIO_SETPIN_NONE,
		S3C_GPIO_PULL_DOWN, S5P_GPIO_DRVSTR_LV1}, /* NC */

	{EXYNOS4212_GPJ0(0), S3C_GPIO_INPUT, S3C_GPIO_SETPIN_ZERO,
		S3C_GPIO_PULL_NONE, S5P_GPIO_DRVSTR_LV4}, /* WLAN_EN */

	{EXYNOS4212_GPJ1(3), S3C_GPIO_INPUT, S3C_GPIO_SETPIN_NONE,
		S3C_GPIO_PULL_DOWN, S5P_GPIO_DRVSTR_LV3}, /* CAM_MCLK */

	{EXYNOS4212_GPM2(2), S3C_GPIO_INPUT, S3C_GPIO_SETPIN_NONE,
		S3C_GPIO_PULL_DOWN, S5P_GPIO_DRVSTR_LV3}, /* VTCAM_MCLK */
};

/*
 * GC1 GPIO Sleep Table
 */
static unsigned int m0_sleep_gpio_table[][3] = {
	{EXYNOS4_GPA0(0),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_NONE},
	{EXYNOS4_GPA0(1),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN},
	{EXYNOS4_GPA0(2),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_NONE},
	{EXYNOS4_GPA0(3),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_UP},
	{EXYNOS4_GPA0(4),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_NONE},
	{EXYNOS4_GPA0(5),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN},
	{EXYNOS4_GPA0(6),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN},
	{EXYNOS4_GPA0(7),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_UP},

	{EXYNOS4_GPA1(0),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN},
	{EXYNOS4_GPA1(1),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN},
	{EXYNOS4_GPA1(2),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN},
	{EXYNOS4_GPA1(3),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN},
#if defined(CONFIG_SEC_MODEM)
	{EXYNOS4_GPA1(4),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC(IPC_RXD) */
	{EXYNOS4_GPA1(5),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC(IPC_TXD) */
#else
	{EXYNOS4_GPA1(4),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* AP_FLM_RXD */
	/*
	 * UART3-TXD : It should be pulled up during sleep, if this uart is
	 * used for PC connection like a factory command program.
	 * Otherwise, a PC might get null characters like noise.
	 * In addition, LPA mode is also applied to this comment, because
	 * LPA mode invokes this GPIO sleep configuration.
	 */
	{EXYNOS4_GPA1(5),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_UP}, /* AP_FLM_TXD */
#endif

	{EXYNOS4_GPB(0),   S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_NONE},
	{EXYNOS4_GPB(1),   S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_NONE},
	{EXYNOS4_GPB(2),   S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_NONE},
	{EXYNOS4_GPB(3),   S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_NONE},
	{EXYNOS4_GPB(4),   S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN},
	{EXYNOS4_GPB(5),   S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_UP},
	{EXYNOS4_GPB(6),   S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_NONE},
	{EXYNOS4_GPB(7),   S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN},

	{EXYNOS4_GPC0(0),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4_GPC0(1),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN},
	{EXYNOS4_GPC0(2),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4_GPC0(3),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4_GPC0(4),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */

	{EXYNOS4_GPC1(0),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4_GPC1(1),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4_GPC1(2),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4_GPC1(3),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4_GPC1(4),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */

	{EXYNOS4_GPD0(0),  S3C_GPIO_SLP_OUT0,  S3C_GPIO_PULL_NONE}, /* VIB */
	{EXYNOS4_GPD0(1),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4_GPD0(2),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_NONE},
	{EXYNOS4_GPD0(3),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_NONE},

	{EXYNOS4_GPD1(0),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN},
	{EXYNOS4_GPD1(1),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN},
	{EXYNOS4_GPD1(2),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_NONE},
	{EXYNOS4_GPD1(3),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_NONE},

	{EXYNOS4_GPF0(0),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4_GPF0(1),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4_GPF0(2),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4_GPF0(3),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4_GPF0(4),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4_GPF0(5),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4_GPF0(6),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4_GPF0(7),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */

	{EXYNOS4_GPF1(0),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN},
	{EXYNOS4_GPF1(1),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4_GPF1(2),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4_GPF1(3),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN},
	{EXYNOS4_GPF1(4),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_NONE},
	{EXYNOS4_GPF1(5),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_NONE},
#ifdef CONFIG_SEC_MODEM_M0
	/* GPF1(6) M0, C1 PDA_ACTIVE, let cp know AP sleep status*/
	{EXYNOS4_GPF1(6),  S3C_GPIO_SLP_OUT0, S3C_GPIO_PULL_NONE},
#elif defined(CONFIG_MACH_GC1_USA_VZW)
	{EXYNOS4_GPF1(6),  S3C_GPIO_SLP_PREV, S3C_GPIO_PULL_UP}, /* NC */
#else
	{EXYNOS4_GPF1(6),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
#endif
	{EXYNOS4_GPF1(7),  S3C_GPIO_SLP_PREV, S3C_GPIO_PULL_NONE},

	{EXYNOS4_GPF2(0),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4_GPF2(1),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN},
	{EXYNOS4_GPF2(2),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4_GPF2(3),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4_GPF2(4),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4_GPF2(5),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4_GPF2(6),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4_GPF2(7),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */

	{EXYNOS4_GPF3(0),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_NONE},
	{EXYNOS4_GPF3(1),  S3C_GPIO_SLP_PREV, S3C_GPIO_PULL_NONE},
	{EXYNOS4_GPF3(2),  S3C_GPIO_SLP_PREV, S3C_GPIO_PULL_NONE},
	{EXYNOS4_GPF3(3),  S3C_GPIO_SLP_PREV, S3C_GPIO_PULL_NONE},
	{EXYNOS4_GPF3(4),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4_GPF3(5),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */

	{EXYNOS4_GPK0(0),  S3C_GPIO_SLP_PREV, S3C_GPIO_PULL_NONE},
	{EXYNOS4_GPK0(1),  S3C_GPIO_SLP_PREV, S3C_GPIO_PULL_NONE},
	{EXYNOS4_GPK0(2),  S3C_GPIO_SLP_PREV, S3C_GPIO_PULL_NONE},
	{EXYNOS4_GPK0(3),  S3C_GPIO_SLP_PREV, S3C_GPIO_PULL_NONE},
	{EXYNOS4_GPK0(4),  S3C_GPIO_SLP_PREV, S3C_GPIO_PULL_NONE},
	{EXYNOS4_GPK0(5),  S3C_GPIO_SLP_PREV, S3C_GPIO_PULL_NONE},
	{EXYNOS4_GPK0(6),  S3C_GPIO_SLP_PREV, S3C_GPIO_PULL_NONE},

	{EXYNOS4_GPK1(0),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4_GPK1(1),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4_GPK1(2),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4_GPK1(3),  S3C_GPIO_SLP_PREV, S3C_GPIO_PULL_NONE},
	{EXYNOS4_GPK1(4),  S3C_GPIO_SLP_PREV, S3C_GPIO_PULL_NONE},
	{EXYNOS4_GPK1(5),  S3C_GPIO_SLP_PREV, S3C_GPIO_PULL_NONE},
	{EXYNOS4_GPK1(6),  S3C_GPIO_SLP_PREV, S3C_GPIO_PULL_NONE},

	{EXYNOS4_GPK2(0),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN},
	{EXYNOS4_GPK2(1),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN},
	{EXYNOS4_GPK2(2),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4_GPK2(3),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN},
	{EXYNOS4_GPK2(4),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN},
	{EXYNOS4_GPK2(5),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN},
	{EXYNOS4_GPK2(6),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN},

	{EXYNOS4_GPK3(0),  S3C_GPIO_SLP_OUT0,  S3C_GPIO_PULL_NONE},
	{EXYNOS4_GPK3(1),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_NONE},
	{EXYNOS4_GPK3(2),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4_GPK3(3),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_NONE},
	{EXYNOS4_GPK3(4),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_NONE},
	{EXYNOS4_GPK3(5),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_NONE},
	{EXYNOS4_GPK3(6),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_NONE},

	{EXYNOS4_GPL0(0),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4_GPL0(1),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4_GPL0(2),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4_GPL0(3),  S3C_GPIO_SLP_PREV,  S3C_GPIO_PULL_NONE},
	{EXYNOS4_GPL0(4),  S3C_GPIO_SLP_OUT0, S3C_GPIO_PULL_NONE},
/*	{EXYNOS4_GPL0(5),  S3C_GPIO_SLP_OUT0,  S3C_GPIO_PULL_NONE}, */
	{EXYNOS4_GPL0(6),  S3C_GPIO_SLP_PREV,  S3C_GPIO_PULL_NONE},
/*	{EXYNOS4_GPL0(7),  S3C_GPIO_SLP_OUT0,  S3C_GPIO_PULL_NONE}, */

	{EXYNOS4_GPL1(0),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4_GPL1(1),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN},
/*	{EXYNOS4_GPL1(2),  S3C_GPIO_SLP_PREV,  S3C_GPIO_PULL_NONE}, */

	{EXYNOS4_GPL2(0),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4_GPL2(1),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4_GPL2(2),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN},
	{EXYNOS4_GPL2(3),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4_GPL2(4),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN},
	{EXYNOS4_GPL2(5),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4_GPL2(6),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4_GPL2(7),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */

	{EXYNOS4_GPY0(0),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4_GPY0(1),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4_GPY0(2),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4_GPY0(3),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4_GPY0(4),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4_GPY0(5),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */

	{EXYNOS4_GPY1(0),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4_GPY1(1),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4_GPY1(2),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4_GPY1(3),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */

	{EXYNOS4_GPY2(0),  S3C_GPIO_SLP_PREV, S3C_GPIO_PULL_NONE},
	{EXYNOS4_GPY2(1),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4_GPY2(2),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
#if defined CONFIG_MACH_GC1_USA_VZW
	{EXYNOS4_GPY2(3),  S3C_GPIO_SLP_PREV, S3C_GPIO_PULL_DOWN}, /* NC */
#else
	{EXYNOS4_GPY2(3),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
#endif
	{EXYNOS4_GPY2(4),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_NONE},
	{EXYNOS4_GPY2(5),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_NONE},

	{EXYNOS4_GPY3(0),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4_GPY3(1),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4_GPY3(2),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4_GPY3(3),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4_GPY3(4),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4_GPY3(5),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4_GPY3(6),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4_GPY3(7),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */

	{EXYNOS4_GPY4(0),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4_GPY4(1),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4_GPY4(2),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4_GPY4(3),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4_GPY4(4),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4_GPY4(5),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4_GPY4(6),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4_GPY4(7),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */

	{EXYNOS4_GPY5(0),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4_GPY5(1),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4_GPY5(2),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4_GPY5(3),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4_GPY5(4),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4_GPY5(5),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4_GPY5(6),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4_GPY5(7),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */

	{EXYNOS4_GPY6(0),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4_GPY6(1),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4_GPY6(2),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4_GPY6(3),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4_GPY6(4),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4_GPY6(5),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4_GPY6(6),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4_GPY6(7),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */

	{EXYNOS4_GPZ(0),   S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN},
	{EXYNOS4_GPZ(1),   S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4_GPZ(2),   S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN},
	{EXYNOS4_GPZ(3),   S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN},
	{EXYNOS4_GPZ(4),   S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN},
	{EXYNOS4_GPZ(5),   S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4_GPZ(6),   S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */

	/* Exynos4212 specific gpio */
	{EXYNOS4212_GPJ0(0),  S3C_GPIO_SLP_PREV,  S3C_GPIO_PULL_NONE},
	{EXYNOS4212_GPJ0(1),  S3C_GPIO_SLP_PREV, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4212_GPJ0(2),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4212_GPJ0(3),  S3C_GPIO_SLP_PREV, S3C_GPIO_PULL_NONE},
	/* EAR_MICBIAS_EN */

	{EXYNOS4212_GPJ0(4),  S3C_GPIO_SLP_PREV,  S3C_GPIO_PULL_NONE},
	{EXYNOS4212_GPJ0(5),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4212_GPJ0(6),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4212_GPJ0(7),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN},

	{EXYNOS4212_GPJ1(0),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4212_GPJ1(1),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4212_GPJ1(2),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4212_GPJ1(3),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN},
	{EXYNOS4212_GPJ1(4),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */

	{EXYNOS4212_GPM0(0),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4212_GPM0(1),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4212_GPM0(2),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4212_GPM0(3),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN},
	{EXYNOS4212_GPM0(4),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4212_GPM0(5),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4212_GPM0(6),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4212_GPM0(7),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */

	{EXYNOS4212_GPM1(0),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4212_GPM1(1),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4212_GPM1(2),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_NONE}, /*HWREV*/
	{EXYNOS4212_GPM1(3),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_NONE}, /*HWREV*/
	{EXYNOS4212_GPM1(4),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_NONE}, /*HWREV*/
	{EXYNOS4212_GPM1(5),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_NONE}, /*HWREV*/
	{EXYNOS4212_GPM1(6),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */

	{EXYNOS4212_GPM2(0),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_NONE},
	{EXYNOS4212_GPM2(1),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_NONE},
	{EXYNOS4212_GPM2(2),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4212_GPM2(3),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN},
#if defined CONFIG_MACH_GC1_USA_VZW
	{EXYNOS4212_GPM2(4),  S3C_GPIO_SLP_PREV, S3C_GPIO_PULL_DOWN}, /* NC */
#else
	{EXYNOS4212_GPM2(4),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
#endif
	{EXYNOS4212_GPM3(0),  S3C_GPIO_SLP_PREV, S3C_GPIO_PULL_NONE},
	{EXYNOS4212_GPM3(1),  S3C_GPIO_SLP_PREV, S3C_GPIO_PULL_NONE},
	{EXYNOS4212_GPM3(2),  S3C_GPIO_SLP_PREV, S3C_GPIO_PULL_NONE},
#ifdef CONFIG_SEC_MODEM_M0
	/* GPM3(3) M0, CP_RESET_REQ hold high */
	{EXYNOS4212_GPM3(3),  S3C_GPIO_SLP_OUT1, S3C_GPIO_PULL_DOWN}, /* NC */
#elif defined(CONFIG_MACH_GC1_USA_VZW)
	{EXYNOS4212_GPM3(3),  S3C_GPIO_SLP_PREV, S3C_GPIO_PULL_DOWN}, /* NC */
#else
	{EXYNOS4212_GPM3(3),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
#endif
	{EXYNOS4212_GPM3(4),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4212_GPM3(5),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4212_GPM3(6),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4212_GPM3(7),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */

	{EXYNOS4212_GPM4(0),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4212_GPM4(1),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4212_GPM4(2),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4212_GPM4(3),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4212_GPM4(4),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4212_GPM4(5),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4212_GPM4(6),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4212_GPM4(7),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */

	{EXYNOS4212_GPV0(0),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4212_GPV0(1),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4212_GPV0(2),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4212_GPV0(3),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4212_GPV0(4),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4212_GPV0(5),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4212_GPV0(6),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4212_GPV0(7),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */

	{EXYNOS4212_GPV1(0),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4212_GPV1(1),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4212_GPV1(2),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4212_GPV1(3),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4212_GPV1(4),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4212_GPV1(5),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4212_GPV1(6),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4212_GPV1(7),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */

	{EXYNOS4212_GPV2(0),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4212_GPV2(1),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4212_GPV2(2),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4212_GPV2(3),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4212_GPV2(4),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4212_GPV2(5),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4212_GPV2(6),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4212_GPV2(7),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */

	{EXYNOS4212_GPV3(0),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4212_GPV3(1),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4212_GPV3(2),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4212_GPV3(3),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4212_GPV3(4),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4212_GPV3(5),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4212_GPV3(6),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4212_GPV3(7),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */

	{EXYNOS4212_GPV4(0),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4212_GPV4(1),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
}; /* GC1_sleep_gpio_table */

/*
 * GC1 Rev0.1 (HW EMUL REV0.4) GPIO Sleep Table
 */
static unsigned int m0_sleep_gpio_table_rev01[][3] = {
	{EXYNOS4_GPF0(3), S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /*GYRO_INT*/
	{EXYNOS4_GPL0(0), S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_NONE}, /*POWER_LED*/
	{EXYNOS4_GPL2(0), S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /*GYRO_DE*/
	{EXYNOS4_GPL2(4),  S3C_GPIO_SLP_OUT1, S3C_GPIO_PULL_NONE}, /*TOP_PCB_PWREN*/
	{EXYNOS4212_GPM0(5), S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_NONE}, /*MOT_EN*/
	{EXYNOS4212_GPM0(6), S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /*SAMBAZ*/
};

/*
 * GC1 Rev0.2 (HW MAIN REV0.0) GPIO Sleep Table
 */
static unsigned int m0_sleep_gpio_table_rev02[][3] = {
	{EXYNOS4_GPB(5),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN},
	{EXYNOS4_GPF0(3), S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /*NC*/
	{EXYNOS4_GPL0(0), S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /*NC*/
	{EXYNOS4_GPL0(3), S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /*NC*/
	{EXYNOS4_GPL2(0), S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /*NC*/
	{EXYNOS4_GPL2(4), S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /*NC*/
};

struct m0_sleep_table {
	unsigned int (*ptr)[3];
	int size;
};

#define GPIO_TABLE(_ptr) \
	{.ptr = _ptr, \
	.size = ARRAY_SIZE(_ptr)} \

#define GPIO_TABLE_NULL \
	{.ptr = NULL, \
	.size = 0} \

/* in order to distinguish SLEEP GPIO of HW version */
static struct m0_sleep_table m0_sleep_table[] = {
	GPIO_TABLE(m0_sleep_gpio_table),	/* HWID(0x0) - GC1 HWREV0.3 */
	GPIO_TABLE(m0_sleep_gpio_table_rev01),	/* HWID(0x1) - GC1 HWREV0.4 */
	GPIO_TABLE(m0_sleep_gpio_table_rev02),	/* HWID(0x2) - GC1 MAIN 0.0 */
};

static void config_sleep_gpio_table(int array_size,
				    unsigned int (*gpio_table)[3])
{
	u32 i, gpio;

	for (i = 0; i < array_size; i++) {
		gpio = gpio_table[i][0];
		s3c_gpio_slp_cfgpin(gpio, gpio_table[i][1]);
		s3c_gpio_slp_setpull_updown(gpio, gpio_table[i][2]);
	}
}

void m0_config_sleep_gpio_table(void)
{
	int i;
	int index = min(ARRAY_SIZE(m0_sleep_table), system_rev + 1);

	for (i = 0; i < index; i++) {
		if (m0_sleep_table[i].ptr == NULL)
			continue;

		config_sleep_gpio_table(m0_sleep_table[i].size,
				m0_sleep_table[i].ptr);
	}
}

/* To save power consumption, gpio pin set before enterling sleep */
void midas_config_sleep_gpio_table(void)
{
	m0_config_sleep_gpio_table();
}

/* Intialize gpio set in midas board */
void midas_config_gpio_table(void)
{
	u32 i, gpio;

	printk(KERN_DEBUG "%s\n", __func__);

	for (i = 0; i < ARRAY_SIZE(m0_init_gpios); i++) {
		gpio = m0_init_gpios[i].num;
		if (gpio <= EXYNOS4212_GPV4(1)) {
			s3c_gpio_cfgpin(gpio, m0_init_gpios[i].cfg);
			s3c_gpio_setpull(gpio, m0_init_gpios[i].pud);

			if (m0_init_gpios[i].val != S3C_GPIO_SETPIN_NONE)
				gpio_set_value(gpio, m0_init_gpios[i].val);

			s5p_gpio_set_drvstr(gpio, m0_init_gpios[i].drv);
		}
	}
}
