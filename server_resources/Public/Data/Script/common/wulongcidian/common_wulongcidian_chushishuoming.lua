--乌龙辞典玩法说明

--MisDescBegin
x310188_g_ScriptId = 310188
x310188_g_MissionIdPre =-1
--x310188_g_MissionId = 
x310188_g_MissionKind = 8
x310188_g_LevelLess	= 	-1 
x310188_g_MissionIdNext = -1
x310188_g_MissionId1 = 9300
x310188_g_Name	="" 
x310188_g_noDemandItem ={}
x310188_g_ExtTarget={}
x310188_g_NeedNum1= 1
x310188_g_NeedNum2= 1
x310188_g_NeedNum3= 1
x310188_g_MissionHelp =	""
x310188_g_MissionName1="【乌龙辞典王国海选赛说明】"
x310188_g_MissionName2="【乌龙辞典王国海选赛说明】"
x310188_g_MissionInfo1="\t乌龙辞典共分为三个阶段：#G乌龙辞典王国海选赛，乌龙辞典大都淘汰赛，乌龙辞典终极挑战赛。#W\n\t#R20#W级以上的各位玩家可以在自己王国的#G记忆之门，东大街，西大街#W任意一处找到海选主持人参加比赛。\n\t等级不低于#G40级#W并且#G回答正确10题以上#W的玩家可以获得参加下一轮大都淘汰赛的资格，在下午2点后，前往大都#G（157，215）（96，222）（66，196）任意一处找到大都一号主持人参加！"  --任务描述
--x310188_g_MissionInfo2="\t#G龙眼石#W是王国加强边防的重要物资。王国大将军派我在这里向所有王国的子民们收集#G龙眼石#W。如果您获得了#G龙眼石#W之后，把它交给我，可以得到珍贵的装备。\n\t龙眼石兑换的装备分为30级，50级，70级三种。30级装备需要#G初级龙眼石#W，50级装备需要#G中级龙眼石#W，70级装备需要#G高级龙眼石#W。\n\t我现在能为您兑换50级和70级装备装备！"  --任务描述
x310188_g_MissionCompleted1=""--完成任务npc说话的话
x310188_g_MissionCompleted2=""--完成任务npc说话的话
x310188_g_ContinueInfo1="\t你将要x310188_g_MissionName5。\n\t将扣除您的龙眼石x310188_g_NeedNum1颗。"
x310188_g_ContinueInfo2=""
x310188_g_ContinueInfo3=""
x310188_g_ErrorInfo1=""
x310188_g_ErrorInfo2=""
x310188_g_BonusMoney1 =0
x310188_g_BonusMoney2 =0
x310188_g_BonusMoney3 =0
x310188_g_BonusItem	=	{}
x310188_g_BonusChoiceItem ={}
x310188_g_ExpBonus = 250
x310188_g_SkillHalfHour = 7510
x310188_g_SkillOneHour = 7511
--MisDescEnd

--**********************************

--任务入口函数

--**********************************

function x310188_ProcEventEntry(sceneId, selfId, targetId,scriptid,extid)	--点击该任务后执行此脚本
	--检测列出条件
--local isHaveMission = IsHaveQuestNM(sceneId,selfId,9300);
--if isHaveMission == 1 then
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"#Y"..x310188_g_MissionName1)
			AddQuestText(sceneId,x310188_g_MissionInfo1)
		EndQuestEvent()
		DispatchQuestEventList(sceneId, selfId,targetId,x310188_g_ScriptId, x310188_g_MissionName1)
	
--end

end



--**********************************

--列举事件

--**********************************

function x310188_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)

--	local country = GetCurCountry(sceneId, selfId)
--	local nDefaultCamp = GetSceneCamp( sceneId )-16
--
--	if country == nDefaultCamp then 
--local isHaveMission = IsHaveQuestNM(sceneId,selfId,9300);
--if isHaveMission == 1 then
		AddQuestNumText(sceneId, x310188_g_ScriptId, x310188_g_MissionName1,13,1)
--	else 
--			return
--	end
--end
	
end



--**********************************

--检测接受条件

--**********************************

function x310188_ProcAcceptCheck(sceneId, selfId, NPCId)

	return 1
end


--**********************************

--检测查看条件

--**********************************

function x310188_CheckPushList(sceneId, selfId, NPCId)
	
end

--**********************************

--接受

--**********************************

function x310188_ProcAccept( sceneId, selfId )
	
end



--**********************************

--放弃

--**********************************

function x310188_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--检测是否可以提交

--**********************************

function x310188_CheckSubmit( sceneId, selfId, NPCId)


end



--**********************************

--提交

--**********************************

function x310188_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)

end



--**********************************

--杀死怪物或玩家

--**********************************

function x310188_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--进入区域事件

--**********************************

function x310188_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)
	

end

function x310188_ProcTiming(sceneId, selfId )
	 
		
end

function x310188_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId )
	
end



--**********************************

--道具改变

--**********************************

function x310188_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	
end
function x310188_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
	    CallScriptFunction( MISSION_SCRIPT, "ProcQuestAttach",sceneId, selfId, npcId, npcGuid, misIndex, MissionId)
end

function x310188_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x310188_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x310188_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x310188_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x310188_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x310188_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end
