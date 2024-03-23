--功能：武器店
--NPC：武器店老板

x211063_g_ScriptId = 211063
x211063_g_MissionName="宝石商店三"
x211063_g_ShopList={13}
--**********************************

--任务入口函数

--**********************************

function x211063_ProcEventEntry(sceneId, selfId, targetId)	--点击该任务后执行此脚本
	DispatchShopItem( sceneId, selfId, targetId, x211063_g_ShopList[1] )
end



--**********************************

--列举事件

--**********************************

function x211063_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
		AddQuestNumText(sceneId, x211063_g_ScriptId, x211063_g_MissionName)
end



--**********************************

--检测接受条件

--**********************************

function x211063_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--接受

--**********************************

function x211063_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--放弃

--**********************************

function x211063_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--检测是否可以提交

--**********************************

function x211063_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--提交

--**********************************

function x211063_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--杀死怪物或玩家

--**********************************

function x211063_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--进入区域事件

--**********************************

function x211063_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--道具改变

--**********************************

function x211063_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end