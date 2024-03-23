--功能：骑乘道具金币商店

x561258_g_ScriptId = 561258
x561258_g_MissionName="骑乘道具金币商店"
x561258_g_ShopList={1258}
--**********************************

--任务入口函数

--**********************************

function x561258_ProcEventEntry(sceneId, selfId, targetId)	--点击该任务后执行此脚本
	DispatchShopItem( sceneId, selfId, targetId, x561258_g_ShopList[1] )
end



--**********************************

--列举事件

--**********************************

function x561258_ProcEnumEvent(sceneId, selfId, targetId, MissionId)	

	local nLevel = GetLevel(sceneId,selfId)
	if nLevel >= 40 then
		AddQuestNumText(sceneId, x561258_g_ScriptId, x561258_g_MissionName,10)
	else
		return
	end
	
end



--**********************************

--检测接受条件

--**********************************

function x561258_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--接受

--**********************************

function x561258_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--放弃

--**********************************

function x561258_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--检测是否可以提交

--**********************************

function x561258_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--提交

--**********************************

function x561258_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--杀死怪物或玩家

--**********************************

function x561258_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--进入区域事件

--**********************************

function x561258_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--道具改变

--**********************************

function x561258_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end