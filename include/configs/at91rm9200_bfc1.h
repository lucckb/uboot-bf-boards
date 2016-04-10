/*
 * Copyright (C) 2010 Andreas Bießmann <biessmann.devel@googlemail.com>
 *
 * based on previous work by
 *
 * Ulf Samuelsson <ulf@atmel.com>
 * Rick Bronson <rick@efn.org>
 *
 * Configuration settings for the AT91RM9200EK board.
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef __AT91RM9200_BFC1_CONFIG_H__
#define __AT91RM9200_BFC1_CONFIG_H__

#include <linux/sizes.h>

/*
 * set some initial configurations depending on configure target
 *
 * at91rm9200ek_config     -> boot from 0x0 in NOR Flash at CS0
 * at91rm9200ek_ram_config -> continue booting from 0x20100000 in RAM; lowlevel
 *                            initialisation was done by some preloader
 */
#define CONFIG_RAMBOOT
#ifdef CONFIG_RAMBOOT
#define CONFIG_SKIP_LOWLEVEL_INIT
#define CONFIG_SYS_TEXT_BASE 0x21f00000
#else
#define CONFIG_SYS_TEXT_BASE 0x10000000
#endif

/*
 * AT91C_XTAL_CLOCK is the frequency of external xtal in hertz
 * AT91C_MAIN_CLOCK is the frequency of PLLA output
 * AT91C_MASTER_CLOCK is the peripherial clock
 * CONFIG_SYS_HZ_CLOCK is the value for CCR in tc0 (divider 2 is implicitely
 *  set in arch/arm/cpu/arm920t/at91/timer.c)
 * CONFIG_SYS_HZ is the tick rate for timer tc0
 */
#define AT91C_XTAL_CLOCK		18432000
#define CONFIG_SYS_AT91_SLOW_CLOCK	32768
#define AT91C_MAIN_CLOCK		((AT91C_XTAL_CLOCK / 4) * 39)
#define AT91C_MASTER_CLOCK		(AT91C_MAIN_CLOCK / 3 )
#define CONFIG_SYS_HZ_CLOCK		(AT91C_MASTER_CLOCK / 2)

/* CPU configuration */
#define CONFIG_AT91RM9200
#define CONFIG_AT91RM9200_BFC1
#define CONFIG_CPUAT91
#define USE_920T_MMU

#include <asm/hardware.h>	/* needed for port definitions */

#define CONFIG_CMDLINE_TAG
#define CONFIG_SETUP_MEMORY_TAGS
#define CONFIG_INITRD_TAG

#define CONFIG_BOARD_EARLY_INIT_F

/*
 * Memory Configuration
 */
#define CONFIG_NR_DRAM_BANKS		1
#define CONFIG_SYS_SDRAM_BASE		0x20000000
#define CONFIG_SYS_SDRAM_SIZE		SZ_32M

#define CONFIG_SYS_MEMTEST_START	CONFIG_SYS_SDRAM_BASE
#define CONFIG_SYS_MEMTEST_END		\
		(CONFIG_SYS_MEMTEST_START + CONFIG_SYS_SDRAM_SIZE - SZ_256K)

/*
 * LowLevel Init
 */
#ifndef CONFIG_SKIP_LOWLEVEL_INIT
#define CONFIG_SYS_USE_MAIN_OSCILLATOR

/* clocks */
#define CONFIG_SYS_PLLAR_VAL	0x20263E04 /* 179.712000 MHz for PCK */
#define CONFIG_SYS_PLLBR_VAL	0x10483E0E /* 48.054857 MHz (divider by 2 for USB) */
/* PCK/3 = MCK Master Clock = 59.904000MHz from PLLA */
#define CONFIG_SYS_MCKR_VAL	0x00000202

/* sdram */
#define CONFIG_SYS_PIOC_ASR_VAL	0xFFFF0000 /* Configure PIOC as peripheral (D16/D31) */
#define CONFIG_SYS_PIOC_BSR_VAL	0x00000000
#define CONFIG_SYS_PIOC_PDR_VAL	0xFFFF0000
#define CONFIG_SYS_EBI_CSA_VAL	0x00000002 /* CS1=CONFIG_SYS_SDRAM */
#define CONFIG_SYS_SDRC_CR_VAL	0x2188c155 /* set up the CONFIG_SYS_SDRAM */
#define CONFIG_SYS_SDRAM	CONFIG_SYS_SDRAM_BASE /* address of the SDRAM */
#define CONFIG_SYS_SDRAM1	(CONFIG_SYS_SDRAM_BASE+0x80)
#define CONFIG_SYS_SDRAM_VAL	0x00000000 /* value written to CONFIG_SYS_SDRAM */
#define CONFIG_SYS_SDRC_MR_VAL	0x00000002 /* Precharge All */
#define CONFIG_SYS_SDRC_MR_VAL1	0x00000004 /* refresh */
#define CONFIG_SYS_SDRC_MR_VAL2	0x00000003 /* Load Mode Register */
#define CONFIG_SYS_SDRC_MR_VAL3	0x00000000 /* Normal Mode */
#define CONFIG_SYS_SDRC_TR_VAL	0x000002E0 /* Write refresh rate */
#endif	/* CONFIG_SKIP_LOWLEVEL_INIT */

/* DataFlash */
#define CONFIG_ATMEL_DATAFLASH_SPI
#define CONFIG_HAS_DATAFLASH
#define CONFIG_SYS_MAX_DATAFLASH_BANKS		1
#define CONFIG_SYS_DATAFLASH_LOGIC_ADDR_CS0	0xC0000000	/* CS0 */
#define AT91_SPI_CLK				15000000
#define DATAFLASH_TCSS				(0x1a << 16)
#define DATAFLASH_TCHS				(0x1 << 24)


/*
 * Hardware drivers
 */
/*
 * Choose a USART for serial console
 * CONFIG_DBGU is DBGU unit on J10
 * CONFIG_USART1 is USART1 on J14
 */
#define CONFIG_ATMEL_USART
#define CONFIG_USART_BASE	ATMEL_BASE_DBGU
#define CONFIG_USART_ID		0/* ignored in arm */

#define CONFIG_BAUDRATE			115200

/*
 * Command line configuration.
 */
#if 1
#define CONFIG_CMD_EXT2
/* #define CONFIG_CMD_MII */
#define CONFIG_CMD_PING
#define CONFIG_FS_EXT4
#endif

/* #define CONFIG_CMD_USB */

/*
 * Network Driver Setting
 */
#define CONFIG_DRIVER_AT91EMAC
#define CONFIG_SYS_RX_ETH_BUFFER	16
#define CONFIG_MII
#define CONFIG_PHY_NATSEMI
#define CONFIG_NET_RETRY_COUNT		20
#define CONFIG_DRIVER_AT91EMAC_PHYADDR 1


/* MMC */
#define CONFIG_CMD_MMC
#ifdef CONFIG_CMD_MMC
#define CONFIG_MMC
#define CONFIG_GENERIC_MMC
#define CONFIG_GENERIC_ATMEL_MCI
#define CONFIG_DOS_PARTITION			1
#endif

/** Disable NOR flash SUPPORT */
#define CONFIG_SYS_MAX_FLASH_BANKS 0
#define CONFIG_SYS_NO_FLASH

/*
 * USB Config
 */
#if 0
#define CONFIG_USB_ATMEL			1
#define CONFIG_USB_ATMEL_CLK_SEL_PLLB
#define CONFIG_USB_OHCI_NEW			1
#define CONFIG_USB_KEYBOARD			1
#define CONFIG_USB_STORAGE			1

#define CONFIG_SYS_USB_OHCI_CPU_INIT		1
#define CONFIG_SYS_USB_OHCI_REGS_BASE		ATMEL_USB_HOST_BASE
#define CONFIG_SYS_USB_OHCI_SLOT_NAME		"at91rm9200"
#define CONFIG_SYS_USB_OHCI_MAX_ROOT_PORTS	15
#endif

/* bootstrap + u-boot + env + linux in dataflash on CS0 */
#define CONFIG_ENV_IS_IN_DATAFLASH 1
#define CONFIG_SYS_MONITOR_BASE	(CONFIG_SYS_DATAFLASH_LOGIC_ADDR_CS0 + 0x8400)
#define CONFIG_ENV_OFFSET	(510*264)
#define CONFIG_ENV_ADDR		(CONFIG_SYS_DATAFLASH_LOGIC_ADDR_CS0 + CONFIG_ENV_OFFSET)
#define CONFIG_ENV_SIZE		(264*2)
#define CONFIG_BOOTCOMMAND	"ext2load mmc 0:1 0x21000000 /boot/uImage; bootm"
#define CONFIG_BOOTARGS		"console=ttyS0,115200 "			\
			  "mem=32m " \
				"root=/dev/mmcblk0p1 "	\
				"rootdelay=1 init=/sbin/init " \
				"rw"

/*
 * Boot option
 */
#define CONFIG_BOOTDELAY		2

/* default load address */
#define CONFIG_SYS_LOAD_ADDR		CONFIG_SYS_SDRAM_BASE + SZ_16M
#define CONFIG_ENV_OVERWRITE

/*
 * Shell Settings
 */
#define CONFIG_CMDLINE_EDITING
/* #define CONFIG_SYS_LONGHELP */
#define CONFIG_AUTO_COMPLETE
#define CONFIG_SYS_HUSH_PARSER
#define CONFIG_SYS_CBSIZE		256	/* Console I/O Buffer Size */
#define CONFIG_SYS_MAXARGS		16	/* max number of command args */
/* Print Buffer Size */
#define CONFIG_SYS_PBSIZE		\
		(CONFIG_SYS_CBSIZE + sizeof(CONFIG_SYS_PROMPT) + 16)

/*
 * Size of malloc() pool
 */
#define CONFIG_SYS_MALLOC_LEN		ROUND(3 * CONFIG_ENV_SIZE + SZ_128K, \
					     SZ_4K)

#define CONFIG_SYS_INIT_SP_ADDR		(CONFIG_SYS_SDRAM_BASE + SZ_4K \
					- GENERATED_GBL_DATA_SIZE)

#endif /* __AT91RM9200_BFC1_CONFIG_H__ */
