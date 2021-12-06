/*Copyright 2018 2019 Juan Bosco Garcia, Almudena Garcia Jurado-Centurion
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


/*Partially based in x15 project, by Richard Braun
 *https://github.com/richardbraun/x15
 *
 */
#ifndef __CPU_H__

#include <types.h>

#define NCPU 256
#define CPU_ENABLE (1 << 0)

/*
 * System defined exception vectors.
 *
 * The local APIC assigns one priority every 16 vectors.
 */
#define CPU_EXC_XCALL               238
#define CPU_EXC_THREAD_SCHEDULE     239
#define CPU_EXC_HALT                240
#define CPU_EXC_LAPIC_PMC_OF        252
#define CPU_EXC_LAPIC_TIMER         253
#define CPU_EXC_LAPIC_ERROR         254
#define CPU_EXC_LAPIC_SPURIOUS      255


struct cpu {
    uint32 apic_id;
	uint32 flags;
	void *stack_base;
};


extern int ncpu;

int cpu_setup();

void cpu_ap_main();

#endif
