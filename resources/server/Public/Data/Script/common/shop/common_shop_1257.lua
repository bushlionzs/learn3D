--功能：宝石图谱金币商店

x561257_g_ScriptId = 561257
x561257_g_MissionName="宝石图谱金币商店"
x561257_g_ShopList={1257}
--**********************************

--任务入口函数

--**********************************

function x561257_ProcEventEntry(sceneId, selfId, targetId)	--点击该任务后执行此脚本
	DispatchShopItem( sceneId, selfId, targetId, x561257_g_ShopList[1] )
end



--**********************************

--列举事件

--**********************************

function x561257_ProcEnumEvent(sceneId, selfId, targetId, MissionId)	

	local nLevel = GetLevel(sceneId,selfId)
	if nLevel >= 50 then
		AddQuestNumText(sceneId, x561257_g_ScriptId, x561257_g_MissionName,10)
	else
		return
	end
	
end



--**********************************

--检测接受条件

--**********************************

function x561257_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--接受

--**********************************

function x561257_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--放弃

--**********************************

function x561257_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--检测是否可以提交

--**********************************

function x561257_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--提交

--**********************************

function x561257_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--杀死怪物或玩家

--**********************************

function x561257_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--进入区域事件

--**********************************

function x561257_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--道具改变

--**********************************

function x561257_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end