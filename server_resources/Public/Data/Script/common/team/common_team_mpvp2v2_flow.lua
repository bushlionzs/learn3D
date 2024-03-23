--########################################
--##跨服 2v2 战场主脚本 by rj 2010-9-24 ##
--########################################

x303101_g_scriptId 					=   303101
x303101_g_GrowPointScriptId         = 	303104
-------------------------------------------------------------
--队伍A的信息
-------------------------------------------------------------
x303101_TeamInfoA					= 	{}							  
x303101_TeamInfoB					= 	{}

-------------------------------------------------------------
--等级差标记
-------------------------------------------------------------									  									  
x303101_LevelFlag					= 	{}

-------------------------------------------------------------
--场景相关信息
-------------------------------------------------------------									  
x303101_SceneInfo					= 	{}

-------------------------------------------------------------
--场景启用相关信息
-------------------------------------------------------------
x303101_g_SceneMapNavPath			= 	{	{"zhanchang_mshuangrenzhanchang/zhanchang_mshuangrenzhanchang.scn", 1, 1},	--场景1
											{"zhanchang_mshuangrenzhanchang/zhanchang_mshuangrenzhanchang.scn", 2, 0},	--场景2
											{"zhanchang_mshuangrenzhanchang/zhanchang_mshuangrenzhanchang.scn", 3, 0},	--场景3
										}
										
x303101_g_TempImpassable			=	{
											{Left = 89, Top = 71,Right = 168, Bottom = 183, Flag = 1},
										}

-------------------------------------------------------------
--战场进入位置信息
-------------------------------------------------------------
x303101_g_EnterScenePos				=	{
											{ {79, 124}, {79, 131}, {176, 124}, {176, 132} },	--进入场景的坐标，与上面的场景相对应
											{ {27, 106}, {23, 107}, {101,107}, {104,107} },
											{ {31, 102}, {27, 99}, {93, 28}, {98, 29} },
										}

x303101_g_CloseTick					= 	10														--关闭场景倒计时
x303101_g_LimitTotalHoldTime		=	4 * 60													--战场最大时间
x303101_g_Kick_Down					=	4														--踢人倒计时
x303101_g_GameId					=	1221													--玩法ID

-------------------------------------------------------------
--玩家基本阵营信息
-------------------------------------------------------------										
x303101_g_CampFlag					= 	{5, 6}												--基础阵营号

-------------------------------------------------------------
--奖励相关
-------------------------------------------------------------
x303101_g_Winner_Bonus_Level		= 	1				--加
x303101_g_Winner_Bonus_Mark			= 	30
x303101_g_Loser_Bonus_Level			= 	1				--减
x303101_g_Loser_Bonus_Mark			= 	7
x303101_g_Other_Bonus_Mark			= 	7

-------------------------------------------------------------
--相关状态
-------------------------------------------------------------
x303101_g_State_Invalid				= 	-1
x303101_g_State_Signup				=  	0
x303101_g_State_SignupFinished		=  	1
x303101_g_State_Begin				=  	2
x303101_g_State_End					=  	3
x303101_g_CurrentState				= 	{}

-------------------------------------------------------------
--随机buf种类，根据玩家级别段不同配置 2010-11-3 by rj
-------------------------------------------------------------
x303101_g_RandBuf_40				= 	{30000, 30010, 30020, 30030, 30040, 30050, 30060}
x303101_g_RandBuf_50				= 	{30001, 30011, 30021, 30031, 30041, 30051, 30061}
x303101_g_RandBuf_60				= 	{30002, 30012, 30022, 30032, 30042, 30052, 30062}
x303101_g_RandBuf_70				= 	{30003, 30013, 30023, 30033, 30043, 30053, 30063}
x303101_g_RandBuf_80				= 	{30004, 30014, 30024, 30034, 30044, 30054, 30064}
x303101_g_RandBuf_90				= 	{30005, 30015, 30025, 30035, 30045, 30055, 30065}
x303101_g_RandBuf_100				= 	{30006, 30016, 30026, 30036, 30046, 30056, 30066}
x303101_g_RandBufName				= 	{}				--采集箱子buf对应名字，key是bufid

-------------------------------------------------------------
--获得奖牌配置 2010-11-3 by rj
-------------------------------------------------------------
x303101_g_Award_ItemID				= 	12266663		--牌子物品ID
x888888_g_AwardGetBufList			= 	{9011,9012,9013}	--奖牌获得许可获得buf
x303101_g_Award_LevelInfo			=  					--奖励级别信息，不同级别有不同的输赢奖励
{ 
{minlevel = 40, maxlevel = 49, win = 1, lose = 0, normal = 0}, 
{minlevel = 50, maxlevel = 59, win = 1, lose = 0, normal = 0}, 
{minlevel = 60, maxlevel = 69, win = 2, lose = 0, normal = 0}, 
{minlevel = 70, maxlevel = 79, win = 2, lose = 0, normal = 0}, 
{minlevel = 80, maxlevel = 89, win = 3, lose = 0, normal = 0}, 
{minlevel = 90, maxlevel = 99, win = 3, lose = 0, normal = 0}, 
{minlevel = 100, maxlevel = 160, win = 3, lose = 0, normal = 0}, 
}

-------------------------------------------------------------
--采集宝箱配置 2010-11-3 by rj
-------------------------------------------------------------
x303101_g_GrowPoint_RefreshInterval	= 	20				--采集宝箱刷新间隔
x303101_g_GrowPoint_TimerTbl		= 	{}				--采集宝箱定时计数器

-------------------------------------------------------------
--获得战场功绩配置 2010-11-8 by rj
-------------------------------------------------------------
x303101_g_BattleHonour_WinVal		= 	40				--胜利获得战场功绩
x303101_g_BattleHonour_NormalVal	= 	10				--平局获得战场功绩
x303101_g_BattleHonour_LoseVal		= 	10				--输局获得战场功绩

function x303101_OnMapInit(sceneId)
	
	--队伍A的信息
	x303101_TeamInfoA[sceneId]			= {	
											{GUID = -1, DIE = 0, ENTER = 0,LEAVE = 0 },
											{GUID = -1, DIE = 0, ENTER = 0,LEAVE = 0 }
										  }
	
	--队伍B的信息
	x303101_TeamInfoB[sceneId]			= {	
											{GUID = -1, DIE = 0, ENTER = 0, LEAVE = 0 },
											{GUID = -1, DIE = 0, ENTER = 0, LEAVE = 0 }
										  }

	--等级差标记
	x303101_LevelFlag[sceneId]			= 0
	
	--场景相关信息
	x303101_SceneInfo[sceneId]			= {
											TICKCOUNT = 0,
											ISCLOSING = 0,
											LEAVECOUNTDOWN = 0,
											RESULT = 0,
											LIMITHOLDTIME = 5 * 60,
										  }
										  
	x303101_g_CurrentState[sceneId]		= x303101_g_State_Invalid
	x303101_g_GrowPoint_TimerTbl[sceneId] = 0
	
	--初始化进场随机buf名字，key是bufid
	x303101_g_RandBufName[30000] = "攻击增加250点"
	x303101_g_RandBufName[30001] = "攻击增加400点"
	x303101_g_RandBufName[30002] = "攻击增加550点"
	x303101_g_RandBufName[30003] = "攻击增加700点"
	x303101_g_RandBufName[30004] = "攻击增加1000点"
	x303101_g_RandBufName[30005] = "攻击增加1300点"
	x303101_g_RandBufName[30006] = "攻击增加1600点"
	x303101_g_RandBufName[30010] = "防御增加250点"
	x303101_g_RandBufName[30011] = "防御增加400点"
	x303101_g_RandBufName[30012] = "防御增加550点"
	x303101_g_RandBufName[30013] = "防御增加700点"
	x303101_g_RandBufName[30014] = "防御增加1000点"
	x303101_g_RandBufName[30015] = "防御增加1300点"
	x303101_g_RandBufName[30016] = "防御增加1600点"
	x303101_g_RandBufName[30020] = "血量上限增加2500点"
	x303101_g_RandBufName[30021] = "血量上限增加4000点"
	x303101_g_RandBufName[30022] = "血量上限增加5500点"
	x303101_g_RandBufName[30023] = "血量上限增加7000点"
	x303101_g_RandBufName[30024] = "血量上限增加10000点"
	x303101_g_RandBufName[30025] = "血量上限增加13000点"
	x303101_g_RandBufName[30026] = "血量上限增加16000点"
	x303101_g_RandBufName[30030] = "暴击增加10点"
	x303101_g_RandBufName[30031] = "暴击增加15点"
	x303101_g_RandBufName[30032] = "暴击增加20点"
	x303101_g_RandBufName[30033] = "暴击增加25点"
	x303101_g_RandBufName[30034] = "暴击增加30点"
	x303101_g_RandBufName[30035] = "暴击增加40点"
	x303101_g_RandBufName[30036] = "暴击增加50点"
	x303101_g_RandBufName[30040] = "命中增加10点"
	x303101_g_RandBufName[30041] = "命中增加15点"
	x303101_g_RandBufName[30042] = "命中增加20点"
	x303101_g_RandBufName[30043] = "命中增加25点"
	x303101_g_RandBufName[30044] = "命中增加30点"
	x303101_g_RandBufName[30045] = "命中增加40点"
	x303101_g_RandBufName[30046] = "命中增加50点"
	x303101_g_RandBufName[30050] = "韧性增加10点"
	x303101_g_RandBufName[30051] = "韧性增加15点"
	x303101_g_RandBufName[30052] = "韧性增加20点"
	x303101_g_RandBufName[30053] = "韧性增加25点"
	x303101_g_RandBufName[30054] = "韧性增加30点"
	x303101_g_RandBufName[30055] = "韧性增加40点"
	x303101_g_RandBufName[30056] = "韧性增加50点"
	x303101_g_RandBufName[30060] = "闪避增加10点"
	x303101_g_RandBufName[30061] = "闪避增加15点"
	x303101_g_RandBufName[30062] = "闪避增加20点"
	x303101_g_RandBufName[30063] = "闪避增加25点"
	x303101_g_RandBufName[30064] = "闪避增加30点"
	x303101_g_RandBufName[30065] = "闪避增加40点"
	x303101_g_RandBufName[30066] = "闪避增加50点"

end

----------------------------------------------------------------------------------------------
--添加物品
----------------------------------------------------------------------------------------------
function x303101_AddItem(sceneId, playerId, nItemID, nType)

	local nItemNum = 0
	local nPlayerLevel = GetLevel(sceneId, playerId)
	
	--找出自身级别的奖牌数量
    for i, item in x303101_g_Award_LevelInfo do
        if nPlayerLevel >= item.minlevel and nPlayerLevel <= item.maxlevel then
            if nType == 0 then
            	nItemNum = item.normal
            elseif nType == 1 then
            	nItemNum = item.win
            elseif nType == 2 then
            	nItemNum = item.lose
            end
        end
    end
    
	if nItemNum > 0 then
	
		--根据是否有buf而获得是否绑定的物品
		local bHaveBuf = 0
		for i, item in x888888_g_AwardGetBufList do
			if IsHaveSpecificImpact(sceneId, playerId, item) > 0 then
				bHaveBuf = 1
				break
			end
		end
		
		BeginAddItem(sceneId)

		if bHaveBuf == 1 then
			AddItem(sceneId, nItemID, nItemNum)
		else
            AddBindItem(sceneId, nItemID, nItemNum)
		end
		
		if EndAddItem(sceneId, playerId) > 0 then
			AddItemListToPlayer(sceneId, playerId)
	 		WriteLog(1, format("MP2BL:x303101_AddItem 1 SceneId=%d PlayerGUID=%u Param1=%u Param2=%d Param3=%d", 
	 			sceneId, GetGUID(sceneId, playerId), nItemID, nItemNum, nType))
		else
			Msg2Player(sceneId, playerId, "背包已满，无法获得奖励物品", 8, 3)
			Msg2Player(sceneId, playerId, "背包已满，无法获得奖励物品", 8, 2)
	 		WriteLog(1, format("MP2BL:x303101_AddItem 2 SceneId=%d PlayerGUID=%u Param1=%u Param2=%d Param3=%d", 
	 			sceneId, GetGUID(sceneId, playerId), nItemID, nItemNum, nType))
		end
	end
end

----------------------------------------------------------------------------------------------
--取得2V2战场类型
----------------------------------------------------------------------------------------------
function x303101_GetBattleSceneType(sceneId)

    local name = GetBattleSceneName(sceneId)
    for i, item in x303101_g_SceneMapNavPath do
        if name == item[1] then
            return item[2]
        end
    end
    return -1
end

----------------------------------------------------------------------------------------------
--战场是否被启用
----------------------------------------------------------------------------------------------
function x303101_IsBattleSceneValid(sceneId)

    local name = GetBattleSceneName(sceneId)
    for i, item in x303101_g_SceneMapNavPath do
        if name == item[1] then
            return item[3]
        end
    end
    return 0
end

----------------------------------------------------------------------------------------------
--报名场景状态回调
----------------------------------------------------------------------------------------------
function x303101_OnMBattleState_SignupScene(sceneId, state)

	--必须是报名场景
	if GetSceneType(sceneId) ~= 8 then
		return
	end

	--相关状态处理。注意，报名场景与战场场景的 x303101_g_CurrentState 是在两个线程里内容是两份。
	if state == x303101_g_State_Signup then

        if x303101_g_CurrentState[sceneId] ~= x303101_g_State_Signup then
            WriteLog(1, format("MP2BL:x303101_g_State_Signup, SceneId=%d", sceneId))
        end
        
        x303101_g_CurrentState[sceneId] = x303101_g_State_Signup
        
    elseif state == x303101_g_State_SignupFinished then

        if x303101_g_CurrentState[sceneId] ~= x303101_g_State_SignupFinished then
            WriteLog(1, format("MP2BL:x303101_g_State_SignupFinished,SceneId=%d", sceneId))
        end
        
        x303101_g_CurrentState[sceneId] = x303101_g_State_SignupFinished
    elseif state == x303101_g_State_Begin then
    
   	 	--本班次战场开始，给报名场景上的所有玩家添加签证，使其不进入就要被传走
   		CallScriptFunction(MPVP2V2_SIGNUP_SCRIPT, "Set2V2SignAndClean", sceneId)
    end
end

----------------------------------------------------------------------------------------------
--战场状态
----------------------------------------------------------------------------------------------
function x303101_OnMBattleState(sceneId, state)

	local sceneType = GetSceneType(sceneId)
	if sceneType == 8 then
		x303101_OnMBattleState_SignupScene(sceneId, state)
	elseif sceneType == 7 then
		x303101_OnBattleState_BattleScene(sceneId, state)
	end
end

----------------------------------------------------------------------------------------------
--战场场景状态处理
----------------------------------------------------------------------------------------------
function x303101_OnBattleState_BattleScene(sceneId, state)

	--检查是否是PVP2v2竞技场
    if  x303101_GetBattleSceneType(sceneId) <= 0 then
        return
    end
    
    --检查场景是否有效
    if x303101_IsBattleSceneValid(sceneId) ~= 1 then
    	return	
    end

    if state == x303101_g_State_Signup then
    	
    	--检测是否已经开始
    	if x303101_g_CurrentState[sceneId] == x303101_g_State_Begin then
    		return
    	end
    	
        if x303101_g_CurrentState[sceneId] ~= x303101_g_State_Signup then
            WriteLog(1, format("MP2BL:x303101_g_State_Signup, SceneId=%d", sceneId))
        end
        
        --设置当前场景报名开始标志并进行这个 2v2 场景的注册
        x303101_g_CurrentState[sceneId] = x303101_g_State_Signup
        MPVP2v2RegisterScene(sceneId)
        
    elseif state == x303101_g_State_Begin then

        if x303101_g_CurrentState[sceneId] ~= x303101_g_State_Begin then
            WriteLog(1, format("MP2BL:x303101_g_State_Begin, SceneId=%d", sceneId))
        end

        --设置战场开始状态并启动开始前预处理
        x303101_g_CurrentState[sceneId] = x303101_g_State_Begin
        x303101_OnBattleSceneReady(sceneId, x303101_g_LimitTotalHoldTime)

    elseif state == x303101_g_State_End then

		--关闭小场时异常状态
        if x303101_g_CurrentState[sceneId] > x303101_g_State_Begin or x303101_g_CurrentState[sceneId] < x303101_g_State_Signup then
            
            WriteLog(1, format("MP2BL:x303101_g_State_End,Result:nState > x303101_g_State_Begin or nState < x303101_g_State_Signup SceneId=%d, state=%d", 
            	sceneId, x303101_g_CurrentState[sceneId]))

            x303101_OnBattleSceneClose(sceneId, 0)
            WriteLog(1, format("MP2BL:x303101_g_State_End, SceneId=%d", sceneId))
            return
        end

        --设置状态，小场结束，清理
		x303101_g_CurrentState[sceneId] = x303101_g_State_End
        x303101_OnBattleSceneClose(sceneId, 1)

        WriteLog(1, format("MP2BL:x303101_g_State_End, SceneId=%d", sceneId))
    end
end

----------------------------------------------------------------------------------------------
--战场是否正在报名
----------------------------------------------------------------------------------------------
function x303101_IsBattleSignup(sceneId)

	--必须是报名场景且已经开始报名
	if GetSceneType(sceneId) == 8 and x303101_g_CurrentState[sceneId] == x303101_g_State_Signup then
		return 1
	end
	return 0
end

----------------------------------------------------------------------------------------------
--开启报名签证
----------------------------------------------------------------------------------------------
function x303101_SetSignupSign(sceneId, humanId)

	--对开启报名签证并记录签证时间
	SetQuestData(sceneId, humanId, MD_MBATTLE_SIGNSTATE[1], MD_MBATTLE_SIGNSTATE[2], MD_MBATTLE_SIGNSTATE[3], 1)
	SetQuestData(sceneId, humanId, MD_MBATTLE_SIGNTIME[1], MD_MBATTLE_SIGNTIME[2], MD_MBATTLE_SIGNTIME[3], MBATTLE_SIGNUP_SIGNTIME)
end

----------------------------------------------------------------------------------------------
--战场匹配队伍信息回调
----------------------------------------------------------------------------------------------
function x303101_OnMBattleMatchInfo(sceneId, leaderguid1, otherguid1, leaderguid2, otherguid2, nLevelFlag)
	
	--队伍A的信息
	x303101_TeamInfoA[sceneId]			= {	
											{GUID = leaderguid1, DIE = 0, ENTER = 0, LEAVE = 0},
											{GUID = otherguid1, DIE = 0, ENTER = 0, LEAVE = 0},
										  }

	--队伍B的信息								  
	x303101_TeamInfoB[sceneId]			= {	
											{GUID = leaderguid2, DIE = 0, ENTER = 0, LEAVE = 0},
											{GUID = otherguid2, DIE = 0, ENTER = 0, LEAVE = 0},
										  }
										  
	--等级差标记
	x303101_LevelFlag[sceneId]			= nLevelFlag
	
	--调用采集点初始化函数，回收所有采集点
	CallScriptFunction(x303101_g_GrowPointScriptId, "OnInit", sceneId)
	--重新初始化采集定时计数器	
	x303101_g_GrowPoint_TimerTbl[sceneId] = 0
end

---------------------------------------------------------------------------------------------------
--取得玩家所在队伍
---------------------------------------------------------------------------------------------------
function x303101_GetPlayerTeamIndex(sceneId, selfId)
	
	local GUID = GetPlayerGUID(sceneId, selfId)
	
	local p = NumberCastIntToUInt(x303101_TeamInfoA[sceneId][1].GUID)
	if GUID == p then
		return 0
	end
	
	p = NumberCastIntToUInt(x303101_TeamInfoA[sceneId][2].GUID)
	if GUID == p then
		return 0
	end
	
	p = NumberCastIntToUInt(x303101_TeamInfoB[sceneId][1].GUID)
	if GUID == p then
		return 1
	end
	
	p = NumberCastIntToUInt(x303101_TeamInfoB[sceneId][2].GUID)
	if GUID == p then
		return 1
	end
	
	return -1
end

---------------------------------------------------------------------------------------------------
--取得玩家位置
---------------------------------------------------------------------------------------------------
function x303101_GetPlayerPos(sceneId, selfId)
	
	local GUID = GetPlayerGUID(sceneId, selfId)
	local nIndex = x303101_GetBattleSceneType(sceneId)
	
	--如果无效
	if nIndex < 1 or nIndex > getn(x303101_g_EnterScenePos) then
		return 100, 100
	end
	
	local p = NumberCastIntToUInt(x303101_TeamInfoA[sceneId][1].GUID)
	if GUID == p then
		local x = x303101_g_EnterScenePos[nIndex][1][1]
		local z = x303101_g_EnterScenePos[nIndex][1][2]
		return x, z
	end
	
	p = NumberCastIntToUInt(x303101_TeamInfoA[sceneId][2].GUID)
	if GUID == p then
		local x = x303101_g_EnterScenePos[nIndex][2][1]
		local z = x303101_g_EnterScenePos[nIndex][2][2]
		return x, z
	end
	
	p = NumberCastIntToUInt(x303101_TeamInfoB[sceneId][1].GUID)
	if GUID == p then
		local x = x303101_g_EnterScenePos[nIndex][3][1]
		local z = x303101_g_EnterScenePos[nIndex][3][2]
		return x, z
	end
	
	p = NumberCastIntToUInt(x303101_TeamInfoB[sceneId][2].GUID)
	if GUID == p then
		local x = x303101_g_EnterScenePos[nIndex][4][1]
		local z = x303101_g_EnterScenePos[nIndex][4][2]
		return x, z
	end
	
	return 100,100
end


---------------------------------------------------------------------------------------------------
--玩家进入战场时的处理
---------------------------------------------------------------------------------------------------
function x303101_OnPlayerEnter(sceneId, selfId)

	--检查是否是PVP2v2竞技场
    if x303101_GetBattleSceneType(sceneId) <= 0 then
        return
    end
    
    --检查场景是否有效
    if x303101_IsBattleSceneValid(sceneId) ~= 1 then
    	return	
    end
	
	--取得保存的回退场景
    local scenePre = GetPlayerRuntimeData(sceneId,selfId, RD_HUMAN_SCENE_PRE) - 1
    if scenePre >= 0 then
    
        --保存回退场景信息
        local CurX = GetPlayerRuntimeData(sceneId, selfId, RD_HUMAN_POSX_PRE)
        local CurZ = GetPlayerRuntimeData(sceneId, selfId, RD_HUMAN_POSZ_PRE)
        SetPlayerBakSceneInfo(sceneId, selfId, scenePre, CurX, CurZ)
        
        SetPlayerRuntimeData(sceneId, selfId, RD_HUMAN_SCENE_PRE, 0)
        SetPlayerRuntimeData(sceneId, selfId, RD_HUMAN_POSX_PRE, 0)
        SetPlayerRuntimeData(sceneId, selfId, RD_HUMAN_POSZ_PRE, 0)
    end
    
	--再次上线，如果开始关闭，要踢出去
	if x303101_SceneInfo[sceneId].ISCLOSING > 0 then
		
		--在战场掉线再上线战场已结束回到报名场景时需要启动报名签证
		x303101_SetPlayerNeedKick(sceneId, selfId)
		WriteLog(1, format("MP2BL:x303101_OnPlayerEnterFinished kick 0 SceneId=%d ", sceneId))
		return
	end
	
	--如果玩家无效（再次上线不是本场的玩家）
	if x303101_CheckPlayerValid(sceneId, selfId) == 0 then
		x303101_SetPlayerNeedKick(sceneId, selfId)
		WriteLog(1, format("MP2BL:x303101_OnPlayerEnterFinished kick 1 SceneId=%d ", sceneId))
		return
	end
	
	--如果玩家曾经死亡
	if x303101_GetPlayerDieFlag(sceneId, selfId) == 1 then
		x303101_SetPlayerNeedKick(sceneId, selfId)
		WriteLog(1, format("MP2BL:x303101_OnPlayerEnterFinished kick 2 SceneId=%d ", sceneId))		
		return
	end
	
	--如果玩家已经进过场景了
	if x303101_GetPlayerEnterSceneFlag(sceneId, selfId) == 1 then
		x303101_SetPlayerNeedKick(sceneId, selfId)
		WriteLog(1, format("MP2BL:x303101_OnPlayerEnterFinished kick 3 SceneId=%d ", sceneId))
		return
	end
	
	--验证所在队伍索引
	local nTeamIndex = x303101_GetPlayerTeamIndex(sceneId, selfId)
	if nTeamIndex < 0 or nTeamIndex > 1 then
		x303101_SetPlayerNeedKick(sceneId, selfId)
		WriteLog(1, format("MP2BL:x303101_OnPlayerEnterFinished kick 4 SceneId=%d ", sceneId))
		return
	end
	
	--设置对战阵营，可以互相开启攻击
	SetCurCamp(sceneId, selfId, x303101_g_CampFlag[nTeamIndex + 1])

	--设置玩家位置
	local x, z = x303101_GetPlayerPos(sceneId, selfId)
	SetPos(sceneId, selfId, x, z)
	
	WriteLog(1, format("MP2BL:x303101_OnPlayerEnterFinished playerEnter SceneId=%d x = %d, z = %d flag = %d name=%s", 
		sceneId, x, z, nTeamIndex, GetName(sceneId, selfId)))
	
	--设置玩家进入场景标记
	x303101_SetPlayerEnterSceneFlag(sceneId, selfId)
	
	--以队伍索引设置玩家名字颜色
	SetMPVP2v2BattleDisable(sceneId, selfId, 0, nTeamIndex)
	
	--检查是否可以播放特效
	if x303101_SceneInfo[sceneId].TICKCOUNT < 31 then
		CallScriptFunction(UTILITY_SCRIPT,"PlayClientMapColor", sceneId, selfId, 0, 0)
	end
	
	--增加随机buf 2010-11-3 by rj
	-- local nPlayerLevel = GetLevel(sceneId, selfId)
	
	-- local tblBuffer = {}
	
	-- if nPlayerLevel >= 40 and nPlayerLevel <= 49 then
		-- tblBuffer = x303101_g_RandBuf_40
	-- elseif nPlayerLevel >= 50 and nPlayerLevel <= 59 then
		-- tblBuffer = x303101_g_RandBuf_50
	-- elseif nPlayerLevel >= 60 and nPlayerLevel <= 69 then
		-- tblBuffer = x303101_g_RandBuf_60
	-- elseif nPlayerLevel >= 70 and nPlayerLevel <= 79 then
		-- tblBuffer = x303101_g_RandBuf_70
	-- elseif nPlayerLevel >= 80 and nPlayerLevel <= 89 then
		-- tblBuffer = x303101_g_RandBuf_80
	-- elseif nPlayerLevel >= 90 and nPlayerLevel <= 99 then
		-- tblBuffer = x303101_g_RandBuf_90
	-- elseif nPlayerLevel >= 100 then
		-- tblBuffer = x303101_g_RandBuf_100
	-- end
	
	-- local nBufNum = getn(tblBuffer)
	-- if nBufNum > 0 then
		-- local bufIdx = random(1, nBufNum)
		-- SendSpecificImpactToUnit(sceneId, selfId, selfId, selfId, tblBuffer[bufIdx], 0)
		-- if x303101_g_RandBufName[tblBuffer[bufIdx]] ~= nil then
			-- Msg2Player(sceneId, selfId, format("进入战场，随机分配到了【%s】效果", x303101_g_RandBufName[tblBuffer[bufIdx]]), 8, 2)
			-- Msg2Player(sceneId, selfId, format("进入战场，随机分配到了【%s】效果", x303101_g_RandBufName[tblBuffer[bufIdx]]), 8, 3)	
			-- RestoreHp(sceneId, selfId,0)
			-- RestoreRage(sceneId, selfId,100)
			-- WriteLog(1, format("MP2BL:x303101_OnPlayerEnter 1 SceneId=%d PlayerGUID=%u Param1=%d", sceneId, GetGUID(sceneId, selfId), tblBuffer[bufIdx]))				
		-- end
	-- end
end

---------------------------------------------------------------------------------------------------
--玩家离开场景
---------------------------------------------------------------------------------------------------
function x303101_OnPlayerLeave(sceneId, selfId)

	local nDebug = 1
	
	if nDebug == 1 then
        WriteLog(1, format("MP2BL:x303101_OnPlayerLeave 0 SceneId=%d Name=%s 2v2 LevelPre = %d", sceneId, GetName(sceneId,selfId), GetPVP2V2Level(sceneId,selfId)))
	end

	--检查是否是PVP2v2竞技场
    if  x303101_GetBattleSceneType(sceneId) <= 0 then
        return
    end
    
    --检查场景是否有效
    if x303101_IsBattleSceneValid(sceneId) ~= 1 then
    	return	
    end
	
	--如果开始关闭，则玩家离开不处理（正常结束）
	if x303101_SceneInfo[sceneId].ISCLOSING > 0 then
		return
	end

	if x303101_GetPlayerLeaveSceneFlag(sceneId, selfId) == 0 then
		
		x303101_SetPlayerLeaveSceneFlag(sceneId, selfId)
		
		local n2v2LevelPre = GetPVP2V2Level(sceneId, selfId)
		
		--中途退出或是非战场判定胜负的情况下，退出，等级减一惩罚
		x303101_SubPVP2V2Level(sceneId, selfId, x303101_g_Loser_Bonus_Level)
		
		local n2v2LevelAfter = GetPVP2V2Level(sceneId,selfId)

        WriteLog(1, format("MP2BL:x303101_OnPlayerLeave 1 SceneId=%d Name=%s 2v2LevelPre = %d 2v2LevelAfter=%d", 
        	sceneId, GetName(sceneId, selfId), n2v2LevelPre, n2v2LevelAfter))
	end	
end

---------------------------------------------------------------------------------------------------
--战场定时器
---------------------------------------------------------------------------------------------------
function x303101_ProcTiming(sceneId, nowTime)

	--检查是否是PVP2v2竞技场
    if  x303101_GetBattleSceneType(sceneId) <= 0 then
        return
    end
    
    --检查场景是否有效
    if x303101_IsBattleSceneValid(sceneId) ~= 1 then
    	return	
    end

	x303101_UpdatePlayerKickState(sceneId)

	--已经开始关闭了
	if x303101_SceneInfo[sceneId].ISCLOSING > 0 then

		local leaveCountDown = x303101_SceneInfo[sceneId].LEAVECOUNTDOWN + 1
		x303101_SceneInfo[sceneId].LEAVECOUNTDOWN = leaveCountDown
		
		if leaveCountDown >= x303101_g_CloseTick then
		
			--倒计时结束踢人
			local humanCount = GetScenePlayerCount(sceneId)
			for	i = 0, humanCount - 1 do
				local humanId = GetScenePlayerObjId(sceneId, i)
                TimerCommand(sceneId, humanId, 1, GUILDBATTLE_TIMERID, GUILDBATTLE_TIMERTYPE, x303101_g_scriptId, -1, -1)	--发送定时器，做定时器同步

                --调用踢人函数
                x303101_SetPlayerNeedKick(sceneId, humanId)
                WriteLog(1, format("MP2BL:x303101_ProcTiming kick 1 SceneId=%d ", sceneId))
			end
		elseif leaveCountDown < x303101_g_CloseTick then  
		
			--提示xx秒后将退出副本
			local humanCount = GetScenePlayerCount(sceneId)
			for	i = 0, humanCount - 1 do
				local humanId = GetScenePlayerObjId(sceneId, i)
  				Msg2Player(sceneId, humanId, format("本场战斗将在%d秒后关闭", x303101_g_CloseTick - leaveCountDown), 8, 3)
			end			
		end
	else
		if x303101_g_CurrentState[sceneId] ~= x303101_g_State_Begin then
			return
		end
		
		local nowTickCount = x303101_SceneInfo[sceneId].TICKCOUNT + 1;
		x303101_SceneInfo[sceneId].TICKCOUNT = nowTickCount
		
		--超过30秒，清除动态阻挡
		if nowTickCount == 31 then
			x303101_ClearTempImpassable(sceneId)
		end
			
		--每 N 秒在战场非关闭倒计时状态下且有玩家的情况下进行资源刷新，不能使用 nowTickCount 这个值将被同步时间函数定时改变会跳过某次执行 2010-11-3 by rj
		x303101_g_GrowPoint_TimerTbl[sceneId] = x303101_g_GrowPoint_TimerTbl[sceneId] + 1
		if mod(x303101_g_GrowPoint_TimerTbl[sceneId], x303101_g_GrowPoint_RefreshInterval) == 0 then
			if GetScenePlayerCount(sceneId) ~= 0 then
				CallScriptFunction(x303101_g_GrowPointScriptId, "OnTimeMakeGrowPoint", sceneId)
			end
		end
		
		--当超过一分钟后，开始检胜利（空场都在这里被检测完成，空场也都是设置战场开始、结束状态并置 ISCLOSING 的）
		if nowTickCount >= 60 then
			if x303101_CheckBattleFinished(sceneId) == 1 then
				x303101_OnBattleSceneClose(sceneId, 2)			
                WriteLog(1, format("MP2BL:x303101_ProcTiming sceneId=%d,nowTickCount=%d 000", sceneId, nowTickCount))
			end
		end

		--战场计时器，程序中设置一场为 4 分钟，到时会发来 x303101_g_State_End 进行结束。这行防止消息阻塞自行结束。
		if nowTickCount >= x303101_g_LimitTotalHoldTime then
			local humanCount = GetScenePlayerCount(sceneId)
			for i = 0, humanCount - 1 do
				local humanId = GetScenePlayerObjId(sceneId, i)
  				Msg2Player(sceneId, humanId, format("本场战斗时间已到，将于%d秒后关闭！", x303101_g_CloseTick), 8, 3)
			end
			
            x303101_OnBattleSceneClose(sceneId, 3)
            WriteLog(1, format("MP2BL:x303101_ProcTiming sceneId=%d, nowTickCount=%d 001", sceneId, nowTickCount))
		end
	end
end

---------------------------------------------------------------------------------------------------
--玩家死亡
---------------------------------------------------------------------------------------------------
function x303101_OnPlayerDie(sceneId, selfId, killerId)	
	
	--检查是否是PVP2v2竞技场
    if  x303101_GetBattleSceneType(sceneId) <= 0 then
        return
    end
    
    --检查场景是否有效
    if x303101_IsBattleSceneValid(sceneId) ~= 1 then
    	return	
    end
    
	x303101_SetPlayerDieFlag(sceneId, selfId)
	
	--检查战场是否可结束，主动死亡监测，不需要定时器 1 分钟后的限制
	if x303101_CheckBattleFinished(sceneId) == 1 then
		x303101_OnBattleSceneClose(sceneId, 4)	
        WriteLog(1, format("MP2BL:x303101_OnPlayerDie sceneId=%d  002", sceneId))
	end
end

---------------------------------------------------------------------------------------------------
--玩家复活, 2v2 战场玩家不许主动复活
---------------------------------------------------------------------------------------------------
function x303101_OnPlayerRelive(sceneId, selfId, ReliveType)
	
	--检查是否是PVP2v2竞技场
    if  x303101_GetBattleSceneType(sceneId) <= 0 then
        return
    end
    
    --检查场景是否有效
    if x303101_IsBattleSceneValid(sceneId) ~= 1 then
    	return	
    end

	--战场结束后不可复活
	if x303101_SceneInfo[sceneId].ISCLOSING > 0 then
		return
	end
	
  	Msg2Player(sceneId, selfId, "跨服双人战场比赛结束之前不能复活，请耐心等待！", 8, 3)
end

---------------------------------------------------------------------------------------------------
--复活，踢人时使用
---------------------------------------------------------------------------------------------------
function x303101_DoPlayerRelive(sceneId, selfId, value)

	--只有死亡的玩家进行处理
	local nHp = GetHp(sceneId, selfId)
	if nHp <= 0 then
	
		ClearRageRecoverTick(sceneId, selfId)
		RestoreHp(sceneId, selfId, value)
		RestoreRage(sceneId, selfId, value)
		ClearMutexState(sceneId, selfId, 6)
		SendReliveResult(sceneId, selfId,1)
	end
	
	--骑上马,并且回血
	LastMount(sceneId, selfId)
	RestoreHp(sceneId, selfId, 0)
end

---------------------------------------------------------------------------------------------------
--踢人
---------------------------------------------------------------------------------------------------
function x303101_KickPlayer(sceneId, selfId)
	
	--启动报名签证
	x303101_SetSignupSign(sceneId, selfId)

	--清除死亡状态
    x303101_DoPlayerRelive(sceneId, selfId, 100)
    x303101_RestorePlayerCamp(sceneId, selfId)
    SetPlayerRuntimeData(sceneId, selfId, RD_BATTLE_SCENE_KICK_DOWN, 0)
    
    --还原名字颜色
    SetMPVP2v2BattleDisable(sceneId, selfId, 1, 0)

	--清除所有在战场中获得的 buf
	CallScriptFunction(x303101_g_GrowPointScriptId, "RecyclePlayerAllBuf", sceneId, selfId)	
	
	local tblBuffer = {}
	local nPlayerLevel = GetLevel(sceneId, selfId)

	if nPlayerLevel >= 40 and nPlayerLevel <= 49 then
		tblBuffer = x303101_g_RandBuf_40
	elseif nPlayerLevel >= 50 and nPlayerLevel <= 59 then
		tblBuffer = x303101_g_RandBuf_50
	elseif nPlayerLevel >= 60 and nPlayerLevel <= 69 then
		tblBuffer = x303101_g_RandBuf_60
	elseif nPlayerLevel >= 70 and nPlayerLevel <= 79 then
		tblBuffer = x303101_g_RandBuf_70
	elseif nPlayerLevel >= 80 and nPlayerLevel <= 89 then
		tblBuffer = x303101_g_RandBuf_80
	elseif nPlayerLevel >= 90 and nPlayerLevel <= 99 then
		tblBuffer = x303101_g_RandBuf_90
	elseif nPlayerLevel >= 100 then
		tblBuffer = x303101_g_RandBuf_100
	end
	
	for i, item in tblBuffer do
        DispelSpecificImpact(sceneId, selfId, item, 1)
    end
	
    --如果存在BakScene信息，则以BakScene信息为准
    local nBakSceneId, x, z = GetPlayerBakSceneInfo(sceneId, selfId)
    if nBakSceneId >= 0 then
        NewWorld(sceneId ,selfId, nBakSceneId, x, z, x303101_g_scriptId)
        return
    end

    --如果没有 BakScene 信息，则传送到王城
    local nCountry = GetCurCountry(sceneId,selfId)
    if nCountry == 0 then
        NewWorld(sceneId, selfId, 50, 123, 57, x303101_g_scriptId)
    elseif nCountry == 1 then
        NewWorld(sceneId, selfId, 150, 123, 57, x303101_g_scriptId)
    elseif nCountry == 2 then
        NewWorld(sceneId, selfId, 250, 123, 57, x303101_g_scriptId)
    elseif nCountry == 3 then
        NewWorld(sceneId, selfId, 350, 123, 57, x303101_g_scriptId)
    end
end

---------------------------------------------------------------------------------------------------
--恢复阵营，踢人时使用
---------------------------------------------------------------------------------------------------
function x303101_RestorePlayerCamp(sceneId,selfId)
    SetCurCamp(sceneId, selfId, GetCurCountry(sceneId, selfId))
end

---------------------------------------------------------------------------------------------------
--时间同步
---------------------------------------------------------------------------------------------------
function x303101_SyncBattleTimeToAllPlayer(sceneId, nTime)
	
	--更新战场所有客户端时间显示
	local nHumanCount = GetScenePlayerCount(sceneId)
    for i = 0, nHumanCount - 1 do
        local objId = GetScenePlayerObjId(sceneId, i)
        if objId >= 0 then
            TimerCommand(sceneId, objId, 1, GUILDBATTLE_TIMERID, GUILDBATTLE_TIMERTYPE, x303101_g_scriptId, -1, -1)
            if nTime > 0 then
                TimerCommand(sceneId, objId, 2, GUILDBATTLE_TIMERID, GUILDBATTLE_TIMERTYPE, x303101_g_scriptId, nTime, nTime)
            end
        end
    end
end

----------------------------------------------------------------------------------------------
--时间同步回调
----------------------------------------------------------------------------------------------
function x303101_OnMSyncBattleTime(sceneId, nTime)
    
    --检查是否是PVP2v2竞技场
    if  x303101_GetBattleSceneType(sceneId) <= 0 then
        return
    end
    
    --检查场景是否有效
    if x303101_IsBattleSceneValid(sceneId) ~= 1 then
    	return	
    end
    
	--更新战场所有客户端时间显示
    x303101_SceneInfo[sceneId].TICKCOUNT = NumberCastIntToUInt(nTime)
    local DownTickCount = x303101_g_LimitTotalHoldTime - NumberCastIntToUInt(nTime)
    x303101_SyncBattleTimeToAllPlayer(sceneId, DownTickCount)
end

---------------------------------------------------------------------------------------------------
--检查战场结束
---------------------------------------------------------------------------------------------------
function x303101_CheckBattleFinished(sceneId)

	--1、只有一方玩家或是双方都不在了
	if  x303101_CheckTeamA_AllLeave(sceneId) == 1 or x303101_CheckTeamB_AllLeave(sceneId) == 1 then
		return 1
	end
	
	--2、某方玩家都死过
	if x303101_CheckTeamA_AllDie(sceneId) == 1 or x303101_CheckTeamB_AllDie(sceneId) == 1 then
		return 1
	end
	
	--3、只有一方玩家一个死亡，一个离开，则可以输
	if x303101_CheckTeamA_Live(sceneId) == 0 or x303101_CheckTeamB_Live(sceneId) == 0 then
		return 1
	end
		
	return 0
end

---------------------------------------------------------------------------------------------------
--给战场奖励
---------------------------------------------------------------------------------------------------
function x303101_GiveBattleBonus(sceneId, nResult)
	
	if nResult == -1 then
		LuaThisScenceM2Wrold(sceneId, "平局", 5, 1)
		x303101_OnGiveTeamA(sceneId, -1)
		x303101_OnGiveTeamB(sceneId, -1)
	elseif nResult == 0 then
		 LuaThisScenceM2Wrold(sceneId, "蓝方获胜", 5, 1)		
		x303101_OnGiveTeamA(sceneId, 0)
		x303101_OnGiveTeamB(sceneId, 0)
	elseif nResult == 1 then
		 LuaThisScenceM2Wrold(sceneId, "红方获胜", 5, 1)
		x303101_OnGiveTeamA(sceneId, 1)
		x303101_OnGiveTeamB(sceneId, 1)
	end
end

---------------------------------------------------------------------------------------------------
--队伍A的奖励
---------------------------------------------------------------------------------------------------
function x303101_OnGiveTeamA(sceneId, nBonusType)
		
	local humanCount = GetScenePlayerCount(sceneId)
	for	i = 0, humanCount - 1 do
		
		local humanId = GetScenePlayerObjId(sceneId, i)
		if IsPlayerStateNormal(sceneId, humanId) == 1 then
			
			local GUID = GetPlayerGUID(sceneId, humanId)

			local p = NumberCastIntToUInt(x303101_TeamInfoA[sceneId][1].GUID)
			if GUID == p then
				
				local name = GetName(sceneId, humanId)
				if name == nil then
					name = "Error "
				end
				
				if nBonusType == -1 then
					
					LuaScenceM2Player(sceneId, humanId, format("#G获得#R%d#G点战场积分", x303101_g_Other_Bonus_Mark), name, 2, 1)
					x303101_AddPVP2V2Level(sceneId, humanId, 0)
					AddPVP2V2Mark(sceneId, humanId, x303101_g_Other_Bonus_Mark)
					x303101_AddItem(sceneId, humanId, x303101_g_Award_ItemID, 0)
					CallScriptFunction(SCENE_SCRIPT_ID, "AddBattleHonour", sceneId, humanId, x303101_g_BattleHonour_NormalVal)
					
				elseif nBonusType == 0 then			
					
					if x303101_LevelFlag[sceneId] == 1 then
						LuaScenceM2Player(sceneId, humanId, "#G战场等级相差悬殊（20级以上），无法获得战场等级！", name, 2, 1)
					else
						LuaScenceM2Player(sceneId, humanId, format("#G战场等级+%d", x303101_g_Winner_Bonus_Level), name, 2, 1)
						x303101_AddPVP2V2Level(sceneId, humanId, x303101_g_Winner_Bonus_Level)
					end

					LuaScenceM2Player( sceneId,humanId,format("#G获得#R%d#G点战场积分",x303101_g_Winner_Bonus_Mark),name,2,1)
					AddPVP2V2Mark(sceneId,humanId,x303101_g_Winner_Bonus_Mark)	
					x303101_AddItem(sceneId, humanId, x303101_g_Award_ItemID, 1)
					CallScriptFunction(SCENE_SCRIPT_ID, "AddBattleHonour", sceneId, humanId, x303101_g_BattleHonour_WinVal)
															
				elseif nBonusType == 1 then
					
					LuaScenceM2Player(sceneId, humanId, format("#G战场等级-%d", x303101_g_Loser_Bonus_Level), name, 2, 1)
					LuaScenceM2Player(sceneId, humanId, format("#G获得#R%d#G点战场积分", x303101_g_Loser_Bonus_Mark) ,name, 2, 1)	
					x303101_SubPVP2V2Level(sceneId, humanId, x303101_g_Loser_Bonus_Level)
					AddPVP2V2Mark(sceneId, humanId, x303101_g_Loser_Bonus_Mark)
					x303101_AddItem(sceneId, humanId, x303101_g_Award_ItemID, 2)
					CallScriptFunction(SCENE_SCRIPT_ID, "AddBattleHonour", sceneId, humanId, x303101_g_BattleHonour_LoseVal)
				end
				
			end
			
			p = NumberCastIntToUInt(x303101_TeamInfoA[sceneId][2].GUID)
			if GUID == p then
				
				local name = GetName(sceneId, humanId)
				if name == nil then
					name = "Error "
				end
				
				if nBonusType == -1 then
					
					LuaScenceM2Player(sceneId, humanId, format("#G获得#R%d#G点战场积分", x303101_g_Other_Bonus_Mark), name, 2, 1)
					x303101_AddPVP2V2Level(sceneId, humanId, 0)
					AddPVP2V2Mark(sceneId, humanId, x303101_g_Other_Bonus_Mark)
					x303101_AddItem(sceneId, humanId, x303101_g_Award_ItemID, 0)
					CallScriptFunction(SCENE_SCRIPT_ID, "AddBattleHonour", sceneId, humanId, x303101_g_BattleHonour_NormalVal)
					
				elseif nBonusType == 0 then
					
					if x303101_LevelFlag[sceneId] == 1 then
						LuaScenceM2Player(sceneId, humanId, "#G战场等级相差悬殊（20级以上），无法获得战场等级！", name, 2, 1)
					else
						LuaScenceM2Player(sceneId, humanId, format("#G战场等级+%d", x303101_g_Winner_Bonus_Level), name, 2, 1)	
						x303101_AddPVP2V2Level(sceneId, humanId, x303101_g_Winner_Bonus_Level)
					end
					
					LuaScenceM2Player(sceneId, humanId, format("#G获得#R%d#G点战场积分", x303101_g_Winner_Bonus_Mark), name, 2, 1)
					AddPVP2V2Mark(sceneId, humanId, x303101_g_Winner_Bonus_Mark)				
					x303101_AddItem(sceneId, humanId, x303101_g_Award_ItemID, 1)
					CallScriptFunction(SCENE_SCRIPT_ID, "AddBattleHonour", sceneId, humanId, x303101_g_BattleHonour_WinVal)
					
				elseif nBonusType == 1 then
					
					LuaScenceM2Player(sceneId, humanId, format("#G战场等级-%d", x303101_g_Loser_Bonus_Level), name, 2, 1)
					LuaScenceM2Player(sceneId, humanId, format("#G获得#R%d#G点战场积分", x303101_g_Loser_Bonus_Mark), name, 2, 1)	
					
					x303101_SubPVP2V2Level(sceneId, humanId, x303101_g_Loser_Bonus_Level)
					AddPVP2V2Mark(sceneId, humanId, x303101_g_Loser_Bonus_Mark)
					x303101_AddItem(sceneId, humanId, x303101_g_Award_ItemID, 2)
					CallScriptFunction(SCENE_SCRIPT_ID, "AddBattleHonour", sceneId, humanId, x303101_g_BattleHonour_LoseVal)
				end
			end
		end
	end
end

---------------------------------------------------------------------------------------------------
--队伍B的奖励
---------------------------------------------------------------------------------------------------
function x303101_OnGiveTeamB( sceneId, nBonusType )

	local humanCount = GetScenePlayerCount(sceneId)
	for	i = 0, humanCount - 1 do
		local humanId = GetScenePlayerObjId(sceneId, i)
		if IsPlayerStateNormal( sceneId,humanId ) == 1 then
			
			local GUID = GetPlayerGUID(sceneId, humanId)

			local p = NumberCastIntToUInt(x303101_TeamInfoB[sceneId][1].GUID)
			if GUID == p then
				
				local name = GetName(sceneId, humanId)
				if name == nil then
					name = "Error "
				end
				
				if nBonusType == -1 then
					
					LuaScenceM2Player(sceneId, humanId, format("#G获得#R%d#G点战场积分", x303101_g_Other_Bonus_Mark), name, 2, 1)
					x303101_AddPVP2V2Level(sceneId, humanId, 0)
					AddPVP2V2Mark(sceneId, humanId, x303101_g_Other_Bonus_Mark)
					x303101_AddItem(sceneId, humanId, x303101_g_Award_ItemID, 0)
					CallScriptFunction(SCENE_SCRIPT_ID, "AddBattleHonour", sceneId, humanId, x303101_g_BattleHonour_NormalVal)
					
				elseif nBonusType == 0 then
					
					LuaScenceM2Player(sceneId, humanId, format("#G战场等级-%d", x303101_g_Loser_Bonus_Level), name, 2, 1)
					LuaScenceM2Player(sceneId, humanId, format("#G获得#R%d#G点战场积分", x303101_g_Loser_Bonus_Mark), name, 2, 1)
					x303101_SubPVP2V2Level(sceneId, humanId, x303101_g_Loser_Bonus_Level)
					AddPVP2V2Mark(sceneId, humanId, x303101_g_Loser_Bonus_Mark)
					x303101_AddItem(sceneId, humanId, x303101_g_Award_ItemID, 2)
					CallScriptFunction(SCENE_SCRIPT_ID, "AddBattleHonour", sceneId, humanId, x303101_g_BattleHonour_LoseVal)
					
				elseif nBonusType == 1 then					

					if x303101_LevelFlag[sceneId] == 2 then
						LuaScenceM2Player(sceneId, humanId,"#G战场等级相差悬殊（20级以上），无法获得战场等级！", name, 2, 1)
					else
						LuaScenceM2Player(sceneId, humanId,format("#G战场等级+%d", x303101_g_Winner_Bonus_Level), name, 2, 1)
						x303101_AddPVP2V2Level(sceneId, humanId, x303101_g_Winner_Bonus_Level)
					end
					
					LuaScenceM2Player(sceneId, humanId, format("#G获得#R%d#G点战场积分", x303101_g_Winner_Bonus_Mark), name, 2, 1)
					AddPVP2V2Mark(sceneId, humanId, x303101_g_Winner_Bonus_Mark)	
					x303101_AddItem(sceneId, humanId, x303101_g_Award_ItemID, 1)
					CallScriptFunction(SCENE_SCRIPT_ID, "AddBattleHonour", sceneId, humanId, x303101_g_BattleHonour_WinVal)
				end
				
			end
			
			p = NumberCastIntToUInt(x303101_TeamInfoB[sceneId][2].GUID)
			if GUID == p then
				
				local name = GetName(sceneId, humanId)
				if name == nil then
					name = "Error "
				end
				
				if nBonusType == -1 then
					
					LuaScenceM2Player(sceneId, humanId, format("#G获得#R%d#G点战场积分",x303101_g_Other_Bonus_Mark), name, 2, 1)		
					x303101_AddPVP2V2Level(sceneId, humanId, 0)
					AddPVP2V2Mark(sceneId, humanId, x303101_g_Other_Bonus_Mark)	
					x303101_AddItem(sceneId, humanId, x303101_g_Award_ItemID, 0)
					CallScriptFunction(SCENE_SCRIPT_ID, "AddBattleHonour", sceneId, humanId, x303101_g_BattleHonour_NormalVal)
					
				elseif nBonusType == 0 then
					
					LuaScenceM2Player(sceneId, humanId, format("#G战场等级-%d", x303101_g_Loser_Bonus_Level), name, 2, 1)
					LuaScenceM2Player(sceneId, humanId, format("#G获得#R%d#G点战场积分", x303101_g_Loser_Bonus_Mark), name, 2, 1)
					x303101_SubPVP2V2Level(sceneId, humanId, x303101_g_Loser_Bonus_Level)
					AddPVP2V2Mark(sceneId, humanId, x303101_g_Loser_Bonus_Mark)
					x303101_AddItem(sceneId, humanId, x303101_g_Award_ItemID, 2)
					CallScriptFunction(SCENE_SCRIPT_ID, "AddBattleHonour", sceneId, humanId, x303101_g_BattleHonour_LoseVal)
					
				elseif nBonusType == 1 then
					
					if x303101_LevelFlag[sceneId] == 2 then
						LuaScenceM2Player(sceneId, humanId, "#G战场等级相差悬殊（20级以上），无法获得战场等级！", name, 2, 1)
					else
						LuaScenceM2Player(sceneId, humanId, format("#G战场等级+%d", x303101_g_Winner_Bonus_Level), name, 2, 1)
						x303101_AddPVP2V2Level(sceneId, humanId,x303101_g_Winner_Bonus_Level)
					end
					
					LuaScenceM2Player(sceneId, humanId, format("#G获得#R%d#G点战场积分", x303101_g_Winner_Bonus_Mark), name, 2, 1)	
					AddPVP2V2Mark(sceneId, humanId, x303101_g_Winner_Bonus_Mark)	
					x303101_AddItem(sceneId, humanId, x303101_g_Award_ItemID, 1)
					CallScriptFunction(SCENE_SCRIPT_ID, "AddBattleHonour", sceneId, humanId, x303101_g_BattleHonour_WinVal)
				end
			end
		end
	end
end

---------------------------------------------------------------------------------------------------
--给战场奖励
---------------------------------------------------------------------------------------------------
function x303101_GenBattleResult(sceneId)

	--如果已经开始关闭，则不允许给奖励
	if x303101_SceneInfo[sceneId].ISCLOSING == 1 then
		return
	end
	
	local nResult = -1 

	---------------------------------------------------------------------------------------------------	
	--1、只有一方玩家
	---------------------------------------------------------------------------------------------------
	
	--当A组玩家在，B组玩家不在，认为A组赢	
	if  x303101_CheckTeamA_AllLeave(sceneId) == 0 and x303101_CheckTeamB_AllLeave(sceneId) == 1 then
		nResult = 0
		x303101_GiveBattleBonus(sceneId, nResult)
		return
	end
	
	--当A组玩家不在，B组玩家在，认为B组赢
	if  x303101_CheckTeamA_AllLeave(sceneId) == 1 and x303101_CheckTeamB_AllLeave(sceneId) == 0 then
		nResult = 1
		x303101_GiveBattleBonus(sceneId, nResult)
		return
	end
	
	---------------------------------------------------------------------------------------------------
	--2、某方玩家都死过
	---------------------------------------------------------------------------------------------------
	
	--当A组玩家没有全死过，B组玩家全死过，认为A组赢
	if x303101_CheckTeamA_AllDie(sceneId) == 0 and x303101_CheckTeamB_AllDie(sceneId) == 1 then
		nResult = 0
		x303101_GiveBattleBonus(sceneId, nResult)
		return
	end
	
	--当A组玩家全死过，B组玩家没有全死过，认为B组赢
	if x303101_CheckTeamA_AllDie(sceneId) == 1 and x303101_CheckTeamB_AllDie(sceneId) == 0 then
		nResult = 1
		x303101_GiveBattleBonus(sceneId, nResult)
		return
	end
	
	---------------------------------------------------------------------------------------------------
	--3.检查某方玩家活着的情况
	---------------------------------------------------------------------------------------------------
	if x303101_CheckTeamA_Live(sceneId) == 1 and x303101_CheckTeamB_Live(sceneId) == 0 then
		nResult = 0
		x303101_GiveBattleBonus(sceneId, nResult)
		return
	end
	
	if x303101_CheckTeamA_Live(sceneId) == 0 and x303101_CheckTeamB_Live(sceneId) == 1 then
		nResult = 1
		x303101_GiveBattleBonus(sceneId, nResult)
		return
	end
	
	---------------------------------------------------------------------------------------------------
	--4、检查活着的玩家的数量
	---------------------------------------------------------------------------------------------------
	if x303101_GetTeamA_LiveCount(sceneId) > x303101_GetTeamB_LiveCount(sceneId)  then
		nResult = 0
		x303101_GiveBattleBonus(sceneId, nResult)
		return
	end
	
	if x303101_GetTeamA_LiveCount(sceneId) < x303101_GetTeamB_LiveCount(sceneId)  then
		nResult = 1
		x303101_GiveBattleBonus(sceneId, nResult)
		return
	end	
	
	---------------------------------------------------------------------------------------------------
	--5、不满足1和2,3,4
	---------------------------------------------------------------------------------------------------
	
	--其他情况，认为战平，如果没人，不处理
	if  x303101_CheckTeamA_AllLeave(sceneId) == 0 and x303101_CheckTeamB_AllLeave(sceneId) == 0 then
		nResult = -1
		x303101_GiveBattleBonus(sceneId, nResult)
		return
	end
		
end


---------------------------------------------------------------------------------------------------
--检查队伍A是否全部离开
---------------------------------------------------------------------------------------------------
function x303101_CheckTeamA_AllLeave(sceneId)

	local humanCount = GetScenePlayerCount(sceneId)
	for	i = 0, humanCount - 1 do
		local humanId = GetScenePlayerObjId(sceneId, i)
		if IsPlayerStateNormal(sceneId, humanId) == 1 then
			
			local GUID = GetPlayerGUID(sceneId, humanId)
			
			--1
			local p = NumberCastIntToUInt(x303101_TeamInfoA[sceneId][1].GUID)
			if GUID == p then
				return 0
			end
			
			--2
			p = NumberCastIntToUInt(x303101_TeamInfoA[sceneId][2].GUID)
			if GUID == p then
				return 0
			end
		end
	end
	
	return 1
end

---------------------------------------------------------------------------------------------------
--检查队伍A是否全部离开
---------------------------------------------------------------------------------------------------
function x303101_CheckTeamB_AllLeave( sceneId )
	
	local humanCount = GetScenePlayerCount(sceneId)
	for	i = 0, humanCount - 1 do
		local humanId = GetScenePlayerObjId(sceneId, i)
		if IsPlayerStateNormal( sceneId,humanId ) == 1 then
			
			local GUID = GetPlayerGUID(sceneId, humanId)

			--3
			local p = NumberCastIntToUInt(x303101_TeamInfoB[sceneId][1].GUID)
			if GUID == p then
				return 0
			end
			
			--4
			p = NumberCastIntToUInt(x303101_TeamInfoB[sceneId][2].GUID)
			if GUID == p then
				return 0
			end
		end
	end
	
	return 1
	
end


---------------------------------------------------------------------------------------------------
--检查队伍A是否全军覆没
---------------------------------------------------------------------------------------------------
function x303101_CheckTeamA_AllDie(sceneId)
	
	--进行计数
	
	local nCount = 0
	if x303101_TeamInfoA[sceneId][1].DIE == 1 then
		nCount = nCount + 1
	end
	
	if x303101_TeamInfoA[sceneId][2].DIE == 1 then
		nCount = nCount + 1
	end
	
	--当计数为2表示A组玩家都死过
	if nCount == 2 then
		return 1
	end
	
	return 0
end

---------------------------------------------------------------------------------------------------
--检查A队活着的玩家
---------------------------------------------------------------------------------------------------
function x303101_CheckTeamA_Live(sceneId)
	
	--如果只有一方玩家，则判断死亡或是其他
	local nLiveCount = 0
	local humanCount = GetScenePlayerCount(sceneId)
	
	for	i = 0, humanCount - 1 do
		local humanId = GetScenePlayerObjId(sceneId, i)
		if IsPlayerStateNormal(sceneId, humanId) == 1 then
			
			local GUID = GetPlayerGUID(sceneId, humanId)

			--1
			local p = NumberCastIntToUInt(x303101_TeamInfoA[sceneId][1].GUID)
			if GUID == p then
				if x303101_TeamInfoA[sceneId][1].DIE ~= 1 then
					nLiveCount = nLiveCount + 1
				end
			end

			--2
			p = NumberCastIntToUInt(x303101_TeamInfoA[sceneId][2].GUID)
			if GUID == p then
				if x303101_TeamInfoA[sceneId][2].DIE ~= 1 then
					nLiveCount = nLiveCount + 1
				end
			end
		end
	end

	if nLiveCount == 0 then
		return 0				
	end

	return 1
end

---------------------------------------------------------------------------------------------------
--检查B队活着的玩家
---------------------------------------------------------------------------------------------------
function x303101_CheckTeamB_Live(sceneId)
	
	--如果只有一方玩家，则判断死亡或是其他
	local nLiveCount = 0
	local humanCount = GetScenePlayerCount(sceneId);
	
	for	i = 0, humanCount - 1 do
		local humanId = GetScenePlayerObjId(sceneId, i)
		if IsPlayerStateNormal(sceneId, humanId) == 1 then
			
			local GUID = GetPlayerGUID(sceneId, humanId)
			
			--1
			local p = NumberCastIntToUInt(x303101_TeamInfoB[sceneId][1].GUID)
			if GUID == p then
				if x303101_TeamInfoB[sceneId][1].DIE ~= 1 then
					nLiveCount = nLiveCount + 1
				end
			end
			
			--2
			p = NumberCastIntToUInt(x303101_TeamInfoB[sceneId][2].GUID)
			if GUID == p then
				if x303101_TeamInfoB[sceneId][2].DIE ~= 1 then
					nLiveCount = nLiveCount + 1
				end
			end
		end
	end
	
	if nLiveCount == 0 then
		return 0				
	end
	
	return 1
end

---------------------------------------------------------------------------------------------------
--取得A队活着的玩家的数量
---------------------------------------------------------------------------------------------------
function x303101_GetTeamA_LiveCount(sceneId)
	
	--如果只有一方玩家，则判断死亡或是其他
	local nLiveCount = 0
	local humanCount = GetScenePlayerCount(sceneId)
	
	for	i = 0, humanCount - 1 do
		local humanId = GetScenePlayerObjId(sceneId, i)
		if IsPlayerStateNormal(sceneId, humanId) == 1 then
			
			local GUID = GetPlayerGUID(sceneId, humanId)
			
			--1
			local p = NumberCastIntToUInt(x303101_TeamInfoA[sceneId][1].GUID)
			if GUID == p then
				if x303101_TeamInfoA[sceneId][1].DIE ~= 1 then
					nLiveCount = nLiveCount + 1
				end
			end
			
			--2
			p = NumberCastIntToUInt(x303101_TeamInfoA[sceneId][2].GUID)
			if GUID == p then
				if x303101_TeamInfoA[sceneId][2].DIE ~= 1 then
					nLiveCount = nLiveCount + 1
				end
			end
		end
	end
	
	return nLiveCount
end

---------------------------------------------------------------------------------------------------
--取得B队活着的玩家的数量
---------------------------------------------------------------------------------------------------
function x303101_GetTeamB_LiveCount(sceneId)
	
	--如果只有一方玩家，则判断死亡或是其他
	local nLiveCount = 0
	local humanCount = GetScenePlayerCount(sceneId)
	
	for	i = 0, humanCount - 1 do
		local humanId = GetScenePlayerObjId(sceneId, i)
		if IsPlayerStateNormal(sceneId, humanId ) == 1 then
			
			local GUID = GetPlayerGUID( sceneId,humanId )
			
			--1
			local p = NumberCastIntToUInt(x303101_TeamInfoB[sceneId][1].GUID)
			if GUID == p then
				if x303101_TeamInfoB[sceneId][1].DIE ~= 1 then
					nLiveCount = nLiveCount + 1
				end
			end
			
			--2
			p = NumberCastIntToUInt(x303101_TeamInfoB[sceneId][2].GUID)
			if GUID == p then
				if x303101_TeamInfoB[sceneId][2].DIE ~= 1 then
					nLiveCount = nLiveCount + 1
				end
			end
		end
	end
	
	return nLiveCount
end



---------------------------------------------------------------------------------------------------
--检查队伍B是否全军覆没
---------------------------------------------------------------------------------------------------
function x303101_CheckTeamB_AllDie(sceneId)
	
	--进行计数
	
	local nCount = 0
	if x303101_TeamInfoB[sceneId][1].DIE == 1 then
		nCount = nCount + 1
	end
	
	if x303101_TeamInfoB[sceneId][2].DIE == 1 then
		nCount = nCount + 1
	end
	
	--当计数为2表示B组玩家都死过
	if nCount == 2 then
		return 1
	end
	
	return 0
end


---------------------------------------------------------------------------------------------------
--检查玩家有效性
---------------------------------------------------------------------------------------------------
function x303101_CheckPlayerValid(sceneId, selfId)
	
	local GUID = GetPlayerGUID(sceneId, selfId)

	local p = NumberCastIntToUInt(x303101_TeamInfoA[sceneId][1].GUID)
	if GUID == p then
		return 1
	end
	
	p = NumberCastIntToUInt(x303101_TeamInfoA[sceneId][2].GUID)
	if GUID == p then
		return 1
	end
	
	p = NumberCastIntToUInt(x303101_TeamInfoB[sceneId][1].GUID)
	if GUID == p then
		return 1
	end
	
	p = NumberCastIntToUInt(x303101_TeamInfoB[sceneId][2].GUID)
	if GUID == p then
		return 1
	end
	
	return 0
end

---------------------------------------------------------------------------------------------------
--取得玩家死亡标记
---------------------------------------------------------------------------------------------------
function x303101_GetPlayerDieFlag(sceneId, selfId)
	
	local GUID = GetPlayerGUID(sceneId, selfId)

	local p = NumberCastIntToUInt(x303101_TeamInfoA[sceneId][1].GUID)
	if GUID == p then
		return x303101_TeamInfoA[sceneId][1].DIE;
	end
	
	p = NumberCastIntToUInt(x303101_TeamInfoA[sceneId][2].GUID)
	if GUID == p then
		return x303101_TeamInfoA[sceneId][2].DIE;
	end
	
	p = NumberCastIntToUInt(x303101_TeamInfoB[sceneId][1].GUID)
	if GUID == p then
		return x303101_TeamInfoB[sceneId][1].DIE;
	end
	
	p = NumberCastIntToUInt(x303101_TeamInfoB[sceneId][2].GUID)
	if GUID == p then
		return x303101_TeamInfoB[sceneId][2].DIE;
	end
	
	return 1
end

---------------------------------------------------------------------------------------------------
--设置玩家死亡标记
---------------------------------------------------------------------------------------------------
function x303101_SetPlayerDieFlag(sceneId, selfId)

	local GUID = GetPlayerGUID(sceneId, selfId)

	local p = NumberCastIntToUInt(x303101_TeamInfoA[sceneId][1].GUID)
	if GUID == p then
		x303101_TeamInfoA[sceneId][1].DIE = 1
		return
	end
	
	p = NumberCastIntToUInt(x303101_TeamInfoA[sceneId][2].GUID)
	if GUID == p then
		x303101_TeamInfoA[sceneId][2].DIE = 1
		return
	end
	
	p = NumberCastIntToUInt(x303101_TeamInfoB[sceneId][1].GUID)
	if GUID == p then
		x303101_TeamInfoB[sceneId][1].DIE = 1
		return
	end
	
	p = NumberCastIntToUInt(x303101_TeamInfoB[sceneId][2].GUID)
	if GUID == p then
		x303101_TeamInfoB[sceneId][2].DIE = 1
		return
	end
end

---------------------------------------------------------------------------------------------------
--取得玩家进入战场标记
---------------------------------------------------------------------------------------------------
function x303101_GetPlayerEnterSceneFlag(sceneId, selfId)

	local GUID = GetPlayerGUID(sceneId, selfId)

	local p = NumberCastIntToUInt(x303101_TeamInfoA[sceneId][1].GUID)
	if GUID == p then
		return x303101_TeamInfoA[sceneId][1].ENTER
	end
	
	p = NumberCastIntToUInt(x303101_TeamInfoA[sceneId][2].GUID)
	if GUID == p then
		return x303101_TeamInfoA[sceneId][2].ENTER
	end
	
	p = NumberCastIntToUInt(x303101_TeamInfoB[sceneId][1].GUID)
	if GUID == p then
		return x303101_TeamInfoB[sceneId][1].ENTER
	end
	
	p = NumberCastIntToUInt(x303101_TeamInfoB[sceneId][2].GUID)
	if GUID == p then
		return x303101_TeamInfoB[sceneId][2].ENTER
	end
	
	return 1
end

---------------------------------------------------------------------------------------------------
--设置玩家进入战场标记
---------------------------------------------------------------------------------------------------
function x303101_SetPlayerEnterSceneFlag(sceneId, selfId)

	--设置玩家进入标记
	local GUID = GetPlayerGUID(sceneId, selfId)

	local p = NumberCastIntToUInt(x303101_TeamInfoA[sceneId][1].GUID)
	if GUID == p then
		x303101_TeamInfoA[sceneId][1].ENTER = 1
		return
	end
	
	p = NumberCastIntToUInt(x303101_TeamInfoA[sceneId][2].GUID)
	if GUID == p then
		x303101_TeamInfoA[sceneId][2].ENTER = 1
		return
	end
	
	p = NumberCastIntToUInt(x303101_TeamInfoB[sceneId][1].GUID)
	if GUID == p then
		x303101_TeamInfoB[sceneId][1].ENTER = 1
		return
	end
	
	p = NumberCastIntToUInt(x303101_TeamInfoB[sceneId][2].GUID)
	if GUID == p then
		x303101_TeamInfoB[sceneId][2].ENTER = 1
		return
	end
end

---------------------------------------------------------------------------------------------------
--取得玩家离开战场标记
---------------------------------------------------------------------------------------------------
function x303101_GetPlayerLeaveSceneFlag(sceneId, selfId)

	local GUID = GetPlayerGUID(sceneId, selfId)

	local p = NumberCastIntToUInt(x303101_TeamInfoA[sceneId][1].GUID)
	if GUID == p then
		return x303101_TeamInfoA[sceneId][1].LEAVE
	end
	
	p = NumberCastIntToUInt(x303101_TeamInfoA[sceneId][2].GUID)
	if GUID == p then
		return x303101_TeamInfoA[sceneId][2].LEAVE
	end
	
	p = NumberCastIntToUInt(x303101_TeamInfoB[sceneId][1].GUID)
	if GUID == p then
		return x303101_TeamInfoB[sceneId][1].LEAVE
	end
	
	p = NumberCastIntToUInt(x303101_TeamInfoB[sceneId][2].GUID)
	if GUID == p then
		return x303101_TeamInfoB[sceneId][2].LEAVE
	end
	
	return 1
end

---------------------------------------------------------------------------------------------------
--设置玩家进入战场标记
---------------------------------------------------------------------------------------------------
function x303101_SetPlayerLeaveSceneFlag(sceneId, selfId)

	--设置玩家进入标记
	local GUID = GetPlayerGUID(sceneId, selfId)

	local p = NumberCastIntToUInt(x303101_TeamInfoA[sceneId][1].GUID)
	if GUID == p then
		x303101_TeamInfoA[sceneId][1].LEAVE = 1
		return
	end
	
	p = NumberCastIntToUInt(x303101_TeamInfoA[sceneId][2].GUID)
	if GUID == p then
		x303101_TeamInfoA[sceneId][2].LEAVE = 1
		return
	end
	
	p = NumberCastIntToUInt(x303101_TeamInfoB[sceneId][1].GUID)
	if GUID == p then
		x303101_TeamInfoB[sceneId][1].LEAVE = 1
		return
	end
	
	p = NumberCastIntToUInt(x303101_TeamInfoB[sceneId][2].GUID)
	if GUID == p then
		x303101_TeamInfoB[sceneId][2].LEAVE = 1
		return
	end
end

---------------------------------------------------------------------------------------------------
--战场准备好了
---------------------------------------------------------------------------------------------------
function x303101_OnBattleSceneReady(sceneId, nTotalTime)
	
	--场景相关信息							  
	x303101_SceneInfo[sceneId] = {
						TICKCOUNT = 0,
						ISCLOSING = 0,
						LEAVECOUNTDOWN = 0,
						RESULT = 0,
						LIMITHOLDTIME = nTotalTime,
				  	  }
				  	  
	local msg = format("MP2BL:x303101_OnBattleSceneReady SceneId=%d", sceneId)
	WriteLog(1, msg)
	
	--设置动态阻挡
	x303101_SetTempImpassable(sceneId)
end

---------------------------------------------------------------------------------------------------
--战场关闭
---------------------------------------------------------------------------------------------------
function x303101_OnBattleSceneClose(sceneId, flag)
	
	x303101_GenBattleResult(sceneId)
	
	if x303101_SceneInfo[sceneId].ISCLOSING == 1 then
		return
	end
	
	--调用采集点初始化函数，回收所有采集点
	CallScriptFunction(x303101_g_GrowPointScriptId, "OnInit", sceneId)	
	
	--场景相关信息							  
	x303101_SceneInfo[sceneId].ISCLOSING = 1	
	x303101_SceneInfo[sceneId].TICKCOUNT = 0
	local msg = format("MP2BL:x303101_OnBattleSceneClose SceneId=%d flag=%d", sceneId, flag)
	WriteLog(1, msg)
end

---------------------------------------------------------------------------------------------------
--队伍无匹配回调
---------------------------------------------------------------------------------------------------
function x303101_OnMBattleMatchOOD(sceneId, selfId)
		
	--开启报名签证
	SetQuestData(sceneId, selfId, MD_MBATTLE_SIGNSTATE[1], MD_MBATTLE_SIGNSTATE[2], MD_MBATTLE_SIGNSTATE[3], 1)
	SetQuestData(sceneId, selfId, MD_MBATTLE_SIGNTIME[1], MD_MBATTLE_SIGNTIME[2], MD_MBATTLE_SIGNTIME[3], MBATTLE_SIGNUP_SIGNTIME)

	local name = GetName(sceneId, selfId)
	LuaScenceM2Player(sceneId, selfId, "双人战场：你所在的队伍本次轮空！", name, 2, 1)	
	LuaScenceM2Player(sceneId, selfId, "双人战场：你所在的队伍本次轮空！", name, 3, 1)
end

---------------------------------------------------------------------------------------------------
--设置玩家需要踢出去
---------------------------------------------------------------------------------------------------
function x303101_SetPlayerNeedKick(sceneId, selfId)
	
	local KickDown = GetPlayerRuntimeData(sceneId, selfId, RD_BATTLE_SCENE_KICK_DOWN) 
    if KickDown <= 0 or KickDown > x303101_g_Kick_Down then                
        SetPlayerRuntimeData(sceneId, selfId, RD_BATTLE_SCENE_KICK_DOWN, x303101_g_Kick_Down) 
    end
end

----------------------------------------------------------------------------------------------
--设置所有玩家需要踢掉
----------------------------------------------------------------------------------------------
function x303101_SetAllPlayerNeedKick(sceneId)
    
    local nHumanCount = GetScenePlayerCount(sceneId)
    for i = 0, nHumanCount - 1 do
        local objId = GetScenePlayerObjId(sceneId, i)
        if objId >= 0 then
            local KickDown = GetPlayerRuntimeData(sceneId, objId, RD_BATTLE_SCENE_KICK_DOWN) 
            if KickDown <= 0 or KickDown > x303101_g_Kick_Down then                
                SetPlayerRuntimeData(sceneId, objId, RD_BATTLE_SCENE_KICK_DOWN, x303101_g_Kick_Down) 
            end
        end
    end
end

----------------------------------------------------------------------------------------------
--更新玩家踢掉状态
----------------------------------------------------------------------------------------------
function x303101_UpdatePlayerKickState(sceneId)
    
    local nHumanCount = GetScenePlayerCount(sceneId)
    for i = 0, nHumanCount - 1 do
        local objId = GetScenePlayerObjId(sceneId, i)
        if objId >= 0 then
            local KickDown = GetPlayerRuntimeData(sceneId, objId, RD_BATTLE_SCENE_KICK_DOWN) 
            if KickDown > 0 then                
                KickDown = KickDown - 1 
                if KickDown == 0 then
                    --倒计时为零，踢掉
                    SetPlayerRuntimeData(sceneId, objId, RD_BATTLE_SCENE_KICK_DOWN, -1) 
                    x303101_KickPlayer(sceneId,objId )                    
                else
                    --否则，继续倒计时
                    SetPlayerRuntimeData(sceneId, objId, RD_BATTLE_SCENE_KICK_DOWN, KickDown) 
                end
            end
        end
    end
end

----------------------------------------------------------------------------------------------
--生成动态阻挡
----------------------------------------------------------------------------------------------
function x303101_SetTempImpassable(sceneId)
	
	local nIndex = x303101_GetBattleSceneType(sceneId)
	
	for i,itm in x303101_g_TempImpassable do
		if itm.Flag == nIndex then
			AddSceneTempImpassable(sceneId, itm.Left, itm.Top, itm.Right, itm.Bottom)
		end
	end
	
end

----------------------------------------------------------------------------------------------
--删除动态阻挡
----------------------------------------------------------------------------------------------
function x303101_ClearTempImpassable(sceneId)
	
	LuaThisScenceM2Wrold(sceneId, "战斗开始", 5, 1)
	
	local nIndex = x303101_GetBattleSceneType(sceneId)
	
	for i, itm in x303101_g_TempImpassable do
		if itm.Flag == nIndex then
			DelSceneTempImpassable(sceneId, itm.Left, itm.Top, itm.Right, itm.Bottom)
		end
	end
	
	--清除特效
	local nHumanCount = GetScenePlayerCount(sceneId)
    for i = 0, nHumanCount - 1 do
        local objId = GetScenePlayerObjId(sceneId, i)
        if objId >= 0 then
            CallScriptFunction(UTILITY_SCRIPT, "StopClientMapColor", sceneId, objId, 0)
        end
    end
end

function x303101_AddPVP2V2Level(mapId, playerId, delta)

	local day = GetQuestData(mapId, playerId, MD_PVP2V2_LEVEL_DAY[1], MD_PVP2V2_LEVEL_DAY[2], MD_PVP2V2_LEVEL_DAY[3])
	local curday = GetWeekFirstDay()
	if day ~= curday then
		local value = GetPVP2V2Level(mapId, playerId)
		SubPVP2V2Level(mapId, playerId, value)
		AddPVP2V2Level(mapId, playerId, 500)
		SetQuestData(mapId, playerId, MD_PVP2V2_LEVEL_DAY[1], MD_PVP2V2_LEVEL_DAY[2], MD_PVP2V2_LEVEL_DAY[3], curday)
	end	
	AddPVP2V2Level(mapId, playerId, delta)
end

function x303101_SubPVP2V2Level(mapId, playerId, delta)

	local day = GetQuestData(mapId, playerId, MD_PVP2V2_LEVEL_DAY[1], MD_PVP2V2_LEVEL_DAY[2], MD_PVP2V2_LEVEL_DAY[3])
	local curday = GetWeekFirstDay()
	if day ~= curday then
		local value = GetPVP2V2Level(mapId, playerId)
		SubPVP2V2Level(mapId, playerId, value)
		AddPVP2V2Level(mapId, playerId, 500)
		SetQuestData(mapId, playerId, MD_PVP2V2_LEVEL_DAY[1], MD_PVP2V2_LEVEL_DAY[2], MD_PVP2V2_LEVEL_DAY[3], curday)
	end	
	SubPVP2V2Level(mapId, playerId, delta)
end

---------------------------------------------------------------------------------------------------
--申请进入副本
---------------------------------------------------------------------------------------------------
function x303101_ProcAcceptCheck( sceneId, selfId, NPCId )
    return 0
end
----------------------------------------------------------------------------------------------
--点确定后
----------------------------------------------------------------------------------------------
function x303101_ProcAccept( sceneId, selfId )
end
----------------------------------------------------------------------------------------------
--默认对话
----------------------------------------------------------------------------------------------
function x303101_ProcEventEntry(sceneId, selfId, NPCId, nScriptId, nFlag)	
end
---------------------------------------------------------------------------------------------------
--进入区域
---------------------------------------------------------------------------------------------------
function x303101_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end
---------------------------------------------------------------------------------------------------
--离开区域
---------------------------------------------------------------------------------------------------
function x303101_ProcAreaLeaved( sceneId, selfId, ScriptId, MissionId )
end