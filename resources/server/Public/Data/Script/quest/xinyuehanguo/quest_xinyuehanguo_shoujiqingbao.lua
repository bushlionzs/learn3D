--���ܣ������ռ��鱨
--NPC���ȷ潫��

--MisDescBegin
x211005_g_ScriptId = 211005

x211005_g_MissionName = "�ռ��鱨"
--MisDescEnd
--**********************************

--������ں���

--**********************************

function x211005_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y�ռ��鱨")
		AddQuestText(sceneId, "������ս���鱨���ռ�������Ϊ��Ҫ���鱨��Ա��Ȼ����ս���ϳ������ɱ�У�����һ����Ҫ���鱨������ɱ�������������С�")
	EndQuestEvent(sceneId)
	DispatchQuestEventList(sceneId,selfId,targetId)
end



--**********************************

--�о��¼�

--**********************************

function x211005_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
	AddQuestNumText(sceneId, x211005_g_ScriptId, x211005_g_MissionName)
end



--**********************************

--����������

--**********************************

function x211005_ProcAcceptCheck(sceneId, selfId, targetId)

end



--**********************************

--����

--**********************************

function x211005_ProcAccept(sceneId, selfId)
    
end



--**********************************

--����

--**********************************

function x211005_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x211005_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x211005_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x211005_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x211005_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x211005_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end