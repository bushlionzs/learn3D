
x561100_g_ScriptId = 561100
x561100_g_MissionName = "����ȡ����˵����"
x561100_g_AwardInfo = "\t�������������ȡ��Ľ����Լ�ϵͳ�����������������ڡ��ɼ�˼��������������صļ��\n\t����˳���ڹ������м���󣬿��Ե��#G��ȡ��������#W��ť������ȡ��"

--�����NPC��
function x561100_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

	AddQuestNumText(sceneId,x561100_g_ScriptId,x561100_g_MissionName,0,-1)
	return 0
	
end



--�������ť������������ִ�д˽ű�
function x561100_ProcEventEntry( sceneId, selfId, targetId,state,index )	
	
	BeginQuestEvent(sceneId)
	AddQuestText(sceneId,"#Y"..x561100_g_MissionName)
	AddQuestText(sceneId,x561100_g_AwardInfo)
	EndQuestEvent(sceneId)
	DispatchQuestEventList( sceneId,selfId,targetId )

	--x561100_DispatchMissionInfo( sceneId, selfId, targetId,index)

end

function x561100_DispatchMissionInfo( sceneId, selfId, targetId,index)


end



--**********************************
--����
--**********************************
function x561100_ProcAccept( sceneId, selfId )
end

function x561100_ProcAcceptCheck( sceneId, selfId, NPCId )
	return 1
end
--�����ȷ����
function x561100_ProcQuestAccept( sceneId, selfId, NPCId )
end

--**********************************
--����
--**********************************
function x561100_ProcQuestAbandon( sceneId, selfId, MissionId )
end
--**********************************
--����
--**********************************
function x561100_OnContinue( sceneId, selfId, targetId )
end
--**********************************
--����Ƿ�����ύ
--**********************************
function x561100_CheckSubmit( sceneId, selfId )
end
--**********************************
--�ύ
--**********************************
function x561100_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end
--**********************************
--ɱ����������
--**********************************
function x561100_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end
--**********************************
--���������¼�