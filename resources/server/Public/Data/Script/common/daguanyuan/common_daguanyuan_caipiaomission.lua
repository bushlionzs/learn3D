-- Ω≈±æ∫≈
x310362_g_ScriptId              = 310362
-- ¥Ûπ€‘∞–“‘À»Ø
x310362_g_LuckyTicket           = 12035040
-- ¥Ûπ€‘∞≥°æ∞ID
x310362_g_TargetSceneId         = 40
-- open flag
x310362_g_IsEnableId            = 1043

function x310362_ProcEnumEvent( sceneId, selfId, NPCId, MissionId)
end

function x310362_ProcEventEntry( sceneId, selfId, NPCId, idScript, idExt)
end

function x310362_GiveItem( sceneId, selfId)
    if HaveItemInBag( sceneId, selfId, x310362_g_LuckyTicket) <= 0 then
        BeginAddItem( sceneId)	
        AddBindItem( sceneId, x310362_g_LuckyTicket, 1)
        if EndAddItem( sceneId, selfId) > 0 then
            AddItemListToPlayer( sceneId, selfId)
        else	
            local msg = format( "#Y±≥∞¸ø’º‰≤ª◊„£¨Œﬁ∑®µ√µΩ#{_ITEM%d}£°", x310362_g_LuckyTicket)			
            Msg2Player( sceneId, selfId, msg, 8, 3)
            return
        end
    end

    local bagIndex = FindFirstBagIndexOfItem( sceneId, selfId, x310362_g_LuckyTicket)
    if bagIndex >= 0 then
        local caipiao = GetCountryParam( sceneId, 0, CD_DAGUANYUAN_CAIPIAO1)
        if caipiao < 0 then
            caipiao = 0
        end
        local day, week = GetWeek()
        if GetCountryParam( sceneId, 2, CD_INDEX_RUOGUO_START_FLAG) ~= week then
            SetCountryParam( sceneId, 2, CD_INDEX_RUOGUO_START_FLAG, week)
            SetCountryParam( sceneId, 3, CD_INDEX_RUOGUO_START_FLAG, day)
            SetCountryParam( sceneId, 1, CD_DAGUANYUAN_CAIPIAO1, -1)
            SetCountryParam( sceneId, 2, CD_DAGUANYUAN_CAIPIAO1, -1)
            SetCountryParam( sceneId, 3, CD_DAGUANYUAN_CAIPIAO1, -1)
            SetCountryParam( sceneId, 0, CD_DAGUANYUAN_CAIPIAO2, -1)
            SetCountryParam( sceneId, 1, CD_DAGUANYUAN_CAIPIAO2, -1)
            SetCountryParam( sceneId, 2, CD_DAGUANYUAN_CAIPIAO2, -1)
            SetCountryParam( sceneId, 3, CD_DAGUANYUAN_CAIPIAO2, -1)
            caipiao = 0
        else
            if GetCountryParam( sceneId, 3, CD_INDEX_RUOGUO_START_FLAG) ~= day then
                SetCountryParam( sceneId, 3, CD_INDEX_RUOGUO_START_FLAG, day)
                SetCountryParam( sceneId, 1, CD_DAGUANYUAN_CAIPIAO1, -1)
                SetCountryParam( sceneId, 2, CD_DAGUANYUAN_CAIPIAO1, -1)
                SetCountryParam( sceneId, 3, CD_DAGUANYUAN_CAIPIAO1, -1)
                SetCountryParam( sceneId, 0, CD_DAGUANYUAN_CAIPIAO2, -1)
                SetCountryParam( sceneId, 1, CD_DAGUANYUAN_CAIPIAO2, -1)
                SetCountryParam( sceneId, 2, CD_DAGUANYUAN_CAIPIAO2, -1)
                SetCountryParam( sceneId, 3, CD_DAGUANYUAN_CAIPIAO2, -1)
                caipiao = 0
            end
        end
        GamePlayScriptLog(sceneId, selfId, 1651)
        local first = floor( caipiao / 80)
        local second = mod( caipiao, 80)
        SetItemParam( sceneId, selfId, bagIndex, 8, 1, first)
        SetItemParam( sceneId, selfId, bagIndex, 10, 1, second)
        -- save get date
        SetItemParam( sceneId, selfId, bagIndex, 4, 2, GetDayOfYear() )

        second = second + 1
        if second >= 80 then
            second = 0
            first = first + 1
        end
        SetCountryParam( sceneId, 0, CD_DAGUANYUAN_CAIPIAO1, first * 80 + second)
    end
end

function x310362_GetReward( sceneId)
    local caipiao = GetCountryParam( sceneId, 0, CD_DAGUANYUAN_CAIPIAO1)
    if caipiao <= 0 then
        return -1, -1, -1
    end
    local first = floor( caipiao / 80)
    local second = mod( caipiao, 80)
    if second > 0 then
        second = second - 1
    end
    local a = random( 0, first)
    local b = random( 0, second)

    return a * 80 + b, a, b
end

function x310362_OnTimerDoingStart( sceneId, actId, Param1, Param2, Param3, Param4, Param5)
    if GetGameOpenById( x310362_g_IsEnableId) <= 0 then
        return
    end

    if sceneId ~= x310362_g_TargetSceneId then
        return
    end

    local day, week = GetWeek()
    if day ~= 6 and day ~= 0 then
        return
    end

    SetCountryParam( sceneId, 1, CD_DAGUANYUAN_CAIPIAO1, -1)
    SetCountryParam( sceneId, 2, CD_DAGUANYUAN_CAIPIAO1, -1)
    SetCountryParam( sceneId, 3, CD_DAGUANYUAN_CAIPIAO1, -1)
    SetCountryParam( sceneId, 0, CD_DAGUANYUAN_CAIPIAO2, -1)
    SetCountryParam( sceneId, 1, CD_DAGUANYUAN_CAIPIAO2, -1)
    SetCountryParam( sceneId, 2, CD_DAGUANYUAN_CAIPIAO2, -1)
    SetCountryParam( sceneId, 3, CD_DAGUANYUAN_CAIPIAO2, -1)

    local curTime = GetMinOfDay()
    local r, a, b = x310362_GetReward( sceneId)
    SetCountryParam( sceneId, 1, CD_DAGUANYUAN_CAIPIAO1, r)
    if r ~= -1 then
        LuaThisScenceM2Wrold( sceneId, format( "√Œ¡ƒ¿÷Õ∏ø™Ω±£¨÷–Ω±∫≈¬Î «%d∫Õ%d", a, b), 5, 1)
        LuaThisScenceM2Wrold( sceneId, format( "√Œ¡ƒ¿÷Õ∏ø™Ω±£¨÷–Ω±∫≈¬Î «%d∫Õ%d°£", a, b), 1, 1)
        LuaThisScenceM2Wrold( sceneId, format( "√Œ¡ƒ¿÷Õ∏ø™Ω±£¨÷–Ω±∫≈¬Î «%d∫Õ%d", a, b), 2, 1)
    end

    SetSystemTimerTick( sceneId, x310362_g_ScriptId, "CheckTime", actId, 30000)
end

function x310362_CheckTime( sceneId, actId, uTime)
    if GetGameOpenById( x310362_g_IsEnableId) <= 0 then
        return
    end

    local curTime = GetMinOfDay()
    local r, a, b = x310362_GetReward( sceneId)
    if curTime == 750 and GetCountryParam( sceneId, 2, CD_DAGUANYUAN_CAIPIAO1) == -1 then
        SetCountryParam( sceneId, 2, CD_DAGUANYUAN_CAIPIAO1, r)
        LuaThisScenceM2Wrold( sceneId, format( "√Œ¡ƒ¿÷Õ∏ø™Ω±£¨÷–Ω±∫≈¬Î «%d∫Õ%d", a, b), 5, 1)
        LuaThisScenceM2Wrold( sceneId, format( "√Œ¡ƒ¿÷Õ∏ø™Ω±£¨÷–Ω±∫≈¬Î «%d∫Õ%d°£", a, b), 1, 1)
        LuaThisScenceM2Wrold( sceneId, format( "√Œ¡ƒ¿÷Õ∏ø™Ω±£¨÷–Ω±∫≈¬Î «%d∫Õ%d", a, b), 2, 1)        
    elseif curTime == 870 and GetCountryParam( sceneId, 3, CD_DAGUANYUAN_CAIPIAO1) == -1 then
        SetCountryParam( sceneId, 3, CD_DAGUANYUAN_CAIPIAO1, r)
        LuaThisScenceM2Wrold( sceneId, format( "√Œ¡ƒ¿÷Õ∏ø™Ω±£¨÷–Ω±∫≈¬Î «%d∫Õ%d", a, b), 5, 1)
        LuaThisScenceM2Wrold( sceneId, format( "√Œ¡ƒ¿÷Õ∏ø™Ω±£¨÷–Ω±∫≈¬Î «%d∫Õ%d°£", a, b), 1, 1)
        LuaThisScenceM2Wrold( sceneId, format( "√Œ¡ƒ¿÷Õ∏ø™Ω±£¨÷–Ω±∫≈¬Î «%d∫Õ%d", a, b), 2, 1)
    elseif curTime == 990 and GetCountryParam( sceneId, 0, CD_DAGUANYUAN_CAIPIAO2) == -1 then
        SetCountryParam( sceneId, 0, CD_DAGUANYUAN_CAIPIAO2, r)
        LuaThisScenceM2Wrold( sceneId, format( "√Œ¡ƒ¿÷Õ∏ø™Ω±£¨÷–Ω±∫≈¬Î «%d∫Õ%d", a, b), 5, 1)
        LuaThisScenceM2Wrold( sceneId, format( "√Œ¡ƒ¿÷Õ∏ø™Ω±£¨÷–Ω±∫≈¬Î «%d∫Õ%d°£", a, b), 1, 1)
        LuaThisScenceM2Wrold( sceneId, format( "√Œ¡ƒ¿÷Õ∏ø™Ω±£¨÷–Ω±∫≈¬Î «%d∫Õ%d", a, b), 2, 1)
    elseif curTime == 1110 and GetCountryParam( sceneId, 1, CD_DAGUANYUAN_CAIPIAO2) == -1 then
        SetCountryParam( sceneId, 1, CD_DAGUANYUAN_CAIPIAO2, r)
        LuaThisScenceM2Wrold( sceneId, format( "√Œ¡ƒ¿÷Õ∏ø™Ω±£¨÷–Ω±∫≈¬Î «%d∫Õ%d", a, b), 5, 1)
        LuaThisScenceM2Wrold( sceneId, format( "√Œ¡ƒ¿÷Õ∏ø™Ω±£¨÷–Ω±∫≈¬Î «%d∫Õ%d°£", a, b), 1, 1)
        LuaThisScenceM2Wrold( sceneId, format( "√Œ¡ƒ¿÷Õ∏ø™Ω±£¨÷–Ω±∫≈¬Î «%d∫Õ%d", a, b), 2, 1)
    elseif curTime == 1230 and GetCountryParam( sceneId, 2, CD_DAGUANYUAN_CAIPIAO2) == -1 then
        SetCountryParam( sceneId, 2, CD_DAGUANYUAN_CAIPIAO2, r)
        LuaThisScenceM2Wrold( sceneId, format( "√Œ¡ƒ¿÷Õ∏ø™Ω±£¨÷–Ω±∫≈¬Î «%d∫Õ%d", a, b), 5, 1)
        LuaThisScenceM2Wrold( sceneId, format( "√Œ¡ƒ¿÷Õ∏ø™Ω±£¨÷–Ω±∫≈¬Î «%d∫Õ%d°£", a, b), 1, 1)
        LuaThisScenceM2Wrold( sceneId, format( "√Œ¡ƒ¿÷Õ∏ø™Ω±£¨÷–Ω±∫≈¬Î «%d∫Õ%d", a, b), 2, 1)
    elseif curTime == 1350 and GetCountryParam( sceneId, 3, CD_DAGUANYUAN_CAIPIAO2) == -1 then
        SetCountryParam( sceneId, 3, CD_DAGUANYUAN_CAIPIAO2, r)
        LuaThisScenceM2Wrold( sceneId, format( "√Œ¡ƒ¿÷Õ∏ø™Ω±£¨÷–Ω±∫≈¬Î «%d∫Õ%d", a, b), 5, 1)
        LuaThisScenceM2Wrold( sceneId, format( "√Œ¡ƒ¿÷Õ∏ø™Ω±£¨÷–Ω±∫≈¬Î «%d∫Õ%d°£", a, b), 1, 1)
        LuaThisScenceM2Wrold( sceneId, format( "√Œ¡ƒ¿÷Õ∏ø™Ω±£¨÷–Ω±∫≈¬Î «%d∫Õ%d", a, b), 2, 1)
    end

    if curTime < 1350 then
        SetSystemTimerTick( sceneId, x310362_g_ScriptId, "CheckTime", actId, 30000)
    end
end


