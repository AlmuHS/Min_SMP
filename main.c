/*Copyright 2018 Juan Bosco Garcia
 *Copyright 2018 2019 Almudena Garcia Jurado-Centurion
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

#include <video.h>
#include <mem.h>
#include <acpi.h>
#include <mp.h>

#include <list.h>
#include <lapic.h>

void
main(){
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

    kernel_id = cpu_number();
    printf("Current CPU: cpu %x\n", kernel_id&0xff); 


idle:
    for(;;)
        __asm__("hlt;");

}
