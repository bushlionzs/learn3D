/*$T MapServer/Server/Base/act_define.h GC 1.140 10/10/09 10:07:20 */

/* act_define.h $v1.0 97203 */
#ifndef _ACT_DEFINE_H_
#define _ACT_DEFINE_H_

enum eSkillActType
{
	eSkillAct_Unknow		= 0,			/* 未知技能操作 */
	eSkillAct_ScriptTrain		= 10,			/* 技能学习 */
	eSkillAct_LevelUp		= 20,			/* 技能升级 */
	eSkillAct_ScriptAbandon		= 30,			/* 技能放弃 */
	eSkillAct_ScriptChangeFaction	= 31,			/* 脚本调用ChangeMenpai */
	eSkillAct_GMModify		= 40,			/* 通过GM命令 学习 */
	eSkillAct_GuildSkillLevelUp_Guild	= 50,			/* 帮会技能（天赋修行）升级 帮会*/
	eSkillAct_GuildSkillLevelUp_Person		= 51,			/* 帮会技能（天赋修行）升级 个人*/
	eSkillAct_InherenceBalance_LevelUp		= 60,			/* 天赋平衡升级*/
	eSkillAct_NUM
};
enum eAbilityActType
{
	eAbilityAct_Unknow		= 0,			/* 未知技能操作 */
	eAbilityAct_ScriptTrain		= 10,			/* 生活技能学习 */
	eAbilityAct_LevelUp		= 20,			/* 生活技能升级 */
	eAbilityAct_ScriptAbandon	= 30,			/* 生活技能放弃 */
	eAbilityAct_GMModify		= 40,			/* 通过GM命令 学习 */
	eAbilityAct_GMModifyAll		= 41,			/* 通过GM命令学习所有 */
	eAbilityAct_NUM
};
enum eCurrencyActType
{
	eCurrencyAct_Unknow				= 0,	/* 未知 */
	eCurrencyAct_SaveBank				= 1,	/* 银行存 */
	eCurrencyAct_TakeMoneyAtBank			= 2,	/* 银行取 */
	eCurrencyAct_ExchangeIncome			= 3,	/* 货币交易收入 */
	eCurrencyAct_ExchangeOutcome			= 4,	/* 货币交易支出 */
	eCurrencyAct_PrivatelyExchangeIncome		= 5,	/* 货币通过摊位交易收入 */
	eCurrencyAct_PrivatelyExchangeOutcome		= 6,	/* 货币通过摊位交易支出 */
	eCurrencyAct_PrivatelyExchangeTaxOutcome	= 7,	/* 货币通过摊位税收支出 */
	eCurrencyAct_PlayerShopExchangeOutcome		= 8,	/* 货币通过玩家商店交易货物支出,钱入玩家商店 */
	eCurrencyAct_BuyPlayerShopOutcome		= 9,	/* 货币通过交易玩家商店支出 */
	eCurrencyAct_CreatePlayerShopOutcome		= 10,	/* 货币通过创建玩家商店支出 */
	eCurrencyAct_PlayerShopSave			= 11,	/* 玩家商店存 */
	eCurrencyAct_PlayerShowTake			= 12,	/* 玩家商店取 */
	eCurrencyAct_ShopCost				= 13,	/* 商店购买支出 */
	eCurrencyAct_ShopSell				= 14,	/* 商店出售收入 */
	eCurrencyAct_ShopRepair				= 15,	/* 商店修理支出 */
	eCurrencyAct_ShopSpecialRepair			= 16,	/* 商店特修支出 */
	eCurrencyAct_TrainAbilityCost			= 17,	/* 学习生活技能支出 */
	eCurrencyAct_TrainSkillCost			= 19,	/* 学习战斗技能 */
	eCurrencyAct_CallScriptCost			= 20,	/* 脚本调用金钱消耗 */
	eCurrencyAct_CallScriptIncome			= 21,	/* 脚本调用金钱收入 */
	eCurrencyAct_DieCost				= 22,	/* 死亡金钱惩罚 */
	eCurrencyAct_PetCost				= 23,	/* 宠物金钱消耗 */
	eCurrencyAct_CreateGuildCost			= 24,	/* 创建帮会金钱消耗 */
	eCurrencyAct_GuildLevelUpCost			= 25,	/* 帮会升级消耗 */
	eCurrencyAct_ChallengeKingCost			= 26,	/* 挑战国王消耗 */
	eCurrencyAct_ApplyActAsKing			= 27,	/* 申请当国王 */
	eCurrencyAct_GuildLevelUpFailedHandBack		= 28,	/* 帮会升级失败还钱 */
	eCurrencyAct_CreateGuildFailedHandBack		= 29,	/* 创建帮会金钱失败还钱 */
	eCurrencyAct_ApplyKingFailedHandBack		= 30,	/* 申请国王失败还钱 */
	eCurrencyAct_CountryDonate			= 31,	/* 国家捐赠 */
	eCurrencyAct_CountryDelate			= 32,	/* 国家弹劾 */
	eCurrencyAct_DrillCost				= 33,	/* 加孔金钱消耗 */
	eCurrencyAct_EquipLevelUpCost			= 34,	/* 装备升级消耗金钱 */
	eCurrencyAct_EquipRemouldCost			= 35,	/* 装备改造金钱消耗 */
	eCurrencyAct_FoundEquipCost			= 36,	/* 装备打造金钱消耗 */
	eCurrencyAct_EquipInlayCost			= 37,	/* 装备镶嵌金钱消耗 */
	eCurrencyAct_EquipBindCost			= 40,	/* 装备绑定金钱消耗 */
	eCurrencyAct_EquipChangeCard			= 41,	/* 装备换牌金钱消耗 */
	eCurrencyAct_GMmodify				= 42,	/* GM 修改 */
	eCurrencyAct_HorseMating			= 43,	/* 马交配 */
	eCurrencyAct_HorseFindingMating			= 44,	/* 发布骑乘征友消耗 [6/16/2008 wuwenbin] */
	eCurrencyAct_HorseRiseHappy			= 46,	/* 增加马的快乐度 */
	eCurrencyAct_MarryCost				= 47,	/* 结婚消耗 */
	eCurrencyAct_DivorceCost			= 48,	/* 离婚消耗 */
	eCurrencyAct_PresentWeddingRB			= 49,	/* 参加婚礼的红包 */
	eCurrencyAct_CashAccountToChar			= 50,	/* 从帐户转到角色的现金 */
	eCurrencyAct_ChatCost				= 51,	/* 聊天消耗 */
	eCurrencyAct_ProxyTrain				= 52,	/* 代练消耗 */
	eCurrencyAct_Exchange				= 53,	/* 金钱兑换 */
	eCurrencyAct_TakeCountryFinancingAtBank		= 54,	/* 提取国家资金 */
	eCurrencyAct_CashVendueCost			= 55,	/* 现金商店寄售预扣 */
	eCurrencyAct_CashVendueFailedHandBack		= 56,	/* 现金商店寄售失败返回 */
	eCurrencyAct_CashShopBuyCost			= 57,	/* 现金商店购买预扣 */
	eCurrencyAct_CashShopBuyFailedHandBack		= 58,	/* 现金商店购买失败返回 */
	eCurrencyAct_CashShopBuySuccessed		= 59,	/* 现金商店购买成功加现金 */
	eCurrencyAct_CashShopRetakeAtBank		= 60,	/* 现金寄售后通过银行领取现金 */
	eCurrencyAct_OnHandSillerShopRetakeAtBank	= 61,	/* 现金寄售后通过银行领取现银 */
	eCurrencyAct_EquipColorChange			= 62,	/* 黄装升紫装花费 */
	eCurrencyAct_EquipPurpleWashAttr		= 63,	/* 紫装洗属性花费 */
	eCurrencyAct_EquipGemLevelUpCost		= 64,	/* 宝石升级消耗 */
	eCurrencyAct_EquipGemCompoundCost		= 65,	/* 宝石合成消耗 */
	eCurrencyAct_EquipGemTeardown			= 66,	/* 宝石拆卸花费 */
	eCurrencyAct_EquipCopyCost			= 67,	/* 装备复制花费 */
	eCurrencyAct_ExchangeGoldIncome			= 68,	/* 现金交易收入 */
	eCurrencyAct_ExchangeGoldOutcome		= 69,	/* 现金交易支出 */
	eCurrencyAct_PrivatelyExchangeIncomeGold = 70,	/* 货币通过摊位交易收入，现金 */
	eCurrencyAct_PrivatelyExchangeOutcomeGold = 71, /* 货币通过摊位交易支出 */
	eCurrencyAct_2v2MarkScriptAdd			= 72,	/* 2v2战场积分增加 */
	eCurrencyAct_2v2MarkScriptSub			= 73,	/* 2v2战场积分减少 */
	eCurrencyAct_PrivatelyExchangeTax		= 74,	/* 摊位交易收税，现银 */
	eCurrencyAct_PrivatelyExchangeTaxGold	= 75,	/* 摊位交易收税，现金 */
	eCurrencyAct_EquipRecallAddMoney		= 76,	/* 装备回收得到的钱*/
	eCurrencyAct_ScriptChangeGP				= 77,	/* 脚本调用，帮贡改变 */
	eCurrencyAct_ServerSyncGP				= 78,	/* GL同步帮贡值 */
	eCurrencyAct_CharGoldToStock			= 79,	/* 股票账户充值扣除，现金 */
	eCurrencyAct_CharSillerToStock			= 80,	/* 股票账户充值扣除，现银 */
	eCurrencyAct_CharGoldToStockFailed		= 81,	/* 股票账户充值失败，回滚现金 */
	eCurrencyAct_CharSillerToStockFailed	= 82,	/* 股票账户充值失败，回滚现银 */
	eCurrencyAct_StockGoldToChar			= 83,	/* 股票账户现金转账到角色，增加现金 */
	eCurrencyAct_StockSillerToChar			= 84,	/* 股票账户现银转账到角色，增加现银 */
	eCurrencyAct_ScriptChangeMerit			= 85,	/* 脚本调用，改变帮会功德值 */
	eCurrencyAct_GMChangeMerit				= 86,	/* GM命令改变帮会功德值 */
	eCurrencyAct_ServerSyncMerit			= 87,	/* GL同步帮会功德值 */
	eCurrencyAct_StockRegisterCostMoney		= 88,	/* 股票系统开户收费，扣除现银 */
	eCurrencyAct_StockRegisterFailedAddMoney= 89,	/* 股票系统开户失败，返回现银 */
	eCurrencyAct_BlueAddCost				= 90,	/* 蓝属性附加的花费 */
	eCurrencyAct_StockAutoSaleCostGold		= 91,	// 委托卖金: 扣除本金和手续费 现金
	eCurrencyAct_StockAccDieAddMoney		= 92,	// 股票账户消亡: 资金返回角色
	eCurrencyAct_StockSysBuyGold			= 93,	// 股票系统：系统工具购买现金
	eCurrencyAct_EquipSwitch				= 94,	// 装备转化花费
	eCurrencyAct_MentalBuyItem				= 95,	/* 答题购买道具 */
	eCurrencyAct_GuildSkillLevelUpCost			= 96,	/* 帮会天赋技能升级消耗 */
	eCurrencyAct_BlueProduceCost      = 97,		/*橙装打造消耗*/
	eCurrencyAct_ConstBindCost	= 98,		/*星座铭刻*/
	eCurrencyAct_EquipHonorBindCost = 99,		/*荣誉铭刻*/

	/* 100->200为玩法中使用人民币的操作类型 */
	eCurrencyAct_TestFee				= 100,	/* 测试费 */
	eCurrencyAct_Prize				= 101,	/* 领奖 */
	eCurrencyAct_ScriptChangeActivity		= 102,	/* 脚本调用，改变帮会活跃度 */
	/* 300->400为脚本玩法等操作类型 */
	/* 花钱*/
	eCurrencyAct_Relive				= 300, /*复活*/
	eCurrencyAct_NormalMission		= 301, /*一般任务*/
	eCurrencyAct_ChuanSong			= 302, /*传送*/
	eCurrencyAct_Betray				= 303, /*叛国*/
	eCurrencyAct_Levelup			= 304, /*升级*/
	eCurrencyAct_Hunyin				= 305, /*婚姻*/
	eCurrencyAct_Wuting				= 306, /*舞厅*/
	eCurrencyAct_GoldDel			= 307, /* 现金清除道具清除现金 */
	eCurrencyAct_SuperSale			= 308, /* 现金促销活动 */
	eCurrencyAct_OfflineTrain		= 309, /* 离线代练 */
	eCurrencyAct_SubscribeToGuild	= 310, /* 捐献帮会金钱 */

	eCurrencyAct_Wulongyin_mojun	= 311, /* 五龙印兑换-天降魔君 */
	eCurrencyAct_Wulongyin_wabao	= 312, /* 五龙印兑换-挖宝大作战 */
	eCurrencyAct_Wulongyin			= 313, /* 五龙印兑换 */
	eCurrencyAct_Wulongyin_huapi	= 314, /* 五龙印兑换-画皮 */
	eCurrencyAct_Wulongyin_qiannv	= 315, /* 五龙印兑换-倩女幽魂 */
	eCurrencyAct_Qiangjiang			= 316, /* 购买生命琼浆 */
	eCurrencyAct_Shangxiang			= 317, /* 上香请愿 */
	eCurrencyAct_Baoxiang			= 318, /* 疯狂宝箱 */
	eCurrencyAct_Xingbing_loulan	= 319, /* 新兵速成 楼兰 */
	eCurrencyAct_Xingbing_tianshan	= 320, /* 新兵速成 天山 */
	eCurrencyAct_Xingbing_kunlun	= 321, /* 新兵速成 昆仑 */
	eCurrencyAct_Xingbing_dunhuang	= 322, /* 新兵速成 敦煌 */
	eCurrencyAct_Mojun				= 323, /* 天降魔君 */
	eCurrencyAct_Baolong			= 324, /* 暴龙大作战 */
	eCurrencyAct_GuildSuCheng		= 325, /* 帮会速成 */
	eCurrencyAct_ITEM_OTHER_195		= 326, /* 新星麒麟大礼包 */
	eCurrencyAct_ITEM_OTHER_197		= 327, /* 天尊麒麟金卡” */
	eCurrencyAct_DynamicShopCost	= 328,	/* 动态价格商店购买支出 */
	eCurrencyAct_GuildSendMail		= 329,  /* 帮主群发邮件扣除现银 */

	eCurrencyAct_NUM
};
enum eQuestActType
{
	eQuestAct_Unknow				= 0,	/* 未知任务操作 */
	eQuestAct_AddQuest				= 10,	/* 增加任务 */
	eQuestAct_DelQuest				= 20,	/* 删除任务（有可能是完成后删除） */
	eQuestAct_ParamChange				= 30,	/* 任务参数变化 */
	eQuestAct_DoneFlag				= 40,	/* 任务完成标志变化 */
	eQuestAct_DataChange				= 50,	/* 任务全局数据变化 */
	eQuestAct_CycleDoneFlag				= 60,	/* 循环任务完成一次标志 */

	eQuestAct_NUM
};
enum eItemActType
{
	eItemAct_Unknow					= 0,	/* 未知物品拾取 */
	eItemAct_TempCreateFromMonster			= 1,	/* 创建掉落临时数据 */
	eItemAct_CreateFromMonster			= 2,	/* 怪物掉落，生成到掉落包 */
	eItemAct_CreateScriptToBox			= 3,	/* 由脚本创建到掉落包，一般是生长点类型 */
	eItemAct_PickFromMonster			= 4,	/* 怪物掉落物品拾取,指到角色身上的创建 */
	eItemAct_PickFromGrowPoint			= 5,	/* 采集拾取,指到角色身上的创建 */
	eItemAct_PickFromPerson				= 6,	/* 人物掉落物品拾取,指到角色身上的创建 */
	eItemAct_CreateFromScript			= 7,	/* 脚本给与物品 */
	eItemAct_CreateFromAbilityScript		= 8,	/* 生活技能相关脚本给予 */
	eItemAct_CreateGM				= 9,	/* GM命令 */
	eItemAct_CreateAbilityComposite			= 10,	/* 宝石合成 */

	eItemAct_CreateAndExtirpate			= 11,	/* 宝石摘除的重新生成 */
	eItemAct_CreateFromShop				= 12,	/* 商店的创建 */
	eItemAct_CreateToStack				= 13,	/* 创建后与原背包物品堆叠 */
	eItemAct_CreateSplit				= 14,	/* 拆分物品时物品的创建 */
	eItemAct_ExchangeToOther			= 15,	/* 物品交易, */
	eItemAct_StallBoxExchange			= 16,	/* 摊位交易 */
	eItemAct_PlayerShopExchange			= 17,	/* 玩家商店 */
	eItemAct_PlayerShopMarket			= 18,	/* 玩家商店上架 */
	eItemAct_PlayerShowMarketGoWay			= 19,	/* 玩家商店下架 */
	eItemAct_InventorySplitDest			= 20,	/* 物品背包拆分目的地 */
	eItemAct_InventorySplitSrc			= 21,	/* 物品背包拆分源头 */
	eItemAct_BankSplitDest				= 22,	/* 银行拆分 */
	eItemAct_BankSplitSrc				= 23,	/* 银行拆分 */
	eItemAct_InventoryStackDest			= 24,	/* 背包物品堆叠目的地 */
	eItemAct_InventoryStackSrc			= 25,	/* 背包物品堆叠源 */
	eItemAct_BankStack				= 26,	/* 银行物品堆叠 */
	eItemAct_SellSplit				= 27,	/* 出售部分商品时的拆分 */
	eItemAct_BankRemoveItem				= 28,	/* 银行移出物品 */
	eItemAct_InventoryRemoveItem			= 29,	/* 从背包移出物品 */
	eItemAct_BankAcquireItem			= 30,	/* 银行获得物品 */
	eItemAct_InventoryAcquireItem			= 31,	/* 背包获得物品 */

	eItemAct_BankStackDest				= 32,	/* 银行物品合并目的 */
	eItemAct_BankStackSrc				= 33,	/* 银行物品合并源头 */
	eItemAct_InventoryToBankExchange		= 34,	/* 背包交换物品到银行物品 */
	eItemAct_BankToInventoryExchange		= 35,	/* 银行交换物品到背包 */
	eItemAct_InventoryToBankRemove			= 36,	/* 背包物品移动到银行 */
	eItemAct_OpenBoxCreate				= 37,	/* 开宝箱得物品 */
	eItemAct_CaptureBeastieCreate			= 38,	/* 捕获小动物得物品 */
	eItemAct_DrillConsume				= 39,	/* 加孔物品消耗 */
	eItemAct_EquipLevelUpConsume			= 40,	/* 升星消耗物品 */
	eItemAct_EquipBindConsume			= 41,	/* 绑定消耗物品 */
	eItemAct_EquipExchangeCardConsume		= 42,	/* 换牌消耗物品 */
	eItemAct_CraftCreateFromStuff			= 43,	/* 打造 */
	eItemAct_CraftConsume				= 44,	/* 打造材料消耗 */
	eItemAct_DecompoundRemove			= 45,	/* 拆解掉 */
	eItemAct_DecomposeAcquireStuff			= 46,	/* 拆解获得材料 */
	eItemAct_RemouldConsume				= 47,	/* 改造物品消耗 */
	eItemAct_SpecialFixConsume			= 48,	/* 特修物品消耗 */
	eItemAct_Drill					= 49,	/* 加孔 */
	eItemAct_EquipLevelUp				= 50,	/* 升星 */
	eItemAct_EquipBind				= 51,	/* 绑定 */
	eItemAct_EquipExchangeCard			= 52,	/* 换牌 */
	eItemAct_CraftCreate				= 53,	/* 打造 */
	eItemAct_Decompound				= 54,	/* 拆解 */
	eItemAct_Remould				= 55,	/* 改造 */

	eItemAct_SpecialFix				= 56,	/* 特修 */
	eItemAct_Repair					= 57,	/* 物品修理, */
	eItemAct_UseGemAndRemove			= 58,	/* 宝石使用时移除 */
	eItemAct_UseGemAndLost				= 59,	/* 宝石合成丢失 */
	eItemAct_Discard				= 60,	/* 玩家主动丢弃 */
	eItemAct_GemCompoundConsume			= 61,	/* 宝石合成的物品消耗 */
	eItemAct_AbilityConsume				= 62,	/* 生活技能物品消耗 */
	eItemAct_ScriptDelete				= 63,	/* 从脚本删除物品 */
	eItemAct_ChangeHairConsume			= 64,	/* 改变发型消耗 */
	eItemAct_DiePunish				= 65,	/* 死亡惩罚 */
	eItemAct_InlayWasting				= 66,	/* 物品镶嵌损失 */
	eItemAct_MachineWasting				= 67,	/* 机械制造损失 */
	eItemAct_DiscardEquip				= 68,	/* 玩家主动丢弃已装备上的物品 */
	eItemAct_DiscardBank				= 69,	/* 玩家主动丢弃银行装备 */
	eItemAct_Use					= 70,	/* 玩家主动使用 */
	eItemAct_UseReelConsume				= 71,	/* 卷轴使用消耗 */
	eItemAct_SystemGiveBack				= 72,	/* 系统返回 */
	eItemAct_DelFromSoldList				= 73,	/* 从回购列表中删除物品 */
	eItemAct_ExchangeEquipToBank			= 74,	/* 装备交换物品到银行物品 */
	eItemAct_ExchangeBankToBank			= 75,	/* 银行交换物品到银行物品 */
	eItemAct_ExchangeInventoryToEquip		= 76,	/* 背包交换物品到装备物品 */
	eItemAct_ExchangeEquipToInventory		= 77,	/* 装备交换物品到背包物品 */
	eItemAct_ExchangeInventoryToInventory		= 78,	/* 背包交换物品到背包物品 */
	eItemAct_BoxRecycle				= 79,	/* ItemBox回收 */
	eItemAct_SkillConsume				= 80,	/* 技能消耗 */
	eItemAct_SkillTrain				= 81,	/* 技能学习 */
	eItemAct_QuestScriptDel				= 82,
	eItemAct_MarryConsume				= 83,	/* 结婚消耗 */
	eItemAct_CatchHorseConsume			= 84,	/* 捉马物品消耗 */
	eItemAct_CreateByPresentWedding			= 85,	/* 参加婚礼赠送的喜糖 */
	eItemAct_DropWedding				= 86,	/* 婚礼掉落的物品 */

	eItemAct_EquipCLRChangeDelGem			= 87,	/* 黄装升紫装删除宝石 */
	eItemAct_EquipCLRChangeDelYellow		= 88,	/* 黄装升紫装删掉黄装 */
	eItemAct_EquipCLRChangeCreate			= 89,	/* 黄装升紫装创建紫装 */
	eItemAct_EquipPurleWashDelGem			= 90,	/* 紫装洗属性删掉宝石 */
	eItemAct_EquipPurleWashChange			= 91,	/* 紫装洗属性属性改变 */
	eItemAct_GemLevelUpDestorySelf			= 92,	/* 宝石升级删掉当前宝石 */
	eItemAct_GemLevelUpConsume			= 93,	/* 宝石升级删掉所需宝石 */
	eItemAct_GemLevelUpResult			= 94,	/* 宝石升级得到产出宝石 */
	eItemAct_GemCompoundDestorySelf			= 95,	/* 宝石合成删除宝石 */
	eItemAct_GemCompoundResult			= 96,	/* 宝石合成得到产出宝石 */
	eItemAct_GemTeardownConsume			= 97,	/* 宝石拆卸删掉所需物品 */
	eItemAct_EquipCopyConsume			= 98,	/* 装备复制删掉所需物品 */
	eItemAct_EquipFushonCreate			= 99,	/* 皇家秘银熔炼，生成物品 */
	eItemAct_EquipFushonConsume			= 100,	/* 皇家秘银熔炼，消耗物品 */
	eItemAct_EquipFushonReback			= 101,	/* 皇家秘银熔炼，退回物品 */
	eItemAct_GemTeardownAddGem			= 102,	/* 宝石拆卸添加宝石 */
	eItemAct_EquipCopyDelYellow			= 103,	/* 装备养成删掉黄色装备 */
	eItemAct_EquipCopyCreatePur			= 104,	/* 装备复制生成紫色装备 */
	eItemAct_EquipRecallDel				= 105,	/* 装备回收删除装备 */
	eItemAct_TransItemUse				= 106, /* 传送符使用时消耗 */
	eItemAct_GoldDel_ItemUse			= 107, /* 清除现金道具消耗 */
	eItemAct_BlueIn_EquipDel			= 108, /* 蓝属性吸收装备删除 */
	eItemAct_BlueIn_ItemDel				= 109, /* 蓝属性吸收物品删除 */
	eItemAct_BlueAdd_ItemDel			= 110, /* 蓝属性附加物品删除 */	
	eItemAct_BlueIn_OldItemDel			= 111, /* 蓝属性吸收能量球替换掉老的能量球 */
	eItemAct_BlueIn_NewItemCreate		= 112, /* 蓝属性吸收生成新的能量球 */
	eItemAct_Equip_Transform			= 113,
	eItemAct_MoveInSoldContainer		= 114, /* 在回购列表中移动物品，不用参与日志统计 */
	eItemAct_AddToSoldList				= 115, /* 向回购列表增加物品 */
	eItemAct_ChangeFace				= 116, /* 整容，消耗物品*/
	eItemAct_BlueSyn_ItemDel        = 117,/*蓝属性合成物品删除*/
	eItemAct_GuildSkillTrain				= 118,	/* 帮会技能学习 */
	eItemAct_BlueProdudce_NewItemCreate = 119,/*橙装打造生成物品*/
	eItemAct_BlueProdudce_DeleteItem    = 220,/*橙装打造删除物品*/
	eItemAct_InherenceBalanceTrain				= 221,	/* 天赋平衡学习 */
	eItemAct_ConstBind_DeleteItem       =222,/*星座铭刻消耗物品*/
	eItemAct_RideCompose_DeleteItem       =223,/*骑乘炼化消耗物品*/
	eItemAct_HonorBind_DeleteItem       =224,/*荣誉铭刻消耗物品*/
	eItemAct_EquipHonorBind				= 225,	/* 荣誉铭刻 */
	eItemAct_NUM,
};
enum eWorldShopCashActType
{
	eWorldShopCashAct_Unknow			= 0,	/* 未知任务操作 */
	eWorldShopCashAct_RequestSell,			/* 玩家请求卖现金 */
	eWorldShopCashAct_MarketSuccessed,		/* 现金上架成功 */
	eWorldShopCashAct_MarketFailed,			/* 现金上架失败 */
	eWorldShopCashAct_MarketReturnNullConnecter,	/* 返回上架结果时GameConnector指针为空 */
	eWorldShopCashAct_MarketReturnNullHuman,	/* 返回上架结果时Human指针为空 */
	eWorldShopCashAct_MarketReturnNullMap,		/* 返回上架结果时Map指针为空 */
	eWorldShopCashAct_MarketReturnNullGamePlayer,	/* 返回上架结果时Player指针为空 */

	eWorldShopCashAct_RequestBuy,			/* 玩家请求买现金 */
	eWorldShopCashAct_BuySuccessed,			/* 购买成功 */
	eWorldShopCashAct_BuyFailed,			/* 购买失败 */
	eWorldShopCashAct_BankTakeReturnNullPlayer,	/* 银行领取时GameConnector指针为空 */
	eWorldShopCashAct_BankTakeReturnNullGamePlayer, /* 银行领取时HUMAN指针为空 */
	eWorldShopCashAct_BankTakeReturnNullScene,	/* 银行领取时SCENE指针为空 */
	eWorldShopCashAct_BankTakeReturnNullHuman,	/* 银行领取时PLAYER指针为空 */
	eWorldShopCashAct_BankTakeSuccessed,		/* 银行领取时成功 */
	eWorldShopCashAct_NullUser,			/* pUser为空 */
	eWorldShopCashAct_ClearCash,			/* 从商店中清除寄售现金 */
	eWorldShopCashAct_SellTimeoutReturnToBank,	/* 寄售超时，现金从商店转入银行 */
	eWorldShopCashAct_SystemBuy,			/* 系统回购，现金从商店转入银行 */
	eWorldShopCashAct_NullShop,			/* Shop为空 */
	eWorldShopCashAct_NullSrvConnecter,		/* ServerPlayer为空 */
	eWorldShopCashAct_ShopFull,			/* 商店满 */
	eWorldShopCashAct_BankFull,			/* 银行满 */
	eWorldShopCashAct_UserFull,			/* 玩家在该商店中的寄售货物已达到上限 */
	eWorldShopCashAct_ClearInTheBank,		/* 从银行中清除寄售现金 */
	eWorldShopCashAct_LoadShopFromDB,		/* 启动时从DB中实际LOAD一条商店数据 */
	eWorldShopCashAct_LoadBankFromDB,		/* 启动时从DB中实际LOAD一条银行数据 */
	eWorldShopCashAct_ShouldLoadShopFromDB,		/* 启动时从DB中应该LOAD的一条商店数据 */
	eWorldShopCashAct_ShouldLoadBankFromDB,		/* 启动时从DB中应该LOAD的一条银行数据 */
	eWorldShopCashAct_AddShopFailed,		/* 加入商店失败 */
	eWorldShopCashAct_DelShopFailed,		/* 从商店删除时失败 */
	eWorldShopCashAct_AddBankFailed,		/* 加入银行失败 */
	eWorldShopCashAct_NUM
};
enum eEquipActType
{
	eEquipAct_Unknow				= 0,	/* 未知任务操作 */
	eEquipAct_LevelUpSuccessed			= 10,	/* 打星成功 */
	eEquipAct_LevelUpFailed				= 20,	/* 打星失败 */
	eEquipAct_Found					= 30,	/* 打造成功 */
	eEquipAct_Remould				= 40,	/* 改造成功 */
	eEquipAct_Majiang				= 50,	/* 麻将改造 */
	eEquipAct_BlueAdd				= 60,	/* 蓝属性附加 */
	eEquipAct_NUM
};

enum eCheatActOpType
{
	eCheatActOp_Unknow				= 0,	/* 未知操作 */
	eCheatActOp_Log,	/* 只写LOG */
	eCheatActOp_Kill,	/* 踢掉 */
	eCheatActOp_Answer,	/* 答题 */
};

enum ePetActType
{
	ePetAct_Unknow					= 0,	/* 宠物未知操作 */
	ePetAct_Catch					= 10,	/* 宠物捕捉 */
	ePetAct_ScriptCreate				= 11,	/* 脚本创建宠物 */
	ePetAct_ScriptDestroy				= 12,	/* 脚本删除宠物 */
	ePetAct_PlayerFree				= 13,	/* 玩家放生 */
	ePetAct_ResumeAllHorseHappy			= 14,	/* 恢复所有骑乘快乐度 */
	ePetAct_GeneraAdd				= 20,	/* 宠物繁殖时增加宠物 */
	ePetAct_GeneraLost				= 21,	/* 宠物繁殖时失去宠物 */
	ePetAct_ComposeMain				= 22,	/* 宠物炼化时主宠物 */
	ePetAct_ComposeSub				= 23,	/* 宠物炼化时副宠物 */
	ePetAct_ComposeNew				= 24,	/* 宠物炼化时新宠物 */
	ePetAct_ComposeRep				= 25,	/* 宠物炼化后恢复主宠物 */
	ePetAct_ComposeDel				= 26,	/* 宠物炼化后反悔删掉新宠物 */
	ePetAct_TradeOther				= 30,	/* 宠物交易获得 */
	ePetAct_StallTradeAcquire			= 40,	/* 摆摊交易获得 */
	ePetAct_PlayerShopTradeAcquire			= 50,	/* 玩家商店交易获得 */
	ePetAct_PlayerShopMarket			= 51,	/* 玩家商店上架 */
	ePetAct_PlayerShopMarketGoWay			= 52,	/* 玩家商店下架 */
	ePetAct_GMCreate				= 60,	/* GM 修改添加 */
	ePetAct_GMDestroy				= 61,	/* GM 修改销毁 */

	ePetAct_PlayerLock				= 62,	/* 骑乘锁定 */
	ePetAct_PlayerUnlock			= 63,	/* 骑乘解锁 */

	ePetAct_ReturnToChild			= 70,	/* 骑乘还童 */
	ePetAct_ReturnToChildExt		= 71,	/* 骑乘还龙 */

	ePetAct_NUM
};

//股票交易相关的操作
enum eStockActType
{
	eStockAct_Unknow			= 0,	// 未知任务操作 
	eStockAct_LoadDataFromDB,			// 启动时从DB中实际LOAD一条数据
	eStockAct_AutoBuyMarketOK,			// 买单上架成功 
	eStockAct_AutoBuyMarketFailed,		// 买单上架失败
	eStockAct_AutoSellMarketOK,			// 卖单上架成功 
	eStockAct_AutoSellMarketFailed,		// 卖单上架失败
	eStockAct_ClearOvertime,			// 超时清除挂单
	eStockAct_ClearTrade,				// 交易清除挂单
	eStockAct_ClearRepeal,				// 玩家撤单时清除挂单
	eStockAct_BuyListFull,				// 买单太多列表爆了
	eStockAct_SellListFull,				// 卖单太多列表爆了
	eStockAct_UserBuyFull,				// 用户买单已达上限
	eStockAct_UserSellFull,				// 用户卖单已达上限
	eStockAct_SystemBuy,				// 系统回购
	eStockAct_TradeOK,					// 交易成功
	eStockAct_LoadFromDBNodeFull,		// 启动时从DB中LOAD一条数据失败(结点已被占用)
	eStockAct_SMUNodeNull,				// 共享内存结点为空
	eStockAct_AutoBuyMarketSMUNull,		// 买单上架时 共享内存结点为空
	eStockAct_AutoSellMarketSMUNull,	// 卖单上架时共享内存结点为空
	eStockAct_NUM
};

//股票账户相关的操作
enum eStockAccActType
{
	eStockAccAct_Unknow			= 0,		// 未知任务操作 
	eStockAccAct_LoadDataFromDB,			// 启动时从DB中实际LOAD一条数据
	eStockAccAct_ClearOvertime,				// 超时清除账户
	eStockAccAct_ClearAccount,				// 清除账户，玩家撤消账户
	eStockAccAct_CharMoneyToStockCost,		// 充值时，MAP扣除角色现金和现银
	eStockAccAct_CharMoneyToStockFailedGL,	// 向GL充值失败
	eStockAccAct_CharMoneyToStockAdd,		// 充值时，GL向账户增加现金和现银
	eStockAccAct_CharMoneyToStockFailedMAP,	// 充值失败，MAP回滚Money
	eStockAccAct_StockMoneyToCharkCost,		// 向角色转账时，GL扣除账户现金和现银
	eStockAccAct_StockMoneyToCharFailedkGL,	// 向角色转账时，GL失败
	eStockAccAct_StockMoneyToCharkAdd,		// 向角色转账成功，MAP增加角色现金和现银
	eStockAccAct_StockMoneyToCharkFailed,	// 向角色转账失败
	eStockAccAct_GoldToCharkFailedAdd,		// 向角色转账失败,GL回滚现金
	eStockAccAct_SillerToCharkFailedAdd,	// 向角色转账失败,GL回滚现银
	eStockAccAct_NullUser,					// pUser为空 
	eStockAccAct_AutoSaleCostGold,			// 委托卖金: 扣除本金和手续费 现金
	eStockAccAct_AutoBuyCostSiller,			// 委托买金: 扣除本金和手续费 现银
	eStockAccAct_AutoSaleAddSiller,			// 委托卖金: 增加现银
	eStockAccAct_AutoBuyAddGold,			// 委托买金: 增加现金
	eStockAccAct_FastBuyCostSiller,			// 手动买金: 扣除本金和手续费 现银
	eStockAccAct_FastSaleCostGold,			// 手动卖金: 扣除本金和手续费 现金
	eStockAccAct_FastBuyAddGold,			// 手动买金成功: 增加现金
	eStockAccAct_FastSaleAddSiller,			// 手动卖金成功: 增加现银
	eStockAccAct_GoldLimit,					// 现金超过上限
	eStockAccAct_SillerLimit,				// 现银超过上限
	eStockAccAct_GoldLack,					// 现金不足
	eStockAccAct_SillerLack,				// 现银不足
	eStockAccAct_BuyOvertimeAdd,			// 买单超时,现银转入账户
	eStockAccAct_SellOvertimeAdd,			// 卖单超时,现金转入账户
	eStockAccAct_RepealTradeAddGold,		// 玩家撤单，现金转入账户
	eStockAccAct_RepealTradeAddSiller,		// 玩家撤单，现银转入账户
	eStockAccAct_AddSillerOwnerNull,		// 向账户增加现银时玩家账户为空
	eStockAccAct_AddGoldOwnerNull,			// 向账户增加现金时玩家账户为空
	eStockAccAct_RegisterOK,				// 开户成功
	eStockAccAct_LoadFromDbNullAcc,			// 启动从DB中LOAD数据时，用户股票账户为空
	eStockAccAct_StockRegisterCostMoney,	// 开户扣现银
	eStockAccAct_StockRegisterFailedAddMoney,//开户失败返回现银
	eStockAccAct_CoolingCostGold,			 //进入冷却状态后扣除现金
	eStockAccAct_CoolingCostSiller,			 //进入冷却状态后扣除现银
	eStockAccAct_StockAccDieAddMoney,		 //股票账户消亡：资金返回角色
	eStockAccAct_NUM
};

enum eGuildActType
{
	eGuildAct_Unknow			= 0,		// 未知任务操作 
	eGuildAct_Exp_GM			= 1,		// 帮会经验，GM指令改变
	eGuildAct_Exp_Script		= 2,		// 帮会经验，脚本调用
	eGuildAct_Money_GM			= 3,		// 帮会金钱，GM指令改变
	eGuildAct_Money_Script		= 4,		// 帮会金钱，脚本调用
	eGuildAct_ShiMing_GM		= 5,		// 帮会使命点，GM指令改变
	eGuildAct_ShiMing_Script	= 6,		// 帮会使命点，脚本调用
	eGuildAct_Money_Leveldown	= 7,		// 帮会降级，将超过限制的金钱扣除
	eGuildAct_ShiMing_RemoveMember = 8,		// 离开成员，使命点扣除
	eGuildAct_ShiMing_AddMember = 9,		// 增加成员，使命点增加
	eGuildAct_ShiMing_SystemCheck = 10,		// 系统每月检查清零
	eGuildAct_Exp_Skill		= 11,			// 帮会经验，帮会技能升级
	eGuildAct_Money_Skill		= 12,			// 帮会金钱，帮会技能升级
	eGuildAct_BusSkill_LevelUp_Money = 13,	// 帮会神兽技能升级,消耗帮会金钱
	eGuildAct_BusSkill_LevelUp_Exp = 14,	// 帮会神兽技能升级,消耗帮会经验
	eSkillAct_GuildBusSkill_LevelUp = 15,	/// 帮会神兽技能升级
	eGuildAct_NUM
};

enum eZhuanJingActType
{
	eZhuanjingAct_Unknow		= 0,			/* 未知操作 */
	eZhuanjingAct_ZhuanGong_Get		= 10,			/* 专攻点数获得 */
	eZhuanjingAct_ZhuanFang_Get		= 20,			/* 专防点数获得 */
	eZhuanjingAct_ZhuanGong_Coefficient		= 30,			/* 专攻系数分配 */
	eZhuanjingAct_ZhuanFang_Reallocate		= 40,			/* 专防点数分配 */
	eZhuanjingAct_ZhuanGong_GM		= 50,			/* 通过 GM命令 专攻点数获得 */
	eZhuanjingAct_ZhuanFang_GM		= 60,			/* 通过 GM命令 专防点数获得 */
	eZhuanjingAct_Zhuangong_LevelUp = 70,			/* 专攻升级 */
	eZhuanjingAct_Zhuanfang_LevelUP = 80,		/* 专防升级 */
	eZhuanjingAct_NUM
};

#endif /* _ACT_DEFINE_H_ */

/* end ??? */
