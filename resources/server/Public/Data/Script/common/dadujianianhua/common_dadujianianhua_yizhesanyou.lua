--MisDescBegin

x300569_g_ScriptId 					= 300569                  --脚本ID
x300569_g_MissionId 				= 9320                    --任务ID

x300569_g_MissionKind 				= 2                       --任务类型
x300569_g_LevelLess					= 40                      --场景开放等级  <=0 表示不限制

x300569_g_MissionName				= "【德】益者三友"                                        --任务名称(512)
x300569_g_MissionTarget				= "\t帮助全美丽找回高丽属国的贡品"      --任务目标
x300569_g_MissionInfo				= "\t#Y@myname#W，小女子全美丽，这里有礼了。\n\t方才我的夫君一时不察，将我高丽国准备敬献给忽必烈陛下的贡品，遗失在大都西郊，这些贡品皆是我高丽国多年珍藏之宝物，若是就此丢失，恐怕我夫君难逃杀身之祸。\n\t久闻大元子民皆是高义仁德之人，不知你可否帮忙将那贡品找回？"            --任务信息
x300569_g_ContinueInfo				= "\t贡品......，这可如何是好。"  --任务继续信息
x300569_g_MissionCompleted			= "\t这......正是丢失的贡品！\n\t大元子民果然高尚仁义，难怪孔圣人云：君子爱财，取之有道。我今日方才真正见识。\n\t#Y@myname#W，还请受我一拜。"  --任务完成信息
x300569_g_MissionHelp				= "#G\t在本任务中，如果您在采集过程中找到高级的高丽贡品，您获得的经验奖励也会增加。"          --任务提示信息
-- 任务放弃提示信息
x300569_g_strMissionAbandon         = "您放弃了任务：【德】益者三友"

--目标
x300569_g_ExtTarget					= { {type=20,n=1,target=""} }
x300569_g_TianfuItems				= {11010100,11010101,11010102}

--奖励
x300569_g_ExpBonus					= 0     --奖励：经验 （数值填0，字符串为空，表示没有该项奖励）
x300569_g_BonusItem					= {}	--奖励：物品

x300569_g_BonusMoney1               = 0  --任务奖励绑定银币
x300569_g_BonusMoney2               = 0  --任务奖励非绑定银币
x300569_g_BonusMoney3               = 0  --任务奖励绑定金币
x300569_g_BonusMoney4               = 0  --任务奖励朝廷声望
x300569_g_BonusMoney5               = 0  --任务奖励江湖声望
x300569_g_BonusMoney6               = 0  --任务奖励荣誉

x300569_g_BonusChoiceItem           = {}

--MisDescEnd

x300569_g_MaxCount					= 1

--任务目标顺序

x300569_g_strMissionFull            = "任务已满，任务接受失败"
x300569_g_strMissionAccept          = "您接受了任务：【德】益者三友"
x300569_g_strMissionBook            ="据全美丽说当天他们在#G京畿路#W和#G观澜湖东南侧#W停留过一段时间。"
x300569_g_strSubMissionInfo         = "\t找回丢失的贡品。"
x300569_g_strMissionFinished        = "你完成了任务：【德】益者三友"
x300569_g_strMissionRefrain         = "你今天已经做过这个任务了"
x300569_g_strMissionTarget1         = "\t找到遗失的贡品#G#{_ITEM13810084} #{_ITEM13810089} #{_ITEM13810092} #{_ITEM13810101} #{_ITEM13810104}#W并将其交给@npc_139130"
x300569_g_strMissionTarget2         = "%s  在@npc_72050找到#{_ITEM13810084}(%d/1)\n%s  在@npc_72051找到#{_ITEM13810089}(%d/1)\n%s  在@npc_72052找到#{_ITEM13810092}(%d/1)\n%s  在@npc_72053找到#{_ITEM13810101}(%d/1)\n%s  在@npc_72054找到#{_ITEM13810104}(%d/1)"
x300569_g_strMissionTitle           = "【德】益者三友"
-- 接受任务记录日志ID
x300569_g_AcceptMissionLogID        = 951
-- 完成任务记录日志ID
x300569_g_FinishMissionLogID        = 952
-- 交任务NPC
x300569_g_TargetNPC                 = 139130
-- 接任务NPC
x300569_g_MissionNPC                = 139129
-- 任务回复NPC
x300569_g_MissionReply              = "@npc_139130"
-- 任务物品列表
x300569_g_MissionItemTable          = {
                                        { itemId = 13810084, PosId = 72050, gpId = 323, strName = "东海珠" }, -- 蓝箱子物品和采集点ID 采集地点：大都西郊
																				{ itemId = 13810089, PosId = 72051, gpId = 325, strName = "裘皮袄" }, -- 绿箱子物品和采集点ID 采集地点：大都西郊
                                        { itemId = 13810092, PosId = 72052, gpId = 326, strName = "高丽参" }, -- 黑箱子物品和采集点ID 采集地点：大都西郊
                                        { itemId = 13810101, PosId = 72053, gpId = 329, strName = "琉璃碗" }, -- 黄箱子物品和采集点ID 采集地点：大都西郊
                                        { itemId = 13810104, PosId = 72054, gpId = 330, strName = "丹阳木" }, -- 绿箱子物品和采集点ID 采集地点：大都西郊
}
-- 经验奖励系数
x300569_g_CoffExp                   = 7000
-- 现银奖励系数
x300569_g_CoffMoney                 = 0
-- 每次任务完成奖励声望值
x300569_g_Credit                    = 150
-- 当天五种颜色的箱子都开过了还要继续接任务时的提示信息
x300569_g_strRefuse                 = "\t多谢你了，夫君丢失的高丽贡品已经都找回了。我们这就准备前去晋见忽必烈陛下。"
-- 玩法开关id
x300569_g_IsEnableId                = 1006
-- 玩法开放时间(从0点起的第x分钟)
x300569_g_OpenTime                  = 1170
-- 玩法关闭时间(从0点起的第x分钟)
x300569_g_EndTime                   = 1440
-- 不在任务时间接任务时的提示信息
x300569_g_strNotMissionTime         = "只有在每日的#G19：30--24：00#cffcf00内才可领取任务"

-- 额外奖励物品ID
x300569_g_AdditionItem              = 12030107

---------------------------------------------------------------------------------------------------
--列举事件
---------------------------------------------------------------------------------------------------
function x300569_ProcEnumEvent( sceneId, selfId, NPCId, MissionId)
    if GetGameOpenById( x300569_g_IsEnableId) <= 0 then
        return 0
    end

    if GetLevel( sceneId, selfId) < x300569_g_LevelLess then
        return 0
    end

    if IsHaveQuestNM( sceneId, selfId, x300569_g_MissionId) > 0 then
        return 0
    end

    AddQuestNumText( sceneId, x300569_g_MissionId, x300569_g_MissionName, GetQuestStateNM( sceneId, selfId, NPCId, x300569_g_MissionId), 1)
end

---------------------------------------------------------------------------------------------------
--任务入口函数
---------------------------------------------------------------------------------------------------
function x300569_ProcEventEntry( sceneId, selfId, NPCId, MissionId, nExtIdx)
    if GetGameOpenById( x300569_g_IsEnableId) <= 0 then
        return 0
    end

	if IsHaveQuestNM( sceneId, selfId, x300569_g_MissionId) > 0 then  -- 如果已经接过这个任务
        local npcGuid = GetMonsterGUID( sceneId, NPCId)
        if npcGuid == x300569_g_TargetNPC then
            local misIndex = GetQuestIndexByID( sceneId, selfId, x300569_g_MissionId)
            if GetQuestParam( sceneId, selfId, misIndex, 0) == 0 and GetQuestParam( sceneId, selfId, misIndex, 7) == 0 then
                x300569_DispatchContinueInfo( sceneId, selfId, NPCId) --未完成任务显示
            else
                x300569_DispatchCompletedInfo( sceneId, selfId, NPCId) --完成任务显示
            end
        end
	else
		x300569_DispatchMissionInfo( sceneId, selfId, NPCId)	--任务信息显示
	end
end

---------------------------------------------------------------------------------------------------
--检测接受条件
---------------------------------------------------------------------------------------------------
function x300569_ProcAcceptCheck( sceneId, selfId, npcId)
	local bHaveMission	= IsHaveQuestNM( sceneId, selfId, x300569_g_MissionId)
	if( bHaveMission > 0) then
		return 0;
	else
		return 1;
	end
end

function x300569_AddTianfuItem( sceneId, selfId)
	local level = GetLevel( sceneId, selfId)
	if level >= 80 then
		if random( 1, 100) <= 22 then
			local nIndex = random(1,3)
			BeginAddItem( sceneId)
	        AddItem( sceneId, x300569_g_TianfuItems[nIndex], 1)
	        if EndAddItem( sceneId, selfId) <= 0 then
	            Msg2Player( sceneId, selfId, "由于你的背包已满，无法获得天赋道具奖励。", 8, 2)
	        else
	            AddItemListToPlayer( sceneId, selfId)
	        end
		end
	end
end
---------------------------------------------------------------------------------------------------
--接受条件
---------------------------------------------------------------------------------------------------
function x300569_ProcQuestAccept( sceneId, selfId, targetId, missionId)
    if GetGameOpenById( x300569_g_IsEnableId) <= 0 then
        return 0
    end

    local name = GetName( sceneId, selfId)
    if IsHaveQuestNM( sceneId, selfId, x300569_g_MissionId) > 0 then
       -- 玩家身上有特殊任务时交任务给的额外奖励
        local rewardExt = 0
        local itemExt = 0
        if IsHaveQuestNM( sceneId, selfId, 1482) > 0 then
            if random( 1, 100) <= 70 then
                rewardExt = 1
                BeginAddItem( sceneId)
                itemExt = 13015012
                AddItem( sceneId, itemExt, 1)
                if EndAddItem( sceneId, selfId) <= 0 then
                    Msg2Player( sceneId, selfId, "无法得到任务额外奖励物品，请整理背包", 8, 3)
                    return
                end
            end
        end
        -- 根据物品类型设置奖励系数
        for i, item in x300569_g_MissionItemTable do
			if DelItem( sceneId, selfId, item.itemId, 1) == 0 then
				Msg2Player( sceneId, selfId, "提交物品失败。", 8, 2)
				Msg2Player( sceneId, selfId, "提交物品失败", 8, 3)
				return 0
			end 
		end

        -- 交任务日期与接任务日期不一致时清除所有箱子标记
        local today = GetDayOfYear()
        if today ~= x300569_GetMissionDate( sceneId, selfId) then
            x300569_SetMissionDate( sceneId, selfId, today)
            x300569_SetDayCount( sceneId, selfId, 1)
        end


        DelQuest( sceneId, selfId, x300569_g_MissionId)
        
        
        LuaScenceM2Player( sceneId, selfId, x300569_g_strMissionFinished, name, 3, 1)
        LuaScenceM2Player( sceneId, selfId, x300569_g_strMissionFinished.."。", name, 2, 1)
        CallScriptFunction( 256224, "Finishyizhe", sceneId, selfId)	
        x300569_SetMissionDate( sceneId, selfId, GetDayOfYear() )
        local playerLevel = GetLevel( sceneId, selfId)
        local xp = playerLevel * x300569_g_CoffExp
        if xp > 0 then
			AddExp( sceneId, selfId, xp)
			Msg2Player( sceneId, selfId, format( "获得#R经验%d点#cffcf00的奖励", xp).."。", 8, 2)
			Msg2Player( sceneId, selfId, format( "获得#R经验%d点#cffcf00的奖励", xp), 8, 3)
        end
        
        local money = playerLevel * x300569_g_CoffMoney
        if money > 0 then
            AddMoney( sceneId, selfId, money, 0)
            Msg2Player( sceneId, selfId, format( "获得#R现银#{_MONEY%d}#cffcf00的奖励", money).."。", 8, 2)
            Msg2Player( sceneId, selfId, format( "获得#R现银#{_MONEY%d}#cffcf00的奖励", money), 8, 3)
        end
        SetShengWang( sceneId, selfId, GetShengWang( sceneId, selfId) + x300569_g_Credit)
        Msg2Player( sceneId, selfId, format( "获得#R%d点声望#cffcf00的奖励", x300569_g_Credit).."。", 8, 2)
        Msg2Player( sceneId, selfId, format( "获得#R%d点声望#cffcf00的奖励", x300569_g_Credit), 8, 3)
        -- 更新Daycount                           
        x300569_SetDayCount( sceneId, selfId, x300569_GetDayCount( sceneId, selfId) + 1)
        if rewardExt == 1 then
            AddItemListToPlayer( sceneId, selfId)
            Msg2Player( sceneId, selfId, format( "获得@item_%d#cffcf00的额外奖励", itemExt).."。", 8, 2)
            Msg2Player( sceneId, selfId, format( "获得@item_%d#cffcf00的额外奖励", itemExt), 8, 3)
        end
        
        x300569_AddTianfuItem( sceneId, selfId)
        
        local value = random( 1, 100)
        local buff 	=	9011
				local buff1 =	9013
				local buff2 =	9012
        if value > 20 and value <= 40 then
            BeginAddItem( sceneId)
            if IsHaveSpecificImpact( sceneId, selfId, buff) == 1 or IsHaveSpecificImpact( sceneId, selfId, buff1) == 1 or IsHaveSpecificImpact( sceneId, selfId, buff2) == 1 then
            	AddItem( sceneId, x300569_g_AdditionItem, 1)
            else
           		AddBindItem( sceneId, x300569_g_AdditionItem, 1)
           	end
            if EndAddItem( sceneId, selfId) <= 0 then
                Msg2Player( sceneId, selfId, "你完成了【德】益者三友。由于你的背包已满，无法获得藏宝图奖励。", 8, 2)
            else
            	AddItemListToPlayer( sceneId, selfId)
                -- LuaAllScenceM2Wrold( sceneId, "#G玩家#Y"..GetName( sceneId, selfId).."#G在完成【德】益者三友时意外的获得了一张#R藏宝图#G。", 1, 1)
            end
        end
        
        -- 添加一枚大都嘉年华娱乐币
        BeginAddItem( sceneId)
        AddItem( sceneId, 11990117, 5)
        if EndAddItem( sceneId, selfId) <= 0 then
            Msg2Player( sceneId, selfId, "你完成了【德】益者三友。由于你的背包已满，无法获得#{_ITEM11990117}奖励。", 8, 2)
        else
            AddItemListToPlayer( sceneId, selfId)
        end
        GamePlayScriptLog( sceneId, selfId, x300569_g_FinishMissionLogID)
    else
        -- 时间检查
        local nowTime = GetMinOfDay()
        if nowTime < x300569_g_OpenTime or nowTime >= x300569_g_EndTime then
            Msg2Player( sceneId, selfId, x300569_g_strNotMissionTime.."。", 8, 2)
            Msg2Player( sceneId, selfId, x300569_g_strNotMissionTime, 8, 3)
            return
        end

        local npcGuid = GetMonsterGUID( sceneId, targetId)
        if npcGuid == x300569_g_TargetNPC then
            return
        end

        local today = GetDayOfYear()
        if x300569_GetMissionDate( sceneId, selfId) == today then
            if x300569_GetDayCount( sceneId, selfId) > x300569_g_MaxCount then
                -- 表示当天5种颜色的箱子都开过了
                BeginQuestEvent( sceneId)
                    AddQuestText( sceneId, "#Y"..x300569_g_MissionName)
                    AddQuestText( sceneId, x300569_g_strRefuse)
                EndQuestEvent()
                DispatchQuestEventList( sceneId, selfId, targetId)
                Msg2Player( sceneId, selfId, format("今天你已经做过这个任务，不能再接了"), 8, 3)
                return 0
            end
        else
            x300569_SetMissionDate( sceneId, selfId, today)
            x300569_SetDayCount( sceneId, selfId, 1)
        end

        --检查前置任务
		local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId, x300569_g_MissionId)
		if FrontMissiontId1 ~= -1 then
			if IsQuestHaveDoneNM( sceneId, selfId, FrontMissiontId1 ) == 0 then
				return 0
			end
		end
		if FrontMissiontId2 ~= -1 then
			if IsQuestHaveDoneNM( sceneId, selfId, FrontMissiontId2 ) == 0 then
				return 0
			end
		end
		if FrontMissiontId3 ~= -1 then
			if IsQuestHaveDoneNM( sceneId, selfId, FrontMissiontId3 ) == 0 then
				return 0
			end
		end

        if AddQuest( sceneId, selfId, x300569_g_MissionId, x300569_g_ScriptId, 0, 0, 1, 1) == 0 then
            LuaScenceM2Player( sceneId, selfId, x300569_g_strMissionFull, name, 3, 1)
            return 0
        else
            -- 显示任务接受信息
            LuaScenceM2Player( sceneId, selfId, x300569_g_strMissionAccept, name, 3, 1)
            LuaScenceM2Player( sceneId, selfId, x300569_g_strMissionAccept, name, 2, 1)
        end

        local misIndex = GetQuestIndexByID( sceneId, selfId, x300569_g_MissionId)
		
        BeginQuestEvent( sceneId)
            AddQuestText( sceneId, "#Y"..x300569_g_MissionName)
            AddQuestText( sceneId, x300569_g_strMissionTarget1 )
        EndQuestEvent()
        DispatchQuestEventList( sceneId, selfId, targetId)

        SetQuestByIndex( sceneId, selfId, misIndex, 7, 0)
        SetQuestByIndex( sceneId, selfId, misIndex, 0, 0)
        
        SetQuestByIndex( sceneId, selfId, misIndex, 1, (HaveItemInBag( sceneId, selfId, x300569_g_MissionItemTable[1].itemId ) > 0 and 1 or 0))
        SetQuestByIndex( sceneId, selfId, misIndex, 2, (HaveItemInBag( sceneId, selfId, x300569_g_MissionItemTable[2].itemId ) > 0 and 1 or 0))
        SetQuestByIndex( sceneId, selfId, misIndex, 3, (HaveItemInBag( sceneId, selfId, x300569_g_MissionItemTable[3].itemId ) > 0 and 1 or 0))
        SetQuestByIndex( sceneId, selfId, misIndex, 4, (HaveItemInBag( sceneId, selfId, x300569_g_MissionItemTable[4].itemId ) > 0 and 1 or 0))
        SetQuestByIndex( sceneId, selfId, misIndex, 5, (HaveItemInBag( sceneId, selfId, x300569_g_MissionItemTable[5].itemId ) > 0 and 1 or 0))

        -- 更新任务跟踪和Q面板
        x300569_ProcQuestLogRefresh( sceneId, selfId, x300569_g_MissionId)

        -- 写日志
        GamePlayScriptLog( sceneId, selfId, x300569_g_AcceptMissionLogID)
    end
end

---------------------------------------------------------------------------------------------------
--放弃任务
---------------------------------------------------------------------------------------------------
function x300569_ProcQuestAbandon( sceneId, selfId, MissionId)
	local bHaveMission	= IsHaveQuestNM( sceneId, selfId, x300569_g_MissionId)
	if bHaveMission > 0 then
       
        -- 如果已经采集到物品，先删除
        for i, item in x300569_g_MissionItemTable do
            if GetItemCountInBag( sceneId, selfId, item.itemId) > 0 and DelItem( sceneId, selfId, item.itemId, 1) == 0 then
                Msg2Player( sceneId, selfId, "删除任务物品失败，无法放弃任务。", 8, 2)
                Msg2Player( sceneId, selfId, "删除任务物品失败，无法放弃任务", 8, 3)
                return 0
            end
        end

		DelQuest( sceneId, selfId, x300569_g_MissionId)

        local today = GetDayOfYear()
        if today == x300569_GetMissionDate( sceneId, selfId) then
            x300569_SetDayCount( sceneId, selfId, x300569_GetDayCount( sceneId, selfId) + 1)
        else
            x300569_SetMissionDate( sceneId, selfId, today)
            -- 计为当天已经做一次
            x300569_SetDayCount( sceneId, selfId, 2)
        end

		Msg2Player( sceneId, selfId, x300569_g_strMissionAbandon, 8, 3)
		Msg2Player( sceneId, selfId, x300569_g_strMissionAbandon, 8, 2)
	end
end

---------------------------------------------------------------------------------------------------
--检查任务是否可提交
---------------------------------------------------------------------------------------------------
function x300569_CheckSubmit( sceneId, selfId, NPCId)

	local misIndex = GetQuestIndexByID( sceneId, selfId, x300569_g_MissionId)

    if GetQuestParam( sceneId, selfId, misIndex, 0) == 1 and GetQuestParam( sceneId, selfId, misIndex, 7) == 1 then
        return 1
    else
        return 0
    end
end

---------------------------------------------------------------------------------------------------
--获得奖励
---------------------------------------------------------------------------------------------------
function x300569_GetBonus( sceneId, selfId,NpcID, SelectId)
	--奖励金钱1
	if x300569_g_BonusMoney1 > 0 then
	    AddMoney( sceneId, selfId, 1, x300569_g_BonusMoney1 )
	    Msg2Player(sceneId,selfId,format("获得银卡#{_MONEY%d}的奖励。", x300569_g_BonusMoney1),4,2)
	end

	--奖励金钱2
	if x300569_g_BonusMoney2 > 0 then
	    AddMoney( sceneId, selfId, 0, x300569_g_BonusMoney2 )
	    Msg2Player(sceneId,selfId,format("获得银币#{_MONEY%d}的奖励。", x300569_g_BonusMoney2),4,2)
	end

	--奖励金钱1
	if x300569_g_BonusMoney3 > 0 then
	    AddMoney( sceneId, selfId, 3, x300569_g_BonusMoney3 )
	    Msg2Player(sceneId,selfId,format("获得金卡#{_MONEY%d}的奖励。", x300569_g_BonusMoney3),4,2)
	end

	--江湖声望
	if x300569_g_BonusMoney4 > 0 then
		local nRongYu = GetRongYu( sceneId, selfId )
		nRongYu = nRongYu + x300569_g_BonusMoney4
		SetRongYu( sceneId, selfId, nRongYu )
		Msg2Player(sceneId,selfId,format("获得声望%d的奖励。", x300569_g_BonusMoney4),4,2)
	end

	--朝廷声望
	if x300569_g_BonusMoney5 > 0 then
		local nShengWang = GetShengWang( sceneId, selfId )
		nShengWang = nShengWang + x300569_g_BonusMoney5
		SetShengWang( sceneId, selfId, nShengWang )
		Msg2Player(sceneId,selfId,format("获得声望%d的奖励。", x300569_g_BonusMoney5),4,2)
	end

	--朝廷声望
	if x300569_g_BonusMoney6 > 0 then
		AddHonor(sceneId,selfId,x300569_g_BonusMoney6)
		Msg2Player(sceneId,selfId,format("获得荣誉值%d的奖励。", x300569_g_BonusMoney6),4,2)
	end

 	--奖励固定物品
	for i, item in x300569_g_BonusItem do
 		BeginAddItem(sceneId)
		AddItem( sceneId, item.item, item.n )
		if EndAddItem( sceneId, selfId) > 0 then
			AddItemListToPlayer(sceneId,selfId)
		else
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"物品栏已满，无法得到任务物品！")
			EndQuestEvent()
			DispatchQuestTips(sceneId,selfId)
		end
    end

	--奖励可选物品
	for i, item in x300569_g_BonusChoiceItem do
	    if item.item == SelectId then
	        BeginAddItem(sceneId)
			AddItem( sceneId, item.item, item.n )
			if EndAddItem( sceneId, selfId) > 0 then
				AddItemListToPlayer( sceneId, selfId)
			else
				BeginQuestEvent( sceneId)
				AddQuestText( sceneId, "物品栏已满，无法得到任务物品！" )
				EndQuestEvent()
				DispatchQuestTips( sceneId, selfId)
			end

			--获取完必，请返回，防止重复添加
			return
		end
    end
end

---------------------------------------------------------------------------------------------------
--提交任务，不管任务是否完成或是任务，显示任务继续信息或是任务完成信息
---------------------------------------------------------------------------------------------------
function x300569_ProcQuestSubmit( sceneId, selfId, NPCId, selectRadioId, MissionId)
end

---------------------------------------------------------------------------------------------------
--向客户端发送任务信息
---------------------------------------------------------------------------------------------------
function x300569_DispatchMissionInfo( sceneId, selfId, NPCId)
	BeginQuestEvent( sceneId)

    --任务信息
    AddQuestText( sceneId, "#Y"..x300569_g_MissionName)
    AddQuestText( sceneId, x300569_g_MissionInfo)
    AddQuestText( sceneId, " ")
           
    --任务目标
    AddQuestText( sceneId, "#Y任务目标：")
    AddQuestText( sceneId, x300569_g_MissionTarget)
    AddQuestText( sceneId, " ")

    --提示信息
    if x300569_g_MissionHelp ~= "" then
        AddQuestText( sceneId, "#Y小提示：")
        AddQuestText( sceneId, x300569_g_MissionHelp)
        AddQuestText( sceneId, " ")
    end                 

    local level = GetLevel( sceneId, selfId)
    --任务奖励信息

    --1、经验
    local playerLevel = GetLevel( sceneId, selfId)
    local exp = level * x300569_g_CoffExp
    if exp > 0 then
        AddQuestExpBonus( sceneId, exp)
    end

    --2、金钱1：银卡
    if x300569_g_BonusMoney1 > 0 then
        AddQuestMoneyBonus1( sceneId, x300569_g_BonusMoney1)
    end

    --3、金钱2：现银
    if x300569_g_CoffMoney > 0 then
        AddQuestMoneyBonus2( sceneId, x300569_g_CoffMoney * level)
    end
    --4、金钱3
    if x300569_g_BonusMoney3 > 0 then
        AddQuestMoneyBonus3( sceneId, x300569_g_BonusMoney3)
    end

    --江湖声望
    if x300569_g_BonusMoney4 > 0 then
        AddQuestMoneyBonus4( sceneId, x300569_g_BonusMoney4)
    end

    --朝廷声望
    if x300569_g_Credit > 0 then
        AddQuestMoneyBonus5( sceneId, x300569_g_Credit)
    end

    --荣誉值
    if x300569_g_BonusMoney6 > 0 then
        AddQuestMoneyBonus6( sceneId, x300569_g_BonusMoney6)
    end

    --5、固定物品
    for i, item in x300569_g_BonusItem do
        AddQuestItemBonus( sceneId, item.item, item.n)
    end

    --6、可选物品
    for i, item in x300569_g_BonusChoiceItem do
        AddQuestRadioItemBonus( sceneId, item.item, item.n)
    end

	EndQuestEvent()
	DispatchQuestInfoNM( sceneId, selfId, NPCId, x300569_g_ScriptId, x300569_g_MissionId)
end

---------------------------------------------------------------------------------------------------
--向客户端发送任务未完成
---------------------------------------------------------------------------------------------------
function x300569_DispatchContinueInfo( sceneId, selfId, NPCId)
	BeginQuestEvent( sceneId)
    AddQuestText( sceneId, "#Y"..x300569_g_MissionName)
    AddQuestText( sceneId, x300569_g_ContinueInfo)
    AddQuestText( sceneId, " ")
	EndQuestEvent()
    DispatchQuestEventList( sceneId, selfId, NPCId)
end

---------------------------------------------------------------------------------------------------
--向客户端发送任务完成信息
---------------------------------------------------------------------------------------------------
function x300569_DispatchCompletedInfo( sceneId, selfId, NPCId)
	BeginQuestEvent( sceneId)
    AddQuestText( sceneId, "#Y"..x300569_g_MissionName)
    AddQuestText( sceneId, x300569_g_MissionCompleted)
    AddQuestText( sceneId, " ")
    -- 奖励系数
    
    local misIndex = GetQuestIndexByID( sceneId, selfId, x300569_g_MissionId)
    local level = GetLevel( sceneId, selfId)
	local exp = level * x300569_g_CoffExp
    if exp > 0 then
        AddQuestExpBonus( sceneId, exp)
    end
    
    -- 现银奖励
    local money = level * x300569_g_CoffMoney
    if money > 0 then
        AddQuestMoneyBonus2( sceneId, money)
    end
    if x300569_g_Credit > 0 then
        AddQuestMoneyBonus5( sceneId, x300569_g_Credit)
    end
	EndQuestEvent()
	DispatchQuestInfoNM( sceneId, selfId, NPCId, x300569_g_ScriptId, x300569_g_MissionId)
end

---------------------------------------------------------------------------------------------------
--怪物被杀的消息处理
---------------------------------------------------------------------------------------------------
function x300569_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId)
end

---------------------------------------------------------------------------------------------------
--物品改变
---------------------------------------------------------------------------------------------------
function x300569_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId)
    if GetGameOpenById( x300569_g_IsEnableId) <= 0 then
        return 0
    end
	
	local misIndex = GetQuestIndexByID( sceneId, selfId, x300569_g_MissionId)
	
	if IsHaveQuestNM( sceneId, selfId, x300569_g_MissionId) > 0 and IsQuestHaveDoneNM( sceneId, selfId, x300569_g_MissionId ) <= 0 then
		local needitem = 0
		for i, item in x300569_g_MissionItemTable do
			if  itemdataId == item.itemId then
				needitem = 1
				
				SetQuestByIndex( sceneId, selfId, misIndex, i, 1)
			end
		end
		if needitem ~= 1 then
			return
		end
        
		x300569_ProcQuestLogRefresh( sceneId, selfId, x300569_g_MissionId)
		
		for i, item in x300569_g_MissionItemTable do
			if item.itemId ~= itemdataId and HaveItemInBag( sceneId, selfId, item.itemId ) < 0 then
				return
			end
		end
		
		Msg2Player( sceneId, selfId, "#Y你找到了所有贡品，快去交给高丽国使吧。", 8, 3)
		
        SetQuestByIndex( sceneId, selfId, misIndex, 0, 1)
        SetQuestByIndex( sceneId, selfId, misIndex, 7, 1)
	end
end

---------------------------------------------------------------------------------------------------
--单击NPC事件
---------------------------------------------------------------------------------------------------
function x300569_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId)
    if GetGameOpenById( x300569_g_IsEnableId) <= 0 then
        return 0
    end

    if IsHaveQuestNM( sceneId, selfId, x300569_g_MissionId) > 0 then
    
        local misIndex = GetQuestIndexByID( sceneId, selfId, x300569_g_MissionId)
        if npcGuid == x300569_g_TargetNPC then
            if GetQuestParam( sceneId, selfId, misIndex, 0) == 0 and GetQuestParam( sceneId, selfId, misIndex, 7) == 0 then
                AddQuestNumText( sceneId, x300569_g_MissionId, x300569_g_MissionName, 6)
            else
                AddQuestNumText( sceneId, x300569_g_MissionId, x300569_g_MissionName, 7)
            end
        end
    end
end

function x300569_GetMissionDate( sceneId, selfId)
    return GetQuestData( sceneId, selfId, MD_YIZHESANYOU_DATE[ 1], MD_YIZHESANYOU_DATE[ 2], MD_YIZHESANYOU_DATE[ 3] )
end

function x300569_SetMissionDate( sceneId, selfId, value)
    SetQuestData( sceneId, selfId, MD_YIZHESANYOU_DATE[ 1], MD_YIZHESANYOU_DATE[ 2], MD_YIZHESANYOU_DATE[ 3], value)
end

function x300569_GetDayCount( sceneId, selfId)
    return GetQuestData( sceneId, selfId, MD_YIZHESANYOU_COUNTER[ 1], MD_YIZHESANYOU_COUNTER[ 2], MD_YIZHESANYOU_COUNTER[ 3] )
end

function x300569_SetDayCount( sceneId, selfId, value)
    SetQuestData( sceneId, selfId, MD_YIZHESANYOU_COUNTER[ 1], MD_YIZHESANYOU_COUNTER[ 2], MD_YIZHESANYOU_COUNTER[ 3], value)
end

function x300569_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID)
    if GetGameOpenById( x300569_g_IsEnableId) <= 0 then
        return 0
    end

    if IsHaveQuestNM( sceneId, selfId, x300569_g_MissionId) > 0 then
 
        local misIndex = GetQuestIndexByID( sceneId, selfId, x300569_g_MissionId)
        
        local index = -1
        for i, item in x300569_g_MissionItemTable do
			if item.gpId == gpType then
				index = i
				break
			end
        end
        
        if index ~= -1 then
			if HaveItemInBag( sceneId, selfId, x300569_g_MissionItemTable[index].itemId ) < 0 then
                return 0
            else
            	if GetQuestParam( sceneId, selfId, misIndex, 0) == 1 and GetQuestParam( sceneId, selfId, misIndex, 7) == 1 then
                Msg2Player( sceneId, selfId, "你已经找齐了所有高丽贡品，快去找高丽国使提交任务吧。", 8, 3)
               else
               	Msg2Player( sceneId, selfId, "你已经得到了此高丽贡品，快去找到别的高丽贡品吧。", 8, 3)
               end
                return 1
            end
        else
			Msg2Player( sceneId, selfId, "这似乎不是你要找的高丽贡品。", 8, 3)
            return 1
        end
    else
        Msg2Player( sceneId, selfId, "你没有接受【德】益者三友，不能采集", 8, 3)
        return 1
    end
end

function x300569_OnRecycle( sceneId, selfId, targetId, gpType, needItemID)
    if GetGameOpenById( x300569_g_IsEnableId) <= 0 then
        return 0
    end

    if IsHaveQuestNM( sceneId, selfId, x300569_g_MissionId) > 0 then
   
        local misIndex = GetQuestIndexByID( sceneId, selfId, x300569_g_MissionId)
        
        if GetQuestParam( sceneId, selfId, misIndex, 0) == 0 then
			for i, item in x300569_g_MissionItemTable do
			
				if item.itemId == needItemID and item.gpId == gpType and HaveItemInBag( sceneId, selfId, needItemID ) < 0 then
					-- 随机选择采集物品
					BeginAddItem( sceneId)
					
					AddItem( sceneId, needItemID, 1)
	                
					-- 添加每次采集有60%几率随机获得高丽贡书一册（id:12030080）、高丽贡书二册(id:12030081)、高丽贡书三册(id:12030082)三种道具之一。三种道具不绑定，可交易。
					if random(1, 100) <= 60 then
						local rnd = random(1, 3)
						if rnd == 1 then
							AddItem( sceneId, 12030080, 1)
						elseif rnd == 2 then
							AddItem( sceneId, 12030081, 1)
						else
							AddItem( sceneId, 12030082, 1)
						end
						
					end
	                
					if EndAddItem( sceneId, selfId) > 0 then
						AddItemListToPlayer( sceneId, selfId)
						return 1
					else
						Msg2Player( sceneId, selfId, "无法得到采集物品，请整理道具栏", 8, 3)
					end
				end
			end
        end
    else
        Msg2Player( sceneId, selfId, "你没有接受【德】益者三友，不能采集", 8, 3)
    end

    return 0
end

---------------------------------------------------------------------------------------------------
--任务日志刷新
---------------------------------------------------------------------------------------------------
function x300569_ProcQuestLogRefresh( sceneId, selfId, MissionId)
    
    local misIndex = GetQuestIndexByID( sceneId, selfId, x300569_g_MissionId)
	
	local fmt = {}
	for i = 1, 5 do
		fmt[i] = {}
		if GetQuestParam(sceneId, selfId, misIndex, i) == 1 then
			fmt[i][1] = "#G"
			fmt[i][2] = 1
		else
			fmt[i][1] = "#W"
			fmt[i][2] = 0
		end
	end
		
    local target = format(x300569_g_strMissionTarget2,
		fmt[1][1], fmt[1][2],
		fmt[2][1], fmt[2][2],
		fmt[3][1], fmt[3][2],
		fmt[4][1], fmt[4][2],
		fmt[5][1], fmt[5][2])
		
	BeginQuestEvent( sceneId)
        AddQuestLogCustomText( sceneId,
                               x300569_g_MissionName,               -- 标题
                               x300569_g_strMissionTitle,               -- 任务名字
                               target,			-- 任务目标
                               x300569_g_MissionReply,              -- 任务NPC
                               x300569_g_strMissionBook,            -- 任务攻略
                               x300569_g_MissionInfo,               -- 任务描述
                               x300569_g_MissionHelp)               -- 任务提示
    local level = GetLevel( sceneId, selfId)
    local exp = level * x300569_g_CoffExp
    if exp > 0 then
        AddQuestExpBonus( sceneId, exp)
    end
    	
    -- 现银奖励
    local money = level * x300569_g_CoffMoney
    if money > 0 then
        AddQuestMoneyBonus2( sceneId, money)
    end
    if x300569_g_Credit > 0 then
        AddQuestMoneyBonus5( sceneId, x300569_g_Credit)
    end
	EndQuestEvent()
	DispatchQuestLogUpdate( sceneId, selfId, MissionId)
end
