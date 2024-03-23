--装备鎏金说明

--MisDescBegin
x570066_g_ScriptId = 570066
x570066_g_MissionName1="【专精天赋说明】"
x570066_g_MissionInfo1="\t#W专精天赋分为专攻和专防两类。\n\t#Y专攻的作用#W：提高自己对其他玩家的伤害，对某个职业的专攻等级越高，自己对此职业的伤害提升越大。以武士专攻为例，每击败一名可以获得荣誉的异国玩家，武士职业分配的练功点数越多，获得的专攻点数越多。当专攻点数累积到一定数量，专攻等级就会得到提升，对相应职业的伤害提升。\n\t#R特别说明：练功点数仅对每天的前10个荣誉击杀有效，即本日如果已经击败过10个可以获得荣誉的玩家，再分配练功点数，将不再能够获得职业专攻点数，练功点数分配效果将于次日生效。\n\t#Y专防的作用#W：减少其他玩家对自己的伤害，对某个职业的专防等级越高，此职业对自己的伤害越低。提升专防等级需要累积专防训练点数，专防训练点数需要完成【个人】防御之路任务获得。"  --任务描述

--**********************************

--任务入口函数

--**********************************

function x570066_ProcEventEntry(sceneId, selfId, targetId,scriptid,extid)	--点击该任务后执行此脚本
	--检测列出条件

		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"#Y"..x570066_g_MissionName1)
			AddQuestText(sceneId,x570066_g_MissionInfo1)
		EndQuestEvent()
		DispatchQuestEventList(sceneId, selfId,targetId,x570066_g_ScriptId, x570066_g_MissionName1)

end



--**********************************

--列举事件

--**********************************

function x570066_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)

		AddQuestNumText(sceneId, x570066_g_ScriptId, x570066_g_MissionName1,13,1)
	
end



--**********************************

--检测接受条件

--**********************************

function x570066_ProcAcceptCheck(sceneId, selfId, NPCId)

		return 1
end


--**********************************

--检测查看条件

--**********************************

function x570066_CheckPushList(sceneId, selfId, NPCId)
	
end

--**********************************

--接受

--**********************************

function x570066_ProcAccept( sceneId, selfId )
	
end



--**********************************

--放弃

--**********************************

function x570066_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--检测是否可以提交

--**********************************

function x570066_CheckSubmit( sceneId, selfId, NPCId)


end



--**********************************

--提交

--**********************************

function x570066_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)

end



--**********************************

--杀死怪物或玩家

--**********************************

function x570066_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--进入区域事件

--**********************************

function x570066_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)
	

end

function x570066_ProcTiming(sceneId, selfId )
	 
		
end

function x570066_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId )
	
end



--**********************************

--道具改变

--**********************************

function x570066_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	
end
function x570066_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
	    CallScriptFunction( MISSION_SCRIPT, "ProcQuestAttach",sceneId, selfId, npcId, npcGuid, misIndex, MissionId)
end

function x570066_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x570066_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x570066_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x570066_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x570066_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x570066_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end
