x300178_g_ScriptId 				= 300178
x300178_g_Name                  = "【美】大都美丽会"
-- 基础Buff
x300178_g_BaseBuffId        = 7646
-- 2倍经验
x300178_g_XPBuffId          = 7647
-- 4倍经验
x300178_g_DoubleXPBuffId    = 7648
-- 2倍声望
x300178_g_CreditBuffId      = 7649
-- 4倍声望
x300178_g_DoubleCreditBuffId= 7650
-- 4倍威望
x300178_g_4ManaBuffId       = 7644
-- 8倍威望
x300178_g_8ManaBuffId       = 7645
-- 8倍经验 X 10小时
x300172_g_10H8XP            = 7667
-- 8倍声望 X 10小时
x300172_g_10H8Credit        = 7666
-- 8倍威望 X 10小时
x300172_g_10H8Mana          = 7665
x300178_g_BuffTable         = {
                                { buffId = 7647, xp = 4,   credit = 0, mana = 0, coffs = { { xpCoff = 12.5, creCoff = 1, manaCoff = 1, minLevel = 40, maxLevel = 70 },
                                                                                             { xpCoff = 22.5, creCoff = 1, manaCoff = 1, minLevel = 70, maxLevel = 80 },
                                                                                             { xpCoff = 45, creCoff = 1, manaCoff = 1, minLevel = 80, maxLevel = 1000 },																							 
                                                                                           } }, 
                                { buffId = 7648, xp = 8,   credit = 0, mana = 0, coffs = { { xpCoff = 12.5, creCoff = 1, manaCoff = 1, minLevel = 40, maxLevel = 70 },
                                                                                             { xpCoff = 22.5, creCoff = 1, manaCoff = 1, minLevel = 70, maxLevel = 80 },
                                                                                             { xpCoff = 45, creCoff = 1, manaCoff = 1, minLevel = 80, maxLevel = 1000 },	
                                                                                           } }, 
                                { buffId = 7649, xp = 0,   credit = 4, mana = 0, coffs = { { xpCoff = 12.5, creCoff = 1, manaCoff = 1, minLevel = 40, maxLevel = 70 },
                                                                                             { xpCoff = 22.5, creCoff = 1, manaCoff = 1, minLevel = 70, maxLevel = 80 },
                                                                                             { xpCoff = 22.5, creCoff = 1, manaCoff = 1, minLevel = 80, maxLevel = 1000 },
                                                                                           } }, 
                                { buffId = 7650, xp = 0,   credit = 8, mana = 0, coffs = { { xpCoff = 12.5, creCoff = 1, manaCoff = 1, minLevel = 40, maxLevel = 70 },
                                                                                             { xpCoff = 22.5, creCoff = 1, manaCoff = 1, minLevel = 70, maxLevel = 80 },
                                                                                             { xpCoff = 22.5, creCoff = 1, manaCoff = 1, minLevel = 80, maxLevel = 1000 },
                                                                                           } }, 
                                { buffId = 7644, xp = 0,   credit = 0, mana = 4, coffs = { { xpCoff = 12.5, creCoff = 1, manaCoff = 1, minLevel = 40, maxLevel = 70 },
                                                                                             { xpCoff = 22.5, creCoff = 1, manaCoff = 1, minLevel = 70, maxLevel = 80 },
                                                                                             { xpCoff = 22.5, creCoff = 1, manaCoff = 1, minLevel = 80, maxLevel = 1000 },
                                                                                           } }, 
                                { buffId = 7645, xp = 0,   credit = 0, mana = 8, coffs = { { xpCoff = 12.5, creCoff = 1, manaCoff = 1, minLevel = 40, maxLevel = 70 },
                                                                                             { xpCoff = 22.5, creCoff = 1, manaCoff = 1, minLevel = 70, maxLevel = 80 },
                                                                                             { xpCoff = 22.5, creCoff = 1, manaCoff = 1, minLevel = 80, maxLevel = 1000 },
                                                                                           } }, 
                                { buffId = 7667, xp = 8,   credit = 0, mana = 0, coffs = { { xpCoff = 12.5, creCoff = 1, manaCoff = 1, minLevel = 40, maxLevel = 70 },
                                                                                             { xpCoff = 22.5, creCoff = 1, manaCoff = 1, minLevel = 70, maxLevel = 80 },
                                                                                             { xpCoff = 45, creCoff = 1, manaCoff = 1, minLevel = 80, maxLevel = 1000 },	
                                                                                           } }, 
                                { buffId = 7666, xp = 0,   credit = 8, mana = 0, coffs = { { xpCoff = 12.5, creCoff = 1, manaCoff = 1, minLevel = 40, maxLevel = 70 },
                                                                                             { xpCoff = 22.5, creCoff = 1, manaCoff = 1, minLevel = 70, maxLevel = 80 },
                                                                                             { xpCoff = 22.5, creCoff = 1, manaCoff = 1, minLevel = 80, maxLevel = 1000 },
                                                                                           } }, 
                                { buffId = 7665, xp = 0,   credit = 0, mana = 8, coffs = { { xpCoff = 12.5, creCoff = 1, manaCoff = 1, minLevel = 40, maxLevel = 70 },
                                                                                             { xpCoff = 22.5, creCoff = 1, manaCoff = 1, minLevel = 70, maxLevel = 80 },
                                                                                             { xpCoff = 22.5, creCoff = 1, manaCoff = 1, minLevel = 80, maxLevel = 1000 },
                                                                                           } }, 
                                { buffId = 7668, xp = 4,   credit = 0, mana = 0, coffs = { { xpCoff = 12.5, creCoff = 1, manaCoff = 1, minLevel = 40, maxLevel = 70 },
                                                                                             { xpCoff = 22.5, creCoff = 1, manaCoff = 1, minLevel = 70, maxLevel = 80 },
                                                                                             { xpCoff = 45, creCoff = 1, manaCoff = 1, minLevel = 80, maxLevel = 1000 },	
                                                                                           } }, 
                                { buffId = 7669, xp = 0,   credit = 4, mana = 0, coffs = { { xpCoff = 12.5, creCoff = 1, manaCoff = 1, minLevel = 40, maxLevel = 70 },
                                                                                             { xpCoff = 22.5, creCoff = 1, manaCoff = 1, minLevel = 70, maxLevel = 80 },
                                                                                             { xpCoff = 22.5, creCoff = 1, manaCoff = 1, minLevel = 80, maxLevel = 1000 },
                                                                                           } }, 
}
-- 现金或金卡余额不足
x300178_g_strNotEnoughMoney = "您身上的现银（银卡）不足，不能使用离线托管功能"
-- 离线托管费用
--x300178_g_Money             = 2000
-- 舞厅关闭时间（一天的第N分钟）
x300178_g_CloseTime         = 540
-- 舞厅开放时间（一天的第N分钟）
x300178_g_OpenTime          = 1380

x300178_g_AdditionalLevel   = 90

function x300178_ProcEnumEvent( sceneId, selfId, targetId, MissionId)
    -- 舞厅关闭前一分钟不显示“离线托管”选项
    local minute = GetMinOfDay()
    if minute >= x300178_g_OpenTime or minute < x300178_g_CloseTime - 1 then
        AddQuestNumText( sceneId, x300178_g_ScriptId, "【美丽会】离线托管", 3, 1)
    end
    -- local y,m,d = GetYearMonthDay()
    -- print( mod( y, 4).."*-*-*-*" )
    --CancelSpecificImpact( sceneId, selfId, x300178_g_BaseBuffId)
end


function x300178_ProcEventEntry( sceneId, selfId, targetId, idScript, idExt)
    --print( "********"..idExt)
    local level = GetLevel( sceneId, selfId)
    local xpAddition = 1
    if level >= x300178_g_AdditionalLevel then
        xpAddition = 1.3
    end
    local lvCoff = 12.5
    if level >= 70 and level < 80 then
        lvCoff = 22.5
    elseif level >= 80 then
        lvCoff = 45
    end
    local index = 1
    for i, item in x300178_g_BuffTable[ 1].coffs do
        if level >= item.minLevel and level < item.maxLevel then
            index = i
        end
    end
    -- 现在到舞厅关闭还有多长时间
    local currentTime = GetMinOfDay()
    local remain = x300178_g_CloseTime - currentTime
    if currentTime > x300178_g_CloseTime then
        remain = x300178_g_CloseTime + 1440 - currentTime
    end
    -- 转换为触发次数
    remain = remain * 6
    -- 根据玩家身上的Buff显示可以获得多少奖励
    local highXp = 0
    local highCredit = 0
    local baseBuff = 0
    BeginQuestEvent( sceneId)
        AddQuestText( sceneId, "#Y"..x300178_g_Name)
        AddQuestText( sceneId, "\t欢迎您使用离线托管服务， 在本次美丽会关闭前您可获得的奖励如下：#r" )
        for i, item in x300178_g_BuffTable do
            if IsHaveSpecificImpact( sceneId, selfId, item.buffId) == 1 then
                local amountTime = GetImpactContinuanceByDataIndex( sceneId, selfId, item.buffId)
                if amountTime > 0 then
                    local remainTime = amountTime - GetImpactContinuanceElapsed( sceneId, selfId, item.buffId)
                    local times = remainTime / 10000
                    -- 获得每次Timer触发可获得的奖励
                    local reward = item.xp * item.coffs[ index].xpCoff * level * xpAddition + item.credit + item.mana
                    local allTimes = 0
                    if reward > 0 then
                        if times > remain then
                            allTimes = remain
                        else
                            allTimes = times
                            baseBuff = remain - times
                        end
                        if item.xp ~= 0 then
                            AddQuestText( sceneId, format( "\t#Y经验：%d", reward * allTimes + baseBuff * level * lvCoff * xpAddition) )
                        end
                        if item.credit ~= 0 then
                            AddQuestText( sceneId, format( "\t#Y声望：%d", reward * allTimes + baseBuff) )
                        end
                        if item.mana ~= 0 then
                            AddQuestText( sceneId, format( "\t#Y威望：%d#r", reward * allTimes) )
                        end
                    end
                    if item.xp ~= 0 then
                        highXp = 1
                    end
                    if item.credit ~= 0 then
                        highCredit = 1
                    end
                end
            end
        end
        if highXp == 0 then
            local amountTime = GetImpactContinuanceByDataIndex( sceneId, selfId, x300178_g_BaseBuffId)
            if amountTime > 0 then
                local remainTime = amountTime - GetImpactContinuanceElapsed( sceneId, selfId, x300178_g_BaseBuffId)
                local times = remainTime / 10000
                local allTimes = 0
                if times > remain then
                    allTimes = remain
                else
                    allTimes = times
                end
                AddQuestText( sceneId, format( "\t#Y经验：%d#r", level * allTimes * lvCoff) )
            end
        end
        if highCredit == 0 then
            local amountTime = GetImpactContinuanceByDataIndex( sceneId, selfId, x300178_g_BaseBuffId)
            if amountTime > 0 then
                local remainTime = amountTime - GetImpactContinuanceElapsed( sceneId, selfId, x300178_g_BaseBuffId)
                local times = remainTime / 10000
                local allTimes = 0
                if times > remain then
                    allTimes = remain
                else
                    allTimes = times
                end
                AddQuestText( sceneId, format( "\t#Y声望：%d#r", allTimes) )
            end
        end
		local level = GetLevel(sceneId, selfId)
		local money = level*200
		local ding=0
		local liang=0
		local wen=0
		local level = GetLevel(sceneId, selfId)
		local money = floor( level*200)
		ding = floor( money / (1000*1000) )
		liang = floor( mod(money,1000*1000)/ 1000 )
		wen = mod(money,1000)
		local Readme = format("\t#G当您选择使用#R离线托管#G功能，您需要花费#R%d锭%d两%d文#W现银（银卡）", ding,liang,wen);
		AddQuestText( sceneId,Readme )
        AddQuestText( sceneId, "\t#G如果您选择确定，您将会马上离线，并且在您上线时会得到您#R离线时间内#G的收益，您需要现在离线托管吗？#r" )
		AddQuestText( sceneId, "\t#G小提示：您的离线时间最好大于您身上的跳舞状态时间，就可以获得最理想的收益。" )
    EndQuestEvent()
    DispatchQuestInfo( sceneId, selfId, targetId, x300178_g_ScriptId, -1)
end


function x300178_ProcMapPlayerNewConnectEnter( sceneId, selfId)
    if IsInitBecauseReconnect( sceneId, selfId) == 1 then
        if GetQuestData( sceneId, selfId, MD_WUTING_OFFLINE_FLAG[ 1], MD_WUTING_OFFLINE_FLAG[ 2], MD_WUTING_OFFLINE_FLAG[ 3] ) == 1 then
            -- 如果托管了并断线重连上来就立即给他踢下去
            KickPlayer( sceneId, selfId, 0)
        end
        return
    end

    local olDate = GetQuestData( sceneId, selfId, MD_WUTING_OFFLINE_DATE[ 1], MD_WUTING_OFFLINE_DATE[ 2], MD_WUTING_OFFLINE_DATE[ 3] )
    local olTime = GetQuestData( sceneId, selfId, MD_WUTING_OFFLINE_TIME[ 1], MD_WUTING_OFFLINE_TIME[ 2], MD_WUTING_OFFLINE_TIME[ 3] )

    local level = GetLevel( sceneId, selfId)
    local xpAddition = 1
    if level >= x300178_g_AdditionalLevel then
        xpAddition = 1.3
    end
    local lvCoff = 12.5
    if level >= 70 and level < 80 then
        lvCoff = 22.5
    elseif level >= 80 then
        lvCoff = 45
    end

    local index = 1
    for i, item in x300178_g_BuffTable[ 1].coffs do
        if level >= item.minLevel and level < item.maxLevel then
            index = i
        end
    end

    -- 计算离线时间
    local times = 3600
    local onDate = GetDayOfYear()
    local onTime = GetMinOfDay()
    if onDate == olDate then
        -- 同一天
        if onTime >= x300178_g_OpenTime then
            -- 上线时间在23点之后
            if olTime >= x300178_g_OpenTime then
                -- 离线时间在23点之后
                times = ( onTime - olTime) * 6
            else
                -- 离线时间在当天上午关闭之前
                times = ( onTime - x300178_g_OpenTime + x300178_g_CloseTime - olTime) * 6
            end
        else
            -- 上线时间在23点之前
            if onTime >= x300178_g_CloseTime then
                -- 上线时间在关闭之后
                times = ( x300178_g_CloseTime - olTime) * 6
            else
                -- 上线时间在关闭之前
                times = ( onTime - olTime) * 6
            end
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
            if onTime >= x300178_g_OpenTime then
                -- 上线时间在23点之后0点前
                if olTime >= x300178_g_OpenTime then
                    -- 离线时间在23点之后0点前
                    times = 600 - ( olTime - onTime)
                else
                    -- 离线时间在0点之后9点前
                    times = onTime - x300178_g_OpenTime + x300178_g_CloseTime - olTime
                end
            else
                -- 上线时间在23点之前
                if onTime >= x300178_g_CloseTime then
                    -- 9点到23点之间，美丽会关闭期间上线
                    times = x300178_g_CloseTime + 1440 - olTime
                else
                    -- 9点前上线
                    if olTime >= x300178_g_OpenTime then
                        -- 0点前离线
                        times = onTime + 1440 - olTime
                    else
                        -- 0点到9点离线(还要加上昨晚的一个小时)
                        times = onTime + x300178_g_CloseTime - olTime + 60
                    end
                end
            end
            times = times * 6
        end
    end

    -- 写日志
    local strLog = format( "WTL: Player %s who has offline management enter game with %d offline times. ", GetName( sceneId, selfId), times)
    WriteLog( 1, strLog)

    if times == 0 then
        -- 更新离线托管标记
        SetQuestData( sceneId, selfId, MD_WUTING_OFFLINE_FLAG[ 1], MD_WUTING_OFFLINE_FLAG[ 2], MD_WUTING_OFFLINE_FLAG[ 3], 0)

        return
    end

    -- 恢复活力
    --SetPlayerVigor( sceneId, selfId, GetPlayerMaxVigor( sceneId, selfId) )

    local highXp = 0
    local highCredit = 0
    local baseReward = 0
    local baseXP = 0
    local baseCredit = 0
    local xpAmount = 0
    local creditAmount = 0
    local manaAmount = 0
    local temp = GetImpactContinuanceByDataIndex( sceneId, selfId, x300178_g_BaseBuffId)
    local baseRemain = 0
    if temp > 0 then
        baseRemain = temp - GetImpactContinuanceElapsed( sceneId, selfId, x300178_g_BaseBuffId)
        baseRemain = baseRemain / 10000
    end
    for i, item in x300178_g_BuffTable do
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
                -- 清除基础奖励标记
                baseReward = 0
                if buffTimes > times then   -- Buff时间大于离线时间
                    -- 用离线时间算
                    finalReward = times * reward
                    -- 剩余Buff时间
                    remainBuff = ( buffTimes - times) * 10000
                else    -- 离线时间大于Buff时间
                    -- 用Buff时间计算
                    finalReward = buffTimes * reward
                    if baseRemain > buffTimes then
                        -- 高奖Buff消失后基础奖励Buff
                        if baseRemain > times then
                            baseReward = times - buffTimes
                        else
                            baseReward = baseRemain - buffTimes
                        end
                    end
                end
                if item.xp ~= 0 then
                    AddExp( sceneId, selfId, finalReward)
                    WriteLog( 1, format( "WTL: Add %d exp with buff %d. ", finalReward, item.buffId) )
                    highXp = 1
                    baseXP = baseReward * lvCoff * level * xpAddition
                    xpAmount = xpAmount + finalReward
                elseif item.credit ~= 0 then
                    SetShengWang( sceneId, selfId, GetShengWang( sceneId, selfId) + finalReward)
                    highCredit = 1
                    baseCredit = baseReward
                    creditAmount = creditAmount + finalReward
                elseif item.mana ~= 0 then
                    SetPlayerGoodBadValue( sceneId, selfId, GetPlayerGoodBadValue( sceneId, selfId) + finalReward)
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

    local amountTime = GetImpactContinuanceByDataIndex( sceneId, selfId, x300178_g_BaseBuffId)
    local remainTime = amountTime - GetImpactContinuanceElapsed( sceneId, selfId, x300178_g_BaseBuffId)
    local buffTimes = remainTime / 10000
    if times >= buffTimes then
        CancelSpecificImpact( sceneId, selfId, x300178_g_BaseBuffId)
    else
        SetImpactContinuanceByDataIndex( sceneId, selfId, x300178_g_BaseBuffId, ( buffTimes - times) * 10000)
        ResetImpactContinuanceElapsed( sceneId, selfId, x300178_g_BaseBuffId)
        RefreshImpactByDataIndex( sceneId, selfId, x300178_g_BaseBuffId)
    end
    -- 基础经验奖励
    if highXp == 0 then
        if amountTime > 0 then
            local finalReward = 0
            if buffTimes > times then
                finalReward = times * lvCoff * level * xpAddition
            else
                finalReward = buffTimes * lvCoff * level * xpAddition
            end
            AddExp( sceneId, selfId, finalReward)
            xpAmount = xpAmount + finalReward
        end
    end
    if baseXP > 0 then
        AddExp( sceneId, selfId, baseXP)
        xpAmount = xpAmount + baseXP
    end
    -- 基础声望奖励
    if highCredit == 0 then
        if amountTime > 0 then
            local finalReward = 0
            if buffTimes > times then
                finalReward = times
            else
                finalReward = buffTimes
            end
            SetShengWang( sceneId, selfId, GetShengWang( sceneId, selfId) + finalReward)
            creditAmount = creditAmount + finalReward
        end
    end
    if baseCredit > 0 then
        SetShengWang( sceneId, selfId, GetShengWang( sceneId, selfId) + baseCredit)
        creditAmount = creditAmount + baseCredit
    end

    -- 显示奖励更新
    local strReward = "您在离线托管时间内获得的奖励如下：#G#r"
    local strDialog = "\t#G感谢您使用本店的离线托管服务，在您离线的这段时间您总共获得的奖励如下：#r #r"
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
    SendNormalMail( sceneId, selfId, GetName( sceneId, selfId), strDialog)
    LuaScenceM2Player( sceneId, selfId, strReward, GetName( sceneId, selfId), 1, 1)

    -- 更新离线托管标记
    SetQuestData( sceneId, selfId, MD_WUTING_OFFLINE_FLAG[ 1], MD_WUTING_OFFLINE_FLAG[ 2], MD_WUTING_OFFLINE_FLAG[ 3], 0)
end


function x300178_ProcAcceptCheck( sceneId, selfId, targetId)
    -- print( "*-*-*-*-*-*" )
    -- 舞厅关闭前1分钟不允许离线托管
    local minute = GetMinOfDay()
    if minute < x300178_g_CloseTime and minute >= x300178_g_CloseTime - 1 then
        Msg2Player( sceneId, selfId, "美丽会关闭前1分钟不能进行离线托管", 8, 3)
        return
    end

    -- 扣钱
	local level = GetLevel(sceneId, selfId)
	local money = level*200
    if GetGoldMode( sceneId, selfId ) == 1 then
        if CostMoney( sceneId, selfId, 0, money,306) ~= 1 then
            if CostMoney(sceneId, selfId, 1, money,306) ~= 1 then
                Msg2Player( sceneId, selfId, x300178_g_strNotEnoughMoney.."。", 8, 2)
                Msg2Player( sceneId, selfId, x300178_g_strNotEnoughMoney, 8, 3)
                return
            end
        end
    else
        if CostMoney( sceneId, selfId, 1, money,306) ~= 1 then
            if CostMoney(sceneId, selfId, 0, money,306) ~= 1 then
                Msg2Player( sceneId, selfId, x300178_g_strNotEnoughMoney.."。", 8, 2)
                Msg2Player( sceneId, selfId, x300178_g_strNotEnoughMoney, 8, 3)
                return
            end
        end
    end

    -- 写日志
    local strLog = format( "WTL: Player %s use offline management with sw(%d), ww(%d), xp=", GetName( sceneId, selfId), GetShengWang( sceneId, selfId), GetPlayerGoodBadValue( sceneId, selfId) )
    strLog = strLog..GetExp( sceneId, selfId)
    WriteLog( 1, strLog)

    for i, item in x300178_g_BuffTable do
        if IsHaveSpecificImpact( sceneId, selfId, item.buffId) == 1 then
            local amountTime = GetImpactContinuanceByDataIndex( sceneId, selfId, item.buffId)
            if amountTime > 0 then
                local remainTime = amountTime - GetImpactContinuanceElapsed( sceneId, selfId, item.buffId)
                strLog = format( "WTL: With Buff %d remain buff time %d second. ", item.buffId, floor( remainTime / 1000) )
                WriteLog( 1, strLog)
            end
        end
    end
    if IsHaveSpecificImpact( sceneId, selfId, x300178_g_BaseBuffId) == 1 then
        local amountTime = GetImpactContinuanceByDataIndex( sceneId, selfId, x300178_g_BaseBuffId)
        if amountTime > 0 then
            local remainTime = amountTime - GetImpactContinuanceElapsed( sceneId, selfId, x300178_g_BaseBuffId)
            strLog = format( "WTL: With Base Buff remain buff time %d second. ", floor( remainTime / 1000) )
            WriteLog( 1, strLog)
        end
    end

    -- 记录日期
    SetQuestData( sceneId, selfId, MD_WUTING_OFFLINE_DATE[ 1], MD_WUTING_OFFLINE_DATE[ 2], MD_WUTING_OFFLINE_DATE[ 3], GetDayOfYear() )
    -- 记录时间
    SetQuestData( sceneId, selfId, MD_WUTING_OFFLINE_TIME[ 1], MD_WUTING_OFFLINE_TIME[ 2], MD_WUTING_OFFLINE_TIME[ 3], GetMinOfDay() )
    -- 设置离线托管标记
    SetQuestData( sceneId, selfId, MD_WUTING_OFFLINE_FLAG[ 1], MD_WUTING_OFFLINE_FLAG[ 2], MD_WUTING_OFFLINE_FLAG[ 3], 1)
    -- 把玩家返回登录界面
    KickPlayer( sceneId, selfId, 1)
    -- 设置T人安全时间
    SetKickTime( sceneId, selfId, 11000)
end


