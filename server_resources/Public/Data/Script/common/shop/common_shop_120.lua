--���ܣ���Ʒ�̵�

x560120_g_ScriptId = 560120
x560120_g_MissionName="������ʯ�̵�"
x560120_g_ShopList={120}
--**********************************

--������ں���

--**********************************

function x560120_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x560120_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x560120_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
		AddQuestNumText(sceneId, x560120_g_ScriptId, x560120_g_MissionName,10)
end



--**********************************

--����������

--**********************************

function x560120_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x560120_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x560120_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x560120_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x560120_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x560120_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x560120_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x560120_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end