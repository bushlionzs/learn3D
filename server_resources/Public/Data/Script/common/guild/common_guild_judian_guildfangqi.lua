x300939_g_ScriptId 					= 300939
x300939_g_MissionName				= "【国家】领主战外援管理" 
x300939_g_Leader_Index              = 5


x300939_g_Laird_Signup                  	= 300     --报名
x300939_g_Laird_WaitBattle              	= 301     --报名结束，等待领主战场
x300939_g_Laird_BeginBattle             	= 302     --开始领主战场
x300939_g_Laird_EndBattle               	= 303     --结束领主战场

----------------------------------------------------------------------------------------------
--枚举
----------------------------------------------------------------------------------------------
function x300939_ProcEnumEvent( sceneId, selfId, targetId )

	--检查是否有帮会
	local nGuildID = GetGuildID(sceneId,selfId)
	if nGuildID < 0 then
		return
	end
	
	--非帮主 
	local pos = GetGuildOfficial(sceneId, selfId)
	if pos ~= x300939_g_Leader_Index then
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
 
 	--不在报名时间范围内   
    local nBattleStatus = CallScriptFunction(300918,"GetBattleState",sceneId)
	if nBattleStatus ~= x300939_g_Laird_Signup then
		return
	end
    
    --显示按钮
    AddQuestNumText(sceneId,x300939_g_ScriptId,x300939_g_MissionName,3,x300939_g_ScriptId);
    
end

----------------------------------------------------------------------------------------------
--事件入口
----------------------------------------------------------------------------------------------
function x300939_ProcEventEntry(sceneId, selfId,targetId,scriptId,idExt )
	
	--不在报名时间范围内   
    local nBattleStatus = CallScriptFunction(300918,"GetBattleState",sceneId)
	if nBattleStatus ~= x300939_g_Laird_Signup then
		return
	end
	
	if idExt ==  x300939_g_ScriptId then

		--检查是否有帮会
		local nGuildID = GetGuildID(sceneId,selfId)
		if nGuildID < 0 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, "#Y【国家】领主战场外援放弃#W#r\t操作失败,您没有帮会。");
			EndQuestEvent(sceneId)
			DispatchQuestEventList(sceneId,selfId,targetId)
			return
		end
		
		--非帮主 
		local pos = GetGuildOfficial(sceneId, selfId)
		if pos ~= x300939_g_Leader_Index then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, "#Y【国家】领主战场外援放弃#W#r\t操作失败,您不是帮主。");
			EndQuestEvent(sceneId)
			DispatchQuestEventList(sceneId,selfId,targetId)
	        return
	    end
	    
	    --检查是否有国王
	    local nHumanGUID = GetPlayerGUID( sceneId,selfId )
	    local nCountryId,nKingGUID,szKingName,nCountryGold = GetCountrySimpleData( sceneId,selfId )
	    if nKingGUID <= 0 or nHumanGUID == nKingGUID then
	    	BeginQuestEvent(sceneId)
			AddQuestText(sceneId, "#Y【国家】领主战场外援放弃#W#r\t操作失败,没有国王。");
			EndQuestEvent(sceneId)
			DispatchQuestEventList(sceneId,selfId,targetId)
	    	return    	
	    end
		
		 --检查是否是青龙
	    if IsSpecialCountryOffical(sceneId,selfId,COUNTRY_POSITION_QINGLONG_LEADER) == 1 then
	    	BeginQuestEvent(sceneId)
			AddQuestText(sceneId, "#Y【国家】领主战场外援放弃#W#r\t操作失败,青龙帮会不能执行。");
			EndQuestEvent(sceneId)
			DispatchQuestEventList(sceneId,selfId,targetId)
	    	return
	    end
	    
	    --检查是否是朱雀
	    if IsSpecialCountryOffical(sceneId,selfId,COUNTRY_POSITION_ZHUQUE_LEADER) == 1 then
	    	BeginQuestEvent(sceneId)
			AddQuestText(sceneId, "#Y【国家】领主战场外援放弃#W#r\t操作失败,朱雀帮会不能执行。");
			EndQuestEvent(sceneId)
			DispatchQuestEventList(sceneId,selfId,targetId)
	    	return
	    end
	    
	    --检查是否是国王
	    if IsSpecialCountryOffical(sceneId,selfId,COUNTRY_POSITION_KING) == 1 then
	    	BeginQuestEvent(sceneId)
			AddQuestText(sceneId, "#Y【国家】领主战场外援放弃#W#r\t操作失败,国王帮会不能执行。");
			EndQuestEvent(sceneId)
			DispatchQuestEventList(sceneId,selfId,targetId)
	    	return
	    end
		
		--检查通过,则向GL请求外援列表
		SetPlayerRuntimeData(sceneId,selfId,RD_COMMON_NPCID,targetId)
		GameBattleLairdRequestPlayerAidList(sceneId,selfId,x300939_g_ScriptId);
		
		return 0
		
	else
		
		--执行放弃外援
		GameBattleLairdRequestCanclePlayerAidByGuildLeader(sceneId,selfId,idExt)
		
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y【国家】领主战场外援放弃#W#r\t请求已经成功提交。");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)
		
		return
		
	end
	
	

end 

----------------------------------------------------------------------------------------------
--接受检查
----------------------------------------------------------------------------------------------
function x300939_ProcAcceptCheck( sceneId, selfId, NPCId )

end

----------------------------------------------------------------------------------------------
--处理外援开始事件
----------------------------------------------------------------------------------------------
function x300939_ProcPlayerAidBegin(sceneId,nPlayerAidCount )
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
function x300939_ProcAddPlayerAid(sceneId,nPlayerAidGUID,strPlayerAidName,nouse1 )
	--添加数据
	AddQuestNumText(sceneId,x300939_g_ScriptId,"放弃 "..strPlayerAidName,3,nPlayerAidGUID);	
end

----------------------------------------------------------------------------------------------
--处理外援结束事件
----------------------------------------------------------------------------------------------
function x300939_ProcPlayerAidEnd(sceneId,selfId )

	--事件结束
	local targetId = GetPlayerRuntimeData(sceneId,selfId,RD_COMMON_NPCID)
	EndQuestEvent(sceneId)
	DispatchQuestEventList(sceneId,selfId,targetId)
end

--**********************************
--接受
--**********************************
function x300939_ProcAccept( sceneId, selfId )
end

--**********************************
--放弃
--**********************************
function x300939_ProcQuestAbandon( sceneId, selfId, MissionId )
end

--**********************************
--继续
--**********************************
function x300939_OnContinue( sceneId, selfId, targetId )
end

--**********************************
--检测是否可以提交
--**********************************
function x300939_CheckSubmit( sceneId, selfId )
end

--**********************************
--提交
--**********************************
function x300939_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end

--**********************************
--杀死怪物或玩家
--**********************************
function x300939_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end

--**********************************
--进入区域事件
--**********************************
function x300939_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--道具改变
--**********************************
function x300939_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end