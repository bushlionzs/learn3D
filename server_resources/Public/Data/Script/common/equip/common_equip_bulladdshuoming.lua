--�������ɫ˵��

--MisDescBegin
x800082_g_ScriptId = 800082
--x800082_g_MissionIdPre =-1
--x800082_g_MissionId = 
--x800082_g_MissionKind = 8
--x800082_g_LevelLess	= 	-1 
--x800082_g_MissionIdNext = -1
--x800082_g_Name	="" 
--x800082_g_noDemandItem ={}
--x800082_g_ExtTarget={}
--x800082_g_NeedNum1= 1
--x800082_g_NeedNum2= 1
--x800082_g_NeedNum3= 1
--x800082_g_MissionHelp =	""
x800082_g_MissionName1="���������ɫ˵����"
x800082_g_MissionInfo1="\t�������ɫ���Խ��������յ���ɫ������ӵ�������ϡ��������ɫ�������Һͷ��ġ�\n#Y����˵��#W��\n\t1.������#G��װ��ʦ#W���#G��װ��ʦ#W�Ի���\n\t2.ѡ��#G�������ɫ#Wѡ�\n\t3.����������뵽�������ɫ�������Ϸ������ڡ�\n\t4.�����ķ��뵽�������ɫ�����·������ڡ�\n\t5.��������·���ɫ��ť��\n#Yע������#W��\n\tһ�������������ɫ����ͬ�ַ��ġ�"  --��������
--x800082_g_MissionInfo2="\t#G����ʯ#W��������ǿ�߷�����Ҫ���ʡ������󽫾������������������������������ռ�#G����ʯ#W������������#G����ʯ#W֮�󣬰��������ң����Եõ�����װ����\n\t����ʯ�һ���װ����Ϊ�������������񴫣��촫���֡�����װ����Ҫ#G��������ʯ#W������װ����Ҫ#G�м�����ʯ#W����װ����Ҫ#G�߼�����ʯ#W���촫װ����Ҫ#G��֮����ʯ#W��\n\t��������Ϊ���һ�����װ������װ�����촫װ����"  --��������
--x800082_g_MissionCompleted1=""--�������npc˵���Ļ�
--x800082_g_MissionCompleted2=""--�������npc˵���Ļ�
--x800082_g_ContinueInfo1="\t�㽫Ҫx800082_g_MissionName5��\n\t���۳���������ʯx800082_g_NeedNum1�š�"
--x800082_g_ContinueInfo2=""
--x800082_g_ContinueInfo3=""
--x800082_g_ErrorInfo1=""
--x800082_g_ErrorInfo2=""
--x800082_g_BonusMoney1 =0
--x800082_g_BonusMoney2 =0
--x800082_g_BonusMoney3 =0
--x800082_g_BonusItem	=	{}
--x800082_g_BonusChoiceItem ={}
--x800082_g_ExpBonus = 250
--x800082_g_SkillHalfHour = 7510
--x800082_g_SkillOneHour = 7511
--MisDescEnd

--**********************************

--������ں���

--**********************************

function x800082_ProcEventEntry(sceneId, selfId, targetId,scriptid,extid)	--����������ִ�д˽ű�
	--����г�����

		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"#Y"..x800082_g_MissionName1)
			AddQuestText(sceneId,x800082_g_MissionInfo1)
		EndQuestEvent()
		DispatchQuestEventList(sceneId, selfId,targetId,x800082_g_ScriptId, x800082_g_MissionName1)

end



--**********************************

--�о��¼�

--**********************************

function x800082_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)

--	local country = GetCurCountry(sceneId, selfId)
--	local nDefaultCamp = GetSceneCamp( sceneId )-16
--
--	if country == nDefaultCamp then 
		AddQuestNumText(sceneId, x800082_g_ScriptId, x800082_g_MissionName1,13,1)
--	else 
--			return
--	end
	
end



--**********************************

--����������

--**********************************

function x800082_ProcAcceptCheck(sceneId, selfId, NPCId)
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

function x800082_CheckPushList(sceneId, selfId, NPCId)
	
end

--**********************************

--����

--**********************************

function x800082_ProcAccept( sceneId, selfId )
	
end



--**********************************

--����

--**********************************

function x800082_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x800082_CheckSubmit( sceneId, selfId, NPCId)


end



--**********************************

--�ύ

--**********************************

function x800082_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)

end



--**********************************

--ɱ����������

--**********************************

function x800082_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x800082_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)
	

end

function x800082_ProcTiming(sceneId, selfId )
	 
		
end

function x800082_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId )
	
end



--**********************************

--���߸ı�

--**********************************

function x800082_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	
end
function x800082_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
	    CallScriptFunction( MISSION_SCRIPT, "ProcQuestAttach",sceneId, selfId, npcId, npcGuid, misIndex, MissionId)
end

function x800082_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x800082_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x800082_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x800082_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x800082_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x800082_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end
