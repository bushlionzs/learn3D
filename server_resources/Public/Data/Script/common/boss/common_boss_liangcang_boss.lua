x305030_g_ScriptId = 305030

x305030_g_CreateTimeSet1        = { 15, 195, 375 }
x305030_g_CreateTimeSet2        = { 495, 555, 615, 675, 735, 795, 855, 915, 975, 1035, 1095, 1155, 1215, 1275, 1335, 1395 }
-- Timer表触发时间
x305030_g_Timers                = { 0, 240, 480, 720, 960, 1200 }

x305030_g_BossTable             = { 
                                    { bossId = 9721, posX =  84, posZ =  46, ai = 0, aiscript = 256, objGuid = -1, campId = 21, liveTime = -1, bossName = "剧毒蛛王" }, 
                                    { bossId = 9564, posX =  87, posZ = 138, ai = 0, aiscript = 256, objGuid = -1, campId = 21, liveTime = -1, bossName = "剧毒蛛王" }, 
                                    { bossId = 9565, posX =  78, posZ = 216, ai = 0, aiscript = 256, objGuid = -1, campId = 21, liveTime = -1, bossName = "剧毒蛛王" }, 
                                    { bossId = 9566, posX = 137, posZ = 198, ai = 0, aiscript = 256, objGuid = -1, campId = 21, liveTime = -1, bossName = "剧毒蛛王" }, 
                                    { bossId = 9567, posX = 199, posZ = 141, ai = 0, aiscript = 256, objGuid = -1, campId = 21, liveTime = -1, bossName = "剧毒蛛王" }, 
                                    { bossId = 9577, posX = 180, posZ =  64, ai = 0, aiscript = 256, objGuid = -1, campId = 21, liveTime = -1, bossName = "剧毒蛛王" }, 
}
x305030_g_LiveTime              = 0
x305030_g_BossAlive             = 0

function x305030_OnTimerDoingStart( sceneId, actId, Param1, Param2, Param3, Param4, Param5)
    if x305030_g_BossAlive == 0 then
        x305030_ProcMapInit( sceneId, actId)
    end
end

-- 场景初始化完毕，设置创建Boss定时器
function x305030_ProcMapInit( sceneId, actId)
    local timeSet = {}
    local setCount = 0

    -- get current time
    local curTime = GetMinOfDay()
    if curTime >= 0 and curTime < 480 then
        -- 0:00——7：59
        if curTime >= 375 then
            -- 超过了本时间段最后一个创建时间(6:15)，直接选取下一个时间段的前4个
            timeSet[ 1] = x305030_g_CreateTimeSet2[ 1]
            timeSet[ 2] = x305030_g_CreateTimeSet2[ 2]
            timeSet[ 3] = x305030_g_CreateTimeSet2[ 3]
            timeSet[ 4] = x305030_g_CreateTimeSet2[ 4]
        else
            for i, item in x305030_g_CreateTimeSet1 do
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
            timeSet[ 1] = x305030_g_CreateTimeSet1[ 1]
            timeSet[ 2] = x305030_g_CreateTimeSet1[ 2]
            timeSet[ 3] = x305030_g_CreateTimeSet1[ 3]
        else
            for i, item in x305030_g_CreateTimeSet2 do
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
    SetSystemTimerTick( sceneId, x305030_g_ScriptId, "OnCreateMonster", actId, interval * 60000)
    -- print( interval.."分钟后Boss出现在："..sceneId)
end

function x305030_OnCreateMonster( sceneId, actId, uTime)
    -- random choose and create a boss
    local boss = x305030_g_BossTable[ 1]
    local str = ""

    local countryName = ""
    if sceneId >= 50 and sceneId < 150 then
        countryName = "楼兰"
    elseif sceneId >= 150 and sceneId < 250 then
        countryName = "天山"
    elseif sceneId >= 250 and sceneId < 350 then
        countryName = "昆仑"
    elseif sceneId >= 350 and sceneId < 450 then
        countryName = "敦煌"
    end
    boss = x305030_g_BossTable[ random( 1, 6) ]
    str = "剧毒蛛王出现在"..countryName.."乌孙古道！"

    CreateMonster( sceneId, boss.bossId, boss.posX, boss.posZ, boss.ai, boss.aiscript, x305030_g_ScriptId, boss.objGuid, boss.campId, -1, 0, boss.bossName)
    x305030_g_BossAlive = 1
    -- print( "Boss位置：x = "..boss.posX.."，z = "..boss.posZ)
    -- print( "SceneId："..sceneId)

    -- broadcast to world
    LuaAllScenceM2Wrold( sceneId, str, CHAT_PLANE_SCROLL, 1)
    LuaAllScenceM2Wrold( sceneId, str, 5, 1)
end

-- Boss被杀后处理
function x305030_OnDie( sceneId, selfId, killerId)
    local countryName = ""
    if sceneId >= 50 and sceneId < 150 then
        countryName = "楼兰"
    elseif sceneId >= 150 and sceneId < 250 then
        countryName = "天山"
    elseif sceneId >= 250 and sceneId < 350 then
        countryName = "昆仑"
    elseif sceneId >= 350 and sceneId < 450 then
        countryName = "敦煌"
    end
    LuaAllScenceM2Wrold( sceneId, countryName.."乌孙古道的剧毒蛛王已被"..GetName( sceneId, killerId).."击败！", 5, 1)
    x305030_g_BossAlive = 0
end

