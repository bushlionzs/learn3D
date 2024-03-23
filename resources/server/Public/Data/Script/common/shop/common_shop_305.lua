--功能：大都声望宝石店

x560305_g_ScriptId = 560305
x560305_g_MissionName="声望宝石店"
x560305_g_ShopList={305}
--**********************************

--任务入口函数

--**********************************

function x560305_ProcEventEntry(sceneId, selfId, targetId)	--点击该任务后执行此脚本
	DispatchShopItem( sceneId, selfId, targetId, x560305_g_ShopList[1] )
end



--**********************************

--列举事件

--**********************************

function x560305_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
		AddQuestNumText(sceneId, x560305_g_ScriptId, x560305_g_MissionName,10)
end



--**********************************

--检测接受条件

--**********************************

function x560305_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--接受

--**********************************

function x560305_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--放弃

--**********************************

function x560305_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--检测是否可以提交

--**********************************

function x560305_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--提交

--**********************************

function x560305_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--杀死怪物或玩家

--**********************************

function x560305_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--进入区域事件

--**********************************

function x560305_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--道具改变

--**********************************

function x560305_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end