--���ܣ���Ʒ�̵�

x560115_g_ScriptId = 560115
x560115_g_MissionName="�����̵�"
x560115_g_ShopList={115}
--**********************************

--������ں���

--**********************************

function x560115_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x560115_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x560115_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
		AddQuestNumText(sceneId, x560115_g_ScriptId, x560115_g_MissionName,10)
end



--**********************************

--����������

--**********************************

function x560115_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x560115_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x560115_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x560115_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x560115_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x560115_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x560115_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x560115_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end