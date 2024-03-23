x300940_g_ScriptId 					= 300940
x300940_g_MissionName				= "【国家】放弃领主战外援" 
x300940_g_Leader_Index              = 5

x300940_g_Laird_Signup                  	= 300     --报名
x300940_g_Laird_WaitBattle              	= 301     --报名结束，等待领主战场
x300940_g_Laird_BeginBattle             	= 302     --开始领主战场
x300940_g_Laird_EndBattle               	= 303     --结束领主战场
----------------------------------------------------------------------------------------------
--枚举
----------------------------------------------------------------------------------------------
function x300940_ProcEnumEvent( sceneId, selfId, targetId )

	local nBattleStatus = CallScriptFunction(300918,"GetBattleState",sceneId)
	if nBattleStatus ~= x300940_g_Laird_Signup then
		return
	end
	
	local bPlayerAid = CallScriptFunction(300918,"IsPlayerInPlayerAidList",sceneId,selfId)
	if bPlayerAid ~= 1 then
		return
	end
    
    --显示按钮
    AddQuestNumText(sceneId,x300940_g_ScriptId,x300940_g_MissionName,3,x300940_g_ScriptId);
    
end

----------------------------------------------------------------------------------------------
--事件入口
----------------------------------------------------------------------------------------------
function x300940_ProcEventEntry(sceneId, selfId,targetId,scriptId,idExt )
	
	if idExt ==  x300940_g_ScriptId then
	
		local nBattleStatus = CallScriptFunction(300918,"GetBattleState",sceneId)
		if nBattleStatus ~= x300940_g_Laird_Signup then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, "#Y【国家】领主战场外援放弃#W#r\t活动没有开始。");
			EndQuestEvent(sceneId)
			DispatchQuestEventList(sceneId,selfId,targetId)
			return
		end
		
		
		local bPlayerAid = CallScriptFunction(300918,"IsPlayerInPlayerAidList",sceneId,selfId)
		if bPlayerAid ~= 1 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, "#Y【国家】领主战场外援放弃#W#r\t您不是外援。");
			EndQuestEvent(sceneId)
			DispatchQuestEventList(sceneId,selfId,targetId)
			return
		end
		
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y【国家】领主战场外援放弃#W#r\t您将放弃外援身份。您确定要这么做吗?");
		AddQuestNumText(sceneId,x300940_g_ScriptId,"确定...",3);
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)
		
		return 0
		
	else
	
		local nBattleStatus = CallScriptFunction(300918,"GetBattleState",sceneId)
		if nBattleStatus ~= x300940_g_Laird_Signup then
			return
		end
		
		local bPlayerAid = CallScriptFunction(300918,"IsPlayerInPlayerAidList",sceneId,selfId)
		if bPlayerAid ~= 1 then
			return
		end
		
		--执行放弃外援
		GameBattleLairdRequestCanclePlayerAidByPlayerAid(sceneId,selfId)
		
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y【国家】领主战场外援放弃#W#r\t请求已经成功提交。");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)
		
		return 0
		
	end
	
	

end 

----------------------------------------------------------------------------------------------
--接受检查
----------------------------------------------------------------------------------------------
function x300940_ProcAcceptCheck( sceneId, selfId, NPCId )

end

--**********************************
--接受
--**********************************
function x300940_ProcAccept( sceneId, selfId )
end

--**********************************
--放弃
--**********************************
function x300940_ProcQuestAbandon( sceneId, selfId, MissionId )
end

--**********************************
--继续
--**********************************
function x300940_OnContinue( sceneId, selfId, targetId )
end

--**********************************
--检测是否可以提交
--**********************************
function x300940_CheckSubmit( sceneId, selfId )
end

--**********************************
--提交
--**********************************
function x300940_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end

--**********************************
--杀死怪物或玩家
--**********************************
function x300940_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end

--**********************************
--进入区域事件
--**********************************
function x300940_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--道具改变
--**********************************
function x300940_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end