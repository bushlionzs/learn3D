--װ���̽�˵��

--MisDescBegin
x570049_g_ScriptId = 570049
--x570049_g_MissionIdPre =-1
--x570049_g_MissionId = 
--x570049_g_MissionKind = 8
--x570049_g_LevelLess	= 	-1 
--x570049_g_MissionIdNext = -1
--x570049_g_Name	="" 
--x570049_g_noDemandItem ={}
--x570049_g_ExtTarget={}
--x570049_g_NeedNum1= 1
--x570049_g_NeedNum2= 1
--x570049_g_NeedNum3= 1
--x570049_g_MissionHelp =	""
x570049_g_MissionName1="���츳����˵����"
x570049_g_MissionInfo1="\t#W�츳�ȼ����ӣ������������������Ƽ��ܵ������ʣ����ͶԷ���ҿ��Ƽ��ܵ������ʡ�70�����ϵ���Ҳſ��Կ�ʼ�����츳��������������츳�ȼ���������ӵ����򲻵�֮�£�\n#Y����˵��#W��\n\t1.���#G�츳������ʦ#W�Ի���\n\t2.ѡ��#G�츳����#Wѡ�\n\t3.��������·�#Gȷ��#W��ť��\n#Yע������#W��\n\t1.�츳�ȼ�����Ϊ����ҵȼ�-69��*4��\n\t2.�����츳Ҫ����һ���ľ���ͽ�Ǯ��"  --��������
--x570049_g_MissionInfo2="\t#G����ʯ#W��������ǿ�߷�����Ҫ���ʡ������󽫾������������������������������ռ�#G����ʯ#W������������#G����ʯ#W֮�󣬰��������ң����Եõ�����װ����\n\t����ʯ�һ���װ����Ϊ�������������񴫣��촫���֡�����װ����Ҫ#G��������ʯ#W������װ����Ҫ#G�м�����ʯ#W����װ����Ҫ#G�߼�����ʯ#W���촫װ����Ҫ#G��֮����ʯ#W��\n\t��������Ϊ���һ�����װ������װ�����촫װ����"  --��������
--x570049_g_MissionCompleted1=""--�������npc˵���Ļ�
--x570049_g_MissionCompleted2=""--�������npc˵���Ļ�
--x570049_g_ContinueInfo1="\t�㽫Ҫx570049_g_MissionName5��\n\t���۳���������ʯx570049_g_NeedNum1�š�"
--x570049_g_ContinueInfo2=""
--x570049_g_ContinueInfo3=""
--x570049_g_ErrorInfo1=""
--x570049_g_ErrorInfo2=""
--x570049_g_BonusMoney1 =0
--x570049_g_BonusMoney2 =0
--x570049_g_BonusMoney3 =0
--x570049_g_BonusItem	=	{}
--x570049_g_BonusChoiceItem ={}
--x570049_g_ExpBonus = 250
--x570049_g_SkillHalfHour = 7510
--x570049_g_SkillOneHour = 7511
--MisDescEnd

--**********************************

--������ں���

--**********************************

function x570049_ProcEventEntry(sceneId, selfId, targetId,scriptid,extid)	--����������ִ�д˽ű�
	--����г�����

		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"#Y"..x570049_g_MissionName1)
			AddQuestText(sceneId,x570049_g_MissionInfo1)
		EndQuestEvent()
		DispatchQuestEventList(sceneId, selfId,targetId,x570049_g_ScriptId, x570049_g_MissionName1)

end



--**********************************

--�о��¼�

--**********************************

function x570049_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)

--	local country = GetCurCountry(sceneId, selfId)
--	local nDefaultCamp = GetSceneCamp( sceneId )-16
--
--	if country == nDefaultCamp then 
		AddQuestNumText(sceneId, x570049_g_ScriptId, x570049_g_MissionName1,13,1)
--	else 
--			return
--	end
	
end



--**********************************

--����������

--**********************************

function x570049_ProcAcceptCheck(sceneId, selfId, NPCId)
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

function x570049_CheckPushList(sceneId, selfId, NPCId)
	
end

--**********************************

--����

--**********************************

function x570049_ProcAccept( sceneId, selfId )
	
end



--**********************************

--����

--**********************************

function x570049_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x570049_CheckSubmit( sceneId, selfId, NPCId)


end



--**********************************

--�ύ

--**********************************

function x570049_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)

end



--**********************************

--ɱ����������

--**********************************

function x570049_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x570049_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)
	

end

function x570049_ProcTiming(sceneId, selfId )
	 
		
end

function x570049_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId )
	
end



--**********************************

--���߸ı�

--**********************************

function x570049_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	
end
function x570049_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
	    CallScriptFunction( MISSION_SCRIPT, "ProcQuestAttach",sceneId, selfId, npcId, npcGuid, misIndex, MissionId)
end

function x570049_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x570049_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x570049_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x570049_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x570049_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x570049_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end
