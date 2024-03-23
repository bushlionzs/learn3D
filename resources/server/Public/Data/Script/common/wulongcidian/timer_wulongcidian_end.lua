--脚本号
x310186_g_ScriptId = 310186

function x310186_OnTimerDoingStart( SceneId, actId, Param1, Param2, Param3, Param4, Param5 )
	if GetWeek() ~= 0 then
		return
	end

	if SceneId ~= 0 then
		return
	end

	if WULONGCIDIAN_AWARD_COUNT  <= 0 then
		return
	end
	
	for i=1, WULONGCIDIAN_AWARD_COUNT do
		if i==1 then
			local msg = format("#G恭喜#Y%s#G获得#Y%s#G的称号,请前往大都在大内总管海总管处领取奖励。", WULONGCIDIAN_AWARD_NAME[i], "乌龙宗师")
			LuaAllScenceM2Wrold(SceneId, msg, CHAT_LEFTDOWN, 0)
		elseif i==2 then
			local msg = format("#G恭喜#Y%s#G获得#Y%s#G的称号,请前往大都在大内总管海总管处领取奖励。", WULONGCIDIAN_AWARD_NAME[i], "乌龙高手")
			LuaAllScenceM2Wrold(SceneId, msg, CHAT_LEFTDOWN, 0)
		elseif i==3 then
			local msg = format("#G恭喜#Y%s#G获得#Y%s#G的称号,请前往大都在大内总管海总管处领取奖励。", WULONGCIDIAN_AWARD_NAME[i], "乌龙强人")
			LuaAllScenceM2Wrold(SceneId, msg, CHAT_LEFTDOWN, 0)
		end
			
	end

	for i=1, 3 do
		WULONGCIDIAN_AWARD_Draw[i] = 0
	end

end
