--���ܣ�����ܲ��ϵ�

x560907_g_ScriptId = 560907
x560907_g_MissionName="����ܲ��ϵ�"
x560907_g_ShopList={907}
--**********************************

--������ں���

--**********************************

function x560907_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x560907_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x560907_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
		AddQuestNumText(sceneId, x560907_g_ScriptId, x560907_g_MissionName,10)
end



--**********************************

--����������

--**********************************

function x560907_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x560907_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x560907_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x560907_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x560907_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x560907_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x560907_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x560907_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end