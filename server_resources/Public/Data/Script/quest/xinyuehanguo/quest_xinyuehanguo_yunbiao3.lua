--功能：三级运镖
--NPC：新月汗国 哈底斯


x211011_g_ScriptId = 211011
x211011_g_MissionName="三级运镖"

--**********************************

--任务入口函数

--**********************************

function x211011_ProcEventEntry(sceneId, selfId, targetId)	--点击该任务后执行此脚本
	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y三级运镖")
		AddQuestText(sceneId, "来到我们的地盘，就得听我们兄弟俩的。只要你对我们服服帖帖的，懂得道上的潜规则，你在这道上就能有出人头地的一天。不听话，嘿嘿……嘿嘿……我的刀呢！难道被运镖的顺手牵羊了？我刚找大哥借的啊，这下惨了……")
	EndQuestEvent(sceneId)
	DispatchQuestEventList(sceneId,selfId,targetId)
end



--**********************************

--列举事件

--**********************************

function x211011_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
		AddQuestNumText(sceneId, x211011_g_ScriptId, x211011_g_MissionName)
end



--**********************************

--检测接受条件

--**********************************

function x211011_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--接受

--**********************************

function x211011_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--放弃

--**********************************

function x211011_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--检测是否可以提交

--**********************************

function x211011_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--提交

--**********************************

function x211011_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--杀死怪物或玩家

--**********************************

function x211011_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--进入区域事件

--**********************************

function x211011_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--道具改变

--**********************************

function x211011_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end