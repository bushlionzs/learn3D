--���ܣ���Ʒ�̵�

x560134_g_ScriptId = 560134
x560134_g_MissionName="ҩƷ�����䷽�̵�"
x560134_g_ShopList={134}
--**********************************

--������ں���

--**********************************

function x560134_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x560134_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x560134_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
		AddQuestNumText(sceneId, x560134_g_ScriptId, x560134_g_MissionName,10)
end



--**********************************

--����������

--**********************************

function x560134_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x560134_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x560134_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x560134_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x560134_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x560134_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x560134_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x560134_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end