-- 圣诞上线送礼

x350008_g_ScriptId 					= 350008
-- 物品列表
x350008_g_ItemTable                 = {
                                        { { 12030019, 1, 1}, { 12031033, 1, 1}, { 12031034, 1, 1}, { 11010015, 1, 1}, { 12030066, 1, 2}, },
                                        { { 12030067, 1, 1}, { 12041201, 1, 1}, { 12041106, 1, 1}, { 11010015, 1, 1}, { 12031033, 1, 1}, { 12031034, 1, 1} },
                                        { { 12030067, 1, 1}, { 12041201, 1, 1}, { 12041106, 1, 1}, { 11010017, 1, 1}, { 12031033, 1, 1}, { 12031034, 1, 1} },
                                        { { 12030019, 1, 1}, { 12041106, 1, 1}, { 11010015, 1, 1}, { 12030066, 1, 2}, },
}
-- 时间段、礼品配置表
x350008_g_GiftTable                 = {
                                        { tstart = 720,  tend = 730,  }, 
                                        { tstart = 900,  tend = 910,  }, 
                                        { tstart = 1080, tend = 1090,  }, 
                                        { tstart = 1260, tend = 1270,  }, 
}
-- 圣诞骑乘ID
x350008_g_ChristmasPet              = 12050247
-- 圣诞套装10300141
x350008_g_ChristmasItem             = 10300141

--**********************************
--点击NPC
--**********************************
function x350008_ProcEnumEvent( sceneId, selfId, targetId, MissionId)
    if GetLevel( sceneId, selfId) < 30 then
        return
    end

    -- 本活动仅在指定时间开放
    local day = GetDayOfYear()
    local y, m, d = GetYearMonthDay()
    if mod( y, 4) == 0 then
        day = day - 1
    end
    if day > 356 or day < 350 then
        return
    end

    AddQuestNumText( sceneId, x350008_g_ScriptId, "圣诞上线送礼", 3)
end

--**********************************
--执行默认事件
--**********************************
function x350008_ProcEventEntry( sceneId, selfId, targetId, state, btnindex)
    local curTime = GetMinOfDay()
    local index = 0

    local day = GetDayOfYear()
    if day ~= GetQuestData( sceneId, selfId, MD_GETGIFT_DAY[ 1], MD_GETGIFT_DAY[ 2], MD_GETGIFT_DAY[ 3] ) then
        SetQuestData( sceneId, selfId, MD_GETGIFT1[ 1], MD_GETGIFT1[ 2], MD_GETGIFT1[ 3], 0)
        SetQuestData( sceneId, selfId, MD_GETGIFT2[ 1], MD_GETGIFT2[ 2], MD_GETGIFT2[ 3], 0)
        SetQuestData( sceneId, selfId, MD_GETGIFT3[ 1], MD_GETGIFT3[ 2], MD_GETGIFT3[ 3], 0)
        SetQuestData( sceneId, selfId, MD_GETGIFT4[ 1], MD_GETGIFT4[ 2], MD_GETGIFT4[ 3], 0)
        SetQuestData( sceneId, selfId, MD_GETGIFT_DAY[ 1], MD_GETGIFT_DAY[ 2], MD_GETGIFT_DAY[ 3], day)
    end

    for i, iter in x350008_g_GiftTable do
        if curTime >= iter.tstart and curTime < iter.tend then
            index = i
            break
        end
    end

    if index == 0 then
        BeginQuestEvent( sceneId)
            AddQuestText( sceneId, "#Y圣诞上线送礼" )
            AddQuestText( sceneId, "\n\t现在还不是领取时间，无法领取。#r" )
            AddQuestText( sceneId, "\t从#G12月17日起至12月23日#W，每天的#G12：00—12：10、15：00—15：10、18：00—18：10和21：00—21：10，#W各位玩家可以在这里领取圣诞礼物。\n\t#G许愿种子#W和#G祈福种子#W就包含在这些圣诞礼物中，你可以使用许愿种子或祈福种子去圣诞树处许愿祈福。" )
        EndQuestEvent()
        DispatchQuestEventList( sceneId, selfId, targetId)
        return
    end

    BeginQuestEvent( sceneId)
        AddQuestText( sceneId, "#Y圣诞上线送礼" )
        AddQuestText( sceneId, "\n\t您是否要领取这个时段的圣诞礼品？#r" )
        AddQuestText( sceneId, "\t从#G12月17日起至12月23日#W，每天的#G12：00—12：10、15：00—15：10、18：00—18：10和21：00—21：10，#W各位玩家可以在这里领取圣诞礼物。\n\t#G许愿种子#W和#G祈福种子#W就包含在这些圣诞礼物中，你可以使用许愿种子或祈福种子去圣诞树处许愿祈福。" )
        SetPlayerRuntimeData( sceneId, selfId, RD_COLLECT_HORSE, index)
    EndQuestEvent()
    DispatchQuestInfo( sceneId, selfId, targetId, x350008_g_ScriptId, -1)
end

--**********************************
--检测
--**********************************
function x350008_ProcAcceptCheck( sceneId, selfId, targetId)
    local curTime = GetMinOfDay()
    local index = 0
    for i, iter in x350008_g_GiftTable do
        if curTime >= iter.tstart and curTime < iter.tend then
            index = i
            break
        end
    end
    if index == 0 then
        BeginQuestEvent( sceneId)
            AddQuestText( sceneId, "#Y圣诞上线送礼" )
            AddQuestText( sceneId, "\t现在还不是领取时间，无法领取。#r" )
            AddQuestText( sceneId, "\t从#G12月22日起至1月4日#W，每天的#G12：00—12：10、15：00—15：10、18：00—18：10和21：00—21：10，#W各位玩家可以在这里领取圣诞礼物。\n\t#G许愿种子#W和#G祈福种子#W就包含在这些圣诞礼物中，你可以使用许愿种子或祈福种子去圣诞树处许愿祈福。" )
        EndQuestEvent()
        DispatchQuestEventList( sceneId, selfId, targetId)
        return
    end

    local index = GetPlayerRuntimeData( sceneId, selfId, RD_COLLECT_HORSE)
    if index == 1 then
        if GetQuestData( sceneId, selfId, MD_GETGIFT1[ 1], MD_GETGIFT1[ 2], MD_GETGIFT1[ 3] ) == 1 then
            Msg2Player( sceneId, selfId, "这个时间的奖品你已经领取了", 8, 3)
            return
        else
            SetQuestData( sceneId, selfId, MD_GETGIFT1[ 1], MD_GETGIFT1[ 2], MD_GETGIFT1[ 3], 1)
        end
    elseif index == 2 then
        if GetQuestData( sceneId, selfId, MD_GETGIFT2[ 1], MD_GETGIFT2[ 2], MD_GETGIFT2[ 3] ) == 1 then
            Msg2Player( sceneId, selfId, "这个时间的奖品你已经领取了", 8, 3)
            return
        else
            SetQuestData( sceneId, selfId, MD_GETGIFT2[ 1], MD_GETGIFT2[ 2], MD_GETGIFT2[ 3], 1)
        end
    elseif index == 3 then
        if GetQuestData( sceneId, selfId, MD_GETGIFT3[ 1], MD_GETGIFT3[ 2], MD_GETGIFT3[ 3] ) == 1 then
            Msg2Player( sceneId, selfId, "这个时间的奖品你已经领取了", 8, 3)
            return
        else
            SetQuestData( sceneId, selfId, MD_GETGIFT3[ 1], MD_GETGIFT3[ 2], MD_GETGIFT3[ 3], 1)
        end
    elseif index == 4 then
        if GetQuestData( sceneId, selfId, MD_GETGIFT4[ 1], MD_GETGIFT4[ 2], MD_GETGIFT4[ 3] ) == 1 then
            Msg2Player( sceneId, selfId, "这个时间的奖品你已经领取了", 8, 3)
            return
        else
            SetQuestData( sceneId, selfId, MD_GETGIFT4[ 1], MD_GETGIFT4[ 2], MD_GETGIFT4[ 3], 1)
        end
    end

    for i, iter in x350008_g_ItemTable[ index] do
        BeginAddItem( sceneId)
        AddItem( sceneId, iter[ 1], random( iter[ 2], iter[ 3] ) )
        if EndAddItem( sceneId, selfId) > 0 then
            AddItemListToPlayer( sceneId, selfId)
            Msg2Player( sceneId, selfId, format( "你获得了@item_%d#cffcc00。", iter[ 1] ), 8, 2)
            Msg2Player( sceneId, selfId, format( "获得圣诞礼品@item_%d", iter[ 1] ), 8, 3)
        else
            Msg2Player( sceneId, selfId, "无法获得物品，请整理道具栏", 8, 3)
        end
    end

    if index == 3 and random( 1, 100) == 50 then
        BeginAddItem( sceneId)
        AddItem( sceneId, x350008_g_ChristmasPet, 1)
        if EndAddItem( sceneId, selfId) > 0 then
            AddItemListToPlayer( sceneId, selfId)
            Msg2Player( sceneId, selfId, format( "你获得了@item_%d#cffcc00。", x350008_g_ChristmasPet), 8, 2)
            Msg2Player( sceneId, selfId, format( "获得圣诞礼品@item_%d", x350008_g_ChristmasPet), 8, 3)
        else
            Msg2Player( sceneId, selfId, "无法获得物品，请整理道具栏", 8, 3)
        end
    end

    if index == 4 and random( 1, 100) == 50 then
        BeginAddItem( sceneId)
        AddItem( sceneId, x350008_g_ChristmasItem, 1)
        if EndAddItem( sceneId, selfId) > 0 then
            AddItemListToPlayer( sceneId, selfId)
            Msg2Player( sceneId, selfId, format( "你获得了@item_%d#cffcc00。", x350008_g_ChristmasItem), 8, 2)
            Msg2Player( sceneId, selfId, format( "获得圣诞礼品@item_%d", x350008_g_ChristmasItem), 8, 3)
        else
            Msg2Player( sceneId, selfId, "无法获得物品，请整理道具栏", 8, 3)
        end
    end

    local xp = GetLevel( sceneId, selfId) * 2000
    AddExp( sceneId, selfId, xp)
    Msg2Player( sceneId, selfId, format( "你获得了#R%d#cffcc00点经验。", xp), 8, 2)

    BeginQuestEvent( sceneId)
        AddQuestText( sceneId, "你领取了这个时间段的奖品。" )
    EndQuestEvent()
    DispatchQuestEventList( sceneId, selfId, targetId)

    -- write log
    GamePlayScriptLog( sceneId, selfId, 1362)
end

--**********************************
--接受
--**********************************
function x350008_ProcAccept( sceneId, selfId)
end

--**********************************
--放弃
--**********************************
function x350008_ProcQuestAbandon( sceneId, selfId, MissionId)

end

--**********************************
--继续
--**********************************
function x350008_OnContinue( sceneId, selfId, targetId)

end

--**********************************
--检测是否可以提交
--**********************************
function x350008_CheckSubmit( sceneId, selfId)

end

--**********************************
--提交
--**********************************
function x350008_ProcQuestSubmit( sceneId, selfId, targetId, index, MissionId)

end

--**********************************
--杀死怪物或玩家
--**********************************
function x350008_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId)

end

--**********************************
--进入区域事件
--**********************************
function x350008_ProcAreaEntered( sceneId, selfId, zoneId, MissionId)
end

