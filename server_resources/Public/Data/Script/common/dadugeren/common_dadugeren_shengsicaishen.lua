--MisDescBegin

x300566_g_ScriptId 					= 300566                  --脚本ID
x300566_g_MissionId 				= 9310                    --任务ID

x300566_g_MissionKind 				= 2                       --任务类型
x300566_g_LevelLess					= 40                      --场景开放等级  <=0 表示不限制

x300566_g_MissionName				= "【个人】生死财神"                                        --任务名称(512)
x300566_g_MissionTarget				= "  找到@npc_140006"      --任务目标
x300566_g_MissionInfo				= "\t近日，帮主沈万三得了一种怪病，整日昏迷不醒。各路名医请了无数，无人能说清这究竟是何种病症。\n\t今日，代帮主@npc_140006，出重金请了神医胡青牛前往盐帮诊治，也不知现在情况如何，真是让人心急啊。"            --任务信息
x300566_g_ContinueInfo				= "\t难道你也对找来这几味药引束手无策？这可如何是好。"  --任务继续信息
x300566_g_MissionCompleted			= "\t这么快你就找齐了所有的药引？我大哥有救了！\n\t#Y@myname#W，这次多亏你的相助，这是我盐帮的一点小小心意，还望不要推辞。"  --任务完成信息
x300566_g_MissionHelp				= "#W@npc_140006就在大都东南方的盐帮总舵内。本任务所需要的物品，您可以通过#G生活技能#W制作得来，也可以向其他玩家购买。"          --任务提示信息
-- 任务放弃提示信息
x300566_g_strMissionAbandon         = "您放弃了任务：【个人】生死财神"

--目标
x300566_g_ExtTarget					= { {type=20,n=1,target=""} }


--奖励
x300566_g_ExpBonus					= 0             --奖励：经验 （数值填0，字符串为空，表示没有该项奖励）
x300566_g_BonusItem					= {}	--奖励：物品

x300566_g_BonusMoney1               = 0  --任务奖励绑定银币
x300566_g_BonusMoney2               = 0  --任务奖励非绑定银币
x300566_g_BonusMoney3               = 0  --任务奖励绑定金币
x300566_g_BonusMoney4               = 0  --任务奖励朝廷声望
x300566_g_BonusMoney5               = 0  --任务奖励江湖声望
x300566_g_BonusMoney6               = 0  --任务奖励荣誉

x300566_g_BonusChoiceItem           = {}
x300566_g_GroupPoint	=	{ {type=10,id =188,target = "木槿"},{type=10,id =189,target = "水荷"},{type=10,id =190,target = "白术"},{type=10,id =191,target = "桑枝"},{type=10,id =192,target = "玄石"}}--专门用于采集点特效用，与任务相关未必就是完成任务的必要因素，因此，只要相关就可以设置这个属性



--MisDescEnd

--任务目标顺序
x300566_MP_GETSUBMISSION            = 1 -- 接收子任务标记
x300566_MP_ITEM1                    = 2
x300566_MP_ITEM2                    = 3
x300566_MP_ITEM3                    = 4
x300566_MP_ITEM4                    = 5
x300566_MP_ITEMINDEX                = 6
x300566_MP_ISCOMPLETE				= 7	-- 代表完成 0未完成， 1完成

x300566_g_strMissionFull            = "任务已满，任务接受失败"
x300566_g_strMissionAccept          = "您接受了任务：【个人】生死财神"
x300566_g_strMissionBook            = "\t听说那神医胡青牛给人医治，从不多话，诊断完开出一副古怪的药方，即飘然离去。\n\t更为神奇的是，只要给病人按药方配药服下，无不药到病除。"
x300566_g_strSubMissionInfo         = "\t方才那神医胡青牛已经给帮主诊断过，不过他并未说帮主得的是何种病症，只是开了张药方就离去。\n\t这药方中共有八种珍奇的物事，饶是我盐帮富甲天下，仍有四种不知能从何处得来。"
x300566_g_strMissionFinished        = "你完成了任务：【个人】生死财神"
x300566_g_strMissionRefrain         = "你今天已经做过这个任务，请明天再来吧。"
x300566_g_strMissionTarget2         = "\t收集@item_%d#W(%d/1)"
-- 接受任务记录日志ID
x300566_g_AcceptMissionLogID        = 941
-- 完成任务记录日志ID
x300566_g_FinishMissionLogID        = 942
-- 沈万四guid
x300566_g_TargetNPC                 = 140006
-- 接任务NPC
x300566_g_MissionNPC                = 139083
-- 任务回复NPC
x300566_g_MissionReply              = "@npc_140006"
-- 收集物品列表
x300566_g_ItemTable                 = {
                                        { mp = x300566_MP_ITEM1, 
                                            itemlist = { 12020001,12020002,12020003,12020004,12020005,12020006 }, -- 物品id列表
                                        },       -- 商店购买的物品
                                        { mp = x300566_MP_ITEM2, 
                                            itemlist = { 14030001,14030006,14030011,12052471,12052481,12052491}, -- 物品id列表
                                        },       -- 采集的物品
                                        { mp = x300566_MP_ITEM3, 
                                            itemlist = { 12052531,11041030,11041040,11041010,11041000,11041050 }, -- 物品id列表
                                        },       -- 定点使用得到的物品
                                        { mp = x300566_MP_ITEM4, 
                                            itemlist =  { 10260040,10250040,10230040,10200040,10280040,10290040 },  -- 物品id列表
                                        },       -- 杀怪得到的物品
}
-- 定点使用坐标
x300566_g_UsePositionX              = 100
x300566_g_UsePositionZ              = 100
-- 经验奖励系数
x300566_g_CoffExp                   = 0
-- 银卡奖励系数
x300566_g_CoffMoney                 = 500
-- 任务物品1目标
x300566_g_strMissionItem1Target     = "  收集@item_%d#W(%d/1)\n"
-- 任务物品2目标
x300566_g_strMissionItem2Target     = "  收集@item_%d#W(%d/1)\n"
-- 任务物品3目标
x300566_g_strMissionItem3Target     = "  收集@item_%d#W(%d/1)\n"
-- 任务物品4目标
x300566_g_strMissionItem4Target     = "  收集@item_%d#W(%d/1)"
-- 获得物品时的提示
x300566_g_strGetItem                = "你获得了@item_%d#cffcf00"
-- 任务攻略2
x300566_g_strGongLue2               = "找到四种药引"
-- 任务描述2
x300566_g_strMissionDescription2    = "救人如救火，看来你要赶紧去帮@npc_140006找到这四种罕见的药引了。"
-- 任务攻略3
x300566_g_strGongLue3               = "将药交给@npc_140006。"
-- 任务描述3
x300566_g_strMissionDescription3    = "终于配齐了药引，还是快去交给@npc_140006吧。"
-- 玩法开关id
x300566_g_IsEnableId                = 1005
-- 任务奖励物品列表
x300566_g_RewardTable       = {
                                { minLevel = 40, maxLevel = 60,  items = { { id = 11000201, cnt = 8 }, { id = 11050002, cnt = 8 }, { id = 12030120, cnt = 1 }, { id = 12030130, cnt = 1 }, { id = 12030140, cnt = 1 } } }, 
                                { minLevel = 60, maxLevel = 80,  items = { { id = 11000202, cnt = 8 }, { id = 11050003, cnt = 8 }, { id = 12030120, cnt = 1 }, { id = 12030130, cnt = 1 }, { id = 12030140, cnt = 1 } } }, 
                                { minLevel = 80, maxLevel = 999, items = { { id = 11000203, cnt = 8 }, { id = 11050004, cnt = 8 }, { id = 12030120, cnt = 1 }, { id = 12030130, cnt = 1 }, { id = 12030140, cnt = 1 } } }, 
}

---------------------------------------------------------------------------------------------------
--列举事件
---------------------------------------------------------------------------------------------------
function x300566_ProcEnumEvent( sceneId, selfId, NPCId, MissionId)

    if GetLevel( sceneId, selfId) < x300566_g_LevelLess then
        return 0
    end
    if IsHaveQuestNM( sceneId, selfId, x300566_g_MissionId) > 0 then
        return 0
    end

    AddQuestNumText( sceneId, x300566_g_MissionId, x300566_g_MissionName, GetQuestStateNM( sceneId, selfId, NPCId, x300566_g_MissionId), 1)
end

---------------------------------------------------------------------------------------------------
--任务入口函数
---------------------------------------------------------------------------------------------------
function x300566_ProcEventEntry( sceneId, selfId, NPCId, MissionId, nExtIdx)

    if GetGameOpenById( x300566_g_IsEnableId) <= 0 and IsHaveQuestNM( sceneId, selfId, x300566_g_MissionId) == 0 then
        x300566_ShowTips(sceneId, selfId, "此活动今天不开放，详情请到大都包打处听查询每日新鲜事")
        return
    end

	if IsHaveQuestNM( sceneId, selfId, x300566_g_MissionId) > 0 then  -- 如果已经接过这个任务
        local npcGuid = GetMonsterGUID( sceneId, NPCId)
        if npcGuid == x300566_g_MissionNPC then
            local bDone = x300566_CheckSubmit( sceneId, selfId, NPCId)
            if bDone > 0 then
                x300566_DispatchCompletedInfo( sceneId, selfId, NPCId) --完成任务显示
            else
                x300566_DispatchContinueInfo( sceneId, selfId, NPCId) --未完成任务显示
            end
        elseif npcGuid == x300566_g_TargetNPC then
            local misIndex = GetQuestIndexByID( sceneId, selfId, x300566_g_MissionId)
            if GetQuestParam( sceneId, selfId, misIndex, 0) == 0 and GetQuestParam( sceneId, selfId, misIndex, 7) == 0 then
                if GetQuestParam( sceneId, selfId, misIndex, x300566_MP_GETSUBMISSION) == 1 then
                    x300566_DispatchContinueInfo( sceneId, selfId, NPCId) --未完成任务显示
                else
                    BeginQuestEvent( sceneId)
                        AddQuestText( sceneId, "#Y"..x300566_g_MissionName)
                        AddQuestText( sceneId, x300566_g_strSubMissionInfo)
                    EndQuestEvent( sceneId)
                    DispatchQuestEventList( sceneId, selfId, NPCId)

                    -- 随机选取任务物品
                    local index = random( 1, getn( x300566_g_ItemTable[ 1].itemlist) )
                    SetQuestByIndex( sceneId, selfId, misIndex, x300566_MP_ITEMINDEX, index)
                    SetQuestByIndex( sceneId, selfId, misIndex, x300566_MP_GETSUBMISSION, 1)
                    -- 检查背包里是否已经有要收集的物品，如果有就直接设置相关标记
                    for i, item in x300566_g_ItemTable do
                        if HaveItemInBag( sceneId, selfId, item.itemlist[ index] ) > 0 then
                            SetQuestByIndex( sceneId, selfId, misIndex, item.mp, 1)
                        end
                    end
                    x300566_ProcQuestLogRefresh( sceneId, selfId, MissionId)
                end
            else
                x300566_DispatchCompletedInfo( sceneId, selfId, NPCId) --完成任务显示
            end
        end
	else
		x300566_DispatchMissionInfo( sceneId, selfId, NPCId)	--任务信息显示
	end
	 
end

---------------------------------------------------------------------------------------------------
--检测接受条件
---------------------------------------------------------------------------------------------------
function x300566_ProcAcceptCheck( sceneId, selfId, npcId)
	local bHaveMission	= IsHaveQuestNM( sceneId, selfId, x300566_g_MissionId)
	if( bHaveMission > 0) then
		return 0;
	else
		return 1;
	end
end

---------------------------------------------------------------------------------------------------
--接受条件
---------------------------------------------------------------------------------------------------
function x300566_ProcQuestAccept( sceneId, selfId, targetId, missionId)
    if GetGameOpenById( x300566_g_IsEnableId) <= 0 and IsHaveQuestNM( sceneId, selfId, x300566_g_MissionId) == 0 then
        return 0
    end

    local name = GetName( sceneId, selfId)
    if IsHaveQuestNM( sceneId, selfId, x300566_g_MissionId) > 0 then
    else
        local today = GetDayOfYear()
        if x300566_GetMissionDate( sceneId, selfId) == today then
            Msg2Player( sceneId, selfId, x300566_g_strMissionRefrain, 8, 3)
            return 0
        end
        if GetQuestData( sceneId, selfId, MD_RICHANG_DAY[ 1], MD_RICHANG_DAY[ 2], MD_RICHANG_DAY[ 3] ) == today then
            if GetQuestData( sceneId, selfId, MD_RICHANG_COUNT[ 1], MD_RICHANG_COUNT[ 2], MD_RICHANG_COUNT[ 3] ) >= 3 then
                Msg2Player( sceneId, selfId, "你不能再领取今天的日常任务了", 8, 3)
                return 0
            end
        else
            SetQuestData( sceneId, selfId, MD_RICHANG_COUNT[1], MD_RICHANG_COUNT[2], MD_RICHANG_COUNT[3], 0)
        end
        --检查前置任务
		local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId,x300566_g_MissionId  )
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
		
        local ret = AddQuest( sceneId, selfId, x300566_g_MissionId, x300566_g_ScriptId, 0, 0, 1, 1)
        if ret == 0 then
            LuaScenceM2Player( sceneId, selfId, x300566_g_strMissionFull, name, 3, 1)
            return 0
        else
            -- 显示任务接受信息
            LuaScenceM2Player( sceneId, selfId, x300566_g_strMissionAccept, name, 3, 1)
            LuaScenceM2Player( sceneId, selfId, x300566_g_strMissionAccept, name, 2, 1)
        end

        BeginQuestEvent( sceneId)
            AddQuestText( sceneId, "#Y"..x300566_g_MissionName)
            AddQuestText( sceneId, x300566_g_strMissionBook)
        EndQuestEvent( sceneId)
        DispatchQuestEventList( sceneId, selfId, targetId)

        local misIndex = GetQuestIndexByID( sceneId, selfId, x300566_g_MissionId)
        SetQuestByIndex( sceneId, selfId, misIndex, 7, 0)
        SetQuestByIndex( sceneId, selfId, misIndex, 0, 0)

        -- 写日志
        GamePlayScriptLog( sceneId, selfId, x300566_g_AcceptMissionLogID)
    end
end

---------------------------------------------------------------------------------------------------
function x300566_ShowTips(sceneId, selfId, str)
	BeginQuestEvent(sceneId);
		AddQuestText(sceneId,str);
	EndQuestEvent();
	DispatchQuestTips(sceneId, selfId);
end
--放弃任务
---------------------------------------------------------------------------------------------------
function x300566_ProcQuestAbandon( sceneId, selfId, MissionId)
	local bHaveMission	= IsHaveQuestNM( sceneId, selfId, x300566_g_MissionId)
	if bHaveMission > 0 then
        -- local misIndex = GetQuestIndexByID( sceneId, selfId, x300566_g_MissionId)
        -- local index = GetQuestParam( sceneId, selfId, misIndex, x300566_MP_ITEMINDEX)
        -- if index ~= 0 then
            -- -- 删除完成任务需要的物品，除了从商店购买的非绑定物品
            -- DelItem( sceneId, selfId, x300566_g_ItemTable[ 2].itemlist[ index], 1)
            -- DelItem( sceneId, selfId, x300566_g_ItemTable[ 3].itemlist[ index], 1)
            -- DelItem( sceneId, selfId, x300566_g_ItemTable[ 4].itemlist[ index], 1)
        -- end
		DelQuest( sceneId, selfId, x300566_g_MissionId)
        --x300566_SetMissionDate( sceneId, selfId, GetDayOfYear() )
        local today = GetDayOfYear()
        SetQuestData( sceneId, selfId, MD_SHENGSICAISHEN_DATE[ 1], MD_SHENGSICAISHEN_DATE[ 2], MD_SHENGSICAISHEN_DATE[ 3], today)
		if today == GetQuestData( sceneId, selfId, MD_RICHANG_DAY[1], MD_RICHANG_DAY[2], MD_RICHANG_DAY[3] ) then
            local count = GetQuestData( sceneId, selfId, MD_RICHANG_COUNT[1], MD_RICHANG_COUNT[2], MD_RICHANG_COUNT[3] )
            if count < 3 then
                SetQuestData( sceneId, selfId, MD_RICHANG_COUNT[1], MD_RICHANG_COUNT[2], MD_RICHANG_COUNT[3], 1 + count)
            end
        else
            SetQuestData( sceneId, selfId, MD_RICHANG_DAY[1], MD_RICHANG_DAY[2], MD_RICHANG_DAY[3], today)
            SetQuestData( sceneId, selfId, MD_RICHANG_COUNT[1], MD_RICHANG_COUNT[2], MD_RICHANG_COUNT[3], 1)
        end

		Msg2Player( sceneId, selfId, x300566_g_strMissionAbandon, 8, 3)
		Msg2Player( sceneId, selfId, x300566_g_strMissionAbandon, 8, 2)
	end
end

---------------------------------------------------------------------------------------------------
--检查任务是否可提交
---------------------------------------------------------------------------------------------------
function x300566_CheckSubmit( sceneId, selfId, NPCId)
	local misIndex = GetQuestIndexByID( sceneId, selfId, x300566_g_MissionId)

    if GetQuestParam( sceneId, selfId, misIndex, 0) == 1 and GetQuestParam( sceneId, selfId, misIndex, 7) == 1 then
        return 1
    else
        return 0
    end
end

---------------------------------------------------------------------------------------------------
--获得奖励
---------------------------------------------------------------------------------------------------
function x300566_GetBonus( sceneId, selfId,NpcID, SelectId)
	--奖励金钱1
	if x300566_g_BonusMoney1 > 0 then
	    AddMoney( sceneId, selfId, 1, x300566_g_BonusMoney1 )
	    Msg2Player(sceneId,selfId,format("获得银卡#{_MONEY%d}的奖励。", x300566_g_BonusMoney1),4,2)
	end

	--奖励金钱2
	if x300566_g_BonusMoney2 > 0 then
	    AddMoney( sceneId, selfId, 0, x300566_g_BonusMoney2 )
	    Msg2Player(sceneId,selfId,format("获得银币#{_MONEY%d}的奖励。", x300566_g_BonusMoney2),4,2)
	end

	--奖励金钱1
	if x300566_g_BonusMoney3 > 0 then
	    AddMoney( sceneId, selfId, 3, x300566_g_BonusMoney3 )
	    Msg2Player(sceneId,selfId,format("获得金卡#{_MONEY%d}的奖励。", x300566_g_BonusMoney3),4,2)
	end

	--江湖声望
	if x300566_g_BonusMoney4 > 0 then
		local nRongYu = GetRongYu( sceneId, selfId )
		nRongYu = nRongYu + x300566_g_BonusMoney4
		SetRongYu( sceneId, selfId, nRongYu )
		Msg2Player(sceneId,selfId,format("获得江湖声望%d的奖励。", x300566_g_BonusMoney4),4,2)
	end

	--朝廷声望
	if x300566_g_BonusMoney5 > 0 then
		local nShengWang = GetShengWang( sceneId, selfId )
		nShengWang = nShengWang + x300566_g_BonusMoney5
		SetShengWang( sceneId, selfId, nShengWang )
		Msg2Player(sceneId,selfId,format("获得朝廷声望%d的奖励。", x300566_g_BonusMoney5),4,2)
	end

	--朝廷声望
	if x300566_g_BonusMoney6 > 0 then
		AddHonor(sceneId,selfId,x300566_g_BonusMoney6)
		Msg2Player(sceneId,selfId,format("获得荣誉值%d的奖励。", x300566_g_BonusMoney6),4,2)
	end

 	--奖励固定物品
	for i, item in x300566_g_BonusItem do
 		BeginAddItem(sceneId)
		AddItem( sceneId, item.item, item.n )
		local ret = EndAddItem(sceneId,selfId)
		if ret > 0 then
			AddItemListToPlayer(sceneId,selfId)
		else
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"背包已满，请整理背包后再来")
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
		end
    end

	--奖励可选物品
	for i, item in x300566_g_BonusChoiceItem do
	    if item.item == SelectId then
	        BeginAddItem(sceneId)
			AddItem( sceneId, item.item, item.n )
			local ret = EndAddItem(sceneId,selfId)
			if ret > 0 then
				AddItemListToPlayer(sceneId,selfId)
			else
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"背包已满，请整理背包后再来")
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
function x300566_ProcQuestSubmit( sceneId, selfId, NPCId, selectRadioId, MissionId)
    if GetGameOpenById( x300566_g_IsEnableId) <= 0 then
        return
    end
    
    if IsHaveQuestNM( sceneId, selfId, x300566_g_MissionId) < 0 then
    	return
    end
 
    
    -- check first
    local misIndex = GetQuestIndexByID( sceneId, selfId, x300566_g_MissionId)
    local name = GetName( sceneId, selfId)
    local index = GetQuestParam( sceneId, selfId, misIndex, x300566_MP_ITEMINDEX)
    for i, item in x300566_g_ItemTable do
        if GetItemCountInBag( sceneId, selfId, item.itemlist[ index] ) < 1 then
            LuaScenceM2Player( sceneId, selfId, format( "没有@item_%d#cffcf00不能交任务", item.itemlist[ index] ), name, 3, 1)
            return
        end
    end

    if CallScriptFunction( 270300, "OnSubmissionFinished", sceneId, selfId, x300566_g_MissionId) == 0 then
        Msg2Player( sceneId, selfId, "今天的日常任务已经不能再交了，请明天再来", 8, 3)
        return 0
    end

    -- remove from bag of player
    for i, item in x300566_g_ItemTable do
        DelItem( sceneId, selfId, item.itemlist[ index], 1)
    end
    DelQuest( sceneId, selfId, x300566_g_MissionId)
    CallScriptFunction( 256225, "Finishcaishen", sceneId, selfId)	
    LuaScenceM2Player( sceneId, selfId, x300566_g_strMissionFinished, name, 3, 1)
    LuaScenceM2Player( sceneId, selfId, x300566_g_strMissionFinished.."。", name, 2, 1)
    x300566_SetMissionDate( sceneId, selfId, GetDayOfYear() )
    -- 检查玩家选择的奖励是不是可判定非绑定的
	local level = GetLevel( sceneId, selfId)
    local canBind = 0
    local count = 0
    local id = 0
    for i, item in x300566_g_RewardTable do
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
        for i, item in x300566_g_RewardTable do
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
		
		
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,format("您获得了物品：@itemid_%d",id))
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
	else
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"背包空间不足，无法获得任务奖励物品，交任务失败")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
	end
    GamePlayScriptLog( sceneId, selfId, x300566_g_FinishMissionLogID)
end

---------------------------------------------------------------------------------------------------
--向客户端发送任务信息
---------------------------------------------------------------------------------------------------
function x300566_DispatchMissionInfo( sceneId, selfId, NPCId)
	BeginQuestEvent( sceneId)

    --任务信息
    AddQuestText( sceneId, "#Y"..x300566_g_MissionName)
    AddQuestText( sceneId, x300566_g_MissionInfo)
    AddQuestText( sceneId, " ")
           
    --任务目标
    AddQuestText( sceneId, "#Y任务目标：")
    AddQuestText( sceneId, x300566_g_MissionTarget)
    AddQuestText( sceneId, " ")

    --提示信息
    if x300566_g_MissionHelp ~= "" then
        AddQuestText( sceneId, "#Y任务提示：")
        AddQuestText( sceneId, x300566_g_MissionHelp)
        AddQuestText( sceneId, " ")
    end                 

    --任务奖励信息
    local level = GetLevel( sceneId, selfId)
    for i, item in x300566_g_RewardTable do
        if level >= item.minLevel and level < item.maxLevel then
            for j, iter in item.items do
                AddQuestRadioItemBonus( sceneId, iter.id, iter.cnt)
            end
            break
        end
    end


	EndQuestEvent()
	DispatchQuestInfoNM( sceneId, selfId, NPCId, x300566_g_ScriptId, x300566_g_MissionId)
end

---------------------------------------------------------------------------------------------------
--向客户端发送任务未完成
---------------------------------------------------------------------------------------------------
function x300566_DispatchContinueInfo( sceneId, selfId, NPCId)
	BeginQuestEvent( sceneId)
    AddQuestText( sceneId, "#Y"..x300566_g_MissionName)
    AddQuestText( sceneId, x300566_g_ContinueInfo)
    AddQuestText( sceneId, " ")
    -- local exp = GetLevel( sceneId, selfId) * x300340_g_ExperienceCoefficient
    -- if exp > 0 then
        -- AddQuestExpBonus( sceneId, exp)
    -- end
    -- -- 090302 银卡奖励
    -- local playerLevel = GetLevel( sceneId, selfId)
    -- if playerLevel > 80 then
        -- playerLevel = 80
    -- end
    -- local money = playerLevel * x300340_g_MoneyCoefficient
    -- AddQuestMoneyBonus1( sceneId, money)
	EndQuestEvent( sceneId)
    DispatchQuestEventList( sceneId, selfId, NPCId)
	--DispatchQuestInfoNM( sceneId, selfId, NPCId, x300566_g_ScriptId, x300566_g_MissionId)
end

---------------------------------------------------------------------------------------------------
--向客户端发送任务完成信息
---------------------------------------------------------------------------------------------------
function x300566_DispatchCompletedInfo( sceneId, selfId, NPCId)
	BeginQuestEvent( sceneId)
    AddQuestText( sceneId, "#Y"..x300566_g_MissionName)
    AddQuestText( sceneId, x300566_g_MissionCompleted)
    AddQuestText( sceneId, " ")
    local level = GetLevel( sceneId, selfId)
    for i, item in x300566_g_RewardTable do
        if level >= item.minLevel and level < item.maxLevel then
            for j, iter in item.items do
                AddQuestRadioItemBonus( sceneId, iter.id, iter.cnt)
            end
            break
        end
    end
	EndQuestEvent( sceneId)
    DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x300566_g_ScriptId, x300566_g_MissionId)
end

---------------------------------------------------------------------------------------------------
--怪物被杀的消息处理
---------------------------------------------------------------------------------------------------
function x300566_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId)
end

---------------------------------------------------------------------------------------------------
--物品改变
---------------------------------------------------------------------------------------------------
function x300566_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId)
    if GetGameOpenById( x300566_g_IsEnableId) <= 0 and IsHaveQuestNM( sceneId, selfId, x300566_g_MissionId) == 0 then
        return 0
    end

    local misIndex = GetQuestIndexByID( sceneId, selfId, x300566_g_MissionId)
    local index = GetQuestParam( sceneId, selfId, misIndex, x300566_MP_ITEMINDEX)
    if itemdataId == x300566_g_ItemTable[ 1].itemlist[ index] then
        if HaveItemInBag( sceneId, selfId, itemdataId) > 0 then
            SetQuestByIndex( sceneId, selfId, misIndex, x300566_MP_ITEM1, 1)
            Msg2Player( sceneId, selfId, format( x300566_g_strGetItem, itemdataId), 8, 3)
        else
            SetQuestByIndex( sceneId, selfId, misIndex, x300566_MP_ITEM1, 0)
        end
        x300566_ProcQuestLogRefresh( sceneId, selfId, x300566_g_MissionId)
    elseif itemdataId == x300566_g_ItemTable[ 2].itemlist[ index] then
        if HaveItemInBag( sceneId, selfId, itemdataId) > 0 then
            SetQuestByIndex( sceneId, selfId, misIndex, x300566_MP_ITEM2, 1)
            Msg2Player( sceneId, selfId, format( x300566_g_strGetItem, itemdataId), 8, 3)
        else
            SetQuestByIndex( sceneId, selfId, misIndex, x300566_MP_ITEM2, 0)
        end
        x300566_ProcQuestLogRefresh( sceneId, selfId, x300566_g_MissionId)
    elseif itemdataId == x300566_g_ItemTable[ 3].itemlist[ index] then
        if HaveItemInBag( sceneId, selfId, itemdataId) > 0 then
            SetQuestByIndex( sceneId, selfId, misIndex, x300566_MP_ITEM3, 1)
            Msg2Player( sceneId, selfId, format( x300566_g_strGetItem, itemdataId), 8, 3)
        else
            SetQuestByIndex( sceneId, selfId, misIndex, x300566_MP_ITEM3, 0)
        end
        x300566_ProcQuestLogRefresh( sceneId, selfId, x300566_g_MissionId)
    elseif itemdataId == x300566_g_ItemTable[ 4].itemlist[ index] then
        if HaveItemInBag( sceneId, selfId, itemdataId) > 0 then
            SetQuestByIndex( sceneId, selfId, misIndex, x300566_MP_ITEM4, 1)
            Msg2Player( sceneId, selfId, format( x300566_g_strGetItem, itemdataId), 8, 3)
        else
            SetQuestByIndex( sceneId, selfId, misIndex, x300566_MP_ITEM4, 0)
        end
        x300566_ProcQuestLogRefresh( sceneId, selfId, x300566_g_MissionId)
    else
        return
    end

    if GetQuestParam( sceneId, selfId, misIndex, x300566_MP_ITEM1) == 1 and
        GetQuestParam( sceneId, selfId, misIndex, x300566_MP_ITEM2) == 1 and
        GetQuestParam( sceneId, selfId, misIndex, x300566_MP_ITEM3) == 1 and
        GetQuestParam( sceneId, selfId, misIndex, x300566_MP_ITEM4) == 1 then
        SetQuestByIndex( sceneId, selfId, misIndex, 0, 1)
        SetQuestByIndex( sceneId, selfId, misIndex, 7, 1)
        Msg2Player( sceneId, selfId, "药引已经配齐，快去交给沈万四吧。", 8, 3)
    else
        SetQuestByIndex( sceneId, selfId, misIndex, 0, 0)
        SetQuestByIndex( sceneId, selfId, misIndex, 7, 0)
    end
end

---------------------------------------------------------------------------------------------------
--单击NPC事件
---------------------------------------------------------------------------------------------------
function x300566_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId)
    if GetGameOpenById( x300566_g_IsEnableId) <= 0 and IsHaveQuestNM( sceneId, selfId, x300566_g_MissionId) == 0 then
        return 0
    end

    if IsHaveQuestNM( sceneId, selfId, x300566_g_MissionId) > 0 then
        local misIndex = GetQuestIndexByID( sceneId, selfId, x300566_g_MissionId)
        if npcGuid == x300566_g_TargetNPC then
            if GetQuestParam( sceneId, selfId, misIndex, 0) == 0 and GetQuestParam( sceneId, selfId, misIndex, 7) == 0 and GetQuestParam( sceneId, selfId, misIndex, x300566_MP_GETSUBMISSION) == 0 then
                AddQuestNumText( sceneId, x300566_g_MissionId, "帮主的病怎么样了？", 13)
            else
                AddQuestNumText( sceneId, x300566_g_MissionId, x300566_g_MissionName, 7)
            end
        end
    end
end

function x300566_GetMissionDate( sceneId, selfId)
    return GetQuestData( sceneId, selfId, MD_SHENGSICAISHEN_DATE[ 1], MD_SHENGSICAISHEN_DATE[ 2], MD_SHENGSICAISHEN_DATE[ 3] )
end

function x300566_SetMissionDate( sceneId, selfId, value)
    SetQuestData( sceneId, selfId, MD_SHENGSICAISHEN_DATE[ 1], MD_SHENGSICAISHEN_DATE[ 2], MD_SHENGSICAISHEN_DATE[ 3], value)
end

function x300566_OnUseItem( sceneId, selfId)
end

function x300566_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID)
    if GetGameOpenById( x300566_g_IsEnableId) <= 0 and IsHaveQuestNM( sceneId, selfId, x300566_g_MissionId) == 0 then
        return 0
    end

    local misIndex = GetQuestIndexByID( sceneId, selfId, x300566_g_MissionId)
    if IsHaveQuestNM( sceneId, selfId, x300566_g_MissionId) > 0 then
        if GetQuestParam( sceneId, selfId, misIndex, x300566_MP_ITEM2) == 1 then
            Msg2Player( sceneId, selfId, "你已经采集到药引了", 8, 3)
            return 1
        else
            return 0
        end
    else
        return 1
    end
end

function x300566_OnRecycle( sceneId, selfId, targetId, gpType, needItemID)
end

---------------------------------------------------------------------------------------------------
--任务日志刷新
---------------------------------------------------------------------------------------------------
function x300566_ProcQuestLogRefresh( sceneId, selfId, MissionId)
    local misIndex = GetQuestIndexByID( sceneId, selfId, x300566_g_MissionId)
    local index = GetQuestParam( sceneId, selfId, misIndex, x300566_MP_ITEMINDEX)
    if GetQuestParam( sceneId, selfId, misIndex, x300566_MP_ITEM1) == 1 and
        GetQuestParam( sceneId, selfId, misIndex, x300566_MP_ITEM2) == 1 and
        GetQuestParam( sceneId, selfId, misIndex, x300566_MP_ITEM3) == 1 and
        GetQuestParam( sceneId, selfId, misIndex, x300566_MP_ITEM4) == 1 then
        SetQuestByIndex( sceneId, selfId, misIndex, 0, 1)
        SetQuestByIndex( sceneId, selfId, misIndex, 7, 1)
    else
        SetQuestByIndex( sceneId, selfId, misIndex, 0, 0)
        SetQuestByIndex( sceneId, selfId, misIndex, 7, 0)
    end
	BeginQuestEvent( sceneId)
    if GetQuestParam( sceneId, selfId, misIndex, x300566_MP_GETSUBMISSION) == 1 then
        local strMissionTarget = ""
        local item1 = GetQuestParam( sceneId, selfId, misIndex, x300566_MP_ITEM1)
        local item2 = GetQuestParam( sceneId, selfId, misIndex, x300566_MP_ITEM2)
        local item3 = GetQuestParam( sceneId, selfId, misIndex, x300566_MP_ITEM3)
        local item4 = GetQuestParam( sceneId, selfId, misIndex, x300566_MP_ITEM4)

        -- "购买@npc_%d#W(%d/1)\n"
        if item1 == 1 then
            strMissionTarget = "#G"..format( x300566_g_strMissionItem1Target, x300566_g_ItemTable[ 1].itemlist[ index], item1)
        else
            strMissionTarget = "#W"..format( x300566_g_strMissionItem1Target, x300566_g_ItemTable[ 1].itemlist[ index], item1)
        end

        -- "采集@npc_%d#W(%d/1)\n"
        if item2 == 1 then
            strMissionTarget = strMissionTarget.."#G"..format( x300566_g_strMissionItem2Target, x300566_g_ItemTable[ 2].itemlist[ index], item2)
        else
            strMissionTarget = strMissionTarget.."#W"..format( x300566_g_strMissionItem2Target, x300566_g_ItemTable[ 2].itemlist[ index], item2)
        end

        -- "到@npc_%d使用@item_%d#W(%d/1)\n"
        if item3 == 1 then
            strMissionTarget = strMissionTarget.."#G"..format( x300566_g_strMissionItem3Target, x300566_g_ItemTable[ 3].itemlist[ index], item3)
        else
            strMissionTarget = strMissionTarget.."#W"..format( x300566_g_strMissionItem3Target, x300566_g_ItemTable[ 3].itemlist[ index], item3)
        end

        -- "杀死@npc_%d获得@item_%d#W(%d/1)"
        if item4 == 1 then
            strMissionTarget = strMissionTarget.."#G"..format( x300566_g_strMissionItem4Target, x300566_g_ItemTable[ 4].itemlist[ index], item4)
        else
            strMissionTarget = strMissionTarget.."#W"..format( x300566_g_strMissionItem4Target, x300566_g_ItemTable[ 4].itemlist[ index], item4)
        end

        if GetQuestParam( sceneId, selfId, misIndex, 0) == 1 and GetQuestParam( sceneId, selfId, misIndex, 7) == 1 then
            AddQuestLogCustomText( sceneId,
                                   x300566_g_MissionName,               -- 标题
                                   x300566_g_MissionName,               -- 任务名字
                                   strMissionTarget,                    -- 任务目标
                                   x300566_g_MissionReply,              -- 任务NPC
                                   x300566_g_strGongLue3,               -- 任务攻略
                                   x300566_g_strMissionDescription3,    -- 任务描述
                                   x300566_g_MissionHelp)               -- 任务提示
        else
            AddQuestLogCustomText( sceneId,
                                   x300566_g_MissionName,               -- 标题
                                   x300566_g_MissionName,               -- 任务名字
                                   strMissionTarget,                    -- 任务目标
                                   x300566_g_MissionReply,              -- 任务NPC
                                   x300566_g_strGongLue2,               -- 任务攻略
                                   x300566_g_strMissionDescription2,    -- 任务描述
                                   x300566_g_MissionHelp)               -- 任务提示
        end
    else
        AddQuestLogCustomText( sceneId,
                               x300566_g_MissionName,               -- 标题
                               x300566_g_MissionName,               -- 任务名字
                               x300566_g_MissionTarget,             -- 任务目标
                               x300566_g_MissionReply,              -- 任务NPC
                               x300566_g_strMissionBook,            -- 任务攻略
                               x300566_g_MissionInfo,               -- 任务描述
                               x300566_g_MissionHelp)               -- 任务提示
    end
    local level = GetLevel( sceneId, selfId)
    for i, item in x300566_g_RewardTable do
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
