--װ���̽�˵��

--MisDescBegin
x800090_g_ScriptId = 800090
--x800090_g_MissionIdPre =-1
--x800090_g_MissionId = 
--x800090_g_MissionKind = 8
--x800090_g_LevelLess	= 	-1 
--x800090_g_MissionIdNext = -1
--x800090_g_Name	="" 
--x800090_g_noDemandItem ={}
--x800090_g_ExtTarget={}
--x800090_g_NeedNum1= 1
--x800090_g_NeedNum2= 1
--x800090_g_NeedNum3= 1
--x800090_g_MissionHelp =	""
x800090_g_MissionName1="��װ���̽�ϴ����˵����"
x800090_g_MissionInfo1="\tװ���̽�ϴ�������װ�����е������Խ������ǿ�����̽���װ��ĳЩ�����Ե���ֵ���õ�������\n\tװ���̽�ϴ��������ĵ���Ϊ����������ս�������̵���ۣ����Ųʾ��������˼䡤�������콵ħ���淨���������ι⾫�������˼䡤�������ڱ�����ս�淨��������ˮ�𾫽������̵���ۣ���ÿ���̽�ʱ������ϴ��ǿ��ֵ�����·��䡣�̽����Խ���������ܹ��õ�������Խ�ߡ�ÿ��װ���������̽�9�Ρ���ҵȼ���װ���ȼ��Ĳ�ֵ����Ŀǰ��ҿ��ԶԸ�װ���̽�Ĵ�����\n\t#Rע�⣺#G���С����ܡ����������ԡ������˺�#R����ÿ�̽����β�������1�㡣\n#Y����˵��#W��\n\t1.������#Gװ���̽��ʦ#W���#Gװ���̽��ʦ#W�Ի���\n\t2.ѡ��#Gװ���̽�ϴ����#Wѡ�\n\t3.����ɫ����ɫװ�����뵽װ���̽�ϴ�����������Ϸ������ڡ�\n\t4.��������·��̽�ť��"  --��������
x800090_g_MissionInfo2="#Yע������#W��\n\t1.ֻ��ǿ��#G���������ݡ����������ʡ�ȫ���ԡ��������������������ޡ����С����ܡ����������ԡ������˺�#W����;#G���С����ܡ����������ԡ������˺�#W����ÿ�̽����β�������1�㡣\n\t2.ֻ��#G3�����ϵȼ�������80����װ��#W����ʹ�ô˹��ܡ�\n\t3.ֻ��#G��ɫװ��#W��#G��ɫװ��#W����ʹ�ô˹��ܡ�\n\t4.#G�Ѱ�#W��װ�����ܽ���װ���̽�\n\t5.װ��80��99����ÿ2���̽�1�Σ�\n\t  װ��100��160��������ȼ����������̽�"  --��������
--x800090_g_MissionCompleted1=""--�������npc˵���Ļ�
--x800090_g_MissionCompleted2=""--�������npc˵���Ļ�
--x800090_g_ContinueInfo1="\t�㽫Ҫx800090_g_MissionName5��\n\t���۳���������ʯx800090_g_NeedNum1�š�"
--x800090_g_ContinueInfo2=""
--x800090_g_ContinueInfo3=""
--x800090_g_ErrorInfo1=""
--x800090_g_ErrorInfo2=""
--x800090_g_BonusMoney1 =0
--x800090_g_BonusMoney2 =0
--x800090_g_BonusMoney3 =0
--x800090_g_BonusItem	=	{}
--x800090_g_BonusChoiceItem ={}
--x800090_g_ExpBonus = 250
--x800090_g_SkillHalfHour = 7510
--x800090_g_SkillOneHour = 7511
--MisDescEnd

--**********************************

--������ں���

--**********************************

function x800090_ProcEventEntry(sceneId, selfId, targetId,scriptid,extid)	--����������ִ�д˽ű�
	--����г�����

		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"#Y"..x800090_g_MissionName1)
			AddQuestText(sceneId,x800090_g_MissionInfo1)
			AddQuestText(sceneId,x800090_g_MissionInfo2)
		EndQuestEvent()
		DispatchQuestEventList(sceneId, selfId,targetId,x800090_g_ScriptId, x800090_g_MissionName1)

end



--**********************************

--�о��¼�

--**********************************

function x800090_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)

--	local country = GetCurCountry(sceneId, selfId)
--	local nDefaultCamp = GetSceneCamp( sceneId )-16
--
--	if country == nDefaultCamp then 
		AddQuestNumText(sceneId, x800090_g_ScriptId, x800090_g_MissionName1,13,1)
--	else 
--			return
--	end
	
end



--**********************************

--����������

--**********************************

function x800090_ProcAcceptCheck(sceneId, selfId, NPCId)
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

function x800090_CheckPushList(sceneId, selfId, NPCId)
	
end

--**********************************

--����

--**********************************

function x800090_ProcAccept( sceneId, selfId )
	
end



--**********************************

--����

--**********************************

function x800090_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x800090_CheckSubmit( sceneId, selfId, NPCId)


end



--**********************************

--�ύ

--**********************************

function x800090_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)

end



--**********************************

--ɱ����������

--**********************************

function x800090_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x800090_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)
	

end

function x800090_ProcTiming(sceneId, selfId )
	 
		
end

function x800090_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId )
	
end



--**********************************

--���߸ı�

--**********************************

function x800090_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	
end
function x800090_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
	    CallScriptFunction( MISSION_SCRIPT, "ProcQuestAttach",sceneId, selfId, npcId, npcGuid, misIndex, MissionId)
end

function x800090_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x800090_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x800090_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x800090_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x800090_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x800090_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end
