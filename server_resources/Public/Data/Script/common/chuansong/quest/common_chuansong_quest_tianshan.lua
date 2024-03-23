--【传送】激活领地阿尔金山马车夫

--MisDescBegin
x550518_g_ScriptId = 550518
x550518_g_MissionId = 1508
x550518_g_LevelLess	= 	1 
x550518_g_MissionIdPre= -1
x550518_g_MissionIdNext = -1
x550518_g_MissionHelp =	""
x550518_g_MissionName="激活领地阿尔金山传送"
x550518_g_MissionInfo="#cffcf00您已经开通了#G领地阿尔金山#W#cffcf00传送！#W"  --任务描述
x550518_g_MissionTarget=""		
x550518_g_MissionCompleted=""					--完成任务npc说话的话
x550518_g_ContinueInfo=""

--任务奖励
x550518_g_BonusMoney1 =0
x550518_g_BonusMoney2 =0
x550518_g_BonusMoney3 =0
x550518_g_BonusItem	=	{}
x550518_g_BonusChoiceItem ={}
x550518_g_ExpBonus = 0
x550518_g_NpcGUID =0
--MisDescEnd

--**********************************

--任务入口函数

--**********************************

function x550518_ProcEventEntry(sceneId, selfId, NPCId, MissionId)	--点击该任务后执行此脚本

		return
	
	
end


--**********************************

--列举事件

--**********************************

function x550518_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)

	if GetSceneRelation(sceneId, selfId, sceneId) == 1 then
		if IsQuestHaveDone(sceneId, selfId, x550518_g_MissionId) > 0 then
			return 
		else
			Msg2Player(sceneId,selfId,x550518_g_MissionInfo,8,3)
			QuestCom(sceneId,selfId,MissionId)
		end
	else 
			return
	end		
end



--**********************************

--检测接受条件

--**********************************

function x550518_ProcAcceptCheck(sceneId, selfId, NPCId)

end


--**********************************

--检测查看条件

--**********************************

function x550518_CheckPushList(sceneId, selfId, NPCId)
	
end

--**********************************

--接受

--**********************************

function x550518_ProcQuestAccept( sceneId, selfId, NPCId, MissionId )

end



--**********************************

--放弃

--**********************************

function x550518_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--检测是否可以提交

--**********************************
function x550518_CheckSubmit( sceneId, selfId, NPCId)

end


--**********************************

--提交

--**********************************
function x550518_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)

end


function x550518_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )

end

--**********************************

--杀死怪物或玩家

--**********************************

function x550518_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
	 

end



--**********************************

--进入区域事件

--**********************************

function x550518_ProcAreaEntered(sceneId, selfId, zoneId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "ProcAreaEntered",sceneId, selfId, zoneId, MissionId )	

end

function x550518_ProcTiming(sceneId, selfId, ScriptId, MissionId)
	 CallScriptFunction( MISSION_SCRIPT, "ProcTiming",sceneId, selfId, ScriptId, MissionId )
		
end

function x550518_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcAreaLeaved",sceneId, selfId, ScriptId, MissionId)
end



--**********************************

--道具改变

--**********************************

function x550518_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcQuestItemChanged",sceneId, selfId, itemdataId, MissionId )
end


function x550518_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x550518_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x550518_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x550518_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x550518_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x550518_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end