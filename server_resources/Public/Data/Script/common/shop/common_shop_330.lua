--���ܣ������

x560330_g_ScriptId = 560330
x560330_g_MissionName="�����˼��ҵ�"
x560330_g_ShopList={330}
--**********************************

--������ں���

--**********************************

function x560330_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x560330_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x560330_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
		AddQuestNumText(sceneId, x560330_g_ScriptId, x560330_g_MissionName,10)
end



--**********************************

--����������

--**********************************

function x560330_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x560330_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x560330_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x560330_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x560330_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x560330_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x560330_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x560330_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end