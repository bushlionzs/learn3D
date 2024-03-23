--装备鎏金说明

--MisDescBegin
x570067_g_ScriptId = 570067
x570067_g_MissionName1="【元素天赋说明】"
x570067_g_MissionInfo1="\t#W元素天赋简要说明。\n#Y元素天赋的作用#W：\n\t秘密。\n#Y元素天赋如何学习#W：\n\t也是秘密。\n#Y道具如何获得#W：\n\t还是秘密。"  --任务描述

--**********************************

--任务入口函数

--**********************************

function x570067_ProcEventEntry(sceneId, selfId, targetId,scriptid,extid)	--点击该任务后执行此脚本
	--检测列出条件

		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"#Y"..x570067_g_MissionName1)
			AddQuestText(sceneId,x570067_g_MissionInfo1)
		EndQuestEvent()
		DispatchQuestEventList(sceneId, selfId,targetId,x570067_g_ScriptId, x570067_g_MissionName1)

end



--**********************************

--列举事件

--**********************************

function x570067_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)

		AddQuestNumText(sceneId, x570067_g_ScriptId, x570067_g_MissionName1,13,1)
	
end



--**********************************

--检测接受条件

--**********************************

function x570067_ProcAcceptCheck(sceneId, selfId, NPCId)

		return 1
end


--**********************************

--检测查看条件

--**********************************

function x570067_CheckPushList(sceneId, selfId, NPCId)
	
end

--**********************************

--接受

--**********************************

function x570067_ProcAccept( sceneId, selfId )
	
end



--**********************************

--放弃

--**********************************

function x570067_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--检测是否可以提交

--**********************************

function x570067_CheckSubmit( sceneId, selfId, NPCId)


end



--**********************************

--提交

--**********************************

function x570067_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)

end



--**********************************

--杀死怪物或玩家

--**********************************

function x570067_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--进入区域事件

--**********************************

function x570067_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)
	

end

function x570067_ProcTiming(sceneId, selfId )
	 
		
end

function x570067_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId )
	
end



--**********************************

--道具改变

--**********************************

function x570067_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	
end
function x570067_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
	    CallScriptFunction( MISSION_SCRIPT, "ProcQuestAttach",sceneId, selfId, npcId, npcGuid, misIndex, MissionId)
end

function x570067_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x570067_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x570067_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x570067_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x570067_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x570067_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end
