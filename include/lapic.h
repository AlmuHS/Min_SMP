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

typedef enum type_enum{
	Fixed = 0b000,
	LowestPriority = 0b001,
	SMI = 0b010,
	NMI = 0b011,
	INIT = 0b101,
	StartUp = 0b110
} icr_type;

typedef enum dest_mode_enum{
	Physical = 0b0,
	Logical = 0b1
} icr_dest_mode;

typedef enum deliv_status_enum{
	Idle = 0b0,
	SendPending = 0b1
} icr_deliv_status;

typedef enum level_enum{
	De_assert = 0b0,
	Assert = 0b1
} icr_level; 

typedef enum trig_mode_enum{
	Edge = 0b0,
	Level = 0b1
} icr_trig_mode;

typedef enum dest_sh_enum{
	NoShortHand = 0b00,
	Self = 0b01,
	AllIncludingSelf = 0b10,
	AllExcludingSelf = 0b11
} icr_dest_sh;
 	

typedef struct icr_low{
	uint8 vector:8;
	icr_type type:3;
	icr_dest_mode dest_mode:1;
	icr_deliv_status deliv_status:1;
	uint8 reserved1:1;
	icr_level level:1;
	icr_trig_mode trigger_mode:1;
	uint8 reserved2:2;
	icr_dest_sh dest_shorthand:2;
	uint16 reserved3:12;
} icrl;

typedef struct icr_high{
	uint32 reserved:24;
	uint8 dest:8;
} icrh;

typedef struct ApicICRHReg
{
	icrh r;	/* the actual register */
	unsigned p[3];	/* pad to the next 128-bit boundary */
} ApicICRHReg;

typedef struct ApicICRLReg
{
	icrl r;	/* the actual register */
	unsigned p[3];	/* pad to the next 128-bit boundary */
} ApicICRLReg;


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
	ApicICRLReg icr_low;
	ApicICRHReg icr_high;
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
