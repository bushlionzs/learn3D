--�Ĵ����淨˵��

--MisDescBegin
x300568_g_ScriptId = 300568
x300568_g_MissionIdPre =-1
--x300568_g_MissionId = 
x300568_g_MissionKind = 8
x300568_g_LevelLess	= 	-1 
x300568_g_MissionIdNext = -1
x300568_g_MissionId1 = 9300
x300568_g_Name	="" 
x300568_g_noDemandItem ={}
x300568_g_ExtTarget={}
x300568_g_NeedNum1= 1
x300568_g_NeedNum2= 1
x300568_g_NeedNum3= 1
x300568_g_MissionHelp =	""
x300568_g_MissionName1="���Ĵ����淨˵����"
x300568_g_MissionName2="���Ĵ����淨˵����"
x300568_g_MissionInfo1="\t�ڱ������У��һ�����ȥѯ���Ĵ�������������#G������#W�������#G�滰#W��#Gһ���˻�����#W��\n\t��ס��#G���ѵ��˲�һ������ͽ����ͽ��һ������#W��\n\t�������#G������#W�в鿴�Ĵ���˵���Ļ����Ա������"  --��������
--x300568_g_MissionInfo2="\t#G����ʯ#W��������ǿ�߷�����Ҫ���ʡ������󽫾������������������������������ռ�#G����ʯ#W������������#G����ʯ#W֮�󣬰��������ң����Եõ�����װ����\n\t����ʯ�һ���װ����Ϊ30����50����70�����֡�30��װ����Ҫ#G��������ʯ#W��50��װ����Ҫ#G�м�����ʯ#W��70��װ����Ҫ#G�߼�����ʯ#W��\n\t��������Ϊ���һ�50����70��װ��װ����"  --��������
x300568_g_MissionCompleted1=""--�������npc˵���Ļ�
x300568_g_MissionCompleted2=""--�������npc˵���Ļ�
x300568_g_ContinueInfo1="\t�㽫Ҫx300568_g_MissionName5��\n\t���۳���������ʯx300568_g_NeedNum1�š�"
x300568_g_ContinueInfo2=""
x300568_g_ContinueInfo3=""
x300568_g_ErrorInfo1=""
x300568_g_ErrorInfo2=""
x300568_g_BonusMoney1 =0
x300568_g_BonusMoney2 =0
x300568_g_BonusMoney3 =0
x300568_g_BonusItem	=	{}
x300568_g_BonusChoiceItem ={}
x300568_g_ExpBonus = 250
x300568_g_SkillHalfHour = 7510
x300568_g_SkillOneHour = 7511
--MisDescEnd

--**********************************

--������ں���

--**********************************

function x300568_ProcEventEntry(sceneId, selfId, targetId,scriptid,extid)	--����������ִ�д˽ű�
	--����г�����
local isHaveMission = IsHaveQuestNM(sceneId,selfId,9300);
if isHaveMission == 1 then
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"#Y"..x300568_g_MissionName2)
			AddQuestText(sceneId,x300568_g_MissionInfo1)
		EndQuestEvent()
		DispatchQuestEventList(sceneId, selfId,targetId,x300568_g_ScriptId, x300568_g_MissionName1)
	
end

end



--**********************************

--�о��¼�

--**********************************

function x300568_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)

--	local country = GetCurCountry(sceneId, selfId)
--	local nDefaultCamp = GetSceneCamp( sceneId )-16
--
--	if country == nDefaultCamp then 
local isHaveMission = IsHaveQuestNM(sceneId,selfId,9300);
if isHaveMission == 1 then
		AddQuestNumText(sceneId, x300568_g_ScriptId, x300568_g_MissionName1,0,1)
--	else 
--			return
--	end
end
	
end



--**********************************

--����������

--**********************************

function x300568_ProcAcceptCheck(sceneId, selfId, NPCId)

	return 1
end


--**********************************

--���鿴����

--**********************************

function x300568_CheckPushList(sceneId, selfId, NPCId)
	
end

--**********************************

--����

--**********************************

function x300568_ProcAccept( sceneId, selfId )
	
end



--**********************************

--����

--**********************************

function x300568_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x300568_CheckSubmit( sceneId, selfId, NPCId)


end



--**********************************

--�ύ

--**********************************

function x300568_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)

end



--**********************************

--ɱ����������

--**********************************

function x300568_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x300568_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)
	

end

function x300568_ProcTiming(sceneId, selfId )
	 
		
end

function x300568_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId )
	
end



--**********************************

--���߸ı�

--**********************************

function x300568_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	
end
function x300568_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
	    CallScriptFunction( MISSION_SCRIPT, "ProcQuestAttach",sceneId, selfId, npcId, npcGuid, misIndex, MissionId)
end

function x300568_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x300568_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x300568_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x300568_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x300568_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x300568_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end
