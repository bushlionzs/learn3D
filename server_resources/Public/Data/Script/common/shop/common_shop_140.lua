--���ܣ���Ʒ�̵�

x560140_g_ScriptId = 560140
x560140_g_MissionName="װ�������̵�"
x560140_g_ShopList={140}
--**********************************

--������ں���

--**********************************

function x560140_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x560140_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x560140_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
		AddQuestNumText(sceneId, x560140_g_ScriptId, x560140_g_MissionName,10)
end



--**********************************

--����������

--**********************************

function x560140_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x560140_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x560140_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x560140_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x560140_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x560140_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x560140_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x560140_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end