--功能：国家国防商店
--NPC：中军将军

--MisDescBegin
x211037_g_ScriptId = 211037

x211037_g_MissionName = "国家国防商店"
x211037_g_ShopList = {1}
--MisDescEnd
--**********************************

--任务入口函数

--**********************************

function x211037_ProcEventEntry(sceneId, selfId, targetId)	--点击该任务后执行此脚本
	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y国家国防商店")
		AddQuestText(sceneId, "国家兴亡，匹夫有责。凡是对国防事业有功之人，国家都会体恤他们的。现在正有一匹物资，正在运送来的路上，一到王城，我就通知大家前来领取。\n我这里只奖励对#G国防事业#W的有功之人。对国家发展建设有功的人应该去找对面的大司马。")
	EndQuestEvent(sceneId)
	DispatchQuestEventList(sceneId,selfId,targetId)
	--DispatchShopItem( sceneId, selfId, targetId, x211037_g_ShopList[1] )
end



--**********************************

--列举事件

--**********************************

function x211037_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
	AddQuestNumText(sceneId, x211037_g_ScriptId, x211037_g_MissionName)
end



--**********************************

--检测接受条件

--**********************************

function x211037_ProcAcceptCheck(sceneId, selfId, targetId)

end



--**********************************

--接受

--**********************************

function x211037_ProcAccept(sceneId, selfId)
    
end



--**********************************

--放弃

--**********************************

function x211037_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--检测是否可以提交

--**********************************

function x211037_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--提交

--**********************************

function x211037_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--杀死怪物或玩家

--**********************************

function x211037_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--进入区域事件

--**********************************

function x211037_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--道具改变

--**********************************

function x211037_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end