--���ܣ����Ŵ���
--NPC�����Ŵ���ʹ��

x211051_g_ScriptId = 211051
x211051_g_MissionName="�����㳡"
--**********************************

--������ں���

--**********************************

function x211051_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	SetPos(sceneId, selfId,108,258)
end



--**********************************

--�о��¼�

--**********************************

function x211051_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
		AddQuestNumText(sceneId, x211051_g_ScriptId, x211051_g_MissionName)
end



--**********************************

--����������

--**********************************

function x211051_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x211051_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x211051_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x211051_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x211051_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x211051_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x211051_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x211051_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end