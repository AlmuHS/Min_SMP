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


#ifndef __ASM_H__
#define __ASM_H__




#define outb(val, port)                         \
    __asm__ __volatile ("outb %%al, %%dx"       \
            :                                   \
            : "a" (val), "d" (port)             \
            )







#endif /* __ASM_H__ */
