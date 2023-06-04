/*$T Client/Game/ItemCommon.h GC 1.140 08/23/09 04:52:37 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#pragma once

/* ��Ʒ���� */
enum
{
	RULE_DROP		= 0,			/* �Ƿ�ɶ��� */
	RULE_OVERLAY,					/* �Ƿ���ص� */
	RULE_QUICK,						/* �Ƿ�ɷ������� */
	RULE_SALE,						/* �Ƿ���Գ��۸�NPC�̵� */
	RULE_EXCHANGE,					/* �Ƿ���Խ��� */
	RULE_USE,						/* �Ƿ����ʹ�� */
	RULE_PICKBIND,					/* �Ƿ���ʰȡ� */
	RULE_EQUIPBIND,					/* �Ƿ���װ��� */
	RULE_UNIQUE,					/* �Ƿ���Ψһ */
	RULE_IDENT,						/* �Ƿ���Ҫ���� �� */
	RULE_DUMMYITEM,					/* �Ƿ�������� �� */
	RULE_BANK,						/* �Ƿ���Դ������� �� */
	RULE_CONSUME,					/* �Ƿ����� */
};

/* ��Ʒ���� */
enum ITEM_OWNER
{
	IO_UNKNOWN,
	IO_MYSELF_EQUIP,				/* ����Լ����ϵ�װ�� */
	IO_MYSELF_PACKET,				/* ����Լ����ϵİ��� */
	IO_MYSELF_BANK,					/* ����Լ����ϵ������� */
	IO_PLAYEROTHER_EQUIP,			/* ����������ϵ�װ�� */
	IO_ITEMBOX,						/* �򿪵ı����� */
	IO_BOOTH,						/* ���˵Ļ��� */
	IO_MYEXBOX,						/* �Լ��Ľ��׺� */
	IO_OTHEREXBOX,					/* �Է��Ľ��׺� */
	IO_QUESTBOX,					/* ����ݽ��� */
	IO_MYSTALLBOX,					/* �Լ���̯λ�� */
	IO_OTSTALLBOX,					/* �Է���̯λ�� */
	IO_QUESTVIRTUALITEM,			/* �������ģ����⣩��Ʒ��ֻ������ʾ�� */
	IO_PS_SELFBOX,					/* ����Լ��̵� */
	IO_PS_OTHERBOX,					/* ��������̵� */
	IO_ITEMDROP,					/* ������Ʒ */
	IO_TREASUREBOX,					/* �����еģ�ֻ������ʾ */
	IO_TOOLBAR,						/* �������ʾʹ�� */
};

/* ��Ʒ������ */
enum EQUIP_BIND_INFO
{
	FREE_BIND				= 0,	/* �ް� */
	BINDED,			/* �Ѿ��� -- ���˰� */
	BINDED_OFFICAL, /* �ٷ��� */

	GETUP_BIND,		/* ʰȡ�� */
	EQUIP_BIND,		/* װ���� */

	EQUIP_BIND_NO_SECBIND	= 0,
	EQUIP_BIND_TWO			= 1,						/* ʹ�ò��Ͻ��еİ󶨣�ĿǰΪ2���� ���Ժ�����и��߼��İ� */
};

struct Rule_t
{
	BOOL	bCanDrop;									/* �Ƿ�ɶ��� */
	BOOL	bCanOverLay;								/* �Ƿ���ص� */
	BOOL	bCanQuick;									/* �Ƿ�ɷ������� */
	BOOL	bCanSale;									/* �Ƿ���Գ��۸�NPC�̵� */
	BOOL	bCanExchange;								/* �Ƿ���Խ��� */
	BOOL	bCanUse;									/* �Ƿ����ʹ�� */
	BOOL	bPickBind;									/* �Ƿ���ʰȡ� */
	BOOL	bEquipBind;									/* �Ƿ���װ��� */
	BOOL	bUnique;									/* �Ƿ���Ψһ */
	BOOL	bCheck;										/* �Ƿ���Ҫ���� */
	BOOL	bUnRealItem;								/* �Ƿ���������� */
	BOOL	bAccessInBack;								/* �Ƿ�ɴ������� */
	BOOL	bWearOut;									/* �Ƿ����� */
	Rule_t()
	{
		bCanDrop = TRUE;
		bCanOverLay = TRUE;
		bCanQuick = TRUE;
		bCanSale = TRUE;
		bCanExchange = TRUE;
		bCanUse = TRUE;
		bPickBind = TRUE;
		bEquipBind = TRUE;
		bUnique = TRUE;
		bCheck = TRUE;
		bUnRealItem = TRUE;
		bAccessInBack = TRUE;
		bWearOut = TRUE;
	}
};

/* ��Ҫ��UI����ʾ������ */
extern const char	*c_ITEMPROPERTY_NAME;				/* ��Ʒ�� װ������ */
extern const char	*ITEMATTRIBUTE_ICON;				/* װ��ͼ�� */
extern const char	*ITEMATTRIBUTE_CARD;				/* �齫���� */
extern const char	*c_ITEMPROPERTY_LEVEL;				/* ��Ʒ�ȼ� */
extern const char	*ITEMATTRIBUTE_PROFESSION;			/* ְҵ */
extern const char	*ITEMATTRIBUTE_MAXDUR;				/* ����;� */
extern const char	*ITEMATTRIBUTE_CURDUR;				/* ��ǰ�;� */
extern const char	*c_ITEMPROPERTY_PRICE;				/* �۸� */
extern const char	*ITEMATTRIBUTE_STARTLEVEL;			/* �Ǽ� */
extern const char	*c_ITEMPROPERTY_PRODUCER;			/* ���� */
extern const char	*ITEMATTRIBUTE_GEMSNUM;				/* ��ʯ���� */
extern const char	*c_ITEMPROPERTY_DESC;				/* ��ϸ���� */
extern const char	*ITEMATTRIBUTE_DROP_COLOR;			/* ������ɫ */
extern const char	*ITEMATTRIBUTE_EQUIP_TYPE;			/* װ������ */
extern const char	*ITEMATTRIBUTE_EQUIP_BINDINFO;		/* װ������Ϣ */
extern const char	*ITEMATTRIBUTE_EQUIP_BASEATT;		/* ����װ���������� */
extern const char	*ITEMATTRIBUTE_EQUIP_ADDATT;		/* ����װ���������� */
extern const char	*ITEMATTRIBUTE_EQUIP_SKILL_ATTR;	/* ����װ�����Ӽ��ܺ�Ӱ�켼������ */
extern const char	*ITEMATTRIBUTE_EQUIP_GEMSATT;		/* װ����ʯ������ */
extern const char	*ITEMATTRIBUTE_EQUIP_SETINFO;		/* װ������װ�����Ϣ */
extern const char	*ITEMATTRIBUTE_SET_ACCTIVEATTR;		/* ��װ��������� */
extern const char	*ITEMATTRIBUTE_EQUIP_FOREVERATTRINFO;	/* װ�������ã���ħ��������Ϣ */
extern const char	*ITEMATTRIBUTE_EQUIP_TEMPATTRINFO;		/* װ������ʱ����ħ��������Ϣ */
extern const char	*ITEMATTRIBUTE_EQUIP_BASEATT_ADDBIND;	/* ����װ���������ԼӰ� */
/* �����������*/
extern const char	*ITEMATTRIBUTE_EQUIP_CONSTATT;
extern const char	*ITEMATTRIBUTE_EQUIP_CONSTATT_COUNT;			
extern const char	*ITEMATTRIBUTE_EQUIP_CONSTATT_ID;
extern const char	*ITEMATTRIBUTE_EQUIP_CONSTATT_NAME;
extern const char	*ITEMATTRIBUTE_EQUIP_CONSTATT_BASEATT;
extern const char	*ITEMATTRIBUTE_EQUIP_CONSTATT_ACTIVEID1;
extern const char	*ITEMATTRIBUTE_EQUIP_CONSTATT_ACTIVENAME1;
extern const char	*ITEMATTRIBUTE_EQUIP_CONSTATT_ACTIVEID2;
extern const char	*ITEMATTRIBUTE_EQUIP_CONSTATT_ACTIVENAME2;
extern const char	*ITEMATTRIBUTE_EQUIP_CONSTATT_ACTIVEATT;
extern const char	*ITEMATTRIBUTE_EQUIP_CONSTATT_ISACTIVE;
extern const char	*ITEMATTRIBUTE_OTHERUSER_EQUIP_CONSTATT_ISACTIVE;
extern const char	*ITEMATTRIBUTE_EQUIP_CONSTATT_ACTIVEPOINT;
const CHAR	SPLTER_VERTICALBAR = '|';

/* ��Ҫ��UI����ʾ������ */
