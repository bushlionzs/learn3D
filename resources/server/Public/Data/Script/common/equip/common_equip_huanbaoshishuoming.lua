--��ʯ�滻˵��

--MisDescBegin
x800075_g_ScriptId = 800075
--x800075_g_MissionIdPre =-1
--x800075_g_MissionId = 
--x800075_g_MissionKind = 8
--x800075_g_LevelLess	= 	-1 
--x800075_g_MissionIdNext = -1
--x800075_g_Name	="" 
--x800075_g_noDemandItem ={}
--x800075_g_ExtTarget={}
--x800075_g_NeedNum1= 1
--x800075_g_NeedNum2= 1
--x800075_g_NeedNum3= 1
--x800075_g_MissionHelp =	""
x800075_g_MissionName1="����ʯ�滻˵����"
x800075_g_MissionInfo1="\t��ʯ�滻����ʹ���±�ʯ����װ�������еı�ʯ����ʯ�滻�������ҺͿ���Ƕ�ı�ʯ��\n#Y����˵��#W��\n\t1.������#Gװ����Ƕ��ʦ#W���#Gװ����Ƕ��ʦ#W�Ի���\n\t2.ѡ��#G��ʯ�滻#Wѡ��򿪱�ʯ�滻���档\n\t3.��װ�����뵽��ʯ�滻�������Ϸ������ڡ�\n\t4.����ʯ���뵽�����·�Ҫ�滻���ı�ʯ���ڸ����ڡ�\n\t5.��������·��滻��ť��\n#Yע������#W��\n\t��ʯ�滻��װ����ԭ����Ƕ�ı�ʯ����ʧ����"  --��������
--x800075_g_MissionInfo2="\t#G����ʯ#W��������ǿ�߷�����Ҫ���ʡ������󽫾������������������������������ռ�#G����ʯ#W������������#G����ʯ#W֮�󣬰��������ң����Եõ�����װ����\n\t����ʯ�һ���װ����Ϊ�������������񴫣��촫���֡�����װ����Ҫ#G��������ʯ#W������װ����Ҫ#G�м�����ʯ#W����װ����Ҫ#G�߼�����ʯ#W���촫װ����Ҫ#G��֮����ʯ#W��\n\t��������Ϊ���һ�����װ������װ�����촫װ����"  --��������
--x800075_g_MissionCompleted1=""--�������npc˵���Ļ�
--x800075_g_MissionCompleted2=""--�������npc˵���Ļ�
--x800075_g_ContinueInfo1="\t�㽫Ҫx800075_g_MissionName5��\n\t���۳���������ʯx800075_g_NeedNum1�š�"
--x800075_g_ContinueInfo2=""
--x800075_g_ContinueInfo3=""
--x800075_g_ErrorInfo1=""
--x800075_g_ErrorInfo2=""
--x800075_g_BonusMoney1 =0
--x800075_g_BonusMoney2 =0
--x800075_g_BonusMoney3 =0
--x800075_g_BonusItem	=	{}
--x800075_g_BonusChoiceItem ={}
--x800075_g_ExpBonus = 250
--x800075_g_SkillHalfHour = 7510
--x800075_g_SkillOneHour = 7511
--MisDescEnd

--**********************************

--������ں���

--**********************************

function x800075_ProcEventEntry(sceneId, selfId, targetId,scriptid,extid)	--����������ִ�д˽ű�
	--����г�����

		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"#Y"..x800075_g_MissionName1)
			AddQuestText(sceneId,x800075_g_MissionInfo1)
		EndQuestEvent()
		DispatchQuestEventList(sceneId, selfId,targetId,x800075_g_ScriptId, x800075_g_MissionName1)

end



--**********************************

--�о��¼�

--**********************************

function x800075_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)

--	local country = GetCurCountry(sceneId, selfId)
--	local nDefaultCamp = GetSceneCamp( sceneId )-16
--
--	if country == nDefaultCamp then 
		AddQuestNumText(sceneId, x800075_g_ScriptId, x800075_g_MissionName1,13,1)
--	else 
--			return
--	end
	
end



--**********************************

--����������

--**********************************

function x800075_ProcAcceptCheck(sceneId, selfId, NPCId)
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

function x800075_CheckPushList(sceneId, selfId, NPCId)
	
end

--**********************************

--����

--**********************************

function x800075_ProcAccept( sceneId, selfId )
	
end



--**********************************

--����

--**********************************

function x800075_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x800075_CheckSubmit( sceneId, selfId, NPCId)


end



--**********************************

--�ύ

--**********************************

function x800075_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)

end



--**********************************

--ɱ����������

--**********************************

function x800075_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x800075_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)
	

end

function x800075_ProcTiming(sceneId, selfId )
	 
		
end

function x800075_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId )
	
end



--**********************************

--���߸ı�

--**********************************

function x800075_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	
end
function x800075_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
	    CallScriptFunction( MISSION_SCRIPT, "ProcQuestAttach",sceneId, selfId, npcId, npcGuid, misIndex, MissionId)
end

function x800075_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x800075_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x800075_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x800075_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x800075_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x800075_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end
