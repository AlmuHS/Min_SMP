/*Copyright 2018 Juan Bosco Garcia
 *Copyright 2019 Almudena Garcia Jurado-Centurion
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


#ifndef __LAPIC_H__
#define __LAPIC_H__

#include <acpi.h>
#include <types.h>

#include <stdint.h>
/*
 * Common bits for registers in the local vector table.
 */
#define LAPIC_LVT_DELIVERY_FIXED    0x00000000
#define LAPIC_LVT_DELIVERY_NMI      0x00000400
#define LAPIC_LVT_DELIVERY_EXTINT   0x00000700
#define LAPIC_LVT_MASK_INTR 0x00010000

/*
 * LVT timer register bits.
 */
#define LAPIC_LVT_TIMER_PERIODIC    0x00020000

/*
 * Various values related to the local APIC timer.
 */
#define LAPIC_TIMER_DCR_DIV1    0x0000000b
#define LAPIC_TIMER_COUNT_MAX   0xffffffff

/*
 * Delay used to calibrate the local APIC timer, in microseconds.
 */
#define LAPIC_TIMER_CAL_DELAY   100000

/*
 * Spurious-interrupt vector register bits.
 */
#define LAPIC_SVR_SOFT_EN 0x00000100

typedef struct ApicReg
{
	unsigned r;	/* the actual register */
	unsigned p[3];	/* pad to the next 128-bit boundary */
} ApicReg;

/* Grateful to trasterlabs for this snippet */

typedef union u_icr_low
{
    uint32_t value[4];
    struct
    {
        uint32_t low;  // FEE0 0300H - 4 bytes
        unsigned :32;  // FEE0 0304H
        unsigned :32;  // FEE0 0308H
        unsigned :32;  // FEE0 030CH
    };
    struct
    {
        unsigned vector: 8; /* Vector of interrupt. Lowest 8 bits of routine address */
        unsigned delivery_mode : 3;
        unsigned destination_mode: 1;
        unsigned delivery_status: 1;
        unsigned :1;
        unsigned level: 1;
        unsigned trigger_mode: 1;
        unsigned :2;
        unsigned destination_shorthand: 2;
        unsigned :12;
    };
        
} IcrLReg;

typedef union u_icr_high
{
    uint32_t value[4];
    struct
    {
        uint32_t high; // FEE0 0310H - 4 bytes
        unsigned :32;  // FEE0 0314H
        unsigned :32;  // FEE0 0318H
        unsigned :32;  // FEE0 031CH
    };
    struct
    {
        unsigned :24; // FEE0 0310H - 4 bytes
        unsigned destination_field :8; /* APIC ID (in physical mode) or MDA (in logical) of destination processor */
    };
} IcrHReg;

typedef enum e_icr_dest_shorthand
{
        NO_SHORTHAND = 0,
        SELF = 1,
        ALL_INCLUDING_SELF = 2,
        ALL_EXCLUDING_SELF = 3
} icr_dest_shorthand;

typedef enum e_icr_deliv_mode
{
        FIXED = 0,
        LOWEST_PRIORITY = 1,
        SMI = 2,
        NMI = 4,
        INIT = 5,
        STARTUP = 6,
} icr_deliv_mode;

typedef enum e_icr_dest_mode
{
        PHYSICAL = 0,
        LOGICAL = 1
} icr_dest_mode;

typedef enum e_icr_deliv_status
{
        IDLE = 0,
        SEND_PENDING = 1
} icr_deliv_status;

typedef enum e_icr_level
{
        DE_ASSERT = 0,
        ASSERT = 1
} icr_level;

typedef enum e_irc_trigger_mode
{
        EDGE = 0,
        LEVEL = 1
} irc_trigger_mode;


typedef struct ApicLocalUnit {
        ApicReg reserved0;               /* 0x000 */
        ApicReg reserved1;               /* 0x010 */
        ApicReg apic_id;                 /* 0x020. Hardware ID of current processor */
        ApicReg version;                 /* 0x030 */
        ApicReg reserved4;               /* 0x040 */
        ApicReg reserved5;               /* 0x050 */
        ApicReg reserved6;               /* 0x060 */
        ApicReg reserved7;               /* 0x070 */
        ApicReg task_pri;                /* 0x080 */
        ApicReg arbitration_pri;         /* 0x090 */
        ApicReg processor_pri;           /* 0x0a0 */
        ApicReg eoi;                     /* 0x0b0 */
        ApicReg remote;                  /* 0x0c0 */
        ApicReg logical_dest;            /* 0x0d0 */
        ApicReg dest_format;             /* 0x0e0 */
        ApicReg spurious_vector;         /* 0x0f0 */
        ApicReg isr[8];                  /* 0x100 */
        ApicReg tmr[8];                  /* 0x180 */
        ApicReg irr[8];                  /* 0x200 */
        ApicReg error_status;            /* 0x280 */
        ApicReg reserved28[6];           /* 0x290 */
        ApicReg lvt_cmci;                /* 0x2f0 */
        IcrLReg icr_low;                 /* 0x300. Store the information to send an IPI (Inter-processor Interrupt) */
        IcrHReg icr_high;                 /* 0x310. Store the information to send an IPI (Inter-processor Interrupt) */
        ApicReg lvt_timer;               /* 0x320 */
        ApicReg lvt_thermal;             /* 0x330 */
        ApicReg lvt_performance_monitor; /* 0x340 */
        ApicReg lvt_lint0;               /* 0x350 */
        ApicReg lvt_lint1;               /* 0x360 */
        ApicReg lvt_error;               /* 0x370 */
        ApicReg init_count;              /* 0x380 */
        ApicReg cur_count;               /* 0x390 */
        ApicReg reserved3a;              /* 0x3a0 */
        ApicReg reserved3b;              /* 0x3b0 */
        ApicReg reserved3c;              /* 0x3c0 */
        ApicReg reserved3d;              /* 0x3d0 */
        ApicReg divider_config;          /* 0x3e0 */
        ApicReg reserved3f;              /* 0x3f0 */
} ApicLocalUnit;


#endif /* __LAPIC_H__ */
