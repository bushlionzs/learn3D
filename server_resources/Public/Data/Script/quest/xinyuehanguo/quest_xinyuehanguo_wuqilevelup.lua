--功能：武器强化功能
--NPC：武器强化大师

--MisDescBegin
x211026_g_ScriptId = 211026

x211026_g_MissionName = "强化材料商店"

x211026_g_ShopList ={6}
--MisDescEnd
--**********************************

--任务入口函数

--**********************************

function x211026_ProcEventEntry(sceneId, selfId, targetId)	--点击该任务后执行此脚本
	DispatchShopItem( sceneId, selfId, targetId, x211026_g_ShopList[1] )
end



--**********************************

--列举事件

--**********************************

function x211026_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
	AddQuestNumText(sceneId, x211026_g_ScriptId, x211026_g_MissionName)
end



--**********************************

--检测接受条件

--**********************************

function x211026_ProcAcceptCheck(sceneId, selfId, targetId)

end



--**********************************

--接受

--**********************************

function x211026_ProcAccept(sceneId, selfId)
    
end



--**********************************

--放弃

--**********************************

function x211026_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--检测是否可以提交

--**********************************

function x211026_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--提交

--**********************************

function x211026_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--杀死怪物或玩家

--**********************************

function x211026_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--进入区域事件

--**********************************

function x211026_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--道具改变

--**********************************

function x211026_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end