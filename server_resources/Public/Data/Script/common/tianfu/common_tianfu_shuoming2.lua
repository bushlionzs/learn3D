--装备鎏金说明

--MisDescBegin
x570065_g_ScriptId = 570065
x570065_g_MissionName1="【平衡天赋说明】"
x570065_g_MissionInfo1="\t#W每个人的成长之路尽不相同，弥补自身在与敌对阵时属性相克而带来的劣势，才能变得更加强大！\n#Y平衡天赋的作用#W：\n\t在自身属性与敌方属性差异过大，发挥平衡作用，减少一定的属性差异，使得自身战斗力可以淋漓尽致的发挥出来。\n\t1.控制命中平衡：提升控制技能的命中率，每级提升1%。\n\t2.控制抵抗平衡：提升控制技能的抵抗率，每级提升1%。（生效的抵抗率上限为90%）\n\t3.命中平衡：当实际命中率低于50%时生效，每级提升1点命中。\n\t4.闪避平衡：当实际闪避率低于20%时生效，每级提升1点闪避。\n\t5.暴击平衡：当实际暴击率低于10%时生效，每级提升1点暴击。\n\t6.韧性平衡：当实际免暴击率低于50%时生效，每级提升1点韧性。（不影响暴击伤害）\n\t7.暴击伤害平衡：当实际暴击伤害低于50时生效，每级提升1%暴击伤害。\n\t8.暴击减免平衡：当实际被暴击伤害高于100时生效，每级提升1%暴击伤害减免。\n#Y平衡天赋如何学习#W：\n\t在大都天赋区#G平衡天赋大师#W处，学习和升级技能。需要一定的天赋等级和相应等级的平衡之书。\n#Y平衡之书如何获得#W：\n\t各级平衡之书通过低级平衡之书合成而来；一级平衡之书通过平衡之书残页合成而来；平衡之书残页可以在各种玩法中获得。"  --任务描述

--**********************************

--任务入口函数

--**********************************

function x570065_ProcEventEntry(sceneId, selfId, targetId,scriptid,extid)	--点击该任务后执行此脚本
	--检测列出条件

		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"#Y"..x570065_g_MissionName1)
			AddQuestText(sceneId,x570065_g_MissionInfo1)
		EndQuestEvent()
		DispatchQuestEventList(sceneId, selfId,targetId,x570065_g_ScriptId, x570065_g_MissionName1)

end



--**********************************

--列举事件

--**********************************

function x570065_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)

		AddQuestNumText(sceneId, x570065_g_ScriptId, x570065_g_MissionName1,13,1)
	
end



--**********************************

--检测接受条件

--**********************************

function x570065_ProcAcceptCheck(sceneId, selfId, NPCId)

		return 1
end


--**********************************

--检测查看条件

--**********************************

function x570065_CheckPushList(sceneId, selfId, NPCId)
	
end

--**********************************

--接受

--**********************************

function x570065_ProcAccept( sceneId, selfId )
	
end



--**********************************

--放弃

--**********************************

function x570065_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--检测是否可以提交

--**********************************

function x570065_CheckSubmit( sceneId, selfId, NPCId)


end



--**********************************

--提交

--**********************************

function x570065_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)

end



--**********************************

--杀死怪物或玩家

--**********************************

function x570065_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--进入区域事件

--**********************************

function x570065_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)
	

end

function x570065_ProcTiming(sceneId, selfId )
	 
		
end

function x570065_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId )
	
end



--**********************************

--道具改变

--**********************************

function x570065_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	
end
function x570065_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
	    CallScriptFunction( MISSION_SCRIPT, "ProcQuestAttach",sceneId, selfId, npcId, npcGuid, misIndex, MissionId)
end

function x570065_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x570065_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x570065_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x570065_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x570065_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x570065_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end
