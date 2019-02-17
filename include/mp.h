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
#include <lapic.h>


int mp_setup();

void startup_cpu(uint8 apic_id);

void mp_print_info();

int16 cpu_number();

void write_icr_type(icr_type type);
void write_icr_destmode(icr_dest_mode dm);
void write_icr_level(icr_level level);
void write_icr_trigmode(icr_trig_mode trigger_mode);
void write_icr_destsh(icr_dest_sh dest_sh);
void write_icr_dest(uint8 dest);

void send_IPI(icrh icr_h, icrl icr_l);



#endif /* __MP_H__ */
