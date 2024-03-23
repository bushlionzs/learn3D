--功能：武器店
--NPC：武器店老板

x211062_g_ScriptId = 211062
x211062_g_MissionName="骑乘商店二"
x211062_g_ShopList={12}
--**********************************

--任务入口函数

--**********************************

function x211062_ProcEventEntry(sceneId, selfId, targetId)	--点击该任务后执行此脚本
	DispatchShopItem( sceneId, selfId, targetId, x211062_g_ShopList[1] )
end



--**********************************

--列举事件

--**********************************

function x211062_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
		AddQuestNumText(sceneId, x211062_g_ScriptId, x211062_g_MissionName)
end



--**********************************

--检测接受条件

--**********************************

function x211062_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--接受

--**********************************

function x211062_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--放弃

--**********************************

function x211062_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--检测是否可以提交

--**********************************

function x211062_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--提交

--**********************************

function x211062_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--杀死怪物或玩家

--**********************************

function x211062_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--进入区域事件

--**********************************

function x211062_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--道具改变

--**********************************

function x211062_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end