--װ����Ƕ˵��

--MisDescBegin
x800074_g_ScriptId = 800074
--x800074_g_MissionIdPre =-1
--x800074_g_MissionId = 
--x800074_g_MissionKind = 8
--x800074_g_LevelLess	= 	-1 
--x800074_g_MissionIdNext = -1
--x800074_g_Name	="" 
--x800074_g_noDemandItem ={}
--x800074_g_ExtTarget={}
--x800074_g_NeedNum1= 1
--x800074_g_NeedNum2= 1
--x800074_g_NeedNum3= 1
--x800074_g_MissionHelp =	""
x800074_g_MissionName1="����ʯ��Ƕ˵����"
x800074_g_MissionInfo1="\t��װ������Ƕ��ʯ����������װ�������ԡ���ʯ��Ƕ�������Һ���Ƕ��ʯ��\n#Y����˵��#W��\n\t1.������#Gװ����Ƕ��ʦ#W���#Gװ����Ƕ��ʦ#W�Ի���\n\t2.ѡ��#G��ʯ��Ƕ#Wѡ��򿪱�ʯ��Ƕ���档\n\t3.��װ�����뵽��ʯ��Ƕ�������Ϸ������ڡ�\n\t4.����ʯ���뵽��ʯ��Ƕ�����·������ڡ�\n\t5.��������·���Ƕ��ť��\n#Yע������#W��\n\t1.#G35������#W����Ҳ���ʹ�ô˹��ܡ�\n\t2.װ���ϱ����п���Ŀף�������Ƕ��ʯ��"  --��������
--x800074_g_MissionInfo2="\t#G����ʯ#W��������ǿ�߷�����Ҫ���ʡ������󽫾������������������������������ռ�#G����ʯ#W������������#G����ʯ#W֮�󣬰��������ң����Եõ�����װ����\n\t����ʯ�һ���װ����Ϊ�������������񴫣��촫���֡�����װ����Ҫ#G��������ʯ#W������װ����Ҫ#G�м�����ʯ#W����װ����Ҫ#G�߼�����ʯ#W���촫װ����Ҫ#G��֮����ʯ#W��\n\t��������Ϊ���һ�����װ������װ�����촫װ����"  --��������
--x800074_g_MissionCompleted1=""--�������npc˵���Ļ�
--x800074_g_MissionCompleted2=""--�������npc˵���Ļ�
--x800074_g_ContinueInfo1="\t�㽫Ҫx800074_g_MissionName5��\n\t���۳���������ʯx800074_g_NeedNum1�š�"
--x800074_g_ContinueInfo2=""
--x800074_g_ContinueInfo3=""
--x800074_g_ErrorInfo1=""
--x800074_g_ErrorInfo2=""
--x800074_g_BonusMoney1 =0
--x800074_g_BonusMoney2 =0
--x800074_g_BonusMoney3 =0
--x800074_g_BonusItem	=	{}
--x800074_g_BonusChoiceItem ={}
--x800074_g_ExpBonus = 250
--x800074_g_SkillHalfHour = 7510
--x800074_g_SkillOneHour = 7511
--MisDescEnd

--**********************************

--������ں���

--**********************************

function x800074_ProcEventEntry(sceneId, selfId, targetId,scriptid,extid)	--����������ִ�д˽ű�
	--����г�����

		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"#Y"..x800074_g_MissionName1)
			AddQuestText(sceneId,x800074_g_MissionInfo1)
		EndQuestEvent()
		DispatchQuestEventList(sceneId, selfId,targetId,x800074_g_ScriptId, x800074_g_MissionName1)

end



--**********************************

--�о��¼�

--**********************************

function x800074_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)

--	local country = GetCurCountry(sceneId, selfId)
--	local nDefaultCamp = GetSceneCamp( sceneId )-16
--
--	if country == nDefaultCamp then 
		AddQuestNumText(sceneId, x800074_g_ScriptId, x800074_g_MissionName1,13,1)
--	else 
--			return
--	end
	
end



--**********************************

--����������

--**********************************

function x800074_ProcAcceptCheck(sceneId, selfId, NPCId)
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

function x800074_CheckPushList(sceneId, selfId, NPCId)
	
end

--**********************************

--����

--**********************************

function x800074_ProcAccept( sceneId, selfId )
	
end



--**********************************

--����

--**********************************

function x800074_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x800074_CheckSubmit( sceneId, selfId, NPCId)


end



--**********************************

--�ύ

--**********************************

function x800074_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)

end



--**********************************

--ɱ����������

--**********************************

function x800074_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x800074_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)
	

end

function x800074_ProcTiming(sceneId, selfId )
	 
		
end

function x800074_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId )
	
end



--**********************************

--���߸ı�

--**********************************

function x800074_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	
end
function x800074_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
	    CallScriptFunction( MISSION_SCRIPT, "ProcQuestAttach",sceneId, selfId, npcId, npcGuid, misIndex, MissionId)
end

function x800074_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x800074_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x800074_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x800074_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x800074_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x800074_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end
