--功能：中原草药术特殊类物品配方店

x560805_g_ScriptId = 560805
x560805_g_MissionName="中原草药术特殊类物品配方店"
x560805_g_ShopList={805}
--**********************************

--任务入口函数

--**********************************

function x560805_ProcEventEntry(sceneId, selfId, targetId)	--点击该任务后执行此脚本
	DispatchShopItem( sceneId, selfId, targetId, x560805_g_ShopList[1] )
end



--**********************************

--列举事件

--**********************************

function x560805_ProcEnumEvent(sceneId, selfId, targetId, MissionId)	

	local nLevel = GetLevel(sceneId,selfId)
	if nLevel >= 0 then
		AddQuestNumText(sceneId, x560805_g_ScriptId, x560805_g_MissionName,10)
	else
		return
	end
	
end



--**********************************

--检测接受条件

--**********************************

function x560805_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--接受

--**********************************

function x560805_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--放弃

--**********************************

function x560805_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--检测是否可以提交

--**********************************

function x560805_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--提交

--**********************************

function x560805_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--杀死怪物或玩家

--**********************************

function x560805_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--进入区域事件

--**********************************

function x560805_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--道具改变

--**********************************

function x560805_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end