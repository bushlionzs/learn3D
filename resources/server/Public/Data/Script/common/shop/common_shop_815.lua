--功能：印度珠宝术特殊类物品配方店

x560815_g_ScriptId = 560815
x560815_g_MissionName="印度珠宝术特殊类物品配方店"
x560815_g_ShopList={815}
--**********************************

--任务入口函数

--**********************************

function x560815_ProcEventEntry(sceneId, selfId, targetId)	--点击该任务后执行此脚本
	DispatchShopItem( sceneId, selfId, targetId, x560815_g_ShopList[1] )
end



--**********************************

--列举事件

--**********************************

function x560815_ProcEnumEvent(sceneId, selfId, targetId, MissionId)	

	local nLevel = GetLevel(sceneId,selfId)
	if nLevel >= 0 then
		AddQuestNumText(sceneId, x560815_g_ScriptId, x560815_g_MissionName,10)
	else
		return
	end
	
end



--**********************************

--检测接受条件

--**********************************

function x560815_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--接受

--**********************************

function x560815_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--放弃

--**********************************

function x560815_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--检测是否可以提交

--**********************************

function x560815_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--提交

--**********************************

function x560815_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--杀死怪物或玩家

--**********************************

function x560815_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--进入区域事件

--**********************************

function x560815_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--道具改变

--**********************************

function x560815_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end