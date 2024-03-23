--无敌幸运星定时器

--脚本号
x310338_g_ScriptId = 310338

function x310338_OnTimerDoingStart( sceneId, actId, Param1, Param2, Param3, Param4, Param5 )
	if sceneId ~= 39 then
			return
	end
	
	if 0 == Param1 then -- 00:00
		SetCountryParam( sceneId, 0, CD_YOULECHANG_CAIPIAO1, 1000)
		SetCountryParam( sceneId, 1, CD_YOULECHANG_CAIPIAO1, -1)
		SetCountryParam( sceneId, 2, CD_YOULECHANG_CAIPIAO1, -1)
		SetCountryParam( sceneId, 3, CD_YOULECHANG_CAIPIAO1, -1)
		
		SetCountryParam( sceneId, 0, CD_YOULECHANG_CAIPIAO2, -1)
		SetCountryParam( sceneId, 1, CD_YOULECHANG_CAIPIAO2, -1)
		SetCountryParam( sceneId, 2, CD_YOULECHANG_CAIPIAO2, -1)
		SetCountryParam( sceneId, 3, CD_YOULECHANG_CAIPIAO2, -1)
	elseif 1 == Param1 then -- 10：30
		local count = GetCountryParam( sceneId, 0, CD_YOULECHANG_CAIPIAO1)
		if count <= 1000 then
			return
		end
		local rnd = random(1000, count-1)
		SetCountryParam( sceneId, 1, CD_YOULECHANG_CAIPIAO1, rnd)
		
		local msg = format("本期乐透彩票开出的号码是:#G%d#R，请中奖的玩家前往#G乐透彩票大使（126，93）#R处领取大奖！", rnd)
		LuaThisScenceM2Wrold(sceneId, msg, CHAT_PLANE_SCROLL, 1)
		LuaThisScenceM2Wrold(sceneId, msg, CHAT_LEFTDOWN, 1)
	elseif 2 == Param1 then -- 12：30
		local count = GetCountryParam( sceneId, 0, CD_YOULECHANG_CAIPIAO1)
		if count <= 1000 then
			return
		end
		local rnd = random(1000, count-1)
		SetCountryParam( sceneId, 2, CD_YOULECHANG_CAIPIAO1, rnd)
		
		local msg = format("本期乐透彩票开出的号码是:#G%d#R，请中奖的玩家前往#G乐透彩票大使（126，93）#R处领取大奖！", rnd)
		LuaThisScenceM2Wrold(sceneId, msg, CHAT_PLANE_SCROLL, 1)
		LuaThisScenceM2Wrold(sceneId, msg, CHAT_LEFTDOWN, 1)
	elseif 3 == Param1 then -- 14：30
		local count = GetCountryParam( sceneId, 0, CD_YOULECHANG_CAIPIAO1)
		if count <= 1000 then
			return
		end
		local rnd = random(1000, count-1)
		SetCountryParam( sceneId, 3, CD_YOULECHANG_CAIPIAO1, rnd)
		
		local msg = format("本期乐透彩票开出的号码是:#G%d#R，请中奖的玩家前往#G乐透彩票大使（126，93）#R处领取大奖！", rnd)
		LuaThisScenceM2Wrold(sceneId, msg, CHAT_PLANE_SCROLL, 1)
		LuaThisScenceM2Wrold(sceneId, msg, CHAT_LEFTDOWN, 1)
	elseif 4 == Param1 then -- 16：30
		local count = GetCountryParam( sceneId, 0, CD_YOULECHANG_CAIPIAO1)
		if count <= 1000 then
			return
		end
		local rnd = random(1000, count-1)
		SetCountryParam( sceneId, 0, CD_YOULECHANG_CAIPIAO2, rnd)
		
		local msg = format("本期乐透彩票开出的号码是:#G%d#R，请中奖的玩家前往#G乐透彩票大使（126，93）#R处领取大奖！", rnd)
		LuaThisScenceM2Wrold(sceneId, msg, CHAT_PLANE_SCROLL, 1)
		LuaThisScenceM2Wrold(sceneId, msg, CHAT_LEFTDOWN, 1)
	elseif 5 == Param1 then -- 18：30
		local count = GetCountryParam( sceneId, 0, CD_YOULECHANG_CAIPIAO1)
		if count <= 1000 then
			return
		end
		local rnd = random(1000, count-1)
		SetCountryParam( sceneId, 1, CD_YOULECHANG_CAIPIAO2, rnd)
		
		local msg = format("本期乐透彩票开出的号码是:#G%d#R，请中奖的玩家前往#G乐透彩票大使（126，93）#R处领取大奖！", rnd)
		LuaThisScenceM2Wrold(sceneId, msg, CHAT_PLANE_SCROLL, 1)
		LuaThisScenceM2Wrold(sceneId, msg, CHAT_LEFTDOWN, 1)
	elseif 6 == Param1 then -- 20：30
		local count = GetCountryParam( sceneId, 0, CD_YOULECHANG_CAIPIAO1)
		if count <= 1000 then
			return
		end
		local rnd = random(1000, count-1)
		SetCountryParam( sceneId, 2, CD_YOULECHANG_CAIPIAO2, rnd)
		
		local msg = format("本期乐透彩票开出的号码是:#G%d#R，请中奖的玩家前往#G乐透彩票大使（126，93）#R处领取大奖！", rnd)
		LuaThisScenceM2Wrold(sceneId, msg, CHAT_PLANE_SCROLL, 1)
		LuaThisScenceM2Wrold(sceneId, msg, CHAT_LEFTDOWN, 1)
	elseif 7 == Param1 then -- 22：30
		local count = GetCountryParam( sceneId, 0, CD_YOULECHANG_CAIPIAO1)
		if count <= 1000 then
			return
		end
		local rnd = random(1000, count-1)
		SetCountryParam( sceneId, 3, CD_YOULECHANG_CAIPIAO2, rnd)
		
		local msg = format("本期乐透彩票开出的号码是:#G%d#R，请中奖的玩家前往#G乐透彩票大使（126，93）#R处领取大奖！", rnd)
		LuaThisScenceM2Wrold(sceneId, msg, CHAT_PLANE_SCROLL, 1)
		LuaThisScenceM2Wrold(sceneId, msg, CHAT_LEFTDOWN, 1)
	end
end