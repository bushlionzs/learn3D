--�����͡����������

--MisDescBegin
x550498_g_ScriptId = 550498
x550498_g_MissionId = 1522
x550498_g_LevelLess	= 	1 
x550498_g_MissionIdPre= -1
x550498_g_MissionIdNext = -1
x550498_g_MissionHelp =	""
x550498_g_MissionName="����󶼴���"
x550498_g_MissionInfo="#cffcf00���Ѿ���ͨ��#G��#W#cffcf00���ͣ�#W"  --��������
x550498_g_MissionTarget=""		
x550498_g_MissionCompleted=""					--�������npc˵���Ļ�
x550498_g_ContinueInfo=""

--������
x550498_g_BonusMoney1 =0
x550498_g_BonusMoney2 =0
x550498_g_BonusMoney3 =0
x550498_g_BonusItem	=	{}
x550498_g_BonusChoiceItem ={}
x550498_g_ExpBonus = 0
x550498_g_NpcGUID =0
--MisDescEnd

--**********************************

--������ں���

--**********************************

function x550498_ProcEventEntry(sceneId, selfId, NPCId, MissionId)	--����������ִ�д˽ű�
			return
	
	
end


--**********************************

--�о��¼�

--**********************************

function x550498_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
		
	--��������ɹ��������
	if IsQuestHaveDone(sceneId, selfId, x550498_g_MissionId) > 0 then
		return 
	else
		Msg2Player(sceneId,selfId,x550498_g_MissionInfo,8,3)
		QuestCom(sceneId,selfId,MissionId)
	end
		
end



--**********************************

--����������

--**********************************

function x550498_ProcAcceptCheck(sceneId, selfId, NPCId)

end


--**********************************

--���鿴����

--**********************************

function x550498_CheckPushList(sceneId, selfId, NPCId)
	
end

--**********************************

--����

--**********************************

function x550498_ProcQuestAccept( sceneId, selfId, NPCId, MissionId )

end



--**********************************

--����

--**********************************

function x550498_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************
function x550498_CheckSubmit( sceneId, selfId, NPCId)

end


--**********************************

--�ύ

--**********************************
function x550498_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)

end


function x550498_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )

end

--**********************************

--ɱ����������

--**********************************

function x550498_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
	 

end



--**********************************

--���������¼�

--**********************************

function x550498_ProcAreaEntered(sceneId, selfId, zoneId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "ProcAreaEntered",sceneId, selfId, zoneId, MissionId )	

end

function x550498_ProcTiming(sceneId, selfId, ScriptId, MissionId)
	 CallScriptFunction( MISSION_SCRIPT, "ProcTiming",sceneId, selfId, ScriptId, MissionId )
		
end

function x550498_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcAreaLeaved",sceneId, selfId, ScriptId, MissionId)
end



--**********************************

--���߸ı�

--**********************************

function x550498_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcQuestItemChanged",sceneId, selfId, itemdataId, MissionId )
end


function x550498_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x550498_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x550498_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x550498_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x550498_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x550498_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end