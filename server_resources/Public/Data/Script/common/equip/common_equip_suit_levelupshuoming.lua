--ʱװ����˵��

--MisDescBegin
x800114_g_ScriptId = 800114
--x800114_g_MissionIdPre =-1
--x800114_g_MissionId = 
--x800114_g_MissionKind = 8
--x800114_g_LevelLess	= 	-1 
--x800114_g_MissionIdNext = -1
--x800114_g_Name	="" 
--x800114_g_noDemandItem ={}
--x800114_g_ExtTarget={}
--x800114_g_NeedNum1= 1
--x800114_g_NeedNum2= 1
--x800114_g_NeedNum3= 1
--x800114_g_MissionHelp =	""
x800114_g_MissionName1="��ʱװ����˵����"
x800114_g_MissionInfo1="\tʱװ������������ʱװ�����ԣ���������Խ������������Խ�ߡ�������Ҫ���Ľ���ӡ���ߣ������˼䡤�������ڱ�����ս�����ˡ��콵ħ�������ˡ�ٻŮ�Ļ귢���ˡ���Ƥ���������ˡ�ʱװ������ʦ���һ���������ʱװ������������Σ�����ʱװ��ǿ���ǲ��Զ����ġ�\n \n#Y����˵��#W��\n\t1.��������װ��ʦ������װ��ʦ��������ʱװ������ʦ�Ի���\n\t2.ѡ��ʱװ����ѡ���ʱװ�������档\n\t3.����Ҫ������ʱװ���뵽ʱװ�����������Ϸ������ڡ�\n\t4.ѡ������ʹ�õĵ��ߡ�\n\t5.��������·�������ť��ʼ��ʱװ������\n\t6.�����Ҫʹ���Զ������Ĺ��ܣ��������ѡ���Զ������ȼ����������ڣ�ѡ���Զ������ȼ�������Զ�������ť���ɡ������һ����ӡ����������ѵ�ѡ��ĵȼ�����߼�ʱ�������Զ�ֹͣ������\n \n#Yע������#W��\n\t#G85������#W����Ҳ���ʹ�øù��ܡ�\n\tʱװ����������Σ������ϲ�������ʱ��ÿ������һ����ɹ���"  --��������
--x800114_g_MissionInfo2="\t#G����ʯ#W��������ǿ�߷�����Ҫ���ʡ������󽫾������������������������������ռ�#G����ʯ#W������������#G����ʯ#W֮�󣬰��������ң����Եõ�����װ����\n\t����ʯ�һ���װ����Ϊ�������������񴫣��촫���֡�����װ����Ҫ#G��������ʯ#W������װ����Ҫ#G�м�����ʯ#W����װ����Ҫ#G�߼�����ʯ#W���촫װ����Ҫ#G��֮����ʯ#W��\n\t��������Ϊ���һ�����װ������װ�����촫װ����"  --��������
--x800114_g_MissionCompleted1=""--�������npc˵���Ļ�
--x800114_g_MissionCompleted2=""--�������npc˵���Ļ�
--x800114_g_ContinueInfo1="\t�㽫Ҫx800114_g_MissionName5��\n\t���۳���������ʯx800114_g_NeedNum1�š�"
--x800114_g_ContinueInfo2=""
--x800114_g_ContinueInfo3=""
--x800114_g_ErrorInfo1=""
--x800114_g_ErrorInfo2=""
--x800114_g_BonusMoney1 =0
--x800114_g_BonusMoney2 =0
--x800114_g_BonusMoney3 =0
--x800114_g_BonusItem	=	{}
--x800114_g_BonusChoiceItem ={}
--x800114_g_ExpBonus = 250
--x800114_g_SkillHalfHour = 7510
--x800114_g_SkillOneHour = 7511
--MisDescEnd

--**********************************

--������ں���

--**********************************

function x800114_ProcEventEntry(sceneId, selfId, targetId,scriptid,extid)	--����������ִ�д˽ű�
	--����г�����

		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"#Y"..x800114_g_MissionName1)
			AddQuestText(sceneId,x800114_g_MissionInfo1)
		EndQuestEvent()
		DispatchQuestEventList(sceneId, selfId,targetId,x800114_g_ScriptId, x800114_g_MissionName1)

end



--**********************************

--�о��¼�

--**********************************

function x800114_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)

--	local country = GetCurCountry(sceneId, selfId)
--	local nDefaultCamp = GetSceneCamp( sceneId )-16
--
--	if country == nDefaultCamp then 
		AddQuestNumText(sceneId, x800114_g_ScriptId, x800114_g_MissionName1,13,1)
--	else 
--			return
--	end
	
end



--**********************************

--����������

--**********************************

function x800114_ProcAcceptCheck(sceneId, selfId, NPCId)
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

function x800114_CheckPushList(sceneId, selfId, NPCId)
	
end

--**********************************

--����

--**********************************

function x800114_ProcAccept( sceneId, selfId )
	
end



--**********************************

--����

--**********************************

function x800114_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x800114_CheckSubmit( sceneId, selfId, NPCId)


end



--**********************************

--�ύ

--**********************************

function x800114_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)

end



--**********************************

--ɱ����������

--**********************************

function x800114_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x800114_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)
	

end

function x800114_ProcTiming(sceneId, selfId )
	 
		
end

function x800114_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId )
	
end



--**********************************

--���߸ı�

--**********************************

function x800114_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	
end
function x800114_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
	    CallScriptFunction( MISSION_SCRIPT, "ProcQuestAttach",sceneId, selfId, npcId, npcGuid, misIndex, MissionId)
end

function x800114_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x800114_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x800114_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x800114_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x800114_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x800114_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end
