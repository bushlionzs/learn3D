--װ������˵��

--MisDescBegin
x800116_g_ScriptId = 800116
--x800116_g_MissionIdPre =-1
--x800116_g_MissionId = 
--x800116_g_MissionKind = 8
--x800116_g_LevelLess	= 	-1 
--x800116_g_MissionIdNext = -1
--x800116_g_Name	="" 
--x800116_g_noDemandItem ={}
--x800116_g_ExtTarget={}
--x800116_g_NeedNum1= 1
--x800116_g_NeedNum2= 1
--x800116_g_NeedNum3= 1
--x800116_g_MissionHelp =	""
x800116_g_MissionName1="����ɫװ������˵����"
x800116_g_MissionInfo1="�߻�������..."  --��������
--x800116_g_MissionInfo2="\t#G����ʯ#W��������ǿ�߷�����Ҫ���ʡ������󽫾������������������������������ռ�#G����ʯ#W������������#G����ʯ#W֮�󣬰��������ң����Եõ�����װ����\n\t����ʯ�һ���װ����Ϊ�������������񴫣��촫���֡�����װ����Ҫ#G��������ʯ#W������װ����Ҫ#G�м�����ʯ#W����װ����Ҫ#G�߼�����ʯ#W���촫װ����Ҫ#G��֮����ʯ#W��\n\t��������Ϊ���һ�����װ������װ�����촫װ����"  --��������
--x800116_g_MissionCompleted1=""--�������npc˵���Ļ�
--x800116_g_MissionCompleted2=""--�������npc˵���Ļ�
--x800116_g_ContinueInfo1="\t�㽫Ҫx800116_g_MissionName5��\n\t���۳���������ʯx800116_g_NeedNum1�š�"
--x800116_g_ContinueInfo2=""
--x800116_g_ContinueInfo3=""
--x800116_g_ErrorInfo1=""
--x800116_g_ErrorInfo2=""
--x800116_g_BonusMoney1 =0
--x800116_g_BonusMoney2 =0
--x800116_g_BonusMoney3 =0
--x800116_g_BonusItem	=	{}
--x800116_g_BonusChoiceItem ={}
--x800116_g_ExpBonus = 250
--x800116_g_SkillHalfHour = 7510
--x800116_g_SkillOneHour = 7511
--MisDescEnd

--**********************************

--������ں���

--**********************************

function x800116_ProcEventEntry(sceneId, selfId, targetId,scriptid,extid)	--����������ִ�д˽ű�
	--����г�����

		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"#Y"..x800116_g_MissionName1)
			AddQuestText(sceneId,x800116_g_MissionInfo1)
		EndQuestEvent()
		DispatchQuestEventList(sceneId, selfId,targetId,x800116_g_ScriptId, x800116_g_MissionName1)

end



--**********************************

--�о��¼�

--**********************************

function x800116_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)

--	local country = GetCurCountry(sceneId, selfId)
--	local nDefaultCamp = GetSceneCamp( sceneId )-16
--
--	if country == nDefaultCamp then 
		AddQuestNumText(sceneId, x800116_g_ScriptId, x800116_g_MissionName1,13,1)
--	else 
--			return
--	end
	
end



--**********************************

--����������

--**********************************

function x800116_ProcAcceptCheck(sceneId, selfId, NPCId)
		return 1
end


--**********************************

--���鿴����

--**********************************

function x800116_CheckPushList(sceneId, selfId, NPCId)
	
end

--**********************************

--����

--**********************************

function x800116_ProcAccept( sceneId, selfId )
	
end



--**********************************

--����

--**********************************

function x800116_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x800116_CheckSubmit( sceneId, selfId, NPCId)


end



--**********************************

--�ύ

--**********************************

function x800116_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)

end



--**********************************

--ɱ����������

--**********************************

function x800116_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x800116_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)
	

end

function x800116_ProcTiming(sceneId, selfId )
	 
		
end

function x800116_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId )
	
end



--**********************************

--���߸ı�

--**********************************

function x800116_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	
end
function x800116_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
	    CallScriptFunction( MISSION_SCRIPT, "ProcQuestAttach",sceneId, selfId, npcId, npcGuid, misIndex, MissionId)
end

function x800116_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x800116_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x800116_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x800116_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x800116_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x800116_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end
