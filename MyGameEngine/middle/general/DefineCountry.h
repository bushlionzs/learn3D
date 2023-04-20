#ifndef __GAMEDEFINE_COUNTRY_H__
#define __GAMEDEFINE_COUNTRY_H__

#define COUNTRY_DELATE_SCRIPT			300316
#define ON_COUNTRY_DELATE_RET			"OnCountryDelateRet"
#define MAX_COUNTRY_VOTER			1024
#define NEED_GUILD_CHIEFTAIN_VOTER_COUNT	4
enum COUNTRY_AUTHORITY
{
	COUNTRY_AUTHORITY_INVALID		= -1,
	COUNTRY_AUTHORITY_APPOINT_GENERAL	= 0,
	COUNTRY_AUTHORITY_APPOINT_LMINISTER	= 1,
	COUNTRY_AUTHORITY_APPOINT_RMINISTER	= 2,
	COUNTRY_AUTHORITY_APPOINT_LGUARD	= 3,
	COUNTRY_AUTHORITY_APPOINT_RGUARD	= 4,
	COUNTRY_AUTHORITY_FORTUNE_YULONG	= 5,
	COUNTRY_AUTHORITY_FORTUNE_HUWEI		= 6,
	COUNTRY_AUTHORITY_FORTUNE_TIANGE1	= 7,
	COUNTRY_AUTHORITY_FORTUNE_TIANGE2	= 8,
	COUNTRY_AUTHORITY_FORTUNE_TIANGE3	= 9,
	COUNTRY_AUTHORITY_FORTUNE_TIANXING	= 10,
	COUNTRY_AUTHORITY_MODIFY_NOTICE		= 11,
	COUNTRY_AUTHORITY_COLLECT		= 12,
	COUNTRY_AUTHORITY_FORBIDCHAT		= 13,
	COUNTRY_AUTHORITY_ENJAIL		= 14,
	COUNTRY_AUTHORITY_ASSOIL		= 15,
	COUNTRY_AUTHORITY_TOPLIST		= 16,
	COUNTRY_AUTHORITY_RESOURCE		= 17,
    COUNTRY_AUTHORITY_GUOYUN        = 18,       // ����ԤԼ
    COUNTRY_AUTHORITY_CHUGUO        = 19,       // ����ԤԼ
    COUNTRY_AUTHORITY_MUJI          = 20,       // ����ļ��ԤԼ
	COUNTRY_AUTHORITY_NUMBER,
};

enum COUNTRY_POSITION
{
	COUNTRY_POSITION_INVALID		= -1,
	COUNTRY_POSITION_MEMBER			= 0,
	COUNTRY_POSITION_GUARDS			= 1,
	COUNTRY_POSITION_LGUARD			= 2,
	COUNTRY_POSITION_RGUARD			= 3,
	COUNTRY_POSITION_LMINISTER		= 4,
	COUNTRY_POSITION_RMINISTER		= 5,
	COUNTRY_POSITION_GENERAL		= 6,
	COUNTRY_POSITION_QUEEN			= 7,
	COUNTRY_POSITION_KING			= 8,
	COUNTRY_POSITION_SIZE,
};

static const char *g_szPosition[] = {
    "����", 
    "��������", 
    "��ǰ����", 
    "��ǰ�һ���", 
    "��ة", 
    "����", 
    "�󽫾�", 
    "����", 
    "����", 
};

enum COUNTRY_SPECIAL_POSITION
{
	COUNTRY_SPECIAL_POSITION_INVALID		= -1,
	//--��������ȸ
	COUNTRY_SPECIAL_POSITION_QINGLONG_LEADER = 0,
	COUNTRY_SPECIAL_POSITION_QINGLONG_MEMBER = 1,
	COUNTRY_SPECIAL_POSITION_ZHUQUE_LEADER = 2,
	COUNTRY_SPECIAL_POSITION_ZHUQUE_MEMBER = 3,
	//--��������ȸend
	COUNTRY_SPECIAL_POSITION_SIZE,
};


//////////////////////////////////////////////////////////////////////////////////
//********************************************************************************
//ע��:
//���ұ����������,��ͬ��ScriptGlobal.lua��ȥ,����ϸ����Ƿ��ͻ
//2009-10-26 ���ι�
//********************************************************************************
//////////////////////////////////////////////////////////////////////////////////
enum COUNTRY_PARAM
{
	CD_INDEX_DESTROY_ISSUE_TIME         		= 0,       	//�й��ƻ��ϴ����˵�ʱ��
	CD_INDEX_DESTROY_ISSUE_COUNT        		= 1,      	//�й��ƻ����˴���
	CD_INDEX_DESTROY_ISSUE_SCENE	    		= 2,		//�����������ڳ���	
	CD_INDEX_MISSION_CAOBAOTU           		= 4,        //�ر�ͼ��Ϣ
	CD_INDEX_QUEST_GUOYUN_COUNT					= 5,		//�������ڼ䣬������ɴ���
	CD_INDEX_QUEST_CHUGUO_COUNT					= 6,		//�������ڼ䣬������ɴ���
	CD_INDEX_COUNTRYBATTLELITE_DATE				= 7,		//����ս����
	CD_INDEX_COUNTRYBATTLELITE_CAMP				= 8,		//����ս��Ӫ
	CD_INDEX_COUNTRYBATTLELITE_KILLCOUNT		= 9,		//����ս��ɱ�󽫾����Ǳ����󽫾�����
	CD_INDEX_COUNTRYBATTLELITE_KING_ISSUE		= 10,		//����ս��������
	CD_INDEX_COUNTRYBATTLELITE_MATCH_COUNTRY	= 11,		//����ս��Թ���
	CD_INDEX_COUNTRYBATTLELITE_FINISHED			= 12,		//����ս�Ƿ��Ѿ�����
	CD_INDEX_POLUOZHOU_RANDOM_DAY               = 14,        //��������������˫������������ڣ�ÿ��һ�죩
	CD_INDEX_GUOYUN_DAY							= 15,		//���������ʱ��
	CD_INDEX_CHUGUO_DAY							= 16,		//���������ʱ��
	CD_INDEX_GUILDWORLDCUP_TURNNUMBER			= 20,
	CD_INDEX_GUOYUN_KING						= 21,
	CD_INDEX_GUOYUN_QUEEN						= 22,
	CD_INDEX_GUOYUN_GENERAL						= 23,
	CD_INDEX_GUOYUN_RMINISTER					= 24,
	CD_INDEX_GUOYUN_LMINISTER					= 25,
	CD_INDEX_GUOYUN_RGUARD						= 26,
	CD_INDEX_GUOYUN_LGUARD						= 27,
	CD_INDEX_CHUGUO_KING						= 28,
	CD_INDEX_CHUGUO_QUEEN						= 29,
	CD_INDEX_CHUGUO_GENERAL						= 30,
	CD_INDEX_CHUGUO_RMINISTER					= 31,
	CD_INDEX_CHUGUO_LMINISTER					= 32,
	CD_INDEX_CHUGUO_RGUARD						= 33,
	CD_INDEX_CHUGUO_LGUARD						= 34,
	CD_INDEX_STRENGTH							= 35,       //commented by jiangchao,[ÿ��Ĺ���ʵ��]��ÿ���������0
	CD_INDEX_STRENGTH_Y							= 36,		//commented by jiangchao,[��������µĹ���ʵ��], ÿ���Լ���ÿ��һ�����ۼ�[ÿ��Ĺ���ʵ��]
	CD_INDEX_STRENGTH_DAY						= 37,		//commented by jiangchao,[ÿ��Ĺ���ʵ��]��ʱ��,ÿ������
	CD_INDEX_CHINAJOY_TIMES						= 38,		//ChinaJoy ����
	CD_INDEX_CHINAJOY_DATE						= 39,		//ChinaJoy ����
	CD_INDEX_RUOGUO_SHOUJI_DATE					= 40,		//���������ϴ��ռ�����
	CD_INDEX_RUOGUO_SHOUJI_FLAG					= 41,		//���������ռ�Index
	CD_INDEX_MOJUN_KILL_COUNT1					= 42,
	CD_INDEX_MOJUN_KILL_COUNT2					= 43,
	CD_INDEX_MOJUN_KILL_COUNT3					= 44,
	CD_INDEX_MOJUN_KILL_COUNT4					= 45,
	CD_INDEX_RUOGUO_START_FLAG					= 46,
	CD_INDEX_STRENGTH_WEEKTOTAL					= 48,		//commented by jiangchao,literally"�ܹ���ʵ��???",����CD_INDEX_STRENGTH_Y,[��������µĹ���ʵ��]
	CD_INDEX_STRENGTH_WEEKTOTAL_Y				= 49,		//commented by jiangchao,"ÿ��һ"�ۼ�CD_INDEX_STRENGTH_WEEKTOTAL
	CD_INDEX_STRENGTH_WEEKTOTAL_DAY				= 50,		//commented by jiangchao,"ÿ��һ"����
	CD_INDEX_MINSTER_KILLDATE					= 51,		//���Ҵ󳼴�ɱ
	CD_INDEX_CREATE_KING_DATE					= 52,		//������������

	CD_INDEX_CREATE_QINGLONG_DATE				= 53,		//������������
	CD_INDEX_CREATE_ZHUQUE_DATE					= 54,		//��ȸ��������
	
	CD_INDEX_BE_DELATED_KING_GUID				= 55,		//����������GUID
    CD_PIONEER_FUNS                             = 56,       // ��˿�ȷ��Ż
	CD_INDEX_KING_DEMISE_COUNT					= 57,
	CD_INDEX_QINGLONG_DEMISE_DATE				= 58,
	CD_INDEX_QINGLONG_DEMISE_COUNT				= 59,
	CD_INDEX_ZHUQUE_DEMISE_DATE					= 60,
	CD_INDEX_ZHUQUE_DEMISE_COUNT				= 61,
	CD_INDEX_ZHAOJILIN_DATE						= 62,
	CD_INDEX_ZHAOJILIN_DAYCOUNT					= 63,
	CD_INDEX_ZHAOJILIN_TIME						= 64,
	CD_ZHAOJILIN_SCENE							= 65,
	CD_ZHAOJILIN_POS_X							= 66,
	CD_ZHAOJILIN_POS_Z							= 67,
    CD_PRECONTRACT_GUOYUN                       = 68,       // ����ԤԼ
    CD_PRECONTRACT_CHUGUO                       = 69,       // ����ԤԼ
    CD_PRECONTRACT_MUJI                         = 70,       // ����ļ��ԤԼ
	CD_RICHANG_QUESTID                          = 71,       // �ճ��淨ID
	CD_YOULECHANG_CAIPIAO1						= 72,       // �޵�������
	CD_YOULECHANG_CAIPIAO2						= 73,       // �޵�������
    CD_DAGUANYUAN_CAIPIAO1                      = 74,       // ���԰˫�Ǳ�ϲ
    CD_DAGUANYUAN_CAIPIAO2                      = 75,       // ���԰˫�Ǳ�ϲ
    CD_INDEX_KING_DEMISE_DATE					= 76,
    
	CD_LASTWEEK_PINGFEN_DATE					= 77,		// �������ܵĽ�Ǯ���Ѽ�¼ʱ��
	CD_LASTWEEK_PINGFEN_MONEY					= 78,		// �������ܵĽ�Ǯ���ѵ�����
	CD_CURWEEK_PINGFEN_DATE						= 79,		// ���ұ��ܵĽ�Ǯ���Ѽ�¼ʱ��
	CD_CURWEEK_PINGFEN_MONEY					= 80,		// ���ұ��ܵĽ�Ǯ���Ѽ�¼ʱ��

	CD_LASTWEEK_STRONG_WEAK_JIFEN				= 81,		//��������ǿ������
	CD_LASTWEEK_STRONG_WEAK_JIFEN_DATE			= 82,		//��������ǿ������ʱ��
	CD_CURWEEK_STRONG_WEAK_JIFEN				= 83,		//���ұ���ǿ������
	CD_CURWEEK_STRONG_WEAK_JIFEN_DATE			= 84,		//���ұ���ǿ������ʱ��
	CD_STRONG_WEAK_LEVEL						= 85,		//����ǿ���ȼ�

	CD_STRONG_WEAK_GUILD_JIFEN					= 86,		//�������Ĺ���ǿ������,��һˢ�µ�����ǿ������֣�Ȼ������		
	CD_STRONG_WEAK_GUILD_JIFEN_DATE			    = 87,		//�������Ĺ���ǿ�����ֵ�ʱ��,��һ����


	CD_HUODONG_XINNIAN							= 88,		//�����淨
	CD_LEAGUE_COUNTRY_ID						= 89,		//���˹���ID ע���ʼ����ʱ��ҪΪ-1������Ĭ�ϵĽ��˹���Ϊ¥��!!!

	CD_DISMISS_COLLEAGUE_DATE					= 90,		//���˵�����
	CD_DISMISS_COLLEAGUE_COUNT					= 91,		//���˵Ĵ���
	
	CD_INDEX_DEFINE_COUNT,

};

enum E_COUNTRY_DELATE_RET
{
	CDR_SUCCESS				= 0,
	CDR_CANNOT_DELATE_YOURSELF,
	CDR_ALREADY_DELATING,
	CDR_NOT_HAVE_ENOUGH_CHIEFTAIN_ONLINE,
	CDR_NOT_HAVE_KING,
	CDR_NEED_HIGH_ORDER,
	CDR_UNKNOW
};

enum E_COUNTRY_DELATE_CHIEFTAIN_VOTE_RET { CDCVR_SUCCESS = 0, CDCVR_DELATING_OVER, CDCVR_CANNOT_DELATE_OTHER_PERSON, CDCVR_UNKNOW };

enum E_COUNTRY_DELATE_MEMBER_VOTE_RET { CDMVR_SUCCESS = 0, CDMVR_DELATING_OVER, CDMVR_CANNOT_DELATE_OTHER_PERSON, CDMVR_UNKNOW };
#endif
