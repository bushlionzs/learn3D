--���ܣ����ҳＯ����
--NPC���������

--MisDescBegin
x211007_g_ScriptId = 211007

x211007_g_MissionName = "�Ｏ����"
--MisDescEnd
--**********************************

--������ں���

--**********************************

function x211007_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y�Ｏ����")
		AddQuestText(sceneId, "ǰ�ߵ�սʿ������ԡѪ��ս�����������ڵ�һ�����ܵ����ӣ��������ǵĴ�󷽡�")
	EndQuestEvent(sceneId)
	DispatchQuestEventList(sceneId,selfId,targetId)
end



--**********************************

--�о��¼�

--**********************************

function x211007_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
	AddQuestNumText(sceneId, x211007_g_ScriptId, x211007_g_MissionName)
end



--**********************************

--����������

--**********************************

function x211007_ProcAcceptCheck(sceneId, selfId, targetId)

end



--**********************************

--����

--**********************************

function x211007_ProcAccept(sceneId, selfId)
    
end



--**********************************

--����

--**********************************

function x211007_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x211007_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x211007_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x211007_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x211007_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x211007_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end