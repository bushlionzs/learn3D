--##########################################
--##跨服 2v2 战场报名脚本 by rj 2010-9-24 ##
--##########################################

x303100_g_ScriptId          		= 303100
x303100_g_MissionName       		="【跨服战场】双人战场申请"
x303100_g_BackSceneIdAry		    = {0, 0, 0, 0}								--四国从报名场景上线已过报名签证时间退回场景 id
x303100_g_BackPosAry		     	= {{168, 68}, {168, 68}, {168, 68}, {168, 68}}		--四国从报名场景上线已过报名签证时间退回场景坐标
x303100_g_curSignupTypeTbl 			= {}												--当前玩家报名双人战场类型表

----------------------------------------------------------------------------------------------
--枚举
----------------------------------------------------------------------------------------------
function x303100_ProcEnumEvent(sceneId, selfId, targetId, missionId)

	--必须是报名场景
	if GetSceneType(sceneId) ~= 8 then
		return
	end
		
	--合服开关
    if GetMergeDBToggle() == 1 then
        return
    end
    
  	--升级数据库开关
	if GetUpdateDBBeforeToggle() == 1 then
		return
	end
    
    --只有在报名时间段内才开启
    if CallScriptFunction(MPVP2V2_BATTLE_SCRIPT, "IsBattleSignup", sceneId) == 1 then
    	AddQuestNumText(sceneId, x303100_g_ScriptId, x303100_g_MissionName, 3)
    else
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "\t现在不在跨服战场报名时间段内，无法报名！");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId, selfId, targetId)
    end
end

----------------------------------------------------------------------------------------------
--默认事件
----------------------------------------------------------------------------------------------
function x303100_ProcEventEntry(sceneId, selfId, targetId, scriptId, idExt)

	--必须是报名场景
	if GetSceneType(sceneId) ~= 8 then
		return
	end

	--合服开关
    if GetMergeDBToggle() == 1 then
        return
    end
    
  	--升级数据库开关
	if GetUpdateDBBeforeToggle() == 1 then
		return
	end
    
    --还没有开始
    if CallScriptFunction(MPVP2V2_BATTLE_SCRIPT, "IsBattleSignup", sceneId) ~= 1 then
    	BeginQuestEvent(sceneId)
        AddQuestText(sceneId, "\t跨服双人战场报名还没有开始！");
        EndQuestEvent(sceneId)
        DispatchQuestEventList(sceneId, selfId, targetId)
    	return
    end
    
  	--非队长
	if IsTeamLeader(sceneId, selfId) ~= 1 then
		BeginQuestEvent(sceneId)
        AddQuestText(sceneId, "\t只有队长才能申请参加跨服双人战场！");
        EndQuestEvent(sceneId)
        DispatchQuestEventList(sceneId, selfId, targetId)
        return
	end
    	    
    if idExt == 0 then
       
        --查询结果
        MPVP2v2SignupState(sceneId, selfId ,targetId)
    elseif idExt == 1 then
    
        --以上都通过，发送申请
       	MPVP2v2Signup(sceneId, selfId, targetId)
	end
	
    return 1
end

----------------------------------------------------------------------------------------------
--查询报名结果
----------------------------------------------------------------------------------------------
function x303100_OnMQuerySignupResult(sceneId, selfId, result, targetId)

    if result == 1 then
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "\t很抱歉，双人战场还没有开始！")
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId, selfId, targetId)
        return 0
    elseif result == 2 then
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "\t您没有队伍！")
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId, selfId, targetId)
        return 0
    elseif result == 3 then
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "\t您所在队伍人数必须为2人才能报名双人战场。")
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId, selfId, targetId)
        return 0
    elseif result == 4 then --该条件已经无效，目前报名时是扫描的周围在线队友
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "\t您所在队伍的玩家必须都在线。")
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId, selfId, targetId)
        return 0
    elseif result == 5 then
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "\t您已经报过名了！");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId, selfId, targetId)
        return 0
    elseif result == 6 then
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "\t您的队友已经报过名了！");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId, selfId, targetId)
        return 0
    elseif result == 7 then
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "\t这次的双人战场报名已经满了，请等候下场战斗。");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId, selfId, targetId)
        return 0
    elseif result == 8 then
    	
    	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "\t很抱歉，您的等级不足40级！");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId, selfId, targetId)
		return 0
    elseif result == 9 then
    	
    	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "\t很抱歉，您的队友的等级必须在40级以上！");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId, selfId, targetId)
		return 0		
    elseif result == 10 then
    	
    	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "\t您周围的在线队友数不足2人！");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId, selfId, targetId)
		return 0
    end

    BeginQuestEvent(sceneId)
    AddQuestText(sceneId, "\t您是否要报名参加【战场】双人战场？");
    AddQuestNumText(sceneId, x303100_g_ScriptId, "确定", 3, 1);
    EndQuestEvent(sceneId)
    DispatchQuestEventList(sceneId, selfId, targetId)
    return 1
end

----------------------------------------------------------------------------------------------
--报名结果
----------------------------------------------------------------------------------------------
function x303100_OnMSignupResult(sceneId, selfId, result, targetId)
    
    if result == 1 then
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "\t很抱歉，双人战场还没有开始！");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId, selfId, targetId)
        return 0
    elseif result == 2 then
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "\t您没有队伍！");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId, selfId, targetId)
        return 0
    elseif result == 3 then
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "\t您所在队伍人数必须为2人才能报名双人战场。");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId, selfId, targetId)
        return 0
    elseif result == 4 then --该条件已经无效，目前报名时是扫描的周围在线队友
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "\t您所在队伍的玩家必须都在线。");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId, selfId, targetId)
        return 0
    elseif result == 5 then
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "\t您已经报过名了！");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId, selfId, targetId)
        return 0
    elseif result == 6 then
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "\t您的队友已经报过名了！");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId, selfId, targetId)
        return 0
    elseif result == 7 then
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "\t这次的双人战场报名已经满了，请等候下场战斗。");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId, selfId, targetId)
        return 0
    elseif result == 8 then
    	
    	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "\t很抱歉，您的等级不足40级！");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId, selfId, targetId)
		return 0
    elseif result == 9 then
    	
    	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "\t很抱歉，您的队友的等级必须在40级以上！");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId, selfId, targetId)
		return 0
		
 	elseif result == 10 then
    	
    	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "\t您周围的在线队友数不足2人！");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId, selfId, targetId)
		return 0
    end

    BeginQuestEvent(sceneId)
    AddQuestText(sceneId, "\t#G您成功的申请了【战场】双人战场，请等待比赛的开始,#R请勿离开本场景#G，以免无法接收到进入战场的邀请！");
	EndQuestEvent(sceneId)
	DispatchQuestEventList(sceneId, selfId, targetId)
	
	--将报名场景上的队友全部取消报名签证，这个获取场景队友是不算自己的
	local sceneMemberNum = GetTeamSceneMemberCount(sceneId, selfId)
	for i = 0, sceneMemberNum - 1 do
		local memberId = GetTeamSceneMember(sceneId, selfId, i)
		SetQuestData(sceneId, memberId, MD_MBATTLE_SIGNSTATE[1], MD_MBATTLE_SIGNSTATE[2], MD_MBATTLE_SIGNSTATE[3], 0)
		x303100_g_curSignupTypeTbl[GetPlayerGUID(sceneId, memberId)] = 1
        
        --使用 Msg2Player 机制，原来的 LuaAllScenceM2Team 是使用 SendPacket_SingleMode 无法支持跨服多 GL 模式
        Msg2Player(sceneId, memberId, "您的队伍顺利的完成了【跨服战场】双人战场的报名,#R请勿离开本场景#G，以免无法接收到进入战场的邀请！", 8, 2)
        Msg2Player(sceneId, memberId, "您的队伍顺利的完成了【跨服战场】双人战场的报名,#R请勿离开本场景#G，以免无法接收到进入战场的邀请！", 8, 3)
		WriteLog(1, format("MP2BL:x303100_OnMSignupResult 1 SceneId=%d PlayerGUID=%u", sceneId, GetGUID(sceneId, memberId)))
	end
	
	--不要忘了自己
	SetQuestData(sceneId, selfId, MD_MBATTLE_SIGNSTATE[1], MD_MBATTLE_SIGNSTATE[2], MD_MBATTLE_SIGNSTATE[3], 0)
	x303100_g_curSignupTypeTbl[GetPlayerGUID(sceneId, selfId)] = 1
    Msg2Player(sceneId, selfId, "您的队伍顺利的完成了【跨服战场】双人战场的报名,#R请勿离开本场景#G，以免无法接收到进入战场的邀请！", 8, 2)
    Msg2Player(sceneId, selfId, "您的队伍顺利的完成了【跨服战场】双人战场的报名,#R请勿离开本场景#G，以免无法接收到进入战场的邀请！", 8, 3)
	WriteLog(1, format("MP2BL:x303100_OnMSignupResult 2 SceneId=%d PlayerGUID=%u", sceneId, GetGUID(sceneId, selfId)))
		
    return 1
end

---------------------------------------------------------------------------------------------------
--设置所有记录的2v2报名者报名签证并清除本次记录表
---------------------------------------------------------------------------------------------------
function x303100_Set2V2SignAndClean(sceneId)

	--本班次战场开始，给报名场景上的所有玩家添加签证，使其不进入就要被传走
	local humanCount = GetScenePlayerCount(sceneId)	
	for	i = 0, humanCount - 1 do
		local humanId = GetScenePlayerObjId(sceneId, i)

		--给所有报名双人战场的玩家（报完名没进去的）重新添加签证。这里判定了双人战场就可以避免和同场景的报名6人战场的分开。
		if x303100_g_curSignupTypeTbl[GetPlayerGUID(sceneId, humanId)] == 1 then
			if GetQuestData(sceneId, humanId, MD_MBATTLE_SIGNSTATE[1], MD_MBATTLE_SIGNSTATE[2], MD_MBATTLE_SIGNSTATE[3]) == 0 then
				SetQuestData(sceneId, humanId, MD_MBATTLE_SIGNSTATE[1], MD_MBATTLE_SIGNSTATE[2], MD_MBATTLE_SIGNSTATE[3], 1)
				SetQuestData(sceneId, humanId, MD_MBATTLE_SIGNTIME[1], MD_MBATTLE_SIGNTIME[2], MD_MBATTLE_SIGNTIME[3], MBATTLE_SIGNUP_SIGNTIME)
				WriteLog(1, format("MP2BL:x303100_Set2V2SignAndClean 1 SceneId=%d PlayerGUID=%u", sceneId, GetGUID(sceneId, humanId)))	
			end
		end  
	end

	--很重要，每次给所有记录表中的玩家添加签证后要清除该表，否则每次开场都将设置一些残留的不该设置的用户签证
	x303100_g_curSignupTypeTbl = {}
end

---------------------------------------------------------------------------------------------------
--玩家进入报名场景时的处理
---------------------------------------------------------------------------------------------------
function x303100_ProcMapPlayerNewConnectEnter(sceneId, selfId)

	--报名场景检测
	if GetSceneType(sceneId) ~= 8 then
		return
	end
	
	local signState = GetQuestData(sceneId, selfId, MD_MBATTLE_SIGNSTATE[1], MD_MBATTLE_SIGNSTATE[2], MD_MBATTLE_SIGNSTATE[3])
	local selfCountry = GetCurCountry(sceneId, selfId)
	
	--报名后下线再上线
	if signState == 0 then
	
		--已经错过了上次报名的场次，倒计时切走。要测出这种情况
	 	if MPVP2v2IsSignup(sceneId, selfId) == 0 then
			SetQuestData(sceneId, selfId, MD_MBATTLE_SIGNSTATE[1], MD_MBATTLE_SIGNSTATE[2], MD_MBATTLE_SIGNSTATE[3], 1)
			SetQuestData(sceneId, selfId, MD_MBATTLE_SIGNTIME[1], MD_MBATTLE_SIGNTIME[2], MD_MBATTLE_SIGNTIME[3], 10)
			WriteLog(1, format("MP2BL:x303100_ProcMapPlayerNewConnectEnter 1 SceneId=%d PlayerGUID=%u", sceneId, GetGUID(sceneId, selfId)))	
	 	end
	 	return
	end

	--没报名下线再上线
	
	local lastLogoutTime = GetLastLogoutTime(sceneId, selfId)
	local thisInterval = GetCurrentTime() - lastLogoutTime
	local signTime = GetQuestData(sceneId, selfId, MD_MBATTLE_SIGNTIME[1], MD_MBATTLE_SIGNTIME[2], MD_MBATTLE_SIGNTIME[3])

	--时间容错判定，防止测试时向前修改日期导致的 thisInterval 为负的情况
	if thisInterval > 0 then
		
		--如果离线的时间大于报名签证时间则将用户传送到对应王城不可以立即跳转，客户端换页 UI 将无法消除，使用定时器，倒计时 10 秒
		if thisInterval > signTime then
			SetQuestData(sceneId, selfId, MD_MBATTLE_SIGNTIME[1], MD_MBATTLE_SIGNTIME[2], MD_MBATTLE_SIGNTIME[3], 10)
			WriteLog(1, format("MP2BL:x303100_ProcMapPlayerNewConnectEnter 2 SceneId=%d PlayerGUID=%u Param1=%u Param2=%u", 
				sceneId, GetGUID(sceneId, selfId), thisInterval, signTime))
		end
	else
		WriteLog(2, format("MP2BL:x303100_ProcMapPlayerNewConnectEnter: get this thisInterval error for modify system time"))    		
	end
end

---------------------------------------------------------------------------------------------------
--报名场景定时器
---------------------------------------------------------------------------------------------------
function x303100_ProcTiming(sceneId, nowTime)

	local humanCount = GetScenePlayerCount(sceneId)	
	for	i = 0, humanCount - 1 do
		
		local humanId = GetScenePlayerObjId(sceneId, i)
		local signState = GetQuestData(sceneId, humanId, MD_MBATTLE_SIGNSTATE[1], MD_MBATTLE_SIGNSTATE[2], MD_MBATTLE_SIGNSTATE[3])
		local isBack = 0		
	 	
	 	--对有签证状态且没有进行过报名的玩家进行签证计时。排除报名后离开场景又回来的玩家！
		if signState == 1 and MPVP2v2IsSignup(sceneId, humanId) == 0 then

			--如果有报名签证则进行时长递减，必须判定是否为 0，否则在倒计时时用户断线，再次上线就是循环回 1024 的数
			local signTime = GetQuestData(sceneId, humanId, MD_MBATTLE_SIGNTIME[1], MD_MBATTLE_SIGNTIME[2], MD_MBATTLE_SIGNTIME[3])
			if signTime ~= 0 then
				SetQuestData(sceneId, humanId, MD_MBATTLE_SIGNTIME[1], MD_MBATTLE_SIGNTIME[2], MD_MBATTLE_SIGNTIME[3], signTime - 1)
				
				--到时警告
				if signTime > 0 and signTime <= 10 then
					Msg2Player(sceneId, humanId, format("由于您长时间没有报名将在%d秒后离开报名场景！", signTime), 8, 3)
				end
				
				--递减时间到要切走
				if signTime - 1 == 0 then
					isBack = 1
				end		
			end	
		end

		if isBack == 1 then
			local humanCountry = GetCurCountry(sceneId, humanId)
			NewWorld
				(
				sceneId, 
				humanId, 
				x303100_g_BackSceneIdAry[humanCountry + 1], 
				x303100_g_BackPosAry[humanCountry + 1][1],
				x303100_g_BackPosAry[humanCountry + 1][2], 
		 		x303100_g_ScriptId
		 		)
			WriteLog(1, format("MP2BL:x303100_ProcTiming 1 SceneId=%d PlayerGUID=%u", sceneId, GetGUID(sceneId, humanId)))
		 end
	end
end

----------------------------------------------------------------------------------------------
--检测接受条件
----------------------------------------------------------------------------------------------
function x303100_ProcAcceptCheck( sceneId, selfId, NPCId )
    return 1
end
----------------------------------------------------------------------------------------------
--接受
----------------------------------------------------------------------------------------------
function x303100_ProcAccept( sceneId, selfId )
end
----------------------------------------------------------------------------------------------
--放弃
----------------------------------------------------------------------------------------------
function x303100_ProcQuestAbandon( sceneId, selfId, missionId )
end
----------------------------------------------------------------------------------------------
--继续
----------------------------------------------------------------------------------------------
function x303100_OnContinue( sceneId, selfId, targetId )
end
----------------------------------------------------------------------------------------------
--检测是否可以提交
----------------------------------------------------------------------------------------------
function x303100_CheckSubmit( sceneId, selfId )
end
----------------------------------------------------------------------------------------------
--提交
----------------------------------------------------------------------------------------------
function x303100_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, missionId )
end
----------------------------------------------------------------------------------------------
--杀死怪物或玩家
----------------------------------------------------------------------------------------------
function x303100_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, missionId )
end

----------------------------------------------------------------------------------------------
--进入区域事件
----------------------------------------------------------------------------------------------
function x303100_ProcAreaEntered( sceneId, selfId, zoneId, missionId )
end

----------------------------------------------------------------------------------------------
--道具改变
----------------------------------------------------------------------------------------------
function x303100_ProcQuestItemChanged( sceneId, selfId, itemdataId, missionId )
end
