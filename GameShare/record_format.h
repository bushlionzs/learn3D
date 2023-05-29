/*$T MapServer/Server/Base/record_format.h GC 1.140 10/10/09 10:07:21 */

/* record_format.h $v1.0 13407899 */
#ifndef _RECORD_FORMAT_H_
#define _RECORD_FORMAT_H_

/*
 * TOL: ;
 * 玩家1GUID（买方GUID）,角色名称,所在地图sceneid,变更类型（0交易，1摆摊）,交易前银币数量,交易后银币数量
 * ;
 * 物品1ID,物品GUID1,物品1变更数量,物品2ID,物品GUID2,物品2变更数量,物品3ID,物品GUID3,物品3变更数量,物品4ID,
 * ;
 * 物品GUID4,物品4变更数量,物品5ID,物品GUID5,物品5变更数量,马匹ID,马匹GUID, ;
 * 玩家2GUID（卖方GUID）,角色名称,所在地图sceneid,变更类型（0交易，1摆摊）,交易前银币数量,交易后银币数量
 * ;
 * 物品1ID,物品GUID1,物品1变更数量,物品2ID,物品GUID2,物品2变更数量,物品3ID,物品GUID3,物品3变更数量,物品4ID,
 * ;
 * 物品GUID4,物品4变更数量,物品5ID,物品GUID5,物品5变更数量,马匹ID,马匹GUID ;
 * Trade 格式为, log类型,
 * 玩家1信息,物品1信息,...物品5信息,pet信息,玩家2信息,物品1信息,...物品5信息,pet信息,
 * ;
 * IOL:GL号,Server号,物品序号,角色GUID,对方GUID,操作类型,最后背包位置,场景号, ;
 * 相关NPC,XPOS,ZPOS,相关商店号(如果是玩家之间填-1),耐久度，镶嵌孔个数 ;
 * 属性类型1，属性1。。。属性类型4，属性4 ;
 * MIL:角色GUID，操作类型，场景，x位置,z位置，任务编号，任务脚本，任务标志 ;
 * 参数0，参数1，参数2，参数3，参数4，参数5，参数6，参数7， ;
 * 完成标志索引，完成标志值，全局任务数据索引，全局任务数据值 ;
 * MOL:参与角色，对象角色，操作类型，货币数量，场景，x位置,z位置 ;
 * POL:参与角色，对象角色，操作类型，场景，x位置,z位置 ,宠物编号 ;
 * SOL:参与角色，操作类型，场景，x位置,z位置,技能编号 ;
 * XOL:参与角色，操作类型，场景，x位置,z位置,技能编号 ;
 * GPL:角色GUID，角色名字，场景，玩法编号，是否组队，组队人数 ;
 * 成员1等级，成员1职业，成员2等级，成员2职业，成员3等级， ;
 * 成员3职业，成员4等级，成员4职业，成员5等级，成员5职业，成员6等级，成员6职业，
 */
static const char	*csRECORD_FORMAT_Quest = "MIL:%u,%d,%d,%.2f,%.2f,%d,%d,%d,%u,%u,%u,%u,%u,%u,%u,%u,%d,%d,%d,%d";
static const char	*csRECORD_FORMAT_Item = "%u,%u,%s,%s,%d,%u,%s,%d,%d,%d,%d,%d,%u,%u,%u,%u,%u,%.2f,%.2f,%d,%u,%d,%d,%d";
static const char	*csRECORD_FORMAT_Equip = "%u,%u,%s,%s,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d";
static const char	*csRECORD_FORMAT_Money = "%u,%u,%s,%d,%d,%d,%d,%d,%.2f,%.2f,%u,%d,%d,%u,%u,%d,%d,%d,%d";
static const char	*csRECORD_FORMAT_Pet = "%u,%u,%d,%d,%.2f,%.2f,%u,%u,%d,%d,%d";
static const char	*csRECORD_FORMAT_Skill = "%u,%d,%d,%.2f,%.2f,%u,%d,%d,%d,%d";
static const char	*csRECORD_FORMAT_Ability = "%u,%d,%d,%.2f,%.2f,%u,%d,%d,%d,%d";
static const char	*csRECORD_FORMAT_GameWay = "%u,%s,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d";
static const char	*csRECORD_FORMAT_IllegalEnter = "%u,%s,%d,%d,%d,%d,%d";
static const char	*csRECORD_FORMAT_IB = "%u,%u,%s,%d,%d,%d,%d,%d,%d,%d,%d";
static const char	*csRECORD_FORMAT_Cheat = "%s,%u,%d,%u,%u,%f,%f,%u,%d,%d";
static const char	*csRECORD_FORMAT_Trade = "%u,%s,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%u,%u,%u,%s,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%u,%u,%d,%d";
static const char	*csRECORD_FORMAT_WorlShop = "%u,%u,%d,%d,%u,%d,%d,%d,%d,%d,%u,%u,%d,%d";
static const char	*csRECORD_FORMAT_ReturnToChild = "%d,%u,%u,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%u,%u,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d";
static const char	*csRECORD_FORMAT_PetSkillChange = "%u,%u,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%u,%u,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d";
static const char	*csRECORD_FORMAT_IBMoney = "%u,%s,%d,%u,%u,%u,%d,%u,%u,%u,%d,%d";
static const char	*csRECORD_FORMAT_IBCost = "%u,%s,%d,%u,%u,%u,%d,%u,%d,%d,%d";
static const char	*csRECORD_FORMAT_StockTrade = "%u,%u,%d,%d,%d,%d,%d,%u,%u,%d,%d";
static const char	*csRECORD_FORMAT_StockAcc = "%u,%d,%d,%d,%d,%d,%d,%d";
static const char	*csRECORD_FORMAT_Guild = "%d,%s,%d,%d,%d,%d,%d,%d,%d";
static const char	*csRECORD_FORMAT_ZhuanJing = "%u,%d,%d,%.2f,%.2f,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d";

#endif /* _RECORD_FORMAT_H_??? */
