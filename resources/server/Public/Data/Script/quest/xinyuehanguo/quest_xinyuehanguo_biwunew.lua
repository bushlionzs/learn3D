--功能：新手阵营
--NPC：新月汗国 苏菲

x211039_g_ScriptId = 211039
x211039_g_MissionName="擂台比武"

--**********************************

--任务入口函数

--**********************************

function x211039_ProcEventEntry(sceneId, selfId, targetId)	--点击该任务后执行此脚本
	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y新手阵营")
		AddQuestText(sceneId, "你恢复了新手阵营，这样别人就没法找你的茬了！")
	EndQuestEvent(sceneId)
	DispatchQuestEventList(sceneId,selfId,targetId)
	BeginQuestEvent(sceneId)
		local strText = "你变换为新手阵营"
		AddQuestText(sceneId,strText);
	EndQuestEvent(sceneId)
	DispatchQuestTips(sceneId,selfId)
	SetCurCamp(sceneId, selfId, 0)
end



--**********************************

--列举事件

--**********************************

function x211039_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
	AddQuestNumText(sceneId, x211039_g_ScriptId, "新手阵营")
end



--**********************************

--检测接受条件

--**********************************

function x211039_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--接受

--**********************************

function x211039_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--放弃

--**********************************

function x211039_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--检测是否可以提交

--**********************************

function x211039_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--提交

--**********************************

function x211039_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--杀死怪物或玩家

--**********************************

function x211039_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--进入区域事件

--**********************************

function x211039_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--道具改变

--**********************************

function x211039_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end