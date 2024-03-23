x310100_g_ScriptId = 310100
x310100_g_MissionName="国王战场传送"

function x310100_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

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
    if GetBattleSceneToggle( BATTLESCENE_TYPE_KINGBATTLE ) == 0 then
        return
    end

	local guild = GetGuildID(sceneId, selfId)
	if guild == -1 then
		return 1
	end

    if GetKingBattleStatus(sceneId) ~= STATE_KING_BATTLE_BATTLE then
        return 1
    end

    if GetKingBattleEnterSceneFlag(sceneId) ~= 1 then
        return 1
    end

	AddQuestNumText(sceneId,x310100_g_ScriptId,x310100_g_MissionName,3);
end


function x310100_ProcEventEntry( sceneId, selfId, targetId )
    --国王战场状态
--	if GetKingBattleStatus(sceneId) ~= STATE_KING_BATTLE_BATTLE then
-- 		BeginQuestEvent(sceneId)
--		AddQuestText(sceneId, "战场未开放！");
--		EndQuestEvent(sceneId)
--		DispatchQuestTips(sceneId,selfId)
--		return 1
--	end
--
--    local guild = GetGuildID(sceneId, selfId)
--	if guild == -1 then
--        BeginQuestEvent(sceneId)
--		AddQuestText(sceneId, "没有帮会,不能申请进入战场！");
--		EndQuestEvent(sceneId)
--		DispatchQuestTips(sceneId,selfId)
--		return 1
--	end
--
--    if GetKingBattleEnterSceneFlag(sceneId) ~= 1 then
--        
--        BeginQuestEvent(sceneId)
--		AddQuestText(sceneId, "现在不能进入战场！");
--		EndQuestEvent(sceneId)
--		DispatchQuestTips(sceneId,selfId)
--        return 1
--    end

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
    if GetBattleSceneToggle( BATTLESCENE_TYPE_KINGBATTLE ) == 0 then
        return
    end

    --玩家状态
    local state,msg = x310100_CheckPlayerState( sceneId,selfId )
    if state == 1 then
        
        BeginQuestEvent(sceneId)
        AddQuestText( sceneId, msg );
        EndQuestEvent(sceneId)
        DispatchQuestTips(sceneId,selfId)
        return 1
    end

    BeginQuestEvent( sceneId )
    AddQuestText( sceneId, "确认要进入国王战场吗？" )
    EndQuestEvent( sceneId )
    DispatchQuestInfo( sceneId, selfId, targetId, x310100_g_ScriptId,-1 )

    return 1
end

function x310100_CheckPlayerState( sceneId,selfId )
    

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


--********************
--检测接受条件
--**********************************
function x310100_ProcAcceptCheck( sceneId, selfId, NPCId )
    return 1
end

--**********************************
--接受
--**********************************
function x310100_ProcAccept( sceneId, selfId )

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
    if GetBattleSceneToggle( BATTLESCENE_TYPE_KINGBATTLE ) == 0 then
        return
    end

    --国王战场状态
	if GetKingBattleStatus(sceneId) ~= STATE_KING_BATTLE_BATTLE then
		return
	end

    local guild = GetGuildID(sceneId, selfId)
	if guild == -1 then
		return
	end

    if GetKingBattleEnterSceneFlag(sceneId) ~= 1 then
        return
    end

    --玩家状态
    local state,msg = x310100_CheckPlayerState( sceneId,selfId )
    if state == 1 then
        return
    end

    --进入国王战场
    RequestEnterKingBattleScene(sceneId, selfId)
    
end

function x310100_AskEnterKingBattle( sceneId,selfId )

    --玩家状态
    local state,msg = x310100_CheckPlayerState( sceneId,selfId )
    if state == 1 then
        
        BeginQuestEvent(sceneId)
        AddQuestText( sceneId, msg );
        EndQuestEvent(sceneId)
        DispatchQuestTips(sceneId,selfId)
        
        return

    end

    --进入国王战场
    RequestEnterKingBattleScene(sceneId, selfId)

end

--**********************************
--放弃
--**********************************
function x310100_ProcQuestAbandon( sceneId, selfId, MissionId )
end

--**********************************
--继续
--**********************************
function x310100_OnContinue( sceneId, selfId, targetId )
end

--**********************************
--检测是否可以提交
--**********************************
function x310100_CheckSubmit( sceneId, selfId )
end

--**********************************
--提交
--**********************************
function x310100_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end

