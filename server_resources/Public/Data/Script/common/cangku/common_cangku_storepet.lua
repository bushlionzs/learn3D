--���ܣ��ֿ�
--NPC�����º��� �ֿ��ϰ壬�ֿ���

x561004_g_ScriptId = 561004
x561004_g_MissionName="��˲ֿ�"

--**********************************

--������ں���

--**********************************

function x561004_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
end



--**********************************

--�о��¼�

--**********************************

function x561004_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
		AddQuestNumText(sceneId, x561004_g_ScriptId, x561004_g_MissionName,12)
end



--**********************************

--����������

--**********************************

function x561004_ProcAcceptCheck(sceneId, selfId, targetId)
	return 1
end

--**********************************

--����

--**********************************

function x561004_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x561004_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x561004_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x561004_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x561004_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x561004_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x561004_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end