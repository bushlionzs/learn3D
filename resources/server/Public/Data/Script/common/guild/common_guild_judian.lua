
x300918_g_scriptId                      = 300918
x300918_g_TotalBattleTime               = 60 * 30     	--战争持续时间1800秒        19:00-19:30

--玩法类型
x300918_g_SceneName                     = { 
											{Name="yewai_caizhoucheng/yewai_caizhoucheng.scn",				Script=300918,MapId= 6,Toggle=1,Buf = {-1,9420,9421,9422,9423}},
											{Name="yewai_suiyecheng/yewai_suiyecheng.scn",					Script=300918,MapId= 9,Toggle=1,Buf = {-1,9400,9401,9402,9403}},
											{Name="yewai_bageda/yewai_bageda.scn",							Script=300918,MapId=13,Toggle=1,Buf = {-1,9416,9417,9418,9419}},
											{Name="yewai_jifugongguo/yewai_jifugongguo.scn",				Script=300918,MapId=18,Toggle=1,Buf = {-1,9412,9413,9414,9415}},
											{Name="yewai_shenshengluomadiguo/yewai_shenshengluomadiguo.scn",Script=300918,MapId=21,Toggle=1,Buf = {-1,9428,9429,9430,9431}},
											{Name="yewai_yelusaleng/yewai_yelusaleng.scn",					Script=300918,MapId=24,Toggle=1,Buf = {-1,-1,-1,-1,-1}},
											{Name="test/test.scn",											Script=300918,MapId=27,Toggle=0,Buf = {-1,-1,-1,-1,-1}},
											{Name="test/test.scn",											Script=300918,MapId=31,Toggle=0,Buf = {-1,-1,-1,-1,-1}},
											{Name="test/test.scn",											Script=300918,MapId=34,Toggle=0,Buf = {-1,-1,-1,-1,-1}},
										  }
x300918_g_BattleType					= 2

x300918_g_Laird_Signup                  = 300     --报名
x300918_g_Laird_WaitBattle              = 301     --报名结束，等待领主战场
x300918_g_Laird_BeginBattle             = 302     --开始领主战场
x300918_g_Laird_EndBattle               = 303     --结束领主战场

--奖励相关
x300918_g_MaxScore                     = 49	     --从0开始计数
x300918_g_BonusTips                    = "#G您获得了#R%d#G点经验,#R%d#G点帮会贡献,#R%d#G帮会经验!" --奖励提示
x300918_g_BonusTips1                   = "您获得了奖励" --奖励提示


--经验奖励
x300918_g_WinPrise                     = 1000*0.5*20              --获胜方经验奖励系数，只与等级有关
x300918_g_LosePrise                    = 1000*0.1*20              --失败方经验奖励系数，只与等级有关
x300918_g_DeucePrise                   = 1000*0.3*20              --战平时经验奖励系数，只与等级有关

--帮贡奖励
x300918_g_WinBangGong                  = 25
x300918_g_DeuceBangGong                = 20

--帮会经验
x300918_g_WinBangExp                   = 2
x300918_g_LoseBangExp                  = 2
x300918_g_DeuceBangExp                 = 2

x300918_g_Guild_Camp_A                 = 5
x300918_g_Guild_Camp_B                 = 6

x300918_g_Leader_Index                 = 5

x300918_g_Kick_Down                    = 8


--相关状态控制
x300918_g_BattleState		   		   = {}
x300918_g_BattleEnterFlag	   		   = {}
x300918_g_GuildA					   = {}
x300918_g_GuildB					   = {}
x300918_g_CountryA					   = {}
x300918_g_CountryB					   = {}
x300918_g_LairdMapID				   = {}
x300918_g_HasLaird					   = {}
x300918_g_CountDownState			   = {}
x300918_g_CountDownTime				   = {}
x300918_g_CountTime				       = {}
x300918_g_GuildAidA					   = {}
x300918_g_GuildAidB					   = {}


--据点相关信息
x300918_g_LairdSceneInfo					= {	--战场地图信息
												{NpcGUID=123839,LairdScene=6, LairdSceneName="蔡州城  （中原）",  	Level=45, Flag0=500,Flag1=15000}, 
												{NpcGUID=123839,LairdScene=9, LairdSceneName="碎叶城  （中亚）",    Level=60, Flag0=501,Flag1=15001},
												{NpcGUID=123839,LairdScene=13,LairdSceneName="巴格达  （西亚）",	Level=70, Flag0=502,Flag1=15002},
												{NpcGUID=123839,LairdScene=18,LairdSceneName="基辅公国（斯拉夫）",  Level=80, Flag0=503,Flag1=15003},
												{NpcGUID=123839,LairdScene=21,LairdSceneName="罗马帝国（东欧）",    Level=90, Flag0=504,Flag1=15004},
												{NpcGUID=123839,LairdScene=24,LairdSceneName="耶路撒冷（阿拉伯）",	Level=100,Flag0=505,Flag1=15005},
												{NpcGUID=123839,LairdScene=27,LairdSceneName="福冈    （东瀛）",    Level=110,Flag0=506,Flag1=15006},
												{NpcGUID=123839,LairdScene=31,LairdSceneName="缅甸    （百夷）",  	Level=120,Flag0=507,Flag1=15007},
												{NpcGUID=123839,LairdScene=34,LairdSceneName="爪哇岛  （南洋）",    Level=130,Flag0=508,Flag1=15008},
												
												{NpcGUID=126139,LairdScene=6, LairdSceneName="蔡州城  （中原）",    Level=45, Flag0=1500,Flag1=25000}, 
												{NpcGUID=126139,LairdScene=9, LairdSceneName="碎叶城  （中亚）",	Level=60, Flag0=1501,Flag1=25001},
												{NpcGUID=126139,LairdScene=13,LairdSceneName="巴格达  （西亚）",	Level=70, Flag0=1502,Flag1=25002},
												{NpcGUID=126139,LairdScene=18,LairdSceneName="基辅公国（斯拉夫）",  Level=80, Flag0=1503,Flag1=22003},
												{NpcGUID=126139,LairdScene=21,LairdSceneName="罗马帝国（东欧）",    Level=90, Flag0=1504,Flag1=25004},
												{NpcGUID=126139,LairdScene=24,LairdSceneName="耶路撒冷（阿拉伯）",  Level=100,Flag0=1505,Flag1=25005},
												{NpcGUID=126139,LairdScene=27,LairdSceneName="福冈    （东瀛）",    Level=110,Flag0=1506,Flag1=25006},
												{NpcGUID=126139,LairdScene=31,LairdSceneName="缅甸    （百夷）",    Level=120,Flag0=1507,Flag1=25007},
												{NpcGUID=126139,LairdScene=34,LairdSceneName="爪哇岛  （南洋）",    Level=130,Flag0=1508,Flag1=25008},
												                                                                              
												{NpcGUID=129741,LairdScene=6, LairdSceneName="蔡州城  （中原）",   Level=45, Flag0=2500,Flag1=35000}, 
												{NpcGUID=129741,LairdScene=9, LairdSceneName="碎叶城  （中亚）",  Level=60, Flag0=2501,Flag1=35001},
												{NpcGUID=129741,LairdScene=13,LairdSceneName="巴格达  （西亚）",	Level=70, Flag0=2502,Flag1=35002},
												{NpcGUID=129741,LairdScene=18,LairdSceneName="基辅公国（斯拉夫）", Level=80, Flag0=2503,Flag1=33003},
												{NpcGUID=129741,LairdScene=21,LairdSceneName="罗马帝国（东欧）",   Level=90, Flag0=2504,Flag1=35004},
												{NpcGUID=129741,LairdScene=24,LairdSceneName="耶路撒冷（阿拉伯）", Level=100,Flag0=2505,Flag1=35005},
												{NpcGUID=129741,LairdScene=27,LairdSceneName="福冈    （东瀛）",   Level=110,Flag0=2506,Flag1=35006},
												{NpcGUID=129741,LairdScene=31,LairdSceneName="缅甸    （百夷）",   Level=120,Flag0=2507,Flag1=35007},
												{NpcGUID=129741,LairdScene=34,LairdSceneName="爪哇岛  （南洋）",   Level=130,Flag0=2508,Flag1=35008},
												                                                                              
												{NpcGUID=132165,LairdScene=6, LairdSceneName="蔡州城  （中原）",    Level=45, Flag0=3500,Flag1=45000}, 
												{NpcGUID=132165,LairdScene=9, LairdSceneName="碎叶城  （中亚）",  Level=60, Flag0=3501,Flag1=45001},
												{NpcGUID=132165,LairdScene=13,LairdSceneName="巴格达  （西亚）",	Level=70, Flag0=3502,Flag1=45002},
												{NpcGUID=132165,LairdScene=18,LairdSceneName="基辅公国（斯拉夫）",  Level=80, Flag0=3503,Flag1=44003},
												{NpcGUID=132165,LairdScene=21,LairdSceneName="罗马帝国（东欧）",    Level=90, Flag0=3504,Flag1=45004},
												{NpcGUID=132165,LairdScene=24,LairdSceneName="耶路撒冷（阿拉伯）",  Level=100,Flag0=3505,Flag1=45005},
												{NpcGUID=132165,LairdScene=27,LairdSceneName="福冈    （东瀛）",    Level=110,Flag0=3506,Flag1=45006},
												{NpcGUID=132165,LairdScene=31,LairdSceneName="缅甸    （百夷）",    Level=120,Flag0=3507,Flag1=45007},
												{NpcGUID=132165,LairdScene=34,LairdSceneName="爪哇岛  （南洋）",    Level=130,Flag0=3508,Flag1=45008},
											   }                                                                              
											   
											   
--动态阻挡处理,第一个门
x300918_g_TempImpassable_Door1			=	{ 																		--战场大门范围
												{ Left = 19,Top = 89,Right =  232,Bottom = 168 },
											}
											
x300918_g_TempImpassable_Door1_Effect	=   { 32, 33 }																--战场大门

--动态阻挡处理,双方的第二个门,需要分开处理
x300918_g_TempImpassable_Door2			=	{																		--两个后门的范围
												{Left =  46,Top = 60,Right =  54,Bottom = 68},
												{Left = 196,Top = 191,Right = 205,Bottom = 199},
											}
											
x300918_g_TempImpassable_Door2_Effect	=   { 34, 35 }																--两个门要播的特效
x300918_g_TempImpassable_Door2_State	=	{} 																		--0表示不播特效,1表示播特效

--生长点相关处理
x300918_g_DoorGrowPointA				=	730																		--A方生长点
x300918_g_DoorGrowPointB				=	731																		--B方生长点

x300918_g_DoorGrowPointA_LairdState		=	{}																		--占领时间逻辑,当被敌方占领时需要给一个占领倒计时状态以及占领倒计时处理,己方抢夺不需要此逻辑(暂定)
x300918_g_DoorGrowPointB_LairdState		=	{}																		--占领时间逻辑,当被敌方占领时需要给一个占领倒计时状态以及占领倒计时处理,己方抢夺不需要此逻辑(暂定)

--BOSS相关
x300918_g_BossA							=	{}																		--A方Boss列表
x300918_g_BossB							=	{}																		--B方Boss列表

--计分相关
x300918_g_ScoreA						=	{}																		--A方计分
x300918_g_ScoreB						=	{}																		--B方计分
x300918_g_IntervalScoreA				=	{}																		--A方内部计分
x300918_g_IntervalScoreB				=	{}																		--B方内部计分

--外援数据保存
x300918_g_PlayerAidList					=	{}																		--外援列表  仅在报名场景使用的外援数据

----------------------------------------------------------------------------------------------
--初始化数外援数据列表
----------------------------------------------------------------------------------------------	
function x300918_InitPlayerAidList(sceneId)
	
	x300918_g_PlayerAidList[sceneId]		= {
												[6]  = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,  -1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
												[9]  = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,  -1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
												[13] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,  -1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
												[18] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,  -1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
												[21] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,  -1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
												[24] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,  -1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
												[27] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,  -1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
												[31] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,  -1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
												[34] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,  -1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
											  }	
end

----------------------------------------------------------------------------------------------
--重置指定外援数据A
----------------------------------------------------------------------------------------------	
function x300918_ResetPlayerAidListAByCustom(sceneId,nLairdMapId )
	
	if nLairdMapId ~= 6  and nLairdMapId ~= 9  and nLairdMapId ~= 13 and 
	   nLairdMapId ~= 18 and nLairdMapId ~= 21 and nLairdMapId ~= 24 and 
	   nLairdMapId ~= 27 and nLairdMapId ~= 31 and nLairdMapId ~= 34 then
		return
	end 

	for i = 1,10 do
		x300918_g_PlayerAidList[sceneId][nLairdMapId][i] = -1	
	end
end

----------------------------------------------------------------------------------------------
--重置指定外援数据B
----------------------------------------------------------------------------------------------	
function x300918_ResetPlayerAidListBByCustom(sceneId,nLairdMapId )
	
	if nLairdMapId ~= 6  and nLairdMapId ~= 9  and nLairdMapId ~= 13 and 
	   nLairdMapId ~= 18 and nLairdMapId ~= 21 and nLairdMapId ~= 24 and 
	   nLairdMapId ~= 27 and nLairdMapId ~= 31 and nLairdMapId ~= 34 then
		return
	end 

	for i = 11,20 do
		x300918_g_PlayerAidList[sceneId][nLairdMapId][i] = -1	
	end
end

----------------------------------------------------------------------------------------------
--添加指定战场的外援A
----------------------------------------------------------------------------------------------	
function x300918_AddPlayerAidAByCustom(sceneId,nLairdMapid,GUID)
	
	if nLairdMapId ~= 6  and nLairdMapId ~= 9  and nLairdMapId ~= 13 and 
	   nLairdMapId ~= 18 and nLairdMapId ~= 21 and nLairdMapId ~= 24 and 
	   nLairdMapId ~= 27 and nLairdMapId ~= 31 and nLairdMapId ~= 34 then
		return
	end 

	for i = 1,10 do
		if x300918_g_PlayerAidList[sceneId][nLairdMapId][i] == -1 then
			x300918_g_PlayerAidList[sceneId][nLairdMapId][i] = GUID
			return
		end
	end
end

----------------------------------------------------------------------------------------------
--添加指定战场的外援B
----------------------------------------------------------------------------------------------	
function x300918_AddPlayerAidBByCustom(sceneId,nLairdMapid,GUID)
	
	if nLairdMapId ~= 6  and nLairdMapId ~= 9  and nLairdMapId ~= 13 and 
	   nLairdMapId ~= 18 and nLairdMapId ~= 21 and nLairdMapId ~= 24 and 
	   nLairdMapId ~= 27 and nLairdMapId ~= 31 and nLairdMapId ~= 34 then
		return
	end 

	for i = 11,20 do
		if x300918_g_PlayerAidList[sceneId][nLairdMapId][i] == -1 then
			x300918_g_PlayerAidList[sceneId][nLairdMapId][i] = GUID
			return
		end
	end
end

----------------------------------------------------------------------------------------------
--移除指定的外援
----------------------------------------------------------------------------------------------	
function x300918_RemovePlayerAidByCustom(sceneId,nLairdMapId,GUID)
	
	if nLairdMapId ~= 6  and nLairdMapId ~= 9  and nLairdMapId ~= 13 and 
	   nLairdMapId ~= 18 and nLairdMapId ~= 21 and nLairdMapId ~= 24 and 
	   nLairdMapId ~= 27 and nLairdMapId ~= 31 and nLairdMapId ~= 34 then
		return
	end 
	
	for i,item in x300918_g_PlayerAidList[sceneId][nLairdMapId] do
		if item == GUID then
			item = -1
			return
		end
	end
end

----------------------------------------------------------------------------------------------
--检查玩家是否在外援列表中
----------------------------------------------------------------------------------------------	
function x300918_IsPlayerInPlayerAidList(sceneId,selfId)

	local nGUID = GetGUID(sceneId,selfId)
	for i,PlayerAidList in x300918_g_PlayerAidList[sceneId] do
		for j,PlayerAid in PlayerAidList do
			if PlayerAid == nGUID then
				return 1
			end
		end
	end

	return 0
end

----------------------------------------------------------------------------------------------
--同外外援数据
----------------------------------------------------------------------------------------------
function x300918_ProcPlayerAidSyncLw(sceneId,nLairdMapId,nCampFlag,nGUID1,nGUID2,nGUID3,nGUID4,nGUID5 )
	
	if nLairdMapId ~= 6  and nLairdMapId ~= 9  and nLairdMapId ~= 13 and 
	   nLairdMapId ~= 18 and nLairdMapId ~= 21 and nLairdMapId ~= 24 and 
	   nLairdMapId ~= 27 and nLairdMapId ~= 31 and nLairdMapId ~= 34 then
		return
	end 
	
	if nCampFlag == 0 then
		
		x300918_g_PlayerAidList[sceneId][nLairdMapId][1] = nGUID1
		x300918_g_PlayerAidList[sceneId][nLairdMapId][2] = nGUID2
		x300918_g_PlayerAidList[sceneId][nLairdMapId][3] = nGUID3
		x300918_g_PlayerAidList[sceneId][nLairdMapId][4] = nGUID4
		x300918_g_PlayerAidList[sceneId][nLairdMapId][5] = nGUID5
	else
		
		x300918_g_PlayerAidList[sceneId][nLairdMapId][11] = nGUID1
		x300918_g_PlayerAidList[sceneId][nLairdMapId][12] = nGUID2
		x300918_g_PlayerAidList[sceneId][nLairdMapId][13] = nGUID3
		x300918_g_PlayerAidList[sceneId][nLairdMapId][14] = nGUID4
		x300918_g_PlayerAidList[sceneId][nLairdMapId][15] = nGUID5
		
	end
	
end

function x300918_ProcPlayerAidSyncHi(sceneId,nLairdMapId,nCampFlag,nGUID6,nGUID7,nGUID8,nGUID9,nGUID10 )
	
	if nLairdMapId ~= 6  and nLairdMapId ~= 9  and nLairdMapId ~= 13 and 
	   nLairdMapId ~= 18 and nLairdMapId ~= 21 and nLairdMapId ~= 24 and 
	   nLairdMapId ~= 27 and nLairdMapId ~= 31 and nLairdMapId ~= 34 then
		return
	end 
	
	if nCampFlag == 0 then
		
		x300918_g_PlayerAidList[sceneId][nLairdMapId][6]  = nGUID6
		x300918_g_PlayerAidList[sceneId][nLairdMapId][7]  = nGUID7
		x300918_g_PlayerAidList[sceneId][nLairdMapId][8]  = nGUID8
		x300918_g_PlayerAidList[sceneId][nLairdMapId][9]  = nGUID9
		x300918_g_PlayerAidList[sceneId][nLairdMapId][10] = nGUID10
	else
		
		x300918_g_PlayerAidList[sceneId][nLairdMapId][16] = nGUID6
		x300918_g_PlayerAidList[sceneId][nLairdMapId][17] = nGUID7
		x300918_g_PlayerAidList[sceneId][nLairdMapId][18] = nGUID8
		x300918_g_PlayerAidList[sceneId][nLairdMapId][19] = nGUID9
		x300918_g_PlayerAidList[sceneId][nLairdMapId][20] = nGUID10
		
	end
	
end

----------------------------------------------------------------------------------------------
--场景初始化处理
----------------------------------------------------------------------------------------------	
function x300918_OnMapInit(sceneId)
	
	--相关状态控制
	x300918_g_BattleState[sceneId]				   	= -1
	x300918_g_BattleEnterFlag[sceneId]			   	= 0
	x300918_g_GuildA[sceneId]					   	= -1
	x300918_g_GuildB[sceneId]					   	= -1
	x300918_g_CountryA[sceneId]					   	= -1
	x300918_g_CountryB[sceneId]					   	= -1
	x300918_g_LairdMapID[sceneId]				   	= -1
	x300918_g_HasLaird[sceneId]					   	= 0
	x300918_g_CountDownState[sceneId]			   	= -1
	x300918_g_CountDownTime[sceneId]			   	= -1
	x300918_g_CountTime[sceneId]				   	= -1
	
	x300918_g_GuildAidA[sceneId]					= {}
	x300918_g_GuildAidB[sceneId]					= {}
	
	x300918_g_TempImpassable_Door2_State[sceneId]	= {  0,  0 } 																--0表示不播特效,1表示播特效
	
	x300918_g_DoorGrowPointA_LairdState[sceneId]	= { LairdCountDownState = 0,LairdCountDownTime = -1,LairdCamp = -1 }		--占领时间逻辑,当被敌方占领时需要给一个占领倒计时状态以及占领倒计时处理,己方抢夺不需要此逻辑(暂定)
	x300918_g_DoorGrowPointB_LairdState[sceneId]	= { LairdCountDownState = 0,LairdCountDownTime = -1,LairdCamp = -1 }		--占领时间逻辑,当被敌方占领时需要给一个占领倒计时状态以及占领倒计时处理,己方抢夺不需要此逻辑(暂定)

	
	--BOSS相关
	x300918_g_BossA[sceneId]						=	nil																		--A方Boss列表
	x300918_g_BossB[sceneId]						=	nil																		--B方Boss列表
	
	--计分相关
	x300918_g_ScoreA[sceneId]						=	0																		--A方计分
	x300918_g_ScoreB[sceneId]						=	0																		--B方计分
	x300918_g_IntervalScoreA[sceneId]				=	0																		--A方内部计分
	x300918_g_IntervalScoreB[sceneId]				=	0																		--B方内部计分
	
	--初始化外援数据
	x300918_InitPlayerAidList(sceneId)
	
end

----------------------------------------------------------------------------------------------
--同步当前据点战场信息
----------------------------------------------------------------------------------------------		
function x300918_ProcSyncLairdInfo(sceneId,nGuildId,nCountryId)
	
	local nObjId = 1
	if IsObjValid(sceneId,nObjId) ~=1 then
		return
	end
	
	if nCountryId < 0 or nCountryId > 3 then
		return
	end
	
	local nCamp = nCountryId + 16
	SetMonsterCamp(sceneId,nObjId,nCamp)
end

----------------------------------------------------------------------------------------------
--取得当前据点战场配对帮会信息
----------------------------------------------------------------------------------------------		
function x300918_GetMatchGuild(sceneId)
	return x300918_g_GuildA[sceneId],x300918_g_GuildB[sceneId]
end											   
										
										
function x300918_GetCountTime(sceneId)
	return x300918_g_CountTime[sceneId]
end
	   
----------------------------------------------------------------------------------------------
--取得据点地图数量
----------------------------------------------------------------------------------------------											   
function x300918_GetLairdSceneCount(sceneId)
	return getn(x300918_g_LairdSceneInfo)
end

----------------------------------------------------------------------------------------------
--取得据点某个地图详细信息
----------------------------------------------------------------------------------------------		
function x300918_GetLairdSceneInfo(sceneId,nIndex)

	if nIndex < 1 or nIndex > getn(x300918_g_LairdSceneInfo) then
		return
	end
	
	local item = x300918_g_LairdSceneInfo[nIndex]
	return item.NpcGUID,item.LairdScene,item.LairdSceneName,item.Level,item.Flag0,item.Flag1
end

----------------------------------------------------------------------------------------------
--取得据点地图名称
----------------------------------------------------------------------------------------------
function x300918_GetLairdSceneInfo_Name(nLairdMapId)
	
	local strName = ""
	for i,item in x300918_g_LairdSceneInfo do
		if item.LairdScene == nLairdMapId then
			strName = item.LairdSceneName
			break
		end
	end
	
	return strName
	
end


----------------------------------------------------------------------------------------------
--取得战场状态
----------------------------------------------------------------------------------------------
function x300918_GetBattleState(sceneId)
	
	return x300918_g_BattleState[sceneId]
	
end

----------------------------------------------------------------------------------------------
--取得战场进入标记
----------------------------------------------------------------------------------------------
function x300918_GetBattleEnterSceneFlag(sceneId)
	return x300918_g_BattleEnterFlag[sceneId];
end

----------------------------------------------------------------------------------------------
--设置进战场标记
----------------------------------------------------------------------------------------------
function x300918_SetBattleEnterSceneFlag(sceneId,nEnterSceneFlag)
	x300918_g_BattleEnterFlag[sceneId] = nEnterSceneFlag
end

----------------------------------------------------------------------------------------------
--检查是否是领主战场场景，如果不是返回0，是返回1
----------------------------------------------------------------------------------------------
function x300918_GetLairdBattleSceneScript( sceneId )

    local name = GetBattleSceneName(sceneId)
    for i,item in x300918_g_SceneName do
        if name == item.Name and item.Toggle == 1 then
            return item.Script
        end
    end

    return 0
end

----------------------------------------------------------------------------------------------
--检查是否是A外援
----------------------------------------------------------------------------------------------
function x300918_IsPlayerAidA(sceneId,selfId)
	
	local nGUID = GetGUID(sceneId,selfId)
	
	for i,item in x300918_g_GuildAidA[sceneId] do
		if item == nGUID then
			return 1
		end
	end
	
	
	return 0
	
end

----------------------------------------------------------------------------------------------
--检查是否是B外援
----------------------------------------------------------------------------------------------
function x300918_IsPlayerAidB(sceneId,selfId)
	
	local nGUID = GetGUID(sceneId,selfId)
	
	for i,item in x300918_g_GuildAidB[sceneId] do
		if item == nGUID then
			return 1
		end
	end
	
	
	return 0
	
end



----------------------------------------------------------------------------------------------
--默认处理
----------------------------------------------------------------------------------------------
function x300918_ProcEventEntry( sceneId, selfId, targetId, MissionId,nExtId )
	BeginQuestEvent(sceneId)
		AddQuestText( sceneId, "\t感谢你为领地图腾升级所做的贡献！" )
    	CallScriptFunction(300950,"CallbackEnumEvent", sceneId, selfId, targetId, 0)
    	CallScriptFunction(300951,"CallbackEnumEvent", sceneId, selfId, targetId, 0)
    	CallScriptFunction(300952,"CallbackEnumEvent", sceneId, selfId, targetId, 0)
		CallScriptFunction(300953,"CallbackEnumEvent", sceneId, selfId, targetId, 0)
		CallScriptFunction(300954,"CallbackEnumEvent", sceneId, selfId, targetId, 0)
		CallScriptFunction(300955,"CallbackEnumEvent", sceneId, selfId, targetId, 0)
		CallScriptFunction(300956,"CallbackEnumEvent", sceneId, selfId, targetId, 0)
		CallScriptFunction(300957,"CallbackEnumEvent", sceneId, selfId, targetId, 0)
		CallScriptFunction(300958,"CallbackEnumEvent", sceneId, selfId, targetId, 0)
		CallScriptFunction(302506,"CallbackEnumEvent", sceneId, selfId, targetId, 0)
    	
    EndQuestEvent(sceneId)
	DispatchQuestEventList(sceneId,selfId,targetId)
end


----------------------------------------------------------------------------------------------
--活动触发
----------------------------------------------------------------------------------------------
function x300918_OnBattleStateEvent( sceneId, state  )

	--合服开关
    if GetMergeDBToggle() == 1 then
        return
    end
    
  --升级数据库开关
	local UpdateDBflag = GetUpdateDBBeforeToggle()
	if UpdateDBflag==1 then
		return
	end
    
    --测试服开关
    --if GetTestServerToggle() == 0 then
    --    return
    --end

    --战场自己的开关
    if GetBattleSceneToggle( BATTLESCENE_TYPE_LAIRDGBATTLELITE ) == 0 then
        return
    end


	local nScriptId = x300918_GetLairdBattleSceneScript( sceneId )
	if  nScriptId == 0 then

		-----------------------------------------------------------------------------------
		--场景类型是普通场景
		-----------------------------------------------------------------------------------
		
        if state == x300918_g_Laird_Signup then

            --检查状态是否已经置过
            if x300918_g_BattleState[sceneId] ~= x300918_g_Laird_Signup then
                local msg = format("LBL:x300918_g_Laird_Signup,SceneId=%d ",sceneId  )
                WriteLog(1,msg)
            end

            
            x300918_g_BattleState[sceneId] = x300918_g_Laird_Signup
            
        elseif state == x300918_g_Laird_WaitBattle then

            --检查状态是否已经置过
            if x300918_g_BattleState[sceneId] ~= x300918_g_Laird_WaitBattle then
                local msg = format("LBL:x300918_g_Laird_WaitBattle,SceneId=%d ",sceneId )
                WriteLog(1,msg)
            end
            
            --报名结束
            x300918_g_BattleState[sceneId] = x300918_g_Laird_WaitBattle
            
        elseif state == x300918_g_Laird_BeginBattle then

            --检查状态是否已经置过
            if x300918_g_BattleState[sceneId] == x300918_g_Laird_BeginBattle then
                local msg = format("LBL:x300918_g_Laird_BeginBattle,SceneId=%d ",sceneId )
                WriteLog(1,msg)
            end
            
            --开始领主战场
            x300918_g_BattleState[sceneId] = x300918_g_Laird_BeginBattle
            x300918_g_BattleEnterFlag[sceneId] = 1

        elseif state == x300918_g_Laird_EndBattle then
            
            --领主战场结束
            x300918_g_BattleState[sceneId] = x300918_g_Laird_EndBattle

            local msg = format("LBL:x300918_g_Laird_EndBattle, SceneId=%d",sceneId )
            WriteLog(1,msg)

        end

	elseif nScriptId == 300918 then
	
		-----------------------------------------------------------------------------------
		--场景类型是领主战场场景
		-----------------------------------------------------------------------------------

        if state == x300918_g_Laird_Signup then

            --检查状态是否已经置过
            if x300918_g_BattleState[sceneId] ~= x300918_g_Laird_Signup then
                
                --记录日志
                local msg = format("LBL:x300918_g_Laird_Signup,SceneId=%d,2 ",sceneId  )
                WriteLog(1,msg)

            end

            --GameBattleSceneAskInit( sceneId,2 )                                             --向GLServer注册一下
            x300918_g_BattleState[sceneId] = x300918_g_Laird_Signup		                      	--设置状态

        elseif state == x300918_g_Laird_WaitBattle then

            --检查状态是否已经置过
            if x300918_g_BattleState[sceneId] ~= x300918_g_Laird_WaitBattle then
                local msg = format("LBL:x300918_g_Laird_WaitBattle,SceneId=%d,2",sceneId )
                WriteLog(1,msg)
            end

            --设置基本数据
            x300918_g_BattleState[sceneId] = x300918_g_Laird_WaitBattle
            
        elseif state == x300918_g_Laird_BeginBattle then

            --检查状态是否已经置过
            if x300918_g_BattleState[sceneId] ~= x300918_g_Laird_BeginBattle then
                local msg = format("LBL:x300918_g_Laird_BeginBattle,SceneId=%d,2",sceneId )
                WriteLog(1,msg)
            end

            --设置基本数据            
            x300918_g_BattleState[sceneId] = x300918_g_Laird_BeginBattle
            x300918_OnBattleSceneReady( sceneId,( x300918_g_TotalBattleTime) )

        elseif state == x300918_g_Laird_EndBattle then

            if x300918_g_BattleState[sceneId] > x300918_g_Laird_BeginBattle or x300918_g_BattleState[sceneId] < x300918_g_Laird_Signup then
                
                local msg = format("LBL:x300918_g_Laird_EndBattle,Result:nState > x300918_g_Laird_BeginBattle or nState < x300918_g_Laird_Signup  SceneId=%d,state=%d,2",sceneId, state )
                WriteLog(1,msg)

                --根据玩法的脚本的不同，进行相关初始化回调
                x300918_OnBattleSceneClose( sceneId )

                local msg = format("LBL:x300918_g_Laird_EndBattle, SceneId=%d,2",sceneId )
                WriteLog(1,msg)
                return
            end

            --设置状态，活动结束
    		x300918_g_BattleState[sceneId] = x300918_g_Laird_EndBattle 
            x300918_OnBattleSceneClose( sceneId )

            local msg = format("LBL:x300918_g_Laird_EndBattle, SceneId=%d,3",sceneId )
            WriteLog(1,msg)
        end
	end
end

----------------------------------------------------------------------------------------------
--领主战场场心跳
----------------------------------------------------------------------------------------------
function x300918_ProcTiming( sceneId,uTime )

    --检查是否是领主战场场景列表中所处理的情况，如果不是，则不处理
    local nScriptId = x300918_GetLairdBattleSceneScript( sceneId )
    if  nScriptId == 0 then
        return
    end
       
    x300918_OnBattleSceneTimer( sceneId, uTime)
end


----------------------------------------------------------------------------------------------
--玩家进入事件
----------------------------------------------------------------------------------------------
function x300918_OnPlayerEnter( sceneId, playerId )

    --检查是否是领主战场场景列表中所处理的情况，如果不是，则不处理
    local nScriptId = x300918_GetLairdBattleSceneScript( sceneId )
    if  nScriptId == 0 then
        return
    end

    local status = x300918_g_BattleState[sceneId]
    if status ~= x300918_g_Laird_BeginBattle then
    
        --x300918_SetAllPlayerNeedKick( sceneId )
        
        --local msg = format("LBL:x300918_OnBattlePlayerEnter Kick,Player,SceneId=%d,playerId=%d status=%d",sceneId,playerId,status )
        --WriteLog(1,msg)
        return
    end


    --取得帮会A和帮会B
    local nGuildA = x300918_g_GuildA[sceneId]
    local nGuildB = x300918_g_GuildB[sceneId]

    local nGuildId = GetGuildID( sceneId,playerId )

    --设置在战场中的阵营属性
    local nSendCCamp = -1
    if nGuildId == nGuildA or x300918_IsPlayerAidA(sceneId,playerId) == 1 then
        nSendCCamp = 0
    elseif nGuildId == nGuildB or x300918_IsPlayerAidB(sceneId,playerId) == 1 then
        nSendCCamp = 1
    else
--        SetPlayerRuntimeData( sceneId,playerId,RD_BATTLE_SCENE_KICK_DOWN ,x300918_g_Kick_Down) 
--        --记录日志
--        local msg = format("LBL:x300918_OnBattlePlayerEnter Kick 2,Player,SceneId=%d,playerId=%d",sceneId,playerId )
--        WriteLog(1,msg)
        return

    end

    --积分栏设定
    --GameBattleSetDisable(sceneId, playerId, 0, nSendCCamp,2 )

    local strGuildA = GetGuildName( nGuildA )
    local strGuildB = GetGuildName( nGuildB )

    --GameBattleSendBattleInfo( sceneId, playerId, strGuildA, strGuildB,2 )
    --GameBattleSyncScoreInfo( sceneId, playerId, x300918_g_ScoreA[sceneId], x300918_g_ScoreB[sceneId], 2 )

    --玩家进入战场，则清空之前的数据
    SetPlayerRuntimeData(sceneId,playerId,RD_KING_BATTLE_BEKILLED,0)

    --设置阵营
    if nGuildId == nGuildA or x300918_IsPlayerAidA(sceneId,playerId) == 1 then
        --SetCurCamp(sceneId,playerId,x300918_g_Guild_Camp_A)
        --SetPos(sceneId,playerId, 66,78)

    elseif nGuildId == nGuildB or x300918_IsPlayerAidB(sceneId,playerId) == 1 then
        --SetCurCamp(sceneId,playerId,x300918_g_Guild_Camp_B)
        --SetPos(sceneId,playerId,185,182)    	
    end

    SetPlayerRuntimeData( sceneId,playerId,RD_BATTLE_SCENE_KICK_DOWN,-1)

    --对玩家原先的场景进行备份
    local scenePre = GetPlayerRuntimeData(sceneId,playerId,RD_HUMAN_SCENE_PRE ) - 1
    if scenePre >= 0 then
        
        local CurX = GetPlayerRuntimeData(sceneId,playerId,RD_HUMAN_POSX_PRE)
        local CurZ = GetPlayerRuntimeData(sceneId,playerId,RD_HUMAN_POSZ_PRE)

        SetPlayerBakSceneInfo(sceneId,playerId,scenePre,CurX,CurZ)

        SetPlayerRuntimeData(sceneId,playerId,RD_HUMAN_SCENE_PRE,0)
        SetPlayerRuntimeData(sceneId,playerId,RD_HUMAN_POSX_PRE,0)
        SetPlayerRuntimeData(sceneId,playerId,RD_HUMAN_POSZ_PRE,0)

    end
--    
--    --设置门1阻挡
--	x300918_SetTempImpassable_Door1_Effect(sceneId,playerId)
--	
--	--设置门2阻挡
--	x300918_SetTempImpassable_Door2_Effect(sceneId,playerId)
	
end

----------------------------------------------------------------------------------------------
--玩家离开事件
----------------------------------------------------------------------------------------------
function x300918_OnPlayerLeave( sceneId, playerId )

    --检查是否是领主战场场景列表中所处理的情况，如果不是，则不处理
    local nScriptId = x300918_GetLairdBattleSceneScript( sceneId )
    if  nScriptId == 0 then
        return
    end

    local nCountryId = GetCurCountry(sceneId,playerId )
    SetCurCamp( sceneId,playerId,nCountryId )

    GameBattleSetDisable(sceneId, playerId,1,-1,2)
end

----------------------------------------------------------------------------------------------
--玩家退会
----------------------------------------------------------------------------------------------
function x300918_OnPlayerLeaveGuild( sceneId,selfId )
--
--    --检查是否是领主战场场景列表中所处理的情况，如果不是，则不处理
--    local nScriptId = x300918_GetLairdBattleSceneScript( sceneId )
--    if  nScriptId == 0 then
--        return
--    end
--    
--    x300918_LairdBattleKickPlayer( sceneId,selfId )
--    GameBattleSetDisable(sceneId, selfId,1,-1,2)

end

----------------------------------------------------------------------------------------------
--设置领主战场相关配对信息
----------------------------------------------------------------------------------------------
function x300918_OnSetLairdBattleMatchInfo( sceneId,nGuildA,nGuildB,nCountryA,nCountryB,nLairdMapId,nHasLaird )

    --检查是否是领主战场场景列表中所处理的情况，如果不是，则不处理
    local nScriptId = x300918_GetLairdBattleSceneScript( sceneId )
    if  nScriptId == 0 then
        return
    end

	--故意写反的.请不要改
    x300918_g_GuildA[sceneId] = nGuildB 
    x300918_g_GuildB[sceneId] = nGuildA
    x300918_g_LairdMapID[sceneId] = nLairdMapId
    x300918_g_HasLaird[sceneId] = nHasLaird
    
    x300918_g_CountryA[sceneId] = nCountryB 
    x300918_g_CountryB[sceneId] = nCountryA

    --debug
    local a = x300918_g_GuildA[sceneId]
    local b = x300918_g_GuildB[sceneId]
    local ca = x300918_g_CountryA[sceneId]
    local cb = x300918_g_CountryB[sceneId]
    local c = x300918_g_LairdMapID[sceneId]
    local d = x300918_g_HasLaird[sceneId]

    local msg = format( "LBL:LAIRD_BATTLE_MATCHINFO:sceneId=%d,A=%d,B=%d,CA=%d,CB=%d,LairdMap=%d,HasLaird=%d", sceneId, a, b,ca,cb, c, d )
    WriteLog(1,msg)
end


----------------------------------------------------------------------------------------------
--设置领主战场相关配对信息
----------------------------------------------------------------------------------------------
function x300918_OnSetLairdBattleMatchInfo_PlayerAid0( sceneId,guildtype,GUID0,GUID1,GUID2,GUID3,GUID4)

    --检查是否是领主战场场景列表中所处理的情况，如果不是，则不处理
    local nScriptId = x300918_GetLairdBattleSceneScript( sceneId )
    if  nScriptId == 0 then
        return
    end

	--故意写反的.请不要改
	if guildtype == 0 then
	    x300918_g_GuildAidB[sceneId][1] = GUID0 
	    x300918_g_GuildAidB[sceneId][2] = GUID1
	    x300918_g_GuildAidB[sceneId][3] = GUID2
	    x300918_g_GuildAidB[sceneId][4] = GUID3
	    x300918_g_GuildAidB[sceneId][5] = GUID4
	else
		x300918_g_GuildAidA[sceneId][1] = GUID0 
	    x300918_g_GuildAidA[sceneId][2] = GUID1
	    x300918_g_GuildAidA[sceneId][3] = GUID2
	    x300918_g_GuildAidA[sceneId][4] = GUID3
	    x300918_g_GuildAidA[sceneId][5] = GUID4
	end
    
end


----------------------------------------------------------------------------------------------
--设置领主战场相关配对信息
----------------------------------------------------------------------------------------------
function x300918_OnSetLairdBattleMatchInfo_PlayerAid1( sceneId,guildtype,GUID5,GUID6,GUID7,GUID8,GUID9)

    --检查是否是领主战场场景列表中所处理的情况，如果不是，则不处理
    local nScriptId = x300918_GetLairdBattleSceneScript( sceneId )
    if  nScriptId == 0 then
        return
    end

	--故意写反的.请不要改
	if guildtype == 0 then
	    x300918_g_GuildAidB[sceneId][6]  = GUID5
	    x300918_g_GuildAidB[sceneId][7]  = GUID6
	    x300918_g_GuildAidB[sceneId][8]  = GUID7
	    x300918_g_GuildAidB[sceneId][9]  = GUID8
	    x300918_g_GuildAidB[sceneId][10] = GUID9
	else
		x300918_g_GuildAidA[sceneId][6]  = GUID5 
	    x300918_g_GuildAidA[sceneId][7]  = GUID6
	    x300918_g_GuildAidA[sceneId][8]  = GUID7
	    x300918_g_GuildAidA[sceneId][9]  = GUID8
	    x300918_g_GuildAidA[sceneId][10] = GUID9
	end
end

----------------------------------------------------------------------------------------------
--玩家重新上线
----------------------------------------------------------------------------------------------
function x300918_OnPlayerNewConnectEnter( sceneId, selfId )

    --检查是否是领主战场场景列表中所处理的情况，如果不是，则不处理
    local nScriptId = x300918_GetLairdBattleSceneScript( sceneId )
    if  nScriptId == 0 then
        return
    end

    local BattleSceneFlag = GetPlayerRuntimeData(sceneId,selfId,RD_BATTLESCENE_ENTER_FLAG)
    if BattleSceneFlag == 0 then

        --新上线的玩家,设置Kick倒计时，准备踢掉
        SetPlayerRuntimeData( sceneId,selfId,RD_BATTLE_SCENE_KICK_DOWN,x300918_g_Kick_Down)

        local name = GetName(sceneId,selfId)
        if name == nil then
            name = "ErrorName"
        end
        local msg = format( "LBL:x300918_OnPlayerNewConnectEnter 0,need kick,sceneId=%d,selfId=%d,name=%s", sceneId, selfId, name )
        WriteLog(1,msg)

    else

        --从别一个服务器转过来的玩家
        --同组服务器的玩家,这时的RD_BATTLESCENE_ENTER_FLAG值目前无法清0，
        --只有在玩家离开战场或下线时清除，但是不同服务器组的可以马上清除
        local name = GetName(sceneId,selfId)
        if name == nil then
            name = "ErrorName"
        end
        local msg = format( "LBL:x300918_OnPlayerNewConnectEnter 1,sceneId=%d,selfId=%d,name=%s", sceneId, selfId, name )
        WriteLog(1,msg)

        SetPlayerRuntimeData(sceneId,selfId,RD_BATTLESCENE_ENTER_FLAG,0)

    end
end

----------------------------------------------------------------------------------------------
--玩家死亡处理
----------------------------------------------------------------------------------------------
function x300918_OnPlayerDie( sceneId, selfId, killerId  )

    --检查是否是领主战场场景列表中所处理的情况，如果不是，则不处理
    local nScriptId = x300918_GetLairdBattleSceneScript( sceneId )
    if  nScriptId == 0 then
        return
    end
    
    --检查状态，如果没有开启，则不处理
    local status = x300918_g_BattleState[sceneId]
    if status ~= x300918_g_Laird_BeginBattle then
        return
    end
    
    --过滤掉非战斗双方的玩家
    local nGuildId = GetGuildID(sceneId,selfId)
    if nGuildId ~= x300918_g_GuildA[sceneId] and x300918_IsPlayerAidA(sceneId,selfId) ~= 1 and
       nGuildId ~= x300918_g_GuildB[sceneId] and x300918_IsPlayerAidB(sceneId,selfId) ~= 1 then
        return
    end
    
    --A方的人死亡,B方加分
    if GetCurCamp(sceneId,selfId) == x300918_g_Guild_Camp_A then
    	x300918_g_ScoreB[sceneId] = x300918_g_ScoreB[sceneId] + 1
    end
    
    --B方的人死亡,A方加分
    if GetCurCamp(sceneId,selfId) == x300918_g_Guild_Camp_B then
    	x300918_g_ScoreA[sceneId] = x300918_g_ScoreA[sceneId] + 1
    end
    
    --积分变化
    x300918_LairdSyncGuildScore(sceneId)

    --记录被杀次数
    local nBeKilled = GetPlayerRuntimeData(sceneId,selfId,RD_KING_BATTLE_BEKILLED ) + 1
    SetPlayerRuntimeData(sceneId,selfId,RD_KING_BATTLE_BEKILLED,nBeKilled)

    --是玩家杀死的
    --local ObjType = GetObjType(sceneId, killerId)

    --杀人者在线并且是玩家，被杀的人死亡6次以内（包含6次）
--    if IsPlayerStateNormal( sceneId,killerId ) == 1 and ObjType == 1 and nBeKilled <= 6 then
--
--        AddGuildUserPoint(sceneId,killerId,10)
--
--        local msg = "您获得了10点帮贡"
--        local name = GetName(sceneId,killerId )
--
--        LuaScenceM2Player(sceneId, killerId, msg, name , 2,1)
--    
--    end

    --超过六次，不再提示
    --if nBeKilled <= 6 then 

        local str = format("#G%s在【国家】领地争夺战中被杀死",GetName(sceneId,selfId ) )
        LuaThisScenceM2Wrold(sceneId,str,3,1)
        LuaThisScenceM2Wrold(sceneId,str,2,1)
    --end

    --第六次，给提示
--    if nBeKilled == 6 then
--
--        local nCountryId = GetCurCountry( sceneId,selfId)
--
--        local str = format("#G%s在【国家】领主战场中，死亡次数已满，被迫离开战场。",GetName(sceneId,selfId ) )
--        LuaAllScenceM2Country(sceneId,str,nCountryId,3,1)
--        LuaAllScenceM2Country(sceneId,str,nCountryId,2,1)
--
--        --加入倒计时保护，防止一直被杀，而不退出战场
--        local KickDown = GetPlayerRuntimeData( sceneId,selfId,RD_BATTLE_SCENE_KICK_DOWN ) 
--        if KickDown <= 0 or KickDown > 4 then
--            SetPlayerRuntimeData( sceneId,selfId,RD_BATTLE_SCENE_KICK_DOWN ,4) 
--        end
--    end

end

-------------------------------------------------------------------------------
--检查状态是否正常
-------------------------------------------------------------------------------
function x300918_CheckPlayerState( sceneId,selfId )
    

    local state
    local ErrorMsg

    state = IsPlayerStateNormal(sceneId,selfId )
    if state == 0 then
        ErrorMsg = "状态异常"
        return 1,ErrorMsg
    end

    state = IsPlayerMutexState(sceneId,selfId,PLAYER_STATE_MENTALGAME )
    if state == 1 then
        ErrorMsg = "处于答题状态，不能进入战场"
        return 1,ErrorMsg
    end

    state = IsPlayerMutexState(sceneId,selfId,PLAYER_STATE_STALL )
    if state == 1 then
        ErrorMsg = "处于摆摊状态，不能进入战场"
        return 1,ErrorMsg
    end

    state = IsPlayerMutexState(sceneId,selfId,PLAYER_STATE_DIE )
    if state == 1 then
        ErrorMsg = "处于死亡状态，不能进入战场"
        return 1,ErrorMsg
    end

    state = IsPlayerMutexState(sceneId,selfId,PLAYER_STATE_CRASHBOX )
    if state == 1 then
        ErrorMsg = "处于运镖状态，不能进入战场"
        return 1,ErrorMsg
    end

    state = IsPlayerMutexState(sceneId,selfId,PLAYER_STATE_AUTOPLAY )
    if state == 1 then
        ErrorMsg = "处于挂机状态，不能进入战场"
        return 1,ErrorMsg
    end

    state = IsPlayerMutexState(sceneId,selfId,PLAYER_STATE_SUBTRAIN )
    if state == 1 then
        ErrorMsg = "处于代练状态，不能进入战场"
        return 1,ErrorMsg
    end

    state = IsPlayerMutexState(sceneId,selfId,PLAYER_STATE_BUS )
    if state == 1 then
        ErrorMsg = "处于BUS状态，不能进入战场"
        return 1,ErrorMsg
    end

    state = IsPlayerMutexState(sceneId,selfId,PLAYER_STATE_PKMODE )
    if state == 1 then
        ErrorMsg = "PK值过高或处于狂暴模式，不能进入战场"
        return 1,ErrorMsg
    end

    return 0

end

-------------------------------------------------------------------------------
--领主战场相关传送脚本
-------------------------------------------------------------------------------
function x300918_OnLairdBattleChangeScene( sceneId,selfId,newSceneID,Flag )
    

    --如果在监狱不可以被传送
	if sceneId == PK_PUNISH_PRISON_SCENE_ID then
		BeginQuestEvent(sceneId)
		local strText = "监狱里还不老实,想走,没门。"
		AddQuestText( sceneId, strText )
		EndQuestEvent( sceneId )
		DispatchQuestTips( sceneId, selfId )
		return
	end

    local PosX = 100
    local PosZ = 100


    if sceneId == newSceneID then
        
        if Flag == 0 then
		    SetPos( sceneId , selfId , 68 ,76 )
        else
            SetPos( sceneId , selfId , 182,181 )
        end
	else
        
        --检查状态
        local state,msg = x300918_CheckPlayerState( sceneId,selfId )
        if state == 1 then
            
            BeginQuestEvent(sceneId)
            AddQuestText( sceneId, msg );
            EndQuestEvent(sceneId)
            DispatchQuestTips(sceneId,selfId)
            return
        end

        --记录一个RuntimeData
        local nCurX,nCurZ = GetWorldPos( sceneId,selfId )
        SetPlayerRuntimeData(sceneId,selfId,RD_HUMAN_SCENE_PRE,sceneId + 1)
        SetPlayerRuntimeData(sceneId,selfId,RD_HUMAN_POSX_PRE,nCurX)
        SetPlayerRuntimeData(sceneId,selfId,RD_HUMAN_POSZ_PRE,nCurZ)
        SetPlayerRuntimeData(sceneId,selfId,RD_BATTLESCENE_ENTER_FLAG,1)

		NewWorld( sceneId , selfId , newSceneID , PosX , PosZ,300918 )
	end
end

function x300918_DoPlayerRelive( sceneId, selfId )
	
	if GetHp(sceneId,selfId) > 0 then
		return
	end
	
    RestoreHp(sceneId, selfId,0)
	RestoreRage(sceneId, selfId,100)
	ClearMutexState(sceneId, selfId, 6)
	SendReliveResult(sceneId, selfId,1)	

    --清除死亡状态
    RelivePlayerNM(sceneId,selfId,2)	
    SetPlayerMutexState(sceneId,selfId,PLAYER_STATE_DIE,0)
end

--领主战场复活
function x300918_OnPlayerRelive( sceneId, selfId )

--    --检查是否是领主战场
--    local nScriptId = x300918_GetLairdBattleSceneScript( sceneId )
--    if nScriptId == 0 then
--        return
--    end
--    
--    --检查死亡次数是否超过6次
--    local nBeKilled = GetPlayerRuntimeData(sceneId,selfId,RD_KING_BATTLE_BEKILLED )
--    if nBeKilled >= 6 then
--        
--        --再做一次保护
--        local KickDown = GetPlayerRuntimeData( sceneId,selfId,RD_BATTLE_SCENE_KICK_DOWN ) 
--        if KickDown <= 0 or KickDown > 4 then
--            SetPlayerRuntimeData( sceneId,selfId,RD_BATTLE_SCENE_KICK_DOWN ,4) 
--        end
--        
--        return
--    end
--    
--    --执行复活操作
--    ClearRageRecoverTick(sceneId, selfId)
--	RestoreHp(sceneId, selfId,100)
--	RestoreRage(sceneId, selfId,100)
--	ClearMutexState(sceneId, selfId, 6)
--	SendReliveResult(sceneId, selfId,1)
--
--	--得到玩家所属方，A或B方
--    local nGuildId = GetGuildID( sceneId,selfId )
--    local nGuildA = x300918_g_GuildA[sceneId]
--    local nGuildB = x300918_g_GuildB[sceneId]
--
--    if nGuildId == nGuildA or x300918_IsPlayerAidA(sceneId,selfId) == 1 then
--
--        x300918_OnLairdBattleChangeScene(sceneId,selfId,sceneId,0)
--    else
--        x300918_OnLairdBattleChangeScene(sceneId,selfId,sceneId,1)
--    end

end


----------------------------------------------------------------------------------------------
--夺旗场景初始化
----------------------------------------------------------------------------------------------
function x300918_OnBattleSceneReady( sceneId,totalTime )

	local nScriptId = x300918_GetLairdBattleSceneScript( sceneId )
    if  nScriptId == 0 then
        return
    end

    --生长点相关初始化
    x300918_g_CountDownState[sceneId] = -1
    x300918_g_CountDownTime[sceneId] = 10

    --设置心跳时间
    x300918_g_CountTime[sceneId] = totalTime
    
    --设置阻挡状态
    x300918_g_TempImpassable_Door2_State[sceneId]	=	{  1,  1 }
    
    --设置阻挡
    --x300918_SetTempImpassable_Door1(sceneId)
    --x300918_SetTempImpassable_Door2(sceneId)
    
    --重置生长点
    --x300918_ResetDoorA(sceneId)
    --x300918_ResetDoorB(sceneId)
    
    --重置内部集分
    x300918_g_ScoreA[sceneId] =	0
	x300918_g_ScoreB[sceneId] =	0
	x300918_g_IntervalScoreA[sceneId] =	0
	x300918_g_IntervalScoreB[sceneId] =	0
    
    
end

----------------------------------------------------------------------------------------------
--显示据点信息
----------------------------------------------------------------------------------------------
function x300918_ShowLairdSceneInfo( sceneId )
	
	local nScriptId = x300918_GetLairdBattleSceneScript( sceneId )
    if  nScriptId == 0 then
        return
    end
    
    local nGuildId = GetSceneLairdGuildId(sceneId)    
    if nGuildId < 0 then
    	return
    end
    
    local nCountryId = GetSceneLairdCountryId(sceneId)
    if nCountryId < 0 or nCountryId > 3 then
    	return
    end
    
    local strGuildName = GetGuildName(nGuildId)
    local strGuildLeaderName = GetGuildLeaderName(nGuildId)
    local strCountryName = CallScriptFunction(888894,"GetCountryName",sceneId,nCountryId)
    local strLairdSceneName = x300918_GetLairdSceneInfo_Name(sceneId)
    
    local strMsg = format("领地争夺战结束，#G%s#o的#R%s#o占领了%s",strCountryName,strGuildName,strLairdSceneName)
    
    LuaAllScenceM2Wrold(sceneId, strMsg, 2, 1)
	LuaAllScenceM2Wrold(sceneId, strMsg, 3, 1)
    
end

----------------------------------------------------------------------------------------------
--关闭处理
----------------------------------------------------------------------------------------------
function x300918_OnBattleSceneClose( sceneId )

	x300918_ShowLairdSceneInfo( sceneId )
	
    if x300918_g_CountDownState[sceneId] == 1 then
        return
    end

    local status = x300918_g_BattleState[sceneId]
	if status == x300918_g_Laird_EndBattle then
		x300918_BattleGenResult( sceneId,0 )
	end


end

----------------------------------------------------------------------------------------------
--领主战场场心跳
----------------------------------------------------------------------------------------------
function x300918_OnBattleSceneTimer( sceneId,uTime )
	
	--修正BOSS阵营操作
    x300918_FixBossCampOp( sceneId )
    
    --BOSS状态更新
    x300918_UpdateBossState(sceneId)

    --更新玩家Kick状态
    --x300918_UpdatePlayerKickState( sceneId )

    local BattleStatus = x300918_g_BattleState[sceneId]
    if BattleStatus ~= x300918_g_Laird_BeginBattle then
    	--给BOSS回满血，如果非战斗情况
    	x300918_FullBossHp(sceneId)
        return
    end

    --计时
    ----------------------------------------------------------------------------------------------
    local nTime = x300918_g_CountTime[sceneId] - 1
    x300918_g_CountTime[sceneId] = nTime

    --倒计时处理
    ----------------------------------------------------------------------------------------------
    if x300918_g_CountDownState[sceneId] == 1 then

	    --倒计时状态
	    local time = x300918_g_CountDownTime[sceneId]
	    if time > 0 then

		    x300918_g_CountDownTime[sceneId] = time - 1
--
--		    local str = format("#G【国家】领主战场结束,#R%d秒#G后战场自动关闭",time)
--
--		    LuaThisScenceM2Guild(sceneId,str,x300918_g_GuildA[sceneId],3,1)
--		    LuaThisScenceM2Guild(sceneId,str,x300918_g_GuildB[sceneId],3,1)

		else

            --踢掉所有玩家
            --x300918_RestoreAllPlayerCamp( sceneId )
	    	--x300918_LairdBattleKickAllPlayer(sceneId)

			--清除数据
			x300918_g_BattleState[sceneId]				   = -1
			x300918_g_GuildA[sceneId]					   = -1
			x300918_g_GuildB[sceneId]					   = -1
			x300918_g_CountryA[sceneId]					   = -1
			x300918_g_CountryB[sceneId]					   = -1
			x300918_g_LairdMapID[sceneId]				   = -1
			x300918_g_HasLaird[sceneId]					   = 0
			x300918_g_CountDownState[sceneId]			   = -1
			x300918_g_CountDownTime[sceneId]			   = -1
			x300918_g_CountTime[sceneId]			       = -1
			x300918_g_GuildAidA[sceneId]					= {}
			x300918_g_GuildAidB[sceneId]					= {}
			
			--重置内部集分
		    x300918_g_ScoreA[sceneId] =	0
			x300918_g_ScoreB[sceneId] =	0
			x300918_g_IntervalScoreA[sceneId] =	0
			x300918_g_IntervalScoreB[sceneId] =	0
            
            --记录日志
            local msg = format("LBL:x300918_OnBattleSceneTimer LairdBattleFinished,SceneId=%d,LeaveTime h= %d,m=%d",sceneId, floor(nTime/60),mod(nTime,60) )
            WriteLog(1,msg)

	    end

	    return

	end
	
	--加血处理
	local nMod = mod(nTime,600)
	if nMod == 0 then
		--10分钟回一次血
		x300918_FixBossHp(sceneId)		
	end
	
--	
--	--一分钟后开始
--    ----------------------------------------------------------------------------------------------
--	if nTime == 29*60 then

--		x300918_ClearTempImpassable_Door1(sceneId)
--	end
--
--    --检查是否结束
--    ----------------------------------------------------------------------------------------------
--    if nTime < 28*60 then
--        local bIsFinished = x300918_CheckIsFinished( sceneId)
--        if bIsFinished == 1 then
--            
--            local status = x300918_g_BattleState[sceneId]
--            if status == x300918_g_Laird_BeginBattle then
--
--                x300918_BattleGenResult( sceneId,1 )
--                return
--            end
--
--        end
--    end
--	
--
--    --定时器时间同步
--    ----------------------------------------------------------------------------------------------
--    x300918_SyncGuildPower( sceneId )
--
--    --小地图上显示帮主
--    x300918_UpdateSceneDataFlag( sceneId )

end

----------------------------------------------------------------------------------------------
--修正阵营
----------------------------------------------------------------------------------------------
function x300918_FixBossCampOp( sceneId )
	
	
	local nObjId = 1
	if IsObjValid(sceneId,nObjId ) ~= 1 or GetHp(sceneId,nObjId) <= 0 then
		return
	end
	
	
	--以下阵营处理
    local status = x300918_g_BattleState[sceneId]
    if status ~= x300918_g_Laird_BeginBattle then
    
    	--战场没有开启
        local nCurCamp = GetMonsterCamp(sceneId,nObjId)		
		if nCurCamp == 20 then
			return
		end
		
		SetMonsterCamp(sceneId,nObjId,20)
		return
		
    else
    	
    	--战场开启处理
    	local nGuildId = GetSceneLairdGuildId( sceneId )
		if nGuildId < 0 then
			
			--没有被占领的处理
			local nCurCamp = GetMonsterCamp(sceneId,nObjId)		
			if nCurCamp == 21 then
				return
			end
			
			SetMonsterCamp(sceneId,nObjId,21)
			return
		else
			
			--已经被占领的处理
			local nCountryId = GetSceneLairdCountryId(sceneId)
			if nCountryId < 0 or nCountryId > 3 then
				return
			end
			
			local nToSetCamp = nCountryId + 16
			local nCurCamp = GetMonsterCamp(sceneId,nObjId)		
			if nToSetCamp == nCurCamp then
				return
			end
			
			SetMonsterCamp(sceneId,nObjId,nToSetCamp)
			return
		end
    end
		
end

----------------------------------------------------------------------------------------------
--Boss相关更新
----------------------------------------------------------------------------------------------
function x300918_UpdateBossState(sceneId)
	
	
	--检查OBJ有效性
	local nObjId = 1
	if IsObjValid(sceneId,nObjId ) ~= 1 or GetHp(sceneId,nObjId) <= 0 then
		return
	end
	
	--自动恢复BUF
	if IsHaveSpecificImpact(sceneId,nObjId,13524)~=1 then
		SendSpecificImpactToUnit(sceneId, nObjId, nObjId, nObjId, 13524, 0)	
	end
	
	--禁止加血BUF
	if IsHaveSpecificImpact(sceneId,nObjId,8354)~=1 then
		SendSpecificImpactToUnit(sceneId, nObjId, nObjId, nObjId, 8354, 0)	
	end
	
	
	--开始处理BUF
	for i,item in x300918_g_SceneName do
		
		if item.Toggle == 1 and item.MapId == sceneId then
			
			--根据等级加上变身BUF 级别从0开始
			local nLairdLevel = GetSceneLairdLevel(sceneId)
			if nLairdLevel == 1 then
				
				--一级的时候
				if item.Buf[1] ~= -1 and IsHaveSpecificImpact(sceneId,nObjId,item.Buf[1])~=1 then
					SendSpecificImpactToUnit(sceneId, nObjId, nObjId, nObjId, item.Buf[1], 0)	
				end
				
				--清除互斥BUF,可能会出现清除不了的情况,所以主动清除不会产生BUG
				if item.Buf[2] ~= -1 and IsHaveSpecificImpact(sceneId,nObjId,item.Buf[2])==1 then
					CancelSpecificImpact(sceneId, nObjId,item.Buf[2], 0)	
				end		
				
				if item.Buf[3] ~= -1 and IsHaveSpecificImpact(sceneId,nObjId,item.Buf[3])==1 then
					CancelSpecificImpact(sceneId, nObjId,item.Buf[3], 0)	
				end
				
				if item.Buf[4] ~= -1 and IsHaveSpecificImpact(sceneId,nObjId,item.Buf[4])==1 then
					CancelSpecificImpact(sceneId, nObjId,item.Buf[4], 0)	
				end
				
				if item.Buf[5] ~= -1 and IsHaveSpecificImpact(sceneId,nObjId,item.Buf[4])==1 then
					CancelSpecificImpact(sceneId, nObjId,item.Buf[5], 0)	
				end
				
			elseif nLairdLevel == 2 then
				
				--二级的时候
				if item.Buf[2] ~= -1 and IsHaveSpecificImpact(sceneId,nObjId,item.Buf[2])~=1 then
					SendSpecificImpactToUnit(sceneId, nObjId, nObjId, nObjId, item.Buf[2], 0)	
				end
				
				--清除互斥BUF,可能会出现清除不了的情况,所以主动清除不会产生BUG
				if item.Buf[1] ~= -1 and IsHaveSpecificImpact(sceneId,nObjId,item.Buf[1])==1 then
					CancelSpecificImpact(sceneId, nObjId,item.Buf[1], 0)	
				end	
				
				if item.Buf[3] ~= -1 and IsHaveSpecificImpact(sceneId,nObjId,item.Buf[3])==1 then
					CancelSpecificImpact(sceneId, nObjId,item.Buf[3], 0)	
				end
				
				if item.Buf[4] ~= -1 and IsHaveSpecificImpact(sceneId,nObjId,item.Buf[4])==1 then
					CancelSpecificImpact(sceneId, nObjId,item.Buf[4], 0)	
				end
				
				if item.Buf[5] ~= -1 and IsHaveSpecificImpact(sceneId,nObjId,item.Buf[4])==1 then
					CancelSpecificImpact(sceneId, nObjId,item.Buf[5], 0)	
				end
			elseif nLairdLevel == 3 then
				
				--三级的时候
				if item.Buf[3] ~= -1 and IsHaveSpecificImpact(sceneId,nObjId,item.Buf[3])~=1 then
					SendSpecificImpactToUnit(sceneId, nObjId, nObjId, nObjId, item.Buf[3], 0)	
				end
				
				--清除互斥BUF,可能会出现清除不了的情况,所以主动清除不会产生BUG
				if item.Buf[1] ~= -1 and IsHaveSpecificImpact(sceneId,nObjId,item.Buf[1])==1 then
					CancelSpecificImpact(sceneId, nObjId,item.Buf[1], 0)	
				end		
				
				if item.Buf[2] ~= -1 and IsHaveSpecificImpact(sceneId,nObjId,item.Buf[2])==1 then
					CancelSpecificImpact(sceneId, nObjId,item.Buf[2], 0)	
				end
				
				if item.Buf[4] ~= -1 and IsHaveSpecificImpact(sceneId,nObjId,item.Buf[4])==1 then
					CancelSpecificImpact(sceneId, nObjId,item.Buf[4], 0)	
				end
				
				if item.Buf[5] ~= -1 and IsHaveSpecificImpact(sceneId,nObjId,item.Buf[4])==1 then
					CancelSpecificImpact(sceneId, nObjId,item.Buf[5], 0)	
				end
			elseif nLairdLevel == 4 then
				
				--四级的时候
				if item.Buf[4] ~= -1 and IsHaveSpecificImpact(sceneId,nObjId,item.Buf[4])~=1 then
					SendSpecificImpactToUnit(sceneId, nObjId, nObjId, nObjId, item.Buf[4], 0)	
				end
				
				--清除互斥BUF,可能会出现清除不了的情况,所以主动清除不会产生BUG
				if item.Buf[1] ~= -1 and IsHaveSpecificImpact(sceneId,nObjId,item.Buf[1])==1 then
					CancelSpecificImpact(sceneId, nObjId,item.Buf[1], 0)	
				end		
				
				if item.Buf[2] ~= -1 and IsHaveSpecificImpact(sceneId,nObjId,item.Buf[2])==1 then
					CancelSpecificImpact(sceneId, nObjId,item.Buf[2], 0)	
				end		
				
				if item.Buf[3] ~= -1 and IsHaveSpecificImpact(sceneId,nObjId,item.Buf[3])==1 then
					CancelSpecificImpact(sceneId, nObjId,item.Buf[3], 0)	
				end
				
				if item.Buf[5] ~= -1 and IsHaveSpecificImpact(sceneId,nObjId,item.Buf[4])==1 then
					CancelSpecificImpact(sceneId, nObjId,item.Buf[5], 0)	
				end
				
			elseif nLairdLevel == 5 then
				
				--五级的时候
				if item.Buf[5] ~= -1 and IsHaveSpecificImpact(sceneId,nObjId,item.Buf[5])~=1 then
					SendSpecificImpactToUnit(sceneId, nObjId, nObjId, nObjId, item.Buf[5], 0)	
				end
				
				
				--清除互斥BUF,可能会出现清除不了的情况,所以主动清除不会产生BUG
				if item.Buf[1] ~= -1 and IsHaveSpecificImpact(sceneId,nObjId,item.Buf[1])==1 then
					CancelSpecificImpact(sceneId, nObjId,item.Buf[1], 0)	
				end		
				
				if item.Buf[2] ~= -1 and IsHaveSpecificImpact(sceneId,nObjId,item.Buf[2])==1 then
					CancelSpecificImpact(sceneId, nObjId,item.Buf[2], 0)	
				end		
				
				if item.Buf[3] ~= -1 and IsHaveSpecificImpact(sceneId,nObjId,item.Buf[3])==1 then
					CancelSpecificImpact(sceneId, nObjId,item.Buf[3], 0)	
				end
				
				if item.Buf[4] ~= -1 and IsHaveSpecificImpact(sceneId,nObjId,item.Buf[4])==1 then
					CancelSpecificImpact(sceneId, nObjId,item.Buf[4], 0)	
				end
			
			else
				
				--清除BUF,可能会出现清除不了的情况,所以主动清除不会产生BUG
				if item.Buf[1] ~= -1 and IsHaveSpecificImpact(sceneId,nObjId,item.Buf[1])==1 then
					CancelSpecificImpact(sceneId, nObjId,item.Buf[1], 0)	
				end		
				
				if item.Buf[2] ~= -1 and IsHaveSpecificImpact(sceneId,nObjId,item.Buf[2])==1 then
					CancelSpecificImpact(sceneId, nObjId,item.Buf[2], 0)	
				end		
				
				if item.Buf[3] ~= -1 and IsHaveSpecificImpact(sceneId,nObjId,item.Buf[3])==1 then
					CancelSpecificImpact(sceneId, nObjId,item.Buf[3], 0)	
				end
				
				if item.Buf[4] ~= -1 and IsHaveSpecificImpact(sceneId,nObjId,item.Buf[4])==1 then
					CancelSpecificImpact(sceneId, nObjId,item.Buf[4], 0)	
				end
				
				if item.Buf[5] ~= -1 and IsHaveSpecificImpact(sceneId,nObjId,item.Buf[4])==1 then
					CancelSpecificImpact(sceneId, nObjId,item.Buf[5], 0)	
				end
			
			end
			
			return
			
		end
		
	end

end

----------------------------------------------------------------------------------------------
--设置回血
----------------------------------------------------------------------------------------------
function x300918_FixBossHp(sceneId)
	
	local nObjId = 1
	if IsObjValid(sceneId,nObjId ) ~= 1 or GetHp(sceneId,nObjId) <= 0 then
		return
	end
	
	--设置回血
	local nHp = floor(GetMaxHp(sceneId,nObjId)* 0.05)
	SetHp(sceneId,nObjId,nHp)
end

----------------------------------------------------------------------------------------------
--给BOSS回满血
----------------------------------------------------------------------------------------------
function x300918_FullBossHp(sceneId)

	local nObjId = 1
	if IsObjValid(sceneId,nObjId ) ~= 1 then
		return
	end
	
	--当前血量
	local nCurHp = GetHp(sceneId,nObjId)
	if nCurHp <= 0 then
		return
	end
	
	--是满血状态
	if nCurHp == GetMaxHp(sceneId,nObjId) then
		return
	end
	
	--回满血
	SetHp(sceneId,nObjId,GetMaxHp(sceneId,nObjId))
end

----------------------------------------------------------------------------------------------
--检查是否可以结束
----------------------------------------------------------------------------------------------
function x300918_CheckIsFinished( sceneId )

    
    --收集信息
    local nGuildA = x300918_g_GuildA[sceneId]
    local nGuildB = x300918_g_GuildB[sceneId]


	--双方的数据,算上外援
    local nGuildA_MemberCount = 0
    local nGuildB_MemberCount = 0


    local nHumanCount = GetScenePlayerCount( sceneId )
    local i = 0
    for i = 0,nHumanCount-1 do
        local objId = GetScenePlayerObjId( sceneId,i)
        if objId >= 0 then
            local nGuildId = GetGuildID( sceneId,objId )
            if nGuildId == nGuildA or x300918_IsPlayerAidA(sceneId,objId) == 1 then		
                nGuildA_MemberCount = nGuildA_MemberCount + 1
            elseif nGuildId == nGuildB  or x300918_IsPlayerAidB(sceneId,objId) == 1  then
                nGuildB_MemberCount = nGuildB_MemberCount + 1
            end
        end
    end

    if nGuildA_MemberCount == 0 and nGuildB_MemberCount == 0 then
        return 1
    end

    --一方无人，则可以结束
    if nGuildA_MemberCount == 0 and nGuildB_MemberCount > 0 then
        return 1
    end

    if nGuildB_MemberCount == 0 and nGuildA_MemberCount > 0 then
        return 1
    end

    return 0

end


----------------------------------------------------------------------------------------------
--得到获胜方：0为A方获胜，1为B方获胜，-1为平手
----------------------------------------------------------------------------------------------
function x300918_GetWinner(sceneId)

	local nScriptId = x300918_GetLairdBattleSceneScript( sceneId )
    if  nScriptId == 0 then
        return
    end

    --收集信息
    local nGuildA = x300918_g_GuildA[sceneId]
    local nGuildB = x300918_g_GuildB[sceneId]

    local nGuildA_MemberCount = 0
    local nGuildB_MemberCount = 0

    local nGuildA_GuildIn = 0
    local nGuildB_GuildIn = 0

    local nGuildA_GuilderDie = 0
    local nGuildB_GuilderDie = 0

    local nHumanCount = GetScenePlayerCount( sceneId )
    local i = 0
    for i = 0,nHumanCount-1 do
        local objId = GetScenePlayerObjId( sceneId,i)
        if objId >= 0 then
            local nGuildId = GetGuildID( sceneId,objId )
            if nGuildId == nGuildA or x300918_IsPlayerAidA(sceneId,objId) == 1  then
                nGuildA_MemberCount = nGuildA_MemberCount + 1
            elseif nGuildId == nGuildB or x300918_IsPlayerAidB(sceneId,objId) == 1 then
                nGuildB_MemberCount = nGuildB_MemberCount + 1
            end

            local pos = GetGuildOfficial(sceneId, objId)
	        if pos == x300918_g_Leader_Index then
                if nGuildId == nGuildA then
                    nGuildA_GuildIn = 1
                    nGuildA_GuilderDie = GetPlayerRuntimeData(sceneId,objId,RD_KING_BATTLE_BEKILLED )
                else
                    nGuildB_GuildIn = 1
                    nGuildB_GuilderDie = GetPlayerRuntimeData(sceneId,objId,RD_KING_BATTLE_BEKILLED )
                end
            end
        end
    end


    --胜负判定
    local nScoreA = x300918_g_ScoreA[sceneId] + x300918_g_IntervalScoreA[sceneId]
    local nScoreB = x300918_g_ScoreB[sceneId] + x300918_g_IntervalScoreB[sceneId]
    
    
    if ( nGuildA_MemberCount == 0 and nGuildB_MemberCount == 0 ) or
       ( nGuildA_MemberCount ~= 0 and nGuildB_MemberCount ~= 0 ) then
       
    	--双方都没有人或都都有人的情况下，优先按分数来判断输赢
    	
    	
    	if nScoreA > nScoreB then
	    	--积分高的赢
	    	return 0
	    elseif nScoreA < nScoreB then
	    	--积分高的赢
	    	return 1
	    else
	    	--积分相同的处理
	    	
		    if nGuildA_MemberCount > 0 and nGuildB_MemberCount > 0 then
		    	
		    	--双方都有人
		    	
		    	
		        if nGuildA_MemberCount > nGuildB_MemberCount then
		        	--优先人多的赢
		            return 0
		        elseif nGuildA_MemberCount < nGuildB_MemberCount then
		        	--优先人多的赢
		            return 1
		        else
		        	
		        	--人数相等，帮主优先在的赢
		            
		            if nGuildA_GuildIn == 1 and nGuildB_GuildIn == 0 then
		                --人数相同，帮主在的为赢
		                return 0
		            elseif nGuildA_GuildIn == 0 and nGuildB_GuildIn == 1 then
		                --人数相同，帮主在的为赢
		                return 1
		            else
		                --人数相同帮主都在，帮主死的次少为赢
		                if nGuildA_GuilderDie > nGuildB_GuilderDie then
		                    return 1
		
		                elseif nGuildA_GuilderDie < nGuildB_GuilderDie then
		                    return 0
		                else
		                
		                	--都相同随机输赢
		                	local nRandWin = random(0,1)
		                	if nRandWin < 0 then nRandWin = 0 end
		                	if nRandWin > 1 then nRandWin = 1 end
		                
		                    return nRandWin
		                end
		            end
		        end
		    else
		    	
		    	--没人且分数相同
		    	
		    	--如果条件都相同，则随机吧
            	local nRandWin = random(0,1)
            	if nRandWin < 0 then nRandWin = 0 end
            	if nRandWin > 1 then nRandWin = 1 end
            
                return nRandWin
		    end
	    end
    else
    	--只有一方有人的处理
    
	    --判断人数多的赢
	    if nGuildA_MemberCount == 0 and nGuildB_MemberCount > 0 then
	        return 1
	    else
	        return 0
	    end
	end

    return 1
end

----------------------------------------------------------------------------------------------
--奖励
----------------------------------------------------------------------------------------------
function x300918_BattleBonus( sceneId,selfId,battleResult )

	local nScriptId = x300918_GetLairdBattleSceneScript( sceneId )
    if  nScriptId == 0 then
        return
    end

end

----------------------------------------------------------------------------------------------
--玩家骑马控制
----------------------------------------------------------------------------------------------
function x300918_LairdBattleBonus( sceneId ,battleResult )

    local nHumanCount = GetScenePlayerCount( sceneId )
    local i = 0
    for i = 0,nHumanCount-1 do
        local objId = GetScenePlayerObjId( sceneId,i)
        if objId >= 0 then
            x300918_BattleBonus( sceneId,objId,battleResult)
        end
    end
end


----------------------------------------------------------------------------------------------
--恢复阵营
----------------------------------------------------------------------------------------------
function x300918_RestorePlayerCamp( sceneId,selfId )
    local nCountryId = GetCurCountry( sceneId,selfId )
    SetCurCamp(sceneId,selfId,nCountryId )
end

----------------------------------------------------------------------------------------------
--恢复阵营
----------------------------------------------------------------------------------------------
function x300918_RestoreAllPlayerCamp( sceneId )

    local nHumanCount = GetScenePlayerCount( sceneId )
    local i = 0
    for i = 0,nHumanCount-1 do
        local objId = GetScenePlayerObjId( sceneId,i)
        if objId >= 0 then
            local nCountryId = GetCurCountry( sceneId,objId )
            SetCurCamp(sceneId,objId,nCountryId )
        end
    end
end


----------------------------------------------------------------------------------------------
--生成帮战结果
----------------------------------------------------------------------------------------------
function x300918_BattleGenResult( sceneId, callerId  )
    
    local nGuildA = x300918_g_GuildA[sceneId]
    local nGuildB = x300918_g_GuildB[sceneId]

    local nLairdMapId = x300918_g_LairdMapID[sceneId]

    if nGuildA == nGuildB then
        return
    end

--    local nWinner = x300918_GetWinner( sceneId )
--    if nWinner == 0 then
--        --挑战方获取
--
--        local strGuildName = GetGuildName(nGuildA)
--        local strGuildLeaderName = GetGuildLeaderName(nGuildA)
--        local strLairdSceneName = x300918_GetLairdSceneInfo_Name(nLairdMapId)
--        
--        local str = format("#G%s帮会获得%s【国家】领主战场的胜利，%s坐上了领主的宝座。 ",strGuildName,strLairdSceneName,strGuildLeaderName)
--        LuaAllScenceM2Wrold(sceneId, str, 2, 1)
--        LuaAllScenceM2Wrold(sceneId, str, 3, 1)
--
--        GameBattleSendResultToGL( x300918_g_BattleType,0,x300918_g_LairdMapID[sceneId],x300918_g_GuildA[sceneId],x300918_g_GuildB[sceneId])
--
--    else
--        --据点方获取
--        local strGuildName = GetGuildName(nGuildB)
--        local strGuildLeaderName = GetGuildLeaderName(nGuildB)
--        local strLairdSceneName = x300918_GetLairdSceneInfo_Name(nLairdMapId)
--        
--        local str = format("#G%s帮会团结一致的顶住了挑战，卫冕了%s领主的宝座。  ",strGuildName,strLairdSceneName )
--        if x300918_g_HasLaird[sceneId] == 0 then
--        	str = format("#G%s帮会获得%s【国家】领主战场的胜利，%s坐上了领主的宝座。 ",strGuildName,strLairdSceneName,strGuildLeaderName)
--        end
--        LuaAllScenceM2Wrold(sceneId, str, 2, 1)
--        LuaAllScenceM2Wrold(sceneId, str, 3, 1)
--
--        GameBattleSendResultToGL( x300918_g_BattleType,1,x300918_g_LairdMapID[sceneId],x300918_g_GuildA[sceneId],x300918_g_GuildB[sceneId])
--    end

    --进入倒计时状态,并设置倒计时间
    x300918_g_CountDownState[sceneId] = 1
    x300918_g_CountDownTime[sceneId] = 10

    local nTime = x300918_g_CountTime[sceneId]
        
    --记录日志
    local msg = format("LBL:x300918_BattleGenResult SceneId=%d,LeaveTime h= %d,m=%d,CallerId=%d",sceneId, floor(nTime/60),mod(nTime,60), callerId )
    WriteLog(1,msg)

    x300918_g_GuildA[sceneId] = -1
    x300918_g_GuildB[sceneId] = -1
    
    x300918_g_CountryA[sceneId] = -1
    x300918_g_CountryB[sceneId] = -1
    
    x300918_g_GuildAidA[sceneId]					= {}
	x300918_g_GuildAidB[sceneId]					= {}

    --x300918_SetAllPlayerNeedKick(sceneId)
    --ClearLairdBattleSceneData(sceneId)
    
end

----------------------------------------------------------------------------------------------
--踢人
----------------------------------------------------------------------------------------------
function x300918_LairdBattleKickPlayer( sceneId,selfId )

    x300918_DoPlayerRelive( sceneId,selfId )

    x300918_RestorePlayerCamp( sceneId,selfId)

    --只要玩家离开战场，将进场景标记置否
    SetPlayerRuntimeData(sceneId,selfId,RD_BATTLESCENE_ENTER_FLAG,0)

    --如果存在BakScene信息，则以BakScene信息为准
    local nBakSceneId,x,z = GetPlayerBakSceneInfo(sceneId,selfId )
    if nBakSceneId >= 0 then
        NewWorld(sceneId,selfId,nBakSceneId,x,z,300918)
        return
    end

    --选择一个合适的场景传送出去
    local nCountry = GetCurCountry(sceneId,selfId)
    if nCountry == 0 then
        
        --楼兰
        local nDestSceneId = 50
        local nPosX = 123
        local nPosZ = 57

        NewWorld(sceneId,selfId,nDestSceneId,nPosX,nPosZ,300918)

    elseif nCountry == 1 then
        
        --天山
        local nDestSceneId = 150
        local nPosX = 123
        local nPosZ = 57

        NewWorld(sceneId,selfId,nDestSceneId,nPosX,nPosZ,300918)

    elseif nCountry == 2 then

        --昆仑
        local nDestSceneId = 250
        local nPosX = 123
        local nPosZ = 57

        NewWorld(sceneId,selfId,nDestSceneId,nPosX,nPosZ,300918)

    elseif nCountry == 3 then
        
        --敦煌
        local nDestSceneId = 350
        local nPosX = 123
        local nPosZ = 57

        NewWorld(sceneId,selfId,nDestSceneId,nPosX,nPosZ,300918)

    end
end

----------------------------------------------------------------------------------------------
--踢掉场景里所有的人
----------------------------------------------------------------------------------------------
function x300918_LairdBattleKickAllPlayer( sceneId )
    
    local nHumanCount = GetScenePlayerCount( sceneId )
    local i = 0
    for i = 0,nHumanCount-1 do
        local objId = GetScenePlayerObjId( sceneId,i)
        if objId >= 0 then
            
            x300918_LairdBattleKickPlayer( sceneId,objId)

        end
    end
end


----------------------------------------------------------------------------------------------
--同步帮战倒计时给全部玩家（当前场景）
----------------------------------------------------------------------------------------------
function x300918_SyncBattleTimeToAllPlayer( sceneId ,nTime )

    local nHumanCount = GetScenePlayerCount( sceneId )
    local i = 0
    for i = 0,nHumanCount-1 do
        local objId = GetScenePlayerObjId( sceneId,i)
        if objId >= 0 then

            TimerCommand( sceneId, objId, 1, GUILDBATTLE_TIMERID, GUILDBATTLE_TIMERTYPE, GUILDBATTLE_SCRIPTID,-1,-1);                 --先强制关闭

            if nTime > 0 then
                TimerCommand( sceneId, objId, 2, GUILDBATTLE_TIMERID, GUILDBATTLE_TIMERTYPE, GUILDBATTLE_SCRIPTID, nTime, nTime );
            end
        end
    end    
end

----------------------------------------------------------------------------------------------
--同步帮战倒计时关闭信息给全部玩家（当前场景）
----------------------------------------------------------------------------------------------
function x300918_SyncBattleTimeCloseToAllPlayer(sceneId )
    
    local nHumanCount = GetScenePlayerCount( sceneId )
    local i = 0
    for i = 0,nHumanCount-1 do
        local objId = GetScenePlayerObjId( sceneId,i)
        if objId >= 0 then

            TimerCommand( sceneId, objId, 1, GUILDBATTLE_TIMERID, GUILDBATTLE_TIMERTYPE, GUILDBATTLE_SCRIPTID,-1,-1);                 --先强制关闭
        end
    end    

end

----------------------------------------------------------------------------------------------
--同步帮会势力
----------------------------------------------------------------------------------------------
function x300918_SyncGuildPower( sceneId )
    
    local nGuildA = x300918_g_GuildA[sceneId]
    local nGuildB = x300918_g_GuildB[sceneId]

    local nGuildA_Count = 0
    local nGuildB_Count = 0

    --统计玩家数量，由于不能处理玩家掉线的情况，所以在这里必须主动同步玩家数据
    local nHumanCount = GetScenePlayerCount( sceneId )
    local i = 0
    for i = 0,nHumanCount-1 do
        local objId = GetScenePlayerObjId( sceneId,i)
        if objId >= 0 then
            local nGuildId = GetGuildID( sceneId,objId )
            if nGuildId == nGuildA or x300918_IsPlayerAidA(sceneId,objId) == 1 then
                nGuildA_Count = nGuildA_Count + 1
            elseif nGuildId == nGuildB or x300918_IsPlayerAidB(sceneId,objId) == 1 then
                nGuildB_Count = nGuildB_Count + 1
            end
        end
    end

    --同步给玩家
    local nHumanCount = GetScenePlayerCount( sceneId )
    local i = 0
    for i = 0,nHumanCount-1 do
        local objId = GetScenePlayerObjId( sceneId,i)
        if objId >= 0 then
            GameBattleSyncPowerInfo(sceneId,objId,nGuildA_Count,nGuildB_Count,2)
        end
    end

end

----------------------------------------------------------------------------------------------
--更新小地图
----------------------------------------------------------------------------------------------
function x300918_UpdateSceneDataFlag( sceneId )

    local nScriptId = x300918_GetLairdBattleSceneScript( sceneId )
    if  nScriptId == 0 then
        return
    end
    
    ClearSceneMapDataFlag( sceneId )

	-- SetSceneMapDataFlag( sceneId,10,8,"申请方传送者",73,180,-1)
	-- SetSceneMapDataFlag( sceneId,11,8,"据点方传送者",215,47,-1)

    --更新帮主的位置
    local GuildLeaderA = -1
    local GuildLeaderB = -1
    
    local nGuildA = x300918_g_GuildA[sceneId]
    local nGuildB = x300918_g_GuildB[sceneId]

    local nHumanCount = GetScenePlayerCount( sceneId )
    local i = 0
    for i = 0,nHumanCount-1 do
        local objId = GetScenePlayerObjId( sceneId,i)
        if objId >= 0 then
            
            local pos = GetGuildOfficial(sceneId, objId)
	        if pos == x300918_g_Leader_Index then
                local nGuild = GetGuildID( sceneId,objId )
                if nGuild == nGuildA then
                    GuildLeaderA = objId
                elseif nGuild == nGuildB then
                    GuildLeaderB = objId
                end
            end
        end
    end


    local a_leader_name = ""
    local a_leader_x = 0
    local a_leader_z = 0
    
    if GuildLeaderA > 0 then
        
        a_leader_name = GetName(sceneId,GuildLeaderA)
        a_leader_x,a_leader_z = GetWorldPos(sceneId,GuildLeaderA)
    end

    local b_leader_name = ""
    local b_leader_x = 0
    local b_leader_z = 0
    
    if GuildLeaderB > 0 then

        b_leader_name = GetName(sceneId,GuildLeaderB)
        b_leader_x,b_leader_z = GetWorldPos(sceneId,GuildLeaderB)
    end

    --发送帮主状态
    local nHumanCount = GetScenePlayerCount( sceneId )
    local i = 0
    for i = 0,nHumanCount-1 do
        local objId = GetScenePlayerObjId( sceneId,i)
        if objId >= 0 then
            
            if GuildLeaderA > 0 and GuildLeaderA ~= objId then
                SetSceneMapDataFlagToPlayer( sceneId,objId,12,8,a_leader_name,a_leader_x,a_leader_z,-1)
            end

            if GuildLeaderB > 0 and GuildLeaderB ~= objId then
                SetSceneMapDataFlagToPlayer( sceneId,objId,13,8,b_leader_name,b_leader_x,b_leader_z,-1)
            end
        end
    end
end

----------------------------------------------------------------------------------------------
--从GLServer过来的同步领主战场时间的东东
----------------------------------------------------------------------------------------------
function x300918_OnSyncLairdBattleTime( sceneId,nTime )
    
    if x300918_GetLairdBattleSceneScript( sceneId ) == 0 then
        return
    end

    local nTime_new = x300918_g_TotalBattleTime - NumberCastIntToUInt( nTime )
    x300918_g_CountTime[sceneId] = nTime_new
    
    if x300918_g_GuildA[sceneId] ~= -1 then
    	WriteLog(1,"LBL:x300918_OnSyncLairdBattleTime x300918_g_CountTime[sceneId]=%d",x300918_g_CountTime[sceneId])
    end

    --定时器时间同步
    ----------------------------------------------------------------------------------------------
    --x300918_SyncBattleTimeToAllPlayer( sceneId, nTime_new )
end

----------------------------------------------------------------------------------------------
--设置所有玩家需要踢掉
----------------------------------------------------------------------------------------------
function x300918_SetAllPlayerNeedKick( sceneId )
    
    local nHumanCount = GetScenePlayerCount( sceneId )
    local i = 0
    for i = 0,nHumanCount-1 do
        local objId = GetScenePlayerObjId( sceneId,i)
        if objId >= 0 then
            local KickDown = GetPlayerRuntimeData( sceneId,objId,RD_BATTLE_SCENE_KICK_DOWN ) 
            if KickDown <= 0 or KickDown > x300918_g_Kick_Down then                
                SetPlayerRuntimeData( sceneId,objId,RD_BATTLE_SCENE_KICK_DOWN ,x300918_g_Kick_Down) 
            end
        end
    end
end

----------------------------------------------------------------------------------------------
--更新玩家踢掉状态
----------------------------------------------------------------------------------------------
function x300918_UpdatePlayerKickState( sceneId )
    
    local nHumanCount = GetScenePlayerCount( sceneId )
    local i = 0
    for i = 0,nHumanCount-1 do
        local objId = GetScenePlayerObjId( sceneId,i)
        if objId >= 0 then
            local KickDown = GetPlayerRuntimeData( sceneId,objId,RD_BATTLE_SCENE_KICK_DOWN ) 
            if KickDown > 0 then                
                KickDown = KickDown - 1 
                if KickDown == 0 then
                    --倒计时为零，踢掉
                    SetPlayerRuntimeData( sceneId,objId,RD_BATTLE_SCENE_KICK_DOWN ,-1) 
                    x300918_LairdBattleKickPlayer( sceneId,objId )                    
                else
                    --否则，继续倒计时
                    SetPlayerRuntimeData( sceneId,objId,RD_BATTLE_SCENE_KICK_DOWN ,KickDown) 
                end
            end
        end
    end
end

----------------------------------------------------------------------------------------------
--怪物事件-创建BOSS
----------------------------------------------------------------------------------------------
function x300918_CreateBoss(sceneId)

	x300918_DestroyBoss(sceneId)

	x300918_g_BossA[sceneId] = {}
	x300918_g_BossB[sceneId] = {}

	--如果不超过指定数量,则认为可以创建新的怪物
	local nIndexFrom = GetFubenDataPosByScriptID( x300918_g_scriptId )
	local nDataCount = GetFubenDataCountByScriptID( x300918_g_scriptId )
	
	--记录日志
	local msg = format("LBL:x300918_CreateBoss before sceneId=%d,monstercount=%d,si = %d,sc = %d",sceneId,GetMonsterCount(sceneId),nIndexFrom,nDataCount)
	WriteLog(1,msg)
	
	for i = 0,nDataCount-1 do
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x300918_g_scriptId,nIndexFrom,i)
		
		
		
		if idScript == x300918_g_scriptId then
			
            for j=0,count -1 do
            
            	local lx = x + random(-r,r)
            	local lz = z + random(-r,r)
            	
            	if flag == 0 and flag1 >= 1 and flag1 <= 3  then
            	
            		--A阵营的BOSS
					if title~="" then
						local objId = CreateMonster(sceneId, type, lx, lz, ai, aiscript, x300918_g_scriptId, -1, camp, -1,facedir, "", title)
						x300918_g_BossA[sceneId][flag1] = objId
					else
						local objId = CreateMonster(sceneId, type, lx, lz, ai, aiscript, x300918_g_scriptId, -1, camp, -1,facedir)
						x300918_g_BossA[sceneId][flag1] = objId
					end
					
				elseif flag == 1 and flag1 >= 1 and flag1 <= 3 then
					
					--B阵营的BOSS
					if title~="" then
						local objId = CreateMonster(sceneId, type, lx, lz, ai, aiscript, x300918_g_scriptId, -1, camp, -1,facedir, "", title)
						x300918_g_BossB[sceneId][flag1] = objId
					else
						local objId = CreateMonster(sceneId, type, lx, lz, ai, aiscript, x300918_g_scriptId, -1, camp, -1,facedir)
						x300918_g_BossB[sceneId][flag1] = objId
					end
				end
			end
        end
	end
	
	--记录日志
	msg = format("LBL:x300918_CreateBoss after sceneId=%d,monstercount=%d",sceneId,GetMonsterCount(sceneId))
	WriteLog(1,msg)
end

----------------------------------------------------------------------------------------------
--怪物事件-删除BOSS
----------------------------------------------------------------------------------------------
function x300918_DestroyBoss(sceneId)
	
	if x300918_g_BossA[sceneId] ~= nil then
	
		--清除A方BOSS
		for i,item in x300918_g_BossA[sceneId] do
			
			if item >=0 and IsObjValid(sceneId,item) == 1 and GetHp(sceneId,item) > 0 then
				DeleteMonster(sceneId,item)
			end
		end
		
		x300918_g_BossA[sceneId] = nil
	
	end
	
	
	if x300918_g_BossB[sceneId] ~= nil then
	
		--清除B方BOSS
		for i,item in x300918_g_BossB[sceneId] do
			
			if item >=0 and IsObjValid(sceneId,item) == 1 and GetHp(sceneId,item) > 0 then
				DeleteMonster(sceneId,item)
			end
		end
		
		x300918_g_BossB[sceneId] = nil
		
	end
	
end


----------------------------------------------------------------------------------------------
--产生领主操作
----------------------------------------------------------------------------------------------
function x300918_OnGenerateLaird(sceneId,nResult,nGuildA,nGuildB )
	
	GameBattleSendResultToGL( x300918_g_BattleType,nResult,x300918_g_LairdMapID[sceneId],nGuildA,nGuildB)
	
end

----------------------------------------------------------------------------------------------
--产生暗道天变
----------------------------------------------------------------------------------------------
function x300918_ProcLairdLevelup(sceneId,nLairdMapId)
	
	local nRandom = random(1,100)
	if nRandom > 10 then
		return
	end
	
	local _,strLairdSceneName = GetBattleSceneNameNM(nLairdMapId)
	local nLairdSceneLevel = GetSceneLairdLevel(nLairdMapId)
	local strMsg = nil
	
	if sceneId == 76 then
		
		
		CreateMonster(sceneId, 3059, 211, 203, 24, -1, -1, -1, 21, -1, 0, "", "" )
		strMsg = format("%s图腾升级，触发天变，楼兰暗道出现天龙之魂",strLairdSceneName)
		
	elseif sceneId == 176 then
	
		CreateMonster(sceneId, 3059,  43,  35, 24, -1, -1, -1, 21, -1, 0, "", "" )
		strMsg = format("%s图腾升级，触发天变，天山暗道出现天龙之魂",strLairdSceneName)

	elseif sceneId == 276 then
	
		CreateMonster(sceneId, 3059, 211, 203, 24, -1, -1, -1, 21, -1, 0, "", "" )
		strMsg = format("%s图腾升级，触发天变，昆仑暗道出现天龙之魂",strLairdSceneName)

	elseif sceneId == 376 then
	
		CreateMonster(sceneId, 3059,  43,  35, 24, -1, -1, -1, 21, -1, 0, "", "" )
		strMsg = format("%s图腾升级，触发天变，敦煌暗道出现天龙之魂",strLairdSceneName)
		
	end
	
	if strMsg ~= nil then
	
		
	
		LuaAllScenceM2Wrold(sceneId,strMsg,CHAT_PLANE_SCROLL,1)
		LuaAllScenceM2Wrold(sceneId,strMsg,CHAT_LEFTDOWN,1)
		LuaAllScenceM2Wrold(sceneId,strMsg,CHAT_MAIN_RIGHTDOWN,1)
	end
	
	
end

----------------------------------------------------------------------------------------------
--怪物事件-怪物死亡处理
----------------------------------------------------------------------------------------------
function x300918_OnDie(sceneId,selfId,killerId)
	
	--如果是宠物杀死,需要取得主人的信息
	local ObjType = GetObjType(sceneId, killerId)
	if ObjType == 3 then
		ObjType = 1
		killerId = GetOwnerID(sceneId, killerId)
	end
	
	--检查玩家是否有效
	if killerId < 0 or IsPlayerStateNormal(sceneId,killerId) ~= 1 then
		--如果玩家无效，这里不能做其他处理
		return
	end

    --检查是否是领主战场场景列表中所处理的情况，如果不是，则不处理
    local nScriptId = x300918_GetLairdBattleSceneScript( sceneId )
    if  nScriptId == 0 then
        return
    end

	--战场是否开启
    local status = x300918_g_BattleState[sceneId]
    if status ~= x300918_g_Laird_BeginBattle then
        return
    end

	--处理战争结果
	local nGuildId = GetGuildID(sceneId,killerId)
	local nGuildA = x300918_g_GuildA[sceneId]
	local nGuildB = x300918_g_GuildB[sceneId]
	
	if nGuildA == nGuildB then
		return
	end
	
	local nCountryID = GetCurCountry(sceneId,killerId)
	
	if nCountryID == x300918_g_CountryA[sceneId]  then
		x300918_OnGenerateLaird(sceneId,0,nGuildA,nGuildB )
		
        local strGuildName = GetGuildName(nGuildA)
        local strGuildLeaderName = GetGuildLeaderName(nGuildA)
        local strLairdSceneName = x300918_GetLairdSceneInfo_Name(sceneId)
        
        local str = format("#G%s帮会在帮主%s的带领下占领了%s。",strGuildName,strGuildLeaderName,strLairdSceneName)
        LuaAllScenceM2Wrold(sceneId, str, 2, 1)
        LuaAllScenceM2Wrold(sceneId, str, 3, 1)
        
        local nCampId = GetCurCountry(sceneId,killerId) + 16
        SetMonsterCamp(sceneId,selfId,nCampId)
		
	elseif nCountryID == x300918_g_CountryB[sceneId]  then
		x300918_OnGenerateLaird(sceneId,1,nGuildA,nGuildB )
		
		local strGuildName = GetGuildName(nGuildB)
        local strGuildLeaderName = GetGuildLeaderName(nGuildB)
        local strLairdSceneName = x300918_GetLairdSceneInfo_Name(sceneId)
        
        local str = format("#G%s帮会在帮主%s的带领下占领了%s。",strGuildName,strGuildLeaderName,strLairdSceneName)
        LuaAllScenceM2Wrold(sceneId, str, 2, 1)
        LuaAllScenceM2Wrold(sceneId, str, 3, 1)
        
        local nCampId = GetCurCountry(sceneId,killerId) + 16
        SetMonsterCamp(sceneId,selfId,nCampId)
	end
	
--	--A方怪物的死亡处理	
--	local nBossACount = getn(x300918_g_BossA[sceneId])
--	for i,item in x300918_g_BossA[sceneId] do
--	
--		if item == selfId then
--			if i < nBossACount then
--				
--				--不是最后一个的处理
--				--local objId = x300918_g_BossA[sceneId][i+1]
--				--if objId >=0 and IsObjValid(sceneId,objId) == 1 and GetHp(sceneId,objId) > 0 then
--				--	SetMonsterCamp(sceneId,objId,x300918_g_Guild_Camp_A)
--				--end
--				x300918_g_BossA[sceneId][i] = -1
--				x300918_g_ScoreB[sceneId] = x300918_g_ScoreB[sceneId] + 50
--				x300918_OnBossDie(sceneId, 0 )
--				x300918_LairdSyncGuildScore(sceneId)
--				local msg = "斯拉夫联军的战旗守护被亚洲联军击杀"
--				LuaThisScenceM2Wrold( sceneId,msg,3,1)
--				LuaThisScenceM2Wrold( sceneId,msg,2,1)
--				return
--				
--			else
--				--最后一个的处理
--				x300918_g_IntervalScoreB[sceneId] = 1000000
--				x300918_BattleGenResult( sceneId,2)
--				local msg = "斯拉夫联军的战旗被亚洲联军夺走"
--				LuaThisScenceM2Wrold( sceneId,msg,3,1)
--				LuaThisScenceM2Wrold( sceneId,msg,2,1)
--				return
--			end
--			
--		end
--		
--	end
--	
--	--B方怪物的死亡处理
--	local nBossBCount = getn(x300918_g_BossB[sceneId])
--	for i,item in x300918_g_BossB[sceneId] do
--	
--		if item == selfId then
--			if i < nBossBCount then
--				
--				--不是最后一个的处理
--				--local objId = x300918_g_BossB[sceneId][i+1]
--				--if objId >=0 and IsObjValid(sceneId,objId) == 1 and GetHp(sceneId,objId) > 0 then
--				--	SetMonsterCamp(sceneId,objId,x300918_g_Guild_Camp_B)
--				--end
--				x300918_g_BossB[sceneId][i] = -1
--				x300918_g_ScoreA[sceneId] = x300918_g_ScoreA[sceneId] + 50
--				x300918_OnBossDie(sceneId, 1 )
--    			x300918_LairdSyncGuildScore(sceneId)
--				local msg = "亚洲联军的战旗守护被斯拉夫联军击杀"
--				LuaThisScenceM2Wrold( sceneId,msg,3,1)
--				LuaThisScenceM2Wrold( sceneId,msg,2,1)
--				return
--			else
--				--最后一个的处理
--				x300918_g_IntervalScoreA[sceneId] = 1000000
--				x300918_BattleGenResult( sceneId,3)
--				local msg = "亚洲联军的战旗被斯拉夫联军夺走"
--				LuaThisScenceM2Wrold( sceneId,msg,3,1)
--				LuaThisScenceM2Wrold( sceneId,msg,2,1)
--				return
--			end
--		end
--	end
end

----------------------------------------------------------------------------------------------
--怪物死亡处理
----------------------------------------------------------------------------------------------
function x300918_OnBossDie(sceneId, flag )

	if flag == 0 then
		
		local nBossACount = getn(x300918_g_BossA[sceneId])
		local nBossADieCount = 0
		for i,item in x300918_g_BossA[sceneId] do
			if x300918_g_BossA[sceneId][i] == -1 then
				nBossADieCount = nBossADieCount + 1
			end			
		end
		
		if nBossADieCount == nBossACount -1 then
			
			local objId = x300918_g_BossA[sceneId][nBossACount]
			if objId >=0 and IsObjValid(sceneId,objId) == 1 and GetHp(sceneId,objId) > 0 then
				SetMonsterCamp(sceneId,objId,x300918_g_Guild_Camp_A)
			end
		end
		
	elseif flag == 1 then
		
		local nBossBCount = getn(x300918_g_BossB[sceneId])
		local nBossBDieCount = 0
		for i,item in x300918_g_BossB[sceneId] do
			if x300918_g_BossB[sceneId][i] == -1 then
				nBossBDieCount = nBossBDieCount + 1
			end			
		end
		
		if nBossBDieCount == nBossBCount -1 then
			
			local objId = x300918_g_BossB[sceneId][nBossBCount]
			if objId >=0 and IsObjValid(sceneId,objId) == 1 and GetHp(sceneId,objId) > 0 then
				SetMonsterCamp(sceneId,objId,x300918_g_Guild_Camp_B)
			end
		end
	end	
end

----------------------------------------------------------------------------------------------
--采集点事件-取得门A类型
----------------------------------------------------------------------------------------------
function x300918_GetDoorA(sceneId)
	return x300918_g_DoorGrowPointA
end

----------------------------------------------------------------------------------------------
--采集点事件-取得门B类型
----------------------------------------------------------------------------------------------
function x300918_GetDoorB(sceneId)	
	return x300918_g_DoorGrowPointB
end

----------------------------------------------------------------------------------------------
--采集点事件-重置门A
----------------------------------------------------------------------------------------------
function x300918_ResetDoorA(sceneId)

	x300918_g_DoorGrowPointA_LairdState[sceneId] = { LairdCountDownState = 0,LairdCountDownTime = -1,LairdCamp = -1 }
	RecycleGrowPointByType(sceneId,x300918_g_DoorGrowPointA,1000)
	
	local msg = format("LBL:x300918_ResetDoorA sceneId=%d",sceneId)
	WriteLog(1,msg)
end

----------------------------------------------------------------------------------------------
--采集点事件-重置门B
----------------------------------------------------------------------------------------------
function x300918_ResetDoorB(sceneId)
	x300918_g_DoorGrowPointB_LairdState[sceneId] = { LairdCountDownState = 0,LairdCountDownTime = -1,LairdCamp = -1 }
	RecycleGrowPointByType(sceneId,x300918_g_DoorGrowPointB,1000)
	
	local msg = format("LBL:x300918_ResetDoorB sceneId=%d",sceneId)
	WriteLog(1,msg)
end


----------------------------------------------------------------------------------------------
--采集点事件-A方 检查是否可以开始
----------------------------------------------------------------------------------------------
function x300918_OnOpenDoorA_Check(sceneId,selfId)
	
	--阵营检查
	local nCampId = GetCurCamp(sceneId,selfId)
	if nCampId ~= x300918_g_Guild_Camp_B then
		return 1
	end

	return 0	
end

----------------------------------------------------------------------------------------------
--采集点事件-A方 检查是否可以开始
----------------------------------------------------------------------------------------------
function x300918_OnOpenDoorB_Check(sceneId,selfId)

	--阵营检查
	local nCampId = GetCurCamp(sceneId,selfId)
	if nCampId ~= x300918_g_Guild_Camp_A then
		return 1
	end
	
	return 0
end

----------------------------------------------------------------------------------------------
--采集点事件-处理A方
----------------------------------------------------------------------------------------------
function x300918_OnOpenDoorA(sceneId,selfId)
	
	--阵营检查
	local nCampId = GetCurCamp(sceneId,selfId)
	if nCampId ~= x300918_g_Guild_Camp_B then
		return 0
	end

	--禁用特效
	x300918_g_TempImpassable_Door2_State[sceneId][1] = 0
	
	--清除动态阻挡
	x300918_ClearTempImpassable_Door2(sceneId,1)
	
	--清除生长点
	SetGrowPointIntervalContainer(sceneId,x300918_g_DoorGrowPointA,-1)
	
	--给出相关提示
	local msg = "斯拉夫联军内城大门被亚洲联军攻破"
	LuaThisScenceM2Wrold( sceneId,msg,3,1)
	LuaThisScenceM2Wrold( sceneId,msg,2,1)
	
	local msg = format("LBL:x300918_OnOpenDoorA sceneId=%d",sceneId)
	WriteLog(1,msg)
	
	return 1	
end

----------------------------------------------------------------------------------------------
--采集点事件-处理B方
----------------------------------------------------------------------------------------------
function x300918_OnOpenDoorB(sceneId,selfId)

	--阵营检查
	local nCampId = GetCurCamp(sceneId,selfId)
	if nCampId ~= x300918_g_Guild_Camp_A then
		return 0
	end

	--禁用特效
	x300918_g_TempImpassable_Door2_State[sceneId][2] = 0
	
	--清除动态阻挡
	x300918_ClearTempImpassable_Door2(sceneId,2)
	
	--清除生长点
	SetGrowPointIntervalContainer(sceneId,x300918_g_DoorGrowPointB,-1)
	
	--给出相关提示
	local msg = "亚洲联军内城大门被斯拉夫联军攻破"
	LuaThisScenceM2Wrold( sceneId,msg,3,1)
	LuaThisScenceM2Wrold( sceneId,msg,2,1)
	
	local msg = format("LBL:x300918_OnOpenDoorB sceneId=%d",sceneId)
	WriteLog(1,msg)
	
	return 1
end

----------------------------------------------------------------------------------------------
--动态阻挡-设置动态阻挡1的特效
----------------------------------------------------------------------------------------------
function x300918_SetTempImpassable_Door1_Effect(sceneId,selfId)
	
	if x300918_g_CountTime[sceneId] <= 18*60 then
		return
	end
	
	for i,itm in x300918_g_TempImpassable_Door1_Effect do
		CallScriptFunction(UTILITY_SCRIPT,"PlayEffect",sceneId,selfId,itm )		
	end
	
	
	local msg = format("LBL:x300918_SetTempImpassable_Door1_Effect sceneId=%d name=%s",sceneId,GetName(sceneId,selfId))
	WriteLog(1,msg)
	
end

----------------------------------------------------------------------------------------------
--动态阻挡-清除动态阻挡1的特效
----------------------------------------------------------------------------------------------
function x300918_ClearTempImpassable_Door1_Effect(sceneId,selfId)
	for i,itm in x300918_g_TempImpassable_Door1_Effect do
		CallScriptFunction(UTILITY_SCRIPT,"StopEffect",sceneId,selfId,itm )		
	end
	
	local msg = format("LBL:x300918_ClearTempImpassable_Door1_Effect sceneId=%d name=%s",sceneId,GetName(sceneId,selfId))
	WriteLog(1,msg)
end


----------------------------------------------------------------------------------------------
--动态阻挡-设置动态阻挡1
----------------------------------------------------------------------------------------------
function x300918_SetTempImpassable_Door1(sceneId)
	for i,itm in x300918_g_TempImpassable_Door1 do
		AddSceneTempImpassable(sceneId,itm.Left,itm.Top,itm.Right,itm.Bottom)
	end
	
	local msg = format("LBL:x300918_SetTempImpassable_Door1 sceneId=%d",sceneId)
	WriteLog(1,msg)
end

----------------------------------------------------------------------------------------------
--动态阻挡-清除动态阻挡1
----------------------------------------------------------------------------------------------
function x300918_ClearTempImpassable_Door1(sceneId)
	
	--广播开始
	LuaThisScenceM2Wrold( sceneId,"战斗开始",5,1)
	
	--删除动态阻挡
	for i,itm in x300918_g_TempImpassable_Door1 do
		DelSceneTempImpassable(sceneId,itm.Left,itm.Top,itm.Right,itm.Bottom)
	end
	
	--清除特效
	local nHumanCount = GetScenePlayerCount( sceneId )
    for i = 0,nHumanCount-1 do
        local objId = GetScenePlayerObjId( sceneId,i)
        if objId >= 0 and IsPlayerStateNormal(sceneId,objId) == 1 then
            x300918_ClearTempImpassable_Door1_Effect(sceneId,objId)
        end
    end
    
    --创建怪物
    x300918_CreateBoss(sceneId)
    
    local msg = format("LBL:x300918_ClearTempImpassable_Door1 sceneId=%d",sceneId)
	WriteLog(1,msg)
end

----------------------------------------------------------------------------------------------
--动态阻挡-设置动态阻挡2的特效
----------------------------------------------------------------------------------------------
function x300918_SetTempImpassable_Door2_Effect(sceneId,selfId)
	for i,itm in x300918_g_TempImpassable_Door2_State[sceneId] do
		if itm == 1 then
			CallScriptFunction(UTILITY_SCRIPT,"PlayEffect",sceneId,selfId,x300918_g_TempImpassable_Door2_Effect[i] )		
		end
	end	
	
	local msg = format("LBL:x300918_SetTempImpassable_Door2_Effect sceneId=%d name=%s",sceneId,GetName(sceneId,selfId))
	WriteLog(1,msg)
end

----------------------------------------------------------------------------------------------
--动态阻挡-清除动态阻挡2的特效
----------------------------------------------------------------------------------------------
function x300918_ClearTempImpassable_Door2_Effect(sceneId,selfId,nIndex)

	if nIndex < 1 or nIndex > getn(x300918_g_TempImpassable_Door2_Effect) then
		return
	end
	
	local itm = x300918_g_TempImpassable_Door2_Effect[nIndex]
	CallScriptFunction(UTILITY_SCRIPT,"StopEffect",sceneId,selfId,itm )
	
	local msg = format("LBL:x300918_ClearTempImpassable_Door2_Effect sceneId=%d name=%s index=%d",sceneId,GetName(sceneId,selfId),nIndex)
	WriteLog(1,msg)
end


----------------------------------------------------------------------------------------------
--动态阻挡-设置动态阻挡2
----------------------------------------------------------------------------------------------
function x300918_SetTempImpassable_Door2(sceneId)
	
	for i,itm in x300918_g_TempImpassable_Door2 do
		AddSceneTempImpassable(sceneId,itm.Left,itm.Top,itm.Right,itm.Bottom)
	end
	
	local msg = format("LBL:x300918_SetTempImpassable_Door2 sceneId=%d",sceneId)
	WriteLog(1,msg)
end

----------------------------------------------------------------------------------------------
--动态阻挡-清除动态阻挡2
----------------------------------------------------------------------------------------------
function x300918_ClearTempImpassable_Door2(sceneId,nIndex)
	
	if nIndex < 1 or nIndex > getn(x300918_g_TempImpassable_Door2) then
		return
	end
	
	--删除动态阻挡
	local itm = x300918_g_TempImpassable_Door2[nIndex]
	DelSceneTempImpassable(sceneId,itm.Left,itm.Top,itm.Right,itm.Bottom)
	
	--清除特效
	local nHumanCount = GetScenePlayerCount( sceneId )
    for i = 0,nHumanCount-1 do
        local objId = GetScenePlayerObjId( sceneId,i)
        if objId >= 0 and IsPlayerStateNormal(sceneId,objId) == 1 then
            x300918_ClearTempImpassable_Door2_Effect(sceneId,objId,nIndex)
        end
    end
    
    local msg = format("LBL:x300918_ClearTempImpassable_Door2_Effect sceneId=%d index=%d",sceneId,nIndex)
	WriteLog(1,msg)
end

----------------------------------------------------------------------------------------------
--同步积分变化 
----------------------------------------------------------------------------------------------
function x300918_LairdSyncGuildScore(sceneId)
	
--	local nHumanCount = GetScenePlayerCount( sceneId )
--    for i = 0,nHumanCount-1 do
--        local objId = GetScenePlayerObjId( sceneId,i)
--        if objId >= 0 and IsPlayerStateNormal(sceneId,objId) == 1 then
--            GameBattleSyncScoreInfo(sceneId,objId,x300918_g_ScoreA[sceneId],x300918_g_ScoreB[sceneId],2)
--        end
--    end
	
	
end

----------------------------------------------------------------------------------------------
--传送帮会帮同至此 
----------------------------------------------------------------------------------------------
function x300918_TransGuildMemberToAround(sceneId,selfId,campId,x,z)

	--有效性检查
	if IsPlayerStateNormal(sceneId,selfId) ~= 1 or GetHp(sceneId,selfId) <= 0 then
		return
	end
	
	--阵营检查
	local nSelfCamp = GetCurCamp(sceneId,selfId)
	if nSelfCamp ~= campId then
		return
	end
	
	local msg = "帮主使用了领主战场召集,将你召唤到他的身边!"

	--传送
	local nHumanCount = GetScenePlayerCount( sceneId )
    for i = 0,nHumanCount-1 do
        local objId = GetScenePlayerObjId( sceneId,i)
        if objId ~=  selfId and IsPlayerStateNormal(sceneId,objId) == 1 and GetHp(sceneId,objId) > 0 and GetCurCamp(sceneId,objId) == campId then
        	
        	local tx = x + random(-3,3)
        	local tz = z + random(-3,3)
        	
            SetPos(sceneId,objId,tx,tz)
            
            Msg2Player(sceneId, objId, msg, 8, 2)
            Msg2Player(sceneId, objId, msg, 8, 3)
        end
    end	
	
end

----------------------------------------------------------------------------------------------
--取得帮会A的积分 
----------------------------------------------------------------------------------------------
function x300918_GetBattleScoreA(sceneId)
	return x300918_g_ScoreA[sceneId]
end

----------------------------------------------------------------------------------------------
--取得帮会B的积分 
----------------------------------------------------------------------------------------------
function x300918_GetBattleScoreB(sceneId)
	return x300918_g_ScoreB[sceneId]
end

----------------------------------------------------------------------------------------------
--设置帮会A的积分 
----------------------------------------------------------------------------------------------
function x300918_SetBattleScoreA(sceneId,nScore)
	
	x300918_g_ScoreA[sceneId] = nScore
	
	if x300918_g_ScoreA[sceneId] < 0 then
		x300918_g_ScoreA[sceneId] = 0 
	end
	
	x300918_LairdSyncGuildScore(sceneId)	
end

----------------------------------------------------------------------------------------------
--设置帮会B的积分 
----------------------------------------------------------------------------------------------
function x300918_SetBattleScoreB(sceneId,nScore)
	x300918_g_ScoreB[sceneId] = nScore
	
	if x300918_g_ScoreB[sceneId] < 0 then
		x300918_g_ScoreB[sceneId] = 0 
	end
	
	x300918_LairdSyncGuildScore(sceneId)	
end


----------------------------------------------------------------------------------------------
--区域事件-进入区域事件A
----------------------------------------------------------------------------------------------
function x300918_ProcAreaEnteredA(sceneId, selfId, zoneId, MissionId)
end

----------------------------------------------------------------------------------------------
--区域事件-离开区域事件A
----------------------------------------------------------------------------------------------
function x300918_ProcAreaLeavedA(sceneId,selfId,zoneId,MissionId)
end

----------------------------------------------------------------------------------------------
--区域事件-进入区域事件B
----------------------------------------------------------------------------------------------
function x300918_ProcAreaEnteredB(sceneId, selfId, zoneId, MissionId)
end

----------------------------------------------------------------------------------------------
--区域事件-离开区域事件B
----------------------------------------------------------------------------------------------
function x300918_ProcAreaLeavedB(sceneId,selfId,zoneId,MissionId)
end