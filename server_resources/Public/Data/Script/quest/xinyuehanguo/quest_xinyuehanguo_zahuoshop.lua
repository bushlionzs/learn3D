--功能：杂货店
--NPC：杂货店老板

x211018_g_ScriptId = 211018
x211018_g_MissionName="杂货商店"
x211018_g_ShopList={2}
--**********************************

--任务入口函数

--**********************************

function x211018_ProcEventEntry(sceneId, selfId, targetId)	--点击该任务后执行此脚本
	DispatchShopItem( sceneId, selfId, targetId, x211018_g_ShopList[1] )
end



--**********************************

--列举事件

--**********************************

function x211018_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
		AddQuestNumText(sceneId, x211018_g_ScriptId, x211018_g_MissionName)
end



--**********************************

--检测接受条件

--**********************************

function x211018_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--接受

--**********************************

function x211018_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--放弃

--**********************************

function x211018_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--检测是否可以提交

--**********************************

function x211018_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--提交

--**********************************

function x211018_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--杀死怪物或玩家

--**********************************

function x211018_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--进入区域事件

--**********************************

function x211018_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--道具改变

--**********************************

function x211018_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end