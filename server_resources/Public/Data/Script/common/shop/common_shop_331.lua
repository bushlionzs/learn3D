--功能：金铲店

x560331_g_ScriptId = 560331
x560331_g_MissionName="灵魂印配方商店"
x560331_g_ShopList={331}
--**********************************

--任务入口函数

--**********************************

function x560331_ProcEventEntry(sceneId, selfId, targetId)	--点击该任务后执行此脚本
	
	if GetTopListInfo_MinLevel( GetWorldID( sceneId, selfId) ) < 80 then
		Msg2Player(sceneId,selfId,"很抱歉，等级排行榜最后一名玩家未到80级，此商店尚未开放",8,3)
    return
  end

	DispatchShopItem( sceneId, selfId, targetId, x560331_g_ShopList[1] )
end



--**********************************

--列举事件

--**********************************

function x560331_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
		AddQuestNumText(sceneId, x560331_g_ScriptId, x560331_g_MissionName,10)
end



--**********************************

--检测接受条件

--**********************************

function x560331_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--接受

--**********************************

function x560331_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--放弃

--**********************************

function x560331_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--检测是否可以提交

--**********************************

function x560331_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--提交

--**********************************

function x560331_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--杀死怪物或玩家

--**********************************

function x560331_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--进入区域事件

--**********************************

function x560331_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--道具改变

--**********************************

function x560331_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end