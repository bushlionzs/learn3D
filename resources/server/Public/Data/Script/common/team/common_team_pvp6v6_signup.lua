
x303005_g_ScriptId          		= 303005
x303005_g_Leader_Index      		= 5
x303005_g_MissionName       		="【战场】六人战场申请"

----------------------------------------------------------------------------------------------
--枚举
----------------------------------------------------------------------------------------------
function x303005_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

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
    if CallScriptFunction(303006,"IsBattleSignup",sceneId) == 1 then
    	AddQuestNumText(sceneId,x303005_g_ScriptId,x303005_g_MissionName,3);
    end
end

----------------------------------------------------------------------------------------------
--默认事件
----------------------------------------------------------------------------------------------
function x303005_ProcEventEntry( sceneId, selfId, targetId,scriptId,idExt )

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
    
    if CallScriptFunction(303006,"IsBattleSignup",sceneId) ~= 1 then
    	BeginQuestEvent(sceneId)
        AddQuestText(sceneId, "\t【战场】六人战场报名还没有开始！");
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
    	if HasTeam(sceneId,selfId) == 1 and IsTeamLeader(sceneId, selfId) ~= 1 then
    		BeginQuestEvent(sceneId)
            AddQuestText(sceneId, "\t队伍模式下,只有队长才能申请参加【战场】六人战场。");
            EndQuestEvent(sceneId)
            DispatchQuestEventList(sceneId,selfId,targetId)
            return
    	end
    	
    	--还没有开始
    	if CallScriptFunction(303006,"IsBattleSignup",sceneId) ~= 1 then
    		BeginQuestEvent(sceneId)
            AddQuestText(sceneId, "\t【战场】六人战场报名还没有开始！");
            EndQuestEvent(sceneId)
            DispatchQuestEventList(sceneId,selfId,targetId)
            return
    	end
    	
        
        --查询结果
        PVP6v6SignupState( sceneId,selfId ,targetId)


    elseif idExt == 1 then

        
        --非队长
    	if HasTeam(sceneId,selfId) == 1 and IsTeamLeader(sceneId, selfId) ~= 1 then
    		BeginQuestEvent(sceneId)
            AddQuestText(sceneId, "\t队伍模式中,只有队长才能申请参加【战场】六人战场。");
            EndQuestEvent(sceneId)
            DispatchQuestEventList(sceneId,selfId,targetId)
            return
    	end
    	
    	--还没有开始
    	if CallScriptFunction(303006,"IsBattleSignup",sceneId) ~= 1 then
    		BeginQuestEvent(sceneId)
            AddQuestText(sceneId, "\t【战场】六人战场报名还没有开始！");
            EndQuestEvent(sceneId)
            DispatchQuestEventList(sceneId,selfId,targetId)
            return
    	end

        --以上都通过，发送申请
        PVP6v6Signup( sceneId,selfId,targetId)
			
	end
    return 1

end

----------------------------------------------------------------------------------------------
--查询报名结果
----------------------------------------------------------------------------------------------
function x303005_OnQuerySignupResult( sceneId,selfId,result,targetId )


    if result == 1 then
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "\t很抱歉，【战场】六人战场还没有开始！");
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
		AddQuestText(sceneId, "\t队伍模式下,您所在队伍人数必须为3人以上才能报名【战场】六人战场。");
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
		AddQuestText(sceneId, "\t这次的【战场】六人战场报名已经满了，请等候下场战斗。");
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
    AddQuestText(sceneId, "\t您是否要报名参加【战场】六人战场？");
    AddQuestNumText(sceneId,x303005_g_ScriptId,"确定",3,1);
    EndQuestEvent(sceneId)
    DispatchQuestEventList(sceneId,selfId,targetId)

    return 1

end

----------------------------------------------------------------------------------------------
--报名结果
----------------------------------------------------------------------------------------------
function x303005_OnSignupResult( sceneId,selfId,result,targetId )
    
    if result == 1 then
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "\t很抱歉，【战场】六人战场还没有开始！");
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
		AddQuestText(sceneId, "\t队伍模式下,您所在队伍人数必须为3人以上才能报名【战场】六人战场。");
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
		AddQuestText(sceneId, "\t这次的【战场】六人战场报名已经满了，请等候下场战斗。");
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
    AddQuestText(sceneId, "\t#G您成功的申请了【战场】六人战场，请等待比赛的开始！");
	EndQuestEvent(sceneId)
	DispatchQuestEventList(sceneId,selfId,targetId)
	
	local nTeamId = GetTeamId( sceneId,selfId)
	if nTeamId >= 0 then
		LuaAllScenceM2Team(sceneId,"您的队伍顺利的完成了【战场】六人战场的报名！",nTeamId,2,1)
		LuaAllScenceM2Team(sceneId,"您的队伍顺利的完成了【战场】六人战场的报名！",nTeamId,3,1)		
	else
	
		local name = GetName(sceneId,selfId)
		LuaScenceM2Player(sceneId,selfId,"您顺利的完成了【战场】六人战场的报名！",name,2,1)
		LuaScenceM2Player(sceneId,selfId,"您顺利的完成了【战场】六人战场的报名！",name,3,1)		
	end

    return 1

end


----------------------------------------------------------------------------------------------
--检测接受条件
----------------------------------------------------------------------------------------------
function x303005_ProcAcceptCheck( sceneId, selfId, NPCId )
    return 1
end

----------------------------------------------------------------------------------------------
--接受
----------------------------------------------------------------------------------------------
function x303005_ProcAccept( sceneId, selfId )
end

----------------------------------------------------------------------------------------------
--放弃
----------------------------------------------------------------------------------------------
function x303005_ProcQuestAbandon( sceneId, selfId, MissionId )
end

----------------------------------------------------------------------------------------------
--继续
----------------------------------------------------------------------------------------------
function x303005_OnContinue( sceneId, selfId, targetId )
end

----------------------------------------------------------------------------------------------
--检测是否可以提交
----------------------------------------------------------------------------------------------
function x303005_CheckSubmit( sceneId, selfId )
end

----------------------------------------------------------------------------------------------
--提交
----------------------------------------------------------------------------------------------
function x303005_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end

----------------------------------------------------------------------------------------------
--杀死怪物或玩家
----------------------------------------------------------------------------------------------
function x303005_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end

----------------------------------------------------------------------------------------------
--进入区域事件
----------------------------------------------------------------------------------------------
function x303005_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

----------------------------------------------------------------------------------------------
--道具改变
----------------------------------------------------------------------------------------------
function x303005_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
