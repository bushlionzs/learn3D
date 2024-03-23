--功能：夜明珠金币商店

x561252_g_ScriptId = 561252
x561252_g_MissionName="夜明珠金币商店"
x561252_g_ShopList={1252}
--**********************************

--任务入口函数

--**********************************

function x561252_ProcEventEntry(sceneId, selfId, targetId)	--点击该任务后执行此脚本
	DispatchShopItem( sceneId, selfId, targetId, x561252_g_ShopList[1] )
end



--**********************************

--列举事件

--**********************************

function x561252_ProcEnumEvent(sceneId, selfId, targetId, MissionId)	

	local nLevel = GetLevel(sceneId,selfId)
	if nLevel >= 80 then
		AddQuestNumText(sceneId, x561252_g_ScriptId, x561252_g_MissionName,10)
	else
		return
	end
	
end



--**********************************

--检测接受条件

--**********************************

function x561252_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--接受

--**********************************

function x561252_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--放弃

--**********************************

function x561252_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--检测是否可以提交

--**********************************

function x561252_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--提交

--**********************************

function x561252_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--杀死怪物或玩家

--**********************************

function x561252_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--进入区域事件

--**********************************

function x561252_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--道具改变

--**********************************

function x561252_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end