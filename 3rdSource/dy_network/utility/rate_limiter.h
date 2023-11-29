#pragma once
#include <double_list.h>
#include <stdint.h>

class limiter_node
{
	uint64_t _limit; //tokens adding in one second
	uint64_t _burst; //max tokens
	double _tokens; //current tokens 
	uint64_t _last;   //last time the limiter's tokens field was updated
public:
	limiter_node(uint64_t limit, uint64_t burst);
	~limiter_node();
	void change_limiter(uint64_t limit, uint64_t burst);
	uint64_t get_tokens();// ==0 means lacking of tokens
	void release_tokens(uint64_t tokens); 

	bool check_and_release_tokens(uint64_t tokens);
private:
	void advance();
};

