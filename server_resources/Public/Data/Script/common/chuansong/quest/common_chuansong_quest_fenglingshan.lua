--�����͡������ԭ���ղ�����

--MisDescBegin
x550533_g_ScriptId = 550533
x550533_g_MissionId = 1515
x550533_g_LevelLess	= 	1 
x550533_g_MissionIdPre= -1
x550533_g_MissionIdNext = -1
x550533_g_MissionHelp =	""
x550533_g_MissionName="�����ԭ���ղ�����"
x550533_g_MissionInfo="#cffcf00���Ѿ���ͨ��#G��ԭ���ղ�#W#cffcf00���ͣ�#W"  --��������
x550533_g_MissionTarget=""		
x550533_g_MissionCompleted=""					--�������npc˵���Ļ�
x550533_g_ContinueInfo=""

--������
x550533_g_BonusMoney1 =0
x550533_g_BonusMoney2 =0
x550533_g_BonusMoney3 =0
x550533_g_BonusItem	=	{}
x550533_g_BonusChoiceItem ={}
x550533_g_ExpBonus = 0
x550533_g_NpcGUID =0
--MisDescEnd

--**********************************

--������ں���

--**********************************

function x550533_ProcEventEntry(sceneId, selfId, NPCId, MissionId)	--����������ִ�д˽ű�

		return
end


--**********************************

--�о��¼�

--**********************************

function x550533_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)

	if GetSceneRelation(sceneId, selfId, sceneId) == 1 then
		if IsQuestHaveDone(sceneId, selfId, x550533_g_MissionId) > 0 then
			return 
		else
				Msg2Player(sceneId,selfId,x550533_g_MissionInfo,8,3)
				QuestCom(sceneId,selfId,MissionId)
		end
	else 
			return
	end		
end



--**********************************

--����������

--**********************************

function x550533_ProcAcceptCheck(sceneId, selfId, NPCId)

end


--**********************************

--���鿴����

--**********************************

function x550533_CheckPushList(sceneId, selfId, NPCId)
	
end

--**********************************

--����

--**********************************

function x550533_ProcQuestAccept( sceneId, selfId, NPCId, MissionId )

end



--**********************************

--����

--**********************************

function x550533_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************
function x550533_CheckSubmit( sceneId, selfId, NPCId)

end


--**********************************

--�ύ

--**********************************
function x550533_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)

end


function x550533_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )

end

--**********************************

--ɱ����������

--**********************************

function x550533_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
	 

end



--**********************************

--���������¼�

--**********************************

function x550533_ProcAreaEntered(sceneId, selfId, zoneId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "ProcAreaEntered",sceneId, selfId, zoneId, MissionId )	

end

function x550533_ProcTiming(sceneId, selfId, ScriptId, MissionId)
	 CallScriptFunction( MISSION_SCRIPT, "ProcTiming",sceneId, selfId, ScriptId, MissionId )
		
end

function x550533_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcAreaLeaved",sceneId, selfId, ScriptId, MissionId)
end



--**********************************

--���߸ı�

--**********************************

function x550533_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcQuestItemChanged",sceneId, selfId, itemdataId, MissionId )
end


function x550533_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x550533_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x550533_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x550533_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x550533_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x550533_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end