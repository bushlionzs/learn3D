--���ܣ��ӻ���
--NPC���ӻ����ϰ�

x211018_g_ScriptId = 211018
x211018_g_MissionName="�ӻ��̵�"
x211018_g_ShopList={2}
--**********************************

--������ں���

--**********************************

function x211018_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x211018_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x211018_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
		AddQuestNumText(sceneId, x211018_g_ScriptId, x211018_g_MissionName)
end



--**********************************

--����������

--**********************************

function x211018_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x211018_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x211018_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x211018_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x211018_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x211018_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x211018_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x211018_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end