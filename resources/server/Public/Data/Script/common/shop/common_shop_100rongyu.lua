--���ܣ���ְҵ����������

x560094_g_ScriptId = 560094
x560094_g_MissionName="100�����̵�"
x560094_g_ShopList={22,25,28,31,34,37}
--**********************************

--������ں���

--**********************************

function x560094_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	local	zhiye = GetZhiye(sceneId, selfId)
	
	if zhiye == 0 then
		DispatchShopItem( sceneId, selfId, targetId, x560094_g_ShopList[1] )
		
		elseif zhiye == 1 then
		DispatchShopItem( sceneId, selfId, targetId, x560094_g_ShopList[2] )
		
		elseif zhiye == 2 then
		DispatchShopItem( sceneId, selfId, targetId, x560094_g_ShopList[3] )
		
		elseif zhiye == 3 then
		DispatchShopItem( sceneId, selfId, targetId, x560094_g_ShopList[4] )
		
		elseif zhiye == 4 then
		DispatchShopItem( sceneId, selfId, targetId, x560094_g_ShopList[5] )
		
		elseif zhiye == 5 then
		DispatchShopItem( sceneId, selfId, targetId, x560094_g_ShopList[6] )
	
	end
	
	
end



--**********************************

--�о��¼�

--**********************************

function x560094_ProcEnumEvent(sceneId, selfId, targetId, MissionId)

		AddQuestNumText(sceneId, x560094_g_ScriptId, x560094_g_MissionName,10)
end



--**********************************

--����������

--**********************************

function x560094_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x560094_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x560094_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x560094_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x560094_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x560094_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x560094_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x560094_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end