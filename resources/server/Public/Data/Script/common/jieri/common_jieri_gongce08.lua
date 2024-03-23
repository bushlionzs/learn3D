-- 糖果

x350007_g_ScriptId 					= 350007


-- 普通许愿种子消耗配置表
x350007_g_OrdinarySeedTable         = {
                                        { useCount = 1,  deplete = 3, scoreDown = 5, scoreUp = 15 }, 
                                        { useCount = 2,  deplete = 3, scoreDown = 5, scoreUp = 15 }, 
                                        { useCount = 3,  deplete = 3, scoreDown = 5, scoreUp = 15 }, 
                                        { useCount = 4,  deplete = 3, scoreDown = 5, scoreUp = 15 }, 
                                        { useCount = 5,  deplete = 3, scoreDown = 5, scoreUp = 15 }, 
                                        { useCount = 6,  deplete = 3, scoreDown = 5, scoreUp = 15 }, 
                                        { useCount = 7,  deplete = 3, scoreDown = 5, scoreUp = 15 }, 
                                        { useCount = 8,  deplete = 3, scoreDown = 5, scoreUp = 15 }, 
                                        { useCount = 9,  deplete = 3, scoreDown = 5, scoreUp = 15 }, 
                                        { useCount = 10, deplete = 3, scoreDown = 5, scoreUp = 15 }, 
                                        { useCount = 11, deplete = 3, scoreDown = 5, scoreUp = 15 }, 
                                        { useCount = 12, deplete = 3, scoreDown = 5, scoreUp = 15 }, 
                                        { useCount = 13, deplete = 3, scoreDown = 5, scoreUp = 15 }, 
                                        { useCount = 14, deplete = 3, scoreDown = 5, scoreUp = 15 }, 
                                        { useCount = 15, deplete = 3, scoreDown = 5, scoreUp = 15 }, 
                                        { useCount = 16, deplete = 3, scoreDown = 5, scoreUp = 15 }, 
}
-- 神奇种子列表
x350007_g_SeedTable					= {
                                        { itemId = 11010015, buttonId = 1, maxTimes = 16, useMode = 0, tableid = x350007_g_OrdinarySeedTable, actName = "许愿", 
                                          dayMD = MD_HOPESEED_DAY,     timesMD = MD_GOLDHOPESEED_TIMES, name = "【活动】节日许愿" },
                                        { itemId = 11010017, buttonId = 2, maxTimes = 1, useMode = 1, tableid = x350007_g_OrdinarySeedTable, actName = "祈福", 
                                         dayMD = MD_LUCKSEED_DAY,     timesMD = MD_LUCKSEED_TIMES,     name = "【活动】节日祈福" },
}
-- 祈福种子消耗获得物品配置表
x350007_g_LuckySeedTable            = {
                                        { itemId = 12041101, probability = 75000, price = 0.8,  name = "修行草",        }, 
                                        { itemId = 12030202, probability = 25000, price = 1,    name = "江湖请柬",          }, 
                                        { itemId = 12030203, probability = 25000, price = 1,    name = "朝廷请柬",          }, 
                                        { itemId = 11990011, probability = 50000, price = 0.99, name = "三番令",        }, 
                                        { itemId = 12030405, probability = 60000,  price = 2,    name = "活力特惠包",        }, 
                                        { itemId = 12030200, probability = 25000,  price = 2,    name = "小喇叭",        },                          
                                        { itemId = 12054300, probability = 25000,  price = 2,    name = "还童书",      }, 
                                        { itemId = 12030201, probability = 50000,  price = 2,    name = "修理石",      }, 
                                        { itemId = 12030018, probability = 50000,  price = 4,    name = "蒙面巾",          }, 
                                        { itemId = 12030013, probability = 50000,  price = 5,    name = "芝华士",          }, 
                                        { itemId = 11990110, probability = 60000,  price = 5,    name = "募集卷",          }, 
                                        { itemId = 12030031, probability = 50000,  price = 5,    name = "神行符",          }, 
                                        { itemId = 12030016, probability = 50000,   price = 10,   name = "队伍召集令", }, 
                                        { itemId = 12041102, probability = 50000,   price = 10,   name = "天赋丹", }, 
                                        { itemId = 12010023, probability = 1000 ,   price = 10,   name = "大生命清露", }, 
                                        { itemId = 11990400, probability = 60000,   price = 10,   name = "融合剂", },
                                        { itemId = 12050100, probability = 1000 ,   price = 10,   name = "归元丹", },  
                                     	{ itemId = 12030502, probability = 1000 ,   price = 50,   name = "宫廷时装礼包", },
                                        { itemId = 10340010, probability = 1000 ,   price = 10,   name = "三彩护身符", },
                                     	{ itemId = 12030503, probability = 25000,   price = 50,   name = "掌门牌平胡礼包", },
                                        { itemId = 11000300, probability = 1000 ,   price = 10,   name = "灵魂印", },     
                                        { itemId = 11000501, probability = 60000,   price = 10,   name = "紫檀木炭", }, 
                                        { itemId = 11000902, probability = 50000,   price = 10,   name = "高级洗石剂", }, 
                                        { itemId = 11000800, probability = 25000,   price = 10,   name = "离石剂", }, 
                                        { itemId = 12030018, probability = 25000,   price = 10,   name = "蒙面巾", }, 
                                        { itemId = 11000544, probability = 54859,   price = 10,   name = "蓝光火石", }, 
                                        { itemId = 11000598, probability = 25000,   price = 10,   name = "五彩石", }, 
                                        { itemId = 11010001, probability = 25000,   price = 10,   name = "一级皇家秘银", }, 
                                        { itemId = 12030504, probability = 14,   price = 50,   name = "熊猫降世符礼包", }, 
                                        { itemId = 12030505, probability = 100,   price = 50,   name = "节日时装礼包", }, 
                                        { itemId = 12030506, probability = 10,   price = 50,   name = "掌门牌碰碰胡礼包", }, 
                                       	{ itemId = 12030507, probability = 10,   price = 50,   name = "掌门牌清一色礼包", }, 
                                       	{ itemId = 12030508, probability = 7,   price = 50,   name = "掌门牌大三元礼包", }, 

}
-- 月饼表
    x350007_g_Yuebing                   = {
                                            { itemId = 12030251, name = "三财月饼", lvDown = 30, lvUp = 40       }, 
                                            { itemId = 12030252, name = "四喜月饼", lvDown = 40, lvUp = 50       }, 
                                            { itemId = 12030253, name = "五仁月饼", lvDown = 50, lvUp = 60       }, 
                                            { itemId = 12030254, name = "六味月饼", lvDown = 60, lvUp = 70       }, 
                                            { itemId = 12030255, name = "七星月饼", lvDown = 70, lvUp = 80       }, 
                                            { itemId = 12030256, name = "八宝月饼", lvDown = 80, lvUp = 90       }, 
}
-- 积分最大值
x350007_g_MaxScore                  = 131072

--**********************************
--点击NPC
--**********************************
function x350007_ProcEnumEvent( sceneId, selfId, targetId, MissionId)
    if GetLevel( sceneId, selfId) < 40 then
        return
    end

    local day = GetDayOfYear()
    if day >= 263 and day <= 276 then
	    for i, iter in x350007_g_SeedTable do
	        AddQuestNumText( sceneId, x350007_g_ScriptId, iter.name, 3, iter.buttonId)
	    end
	    AddQuestNumText( sceneId, x350007_g_ScriptId, "【活动】积分查询", 3, 5)
        AddQuestNumText( sceneId, x350007_g_ScriptId, "节日积分商店", 10, 6)
        AddQuestNumText( sceneId, x350007_g_ScriptId, "种子商店", 10, 7)
    end
    -- print( GetQuestData( sceneId, selfId, MD_SEED_SCORE[ 1], MD_SEED_SCORE[ 2], MD_SEED_SCORE[ 3] ) )
end

--**********************************
--执行默认事件
--**********************************
function x350007_ProcEventEntry( sceneId, selfId, targetId, state, index)
    if index >= 1 and index <= getn( x350007_g_SeedTable) then  
        local strInfo = ""
        local strInfo1 = ""
        local strInfo2 = ""
        local strTitle = "#Y"..x350007_g_SeedTable[ index].name

        if GetDayOfYear() ~= GetQuestData( sceneId, selfId, x350007_g_SeedTable[ index].dayMD[ 1], x350007_g_SeedTable[ index].dayMD[ 2], x350007_g_SeedTable[ index].dayMD[ 3] ) then
            SetQuestData( sceneId, selfId, x350007_g_SeedTable[ index].timesMD[ 1], x350007_g_SeedTable[ index].timesMD[ 2], x350007_g_SeedTable[ index].timesMD[ 3], 0)
            SetQuestData( sceneId, selfId, x350007_g_SeedTable[ index].dayMD[ 1],   x350007_g_SeedTable[ index].dayMD[ 2],   x350007_g_SeedTable[ index].dayMD[ 3], GetDayOfYear() )
        end
        if x350007_g_SeedTable[ index].useMode == 0 then
            local needSeed = GetQuestData( sceneId, selfId, x350007_g_SeedTable[ index].timesMD[ 1], x350007_g_SeedTable[ index].timesMD[ 2], x350007_g_SeedTable[ index].timesMD[ 3] ) + 1
            if  needSeed > x350007_g_SeedTable[ index].maxTimes then
                BeginQuestEvent( sceneId)
                    AddQuestText( sceneId, "#Y许愿种子" )
                    AddQuestText( sceneId, "\n\t许愿种子，代表着真诚的许诺和美好的愿望，使用许愿种子后，可以让好运一直伴随在你的身边。" )
                    AddQuestText( sceneId, "\n\t许愿种子每天最多可以许愿#R十六#W次。#r" )
                    AddQuestText( sceneId, "\t您今日已经许愿十六次了，请明日再来。" )
                EndQuestEvent()
                DispatchQuestEventList( sceneId, selfId, targetId)
                return
            end
            strInfo = "\t许愿种子，代表着真诚的许诺和美好的愿望，使用许愿种子后，可以让好运一直伴随在你的身边。"
            strInfo1 = format( "#G小提示:#G\n\t节日许愿每天可进行十六次许愿，每次需要三个许愿种子。\t\n\t#W您现在是第#R%d#W次使用，需要#R3#W个@item_%d#W。", needSeed, x350007_g_SeedTable[ index].itemId)
            strInfo2 = "#Y奖励内容:#W\n\t活动积分 "
        else
            strInfo = "\t祈福种子，代表着衷心的祈祷和善意的祝福，使用祈福种子之后，有可能会获得神秘的礼物哦。"
            strInfo1 = format( "#G小提示:\n\t#G每天都可以进行祈福，每次祈福需要一个祈福种子，祈福种子可以从领奖大使处购得。\t\n\t\n\t#W您是否要使用#R1#W个@item_%d#W?", x350007_g_SeedTable[ index].itemId)
            strInfo2 = "#Y奖励内容:\n\t#W\神秘道具 "
        end
        BeginQuestEvent( sceneId)
            --任务信息
            AddQuestText( sceneId, strTitle)
            AddQuestText( sceneId, " " )
            AddQuestText( sceneId, strInfo)
            AddQuestText( sceneId, " " )
            AddQuestText( sceneId, strInfo1)
            AddQuestText( sceneId, " " )
            AddQuestText( sceneId, strInfo2)
            AddQuestText( sceneId, " " )
            SetPlayerRuntimeData( sceneId, selfId, RD_COLLECT_HORSE, index)
        EndQuestEvent()
        DispatchQuestInfo( sceneId, selfId, targetId, x350007_g_ScriptId, -1)
    end

    if index == 5 then
        BeginQuestEvent( sceneId)
            AddQuestText( sceneId, "#Y【活动】积分查询" )
            AddQuestText( sceneId, format( "\n\t您目前的节日积分为#G%d#W。", GetQuestData( sceneId, selfId, MD_SEED_SCORE[ 1], MD_SEED_SCORE[ 2], MD_SEED_SCORE[ 3] ) ) )
        EndQuestEvent()
        DispatchQuestEventList( sceneId, selfId, targetId)
    end

    if index == 6 then
        DispatchShopItem( sceneId, selfId, targetId, 1104)
    end
    if index == 7 then
        DispatchShopItem( sceneId, selfId, targetId, 1105)
    end
end

-- 当日使用次数检查是否可用，如果可用返回1，否则返回0
function x350007_CheckUseTimes( sceneId, selfId, dayMD, timesMD, maxTimes)
    local result = 1

    if GetDayOfYear() == GetQuestData( sceneId, selfId, dayMD[ 1], dayMD[ 2], dayMD[ 3] ) then
        if GetQuestData( sceneId, selfId, timesMD[ 1], timesMD[ 2], timesMD[ 3] ) >= maxTimes then
            result = 0
        end
    else
        SetQuestData( sceneId, selfId, timesMD[ 1], timesMD[ 2], timesMD[ 3], 0)
    end

    return result
end

--**********************************
--检测
--**********************************
function x350007_ProcAcceptCheck( sceneId, selfId, targetId)
    local index = GetPlayerRuntimeData( sceneId, selfId, RD_COLLECT_HORSE)

    for i, iter in x350007_g_SeedTable do
        if index == iter.buttonId then
            -- 检查身上携带数量
            local iCount = GetItemCountInBag( sceneId, selfId, iter.itemId)
            if iCount == 0 then
                Msg2Player( sceneId, selfId, format( "您没有@item_%d", iter.itemId), 8, 3)
                return
            end
            -- 检查当日使用次数
            if iter.useMode == 0 and x350007_CheckUseTimes( sceneId, selfId, iter.dayMD, iter.timesMD, iter.maxTimes) == 0 then
                Msg2Player( sceneId, selfId, format( "您今天%s次数已达十六次，不能继续%s", iter.actName, iter.actName), 8, 3)
                return
            end
            local needSeed = GetQuestData( sceneId, selfId, iter.timesMD[ 1], iter.timesMD[ 2], iter.timesMD[ 3] ) + 1
            if iter.useMode == 0 and iCount < iter.tableid[ needSeed].deplete then
                Msg2Player( sceneId, selfId, format( "您的@item_%d#cffcc00不足#R%d#cffcc00颗，无法%s", iter.itemId, iter.tableid[ needSeed].deplete, iter.actName), 8, 3)
                return
            end
            local score = GetQuestData( sceneId, selfId, MD_SEED_SCORE[ 1], MD_SEED_SCORE[ 2], MD_SEED_SCORE[ 3] )
            if iter.useMode == 0 and score == x350007_g_MaxScore then
                Msg2Player( sceneId, selfId, format( "您的积分已达最大值，不能再使用@item_%d", iter.itemId), 8, 3)
                return
            end
            if iter.useMode == 1 then
                -- 祈福种子
                local result = random( 1, 1000000)
                -- print( "*-*-*-*-*"..result)
                local top = 1
                local bottom = 1
                local itemIndex = 1
                for i, item in x350007_g_LuckySeedTable do
                    top = top + item.probability
                    if result >= bottom and result < top then
                        itemIndex = i
                        break
                    end
                    bottom = bottom + item.probability
                end
                local itemId = x350007_g_LuckySeedTable[ itemIndex].itemId
            --- if itemIndex == 1 then
            ---     -- 根据等级给对应的月饼
            ---     local lv = GetLevel( sceneId, selfId)
            ---     for i, item in x350007_g_Yuebing do
            ---         if lv >= item.lvDown and lv < item.lvUp then
            ---             itemId = item.itemId
            ---             break
            ---         end
            ---     end
            --- end
                local isBind = 0
                local bagPos = 0
                for i = 0, 108 do
                	local id = GetItemIDByIndexInBag( sceneId, selfId, i)
                	if id == iter.itemId then
                		if IsItemBind( sceneId, selfId, i) > 0 then
                			isBind = 1
                            bagPos = i
                			break
                		end
                	end
                end
                local broadcast = 0
                local itemname = ""
                if x350007_g_LuckySeedTable[ itemIndex].price >= 45 then
                    broadcast = 1
                    itemname = x350007_g_LuckySeedTable[ itemIndex].name
                end
                BeginAddItem( sceneId) 
                if isBind == 1 then
                	AddBindItem( sceneId, itemId, 1)
                else
	                AddItem( sceneId, itemId, 1)
                end
                if GetBagSpace( sceneId, selfId) > 0 and EndAddItem( sceneId, selfId) > 0 then
                    if isBind == 1 then
                    if DelItemByIndexInBag( sceneId, selfId, bagPos, 1) == 0 then
                        Msg2Player( sceneId, selfId, format( "提交@item_%d#cffcc00失败", iter.itemId), 8, 3)
                        return
                        end
                    else
                        if DelItem( sceneId, selfId, iter.itemId, 1) == 0 then
                            Msg2Player( sceneId, selfId, format( "提交@item_%d#cffcc00失败", iter.itemId), 8, 3)
                            return
                        end
                    end
                    AddItemListToPlayer( sceneId, selfId)
                    Msg2Player( sceneId, selfId, format( "您获得了@item_%d#cffcc00。", itemId), 8, 2)
                    BeginQuestEvent( sceneId)
                        AddQuestText( sceneId, "#Y"..iter.name)
                        AddQuestText( sceneId, format( "\n您获得了@item_%d#W。", itemId) )
                    EndQuestEvent()
                    DispatchQuestEventList( sceneId, selfId, targetId)
                    if broadcast == 1 then
                        LuaAllScenceM2Wrold( sceneId, format( "恭喜%s使用祈福种子获得了%s", GetName( sceneId, selfId), itemname), 5, 1)
                    end

                    -- write log
                    GamePlayScriptLog( sceneId, selfId, 1372)
                else
                    Msg2Player( sceneId, selfId, "无法获得物品，请整理您的背包", 8, 3)
                    return
                end
            else
                if DelItem( sceneId, selfId, iter.itemId, iter.tableid[ needSeed].deplete) == 0 then
                    Msg2Player( sceneId, selfId, format( "提交@item_%d#cffcc00失败", iter.itemId), 8, 3)
                    return
                end
                -- 许愿种子
                local add = random( iter.tableid[ needSeed].scoreDown, iter.tableid[ needSeed].scoreUp)
                score = score + add
                if score > x350007_g_MaxScore then
                    score = x350007_g_MaxScore
                end
                SetQuestData( sceneId, selfId, MD_SEED_SCORE[ 1], MD_SEED_SCORE[ 2], MD_SEED_SCORE[ 3], score)
                SetFeastScore( sceneId, selfId, GetQuestData( sceneId, selfId, MD_SEED_SCORE[ 1], MD_SEED_SCORE[ 2], MD_SEED_SCORE[ 3] ) )
                Msg2Player( sceneId, selfId, format( "您获得#R%d#cffcc00点积分，总积分#G%d", add, score), 8, 3)
                BeginQuestEvent( sceneId)
                    AddQuestText( sceneId, "#Y"..iter.name)
                    AddQuestText( sceneId, format( "\n\t恭喜您获得#R%d#W点积分，总积分为#G%d#W分。", add, score) )
                EndQuestEvent()
                DispatchQuestEventList( sceneId, selfId, targetId)

                -- write log
                GamePlayScriptLog( sceneId, selfId, 1382)
            end
            local times = GetQuestData( sceneId, selfId, iter.timesMD[ 1], iter.timesMD[ 2], iter.timesMD[ 3] )
            SetQuestData( sceneId, selfId, iter.timesMD[ 1], iter.timesMD[ 2], iter.timesMD[ 3], times + 1)
            break
        end
    end
end

--**********************************
--接受
--**********************************
function x350007_ProcAccept( sceneId, selfId)
end

--**********************************
--放弃
--**********************************
function x350007_ProcQuestAbandon( sceneId, selfId, MissionId)

end

--**********************************
--继续
--**********************************
function x350007_OnContinue( sceneId, selfId, targetId)

end

--**********************************
--检测是否可以提交
--**********************************
function x350007_CheckSubmit( sceneId, selfId)

end

--**********************************
--提交
--**********************************
function x350007_ProcQuestSubmit( sceneId, selfId, targetId, index, MissionId)

end

--**********************************
--杀死怪物或玩家
--**********************************
function x350007_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId)

end

--**********************************
--进入区域事件
--**********************************
function x350007_ProcAreaEntered( sceneId, selfId, zoneId, MissionId)
end

--**********************************
--道具改变
--**********************************
function x350007_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId)
end

-- 更新节日积分，在节日积分商店消费后调用此函数更新MD
function x350007_UpdateFeastScore( sceneId, selfId, newScore)
    SetQuestData( sceneId, selfId, MD_SEED_SCORE[ 1], MD_SEED_SCORE[ 2], MD_SEED_SCORE[ 3], newScore)
    SetFeastScore( sceneId, selfId, GetQuestData( sceneId, selfId, MD_SEED_SCORE[ 1], MD_SEED_SCORE[ 2], MD_SEED_SCORE[ 3] ) )
end



