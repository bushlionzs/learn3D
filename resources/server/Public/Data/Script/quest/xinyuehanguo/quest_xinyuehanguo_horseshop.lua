--���ܣ�����̵�
--NPC����˵��ϰ�

--MisDescBegin
x211025_g_ScriptId = 211025

x211025_g_MissionName = "����̵�"
--MisDescEnd
--**********************************

--������ں���

--**********************************

function x211025_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, 950 )
end



--**********************************

--�о��¼�

--**********************************

function x211025_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
	AddQuestNumText(sceneId, x211025_g_ScriptId, x211025_g_MissionName)
end



--**********************************

--����������

--**********************************

function x211025_ProcAcceptCheck(sceneId, selfId, targetId)

end



--**********************************

--����

--**********************************

function x211025_ProcAccept(sceneId, selfId)
    
end



--**********************************

--����

--**********************************

function x211025_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x211025_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x211025_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x211025_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x211025_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x211025_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end