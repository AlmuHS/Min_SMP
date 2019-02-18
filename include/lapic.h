/*Copyright 2018 Juan Bosco Garcia
 *Copyright 2019 Almudena Garcia Jurado-Centurion
 *This file is part of Min_SMP. 
 *Min_SMP is free software: you can redistribute it and/or modify
 *it under the terms of the GNU General Public License as published by
 *the Free Software Foundation, either version 3 of the License, or
 *(at your option) any later version.
 *Min_SMP is distributed in the hope that it will be useful,
 *but WITHOUT ANY WARRANTY; without even the implied warranty of
 *MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *GNU General Public License for more details.
 *You should have received a copy of the GNU General Public License
 *along with Min_SMP.  If not, see <http://www.gnu.org/licenses/>.
 */


#ifndef __LAPIC_H__
#define __LAPIC_H__

#include <acpi.h>
#include <types.h>


typedef struct ApicReg
{
	unsigned r;	/* the actual register */
	unsigned p[3];	/* pad to the next 128-bit boundary */
} ApicReg;

typedef struct ApicIoUnit
{
	ApicReg select;
	ApicReg window;
} ApicIoUnit;


//#define APIC_IO_UNIT_ID			0x00
//#define APIC_IO_VERSION			0x01
//#define APIC_IO_REDIR_LOW(int_pin)	(0x10+(int_pin)*2)
//#define APIC_IO_REDIR_HIGH(int_pin)	(0x11+(int_pin)*2)

typedef struct ApicLocalUnit
{
    /* 0x000 */
    ApicReg reserved0;
    /* 0x010 */
    ApicReg reserved1;
    /* 0x020 */
    ApicReg apic_id;
    /* 0x030 */
    ApicReg version;
    /* 0x040 */
    ApicReg reserved4;
    /* 0x050 */
    ApicReg reserved5;
    /* 0x060 */
    ApicReg reserved6;
    /* 0x070 */
    ApicReg reserved7;
    /* 0x080 */
    ApicReg task_pri;
    /* 0x090 */
    ApicReg arbitration_pri;
    /* 0x0a0 */
    ApicReg processor_pri;
    /* 0x0b0 */
    ApicReg eoi;
    /* 0x0c0 */
    ApicReg remote;
    /* 0x0d0 */
    ApicReg logical_dest;
    /* 0x0e0 */
    ApicReg dest_format;
    /* 0x0f0 */
    ApicReg spurious_vector;
    /* 0x100 */
    ApicReg isr[8];
    /* 0x180 */
    ApicReg tmr[8];
    /* 0x200 */
    ApicReg irr[8];
    /* 0x280 */
    ApicReg error_status;
    /* 0x290 */
    ApicReg reserved28[6];
    /* 0x2f0 */
    ApicReg lvt_cmci;
    /* 0x300 */
    ApicReg icr_low;
    /* 0x310 */
    ApicReg icr_high;
    /* 0x320 */
    ApicReg timer_vector;
    /* 0x330 */
    ApicReg thermal_sensor;
    /* 0x340 */
    ApicReg performance_monitor;
    /* 0x350 */
    ApicReg lint0_vector;
    /* 0x360 */
    ApicReg lint1_vector;
    /* 0x370 */
    ApicReg error;
    /* 0x380 */
    ApicReg init_count;
    /* 0x390 */
    ApicReg cur_count;
    /* 0x3a0 */
    ApicReg reserved3a;
    /* 0x3b0 */
    ApicReg reserved3b;
    /* 0x3c0 */
    ApicReg reserved3c;
    /* 0x3d0 */
    ApicReg reserved3d;
    /* 0x3e0 */
    ApicReg divider_config;
    /* 0x3f0 */
    ApicReg reserved3f;
} ApicLocalUnit;






#endif /* __LAPIC_H__ */
