--���ܣ�5���ﹱ�̵�

x560159_g_ScriptId = 560159
x560159_g_MissionName="�弶�ﹱ�̵�"
x560159_g_ShopList={159}
--**********************************

--������ں���

--**********************************

function x560159_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x560159_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x560159_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
		AddQuestNumText(sceneId, x560159_g_ScriptId, x560159_g_MissionName,10)
end



--**********************************

--����������

--**********************************

function x560159_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x560159_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x560159_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x560159_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x560159_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x560159_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x560159_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x560159_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end