/*$T Client/Game/ItemCommon.h GC 1.140 08/23/09 04:52:37 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#pragma once

/* 物品规则 */
enum
{
	RULE_DROP		= 0,			/* 是否可丢弃 */
	RULE_OVERLAY,					/* 是否可重叠 */
	RULE_QUICK,						/* 是否可放入快捷栏 */
	RULE_SALE,						/* 是否可以出售给NPC商店 */
	RULE_EXCHANGE,					/* 是否可以交易 */
	RULE_USE,						/* 是否可以使用 */
	RULE_PICKBIND,					/* 是否是拾取邦定 */
	RULE_EQUIPBIND,					/* 是否是装备邦定 */
	RULE_UNIQUE,					/* 是否是唯一 */
	RULE_IDENT,						/* 是否需要鉴定 　 */
	RULE_DUMMYITEM,					/* 是否虚拟道具 　 */
	RULE_BANK,						/* 是否可以存入银行 　 */
	RULE_CONSUME,					/* 是否消耗 */
};

/* 物品归属 */
enum ITEM_OWNER
{
	IO_UNKNOWN,
	IO_MYSELF_EQUIP,				/* 玩家自己身上的装备 */
	IO_MYSELF_PACKET,				/* 玩家自己身上的包中 */
	IO_MYSELF_BANK,					/* 玩家自己身上的银行中 */
	IO_PLAYEROTHER_EQUIP,			/* 其他玩家身上的装备 */
	IO_ITEMBOX,						/* 打开的宝箱中 */
	IO_BOOTH,						/* 商人的货架 */
	IO_MYEXBOX,						/* 自己的交易盒 */
	IO_OTHEREXBOX,					/* 对方的交易盒 */
	IO_QUESTBOX,					/* 任务递交盒 */
	IO_MYSTALLBOX,					/* 自己的摊位盒 */
	IO_OTSTALLBOX,					/* 对方的摊位盒 */
	IO_QUESTVIRTUALITEM,			/* 任务奖励的（虚拟）物品，只用于显示。 */
	IO_PS_SELFBOX,					/* 玩家自己商店 */
	IO_PS_OTHERBOX,					/* 其他玩家商店 */
	IO_ITEMDROP,					/* 掉落物品 */
	IO_TREASUREBOX,					/* 宝箱中的，只用于显示 */
	IO_TOOLBAR,						/* 快捷栏显示使用 */
};

/* 物品绑定属性 */
enum EQUIP_BIND_INFO
{
	FREE_BIND				= 0,	/* 无绑定 */
	BINDED,			/* 已经绑定 -- 个人绑定 */
	BINDED_OFFICAL, /* 官方绑定 */

	GETUP_BIND,		/* 拾取绑定 */
	EQUIP_BIND,		/* 装备绑定 */

	EQUIP_BIND_NO_SECBIND	= 0,
	EQUIP_BIND_TWO			= 1,						/* 使用材料进行的绑定，目前为2级绑定 ，以后可能有更高级的绑定 */
};

struct Rule_t
{
	BOOL	bCanDrop;									/* 是否可丢弃 */
	BOOL	bCanOverLay;								/* 是否可重叠 */
	BOOL	bCanQuick;									/* 是否可放入快捷栏 */
	BOOL	bCanSale;									/* 是否可以出售给NPC商店 */
	BOOL	bCanExchange;								/* 是否可以交易 */
	BOOL	bCanUse;									/* 是否可以使用 */
	BOOL	bPickBind;									/* 是否是拾取邦定 */
	BOOL	bEquipBind;									/* 是否是装备邦定 */
	BOOL	bUnique;									/* 是否是唯一 */
	BOOL	bCheck;										/* 是否需要鉴定 */
	BOOL	bUnRealItem;								/* 是否是虚拟道具 */
	BOOL	bAccessInBack;								/* 是否可存入银行 */
	BOOL	bWearOut;									/* 是否消耗 */
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

/* 需要在UI上显示的属性 */
extern const char	*c_ITEMPROPERTY_NAME;				/* 物品名 装备名称 */
extern const char	*ITEMATTRIBUTE_ICON;				/* 装备图标 */
extern const char	*ITEMATTRIBUTE_CARD;				/* 麻将牌型 */
extern const char	*c_ITEMPROPERTY_LEVEL;				/* 物品等级 */
extern const char	*ITEMATTRIBUTE_PROFESSION;			/* 职业 */
extern const char	*ITEMATTRIBUTE_MAXDUR;				/* 最大耐久 */
extern const char	*ITEMATTRIBUTE_CURDUR;				/* 当前耐久 */
extern const char	*c_ITEMPROPERTY_PRICE;				/* 价格 */
extern const char	*ITEMATTRIBUTE_STARTLEVEL;			/* 星级 */
extern const char	*c_ITEMPROPERTY_PRODUCER;			/* 作者 */
extern const char	*ITEMATTRIBUTE_GEMSNUM;				/* 宝石数量 */
extern const char	*c_ITEMPROPERTY_DESC;				/* 详细解释 */
extern const char	*ITEMATTRIBUTE_DROP_COLOR;			/* 掉落颜色 */
extern const char	*ITEMATTRIBUTE_EQUIP_TYPE;			/* 装备类型 */
extern const char	*ITEMATTRIBUTE_EQUIP_BINDINFO;		/* 装备绑定信息 */
extern const char	*ITEMATTRIBUTE_EQUIP_BASEATT;		/* 所有装备基本属性 */
extern const char	*ITEMATTRIBUTE_EQUIP_ADDATT;		/* 所有装备附加属性 */
extern const char	*ITEMATTRIBUTE_EQUIP_SKILL_ATTR;	/* 所有装备附加技能和影响技能属性 */
extern const char	*ITEMATTRIBUTE_EQUIP_GEMSATT;		/* 装备宝石的属性 */
extern const char	*ITEMATTRIBUTE_EQUIP_SETINFO;		/* 装备的套装组合信息 */
extern const char	*ITEMATTRIBUTE_SET_ACCTIVEATTR;		/* 套装激活的属性 */
extern const char	*ITEMATTRIBUTE_EQUIP_FOREVERATTRINFO;	/* 装备的永久（附魔）属性信息 */
extern const char	*ITEMATTRIBUTE_EQUIP_TEMPATTRINFO;		/* 装备的临时（附魔）属性信息 */
extern const char	*ITEMATTRIBUTE_EQUIP_BASEATT_ADDBIND;	/* 所有装备基本属性加绑定 */
/* 星座属性相关*/
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

/* 需要在UI上显示的属性 */
