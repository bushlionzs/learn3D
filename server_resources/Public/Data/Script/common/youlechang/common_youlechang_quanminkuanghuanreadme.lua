--װ������˵��

--MisDescBegin
x310345_g_ScriptId = 310345
--x310345_g_MissionIdPre =-1
--x310345_g_MissionId = 
--x310345_g_MissionKind = 8
--x310345_g_LevelLess	= 	-1 
--x310345_g_MissionIdNext = -1
--x310345_g_Name	="" 
--x310345_g_noDemandItem ={}
--x310345_g_ExtTarget={}
--x310345_g_NeedNum1= 1
--x310345_g_NeedNum2= 1
--x310345_g_NeedNum3= 1
--x310345_g_MissionHelp =	""
x310345_g_MissionName1="��ˮ�����ܶ�Ա˵����"
x310345_g_MissionInfo1="\t���ħŮ��ˮ�����ܵ��ˣ���������ħŮ���Ҳ�֪����������ˮ������Һ���Ҫ���Ǵ�С���Ҵ���������͸��ҵģ�������ֺ���Ƥ�Ĳ����������ҵ��������ͻ�ص�����ߡ���Ȼ���㣬�Լ��������˼䡤�����ڵ������˶��������޵ľ�ϲ��\n \n#Y�����#W��\n\t1.��������9��00����23��00��ˮ�����#G����#W�ĳ����������˼䡤���������\n\t2.��Ѱ��ˮ�������һ�ô������齱����ͬʱ�����˼䡤������������һ�ò��־��齱����\n\t3.ˮ���򲢲��������ұ�������Ѱ����������ص�ħŮ��ߣ�������Ƥ������ʱ���������ط��ٴγ��֡�"  --��������
--x310345_g_MissionInfo2="\t#G����ʯ#W��������ǿ�߷�����Ҫ���ʡ������󽫾������������������������������ռ�#G����ʯ#W������������#G����ʯ#W֮�󣬰��������ң����Եõ�����װ����\n\t����ʯ�һ���װ����Ϊ�������������񴫣��촫���֡�����װ����Ҫ#G��������ʯ#W������װ����Ҫ#G�м�����ʯ#W����װ����Ҫ#G�߼�����ʯ#W���촫װ����Ҫ#G��֮����ʯ#W��\n\t��������Ϊ���һ�����װ������װ�����촫װ����"  --��������
--x310345_g_MissionCompleted1=""--�������npc˵���Ļ�
--x310345_g_MissionCompleted2=""--�������npc˵���Ļ�
--x310345_g_ContinueInfo1="\t�㽫Ҫx310345_g_MissionName5��\n\t���۳���������ʯx310345_g_NeedNum1�š�"
--x310345_g_ContinueInfo2=""
--x310345_g_ContinueInfo3=""
--x310345_g_ErrorInfo1=""
--x310345_g_ErrorInfo2=""
--x310345_g_BonusMoney1 =0
--x310345_g_BonusMoney2 =0
--x310345_g_BonusMoney3 =0
--x310345_g_BonusItem	=	{}
--x310345_g_BonusChoiceItem ={}
--x310345_g_ExpBonus = 250
--x310345_g_SkillHalfHour = 7510
--x310345_g_SkillOneHour = 7511
--MisDescEnd

--**********************************

--������ں���

--**********************************

function x310345_ProcEventEntry(sceneId, selfId, targetId,scriptid,extid)	--����������ִ�д˽ű�
	--����г�����

		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"#Y"..x310345_g_MissionName1)
			AddQuestText(sceneId,x310345_g_MissionInfo1)
		EndQuestEvent()
		DispatchQuestEventList(sceneId, selfId,targetId,x310345_g_ScriptId, x310345_g_MissionName1)

end



--**********************************

--�о��¼�

--**********************************

function x310345_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)

--	local country = GetCurCountry(sceneId, selfId)
--	local nDefaultCamp = GetSceneCamp( sceneId )-16
--
--	if country == nDefaultCamp then 
		AddQuestNumText(sceneId, x310345_g_ScriptId, x310345_g_MissionName1,13,1)
--	else 
--			return
--	end
	
end



--**********************************

--����������

--**********************************

function x310345_ProcAcceptCheck(sceneId, selfId, NPCId)
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

function x310345_CheckPushList(sceneId, selfId, NPCId)
	
end

--**********************************

--����

--**********************************

function x310345_ProcAccept( sceneId, selfId )
	
end



--**********************************

--����

--**********************************

function x310345_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x310345_CheckSubmit( sceneId, selfId, NPCId)


end



--**********************************

--�ύ

--**********************************

function x310345_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)

end



--**********************************

--ɱ����������

--**********************************

function x310345_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x310345_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)
	

end

function x310345_ProcTiming(sceneId, selfId )
	 
		
end

function x310345_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId )
	
end



--**********************************

--���߸ı�

--**********************************

function x310345_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	
end
function x310345_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
	    CallScriptFunction( MISSION_SCRIPT, "ProcQuestAttach",sceneId, selfId, npcId, npcGuid, misIndex, MissionId)
end

function x310345_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x310345_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x310345_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x310345_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x310345_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x310345_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end
