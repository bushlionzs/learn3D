--功能：武器店
--NPC：武器店老板

x211058_g_ScriptId = 211058
x211058_g_MissionName="宝石商店一"
x211058_g_ShopList={8}
--**********************************

--任务入口函数

--**********************************

function x211058_ProcEventEntry(sceneId, selfId, targetId)	--点击该任务后执行此脚本
	DispatchShopItem( sceneId, selfId, targetId, x211058_g_ShopList[1] )
end



--**********************************

--列举事件

--**********************************

function x211058_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
		AddQuestNumText(sceneId, x211058_g_ScriptId, x211058_g_MissionName)
end



--**********************************

--检测接受条件

--**********************************

function x211058_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--接受

--**********************************

function x211058_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--放弃

--**********************************

function x211058_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--检测是否可以提交

--**********************************

function x211058_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--提交

--**********************************

function x211058_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--杀死怪物或玩家

--**********************************

function x211058_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--进入区域事件

--**********************************

function x211058_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--道具改变

--**********************************

function x211058_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end