
--MisDescBegin
--�ű���
x800088_g_ScriptId = 800088

--���װ����չ��������
x800088_g_MaxEquipExtAttr = 8

--������ǿ���Ĳ�������
x800088_g_EquipOpType = 12

--��װ��ɫֵ
x800088_g_EquipColorYellow = 4

--װ�����ǿ������
x800088_g_MaxEquipIntensifyCount = 9

--�淨ID
x800088_g_GamePlayerID = 1591

--������ǿ���ڴ����淨�е����ͣ���Ӧ����EQUIP_WANFA_TYPE_BLUE_INTENSIFY
x800088_g_BlueIntensifyType = 20

--EQUIP_WANFA_TYPE_BLUE_RESET
x800088_g_BlueResetType = 21

--ǿ���ȼ�����
x800088_g_IntensifyCountList = {	
									{ minEquipLevel = 20, maxEquipLevel = 39, requireLevel =10 },	--װ���ȼ�20��39��������ȼ�����װ���ȼ�10��ǿ��һ��
									{ minEquipLevel = 40, maxEquipLevel = 59, requireLevel = 6 },	--װ���ȼ�40��59��������ȼ�����װ���ȼ�6��ǿ��һ��	
									{ minEquipLevel = 60, maxEquipLevel = 79, requireLevel = 5 },	--װ���ȼ�60��79��������ȼ�����װ���ȼ�5��ǿ��һ��
									{ minEquipLevel = 80, maxEquipLevel = 99, requireLevel = 2 },	--װ���ȼ�80��99��������ȼ�����װ���ȼ�2��ǿ��һ��
								    { minEquipLevel = 100,maxEquipLevel = 160,requireLevel = 0 },	--װ���ȼ�100��160��������ȼ�����װ���ȼ�1��ǿ��һ��										
								}

--ǿ��ʱ��Ҫ��money
x800088_g_IntensifyNeedMoney = 	{
									{minEquipLevel = 20, maxEquipLevel = 39,  needMoney = 6000,    needMoney2 = 10000,},	--װ���ȼ�20��39������ҪMoney6000��
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

--ǿ��ʱ��Ҫ�Ĳ���
x800088_g_NeedItemList = 	{
								--��������װ��(EQUIP_TYPE)��Ӧ����ƷID������: item1Ϊǿ�����ϣ�item2Ϊ��ͯ����
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
								--���и���װ����Ӧ����Ʒ
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
								--���¶�Ӧ����Ʒ					
								{minEquipLevel = 20, maxEquipLevel = 39, equipType = 21,needItemId1 = 11000545,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },		
								--������Ӧ����Ʒ						
								{minEquipLevel = 20, maxEquipLevel = 39, equipType = 24,needItemId1 = 11000546,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },			
								--��ָ��Ӧ����Ʒ							
								{minEquipLevel = 20, maxEquipLevel = 39, equipType = 28,needItemId1 = 11000546,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },		
								--�·���Ӧ����Ʒ	
								{minEquipLevel = 20, maxEquipLevel = 39, equipType = 23,needItemId1 = 11000547,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },		
								--ñ��Ӧ����ƷID		
								{minEquipLevel = 20, maxEquipLevel = 39, equipType = 20,needItemId1 = 11000547,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },
								--������Ӧ����Ʒ	
								{minEquipLevel = 20, maxEquipLevel = 39, equipType = 26,needItemId1 = 11000547,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },																
								--�����Ӧ����Ʒ	
								{minEquipLevel = 20, maxEquipLevel = 39, equipType = 22,needItemId1 = 11000547,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },	
								--���ֶ�Ӧ����Ʒ	
								{minEquipLevel = 20, maxEquipLevel = 39, equipType = 25,needItemId1 = 11000548,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },	
								--ѥ�Ӷ�Ӧ����Ʒ
								{minEquipLevel = 20, maxEquipLevel = 39, equipType = 27,needItemId1 = 11000548,needItemNum1 = 1,needItemId2 = 11000544,needItemNum2 = 1 },		
								--�����Ӧ����Ʒ
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

--�����ı�����
x800088_g_MissionName="װ���̽�ϴ����"

--MisDescEnd

--**********************************
--������ں���
--**********************************
function x800088_ProcEventEntry( sceneId, selfId, targetId )	--����������ִ�д˽ű�
end

--********************
--����������
--**********************************
function x800088_ProcAcceptCheck( sceneId, selfId, NPCId )

		return 1
		
end

function x800088_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

	AddQuestNumText(sceneId,x800088_g_ScriptId,x800088_g_MissionName,3);

end

--�ж��Ƿ�����ǿ������
function x800088_IsCanIntensify( sceneId, selfId, itemPos )
	
	--���װ���Ƿ����ǿ��������
	if IsEquipCanOp( sceneId, selfId, itemPos, x800088_g_EquipOpType ) < 1 then
	
		local Readme = "��װ�����ܽ���ϴ��ǿ����" 
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, Readme);
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,Readme,8,2)
			
		return 0
		
	end
	
	--���װ���Ƿ����������
	local blueAttrCount = GetEquipBlueAttrCount( sceneId, selfId,itemPos )
	if blueAttrCount < 1 then
		local Readme = "��װ��û��������,��ȷ�������װ����ȷ��" 
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, Readme);
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,Readme,8,2)
			
		return 0	
	end
	
	--�ж��Ƿ��װ������	
	if GetEquipColorType( sceneId, selfId, itemPos ) < x800088_g_EquipColorYellow  then
	    			
    	local Readme = "��ɫ����Ʒ�ʵ�װ�����ܽ���ϴ��ǿ����" 
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, Readme);
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,Readme,8,2)
		
		return 0
		
	end
	
	--�󶨵�װ������ǿ��������
	if IsItemBind( sceneId, selfId, itemPos ) < 1 then
	    			
    	local Readme = "�󶨵�װ�����ܽ���ϴ��ǿ����" 
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, Readme);
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,Readme,8,2)
		
		return 0	
		
	end
	
	--�ж��Ƿ�ﵽװ��ǿ���ȼ�����
	local intensifyCount = GetEquipBlueIntensifyCount( sceneId, selfId, itemPos )
	if intensifyCount >= x800088_g_MaxEquipIntensifyCount then
    	
    	local Readme = "װ��ϴ��ǿ�������Ѵ����ޣ�" 
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, Readme);
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,Readme,8,2)
		
		return 0
			
	end
	
	--��ɫ�ȼ��Ƿ����װ���ȼ�N��
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
    	local Readme = "ÿ��"..requireLevel.."�����ܶԸ�װ��ǿ��1�Σ����ĵȼ�����"..showlevel.."�����޷�ǿ����" 
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, Readme);
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,Readme,8,2)
		
		return 0	
		
	end
		
	if requireLevel > 0 and floor ( diffLeve / requireLevel ) <= intensifyCount then
	    local showlevel = equipLevel+requireLevel*(intensifyCount+1)
    	local Readme = "ÿ��"..requireLevel.."�����ܶԸ�װ��ǿ��1�Σ����ĵȼ�����"..showlevel.."�����޷�����ǿ����"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, Readme);
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,Readme,8,2)
		
		return 0
		
	end
	
	--����װ����Ӧ�ı�ʯ
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
		
	--�����ұ����ﱦʯ������,�Լ���Ƿ����㹻�ı�ʯ	
    local itemCount = GetItemCountInBag( sceneId, selfId, needItemId)
    if itemCount < needItemNum then
    			
    	local Readme = "�����㣬���ܽ���ϴ��ǿ����" 
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, Readme);
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,Readme,8,2)
		
		return 0
		
    end
    
    --����װ���ȼ���Ӧ�Ľ�Ǯ
	local needMoney = 999999999
		
	for i,itm in x800088_g_IntensifyNeedMoney do
	
		if equipLevel >= itm.minEquipLevel and equipLevel <= itm.maxEquipLevel then
			needMoney = itm.needMoney
			break
		end
		
	end
	
	--�۳���Ǯ
	if SpendMoney( sceneId, selfId, needMoney, x800088_g_GamePlayerID ) < 1  then
		
		local Readme = "�ܱ�Ǹ���������е����������������㣡" 
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, Readme);
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,Readme,8,2)
		
		return 0
		
	end
	
	--���Ĳ���
	if DelItem( sceneId, selfId,needItemId,needItemNum ) < 1 then
		
		return
		
	end
		
	return 1
	
end

--ǿ���������
function x800088_OnEquipBlueIntensify( sceneId, selfId, itemPos )	

	--�����ж�
	if x800088_IsCanIntensify( sceneId, selfId, itemPos ) == 0  then
		
		--����ǿ������
		return
		
	end
	
	--�õ�װ���̽�ϴ��������
	local intensifyCount = GetEquipBlueIntensifyCount( sceneId, selfId, itemPos ) + 1

	if intensifyCount > x800088_g_MaxEquipIntensifyCount then
		
		intensifyCount = x800088_g_MaxEquipIntensifyCount
			
	end
	
	--�ӱ��лָ�������
	ResetEquipBlueAttFromTB( sceneId, selfId,itemPos )	

	--�õ���ǰװ������������
	local blueAttrCount = GetEquipBlueAttrCount( sceneId, selfId,itemPos )
	
	for i=1, intensifyCount do
		
		local attrPos = random(1,blueAttrCount) - 1	
		
		--����attrPos�õ�װ��������ID	 
		local attrId = GetEquipBlueAttrIdByPos( sceneId, selfId,itemPos,attrPos )
		
		if attrId >= 0 then
		
			--����װ���̽�ϴ��������
			IncreaseEquipAttrIntensifyCount( sceneId, selfId, itemPos, attrId, 1 )	
			
			--�����µ�������
			x800088_SetEquipBlueAttrByAttrId( sceneId, selfId, itemPos, attrId )	
				
		end
			
	end
	
	--ǿ����ɣ�ͬ�����ͻ���
	NotifyEquipWanFa( sceneId, selfId, x800088_g_BlueIntensifyType, 1 )

end

--�޸�����������ֵ
function x800088_SetEquipBlueAttrByAttrId( sceneId, selfId, itemPos, tabAttrId )

	--�õ�������ǿ������
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
	
	--�޸�����������ֵ
	
	local newValue = currValue
	if IntensifyCount > 0 and ReqIntensifyCount > 0 and mod(IntensifyCount,ReqIntensifyCount) == 0 then
		newValue = blueAttrValue + currValue;
	end
	
	--print (format("attrId:%d,ReqIntensifyCount:%d,IntensifyCount:%d,currValue:%d,blueAttrValue:%d,newValue:%d",attrId,ReqIntensifyCount,IntensifyCount,currValue,blueAttrValue,newValue))
	
	SetEquipExtAttrByAttrId( sceneId, selfId, itemPos, attrId, newValue )	
		
end

--�ж��Ƿ�������������
function x800088_IsCanReset( sceneId, selfId, itemPos )
	
	--�õ�װ���̽�ϴ��������
	local intensifyCount = GetEquipBlueIntensifyCount( sceneId, selfId, itemPos )
	if intensifyCount < 1 then
		
		local Readme = "ֻ��ǿ������װ������ϴ����¯" 
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, Readme);
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,Readme,8,2)
			
		return 0	
		
	end
	
	--���װ���Ƿ����������
	local blueAttrCount = GetEquipBlueAttrCount( sceneId, selfId,itemPos )
	if blueAttrCount < 1 then
		local Readme = "��װ��û��������,��ȷ�������װ����ȷ��" 
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, Readme);
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,Readme,8,2)
			
		return 0	
	end
	
	--���װ���Ƿ����ǿ��������
	if IsEquipCanOp( sceneId, selfId, itemPos, x800088_g_EquipOpType ) < 1 then
	
		local Readme = "��װ�����ܽ���ϴ��ǿ����" 
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, Readme);
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,Readme,8,2)
			
		return 0
		
	end
	
	--�ж��Ƿ��װ������	
	if GetEquipColorType( sceneId, selfId, itemPos ) < x800088_g_EquipColorYellow  then
	    			
    	local Readme = "��ɫƷ�����ϵ�װ�����ܽ���ϴ��ǿ����" 
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, Readme);
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,Readme,8,2)
		
		return 0
		
	end
	
	--��ɫ�ȼ��Ƿ����װ���ȼ�N��
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
	
    	local Readme = "��ҵȼ�������ڵ���װ���ȼ�"..requireLevel.."�����ϲ��ܽ���ϴ��ǿ����" 
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, Readme);
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,Readme,8,2)
		
		return 0	
		
	end
	
	--����װ����Ӧ�ı�ʯ
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
		
	--�����ұ����ﱦʯ������,�Լ���Ƿ����㹻�ı�ʯ	
    local itemCount = GetItemCountInBag( sceneId, selfId, needItemId)
    if itemCount < needItemNum then
    			
    	local Readme = "�����ʯ���㣬���ܽ���ϴ����¯��" 
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, Readme);
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,Readme,8,2)
		
		return 0
		
    end
    
    --����װ���ȼ���Ӧ�Ľ�Ǯ
	local needMoney = 999999999
		
	for i,itm in x800088_g_IntensifyNeedMoney do
	
		if equipLevel >= itm.minEquipLevel and equipLevel <= itm.maxEquipLevel then
			needMoney = itm.needMoney2
			break
		end
		
	end
	
	--�۳���Ǯ
	if SpendMoney( sceneId, selfId, needMoney, x800088_g_GamePlayerID ) < 1  then
		
		local Readme = "�ܱ�Ǹ���������е����������������㣡" 
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, Readme);
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,Readme,8,2)
		
		return 0
		
	end
	
	--���Ĳ���
	if DelItem( sceneId, selfId,needItemId,needItemNum ) < 1 then
		
		return
		
	end
		
	return 1
	
end

--�������������
function x800088_OnEquipBlueReset( sceneId, selfId, itemPos )

	--�����ж�
	if x800088_IsCanReset( sceneId, selfId, itemPos ) == 0  then
		
		--������������
		return
		
	end
	
	--�õ�װ���̽�ϴ��������
	local intensifyCount = GetEquipBlueIntensifyCount( sceneId, selfId, itemPos )
	if intensifyCount > x800088_g_MaxEquipIntensifyCount then
		
		intensifyCount = x800088_g_MaxEquipIntensifyCount
			
	end
	
	--�ӱ��лָ�������
	ResetEquipBlueAttFromTB( sceneId, selfId,itemPos )	

	--�õ���ǰװ������������
	local blueAttrCount = GetEquipBlueAttrCount( sceneId, selfId,itemPos )
	
	for i=1, intensifyCount do
		
		local attrPos = random(1,blueAttrCount) - 1	
		
		--����attrPos�õ�װ��������ID	 
		local attrId = GetEquipBlueAttrIdByPos( sceneId, selfId,itemPos,attrPos )
		
		if attrId >= 0 then
		
			--����װ���̽�ϴ��������
			IncreaseEquipAttrIntensifyCount( sceneId, selfId, itemPos, attrId, 1 )	

			--�����µ�������
			x800088_SetEquipBlueAttrByAttrId( sceneId, selfId, itemPos, attrId )	
					
		end
			
	end
	
	--������ɣ�ͬ�����ͻ���
	NotifyEquipWanFa( sceneId, selfId, x800088_g_BlueResetType, 1 )
	
end