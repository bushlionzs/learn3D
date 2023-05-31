#define THIS_MODULE MODULE_EPC_PLATFORM
#include "timer_logic.h"
#include "platform_util.h"
#include <stdio.h>

#if defined(__gnu_linux__) && !defined(__ANDROID__)
static const uint8_t kTimerBitCount = 20;
#else
static const uint8_t kTimerBitCount = 16;
#endif


namespace highperformance
{
#define TIMER_INDEX( id ) ( id >> 16 )

CTimerLogic::CTimerLogic():m_timer_mgr(kTimerBitCount)
{
	m_timer_jiffies = 0;
	m_tvecs[0] = &m_tv2;
	m_tvecs[1] = &m_tv3;
	m_tvecs[2] = &m_tv4;
	m_tvecs[3] = &m_tv5;

}

CTimerLogic::~CTimerLogic()
{

}

uint32_t CTimerLogic::add_timer( uint32_t duration , int32_t (*platfom_timer_callback)(void* param ), void* param)
{
    if (duration < TIMER_DURATION)
    {
        duration = TIMER_DURATION;
    }

	timer_node* node = _alloc_timer_node();
	node->m_duration	= duration;
	node->m_param		= param;
	node->m_platfom_timer_callback = platfom_timer_callback;
    node->deleted = false;
    node->running = false;

    ScopedLock<PlatformMutex> lock(m_mutex);
	node->m_expires  = duration / TIMER_DURATION + m_timer_jiffies;
    node->m_timer_handler = m_timer_mgr.alloc_and_set( node );
    if( INVALID_TIMER_ID == node->m_timer_handler )
    {
        relase_timer_node( node );
        return INVALID_TIMER_ID;
    }

    add_timer( node );
    
	return node->m_timer_handler;
}

bool CTimerLogic::delete_timer( uint32_t timerid )
{
	ScopedLock<PlatformMutex> lock(m_mutex);
	timer_node* node = m_timer_mgr.get_object( timerid );
	if( NULL == node )
	{
		return false;
	}
	if( node->m_timer_handler != timerid )
	{
		return false;
	}

    node->deleted = true;
    list_del(&node->m_list);

    if (!node->running)
    {
        relase_timer_node( node );
    }

    return true;
}


void CTimerLogic::clean()
{

}

void CTimerLogic::add_timer( timer_node* timer )
{
	uint32_t expires = timer->m_expires;

	uint32_t idx = expires - m_timer_jiffies;

	struct list_head * vec;
	if( idx < TVR_SIZE )
	{
		int index = expires & TVR_MASK;
		vec = &m_tv1.m_vec[index]; 
	}
	else if( idx < 1 << (TVR_BITS + TVN_BITS) )
	{
		int index = (expires >> TVR_BITS) & TVN_MASK;
		vec = &m_tv2.m_vec[index];
	}
	else if( idx < 1 << (TVR_BITS + 2 * TVN_BITS) )
	{
		int index = (expires >> (TVR_BITS + TVN_BITS)) & TVN_MASK;
		vec = &m_tv3.m_vec[index]; 
	}
	else if( idx < 1 << (TVR_BITS + 3 * TVN_BITS) )
	{
		int index = (expires >> (TVR_BITS + 2 * TVN_BITS)) & TVN_MASK;
		vec = &m_tv4.m_vec[index]; 
	}
	else
	{
		int index = (expires >> (TVR_BITS + 3 * TVN_BITS)) & TVN_MASK;
		vec = &m_tv5.m_vec[index];
	}

	list_add(&timer->m_list, vec->m_prev);

}

void CTimerLogic::update_timer()
{
	ScopedLock<PlatformMutex> lock(m_mutex);
	
	if (0 == m_tv1.m_index)
	{
		int n = 0;
		do {
			cascade_timers(m_tvecs[n]);
		} while (m_tvecs[n]->m_index == 1 && ++n < VECS_COUNT );
	}
	
	cascade_timers( &m_tv1 );

	m_timer_jiffies++;
}


void CTimerLogic::cascade_timers(struct timer_vec *tv)
{
	struct list_head *head, *curr, *next;
	head = tv->m_vec + tv->m_index;
	curr = head->m_next;

	while( curr != head )
	{
		struct timer_node* node = list_entry(curr, struct timer_node, m_list);
		next = curr->m_next;
		list_del(curr);
		add_timer(node);
		curr = next;
	}

	tv->m_index = (tv->m_index + 1) & TVN_MASK;
}

void CTimerLogic::cascade_timers( struct timer_vec_root *tv )
{
	struct list_head *head, *curr, *next;
	head = tv->m_vec + tv->m_index;
	curr = head->m_next;

	while( curr != head )
	{
		timer_node* node = list_entry( curr , struct timer_node , m_list );
		next = curr->m_next;
		list_del( curr );
		curr = next;

        node->running = true;
        int32_t ret = node->m_platfom_timer_callback( node->m_param );
        node->running = false;

		if( 0 == ret && !node->deleted)
		{
			node->m_expires  = node->m_duration / TIMER_DURATION + m_timer_jiffies;
			add_timer( node );
		}
		else
		{
			relase_timer_node( node );
		}
	}
	
	tv->m_index = (tv->m_index + 1) & TVR_MASK;
}


timer_node* CTimerLogic::_alloc_timer_node()
{
    timer_node* node = (timer_node*)malloc(sizeof(timer_node));
    list_init(&node->m_list);
	return node;
}

void CTimerLogic::relase_timer_node( timer_node* node )
{
	m_timer_mgr.release_object( node->m_timer_handler );
	free(node);
}
}
