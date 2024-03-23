--MisDescBegin

x300565_g_ScriptId 					= 300565                  --脚本ID
x300565_g_MissionId 				= 9302                    --任务ID

x300565_g_MissionKind 				= 2                       --任务类型
x300565_g_LevelLess					= 40                      --场景开放等级  <=0 表示不限制

x300565_g_MissionName				= "【个人】相国寺比武"                                        --任务名称(512)
x300565_g_MissionTarget				= "  找到@npc_%d"      --任务目标
x300565_g_MissionInfo				= "\t我们大相国寺正在召集天下武林人士，召开武林大会，推选新一届的武林盟主。\n\t这位施主看来武功不凡，若你也想参加这武林大会，可以去找我寺主持@npc_%d。"            --任务信息
x300565_g_MissionInfo1	            = "\t阿弥陀佛。\n\t施主也是来参加这武林大会的？我观施主目有精光，显然是内功深湛之人，你可先去和@npc_%d切磋一番。"
x300565_g_ContinueInfo				= "\t施主为何还在此徘徊，莫非心生胆怯？"  --任务继续信息
x300565_g_MissionCompleted			= "\t如今这武林中果然是英才辈出啊，想不到这么快施主就得胜归来，恭喜施主了。\n\t武林大会举办之日，还请施主定要光临本寺。"  --任务完成信息
x300565_g_MissionHelp				= ""          --任务提示信息
-- 任务放弃提示信息
x300565_g_strMissionAbandon         = "您放弃了任务：【个人】相国寺比武"

--目标
x300565_g_ExtTarget					= { {type=20,n=1,target=""} }


--奖励
x300565_g_ExpBonus					= 0             --奖励：经验 （数值填0，字符串为空，表示没有该项奖励）
x300565_g_BonusItem					= {}	--奖励：物品

x300565_g_BonusMoney1               = 0  --任务奖励绑定银币
x300565_g_BonusMoney2               = 0  --任务奖励非绑定银币
x300565_g_BonusMoney3               = 0  --任务奖励绑定金币
x300565_g_BonusMoney4               = 0  --任务奖励朝廷声望
x300565_g_BonusMoney5               = 0  --任务奖励江湖声望
x300565_g_BonusMoney6               = 0  --任务奖励荣誉

x300565_g_BonusChoiceItem           = {}


--MisDescEnd

-- 测试这个脚本MapServer必须用loadscriptonce参数启动

--任务目标顺序
x300565_MP_FINDMASTER               = 1 -- 找到大师标记
x300565_MP_TARGETINDEX              = 2 -- 最终召唤武林高手的NPC在x300565_g_TargetNPCList的索引
x300565_MP_ISCOMPLETE				= 7	-- 代表完成 0未完成， 1完成

x300565_g_strMissionFull            = "任务已满，任务接受失败"
x300565_g_strMissionAccept          = "您接受了任务：【个人】相国寺比武"
x300565_g_strMissionBook            = "\t@npc_139300就在大相国寺内等待各路武林英豪，少侠还是快快前往吧。"
x300565_g_strMonsterHasCreated      = "\t方才那位少侠已经在挑战，#G你可以与他一起和我切磋#W，放心，我并不担心你们倚多为胜。"
x300565_g_strMonsterCreated         = "\t智障大师让你来的？\n\t好的，我就和你切磋一番，不必担心，我只会使出二成功力。"
x300565_g_strMissionFinished        = "你完成了任务：【个人】相国寺比武"
x300565_g_strMissionRefrain         = "很抱歉，你今天已经做过此任务，不能再次领取。"
x300565_g_strMissionTarget2         = "\t战胜#G%s#W(%d/1)"
x300565_g_strMissionInfo2           = "\t和@npc_%d切磋武艺"
x300565_g_strMissionInfo3           = "\t战胜#S%s"
x300565_g_strMissionBook1           = "\t回复@npc_139300"
-- 接受任务记录日志ID
x300565_g_AcceptMissionLogID        = 931
-- 完成任务记录日志ID
x300565_g_FinishMissionLogID        = 932
-- 智障禅师guid
x300565_g_TargetNPC                 = 139300
-- 接任务NPC
x300565_g_MissionNPC                = 139116
-- 交任务NPC
x300565_g_MissionReply              = "@npc_139300"
-- 杀怪有效范围，武林人士被做掉时，在这个矩形中的玩家如果接了相关任务就都算完成
x300565_g_Range                     = 20
-- 经验奖励系数
--x300565_g_CoffExp                   = 2000
-- 声望奖励系数
x300565_g_CoffCredit                = 0
-- 发布NPC列表
x300565_g_TargetNPCList             = {
                                        { id = 139323, monsterId = 0, constId = 1056, bornTime = -1, name = "何足道" }, 
                                        { id = 139326, monsterId = 0, constId = 1052, bornTime = -1, name = "风陵师太"}, 
                                        { id = 139320, monsterId = 0, constId = 1050, bornTime = -1, name = "张三丰" }, 
                                        { id = 139331, monsterId = 0, constId = 1051, bornTime = -1, name = "郭破虏" }, 
                                        { id = 139338, monsterId = 0, constId = 1054, bornTime = -1, name = "铁中堂" }, 
                                        { id = 139341, monsterId = 0, constId = 1053, bornTime = -1, name = "西门君临" }, 
                                        { id = 139346, monsterId = 0, constId = 1055, bornTime = -1, name = "陈铁志" }, 
}
-- 玩法开关id
x300565_g_IsEnableId                = 1004
-- 任务奖励物品列表
x300565_g_RewardTable               = {
                                { minLevel = 40, maxLevel = 60,  items = { { id = 11000201, cnt = 8 }, { id = 11050002, cnt = 8 }, { id = 12030120, cnt = 1 }, { id = 12030130, cnt = 1 }, { id = 12030140, cnt = 1 } } }, 
                                { minLevel = 60, maxLevel = 80,  items = { { id = 11000202, cnt = 8 }, { id = 11050003, cnt = 8 }, { id = 12030120, cnt = 1 }, { id = 12030130, cnt = 1 }, { id = 12030140, cnt = 1 } } }, 
                                { minLevel = 80, maxLevel = 999, items = { { id = 11000203, cnt = 8 }, { id = 11050004, cnt = 8 }, { id = 12030120, cnt = 1 }, { id = 12030130, cnt = 1 }, { id = 12030140, cnt = 1 } } }, 
}

---------------------------------------------------------------------------------------------------
--列举事件
---------------------------------------------------------------------------------------------------
function x300565_ProcEnumEvent( sceneId, selfId, NPCId, MissionId)

    if GetLevel( sceneId, selfId) < x300565_g_LevelLess then
        return 0
    end

    -- print( "*-*-*-*-*-*" )
    local npcGuid = GetMonsterGUID( sceneId, NPCId)
    if npcGuid == x300565_g_TargetNPC then
        return 0
    end
    if IsHaveQuestNM( sceneId, selfId, x300565_g_MissionId) > 0 then
        return 0
    end
    AddQuestNumText( sceneId, x300565_g_MissionId, x300565_g_MissionName, GetQuestStateNM( sceneId, selfId, NPCId, x300565_g_MissionId), 1)
end

---------------------------------------------------------------------------------------------------
--任务入口函数
---------------------------------------------------------------------------------------------------
function x300565_ProcEventEntry( sceneId, selfId, NPCId, MissionId, nExtIdx)

    if GetGameOpenById( x300565_g_IsEnableId) <= 0 and IsHaveQuestNM( sceneId, selfId, x300565_g_MissionId) == 0 then
        x300565_ShowTips(sceneId, selfId, "此活动今天不开放，详情请到大都包打处听查询每日新鲜事")
        return
    end
    
	if IsHaveQuestNM( sceneId, selfId, x300565_g_MissionId) > 0 then  -- 如果已经接过这个任务
        local misIndex = GetQuestIndexByID( sceneId, selfId, x300565_g_MissionId)
        local npcGuid = GetMonsterGUID( sceneId, NPCId)
        local index = GetQuestParam( sceneId, selfId, misIndex, x300565_MP_TARGETINDEX)
        if npcGuid == x300565_g_MissionNPC then
            local bDone = x300565_CheckSubmit( sceneId, selfId, NPCId)
            if bDone > 0 then
                x300565_DispatchCompletedInfo( sceneId, selfId, NPCId) --完成任务显示
            else
                x300565_DispatchContinueInfo( sceneId, selfId, NPCId) --未完成任务显示
            end
        elseif npcGuid == x300565_g_TargetNPC then
            local bDone = x300565_CheckSubmit( sceneId, selfId, NPCId)
            if bDone > 0 then
                x300565_DispatchCompletedInfo( sceneId, selfId, NPCId) --完成任务显示
            else
                if GetQuestParam( sceneId, selfId, misIndex, x300565_MP_FINDMASTER) == 0 then
	                -- 随机选择一个NPC
	                local index1 = random( 1, getn( x300565_g_TargetNPCList) )
	                local npcId = x300565_g_TargetNPCList[ index1].id
	                SetQuestByIndex( sceneId, selfId, misIndex, x300565_MP_TARGETINDEX, index1)
	                BeginQuestEvent( sceneId)
	                    AddQuestText( sceneId, "#Y"..x300565_g_MissionName)
	                    AddQuestText( sceneId, format( x300565_g_MissionInfo1, npcId) )
	                    AddQuestText( sceneId, " ")
	                    AddQuestText( sceneId, "#Y任务目标：")
	                    AddQuestText( sceneId, format( x300565_g_MissionTarget, npcId) )
	                    AddQuestText( sceneId, " ")
	                EndQuestEvent( sceneId)
	                DispatchQuestEventList( sceneId, selfId, NPCId)
	                SetQuestByIndex( sceneId, selfId, misIndex, x300565_MP_FINDMASTER, 1)
	                x300565_ProcQuestLogRefresh( sceneId, selfId, MissionId)
                else
                	x300565_DispatchContinueInfo( sceneId, selfId, NPCId) --未完成任务显示
                end
            end
        elseif index ~= 0 then
            if npcGuid ~= x300565_g_TargetNPCList[ index].id then
                return
            end
            if x300565_g_TargetNPCList[ index].monsterId == 0 then
                BeginQuestEvent( sceneId)
                    AddQuestText( sceneId, x300565_g_strMonsterCreated)
                EndQuestEvent( sceneId)
                DispatchQuestEventList( sceneId, selfId, NPCId)

                local x, z = GetWorldPos( sceneId, NPCId)
                -- 创建武林高手
                x300565_g_TargetNPCList[ index].monsterId = CreateMonster( sceneId, x300565_g_TargetNPCList[ index].constId, x + random( -2, 2), z + random( -2, 2), 1, 0, x300565_g_ScriptId, -1, 21, 1200000)
                if x300565_g_TargetNPCList[ index].monsterId >= 0 then
                    x300565_g_TargetNPCList[ index].bornTime = GetMinOfDay()
                end
            else
                -- 高手已经被创建过
                local liveTime = 0
                if GetMinOfDay() < x300565_g_TargetNPCList[ index].bornTime then
                    liveTime = GetMinOfDay() + 1440 - x300565_g_TargetNPCList[ index].bornTime
                else
                    liveTime = GetMinOfDay() - x300565_g_TargetNPCList[ index].bornTime
                end
                if liveTime >= 20 then
                    -- 如果敌人被创建20分钟了还没被做掉会自动消失，需要再次创建
                    BeginQuestEvent( sceneId)
                        AddQuestText( sceneId, x300565_g_strMonsterCreated)
                    EndQuestEvent( sceneId)
                    DispatchQuestEventList( sceneId, selfId, NPCId)

                    local x, z = GetWorldPos( sceneId, NPCId)
                    -- 创建武林高手
                    x300565_g_TargetNPCList[ index].monsterId = CreateMonster( sceneId, x300565_g_TargetNPCList[ index].constId, x + random( -2, 2), z + random( -2, 2), 1, 0, x300565_g_ScriptId, -1, 21, 1200000)
                    if x300565_g_TargetNPCList[ index].monsterId >= 0 then
                        x300565_g_TargetNPCList[ index].bornTime = GetMinOfDay()
                    end
                else
                    BeginQuestEvent( sceneId)
                        AddQuestText( sceneId, x300565_g_strMonsterHasCreated)
                    EndQuestEvent( sceneId)
                    DispatchQuestEventList( sceneId, selfId, NPCId)
                end
            end
            SetQuestByIndex( sceneId, selfId, misIndex, x300565_MP_FINDMASTER, 2)
            x300565_ProcQuestLogRefresh( sceneId, selfId, MissionId)
        end
	else
		x300565_DispatchMissionInfo( sceneId, selfId, NPCId)	--任务信息显示
	end
end

---------------------------------------------------------------------------------------------------
--检测接受条件
---------------------------------------------------------------------------------------------------
function x300565_ProcAcceptCheck( sceneId, selfId, npcId)
	local bHaveMission	= IsHaveQuestNM( sceneId, selfId, x300565_g_MissionId)
	if( bHaveMission > 0) then
		return 0;
	else
		return 1;
	end
end

---------------------------------------------------------------------------------------------------
--接受条件
---------------------------------------------------------------------------------------------------
function x300565_ProcQuestAccept( sceneId, selfId, targetId, missionId)

    local name = GetName( sceneId, selfId)
    if IsHaveQuestNM( sceneId, selfId, x300565_g_MissionId) > 0 then
    else
        local npcGuid = GetMonsterGUID( sceneId, targetId)
        if npcGuid ~= x300565_g_MissionNPC then
            return 0
        end
        local today = GetDayOfYear()
        if x300565_GetMissionDate( sceneId, selfId) == today then
            Msg2Player( sceneId, selfId, x300565_g_strMissionRefrain, 8, 3)
            return 0
        end
        
        --检查前置任务
		local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId,x300565_g_MissionId  )
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
        
        if GetQuestData( sceneId, selfId, MD_RICHANG_DAY[ 1], MD_RICHANG_DAY[ 2], MD_RICHANG_DAY[ 3] ) == GetDayOfYear() then
            if GetQuestData( sceneId, selfId, MD_RICHANG_COUNT[ 1], MD_RICHANG_COUNT[ 2], MD_RICHANG_COUNT[ 3] ) >= 3 then
                Msg2Player( sceneId, selfId, "你不能再领取今天的日常任务了", 8, 3)
                return 0
            end
        else
            SetQuestData( sceneId, selfId, MD_RICHANG_COUNT[1], MD_RICHANG_COUNT[2], MD_RICHANG_COUNT[3], 0)
        end

        local ret = AddQuest( sceneId, selfId, x300565_g_MissionId, x300565_g_ScriptId, 0, 0, 0, 1)
        if ret == 0 then
            LuaScenceM2Player( sceneId, selfId, x300565_g_strMissionFull, name, 3, 1)
            return 0
        else
            -- 显示任务接受信息
            LuaScenceM2Player( sceneId, selfId, x300565_g_strMissionAccept, name, 3, 1)
            LuaScenceM2Player( sceneId, selfId, x300565_g_strMissionAccept, name, 2, 1)
        end

        BeginQuestEvent( sceneId)
            AddQuestText( sceneId, "#Y"..x300565_g_MissionName)
            AddQuestText( sceneId, x300565_g_strMissionBook)
        EndQuestEvent( sceneId)
        DispatchQuestEventList( sceneId, selfId, targetId)

        local misIndex = GetQuestIndexByID( sceneId, selfId, x300565_g_MissionId)
        SetQuestByIndex( sceneId, selfId, misIndex, 0, 0)
        SetQuestByIndex( sceneId, selfId, misIndex, 1, 0)
        SetQuestByIndex( sceneId, selfId, misIndex, 2, 0)
        SetQuestByIndex( sceneId, selfId, misIndex, 7, 0)

        -- 写日志
        GamePlayScriptLog( sceneId, selfId, x300565_g_AcceptMissionLogID)
    end
end

---------------------------------------------------------------------------------------------------
function x300565_ShowTips(sceneId, selfId, str)
	BeginQuestEvent(sceneId);
		AddQuestText(sceneId,str);
	EndQuestEvent();
	DispatchQuestTips(sceneId, selfId);
end
--放弃任务
---------------------------------------------------------------------------------------------------
function x300565_ProcQuestAbandon( sceneId, selfId, MissionId)
	local bHaveMission	= IsHaveQuestNM(sceneId, selfId, x300565_g_MissionId)
	if bHaveMission > 0 then
		local misIndex = GetQuestIndexByID( sceneId, selfId, x300565_g_MissionId)
		DelQuest( sceneId, selfId, x300565_g_MissionId)
		
        --x300565_SetMissionDate( sceneId, selfId, GetDayOfYear() )
        local today = GetDayOfYear()
        SetQuestData( sceneId, selfId, MD_WULINDAHUI_DATE[ 1], MD_WULINDAHUI_DATE[ 2], MD_WULINDAHUI_DATE[ 3], today)
		if today == GetQuestData( sceneId, selfId, MD_RICHANG_DAY[1], MD_RICHANG_DAY[2], MD_RICHANG_DAY[3] ) then
            local count = GetQuestData( sceneId, selfId, MD_RICHANG_COUNT[1], MD_RICHANG_COUNT[2], MD_RICHANG_COUNT[3] )
            if count < 3 then
                SetQuestData( sceneId, selfId, MD_RICHANG_COUNT[1], MD_RICHANG_COUNT[2], MD_RICHANG_COUNT[3], 1 + count)
            end
        else
            SetQuestData( sceneId, selfId, MD_RICHANG_DAY[1], MD_RICHANG_DAY[2], MD_RICHANG_DAY[3], today)
            SetQuestData( sceneId, selfId, MD_RICHANG_COUNT[1], MD_RICHANG_COUNT[2], MD_RICHANG_COUNT[3], 1)
        end

		Msg2Player( sceneId, selfId, x300565_g_strMissionAbandon, 8, 3)
		Msg2Player( sceneId, selfId, x300565_g_strMissionAbandon, 8, 2)
	end
end

---------------------------------------------------------------------------------------------------
--检查任务是否可提交
---------------------------------------------------------------------------------------------------
function x300565_CheckSubmit( sceneId, selfId, NPCId)
	local misIndex = GetQuestIndexByID( sceneId, selfId, x300565_g_MissionId)

    if GetQuestParam( sceneId, selfId, misIndex, 0) == 1 and GetQuestParam( sceneId, selfId, misIndex, 7) == 1 then
        return 1
    else
        return 0
    end
end

---------------------------------------------------------------------------------------------------
--获得奖励
---------------------------------------------------------------------------------------------------
function x300565_GetBonus( sceneId, selfId,NpcID, SelectId)
	--奖励金钱1
	if x300565_g_BonusMoney1 > 0 then
	    AddMoney( sceneId, selfId, 1, x300565_g_BonusMoney1 )
	    Msg2Player(sceneId,selfId,format("获得银卡#{_MONEY%d}的奖励。", x300565_g_BonusMoney1),4,2)
	end

	--奖励金钱2
	if x300565_g_BonusMoney2 > 0 then
	    AddMoney( sceneId, selfId, 0, x300565_g_BonusMoney2 )
	    Msg2Player(sceneId,selfId,format("获得银币#{_MONEY%d}的奖励。", x300565_g_BonusMoney2),4,2)
	end

	--奖励金钱1
	if x300565_g_BonusMoney3 > 0 then
	    AddMoney( sceneId, selfId, 3, x300565_g_BonusMoney3 )
	    Msg2Player(sceneId,selfId,format("获得金卡#{_MONEY%d}的奖励。", x300565_g_BonusMoney3),4,2)
	end

	--江湖声望
	if x300565_g_BonusMoney4 > 0 then
		local nRongYu = GetRongYu( sceneId, selfId )
		nRongYu = nRongYu + x300565_g_BonusMoney4
		SetRongYu( sceneId, selfId, nRongYu )
		Msg2Player(sceneId,selfId,format("获得江湖声望%d的奖励。", x300565_g_BonusMoney4),4,2)
	end

	--朝廷声望
	if x300565_g_BonusMoney5 > 0 then
		local nShengWang = GetShengWang( sceneId, selfId )
		nShengWang = nShengWang + x300565_g_BonusMoney5
		SetShengWang( sceneId, selfId, nShengWang )
		Msg2Player(sceneId,selfId,format("获得朝廷声望%d的奖励。", x300565_g_BonusMoney5),4,2)
	end

	--朝廷声望
	if x300565_g_BonusMoney6 > 0 then
		AddHonor(sceneId,selfId,x300565_g_BonusMoney6)
		Msg2Player(sceneId,selfId,format("获得荣誉值%d的奖励。", x300565_g_BonusMoney6),4,2)
	end

 	--奖励固定物品
	for i, item in x300565_g_BonusItem do
 		BeginAddItem(sceneId)
		AddItem( sceneId, item.item, item.n )
		local ret = EndAddItem(sceneId,selfId)
		if ret > 0 then
			AddItemListToPlayer(sceneId,selfId)
		else
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"物品栏已满，无法得到任务物品！")
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
		end
    end

	--奖励可选物品
	for i, item in x300565_g_BonusChoiceItem do
	    if item.item == SelectId then
	        BeginAddItem(sceneId)
			AddItem( sceneId, item.item, item.n )
			local ret = EndAddItem(sceneId,selfId)
			if ret > 0 then
				AddItemListToPlayer(sceneId,selfId)
			else
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"物品栏已满，无法得到任务物品！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
			end

			--获取完必，请返回，防止重复添加
			return
		end
    end
end

---------------------------------------------------------------------------------------------------
--提交任务，不管任务是否完成或是任务，显示任务继续信息或是任务完成信息
---------------------------------------------------------------------------------------------------
function x300565_ProcQuestSubmit( sceneId, selfId, NPCId, selectRadioId, MissionId)
    if GetGameOpenById( x300565_g_IsEnableId) <= 0 and IsHaveQuestNM( sceneId, selfId, x300565_g_MissionId) == 0 then
        return
    end

	if IsHaveQuestNM( sceneId, selfId, x300565_g_MissionId) <= 0 then
        return 0
    end
    
    local today = GetDayOfYear()
    local count = GetQuestData( sceneId, selfId, MD_RICHANG_COUNT[1], MD_RICHANG_COUNT[2], MD_RICHANG_COUNT[3] )
    if today == GetQuestData(sceneId, selfId, MD_RICHANG_DAY[1], MD_RICHANG_DAY[2],MD_RICHANG_DAY[3] ) and count >= 3 then
        Msg2Player( sceneId, selfId, "今天的日常任务已经不能再交了，请明天再来", 8, 3)
        return 0
    end

    -- 检查玩家选择的奖励是不是可判定非绑定的
	local level = GetLevel( sceneId, selfId)
    local canBind = 0
    local count = 0
    local id = 0
    for i, item in x300565_g_RewardTable do
        if level >= item.minLevel and level < item.maxLevel then
            for j, iter in item.items do
                if selectRadioId == iter.id then
                    if j <= 2 then
                        canBind = 1
                    end
                    count = iter.cnt
                    id = iter.id
                    break
                end
            end
            break
        end
    end

    -- 特殊情况处理，玩家在选择物品后升级跨越到下个奖励区时的处理
    if count == 0 then
        for i, item in x300565_g_RewardTable do
            for j, iter in item.items do
                if selectRadioId == iter.id then
                    if j <= 2 then
                        canBind = 1
                    end
                    count = iter.cnt
                    id = iter.id
                    break
                end
            end
        end
    end

    if id == 0 or count == 0 then
        return 0
    end

	BeginAddItem(sceneId)
    if IsHaveSpecificImpact( sceneId, selfId, 9011) == 1 or IsHaveSpecificImpact( sceneId, selfId, 9012) == 1 or IsHaveSpecificImpact( sceneId, selfId, 9013) == 1 then
        if canBind == 1 then
            AddItem( sceneId, id, count)
        else
            AddBindItem( sceneId, id, count)
        end
    else
		AddBindItem( sceneId, id, count)
    end
		
	local ret = EndAddItem(sceneId,selfId)
	if ret > 0 then
		AddItemListToPlayer(sceneId,selfId)

        Msg2Player( sceneId, selfId, format( "您获得了物品：@itemid_%d",id), 8, 3)
	else
        Msg2Player( sceneId, selfId, "背包空间不足，无法获得任务奖励物品，交任务失败", 8, 3)
        return 0
	end
    CallScriptFunction( 256225, "Finishbiwu", sceneId, selfId)
    CallScriptFunction( 270300, "OnSubmissionFinished", sceneId, selfId, x300565_g_MissionId)
    DelQuest( sceneId, selfId, x300565_g_MissionId)
    local name = GetName( sceneId, selfId)
    LuaScenceM2Player( sceneId, selfId, x300565_g_strMissionFinished, name, 3, 1)
    LuaScenceM2Player( sceneId, selfId, x300565_g_strMissionFinished.."。", name, 2, 1)
    x300565_SetMissionDate( sceneId, selfId, GetDayOfYear() )
    GamePlayScriptLog( sceneId, selfId, x300565_g_FinishMissionLogID)
end

---------------------------------------------------------------------------------------------------
--向客户端发送任务信息
---------------------------------------------------------------------------------------------------
function x300565_DispatchMissionInfo( sceneId, selfId, NPCId)
	BeginQuestEvent( sceneId)

    --任务信息
    AddQuestText( sceneId, "#Y"..x300565_g_MissionName)
    AddQuestText( sceneId, format( x300565_g_MissionInfo, x300565_g_TargetNPC) )
    AddQuestText( sceneId, " ")

    --任务目标
    AddQuestText( sceneId, "#Y任务目标：")
    AddQuestText( sceneId, format( x300565_g_MissionTarget, x300565_g_TargetNPC) )
    AddQuestText( sceneId, " ")

    --提示信息
    if x300565_g_MissionHelp ~= "" then
        AddQuestText( sceneId, "#Y任务提示：")
        AddQuestText( sceneId, x300565_g_MissionHelp)
        AddQuestText( sceneId, " ")
    end                 

    --任务奖励信息
	local level = GetLevel(sceneId, selfId)
    for i, item in x300565_g_RewardTable do
        if level >= item.minLevel and level < item.maxLevel then
            for j, iter in item.items do
                AddQuestRadioItemBonus( sceneId, iter.id, iter.cnt)
            end
            break
        end
    end

	EndQuestEvent()
	DispatchQuestInfoNM( sceneId, selfId, NPCId, x300565_g_ScriptId, x300565_g_MissionId)
end

---------------------------------------------------------------------------------------------------
--向客户端发送任务未完成
---------------------------------------------------------------------------------------------------
function x300565_DispatchContinueInfo( sceneId, selfId, NPCId)
	BeginQuestEvent( sceneId)
    AddQuestText( sceneId, "#Y"..x300565_g_MissionName)
    AddQuestText( sceneId, x300565_g_ContinueInfo)
    AddQuestText( sceneId, " ")
    local playerLevel = GetLevel( sceneId, selfId)
    -- if x300565_g_CoffExp > 0 then
        -- AddQuestExpBonus( sceneId, playerLevel * x300565_g_CoffExp)
    -- end
    -- if x300565_g_CoffCredit > 0 then
        -- AddQuestMoneyBonus5( sceneId, x300565_g_CoffCredit)
    -- end
    -- AddQuestItemBonus( sceneId, 11050002, 5)
    -- AddQuestText( sceneId, " " )
    -- AddQuestText( sceneId, "#Y奖励内容：" )
    --AddQuestText( sceneId, format( "经验值：%d点", playerLevel * x300565_g_CoffExp) )
    --AddQuestText( sceneId, format( "声望：%d点", x300565_g_CoffCredit) )
	EndQuestEvent( sceneId)
	DispatchQuestEventList( sceneId, selfId, NPCId)
	--DispatchQuestInfoNM( sceneId, selfId, NPCId, x300565_g_ScriptId, x300565_g_MissionId)
end

---------------------------------------------------------------------------------------------------
--向客户端发送任务完成信息
---------------------------------------------------------------------------------------------------
function x300565_DispatchCompletedInfo( sceneId, selfId, NPCId)
    if IsHaveQuestNM( sceneId, selfId, x300565_g_MissionId) > 0 then
        BeginQuestEvent( sceneId)
        AddQuestText( sceneId, "#Y"..x300565_g_MissionName)
        AddQuestText( sceneId, x300565_g_MissionCompleted)
        AddQuestText( sceneId, " ")
        local level = GetLevel(sceneId, selfId)
        for i, item in x300565_g_RewardTable do
            if level >= item.minLevel and level < item.maxLevel then
                for j, iter in item.items do
                    AddQuestRadioItemBonus( sceneId, iter.id, iter.cnt)
                end
                break
            end
        end
        EndQuestEvent()
        DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x300565_g_ScriptId, x300565_g_MissionId)
    else
        BeginQuestEvent( sceneId)
            AddQuestText( "你身上无此任务！" )
        EndQuestEvent()
        DispatchQuestEventList( sceneId, selfId, NPCId)
    end
end

---------------------------------------------------------------------------------------------------
--怪物被杀的消息处理
---------------------------------------------------------------------------------------------------
function x300565_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId)
end

function x300565_OnDie( sceneId, selfId, killerId)
    -- 查找被杀怪物是不是武林高手
    local index = 0
    for i, item in x300565_g_TargetNPCList do
        if selfId == item.monsterId then
            index = i
        end
    end
    if index == 0 then
        return
    else
        x300565_g_TargetNPCList[ index].monsterId = 0
    end

    if GetGameOpenById( x300565_g_IsEnableId) <= 0 and IsHaveQuestNM( sceneId, selfId, x300565_g_MissionId) == 0 then
        return
    end

    -- 获得怪物被杀死时的位置
    local x, z = GetWorldPos( sceneId, selfId)
    -- 获得当前场景的总人数
    local humanCount = GetScenePlayerCount( sceneId)
    for i = 0, humanCount - 1 do
        local humanId = GetScenePlayerObjId( sceneId, i)
        if humanId >= 0 and IsPlayerStateNormal( sceneId, humanId) == 1 and IsHaveQuestNM( sceneId, humanId, x300565_g_MissionId) > 0 then
            -- 
            local playerx, playerz = GetWorldPos( sceneId, humanId)
            if abs( x - playerx) <= x300565_g_Range and abs( z - playerz) <= x300565_g_Range and GetHp( sceneId, humanId) > 0 then
                local misIndex = GetQuestIndexByID( sceneId, humanId, x300565_g_MissionId)
                if GetQuestParam( sceneId, humanId, misIndex, x300565_MP_TARGETINDEX) == index and GetQuestParam( sceneId, humanId, misIndex, 0) == 0 then
                    SetQuestByIndex( sceneId, humanId, misIndex, 7, 1)
                    SetQuestByIndex( sceneId, humanId, misIndex, 0, 1)
                    Msg2Player( sceneId, humanId, "任务已完成，快去找智障禅师交任务吧", 8, 3)
                    x300565_ProcQuestLogRefresh( sceneId, humanId, x300565_g_MissionId)
                end
            end
        end
    end
end

---------------------------------------------------------------------------------------------------
--物品改变
---------------------------------------------------------------------------------------------------
function x300565_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId)
end

---------------------------------------------------------------------------------------------------
--单击NPC事件
---------------------------------------------------------------------------------------------------
function x300565_ProcQuestAttach( sceneId, selfId, NPCId, npcGuid, misIndex, MissionId)
    if GetGameOpenById( x300565_g_IsEnableId) <= 0 and IsHaveQuestNM( sceneId, selfId, x300565_g_MissionId) == 0 then
        return
    end

    if IsHaveQuestNM( sceneId, selfId, x300565_g_MissionId) > 0 then
        local misIndex = GetQuestIndexByID( sceneId, selfId, x300565_g_MissionId)
        local index = GetQuestParam( sceneId, selfId, misIndex, x300565_MP_TARGETINDEX)
        if index ~= 0 and npcGuid == x300565_g_TargetNPCList[ index].id and GetQuestParam( sceneId, selfId, misIndex, 0) == 0 and GetQuestParam( sceneId, selfId, misIndex, 7) == 0 then
            AddQuestNumText( sceneId, x300565_g_MissionId, "我要挑战", 13, 3)
        elseif npcGuid == x300565_g_TargetNPC and GetQuestParam( sceneId, selfId, misIndex, x300565_MP_FINDMASTER) == 0 then
            AddQuestNumText( sceneId, x300565_g_MissionId, "相国寺比武", 13, 2)
        elseif npcGuid == x300565_g_TargetNPC then
            AddQuestNumText( sceneId, x300565_g_MissionId, x300565_g_MissionName, GetQuestStateNM( sceneId, selfId, NPCId, x300565_g_MissionId), 4)
        end
    end
end

function x300565_GetMissionDate( sceneId, selfId)
    return GetQuestData( sceneId, selfId, MD_WULINDAHUI_DATE[ 1], MD_WULINDAHUI_DATE[ 2], MD_WULINDAHUI_DATE[ 3] )
end

function x300565_SetMissionDate( sceneId, selfId, value)
    SetQuestData( sceneId, selfId, MD_WULINDAHUI_DATE[ 1], MD_WULINDAHUI_DATE[ 2], MD_WULINDAHUI_DATE[ 3], value)
end

---------------------------------------------------------------------------------------------------
--任务日志刷新
---------------------------------------------------------------------------------------------------
function x300565_ProcQuestLogRefresh( sceneId, selfId, MissionId)
    local misIndex = GetQuestIndexByID( sceneId, selfId, x300565_g_MissionId)
    local strTarget = ""
    local strDetail = ""
    local strGonglue = x300565_g_strMissionBook
    local findNPC = GetQuestParam( sceneId, selfId, misIndex, x300565_MP_FINDMASTER)
	BeginQuestEvent( sceneId)
    if findNPC == 2 then
        local index = GetQuestParam( sceneId, selfId, misIndex, x300565_MP_TARGETINDEX)
        if x300565_g_TargetNPCList[ index].monsterId == 0 then
            if GetQuestParam( sceneId, selfId, misIndex, 0) == 1 and GetQuestParam( sceneId, selfId, misIndex, 7) == 1 then
                strTarget = format( x300565_g_strMissionTarget2, x300565_g_TargetNPCList[ index].name, 1)
                strDetail = x300565_g_strMissionBook1
                strGonglue = x300565_g_strMissionBook1
            else
                -- 召唤之后但还没有做掉时服务器停机维护，再启动时需要恢复到前一个阶段，重新召唤或等别人召唤
                strTarget = format( x300565_g_MissionTarget, x300565_g_TargetNPCList[ index].id)
                SetQuestByIndex( sceneId, selfId, misIndex, x300565_MP_FINDMASTER, 1)
            end
        else
            -- 战胜武林高手
            strTarget = format( x300565_g_strMissionTarget2, x300565_g_TargetNPCList[ index].name, 0)
            strDetail = format( x300565_g_strMissionInfo3, x300565_g_TargetNPCList[ index].name)
            strGonglue = format( x300565_g_strMissionInfo2, x300565_g_TargetNPCList[ index].id)
        end
    elseif findNPC == 1 then
        -- 找到武林高手
        local index = GetQuestParam( sceneId, selfId, misIndex, x300565_MP_TARGETINDEX)
        strTarget = format( x300565_g_MissionTarget, x300565_g_TargetNPCList[ index].id)
        strDetail = format( x300565_g_MissionInfo1, x300565_g_TargetNPCList[ index].id)
        strGonglue = format( x300565_g_strMissionInfo2, x300565_g_TargetNPCList[ index].id)
    elseif findNPC == 0 then
        -- 找到智障禅师
        strTarget = format( x300565_g_MissionTarget, x300565_g_TargetNPC)
        strDetail = format( x300565_g_MissionInfo, x300565_g_TargetNPC)
    end
    AddQuestLogCustomText( sceneId,
                           x300565_g_MissionName,               -- 标题
                           x300565_g_MissionName,               -- 任务名字
                           strTarget,                           -- 任务跟踪显示的任务目标
                           x300565_g_MissionReply,              -- 任务NPC
                           strGonglue,            -- 任务攻略
                           strDetail,               -- 任务描述
                           x300565_g_MissionHelp)               -- 任务提示
    -- 显示奖励
	local level = GetLevel(sceneId, selfId)
    for i, item in x300565_g_RewardTable do
        if level >= item.minLevel and level < item.maxLevel then
            for j, iter in item.items do
                AddQuestRadioItemBonus( sceneId, iter.id, iter.cnt)
            end
            break
        end
    end
	EndQuestEvent()
	DispatchQuestLogUpdate( sceneId, selfId, MissionId)
end
