#ifndef __CPU_H__

#include <types.h>

#define NCPU 256
#define CPU_ENABLE (1 << 0)

struct cpu {
    uint32 apic_id;
	uint32 flags;
	void *stack_base;
};


int ncpu;
struct cpu cpus[NCPU];

int cpu_setup();

void cpu_ap_main();

#endif
