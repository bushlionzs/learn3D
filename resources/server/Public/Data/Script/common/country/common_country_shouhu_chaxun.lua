x300319_g_MissionName = "【国家】本国守护查询"
x300319_g_ScriptId = 300319

--**********************************

--列举事件

--**********************************

function x300319_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
	
	AddQuestNumText(sceneId, x300319_g_ScriptId, x300319_g_MissionName,3)
	
end

function x300319_ProcEventEntry(sceneId, selfId, NPCId, MissionId,which)	--点击该任务后执行此脚本
	x300319_DispatchPlayInfo( sceneId, selfId, NPCId )
end


---------------------------------------------------------------------------------------------------
--进入副本文字显示
---------------------------------------------------------------------------------------------------
function x300319_DispatchPlayInfo( sceneId, selfId, NPCId )

	local guild1 = GetCountrySpecialGuild(sceneId, selfId,0)
	local guild2 = GetCountrySpecialGuild(sceneId, selfId,1)
	
	local leaderName1 = "暂无"
	local leaderName2 = "暂无"
	local guildName1 = "暂无"
	local guildName2 = "暂无"
	
	if guild1>=0 then
		guildName1 = GetGuildName(guild1)
		leaderName1 = GetGuildLeaderName(guild1)
	end

	if guild2>=0 then
		guildName2 = GetGuildName(guild2)
		leaderName2 = GetGuildLeaderName(guild2)
	end

	BeginQuestEvent(sceneId)

		--任务信息
		AddQuestText(sceneId,"#Y"..x300319_g_MissionName)
		AddQuestText(sceneId,"\n")
		AddQuestText(sceneId,"#G青龙之主：#W"..leaderName1)
		AddQuestText(sceneId,"#G青龙守护帮会：#W"..guildName1)
		AddQuestText(sceneId,"\n")
		AddQuestText(sceneId,"#G朱雀之主：#W"..leaderName2)
		AddQuestText(sceneId,"#G朱雀守护帮会：#W"..guildName2)
		--AddQuestText(sceneId," ")

		


	EndQuestEvent()



	DispatchQuestDemandInfo(sceneId, selfId, NPCId, x300319_g_ScriptId, 0,0);
end
