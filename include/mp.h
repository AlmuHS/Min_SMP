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
	Fixed = 0b000,
	LowestPriority = 0b001,
	SMI = 0b010,
	NMI = 0b011,
	INIT = 0b101,
	StartUp = 0b110
};

enum dest_mode_enum{
	Physical = 0b0,
	Logical = 0b1
};

enum deliv_status_enum{
	Idle = 0b0,
	SendPending = 0b1
};

enum level_enum{
	De_assert = 0b0,
	Assert = 0b1
};

enum trig_mode_enum{
	Edge = 0b0,
	Level = 0b1
};

enum dest_sh_enum{
	NoShortHand = 0b00,
	Self = 0b01,
	AllIncludingSelf = 0b10,
	AllExcludingSelf = 0b11
};
 	

typedef enum type_enum type_t;
typedef enum dest_mode_enum dest_mode_t;
typedef enum deliv_status_enum deliv_status_t;
typedef enum level_enum level_t;
typedef enum trig_mode_enum trig_mode_t;
typedef enum dest_sh_enum dest_sh_t;

struct icr_low{
	uint8 vector:8;
	type_t type:3;
	dest_mode_t dest_mode:1;
	deliv_status_t deliv_status:1;
	uint8 reserved1:1;
	level_t level:1;
	trig_mode_t trigger_mode:1;
	uint8 reserved2:2;
	dest_sh_t dest_shorthand:2;
	uint16 reserved3:12;
};

struct icr_high{
	uint32 reserved:24;
	uint8 dest:8;
};

typedef struct icr_low icrl;
typedef struct icr_high icrh;

int mp_setup();

void startup_cpu(uint8 apic_id);

void mp_print_info();

int16 cpu_number();

void write_icr_type(type_t type);
void write_icr_destmode(dest_mode_t dm);
void write_icr_level(level_t level);
void write_icr_trigmode(trig_mode_t trigger_mode);
void write_icr_destsh(dest_sh_t dest_sh);
void write_icr_dest(uint8 dest);

void send_IPI(struct icr_high icr_h, struct icr_low icr_l);



#endif /* __MP_H__ */
