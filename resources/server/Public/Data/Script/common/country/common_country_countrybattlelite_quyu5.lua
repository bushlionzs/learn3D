
--屠城战区域事件

--MisDescBegin
x310144_g_ScriptId              = 310144
x310144_g_Time					= { min = 2000,max = 2059 }	--时间限制
x310144_g_minsterGuid			= 129744					--屠城战国家军力GUID
x310144_g_PreTime				=  0
x310144_g_AreaTipsInterval		=  2						--区域事件间隔
x310144_g_AreaTips				= "#R警报！敌国正在攻击我国古道#aB{goto_%d,%d,%d}(%d,%d)#aE的国家军力，请火速救援！"
--MisDescEnd
----------------------------------------------------------------------------------------------
function x310144_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
	local hour,minute,sec =GetHourMinSec(); --检查时间是否正确
	local now = hour *100 + minute
	if now < x310144_g_Time.min or now > x310144_g_Time.max then
		return
	end
	
	local nCurMin = GetMinOfYear()  --检查上次提醒时间
	local nInterval = nCurMin - x310144_g_PreTime
	if nInterval < x310144_g_AreaTipsInterval then
		return	
	end
	
	local nCountry = -1
	local x =0
	local z= 0
	if sceneId == 86 then
		nCountry = 0
		x = 146
		z = 69
	elseif sceneId == 186 then
		nCountry = 1
		x = 154
		z = 89
	elseif sceneId == 286 then
		nCountry = 2
		x = 152
		z = 166
	elseif sceneId == 386 then
		nCountry = 3
		x = 136
		z = 91
	else
		return
	end
	
	if nCountry == GetCurCountry(sceneId,selfId) then  -- 同国进入退出
		return
	end
	
	if CallScriptFunction(310150,"IsMonsterValid_x86",sceneId,3 ) == 1 then
		x310144_g_PreTime = nCurMin
		local msg = format( x310144_g_AreaTips,sceneId,x,z,x,z)
		local msg3 ="#R古道国家军力受到敌国袭击！"
		LuaAllScenceM2Country( sceneId,msg,nCountry, 2,1)
		LuaAllScenceM2Country( sceneId,msg3,nCountry, 5,1)
	end
end

function x310144_ProcTiming( sceneId, now )

end

--玩家离开一个 area 时触发
function x310144_ProcAreaLeaved( sceneId, selfId, ScriptId, MissionId )

end