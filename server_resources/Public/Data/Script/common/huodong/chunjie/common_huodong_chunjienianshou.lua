-- 春节年兽活动

-- 脚本号
x310801_g_ScriptId = 310801						

function x310801_OnTimerDoingStart( sceneId, actId, Param1, Param2, Param3, Param4, Param5)
    --SetSystemTimerTick( sceneId, 310801, "BroadCast", actId, 10 * 1000)
    if sceneId ~= 88 and sceneId ~= 188 and sceneId ~= 288 and sceneId ~= 388 then
        return
    end

    local day = GetDayOfYear()
    local rx = random( 3, 5)
    local rz = random( 3, 5)
    -- 2010年2月14日至2月22日(branch)
    if day >= 44 and day <= 52  then
        CreateMonster( sceneId, 9752, 84 + rx, 164 + rz, 1, 1006, x310801_g_ScriptId, -1, 21, 3600000, 0)
        LuaAllScenceM2Wrold( sceneId, "“年”突然出现在铁骑牧场，大肆掠夺钱物，破坏春节喜庆。望各国勇士勇于前往保护家园！！击败年兽可获得大量宝物哦～！", CHAT_PLANE_SCROLL, 1)
    end
end

function x310801_OnDie( sceneId, selfId, killerId)
    LuaAllScenceM2Wrold( sceneId, "经过各国勇士的奋勇抵抗，“年”已被消灭！", CHAT_PLANE_SCROLL, 1)
end

