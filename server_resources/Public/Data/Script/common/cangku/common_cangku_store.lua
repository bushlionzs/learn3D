--���ܣ��ֿ�
--NPC�����º��� �ֿ��ϰ壬�ֿ���

x561000_g_ScriptId = 561000
x561000_g_MissionName="�ֿ�"

--**********************************

--������ں���

--**********************************

function x561000_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	BankBegin(sceneId, selfId,targetId)
end



--**********************************

--�о��¼�

--**********************************

function x561000_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
		AddQuestNumText(sceneId, x561000_g_ScriptId, x561000_g_MissionName,12)
end



--**********************************

--����������

--**********************************

function x561000_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x561000_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x561000_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x561000_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x561000_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x561000_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x561000_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x561000_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end