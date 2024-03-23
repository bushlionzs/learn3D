--玩法：大都个人--生死财神--天桥米店

x560910_g_ScriptId = 560910
x560910_g_MissionName="天桥米铺"
x560910_g_ShopList={910}
--**********************************

--任务入口函数

--**********************************

function x560910_ProcEventEntry(sceneId, selfId, targetId)	--点击该任务后执行此脚本
	DispatchShopItem( sceneId, selfId, targetId, x560910_g_ShopList[1] )
end



--**********************************

--列举事件

--**********************************

function x560910_ProcEnumEvent(sceneId, selfId, targetId, MissionId)

		AddQuestNumText(sceneId, x560910_g_ScriptId, x560910_g_MissionName,10)

end



--**********************************

--检测接受条件

--**********************************

function x560910_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--接受

--**********************************

function x560910_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--放弃

--**********************************

function x560910_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--检测是否可以提交

--**********************************

function x560910_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--提交

--**********************************

function x560910_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--杀死怪物或玩家

--**********************************

function x560910_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--进入区域事件

--**********************************

function x560910_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--道具改变

--**********************************

function x560910_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end