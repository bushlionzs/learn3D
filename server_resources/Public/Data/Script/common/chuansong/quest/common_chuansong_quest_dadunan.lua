--�����͡������������

--MisDescBegin
x550497_g_ScriptId = 550497
x550497_g_MissionId = 1524
x550497_g_LevelLess	= 	1 
x550497_g_MissionIdPre= -1
x550497_g_MissionIdNext = -1
x550497_g_MissionHelp =	""
x550497_g_MissionName="����󶼡��ϴ���"
x550497_g_MissionInfo="#cffcf00���Ѿ���ͨ��#G�󶼡���#W#cffcf00���ͣ�#W"  --��������
x550497_g_MissionTarget=""		
x550497_g_MissionCompleted=""					--�������npc˵���Ļ�
x550497_g_ContinueInfo=""

--������
x550497_g_BonusMoney1 =0
x550497_g_BonusMoney2 =0
x550497_g_BonusMoney3 =0
x550497_g_BonusItem	=	{}
x550497_g_BonusChoiceItem ={}
x550497_g_ExpBonus = 0
x550497_g_NpcGUID =0
--MisDescEnd

--**********************************

--������ں���

--**********************************

function x550497_ProcEventEntry(sceneId, selfId, NPCId, MissionId)	--����������ִ�д˽ű�
			return
	
	
end


--**********************************

--�о��¼�

--**********************************

function x550497_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
		
	--��������ɹ��������
	if IsQuestHaveDone(sceneId, selfId, x550497_g_MissionId) > 0 then
		return 
	else
		Msg2Player(sceneId,selfId,x550497_g_MissionInfo,8,3)
		QuestCom(sceneId,selfId,MissionId)
	end
		
end



--**********************************

--����������

--**********************************

function x550497_ProcAcceptCheck(sceneId, selfId, NPCId)

end


--**********************************

--���鿴����

--**********************************

function x550497_CheckPushList(sceneId, selfId, NPCId)
	
end

--**********************************

--����

--**********************************

function x550497_ProcQuestAccept( sceneId, selfId, NPCId, MissionId )

end



--**********************************

--����

--**********************************

function x550497_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************
function x550497_CheckSubmit( sceneId, selfId, NPCId)

end


--**********************************

--�ύ

--**********************************
function x550497_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)

end


function x550497_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )

end

--**********************************

--ɱ����������

--**********************************

function x550497_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
	 

end



--**********************************

--���������¼�

--**********************************

function x550497_ProcAreaEntered(sceneId, selfId, zoneId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "ProcAreaEntered",sceneId, selfId, zoneId, MissionId )	

end

function x550497_ProcTiming(sceneId, selfId, ScriptId, MissionId)
	 CallScriptFunction( MISSION_SCRIPT, "ProcTiming",sceneId, selfId, ScriptId, MissionId )
		
end

function x550497_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcAreaLeaved",sceneId, selfId, ScriptId, MissionId)
end



--**********************************

--���߸ı�

--**********************************

function x550497_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcQuestItemChanged",sceneId, selfId, itemdataId, MissionId )
end


function x550497_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x550497_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x550497_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x550497_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x550497_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x550497_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end