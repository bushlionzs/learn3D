---------------------------------------------------------------------------------------------------
--地图的脚本文件
---------------------------------------------------------------------------------------------------

x888888_g_defaultRelive_SceneID_1	= 11;
x888888_g_defaultRelive_SceneID_2	= 11;
x888888_g_ReliveType 				= { OriginLosslessRelive=0,CityPosRelive=1,SceneRelive=2}									--0:原地无损复活    1:城市定点复活	2:地图复活

x888888_g_BattleSceneList 			= {
										{"zhanchang_banghuizhanchang/zhanchang_banghuizhanchang.scn",			GUILDBATTLE_SCRIPTID	},	--帮会战场
										{"zhanchang_guowangzhanchang/zhanchang_guowangzhanchang.scn",			KINGBATTLE_FLOW_SCRIPT	},	--国王争夺战
										{"zhanchang_shuangrenzhanchang/zhanchang_shuangrenzhanchang.scn",		PVP2V2_BATTLE_SCRIPT	},	--PVP2v2竞技场
										{"zhanchang_shuangrenzhanchang/zhanchang_shuangrenzhanchang.scn",		PVP2V2_BATTLE_SCRIPT	},	--PVP2v2竞技场
										{"zhanchang_shuangrenzhanchang/zhanchang_shuangrenzhanchang.scn",		PVP2V2_BATTLE_SCRIPT	},  --PVP2v2竞技场
										{"zhanchang_shijiebeizhanchang/zhanchang_shijiebeizhanchang.scn",	    GUILD_CONTEND_SCRIPT	},	--世界杯
										{"zhanchang_liurenzhanchang/zhanchang_liurenzhanchang.scn",							PVP6V6_BATTLE_SCRIPT	},	--PVP2v2竞技场
										{"zhanchang_zhuqueshouhu/zhanchang_zhuqueshouhu.scn",					ZHUQUE_BATTLE_SCRIPT	},	--朱雀守护
										{"zhanchang_qinglongshouhu/zhanchang_qinglongshouhu.scn",				QINGLONG_BATTLE_SCRIPT	},	--青龙守护
--										{"zhanchang_lingzhuzhanchang/zhanchang_lingzhuzhanchang.scn",			LAIRD_BATTLE_SCRIPT		},	--据点争夺
										{"zhanchang_mshuangrenzhanchang/zhanchang_mshuangrenzhanchang.scn",		MPVP2V2_BATTLE_SCRIPT	},	--跨服PVP2v2竞技场	
							   		  }
							   		  
x888888_g_LairdSceneList			= {
										{"yewai_caizhoucheng/yewai_caizhoucheng.scn",							LAIRD_BATTLE_SCRIPT, 6	},	--据点争夺 6
										{"yewai_suiyecheng/yewai_suiyecheng.scn",								LAIRD_BATTLE_SCRIPT, 9	},	--据点争夺 9
										{"yewai_bageda/yewai_bageda.scn",										LAIRD_BATTLE_SCRIPT,13	},	--据点争夺13
										{"yewai_jifugongguo/yewai_jifugongguo.scn",								LAIRD_BATTLE_SCRIPT,18	},	--据点争夺18
										{"yewai_shenshengluomadiguo/yewai_shenshengluomadiguo.scn",				LAIRD_BATTLE_SCRIPT,21	},	--据点争夺21
										{"yewai_yelusaleng/yewai_yelusaleng.scn",								LAIRD_BATTLE_SCRIPT,24	},	--据点争夺24
										{"test/test.scn",														LAIRD_BATTLE_SCRIPT,27	},	--据点争夺27
										{"test/test.scn",														LAIRD_BATTLE_SCRIPT,31	},	--据点争夺31
										{"test/test.scn",														LAIRD_BATTLE_SCRIPT,34	},	--据点争夺34
									  }
					   		
x888888_g_expTable 					= {
										[21]={210000,	168},
										[22]={220000,	176},
										[23]={230000,	184},
										[24]={240000,	192},
										[25]={250000,	200},
										[26]={260000,	208},
										[27]={270000,	216},
										[28]={280000,	224},
										[29]={290000,	232},
										[30]={300000,	240},
										[31]={310000,	248},
										[32]={320000,	256},
										[33]={330000,	264},
										[34]={340000,	272},
										[35]={350000,	280},
										[36]={360000,	288},
										[37]={370000,	296},
										[38]={380000,	304},
										[39]={390000,	312},
										[40]={600000,	1000},
										[41]={615000,	1025},
										[42]={630000,	1050},
										[43]={645000,	1075},
										[44]={660000,	1100},
										[45]={675000,	1125},
										[46]={690000,	1150},
										[47]={705000,	1175},
										[48]={720000,	1200},
										[49]={735000,	1225},
										[50]={750000,	1250},
										
										[51]={765000,	1275},
										[52]={780000,	1300},
										[53]={795000,	1325},
										[54]={810000,	1350},
										[55]={825000,	1375},
										[56]={840000,	1400},
										[57]={855000,	1425},
										[58]={870000,	1450},
										[59]={885000,	1475},
										[60]={1800000,	6000},
										[61]={1830000,	6100},
										[62]={1860000,	6200},
										[63]={1890000,	6300},
										[64]={1920000,	6400},
										[65]={1950000,	6500},
										[66]={1980000,	6600},
										[67]={2010000,	6700},
										[68]={2040000,	6800},
										[69]={2070000,	6900},
										[70]={8400000,	28000},
										[71]={8520000,	28400},
										[72]={8640000,	28800},
										[73]={8760000,	29200},
										[74]={8880000,	29600},
										[75]={9000000,	30000},
										[76]={9120000,	30400},
										[77]={9240000,	30800},
										[78]={9360000,	31200},
										[79]={9480000,	31600},
										[80]={14400000,	48000},

										[81]={14580000,	48600},
										[82]={14760000,	49200},
										[83]={14940000,	49800},
										[84]={15120000,	50400},
										[85]={15300000,	51000},
										[86]={15480000,	51600},
										[87]={15660000,	52200},
										[88]={15840000,	52800},
										[89]={16020000,	53400},
										[90]={27000000,	90000},
										[91]={27300000,	91000},
										[92]={27600000,	92000},
										[93]={27900000,	93000},
										[94]={28200000,	94000},
										[95]={28500000,	95000},
										[96]={28800000,	96000},
										[97]={29100000,	97000},
										[98]={29400000,	98000},
										[99]={29700000,	99000},
										[100]={30000000,	100000},

										[101]={30300000, 101000},  
										[102]={30600000, 102000},  
										[103]={30900000, 103000},  
										[104]={31200000, 104000},  
										[105]={31500000, 105000},  
										[106]={31800000, 106000},  
										[107]={32100000, 107000},  
										[108]={32400000, 108000},  
										[109]={32700000, 109000},  
										[110]={33000000, 110000},  
										[111]={33300000, 111000},  
										[112]={33600000, 112000},  
										[113]={33900000, 113000},  
										[114]={34200000, 114000},  
										[115]={34500000, 115000},  
										[116]={34800000, 116000},  
										[117]={35100000, 117000},  
										[118]={35400000, 118000},  
										[119]={35700000, 119000},  
										[120]={36000000, 120000},  
										[121]={36300000, 121000},  
										[122]={36600000, 122000},  
										[123]={36900000, 123000},  
										[124]={37200000, 124000},  
										[125]={37500000, 125000},  
										[126]={37800000, 126000},  
										[127]={38100000, 127000},  
										[128]={38400000, 128000},  
										[129]={38700000, 129000},  
										[130]={39000000, 130000},  
										[131]={39300000, 131000},  
										[132]={39600000, 132000},  
										[133]={39900000, 133000},  
										[134]={40200000, 134000},  
										[135]={40500000, 135000},  
										[136]={40800000, 136000},  
										[137]={41100000, 137000},  
										[138]={41400000, 138000},  
										[139]={41700000, 139000},  
										[140]={42000000, 140000},  
										[141]={42300000, 141000},  
										[142]={42600000, 142000},  
										[143]={42900000, 143000},  
										[144]={43200000, 144000},  
										[145]={43500000, 145000},  
										[146]={43800000, 146000},  
										[147]={44100000, 147000},  
										[148]={44400000, 148000},  
										[149]={44700000, 149000},  
										[150]={45000000, 150000},  
										[151]={45300000, 151000},  
										[152]={45600000, 152000},  
										[153]={45900000, 153000},  
										[154]={46200000, 154000},  
										[155]={46500000, 155000},  
										[156]={46800000, 156000},  
										[157]={47100000, 157000},  
										[158]={47400000, 158000},  
										[159]={47700000, 159000},  
										[160]={48000000, 160000},  

									  }
						
						
x888888_g_CheckScriptTable 			= { 300501,300573,300351,300352,300350,300782}																	--做特殊检查的任务脚本
x888888_g_HP_SkillID	   			= { 604,606,611,612,10527,10505,}																				--加血技能ID
x888888_g_PrisonMinPKVal			= 200																											--PK值大于200时杀死本国玩家投入监狱(国王不受此限制)
x888888_g_DonotAddGoodbadTable		= { 																											--
										0,15,19,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,82,88,150,151,152,
										153,154,155,156,157,158,159,160,161,162,163,164,165,166,167,182,188,250,251,252,
										253,254,255,256,257,258,259,260,261,262,263,264,265,266,267,282,288,350,351,352,
										353,354,355,356,357,358,359,360,361,362,363,364,365,366,367,382,388
									  }
x888888_g_PVP6V6ItemList			= {12041200,}																									--PVP6v6战场物品列表
x888888_g_PVP6V6BufList				= {																												--PVP6v6战场BUF列表
										7910,7911,7912,7913,7914,7915,7916,7917,7918,7919,7920,7921,7922,7923,7924,7925,
										7926,7927,7928,7929,7930,7931,7932,7933,7934,7935,7936,7937,7938,7939,7940,7941,
										7942,7943,7944,7945,7946,7947,7948,7949,7950,7951,7952,7953,7954,7955,7956,7957,
										7958,7959,7960,7961,7962,7963,7964,7965,7966,7967,7968,7969,7987
									  }			
x888888_g_CountryBattleLite_BufID	= {8719,8720,8721,8722,8723,8724,8725,8726,8727}																--玩家BUFID,当玩家接受屠城战时,将从此表获取BUFID,此表按顺序为:楼兰,天山,昆仑,敦煌
x888888_g_Wiqi						= {10011001,10021001,10031001,10041001,10051001,10061001,10351001,10361001,10371001,10381001,10391001,10401001}	--武器
x888888_g_GuildBuildMissions		= {1369, 1370, 1371, 1372 }																						--帮会建设任务
x888888_g_GuildKillMonsterMission	= {7004,7716,7710,7704}																							--帮会杀怪任务
x888888_g_GuildChuYaoMission		= {7004,7716,7710,7704}																							--帮会除妖任务
x888888_g_HeiJinMission 			= {7001,7009,7010,7543,7544,7545}																				--官府押运任务（楼兰）
x888888_g_HeiJinMission1 			= {7620,7621,7622,7623,7624,7625}																				--官府押运任务（天山）
x888888_g_HeiJinMission2 			= {7614,7615,7616,7617,7618,7619}																				--官府押运任务（昆仑）
x888888_g_HeiJinMission3 			= {7608,7609,7610,7611,7612,7613}																				--官府押运任务（敦煌）

x888888_g_PaoQianMission			= {7556,7557,7558,7546,7547,7548}																				--黑金押运任务（楼兰）
x888888_g_PaoQianMission1			= {7638,7639,7640,7641,7642,7643}																				--黑金押运任务（天山）
x888888_g_PaoQianMission2			= {7632,7633,7634,7635,7636,7637}																				--黑金押运任务（昆仑）
x888888_g_PaoQianMission3			= {7626,7627,7628,7629,7630,7631}																				--黑金押运任务（敦煌）

x888888_g_YunYuFanMission			= {8080,8081,8082,8083,8084,8085,8086,8087,8088,8089,8090}														--云游贬任务
x888888_g_YiGuoDouQiMission			= {7596,7597,7598,7599}																							--楼兰异国夺旗任务
x888888_g_YiGuoDouQiMission1		= {7694,7695,7696,7697}																							--天山异国夺旗任务
x888888_g_YiGuoDouQiMission2		= {7690,7691,7692,7693}																							--昆仑异国夺旗任务
x888888_g_YiGuoDouQiMission3		= {7686,7687,7688,7689}																							--敦煌异国夺旗任务
x888888_g_TieSanMission				= {7537,7538,7539,7551,7552}																					--铁人三项任务

x888888_g_PlayerSyncLairdInfo = {
	{7760, 6, "蔡州城", "【国家】蔡州城进贡"},
	{7761, 9, "碎叶城", "【国家】碎叶城进贡"},
	{7762, 13, "巴格达", "【国家】巴格达进贡"},
	{7763, 18, "基辅公国", "【国家】基辅公国进贡"},
	{7764, 21, "神圣罗马帝国", "【国家】神圣罗马帝国进贡"},
	{7765, 24, "耶路撒冷", "【国家】耶路撒冷进贡"},
	{7766, 27, "福冈", "【国家】福冈进贡"},
	{7767, 31, "缅甸", "【国家】缅甸进贡"},
	{7768, 34, "爪哇岛", "【国家】爪哇岛进贡"},
}

-- 职业转换后清除原有被动技能列表，数组一维索引是当前职业转职前的职业ID，每次登录后清除原职业的被动技能
x888888_g_DispelSkillList           = {
                                        { 17150, 17151, 17152, 17153, 17154, 17155, 17156, 17157, 17158, 17159, 17160, 17161, 17162, 17163, 17164, 17165, 17166, 17167, 17168, 17169, 17170, 17171, 17172, 17173, 17174, 17175, 17176, 17177, 17178, 17179, 17180, 17181, 17182, 17183, 17184, 17185, 17186, 17187, 17188, 17189 }, 
                                        { 18160, 18161, 18162, 18163, 18164, 18165, 18166, 18167, 18168, 18169, 18170, 18171, 18172, 18173, 18174, 18175, 18176, 18177, 18178, 18179, 18180, 18181, 18182, 18183, 18184, 18185, 18186, 18187, 18188, 18189 }, 
                                        { 19120, 19121, 19122, 19123, 19124, 19125, 19126, 19127, 19128, 19129, 19130, 19131, 19132, 19133, 19134, 19135, 19136, 19137, 19138, 19139, 19140, 19141, 19142, 19143, 19144, 19145, 19146, 19147, 19148, 19149 }, 
                                        { 20120, 20121, 20122, 20123, 20124, 20125, 20126, 20127, 20128, 20129, 20130, 20131, 20132, 20133, 20134, 20135, 20136, 20137, 20138, 20139, 20140, 20141, 20142, 20143, 20144, 20145, 20146, 20147, 20148, 20149 }, 
                                        { 21110, 21111, 21112, 21113, 21114, 21115, 21116, 21117, 21118, 21119, 21120, 21121, 21122, 21123, 21124, 21125, 21126, 21127, 21128, 21129, 21130, 21131, 21132, 21133, 21134, 21135, 21136, 21137, 21138, 21139 }, 
                                        { 22000, 22001, 22002, 22003, 22004, 22005, 22006, 22007, 22008, 22009, 22010, 22011, 22012, 22013, 22014, 22015, 22016, 22017, 22018, 22019, 22180, 22181, 22182, 22183, 22184, 22185, 22186, 22187, 22188, 22189, 22190, 22191, 22192, 22193, 22194, 22195, 22196, 22197, 22198, 22199, 22200, 22201, 22202, 22203, 22204, 22205, 22206, 22207, 22208, 22209 }, 
                                        { 1341, 1342, 1343, 1344, 1345, 1346, 1347, 1348, 1349, 1350, 1351, 1352, 1353, 1354, 1355, 1356, 1357, 1358, 1359, 1360, 1361, 1362, 1363, 1364, 1365, 1366, 1367, 1368, 1369, 1370, 1371, 1372, 1373, 1374, 1375, 1376, 1377, 1378, 1379, 1380 }, 
                                        { 2121, 2122, 2123, 2124, 2125, 2126, 2127, 2128, 2129, 2130, 2131, 2132, 2133, 2134, 2135, 2136, 2137, 2138, 2139, 2140, 2141, 2142, 2143, 2144, 2145, 2146, 2147, 2148, 2149, 2150 }, 
                                        { 3131, 3132, 3133, 3134, 3135, 3136, 3137, 3138, 3139, 3140, 3141, 3142, 3143, 3144, 3145, 3146, 3147, 3148, 3149, 3150, 3151, 3152, 3153, 3154, 3155, 3156, 3157, 3158, 3159, 3160 }, 
                                        { 4121, 4122, 4123, 4124, 4125, 4126, 4127, 4128, 4129, 4130, 4131, 4132, 4133, 4134, 4135, 4136, 4137, 4138, 4139, 4140, 4141, 4142, 4143, 4144, 4145, 4146, 4147, 4148, 4149, 4150 }, 
                                        { 5131, 5132, 5133, 5134, 5135, 5136, 5137, 5138, 5139, 5140, 5141, 5142, 5143, 5144, 5145, 5146, 5147, 5148, 5149, 5150, 5151, 5152, 5153, 5154, 5155, 5156, 5157, 5158, 5159, 5160 }, 
                                        { 6201, 6202, 6203, 6204, 6205, 6206, 6207, 6208, 6209, 6210, 6131, 6132, 6133, 6134, 6135, 6136, 6137, 6138, 6139, 6140, 6141, 6142, 6143, 6144, 6145, 6146, 6147, 6148, 6149, 6150, 6151, 6152, 6153, 6154, 6155, 6156, 6157, 6158, 6159, 6160 }, 
}

--跨服双人战场场景内禁止使用的道具列表  蒙面巾,回城卷轴,领地传送,神行符,国王召集,帮会召集,队伍召集,铃铛召集
x888888_g_ForbidM2v2BattleUseItemList = {12030018, 12250008, 12030007, 12030031, 12250005, 12030015, 12030016, 12030019,12030001,12030002}

--跨服报名场景内禁止使用的道具列表  蒙面巾,国王召集,帮会召集,队伍召集,铃铛召集
x888888_g_ForbidMSignupUseItemList = {12030018, 12250005, 12030015, 12030016, 12030019,12030001,12030031,12030002,12030007}
-- 排行榜挑战顺序
x888888_g_TopList = {57, 17, 63, 49, 65, 37, 59, 31, 61, 43, 51, 45, 53, 47, 55, 15}

--额外战场功绩获得buf列表
x888888_g_ExaBattleHonourValueBufList = {9017}
--每周按比例增加的获得战场功绩上限buf列表
x888888_g_ExaBattleHonourRatioBufList = {9011, 9012, 9013}
--每周增加的获得战场功绩上限比例
x888888_g_ExaBattleHonourRatio = 20
--每周获得的战场功绩上限
x888888_g_BattleHonourWeekMaxValue = 1200

--专攻系数修改消耗
x888888_g_Zhuangong_Coefficient = 100 * 1000
--专攻引导任务ID
x888888_g_MissionId_Zhuangong = 4082

---------------------------------------------------------------------------------------------------
--初始化
---------------------------------------------------------------------------------------------------
function x888888_ProcMapInit( mapId )
	
	------------------
	--战场的固定处理--
	------------------
	local sceneType = GetSceneType(mapId) ;
	if sceneType == 2 or sceneType == 7 then
	
		--帮会战
		if x888888_GetBattleSceneTypeNM( mapId ) == GUILDBATTLE_SCRIPTID then
			CallScriptFunction(GUILDBATTLE_SCRIPTID,"OnMapInit",mapId)
			return
		end

        -- 世界杯
        if x888888_GetBattleSceneTypeNM( mapId ) == GUILD_CONTEND_SCRIPT then
            CallScriptFunction( GUILD_CONTEND_SCRIPT, "OnMapInit", mapId)
            return
        end
		
		--2v2战场初始化
		if x888888_GetBattleSceneTypeNM( mapId ) == PVP2V2_BATTLE_SCRIPT then
			CallScriptFunction(PVP2V2_BATTLE_SCRIPT,"OnMapInit",mapId)
			return
		end
		
		--6v6战场初始化
		if x888888_GetBattleSceneTypeNM( mapId ) == PVP6V6_BATTLE_SCRIPT then
			CallScriptFunction(PVP6V6_BATTLE_SCRIPT,"OnMapInit",mapId)
			return
		end		
		
		--朱雀
		if x888888_GetBattleSceneTypeNM( mapId ) == ZHUQUE_BATTLE_SCRIPT then
			CallScriptFunction(ZHUQUE_BATTLE_SCRIPT,"OnMapInit",mapId)
			return
		end
		
		--朱雀
		if x888888_GetBattleSceneTypeNM( mapId ) == QINGLONG_BATTLE_SCRIPT then
			CallScriptFunction(QINGLONG_BATTLE_SCRIPT,"OnMapInit",mapId)
			return
		end
		
		--跨服 2v2 战场
		if x888888_GetBattleSceneTypeNM(mapId) == MPVP2V2_BATTLE_SCRIPT then
			CallScriptFunction(MPVP2V2_BATTLE_SCRIPT, "OnMapInit", mapId)
			return
		end
	end
	
	if mapId == 37 then
		SetPatrolNoBreak(mapId,8,1)
	end
	
	
	--------------------
	--以下入口场景处理--
	--------------------
	--王城的数据处理
	if mapId == 50 or mapId == 150 or mapId == 250 or mapId == 350 then
		CallScriptFunction(COUNTRY_BATTLE_LITE_SCRIPT,"OnMapInit",mapId)			--屠城战
		CallScriptFunction(ZHUQUE_BATTLE_SCRIPT,"OnMapInit",mapId)					--朱雀
		CallScriptFunction(QINGLONG_BATTLE_SCRIPT,"OnMapInit",mapId)				--朱雀
		CallScriptFunction(LAIRD_BATTLE_SCRIPT,"OnMapInit",mapId)					--据点
        CallScriptFunction( GUILD_CONTEND_SCRIPT, "OnMapInit", mapId)				-- 世界杯
		return
	end
	
	--据点战
	if x888888_GetLairdSceneTypeNM( mapId ) == LAIRD_BATTLE_SCRIPT then
		CallScriptFunction(LAIRD_BATTLE_SCRIPT,"OnMapInit",mapId)
		return
	end
	
	--边境的数据处理
	if mapId == 51 or mapId == 151 or mapId == 251 or mapId == 351 then
		CallScriptFunction(COUNTRY_BATTLE_LITE_SCRIPT,"OnMapInit",mapId)			--屠城战
		return
	end
	
	--大都数据初始化
	if mapId == 0 then
		CallScriptFunction(PVP2V2_BATTLE_SCRIPT,"OnMapInit",mapId)					--2v2
		CallScriptFunction(PVP6V6_BATTLE_SCRIPT,"OnMapInit",mapId)					--6v6
		return
	end
	
	--屠城战的处理
	if x888888_IsCountryBattleLiteMap(mapId ) == 1 then                                            
	   CallScriptFunction(COUNTRY_BATTLE_LITE_SCRIPT,"OnMapInit",mapId)				--屠城战
	   return
	end
	
end

---------------------------------------------------------------------------------------------------
--定时器
---------------------------------------------------------------------------------------------------
function x888888_ProcMapTimer( mapId, nowTime )

	--地图计时器
	--sceneId表示地图号，nowTime表示当前时间（程序启动后的时间，单位毫秒）

	local sceneType = GetSceneType(mapId)
		
	if sceneType == 1 then --地图类型是副本
		
		CallScriptFunction(FUBEN_COMMON_SCRIPT, "OnFubenTimer", mapId, nowTime)		
	elseif sceneType == 2 or sceneType == 7 then  --地图类型是战场(包括跨服)
		
		local sceneScriptID = x888888_GetBattleSceneType(mapId)
	    if sceneScriptID ~= -1 then
	    	CallScriptFunction( sceneScriptID,"ProcTiming",mapId, nowTime)
	    end
	elseif sceneType == 8 then --地图类型是跨服报名场景
	
		--这里需要对每种报名场景脚本进行调用
	    CallScriptFunction(MPVP2V2_SIGNUP_SCRIPT, "ProcTiming", mapId, nowTime)
	else
		local sceneScriptID = x888888_GetLairdSceneType(mapId)
	    if sceneScriptID ~= -1 then
	    	CallScriptFunction( sceneScriptID,"ProcTiming",mapId, nowTime)
	    end
	end
end


---------------------------------------------------------------------------------------------------
--退出
---------------------------------------------------------------------------------------------------
function x888888_ProcMapQuit( mapId )
end


---------------------------------------------------------------------------------------------------
--新角色创建事件
---------------------------------------------------------------------------------------------------
function x888888_ProcMapPlayerFirstEnter( mapId, playerId )

	--设置缺省的信息
	local yifu = 10231001
	local shoutao = 10251001
	local xiezi = 10271001
	local ZhiYe= GetZhiye( mapId, playerId)
	local nCountry = GetCurCountry(mapId,playerId)
	local level = GetLevel( mapId,playerId) 
	
	CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", mapId, playerId, 1,1 ) -- 第二个 1 打开界面 0 关闭界面
	CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", mapId, playerId, 89,1 )
	
	if GetZhiye( mapId, playerId)==0 then
		AddSkillToPlayer(mapId, playerId, 31, 1, 2)
	elseif GetZhiye( mapId, playerId)==1 then
		AddSkillToPlayer(mapId, playerId, 32, 1, 2)
	elseif GetZhiye( mapId, playerId)==2 then
		AddSkillToPlayer(mapId, playerId, 33, 1, 2)
	elseif GetZhiye( mapId, playerId)==3 then
		AddSkillToPlayer(mapId, playerId, 34, 1, 2)
	elseif GetZhiye( mapId, playerId)==4 then
		AddSkillToPlayer(mapId, playerId, 35, 1, 2)
	elseif GetZhiye( mapId, playerId)==5 then
		AddSkillToPlayer(mapId, playerId, 36, 1, 2)
	elseif GetZhiye( mapId, playerId)==6 then
		AddSkillToPlayer(mapId, playerId, 4, 1, 2)
	elseif GetZhiye( mapId, playerId)==7 then
		AddSkillToPlayer(mapId, playerId, 5, 1, 2)
	elseif GetZhiye( mapId, playerId)==8 then
		AddSkillToPlayer(mapId, playerId, 6, 1, 2)
	elseif GetZhiye( mapId, playerId)==9 then
		AddSkillToPlayer(mapId, playerId, 7, 1, 2)
	elseif GetZhiye( mapId, playerId)==10 then
		AddSkillToPlayer(mapId, playerId, 8, 1, 2)
	elseif GetZhiye( mapId, playerId)==11 then
		AddSkillToPlayer(mapId, playerId, 9, 1, 2)			
	end
	
	BeginUICommand(mapId)
	EndUICommand(mapId)
	DispatchUICommand(mapId,playerId,18)

	BeginUICommand(mapId)
	UICommand_AddInt(mapId, 139)
	EndUICommand(mapId)
	DispatchUICommand(mapId,playerId,17)
	
	BeginAddItem(mapId)
		AddItem( mapId , 12030475, 1 )
	EndAddItem(mapId,playerId)
	AddItemListToPlayer(mapId,playerId)	
	
	if GetQMoneyToggle() > 0 then  --百元Q币兑换卡
		BeginAddItem(mapId)
			AddBindItem( mapId , 12030042, 1 )
		EndAddItem(mapId,playerId)
		AddItemListToPlayer(mapId,playerId)	
	end	
	
	BeginAddItem(mapId)
	AddItem( mapId,x888888_g_Wiqi[ZhiYe+1],1)
		AddItem( mapId,yifu,1)
		AddItem( mapId,shoutao,1)
		AddItem( mapId,xiezi,1)
	EndAddItem(mapId,playerId)
	AddItemListToPlayer(mapId,playerId)
	
	UseItem(mapId,playerId,x888888_g_Wiqi[ZhiYe+1])
	UseItem(mapId,playerId,yifu)
	UseItem(mapId,playerId,shoutao)
	UseItem(mapId,playerId,xiezi)
	
	AddSkillToPlayer(mapId, playerId, 16, 1, 7)
	BeginQuestEvent(mapId)
		AddQuestText(mapId,"#Y【新手】初入世界")
	AddQuestText(mapId,"\t欢迎来到成吉思汗的世界！请耐心阅读一下：#r　#r\t通过您的鼠标#G左键#W点击地面可以#G行走#W，点击游戏中的人物可以和他#G交谈#W。#r\t#W若您看到的NPC头顶有#Y金色的问号#W“#Y？#W”，您可以使用鼠标左键点击他#G完成任务#W。#r　#r\t现在，看到身旁的#G郭守谦#W头顶的金色问号#Y？#W了吗？他已经等候你许久了，和他谈谈吧。")
	AddQuestText(mapId," ")

	AddQuestText(mapId," ")
	EndQuestEvent()
	
	if level <=20 then
	if nCountry == 0 then
		DispatchQuestInfoNM(mapId, playerId, -1, 203500, 3200)
		AddQuest( mapId, playerId, 3200, 203500, 1, 0, 0)
		SetQuestByIndex(mapId,playerId,GetQuestIndexByID(mapId,playerId,3200),0,1)
		SetQuestByIndex(mapId,playerId,GetQuestIndexByID(mapId,playerId,3200),7,1)
		CallScriptFunction( SYSTEM_MAIL_SCRIPT, "firstintest",mapId, playerId)
	elseif nCountry == 1 then
		DispatchQuestInfoNM(mapId, playerId, -1, 203600, 3300)
		AddQuest( mapId, playerId, 3300, 203600, 1, 0, 0)
		SetQuestByIndex(mapId,playerId,GetQuestIndexByID(mapId,playerId,3300),0,1)
		SetQuestByIndex(mapId,playerId,GetQuestIndexByID(mapId,playerId,3300),7,1)
		CallScriptFunction( SYSTEM_MAIL_SCRIPT, "firstintest",mapId, playerId)
	elseif nCountry == 2 then
		DispatchQuestInfoNM(mapId, playerId, -1, 203550, 3400)
		AddQuest( mapId, playerId, 3400, 203550, 1, 0, 0)
		SetQuestByIndex(mapId,playerId,GetQuestIndexByID(mapId,playerId,3400),0,1)
		SetQuestByIndex(mapId,playerId,GetQuestIndexByID(mapId,playerId,3400),7,1)
		CallScriptFunction( SYSTEM_MAIL_SCRIPT, "firstintest",mapId, playerId)
	elseif nCountry == 3 then
		DispatchQuestInfoNM(mapId, playerId, -1, 203650, 3700)
		AddQuest( mapId, playerId, 3700, 203650, 1, 0, 0)
		SetQuestByIndex(mapId,playerId,GetQuestIndexByID(mapId,playerId,3700),0,1)
		SetQuestByIndex(mapId,playerId,GetQuestIndexByID(mapId,playerId,3700),7,1)
		CallScriptFunction( SYSTEM_MAIL_SCRIPT, "firstintest",mapId, playerId)
	end
	end
	--初始化玩家的活力值
	SetPlayerVigor(mapId, playerId, 48)

	--//add by zp on 2009-4-14
--	BeginAddItem(mapId)
--	AddItem( mapId, 12030301, 1 )
--	--AddItem( mapId, 12030306, 1 )
--	local ret = EndAddItem(mapId,playerId)
--	if ret > 0 then
--		AddItemListToPlayer(mapId,playerId)
--		
--		
--	else
--		BeginQuestEvent(mapId)
--		AddQuestText(mapId,"物品栏已满，无法得到物品！")
--		EndQuestEvent(mapId)
--		DispatchQuestTips(mapId,playerId)
--	end
	--//add end

end


function x888888_CheckMasterPrentic(mapId, playerId)

	-- 是否超过3天未登陆
	local time = 3600*24*3 --单位秒
	local loginTime = GetLoginTime(mapId, playerId); --单位秒
	local lastLogoutTime = GetLastLogoutTime(mapId, playerId); --单位秒
	if( loginTime - lastLogoutTime < time ) then
		return
	end
	local selfName	= GetName( mapId, playerId )
	-- 处理徒弟
	local index = 0
	while index < MAX_PRENTICE_NUM do
			local PrenticeGUID = GetPrenticeGUID( mapId, playerId, tonumber(index) );
			if( PrenticeGUID ~= -1 ) then
					local PrenticeName	= GetFriendName( mapId, playerId, PrenticeGUID )
					--发普通邮件给徒弟
					SendNormalMail( mapId, playerId, PrenticeName, "你的师父" .. selfName .. "已与你脱离了师徒关系。" )
					--发可执行邮件给徒弟
					SendScriptMail( mapId, PrenticeName, MAIL_EXPELPRENTICE, 0, GetGUID(mapId, playerId), 0, playerId )
					--最终清理门户
					ExpelPrentice( mapId, playerId, PrenticeGUID, 0 )
					--发普通邮件给师傅
					SendNormalMail( mapId, playerId, selfName, "你已经与你的徒弟" .. PrenticeName .. "脱离了师徒关系。" )
			end
			index = index + 1
	end

	-- 处理师傅
	local targetGUID = GetMasterGUID(mapId, playerId);
	if targetGUID == -1 then
		return
	end
	local MasterName = GetFriendName( mapId, playerId, targetGUID )
	if( MasterName == "") then
		return
	end
	--发普通邮件给师傅
	SendNormalMail(mapId, playerId, MasterName, "你的徒弟" .. selfName .. "已经与你解除了师徒关系。");
	--发可执行邮件给师傅
	local MyGUID = GetGUID( mapId, playerId )
	SendScriptMail( mapId, MasterName, MAIL_BETRAYMASTER, MyGUID, 2, 0, playerId )
	--叛师
	BetrayMaster(mapId, playerId);
	--发普通邮件给徒弟
	SendNormalMail( mapId, playerId, selfName, "你已经与" .. MasterName .. "解除了师徒关系。" )
end

---------------------------------------------------------------------------------------------------
--玩家进入新场景事件
---------------------------------------------------------------------------------------------------
function x888888_ProcMapPlayerEnter( mapId, playerId )
	

	--检查地图PK模式
	local SceneRestrictiveMode = GetSceneRestrictiveMode(mapId) ;
	if SceneRestrictiveMode >= 0 then
		SetCurPKMode( mapId, playerId, SceneRestrictiveMode, 0 )
	end
	
	--081217(齐亮)进入游戏前根据玩家上次退出游戏时所处的PK模式设置互斥状态
	local pkMode = GetPlayerPKMode( mapId, playerId)
	if pkMode ==2 then
		-- 22 = PLAYER_STATE_PKMODE，定义在ScriptGlobal.lua
		SetPlayerMutexState( mapId, playerId, PLAYER_STATE_PKMODE, 1)
	end

    -- 进入舞厅设置互斥状态
    if mapId == 14 then
        SetPlayerMutexState( mapId, playerId, PLAYER_STATE_DANCERY, 1)
    end

    -- 如果去大都并且身上有跳舞状态就清除
    if mapId == 0 and IsPlayerMutexState( mapId, playerId, PLAYER_STATE_DANCERY) == 1 then
        SetPlayerMutexState( mapId, playerId, PLAYER_STATE_DANCERY, 0)
    end

	--设置缺省的复活信息
	local sceneType = GetSceneType(mapId) ;

	if sceneType ~= 2 then      --帮会战地图

		--关闭积分栏
		SetGuildBattleDisable(mapId, playerId,1,0)
        TimerCommand( mapId, playerId, 1, GUILDBATTLE_TIMERID, GUILDBATTLE_TIMERTYPE, GUILDBATTLE_SCRIPTID,-1,-1);                 --先强制关闭
	end
	
	if sceneType == 0 then		--据点处理
		
		local sceneScriptID = x888888_GetLairdSceneType(mapId)
	    if sceneScriptID ~= -1 then
	    	CallScriptFunction( sceneScriptID,"OnPlayerEnter",mapId, playerId)
	    end
		
	end

	if sceneType == 1 then --地图类型是副本
		
		local fubenscript = GetFubenData_Param(mapId,1) ; --取得脚本号
		CallScriptFunction( FUBEN_COMMON_SCRIPT, "OnPlayerEnter", mapId, playerId ) ;
        SetPlayerMutexState( mapId,playerId ,PLAYER_STATE_READYFUBEN ,0)

	else

		if GetZhiye( mapId, playerId) ~=9 then
			SetPlayerDefaultReliveInfo( mapId, playerId, "%100", -1, "0", x888888_g_defaultRelive_SceneID_1, 430, 428 );
		else
			SetPlayerDefaultReliveInfo( mapId, playerId, "%100", -1, "0", x888888_g_defaultRelive_SceneID_2, 430, 428 );
		end
	end

    if sceneType == 2 then
		local sceneScriptID = x888888_GetBattleSceneType( mapId)
	    if sceneScriptID ~= -1 and sceneScriptID == GUILD_CONTEND_SCRIPT then
	    	CallScriptFunction( sceneScriptID, "ProcMapPlayerEnter", mapId, playerId)
	    end
    end

    --从MD中取出节日积分并更新到角色属性
    SetFeastScore( mapId, playerId, GetQuestData( mapId, playerId, MD_SEED_SCORE[ 1], MD_SEED_SCORE[ 2], MD_SEED_SCORE[ 3] ) )

	if mapId == 41 then
		UpdateToplist(mapId, playerId, WORLDCUP_TOPLIST_A, 0, 20)
		
		local nWeekIndex = GetWeekIndex() --since 2010-01-25
		local nTitleIndex = mod(nWeekIndex,16)
		if nTitleIndex == 0 then
			nTitleIndex = 16
		end
		nTitleIndex = nTitleIndex -1	--上周的
		if nTitleIndex == 0 then
			nTitleIndex = 16
		end
		
		UpdateToplist(mapId, playerId, x888888_g_TopList[nTitleIndex], 0, 20)
	end
	--进入的是监狱，加状态互斥
--	if mapId == PK_PUNISH_PRISON_SCENE_ID then
--		SetPlayerMutexState( mapId, playerId,PLAYER_STATE_READYFUBEN,1 )
--	end
    
    -- 如果是禁骑地图设置禁止上马标记
   -- for i, item in FORBID_RIDE_SCENE_LIST do
        --if mapId == item then
           -- SetPlayerMutexState( mapId, playerId, PLAYER_STATE_FORBID_RIDE, 1)
            --break
        --end
   -- end
end

---------------------------------------------------------------------------------------------------
--玩家进入新场景结束事件
---------------------------------------------------------------------------------------------------
function x888888_ProcMapPlayerEnterFinished( mapId, playerId )

	--MD数据清除作业
	x888888_QuestDataClearTask(mapId,playerId)

	--进入场景OK,据点相关信息处理
	x888888_ShowGuildLairdInfo(mapId,playerId)
	
	--进入场景OK,显示场景PK信息
	x888888_ShowMapPKInfo(mapId,playerId)

   	CallScriptFunction( 302500, "PlayEffect", mapId, playerId)
	ClearPlayerNextSceneInfo(mapId, playerId)
	
	--删除6v6战场中所有物品和BUF
	if x888888_GetBattleSceneType( mapId ) == PVP6V6_BATTLE_SCRIPT then
		
		--如果玩家不属于本战场,则清数据
		if CallScriptFunction(PVP6V6_BATTLE_SCRIPT,"CheckPlayerValid",mapId,playerId ) ~= 1 then
			
			--清除数物品
			for i,itm in x888888_g_PVP6V6ItemList do
		
				local nItemCount = GetItemCountInBag(mapId,playerId,itm)
				if nItemCount > 0 then
					DelItemByIDInBag(mapId, playerId, itm, nItemCount)
				end
			end
			
			--清除BUF
			for i,itm in x888888_g_PVP6V6BufList do
		
				if IsHaveSpecificImpact(mapId,playerId,itm ) == 1 then
					CancelSpecificImpact(mapId,playerId,itm)
				end
			end
		end
		
	else
	
		--如果进的不是战场,则清数据
		
		--清除数物品
		for i,itm in x888888_g_PVP6V6ItemList do
	
			local nItemCount = GetItemCountInBag(mapId,playerId,itm)
			if nItemCount > 0 then
				DelItemByIDInBag(mapId, playerId, itm, nItemCount)
			end
		end
		
		--清除BUF
		for i,itm in x888888_g_PVP6V6BufList do
	
			if IsHaveSpecificImpact(mapId,playerId,itm ) == 1 then
				CancelSpecificImpact(mapId,playerId,itm)
			end
		end
	end


	--迷宫双倍经验玩法
	--CallScriptFunction( MIGONGSHUANGBEI_SCRIPT, "EnterScene", mapId, playerId ) ;
	
	--妖邪地宫
	if mapId == YX_LOULAN_SCENE_ID1 or 
	   mapId == YX_LOULAN_SCENE_ID2 or 
	   mapId == YX_LOULAN_SCENE_ID3 or
	   mapId == YX_LOULAN_SCENE_ID4 or
	   mapId == YX_LOULAN_SCENE_ID5 or
	   mapId == YX_LOULAN_SCENE_ID6 or
	   mapId == YX_LOULAN_SCENE_ID7 or
	   mapId == YX_LOULAN_SCENE_ID8 or
	   mapId == YX_LOULAN_SCENE_ID9 or

	   mapId == YX_LAIYIN_SCENE_ID1 or
	   mapId == YX_LAIYIN_SCENE_ID2 or
	   mapId == YX_LAIYIN_SCENE_ID3 or
	   mapId == YX_LAIYIN_SCENE_ID4 or
	   mapId == YX_LAIYIN_SCENE_ID5 or
	   mapId == YX_LAIYIN_SCENE_ID6 or	
	   mapId == YX_LAIYIN_SCENE_ID7 or	
	   mapId == YX_LAIYIN_SCENE_ID8 or
	   mapId == YX_LAIYIN_SCENE_ID9 or
	      
	      
	   mapId == YX_KUNLUN_SCENE_ID1 or
	   mapId == YX_KUNLUN_SCENE_ID2 or
	   mapId == YX_KUNLUN_SCENE_ID3 or
	   mapId == YX_KUNLUN_SCENE_ID4 or
	   mapId == YX_KUNLUN_SCENE_ID5 or
	   mapId == YX_KUNLUN_SCENE_ID6 or	   
	   mapId == YX_KUNLUN_SCENE_ID7 or		   
	   mapId == YX_KUNLUN_SCENE_ID8 or
	   mapId == YX_KUNLUN_SCENE_ID9 or	   
	   
	   mapId == YX_DUNHUANG_SCENE_ID1 or
	   mapId == YX_DUNHUANG_SCENE_ID2 or
	   mapId == YX_DUNHUANG_SCENE_ID3 or 
	   mapId == YX_DUNHUANG_SCENE_ID4 or
	   mapId == YX_DUNHUANG_SCENE_ID5 or
	   mapId == YX_DUNHUANG_SCENE_ID6 or
	   mapId == YX_DUNHUANG_SCENE_ID7 or
	   mapId == YX_DUNHUANG_SCENE_ID8 or
	   mapId == YX_DUNHUANG_SCENE_ID9 then
		CallScriptFunction( YAOXIEDIGONG_SCRIPT, "EnterScene", mapId, playerId ) ;
	end

	if mapId == QT_LOULAN_SCENE_ID or
	   mapId == QT_LAIYIN_SCENE_ID or
	   mapId == QT_KUNLUN_SCENE_ID or
	   mapId == QT_DUNHUANG_SCENE_ID then
		CallScriptFunction( QIANGTANDENGLU_SCRIPT, "EnterScene", mapId, playerId ) ;
	end
	
    --舞厅
    if mapId == 14 then
    	CallScriptFunction( 300160, "EnterScene", mapId, playerId)
    	CallScriptFunction( 256224, "Finishwuting", mapId, playerId)	
    end
    
    --屠城战相关处理
    x888888_OnCountryBattleLitePlayerEnter( mapId,playerId)

    local sceneType = GetSceneType(mapId)
	if sceneType == 2 or sceneType == 7 then --地图类型是战场(包括跨服)
		
		local sceneScriptID = x888888_GetBattleSceneType(mapId)
	    if sceneScriptID ~= -1 then
	    	CallScriptFunction( sceneScriptID,"OnPlayerEnter",mapId, playerId)
	    end
    elseif sceneType == 1 then --地图类型是副本

		local fubenscript = GetFubenData_Param(mapId, 1)
		CallScriptFunction(FUBEN_COMMON_SCRIPT, "OnPlayerEnterFinished", mapId, playerId)
	else
		
		local sceneScriptID = x888888_GetLairdSceneType(mapId)
	    if sceneScriptID ~= -1 then
	    	CallScriptFunction( sceneScriptID,"OnPlayerLeave",mapId, playerId)
	    end
	end
	
	--切换地图时检查国王，王后状态
	x888888_CheckKingAndQueen(mapId, playerId)	
	
	
	--屠城战相关处理
	if x888888_IsCountryBattleLiteMap(mapId ) == 1 then
	
		--地图检查通过，可以参加屠城战
		CallScriptFunction( COUNTRY_BATTLE_LITE_SCRIPT,"CountryBattleLite_RefreshQuest", mapId,playerId )
	end

    x888888_ClearSpell( mapId, playerId)
end

function x888888_ClearSpell( mapId, playerId)
    local profession = GetZhiye( mapId, playerId) + 1
    for i, item in x888888_g_DispelSkillList[ profession] do
        DispelSpecificImpact( mapId, playerId, item, 1)
    end
end

---------------------------------------------------------------------------------------------------
--根据玩家信息,返回复活场景信息
---------------------------------------------------------------------------------------------------
function x888888_GetReturnCity( mapId, playerId )
	local nCountry = GetCurCountry(mapId,playerId)
	
	local newSceneId = -1
	local posX = 64
	local posZ = 64
	
	if nCountry == 0 then
		newSceneId = 91
	elseif nCountry == 1 then
		newSceneId = 191
	elseif nCountry == 2 then
		newSceneId = 291
	elseif nCountry == 3 then
		newSceneId = 391
	else
		posX = -1
		posZ = -1
	end
	
	return newSceneId, posX, posZ
end

---------------------------------------------------------------------------------------------------
--执行玩家复活
---------------------------------------------------------------------------------------------------
function x888888_DoPlayerRelive( mapId, playerId, value, usehorse )
	ClearRageRecoverTick(mapId, playerId)
	RestoreHp(mapId, playerId,value)
	RestoreRage(mapId, playerId,value)
	ClearMutexState(mapId, playerId, 6)
	SendReliveResult(mapId, playerId,1)	
	if usehorse==1 then
		LastMount(mapId, playerId )
		RestoreHp(mapId, playerId,0)
	end
end

---------------------------------------------------------------------------------------------------
--使用原地复活，扣除玩家现金或金卡
---------------------------------------------------------------------------------------------------
function x888888_PayReliveMoney( mapId, playerId, value )
	local nGoldMode = GetGoldMode( mapId, playerId )
	
	if nGoldMode == 1 then		--优先现金结算
		if CostMoney(mapId, playerId, 2, value,300) == -1 then
			return 0
		end
	
	elseif nGoldMode == 0 then	--优先金卡结算
		if CostMoney(mapId, playerId, 3, value,300) == -1 then
			if CostMoney(mapId, playerId, 2, value,300) == -1 then
				return 0
			end
		end
	
	else						--未知的结算模式
		return 0
	end

	return 1
end

---------------------------------------------------------------------------------------------------
--玩家复活的脚本事件
--ReliveType:复活方式  	1.原地安全复活（虚弱状态）  2.原地安全复活（无虚弱状态）  3.健康复活（回城）
---------------------------------------------------------------------------------------------------
function x888888_ProcMapPlayerRelive( mapId, playerId, ReliveType )

	local sceneType = GetSceneType(mapId)
	if sceneType == 0 then
		
		local sceneScriptID = x888888_GetLairdSceneType(mapId)
	    if sceneScriptID ~= -1 then
	    	CallScriptFunction( sceneScriptID,"OnPlayerRelive",mapId, playerId)
	    end
		
	elseif sceneType == 1 then 
	elseif sceneType == 2 or sceneType == 7 then

		local sceneScriptID = x888888_GetBattleSceneType(mapId)
	    if sceneScriptID ~= -1 then
	    	CallScriptFunction( sceneScriptID, "OnPlayerRelive", mapId, playerId,ReliveType)
	    	return
	    end
	end
	
	

	--//add in 2009-4-8 for guojiashoubian
	if IsHaveQuestNM( mapId, playerId, 7563 ) > 0 then --如果有国家守边任务
		CallScriptFunction( 300734, "OnPlayerRelive", mapId, playerId  )
	end
	--//add end
	if IsHaveQuestNM( mapId, playerId, 7569 ) > 0 then --如果有国家守边任务
		CallScriptFunction( 300860, "OnPlayerRelive", mapId, playerId  )
	end
	
	if IsHaveQuestNM( mapId, playerId, 7575 ) > 0 then --如果有国家守边任务
		CallScriptFunction( 300859, "OnPlayerRelive", mapId, playerId  )
	end
	
	if IsHaveQuestNM( mapId, playerId, 7584 ) > 0 then --如果有国家守边任务
		CallScriptFunction( 300858, "OnPlayerRelive", mapId, playerId  )
	end
	
	local money = 0
	local level = GetLevel(mapId, playerId)
	if level <= 9 then
		money = 0
	else
		money = 800
	end
	
	x888888_UpdateHideNameState( mapId, playerId, ReliveType )
	
	if ReliveType == x888888_g_ReliveType.OriginLosslessRelive then
		--原地无损复活
		--1.不需要金钱
		if money == 0 then
			x888888_DoPlayerRelive(mapId,playerId,100,1)
			ClearPlayerNextSceneInfo(mapId,playerId)
			return
		end
		
		--2.使用非绑定返生券
		if HaveItem(mapId,playerId,11990050)>0 then
			if DelItem(mapId,playerId,11990050,1) == 1 then
				x888888_DoPlayerRelive(mapId,playerId,100,1)
				ClearPlayerNextSceneInfo(mapId,playerId)
				return
			end
		end
		
		--3.使用绑定返生券
		if HaveItem(mapId,playerId,11990051)>0 then
			if DelItem(mapId,playerId,11990051,1) == 1 then
				x888888_DoPlayerRelive(mapId,playerId,100,1)
				ClearPlayerNextSceneInfo(mapId,playerId)
				return
			end
		end
		
		--4.使用金钱
		if x888888_PayReliveMoney( mapId, playerId, money ) == 1 then
			x888888_DoPlayerRelive(mapId,playerId,100,1)
			ClearPlayerNextSceneInfo(mapId,playerId)
			return
		else
			BeginQuestEvent(mapId)
			AddQuestText(mapId, "很抱歉，您没有携带回魂丹，您的现金或金卡也不足支付复活费用。")
			EndQuestEvent(mapId)
			DispatchQuestTips(mapId,playerId)
			SendReliveResult(mapId, playerId,0)
			return		
		end

	elseif ReliveType == x888888_g_ReliveType.CityPosRelive then
		--回城复活
		x888888_DoPlayerRelive(mapId,playerId,100,0)
		
		--newSceneId是玩家重生的地图ID，需策划指定
		local newSceneId,posX,posZ = x888888_GetReturnCity(mapId,playerId)
		posX = posX+random(1,7)-4
		posZ = posZ+random(1,7)-4
		
		if posX <= 0 then
			posX = 1
		end
		if posZ <= 0 then
			posZ = 1
		end
		
		SetPlayerNextSceneInfo(mapId, playerId, newSceneId, posX, posZ)

		if newSceneId ~= -1 then
			if mapId ~= newSceneId then
				NewWorld(mapId, playerId,newSceneId,posX,posZ, 8888881)
			else
				SetPos(mapId,playerId,posX,posZ)
			end
		end	
		
	elseif ReliveType == x888888_g_ReliveType.SceneRelive then
		--地图复活
		ClearPlayerNextSceneInfo(mapId,playerId)
		if GetSceneType(mapId)==1 then
			x888888_DoPlayerRelive(mapId,playerId,50,0)
		else
			x888888_DoPlayerRelive(mapId,playerId,100,0)
		end
		
		local newSceneId = -1
		local posX = -1
		local posZ = -1
		newSceneId,posX,posZ = GetDeathDeal(mapId, playerId)
		
		-- 地图号-1，表示回本国王城
		if newSceneId == -1 then
			newSceneId,posX,posZ = x888888_GetReturnCity(mapId,playerId)
		end

		if newSceneId ~= -1 then
			if mapId ~= newSceneId then
				NewWorld( mapId, playerId, newSceneId, posX + random( 0, 5), posZ + random( 0, 5), 8888882)
			else
				SetPos(mapId,playerId,posX,posZ)
			end
		end	
		
	end
end


---------------------------------------------------------------------------------------------------
--广播异国玩家PK消息
---------------------------------------------------------------------------------------------------
function x888888_BroadcastFightInfo( mapId, diedId, killerId )

	local diedCamp = GetCurCamp(mapId, diedId)
	local killerCamp = GetCurCamp(mapId, killerId)
	local killerType = GetObjType(mapId, killerId)
	local sceneCamp = GetSceneInfo(mapId, "CAMP")
	local szFightPos = ""
	local szFightType = ""
	sceneCamp = sceneCamp - 16	--必须要-16
	
	if killerType ~= 1 then -- killer不是玩家 died肯定是玩家 不需要判断
		return
	end
	
	if diedCamp == killerCamp then --同国 不处理
		return
	end
	
	if sceneCamp >= 4 then --中立地图
		return
	end
	
	if (tonumber(sceneCamp)*100 + 50) == mapId then
		szFightPos = "王城"
	elseif (tonumber(sceneCamp)*100 + 51) == mapId then
		szFightPos = "边境"
	elseif (tonumber(sceneCamp)*100 + 86) == mapId then
		szFightPos = "古道"
	elseif (tonumber(sceneCamp)*100 + 87) == mapId then
		szFightPos = "牧场"
	elseif (tonumber(sceneCamp)*100 + 89) == mapId then
		szFightPos = "草场"
	elseif (tonumber(sceneCamp)*100 + 58) == mapId then
		szFightPos = "外城"
	else
		return
	end
	if killerCamp == sceneCamp then
		szFightType = "守卫成功"
	end
	
	if diedCamp == sceneCamp then
		szFightType = "守卫失败"
	end
	
	
	local fightTime = GetSceneInfo(mapId, "FIGHTTIME")
	local curTime = GetCurrentTime()	--单位秒

	if fightTime == 0 then
		SetSceneInfo(mapId, "FIGHTTIME", curTime)
	elseif curTime - fightTime > 10 then
		SetSceneInfo(mapId, "FIGHTTIME", curTime)
	else
		return
	end
	
	local diedName = GetName(mapId, diedId)
	local killerName = GetName(mapId, killerId)
	if IsHideName(mapId, killerId) > 0 then
		killerName = HIDE_NAME
	end
	
	local sceneName = GetSceneInfo(mapId, "NAME")
	local diedPosX, diedPosZ = GetWorldPos(mapId, diedId)
	diedPosX = format("%d", diedPosX)
	diedPosZ = format("%d", diedPosZ)
	local colorYellow = "#cFFFF00"
	local colorGreen = "#c00FF00"
	local colorRed = "#cFF0000"
	if "守卫成功" == szFightType then
		LuaAllScenceM2Country (mapId,  colorYellow .. "英雄!" .. colorGreen .. killerName .. colorYellow .. "在" .. szFightPos .. "成功抵御了入侵者的进攻", sceneCamp, CHAT_RIGHTDOWN, 0)
	else
		local szFightInfo = colorRed .. "警报！本国" .. colorGreen .. szFightPos .. "#aB{onfight_".. mapId .. "," .. diedPosX..","..diedPosZ.."}"..diedPosX..","..diedPosZ.."#aE".. colorRed .. "坐标发现敌方入侵者"
		BroadcastFightInfo(mapId, sceneCamp, diedPosX, diedPosZ, szFightInfo)
	end

end

---------------------------------------------------------------------------------------------------
--组队荣誉共享
---------------------------------------------------------------------------------------------------
function x888888_TeamShareHonor( mapId, diedId, killerId, honor )
	
	local nMemberNum = 1
	local bHasTeam = HasTeam(mapId, killerId)
	
	if bHasTeam > 0 then
    nMemberNum = GetNearTeamCount(mapId, killerId)
  end
  
  if nMemberNum >= 2 then
	  for i=0, nMemberNum-1 do
			local memberId = GetNearTeamMember(mapId, killerId, i)
			if IsPlayerStateNormal(mapId, memberId) > 0 and GetHp(mapId, memberId) > 0 and memberId ~= killerId then
				LuaScenceM2Player(mapId, memberId, "#cFF0000本次荣誉变化来源于队伍的荣誉共享", GetName(mapId, memberId), CHAT_RIGHTDOWN, 1 )
				local updateResult = x888888_UpdateHonorRecord( mapId, diedId, memberId )
				LuaScenceM2Player(mapId, memberId, updateResult, GetName(mapId, memberId), CHAT_RIGHTDOWN, 1 )
				
				local addResult = x888888_IsCanAddHonor( mapId, diedId, memberId );
				if addResult ~= nil then
					LuaScenceM2Player(mapId, memberId, addResult, GetName(mapId, memberId), CHAT_RIGHTDOWN, 1 )
				else
					
					--专精天赋处理,剔除副本和战场
					if GetSceneType(mapId) == 0  then
						CallScriptFunction(404909,"ComputeZhuanJingTianfuCnt", mapId, diedId, memberId ) 
					end
					
					local canAddHonor = x888888_CanAddHonorNum( mapId, diedId, memberId )
					if honor > canAddHonor then
						honor = canAddHonor
					end
					if honor > 0 then
						SetHonorInfo(mapId, memberId, "HONORNUM", GetHonorInfo(mapId, memberId, "HONORNUM") + honor)
						AddHonor(mapId, memberId, honor)
						local szMsg = "获得荣誉" .. honor .. "点"
						LuaScenceM2Player(mapId, memberId, szMsg, GetName(mapId, memberId), CHAT_RIGHTDOWN, 1 )					
						
					end
					if 1 == x888888_IsHonorOverflow(mapId, memberId) then
						LuaScenceM2Player(mapId, memberId, "已经达到每天可以获得的最大荣誉上限", GetName(mapId, memberId), CHAT_RIGHTDOWN, 1 )
					end
				end
			end
		end
	end

end

---------------------------------------------------------------------------------------------------
--取得能添加荣誉的值
---------------------------------------------------------------------------------------------------
function x888888_CanAddHonorNum( mapId, diedId, killerId )
	local killerLevel = GetLevel(mapId, killerId)
	local honorNum = GetHonorInfo(mapId, killerId, "HONORNUM")
	return floor(killerLevel * 40 - honorNum)
end

---------------------------------------------------------------------------------------------------
--荣誉计算
---------------------------------------------------------------------------------------------------
function x888888_HonorNumCalculate( mapId, diedId, killerId )
	local killerLevel = GetLevel(mapId, killerId)
	local diedLevel = GetLevel(mapId, diedId)

	--（被杀者等级的平方/（杀人者等级+被杀者等级））/2
	local honor = (diedLevel * diedLevel / (killerLevel + diedLevel)) / 2
	local killerCountry = GetCurCountry(mapId, killerId)
	--0楼兰王国 1天山王国 2昆仑王国 3敦煌王国
	if (mapId == killerCountry*100 + 50) or (mapId == killerCountry*100 + 51) then
		honor = 3 * honor
	end
	--四舍五入
	local tempHonor = floor(honor);
	if honor >= tempHonor + 0.5 then
		honor = tempHonor + 1
	else
		honor = tempHonor
	end
	return honor
end

---------------------------------------------------------------------------------------------------
--荣誉是否已满
---------------------------------------------------------------------------------------------------
function x888888_IsHonorOverflow(mapId,playerId)
	local selfLevel = GetLevel(mapId, playerId)
	local honorNum = GetHonorInfo(mapId, playerId, "HONORNUM")
	if honorNum >= selfLevel * 20 then
		return 1
	end
	return -1
end

---------------------------------------------------------------------------------------------------
--计算荣誉
---------------------------------------------------------------------------------------------------
function x888888_CalculateHonor( mapId, diedId, killerId )
	
	if mapId == PK_PUNISH_PRISON_SCENE_ID then --如果是监狱地图，不计算荣誉值
		return
	end

	local killerType = GetObjType(mapId, killerId)
	
	--宠物杀的，记主人身上
	if killerType == 3 then
		
		killerType = 1
		killerId = GetOwnerID(mapId, killerId)
		killerType = GetObjType(mapId, killerId)
	end	

	if killerType ~= 1 then
		return	--不是玩家
	end
	
	if IsHideName(mapId, diedId) > 0 or IsHideName(mapId, killerId) > 0 then
		return
	end
	
	--//判断是不是自己杀了自己
	if diedId==killerId then  
		return
	end
	
	local killerLevel = GetLevel(mapId, killerId)
	local diedLevel = GetLevel(mapId, diedId)
	local killerName = GetName(mapId, killerId)
	local nMemberNum = 1
	local bHasTeam = HasTeam(mapId, killerId)
	local nShareMemberNum = 0
	
	if bHasTeam > 0 then
    	nMemberNum = GetNearTeamCount(mapId, killerId)
  	end
  
  	if nMemberNum >= 2 then
	  for i=0, nMemberNum-1 do
				local memberId = GetNearTeamMember(mapId, killerId, i)
				if IsPlayerStateNormal(mapId, memberId) > 0 and GetHp(mapId, memberId) > 0 and memberId ~= killerId then
					nShareMemberNum = nShareMemberNum + 1
				end
		end
	end
	
	local updateResult = x888888_UpdateHonorRecord( mapId, diedId, killerId )
	LuaScenceM2Player(mapId, killerId, updateResult, killerName, CHAT_RIGHTDOWN, 1 )
		
	local getHonor = x888888_HonorNumCalculate( mapId, diedId, killerId )
	local addHonorNum = getHonor / (nShareMemberNum + 1) --算上自己 所以加一
	local tempHonor = floor(addHonorNum);
	if addHonorNum >= tempHonor + 0.5 then
		addHonorNum = tempHonor + 1
	else
		addHonorNum = tempHonor
	end
	
	if addHonorNum > 0 then
	
		x888888_TeamShareHonor( mapId, diedId, killerId, addHonorNum )--不包括自己
		
		local addResult = x888888_IsCanAddHonor( mapId, diedId, killerId );
		if addResult == nil then
			
			--专精天赋处理,剔除副本和战场
			if GetSceneType(mapId) == 0  then
				----------下面的逻辑放在沙袋的道具脚本里面处理
				----------local nQuest = GetQuestData(sceneId, selfId, MD_TISHENSHADAI_DAYCOUNT[1], MD_TISHENSHADAI_DAYCOUNT[2], MD_TISHENSHADAI_DAYCOUNT[3]) 
				----------if GetQuestData(sceneId, selfId, MD_TISHENSHADAI_DAYCOUNT[1], MD_TISHENSHADAI_DAYCOUNT[2], MD_TISHENSHADAI_DAYCOUNT[3]) <= 10 then
				----------	AddInherenceZhuanGongExp(mapId,killerId)
				----------end
				CallScriptFunction(404909,"ComputeZhuanJingTianfuCnt", mapId, diedId, killerId ) 
			end
			
			--当能获得荣誉的时候，普通处理
			local canAddHonor = x888888_CanAddHonorNum( mapId, diedId, killerId )
			if addHonorNum > canAddHonor then
				addHonorNum = canAddHonor
			end
			
			--执行添加荣誉
			if addHonorNum > 0 then
				SetHonorInfo(mapId, killerId, "HONORNUM", GetHonorInfo(mapId, killerId, "HONORNUM") + addHonorNum)
				AddHonor(mapId, killerId, addHonorNum)
				local szMsg = "获得荣誉" .. addHonorNum .. "点"
				LuaScenceM2Player(mapId, killerId, szMsg, killerName, CHAT_RIGHTDOWN, 1 )
				
				-- 屠城战额外处理
				if mapId == 50 or mapId == 150 or mapId == 250 or mapId == 350 or
				   mapId == 51 or mapId == 151 or mapId == 251 or mapId == 351 or
				   mapId == 58 or mapId == 158 or mapId ~= 258 or mapId ~= 358 or
				   mapId == 86 or mapId == 186 or mapId == 286 or mapId == 386 then
					CallScriptFunction(COUNTRY_BATTLE_LITE_SCRIPT,"OnCountryBattleLitePlayerKilled", mapId,diedId,killerId,addHonorNum*2 )   
				end
			end
			
			--检查一下是否需要给出荣誉已达上限的提示
			if 1 == x888888_IsHonorOverflow(mapId, killerId) then
				LuaScenceM2Player(mapId, killerId, "已经达到每天可以获得的最大荣誉上限", killerName, CHAT_RIGHTDOWN, 1 )
			end
		else
			
			--当不能再获得荣誉的时候，屠城战需要特殊处理
			if addHonorNum > 0 then
								
				-- 屠城战额外处理
				if mapId == 50 or mapId == 150 or mapId == 250 or mapId == 350 or
				   mapId == 51 or mapId == 151 or mapId == 251 or mapId == 351 or
				   mapId == 58 or mapId == 158 or mapId ~= 258 or mapId ~= 358 or
				   mapId == 86 or mapId == 186 or mapId == 286 or mapId == 386 then
					CallScriptFunction(COUNTRY_BATTLE_LITE_SCRIPT,"OnCountryBattleLitePlayerKilled", mapId,diedId,killerId,addHonorNum*2 )   
				end
			end
			
			LuaScenceM2Player(mapId, killerId, addResult, killerName, CHAT_RIGHTDOWN, 1 )
		end
	end
	
end

---------------------------------------------------------------------------------------------------
--杀人数量改变事件
---------------------------------------------------------------------------------------------------
function x888888_OnKillCount( mapId,diedId,playerId)
	
	
	--检查玩家状态是否正常
	if (IsPlayerStateNormal( mapId,diedId ) ~= 1) or
	   (IsPlayerStateNormal( mapId,playerId ) ~= 1) then
	    return
	end
	
	local diedCountry   = GetCurCountry( mapId,diedId)
	local killerCountry = GetCurCountry( mapId,playerId)
	local diedlevel		= GetLevel( mapId,diedId)
	local killerlevel	= GetLevel( mapId,playerId)
	local killcount
	
	if killerlevel > diedlevel + 20 then
		return
	end
	
	if x888888_GetKillCount(mapId,diedId,playerId) > 10 then
		return
	end

	if(diedCountry == killerCountry) then
		return
	end

    -- 如果在监狱杀人不处理杀人计数
    if mapId == 12 then
        return
    end

	--异国杀人数排行榜更新通知
	local day = GetQuestData( mapId, playerId, MD_KILLCOUNT_DAY[1], MD_KILLCOUNT_DAY[2], MD_KILLCOUNT_DAY[3] )
	local curday = GetWeekFirstDay()
	if day ~= curday then
		killcount = 0
	else
		killcount = GetKillCount(mapId,playerId)+1
	end

	SetKillCount( mapId, playerId, killcount )
	SetQuestData( mapId, playerId, MD_KILLCOUNT_DAY[1], MD_KILLCOUNT_DAY[2], MD_KILLCOUNT_DAY[3], curday )

	--调用我的脚本的函数
	--传入dieID,可以获取职业
	--如果符合这种职业，则计数加1
	if killerCountry == 0 then  
		CallScriptFunction(300980,"UpdateKillCountProfession",mapId,playerId,diedId) --楼兰脚本
	elseif killerCountry == 1 then
		CallScriptFunction(300981,"UpdateKillCountProfession",mapId,playerId,diedId) --天山脚本
	elseif killerCountry == 2 then
		CallScriptFunction(300982,"UpdateKillCountProfession",mapId,playerId,diedId) --昆仑脚本 
	elseif killerCountry == 3 then
		CallScriptFunction(300983,"UpdateKillCountProfession",mapId,playerId,diedId) --敦煌脚本
	end
	
end

---------------------------------------------------------------------------------------------------
--提示今天获得荣誉信息
---------------------------------------------------------------------------------------------------
function x888888_UpdateHonorRecord( mapId, diedId, playerId )

	local diedName = GetName(mapId, diedId)
	diedName = "#cFF0000" .. diedName
	local diedGuid = GetGUID(mapId, diedId)
	
	local totalNum = 10
	local timeLimit = 3600*2 --秒
	local curTime = GetCurrentTime();
	
	local IsDiedInRecord = -1;
	local diedIndex = -1;
	local diedFirstBeKillTime = -1;
	local diedTimes = 1;
	--超过2小时的清零
	for index=0, tonumber(totalNum - 1) do
		local guid,killTime, times = GetHonorRecord(mapId, playerId, index)
		if guid ~= -1 then
			if curTime - killTime > timeLimit then
				SetHonorRecord(mapId, playerId, index, "TIMES", -1)
				SetHonorRecord(mapId, playerId, index, "KILL_TIME", -1)
				SetHonorRecord(mapId, playerId, index, "GUID", -1)
			end
		end
	end
	
	--每天的荣誉限制 如果天数变了 更新之
	local today = GetDayOfYear()
	local honorDay = GetHonorInfo(mapId, playerId, "HONORDAY") 
	if today ~= honorDay then
		SetHonorInfo(mapId, playerId, "HONORDAY", today)
		SetHonorInfo(mapId, playerId, "HONORNUM", 0)
	end
	
	--记录中找此死者
	for index=0, tonumber(totalNum - 1) do
		local guid, killTime, times = GetHonorRecord(mapId, playerId, index)
		if tonumber(guid) == tonumber(diedGuid) then
			IsDiedInRecord = 1;
			diedIndex = index;
			diedFirstBeKillTime = killTime
			diedTimes = times
		end
	end
	--不在记录中
	if( IsDiedInRecord == -1 ) then
		local bFull = IsHonorRecordFull(mapId, playerId)
		if( bFull == 1 ) then
			--第一个记录被后面的记录顶上来
			for index=1, tonumber(totalNum - 1) do
					local guid,killTime, times = GetHonorRecord(mapId, playerId, index)
					SetHonorRecord(mapId, playerId, index - 1, "TIMES", times)
					SetHonorRecord(mapId, playerId, index - 1, "KILL_TIME", killTime)
					SetHonorRecord(mapId, playerId, index - 1, "GUID", guid)
			end
			--最后一个记录被置空
			SetHonorRecord(mapId, playerId, totalNum - 1, "TIMES", 0)
			SetHonorRecord(mapId, playerId, totalNum - 1, "KILL_TIME", 0)
			SetHonorRecord(mapId, playerId, totalNum - 1, "GUID", -1)
			return "最多记录10个被杀的玩家, 杀人记录已满, 第一个玩家被顶掉, " .. diedName .. "被加到记录中。"
		end
		AddHonorRecord(mapId, playerId, diedId)
		return "杀死玩家："..diedName.."  1次"
	--在记录中
	else
		diedTimes = diedTimes + 1
		SetHonorRecord(mapId, playerId, diedIndex, "TIMES", diedTimes)
		return "杀死玩家："..diedName.."  "..diedTimes.. "次"
	end
	return "荣誉记录无法更新"
end

---------------------------------------------------------------------------------------------------
--获得2小时内杀某个GUID的次数
---------------------------------------------------------------------------------------------------
function x888888_GetKillCount(mapId, diedId, playerId)

	local index
	local totalNum = 10
	local diedGuid = GetGUID(mapId, diedId)
	local diedTimes = 0
	
	for index=0, tonumber(totalNum - 1) do
		local guid, killTime, times = GetHonorRecord(mapId, playerId, index)
		if tonumber(guid) == tonumber(diedGuid) then
			diedTimes = times
		end
	end
	
	return diedTimes
end

---------------------------------------------------------------------------------------------------
--调用此函数之前一定要先调用 x888888_UpdateHonorRecord
---------------------------------------------------------------------------------------------------
function x888888_IsCanAddHonor( mapId, diedId, playerId )

	local totalNum = 10
	local timeLimit = 3600*2 --秒
	local timesLimit = 10 --次
	local curTime = GetCurrentTime();
	
	local diedCountry = GetCurCountry(mapId, diedId)
	local selfCountry = GetCurCountry(mapId, playerId)
	local diedLevel = GetLevel(mapId, diedId)
	local selfLevel = GetLevel(mapId, playerId)
	local diedGuid = GetGUID(mapId, diedId)
	local diedName = GetName(mapId, diedId)
	diedName = "#cFF0000" .. diedName
	
	local IsDiedInRecord = -1;
	local diedIndex = -1;
	local diedFirstBeKillTime = -1;
	local diedTimes = 1;
	
	if(diedCountry == selfCountry) then
		return "杀死本国玩家，无荣誉获得"
	end
	
	if(diedLevel < 30) then
		return "被杀者等级小于30，无荣誉获得"
	end
	
	if(selfLevel - diedLevel > 20) then
		return "你的等级大于被杀者20级以上，无荣誉获得"
	end
	
	--记录中找此死者
	for index=0, tonumber(totalNum - 1) do
		local guid, killTime, times = GetHonorRecord(mapId, playerId, index)
		if tonumber(guid) == tonumber(diedGuid) then
			IsDiedInRecord = 1
			diedIndex = index
			diedFirstBeKillTime = killTime
			diedTimes = times
		end
	end
	
	if 1 == IsDiedInRecord and (curTime - diedFirstBeKillTime < timeLimit and diedTimes > timesLimit) then
		return "在" .. timeLimit/3600 .. "小时之内，杀死" .. diedName .. "次数超过" .. timesLimit .. "次，不再给荣誉"
	end
	
	local honorNum = GetHonorInfo(mapId, playerId, "HONORNUM")
	
	local honorMax = 0
	if IsHaveSpecificImpact( mapId, playerId, 9016) > 0 then
		honorMax = selfLevel * 40
	else
		honorMax = selfLevel * 20
	end
	
	if honorNum >= honorMax then
		return "你今天已经击败了足够的敌国玩家，不能再通过击败敌国玩家来获得荣誉。"
	end
		
	return nil
end

---------------------------------------------------------------------------------------------------
--玩家死亡后脚本事件
--1.根据玩家等级降低装备耐久度
--2.根据玩家PK值，掉落未绑定物品
--3.一些特定的任务在玩家死亡后删除
---------------------------------------------------------------------------------------------------
function x888888_ProcMapPlayerDie( mapId, playerId, killerId )

	if killerId== -1 then
		if GetSceneType(mapId) == 1 then
			return
		end
	end
	
	--如果killer不在本地图了，忽略
	if IsObjValid(mapId,killerId)~=1 then
		return
	end	


	--战场相关处理
    if GetSceneType(mapId) == 2 or GetSceneType(mapId) == 7 then
	    x888888_ClearPlayerData(mapId, playerId)
	    local sceneScriptID = x888888_GetBattleSceneType(mapId)
	    if sceneScriptID ~= -1 then
	    	CallScriptFunction( sceneScriptID,"OnPlayerDie",mapId, playerId, killerId)
	    	return
	    end
	end

	
	--副本相关处理
	local sceneType = GetSceneType(mapId)
	if sceneType == 1 then 

		--对比武擂台需要特别处理一下,比武擂台不需要惩罚
		local fubentype   = GetFubenData_Param(mapId,0) ; --取得副本号
		local fubenscript = GetFubenData_Param(mapId,1) ; --取得脚本号

		if fubentype==FUBEN_BIWULEITAI then 
		   	CallScriptFunction( FUBEN_COMMON_SCRIPT, "OnPlayerDie", mapId, playerId, killerId )
		   	return
		end
	end
	
	
	--据点处理
	if sceneType == 0 then
		
		local sceneScriptID = x888888_GetLairdSceneType(mapId)
	    if sceneScriptID ~= -1 then
	    	CallScriptFunction( sceneScriptID,"OnPlayerDie",mapId, playerId)
	    end
		
	end
	
	--计算荣誉
	x888888_CalculateHonor( mapId, playerId, killerId )
	
	--清除死亡、断线后无效的任务数据
	x888888_ClearPlayerData(mapId, playerId)
	
	--如果处于黑金答题状态,单独清除
	ClearMutexState(mapId, playerId, PLAYER_STATE_BLACKGOLD);
	
	--死亡计次
	x888888_OnKillCount( mapId, playerId, killerId )

	if playerId == killerId then	--自杀，只掉装备耐久
		local nEndureMin,nEndureMax,nBagMin,nBagMax,nEquipMin,nEquipMax = OndieMonster(mapId, playerId);
		local wordpart = 0;
		local balive = 0;
		for i=0,14 do
			--改变玩家装备耐久度
			local endureDelta = random(nEndureMin, nEndureMax)
			endureDelta = endureDelta + GetItemDurOnDieRefix( mapId, playerId )
			if( endureDelta < 0 ) then
				endureDelta = 0
			end

			local oldVal = GetBodyItemDur(mapId, playerId, i)
			local newVal = oldVal * ( (100 - endureDelta) / 100.0 )
			local bChange = SetBodyItemDur(mapId, playerId, i, newVal, wordpart)
			if bChange>0 then
				wordpart = bChange
				if oldVal>0 then
					newVal = GetBodyItemDur(mapId, playerId, i)
					if newVal == 0 then
						balive = 1
					end
				end
			end
		end
		if wordpart > 0 then
			UpdateBodyItem(mapId, playerId, wordpart, balive)
		end
		return	--直接返回了
	end

	--获取杀人者的类型（玩家或者怪物）
	local ObjType = GetObjType(mapId, killerId)
	-- 被怪杀的死亡惩罚
	if ObjType == 2 then
		-- 1, 装备耐久变化
   		local nEndureMin,nEndureMax,nBagMin,nBagMax,nEquipMin,nEquipMax = OndieMonster(mapId, playerId);
		local wordpart = 0;
		local balive = 0;
		for i=0,14 do
			--改变玩家装备耐久度
			local endureDelta = random(nEndureMin, nEndureMax)
			endureDelta = endureDelta + GetItemDurOnDieRefix( mapId, playerId )
			if( endureDelta < 0 ) then
				endureDelta = 0
			end
			local oldVal = GetBodyItemDur(mapId, playerId, i)
			local newVal = oldVal * ( (100 - endureDelta) / 100.0 )
			local bChange = SetBodyItemDur(mapId, playerId, i, newVal, wordpart)
			if bChange>0 then
				wordpart = bChange
				if oldVal>0 then
					newVal = GetBodyItemDur(mapId, playerId, i)
					if newVal == 0 then
						balive = 1
					end
				end
			end
		end
		if wordpart > 0 then
			UpdateBodyItem(mapId, playerId, wordpart, balive)
		end

		-- 2, 背包掉落
		--得到玩家背包和身上未绑定物品数
		local ItemCntInBag = GetNotBindItemCountInBag(mapId, playerId)
		local DropCountInBag = 0
		DropCountInBag 	= random (nBagMin , nBagMax) / 100 * ItemCntInBag

		--掉落背包
		if IsKing(mapId, playerId) ~= 1 then
			DropNotBindItemInBag(mapId, playerId,DropCountInBag)
		end

		-- 3, 玩家随身掉落
		local ItemCntInBody = GetNotBindItemCountInBody(mapId, playerId)
		local DropCountInBody = random (nEquipMin , nEquipMax) / 100 * ItemCntInBody

		--掉落随身装备
		if IsKing(mapId, playerId) ~= 1 then
			DropNotBindItemInBody(mapId, playerId,DropCountInBody)
		end
	end

	-- 被PET杀死 ^_^!
	if ObjType == 3 then
		ObjType = 1
		killerId = GetOwnerID(mapId, killerId)
		if IsObjValid(mapId,killerId)~=1 then
			return
		end
	end

	-- 被人杀的死亡惩罚
	if ObjType == 1 then 

		local killerName = GetName(mapId, killerId)
		if IsHideName(mapId, killerId) > 0 then
			killerName = HIDE_NAME
		end
		local selfName = GetName(mapId, playerId)
		local szMsg = "你被" .. killerName .. "杀死了"
		LuaScenceM2Player(mapId, playerId, szMsg, selfName, CHAT_RIGHTDOWN, 1 )
	
		local punishType = GetScenePunishType(mapId, playerId)
		-- 1,无惩罚地图
		if punishType == 0 then
			local nEndureMin,nEndureMax = OndieNopunish(mapId, playerId)

			--得到玩家装备当前耐久度
			local wordpart = 0;
		  	local balive = 0;
		  	
			for i=0,14 do
			--改变玩家装备耐久度
				local endureDelta = random(nEndureMin, nEndureMax)
				endureDelta = endureDelta + GetItemDurOnDieRefix( mapId, playerId )
				if( endureDelta < 0 ) then
					endureDelta = 0
				end
				local oldVal = GetBodyItemDur(mapId, playerId, i)
				local newVal = oldVal * ( (100 - endureDelta) / 100.0 )
				local bChange = SetBodyItemDur(mapId, playerId, i, newVal, wordpart)
				if bChange>0 then
					wordpart = bChange
					if oldVal>0 then
						newVal = GetBodyItemDur(mapId, playerId, i)
						if newVal == 0 then
							balive = 1
						end
					end
				end
			end
			if wordpart > 0 then
				UpdateBodyItem(mapId, playerId, wordpart, balive)
			end
    		end

		-- 2,有惩罚地图

 		if punishType == 1 then

 			--广播异国玩家杀死本国玩家的消息
			x888888_BroadcastFightInfo( mapId, playerId, killerId )
			
			local selfLevel = GetLevel(mapId, playerId)
			local killerLevel = GetLevel(mapId, killerId)
			local deltaLevel = abs(selfLevel - killerLevel)
			local CountryIDSelf 	= GetCurCountry(mapId, playerId)
			local CountryIDKiller	= GetCurCountry(mapId, killerId)

			if IsHideName(mapId, playerId) <= 0 and IsHideName(mapId, killerId) <= 0 then
				AddEnemy(mapId,playerId,killerId)
				DeleteEnemy(mapId, killerId, playerId)
			end

			-- 081217(齐亮)不管是不是同国玩家之间PK，只要被杀者是红名就按30%概率掉落非绑定物品
			if GetPKMode(mapId, playerId)==2 and IsKing(mapId, playerId) ~= 1 then
				-- get random number from 1 to 100
				local isDrop = random( 100)
				if isDrop >= 1 and isDrop <= 30 then
					DropNotBindItemInBag(mapId, playerId, 1)
				end
			end

			--同国玩家
			if CountryIDSelf == CountryIDKiller then

				--******************************************************************************
				--*死者惩罚                                                                    *
				--******************************************************************************
				--a.玩家等级差（杀手等级-死者等级）对照表格，取得分数基数n（等级基数）
				--b.死者PK值对照表格，取得分数基数m（PK值基数）
				--c.惩罚算法为(n/100+m/20)=z（惩罚基数）
				--d.根据z的值对照表格，获得具体死者惩罚内容
		 		--a
				local levelP 	= GetPKLevel(mapId, playerId, deltaLevel)
				--b
				local pkValue 	= GetPKValue(mapId, playerId)
				local PKP	 	= GetPKPoint(mapId, playerId, pkValue)
				--c
				local punishP	= levelP/100 + PKP/20
				local TotalValue= GetPKPunish(mapId, playerId, punishP)

				--d
				--监狱：当TotalValue>100时，将玩家送入指定地图的指定坐标。

				local nEndureMin,nEndureMax,nBagMin,nBagMax,nEquipMin,nEquipMax,nSelfPK = OndieSameCountry(mapId, playerId, punishP)
				local wordpart = 0;
				local balive = 0;
				for i=0,14 do
					--改变玩家装备耐久度
					local endureDelta = random(nEndureMin, nEndureMax)
					endureDelta = endureDelta + GetItemDurOnDieRefix( mapId, playerId )
					if( endureDelta < 0 ) then
						endureDelta = 0
					end
					local oldVal = GetBodyItemDur(mapId, playerId, i)
					local newVal = oldVal * ( (100 - endureDelta) / 100.0 )
					local bChange = SetBodyItemDur(mapId, playerId, i, newVal, wordpart)
					if bChange>0 then
						wordpart = bChange
						if oldVal>0 then
							newVal = GetBodyItemDur(mapId, playerId, i)
							if newVal == 0 then
								balive = 1
							end
						end
					end
				end
				if wordpart > 0 then
					UpdateBodyItem(mapId, playerId, wordpart, balive)
				end

				--得到玩家背包和身上未绑定物品数
				local ItemCntInBag = GetNotBindItemCountInBag(mapId, playerId)
				local ItemCntInBody = GetNotBindItemCountInBody(mapId, playerId)
				local DropCountInBag = 0
				local DropCountInBody = 0

				if TotalValue > 100 then
					--传送到监狱   ToDo
				else
					DropCountInBag 	= random (nBagMin , nBagMax) / 100 * ItemCntInBag
					DropCountInBody = random (nEquipMin , nEquipMax) / 100 * ItemCntInBody
				end

				--掉落背包
				--081217（齐亮）统一按是否红名掉落物品，所以注释
				--DropNotBindItemInBag(mapId, playerId,DropCountInBag)

				--掉落随身装备（国王不掉落，非狂暴模式不掉落）
				if GetPKMode(mapId, playerId)==2 and IsKing(mapId, playerId) ~= 1 then
					DropNotBindItemInBody(mapId, playerId,DropCountInBody)
				end
					
				local IsPunish = x888888_ComputePKPunish( mapId, playerId, killerId )

				--******************************************************************************
				--*杀人者惩罚                                                                  *
				--******************************************************************************

				local selfLevel = GetLevel(mapId, playerId)
				local killerLevel = GetLevel(mapId, killerId)
				local deltaLevel = abs(killerLevel - selfLevel)
				local PKMode = GetPKMode(mapId, killerId)
				local PK1,PK2 = OndieKiller(mapId, playerId, deltaLevel);

				-- 1,普通
				if PKMode ~= 2 then
					local PKkiller = GetPKValue(mapId, killerId)
					PKkiller = PKkiller + PK1
				end

				-- 2,善恶模式: 新玩法不处理此模式：修改者：王勇鸷
--				if PKMode == 7 then
--					local PKkiller = GetPKValue(mapId, killerId)
--					PKkiller = PKkiller + PK2
--					if IsKing(mapId, killerId) ~= 1 then
--						SetPKValue(mapId, killerId, PKkiller)
--					end
--				end
			
				if IsKing(mapId, killerId) ~= 1 and IsPunish == 1 then
					--非国王并且PK惩罚值大于0
					x888888_KillerEnterPrison(mapId, killerId)
				end
			else			--不同国
				local selfLevel = GetLevel(mapId, playerId)
				local killerLevel = GetLevel(mapId, killerId)
		   	-- 1, 装备耐久变化
				local nEndureMin,nEndureMax,nBagMin,nBagMax,nEquipMin,nEquipMax,nSelfHonor,nKillerHonor = OndieDiffCountry(selfLevel,killerLevel);
				local wordpart = 0;
				local balive = 0;
				for i=0,14 do
					--改变玩家装备耐久度
					local endureDelta = random(nEndureMin, nEndureMax)
					endureDelta = endureDelta + GetItemDurOnDieRefix( mapId, playerId )
					if( endureDelta < 0 ) then
						endureDelta = 0
					end
					local oldVal = GetBodyItemDur(mapId, playerId, i)
					local newVal = oldVal * ( (100 - endureDelta) / 100.0 )
					local bChange = SetBodyItemDur(mapId, playerId, i, newVal, wordpart)
					if bChange>0 then
						wordpart = bChange
						if oldVal>0 then
							newVal = GetBodyItemDur(mapId, playerId, i)
							if newVal == 0 then
								balive = 1
							end
						end
					end
				end
				if wordpart > 0 then
					UpdateBodyItem(mapId, playerId, wordpart, balive)
				end

				-- 2, 背包掉落
				--得到玩家背包和身上未绑定物品数
				local ItemCntInBag = GetNotBindItemCountInBag(mapId, playerId)
				local DropCountInBag = 0
				DropCountInBag 	= random (nBagMin , nBagMax) / 100 * ItemCntInBag

				--掉落背包
				--081217（齐亮）统一按是否红名掉落物品，所以注释
				--DropNotBindItemInBag(mapId, playerId,DropCountInBag)

				-- 3, 玩家随身掉落
				local ItemCntInBody = GetNotBindItemCountInBody(mapId, playerId)
				local DropCountInBody = random (nEquipMin , nEquipMax) / 100 * ItemCntInBody
				--掉落随身装备
				if IsKing(mapId, playerId) ~= 1 then
					DropNotBindItemInBody(mapId, playerId,DropCountInBody)
				end

				-- 4, 荣誉值
				AddHonor(mapId, playerId, nSelfHonor)
				AddHonor(mapId, killerId, nKillerHonor)
			end
		end
				
		--杀死了国家官员
		x888888_OnKillCountryOfficial(mapId,playerId,killerId)

	end
	local sceneType = GetSceneType(mapId)
	if sceneType == 1 then --地图类型是副本
		local fubenscript = GetFubenData_Param(mapId,1) ; --取得脚本号
		CallScriptFunction( FUBEN_COMMON_SCRIPT, "OnPlayerDie", mapId, playerId, killerId )
	end
	
	--设置轮回之地的场景
	if sceneType ~= 1 and mapId ~= PK_PUNISH_PRISON_SCENE_ID and GetLevel(mapId, playerId)>=10 then --地图类型是副本和在监狱中的时候，不允许传回轮回台
		local newSceneId,posX,posZ = x888888_GetReturnCity(mapId,playerId)
		posX = posX+random(1,7)-4
		posZ = posZ+random(1,7)-4
		if posX <= 0 then
			posX = 1
		end
		if posZ <= 0 then
			posZ = 1
		end
		SetPlayerNextSceneInfo(mapId, playerId, newSceneId, posX, posZ)	
	end

end

---------------------------------------------------------------------------------------------------
--玩家死亡后脚本事件
--1.根据玩家等级降低装备耐久度
--2.根据玩家PK值，掉落未绑定物品
--3.一些特定的任务在玩家死亡后删除
---------------------------------------------------------------------------------------------------
function x888888_OnKillCountryOfficial(mapId,playerId,killerId)
--需求：如果玩家杀死了任意一个国家官职（国王，王后，左丞，右相，大将军，左捕，右捕），则给与全世界提示：XXX杀死了XX王国XXX官职。
	
	if IsHideName(mapId,playerId) > 0 then
		return
	end
	
	local countryofficial = CountryGetOfficial(mapId,playerId)
	
	if countryofficial>=2 then
		local szCountry_killer = x888888_GetCountryName(mapId,killerId)
		local szCountry = x888888_GetCountryName(mapId,playerId)
		local killerName = GetName(mapId, killerId)
		if IsHideName(mapId,killerId) > 0 then
			killerName = HIDE_NAME
			szCountry_killer = ""
		end
		local selfName = GetName(mapId, playerId)	
		local szOfficial = x888888_GetCountryOfficialName(countryofficial)
		if IsHideName(mapId,playerId) > 0 then
			selfName = HIDE_NAME
			szCountry = ""
			szOfficial = ""
		end
		local msg = szCountry_killer..killerName.."杀死了"..szCountry..szOfficial..selfName
		--世界广播msg
		LuaAllScenceM2Wrold(mapId,msg,5,0)
		return
	end
	
	for i=0, 1 do
		if IsQinglongZhuque(mapId,playerId, i)>0 then
			local szCountry_killer = x888888_GetCountryName(mapId,killerId)
			local szCountry = x888888_GetCountryName(mapId,playerId)
			local killerName = GetName(mapId, killerId)
			if IsHideName(mapId,killerId) > 0 then
				killerName = HIDE_NAME
				szCountry_killer = ""
			end
			local selfName = GetName(mapId, playerId)	
			local szOfficial = x888888_GetCountrySpecialOfficialName(i)
			if IsHideName(mapId,playerId) > 0 then
				selfName = HIDE_NAME
				szCountry = ""
				szOfficial = ""
			end
			local msg = szCountry_killer..killerName.."杀死了"..szCountry..szOfficial..selfName
			--世界广播msg
			LuaAllScenceM2Wrold(mapId,msg,5,0)
			return
		end
	end
end

---------------------------------------------------------------------------------------------------
--取得官职系统
---------------------------------------------------------------------------------------------------
function x888888_GetCountrySpecialOfficialName( nIndex)
	if nIndex ==0 then
		return "青龙之主"
	elseif nIndex ==1 then
		return "朱雀之主"
	end
	
	return "";
		
end

---------------------------------------------------------------------------------------------------
--取得玩家的国家名称
---------------------------------------------------------------------------------------------------
function x888888_GetCountryName(mapId,playerId)
	local szCountry = ""
	local countryid = GetCurCountry(mapId,playerId)
	if countryid==0 then
		szCountry = "楼兰"
	elseif countryid==1 then
		szCountry = "天山"
	elseif countryid==2 then
		szCountry = "昆仑"
	elseif countryid==3 then
		szCountry = "敦煌"
	end	
	
	return szCountry
end

---------------------------------------------------------------------------------------------------
--根据官职类型取得官职名称
---------------------------------------------------------------------------------------------------
function x888888_GetCountryOfficialName(countryofficial)
	local szOfficial = ""
	if countryofficial==8 then
		szOfficial = "国王"
	elseif countryofficial==7 then
		szOfficial = "王后"
	elseif countryofficial==6 then
		szOfficial = "大将军"
	elseif countryofficial==5 then
		szOfficial = "右相"
	elseif countryofficial==4 then
		szOfficial = "左丞"
	elseif countryofficial==3 then
		szOfficial = "金牌右捕"
	elseif countryofficial==2 then
		szOfficial = "金牌左捕"
	end
	
	return szOfficial
end

---------------------------------------------------------------------------------------------------
--给师傅的奖励
---------------------------------------------------------------------------------------------------
function x888888_GiveMasterAward(mapId, playerId, MasterName, level)
	
	local selfName	= GetName( mapId, playerId )
	local nCachet = 0
	local nExp = 0
	nExp = x888888_g_expTable[level][1]
	nCachet = x888888_g_expTable[level][2]

	SendScriptMail( mapId, MasterName, MAIL_MASTER_AWARD, nExp, nCachet, 0, playerId )
	local szMsg = format("恭喜您!由于您徒弟%s升到了%d级，您获得了%d点经验和%d点威望的奖励。", selfName,level,nExp,nCachet)
	--SendNormalMail( mapId, playerId, MasterName, szMsg )
	SendSystemMail( mapId, MasterName, szMsg )
end

---------------------------------------------------------------------------------------------------
--检查徒弟是否可以出师
---------------------------------------------------------------------------------------------------
function x888888_OnPrenticLevelUp(mapId, playerId, level)
		local targetGUID = GetMasterGUID(mapId, playerId);
		if targetGUID == tonumber(-1) then
			return
		end
		
		local MasterName = GetFriendName( mapId, playerId, targetGUID )
		if MasterName == "" then
			return
		end
		
		local selfName	= GetName( mapId, playerId )
		
		x888888_GiveMasterAward(mapId, playerId, MasterName,level)

		--if level >= 21 and level < 50 then
			--x888888_GiveMasterAward(mapId, playerId, MasterName,level)
		--elseif level == 50 then
			--x888888_GiveMasterAward(mapId, playerId, MasterName,level)
			
			--SendNormalMail(mapId, playerId, MasterName, "恭喜你!你的徒弟" .. selfName .. "达到出师等级,已经出师了。");
			--local MyGUID = GetGUID( mapId, playerId )
			--SendScriptMail( mapId, MasterName, MAIL_BETRAYMASTER, MyGUID, 0, 0, playerId )

			--local szMsg = format("恭喜你!你已经达到出师等级,已经出师了,所以与你的师傅%s脱离了师徒关系。", MasterName)
			--SendNormalMail( mapId, playerId, selfName, szMsg )
			--Msg2Player(mapId, playerId, szMsg, 8, 2)
			
			--BetrayMaster(mapId, playerId);
		--end	
end

---------------------------------------------------------------------------------------------------
--玩家升级事件
---------------------------------------------------------------------------------------------------
function x888888_ProcMapPlayerLevelUp( mapId, objId, level )

		CallScriptFunction( SYSTEM_MAIL_SCRIPT, "leveluptest",mapId, objId, level )
		
		-- 检查徒弟是否可以出师
		x888888_OnPrenticLevelUp( mapId, objId, level );
				--升级至30级任务
		if IsHaveQuestNM(mapId,objId,1577) == 1 then
			if GetLevel(mapId, objId)>= 30 then
	 			local misIndex0 = GetQuestIndexByID(mapId,objId,1577)                                                  
	 			SetQuestByIndex(mapId,objId,misIndex0,0,1)                                                  
	    	SetQuestByIndex(mapId,objId,misIndex0,7,1)
	 		else
	  		local misIndex0 = GetQuestIndexByID(mapId,objId,1577)                                                  
	  		SetQuestByIndex(mapId,objId,misIndex0,0,0)                                               
	    	SetQuestByIndex(mapId,objId,misIndex0,7,0)
	 		end
		end
	  if IsHaveQuestNM(mapId,objId,1578) == 1 then 
	  	if GetLevel(mapId, objId)>= 30 then
	    	local misIndex1 = GetQuestIndexByID(mapId,objId,1578)                                                  
	    	SetQuestByIndex(mapId,objId,misIndex1,0,1)                                                
	    	SetQuestByIndex(mapId,objId,misIndex1,7,1)
	    else		
	  	   local misIndex1 = GetQuestIndexByID(mapId,objId,1578)                                                  
	  	   SetQuestByIndex(mapId,objId,misIndex1,0,0)                                                 
	    	SetQuestByIndex(mapId,objId,misIndex1,7,0)
	    end
	  end 	
	  if IsHaveQuestNM(mapId,objId,1579) == 1 then
	  	if GetLevel(mapId, objId)>= 30 then
	    	local misIndex2 = GetQuestIndexByID(mapId,objId,1579)                                                  
	    	SetQuestByIndex(mapId,objId,misIndex2,0,1)                                               
	    	SetQuestByIndex(mapId,objId,misIndex2,7,1)
	    else
	    	local misIndex2 = GetQuestIndexByID(mapId,objId,1579)                                                  
	    	SetQuestByIndex(mapId,objId,misIndex2,0,0)                                                 
	    	SetQuestByIndex(mapId,objId,misIndex2,7,0)
	    end
	  end
	  if IsHaveQuestNM(mapId,objId,1580) == 1 then  	
	  	if GetLevel(mapId, objId)>= 30 then	
	    	local misIndex3 = GetQuestIndexByID(mapId,objId,1580)                                                  
	    		SetQuestByIndex(mapId,objId,misIndex3,0,1)                                                 
	    		SetQuestByIndex(mapId,objId,misIndex3,7,1)
	    else		
	    		local misIndex3 = GetQuestIndexByID(mapId,objId,1580)                                                  
	    		SetQuestByIndex(mapId,objId,misIndex3,0,0)                                                  
	    		SetQuestByIndex(mapId,objId,misIndex3,7,0)
	 		end
		end
		
		
		if IsHaveQuestNM(mapId,objId,1573) == 1 then
			if GetLevel(mapId, objId)>= 40 then
	 			local misIndex0 = GetQuestIndexByID(mapId,objId,1573)                                                  
	 				SetQuestByIndex(mapId,objId,misIndex0,0,1)                                                 
	    		SetQuestByIndex(mapId,objId,misIndex0,7,1)
	 		else
	  			local misIndex0 = GetQuestIndexByID(mapId,objId,1573)                                                  
	  			SetQuestByIndex(mapId,objId,misIndex0,0,0)                                                  
	    		SetQuestByIndex(mapId,objId,misIndex0,7,0)
	    end
	  end
	  if IsHaveQuestNM(mapId,objId,1574) then
	    if 	GetLevel(mapId, objId)>= 40  == 1 then
	    	local misIndex1 = GetQuestIndexByID(mapId,objId,1574)                                                  
	    		SetQuestByIndex(mapId,objId,misIndex1,0,1)                                                
	    		SetQuestByIndex(mapId,objId,misIndex1,7,1)
	    else		
	    		local misIndex1 = GetQuestIndexByID(mapId,objId,1574)                                                  
	    		SetQuestByIndex(mapId,objId,misIndex1,0,0)                                                  
	    		SetQuestByIndex(mapId,objId,misIndex1,7,0)	
	    end
	   end 		
	  if IsHaveQuestNM(mapId,objId,1575) == 1 then
	  	if 	GetLevel(mapId, objId)>= 40  == 1 then
	    	local misIndex2 = GetQuestIndexByID(mapId,objId,1575)                                                  
	    		SetQuestByIndex(mapId,objId,misIndex2,0,1)                                                  
	    		SetQuestByIndex(mapId,objId,misIndex2,7,1)
			else	local misIndex2 = GetQuestIndexByID(mapId,objId,1575)                                                  
					SetQuestByIndex(mapId,objId,misIndex2,0,0)                                                
	    		SetQuestByIndex(mapId,objId,misIndex2,7,0)
	 		end
	 	end
	 	if IsHaveQuestNM(mapId,objId,1576) == 1 then  		 		
    		if 	GetLevel(mapId, objId)>= 40  == 1 then
	    		local misIndex3 = GetQuestIndexByID(mapId,objId,1576)                                                  
	    		SetQuestByIndex(mapId,objId,misIndex3,0,1)                                                
	    		SetQuestByIndex(mapId,objId,misIndex3,7,1)
	    	else	
	    		local misIndex3 = GetQuestIndexByID(mapId,objId,1576)                                                  
	    		SetQuestByIndex(mapId,objId,misIndex3,0,0)                                                  
	    		SetQuestByIndex(mapId,objId,misIndex3,7,0)
	 		end
		end
		--升级到50级任务
		if IsHaveQuestNM(mapId,objId,1600) == 1 then
			if GetLevel(mapId, objId)>= 50 then
	 			local misIndex0 = GetQuestIndexByID(mapId,objId,1600)                                                  
	 			SetQuestByIndex(mapId,objId,misIndex0,0,1)                                                  
	    	SetQuestByIndex(mapId,objId,misIndex0,7,1)
	 		else
	  		local misIndex0 = GetQuestIndexByID(mapId,objId,1600)                                                  
	  		SetQuestByIndex(mapId,objId,misIndex0,0,0)                                                 
	    	SetQuestByIndex(mapId,objId,misIndex0,7,0)
	 		end
		end
		--升级到60级任务
		if IsHaveQuestNM(mapId,objId,1601) == 1 then
			if GetLevel(mapId, objId)>= 60 then
	 			local misIndex0 = GetQuestIndexByID(mapId,objId,1601)                                                  
	 			SetQuestByIndex(mapId,objId,misIndex0,0,1)                                                
	    	SetQuestByIndex(mapId,objId,misIndex0,7,1)
	 		else
	  		local misIndex0 = GetQuestIndexByID(mapId,objId,1601)                                                  
	  		SetQuestByIndex(mapId,objId,misIndex0,0,0)                                                 
	    	SetQuestByIndex(mapId,objId,misIndex0,7,0)
	 		end
		end
		--升级到70级任务
		if IsHaveQuestNM(mapId,objId,1602) == 1 then
			if GetLevel(mapId, objId)>= 70 then
	 			local misIndex0 = GetQuestIndexByID(mapId,objId,1602)                                                  
	 			SetQuestByIndex(mapId,objId,misIndex0,0,1)                                                 
	    	SetQuestByIndex(mapId,objId,misIndex0,7,1)
	 		else
	  		local misIndex0 = GetQuestIndexByID(mapId,objId,1602)                                                  
	  		SetQuestByIndex(mapId,objId,misIndex0,0,0)                                                 
	    	SetQuestByIndex(mapId,objId,misIndex0,7,0)
	 		end
		end
		--升级到80级任务
		if IsHaveQuestNM(mapId,objId,1603) == 1 then
			if GetLevel(mapId, objId)>= 80 then
	 			local misIndex0 = GetQuestIndexByID(mapId,objId,1603)                                                  
	 			SetQuestByIndex(mapId,objId,misIndex0,0,1)                                                 
	    	SetQuestByIndex(mapId,objId,misIndex0,7,1)
	 		else
	  		local misIndex0 = GetQuestIndexByID(mapId,objId,1603)                                                  
	  		SetQuestByIndex(mapId,objId,misIndex0,0,0)                                                 
	    	SetQuestByIndex(mapId,objId,misIndex0,7,0)
	 		end
		end
		
		-- 王国内务任务检查
        CallScriptFunction( 256216, "LevelUp", mapId, objId)
        -- 帮会引导任务检查
        CallScriptFunction( 256238, "LevelUp", mapId, objId)
end


---------------------------------------------------------------------------------------------------
--副本切场景机制
---------------------------------------------------------------------------------------------------
function x888888_ProcMapNotify( mapId, destmapId )

	--mapId 为副本入口所在地图ID, destsceneId为副本地图ID
	--此函数响应调用表示副本地图已经初始化完成，可以传送玩家了

	local destsceneType = GetSceneType(destmapId) ;
	if destsceneType == 1 then 	--地图类型是副本
		
		CallScriptFunction( FUBEN_COMMON_SCRIPT, "OnFubenReady", mapId, destmapId ) ;
		
	end

end


---------------------------------------------------------------------------------------------------
--任务接受检测
---------------------------------------------------------------------------------------------------
function x888888_ProcAcceptQuestCheck( mapId, playerId, missionScript )
	return 1
end


---------------------------------------------------------------------------------------------------
--任务Npc默认对话框
---------------------------------------------------------------------------------------------------
function x888888_ProcNpcDefaultDialog( mapId, playerId, targetId, targetGUID)
	local npcType = GetMonsterDataID(mapId,targetId)
	BeginQuestEvent(mapId)

		local strText = "&&"..targetGUID.."&&"

		AddQuestText(mapId,strText);

		OnNPCClickedQuestNM(mapId,playerId,targetId, targetGUID)
	EndQuestEvent(mapId)
	DispatchQuestEventList(mapId,playerId,targetId)

	return 1

end


---------------------------------------------------------------------------------------------------
--NPC默认对话框显示列表
---------------------------------------------------------------------------------------------------
function x888888_ProcNpcDefaultQuestEventList( mapId, playerId, targetId, targetGUID)
	BeginQuestEvent(mapId)
	local npcType = GetMonsterDataID(mapId,targetId)


		local strText = "&&"..targetGUID.."&&"

		AddQuestText(mapId,strText);
		OnNPCClickedQuestNM(mapId,playerId,targetId, targetGUID)
		ShowNpcQuestEventList(mapId,playerId,targetId)
	EndQuestEvent(mapId)
	DispatchQuestEventList(mapId,playerId,targetId)
	return 1

end
---------------------------------------------------------------------------------------------------
--切换PK模式
---------------------------------------------------------------------------------------------------
function x888888_ChangePKMode( mapId, playerId, PKMode)
    -- 检查狂暴丸Buff是否存在，消失了才能切换
    local buffId = 7211
    if IsHaveSpecificImpact( mapId, playerId, buffId) > 0 then
		local nContinuance = GetImpactContinuanceByDataIndex(mapId, playerId, buffId)
		local nElapse = GetImpactContinuanceElapsed(mapId, playerId, buffId)
		local nLeft = floor((nContinuance - nElapse)/1000)
		BeginQuestEvent( mapId)
		AddQuestText( mapId, "很抱歉，您正处于狂暴模式，请在".. nLeft .. "秒后重试" )
		EndQuestEvent()
		DispatchQuestTips( mapId, playerId)
        return 0
    end
	
	-- 从狂暴模式切出
	if (PKMode==0 or PKMode==1) 
		and GetPKMode(mapId, playerId)==2 
		and GetPKValue(mapId, playerId)>0 then
		BeginQuestEvent( mapId)
		AddQuestText( mapId, "PK值过高，无法切出狂暴模式" )
		EndQuestEvent()
		DispatchQuestTips( mapId, playerId)
        return 0		
	end

    -- 切换间隔，单位是秒
    local interval = 300
    local lastChange = GetLastChgPKModeTime( mapId, playerId )
--	print("lastChange="..lastChange)
    local curTime = GetCurrentTime()
    if curTime - lastChange > interval or lastChange == 0 then
        -- 更新切换时间
		SetLastChgPKModeTime( mapId, playerId, curTime )
        return 1
    else
		local nLeft = interval - (curTime - lastChange)
		BeginQuestEvent( mapId)
		AddQuestText( mapId, "PK模式切换太频繁，请在"..nLeft.."秒后重试。" )
		EndQuestEvent()
		DispatchQuestTips( mapId, playerId)
        return 0
    end
end

---------------------------------------------------------------------------------------------------
--国王囚禁玩家
---------------------------------------------------------------------------------------------------
function x888888_OnEnjail(mapId, playerId)
	--根据BUFF 7902,7903 判断是否在囚禁中。
	if IsHaveSpecificImpact(mapId,playerId,7902)==1 then
		CountrySendFeedBack(mapId,playerId,0,-1)
		return
	end
	
	--判断玩家是否是死亡状态
	if ( GetHp(mapId,playerId)<=0 ) then
		CountrySendFeedBack(mapId,playerId,0,-2)
		return
	end

    -- 舞厅内不允许被囚禁
    if mapId == 14 then
		CountrySendFeedBack(mapId,playerId,0,-5)
        return
    end

	--判断是否在摆摊
	if 1 == IsInStall(mapId, playerId) then
		CloseStall(mapId, playerId)
	end
	
	--判断是否在马上
	if 1 == IsHaveMount(mapId, playerId, -1) then
		ReCallHorse(mapId, playerId)
	end
	
	--判断是否在车上
	if 1 == IsBusMember(mapId, playerId) then
		local busId = GetBusId(mapId, playerId)
		if busId ~= -1 then	
			-- 0--普通镖车，1--BUS，2--帮会镖车
			local BusHp = GetHp(mapId, busId)
			local BusType = GetBusType(mapId, busId)
			
			if BusType == 1 then		--普通BUS
				--DelBusMember(mapId, playerId,busId)
			elseif BusType == 0 then	--个人镖车
				--if BusHp > 0 then
				--	SetHp(mapId,busId,-BusHp)
				--end
			elseif BusType == 2 then	--帮会镖车
				--DeleteBus(mapId, busId, 1)
				--if BusHp > 0 then
				--	SetHp(mapId,busId,-BusHp)
				--end
			end			
						
		end
	end
	
	--铁人三项中，牵制任务失败，取消任务
	if 1 == IsHaveQuest(mapId, playerId, 7537) then
		AbandonQuest(mapId, playerId, 7537)
	end
	if 1 == IsHaveQuest(mapId, playerId, 7538) then
		AbandonQuest(mapId, playerId, 7538)
	end
	if 1 == IsHaveQuest(mapId, playerId, 7539) then
		AbandonQuest(mapId, playerId, 7539)
	end

	--成功了，开始加囚禁的BUFF
	SendSpecificImpactToUnit(mapId, playerId, playerId, playerId, 7902, 0)
	if 1 == IsBusMember(mapId, playerId) then
		local busId = GetBusId(mapId, playerId)
		if busId ~= -1 then	
			local BusType = GetBusType(mapId, busId)
			if BusType == 0 then	--个人镖车
				SendSpecificImpactToUnit(mapId, playerId, playerId, busId, 7902, 0)
			elseif BusType == 2 then	--帮会镖车
				SendSpecificImpactToUnit(mapId, playerId, playerId, busId, 7902, 0)
			end
		end
	end

	CountrySendFeedBack(mapId,playerId,0,0)
	return
	
end

---------------------------------------------------------------------------------------------------
--赦免
---------------------------------------------------------------------------------------------------
function x888888_OnAssoil(mapId, playerId)

	if IsHaveSpecificImpact(mapId,playerId,7902)==0 then
		return 0
	end
	
	CancelSpecificImpact(mapId, playerId,7902)
	
	if 1 == IsBusMember(mapId, playerId) then
		local busId = GetBusId(mapId, playerId)
		if busId ~= -1 then	
			local BusType = GetBusType(mapId, busId)
			if BusType == 0 then	--个人镖车
				CancelSpecificImpact(mapId, busId,7902)
			elseif BusType == 2 then	--帮会镖车
				CancelSpecificImpact(mapId, busId,7902)
			end
		end
	end	
	
	return 1
	
end

function x888888_CheckEnjailState(mapId, playerId)
	if IsHaveSpecificImpact(mapId,playerId,7902)==1 then
		MarkMutexState( mapId, playerId, 25 )
	end
end

---------------------------------------------------------------------------------------------------
--检查国王状态，是否需要清数据
---------------------------------------------------------------------------------------------------
function x888888_CheckKingAndQueen(mapId,playerId)
	--如果不是国王、王后，但有王者套装或王者坐骑
	local official = CountryGetOfficial(mapId,playerId)
	if official~=8 and official~=7 then
		if HaveItem(mapId, playerId,10300100)>0 then
			x888888_DrawBack_Kingly_bonus(mapId,playerId,official, 1)
		end
		
		for i=3001,3008 do
			if IsHaveHorse(mapId, playerId,i) then
				x888888_DrawBack_Kingly_bonus(mapId,playerId,official, 1)
				break
			end
		end
		
	end
	
	--//删除青龙朱雀坐骑
	local bSpecialOffical = 0
	for i=0, 1 do
		if IsQinglongZhuque(mapId, playerId, i)>0 then
			bSpecialOffical = 1
		end
	end
	
	if bSpecialOffical==0 then
		for i=3011,3018 do
			if IsHaveHorse(mapId, playerId,i) then
				x888888_DrawBack_Kingly_bonus(mapId,playerId,official, 2)
				break
			end
		end
	end
	
end

---------------------------------------------------------------------------------------------------
--收回王者AABB
---------------------------------------------------------------------------------------------------
function x888888_DrawBack_Kingly_bonus(mapId,playerId,official, nMode)

	if nMode ==nil then
		nMode =0 
	end
	
	local sendMail = 0
	
	if nMode~=2 then --//等于2只回收青龙朱雀的
		--收回王者套装
		if HaveItem(mapId, playerId,10300100) > 0 then
			if DelItem(mapId, playerId,10300100,1)==0 then
				DelItemInBody(mapId, playerId, 10300100)
			end
			sendMail = 1
		end
		
		--收回王者坐骑
		for i=3001,3008 do
			if IsHaveHorse(mapId, playerId,i)>0 then
				FreeHorseByType(mapId, playerId,i)
				sendMail = 1		
			end
		end
		
		--发邮件
		if sendMail==1 then
			local mail = "很抱歉，新国王收回了您的王者套装及王者坐骑。"
			SendSystemMail(mapId, GetName(mapId, playerId), mail)	
		end
	end
	

	--// add by wangzhiping for 青龙, 朱雀
	if nMode ~=1 then --//等于1只回收国王皇后的
		--收回青龙朱雀坐骑
		sendMail = 0
		for i=3011,3018 do
			if IsHaveHorse(mapId, playerId,i)>0 then
				FreeHorseByType(mapId, playerId,i)
				sendMail = 1		
			end
		end
		
		--发邮件
		if sendMail==1 then
			local mail = "很抱歉，您的守护坐骑已被收回。"
			SendSystemMail(mapId, GetName(mapId, playerId), mail)	
		end
	end
	
end

---------------------------------------------------------------------------------------------------
--加入帮会或是受邀加入帮会事件
--opType = 0 受邀 
--opType = 1 主动申请加入帮会
---------------------------------------------------------------------------------------------------
function x888888_OnJoinGuild(mapId,playerId,guildId )
	--加入帮会的引导任务3126
  	if IsHaveQuestNM(mapId,playerId,2612) == 1 then  
		local misIndex = GetQuestIndexByID(mapId,playerId,2612) 
		SetQuestByIndex(mapId,playerId,misIndex,0,1) 
		SetQuestByIndex(mapId,playerId,misIndex,7,1)
	elseif   IsHaveQuestNM(mapId,playerId,2613) == 1 then  
		local misIndex = GetQuestIndexByID(mapId,playerId,2613) 
		SetQuestByIndex(mapId,playerId,misIndex,0,1) 
		SetQuestByIndex(mapId,playerId,misIndex,7,1)  
	elseif   IsHaveQuestNM(mapId,playerId,2614) == 1 then  
		local misIndex = GetQuestIndexByID(mapId,playerId,2614) 
		SetQuestByIndex(mapId,playerId,misIndex,0,1) 
		SetQuestByIndex(mapId,playerId,misIndex,7,1)  
	elseif   IsHaveQuestNM(mapId,playerId,2615) == 1 then  
		local misIndex = GetQuestIndexByID(mapId,playerId,2615) 
		SetQuestByIndex(mapId,playerId,misIndex,0,1) 
		SetQuestByIndex(mapId,playerId,misIndex,7,1)                                                
  	end       	  
end


---------------------------------------------------------------------------------------------------
--马的技能变化情况,记住,这里不是所有的情况,仅处理以下三种情况
--opType = 2 	遗忘技能
--opType = 4 	技能学习
--opType = 13	还童学习
---------------------------------------------------------------------------------------------------
function x888888_OnHorseSillChagned(mapId,playerId,petLowGUID,petHighGUID,opType)
end


---------------------------------------------------------------------------------------------------
--离开、被开除出帮会或帮会解散时调用
--type：0:离开	1：被开除	2：帮会解散
---------------------------------------------------------------------------------------------------
function x888888_OnLeaveGuild( mapId,playerId,type )

	--执行战场中相关逻辑
 	if GetSceneType(mapId) == 2 then
 		local sceneScriptID = x888888_GetBattleSceneType(mapId)
	    if sceneScriptID ~= -1 then
	    	CallScriptFunction( sceneScriptID,"OnPlayerLeaveGuild",mapId, playerId)
	    end
 	end
 	
 	--据点处理
 	if GetSceneType(mapId) == 0 then
 		local sceneScriptID = x888888_GetLairdSceneType(mapId)
	    if sceneScriptID ~= -1 then
	    	CallScriptFunction( sceneScriptID,"OnPlayerLeaveGuild",mapId, playerId)
	    end
 	end

 	--清除帮会采集任务
	if IsHaveQuestNM( mapId,playerId, 7006 ) > 0 then
 		CallScriptFunction( 300621, "ProcQuestAbandon", mapId, playerId,7006 ) --楼兰
		Msg2Player(mapId,playerId,"离开帮会，【帮会】收集黑木任务自动结束！",8,2)
		Msg2Player(mapId,playerId,"离开帮会，【帮会】收集黑木任务自动结束！",8,3)
	end
	
	if IsHaveQuestNM( mapId,playerId, 7013 ) > 0 then
 		CallScriptFunction( 300905, "ProcQuestAbandon", mapId, playerId,7013 ) --天山
		Msg2Player(mapId,playerId,"离开帮会，【帮会】收集黑木任务自动结束！",8,2)
		Msg2Player(mapId,playerId,"离开帮会，【帮会】收集黑木任务自动结束！",8,3)
	end
	if IsHaveQuestNM( mapId,playerId, 7698 ) > 0 then
 		CallScriptFunction( 300904, "ProcQuestAbandon", mapId, playerId,7698 ) --昆仑
		Msg2Player(mapId,playerId,"离开帮会，【帮会】收集黑木任务自动结束！",8,2)
		Msg2Player(mapId,playerId,"离开帮会，【帮会】收集黑木任务自动结束！",8,3)
	end
	if IsHaveQuestNM( mapId,playerId, 7701 ) > 0 then
 		CallScriptFunction( 300903, "ProcQuestAbandon", mapId, playerId,7701 ) --墩煌
		Msg2Player(mapId,playerId,"离开帮会，【帮会】收集黑木任务自动结束！",8,2)
		Msg2Player(mapId,playerId,"离开帮会，【帮会】收集黑木任务自动结束！",8,3)
	end
	
	--清除收集红木任务
	if IsHaveQuestNM( mapId,playerId, 7011 ) > 0 then
 		CallScriptFunction( 300827, "ProcQuestAbandon", mapId, playerId,7011 )   --楼兰
		Msg2Player(mapId,playerId,"离开帮会，【帮会】收集红木任务自动结束！",8,2)
		Msg2Player(mapId,playerId,"离开帮会，【帮会】收集红木任务自动结束！",8,3)
	end
	if IsHaveQuestNM( mapId,playerId, 7014 ) > 0 then
 		CallScriptFunction( 300827, "ProcQuestAbandon", mapId, playerId,7014 )  --天山
		Msg2Player(mapId,playerId,"离开帮会，【帮会】收集红木任务自动结束！",8,2)
		Msg2Player(mapId,playerId,"离开帮会，【帮会】收集红木任务自动结束！",8,3)
	end
	if IsHaveQuestNM( mapId,playerId, 7699 ) > 0 then
 		CallScriptFunction( 300827, "ProcQuestAbandon", mapId, playerId,7699 )  --昆仑
		Msg2Player(mapId,playerId,"离开帮会，【帮会】收集红木任务自动结束！",8,2)
		Msg2Player(mapId,playerId,"离开帮会，【帮会】收集红木任务自动结束！",8,3)
	end
	if IsHaveQuestNM( mapId,playerId, 7702 ) > 0 then
 		CallScriptFunction( 300827, "ProcQuestAbandon", mapId, playerId,7702)  --墩煌
		Msg2Player(mapId,playerId,"离开帮会，【帮会】收集红木任务自动结束！",8,2)
		Msg2Player(mapId,playerId,"离开帮会，【帮会】收集红木任务自动结束！",8,3)
	end
	
	--清除收集丹木任务
	if IsHaveQuestNM( mapId,playerId, 7012 ) > 0 then
 		CallScriptFunction( 300827, "ProcQuestAbandon", mapId, playerId,7012 )  --楼兰
		Msg2Player(mapId,playerId,"离开帮会，【帮会】收集丹木任务自动结束！",8,2)
		Msg2Player(mapId,playerId,"离开帮会，【帮会】收集丹木任务自动结束！",8,3)
	end
	if IsHaveQuestNM( mapId,playerId, 7015 ) > 0 then
 		CallScriptFunction( 300827, "ProcQuestAbandon", mapId, playerId,7015 )  --天山
		Msg2Player(mapId,playerId,"离开帮会，【帮会】收集丹木任务自动结束！",8,2)
		Msg2Player(mapId,playerId,"离开帮会，【帮会】收集丹木任务自动结束！",8,3)
	end
	if IsHaveQuestNM( mapId,playerId, 7700 ) > 0 then
 		CallScriptFunction( 300827, "ProcQuestAbandon", mapId, playerId,7700 )  --昆仑
		Msg2Player(mapId,playerId,"离开帮会，【帮会】收集丹木任务自动结束！",8,2)
		Msg2Player(mapId,playerId,"离开帮会，【帮会】收集丹木任务自动结束！",8,3)
	end
	if IsHaveQuestNM( mapId,playerId, 7703 ) > 0 then
 		CallScriptFunction( 300827, "ProcQuestAbandon", mapId, playerId,7703 )  --墩煌
		Msg2Player(mapId,playerId,"离开帮会，【帮会】收集丹木任务自动结束！",8,2)
		Msg2Player(mapId,playerId,"离开帮会，【帮会】收集丹木任务自动结束！",8,3)
	end

	
	--清除帮会暗战任务
	if IsHaveQuestNM( mapId,playerId, 7020 ) > 0 then
 		CallScriptFunction( 300640, "ProcQuestAbandon", mapId, playerId,7020 )
		Msg2Player(mapId,playerId,"离开帮会，【帮会】帮会暗战任务自动结束！",8,2)
		Msg2Player(mapId,playerId,"离开帮会，【帮会】帮会暗战任务自动结束！",8,3)
	end
	if IsHaveQuestNM( mapId,playerId, 7742 ) > 0 then
 		CallScriptFunction( 300640, "ProcQuestAbandon", mapId, playerId,7742 )
		Msg2Player(mapId,playerId,"离开帮会，【帮会】帮会暗战任务自动结束！",8,2)
		Msg2Player(mapId,playerId,"离开帮会，【帮会】帮会暗战任务自动结束！",8,3)
	end
	if IsHaveQuestNM( mapId,playerId, 7741 ) > 0 then
 		CallScriptFunction( 300640, "ProcQuestAbandon", mapId, playerId,7741 )
		Msg2Player(mapId,playerId,"离开帮会，【帮会】帮会暗战任务自动结束！",8,2)
		Msg2Player(mapId,playerId,"离开帮会，【帮会】帮会暗战任务自动结束！",8,3)
	end
	if IsHaveQuestNM( mapId,playerId, 7740 ) > 0 then
 		CallScriptFunction( 300640, "ProcQuestAbandon", mapId, playerId,7740 )
		Msg2Player(mapId,playerId,"离开帮会，【帮会】帮会暗战任务自动结束！",8,2)
		Msg2Player(mapId,playerId,"离开帮会，【帮会】帮会暗战任务自动结束！",8,3)
	end
	
	--清除帮会内政任务
    local scriptList = { 300925, 300926, 300927, 300928 }
    for i, item in x888888_g_GuildBuildMissions do
        if IsHaveQuestNM( mapId, playerId, item) > 0 then
            CallScriptFunction( scriptList[ GetCurCountry( mapId, playerId) + 1], "ProcQuestAbandon", mapId, playerId, item)
            Msg2Player( mapId, playerId, "离开帮会，帮会内政任务自动结束", 8, 3)
            Msg2Player( mapId, playerId, "离开帮会，帮会内政任务自动结束！", 8, 2)
            break
        end
    end

 	--清除帮会杀怪任务
	for i,item in x888888_g_GuildKillMonsterMission do
		if IsHaveQuestNM( mapId,playerId, item ) > 0 then
 			CallScriptFunction( GUILD_KILLMONSTER_SCRIPT, "ProcQuestAbandon", mapId, playerId,item )
 		end
	end
	
	--清除帮会除妖任务
	for i,item in x888888_g_GuildChuYaoMission do
		if IsHaveQuestNM( mapId,playerId, item ) > 0 then
 			CallScriptFunction( 300619, "ProcQuestAbandon", mapId, playerId,item )
 		end
	end

	--清除跑帮贡任务
	if IsHaveQuestNM( mapId,playerId, 7020 ) > 0 then
 		CallScriptFunction( GUILD_PAOBANGGONG_SCRIPT, "OnLeaveGuild", mapId, playerId,7020 )
	end
	
	--清除帮会跑商任务
	if IsHaveQuestNM( mapId,playerId, 7026 ) > 0 then
	 	CallScriptFunction( 300671, "ProcQuestAbandon", mapId, playerId,7026 )
		Msg2Player(mapId,playerId,"离开帮会，【帮会】帮会跑商任务自动结束！",8,2)
		Msg2Player(mapId,playerId,"离开帮会，【帮会】帮会跑商任务自动结束！",8,3)
	end
	if IsHaveQuestNM( mapId,playerId, 7027 ) > 0 then
	 	CallScriptFunction( 300677, "ProcQuestAbandon", mapId, playerId,7027 )
		Msg2Player(mapId,playerId,"离开帮会，【帮会】帮会跑商任务自动结束！",8,2)
		Msg2Player(mapId,playerId,"离开帮会，【帮会】帮会跑商任务自动结束！",8,3)
	end
	if IsHaveQuestNM( mapId,playerId, 7028 ) > 0 then
	 	CallScriptFunction( 300678, "ProcQuestAbandon", mapId, playerId,7028 )
		Msg2Player(mapId,playerId,"离开帮会，【帮会】帮会跑商任务自动结束！",8,2)
		Msg2Player(mapId,playerId,"离开帮会，【帮会】帮会跑商任务自动结束！",8,3)
	end
	if IsHaveQuestNM( mapId,playerId, 7029 ) > 0 then
	 	CallScriptFunction( 300679, "ProcQuestAbandon", mapId, playerId,7029 )
		Msg2Player(mapId,playerId,"离开帮会，【帮会】帮会跑商任务自动结束！",8,2)
		Msg2Player(mapId,playerId,"离开帮会，【帮会】帮会跑商任务自动结束！",8,3)
	end

	--清除帮会跑环任务
	if IsHaveQuestNM( mapId,playerId, 9410 ) > 0 then
		CallScriptFunction( 300783, "OnLeaveGuild", mapId, playerId, 9410 )
	end
	--清除皇帝密令任务
	if IsHaveQuestNM( mapId,playerId, 7790 ) > 0 then
		CallScriptFunction( 300971, "ProcQuestAbandon", mapId, playerId, 7790 )
		Msg2Player(mapId,playerId,"离开帮会，【国家】皇帝密令任务自动结束！",8,2)
		Msg2Player(mapId,playerId,"离开帮会，【国家】皇帝密令任务自动结束！",8,3)
	end	
	--清除帮会速成任务
	if IsHaveQuestNM( mapId,playerId, 7784 ) > 0 then
	 	CallScriptFunction( 300683, "ProcQuestAbandon", mapId, playerId,7784 )
		Msg2Player(mapId,playerId,"离开帮会，【帮会】帮会速成任务自动结束！",8,2)
		Msg2Player(mapId,playerId,"离开帮会，【帮会】帮会速成任务自动结束！",8,3)
	end
	if IsHaveQuestNM( mapId,playerId, 7785 ) > 0 then
	 	CallScriptFunction( 300683, "ProcQuestAbandon", mapId, playerId,7785 )
		Msg2Player(mapId,playerId,"离开帮会，【帮会】帮会速成任务自动结束！",8,2)
		Msg2Player(mapId,playerId,"离开帮会，【帮会】帮会速成任务自动结束！",8,3)
	end
	if IsHaveQuestNM( mapId,playerId, 7786 ) > 0 then
	 	CallScriptFunction( 300683, "ProcQuestAbandon", mapId, playerId,7786 )
		Msg2Player(mapId,playerId,"离开帮会，【帮会】帮会速成任务自动结束！",8,2)
		Msg2Player(mapId,playerId,"离开帮会，【帮会】帮会速成任务自动结束！",8,3)
	end
	if IsHaveQuestNM( mapId,playerId, 7787 ) > 0 then
	 	CallScriptFunction( 300683, "ProcQuestAbandon", mapId, playerId,7787 )
		Msg2Player(mapId,playerId,"离开帮会，【帮会】帮会速成任务自动结束！",8,2)
		Msg2Player(mapId,playerId,"离开帮会，【帮会】帮会速成任务自动结束！",8,3)
	end
	--帮贡清零
	local nGP = GetGuildUserPoint(mapId, playerId)
	SubGuildUserPoint(mapId, playerId, nGP)
	
	--帮会功德值清零
	local nMerit = GetGuildMerit(mapId, playerId)
	SubGuildMerit(mapId, playerId, nMerit)
	
	--功勋值清零
	-- local nExploit = GetExploit(mapId, playerId)
	-- SubExploit(mapId, playerId, nExploit)

end

---------------------------------------------------------------------------------------------------
--清除死亡、断线后无效的任务数据
---------------------------------------------------------------------------------------------------
function x888888_ClearPlayerData(mapId, playerId)
	
	--异国夺旗相关
	--楼兰夺旗
	for i,item in x888888_g_YiGuoDouQiMission do
		if IsHaveQuestNM( mapId, playerId,item ) ==1 then
			CallScriptFunction( 300778, "OnLogInOrDie", mapId, playerId  )
			break
		end
	end
	
	--天山夺旗
	for i,item in x888888_g_YiGuoDouQiMission1 do
		if IsHaveQuestNM( mapId, playerId,item ) ==1 then
			CallScriptFunction( 300890, "OnLogInOrDie", mapId, playerId  )
			break
		end
	end

	--昆仑夺旗
	for i,item in x888888_g_YiGuoDouQiMission2 do
		if IsHaveQuestNM( mapId, playerId,item ) ==1 then
			CallScriptFunction( 300886, "OnLogInOrDie", mapId, playerId  )
			break
		end
	end

	--敦煌夺旗
	for i,item in x888888_g_YiGuoDouQiMission3 do
		if IsHaveQuestNM( mapId, playerId,item ) ==1 then
			CallScriptFunction( 300882, "OnLogInOrDie", mapId, playerId  )
			break
		end
	end
	
	--铁人三项断线处理
	for i,item in x888888_g_TieSanMission do
		if IsHaveQuestNM( mapId, playerId,item ) ==1 then
			CallScriptFunction( 300703, "TieSanOnDie", mapId, playerId )
			break
		end
	end
	
	--把删除旗的buff
	CancelSpecificImpact(mapId, playerId, 7702);
	
	--清掉互斥状态
	ClearMutexState(mapId, playerId, 20);
	
	--童趣相关处理
	--CallScriptFunction( 300320, "TongquOnDie", mapId, playerId )
	local impactTbl = {7517,7516}
	for i,item in impactTbl do
		if IsHaveSpecificImpact(mapId, playerId, 7517) > 0 then
			SendSpecificImpactToUnit(mapId, playerId, playerId, playerId, 7534, 0)--添加互斥
			MarkMutexState(mapId, playerId, 21)
			break
		end
	end
end

---------------------------------------------------------------------------------------------------
--玩家连接登陆服务器后第一次进入地图
---------------------------------------------------------------------------------------------------
function x888888_ProcMapPlayerNewConnectEnter(mapId, playerId)

	--显示上次离线信息
	local lastLogoutTime = GetLastLogoutTime(mapId, playerId)
	local szLogoutTime = GetDetailTime(lastLogoutTime)
	local szLastLoginIP = GetLastLoginIP(mapId, playerId)
	if lastLogoutTime ~= 0 and szLastLoginIP ~= "0.0.0.0" then
		Msg2Player(mapId, playerId, "您上一次的离线时间为："..szLogoutTime.."，上次登陆的IP地址为："..szLastLoginIP, 4)
	end

	--检查师徒关系是否要解除
	--x888888_CheckMasterPrentic( mapId, playerId );
	
	--超过多少小时未增加好友度，则上线之后扣除一定的好友度
	--DepleteFriendPoint( mapId, playerId );
	
	--清除死亡、断线后无效的任务数据
	x888888_ClearPlayerData(mapId, playerId)

    --发送帮战请求，这个只在普通地图进行
    if GetSceneType(mapId) == 0 then
    	AskGuildBattleEnter(mapId,playerId)
    end

	--清除答题状态Buffer
	CancelSpecificImpact(mapId, playerId, 9825);
	
	--检查国王状态，是否需要清除数据
	x888888_CheckKingAndQueen(mapId, playerId)
    
    --国王争夺战
    if x888888_GetBattleSceneType(mapId) == KINGBATTLE_FLOW_SCRIPT then
    	CallScriptFunction( KINGBATTLE_FLOW_SCRIPT,"OnPlayerNewConnectEnter",mapId, playerId)
    end
    
    --朱雀争夺战
    if x888888_GetBattleSceneType(mapId) == ZHUQUE_BATTLE_SCRIPT then
    	CallScriptFunction( ZHUQUE_BATTLE_SCRIPT,"OnPlayerNewConnectEnter",mapId, playerId)
    end
    
    --青龙争夺战
    if x888888_GetBattleSceneType(mapId) == QINGLONG_BATTLE_SCRIPT then
    	CallScriptFunction( QINGLONG_BATTLE_SCRIPT,"OnPlayerNewConnectEnter",mapId, playerId)
    end
    
    --据点争夺战
    if x888888_GetLairdSceneType(mapId) == LAIRD_BATTLE_SCRIPT then
    	CallScriptFunction( LAIRD_BATTLE_SCRIPT,"OnPlayerNewConnectEnter",mapId, playerId)
    end
    
    --帮会争霸赛
    if x888888_GetBattleSceneType(mapId) == GUILD_CONTEND_SCRIPT then
    	CallScriptFunction( GUILD_CONTEND_SCRIPT, "OnPlayerNewConnectEnter", mapId, playerId)
    end

	--舞厅的重连处理
    if mapId == 14 then
        CallScriptFunction( 300160, "ProcMapPlayerNewConnectEnter", mapId, playerId)
    end
    
    --游乐场的重连处理
    if mapId == 39 then
        CallScriptFunction( 310320, "ProcMapPlayerNewConnectEnter", mapId, playerId)
    end
    --游乐场2的重连处理
    if mapId == 40 then
        CallScriptFunction( 310365, "ProcMapPlayerNewConnectEnter", mapId, playerId)
    end    
    --舞厅离线预约处理
    CallScriptFunction( 300179, "ProcMapPlayerNewConnectEnter", mapId, playerId)
    
   	--检查囚禁状态
   	x888888_CheckEnjailState(mapId, playerId)

	if GetAccountGold( mapId, playerId ) > 0 then
		
		local text = format("你的账号目前还有#{_MONEY%d}现金未领取",GetAccountGold( mapId, playerId ))
		Msg2Player(mapId, playerId, text, 4)

		--同步客户端帐户现金余额
		SendAccountGold( mapId, playerId )

	end

	--//add in 2009-4-8 for guojiashoubian
	if IsHaveQuestNM( mapId, playerId, 7563 ) > 0 then --如果有国家守边任务
		CallScriptFunction( 300734, "OnPlayerLogin", mapId, playerId  )
	end
	--//add end

	--重算疲劳时间
	local currTime = GetCurrentTime()
	local timeVal = floor( ( currTime - lastLogoutTime ) / 60 )
	if lastLogoutTime ~= 0 and timeVal > 0 then
		DecreaseTiredTime( mapId, playerId,timeVal)
	end
	
	--服务器自动分配国家奖励
	if GetDBFlag(mapId, playerId,0) == 1 then
		Msg2Player(mapId, playerId, "恭喜您！因为您的角色由系统自动分配国家，您获得了奖励！", 4)
		--AddMoney(mapId, playerId, 1, 10000)
		BeginAddItem(mapId)
		AddItem( mapId,12030386,1)
		EndAddItem(mapId,playerId)
		AddItemListToPlayer(mapId,playerId)
		SetDBFlag(mapId, playerId,0,0)
	end

    --骑乘解锁状态检查
    --x888888_CheckPetUnlockState( mapId, playerId)

    --从MD中取出节日积分并更新到角色属性
    SetFeastScore( mapId, playerId, GetQuestData( mapId, playerId, MD_SEED_SCORE[ 1], MD_SEED_SCORE[ 2], MD_SEED_SCORE[ 3] ) )
	
	--更新排行榜数据
	x888888_UpdateTopListKeyValue(mapId, playerId)
    x888888_OnSwitchDayCheck(mapId,playerId)
	
	--离线代练新用户上线处理
	CallScriptFunction(310401, "ProcMapPlayerNewConnectEnter", mapId, playerId)
	
	--如果是跨服报名场景则执行其新用户上线函数
    if GetSceneType(mapId) == 8 then
		CallScriptFunction(MPVP2V2_SIGNUP_SCRIPT, "ProcMapPlayerNewConnectEnter", mapId, playerId)
	end
	
	-- 图腾养成上线处理
	x888888_ProcPlayerSyncLairdInfo(mapId, playerId)

	-- 追踪符 
	for i = 0, 107 do
		local itemid = GetItemIDByIndexInBag(mapId, playerId, i)
		if itemid == 12030043 then
			if GetItemParam( mapId, playerId, i, 8, 2) == 1 then
				if IsItemLocked(mapId, playerId, i) then
					UnlockItem(mapId, playerId, i)
				end
				SetItemParam( mapId, playerId, i, 8, 2, 0)
			end
		end
	end
end

---------------------------------------------------------------------------------------------------
-- 骑乘解锁状态检查
---------------------------------------------------------------------------------------------------
function x888888_CheckPetUnlockState( mapId, playerId)
	-- 携带骑乘总数
    local iCount = GetPetCount( mapId, playerId)
    -- 携带骑乘处于解锁状态的计数
    local unlocking = 0
    -- 骑乘仓库中处于解锁状态的计数
    local unlockingInRep = 0
    local arrPets = {}
    local repArr = {}
    -- 检查身上的骑乘
    for i = 0, 6 do
        if IsPetLocked( mapId, playerId, i) == 2 then
            unlocking = unlocking + 1
            arrPets[ unlocking] = GetPetUnlockTime( mapId, playerId, i) - GetCurrentTime()
        end
    end
    -- 检查骑乘仓库
    iCount = LuaGetActiveBankPetSlot( mapId, playerId)
    for i = 0, iCount - 1 do
        if GetActiveBankPetLockState( mapId, playerId, i) == 2 then
            unlockingInRep = unlockingInRep + 1
            repArr[ unlockingInRep] = GetPetUnlockTime( mapId, playerId, i, 1) - GetCurrentTime()
        end
    end
    local strMail = ""
    if unlocking == 1 then
        strMail = format( "您的骑乘处于解锁状态，将在%s解开。", GetDetailTime( GetCurrentTime() + arrPets[ 1] ) )
        if unlockingInRep == 1 then
            strMail = strMail..format( "#r您的骑乘仓库中有坐骑处于解锁状态，将在%s解开。", GetDetailTime( GetCurrentTime() + repArr[ 1] ) )
        elseif unlockingInRep > 1 then
            local strText = ""
            for i, item in repArr do
                strText = strText..GetDetailTime( GetCurrentTime() + item)
                if i ~= getn( repArr) then
                    strText = strText.."、"
                end
            end
            strMail = strMail..format( "#r您的骑乘仓库中有#G%d#W只骑乘处于解锁状态，将分别在%s解锁。", unlockingInRep, strText)
        end
        SendNormalMail( mapId, playerId, GetName( mapId, playerId), strMail)
    elseif unlocking > 1 then
        local strText = ""
        for i, item in arrPets do
            strText = strText..GetDetailTime( GetCurrentTime() + item)
            if i ~= getn( arrPets) then
                strText = strText.."、"
            end
        end
        strMail = format( "您有#G%d#W只骑乘处于解锁状态，将分别在%s解锁。", unlocking, strText)
        if unlockingInRep == 1 then
            strMail = strMail..format( "#r您的骑乘仓库中有坐骑处于解锁状态，将在%s解开。", GetDetailTime( GetCurrentTime() + repArr[ 1] ) )
        elseif unlockingInRep > 1 then
            local strText = ""
            for i, item in repArr do
                strText = strText..GetDetailTime( GetCurrentTime() + item)
                if i ~= getn( repArr) then
                    strText = strText.."、"
                end
            end
            strMail = strMail..format( "#r您的骑乘仓库中有#G%d#W只骑乘处于解锁状态，将分别在%s解锁。", unlockingInRep, strText)
        end
        SendNormalMail( mapId, playerId, GetName( mapId, playerId), strMail)
    else
        -- 没有携带骑乘，检查仓库
        if unlockingInRep == 1 then
            strMail = strMail..format( "#r您的骑乘仓库中有坐骑处于解锁状态，将在%s解开。", GetDetailTime( GetCurrentTime() + repArr[ 1] ) )
            SendNormalMail( mapId, playerId, GetName( mapId, playerId), strMail)
        elseif unlockingInRep > 1 then
            local strText = ""
            for i, item in repArr do
                strText = strText..GetDetailTime( GetCurrentTime() + item)
                if i ~= getn( repArr) then
                    strText = strText.."、"
                end
            end
            strMail = strMail..format( "#r您的骑乘仓库中有#G%d#W只骑乘处于解锁状态，将分别在%s解锁。", unlockingInRep, strText)
            SendNormalMail( mapId, playerId, GetName( mapId, playerId), strMail)
        end
    end
end

---------------------------------------------------------------------------------------------------
--玩家离开地图，切地图和断线都会掉此接口，不过断线执行此函数之前不会置active，此时可处理玩家逻辑
---------------------------------------------------------------------------------------------------
function x888888_ProcMapPlayerLeave( mapId, playerId )
    	
    local sceneType = GetSceneType(mapId)
    
    if sceneType == 2 or sceneType == 7 then 	--战场地图(包括跨服战场)
    	local sceneScriptID = x888888_GetBattleSceneType(mapId)
	    if sceneScriptID ~= -1 then
	    	CallScriptFunction( sceneScriptID,"OnPlayerLeave",mapId, playerId)
	    end
    elseif sceneType == 1 then  				--副本地图
    	CallScriptFunction( FUBEN_COMMON_SCRIPT,"OnPlayerLeave",mapId, playerId)
    else
    	local sceneScriptID = x888888_GetLairdSceneType(mapId)
	    if sceneScriptID ~= -1 then
	    	CallScriptFunction( sceneScriptID,"OnPlayerLeave",mapId, playerId)
	    end
    end 
    
    
    
end

---------------------------------------------------------------------------------------------------
--清除与BUS相关的任务数据,如个人运镖
---------------------------------------------------------------------------------------------------
function x888888_OnClearBusQuestData(mapId, playerId)
	
	--官府押运任务（楼兰）
	for i,item in x888888_g_HeiJinMission do
		if IsHaveQuest(mapId,playerId,item) == 1 then
			CallScriptFunction( 300623, "CleaupMission", mapId, playerId )
			break
		end
	end
    
	--官府押运任务（天山）
	for i,item in x888888_g_HeiJinMission1 do
		if IsHaveQuest(mapId,playerId,item) == 1 then
			CallScriptFunction( 300854,"CleaupMission",mapId,playerId )
			break
		end
	end
	
	--官府押运任务（昆仑）
	for i,item in x888888_g_HeiJinMission2 do
		if IsHaveQuest(mapId,playerId,item) == 1 then
			CallScriptFunction( 300853,"CleaupMission",mapId,playerId )
			break
		end
	end
	
	--官府押运任务（敦煌）
	for i,item in x888888_g_HeiJinMission3 do
		if IsHaveQuest(mapId,playerId,item) == 1 then
			CallScriptFunction( 300852,"CleaupMission",mapId,playerId )
			break
		end
	end
	
	
    --黑金押运任务（楼兰）
    for i,item in x888888_g_PaoQianMission do
		if IsHaveQuest(mapId,playerId,item) == 1 then
			CallScriptFunction( 300760, "CleaupMission", mapId, playerId )
			break
		end
	end
	
	--黑金押运任务（天山）
	for i,item in x888888_g_PaoQianMission1 do
		if IsHaveQuest(mapId,playerId,item) == 1 then
			CallScriptFunction(	300866,"CleaupMission",mapId,playerId )
			break
		end
	end
	
	--黑金押运任务（昆仑）
	for i,item in x888888_g_PaoQianMission2 do
		if IsHaveQuest(mapId,playerId,item) == 1 then
			CallScriptFunction( 300865,"CleaupMission",mapId,playerId )
			break
		end
	end
	
	--黑金押运任务（敦煌）
	for i,item in x888888_g_PaoQianMission3 do
		if IsHaveQuest(mapId,playerId,item) == 1 then
			CallScriptFunction( 300864,"CleaupMission",mapId,playerId )
			break
		end
	end
	
	--云游贩任务
	 for i,item in x888888_g_YunYuFanMission do
		if IsHaveQuest(mapId,playerId,item) == 1 then
			CallScriptFunction( 310071, "OnLogInOrDie", mapId, playerId  )
			break
		end
	end
    
    --护送任务
    if IsHaveQuest(mapId, playerId, SPOUSE_TASK[2]) == 1 and 
       GetSex(mapId, playerId) == 1 then
		CallScriptFunction( 300354, "Abandon", mapId, playerId )
	end
    
    --运镖任务
    local nMissionID = GetQuestData(mapId,playerId,MD_GUOJIARENWU_RANDMISSIONID[1], MD_GUOJIARENWU_RANDMISSIONID[2], MD_GUOJIARENWU_RANDMISSIONID[3])
    if nMissionID >= 6450 and nMissionID <= 6461 then
    	CallScriptFunction( 300519, "ClearBusMission", mapId, playerId )
    end
    
    -- 战车押运
    if IsHaveQuest(mapId, playerId, 7031) == 1 then 
        CallScriptFunction( 300763, "CleaupMission", mapId, playerId )
    end

	
    if IsHaveQuest(mapId, playerId, 7032) == 1 then 
        CallScriptFunction( 300911, "CleaupMission", mapId, playerId )
    end
    
    
    if IsHaveQuest(mapId, playerId, 7033) == 1 then 
        CallScriptFunction( 300914, "CleaupMission", mapId, playerId )
    end
    
    
    if IsHaveQuest(mapId, playerId, 7034) == 1 then 
        CallScriptFunction( 300917, "CleaupMission", mapId, playerId )
    end
    
    -- 帮会神兽
    if 5 == GetGuildOfficial(mapId, playerId) then
		if IsHaveQuest(mapId, playerId, 7002) == 1 then 
			CallScriptFunction( 300608, "ClearBusMission", mapId, playerId )
		end
		if IsHaveQuest(mapId, playerId, 7023) == 1 then 
			CallScriptFunction( 300871, "ClearBusMission", mapId, playerId )
		end
		if IsHaveQuest(mapId, playerId, 7022) == 1 then 
			CallScriptFunction( 300869, "ClearBusMission", mapId, playerId )
		end
		if IsHaveQuest(mapId, playerId, 7021) == 1 then 
			CallScriptFunction( 300867, "ClearBusMission", mapId, playerId )
		end
	end
    
    missionTbl = nil
end


---------------------------------------------------------------------------------------------------
--杀死玩家的PK值计算
---------------------------------------------------------------------------------------------------
function x888888_ComputePKPunish( mapId, playerId, killerId )

	--081212(齐亮)加入被杀者如果处于PK模式(包括使用面具和“六亲不认”等道具)也不增加杀人者的PK值
	local IncrePK = 0
	local DierPKValue = GetPKValue(mapId, playerId)	
	local DierPKMode = GetPlayerPKMode(mapId, playerId)
	local killerPKValue = GetPKValue(mapId, killerId)
	local killerPKMode = GetPlayerPKMode(mapId, killerId)

	--死者是红名玩家（狂暴模式），降低1点PK值
	if DierPKMode == 2 then	
	--	DierPKValue = DierPKValue - PK_PUNISH_DIER_RED_NAME_DECRE_PK
	--	SetPKValue(mapId, playerId, DierPKValue)
	end	
		
	if (DierPKMode==0 or DierPKMode==1) and (killerPKMode==2) then
		IncrePK = PK_PUNISH_KILL_GREEN_NAME_INCRE_PK
	end

	--PK值变化
	local PKSelf = GetPKValue(mapId, killerId)
	PKSelf = PKSelf + IncrePK
	if IsKing(mapId, killerId) ~= 1 and IncrePK > 0 then
		--非国王并且PK惩罚值大于0
		SetPKValue(mapId, killerId, PKSelf)
		return 1
	end

	return 0

end

---------------------------------------------------------------------------------------------------
--杀死镖车的PK值计算
---------------------------------------------------------------------------------------------------
function x888888_CashboxComputePKPunish( mapId, playerId, killerId )
	
	--计算PK值
	local IncrePK = 0
	local DierPK = GetPKValue(mapId, playerId)
	if DierPK > 0 then	--镖车主人是红名玩家				
		IncrePK = 0	
	else				--死者是绿名玩家		
		IncrePK = PK_PUNISH_KILL_GREEN_CASHBOX_INCRE_PK
	end

	--PK值变化
	local PKSelf = GetPKValue(mapId, killerId)
	PKSelf = PKSelf + IncrePK
	if IsKing(mapId, killerId) ~= 1 and IncrePK > 0 then
		--非国王并且PK惩罚值大于0
		SetPKValue(mapId, killerId, PKSelf)
		return 1
	end

	return 0

end

---------------------------------------------------------------------------------------------------
--根据PK规则将杀人者投入监狱
---------------------------------------------------------------------------------------------------
function x888888_KillerEnterPrison(mapId, playerId)

	if IsKing(mapId, playerId) == 1 then
		return
	end

	local PKVal = GetPKValue(mapId, playerId)
	if PKVal < x888888_g_PrisonMinPKVal then
		return
	end

	if IsBusMember( mapId, playerId ) == 1 then  

		local BusId = GetBusId(mapId, playerId)
		if BusId ~= 1 then

			local BusHp = GetHp(mapId, BusId)	--得到BUS的HP

			local BusType = GetBusType(mapId, BusId)
			if BusType == 1 then		--普通BUS
				DelBusMember(mapId, playerId,BusId)
			elseif BusType == 0 then	--个人镖车
				if BusHp > 0 then
					SetHp(mapId,BusId,-BusHp)
				end
			elseif BusType == 2 then	--帮会镖车
				if BusHp > 0 then
					SetHp(mapId,BusId,-BusHp)
				end
			end
		end

	end

	if IsInStall(mapId, playerId) == 1 then
		--解除摆滩状态
		CloseStall(mapId, playerId)
	end

	--取消答题状态
	local MentalActId = 0
	if AbandonMentalGame( mapId,playerId,MentalActId ) == -1 then
		return
	end

	--增加监狱倒计时BUF
	--local bRet = SendSpecificImpactToUnit(mapId, playerId, playerId, playerId, PK_PUNISH_PRISON_TIME_BUF_ID, 0)
	--if bRet == 0 then
	--	return
	--end

	--全国公告
	local Text = format( "%s因杀戮过多，被投入监狱进行惩罚",GetName(mapId, playerId) )
	if GetGuildID(mapId, playerId) ~= -1 then
		Text = format( "%s帮会%s因杀戮过多，被投入监狱进行惩罚",GetGuildTitle(mapId, playerId),GetName(mapId, playerId) )
	end
	Msg2Player(mapId,playerId,Text,7,2)

	--投入监狱
	SendSpecificImpactToUnit(mapId, playerId, playerId, playerId, PK_PUNISH_PRISON_TIME_BUF_ID, 0)	
	if NewWorld(mapId, playerId, PK_PUNISH_PRISON_SCENE_ID, 25, 15, 888888) == 1 then
		SetPlayerNextSceneInfo(mapId, playerId, PK_PUNISH_PRISON_SCENE_ID, 25, 15)
		SetPlayerMutexState( mapId,playerId ,PLAYER_STATE_PRISON ,1)
	else
		CancelSpecificImpact(mapId, playerId,PK_PUNISH_PRISON_TIME_BUF_ID )
	end
	
end

---------------------------------------------------------------------------------------------------
--检查是否能加参婚礼
---------------------------------------------------------------------------------------------------
function x888888_IsCanGotoWeddingPosition( mapId, playerId, newMapId )
	local msg = nil
	local level = GetLevel(mapId, playerId)
	local IsCanTrans = CallScriptFunction( COUNTRY_BATTLE_LITE_SCRIPT,"CheckCountryBattleLiteSceneTrans", mapId, playerId, newMapId)
  if IsCanTrans <= 0 then
  	msg = "当前场景不能参加婚礼。"
	elseif PK_PUNISH_PRISON_SCENE_ID == mapId then
		msg = "当前在监狱中不能参加婚礼。"
	elseif level < 40 then
		msg = "等级低于40不能参加婚礼。"
	end
	--是否在游乐场并处于变身状态
	local IsHaveFlag = IsHaveSpecificImpact(mapId, playerId, 7536  )
    if IsHaveFlag ~= 0 then
    	msg = "在暴龙大作战期间，不能参加婚礼。"
    end
    
    IsHaveFlag = IsHaveSpecificImpact(mapId, playerId, 7537 )
    if IsHaveFlag ~= 0 then
    	msg = "在暴龙大作战期间，不能参加婚礼。"
    end
    
	if msg ~= nil then
		BeginQuestEvent(mapId);
		AddQuestText(mapId, msg);
		EndQuestEvent();
		DispatchQuestTips(mapId, playerId);
		Msg2Player(mapId, playerId, msg, CHAT_TYPE_SELF, CHAT_RIGHTDOWN)
		return 0
	end
	return 1
end

---------------------------------------------------------------------------------------------------
--参加婚礼
---------------------------------------------------------------------------------------------------
function x888888_OnGotoWeddingPosition( mapId, playerId, moneyCount)
	local level = GetLevel(mapId, playerId)
	local exp = 0
	if moneyCount == 5000 then
		exp = level *1500
	elseif moneyCount == 10000 then
		exp = level *3000
	end
	AddExp(mapId, playerId, exp);
	BeginQuestEvent(mapId);
	AddQuestText(mapId, "您获得"..exp.."点经验");
	EndQuestEvent();
	DispatchQuestTips(mapId, playerId);
	Msg2Player(mapId,playerId,"您获得"..exp.."点经验",CHAT_TYPE_SELF,CHAT_RIGHTDOWN)
end

---------------------------------------------------------------------------------------------------
--现金领取检查
---------------------------------------------------------------------------------------------------
function x888888_OnIsCanTransGoldToChar( mapId, playerId)

    if IsPlayerStateNormal(mapId,playerId ) == 0 then
		--状态异常
		return 0
	end

	--当低于10级的玩家进行领取现金的操作时，进行提示
	local level = GetLevel(mapId, playerId)
	if level < 10 then
		BeginQuestEvent(mapId)
		AddQuestText(mapId, "操作失败！10级以下玩家无法领取现金！");
		EndQuestEvent(mapId)
		DispatchQuestTips(mapId,playerId)
		return 0
	end
	
	if IsPlayerMutexState(mapId,playerId,PLAYER_STATE_READYFUBEN ) == 1 then
		--副本准备状态
		if mapId ~= 12 then
			BeginQuestEvent(mapId)
			AddQuestText(mapId, "接受副本任务准备进入副本时不可以领取现金！");
			EndQuestEvent(mapId)
			DispatchQuestTips(mapId,playerId)
			return 0
		end

	end

	if IsPlayerMutexState(mapId,playerId,PLAYER_STATE_TransGold ) == 1 then
		--领取现金状态
		BeginQuestEvent(mapId)
		AddQuestText(mapId, "上一次领取现金操作未返回，稍后重试！");
		EndQuestEvent(mapId)
		DispatchQuestTips(mapId,playerId)
		return 0
	end

	return 1

end

---------------------------------------------------------------------------------------------------
--检查是否可以传送到打架位置
---------------------------------------------------------------------------------------------------
function x888888_CheckGotoFightPos(mapId, playerId)
	
	local country = GetCurCountry(mapId, playerId)		--0楼兰王国 1天山王国 2昆仑王国 3敦煌王国
	if (mapId == country*100 + 50) or 		--王城
	   (mapId == country*100 + 51) or 		--边境
	   (mapId == country*100 + 86) or 		--古道
	   (mapId == country*100 + 87) or 		--马场
	   (mapId == country*100 + 89) or 		--草场
	   (mapId == country*100 + 58) then		--外城
		return 1
	end
	
	local szMsg = "只有在本国王城、本国边境、本国古道、本国马场、本国猎场才能传送到战斗地点。"
	Msg2Player(mapId,playerId,szMsg,8,2)
	BeginQuestEvent(mapId)
	AddQuestText(mapId, szMsg);
	EndQuestEvent(mapId)
	DispatchQuestTips(mapId,playerId)
	return -1
end

---------------------------------------------------------------------------------------------------
--玩家技能使用情况
---------------------------------------------------------------------------------------------------
function x888888_IsHumanCanUseSkillNow(mapId, playerId, skillId,targetId)
	if skillId == 16 then --回城技能
	
		if IsBusMember(mapId, playerId) == 1 then
			local msg = "运镖、乘坐公交车或者护送状态时不能使用回城类技能！"
			Msg2Player(mapId,playerId,msg,8,2)
			Msg2Player(mapId,playerId,msg,8,3)
			return -1
		end
		
		if IsHaveQuestNM( mapId, playerId, 7537) ~= 0 or  
		   IsHaveQuestNM( mapId, playerId, 7538) ~= 0 or 
		   IsHaveQuestNM( mapId, playerId, 7539) ~= 0 then
			Msg2Player(mapId,playerId,"未完成铁人三项任务不能使用回城类技能",8,2)
			return -1
		end
		
		if mapId==PK_PUNISH_PRISON_SCENE_ID then
			local msg = "监狱中不能使用回城类技能！"
			Msg2Player(mapId,playerId,msg,8,2)
			Msg2Player(mapId,playerId,msg,8,3)
			return -1	
		end
		
		--PVP2v2竞技场
		local nSceneType = x888888_GetBattleSceneType(mapId)
		if  nSceneType == PVP2V2_BATTLE_SCRIPT or nSceneType == MPVP2V2_BATTLE_SCRIPT then
			local msg = "竞技场中不能使用回城类技能！"
			Msg2Player(mapId,playerId,msg,8,2)
			Msg2Player(mapId,playerId,msg,8,3)
			return -1
			
		end		
	end

	--6V6竞技场对所有加血技能进行处理
	if x888888_GetBattleSceneType( mapId ) == PVP6V6_BATTLE_SCRIPT then
		
		for i,itm in x888888_g_HP_SkillID do
		
			if itm == skillId then
			
				--目标有效
				if IsObjValid(mapId,targetId) == 1 then
				
					--不是玩家也不是宠物,不可以使用
					local objType = GetObjType(mapId, targetId)
					if objType ~= 3 then
						if IsPlayerStateNormal(mapId,targetId) ~= 1 then
							return -1
						end
					end					
				end
				
				return 1
			end
		end
	end
	
	
	return 1
end

---------------------------------------------------------------------------------------------------
--决斗结果
---------------------------------------------------------------------------------------------------
function x888888_OnDuelResult(mapId, playerId, loserid)

	if IsObjValid(mapId,loserid)~=1 then
		return
	end	
	local buffID = 8356
	SendSpecificImpactToUnit(sceneId,playerId,playerId,playerId,buffID,0)
	SendSpecificImpactToUnit(sceneId,loserid,loserid,loserid,buffID,0)
	
	local szWinName = GetName(mapId, playerId)
	local szLoseName = GetName(mapId, loserid)
	local msg = szWinName .. "在决斗中战胜了" .. szLoseName
	LuaScenceM2Near(mapId,playerId,msg,5,-1)
end

---------------------------------------------------------------------------------------------------
--检查宠物是否可以放到仓库
---------------------------------------------------------------------------------------------------
function x888888_CanMovePetToBank(mapId, playerId, petType)
	--国王、王后等的骑乘不能放到仓库
	for i=3001,3018 do
		if i == petType then
			local szMsg = "国王、王后、守护骑乘不能放入仓库"
			BeginQuestEvent(mapId)
			AddQuestText(mapId, szMsg);
			EndQuestEvent(mapId)
			DispatchQuestTips(mapId,playerId)
			return 0
		end
	end
	return 1
end

---------------------------------------------------------------------------------------------------
--检查宠是否可以锁定
---------------------------------------------------------------------------------------------------
function x888888_CanLockPet(mapId, playerId, petType)
	--国王、王后等的骑乘不能lock
	for i=3001,3018 do
		if i == petType then
			local szMsg = "国王、王后、守护骑乘不能加锁"
			BeginQuestEvent(mapId)
			AddQuestText(mapId, szMsg);
			EndQuestEvent(mapId)
			DispatchQuestTips(mapId,playerId)		
			return 0
		end
	end
	return 1
end

---------------------------------------------------------------------------------------------------
--检查装备是否可以锁定
---------------------------------------------------------------------------------------------------
function x888888_CanLockEquip(mapId, playerId, itemType)
	--国王套装不能lock
	--print(itemType)
	if 10300100 == itemType then
		local szMsg = "国王、王后装备不能加锁"
		BeginQuestEvent(mapId)
		AddQuestText(mapId, szMsg);
		EndQuestEvent(mapId)
		DispatchQuestTips(mapId,playerId)	
		return 0
	end
	return 1
end

---------------------------------------------------------------------------------------------------
--每周更新2v2英雄会等级
---------------------------------------------------------------------------------------------------
function x888888_OnCheckpvp2v2Data(mapId, playerId,bClear)

	if IsObjValid(mapId,playerId)~=1 then
		return
	end	

	local flag = 0
	local weekfirstday = GetWeekFirstDay()
	if bClear == 0 then
		local lastDay = GetQuestData( mapId, playerId, MD_PVP2V2_CLEARMARK_DATE[1], MD_PVP2V2_CLEARMARK_DATE[2], MD_PVP2V2_CLEARMARK_DATE[3] )
		local curDay = GetDayOfYear()
		if lastDay ~= weekfirstday then
			flag = 1
		end	
	elseif bClear == 1 then
		if GetWeek() == 1 then
			flag = 1
		end
	end
	
	if flag==1 then
		SetQuestData(mapId, playerId, MD_PVP2V2_CLEARMARK_DATE[1], MD_PVP2V2_CLEARMARK_DATE[2], MD_PVP2V2_CLEARMARK_DATE[3], weekfirstday)
		SetPVP2V2Mark_WeekTotal(mapId, playerId,0)
	end
	
end
---------------------------------------------------------------------------------------------------
--在这里加上处理，是为了防止脚本出错和误载入
---------------------------------------------------------------------------------------------------
function x888888_OnCheckQuestSubmitNPC(mapId,playerId,idScript,idMission,npcGUID)
	
	for i,item in x888888_g_CheckScriptTable do
		if item == idScript then
			return CallScriptFunction(idScript,"CheckSubmitNPC",mapId,playerId,idScript,idMission,npcGUID)
		end
	end
	
	return 0
end

---------------------------------------------------------------------------------------------------
--取得战场类型，普通地图或是没有在这里注册过的战场，返回-1
---------------------------------------------------------------------------------------------------
function x888888_GetBattleSceneType( mapId )
	
	--非战场类型的地图
	local sceneType = GetSceneType(mapId)
	if sceneType ~= 2 and sceneType ~= 7 then
		return -1
	end
	
	local name = GetBattleSceneName(mapId)
					   
	for i,item in x888888_g_BattleSceneList do
		if name == item[1] then
			return item[2]
		end
	end
	
	return -1
end

---------------------------------------------------------------------------------------------------
--取得据点战类型
---------------------------------------------------------------------------------------------------
function x888888_GetLairdSceneType( mapId )
	
	--非战场类型的地图
	if GetSceneType(mapId) ~= 0 then
		return -1
	end
	
	local name = GetBattleSceneName(mapId)
					   
	for i,item in x888888_g_LairdSceneList do
		if name == item[1] then
			return item[2]
		end
	end
	
	return -1
end

---------------------------------------------------------------------------------------------------
--检查场景是否是据点场景
---------------------------------------------------------------------------------------------------
function x888888_IsLairdScene( mapId )
	
	if mapId ==  6 or mapId ==  5 or mapId ==  7 or
	   mapId ==  9 or mapId ==  8 or mapId == 10 or
	   mapId == 13 or mapId == 11 or mapId == 16 or
	   mapId == 18 or mapId == 17 or mapId == 19 or
	   mapId == 21 or mapId == 20 or mapId == 22 or
	   mapId == 24 or mapId == 23 or mapId == 25 or
	   mapId == 27 or mapId == 26 or mapId == 29 or
	   mapId == 31 or mapId == 30 or mapId == 32 or 
	   mapId == 34 or mapId == 33 or mapId == 35 then
	   return 1
	end
	
	return 0
end

---------------------------------------------------------------------------------------------------
--取得国家占领的据点场景数量
---------------------------------------------------------------------------------------------------
function x888888_GetCountryLairdSceneCount(mapId,countryId)
	
	local nLairdCountry = 0
	if countryId < 0 or countryId > 3 then
		return nLairdCountry
	end
	
	for i,item in x888888_g_LairdSceneList do
		if GetSceneLairdCountryId(item[3]) == countryId then
			nLairdCountry =nLairdCountry + 1
		end
	end
	
	return nLairdCountry
end

---------------------------------------------------------------------------------------------------
--根据国家信息,取得本国所占的据点场景数量以及所有据点的等级和
---------------------------------------------------------------------------------------------------
function x888888_GetCountryLairdSceneInfo(mapId,countryId)
	
	local nLairdCountry = 0
	local nLairdSumLevel = 0
	if countryId < 0 or countryId > 3 then
		return nLairdCountry,nLairdSumLevel
	end
	
	for i,item in x888888_g_LairdSceneList do
		if GetSceneLairdCountryId(item[3]) == countryId then
			nLairdCountry =nLairdCountry + 1
			nLairdSumLevel = nLairdSumLevel + GetSceneLairdLevel(item[3])
		end
	end
	
	return nLairdCountry,nLairdSumLevel
end

---------------------------------------------------------------------------------------------------
--取得战场类型，普通地图或是没有在这里注册过的战场，返回-1
--注:此函数仅能在ProcMapInit中调用,其他地方禁止调用,因为此函数实现是线程不安全的
---------------------------------------------------------------------------------------------------
function x888888_GetBattleSceneTypeNM( mapId )
	
	--非战场类型的地图
	local sceneType = GetSceneType(mapId)
	
	if sceneType ~= 2 and sceneType ~= 7 then
		return -1
	end
	
	local name = GetBattleSceneNameNM(mapId)
					   
	for i,item in x888888_g_BattleSceneList do
		if name == item[1] then
			return item[2]
		end
	end
	
	return -1
end


---------------------------------------------------------------------------------------------------
--取得战场类型，普通地图或是没有在这里注册过的战场，返回-1
--注:此函数仅能在ProcMapInit中调用,其他地方禁止调用,因为此函数实现是线程不安全的
---------------------------------------------------------------------------------------------------
function x888888_GetLairdSceneTypeNM( mapId )
	
	--非战场类型的地图
	if GetSceneType(mapId) ~= 0 then
		return -1
	end
	
	local name = GetBattleSceneNameNM(mapId)
					   
	for i,item in x888888_g_LairdSceneList do
		if name == item[1] then
			return item[2]
		end
	end
	
	return -1
end

---------------------------------------------------------------------------------------------------
--检查是否是屠城战场景
---------------------------------------------------------------------------------------------------
function x888888_IsCountryBattleLiteMap(mapId )
	
	if mapId ==  50 or mapId == 150 or mapId == 250 or mapId == 350 or
       mapId ==  51 or mapId == 151 or mapId == 251 or mapId == 351 or 
	   mapId ==  58 or mapId == 158 or mapId == 258 or mapId == 358 or 	   
       mapId ==  68 or mapId == 168 or mapId == 268 or mapId == 368 or
       mapId ==  76 or mapId == 176 or mapId == 276 or mapId == 376 or
       mapId ==  86 or mapId == 186 or mapId == 286 or mapId == 386 or
	   mapId ==  89 or mapId == 189 or mapId == 289 or mapId == 389 or
	   mapId == 104 or mapId == 204 or mapId == 304 or mapId == 404 or
	   mapId == 105 or mapId == 205 or mapId == 305 or mapId == 405 or
	   mapId == 106 or mapId == 206 or mapId == 306 or mapId == 406 or
	   mapId == 107 or mapId == 207 or mapId == 307 or mapId == 407 or
	   mapId == 108 or mapId == 208 or mapId == 308 or mapId == 408 or
	   mapId == 109 or mapId == 209 or mapId == 309 or mapId == 409 or
	   mapId == 110 or mapId == 210 or mapId == 310 or mapId == 410 or
	   mapId == 111 or mapId == 211 or mapId == 311 or mapId == 411 or
       mapId ==  91 or mapId == 191 or mapId == 291 or mapId == 391 or mapId == 3 then
       
       return 1
	end
	
	return 0
	
end

---------------------------------------------------------------------------------------------------
--屠城战接受任务的请求
---------------------------------------------------------------------------------------------------
function x888888_OnCountryBattleLiteChangeScene( mapId,playerId,campFlag,nMatchCountry )
	
	if x888888_IsCountryBattleLiteMap(mapId ) ~= 1 then   	
	
	   	--只有在王城和大都才可以接受屠城战
	   	Msg2Player(mapId, playerId, "身处中兴府，王城，外城，边境及古道才能参加【国家】屠城战", 0, 2)
		Msg2Player(mapId, playerId, "身处中兴府，王城，外城，边境及古道才能参加【国家】屠城战", 0, 3)
	   	
	   	return
	end
	
	--地图检查通过，可以参加屠城战
	CallScriptFunction( COUNTRY_BATTLE_LITE_SCRIPT,"OnCountryBattleLiteChangeScene", mapId,playerId,campFlag,nMatchCountry )
end

---------------------------------------------------------------------------------------------------
--屠城战切地图处理
---------------------------------------------------------------------------------------------------
function x888888_OnCountryBattleLitePlayerEnter( mapId,playerId )

	--当有屠城战任务的时候，进行相关处理
	if IsHaveQuest(mapId,playerId, 7559) == 1 then
    	
		if x888888_IsCountryBattleLiteMap(mapId ) ~= 1 then
		   	--清除任务
			DelQuest(mapId, playerId, 7559)
			
			--清除BUF
			for i,item in x888888_g_CountryBattleLite_BufID do
				if IsHaveSpecificImpact(mapId,playerId,item) == 1 then
					CancelSpecificImpact(mapId,playerId,item)
				end
			end			
			
			GamePlayScriptLog( mapId, playerId, 1513)
			
		  	Msg2Player(mapId, playerId, "您退出了【国家】屠城战！", 0, 2)
			Msg2Player(mapId, playerId, "您退出了【国家】屠城战！", 0, 3)
		end
	end
end

---------------------------------------------------------------------------------------------------
--传送到队友身边提示
---------------------------------------------------------------------------------------------------
function x888888_IsCanGotoTeamMemberPosition( mapId, playerId, newMapId )
	local msg = nil
 	local IsCanTrans = CallScriptFunction( COUNTRY_BATTLE_LITE_SCRIPT,"CheckCountryBattleLiteSceneTrans", mapId, playerId, newMapId)
 	if IsCanTrans <= 0 then
  		msg = "当前场景不能传送到队友的身边。"
	elseif PK_PUNISH_PRISON_SCENE_ID == mapId then
		msg = "在监狱中不能被传送到队友的身边。"
	end
	
	--是否在游乐场并处于变身状态
	local IsHaveFlag = IsHaveSpecificImpact(mapId, playerId, 7536  )
    if IsHaveFlag ~= 0 then
    	msg = "在暴龙大作战期间，不能传送"
    end
    
    IsHaveFlag = IsHaveSpecificImpact(mapId, playerId, 7537 )
    if IsHaveFlag ~= 0 then
    	msg = "在暴龙大作战期间，不能传送"
    end
	
	
	--提示信息
	if msg ~= nil then
		BeginQuestEvent(mapId);
		AddQuestText(mapId, msg);
		EndQuestEvent();
		DispatchQuestTips(mapId, playerId);
		Msg2Player(mapId, playerId, msg, CHAT_TYPE_SELF, CHAT_RIGHTDOWN)
		return 0
	end
	
	
	
	msg = "被传送到队友的身边。"
	BeginQuestEvent(mapId);
	AddQuestText(mapId, msg);
	EndQuestEvent();
	DispatchQuestTips(mapId, playerId);
	Msg2Player(mapId, playerId, msg, CHAT_TYPE_SELF, CHAT_RIGHTDOWN)
	return 1
end


---------------------------------------------------------------------------------------------------
--增加善恶值?
---------------------------------------------------------------------------------------------------
function x888888_IsCanAddGoodbadValue( mapId, monsterDataId )
	for i, item in x888888_g_DonotAddGoodbadTable do
		if tonumber(item) == tonumber(mapId) then
			return -1
		end
	end
	return 1
end

---------------------------------------------------------------------------------------------------
--更新蒙面人状态
---------------------------------------------------------------------------------------------------
function x888888_UpdateHideNameState( mapId, playerId, ReliveType )
	if ReliveType ~= x888888_g_ReliveType.OriginLosslessRelive then
		DispelSpecificImpact(mapId, playerId, 7661)
		DispelSpecificImpact(mapId, playerId, 7662)
	end
end

---------------------------------------------------------------------------------------------------
--更新排行榜数据
---------------------------------------------------------------------------------------------------
function x888888_UpdateTopListKeyValue(mapId, playerId)

	-- 夫妻排行榜
	local spouseguid = GetSpouseGUID(mapId, playerId)
	if spouseguid ~= 4294967295 then
		local friendpoint = GetFriendPointByGuid(mapId, playerId, spouseguid)
		SendToplistKeyValue2GL( mapId, playerId, SPOUSE_TOPLIST, friendpoint )
	end
	
	-- 师傅排行榜
	--local prenticescore = GetFinishedPrenticeshipCount(mapId, playerId)
	--if prenticescore > 0 then
		--SendToplistKeyValue2GL( mapId, playerId, MASTER_TOPLIST, prenticescore )
	--end

end


---------------------------------------------------------------------------------------------------
--送给好友礼物
---------------------------------------------------------------------------------------------------
function x888888_OnUseFriendItem(mapId, playerId, itemindex)
	
end

---------------------------------------------------------------------------------------------------
--收到好友送的礼物
---------------------------------------------------------------------------------------------------
function x888888_OnReceiveFriendItem(mapId, playerId, itemindex)
	
	local curPoint = GetQuestData( mapId, playerId, MD_AMATIVE_POINT[1], MD_AMATIVE_POINT[2], MD_AMATIVE_POINT[3] )
	local lastday = GetQuestData( mapId, playerId, MD_AMATIVE_DAY[1], MD_AMATIVE_DAY[2], MD_AMATIVE_DAY[3] )
	local curDay = GetWeekFirstDay()
	if lastday ~= curDay then
		curPoint = 0
	end
	
	--钟情一生，加1点
	if itemindex==12110206 then
	
		curPoint = curPoint + 1
		if curPoint > 99999 then
			curPoint = 99999
		end
		SetQuestData( mapId, playerId, MD_AMATIVE_POINT[1], MD_AMATIVE_POINT[2], MD_AMATIVE_POINT[3], curPoint )
		SetQuestData( mapId, playerId, MD_AMATIVE_DAY[1], MD_AMATIVE_DAY[2], MD_AMATIVE_DAY[3], curDay )
		
		SendToplistKeyValue2GL(mapId, playerId, AMATIVE_TOPLIST, curPoint)
	end
	
	--爱无止境，加10点
	if itemindex==12110207 then

		curPoint = curPoint + 10
		if curPoint > 99999 then
			curPoint = 99999
		end		
		SetQuestData( mapId, playerId, MD_AMATIVE_POINT[1], MD_AMATIVE_POINT[2], MD_AMATIVE_POINT[3], curPoint )	
		SetQuestData( mapId, playerId, MD_AMATIVE_DAY[1], MD_AMATIVE_DAY[2], MD_AMATIVE_DAY[3], curDay )
		
		SendToplistKeyValue2GL(mapId, playerId, AMATIVE_TOPLIST, curPoint)
	end
	
end

---------------------------------------------------------------------------------------------------
--使用小喇叭触发
---------------------------------------------------------------------------------------------------
function x888888_OnUseLaBa(mapId, playerId)

	local lastday = GetQuestData( mapId, playerId, MD_LABA_DAY[1], MD_LABA_DAY[2], MD_LABA_DAY[3] )
	local curCount = GetQuestData( mapId, playerId, MD_LABA_COUNT[1], MD_LABA_COUNT[2], MD_LABA_COUNT[3] )
	local curday = GetWeekFirstDay()
	--print("curday="..curday..", lastday="..lastday..", curCount="..curCount)
	if lastday ~= curday then
		--print("XXXXXXXXXXXXXXX")
		curCount = 0
	end
	curCount = curCount + 1
	SetQuestData( mapId, playerId, MD_LABA_COUNT[1], MD_LABA_COUNT[2], MD_LABA_COUNT[3], curCount )
	SetQuestData( mapId, playerId, MD_LABA_DAY[1], MD_LABA_DAY[2], MD_LABA_DAY[3], curday )
	
	--print("curCount="..curCount)
	SendToplistKeyValue2GL(mapId, playerId, LABA_TOPLIST, curCount)
	
end

---------------------------------------------------------------------------------------------------
--答题触发
---------------------------------------------------------------------------------------------------
function x888888_OnTopListMental(mapId,playerId,nScore)

	--智力竞赛加上排行榜开关
	if GetGameOpenById(1035) ~= 1 then
		return
	end
	
	--取得上次记录的周和分数
	local lastweek = GetQuestData( mapId, playerId, MD_MENTAL_WEEK[1], MD_MENTAL_WEEK[2], MD_MENTAL_WEEK[3] )
	local curscore = GetQuestData( mapId, playerId, MD_MENTAL_SCORE[1], MD_MENTAL_SCORE[2], MD_MENTAL_SCORE[3] )
	
	--取得当前周，如果当前周与上次记录的周不匹配，先清空数据
	local curweek = GetWeekFirstDay()
	if lastweek ~= curweek then
		curscore = 0
	end
	
	--分数相关，然后记录
	curscore = curscore + nScore
	if curscore < 0 then
		curscore = 0
	end
	SetQuestData( mapId, playerId, MD_MENTAL_SCORE[1], MD_MENTAL_SCORE[2], MD_MENTAL_SCORE[3], curscore )
	SetQuestData( mapId, playerId, MD_MENTAL_WEEK[1], MD_MENTAL_WEEK[2], MD_MENTAL_WEEK[3], curweek )
	
	--传送相关数据到gl
	SendToplistKeyValue2GL(mapId, playerId, DATI_TOPLIST, curscore)
	
end

---------------------------------------------------------------------------------------------------
--排行榜GM命令设置值
---------------------------------------------------------------------------------------------------
function x888888_OnTopListGMCommand(mapId,playerId,nValue,nType)

	if nType == LUNHUITAI_TOPLIST 					-- 轮回台
		or nType == QIULONGDAO_TOPLIST				-- 囚龙岛
		or nType == HESHIBI_TOPLIST					-- 和氏璧
		or nType == CAISHENDIAN_TOPLIST				-- 财神殿
		or nType == ZHUJIAZHUANG_TOPLIST			-- 祝家庄
        or nType == JINGJIAOTANG_TOPLIST            -- 景教堂
        or nType == ZHANSHENMU_TOPLIST              -- 战神墓
        or nType == INDIANTEMPLE_TOPLIST            -- 印度神庙
		then			
		SendToplistKeyValue2GL(mapId,playerId,nType,nValue)
		
	elseif nType == DATI_TOPLIST then				-- 智力竞赛
		x888888_OnTopListMental(mapId,playerId,nValue)
		
	elseif nType == AMATIVE_TOPLIST	then			-- 恋爱榜
		local lastweek = GetQuestData( mapId, playerId, MD_AMATIVE_DAY[1], MD_AMATIVE_DAY[2], MD_AMATIVE_DAY[3] )
		local curcount = GetQuestData( mapId, playerId, MD_AMATIVE_POINT[1], MD_AMATIVE_POINT[2], MD_AMATIVE_POINT[3] )
		local curweek = GetWeekFirstDay()
		if lastweek ~= curweek then
			curcount = 0
		end
		curcount = nValue
		SetQuestData( mapId, playerId, MD_AMATIVE_POINT[1], MD_AMATIVE_POINT[2], MD_AMATIVE_POINT[3], curcount )
		SetQuestData( mapId, playerId, MD_AMATIVE_DAY[1], MD_AMATIVE_DAY[2], MD_AMATIVE_DAY[3], curweek )
		SendToplistKeyValue2GL(mapId, playerId, AMATIVE_TOPLIST, curcount)	
	
	elseif nType == YANHUA_TOPLIST then				-- 烟花榜
		local lastweek = GetQuestData( mapId, playerId, MD_YANHUA_WEEK[1], MD_YANHUA_WEEK[2], MD_YANHUA_WEEK[3] )
		local curcount = GetQuestData( mapId, playerId, MD_YANHUA_COUNT[1], MD_YANHUA_COUNT[2], MD_YANHUA_COUNT[3] )
		local curweek = x888888_GetWorldWeek()
		if lastweek ~= curweek then
			curcount = 0
		end
		curcount = nValue
		SetQuestData( mapId, playerId, MD_YANHUA_COUNT[1], MD_YANHUA_COUNT[2], MD_YANHUA_COUNT[3], curcount )
		SetQuestData( mapId, playerId, MD_YANHUA_WEEK[1], MD_YANHUA_WEEK[2], MD_YANHUA_WEEK[3], curweek )
		SendToplistKeyValue2GL(mapId, playerId, YANHUA_TOPLIST, curcount)	
	
	elseif nType == BAOZANG_TOPLIST then			-- 宝藏榜
		local lastday = GetQuestData( mapId, playerId, MD_BAOZANG_DAY[1], MD_BAOZANG_DAY[2], MD_BAOZANG_DAY[3] )
		local curCount = GetQuestData( mapId, playerId, MD_BAOZANG_COUNT[1], MD_BAOZANG_COUNT[2], MD_BAOZANG_COUNT[3] )
		local curday = GetWeekFirstDay()
		if lastday ~= curday then
			curCount = 0
		end
		curCount = nValue
		SetQuestData( mapId, playerId, MD_BAOZANG_COUNT[1], MD_BAOZANG_COUNT[2], MD_BAOZANG_COUNT[3], curCount )
		SetQuestData( mapId, playerId, MD_BAOZANG_DAY[1], MD_BAOZANG_DAY[2], MD_BAOZANG_DAY[3], curday )
		SendToplistKeyValue2GL(mapId, playerId, BAOZANG_TOPLIST, curCount)	
	
	elseif nType == TULONG_TOPLIST then				-- 屠龙榜
		local lastday = GetQuestData( mapId, playerId, MD_TULONG_DAY[1], MD_TULONG_DAY[2], MD_TULONG_DAY[3] )
		local curCount = GetQuestData( mapId, playerId, MD_TULONG_COUNT[1], MD_TULONG_COUNT[2], MD_TULONG_COUNT[3] )
		local curday = GetWeekFirstDay()
		if lastday ~= curday then
			curCount = 0
		end
		curCount = nValue
		SetQuestData( mapId, playerId, MD_TULONG_COUNT[1], MD_TULONG_COUNT[2], MD_TULONG_COUNT[3], curCount )
		SetQuestData( mapId, playerId, MD_TULONG_DAY[1], MD_TULONG_DAY[2], MD_TULONG_DAY[3], curday )
		SendToplistKeyValue2GL(mapId, playerId, TULONG_TOPLIST, curCount)		
	end
end


---------------------------------------------------------------------------------------------------
--检查杀人数
---------------------------------------------------------------------------------------------------
function x888888_OnCheckKillCount(mapId,playerId)
	if IsObjValid(mapId,playerId)~=1 then
		return
	end	

	local day = GetQuestData( mapId, playerId, MD_KILLCOUNT_DAY[1], MD_KILLCOUNT_DAY[2], MD_KILLCOUNT_DAY[3] )
	local curday = GetWeekFirstDay()
	if day ~= curday then
		SetKillCount( mapId, playerId, 0 )
		SetQuestData( mapId, playerId, MD_KILLCOUNT_DAY[1], MD_KILLCOUNT_DAY[2], MD_KILLCOUNT_DAY[3], curday )
	end
end


---------------------------------------------------------------------------------------------------
--检查pvp2v2等级
---------------------------------------------------------------------------------------------------
function x888888_OnCheckpvp2v2Level(mapId,playerId)
	if IsObjValid(mapId,playerId)~=1 then
		return
	end	
	
	local day = GetQuestData( mapId, playerId, MD_PVP2V2_LEVEL_DAY[1], MD_PVP2V2_LEVEL_DAY[2], MD_PVP2V2_LEVEL_DAY[3] )
	local curday = GetWeekFirstDay()
	if day ~= curday then
		local value = GetPVP2V2Level(mapId,playerId)
		SubPVP2V2Level(mapId,playerId,value)
		AddPVP2V2Level(mapId,playerId,500)
		SetQuestData( mapId, playerId, MD_PVP2V2_LEVEL_DAY[1], MD_PVP2V2_LEVEL_DAY[2], MD_PVP2V2_LEVEL_DAY[3], curday )
	end	
end

---------------------------------------------------------------------------------------------------
--切换日期时操作
---------------------------------------------------------------------------------------------------
function x888888_OnSwitchDayCheck(mapId,playerId)
	
	if IsObjValid(mapId,playerId)~=1 then
		return
	end		

	if GetWeek() == 1 then
		x888888_OnCheckKillCount(mapId,playerId)
		x888888_OnCheckpvp2v2Level(mapId,playerId)
		
		local nWeekIndex = GetWeekIndex() --since 2010-01-25
		local nTitleIndex = mod(nWeekIndex,16)
		if nTitleIndex == 0 then
			nTitleIndex = 16
		end
		nTitleIndex = nTitleIndex -1	--上周的
		if nTitleIndex == 0 then
			nTitleIndex = 16
		end

		if mapId == 41 then
			UpdateToplist(mapId, playerId, x888888_g_TopList[nTitleIndex], 0, 20)
		end
	end
end
---------------------------------------------------------------------------------------------------
--功勋改变
function x888888_OnExploitChanged(mapId,playerId, exploit)
	
	if IsObjValid(mapId,playerId)~=1 then
		return
	end		

	local playerCountry =GetCurCountry(mapId,playerId)
	
	if playerCountry == 0 then
		-- 楼兰王国
		CallScriptFunction( 260002,"OnExploitChanged",mapId, playerId, exploit)
		CallScriptFunction( 260003,"OnExploitChanged",mapId, playerId, exploit)
		CallScriptFunction( 260004,"OnExploitChanged",mapId, playerId, exploit)
		CallScriptFunction( 260005,"OnExploitChanged",mapId, playerId, exploit)
	elseif playerCountry == 1 then
		-- 天山王国
		CallScriptFunction( 260006,"OnExploitChanged",mapId, playerId, exploit)
		CallScriptFunction( 260007,"OnExploitChanged",mapId, playerId, exploit)
		CallScriptFunction( 260008,"OnExploitChanged",mapId, playerId, exploit)
		CallScriptFunction( 260009,"OnExploitChanged",mapId, playerId, exploit)
	elseif playerCountry == 2 then
		-- 昆仑王国
		CallScriptFunction( 260010,"OnExploitChanged",mapId, playerId, exploit)
		CallScriptFunction( 260011,"OnExploitChanged",mapId, playerId, exploit)
		CallScriptFunction( 260012,"OnExploitChanged",mapId, playerId, exploit)
		CallScriptFunction( 260013,"OnExploitChanged",mapId, playerId, exploit)
	elseif playerCountry == 3 then
		-- 敦煌王国
		CallScriptFunction( 260014,"OnExploitChanged",mapId, playerId, exploit)
		CallScriptFunction( 260015,"OnExploitChanged",mapId, playerId, exploit)
		CallScriptFunction( 260016,"OnExploitChanged",mapId, playerId, exploit)
		CallScriptFunction( 260017,"OnExploitChanged",mapId, playerId, exploit)
	end
end



---------------------------------------------------------------------------------------------------
--宠物抓取成功事件
---------------------------------------------------------------------------------------------------
function x888888_OnMapHorseCaptureSuccesss(mapId,playerId,horseName,reverse)
	
	if IsObjValid(mapId,playerId)~=1 then
		return
	end 
	
	if HasTeam(mapId,playerId) <= 0 then
		return
	end
	
	local msg = format("%s捕捉了#W%s",GetName(mapId,playerId),horseName)
	LuaThisScenceM2Team(mapId,msg,GetTeamId(mapId,playerId),0,1)
	
end

---------------------------------------------------------------------------------------------------
--显示帮会占领据点信息
---------------------------------------------------------------------------------------------------
function x888888_ShowGuildLairdInfo(mapId,playerId)

	--如果不是据点场景，过滤显示
	if x888888_IsLairdScene(mapId) ~= 1 then
		return
	end

	--以下操作仅为据点场景才显示相关信息	
	local nGuildId = GetSceneLairdGuildId(mapId)
	if nGuildId >= 0 then
		local strGuildName = GetGuildName(nGuildId)
		local strLairdMsg = format("您进入了%s帮会的领地%s",strGuildName,GetSceneInfo(mapId,"NAME"))
		local strPlayerName = GetName(mapId,playerId)
		LuaScenceM2Player(mapId,playerId,strLairdMsg,strPlayerName,5,1)
		LuaScenceM2Player(mapId,playerId,strLairdMsg,strPlayerName,2,1)
	end
	
end

---------------------------------------------------------------------------------------------------
--显示场景PK信息
---------------------------------------------------------------------------------------------------
function x888888_ShowMapPKInfo(mapId,playerId)
	
	--取得场景PK模式
	local _,nSecurityLevel = GetSceneRestrictiveMode(mapId,playerId,mapId) ;
	if nSecurityLevel == 1 then
		if mapId ~= 50 and mapId ~= 150 and mapId ~= 250 and mapId ~= 350 then
		Msg2Player( mapId, playerId, "请注意，您已经进入了允许玩家之间互相发起战斗的区域！", 4, 1)
	else
		Msg2Player( mapId, playerId, "请注意，您已经进入了和平区域！此区域不允许玩家之间互相发起战斗！", 4, 1)
	end
	else
		Msg2Player( mapId, playerId, "请注意，您已经进入了和平区域！此区域不允许玩家之间互相发起战斗！", 4, 1)
	end
	
end

---------------------------------------------------------------------------------------------------
--任务数据清除作业
---------------------------------------------------------------------------------------------------
function x888888_QuestDataClearTask(mapId,playerId)

	--MDVersion Flag==0
	local MDFlag0 = GetQuestData(mapId,playerId,MD_VERSION_FLAG_0[1],MD_VERSION_FLAG_0[2],MD_VERSION_FLAG_0[3])
	if MDFlag0 == 0 then
	
		--设置MD已经清除成功
		SetQuestData(mapId,playerId,MD_VERSION_FLAG_0[1],MD_VERSION_FLAG_0[2],MD_VERSION_FLAG_0[3],1)
	
		SetQuestData(mapId,playerId, 9, 0,31, 0)
		SetQuestData(mapId,playerId,13,14, 9, 0)
		SetQuestData(mapId,playerId,15,23, 9, 0)
		SetQuestData(mapId,playerId,27, 5,18, 0)
		
		SetQuestData(mapId,playerId,30, 0,32, 0)
		
		SetQuestData(mapId,playerId,42,13, 4, 0)
		SetQuestData(mapId,playerId,44,0,  5, 0)
		
		SetQuestData(mapId,playerId,50, 0,32, 0)
		
		SetQuestData(mapId,playerId,52,17, 9, 0)
		
		SetQuestData(mapId,playerId,53, 0,30, 0)
		
		SetQuestData(mapId,playerId,54,16, 8, 0)
		
		SetQuestData(mapId,playerId,55, 1, 2, 0)
		SetQuestData(mapId,playerId,55, 8, 2, 0)
		SetQuestData(mapId,playerId,55,16, 2, 0)
		SetQuestData(mapId,playerId,55,21, 2, 0)
		
		SetQuestData(mapId,playerId,57,28, 3, 0)
		
		SetQuestData(mapId,playerId,60,21, 9, 0)
		
		SetQuestData(mapId,playerId,61, 1,25, 0)
		
		SetQuestData(mapId,playerId,77,16,16, 0)
		
		SetQuestData(mapId,playerId,80, 0,24, 0)
	
		SetQuestData(mapId,playerId,198,16,16, 0)
		
		SetQuestData(mapId,playerId,201, 0,16, 0)
		
		SetQuestData(mapId,playerId,206,16,16, 0)
		
		SetQuestData(mapId,playerId,207, 0,16, 0)
		
		SetQuestData(mapId,playerId,208, 0,27, 0)
		
		SetQuestData(mapId,playerId,210,16,16, 0)
		
		SetQuestData(mapId,playerId,233, 0,32, 0)
		SetQuestData(mapId,playerId,234, 0,32, 0)
		SetQuestData(mapId,playerId,235, 0,32, 0)
		SetQuestData(mapId,playerId,236, 0,32, 0)
		SetQuestData(mapId,playerId,237, 0,32, 0)
		SetQuestData(mapId,playerId,238, 0,32, 0)
		
		
		
		--以下行为只在MD版本维护的时候处理,并且每个MD的维护处理内容不一
		--顺便清理铁人三项的BUF
		if IsHaveSpecificImpact(mapId,playerId,7605 ) == 1 then
			CancelSpecificImpact(mapId,playerId,7605)
		end
		
		if IsHaveSpecificImpact(mapId,playerId,7606 ) == 1 then
			CancelSpecificImpact(mapId,playerId,7606)
		end
		
		if IsHaveSpecificImpact(mapId,playerId,7607 ) == 1 then
			CancelSpecificImpact(mapId,playerId,7607)
		end
		
		if IsHaveSpecificImpact(mapId,playerId,7608 ) == 1 then
			CancelSpecificImpact(mapId,playerId,7608)
		end
		
		if IsHaveSpecificImpact(mapId,playerId,7609 ) == 1 then
			CancelSpecificImpact(mapId,playerId,7609)
		end
		
		if IsHaveSpecificImpact(mapId,playerId,7610 ) == 1 then
			CancelSpecificImpact(mapId,playerId,7610)
		end		
		
		if IsHaveSpecificImpact(mapId,playerId,7611 ) == 1 then
			CancelSpecificImpact(mapId,playerId,7611)
		end		

		if IsHaveSpecificImpact(mapId,playerId,7612 ) == 1 then
			CancelSpecificImpact(mapId,playerId,7612)
		end		

		if IsHaveSpecificImpact(mapId,playerId,7613 ) == 1 then
			CancelSpecificImpact(mapId,playerId,7613)
		end		

		if IsHaveSpecificImpact(mapId,playerId,7614 ) == 1 then
			CancelSpecificImpact(mapId,playerId,7614)
		end		

		if IsHaveSpecificImpact(mapId,playerId,7615 ) == 1 then
			CancelSpecificImpact(mapId,playerId,7615)
		end		

		if IsHaveSpecificImpact(mapId,playerId,7616 ) == 1 then
			CancelSpecificImpact(mapId,playerId,7616)
		end		

		if IsHaveSpecificImpact(mapId,playerId,7617 ) == 1 then
			CancelSpecificImpact(mapId,playerId,7617)
		end		

		if IsHaveSpecificImpact(mapId,playerId,7618 ) == 1 then
			CancelSpecificImpact(mapId,playerId,7618)
		end		

		if IsHaveSpecificImpact(mapId,playerId,7619 ) == 1 then
			CancelSpecificImpact(mapId,playerId,7619)
		end		

		if IsHaveSpecificImpact(mapId,playerId,7620 ) == 1 then
			CancelSpecificImpact(mapId,playerId,7620)
		end		

		if IsHaveSpecificImpact(mapId,playerId,7621 ) == 1 then
			CancelSpecificImpact(mapId,playerId,7621)
		end		

		if IsHaveSpecificImpact(mapId,playerId,7622 ) == 1 then
			CancelSpecificImpact(mapId,playerId,7622)
		end		
		
		if IsHaveSpecificImpact(mapId,playerId,7623 ) == 1 then
			CancelSpecificImpact(mapId,playerId,7623)
		end		

		if IsHaveSpecificImpact(mapId,playerId,7624 ) == 1 then
			CancelSpecificImpact(mapId,playerId,7624)
		end		

		if IsHaveSpecificImpact(mapId,playerId,7625 ) == 1 then
			CancelSpecificImpact(mapId,playerId,7625)
		end		

		if IsHaveSpecificImpact(mapId,playerId,7626 ) == 1 then
			CancelSpecificImpact(mapId,playerId,7626)
		end		

		if IsHaveSpecificImpact(mapId,playerId,7627 ) == 1 then
			CancelSpecificImpact(mapId,playerId,7627)
		end		

		if IsHaveSpecificImpact(mapId,playerId,7628 ) == 1 then
			CancelSpecificImpact(mapId,playerId,7628)
		end						

        --舞厅的变身BUFF处理
		CallScriptFunction( 300160, "ChangeBody", mapId, playerId, 0, 0 )
		--舞厅的离线托管处理
		if GetQuestData( mapId, playerId, MD_WUTING_OFFLINE_FLAG[ 1], MD_WUTING_OFFLINE_FLAG[ 2], MD_WUTING_OFFLINE_FLAG[ 3] ) == 1 then
			CallScriptFunction( 300178, "ProcMapPlayerNewConnectEnter", mapId, playerId)
        end
		--舞厅离线预约处理
   	    CallScriptFunction( 300179, "ProcMapPlayerNewConnectEnter", mapId, playerId)
   	    
   	    
   	    --为成2转档玩家自动激活王城，大都，边塞的传送 --程骏
   	    
   	    --当玩家小于20级 激活王城传送
		local level = GetLevel(mapId, playerId)
		if level < 20 and level >=10 then  
			if IsQuestHaveDone(mapId, playerId,1520   ) <= 0 then
				QuestCom(mapId, playerId, 1520 )
			end
		end
		 
		--当玩家大于20小于40，激活王城，边塞传送
		if level >=20 and level < 40 then
			if IsQuestHaveDone(mapId, playerId, 1520  ) <= 0 then
				QuestCom(mapId, playerId,1520  )
			end
			if IsQuestHaveDone(mapId, playerId, 1502  ) <= 0 then
		 		QuestCom(mapId, playerId, 1502 )
			end 
		end
		 
		--当玩家大于等于40级，激活王城，边塞，大都传送
		if level >=40 then   
			if IsQuestHaveDone(mapId, playerId, 1520  ) <= 0 then
				QuestCom(mapId, playerId, 1520 )
			end
			if IsQuestHaveDone(mapId, playerId,  1502 ) <= 0 then
				QuestCom(mapId, playerId,1502  )
			end
			if IsQuestHaveDone(mapId, playerId, 1522  ) <= 0 then
				QuestCom(mapId, playerId,1522  )
		 	end 
		end
		
		--添加江湖指南
		BeginAddItem(mapId)
		AddItem( mapId,12030214,1)
		EndAddItem(mapId,playerId)
		AddItemListToPlayer(mapId,playerId)		
	
		--添加老玩家引导任务
		local nCountry = GetCurCountry(mapId,playerId)
		local level = GetLevel(mapId,playerId)
		if level >= 30 then
			 	if 	nCountry == 0 then
			 			if IsHaveQuestNM( mapId, playerId, 4010 ) <= 0 then 
			 				AddQuestNM( mapId, playerId, 4010) 
			 				
			 			end
			 	elseif nCountry == 1 then 
			 			if IsHaveQuestNM( mapId, playerId, 4011 ) <= 0 then 
			 	    	AddQuestNM( mapId, playerId, 4011)                
			      end    
			  elseif nCountry == 2 then                                    
			   		if IsHaveQuestNM( mapId, playerId, 4012 ) <= 0 then      
			   	    AddQuestNM( mapId, playerId, 4012)                     
			      end   
			  elseif nCountry == 3 then                                    
			   		if IsHaveQuestNM( mapId, playerId, 4013 ) <= 0 then      
			   	    AddQuestNM( mapId, playerId, 4013)                     
			      end   	      
			 	  end 
	     end
	     --添加获得转职道具任务
		if level >= 60 then
			 	if 	nCountry == 0 then
			 			if IsHaveQuest( mapId, playerId, 4387 ) <= 0 then 
			 				AddQuest( mapId, playerId, 4387, 203813, 0, 0, 0,1)
			 				local misIndex0 = GetQuestIndexByID(mapId,playerId,4387)
	 						SetQuestByIndex(mapId,playerId,misIndex0,0,1)                                                  
	    				SetQuestByIndex(mapId,playerId,misIndex0,7,1)
			 			end
			 	elseif nCountry == 1 then 
			 			if IsHaveQuest( mapId, playerId, 4388 ) <= 0 then 
			 	    		AddQuest( mapId, playerId, 4388, 203814, 0, 0, 0,1)  
			 	    		local misIndex1 = GetQuestIndexByID(mapId,playerId,4388)
	 							SetQuestByIndex(mapId,playerId,misIndex1,0,1)                                                  
	    					SetQuestByIndex(mapId,playerId,misIndex1,7,1)
			 	    		           
			     		 end    
			  	elseif nCountry == 2 then                                    
			   			if IsHaveQuest( mapId, playerId, 4389 ) <= 0 then      
			   	    		AddQuest( mapId, playerId, 4389, 203815, 0, 0, 0,1)
			   	    		local misIndex2 = GetQuestIndexByID(mapId,playerId,4389)
	 								SetQuestByIndex(mapId,playerId,misIndex2,0,1)                                                  
	    						SetQuestByIndex(mapId,playerId,misIndex2,7,1)                   
			      		end   
			 	elseif nCountry == 3 then                                    
			   			if IsHaveQuest( mapId, playerId, 4390 ) <= 0 then      
			   	    		AddQuest( mapId, playerId, 4390, 203816, 0, 0, 0,1)
			   	    		local misIndex3 = GetQuestIndexByID(mapId,playerId,4390)
	 								SetQuestByIndex(mapId,playerId,misIndex3,0,1)                                                  
	    						SetQuestByIndex(mapId,playerId,misIndex3,7,1)                  
			      		end   	      
			 	end 
	     end	
		  
		local msg = format("x888888_QuestDataClearTask First Check, guid=%X", GetGUID(mapId,playerId))
		WriteLog(1,msg)
				
	end
	
	
	
	
	--MDVersion Flag==1
	local MDFlag1 = GetQuestData(mapId,playerId,MD_VERSION_FLAG_1[1],MD_VERSION_FLAG_1[2],MD_VERSION_FLAG_1[3])
	if MDFlag1 == 0 then
	
		--设置MD已经清除成功
		--SetQuestData(mapId,playerId,MD_VERSION_FLAG_1[1],MD_VERSION_FLAG_1[2],MD_VERSION_FLAG_1[3],1)
		
	end
end

---------------------------------------------------------------------------------------------------
--国务预约检查处理
---------------------------------------------------------------------------------------------------
function x888888_CheckCountryPrecontract( mapId, playerId, hour, minute, enable, lastDay, count)
    if hour < 0 or hour > 23 or minute < 0 or minute > 59 then
        return 0
    end

    local today = GetDayOfYear()
    if lastDay == today then
        if count >= COUNTRY_PRECONTRACT_MAXTIMES and enable ~= 0 then
            Msg2Player( mapId, playerId, "今天国务预约次数已达上限，请明天再来", 8, 3)
            return 0
        end
    else
        count = 0
    end

    -- 因为不能返回多个值给程序，所以把日期值扩大100倍再加上次数的和返回给程序处理
    today = today * 100

    return today + count
end

----------------------------------------------------------------------------------------------
--同步当前据点战场信息
----------------------------------------------------------------------------------------------		
function x888888_ProcPlayerSyncLairdInfo(sceneId, selfId)

	for i, item in x888888_g_PlayerSyncLairdInfo do
		if IsHaveQuest(sceneId, selfId, item[1]) > 0 then
			local country = GetCurCountry(sceneId, selfId)
			local nLairdCountry = GetSceneLairdCountryId(item[2])
			if nLairdCountry ~= country then
				DelQuest( sceneId, selfId, item[1])
				local msg = format("由于%s领地已经被敌国占领，您的%s任务无法继续完成，已放弃任务。",item[3],item[4])
				Msg2Player( sceneId, selfId, msg, 8, 3)
				Msg2Player( sceneId, selfId, msg, 8, 2)
			end
		end
	end
end


---------------------------------------------------------------------------------------------------
--拜师成功回调
---------------------------------------------------------------------------------------------------
function x888888_ProcMapOnAddMasterSucceed(mapId,playerId)
local country = GetCurCountry( mapId, playerId)
	if country == 0 then 
		if IsHaveQuest(mapId,playerId,4076 ) > 0 then
			local misIndex = GetQuestIndexByID(mapId,playerId,4076)                                                  
	    	SetQuestByIndex(mapId,playerId,misIndex,0,1)
	    	SetQuestByIndex(mapId,playerId,misIndex,7,1)
		end
	elseif country == 1 then
		if IsHaveQuest(mapId,playerId,4077 ) > 0 then
			local misIndex = GetQuestIndexByID(mapId,playerId,4077)                                                  
	    	SetQuestByIndex(mapId,playerId,misIndex,0,1)
	    	SetQuestByIndex(mapId,playerId,misIndex,7,1)
		end
	elseif country == 2 then
		if IsHaveQuest(mapId,playerId,4078 ) > 0 then
			local misIndex = GetQuestIndexByID(mapId,playerId,4078)                                                  
	    	SetQuestByIndex(mapId,playerId,misIndex,0,1)
	    	SetQuestByIndex(mapId,playerId,misIndex,7,1)
		end
	elseif country == 3 then
		if IsHaveQuest(mapId,playerId,4079 ) > 0 then
			local misIndex = GetQuestIndexByID(mapId,playerId,4079)                                                  
	    	SetQuestByIndex(mapId,playerId,misIndex,0,1)
	    	SetQuestByIndex(mapId,playerId,misIndex,7,1)
		end
	end
end

---------------------------------------------------------------------------------------------------
--收徒成功回调
---------------------------------------------------------------------------------------------------
function x888888_ProcMapOnAddPrenticeSucceed(mapId,playerId)
	local country = GetCurCountry( mapId, playerId)
	if country == 0 then 
		if IsHaveQuest(mapId,playerId,4042 ) > 0 then
			local misIndex = GetQuestIndexByID(mapId,playerId,4042)                                                  
	    	SetQuestByIndex(mapId,playerId,misIndex,0,1)
	    	SetQuestByIndex(mapId,playerId,misIndex,7,1)
		end
	elseif country == 1 then
		if IsHaveQuest(mapId,playerId,4043 ) > 0 then
			local misIndex = GetQuestIndexByID(mapId,playerId,4043)                                                  
	    	SetQuestByIndex(mapId,playerId,misIndex,0,1)
	    	SetQuestByIndex(mapId,playerId,misIndex,7,1)
		end
	elseif country == 2 then
		if IsHaveQuest(mapId,playerId,4044 ) > 0 then
			local misIndex = GetQuestIndexByID(mapId,playerId,4044)                                                  
	    	SetQuestByIndex(mapId,playerId,misIndex,0,1)
	    	SetQuestByIndex(mapId,playerId,misIndex,7,1)
		end
	elseif country == 3 then
		if IsHaveQuest(mapId,playerId,4045 ) > 0 then
			local misIndex = GetQuestIndexByID(mapId,playerId,4045)                                                  
	    	SetQuestByIndex(mapId,playerId,misIndex,0,1)
	    	SetQuestByIndex(mapId,playerId,misIndex,7,1)
		end
	end
end

---------------------------------------------------------------------------------------------------
--好友度增加时的回调
---------------------------------------------------------------------------------------------------
function x888888_ProcMapOnFriendPointAdd(mapId,playerId)
	local friend = IsHaveFriend_FriendPointMoreThenPara(mapId, playerId, 10)
	if friend > 0 then
    local country = GetCurCountry( mapId, playerId)
	if country == 0 then 
		if IsHaveQuest(mapId,playerId,4046 ) > 0 then
			local misIndex = GetQuestIndexByID(mapId,playerId,4046)                                                  
	    	SetQuestByIndex(mapId,playerId,misIndex,0,1)
	    	SetQuestByIndex(mapId,playerId,misIndex,7,1)
		end
	elseif country == 1 then
		if IsHaveQuest(mapId,playerId,4047 ) > 0 then
			local misIndex = GetQuestIndexByID(mapId,playerId,4047)                                                  
	    	SetQuestByIndex(mapId,playerId,misIndex,0,1)
	    	SetQuestByIndex(mapId,playerId,misIndex,7,1)
		end
	elseif country == 2 then
		if IsHaveQuest(mapId,playerId,4048 ) > 0 then
			local misIndex = GetQuestIndexByID(mapId,playerId,4048)                                                  
	    	SetQuestByIndex(mapId,playerId,misIndex,0,1)
	    	SetQuestByIndex(mapId,playerId,misIndex,7,1)
		end
	elseif country == 3 then
		if IsHaveQuest(mapId,playerId,4049 ) > 0 then
			local misIndex = GetQuestIndexByID(mapId,playerId,4049)                                                  
	    	SetQuestByIndex(mapId,playerId,misIndex,0,1)
	    	SetQuestByIndex(mapId,playerId,misIndex,7,1)
		end
	end
	end
end

---------------------------------------------------------------------------------------------------
--是否可以进行骑乘合成
---------------------------------------------------------------------------------------------------
function x888888_IsCanHorseCompose(mapId, playerId)

	local lastday = GetQuestData( mapId, playerId, MD_HORSE_COMPOSE_DATE[1], MD_HORSE_COMPOSE_DATE[2], MD_HORSE_COMPOSE_DATE[3] )
	local today = GetDayTime()
	if lastday ~= today then
		return 1
	end
	return 0
end

---------------------------------------------------------------------------------------------------
--设置骑乘合成日期MD
---------------------------------------------------------------------------------------------------
function x888888_SetHorseComposeDate(mapId, playerId)
	local today = GetDayTime()
	SetQuestData( mapId, playerId, MD_HORSE_COMPOSE_DATE[1], MD_HORSE_COMPOSE_DATE[2], MD_HORSE_COMPOSE_DATE[3], today )
	return 1
end

---------------------------------------------------------------------------------------------------
--获得从2009年1月1日到今天是第N周，以GLServer时间为准
---------------------------------------------------------------------------------------------------
function x888888_GetWorldWeek()
	--取得今天的日期
	local nCurrentTime = ( GetWorldCTime() + 8 * 3600) / 86400 - 4  --换算成天
	local nWeek = floor( nCurrentTime / 7)		 --换算成周,并取整

	return nWeek - 2034
end

---------------------------------------------------------------------------------------------------
--跨服场景使用物品许可检测 2010-10-20 by rj
---------------------------------------------------------------------------------------------------
function x888888_CheckMPVPBattleUseItem(sceneId, selfId, itemId)
		
	local sceneType = GetSceneType(sceneId)
	
	--分开报名及战场场景
	if sceneType == 7 then
	
		if x888888_GetBattleSceneTypeNM(sceneId) == MPVP2V2_BATTLE_SCRIPT then
		    for i, item in x888888_g_ForbidM2v2BattleUseItemList do
		        if item == itemId then
					Msg2Player(sceneId, selfId, "跨服双人战场场景不许使用该道具", 8, 3)
					return 0
		        end
		   	end
		end
	elseif sceneType == 8 then
	
	    for i, item in x888888_g_ForbidMSignupUseItemList do
	        if item == itemId then
				Msg2Player(sceneId, selfId, "跨服报名场景不许使用该道具", 8, 3)
				return 0
	        end
	   	end   			
	end
	
	return 1
end

function x888888_OnFindPlayerItemResult(sceneId, selfId, ret)
	--SetFindPlayerItemData(sceneId, selfId, 0)
	local bagIndex = -1
	for i = 0, 107 do
		local itemid = GetItemIDByIndexInBag(sceneId, selfId, i)
		if itemid == 12030043 and IsItemLocked(sceneId, selfId, i) > 0 then
			if GetItemParam( sceneId, selfId, i, 8, 2) == 1 then
				bagIndex = i
				SetItemParam( sceneId, selfId, i, 8, 2, 0)
				UnlockItem(sceneId, selfId, i)
				break
			end
		end
	end

	if ret > 0 and bagIndex ~= -1 then
		if DelItemByIndexInBag( sceneId, selfId, bagIndex, 1) > 0 then -- 12030043
			GamePlayScriptLog(sceneId, selfId, 1471)
		end
	end

    if ret == 2 then
     	Msg2Player(sceneId, selfId, "目标玩家在战场或副本中。", 8, 3)
		Msg2Player(sceneId, selfId, "目标玩家在战场或副本中。", 8, 2)
	end
end

function x888888_OnFindPlayerItem(sceneId, selfId)

	if HasTeam(sceneId, selfId) <= 0 then
		Msg2Player(sceneId, selfId, "你突然觉得一阵凉意，看来有人正在用#G千里镜#o观察你的行踪。", 8, 3)
		Msg2Player(sceneId, selfId, "你突然觉得一阵凉意，看来有人正在用#G千里镜#o观察你的行踪。", 8, 2)
	else
		local name = GetName(sceneId, selfId)
		Msg2Player(sceneId, selfId, format("#G%s#o似乎刚刚成为了#G千里镜#o观察的目标。", name), 1, 3)
		Msg2Player(sceneId, selfId, format("#G%s#o似乎刚刚成为了#G千里镜#o观察的目标。", name), 1, 2)
	end
end

---------------------------------------------------------------------------------------------------
--玩家与系统之间发生消费行为的时候统计信息
--nMoney:改变的金钱数目
--eCurrencyActType:引起金钱改变的操作类型
---------------------------------------------------------------------------------------------------
function x888888_OnPlayerMoneyChanged(sceneId, selfId, nMoney,eCurrencyActType)
	
	--国家实力评分系统
	if (	eCurrencyActType == eCurrencyAct_Wulongyin_mojun 			or --五龙印魔君
           	eCurrencyActType == eCurrencyAct_Baoxiang			        or --疯狂宝箱
            eCurrencyActType == eCurrencyAct_Mojun				        or --天降魔君
            eCurrencyActType == eCurrencyAct_Baolong			        or --暴龙大作战
			eCurrencyActType == eCurrencyAct_Wulongyin_wabao			  ) then
			
			local nCountryIdx = GetCurCountry(sceneId, selfId);
			
			local  nCurSysWeek  = GetWeekIndex();
			local  nCurWeek     = GetCountryParam(sceneId,nCountryIdx,CD_CURWEEK_PINGFEN_DATE)
			local  nLastWeek    = GetCountryParam(sceneId,nCountryIdx,CD_LASTWEEK_PINGFEN_DATE)
			
			--如果跨周了,数据平移
			if nCurWeek ~= nCurSysWeek then
					local  nCurSysWeek  = GetWeekIndex() 
					local curWeek  = GetCountryParam(sceneId,nCountryIdx,CD_CURWEEK_PINGFEN_DATE)
					local curMoney = GetCountryParam(sceneId,nCountryIdx,CD_CURWEEK_PINGFEN_MONEY)
					
					SetCountryParam(sceneId,nCountryIdx,CD_CURWEEK_PINGFEN_DATE,nCurSysWeek)
					SetCountryParam(sceneId,nCountryIdx,CD_CURWEEK_PINGFEN_MONEY,nMoney)
					
					SetCountryParam(sceneId,nCountryIdx,CD_LASTWEEK_PINGFEN_DATE,curWeek)
					SetCountryParam(sceneId,nCountryIdx,CD_LASTWEEK_PINGFEN_MONEY,curMoney)
			else--没有跨周,数据叠加
					local nOldMoney = GetCountryParam(sceneId,nCountryIdx,CD_CURWEEK_PINGFEN_MONEY)
					local nNewMoney = nOldMoney + nMoney
					SetCountryParam(sceneId,nCountryIdx,CD_CURWEEK_PINGFEN_MONEY,nNewMoney)
			end
			
			
			
	end
	
	
	
	--1 统计该玩家是否有帮会
	--2 获取本月记次的次数,如果还未计次，则初始化为0 SetGuildParam(sceneId,selfId,GD_GUILD_LASTWEEK_GUILD_MEMBER_MONEY,0)
	--					   如果已经计次，则累加 
	--3	如果跨月了,		   对本周的GD_GUILD_CURWEEK_GUILD_MEMBER_MONEY参数初始化
	
	--过滤各种eCurrencyActType，这里仅仅处理我感兴趣的交易类型【和系统发生交易的类型】
	--暂时只在程序中有选择的调用OnMoneyChanged,只在发生玩家金钱消费的时候触发
	--过滤optype
	if (eCurrencyActType ~= eCurrencyAct_PlayerShopExchangeOutcome 	    and
			eCurrencyActType ~= eCurrencyAct_BuyPlayerShopOutcome 		and 
			eCurrencyActType ~= eCurrencyAct_CreatePlayerShopOutcome    and
			eCurrencyActType ~= eCurrencyAct_PlayerShowTake				and
			eCurrencyActType ~= eCurrencyAct_ShopCost                   and
			eCurrencyActType ~= eCurrencyAct_ShopRepair                 and
			eCurrencyActType ~= eCurrencyAct_CallScriptCost             and
			eCurrencyActType ~= eCurrencyAct_GuildLevelUpCost			and
			eCurrencyActType ~= eCurrencyAct_ChallengeKingCost          and
			eCurrencyActType ~= eCurrencyAct_ApplyActAsKing             and
			eCurrencyActType ~= eCurrencyAct_DrillCost                  and
			eCurrencyActType ~= eCurrencyAct_EquipLevelUpCost			and
			eCurrencyActType ~= eCurrencyAct_EquipRemouldCost           and
			eCurrencyActType ~= eCurrencyAct_FoundEquipCost             and
			eCurrencyActType ~= eCurrencyAct_EquipInlayCost             and
			eCurrencyActType ~= eCurrencyAct_EquipBindCost				and
			eCurrencyActType ~= eCurrencyAct_EquipChangeCard			and
			eCurrencyActType ~= eCurrencyAct_HorseMating                and
			eCurrencyActType ~= eCurrencyAct_HorseFindingMating         and
			eCurrencyActType ~= eCurrencyAct_HorseRiseHappy				and		
			eCurrencyActType ~= eCurrencyAct_MarryCost                  and
			eCurrencyActType ~= eCurrencyAct_DivorceCost                and
			eCurrencyActType ~= eCurrencyAct_ChatCost                   and
			eCurrencyActType ~= eCurrencyAct_ProxyTrain                 and
			eCurrencyActType ~= eCurrencyAct_CashVendueCost             and
			eCurrencyActType ~= eCurrencyAct_CashShopBuyCost            and
			eCurrencyActType ~= eCurrencyAct_EquipColorChange           and
			eCurrencyActType ~= eCurrencyAct_EquipPurpleWashAttr        and
			eCurrencyActType ~= eCurrencyAct_EquipGemLevelUpCost        and
			eCurrencyActType ~= eCurrencyAct_EquipGemCompoundCost       and
			eCurrencyActType ~= eCurrencyAct_EquipGemTeardown           and
			eCurrencyActType ~= eCurrencyAct_EquipCopyCost              and
			eCurrencyActType ~= eCurrencyAct_ExchangeGoldOutcome        and
			eCurrencyActType ~= eCurrencyAct_CharGoldToStock            and
			eCurrencyActType ~= eCurrencyAct_StockAutoSaleCostGold      and
			eCurrencyActType ~= eCurrencyAct_EquipSwitch                and
			eCurrencyActType ~= eCurrencyAct_MentalBuyItem              and
			eCurrencyActType ~= eCurrencyAct_GuildSkillLevelUpCost      and
			eCurrencyActType ~= eCurrencyAct_BlueProduceCost            and
			eCurrencyActType ~= eCurrencyAct_ConstBindCost				and
			eCurrencyActType ~= eCurrencyAct_Relive						and	--死亡复活		 	
			eCurrencyActType ~= eCurrencyAct_NormalMission				and --任务消耗：押运,官府押运
			eCurrencyActType ~= eCurrencyAct_Xingbing_loulan	  	 	and --新兵速成 
			eCurrencyActType ~= eCurrencyAct_Xingbing_tianshan	   		and --新兵速成 
			eCurrencyActType ~= eCurrencyAct_Xingbing_kunlun			and --新兵速成 
			eCurrencyActType ~= eCurrencyAct_Xingbing_dunhuang	 		and --新兵速成 
			eCurrencyActType ~= eCurrencyAct_GuildSuCheng				and --帮会速成	
			eCurrencyActType ~= eCurrencyAct_Wulongyin_mojun	        and --五龙印
           	eCurrencyActType ~= eCurrencyAct_Wulongyin			        and --五龙印
            eCurrencyActType ~= eCurrencyAct_Wulongyin_huapi	        and --五龙印
            eCurrencyActType ~= eCurrencyAct_Wulongyin_qiannv	        and --五龙印
           	eCurrencyActType ~= eCurrencyAct_Baoxiang			        and --疯狂宝箱
            eCurrencyActType ~= eCurrencyAct_Mojun				        and --天降魔君
            eCurrencyActType ~= eCurrencyAct_Baolong			        and --暴龙大作战
            eCurrencyActType ~= eCurrencyAct_MarryCost					and --结婚		
			eCurrencyActType ~= eCurrencyAct_Hunyin						and --婚礼
			eCurrencyActType ~= eCurrencyAct_PresentWeddingRB			) then 
			return 0
	end

	
	local nGuildID = GetGuildID(sceneId,selfId)
	if nGuildID == -1 then
		return 0
	end
	
	--PrintNum(GD_GUILD_CURMONTH_GUILD_MEMBER_MONEY) --55
	--PrintNum(GD_GUILD_LASTMONTH_GUILD_MEMBER_MONEY) --54
	
	
	local year, curMonth,  day = GetYearMonthDay()
	curMonth = year*100 + curMonth
	local sysCurMonth = GetGuildParam(nGuildID, GD_GUILD_CURMONTH)
	if curMonth ~= sysCurMonth then --跨月了,数据平移
		local nCurMonth = GetGuildParam(nGuildID, GD_GUILD_CURMONTH)
		local nCurMoney = GetGuildParam(nGuildID,GD_GUILD_CURMONTH_GUILD_MEMBER_MONEY)			--这个就是最终的结果了	
		
		
		SetGuildParam(nGuildID,GD_GUILD_CURMONTH,curMonth)										--本月重新开始计算
		SetGuildParam(nGuildID,GD_GUILD_CURMONTH_GUILD_MEMBER_MONEY,nMoney)					

		
		SetGuildParam(nGuildID,GD_GUILD_LASTMONTH,nCurMonth)
		SetGuildParam(nGuildID,GD_GUILD_LASTMONTH_GUILD_MEMBER_MONEY,nCurMoney)			--设置上月的总金额
	else --没有跨月，数据叠加		
		local nOld =  GetGuildParam(nGuildID,GD_GUILD_CURMONTH_GUILD_MEMBER_MONEY)
		local nNew =  nOld + nMoney
		SetGuildParam(nGuildID,GD_GUILD_CURMONTH_GUILD_MEMBER_MONEY,nNew)
	end	
end

----------------------------------------------------------------------------------------------
--增加战场功绩
----------------------------------------------------------------------------------------------
function x888888_AddBattleHonour(sceneId, selfId, honour)
	
	--自身战场功绩获得上限公式配置
	local nSelfMaxHonour = 40000
	local nWeekMaxHonour = x888888_g_BattleHonourWeekMaxValue

	--计算额外增加战场功绩buf，双倍
	for i, item in x888888_g_ExaBattleHonourValueBufList do
		if IsHaveSpecificImpact(sceneId, selfId, item) > 0 then
			honour = honour * 2
	 		WriteLog(1, format("MP2BL:x888888_AddBattleHonour 1 SceneId=%d PlayerGUID=%u Param1=%u Param2=%u", 
	 			sceneId, GetGUID(sceneId, selfId), honour, item))
			break
		end
	end
	
	--计算额外增加战场功绩周上限比例buf，切记，增加完上限后不可大于 MD_BATTLEHONOUR_WEEKVALUE 位数值
	for i, item in x888888_g_ExaBattleHonourRatioBufList do
		if IsHaveSpecificImpact(sceneId, selfId, item) > 0 then
			nWeekMaxHonour = nWeekMaxHonour + nWeekMaxHonour * (x888888_g_ExaBattleHonourRatio / 100)
	 		WriteLog(1, format("MP2BL:x888888_AddBattleHonour 2 SceneId=%d PlayerGUID=%u Param1=%u Param2=%u", 
	 			sceneId, GetGUID(sceneId, selfId), nWeekMaxHonour, item))
			break
		end
	end
	
	--根据自身战场功绩上限来修正 honour
	local nCurSelfHonour = GetBattleHonour(sceneId, selfId)
	if nCurSelfHonour + honour > nSelfMaxHonour then
		honour = nSelfMaxHonour - nCurSelfHonour
		if honour == 0 then
			Msg2Player(sceneId, selfId, format("获得战场功绩已经到达角色上限%d点，无法再获得战场功绩", nSelfMaxHonour), 8, 3)
	 		WriteLog(1, format("MP2BL:x888888_AddBattleHonour 3 SceneId=%d PlayerGUID=%u", sceneId, GetGUID(sceneId, selfId)))
			return
		elseif honour < 0 then
			--Msg2Player(sceneId, selfId, "GM指令调低等级已使公式失效，取消本次战场功绩获得", 8, 3)
	 		WriteLog(1, format("MP2BL:x888888_AddBattleHonour 4 SceneId=%d PlayerGUID=%u Param1=%d", sceneId, GetGUID(sceneId, selfId), honour))
			return
		end
	end	
	
	--取得上次记录的周和点数
	local nLastWeek = GetQuestData(sceneId, selfId, MD_BATTLEHONOUR_WEEKDAY[1], MD_BATTLEHONOUR_WEEKDAY[2], MD_BATTLEHONOUR_WEEKDAY[3])
	local nCurWeekValue = GetQuestData(sceneId, selfId, MD_BATTLEHONOUR_WEEKVALUE[1], MD_BATTLEHONOUR_WEEKVALUE[2], MD_BATTLEHONOUR_WEEKVALUE[3])
	
	--取得当前周，如果当前周与上次记录的周不匹配，先清空数据
	local nCurWeekDay = GetWeekIndex() --since 2010-01-25
	if nLastWeek ~= nCurWeekDay then
		nCurWeekValue = 0
	end
	
	--计算 nCurWeekValue 是否到达上限，是则进行修正
	if nCurWeekValue + honour > nWeekMaxHonour then	
		honour = nWeekMaxHonour - nCurWeekValue
		nCurWeekValue = nWeekMaxHonour
		
		--必须小于等于判定，因为取消比例buf后很可能周最大值将比MD中记录的要小
		if honour <= 0 then
			Msg2Player(sceneId, selfId, format("获得战场功绩已经到达本周上限%d点，无法再获得战场功绩", nWeekMaxHonour), 8, 3)
	 		WriteLog(1, format("MP2BL:x888888_AddBattleHonour 5 SceneId=%d PlayerGUID=%u Param1=%d", sceneId, GetGUID(sceneId, selfId), honour))
			return
		end
	else
		nCurWeekValue = nCurWeekValue + honour
	end
	
	AddBattleHonour(sceneId, selfId, honour)
	WriteLog(1, format("MP2BL:x888888_AddBattleHonour 6 SceneId=%d PlayerGUID=%u Param1=%u", sceneId, GetGUID(sceneId, selfId), honour))
	 		
	SetQuestData(sceneId, selfId, MD_BATTLEHONOUR_WEEKVALUE[1], MD_BATTLEHONOUR_WEEKVALUE[2], MD_BATTLEHONOUR_WEEKVALUE[3], nCurWeekValue)
	SetQuestData(sceneId, selfId, MD_BATTLEHONOUR_WEEKDAY[1], MD_BATTLEHONOUR_WEEKDAY[2], MD_BATTLEHONOUR_WEEKDAY[3], nCurWeekDay)

	Msg2Player(sceneId, selfId, format("获得%u点战场功绩", honour), 8, 3)
	Msg2Player(sceneId, selfId, format("获得%u点战场功绩", honour), 8, 2)
end

----------------------------------------------------------------------------------------------
--添加及删除头顶称号时程序调用，type 0 删除 1 添加 2 过期删除
----------------------------------------------------------------------------------------------
function x888888_OnChangeSelfTitle(sceneId, selfId, titleId, type)

	WriteLog(1, format("x888888_OnChangeSelfTitle 1 SceneId=%d PlayerGUID=%u Param1=%d Param2=%d", sceneId, GetGUID(sceneId, selfId), titleId, type))
	
	--第一个应用，执行战场奖牌兑换称号升降级功能
	CallScriptFunction(303105, "OnChangeSelfTitle", sceneId, selfId, titleId, type)
end

---------------------------------------------------------------------------------------------------
--天赋专攻系数点数变化
---------------------------------------------------------------------------------------------------
function x888888_ProcMapOnCoefficientChanged(mapId,playerId)
	local isFirst = GetQuestData( mapId, playerId, MD_ZHUANGONG_COEFFICIENT[1], MD_ZHUANGONG_COEFFICIENT[2], MD_ZHUANGONG_COEFFICIENT[3] )
	if isFirst == 0 then
		--判断专精天赋引导任务是否完成
		if IsHaveQuestNM( mapId,playerId, x888888_g_MissionId_Zhuangong) == 1 then
			local misidx = GetQuestIndexByID(mapId,playerId,x888888_g_MissionId_Zhuangong)		
			SetQuestByIndex(mapId,playerId,misidx,0,1)
			SetQuestByIndex(mapId,playerId,misidx,7,1)
		end

		SetQuestData( mapId, playerId, MD_ZHUANGONG_COEFFICIENT[1], MD_ZHUANGONG_COEFFICIENT[2], MD_ZHUANGONG_COEFFICIENT[3], 1 )
	end

	SetQuestData( mapId, playerId, MD_ZHUANGONG_COEFFICIENT_RESET[1], MD_ZHUANGONG_COEFFICIENT_RESET[2], MD_ZHUANGONG_COEFFICIENT_RESET[3], 1 )

end

---------------------------------------------------------------------------------------------------
--天赋专攻系数点数重置
---------------------------------------------------------------------------------------------------
function x888888_ProcMapOnCoefficientReset(mapId,playerId)
	local ret = 0
	if IsEnoughMoney(mapId, playerId, x888888_g_Zhuangong_Coefficient) == 1 then
		local tmpRet, type = SpendMoney(mapId, playerId, x888888_g_Zhuangong_Coefficient)
		if tmpRet > 0 then
			ret = 1
			local sillerMode
			if type == 0 then
				sillerMode = "现银"
			else
				sillerMode = "银卡"
			end
			local Readme = format("重置专攻分配点数，扣除#R%s#{_MONEY%d}。", sillerMode, x888888_g_Zhuangong_Coefficient)
			Msg2Player(mapId,playerId,Readme,8,3)
			Msg2Player(mapId,playerId,Readme,8,2)
			SetQuestData( mapId, playerId, MD_ZHUANGONG_COEFFICIENT_RESET[1], MD_ZHUANGONG_COEFFICIENT_RESET[2], MD_ZHUANGONG_COEFFICIENT_RESET[3], 0 )
		end
	end

	if ret ~= 1 then
		local money = x888888_g_Zhuangong_Coefficient / 1000
		local Readme = "很抱歉，重置专攻分配点数需要"..money.."两"
		Msg2Player(mapId,playerId,Readme,8,3)
		Msg2Player(mapId,playerId,Readme,8,2)
	end

	return ret

end

---------------------------------------------------------------------------------------------------
--天赋专攻系数点数分配检查
---------------------------------------------------------------------------------------------------
function x888888_ProcMapOnCoefficientConditionCheck(mapId,playerId)
	local ret = GetQuestData( mapId, playerId, MD_ZHUANGONG_COEFFICIENT_RESET[1], MD_ZHUANGONG_COEFFICIENT_RESET[2], MD_ZHUANGONG_COEFFICIENT_RESET[3] )
	
	if ret == 0 then
		return 1
	else
		return 0
	end
end


