
x300941_g_ScriptId 					= 300941
x300941_g_MissionName				= "【国家】查询领主战外援" 
x300941_g_Leader_Index              = 5

----------------------------------------------------------------------------------------------
--枚举
----------------------------------------------------------------------------------------------
function x300941_ProcEnumEvent( sceneId, selfId, targetId )

	--检查是否有帮会
	local nGuildID = GetGuildID(sceneId,selfId)
	if nGuildID < 0 then
		return
	end
	
	--非帮主 
	local pos = GetGuildOfficial(sceneId, selfId)
	if pos ~= x300941_g_Leader_Index then
        return
    end
    
    --检查是否有国王
    local nHumanGUID = GetPlayerGUID( sceneId,selfId )
    local nCountryId,nKingGUID,szKingName,nCountryGold = GetCountrySimpleData( sceneId,selfId )
    if nKingGUID <= 0 or nHumanGUID == nKingGUID then
    	return    	
    end
	
	 --检查是否是青龙
    if IsSpecialCountryOffical(sceneId,selfId,COUNTRY_POSITION_QINGLONG_LEADER) == 1 then
    	return
    end
    
    --检查是否是朱雀
    if IsSpecialCountryOffical(sceneId,selfId,COUNTRY_POSITION_ZHUQUE_LEADER) == 1 then
    	return
    end
    
    --检查是否是国王
    if IsSpecialCountryOffical(sceneId,selfId,COUNTRY_POSITION_KING) == 1 then
    	return
    end
    
    --显示按钮
    AddQuestNumText(sceneId,x300941_g_ScriptId,x300941_g_MissionName,3,x300941_g_ScriptId);
    
end

----------------------------------------------------------------------------------------------
--事件入口
----------------------------------------------------------------------------------------------
function x300941_ProcEventEntry(sceneId, selfId,targetId,scriptId,idExt )
	
	if idExt ~=  x300941_g_ScriptId then
		return
	end

	--检查是否有帮会
	local nGuildID = GetGuildID(sceneId,selfId)
	if nGuildID < 0 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y【国家】领主战场外援查询#W#r\t操作失败,您没有帮会。");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)
		return
	end
	
	--非帮主 
	local pos = GetGuildOfficial(sceneId, selfId)
	if pos ~= x300941_g_Leader_Index then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y【国家】领主战场外援查询#W#r\t操作失败,您不是帮主。");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)
        return
    end
    
    --检查是否有国王
    local nHumanGUID = GetPlayerGUID( sceneId,selfId )
    local nCountryId,nKingGUID,szKingName,nCountryGold = GetCountrySimpleData( sceneId,selfId )
    if nKingGUID <= 0 or nHumanGUID == nKingGUID then
    	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y【国家】领主战场外援查询#W#r\t操作失败,没有国王。");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)
    	return    	
    end
	
	 --检查是否是青龙
    if IsSpecialCountryOffical(sceneId,selfId,COUNTRY_POSITION_QINGLONG_LEADER) == 1 then
    	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y【国家】领主战场外援查询#W#r\t操作失败,青龙帮会不能执行。");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)
    	return
    end
    
    --检查是否是朱雀
    if IsSpecialCountryOffical(sceneId,selfId,COUNTRY_POSITION_ZHUQUE_LEADER) == 1 then
    	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y【国家】领主战场外援查询#W#r\t操作失败,朱雀帮会不能执行。");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)
    	return
    end
    
    --检查是否是国王
    if IsSpecialCountryOffical(sceneId,selfId,COUNTRY_POSITION_KING) == 1 then
    	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y【国家】领主战场外援查询#W#r\t操作失败,国王帮会不能执行。");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)
    	return
    end
	
	--检查通过,则向GL请求外援列表
	SetPlayerRuntimeData(sceneId,selfId,RD_COMMON_NPCID,targetId)
	GameBattleLairdRequestPlayerAidList(sceneId,selfId,x300941_g_ScriptId);
	
	return 0

end 

----------------------------------------------------------------------------------------------
--接受检查
----------------------------------------------------------------------------------------------
function x300941_ProcAcceptCheck( sceneId, selfId, NPCId )

end

----------------------------------------------------------------------------------------------
--处理外援开始事件
----------------------------------------------------------------------------------------------
function x300941_ProcPlayerAidBegin(sceneId,nPlayerAidCount )
	--事件开始
	BeginQuestEvent(sceneId)
	if nPlayerAidCount <= 0 then
		AddQuestText(sceneId, "#Y【国家】领主战场外援列表:#W#r\当前没有外援！");
	else
		AddQuestText(sceneId, "#Y【国家】领主战场外援列表:#W#r");
	end
end

----------------------------------------------------------------------------------------------
--添加外援信息
----------------------------------------------------------------------------------------------
function x300941_ProcAddPlayerAid(sceneId,nPlayerAidGUID,strPlayerAidName,nouse1 )
	--添加数据
	AddQuestNumText(sceneId,x300941_g_ScriptId,strPlayerAidName,3,nPlayerAidGUID);	
end

----------------------------------------------------------------------------------------------
--处理外援结束事件
----------------------------------------------------------------------------------------------
function x300941_ProcPlayerAidEnd(sceneId,selfId )

	--事件结束
	local targetId = GetPlayerRuntimeData(sceneId,selfId,RD_COMMON_NPCID)
	EndQuestEvent(sceneId)
	DispatchQuestEventList(sceneId,selfId,targetId)
end

--**********************************
--接受
--**********************************
function x300941_ProcAccept( sceneId, selfId )
end

--**********************************
--放弃
--**********************************
function x300941_ProcQuestAbandon( sceneId, selfId, MissionId )
end

--**********************************
--继续
--**********************************
function x300941_OnContinue( sceneId, selfId, targetId )
end

--**********************************
--检测是否可以提交
--**********************************
function x300941_CheckSubmit( sceneId, selfId )
end

--**********************************
--提交
--**********************************
function x300941_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end

--**********************************
--杀死怪物或玩家
--**********************************
function x300941_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end

--**********************************
--进入区域事件
--**********************************
function x300941_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--道具改变
--**********************************
function x300941_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end