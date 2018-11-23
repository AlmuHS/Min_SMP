/*Copyright 2018 Juan Bosco Garcia, Almudena Garcia Jurado-Centurion
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

#ifndef __MP_H__
#define __MP_H__

#include <types.h>

#define NCPU 128

struct cpu {
    uint8 apic_id;
};


enum type_enum{
	Fixed = 0x0,
	LowestPriority = 0x1,
	SMI = 0x2,
	NMI = 0x4,
	INIT = 0x5,
	StartUp = 0x6
};

enum dest_mode_enum{
	Physical = 0x0,
	Logical = 0x1
};

enum deliv_status_enum{
	Idle = 0x0,
	SendPending = 0x1
};

enum level_enum{
	De_assert = 0x0,
	Assert = 0x1
};

enum trig_mode_enum{
	Edge = 0x0,
	Level = 0x1
};

enum dest_sh_enum{
	NoShortHand = 0x0,
	Self = 0x1,
	AllIncludingSelf = 0x2,
	AllExcludingSelf = 0x3
};

struct icr_low{
	uint8 vector:8;
	enum type_enum type:3;
	enum dest_mode_enum dest_mode:1;
	enum deliv_status_enum deliv_status:1;
	uint8 reserved1:1;
	enum level_enum level:1;
	enum trig_mode_enum trigger_mode:1;
	uint8 reserved2:2;
	enum dest_sh_enum dest_shorthand:2;
	uint16 reserved3:12;
};

struct icr_high{
	uint32 reserved:24;
	uint8 dest:8;
};


volatile struct icr_low* icr_low_addr = (struct icr_low*) 0xFEE00300;
volatile struct icr_high* icr_high_addr = (struct icr_high*) 0xFEE00310;

int mp_setup();

void mp_print_info();

int16 cpu_number();

void send_IPI(struct icr_high icr_h, struct icr_low icr_l);



#endif /* __MP_H__ */
