--玩法：大都个人--生死财神--茶店

x560914_g_ScriptId = 560914
x560914_g_MissionName="珍宝商店"
x560914_g_ShopList={914}
--**********************************

--任务入口函数

--**********************************

function x560914_ProcEventEntry(sceneId, selfId, targetId)	--点击该任务后执行此脚本
	DispatchShopItem( sceneId, selfId, targetId, x560914_g_ShopList[1] )
end



--**********************************

--列举事件

--**********************************

function x560914_ProcEnumEvent(sceneId, selfId, targetId, MissionId)

		AddQuestNumText(sceneId, x560914_g_ScriptId, x560914_g_MissionName,10)

end



--**********************************

--检测接受条件

--**********************************

function x560914_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--接受

--**********************************

function x560914_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--放弃

--**********************************

function x560914_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--检测是否可以提交

--**********************************

function x560914_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--提交

--**********************************

function x560914_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--杀死怪物或玩家

--**********************************

function x560914_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--进入区域事件

--**********************************

function x560914_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--道具改变

--**********************************

function x560914_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end