
--MisDescBegin
x300502_g_ScriptId = 300502
x300502_g_LevelLess	= 	30 
x300502_g_MissionName = "【收集材料任务说明】" 
x300502_g_ContinueInfo="\t#W该任务十环为一轮，每天只能完成一轮。在任务中，也许材料收集人会#G多次向你收集同一物品#W，满足他的需求，你将会获得丰厚的奖励。\n\t#G如果你放弃了任务，当天无法再次领取收集材料任务了。\n\t#W你可以通过在野外打怪掉落获得材料，也可以去找@npc_138591、@npc_138592或@npc_138593学习生活技能获得所需的材料。"
--MisDescEnd

function x300502_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
	
	AddQuestNumText(sceneId, x300502_g_ScriptId, x300502_g_MissionName, 13, 1)
		
end

function x300502_ProcEventEntry(sceneId, selfId, targetId,scriptid,extid)	--点击该任务后执行此脚本

	BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"#Y"..x300502_g_MissionName)
		AddQuestText(sceneId,x300502_g_ContinueInfo)
	EndQuestEvent()
	DispatchQuestEventList(sceneId, selfId, targetId)

end
