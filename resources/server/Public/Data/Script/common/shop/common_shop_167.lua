--���ܣ�6���ﹱ�̵�

x560167_g_ScriptId = 560167
x560167_g_MissionName="�����ﹱ�̵�"
x560167_g_ShopList={167}
--**********************************

--������ں���

--**********************************

function x560167_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x560167_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x560167_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
		AddQuestNumText(sceneId, x560167_g_ScriptId, x560167_g_MissionName,10)
end



--**********************************

--����������

--**********************************

function x560167_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x560167_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x560167_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x560167_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x560167_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x560167_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x560167_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x560167_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end