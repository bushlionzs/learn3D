--�����ǵ��淨˵��

--MisDescBegin
x310189_g_ScriptId = 310189
x310189_g_MissionIdPre =-1
--x310189_g_MissionId = 
x310189_g_MissionKind = 8
x310189_g_LevelLess	= 	-1 
x310189_g_MissionIdNext = -1
x310189_g_MissionId1 = 9300
x310189_g_Name	="" 
x310189_g_noDemandItem ={}
x310189_g_ExtTarget={}
x310189_g_NeedNum1= 1
x310189_g_NeedNum2= 1
x310189_g_NeedNum3= 1
x310189_g_MissionHelp =	""
x310189_g_MissionName1="�������ǵ����̭��˵����"
x310189_g_MissionName2="�������ǵ����̭��˵����"
x310189_g_MissionInfo1="\t����̭����ÿ�˿��Բμ����֣������ڴ�#G��157��215����96��222����66��196������һ���ҵ���һ�������˲μӡ�\n\tÿ�ֱ���Ҫͨ��#Gһ��#W��#G��ʮ�������˵Ŀ���#W����һλ�����˴�#G�ش���ȷ#W����#G�ش��������#W������ǰ����һλ�����˴��ش�\n\t#Gÿ�ش����һ�Σ���������15��������ʱ�䡣���ǣ�ÿ����1��ʹ�ù����һ���ش���ȷ����3��ʹ�úڰ��50%���ܻش���ȷ���Ļ��ᡣ\n\t#W���ǽ���ͳ��#Gÿ����ʱ��̵�ǰ��ʮλ���#W�����ǽ�ȡ�������ǵ��ռ���ս���ʸ�������16��30��ǰ����Ԫ�ʹ��ҵ����ܹܣ�135��54�����ܿ��顣"  --��������
--x310189_g_MissionInfo2="\t#G����ʯ#W��������ǿ�߷�����Ҫ���ʡ������󽫾������������������������������ռ�#G����ʯ#W������������#G����ʯ#W֮�󣬰��������ң����Եõ�����װ����\n\t����ʯ�һ���װ����Ϊ30����50����70�����֡�30��װ����Ҫ#G��������ʯ#W��50��װ����Ҫ#G�м�����ʯ#W��70��װ����Ҫ#G�߼�����ʯ#W��\n\t��������Ϊ���һ�50����70��װ��װ����"  --��������
x310189_g_MissionCompleted1=""--�������npc˵���Ļ�
x310189_g_MissionCompleted2=""--�������npc˵���Ļ�
x310189_g_ContinueInfo1="\t�㽫Ҫx310189_g_MissionName5��\n\t���۳���������ʯx310189_g_NeedNum1�š�"
x310189_g_ContinueInfo2=""
x310189_g_ContinueInfo3=""
x310189_g_ErrorInfo1=""
x310189_g_ErrorInfo2=""
x310189_g_BonusMoney1 =0
x310189_g_BonusMoney2 =0
x310189_g_BonusMoney3 =0
x310189_g_BonusItem	=	{}
x310189_g_BonusChoiceItem ={}
x310189_g_ExpBonus = 250
x310189_g_SkillHalfHour = 7510
x310189_g_SkillOneHour = 7511
--MisDescEnd

--**********************************

--������ں���

--**********************************

function x310189_ProcEventEntry(sceneId, selfId, targetId,scriptid,extid)	--����������ִ�д˽ű�
	--����г�����
--local isHaveMission = IsHaveQuestNM(sceneId,selfId,9300);
--if isHaveMission == 1 then
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"#Y"..x310189_g_MissionName1)
			AddQuestText(sceneId,x310189_g_MissionInfo1)
		EndQuestEvent()
		DispatchQuestEventList(sceneId, selfId,targetId,x310189_g_ScriptId, x310189_g_MissionName1)
	
--end

end



--**********************************

--�о��¼�

--**********************************

function x310189_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)

--	local country = GetCurCountry(sceneId, selfId)
--	local nDefaultCamp = GetSceneCamp( sceneId )-16
--
--	if country == nDefaultCamp then 
--local isHaveMission = IsHaveQuestNM(sceneId,selfId,9300);
--if isHaveMission == 1 then
		AddQuestNumText(sceneId, x310189_g_ScriptId, x310189_g_MissionName1,13,1)
--	else 
--			return
--	end
--end
	
end



--**********************************

--����������

--**********************************

function x310189_ProcAcceptCheck(sceneId, selfId, NPCId)

	return 1
end


--**********************************

--���鿴����

--**********************************

function x310189_CheckPushList(sceneId, selfId, NPCId)
	
end

--**********************************

--����

--**********************************

function x310189_ProcAccept( sceneId, selfId )
	
end



--**********************************

--����

--**********************************

function x310189_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x310189_CheckSubmit( sceneId, selfId, NPCId)


end



--**********************************

--�ύ

--**********************************

function x310189_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)

end



--**********************************

--ɱ����������

--**********************************

function x310189_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x310189_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)
	

end

function x310189_ProcTiming(sceneId, selfId )
	 
		
end

function x310189_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId )
	
end



--**********************************

--���߸ı�

--**********************************

function x310189_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	
end
function x310189_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
	    CallScriptFunction( MISSION_SCRIPT, "ProcQuestAttach",sceneId, selfId, npcId, npcGuid, misIndex, MissionId)
end

function x310189_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x310189_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x310189_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x310189_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x310189_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x310189_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end
