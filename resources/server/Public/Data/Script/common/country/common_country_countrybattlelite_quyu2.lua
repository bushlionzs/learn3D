
--屠城战区域事件

--MisDescBegin
x310141_g_ScriptId              = 310141
x310141_g_Time					= { min = 2000,max = 2059 }	--时间限制
x310141_g_minsterGuid			= 129741					--屠城战国家军力GUID
x310141_g_PreTime				=  0
x310141_g_AreaTipsInterval		=  2						--区域事件间隔
x310141_g_AreaTips				= "#R警报！敌国正在攻击我国边境#aB{goto_%d,%d,%d}(%d,%d)#aE的玉门关守备，请火速救援！"
--MisDescEnd
----------------------------------------------------------------------------------------------
function x310141_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
	local hour,minute,sec =GetHourMinSec(); --检查时间是否正确
	local now = hour *100 + minute
	if now < x310141_g_Time.min or now > x310141_g_Time.max then
		return
	end
	
	local nCurMin = GetMinOfYear()  --检查上次提醒时间
	local nInterval = nCurMin - x310141_g_PreTime
	if nInterval < x310141_g_AreaTipsInterval then
		return	
	end
	
	local nCountry = -1
	local x =0
	local z= 0
	if sceneId == 51 then
		nCountry = 0
		x = 126
		z = 81
	elseif sceneId == 151 then
		nCountry = 1
		x = 127
		z = 82
	elseif sceneId == 251 then
		nCountry = 2
		x = 126
		z = 166
	elseif sceneId == 351 then
		nCountry = 3
		x = 126
		z = 166
	else
		return
	end
	if nCountry == GetCurCountry(sceneId,selfId) then  -- 同国进入退出
		return
	end
	if CallScriptFunction(310150,"IsMonsterValid_x51",sceneId,2 ) == 1 then
		x310141_g_PreTime = nCurMin
		local msg = format( x310141_g_AreaTips,sceneId,x,z,x,z)
		local msg3 ="#R边境附近国家军力受到敌国袭击！"
		LuaAllScenceM2Country( sceneId,msg,nCountry, 2,1)
		LuaAllScenceM2Country( sceneId,msg3,nCountry, 5,1)
	end
end

function x310141_ProcTiming( sceneId, now )

end

--玩家离开一个 area 时触发
function x310141_ProcAreaLeaved( sceneId, selfId, ScriptId, MissionId )

end