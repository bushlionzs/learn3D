--功能：饰品商店  B

x560401_g_ScriptId = 560401
x560401_g_MissionName="药品店"
x560401_g_ShopList={101}
--**********************************

--任务入口函数

--**********************************

function x560401_ProcEventEntry(sceneId, selfId, targetId)	--点击该任务后执行此脚本
	DispatchShopItem( sceneId, selfId, targetId, x560401_g_ShopList[1] )
end



--**********************************

--列举事件

--**********************************

function x560401_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
	local camp = GetCurCamp(sceneId,selfId)
	

	if camp == 6 then
        
		AddQuestNumText(sceneId, x560401_g_ScriptId, x560401_g_MissionName,10)
	else 	
		return
	end

end



--**********************************

--检测接受条件

--**********************************

function x560401_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--接受

--**********************************

function x560401_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--放弃

--**********************************

function x560401_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--检测是否可以提交

--**********************************

function x560401_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--提交

--**********************************

function x560401_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--杀死怪物或玩家

--**********************************

function x560401_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--进入区域事件

--**********************************

function x560401_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--道具改变

--**********************************

function x560401_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end