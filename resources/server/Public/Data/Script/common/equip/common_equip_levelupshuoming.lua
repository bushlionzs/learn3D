--װ������˵��

--MisDescBegin
x800072_g_ScriptId = 800072
--x800072_g_MissionIdPre =-1
--x800072_g_MissionId = 
--x800072_g_MissionKind = 8
--x800072_g_LevelLess	= 	-1 
--x800072_g_MissionIdNext = -1
--x800072_g_Name	="" 
--x800072_g_noDemandItem ={}
--x800072_g_ExtTarget={}
--x800072_g_NeedNum1= 1
--x800072_g_NeedNum2= 1
--x800072_g_NeedNum3= 1
--x800072_g_MissionHelp =	""
x800072_g_MissionName1="��װ������˵����"
x800072_g_MissionInfo1="\tװ�����ǿ�������װ���Ļ������ԣ��Ǽ�Խ������������Խ�ࡣ������Ҫ�������ҡ�ˮ������ʯ��\n#Y����˵��#W��\n\t1.������#Gװ�����Ǵ�ʦ#W���#Gװ�����Ǵ�ʦ#W�Ի���\n\t2.ѡ��#Gװ������#Wѡ���װ�����ǽ��档\n\t3.����Ҫ���ǵ�װ�����뵽װ�����ǽ������Ϸ������ڡ�\n\t4.��ѡ��ʯ�����������ڣ�ѡ������ʹ�õı�ʯ��\n\t5.��������·����ǰ�ť��ʼ��װ�����ǡ�\n\t6.�����Ҫʹ���Զ����ǵĹ��ܣ��������ѡ���Զ����ǵȼ����������ڣ�ѡ���Զ����ǵȼ�������Զ����ǰ�ť���ɣ������һ�ˮ������ʯ���㣬��װ����������ѡ��ĵȼ����Զ����ǽ����Զ�ֹͣ��\n#Yע������#W��\n\t1.װ��ǰ���ǵ�����һ���ɹ����������Ǽ��������϶�#G�м�������ʧ��#W��\n\t2.ʹ��#Gˮ��#W��װ�����ǣ���4������ʱʧ�ܣ�װ���Ǽ����˵�3�ǡ�\n\t3.ʹ��#G��ʯ#W��װ�����ǣ�����ʧ��ʱ��װ���Ǽ������½�����������ǰ�ȼ���"  --��������
--x800072_g_MissionInfo2="\t#G����ʯ#W��������ǿ�߷�����Ҫ���ʡ������󽫾������������������������������ռ�#G����ʯ#W������������#G����ʯ#W֮�󣬰��������ң����Եõ�����װ����\n\t����ʯ�һ���װ����Ϊ�������������񴫣��촫���֡�����װ����Ҫ#G��������ʯ#W������װ����Ҫ#G�м�����ʯ#W����װ����Ҫ#G�߼�����ʯ#W���촫װ����Ҫ#G��֮����ʯ#W��\n\t��������Ϊ���һ�����װ������װ�����촫װ����"  --��������
--x800072_g_MissionCompleted1=""--�������npc˵���Ļ�
--x800072_g_MissionCompleted2=""--�������npc˵���Ļ�
--x800072_g_ContinueInfo1="\t�㽫Ҫx800072_g_MissionName5��\n\t���۳���������ʯx800072_g_NeedNum1�š�"
--x800072_g_ContinueInfo2=""
--x800072_g_ContinueInfo3=""
--x800072_g_ErrorInfo1=""
--x800072_g_ErrorInfo2=""
--x800072_g_BonusMoney1 =0
--x800072_g_BonusMoney2 =0
--x800072_g_BonusMoney3 =0
--x800072_g_BonusItem	=	{}
--x800072_g_BonusChoiceItem ={}
--x800072_g_ExpBonus = 250
--x800072_g_SkillHalfHour = 7510
--x800072_g_SkillOneHour = 7511
--MisDescEnd

--**********************************

--������ں���

--**********************************

function x800072_ProcEventEntry(sceneId, selfId, targetId,scriptid,extid)	--����������ִ�д˽ű�
	--����г�����

		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"#Y"..x800072_g_MissionName1)
			AddQuestText(sceneId,x800072_g_MissionInfo1)
		EndQuestEvent()
		DispatchQuestEventList(sceneId, selfId,targetId,x800072_g_ScriptId, x800072_g_MissionName1)

end



--**********************************

--�о��¼�

--**********************************

function x800072_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)

--	local country = GetCurCountry(sceneId, selfId)
--	local nDefaultCamp = GetSceneCamp( sceneId )-16
--
--	if country == nDefaultCamp then 
		AddQuestNumText(sceneId, x800072_g_ScriptId, x800072_g_MissionName1,13,1)
--	else 
--			return
--	end
	
end



--**********************************

--����������

--**********************************

function x800072_ProcAcceptCheck(sceneId, selfId, NPCId)
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

function x800072_CheckPushList(sceneId, selfId, NPCId)
	
end

--**********************************

--����

--**********************************

function x800072_ProcAccept( sceneId, selfId )
	
end



--**********************************

--����

--**********************************

function x800072_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x800072_CheckSubmit( sceneId, selfId, NPCId)


end



--**********************************

--�ύ

--**********************************

function x800072_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)

end



--**********************************

--ɱ����������

--**********************************

function x800072_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x800072_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)
	

end

function x800072_ProcTiming(sceneId, selfId )
	 
		
end

function x800072_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId )
	
end



--**********************************

--���߸ı�

--**********************************

function x800072_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	
end
function x800072_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
	    CallScriptFunction( MISSION_SCRIPT, "ProcQuestAttach",sceneId, selfId, npcId, npcGuid, misIndex, MissionId)
end

function x800072_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x800072_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x800072_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x800072_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x800072_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x800072_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end
