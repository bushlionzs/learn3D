--װ������˵��

--MisDescBegin
x800120_g_ScriptId = 800120
--x800120_g_MissionIdPre =-1
--x800120_g_MissionId = 
--x800120_g_MissionKind = 8
--x800120_g_LevelLess	= 	-1 
--x800120_g_MissionIdNext = -1
--x800120_g_Name	="" 
--x800120_g_noDemandItem ={}
--x800120_g_ExtTarget={}
--x800120_g_NeedNum1= 1
--x800120_g_NeedNum2= 1
--x800120_g_NeedNum3= 1
--x800120_g_MissionHelp =	""
x800120_g_MissionName1="��ս������˵����"
x800120_g_MissionInfo1="\tװ������ս�����̻������������ԣ���߿�������9����ս�������������Һ�ս����õĽ��¡�Ŀǰֻ���ŵ�3��ս�����̡�\n#Y����˵����\n\t#W1.������#Gװ�����̴�ʦ#W���#Gװ�����̴�ʦ#W�Ի���\n\t2.ѡ��#Gս������#Wѡ�\n\t3.��װ�����뵽ս�����̽������Ϸ������ڡ�\n\t4.��ѡ�����̵����б��ڣ�ѡ������ʹ�õĽ��¡�\n\t5.��������·����̰�ť��װ��ս�����̡�\n\t6.�����Ҫʹ���Զ����̵Ĺ��ܣ��������ѡ���Զ����̵ȼ����������ڣ�ѡ���Զ����̵ȼ�������Զ����̰�ť���ɣ������һ��²��㣬��װ����������ѡ��ĵȼ����Զ����̽����Զ�ֹͣ��\n#Yע�����\n\t#W1.ս������ǿ���Ļ������Բ��ܴ���Ӱ�졣\n\t2.���̹����м���ʧ�ܣ�ʧ�ܺ����һ�����̵ȼ���0��1����3��4����6��7������ʧ�ܺ��˵ȼ���"  --��������
--x800120_g_MissionInfo2="\t#G����ʯ#W��������ǿ�߷�����Ҫ���ʡ������󽫾������������������������������ռ�#G����ʯ#W������������#G����ʯ#W֮�󣬰��������ң����Եõ�����װ����\n\t����ʯ�һ���װ����Ϊ�������������񴫣��촫���֡�����װ����Ҫ#G��������ʯ#W������װ����Ҫ#G�м�����ʯ#W����װ����Ҫ#G�߼�����ʯ#W���촫װ����Ҫ#G��֮����ʯ#W��\n\t��������Ϊ���һ�����װ������װ�����촫װ����"  --��������
--x800120_g_MissionCompleted1=""--�������npc˵���Ļ�
--x800120_g_MissionCompleted2=""--�������npc˵���Ļ�
--x800120_g_ContinueInfo1="\t�㽫Ҫx800120_g_MissionName5��\n\t���۳���������ʯx800120_g_NeedNum1�š�"
--x800120_g_ContinueInfo2=""
--x800120_g_ContinueInfo3=""
--x800120_g_ErrorInfo1=""
--x800120_g_ErrorInfo2=""
--x800120_g_BonusMoney1 =0
--x800120_g_BonusMoney2 =0
--x800120_g_BonusMoney3 =0
--x800120_g_BonusItem	=	{}
--x800120_g_BonusChoiceItem ={}
--x800120_g_ExpBonus = 250
--x800120_g_SkillHalfHour = 7510
--x800120_g_SkillOneHour = 7511
--MisDescEnd

--**********************************

--������ں���

--**********************************

function x800120_ProcEventEntry(sceneId, selfId, targetId,scriptid,extid)	--����������ִ�д˽ű�
	--����г�����

		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"#Y"..x800120_g_MissionName1)
			AddQuestText(sceneId,x800120_g_MissionInfo1)
		EndQuestEvent()
		DispatchQuestEventList(sceneId, selfId,targetId,x800120_g_ScriptId, x800120_g_MissionName1)

end



--**********************************

--�о��¼�

--**********************************

function x800120_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)

--	local country = GetCurCountry(sceneId, selfId)
--	local nDefaultCamp = GetSceneCamp( sceneId )-16
--
--	if country == nDefaultCamp then 
		AddQuestNumText(sceneId, x800120_g_ScriptId, x800120_g_MissionName1,13,1)
--	else 
--			return
--	end
	
end



--**********************************

--����������

--**********************************

function x800120_ProcAcceptCheck(sceneId, selfId, NPCId)
		return 1
end


--**********************************

--���鿴����

--**********************************

function x800120_CheckPushList(sceneId, selfId, NPCId)
	
end

--**********************************

--����

--**********************************

function x800120_ProcAccept( sceneId, selfId )
	
end



--**********************************

--����

--**********************************

function x800120_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x800120_CheckSubmit( sceneId, selfId, NPCId)


end



--**********************************

--�ύ

--**********************************

function x800120_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)

end



--**********************************

--ɱ����������

--**********************************

function x800120_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x800120_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)
	

end

function x800120_ProcTiming(sceneId, selfId )
	 
		
end

function x800120_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId )
	
end



--**********************************

--���߸ı�

--**********************************

function x800120_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	
end
function x800120_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
	    CallScriptFunction( MISSION_SCRIPT, "ProcQuestAttach",sceneId, selfId, npcId, npcGuid, misIndex, MissionId)
end

function x800120_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x800120_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x800120_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x800120_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x800120_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x800120_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end
