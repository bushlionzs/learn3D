
x350011_g_ScriptId = 350011
x350011_g_MissionName = "ʥ����������"
x350011_g_AwardInfo = "\t��#G12��22������1��4��#W��ÿ���#G12��00��12��10��15��00��15��10��18��00��18��10��21��00��21��10��#W��λ��ҿ�����������ȡʥ�����\n\t#G��Ը����#W��#G������#W�Ͱ�������Щʥ�������У������ʹ����Ը���ӻ�������ȥʥ��������Ը����"

--�����NPC��
function x350011_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

	AddQuestNumText(sceneId,x350011_g_ScriptId,x350011_g_MissionName,0,-1)
	return 0
	
end



--�������ť������������ִ�д˽ű�
function x350011_ProcEventEntry( sceneId, selfId, targetId,state,index )	
	
	BeginQuestEvent(sceneId)
	AddQuestText(sceneId,x350011_g_AwardInfo)
	EndQuestEvent(sceneId)
	DispatchQuestEventList( sceneId,selfId,targetId )

	--x350011_DispatchMissionInfo( sceneId, selfId, targetId,index)

end

function x350011_DispatchMissionInfo( sceneId, selfId, targetId,index)


end



--**********************************
--����
--**********************************
function x350011_ProcAccept( sceneId, selfId )
end

function x350011_ProcAcceptCheck( sceneId, selfId, NPCId )
	return 1
end
--�����ȷ����
function x350011_ProcQuestAccept( sceneId, selfId, NPCId )
end

--**********************************
--����
--**********************************
function x350011_ProcQuestAbandon( sceneId, selfId, MissionId )
end
--**********************************
--����
--**********************************
function x350011_OnContinue( sceneId, selfId, targetId )
end
--**********************************
--����Ƿ�����ύ
--**********************************
function x350011_CheckSubmit( sceneId, selfId )
end
--**********************************
--�ύ
--**********************************
function x350011_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end
--**********************************
--ɱ����������
--**********************************
function x350011_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end
--**********************************
--��������