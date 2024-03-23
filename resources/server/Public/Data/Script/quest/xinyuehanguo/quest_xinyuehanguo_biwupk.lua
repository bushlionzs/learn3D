--功能：PK阵营
--NPC：新月汗国 苏菲

x211038_g_ScriptId = 211038
x211038_g_MissionName="擂台比武"

--**********************************

--任务入口函数

--**********************************

function x211038_ProcEventEntry(sceneId, selfId, targetId)	--点击该任务后执行此脚本
	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#YPK阵营")
		AddQuestText(sceneId, "你现在已经是PK阵营了，找些高手来挑战挑战，看看自己的势力到底如何！")
	EndQuestEvent(sceneId)
	DispatchQuestEventList(sceneId,selfId,targetId)
	BeginQuestEvent(sceneId)
		local strText = "你变换为PK阵营"
		AddQuestText(sceneId,strText);
	EndQuestEvent(sceneId)
	DispatchQuestTips(sceneId,selfId)
	SetCurCamp(sceneId, selfId, 4)
end



--**********************************

--列举事件

--**********************************

function x211038_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
		AddQuestNumText(sceneId, x211038_g_ScriptId, "PK阵营")
end



--**********************************

--检测接受条件

--**********************************

function x211038_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--接受

--**********************************

function x211038_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--放弃

--**********************************

function x211038_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--检测是否可以提交

--**********************************

function x211038_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--提交

--**********************************

function x211038_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--杀死怪物或玩家

--**********************************

function x211038_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--进入区域事件

--**********************************

function x211038_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--道具改变

--**********************************

function x211038_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end