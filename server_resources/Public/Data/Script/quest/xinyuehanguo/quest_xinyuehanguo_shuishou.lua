--���ܣ�����˰������
--NPC����˾��

--MisDescBegin
x211003_g_ScriptId = 211003

x211003_g_MissionName = "˰��"
--MisDescEnd
--**********************************

--������ں���

--**********************************

function x211003_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y˰��")
		AddQuestText(sceneId, "���˳����˰�գ����ҾͿ��Է�չ�Ƽ������蹤�̡����ǹ��ص�˰��Ҳ�ᵼ����Թ��������֮��֮����")
	EndQuestEvent(sceneId)
	DispatchQuestEventList(sceneId,selfId,targetId)
end



--**********************************

--�о��¼�

--**********************************

function x211003_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
	AddQuestNumText(sceneId, x211003_g_ScriptId, x211003_g_MissionName)
end



--**********************************

--����������

--**********************************

function x211003_ProcAcceptCheck(sceneId, selfId, targetId)

end



--**********************************

--����

--**********************************

function x211003_ProcAccept(sceneId, selfId)
    
end



--**********************************

--����

--**********************************

function x211003_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x211003_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x211003_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x211003_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x211003_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x211003_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end