--玩法：大都个人--生死财神--茶店

x560918_g_ScriptId = 560918
x560918_g_MissionName="四级技能书商店"
x560918_g_ShopList={918}
--**********************************

--任务入口函数

--**********************************

function x560918_ProcEventEntry(sceneId, selfId, targetId)	--点击该任务后执行此脚本
	DispatchShopItem( sceneId, selfId, targetId, x560918_g_ShopList[1] )
end



--**********************************

--列举事件

--**********************************

function x560918_ProcEnumEvent(sceneId, selfId, targetId, MissionId)

		AddQuestNumText(sceneId, x560918_g_ScriptId, x560918_g_MissionName,10)

end



--**********************************

--检测接受条件

--**********************************

function x560918_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--接受

--**********************************

function x560918_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--放弃

--**********************************

function x560918_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--检测是否可以提交

--**********************************

function x560918_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--提交

--**********************************

function x560918_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--杀死怪物或玩家

--**********************************

function x560918_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--进入区域事件

--**********************************

function x560918_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--道具改变

--**********************************

function x560918_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end