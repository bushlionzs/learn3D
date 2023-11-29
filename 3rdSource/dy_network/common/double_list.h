#ifndef __DOUBLE_LIST_H
#define __DOUBLE_LIST_H

struct list_head 
{
    list_head()
    {
        m_next = this;
        m_prev = this;
    }
	struct list_head *m_next, *m_prev;
};

void list_add(struct list_head *entry, struct list_head *head);

void list_add_tail(struct list_head* _new, struct list_head* head);

void list_del(struct list_head *entry);

bool list_empty( struct list_head *entry);

void list_init( struct list_head * entry );
#define list_entry(ptr, type, member) ((type *)((char *)(ptr)-(char *)(&((type *)0)->member)))


#endif//__DOUBLE_LIST_H
