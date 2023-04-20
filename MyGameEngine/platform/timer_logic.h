#ifndef __TIMER_LOGIC_H__
#define __TIMER_LOGIC_H__


#include <stdint.h>
#include <vector>
#include <list>

#include "object_index.h"

#include "double_list.h"


#define TVN_BITS 6
#define TVR_BITS 8
#define TVN_SIZE (1 << TVN_BITS)
#define TVR_SIZE (1 << TVR_BITS)
#define TVN_MASK (TVN_SIZE - 1)
#define TVR_MASK (TVR_SIZE - 1)


namespace highperformance
{
struct timer_node
{
	struct list_head m_list;
	uint32_t m_expires;
	uint32_t m_duration;
	int32_t (*m_platfom_timer_callback)( void* param );
	void*    m_param;
	uint32_t m_timer_handler;
    bool running;
    bool deleted;
};



struct timer_vec
{
	int32_t m_index;
	list_head m_vec[TVN_SIZE];
	timer_vec()
	{
		m_index = 0;
	}
};

struct timer_vec_root
{
	int32_t m_index;
	list_head m_vec[TVR_SIZE];
	timer_vec_root()
	{
		m_index = 0;
	}
};

#define VECS_COUNT 4
#define TIMER_DURATION 10

class CTimerLogic
{
public:
	CTimerLogic();
	~CTimerLogic();
public:
	uint32_t add_timer( uint32_t duration , int32_t (*platfom_timer_callback)( void* param ), void* param  );
	void update_timer();
	bool delete_timer( uint32_t timerid );
    void clean();
private:
	void add_timer( timer_node* timer );
	void delete_timer( timer_node& timer );
	void cascade_timers( struct timer_vec *tv );
	void cascade_timers( struct timer_vec_root *tv );
private:
	timer_node* _alloc_timer_node();
	void relase_timer_node( timer_node* node );
private:
	timer_vec_root m_tv1;
	timer_vec m_tv2 , m_tv3 , m_tv4 , m_tv5;
	timer_vec* m_tvecs[VECS_COUNT];
	uint32_t   m_timer_jiffies;
	PlatformMutex m_mutex;
	CObjectMgr<timer_node> m_timer_mgr;
};
}
#endif //__TIMER_LOGIC_H__
