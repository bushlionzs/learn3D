--���ܣ��ճ�����
--NPC�����º��� ����

x211012_g_ScriptId = 211012
x211012_g_MissionName="�ճ�����"

--**********************************

--������ں���

--**********************************

function x211012_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y�ճ�����")
		AddQuestText(sceneId, "�ҳ�����Ǯ��ʲô��û�С�һ���������£����ܵ�Ҫ���������Ҿͷ�����ʾ��ȫ��������Щ�¡����ºã�ÿ�춼��N����������Ұ�æ�ˣ�������æ�ù��������Ը�����ҷֵ�һЩ����˵���ҳ�����Ǯ��ʲô��û�У������Ҳ��������ġ�")
	EndQuestEvent(sceneId)
	DispatchQuestEventList(sceneId,selfId,targetId)
end



--**********************************

--�о��¼�

--**********************************

function x211012_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
		AddQuestNumText(sceneId, x211012_g_ScriptId, x211012_g_MissionName)
end



--**********************************

--����������

--**********************************

function x211012_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x211012_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x211012_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x211012_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x211012_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x211012_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x211012_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x211012_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end