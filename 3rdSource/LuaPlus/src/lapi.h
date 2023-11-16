/*
** $Id: lapi.h,v 1.1 2010/04/07 06:30:47 xiaochunlin Exp $
** Auxiliary functions from Lua API
** See Copyright Notice in lua.h
*/

#ifndef lapi_h
#define lapi_h


#include "lobject.h"

NAMESPACE_LUA_BEGIN

LUAI_FUNC void luaA_pushobject (lua_State *L, const TValue *o);

NAMESPACE_LUA_END

#endif
