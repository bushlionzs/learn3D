--���ܣ����Ŵ���
--NPC�����Ŵ���ʹ��

x211032_g_ScriptId = 211032
x211032_g_MissionName="�����㳡"
--**********************************

--������ں���

--**********************************

function x211032_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	SetPos(sceneId, selfId,108,258)
end



--**********************************

--�о��¼�

--**********************************

function x211032_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
		AddQuestNumText(sceneId, x211032_g_ScriptId, x211032_g_MissionName)
end



--**********************************

--����������

--**********************************

function x211032_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x211032_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x211032_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x211032_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x211032_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x211032_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x211032_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x211032_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end