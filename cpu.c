#include <cpu.h>
#include <mp.h>
#include <lapic.h>
#include <ioapic.h>
#include <video.h>
#include <list.h>

extern volatile ApicLocalUnit* lapic;
int ncpu;
struct cpu cpus[NCPU];

int
cpu_setup(){

    int i = 0;
    while(i<ncpu && (cpus[i].flags && CPU_ENABLE)) i++;

    /* panic? */
    if(i>=ncpu)
	return -1;

    /* assume Pentium 4, Xeon, or later processors */
    cpus[i].apic_id = (lapic->apic_id.r >> 24) & 0xff;
    cpus[i].flags |= CPU_ENABLE;


    return 0;
}


void
cpu_ap_main(){

    printf("\ncurrent processor: %x\n", cpu_number());

   if(cpu_setup())
        goto idle;

idle:
    for(;;)
        asm volatile("hlt");
}

