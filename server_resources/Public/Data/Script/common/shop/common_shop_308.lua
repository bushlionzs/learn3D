--功能：大都马技能商店：2级技能书

x560308_g_ScriptId = 560308
x560308_g_MissionName="二级坐骑技能"
x560308_g_ShopList={308}
--**********************************

--任务入口函数

--**********************************

function x560308_ProcEventEntry(sceneId, selfId, targetId)	--点击该任务后执行此脚本
	DispatchShopItem( sceneId, selfId, targetId, x560308_g_ShopList[1] )
end



--**********************************

--列举事件

--**********************************

function x560308_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
	
	local nLevel = GetLevel(sceneId,selfId)
	if nLevel >= 30 then
		AddQuestNumText(sceneId, x560308_g_ScriptId, x560308_g_MissionName,10)
	else
		return
	end
	
end



--**********************************

--检测接受条件

--**********************************

function x560308_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--接受

--**********************************

function x560308_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--放弃

--**********************************

function x560308_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--检测是否可以提交

--**********************************

function x560308_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--提交

--**********************************

function x560308_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--杀死怪物或玩家

--**********************************

function x560308_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--进入区域事件

--**********************************

function x560308_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--道具改变

--**********************************

function x560308_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end