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

#ifndef __LIST_H__
#define __LIST_H__


struct list {
    struct list *prev;
    struct list *next;
};



static inline  void
list_init(struct list *list){
    list->prev = list;
    list->next = list;
}

static inline void
list_init_node(struct list *node){
    node->prev = 0;
    node->next = 0;
}

static inline void
list_add(struct list *prev, struct list *next, struct list *node){
    next->prev = node;
    node->next = next;
    prev->next = node;
    node->prev = prev;
}

static inline void
list_insert_tail(struct list *list, struct list *node){
    list_add(list->prev, list, node);
}

#define list_foreach(list, node)    \
    for( (node) = (list)->next;     \
            (node) != (list);       \
            (node) = (node)->next)

#define list_get_entry(nod, type)  \
    (type *)  ( (void *)nod - (void *)&(((type *)0)->node))
    





#endif /* __LIST_H__ */
