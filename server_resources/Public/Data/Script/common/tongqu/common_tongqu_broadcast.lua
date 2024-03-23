function x300325_OnTimerDoingStart( sceneId, actId, Param1, Param2, Param3, Param4,Param5 )
	
	--local week = GetWeek()
	--if week == 0 then
		--local year, month, day = GetYearMonthDay()
		--if day<=7 then
			if sceneId == 0 then
				TONGQU_COMMIT_NUM = 0
			end
			local message = "【个人】童趣将在21：00开始，请40级以上玩家到大都童博处接取任务"
			LuaThisScenceM2Wrold( sceneId, message, CHAT_PLANE_SCROLL, 1 )
			LuaThisScenceM2Wrold( sceneId, message, CHAT_LEFTDOWN, 1 )
			SetSystemTimerTick( sceneId, 300325, "BroadCast1", actId, 60*1000*10  ) 
		--end
		
	--end
	
end


function x300325_BroadCast1(sceneId, actId, uTime)
	local message = "【个人】童趣开始了，请40级以上玩家到大都童博处接取任务"
	LuaThisScenceM2Wrold( sceneId, message, CHAT_PLANE_SCROLL, 1 )
	LuaThisScenceM2Wrold( sceneId, message, CHAT_LEFTDOWN, 1 )
	SetSystemTimerTick( sceneId, 300325, "BroadCast2", actId, 60*1000*30  ) 
end

function x300325_BroadCast2(sceneId, actId, uTime)
	local message = "【个人】童趣结束了，请随时关注系统公告"
	LuaThisScenceM2Wrold( sceneId, message, CHAT_PLANE_SCROLL, 1 )
	LuaThisScenceM2Wrold( sceneId, message, CHAT_LEFTDOWN, 1 )
end