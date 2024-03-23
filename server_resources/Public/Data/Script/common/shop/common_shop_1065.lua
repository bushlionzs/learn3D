--功能：战场功绩商店

x561065_g_ScriptId = 561065
x561065_g_MissionName="60级战功装备商店"
x561065_g_ShopList={1065,1066,1067,1068,1069,1070,1071,1072,1073,1074,1075,1076}
--**********************************

--任务入口函数

--**********************************

function x561065_ProcEventEntry(sceneId, selfId, targetId)	--点击该任务后执行此脚本
	local	zhiye = GetZhiye(sceneId, selfId)
	if GetTopListInfo_MinLevel( GetWorldID( sceneId, selfId) ) < 75 then
		Msg2Player(sceneId,selfId,"很抱歉，等级排行榜最后一名玩家未到75级，此商店尚未开放",8,3)
    	return
  	end
	if zhiye == 0 then
		DispatchShopItem( sceneId, selfId, targetId, x561065_g_ShopList[1] )
		
		elseif zhiye == 1 then
		DispatchShopItem( sceneId, selfId, targetId, x561065_g_ShopList[2] )
		
		elseif zhiye == 2 then
		DispatchShopItem( sceneId, selfId, targetId, x561065_g_ShopList[3] )
		
		elseif zhiye == 3 then
		DispatchShopItem( sceneId, selfId, targetId, x561065_g_ShopList[4] )
		
		elseif zhiye == 4 then
		DispatchShopItem( sceneId, selfId, targetId, x561065_g_ShopList[5] )
		
		elseif zhiye == 5 then
		DispatchShopItem( sceneId, selfId, targetId, x561065_g_ShopList[6] )
		
		elseif zhiye == 6 then
		DispatchShopItem( sceneId, selfId, targetId, x561065_g_ShopList[7] )
		
		elseif zhiye == 7 then
		DispatchShopItem( sceneId, selfId, targetId, x561065_g_ShopList[8] )
		
		elseif zhiye == 8 then
		DispatchShopItem( sceneId, selfId, targetId, x561065_g_ShopList[9] )
		
		elseif zhiye == 9 then
		DispatchShopItem( sceneId, selfId, targetId, x561065_g_ShopList[10] )
		
		elseif zhiye == 10 then
		DispatchShopItem( sceneId, selfId, targetId, x561065_g_ShopList[11] )
		
		elseif zhiye == 11 then
		DispatchShopItem( sceneId, selfId, targetId, x561065_g_ShopList[12] )
	
	end
	
	
end



--**********************************

--列举事件

--**********************************

function x561065_ProcEnumEvent(sceneId, selfId, targetId, MissionId)

		AddQuestNumText(sceneId, x561065_g_ScriptId, x561065_g_MissionName,10)
end



--**********************************

--检测接受条件

--**********************************

function x561065_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--接受

--**********************************

function x561065_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--放弃

--**********************************

function x561065_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--检测是否可以提交

--**********************************

function x561065_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--提交

--**********************************

function x561065_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--杀死怪物或玩家

--**********************************

function x561065_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--进入区域事件

--**********************************

function x561065_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--道具改变

--**********************************

function x561065_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end