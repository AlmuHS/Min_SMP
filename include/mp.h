

#ifndef __MP_H__
#define __MP_H__

#include <types.h>

#define NCPU 128


struct cpu {
    uint8 apic_id;
};

int mp_setup();

void mp_print_info();

int16 cpu_number();


#endif /* __MP_H__ */
