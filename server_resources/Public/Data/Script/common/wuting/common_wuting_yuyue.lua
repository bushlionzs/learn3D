x300179_g_ScriptId 			= 300179
x300179_g_Name              = "��������������"
-- ����Buff
x300179_g_BaseBuffId        = 7646
x300179_g_BuffTable         = {
                                { buffId = 7647, xp = 4,   credit = 0, mana = 0, coffs = { { xpCoff = 12.5, creCoff = 1, manaCoff = 1, minLevel = 40, maxLevel = 70 },
                                                                                             { xpCoff = 22.5, creCoff = 1, manaCoff = 1, minLevel = 70, maxLevel = 80 },
                                                                                             { xpCoff = 45, creCoff = 1, manaCoff = 1, minLevel = 80, maxLevel = 1000 },
                                                                                           }, name = "����" }, 
                                { buffId = 7648, xp = 8,   credit = 0, mana = 0, coffs = { { xpCoff = 12.5, creCoff = 1, manaCoff = 1, minLevel = 40, maxLevel = 70 },
                                                                                             { xpCoff = 22.5, creCoff = 1, manaCoff = 1, minLevel = 70, maxLevel = 80 },
                                                                                             { xpCoff = 45, creCoff = 1, manaCoff = 1, minLevel = 80, maxLevel = 1000 },
                                                                                           }, name = "����" }, 
                                { buffId = 7649, xp = 0,   credit = 4, mana = 0, coffs = { { xpCoff = 12.5, creCoff = 1, manaCoff = 1, minLevel = 40, maxLevel = 70 },
                                                                                             { xpCoff = 22.5, creCoff = 1, manaCoff = 1, minLevel = 70, maxLevel = 80 },
                                                                                             { xpCoff = 22.5, creCoff = 1, manaCoff = 1, minLevel = 80, maxLevel = 1000 },
                                                                                           }, name = "����" }, 
                                { buffId = 7650, xp = 0,   credit = 8, mana = 0, coffs = { { xpCoff = 12.5, creCoff = 1, manaCoff = 1, minLevel = 40, maxLevel = 70 },
                                                                                             { xpCoff = 22.5, creCoff = 1, manaCoff = 1, minLevel = 70, maxLevel = 80 },
                                                                                             { xpCoff = 22.5, creCoff = 1, manaCoff = 1, minLevel = 80, maxLevel = 1000 },
                                                                                           }, name = "����" }, 
                                { buffId = 7645, xp = 0,   credit = 0, mana = 8, coffs = { { xpCoff = 12.5, creCoff = 1, manaCoff = 1, minLevel = 40, maxLevel = 70 },
                                                                                             { xpCoff = 22.5, creCoff = 1, manaCoff = 1, minLevel = 70, maxLevel = 80 },
                                                                                             { xpCoff = 22.5, creCoff = 1, manaCoff = 1, minLevel = 80, maxLevel = 1000 },
                                                                                           }, name = "����" }, 
                                { buffId = 7667, xp = 8,   credit = 0, mana = 0, coffs = { { xpCoff = 12.5, creCoff = 1, manaCoff = 1, minLevel = 40, maxLevel = 70 },
                                                                                             { xpCoff = 22.5, creCoff = 1, manaCoff = 1, minLevel = 70, maxLevel = 80 },
                                                                                             { xpCoff = 45, creCoff = 1, manaCoff = 1, minLevel = 80, maxLevel = 1000 },
                                                                                           }, name = "����" }, 
                                { buffId = 7666, xp = 0,   credit = 8, mana = 0, coffs = { { xpCoff = 12.5, creCoff = 1, manaCoff = 1, minLevel = 40, maxLevel = 70 },
                                                                                             { xpCoff = 22.5, creCoff = 1, manaCoff = 1, minLevel = 70, maxLevel = 80 },
                                                                                             { xpCoff = 22.5, creCoff = 1, manaCoff = 1, minLevel = 80, maxLevel = 1000 },
                                                                                           }, name = "����" }, 
                                { buffId = 7665, xp = 0,   credit = 0, mana = 8, coffs = { { xpCoff = 12.5, creCoff = 1, manaCoff = 1, minLevel = 40, maxLevel = 70 },
                                                                                             { xpCoff = 22.5, creCoff = 1, manaCoff = 1, minLevel = 70, maxLevel = 80 },
                                                                                             { xpCoff = 22.5, creCoff = 1, manaCoff = 1, minLevel = 80, maxLevel = 1000 },
                                                                                           }, name = "����" }, 
                                { buffId = 7668, xp = 4,   credit = 0, mana = 0, coffs = { { xpCoff = 12.5, creCoff = 1, manaCoff = 1, minLevel = 40, maxLevel = 70 },
                                                                                             { xpCoff = 22.5, creCoff = 1, manaCoff = 1, minLevel = 70, maxLevel = 80 },
                                                                                             { xpCoff = 45, creCoff = 1, manaCoff = 1, minLevel = 80, maxLevel = 1000 },
                                                                                           }, name = "����" }, 
                                { buffId = 7669, xp = 0,   credit = 4, mana = 0, coffs = { { xpCoff = 12.5, creCoff = 1, manaCoff = 1, minLevel = 40, maxLevel = 70 },
                                                                                             { xpCoff = 22.5, creCoff = 1, manaCoff = 1, minLevel = 70, maxLevel = 80 },
                                                                                             { xpCoff = 22.5, creCoff = 1, manaCoff = 1, minLevel = 80, maxLevel = 1000 },
                                                                                           }, name = "����" }, 
}
-- �ֽ�������
x300179_g_strNotEnoughMoney = "�����ϵ����������������㣬����ʹ��ԤԼ�йܹ���"
-- ԤԼ�йܷ���
x300179_g_Money             = 2000
-- �����ر�ʱ�䣨һ��ĵ�N���ӣ�
x300179_g_CloseTime         = 540
-- ��������ʱ�䣨һ��ĵ�N���ӣ�
x300179_g_OpenTime          = 1380

x300179_g_AdditionalLevel   = 90

function x300179_ProcEnumEvent( sceneId, selfId, targetId, MissionId)
    -- �ȼ�����
    if GetLevel( sceneId, selfId) < 40 then
        return
    end
    local minute = GetMinOfDay()
    if minute >= x300179_g_CloseTime and minute < x300179_g_OpenTime then
        AddQuestNumText( sceneId, x300179_g_ScriptId, "�������᡿ԤԼ�й�", 3)
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

    -- ������������û�йһ�Buff������Ҫ��һ�����ܼ���
    for i, item in x300179_g_BuffTable do
        if IsHaveSpecificImpact( sceneId, selfId, item.buffId) == 1 then
            haveBuff = 1
            break
        end
    end
    if haveBuff == 0 then
        BeginQuestEvent( sceneId)
            AddQuestText( sceneId, "#Y"..x300179_g_Name)
            AddQuestText( sceneId, "\t�ܱ�Ǹ�������ϱ����оƻ�ѩ�Ѳ���ԤԼ�йܡ�" )
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
    AddQuestText( sceneId, "\t��ӭ��ʹ��ԤԼ�йܷ��񣬴ӱ��������Ὺʼ���ر���10��Сʱ֮�����ɻ�õĽ������£�#r" )
    for i, item in x300179_g_BuffTable do
        if IsHaveSpecificImpact( sceneId, selfId, item.buffId) == 1 then
            local amountTime = GetImpactContinuanceByDataIndex( sceneId, selfId, item.buffId)
            if amountTime > 0 then
                local remainTime = amountTime - GetImpactContinuanceElapsed( sceneId, selfId, item.buffId)
                times = remainTime / 10000
                local reward = item.xp * item.coffs[ index].xpCoff * level * xpAddition + item.credit + item.mana
                if reward > 0 then
                    AddQuestText( sceneId, format( "\t#Y%s��%d#r", item.name, reward * times) )
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
	local Readme = format("\t#G����ѡ��ʹ��#RԤԼ�й�#G���ܣ�����Ҫ����#R%d��%d��%d��#W������������", ding,liang,wen);
	AddQuestText( sceneId,Readme )
    AddQuestText( sceneId, "\t#G�������Ὺ��ǰ�������ѡ��ȷ����������ԤԼ��������������棬���������ߡ�����ԤԼ����#R����23��00��ʼ��Ч#G��������#R����9��00ԤԼ����#G���ڴ��ڼ䣬���ɻ�����10��Сʱ�����棬������������23��00���ٴ����߲��ܻ�����棬��������ϵ����轱��״̬ʱ������������ѿ���ʱ�䣬���ǽ����ʣ������轱��ʱ�䷵������������Ҫ����ԤԼ�й���#r" )
	AddQuestText( sceneId, "\t#GС��ʾ�������ߺ�������ʱ�������#R���������Ὺ��#G�󣬲��ܻ�ý������������ߺ��ٴ�����ʱ�����#R����9��00��#G���Ϳ��Ի������������档" )
    EndQuestEvent()
    DispatchQuestInfo( sceneId, selfId, targetId, x300179_g_ScriptId, -1)
end


function x300179_ProcMapPlayerNewConnectEnter( sceneId, selfId)
    if IsInitBecauseReconnect( sceneId, selfId) == 1 then
        if GetQuestData( sceneId, selfId, MD_WUTING_PRECONTRACT_FLAG[ 1], MD_WUTING_PRECONTRACT_FLAG[ 2], MD_WUTING_PRECONTRACT_FLAG[ 3] ) == 1 then
            -- ���ԤԼ�˲���������������������������ȥ
            KickPlayer( sceneId, selfId, 0)
        end
        return
    end

    if GetQuestData( sceneId, selfId, MD_WUTING_PRECONTRACT_FLAG[ 1], MD_WUTING_PRECONTRACT_FLAG[ 2], MD_WUTING_PRECONTRACT_FLAG[ 3] ) == 0 then
        return
    end

    -- �ָ�����
    --SetPlayerVigor( sceneId, selfId, GetPlayerMaxVigor( sceneId, selfId) )

    -- �õ�ԤԼԤԼʱ�������
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

    -- ����ԤԼʱ��
    local times = 3600
    local onDate = GetDayOfYear()
    local onTime = GetMinOfDay()
    if onDate == olDate then
        -- ͬһ��
        if onTime >= x300179_g_OpenTime then
            -- ����ʱ����23��֮��
            times = ( onTime - x300179_g_OpenTime) * 6
        else
            -- ����ʱ����23��֮ǰ
            times = 0
        end
    else
        -- ����
        local days = onDate - olDate
        if olDate > onDate then
            -- ����
            local y,m,d = GetYearMonthDay()
            if mod( y, 4) == 0 then
                -- ����
                days = onDate + 366 - olDate
            else
                days = onDate + 365 - olDate
            end
        end
        if days == 1 and onTime < olTime then
            -- ���첢�Ҳ���24Сʱ
            if onTime < x300179_g_CloseTime then
                -- ����ʱ����9��֮ǰ
                times = 60 + onTime
                times = times * 6
            end
        end
    end

    -- д��־
    local strLog = format( "WTL: Player %s who has precontract management enter game with %d offline times. ", GetName( sceneId, selfId), times)
    WriteLog( 1, strLog)

    if times == 0 then
        -- ����ԤԼ�йܱ��
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
                -- ���ÿ��Timer�����ɻ�õĽ���
                local reward = item.xp * item.coffs[ index].xpCoff * level * xpAddition + item.credit + item.mana
                local finalReward = 0
                local remainBuff = 0
                if buffTimes > times then   -- Buffʱ���������ʱ��
                    -- ������ʱ����
                    finalReward = times * reward
                    -- ʣ��Buffʱ��
                    remainBuff = ( buffTimes - times) * 10000
                else    -- ����ʱ�����Buffʱ��
                    -- ��Buffʱ�����
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
                -- ��ʣ��Buff�������
                SetImpactContinuanceByDataIndex( sceneId, selfId, item.buffId, remainBuff)
                WriteLog( 1, format( "WTL: Refresh Buff(id:%d) time is %d ms. ", item.buffId, remainBuff) )
                ResetImpactContinuanceElapsed( sceneId, selfId, item.buffId)
                RefreshImpactByDataIndex( sceneId, selfId, item.buffId)
            end
        end
    end

    -- ��ʾ��������
    local strReward = "����ԤԼ�й�ʱ���ڻ�õĽ������£�#G#r"
    local strDialog = "\t#G��л��ʹ�ñ����ԤԼ�йܷ�������ԤԼ�����ʱ�����ܹ���õĽ������£�#r #r"
    if xpAmount > 0 then
        strReward = strReward..format( "���飺%d��#r", xpAmount)
        strDialog = strDialog..format( "���飺%d��#r #r", xpAmount)
    end
    if creditAmount > 0 then
        strReward = strReward..format( "������%d��#r", creditAmount)
        strDialog = strDialog..format( "������%d��#r #r", creditAmount)
    end
    if manaAmount > 0 then
        strReward = strReward..format( "������%d��#r", manaAmount)
        strDialog = strDialog..format( "������%d��#r #r", manaAmount)
    end
    BeginQuestEvent( sceneId)
        AddQuestText( sceneId, "#Y".."�������᡿ԤԼ�й�" )
        AddQuestText( sceneId, strDialog)
    EndQuestEvent( sceneId)
    DispatchQuestEventList( sceneId, selfId, 0)
    LuaScenceM2Player( sceneId, selfId, strReward, GetName( sceneId, selfId), 1, 1)

    -- ����ԤԼ�йܱ��
    SetQuestData( sceneId, selfId, MD_WUTING_PRECONTRACT_FLAG[ 1], MD_WUTING_PRECONTRACT_FLAG[ 2], MD_WUTING_PRECONTRACT_FLAG[ 3], 0)
end


function x300179_ProcAcceptCheck( sceneId, selfId, targetId)
    local minute = GetMinOfDay()
    if minute < x300179_g_CloseTime or minute >= x300179_g_OpenTime then
        Msg2Player( sceneId, selfId, "�ܱ�Ǹ�������Ὺ���ڼ����ǲ�����ԤԼ�й�", 8, 3)
        return
    end

    -- ��Ǯ
	local level = GetLevel(sceneId, selfId)
	local money = level*200
    if GetGoldMode( sceneId, selfId ) == 1 then
        if CostMoney( sceneId, selfId, 0, money,306) ~= 1 then
            if CostMoney(sceneId, selfId, 1, money,306) ~= 1 then
                Msg2Player( sceneId, selfId, x300179_g_strNotEnoughMoney.."��", 8, 2)
                Msg2Player( sceneId, selfId, x300179_g_strNotEnoughMoney, 8, 3)
                return
            end
        end
    else
        if CostMoney( sceneId, selfId, 1, money,306) ~= 1 then
            if CostMoney(sceneId, selfId, 0, money,306) ~= 1 then
                Msg2Player( sceneId, selfId, x300179_g_strNotEnoughMoney.."��", 8, 2)
                Msg2Player( sceneId, selfId, x300179_g_strNotEnoughMoney, 8, 3)
                return
            end
        end
    end

    -- д��־
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

    -- ��¼����
    SetQuestData( sceneId, selfId, MD_WUTING_PRECONTRACT_DATE[ 1], MD_WUTING_PRECONTRACT_DATE[ 2], MD_WUTING_PRECONTRACT_DATE[ 3], GetDayOfYear() )
    -- ��¼ʱ��
    SetQuestData( sceneId, selfId, MD_WUTING_PRECONTRACT_TIME[ 1], MD_WUTING_PRECONTRACT_TIME[ 2], MD_WUTING_PRECONTRACT_TIME[ 3], GetMinOfDay() )
    -- ����ԤԼ�йܱ��
    SetQuestData( sceneId, selfId, MD_WUTING_PRECONTRACT_FLAG[ 1], MD_WUTING_PRECONTRACT_FLAG[ 2], MD_WUTING_PRECONTRACT_FLAG[ 3], 1)
    -- ����ҷ��ص�¼����
    KickPlayer( sceneId, selfId, 1)
    -- ����T�˰�ȫʱ��
    SetKickTime( sceneId, selfId, 11000)
   
end


