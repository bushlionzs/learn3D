--装备鎏金说明

--MisDescBegin
x570064_g_ScriptId = 570064
x570064_g_MissionName1="【属性天赋说明】"
x570064_g_MissionInfo1="\t#W只有各项属性全面增强，才能变得更加强大！\n#Y属性天赋的作用#W：\n\t通过学习各种属性，提升自身的综合实力，力图在战场上立于不败之地。\n#Y属性天赋如何学习#W：\n\t在大都天赋区#G属性天赋大师#W处，学习和升级技能（仅能学习帮会已经研发的技能）。需要一定的天赋等级和帮贡。\n#Y帮贡如何获得#W：\n\t各种帮会玩法和帮会战中可以获得帮贡。"  --任务描述

--**********************************

--任务入口函数

--**********************************

function x570064_ProcEventEntry(sceneId, selfId, targetId,scriptid,extid)	--点击该任务后执行此脚本
	--检测列出条件

		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"#Y"..x570064_g_MissionName1)
			AddQuestText(sceneId,x570064_g_MissionInfo1)
		EndQuestEvent()
		DispatchQuestEventList(sceneId, selfId,targetId,x570064_g_ScriptId, x570064_g_MissionName1)

end



--**********************************

--列举事件

--**********************************

function x570064_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)

		AddQuestNumText(sceneId, x570064_g_ScriptId, x570064_g_MissionName1,13,1)
	
end



--**********************************

--检测接受条件

--**********************************

function x570064_ProcAcceptCheck(sceneId, selfId, NPCId)

		return 1
end


--**********************************

--检测查看条件

--**********************************

function x570064_CheckPushList(sceneId, selfId, NPCId)
	
end

--**********************************

--接受

--**********************************

function x570064_ProcAccept( sceneId, selfId )
	
end



--**********************************

--放弃

--**********************************

function x570064_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--检测是否可以提交

--**********************************

function x570064_CheckSubmit( sceneId, selfId, NPCId)


end



--**********************************

--提交

--**********************************

function x570064_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)

end



--**********************************

--杀死怪物或玩家

--**********************************

function x570064_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--进入区域事件

--**********************************

function x570064_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)
	

end

function x570064_ProcTiming(sceneId, selfId )
	 
		
end

function x570064_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId )
	
end



--**********************************

--道具改变

--**********************************

function x570064_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	
end
function x570064_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
	    CallScriptFunction( MISSION_SCRIPT, "ProcQuestAttach",sceneId, selfId, npcId, npcGuid, misIndex, MissionId)
end

function x570064_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x570064_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x570064_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x570064_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x570064_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x570064_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end
