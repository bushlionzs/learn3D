--���ܣ��ӻ��̵�

x560906_g_ScriptId = 560906
x560906_g_MissionName="�ӻ��̵�"
x560906_g_ShopList={906}
--**********************************

--������ں���

--**********************************

function x560906_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x560906_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x560906_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
		AddQuestNumText(sceneId, x560906_g_ScriptId, x560906_g_MissionName,10)
end



--**********************************

--����������

--**********************************

function x560906_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x560906_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x560906_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x560906_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x560906_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x560906_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x560906_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x560906_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end