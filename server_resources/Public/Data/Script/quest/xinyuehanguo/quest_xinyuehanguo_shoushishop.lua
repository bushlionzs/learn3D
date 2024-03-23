--功能：首饰店
--NPC：首饰店老板

x211021_g_ScriptId = 211021
x211021_g_MissionName="首饰商店"
x211021_g_ShopList={5}
--**********************************

--任务入口函数

--**********************************

function x211021_ProcEventEntry(sceneId, selfId, targetId)	--点击该任务后执行此脚本
	DispatchShopItem( sceneId, selfId, targetId, x211021_g_ShopList[1] )
end



--**********************************

--列举事件

--**********************************

function x211021_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
		AddQuestNumText(sceneId, x211021_g_ScriptId, x211021_g_MissionName)
end



--**********************************

--检测接受条件

--**********************************

function x211021_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--接受

--**********************************

function x211021_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--放弃

--**********************************

function x211021_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--检测是否可以提交

--**********************************

function x211021_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--提交

--**********************************

function x211021_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--杀死怪物或玩家

--**********************************

function x211021_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--进入区域事件

--**********************************

function x211021_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--道具改变

--**********************************

function x211021_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end