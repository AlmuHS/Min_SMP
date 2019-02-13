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
#include <ioapic.h>
#include <video.h>
#include <list.h>
#include <mem.h>

int ncpu;
struct cpu cpus[NCPU];

extern volatile ApicLocalUnit* lapic;
extern uint32 nioapic;	
extern struct list ioapics;
extern void lapicstartap(uint8 apicid, uint16 addr);


#define VECTOR 0xFEE00300
#define DELIVMODE 0xFEE00308
#define DESTMODE 0xFEE0030A
#define DELIVSTATUS 0xFEE0030B
#define LEVEL 0xFEE0030D
#define TRIGMODE 0xFEE0030E
#define DESTSH 0xFEE00312
#define DEST 0xFEE00348

int mp_setup(){
	int n;

	//TODO: Start CPUs
	//uint8 *code;
	//code = P2V(0x7000);
	
	//for(int i = 0; i < ncpu; i++){
	//	lapicstartap(cpus[i].apic_id, 0x7000);
	//}

	if(cpu_number() == 1) n = 0;
	else n = 1;

	startup_cpu(cpus[n].apic_id);
	
	
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


void startup_cpu(uint8 apic_id){	
	icrl icr_l;
	icrh icr_h;
	int i = 0;

	icr_h.dest = apic_id;	
	icr_l.dest_mode = Physical;
	icr_l.dest_shorthand = NoShortHand;
	icr_l.vector = 0x7E00 >> 12;


	icr_l.type = INIT;

	send_IPI(icr_h, icr_l);

	
	while(i < 100) i++;

	send_IPI(icr_h, icr_l);
	write_icr_type(StartUp);
	

	i = 0;
	while(i < 5000) i++;

}

int16 cpu_number(){
	uint16 apic_id, i = 0;

	//Read apic id from the current cpu, using its lapic
	
	apic_id = lapic->apic_id.r;

	printf("apic id: %x ", apic_id);
	printf("version: %x ", lapic->version.r);

	//Search apic id in cpu2apic vector
	while(cpus[i].apic_id != apic_id && i < ncpu) i = i+1;

	if(i == ncpu) return -1;

	else return i;
}


void write_icr_type(icr_type type){
	lapic->icr_low.r.type = type;
}

void write_icr_destmode(icr_dest_mode dm){
	lapic->icr_low.r.dest_mode = dm;
}

void write_icr_level(icr_level level){
	lapic->icr_low.r.level = level;
}

void write_icr_trigmode(icr_trig_mode trigger_mode){
	lapic->icr_low.r.trigger_mode = trigger_mode;
}

void write_icr_destsh(icr_dest_sh dest_sh){
	lapic->icr_low.r.dest_shorthand = dest_sh;
}

void write_icr_dest(uint8 dest){
	lapic->icr_high.r.dest = dest;
}

void send_IPI(icrh icr_h, icrl icr_l){	
	lapic->icr_low.r = icr_l;
	lapic->icr_high.r = icr_h;

}




