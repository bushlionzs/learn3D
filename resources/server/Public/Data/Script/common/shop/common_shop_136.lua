--���ܣ���Ʒ�̵�

x560136_g_ScriptId = 560136
x560136_g_MissionName="�����̵�"
x560136_g_ShopList={136}
--**********************************

--������ں���

--**********************************

function x560136_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x560136_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x560136_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
		AddQuestNumText(sceneId, x560136_g_ScriptId, x560136_g_MissionName,10)
end



--**********************************

--����������

--**********************************

function x560136_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x560136_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x560136_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x560136_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x560136_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x560136_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x560136_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x560136_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end