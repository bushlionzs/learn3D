--功能：大都药品店

x560303_g_ScriptId = 560303
x560303_g_MissionName="药品店"
x560303_g_ShopList={303}
--**********************************

--任务入口函数

--**********************************

function x560303_ProcEventEntry(sceneId, selfId, targetId)	--点击该任务后执行此脚本
	DispatchShopItem( sceneId, selfId, targetId, x560303_g_ShopList[1] )
end



--**********************************

--列举事件

--**********************************

function x560303_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
		AddQuestNumText(sceneId, x560303_g_ScriptId, x560303_g_MissionName,10)
end



--**********************************

--检测接受条件

--**********************************

function x560303_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--接受

--**********************************

function x560303_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--放弃

--**********************************

function x560303_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--检测是否可以提交

--**********************************

function x560303_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--提交

--**********************************

function x560303_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--杀死怪物或玩家

--**********************************

function x560303_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--进入区域事件

--**********************************

function x560303_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--道具改变

--**********************************

function x560303_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end