--���ܣ���̨����
--NPC�����º��� �շ�

x211008_g_ScriptId = 211008
x211008_g_MissionName="��̨����"

--**********************************

--������ں���

--**********************************

function x211008_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y��̨����")
		AddQuestText(sceneId, "���䳡���������У��ȵ����䳡���ŵ�ʱ�����Ҫ����������������Ǹ����Ƽ�����Ҫһս��������Ҫ���и�����ѧ�������������ң��һ������ġ���Ȼ���һ���ȡһ���С���ˣ���Ҫ�����ھͱ����������Ը������ۣ�")
	EndQuestEvent(sceneId)
	DispatchQuestEventList(sceneId,selfId,targetId)
end



--**********************************

--�о��¼�

--**********************************

function x211008_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
		AddQuestNumText(sceneId, x211008_g_ScriptId, x211008_g_MissionName)
end



--**********************************

--����������

--**********************************

function x211008_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x211008_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x211008_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x211008_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x211008_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x211008_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x211008_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x211008_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end