--���ܣ���ְҵ60����ʱ�ʯ��

x560022_g_ScriptId = 560022
x560022_g_MissionName="��ʮ��������ʯ��"
x560022_g_ShopList={22,25,28,31,34,37,1202,1206,1210,1214,1218,1222}
--**********************************

--������ں���

--**********************************

function x560022_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	local	zhiye = GetZhiye(sceneId, selfId)
	
	if zhiye == 0 then
		DispatchShopItem( sceneId, selfId, targetId, x560022_g_ShopList[1] )
		
		elseif zhiye == 1 then
		DispatchShopItem( sceneId, selfId, targetId, x560022_g_ShopList[2] )
		
		elseif zhiye == 2 then
		DispatchShopItem( sceneId, selfId, targetId, x560022_g_ShopList[3] )
		
		elseif zhiye == 3 then
		DispatchShopItem( sceneId, selfId, targetId, x560022_g_ShopList[4] )
		
		elseif zhiye == 4 then
		DispatchShopItem( sceneId, selfId, targetId, x560022_g_ShopList[5] )
		
		elseif zhiye == 5 then
		DispatchShopItem( sceneId, selfId, targetId, x560022_g_ShopList[6] )
		
		elseif zhiye == 6 then
		DispatchShopItem( sceneId, selfId, targetId, x560022_g_ShopList[7] )
		
		elseif zhiye == 7 then
		DispatchShopItem( sceneId, selfId, targetId, x560022_g_ShopList[8] )
		
		elseif zhiye == 8 then
		DispatchShopItem( sceneId, selfId, targetId, x560022_g_ShopList[9] )
		
		elseif zhiye == 9 then
		DispatchShopItem( sceneId, selfId, targetId, x560022_g_ShopList[10] )
		
		elseif zhiye == 10 then
		DispatchShopItem( sceneId, selfId, targetId, x560022_g_ShopList[11] )
		
		elseif zhiye == 11 then
		DispatchShopItem( sceneId, selfId, targetId, x560022_g_ShopList[12] )
	
	end
	
	
end



--**********************************

--�о��¼�

--**********************************

function x560022_ProcEnumEvent(sceneId, selfId, targetId, MissionId)

	local nLevel = GetLevel(sceneId, selfId)
	if nLevel >= 60 then
		AddQuestNumText(sceneId, x560022_g_ScriptId, x560022_g_MissionName,10)
	else
		return
	end

end



--**********************************

--����������

--**********************************

function x560022_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x560022_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x560022_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x560022_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x560022_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x560022_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x560022_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x560022_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end