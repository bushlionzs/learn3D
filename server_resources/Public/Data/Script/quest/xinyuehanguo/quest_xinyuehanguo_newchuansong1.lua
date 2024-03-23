--功能：新手村传送
--NPC：长者

x211064_g_ScriptId = 211064
x211064_g_MissionName="特殊商店二"
--**********************************

--任务入口函数

--**********************************

function x211064_ProcEventEntry(sceneId, selfId, targetId)	--点击该任务后执行此脚本
	DispatchShopItem( sceneId, selfId, targetId, 15 )
	--if GetLevel( sceneId, selfId ) >= 10 then
	--	SetPos(sceneId, selfId,108,258)
	--	BeginQuestEvent(sceneId)
	--		strText = "你来到了汗国中心广场"
	--		AddQuestText(sceneId,strText);
	--	EndQuestEvent(sceneId)
	--	DispatchQuestTips(sceneId,selfId)
	--else
	--	BeginQuestEvent(sceneId)
	--		AddQuestText(sceneId, "#Y汗国中心广场")
	--		AddQuestText(sceneId, "只有村子里得到大家认可的英雄，我才会派人将你快速送到汗国中心广场。当你10级的时候，就会得到大家的认可，成为村里的英雄！")
	--	EndQuestEvent(sceneId)
	--	DispatchQuestEventList(sceneId,selfId,targetId)
	--end
end



--**********************************

--列举事件

--**********************************

function x211064_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
	AddQuestNumText(sceneId, x211064_g_ScriptId, x211064_g_MissionName)
end



--**********************************

--检测接受条件

--**********************************

function x211064_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--接受

--**********************************

function x211064_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--放弃

--**********************************

function x211064_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--检测是否可以提交

--**********************************

function x211064_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--提交

--**********************************

function x211064_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--杀死怪物或玩家

--**********************************

function x211064_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--进入区域事件

--**********************************

function x211064_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--道具改变

--**********************************

function x211064_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end