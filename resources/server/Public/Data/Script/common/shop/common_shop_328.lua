--功能：铁铲店

x560328_g_ScriptId = 560328
x560328_g_MissionName="铁铲店"
x560328_g_ShopList={328}
--**********************************

--任务入口函数

--**********************************

function x560328_ProcEventEntry(sceneId, selfId, targetId)	--点击该任务后执行此脚本
	DispatchShopItem( sceneId, selfId, targetId, x560328_g_ShopList[1] )
end



--**********************************

--列举事件

--**********************************

function x560328_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
		AddQuestNumText(sceneId, x560328_g_ScriptId, x560328_g_MissionName,10)
end



--**********************************

--检测接受条件

--**********************************

function x560328_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--接受

--**********************************

function x560328_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--放弃

--**********************************

function x560328_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--检测是否可以提交

--**********************************

function x560328_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--提交

--**********************************

function x560328_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--杀死怪物或玩家

--**********************************

function x560328_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--进入区域事件

--**********************************

function x560328_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--道具改变

--**********************************

function x560328_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end