--���ܣ����ҽ��蹤��
--NPC����˾��

--MisDescBegin
x211004_g_ScriptId = 211004

x211004_g_MissionName = "���蹤��"
--MisDescEnd
--**********************************

--������ں���

--**********************************

function x211004_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y���蹤��")
		AddQuestText(sceneId, "���һ�����������ˣ��������������������ߡ�")
	EndQuestEvent(sceneId)
	DispatchQuestEventList(sceneId,selfId,targetId)
end



--**********************************

--�о��¼�

--**********************************

function x211004_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
	AddQuestNumText(sceneId, x211004_g_ScriptId, x211004_g_MissionName)
end



--**********************************

--����������

--**********************************

function x211004_ProcAcceptCheck(sceneId, selfId, targetId)

end



--**********************************

--����

--**********************************

function x211004_ProcAccept(sceneId, selfId)
    
end



--**********************************

--����

--**********************************

function x211004_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x211004_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x211004_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x211004_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x211004_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x211004_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end