--�����͡�����ŵ�����

--MisDescBegin
x550294_g_ScriptId = 550294
x550294_g_MissionId = 1494
x550294_g_LevelLess	= 	1 
x550294_g_MissionIdPre= -1
x550294_g_MissionIdNext = -1
x550294_g_MissionHelp =	""
x550294_g_MissionName="���������Թ����㴫��"
x550294_g_MissionInfo="#cffcf00���Ѿ���ͨ��#G�����Թ�����#W#cffcf00���ͣ�#W"  --��������
x550294_g_MissionTarget=""		
x550294_g_MissionCompleted=""					--�������npc˵���Ļ�
x550294_g_ContinueInfo=""

--������
x550294_g_BonusMoney1 =0
x550294_g_BonusMoney2 =0
x550294_g_BonusMoney3 =0
x550294_g_BonusItem	=	{}
x550294_g_BonusChoiceItem ={}
x550294_g_ExpBonus = 0
x550294_g_NpcGUID =0
--MisDescEnd

--**********************************

--������ں���

--**********************************

function x550294_ProcEventEntry(sceneId, selfId, NPCId, MissionId)	--����������ִ�д˽ű�

			return
	
end


--**********************************

--�о��¼�

--**********************************

function x550294_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)

	if GetSceneRelation(sceneId, selfId, sceneId) == 1 then
		if IsQuestHaveDone(sceneId, selfId, x550294_g_MissionId) > 0 then
			return 
		else
				Msg2Player(sceneId,selfId,x550294_g_MissionInfo,8,3)
				QuestCom(sceneId,selfId,MissionId)
		end
	else 
			return
	end		
end



--**********************************

--����������

--**********************************

function x550294_ProcAcceptCheck(sceneId, selfId, NPCId)

end


--**********************************

--���鿴����

--**********************************

function x550294_CheckPushList(sceneId, selfId, NPCId)
	
end

--**********************************

--����

--**********************************

function x550294_ProcQuestAccept( sceneId, selfId, NPCId, MissionId )

end



--**********************************

--����

--**********************************

function x550294_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************
function x550294_CheckSubmit( sceneId, selfId, NPCId)

end


--**********************************

--�ύ

--**********************************
function x550294_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)

end


function x550294_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )

end

--**********************************

--ɱ����������

--**********************************

function x550294_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
	 

end



--**********************************

--���������¼�

--**********************************

function x550294_ProcAreaEntered(sceneId, selfId, zoneId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "ProcAreaEntered",sceneId, selfId, zoneId, MissionId )	

end

function x550294_ProcTiming(sceneId, selfId, ScriptId, MissionId)
	 CallScriptFunction( MISSION_SCRIPT, "ProcTiming",sceneId, selfId, ScriptId, MissionId )
		
end

function x550294_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcAreaLeaved",sceneId, selfId, ScriptId, MissionId)
end



--**********************************

--���߸ı�

--**********************************

function x550294_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcQuestItemChanged",sceneId, selfId, itemdataId, MissionId )
end


function x550294_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x550294_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x550294_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x550294_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x550294_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x550294_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end