--MisDescBegin
--脚本号
x920006_g_ScriptId = 920006


--任务文本描述
x920006_g_MissionName       = "【个人】收集战马"
-- 收马描述
x920006_g_strCollectHorse   = "\t国家需要更多的战马！去#G王国马场#W带回蒙古马，在我这里可换取银卡一百文。如果你能捕捉到更好的蒙古马，则可以换取8倍的报酬。"

x920006_CountrySceneList	= { 50, 150, 250, 350}
--MisDescEnd

-- 宝马ID列表
x920006_g_GoodHorseTable    = {  2,  3,  4,  5, 
                                12, 13, 14, 15, 
                                22, 23, 24, 25, 
                                32, 33, 34, 35, 
                                42, 43, 44, 45, 
                                52, 53, 54, 55 
}
-- 普通马ID列表
x920006_g_CommonHorseTable  = { 1, 11, 21, 31, 41, 51 }
-- 每天最多交马次数
x920006_g_MaxTimes          = 10
x920006_g_strOverMaxTimes   = "你本日已经交过十匹战马，不能再交了"

--**********************************
--任务入口函数
--**********************************
function x920006_ProcEventEntry( sceneId, selfId, targetId, scriptid, extid)	--点击该任务后执行此脚本
    --print( "*********************-*"..extid)
    
    -- 判断玩家是否有骑乘
    if GetHorseCount( sceneId, selfId) > 0 then--
        BeginQuestEvent( sceneId)
            AddQuestText( sceneId, "#Y【个人】收集战马" )
            AddQuestText( sceneId, "\t国家需要更多的战马！去#G王国马场#W带回一匹马来，在我这里可换取银卡奖励。\n\t如果你能捕捉到良品马来，则可以换取8倍的报酬。\n\t当然，战马的携带等级越高，我所给的薪偿也就更高。" )
        EndQuestEvent()
        DispatchQuestEventList( sceneId, selfId, targetId, x920006_g_ScriptId, x920006_g_MissionName)

        -- 通知客户端显示宠物列表窗口
        BeginUICommand( sceneId);
            UICommand_AddInt( sceneId, x920006_g_ScriptId);
            UICommand_AddInt( sceneId, 0);	--任务ID随便填一个即可
            UICommand_AddInt( sceneId, targetId);
            DispatchUICommand( sceneId, selfId, 101);
        EndUICommand( sceneId)
    else
        BeginQuestEvent( sceneId)
            AddQuestText( sceneId, "#Y【个人】收集战马" )
            AddQuestText( sceneId, "\t你自己都无马可骑，怎么能贡献战马给国家呢？" )
        EndQuestEvent()
        DispatchQuestEventList( sceneId, selfId, targetId, x920006_g_ScriptId, x920006_g_MissionName)
    end
end

--**********************************
--列举事件
--**********************************
function x920006_ProcEnumEvent( sceneId, selfId, targetId, MissionId)
    SetPlayerRuntimeData( sceneId, selfId, RD_COLLECT_HORSE_HIGH, 0)
    SetPlayerRuntimeData( sceneId, selfId, RD_COLLECT_HORSE_LOW, 0)
    SetPlayerRuntimeData( sceneId, selfId, RD_COLLECT_HORSE, 0)

    -- 判断国家场景，防止异国卖马
    if x920006_CountrySceneList[ GetCurCountry( sceneId, selfId) + 1] == sceneId then
        AddQuestNumText( sceneId, x920006_g_ScriptId, x920006_g_MissionName, 3)
        BeginUICommand( sceneId)
            DispatchUICommand( sceneId, selfId, 102)
        EndUICommand( sceneId)
    end
end


--********************
--检测接受条件
--**********************************
function x920006_ProcAcceptCheck( sceneId, selfId, NPCId)
    --print( "x920006_ProcAcceptCheck" )
    local high = GetPlayerRuntimeData( sceneId, selfId, RD_COLLECT_HORSE_HIGH)
    local low = GetPlayerRuntimeData( sceneId, selfId, RD_COLLECT_HORSE_LOW)
    local nIndex = GetPlayerRuntimeData( sceneId, selfId, RD_COLLECT_HORSE)
    local PetID = GetHorseDataID( sceneId, selfId, nIndex)
    local takeLevel = GetPet_TakeLevel( sceneId, selfId, nIndex)
    local id = 0
    if PetID < 2000 and PetID >=100 then
        id = mod( PetID, 100)
    end

    -- 检查防止玩家在确定卖马前把马放了等异常情况下可以领到钱的问题
    if IsHaveHorse( sceneId, selfId, PetID) == 0 then
        BeginQuestEvent( sceneId)
            AddQuestText( sceneId, "#Y【个人】收集战马" )
            AddQuestText( sceneId, "\t找不到你要卖的马！" )
        EndQuestEvent()
        DispatchQuestEventList( sceneId, selfId, NPCId, x920006_g_ScriptId, x920006_g_MissionName)
        return
    end

    -- 判断马种类
    local bFindGood = 0
    for i, item in x920006_g_GoodHorseTable do
        if id == item then
            bFindGood = 1
            break
        end
    end
    local bFindCommon = 0
    if bFindGood == 0 then
        for i, item in x920006_g_CommonHorseTable do
            if id == item then
                bFindCommon = 1
                break
            end
        end
    end
    
    if bFindCommon ~= 1 and bFindGood ~= 1 then
        Msg2Player( sceneId, selfId, "我这里只收集普通马和良品马", 8, 3)
        return
    end

    -- 次数检查
    local today = GetDayOfYear()
    if x920006_GetMissionDate( sceneId, selfId) == today then
        local times = x920006_GetMissionTimes( sceneId, selfId)
        if times >= x920006_g_MaxTimes then
            Msg2Player( sceneId, selfId, x920006_g_strOverMaxTimes, 8, 3)
            Msg2Player( sceneId, selfId, x920006_g_strOverMaxTimes, 8, 2)
            return
        end
    end

    -- 收马
    if FreeHorse( sceneId, selfId, high, low) ~= 1 then
        Msg2Player( sceneId, selfId, "收集战马失败", 8, 3)
        return
    end

    local today = GetDayOfYear()
    if x920006_GetMissionDate( sceneId, selfId) ~= today then
        -- 更新日期
        x920006_SetMissionDate( sceneId, selfId, today)
        x920006_SetMissionTimes( sceneId, selfId, 1)
    else
        local times = x920006_GetMissionTimes( sceneId, selfId)
        if times >= x920006_g_MaxTimes then
            Msg2Player( sceneId, selfId, x920006_g_strOverMaxTimes, 8, 3)
            Msg2Player( sceneId, selfId, x920006_g_strOverMaxTimes, 8, 2)
            return
        else
            -- 更新当天交马次数
            x920006_SetMissionTimes( sceneId, selfId, times + 1)
        end
    end

    -- 判断是不是良品马
    if bFindGood == 1 then
        -- 良品马
        local money = takeLevel * 80
        AddMoney( sceneId, selfId, 1, money)
        Msg2Player( sceneId, selfId, format( "你获得了#R银卡#{_MONEY%d}#cffcf00的奖励", money), 8, 3)
        Msg2Player( sceneId, selfId, format( "你获得了#R银卡#{_MONEY%d}#cffcf00的奖励", money), 8, 2)
    elseif bFindCommon == 1 then
        -- 普通马
        local money = takeLevel * 10
        AddMoney( sceneId, selfId, 1, money)
        Msg2Player( sceneId, selfId, format( "你获得了#R银卡#{_MONEY%d}#cffcf00的奖励", money), 8, 3)
        Msg2Player( sceneId, selfId, format( "你获得了#R银卡#{_MONEY%d}#cffcf00的奖励", money), 8, 2)
    end

    SetPlayerRuntimeData( sceneId, selfId, RD_COLLECT_HORSE_HIGH, -1)
    SetPlayerRuntimeData( sceneId, selfId, RD_COLLECT_HORSE_LOW, -1)
    SetPlayerRuntimeData( sceneId, selfId, RD_COLLECT_HORSE, -1)

    -- 写日志
    GamePlayScriptLog( sceneId, selfId, 401)
end

--**********************************
--接受
--**********************************
function x920006_ProcAccept( sceneId, selfId)
end

--**********************************
--放弃
--**********************************
function x920006_ProcQuestAbandon( sceneId, selfId, MissionId )
end

--**********************************
--继续
--**********************************
function x920006_OnContinue( sceneId, selfId, targetId )
end

--**********************************
--检测是否可以提交
--**********************************
function x920006_CheckSubmit( sceneId, selfId )

end

--**********************************
--提交
--**********************************
function x920006_ProcQuestSubmit( sceneId, selfId, targetId, selectRadioId, MissionId )

end

--**********************************
--杀死怪物或玩家
--**********************************
function x920006_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--进入区域事件
--**********************************
function x920006_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--道具改变
--**********************************
function x920006_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end

-- 根据提交的宠物ID判断是否符合任务要求，不符合返回0，否则扣马、关闭宠物列表界面、返回非0值
-- 参数：
--  sceneId：场景ID
--  selfId：玩家ID
--  PetID：宠物的模型ID
--  targetId：NPC的id
--  horseGUID_high：GUID高位
--  horseGUID_low：GUID低位
--  nIndex：宠物列表索引值
function x920006_OnCommitPet( sceneId, selfId, MissionId, targetId, horseGUID_high, horseGUID_low, nIndex)
    --print( "战马Id："..PetID)
    local id = 0
    local PetID = GetHorseDataID( sceneId, selfId, nIndex)
    if PetID < 2000 and PetID >=100 then
        id = mod( PetID, 100)
    end
    local takeLevel = GetPet_TakeLevel( sceneId, selfId, nIndex)
    -- 判断提交的马是否符合要求
    local bFindGood = 0
    for i, item in x920006_g_GoodHorseTable do
        if id == item then
            bFindGood = 1
            break
        end
    end
    local bFindCommon = 0
    if bFindGood == 0 then
        for i, item in x920006_g_CommonHorseTable do
            if id == item then
                bFindCommon = 1
                break
            end
        end
    end
    if bFindGood == 1 or bFindCommon == 1 then--
        -- 判断是不是良品马
        if bFindGood == 1 then
            -- 良品马
            BeginQuestEvent( sceneId)
                AddQuestText( sceneId, "#Y【个人】收集战马" )
                AddQuestText( sceneId, "\t竟然是如此优秀的马匹！将它交给我，你会获得丰厚的回报。" )
                AddQuestText( sceneId, " " )
                AddQuestText( sceneId, "#Y奖励内容：" )
                AddQuestText( sceneId, format( "银卡：#{_MONEY%d}", takeLevel * 80) )
            EndQuestEvent()
        else
            -- 普通马
            BeginQuestEvent( sceneId)
                AddQuestText( sceneId, "#Y【个人】收集战马" )
                AddQuestText( sceneId, "\t想将这匹战马交给我吗？放心，我不会亏待你的。" )
                AddQuestText( sceneId, " " )
                AddQuestText( sceneId, "#Y奖励内容：" )
                AddQuestText( sceneId, format( "银卡：#{_MONEY%d}", takeLevel * 10) )
            EndQuestEvent()
        end
        DispatchQuestInfo( sceneId, selfId, targetId, x920006_g_ScriptId, -1)

        SetPlayerRuntimeData( sceneId, selfId, RD_COLLECT_HORSE_HIGH, horseGUID_high)
        SetPlayerRuntimeData( sceneId, selfId, RD_COLLECT_HORSE_LOW, horseGUID_low)
        SetPlayerRuntimeData( sceneId, selfId, RD_COLLECT_HORSE, nIndex)

        -- close horse UI
        BeginUICommand( sceneId)
            DispatchUICommand( sceneId, selfId, 102)
        EndUICommand( sceneId)
    else
        -- 提示不符合要求
        BeginQuestEvent( sceneId)
            AddQuestText( sceneId, "你提交的骑乘不符合需求" )
        EndQuestEvent()
        DispatchQuestTips( sceneId, selfId)
        -- 添加客户端右下角显示
        Msg2Player( sceneId, selfId, "你提交的骑乘不符合需求", 4, 2)
    end
end

function x920006_ProcQuestAccept( sceneId, selfId, targetId, missionId)
    --print( "****************" )
end

function x920006_GetMissionDate( sceneId, selfId)
    return GetQuestData( sceneId, selfId, MD_COLLECTHORSE_DATE[ 1], MD_COLLECTHORSE_DATE[ 2], MD_COLLECTHORSE_DATE[ 3] )
end

function x920006_SetMissionDate( sceneId, selfId, value)
    SetQuestData( sceneId, selfId, MD_COLLECTHORSE_DATE[ 1], MD_COLLECTHORSE_DATE[ 2], MD_COLLECTHORSE_DATE[ 3], value)
end

function x920006_GetMissionTimes( sceneId, selfId)
    return GetQuestData( sceneId, selfId, MD_COLLECTHORSE_TIMES[ 1], MD_COLLECTHORSE_TIMES[ 2], MD_COLLECTHORSE_TIMES[ 3] )
end

function x920006_SetMissionTimes( sceneId, selfId, value)
    SetQuestData( sceneId, selfId, MD_COLLECTHORSE_TIMES[ 1], MD_COLLECTHORSE_TIMES[ 2], MD_COLLECTHORSE_TIMES[ 3], value)
end


