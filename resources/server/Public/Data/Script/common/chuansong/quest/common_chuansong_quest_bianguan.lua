--�����͡��������Ī˹�ƹ�������

--MisDescBegin
x550520_g_ScriptId = 550520
x550520_g_MissionId = 1510
x550520_g_LevelLess	= 	1 
x550520_g_MissionIdPre= -1
x550520_g_MissionIdNext = -1
x550520_g_MissionHelp =	""
x550520_g_MissionName="�������Ī˹�ƹ�������"
x550520_g_MissionInfo="#cffcf00���Ѿ���ͨ��#G���Ī˹�ƹ���#W#cffcf00���ͣ�#W"  --��������
x550520_g_MissionTarget=""		
x550520_g_MissionCompleted=""					--�������npc˵���Ļ�
x550520_g_ContinueInfo=""

--������
x550520_g_BonusMoney1 =0
x550520_g_BonusMoney2 =0
x550520_g_BonusMoney3 =0
x550520_g_BonusItem	=	{}
x550520_g_BonusChoiceItem ={}
x550520_g_ExpBonus = 0
x550520_g_NpcGUID =0
--MisDescEnd

--**********************************

--������ں���

--**********************************

function x550520_ProcEventEntry(sceneId, selfId, NPCId, MissionId)	--����������ִ�д˽ű�
		return
	
end


--**********************************

--�о��¼�

--**********************************

function x550520_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)

	if GetSceneRelation(sceneId, selfId, sceneId) == 1 then
	
		if IsQuestHaveDone(sceneId, selfId, x550520_g_MissionId) > 0 then
			return 
		else
				Msg2Player(sceneId,selfId,x550520_g_MissionInfo,8,3)
				QuestCom(sceneId,selfId,MissionId)
		end
	else 
		return
	end	
end



--**********************************

--����������

--**********************************

function x550520_ProcAcceptCheck(sceneId, selfId, NPCId)

end


--**********************************

--���鿴����

--**********************************

function x550520_CheckPushList(sceneId, selfId, NPCId)
	
end

--**********************************

--����

--**********************************

function x550520_ProcQuestAccept( sceneId, selfId, NPCId, MissionId )

end



--**********************************

--����

--**********************************

function x550520_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************
function x550520_CheckSubmit( sceneId, selfId, NPCId)

end


--**********************************

--�ύ

--**********************************
function x550520_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)

end


function x550520_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )

end

--**********************************

--ɱ����������

--**********************************

function x550520_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
	 

end



--**********************************

--���������¼�

--**********************************

function x550520_ProcAreaEntered(sceneId, selfId, zoneId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "ProcAreaEntered",sceneId, selfId, zoneId, MissionId )	

end

function x550520_ProcTiming(sceneId, selfId, ScriptId, MissionId)
	 CallScriptFunction( MISSION_SCRIPT, "ProcTiming",sceneId, selfId, ScriptId, MissionId )
		
end

function x550520_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcAreaLeaved",sceneId, selfId, ScriptId, MissionId)
end



--**********************************

--���߸ı�

--**********************************

function x550520_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcQuestItemChanged",sceneId, selfId, itemdataId, MissionId )
end


function x550520_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x550520_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x550520_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x550520_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x550520_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x550520_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end