--�淨���󶼸���--��������--���

x560916_g_ScriptId = 560916
x560916_g_MissionName="�����������̵�"
x560916_g_ShopList={916}
--**********************************

--������ں���

--**********************************

function x560916_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x560916_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x560916_ProcEnumEvent(sceneId, selfId, targetId, MissionId)

		AddQuestNumText(sceneId, x560916_g_ScriptId, x560916_g_MissionName,10)

end



--**********************************

--����������

--**********************************

function x560916_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x560916_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x560916_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x560916_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x560916_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x560916_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x560916_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x560916_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end