
--MisDescBegin
x300798_g_ScriptId = 300798
x300798_g_LevelLess	= 	75 
x300798_g_MissionName = "【军需武备说明】" 
x300798_g_ContinueInfo="\t接取任务：#G75级#W以上玩家可以接取军需武备任务，每轮任务为#G30环#W。\n\t1.从完成整轮任务起计时，#G下周#W可以再次接取。\n\t2.如上周任务没有全部完成，本周仍可继续完成。例如：#G上周完成任务为(24/30)环，本周继续此任务(24/30)环#W，但完成30环任务后无法继续接取，#G下周#W可以再次接取任务。\n\t3.玩家放弃任务后，下周才能重新接受新一轮任务。\n\t4.#W完成的任务环数越多，获得#G经验奖励#W就会越丰厚。\n\t5.完成第30环时有几率获得了一个@item_10310003"
--MisDescEnd

function x300798_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
	
	AddQuestNumText(sceneId, x300798_g_ScriptId, x300798_g_MissionName, 13, 1)
		
end

function x300798_ProcEventEntry(sceneId, selfId, targetId,scriptid,extid)	--点击该任务后执行此脚本

	BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"#Y"..x300798_g_MissionName)
		AddQuestText(sceneId,x300798_g_ContinueInfo)
	EndQuestEvent()
	DispatchQuestEventList(sceneId, selfId, targetId)

end
