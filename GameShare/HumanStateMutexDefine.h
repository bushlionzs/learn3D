/*$T Common/HumanStateMutexDefine.h GC 1.140 10/10/07 10:06:30 */

/*
 * created: 2008/10/10 created: 10:10:2008 11:29 filename:
 * Common\HumanStateMutexDefine.h file path: Common file base:
 * HumanStateMutexDefine file ext: h author: Richard purpose:
 * ���״̬���������������ݽṹ��ö�ٵ�����
 */
#ifndef HumanStateMutexDefine_h__10_10_2008_11_34
#define HumanStateMutexDefine_h__10_10_2008_11_34

const int32	Max_Mutex_State = 64;
const int32	Max_Input_Event = 128;

#define FILE_HUMAN_MUTEX	"./../Public/Config/PlayerStateMutex.tab"

enum _MutexState
{
	MS_FreeState		= -1,
	MS_Stall		= 0,	/* ��̯ */
	MS_Fuben,			/* ���� */
	MS_BattleFieldMap,		/* ս�� */
	MS_ArenaMap,			/* ��̨ */
	MS_CityMap,			/* ���� */
	MS_PrisonMap,			/* ���� */
	MS_Die,			/* ���� */
	MS_Bus,			/* Bus */
	MS_Cashbox,		/* ���� */
	MS_Exchange,		/* ���� */
	MS_MentalGame,		/* ���� */
	MS_TeamFollow,		/* ��Ӹ��� */
	MS_AutoPlay,		/* �һ�Client */
	MS_SubTrain,		/* ���� */
	MS_Prison,		/* ���� */
	MS_OpenBox,		/* ���� */
	MS_ProtectTime,		/* ������������ʱ�� */
	MS_KeyboardMove,	/* �����ƶ�Client */
	MS_Quest_TieSan,	/* ���������������� */
	MS_ReadyFuben,		/* �Ѿ����ܸ������񣬵ȴ� */
	MS_Quest_DuoQiBuff,	/* ����������buffʱ��״̬ */
	MS_Quest_TongQuBuff,	/* ͯȤ������buffʱ��״̬ */
	MS_PKMode,		/* ����PKģʽ״̬ */
	MS_ForbidRide,		/* 081226������������״̬�������������ض������������������� */
	MS_Wedding,		/* ���ڻ���״̬ */
	MS_Enjail,		/* ����״̬ */
	MS_Award,		/* �콱״̬ */
	MS_TransGold,		/* ��ȡ�ֽ�״̬ */
	MS_InDancery,		/* ������ */
	MS_BlackGold,		/* �ڽ����״̬ */
	MS_NumOfMutexState
};

enum _MutexStateEvent
{
	ME_CXAskQuestList	= 0,	/* ���� */
	ME_CXEventRequest,		/* �����¼� */
	ME_CXQuestAccept,		/* �������� */
	ME_CXQuestAbandon,		/* �������� */
	ME_CXQuestRefuse,		/* �ܾ����� */
	ME_CXQuestSubmit,		/* ������� */
	ME_CXQuestContinue,		/* �������� */
	ME_CXCharJump,			/* �����Ծ */
	ME_CXCharMoodState,		/* ��ұ��鶯�� */
	ME_CXCharMove,			/* ����ƶ� */
	ME_CXPlayerDieResult,		/* ������� */
	ME_CXChat,			/* ���� */
	ME_CXUseItem,			/* ʹ����Ʒ */
	ME_CXShopBuy,			/* �̵깺�� */
	ME_CXShopSell,			/* �̵��� */
	ME_CXShopRepair,		/* �̵��� */
	ME_CXCountryAppoint,		/* ����ί�� */
	ME_CXExchangeSynchLock,		/* ������ */
	ME_CXStallEstablish,		/* ������̯ */
	ME_CXStallOpen,			/* ��ʼ̯λ */
	ME_CXSplitItem,			/* ��Ʒ��� */
	ME_CXAskSubTrainMode,		/* ����ģʽ */
	ME_CXSetShowSuitMode,		/* ������ʾ��װģʽ */
	ME_CXOpenBox,			/* ������ */
	ME_CXOpenBoxManipulate,		/* ���������� */
	ME_CXRegisterTeamRecruit,	/* ע�������ļ */
	ME_CXCountryCollect,		/* ���Ҳɼ� */
	ME_CXCountryDonative,		/* ���Ҿ��� */
	ME_CXBusApplyInto,		/* ���� */
	ME_CXBusLeave,			/* �뿪 */
	ME_CXBusRetInto,		/* ���ؽ��� */
	ME_CXGuildBattle,		/* ��ս */
	ME_CXMentalGame,		/* ���� */
	ME_ChangeScene,			/* �г��� */
	ME_CountryCallOfMan,		/* �������� */
	ME_TeamFollow,			/* ��Ӹ��� */
	ME_UseSkill,			/* ʹ�ü��� */
	ME_GuildCallOfMan,		/* ������� */
	ME_AcceptBuff,			/* ����buff */
	ME_GetRide,			/* ��� */
	ME_SwitchPKMode,		/* �л�PKģʽ */
	ME_JoinWedding,			/* �μӻ��� */
	ME_Enjail,			/* ������ */
	ME_Award,			/* �콱�� */
	ME_TransGold,			/* ��ȡ�ֽ��� */
	ME_GotoFightPos,		/* ���͵��������ս����λ�� */
	ME_Wedding,			/* �ٰ���� */
	ME_Dress,			/* ʹ����װ */
	ME_GuildConvoke,		/* ����ټ� */
	ME_Duel,			/* ���� */
	ME_NumOfStateEvent
};

struct _HumanStateMutexTBL
{
	BOOL	aMutexState[MS_NumOfMutexState][ME_NumOfStateEvent];
};
#endif /* HumanStateMutexDefine_h__10_10_2008_11_34 */
