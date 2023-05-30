/*********************************************************************************************
created:	10/10/07 10:07:26
filename: 	MisBuf.h
file path:	F:\khan2\src\MapServer\Server\Map
file base:
file ext:	h
author:		
modified:	wujianping
purpose:	任务显示相关 由脚本设置显示的数据
			每一种类型的数据 都对应了显示图标和显示方式
**********************************************************************************************/


#ifndef __MISBUF__H_
#define __MISBUF__H_

struct SQuestBuffer
{
	enum { QUESTBUFLEN = 32, QUESTCHARBUFLEN = QUESTBUFLEN *4 *8, };

	typedef struct _QuestItemBuf
	{
		char	buf[QUESTCHARBUFLEN];
		enum BufType
		{
			BufType_Int,
			BufType_Str,
			BufType_IntStr,
			BufType_Exp,
			BufType_Money,
			BufType_Money1,
			BufType_Money2,
			BufType_Money3,
			BufType_Money4,
			BufType_Money5,
			BufType_Money6,
			BufType_Item,
			BufType_RandItem,
			BufType_RadioItem,
			BufType_Money7,
			BufType_Money8,
			BufType_Money9,
			BufType_Vigor,
			BufType_Charm,
			BufType_Genius,
			BufType_GuildExp,
			BufType_CountryFood,
			BufType_CountryMoney,
			BufType_CountryWood,
			BufType_CountryMetal,
			BufType_WeiWang,
			BufType_QuestTitle,
			BufType_QuestName,
			BufType_QuestTarget,
			BufType_QuestSubmitNPC,
			BufType_QuestManual,
			BufType_QuestInfo,
			BufType_QuestHelp,
			BufType_InherenceExp,
			BufType_GuildMoney,
		} mType;
	} QuestItemInfo[QUESTBUFLEN];

	QuestItemInfo	Buff;
	int32		mUseNum;

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	void Reset()
	{
		mUseNum = 0;
	}
};
#endif
