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
extern void* *apboot, *apbootend;
extern void dummyf(uint32);

extern struct cpu cpus[NCPU];

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

        //send IPI to start CPU
        startup_cpu(cpus[i].apic_id);
    
        //wait until new cpu is enabled
        volatile uint32 *flags_p = &cpus[i].flags;
	    while(!(*flags_p & CPU_ENABLE));

    }
	
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

/*TODO: Add delay between IPI*/
void startup_cpu(uint32 apic_id){
	    
    /* First INIT IPI */	    
    send_ipi(NO_SHORTHAND, INIT, PHYSICAL, ASSERT, LEVEL, 0 , apic_id);
    dummyf(lapic->apic_id.r);	

    /* Second INIT IPI */
    send_ipi(NO_SHORTHAND, INIT, PHYSICAL, ASSERT, LEVEL, 0 , apic_id);
    dummyf(lapic->apic_id.r);	

    /* First StartUp IPI */
    send_ipi(NO_SHORTHAND, STARTUP, PHYSICAL, ASSERT, LEVEL, AP_BOOT_ADDR >>12 , apic_id);
    dummyf(lapic->apic_id.r);

    /* Second StartUp IPI */
    send_ipi(NO_SHORTHAND, STARTUP, PHYSICAL, ASSERT, LEVEL, AP_BOOT_ADDR >>12 , apic_id);
    dummyf(lapic->apic_id.r);

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



void send_ipi(unsigned dest_shorthand, unsigned deliv_mode, unsigned dest_mode, unsigned level, unsigned trig_mode, unsigned vector, unsigned dest_id)
{
    IcrLReg icrl_values;
    IcrHReg icrh_values;
    
    icrl_values.destination_shorthand = dest_shorthand;
    icrl_values.delivery_mode = deliv_mode;
    icrl_values.destination_mode = dest_mode;
    icrl_values.level = level;
    icrl_values.trigger_mode = trig_mode;
    icrl_values.vector = vector;
    icrh_values.destination_field = dest_id;
    
    lapic->icr_high = icrh_values;
    lapic->icr_low = icrl_values;
    
}




