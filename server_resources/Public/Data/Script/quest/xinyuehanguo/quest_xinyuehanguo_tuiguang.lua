--���ܣ��ƹ�Ա
--NPC�����º��� �ƹ�Ա

x211016_g_ScriptId = 211016
x211016_g_MissionName="�ƹ�Աϵͳ"

--**********************************

--������ں���

--**********************************

function x211016_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y�ƹ�Աϵͳ")
		AddQuestText(sceneId, "ֻҪ�������������˼��뵽��Ϸ���������Ҷ����������൱�Ľ�����")
	EndQuestEvent(sceneId)
	DispatchQuestEventList(sceneId,selfId,targetId)
end



--**********************************

--�о��¼�

--**********************************

function x211016_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
		AddQuestNumText(sceneId, x211016_g_ScriptId, x211016_g_MissionName)
end



--**********************************

--����������

--**********************************

function x211016_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x211016_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x211016_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x211016_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x211016_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x211016_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x211016_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x211016_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end