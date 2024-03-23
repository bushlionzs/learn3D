--功能：舞厅道具商店

x300164_g_ScriptId = 300164
x300164_g_MissionName="【美丽会】商店"
x300164_g_ShopList={903}
--**********************************

--任务入口函数

--**********************************

function x300164_ProcEventEntry(sceneId, selfId, targetId)	--点击该任务后执行此脚本
	DispatchShopItem( sceneId, selfId, targetId, x300164_g_ShopList[1] )
end



--**********************************

--列举事件

--**********************************

function x300164_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
		AddQuestNumText(sceneId, x300164_g_ScriptId, x300164_g_MissionName,10)
end



--**********************************

--检测接受条件

--**********************************

function x300164_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--接受

--**********************************

function x300164_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--放弃

--**********************************

function x300164_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--检测是否可以提交

--**********************************

function x300164_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--提交

--**********************************

function x300164_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--杀死怪物或玩家

--**********************************

function x300164_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--进入区域事件

--**********************************

function x300164_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--道具改变

--**********************************

function x300164_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end