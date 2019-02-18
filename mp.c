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

//ICR Destination mode
#define PHYSICAL 0
#define LOGICAL 1

//ICR Delivery mode
#define STARTUP 6
#define INIT 5

//ICR Level
#define DE_ASSERT 0
#define ASSERT 1

//ICR Trigger mode
#define EDGE 0
#define LEVEL 1

//ICR Destination Shorthand
#define NO_SHORTHAND 0


extern volatile ApicLocalUnit* lapic;
extern uint32 nioapic;	
extern struct list ioapics;
extern struct cpu cpus[NCPU];
extern int ncpu;
extern void* *apboot, *apbootend;
extern void dummyf(uint32);

extern void* *stack_ptr;

extern void *stack_bsp;

int mp_setup(){
	int i=0;

    /* setup BSP processor */
	cpus[i].stack_base = &stack_bsp;

    if(cpu_setup()) return -1;
	
    //TODO: Start CPUs
    memcpy((void*)AP_BOOT_ADDR, (void*)&apboot, (uint32)&apbootend - (uint32)&apboot);

    for(i = 1; i < ncpu; i++){
        #define STACK_SIZE (4096 * 2)
        *stack_ptr = malloc(STACK_SIZE);
        cpus[i].stack_base = *stack_ptr;

        uint32 apic_id = cpus[i].apic_id;
        printf("sending IPI to %x\n", apic_id);

        startup_cpu(apic_id);

        printf("IPI send\n");
    }

	//volatile uint32 *flags_p = &cpus[i].flags;
	//while((*flags_p & CPU_ENABLE) == 0);
	
    return 0;
}


void
mp_print_info(){

    printf("LAPIC\n");
    printf(" lapic_addr = %x\n", lapic);

    printf("CPU:\n");
    int i;

    for(i=0;i<ncpu;i++){
        printf(" cpu %x: apic_id = %x", i, cpus[i].apic_id);
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


void startup_cpu(uint32 apic_id){	    

    lapic->icr_high.r = (apic_id << 24);
    lapic->icr_low.r = (INIT << 8) | (ASSERT << 14) | (LEVEL << 15);    
    
	dummyf(lapic->apic_id.r);	

    lapic->icr_high.r = (apic_id << 24);
    lapic->icr_low.r = (INIT << 8) | (DE_ASSERT << 14) | (LEVEL << 15);
    
	dummyf(lapic->apic_id.r);	

    lapic->icr_high.r = (apic_id << 24);
    lapic->icr_low.r = (STARTUP << 8) | ((AP_BOOT_ADDR >>12) & 0xff);
    
	dummyf(lapic->apic_id.r);

    lapic->icr_high.r = (apic_id << 24);
    lapic->icr_low.r = (STARTUP << 8) | ((AP_BOOT_ADDR >>12) & 0xff);
    
	dummyf(lapic->apic_id.r);

    //printf("\nicr_high: %x\n", lapic->icr_high.r);
    //printf("\nicr_low: %x\n", lapic->icr_low.r);
	
}

int16 cpu_number(){
	uint32 apic_id;
    uint16 i = 0;

	//Read apic id from the current cpu, using its lapic
	apic_id = lapic->apic_id.r >>24;

	printf("apic id: %x ", apic_id);
	printf("version: %x ", lapic->version.r);

	//Search apic id in cpu2apic vector
	while(cpus[i].apic_id != apic_id && i < ncpu) i = i+1;

	if(i == ncpu) return -1;

	else return i;
}


void send_IPI(unsigned icr_h, unsigned icr_l){	
	lapic->icr_low.r = icr_l;
	lapic->icr_high.r = icr_h;
}




