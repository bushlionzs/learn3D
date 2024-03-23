
--帮战申请

--MisDescBegin
x300642_g_ScriptId          = 300642
x300642_g_Leader_Index      = 5
x300642_g_MissionName       ="申请帮会战场"
--MisDescEnd

----------------------------------------------------------------------------------------------
--枚举
----------------------------------------------------------------------------------------------
function x300642_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

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

    local pos = GetGuildOfficial(sceneId, selfId)
	if pos == x300642_g_Leader_Index and GetGuildBattleStatus(sceneId) == STATE_GUILD_BATTLE_SIGNUP then
        
        AddQuestNumText(sceneId,x300642_g_ScriptId,x300642_g_MissionName,3);

    end
end

----------------------------------------------------------------------------------------------
--默认事件
----------------------------------------------------------------------------------------------
function x300642_ProcEventEntry( sceneId, selfId, targetId,scriptId,idExt )

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

    if idExt == 0 then
        
        --查询结果
        local nGuildId = GetGuildID( sceneId,selfId )
        QueryGuildBattleSignupState( sceneId,selfId,nGuildId,targetId )


    elseif idExt == 1 then

        
        local nGuildId = GetGuildID( sceneId,selfId )
        if nGuildId < 0 then
            return
        end
        
        --是否是帮主
        local pos = GetGuildOfficial(sceneId, selfId)
        if pos ~= x300642_g_Leader_Index then
            BeginQuestEvent(sceneId)
            AddQuestText(sceneId, "申请失败，很抱歉，您还不是帮主无法申请帮会战。");
            EndQuestEvent(sceneId)
            DispatchQuestEventList(sceneId,selfId,targetId)
            return
        end



        if GetGuildBattleStatus(sceneId) ~= STATE_GUILD_BATTLE_SIGNUP then
            BeginQuestEvent(sceneId)
            AddQuestText(sceneId, "帮会战的申请时间为每周二和周五的17：00~~18：30");
            EndQuestEvent(sceneId)
            DispatchQuestTips(sceneId,selfId)
            return
        end

        --以上都通过，发送申请
        SignupGuildBattle( sceneId,selfId,nGuildId,targetId )

    end
    return 1

end

function x300642_OnQueryBattleSignup( sceneId,selfId,result,targetId )


    if result == 1 then
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "很抱歉，活动还没有开始！");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)

        return 0

    elseif result == 2 then
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "您没有帮会！");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)

    elseif result == 3 then
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "您所在的帮会还没有报名！");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)

        return 0

    elseif result == 4 then
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "帮会战还没有开始！");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)

        return 0

    elseif result == 5 then
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "很抱歉，您所在的帮会在此次帮会战中轮空！");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)

        return 0

    elseif result == 6 then
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "很抱歉，您的帮会信息区配不正确！");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)

        return 0

    elseif result == 7 then
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "很抱歉，您不是帮主！");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)

        return 0

    elseif result == 8 then
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "很抱歉，您的帮会成员不足10人！");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)

        return 0

    elseif result == 9 then
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "很抱歉，已经受理过您的帮战申请请求！");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)

        return 0

    elseif result == 10 then
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "很抱歉，帮会战报名已达上限！");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)

        return 0
    end


    BeginQuestEvent(sceneId)
    AddQuestText(sceneId, "您是否要报名今天的帮会战？");
    AddQuestNumText(sceneId,x300642_g_ScriptId,"确定..",3,1);
    EndQuestEvent(sceneId)
    DispatchQuestEventList(sceneId,selfId,targetId)

    return 1

end

function x300642_OnBattleSignup( sceneId,selfId,result,targetId )
    
    if result == 1 then
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "很抱歉，活动还没有开始！");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)

        return 0

    elseif result == 2 then
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "很抱歉，您没有帮会！");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)

    elseif result == 3 then
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "很抱歉，您所在的帮会还没有报名！");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)

        return 0

    elseif result == 4 then
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "很抱歉，帮会战还没有开始！");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)

        return 0

    elseif result == 5 then
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "很抱歉，您所在的帮会在此次帮会战中轮空！");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)

        return 0

    elseif result == 6 then
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "很抱歉，您的帮会信息区配不正确！");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)

        return 0

    elseif result == 7 then
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "很抱歉，您不是帮主！");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)

        return 0

    elseif result == 8 then
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "很抱歉，您的帮会成员不足10人！");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)

        return 0

    elseif result == 9 then
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "很抱歉，已经受理过您的帮战申请请求！");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)

        return 0

    elseif result == 10 then
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "很抱歉，帮会战报名已达上限！");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)

        return 0
    end

    BeginQuestEvent(sceneId)
    AddQuestText(sceneId, "#G您的申请已经记录，#R20点#G正式开始！");
	EndQuestEvent(sceneId)
	DispatchQuestEventList(sceneId,selfId,targetId)

    local str = "#G帮主申请了帮会战，请做好准备，#R20点#G正式开始！"
    local nGuildID = GetGuildID(sceneId,selfId)
    LuaAllScenceM2Guild(sceneId, str, nGuildID, 2, 1)
    LuaAllScenceM2Guild(sceneId, str, nGuildID, 3, 1)

    return 1

end


----------------------------------------------------------------------------------------------
--检测接受条件
----------------------------------------------------------------------------------------------
function x300642_ProcAcceptCheck( sceneId, selfId, NPCId )
    return 1
end

----------------------------------------------------------------------------------------------
--接受
----------------------------------------------------------------------------------------------
function x300642_ProcAccept( sceneId, selfId )

    

	--GetGuildQuestData(sceneId, selfId, GD_GUILD_INDEX_BATTLE_SINGUP, x300642_g_ScriptId,-1,"OnReturn")
end

----------------------------------------------------------------------------------------------
--检查是否已经申请
----------------------------------------------------------------------------------------------
function x300642_OnReturn(sceneId, selfId,MissionData,MissionId,targetId)

--	if MissionData >= 0 then
-- 		BeginQuestEvent(sceneId)
--		AddQuestText(sceneId, "#G您的申请已经记录，#R20点#G正式开始！");
--		EndQuestEvent(sceneId)
--		DispatchQuestEventList(sceneId,selfId,targetId)
--	else
--
--		local guild = GetGuildID(sceneId, selfId)
--		SignupGuildBattle(sceneId,selfId,guild)       	--报名
--
--		--请求报名结果
--		GetGuildQuestData(sceneId, selfId, GD_GUILD_INDEX_BATTL_SINGUP_RESULT, x300642_g_ScriptId,-1,"OnReturn2")
--
--  	end

end

----------------------------------------------------------------------------------------------
--申请结果
----------------------------------------------------------------------------------------------
function x300642_OnReturn2(sceneId, selfId,MissionData,MissionId,targetId)

	if MissionData == 1 then    	--报名成功
		local str = "#G帮主申请了帮会战，请做好准备，#R20点#G正式开始！"
        local nGuildID = GetGuildID(sceneId,selfId)
        LuaAllScenceM2Guild(sceneId, str, nGuildID, 2, 1)
        LuaAllScenceM2Guild(sceneId, str, nGuildID, 3, 1)

        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "您申请了帮会战，请做好准备，20点正式开始！");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)

	elseif MissionData == 0 then
  	 	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "您的帮会不存在");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)
	elseif MissionData == -2 then
   	 	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "帮会战报名数已达上限！");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)
	elseif MissionData == -3 then
   	 	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "您的帮会人数太少，报名失败。");
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
	elseif MissionData == -4 then
 		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "您已经报过名了");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)
	end

end

----------------------------------------------------------------------------------------------
--放弃
----------------------------------------------------------------------------------------------
function x300642_ProcQuestAbandon( sceneId, selfId, MissionId )
end

----------------------------------------------------------------------------------------------
--继续
----------------------------------------------------------------------------------------------
function x300642_OnContinue( sceneId, selfId, targetId )
end

----------------------------------------------------------------------------------------------
--检测是否可以提交
----------------------------------------------------------------------------------------------
function x300642_CheckSubmit( sceneId, selfId )
end

----------------------------------------------------------------------------------------------
--提交
----------------------------------------------------------------------------------------------
function x300642_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end

----------------------------------------------------------------------------------------------
--杀死怪物或玩家
----------------------------------------------------------------------------------------------
function x300642_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end

----------------------------------------------------------------------------------------------
--进入区域事件
----------------------------------------------------------------------------------------------
function x300642_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

----------------------------------------------------------------------------------------------
--道具改变
----------------------------------------------------------------------------------------------
function x300642_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
