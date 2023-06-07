#pragma once
#include "StructDB.h"
#include "data/struct/GameDataStructSkill.h"

struct SDataCharacter
{
	int32				m_nRaceID;			/* ���ݱ��е�ID */

	int32				m_nPortraitID;		/* ͷ��ID */
	String				m_strName;			/* ��ɫ�����֣��ӷ��������� */
	String				m_strUtf8Name;		/* ��ɫ��Utf8 ���� */
	String				m_strCountryTitle;	/* ��ǰ���ҳƺ� */
	String				m_strGuildTitle;	/* ��ǰ���ƺ� */
	String				m_strTitle;			/* ��ǰ�淨�ƺ� */
	String				m_strConsortName;	/* ��ż���� add by QL 081022 */
	BYTE				m_TitleType;		/* ��ǰ�ƺ����� */
	FLOAT				m_fHPPercent;		/* ����ֵ�ٷֱ� */
	FLOAT				m_fMPPercent;		/* ħ��ֵ�ٷֱ� */
	int32				m_nHP;				/* ������ */
	int32				m_nMaxHP;			/* ��������� */
	int32				m_nRage;			/* ŭ�� */
	int32				m_nMaxRage;			/* ���ŭ�� */
	FLOAT				m_fMoveSpeed;		/* �ƶ����ٶ� */
	SCampData			m_CampData;			/* ��ӪID */
	int32				m_nOwnerID;			/* ������ID */
	int32				m_nRelative;		/* ��Թ�ϵ��������Ƿ�ɱ��������Ƿ��������� */
	int32				m_nModelID;			/* ģ��ID */
	int32				m_nMountID;			/* ����ID */
	int32				m_nLevel;			/* �ȼ� */
	BOOL				m_bFightState;		/* ս��״̬ */
	int32				m_nStealthLevel;	/* ������ */
	BOOL				m_bSit;				/* ����״̬ */
	int32				m_nAIType;			/* AI���� */
	int32				m_nCountry;			/* ���� */
	int32				m_nAttachID;		/* ���󶨵�ObjID */
	int32				m_nGuild;			/* ����ID */
	int32				m_nGuildPosition;			/* �ڰ����е�ְλ */
	FLOAT				m_fSpeedRate;		/* �ı��ɫƵ����� */
	int32				m_nTargetId;		/* ѡ�е�Ŀ�� */
	BOOL				m_bVisibleState;	/* �Ƿ�ɼ� */
	FLOAT				m_fDir;				/* ���� */
	int32				m_nMoveLogicMode;	/* �ƶ�ģʽ */
	int32				m_nMoveActionMode;		/* �ƶ�ģʽ */
	int32				m_nTeamID;			/* ����ID */
	BOOL				m_bLimitMove;		/* �Ƿ����Ʋ����ƶ�,����� */
	BOOL				m_bLimitMove_2;		/* �����ƶ���ʶ���־�� */
	BOOL				m_bCanActionFlag1;	/* �������ޱ��1,���ڳ�Ĭ */
	BOOL				m_bCanActionFlag2;	/* �������ޱ��2,���ڲ��ɹ��� */
	BOOL				m_bAttachSetFlag;	/* �ж��Ƿ��Ѿ����ù������� */
	int32				m_nControlState;	/* ����״̬ */
	BOOL				m_bBusState;		/* �����ڳ�״̬ */
	FLOAT				m_fCharScale;		// �������ű���
	int32				m_nDefaultSkill;	// Ĭ�ϼ���
	SkillDataMap		m_theSkill;			/* �������� */
	/*
	 * ע��: ��ɾ������Ҫ�� _Init_AsCharacter() ��ʼ��!!! 
	 * ע��: ��ɾ������Ҫ�� _Init_AsCharacter() ��ʼ��!!! ;
	 * ע��: ��ɾ������Ҫ�� _Init_AsCharacter() ��ʼ��!!!
	 * Set �� Get ����ע���Լ�����������, ��Ҫ�� MUST_NOT_CHECK() ���!!! ;
	 */
};

/*
 -----------------------------------------------------------------------------------------------------------------------
    -->1. Character_NPC ����NPC ;
 -----------------------------------------------------------------------------------------------------------------------
 */
struct SDataNPC :
	public SDataCharacter
{
	int32 m_nWeaponID;	/* ����ID */
	int32 m_nAttachMemberID[DEF_BUS_MAX_PASSENGER_COUNT]; /* �˿�ID,����ר�� */

	/*
	 * ע��: ��ɾ������Ҫ�� _Init_AsNPC() ��ʼ��!!! 
	 * ע��: ��ɾ������Ҫ�� _Init_AsNPC() ��ʼ��!!! ;
	 * ע��: ��ɾ������Ҫ�� _Init_AsNPC() ��ʼ��!!!
	   Set �� Get ����ע���Լ�����������, ��Ҫ�� MUST_NOT_CHECK() ���!!! ;
	 */
};

/*
 -----------------------------------------------------------------------------------------------------------------------
    -->2. Character_PlayerOther ����������� ;
 -----------------------------------------------------------------------------------------------------------------------
 */
struct SDataPlayerOther :
	public SDataNPC
{
	int32				m_nProfession;						/* ְҵ 0[��ʿ] 1[����] 2[����] 3[��ǹ] 4[����] 5[��֪] */
	int32				m_nHairMeshID;						/* ͷ������ -> TABLE_CHARACTER_HAIR_GEO */
	int32				m_nFaceMeshID;						/* �������� -> TABLE_CHARACTER_HEAD_GEO( char_head.tab ) */
	uint32				m_uHairColor;						/* ͷ����ɫ */
	int32				m_nEquipVer;						/* ��ɫ��װ��״̬�汾�ţ����ںͷ�����ͬ�����ݵ����� */
	int32				m_nEquipmentID[HEQUIP_NUMBER];		/* װ����;
															* ����������ʾ */
	int32				m_nEquipmentGemID[HEQUIP_NUMBER];	/* װ����ʯ��;
															* ����������ʾ */
	_SUIT_SETTING		m_oChangeSuit[MAX_EQUIP_SUIT_NUM];	/* һ����װ���� */
	BOOL				m_bShowFashion;						/* �Ƿ���ʾʱװ */
	int32				m_nCurTitleIndex;					/* ��ǰʹ�õĳƺ����� */
	BOOL				m_bIsInStall;						/* �Ƿ��̯�� */
	String				m_strStallName;						/* ̯λ�� */
	uchar				m_StallMoneyType;					/* ̯λ��Ǯģʽ*/
	int32				m_nFamily;							/* ����ID */
	int32				m_nPKValue;							/* pkvalue */
	String				m_strProvince;						/* ʡ�� */
	String				m_strZone;							/* ���� */
	String				m_strGuildName;						/* ������� */
	String				m_strFamilyName;					/* �������� */
	BYTE				m_NameColor;						/* ����ʱ��������ɫ */
	int32				m_nMountStrApt;						/* ������������ */
	int32				m_nMountDexApt;						/* ������������ */
	int32				m_nMountIntApt;						/* ������������ */
	int32				m_nMountConApt;						/* ������������ */
	int32				m_nMountEra;						/* ������� */
	int32				m_nCurSuitId;						/* ��ǰ��װid */
	int32				m_nCurEquipSign;					/* ��ǰ���ĵļ��� */
	uint32				m_nCurStarSign;						/* ��ǰ������Ч�ļ��� */
	uint32				m_nCurSuitSign;						/* ��ǰ������װ */
	int32				nLeftWeaponVisual;					/* ʱװ������ʶ */
	int32				nRighttWeaponVisual;
	int32				nShoulderVisual;					/* ʱװ�������α�ʶ */
	int32				nHeadVisual;						/* ʱװͷ�����α�ʶ */
	int32				nKillCount;							/* ɱ���� */
	BOOL				m_bIsHideName;						/* �Ƿ�������״̬ */
	uint32				m_uInherenceExp;			/* �츳���� */
	uint32				m_uInherenceNextLevelExp;	/* �츳���� */
	uint32				m_uInherenceLevel;			/* �츳�ȼ� */

	/*
	 * ע��: ��ɾ������Ҫ�� _Init_AsPlayerOther() ��ʼ��!!! 
	 * ע��: ��ɾ������Ҫ�� _Init_AsPlayerOther() ��ʼ��!!! ;
	 * ע��: ��ɾ������Ҫ�� _Init_AsPlayerOther() ��ʼ��!!!
	   Set �� Get����ע���Լ�����������, ��Ҫ�� MUST_NOT_CHECK() ���!!! ;
	 */
};

/*
 * -->3. Character_PlayerMySelf ��������Լ� ;
 */
#define PLAYER_COIN_NUM 4							/* ��ұ��������������� */
class	KItem;
struct SDataPlayerMyself :
	public SDataPlayerOther
{
	int32					m_nMP;						/* ħ���� */
	int64_t					m_nExp;						/* ����ֵ */
	int64_t					m_nMoney[PLAYER_COIN_NUM];	/* ��ҽ�Ǯ */
	int32					m_nSilverCoin;

	int32					m_nStrikePoint;				/* ������ */
	int32					m_nVigor;					/* ����ֵ */
	int32					m_nMaxVigor;				/* ����ֵ���� */
	int32					m_nRegeneRate;
	int32					m_nEnergy;					/* ����ֵ */
	int32					m_nMaxEnergy;				/* ����ֵ���� */
	int32					m_nGoodBadValue;			/* �ƶ�ֵ */
	SHorseGuid				m_guidCurrentPet;			/* ��ǰ����GUID */

	/* �Ѿ������ϵ����� */
	int32					m_nSeriesPoint_1;			/* ϵ�� 1 */
	int32					m_nSeriesPoint_2;			/* ϵ�� 2 */
	int32					m_nSeriesPoint_3;			/* ϵ�� 3 */
	int32					m_nSkillPoint;

	/* һ��ս������ */
	int32					m_nSTR;						/* �⹦ */
	int32					m_nCON;						/* �� */
	int32					m_nINT;						/* ���� */
	int32					m_nDEX;						/* �ǻ� */
	int32					m_nPoint_Remain;			/* ʣ���������� */

	/* ����ս������ */
	int32					m_nAtt_Near;				/* ���� */
	int32					m_nDef_Near;				/* ���� */
	int32					m_nAtt_Far;					/* Զ�� */
	int32					m_nDef_Far;					/* Զ�� */

	int32					m_nAtt_Magic;				/* ħ�������� */
	int32					m_nDef_Magic;				/* ħ�������� */
	int32					m_nMaxMP;					/* ���ħ���� */
	int32					m_nHP_ReSpeed;				/* HP�ָ��ٶ� ��/�� */
	int32					m_nMP_ReSpeed;				/* MP�ָ��ٶ� ��/�� */
	int32					m_nRage_Respeed;			/* ŭ���ָ� */
	int32					m_nToughness;				/* ���� */
	int32					m_nHit;						/* ������ */
	int32					m_nMiss;					/* ������ */
	int32					m_nCritRate;				/* ������ */
	int32					m_nCritHurt;				/* �����˺� */
	float					m_nAttackSpeed;				/* �����ٶ� */

	int32					m_nAtt_Cold;				/* ������ */
	int32					m_nDef_Cold;				/* ������ */
	int32					m_nAtt_Fire;				/* �𹥻� */
	int32					m_nDef_Fire;				/* ����� */
	int32					m_nAtt_Light;				/* �繥�� */
	int32					m_nDef_Light;				/* ����� */
	int32					m_nAtt_Posion;				/* ������ */
	int32					m_nDef_Posion;				/* ������ */

	int32					m_nNear_Reduce;				/* ���̼��� */
	int32					m_nFar_Reduce;				/* Զ�̼��� */
	int32					m_nMagic_Reduce;			/* ħ������ */

	int32					m_nDread_Resist;			/* �־忹�� */
	int32					m_nComa_Resist;				/* ���Կ��� */
	int32					m_nHush_Resist;				/* ��Ĭ���� */
	int32					m_nUnarm_Resist;			/* ��е���� */
	int32					m_nAttackSpeed_Resist;		/* �����ٿ��� */
	int32					m_nSkillSpeed_Resist;		/* ��ʩ�ٿ��� */
	int32					m_nMoveReduce_Resist;		/* �����ٿ��� */


	int32					m_nPerCon;					/* �ﹱ */
	int32					m_nHonor;					/* ����ֵ */
	int32					m_RongYu;					/* ��͢���� */
	int32					m_ShengWang;				/* �������� */
	int32					m_WenCai;					/* �Ĳ� */

	int32					m_nHot;						/* ���� */
	uint32					m_uTiredTime;				/* ƣ��ʱ�� */
	
	uint32					m_nBattleHonour;			/* ս������ */
	USHORT					m_PVP2V2Level;				/* pvp2v2�������ȼ� */
	USHORT					m_PVP2V2Mark;				/* pvp2v2���������� */
	int32					m_PVP2V2Mark_WeekTotal;		/* pvp2v2���������ֱ����ܼ� */
	BYTE					m_byBankPetValidCt;			/* ������������ */
	int32					m_nMerit;					/* ��Ṧ��ֵ */
    uint32                  m_dwFeastScore;             /* ���ջ��� */

    //! ר��ʣ�����
    uint32                  m_uiDefendRemainPoints;
};
