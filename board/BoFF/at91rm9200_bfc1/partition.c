
/*
 * (C) Copyright 2016
 * Lucjan Bryndza <lbryndza.p@boff.pl>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */
#include <common.h>
#include <config.h>
#include <asm/hardware.h>
#include <dataflash.h>

#define FLAG_PROTECT_CLR 0

AT91S_DATAFLASH_INFO dataflash_info[CONFIG_SYS_MAX_DATAFLASH_BANKS];

struct dataflash_addr cs[CONFIG_SYS_MAX_DATAFLASH_BANKS] = {
	{CONFIG_SYS_DATAFLASH_LOGIC_ADDR_CS0, 0},	/* Logical adress, CS */
};

/*
  DB011 Memory sector 264B Sectors 512
   0 sector - Darrel loader [ max size 11351 ]
   43 sector - Uboot base [ max size 123287 ]
   510 sector - Environment [ max size 11351 ]
*/

/*define the area offsets*/
dataflash_protect_t area_list[NB_DATAFLASH_AREA] = {
	{0x00000000, 0x00002c57, FLAG_PROTECT_SET,   0, "1st-ldr"},
	{0x00002c58, 0x00020def, FLAG_PROTECT_SET, 0, "U-Boot"},
	{0x00020df0, 0x00020fff, FLAG_PROTECT_CLR,   0, "env"},
};
