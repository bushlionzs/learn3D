--ϴʯ������˵��

--MisDescBegin
x800078_g_ScriptId = 800078
--x800078_g_MissionIdPre =-1
--x800078_g_MissionId = 
--x800078_g_MissionKind = 8
--x800078_g_LevelLess	= 	-1 
--x800078_g_MissionIdNext = -1
--x800078_g_Name	="" 
--x800078_g_noDemandItem ={}
--x800078_g_ExtTarget={}
--x800078_g_NeedNum1= 1
--x800078_g_NeedNum2= 1
--x800078_g_NeedNum3= 1
--x800078_g_MissionHelp =	""
x800078_g_MissionName1="��ϴʯ������˵����"
x800078_g_MissionInfo1="\tϴʯ�����ƿ��Խ�5���͵ȼ���ϴʯ������Ϊ1���ߵȼ���ϴʯ����ϴʯ�������������ҡ�\n#Y����˵��#W��\n\t1.������#Gװ����Ƕ��ʦ#W���#Gװ����Ƕ��ʦ#W�Ի���\n\t2.ѡ��#Gϴʯ������#Wѡ���ϴʯ�����ƽ��档\n\t3.�����ϳɵ�ϴʯ�����뵽ϴʯ�����ƽ������Ϸ������ڡ�\n\t4.��������·����ư�ť��"  --��������
--x800078_g_MissionInfo2="\t#G����ʯ#W��������ǿ�߷�����Ҫ���ʡ������󽫾������������������������������ռ�#G����ʯ#W������������#G����ʯ#W֮�󣬰��������ң����Եõ�����װ����\n\t����ʯ�һ���װ����Ϊ�������������񴫣��촫���֡�����װ����Ҫ#G��������ʯ#W������װ����Ҫ#G�м�����ʯ#W����װ����Ҫ#G�߼�����ʯ#W���촫װ����Ҫ#G��֮����ʯ#W��\n\t��������Ϊ���һ�����װ������װ�����촫װ����"  --��������
--x800078_g_MissionCompleted1=""--�������npc˵���Ļ�
--x800078_g_MissionCompleted2=""--�������npc˵���Ļ�
--x800078_g_ContinueInfo1="\t�㽫Ҫx800078_g_MissionName5��\n\t���۳���������ʯx800078_g_NeedNum1�š�"
--x800078_g_ContinueInfo2=""
--x800078_g_ContinueInfo3=""
--x800078_g_ErrorInfo1=""
--x800078_g_ErrorInfo2=""
--x800078_g_BonusMoney1 =0
--x800078_g_BonusMoney2 =0
--x800078_g_BonusMoney3 =0
--x800078_g_BonusItem	=	{}
--x800078_g_BonusChoiceItem ={}
--x800078_g_ExpBonus = 250
--x800078_g_SkillHalfHour = 7510
--x800078_g_SkillOneHour = 7511
--MisDescEnd

--**********************************

--������ں���

--**********************************

function x800078_ProcEventEntry(sceneId, selfId, targetId,scriptid,extid)	--����������ִ�д˽ű�
	--����г�����

		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"#Y"..x800078_g_MissionName1)
			AddQuestText(sceneId,x800078_g_MissionInfo1)
		EndQuestEvent()
		DispatchQuestEventList(sceneId, selfId,targetId,x800078_g_ScriptId, x800078_g_MissionName1)

end



--**********************************

--�о��¼�

--**********************************

function x800078_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)

--	local country = GetCurCountry(sceneId, selfId)
--	local nDefaultCamp = GetSceneCamp( sceneId )-16
--
--	if country == nDefaultCamp then 
		AddQuestNumText(sceneId, x800078_g_ScriptId, x800078_g_MissionName1,13,1)
--	else 
--			return
--	end
	
end



--**********************************

--����������

--**********************************

function x800078_ProcAcceptCheck(sceneId, selfId, NPCId)
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

function x800078_CheckPushList(sceneId, selfId, NPCId)
	
end

--**********************************

--����

--**********************************

function x800078_ProcAccept( sceneId, selfId )
	
end



--**********************************

--����

--**********************************

function x800078_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x800078_CheckSubmit( sceneId, selfId, NPCId)


end



--**********************************

--�ύ

--**********************************

function x800078_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)

end



--**********************************

--ɱ����������

--**********************************

function x800078_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x800078_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)
	

end

function x800078_ProcTiming(sceneId, selfId )
	 
		
end

function x800078_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId )
	
end



--**********************************

--���߸ı�

--**********************************

function x800078_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	
end
function x800078_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
	    CallScriptFunction( MISSION_SCRIPT, "ProcQuestAttach",sceneId, selfId, npcId, npcGuid, misIndex, MissionId)
end

function x800078_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x800078_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x800078_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x800078_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x800078_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x800078_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end
