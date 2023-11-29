#ifndef __MSG_PROCESS_H__
#define __MSG_PROCESS_H__
#include <stdint.h>

void serverlogic_init();
uint32_t serverlogic_entry(uint32_t moduleid, uint32_t msg_id, uint64_t sender, uint64_t param, void* msg , uint32_t msg_size, void* pNetThreadData);

void msg_init();
uint32_t msg_entry(uint32_t moduleid, uint32_t msg_id, uint64_t sender, uint64_t param, void* msg , uint32_t msg_size, void* pNetThreadData);

#endif //__MSG_PROCESS_H__