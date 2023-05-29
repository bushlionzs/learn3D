/*$T Common/Type.h GC 1.140 10/10/07 10:06:57 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#ifndef __TYPE_H__
#define __TYPE_H__

#include <vector>
#include "Basics.h"
#include <stdint.h>

typedef int16		ID_t;
typedef uint16		MKID_t;
typedef uint32		MK_VALUE;
typedef uint32		ObjID_t;
typedef int32_t     int32;

typedef int32_t		PrescriptionID_t;
typedef ID_t		SkillID_t;
typedef ID_t		TeamID_t;
typedef ID_t		MapID_t;
typedef ID_t		ConnectorID_t;
typedef ID_t		GridID_t;
typedef ID_t		SpellID_t;
typedef ID_t		ActionID_t;
typedef ID_t		EffectID_t;
typedef ID_t		ImpactClassID_t;
typedef ID_t		Coord_t;
typedef int32_t		ScriptID_t;
typedef int32_t		QuestID_t;
typedef ID_t		GroupID_t;
typedef ID_t		ChannelID_t;
typedef ID_t		CooldownID_t;
typedef uchar		CampID_t;
typedef ID_t		GuildID_t;
typedef ID_t		CityID_t;
typedef ID_t		TopListID_t;
typedef ID_t		BusID_t;
typedef ID_t		CountryID_t;
typedef ID_t		JiaZuID_t;
typedef int32_t		Time_t;
typedef int32_t		BOOL;
typedef unsigned long	ulong;

typedef struct _Int64
{
	long		a;
	unsigned long	b;
} Int64;

typedef uint32			GUID_t;

#define INVALID_GUID	((GUID_t) (-1))
#define INVALID_INDEX	(-1)
#define INVALID_ID_EX	- 2

#if defined(__WINDOWS__)
typedef ulong			TID;
typedef unsigned __int64	MODEL_PART;
typedef unsigned __int64	uint64;

#elif defined(__LINUX__)
typedef void			VOID;
typedef pthread_t		TID;
typedef unsigned long long	uint64;
typedef unsigned long long	MODEL_PART;
typedef const char		*LPCSTR;
#endif
#if defined(__LINUX__)
typedef int32			MKHandle;
typedef struct
{
	volatile int32	counter;
} atomic_t;
typedef atomic_t	atword;
#define initword(v, i)	(((v).counter) = (i))
#elif defined(__WINDOWS__)
typedef void		*MKHandle;
typedef volatile long	atword;
#define initword(v, i)	((v) = (i))
#endif
typedef void	*DBHandle;

#define ISSET0(x)	((x) & 0x1)
#define ISSET1(x)	((x) & 0x2)
#define ISSET2(x)	((x) & 0x4)
#define ISSET3(x)	((x) & 0x8)
#define ISSET4(x)	((x) & 0x10)
#define ISSET5(x)	((x) & 0x20)
#define ISSET6(x)	((x) & 0x40)
#define ISSET7(x)	((x) & 0x80)
#define ISSET8(x)	((x) & 0x100)
#define ISSET9(x)	((x) & 0x200)
#define ISSET10(x)	((x) & 0x400)
#define ISSET11(x)	((x) & 0x800)
#define ISSET12(x)	((x) & 0x1000)
#define ISSET13(x)	((x) & 0x2000)
#define ISSET14(x)	((x) & 0x4000)
#define ISSET15(x)	((x) & 0x8000)
#include "Debug.h"
#include "Define.h"
#include "Enum.h"
#include "DefineAttr.h"
#include "DefineItem.h"
#include "DefineResult.h"
#include "DefineMap.h"
#include "DefineGuild.h"
#include "DefinePlayerShop.h"
#include "Struct.h"
#include "Util.h"

#if defined(GAME_CLIENT)
#define __GUARD__
#define __UNGUARD__
#elif 1
#if defined(__WINDOWS__)
#if defined(NDEBUG)
#define __GUARD__ 

#define __UNGUARD__ 
#else
#define __GUARD__ \
	{ \
		try \
		{
#define __UNGUARD__ \
} \
catch(...) \
{ \
	KCheckSpecial(FALSE, __FUNCTION__); \
} \
}
#endif
#else
#define __GUARD__ \
	{ \
		try \
		{
#define __UNGUARD__ \
} \
catch(...) \
{ \
	KCheckSpecial(FALSE, __PRETTY_FUNCTION__); \
} \
}
#endif
#endif
#endif
