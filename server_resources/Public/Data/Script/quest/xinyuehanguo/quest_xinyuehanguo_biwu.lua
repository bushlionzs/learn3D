--功能：擂台比武
--NPC：新月汗国 苏菲

x211008_g_ScriptId = 211008
x211008_g_MissionName="擂台比武"

--**********************************

--任务入口函数

--**********************************

function x211008_ProcEventEntry(sceneId, selfId, targetId)	--点击该任务后执行此脚本
	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y擂台比武")
		AddQuestText(sceneId, "比武场还在修缮中，等到比武场开放的时候，你可要多来看看，这里可是高手云集。想要一战成名，想要钻研更高武学，都可以来找我，我会帮助你的。当然了我会收取一点点小费了，你要是现在就报名，还可以给你打个折！")
	EndQuestEvent(sceneId)
	DispatchQuestEventList(sceneId,selfId,targetId)
end



--**********************************

--列举事件

--**********************************

function x211008_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
		AddQuestNumText(sceneId, x211008_g_ScriptId, x211008_g_MissionName)
end



--**********************************

--检测接受条件

--**********************************

function x211008_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--接受

--**********************************

function x211008_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--放弃

--**********************************

function x211008_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--检测是否可以提交

--**********************************

function x211008_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--提交

--**********************************

function x211008_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--杀死怪物或玩家

--**********************************

function x211008_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--进入区域事件

--**********************************

function x211008_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--道具改变

--**********************************

function x211008_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end