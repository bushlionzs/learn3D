--�һ�����ʯ˵��

--MisDescBegin
x570000_g_ScriptId = 570000
x570000_g_MissionIdPre =-1
--x570000_g_MissionId = 
x570000_g_MissionKind = 8
x570000_g_LevelLess	= 	-1 
x570000_g_MissionIdNext = -1
x570000_g_Name	="" 
x570000_g_noDemandItem ={}
x570000_g_ExtTarget={}
x570000_g_NeedNum1= 1
x570000_g_NeedNum2= 1
x570000_g_NeedNum3= 1
x570000_g_MissionHelp =	""
x570000_g_MissionName1="����ʯ�һ�˵��"
x570000_g_MissionInfo1="\t#G����ʯ#W��������ǿ�߷�����Ҫ���ʡ������󽫾������������������������������ռ�#G����ʯ#W������������#G����ʯ#W֮�󣬰��������ң����Եõ�����װ����\n\t����ʯ�һ���װ����Ϊ�������������񴫣��촫��ڤ�����֡�����װ����Ҫ#G��������ʯ#W������װ����Ҫ#G�м�����ʯ#W����װ����Ҫ#G�߼�����ʯ#W���촫װ����Ҫ#G��֮����ʯ#W��ڤ��װ����Ҫ#Gڤ֮����ʯ#W��\n\t��������Ϊ���һ�����װ����"  --��������
x570000_g_MissionInfo2="\t#G����ʯ#W��������ǿ�߷�����Ҫ���ʡ������󽫾������������������������������ռ�#G����ʯ#W������������#G����ʯ#W֮�󣬰��������ң����Եõ�����װ����\n\t����ʯ�һ���װ����Ϊ�������������񴫣��촫��ڤ�����֡�����װ����Ҫ#G��������ʯ#W������װ����Ҫ#G�м�����ʯ#W����װ����Ҫ#G�߼�����ʯ#W���촫װ����Ҫ#G��֮����ʯ#W��ڤ��װ����Ҫ#Gڤ֮����ʯ#W��\n\t��������Ϊ���һ�����װ������װ�����촫װ����ڤ��װ����"  --��������
x570000_g_MissionCompleted1=""--�������npc˵���Ļ�
x570000_g_MissionCompleted2=""--�������npc˵���Ļ�
x570000_g_ContinueInfo1="\t�㽫Ҫx570000_g_MissionName5��\n\t���۳���������ʯx570000_g_NeedNum1�š�"
x570000_g_ContinueInfo2=""
x570000_g_ContinueInfo3=""
x570000_g_ErrorInfo1=""
x570000_g_ErrorInfo2=""
x570000_g_BonusMoney1 =0
x570000_g_BonusMoney2 =0
x570000_g_BonusMoney3 =0
x570000_g_BonusItem	=	{}
x570000_g_BonusChoiceItem ={}
x570000_g_ExpBonus = 250
x570000_g_SkillHalfHour = 7510
x570000_g_SkillOneHour = 7511
--MisDescEnd

--**********************************

--������ں���

--**********************************

function x570000_ProcEventEntry(sceneId, selfId, targetId,scriptid,extid)	--����������ִ�д˽ű�
	--����г�����
	if sceneId ==0 then
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"#Y"..x570000_g_MissionName1)
			AddQuestText(sceneId,x570000_g_MissionInfo2)
		EndQuestEvent()
		DispatchQuestEventList(sceneId, selfId,targetId,x570000_g_ScriptId, x570000_g_MissionName1)
	else  	
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"#Y"..x570000_g_MissionName1)
			AddQuestText(sceneId,x570000_g_MissionInfo1)
		EndQuestEvent()
		DispatchQuestEventList(sceneId, selfId,targetId,x570000_g_ScriptId, x570000_g_MissionName1)
	end

end



--**********************************

--�о��¼�

--**********************************

function x570000_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)

--	local country = GetCurCountry(sceneId, selfId)
--	local nDefaultCamp = GetSceneCamp( sceneId )-16
--
--	if country == nDefaultCamp then 
		AddQuestNumText(sceneId, x570000_g_ScriptId, "��"..x570000_g_MissionName1.."��",0,1)
--	else 
--			return
--	end
	
end



--**********************************

--����������

--**********************************

function x570000_ProcAcceptCheck(sceneId, selfId, NPCId)
	--081217(����)����PKģʽ��PKֵ����0���ܡ���˫��
	local pkMode = GetPlayerPKMode( sceneId, selfId)
	local pkValue = GetPKValue( sceneId, selfId)
	if pkMode ~= 0 or pkValue > 0 then
		BeginQuestEvent( sceneId)
		AddQuestText( sceneId, "����PKģʽ��PKֵ����0���ܻ��˫������" )
		EndQuestEvent()
		DispatchQuestTips( sceneId, selfId)
		return 0
	end

	return 1
end


--**********************************

--���鿴����

--**********************************

function x570000_CheckPushList(sceneId, selfId, NPCId)
	
end

--**********************************

--����

--**********************************

function x570000_ProcAccept( sceneId, selfId )
	
end



--**********************************

--����

--**********************************

function x570000_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x570000_CheckSubmit( sceneId, selfId, NPCId)


end



--**********************************

--�ύ

--**********************************

function x570000_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)

end



--**********************************

--ɱ����������

--**********************************

function x570000_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x570000_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)
	

end

function x570000_ProcTiming(sceneId, selfId )
	 
		
end

function x570000_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId )
	
end



--**********************************

--���߸ı�

--**********************************

function x570000_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	
end
function x570000_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
	    CallScriptFunction( MISSION_SCRIPT, "ProcQuestAttach",sceneId, selfId, npcId, npcGuid, misIndex, MissionId)
end

function x570000_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x570000_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x570000_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x570000_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x570000_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x570000_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end
