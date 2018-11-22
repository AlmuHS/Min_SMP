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

struct icr_high{
	uint32 reserved:24;
	uint8 dest:8;
};

struct icr_low{
	uint8 vector:8;
	uint8 type:3;
	uint8 dest_mode:1;
	uint8 deliv_status:1;
	uint8 reserved1:1;
	uint8 level:1;
	uint8 trigger_mode:1;
	uint8 reserved2:2;
	uint8 dest_shorthand:2;
	uint16 reserved3:12;
};

int mp_setup();

void mp_print_info();

int16 cpu_number();


#endif /* __MP_H__ */
