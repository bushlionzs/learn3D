---------------------------------------------------
-- File: fuben_foshou.lua
-- Author: ZP Wang
-- Created: 2008-12-19
-- Version: 0.1

----------------------------------------------------
--********************************
--	#define
--********************************
----------------------------------------------------

x700026_CSP_FUBENTYPE				= 	0
x700026_CSP_SCRIPTID				=	1
x700026_CSP_TICKCOUNT				= 	2
x700026_CSP_FROMSCENEID				= 	3
x700026_CSP_ISCLOSING				= 	4
x700026_CSP_LEAVECOUNTDOWN			= 	5
x700026_CSP_TEAMID					=	6
x700026_CSP_BACKSCENEX       		=   7
x700026_CSP_BACKSCENEZ      		=   8
x700026_CSP_FUBENLEVEL			=	9
x700026_CSP_KILLCOUNT				=	10
x700026_CSP_FUBEN_SCENE_ID			=	11
x700026_CSP_GAME_STEP				=	12
x700026_CSP_STEP_TICKCOUNT			=	13
x700026_CSP_NPC_ID					=	14
x700026_CSP_SCORE					=	15
x700026_CSP_KILLCOUNT				=	16
x700026_CSP_NEEDKILLCOUNT			=	17


x700026_CSP_RESULT_START			=	20

x700026_CSP_GP_BOXID_START			=	30
x700026_CSP_GP_ID_START				=	65

x700026_CSP_GP_POSIDX_START			=	200
x700026_CSP_HUMAN_COUNT				=	240
x700026_CSP_OBJID_START				=	241
x700026_CSP_GUID_START              =   248


-------------------------FUBEN type ---------------------------
x700026_ENTER_TYPE_TEAM			=	1
x700026_ENTER_TYPE_FUQI			=	2
x700026_ENTER_TYPE_BANGHUI		=	3
x700026_FubenEnterType			=	x700026_ENTER_TYPE_TEAM

------------------------Scene System Setting -----------------------------------

x700026_g_ScriptId 					= 700026
x700026_g_FubenName				= "【队伍】勾魂牌局"
x700026_g_SceneMapNavPath			= 	"fuben_fututabaceng/fuben_fututabaceng.nav"
x700026_g_NoUserTime				= 	30						--副本中没有人后可以继续保存的时间（单位：秒）
x700026_g_TickTime					= 	5						--回调脚本的时钟时间（单位：秒/次）
x700026_g_FubenType				= 	FUBEN_FOSHOU		    --副本类型
x700026_g_LimitTotalHoldTime		= 	540						--副本可以存活的时间（单位：次数）,如果此时间到了，则任务将会失败
x700026_g_TimeZoneBias				= 	0;
x700026_g_CloseTick					= 	6						--副本关闭前倒计时（单位：次数）
x700026_g_NoUserTime				= 	30						--副本中没有人后可以继续保存的时间（单位：秒）
x700026_g_DeadTrans					= 	0						--死亡转移模式，0：死亡后还可以继续在副本，1：死亡后被强制移出副本
x700026_g_Fuben_X					= 	21						--进入副本的位置X
x700026_g_Fuben_Z					= 	20						--进入副本的位置Z
x700026_g_Back_X					= 	310						--源场景位置X
x700026_g_Back_Z					= 	36						--源场景位置Z
x700026_g_BackScene					=	{0,0,0,0}
----------------------------- special for this Fuben --------------------

x700026_g_GPInterval		=	1000
x700026_g_GPInterval2		=	10000
x700026_g_IntervalList = {2,2*12,2*12,2*12,6}--{2,6,6,6,6}    -- 每个数值的意义： 结束n-1步，开始第n步


x700026_g_GrowPosLen		=	56
x700026_g_GrowPoint_PosList = {
							{x=26,z=63},
							{x=26,z=61},
							{x=26,z=59},
							{x=26,z=57},
							{x=26,z=65},
							{x=26,z=67},
							{x=26,z=69},
							{x=24,z=63},
							{x=24,z=61},
							{x=24,z=59},
							{x=24,z=57},
							{x=24,z=65},
							{x=24,z=67},
							{x=24,z=69},
							{x=22,z=63},
							{x=22,z=61},
							{x=22,z=59},
							{x=22,z=57},
							{x=22,z=65},
							{x=22,z=67},
							{x=22,z=69},
							{x=28,z=63},
							{x=28,z=61},
							{x=28,z=59},
							{x=28,z=57},
							{x=28,z=65},
							{x=28,z=67},
							{x=28,z=69},
							{x=30,z=63},
							{x=30,z=61},
							{x=30,z=59},
							{x=30,z=57},
							{x=30,z=65},
							{x=30,z=67},
                            {x=30,z=69},
							{x=32,z=63},
                            {x=32,z=61},
                            {x=32,z=59},
                            {x=32,z=57},
                            {x=32,z=65},
                            {x=32,z=67},
                            {x=32,z=69},
							{x=34,z=63},
                            {x=34,z=61},
                            {x=34,z=59},
                            {x=34,z=57},
                            {x=34,z=65},
                            {x=34,z=67},
                            {x=34,z=69},
							{x=20,z=63},
                            {x=20,z=61},
                            {x=20,z=59},
                            {x=20,z=57},
                            {x=20,z=65},
                            {x=20,z=67},
                            {x=20,z=69},
						}

x700026_g_Pai_NameList	=	{
								{id = 1	,name="1条"},
								{id = 2	,name="2条"},
								{id = 3	,name="3条"},
								{id = 4	,name="4条"},
								{id = 5	,name="5条"},
								{id = 6	,name="6条"},
								{id = 7	,name="7条"},
								{id = 8	,name="8条"},
								{id = 9	,name="9条"},
								{id = 10,name="1筒"},
								{id = 11,name="2筒"},
								{id = 12,name="3筒"},
								{id = 13,name="4筒"},
								{id = 14,name="5筒"},
								{id = 15,name="6筒"},
								{id = 16,name="7筒"},
								{id = 17,name="8筒"},
								{id = 18,name="9筒"},
								{id = 19,name="1万"},
								{id = 20,name="2万"},
								{id = 21,name="3万"},
								{id = 22,name="4万"},
								{id = 23,name="5万"},
								{id = 24,name="6万"},
								{id = 25,name="7万"},
								{id = 26,name="8万"},
								{id = 27,name="9万"},
								{id = 28,name="中"},
								{id = 29,name="发"},
								{id = 30,name="白"},
								{id = 31,name="东"},
								{id = 32,name="南"},
								{id = 33,name="西"},
								{id = 34,name="北"}
							}


x700026_g_Start_GPID		=	500

x700026_g_Buff1				=	14110

------------------------- limitted -------------------------------
x700026_g_DayCountUntil				=	10

x700026_g_LimitMembers				=	1


x700026_g_LevelMin					=   100
x700026_g_LevelMax					=   100

x700026_NeedKillMonster_Count		=	1

x700026_g_EnterTime					=	{                       --副本可进入时间段
											{min=0*60+0,  max=24*60+0},
										}

x700026_g_EnterDay					=	{0,1,2,3,4,5,6};


------------------------- Output Text ----------------------------------

x700026_g_EnterInfo					=	"\t银钩赌坊内的勾魂牌局是蓝胡子和赵金手共同设下的圈套，专门引诱江湖上阅历尚浅的少年侠士进入牌局，将他们所有的钱财骗光。明教前教主玉罗刹之子玉柱也被困其中，要救出玉柱等人，必须先破了蓝胡子和赵金手的勾魂牌局。\n#Y开放时间：#W全天\n#Y友情提示：#W组上几个志同道合的朋友，可以提高效率！\n#Y副本说明：#W在这个副本中，你可以获得意外的奖励！"
x700026_g_FuBenCreateOK				= 	"副本创建成功！"
x700026_g_FuBenCreateFailed			= 	"副本已达上限，请稍后再试！"
x700026_g_CountDownMessage			= 	"你将在%d秒后离开场景！"
x700026_g_TimeOutFailedMessage		= 	"副本时间到！即将被传出副本！"

x700026_str_NotTime				= "进入副本的时间未到"
x700026_str_UnderLevel			= format("你的等级不足%d级！", x700026_g_LevelMin)
x700026_str_UpLevel				= "等级过高"
x700026_str_TimesOver			= "超出当日次数限制"	
x700026_str_NotDay				= "今天不能进入副本"
------------------------- list -----------------------------------------

x700026_g_EnterPos                  =   {
                                            { idx = 1, x = 33, z=58 },
                                            { idx = 2, x = 31, z=58 },
                                            { idx = 3, x = 36, z=58 },
                                            { idx = 4, x = 33, z=61 },
                                            { idx = 5, x = 31, z=61 },
                                            { idx = 6, x = 36, z=61 },
                                        }
--出去位置
x700026_g_BackPos                  =   {
                                            { idx = 1, x = 259, z=272 },
                                            { idx = 2, x = 259, z=272 },
                                            { idx = 3, x = 259, z=272 },
                                            { idx = 4, x = 259, z=272 },
                                            { idx = 5, x = 259, z=272 },
                                            { idx = 6, x = 259, z=272 },
                                        }

x700026_g_SubmitNPC                 =   { type =25037,guid= 150537,x = 32, z=60, facedir =0, title="" }


x700026_g_GameNPC                 =   { type =25036,guid= 150538,x = 36, z=56, facedir=0, title="" }


--BOSS类型
x700026_g_BossCreate				=	{
                                            {levelmin =60, levelmax=64, name ="通灵筛子",   type= 26861,  x=37, z=59,  r=2, ai=7, aiscript=-1, facedir = 0, title = ""},
                                            {levelmin =65, levelmax=69, name ="通灵筛子",   type= 26862,  x=37, z=59,  r=2, ai=7, aiscript=-1, facedir = 0, title = ""},
                                            {levelmin =70, levelmax=74, name ="通灵筛子",   type= 26863,  x=37, z=59,  r=2, ai=7, aiscript=-1, facedir = 0, title = ""},
                                            {levelmin =75, levelmax=79, name ="通灵筛子",   type= 26864,  x=37, z=59,  r=2, ai=7, aiscript=-1, facedir = 0, title = ""},
                                            {levelmin =80, levelmax=84, name ="通灵筛子",   type= 26865,  x=37, z=59,  r=2, ai=7, aiscript=-1, facedir = 0, title = ""},
                                            {levelmin =85, levelmax=89, name ="通灵筛子",   type= 26866,  x=37, z=59,  r=2, ai=7, aiscript=-1, facedir = 0, title = ""},
                                            {levelmin =90, levelmax=94, name ="通灵筛子",   type= 26867,  x=37, z=59,  r=2, ai=7, aiscript=-1, facedir = 0, title = ""},
                                            {levelmin =95, levelmax=100, name ="通灵筛子",  type= 26868,  x=37, z=59,  r=2, ai=7, aiscript=-1, facedir = 0, title = ""},

										

										}
-------------------------
--***********************
--ProcEnumEvent
--***********************
-------------------------

function x700026_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
	--PrintStr("x700026_ProcEnumEvent")
	local level = GetLevel( sceneId,selfId )
    if level < x700026_g_LevelMin then
       return
    end

    if level > x700026_g_LevelMax then
		 return
    end
    
	AddQuestNumText(sceneId, x700026_g_ScriptId, x700026_g_FubenName,14,1);
	
end

---------------------------------------------------------------------------------------------------
--进入副本文字显示
---------------------------------------------------------------------------------------------------
function x700026_DispatchEnterInfo( sceneId, selfId, NPCId )

	BeginQuestEvent(sceneId)

		--任务信息
		AddQuestText(sceneId,"#Y"..x700026_g_FubenName)
		AddQuestText(sceneId,x700026_g_EnterInfo)
		--AddQuestText(sceneId," ")

		


	EndQuestEvent()
	DispatchQuestInfo(sceneId, selfId, NPCId, x700026_g_ScriptId, -1);
end


---------------------------------------------------------------------------------------------------
--申请进入副本
---------------------------------------------------------------------------------------------------
function x700026_ProcAcceptCheck( sceneId, selfId, NPCId )
    return 1
end

----------------------------------------------------------------------------------------------
--点确定后
----------------------------------------------------------------------------------------------
function x700026_ProcAccept( sceneId, selfId )

	x700026_OnRequestEnterFuben(sceneId, selfId);
end


-------------------------
--***********************
--ProcEventEntry
--***********************
-------------------------


function x700026_ProcEventEntry(sceneId, selfId, NPCId,nScriptId, nFlag)

	if nFlag== nil then
		return
	end

	
	

	x700026_DispatchEnterInfo( sceneId, selfId, NPCId )
	
end






function x700026_OnRequestEnterFuben(sceneId, selfId)
	local nRet = x700026_CheckRequest(sceneId, selfId)


	if nRet>0 then
		x700026_OnApproveRequestEnterFuben(sceneId, selfId, nRet)
	end
end

-----------------------------------------------------------
--*********************************************************
--OnFubenSceneCreated  :  当副本创建成功时， 开始刷怪和npc
--*********************************************************
-----------------------------------------------------------
function x700026_OnFubenSceneCreated( sceneId )
	-- @Param sceneId:  副本场景id
	
	
	local humancount = GetFuben_PlayerCount(sceneId);
	SetFubenData_Param(sceneId, x700026_CSP_HUMAN_COUNT, humancount);
	for	i = 0, humancount - 1 do
		local humanId = GetFuben_PlayerObjId(sceneId, i);
		--SetFubenData_Param(sceneId, x700026_CSP_OBJID_START+i, humanId);
	end
	
	SetFubenData_Param(sceneId, x700026_CSP_GAME_STEP, 0);
	SetFubenData_Param(sceneId, x700026_CSP_STEP_TICKCOUNT, 1);

	SetFubenData_Param(sceneId, x700026_CSP_SCORE, 0);
	

	for i=1, 34 do
		SetFubenData_Param(sceneId, x700026_CSP_GP_ID_START+i, -1);

		SetGrowPointIntervalContainer(sceneId,x700026_g_Start_GPID+i,-1)
	end



	x700026_CreateNpc( sceneId)
		
end



function x700026_CheckRequest(sceneId, selfId)

	local nRet = x700026_CheckCommonCondition(sceneId, selfId)

	if nRet<=0 then
		return 0;
	end

	
	
	if x700026_FubenEnterType == x700026_ENTER_TYPE_TEAM then

		nRet =  x700026_CheckTeamCondition(sceneId, selfId);
		if nRet>0 then
			return x700026_ENTER_TYPE_TEAM;
		end

	elseif x700026_FubenEnterType == x700026_ENTER_TYPE_FUQI then
		
		nRet =  x700026_CheckFuqiCondition(sceneId, selfId);
		if nRet>0 then
			return x700026_ENTER_TYPE_FUQI;
		end

	elseif x700026_FubenEnterType == x700026_ENTER_TYPE_BANGHUI then
		
		nRet =  x700026_CheckBanghuiCondition(sceneId, selfId);	
		if nRet>0 then
			return x700026_ENTER_TYPE_BANGHUI;
		end
	
	else
		--PrintStr("Error Enter Type List")
		return 0;
	end

	
	
	
	return 0;
end

function x700026_CheckCommonCondition(sceneId, selfId)

	
	local nRet = x700026_CheckCommonCondition_Day(sceneId, selfId)  -- Time

	if nRet <=0 then
		return 0;
	end
	
	local nRet = x700026_CheckCommonCondition_Time(sceneId, selfId)  -- Time

	if nRet <=0 then
		return 0;
	end
	
	local nRet = x700026_CheckCommonCondition_Level(sceneId, selfId)  -- level

	if nRet <=0 then
		return 0;
	end

	local nRet = x700026_CheckCommonCondition_Times(sceneId, selfId)  -- Times

	if nRet <=0 then
		return 0;
	end

	return 1;


	
end

function x700026_CheckCommonCondition_Time(sceneId, selfId)
	local hour,minute,sec =GetHourMinSec();
	local nowtime = hour*60+minute
	
	for i, item in x700026_g_EnterTime do
		if nowtime >= item.min and nowtime <= item.max then
			
			
			return 1;
			
		end
	end
	BeginQuestEvent(sceneId);
		AddQuestText(sceneId, x700026_str_NotTime);
	EndQuestEvent();
	DispatchQuestTips(sceneId, selfId);
	return 0;
end

function x700026_CheckCommonCondition_Day(sceneId, selfId)

	local weekDay = GetWeek()
	for i, item in x700026_g_EnterDay do
		if weekDay==item then
			
			
			return 1;
			
		end
	end
	BeginQuestEvent(sceneId);
		AddQuestText(sceneId, x700026_str_NotDay);
	EndQuestEvent();
	DispatchQuestTips(sceneId, selfId);
	return 0;
end

function x700026_CheckCommonCondition_Level(sceneId, selfId)
	
	local level = GetLevel( sceneId,selfId )
    if level < x700026_g_LevelMin then
        BeginQuestEvent(sceneId);
			AddQuestText(sceneId, x700026_str_UnderLevel);
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
		return 0
    end

    if level > x700026_g_LevelMax then
		 BeginQuestEvent(sceneId);
			AddQuestText(sceneId, x700026_str_UpLevel);
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
        return 0
    end
	
	return 1;
end



function x700026_CheckCommonCondition_Times(sceneId, selfId)
	if x700026_g_DayCountUntil >0 then
		local nDayCount = x700026_GetDayCount(sceneId, selfId)
		if nDayCount>= x700026_g_DayCountUntil then
			BeginQuestEvent(sceneId);
				AddQuestText(sceneId, x700026_str_TimesOver);
			EndQuestEvent();
			DispatchQuestTips(sceneId, selfId);
			return 0;
		end
	end
	return 1;
end



function x700026_CheckTeamCondition(sceneId, selfId)
	local teamid = GetTeamId(sceneId, selfId);
	local teamnum = GetTeamSize(sceneId, selfId);
	local nearteamnum = GetNearTeamCount(sceneId, selfId);

	local str = "";
	local bPassed = 1;

	if IsTeamLeader(sceneId, selfId) <= 0 then
		str	= "你不是队长！"
		bPassed = 0
	elseif x700026_CheckAllMemberNear( sceneId,selfId) <= 0 then
		str	= "需要所有的队友在附近！"
		bPassed = 0
	elseif teamid < 0 then
		str	= "你不在队伍中！"
		bPassed = 0
	elseif teamnum < x700026_g_LimitMembers then
		str	= format("你的队伍不足%d人！", x700026_g_LimitMembers)
		bPassed = 0
	elseif nearteamnum < x700026_g_LimitMembers then
		str	= format("附近队友不足%d人！", x700026_g_LimitMembers)
		bPassed = 0
	else

		local ret, tips;

		ret, tips = x700026_CheckAllMemberMinLevel(sceneId, selfId, nearteamnum);
		if ret <= 0 then
			str = tips;
			bPassed = 0
		end
		ret, tips = x700026_CheckAllMemberMaxLevel( sceneId, selfId, nearteamnum )

		if ret <= 0 then
			str = tips;
			bPassed = 0
		end

		ret, tips = x700026_CheckAllMemberDayCount(sceneId, selfId, nearteamnum);
		if ret == 0 then
			str = tips;
			bPassed = 0
		end



		 -- 检查所有玩家异常状态
		ret, tips = x700026_CheckAllMemberErrorState(sceneId, selfId, nearteamnum)
		if ret <= 0 then
			str = tips;
			bPassed = 0
		end

		if ret<=0 then
			str = tips;
			bPassed = 0
		end
		

	end

	if bPassed == 1 then
		return 1;
	else
		if str ~= "" then
			BeginQuestEvent(sceneId);
				AddQuestText(sceneId, str);
			EndQuestEvent();
			DispatchQuestTips(sceneId, selfId);
			return 0;
		end
	end


	return 1;
end

function x700026_CheckFuqiCondition(sceneId, selfId)
	return 1;
end

function x700026_CheckBanghuiCondition(sceneId, selfId)
	return 1;
end







function x700026_OnApproveRequestEnterFuben(sceneId, selfId, nEnterType)
	
	
	if nEnterType == x700026_ENTER_TYPE_TEAM then

		local memberNum = GetNearTeamCount(sceneId, selfId);

		x700026_MakeFuben_Team(sceneId, selfId, memberNum);

	elseif nEnterType == x700026_ENTER_TYPE_FUQI then
		
		

	elseif nEnterType == x700026_ENTER_TYPE_BANGHUI then
		
		
	
	else
		--PrintStr("Error Enter Type List")
		return 0;
	end

	

end



function x700026_MakeFuben_Team(sceneId, selfId, memberNum)
	--PrintStr(memberNum)
	for i = 0, memberNum - 1 do
        local memberId = GetNearTeamMember(sceneId, selfId, i);
        local ErrorCode = x700026_IsPlayerErrorState( sceneId, memberId )
        if ErrorCode == 0 then
            --lock
            SetPlayerMutexState( sceneId, memberId , PLAYER_STATE_READYFUBEN ,1)
        end
    end

	local leaderguid = ObjId2Guid(sceneId, selfId);
    local x,z =GetWorldPos(sceneId,selfId)

	--//add in 2009-3-6 for continous fuben
	local sceneParamList ={}
	for i=0, 255 do
		local nValue = GetFubenData_Param(sceneId, i);
		sceneParamList[i+1] = nValue;
	end
	--//add end

	SetSceneLoad_Map(sceneId, x700026_g_SceneMapNavPath); 								--地图是必须选取的，而且必须在Config/SceneInfo.ini里配置好
	SetFubenData_TeamLeader(sceneId, leaderguid);   
	SetFubenData_NoUserCloseTime(sceneId, x700026_g_NoUserTime * 1000);            --场景没人的保留时间
	SetFubenData_Timer(sceneId, x700026_g_TickTime * 1000);                        --设置定时器触发频率
	SetFubenData_Param(sceneId, x700026_CSP_FUBENTYPE, x700026_g_FubenType);	--设置副本数据，这里将0号索引的数据设置为999，用于表示副本号999(数字自定义)
	SetFubenData_Param(sceneId, x700026_CSP_SCRIPTID, x700026_g_ScriptId)			--将1号数据设置为副本场景事件脚本号
	SetFubenData_Param(sceneId, x700026_CSP_TICKCOUNT, 0);							--设置定时器调用次数
	SetFubenData_Param(sceneId, x700026_CSP_FROMSCENEID, -1);						--设置副本入口场景号, 初始化
	SetFubenData_Param(sceneId, x700026_CSP_ISCLOSING, 0);							--设置副本关闭标志, 0开放，1关闭
	SetFubenData_Param(sceneId, x700026_CSP_LEAVECOUNTDOWN, 0);					--设置离开倒计时次数
    SetFubenData_Param(sceneId, x700026_CSP_TEAMID, GetTeamId(sceneId, selfId)); 	--保存队伍号
	SetFubenData_Param(sceneId, x700026_CSP_BACKSCENEX, x) ;					    --杀死BOSS2的数量
	SetFubenData_Param(sceneId, x700026_CSP_BACKSCENEZ, z);                        --杀死BOSS3的数量
	SetFubenData_Param(sceneId, x700026_CSP_KILLCOUNT, 0);   

	--//add for 连环副本
	for i=x700026_CSP_GUID_START248, x700026_CSP_GUID_START+5 do
		SetFubenData_Param(sceneId, i ,0 )
	end
	--// add end



    for i= 0 ,memberNum - 1  do
        local memberId = GetNearTeamMember(sceneId, selfId, i);
        local guid = GetPlayerGUID( sceneId,memberId )
        local paramidx = x700026_CSP_GUID_START + i

        SetFubenData_Param(sceneId, paramidx ,guid )
    end


	-- 适应类型: 0-最高等级 1-最低等级 2-平均等级
    x700026_InitAutoLevel_Team(sceneId,selfId, memberNum,2)
    

	local bRetSceneID = CreateFuben(sceneId); 										--初始化完成后调用创建副本函数

	--//add in 2009-3-6 for continous fuben
	for i=0, 255 do
		local nValue = sceneParamList[i+1];
		SetFubenData_Param(sceneId, i,nValue);
	end
	--//add end


    if bRetSceneID > 0 then
        for i = 0, memberNum - 1 do
            local memberId = GetNearTeamMember(sceneId, selfId, i);
            BeginQuestEvent(sceneId);
            AddQuestText(sceneId, x700026_g_FuBenCreateOK);
            EndQuestEvent();
            DispatchQuestTips(sceneId, memberId);
        end


        --// update in 2009-3-17
		GamePlayScriptLog(sceneId, selfId, 1201)
		--//update end

    else

        for i = 0, memberNum - 1 do
            local memberId = GetNearTeamMember(sceneId, selfId, i);
            BeginQuestEvent(sceneId);
            AddQuestText(sceneId, x700026_g_FuBenCreateFailed);
            EndQuestEvent();
            DispatchQuestTips(sceneId, memberId);

            -- unlock
            SetPlayerMutexState( sceneId,memberId ,PLAYER_STATE_READYFUBEN ,0)
        end
    end
end


---------------------------------------------------------------------------------------------------
--副本已经准备完毕，此时将附近玩家拉到副本里
---------------------------------------------------------------------------------------------------
function x700026_OnFubenReady(sceneId, destsceneId)
	
	if x700026_FubenEnterType == x700026_ENTER_TYPE_TEAM then

		x700026_OnFubenReady_Team(sceneId, destsceneId)

	elseif x700026_FubenEnterType == x700026_ENTER_TYPE_FUQI then
		
		x700026_OnFubenReady_Fuqi(sceneId, destsceneId)

	elseif x700026_FubenEnterType == x700026_ENTER_TYPE_BANGHUI then
		
		x700026_OnFubenReady_Banghui(sceneId, destsceneId)
	
	else
		--PrintStr("Error Enter Type List")
		return 0;
	end

	

end

function x700026_OnFubenReady_Team(sceneId, destsceneId)

	for i=10, x700026_CSP_GUID_START do
		SetFubenData_Param(destsceneId,i,0)
	end
	
	SetFubenData_Param(destsceneId, x700026_CSP_FUBEN_SCENE_ID, destsceneId);--保存副本场景号
	
	local leaderguid = GetFubenData_TeamLeader(destsceneId);
	local leaderObjId = Guid2ObjId(sceneId, leaderguid);

	local	memberNum = GetNearTeamCount(sceneId, leaderObjId);


	--进入副本DEBUG信息
    local msg = "CSD,EnterFuben,"..x700026_g_ScriptId..","..destsceneId..","..memberNum
	
	--// add in 2009-4-3---------------------------
	local j=0
	for i=x700026_CSP_GUID_START, x700026_CSP_GUID_START+5 do
		local nGuid = GetFubenData_Param(destsceneId,i)

		--nGuid = NumberCastIntToUInt(nGuid)

		if nGuid~=0 then
			local memberId =  Guid2ObjId(sceneId, nGuid);

			local nFromSceneId = GetFubenData_Param(destsceneId, x700026_CSP_FROMSCENEID)
			if nFromSceneId<0 then
				if IsPlayerStateNormal(sceneId,memberId ) > 0 then
					local countryId = GetCurCountry( sceneId, memberId )
					SetFubenData_Param(destsceneId, x700026_CSP_FROMSCENEID, x700026_g_BackScene[countryId+1]);--设置副本入口场景号
				end
			end

			

			local ErrorCode = x700026_IsPlayerErrorState( sceneId,memberId )
			if ErrorCode == 0 then --正常游戏状态
				
				
				local x = x700026_g_EnterPos[j+1].x
				local z = x700026_g_EnterPos[j+1].z
				if CallScriptFunction(COUNTRY_BATTLE_LITE_SCRIPT,"CheckCountryBattleLiteSceneTrans",sceneId,memberId,destsceneId) == 1 then
					NewWorld(sceneId, memberId, destsceneId, x, z, 700026);
					msg = msg..","..nGuid
				end
				
				
				j = j+1
			end

			if IsPlayerStateNormal(sceneId,memberId ) > 0 then
				-- unlock
				SetPlayerMutexState( sceneId,memberId ,PLAYER_STATE_READYFUBEN ,0)
			end

			
		end
	end
	--// add end-----------------------------------

	--写日志
    WriteLog(1,msg)

end

function x700026_GetDayCountUntil(sceneId, selfId)
	return x700026_g_DayCountUntil;
end

function x700026_GetBackPosition(sceneId, selfId)
	local npos = random(1,6)
	local x1 = x700026_g_BackPos[npos].x
	local z1 = x700026_g_BackPos[npos].z

	return x1,z1
	
end

function x700026_OnFubenReady_Fuqi(sceneId, destsceneId)
end

function x700026_OnFubenReady_Banghui(sceneId, destsceneId)
end

---------------------------------------------------------------------------------------------------
--玩家进入副本时的处理,设置进入副本的位置
---------------------------------------------------------------------------------------------------
function x700026_OnPlayerEnter(sceneId, selfId)
	--//add in 2009-6-12
	local leaveFlag = GetFubenData_Param(sceneId, x700026_CSP_ISCLOSING);

	if leaveFlag > 0 then

		--提示xx秒后将退出副本
		local leaveCountDown = GetFubenData_Param(sceneId, x700026_CSP_LEAVECOUNTDOWN) + 1;
		
		if leaveCountDown >= x700026_g_CloseTick then
			local oldsceneId = GetFubenData_Param(sceneId, x700026_CSP_FROMSCENEID);
			
			RelivePlayerNM( sceneId,selfId,2) --如果玩家处于死亡状态，自动复活
			SetPlayerMutexState( sceneId,selfId,PLAYER_STATE_DIE,0)
			TimerCommand( sceneId, selfId, 1, 7010, 3, x700026_g_ScriptId, -1, -1 );


			local npos = random(1,6)
			local x = x700026_g_BackPos[npos].x
			local z = x700026_g_BackPos[npos].z

			NewWorld(sceneId, selfId, oldsceneId, x, z, 700026);
			return
		end
			
	end
	--//add end

	SetPlayerDefaultReliveInfo(sceneId, selfId, "%10", "%10", "%10", sceneId, x700026_g_Fuben_X, x700026_g_Fuben_Z);

	--//add in 2009-6-2 check if it is the human who have applyed
	local myGuid = GetPlayerGUID( sceneId,selfId )
	myGuid = format("%u",myGuid)
	local bFind =0
	for i= 0 ,6 - 1  do
       
        local paramidx = x700026_CSP_GUID_START + i

        local guid = GetFubenData_Param(sceneId, paramidx )
		guid=format("%u",guid)
		if myGuid==guid then
			bFind =1
			break;
		end
    end

	if bFind==0 then
		local nDayCount = x700026_GetDayCount(sceneId, selfId)
		FubenIllegalEnterLog(sceneId, selfId, 1201,nDayCount)
		
	end
	--//add end
	
	
	
end

function x700026_OnPlayerEnterFinished(sceneId, selfId)
	
end



function x700026_OnEnterTick(sceneId,nowTickCount)

	local nCurrentStep = GetFubenData_Param(sceneId, x700026_CSP_GAME_STEP);
	local nTickCount = GetFubenData_Param(sceneId, x700026_CSP_STEP_TICKCOUNT) + 1;
	SetFubenData_Param(sceneId, x700026_CSP_STEP_TICKCOUNT, nTickCount);

	
	if nTickCount == x700026_g_IntervalList[nCurrentStep+1] then
		if nCurrentStep<4 then
			if nCurrentStep+1>1 then
				local nNpcId = GetFubenData_Param(sceneId, x700026_CSP_NPC_ID )
				NpcTalk(sceneId, nNpcId, "时间到，本轮结束",  -1)
				x700026_ShowTipsToAll(sceneId, "时间到，本轮结束")
			end
			x700026_StartStep(sceneId, nCurrentStep+1)
		elseif nCurrentStep==4 then
			x700026_OnAllGatherCompleted(sceneId)
		end
	else
		if nCurrentStep>=1 and nCurrentStep<=4 then
			
			for i=1, 34 do
				local nGrowpointId = GetFubenData_Param(sceneId, x700026_CSP_GP_ID_START+i);
				local nStatus = GetFubenData_Param(sceneId, x700026_CSP_GP_BOXID_START+i);
				if nGrowpointId<0 and nStatus==-2 then
					 SetFubenData_Param(sceneId, x700026_CSP_GP_BOXID_START+i,-1);

					 x700026_InitMyGrowXZ(sceneId, i)

					 local nPosIndex = GetFubenData_Param(sceneId, x700026_CSP_GP_POSIDX_START+i)
					 local x = x700026_g_GrowPoint_PosList[nPosIndex].x
					 local z = x700026_g_GrowPoint_PosList[nPosIndex].z

					 SetGrowPointPos(sceneId,x700026_g_Start_GPID+i,x,z)
				end
			end
		end
	end

	

	

	
end

function x700026_StartStep(sceneId, nNextStep)

	
	
	if nNextStep<1 or nNextStep>4 then
		return
	end

	local nCurrentStep = GetFubenData_Param(sceneId, x700026_CSP_GAME_STEP);

	if nCurrentStep~=nNextStep-1 then
		return
	end

	SetFubenData_Param(sceneId, x700026_CSP_GAME_STEP,nNextStep);
	SetFubenData_Param(sceneId, x700026_CSP_STEP_TICKCOUNT, 0);

	x700026_DeleteAllGrowPoint(sceneId)

	x700026_InitGrowXZ(sceneId)

	for i=1, 34 do

		local nPosIndex = GetFubenData_Param(sceneId, x700026_CSP_GP_POSIDX_START+i)
		local x = x700026_g_GrowPoint_PosList[nPosIndex].x
		local z = x700026_g_GrowPoint_PosList[nPosIndex].z
		
		SetGrowPointPos(sceneId,x700026_g_Start_GPID+i,x,z)
	end
	
	for i=1, 34 do
		SetGrowPointIntervalContainer(sceneId,x700026_g_Start_GPID+i,x700026_g_GPInterval)
		
		--if nNextStep>=2 then
		--	local nPosIndex = GetFubenData_Param(sceneId, x700026_CSP_GP_POSIDX_START+i)
		--	local x = x700026_g_GrowPoint_PosList[nPosIndex].x
		--	local z = x700026_g_GrowPoint_PosList[nPosIndex].z
		--	x700026_OnCreateGrowPoint(sceneId,x700026_g_Start_GPID+i,x,z)
		--end
	end
	
	local nNpcId = GetFubenData_Param(sceneId, x700026_CSP_NPC_ID )
	if nNextStep==1 then
		x700026_ShowTipsToAll(sceneId, "第一轮开始")
		local iResult = random(1,3)

		if iResult ==1 then
			NpcTalk(sceneId, nNpcId, "采集所有的条子",  -1)
			x700026_ShowTipsToAll(sceneId, "采集所有的条子")	
		elseif iResult ==2 then
			NpcTalk(sceneId, nNpcId, "采集所有的筒子",  -1)
			x700026_ShowTipsToAll(sceneId, "采集所有的筒子")	
		elseif iResult ==3 then
			NpcTalk(sceneId, nNpcId, "采集所有的万子",  -1)
			x700026_ShowTipsToAll(sceneId, "采集所有的万子")	
		else
			return
		end
		
		SetFubenData_Param(sceneId, x700026_CSP_RESULT_START,iResult);
	elseif nNextStep==2 then
		x700026_ShowTipsToAll(sceneId, "第一轮结束，第二轮开始")
		NpcTalk(sceneId, nNpcId, "采集所有的风牌和箭牌",  -1)
		x700026_ShowTipsToAll(sceneId, "采集所有的风牌和箭牌")	
	elseif nNextStep==3 then

		x700026_ShowTipsToAll(sceneId, "第二轮结束，第三轮开始")
			

		local iSeg = random(1,3)
		local iResult = random((iSeg-1)*9+1, (iSeg-1)*9+7)

		
		
		local str = x700026_GetShunziName(sceneId,iResult)
		str = "采集顺子"..str
		NpcTalk(sceneId, nNpcId, str,  -1)
		x700026_ShowTipsToAll(sceneId, str)

		SetFubenData_Param(sceneId, x700026_CSP_RESULT_START,iResult);
	elseif nNextStep==4 then
		x700026_ShowTipsToAll(sceneId, "第三轮结束，第四轮开始")
		NpcTalk(sceneId, nNpcId, "抢积分时间到！牌面越大积分越多,采集时间30秒",  -1)
		x700026_ShowTipsToAll(sceneId, "抢积分时间到！牌面越大积分越多,采集时间30秒")	
	end

	
	
end

function x700026_GetShunziName(sceneId,iStartId)

	local strTypeName = "";
	if iStartId<9 then
		strTypeName =format("%d,%d,%d条",iStartId,iStartId+1,iStartId+2);
	elseif iStartId<18 then
		strTypeName =format("%d,%d,%d筒",iStartId-9,iStartId-9+1,iStartId-9+2);
	elseif iStartId<27 then
		strTypeName =format("%d,%d,%d万",iStartId-18,iStartId-18+1,iStartId-18+2);
	end

	return strTypeName;



end

function x700026_OnAnwer(sceneId,nGrowpointId)
	local nAnswerId = nGrowpointId - x700026_g_Start_GPID
	local nCurrentStep = GetFubenData_Param(sceneId, x700026_CSP_GAME_STEP);

	if nCurrentStep==1 then
		local iResult = GetFubenData_Param(sceneId, x700026_CSP_RESULT_START)
		if nAnswerId>(iResult-1)*9 and nAnswerId<=iResult*9 then
			x700026_OnCorrect(sceneId,nAnswerId)
		else
			x700026_OnIncorrect(sceneId,nAnswerId)
		end
	elseif  nCurrentStep==2 then
		if nAnswerId<=27 then
			x700026_OnIncorrect(sceneId,nAnswerId)
		else
			x700026_OnCorrect(sceneId,nAnswerId)
		end
	elseif  nCurrentStep==3 then
		local iResult = GetFubenData_Param(sceneId, x700026_CSP_RESULT_START)
		
		local bCorrect = 0
		for i=iResult, iResult+2 do
			if nAnswerId==i then
				bCorrect = 1
				break
			end
		end

		if bCorrect<=0 then
			x700026_OnIncorrect(sceneId,nAnswerId)
		else
			x700026_OnCorrect(sceneId,nAnswerId)
		end
	elseif nCurrentStep==4 then
		local nScore = GetFubenData_Param(sceneId, x700026_CSP_SCORE);
		local nAdd =0
		if nAnswerId<=27 then
			if mod(nAnswerId,9)==0 then
				
				nAdd =9
			else
				nAdd = mod(nAnswerId,9)
			end
		else
			nAdd = 1
		end
		
		nScore	= nScore + nAdd;
		SetFubenData_Param(sceneId, x700026_CSP_SCORE,nScore)
		x700026_ShowTipsToAll(sceneId, format("回答正确，积分增加%d,总分为%d",nAdd,nScore))
	end

	

	

	


end

function x700026_OnAllGatherCompleted(sceneId)
	local nCurrentStep = GetFubenData_Param(sceneId, x700026_CSP_GAME_STEP);
	if nCurrentStep~=4 then
		return
	end

	SetFubenData_Param(sceneId, x700026_CSP_GAME_STEP,5);


	x700026_DeleteAllGrowPoint(sceneId)
	


	

	local nScore = GetFubenData_Param(sceneId, x700026_CSP_SCORE)
	local nNpcId = GetFubenData_Param(sceneId, x700026_CSP_NPC_ID )

	NpcTalk(sceneId, nNpcId, "时间到，本轮结束",  -1)
	x700026_ShowTipsToAll(sceneId, format("选牌结束，你们总共得到%d分",nScore))
	x700026_OnCreateFinalBoss(sceneId)
end

function x700026_DeleteAllGrowPoint(sceneId)
	for i=1, 34 do
		local nGrowpointId = x700026_g_Start_GPID+i

		
		RecycleGrowPointByType(sceneId,nGrowpointId,-1)
		
		
		SetFubenData_Param(sceneId, x700026_CSP_GP_ID_START+i,-1);
			
		
	end
end

function x700026_OnCreateFinalBoss(sceneId)
	local nNpcId = GetFubenData_Param(sceneId, x700026_CSP_NPC_ID )

	NpcTalk(sceneId, nNpcId, "打骰子啦！",  -1)


	local fubenlevel = GetFubenData_Param(sceneId, x700026_CSP_FUBENLEVEL ) ;

	--PrintStr(fubenlevel)
	local nScore = GetFubenData_Param(sceneId, x700026_CSP_SCORE)


	local nCount =0;
	if nScore<=126 then
		nCount =1;
	elseif nScore<=252 then
		nCount =2;
	elseif nScore<=378 then
		nCount =4;
	elseif nScore<=480 then
		nCount =8;
	elseif nScore<=582 then
		nCount =10;
	elseif nScore<=683 then
		nCount =12;
	else
		nCount =18;
	end
	
	
	for i, item in x700026_g_BossCreate do

        if item.levelmin <= fubenlevel and item.levelmax >= fubenlevel then
		   for j=0,nCount -1 do

                local rx = random(-item.r,item.r)
                local x = item.x + rx
                local rz = random(-item.r,item.r)
                local z = item.z + rz

				if item.title~="" then
					CreateMonster(sceneId, item.type, x, z, item.ai, item.aiscript, x700026_g_ScriptId, -1, 21,-1,item.facedir,  "",item.title)
				else
					CreateMonster(sceneId, item.type, x, z, item.ai, item.aiscript, x700026_g_ScriptId, -1, 21,-1,item.facedir)
				end
			end

        end
	end

	x700026_ShowTipsToAll(sceneId, format("刷出%d个骰子！",nCount))

	SetFubenData_Param(sceneId, x700026_CSP_KILLCOUNT, 0);
	SetFubenData_Param(sceneId, x700026_CSP_NEEDKILLCOUNT, nCount);
end

function x700026_OnDie(sceneId, selfId, killerId)
	local nDieCount = GetFubenData_Param(sceneId, x700026_CSP_KILLCOUNT)
	SetFubenData_Param(sceneId, x700026_CSP_KILLCOUNT, nDieCount+1);

	nDieCount = nDieCount+1;

	local nNeedKillCount = GetFubenData_Param(sceneId, x700026_CSP_NEEDKILLCOUNT);

	if nNeedKillCount== nDieCount then

		--//--------------------------- 世界喊话 Start--------------------
	
		local nowTickCount = GetFubenData_Param(sceneId, x700026_CSP_TICKCOUNT)

		local nowTime = x700026_g_TickTime* nowTickCount;

		local nMinute = floor(nowTime/60)
		local nSec = mod(nowTime,60)

			
		local strPlayerName = GetName(sceneId, killerId)     -- 杀死怪物的玩家名字
		-------- if killed by pet -----------------
		local nKillerType = GetObjType(sceneId, killerId)
		--PrintStr(nKillerType)
		if nKillerType== 3 then
			local nOwnerId = GetOwnerID(sceneId, killerId)
			strPlayerName = GetName(sceneId, nOwnerId)
		end
		--------- end -------------------------------
		local strBossName = GetName(sceneId, selfId)		 -- Boss name	
		local strKillTime = format("%d分%d秒", nMinute, nSec) -- 杀死关务的事件

		
		--if selfId == objId1 then -- boss flag=0
			LuaAllScenceM2Wrold (sceneId,"#R四撇眉毛#G"..strPlayerName.."#R和他的队友们以钢铁的意志和超人的勇气仅用了#G"..strKillTime.."#R就顺利地救出了被困的玉柱。", 0, 1)
		--end

	
	
	--//--------------------------- 世界喊话 end----------------------
		x700026_OnAllMonsterDead( sceneId)
	end
end

function x700026_OnAllMonsterDead( sceneId)
	
	local nNpcId = GetFubenData_Param(sceneId, x700026_CSP_NPC_ID )

	NpcTalk(sceneId, nNpcId, "你们出色地完成了副本，可以离开了",  -1)

	x700026_CreateSubmitNpc( sceneId)
end

function x700026_CreateSubmitNpc( sceneId)
	if x700026_g_SubmitNPC.title~="" then
		CreateMonster(sceneId, x700026_g_SubmitNPC.type, x700026_g_SubmitNPC.x, x700026_g_SubmitNPC.z, 3, 0, -1, x700026_g_SubmitNPC.guid, -1,-1,x700026_g_SubmitNPC.facedir, "",x700026_g_SubmitNPC.title )
	else
		CreateMonster(sceneId, x700026_g_SubmitNPC.type, x700026_g_SubmitNPC.x, x700026_g_SubmitNPC.z, 3, 0, -1, x700026_g_SubmitNPC.guid, -1,-1,x700026_g_SubmitNPC.facedir)
	end
end


function x700026_OnCorrect(sceneId,nAnswerId)
	local nScore = GetFubenData_Param(sceneId, x700026_CSP_SCORE)+1;
	SetFubenData_Param(sceneId, x700026_CSP_SCORE,nScore)
	x700026_ShowTipsToAll(sceneId, format("回答正确，积分增加1,总分为%d",nScore))

	
--	local nCurrentStep = GetFubenData_Param(sceneId, x700026_CSP_GAME_STEP);
--
--	local bAllOk=1;
--
--	if nCurrentStep==1 then
--		local iResult = GetFubenData_Param(sceneId, x700026_CSP_RESULT_START)
--		
--		for i=(iResult-1)*9+1, iResult*9 do
--			local nGrowpointId = GetFubenData_Param(sceneId, x700026_CSP_GP_ID_START+i);
--
--			if nGrowpointId>=0 then
--				bAllOk = 0;
--			end
--		end
--	elseif nCurrentStep==2 then
--		
--		for i=28, 34 do
--			local nGrowpointId = GetFubenData_Param(sceneId, x700026_CSP_GP_ID_START+i);
--
--			if nGrowpointId>=0 then
--				bAllOk = 0;
--			end
--		end
--	elseif nCurrentStep==3 then
--		local iResult = GetFubenData_Param(sceneId, x700026_CSP_RESULT_START)
--		
--		for i=iResult, iResult+2 do
--			local nGrowpointId = GetFubenData_Param(sceneId, x700026_CSP_GP_ID_START+i);
--
--			if nGrowpointId>=0 then
--				bAllOk = 0;
--			end
--		end
--	else
--		bAllOk = 0
--	end
--
--	if bAllOk>0 then
--		if nCurrentStep<4 then
--			x700026_ShowTipsToAll(sceneId, "非常好的完成了任务,马上开始下一轮")
--			
--			x700026_StartStep(sceneId, nCurrentStep+1)
--		
--		end
--	end
end

function x700026_OnIncorrect(sceneId,nAnswerId)
	
	x700026_ShowTipsToAll(sceneId, "回答错误")

	local humancount = GetFuben_PlayerCount(sceneId);

	for i = 0, humancount - 1 do


		local humanId = GetFuben_PlayerObjId(sceneId, i);	--取得当前场景里人的objId
		SendSpecificImpactToUnit(sceneId, humanId,humanId,humanId, x700026_g_Buff1,0 )
		
	end
end


function x700026_GetGaterHoldTime(sceneId)
	local nCurrentStep = GetFubenData_Param(sceneId, x700026_CSP_GAME_STEP);
	local nTickCount = GetFubenData_Param(sceneId, x700026_CSP_STEP_TICKCOUNT);

	if nCurrentStep>4 or nCurrentStep<1 then
		return -1;
	end

	local nHoldTime =0;

	
	nHoldTime = x700026_g_IntervalList[nCurrentStep+1]-nTickCount
	
	return nHoldTime;
end
---------------------------------------------------------------------------------------------------
--副本定时器处理
---------------------------------------------------------------------------------------------------
function x700026_OnFubenTimer(sceneId, nowTime)

	
	
	
	local nowTickCount = GetFubenData_Param(sceneId, x700026_CSP_TICKCOUNT) + 1;
	SetFubenData_Param(sceneId, x700026_CSP_TICKCOUNT, nowTickCount);
	


	--PrintStr(nowTickCount)
	local leaveFlag = GetFubenData_Param(sceneId, x700026_CSP_ISCLOSING);

	if leaveFlag > 0 then

		--提示xx秒后将退出副本
		local leaveCountDown = GetFubenData_Param(sceneId, x700026_CSP_LEAVECOUNTDOWN) + 1;
		SetFubenData_Param(sceneId, x700026_CSP_LEAVECOUNTDOWN, leaveCountDown);

		if leaveCountDown >= x700026_g_CloseTick then
			local oldsceneId = GetFubenData_Param(sceneId, x700026_CSP_FROMSCENEID);
			local humancount = GetFuben_PlayerCount(sceneId);
			for	i = 0, humancount - 1 do
				local humanId = GetFuben_PlayerObjId(sceneId, i);
                RelivePlayerNM( sceneId,humanId,2) --如果玩家处于死亡状态，自动复活
                SetPlayerMutexState( sceneId,humanId,PLAYER_STATE_DIE,0) --####
--                local x = GetFubenData_Param(sceneId, x700026_CSP_BACKSCENEX ) ;
--                local z = GetFubenData_Param(sceneId, x700026_CSP_BACKSCENEZ ) ;
                TimerCommand( sceneId, humanId, 1, 7010, 3, x700026_g_ScriptId, -1, -1 );

                local npos = random(1,6)
                local x = x700026_g_BackPos[npos].x
                local z = x700026_g_BackPos[npos].z

				NewWorld(sceneId, humanId, oldsceneId, x, z, 700026);
			end
		elseif leaveCountDown < x700026_g_CloseTick then
			local humancount = GetFuben_PlayerCount(sceneId);
			for	i = 0, humancount - 1 do
				local humanId = GetFuben_PlayerObjId(sceneId, i);
 				local str = format(x700026_g_CountDownMessage, (x700026_g_CloseTick - leaveCountDown) * x700026_g_TickTime);
  				BeginQuestEvent(sceneId);
  				AddQuestText(sceneId, str);
  				EndQuestEvent(sceneId);

  				DispatchQuestTips(sceneId, humanId);
			end
		end

	else

        if nowTickCount == 1 then
			
			x700026_OnFubenSceneCreated(sceneId )
           
        end

		
--        x700026_CheckAllMemberState( sceneId )

		--副本计时器
        --local nTime = (x700026_g_LimitTotalHoldTime - nowTickCount )*5

		local nCurrentStep = GetFubenData_Param(sceneId, x700026_CSP_GAME_STEP);
		local bNormalTime = 0
		if nCurrentStep<1 or nCurrentStep>4 then
			bNormalTime = 1
		end

		

		local humancount = GetFuben_PlayerCount(sceneId);

		if nowTickCount >= 2 then
            if humancount>0 then
				x700026_OnEnterTick(sceneId,nowTickCount);
			end
        end

		local nTime = 0;
		local nGatherHoldTime = x700026_GetGaterHoldTime(sceneId)
		if bNormalTime==0 then
			nTime= nGatherHoldTime*5
		else
			nTime= (x700026_g_LimitTotalHoldTime - nowTickCount )*5
		end

		for i = 0, humancount - 1 do
			local humanId = GetFuben_PlayerObjId(sceneId, i);
            
            TimerCommand( sceneId, humanId, 1, 7010, 3, x700026_g_ScriptId, -1, -1 );

            if nTime > 0 then

                local nEventTime = nTime
                if nTime > 10 then
                    nEventTime = nTime - 10
                end
                --TimerCommand( sceneId, humanId, 2, 7010, 3, x700026_g_ScriptId, nTime, nTime );
				if bNormalTime==0 then
					TimerCommand( sceneId, humanId, 2, 7010, 3, x700026_g_ScriptId, nTime, nTime+10 );
				else
					TimerCommand( sceneId, humanId, 2, 7010, 3, x700026_g_ScriptId, nTime, nTime );
				end
            end

			-- 检查是否过了场景的生存期
			if nowTickCount == x700026_g_LimitTotalHoldTime then
				--local oldsceneId = x700026_CancelMission(sceneId, humanId);
				BeginQuestEvent(sceneId);
					AddQuestText(sceneId, x700026_g_TimeOutFailedMessage);
				EndQuestEvent();
				DispatchQuestTips(sceneId, humanId);
			end
		end

        if nowTickCount == x700026_g_LimitTotalHoldTime then
            SetFubenData_Param(sceneId, x700026_CSP_ISCLOSING,1);
        end
	end

end


---------------------------------------------------------------------------------------------------
--初始化自动等级
---------------------------------------------------------------------------------------------------
function x700026_InitAutoLevel_Team( sceneId,selfId ,memberNum,autoleveltype )

    if autoleveltype == 0 then          -- 最高等级匹配

        --取得队伍里玩家最高等级
        local maxlevel = 0
        for i = 0, memberNum - 1 do
            local memberId = GetNearTeamMember(sceneId, selfId, i);
            local level = GetLevel(sceneId,memberId)

            if maxlevel < level then
                maxlevel = level
            end
        end

        SetFubenData_Param(sceneId, x700026_CSP_FUBENLEVEL, maxlevel) ;					    --配置副本等级

    elseif autoleveltype == 1 then      -- 最低等级匹配

        --取得队伍里玩家最低等级
        local minlevel = 1000
        for i = 0, memberNum - 1 do
            local memberId = GetNearTeamMember(sceneId, selfId, i);
            local level = GetLevel(sceneId,memberId)

            if minlevel > level then
                minlevel = level
            end
        end

        SetFubenData_Param(sceneId, x700026_CSP_FUBENLEVEL, minlevel) ;					    --配置副本等级

    elseif autoleveltype == 2 then      --平均等级匹配

        --计算平均等级

        local averagelevel = 0
        local levelval1 = 0
        local levelval2 = 0
        for i = 0, memberNum - 1 do
            local memberId = GetNearTeamMember(sceneId, selfId, i);
            local level = GetLevel(sceneId,memberId)

            levelval1 = levelval1 + level*level
            levelval2 = levelval2 + level
        end

        averagelevel = levelval1 / levelval2

        SetFubenData_Param(sceneId, x700026_CSP_FUBENLEVEL, averagelevel) ;					--配置副本等级

    end
end


---------------------------------------------------------------------------------------------------
--检查玩家错误状态
---------------------------------------------------------------------------------------------------
function x700026_IsPlayerErrorState( sceneId,selfId )

    local state

    state = IsPlayerStateNormal(sceneId,selfId )
    if state == 0 then
        return 1
    end

    state = IsPlayerMutexState(sceneId,selfId,PLAYER_STATE_MENTALGAME )
    if state == 1 then
        return 1
    end

    state = IsPlayerMutexState(sceneId,selfId,PLAYER_STATE_STALL )
    if state == 1 then
        return 1
    end

    state = IsPlayerMutexState(sceneId,selfId,PLAYER_STATE_DIE )
    if state == 1 then
        return 1
    end

    state = IsPlayerMutexState(sceneId,selfId,PLAYER_STATE_CRASHBOX )
    if state == 1 then
        return 1
    end

    state = IsPlayerMutexState(sceneId,selfId,PLAYER_STATE_AUTOPLAY )
    if state == 1 then
        return 1
    end

    state = IsPlayerMutexState(sceneId,selfId,PLAYER_STATE_SUBTRAIN )
    if state == 1 then
        return 1
    end

    state = IsPlayerMutexState(sceneId,selfId,PLAYER_STATE_BUS )
    if state == 1 then
        return 1
    end

		state = IsPlayerMutexState(sceneId,selfId,PLAYER_STATE_ENJAIL )
    if state == 1 then
        return 1
    end	

	--// add in 2-20-2009
	state = IsPlayerMutexState(sceneId,selfId,PLAYER_STATE_WEDDING )
    if state == 1 then
        return 1
    end

	state = IsPlayerMutexState(sceneId,selfId,PLAYER_STATE_TONGQUBUFF )
    if state == 1 then
        return 1
    end

	state = IsPlayerMutexState(sceneId,selfId,PLAYER_STATE_TIESAN )
    if state == 1 then
        return 1
    end
	--// added end


    return 0

end



---------------------------------------------------------------------------------------------------
--取得当前次数
---------------------------------------------------------------------------------------------------
function x700026_GetDayCount(sceneId, selfId)
	local today = GetDayOfYear()
	local lastday = GetQuestData(sceneId, selfId, MD_FUBEN_FOSHOU_DATE[1], MD_FUBEN_FOSHOU_DATE[2],MD_FUBEN_FOSHOU_DATE[3] );
	
	if lastday ~= today then
		return 0
	end

	local daycount = GetQuestData(sceneId, selfId, MD_FUBEN_FOSHOU_DAYCOUNT[1], MD_FUBEN_FOSHOU_DAYCOUNT[2],MD_FUBEN_FOSHOU_DAYCOUNT[3] );
	return daycount;
end

---------------------------------------------------------------------------------------------------
--设置当天次数
---------------------------------------------------------------------------------------------------
function x700026_SetDayCount(sceneId, selfId)

	local today = GetDayOfYear()

	local lastday = GetQuestData(sceneId, selfId, MD_FUBEN_FOSHOU_DATE[1], MD_FUBEN_FOSHOU_DATE[2], MD_FUBEN_FOSHOU_DATE[3])

	if lastday ~= today then
		SetQuestData(sceneId, selfId, MD_FUBEN_FOSHOU_DATE[1], MD_FUBEN_FOSHOU_DATE[2], MD_FUBEN_FOSHOU_DATE[3], today)
		SetQuestData(sceneId, selfId, MD_FUBEN_FOSHOU_DAYCOUNT[1], MD_FUBEN_FOSHOU_DAYCOUNT[2], MD_FUBEN_FOSHOU_DAYCOUNT[3], 1)
	else
		local daycount = GetQuestData(sceneId, selfId, MD_FUBEN_FOSHOU_DAYCOUNT[1], MD_FUBEN_FOSHOU_DAYCOUNT[2], MD_FUBEN_FOSHOU_DAYCOUNT[3])
		SetQuestData(sceneId, selfId, MD_FUBEN_FOSHOU_DAYCOUNT[1], MD_FUBEN_FOSHOU_DAYCOUNT[2], MD_FUBEN_FOSHOU_DAYCOUNT[3], daycount+1)
	end
	
	
	
end



---------------------------------------------------------------------------------------------------
--玩家死亡
---------------------------------------------------------------------------------------------------
function x700026_OnPlayerDie(sceneId, selfId, killerId)
end


----*************************************************************************************************
-- Check Team Function
----*************************************************************************************************

function x700026_CheckAllMemberNear(sceneId, selfId)
    local nNearCount  = GetNearTeamCount( sceneId,selfId )
    local nTotalCount = GetTeamSize( sceneId,selfId )

    if nNearCount ~= nTotalCount then
        return 0
    end

    return 1
end



---------------------------------------------------------------------------------------------------
--检查队伍里附近队友的最小级别
---------------------------------------------------------------------------------------------------
function x700026_CheckAllMemberMinLevel(sceneId, selfId, teamnum)


	local tips,result

	result = 1

	if( x700026_g_LevelMin > 0 ) then
		for i = 0, teamnum - 1 do
			local memberId = GetNearTeamMember(sceneId, selfId, i);
			if GetLevel(sceneId, memberId) < x700026_g_LevelMin then
				if result == 1 then
					result = 0
					tips = GetName(sceneId, memberId)
				else
					tips = tips..","..GetName(sceneId, memberId)
				end
			end
		end
	end

	if result == 0 then
		tips = tips..format("的等级不足%d级！", x700026_g_LevelMin)
	end

	return result,tips;
end

---------------------------------------------------------------------------------------------------
--检查队伍里附近队友的级别
---------------------------------------------------------------------------------------------------
function x700026_CheckAllMemberMaxLevel(sceneId, selfId, teamnum)       --**


	local tips,result

	result = 1

	if( x700026_g_LevelMax > 0 ) then
		for i = 0, teamnum - 1 do
			local memberId = GetNearTeamMember(sceneId, selfId, i);
			if GetLevel(sceneId, memberId) > x700026_g_LevelMax then
				if result == 1 then
					result = 0
					tips = GetName(sceneId, memberId)
				else
					tips = tips..","..GetName(sceneId, memberId)
				end
			end
		end
	end

	if result == 0 then
		tips = tips.." 超出等级限制"
	end

	return result,tips;
end

---------------------------------------------------------------------------------------------------
--检查队伍里玩家当天任务次数
---------------------------------------------------------------------------------------------------
function x700026_CheckAllMemberDayCount(sceneId, selfId, teamnum)

	local tips,result

	result = 1

	if( x700026_g_DayCountUntil > 0 ) then
		for i = 0, teamnum - 1 do
			local memberId = GetNearTeamMember(sceneId, selfId, i);
			if x700026_GetDayCount(sceneId, memberId) >= x700026_g_DayCountUntil then
				if result == 1 then
					result = 0
					tips = GetName(sceneId, memberId)
				else
					tips = tips..","..GetName(sceneId, memberId)
				end
			end
		end
	end

	if result == 0 then
		tips = tips.." 超过当日进入副本次数限制"
	end

	return result,tips;

end



---------------------------------------------------------------------------------------------------
--检查队伍中是否有错误状态
---------------------------------------------------------------------------------------------------
function x700026_CheckAllMemberErrorState( sceneId, selfId, teamnum )

    local result,tips ;

    -- 正常游戏状态
    result,tips = x700026_CheckAllMemberErrorState_NormalState( sceneId,selfId,teamnum )
    if result == 0 then
        return result,tips
    end

    -- 死亡状态
    result,tips = x700026_CheckAllMemberErrorState_Die( sceneId, selfId, teamnum )
    if result == 0 then
        return result,tips
    end

    -- 代练状态
    result,tips = x700026_CheckAllMemberErrorState_AutoPlay( sceneId,selfId,teamnum )
    if result == 0 then
        return result,tips
    end

    -- 摆摊状态
    result,tips = x700026_CheckAllMemberErrorState_Stall( sceneId,selfId,teamnum )
    if result == 0 then
        return result,tips
    end

    -- 答题状态
    result,tips = x700026_CheckAllMemberErrorState_MentalGame( sceneId,selfId,teamnum )
    if result == 0 then
        return result,tips
    end

    -- 运镖状态
    result,tips = x700026_CheckAllMemberErrorState_CrashBox( sceneId,selfId,teamnum )
    if result == 0 then
        return result,tips
    end

    -- BUS状态
    result,tips = x700026_CheckAllMemberErrorState_Bus( sceneId,selfId,teamnum )
    if result == 0 then
        return result,tips
    end

	 -- Enjail状态
    result,tips = x700026_CheckAllMemberErrorState_Enjail( sceneId,selfId,teamnum )
    if result == 0 then
        return result,tips
    end

	--// add in 2-20-2009
	-- 婚礼状态
	result,tips = x700026_CheckAllMemberErrorState_Wedding( sceneId,selfId,teamnum )
    if result == 0 then
        return result,tips
    end

	-- 童趣状态
	result,tips = x700026_CheckAllMemberErrorState_Tongqu( sceneId,selfId,teamnum )
    if result == 0 then
        return result,tips
    end

	-- 铁人三项状态
	result,tips = x700026_CheckAllMemberErrorState_Tiesan( sceneId,selfId,teamnum )
    if result == 0 then
        return result,tips
    end

	--// added end

	--//add in 3-9-2009
	--处于CopyReady状态
--	result,tips = x700026_CheckAllMemberErrorState_FubenReady( sceneId,selfId,teamnum )
--    if result == 0 then
--        return result,tips
--    end
	
	--//add end


    return 1


end


---------------------------------------------------------------------------------------------------
--正常游戏状态
---------------------------------------------------------------------------------------------------
function x700026_CheckAllMemberErrorState_NormalState( sceneId, selfId, teamnum )
    local tips,result

	result = 1

    -- 检查游戏状态是否正常
    for i = 0, teamnum - 1 do
        local memberId = GetNearTeamMember(sceneId, selfId, i);
        local state = IsPlayerStateNormal(sceneId,memberId )
        if state == 0 then
            if result == 1 then
                result = 0
                tips = GetName(sceneId, memberId)
            else
                tips = tips..","..GetName(sceneId, memberId)
            end
        end
    end

	if result == 0 then
		tips = tips.." 离线或不在当前场景"
	end

	return result,tips;
end

---------------------------------------------------------------------------------------------------
--处于答题状态
---------------------------------------------------------------------------------------------------
function x700026_CheckAllMemberErrorState_MentalGame( sceneId, selfId, teamnum )
    local tips,result

	result = 1

    -- 检查游戏状态是否正常
    for i = 0, teamnum - 1 do
        local memberId = GetNearTeamMember(sceneId, selfId, i);
        local state = IsPlayerMutexState(sceneId,memberId,PLAYER_STATE_MENTALGAME )
        if state == 1 then
            if result == 1 then
                result = 0
                tips = GetName(sceneId, memberId)
            else
                tips = tips..","..GetName(sceneId, memberId)
            end
        end
    end

	if result == 0 then
		tips = tips.." 处于答题状态"
	end

	return result,tips
end

---------------------------------------------------------------------------------------------------
--处于摆摊状态
---------------------------------------------------------------------------------------------------
function x700026_CheckAllMemberErrorState_Stall( sceneId, selfId, teamnum )
    local tips,result

	result = 1

    -- 检查游戏状态是否正常
    for i = 0, teamnum - 1 do
        local memberId = GetNearTeamMember(sceneId, selfId, i);
        local state = IsPlayerMutexState(sceneId,memberId,PLAYER_STATE_STALL )
        if state == 1 then
            if result == 1 then
                result = 0
                tips = GetName(sceneId, memberId)
            else
                tips = tips..","..GetName(sceneId, memberId)
            end
        end
    end

	if result == 0 then
		tips = tips.." 处于摆摊状态"
	end

	return result,tips
end

---------------------------------------------------------------------------------------------------
--处于死亡状态
---------------------------------------------------------------------------------------------------
function x700026_CheckAllMemberErrorState_Die( sceneId, selfId, teamnum )
    local tips,result

	result = 1

    -- 检查游戏状态是否正常
    for i = 0, teamnum - 1 do
        local memberId = GetNearTeamMember(sceneId, selfId, i);
        local state = IsPlayerMutexState(sceneId,memberId,PLAYER_STATE_DIE )
        if state == 1 then
            if result == 1 then
                result = 0
                tips = GetName(sceneId, memberId)
            else
                tips = tips..","..GetName(sceneId, memberId)
            end
        end
    end

	if result == 0 then
		tips = tips.." 处于死亡状态"
	end

	return result,tips
end

---------------------------------------------------------------------------------------------------
--处于运镖状态
---------------------------------------------------------------------------------------------------
function x700026_CheckAllMemberErrorState_CrashBox( sceneId, selfId, teamnum )
    local tips,result

	result = 1

    -- 检查游戏状态是否正常
    for i = 0, teamnum - 1 do
        local memberId = GetNearTeamMember(sceneId, selfId, i);
        local state = IsPlayerMutexState(sceneId,memberId,PLAYER_STATE_CRASHBOX )
        if state == 1 then
            if result == 1 then
                result = 0
                tips = GetName(sceneId, memberId)
            else
                tips = tips..","..GetName(sceneId, memberId)
            end
        end
    end

	if result == 0 then
		tips = tips.." 处于运镖状态"
	end

	return result,tips
end

---------------------------------------------------------------------------------------------------
--处于代练或挂机状态
---------------------------------------------------------------------------------------------------
function x700026_CheckAllMemberErrorState_AutoPlay( sceneId, selfId, teamnum )
    local tips,result

	result = 1

    -- 检查游戏状态是否正常
    for i = 0, teamnum - 1 do
        local memberId = GetNearTeamMember(sceneId, selfId, i);
        local state = IsPlayerMutexState(sceneId,memberId,PLAYER_STATE_AUTOPLAY )
        local state2 = IsPlayerMutexState(sceneId,memberId,PLAYER_STATE_SUBTRAIN )
        if state == 1 or state2 == 1 then
            if result == 1 then
                result = 0
                tips = GetName(sceneId, memberId)
            else
                tips = tips..","..GetName(sceneId, memberId)
            end
        end
    end

	if result == 0 then
		tips = tips.." 处于代练或挂机状态"
	end

	return result,tips
end

---------------------------------------------------------------------------------------------------
--处于Bus状态
---------------------------------------------------------------------------------------------------
function x700026_CheckAllMemberErrorState_Bus( sceneId, selfId, teamnum )
    local tips,result

	result = 1

    -- 检查游戏状态是否正常
    for i = 0, teamnum - 1 do
        local memberId = GetNearTeamMember(sceneId, selfId, i);
        local state = IsPlayerMutexState(sceneId,memberId,PLAYER_STATE_BUS )
        if state == 1 then
            if result == 1 then
                result = 0
                tips = GetName(sceneId, memberId)
            else
                tips = tips..","..GetName(sceneId, memberId)
            end
        end
    end

	if result == 0 then
		tips = tips.." 处于BUS状态"
	end

	return result,tips
end

---------------------------------------------------------------------------------------------------
--处于监狱状态
---------------------------------------------------------------------------------------------------
function x700026_CheckAllMemberErrorState_Enjail( sceneId, selfId, teamnum )
    local tips,result

	result = 1


    -- 检查游戏状态是否正常
    for i = 0, teamnum - 1 do
        local memberId = GetNearTeamMember(sceneId, selfId, i);
        local state = IsPlayerMutexState(sceneId,memberId,PLAYER_STATE_ENJAIL )
        if state == 1 then
            if result == 1 then
                result = 0
                tips = GetName(sceneId, memberId)
            else
                tips = tips..","..GetName(sceneId, memberId)
            end
        end
    end

	if result == 0 then
		tips = tips.." 处于监禁状态"
	end

	return result,tips
end


---------------------------------------------------------------------------------------------------
--处于婚礼状态
---------------------------------------------------------------------------------------------------
function x700026_CheckAllMemberErrorState_Wedding( sceneId, selfId, teamnum )
    local tips,result

	result = 1


    -- 检查游戏状态是否正常
    for i = 0, teamnum - 1 do
        local memberId = GetNearTeamMember(sceneId, selfId, i);
        local state = IsPlayerMutexState(sceneId,memberId,PLAYER_STATE_WEDDING )
        if state == 1 then
            if result == 1 then
                result = 0
                tips = GetName(sceneId, memberId)
            else
                tips = tips..","..GetName(sceneId, memberId)
            end
        end
    end

	if result == 0 then
		tips = tips.." 处于婚礼状态"
	end

	return result,tips
end


---------------------------------------------------------------------------------------------------
--处于童趣状态
---------------------------------------------------------------------------------------------------
function x700026_CheckAllMemberErrorState_Tongqu( sceneId, selfId, teamnum )
    local tips,result

	result = 1


    -- 检查游戏状态是否正常
    for i = 0, teamnum - 1 do
        local memberId = GetNearTeamMember(sceneId, selfId, i);
        local state = IsPlayerMutexState(sceneId,memberId,PLAYER_STATE_TONGQUBUFF )
        if state == 1 then
            if result == 1 then
                result = 0
                tips = GetName(sceneId, memberId)
            else
                tips = tips..","..GetName(sceneId, memberId)
            end
        end
    end

	if result == 0 then
		tips = tips.." 处于童趣状态"
	end

	return result,tips
end


---------------------------------------------------------------------------------------------------
--处于铁三状态
---------------------------------------------------------------------------------------------------
function x700026_CheckAllMemberErrorState_Tiesan( sceneId, selfId, teamnum )
    local tips,result

	result = 1


    -- 检查游戏状态是否正常
    for i = 0, teamnum - 1 do
        local memberId = GetNearTeamMember(sceneId, selfId, i);
        local state = IsPlayerMutexState(sceneId,memberId,PLAYER_STATE_TIESAN )
        if state == 1 then
            if result == 1 then
                result = 0
                tips = GetName(sceneId, memberId)
            else
                tips = tips..","..GetName(sceneId, memberId)
            end
        end
    end

	if result == 0 then
		tips = tips.." 处于铁人三项状态"
	end

	return result,tips
end

---------------------------------------------------------------------------------------------------
--处于FubenReady
---------------------------------------------------------------------------------------------------
function x700026_CheckAllMemberErrorState_FubenReady( sceneId, selfId, teamnum )
    local tips,result

	result = 1


    -- 检查游戏状态是否正常
    for i = 0, teamnum - 1 do
        local memberId = GetNearTeamMember(sceneId, selfId, i);
        local state = IsPlayerMutexState(sceneId,memberId,PLAYER_STATE_READYFUBEN )
        if state == 1 then
            if result == 1 then
                result = 0
                --tips = GetName(sceneId, memberId)
            else
                --tips = tips..","..GetName(sceneId, memberId)
            end
			break;
        end
    end

	if result == 0 then
		tips = "您已经申请进入一个副本，请耐心等待"
	end

	return result,tips
end


function x700026_ShowTipsToAll(sceneId, str)

	local humancount = GetFuben_PlayerCount(sceneId);

	--通知玩家
	for i = 0, humancount - 1 do
		local humanId = GetFuben_PlayerObjId(sceneId, i);
		
		BeginQuestEvent(sceneId);
			AddQuestText(sceneId,str);
		EndQuestEvent();
		DispatchQuestTips(sceneId, humanId);
	end
end


--------------------------------------------------------------------------------------
-- 怪物和死亡脚本
--------------------------------------------------------------------------------------
function x700026_CreateNpc( sceneId)
	
	 local nRet = 0;
	 if x700026_g_GameNPC.title~="" then
		nRet = CreateMonster(sceneId, x700026_g_GameNPC.type, x700026_g_GameNPC.x, x700026_g_GameNPC.z, 3, 0, -1,x700026_g_GameNPC.guid, -1,-1,x700026_g_GameNPC.facedir, "",x700026_g_GameNPC.title )	
	 else
		nRet = CreateMonster(sceneId, x700026_g_GameNPC.type, x700026_g_GameNPC.x, x700026_g_GameNPC.z, 3, 0, -1,x700026_g_GameNPC.guid, -1,-1,x700026_g_GameNPC.facedir)	
	 
	 end

	 SetFubenData_Param(sceneId, x700026_CSP_NPC_ID, nRet )
end

--------------------------------------------------------------------------------------
-- 生长点脚本
--------------------------------------------------------------------------------------
function x700026_InitGrowXZ(sceneId)
	local posList ={}

	for i=1, 34 do
		local j= random(1,x700026_g_GrowPosLen)
		
		while 1>0 do
			local bDup =0;
			for k=1, i-1 do
				if posList[k] == j then
					j= random(1,x700026_g_GrowPosLen)
					bDup = 1;
					break;
				end
			end

			if bDup==0 then
				break;
			
			end
			
		end
		posList[i] = j;
		SetFubenData_Param(sceneId, x700026_CSP_GP_POSIDX_START+i,j)
	end
end


function x700026_InitMyGrowXZ(sceneId, iIndex)

	local j= random(1,x700026_g_GrowPosLen)
		
	while 1>0 do
		local bDup =0;
		for k=1, 34 do
			local nStatus = GetFubenData_Param(sceneId, x700026_CSP_GP_BOXID_START+k);

			if nStatus>=0 or nStatus==-1 then
				local nPosIndex= GetFubenData_Param(sceneId, x700026_CSP_GP_POSIDX_START+k)

				if nPosIndex==j then
					j= random(1,x700026_g_GrowPosLen)
					bDup = 1;
					break;
				end
			end
			
		end

		if bDup==0 then
			break;
		
		end
		
	end
	
	SetFubenData_Param(sceneId, x700026_CSP_GP_POSIDX_START+iIndex,j)

end


function x700026_OnCreateGrowPoint(sceneId,growPointType,tx,ty)
	
	local ItemBoxId = ItemBoxEnterScene(tx, ty, growPointType, sceneId, 0, -1)
	
	SetGrowPointObjID(sceneId,growPointType,tx,ty,ItemBoxId)
	
	--SetGrowPointPos(sceneId,growPointType,x,z)

	SetFubenData_Param(sceneId, x700026_CSP_GP_BOXID_START+growPointType-x700026_g_Start_GPID, ItemBoxId);
	SetFubenData_Param(sceneId, x700026_CSP_GP_ID_START+growPointType-x700026_g_Start_GPID, growPointType);	
	
end

function x700026_OnCreate(sceneId,growPointType,x,y)
	
	x700026_OnCreateGrowPoint(sceneId,growPointType,x,y)	
	
end



function x700026_OnOpen(sceneId,selfId,targetId)
	
	return 0;
	
end

function x700026_OnRecycle(sceneId,selfId,targetId)
	
	return 1;
	--return CallScriptFunction( MISSION_SCRIPT, "OnRecycle", sceneId, selfId, targetId, x700026_g_GrowpointId, x700026_g_ItemIndex )
end

function x700026_OnProcOver(sceneId,selfId,targetId)
	-- 采集完毕
	
	
	local nGrowpointId = 0;
	for i=1, 34 do
		local ItemBoxId = GetFubenData_Param(sceneId, x700026_CSP_GP_BOXID_START+i);
		if ItemBoxId== targetId then
			nGrowpointId = GetFubenData_Param(sceneId, x700026_CSP_GP_ID_START+i);
			local strPlayerName = GetName( sceneId,selfId)
			SetFubenData_Param(sceneId, x700026_CSP_GP_BOXID_START+i,-2);
			SetFubenData_Param(sceneId, x700026_CSP_GP_ID_START+i,-1);
			local strPaiName = "";
			if nGrowpointId-x700026_g_Start_GPID>0 and nGrowpointId-x700026_g_Start_GPID<=34 then
				strPaiName = x700026_g_Pai_NameList[nGrowpointId-x700026_g_Start_GPID].name
			else
--				PrintStr(format("error%d",nGrowpointId))
			end
			local str = strPlayerName.."采集了"..strPaiName
			x700026_ShowTipsToAll(sceneId, str)
			
			break;
		end
	end

	--RecycleGrowPointByType(sceneId,nGrowpointId,-1)
	SetGrowPointIntervalContainer(sceneId,nGrowpointId,x700026_g_GPInterval2)

	x700026_OnAnwer(sceneId,nGrowpointId)
	

	--CallScriptFunction( MISSION_SCRIPT, "OnProcOver", sceneId, selfId, targetId )
end


function x700026_OpenCheck(sceneId,selfId,AbilityId,AblityLevel)

	--CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end

--//added in 2009-3-17
---------------------------------------------------------------------------------------------------
--进入区域
---------------------------------------------------------------------------------------------------
function x700026_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

---------------------------------------------------------------------------------------------------
--离开区域
---------------------------------------------------------------------------------------------------
function x700026_ProcAreaLeaved( sceneId, selfId, ScriptId, MissionId )
end
--//add end







