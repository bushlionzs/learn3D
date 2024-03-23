
x300172_g_ScriptId = 300172
x300172_g_FarScriptId = 300160

-- 2倍经验 杰克丹尼
x300172_g_XPBuffId          = 7647
-- 4倍经验 芝华士
x300172_g_DoubleXPBuffId    = 7648
-- 2倍声望 路易十三
x300172_g_CreditBuffId      = 7649
-- 4倍声望 轩尼诗理查
x300172_g_DoubleCreditBuffId= 7650
-- 8倍威望 哈瓦那雪茄
x300172_g_Mana8             = 7645
-- 可保存最大值(分钟)
x300172_g_SaveMaxMinute     = 600
-- 8倍经验 X 10小时
x300172_g_10H8XP            = 7667
-- 8倍声望 X 10小时
x300172_g_10H8Credit        = 7666
-- 8倍威望 X 10小时
x300172_g_10H8Mana          = 7665
-- 4倍经验 X 10小时
x300172_g_10H4XP            = 7668
-- 4倍声望 X 10小时
x300172_g_10H4Credit        = 7669


function x300172_GetExp2( sceneId, selfId)
    return GetQuestData( sceneId, selfId, MD_WUTING_EXP_2[ 1], MD_WUTING_EXP_2[ 2], MD_WUTING_EXP_2[ 3] )
end

function x300172_SetExp2( sceneId, selfId, value)
    SetQuestData( sceneId, selfId, MD_WUTING_EXP_2[ 1], MD_WUTING_EXP_2[ 2], MD_WUTING_EXP_2[ 3], value)
end

function x300172_GetExp4( sceneId, selfId)
    return GetQuestData( sceneId, selfId, MD_WUTING_EXP_4[ 1], MD_WUTING_EXP_4[ 2], MD_WUTING_EXP_4[ 3] )
end

function x300172_SetExp4( sceneId, selfId, value)
    SetQuestData( sceneId, selfId, MD_WUTING_EXP_4[ 1], MD_WUTING_EXP_4[ 2], MD_WUTING_EXP_4[ 3], value)
end

function x300172_GetCredit4( sceneId, selfId)
    return GetQuestData( sceneId, selfId, MD_WUTING_CREDIT_4[ 1], MD_WUTING_CREDIT_4[ 2], MD_WUTING_CREDIT_4[ 3] )
end

function x300172_SetCredit4( sceneId, selfId, value)
    SetQuestData( sceneId, selfId, MD_WUTING_CREDIT_4[ 1], MD_WUTING_CREDIT_4[ 2], MD_WUTING_CREDIT_4[ 3], value)
end

function x300172_GetCredit8( sceneId, selfId)
    return GetQuestData( sceneId, selfId, MD_WUTING_CREDIT_8[ 1], MD_WUTING_CREDIT_8[ 2], MD_WUTING_CREDIT_8[ 3] )
end

function x300172_SetCredit8( sceneId, selfId, value)
    SetQuestData( sceneId, selfId, MD_WUTING_CREDIT_8[ 1], MD_WUTING_CREDIT_8[ 2], MD_WUTING_CREDIT_8[ 3], value)
end

function x300172_GetMana8( sceneId, selfId)
    return GetQuestData( sceneId, selfId, MD_DANCERY_8MANA[ 1], MD_DANCERY_8MANA[ 2], MD_DANCERY_8MANA[ 3] )
end

function x300172_SetMana8( sceneId, selfId, value)
    SetQuestData( sceneId, selfId, MD_DANCERY_8MANA[ 1], MD_DANCERY_8MANA[ 2], MD_DANCERY_8MANA[ 3], value)
end

function x300172_GetXP8X10( sceneId, selfId)
    return GetQuestData( sceneId, selfId, MD_DANCERY_XP8X10[ 1], MD_DANCERY_XP8X10[ 2], MD_DANCERY_XP8X10[ 3] )
end

function x300172_SetXP8X10( sceneId, selfId, value)
    SetQuestData( sceneId, selfId, MD_DANCERY_XP8X10[ 1], MD_DANCERY_XP8X10[ 2], MD_DANCERY_XP8X10[ 3], value)
end

function x300172_GetXP4X10( sceneId, selfId)
    return GetQuestData( sceneId, selfId, MD_DANCERY_XP4X10[ 1], MD_DANCERY_XP4X10[ 2], MD_DANCERY_XP4X10[ 3] )
end

function x300172_SetXP4X10( sceneId, selfId, value)
    SetQuestData( sceneId, selfId, MD_DANCERY_XP4X10[ 1], MD_DANCERY_XP4X10[ 2], MD_DANCERY_XP4X10[ 3], value)
end

function x300172_GetCredit8X10( sceneId, selfId)
    return GetQuestData( sceneId, selfId, MD_DANCERY_CREDIT8X10[ 1], MD_DANCERY_CREDIT8X10[ 2], MD_DANCERY_CREDIT8X10[ 3] )
end

function x300172_SetCredit8X10( sceneId, selfId, value)
    SetQuestData( sceneId, selfId, MD_DANCERY_CREDIT8X10[ 1], MD_DANCERY_CREDIT8X10[ 2], MD_DANCERY_CREDIT8X10[ 3], value)
end

function x300172_GetCredit4X10( sceneId, selfId)
    return GetQuestData( sceneId, selfId, MD_DANCERY_CREDIT4X10[ 1], MD_DANCERY_CREDIT4X10[ 2], MD_DANCERY_CREDIT4X10[ 3] )
end

function x300172_SetCredit4X10( sceneId, selfId, value)
    SetQuestData( sceneId, selfId, MD_DANCERY_CREDIT4X10[ 1], MD_DANCERY_CREDIT4X10[ 2], MD_DANCERY_CREDIT4X10[ 3], value)
end

function x300172_GetMana8X10( sceneId, selfId)
    return GetQuestData( sceneId, selfId, MD_DANCERY_MANA8X10[ 1], MD_DANCERY_MANA8X10[ 2], MD_DANCERY_MANA8X10[ 3] )
end

function x300172_SetMana8X10( sceneId, selfId, value)
    SetQuestData( sceneId, selfId, MD_DANCERY_MANA8X10[ 1], MD_DANCERY_MANA8X10[ 2], MD_DANCERY_MANA8X10[ 3], value)
end

-- BuffID名称对应表
x300172_g_BuffTable         = {
                                { buffId = 7647, name = "杰克丹尼",     Get = x300172_GetExp2,       Set = x300172_SetExp2 }, 
                                { buffId = 7648, name = "芝华士",       Get = x300172_GetExp4,       Set = x300172_SetExp4 }, 
                                { buffId = 7649, name = "路易十三",     Get = x300172_GetCredit4,    Set = x300172_SetCredit4 }, 
                                { buffId = 7650, name = "轩尼诗理查",   Get = x300172_GetCredit8,    Set = x300172_SetCredit8 }, 
                                { buffId = 7645, name = "哈瓦那雪茄",   Get = x300172_GetMana8,      Set = x300172_SetMana8 }, 
                                { buffId = 7667, name = "精品芝华士",   Get = x300172_GetXP8X10,     Set = x300172_SetXP8X10 }, 
                                { buffId = 7666, name = "精品轩尼诗理查",   Get = x300172_GetCredit8X10, Set = x300172_SetCredit8X10 }, 
                                { buffId = 7665, name = "精品哈瓦那雪茄",   Get = x300172_GetMana8X10,   Set = x300172_SetMana8X10 }, 
                                { buffId = 7668, name = "精品杰克丹尼",   Get = x300172_GetXP4X10,     Set = x300172_SetXP4X10 }, 
                                { buffId = 7669, name = "精品路易十三",   Get = x300172_GetCredit4X10, Set = x300172_SetCredit4X10 }, 
}
-- 互斥检查表
x300172_g_MutexTable        = {
                                { buffId = 7647, check = { { buffId = 7648, name = "芝华士" },     { buffId = 7667, name = "精品芝华士" }, { buffId = 7668, name = "精品杰克丹尼" } } },
                                { buffId = 7648, check = { { buffId = 7647, name = "杰克丹尼" },   { buffId = 7667, name = "精品芝华士" }, { buffId = 7668, name = "精品杰克丹尼" } } },
                                { buffId = 7649, check = { { buffId = 7650, name = "轩尼诗理查" }, { buffId = 7666, name = "精品轩尼诗理查" }, { buffId = 7669, name = "精品路易十三" } } },
                                { buffId = 7650, check = { { buffId = 7649, name = "路易十三" },   { buffId = 7666, name = "精品轩尼诗理查" }, { buffId = 7669, name = "精品路易十三" } } },
                                { buffId = 7645, check = { { buffId = 7665, name = "精品哈瓦那雪茄" } } },
                                { buffId = 7667, check = { { buffId = 7648, name = "芝华士" },     { buffId = 7647, name = "杰克丹尼" }, { buffId = 7668, name = "精品杰克丹尼" } } },
                                { buffId = 7666, check = { { buffId = 7650, name = "轩尼诗理查" }, { buffId = 7649, name = "路易十三" }, { buffId = 7669, name = "精品路易十三" } } },
                                { buffId = 7665, check = { { buffId = 7645, name = "哈瓦那雪茄" } } },
                                { buffId = 7668, check = { { buffId = 7648, name = "芝华士" },     { buffId = 7647, name = "杰克丹尼" }, { buffId = 7667, name = "精品芝华士" } } },
                                { buffId = 7669, check = { { buffId = 7650, name = "轩尼诗理查" }, { buffId = 7649, name = "路易十三" }, { buffId = 7666, name = "精品轩尼诗理查" } } },
}

function x300172_ProcEnumEvent( sceneId, selfId, NPCId, MissionId)
    AddQuestNumText( sceneId, x300172_g_ScriptId, "【美丽会】存储", 3, 1)
    AddQuestNumText( sceneId, x300172_g_ScriptId, "【美丽会】取出", 3, 2)
    AddQuestNumText( sceneId, x300172_g_ScriptId, "【美丽会】存（取）说明", 13, 3)
end

function x300172_ProcEventEntry( sceneId, selfId, NPCId, idScript, idExt)
    -- print( "*-*-*-*-*-*-*-*-*-*-*" )
    if idExt == 1 then
        BeginQuestEvent( sceneId)
            AddQuestText( sceneId, "#Y【美】大都美丽会" )
            AddQuestText( sceneId, "\t您要储存哪种物品？" )
            AddQuestNumText( sceneId, x300172_g_ScriptId, "杰克丹尼", 3, 4)
            AddQuestNumText( sceneId, x300172_g_ScriptId, "芝华士", 3, 5)
            AddQuestNumText( sceneId, x300172_g_ScriptId, "路易十三", 3, 6)
            AddQuestNumText( sceneId, x300172_g_ScriptId, "轩尼诗理查", 3, 7)
            AddQuestNumText( sceneId, x300172_g_ScriptId, "哈瓦那雪茄", 3, 13)
            AddQuestNumText( sceneId, x300172_g_ScriptId, "精品芝华士", 3, 14)
            AddQuestNumText( sceneId, x300172_g_ScriptId, "精品轩尼诗理查", 3, 15)
            AddQuestNumText( sceneId, x300172_g_ScriptId, "精品哈瓦那雪茄", 3, 16)
            AddQuestNumText( sceneId, x300172_g_ScriptId, "精品杰克丹尼", 3, 20)
            AddQuestNumText( sceneId, x300172_g_ScriptId, "精品路易十三", 3, 21)
        EndQuestEvent()
        DispatchQuestEventList( sceneId, selfId, NPCId)
    elseif idExt == 2 then
        BeginQuestEvent( sceneId)
            AddQuestText( sceneId, "#Y【美】大都美丽会" )
            AddQuestText( sceneId, "\t您要取回哪种物品？" )
            local remainTime = x300172_GetExp2( sceneId, selfId)
            AddQuestNumText( sceneId, x300172_g_ScriptId, format( "杰克丹尼#G（%s）", x300172_GetTimeString( remainTime) ), 3, 8)
            remainTime = x300172_GetExp4( sceneId, selfId)
            AddQuestNumText( sceneId, x300172_g_ScriptId, format( "芝华士#G（%s）", x300172_GetTimeString( remainTime) ), 3, 9)
            remainTime = x300172_GetCredit4( sceneId, selfId)
            AddQuestNumText( sceneId, x300172_g_ScriptId, format( "路易十三#G（%s）", x300172_GetTimeString( remainTime) ), 3, 10)
            remainTime = x300172_GetCredit8( sceneId, selfId)
            AddQuestNumText( sceneId, x300172_g_ScriptId, format( "轩尼诗理查#G（%s）", x300172_GetTimeString( remainTime) ), 3, 11)
            remainTime = x300172_GetMana8( sceneId, selfId)
            AddQuestNumText( sceneId, x300172_g_ScriptId, format( "哈瓦那雪茄#G（%s）", x300172_GetTimeString( remainTime) ), 3, 12)
            remainTime = x300172_GetXP8X10( sceneId, selfId)
            AddQuestNumText( sceneId, x300172_g_ScriptId, format( "精品芝华士#G（%s）", x300172_GetTimeString( remainTime) ), 3, 17)
            remainTime = x300172_GetCredit8X10( sceneId, selfId)
            AddQuestNumText( sceneId, x300172_g_ScriptId, format( "精品轩尼诗理查#G（%s）", x300172_GetTimeString( remainTime) ), 3, 18)
            remainTime = x300172_GetMana8X10( sceneId, selfId)
            AddQuestNumText( sceneId, x300172_g_ScriptId, format( "精品哈瓦那雪茄#G（%s）", x300172_GetTimeString( remainTime) ), 3, 19)
            remainTime = x300172_GetXP4X10( sceneId, selfId)
            AddQuestNumText( sceneId, x300172_g_ScriptId, format( "精品杰克丹尼#G（%s）", x300172_GetTimeString( remainTime) ), 3, 22)
            remainTime = x300172_GetCredit4X10( sceneId, selfId)
            AddQuestNumText( sceneId, x300172_g_ScriptId, format( "精品路易十三#G（%s）", x300172_GetTimeString( remainTime) ), 3, 23)
        EndQuestEvent()
        DispatchQuestEventList( sceneId, selfId, NPCId)
    elseif idExt == 3 then
        BeginQuestEvent( sceneId)
            AddQuestText( sceneId, "#Y【美】大都美丽会" )
            AddQuestText( sceneId, "\t假如您想离开美丽会，又担心自己的酒（雪茄）浪费掉，您可以通过我来储存，但是每种物品我只能帮您储存最多10个小时哦！" )
        EndQuestEvent()
        DispatchQuestEventList( sceneId, selfId, NPCId)
    elseif idExt == 4 then
        x300172_ShowSaveInfo( sceneId, selfId, NPCId, x300172_g_XPBuffId)
    elseif idExt == 5 then
        x300172_ShowSaveInfo( sceneId, selfId, NPCId, x300172_g_DoubleXPBuffId)
    elseif idExt == 6 then
        x300172_ShowSaveInfo( sceneId, selfId, NPCId, x300172_g_CreditBuffId)
    elseif idExt == 7 then
        x300172_ShowSaveInfo( sceneId, selfId, NPCId, x300172_g_DoubleCreditBuffId)
    elseif idExt == 13 then
        x300172_ShowSaveInfo( sceneId, selfId, NPCId, x300172_g_Mana8)
    elseif idExt == 14 then
        x300172_ShowSaveInfo( sceneId, selfId, NPCId, x300172_g_10H8XP)
    elseif idExt == 15 then
        x300172_ShowSaveInfo( sceneId, selfId, NPCId, x300172_g_10H8Credit)
    elseif idExt == 16 then
        x300172_ShowSaveInfo( sceneId, selfId, NPCId, x300172_g_10H8Mana)
    elseif idExt == 20 then
        x300172_ShowSaveInfo( sceneId, selfId, NPCId, x300172_g_10H4XP)
    elseif idExt == 21 then
        x300172_ShowSaveInfo( sceneId, selfId, NPCId, x300172_g_10H4Credit)
    elseif idExt == 8 then
        x300172_ShowLoadInfo( sceneId, selfId, NPCId, x300172_g_XPBuffId)
    elseif idExt == 9 then
        x300172_ShowLoadInfo( sceneId, selfId, NPCId, x300172_g_DoubleXPBuffId)
    elseif idExt == 10 then
        x300172_ShowLoadInfo( sceneId, selfId, NPCId, x300172_g_CreditBuffId)
    elseif idExt == 11 then
        x300172_ShowLoadInfo( sceneId, selfId, NPCId, x300172_g_DoubleCreditBuffId)
    elseif idExt == 12 then
        x300172_ShowLoadInfo( sceneId, selfId, NPCId, x300172_g_Mana8)
    elseif idExt == 17 then
        x300172_ShowLoadInfo( sceneId, selfId, NPCId, x300172_g_10H8XP)
    elseif idExt == 18 then
        x300172_ShowLoadInfo( sceneId, selfId, NPCId, x300172_g_10H8Credit)
    elseif idExt == 19 then
        x300172_ShowLoadInfo( sceneId, selfId, NPCId, x300172_g_10H8Mana)
    elseif idExt == 22 then
        x300172_ShowLoadInfo( sceneId, selfId, NPCId, x300172_g_10H4XP)
    elseif idExt == 23 then
        x300172_ShowLoadInfo( sceneId, selfId, NPCId, x300172_g_10H4Credit)
    end             
end

function x300172_ProcAcceptCheck( sceneId, selfId, NPCId)
    return 1
end

function x300172_ProcAccept( sceneId, selfId)
    local runtimeData = GetPlayerRuntimeData( sceneId, selfId, RD_COLLECT_HORSE)
    if mod( runtimeData, 10) == 0 then
        x300172_SaveBuff( sceneId, selfId, runtimeData / 10)
    else
        x300172_LoadBuff( sceneId, selfId, floor( runtimeData / 10) )
    end
end

-- 分钟转换为N小时M分钟
function x300172_GetTimeString( minute)
    local strResult = ""

    if minute >= 60 then
        local h = floor( minute / 60)
        local m = mod( minute, 60)
        if m == 0 then
            strResult = format( "%d小时", h)
        else
            strResult = format( "%d小时%d分", h, m)
        end
    else
        strResult = format( "%d分钟", minute)
    end

    return strResult
end

-- 储存Buff
function x300172_SaveBuff( sceneId, selfId, buffId)
    local saveItem = nil
    for i, item in x300172_g_BuffTable do
        if item.buffId == buffId then
            saveItem = item
            break
        end
    end
    -- 获得Buff持续总时间
    local amountTime = GetImpactContinuanceByDataIndex( sceneId, selfId, buffId)
    if amountTime > 0 then
        -- 剩余时间(分钟)
        local remainTime = ( amountTime - GetImpactContinuanceElapsed( sceneId, selfId, buffId) ) / 60000
        -- 已经保存的时间
        local savedTime = saveItem.Get( sceneId, selfId)
        local newTime = savedTime + remainTime
        if newTime > x300172_g_SaveMaxMinute then
            -- 保存Buff
            saveItem.Set( sceneId, selfId, x300172_g_SaveMaxMinute)
            -- 更新身上的Buff时间
            SetImpactContinuanceByDataIndex( sceneId, selfId, buffId, ( newTime - x300172_g_SaveMaxMinute) * 60000)
            ResetImpactContinuanceElapsed( sceneId, selfId, buffId)
            RefreshImpactByDataIndex( sceneId, selfId,buffId)
            Msg2Player( sceneId, selfId, "你已经存满10小时，不能再多存了", 8, 3)
        else
            -- 保存Buff
            saveItem.Set( sceneId, selfId, newTime)
            -- 清除身上的Buff时间
            CancelSpecificImpact( sceneId, selfId, buffId)
        end
    else
        Msg2Player( sceneId, selfId, format( "你身上已经没有%s了", saveItem.name), 8, 3)
    end
end

-- 恢复Buff
function x300172_LoadBuff( sceneId, selfId, buffId)
    local loadItem = nil
    for i, item in x300172_g_BuffTable do
        if item.buffId == buffId then
            loadItem = item
            break
        end
    end

    -- 互斥检查
    for i, item in x300172_g_MutexTable do
        if buffId == item.buffId then
            for j, iter in item.check do
                if IsHaveSpecificImpact( sceneId, selfId, iter.buffId) == 1 then
                    Msg2Player( sceneId, selfId, format( "你身上已有#G%s#cffcc00不能取出#G%s", iter.name, loadItem.name), 8, 3)
                    return
                end
            end
        end
    end

    local savedTime = loadItem.Get( sceneId, selfId)
    if savedTime == 0 then
        Msg2Player( sceneId, selfId, format( "你没有%s", loadItem.name), 8, 3)
        return
    end
    -- 获得Buff持续总时间
    local amountTime = GetImpactContinuanceByDataIndex( sceneId, selfId, buffId)
    -- 剩余时间(分钟)
    local remainTime = ( amountTime - GetImpactContinuanceElapsed( sceneId, selfId, buffId) ) / 60000
    local newTime = remainTime + savedTime
    if newTime > x300172_g_SaveMaxMinute then
        if remainTime == 0 then
            SendSpecificImpactToUnit( sceneId, selfId, selfId, selfId, buffId, 0)
        end
        -- 更新身上的Buff时间
        SetImpactContinuanceByDataIndex( sceneId, selfId, buffId, x300172_g_SaveMaxMinute * 60000)
        ResetImpactContinuanceElapsed( sceneId, selfId, buffId)
        RefreshImpactByDataIndex( sceneId, selfId, buffId)
        -- 更新保存的时间
        loadItem.Set( sceneId, selfId, newTime - x300172_g_SaveMaxMinute)
        Msg2Player( sceneId, selfId, format( "你身上的%s已达最大值，还剩余存储#G%s", loadItem.name, x300172_GetTimeString( newTime - x300172_g_SaveMaxMinute) ), 8, 3)
    else
        if remainTime == 0 then
            SendSpecificImpactToUnit( sceneId, selfId, selfId, selfId, buffId, 0)
        end
        -- 更新身上的Buff时间
        SetImpactContinuanceByDataIndex( sceneId, selfId, buffId, newTime * 60000)
        ResetImpactContinuanceElapsed( sceneId, selfId, buffId)
        RefreshImpactByDataIndex( sceneId, selfId, buffId)
        -- 更新保存的时间
        loadItem.Set( sceneId, selfId, 0)
        Msg2Player( sceneId, selfId, format( "你取回了所有的%s", loadItem.name), 8, 2)
    end
end

-- 显示保存Buff确认界面
function x300172_ShowSaveInfo( sceneId, selfId, NPCId, buffId)
    BeginQuestEvent( sceneId)
        AddQuestText( sceneId, "#Y【美】大都美丽会" )
        if buffId == x300172_g_XPBuffId then
            AddQuestText( sceneId, "你是否要储存杰克丹尼？" )
        elseif buffId == x300172_g_DoubleXPBuffId then
            AddQuestText( sceneId, "你是否要储存芝华士？" )
        elseif buffId == x300172_g_CreditBuffId then
            AddQuestText( sceneId, "你是否要储存路易十三？" )
        elseif buffId == x300172_g_DoubleCreditBuffId then
            AddQuestText( sceneId, "你是否要储存轩尼诗理查？" )
        elseif buffId == x300172_g_Mana8 then
            AddQuestText( sceneId, "你是否要储存哈瓦那雪茄？" )
        elseif buffId == x300172_g_10H8XP then
            AddQuestText( sceneId, "你是否要储存精品芝华士？" )
        elseif buffId == x300172_g_10H4XP then
            AddQuestText( sceneId, "你是否要储存精品杰克丹尼？" )
        elseif buffId == x300172_g_10H8Credit then
            AddQuestText( sceneId, "你是否要储存精品轩尼诗理查？" )
        elseif buffId == x300172_g_10H4Credit then
            AddQuestText( sceneId, "你是否要储存精品路易十三？" )
        elseif buffId == x300172_g_10H8Mana then
            AddQuestText( sceneId, "你是否要储存精品哈瓦那雪茄？" )
        end
    EndQuestEvent()
    SetPlayerRuntimeData( sceneId, selfId, RD_COLLECT_HORSE, buffId * 10)
    DispatchQuestInfo( sceneId, selfId, NPCId, x300172_g_ScriptId, -1)
end

-- 显示取回Buff确认界面
function x300172_ShowLoadInfo( sceneId, selfId, NPCId, buffId)
    BeginQuestEvent( sceneId)
        AddQuestText( sceneId, "#Y【美】大都美丽会" )
        if buffId == x300172_g_XPBuffId then
            AddQuestText( sceneId, "你是否要取回杰克丹尼？" )
        elseif buffId == x300172_g_DoubleXPBuffId then
            AddQuestText( sceneId, "你是否要取回芝华士？" )
        elseif buffId == x300172_g_CreditBuffId then
            AddQuestText( sceneId, "你是否要取回路易十三？" )
        elseif buffId == x300172_g_DoubleCreditBuffId then
            AddQuestText( sceneId, "你是否要取回轩尼诗理查？" )
        elseif buffId == x300172_g_Mana8 then
            AddQuestText( sceneId, "你是否要取回哈瓦那雪茄？" )
        elseif buffId == x300172_g_10H8XP then
            AddQuestText( sceneId, "你是否要取回精品芝华士？" )
        elseif buffId == x300172_g_10H4XP then
            AddQuestText( sceneId, "你是否要取回精品杰克丹尼？" )
        elseif buffId == x300172_g_10H8Credit then
            AddQuestText( sceneId, "你是否要取回精品轩尼诗理查？" )
        elseif buffId == x300172_g_10H4Credit then
            AddQuestText( sceneId, "你是否要取回精品路易十三？" )
        elseif buffId == x300172_g_10H8Mana then
            AddQuestText( sceneId, "你是否要取回精品哈瓦那雪茄？" )
        end
    EndQuestEvent()
    SetPlayerRuntimeData( sceneId, selfId, RD_COLLECT_HORSE, buffId * 10 + 1)
	DispatchQuestInfo( sceneId, selfId, NPCId, x300172_g_ScriptId, -1)
end


