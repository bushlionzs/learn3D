-- 脚本号
x310393_g_ScriptId              = 310393
-- 任务ID
x310393_g_MissionId             = 9060
-- 任务名
x310393_g_MissionName           = "金龙印兑换"
-- 物品ID
x310393_g_ItemID                = 11000597
-- 花费价格
x310393_g_CostMoney             = 500

function x310393_ProcEnumEvent( sceneId, selfId, NPCId, MissionId)
    AddQuestNumText( sceneId, x310393_g_ScriptId, x310393_g_MissionName, 3, 1)
end

function x310393_ProcEventEntry( sceneId, selfId, NPCId, idScript, idExt)
    if idExt == 1 then
        BeginQuestEvent( sceneId)
            AddQuestText( sceneId, "#Y"..x310393_g_MissionName)
            AddQuestText( sceneId, format( "\t@item_%d#W是时装纹龙的必备道具。只要本周进行过挖宝大作战，就能在我这里兑换一个@item_%d。\n\t#W是否花费#R500#W文金卡/现金换取一个@item_%d#W？", x310393_g_ItemID, x310393_g_ItemID , x310393_g_ItemID) )
        EndQuestEvent()
        DispatchQuestInfo( sceneId, selfId, NPCId, x310393_g_ScriptId, -1)
    end
end

function x310393_ProcAcceptCheck( sceneId, selfId, NPCId)
    local day, week = GetWeek()
    if week ~= x310393_GetMD( sceneId, selfId, MD_WABAO_WEEK) then
        Msg2Player( sceneId, selfId, "你没有接受挖宝大作战任务", 8, 3)
        return 0
    else
        if day == 6 then
            if x310393_GetMD( sceneId, selfId, MD_WABAO_FINISHED) == 0 then
                Msg2Player( sceneId, selfId, "你今天没有完成挖宝大作战，不能兑换", 8, 3)
                return 0
            end
            if x310393_GetMD( sceneId, selfId, MD_WABAO_DUIHUAN1) == 1 then
                Msg2Player( sceneId, selfId, "你本周已经兑换过一次，不能再次兑换", 8, 3)
                return 0
            end
        end
        if day == 0 then
            if x310393_GetMD( sceneId, selfId, MD_WABAO_TIMES) == 0 then
                Msg2Player( sceneId, selfId, "你今天没有完成挖宝大作战，不能兑换", 8, 3)
                return 0
            end
            if x310393_GetMD( sceneId, selfId, MD_WABAO_DUIHUAN1) == 1 then
                Msg2Player( sceneId, selfId, "你本周已经兑换过一次，不能再次兑换", 8, 3)
                return 0
            end
        end
    end

    BeginAddItem( sceneId)
    AddBindItem( sceneId, x310393_g_ItemID, 1)
    if EndAddItem( sceneId, selfId) == 0 then
        Msg2Player( sceneId, selfId, "背包空间不足，无法领取", 8, 3)
        return 0
    end

    if GetGoldMode( sceneId, selfId) == 1 then
        if CostMoney( sceneId, selfId, 2, x310393_g_CostMoney,312) ~= 1 then
            if CostMoney(sceneId, selfId, 3, x310393_g_CostMoney) ~= 1 then
                Msg2Player( sceneId, selfId, format( "你身上的金卡/现金不足#R%d#cffcc00文", x310393_g_CostMoney), 8, 3)
                return 0
            end
        end
    else
        if CostMoney( sceneId, selfId, 3, x310393_g_CostMoney) ~= 1 then
            if CostMoney(sceneId, selfId, 2, x310393_g_CostMoney,312) ~= 1 then
                Msg2Player( sceneId, selfId, format( "你身上的金卡/现金不足#R%d#cffcc00文", x310393_g_CostMoney), 8, 3)
                return 0
            end
        end
    end

    AddItemListToPlayer( sceneId, selfId)

        x310393_SetMD( sceneId, selfId, MD_WABAO_DUIHUAN1, 1)

    return 1
end

function x310393_GetMD( sceneId, selfId, mdName)
    return GetQuestData( sceneId, selfId, mdName[ 1], mdName[ 2], mdName[ 3] )
end

function x310393_SetMD( sceneId, selfId, mdName, value)
    SetQuestData( sceneId, selfId, mdName[ 1], mdName[ 2], mdName[ 3], value)
end

function x310393_ProcAccept( sceneId, selfId, NPCId)
end
