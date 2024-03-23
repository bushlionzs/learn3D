--功能：天传声望装备店-火枪

x560081_g_ScriptId = 560081
x560081_g_MissionName="天传声望装备店"
x560081_g_ShopList={81}
--**********************************

--任务入口函数

--**********************************

function x560081_ProcEventEntry(sceneId, selfId, targetId)	--点击该任务后执行此脚本
	DispatchShopItem( sceneId, selfId, targetId, x560081_g_ShopList[1] )
end



--**********************************

--列举事件

--**********************************

function x560081_ProcEnumEvent(sceneId, selfId, targetId, MissionId)

	local nLevel = GetLevel(sceneId, selfId)
	if nLevel >= 35 then
		AddQuestNumText(sceneId, x560081_g_ScriptId, x560081_g_MissionName,10)
	else
		return
	end

end



--**********************************

--检测接受条件

--**********************************

function x560081_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--接受

--**********************************

function x560081_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--放弃

--**********************************

function x560081_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--检测是否可以提交

--**********************************

function x560081_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--提交

--**********************************

function x560081_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--杀死怪物或玩家

--**********************************

function x560081_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--进入区域事件

--**********************************

function x560081_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--道具改变

--**********************************

function x560081_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end