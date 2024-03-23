--四大法王玩法说明

--MisDescBegin
x300568_g_ScriptId = 300568
x300568_g_MissionIdPre =-1
--x300568_g_MissionId = 
x300568_g_MissionKind = 8
x300568_g_LevelLess	= 	-1 
x300568_g_MissionIdNext = -1
x300568_g_MissionId1 = 9300
x300568_g_Name	="" 
x300568_g_noDemandItem ={}
x300568_g_ExtTarget={}
x300568_g_NeedNum1= 1
x300568_g_NeedNum2= 1
x300568_g_NeedNum3= 1
x300568_g_MissionHelp =	""
x300568_g_MissionName1="【四大法王玩法说明】"
x300568_g_MissionName2="【四大法王玩法说明】"
x300568_g_MissionInfo1="\t在本任务中，我会让你去询问四大法王，他们中有#G三个人#W会告诉你#G真话#W，#G一个人会撒谎#W。\n\t记住，#G撒谎的人不一定是叛徒，叛徒不一定撒谎#W。\n\t你可以在#G任务攻略#W中查看四大法王说过的话，以便分析。"  --任务描述
--x300568_g_MissionInfo2="\t#G龙眼石#W是王国加强边防的重要物资。王国大将军派我在这里向所有王国的子民们收集#G龙眼石#W。如果您获得了#G龙眼石#W之后，把它交给我，可以得到珍贵的装备。\n\t龙眼石兑换的装备分为30级，50级，70级三种。30级装备需要#G初级龙眼石#W，50级装备需要#G中级龙眼石#W，70级装备需要#G高级龙眼石#W。\n\t我现在能为您兑换50级和70级装备装备！"  --任务描述
x300568_g_MissionCompleted1=""--完成任务npc说话的话
x300568_g_MissionCompleted2=""--完成任务npc说话的话
x300568_g_ContinueInfo1="\t你将要x300568_g_MissionName5。\n\t将扣除您的龙眼石x300568_g_NeedNum1颗。"
x300568_g_ContinueInfo2=""
x300568_g_ContinueInfo3=""
x300568_g_ErrorInfo1=""
x300568_g_ErrorInfo2=""
x300568_g_BonusMoney1 =0
x300568_g_BonusMoney2 =0
x300568_g_BonusMoney3 =0
x300568_g_BonusItem	=	{}
x300568_g_BonusChoiceItem ={}
x300568_g_ExpBonus = 250
x300568_g_SkillHalfHour = 7510
x300568_g_SkillOneHour = 7511
--MisDescEnd

--**********************************

--任务入口函数

--**********************************

function x300568_ProcEventEntry(sceneId, selfId, targetId,scriptid,extid)	--点击该任务后执行此脚本
	--检测列出条件
local isHaveMission = IsHaveQuestNM(sceneId,selfId,9300);
if isHaveMission == 1 then
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"#Y"..x300568_g_MissionName2)
			AddQuestText(sceneId,x300568_g_MissionInfo1)
		EndQuestEvent()
		DispatchQuestEventList(sceneId, selfId,targetId,x300568_g_ScriptId, x300568_g_MissionName1)
	
end

end



--**********************************

--列举事件

--**********************************

function x300568_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)

--	local country = GetCurCountry(sceneId, selfId)
--	local nDefaultCamp = GetSceneCamp( sceneId )-16
--
--	if country == nDefaultCamp then 
local isHaveMission = IsHaveQuestNM(sceneId,selfId,9300);
if isHaveMission == 1 then
		AddQuestNumText(sceneId, x300568_g_ScriptId, x300568_g_MissionName1,0,1)
--	else 
--			return
--	end
end
	
end



--**********************************

--检测接受条件

--**********************************

function x300568_ProcAcceptCheck(sceneId, selfId, NPCId)

	return 1
end


--**********************************

--检测查看条件

--**********************************

function x300568_CheckPushList(sceneId, selfId, NPCId)
	
end

--**********************************

--接受

--**********************************

function x300568_ProcAccept( sceneId, selfId )
	
end



--**********************************

--放弃

--**********************************

function x300568_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--检测是否可以提交

--**********************************

function x300568_CheckSubmit( sceneId, selfId, NPCId)


end



--**********************************

--提交

--**********************************

function x300568_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)

end



--**********************************

--杀死怪物或玩家

--**********************************

function x300568_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--进入区域事件

--**********************************

function x300568_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)
	

end

function x300568_ProcTiming(sceneId, selfId )
	 
		
end

function x300568_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId )
	
end



--**********************************

--道具改变

--**********************************

function x300568_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	
end
function x300568_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
	    CallScriptFunction( MISSION_SCRIPT, "ProcQuestAttach",sceneId, selfId, npcId, npcGuid, misIndex, MissionId)
end

function x300568_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x300568_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x300568_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x300568_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x300568_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x300568_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end
