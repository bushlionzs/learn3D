--功能：平衡天赋金币商店

x561260_g_ScriptId = 561260
x561260_g_MissionName="平衡天赋金币商店"
x561260_g_ShopList={1260}
--**********************************

--任务入口函数

--**********************************

function x561260_ProcEventEntry(sceneId, selfId, targetId)	--点击该任务后执行此脚本
	DispatchShopItem( sceneId, selfId, targetId, x561260_g_ShopList[1] )
end



--**********************************

--列举事件

--**********************************

function x561260_ProcEnumEvent(sceneId, selfId, targetId, MissionId)	

	local nLevel = GetLevel(sceneId,selfId)
	if nLevel >= 80 then
		AddQuestNumText(sceneId, x561260_g_ScriptId, x561260_g_MissionName,10)
	else
		return
	end
	
end



--**********************************

--检测接受条件

--**********************************

function x561260_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--接受

--**********************************

function x561260_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--放弃

--**********************************

function x561260_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--检测是否可以提交

--**********************************

function x561260_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--提交

--**********************************

function x561260_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--杀死怪物或玩家

--**********************************

function x561260_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--进入区域事件

--**********************************

function x561260_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--道具改变

--**********************************

function x561260_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end