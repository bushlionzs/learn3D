--##############################################
--##跨服 2v2 进入报名场景脚本 by rj 2010-9-24 ##
--##############################################

x303102_g_ScriptId          		= 303102
x303102_g_MissionName       		= "【双人战场】进入报名场景"
x303102_g_MMapServerId       		= 7															--跨服 MapServer id
x303102_g_MinLevelLimit       		= 40															--最小级别限制
x303102_g_MaxEnterLimit       		= 2000															--跨服 MapServer 最大进入限制
x303102_g_SignupSceneIdAry		    = {519, 530, 531, 532}												--四国双人战场报名场景 id
x303102_g_EnterPosAry		     	= {																--四国双人战场进入坐标
[1] = {{54, 52}, {204, 53}, {205, 203}, {55, 203}, {130, 128}},
[2] = {{54, 52}, {204, 53}, {205, 203}, {55, 203}, {130, 128}},
[3] = {{54, 52}, {204, 53}, {205, 203}, {55, 203}, {130, 128}},
[4] = {{54, 52}, {204, 53}, {205, 203}, {55, 203}, {130, 128}},
}	
x303102_g_GameId = 1061
----------------------------------------------------------------------------------------------
--枚举
----------------------------------------------------------------------------------------------
function x303102_ProcEnumEvent(sceneId, selfId, targetId, missionId)

    AddQuestNumText(sceneId, x303102_g_ScriptId, x303102_g_MissionName, 3)
end

----------------------------------------------------------------------------------------------
--默认事件
----------------------------------------------------------------------------------------------
function x303102_ProcEventEntry(sceneId, selfId, targetId, scriptId, idExt)

	--合服开关
    if GetMergeDBToggle() == 1 then
        return
    end
    
  	--升级数据库开关
	if GetUpdateDBBeforeToggle() == 1 then
		return
	end
        
   	BeginQuestEvent(sceneId)
	AddQuestText(sceneId, "#Y【双人战场】#W\n\t那里可是群英荟萃、英雄云集的地方，你确定要进入吗？")
 	EndQuestEvent()
	DispatchQuestInfo(sceneId, selfId, targetId, x303102_g_ScriptId, -1)
    return
end

----------------------------------------------------------------------------------------------
--检测接受条件
----------------------------------------------------------------------------------------------
function x303102_ProcAcceptCheck(sceneId, selfId, npcId)
	--判断玩法开关
	if GetGameOpenById(x303102_g_GameId) ~= 1 then
		Msg2Player(sceneId,selfId,"活动没有开启，敬请期待！",8, 3)	
		return
	end
	--是否开启时间
	if GetWeek() == 1 or GetWeek() == 4 then
		if GetMinOfDay() < 1195 or GetMinOfDay() >= 1260 then	
			Msg2Player(sceneId, selfId, "跨服双人战场报名还没有开始！", 8, 3)		
			return
		end	
	elseif GetWeek() == 0 then
		if GetMinOfDay() < 775 or GetMinOfDay() >= 900 then	
			Msg2Player(sceneId, selfId, "跨服双人战场报名还没有开始！", 8, 3)		
			return
		end
	else 
		Msg2Player(sceneId, selfId, "跨服双人战场报名还没有开始！", 8, 3)		
		return
	end
	
  	--必须有队伍
	if HasTeam(sceneId, selfId) ~= 1 then
		Msg2Player(sceneId, selfId, "必须有队伍才能申请参加跨服双人战场！", 8, 3)
        return
	end
	
  	--非队长
	if IsTeamLeader(sceneId, selfId) ~= 1 then
		Msg2Player(sceneId, selfId, "只有队长才能申请参加跨服双人战场！", 8, 3)
        return
	end
	
	--队伍人数必须为 2
	if GetTeamSize(sceneId, selfId) ~= 2 then
		Msg2Player(sceneId, selfId, "只有两人的队伍可以申请！", 8, 3)
      return
	end
	
	local nearCount = GetNearTeamCount(sceneId, selfId)
	
	--附近队员数必须为 2
	if nearCount ~= 2 then
		Msg2Player(sceneId, selfId, "附近的人数不足两人！", 8, 3)
        return
	end
	
	for i = 0, nearCount - 1 do

		local memberId = GetNearTeamMember(sceneId, selfId, i)
		
		local ret, msg = x303102_EnterSignupSceneCheck(sceneId, memberId)
       	if ret == 0 then
       		Msg2Player(sceneId, selfId, msg, 8, 3)
		 	WriteLog(1, format("MP2BL:x303102_ProcAcceptCheck 1 SceneId=%d PlayerGUID=%u Param1=%u Param2=%u Param3=%s", 
		 		sceneId, GetGUID(sceneId, selfId), GetGUID(sceneId, memberId), npcId, msg))
       		return
       	end
    end
	
	--检测跨服战场服务器人数是否超过限制
	local userNum = GetMapServerCurUserNum(x303102_g_MMapServerId)
	if userNum + 2 > x303102_g_MaxEnterLimit then
    	Msg2Player(sceneId, selfId, "跨服战场服务器人数已满，请稍后进入！", 8, 3)
	 	WriteLog(1, format("MP2BL:x303102_ProcAcceptCheck 2 SceneId=%d PlayerGUID=%u", sceneId, GetGUID(sceneId, selfId)))
   	 	return       
   	end 
	
	local rand = random(1, 5)
		
	for i = 0, nearCount - 1 do
		
		local memberId = GetNearTeamMember(sceneId, selfId, i)
		
		--开启报名签证并记录签证时间
		SetQuestData(sceneId, memberId, MD_MBATTLE_SIGNSTATE[1], MD_MBATTLE_SIGNSTATE[2], MD_MBATTLE_SIGNSTATE[3], 1)
		SetQuestData(sceneId, memberId, MD_MBATTLE_SIGNTIME[1], MD_MBATTLE_SIGNTIME[2], MD_MBATTLE_SIGNTIME[3], MBATTLE_SIGNUP_SIGNTIME)
		
		local nPlayerLevel = GetLevel(sceneId, memberId)
		
		if nPlayerLevel >= 65 and nPlayerLevel < 85 then
			SendSpecificImpactToUnit(sceneId, memberId, memberId, memberId, 7717, 0)
		elseif nPlayerLevel >= 85 then
			SendSpecificImpactToUnit(sceneId, memberId, memberId, memberId, 7718, 0)
			DispelSpecificImpact(sceneId, memberId, 7717, 1)
		end
		
		--根据不同国家导向到不同的报名地图
		local memberCountry = GetCurCountry(sceneId, memberId)
		NewWorld
			(
			sceneId, 
			memberId, 
			x303102_g_SignupSceneIdAry[memberCountry + 1], 
			x303102_g_EnterPosAry[memberCountry + 1][rand][1],
			x303102_g_EnterPosAry[memberCountry + 1][rand][2], 
	 		x303102_g_ScriptId
	 		)

	 	WriteLog(1, format("MP2BL:x303102_ProcAcceptCheck 3 SceneId=%d PlayerGUID=%u Param1=%d", 
	 		sceneId, GetGUID(sceneId, memberId), x303102_g_SignupSceneIdAry[memberCountry + 1]))	
	end
end

function x303102_EnterSignupSceneCheck(sceneId, selfId)

	if GetLevel(sceneId, selfId) < x303102_g_MinLevelLimit then
		return 0, format("队伍中有成员没有达到%d级，不能进入报名场景", x303102_g_MinLevelLimit)
	end

	if GetPKMode(sceneId, selfId) ~= 0 then
    	return 0, "队伍中有成员处于PK模式下，不能进入报名场景" 
   	end 

	if GetBusId(sceneId, selfId) ~= -1 then
		return 0, "队伍中有成员处于护送状态，不能进入报名场景"
	end
    
    if IsHideName(sceneId, selfId) > 0 then
    	return 0, "队伍中有成员处于蒙面状态下,不能进入报名场景"
    end
    
    if sceneId == PK_PUNISH_PRISON_SCENE_ID then
    	return 0,"队伍中有成员在监狱里，不能进入报名场景"
    end

    if IsHaveSpecificImpact(sceneId, selfId, 7536) ~= 0 then
        return 0, "队伍中有成员处于暴龙大作战期间，不能进入报名场景"
    end

    if IsHaveSpecificImpact(sceneId, selfId, 7537) ~= 0 then
        return 0, "队伍中有成员处于暴龙大作战期间，不能进入报名场景"
    end
    
    if IsHaveSpecificImpact(sceneId, selfId, 7702) ~= 0 then
        return 0, "队伍中有成员处在夺旗状态下，不能进入报名场景"
    end

    if IsPlayerStateNormal(sceneId, selfId) == 0 then
        return 0, "队伍中有成员状态异常，不能进入报名场景"
    end
    
    if IsPlayerMutexState(sceneId, selfId, PLAYER_STATE_TONGQUBUFF) == 1 then
        return 0, "队伍中有成员处于童趣变身状态，不能进入报名场景"
    end

    if IsPlayerMutexState(sceneId, selfId, PLAYER_STATE_TIESAN) == 1 then
        return 0, "队伍中有成员处于铁人三项变身状态，不能进入报名场景"
    end

    if IsPlayerMutexState(sceneId, selfId, PLAYER_STATE_MENTALGAME) == 1 then
        return 0, "队伍中有成员处于答题状态，不能进入报名场景"
    end

    if IsPlayerMutexState(sceneId, selfId, PLAYER_STATE_STALL) == 1 then
        return 0, "队伍中有成员处于摆摊状态，不能进入报名场景"
    end

    if IsPlayerMutexState(sceneId, selfId, PLAYER_STATE_DIE) == 1 then
        return 0, "队伍中有成员处于死亡状态，不能进入报名场景"
    end

    if IsPlayerMutexState(sceneId, selfId, PLAYER_STATE_CRASHBOX) == 1 then
        return 0, "队伍中有成员处于运镖状态，不能进入报名场景"
    end

    if IsPlayerMutexState(sceneId,selfId,PLAYER_STATE_AUTOPLAY) == 1 then
        return 0, "队伍中有成员处于挂机状态，不能进入报名场景"
    end

    if IsPlayerMutexState(sceneId, selfId, PLAYER_STATE_SUBTRAIN) == 1 then
        return 0, "队伍中有成员处于代练状态，不能进入报名场景"
    end

    if IsPlayerMutexState(sceneId, selfId, PLAYER_STATE_BUS) == 1 then
        return 0, "队伍中有成员处于BUS状态，不能进入报名场景"
    end

    if IsPlayerMutexState(sceneId, selfId, PLAYER_STATE_PKMODE) == 1 then
        return 0, "队伍中有成员PK值过高或处于狂暴模式，不能进入报名场景"
    end

    return 1
end

----------------------------------------------------------------------------------------------
--接受
----------------------------------------------------------------------------------------------
function x303102_ProcAccept( sceneId, selfId )
end
----------------------------------------------------------------------------------------------
--放弃
----------------------------------------------------------------------------------------------
function x303102_ProcQuestAbandon( sceneId, selfId, missionId )
end
----------------------------------------------------------------------------------------------
--继续
----------------------------------------------------------------------------------------------
function x303102_OnContinue( sceneId, selfId, targetId )
end
----------------------------------------------------------------------------------------------
--检测是否可以提交
----------------------------------------------------------------------------------------------
function x303102_CheckSubmit( sceneId, selfId )
end
----------------------------------------------------------------------------------------------
--提交
----------------------------------------------------------------------------------------------
function x303102_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, missionId )
end
----------------------------------------------------------------------------------------------
--杀死怪物或玩家
----------------------------------------------------------------------------------------------
function x303102_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, missionId )
end

----------------------------------------------------------------------------------------------
--进入区域事件
----------------------------------------------------------------------------------------------
function x303102_ProcAreaEntered( sceneId, selfId, zoneId, missionId )
end

----------------------------------------------------------------------------------------------
--道具改变
----------------------------------------------------------------------------------------------
function x303102_ProcQuestItemChanged( sceneId, selfId, itemdataId, missionId )
end
