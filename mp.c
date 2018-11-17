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

#include <mp.h>
#include <lapic.h>
#include <ioapic.h>
#include <video.h>
#include <list.h>
#include <mem.h>




int ncpu;
struct cpu cpus[NCPU];

extern uint32 lapic;
extern uint32 nioapic;
extern struct list ioapics;
extern void lapicstartap(uint8 apicid, uint16 addr);


int
mp_setup(){

	//TODO: Start CPUs
	//uint8 *code;
	//code = P2V(0x7000);
	
	//for(int i = 0; i < ncpu; i++){
	//	lapicstartap(cpus[i].apic_id, 0x7000);
	//}

    return 0;
}


void
mp_print_info(){

    printf("LAPIC\n");
    printf(" lapic_addr = %x\n", lapic);

    printf("CPU:\n");
    int i;
    for(i=0;i<ncpu;i++){
        printf(" cpu %x: apic_id = %x\n", i, cpus[i].apic_id);
    }

    printf("IOAPIC:\n");
    struct list *node;
    list_foreach(&ioapics, node){
        struct ioapic *ioapic;
        ioapic = list_get_entry(node, struct ioapic);

        printf(" ioapic: apic_id= %x addr = %x, base = %x\n",
                ioapic->apic_id, ioapic->addr,
                ioapic->base);
    }

}

int16 cpu_number(){
	uint16 apic_id;
	int i = 0;

	apic_id = *(uint16*) (lapic+0x20);

	//printf("apic id: %x ", apic_id);

	while(cpus[i].apic_id != apic_id && i < ncpu) i = i+1;

	if(i == ncpu) return -1;
	else return i;
}

