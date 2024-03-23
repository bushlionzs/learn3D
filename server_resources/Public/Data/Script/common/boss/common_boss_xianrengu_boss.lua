x305031_g_ScriptId = 305031

x305031_g_CreateTimeSet1        = { 15, 195, 375 }
x305031_g_CreateTimeSet2        = { 495, 555, 615, 675, 735, 795, 855, 915, 975, 1035, 1095, 1155, 1215, 1275, 1335, 1395 }
-- Timer表触发时间
x305031_g_Timers                = { 
                                    { minofDay =   15,  timerId =  92 },
                                    { minofDay =  255,  timerId = 109 },
                                    { minofDay =  495,  timerId = 110 },
                                    { minofDay =  735,  timerId = 111 },
                                    { minofDay =  975,  timerId = 112 },
                                    { minofDay = 1215,  timerId = 113 },
}

x305031_g_BossTable             = { 
                                    { bossId = 9722, posX = 96, posZ = 82, ai = 0, aiscript = 255, objGuid = -1, campId = 21, liveTime = -1, bossName = "怒炎力士" }, 
                                    { bossId = 9568, posX = 96, posZ = 31, ai = 0, aiscript = 255, objGuid = -1, campId = 21, liveTime = -1, bossName = "怒炎力士" }, 
                                    { bossId = 9569, posX = 33, posZ = 35, ai = 0, aiscript = 255, objGuid = -1, campId = 21, liveTime = -1, bossName = "怒炎力士" }, 
                                    { bossId = 9570, posX = 29, posZ = 99, ai = 0, aiscript = 255, objGuid = -1, campId = 21, liveTime = -1, bossName = "怒炎力士" }, 
                                    { bossId = 9571, posX = 64, posZ = 52, ai = 0, aiscript = 255, objGuid = -1, campId = 21, liveTime = -1, bossName = "怒炎力士" }, 
                                    { bossId = 9563, posX = 53, posZ = 59, ai = 0, aiscript = 255, objGuid = -1, campId = 21, liveTime = -1, bossName = "怒炎力士" }, 
}
-- x305031_g_LiveTime              = 0
x305031_g_BossAlive                = 0

function x305031_OnTimerDoingStart( sceneId, actId, Param1, Param2, Param3, Param4, Param5)
    if x305031_g_BossAlive == 0 then
        x305031_ProcMapInit( sceneId, actId)
    end
end

-- 场景初始化完毕，设置创建Boss定时器
function x305031_ProcMapInit( sceneId, actId)
    local timeSet = {}
    local setCount = 0

    -- get current time
    local curTime = GetMinOfDay()
    if curTime >= 0 and curTime < 480 then
        -- 0:00——7：59
        if curTime >= 375 then
            -- 超过了本时间段最后一个创建时间(6:15)，直接选取下一个时间段的前4个
            timeSet[ 1] = x305031_g_CreateTimeSet2[ 1]
            timeSet[ 2] = x305031_g_CreateTimeSet2[ 2]
            timeSet[ 3] = x305031_g_CreateTimeSet2[ 3]
            timeSet[ 4] = x305031_g_CreateTimeSet2[ 4]
        else
            for i, item in x305031_g_CreateTimeSet1 do
                if curTime <= item then
                    timeSet[ 1 + setCount] = item
                    setCount = 1 + setCount
                end
            end
        end
    else
        -- 8:00——23：59
        if curTime >= 1395 then
            -- 超过了本时间段最后一个创建时间(23:15)，直接选取下一个时间段的前3个
            timeSet[ 1] = x305031_g_CreateTimeSet1[ 1]
            timeSet[ 2] = x305031_g_CreateTimeSet1[ 2]
            timeSet[ 3] = x305031_g_CreateTimeSet1[ 3]
        else
            for i, item in x305031_g_CreateTimeSet2 do
                if curTime <= item then
                    timeSet[ 1 + setCount] = item
                    setCount = 1 + setCount
                    if setCount >= 4 then
                        break
                    end
                end
            end
        end
    end

    -- 随机选一个创建时间
    local createTime = timeSet[ random( 1, getn( timeSet) ) ]
    -- 计算目前距创建时间的间隔(分钟)
    local interval = 0
    if createTime < curTime then
        interval = createTime + 1440 - curTime
    else
        interval = createTime - curTime
    end
    -- 设置创建定时器
    SetSystemTimerTick( sceneId, x305031_g_ScriptId, "OnCreateMonster", actId, interval * 60000)
    --print( interval.."分钟后Boss出现在："..sceneId)
end

function x305031_OnCreateMonster( sceneId, actId, uTime)
    -- random choose and create a boss
    local boss = x305031_g_BossTable[ 1]
    local str = ""

    boss = x305031_g_BossTable[ random( 1, 6) ]
    str = "怒炎力士出现在仙人谷一层！"
    CreateMonster( sceneId, boss.bossId, boss.posX, boss.posZ, boss.ai, boss.aiscript, x305031_g_ScriptId, boss.objGuid, boss.campId, -1, 0, boss.bossName)
    x305031_g_BossAlive = 1
    --print( "Boss位置：x = "..boss.posX.."，z = "..boss.posZ)

    -- broadcast to world
    LuaAllScenceM2Wrold( sceneId, str, CHAT_PLANE_SCROLL, 1)
    LuaAllScenceM2Wrold( sceneId, str, 5, 1)
end

-- Boss被杀后处理
function x305031_OnDie( sceneId, selfId, killerId)
    LuaAllScenceM2Wrold( sceneId, "怒炎力士已被"..GetName( sceneId, killerId).."击败！", 5, 1)
    -- 标记Boss死亡
    x305031_g_BossAlive = 0
    local minute = GetMinOfDay()
    local index = 1
    for i, item in x305031_g_Timers do
        if i == getn( x305031_g_Timers) then
            index = item.timerId
        else
            if minute >= item.minofDay and minute < x305031_g_Timers[ i + 1].minofDay then
                index = item.timerId
                break
            end
        end
    end
    x305031_ProcMapInit( sceneId, index)
end

