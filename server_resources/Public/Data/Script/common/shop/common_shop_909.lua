--功能：银票商店

x560909_g_ScriptId = 560909
x560909_g_MissionName="银票商店"
x560909_g_ShopList={909}
--**********************************

--任务入口函数

--**********************************

function x560909_ProcEventEntry(sceneId, selfId, targetId)	--点击该任务后执行此脚本
	DispatchShopItem( sceneId, selfId, targetId, x560909_g_ShopList[1] )
end



--**********************************

--列举事件

--**********************************

function x560909_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
		AddQuestNumText(sceneId, x560909_g_ScriptId, x560909_g_MissionName,10)
end



--**********************************

--检测接受条件

--**********************************

function x560909_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--接受

--**********************************

function x560909_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--放弃

--**********************************

function x560909_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--检测是否可以提交

--**********************************

function x560909_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--提交

--**********************************

function x560909_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--杀死怪物或玩家

--**********************************

function x560909_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--进入区域事件

--**********************************

function x560909_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--道具改变

--**********************************

function x560909_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end