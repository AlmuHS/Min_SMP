


#ifndef __LAPIC_H__
#define __LAPIC_H__

#include <acpi.h>
#include <types.h>

/* TODO: send IPI and configure lapic

*/


/*struct lapic_table{
*	uint32 reserved1;
*	uint16 apic_id;
*	const uint16 apic_version;
*	uint32 reserved2;
*	uint32 reserved3;
*	const uint16 tpr;
*	const uint16 apr;
*	const uint16 ppr;
*	uint16 eoi;
*	const uint16 rrd;
*	uint16 ldr;
*	uint16 int_vector;
*	uint64 isr_1;
*	uint64 isr_2;
*};
*/

//static void lapicw(int index, int value);
void lapicinit(void);
void lapicstartap(uint8 apicid, uint16 addr);




#endif /* __LAPIC_H__ */
