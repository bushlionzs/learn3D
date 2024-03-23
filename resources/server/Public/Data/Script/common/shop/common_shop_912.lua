--玩法：大都个人--生死财神--水果店

x560912_g_ScriptId = 560912
x560912_g_MissionName="施记水果"
x560912_g_ShopList={912}
--**********************************

--任务入口函数

--**********************************

function x560912_ProcEventEntry(sceneId, selfId, targetId)	--点击该任务后执行此脚本
	DispatchShopItem( sceneId, selfId, targetId, x560912_g_ShopList[1] )
end



--**********************************

--列举事件

--**********************************

function x560912_ProcEnumEvent(sceneId, selfId, targetId, MissionId)

		AddQuestNumText(sceneId, x560912_g_ScriptId, x560912_g_MissionName,10)

end



--**********************************

--检测接受条件

--**********************************

function x560912_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--接受

--**********************************

function x560912_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--放弃

--**********************************

function x560912_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--检测是否可以提交

--**********************************

function x560912_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--提交

--**********************************

function x560912_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--杀死怪物或玩家

--**********************************

function x560912_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--进入区域事件

--**********************************

function x560912_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--道具改变

--**********************************

function x560912_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end