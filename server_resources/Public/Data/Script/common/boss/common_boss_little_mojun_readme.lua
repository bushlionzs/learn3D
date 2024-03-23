
x305004_g_ScriptId = 305004
x305004_g_MissionName = "【魔君部将说明】" 
x305004_g_ContinueInfo="\t十八魔君的部将们各个身手了得，暴虐成性。他们很有可能出现在如下地点！\n#Y\n完颜洪烈部将#G（凤翔府）\n \n#Y屈出律部将#G（阿尔金山）\n \n#Y札兰丁部将#G（撒马尔罕）  \n \n#Y弗拉基米尔部将#G（莫斯科公国）\n \n#W\n消灭各个魔君部将会获得其身上的各种财宝。"
function x305004_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
	
	AddQuestNumText(sceneId, x305004_g_ScriptId, x305004_g_MissionName, 13, 1)
		
end

function x305004_ProcEventEntry(sceneId, selfId, targetId,scriptid,extid)	--点击该任务后执行此脚本

	BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"#Y"..x305004_g_MissionName)
		AddQuestText(sceneId,x305004_g_ContinueInfo)
	EndQuestEvent()
	DispatchQuestEventList(sceneId, selfId, targetId)

end
