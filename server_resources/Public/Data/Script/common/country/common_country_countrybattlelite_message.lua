x310157_g_ScriptId = 310157
 -- 屠城战玩法开关ID
x310157_g_GameOpenId = 1026

function x310157_OnTimerDoingStart( sceneId, actId, Param1, Param2, Param3, Param4, Param5 )

    if GetGameOpenById(x310157_g_GameOpenId) <= 0 then
		return
	end

	--检查周配置
	if CountryBattleLite_CheckWeekConfig() == 0 then
		return
	end
	
	
	--相关广播
	if actId == 42 then
		
		LuaAllScenceM2Wrold(sceneId,"屠城战将于20：00开启，身处中兴府，王城，古道，边境的国民可以参加！",1,1)
		
	elseif actId == 43 then
		
		LuaAllScenceM2Wrold(sceneId,"屠城战将在5分钟后开始，国民请尽快赶往中兴府，王城，古道，边境参加屠城战！",1,1)
		
	elseif actId == 44 then
		
		LuaAllScenceM2Wrold(sceneId,"屠城战火热进行中，您可以在国家管理员处参加！",1,1)
		
	elseif actId == 45then
		
		LuaAllScenceM2Wrold(sceneId,"距离屠城战参加截止时间还有5分钟！",1,1)
	
	elseif actId == 46 then
	
	    LuaAllScenceM2Wrold(sceneId,"屠城战已经结束！",1,1)
	end

end