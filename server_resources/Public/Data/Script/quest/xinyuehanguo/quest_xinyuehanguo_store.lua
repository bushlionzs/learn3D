--���ܣ��ֿ�
--NPC�����º��� �ֿ��ϰ壬�ֿ���

x211017_g_ScriptId = 211017
x211017_g_MissionName="�ֿ�"

--**********************************

--������ں���

--**********************************

function x211017_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	BankBegin(sceneId, selfId,targetId)
end



--**********************************

--�о��¼�

--**********************************

function x211017_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
		AddQuestNumText(sceneId, x211017_g_ScriptId, x211017_g_MissionName)
end



--**********************************

--����������

--**********************************

function x211017_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x211017_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x211017_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x211017_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x211017_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x211017_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x211017_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x211017_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end