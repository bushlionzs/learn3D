--���ܣ�1���ﹱ�̵�

x560155_g_ScriptId = 560155
x560155_g_MissionName="һ���ﹱ�̵�"
x560155_g_ShopList={155}
--**********************************

--������ں���

--**********************************

function x560155_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x560155_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x560155_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
		AddQuestNumText(sceneId, x560155_g_ScriptId, x560155_g_MissionName,10)
end



--**********************************

--����������

--**********************************

function x560155_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x560155_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x560155_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x560155_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x560155_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x560155_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x560155_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x560155_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end