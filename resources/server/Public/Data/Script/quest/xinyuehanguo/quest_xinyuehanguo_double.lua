--���ܣ���˫���
--NPC�����־�ͳ��

--MisDescBegin
x211034_g_ScriptId = 211034

--MisDescEnd
--**********************************

--������ں���

--**********************************

function x211034_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	--BeginQuestEvent(sceneId)
	--	AddQuestText(sceneId, "����ȡ��#GһСʱ#W��˫������ʱ�䣬��ȥ�����ɣ�����Լ�����Խ�Լ���")
	--EndQuestEvent(sceneId)
	--DispatchQuestEventList(sceneId,selfId,targetId)
	--
	--BeginQuestEvent(sceneId)
	--	AddQuestText(sceneId, "����ȡ��һСʱ˫������ʱ��")
	--EndQuestEvent(sceneId)
	--DispatchQuestTips(sceneId,selfId)
end



--**********************************

--�о��¼�

--**********************************

function x211034_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
	AddQuestNumText(sceneId, 211034, "һСʱ")
end

--**********************************

--����������

--**********************************

function x211034_ProcAcceptCheck(sceneId, selfId, targetId)
end


--**********************************

--����

--**********************************

function x211034_ProcAccept(sceneId, selfId)
end



--**********************************

--����

--**********************************

function x211034_ProcQuestAbandon(sceneId, selfId, MissionId)
end



--**********************************

--����Ƿ�����ύ

--**********************************

function x211034_CheckSubmit( sceneId, selfId, targetId)
end



--**********************************

--�ύ

--**********************************

function x211034_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
end



--**********************************

--ɱ����������

--**********************************

function x211034_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
end



--**********************************

--���������¼�

--**********************************

function x211034_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)
end



--**********************************

--���߸ı�

--**********************************

function x211034_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
end