--���ܣ����Ŵ���
--NPC�����Ŵ���ʹ��

x211028_g_ScriptId = 211028
x211028_g_MissionName="�����㳡"
--**********************************

--������ں���

--**********************************

function x211028_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	SetPos(sceneId, selfId,108,258)
end



--**********************************

--�о��¼�

--**********************************

function x211028_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
		AddQuestNumText(sceneId, x211028_g_ScriptId, x211028_g_MissionName)
end



--**********************************

--����������

--**********************************

function x211028_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x211028_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x211028_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x211028_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x211028_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x211028_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x211028_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x211028_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end