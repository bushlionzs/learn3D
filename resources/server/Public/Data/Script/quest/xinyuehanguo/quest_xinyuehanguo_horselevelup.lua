--���ܣ����ǿ������
--NPC�����ǿ����ʦ

--MisDescBegin
x211027_g_ScriptId = 211027

x211027_g_MissionName = "��˷�ֳ"
--MisDescEnd
--**********************************

--������ں���

--**********************************

function x211027_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y��˷�ֳ")
		AddQuestText(sceneId, "�������ѵð���������һƥ����˭��ϣ�������õø����ء�������ֳ��õ�����ԣ����ǳ����еĳ��ã������е���������")
	EndQuestEvent(sceneId)
	DispatchQuestEventList(sceneId,selfId,targetId)
end



--**********************************

--�о��¼�

--**********************************

function x211027_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
	AddQuestNumText(sceneId, x211027_g_ScriptId, x211027_g_MissionName)
end



--**********************************

--����������

--**********************************

function x211027_ProcAcceptCheck(sceneId, selfId, targetId)

end



--**********************************

--����

--**********************************

function x211027_ProcAccept(sceneId, selfId)
    
end



--**********************************

--����

--**********************************

function x211027_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x211027_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x211027_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x211027_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x211027_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x211027_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end