--功能：突厥锻造术副手类武器配方店

x560834_g_ScriptId = 560834
x560834_g_MissionName="突厥锻造术副武器配方店"
x560834_g_ShopList={834}
--**********************************

--任务入口函数

--**********************************

function x560834_ProcEventEntry(sceneId, selfId, targetId)	--点击该任务后执行此脚本
	DispatchShopItem( sceneId, selfId, targetId, x560834_g_ShopList[1] )
end



--**********************************

--列举事件

--**********************************

function x560834_ProcEnumEvent(sceneId, selfId, targetId, MissionId)	

	local nLevel = GetLevel(sceneId,selfId)
	if nLevel >= 0 then
		AddQuestNumText(sceneId, x560834_g_ScriptId, x560834_g_MissionName,10)
	else
		return
	end
	
end



--**********************************

--检测接受条件

--**********************************

function x560834_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--接受

--**********************************

function x560834_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--放弃

--**********************************

function x560834_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--检测是否可以提交

--**********************************

function x560834_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--提交

--**********************************

function x560834_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--杀死怪物或玩家

--**********************************

function x560834_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--进入区域事件

--**********************************

function x560834_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--道具改变

--**********************************

function x560834_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end