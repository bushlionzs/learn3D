--���ܣ���ְҵ70����ʱ�ʯ��

x560160_g_ScriptId = 560160
x560160_g_MissionName="��ʮ��������ʯ��"
x560160_g_ShopList={160,161,162,163,164,165,1203,1207,1211,1215,1219,1223}
--**********************************

--������ں���

--**********************************

function x560160_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	local	zhiye = GetZhiye(sceneId, selfId)
	
	if zhiye == 0 then
		DispatchShopItem( sceneId, selfId, targetId, x560160_g_ShopList[1] )
		
		elseif zhiye == 1 then
		DispatchShopItem( sceneId, selfId, targetId, x560160_g_ShopList[2] )
		
		elseif zhiye == 2 then
		DispatchShopItem( sceneId, selfId, targetId, x560160_g_ShopList[3] )
		
		elseif zhiye == 3 then
		DispatchShopItem( sceneId, selfId, targetId, x560160_g_ShopList[4] )
		
		elseif zhiye == 4 then
		DispatchShopItem( sceneId, selfId, targetId, x560160_g_ShopList[5] )
		
		elseif zhiye == 5 then
		DispatchShopItem( sceneId, selfId, targetId, x560160_g_ShopList[6] )
		
		elseif zhiye == 6 then
		DispatchShopItem( sceneId, selfId, targetId, x560160_g_ShopList[7] )
		
		elseif zhiye == 7 then
		DispatchShopItem( sceneId, selfId, targetId, x560160_g_ShopList[8] )
		
		elseif zhiye == 8 then
		DispatchShopItem( sceneId, selfId, targetId, x560160_g_ShopList[9] )
		
		elseif zhiye == 9 then
		DispatchShopItem( sceneId, selfId, targetId, x560160_g_ShopList[10] )
		
		elseif zhiye == 10 then
		DispatchShopItem( sceneId, selfId, targetId, x560160_g_ShopList[11] )
		
		elseif zhiye == 11 then
		DispatchShopItem( sceneId, selfId, targetId, x560160_g_ShopList[12] )
	
	end
	
	
end



--**********************************

--�о��¼�

--**********************************

function x560160_ProcEnumEvent(sceneId, selfId, targetId, MissionId)

	local nLevel = GetLevel(sceneId, selfId)
	if nLevel >= 70 then
		AddQuestNumText(sceneId, x560160_g_ScriptId, x560160_g_MissionName,10)
	else
		return
	end

end



--**********************************

--����������

--**********************************

function x560160_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x560160_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x560160_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x560160_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x560160_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x560160_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x560160_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x560160_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end