--װ������˵��

--MisDescBegin
x310340_g_ScriptId = 310340
--x310340_g_MissionIdPre =-1
--x310340_g_MissionId = 
--x310340_g_MissionKind = 8
--x310340_g_LevelLess	= 	-1 
--x310340_g_MissionIdNext = -1
--x310340_g_Name	="" 
--x310340_g_noDemandItem ={}
--x310340_g_ExtTarget={}
--x310340_g_NeedNum1= 1
--x310340_g_NeedNum2= 1
--x310340_g_NeedNum3= 1
--x310340_g_MissionHelp =	""
x310340_g_MissionName1="�������˼䡤����˵����"
x310340_g_MissionInfo1="\t�����˼䡤��������Ħ����������תľ��������Ҥ������������ս����������̨�����λóǱ���������������������ɵĴ�����ĩ�������\n\t�����˼䡤����ÿ#G��������#W��09��00����23��00���ţ�������#G65��#W����ҿ�ͨ������#G10��#W�������������롣\n \n#Y�����˼䡤��������淨#W��\n\tÿ���״ν��������˼䡤����ʱ��õ�һ��#G������͸��ȯ#W��ƾ�������¼�������ܲμӵ���10��30��12��30��14��30��16��30��18��30��20��30��22��30�ٰ�������˼䡤����#G��͸��齱#W��\n\t��������9��00����23��00�ڼ䣬ħŮ������˿��ˮ�����#G����#W�ĳ����������˼䡤�����������Ѱ��ˮ�������һ�ô������齱����ͬʱ�����˼䡤�������������Ҳ���ò��־��齱����\n\t12:00��ʼ��22��00ÿ��Сʱ������ҿɲ���#G��������ս#W���\n\t12��00��22��00ÿ����ɲ���#G���ı���#W���\n\t�������˼䡤����������Խ���#G��Ҥ#W������#G������̨#W������\n \n#Yע������#W��\n\t1.����#G��һ��#W���������˼䡤�����շѼ�������͸��ȯ��\n\t2.�����˼䡤�����ʺ�65����84������ҽ���,����84���������ȥ#G��ի���԰#W������ػ"  --��������
--x310340_g_MissionInfo2="\t#G����ʯ#W��������ǿ�߷�����Ҫ���ʡ������󽫾������������������������������ռ�#G����ʯ#W������������#G����ʯ#W֮�󣬰��������ң����Եõ�����װ����\n\t����ʯ�һ���װ����Ϊ�������������񴫣��촫���֡�����װ����Ҫ#G��������ʯ#W������װ����Ҫ#G�м�����ʯ#W����װ����Ҫ#G�߼�����ʯ#W���촫װ����Ҫ#G��֮����ʯ#W��\n\t��������Ϊ���һ�����װ������װ�����촫װ����"  --��������
--x310340_g_MissionCompleted1=""--�������npc˵���Ļ�
--x310340_g_MissionCompleted2=""--�������npc˵���Ļ�
--x310340_g_ContinueInfo1="\t�㽫Ҫx310340_g_MissionName5��\n\t���۳���������ʯx310340_g_NeedNum1�š�"
--x310340_g_ContinueInfo2=""
--x310340_g_ContinueInfo3=""
--x310340_g_ErrorInfo1=""
--x310340_g_ErrorInfo2=""
--x310340_g_BonusMoney1 =0
--x310340_g_BonusMoney2 =0
--x310340_g_BonusMoney3 =0
--x310340_g_BonusItem	=	{}
--x310340_g_BonusChoiceItem ={}
--x310340_g_ExpBonus = 250
--x310340_g_SkillHalfHour = 7510
--x310340_g_SkillOneHour = 7511
--MisDescEnd

--**********************************

--������ں���

--**********************************

function x310340_ProcEventEntry(sceneId, selfId, targetId,scriptid,extid)	--����������ִ�д˽ű�
	--����г�����

		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"#Y"..x310340_g_MissionName1)
			AddQuestText(sceneId,x310340_g_MissionInfo1)
		EndQuestEvent()
		DispatchQuestEventList(sceneId, selfId,targetId,x310340_g_ScriptId, x310340_g_MissionName1)

end



--**********************************

--�о��¼�

--**********************************

function x310340_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)

--	local country = GetCurCountry(sceneId, selfId)
--	local nDefaultCamp = GetSceneCamp( sceneId )-16
--
--	if country == nDefaultCamp then 
		AddQuestNumText(sceneId, x310340_g_ScriptId, x310340_g_MissionName1,13,1)
--	else 
--			return
--	end
	
end



--**********************************

--����������

--**********************************

function x310340_ProcAcceptCheck(sceneId, selfId, NPCId)
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

function x310340_CheckPushList(sceneId, selfId, NPCId)
	
end

--**********************************

--����

--**********************************

function x310340_ProcAccept( sceneId, selfId )
	
end



--**********************************

--����

--**********************************

function x310340_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x310340_CheckSubmit( sceneId, selfId, NPCId)


end



--**********************************

--�ύ

--**********************************

function x310340_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)

end



--**********************************

--ɱ����������

--**********************************

function x310340_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x310340_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)
	

end

function x310340_ProcTiming(sceneId, selfId )
	 
		
end

function x310340_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId )
	
end



--**********************************

--���߸ı�

--**********************************

function x310340_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	
end
function x310340_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
	    CallScriptFunction( MISSION_SCRIPT, "ProcQuestAttach",sceneId, selfId, npcId, npcGuid, misIndex, MissionId)
end

function x310340_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x310340_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x310340_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x310340_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x310340_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x310340_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end
