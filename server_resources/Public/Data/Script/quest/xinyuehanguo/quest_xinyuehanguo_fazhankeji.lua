--���ܣ����ҷ�չ�Ƽ�����
--NPC����˾ͽ

--MisDescBegin
x211002_g_ScriptId = 211002

x211002_g_MissionName = "��չ�Ƽ�"
--MisDescEnd
--**********************************

--������ں���

--**********************************

function x211002_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y��չ�Ƽ�")
		AddQuestText(sceneId, "����Ҫ��չǿ����Ҫ�Ƽ��Ĳ�����������ǿ����ǿ��������������Ϊ�����ף��岻�ݴǡ�")
	EndQuestEvent(sceneId)
	DispatchQuestEventList(sceneId,selfId,targetId)
end



--**********************************

--�о��¼�

--**********************************

function x211002_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
	AddQuestNumText(sceneId, x211002_g_ScriptId, x211002_g_MissionName)
end



--**********************************

--����������

--**********************************

function x211002_ProcAcceptCheck(sceneId, selfId, targetId)

end



--**********************************

--����

--**********************************

function x211002_ProcAccept(sceneId, selfId)
    
end



--**********************************

--����

--**********************************

function x211002_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x211002_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x211002_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x211002_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x211002_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x211002_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end