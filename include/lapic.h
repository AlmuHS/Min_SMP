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

/* TODO: send IPI and configure lapic

*/


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


#define APIC_IO_UNIT_ID			0x00
#define APIC_IO_VERSION			0x01
#define APIC_IO_REDIR_LOW(int_pin)	(0x10+(int_pin)*2)
#define APIC_IO_REDIR_HIGH(int_pin)	(0x11+(int_pin)*2)

typedef struct ApicLocalUnit
{
	ApicReg reserved0;
	ApicReg reserved1;
	ApicReg apic_id;
	ApicReg version;
	ApicReg reserved4;
	ApicReg reserved5;
	ApicReg reserved6;
	ApicReg reserved7;
	ApicReg task_pri;
	ApicReg arbitration_pri;
	ApicReg processor_pri;
	ApicReg eoi;
	ApicReg remote;
	ApicReg logical_dest;
	ApicReg dest_format;
	ApicReg spurious_vector;
	ApicReg isr[8];
	ApicReg tmr[8];
	ApicReg irr[8];
	ApicReg error_status;
	ApicReg reserved28[5];
	ApicReg lvt_cmci;
	ApicReg icr_low;
	ApicReg icr_high;
	ApicReg timer_vector;
	ApicReg thermal_sensor;
	ApicReg performance_monitor;
	ApicReg lint0_vector;
	ApicReg lint1_vector;
	ApicReg error;
	ApicReg init_count;
	ApicReg cur_count;
	ApicReg reserved3a;
	ApicReg reserved3b;
	ApicReg reserved3c;
	ApicReg reserved3d;
	ApicReg divider_config;
	ApicReg reserved3f;
} ApicLocalUnit;






#endif /* __LAPIC_H__ */
