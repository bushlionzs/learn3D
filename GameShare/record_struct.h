/*$T MapServer/Server/Base/record_struct.h GC 1.140 10/10/09 10:07:21 */

/*
$File Name:
	record_struct.h
$Purpose:
	����������Ϸϵͳ��Ϊ��־�ĸ�ʽ
$Update history:
	v1.0 created.
*/
#ifndef _RECORD_STRUCT_H_
#define _RECORD_STRUCT_H_

/*
 * ifndef __RECORD_GAMEWAY_H_ ;
 * #error "Not direct include record_struct.h, Please include record_gameway.h" ;
 * #endif
 */
#include "act_define.h"

struct ItemLogRecordInfo
{
	GUID_t		CharGUID;			/* �����ɫ,��Ʒ������ */
	char		Name[MAX_CHARACTER_NAME];	/* ��ɫ���� */
	char		TargetName[MAX_CHARACTER_NAME]; /* Ŀ���ɫ���� */
	char		IP[IP_SIZE];			/* ����server IP */
	SItemGuid	ItemGuid;			/* ��Ʒ��� */
	uint32		ItemType;			/* ��Ʒȫ�ֱ�� */
	GUID_t		TargetGUID;			/* Ŀ���ɫ */
	eItemActType	OpType;			/* �������� */
	char		OpDesc[128];		/* �������� */
	eItemActType	SecOpType;		/* ת������ */
	uint8		ContainerPos;		/* ����λ�� */
	uint8		DestContainerPos;	/* Ŀ������λ�� */
	uint32		Count;			/* �仯���� */
	MapID_t		MapID;			/* ������� */
	int32		NpcType;		/* npc ����,����ʱ��������� */
	float		XPos;			/* �¼�����λ�� */
	float		ZPos;
	int32		ShopGUID;		/* ����̵�� */
	uint8		GemMax;			/* ���ʯ����(��װ����Ҫ) */
	int32		ScriptID;		/* �ű�ID */
	int32		WorldID;		/* ������ID */

	ItemLogRecordInfo (void)
	{
		clear();
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void clear(void)
	{
		CharGUID = TargetGUID = -1;
		OpType = OpType = eItemAct_Unknow;
		ContainerPos = DestContainerPos = -1;
		Count = 1;
		MapID = NpcType = -1;
		XPos = ZPos = 0.0f;
		ShopGUID = -1;
		GemMax = 0;
		ItemType = 0;
		ScriptID = -1;
		WorldID = 0;
		memset(Name, 0, sizeof(Name));
		memset(TargetName, 0, sizeof(TargetName));
		memset(IP, 0, sizeof(IP));
		memset(OpDesc, 0, sizeof(OpDesc));
	}
};

struct EquipLogRecordInfo
{
	GUID_t		CharGUID;	/* �����ɫ,��Ʒ������ */
	char		Name[MAX_CHARACTER_NAME];	/* ��ɫ���� */
	char		IP[IP_SIZE];			/* ����server IP */
	SItemGuid	ItemGuid;			/* ��Ʒ��� */
	uint32		ItemType;			/* ��Ʒȫ�ֱ�� */
	eEquipActType	OpType;		/* �������� */
	uint8		Level;		/* �Ǽ� */
	uint8		MaJiang;	/* �齫 */
	_ITEM_PROPERTY	AttContent[MAX_EQUIP_EXT_ATTR]; /* װ������ */
	MapID_t		MapID;			/* ������� */
	int32		WorldID;	/* ������ID */

	EquipLogRecordInfo (void)
	{
		clear();
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void clear(void)
	{
		CharGUID = -1;
		OpType = eEquipAct_Unknow;
		ItemType = Level = 0;
		MaJiang = INVALID_PAI_TYPE;
		for(int32 i = 0; i < MAX_EQUIP_EXT_ATTR; ++i) AttContent[i].Clear();
		memset(Name, 0, sizeof(Name));
		memset(IP, 0, sizeof(IP));
		ItemGuid.Reset();
		MapID = -1;
		WorldID = 0;
	}
};

struct CurrencyLogRecordInfo
{
	GUID_t			CharGUID;			/* �����ɫ,money������ */
	GUID_t			TargetGUID;			/* Ŀ���ɫ */
	eCurrencyActType	OPType;				/* �������� */
	uint8			MoneyType;			/* ��Ǯ���� */
	int32			Count;				/* ���� */
	int32			RemainCount;			/* ʣ���Ǯ������ */
	MapID_t			MapID;				/* ������� */
	float			XPos;				/* �¼�����λ�� */
	float			ZPos;
	char			Name[MAX_CHARACTER_NAME];	/* ��ɫ���� */
	int32			ItemIndex;			/* ��Ʒ���(������ʱ����Ч) */
	int32			ItemCount;			/* ������Ʒ���� */
	SHorseGiud		PetGUID;			/* ����GUID */
	ScriptID_t		ScriptId;			/* �ű�id*/
	int16			nExt;				/* ����nExt, ������չ����ȷ�Ľ�Ǯ�ļ�¼*/
	int32			WorldID;			/* ������ID */

	CurrencyLogRecordInfo()
	{
		clear();
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void clear(void)
	{
		CharGUID = TargetGUID = INVALID_ID;
		OPType = eCurrencyAct_Unknow;
		MoneyType = 0;
		Count = 0;
		MapID = -1;
		XPos = ZPos = 0.0f;
		memset(Name, 0, sizeof(Name));
		ItemIndex = -1;
		ItemCount = 0;
		PetGUID.m_uHighSection = 0;
		PetGUID.m_uLowSection = 0;
		ScriptId = 0;
		nExt = 0;	
		WorldID = 0;
	}
};

struct PetLogRecordInfo
{
	GUID_t		CharGUID;	/* �����ɫ,Pet������ */
	GUID_t		TargetGUID;	/* Ŀ���ɫ */
	ePetActType	OPType;		/* �������� */
	MapID_t		MapID;		/* ������� */
	float		XPos;		/* �¼�����λ�� */
	float		ZPos;
	SHorseGiud	PetGUID;	/* ����GUID */
	int32		DataID;		/* �������� */
	int32		WorldID;	/* ������ID */

	PetLogRecordInfo (void)
	{
		clear();
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void clear(void)
	{
		CharGUID = INVALID_ID;
		TargetGUID = INVALID_ID;
		OPType = ePetAct_Unknow;
		MapID = -1;
		DataID = -1;
		XPos = 0.0f;
		ZPos = 0.0f;
		WorldID = 0;
		PetGUID.m_uHighSection = 0;
		PetGUID.m_uLowSection = 0;
	}
};
struct SkillLogRecordInfo
{
	GUID_t		CharGUID;	/* �����ɫ,Skill������ */
	eSkillActType	OPType;		/* �������� */
	MapID_t		MapID;		/* ������� */
	float		XPos;		/* �¼�����λ�� */
	float		ZPos;
	SpellID_t	SkillID;	/* ���ܺ� */
	int32		Level;		/* ���� */
	int32		Count;		/* ���� */
	int32		WorldID;	/* ������ID */

	SkillLogRecordInfo()
	{
		clear();
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void clear(void)
	{
		CharGUID = INVALID_ID;
		OPType = eSkillAct_Unknow;
		MapID = -1;
		XPos = 0.0f;
		ZPos = 0.0f;
		SkillID = -1;
		Level = -1;
		Count = 0;
		WorldID = 0;
	}
};

struct AbilityLogRecordInfo
{
	GUID_t		CharGUID;	/* �����ɫ,Skill������ */
	eAbilityActType OPType;		/* �������� */
	MapID_t		MapID;		/* ������� */
	float		XPos;		/* �¼�����λ�� */
	float		ZPos;
	SpellID_t	AbilityID;	/* ���ܺ� */
	int32		Level;		/* ���� */
	int32		Count;
	int32		WorldID;

	AbilityLogRecordInfo()
	{
		clear();
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void clear(void)
	{
		CharGUID = INVALID_ID;
		OPType = eAbilityAct_Unknow;
		MapID = -1;
		XPos = 0.0f;
		ZPos = 0.0f;
		AbilityID = -1;
		Level = -1;
		Count = 0;
		WorldID = 0;
	}
};

struct QuestLogRecordInfo
{
	GUID_t		CharGUID;	/* �����ɫ,Skill������ */
	eQuestActType	OPType;		/* �������� */
	MapID_t		MapID;		/* ������� */
	float		XPos;		/* �¼�����λ�� */
	float		ZPos;
	QuestID_t	idMission;
	ScriptID_t	idScript;
	uint8		yFlags;
	uint32		aParam[MAX_QUEST_PARAM_NUM];
	int32		nDoneFlagIndex;
	int32		nDoneFlagValue;
	int32		nDataIndex;
	int32		nDataValue;

	QuestLogRecordInfo (void)
	{
		clear();
	};

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void clear(void)
	{
		CharGUID = INVALID_ID;		/* �����ɫ,Skill������ */
		OPType = eQuestAct_Unknow;	/* �������� */
		MapID = INVALID_ID;		/* ������� */
		XPos = 0.0f;			/* �¼�����λ�� */
		ZPos = 0.0f;
		idMission = INVALID_ID;
		idScript = INVALID_ID;
		yFlags = 0;
		memset(aParam, 0, sizeof(uint32) * MAX_QUEST_PARAM_NUM);
		nDoneFlagIndex = INVALID_INDEX;
		nDoneFlagValue = 0;
		nDataIndex = INVALID_INDEX;
		nDataValue = 0;
	}
};

struct TeamMemberLvlAndJob
{
	int32	Level;
	int32	Job;
	TeamMemberLvlAndJob (void)
	{
		clear();
	};

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void clear(void)
	{
		Job = Level = -1;
	}
};

struct GameWayLogRecoreInfo
{
	GUID_t			CharGUID;			/* �����ɫ */
	char			Name[MAX_CHARACTER_NAME];	/* ��ɫ���� */
	MapID_t			MapID;	/* ������� */
	int32			GameID;
	uint8			HaveTeam;
	uint8			member_cnt;
	int32			WorldID;		/* ������ID */
	TeamMemberLvlAndJob	member[MAX_TEAM_MEMBER];

	GameWayLogRecoreInfo (void)
	{
		clear();
	};

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void clear(void)
	{
		CharGUID = INVALID_ID;		/* �����ɫ,Skill������ */
		MapID = INVALID_ID;		/* ������� */
		GameID = INVALID_ID;
		HaveTeam = 0;
		member_cnt = 0;
		WorldID = 0;
		for(int32 i = 0; i < MAX_TEAM_MEMBER; ++i) member[i].clear();
	}
};

struct EnterSceneLogRecordInfo
{
	GUID_t	CharGUID;			/* �����ɫ */
	char	Name[MAX_CHARACTER_NAME];	/* ��ɫ���� */
	MapID_t MapID;	/* ������� */
	int32	GameID;
	int32	DayCount;
	int32	WorldID;

	EnterSceneLogRecordInfo (void)
	{
		clear();
	};

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void clear()
	{
		CharGUID = INVALID_ID;	/* �����ɫ,Skill������ */
		MapID = INVALID_ID;	/* ������� */
		GameID = INVALID_ID;
		DayCount = 0;
		WorldID = 0;
	}
};

struct GoldCardLogRecordInfo
{
	GUID_t	guidChar;		/* ���GUID */
	char	Name[MAX_CHARACTER_NAME];	/* ��ɫ���� */
	MapID_t mapId;		/* ����ID */
	int32	iChangeType;	/* ������� */
	int32	iCostTypeId;	/* ��Ǯ���� */
	uint32	uPayment;	/* ��Ǯ������� */
	uint32	uItemTypeID;	/* �����ƷID */
	int32	iItemCount;	/* �����Ʒ���� */
	int32	WorldID;

	GoldCardLogRecordInfo (void)
	{
		clear();
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void clear(void)
	{
		guidChar = INVALID_ID;
		mapId = INVALID_ID;
		iChangeType = INVALID_ID;
		uItemTypeID = 0;
		uPayment = 0;
		iCostTypeId = INVALID_ID;
		memset(Name, 0, sizeof(Name));
		WorldID = 0;
	}
};

enum ManageLogType
{
	MLT_ONLENE_USER_COUNT	= 0,
	MLT_ONLENE_ITEM,
	MLT_ONLENE_MONEY,
	MLT_ONLENE_IB,
	MLT_ONLENE_TRADE,
	MLT_ONLENE_EQUIP,
};

struct TradeLogRecordInfo
{
	struct ItemParam
	{

		/*
		 =======================================================================================================
		 =======================================================================================================
		 */
		void clear(void)
		{
			m_nItemId = INVALID_ID;
			m_nCount = 0;
			m_nItemGuid.Reset();
		}

		int32		m_nItemId;
		SItemGuid	m_nItemGuid;
		int32		m_nCount;
	};
	struct TradeParam
	{
		enum eTradeType { eExchange = 0, eStallSiller, eStallGold };

		/*
		 =======================================================================================================
		 =======================================================================================================
		 */
		void clear(void)
		{
			m_nCharGuid = INVALID_GUID;
			memset(m_szCharName, 0, sizeof(m_szCharName));
			m_nSceneId = INVALID_ID;
			m_nTradeType = eExchange;
			m_nPreGold = 0;
			m_nAftGold = 0;
			for(int32 i = 0; i < EXCHANGE_BOX_SIZE; ++i) m_anItem[i].clear();
			m_nPetId = INVALID_ID;
			m_nPetGuid.Reset();
		}

		GUID_t		m_nCharGuid;
		char		m_szCharName[MAX_CHARACTER_NAME];
		MapID_t		m_nSceneId;
		int32		m_nTradeType;
		int32		m_nPreGold;
		int32		m_nAftGold;
		ItemParam	m_anItem[EXCHANGE_BOX_SIZE];
		int32		m_nPetId;
		SHorseGiud	m_nPetGuid;
	};

	TradeLogRecordInfo (void)
	{
		clear();
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void clear(void)
	{
		for(int32 i = 0; i < 2; ++i) m_anTradeParam[i].clear();
		m_WorldID = 0;
	}

	TradeParam	m_anTradeParam[2];
	int32		m_WorldID;
};

struct WorldShopLogRecordInfo
{
	GUID_t			OwnerGUID;	/* ������GUID */
	GUID_t			BuyerGUID;	/* ������GUID */
	eWorldShopCashActType	OPType;		/* �������� */
	int32			ShopId;		/* �̵�ID */
	uint32			SerialId;	/* �̵��е�λ��,-1��ʾ����Ҫλ�� */
	int32			SellGold;	/* ����/������ȡ�ֽ��� */
	int32			GoldNum;	/* ������ȡʱ��¼���ֽ���� */
	int32			Price;		/* �ۼ� */
	int32			SillerNum;	/* ������ȡʱ��¼���������� */
	int32			Charge;		/* �̷ּ� */
	uint32			CreateTime;	/* ����ʱ�� */
	uint32			DeleteTime;	/* ɾ��ʱ�� */
	MapID_t			MapID;		/* ����ID */
	int32			WorldID;	/* ������ID */

	WorldShopLogRecordInfo (void)
	{
		clear();
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void clear(void)
	{
		OwnerGUID = INVALID_ID;
		BuyerGUID = INVALID_ID;
		OPType = eWorldShopCashAct_Unknow;
		ShopId = -1;
		SerialId = -1;
		SellGold = 0;
		GoldNum = 0;
		Price = 0;
		SillerNum = 0;
		Charge = 0;
		CreateTime = -1;
		DeleteTime = -1;
		MapID = -1;
		WorldID = 0;
	}
};

struct GLGoldShopLogRecordInfo
{
	GUID_t			OwnerGUID;	/* ������GUID */
	GUID_t			BuyerGUID;	/* ������GUID */
	eWorldShopCashActType	OPType;		/* �������� */
	int32			ShopId;		/* �̵�ID */
	uint32			SerialId;	/* �̵��е�λ��,-1��ʾ����Ҫλ�� */
	int32			SellGold;	/* ����/������ȡ�ֽ��� */
	int32			GoldNum;	/* ������ȡʱ��¼���ֽ���� */
	int32			Price;		/* �ۼ� */
	int32			SillerNum;	/* ������ȡʱ��¼���������� */
	int32			Charge;		/* �̷ּ� */
	uint32			CreateTime;	/* ����ʱ�� */
	uint32			DeleteTime;	/* ɾ��ʱ�� */

	GLGoldShopLogRecordInfo (void)
	{
		clear();
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void clear(void)
	{
		OwnerGUID = INVALID_ID;
		BuyerGUID = INVALID_ID;
		OPType = eWorldShopCashAct_Unknow;
		ShopId = -1;
		SerialId = -1;
		SellGold = 0;
		GoldNum = 0;
		Price = 0;
		SillerNum = 0;
		Charge = 0;
		CreateTime = -1;
		DeleteTime = -1;
	}
};

struct CheatActLogRecordInfo
{
	char		Account[MAX_ACCOUNT + 1];		/* �ʺ� */
	char		CharName[MAX_CHARACTER_NAME + 1];	/* ��ɫ���� */
	GUID_t		OwnerGUID;	/* ������GUID */
	eCheatActType	OPType;		/* �������� */
	MapID_t		MapID;		/* ����ID */
	uint32		Offset;		/* �����ƫ���� */
	float		PosX;		/* ��ɫ��ǰX���� */
	float		PosZ;		/* ��ɫ��ǰZ���� */
	int32		WorldID;	/* ������ID */

	/*
	 * �ƶ�ʱ�������X+Z������������������ʱ��ObiId ;
	 * ��½��֤�� 0:��������ģʽ��1���������ģʽ��2��ʱ�����ģʽ
	 */
	uint32		Param;

	CheatActLogRecordInfo()
	{
		clear();
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void clear(void)
	{
		memset(Account, 0, sizeof(Account));
		memset(CharName, 0, sizeof(CharName));
		OwnerGUID = INVALID_ID;
		OPType = eCheatAct_Unknow;
		MapID = INVALID_ID;
		Offset = -1;
		PosX = 0;
		PosZ = 0;
		Param = 0;
		WorldID = 0;
	}
};

struct ReturnToChildLogRecordInfo
{
	uint32	m_uHighSection;
	uint32	m_uLowSection;
	int32	m_nBaseStr;
	int32	m_nBaseCon;
	int32	m_nBaseDex;
	int32	m_nBaseInt;
	int32	m_nExtStr;
	int32	m_nExtCon;
	int32	m_nExtDex;
	int32	m_nExtInt;
	int32	m_nSkill[PET_MAX_SKILL_COUNT];

	ReturnToChildLogRecordInfo()
	{
		m_uHighSection = 0;
		m_uLowSection = 0;
		m_nBaseStr = 0;
		m_nBaseCon = 0;
		m_nBaseDex = 0;
		m_nBaseInt = 0;
		m_nExtStr = 0;
		m_nExtCon = 0;
		m_nExtDex = 0;
		m_nExtInt = 0;
		memset(m_nSkill, 0, sizeof(m_nSkill));
	}

	void Init(_HORSE_DB* data)
	{
		KCheck(data);

		m_uHighSection = data->m_GUID.m_uHighSection;
		m_uLowSection = data->m_GUID.m_uLowSection;

		m_nBaseStr= data->m_BaseAttrLevel1.m_pAttr[0];
		m_nBaseCon= data->m_BaseAttrLevel1.m_pAttr[1];
		m_nBaseDex= data->m_BaseAttrLevel1.m_pAttr[3];
		m_nBaseInt= data->m_BaseAttrLevel1.m_pAttr[2];

		m_nExtStr = data->m_iStrengthPerception;
		m_nExtCon = data->m_iConstitutionPerception;
		m_nExtDex = data->m_iSmartnessPerception;
		m_nExtInt = data->m_iMindPerception;
		for(int32 i = 0; i < PET_MAX_SKILL_COUNT; ++i)
		{
			m_nSkill[i] = data->m_SkillList[i].m_nSkillID;
		}
	}
};

//���＼����־
struct PetSkillLogRecordInfo
{
	uint32	m_uHighSection;
	uint32	m_uLowSection;
	int32	m_nBaseStr;
	int32	m_nBaseCon;
	int32	m_nBaseDex;
	int32	m_nBaseInt;
	int32	m_nExtStr;
	int32	m_nExtCon;
	int32	m_nExtDex;
	int32	m_nExtInt;
	int32	m_nSkill[PET_MAX_SKILL_COUNT];

	PetSkillLogRecordInfo()
	{
		m_uHighSection = 0;
		m_uLowSection = 0;
		m_nBaseStr = 0;
		m_nBaseCon = 0;
		m_nBaseDex = 0;
		m_nBaseInt = 0;
		m_nExtStr = 0;
		m_nExtCon = 0;
		m_nExtDex = 0;
		m_nExtInt = 0;
		memset(m_nSkill, 0, sizeof(m_nSkill));
	}

	void Init(const _HORSE_DB* data)
	{
		KCheck(data);

		m_uHighSection = data->m_GUID.m_uHighSection;
		m_uLowSection = data->m_GUID.m_uLowSection;

		m_nBaseStr= data->m_BaseAttrLevel1.m_pAttr[0];
		m_nBaseCon= data->m_BaseAttrLevel1.m_pAttr[1];
		m_nBaseDex= data->m_BaseAttrLevel1.m_pAttr[3];
		m_nBaseInt= data->m_BaseAttrLevel1.m_pAttr[2];

		m_nExtStr = data->m_iStrengthPerception;
		m_nExtCon = data->m_iConstitutionPerception;
		m_nExtDex = data->m_iSmartnessPerception;
		m_nExtInt = data->m_iMindPerception;
		for(int32 i = 0; i < PET_MAX_SKILL_COUNT; ++i)
		{
			m_nSkill[i] = data->m_SkillList[i].m_nSkillID;
		}
	}
};

struct IBInItemLogRecordInfo
{
	GUID_t		CharGUID;			/* �����ɫ,��Ʒ������ */
	char		Name[MAX_CHARACTER_NAME];	/* ��ɫ���� */
	SItemGuid	ItemGuid;			/* ��Ʒ��� */
	uint32		ItemType;			/* ��Ʒȫ�ֱ�� */
	uint32		OpType;			/* �������� */
	uint32		Count;			/* ���� */
	uint32		GoldCash;		/* �ֽ��� */
	uint32		TermTime;		/* ��Ч�� */
	MapID_t		MapID;			/* ����ID */
	int32		WorldID;		/* ������ID */

	IBInItemLogRecordInfo (void)
	{
		clear();
	}

	/*
	===============================================================================================================
	===============================================================================================================
	*/
	void clear(void)
	{
		CharGUID =  -1;
		Count = 1;
		ItemType = 0;
		TermTime = 0;
		GoldCash = 0;
		WorldID = 0;
		MapID = -1;
		OpType = eItemAct_Unknow;
		memset(Name, 0, sizeof(Name));
	}
};

struct IBOutItemLogRecordInfo
{
	GUID_t		CharGUID;			/* �����ɫ,��Ʒ������ */
	char		Name[MAX_CHARACTER_NAME];	/* ��ɫ���� */
	SItemGuid	ItemGuid;			/* ��Ʒ��� */
	uint32		ItemType;			/* ��Ʒȫ�ֱ�� */
	uint32		OpType;			/* �������� */
	uint32		Count;			/* ���� */
	uint32		GoldCash;		/* �ֽ��� */
	MapID_t		MapID;			/* ����ID */
	int32		WorldID;		/* ������ID */

	IBOutItemLogRecordInfo (void)
	{
		clear();
	}

	/*
	===============================================================================================================
	===============================================================================================================
	*/
	void clear(void)
	{
		CharGUID =  -1;
		Count = 1;
		ItemType = 0;
		OpType = eItemAct_Unknow;
		memset(Name, 0, sizeof(Name));
		GoldCash = 0;
		WorldID = 0;
		MapID = -1;
	}
};


struct GLStockTradeLogRecordInfo
{
	GUID_t			OwnerGUID;	/* ������GUID */
	GUID_t			OtherGUID;	/* ������һ��GUID */
	eStockActType	OPType;		/* �������� */
	uchar			TradeType;	/* �������� */
	int32			OwnerPrice;	/* �����߳��ۣ����� */
	int32			OtherPrice;	/* ������һ�����ۣ����� */
	int32			Gold;		/* ���׵��ֽ����� */
	uint32			CreateTime;	/* ����ʱ�� */
	uint32			DeleteTime;	/* ɾ��ʱ�� */

	GLStockTradeLogRecordInfo(void)
	{
		clear();
	}

	/*
	===============================================================================================================
	===============================================================================================================
	*/
	void clear(void)
	{
		OwnerGUID = INVALID_ID;
		OtherGUID = INVALID_ID;
		OPType = eStockAct_Unknow;
		TradeType = STOCK_TRADE_TYPE_BUY;
		OwnerPrice = 0;
		OtherPrice = 0;
		Gold = 0;
		CreateTime = -1;
		DeleteTime = -1;
	}
};

//�˻���¼LOG
struct MapStockAccLogRecordInfo
{
	GUID_t			OwnerGUID;	/* ������GUID */
	eStockAccActType OPType;	/* �������� */
	int32			TransGold;	/* ת�˵��ֽ� */
	int32			TransSiller;/* ת�˵����� */
	int32			StockGold;	/* �˻���� �ֽ� */
	int32			StockSiller;/* �˻���� ���� */
	MapID_t			MapID;		/* ����ID */
	int32			WorldID;	/* ������ID */

	MapStockAccLogRecordInfo()
	{
		clear();
	}

	/*
	===============================================================================================================
	===============================================================================================================
	*/
	void clear()
	{
		OwnerGUID = INVALID_ID;
		OPType = eStockAccAct_Unknow;
		TransGold = 0;
		TransSiller = 0;
		StockGold = 0;
		StockSiller = 0;
		MapID = -1;
		WorldID = 0;
	}
};

//�˻���¼LOG
struct GLStockAccLogRecordInfo
{
	GUID_t			OwnerGUID;	/* ������GUID */
	eStockAccActType OPType;	/* �������� */
	int32			TransGold;	/* ת�˵��ֽ� */
	int32			TransSiller;/* ת�˵����� */
	int32			StockGold;	/* �˻���� �ֽ� */
	int32			StockSiller;/* �˻���� ���� */

	GLStockAccLogRecordInfo()
	{
		clear();
	}

	/*
	===============================================================================================================
	===============================================================================================================
	*/
	void clear()
	{
		OwnerGUID = INVALID_ID;
		OPType = eStockAccAct_Unknow;
		TransGold = 0;
		TransSiller = 0;
		StockGold = 0;
		StockSiller = 0;
	}
};

// GL�������Log
struct GLGuildLogRecordInfo
{
	GuildID_t		m_GuildId;								//���ID
	char			m_szGuildName[MAX_GUILD_NAME_SIZE];		//�����
	eGuildActType	m_OpType;								//��������
	int32			m_nCount;								//�仯ֵ
	int32			m_nRemainCount;							//�仯���ֵ
	int32			m_nParam;								//������صĲ���
	int32			m_nScriptId;							//�ű�Id


	GLGuildLogRecordInfo (void)
	{
		clear();
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void clear(void)
	{
		m_GuildId = INVALID_GUILD_ID;
		memset( m_szGuildName, 0, MAX_GUILD_NAME_SIZE );
		m_OpType = eGuildAct_Unknow;
		m_nCount = 0;
		m_nRemainCount = 0;
		m_nParam = 0;
		m_nScriptId = -1;
	}
};

struct ZhuanJingLogRecordInfo
{
	GUID_t		CharGUID;	/* �����ɫ */
	eZhuanJingActType	OPType;		/* �������� */
	MapID_t		MapID;		/* ������� */
	float		XPos;		/* �¼�����λ�� */
	float		ZPos;
	int32		TotalPoint;
	int32		Profession[PROFESSION_NUMBER];
	int32		Reserve_param0;
	int32		Reserve_param1;
	int32		WorldID;	/* ������ID */


	ZhuanJingLogRecordInfo()
	{
		clear();
	}

	/*
	===============================================================================================================
	===============================================================================================================
	*/
	void clear(void)
	{
		CharGUID = INVALID_ID;
		OPType = eZhuanjingAct_Unknow;
		MapID = -1;
		XPos = 0.0f;
		ZPos = 0.0f;
		TotalPoint = 0;
		Reserve_param0 = 0;
		Reserve_param1 = 0;
		WorldID = 0;
		memset(Profession, 0, sizeof(Profession));
	}
};

#endif /* _RECORD_STRUCT_H_ */

/* ???? */
