--���ܣ���ְҵ����װ����

x560086_g_ScriptId = 560086
x560086_g_MissionName="��ȡ����������װ"
x560086_g_ShopList={60,63,66,69,72,75,1150,1154,1158,1162,1166,1170}
--**********************************

--������ں���

--**********************************

function x560086_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	local	zhiye = GetZhiye(sceneId, selfId)
	
	if zhiye == 0 then
		DispatchShopItem( sceneId, selfId, targetId, x560086_g_ShopList[1] )
		
		elseif zhiye == 1 then
		DispatchShopItem( sceneId, selfId, targetId, x560086_g_ShopList[2] )
		
		elseif zhiye == 2 then
		DispatchShopItem( sceneId, selfId, targetId, x560086_g_ShopList[3] )
		
		elseif zhiye == 3 then
		DispatchShopItem( sceneId, selfId, targetId, x560086_g_ShopList[4] )
		
		elseif zhiye == 4 then
		DispatchShopItem( sceneId, selfId, targetId, x560086_g_ShopList[5] )
		
		elseif zhiye == 5 then
		DispatchShopItem( sceneId, selfId, targetId, x560086_g_ShopList[6] )
		
		elseif zhiye == 6 then
		DispatchShopItem( sceneId, selfId, targetId, x560086_g_ShopList[7] )
		
		elseif zhiye == 7 then
		DispatchShopItem( sceneId, selfId, targetId, x560086_g_ShopList[8] )
		
		elseif zhiye == 8 then
		DispatchShopItem( sceneId, selfId, targetId, x560086_g_ShopList[9] )
		
		elseif zhiye == 9 then
		DispatchShopItem( sceneId, selfId, targetId, x560086_g_ShopList[10] )
		
		elseif zhiye == 10 then
		DispatchShopItem( sceneId, selfId, targetId, x560086_g_ShopList[11] )
		
		elseif zhiye == 11 then
		DispatchShopItem( sceneId, selfId, targetId, x560086_g_ShopList[12] )
	
	end
	if IsHaveQuest(sceneId,selfId, 3092) > 0 and x256226_CheckSubmit( sceneId, selfId, NPCId) <= 0 then
		CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 33,1 )
	end
	
end



--**********************************

--�о��¼�

--**********************************

function x560086_ProcEnumEvent(sceneId, selfId, targetId, MissionId)

		AddQuestNumText(sceneId, x560086_g_ScriptId, x560086_g_MissionName,10)
end



--**********************************

--����������

--**********************************

function x560086_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x560086_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x560086_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x560086_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x560086_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x560086_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x560086_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x560086_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end