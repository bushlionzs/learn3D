#include "rate_limiter.h"
#include "platform_util.h"

limiter_node::limiter_node(uint64_t limit, uint64_t burst)
{
	_limit = limit;
	_burst = burst;
	_tokens = burst;
	_last = platform_get_tickcount();
}

limiter_node::~limiter_node()
{

}

void limiter_node::change_limiter(uint64_t limit, uint64_t burst)
{
	_limit = limit;
	_burst = burst;
}

uint64_t limiter_node::get_tokens()
{
	advance();
	return _tokens;
}

void limiter_node::release_tokens(uint64_t tokens)
{
	advance();

	if (tokens > _tokens)
	{
		_tokens = 0;
	}
	else
	{
		_tokens -= tokens;
	}
}

bool limiter_node::check_and_release_tokens(uint64_t tokens)
{
	advance();

	if (tokens > _tokens)
	{
		return false;
	}
	else
	{
		_tokens -= tokens;
		return true;
	}
}

void limiter_node::advance()
{
	uint64_t current = platform_get_tickcount();
	uint64_t delta = current - _last;

	_tokens += delta / 1000.0f * _limit;
	if (_tokens > _burst)
	{
		_tokens = _burst;
	}
	_last = current;
}
