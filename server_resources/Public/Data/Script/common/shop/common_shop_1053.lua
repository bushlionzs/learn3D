--功能：战场功绩商店

x561053_g_ScriptId = 561053
x561053_g_MissionName="40级战功装备商店"
x561053_g_ShopList={1053,1054,1055,1056,1057,1058,1059,1060,1061,1062,1063,1064}
--**********************************

--任务入口函数

--**********************************

function x561053_ProcEventEntry(sceneId, selfId, targetId)	--点击该任务后执行此脚本
	local	zhiye = GetZhiye(sceneId, selfId)
	if GetTopListInfo_MinLevel( GetWorldID( sceneId, selfId) ) < 60 then
		Msg2Player(sceneId,selfId,"很抱歉，等级排行榜最后一名玩家未到60级，此商店尚未开放",8,3)
   		return
  	end
	if zhiye == 0 then
		DispatchShopItem( sceneId, selfId, targetId, x561053_g_ShopList[1] )
		
		elseif zhiye == 1 then
		DispatchShopItem( sceneId, selfId, targetId, x561053_g_ShopList[2] )
		
		elseif zhiye == 2 then
		DispatchShopItem( sceneId, selfId, targetId, x561053_g_ShopList[3] )
		
		elseif zhiye == 3 then
		DispatchShopItem( sceneId, selfId, targetId, x561053_g_ShopList[4] )
		
		elseif zhiye == 4 then
		DispatchShopItem( sceneId, selfId, targetId, x561053_g_ShopList[5] )
		
		elseif zhiye == 5 then
		DispatchShopItem( sceneId, selfId, targetId, x561053_g_ShopList[6] )
		
		elseif zhiye == 6 then
		DispatchShopItem( sceneId, selfId, targetId, x561053_g_ShopList[7] )
		
		elseif zhiye == 7 then
		DispatchShopItem( sceneId, selfId, targetId, x561053_g_ShopList[8] )
		
		elseif zhiye == 8 then
		DispatchShopItem( sceneId, selfId, targetId, x561053_g_ShopList[9] )
		
		elseif zhiye == 9 then
		DispatchShopItem( sceneId, selfId, targetId, x561053_g_ShopList[10] )
		
		elseif zhiye == 10 then
		DispatchShopItem( sceneId, selfId, targetId, x561053_g_ShopList[11] )
		
		elseif zhiye == 11 then
		DispatchShopItem( sceneId, selfId, targetId, x561053_g_ShopList[12] )
	
	end
	
	
end



--**********************************

--列举事件

--**********************************

function x561053_ProcEnumEvent(sceneId, selfId, targetId, MissionId)

		AddQuestNumText(sceneId, x561053_g_ScriptId, x561053_g_MissionName,10)
end



--**********************************

--检测接受条件

--**********************************

function x561053_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--接受

--**********************************

function x561053_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--放弃

--**********************************

function x561053_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--检测是否可以提交

--**********************************

function x561053_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--提交

--**********************************

function x561053_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--杀死怪物或玩家

--**********************************

function x561053_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--进入区域事件

--**********************************

function x561053_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--道具改变

--**********************************

function x561053_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end