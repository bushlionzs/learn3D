-- 脚本号
x310392_g_ScriptId              = 310392
-- 任务ID
x310392_g_MissionId             = 9060
-- 任务名
x310392_g_MissionName           = "金龙印兑换"
-- 物品ID
x310392_g_ItemID                = 11000597
-- 花费价格
x310392_g_CostMoney             = 500

function x310392_ProcEnumEvent( sceneId, selfId, NPCId, MissionId)
    AddQuestNumText( sceneId, x310392_g_ScriptId, x310392_g_MissionName, 3, 1)
end

function x310392_ProcEventEntry( sceneId, selfId, NPCId, idScript, idExt)
    if idExt == 1 then
        BeginQuestEvent( sceneId)
            AddQuestText( sceneId, "#Y"..x310392_g_MissionName)
            AddQuestText( sceneId, format( "\t@item_%d#W是时装纹龙的必备道具。只要本周进行过天降魔君，就能在我这里兑换一个@item_%d。\n\t#W是否花费#R500#W文金卡/现金换取一个@item_%d#W？", x310392_g_ItemID, x310392_g_ItemID, x310392_g_ItemID) )
        EndQuestEvent()
        DispatchQuestInfo( sceneId, selfId, NPCId, x310392_g_ScriptId, -1)
    end
end

function x310392_ProcAcceptCheck( sceneId, selfId, NPCId)
    local day, week = GetWeek()
    local weekIndex = GetWeekIndex()
    if GetDayOfYear() ~= x310392_GetMD( sceneId, selfId, MD_TJMJ_DATE) then
        Msg2Player( sceneId, selfId, "你今天还没有参加天降魔君活动，不能兑换", 8, 3)
        return 0
    else
        if x310392_GetMD( sceneId, selfId, MD_MOJUN_WEEK) == weekIndex and x310392_GetMD( sceneId, selfId, MD_MOJUN_DUIHUAN) == 1 then
            Msg2Player( sceneId, selfId, "你本周已经兑换过一次，不能再次兑换", 8, 3)
            return 0
        end

        if x310392_GetMD( sceneId, selfId, MD_TJMJ_TIMES) == 0 then
            Msg2Player( sceneId, selfId, "你今天还没有参加天降魔君活动，不能兑换", 8, 3)
            return 0
        end
    end

    BeginAddItem( sceneId)
    AddBindItem( sceneId, x310392_g_ItemID, 1)
    if EndAddItem( sceneId, selfId) == 0 then
        Msg2Player( sceneId, selfId, "背包空间不足，无法兑换", 8, 3)
        return 0
    end

    if GetGoldMode( sceneId, selfId) == 1 then
        if CostMoney( sceneId, selfId, 2, x310392_g_CostMoney,311) ~= 1 then
            if CostMoney(sceneId, selfId, 3, x310392_g_CostMoney) ~= 1 then
                Msg2Player( sceneId, selfId, format( "你身上的金卡/现金不足#R%d#cffcc00文", x310392_g_CostMoney), 8, 3)
                return 0
            end
        end
    else
        if CostMoney( sceneId, selfId, 3, x310392_g_CostMoney) ~= 1 then
            if CostMoney(sceneId, selfId, 2, x310392_g_CostMoney,311) ~= 1 then
                Msg2Player( sceneId, selfId, format( "你身上的金卡/现金不足#R%d#cffcc00文", x310392_g_CostMoney), 8, 3)
                return 0
            end
        end
    end

    AddItemListToPlayer( sceneId, selfId)

    x310392_SetMD( sceneId, selfId, MD_MOJUN_DUIHUAN, 1)
    x310392_SetMD( sceneId, selfId, MD_MOJUN_WEEK, weekIndex)

    return 1
end

function x310392_GetMD( sceneId, selfId, mdName)
    return GetQuestData( sceneId, selfId, mdName[ 1], mdName[ 2], mdName[ 3] )
end

function x310392_SetMD( sceneId, selfId, mdName, value)
    SetQuestData( sceneId, selfId, mdName[ 1], mdName[ 2], mdName[ 3], value)
end

function x310392_ProcAccept( sceneId, selfId, NPCId)
end
