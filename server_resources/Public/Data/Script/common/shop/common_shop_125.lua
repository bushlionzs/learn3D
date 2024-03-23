--功能：声望宝石配方店

x560125_g_ScriptId = 560125
x560125_g_MissionName="声望宝石配方店"
x560125_g_ShopList={125}
--**********************************

--任务入口函数

--**********************************

function x560125_ProcEventEntry(sceneId, selfId, targetId)	--点击该任务后执行此脚本
	DispatchShopItem( sceneId, selfId, targetId, x560125_g_ShopList[1] )
end



--**********************************

--列举事件

--**********************************

function x560125_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
		AddQuestNumText(sceneId, x560125_g_ScriptId, x560125_g_MissionName,10)
end



--**********************************

--检测接受条件

--**********************************

function x560125_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--接受

--**********************************

function x560125_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--放弃

--**********************************

function x560125_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--检测是否可以提交

--**********************************

function x560125_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--提交

--**********************************

function x560125_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--杀死怪物或玩家

--**********************************

function x560125_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--进入区域事件

--**********************************

function x560125_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--道具改变

--**********************************

function x560125_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end