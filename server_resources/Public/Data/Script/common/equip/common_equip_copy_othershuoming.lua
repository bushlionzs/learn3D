--װ����ֵ(�缶װ��)˵��

--MisDescBegin
x800087_g_ScriptId = 800087
--x800087_g_MissionIdPre =-1
--x800087_g_MissionId = 
--x800087_g_MissionKind = 8
--x800087_g_LevelLess	= 	-1 
--x800087_g_MissionIdNext = -1
--x800087_g_Name	="" 
--x800087_g_noDemandItem ={}
--x800087_g_ExtTarget={}
--x800087_g_NeedNum1= 1
--x800087_g_NeedNum2= 1
--x800087_g_NeedNum3= 1
--x800087_g_MissionHelp =	""
x800087_g_MissionName1="��װ����ֵ(�缶װ��)˵����"
x800087_g_MissionInfo1="\t�缶װ����ֵ�����Խ�ԭ��װ��������״̬���������״̬���齫����״̬�����״̬����ɫ���������ĸ��Ƶ���װ���ϡ�\n#Y����˵��#W��\n\t1.������#Gװ����ֵ��ʦ#W���#Gװ����ֵ��ʦ#W�Ի���\n\t2.ѡ��#Gװ����ֵ���缶װ����#Wѡ�\n\t3.��ԭ�е�װ������װ����ֵ�������Ϸ������ڡ�\n\t4.����װ������װ����ֵ�����в������ڡ�\n\t5.��������·���ֵ��ť��\n#Yע������#W��\n\tֻ�ܽ�#G�Ѱ�#W��#G��װ��#W��������Ը��Ƶ�#G�켶װ��#W����#G�Ѱ�#W��#G�켶װ��#W��������Ը��Ƶ�#Gڤ��װ��#W����ԭ��װ������Ϊ#G��ɫװ��#W������ֵ��װ����λ������ȫһ�£���ֵ���װ�����Ϊ��װ����"  --��������
--x800087_g_MissionInfo2="\t#G����ʯ#W��������ǿ�߷�����Ҫ���ʡ������󽫾������������������������������ռ�#G����ʯ#W������������#G����ʯ#W֮�󣬰��������ң����Եõ�����װ����\n\t����ʯ�һ���װ����Ϊ�������������񴫣��촫���֡�����װ����Ҫ#G��������ʯ#W������װ����Ҫ#G�м�����ʯ#W����װ����Ҫ#G�߼�����ʯ#W���촫װ����Ҫ#G��֮����ʯ#W��\n\t��������Ϊ���һ�����װ������װ�����촫װ����"  --��������
--x800087_g_MissionCompleted1=""--�������npc˵���Ļ�
--x800087_g_MissionCompleted2=""--�������npc˵���Ļ�
--x800087_g_ContinueInfo1="\t�㽫Ҫx800087_g_MissionName5��\n\t���۳���������ʯx800087_g_NeedNum1�š�"
--x800087_g_ContinueInfo2=""
--x800087_g_ContinueInfo3=""
--x800087_g_ErrorInfo1=""
--x800087_g_ErrorInfo2=""
--x800087_g_BonusMoney1 =0
--x800087_g_BonusMoney2 =0
--x800087_g_BonusMoney3 =0
--x800087_g_BonusItem	=	{}
--x800087_g_BonusChoiceItem ={}
--x800087_g_ExpBonus = 250
--x800087_g_SkillHalfHour = 7510
--x800087_g_SkillOneHour = 7511
--MisDescEnd

--**********************************

--������ں���

--**********************************

function x800087_ProcEventEntry(sceneId, selfId, targetId,scriptid,extid)	--����������ִ�д˽ű�
	--����г�����

		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"#Y"..x800087_g_MissionName1)
			AddQuestText(sceneId,x800087_g_MissionInfo1)
		EndQuestEvent()
		DispatchQuestEventList(sceneId, selfId,targetId,x800087_g_ScriptId, x800087_g_MissionName1)

end



--**********************************

--�о��¼�

--**********************************

function x800087_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)

--	local country = GetCurCountry(sceneId, selfId)
--	local nDefaultCamp = GetSceneCamp( sceneId )-16
--
--	if country == nDefaultCamp then 
		AddQuestNumText(sceneId, x800087_g_ScriptId, x800087_g_MissionName1,13,1)
--	else 
--			return
--	end
	
end



--**********************************

--����������

--**********************************

function x800087_ProcAcceptCheck(sceneId, selfId, NPCId)
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

function x800087_CheckPushList(sceneId, selfId, NPCId)
	
end

--**********************************

--����

--**********************************

function x800087_ProcAccept( sceneId, selfId )
	
end



--**********************************

--����

--**********************************

function x800087_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x800087_CheckSubmit( sceneId, selfId, NPCId)


end



--**********************************

--�ύ

--**********************************

function x800087_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)

end



--**********************************

--ɱ����������

--**********************************

function x800087_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x800087_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)
	

end

function x800087_ProcTiming(sceneId, selfId )
	 
		
end

function x800087_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId )
	
end



--**********************************

--���߸ı�

--**********************************

function x800087_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	
end
function x800087_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
	    CallScriptFunction( MISSION_SCRIPT, "ProcQuestAttach",sceneId, selfId, npcId, npcGuid, misIndex, MissionId)
end

function x800087_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x800087_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x800087_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x800087_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x800087_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x800087_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end
