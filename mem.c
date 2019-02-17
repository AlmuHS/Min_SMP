/*Copyright 2018 Juan Bosco Garcia
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


#include <mem.h>


extern void* _end;
void *last;


void
mem_setup(){

    last = (void*) ( (((uint32)&_end + 0x10 - 1 ) / 0x10) * 0x10 );


}


void*
malloc(uint32 size){

    void *addr = last;

    last += size;
    last = (void*) ( (((uint32)last + 0x10 - 1 ) / 0x10) * 0x10 );

    return addr;
}


int
memcmp(void *ptr1, void *ptr2, uint32 size){
    uint8 *s1 = ptr1;
    uint8 *s2 = ptr2;
    unsigned int i;

    for(i=0;i<size;i++){
        if(s1[i] != s2[i])
            return -1;
    }

    return 0;
}

int
memcpy(void *dest, void *src, uint32 size){
    uint8 *d = dest;
    uint8 *s = src;
    unsigned int i;

    for(i=0;i<size;i++){
        d[i] = s[i];
    }

    return 0;
}

