--��ʯ��ж˵��

--MisDescBegin
x800076_g_ScriptId = 800076
--x800076_g_MissionIdPre =-1
--x800076_g_MissionId = 
--x800076_g_MissionKind = 8
--x800076_g_LevelLess	= 	-1 
--x800076_g_MissionIdNext = -1
--x800076_g_Name	="" 
--x800076_g_noDemandItem ={}
--x800076_g_ExtTarget={}
--x800076_g_NeedNum1= 1
--x800076_g_NeedNum2= 1
--x800076_g_NeedNum3= 1
--x800076_g_MissionHelp =	""
x800076_g_MissionName1="����ʯ��ж˵����"
x800076_g_MissionInfo1="\t��ʯ��ж���Խ�����Ƕ��װ���ϵı�ʯ��ж��������ʯ��ж�������Һ���ʯ����\n#Y����˵��#W��\n\t1.������#Gװ����Ƕ��ʦ#W���#Gװ����Ƕ��ʦ#W�Ի���\n\t2.ѡ��#G��ʯ��ж#Wѡ��򿪱�ʯ�滻���档\n\t3.��װ�����뵽��ʯ��ж�������Ϸ������ڡ�\n\t4.��������ѡ��Ҫ��ж�ı�ʯ��\n\t5.��������·���ж��ť��\n#Yע������#W��\n\t1.#G��ʯ��#W�ڽ���̳ǣ���ݼ���J�����������ۡ�\n\t2.һƿ��ʯ��ֻ�ܲ��һ�ű�ʯ��"  --��������
--x800076_g_MissionInfo2="\t#G����ʯ#W��������ǿ�߷�����Ҫ���ʡ������󽫾������������������������������ռ�#G����ʯ#W������������#G����ʯ#W֮�󣬰��������ң����Եõ�����װ����\n\t����ʯ�һ���װ����Ϊ�������������񴫣��촫���֡�����װ����Ҫ#G��������ʯ#W������װ����Ҫ#G�м�����ʯ#W����װ����Ҫ#G�߼�����ʯ#W���촫װ����Ҫ#G��֮����ʯ#W��\n\t��������Ϊ���һ�����װ������װ�����촫װ����"  --��������
--x800076_g_MissionCompleted1=""--�������npc˵���Ļ�
--x800076_g_MissionCompleted2=""--�������npc˵���Ļ�
--x800076_g_ContinueInfo1="\t�㽫Ҫx800076_g_MissionName5��\n\t���۳���������ʯx800076_g_NeedNum1�š�"
--x800076_g_ContinueInfo2=""
--x800076_g_ContinueInfo3=""
--x800076_g_ErrorInfo1=""
--x800076_g_ErrorInfo2=""
--x800076_g_BonusMoney1 =0
--x800076_g_BonusMoney2 =0
--x800076_g_BonusMoney3 =0
--x800076_g_BonusItem	=	{}
--x800076_g_BonusChoiceItem ={}
--x800076_g_ExpBonus = 250
--x800076_g_SkillHalfHour = 7510
--x800076_g_SkillOneHour = 7511
--MisDescEnd

--**********************************

--������ں���

--**********************************

function x800076_ProcEventEntry(sceneId, selfId, targetId,scriptid,extid)	--����������ִ�д˽ű�
	--����г�����

		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"#Y"..x800076_g_MissionName1)
			AddQuestText(sceneId,x800076_g_MissionInfo1)
		EndQuestEvent()
		DispatchQuestEventList(sceneId, selfId,targetId,x800076_g_ScriptId, x800076_g_MissionName1)

end



--**********************************

--�о��¼�

--**********************************

function x800076_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)

--	local country = GetCurCountry(sceneId, selfId)
--	local nDefaultCamp = GetSceneCamp( sceneId )-16
--
--	if country == nDefaultCamp then 
		AddQuestNumText(sceneId, x800076_g_ScriptId, x800076_g_MissionName1,13,1)
--	else 
--			return
--	end
	
end



--**********************************

--����������

--**********************************

function x800076_ProcAcceptCheck(sceneId, selfId, NPCId)
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

function x800076_CheckPushList(sceneId, selfId, NPCId)
	
end

--**********************************

--����

--**********************************

function x800076_ProcAccept( sceneId, selfId )
	
end



--**********************************

--����

--**********************************

function x800076_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x800076_CheckSubmit( sceneId, selfId, NPCId)


end



--**********************************

--�ύ

--**********************************

function x800076_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)

end



--**********************************

--ɱ����������

--**********************************

function x800076_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x800076_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)
	

end

function x800076_ProcTiming(sceneId, selfId )
	 
		
end

function x800076_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId )
	
end



--**********************************

--���߸ı�

--**********************************

function x800076_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	
end
function x800076_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
	    CallScriptFunction( MISSION_SCRIPT, "ProcQuestAttach",sceneId, selfId, npcId, npcGuid, misIndex, MissionId)
end

function x800076_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x800076_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x800076_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x800076_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x800076_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x800076_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end
