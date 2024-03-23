--功能：武器店
--NPC：武器店老板

x211059_g_ScriptId = 211059
x211059_g_MissionName="宝石商店二"
x211059_g_ShopList={9}
--**********************************

--任务入口函数

--**********************************

function x211059_ProcEventEntry(sceneId, selfId, targetId)	--点击该任务后执行此脚本
	DispatchShopItem( sceneId, selfId, targetId, x211059_g_ShopList[1] )
end



--**********************************

--列举事件

--**********************************

function x211059_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
		AddQuestNumText(sceneId, x211059_g_ScriptId, x211059_g_MissionName)
end



--**********************************

--检测接受条件

--**********************************

function x211059_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--接受

--**********************************

function x211059_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--放弃

--**********************************

function x211059_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--检测是否可以提交

--**********************************

function x211059_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--提交

--**********************************

function x211059_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--杀死怪物或玩家

--**********************************

function x211059_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--进入区域事件

--**********************************

function x211059_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--道具改变

--**********************************

function x211059_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end