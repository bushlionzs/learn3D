--�һ���պ���ʯ˵��

--MisDescBegin
x570036_g_ScriptId = 570036
x570036_g_MissionIdPre =-1
--x570036_g_MissionId = 
x570036_g_MissionKind = 8
x570036_g_LevelLess	= 	-1 
x570036_g_MissionIdNext = -1
x570036_g_Name	="" 
x570036_g_noDemandItem ={}
x570036_g_ExtTarget={}
x570036_g_NeedNum1= 1
x570036_g_NeedNum2= 1
x570036_g_NeedNum3= 1
x570036_g_MissionHelp =	""
x570036_g_MissionName1="��ʯԭʯ˵��"
x570036_g_MissionInfo1="\n\t#G��ʯ#W��#G���#W�Ǵ��켫Ʒ��װ���������Եı�Ҫ���ʡ�\n\t#G��ʯԭʯ#W�ǳ�ϡ�У�ֻ���ػ���Ҥ��#G��¼#W������У������ͨ���󶼵�#Gʯ����#W�����Ҥ�����������¼���ܷ�ӵ�����ĵ�����ʮ������󣬱����ʹ��#G������ʯ��#W��#Gԭ����ʯ��#W�����һ���#G��ʯԭʯ#W��\n\t�ҿ��Դ���ʯ��������������Ҫ�ĸ���#G��ʯ#W��#G���#W��"  --��������
--x570036_g_MissionInfo2="\t#G����ʯ#W��������ǿ�߷�����Ҫ���ʡ������󽫾������������������������������ռ�#G����ʯ#W������������#G����ʯ#W֮�󣬰��������ң����Եõ�����װ����\n\t����ʯ�һ���װ����Ϊ�������������񴫣��촫���֡�����װ����Ҫ#G��������ʯ#W������װ����Ҫ#G�м�����ʯ#W����װ����Ҫ#G�߼�����ʯ#W���촫װ����Ҫ#G��֮����ʯ#W��\n\t��������Ϊ���һ�����װ������װ�����촫װ����"  --��������
x570036_g_MissionCompleted1=""--�������npc˵���Ļ�
x570036_g_MissionCompleted2=""--�������npc˵���Ļ�
x570036_g_ContinueInfo1="\t�㽫Ҫx570036_g_MissionName5��\n\t���۳���������ʯx570036_g_NeedNum1�š�"
x570036_g_ContinueInfo2=""
x570036_g_ContinueInfo3=""
x570036_g_ErrorInfo1=""
x570036_g_ErrorInfo2=""
x570036_g_BonusMoney1 =0
x570036_g_BonusMoney2 =0
x570036_g_BonusMoney3 =0
x570036_g_BonusItem	=	{}
x570036_g_BonusChoiceItem ={}
x570036_g_ExpBonus = 250
x570036_g_SkillHalfHour = 7510
x570036_g_SkillOneHour = 7511
--MisDescEnd

--**********************************

--������ں���

--**********************************

function x570036_ProcEventEntry(sceneId, selfId, targetId,scriptid,extid)	--����������ִ�д˽ű�
	--����г�����
	if sceneId ==0 then
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"#Y"..x570036_g_MissionName1)
			AddQuestText(sceneId,x570036_g_MissionInfo1)
		EndQuestEvent()
		DispatchQuestEventList(sceneId, selfId,targetId,x570036_g_ScriptId, x570036_g_MissionName1)
	--else  	
	--	BeginQuestEvent(sceneId)
	--		AddQuestText(sceneId,"#Y"..x570036_g_MissionName1)
	--		AddQuestText(sceneId,x570036_g_MissionInfo1)
	--	EndQuestEvent()
	--	DispatchQuestEventList(sceneId, selfId,targetId,x570036_g_ScriptId, x570036_g_MissionName1)
	end

end



--**********************************

--�о��¼�

--**********************************

function x570036_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)

--	local country = GetCurCountry(sceneId, selfId)
--	local nDefaultCamp = GetSceneCamp( sceneId )-16
--
--	if country == nDefaultCamp then 
		AddQuestNumText(sceneId, x570036_g_ScriptId, x570036_g_MissionName1,13,1)
--	else 
--			return
--	end
	
end



--**********************************

--����������

--**********************************

function x570036_ProcAcceptCheck(sceneId, selfId, NPCId)
	--081217(����)����PKģʽ��PKֵ����0���ܡ���˫��
	local pkMode = GetPlayerPKMode( sceneId, selfId)
	local pkValue = GetPKValue( sceneId, selfId)
	if pkMode ~= 0 or pkValue > 0 then
		BeginQuestEvent( sceneId)
		AddQuestText( sceneId, "����PKģʽ��PKֵ����0���ܻ��˫������" )
		EndQuestEvent()
		DispatchQuestTips( sceneId, selfId)
		return 0
	end

	return 1
end


--**********************************

--���鿴����

--**********************************

function x570036_CheckPushList(sceneId, selfId, NPCId)
	
end

--**********************************

--����

--**********************************

function x570036_ProcAccept( sceneId, selfId )
	
end



--**********************************

--����

--**********************************

function x570036_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x570036_CheckSubmit( sceneId, selfId, NPCId)


end



--**********************************

--�ύ

--**********************************

function x570036_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)

end



--**********************************

--ɱ����������

--**********************************

function x570036_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x570036_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)
	

end

function x570036_ProcTiming(sceneId, selfId )
	 
		
end

function x570036_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId )
	
end



--**********************************

--���߸ı�

--**********************************

function x570036_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	
end
function x570036_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
	    CallScriptFunction( MISSION_SCRIPT, "ProcQuestAttach",sceneId, selfId, npcId, npcGuid, misIndex, MissionId)
end

function x570036_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x570036_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x570036_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x570036_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x570036_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x570036_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end
