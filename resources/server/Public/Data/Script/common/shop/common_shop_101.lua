--���ܣ���Ʒ�̵�

x560101_g_ScriptId = 560101
x560101_g_MissionName="�����̵�"
x560101_g_ShopList={101}
--**********************************

--������ں���

--**********************************

function x560101_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x560101_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x560101_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
		AddQuestNumText(sceneId, x560101_g_ScriptId, x560101_g_MissionName,10)
end



--**********************************

--����������

--**********************************

function x560101_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x560101_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x560101_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x560101_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x560101_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x560101_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x560101_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x560101_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end