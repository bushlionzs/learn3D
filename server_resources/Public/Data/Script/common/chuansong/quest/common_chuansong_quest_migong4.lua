--�����͡����������Թ��Ĳ�����

--MisDescBegin
x550295_g_ScriptId = 550295
x550295_g_MissionId = 1495
x550295_g_LevelLess	= 	1 
x550295_g_MissionIdPre= -1
x550295_g_MissionIdNext = -1
x550295_g_MissionHelp =	""
x550295_g_MissionName="���������Թ��Ĳ㴫��"
x550295_g_MissionInfo="#cffcf00���Ѿ���ͨ��#G�����Թ��Ĳ�#W#cffcf00���ͣ�#W"  --��������
x550295_g_MissionTarget=""		
x550295_g_MissionCompleted=""					--�������npc˵���Ļ�
x550295_g_ContinueInfo=""

--������
x550295_g_BonusMoney1 =0
x550295_g_BonusMoney2 =0
x550295_g_BonusMoney3 =0
x550295_g_BonusItem	=	{}
x550295_g_BonusChoiceItem ={}
x550295_g_ExpBonus = 0
x550295_g_NpcGUID =0
--MisDescEnd

--**********************************

--������ں���

--**********************************

function x550295_ProcEventEntry(sceneId, selfId, NPCId, MissionId)	--����������ִ�д˽ű�

			return
	
end


--**********************************

--�о��¼�

--**********************************

function x550295_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)

	if GetSceneRelation(sceneId, selfId, sceneId) == 1 then
		if IsQuestHaveDone(sceneId, selfId, x550295_g_MissionId) > 0 then
			return 
		else
				Msg2Player(sceneId,selfId,x550295_g_MissionInfo,8,3)
				QuestCom(sceneId,selfId,MissionId)
		end
	else 
			return
	end		
end



--**********************************

--����������

--**********************************

function x550295_ProcAcceptCheck(sceneId, selfId, NPCId)

end


--**********************************

--���鿴����

--**********************************

function x550295_CheckPushList(sceneId, selfId, NPCId)
	
end

--**********************************

--����

--**********************************

function x550295_ProcQuestAccept( sceneId, selfId, NPCId, MissionId )

end



--**********************************

--����

--**********************************

function x550295_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************
function x550295_CheckSubmit( sceneId, selfId, NPCId)

end


--**********************************

--�ύ

--**********************************
function x550295_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)

end


function x550295_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )

end

--**********************************

--ɱ����������

--**********************************

function x550295_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
	 

end



--**********************************

--���������¼�

--**********************************

function x550295_ProcAreaEntered(sceneId, selfId, zoneId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "ProcAreaEntered",sceneId, selfId, zoneId, MissionId )	

end

function x550295_ProcTiming(sceneId, selfId, ScriptId, MissionId)
	 CallScriptFunction( MISSION_SCRIPT, "ProcTiming",sceneId, selfId, ScriptId, MissionId )
		
end

function x550295_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcAreaLeaved",sceneId, selfId, ScriptId, MissionId)
end



--**********************************

--���߸ı�

--**********************************

function x550295_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcQuestItemChanged",sceneId, selfId, itemdataId, MissionId )
end


function x550295_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x550295_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x550295_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x550295_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x550295_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x550295_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end