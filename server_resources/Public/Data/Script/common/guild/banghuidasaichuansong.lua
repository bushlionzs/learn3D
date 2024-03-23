
--帮会升级
--MisDescBegin
--脚本号
x300641_g_ScriptId = 300641


--任务文本描述
x300641_g_MissionName="帮会战场传送"
x300641_g_CountryID = 3
--MisDescEnd


function x300641_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

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
    if GetBattleSceneToggle( BATTLESCENE_TYPE_GUILDBATTLE ) == 0 then
        return
    end

	local guild = GetGuildID(sceneId, selfId)
	if guild == -1 then
		return 1
	end

    if GetGuildBattleStatus(sceneId) ~= STATE_GUILD_BATTLE_BATTLE then
        return 1
    end

	AddQuestNumText(sceneId,x300641_g_ScriptId,x300641_g_MissionName,3);
end


function x300641_ProcEventEntry( sceneId, selfId, targetId ,idScript,idExt )

--	if GetGuildBattleStatus(sceneId) ~= STATE_GUILD_BATTLE_BATTLE then
-- 		BeginQuestEvent(sceneId)
--		AddQuestText(sceneId, "战场未开放");
--		EndQuestEvent(sceneId)
--		DispatchQuestTips(sceneId,selfId)
--		return
--	end

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
    if GetBattleSceneToggle( BATTLESCENE_TYPE_GUILDBATTLE ) == 0 then
        return
    end

    local state,msg = x300641_CheckPlayerState( sceneId,selfId )
    if state == 1 then
        
        BeginQuestEvent(sceneId)
        AddQuestText( sceneId, msg );
        EndQuestEvent(sceneId)
        DispatchQuestEventList(sceneId,selfId,targetId)
        return
    end

    GuildBattleAskEnterScene(sceneId, selfId)

    return 1
end

function x300641_OnEnterSceneError( sceneId,selfId,nError )
    

    if nError == 1 then
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "很抱歉，活动还没有开始！");
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)

        return 0

    elseif nError == 2 then
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "很抱歉，您没有帮会！");
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)

    elseif nError == 3 then
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "很抱歉，您所在的帮会还没有报名！");
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)

        return 0

    elseif nError == 4 then
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "很抱歉，帮会战还没有开始！");
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)

        return 0

    elseif nError == 5 then

        
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "很抱歉，您所在的帮会在此次帮会战中轮空！");
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)

        return 0

    elseif nError == 6 then
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "很抱歉，您的帮会信息区配不正确！");
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)

        return 0

    elseif nError == 7 then
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "很抱歉，您不是帮主！");
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)

        return 0

    elseif nError == 8 then
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "很抱歉，您的帮会成员不足10人！");
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)

        return 0

    elseif nError == 9 then
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "很抱歉，已经受理过您的帮战申请请求！");
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)

        return 0

    elseif nError == 10 then
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "很抱歉，帮会战报名已达上限！");
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)

        return 0
    elseif nError == 11 then
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "很抱歉，帮会战已经结束！");
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)

        return 0

    else
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "很抱歉，未知错误！");
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)

        return 0

    end
end

function x300641_CheckPlayerState( sceneId,selfId )
    

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

    local IsHaveFlag = IsHaveSpecificImpact(sceneId, selfId,7702 )
    if IsHaveFlag ~= 0 then
        ErrorMsg = "在夺旗状态下，不能进入战场"
        return 1,ErrorMsg
    end

    return 0

end


--********************
--检测接受条件
--**********************************
function x300641_ProcAcceptCheck( sceneId, selfId, NPCId )
		return 1
end

--**********************************
--接受
--**********************************
function x300641_ProcAccept( sceneId, selfId )

end

--**********************************
--放弃
--**********************************
function x300641_ProcQuestAbandon( sceneId, selfId, MissionId )
end

--**********************************
--继续
--**********************************
function x300641_OnContinue( sceneId, selfId, targetId )
end

--**********************************
--检测是否可以提交
--**********************************
function x300641_CheckSubmit( sceneId, selfId )
end

--**********************************
--提交
--**********************************
function x300641_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end

