--��ʦר������˵��

--MisDescBegin
x310707_g_ScriptId = 310707
--x310707_g_MissionIdPre =-1
--x310707_g_MissionId = 
--x310707_g_MissionKind = 8
--x310707_g_LevelLess	= 	-1 
--x310707_g_MissionIdNext = -1
--x310707_g_Name	="" 
--x310707_g_noDemandItem ={}
--x310707_g_ExtTarget={}
--x310707_g_NeedNum1= 1
--x310707_g_NeedNum2= 1
--x310707_g_NeedNum3= 1
--x310707_g_MissionHelp =	""
x310707_g_MissionName1="����ʦר������˵����"
x310707_g_MissionInfo1="\t��ʦר���������ͨ���������յĸ߳��������������������Ʒ��\n#Y��ϸ˵��#W��\n#G��ҩ��ʦ#W����������\n\t�ٻ���¶����5��/�Σ�\n\t���������裨3��/�Σ�\n\t�����ɻ��裨3��/�Σ�\n\t����ħ���裨3��/�Σ�\n#G�鱦��ʦ#W����������\n\t��ʦ����������1��/�Σ�\n\t��ʦ����������1��/�Σ�\n\t��ʦ����������1��/�Σ�\n\t��ʦ����������1��/�Σ�\n\t��ʦ�����ʯ��1��/�Σ�\n\t��ʦ��ϴʯ����1��/�Σ�\n\t�����꣨1��/�Σ�\n#Gѱ���ʦ#W����������\n\t����ǿ������һ�����壨3��/�Σ�\n\t����ǿ������һ��������3��/�Σ�\n\t����ǿ������һ���ϻۣ�3��/�Σ�\n\t����ǿ������һ��׷Ӱ��3��/�Σ�\n\t����ǿ������һ��ȫ�ܣ�3��/�Σ�\n#G�����ʦ#W����������\n\t������ˮ��3��/�Σ�\n\tѪ���꣨1��/�Σ�\n#G���״�ʦ#W����������\n\tһ������裨3��/�Σ�\n\tһ�������裨3��/�Σ�\n\tһ���ۼ��裨3��/�Σ�\n\t�����꣨1��/�Σ�\n#G���մ�ʦ#W����������\n\t��ʿ����5��/�Σ�\n\t���ʷ��Ĳ���10��/�Σ�\n\t�����꣨1��/�Σ�"  --��������
x310707_g_MissionInfo2="#Yע������#W��\n\t#R��ʦ��ר���������Ʒ������ȴʱ�䡪��24Сʱ��#W����������������������Ʒһ��֮��24Сʱ�ڲ�����������ʦר���������Ʒ��"  --��������
--x310707_g_MissionCompleted1=""--�������npc˵���Ļ�
--x310707_g_MissionCompleted2=""--�������npc˵���Ļ�
--x310707_g_ContinueInfo1="\t�㽫Ҫx310707_g_MissionName5��\n\t���۳���������ʯx310707_g_NeedNum1�š�"
--x310707_g_ContinueInfo2=""
--x310707_g_ContinueInfo3=""
--x310707_g_ErrorInfo1=""
--x310707_g_ErrorInfo2=""
--x310707_g_BonusMoney1 =0
--x310707_g_BonusMoney2 =0
--x310707_g_BonusMoney3 =0
--x310707_g_BonusItem	=	{}
--x310707_g_BonusChoiceItem ={}
--x310707_g_ExpBonus = 250
--x310707_g_SkillHalfHour = 7510
--x310707_g_SkillOneHour = 7511
--MisDescEnd

--**********************************

--������ں���

--**********************************

function x310707_ProcEventEntry(sceneId, selfId, targetId,scriptid,extid)	--����������ִ�д˽ű�
	--����г�����

		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"#Y"..x310707_g_MissionName1)
			AddQuestText(sceneId,x310707_g_MissionInfo1)
            AddQuestText(sceneId,x310707_g_MissionInfo2)
		EndQuestEvent()
		DispatchQuestEventList(sceneId, selfId,targetId,x310707_g_ScriptId, x310707_g_MissionName1)

end



--**********************************

--�о��¼�

--**********************************

function x310707_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)

--	local country = GetCurCountry(sceneId, selfId)
--	local nDefaultCamp = GetSceneCamp( sceneId )-16
--
--	if country == nDefaultCamp then 
		AddQuestNumText(sceneId, x310707_g_ScriptId, x310707_g_MissionName1,13,1)
--	else 
--			return
--	end
	
end



--**********************************

--����������

--**********************************

function x310707_ProcAcceptCheck(sceneId, selfId, NPCId)
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

function x310707_CheckPushList(sceneId, selfId, NPCId)
	
end

--**********************************

--����

--**********************************

function x310707_ProcAccept( sceneId, selfId )
	
end



--**********************************

--����

--**********************************

function x310707_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x310707_CheckSubmit( sceneId, selfId, NPCId)


end



--**********************************

--�ύ

--**********************************

function x310707_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)

end



--**********************************

--ɱ����������

--**********************************

function x310707_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x310707_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)
	

end

function x310707_ProcTiming(sceneId, selfId )
	 
		
end

function x310707_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId )
	
end



--**********************************

--���߸ı�

--**********************************

function x310707_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	
end
function x310707_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
	    CallScriptFunction( MISSION_SCRIPT, "ProcQuestAttach",sceneId, selfId, npcId, npcGuid, misIndex, MissionId)
end

function x310707_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x310707_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x310707_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x310707_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x310707_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x310707_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end
