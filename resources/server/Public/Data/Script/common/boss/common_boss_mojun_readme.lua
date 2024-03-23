
x305003_g_ScriptId = 305003
x305003_g_MissionName = "【十八魔君说明】" 
x305003_g_ContinueInfo="\t你可知道十八魔君？他们很有可能出现在如下地点：\n#Y\n大河之王\n#G泰山（192，77）\n#Y黑水之王\n#G中兴府（128，45）\n#Y波西米亚之王\n#G中兴府（128，204）\n#Y贺兰山之王\n#G中兴府（128，128）\n#Y雪山之王\n#G太行山（142，48）\n#Y戈壁之王\n#G凤翔府（47，179）\n#Y平原之王\n#G蔡州城（65，141）\n#Y高加索之王\n#G秦岭（161，40）\n#Y沙漠之王\n#G阿尔金山（188，206）\n#Y西域之王\n#G碎叶城（49，103）\n#Y死海之王\n#G红沙漠（103，190）\n#Y埃及之王\n#G西奈半岛（176，138）\n#Y巴格达之王\n#G巴格达（87，155）\n#Y恒河之王\n#G波斯高原（92，191）\n#Y匈牙利之王\n#G匈牙利（230，126）\n#Y顿河之王\n#G莫斯科（77，181）\n#Y伏尔加之王\n#G基辅公国（217，118）\n#Y波兰之王\n#G波兰王国（130，225）\n#Y撒马尔罕之王\n#G撒马尔罕（83，225）\n#Y条顿之王\n#G神圣罗马（66，222）\n#Y哈布斯堡之王\n#G拜占庭（122，191）\n#Y大马士革之王\n#G大马士革（217，182）\n#Y圣域之王\n#G耶路撒冷（43，36）\n#Y叶密立之王\n#G楼兰暗道（211，203）\n#Y鲜血之王\n#G天山暗道（43，45）\n#Y幕府之王\n#G昆仑暗道（211，203）\n#Y漠北之王\n#G敦煌暗道（43，45）\n#W\n每周六，击败80级以下的十八魔君后，海都大王将会出现在中兴府（128，128）。"
function x305003_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
	AddQuestNumText(sceneId, x305003_g_ScriptId, x305003_g_MissionName, 13, 1)
end

function x305003_ProcEventEntry(sceneId, selfId, targetId,scriptid,extid)	--点击该任务后执行此脚本
	BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"#Y"..x305003_g_MissionName)
		AddQuestText(sceneId,x305003_g_ContinueInfo)
	EndQuestEvent()
	DispatchQuestEventList(sceneId, selfId, targetId)
end
