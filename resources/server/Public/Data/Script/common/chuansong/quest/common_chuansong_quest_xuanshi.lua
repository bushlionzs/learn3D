--�����͡������������ݹŵ�

--MisDescBegin
x550513_g_ScriptId = 550513
x550513_g_MissionId = 1503
x550513_g_LevelLess	= 	1 
x550513_g_MissionIdPre= -1
x550513_g_MissionIdNext = -1
x550513_g_MissionHelp =	""
x550513_g_MissionName="�������������������ȴ���"
x550513_g_MissionInfo="#cffcf00���Ѿ���ͨ��#G����������������#W#cffcf00���ͣ�#W"  --��������
x550513_g_MissionTarget=""		
x550513_g_MissionCompleted=""					--�������npc˵���Ļ�
x550513_g_ContinueInfo=""

--������
x550513_g_BonusMoney1 =0
x550513_g_BonusMoney2 =0
x550513_g_BonusMoney3 =0
x550513_g_BonusItem	=	{}
x550513_g_BonusChoiceItem ={}
x550513_g_ExpBonus = 0
x550513_g_NpcGUID =0
--MisDescEnd

--**********************************

--������ں���

--**********************************

function x550513_ProcEventEntry(sceneId, selfId, NPCId, MissionId)	--����������ִ�д˽ű�

		return
	
end


--**********************************

--�о��¼�

--**********************************

function x550513_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)


	if GetSceneRelation(sceneId, selfId, sceneId) == 1 then
		if IsQuestHaveDone(sceneId, selfId, x550513_g_MissionId) > 0 then
			return 
		else
				Msg2Player(sceneId,selfId,x550513_g_MissionInfo,8,3)
				QuestCom(sceneId,selfId,MissionId)
		end
	else 
			return
	end		
end



--**********************************

--����������

--**********************************

function x550513_ProcAcceptCheck(sceneId, selfId, NPCId)

end


--**********************************

--���鿴����

--**********************************

function x550513_CheckPushList(sceneId, selfId, NPCId)
	
end

--**********************************

--����

--**********************************

function x550513_ProcQuestAccept( sceneId, selfId, NPCId, MissionId )

end



--**********************************

--����

--**********************************

function x550513_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************
function x550513_CheckSubmit( sceneId, selfId, NPCId)

end


--**********************************

--�ύ

--**********************************
function x550513_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)

end


function x550513_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )

end

--**********************************

--ɱ����������

--**********************************

function x550513_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
	 

end



--**********************************

--���������¼�

--**********************************

function x550513_ProcAreaEntered(sceneId, selfId, zoneId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "ProcAreaEntered",sceneId, selfId, zoneId, MissionId )	

end

function x550513_ProcTiming(sceneId, selfId, ScriptId, MissionId)
	 CallScriptFunction( MISSION_SCRIPT, "ProcTiming",sceneId, selfId, ScriptId, MissionId )
		
end

function x550513_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcAreaLeaved",sceneId, selfId, ScriptId, MissionId)
end



--**********************************

--���߸ı�

--**********************************

function x550513_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcQuestItemChanged",sceneId, selfId, itemdataId, MissionId )
end


function x550513_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x550513_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x550513_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x550513_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x550513_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x550513_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end