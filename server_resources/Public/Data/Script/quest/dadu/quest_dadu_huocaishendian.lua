
--任务系统全局函数的脚本文件

--脚本号
x300270_g_scriptId = 700003

function x300270_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
 	CallScriptFunction( x300270_g_scriptId, "ProcEnumEvent", sceneId, selfId, targetId, -1 )
end

--选中任务
function x300270_ProcEventEntry( sceneId, selfId, targetId, MissionId )
    CallScriptFunction( x300270_g_scriptId, "ProcEventEntry", sceneId, selfId, targetId )
end

--接受任务
function x300270_ProcQuestAccept( sceneId, selfId, targetId, MissionId )
 	return CallScriptFunction( x300270_g_scriptId, "ProcAccept", sceneId, selfId, targetId )
end

--杀死怪物
function x300270_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
	return CallScriptFunction( x300270_g_scriptId, "ProcQuestObjectKilled", sceneId, selfId, objdataId, objId )
end


--任务放弃
function x300270_ProcQuestAbandon( sceneId, selfId, MissionId )
 	CallScriptFunction( x300270_g_scriptId, "ProcQuestAbandon", sceneId, selfId )
end

function x300270_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
 	CallScriptFunction( MISSION_SCRIPT, "ProcQuestAttach", sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
end


--完成任务
--返回1代表成功，0代表交任务失败
function x300270_ProcQuestSubmit( sceneId, selfId, targetId, selectId, MissionId )
 	return CallScriptFunction( x300270_g_scriptId, "ProcQuestSubmit", sceneId, selfId, targetId )
end

--任务完成
function x300270_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
 	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId,MissionId )
end

--物品改变
function x300270_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
 	CallScriptFunction( MISSION_SCRIPT, "ProcQuestItemChanged",sceneId, selfId, itemdataId, MissionId )
end

function x300270_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
    return CallScriptFunction( MISSION_SCRIPT, "ProcAreaEntered",sceneId, selfId, zoneId, MissionId )
end

--离开区域
function x300270_ProcAreaLeaved( sceneId, selfId, ScriptId, MissionId )
    CallScriptFunction( MISSION_SCRIPT, "ProcAreaLeaved",sceneId, selfId, ScriptId, MissionId)
end

--区域定时器
function x300270_ProcTiming( sceneId, selfId, ScriptId, MissionId )
    CallScriptFunction( MISSION_SCRIPT, "ProcTiming",sceneId, selfId, ScriptId, MissionId )
end


--**********************************************************************
--定点使用物品任务
function x300270_PositionUseItem( sceneId, selfId, BagIndex, impactId )
 	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end


--**********************************************************************
--采集任务
--打开ItemBox
function x300270_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

--回收
function x300270_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

--打开
function x300270_OnProcOver( sceneId, selfId, targetId )
    CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

--打开后检查
function x300270_OpenCheck( sceneId, selfId, targetId )
    CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end


--**********************************************************************

