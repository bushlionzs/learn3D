--���ܣ�����ߵ�

x560309_g_ScriptId = 560309
x560309_g_MissionName="����ߵ�"
x560309_g_ShopList={309}
--**********************************

--������ں���

--**********************************

function x560309_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x560309_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x560309_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
		AddQuestNumText(sceneId, x560309_g_ScriptId, x560309_g_MissionName,10)
end



--**********************************

--����������

--**********************************

function x560309_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x560309_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x560309_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x560309_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x560309_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x560309_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x560309_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x560309_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end