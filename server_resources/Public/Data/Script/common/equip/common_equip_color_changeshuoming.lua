--װ���̽�˵��

--MisDescBegin
x800083_g_ScriptId = 800083
--x800083_g_MissionIdPre =-1
--x800083_g_MissionId = 
--x800083_g_MissionKind = 8
--x800083_g_LevelLess	= 	-1 
--x800083_g_MissionIdNext = -1
--x800083_g_Name	="" 
--x800083_g_noDemandItem ={}
--x800083_g_ExtTarget={}
--x800083_g_NeedNum1= 1
--x800083_g_NeedNum2= 1
--x800083_g_NeedNum3= 1
--x800083_g_MissionHelp =	""
x800083_g_MissionName1="��װ���̽�ϴ�ϣ�˵����"
x800083_g_MissionInfo1="\tװ���̽�ϴ�ϣ�����Ϊ��ɫװ��������ɫ���ԣ�������Ϊ��ɫװ����װ���̽�ϴ�ϣ��������Һ�ˮ����\n#Y����˵��#W��\n\t1.������#Gװ���̽��ʦ#W���#Gװ���̽��ʦ#W�Ի���\n\t2.ѡ��#Gװ���̽�ϴ�ϣ�#Wѡ�\n\t3.����ɫװ�����뵽װ���̽�ϴ�ϣ��������Ϸ������ڡ�\n\t4.��������·�������ť��\n#Yע������#W��\n\t1.#G60������#W����Ҳ���ʹ�ô˹��ܡ�\n\t2.#G60������#W��װ������ʹ�ô˹��ܡ�\n\t3.ֻ��#G��ɫװ��#W����ʹ�ô˹��ܡ�\n\t4.�̽�ϴ�ϣ�֮��װ����#G���#W�����ɫ���ԡ�"  --��������
--x800083_g_MissionInfo2="\t#G����ʯ#W��������ǿ�߷�����Ҫ���ʡ������󽫾������������������������������ռ�#G����ʯ#W������������#G����ʯ#W֮�󣬰��������ң����Եõ�����װ����\n\t����ʯ�һ���װ����Ϊ�������������񴫣��촫���֡�����װ����Ҫ#G��������ʯ#W������װ����Ҫ#G�м�����ʯ#W����װ����Ҫ#G�߼�����ʯ#W���촫װ����Ҫ#G��֮����ʯ#W��\n\t��������Ϊ���һ�����װ������װ�����촫װ����"  --��������
--x800083_g_MissionCompleted1=""--�������npc˵���Ļ�
--x800083_g_MissionCompleted2=""--�������npc˵���Ļ�
--x800083_g_ContinueInfo1="\t�㽫Ҫx800083_g_MissionName5��\n\t���۳���������ʯx800083_g_NeedNum1�š�"
--x800083_g_ContinueInfo2=""
--x800083_g_ContinueInfo3=""
--x800083_g_ErrorInfo1=""
--x800083_g_ErrorInfo2=""
--x800083_g_BonusMoney1 =0
--x800083_g_BonusMoney2 =0
--x800083_g_BonusMoney3 =0
--x800083_g_BonusItem	=	{}
--x800083_g_BonusChoiceItem ={}
--x800083_g_ExpBonus = 250
--x800083_g_SkillHalfHour = 7510
--x800083_g_SkillOneHour = 7511
--MisDescEnd

--**********************************

--������ں���

--**********************************

function x800083_ProcEventEntry(sceneId, selfId, targetId,scriptid,extid)	--����������ִ�д˽ű�
	--����г�����

		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"#Y"..x800083_g_MissionName1)
			AddQuestText(sceneId,x800083_g_MissionInfo1)
		EndQuestEvent()
		DispatchQuestEventList(sceneId, selfId,targetId,x800083_g_ScriptId, x800083_g_MissionName1)

end



--**********************************

--�о��¼�

--**********************************

function x800083_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)

--	local country = GetCurCountry(sceneId, selfId)
--	local nDefaultCamp = GetSceneCamp( sceneId )-16
--
--	if country == nDefaultCamp then 
		AddQuestNumText(sceneId, x800083_g_ScriptId, x800083_g_MissionName1,13,1)
--	else 
--			return
--	end
	
end



--**********************************

--����������

--**********************************

function x800083_ProcAcceptCheck(sceneId, selfId, NPCId)
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

function x800083_CheckPushList(sceneId, selfId, NPCId)
	
end

--**********************************

--����

--**********************************

function x800083_ProcAccept( sceneId, selfId )
	
end



--**********************************

--����

--**********************************

function x800083_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x800083_CheckSubmit( sceneId, selfId, NPCId)


end



--**********************************

--�ύ

--**********************************

function x800083_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)

end



--**********************************

--ɱ����������

--**********************************

function x800083_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x800083_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)
	

end

function x800083_ProcTiming(sceneId, selfId )
	 
		
end

function x800083_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId )
	
end



--**********************************

--���߸ı�

--**********************************

function x800083_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	
end
function x800083_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
	    CallScriptFunction( MISSION_SCRIPT, "ProcQuestAttach",sceneId, selfId, npcId, npcGuid, misIndex, MissionId)
end

function x800083_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x800083_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x800083_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x800083_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x800083_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x800083_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end
