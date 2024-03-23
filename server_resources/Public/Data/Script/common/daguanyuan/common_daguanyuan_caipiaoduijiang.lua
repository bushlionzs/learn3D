-- 脚本号
x310360_g_ScriptId              = 310360
-- item id
x310360_g_Item                  = 12035040

function x310360_ProcEnumEvent( sceneId, selfId, NPCId, MissionId)
    AddQuestNumText( sceneId, x310360_g_ScriptId, "领取乐透奖励", 3, 1)
end

function x310360_ProcEventEntry( sceneId, selfId, NPCId, idScript, idExt)
    local wday, week = GetWeek()
    if wday ~= 0 and wday ~= 6 then
        Msg2Player( sceneId, selfId, "周六、周日才能领奖", 8, 3)
        return
    end

    if idExt == 1 then
        -- get own number of item
        local bagIndex = FindFirstBagIndexOfItem( sceneId, selfId, x310360_g_Item)
        if bagIndex < 0 then
            Msg2Player( sceneId, selfId, format( "没有@item_%d#cffcc00不能领奖", x310360_g_Item), 8, 3)
            return
        end

        local day = GetItemParam( sceneId, selfId, bagIndex, 4, 2)
        if day ~= GetDayOfYear() then
            Msg2Player( sceneId, selfId, "很遗憾，这张幸运卷的领奖日期已过", 8, 3)
            return
        end
        local a = GetItemParam( sceneId, selfId, bagIndex, 8, 1)
        local b = GetItemParam( sceneId, selfId, bagIndex, 10, 1)
        local r = a * 80 + b
        if r == GetCountryParam( sceneId, 1, CD_DAGUANYUAN_CAIPIAO1) or
                r == GetCountryParam( sceneId, 2, CD_DAGUANYUAN_CAIPIAO1) or
                r == GetCountryParam( sceneId, 3, CD_DAGUANYUAN_CAIPIAO1) or
                r == GetCountryParam( sceneId, 0, CD_DAGUANYUAN_CAIPIAO2) or
                r == GetCountryParam( sceneId, 1, CD_DAGUANYUAN_CAIPIAO2) or
                r == GetCountryParam( sceneId, 2, CD_DAGUANYUAN_CAIPIAO2) or
                r == GetCountryParam( sceneId, 3, CD_DAGUANYUAN_CAIPIAO2) then
            BeginQuestEvent( sceneId)
                AddQuestText( sceneId, "#Y乐透彩票" )
                AddQuestText( sceneId, "#Y恭喜您获得本日乐透彩票大奖#W，是否领取奖励？" )
                AddQuestMoneyBonus1( sceneId, GetCountryParam( sceneId, 0, CD_DAGUANYUAN_CAIPIAO1) * 1000)
            EndQuestEvent()
            DispatchQuestInfo( sceneId, selfId, NPCId, x310360_g_ScriptId, -1)
        else
            Msg2Player( sceneId, selfId, "很遗憾，你的幸运卷号码没有中奖", 8, 3)
            return
        end
    end
end

function x310360_ProcAcceptCheck( sceneId, selfId, NPCId)
    local bagIndex = FindFirstBagIndexOfItem( sceneId, selfId, x310360_g_Item)
    if bagIndex < 0 then
        Msg2Player( sceneId, selfId, format( "没有@item_%d#cffcc00不能领奖", x310360_g_Item), 8, 3)
        return 0
    end

    local day = GetItemParam( sceneId, selfId, bagIndex, 4, 2)
    if day ~= GetDayOfYear() then
        Msg2Player( sceneId, selfId, "很遗憾，这张幸运卷的领奖日期已过", 8, 3)
        return 0
    end

    DelItem( sceneId, selfId, x310360_g_Item, 1)
    GamePlayScriptLog(sceneId, selfId, 1652)
    -- 给奖励
    local reward = GetCountryParam( sceneId, 0, CD_DAGUANYUAN_CAIPIAO1) * 1000
    AddMoney( sceneId, selfId, 1, reward)
    Msg2Player( sceneId, selfId, format( "恭喜您获得本日乐透彩票大奖，获得奖金#R#{_MONEY%d}#cffcc00银卡。", reward), 8, 2)
    Msg2Player( sceneId, selfId, format( "恭喜您获得本日乐透彩票大奖，获得奖金#R#{_MONEY%d}#cffcc00银卡", reward), 8, 3)

    return 1
end

function x310360_ProcAccept( sceneId, selfId, NPCId)
end
