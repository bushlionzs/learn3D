--���ܣ����������̵�

x300164_g_ScriptId = 300164
x300164_g_MissionName="�������᡿�̵�"
x300164_g_ShopList={903}
--**********************************

--������ں���

--**********************************

function x300164_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x300164_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x300164_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
		AddQuestNumText(sceneId, x300164_g_ScriptId, x300164_g_MissionName,10)
end



--**********************************

--����������

--**********************************

function x300164_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x300164_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x300164_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x300164_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x300164_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x300164_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x300164_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x300164_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end