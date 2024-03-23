--功能：新手村药店
--NPC：新手村药店医生

x211041_g_ScriptId = 211041
x211041_g_MissionName="药品商店"
x211041_g_ShopList={16}
--**********************************

--任务入口函数

--**********************************

function x211041_ProcEventEntry(sceneId, selfId, targetId)	--点击该任务后执行此脚本
	DispatchShopItem( sceneId, selfId, targetId, x211041_g_ShopList[1] )
end



--**********************************

--列举事件

--**********************************

function x211041_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
		AddQuestNumText(sceneId, x211041_g_ScriptId, x211041_g_MissionName)
end



--**********************************

--检测接受条件

--**********************************

function x211041_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--接受

--**********************************

function x211041_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--放弃

--**********************************

function x211041_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--检测是否可以提交

--**********************************

function x211041_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--提交

--**********************************

function x211041_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--杀死怪物或玩家

--**********************************

function x211041_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--进入区域事件

--**********************************

function x211041_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--道具改变

--**********************************

function x211041_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end