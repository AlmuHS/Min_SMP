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

#include <mp.h>
#include <ioapic.h>
#include <video.h>
#include <list.h>
#include <mem.h>
#include <cpu.h>

#define AP_BOOT_ADDR (0x7000)	

extern volatile ApicLocalUnit* lapic;
extern uint32 nioapic;	
extern struct list ioapics;
extern struct cpu cpus[NCPU];
extern int ncpu;
extern void* *apboot, *apbootend;

extern void* *stack_ptr;

extern void *stack_bsp;

int mp_setup(){
	int i=0;

    /* setup BSP processor */
	cpus[i].stack_base = &stack_bsp;

	
    //TODO: Start CPUs
    memcpy((void*)AP_BOOT_ADDR, (void*)&apboot, (uint32)&apbootend - (uint32)&apboot);

    for(i = 1; i < ncpu; i++){
		#define STACK_SIZE (4096 * 2)
        *stack_ptr = malloc(STACK_SIZE);
		cpus[i].stack_base = *stack_ptr;

	    startup_cpu(cpus[i].apic_id);
    }

	volatile uint32 *flags_p = &cpus[i].flags;
	while((*flags_p & CPU_ENABLE) == 0);
	
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
        if(cpus[i].flags & CPU_ENABLE) printf(" ENABLE");
        printf("\n");
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

	icr_h.dest = apic_id;	

    lapic->icr_low.r.dest_mode = Physical;
    lapic->icr_low.r.dest_shorthand = NoShortHand;
    lapic->icr_low.r.type = INIT;
    lapic->icr_low.r.level = Assert;
    lapic->icr_high.r.dest = apic_id;
    //icr_l.dest_mode = Physical;
	//icr_l.dest_shorthand = NoShortHand;
	
    //icr_l.type = INIT;
	//icr_l.level = Assert;

    //printf("\nIPI type: %x\n", icr_l.type);
    

	//send_IPI(icr_h, icr_l);

    printf("\nIPI type: %x\n", lapic->icr_low.r.type);

	lapic->apic_id.r;	

    while(lapic->icr_low.r.deliv_status == 1){
        printf("waiting to INIT assert IPI...\n");
    };

	icr_l.level = De_assert;
	send_IPI(icr_h, icr_l);
	lapic->apic_id.r;	

    /*while(lapic->icr_low.r.deliv_status == 1){
        printf("waiting to INIT deassert IPI...");
    };*/

    icr_l.type = StartUp;
    icr_l.vector = AP_BOOT_ADDR >>12;
    icr_l.level = Assert;	

    send_IPI(icr_h, icr_l);
	//lapic->apic_id.r;

    /*while(lapic->icr_low.r.deliv_status == 1){
        printf("waiting to Startup IPI...");
    };*/

    //printf("\nIPI type: %x\n", lapic->icr_low.r.type);
    icr_l.vector = AP_BOOT_ADDR >>12;
	send_IPI(icr_h, icr_l);
	lapic->apic_id.r;

    while(lapic->icr_low.r.deliv_status == 1){
        printf("waiting to 2nd Startup IPI...");
    };
	
}

int16 cpu_number(){
	uint16 apic_id, i = 0;

	//Read apic id from the current cpu, using its lapic
	
	apic_id = lapic->apic_id.r >>24;

	printf("apic id: %x ", apic_id);
	printf("version: %x ", lapic->version.r);

	//Search apic id in cpu2apic vector
	while(cpus[i].apic_id != apic_id && i < ncpu) i = i+1;

	if(i == ncpu) return -1;

	else return i;
}


void write_icr_type(uint8 type){
	lapic->icr_low.r.type = type;
}

void write_icr_destmode(uint8 dm){
	lapic->icr_low.r.dest_mode = dm;
}

void write_icr_vector(uint8 vector){
	lapic->icr_low.r.vector = vector;
}

void write_icr_level(uint8 level){
	lapic->icr_low.r.level = level;
}

void write_icr_trigmode(uint8 trigger_mode){
	lapic->icr_low.r.trigger_mode = trigger_mode;
}

void write_icr_destsh(uint8 dest_sh){
	lapic->icr_low.r.dest_shorthand = dest_sh;
}

void write_icr_dest(uint8 dest){
	lapic->icr_high.r.dest = dest;
}

void send_IPI(icrh icr_h, icrl icr_l){	
	lapic->icr_low.r = icr_l;
	lapic->icr_high.r = icr_h;
    //printf("\nIPI type: %x\n", lapic->icr_low.r.type);
}




