--功能：饰品商店  A

x560400_g_ScriptId = 560400
x560400_g_MissionName="药品店"
x560400_g_ShopList={101}
--**********************************

--任务入口函数

--**********************************

function x560400_ProcEventEntry(sceneId, selfId, targetId)	--点击该任务后执行此脚本
	DispatchShopItem( sceneId, selfId, targetId, x560400_g_ShopList[1] )
end



--**********************************

--列举事件

--**********************************

function x560400_ProcEnumEvent(sceneId, selfId, targetId, MissionId)

	local camp = GetCurCamp(sceneId,selfId)
	
	if camp == 5 then
		AddQuestNumText(sceneId, x560400_g_ScriptId, x560400_g_MissionName,10)
	else 	
		return
	end


end



--**********************************

--检测接受条件

--**********************************

function x560400_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--接受

--**********************************

function x560400_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--放弃

--**********************************

function x560400_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--检测是否可以提交

--**********************************

function x560400_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--提交

--**********************************

function x560400_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--杀死怪物或玩家

--**********************************

function x560400_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--进入区域事件

--**********************************

function x560400_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--道具改变

--**********************************

function x560400_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end