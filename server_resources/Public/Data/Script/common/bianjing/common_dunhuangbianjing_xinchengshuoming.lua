--�ĳ������淨˵��

--MisDescBegin
x300582_g_ScriptId = 300582
x300582_g_MissionIdPre =-1
--x300582_g_MissionId = 
x300582_g_MissionKind = 8
x300582_g_LevelLess	= 	-1 
x300582_g_MissionIdNext = -1
--x300582_g_MissionId1 = -1
--x300582_g_Name	=	"" 
--x300582_g_noDemandItem =	{}
--x300582_g_ExtTarget={}
x300582_g_NeedNum1= 1
x300582_g_NeedNum2= 1
x300582_g_NeedNum3= 1
x300582_g_MissionHelp =	""
x300582_g_MissionName1="���ĳ������淨˵����"
x300582_g_MissionName2="���ĳ������淨˵����"
x300582_g_MissionInfo1="\t��������ˮ���Ŀ����ǰ���Ŀ�Сˮ����#G���������˸��â#W��\n\t��ס�Ŀ�ˮ����˸��#G˳��#W���ڹ�â��˸�󣬰���ˮ��#G��˸˳�����ε���Ŀ�ˮ��#W��ɿ��顣\n\tǰ6���е��ˮ����Ȼ���Լ�����ֱ����ȷ���ڵ�6�ֳɹ���ɺ󣬿���ȡ�����������顣���ߵ�#G����ˮ��#W����ս#G���߽���#W��\n\t��ս�ɹ���7�͵�8�֣��п��ܻ��ö���Ľ�����\n\t������#G��7��8�֣����һ��ˮ���������Ҫ�ӵ�1�����¿�ʼ#W��"  --��������
--x300582_g_MissionInfo2="\t#G����ʯ#W��������ǿ�߷�����Ҫ���ʡ������󽫾������������������������������ռ�#G����ʯ#W������������#G����ʯ#W֮�󣬰��������ң����Եõ�����װ����\n\t����ʯ�һ���װ����Ϊ30����50����70�����֡�30��װ����Ҫ#G��������ʯ#W��50��װ����Ҫ#G�м�����ʯ#W��70��װ����Ҫ#G�߼�����ʯ#W��\n\t��������Ϊ���һ�50����70��װ��װ����"  --��������
x300582_g_MissionCompleted1=""--�������npc˵���Ļ�
x300582_g_MissionCompleted2=""--�������npc˵���Ļ�
x300582_g_ContinueInfo1="\t�㽫Ҫx300582_g_MissionName5��\n\t���۳���������ʯx300582_g_NeedNum1�š�"
x300582_g_ContinueInfo2=""
x300582_g_ContinueInfo3=""
x300582_g_ErrorInfo1=""
x300582_g_ErrorInfo2=""
x300582_g_BonusMoney1 =0
x300582_g_BonusMoney2 =0
x300582_g_BonusMoney3 =0
x300582_g_BonusItem	=	{}
x300582_g_BonusChoiceItem ={}
x300582_g_ExpBonus = 250
x300582_g_SkillHalfHour = 7510
x300582_g_SkillOneHour = 7511
--MisDescEnd

--**********************************

--������ں���

--**********************************

function x300582_ProcEventEntry(sceneId, selfId, targetId,scriptid,extid)	--����������ִ�д˽ű�
	--����г�����
local isHaveMission = IsHaveQuestNM(sceneId,selfId,9500);
if isHaveMission == 1 then
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"#Y"..x300582_g_MissionName2)
			AddQuestText(sceneId,x300582_g_MissionInfo1)
		EndQuestEvent()
		DispatchQuestEventList(sceneId, selfId,targetId,x300582_g_ScriptId, x300582_g_MissionName1)
	
end

end



--**********************************

--�о��¼�

--**********************************

function x300582_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)

--	local country = GetCurCountry(sceneId, selfId)
--	local nDefaultCamp = GetSceneCamp( sceneId )-16
--
--	if country == nDefaultCamp then 
local isHaveMission = IsHaveQuestNM(sceneId,selfId,9500);
if isHaveMission == 1 then
		AddQuestNumText(sceneId, x300582_g_ScriptId, x300582_g_MissionName1,0,1)
--	else 
--			return
--	end
end
	
end



--**********************************

--����������

--**********************************

function x300582_ProcAcceptCheck(sceneId, selfId, NPCId)

	return 1
end


--**********************************

--���鿴����

--**********************************

function x300582_CheckPushList(sceneId, selfId, NPCId)
	
end

--**********************************

--����

--**********************************

function x300582_ProcAccept( sceneId, selfId )
	
end



--**********************************

--����

--**********************************

function x300582_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x300582_CheckSubmit( sceneId, selfId, NPCId)


end



--**********************************

--�ύ

--**********************************

function x300582_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)

end



--**********************************

--ɱ����������

--**********************************

function x300582_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x300582_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)
	

end

function x300582_ProcTiming(sceneId, selfId )
	 
		
end

function x300582_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId )
	
end



--**********************************

--���߸ı�

--**********************************

function x300582_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	
end
function x300582_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
	    CallScriptFunction( MISSION_SCRIPT, "ProcQuestAttach",sceneId, selfId, npcId, npcGuid, misIndex, MissionId)
end

function x300582_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x300582_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x300582_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x300582_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x300582_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x300582_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end
