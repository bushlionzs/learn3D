--װ������˵��

--MisDescBegin
x310346_g_ScriptId = 310346
--x310346_g_MissionIdPre =-1
--x310346_g_MissionId = 
--x310346_g_MissionKind = 8
--x310346_g_LevelLess	= 	-1 
--x310346_g_MissionIdNext = -1
--x310346_g_Name	="" 
--x310346_g_noDemandItem ={}
--x310346_g_ExtTarget={}
--x310346_g_NeedNum1= 1
--x310346_g_NeedNum2= 1
--x310346_g_NeedNum3= 1
--x310346_g_MissionHelp =	""
x310346_g_MissionName1="����͸��Ʊ˵����"
x310346_g_MissionInfo1="\t���������ο͵�һ�ν��������˼��õ�һ�ź������ֵ���͸��Ʊ��ƾ����͸��Ʊ���Բμ���͸��齱���\n \n#Y��ϸ����#W:\n\t1.ֻ�е����һ�ν����Ӧ�ȼ������˼�Ż�����͸��Ʊ��\n\t2.��͸��Ʊ������Ч����ʧ������\n\t3.ÿ�ο����Ľ�����Ϊ����ֹ������ʱ�䣬���������˼�Ĳ�����Ʊ���롣\n\t4.����ʱ��Ϊ���������յ�10��30��12��30��14��30��16��30��18��30��20��30��22��30��\n\t5.ÿ�Ų�Ʊ�ҽ������ϣ�ϵͳ���ա�\n\t6.δ�н��Ĳ�Ʊ������������١�"  --��������
--x310346_g_MissionInfo2="\t#G����ʯ#W��������ǿ�߷�����Ҫ���ʡ������󽫾������������������������������ռ�#G����ʯ#W������������#G����ʯ#W֮�󣬰��������ң����Եõ�����װ����\n\t����ʯ�һ���װ����Ϊ�������������񴫣��촫���֡�����װ����Ҫ#G��������ʯ#W������װ����Ҫ#G�м�����ʯ#W����װ����Ҫ#G�߼�����ʯ#W���촫װ����Ҫ#G��֮����ʯ#W��\n\t��������Ϊ���һ�����װ������װ�����촫װ����"  --��������
--x310346_g_MissionCompleted1=""--�������npc˵���Ļ�
--x310346_g_MissionCompleted2=""--�������npc˵���Ļ�
--x310346_g_ContinueInfo1="\t�㽫Ҫx310346_g_MissionName5��\n\t���۳���������ʯx310346_g_NeedNum1�š�"
--x310346_g_ContinueInfo2=""
--x310346_g_ContinueInfo3=""
--x310346_g_ErrorInfo1=""
--x310346_g_ErrorInfo2=""
--x310346_g_BonusMoney1 =0
--x310346_g_BonusMoney2 =0
--x310346_g_BonusMoney3 =0
--x310346_g_BonusItem	=	{}
--x310346_g_BonusChoiceItem ={}
--x310346_g_ExpBonus = 250
--x310346_g_SkillHalfHour = 7510
--x310346_g_SkillOneHour = 7511
--MisDescEnd

--**********************************

--������ں���

--**********************************

function x310346_ProcEventEntry(sceneId, selfId, targetId,scriptid,extid)	--����������ִ�д˽ű�
	--����г�����

		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"#Y"..x310346_g_MissionName1)
			AddQuestText(sceneId,x310346_g_MissionInfo1)
		EndQuestEvent()
		DispatchQuestEventList(sceneId, selfId,targetId,x310346_g_ScriptId, x310346_g_MissionName1)

end



--**********************************

--�о��¼�

--**********************************

function x310346_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)

--	local country = GetCurCountry(sceneId, selfId)
--	local nDefaultCamp = GetSceneCamp( sceneId )-16
--
--	if country == nDefaultCamp then 
		AddQuestNumText(sceneId, x310346_g_ScriptId, x310346_g_MissionName1,13,1)
--	else 
--			return
--	end
	
end



--**********************************

--����������

--**********************************

function x310346_ProcAcceptCheck(sceneId, selfId, NPCId)
	--081217(����)����PKģʽ��PKֵ����0���ܡ���˫��
--local pkMode = GetPlayerPKMode( sceneId, selfId)
--local pkValue = GetPKValue( sceneId, selfId)
--if pkMode ~= 0 or pkValue > 0 then
--	BeginQuestEvent( sceneId)
--	AddQuestText( sceneId, "����PKģʽ��PKֵ����0���ܻ��˫������" )
--	EndQuestEvent()
--	DispatchQuestTips( sceneId, selfId)
--	return 0
--end

		return 1
end


--**********************************

--���鿴����

--**********************************

function x310346_CheckPushList(sceneId, selfId, NPCId)
	
end

--**********************************

--����

--**********************************

function x310346_ProcAccept( sceneId, selfId )
	
end



--**********************************

--����

--**********************************

function x310346_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x310346_CheckSubmit( sceneId, selfId, NPCId)


end



--**********************************

--�ύ

--**********************************

function x310346_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)

end



--**********************************

--ɱ����������

--**********************************

function x310346_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x310346_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)
	

end

function x310346_ProcTiming(sceneId, selfId )
	 
		
end

function x310346_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId )
	
end



--**********************************

--���߸ı�

--**********************************

function x310346_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	
end
function x310346_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
	    CallScriptFunction( MISSION_SCRIPT, "ProcQuestAttach",sceneId, selfId, npcId, npcGuid, misIndex, MissionId)
end

function x310346_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x310346_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x310346_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x310346_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x310346_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x310346_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end