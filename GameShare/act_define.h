/*$T MapServer/Server/Base/act_define.h GC 1.140 10/10/09 10:07:20 */

/* act_define.h $v1.0 97203 */
#ifndef _ACT_DEFINE_H_
#define _ACT_DEFINE_H_

enum eSkillActType
{
	eSkillAct_Unknow		= 0,			/* δ֪���ܲ��� */
	eSkillAct_ScriptTrain		= 10,			/* ����ѧϰ */
	eSkillAct_LevelUp		= 20,			/* �������� */
	eSkillAct_ScriptAbandon		= 30,			/* ���ܷ��� */
	eSkillAct_ScriptChangeFaction	= 31,			/* �ű�����ChangeMenpai */
	eSkillAct_GMModify		= 40,			/* ͨ��GM���� ѧϰ */
	eSkillAct_GuildSkillLevelUp_Guild	= 50,			/* ��Ἴ�ܣ��츳���У����� ���*/
	eSkillAct_GuildSkillLevelUp_Person		= 51,			/* ��Ἴ�ܣ��츳���У����� ����*/
	eSkillAct_InherenceBalance_LevelUp		= 60,			/* �츳ƽ������*/
	eSkillAct_NUM
};
enum eAbilityActType
{
	eAbilityAct_Unknow		= 0,			/* δ֪���ܲ��� */
	eAbilityAct_ScriptTrain		= 10,			/* �����ѧϰ */
	eAbilityAct_LevelUp		= 20,			/* ��������� */
	eAbilityAct_ScriptAbandon	= 30,			/* ����ܷ��� */
	eAbilityAct_GMModify		= 40,			/* ͨ��GM���� ѧϰ */
	eAbilityAct_GMModifyAll		= 41,			/* ͨ��GM����ѧϰ���� */
	eAbilityAct_NUM
};
enum eCurrencyActType
{
	eCurrencyAct_Unknow				= 0,	/* δ֪ */
	eCurrencyAct_SaveBank				= 1,	/* ���д� */
	eCurrencyAct_TakeMoneyAtBank			= 2,	/* ����ȡ */
	eCurrencyAct_ExchangeIncome			= 3,	/* ���ҽ������� */
	eCurrencyAct_ExchangeOutcome			= 4,	/* ���ҽ���֧�� */
	eCurrencyAct_PrivatelyExchangeIncome		= 5,	/* ����ͨ��̯λ�������� */
	eCurrencyAct_PrivatelyExchangeOutcome		= 6,	/* ����ͨ��̯λ����֧�� */
	eCurrencyAct_PrivatelyExchangeTaxOutcome	= 7,	/* ����ͨ��̯λ˰��֧�� */
	eCurrencyAct_PlayerShopExchangeOutcome		= 8,	/* ����ͨ������̵꽻�׻���֧��,Ǯ������̵� */
	eCurrencyAct_BuyPlayerShopOutcome		= 9,	/* ����ͨ����������̵�֧�� */
	eCurrencyAct_CreatePlayerShopOutcome		= 10,	/* ����ͨ����������̵�֧�� */
	eCurrencyAct_PlayerShopSave			= 11,	/* ����̵�� */
	eCurrencyAct_PlayerShowTake			= 12,	/* ����̵�ȡ */
	eCurrencyAct_ShopCost				= 13,	/* �̵깺��֧�� */
	eCurrencyAct_ShopSell				= 14,	/* �̵�������� */
	eCurrencyAct_ShopRepair				= 15,	/* �̵�����֧�� */
	eCurrencyAct_ShopSpecialRepair			= 16,	/* �̵�����֧�� */
	eCurrencyAct_TrainAbilityCost			= 17,	/* ѧϰ�����֧�� */
	eCurrencyAct_TrainSkillCost			= 19,	/* ѧϰս������ */
	eCurrencyAct_CallScriptCost			= 20,	/* �ű����ý�Ǯ���� */
	eCurrencyAct_CallScriptIncome			= 21,	/* �ű����ý�Ǯ���� */
	eCurrencyAct_DieCost				= 22,	/* ������Ǯ�ͷ� */
	eCurrencyAct_PetCost				= 23,	/* �����Ǯ���� */
	eCurrencyAct_CreateGuildCost			= 24,	/* ��������Ǯ���� */
	eCurrencyAct_GuildLevelUpCost			= 25,	/* ����������� */
	eCurrencyAct_ChallengeKingCost			= 26,	/* ��ս�������� */
	eCurrencyAct_ApplyActAsKing			= 27,	/* ���뵱���� */
	eCurrencyAct_GuildLevelUpFailedHandBack		= 28,	/* �������ʧ�ܻ�Ǯ */
	eCurrencyAct_CreateGuildFailedHandBack		= 29,	/* ��������Ǯʧ�ܻ�Ǯ */
	eCurrencyAct_ApplyKingFailedHandBack		= 30,	/* �������ʧ�ܻ�Ǯ */
	eCurrencyAct_CountryDonate			= 31,	/* ���Ҿ��� */
	eCurrencyAct_CountryDelate			= 32,	/* ���ҵ��� */
	eCurrencyAct_DrillCost				= 33,	/* �ӿ׽�Ǯ���� */
	eCurrencyAct_EquipLevelUpCost			= 34,	/* װ���������Ľ�Ǯ */
	eCurrencyAct_EquipRemouldCost			= 35,	/* װ�������Ǯ���� */
	eCurrencyAct_FoundEquipCost			= 36,	/* װ�������Ǯ���� */
	eCurrencyAct_EquipInlayCost			= 37,	/* װ����Ƕ��Ǯ���� */
	eCurrencyAct_EquipBindCost			= 40,	/* װ���󶨽�Ǯ���� */
	eCurrencyAct_EquipChangeCard			= 41,	/* װ�����ƽ�Ǯ���� */
	eCurrencyAct_GMmodify				= 42,	/* GM �޸� */
	eCurrencyAct_HorseMating			= 43,	/* ���� */
	eCurrencyAct_HorseFindingMating			= 44,	/* ��������������� [6/16/2008 wuwenbin] */
	eCurrencyAct_HorseRiseHappy			= 46,	/* ������Ŀ��ֶ� */
	eCurrencyAct_MarryCost				= 47,	/* ������� */
	eCurrencyAct_DivorceCost			= 48,	/* ������� */
	eCurrencyAct_PresentWeddingRB			= 49,	/* �μӻ���ĺ�� */
	eCurrencyAct_CashAccountToChar			= 50,	/* ���ʻ�ת����ɫ���ֽ� */
	eCurrencyAct_ChatCost				= 51,	/* �������� */
	eCurrencyAct_ProxyTrain				= 52,	/* �������� */
	eCurrencyAct_Exchange				= 53,	/* ��Ǯ�һ� */
	eCurrencyAct_TakeCountryFinancingAtBank		= 54,	/* ��ȡ�����ʽ� */
	eCurrencyAct_CashVendueCost			= 55,	/* �ֽ��̵����Ԥ�� */
	eCurrencyAct_CashVendueFailedHandBack		= 56,	/* �ֽ��̵����ʧ�ܷ��� */
	eCurrencyAct_CashShopBuyCost			= 57,	/* �ֽ��̵깺��Ԥ�� */
	eCurrencyAct_CashShopBuyFailedHandBack		= 58,	/* �ֽ��̵깺��ʧ�ܷ��� */
	eCurrencyAct_CashShopBuySuccessed		= 59,	/* �ֽ��̵깺��ɹ����ֽ� */
	eCurrencyAct_CashShopRetakeAtBank		= 60,	/* �ֽ���ۺ�ͨ��������ȡ�ֽ� */
	eCurrencyAct_OnHandSillerShopRetakeAtBank	= 61,	/* �ֽ���ۺ�ͨ��������ȡ���� */
	eCurrencyAct_EquipColorChange			= 62,	/* ��װ����װ���� */
	eCurrencyAct_EquipPurpleWashAttr		= 63,	/* ��װϴ���Ի��� */
	eCurrencyAct_EquipGemLevelUpCost		= 64,	/* ��ʯ�������� */
	eCurrencyAct_EquipGemCompoundCost		= 65,	/* ��ʯ�ϳ����� */
	eCurrencyAct_EquipGemTeardown			= 66,	/* ��ʯ��ж���� */
	eCurrencyAct_EquipCopyCost			= 67,	/* װ�����ƻ��� */
	eCurrencyAct_ExchangeGoldIncome			= 68,	/* �ֽ������� */
	eCurrencyAct_ExchangeGoldOutcome		= 69,	/* �ֽ���֧�� */
	eCurrencyAct_PrivatelyExchangeIncomeGold = 70,	/* ����ͨ��̯λ�������룬�ֽ� */
	eCurrencyAct_PrivatelyExchangeOutcomeGold = 71, /* ����ͨ��̯λ����֧�� */
	eCurrencyAct_2v2MarkScriptAdd			= 72,	/* 2v2ս���������� */
	eCurrencyAct_2v2MarkScriptSub			= 73,	/* 2v2ս�����ּ��� */
	eCurrencyAct_PrivatelyExchangeTax		= 74,	/* ̯λ������˰������ */
	eCurrencyAct_PrivatelyExchangeTaxGold	= 75,	/* ̯λ������˰���ֽ� */
	eCurrencyAct_EquipRecallAddMoney		= 76,	/* װ�����յõ���Ǯ*/
	eCurrencyAct_ScriptChangeGP				= 77,	/* �ű����ã��ﹱ�ı� */
	eCurrencyAct_ServerSyncGP				= 78,	/* GLͬ���ﹱֵ */
	eCurrencyAct_CharGoldToStock			= 79,	/* ��Ʊ�˻���ֵ�۳����ֽ� */
	eCurrencyAct_CharSillerToStock			= 80,	/* ��Ʊ�˻���ֵ�۳������� */
	eCurrencyAct_CharGoldToStockFailed		= 81,	/* ��Ʊ�˻���ֵʧ�ܣ��ع��ֽ� */
	eCurrencyAct_CharSillerToStockFailed	= 82,	/* ��Ʊ�˻���ֵʧ�ܣ��ع����� */
	eCurrencyAct_StockGoldToChar			= 83,	/* ��Ʊ�˻��ֽ�ת�˵���ɫ�������ֽ� */
	eCurrencyAct_StockSillerToChar			= 84,	/* ��Ʊ�˻�����ת�˵���ɫ���������� */
	eCurrencyAct_ScriptChangeMerit			= 85,	/* �ű����ã��ı��Ṧ��ֵ */
	eCurrencyAct_GMChangeMerit				= 86,	/* GM����ı��Ṧ��ֵ */
	eCurrencyAct_ServerSyncMerit			= 87,	/* GLͬ����Ṧ��ֵ */
	eCurrencyAct_StockRegisterCostMoney		= 88,	/* ��Ʊϵͳ�����շѣ��۳����� */
	eCurrencyAct_StockRegisterFailedAddMoney= 89,	/* ��Ʊϵͳ����ʧ�ܣ��������� */
	eCurrencyAct_BlueAddCost				= 90,	/* �����Ը��ӵĻ��� */
	eCurrencyAct_StockAutoSaleCostGold		= 91,	// ί������: �۳������������ �ֽ�
	eCurrencyAct_StockAccDieAddMoney		= 92,	// ��Ʊ�˻�����: �ʽ𷵻ؽ�ɫ
	eCurrencyAct_StockSysBuyGold			= 93,	// ��Ʊϵͳ��ϵͳ���߹����ֽ�
	eCurrencyAct_EquipSwitch				= 94,	// װ��ת������
	eCurrencyAct_MentalBuyItem				= 95,	/* ���⹺����� */
	eCurrencyAct_GuildSkillLevelUpCost			= 96,	/* ����츳������������ */
	eCurrencyAct_BlueProduceCost      = 97,		/*��װ��������*/
	eCurrencyAct_ConstBindCost	= 98,		/*��������*/
	eCurrencyAct_EquipHonorBindCost = 99,		/*��������*/

	/* 100->200Ϊ�淨��ʹ������ҵĲ������� */
	eCurrencyAct_TestFee				= 100,	/* ���Է� */
	eCurrencyAct_Prize				= 101,	/* �콱 */
	eCurrencyAct_ScriptChangeActivity		= 102,	/* �ű����ã��ı����Ծ�� */
	/* 300->400Ϊ�ű��淨�Ȳ������� */
	/* ��Ǯ*/
	eCurrencyAct_Relive				= 300, /*����*/
	eCurrencyAct_NormalMission		= 301, /*һ������*/
	eCurrencyAct_ChuanSong			= 302, /*����*/
	eCurrencyAct_Betray				= 303, /*�ѹ�*/
	eCurrencyAct_Levelup			= 304, /*����*/
	eCurrencyAct_Hunyin				= 305, /*����*/
	eCurrencyAct_Wuting				= 306, /*����*/
	eCurrencyAct_GoldDel			= 307, /* �ֽ������������ֽ� */
	eCurrencyAct_SuperSale			= 308, /* �ֽ����� */
	eCurrencyAct_OfflineTrain		= 309, /* ���ߴ��� */
	eCurrencyAct_SubscribeToGuild	= 310, /* ���װ���Ǯ */

	eCurrencyAct_Wulongyin_mojun	= 311, /* ����ӡ�һ�-�콵ħ�� */
	eCurrencyAct_Wulongyin_wabao	= 312, /* ����ӡ�һ�-�ڱ�����ս */
	eCurrencyAct_Wulongyin			= 313, /* ����ӡ�һ� */
	eCurrencyAct_Wulongyin_huapi	= 314, /* ����ӡ�һ�-��Ƥ */
	eCurrencyAct_Wulongyin_qiannv	= 315, /* ����ӡ�һ�-ٻŮ�Ļ� */
	eCurrencyAct_Qiangjiang			= 316, /* ���������� */
	eCurrencyAct_Shangxiang			= 317, /* ������Ը */
	eCurrencyAct_Baoxiang			= 318, /* ����� */
	eCurrencyAct_Xingbing_loulan	= 319, /* �±��ٳ� ¥�� */
	eCurrencyAct_Xingbing_tianshan	= 320, /* �±��ٳ� ��ɽ */
	eCurrencyAct_Xingbing_kunlun	= 321, /* �±��ٳ� ���� */
	eCurrencyAct_Xingbing_dunhuang	= 322, /* �±��ٳ� �ػ� */
	eCurrencyAct_Mojun				= 323, /* �콵ħ�� */
	eCurrencyAct_Baolong			= 324, /* ��������ս */
	eCurrencyAct_GuildSuCheng		= 325, /* ����ٳ� */
	eCurrencyAct_ITEM_OTHER_195		= 326, /* ������������ */
	eCurrencyAct_ITEM_OTHER_197		= 327, /* ��������𿨡� */
	eCurrencyAct_DynamicShopCost	= 328,	/* ��̬�۸��̵깺��֧�� */
	eCurrencyAct_GuildSendMail		= 329,  /* ����Ⱥ���ʼ��۳����� */

	eCurrencyAct_NUM
};
enum eQuestActType
{
	eQuestAct_Unknow				= 0,	/* δ֪������� */
	eQuestAct_AddQuest				= 10,	/* �������� */
	eQuestAct_DelQuest				= 20,	/* ɾ�������п�������ɺ�ɾ���� */
	eQuestAct_ParamChange				= 30,	/* ��������仯 */
	eQuestAct_DoneFlag				= 40,	/* ������ɱ�־�仯 */
	eQuestAct_DataChange				= 50,	/* ����ȫ�����ݱ仯 */
	eQuestAct_CycleDoneFlag				= 60,	/* ѭ���������һ�α�־ */

	eQuestAct_NUM
};
enum eItemActType
{
	eItemAct_Unknow					= 0,	/* δ֪��Ʒʰȡ */
	eItemAct_TempCreateFromMonster			= 1,	/* ����������ʱ���� */
	eItemAct_CreateFromMonster			= 2,	/* ������䣬���ɵ������ */
	eItemAct_CreateScriptToBox			= 3,	/* �ɽű��������������һ�������������� */
	eItemAct_PickFromMonster			= 4,	/* ���������Ʒʰȡ,ָ����ɫ���ϵĴ��� */
	eItemAct_PickFromGrowPoint			= 5,	/* �ɼ�ʰȡ,ָ����ɫ���ϵĴ��� */
	eItemAct_PickFromPerson				= 6,	/* ���������Ʒʰȡ,ָ����ɫ���ϵĴ��� */
	eItemAct_CreateFromScript			= 7,	/* �ű�������Ʒ */
	eItemAct_CreateFromAbilityScript		= 8,	/* �������ؽű����� */
	eItemAct_CreateGM				= 9,	/* GM���� */
	eItemAct_CreateAbilityComposite			= 10,	/* ��ʯ�ϳ� */

	eItemAct_CreateAndExtirpate			= 11,	/* ��ʯժ������������ */
	eItemAct_CreateFromShop				= 12,	/* �̵�Ĵ��� */
	eItemAct_CreateToStack				= 13,	/* ��������ԭ������Ʒ�ѵ� */
	eItemAct_CreateSplit				= 14,	/* �����Ʒʱ��Ʒ�Ĵ��� */
	eItemAct_ExchangeToOther			= 15,	/* ��Ʒ����, */
	eItemAct_StallBoxExchange			= 16,	/* ̯λ���� */
	eItemAct_PlayerShopExchange			= 17,	/* ����̵� */
	eItemAct_PlayerShopMarket			= 18,	/* ����̵��ϼ� */
	eItemAct_PlayerShowMarketGoWay			= 19,	/* ����̵��¼� */
	eItemAct_InventorySplitDest			= 20,	/* ��Ʒ�������Ŀ�ĵ� */
	eItemAct_InventorySplitSrc			= 21,	/* ��Ʒ�������Դͷ */
	eItemAct_BankSplitDest				= 22,	/* ���в�� */
	eItemAct_BankSplitSrc				= 23,	/* ���в�� */
	eItemAct_InventoryStackDest			= 24,	/* ������Ʒ�ѵ�Ŀ�ĵ� */
	eItemAct_InventoryStackSrc			= 25,	/* ������Ʒ�ѵ�Դ */
	eItemAct_BankStack				= 26,	/* ������Ʒ�ѵ� */
	eItemAct_SellSplit				= 27,	/* ���۲�����Ʒʱ�Ĳ�� */
	eItemAct_BankRemoveItem				= 28,	/* �����Ƴ���Ʒ */
	eItemAct_InventoryRemoveItem			= 29,	/* �ӱ����Ƴ���Ʒ */
	eItemAct_BankAcquireItem			= 30,	/* ���л����Ʒ */
	eItemAct_InventoryAcquireItem			= 31,	/* ���������Ʒ */

	eItemAct_BankStackDest				= 32,	/* ������Ʒ�ϲ�Ŀ�� */
	eItemAct_BankStackSrc				= 33,	/* ������Ʒ�ϲ�Դͷ */
	eItemAct_InventoryToBankExchange		= 34,	/* ����������Ʒ��������Ʒ */
	eItemAct_BankToInventoryExchange		= 35,	/* ���н�����Ʒ������ */
	eItemAct_InventoryToBankRemove			= 36,	/* ������Ʒ�ƶ������� */
	eItemAct_OpenBoxCreate				= 37,	/* ���������Ʒ */
	eItemAct_CaptureBeastieCreate			= 38,	/* ����С�������Ʒ */
	eItemAct_DrillConsume				= 39,	/* �ӿ���Ʒ���� */
	eItemAct_EquipLevelUpConsume			= 40,	/* ����������Ʒ */
	eItemAct_EquipBindConsume			= 41,	/* ��������Ʒ */
	eItemAct_EquipExchangeCardConsume		= 42,	/* ����������Ʒ */
	eItemAct_CraftCreateFromStuff			= 43,	/* ���� */
	eItemAct_CraftConsume				= 44,	/* ����������� */
	eItemAct_DecompoundRemove			= 45,	/* ���� */
	eItemAct_DecomposeAcquireStuff			= 46,	/* ����ò��� */
	eItemAct_RemouldConsume				= 47,	/* ������Ʒ���� */
	eItemAct_SpecialFixConsume			= 48,	/* ������Ʒ���� */
	eItemAct_Drill					= 49,	/* �ӿ� */
	eItemAct_EquipLevelUp				= 50,	/* ���� */
	eItemAct_EquipBind				= 51,	/* �� */
	eItemAct_EquipExchangeCard			= 52,	/* ���� */
	eItemAct_CraftCreate				= 53,	/* ���� */
	eItemAct_Decompound				= 54,	/* ��� */
	eItemAct_Remould				= 55,	/* ���� */

	eItemAct_SpecialFix				= 56,	/* ���� */
	eItemAct_Repair					= 57,	/* ��Ʒ����, */
	eItemAct_UseGemAndRemove			= 58,	/* ��ʯʹ��ʱ�Ƴ� */
	eItemAct_UseGemAndLost				= 59,	/* ��ʯ�ϳɶ�ʧ */
	eItemAct_Discard				= 60,	/* ����������� */
	eItemAct_GemCompoundConsume			= 61,	/* ��ʯ�ϳɵ���Ʒ���� */
	eItemAct_AbilityConsume				= 62,	/* �������Ʒ���� */
	eItemAct_ScriptDelete				= 63,	/* �ӽű�ɾ����Ʒ */
	eItemAct_ChangeHairConsume			= 64,	/* �ı䷢������ */
	eItemAct_DiePunish				= 65,	/* �����ͷ� */
	eItemAct_InlayWasting				= 66,	/* ��Ʒ��Ƕ��ʧ */
	eItemAct_MachineWasting				= 67,	/* ��е������ʧ */
	eItemAct_DiscardEquip				= 68,	/* �������������װ���ϵ���Ʒ */
	eItemAct_DiscardBank				= 69,	/* ���������������װ�� */
	eItemAct_Use					= 70,	/* �������ʹ�� */
	eItemAct_UseReelConsume				= 71,	/* ����ʹ������ */
	eItemAct_SystemGiveBack				= 72,	/* ϵͳ���� */
	eItemAct_DelFromSoldList				= 73,	/* �ӻع��б���ɾ����Ʒ */
	eItemAct_ExchangeEquipToBank			= 74,	/* װ��������Ʒ��������Ʒ */
	eItemAct_ExchangeBankToBank			= 75,	/* ���н�����Ʒ��������Ʒ */
	eItemAct_ExchangeInventoryToEquip		= 76,	/* ����������Ʒ��װ����Ʒ */
	eItemAct_ExchangeEquipToInventory		= 77,	/* װ��������Ʒ��������Ʒ */
	eItemAct_ExchangeInventoryToInventory		= 78,	/* ����������Ʒ��������Ʒ */
	eItemAct_BoxRecycle				= 79,	/* ItemBox���� */
	eItemAct_SkillConsume				= 80,	/* �������� */
	eItemAct_SkillTrain				= 81,	/* ����ѧϰ */
	eItemAct_QuestScriptDel				= 82,
	eItemAct_MarryConsume				= 83,	/* ������� */
	eItemAct_CatchHorseConsume			= 84,	/* ׽����Ʒ���� */
	eItemAct_CreateByPresentWedding			= 85,	/* �μӻ������͵�ϲ�� */
	eItemAct_DropWedding				= 86,	/* ����������Ʒ */

	eItemAct_EquipCLRChangeDelGem			= 87,	/* ��װ����װɾ����ʯ */
	eItemAct_EquipCLRChangeDelYellow		= 88,	/* ��װ����װɾ����װ */
	eItemAct_EquipCLRChangeCreate			= 89,	/* ��װ����װ������װ */
	eItemAct_EquipPurleWashDelGem			= 90,	/* ��װϴ����ɾ����ʯ */
	eItemAct_EquipPurleWashChange			= 91,	/* ��װϴ�������Ըı� */
	eItemAct_GemLevelUpDestorySelf			= 92,	/* ��ʯ����ɾ����ǰ��ʯ */
	eItemAct_GemLevelUpConsume			= 93,	/* ��ʯ����ɾ�����豦ʯ */
	eItemAct_GemLevelUpResult			= 94,	/* ��ʯ�����õ�������ʯ */
	eItemAct_GemCompoundDestorySelf			= 95,	/* ��ʯ�ϳ�ɾ����ʯ */
	eItemAct_GemCompoundResult			= 96,	/* ��ʯ�ϳɵõ�������ʯ */
	eItemAct_GemTeardownConsume			= 97,	/* ��ʯ��жɾ��������Ʒ */
	eItemAct_EquipCopyConsume			= 98,	/* װ������ɾ��������Ʒ */
	eItemAct_EquipFushonCreate			= 99,	/* �ʼ�����������������Ʒ */
	eItemAct_EquipFushonConsume			= 100,	/* �ʼ�����������������Ʒ */
	eItemAct_EquipFushonReback			= 101,	/* �ʼ������������˻���Ʒ */
	eItemAct_GemTeardownAddGem			= 102,	/* ��ʯ��ж��ӱ�ʯ */
	eItemAct_EquipCopyDelYellow			= 103,	/* װ������ɾ����ɫװ�� */
	eItemAct_EquipCopyCreatePur			= 104,	/* װ������������ɫװ�� */
	eItemAct_EquipRecallDel				= 105,	/* װ������ɾ��װ�� */
	eItemAct_TransItemUse				= 106, /* ���ͷ�ʹ��ʱ���� */
	eItemAct_GoldDel_ItemUse			= 107, /* ����ֽ�������� */
	eItemAct_BlueIn_EquipDel			= 108, /* ����������װ��ɾ�� */
	eItemAct_BlueIn_ItemDel				= 109, /* ������������Ʒɾ�� */
	eItemAct_BlueAdd_ItemDel			= 110, /* �����Ը�����Ʒɾ�� */	
	eItemAct_BlueIn_OldItemDel			= 111, /* �����������������滻���ϵ������� */
	eItemAct_BlueIn_NewItemCreate		= 112, /* ���������������µ������� */
	eItemAct_Equip_Transform			= 113,
	eItemAct_MoveInSoldContainer		= 114, /* �ڻع��б����ƶ���Ʒ�����ò�����־ͳ�� */
	eItemAct_AddToSoldList				= 115, /* ��ع��б�������Ʒ */
	eItemAct_ChangeFace				= 116, /* ���ݣ�������Ʒ*/
	eItemAct_BlueSyn_ItemDel        = 117,/*�����Ժϳ���Ʒɾ��*/
	eItemAct_GuildSkillTrain				= 118,	/* ��Ἴ��ѧϰ */
	eItemAct_BlueProdudce_NewItemCreate = 119,/*��װ����������Ʒ*/
	eItemAct_BlueProdudce_DeleteItem    = 220,/*��װ����ɾ����Ʒ*/
	eItemAct_InherenceBalanceTrain				= 221,	/* �츳ƽ��ѧϰ */
	eItemAct_ConstBind_DeleteItem       =222,/*��������������Ʒ*/
	eItemAct_RideCompose_DeleteItem       =223,/*�������������Ʒ*/
	eItemAct_HonorBind_DeleteItem       =224,/*��������������Ʒ*/
	eItemAct_EquipHonorBind				= 225,	/* �������� */
	eItemAct_NUM,
};
enum eWorldShopCashActType
{
	eWorldShopCashAct_Unknow			= 0,	/* δ֪������� */
	eWorldShopCashAct_RequestSell,			/* ����������ֽ� */
	eWorldShopCashAct_MarketSuccessed,		/* �ֽ��ϼܳɹ� */
	eWorldShopCashAct_MarketFailed,			/* �ֽ��ϼ�ʧ�� */
	eWorldShopCashAct_MarketReturnNullConnecter,	/* �����ϼܽ��ʱGameConnectorָ��Ϊ�� */
	eWorldShopCashAct_MarketReturnNullHuman,	/* �����ϼܽ��ʱHumanָ��Ϊ�� */
	eWorldShopCashAct_MarketReturnNullMap,		/* �����ϼܽ��ʱMapָ��Ϊ�� */
	eWorldShopCashAct_MarketReturnNullGamePlayer,	/* �����ϼܽ��ʱPlayerָ��Ϊ�� */

	eWorldShopCashAct_RequestBuy,			/* ����������ֽ� */
	eWorldShopCashAct_BuySuccessed,			/* ����ɹ� */
	eWorldShopCashAct_BuyFailed,			/* ����ʧ�� */
	eWorldShopCashAct_BankTakeReturnNullPlayer,	/* ������ȡʱGameConnectorָ��Ϊ�� */
	eWorldShopCashAct_BankTakeReturnNullGamePlayer, /* ������ȡʱHUMANָ��Ϊ�� */
	eWorldShopCashAct_BankTakeReturnNullScene,	/* ������ȡʱSCENEָ��Ϊ�� */
	eWorldShopCashAct_BankTakeReturnNullHuman,	/* ������ȡʱPLAYERָ��Ϊ�� */
	eWorldShopCashAct_BankTakeSuccessed,		/* ������ȡʱ�ɹ� */
	eWorldShopCashAct_NullUser,			/* pUserΪ�� */
	eWorldShopCashAct_ClearCash,			/* ���̵�����������ֽ� */
	eWorldShopCashAct_SellTimeoutReturnToBank,	/* ���۳�ʱ���ֽ���̵�ת������ */
	eWorldShopCashAct_SystemBuy,			/* ϵͳ�ع����ֽ���̵�ת������ */
	eWorldShopCashAct_NullShop,			/* ShopΪ�� */
	eWorldShopCashAct_NullSrvConnecter,		/* ServerPlayerΪ�� */
	eWorldShopCashAct_ShopFull,			/* �̵��� */
	eWorldShopCashAct_BankFull,			/* ������ */
	eWorldShopCashAct_UserFull,			/* ����ڸ��̵��еļ��ۻ����Ѵﵽ���� */
	eWorldShopCashAct_ClearInTheBank,		/* ����������������ֽ� */
	eWorldShopCashAct_LoadShopFromDB,		/* ����ʱ��DB��ʵ��LOADһ���̵����� */
	eWorldShopCashAct_LoadBankFromDB,		/* ����ʱ��DB��ʵ��LOADһ���������� */
	eWorldShopCashAct_ShouldLoadShopFromDB,		/* ����ʱ��DB��Ӧ��LOAD��һ���̵����� */
	eWorldShopCashAct_ShouldLoadBankFromDB,		/* ����ʱ��DB��Ӧ��LOAD��һ���������� */
	eWorldShopCashAct_AddShopFailed,		/* �����̵�ʧ�� */
	eWorldShopCashAct_DelShopFailed,		/* ���̵�ɾ��ʱʧ�� */
	eWorldShopCashAct_AddBankFailed,		/* ��������ʧ�� */
	eWorldShopCashAct_NUM
};
enum eEquipActType
{
	eEquipAct_Unknow				= 0,	/* δ֪������� */
	eEquipAct_LevelUpSuccessed			= 10,	/* ���ǳɹ� */
	eEquipAct_LevelUpFailed				= 20,	/* ����ʧ�� */
	eEquipAct_Found					= 30,	/* ����ɹ� */
	eEquipAct_Remould				= 40,	/* ����ɹ� */
	eEquipAct_Majiang				= 50,	/* �齫���� */
	eEquipAct_BlueAdd				= 60,	/* �����Ը��� */
	eEquipAct_NUM
};

enum eCheatActOpType
{
	eCheatActOp_Unknow				= 0,	/* δ֪���� */
	eCheatActOp_Log,	/* ֻдLOG */
	eCheatActOp_Kill,	/* �ߵ� */
	eCheatActOp_Answer,	/* ���� */
};

enum ePetActType
{
	ePetAct_Unknow					= 0,	/* ����δ֪���� */
	ePetAct_Catch					= 10,	/* ���ﲶ׽ */
	ePetAct_ScriptCreate				= 11,	/* �ű��������� */
	ePetAct_ScriptDestroy				= 12,	/* �ű�ɾ������ */
	ePetAct_PlayerFree				= 13,	/* ��ҷ��� */
	ePetAct_ResumeAllHorseHappy			= 14,	/* �ָ�������˿��ֶ� */
	ePetAct_GeneraAdd				= 20,	/* ���ﷱֳʱ���ӳ��� */
	ePetAct_GeneraLost				= 21,	/* ���ﷱֳʱʧȥ���� */
	ePetAct_ComposeMain				= 22,	/* ��������ʱ������ */
	ePetAct_ComposeSub				= 23,	/* ��������ʱ������ */
	ePetAct_ComposeNew				= 24,	/* ��������ʱ�³��� */
	ePetAct_ComposeRep				= 25,	/* ����������ָ������� */
	ePetAct_ComposeDel				= 26,	/* ���������󷴻�ɾ���³��� */
	ePetAct_TradeOther				= 30,	/* ���ｻ�׻�� */
	ePetAct_StallTradeAcquire			= 40,	/* ��̯���׻�� */
	ePetAct_PlayerShopTradeAcquire			= 50,	/* ����̵꽻�׻�� */
	ePetAct_PlayerShopMarket			= 51,	/* ����̵��ϼ� */
	ePetAct_PlayerShopMarketGoWay			= 52,	/* ����̵��¼� */
	ePetAct_GMCreate				= 60,	/* GM �޸���� */
	ePetAct_GMDestroy				= 61,	/* GM �޸����� */

	ePetAct_PlayerLock				= 62,	/* ������� */
	ePetAct_PlayerUnlock			= 63,	/* ��˽��� */

	ePetAct_ReturnToChild			= 70,	/* ��˻�ͯ */
	ePetAct_ReturnToChildExt		= 71,	/* ��˻��� */

	ePetAct_NUM
};

//��Ʊ������صĲ���
enum eStockActType
{
	eStockAct_Unknow			= 0,	// δ֪������� 
	eStockAct_LoadDataFromDB,			// ����ʱ��DB��ʵ��LOADһ������
	eStockAct_AutoBuyMarketOK,			// ���ϼܳɹ� 
	eStockAct_AutoBuyMarketFailed,		// ���ϼ�ʧ��
	eStockAct_AutoSellMarketOK,			// �����ϼܳɹ� 
	eStockAct_AutoSellMarketFailed,		// �����ϼ�ʧ��
	eStockAct_ClearOvertime,			// ��ʱ����ҵ�
	eStockAct_ClearTrade,				// ��������ҵ�
	eStockAct_ClearRepeal,				// ��ҳ���ʱ����ҵ�
	eStockAct_BuyListFull,				// ��̫���б���
	eStockAct_SellListFull,				// ����̫���б���
	eStockAct_UserBuyFull,				// �û����Ѵ�����
	eStockAct_UserSellFull,				// �û������Ѵ�����
	eStockAct_SystemBuy,				// ϵͳ�ع�
	eStockAct_TradeOK,					// ���׳ɹ�
	eStockAct_LoadFromDBNodeFull,		// ����ʱ��DB��LOADһ������ʧ��(����ѱ�ռ��)
	eStockAct_SMUNodeNull,				// �����ڴ���Ϊ��
	eStockAct_AutoBuyMarketSMUNull,		// ���ϼ�ʱ �����ڴ���Ϊ��
	eStockAct_AutoSellMarketSMUNull,	// �����ϼ�ʱ�����ڴ���Ϊ��
	eStockAct_NUM
};

//��Ʊ�˻���صĲ���
enum eStockAccActType
{
	eStockAccAct_Unknow			= 0,		// δ֪������� 
	eStockAccAct_LoadDataFromDB,			// ����ʱ��DB��ʵ��LOADһ������
	eStockAccAct_ClearOvertime,				// ��ʱ����˻�
	eStockAccAct_ClearAccount,				// ����˻�����ҳ����˻�
	eStockAccAct_CharMoneyToStockCost,		// ��ֵʱ��MAP�۳���ɫ�ֽ������
	eStockAccAct_CharMoneyToStockFailedGL,	// ��GL��ֵʧ��
	eStockAccAct_CharMoneyToStockAdd,		// ��ֵʱ��GL���˻������ֽ������
	eStockAccAct_CharMoneyToStockFailedMAP,	// ��ֵʧ�ܣ�MAP�ع�Money
	eStockAccAct_StockMoneyToCharkCost,		// ���ɫת��ʱ��GL�۳��˻��ֽ������
	eStockAccAct_StockMoneyToCharFailedkGL,	// ���ɫת��ʱ��GLʧ��
	eStockAccAct_StockMoneyToCharkAdd,		// ���ɫת�˳ɹ���MAP���ӽ�ɫ�ֽ������
	eStockAccAct_StockMoneyToCharkFailed,	// ���ɫת��ʧ��
	eStockAccAct_GoldToCharkFailedAdd,		// ���ɫת��ʧ��,GL�ع��ֽ�
	eStockAccAct_SillerToCharkFailedAdd,	// ���ɫת��ʧ��,GL�ع�����
	eStockAccAct_NullUser,					// pUserΪ�� 
	eStockAccAct_AutoSaleCostGold,			// ί������: �۳������������ �ֽ�
	eStockAccAct_AutoBuyCostSiller,			// ί�����: �۳������������ ����
	eStockAccAct_AutoSaleAddSiller,			// ί������: ��������
	eStockAccAct_AutoBuyAddGold,			// ί�����: �����ֽ�
	eStockAccAct_FastBuyCostSiller,			// �ֶ����: �۳������������ ����
	eStockAccAct_FastSaleCostGold,			// �ֶ�����: �۳������������ �ֽ�
	eStockAccAct_FastBuyAddGold,			// �ֶ����ɹ�: �����ֽ�
	eStockAccAct_FastSaleAddSiller,			// �ֶ�����ɹ�: ��������
	eStockAccAct_GoldLimit,					// �ֽ𳬹�����
	eStockAccAct_SillerLimit,				// ������������
	eStockAccAct_GoldLack,					// �ֽ���
	eStockAccAct_SillerLack,				// ��������
	eStockAccAct_BuyOvertimeAdd,			// �򵥳�ʱ,����ת���˻�
	eStockAccAct_SellOvertimeAdd,			// ������ʱ,�ֽ�ת���˻�
	eStockAccAct_RepealTradeAddGold,		// ��ҳ������ֽ�ת���˻�
	eStockAccAct_RepealTradeAddSiller,		// ��ҳ���������ת���˻�
	eStockAccAct_AddSillerOwnerNull,		// ���˻���������ʱ����˻�Ϊ��
	eStockAccAct_AddGoldOwnerNull,			// ���˻������ֽ�ʱ����˻�Ϊ��
	eStockAccAct_RegisterOK,				// �����ɹ�
	eStockAccAct_LoadFromDbNullAcc,			// ������DB��LOAD����ʱ���û���Ʊ�˻�Ϊ��
	eStockAccAct_StockRegisterCostMoney,	// ����������
	eStockAccAct_StockRegisterFailedAddMoney,//����ʧ�ܷ�������
	eStockAccAct_CoolingCostGold,			 //������ȴ״̬��۳��ֽ�
	eStockAccAct_CoolingCostSiller,			 //������ȴ״̬��۳�����
	eStockAccAct_StockAccDieAddMoney,		 //��Ʊ�˻��������ʽ𷵻ؽ�ɫ
	eStockAccAct_NUM
};

enum eGuildActType
{
	eGuildAct_Unknow			= 0,		// δ֪������� 
	eGuildAct_Exp_GM			= 1,		// ��ᾭ�飬GMָ��ı�
	eGuildAct_Exp_Script		= 2,		// ��ᾭ�飬�ű�����
	eGuildAct_Money_GM			= 3,		// ����Ǯ��GMָ��ı�
	eGuildAct_Money_Script		= 4,		// ����Ǯ���ű�����
	eGuildAct_ShiMing_GM		= 5,		// ���ʹ���㣬GMָ��ı�
	eGuildAct_ShiMing_Script	= 6,		// ���ʹ���㣬�ű�����
	eGuildAct_Money_Leveldown	= 7,		// ��ή�������������ƵĽ�Ǯ�۳�
	eGuildAct_ShiMing_RemoveMember = 8,		// �뿪��Ա��ʹ����۳�
	eGuildAct_ShiMing_AddMember = 9,		// ���ӳ�Ա��ʹ��������
	eGuildAct_ShiMing_SystemCheck = 10,		// ϵͳÿ�¼������
	eGuildAct_Exp_Skill		= 11,			// ��ᾭ�飬��Ἴ������
	eGuildAct_Money_Skill		= 12,			// ����Ǯ����Ἴ������
	eGuildAct_BusSkill_LevelUp_Money = 13,	// ������޼�������,���İ���Ǯ
	eGuildAct_BusSkill_LevelUp_Exp = 14,	// ������޼�������,���İ�ᾭ��
	eSkillAct_GuildBusSkill_LevelUp = 15,	/// ������޼�������
	eGuildAct_NUM
};

enum eZhuanJingActType
{
	eZhuanjingAct_Unknow		= 0,			/* δ֪���� */
	eZhuanjingAct_ZhuanGong_Get		= 10,			/* ר��������� */
	eZhuanjingAct_ZhuanFang_Get		= 20,			/* ר��������� */
	eZhuanjingAct_ZhuanGong_Coefficient		= 30,			/* ר��ϵ������ */
	eZhuanjingAct_ZhuanFang_Reallocate		= 40,			/* ר���������� */
	eZhuanjingAct_ZhuanGong_GM		= 50,			/* ͨ�� GM���� ר��������� */
	eZhuanjingAct_ZhuanFang_GM		= 60,			/* ͨ�� GM���� ר��������� */
	eZhuanjingAct_Zhuangong_LevelUp = 70,			/* ר������ */
	eZhuanjingAct_Zhuanfang_LevelUP = 80,		/* ר������ */
	eZhuanjingAct_NUM
};

#endif /* _ACT_DEFINE_H_ */

/* end ??? */
