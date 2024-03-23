
x303000_g_ScriptId          		= 303000
x303000_g_Leader_Index      		= 5
x303000_g_MissionName       		="【战场】双人战场申请"

----------------------------------------------------------------------------------------------
--枚举
----------------------------------------------------------------------------------------------
function x303000_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

	--必须对场景校验
	if sceneId ~= 0 and sceneId ~= 50 and sceneId ~= 150 and sceneId ~= 250 and sceneId ~= 350 then
		return
	end

	--合服开关
    if GetMergeDBToggle() == 1 then
        return
    end
    
    --升级数据库开关
		local UpdateDBflag = GetUpdateDBBeforeToggle()
		if UpdateDBflag==1 then
			return
		end

    --战场自己的开关
    
    
    --只有在报名时间段内才开启
    if CallScriptFunction(303001,"IsBattleSignup",sceneId) == 1 then
    	AddQuestNumText(sceneId,x303000_g_ScriptId,x303000_g_MissionName,3);
    end
end

----------------------------------------------------------------------------------------------
--默认事件
----------------------------------------------------------------------------------------------
function x303000_ProcEventEntry( sceneId, selfId, targetId,scriptId,idExt )

	--必须对场景校验
	if sceneId ~= 0 and sceneId ~= 50 and sceneId ~= 150 and sceneId ~= 250 and sceneId ~= 350  then
		return
	end

	--合服开关
    if GetMergeDBToggle() == 1 then
        return
    end
    
    --升级数据库开关
		local UpdateDBflag = GetUpdateDBBeforeToggle()
		if UpdateDBflag==1 then
			return
		end
    
    if CallScriptFunction(303001,"IsBattleSignup",sceneId) ~= 1 then
    	BeginQuestEvent(sceneId)
        AddQuestText(sceneId, "\t双人战场报名还没有开始！");
        EndQuestEvent(sceneId)
        DispatchQuestEventList(sceneId,selfId,targetId)
    	return
    end
    
    --测试服开关
    --if GetTestServerToggle() == 0 then
    --    return
    --end

    --战场自己的开关

    if idExt == 0 then
    	
    	--非队长
    	if IsTeamLeader(sceneId, selfId) ~= 1 then
    		BeginQuestEvent(sceneId)
            AddQuestText(sceneId, "\t只有队长才能申请参加双人战场。");
            EndQuestEvent(sceneId)
            DispatchQuestEventList(sceneId,selfId,targetId)
            return
    	end
    	
    	--还没有开始
    	if CallScriptFunction(303001,"IsBattleSignup",sceneId) ~= 1 then
    		BeginQuestEvent(sceneId)
            AddQuestText(sceneId, "\t双人战场报名还没有开始！");
            EndQuestEvent(sceneId)
            DispatchQuestEventList(sceneId,selfId,targetId)
            return
    	end
    	
        
        --查询结果
        PVP2v2SignupState( sceneId,selfId ,targetId)


    elseif idExt == 1 then

        
        --非队长
    	if IsTeamLeader(sceneId, selfId) ~= 1 then
    		BeginQuestEvent(sceneId)
            AddQuestText(sceneId, "\t只有队长才能申请参加双人战场。");
            EndQuestEvent(sceneId)
            DispatchQuestEventList(sceneId,selfId,targetId)
            return
    	end
    	
    	--还没有开始
    	if CallScriptFunction(303001,"IsBattleSignup",sceneId) ~= 1 then
    		BeginQuestEvent(sceneId)
            AddQuestText(sceneId, "\t双人战场报名还没有开始！");
            EndQuestEvent(sceneId)
            DispatchQuestEventList(sceneId,selfId,targetId)
            return
    	end

        --以上都通过，发送申请
        PVP2v2Signup( sceneId,selfId,targetId)
			
	end
    return 1

end

----------------------------------------------------------------------------------------------
--查询报名结果
----------------------------------------------------------------------------------------------
function x303000_OnQuerySignupResult( sceneId,selfId,result,targetId )


    if result == 1 then
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "\t很抱歉，双人战场还没有开始！");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)

        return 0

    elseif result == 2 then
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "\t您没有队伍！");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)

    elseif result == 3 then
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "\t您所在队伍人数必须为2人才能报名双人战场。");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)

        return 0

    elseif result == 4 then
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "\t您所在队伍的玩家必须都在线。");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)

        return 0

    elseif result == 5 then
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "\t您已经报过名了！");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)

        return 0

    elseif result == 6 then
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "\t您的队友已经报过名了！");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)

        return 0

    elseif result == 7 then
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "\t这次的双人战场报名已经满了，请等候下场战斗。");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)

        return 0
    elseif result == 8 then
    	
    	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "\t很抱歉，您的等级不足60级！");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)
		
		return 0
    elseif result == 9 then
    	
    	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "\t很抱歉，您的队友的等级必须在60级以上！");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)
		
		return 0
    end


    BeginQuestEvent(sceneId)
    AddQuestText(sceneId, "\t您是否要报名参加【战场】双人战场？");
    AddQuestNumText(sceneId,x303000_g_ScriptId,"确定",3,1);
    EndQuestEvent(sceneId)
    DispatchQuestEventList(sceneId,selfId,targetId)

    return 1

end

----------------------------------------------------------------------------------------------
--报名结果
----------------------------------------------------------------------------------------------
function x303000_OnSignupResult( sceneId,selfId,result,targetId )
    
    if result == 1 then
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "\t很抱歉，双人战场还没有开始！");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)

        return 0

    elseif result == 2 then
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "\t您没有队伍！");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)

    elseif result == 3 then
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "\t您所在队伍人数必须为2人才能报名双人战场。");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)

        return 0

    elseif result == 4 then
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "\t您所在队伍的玩家必须都在线。");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)

        return 0

    elseif result == 5 then
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "\t您已经报过名了！");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)

        return 0

    elseif result == 6 then
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "\t您的队友已经报过名了！");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)

        return 0

    elseif result == 7 then
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "\t这次的双人战场报名已经满了，请等候下场战斗。");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)

        return 0
    elseif result == 8 then
    	
    	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "\t很抱歉，您的等级不足60级！");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)
		
		return 0
    elseif result == 9 then
    	
    	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "\t很抱歉，您的队友的等级必须在60级以上！");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)
		
		return 0
		
    end

    BeginQuestEvent(sceneId)
    AddQuestText(sceneId, "\t#G您成功的申请了【战场】双人战场，请等待比赛的开始！");
	EndQuestEvent(sceneId)
	DispatchQuestEventList(sceneId,selfId,targetId)
	
	local nTeamId = GetTeamId( sceneId,selfId)
	if nTeamId >= 0 then
		LuaAllScenceM2Team(sceneId,"您的队伍顺利的完成了【战场】双人战场的报名！",nTeamId,2,1)
		LuaAllScenceM2Team(sceneId,"您的队伍顺利的完成了【战场】双人战场的报名！",nTeamId,3,1)		
	end

    return 1

end


----------------------------------------------------------------------------------------------
--检测接受条件
----------------------------------------------------------------------------------------------
function x303000_ProcAcceptCheck( sceneId, selfId, NPCId )
    return 1
end

----------------------------------------------------------------------------------------------
--接受
----------------------------------------------------------------------------------------------
function x303000_ProcAccept( sceneId, selfId )
end

----------------------------------------------------------------------------------------------
--放弃
----------------------------------------------------------------------------------------------
function x303000_ProcQuestAbandon( sceneId, selfId, MissionId )
end

----------------------------------------------------------------------------------------------
--继续
----------------------------------------------------------------------------------------------
function x303000_OnContinue( sceneId, selfId, targetId )
end

----------------------------------------------------------------------------------------------
--检测是否可以提交
----------------------------------------------------------------------------------------------
function x303000_CheckSubmit( sceneId, selfId )
end

----------------------------------------------------------------------------------------------
--提交
----------------------------------------------------------------------------------------------
function x303000_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end

----------------------------------------------------------------------------------------------
--杀死怪物或玩家
----------------------------------------------------------------------------------------------
function x303000_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end

----------------------------------------------------------------------------------------------
--进入区域事件
----------------------------------------------------------------------------------------------
function x303000_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

----------------------------------------------------------------------------------------------
--道具改变
----------------------------------------------------------------------------------------------
function x303000_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
