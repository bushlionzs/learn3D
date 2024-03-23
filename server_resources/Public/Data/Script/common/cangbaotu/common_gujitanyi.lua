--MisDescBegin

-- 草原三宝任务脚本ID
x300340_g_ScritpId = 300340
-- 任务ID
x300340_g_MissionId = 8051
-- 接任务最小等级
x300340_g_LevelLess = 20
-- 任务名称
x300340_g_MissionName           = "【个人】草原三宝"
-- 
x300340_g_NeedGold = 10000
x300340_g_KillMissionId =  7012
x300340_g_Material_Thread = 13011010

-- “诱兽炉香”物品ID
x300340_g_MissionPropertyId =  12030021

x300340_g_AwardItemId = 13011012 --奖励物品id

x300340_g_ExpBonus					= 	0                    	--奖励：经验 （数值填0，字符串为空，表示没有该项奖励）
x300340_g_BonusItem					=	{}	--奖励：物品

x300340_g_BonusMoney1               = 	0  --任务奖励绑定银币
x300340_g_BonusMoney2               =   0  --任务奖励非绑定银币
x300340_g_BonusMoney3               =   0  --任务奖励绑定金币
x300340_g_BonusMoney4               =   0  --任务奖励朝廷声望
x300340_g_BonusMoney5               =   0  --任务奖励江湖声望
x300340_g_BonusMoney6               =   0  --任务奖励荣誉

x300340_g_BonusChoiceItem           =   {}

--MisDescEnd

x300340_g_MissionTable              = {
                                        { minLevel = 20, maxLevel = 40, placeId = 36, placeName = "@npcsp_温泉谷_82004",  itemId = 13013100, itemName = "珍宝皮毛",	monsterName="生物" }, 
                                        { minLevel = 40, maxLevel = 60, placeId = 37, placeName = "@npcsp_风陵山_82005",  itemId = 13013101, itemName = "明目胆汁",	monsterName="生物" }, 
                                        { minLevel = 60, maxLevel = 9999, placeId = 39, placeName = "@npcsp_黄叶林_82006",  itemId = 13013102, itemName = "血玉骨",	monsterName="生物" }
}

-- 任务描述

x300340_g_MissionDescription    = "\t辽阔草原中，生物所带来的不仅是肥美的鲜肉，有些入药至宝都是不可多得的珍品，不知道你可否知道#G草原三宝#W一说，我就在收集它们。\n\t前往#G%s#W，到其中击败%s，收集100个@item_%d#W后交给我。\n\t这里有一个@item_12030021#W，现在送给你，请在草原生物密集的#G%s#W中使用吧！如果觉得好用的话可以去@npc_138502那里购买。"
-- 任务提示
x300340_g_MissionHelp           = "\t#G诱兽炉香可以让迷宫中的生物必定掉落任务所需的物品，如果你需要更多的话，请去@npc_138502那里买吧。"
-- 任务目标
x300340_g_strMissionTarget      = "  到%s收集@item_%d#W(%d/100)"
-- 放弃任务提示字符
x300340_g_strMissionAbandon     = "你放弃了任务：【个人】草原三宝"
-- 任务完成字符串
x300340_g_strMissionComplete    = "你完成了任务：【个人】草原三宝"
-- 接受任务提示
x300340_g_strMissionAccept      = "你接受了任务：【个人】草原三宝"
-- 任务继续信息
x300340_g_MissionContinue       = "\t请你前往#G%s#W，到其中击败草原%s，收集100个#G%s#W后交给我。"

x300340_g_MissionProcess				=	"\t请你前往#G%s#W，到其中击败草原生物，收集100个@item_%d#W。"
-- “诱兽炉香”的持续时间（秒）
x300340_g_FanqiTime             = 180
-- “诱兽炉香”的作用范围
x300340_g_Range                 = 4
-- 任务回复NPC
x300340_g_NPC                   = "@npc_138558"
-- 完成任务要收集的物品数量
x300340_g_FinishCount           = 100
-- 任务收集目标物品的ID
x300340_g_MP_TargetItemId       = 1
-- 使用“诱兽炉香”X坐标
x300340_g_MP_PosX               = 2
-- 使用“诱兽炉香”Z坐标
x300340_g_MP_PosZ               = 3
-- 使用“诱兽炉香”时间
x300340_g_MP_UseTime            = 4
-- 任务目标场景
x300340_g_MP_TargetScene        = 5
-- 银卡奖励系数
x300340_g_MoneyCoefficient      = 300
-- 经验系数
x300340_g_ExperienceCoefficient = 3000

function x300340_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
    if GetLevel( sceneId, selfId) >= x300340_g_LevelLess then
        local state = GetQuestStateNM( sceneId, selfId, targetId, MissionId)
        -- print( state)
        AddQuestNumText( sceneId, x300340_g_MissionId, x300340_g_MissionName, state)
    end
end

function x300340_ProcEventEntry( sceneId, selfId, targetId, MissionId )
    if IsHaveQuestNM( sceneId, selfId, MissionId ) == 0 then	-- 如果没有这个任务    
        -- 显示接受任务信息
        x300340_DispatchMissionInfo( sceneId, selfId, targetId)
    else--检查是不是可以提交    
		local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId)
        local isFinish = GetQuestParam( sceneId, selfId, misIndex, 7)
        local itemId = GetQuestParam( sceneId, selfId, misIndex, x300340_g_MP_TargetItemId)
		if isFinish > 0 and GetItemCountInBag( sceneId, selfId, itemId) >= 100 then -- 如果任务可以完成
			x300340_MissionComplateInfo( sceneId, selfId, targetId, MissionId) -- 显示完成信息
		else
            --print( "***********" )
			x300340_MissionContinue( sceneId, selfId, targetId, MissionId) -- 显示任务未完成信息
		end
    end
end

-- 任务继续信息
function x300340_MissionContinue( sceneId, selfId, targetId, MissionId)
    local misIndex = GetQuestIndexByID( sceneId, selfId, x300340_g_MissionId)
    local taritem = GetQuestParam( sceneId, selfId, misIndex, x300340_g_MP_TargetItemId)
    local strItem = ""
    local strPalace = ""
    local strMonster = ""
    for i, item in x300340_g_MissionTable do
        if item.itemId == taritem then
            strItem = item.itemName
            strPalace = item.placeName
            strMonster = item.monsterName
            break
        end
    end
	BeginQuestEvent( sceneId)
		AddQuestText( sceneId, "#Y"..x300340_g_MissionName)
        AddQuestText( sceneId, format( x300340_g_MissionContinue, strPalace, strMonster, strItem) )

	EndQuestEvent()
    DispatchQuestEventList( sceneId, selfId, targetId)
end

-- 显示接受任务信息
function x300340_DispatchMissionInfo( sceneId, selfId, NPCId )
	local level = GetLevel( sceneId, selfId)
    local bFind = 0
    local strDescription = ""
    local itemId = 0
    local baseScene = ( GetCurCountry( sceneId, selfId) ) * 100 + 50

    -- 根据玩家等级得出任务场景和物品
    for i, item in x300340_g_MissionTable do
        if level >= item.minLevel and level < item.maxLevel then
            SetPlayerRuntimeData( sceneId, selfId, RD_GUJI_SCENEID, baseScene + item.placeId)
            SetPlayerRuntimeData( sceneId, selfId, RD_GUJI_ITEMID, item.itemId)
            itemId = item.itemId
            strDescription = format( x300340_g_MissionDescription, item.placeName, item.monsterName, item.itemId, item.placeName)
            bFind = 1
            break
        end
    end

    if bFind == 0 then
        return
    end

	BeginQuestEvent( sceneId)

		--任务信息
		AddQuestText( sceneId, "#Y"..x300340_g_MissionName)
		AddQuestText( sceneId, strDescription)

		--任务目标
		AddQuestText( sceneId, "#Y任务目标：")
		AddQuestText( sceneId, format( "收集@item_%d#W。", itemId ) )
		AddQuestText( sceneId, " ")
		AddQuestText( sceneId, " ")

		--提示信息
        AddQuestText( sceneId, "#Y小提示：")
        AddQuestText( sceneId, x300340_g_MissionHelp)
        -- AddQuestText( sceneId, " ")

		--任务奖励信息

		--1、经验
		local exp = GetLevel( sceneId, selfId) * x300340_g_ExperienceCoefficient
		if exp > 0 then
			AddQuestExpBonus( sceneId, exp)
		end

		--2、金钱1
        local money = level * x300340_g_MoneyCoefficient
		if money > 0 then
			AddQuestMoneyBonus1( sceneId, money)
		end

		--3、金钱2
		if x300340_g_BonusMoney2 > 0 then
			AddQuestMoneyBonus2(sceneId, x300340_g_BonusMoney2 )
		end

		--4、金钱3
		if x300340_g_BonusMoney3 > 0 then
			AddQuestMoneyBonus3(sceneId, x300340_g_BonusMoney3 )
		end

		--江湖声望
		if x300340_g_BonusMoney4 > 0 then
			AddQuestMoneyBonus4(sceneId, x300340_g_BonusMoney4 )
		end

		--朝廷声望
		if x300340_g_BonusMoney5 > 0 then
			AddQuestMoneyBonus5(sceneId, x300340_g_BonusMoney5 )
		end

		--荣誉值
		if x300340_g_BonusMoney6 > 0 then
			AddQuestMoneyBonus6(sceneId, x300340_g_BonusMoney6 )
		end

		--5、固定物品
		for i, item in x300340_g_BonusItem do
		   	AddQuestItemBonus(sceneId, item.item, item.n)
	    end

		--6、可选物品
		for i, item in x300340_g_BonusChoiceItem do
	    	AddQuestRadioItemBonus(sceneId, item.item, item.n)
	    end

	EndQuestEvent()

	DispatchQuestInfoNM( sceneId, selfId, NPCId, x300340_g_ScritpId, x300340_g_MissionId);
end

-- 检查当天是否已经接受过这个任务，接受过返回1，否则返回0
function x300340_CheckDayTimes( sceneId, selfId)
    local today = GetDayOfYear()

    if x300340_GetAcceptTime( sceneId, selfId) ~= today then
        return 0
    else
        return 1
    end
end

function x300340_ProcQuestAccept(sceneId, selfId, targetId, MissionId)
    if IsHaveQuestNM( sceneId, selfId, MissionId) == 0 then   -- 没有这个任务
        -- 检查当天是否已经做过这个任务
        if x300340_CheckDayTimes( sceneId, selfId) ~= 0 then
        	local str = "你今天已经完成过这个任务，请明天再来"
            BeginQuestEvent( sceneId)
            AddQuestText( sceneId, str )
            EndQuestEvent()
            DispatchQuestTips( sceneId, selfId)
            Msg2Player(sceneId, selfId, str, 8, 2)
            return
        end
        -- 检查背包是否已满
        BeginAddItem( sceneId)
            AddItem( sceneId, x300340_g_MissionPropertyId, 1)
        local result = EndAddItem( sceneId, selfId)
        if result == 0 then
        	local str = "背包已满，无法存放任务道具，任务接受失败！";
    		BeginQuestEvent( sceneId)
    		AddQuestText( sceneId, str )
    		EndQuestEvent( sceneId)
    		DispatchQuestTips( sceneId, selfId)
          	Msg2Player(sceneId, selfId, str, 8, 2)
    		
            return 0
        end
    	local ret	= AddQuest( sceneId, selfId, x300340_g_MissionId, x300340_g_ScritpId, 1, 0, 0, 1);
    	if( ret == 0) then
    		local str = "任务已满，任务接受失败！"
    		BeginQuestEvent( sceneId)
    		AddQuestText( sceneId, str )
    		EndQuestEvent( sceneId)
    		DispatchQuestTips( sceneId, selfId)
          	Msg2Player(sceneId, selfId, str, 8, 2)
    		return 0
        else
            -- 更新接任务时间
            local today = GetDayOfYear()
            x300340_SetAcceptTime( sceneId, selfId, today)
            
            local misIndex = GetQuestIndexByID( sceneId, selfId, x300340_g_MissionId)
            SetQuestByIndex( sceneId, selfId, misIndex, 7, 0)
            SetQuestByIndex( sceneId, selfId, misIndex, 0, 0)
            SetQuestByIndex( sceneId, selfId, misIndex, x300340_g_MP_TargetItemId, GetPlayerRuntimeData( sceneId, selfId, RD_GUJI_ITEMID) )
            SetQuestByIndex( sceneId, selfId, misIndex, x300340_g_MP_TargetScene, GetPlayerRuntimeData( sceneId, selfId, RD_GUJI_SCENEID) )
            SetQuestByIndex( sceneId, selfId, misIndex, x300340_g_MP_PosX, 0)
            SetQuestByIndex( sceneId, selfId, misIndex, x300340_g_MP_PosZ, 0)
            SetQuestByIndex( sceneId, selfId, misIndex, x300340_g_MP_UseTime, 0)

            x300340_ProcQuestLogRefresh( sceneId, selfId, MissionId)

    		BeginQuestEvent( sceneId)
    		AddQuestText( sceneId, x300340_g_strMissionAccept);
    		EndQuestEvent( sceneId);
    		DispatchQuestTips( sceneId, selfId);
    		Msg2Player( sceneId, selfId, x300340_g_strMissionAccept, 8, 2)
    		Msg2Player( sceneId, selfId, x300340_g_strMissionAccept, 8, 3)

            -- 添加任务物品
            AddItemListToPlayer( sceneId, selfId)
            local str = "你获得了物品：@item_"..x300340_g_MissionPropertyId;
    		BeginQuestEvent( sceneId)
    		AddQuestText( sceneId, str);
    		EndQuestEvent( sceneId);
    		DispatchQuestTips( sceneId, selfId);
            -- Msg2Player( sceneId, selfId, "", 8, 3)

            -- 写日志
            GamePlayScriptLog( sceneId, selfId, 441)
        end
    else
        -- 
        x300340_MissionComplate( sceneId, selfId, targetId, MissionId)
    end
end

function x300340_QuestLogRefresh( sceneId, selfId, MissionId)
    x300340_ProcQuestLogRefresh( sceneId, selfId, MissionId)
end

function x300340_ProcQuestLogRefresh( sceneId, selfId, MissionId)
    local misIndex = GetQuestIndexByID( sceneId, selfId, x300340_g_MissionId)
    local taritem = GetQuestParam( sceneId, selfId, misIndex, x300340_g_MP_TargetItemId)
    local strItem = ""
    local strPalace = ""
    local strMonster = ""
    for i, item in x300340_g_MissionTable do
        if item.itemId == taritem then
            strItem = item.itemName
            strPalace = item.placeName
            strMonster = item.monsterName
            break
        end
    end

    -- 察看玩家背包中物品数量总数
    local itemSize = GetItemCount( sceneId, selfId, taritem)
    if itemSize >= x300340_g_FinishCount then
        local misIndex = GetQuestIndexByID( sceneId, selfId, x300340_g_MissionId)
        SetQuestByIndex( sceneId, selfId, misIndex, 7, 1)
        SetQuestByIndex( sceneId, selfId, misIndex, 0, 1)
    end

    BeginQuestEvent( sceneId)
        AddQuestLogCustomText( sceneId,
                                "",                             -- 标题
                                x300340_g_MissionName,          -- 任务名字
                                format( x300340_g_strMissionTarget, strPalace, taritem, itemSize),     -- 任务目标
                                x300340_g_NPC,                  -- 任务NPC
                                format(x300340_g_MissionProcess, strPalace, taritem),          -- 任务攻略
                                format( x300340_g_MissionDescription, strPalace, strMonster, taritem, strPalace),   -- 任务描述
                                x300340_g_MissionHelp )          -- 任务提示
    local exp = GetLevel( sceneId, selfId) * x300340_g_ExperienceCoefficient
    AddQuestExpBonus( sceneId, exp)
    -- 090302 银卡奖励
    local playerLevel = GetLevel( sceneId, selfId)
    if playerLevel > 80 then
        playerLevel = 80
    end
    local money = playerLevel * x300340_g_MoneyCoefficient
    AddQuestMoneyBonus1( sceneId, money)

    EndQuestEvent()
    DispatchQuestLogUpdate( sceneId, selfId, MissionId);
end

function x300340_Accept( sceneId, selfId, MissionId )
	return -1
end

--杀死怪物
--场景ID, 自己的ID(组队状态下为接任务成员的Id), 怪物表位置号, 怪物objId, 任务ID
function x300340_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId)
    
    if IsPlayerStateNormal( sceneId, selfId) ~= 1 then
        return
    end
    
    local misIndex = GetQuestIndexByID( sceneId, selfId, x300340_g_MissionId)
    -- 获得任务场景Id
    local misScene = GetQuestParam( sceneId, selfId, misIndex, x300340_g_MP_TargetScene)
    -- print( "任务场景ID："..misScene)
    -- print( "当前场景ID："..sceneId)
    -- 检查杀怪场景是不是任务场景
    if misScene == sceneId then
        -- 怪物死在“诱兽炉香”的有效范围内标记
        local bUseFanqi = 0
        -- 获得当前时间
        local curTime = GetCurrentTime()

        -- 使用“诱兽炉香”时间短于3分钟的玩家队列
        local useItemArray = {}
        -- 获得队伍附近人数
        local nearteamnum = GetNearTeamCount( sceneId, selfId)
        local useTime = GetQuestParam( sceneId, selfId, misIndex, x300340_g_MP_UseTime)
        if nearteamnum <= 1 and curTime - useTime < x300340_g_FanqiTime then
            useItemArray[ 1] = selfId
        else
            for i = 0, nearteamnum - 1 do
                -- 获得队伍成员的ID
                local memberId = GetNearTeamMember( sceneId, selfId, i)

                if memberId >= 0 and IsPlayerStateNormal( sceneId, memberId) == 1 then
                    -- 查看有没有任务
                    local mIndex = GetQuestIndexByID( sceneId, memberId, x300340_g_MissionId)
                    if mIndex >= 0 then
                        local useitem = GetQuestParam( sceneId, memberId, mIndex, x300340_g_MP_UseTime)
                        if curTime - useitem < x300340_g_FanqiTime then
                            useItemArray[ i + 1] = memberId
                        end
                    end
                end
            end
        end

        -- 遍历检查被杀怪物是否处于这些道具的有效范围中
        for i, id in useItemArray do
            -- 获得被杀怪物的遇害坐标
            local x, z = GetWorldPos( sceneId, objId)
            local mIndex = GetQuestIndexByID( sceneId, id, x300340_g_MissionId)
            -- 获得使用“诱兽炉香”的坐标
            local ux = GetQuestParam( sceneId, id, mIndex, x300340_g_MP_PosX)
            local uz = GetQuestParam( sceneId, id, mIndex, x300340_g_MP_PosZ)
            -- print(ux)
            -- print(uz)
            if ux ~= 0 and uz ~= 0 then
                -- print( abs( x - ux) )
                -- print( abs( z - uz) )
                if abs( x - ux) < x300340_g_Range and abs( z - uz) < x300340_g_Range then
                    -- 如果怪物死在队伍成员使用的“诱兽炉香”的有效范围内
                    bUseFanqi = 1
                    break
                end
            end
        end

        -- print( bUseFanqi)
        local DropItem = 0
        if bUseFanqi == 1 then
            -- 按100%的概率掉落任务所需的物品给所有有任务的成员
            DropItem = 1
        else
            -- 超过了“诱兽炉香”的时间或没有在有效范伟之外，按10%的概率掉落任务所需的物品给所有有任务的成员
            local temp = random( 1, 100)
            -- print( "random = "..temp)
            if temp > 45 and temp <= 55 then
                DropItem = 1
            end
        end

        -- 获得任务物品Id
        local toGiveItem = GetQuestParam( sceneId, selfId, misIndex, x300340_g_MP_TargetItemId)

        -- 把任务物品放到玩家背包里
        if DropItem == 1 then
            if nearteamnum <= 1 then   -- 个人做任务或其他队员不在周围
                local misIndex = GetQuestIndexByID( sceneId, selfId, x300340_g_MissionId)
                if GetQuestParam( sceneId, selfId, misIndex, 7) == 0 then
                    BeginAddItem( sceneId)
                    AddItem( sceneId, toGiveItem, 1)
                    local result = EndAddItem( sceneId, selfId)
                    if result == 0 then
                		BeginQuestEvent( sceneId)
                		AddQuestText( sceneId, "背包已满，无法得到任务物品" )
                		EndQuestEvent( sceneId)
                		DispatchQuestTips( sceneId, selfId)
                        return
                    end
                    AddItemListToPlayer( sceneId, selfId)
                    local str = "#Y你获得了物品：#G#{_ITEM"..toGiveItem.."}";
                    BeginQuestEvent( sceneId)
                    AddQuestText( sceneId, str.."#Y ("..GetItemCount(sceneId, selfId, toGiveItem).."/"..x300340_g_FinishCount..")" )
                    EndQuestEvent( sceneId)
                    DispatchQuestTips( sceneId, selfId )
                    --Msg2Player(sceneId, selfId, str, 8, 2);
                    x300340_ProcQuestLogRefresh( sceneId, selfId, x300340_g_MissionId)
                end
            else  -- 组队做任务
                local Count = 1
                local arrMember = {}
                -- 收集队伍中有任务的玩家Id
                for i = 0, nearteamnum - 1 do
                    -- 获得队伍成员的ID
                    local memberId = GetNearTeamMember( sceneId, selfId, i)
                    if memberId >= 0 and IsPlayerStateNormal( sceneId, memberId) == 1 then
                        local misIndex = GetQuestIndexByID( sceneId, memberId, x300340_g_MissionId)
                        if IsHaveQuestNM( sceneId, memberId, x300340_g_MissionId) ~= 0 and GetQuestParam( sceneId, memberId, misIndex, 7) == 0 then -- 如果有这个任务且未完成
                            arrMember[ Count] = memberId
                            Count = Count + 1
                        end
                    end
                end
                if Count == 1 then
                    -- 如果任务都已完成直接返回
                    return
                end
                -- 从中随机选一个人得到任务物品
                local i = random( 1, getn( arrMember) )
                local misIndex = GetQuestIndexByID( sceneId, arrMember[ i], x300340_g_MissionId)
                toGiveItem = GetQuestParam( sceneId, arrMember[ i], misIndex, x300340_g_MP_TargetItemId)
                BeginAddItem( sceneId)
                AddItem( sceneId, toGiveItem, 1)
                local result = EndAddItem( sceneId, arrMember[ i] )
                if result == 0 then
                    BeginQuestEvent( sceneId)
                    AddQuestText( sceneId, "背包已满，无法得到任务物品" )
                    EndQuestEvent( sceneId)
                    DispatchQuestTips( sceneId, arrMember[ i] )
                    return
                end
                AddItemListToPlayer( sceneId, arrMember[ i] )
                local str = "#Y你获得了物品：#G#{_ITEM"..toGiveItem.."}";
                BeginQuestEvent( sceneId)
                AddQuestText( sceneId,  str.."#Y ("..GetItemCount(sceneId, arrMember[ i], toGiveItem).."/"..x300340_g_FinishCount..")" )
                EndQuestEvent( sceneId)
                DispatchQuestTips( sceneId, arrMember[ i] )
                --Msg2Player(sceneId, selfId, str, 8, 2)
                x300340_ProcQuestLogRefresh( sceneId, arrMember[ i], x300340_g_MissionId)
            end
            -- 只要得到一个任务物品就设置任务完成标记
            -- local misIndex = GetQuestIndexByID( sceneId, selfId, x300340_g_MissionId)
            -- SetQuestByIndex( sceneId, selfId, misIndex, 7, 1)
        end
    end
end

--物品改变
function x300340_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )--寻找材料的任务完成后再添加合成任务
	return 0
end

function x300340_MissionComplateInfo( sceneId, selfId, targetId)
	-- DelQuest( sceneId, selfId, MissionId )
	BeginQuestEvent( sceneId)
	AddQuestText( sceneId, "#Y"..x300340_g_MissionName.."#W\n\t谢谢你，你简直是草原的制霸者，我为你而骄傲！" )
    local exp = GetLevel( sceneId, selfId) * x300340_g_ExperienceCoefficient
    if exp > 0 then
        AddQuestExpBonus( sceneId, exp)
    end
    -- 090302 银卡奖励
    local playerLevel = GetLevel( sceneId, selfId)
    if playerLevel > 80 then
        playerLevel = 80
    end
    local money = playerLevel * x300340_g_MoneyCoefficient
    AddQuestMoneyBonus1( sceneId, money)
	EndQuestEvent( sceneId)
	DispatchQuestInfoNM( sceneId, selfId, targetId, x300340_g_ScritpId, x300340_g_MissionId)
end

function x300340_MissionComplate( sceneId, selfId, targetId, MissionId)
    local misIndex = GetQuestIndexByID( sceneId, selfId, x300340_g_MissionId)
    local itemId = GetQuestParam( sceneId, selfId, misIndex, x300340_g_MP_TargetItemId)
    -- 获得玩家背包里任务物品的数量
    local itemCount = GetItemCountInBag( sceneId, selfId, itemId)
    -- 获得玩家等级
    local playerLevel = GetLevel( sceneId, selfId)
    DelQuest( sceneId, selfId, MissionId)
    -- 最终经验值
    local xp = x300340_g_ExperienceCoefficient * playerLevel
    DelItem( sceneId, selfId, itemId, itemCount)
    AddExp( sceneId, selfId, xp)
    -- 090302 银卡奖励
    if playerLevel > 80 then
        playerLevel = 80
    end
    local money = playerLevel * x300340_g_MoneyCoefficient
    AddMoney( sceneId, selfId, 1, money)

    BeginQuestEvent( sceneId)
    AddQuestText( sceneId, x300340_g_strMissionComplete)
    EndQuestEvent( sceneId)
    DispatchQuestTips( sceneId, selfId)
    Msg2Player( sceneId, selfId, x300340_g_strMissionComplete, 8, 2)

    Msg2Player( sceneId, selfId, format( "获得#R经验%d点#cffcf00的奖励", xp), 8, 2)
    BeginQuestEvent( sceneId)
    AddQuestText( sceneId, format( "获得#R经验%d点#cffcf00的奖励", xp) )
    EndQuestEvent( sceneId)
    DispatchQuestTips( sceneId, selfId)

    Msg2Player( sceneId, selfId, format( "获得#R银卡#{_MONEY%d}#cffcf00的奖励", money), 8, 3)
    Msg2Player( sceneId, selfId, format( "获得#R银卡#{_MONEY%d}#cffcf00的奖励。", money), 8, 2)

    -- 更新交任务时间，避免第一天接任务，第二天交任务后可以立刻再接的问题
    local today = GetDayOfYear()
    x300340_SetAcceptTime( sceneId, selfId, today)

    -- 写日志
    GamePlayScriptLog( sceneId, selfId, 442)
end

-- 
function x300340_GetAcceptTime( sceneId, selfId)
    return GetQuestData( sceneId, selfId, MD_GUJI_ACCEPTTIME[ 1], MD_GUJI_ACCEPTTIME[ 2], MD_GUJI_ACCEPTTIME[ 3] )
end

function x300340_SetAcceptTime( sceneId, selfId, value)
    SetQuestData( sceneId, selfId, MD_GUJI_ACCEPTTIME[ 1], MD_GUJI_ACCEPTTIME[ 2], MD_GUJI_ACCEPTTIME[ 3], value)
end

function x300340_ProcQuestAbandon( sceneId, selfId, MissionId)
    local misIndex = GetQuestIndexByID( sceneId, selfId, x300340_g_MissionId)
    local id = GetQuestParam( sceneId, selfId, misIndex, x300340_g_MP_TargetItemId)
    local count = GetItemCountInBag( sceneId, selfId, id)
    if count > 0 then
        DelItem( sceneId, selfId, id, count)
    end

	local ret = 0
	local MissionName = GetQuestNameNM( sceneId, selfId, x300340_g_MissionId)
	ret = DelQuestNM( sceneId, selfId, x300340_g_MissionId)
	if ret == 1 then
		BeginQuestEvent( sceneId)
		AddQuestText( sceneId, x300340_g_strMissionAbandon);
		EndQuestEvent( sceneId);
		DispatchQuestTips( sceneId, selfId);
		Msg2Player( sceneId, selfId, x300340_g_strMissionAbandon, 8, 2)
	end

    local today = GetDayOfYear()

    x300340_SetAcceptTime( sceneId, selfId, today)
end

function x300340_ProcQuestSubmit( sceneId, selfId, targetId, selectId, MissionId )
end

function x300340_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )

end
