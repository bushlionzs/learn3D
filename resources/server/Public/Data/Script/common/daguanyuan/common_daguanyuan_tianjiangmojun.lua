-- 脚本号
x310365_g_ScriptId          = 310365
-- 活动名称
x310365_g_Name              = "【个人】镇妖除魔"
-- 参加活动的最低等级
x310365_g_MinLevel          = 85
-- 提示等级不足
x310365_g_LessThanMinLevel  = format( "本活动只对#G%d#cffcc00级以上玩家开放", x310365_g_MinLevel)
-- 每天完成次数
x310365_g_MaxTimesInDay     = 20
-- 提示本日已完成最大次数
x310365_g_strOverMaxTimes   = format( "你今天已经为万妖壶增加了#G%d#cffcc00次灵气了，改天再来吧。", x310365_g_MaxTimesInDay)
-- 最少背包空间
x310365_g_MinBagSpace       = 1
-- 提示背包空间不足
x310365_g_strNotEnoughBag   = format( "您的背包空间不足#G%d#cffcc00个，请清理后再来。", x310365_g_MinBagSpace)
-- 花费金
x310365_g_CostMoney         = 500
-- 全局祈福计次
x310365_g_GlobalCount       = 0
-- 物品奖励配置表
x310365_g_ItemTable         = {
                                { itemId = 12041101, name = "修行草" }, 
                                { itemId = 11000300, name = "灵魂印" }, 
                                { itemId = 11990011, name = "三番令" }, 
                                { itemId = 12041103, name = "活力丹" }, 
                                { itemId = 12030016, name = "队伍召集令" }, 
                                { itemId = 12030031, name = "神行符" }, 
                                { itemId = 11990015, name = "藏宝令" }, 
                                { itemId = 12030213, name = "强效极乐草" }, 
                                { itemId = 12030013, name = "芝华士" }, 
                                { itemId = 12030014, name = "轩尼诗理查" }, 
                                { itemId = 12030017, name = "哈瓦那雪茄" }, 
                                { itemId = 11000501, name = "紫檀木炭" }, 
                                { itemId = 12240002, name = "优质符文布" }, 
                                { itemId = 11000548, name = "炫彩强化石" }, 
}
-- 添加物品失败
x310365_g_strAddItemFailed  = "添加物品失败，请整理背包"
-- 小Boss列表
x310365_g_MonsterTableLittle= {                              
                                { monsterId=	17321	,ai=	1	,aiScript=	902, campId = 21, liveTime = -1 },	
																{ monsterId=	17322	,ai=	1	,aiScript=	902, campId = 21, liveTime = -1 },
																{ monsterId=	17323	,ai=	1	,aiScript=	902, campId = 21, liveTime = -1 },	
																{ monsterId=	17324	,ai=	1	,aiScript=	902, campId = 21, liveTime = -1 },	
																{ monsterId=	17325	,ai=	1	,aiScript=	902, campId = 21, liveTime = -1 },	
																{ monsterId=	17326	,ai=	1	,aiScript=	902, campId = 21, liveTime = -1 },	
																{ monsterId=	17327	,ai=	1	,aiScript=	902, campId = 21, liveTime = -1 },							
																{ monsterId=	17328	,ai=	1	,aiScript=	903, campId = 21, liveTime = -1 },	
																{ monsterId=	17329	,ai=	1	,aiScript=	903, campId = 21, liveTime = -1 },
																{ monsterId=	17330	,ai=	1	,aiScript=	903, campId = 21, liveTime = -1 },	
																{ monsterId=	17331	,ai=	1	,aiScript=	903, campId = 21, liveTime = -1 },	
																{ monsterId=	17332	,ai=	1	,aiScript=	903, campId = 21, liveTime = -1 },	
																{ monsterId=	17333	,ai=	1	,aiScript=	903, campId = 21, liveTime = -1	},	
																{ monsterId=	17320	,ai=	1	,aiScript=	903, campId = 21, liveTime = -1	},
                                
}
-- 大Boss列表
x310365_g_MonsterTableBig   = {
                                { monsterId = 17340, ai = 1, aiScript = 971, campId = 21, liveTime = -1 }, 
                                { monsterId = 17341, ai = 1, aiScript = 970, campId = 21, liveTime = -1 },
                                { monsterId = 17342, ai = 1, aiScript = 973, campId = 21, liveTime = -1 },
                                { monsterId = 17343, ai = 1, aiScript = 977, campId = 21, liveTime = -1 },
                                { monsterId = 17344, ai = 1, aiScript = 970, campId = 21, liveTime = -1 },
                                
}
x310365_g_BossA             = { monsterId = 17350, ai = 1, aiScript = 973, campId = 21, liveTime = -1 }
x310365_g_BossB             = { monsterId = 17351, ai = 1, aiScript = 973, campId = 21, liveTime = -1 }
-- 创建Boss随机位置配置表
x310365_g_MonsterPosTable   = {
                                { x = 88 , z = 90  }, 
                                { x = 100, z = 131 }, 
                                { x = 90 , z = 157 }, 
                                { x = 97 , z = 203 }, 
                                { x = 151, z = 197 }, 
                                { x = 192, z = 215 }, 
                                { x = 201, z = 178 }, 
                                { x = 149, z = 160 }, 
                                { x = 170, z = 84  },     
                                { x = 216, z = 120 }, 
                                { x = 127, z = 120 }, 
                                { x = 117, z = 223 }, 
                                { x = 65 , z = 129 }, 
                                { x = 205, z = 50  },     
                                { x = 55 , z = 192 },                                                           
}
-- open flag
x310365_g_IsEnableId        = 1046
-- random reward
x310365_g_RewardTable           = { 11010100, 11010101, 11010102 }

-- 玩家在天上人间·麒麟里退出游戏或掉线，再次进入游戏时的处理
function x310365_ProcMapPlayerNewConnectEnter( sceneId, selfId)

	local today = GetDayOfYear()
    local hour = GetHourMinSec()
    
	local lastDay = GetQuestData(sceneId, selfId, MD_DAGUANYUAN_DATE[1], MD_DAGUANYUAN_DATE[2], MD_DAGUANYUAN_DATE[3])
	if hour == 23 or hour < 9 or today ~= lastDay then

		-- 超过了上次进入的游乐场开放时间就把角色变身回去并放回大都南
		-- 做一个T人标记，在Buff里完成，直接T可能造成跨MapServer数据丢失
		--CancelSpecificImpact( sceneId, selfId, x310365_g_LanBuff)
		--CancelSpecificImpact( sceneId, selfId, x310365_g_HongBuff)
		--SetPlayerRuntimeData( sceneId, selfId, RD_DANCERY_BODYID, 1)
		SendSpecificImpactToUnit( sceneId, selfId, selfId, selfId, 8400, 0)
	end
end

function x310365_ProcEnumEvent( sceneId, selfId, NPCId, MissionId)
    if GetGameOpenById( x310365_g_IsEnableId) <= 0 then
        return
    end

    AddQuestNumText( sceneId, x310365_g_ScriptId, "我要给万妖壶增加灵气", 3, 1)
    AddQuestNumText( sceneId, x310365_g_ScriptId, "查询万妖壶的灵气指数", 3, 2)
    if x310365_GetMD( sceneId, selfId, MD_TJMJ_DATE) ~= GetDayOfYear() then
        x310365_SetMD( sceneId, selfId, MD_TJMJ_TIMES, 0)
    end
end

function x310365_ProcEventEntry( sceneId, selfId, NPCId, idScript, idExt)
    if GetGameOpenById( x310365_g_IsEnableId) <= 0 then
        return
    end

    if idExt == 1 then
        local exp =GetLevel( sceneId, selfId)*25920
        SetPlayerRuntimeData( sceneId, selfId, RD_COLLECT_HORSE, 1)
        BeginQuestEvent( sceneId)
            AddQuestText( sceneId, "#Y"..x310365_g_Name)
            AddQuestText( sceneId, "\t看见这个神奇的万妖壶了吗？这里面可有无数的千年老妖。\n\t你可以在我这里选择给万妖壶增加灵气，每次成功给万妖壶增加灵气，你都会获得丰厚的经验奖励，有时也会得到稀罕的宝贝。" )
            AddQuestText( sceneId, format("\n#Y奖励内容#W：\n经验值：%d点\n有几率获得#G双倍经验#W和#G修行草#W、#G灵魂印#W、#G三番令#W、#G活力丹#W、#G队伍召集令#W、#G定位符#W、#G藏宝令#W、#G强效极乐草#W、#G芝华士#W、#G轩尼诗理查#W、#G哈瓦那雪茄#W、#G紫檀木炭#W、#G优质符文布#W、#G炫彩强化石#W等珍稀道具。\n \n#G小提示：\n每人每天第一次给万妖壶增加灵气免费，其后每次需要消耗#R500文#G金卡/现金，灵气增加2点。\n \n当万妖壶的灵气指数到达#R100#G或#R100#G的整数倍时，魔王将会被释放在天上人间·梦聊内，消灭魔王更会获得大量的奖励！\n \n当万妖壶的灵气指数到达#R400#G或#R400#G的整数倍时，带有更多奖励的魔王将会被释放在天上人间·梦聊内！\n \n当万妖壶的灵气指数到达#R10000#G时，带有#R特有坐骑#G的魔王将会被释放在天上人间·梦聊内！\n \n当万妖壶的灵气指数到达#R20000#G时，带有#R绝世坐骑#G的魔王将会被释放在天上人间·梦聊内！）",exp))
        EndQuestEvent()
        DispatchQuestInfo( sceneId, selfId, NPCId, x310365_g_ScriptId, -1)
    elseif idExt == 2 then
        BeginQuestEvent( sceneId)
            AddQuestText( sceneId, "#Y"..x310365_g_Name)
            local rtimes = x310365_g_MaxTimesInDay
            if x310365_GetMD( sceneId, selfId, MD_TJMJ_DATE) == GetDayOfYear() then
                rtimes = x310365_g_MaxTimesInDay - x310365_GetMD( sceneId, selfId, MD_TJMJ_TIMES)
            end
            AddQuestText( sceneId, format( "\t现在万妖壶的灵气指数为#R%d#W点，你今天还可以给万妖壶增加#R%d#W次灵气。", x310365_g_GlobalCount, rtimes) )
        EndQuestEvent()
        DispatchQuestEventList( sceneId, selfId, NPCId)
    end
end

function x310365_ProcAcceptCheck( sceneId, selfId, NPCId)
    if GetGameOpenById( x310365_g_IsEnableId) <= 0 then
        return
    end

    local step = GetPlayerRuntimeData( sceneId, selfId, RD_COLLECT_HORSE)
    local today = GetDayOfYear()
    if step == 1 then
        if GetLevel( sceneId, selfId) < x310365_g_MinLevel then
            Msg2Player( sceneId, selfId, x310365_g_LessThanMinLevel, 8, 3)
            return 0
        end

        local times = x310365_GetMD( sceneId, selfId, MD_TJMJ_TIMES)
        -- print( "*-*-*-*-*", times)
        if x310365_GetMD( sceneId, selfId, MD_TJMJ_DATE) == today then
            if times >= x310365_g_MaxTimesInDay then
                Msg2Player( sceneId, selfId, x310365_g_strOverMaxTimes, 8, 3)
                return 0
            end
        else
            x310365_SetMD( sceneId, selfId, MD_TJMJ_TIMES, 0)
            x310365_SetMD( sceneId, selfId, MD_TJMJ_DATE, today)
            local weekIndex = GetWeekIndex()
            if weekIndex ~= x310365_GetMD( sceneId, selfId, MD_MOJUN_WEEK) then
            	x310365_SetMD( sceneId, selfId, MD_MOJUN_DUIHUAN, 0)
            end
            times = 0
        end

        if GetBagSpace( sceneId, selfId) < 1 then
            Msg2Player( sceneId, selfId, x310365_g_strNotEnoughBag, 8, 3)
            return 0
        end

        if times == 0 then
            -- 免费
            x310365_GiveReward( sceneId, selfId)
        else
            -- 确认是否花费金卡或现金
            SetPlayerRuntimeData( sceneId, selfId, RD_COLLECT_HORSE, 2)
            BeginQuestEvent( sceneId)
                AddQuestText( sceneId, "#Y"..x310365_g_Name)
                AddQuestText( sceneId, "\t本次给万妖壶增加灵气需要花费500文金卡或现金，是否继续？" )
            EndQuestEvent()
            DispatchQuestInfo( sceneId, selfId, NPCId, x310365_g_ScriptId, -1)
        end
    elseif step == 2 then
        if GetBagSpace( sceneId, selfId) < 1 then
            Msg2Player( sceneId, selfId, x310365_g_strNotEnoughBag, 8, 3)
            return 0
        end

        if x310365_GetMD( sceneId, selfId, MD_TJMJ_DATE) == today then
            if GetMoney( sceneId, selfId, 2) < x310365_g_CostMoney and GetMoney( sceneId, selfId, 3) < x310365_g_CostMoney then
                Msg2Player( sceneId, selfId, "你的金卡或现金不足", 8, 3)
                return 0
            end

            if GetGoldMode( sceneId, selfId) == 1 then
                if CostMoney( sceneId, selfId, 2, x310365_g_CostMoney,323) ~= 1 then
                    if CostMoney( sceneId, selfId, 3, x310365_g_CostMoney) ~= 1 then
                        Msg2Player( sceneId, selfId, "扣除金卡/现金失败，请稍候再试", 8, 3)
                        return 0
                    end
                end
            else
                if CostMoney( sceneId, selfId, 3, x310365_g_CostMoney) ~= 1 then
                    if CostMoney( sceneId, selfId, 2, x310365_g_CostMoney,323) ~= 1 then
                        Msg2Player( sceneId, selfId, "扣除金卡/现金失败，请稍候再试", 8, 3)
                        return 0
                    end
                end
            end
        else
            x310365_SetMD( sceneId, selfId, MD_TJMJ_TIMES, 0)
            x310365_SetMD( sceneId, selfId, MD_TJMJ_DATE, today)
        end

        x310365_GiveReward( sceneId, selfId)
        GamePlayScriptLog(sceneId, selfId, 1681)
    end

    return 1
end

function x310365_GiveReward( sceneId, selfId)
    -- 按随机值几率给经验
    local level = GetLevel( sceneId, selfId)
    local Probability = random( 1, 100)
    local xp = 0
    if Probability <= 75 then
        xp = level*25920
    else
        xp = level*25920*2
    end
    AddExp( sceneId, selfId, xp)
    Msg2Player( sceneId, selfId, format( "获得#R%d#cffcc00点经验。", xp), 8, 2)
	if Probability == 100 then
		LuaAllScenceM2Wrold( sceneId, format( "真是幸运！%s在天上人间·梦聊镇妖除魔的活动中意外的获得了%d点的超级经验奖励。", GetName( sceneId, selfId), level*25920*3, 1, 1))
	end
    -- 按随机值几率给物品奖励

    local index = 0
    local itemId = 0
    Probability = random( 1, 2000)
      if  Probability <=772 then
    		if Probability > 50 and Probability <= 52 then
    		    index = 2
    		elseif Probability > 52 and Probability <= 102 then
    		    index = 3
    		elseif Probability > 102 and Probability <= 152 then
    		    index = 4
    		elseif Probability > 152 and Probability <= 177 then
    		    index = 5
    		elseif Probability > 177 and Probability <= 187 then
    		    index = 6
    		elseif Probability > 187 and Probability <= 287 then
    		    index = 7
    		elseif Probability > 287 and Probability <= 337 then
    		    index = 8
    		elseif Probability > 337 and Probability <= 387 then
    		    index = 9
    		elseif Probability > 387 and Probability <= 412 then
    		    index = 10
    		elseif Probability > 412 and Probability <= 437 then
    		    index = 11
    		elseif Probability > 437 and Probability <= 462 then
    		    index = 12
    		elseif Probability > 462 and Probability <= 512 then
    		    index = 13
    		elseif Probability > 512 and Probability <= 772 then
    		    index = 14
            else
                index = 1
            end
        if index ~= 0 then
            itemId = x310365_g_ItemTable[ index].itemId
        end
    elseif Probability >= 1000 and Probability < 1340 then
        itemId = 11000598
    end
    if itemId ~= 0 then
    		BeginAddItem( sceneId)
        AddItem( sceneId, itemId, 1)
    		local bRes = EndAddItem( sceneId, selfId)
    		if bRes == 0 then
    		    Msg2Player( sceneId, selfId, x310365_g_strAddItemFailed, 8, 3)
    		    return
    		else
    		    AddItemListToPlayer( sceneId, selfId)
    		    if index == 15 then
            LuaThisScenceM2Wrold( sceneId, format( "真是幸运！%s在天上人间·梦聊镇妖除魔的活动中意外的获得了一个@item_%d。", GetName( sceneId, selfId), itemId), 1, 1)
    		    end
    		end
     end
     
    -- 更新全局计次
    x310365_g_GlobalCount = x310365_g_GlobalCount + 2
    if mod( x310365_g_GlobalCount, 20000) == 0 then
        -- 召唤BossB
        local pos = x310365_g_MonsterPosTable[ random( 1, getn( x310365_g_MonsterPosTable) ) ]
        CreateMonster( sceneId, x310365_g_BossB.monsterId, pos.x, pos.z, x310365_g_BossB.ai, x310365_g_BossB.aiScript, x310365_g_ScriptId, -1, x310365_g_BossB.campId, x310365_g_BossB.liveTime)
        LuaThisScenceM2Wrold( sceneId, format( "在大家的努力下，威力无比的大魔头被万妖壶释放出来，在天上人间·梦聊内（%s，%d）出现了！各位英雄速去将其剿灭！", pos.x, pos.z), 1, 1)
        LuaThisScenceM2Wrold( sceneId, format( "大魔头出现！（%s，%d）", pos.x, pos.z), 5, 1)
    elseif mod( x310365_g_GlobalCount, 10000) == 0 then
        -- 召唤BossA
        local pos = x310365_g_MonsterPosTable[ random( 1, getn( x310365_g_MonsterPosTable) ) ]
        CreateMonster( sceneId, x310365_g_BossA.monsterId, pos.x, pos.z, x310365_g_BossA.ai, x310365_g_BossA.aiScript, x310365_g_ScriptId, -1, x310365_g_BossA.campId, x310365_g_BossA.liveTime)
        LuaThisScenceM2Wrold( sceneId, format( "在大家的努力下，威力无比的大魔头被万妖壶释放出来，在天上人间·梦聊内（%s，%d）出现了！各位英雄速去将其剿灭！", pos.x, pos.z), 1, 1)
        LuaThisScenceM2Wrold( sceneId, format( "大魔头出现！（%s，%d）", pos.x, pos.z), 5, 1)
    elseif mod( x310365_g_GlobalCount, 400) == 0 then
        -- 召唤大Boss
        local boss = x310365_g_MonsterTableBig[ random( 1, getn( x310365_g_MonsterTableBig) ) ]
        local pos = x310365_g_MonsterPosTable[ random( 1, getn( x310365_g_MonsterPosTable) ) ]
        CreateMonster( sceneId, boss.monsterId, pos.x, pos.z, boss.ai, boss.aiScript, x310365_g_ScriptId, -1, boss.campId, boss.liveTime)
        LuaThisScenceM2Wrold( sceneId, format( "在大家的努力下，威力无比的大魔头被万妖壶释放出来，在天上人间·梦聊内（%s，%d）出现了！各位英雄速去将其剿灭！", pos.x, pos.z), 1, 1)
        LuaThisScenceM2Wrold( sceneId, format( "大魔头出现！（%s，%d）", pos.x, pos.z), 5, 1)
    elseif mod( x310365_g_GlobalCount, 100) == 0 then
        -- 召唤小Boss
        local boss = x310365_g_MonsterTableLittle[ random( 1, getn( x310365_g_MonsterTableLittle) ) ]
        local pos = x310365_g_MonsterPosTable[ random( 1, getn( x310365_g_MonsterPosTable) ) ]
        CreateMonster( sceneId, boss.monsterId, pos.x, pos.z, boss.ai, boss.aiScript, x310365_g_ScriptId, -1, boss.campId, boss.liveTime)
        LuaThisScenceM2Wrold( sceneId, format( "在大家的努力下，威力无比的大魔头被万妖壶释放出来，在天上人间·梦聊内（%s，%d）出现了！各位英雄速去将其剿灭！", pos.x, pos.z), 1, 1)
        LuaThisScenceM2Wrold( sceneId, format( "大魔头出现！（%s，%d）", pos.x, pos.z), 5, 1)
    end

    x310365_SetMD( sceneId, selfId, MD_TJMJ_TIMES, x310365_GetMD( sceneId, selfId, MD_TJMJ_TIMES) + 1)

    if random( 1, 100) <= 5 then
        BeginAddItem( sceneId)
        AddItem( sceneId, x310365_g_RewardTable[ random( 1, 3) ], 1)
        if EndAddItem( sceneId, selfId) == 0 then
            Msg2Player( sceneId, selfId, "背包已满，无法获得额外奖励物品", 8, 3)
        else
            AddItemListToPlayer( sceneId, selfId)
        end
    end

    Msg2Player( sceneId, selfId, format( "灵气增加成功(%d/%d)", x310365_GetMD( sceneId, selfId, MD_TJMJ_TIMES), x310365_g_MaxTimesInDay), 8, 3)
end

function x310365_ProcAccept( sceneId, selfId, NPCId)
end

function x310365_OnDie( sceneId, selfId, killerId)
end

function x310365_GetMD( sceneId, selfId, mdName)
    return GetQuestData( sceneId, selfId, mdName[ 1], mdName[ 2], mdName[ 3] )
end

function x310365_SetMD( sceneId, selfId, mdName, value)
    SetQuestData( sceneId, selfId, mdName[ 1], mdName[ 2], mdName[ 3], value)
end

function x310365_OnTimerDoingStart( sceneId, actId, Param1, Param2, Param3, Param4, Param5)
    if sceneId ~= 40 then
        return
    end

    x310365_g_GlobalCount = 0
end
