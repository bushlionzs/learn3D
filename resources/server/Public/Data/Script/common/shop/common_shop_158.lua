--功能：4级帮贡商店

x560158_g_ScriptId = 560158
x560158_g_MissionName="四级帮贡商店"
x560158_g_ShopList={158}
--**********************************

--任务入口函数

--**********************************

function x560158_ProcEventEntry(sceneId, selfId, targetId)	--点击该任务后执行此脚本
	DispatchShopItem( sceneId, selfId, targetId, x560158_g_ShopList[1] )
end



--**********************************

--列举事件

--**********************************

function x560158_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
		AddQuestNumText(sceneId, x560158_g_ScriptId, x560158_g_MissionName,10)
end



--**********************************

--检测接受条件

--**********************************

function x560158_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--接受

--**********************************

function x560158_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--放弃

--**********************************

function x560158_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--检测是否可以提交

--**********************************

function x560158_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--提交

--**********************************

function x560158_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--杀死怪物或玩家

--**********************************

function x560158_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--进入区域事件

--**********************************

function x560158_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--道具改变

--**********************************

function x560158_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end