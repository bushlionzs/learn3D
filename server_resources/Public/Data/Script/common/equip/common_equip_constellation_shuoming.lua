--װ������˵��

--MisDescBegin
x800118_g_ScriptId = 800118
--x800118_g_MissionIdPre =-1
--x800118_g_MissionId = 
--x800118_g_MissionKind = 8
--x800118_g_LevelLess	= 	-1 
--x800118_g_MissionIdNext = -1
--x800118_g_Name	="" 
--x800118_g_noDemandItem ={}
--x800118_g_ExtTarget={}
--x800118_g_NeedNum1= 1
--x800118_g_NeedNum2= 1
--x800118_g_NeedNum3= 1
--x800118_g_MissionHelp =	""
x800118_g_MissionName1="����������˵����"
x800118_g_MissionInfo1="\t1.Ϊ10�����������̵Ļ�װ����װ�����������̡�\n\t2.�������̻������װ������һ��������������ÿ����������һ���������ԣ�������һ�����������Կɱ����\n\t3.ÿ�������ļ���������Ҫ���ض���������ţ��˫�㼤�����˫�ӻ���򼤻��ţ����з���ţ����˫�ӣ�ʨ�ӻ�˫�Ӽ����з����Ů���з����ʨ�ӣ����һ�ʨ�Ӽ��Ů����Ы��Ů�������ң����ֻ����Ҽ�����Ы��ħ�ɻ���Ы�������֣�ˮƿ�����ּ���ħ�ɣ�˫���ħ�ɼ���ˮƿ�������ˮƿ����˫�㡣\n\t3.��������װ������˳��Ϊ��ͷ���������֣��·�����ͷ���������ϣ������·��������£����������ϣ����������������£������缤�����������¼������磬Ь�Ӽ�����£���ָ���£�����Ь�ӣ���ָ���ϣ������ָ���£������ּ����ָ���ϣ�����������֣����ּ������������ּ���֡�\n#Y����˵��#W��\n\t1.���#G���̴�ʦ#W�Ի���\n\t2.ѡ��#G��������#Wѡ���#G��������#W���档\n\t3.����Ҫ���̵�װ������װ�����в���ʾװ���������ԡ�\n\t4.�����������̵��ߡ�\n\t5.���#G����#W��ť��\n#Yע������#W��\n\t1.10�����������̵Ļ�װ����װ���ɽ����������̡�\n\t2.������������Ҫ����󷽿���Ч��"  --��������
--x800118_g_MissionInfo2="\t#G����ʯ#W��������ǿ�߷�����Ҫ���ʡ������󽫾������������������������������ռ�#G����ʯ#W������������#G����ʯ#W֮�󣬰��������ң����Եõ�����װ����\n\t����ʯ�һ���װ����Ϊ�������������񴫣��촫���֡�����װ����Ҫ#G��������ʯ#W������װ����Ҫ#G�м�����ʯ#W����װ����Ҫ#G�߼�����ʯ#W���촫װ����Ҫ#G��֮����ʯ#W��\n\t��������Ϊ���һ�����װ������װ�����촫װ����"  --��������
--x800118_g_MissionCompleted1=""--�������npc˵���Ļ�
--x800118_g_MissionCompleted2=""--�������npc˵���Ļ�
--x800118_g_ContinueInfo1="\t�㽫Ҫx800118_g_MissionName5��\n\t���۳���������ʯx800118_g_NeedNum1�š�"
--x800118_g_ContinueInfo2=""
--x800118_g_ContinueInfo3=""
--x800118_g_ErrorInfo1=""
--x800118_g_ErrorInfo2=""
--x800118_g_BonusMoney1 =0
--x800118_g_BonusMoney2 =0
--x800118_g_BonusMoney3 =0
--x800118_g_BonusItem	=	{}
--x800118_g_BonusChoiceItem ={}
--x800118_g_ExpBonus = 250
--x800118_g_SkillHalfHour = 7510
--x800118_g_SkillOneHour = 7511
--MisDescEnd

--**********************************

--������ں���

--**********************************

function x800118_ProcEventEntry(sceneId, selfId, targetId,scriptid,extid)	--����������ִ�д˽ű�
	--����г�����

		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"#Y"..x800118_g_MissionName1)
			AddQuestText(sceneId,x800118_g_MissionInfo1)
		EndQuestEvent()
		DispatchQuestEventList(sceneId, selfId,targetId,x800118_g_ScriptId, x800118_g_MissionName1)

end



--**********************************

--�о��¼�

--**********************************

function x800118_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)

--	local country = GetCurCountry(sceneId, selfId)
--	local nDefaultCamp = GetSceneCamp( sceneId )-16
--
--	if country == nDefaultCamp then 
		AddQuestNumText(sceneId, x800118_g_ScriptId, x800118_g_MissionName1,13,1)
--	else 
--			return
--	end
	
end



--**********************************

--����������

--**********************************

function x800118_ProcAcceptCheck(sceneId, selfId, NPCId)
		return 1
end


--**********************************

--���鿴����

--**********************************

function x800118_CheckPushList(sceneId, selfId, NPCId)
	
end

--**********************************

--����

--**********************************

function x800118_ProcAccept( sceneId, selfId )
	
end



--**********************************

--����

--**********************************

function x800118_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x800118_CheckSubmit( sceneId, selfId, NPCId)


end



--**********************************

--�ύ

--**********************************

function x800118_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)

end



--**********************************

--ɱ����������

--**********************************

function x800118_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x800118_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)
	

end

function x800118_ProcTiming(sceneId, selfId )
	 
		
end

function x800118_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId )
	
end



--**********************************

--���߸ı�

--**********************************

function x800118_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	
end
function x800118_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
	    CallScriptFunction( MISSION_SCRIPT, "ProcQuestAttach",sceneId, selfId, npcId, npcGuid, misIndex, MissionId)
end

function x800118_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x800118_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x800118_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x800118_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x800118_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x800118_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end
