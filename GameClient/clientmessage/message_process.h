#pragma once

#include <net_define.h>
void sc_human_base_attr(NetHandle h, const char* msg, uint32_t msg_size);

void sc_detail_equip(NetHandle h, const char* msg, uint32_t msg_size);

void sc_detail_item(NetHandle h, const char* msg, uint32_t msg_size);

void sc_detail_skill(NetHandle h, const char* msg, uint32_t msg_size);

void sc_enter_scene(NetHandle h, const char* msg, uint32_t msg_size);

void sc_new_monster(NetHandle h, const char* msg, uint32_t msg_size);

void sc_unequip_result(NetHandle h, const char* msg, uint32_t msg_size);

void sc_use_equip_result(NetHandle h, const char* msg, uint32_t msg_size);

void sc_char_move(NetHandle h, const char* msg, uint32_t msg_size);

