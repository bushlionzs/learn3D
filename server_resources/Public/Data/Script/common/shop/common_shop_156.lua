--���ܣ�2���ﹱ�̵�

x560156_g_ScriptId = 560156
x560156_g_MissionName="�����ﹱ�̵�"
x560156_g_ShopList={156}
--**********************************

--������ں���

--**********************************

function x560156_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x560156_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x560156_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
		AddQuestNumText(sceneId, x560156_g_ScriptId, x560156_g_MissionName,10)
end



--**********************************

--����������

--**********************************

function x560156_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x560156_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x560156_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x560156_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x560156_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x560156_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x560156_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x560156_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end