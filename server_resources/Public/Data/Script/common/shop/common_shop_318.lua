--功能：声望工艺配方

x560318_g_ScriptId = 560318
x560318_g_MissionName="声望工艺配方商店"
x560318_g_ShopList={318}
--**********************************

--任务入口函数

--**********************************

function x560318_ProcEventEntry(sceneId, selfId, targetId)	--点击该任务后执行此脚本
	DispatchShopItem( sceneId, selfId, targetId, x560318_g_ShopList[1] )
end



--**********************************

--列举事件

--**********************************

function x560318_ProcEnumEvent(sceneId, selfId, targetId, MissionId)	

--	local nLevel = GetLevel(sceneId,selfId)
--	if nLevel >= 60 then
		AddQuestNumText(sceneId, x560318_g_ScriptId, x560318_g_MissionName,10)
--	else
--		return
--	end
	
end



--**********************************

--检测接受条件

--**********************************

function x560318_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--接受

--**********************************

function x560318_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--放弃

--**********************************

function x560318_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--检测是否可以提交

--**********************************

function x560318_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--提交

--**********************************

function x560318_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--杀死怪物或玩家

--**********************************

function x560318_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--进入区域事件

--**********************************

function x560318_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--道具改变

--**********************************

function x560318_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end