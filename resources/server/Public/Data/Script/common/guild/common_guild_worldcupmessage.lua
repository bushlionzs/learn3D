--MisDescBegin 
x300837_g_ScriptId 					= 	300837
--MisDescEnd

-- x300837_g_BroadCastTable            = {
                                        -- { minute = 1020, clocktime = 1700, message = "世界杯战场将于17：30开启，请参赛帮会做好准备！" }, 
                                        -- { minute = 1045, clocktime = 1725, message = "世界杯战场将在5分钟后开始！" }, 
                                        -- { minute = 1050, clocktime = 1730, message = "世界杯战场火热进行中" }, 
                                        -- { minute = 1065, clocktime = 1745, message = "世界杯战场火热进行中" }, 
                                        -- { minute = 1075, clocktime = 1755, message = "世界杯战场世界杯战场结束还有5分钟！" }, 
                                        -- { minute = 1080, clocktime = 1800, message = "世界杯战场世界杯战场已经结束！" }, 
-- }
x300837_g_BroadCastTable            = {
                                        { minute = 930, clocktime = 1530, message = "世界杯战场将于16：00开启，请参赛帮会做好准备！" }, 
                                        { minute = 955, clocktime = 1555, message = "世界杯战场将在5分钟后开始！" }, 
                                        { minute = 960, clocktime = 1600, message = "世界杯战场火热进行中" }, 
                                        { minute = 975, clocktime = 1615, message = "世界杯战场火热进行中" }, 
                                        { minute = 985, clocktime = 1625, message = "世界杯战场结束还有5分钟！" }, 
                                        { minute = 990, clocktime = 1630, message = "世界杯战场已经结束！" }, 
}

function x300837_OnTimerDoingStart( sceneId, actId, Param1, Param2, Param3, Param4, Param5)
    -- 周四到周日才广播此消息
    local week, YearIndex = GetWeek()
    if week ~= 0 then
        return
    end

    -- 如果处于禁止报名阶段即使杀死十八魔君也不广播消息
    local state = GetWorldCupState( sceneId)
    if state == STATE_GUILD_WORLDCUP_DISABLESIGNUP then
        return
    end

    local switch = GetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_SWITCH)
    -- 如果比赛开启才启用Timer
    if switch == 1 then
        SetSystemTimerTick( sceneId, 300837, "BroadCast", actId, 60000)
    end
end

function x300837_BroadCast( sceneId, actId, uTime)
    local curTime = GetMinOfDay()

    local broadcast = 0
    for i, item in x300837_g_BroadCastTable do
        if curTime == item.minute then
            broadcast = i
            break
        end
    end

    if broadcast ~= 0 then
        LuaAllScenceM2Wrold( sceneId, x300837_g_BroadCastTable[ broadcast].message, CHAT_PLANE_SCROLL, 1)
        LuaAllScenceM2Wrold( sceneId, x300837_g_BroadCastTable[ broadcast].message, CHAT_LEFTDOWN, 1)
        if broadcast == getn( x300837_g_BroadCastTable) then
            -- 最后一次触发Timer后不再设置定时器
            return
        end
    end
    SetSystemTimerTick( sceneId, 300837, "BroadCast", actId, 60000)
end

