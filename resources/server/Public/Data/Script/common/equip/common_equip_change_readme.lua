--�齫����˵��

--MisDescBegin
x800092_g_ScriptId = 800092
--x800092_g_MissionIdPre =-1
--x800092_g_MissionId = 
--x800092_g_MissionKind = 8
--x800092_g_LevelLess	= 	-1 
--x800092_g_MissionIdNext = -1
--x800092_g_Name	="" 
--x800092_g_noDemandItem ={}
--x800092_g_ExtTarget={}
--x800092_g_NeedNum1= 1
--x800092_g_NeedNum2= 1
--x800092_g_NeedNum3= 1
--x800092_g_MissionHelp =	""
x800092_g_MissionName1="��װ��ת��˵����"
x800092_g_MissionInfo1="\t����װ��ת��ʱ������Ҫӵ��#Gװ��ת����#W���������װ��ֻ��ת��Ϊ��Ӧְҵ��װ����\n\t����װ��ת����ӦΪ��\n\t#Gͻ����ʿ#W��ת��Ϊ#G���к�ʮ�־�#W\n\t#G���Ͻ���#W��ת��Ϊ#G����ʥ��ʹ#W\n\t#G�ɹ�������#W��ת��Ϊ#G���Ĵ̿�#W\n\t#G��ԭ��ǹ��#W��ת��Ϊ#G�ɹŽ�����#W\n\t#G��˹��֪#W��ת��Ϊ#G˹��������ʿ#W\n\t#Gѩɽ����#W��ת��Ϊ#G��ԭɮ��#W\n#Yע������#W��\n\tֻ��#G��ɫװ��#W��#G��ɫװ��#W���ܽ���װ��ת����"  --��������
--x800092_g_MissionInfo2="\t#G����ʯ#W��������ǿ�߷�����Ҫ���ʡ������󽫾������������������������������ռ�#G����ʯ#W������������#G����ʯ#W֮�󣬰��������ң����Եõ�����װ����\n\t����ʯ�һ���װ����Ϊ�������������񴫣��촫���֡�����װ����Ҫ#G��������ʯ#W������װ����Ҫ#G�м�����ʯ#W����װ����Ҫ#G�߼�����ʯ#W���촫װ����Ҫ#G��֮����ʯ#W��\n\t��������Ϊ���һ�����װ������װ�����촫װ����"  --��������
--x800092_g_MissionCompleted1=""--�������npc˵���Ļ�
--x800092_g_MissionCompleted2=""--�������npc˵���Ļ�
--x800092_g_ContinueInfo1="\t�㽫Ҫx800092_g_MissionName5��\n\t���۳���������ʯx800092_g_NeedNum1�š�"
--x800092_g_ContinueInfo2=""
--x800092_g_ContinueInfo3=""
--x800092_g_ErrorInfo1=""
--x800092_g_ErrorInfo2=""
--x800092_g_BonusMoney1 =0
--x800092_g_BonusMoney2 =0
--x800092_g_BonusMoney3 =0
--x800092_g_BonusItem	=	{}
--x800092_g_BonusChoiceItem ={}
--x800092_g_ExpBonus = 250
--x800092_g_SkillHalfHour = 7510
--x800092_g_SkillOneHour = 7511
--MisDescEnd

--**********************************

--������ں���

--**********************************

function x800092_ProcEventEntry(sceneId, selfId, targetId,scriptid,extid)	--����������ִ�д˽ű�
	--����г�����

		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"#Y"..x800092_g_MissionName1)
			AddQuestText(sceneId,x800092_g_MissionInfo1)
		EndQuestEvent()
		DispatchQuestEventList(sceneId, selfId,targetId,x800092_g_ScriptId, x800092_g_MissionName1)

end



--**********************************

--�о��¼�

--**********************************

function x800092_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)

--	local country = GetCurCountry(sceneId, selfId)
--	local nDefaultCamp = GetSceneCamp( sceneId )-16
--
--	if country == nDefaultCamp then 
		AddQuestNumText(sceneId, x800092_g_ScriptId, x800092_g_MissionName1,13,1)
--	else 
--			return
--	end
	
end



--**********************************

--����������

--**********************************

function x800092_ProcAcceptCheck(sceneId, selfId, NPCId)
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

function x800092_CheckPushList(sceneId, selfId, NPCId)
	
end

--**********************************

--����

--**********************************

function x800092_ProcAccept( sceneId, selfId )
	
end



--**********************************

--����

--**********************************

function x800092_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x800092_CheckSubmit( sceneId, selfId, NPCId)


end



--**********************************

--�ύ

--**********************************

function x800092_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)

end



--**********************************

--ɱ����������

--**********************************

function x800092_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x800092_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)
	

end

function x800092_ProcTiming(sceneId, selfId )
	 
		
end

function x800092_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId )
	
end



--**********************************

--���߸ı�

--**********************************

function x800092_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	
end
function x800092_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
	    CallScriptFunction( MISSION_SCRIPT, "ProcQuestAttach",sceneId, selfId, npcId, npcGuid, misIndex, MissionId)
end

function x800092_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x800092_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x800092_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x800092_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x800092_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x800092_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end
