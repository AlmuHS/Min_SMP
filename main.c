

#include <video.h>
#include <mem.h>
#include <acpi.h>
#include <mp.h>

#include <list.h>
#include <lapic.h>

void
main(){
	int i = 0;
	int16 kernel_id;

    mem_setup();
    video_setup();

    if(acpi_setup()){
        puts("ACPI error");
        goto idle;
    }
    if(mp_setup()){
        puts("MP error");
        goto idle;
    }


    puts("MinSMP");

    acpi_print_info();
    mp_print_info();

	lapicinit();

	while(i < 10){
		kernel_id = cpu_number();
		printf("Current CPU: cpu %x\n", kernel_id&0xff); 
		i++;
	}





idle:
    for(;;)
        __asm__("hlt;");


}
