x303001_g_scriptId 					=   303001

-------------------------------------------------------------
--队伍A的信息
-------------------------------------------------------------
x303001_TeamInfoA					= {}							  
x303001_TeamInfoB					= {}
									  
-------------------------------------------------------------
--等级差标记
-------------------------------------------------------------									  									  
x303001_LevelFlag					= {}

-------------------------------------------------------------
--场景相关信息
-------------------------------------------------------------									  
x303001_SceneInfo					= {}

-------------------------------------------------------------
--场景启用相关信息
-------------------------------------------------------------
x303001_g_SceneMapNavPath			= 	{	{"zhanchang_shuangrenzhanchang/zhanchang_shuangrenzhanchang.scn",	1,1},	--场景1
											{"zhanchang_shuangrenzhanchang/zhanchang_shuangrenzhanchang.scn",	2,0},	--场景2
											{"zhanchang_shuangrenzhanchang/zhanchang_shuangrenzhanchang.scn",	3,0},	--场景3
										}
										
x303001_g_TempImpassable			=	{
											{Left = 89,Top = 71,Right =  168,Bottom = 183,Flag=1},
										}

-------------------------------------------------------------
--战场进入位置信息
-------------------------------------------------------------
x303001_g_EnterScenePos				=	{
											{ {79, 124},{79, 131},{ 176, 124},{ 176, 132}	},		--进入场景的坐标，与上面的场景相对应
											{ {27,106},{23,107},{101,107},{104,107}	},
											{ {31,102},{27, 99},{ 93, 28},{ 98, 29} },
										}
										
x303001_g_CloseTick					= 	10													--关闭场景倒计时
x303001_g_LimitTotalHoldTime		=	4*60												--战场最大时间

x303001_g_Kick_Down					=	4													--踢人倒计时

x303001_g_GameId					=	1221												--玩法ID

-------------------------------------------------------------
--玩家基本阵营信息
-------------------------------------------------------------										
x303001_g_CampFlag					= { 5, 6 }												--基础阵营号


-------------------------------------------------------------
--奖励相关
-------------------------------------------------------------
x303001_g_Winner_Bonus_Level		= 1				--加
x303001_g_Winner_Bonus_Mark			= 30

x303001_g_Loser_Bonus_Level			= 1				--减
x303001_g_Loser_Bonus_Mark			= 7

x303001_g_Other_Bonus_Mark			= 7


-------------------------------------------------------------
--相关状态
-------------------------------------------------------------
x303001_g_State_Invalid				= -1
x303001_g_State_Signup				=  0
x303001_g_State_SignupFinished		=  1
x303001_g_State_Begin				=  2
x303001_g_State_End					=  3

x303001_g_CurrentState				= {}



function x303001_OnMapInit(sceneId)
	
	--队伍A的信息
	x303001_TeamInfoA[sceneId]			= {	
											{GUID=-1,DIE=0,ENTER=0,LEAVE=0 },
											{GUID=-1,DIE=0,ENTER=0,LEAVE=0 }
										  }
	
	--队伍B的信息
	x303001_TeamInfoB[sceneId]			= {	
											{GUID=-1,DIE=0,ENTER=0,LEAVE=0 },
											{GUID=-1,DIE=0,ENTER=0,LEAVE=0 }
										  }
										  
	--等级差标记
	x303001_LevelFlag[sceneId]			= 0
	
	--场景相关信息
	x303001_SceneInfo[sceneId]			= {
											TICKCOUNT = 0,
											ISCLOSING = 0,
											LEAVECOUNTDOWN = 0,
											RESULT = 0,
											LIMITHOLDTIME = 5*60,
										  }
										  
	x303001_g_CurrentState[sceneId]		= x303001_g_State_Invalid
	
	
	
end

----------------------------------------------------------------------------------------------
--取得2V2战场类型
----------------------------------------------------------------------------------------------
function x303001_GetBattleSceneType(sceneId)

    local name = GetBattleSceneName(sceneId)
    for i,item in x303001_g_SceneMapNavPath do
        if name == item[1] then
            return item[2]
        end
    end

    return -1
	
end

----------------------------------------------------------------------------------------------
--战场是否被启用
----------------------------------------------------------------------------------------------
function x303001_IsBattleSceneValid(sceneId)

    local name = GetBattleSceneName(sceneId)
    for i,item in x303001_g_SceneMapNavPath do
        if name == item[1] then
            return item[3]
        end
    end

    return 0
	
end

----------------------------------------------------------------------------------------------
--普通场景状态处理
----------------------------------------------------------------------------------------------
function x303001_OnBattleState_NormalScene(sceneId,state)

	--限定为大都和王城
	if sceneId ~= 0 and sceneId ~= 50 and sceneId ~= 150 and sceneId ~= 250 and sceneId ~= 350 then
		return
	end

	--相关状态处理
	if state == x303001_g_State_Signup then

        if x303001_g_CurrentState[sceneId] ~= x303001_g_State_Signup then
            local msg = format("P2BL:x303001_g_State_Signup,SceneId=%d ",sceneId  )
            WriteLog(1,msg)
        end
        
        x303001_g_CurrentState[sceneId] = x303001_g_State_Signup
        
    elseif state == x303001_g_State_SignupFinished then

        if x303001_g_CurrentState[sceneId] ~= x303001_g_State_SignupFinished then
            local msg = format("P2BL:x303001_g_State_SignupFinished,SceneId=%d ",sceneId )
            WriteLog(1,msg)
        end
        
        x303001_g_CurrentState[sceneId] = x303001_g_State_SignupFinished            
        
--    elseif state == x303001_g_State_Begin then
--
--        if x303001_g_CurrentState[sceneId] ~= x303001_g_State_Begin then
--            local msg = format("P2BL:x303001_g_State_Begin,SceneId=%d ",sceneId )
--            WriteLog(1,msg)
--        end
--        
--        x303001_g_CurrentState[sceneId] = x303001_g_State_Begin
--
--    elseif state == x303001_g_State_End then
--        x303001_g_CurrentState[sceneId] = x303001_g_State_End
--
--        --记录日志
--        local msg = format("P2BL:x303001_g_State_End, SceneId=%d",sceneId )
--        WriteLog(1,msg)

    end
    
end

----------------------------------------------------------------------------------------------
--战场场景状态处理
----------------------------------------------------------------------------------------------
function x303001_OnBattleState_BattleScene(sceneId,state)

	--检查是否是PVP2v2竞技场
    local nBattleScene = x303001_GetBattleSceneType( sceneId )
    if  nBattleScene <= 0 then
        return
    end
    
    --检查场景是否有效
    local nBattleSceneValid = x303001_IsBattleSceneValid(sceneId)
    if nBattleSceneValid ~= 1 then
    	return	
    end

    if state == x303001_g_State_Signup then
    	
    	--如果已经开始，特殊处理一下
    	if x303001_g_CurrentState[sceneId] == x303001_g_State_Begin then
    		return
    	end
    	
        if x303001_g_CurrentState[sceneId] ~= x303001_g_State_Signup then
            local msg = format("P2BL:x303001_g_State_Signup,SceneId=%d,2 ",sceneId  )
            WriteLog(1,msg)
        end
        
        x303001_g_CurrentState[sceneId] = x303001_g_State_Signup
        PVP2v2RegisterScene( sceneId )

--    elseif state == x303001_g_State_SignupFinished then
--
--        --检查状态是否已经置过
--        if x303001_g_CurrentState[sceneId] ~= x303001_g_State_SignupFinished then
--            local msg = format("P2BL:x303001_g_State_SignupFinished,SceneId=%d,2",sceneId )
--            WriteLog(1,msg)
--        end
--
--        --设置基本数据
--        x303001_g_CurrentState[sceneId] = x303001_g_State_SignupFinished

    elseif state == x303001_g_State_Begin then

        --检查状态是否已经置过
        if x303001_g_CurrentState[sceneId] ~= x303001_g_State_Begin then
            local msg = format("P2BL:x303001_g_State_Begin,SceneId=%d,2",sceneId )
            WriteLog(1,msg)
        end

        --设置基本数据            
        x303001_g_CurrentState[sceneId] = x303001_g_State_Begin
        x303001_OnBattleSceneReady( sceneId,x303001_g_LimitTotalHoldTime )

    elseif state == x303001_g_State_End then

        if x303001_g_CurrentState[sceneId] > x303001_g_State_Begin or x303001_g_CurrentState[sceneId] < x303001_g_State_Signup then
            
            --记录日志
            local msg = format("P2BL:x303001_g_State_End,Result:nState > x303001_g_State_Begin or nState < x303001_g_State_Signup  SceneId=%d,state=%d,2",sceneId, x303001_g_CurrentState[sceneId] )
            WriteLog(1,msg)

            --根据玩法的脚本的不同，进行相关初始化回调
            x303001_OnBattleSceneClose( sceneId,0 )

            --记录日志
            local msg = format("P2BL:x303001_g_State_End, SceneId=%d,2",sceneId )
            WriteLog(1,msg)
            return
        end

        --设置状态，活动结束
		x303001_g_CurrentState[sceneId] = x303001_g_State_End
        x303001_OnBattleSceneClose( sceneId,1 )

        --记录日志
        local msg = format("P2BL:x303001_g_State_End, SceneId=%d,2",sceneId )
        WriteLog(1,msg)
    end
end

----------------------------------------------------------------------------------------------
--战场状态
----------------------------------------------------------------------------------------------
function x303001_OnBattleState(sceneId,state)

	local sceneType = GetSceneType(sceneId);
	if sceneType == 0 then
		x303001_OnBattleState_NormalScene(sceneId,state)
	elseif sceneType == 2 then
		x303001_OnBattleState_BattleScene(sceneId,state)
	end
end


----------------------------------------------------------------------------------------------
--战场是否正在报名
----------------------------------------------------------------------------------------------
function x303001_IsBattleSignup( sceneId )

	if sceneId == 0  or sceneId == 50 or sceneId == 150 or sceneId == 250 or sceneId == 350 then
		if x303001_g_CurrentState[sceneId] == x303001_g_State_Signup then
			return 1
		end
	end
	
	return 0
	
end

----------------------------------------------------------------------------------------------
--创建战场副本
----------------------------------------------------------------------------------------------
function x303001_OnBattleMatchInfo( sceneId, leaderguid1,otherguid1,leaderguid2,otherguid2,nLevelFlag )
	
	--队伍A的信息
	x303001_TeamInfoA[sceneId]			= {	
											{GUID=leaderguid1,DIE=0,ENTER=0,LEAVE=0 },
											{GUID=otherguid1, DIE=0,ENTER=0,LEAVE=0 },
										  }

	--队伍B的信息								  
	x303001_TeamInfoB[sceneId]			= {	
											{GUID=leaderguid2,DIE=0,ENTER=0,LEAVE=0 },
											{GUID=otherguid2, DIE=0,ENTER=0,LEAVE=0 },
										  }
										  
	--等级差标记
	x303001_LevelFlag[sceneId]			= nLevelFlag
end

---------------------------------------------------------------------------------------------------
--取得玩家阵营
---------------------------------------------------------------------------------------------------
function x303001_GetPlayerCampFlag( sceneId,selfId)
	
	local GUID = GetPlayerGUID(sceneId,selfId)
	
	local p = NumberCastIntToUInt(x303001_TeamInfoA[sceneId][1].GUID)
	if GUID == p then
		return 0
	end
	
	p = NumberCastIntToUInt(x303001_TeamInfoA[sceneId][2].GUID)
	if GUID == p then
		return 0
	end
	
	p = NumberCastIntToUInt(x303001_TeamInfoB[sceneId][1].GUID)
	if GUID == p then
		return 1
	end
	
	p = NumberCastIntToUInt(x303001_TeamInfoB[sceneId][2].GUID)
	if GUID == p then
		return 1
	end
	
	return -1
	
end

---------------------------------------------------------------------------------------------------
--设置玩家位置
---------------------------------------------------------------------------------------------------
function x303001_GetPlayerPos( sceneId,selfId )
	
	local GUID = GetPlayerGUID(sceneId,selfId)
	local nIndex = x303001_GetBattleSceneType(sceneId)
	
	--如果无效
	if nIndex < 1 or nIndex > getn(x303001_g_EnterScenePos) then
		return 100,100
	end
	
	local p = NumberCastIntToUInt(x303001_TeamInfoA[sceneId][1].GUID)
	if GUID == p then
		local x = x303001_g_EnterScenePos[nIndex][1][1]
		local z = x303001_g_EnterScenePos[nIndex][1][2]
		return x,z
	end
	
	p = NumberCastIntToUInt(x303001_TeamInfoA[sceneId][2].GUID)
	if GUID == p then
		local x = x303001_g_EnterScenePos[nIndex][2][1]
		local z = x303001_g_EnterScenePos[nIndex][2][2]
		return x,z
	end
	
	p = NumberCastIntToUInt(x303001_TeamInfoB[sceneId][1].GUID)
	if GUID == p then
		local x = x303001_g_EnterScenePos[nIndex][3][1]
		local z = x303001_g_EnterScenePos[nIndex][3][2]
		return x,z
	end
	
	p = NumberCastIntToUInt(x303001_TeamInfoB[sceneId][2].GUID)
	if GUID == p then
		local x = x303001_g_EnterScenePos[nIndex][4][1]
		local z = x303001_g_EnterScenePos[nIndex][4][2]
		return x,z
	end
	
	return 100,100
end


----------------------------------------------------------------------------------------------
--请求进入场景
----------------------------------------------------------------------------------------------
function x303001_AskBattleSceneEnter( sceneId,selfId)

	--向GLServer请求进入战场
	PVP2v2AskBattleSceneEnter(sceneId,selfId)
	
end

---------------------------------------------------------------------------------------------------
--申请进入副本
---------------------------------------------------------------------------------------------------
function x303001_ProcAcceptCheck( sceneId, selfId, NPCId )
    return 0
end

----------------------------------------------------------------------------------------------
--点确定后
----------------------------------------------------------------------------------------------
function x303001_ProcAccept( sceneId, selfId )
end

----------------------------------------------------------------------------------------------
--默认对话
----------------------------------------------------------------------------------------------
function x303001_ProcEventEntry(sceneId, selfId, NPCId, nScriptId, nFlag)	
end

---------------------------------------------------------------------------------------------------
--玩家进入战场时的处理
---------------------------------------------------------------------------------------------------
function x303001_OnPlayerEnter(sceneId, selfId)

	--检查是否是PVP2v2竞技场
    local nBattleScene = x303001_GetBattleSceneType( sceneId )
    if  nBattleScene <= 0 then
        return
    end
    
    --检查场景是否有效
    local nBattleSceneValid = x303001_IsBattleSceneValid(sceneId)
    if nBattleSceneValid ~= 1 then
    	return	
    end
	
	--对玩家原先的场景进行备份
    local scenePre = GetPlayerRuntimeData(sceneId,selfId,RD_HUMAN_SCENE_PRE ) - 1
    if scenePre >= 0 then
        
        local CurX = GetPlayerRuntimeData(sceneId,selfId,RD_HUMAN_POSX_PRE)
        local CurZ = GetPlayerRuntimeData(sceneId,selfId,RD_HUMAN_POSZ_PRE)

        SetPlayerBakSceneInfo(sceneId,selfId,scenePre,CurX,CurZ)

        SetPlayerRuntimeData(sceneId,selfId,RD_HUMAN_SCENE_PRE,0)
        SetPlayerRuntimeData(sceneId,selfId,RD_HUMAN_POSX_PRE,0)
        SetPlayerRuntimeData(sceneId,selfId,RD_HUMAN_POSZ_PRE,0)

    end
    
	--如果开始关闭，则玩家进入也要踢出去
	local leaveFlag = x303001_SceneInfo[sceneId].ISCLOSING
	if leaveFlag > 0 then
		
		x303001_SetPlayerNeedKick(sceneId,selfId)
		
		local msg = format("P2BL:x303001_OnPlayerEnterFinished kick 0 SceneId=%d ",sceneId  )
		WriteLog(1,msg)
		
		return
	end
	
	--如果玩家无效
	if x303001_CheckPlayerValid(sceneId,selfId ) == 0 then
		
		x303001_SetPlayerNeedKick(sceneId,selfId)
		
		local msg = format("P2BL:x303001_OnPlayerEnterFinished kick 1 SceneId=%d ",sceneId  )
		WriteLog(1,msg)
		
		return
	end
	
	--如果玩家曾经死亡
	if x303001_GetPlayerDieFlag(sceneId,selfId ) == 1 then
		
		x303001_SetPlayerNeedKick(sceneId,selfId)
		
		local msg = format("P2BL:x303001_OnPlayerEnterFinished kick 2 SceneId=%d ",sceneId  )
		WriteLog(1,msg)
		
		return
	end
	
	--如果玩家已经进过场景了
	if x303001_GetPlayerEnterSceneFlag( sceneId,selfId ) == 1 then
		
		x303001_SetPlayerNeedKick(sceneId,selfId)
		
		local msg = format("P2BL:x303001_OnPlayerEnterFinished kick 3 SceneId=%d ",sceneId  )
		WriteLog(1,msg)
		
		return
	end
	
	--设置玩家阵营
	local nCampFlag = x303001_GetPlayerCampFlag( sceneId,selfId)
	if nCampFlag < 0 or nCampFlag > 1 then
		
		x303001_SetPlayerNeedKick(sceneId,selfId)
		
		local msg = format("P2BL:x303001_OnPlayerEnterFinished kick 4 SceneId=%d ",sceneId  )
		WriteLog(1,msg)
		
		return
	end
	
	SetCurCamp(sceneId,selfId,x303001_g_CampFlag[nCampFlag+1])

	--设置玩家位置
	local x,z = x303001_GetPlayerPos( sceneId,selfId)
	SetPos(sceneId,selfId,x,z)
	
	--记录一下坐标
	local name = GetName(sceneId,selfId)
	local msg = format("P2BL:x303001_OnPlayerEnterFinished playerEnter SceneId=%d x = %d, z = %d flag = %d name=%s",sceneId,x,z,nCampFlag ,name )
	WriteLog(1,msg)
	
	--设置玩家进入场景标记
	x303001_SetPlayerEnterSceneFlag( sceneId,selfId)
	
	--设置客户端相关信息
	SetPVP2v2BattleDisable( sceneId,selfId,0,nCampFlag)
	
	--检查是否可以播放特效
	if x303001_SceneInfo[sceneId].TICKCOUNT < 31 then
		CallScriptFunction(UTILITY_SCRIPT,"PlayClientMapColor", sceneId, selfId, 0, 0)
	end
	
	--记录玩法日志
	GamePlayScriptLog(sceneId,selfId,x303001_g_GameId)
	
end

---------------------------------------------------------------------------------------------------
--玩家离开场景
---------------------------------------------------------------------------------------------------
function x303001_OnPlayerLeave( sceneId,selfId)

	local nDebug = 1
	if nDebug == 1 then
		
		local n2v2LevelPre = GetPVP2V2Level(sceneId,selfId)
		local name = GetName(sceneId,selfId)
		local msg = format("P2BL:x303001_OnPlayerLeave 0 SceneId=%d Name=%s 2v2LevelPre = %d", sceneId, name, n2v2LevelPre  )
        WriteLog(1,msg)
	end

	--检查是否是PVP2v2竞技场
    local nBattleScene = x303001_GetBattleSceneType( sceneId )
    if  nBattleScene <= 0 then
        return
    end
    
    --检查场景是否有效
    local nBattleSceneValid = x303001_IsBattleSceneValid(sceneId)
    if nBattleSceneValid ~= 1 then
    	return	
    end
	
	--如果开始关闭，则玩家离开不处理
	local leaveFlag = x303001_SceneInfo[sceneId].ISCLOSING
	if leaveFlag > 0 then
		return
	end
	
	--如果没有开始关闭
	if x303001_GetPlayerLeaveSceneFlag( sceneId,selfId) == 0 then
		
		x303001_SetPlayerLeaveSceneFlag( sceneId,selfId)
		
		local n2v2LevelPre = GetPVP2V2Level(sceneId,selfId)
		
		--中途退出或是非战场判定胜负的情况下，退出，等级减一惩罚
		x303001_SubPVP2V2Level(sceneId,selfId,x303001_g_Loser_Bonus_Level)
		
		local n2v2LevelAfter = GetPVP2V2Level(sceneId,selfId)
		
		--记录相关日志
		local name = GetName(sceneId,selfId)
		local msg = format("P2BL:x303001_OnPlayerLeave 1 SceneId=%d Name=%s 2v2LevelPre = %d 2v2LevelAfter=%d", sceneId, name, n2v2LevelPre, n2v2LevelAfter  )
        WriteLog(1,msg)
	end	
end

---------------------------------------------------------------------------------------------------
--战场定时器
---------------------------------------------------------------------------------------------------
function x303001_ProcTiming(sceneId, nowTime)

	--检查是否是PVP2v2竞技场
    local nBattleScene = x303001_GetBattleSceneType( sceneId )
    if  nBattleScene <= 0 then
        return
    end
    
    --检查场景是否有效
    local nBattleSceneValid = x303001_IsBattleSceneValid(sceneId)
    if nBattleSceneValid ~= 1 then
    	return	
    end

	x303001_UpdatePlayerKickState(sceneId)

	local leaveFlag = x303001_SceneInfo[sceneId].ISCLOSING
	if leaveFlag > 0 then

		--提示xx秒后将退出副本
		local leaveCountDown = x303001_SceneInfo[sceneId].LEAVECOUNTDOWN + 1
		x303001_SceneInfo[sceneId].LEAVECOUNTDOWN = leaveCountDown

		if leaveCountDown >= x303001_g_CloseTick then
			
			local humancount = GetScenePlayerCount(sceneId);
			for	i = 0, humancount - 1 do
				local humanId = GetScenePlayerObjId(sceneId, i);
                --x303001_DoPlayerRelive( sceneId,humanId,100)
                TimerCommand( sceneId, humanId, 1, GUILDBATTLE_TIMERID, GUILDBATTLE_TIMERTYPE, x303001_g_scriptId, -1, -1 );	--发送定时器，做定时器同步

                --调用踢人函数
                x303001_SetPlayerNeedKick(sceneId,humanId)
                local msg = format("P2BL:x303001_ProcTiming kick 1 SceneId=%d ",sceneId  )
                WriteLog(1,msg)
			end
			
		elseif leaveCountDown < x303001_g_CloseTick then
			
			local humancount = GetScenePlayerCount(sceneId);
			for	i = 0, humancount - 1 do
				local humanId = GetScenePlayerObjId(sceneId, i);
 				local str = format("本场战斗将在%d秒后关闭", x303001_g_CloseTick - leaveCountDown);
  				BeginQuestEvent(sceneId);
  				AddQuestText(sceneId, str);
  				EndQuestEvent(sceneId);
  				DispatchQuestTips(sceneId, humanId);
			end
			
		end

	else
		
		if x303001_g_CurrentState[sceneId] ~= x303001_g_State_Begin then
			return
		end
		
		local nowTickCount = x303001_SceneInfo[sceneId].TICKCOUNT + 1;
		x303001_SceneInfo[sceneId].TICKCOUNT = nowTickCount
		
		--超过30秒，清除动态阻挡
		if nowTickCount == 31 then
			x303001_ClearTempImpassable(sceneId)
		end
		
		--当超过一分钟后，开始检胜利
		if nowTickCount >= 60 then
			if x303001_CheckBattleFinished( sceneId ) == 1 then
				x303001_OnBattleSceneClose( sceneId,2 )
				
				
				local msg = format("P2BL:x303001_ProcTiming sceneId=%d,nowTickCount=%d 000 ",sceneId ,nowTickCount )
                WriteLog(1,msg)
                
			end
		end

		--副本计时器
		if nowTickCount >= x303001_g_LimitTotalHoldTime then
			local humancount = GetScenePlayerCount(sceneId);
			for i = 0, humancount - 1 do
				local humanId = GetScenePlayerObjId(sceneId, i);
				
				BeginQuestEvent(sceneId);
					AddQuestText(sceneId, format("本场战斗时间已到，将于%d秒后关闭！",x303001_g_CloseTick));
				EndQuestEvent();
				DispatchQuestTips(sceneId, humanId);
			end
		end

        if nowTickCount == x303001_g_LimitTotalHoldTime then
            x303001_OnBattleSceneClose( sceneId,3 )
            
            local msg = format("P2BL:x303001_ProcTiming sceneId=%d,nowTickCount=%d 001 ",sceneId ,nowTickCount )
            WriteLog(1,msg)
        end
	end
end

---------------------------------------------------------------------------------------------------
--玩家死亡
---------------------------------------------------------------------------------------------------
function x303001_OnPlayerDie(sceneId, selfId, killerId)	
	
	--检查是否是PVP2v2竞技场
    local nBattleScene = x303001_GetBattleSceneType( sceneId )
    if  nBattleScene <= 0 then
        return
    end
    
    --检查场景是否有效
    local nBattleSceneValid = x303001_IsBattleSceneValid(sceneId)
    if nBattleSceneValid ~= 1 then
    	return	
    end
    
	x303001_SetPlayerDieFlag( sceneId,selfId )
	if x303001_CheckBattleFinished( sceneId ) == 1 then
		x303001_OnBattleSceneClose( sceneId,4 )	
		
		local msg = format("P2BL:x303001_OnPlayerDie sceneId=%d  002 ",sceneId )
        WriteLog(1,msg)
	end
end

---------------------------------------------------------------------------------------------------
--玩家复活
---------------------------------------------------------------------------------------------------
function x303001_OnPlayerRelive(sceneId, selfId, ReliveType)
	
	--检查是否是PVP2v2竞技场
    local nBattleScene = x303001_GetBattleSceneType( sceneId )
    if  nBattleScene <= 0 then
        return
    end
    
    --检查场景是否有效
    local nBattleSceneValid = x303001_IsBattleSceneValid(sceneId)
    if nBattleSceneValid ~= 1 then
    	return	
    end
	
	local leaveFlag = x303001_SceneInfo[sceneId].ISCLOSING;
	if leaveFlag > 0 then
		return
	end
	
	BeginQuestEvent(sceneId);
		AddQuestText(sceneId, "双人战场比赛结束之前不能复活，请耐心等待！");
	EndQuestEvent();
	DispatchQuestTips(sceneId, selfId);
	
end

---------------------------------------------------------------------------------------------------
--进入区域
---------------------------------------------------------------------------------------------------
function x303001_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

---------------------------------------------------------------------------------------------------
--离开区域
---------------------------------------------------------------------------------------------------
function x303001_ProcAreaLeaved( sceneId, selfId, ScriptId, MissionId )
end

---------------------------------------------------------------------------------------------------
--场景关闭
---------------------------------------------------------------------------------------------------
function x303001_OnSceneClose( sceneId )
	--向GlServer通知，本场景已经关闭
	PVP2v2SendMakeBattleSceneClose(sceneId)
end

---------------------------------------------------------------------------------------------------
--复活
---------------------------------------------------------------------------------------------------
function x303001_DoPlayerRelive( sceneId, selfId, value )

	--只有死亡的玩家进行处理
	local nHp = GetHp(sceneId,selfId)
	if nHp <= 0 then
	
		ClearRageRecoverTick(sceneId, selfId)
		RestoreHp(sceneId, selfId,value)
		RestoreRage(sceneId, selfId,value)
		ClearMutexState(sceneId, selfId, 6)
		SendReliveResult(sceneId, selfId,1)
	end
	
	--骑上马,并且回血
	LastMount(sceneId, selfId )
	RestoreHp(sceneId, selfId,0)
end

---------------------------------------------------------------------------------------------------
--踢人
---------------------------------------------------------------------------------------------------
function x303001_KickPlayer(sceneId,selfId)

	--清除死亡状态
    x303001_DoPlayerRelive( sceneId, selfId, 100 )
    x303001_RestorePlayerCamp(sceneId,selfId)
    SetPlayerRuntimeData(sceneId,selfId,RD_BATTLE_SCENE_KICK_DOWN ,0)
    
    SetPVP2v2BattleDisable( sceneId,selfId,1,0)


    --如果存在BakScene信息，则以BakScene信息为准
    local nBakSceneId,x,z = GetPlayerBakSceneInfo(sceneId,selfId )
    if nBakSceneId >= 0 then
        NewWorld(sceneId,selfId,nBakSceneId,x,z,x303001_g_scriptId)
        return
    end

    --如果没有BakScene信息，则传送到王城新手村
    local nCountry = GetCurCountry(sceneId,selfId)
    if nCountry == 0 then
        
        --楼兰
        local nDestSceneId = 50
        local nPosX = 123
        local nPosZ = 57

        NewWorld(sceneId,selfId,nDestSceneId,nPosX,nPosZ,x303001_g_scriptId)

    elseif nCountry == 1 then
        
        --天山
        local nDestSceneId = 150
        local nPosX = 123
        local nPosZ = 57

        NewWorld(sceneId,selfId,nDestSceneId,nPosX,nPosZ,x303001_g_scriptId)

    elseif nCountry == 2 then

        --昆仑
        local nDestSceneId = 250
        local nPosX = 123
        local nPosZ = 57

        NewWorld(sceneId,selfId,nDestSceneId,nPosX,nPosZ,x303001_g_scriptId)

    elseif nCountry == 3 then
        
        --敦煌
        local nDestSceneId = 350
        local nPosX = 123
        local nPosZ = 57

        NewWorld(sceneId,selfId,nDestSceneId,nPosX,nPosZ,x303001_g_scriptId)
        
    end
end


---------------------------------------------------------------------------------------------------
--恢复阵营
---------------------------------------------------------------------------------------------------
function x303001_RestorePlayerCamp(sceneId,selfId)

	local nCountryId = GetCurCountry( sceneId,selfId )
    SetCurCamp(sceneId,selfId,nCountryId )
    
end

---------------------------------------------------------------------------------------------------
--时间同步，先暂时不用管
---------------------------------------------------------------------------------------------------
function x303001_SyncBattleTimeToAllPlayer(sceneId,nTime)
	
	local nHumanCount = GetScenePlayerCount( sceneId )
    local i = 0
    for i = 0,nHumanCount-1 do
        local objId = GetScenePlayerObjId( sceneId,i)
        if objId >= 0 then

            TimerCommand( sceneId, objId, 1, GUILDBATTLE_TIMERID, GUILDBATTLE_TIMERTYPE, x303001_g_scriptId,-1,-1)

            if nTime > 0 then
                TimerCommand( sceneId, objId, 2, GUILDBATTLE_TIMERID, GUILDBATTLE_TIMERTYPE, x303001_g_scriptId, nTime, nTime );
            end
        end
    end
end

----------------------------------------------------------------------------------------------
--从GLServer过来的同步国王争夺战时间的东东
----------------------------------------------------------------------------------------------
function x303001_OnSyncBattleTime( sceneId,nTime )
    
    --检查是否是PVP2v2竞技场
    local nBattleScene = x303001_GetBattleSceneType( sceneId )
    if  nBattleScene <= 0 then
        return
    end
    
    --检查场景是否有效
    local nBattleSceneValid = x303001_IsBattleSceneValid(sceneId)
    if nBattleSceneValid ~= 1 then
    	return	
    end
    
    x303001_SceneInfo[sceneId].TICKCOUNT = NumberCastIntToUInt( nTime )
    local DownTickCount = x303001_g_LimitTotalHoldTime - NumberCastIntToUInt( nTime )
    x303001_SyncBattleTimeToAllPlayer( sceneId, DownTickCount )
end

---------------------------------------------------------------------------------------------------
--检查战场结束
---------------------------------------------------------------------------------------------------
function x303001_CheckBattleFinished( sceneId )

	---------------------------------------------------------------------------------------------------	
	--1、只有一方玩家或是双方都不在了
	---------------------------------------------------------------------------------------------------
	if  x303001_CheckTeamA_AllLeave( sceneId ) == 1 or x303001_CheckTeamB_AllLeave( sceneId ) == 1 then
		return 1
	end
	
	---------------------------------------------------------------------------------------------------
	--2、某方玩家都死过
	---------------------------------------------------------------------------------------------------
	if x303001_CheckTeamA_AllDie( sceneId ) == 1 or x303001_CheckTeamB_AllDie( sceneId ) == 1 then
		return 1
	end
	
	---------------------------------------------------------------------------------------------------
	--3、只有一方玩家一个死亡，一个离开，则可以输
	---------------------------------------------------------------------------------------------------
	if x303001_CheckTeamA_Live( sceneId ) == 0 or x303001_CheckTeamB_Live( sceneId ) == 0 then
		return 1
	end
	
	
	return 0
end

---------------------------------------------------------------------------------------------------
--给战场奖励
---------------------------------------------------------------------------------------------------
function x303001_GiveBattleBonus( sceneId,nResult )
	
	if nResult == -1 then
		
		LuaThisScenceM2Wrold( sceneId,"平局",5,1)
		
		x303001_OnGiveTeamA(sceneId,-1)
		x303001_OnGiveTeamB(sceneId,-1)
		
	elseif nResult == 0 then
		
		LuaThisScenceM2Wrold( sceneId,"克烈军获胜",5,1)
		
		x303001_OnGiveTeamA(sceneId,0)
		x303001_OnGiveTeamB(sceneId,0)
		
	elseif nResult == 1 then
		
		LuaThisScenceM2Wrold( sceneId,"乃蛮军获胜",5,1)
		
		x303001_OnGiveTeamA(sceneId,1)
		x303001_OnGiveTeamB(sceneId,1)
	end
end

---------------------------------------------------------------------------------------------------
--队伍A的获奖
---------------------------------------------------------------------------------------------------
function x303001_OnGiveTeamA( sceneId, nBonusType )
		
	local humancount = GetScenePlayerCount(sceneId);
	for	i = 0, humancount - 1 do
		local humanId = GetScenePlayerObjId(sceneId, i);
		if IsPlayerStateNormal( sceneId,humanId ) == 1 then
			
			local GUID = GetPlayerGUID( sceneId,humanId )

			local p = NumberCastIntToUInt(x303001_TeamInfoA[sceneId][1].GUID)
			if GUID == p then
				
				local name = GetName(sceneId,humanId)
				if name == nil then
					name = "Error "
				end
				
				if nBonusType == -1 then
					
					LuaScenceM2Player( sceneId,humanId,format("#G获得#R%d#G点战场积分",x303001_g_Other_Bonus_Mark),name,2,1)
					
					x303001_AddPVP2V2Level(sceneId,humanId,0)
					AddPVP2V2Mark(sceneId,humanId,x303001_g_Other_Bonus_Mark)
					
				elseif nBonusType == 0 then			
					
					if x303001_LevelFlag[sceneId] == 1 then
						LuaScenceM2Player( sceneId,humanId,"#G战场等级相差悬殊（20级以上），无法获得战场等级！",name,2,1)
					else
						LuaScenceM2Player( sceneId,humanId,format("#G战场等级+%d",x303001_g_Winner_Bonus_Level),name,2,1)
						x303001_AddPVP2V2Level(sceneId,humanId,x303001_g_Winner_Bonus_Level)
					end
					
					
					LuaScenceM2Player( sceneId,humanId,format("#G获得#R%d#G点战场积分",x303001_g_Winner_Bonus_Mark),name,2,1)
					AddPVP2V2Mark(sceneId,humanId,x303001_g_Winner_Bonus_Mark)	
					
				elseif nBonusType == 1 then
					
					LuaScenceM2Player( sceneId,humanId,format("#G战场等级-%d",x303001_g_Loser_Bonus_Level),name,2,1)
					LuaScenceM2Player( sceneId,humanId,format("#G获得#R%d#G点战场积分",x303001_g_Loser_Bonus_Mark),name,2,1)	
					
					x303001_SubPVP2V2Level(sceneId,humanId,x303001_g_Loser_Bonus_Level)
					AddPVP2V2Mark(sceneId,humanId,x303001_g_Loser_Bonus_Mark)
					
				end
				
			end
			
			p = NumberCastIntToUInt(x303001_TeamInfoA[sceneId][2].GUID)
			if GUID == p then
				
				local name = GetName(sceneId,humanId)
				if name == nil then
					name = "Error "
				end
				
				if nBonusType == -1 then
					
					LuaScenceM2Player( sceneId,humanId,format("#G获得#R%d#G点战场积分",x303001_g_Other_Bonus_Mark),name,2,1)
					
					x303001_AddPVP2V2Level(sceneId,humanId,0)
					AddPVP2V2Mark(sceneId,humanId,x303001_g_Other_Bonus_Mark)
					
				elseif nBonusType == 0 then
					
					if x303001_LevelFlag[sceneId] == 1 then
						LuaScenceM2Player( sceneId,humanId,"#G战场等级相差悬殊（20级以上），无法获得战场等级！",name,2,1)
					else
						LuaScenceM2Player( sceneId,humanId,format("#G战场等级+%d",x303001_g_Winner_Bonus_Level),name,2,1)	
						x303001_AddPVP2V2Level(sceneId,humanId,x303001_g_Winner_Bonus_Level)
					end
					
					LuaScenceM2Player( sceneId,humanId,format("#G获得#R%d#G点战场积分",x303001_g_Winner_Bonus_Mark),name,2,1)
					AddPVP2V2Mark(sceneId,humanId,x303001_g_Winner_Bonus_Mark)				
					
				elseif nBonusType == 1 then
					
					LuaScenceM2Player( sceneId,humanId,format("#G战场等级-%d",x303001_g_Loser_Bonus_Level),name,2,1)
					LuaScenceM2Player( sceneId,humanId,format("#G获得#R%d#G点战场积分",x303001_g_Loser_Bonus_Mark),name,2,1)	
					
					x303001_SubPVP2V2Level(sceneId,humanId,x303001_g_Loser_Bonus_Level)
					AddPVP2V2Mark(sceneId,humanId,x303001_g_Loser_Bonus_Mark)
				end
			end
		end
	end
end

---------------------------------------------------------------------------------------------------
--队伍B的获奖
---------------------------------------------------------------------------------------------------
function x303001_OnGiveTeamB( sceneId, nBonusType )

	local humancount = GetScenePlayerCount(sceneId);
	for	i = 0, humancount - 1 do
		local humanId = GetScenePlayerObjId(sceneId, i);
		if IsPlayerStateNormal( sceneId,humanId ) == 1 then
			
			local GUID = GetPlayerGUID( sceneId,humanId )

			local p = NumberCastIntToUInt(x303001_TeamInfoB[sceneId][1].GUID)
			if GUID == p then
				
				local name = GetName(sceneId,humanId)
				if name == nil then
					name = "Error "
				end
				
				if nBonusType == -1 then
					
					LuaScenceM2Player( sceneId,humanId,format("#G获得#R%d#G点战场积分",x303001_g_Other_Bonus_Mark),name,2,1)
					
					x303001_AddPVP2V2Level(sceneId,humanId,0)
					AddPVP2V2Mark(sceneId,humanId,x303001_g_Other_Bonus_Mark)
					
				elseif nBonusType == 0 then
					
					LuaScenceM2Player( sceneId,humanId,format("#G战场等级-%d",x303001_g_Loser_Bonus_Level),name,2,1)
					LuaScenceM2Player( sceneId,humanId,format("#G获得#R%d#G点战场积分",x303001_g_Loser_Bonus_Mark),name,2,1)
					
					x303001_SubPVP2V2Level(sceneId,humanId,x303001_g_Loser_Bonus_Level)
					AddPVP2V2Mark(sceneId,humanId,x303001_g_Loser_Bonus_Mark)
					
				elseif nBonusType == 1 then					
					
					
					if x303001_LevelFlag[sceneId] == 2 then
						LuaScenceM2Player( sceneId,humanId,"#G战场等级相差悬殊（20级以上），无法获得战场等级！",name,2,1)
					else
						LuaScenceM2Player( sceneId,humanId,format("#G战场等级+%d",x303001_g_Winner_Bonus_Level),name,2,1)
						x303001_AddPVP2V2Level(sceneId,humanId,x303001_g_Winner_Bonus_Level)
					end
					
					LuaScenceM2Player( sceneId,humanId,format("#G获得#R%d#G点战场积分",x303001_g_Winner_Bonus_Mark),name,2,1)
					AddPVP2V2Mark(sceneId,humanId,x303001_g_Winner_Bonus_Mark)	
					
				end
				
			end
			
			p = NumberCastIntToUInt(x303001_TeamInfoB[sceneId][2].GUID)
			if GUID == p then
				
				local name = GetName(sceneId,humanId)
				if name == nil then
					name = "Error "
				end
				
				if nBonusType == -1 then
					
					LuaScenceM2Player( sceneId,humanId,format("#G获得#R%d#G点战场积分",x303001_g_Other_Bonus_Mark),name,2,1)		
					
					x303001_AddPVP2V2Level(sceneId,humanId,0)
					AddPVP2V2Mark(sceneId,humanId,x303001_g_Other_Bonus_Mark)	
					
				elseif nBonusType == 0 then
					
					LuaScenceM2Player( sceneId,humanId,format("#G战场等级-%d",x303001_g_Loser_Bonus_Level),name,2,1)
					LuaScenceM2Player( sceneId,humanId,format("#G获得#R%d#G点战场积分",x303001_g_Loser_Bonus_Mark),name,2,1)
					
					x303001_SubPVP2V2Level(sceneId,humanId,x303001_g_Loser_Bonus_Level)
					AddPVP2V2Mark(sceneId,humanId,x303001_g_Loser_Bonus_Mark)
					
				elseif nBonusType == 1 then
					
					if x303001_LevelFlag[sceneId] == 2 then
						LuaScenceM2Player( sceneId,humanId,"#G战场等级相差悬殊（20级以上），无法获得战场等级！",name,2,1)
					else
						LuaScenceM2Player( sceneId,humanId,format("#G战场等级+%d",x303001_g_Winner_Bonus_Level),name,2,1)
						x303001_AddPVP2V2Level(sceneId,humanId,x303001_g_Winner_Bonus_Level)
					end
					
					LuaScenceM2Player( sceneId,humanId,format("#G获得#R%d#G点战场积分",x303001_g_Winner_Bonus_Mark),name,2,1)	
					AddPVP2V2Mark(sceneId,humanId,x303001_g_Winner_Bonus_Mark)	
					
				end
			end
		end
	end
	
end

---------------------------------------------------------------------------------------------------
--生成战场结果
---------------------------------------------------------------------------------------------------
function x303001_GenBattleResult( sceneId )

	--如果已经开始关闭，则不允许给奖励
	if x303001_SceneInfo[sceneId].ISCLOSING == 1 then
		return
	end
	
	local nResult = -1 

	---------------------------------------------------------------------------------------------------	
	--1、只有一方玩家
	---------------------------------------------------------------------------------------------------
	
	--当A组玩家在，B组玩家不在，认为A组赢	
	if  x303001_CheckTeamA_AllLeave( sceneId ) == 0 and x303001_CheckTeamB_AllLeave( sceneId ) == 1 then
		nResult = 0
		x303001_GiveBattleBonus( sceneId,nResult )
		return
	end
	
	--当A组玩家不在，B组玩家在，认为B组赢
	if  x303001_CheckTeamA_AllLeave( sceneId ) == 1 and x303001_CheckTeamB_AllLeave( sceneId ) == 0 then
		nResult = 1
		x303001_GiveBattleBonus( sceneId,nResult )
		return
	end
	
	---------------------------------------------------------------------------------------------------
	--2、某方玩家都死过
	---------------------------------------------------------------------------------------------------
	
	--当A组玩家没有全死过，B组玩家全死过，认为A组赢
	if x303001_CheckTeamA_AllDie( sceneId ) == 0 and x303001_CheckTeamB_AllDie( sceneId ) == 1 then
		nResult = 0
		x303001_GiveBattleBonus( sceneId,nResult )
		return
	end
	
	--当A组玩家全死过，B组玩家没有全死过，认为B组赢
	if x303001_CheckTeamA_AllDie( sceneId ) == 1 and x303001_CheckTeamB_AllDie( sceneId ) == 0 then
		nResult = 1
		x303001_GiveBattleBonus( sceneId,nResult )
		return
	end
	
	---------------------------------------------------------------------------------------------------
	--3.检查某方玩家活着的情况
	---------------------------------------------------------------------------------------------------
	if x303001_CheckTeamA_Live( sceneId ) == 1 and x303001_CheckTeamB_Live( sceneId ) == 0 then
		nResult = 0
		x303001_GiveBattleBonus( sceneId,nResult )
		return
	end
	
	if x303001_CheckTeamA_Live( sceneId ) == 0 and x303001_CheckTeamB_Live( sceneId ) == 1 then
		nResult = 1
		x303001_GiveBattleBonus( sceneId,nResult )
		return
	end
	
	---------------------------------------------------------------------------------------------------
	--4、检查活着的玩家的数量
	---------------------------------------------------------------------------------------------------
	if x303001_GetTeamA_LiveCount(sceneId ) > x303001_GetTeamB_LiveCount(sceneId)  then
		nResult = 0
		x303001_GiveBattleBonus( sceneId,nResult )
		return
	end
	
	if x303001_GetTeamA_LiveCount(sceneId ) < x303001_GetTeamB_LiveCount(sceneId)  then
		nResult = 1
		x303001_GiveBattleBonus( sceneId,nResult )
		return
	end	
	
	---------------------------------------------------------------------------------------------------
	--5、不满足1和2,3,4
	---------------------------------------------------------------------------------------------------
	
	--其他情况,认为战平，如果没人，不处理
	if  x303001_CheckTeamA_AllLeave( sceneId ) == 0 and x303001_CheckTeamB_AllLeave( sceneId ) == 0 then
		nResult = -1
		x303001_GiveBattleBonus( sceneId,nResult )
		return
	end
		
end


---------------------------------------------------------------------------------------------------
--检查队伍A是否全部离开
---------------------------------------------------------------------------------------------------
function x303001_CheckTeamA_AllLeave( sceneId )

	local humancount = GetScenePlayerCount(sceneId);
	for	i = 0, humancount - 1 do
		local humanId = GetScenePlayerObjId(sceneId, i);
		if IsPlayerStateNormal( sceneId,humanId ) == 1 then
			
			local GUID = GetPlayerGUID( sceneId,humanId )
			
			--1
			local p = NumberCastIntToUInt(x303001_TeamInfoA[sceneId][1].GUID)
			if GUID == p then
				return 0
			end
			
			--2
			p = NumberCastIntToUInt(x303001_TeamInfoA[sceneId][2].GUID)
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
function x303001_CheckTeamB_AllLeave( sceneId )
	
	local humancount = GetScenePlayerCount(sceneId);
	for	i = 0, humancount - 1 do
		local humanId = GetScenePlayerObjId(sceneId, i);
		if IsPlayerStateNormal( sceneId,humanId ) == 1 then
			
			local GUID = GetPlayerGUID( sceneId,humanId )
			
			--3
			local p = NumberCastIntToUInt(x303001_TeamInfoB[sceneId][1].GUID)
			if GUID == p then
				return 0
			end
			
			--4
			p = NumberCastIntToUInt(x303001_TeamInfoB[sceneId][2].GUID)
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
function x303001_CheckTeamA_AllDie( sceneId )
	
	--进行计数
	
	local nCount = 0
	if x303001_TeamInfoA[sceneId][1].DIE == 1 then
		nCount = nCount + 1
	end
	
	if x303001_TeamInfoA[sceneId][2].DIE == 1 then
		nCount = nCount + 1
	end
	
	--当计数为2表示A组玩家都死过
	if nCount == 2 then
		return 1
	end
	
	return 0
end

---------------------------------------------------------------------------------------------------
--检查活着的玩家
---------------------------------------------------------------------------------------------------
function x303001_CheckTeamA_Live( sceneId )
	
	--如果只有一方玩家，则判断死亡或是其他
	local nLiveCount = 0
	local humancount = GetScenePlayerCount(sceneId);
	for	i = 0, humancount - 1 do
		local humanId = GetScenePlayerObjId(sceneId, i);
		if IsPlayerStateNormal( sceneId,humanId ) == 1 then
			
			local GUID = GetPlayerGUID( sceneId,humanId )
			
			--1
			local p = NumberCastIntToUInt(x303001_TeamInfoA[sceneId][1].GUID)
			if GUID == p then
				if x303001_TeamInfoA[sceneId][1].DIE ~= 1 then
					nLiveCount = nLiveCount + 1
				end
			end
			
			--2
			p = NumberCastIntToUInt(x303001_TeamInfoA[sceneId][2].GUID)
			if GUID == p then
				if x303001_TeamInfoA[sceneId][2].DIE ~= 1 then
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
--检查活着的玩家
---------------------------------------------------------------------------------------------------
function x303001_CheckTeamB_Live( sceneId )
	
	--如果只有一方玩家，则判断死亡或是其他
	local nLiveCount = 0
	local humancount = GetScenePlayerCount(sceneId);
	for	i = 0, humancount - 1 do
		local humanId = GetScenePlayerObjId(sceneId, i);
		if IsPlayerStateNormal( sceneId,humanId ) == 1 then
			
			local GUID = GetPlayerGUID( sceneId,humanId )
			
			--1
			local p = NumberCastIntToUInt(x303001_TeamInfoB[sceneId][1].GUID)
			if GUID == p then
				if x303001_TeamInfoB[sceneId][1].DIE ~= 1 then
					nLiveCount = nLiveCount + 1
				end
			end
			
			--2
			p = NumberCastIntToUInt(x303001_TeamInfoB[sceneId][2].GUID)
			if GUID == p then
				if x303001_TeamInfoB[sceneId][2].DIE ~= 1 then
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
--取得活着的玩家的数量
---------------------------------------------------------------------------------------------------
function x303001_GetTeamA_LiveCount( sceneId )
	
	--如果只有一方玩家，则判断死亡或是其他
	local nLiveCount = 0
	local humancount = GetScenePlayerCount(sceneId);
	for	i = 0, humancount - 1 do
		local humanId = GetScenePlayerObjId(sceneId, i);
		if IsPlayerStateNormal( sceneId,humanId ) == 1 then
			
			local GUID = GetPlayerGUID( sceneId,humanId )
			
			--1
			local p = NumberCastIntToUInt(x303001_TeamInfoA[sceneId][1].GUID)
			if GUID == p then
				if x303001_TeamInfoA[sceneId][1].DIE ~= 1 then
					nLiveCount = nLiveCount + 1
				end
			end
			
			--2
			p = NumberCastIntToUInt(x303001_TeamInfoA[sceneId][2].GUID)
			if GUID == p then
				if x303001_TeamInfoA[sceneId][2].DIE ~= 1 then
					nLiveCount = nLiveCount + 1
				end
			end
		end
		
	end
	
	return nLiveCount
end

---------------------------------------------------------------------------------------------------
--检查活着的玩家
---------------------------------------------------------------------------------------------------
function x303001_GetTeamB_LiveCount( sceneId )
	
	--如果只有一方玩家，则判断死亡或是其他
	local nLiveCount = 0
	local humancount = GetScenePlayerCount(sceneId);
	for	i = 0, humancount - 1 do
		local humanId = GetScenePlayerObjId(sceneId, i);
		if IsPlayerStateNormal( sceneId,humanId ) == 1 then
			
			local GUID = GetPlayerGUID( sceneId,humanId )
			
			--1
			local p = NumberCastIntToUInt(x303001_TeamInfoB[sceneId][1].GUID)
			if GUID == p then
				if x303001_TeamInfoB[sceneId][1].DIE ~= 1 then
					nLiveCount = nLiveCount + 1
				end
			end
			
			--2
			p = NumberCastIntToUInt(x303001_TeamInfoB[sceneId][2].GUID)
			if GUID == p then
				if x303001_TeamInfoB[sceneId][2].DIE ~= 1 then
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
function x303001_CheckTeamB_AllDie( sceneId )
	
	--进行计数
	
	local nCount = 0
	if x303001_TeamInfoB[sceneId][1].DIE == 1 then
		nCount = nCount + 1
	end
	
	if x303001_TeamInfoB[sceneId][2].DIE == 1 then
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
function x303001_CheckPlayerValid( sceneId,selfId )
	
	local GUID = GetPlayerGUID(sceneId,selfId)

	local p = NumberCastIntToUInt(x303001_TeamInfoA[sceneId][1].GUID)
	if GUID == p then
		return 1
	end
	
	p = NumberCastIntToUInt(x303001_TeamInfoA[sceneId][2].GUID)
	if GUID == p then
		return 1
	end
	
	p = NumberCastIntToUInt(x303001_TeamInfoB[sceneId][1].GUID)
	if GUID == p then
		return 1
	end
	
	p = NumberCastIntToUInt(x303001_TeamInfoB[sceneId][2].GUID)
	if GUID == p then
		return 1
	end
	
	return 0

end

---------------------------------------------------------------------------------------------------
--取得玩家死亡标记
---------------------------------------------------------------------------------------------------
function x303001_GetPlayerDieFlag( sceneId,selfId )
	
	local GUID = GetPlayerGUID(sceneId,selfId)

	local p = NumberCastIntToUInt(x303001_TeamInfoA[sceneId][1].GUID)
	if GUID == p then
		return x303001_TeamInfoA[sceneId][1].DIE;
	end
	
	p = NumberCastIntToUInt(x303001_TeamInfoA[sceneId][2].GUID)
	if GUID == p then
		return x303001_TeamInfoA[sceneId][2].DIE;
	end
	
	p = NumberCastIntToUInt(x303001_TeamInfoB[sceneId][1].GUID)
	if GUID == p then
		return x303001_TeamInfoB[sceneId][1].DIE;
	end
	
	p = NumberCastIntToUInt(x303001_TeamInfoB[sceneId][2].GUID)
	if GUID == p then
		return x303001_TeamInfoB[sceneId][2].DIE;
	end
	
	return 1
	
end

---------------------------------------------------------------------------------------------------
--设置玩家死亡标记
---------------------------------------------------------------------------------------------------
function x303001_SetPlayerDieFlag( sceneId,selfId )

	local GUID = GetPlayerGUID(sceneId,selfId)

	local p = NumberCastIntToUInt(x303001_TeamInfoA[sceneId][1].GUID)
	if GUID == p then
		x303001_TeamInfoA[sceneId][1].DIE = 1
		return
	end
	
	p = NumberCastIntToUInt(x303001_TeamInfoA[sceneId][2].GUID)
	if GUID == p then
		x303001_TeamInfoA[sceneId][2].DIE = 1
		return
	end
	
	p = NumberCastIntToUInt(x303001_TeamInfoB[sceneId][1].GUID)
	if GUID == p then
		x303001_TeamInfoB[sceneId][1].DIE = 1
		return
	end
	
	p = NumberCastIntToUInt(x303001_TeamInfoB[sceneId][2].GUID)
	if GUID == p then
		x303001_TeamInfoB[sceneId][2].DIE = 1
		return
	end
	
end

---------------------------------------------------------------------------------------------------
--取得玩家进入战场标记
---------------------------------------------------------------------------------------------------
function x303001_GetPlayerEnterSceneFlag( sceneId,selfId)

	local GUID = GetPlayerGUID(sceneId,selfId)

	local p = NumberCastIntToUInt(x303001_TeamInfoA[sceneId][1].GUID)
	if GUID == p then
		return x303001_TeamInfoA[sceneId][1].ENTER
	end
	
	p = NumberCastIntToUInt(x303001_TeamInfoA[sceneId][2].GUID)
	if GUID == p then
		return x303001_TeamInfoA[sceneId][2].ENTER
	end
	
	p = NumberCastIntToUInt(x303001_TeamInfoB[sceneId][1].GUID)
	if GUID == p then
		return x303001_TeamInfoB[sceneId][1].ENTER
	end
	
	p = NumberCastIntToUInt(x303001_TeamInfoB[sceneId][2].GUID)
	if GUID == p then
		return x303001_TeamInfoB[sceneId][2].ENTER
	end
	
	return 1
end

---------------------------------------------------------------------------------------------------
--设置玩家进入战场标记
---------------------------------------------------------------------------------------------------
function x303001_SetPlayerEnterSceneFlag( sceneId,selfId)

	--设置玩家进入标记
	local GUID = GetPlayerGUID(sceneId,selfId)

	local p = NumberCastIntToUInt(x303001_TeamInfoA[sceneId][1].GUID)
	if GUID == p then
		x303001_TeamInfoA[sceneId][1].ENTER = 1
		return
	end
	
	p = NumberCastIntToUInt(x303001_TeamInfoA[sceneId][2].GUID)
	if GUID == p then
		x303001_TeamInfoA[sceneId][2].ENTER = 1
		return
	end
	
	p = NumberCastIntToUInt(x303001_TeamInfoB[sceneId][1].GUID)
	if GUID == p then
		x303001_TeamInfoB[sceneId][1].ENTER = 1
		return
	end
	
	p = NumberCastIntToUInt(x303001_TeamInfoB[sceneId][2].GUID)
	if GUID == p then
		x303001_TeamInfoB[sceneId][2].ENTER = 1
		return
	end
end

---------------------------------------------------------------------------------------------------
--取得玩家离开战场标记
---------------------------------------------------------------------------------------------------
function x303001_GetPlayerLeaveSceneFlag( sceneId,selfId)

	local GUID = GetPlayerGUID(sceneId,selfId)

	local p = NumberCastIntToUInt(x303001_TeamInfoA[sceneId][1].GUID)
	if GUID == p then
		return x303001_TeamInfoA[sceneId][1].LEAVE
	end
	
	p = NumberCastIntToUInt(x303001_TeamInfoA[sceneId][2].GUID)
	if GUID == p then
		return x303001_TeamInfoA[sceneId][2].LEAVE
	end
	
	p = NumberCastIntToUInt(x303001_TeamInfoB[sceneId][1].GUID)
	if GUID == p then
		return x303001_TeamInfoB[sceneId][1].LEAVE
	end
	
	p = NumberCastIntToUInt(x303001_TeamInfoB[sceneId][2].GUID)
	if GUID == p then
		return x303001_TeamInfoB[sceneId][2].LEAVE
	end
	
	return 1
end

---------------------------------------------------------------------------------------------------
--设置玩家进入战场标记
---------------------------------------------------------------------------------------------------
function x303001_SetPlayerLeaveSceneFlag( sceneId,selfId)

	--设置玩家进入标记
	local GUID = GetPlayerGUID(sceneId,selfId)

	local p = NumberCastIntToUInt(x303001_TeamInfoA[sceneId][1].GUID)
	if GUID == p then
		x303001_TeamInfoA[sceneId][1].LEAVE = 1
		return
	end
	
	p = NumberCastIntToUInt(x303001_TeamInfoA[sceneId][2].GUID)
	if GUID == p then
		x303001_TeamInfoA[sceneId][2].LEAVE = 1
		return
	end
	
	p = NumberCastIntToUInt(x303001_TeamInfoB[sceneId][1].GUID)
	if GUID == p then
		x303001_TeamInfoB[sceneId][1].LEAVE = 1
		return
	end
	
	p = NumberCastIntToUInt(x303001_TeamInfoB[sceneId][2].GUID)
	if GUID == p then
		x303001_TeamInfoB[sceneId][2].LEAVE = 1
		return
	end
end

---------------------------------------------------------------------------------------------------
--战场准备好了
---------------------------------------------------------------------------------------------------
function x303001_OnBattleSceneReady(sceneId,nTotalTime)
	
	--场景相关信息							  
	x303001_SceneInfo[sceneId] = {
						TICKCOUNT = 0,
						ISCLOSING = 0,
						LEAVECOUNTDOWN = 0,
						RESULT = 0,
						LIMITHOLDTIME = nTotalTime,
				  	  }
				  	  
	local msg = format("P2BL:x303001_OnBattleSceneReady SceneId=%d ",sceneId  )
	WriteLog(1,msg)
	
	
	--设置动态阻挡
	x303001_SetTempImpassable(sceneId)
		
end

---------------------------------------------------------------------------------------------------
--战场关闭
---------------------------------------------------------------------------------------------------
function x303001_OnBattleSceneClose(sceneId,flag )
	
	x303001_GenBattleResult( sceneId )
	
	if x303001_SceneInfo[sceneId].ISCLOSING == 1	then
		return
	end
	
	--场景相关信息							  
	x303001_SceneInfo[sceneId].ISCLOSING = 1	
	x303001_SceneInfo[sceneId].TICKCOUNT = 0
	local msg = format("P2BL:x303001_OnBattleSceneClose SceneId=%d flag=%d",sceneId,flag  )
	WriteLog(1,msg)
	
end

---------------------------------------------------------------------------------------------------
--战场关闭
---------------------------------------------------------------------------------------------------
function x303001_OnBattleMatchOOD(sceneId,selfId)
	
	local name = GetName(sceneId,selfId)
	LuaScenceM2Player( sceneId,selfId,"双人战场：你所在的队伍本次轮空！",name,2,1)	
	LuaScenceM2Player( sceneId,selfId,"双人战场：你所在的队伍本次轮空！",name,3,1)	
	
end

---------------------------------------------------------------------------------------------------
--设置玩家需要踢出去
---------------------------------------------------------------------------------------------------
function x303001_SetPlayerNeedKick( sceneId,selfId)
	
	local KickDown = GetPlayerRuntimeData( sceneId,selfId,RD_BATTLE_SCENE_KICK_DOWN ) 
    if KickDown <= 0 or KickDown > x303001_g_Kick_Down then                
        SetPlayerRuntimeData( sceneId,selfId,RD_BATTLE_SCENE_KICK_DOWN ,x303001_g_Kick_Down) 
    end
	
end

----------------------------------------------------------------------------------------------
--设置所有玩家需要踢掉
----------------------------------------------------------------------------------------------
function x303001_SetAllPlayerNeedKick( sceneId )
    
    local nHumanCount = GetScenePlayerCount( sceneId )
    local i = 0
    for i = 0,nHumanCount-1 do
        local objId = GetScenePlayerObjId( sceneId,i)
        if objId >= 0 then
            local KickDown = GetPlayerRuntimeData( sceneId,objId,RD_BATTLE_SCENE_KICK_DOWN ) 
            if KickDown <= 0 or KickDown > x303001_g_Kick_Down then                
                SetPlayerRuntimeData( sceneId,objId,RD_BATTLE_SCENE_KICK_DOWN ,x303001_g_Kick_Down) 
            end
        end
    end
end

----------------------------------------------------------------------------------------------
--更新玩家踢掉状态
----------------------------------------------------------------------------------------------
function x303001_UpdatePlayerKickState( sceneId )
    
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
                    x303001_KickPlayer( sceneId,objId )                    
                else
                    --否则，继续倒计时
                    SetPlayerRuntimeData( sceneId,objId,RD_BATTLE_SCENE_KICK_DOWN ,KickDown) 
                end
            end
        end
    end
end

----------------------------------------------------------------------------------------------
--生成动态阻挡
----------------------------------------------------------------------------------------------
function x303001_SetTempImpassable(sceneId)
	
	local nIndex = x303001_GetBattleSceneType(sceneId)
	
	for i,itm in x303001_g_TempImpassable do
		if itm.Flag == nIndex then
			AddSceneTempImpassable(sceneId,itm.Left,itm.Top,itm.Right,itm.Bottom)
		end
	end
	
end

----------------------------------------------------------------------------------------------
--删除动态阻挡
----------------------------------------------------------------------------------------------
function x303001_ClearTempImpassable(sceneId)
	
	LuaThisScenceM2Wrold( sceneId,"战斗开始",5,1)
	
	local nIndex = x303001_GetBattleSceneType(sceneId)
	
	for i,itm in x303001_g_TempImpassable do
		if itm.Flag == nIndex then
			DelSceneTempImpassable(sceneId,itm.Left,itm.Top,itm.Right,itm.Bottom)
		end
	end
	
	--清除特效
	local nHumanCount = GetScenePlayerCount( sceneId )
    for i = 0,nHumanCount-1 do
        local objId = GetScenePlayerObjId( sceneId,i)
        if objId >= 0 then
            CallScriptFunction(UTILITY_SCRIPT,"StopClientMapColor", sceneId, objId, 0)
        end
    end
end

function x303001_AddPVP2V2Level(mapId,playerId,delta)
	local day = GetQuestData( mapId, playerId, MD_PVP2V2_LEVEL_DAY[1], MD_PVP2V2_LEVEL_DAY[2], MD_PVP2V2_LEVEL_DAY[3] )
	local curday = GetWeekFirstDay()
	if day ~= curday then
		local value = GetPVP2V2Level(mapId,playerId)
		SubPVP2V2Level(mapId,playerId,value)
		AddPVP2V2Level(mapId,playerId,500)
		SetQuestData( mapId, playerId, MD_PVP2V2_LEVEL_DAY[1], MD_PVP2V2_LEVEL_DAY[2], MD_PVP2V2_LEVEL_DAY[3], curday )
	end	
	AddPVP2V2Level(mapId,playerId,delta)
end

function x303001_SubPVP2V2Level(mapId,playerId,delta)
	local day = GetQuestData( mapId, playerId, MD_PVP2V2_LEVEL_DAY[1], MD_PVP2V2_LEVEL_DAY[2], MD_PVP2V2_LEVEL_DAY[3] )
	local curday = GetWeekFirstDay()
	if day ~= curday then
		local value = GetPVP2V2Level(mapId,playerId)
		SubPVP2V2Level(mapId,playerId,value)
		AddPVP2V2Level(mapId,playerId,500)
		SetQuestData( mapId, playerId, MD_PVP2V2_LEVEL_DAY[1], MD_PVP2V2_LEVEL_DAY[2], MD_PVP2V2_LEVEL_DAY[3], curday )
	end	
	SubPVP2V2Level(mapId,playerId,delta)
end
