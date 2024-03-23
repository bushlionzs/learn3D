
x300358_g_ScriptId 					= 300358
x300358_g_MissionName				= "【查询收徒剩余时间】"

function x300358_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
	AddQuestNumText(sceneId,x300358_g_ScriptId,x300358_g_MissionName,3,0)
end

function x300358_ProcEventEntry(sceneId, selfId, targetId)
	if GetLevel(sceneId, selfId) >= 50 then
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId, x300358_ShituQuery(sceneId, selfId))
		EndQuestEvent()
		DispatchQuestInfo(sceneId, selfId, targetId, x300358_g_ScriptId, -1)
	else
		Msg2Player(sceneId, selfId, "50级以上的玩家才可以收徒弟。", 8, 3)
	end
end

function x300358_ProcAcceptCheck(sceneId, selfId, targetId)
	return 1
end

function x300358_ProcAccept(sceneId, selfId, targetId)
	return 1
end

function x300358_ShituQuery(sceneId, selfId)
	if IsPrenticeFull(sceneId, selfId) == 1 then
		return "\t您徒弟数量已满，升级师傅称号能收取更多的徒弟，每位师傅最多能收取5位徒弟。"
	end
	
	--是否大于3天 得到最后一次添加徒弟的时间,得到的是时间差（秒数）
	local iTime = GetPrenticeBetrayTime(sceneId, selfId)
	if iTime > 0 and iTime < MASTER_PRENTICE_TIME_LIMIT*3600 then
		return format("\t距离您下一次收徒弟还需要%d小时%d分。", x300358_Time(iTime))
	end
	
	return "\t您现在就可以收取下一位徒弟了，您可以通过查找徒弟功能找寻徒弟。"
end

function x300358_Time(iTime)
	iTime = iTime/60
	local h = iTime/60
	local m = mod(iTime, 60)
	if m >= 1 then
		h = h+1
	end
	if m < 1 then
		m = 60
	end
	return MASTER_PRENTICE_TIME_LIMIT-floor(h), 60-floor(m)
end