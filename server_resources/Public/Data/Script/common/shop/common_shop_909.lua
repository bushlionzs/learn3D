--���ܣ���Ʊ�̵�

x560909_g_ScriptId = 560909
x560909_g_MissionName="��Ʊ�̵�"
x560909_g_ShopList={909}
--**********************************

--������ں���

--**********************************

function x560909_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x560909_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x560909_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
		AddQuestNumText(sceneId, x560909_g_ScriptId, x560909_g_MissionName,10)
end



--**********************************

--����������

--**********************************

function x560909_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x560909_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x560909_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x560909_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x560909_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x560909_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x560909_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x560909_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end