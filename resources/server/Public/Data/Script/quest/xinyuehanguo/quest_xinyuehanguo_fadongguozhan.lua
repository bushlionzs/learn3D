--���ܣ����ҷ�����ս
--NPC���о�����

--MisDescBegin
x211006_g_ScriptId = 211006

x211006_g_MissionName = "������ս"
--MisDescEnd
--**********************************

--������ں���

--**********************************

function x211006_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y������ս")
		AddQuestText(sceneId, "���ڵ��ˣ����Ǽ������ʾ�������ֹ��˵�ս�����飬�ҹ�������ս���������Ȼ���")
	EndQuestEvent(sceneId)
	DispatchQuestEventList(sceneId,selfId,targetId)
end



--**********************************

--�о��¼�

--**********************************

function x211006_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
	AddQuestNumText(sceneId, x211006_g_ScriptId, x211006_g_MissionName)
end



--**********************************

--����������

--**********************************

function x211006_ProcAcceptCheck(sceneId, selfId, targetId)

end



--**********************************

--����

--**********************************

function x211006_ProcAccept(sceneId, selfId)
    
end



--**********************************

--����

--**********************************

function x211006_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x211006_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x211006_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x211006_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x211006_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x211006_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end