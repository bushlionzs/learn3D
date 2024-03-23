--装备锻造说明

--MisDescBegin
x800116_g_ScriptId = 800116
--x800116_g_MissionIdPre =-1
--x800116_g_MissionId = 
--x800116_g_MissionKind = 8
--x800116_g_LevelLess	= 	-1 
--x800116_g_MissionIdNext = -1
--x800116_g_Name	="" 
--x800116_g_noDemandItem ={}
--x800116_g_ExtTarget={}
--x800116_g_NeedNum1= 1
--x800116_g_NeedNum2= 1
--x800116_g_NeedNum3= 1
--x800116_g_MissionHelp =	""
x800116_g_MissionName1="【橙色装备打造说明】"
x800116_g_MissionInfo1="策划待补充..."  --任务描述
--x800116_g_MissionInfo2="\t#G龙眼石#W是王国加强边防的重要物资。王国大将军派我在这里向所有王国的子民们收集#G龙眼石#W。如果您获得了#G龙眼石#W之后，把它交给我，可以得到珍贵的装备。\n\t龙眼石兑换的装备分为世传，国传，神传，天传四种。世传装备需要#G初级龙眼石#W，国传装备需要#G中级龙眼石#W，神传装备需要#G高级龙眼石#W。天传装备需要#G天之龙眼石#W。\n\t我现在能为您兑换国传装备、神传装备和天传装备！"  --任务描述
--x800116_g_MissionCompleted1=""--完成任务npc说话的话
--x800116_g_MissionCompleted2=""--完成任务npc说话的话
--x800116_g_ContinueInfo1="\t你将要x800116_g_MissionName5。\n\t将扣除您的龙眼石x800116_g_NeedNum1颗。"
--x800116_g_ContinueInfo2=""
--x800116_g_ContinueInfo3=""
--x800116_g_ErrorInfo1=""
--x800116_g_ErrorInfo2=""
--x800116_g_BonusMoney1 =0
--x800116_g_BonusMoney2 =0
--x800116_g_BonusMoney3 =0
--x800116_g_BonusItem	=	{}
--x800116_g_BonusChoiceItem ={}
--x800116_g_ExpBonus = 250
--x800116_g_SkillHalfHour = 7510
--x800116_g_SkillOneHour = 7511
--MisDescEnd

--**********************************

--任务入口函数

--**********************************

function x800116_ProcEventEntry(sceneId, selfId, targetId,scriptid,extid)	--点击该任务后执行此脚本
	--检测列出条件

		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"#Y"..x800116_g_MissionName1)
			AddQuestText(sceneId,x800116_g_MissionInfo1)
		EndQuestEvent()
		DispatchQuestEventList(sceneId, selfId,targetId,x800116_g_ScriptId, x800116_g_MissionName1)

end



--**********************************

--列举事件

--**********************************

function x800116_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)

--	local country = GetCurCountry(sceneId, selfId)
--	local nDefaultCamp = GetSceneCamp( sceneId )-16
--
--	if country == nDefaultCamp then 
		AddQuestNumText(sceneId, x800116_g_ScriptId, x800116_g_MissionName1,13,1)
--	else 
--			return
--	end
	
end



--**********************************

--检测接受条件

--**********************************

function x800116_ProcAcceptCheck(sceneId, selfId, NPCId)
		return 1
end


--**********************************

--检测查看条件

--**********************************

function x800116_CheckPushList(sceneId, selfId, NPCId)
	
end

--**********************************

--接受

--**********************************

function x800116_ProcAccept( sceneId, selfId )
	
end



--**********************************

--放弃

--**********************************

function x800116_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--检测是否可以提交

--**********************************

function x800116_CheckSubmit( sceneId, selfId, NPCId)


end



--**********************************

--提交

--**********************************

function x800116_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)

end



--**********************************

--杀死怪物或玩家

--**********************************

function x800116_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--进入区域事件

--**********************************

function x800116_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)
	

end

function x800116_ProcTiming(sceneId, selfId )
	 
		
end

function x800116_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId )
	
end



--**********************************

--道具改变

--**********************************

function x800116_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	
end
function x800116_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
	    CallScriptFunction( MISSION_SCRIPT, "ProcQuestAttach",sceneId, selfId, npcId, npcGuid, misIndex, MissionId)
end

function x800116_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x800116_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x800116_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x800116_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x800116_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x800116_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end
