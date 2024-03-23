
--MisDescBegin
--脚本号
x800088_g_ScriptId = 800088

--最大装备扩展属性数量
x800088_g_MaxEquipExtAttr = 8

--蓝属性强化的操作类型
x800088_g_EquipOpType = 12

--黄装颜色值
x800088_g_EquipColorYellow = 4

--装备最大强化次数
x800088_g_MaxEquipIntensifyCount = 9

--玩法ID
x800088_g_GamePlayerID = 1591

--蓝属性强化在代码玩法中的类型，对应代码EQUIP_WANFA_TYPE_BLUE_INTENSIFY
x800088_g_BlueIntensifyType = 20

--EQUIP_WANFA_TYPE_BLUE_RESET
x800088_g_BlueResetType = 21

--强化等级限制
x800088_g_IntensifyCountList = {	
									{ minEquipLevel = 20, maxEquipLevel = 39, requireLevel =10 },	--装备等级20～39级，人物等级大于装备等级10级强化一次
									{ minEquipLevel = 40, maxEquipLevel = 59, requireLevel = 6 },	--装备等级40～59级，人物等级大于装备等级6级强化一次	
									{ minEquipLevel = 60, maxEquipLevel = 79, requireLevel = 5 },	--装备等级60～79级，人物等级大于装备等级5级强化一次
									{ minEquipLevel = 80, maxEquipLevel = 99, requireLevel = 2 },	--装备等级80～99级，人物等级大于装备等级2级强化一次
								    { minEquipLevel = 100,maxEquipLevel = 160,requireLevel = 0 },	--装备等级100～160级，人物等级大于装备等级1级强化一次										
								}

--强化时需要的money
x800088_g_IntensifyNeedMoney = 	{
									{minEquipLevel = 20, maxEquipLevel = 39,  needMoney = 6000,    needMoney2 = 10000,},	--装备等级20～39级，需要Money6000文
									{minEquipLevel = 40, maxEquipLevel = 59,  needMoney = 20000,   needMoney2 = 10000,},	
									{minEquipLevel = 60, maxEquipLevel = 79,  needMoney = 60000,   needMoney2 = 10000,},
									{minEquipLevel = 80, maxEquipLevel = 99,  needMoney = 200000,  needMoney2 = 10000,},
									{minEquipLevel = 100,maxEquipLevel = 109, needMoney = 200000,  needMoney2 = 10000,},
									{minEquipLevel = 110,maxEquipLevel = 119, needMoney = 200000,  needMoney2 = 10000,},
									{minEquipLevel = 120,maxEquipLevel = 129, needMoney = 200000,  needMoney2 = 10000,},
									{minEquipLevel = 130,maxEquipLevel = 139, needMoney = 200000,  needMoney2 = 10000,},
									{minEquipLevel = 140,maxEquipLevel = 149, needMoney = 200000,  needMoney2 = 10000,},
									{minEquipLevel = 150,maxEquipLevel = 159, needMoney = 200000,  needMoney2 = 10000,},
									{minEquipLevel = 160,maxEquipLevel = 200, needMoney = 200000,  needMoney2 = 10000,},
								}

--强化时需要的材料
x800088_g_NeedItemList = 	{
								--所有主手装备(EQUIP_TYPE)对应的物品ID和数量: item1为强化材料，item2为还童材料
								{minEquipLevel = 20, maxEquipLevel = 39, equipType = 1, needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel = 20, maxEquipLevel = 39, equipType = 2, needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel = 20, maxEquipLevel = 39, equipType = 3, needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel = 20, maxEquipLevel = 39, equipType = 4, needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel = 20, maxEquipLevel = 39, equipType = 5, needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel = 20, maxEquipLevel = 39, equipType = 6, needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel = 20, maxEquipLevel = 39, equipType = 35,needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel = 20, maxEquipLevel = 39, equipType = 36,needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel = 20, maxEquipLevel = 39, equipType = 37,needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel = 20, maxEquipLevel = 39, equipType = 38,needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel = 20, maxEquipLevel = 39, equipType = 39,needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel = 20, maxEquipLevel = 39, equipType = 40,needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								--所有副手装备对应的物品
								{minEquipLevel = 20, maxEquipLevel = 39, equipType = 7, needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel = 20, maxEquipLevel = 39, equipType = 8, needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel = 20, maxEquipLevel = 39, equipType = 9, needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel = 20, maxEquipLevel = 39, equipType = 10,needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel = 20, maxEquipLevel = 39, equipType = 11,needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel = 20, maxEquipLevel = 39, equipType = 12,needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel = 20, maxEquipLevel = 39, equipType = 41,needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel = 20, maxEquipLevel = 39, equipType = 42,needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel = 20, maxEquipLevel = 39, equipType = 43,needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel = 20, maxEquipLevel = 39, equipType = 44,needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel = 20, maxEquipLevel = 39, equipType = 45,needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel = 20, maxEquipLevel = 39, equipType = 46,needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								--徽章对应的物品					
								{minEquipLevel = 20, maxEquipLevel = 39, equipType = 21,needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },		
								--项链对应的物品						
								{minEquipLevel = 20, maxEquipLevel = 39, equipType = 24,needItemId1 = 11000546,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },			
								--戒指对应的物品							
								{minEquipLevel = 20, maxEquipLevel = 39, equipType = 28,needItemId1 = 11000546,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },		
								--衣服对应的物品	
								{minEquipLevel = 20, maxEquipLevel = 39, equipType = 23,needItemId1 = 11000547,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },		
								--帽对应的物品ID		
								{minEquipLevel = 20, maxEquipLevel = 39, equipType = 20,needItemId1 = 11000547,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								--腰带对应的物品	
								{minEquipLevel = 20, maxEquipLevel = 39, equipType = 26,needItemId1 = 11000547,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },																
								--披风对应的物品	
								{minEquipLevel = 20, maxEquipLevel = 39, equipType = 22,needItemId1 = 11000547,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },	
								--护手对应的物品	
								{minEquipLevel = 20, maxEquipLevel = 39, equipType = 25,needItemId1 = 11000548,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },	
								--靴子对应的物品
								{minEquipLevel = 20, maxEquipLevel = 39, equipType = 27,needItemId1 = 11000548,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },		
								--手镯对应的物品
								{minEquipLevel = 20, maxEquipLevel = 39, equipType = 29,needItemId1 = 11000548,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },		
								
								{minEquipLevel = 40, maxEquipLevel = 59, equipType = 1, needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel = 40, maxEquipLevel = 59, equipType = 2, needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel = 40, maxEquipLevel = 59, equipType = 3, needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel = 40, maxEquipLevel = 59, equipType = 4, needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel = 40, maxEquipLevel = 59, equipType = 5, needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel = 40, maxEquipLevel = 59, equipType = 6, needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel = 40, maxEquipLevel = 59, equipType = 7, needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel = 40, maxEquipLevel = 59, equipType = 8, needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel = 40, maxEquipLevel = 59, equipType = 9, needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel = 40, maxEquipLevel = 59, equipType = 10,needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel = 40, maxEquipLevel = 59, equipType = 11,needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel = 40, maxEquipLevel = 59, equipType = 12,needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel = 40, maxEquipLevel = 59, equipType = 35,needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel = 40, maxEquipLevel = 59, equipType = 36,needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel = 40, maxEquipLevel = 59, equipType = 37,needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel = 40, maxEquipLevel = 59, equipType = 38,needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel = 40, maxEquipLevel = 59, equipType = 39,needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel = 40, maxEquipLevel = 59, equipType = 40,needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel = 40, maxEquipLevel = 59, equipType = 41,needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel = 40, maxEquipLevel = 59, equipType = 42,needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel = 40, maxEquipLevel = 59, equipType = 43,needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel = 40, maxEquipLevel = 59, equipType = 44,needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel = 40, maxEquipLevel = 59, equipType = 45,needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel = 40, maxEquipLevel = 59, equipType = 46,needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel = 40, maxEquipLevel = 59, equipType = 21,needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel = 40, maxEquipLevel = 59, equipType = 24,needItemId1 = 11000546,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel = 40, maxEquipLevel = 59, equipType = 28,needItemId1 = 11000546,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel = 40, maxEquipLevel = 59, equipType = 23,needItemId1 = 11000547,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel = 40, maxEquipLevel = 59, equipType = 20,needItemId1 = 11000547,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel = 40, maxEquipLevel = 59, equipType = 26,needItemId1 = 11000547,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel = 40, maxEquipLevel = 59, equipType = 22,needItemId1 = 11000547,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel = 40, maxEquipLevel = 59, equipType = 25,needItemId1 = 11000548,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel = 40, maxEquipLevel = 59, equipType = 27,needItemId1 = 11000548,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel = 40, maxEquipLevel = 59, equipType = 29,needItemId1 = 11000548,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
																									          
								{minEquipLevel = 60, maxEquipLevel = 79, equipType = 1, needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel = 60, maxEquipLevel = 79, equipType = 2, needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel = 60, maxEquipLevel = 79, equipType = 3, needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel = 60, maxEquipLevel = 79, equipType = 4, needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel = 60, maxEquipLevel = 79, equipType = 5, needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel = 60, maxEquipLevel = 79, equipType = 6, needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel = 60, maxEquipLevel = 79, equipType = 7, needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel = 60, maxEquipLevel = 79, equipType = 8, needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel = 60, maxEquipLevel = 79, equipType = 9, needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel = 60, maxEquipLevel = 79, equipType = 10,needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel = 60, maxEquipLevel = 79, equipType = 11,needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel = 60, maxEquipLevel = 79, equipType = 12,needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel = 60, maxEquipLevel = 79, equipType = 35,needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel = 60, maxEquipLevel = 79, equipType = 36,needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel = 60, maxEquipLevel = 79, equipType = 37,needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel = 60, maxEquipLevel = 79, equipType = 38,needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel = 60, maxEquipLevel = 79, equipType = 39,needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel = 60, maxEquipLevel = 79, equipType = 40,needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel = 60, maxEquipLevel = 79, equipType = 41,needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel = 60, maxEquipLevel = 79, equipType = 42,needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel = 60, maxEquipLevel = 79, equipType = 43,needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel = 60, maxEquipLevel = 79, equipType = 44,needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel = 60, maxEquipLevel = 79, equipType = 45,needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel = 60, maxEquipLevel = 79, equipType = 46,needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel = 60, maxEquipLevel = 79, equipType = 21,needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel = 60, maxEquipLevel = 79, equipType = 24,needItemId1 = 11000546,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel = 60, maxEquipLevel = 79, equipType = 28,needItemId1 = 11000546,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel = 60, maxEquipLevel = 79, equipType = 23,needItemId1 = 11000547,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel = 60, maxEquipLevel = 79, equipType = 20,needItemId1 = 11000547,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel = 60, maxEquipLevel = 79, equipType = 26,needItemId1 = 11000547,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel = 60, maxEquipLevel = 79, equipType = 22,needItemId1 = 11000547,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel = 60, maxEquipLevel = 79, equipType = 25,needItemId1 = 11000548,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel = 60, maxEquipLevel = 79, equipType = 27,needItemId1 = 11000548,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel = 60, maxEquipLevel = 79, equipType = 29,needItemId1 = 11000548,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
																									          
								{minEquipLevel = 80, maxEquipLevel = 99, equipType = 1, needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel = 80, maxEquipLevel = 99, equipType = 2, needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel = 80, maxEquipLevel = 99, equipType = 3, needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel = 80, maxEquipLevel = 99, equipType = 4, needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel = 80, maxEquipLevel = 99, equipType = 5, needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel = 80, maxEquipLevel = 99, equipType = 6, needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel = 80, maxEquipLevel = 99, equipType = 7, needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel = 80, maxEquipLevel = 99, equipType = 8, needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel = 80, maxEquipLevel = 99, equipType = 9, needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel = 80, maxEquipLevel = 99, equipType = 10,needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel = 80, maxEquipLevel = 99, equipType = 11,needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel = 80, maxEquipLevel = 99, equipType = 12,needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel = 80, maxEquipLevel = 99, equipType = 35,needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel = 80, maxEquipLevel = 99, equipType = 36,needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel = 80, maxEquipLevel = 99, equipType = 37,needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel = 80, maxEquipLevel = 99, equipType = 38,needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel = 80, maxEquipLevel = 99, equipType = 39,needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel = 80, maxEquipLevel = 99, equipType = 40,needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel = 80, maxEquipLevel = 99, equipType = 41,needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel = 80, maxEquipLevel = 99, equipType = 42,needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel = 80, maxEquipLevel = 99, equipType = 43,needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel = 80, maxEquipLevel = 99, equipType = 44,needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel = 80, maxEquipLevel = 99, equipType = 45,needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel = 80, maxEquipLevel = 99, equipType = 46,needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel = 80, maxEquipLevel = 99, equipType = 21,needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel = 80, maxEquipLevel = 99, equipType = 24,needItemId1 = 11000546,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel = 80, maxEquipLevel = 99, equipType = 28,needItemId1 = 11000546,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel = 80, maxEquipLevel = 99, equipType = 23,needItemId1 = 11000547,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel = 80, maxEquipLevel = 99, equipType = 20,needItemId1 = 11000547,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel = 80, maxEquipLevel = 99, equipType = 26,needItemId1 = 11000547,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel = 80, maxEquipLevel = 99, equipType = 22,needItemId1 = 11000547,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel = 80, maxEquipLevel = 99, equipType = 25,needItemId1 = 11000548,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel = 80, maxEquipLevel = 99, equipType = 27,needItemId1 = 11000548,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel = 80, maxEquipLevel = 99, equipType = 29,needItemId1 = 11000548,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
																									          
								{minEquipLevel =100, maxEquipLevel =119, equipType = 1, needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel =100, maxEquipLevel =119, equipType = 2, needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel =100, maxEquipLevel =119, equipType = 3, needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel =100, maxEquipLevel =119, equipType = 4, needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel =100, maxEquipLevel =119, equipType = 5, needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel =100, maxEquipLevel =119, equipType = 6, needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel =100, maxEquipLevel =119, equipType = 7, needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel =100, maxEquipLevel =119, equipType = 8, needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel =100, maxEquipLevel =119, equipType = 9, needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel =100, maxEquipLevel =119, equipType = 10,needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel =100, maxEquipLevel =119, equipType = 11,needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel =100, maxEquipLevel =119, equipType = 12,needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel =100, maxEquipLevel =119, equipType = 35,needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel =100, maxEquipLevel =119, equipType = 36,needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel =100, maxEquipLevel =119, equipType = 37,needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel =100, maxEquipLevel =119, equipType = 38,needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel =100, maxEquipLevel =119, equipType = 39,needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel =100, maxEquipLevel =119, equipType = 40,needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel =100, maxEquipLevel =119, equipType = 41,needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel =100, maxEquipLevel =119, equipType = 42,needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel =100, maxEquipLevel =119, equipType = 43,needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel =100, maxEquipLevel =119, equipType = 44,needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel =100, maxEquipLevel =119, equipType = 45,needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel =100, maxEquipLevel =119, equipType = 46,needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel =100, maxEquipLevel =119, equipType = 21,needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel =100, maxEquipLevel =119, equipType = 24,needItemId1 = 11000546,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel =100, maxEquipLevel =119, equipType = 28,needItemId1 = 11000546,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel =100, maxEquipLevel =119, equipType = 23,needItemId1 = 11000547,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel =100, maxEquipLevel =119, equipType = 20,needItemId1 = 11000547,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel =100, maxEquipLevel =119, equipType = 26,needItemId1 = 11000547,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel =100, maxEquipLevel =119, equipType = 22,needItemId1 = 11000547,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel =100, maxEquipLevel =119, equipType = 25,needItemId1 = 11000548,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel =100, maxEquipLevel =119, equipType = 27,needItemId1 = 11000548,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel =100, maxEquipLevel =119, equipType = 29,needItemId1 = 11000548,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
																									          
								{minEquipLevel =120, maxEquipLevel =139, equipType = 1, needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel =120, maxEquipLevel =139, equipType = 2, needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel =120, maxEquipLevel =139, equipType = 3, needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel =120, maxEquipLevel =139, equipType = 4, needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel =120, maxEquipLevel =139, equipType = 5, needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel =120, maxEquipLevel =139, equipType = 6, needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel =120, maxEquipLevel =139, equipType = 7, needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel =120, maxEquipLevel =139, equipType = 8, needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel =120, maxEquipLevel =139, equipType = 9, needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel =120, maxEquipLevel =139, equipType = 10,needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel =120, maxEquipLevel =139, equipType = 11,needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel =120, maxEquipLevel =139, equipType = 12,needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel =120, maxEquipLevel =139, equipType = 35,needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel =120, maxEquipLevel =139, equipType = 36,needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel =120, maxEquipLevel =139, equipType = 37,needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel =120, maxEquipLevel =139, equipType = 38,needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel =120, maxEquipLevel =139, equipType = 39,needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel =120, maxEquipLevel =139, equipType = 40,needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel =120, maxEquipLevel =139, equipType = 41,needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel =120, maxEquipLevel =139, equipType = 42,needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel =120, maxEquipLevel =139, equipType = 43,needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel =120, maxEquipLevel =139, equipType = 44,needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel =120, maxEquipLevel =139, equipType = 45,needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel =120, maxEquipLevel =139, equipType = 46,needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel =120, maxEquipLevel =139, equipType = 21,needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel =120, maxEquipLevel =139, equipType = 24,needItemId1 = 11000546,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel =120, maxEquipLevel =139, equipType = 28,needItemId1 = 11000546,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel =120, maxEquipLevel =139, equipType = 23,needItemId1 = 11000547,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel =120, maxEquipLevel =139, equipType = 20,needItemId1 = 11000547,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel =120, maxEquipLevel =139, equipType = 26,needItemId1 = 11000547,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel =120, maxEquipLevel =139, equipType = 22,needItemId1 = 11000547,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel =120, maxEquipLevel =139, equipType = 25,needItemId1 = 11000548,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel =120, maxEquipLevel =139, equipType = 27,needItemId1 = 11000548,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel =120, maxEquipLevel =139, equipType = 29,needItemId1 = 11000548,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
																									          
								{minEquipLevel =140, maxEquipLevel =159, equipType = 1, needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel =140, maxEquipLevel =159, equipType = 2, needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel =140, maxEquipLevel =159, equipType = 3, needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel =140, maxEquipLevel =159, equipType = 4, needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel =140, maxEquipLevel =159, equipType = 5, needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel =140, maxEquipLevel =159, equipType = 6, needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel =140, maxEquipLevel =159, equipType = 7, needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel =140, maxEquipLevel =159, equipType = 8, needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel =140, maxEquipLevel =159, equipType = 9, needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel =140, maxEquipLevel =159, equipType = 10,needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel =140, maxEquipLevel =159, equipType = 11,needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel =140, maxEquipLevel =159, equipType = 12,needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel =140, maxEquipLevel =159, equipType = 35,needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel =140, maxEquipLevel =159, equipType = 36,needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel =140, maxEquipLevel =159, equipType = 37,needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel =140, maxEquipLevel =159, equipType = 38,needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel =140, maxEquipLevel =159, equipType = 39,needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel =140, maxEquipLevel =159, equipType = 40,needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel =140, maxEquipLevel =159, equipType = 41,needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel =140, maxEquipLevel =159, equipType = 42,needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel =140, maxEquipLevel =159, equipType = 43,needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel =140, maxEquipLevel =159, equipType = 44,needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel =140, maxEquipLevel =159, equipType = 45,needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel =140, maxEquipLevel =159, equipType = 46,needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel =140, maxEquipLevel =159, equipType = 21,needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel =140, maxEquipLevel =159, equipType = 24,needItemId1 = 11000546,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel =140, maxEquipLevel =159, equipType = 28,needItemId1 = 11000546,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel =140, maxEquipLevel =159, equipType = 23,needItemId1 = 11000547,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel =140, maxEquipLevel =159, equipType = 20,needItemId1 = 11000547,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel =140, maxEquipLevel =159, equipType = 26,needItemId1 = 11000547,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel =140, maxEquipLevel =159, equipType = 22,needItemId1 = 11000547,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel =140, maxEquipLevel =159, equipType = 25,needItemId1 = 11000548,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel =140, maxEquipLevel =159, equipType = 27,needItemId1 = 11000548,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel =140, maxEquipLevel =159, equipType = 29,needItemId1 = 11000548,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
																									          
								{minEquipLevel =160, maxEquipLevel =200, equipType = 1, needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel =160, maxEquipLevel =200, equipType = 2, needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel =160, maxEquipLevel =200, equipType = 3, needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel =160, maxEquipLevel =200, equipType = 4, needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel =160, maxEquipLevel =200, equipType = 5, needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel =160, maxEquipLevel =200, equipType = 6, needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel =160, maxEquipLevel =200, equipType = 7, needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel =160, maxEquipLevel =200, equipType = 8, needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel =160, maxEquipLevel =200, equipType = 9, needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel =160, maxEquipLevel =200, equipType = 10,needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel =160, maxEquipLevel =200, equipType = 11,needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel =160, maxEquipLevel =200, equipType = 12,needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel =160, maxEquipLevel =200, equipType = 35,needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel =160, maxEquipLevel =200, equipType = 36,needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel =160, maxEquipLevel =200, equipType = 37,needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel =160, maxEquipLevel =200, equipType = 38,needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel =160, maxEquipLevel =200, equipType = 39,needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel =160, maxEquipLevel =200, equipType = 40,needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel =160, maxEquipLevel =200, equipType = 41,needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel =160, maxEquipLevel =200, equipType = 42,needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel =160, maxEquipLevel =200, equipType = 43,needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel =160, maxEquipLevel =200, equipType = 44,needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel =160, maxEquipLevel =200, equipType = 45,needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel =160, maxEquipLevel =200, equipType = 46,needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel =160, maxEquipLevel =200, equipType = 21,needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel =160, maxEquipLevel =200, equipType = 24,needItemId1 = 11000546,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel =160, maxEquipLevel =200, equipType = 28,needItemId1 = 11000546,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel =160, maxEquipLevel =200, equipType = 23,needItemId1 = 11000547,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel =160, maxEquipLevel =200, equipType = 20,needItemId1 = 11000547,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel =160, maxEquipLevel =200, equipType = 26,needItemId1 = 11000547,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel =160, maxEquipLevel =200, equipType = 22,needItemId1 = 11000547,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel =160, maxEquipLevel =200, equipType = 25,needItemId1 = 11000548,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel =160, maxEquipLevel =200, equipType = 27,needItemId1 = 11000548,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								{minEquipLevel =160, maxEquipLevel =200, equipType = 29,needItemId1 = 11000548,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },


							} 

--任务文本描述
x800088_g_MissionName="装备鎏金（洗蓝）"

--MisDescEnd

--**********************************
--任务入口函数
--**********************************
function x800088_ProcEventEntry( sceneId, selfId, targetId )	--点击该任务后执行此脚本
end

--********************
--检测接受条件
--**********************************
function x800088_ProcAcceptCheck( sceneId, selfId, NPCId )

		return 1
		
end

function x800088_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

	AddQuestNumText(sceneId,x800088_g_ScriptId,x800088_g_MissionName,3);

end

--判断是否满足强化条件
function x800088_IsCanIntensify( sceneId, selfId, itemPos )
	
	--检查装备是否可以强化蓝属性
	if IsEquipCanOp( sceneId, selfId, itemPos, x800088_g_EquipOpType ) < 1 then
	
		local Readme = "该装备不能进行洗蓝强化！" 
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, Readme);
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,Readme,8,2)
			
		return 0
		
	end
	
	--检查装备是否俱有蓝属性
	local blueAttrCount = GetEquipBlueAttrCount( sceneId, selfId,itemPos )
	if blueAttrCount < 1 then
		local Readme = "该装备没有蓝属性,请确定放入的装备正确！" 
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, Readme);
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,Readme,8,2)
			
		return 0	
	end
	
	--判断是否黄装及以上	
	if GetEquipColorType( sceneId, selfId, itemPos ) < x800088_g_EquipColorYellow  then
	    			
    	local Readme = "黄色以上品质的装备才能进行洗蓝强化！" 
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, Readme);
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,Readme,8,2)
		
		return 0
		
	end
	
	--绑定的装备才能强化蓝属性
	if IsItemBind( sceneId, selfId, itemPos ) < 1 then
	    			
    	local Readme = "绑定的装备才能进行洗蓝强化！" 
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, Readme);
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,Readme,8,2)
		
		return 0	
		
	end
	
	--判断是否达到装备强化等级上限
	local intensifyCount = GetEquipBlueIntensifyCount( sceneId, selfId, itemPos )
	if intensifyCount >= x800088_g_MaxEquipIntensifyCount then
    	
    	local Readme = "装备洗蓝强化次数已达上限！" 
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, Readme);
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,Readme,8,2)
		
		return 0
			
	end
	
	--角色等级是否大于装备等级N级
	local requireLevel = 1000
	local equipLevel = GetEquipNeedLevelByBagPos( sceneId, selfId, itemPos )

	for i,itm in x800088_g_IntensifyCountList do
	
		if equipLevel >= itm.minEquipLevel and equipLevel <= itm.maxEquipLevel  then
			requireLevel = itm.requireLevel
			break
		end
		
	end	
		
	local diffLeve = GetLevel( sceneId, selfId ) - equipLevel
	
	if requireLevel>0 and diffLeve < requireLevel then
	    local showlevel = equipLevel+requireLevel
    	local Readme = "每隔"..requireLevel.."级才能对该装备强化1次，您的等级不足"..showlevel.."级，无法强化！" 
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, Readme);
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,Readme,8,2)
		
		return 0	
		
	end
		
	if requireLevel > 0 and floor ( diffLeve / requireLevel ) <= intensifyCount then
	    local showlevel = equipLevel+requireLevel*(intensifyCount+1)
    	local Readme = "每隔"..requireLevel.."级才能对该装备强化1次，您的等级不足"..showlevel.."级，无法继续强化！"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, Readme);
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,Readme,8,2)
		
		return 0
		
	end
	
	--计算装备对应的宝石
	local needItemId = -1
	local needItemNum = 1000
	local equipType = GetItemTypeByBagPos( sceneId, selfId, itemPos )
	local equipLevel = GetEquipNeedLevelByBagPos( sceneId, selfId, itemPos )
	
	for i,itm in x800088_g_NeedItemList do
	
		if equipLevel >= itm.minEquipLevel and equipLevel <= itm.maxEquipLevel and equipType == itm.equipType  then
			needItemId = itm.needItemId1
			needItemNum = itm.needItemNum1
			break
		end
		
	end		
		
	--获得玩家背包里宝石的数量,以检查是否有足够的宝石	
    local itemCount = GetItemCountInBag( sceneId, selfId, needItemId)
    if itemCount < needItemNum then
    			
    	local Readme = "精金不足，不能进行洗蓝强化！" 
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, Readme);
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,Readme,8,2)
		
		return 0
		
    end
    
    --计算装备等级对应的金钱
	local needMoney = 999999999
		
	for i,itm in x800088_g_IntensifyNeedMoney do
	
		if equipLevel >= itm.minEquipLevel and equipLevel <= itm.maxEquipLevel then
			needMoney = itm.needMoney
			break
		end
		
	end
	
	--扣除金钱
	if SpendMoney( sceneId, selfId, needMoney, x800088_g_GamePlayerID ) < 1  then
		
		local Readme = "很抱歉，您包裹中的现银（银卡）不足！" 
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, Readme);
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,Readme,8,2)
		
		return 0
		
	end
	
	--消耗材料
	if DelItem( sceneId, selfId,needItemId,needItemNum ) < 1 then
		
		return
		
	end
		
	return 1
	
end

--强化处理入口
function x800088_OnEquipBlueIntensify( sceneId, selfId, itemPos )	

	--条件判断
	if x800088_IsCanIntensify( sceneId, selfId, itemPos ) == 0  then
		
		--不够强化条件
		return
		
	end
	
	--得到装备鎏金（洗蓝）次数
	local intensifyCount = GetEquipBlueIntensifyCount( sceneId, selfId, itemPos ) + 1

	if intensifyCount > x800088_g_MaxEquipIntensifyCount then
		
		intensifyCount = x800088_g_MaxEquipIntensifyCount
			
	end
	
	--从表中恢复蓝属性
	ResetEquipBlueAttFromTB( sceneId, selfId,itemPos )	

	--得到当前装备蓝属性数量
	local blueAttrCount = GetEquipBlueAttrCount( sceneId, selfId,itemPos )
	
	for i=1, intensifyCount do
		
		local attrPos = random(1,blueAttrCount) - 1	
		
		--根据attrPos得到装备蓝属性ID	 
		local attrId = GetEquipBlueAttrIdByPos( sceneId, selfId,itemPos,attrPos )
		
		if attrId >= 0 then
		
			--增加装备鎏金（洗蓝）次数
			IncreaseEquipAttrIntensifyCount( sceneId, selfId, itemPos, attrId, 1 )	
			
			--设置新的蓝属性
			x800088_SetEquipBlueAttrByAttrId( sceneId, selfId, itemPos, attrId )	
				
		end
			
	end
	
	--强化完成：同步到客户端
	NotifyEquipWanFa( sceneId, selfId, x800088_g_BlueIntensifyType, 1 )

end

--修改蓝属性属性值
function x800088_SetEquipBlueAttrByAttrId( sceneId, selfId, itemPos, tabAttrId )

	--得到蓝属性强化次数
	local blueCount = 0
	
	local blueAttrValue = 0
		
	local attrId,value1,value2,value3,value4,value5,value6,value7,value8,value9,value10,value11,ReqIntensifyCount = GetEquipBlueIntensifyTB( sceneId, selfId, tabAttrId )
	
	local equipLevel = GetEquipNeedLevelByBagPos( sceneId, selfId, itemPos )
	
	if equipLevel >= x800088_g_IntensifyNeedMoney[1].minEquipLevel and equipLevel < x800088_g_IntensifyNeedMoney[1].maxEquipLevel then
		blueAttrValue = value1
	elseif equipLevel >= x800088_g_IntensifyNeedMoney[2].minEquipLevel and equipLevel < x800088_g_IntensifyNeedMoney[2].maxEquipLevel then
		blueAttrValue = value2
	elseif equipLevel >= x800088_g_IntensifyNeedMoney[3].minEquipLevel and equipLevel < x800088_g_IntensifyNeedMoney[3].maxEquipLevel then
		blueAttrValue = value3
	elseif equipLevel >= x800088_g_IntensifyNeedMoney[4].minEquipLevel and equipLevel < x800088_g_IntensifyNeedMoney[4].maxEquipLevel then
		blueAttrValue = value4
	elseif equipLevel >= x800088_g_IntensifyNeedMoney[5].minEquipLevel and equipLevel < x800088_g_IntensifyNeedMoney[5].maxEquipLevel then
		blueAttrValue = value5
	elseif equipLevel >= x800088_g_IntensifyNeedMoney[6].minEquipLevel and equipLevel < x800088_g_IntensifyNeedMoney[6].maxEquipLevel then
		blueAttrValue = value6
	elseif equipLevel >= x800088_g_IntensifyNeedMoney[7].minEquipLevel and equipLevel < x800088_g_IntensifyNeedMoney[7].maxEquipLevel then
		blueAttrValue = value7
	elseif equipLevel >= x800088_g_IntensifyNeedMoney[8].minEquipLevel and equipLevel < x800088_g_IntensifyNeedMoney[8].maxEquipLevel then
		blueAttrValue = value8
	elseif equipLevel >= x800088_g_IntensifyNeedMoney[9].minEquipLevel and equipLevel < x800088_g_IntensifyNeedMoney[9].maxEquipLevel then
		blueAttrValue = value9
	elseif equipLevel >= x800088_g_IntensifyNeedMoney[10].minEquipLevel and equipLevel < x800088_g_IntensifyNeedMoney[10].maxEquipLevel then
		blueAttrValue = value10
	elseif equipLevel >= x800088_g_IntensifyNeedMoney[11].minEquipLevel then
		blueAttrValue = value11
	end
	
	local currValue,IntensifyCount = GetEquipExtAttrByAttrId( sceneId, selfId, itemPos, tabAttrId )
	
	--修改蓝属性属性值
	
	local newValue = currValue
	if IntensifyCount > 0 and ReqIntensifyCount > 0 and mod(IntensifyCount,ReqIntensifyCount) == 0 then
		newValue = blueAttrValue + currValue;
	end
	
	--print (format("attrId:%d,ReqIntensifyCount:%d,IntensifyCount:%d,currValue:%d,blueAttrValue:%d,newValue:%d",attrId,ReqIntensifyCount,IntensifyCount,currValue,blueAttrValue,newValue))
	
	SetEquipExtAttrByAttrId( sceneId, selfId, itemPos, attrId, newValue )	
		
end

--判断是否满足重置条件
function x800088_IsCanReset( sceneId, selfId, itemPos )
	
	--得到装备鎏金（洗蓝）次数
	local intensifyCount = GetEquipBlueIntensifyCount( sceneId, selfId, itemPos )
	if intensifyCount < 1 then
		
		local Readme = "只有强化过的装备才能洗蓝回炉" 
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, Readme);
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,Readme,8,2)
			
		return 0	
		
	end
	
	--检查装备是否俱有蓝属性
	local blueAttrCount = GetEquipBlueAttrCount( sceneId, selfId,itemPos )
	if blueAttrCount < 1 then
		local Readme = "该装备没有蓝属性,请确定放入的装备正确！" 
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, Readme);
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,Readme,8,2)
			
		return 0	
	end
	
	--检查装备是否可以强化蓝属性
	if IsEquipCanOp( sceneId, selfId, itemPos, x800088_g_EquipOpType ) < 1 then
	
		local Readme = "该装备不能进行洗蓝强化！" 
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, Readme);
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,Readme,8,2)
			
		return 0
		
	end
	
	--判断是否黄装及以上	
	if GetEquipColorType( sceneId, selfId, itemPos ) < x800088_g_EquipColorYellow  then
	    			
    	local Readme = "黄色品质以上的装备才能进行洗蓝强化！" 
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, Readme);
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,Readme,8,2)
		
		return 0
		
	end
	
	--角色等级是否大于装备等级N级
	local requireLevel = 1000
	local equipLevel = GetEquipNeedLevelByBagPos( sceneId, selfId, itemPos )
	
	for i,itm in x800088_g_IntensifyCountList do
	
		if equipLevel >= itm.minEquipLevel and equipLevel <= itm.maxEquipLevel  then
			requireLevel = itm.requireLevel
			break
		end
		
	end	
	 	
	local diffLeve = GetLevel( sceneId, selfId ) - equipLevel
	
	if requireLevel>0 and diffLeve < requireLevel then
	
    	local Readme = "玩家等级必需大于等于装备等级"..requireLevel.."级以上才能进行洗蓝强化！" 
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, Readme);
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,Readme,8,2)
		
		return 0	
		
	end
	
	--计算装备对应的宝石
	local needItemId = -1
	local needItemNum = 1000
	local equipType = GetItemTypeByBagPos( sceneId, selfId, itemPos )
	local equipLevel = GetEquipNeedLevelByBagPos( sceneId, selfId, itemPos )
	
	for i,itm in x800088_g_NeedItemList do
	
		if equipLevel >= itm.minEquipLevel and equipLevel <= itm.maxEquipLevel and equipType == itm.equipType  then
			needItemId = itm.needItemId2
			needItemNum = itm.needItemNum2
			break
		end
		
	end		
		
	--获得玩家背包里宝石的数量,以检查是否有足够的宝石	
    local itemCount = GetItemCountInBag( sceneId, selfId, needItemId)
    if itemCount < needItemNum then
    			
    	local Readme = "蓝光火石不足，不能进行洗蓝回炉！" 
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, Readme);
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,Readme,8,2)
		
		return 0
		
    end
    
    --计算装备等级对应的金钱
	local needMoney = 999999999
		
	for i,itm in x800088_g_IntensifyNeedMoney do
	
		if equipLevel >= itm.minEquipLevel and equipLevel <= itm.maxEquipLevel then
			needMoney = itm.needMoney2
			break
		end
		
	end
	
	--扣除金钱
	if SpendMoney( sceneId, selfId, needMoney, x800088_g_GamePlayerID ) < 1  then
		
		local Readme = "很抱歉，您包裹中的现银（银卡）不足！" 
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, Readme);
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,Readme,8,2)
		
		return 0
		
	end
	
	--消耗材料
	if DelItem( sceneId, selfId,needItemId,needItemNum ) < 1 then
		
		return
		
	end
		
	return 1
	
end

--蓝属性重置入口
function x800088_OnEquipBlueReset( sceneId, selfId, itemPos )

	--条件判断
	if x800088_IsCanReset( sceneId, selfId, itemPos ) == 0  then
		
		--不够重置条件
		return
		
	end
	
	--得到装备鎏金（洗蓝）次数
	local intensifyCount = GetEquipBlueIntensifyCount( sceneId, selfId, itemPos )
	if intensifyCount > x800088_g_MaxEquipIntensifyCount then
		
		intensifyCount = x800088_g_MaxEquipIntensifyCount
			
	end
	
	--从表中恢复蓝属性
	ResetEquipBlueAttFromTB( sceneId, selfId,itemPos )	

	--得到当前装备蓝属性数量
	local blueAttrCount = GetEquipBlueAttrCount( sceneId, selfId,itemPos )
	
	for i=1, intensifyCount do
		
		local attrPos = random(1,blueAttrCount) - 1	
		
		--根据attrPos得到装备蓝属性ID	 
		local attrId = GetEquipBlueAttrIdByPos( sceneId, selfId,itemPos,attrPos )
		
		if attrId >= 0 then
		
			--增加装备鎏金（洗蓝）次数
			IncreaseEquipAttrIntensifyCount( sceneId, selfId, itemPos, attrId, 1 )	

			--设置新的蓝属性
			x800088_SetEquipBlueAttrByAttrId( sceneId, selfId, itemPos, attrId )	
					
		end
			
	end
	
	--重置完成：同步到客户端
	NotifyEquipWanFa( sceneId, selfId, x800088_g_BlueResetType, 1 )
	
end