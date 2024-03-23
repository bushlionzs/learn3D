

function x310074_OnTimerDoingStart( sceneId, actId, Param1, Param2, Param3, Param4,Param5 )
	
	--local week = GetWeek()
	--if week == 0 then
		--local year, month, day = GetYearMonthDay()
		--if day>7 and day <=14 then
			if 0 == sceneId then
				YUNYOU_COMMIT_NUM = 0
			end
			local message = "【个人】寿诞采办将在21：30开始，请40级以上的玩家到大都海总管处进行活动！"
			LuaThisScenceM2Wrold( sceneId, message, CHAT_PLANE_SCROLL, 1 )
			LuaThisScenceM2Wrold( sceneId, message, CHAT_LEFTDOWN, 1 )
			SetSystemTimerTick( sceneId, 310074, "BroadCast1", actId, 60*1000*10  ) 
		--end
		
	--end
	
end


function x310074_BroadCast1(sceneId, actId, uTime)
	local message = "【个人】寿诞采办已经开始了，请40级以上的玩家到大都海总管处进行活动！"
	LuaThisScenceM2Wrold( sceneId, message, CHAT_PLANE_SCROLL, 1 )
	LuaThisScenceM2Wrold( sceneId, message, CHAT_LEFTDOWN, 1 )
	SetSystemTimerTick( sceneId, 310074, "BroadCast2", actId, 60*1000*30  ) 
end

function x310074_BroadCast2(sceneId, actId, uTime)
	local message = "【个人】寿诞采办已经结束了，请随时关注公告！"
	LuaThisScenceM2Wrold( sceneId, message, CHAT_PLANE_SCROLL, 1 )
	LuaThisScenceM2Wrold( sceneId, message, CHAT_LEFTDOWN, 1 )
	
end