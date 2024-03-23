x310084_g_ScriptId = 310084

x310084_g_MissionName = "【游览公车说明】"
x310084_g_MissionComment = "\t每日#G12：15~12：45,14：15~14：45,16：15~16：45和18：15~18：45#W，神兽玄武将从此处降临，绕马场一周后返回，#G超过20级#W的玩家将可以免费乘坐神兽玄武游览整个马场，威风神武！并且在车子行进过程中，每隔一定时间将会获得#G高额经验和银卡奖励#W，车上坐的人#G越多#W，获得的#G经验#W就会#G越高#W，欢迎乘坐！\n\t玄武的后背只可#R乘坐8人#W，请大家在规定时间内，在发车车站附近有序上车。\n\t注意，神兽玄武驶出后将不再接受乘客中途上车，请大家有序排队等候。"

function x310084_ProcEventEntry(sceneId, selfId, targetId,scriptid,extid)	--点击该任务后执行此脚本

		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"#Y"..x310084_g_MissionName)
			AddQuestText(sceneId,x310084_g_MissionComment)
		EndQuestEvent()
		DispatchQuestEventList(sceneId, selfId, targetId)

end



--**********************************

--列举事件

--**********************************

function x310084_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)

		AddQuestNumText(sceneId, x310084_g_ScriptId, x310084_g_MissionName,13,1)
	
end