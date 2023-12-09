#include "message_process.h"

#include "db/db_manager.h"
#include "db/db_task.h"

void cs_user_login(NetHandle h, const char* msg, uint32_t msg_size)
{
	auto id = std::string("1610000020");
	CharDataTask* task = new CharDataTask(id, h);
	DBManager::GetSingletonPtr()->addDbTask(task);
}

void cs_char_move(NetHandle h, const char* msg, uint32_t msg_size)
{

}

void cs_char_use_skill(NetHandle h, const char* msg, uint32_t msg_size)
{

}

void cs_event_request(NetHandle h, const char* msg, uint32_t msg_size)
{

}

void cs_manipulate_pet(NetHandle h, const char* msg, uint32_t msg_size)
{

}

void cs_pick_item(NetHandle h, const char* msg, uint32_t msg_size)
{

}

void cs_player_request_base_attr(NetHandle h, const char* msg, uint32_t msg_size)
{

}

void cs_query_event(NetHandle h, const char* msg, uint32_t msg_size)
{

}

void cs_quest_abandon(NetHandle h, const char* msg, uint32_t msg_size)
{

}

void cs_quest_accept(NetHandle h, const char* msg, uint32_t msg_size)
{

}

void cs_quest_continue(NetHandle h, const char* msg, uint32_t msg_size)
{

}

void cs_quest_refuse(NetHandle h, const char* msg, uint32_t msg_size)
{

}

void cs_quest_submit(NetHandle h, const char* msg, uint32_t msg_size)
{

}

void cs_swap_item(NetHandle h, const char* msg, uint32_t msg_size)
{

}

void cs_tick(NetHandle h, const char* msg, uint32_t msg_size)
{

}

void cs_takedown_equip(NetHandle h, const char* msg, uint32_t msg_size)
{

}

void cs_use_ability(NetHandle h, const char* msg, uint32_t msg_size)
{

}

void cs_use_equip(NetHandle h, const char* msg, uint32_t msg_size)
{

}