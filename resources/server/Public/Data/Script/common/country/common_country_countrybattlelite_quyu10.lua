
--屠城战区域事件

--MisDescBegin
x310149_g_ScriptId              = 310149
x310149_g_Time					= { min = 2000,max = 2059 }	--时间限制
x310149_g_minsterGuid			= 129749					--屠城战国家军力GUID
x310149_g_PreTime				=  0
x310149_g_AreaTipsInterval		=  2						--区域事件间隔
x310149_g_AreaTips				= "#R警报！敌国正在攻击我国外城#aB{goto_%d,%d,%d}(%d,%d)#aE的镇国上将军，请火速救援！"
--MisDescEnd
----------------------------------------------------------------------------------------------
function x310149_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
	
	local hour,minute,sec =GetHourMinSec(); --检查时间是否正确
	local now = hour *100 + minute
	if now < x310149_g_Time.min or now > x310149_g_Time.max then
		return
	end
	
	local nCurMin = GetMinOfYear()  --检查上次提醒时间
	local nInterval = nCurMin - x310149_g_PreTime
	if nInterval < x310149_g_AreaTipsInterval then
		return	
	end
	
	local nCountry = -1
	local x =0
	local z= 0
	if sceneId == 58 then
		nCountry = 0
		x = 128
		z = 43
	elseif sceneId == 158 then
		nCountry = 1
		x = 128
		z = 43
	elseif sceneId == 258 then
		nCountry = 2
		x = 128
		z = 213
	elseif sceneId == 358 then
		nCountry = 3
		x = 128
		z = 213
	else
		return
	end
	
	if nCountry == GetCurCountry(sceneId,selfId) then  -- 同国进入退出
		return
	end
	if CallScriptFunction(310150,"IsMonsterValid_x58",sceneId,5 ) == 1 then
		x310149_g_PreTime = nCurMin
		local msg = format( x310149_g_AreaTips,sceneId,x,z,x,z)
		local msg3 ="#R外城国家军力受到敌国袭击！"
		LuaAllScenceM2Country( sceneId,msg,nCountry, 2,1)
		LuaAllScenceM2Country( sceneId,msg3,nCountry, 5,1)
	end
end

function x310149_ProcTiming( sceneId, now )

end

--玩家离开一个 area 时触发
function x310149_ProcAreaLeaved( sceneId, selfId, ScriptId, MissionId )

end