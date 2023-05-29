/*$T Common/HumanStateMutex.h GC 1.140 10/10/07 10:06:30 */

/*
 * created: 2008/10/10 created: 10:10:2008 10:45 filename:
 * Common\HumanStateMutex.h file path: Common file base: HumanStateMutex file ext:
 * h author: Richard purpose:
 * 当玩家处于某持续状态时，是否允许其进行某项操作的管理类
 * 提供查询和设置当前状态的接口
 * 当某项操作会改变玩家当前状态的时候，操作的接受者负责设
 * 置自身新的当前状态，这很重要，一旦玩家当前状态和玩家逻
 * 辑状态不符，会引起后续判断失效，直到玩家当前状态再次被
 * 设置成与玩家逻辑状态符合为止 本管理器是线程安全的，只在server启动时设计写操作，
 * 运行 时逻辑对本管理器仅存在只读的查询需求， 将作为全局对象实 例
 */
#ifndef HumanStateMutex_h__10_10_2008_10_45
#define HumanStateMutex_h__10_10_2008_10_45

#include "TypeDefine.h"
#include "Define.h"
#include "Struct.h"
#include "HumanStateMutexDefine.h"
#include "TAB.h"

struct StateReturnCode
{
	int32	iState;
	int32	iReturnCode;
};

#define RETURNCODE(state)	OR_##state

static StateReturnCode	s_ReturnCode[] =
{
	{ MS_Stall, RETURNCODE(MS_Stall) },
	{ MS_Fuben, RETURNCODE(MS_Fuben) },
	{ MS_BattleFieldMap, RETURNCODE(MS_BattleFieldMap) },
	{ MS_ArenaMap, RETURNCODE(MS_ArenaMap) },
	{ MS_CityMap, RETURNCODE(MS_CityMap) },
	{ MS_PrisonMap, RETURNCODE(MS_PrisonMap) },
	{ MS_Die, RETURNCODE(MS_Die) },
	{ MS_Bus, RETURNCODE(MS_Bus) },
	{ MS_Cashbox, RETURNCODE(MS_Cashbox) },
	{ MS_Exchange, RETURNCODE(MS_Exchange) },
	{ MS_MentalGame, RETURNCODE(MS_MentalGame) },
	{ MS_TeamFollow, RETURNCODE(MS_TeamFollow) },
	{ MS_AutoPlay, RETURNCODE(MS_AutoPlay) },
	{ MS_SubTrain, RETURNCODE(MS_SubTrain) },
	{ MS_Prison, RETURNCODE(MS_Prison) },
	{ MS_OpenBox, RETURNCODE(MS_OpenBox) },
	{ MS_ProtectTime, RETURNCODE(MS_ProtectTime) },
	{ MS_KeyboardMove, RETURNCODE(MS_KeyboardMove) },
	{ MS_Quest_TieSan, RETURNCODE(MS_Quest_TieSan) },
	{ MS_ReadyFuben, RETURNCODE(MS_ReadyFuben) },
	{ MS_Quest_DuoQiBuff, RETURNCODE(MS_Quest_DuoQiBuff) },
	{ MS_Quest_TongQuBuff, RETURNCODE(MS_Quest_TongQuBuff) },
	{ MS_PKMode, RETURNCODE(MS_PKMode) },
	{ MS_ForbidRide, RETURNCODE(MS_ForbidRide) },
	{ MS_Wedding, RETURNCODE(MS_Wedding) },
	{ MS_Enjail, RETURNCODE(MS_Enjail) },
	{ MS_Award, RETURNCODE(MS_Award) },
	{ MS_TransGold, RETURNCODE(MS_TransGold) },
	{ MS_InDancery, RETURNCODE(MS_InDancery) },
	{ MS_BlackGold, RETURNCODE(MS_BlackGold) },
};

class Player;

class			PlayerStateMutex
{
/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	PlayerStateMutex();
	~	PlayerStateMutex();

	/*
	 * Method: InitStateMutexTable ;
	 * FullName: BaseHumanStateMutex::InitStateMutexTable ;
	 * Access: public ;
	 * Returns: void ;
	 * 初始化状态互斥表 ;
	 */
	BOOL	InitStateMutexTable(void);

	/*
	 * Method: IsCanAccptEvent ;
	 * FullName: BaseHumanStateMutex::IsCanAccptEvent ;
	 * Access: public ;
	 * Returns: BOOL TRUE: 可以响应事件, FALSE: 不可响应事件 ;
	 * Qualifier: ;
	 * Parameter: _MutexState eState 查询者自身所处的状态 ;
	 * Parameter: _MutexStateEvent eEvent 事件ID ;
	 */
	BOOL	IsCanAccptEvent(const Player *pPlayer, _MutexStateEvent eEvent);

	/* 清理所有属性 */
	void	Clear(void);

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	int32 GetMutexStateCode()
	{
		return(s_ReturnCode[m_iMutexStateCode].iReturnCode);
	}

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
private:
	void	InitTableLine(TAB::TABFile &ThirdFile, int32 iColumnCount, int32 i);

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
private:
	_HumanStateMutexTBL	m_oStateMutex;

	int32			m_iMutexStateCode;
};

extern PlayerStateMutex g_HumanStateMutex;

#define Check_Human_State_Mutex(a) \
	if(!g_HumanStateMutex.IsCanAccptEvent(pPlayer, (a))) \
	{ \
		pPlayer->SendOperateResultMsg(g_HumanStateMutex.GetMutexStateCode()); \
		return MP_CONTINUE; \
	}
#endif /* HumanStateMutex_h__10_10_2008_10_45 */
