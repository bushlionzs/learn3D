--�һ����˵��

--MisDescBegin
x570037_g_ScriptId = 570037
x570037_g_MissionIdPre =-1
--x570037_g_MissionId = 
x570037_g_MissionKind = 8
x570037_g_LevelLess	= 	-1 
x570037_g_MissionIdNext = -1
x570037_g_Name	="" 
x570037_g_noDemandItem ={}
x570037_g_ExtTarget={}
x570037_g_NeedNum1= 1
x570037_g_NeedNum2= 1
x570037_g_NeedNum3= 1
x570037_g_MissionHelp =	""
x570037_g_MissionName1="��նһ�˵��"
x570037_g_MissionInfo1="\n\t#G��ʯ#W��#G���#W�Ǵ��켫Ʒ��װ���������Եı�Ҫ���ʡ��ҿ��Խ�#G��ʯ#W�һ���#G���#W����տ����ڲ�����75����װ����9������10�ǣ�����ʧ�ܺ�װ���Ǽ������½���\n\t��յĶһ���ʽ�ܼ򵥣�ֻҪ�����һ��#G��ʯ#W��һ�������Ĳ��ϣ�����#Gҹ����#W�ȣ��ҾͿ��Ը���һ�����Ӧ��#G���#W��\n\t��û�����ף��ٸ����Ӱɣ���������һ��#G������ʯ#W��#Gҹ����#W���Ϳ��Դ�������һ���һ��#G�������#W����������һ��#Gˮ����ʯ#W��#Gҹ����#W���ҾͿ��Ը���һ���һ��#Gˮ����#W���Դ����ơ�"  --��������
--x570037_g_MissionInfo2="\t#G����ʯ#W��������ǿ�߷�����Ҫ���ʡ������󽫾������������������������������ռ�#G����ʯ#W������������#G����ʯ#W֮�󣬰��������ң����Եõ�����װ����\n\t����ʯ�һ���װ����Ϊ�������������񴫣��촫���֡�����װ����Ҫ#G��������ʯ#W������װ����Ҫ#G�м�����ʯ#W����װ����Ҫ#G�߼�����ʯ#W���촫װ����Ҫ#G��֮����ʯ#W��\n\t��������Ϊ���һ�����װ������װ�����촫װ����"  --��������
x570037_g_MissionCompleted1=""--�������npc˵���Ļ�
x570037_g_MissionCompleted2=""--�������npc˵���Ļ�
x570037_g_ContinueInfo1="\t�㽫Ҫx570037_g_MissionName5��\n\t���۳���������ʯx570037_g_NeedNum1�š�"
x570037_g_ContinueInfo2=""
x570037_g_ContinueInfo3=""
x570037_g_ErrorInfo1=""
x570037_g_ErrorInfo2=""
x570037_g_BonusMoney1 =0
x570037_g_BonusMoney2 =0
x570037_g_BonusMoney3 =0
x570037_g_BonusItem	=	{}
x570037_g_BonusChoiceItem ={}
x570037_g_ExpBonus = 250
x570037_g_SkillHalfHour = 7510
x570037_g_SkillOneHour = 7511
--MisDescEnd

--**********************************

--������ں���

--**********************************

function x570037_ProcEventEntry(sceneId, selfId, targetId,scriptid,extid)	--����������ִ�д˽ű�
	--����г�����
	if sceneId ==0 then
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"#Y"..x570037_g_MissionName1)
			AddQuestText(sceneId,x570037_g_MissionInfo1)
		EndQuestEvent()
		DispatchQuestEventList(sceneId, selfId,targetId,x570037_g_ScriptId, x570037_g_MissionName1)
	--else  	
	--	BeginQuestEvent(sceneId)
	--		AddQuestText(sceneId,"#Y"..x570037_g_MissionName1)
	--		AddQuestText(sceneId,x570037_g_MissionInfo1)
	--	EndQuestEvent()
	--	DispatchQuestEventList(sceneId, selfId,targetId,x570037_g_ScriptId, x570037_g_MissionName1)
	end

end



--**********************************

--�о��¼�

--**********************************

function x570037_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)

--	local country = GetCurCountry(sceneId, selfId)
--	local nDefaultCamp = GetSceneCamp( sceneId )-16
--
--	if country == nDefaultCamp then 
		AddQuestNumText(sceneId, x570037_g_ScriptId, x570037_g_MissionName1,13,1)
--	else 
--			return
--	end
	
end



--**********************************

--����������

--**********************************

function x570037_ProcAcceptCheck(sceneId, selfId, NPCId)
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

function x570037_CheckPushList(sceneId, selfId, NPCId)
	
end

--**********************************

--����

--**********************************

function x570037_ProcAccept( sceneId, selfId )
	
end



--**********************************

--����

--**********************************

function x570037_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x570037_CheckSubmit( sceneId, selfId, NPCId)


end



--**********************************

--�ύ

--**********************************

function x570037_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)

end



--**********************************

--ɱ����������

--**********************************

function x570037_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x570037_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)
	

end

function x570037_ProcTiming(sceneId, selfId )
	 
		
end

function x570037_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId )
	
end



--**********************************

--���߸ı�

--**********************************

function x570037_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	
end
function x570037_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
	    CallScriptFunction( MISSION_SCRIPT, "ProcQuestAttach",sceneId, selfId, npcId, npcGuid, misIndex, MissionId)
end

function x570037_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x570037_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x570037_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x570037_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x570037_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x570037_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end
