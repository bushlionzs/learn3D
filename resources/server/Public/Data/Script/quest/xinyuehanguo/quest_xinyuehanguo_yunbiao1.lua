--���ܣ�һ������
--NPC�����º��� ����˹

x211009_g_ScriptId = 211009
x211009_g_MissionName="һ������"

--**********************************

--������ں���

--**********************************

function x211009_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Yһ������")
		AddQuestText(sceneId, "�������������𣿱�����С���ڵ����ҿ��ǳ������ģ��Ա��������������յ�С�ܡ�\nֻҪ��Ը������ҵ����£������Ժ��ڵ��ϻ�ÿ�����Ȼ���ٺ١����ҵ����ֿɲ��ǽ�����ģ�����")
	EndQuestEvent(sceneId)
	DispatchQuestEventList(sceneId,selfId,targetId)
end



--**********************************

--�о��¼�

--**********************************

function x211009_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
		AddQuestNumText(sceneId, x211009_g_ScriptId, x211009_g_MissionName)
end



--**********************************

--����������

--**********************************

function x211009_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x211009_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x211009_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x211009_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x211009_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x211009_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x211009_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x211009_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end