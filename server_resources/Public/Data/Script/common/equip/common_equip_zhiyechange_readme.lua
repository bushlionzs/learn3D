--�齫����˵��

--MisDescBegin
x800093_g_ScriptId = 800093
--x800093_g_MissionIdPre =-1
--x800093_g_MissionId = 
--x800093_g_MissionKind = 8
--x800093_g_LevelLess	= 	-1 
--x800093_g_MissionIdNext = -1
--x800093_g_Name	="" 
--x800093_g_noDemandItem ={}
--x800093_g_ExtTarget={}
--x800093_g_NeedNum1= 1
--x800093_g_NeedNum2= 1
--x800093_g_NeedNum3= 1
--x800093_g_MissionHelp =	""
x800093_g_MissionName1="��ְҵת��˵����"
x800093_g_MissionInfo1="\t�ڳɼ�˼��2��������6��ְҵ���ҿ��԰���תְΪ��Ӧ����ְҵ��\n\t��ת��ְҵʱ������Ҫһ��#Gְҵת����#W��һ�������Ľ�Ǯ��\n\t����ְҵת����ӦΪ��\n\t#Gͻ����ʿ#W��תְΪ#G���к�ʮ�־�#W\n\t#G���Ͻ���#W��תְΪ#G����ʥ��ʹ#W\n\t#G�ɹ�������#W��תְΪ#G���Ĵ̿�#W\n\t#G��ԭ��ǹ��#W��תְΪ#G�ɹŽ�����#W\n\t#G��˹��֪#W��תְΪ#G˹��������ʿ#W\n\t#Gѩɽ����#W��תְΪ#G��ԭɮ��#W\n#Yע������#W��\n\t��תְ֮�����ԭ�м���Ҳ����֮ת������װ�����ᷢ���仯��������Ҫ����װ��ת������ȡ��ְҵ��װ����"  --��������
--x800093_g_MissionInfo2="\t#G����ʯ#W��������ǿ�߷�����Ҫ���ʡ������󽫾������������������������������ռ�#G����ʯ#W������������#G����ʯ#W֮�󣬰��������ң����Եõ�����װ����\n\t����ʯ�һ���װ����Ϊ�������������񴫣��촫���֡�����װ����Ҫ#G��������ʯ#W������װ����Ҫ#G�м�����ʯ#W����װ����Ҫ#G�߼�����ʯ#W���촫װ����Ҫ#G��֮����ʯ#W��\n\t��������Ϊ���һ�����װ������װ�����촫װ����"  --��������
--x800093_g_MissionCompleted1=""--�������npc˵���Ļ�
--x800093_g_MissionCompleted2=""--�������npc˵���Ļ�
--x800093_g_ContinueInfo1="\t�㽫Ҫx800093_g_MissionName5��\n\t���۳���������ʯx800093_g_NeedNum1�š�"
--x800093_g_ContinueInfo2=""
--x800093_g_ContinueInfo3=""
--x800093_g_ErrorInfo1=""
--x800093_g_ErrorInfo2=""
--x800093_g_BonusMoney1 =0
--x800093_g_BonusMoney2 =0
--x800093_g_BonusMoney3 =0
--x800093_g_BonusItem	=	{}
--x800093_g_BonusChoiceItem ={}
--x800093_g_ExpBonus = 250
--x800093_g_SkillHalfHour = 7510
--x800093_g_SkillOneHour = 7511
--MisDescEnd

--**********************************

--������ں���

--**********************************

function x800093_ProcEventEntry(sceneId, selfId, targetId,scriptid,extid)	--����������ִ�д˽ű�
	--����г�����

		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"#Y"..x800093_g_MissionName1)
			AddQuestText(sceneId,x800093_g_MissionInfo1)
		EndQuestEvent()
		DispatchQuestEventList(sceneId, selfId,targetId,x800093_g_ScriptId, x800093_g_MissionName1)

end



--**********************************

--�о��¼�

--**********************************

function x800093_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)

--	local country = GetCurCountry(sceneId, selfId)
--	local nDefaultCamp = GetSceneCamp( sceneId )-16
--
--	if country == nDefaultCamp then 
		AddQuestNumText(sceneId, x800093_g_ScriptId, x800093_g_MissionName1,13,1)
--	else 
--			return
--	end
	
end



--**********************************

--����������

--**********************************

function x800093_ProcAcceptCheck(sceneId, selfId, NPCId)
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

function x800093_CheckPushList(sceneId, selfId, NPCId)
	
end

--**********************************

--����

--**********************************

function x800093_ProcAccept( sceneId, selfId )
	
end



--**********************************

--����

--**********************************

function x800093_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x800093_CheckSubmit( sceneId, selfId, NPCId)


end



--**********************************

--�ύ

--**********************************

function x800093_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)

end



--**********************************

--ɱ����������

--**********************************

function x800093_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x800093_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)
	

end

function x800093_ProcTiming(sceneId, selfId )
	 
		
end

function x800093_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId )
	
end



--**********************************

--���߸ı�

--**********************************

function x800093_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	
end
function x800093_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
	    CallScriptFunction( MISSION_SCRIPT, "ProcQuestAttach",sceneId, selfId, npcId, npcGuid, misIndex, MissionId)
end

function x800093_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x800093_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x800093_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x800093_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x800093_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x800093_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end
