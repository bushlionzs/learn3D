#ifndef _HUMAN_DB_INL_
#define _HUMAN_DB_INL_
#include "BaseTool.h"
#include "TabDefine_Map_Item.h"
#include "data/data_manager.h"
#include "server_settting.h"


void				PlayerArchive::Lock()
{
	N_SM_LOCK(SM_S_WRITE)
}

void				PlayerArchive::UnLock()
{
	N_SM_UNLOCK(SM_S_WRITE)
}

BOOL				PlayerArchive::IsFirstEnterGame()
{
	return m_dbPlayer->m_bFirstEnterScence;
}

void				PlayerArchive::ClearFirstEnterGame()
{
	m_dbPlayer->m_bFirstEnterScence = FALSE;
	SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_FIRSTLOGIN);
}

GUID_t				PlayerArchive::GetGUID() const
{
	return m_dbPlayer->m_GUID ; 
}
void				PlayerArchive::SetGUID( GUID_t guid )
{ 
	m_dbPlayer->m_GUID = guid ; 
	SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_GUID);
} 

int32					PlayerArchive::GetPortraitID() const
{
	return m_dbPlayer->m_PortraitID ; 
}

void				PlayerArchive::SetPortraitID( int32 nID )
{
	m_dbPlayer->m_PortraitID = nID ; 
	SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_PORTRAITID);
}

const	char*		PlayerArchive::GetName()const
{
	return m_dbPlayer->m_Name ;
} 
uchar				PlayerArchive::GetSex()
{ 
	return m_dbPlayer->m_Sex ; 
} 

int32					PlayerArchive::GetHP()
{
	return m_dbPlayer->m_HP ; 
} 
void				PlayerArchive::SetHP( int32 hp )
{
	m_dbPlayer->m_HP = hp ; 
	SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_HP);
} 

int32					PlayerArchive::GetMP()
{
	return m_dbPlayer->m_MP ; 
} 
void				PlayerArchive::SetMP( int32 mp )
{
	m_dbPlayer->m_MP = mp ; 
	SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_MP);
} 

int32					PlayerArchive::Get_Property_StrikePoint(void) 
{
	return m_dbPlayer->m_StrikePoint;
}
void				PlayerArchive::Set_Property_StrikePoint(int32 nStrikePoint) 
{
	m_dbPlayer->m_StrikePoint = nStrikePoint;
	SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_STRIKEPOINT);
}

int32					PlayerArchive::Get_Property_Vigor(void)
{
	return m_dbPlayer->m_Vigor;
}
void				PlayerArchive::Set_Property_Vigor(int32 nVigor)
{
	m_dbPlayer->m_Vigor = nVigor;
	SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_VIGOR);
}

int32					PlayerArchive::Get_Property_MaxVigor(void)
{
	return m_dbPlayer->m_MaxVigor;
}
void				PlayerArchive::Set_Property_MaxVigor(int32 nMaxVigor)
{
	m_dbPlayer->m_MaxVigor = nMaxVigor;
	SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_MAX_VIGOR);
}

int32					PlayerArchive::Get_Property_VigorRegeneRate(void)
{
	return m_dbPlayer->m_VigorRegeneRate;
}
void				PlayerArchive::Set_Property_VigorRegeneRate(int32 nRate)
{
	m_dbPlayer->m_VigorRegeneRate = nRate;
	SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_VIGOR_REGENE_RATE);
}

int32					PlayerArchive::Get_Property_Energy(void)
{
	return m_dbPlayer->m_Energy;
}
void				PlayerArchive::Set_Property_Energy(int32 nEnergy)
{
	m_dbPlayer->m_Energy = nEnergy;
	SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_ENERGY);
}

int32					PlayerArchive::Get_Property_MaxEnergy(void)
{
	return m_dbPlayer->m_MaxEnergy;
}
void				PlayerArchive::Set_Property_MaxEnergy(int32 nMaxEnergy)
{
	m_dbPlayer->m_MaxEnergy = nMaxEnergy;
	SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_MAX_ENERGY);
}

int32					PlayerArchive::Get_Property_EnergyRegeneRate(void)
{
	return m_dbPlayer->m_EnergyRegeneRate;
}
void				PlayerArchive::Set_Property_EnergyRegeneRate(int32 nRate)
{
	m_dbPlayer->m_EnergyRegeneRate = nRate;
	SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_ENERGY_REGENE_RATE);
}

int32 				PlayerArchive::Get_Property_Rage( void )
{ 
	return m_dbPlayer->m_Rage; 
}
void				PlayerArchive::Set_Property_Rage( int32 nRage )
{
	m_dbPlayer->m_Rage = nRage; 
	SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_RAGE);
}

uchar				PlayerArchive::GetLevel()
{
	return m_dbPlayer->m_Level ; 
} 

void				PlayerArchive::SetLevel( uchar level )
{ 
	m_dbPlayer->m_Level = level ; 
	SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_LEVEL);
}

int32					PlayerArchive::GetPKValue( void )const
{
	return m_dbPlayer->m_nPKValue;
}

void				PlayerArchive::SetPKValue( int32 nValue )
{
	m_dbPlayer->m_nPKValue = nValue;
	SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_PKVALUE);
}

int32					PlayerArchive::GetLastChgPKModeTime( void ) const
{
	return m_dbPlayer->m_nLastChgPKModeTime;
}

void				PlayerArchive::SetLastChgPKModeTime( int32 nValue )
{
	m_dbPlayer->m_nLastChgPKModeTime = nValue;
	SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_LAST_CHGPKMODE_TIME);
}

SHorseGuid			PlayerArchive::GetCurrentPetGUID( void )const
{
	return m_dbPlayer->m_guidCurrentPet;
}

void				PlayerArchive::SetCurrentPetGUID(SHorseGuid guid )
{
	m_dbPlayer->m_guidCurrentPet = guid;
	SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_CURRENTPET);
}

uint64				PlayerArchive::GetExp()
{
	return m_dbPlayer->m_Exp ; 
} 
void				PlayerArchive::SetExp( uint64 exp )
{
	m_dbPlayer->m_Exp = exp ; 
	SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_EXP);
} 

int32					PlayerArchive::GetCountry( )
{
	return m_dbPlayer->m_nCountry;
}

void				PlayerArchive::SetCountry( int32 nCountry )
{
	m_dbPlayer->m_nCountry = nCountry;
	SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_COUNTRY);
}

uint16				PlayerArchive::GetWenCai( )
{
	return m_dbPlayer->m_nWenCai;
}

void				PlayerArchive::SetWenCai( uint16 nWenCai )
{
	if( nWenCai > 32768)
		nWenCai = 32768 ;

	m_dbPlayer->m_nWenCai = nWenCai;
	SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_WENCAI);
}

int32				PlayerArchive::GetRongYu( )
{
	return m_dbPlayer->m_nRongYu;
}

void				PlayerArchive::SetRongYu( int32 nRongYu )
{
	if( nRongYu > MAX_SHENGWANG_COUNT)
		nRongYu = MAX_SHENGWANG_COUNT ;

	m_dbPlayer->m_nRongYu = nRongYu;
	SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_RONGYU);
}

int32				PlayerArchive::GetShengWang( )
{
	return m_dbPlayer->m_nShengWang;
}

void				PlayerArchive::SetShengWang( int32 nShengWang )
{
	if( nShengWang > MAX_SHENGWANG_COUNT)
		nShengWang = MAX_SHENGWANG_COUNT ;

	m_dbPlayer->m_nShengWang = nShengWang;
	SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_SHENGWANG);
}

int32				PlayerArchive::GetHotValue( )
{
	return m_dbPlayer->m_nHotValue;
}

void				PlayerArchive::SetHotValue( int32 nHotValue )
{
	if( nHotValue > MAX_HOT_VALUE)
		nHotValue = MAX_HOT_VALUE ;
	if( nHotValue < 0)
		nHotValue = 0;
	m_dbPlayer->m_nHotValue = nHotValue;
	SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_HOTVALUE);
}

int32					PlayerArchive::GetProfession( )
{ 
	return m_dbPlayer->m_nProfession ; 
} 
void				PlayerArchive::SetProfession( int32 Profession )
{
	m_dbPlayer->m_nProfession = Profession ; 
	SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_PROFESSION);
} 

int32				PlayerArchive::GetSiller()
{	
	return m_dbPlayer->m_Siller;
}
void				PlayerArchive::SetSiller(int32 siller)
{
	if(siller>MAX_MONEY_COUNT)
		siller = MAX_MONEY_COUNT;
	if(siller<0)
		siller = 0;
	m_dbPlayer->m_Siller	=	siller;
	SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_SILLER);
}

int32				PlayerArchive::GetCharGold()
{
    return m_dbPlayer->m_Gold;
}

void				PlayerArchive::SetCharGold(int32 gold)
{
	if(gold>MAX_MONEY_COUNT)
		gold = MAX_MONEY_COUNT;
	if(gold<0)
		gold = 0;
    m_dbPlayer->m_Gold   =   gold;
	SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_GOLD);
}
int32				PlayerArchive::GetBindSiller()
{
    return m_dbPlayer->m_BindSiller;
}

void				PlayerArchive::SetBindSiller(int32 bindSiller)
{
	if(bindSiller>MAX_MONEY_COUNT)
		bindSiller = MAX_MONEY_COUNT;
	if(bindSiller<0)
		bindSiller = 0;
    m_dbPlayer->m_BindSiller =   bindSiller;
	SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_BINDSILLER);
}
int32				PlayerArchive::GetBindGold()
{
    return m_dbPlayer->m_BindGold;
}

void				PlayerArchive::SetBindGold(int32 bindGold)
{
	if(bindGold>MAX_MONEY_COUNT)
		bindGold = MAX_MONEY_COUNT;
	if(bindGold<0)
		bindGold = 0;
    m_dbPlayer->m_BindGold =   bindGold;
	SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_BINDGOLD);
}

uchar				PlayerArchive::GetSillerMode()
{
	uchar bOffset = m_dbPlayer->m_MoneyMode&0x0f;
	switch(bOffset)
	{
	case MONEY_SILLERCARD:
		{
			return SILLER_CARD;
		}
		break;
	case MONEY_SILLERCASH:
		{
			return SILLER_CASH;
		}
		break;
	}
	SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_MONEYMODE);
    return SILLER_INVALID;
}

void				PlayerArchive::SetSillerMode(uchar SillerMode)
{
	uchar bOffset = m_dbPlayer->m_MoneyMode&0xf0;
	switch(SillerMode)
	{
	case SILLER_CASH:
		{
			bOffset = MONEY_SILLERCASH|bOffset;
		}
		break;
	case SILLER_CARD:
		{
			bOffset = MONEY_SILLERCARD|bOffset;
		}
		break;

	}
    m_dbPlayer->m_MoneyMode  =  bOffset;
	SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_MONEYMODE);
}

uchar				PlayerArchive::GetGoldMode()
{
   uchar bOffset = m_dbPlayer->m_MoneyMode&0xf0;
	switch(bOffset)
	{
	case MONEY_GOLDCARD:
		{
			return GOLD_CARD;
		}
		break;
	case MONEY_GOLDCASH:
		{
			return GOLD_CASH;
		}
		break;
	}
    return GOLD_INVALID;
}

void				PlayerArchive::SetGoldMode(uchar goldMode)
{
	uchar bOffset = m_dbPlayer->m_MoneyMode&0x0f;
	switch(goldMode)
	{
	case GOLD_CARD:
		{
			bOffset = MONEY_GOLDCARD|bOffset;
		}
		break;
	case GOLD_CASH:
		{
			bOffset = MONEY_GOLDCASH|bOffset;
		}
		break;
	}
    m_dbPlayer->m_MoneyMode  =  bOffset;
	SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_MONEYMODE);
}

int32					PlayerArchive::Get_Property_GoodBadValue()
{
	if (m_dbPlayer->m_nGoodBadValue == -1)
	{
		m_dbPlayer->m_nGoodBadValue = 0;
	}
	return m_dbPlayer->m_nGoodBadValue;
}

int32					PlayerArchive::Set_Property_GoodBadValue(int32 nValue)
{
	m_dbPlayer->m_nGoodBadValue = nValue;
	SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_GOODBAD);
	return m_dbPlayer->m_nGoodBadValue;
}


const uchar			PlayerArchive::GetPwdType()
{
	return m_dbPlayer->m_uPwdFlag;
}

void				PlayerArchive::SetPwdType(uchar pwdType)
{
	 m_dbPlayer->m_uPwdFlag = pwdType;
	 SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_PWD_TYPE);
}

const char*			PlayerArchive::GetPasswd()
{
	return m_dbPlayer->m_Passwd;
}

void				PlayerArchive::SetPasswd( const char* szPasswd )
{
	strncpy( m_dbPlayer->m_Passwd, szPasswd, MAX_PWD - 1 );
	SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_PASSWORD);
}

void				PlayerArchive::DelPasswd()
{
	memset(m_dbPlayer->m_Passwd, 0, MAX_PWD );
	SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_PASSWORD);
}

uint32				PlayerArchive::GetPasswdDeleteTime()
{
	return m_dbPlayer->m_uPwdDelTime;
}

void				PlayerArchive::SetPasswdDeleteTime( uint32 uTime )
{
	m_dbPlayer->m_uPwdDelTime = uTime;
	SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_PWDDELTIME);
}

uchar				PlayerArchive::GetLastProtectTime()
{
	return m_dbPlayer->m_cLastProtectTime;
}

void				PlayerArchive::SetLastProtectTime( uchar uTime )
{
	m_dbPlayer->m_cLastProtectTime = uTime;
	SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_LASTPROTECTIME);
}

uchar				PlayerArchive::GetProtectTime()
{
	return m_dbPlayer->m_cProtectTime;
}

void				PlayerArchive::SetProtectTime( uchar uTime )
{
	m_dbPlayer->m_cProtectTime = uTime;
	SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_PROTECTIME);
}

uint32				PlayerArchive::GetProtectDeleteTime()
{
	return m_dbPlayer->m_uProtectDelTime;
}

void				PlayerArchive::SetProtectDeleteTime( uint32 uTime )
{
	m_dbPlayer->m_uProtectDelTime = uTime;
	SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_PROTECDELTIME);
}

uint32				PlayerArchive::Get_Property_HairColor(void)const
{
	return m_dbPlayer->m_HairColor;
}

void				PlayerArchive::SetHairColor(uint32 uColor)
{
	m_dbPlayer->m_HairColor = uColor;
	SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_HAIR_COLOR);
}

uchar				PlayerArchive::GetFaceColor(void)const
{
	return m_dbPlayer->m_FaceColor;
}

void				PlayerArchive::SetFaceColor(uchar byColor)
{
	m_dbPlayer->m_FaceColor = byColor;
	SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_FACE_COLOR);
}

uchar				PlayerArchive::Get_Property_HairModel(void)const
{
	return m_dbPlayer->m_HairModel;
}

void				PlayerArchive::SetHairModel(uchar byModel)
{
	m_dbPlayer->m_HairModel = byModel;
	SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_HAIR_MODEL);
}

uchar				PlayerArchive::Get_Property_FaceModel(void)const
{
	return m_dbPlayer->m_FaceModel;
}

void				PlayerArchive::SetFaceModel(uchar byModel)
{
	m_dbPlayer->m_FaceModel = byModel;
	SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_FACE_MODEL);
}

inline	void		PlayerArchive::SetSoulID(int32 nSoulID)
{
	m_dbPlayer->m_SoulID = nSoulID;
	SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_SOULID);
}

inline	int32			PlayerArchive::GetSoulID()
{
	return m_dbPlayer->m_SoulID;
}

inline	void		PlayerArchive::SetGemAff(uint32 nGemAff)
{
	m_dbPlayer->m_GemAff = nGemAff;
	SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_GEMATT);
}

inline	uint32			PlayerArchive::GetGemAff()
{
	return m_dbPlayer->m_GemAff;
}

inline	void		PlayerArchive::SetSetSuit(uint32 nSetSuit)
{
	m_dbPlayer->m_SetSuit = nSetSuit;
	SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_SETSUIT);
}

inline	uint32			PlayerArchive::GetSetSuit()
{
	return m_dbPlayer->m_SetSuit;
}

inline	void		PlayerArchive::SetLevelAff(uint32 nLevelAff)
{
	m_dbPlayer->m_LevelAff = nLevelAff;
	SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_LEVELATT);
}

inline	uint32			PlayerArchive::GetLevelAff()
{
	return m_dbPlayer->m_LevelAff;
}

uint32				PlayerArchive::GetEquipID(PLAYER_EQUIP	equipPoint)
{
	return m_dbEquip->m_pItem[equipPoint].m_ItemIndex;
}

uint32				PlayerArchive::GetEquipLevel(PLAYER_EQUIP	equipPoint)
{
	return m_dbEquip->m_pItem[equipPoint].GetEquipData()->m_NeedLevel;
}

int32					PlayerArchive::GetArchiveAttrLvl1(PLAYER_PROPERTY_LEVEL1 enAttrType)              
{
	return	 m_dbPlayer->m_BaseAttrLevel1.Get(enAttrType) ;
}
void				PlayerArchive::SetArchiveAttrLvl1(PLAYER_PROPERTY_LEVEL1 enAttrType,int32 iValue)	
{
		m_dbPlayer->m_BaseAttrLevel1.Set(enAttrType,iValue) ;
		SetArchiveEnumPropertyDirty((PLAYER_PROPERTY_ARCHIVE)(CPROPERTY_ARCHIVE_STR+enAttrType));
}
int32					PlayerArchive::GetRemainPoints()
{
	return m_dbPlayer->m_Level1Points;
}	

int32					PlayerArchive::GetRemainSkillPoints()
{
	return m_dbPlayer->m_RemainSkillPoints;
}	

int32					PlayerArchive::Get_S_SkillPoints(int32 nS)
{
	KCheck((COMMON_S)nS<COMMON_S_NUMBER);
	return m_dbPlayer->m_S_SkillPoints[nS];
}	

void				PlayerArchive::SetDBRemainPoints(int32 Point)
{ 
	m_dbPlayer->m_Level1Points=Point;
	SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_REMAINPOINT);
}

void               PlayerArchive::SetDBRemainSkillPoints(int32 Point)
{ 
	m_dbPlayer->m_RemainSkillPoints=Point;
	SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_REMAINSKILLPOINT);
}

void				PlayerArchive::SetDB_S_SkillPoints(int32 nS, int32 Point)
{ 
	KCheck((COMMON_S)nS<COMMON_S_NUMBER);
	m_dbPlayer->m_S_SkillPoints[nS]=Point;
	SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_REMAINSKILLPOINT);
}

void				PlayerArchive::SetMonsterPetAttr( int32 iIndex, _Monster_Pet_DB_Struct* pMonsterPet )
{
	
	KCheck( iIndex>=0 && iIndex<MAX_MONSTER_PET_TAKE );
	m_dbMonsterPet->m_aMonsterPet[iIndex] = *pMonsterPet;
}

const SCampData *PlayerArchive::GetDBCampData(void)const
{
	return &(m_dbPlayer->m_CampData);
}
void				PlayerArchive::SetDBCampData(const SCampData *pCampData)
{
	m_dbPlayer->m_CampData	=	*pCampData;
	SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_CAMP);
}
MapID_t			PlayerArchive::GetDBStartScene( )
{
	return		m_dbPlayer->m_StartScene ;
}
void				PlayerArchive::SetDBStartScene(MapID_t	sceneID)
{
	m_dbPlayer->m_StartScene	=	sceneID;
	SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_AT_SCENE);
}
MapID_t			PlayerArchive::GetDBBakScene( )
{
	return		m_dbPlayer->m_BakScene ;
}
void				PlayerArchive::SetDBBakScene(MapID_t	sceneID)
{
	m_dbPlayer->m_BakScene	=	sceneID;
	SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_BK_SCENE);
}
MapID_t			PlayerArchive::GetDBNextScene()
{
	return		m_dbPlayer->m_NextScene;
}
void				PlayerArchive::SetDBNextScene(MapID_t	sceneID)
{
	m_dbPlayer->m_NextScene	=	sceneID;
	SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_NEXT_SCENE);	
}


const STitle*       PlayerArchive::GetTitleInfo() const
{
    return &m_dbPlayer->m_Titles;
}

const char*       PlayerArchive::GetTitleNameByID( int32 iTitleID, int32 iSex ) 
{
    return NULL;
}

BOOL                PlayerArchive::UpdateTitleTime( uchar& titleId, uchar& comId, int32& buffId1, int32& buffId2 )
{
    for (int32 i=0; i<MAX_TITLE_SIZE; ++i)
    {
        if (m_dbPlayer->m_Titles.m_TitleArray[i].m_TitleID != INVALID_TITLE_ID)
        {
            int32 iTime = DataManager::GetSingletonPtr()->getTitleInfo().m_TableInfo[i].m_uTime;
            if (iTime > 0)
            {

                if ((uint32)GET_TIME().GetCTime() >= m_dbPlayer->m_Titles.m_TitleArray[i].m_uTime) 
                {
					titleId = i;
                    RemoveTitle(i, comId, buffId1, buffId2);
					
                    return TRUE;
                }
            }
        }
    }

    return FALSE;
}

void                PlayerArchive::AddTitle(int32 iTitleID, int32 &BuffID1, int32 &BuffID2, uchar &ComId )
{
    m_dbPlayer->m_Titles.m_TitleArray[iTitleID].m_TitleID   = iTitleID;
    
    
    
   
	BuffID1 = DataManager::GetSingletonPtr()->getTitleInfo().m_TableInfo[iTitleID].m_iBuffID;


    uint32 uTime = DataManager::GetSingletonPtr()->getTitleInfo().m_TableInfo[iTitleID].m_uTime;
    if (uTime > 0)
    {

        m_dbPlayer->m_Titles.m_TitleArray[iTitleID].m_uTime  = (uint32)uTime * 60 + (uint32)GET_TIME().GetCTime();

    }

    
	int32 iSuitID = DataManager::GetSingletonPtr()->getTitleInfo().m_TableInfo[iTitleID].m_iSuitID;

    BOOL bSuitable = TRUE;
	int32 nInvalidCount = 0;
    if (iSuitID != INVALID_TITLE_ID)
    {
        int32 comTitleID = DataManager::GetSingletonPtr()->getTitleCombination().m_TableCombination[iSuitID].m_comTitleID;

        
        for (int32 i=0; i<MAX_TITLE_COMBINATION; ++i)
        {
            int32 part = DataManager::GetSingletonPtr()->getTitleCombination().m_TableCombination[iSuitID].m_arPart[i];

            KCheck(part < MAX_TITLE_SIZE);
            if (part == INVALID_TITLE_ID)
                continue;

            if (m_dbPlayer->m_Titles.m_TitleArray[part].m_TitleID == INVALID_TITLE_ID)
            {
                bSuitable = FALSE;
                break;
            }
			else
			{
				++nInvalidCount;
			}
        }

		if ( nInvalidCount == 0 )
		{
			bSuitable = FALSE;

		}

        if (bSuitable)
        {
			if ( m_dbPlayer->m_Titles.m_TitleArray[comTitleID].m_TitleID != INVALID_TITLE_ID )
				return;

            int32 iNewTitle = DataManager::GetSingletonPtr()->getTitleCombination().m_TableCombination[iSuitID].m_comTitleID;
            m_dbPlayer->m_Titles.m_TitleArray[comTitleID].m_TitleID   = DataManager::GetSingletonPtr()->getTitleInfo().m_TableInfo[iNewTitle].m_TitleID;
           
            m_dbPlayer->m_Titles.m_TitleArray[comTitleID].m_uTime      = DataManager::GetSingletonPtr()->getTitleInfo().m_TableInfo[iNewTitle].m_uTime;
           
           
            BuffID2 = DataManager::GetSingletonPtr()->getTitleInfo().m_TableInfo[comTitleID].m_iBuffID;
			ComId = (uchar)comTitleID;
        }
    }
	SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_TITLEINFO);
}

int32			   PlayerArchive::SetCurCountryTitle( int32 iTitleID, int32 &BuffID1, int32 &BuffID2, uchar &ComId )
{
	KCheckEx(iTitleID < MAX_TITLE_SIZE && iTitleID >=0 ,"国家称号ID越界");
	
	if (INVALID_TITLE_ID == m_dbPlayer->m_Titles.m_TitleArray[iTitleID].m_TitleID)
	{
		AddTitle(iTitleID, BuffID1, BuffID2, ComId);
		m_dbPlayer->m_Titles.m_CurCountryTitle = iTitleID;
		SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_TITLEINFO);
		return UPDATE_TITLE_ADD;
	}
	m_dbPlayer->m_Titles.m_CurCountryTitle = iTitleID;

	SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_TITLEINFO);
	return UPDATE_TITLE_NO_CHANGE;
}

int32                PlayerArchive::SetCurGuildTitle(int32 iTitleID, int32 &BuffID1, int32 &BuffID2, uchar &ComId )
{
    KCheckEx(iTitleID < MAX_TITLE_SIZE && iTitleID >=0 ,"帮会称号ID越界");
    
    if (INVALID_TITLE_ID == m_dbPlayer->m_Titles.m_TitleArray[iTitleID].m_TitleID)
    {
        AddTitle(iTitleID, BuffID1, BuffID2, ComId);
		m_dbPlayer->m_Titles.m_CurGuildTitle = iTitleID;
		SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_TITLEINFO);
		return UPDATE_TITLE_ADD;
    }
    m_dbPlayer->m_Titles.m_CurGuildTitle = iTitleID;
    SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_TITLEINFO);
	return UPDATE_TITLE_NO_CHANGE;
}

int32                PlayerArchive::SetCurNormalTitle(int32 iTitleID, int32 &BuffID1, int32 &BuffID2, uchar &ComId, int32 nCommand )
{
    KCheckEx(iTitleID < MAX_TITLE_SIZE && iTitleID >=0, "功能称号ID越界");
    
    if (INVALID_TITLE_ID == m_dbPlayer->m_Titles.m_TitleArray[iTitleID].m_TitleID)
    {
        AddTitle(iTitleID, BuffID1, BuffID2, ComId);
		m_dbPlayer->m_Titles.m_CurNormalTitle = iTitleID;
		SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_TITLEINFO);
		return UPDATE_TITLE_ADD;

    }
	else
	{
		if ( UPDATE_TITLE_ADD == nCommand )
		{
			uint32 uTime = DataManager::GetSingletonPtr()->getTitleInfo().m_TableInfo[iTitleID].m_uTime;
			if (uTime > 0)
			{

				m_dbPlayer->m_Titles.m_TitleArray[iTitleID].m_uTime  = (uint32)uTime * 60 + (uint32)GET_TIME().GetCTime();

			}

			m_dbPlayer->m_Titles.m_CurNormalTitle = iTitleID;
			BuffID1 = DataManager::GetSingletonPtr()->getTitleInfo().m_TableInfo[iTitleID].m_iBuffID;
			SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_TITLEINFO);
			return UPDATE_TITLE_TIME;
		}
		else
		{
			m_dbPlayer->m_Titles.m_CurNormalTitle = iTitleID;
			BuffID1 = DataManager::GetSingletonPtr()->getTitleInfo().m_TableInfo[iTitleID].m_iBuffID;
			SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_TITLEINFO);
			return UPDATE_TITLE_NO_CHANGE;
		}

	}

}

uchar			    PlayerArchive::GetCurCountryTitle()
{
    return m_dbPlayer->m_Titles.m_CurCountryTitle;
}

uchar                PlayerArchive::GetCurGuildTitle()
{
    return m_dbPlayer->m_Titles.m_CurGuildTitle;
}

uchar                 PlayerArchive::GetCurNormalTitle()
{
    return m_dbPlayer->m_Titles.m_CurNormalTitle;
}

BOOL				PlayerArchive::IsHaveTitle(int32 iTitleID)
{
	if( INVALID_ID == iTitleID || INVALID_TITLE_ID == iTitleID ) return TRUE;
	for(int32 i = 0; i < MAX_TITLE_SIZE; ++i)
	{
		if( m_dbPlayer->m_Titles.m_TitleArray[i].m_TitleID == iTitleID )
			return TRUE;
	}
	return FALSE;
	
}

int32                 PlayerArchive::RemoveTitle(int32 iTitleID, uchar& comId, int32& buffId1, int32& buffId2)
{

    if (GetCurCountryTitle() == iTitleID )
    {
        
		m_dbPlayer->m_Titles.m_CurCountryTitle = INVALID_TITLE_ID;
		SetCountryTitleName("", 0);
    }

    if (GetCurGuildTitle() == iTitleID )
    {
        
		m_dbPlayer->m_Titles.m_CurGuildTitle = INVALID_TITLE_ID;
		SetGuildTitleName("", 0);
    }

    if (GetCurNormalTitle() == iTitleID )
    {
        
		m_dbPlayer->m_Titles.m_CurNormalTitle = INVALID_TITLE_ID;
		SetNormalTitleName("", 0);
    }

    m_dbPlayer->m_Titles.m_TitleArray[iTitleID].m_TitleID   = INVALID_TITLE_ID;
    m_dbPlayer->m_Titles.m_TitleArray[iTitleID].m_uTime      = 0;
	buffId1 = DataManager::GetSingletonPtr()->getTitleInfo().m_TableInfo[iTitleID].m_iBuffID;

	
	int32 iSuitID = DataManager::GetSingletonPtr()->getTitleInfo().m_TableInfo[iTitleID].m_iSuitID;

	if ( iSuitID != INVALID_TITLE_ID )
	{
		int32 newTitle = DataManager::GetSingletonPtr()->getTitleCombination().m_TableCombination[iSuitID].m_comTitleID;

		if ( m_dbPlayer->m_Titles.m_TitleArray[newTitle].m_TitleID   != INVALID_TITLE_ID )
		{
			comId = newTitle;
			m_dbPlayer->m_Titles.m_TitleArray[newTitle].m_TitleID   = INVALID_TITLE_ID;
			m_dbPlayer->m_Titles.m_TitleArray[newTitle].m_uTime      = 0;
			buffId2 = DataManager::GetSingletonPtr()->getTitleInfo().m_TableInfo[newTitle].m_iBuffID;

			if ( GetCurCountryTitle() == newTitle )
			{
				m_dbPlayer->m_Titles.m_CurCountryTitle = INVALID_TITLE_ID;
				SetCountryTitleName("", 0);
			}

			if (GetCurGuildTitle() == newTitle )
			{
				
				m_dbPlayer->m_Titles.m_CurGuildTitle = INVALID_TITLE_ID;
				SetGuildTitleName("", 0);
			}

			if (GetCurNormalTitle() == newTitle )
			{
				
				m_dbPlayer->m_Titles.m_CurNormalTitle = INVALID_TITLE_ID;
				SetNormalTitleName("", 0);
			}

		}

	}

	SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_TITLEINFO);

	return 0;
}

void                PlayerArchive::SetOfficalTitleName(const char *pszTitle, int32 iSize)
{
    KCheck(iSize<MAX_NICK_NAME);
    memset(m_dbPlayer->m_Titles.m_szOfficialTitleName, 0, MAX_NICK_NAME);
    memcpy(m_dbPlayer->m_Titles.m_szOfficialTitleName, pszTitle, iSize);

    SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_TITLEINFO);
}

const char*         PlayerArchive::GetOfficalTitleName() const
{
    return m_dbPlayer->m_Titles.m_szOfficialTitleName;
}

void                PlayerArchive::SetCountryTitleName(const char *pszTitle, int32 iSize)
{
    KCheck(iSize<MAX_NICK_NAME);
    memset(m_dbPlayer->m_Titles.m_szCurCountryTitle, 0, MAX_NICK_NAME);
    memcpy(m_dbPlayer->m_Titles.m_szCurCountryTitle, pszTitle, iSize);

    SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_TITLEINFO);
}

const char*         PlayerArchive::GetCountryTitleName() const
{
    return m_dbPlayer->m_Titles.m_szCurCountryTitle;
}

void                PlayerArchive::SetGuildTitleName(const char *pszTitle, int32 iSize)
{
    KCheck(iSize<MAX_NICK_NAME);
    memset(m_dbPlayer->m_Titles.m_szCurGuildTitle, 0, MAX_NICK_NAME);
    memcpy(m_dbPlayer->m_Titles.m_szCurGuildTitle, pszTitle, iSize);

    SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_TITLEINFO);
}

const char*         PlayerArchive::GetGuildTitleName() const
{
    return m_dbPlayer->m_Titles.m_szCurGuildTitle;
}

void                PlayerArchive::SetNormalTitleName(const char *pszTitle, int32 iSize)
{
    KCheck(iSize<MAX_NICK_NAME);
    memset(m_dbPlayer->m_Titles.m_szCurNormalTitle, 0, MAX_NICK_NAME);
    memcpy(m_dbPlayer->m_Titles.m_szCurNormalTitle, pszTitle, iSize);

    SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_TITLEINFO);
}

const char*         PlayerArchive::GetNormalTitleName() const
{
    return m_dbPlayer->m_Titles.m_szCurNormalTitle;
}


const int32			PlayerArchive::GetBankItemCount( ) const
{
	return m_dbBank->m_Count;
}
const SItem*		PlayerArchive::GetBankItem( const int32 bankindex ) const
{
	KCheck(bankindex<MAX_BANK_SIZE);
	return &m_dbBank->m_pItem[bankindex];
}

const int32			PlayerArchive::GetBankEndIndex( ) const
{
	return m_dbBank->m_CurEndIndex;
}
void				PlayerArchive::SetBankEndIndex( const int32 bankindex )
{
	m_dbBank->m_CurEndIndex = bankindex;
	SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_BANK_OFFSIZE);
}
const int32			PlayerArchive::GetBankMoney( ) const
{
	return m_dbBank->m_Money;
}
void				PlayerArchive::SetBankMoney( const int32 money )
{
	m_dbBank->m_Money = money;
	SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_BANK_MONEY);
}

const int32			PlayerArchive::GetBankSize( ) const
{
    GetBankEndIndex();
}

void				PlayerArchive::ExpandBankSize(uint32 uBanksize)
{
    int32 nSize = uBanksize+GetBankEndIndex();
    KCheck(nSize <= MAX_BANK_SIZE);
    SetBankEndIndex(nSize);
}

void				PlayerArchive::SetDBPosition(const GLPos& pos)
{
	m_dbPlayer->m_Position	=	pos;
	SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_AT_POSITION);
}
inline  const GLPos*	PlayerArchive::GetDBPosition()
{
	return &m_dbPlayer->m_Position;
}

void				PlayerArchive::SetDBBakPosition(const GLPos& pos)
{
	m_dbPlayer->m_BakPosition = pos;
	SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_BK_POSITION);
}

inline  const GLPos*	PlayerArchive::GetDBBakPosition()
{
	return &m_dbPlayer->m_BakPosition;
}

void				PlayerArchive::SetDBNextPosition(const GLPos& pos)
{
	m_dbPlayer->m_NextPosition = pos;
	SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_NEXT_POSITION);
}

inline	const GLPos*	PlayerArchive::GetDBNextPosition()
{
	return &m_dbPlayer->m_NextPosition;
}

void				PlayerArchive::WriteDBPosition(GLPos& pos)
{
	m_dbPlayer->m_Position	=	pos;
	SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_AT_POSITION);
}

void				PlayerArchive::SetOnlineTime(uint32 uTime)	
{
	m_dbPlayer->m_OnlineTime = uTime;
	SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_ONLINETIME);
}
uint32				PlayerArchive::GetOnlineTime()			
{
	return m_dbPlayer->m_OnlineTime;
}
void				PlayerArchive::SetLoginTime(uint32 uTime)	
{
	m_dbPlayer->m_LastLoginTime = uTime;
	SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_LASTLOGINTIME);
}
uint32				PlayerArchive::GetLoginTime()				
{
	return m_dbPlayer->m_LastLoginTime;
}
void				PlayerArchive::SetLogoutTime(uint32 uTime)	
{
	m_dbPlayer->m_LastLogoutTime = uTime;
	SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_LASTLOGOUTTIME);
}
uint32				PlayerArchive::GetLogoutTime()			
{
	return m_dbPlayer->m_LastLogoutTime;
}

void				PlayerArchive::SetLeaveGuildTime(uint32 uTime)	
{
    m_dbPlayer->m_LeaveGuildTime = uTime;
    SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_LEAVEGUILDTIME);
}
uint32				PlayerArchive::GetLeaveGuildTime() const		
{
    return (uint32)m_dbPlayer->m_LeaveGuildTime;
}


inline  void		PlayerArchive::SetDBVersion(uint32 Ver)		
{
	m_dbPlayer->m_DBVersion = Ver;
	SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_DBVERSION);
}
inline  uint32		PlayerArchive::GetDBVersion()				
{
	return m_dbPlayer->m_DBVersion;
}

int32					PlayerArchive::GetWallowOnlineTime()
{
	return m_dbPlayer->m_nWallowOnlineTime;
}

void				PlayerArchive::SetWallowOnlineTime(int32 nTime)
{
	m_dbPlayer->m_nWallowOnlineTime = nTime;
	SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_WALLOWONLINETIME);
}

int32					PlayerArchive::GetWallowOfflineTime()
{
	return m_dbPlayer->m_nWallowOfflineTime;
}

void				PlayerArchive::SetWallowOfflineTime(int32 nTime)
{
	m_dbPlayer->m_nWallowOfflineTime = nTime;
	SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_WALLOWOFFLINETIME);
}

int32					PlayerArchive::GetTotalOnlineTime()
{
	return m_dbPlayer->m_nTotalOnlineTime;
}

void				PlayerArchive::SetTotalOnlineTime(int32 nTime)
{
	m_dbPlayer->m_nTotalOnlineTime = nTime;
	SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_TOTALONLINETIME);
}

uint32					PlayerArchive::GetTiredTime()
{
	return m_dbPlayer->m_TiredTime;
}

void				PlayerArchive::SetTiredTime(uint32 uTime)
{
	m_dbPlayer->m_TiredTime = uTime;
	SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_TIRED_TIME);
}

void				PlayerArchive::SetDBGuid(GUID_t	guid)
{
	m_dbPlayer->m_GUID	=	guid;
	SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_GUID);
}

GuildID_t			PlayerArchive::GetDBGuildID( )
{
	return m_dbPlayer->m_GuildID ;
}

void				PlayerArchive::SetDBGuildID( GuildID_t guildID )
{
	m_dbPlayer->m_GuildID	=	guildID;
	SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_GUILDID);
}

int32                 PlayerArchive::GetDBFamilyID( )
{
    return m_dbPlayer->m_FamilyID;
}

void				PlayerArchive::SetDBFamilyID( int32 nFamilyID )
{
    m_dbPlayer->m_FamilyID	=	nFamilyID;
    SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_FAMILYID);
}

int32                 PlayerArchive::GetDBGuildOfficial( )
{
    return m_dbPlayer->m_nGuildOfficial;   
}

void				PlayerArchive::SetDBGuildOfficial( int32 nOfficial )
{
    m_dbPlayer->m_nGuildOfficial =   nOfficial;
    SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_GUILDOFFICIAL);
}

BOOL                PlayerArchive::GetKing() const
{
	return m_dbPlayer->m_nCountryOfficial==COUNTRY_POSITION_KING;
}

void                PlayerArchive::SetKing(BOOL bValue)
{
	if( bValue==TRUE )
		m_dbPlayer->m_nCountryOfficial = COUNTRY_POSITION_KING;
	else
		m_dbPlayer->m_nCountryOfficial = COUNTRY_POSITION_MEMBER;

	SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_COUNTRY_OFFICIAL);
}

int32					PlayerArchive::GetCountryOfficial()
{
	return m_dbPlayer->m_nCountryOfficial;
}

void				PlayerArchive::SetCountryOfficial(int32 pos)
{
	m_dbPlayer->m_nCountryOfficial = pos;
	SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_COUNTRY_OFFICIAL);
}

BOOL                PlayerArchive::IsNeedRename() const
{
	return m_dbPlayer->m_nIsNeedRename == 0 ? FALSE : TRUE;
}

void				PlayerArchive::SetNewName(const char* pName)
{
	if( pName )
	{
		tsnprintf_s(m_dbPlayer->m_szNewName, sizeof(m_dbPlayer->m_szNewName), "%s", pName);
		SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_NEW_NAME);
	}
}

int32                 PlayerArchive::GetDBGuildPoint( )
{
    return m_dbPlayer->m_nGP;
}

void				PlayerArchive::SetDBGuildPoint( int32 nGP )
{
    m_dbPlayer->m_nGP            =   nGP;
    SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_GUILDPOINT);
}

int32				PlayerArchive::GetDBGuildMerit()
{
	return m_dbPlayer->m_nMerit;
}

void				PlayerArchive::SetDBGuildMerit(int32 nMerit)
{
	m_dbPlayer->m_nMerit = nMerit;
}

int32                 PlayerArchive::GetDBHonor( )
{
    return m_dbPlayer->m_nHonor;
}
void				PlayerArchive::SetDBHonor( int32 nHonor )
{
	if( nHonor > MAX_SHENGWANG_COUNT)
		nHonor = MAX_SHENGWANG_COUNT ;
    m_dbPlayer->m_nHonor =   nHonor;
    SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_HONOR);
}


void                 PlayerArchive::SetKillCountToday( uint16 nKillCount )
{
	if( m_dbPlayer->m_nKillCountToday != nKillCount )
	{
		m_dbPlayer->m_nKillCountToday = nKillCount;
		SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_KILL_COUNT_TODAY);
	}
}

uint16               PlayerArchive::GetKillCountToday()
{
	return m_dbPlayer->m_nKillCountToday;
}


void PlayerArchive::SetBattleHonour(uint32 nHonour)
{
	if( m_dbPlayerExtendInfo->m_nBattleHonour != nHonour )
	{
		m_dbPlayerExtendInfo->m_nBattleHonour = nHonour;
		SetArchiveEnumPropertyDirty( CPROPERTY_ARCHIVE_BATTLEHONOUR );
	}
}

uint32 PlayerArchive::GetBattleHonour()
{
	return m_dbPlayerExtendInfo->m_nBattleHonour;
}

void				PlayerArchive::SetPVP2V2Level( uint16 nLevel )
{
	if( m_dbPlayer->m_nPVP2V2_Level != nLevel )
	{
		m_dbPlayer->m_nPVP2V2_Level = nLevel;
		SetArchiveEnumPropertyDirty( CPROPERTY_ARCHIVE_PVP2V2_LEVEL );
	}
}

uint16				PlayerArchive::GetPVP2V2Level()
{
	return m_dbPlayer->m_nPVP2V2_Level;
}

void				PlayerArchive::SetPVP2V2Mark( uint16 nMark )
{
	if( m_dbPlayer->m_nPVP2V2_Mark != nMark )
	{
		m_dbPlayer->m_nPVP2V2_Mark = nMark;
		SetArchiveEnumPropertyDirty( CPROPERTY_ARCHIVE_PVP2V2_MARK );
	}
}

uint16				PlayerArchive::GetPVP2V2Mark()
{
	return m_dbPlayer->m_nPVP2V2_Mark;
}

int32					PlayerArchive::GetPVP2v2Mark_WeekTotal()
{
	return m_dbPlayer->m_nPVP2V2_Mark_WeekTotal;
}

void				PlayerArchive::SetPVP2v2Mark_WeekTotal(int32 nTotal)
{
	m_dbPlayer->m_nPVP2V2_Mark_WeekTotal = nTotal;
	SetArchiveEnumPropertyDirty( CPROPERTY_ARCHIVE_PVP2V2_MARK_WEEKTOTAL );
}

void				PlayerArchive::SetPVP2V2Day(int32 nDay)
{
	if( m_dbPlayer->m_nPVP2V2_Day != nDay )
	{
		m_dbPlayer->m_nPVP2V2_Day = nDay;
		SetArchiveEnumPropertyDirty( CPROPERTY_ARCHIVE_PVP2V2_DAY );
	}
}

int32					PlayerArchive::GetPVP2V2Day()
{
	return m_dbPlayer->m_nPVP2V2_Day;
}

int32					PlayerArchive::GetDuelMark()
{
	return m_dbPlayer->m_nDuelMark;
}

void				PlayerArchive::SetDuelMark( int32 nMark )
{
	if( m_dbPlayer->m_nDuelMark != nMark )
	{
		m_dbPlayer->m_nDuelMark = nMark;
		SetArchiveEnumPropertyDirty( CPROPERTY_ARCHIVE_DUEL_MARK );
	}
}

uint32                 PlayerArchive::GetDBInherenceExp( )
{
	return m_dbPlayer->m_nInherenceExp;
}

void				PlayerArchive::SetDBInherenceExp( uint32 nInherenceExp )
{
	m_dbPlayer->m_nInherenceExp =   nInherenceExp;
	SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_INHERENCE_EXP);
}

uint16                 PlayerArchive::GetDBInherenceLevel( )
{
	if( 0 == m_dbPlayer->m_nInherenceLevel )
	{
		m_dbPlayer->m_nInherenceLevel = 1;
	}
	return m_dbPlayer->m_nInherenceLevel;
}

void				PlayerArchive::SetDBInherenceLevel( uint16 nLevel )
{
	m_dbPlayer->m_nInherenceLevel =   nLevel;
	SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_INHERENCE_LEVEL);
}

TeamID_t			PlayerArchive::GetDBTeamID( )
{
	return m_dbPlayer->m_TeamID ;
}

void				PlayerArchive::SetDBTeamID( TeamID_t teamID )
{
	m_dbPlayer->m_TeamID	=	teamID;
	SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_TEAMID);
}

BusID_t			PlayerArchive::GetDBBusID( )
{
	return m_dbPlayer->m_BusID ;
}

void				PlayerArchive::SetDBBusID( BusID_t BusID )
{
	m_dbPlayer->m_BusID	=	BusID;
	SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_BUS_ID);
}

BOOL	PlayerArchive::GetDelCharFlag( ) 
{
	return m_dbPlayer->m_IsDelChar;
}
void	PlayerArchive::SetDelCharFlag( BOOL flag ) 
{
	m_dbPlayer->m_IsDelChar = flag;
	SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_IS_DEL_CHAR);
}

int32	PlayerArchive::GetLastForbidChatTime() const
{
	return m_dbPlayer->m_LastForbidChatTime;
}

void PlayerArchive::SetLastForbidChatTime(int32 iTime)
{
	m_dbPlayer->m_LastForbidChatTime = iTime;
	SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_LAST_FORBIDCHAT_TIME);
}

int32	PlayerArchive::GetLastEnjailTime() const
{
	return m_dbPlayer->m_LastEnjailTime;
}

void PlayerArchive::SetLastEnjailTime(int32 iTime)
{
	m_dbPlayer->m_LastEnjailTime = iTime;
	SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_LAST_ENJAIL_TIME);
}

const SItem*		PlayerArchive::GetBagItem(uint32 iBagIndex) const
{
	
	return m_dbBag->GetBagDB(iBagIndex);
}

const	SItem*		PlayerArchive::GetEquipItem(PLAYER_EQUIP equipPoint)
{
	return &m_dbEquip->m_pItem[equipPoint];
}

inline	uint32		PlayerArchive::GetBaseBagSize()
{
	return	MAX_SINGLEBAG_SIZE;
}

inline uint32			PlayerArchive::GetExtraContainerSize()
{
	return MAX_EXTRA_BAG_NUM;
}

inline	uint32		PlayerArchive::GetExtraBagSize(uint32 nIndex)
{
	SItem* pExtraBagItem = _GetBagItem(EXTRA_CONTAINER_OFFSET+nIndex);
	KCheck(pExtraBagItem);
	if (pExtraBagItem->IsNullType())
	{
		return 0;
	}
	KCheck(pExtraBagItem->ItemClass() == ICLASS_EXTRABAG);
	EXTRABAG_INFO_TB*	pGET		=		g_ItemTab.GetExtraBagInfoTB(pExtraBagItem->m_ItemIndex);
	KCheck(pGET);
	
	return pGET->m_nSize;
}

inline SItem*		PlayerArchive::_GetBagItem(uint32 uBagIndex)
{
	return	m_dbBag->m_pItem+uBagIndex;
}
inline SItem*		PlayerArchive::_GetBankItem(uint32 uBankIndex)
{
	KCheck(uBankIndex<MAX_BANK_SIZE);
	return	m_dbBank->m_pItem+uBankIndex;
}
inline void			PlayerArchive::SetCooldown(CooldownID_t nID,Time_t nTime)
{
	m_dbCooldown->RegisterCooldown(nID, nTime);
	SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_COOLDOWN);
}
inline BOOL			PlayerArchive::IsCooldowned(CooldownID_t nID) const
{
	return m_dbCooldown->IsSpecificSlotCooldownedByID(nID);
}
inline void			PlayerArchive::HeartBeat_Cooldown(Time_t nDeltaTime)
{
	
	m_dbCooldown->HeartBeat(nDeltaTime);
}
inline Time_t		PlayerArchive::GetCooldownRemain(CooldownID_t nID) const
{
	return m_dbCooldown->GetRemainTimeByID(nID);
}

inline void			PlayerArchive::ClearCooldown()
{
	m_dbCooldown->ClearCD();
}

inline uchar		PlayerArchive::GetSkillCount()
{
	return m_dbSpell->m_Count;
}
inline void		PlayerArchive::SetSkillCount(uchar Count)
{
	KCheck(Count<=MAX_CHAR_SKILL_NUM);
	m_dbSpell->m_Count	=	Count;
	SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_SKILL);
}
inline _PLAYER_SPELL& PlayerArchive::GetSkillID(uchar Index)
{
	KCheck(Index<MAX_CHAR_SKILL_NUM);
	return m_dbSpell->m_aSkill[Index];
}
inline void		PlayerArchive::SetSkillID(const _PLAYER_SPELL& oSkill,uchar Index)
{
	KCheck(Index<MAX_CHAR_SKILL_NUM);
	m_dbSpell->m_aSkill[Index]	=	oSkill;
	SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_SKILL);
}

inline void		PlayerArchive::SetSkillLevel(const int32 nID, uchar Index, const int32 nLevel)
{
	KCheck(Index<MAX_CHAR_SKILL_NUM);
	m_dbSpell->m_aSkill[Index].m_nLevel	=	nLevel;
	if(nLevel>0)
		m_dbSpell->m_aSkill[Index].m_eState = _PLAYER_SPELL::OWN_SKILL_CAN_USE;
	SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_SKILL);
}

inline void PlayerArchive::SetQuestDone(QuestID_t idQuest,QuestID_t idIndex)
{
	((m_DBQuest->m_aQuestHaveDoneFlags[idIndex] |= (0x00000001 << ((uint32)idQuest & 0x0000001F))) != 0);
	SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_QUEST);
}

inline void PlayerArchive::SetQuestUnDone(QuestID_t idQuest,QuestID_t idIndex)
{
	m_DBQuest->m_aQuestHaveDoneFlags[idIndex] &= ~(0x00000001 << ((uint32)idQuest & 0x0000001F));
	SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_QUEST);
}

inline void PlayerArchive::SetQuestParam(uint32 uIndexQuest, uint32 uIndexParam, int32 nValue )
{
	m_DBQuest->m_aQuest[uIndexQuest].m_anParam[uIndexParam] = nValue;
	SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_QUEST);
}

inline void PlayerArchive::SetQuestParam_Unsigned(uint32 uIndexQuest, uint32 uIndexParam, uint32 nValue)
{
	m_DBQuest->m_aQuest[uIndexQuest].m_aParam[uIndexParam] = nValue;
	SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_QUEST);
}

inline void	PlayerArchive::SetQuestData( int32 nIndex, int32 nData )
{
	m_DBQuest->m_aQuestData[nIndex] = nData ;
	SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_QUEST);
}

inline void PlayerArchive::SetQuest(uint32 uIndex,QuestID_t idQuest,ScriptID_t idScript)
{
	m_DBQuest->m_aQuest[uIndex].m_idQuest = idQuest;
	m_DBQuest->m_aQuest[uIndex].m_idScript  = idScript;
	SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_QUEST);
}

inline void	PlayerArchive::SetQuestCount(uint32 uCount)
{
	m_DBQuest->m_Count = uCount;
	SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_QUEST);
}

inline void	PlayerArchive::SetFlags_KillObject(uint32 uIndex, BOOL bSet )
{
	m_DBQuest->m_aQuest[uIndex].SetFlags_KillObject(bSet);
	SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_QUEST);
}
inline void	PlayerArchive::SetFlags_EnterArea(uint32 uIndex, BOOL bSet )
{
	m_DBQuest->m_aQuest[uIndex].SetFlags_EnterArea(bSet);
	SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_QUEST);
}
inline void	PlayerArchive::SetFlags_ItemChanged(uint32 uIndex, BOOL bSet )
{
	m_DBQuest->m_aQuest[uIndex].SetFlags_ItemChanged(bSet);
	SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_QUEST);
}
inline void	PlayerArchive::SetFlags_PetChanged(uint32 uIndex, BOOL bSet )
{
	m_DBQuest->m_aQuest[uIndex].SetFlags_PetChanged(bSet);
	SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_QUEST);
}
inline void	PlayerArchive::SetFlags_ClickNPC(uint32 uIndex, BOOL bSet )
{
	m_DBQuest->m_aQuest[uIndex].SetFlags_ClickNPC(bSet);
	SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_QUEST);
}
inline void PlayerArchive::ClearQuest(uint32 uIndex)
{
	m_DBQuest->m_aQuest[uIndex].Clear();
	m_DBQuest->m_Count--;
}


void				PlayerArchive::ChangeTitleForPrenticeCount(uint16 uTitleID)
{
	m_dbRelation->m_otherRelation.m_PrenticeInfo.m_uTitleForMaxCount = uTitleID;
	SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_RELATION);
}

int32				PlayerArchive::GetTitleForPrenticeCount()
{
	return m_dbRelation->m_otherRelation.m_PrenticeInfo.m_uTitleForMaxCount;
}

int32				PlayerArchive::GetCurPrenticeCount()
{
	return m_dbRelation->m_otherRelation.m_PrenticeInfo.GetPrenticeNum();
}

Time_t				PlayerArchive::GetSendGiftTime()
{
	return m_dbRelation->m_otherRelation.m_SendGiftTime;
}

uchar				PlayerArchive::GetSendGiftTimes()
{
	return m_dbRelation->m_otherRelation.m_SendTimes;
}

void				PlayerArchive::SetSendGiftTime(Time_t time)
{
	
	m_dbRelation->m_otherRelation.m_SendGiftTime = time;
	SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_RELATION);
}

void				PlayerArchive::SetSendGiftTimes(uchar times)
{
	KCheck(times >= 0);
	m_dbRelation->m_otherRelation.m_SendTimes = times;
	SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_RELATION);
}

void				PlayerArchive::SetRelationGroupName(const int32 index,const char* szName)
{
	KCheck( szName );
	
	
	SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_RELATION);
}

void				PlayerArchive::IncRelationCount(int32 Index)
{
	
	
	
}

void				PlayerArchive::DecRelationCount(int32 Index)
{
	
	
	
}

void				PlayerArchive::SetSpouse(const SMarriageInfo* pMarriageInfo)
{
	KCheck(pMarriageInfo);
	m_dbRelation->m_otherRelation.m_MarriageInfo.m_SpouseGUID = pMarriageInfo->m_SpouseGUID;
	m_dbRelation->m_otherRelation.m_MarriageInfo.m_uMarriageTime = GET_TIME().GetCTime();
	m_dbRelation->m_otherRelation.m_MarriageInfo.m_bHaveWedding = pMarriageInfo->m_bHaveWedding;
	SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_RELATION);
}

void				PlayerArchive::AddPrentice(GUID_t guid)
{
	KCheck( m_dbRelation->m_otherRelation.m_PrenticeInfo.GetPrenticeNum() < MAX_PRENTICE_COUNT );

	for( int32 i=0; i<MAX_PRENTICE_COUNT; ++i )
	{
		if(m_dbRelation->m_otherRelation.m_PrenticeInfo.m_aPrentice[i].m_nGuid == INVALID_ID)
		{
			m_dbRelation->m_otherRelation.m_PrenticeInfo.m_aPrentice[i].m_nGuid = guid;
			m_dbRelation->m_otherRelation.m_PrenticeInfo.m_aPrentice[i].m_nOfflineTime = 0;
			m_dbRelation->m_otherRelation.m_PrenticeInfo.m_DeleteRelationTime = GET_TIME().GetCTime();
			break;
		}
	}

	SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_RELATION);
}

void				PlayerArchive::DelPrentice(GUID_t guid, BOOL bIsForce/* = FALSE*/)
{
	KCheck(m_dbRelation->m_otherRelation.m_PrenticeInfo.GetPrenticeNum()>0);

	for( int32 i=0; i<MAX_PRENTICE_COUNT; ++i )
	{
		if(m_dbRelation->m_otherRelation.m_PrenticeInfo.m_aPrentice[i].m_nGuid == guid)
		{
			m_dbRelation->m_otherRelation.m_PrenticeInfo.m_aPrentice[i].m_nGuid = INVALID_ID;
			m_dbRelation->m_otherRelation.m_PrenticeInfo.m_aPrentice[i].m_nOfflineTime = 0;
			break;
		}
	}
	//if( TRUE == bIsForce )
	//{
	//	m_dbRelation->m_otherRelation.m_PrenticeInfo.m_DeleteRelationTime = GET_TIME().GetCTime();
	//}
	SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_RELATION);
}

void				PlayerArchive::Set_Property_MoralPoint(uint32 uPoint)
{
	
	
	
}

void				PlayerArchive::DelMaster()
{
	KCheck( m_dbRelation->m_otherRelation.m_MasterInfo.m_MasterGUID != INVALID_GUID );
	m_dbRelation->m_otherRelation.m_MasterInfo.m_MasterGUID = INVALID_GUID;
	
	SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_RELATION);
}

void				PlayerArchive::AddMaster(GUID_t guid)
{
	KCheck( m_dbRelation->m_otherRelation.m_MasterInfo.m_MasterGUID == INVALID_GUID );
	m_dbRelation->m_otherRelation.m_MasterInfo.m_MasterGUID = guid;
	m_dbRelation->m_otherRelation.m_MasterInfo.m_DeleteRelationTime = GET_TIME().GetCTime();
	SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_RELATION);
}

void				PlayerArchive::DoWedding()
{
	KCheck( m_dbRelation->m_otherRelation.m_MarriageInfo.m_SpouseGUID != INVALID_GUID );
	m_dbRelation->m_otherRelation.m_MarriageInfo.m_bHaveWedding = TRUE;
	SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_RELATION);
}

int32					PlayerArchive::GetPatrolID() const
{
	return m_dbRelation->m_otherRelation.m_nPatrolID;
}
void				PlayerArchive::SetPatrolID(int32 nIndex)
{
	KCheck( nIndex >= 0);
	m_dbRelation->m_otherRelation.m_nPatrolID = nIndex;
	SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_RELATION);
}

int32					PlayerArchive::GetCurrentPathNode() const
{
	return m_dbRelation->m_otherRelation.m_nCurrentPathNode;
}

void				PlayerArchive::SetCurrentPathNode(int32 nIndex)
{
	KCheck( nIndex >= 0);
	m_dbRelation->m_otherRelation.m_nCurrentPathNode = nIndex;
	SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_RELATION);
}
void				PlayerArchive::SetHonorRecord(const SArchiveLoader_Honor* pRecord)
{
	m_dbHonorRecord->Init(pRecord);
	SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_HONOR_RECORD);
}

void				PlayerArchive::SetAbilityLevel(SpellID_t abilityid,int32 lvl)
{
	if( abilityid<1 || abilityid>MAX_CHAR_ABILITY_NUM )
	{
		return;
	}

	m_dbSkill->Get_Ability(abilityid).m_Level = lvl;

	SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_ABILITY);
}

void				PlayerArchive::SetAbilityExp(SpellID_t abilityid,int32 exp)
{
	if( abilityid<1 || abilityid>MAX_CHAR_ABILITY_NUM )
	{
		return;
	}

	m_dbSkill->Get_Ability(abilityid).m_Exp = exp;
	SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_ABILITY);
}

void				PlayerArchive::SetPrescrLearnedFlag(const PrescriptionID_t prescrid, BOOL flag )
{
	__GUARD__

	int32 idx;
	idx = (int32)prescrid;
	if( idx<0 || idx>=MAX_SKILL_PRESCRIPTION_NUM )
	{
		KCheck(FALSE);
		return;
	}

	if ( flag != FALSE )
	{ 
		m_dbSkill->m_aPrescr[idx>>3] |= (0x01<<idx%8);
	}
	else
	{ 
		m_dbSkill->m_aPrescr[idx>>3] &= ~(0x01<<idx%8);
	}
	
	SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_ABILITY);

	__UNGUARD__
}


inline	const _HORSE_DB_LOAD*	PlayerArchive::GetPet(uint32	iIndex)	const 
{
		KCheck(iIndex<PLAYER_PET_MAX_COUNT);
		return &m_dbPetList->m_aPetDB[iIndex];
}

inline const	_HORSE_DB_LOAD* PlayerArchive::GetBankPet(uint32	iIndex)	const
{
	KCheck(iIndex<PLAYER_BANKPET_MAX_COUNT);
	return &m_dbBankPetList->m_aPetDB[iIndex];
}

inline void			PlayerArchive::_RegArchiveAttr(PLAYER_PROPERTY_ARCHIVE eOffSet,void* pArg,int32 iSize)
{
	KCheck(eOffSet<CPROPERTY_ARCHIVE_NUMBER);
	KCheck(eOffSet>=0);
	KCheck(pArg);
	KCheck(iSize);
	KCheck(m_AttrReg);
	m_AttrReg->m_AttrPtr[eOffSet] = pArg;
	m_AttrReg->m_AttrSize[eOffSet] = iSize;
}

inline void			PlayerArchive::_RegSHMAttr(PLAYER_PROPERTY_ARCHIVE eOffSet,void* pArg,int32 iSize)
{
	KCheck(eOffSet<CPROPERTY_ARCHIVE_NUMBER);
	KCheck(eOffSet>=0);
	KCheck(pArg);
	KCheck(iSize);
	KCheck(m_AttrRegSM);
	m_AttrRegSM->m_AttrPtr[eOffSet] = pArg;
	m_AttrRegSM->m_AttrSize[eOffSet] = iSize;
}

inline void			PlayerArchive::SetSettingData(int32 nType, _PLAYER_SETTING* Value )
{
	if( nType<0 || nType>=SETTING_TYPE_NUMBER )
		return ;

	m_dbSetting->m_aSetting[nType] = *Value ;
	SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_SETTING);
}

#define SETTINGFLAGISTRUE(Setting, FlagSet) (Setting&(1<<FlagSet))
inline void			PlayerArchive::SetPrivateInfo(SArchiveLoader_PrivateInfo* pPrivateInfo)
{
	__GUARD__
		
		KCheck(pPrivateInfo);
		memcpy(m_dbPrivateInfo,pPrivateInfo,sizeof(SArchiveLoader_PrivateInfo));
		SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_PRIVATEINFO);

	__UNGUARD__

}

inline const _PLAYER_SETTING* PlayerArchive::GetSetting( int32 nType ) const
{
	if( nType<0 || nType>=SETTING_TYPE_NUMBER )
		return NULL ;

	return &(m_dbSetting->m_aSetting[nType]) ;
}

inline	void	PlayerArchive::SetGameSetting( int32 settingMode, BOOL bShow)
{
__GUARD__
	uint16 SettingFlat = m_dbSetting->m_FlagGameSetting;
	switch(settingMode)
	{
	case SETTING_SHOWSUIT:
		{
			if(bShow)
				SettingFlat = (SettingFlat | 1<<SETTING_SHOWSUIT);
			else
				SettingFlat = ( SettingFlat & ~(1<<SETTING_SHOWSUIT)) ;
		}
		break;
	case SETTING_CHATNEAR:		
		{
			if(bShow)
				SettingFlat = (SettingFlat | 1<<SETTING_CHATNEAR);
			else
				SettingFlat = ( SettingFlat & ~(1<<SETTING_CHATNEAR)) ;
		}
		break;
	case SETTING_CHATTEAM:		
		{
			if(bShow)
				SettingFlat = (SettingFlat | 1<<SETTING_CHATTEAM);
			else
				SettingFlat = ( SettingFlat & ~(1<<SETTING_CHATTEAM)) ;
		}
		break;
	case SETTING_CHATGUILD:		
		{
			if(bShow)
				SettingFlat = (SettingFlat | 1<<SETTING_CHATGUILD);
			else
				SettingFlat = ( SettingFlat & ~(1<<SETTING_CHATGUILD)) ;
		}
		break;
	case SETTING_CHATWORLD:		
		{
			if(bShow)
				SettingFlat = (SettingFlat | 1<<SETTING_CHATWORLD);
			else
				SettingFlat = ( SettingFlat & ~(1<<SETTING_CHATWORLD)) ;
		}
		break;
	case SETTING_CHATJIAZU:		
		{
			if(bShow)
				SettingFlat = (SettingFlat | 1<<SETTING_CHATJIAZU);
			else
				SettingFlat = ( SettingFlat & ~(1<<SETTING_CHATJIAZU)) ;
		}
		break;
	case SETTING_CHATCOUNTRY:		
		{
			if(bShow)
				SettingFlat = (SettingFlat | 1<<SETTING_CHATCOUNTRY);
			else
				SettingFlat = ( SettingFlat & ~(1<<SETTING_CHATCOUNTRY)) ;
		}
		break;
	default:
		{
			KCheck(0);
		}
	}
	
	m_dbSetting->m_FlagGameSetting = SettingFlat;
	SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_SETTING);

	__UNGUARD__
}

inline const	uchar	PlayerArchive::GetGameSettingMode( int32 settingMode ) const
{
__GUARD__
	switch(settingMode)
	{
	case SETTING_SHOWSUIT:		
		{
			return ((m_dbSetting->m_FlagGameSetting>>SETTING_SHOWSUIT) & 1) ;
		}
		break;
	case SETTING_CHATNEAR:		
		{
			return ((m_dbSetting->m_FlagGameSetting>>SETTING_CHATNEAR) & 1) ;
		}
		break;
	case SETTING_CHATTEAM:		
		{
			return ((m_dbSetting->m_FlagGameSetting>>SETTING_CHATTEAM) & 1);
		}
		break;
	case SETTING_CHATGUILD:		
		{
			return ((m_dbSetting->m_FlagGameSetting>>SETTING_CHATGUILD) & 1) ;
		}
		break;
	case SETTING_CHATWORLD:		
		{
			return ((m_dbSetting->m_FlagGameSetting>>SETTING_CHATWORLD) & 1) ;
		}
		break;
	case SETTING_CHATJIAZU:		
		{
			return ((m_dbSetting->m_FlagGameSetting>>SETTING_CHATJIAZU) & 1) ;
		}
		break;
	case SETTING_CHATCOUNTRY:		
		{
			return ((m_dbSetting->m_FlagGameSetting>>SETTING_CHATCOUNTRY) & 1) ;
		}
		break;
	default:
		{
			KCheck(0);
		}
	}
	return 0;
	__UNGUARD__
		return 0;
}

inline	int32					PlayerArchive::GetReserve(int32 index)
{
	KCheck(index>=0);
	KCheck(index<MAX_RESERVE);
	return	m_dbPlayer->m_Reserve[index];
}
inline void						PlayerArchive::SetReserve(int32 index,int32 value)
{
	KCheck(index>=0);
	KCheck(index<MAX_RESERVE);
	m_dbPlayer->m_Reserve[index] = value;
	SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_RESERVE);
}

inline	uchar				PlayerArchive::GetGuildBuildCount()
{
	return m_dbPlayer->m_cGuildBuild_Count;
}

inline void					PlayerArchive::SetGuildBuildCount(uchar count)
{
	m_dbPlayer->m_cGuildBuild_Count = count;
	SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_GUILDBUILD_COUNT);
}

inline	int32					PlayerArchive::GetGuildBuildDay()
{
	return m_dbPlayer->m_nGuildBuild_Day;
}

inline void					PlayerArchive::SetGuildBuildDay(int32 nDay)
{
	m_dbPlayer->m_nGuildBuild_Day = nDay;
	SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_GUILDBUILD_DAY);
}

inline void		PlayerArchive::SetSoldItemValue(int32 idx, SItem* pItem)
{
	KCheck(idx>=0);
	KCheck(idx<MAX_BOOTH_SOLD_NUMBER);
	m_dbSoldList->m_list[idx].m_ItemHasBeenSold = *pItem;
	SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_SOLDLIST);
}

inline void		PlayerArchive::SetSoldItemPrice(int32 idx, int32 iPrice)
{
	KCheck(idx>=0);
	KCheck(idx<MAX_BOOTH_SOLD_NUMBER);
	m_dbSoldList->m_list[idx].m_SoldPrice = iPrice;
	SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_SOLDLIST);
}

inline void		PlayerArchive::SetSoldItemPriceType(int32 idx, int32 iPriceType)
{
	KCheck(idx>=0);
	KCheck(idx<MAX_BOOTH_SOLD_NUMBER);
	m_dbSoldList->m_list[idx].m_SoldPriceType = iPriceType;
	SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_SOLDLIST);
}

inline SItem*	PlayerArchive::GetSoldItemValue(int32 idx) const
{
	KCheck(idx>=0);
	KCheck(idx<MAX_BOOTH_SOLD_NUMBER);
	return &(m_dbSoldList->m_list[idx].m_ItemHasBeenSold);
}

inline int32		PlayerArchive::GetSoldItemPrice(int32 idx) const
{
	KCheck(idx>=0);
	KCheck(idx<MAX_BOOTH_SOLD_NUMBER);
	return m_dbSoldList->m_list[idx].m_SoldPrice;
}

inline int32		PlayerArchive::GetSoldItemPriceType(int32 idx) const
{
	KCheck(idx>=0);
	KCheck(idx<MAX_BOOTH_SOLD_NUMBER);
	return m_dbSoldList->m_list[idx].m_SoldPriceType;
}


const	SArchiveLoader_Bag*			PlayerArchive::GetBagArchive()
{
	return m_dbBag;
}
const	SArchiveLoader_Player*			PlayerArchive::GetPlayerArchive()	const
{
	return	m_dbPlayer;
}
const	SArchiveLoader_Equip*			PlayerArchive::GetEquipArchive()
{
	return	m_dbEquip;
}
const	SArchiveLoader_Bank*			PlayerArchive::GetBankArchive()
{
	return m_dbBank;
}

const SArchiveLoader_Spell*			PlayerArchive::GetSpellArchive()
{
	return m_dbSpell;
}

const SArchiveLoader_MonsterPet*			PlayerArchive::GetMonsterPetArchive() const
{
	return m_dbMonsterPet;
}

const	SArchiveLoader_SoldList*		PlayerArchive::GetSoldListArchive() const
{
	return m_dbSoldList;
}

const SArchiveLoader_CoolDown* PlayerArchive::GetCooldownArchive() const
{
	return m_dbCooldown;	
}

const	SArchiveLoader_Relationship*		PlayerArchive::GetRelationArchive() const
{
	return m_dbRelation;
}

const	SArchiveLoader_Honor*		PlayerArchive::GetHonorRecordArchive()	const
{
	return m_dbHonorRecord;
}

const SArchiveLoader_Skill*	PlayerArchive::GetSkillArchive() const
{
	return m_dbSkill;
}


const SArchiveLoader_Effect*		PlayerArchive::GetEffectArchive() const
{
	return m_dbEffect;
}

const void PlayerArchive::MarkImpactDirty()
{
	SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_IMPACT);
}

const SArchiveLoader_Quest*		PlayerArchive::GetQuestArchive() const
{
	return m_DBQuest;
}

const SArchiveLoader_Setting*		PlayerArchive::GetSettingArchive() const
{
	return m_dbSetting;
}

const	SArchiveLoader_PrivateInfo*	PlayerArchive::GetPrivateInfoArchive() const
{
	return m_dbPrivateInfo;
}

void				PlayerArchive::WritePlayerArchive(const	SArchiveLoader_Player* pHumanDB)
{
	memcpy(m_dbPlayer,pHumanDB,sizeof(SArchiveLoader_Player));
}

void				PlayerArchive::WriteBagArchive(const	SArchiveLoader_Bag* pBagDB)
{
	memcpy(m_dbBag,pBagDB,sizeof(SArchiveLoader_Bag));
}

void				PlayerArchive::WriteEquipArchive(const	SArchiveLoader_Equip*	pEquipDB)
{
	memcpy(m_dbEquip,pEquipDB,sizeof(SArchiveLoader_Equip));
}


void				PlayerArchive::WriteBankArchive(const	SArchiveLoader_Bank*	pBankDB)
{
	memcpy(m_dbBank,pBankDB,sizeof(SArchiveLoader_Bank));					
}

void				PlayerArchive::WriteSpellArchive(const SArchiveLoader_Spell* pSkillDB)
{
	memcpy(m_dbSpell,pSkillDB,sizeof(SArchiveLoader_Spell));					
}

void				PlayerArchive::WriteCooldownArchive(const SArchiveLoader_CoolDown* pCooldownDB)
{
	memcpy(m_dbCooldown,pCooldownDB,sizeof(SArchiveLoader_CoolDown));					
}

void				PlayerArchive::WriteRelationArchive(const SArchiveLoader_Relationship* pRelationDB)
{
	memcpy(m_dbRelation, pRelationDB, sizeof(SArchiveLoader_Relationship));					
}

void				PlayerArchive::WriteHonorRecordArchive(const SArchiveLoader_Honor* pHonorRecordDB)
{
	memcpy(m_dbHonorRecord, pHonorRecordDB, sizeof(SArchiveLoader_Honor));
}

void				PlayerArchive::WriteAbilityArchive(const SArchiveLoader_Skill* pAbilityDB)
{
	memcpy(m_dbSkill,pAbilityDB,sizeof(SArchiveLoader_Skill));
}

void				PlayerArchive::WriteImpactArchive(const SArchiveLoader_Effect* pImpactDB)
{
	memcpy(m_dbEffect,pImpactDB,sizeof(SArchiveLoader_Effect));
}

void				PlayerArchive::WriteQuestArchive(const SArchiveLoader_Quest* pQuestDB)
{
	memcpy(m_DBQuest,pQuestDB,sizeof(SArchiveLoader_Quest));
}

void				PlayerArchive::WriteSettingArchive(const SArchiveLoader_Setting* pSettingDB)
{
	memcpy(m_dbSetting,pSettingDB,sizeof(SArchiveLoader_Setting));
}
void			PlayerArchive::WritePrivateInfoArchive(const SArchiveLoader_PrivateInfo* pPrivateDB)
{
	memcpy(m_dbPrivateInfo,pPrivateDB,sizeof(SArchiveLoader_PrivateInfo));
}
void			PlayerArchive::WriteMonsterPetArchive(const SArchiveLoader_MonsterPet* pMonsterPetDB)
{
	memcpy(m_dbMonsterPet,pMonsterPetDB,sizeof(SArchiveLoader_MonsterPet));
}

void			PlayerArchive::WritePetArchive(const _HORSE_DB_LIST_LOAD* pPetData)
{
	memcpy( m_dbPetList, pPetData, sizeof(_HORSE_DB_LIST_LOAD) ) ;
}

void			PlayerArchive::WriteBankPetArchive(const _BANKPET_DB_LIST_LOAD* pPetData)
{
	memcpy( m_dbBankPetList, pPetData, sizeof(_BANKPET_DB_LIST_LOAD) ) ;
}

void			PlayerArchive::WriteSoldListArchive(const SArchiveLoader_SoldList* pSoldList)
{
	memcpy( m_dbSoldList, pSoldList, sizeof(SArchiveLoader_SoldList) );
}

void			PlayerArchive::WritePlayerExtendInfoArchive(const SArchiveLoader_Player_ExtendInfo *pPlayerExtendInfo)
{
		memcpy( m_dbPlayerExtendInfo, pPlayerExtendInfo, sizeof(SArchiveLoader_Player_ExtendInfo) );
}


void PlayerArchive::SetBankPetValidSlot(int32 val)
{
	KCheck(val <= PLAYER_BANKPET_MAX_COUNT);
	m_dbBankPetList->m_uValidCount = val;
	SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_BANKPET);
}

int32	PlayerArchive::GetBankPetValidSlot()
{
	return m_dbBankPetList->m_uValidCount;
}

void PlayerArchive::SetDBFlag(CHAR_ATTR_DBFLAG uIndex,BOOL bFlag)
{
	if( bFlag )
	{
		m_dbPlayer->m_uDBFlag |= (1<<uIndex);
	}
	else
	{
		m_dbPlayer->m_uDBFlag &= ~(1<<uIndex);
	}

	SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_DBFLAG);
}

BOOL PlayerArchive::GetDBFlag(CHAR_ATTR_DBFLAG uIndex)
{
	return m_dbPlayer->m_uDBFlag & (1<<uIndex);
}


void PlayerArchive::SetExploit(int32 nExploit)
{
	m_dbPlayer->m_nExploit = nExploit;
	SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_EXPLOIT);
}

int32 PlayerArchive::GetExploit()
{
	return m_dbPlayer->m_nExploit;
}

void PlayerArchive::SetExploitDay(int16 nDay)
{
	m_dbPlayer->m_nExploitDay = nDay;
	SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_EXPLOITDAY);
}

int16 PlayerArchive::GetExploitDay()
{
	return m_dbPlayer->m_nExploitDay;
}

ID_t PlayerArchive::GetWorldID()
{
	return m_dbPlayer->m_nPlayerWorldID;
}

void PlayerArchive::SetMountModelID(int32 nModelID)
{
	m_dbPlayer->m_MountModelID = nModelID;
	SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_MOUNTMODELID);
}

const SArchiveLoader_Player_ExtendInfo* PlayerArchive::GetPlayerExtendInfoArchive()
{
	return m_dbPlayerExtendInfo;
}

const SPlayerShopFolder& PlayerArchive::GetShopItemFavorite()
{
	return m_dbPlayerExtendInfo->m_ShopItemFavorite;
}

const SPlayerShopFolder& PlayerArchive::GetShopItemBuyHistory()
{
	return m_dbPlayerExtendInfo->m_ShopItemBuyHistory;
}

SPlayerInherenceZhanJing& PlayerArchive::GetInherenceZhanJing()
{
	return m_dbPlayerExtendInfo->m_InherenceZhanJing;
}

int32 PlayerArchive::GetInherenceZhuanGongLevel(PROFESSION_TYPE eProfession)
{
	KCheck(eProfession > PROFESSION_UNKNOW && eProfession < PROFESSION_NUMBER);

	return m_dbPlayerExtendInfo->m_InherenceZhanJing.m_pZhanGong_Level[eProfession];
}

void PlayerArchive::SetInherenceZhuanGongLevel(PROFESSION_TYPE eProfession, int32 value)
{
	KCheck(eProfession > PROFESSION_UNKNOW && eProfession < PROFESSION_NUMBER);

	m_dbPlayerExtendInfo->m_InherenceZhanJing.m_pZhanGong_Level[eProfession] = value;
	SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_INHERENCEZHUANJING);

}

int32 PlayerArchive::GetInherenceZhuanGongPoint(PROFESSION_TYPE eProfession)
{
	KCheck(eProfession > PROFESSION_UNKNOW && eProfession < PROFESSION_NUMBER);

	return m_dbPlayerExtendInfo->m_InherenceZhanJing.m_pZhanGong_Point[eProfession];
}

void PlayerArchive::SetInherenceZhuanGongPoint(PROFESSION_TYPE eProfession, int32 value)
{
	KCheck(eProfession > PROFESSION_UNKNOW && eProfession < PROFESSION_NUMBER);

	m_dbPlayerExtendInfo->m_InherenceZhanJing.m_pZhanGong_Point[eProfession] = value;
	SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_INHERENCEZHUANJING);

}

int32 PlayerArchive::GetInherenceZhuanGongTotalCoefficient()
{
	return m_dbPlayerExtendInfo->m_InherenceZhanJing.m_nZhanGong_Total_Coefficient;
}

void PlayerArchive::SetInherenceZhuanGongTotalCoefficient(int32 value)
{
	m_dbPlayerExtendInfo->m_InherenceZhanJing.m_nZhanGong_Total_Coefficient = value;
	SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_INHERENCEZHUANJING);

}

int32 PlayerArchive::GetInherenceZhuanGongCoefficient(PROFESSION_TYPE eProfession)
{
	KCheck(eProfession > PROFESSION_UNKNOW && eProfession < PROFESSION_NUMBER);

	return m_dbPlayerExtendInfo->m_InherenceZhanJing.m_pZhanGong_Coefficient[eProfession];
}

void PlayerArchive::SetInherenceZhuanGongCoefficient(PROFESSION_TYPE eProfession, int32 value)
{
	KCheck(eProfession > PROFESSION_UNKNOW && eProfession < PROFESSION_NUMBER);

	m_dbPlayerExtendInfo->m_InherenceZhanJing.m_pZhanGong_Coefficient[eProfession] = value;
	SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_INHERENCEZHUANJING);

}

int32 PlayerArchive::GetInherenceZhuanFangTotalPoint()
{
	return m_dbPlayerExtendInfo->m_InherenceZhanJing.m_nZhanFang_Total_Point;
}

void PlayerArchive::SetInherenceZhuanFangTotalPoint(int32 value)
{
	m_dbPlayerExtendInfo->m_InherenceZhanJing.m_nZhanFang_Total_Point = value;
	SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_INHERENCEZHUANJING);

}

int32 PlayerArchive::GetInherenceZhuanFangLevel(PROFESSION_TYPE eProfession)
{
	KCheck(eProfession > PROFESSION_UNKNOW && eProfession < PROFESSION_NUMBER);

	return m_dbPlayerExtendInfo->m_InherenceZhanJing.m_pZhanFang_Level[eProfession];
}

void PlayerArchive::SetInherenceZhuanFangLevel(PROFESSION_TYPE eProfession, int32 value)
{
	KCheck(eProfession > PROFESSION_UNKNOW && eProfession < PROFESSION_NUMBER);

	m_dbPlayerExtendInfo->m_InherenceZhanJing.m_pZhanFang_Level[eProfession] = value;
	SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_INHERENCEZHUANJING);

}

#endif
