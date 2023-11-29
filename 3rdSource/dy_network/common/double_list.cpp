#include "double_list.h"

static inline void __list_del(struct list_head * prev,
				  struct list_head * next)
{
	next->m_prev = prev;
	prev->m_next = next;
}




static inline void __list_add(struct list_head * entry,
	struct list_head * prev,
	struct list_head * next)
{
	next->m_prev = entry;
	entry->m_next = next;
	entry->m_prev = prev;
	prev->m_next = entry;
}


void list_add_tail(struct list_head* _new, struct list_head* head)
{
	__list_add(_new, head->m_prev, head);
}


void list_add(struct list_head *entry, struct list_head *head)
{
	__list_add(entry, head, head->m_next);
}

void list_del(struct list_head *entry)
{
	__list_del(entry->m_prev, entry->m_next);
}

bool list_empty( struct list_head *entry)
{
	return entry->m_next == entry;
}

void list_init( struct list_head * entry )
{
	entry->m_next = entry;
	entry->m_prev = entry;
}
