x300179_g_ScriptId 			= 300179
x300179_g_Name              = "【美】大都美丽会"
-- 基础Buff
x300179_g_BaseBuffId        = 7646
x300179_g_BuffTable         = {
                                { buffId = 7647, xp = 4,   credit = 0, mana = 0, coffs = { { xpCoff = 12.5, creCoff = 1, manaCoff = 1, minLevel = 40, maxLevel = 70 },
                                                                                             { xpCoff = 22.5, creCoff = 1, manaCoff = 1, minLevel = 70, maxLevel = 80 },
                                                                                             { xpCoff = 45, creCoff = 1, manaCoff = 1, minLevel = 80, maxLevel = 1000 },
                                                                                           }, name = "经验" }, 
                                { buffId = 7648, xp = 8,   credit = 0, mana = 0, coffs = { { xpCoff = 12.5, creCoff = 1, manaCoff = 1, minLevel = 40, maxLevel = 70 },
                                                                                             { xpCoff = 22.5, creCoff = 1, manaCoff = 1, minLevel = 70, maxLevel = 80 },
                                                                                             { xpCoff = 45, creCoff = 1, manaCoff = 1, minLevel = 80, maxLevel = 1000 },
                                                                                           }, name = "经验" }, 
                                { buffId = 7649, xp = 0,   credit = 4, mana = 0, coffs = { { xpCoff = 12.5, creCoff = 1, manaCoff = 1, minLevel = 40, maxLevel = 70 },
                                                                                             { xpCoff = 22.5, creCoff = 1, manaCoff = 1, minLevel = 70, maxLevel = 80 },
                                                                                             { xpCoff = 22.5, creCoff = 1, manaCoff = 1, minLevel = 80, maxLevel = 1000 },
                                                                                           }, name = "声望" }, 
                                { buffId = 7650, xp = 0,   credit = 8, mana = 0, coffs = { { xpCoff = 12.5, creCoff = 1, manaCoff = 1, minLevel = 40, maxLevel = 70 },
                                                                                             { xpCoff = 22.5, creCoff = 1, manaCoff = 1, minLevel = 70, maxLevel = 80 },
                                                                                             { xpCoff = 22.5, creCoff = 1, manaCoff = 1, minLevel = 80, maxLevel = 1000 },
                                                                                           }, name = "声望" }, 
                                { buffId = 7645, xp = 0,   credit = 0, mana = 8, coffs = { { xpCoff = 12.5, creCoff = 1, manaCoff = 1, minLevel = 40, maxLevel = 70 },
                                                                                             { xpCoff = 22.5, creCoff = 1, manaCoff = 1, minLevel = 70, maxLevel = 80 },
                                                                                             { xpCoff = 22.5, creCoff = 1, manaCoff = 1, minLevel = 80, maxLevel = 1000 },
                                                                                           }, name = "威望" }, 
                                { buffId = 7667, xp = 8,   credit = 0, mana = 0, coffs = { { xpCoff = 12.5, creCoff = 1, manaCoff = 1, minLevel = 40, maxLevel = 70 },
                                                                                             { xpCoff = 22.5, creCoff = 1, manaCoff = 1, minLevel = 70, maxLevel = 80 },
                                                                                             { xpCoff = 45, creCoff = 1, manaCoff = 1, minLevel = 80, maxLevel = 1000 },
                                                                                           }, name = "经验" }, 
                                { buffId = 7666, xp = 0,   credit = 8, mana = 0, coffs = { { xpCoff = 12.5, creCoff = 1, manaCoff = 1, minLevel = 40, maxLevel = 70 },
                                                                                             { xpCoff = 22.5, creCoff = 1, manaCoff = 1, minLevel = 70, maxLevel = 80 },
                                                                                             { xpCoff = 22.5, creCoff = 1, manaCoff = 1, minLevel = 80, maxLevel = 1000 },
                                                                                           }, name = "声望" }, 
                                { buffId = 7665, xp = 0,   credit = 0, mana = 8, coffs = { { xpCoff = 12.5, creCoff = 1, manaCoff = 1, minLevel = 40, maxLevel = 70 },
                                                                                             { xpCoff = 22.5, creCoff = 1, manaCoff = 1, minLevel = 70, maxLevel = 80 },
                                                                                             { xpCoff = 22.5, creCoff = 1, manaCoff = 1, minLevel = 80, maxLevel = 1000 },
                                                                                           }, name = "威望" }, 
                                { buffId = 7668, xp = 4,   credit = 0, mana = 0, coffs = { { xpCoff = 12.5, creCoff = 1, manaCoff = 1, minLevel = 40, maxLevel = 70 },
                                                                                             { xpCoff = 22.5, creCoff = 1, manaCoff = 1, minLevel = 70, maxLevel = 80 },
                                                                                             { xpCoff = 45, creCoff = 1, manaCoff = 1, minLevel = 80, maxLevel = 1000 },
                                                                                           }, name = "经验" }, 
                                { buffId = 7669, xp = 0,   credit = 4, mana = 0, coffs = { { xpCoff = 12.5, creCoff = 1, manaCoff = 1, minLevel = 40, maxLevel = 70 },
                                                                                             { xpCoff = 22.5, creCoff = 1, manaCoff = 1, minLevel = 70, maxLevel = 80 },
                                                                                             { xpCoff = 22.5, creCoff = 1, manaCoff = 1, minLevel = 80, maxLevel = 1000 },
                                                                                           }, name = "声望" }, 
}
-- 现金或金卡余额不足
x300179_g_strNotEnoughMoney = "您身上的现银（银卡）不足，不能使用预约托管功能"
-- 预约托管费用
x300179_g_Money             = 2000
-- 舞厅关闭时间（一天的第N分钟）
x300179_g_CloseTime         = 540
-- 舞厅开放时间（一天的第N分钟）
x300179_g_OpenTime          = 1380

x300179_g_AdditionalLevel   = 90

function x300179_ProcEnumEvent( sceneId, selfId, targetId, MissionId)
    -- 等级限制
    if GetLevel( sceneId, selfId) < 40 then
        return
    end
    local minute = GetMinOfDay()
    if minute >= x300179_g_CloseTime and minute < x300179_g_OpenTime then
        AddQuestNumText( sceneId, x300179_g_ScriptId, "【美丽会】预约托管", 3)
    end
    -- local y,m,d = GetYearMonthDay()
    -- print( mod( y, 4).."*-*-*-*" )
    --CancelSpecificImpact( sceneId, selfId, x300179_g_BaseBuffId)
end


function x300179_ProcEventEntry( sceneId, selfId, targetId, idScript, idExt)
    local haveBuff = 0
    local level = GetLevel( sceneId, selfId)
    local index = 1
    for i, item in x300179_g_BuffTable[ 1].coffs do
        if level >= item.minLevel and level < item.maxLevel then
            index = i
        end
    end

    -- 检查玩家身上有没有挂机Buff，至少要有一个才能继续
    for i, item in x300179_g_BuffTable do
        if IsHaveSpecificImpact( sceneId, selfId, item.buffId) == 1 then
            haveBuff = 1
            break
        end
    end
    if haveBuff == 0 then
        BeginQuestEvent( sceneId)
            AddQuestText( sceneId, "#Y"..x300179_g_Name)
            AddQuestText( sceneId, "\t很抱歉，您身上必须有酒或雪茄才能预约托管。" )
        EndQuestEvent()
        DispatchQuestEventList( sceneId, selfId, targetId, x300179_g_ScriptId, -1)
        return
    end

    local times = 0
    local xpAddition = 1
    if level >= x300179_g_AdditionalLevel then
        xpAddition = 1.3
    end
    BeginQuestEvent( sceneId)
    AddQuestText( sceneId, "#Y"..x300179_g_Name)
    AddQuestText( sceneId, "\t欢迎您使用预约托管服务，从本次美丽会开始到关闭这10个小时之间您可获得的奖励如下：#r" )
    for i, item in x300179_g_BuffTable do
        if IsHaveSpecificImpact( sceneId, selfId, item.buffId) == 1 then
            local amountTime = GetImpactContinuanceByDataIndex( sceneId, selfId, item.buffId)
            if amountTime > 0 then
                local remainTime = amountTime - GetImpactContinuanceElapsed( sceneId, selfId, item.buffId)
                times = remainTime / 10000
                local reward = item.xp * item.coffs[ index].xpCoff * level * xpAddition + item.credit + item.mana
                if reward > 0 then
                    AddQuestText( sceneId, format( "\t#Y%s：%d#r", item.name, reward * times) )
                end
            end
        end
    end
	local ding=0
	local liang=0
	local wen=0
	local level = GetLevel(sceneId, selfId)
	local money = floor( level*200)
	ding = floor( money / (1000*1000) )
	liang = floor( mod(money,1000*1000)/ 1000 )
	wen = mod(money,1000)
	local Readme = format("\t#G当您选择使用#R预约托管#G功能，您需要花费#R%d锭%d两%d文#W现银（银卡）", ding,liang,wen);
	AddQuestText( sceneId,Readme )
    AddQuestText( sceneId, "\t#G在美丽会开启前，如果您选择确定，您将会预约今天的美丽会收益，并立即离线。您的预约将在#R当天23：00开始生效#G，并且于#R次日9：00预约结束#G。在此期间，您可获得最多10个小时的收益，所以您必须在23：00后再次上线才能获得收益，如果您身上的跳舞奖励状态时间大于美丽会已开放时间，我们将会把剩余的跳舞奖励时间返还给您，您需要现在预约托管吗？#r" )
	AddQuestText( sceneId, "\t#G小提示：您离线后再上线时间必须在#R本次美丽会开启#G后，才能获得奖励。并且离线后再次上线时最好在#R次日9：00后#G，就可以获得最理想的收益。" )
    EndQuestEvent()
    DispatchQuestInfo( sceneId, selfId, targetId, x300179_g_ScriptId, -1)
end


function x300179_ProcMapPlayerNewConnectEnter( sceneId, selfId)
    if IsInitBecauseReconnect( sceneId, selfId) == 1 then
        if GetQuestData( sceneId, selfId, MD_WUTING_PRECONTRACT_FLAG[ 1], MD_WUTING_PRECONTRACT_FLAG[ 2], MD_WUTING_PRECONTRACT_FLAG[ 3] ) == 1 then
            -- 如果预约了并断线重连上来就立即给他踢下去
            KickPlayer( sceneId, selfId, 0)
        end
        return
    end

    if GetQuestData( sceneId, selfId, MD_WUTING_PRECONTRACT_FLAG[ 1], MD_WUTING_PRECONTRACT_FLAG[ 2], MD_WUTING_PRECONTRACT_FLAG[ 3] ) == 0 then
        return
    end

    -- 恢复活力
    --SetPlayerVigor( sceneId, selfId, GetPlayerMaxVigor( sceneId, selfId) )

    -- 得到预约预约时间和日期
    local olDate = GetQuestData( sceneId, selfId, MD_WUTING_PRECONTRACT_DATE[ 1], MD_WUTING_PRECONTRACT_DATE[ 2], MD_WUTING_PRECONTRACT_DATE[ 3] )
    local olTime = GetQuestData( sceneId, selfId, MD_WUTING_PRECONTRACT_TIME[ 1], MD_WUTING_PRECONTRACT_TIME[ 2], MD_WUTING_PRECONTRACT_TIME[ 3] )

    local level = GetLevel( sceneId, selfId)
    local xpAddition = 1
    if level >= x300179_g_AdditionalLevel then
        xpAddition = 1.3
    end
    local lvCoff = 12.5
    if level >= 70 then
        lvCoff = 22.5
    end

    local index = 1
    for i, item in x300179_g_BuffTable[ 1].coffs do
        if level >= item.minLevel and level < item.maxLevel then
            index = i
        end
    end

    -- 计算预约时间
    local times = 3600
    local onDate = GetDayOfYear()
    local onTime = GetMinOfDay()
    if onDate == olDate then
        -- 同一天
        if onTime >= x300179_g_OpenTime then
            -- 上线时间在23点之后
            times = ( onTime - x300179_g_OpenTime) * 6
        else
            -- 上线时间在23点之前
            times = 0
        end
    else
        -- 跨天
        local days = onDate - olDate
        if olDate > onDate then
            -- 跨年
            local y,m,d = GetYearMonthDay()
            if mod( y, 4) == 0 then
                -- 闰年
                days = onDate + 366 - olDate
            else
                days = onDate + 365 - olDate
            end
        end
        if days == 1 and onTime < olTime then
            -- 跨天并且不足24小时
            if onTime < x300179_g_CloseTime then
                -- 上线时间在9点之前
                times = 60 + onTime
                times = times * 6
            end
        end
    end

    -- 写日志
    local strLog = format( "WTL: Player %s who has precontract management enter game with %d offline times. ", GetName( sceneId, selfId), times)
    WriteLog( 1, strLog)

    if times == 0 then
        -- 更新预约托管标记
        SetQuestData( sceneId, selfId, MD_WUTING_PRECONTRACT_FLAG[ 1], MD_WUTING_PRECONTRACT_FLAG[ 2], MD_WUTING_PRECONTRACT_FLAG[ 3], 0)

        return
    end

    local xpAmount = 0
    local creditAmount = 0
    local manaAmount = 0
    local temp = GetImpactContinuanceByDataIndex( sceneId, selfId, x300179_g_BaseBuffId)
    local baseRemain = 0
    if temp > 0 then
        baseRemain = temp - GetImpactContinuanceElapsed( sceneId, selfId, x300179_g_BaseBuffId)
        baseRemain = baseRemain / 10000
    end
    for i, item in x300179_g_BuffTable do
        if IsHaveSpecificImpact( sceneId, selfId, item.buffId) == 1 then
            local amountTime = GetImpactContinuanceByDataIndex( sceneId, selfId, item.buffId)
            if amountTime > 0 then
                local remainTime = amountTime - GetImpactContinuanceElapsed( sceneId, selfId, item.buffId)
                local buffTimes = remainTime / 10000
                local strLog = format( "WTL: Player %s remain buff( id: %d, times: %d) when connection. ", GetName( sceneId, selfId), item.buffId, buffTimes)
                WriteLog( 1, strLog)
                -- 获得每次Timer触发可获得的奖励
                local reward = item.xp * item.coffs[ index].xpCoff * level * xpAddition + item.credit + item.mana
                local finalReward = 0
                local remainBuff = 0
                if buffTimes > times then   -- Buff时间大于离线时间
                    -- 用离线时间算
                    finalReward = times * reward
                    -- 剩余Buff时间
                    remainBuff = ( buffTimes - times) * 10000
                else    -- 离线时间大于Buff时间
                    -- 用Buff时间计算
                    finalReward = buffTimes * reward
                end
                if item.xp ~= 0 then
                    AddExp( sceneId, selfId, finalReward)
                    WriteLog( 1, format( "WTL: Add %d exp with buff %d. ", finalReward, item.buffId) )
                    xpAmount = xpAmount + finalReward
                elseif item.credit ~= 0 then
                    SetShengWang( sceneId, selfId, GetShengWang( sceneId, selfId) + finalReward)
                    WriteLog( 1, format( "WTL: Add %d ShengWang. ", finalReward) )
                    creditAmount = creditAmount + finalReward
                elseif item.mana ~= 0 then
                    SetPlayerGoodBadValue( sceneId, selfId, GetPlayerGoodBadValue( sceneId, selfId) + finalReward)
                    WriteLog( 1, format( "WTL: Add %d GoodBad. ", finalReward) )
                    manaAmount = manaAmount + finalReward
                end
                -- 把剩余Buff还给玩家
                SetImpactContinuanceByDataIndex( sceneId, selfId, item.buffId, remainBuff)
                WriteLog( 1, format( "WTL: Refresh Buff(id:%d) time is %d ms. ", item.buffId, remainBuff) )
                ResetImpactContinuanceElapsed( sceneId, selfId, item.buffId)
                RefreshImpactByDataIndex( sceneId, selfId, item.buffId)
            end
        end
    end

    -- 显示奖励更新
    local strReward = "您在预约托管时间内获得的奖励如下：#G#r"
    local strDialog = "\t#G感谢您使用本店的预约托管服务，在您预约的这段时间您总共获得的奖励如下：#r #r"
    if xpAmount > 0 then
        strReward = strReward..format( "经验：%d点#r", xpAmount)
        strDialog = strDialog..format( "经验：%d点#r #r", xpAmount)
    end
    if creditAmount > 0 then
        strReward = strReward..format( "声望：%d点#r", creditAmount)
        strDialog = strDialog..format( "声望：%d点#r #r", creditAmount)
    end
    if manaAmount > 0 then
        strReward = strReward..format( "威望：%d点#r", manaAmount)
        strDialog = strDialog..format( "威望：%d点#r #r", manaAmount)
    end
    BeginQuestEvent( sceneId)
        AddQuestText( sceneId, "#Y".."【美丽会】预约托管" )
        AddQuestText( sceneId, strDialog)
    EndQuestEvent( sceneId)
    DispatchQuestEventList( sceneId, selfId, 0)
    LuaScenceM2Player( sceneId, selfId, strReward, GetName( sceneId, selfId), 1, 1)

    -- 更新预约托管标记
    SetQuestData( sceneId, selfId, MD_WUTING_PRECONTRACT_FLAG[ 1], MD_WUTING_PRECONTRACT_FLAG[ 2], MD_WUTING_PRECONTRACT_FLAG[ 3], 0)
end


function x300179_ProcAcceptCheck( sceneId, selfId, targetId)
    local minute = GetMinOfDay()
    if minute < x300179_g_CloseTime or minute >= x300179_g_OpenTime then
        Msg2Player( sceneId, selfId, "很抱歉，美丽会开放期间我们不接受预约托管", 8, 3)
        return
    end

    -- 扣钱
	local level = GetLevel(sceneId, selfId)
	local money = level*200
    if GetGoldMode( sceneId, selfId ) == 1 then
        if CostMoney( sceneId, selfId, 0, money,306) ~= 1 then
            if CostMoney(sceneId, selfId, 1, money,306) ~= 1 then
                Msg2Player( sceneId, selfId, x300179_g_strNotEnoughMoney.."。", 8, 2)
                Msg2Player( sceneId, selfId, x300179_g_strNotEnoughMoney, 8, 3)
                return
            end
        end
    else
        if CostMoney( sceneId, selfId, 1, money,306) ~= 1 then
            if CostMoney(sceneId, selfId, 0, money,306) ~= 1 then
                Msg2Player( sceneId, selfId, x300179_g_strNotEnoughMoney.."。", 8, 2)
                Msg2Player( sceneId, selfId, x300179_g_strNotEnoughMoney, 8, 3)
                return
            end
        end
    end

    -- 写日志
    local strLog = format( "WTL: Player %s use precontract management with sw(%d), ww(%d), xp=", GetName( sceneId, selfId), GetShengWang( sceneId, selfId), GetPlayerGoodBadValue( sceneId, selfId) )
    strLog = strLog..GetExp( sceneId, selfId)
    WriteLog( 1, strLog)

    for i, item in x300179_g_BuffTable do
        if IsHaveSpecificImpact( sceneId, selfId, item.buffId) == 1 then
            local amountTime = GetImpactContinuanceByDataIndex( sceneId, selfId, item.buffId)
            if amountTime > 0 then
                local remainTime = amountTime - GetImpactContinuanceElapsed( sceneId, selfId, item.buffId)
                strLog = format( "WTL: With Buff %d remain buff time %d second. ", item.buffId, floor( remainTime / 1000) )
                WriteLog( 1, strLog)
            end
        end
    end

    -- 记录日期
    SetQuestData( sceneId, selfId, MD_WUTING_PRECONTRACT_DATE[ 1], MD_WUTING_PRECONTRACT_DATE[ 2], MD_WUTING_PRECONTRACT_DATE[ 3], GetDayOfYear() )
    -- 记录时间
    SetQuestData( sceneId, selfId, MD_WUTING_PRECONTRACT_TIME[ 1], MD_WUTING_PRECONTRACT_TIME[ 2], MD_WUTING_PRECONTRACT_TIME[ 3], GetMinOfDay() )
    -- 设置预约托管标记
    SetQuestData( sceneId, selfId, MD_WUTING_PRECONTRACT_FLAG[ 1], MD_WUTING_PRECONTRACT_FLAG[ 2], MD_WUTING_PRECONTRACT_FLAG[ 3], 1)
    -- 把玩家返回登录界面
    KickPlayer( sceneId, selfId, 1)
    -- 设置T人安全时间
    SetKickTime( sceneId, selfId, 11000)
   
end


