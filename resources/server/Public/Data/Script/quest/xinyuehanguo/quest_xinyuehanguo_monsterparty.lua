--���ܣ������ܶ�Ա
--NPC�����º��� ����

x211013_g_ScriptId = 211013
x211013_g_MissionName="�����ܶ�Ա"

--**********************************

--������ں���

--**********************************

function x211013_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y�����ܶ�Ա")
		AddQuestText(sceneId, "������ں������������ſͣ����ֵ���Ҳ�в������Ը��ص��˲ţ���ɸ������ǽ�����������Ҳ���ÿ��������ǲ������汾�¡��Ķ��䶷������ѡ��")
	EndQuestEvent(sceneId)
	DispatchQuestEventList(sceneId,selfId,targetId)
end



--**********************************

--�о��¼�

--**********************************

function x211013_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
		AddQuestNumText(sceneId, x211013_g_ScriptId, x211013_g_MissionName)
end



--**********************************

--����������

--**********************************

function x211013_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x211013_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x211013_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x211013_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x211013_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x211013_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x211013_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x211013_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end