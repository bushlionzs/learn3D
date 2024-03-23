--MisDescBegin

-- 婆罗洲任务任务脚本ID
x305015_g_ScriptId = 305015
-- 接任务最小等级
x305015_g_LevelLess = 70
-- 任务名称
x305015_g_MissionName           = "【个人】四国争霸"

x305015_g_AwardItemId = 13011012 --奖励物品id

x305015_g_ExpBonus					= 	0   --奖励：经验 （数值填0，字符串为空，表示没有该项奖励）
x305015_g_BonusItem					=	{}	--奖励：物品

x305015_g_BonusMoney1               = 	0  --任务奖励绑定银币
x305015_g_BonusMoney2               =   0  --任务奖励非绑定银币
x305015_g_BonusMoney3               =   0  --任务奖励绑定金币
x305015_g_BonusMoney4               =   0  --任务奖励朝廷声望
x305015_g_BonusMoney5               =   0  --任务奖励江湖声望
x305015_g_BonusMoney6               = 450  --任务奖励荣誉

x305015_g_BonusChoiceItem           =   {}

--MisDescEnd

-- 任务描述
x305015_g_MissionDescription    = "\t这段时间以来，我们和其他三国之间的战争愈加激烈，虽然我国将士人人奋勇杀敌，可是在资源补给方面，我们并没有占据优势。\n\t近日探马来报，在中兴府的其他国家驻地，堆积了大量军用物资，如果我们能将其夺走，不仅能打击别国的士气，对我国军队的补给也有着莫大的好处。"
-- 任务攻略
x305015_g_MissionFlow           = "\t秘密潜入到别国远征军驻地，获得我军急需的物资，解燃眉之急。切记，遇到后一定要除掉他们，以免泄露此次行动，引来其他三国的报复。"
-- 任务提示
x305015_g_MissionHelp           = "\t你需要杀死别国探马，才可以成功获得本国军队所急需的物资。"
-- 任务目标
x305015_g_strMissionTarget      = "杀死@npc_%d并采集他附近的@item_%d#W(%d/3)。"
-- 放弃任务提示字符
x305015_g_strMissionAbandon     = "你放弃了任务：【个人】四国争霸"
-- 任务完成字符串
x305015_g_strMissionComplete    = "你完成了任务：【个人】四国争霸"
-- 接受任务提示
x305015_g_strMissionAccept      = "你接受了任务：【个人】四国争霸"
-- 任务继续信息
x305015_g_MissionContinue       = "\t请你前往#G%s#W，到其中击败草原%s，收集100个#G%s#W后交给我。"
-- 任务回复NPC
x305015_g_NPC                   = "@npc_%d"
-- 任务需要采集的总数
x305015_g_TotalCount            = 3
-- 目标国家ID
x305015_g_MP_TargetCountryId    = 1
-- 任务收集目标物品的ID
x305015_g_MP_TargetItemId       = 2
-- 收集到的物品计数
x305015_g_MP_ItemCount          = 3
-- 本周双倍任务经验奖励日
x305015_g_MP_DoubleDay          = 4
-- 银卡奖励系数
x305015_g_MoneyCoefficient      = 0
-- 经验系数
x305015_g_ExperienceCoefficient = 15000
-- 接任务日志ID
x305015_g_AcceptQuestID         = 1281
-- 交任务日志ID
x305015_g_FinishQuestID         = 1282
-- 楼兰NPC的Guid
x305015_g_Loulan_NPC_Guid       = 142600
-- 昆仑NPC的Guid
x305015_g_Kunlun_NPC_Guid       = 142601
-- 天山NPC的Guid
x305015_g_Laiyin_NPC_Guid       = 142602
-- 敦煌NPC的Guid
x305015_g_Dunhuang_NPC_Guid     = 142603
-- 任务NPC配置表
x305015_g_MissionNPC_Table      = {
                                    { typeId = 9720, posX = 50, posZ = 50, ai = 2, aiscript = 0, objGuid = 142600, campId = 16, liveTime = -1, name = "楼兰探马", timerId = 93 }, 
                                    { typeId = 9720, posX = 206, posZ = 50, ai = 2, aiscript = 0, objGuid = 142602, campId = 17, liveTime = -1, name = "天山探马", timerId = 94 }, 
                                    { typeId = 9720, posX = 50, posZ = 206, ai = 2, aiscript = 0, objGuid = 142601, campId = 18, liveTime = -1, name = "昆仑探马", timerId = 95 }, 
                                    { typeId = 9720, posX = 206, posZ = 206, ai = 2, aiscript = 0, objGuid = 142603, campId = 19, liveTime = -1, name = "敦煌探马", timerId = 96 }, 
}
-- 任务更新日期(1--366)，每天第一个玩家接此任务时更新此值
x305015_g_MissionUpdateDate     = 0
-- 
x305015_g_Group1                = { 0, 0 }
x305015_g_Group2                = { 0, 0 }
-- 国家及其ID对应表
x305015_g_CountryTable          = {
                                    { id = 0, name = "楼兰", npcId = 142600 }, 
                                    { id = 1, name = "天山", npcId = 142602 }, 
                                    { id = 2, name = "昆仑", npcId = 142601 }, 
                                    { id = 3, name = "敦煌", npcId = 142603 }, 
}
-- NPC复活时间（毫秒）
x305015_g_TargetNPC_ReliveTime  = 180000
-- 采集点每次最大采集数
x305015_g_MaxCount              = 3
-- 任务物品表
x305015_g_ItemTable             = { 13070010, 13070011, 13070012 }
-- 荣誉奖励
x305015_g_RongYu                = 450
-- 国家任务对应表
x305015_g_MissionTable          = {
                                    7100,  
                                    7101,  
                                    7102,  
                                    7103,  
}

function x305015_ProcEnumEvent( sceneId, selfId, targetId, MissionId)
    if GetLevel( sceneId, selfId) >= x305015_g_LevelLess then
        local missionId = 0
        for i, item in x305015_g_MissionTable do
            if IsHaveQuestNM( sceneId, selfId, item) ~= 0 then
                missionId = item
                break
            end
        end
        if missionId ~= 0 then
            local state = GetQuestStateNM( sceneId, selfId, targetId, x305015_GetMissionId( sceneId, selfId, missionId) )
            AddQuestNumText( sceneId, x305015_GetMissionId( sceneId, selfId, missionId), x305015_g_MissionName, state)
        else
            local state = GetQuestStateNM( sceneId, selfId, targetId, x305015_g_MissionTable[ GetCurCountry( sceneId, selfId) + 1] )
            AddQuestNumText( sceneId, x305015_g_MissionTable[ GetCurCountry( sceneId, selfId) + 1], x305015_g_MissionName, state)
        end
    end
end

function x305015_ProcEventEntry( sceneId, selfId, targetId, MissionId)
    if IsHaveQuestNM( sceneId, selfId, MissionId) == 0 then	-- 如果没有这个任务    
        -- 显示接受任务信息
        x305015_DispatchMissionInfo( sceneId, selfId, targetId)
    else--检查是不是可以提交    
		local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId)
        local isFinish = GetQuestParam( sceneId, selfId, misIndex, 7)
		if isFinish > 0 then -- 如果任务可以完成
			x305015_MissionComplateInfo( sceneId, selfId, targetId, MissionId) -- 显示完成信息
		else
			x305015_MissionContinue( sceneId, selfId, targetId, MissionId) -- 显示任务未完成信息
		end
    end
end

-- 任务继续信息
function x305015_MissionContinue( sceneId, selfId, targetId, MissionId)
	BeginQuestEvent( sceneId)
		AddQuestText( sceneId, "#Y"..x305015_g_MissionName)
        AddQuestText( sceneId, "\t怎么，你没有找到我们所需的物资？" )
	EndQuestEvent()
    DispatchQuestEventList( sceneId, selfId, targetId)
end

-- 显示接受任务信息
function x305015_DispatchMissionInfo( sceneId, selfId, NPCId )
	local level = GetLevel( sceneId, selfId)

	BeginQuestEvent( sceneId)

		--任务信息
		AddQuestText( sceneId, "#Y"..x305015_g_MissionName)
		AddQuestText( sceneId, x305015_g_MissionDescription)

		--任务目标
		AddQuestText( sceneId, "#Y任务目标：")
		AddQuestText( sceneId, x305015_g_MissionFlow )
		AddQuestText( sceneId, " ")
		AddQuestText( sceneId, " ")

		--提示信息
        AddQuestText( sceneId, "#Y小提示：")
        AddQuestText( sceneId, x305015_g_MissionHelp)
        -- AddQuestText( sceneId, " ")

		--任务奖励信息

		--1、经验
		local exp = GetLevel( sceneId, selfId) * x305015_g_ExperienceCoefficient
		if exp > 0 then
			AddQuestExpBonus( sceneId, exp)
		end

		--2、金钱1
        local money = level * x305015_g_MoneyCoefficient
		if money > 0 then
			AddQuestMoneyBonus1( sceneId, money)
		end

		--3、金钱2
		if x305015_g_BonusMoney2 > 0 then
			AddQuestMoneyBonus2(sceneId, x305015_g_BonusMoney2 )
		end

		--4、金钱3
		if x305015_g_BonusMoney3 > 0 then
			AddQuestMoneyBonus3(sceneId, x305015_g_BonusMoney3 )
		end

		--江湖声望
		if x305015_g_BonusMoney4 > 0 then
			AddQuestMoneyBonus4(sceneId, x305015_g_BonusMoney4 )
		end

		--朝廷声望
		if x305015_g_BonusMoney5 > 0 then
			AddQuestMoneyBonus5(sceneId, x305015_g_BonusMoney5 )
		end

		--荣誉值
		if x305015_g_BonusMoney6 > 0 then
			AddQuestMoneyBonus6(sceneId, x305015_g_BonusMoney6 )
		end

		--5、固定物品
		for i, item in x305015_g_BonusItem do
		   	AddQuestItemBonus(sceneId, item.item, item.n)
	    end

		--6、可选物品
		for i, item in x305015_g_BonusChoiceItem do
	    	AddQuestRadioItemBonus(sceneId, item.item, item.n)
	    end

	EndQuestEvent()

	DispatchQuestInfoNM( sceneId, selfId, NPCId, x305015_g_ScriptId, x305015_g_MissionTable[ GetCurCountry( sceneId, selfId) + 1]);
end

-- 检查当天是否已经接受过这个任务，接受过返回1，否则返回0
function x305015_CheckDayTimes( sceneId, selfId)
    local today = GetDayOfYear()

    if x305015_GetAcceptDate( sceneId, selfId) ~= today then
        return 0
    else
        return 1
    end
end

function x305015_ProcQuestAccept(sceneId, selfId, targetId, MissionId)
    if IsHaveQuestNM( sceneId, selfId, MissionId) == 0 then   -- 没有这个任务
        -- 检查当天是否已经做过这个任务
        local today = GetDayOfYear()
        if x305015_GetAcceptDate( sceneId, selfId) == today then
            Msg2Player( sceneId, selfId, "你今天已经完成过这个任务，请明天再来", 8, 3)
            return
        end
    	local result = AddQuest( sceneId, selfId, x305015_g_MissionTable[ GetCurCountry( sceneId, selfId) + 1], x305015_g_ScriptId, 1, 0, 1, 0)
    	if( result == 0) then
    		local str = "任务已满，任务接受失败！"
    		BeginQuestEvent( sceneId)
    		AddQuestText( sceneId, str)
    		EndQuestEvent( sceneId)
    		DispatchQuestTips( sceneId, selfId)
          	Msg2Player(sceneId, selfId, str, 8, 2)
    		return 0
        else
            -- 更新接任务时间
            x305015_SetAcceptDate( sceneId, selfId, today)

            -- 本日第一次接任务
            local oppoId = 0
            -- 获得接任务玩家国家
            local country = GetCurCountry( sceneId, selfId)
            if today ~= x305015_g_MissionUpdateDate then
                x305015_g_MissionUpdateDate = today
                x305015_g_Group1[ 1] = country
                -- 随机配对任务目标国家
                local allCountry = {}
                local count = 0
                -- 把玩家之外的三个国家Id放入allCountry
                for i = 0, 3 do
                    if country ~= i then
                        count = count + 1
                        allCountry[ count] = i
                    end
                end
                -- 从三个国家里随机选一个
                local rcount = 0
                x305015_g_Group1[ 2] = allCountry[ random( 1, count) ]
                oppoId = x305015_g_Group1[ 2]
                local remain = {}
                -- 收集剩下两个国家
                for i, item in allCountry do
                    if x305015_g_Group1[ 2] ~= item then
                        rcount = rcount + 1
                        remain[ rcount] = item
                    end
                end
                x305015_g_Group2[ 1] = remain[ 1]
                x305015_g_Group2[ 2] = remain[ 2]

                -- 每周一的第一次接任务时随机生成每个国家本周双倍经验日
                -- if GetWeek() == 1 then
                    -- SetCountryQuestData( sceneId, 0, CD_INDEX_POLUOZHOU_RANDOM_DAY, random( 1, 7) - 1)
                    -- SetCountryQuestData( sceneId, 1, CD_INDEX_POLUOZHOU_RANDOM_DAY, random( 1, 7) - 1)
                    -- SetCountryQuestData( sceneId, 2, CD_INDEX_POLUOZHOU_RANDOM_DAY, random( 1, 7) - 1)
                    -- SetCountryQuestData( sceneId, 3, CD_INDEX_POLUOZHOU_RANDOM_DAY, random( 1, 7) - 1)
                -- end
            else
                -- 直接从全局变量取
                if country == x305015_g_Group1[ 1] or country == x305015_g_Group1[ 2] then
                    if country == x305015_g_Group1[ 1] then
                        oppoId = x305015_g_Group1[ 2]
                    else
                        oppoId = x305015_g_Group1[ 1]
                    end
                else
                    if country == x305015_g_Group2[ 1] then
                        oppoId = x305015_g_Group2[ 2]
                    else
                        oppoId = x305015_g_Group2[ 1]
                    end
                end
            end

            -- 获取随机双倍经验日
            -- GetCountryQuestData( sceneId, selfId, CD_INDEX_POLUOZHOU_RANDOM_DAY, x305015_g_ScriptId, -1, "GetRandomDay" )

            local misIndex = GetQuestIndexByID( sceneId, selfId, x305015_g_MissionTable[ GetCurCountry( sceneId, selfId) + 1] )
			local targetItem = x305015_g_ItemTable[ random( 1, 3) ]
            SetQuestByIndex( sceneId, selfId, misIndex, 0, 0)
            SetQuestByIndex( sceneId, selfId, misIndex, 7, 0)
            SetQuestByIndex( sceneId, selfId, misIndex, x305015_g_MP_TargetCountryId, oppoId)
            SetQuestByIndex( sceneId, selfId, misIndex, x305015_g_MP_TargetItemId, targetItem)
            local minute = GetMinOfDay()
            if GetWeek() == 3 and minute >= 1200 and minute <= 1230 then
                SetQuestByIndex( sceneId, selfId, misIndex, x305015_g_MP_DoubleDay, 2)
            end
            SetQuestByIndex( sceneId, selfId, misIndex, x305015_g_MP_ItemCount, 0)

            -- 更新任务跟踪
            x305015_ProcQuestLogRefresh( sceneId, selfId, MissionId)

    		Msg2Player( sceneId, selfId, x305015_g_strMissionAccept, 8, 2)
    		Msg2Player( sceneId, selfId, x305015_g_strMissionAccept, 8, 3)

            -- 显示任务接取界面
			local name = ""
			for i, item in x305015_g_CountryTable do
				if oppoId == item.id then
					name = item.name
				end
			end
    		BeginQuestEvent( sceneId)
			AddQuestText( sceneId, "#Y"..x305015_g_MissionName)
    		AddQuestText( sceneId, format( "\t寻找并消灭#G%s探马#W，以免走漏消息。然后在%s远征军驻地周围获取@item_%d#W。", name, name, targetItem) )
    		EndQuestEvent( sceneId)
            DispatchQuestEventList( sceneId, selfId, targetId)

            -- 写日志
            GamePlayScriptLog( sceneId, selfId, x305015_g_AcceptQuestID)
        end
    else
        
        x305015_MissionComplate( sceneId, selfId, targetId, MissionId)
    end
end

function x305015_GetRandomDay( sceneId, selfId, MissionData, MissionId)
    if IsHaveQuestNM( sceneId, selfId, x305015_g_MissionTable[ GetCurCountry( sceneId, selfId) + 1] ) == 0 then
        return
    else
        local misIndex = GetQuestIndexByID( sceneId, selfId, x305015_g_MissionTable[ GetCurCountry( sceneId, selfId) + 1] )
        SetQuestByIndex( sceneId, selfId, misIndex, x305015_g_MP_DoubleDay, MissionData)
    end
end

function x305015_QuestLogRefresh( sceneId, selfId, MissionId)
    x305015_ProcQuestLogRefresh( sceneId, selfId, MissionId)
end

function x305015_GetMissionId( sceneId, selfId, MissionId)
    local missionId = x305015_g_MissionTable[ GetCurCountry( sceneId, selfId) + 1]
    if GetCurCountry( sceneId, selfId) ~= 0 then
        if MissionId == x305015_g_MissionTable[ 1] then
            missionId = MissionId
        end
    end

    return missionId
end

function x305015_ProcQuestLogRefresh( sceneId, selfId, MissionId)
    local misIndex = GetQuestIndexByID( sceneId, selfId, x305015_GetMissionId( sceneId, selfId, MissionId) )
    local oppoId = GetQuestParam( sceneId, selfId, misIndex, x305015_g_MP_TargetCountryId)
    local targetNPC = 0
    local itemId = GetQuestParam( sceneId, selfId, misIndex, x305015_g_MP_TargetItemId)
    -- 获得玩家背包里任务物品的数量
    local itemCount = GetItemCountInBag( sceneId, selfId, itemId)
	local npcId = 0
	local myCountry = GetCurCountry( sceneId, selfId)

    -- 获得目标国家名
    for i, item in x305015_g_CountryTable do
        if oppoId == item.id then
            targetNPC = item.npcId
        end
    end
	-- 回复NPC
    for i, item in x305015_g_CountryTable do
        if myCountry == item.id then
			npcId = item.npcId
        end
    end

    BeginQuestEvent( sceneId)
        AddQuestLogCustomText( sceneId,
                                "t",                            -- 标题
                                x305015_g_MissionName,          -- 任务名字
                                format( x305015_g_strMissionTarget, targetNPC, itemId, itemCount),     -- 任务目标
                                format( x305015_g_NPC, npcId),  -- 任务NPC
                                x305015_g_MissionFlow,          -- 任务攻略
                                x305015_g_MissionDescription,   -- 任务描述
                                x305015_g_MissionHelp)          -- 任务提示
    local exp = GetLevel( sceneId, selfId) * x305015_g_ExperienceCoefficient
    AddQuestExpBonus( sceneId, exp)
    -- 090302 银卡奖励
    local playerLevel = GetLevel( sceneId, selfId)
    if playerLevel > 80 then
        playerLevel = 80
    end
    --local money = playerLevel * x305015_g_MoneyCoefficient
    AddQuestMoneyBonus6(sceneId, x305015_g_BonusMoney6 )

    EndQuestEvent()
    DispatchQuestLogUpdate( sceneId, selfId, MissionId);
end

function x305015_Accept( sceneId, selfId, MissionId )
	return -1
end

function x305015_OnOpenItemBox( sceneId, selfId, targetId, growpointId, itemIndex)
    -- 检查有没有任务
    local missionId = 0
    for i, item in x305015_g_MissionTable do
        if IsHaveQuestNM( sceneId, selfId, item) ~= 0 then
            missionId = item
            break
        end
    end

    if missionId == 0 then
        return 1
    end

    local misIndex = GetQuestIndexByID( sceneId, selfId, x305015_GetMissionId( sceneId, selfId, missionId) )
    local oppoId = GetQuestParam( sceneId, selfId, misIndex, x305015_g_MP_TargetCountryId)
    local itemId = GetQuestParam( sceneId, selfId, misIndex, x305015_g_MP_TargetItemId)
    if itemId ~= itemIndex then
        Msg2Player( sceneId, selfId, "请依照任务提示，抢夺相应的资源。", 8, 3)
        return 1
    end
    local x, z = GetWorldPos( sceneId, selfId)
    -- local country = GetCurCountry( sceneId, selfId)
    if oppoId == 0 then    -- 楼兰
        if FindMonsterByGUID( sceneId, x305015_g_Loulan_NPC_Guid) ~= 4294967295 then
            Msg2Player( sceneId, selfId, "请先去杀死#G楼兰探马#cffcf00再来采集！", 8, 3)
            return 1
        else
            if x > 1 and x < 80 and z > 1 and z < 80 then
                return 0
            else
                Msg2Player( sceneId, selfId, "必须在#G楼兰探马#cffcf00附近采集", 8, 3)
                return 1
            end
        end
    elseif oppoId == 1 then    -- 天山
        if FindMonsterByGUID( sceneId, x305015_g_Laiyin_NPC_Guid) ~= 4294967295 then
            Msg2Player( sceneId, selfId, "请先去杀死#G天山探马#cffcf00再来采集！", 8, 3)
            return 1
        else
            if x > 176 and x < 256 and z > 1 and z < 80 then
                return 0
            else
                Msg2Player( sceneId, selfId, "必须在#G天山探马#cffcf00附近采集", 8, 3)
                return 1
            end
        end
    elseif oppoId == 2 then    -- 昆仑
        if FindMonsterByGUID( sceneId, x305015_g_Kunlun_NPC_Guid) ~= 4294967295 then
            Msg2Player( sceneId, selfId, "请先去杀死#G昆仑探马#cffcf00再来采集！", 8, 3)
            return 1
        else
            if x > 1 and x < 80 and z > 176 and z < 256 then
                return 0
            else
                Msg2Player( sceneId, selfId, "必须在#G昆仑探马#cffcf00附近采集", 8, 3)
                return 1
            end
        end
    elseif oppoId == 3 then    -- 敦煌
        if FindMonsterByGUID( sceneId, x305015_g_Dunhuang_NPC_Guid) ~= 4294967295 then
            Msg2Player( sceneId, selfId, "请先去杀死#G敦煌探马#cffcf00再来采集！", 8, 3)
            return 1
        else
            if x > 176 and x < 256 and z > 176 and z < 256 then
                return 0
            else
                Msg2Player( sceneId, selfId, "必须在#G敦煌探马#cffcf00附近采集", 8, 3)
                return 1
            end
        end
    end
end

function x305015_OnRecycle( sceneId, selfId, targetId, growpointId, itemIndex)
    -- print( "***x305015_OnRecycle***"..growpointId.."index: "..itemIndex)
    local missionId = 0
    for i, item in x305015_g_MissionTable do
        if IsHaveQuestNM( sceneId, selfId, item) ~= 0 then
            missionId = item
            break
        end
    end

    if missionId == 0 then
        return 0
    end

    -- 根据玩家背包已有的物品数量设置本次采集最大数
    local misIndex = GetQuestIndexByID( sceneId, selfId, x305015_GetMissionId( sceneId, selfId, missionId) )
    local itemCount = GetQuestParam( sceneId, selfId, misIndex, x305015_g_MP_ItemCount)
    local maxCount = x305015_g_MaxCount
    if itemCount > x305015_g_TotalCount - x305015_g_MaxCount then
        maxCount = x305015_g_TotalCount - itemCount
    end
    if maxCount == 0 then
        Msg2Player( sceneId, selfId, "任务已经完成，不能继续采集", 8, 3)
        return 0
    end
    local itemCount = random( 1, maxCount)
    BeginAddItem( sceneId)
    AddItem( sceneId, itemIndex, itemCount)
    if EndAddItem( sceneId, selfId) > 0 then
        AddItemListToPlayer( sceneId, selfId)

        -- 更新任务跟踪
        x305015_ProcQuestLogRefresh( sceneId, selfId, x305015_GetMissionId( sceneId, selfId, missionId) )

        return 1
    else
        Msg2Player( sceneId, selfId, "无法得到采集物品，请整理道具栏", 8, 3)
        return 0
    end
end

--杀死怪物
--场景ID, 自己的ID(组队状态下为接任务成员的Id), 怪物表位置号, 怪物objId, 任务ID
function x305015_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId)
end

--物品改变
function x305015_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId)--寻找材料的任务完成后再添加合成任务
    -- 检查有没有任务
    local missionId = 0
    for i, item in x305015_g_MissionTable do
        if IsHaveQuestNM( sceneId, selfId, item) ~= 0 then
            missionId = item
            break
        end
    end

    if missionId == 0 then
        return 1
    end

    local misIndex = GetQuestIndexByID( sceneId, selfId, x305015_GetMissionId( sceneId, selfId, missionId) )
    local itemId = GetQuestParam( sceneId, selfId, misIndex, x305015_g_MP_TargetItemId)
    if itemId ~= itemdataId then
        return 0
    end

    -- 获得玩家背包里任务物品的数量
    local itemCount = GetItemCountInBag( sceneId, selfId, itemId)
    SetQuestByIndex( sceneId, selfId, misIndex, x305015_g_MP_ItemCount, itemCount)
    if itemCount >= x305015_g_TotalCount then
        SetQuestByIndex( sceneId, selfId, misIndex, 7, 1)
        SetQuestByIndex( sceneId, selfId, misIndex, 0, 1)
        Msg2Player( sceneId, selfId, "任务已完成，快去交任务吧", 8, 3)
    else
        SetQuestByIndex( sceneId, selfId, misIndex, 7, 0)
        SetQuestByIndex( sceneId, selfId, misIndex, 0, 0)
    end

	return 0
end

function x305015_MissionComplateInfo( sceneId, selfId, targetId)
	BeginQuestEvent( sceneId)
	AddQuestText( sceneId, "#Y"..x305015_g_MissionName.."#W\n\t王国的英雄，你是远征军的骄傲！这些物资不知可以挽救多少我们受伤的兄弟！" )
    local exp = GetLevel( sceneId, selfId) * x305015_g_ExperienceCoefficient
    if exp > 0 then
        AddQuestExpBonus( sceneId, exp)
    end
    -- 090302 银卡奖励
    local playerLevel = GetLevel( sceneId, selfId)
    if playerLevel > 80 then
        playerLevel = 80
    end
    --local money = playerLevel * x305015_g_MoneyCoefficient
    AddQuestMoneyBonus6( sceneId, x305015_g_BonusMoney6)
	EndQuestEvent( sceneId)
    local missionId = 0
    for i, item in x305015_g_MissionTable do
        if IsHaveQuestNM( sceneId, selfId, item) ~= 0 then
            missionId = item
            break
        end
    end
	DispatchQuestInfoNM( sceneId, selfId, targetId, x305015_g_ScriptId, x305015_GetMissionId( sceneId, selfId, missionId) )
end

function x305015_MissionComplate( sceneId, selfId, targetId, MissionId)
    local misIndex = GetQuestIndexByID( sceneId, selfId, x305015_GetMissionId( sceneId, selfId, MissionId) )
    local itemId = GetQuestParam( sceneId, selfId, misIndex, x305015_g_MP_TargetItemId)
    local doubleDay = GetQuestParam( sceneId, selfId, misIndex, x305015_g_MP_DoubleDay)
    -- 获得玩家背包里任务物品的数量
    local itemCount = GetItemCountInBag( sceneId, selfId, itemId)
    -- 获得玩家等级
    local playerLevel = GetLevel( sceneId, selfId)
    DelQuest( sceneId, selfId, MissionId)
    -- 最终经验值
    local xp = x305015_g_ExperienceCoefficient * playerLevel
    DelItem( sceneId, selfId, itemId, itemCount)
    AddExp( sceneId, selfId, xp)
    -- 090302 银卡奖励
    -- if playerLevel > 80 then
        -- playerLevel = 80
    -- end
    -- local money = playerLevel * x305015_g_MoneyCoefficient
    --AddMoney( sceneId, selfId, 1, money)

    BeginQuestEvent( sceneId)
    AddQuestText( sceneId, x305015_g_strMissionComplete)
    EndQuestEvent( sceneId)
    DispatchQuestTips( sceneId, selfId)
    Msg2Player( sceneId, selfId, x305015_g_strMissionComplete, 8, 2)

    Msg2Player( sceneId, selfId, format( "你获得#R经验%d点#cffcf00的奖励", xp), 8, 2)
    BeginQuestEvent( sceneId)
    AddQuestText( sceneId, format( "你获得#R经验%d点#cffcf00的奖励", xp) )
    EndQuestEvent( sceneId)
    DispatchQuestTips( sceneId, selfId)

    --Msg2Player( sceneId, selfId, format( "获得#R银卡#{_MONEY%d}#cffcf00的奖励", money), 8, 3)
    --Msg2Player( sceneId, selfId, format( "获得#R银卡#{_MONEY%d}#cffcf00的奖励。", money), 8, 2)

    -- 给荣誉
    AddHonor(sceneId, selfId, x305015_g_RongYu)
    Msg2Player( sceneId, selfId, format( "你获得#R%d点荣誉#cffcf00的奖励", x305015_g_RongYu), 8, 3)
    Msg2Player( sceneId, selfId, format( "你获得#R%d点荣誉#cffcf00的奖励。", x305015_g_RongYu), 8, 2)

    local minute = GetMinOfDay()
    if doubleDay == 2 and GetWeek() == 3 and minute >= 1200 and minute <= 1230 then
        --AddExp( sceneId, selfId, xp)
        --Msg2Player( sceneId, selfId, format( "由于你在周三的20：00-20：30之间接取并交付本任务，你获得额外#R经验%d点#cffcf00的奖励", xp), 8, 3)
        --Msg2Player( sceneId, selfId, format( "由于你在周三的20：00-20：30之间接取并交付本任务，你获得额外#R经验%d点#cffcf00的奖励。", xp), 8, 2)
    end

    -- 更新交任务时间，避免第一天接任务，第二天交任务后可以立刻再接的问题
    local today = GetDayOfYear()
    x305015_SetAcceptDate( sceneId, selfId, today)

    -- 写日志
    GamePlayScriptLog( sceneId, selfId, x305015_g_FinishQuestID)
end

function x305015_GetAcceptDate( sceneId, selfId)
    return GetQuestData( sceneId, selfId, MD_POLO_DATE[ 1], MD_POLO_DATE[ 2], MD_POLO_DATE[ 3] )
end

function x305015_SetAcceptDate( sceneId, selfId, value)
    SetQuestData( sceneId, selfId, MD_POLO_DATE[ 1], MD_POLO_DATE[ 2], MD_POLO_DATE[ 3], value)
end

function x305015_ProcQuestAbandon( sceneId, selfId, MissionId)
    local missionId = 0
    for i, item in x305015_g_MissionTable do
        if IsHaveQuestNM( sceneId, selfId, item) ~= 0 then
            missionId = item
            break
        end
    end
    local misIndex = GetQuestIndexByID( sceneId, selfId, x305015_GetMissionId( sceneId, selfId, missionId) )
    local itemId = GetQuestParam( sceneId, selfId, misIndex, x305015_g_MP_TargetItemId)
	if DelQuestNM( sceneId, selfId, x305015_GetMissionId( sceneId, selfId, missionId) ) == 1 then
		Msg2Player( sceneId, selfId, x305015_g_strMissionAbandon, 8, 3)
		Msg2Player( sceneId, selfId, x305015_g_strMissionAbandon.."。", 8, 2)
        x305015_SetAcceptDate( sceneId, selfId, GetDayOfYear() )
        -- 获得玩家背包里任务物品的数量
        local itemCount = GetItemCountInBag( sceneId, selfId, itemId)
        if itemCount > 0 then
            -- 删除任务物品
            DelItem( sceneId, selfId, itemId, itemCount)
        end
	end
end

function x305015_ProcQuestSubmit( sceneId, selfId, targetId, chooseId, MissionId )
end

function x305015_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )

end
