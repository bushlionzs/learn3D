--�����͡������ԭ���ϲ�����

--MisDescBegin
x550535_g_ScriptId = 550535
x550535_g_MissionId = 1517
x550535_g_LevelLess	= 	1 
x550535_g_MissionIdPre= -1
x550535_g_MissionIdNext = -1
x550535_g_MissionHelp =	""
x550535_g_MissionName="�����ԭ����������"
x550535_g_MissionInfo="#cffcf00���Ѿ���ͨ��#G��ԭ������#W#cffcf00���ͣ�#W"  --��������
x550535_g_MissionTarget=""		
x550535_g_MissionCompleted=""					--�������npc˵���Ļ�
x550535_g_ContinueInfo=""

--������
x550535_g_BonusMoney1 =0
x550535_g_BonusMoney2 =0
x550535_g_BonusMoney3 =0
x550535_g_BonusItem	=	{}
x550535_g_BonusChoiceItem ={}
x550535_g_ExpBonus = 0
x550535_g_NpcGUID =0
--MisDescEnd

--**********************************

--������ں���

--**********************************

function x550535_ProcEventEntry(sceneId, selfId, NPCId, MissionId)	--����������ִ�д˽ű�

	return
	
	
end


--**********************************

--�о��¼�

--**********************************

function x550535_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)

	if GetSceneRelation(sceneId, selfId, sceneId) == 1 then
		if IsQuestHaveDone(sceneId, selfId, x550535_g_MissionId) > 0 then
			return 
		else
			Msg2Player(sceneId,selfId,x550535_g_MissionInfo,8,3)
			QuestCom(sceneId,selfId,MissionId)
		end
	else 
			return
	end		
end



--**********************************

--����������

--**********************************

function x550535_ProcAcceptCheck(sceneId, selfId, NPCId)

end


--**********************************

--���鿴����

--**********************************

function x550535_CheckPushList(sceneId, selfId, NPCId)
	
end

--**********************************

--����

--**********************************

function x550535_ProcQuestAccept( sceneId, selfId, NPCId, MissionId )

end



--**********************************

--����

--**********************************

function x550535_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************
function x550535_CheckSubmit( sceneId, selfId, NPCId)

end


--**********************************

--�ύ

--**********************************
function x550535_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)

end


function x550535_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )

end

--**********************************

--ɱ����������

--**********************************

function x550535_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
	 

end



--**********************************

--���������¼�

--**********************************

function x550535_ProcAreaEntered(sceneId, selfId, zoneId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "ProcAreaEntered",sceneId, selfId, zoneId, MissionId )	

end

function x550535_ProcTiming(sceneId, selfId, ScriptId, MissionId)
	 CallScriptFunction( MISSION_SCRIPT, "ProcTiming",sceneId, selfId, ScriptId, MissionId )
		
end

function x550535_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcAreaLeaved",sceneId, selfId, ScriptId, MissionId)
end



--**********************************

--���߸ı�

--**********************************

function x550535_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcQuestItemChanged",sceneId, selfId, itemdataId, MissionId )
end


function x550535_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x550535_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x550535_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x550535_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x550535_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x550535_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end