#ifndef __GAMEDEFINE_PLAYERSHOP_H__
#define __GAMEDEFINE_PLAYERSHOP_H__

namespace	PLAYER_SHANGDIAN
{
enum STATUS_STALL
{
	STALL_INVALID	= 0,			/* 此柜台还没有开放给玩家使用 */
	STALL_CLOSE,				/* 此柜台已经打烊 */
	STALL_OPEN,				/* 此柜台已经开张 */
};
}
#define MAX_DY_GROUP_PRICE_NUM		10	/* 动态商店组物品价格种类上限 */
#define MAX_DY_PER_GROUP_GOODS_NUM	10	/* 动态商店每组贩卖物品上限 */

enum DY_PRICE_TYPE		/* 动态商店价格类型 */
{
	PRICE_GOLD	= 0,	/* 游戏币 */
	PRICE_CREDIT,		/* 声望 */
	PRICE_HONOR,		/* 荣誉 */
	PRICE_GP,		/* 帮贡 */
	PRICE_ITEM,		/* 物品 */

	PRICE_RMB,		/* 人民币 */
	PRICE_TYPE_NUM,
};
#endif /* __GAMEDEFINE_PLAYERSHOP_H__ */
