--���ܣ���������
--NPC�����º��� ����˹


x211010_g_ScriptId = 211010
x211010_g_MissionName="��������"

--**********************************

--������ں���

--**********************************

function x211010_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y��������")
		AddQuestText(sceneId, "����˹�����������������������ı����£��Ҳ���������ϻ�ڷ��ԡ��Һ��Ҷ��ܹ���˹�����ǹ���˹���˵�����Ұ�����ʲô����������������˹���˺�æ�����������˵ģ�֪������")
	EndQuestEvent(sceneId)
	DispatchQuestEventList(sceneId,selfId,targetId)
end



--**********************************

--�о��¼�

--**********************************

function x211010_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
		AddQuestNumText(sceneId, x211010_g_ScriptId, x211010_g_MissionName)
end



--**********************************

--����������

--**********************************

function x211010_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x211010_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x211010_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x211010_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x211010_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x211010_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x211010_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x211010_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end