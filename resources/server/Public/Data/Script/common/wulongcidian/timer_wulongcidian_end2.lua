--脚本号
x310187_g_ScriptId = 310187

function x310187_OnTimerDoingStart( SceneId, actId, Param1, Param2, Param3, Param4, Param5 )

	if GetWeek() ~= 0 then
		return
	end
	
	if SceneId ~= 0 then
		return
	end
	
	if WULONGCIDIAN_STEPIN_COUNT  <= 0 then
		return
	end
	
	local msg = ""
	local count =0
	local msg1=""
	local msg2=""
	local msg3=""

	for i=1, WULONGCIDIAN_STEPIN_COUNT do
		count = count +1
		if count<=10 then
			msg1 = msg1.."#Y "..WULONGCIDIAN_STEPIN_NAME[i]
		elseif count<=20 then
			msg2 = msg2.."#Y "..WULONGCIDIAN_STEPIN_NAME[i]
		else
			msg3 = msg3.."#Y "..WULONGCIDIAN_STEPIN_NAME[i]
		end
		SendSystemMail(SceneId, WULONGCIDIAN_STEPIN_NAME[i], "恭喜您获得乌龙辞典第三轮参赛资格，请在下午16：30-17：00之内前往大都找到大内总管海总管参加最终决赛！" )
		
	end
	if count<=10 then
		msg = "#G恭喜"
		msg = msg..msg1.."#G获得乌龙辞典第三轮参赛资格，请在下午16：30-17：00之内前往大都找到大内总管海总管参加最终决赛！"
	LuaAllScenceM2Wrold(SceneId, msg, CHAT_LEFTDOWN, 0)
		return
	end
	
	if count<=20 then
		msg = "#G恭喜"
		msg = msg..msg1.."#G获得乌龙辞典第三轮参赛资格，请在下午16：30-17：00之内前往大都找到大内总管海总管参加最终决赛！"
		LuaAllScenceM2Wrold(SceneId, msg, CHAT_LEFTDOWN, 0)
	 msg = "#G恭喜"
	 msg = msg..msg2.."#G获得乌龙辞典第三轮参赛资格，请在下午16：30-17：00之内前往大都找到大内总管海总管参加最终决赛！"
	LuaAllScenceM2Wrold(SceneId, msg, CHAT_LEFTDOWN, 0)
		return
	end
	
	 msg = "#G恭喜"
	msg = msg..msg1.."#G获得乌龙辞典第三轮参赛资格，请在下午16：30-17：00之内前往大都找到大内总管海总管参加最终决赛！"
	LuaAllScenceM2Wrold(SceneId, msg, CHAT_LEFTDOWN, 0)
	msg = "#G恭喜"
	msg = msg..msg2.."#G获得乌龙辞典第三轮参赛资格，请在下午16：30-17：00之内前往大都找到大内总管海总管参加最终决赛！"
	LuaAllScenceM2Wrold(SceneId, msg, CHAT_LEFTDOWN, 0)
	msg = "#G恭喜"
	msg = msg..msg3.."#G获得乌龙辞典第三轮参赛资格，请在下午16：30-17：00之内前往大都找到大内总管海总管参加最终决赛！"
	LuaAllScenceM2Wrold(SceneId, msg, CHAT_LEFTDOWN, 0)
	
end
