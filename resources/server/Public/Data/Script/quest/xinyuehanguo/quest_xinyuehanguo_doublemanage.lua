--���ܣ���˫���
--NPC�����־�ͳ��

--MisDescBegin
x211001_g_ScriptId = 211001
x211001_g_EventList={211034}

--MisDescEnd
--**********************************

--������ں���

--**********************************

function x211001_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"�������Ǿ��ӻ������࣬����������󣬽��������º�������ʿ���Ÿ����˫������ʱ�䡣���Ҫע�����ǵ�������ʾ�ˡ�")
	EndQuestEvent(sceneId)
	DispatchQuestEventList(sceneId,selfId,targetId)	
end



--**********************************

--�о��¼�

--**********************************

function x211001_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
	AddQuestNumText(sceneId, x211001_g_ScriptId, "��ȡ˫��ʱ��")
end

--**********************************

--����������

--**********************************

function x211001_ProcAcceptCheck(sceneId, selfId, targetId)

end


--**********************************

--����

--**********************************

function x211001_ProcAccept(sceneId, selfId)

end



--**********************************

--����

--**********************************

function x211001_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x211001_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x211001_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)

end



--**********************************

--ɱ����������

--**********************************

function x211001_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x211001_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x211001_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end