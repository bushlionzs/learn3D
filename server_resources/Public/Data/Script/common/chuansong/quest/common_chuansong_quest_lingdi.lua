--�����͡������������

--MisDescBegin
x550522_g_ScriptId = 550522
x550522_g_MissionId = 1512
x550522_g_LevelLess	= 	1 
x550522_g_MissionIdPre= -1
x550522_g_MissionIdNext = -1
x550522_g_MissionHelp =	""
x550522_g_MissionName="������ش���"
x550522_g_MissionInfo="#cffcf00���Ѿ���ͨ��#G���#W#cffcf00���ͣ�#W"  --��������
x550522_g_MissionTarget=""		
x550522_g_MissionCompleted=""					--�������npc˵���Ļ�
x550522_g_ContinueInfo=""

--������
x550522_g_BonusMoney1 =0
x550522_g_BonusMoney2 =0
x550522_g_BonusMoney3 =0
x550522_g_BonusItem	=	{}
x550522_g_BonusChoiceItem ={}
x550522_g_ExpBonus = 0
x550522_g_NpcGUID =0
--MisDescEnd

--**********************************

--������ں���

--**********************************

function x550522_ProcEventEntry(sceneId, selfId, NPCId, MissionId)	--����������ִ�д˽ű�
			return
	
	
end


--**********************************

--�о��¼�

--**********************************

function x550522_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
		
	--��������ɹ��������
	if IsQuestHaveDone(sceneId, selfId, x550522_g_MissionId) > 0 then
		return 
	else
		Msg2Player(sceneId,selfId,x550522_g_MissionInfo,8,3)
		QuestCom(sceneId,selfId,MissionId)
	end
		
end



--**********************************

--����������

--**********************************

function x550522_ProcAcceptCheck(sceneId, selfId, NPCId)

end


--**********************************

--���鿴����

--**********************************

function x550522_CheckPushList(sceneId, selfId, NPCId)
	
end

--**********************************

--����

--**********************************

function x550522_ProcQuestAccept( sceneId, selfId, NPCId, MissionId )

end



--**********************************

--����

--**********************************

function x550522_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************
function x550522_CheckSubmit( sceneId, selfId, NPCId)

end


--**********************************

--�ύ

--**********************************
function x550522_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)

end


function x550522_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )

end

--**********************************

--ɱ����������

--**********************************

function x550522_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
	 

end



--**********************************

--���������¼�

--**********************************

function x550522_ProcAreaEntered(sceneId, selfId, zoneId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "ProcAreaEntered",sceneId, selfId, zoneId, MissionId )	

end

function x550522_ProcTiming(sceneId, selfId, ScriptId, MissionId)
	 CallScriptFunction( MISSION_SCRIPT, "ProcTiming",sceneId, selfId, ScriptId, MissionId )
		
end

function x550522_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcAreaLeaved",sceneId, selfId, ScriptId, MissionId)
end



--**********************************

--���߸ı�

--**********************************

function x550522_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcQuestItemChanged",sceneId, selfId, itemdataId, MissionId )
end


function x550522_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x550522_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x550522_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x550522_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x550522_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x550522_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end