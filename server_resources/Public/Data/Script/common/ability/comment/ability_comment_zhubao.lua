
x540202_g_ScriptId = 540202
x540202_g_MissionName = "【采矿技能说明】" 
x540202_g_ContinueInfo="\t学习#R采矿#W技能后，在#G草原地图#W可以挖掘到各种生活技能材料，地点如下：\n#W\n#Y1~2级技能#W  可以挖掘#G初级矿石#W\n#Y挖掘地点   #G罕难河草原、乞颜部\n#W\n#Y3~4级技能#W  可以挖掘#G中级矿石#W\n#Y挖掘地点   #G乞颜部、塔塔尔部\n#W\n#Y5~6级技能#W  可以挖掘#G高级矿石#W\n#Y挖掘地点   #G克烈部、乃蛮部\n#W\n#Y7~8级技能#W  可以挖掘#G圣徒级矿石#W\n#Y挖掘地点   #G乃蛮部、居庸关\n#W请注意：剧场内是没有生活技能采集点存在的，你需要前往正常的世界地图中采集，如：王国草原-罕难河，而不是 剧场-罕难河。"

function x540202_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
	
	AddQuestNumText(sceneId, x540202_g_ScriptId, x540202_g_MissionName, 13, 1)
		
end

function x540202_ProcEventEntry(sceneId, selfId, targetId,scriptid,extid)	--点击该任务后执行此脚本

	BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"#Y"..x540202_g_MissionName)
		AddQuestText(sceneId,x540202_g_ContinueInfo)
	EndQuestEvent()
	DispatchQuestEventList(sceneId, selfId, targetId)

end
