
--����ϵͳȫ�ֺ����Ľű��ļ�

--�ű���
x300270_g_scriptId = 700003

function x300270_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
 	CallScriptFunction( x300270_g_scriptId, "ProcEnumEvent", sceneId, selfId, targetId, -1 )
end

--ѡ������
function x300270_ProcEventEntry( sceneId, selfId, targetId, MissionId )
    CallScriptFunction( x300270_g_scriptId, "ProcEventEntry", sceneId, selfId, targetId )
end

--��������
function x300270_ProcQuestAccept( sceneId, selfId, targetId, MissionId )
 	return CallScriptFunction( x300270_g_scriptId, "ProcAccept", sceneId, selfId, targetId )
end

--ɱ������
function x300270_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
	return CallScriptFunction( x300270_g_scriptId, "ProcQuestObjectKilled", sceneId, selfId, objdataId, objId )
end


--�������
function x300270_ProcQuestAbandon( sceneId, selfId, MissionId )
 	CallScriptFunction( x300270_g_scriptId, "ProcQuestAbandon", sceneId, selfId )
end

function x300270_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
 	CallScriptFunction( MISSION_SCRIPT, "ProcQuestAttach", sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
end


--�������
--����1����ɹ���0��������ʧ��
function x300270_ProcQuestSubmit( sceneId, selfId, targetId, selectId, MissionId )
 	return CallScriptFunction( x300270_g_scriptId, "ProcQuestSubmit", sceneId, selfId, targetId )
end

--�������
function x300270_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
 	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId,MissionId )
end

--��Ʒ�ı�
function x300270_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
 	CallScriptFunction( MISSION_SCRIPT, "ProcQuestItemChanged",sceneId, selfId, itemdataId, MissionId )
end

function x300270_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
    return CallScriptFunction( MISSION_SCRIPT, "ProcAreaEntered",sceneId, selfId, zoneId, MissionId )
end

--�뿪����
function x300270_ProcAreaLeaved( sceneId, selfId, ScriptId, MissionId )
    CallScriptFunction( MISSION_SCRIPT, "ProcAreaLeaved",sceneId, selfId, ScriptId, MissionId)
end

--����ʱ��
function x300270_ProcTiming( sceneId, selfId, ScriptId, MissionId )
    CallScriptFunction( MISSION_SCRIPT, "ProcTiming",sceneId, selfId, ScriptId, MissionId )
end


--**********************************************************************
--����ʹ����Ʒ����
function x300270_PositionUseItem( sceneId, selfId, BagIndex, impactId )
 	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end


--**********************************************************************
--�ɼ�����
--��ItemBox
function x300270_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

--����
function x300270_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

--��
function x300270_OnProcOver( sceneId, selfId, targetId )
    CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

--�򿪺���
function x300270_OpenCheck( sceneId, selfId, targetId )
    CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end


--**********************************************************************

