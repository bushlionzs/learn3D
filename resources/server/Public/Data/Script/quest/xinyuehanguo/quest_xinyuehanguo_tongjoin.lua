--功能：帮会相关
--NPC：祖兰德

--MisDescBegin
x211035_g_ScriptId = 211035
x211035_g_MissionName = "【帮会】加入帮会"

--MisDescEnd
--**********************************

--任务入口函数

--**********************************

function x211035_ProcEventEntry(sceneId, selfId, targetId)	--点击该任务后执行此脚本

	
	
	local Readme_1 = "#Y【帮会】加入帮会#W#r #r"
	
	local Readme_2 = "加入帮会您要满足二个条件：#r #r"
	
	local Readme_3 = "  1，加入帮会所需#G等级#W至少#G20级#W。#r #r"
	
	local Readme_4 = "  2，加入帮会必须是#G无帮会状态#W，或者#G离开帮会#W在#G24小时#W以上。#r #r"
	
	local Readme_5 = "满足以上条件，点击#G确定#W就可以#G查看帮会#W信息，您一定会找到心仪的帮会，祝您成功。#r #r"
	
	local Readme = Readme_1..Readme_2..Readme_3..Readme_4..Readme_5
	
	BeginQuestEvent(sceneId);AddQuestText(sceneId, Readme);EndQuestEvent(sceneId);DispatchQuestEventList(sceneId,selfId,targetId);DispatchQuestInfo( sceneId, selfId, targetId, x211035_g_ScriptId, -1 );	
end



--**********************************

--列举事件

--**********************************

function x211035_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
 	local pos = GetGuildOfficial(sceneId, selfId)--判断是否加入帮会了
	if pos ~= -1 then
		return
	end
	AddQuestNumText(sceneId, x211035_g_ScriptId, x211035_g_MissionName, 3)
end



--**********************************

--检测接受条件

--**********************************

function x211035_ProcAcceptCheck(sceneId, selfId, targetId)
	return 1
end
--**********************************

--接受

--**********************************

function x211035_ProcAccept(sceneId, selfId)
	GuildList(sceneId, selfId, 0)
end



--**********************************

--放弃

--**********************************

function x211035_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--检测是否可以提交

--**********************************

function x211035_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--提交

--**********************************

function x211035_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)

end



--**********************************

--杀死怪物或玩家

--**********************************

function x211035_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--进入区域事件

--**********************************

function x211035_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--道具改变

--**********************************

function x211035_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end