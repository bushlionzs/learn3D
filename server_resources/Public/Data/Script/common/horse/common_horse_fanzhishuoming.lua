--��˷�ֳ˵��

--MisDescBegin
x570051_g_ScriptId = 570051
--x570051_g_MissionIdPre =-1
--x570051_g_MissionId = 
--x570051_g_MissionKind = 8
--x570051_g_LevelLess	= 	-1 
--x570051_g_MissionIdNext = -1
--x570051_g_Name	="" 
--x570051_g_noDemandItem ={}
--x570051_g_ExtTarget={}
--x570051_g_NeedNum1= 1
--x570051_g_NeedNum2= 1
--x570051_g_NeedNum3= 1
--x570051_g_MissionHelp =	""
x570051_g_MissionName1="����˷�ֳ˵����"
x570051_g_MissionInfo1="\t��˷�ֳ����ͨ������#Gͬ����#W��#Gһ������#W��ˣ���ֳ�����Ը��ߵ�#G����#W��ˡ���˷�ֳ�������ҡ�\n#Y����˵��#W��\n\t1.������#G��˷�ֳ��ʦ#W���#G��˷�ֳ��ʦ#W�Ի���\n\t2.ѡ��#G��˷�ֳ#Wѡ�����˷�ֳ���档\n\t3.����˷�ֳ�������������������ѡ������ˡ�\n\t4.����˷�ֳ�����ҷ��������������ѡ����ˡ�\n#Yע��#W��\n\t1.����˵ȼ����ɵ���60����\n\t2.��ֳ����������˶���ʧȥ��\n\t3.��ֳ�������#G����#W��������˵����ʲ�����������\n\t4.��ֳ������˱�������˵�����#G����#W��\n\t5.��ֳ������˵�#G��ʼ��������#W�͸���˵ĳ�ʼ����һ�¡�\n\t6.��ֳ�������#G�ȼ�#WΪ1����"  --��������
--x570051_g_MissionInfo2="\t#G����ʯ#W��������ǿ�߷�����Ҫ���ʡ������󽫾������������������������������ռ�#G����ʯ#W������������#G����ʯ#W֮�󣬰��������ң����Եõ�����װ����\n\t����ʯ�һ���װ����Ϊ�������������񴫣��촫���֡�����װ����Ҫ#G��������ʯ#W������װ����Ҫ#G�м�����ʯ#W����װ����Ҫ#G�߼�����ʯ#W���촫װ����Ҫ#G��֮����ʯ#W��\n\t��������Ϊ���һ�����װ������װ�����촫װ����"  --��������
--x570051_g_MissionCompleted1=""--�������npc˵���Ļ�
--x570051_g_MissionCompleted2=""--�������npc˵���Ļ�
--x570051_g_ContinueInfo1="\t�㽫Ҫx570051_g_MissionName5��\n\t���۳���������ʯx570051_g_NeedNum1�š�"
--x570051_g_ContinueInfo2=""
--x570051_g_ContinueInfo3=""
--x570051_g_ErrorInfo1=""
--x570051_g_ErrorInfo2=""
--x570051_g_BonusMoney1 =0
--x570051_g_BonusMoney2 =0
--x570051_g_BonusMoney3 =0
--x570051_g_BonusItem	=	{}
--x570051_g_BonusChoiceItem ={}
--x570051_g_ExpBonus = 250
--x570051_g_SkillHalfHour = 7510
--x570051_g_SkillOneHour = 7511
--MisDescEnd

--**********************************

--������ں���

--**********************************

function x570051_ProcEventEntry(sceneId, selfId, targetId,scriptid,extid)	--����������ִ�д˽ű�
	--����г�����

		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"#Y"..x570051_g_MissionName1)
			AddQuestText(sceneId,x570051_g_MissionInfo1)
		EndQuestEvent()
		DispatchQuestEventList(sceneId, selfId,targetId,x570051_g_ScriptId, x570051_g_MissionName1)

end



--**********************************

--�о��¼�

--**********************************

function x570051_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)

--	local country = GetCurCountry(sceneId, selfId)
--	local nDefaultCamp = GetSceneCamp( sceneId )-16
--
--	if country == nDefaultCamp then 
		AddQuestNumText(sceneId, x570051_g_ScriptId, x570051_g_MissionName1,13,1)
--	else 
--			return
--	end
	
end



--**********************************

--����������

--**********************************

function x570051_ProcAcceptCheck(sceneId, selfId, NPCId)
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

function x570051_CheckPushList(sceneId, selfId, NPCId)
	
end

--**********************************

--����

--**********************************

function x570051_ProcAccept( sceneId, selfId )
	
end



--**********************************

--����

--**********************************

function x570051_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x570051_CheckSubmit( sceneId, selfId, NPCId)


end



--**********************************

--�ύ

--**********************************

function x570051_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)

end



--**********************************

--ɱ����������

--**********************************

function x570051_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x570051_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)
	

end

function x570051_ProcTiming(sceneId, selfId )
	 
		
end

function x570051_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId )
	
end



--**********************************

--���߸ı�

--**********************************

function x570051_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	
end
function x570051_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
	    CallScriptFunction( MISSION_SCRIPT, "ProcQuestAttach",sceneId, selfId, npcId, npcGuid, misIndex, MissionId)
end

function x570051_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x570051_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x570051_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x570051_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x570051_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x570051_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end
