--MisDescBegin

x300332_g_ScriptId 					= 	300332                  --脚本ID
x300332_g_MissionId 				= 	8091                    --任务ID

x300332_g_MissionKind 				= 	1                       --任务类型
x300332_g_LevelLess					= 	0                      --场景开放等级  <=0 表示不限制

x300332_g_MissionName				= 	"【个人】盗宝客"
x300332_g_MissionTarget				= 	"  击败@npc_%d(%d/1)"          --任务目标
x300332_g_MissionInfo				= 	""            --任务信息
x300332_g_ContinueInfo				= 	"\t怎么？你对付不了那些可恶的盗宝客么？看来我们要另外物色人选了。"  --任务继续信息
x300332_g_MissionCompleted			= 	"\t啊，没想到你这么快就击败盗宝客，真是太好了！\n\t你一定搜集了不少盗宝客的藏宝图碎片吧？喏，我再送给你一些藏宝图碎片。等你收集了#R四张不同的藏宝图碎片#W之后，我会帮你合成一张完整的藏宝图。"  --任务完成信息
x300332_g_MissionHelp				=	"\t#G据说这些盗宝客身上也带有类似的藏宝图，在清缴他们的过程中，你也很有可能会获得藏宝图的一部分。#W"          --任务提示信息

--目标
x300332_g_ExtTarget					=	{ {type=20,n=10 ,target=""} }


--奖励
x300332_g_ExpBonus					= 	0                    	--奖励：经验 （数值填0，字符串为空，表示没有该项奖励）
x300332_g_BonusItem					=	{}	--奖励：物品

x300332_g_BonusMoney1               = 	0   --任务奖励绑定银币
x300332_g_BonusMoney2               =   0   --任务奖励非绑定银币
x300332_g_BonusMoney3               =   0   --任务奖励绑定金币
x300332_g_BonusMoney4               =   0   --任务奖励朝廷声望
x300332_g_BonusMoney5               =   0   --任务奖励江湖声望
x300332_g_BonusMoney6               =   0   --任务奖励荣誉

x300332_g_BonusChoiceItem           =   {}


--MisDescEnd

--任务目标顺序
x300332_MP_TARGET1					= 1         -- 要杀怪1
x300332_MP_TARGET4					= 4         -- 
x300332_MP_FINISH                   = 7         -- 玩家接任务时的等级
x300332_MP_ISCOMPLETE				= 0	        -- 代表完成 0未完成， 1完成

-- 接受任务提示
x300332_g_strAcceptMission          = "您接受了任务：【个人】盗宝客"
-- 放弃任务提示
x300332_g_strAbandonMission         = "您放弃了任务：【个人】盗宝客"
-- 完成任务提示
x300332_g_strFinishMission          = "您完成了任务：【个人】盗宝客"
-- 放弃任务后禁止再领任务的时限(分钟)
-- x300332_g_PunishTime                = 2

-- 接受任务的玩家最小等级
x300332_g_PlayerMinLevel            = 40
-- 接受任务的玩家最大等级
x300332_g_PlayerMaxLevel            = 80

x300332_SubmitNPCGUID				= 124057	--交任务NPC GUID

-- 掉落物品表，四件宝图碎片，Id参见common.tab
x300332_ItemID_Table                ={
                                        {index = 1, itemid = 12030109},-- 神龙藏宝图碎片（龙尾）
                                        {index = 2, itemid = 12030110},-- 神龙藏宝图碎片（龙爪）
										{index = 3, itemid = 12030111},-- 神龙藏宝图碎片（龙身）
										{index = 4, itemid = 12030112},-- 神龙藏宝图碎片（龙首）
                                     }                                     


-- 任务小提示
x300332_g_MissionTips               = "\t#G据说这些盗宝客身上也带有类似的藏宝图，在清缴他们的过程中，你也很有可能会获得藏宝图的一部分。#W"
-- 任务描述
x300332_g_MissionDescription        = "\t传说当年金国灭亡时，金国六王爷完颜洪烈将带不走的金银财宝都埋藏了起来。可具体地点因为长期的战乱和金国的灭亡而无人知晓了。\n\t 但最近传闻金王宝藏埋在太行山和泰山，一些盗宝客蜂拥而至，疯狂的挖掘，企图找到金王宝藏。金国乃是我大元所灭，宝藏理所当然应归我大元所有，所以我现在委派你前去消灭这些盗宝客！\n\t 当然，我相信那些盗宝客身上会有其他宝藏的藏宝图碎片，要是你消灭了这些盗宝客，那么那些藏宝图碎片就算是给你的酬劳吧！\n\t#G注：本任务每天只能接取10次。#W"
-- 任务攻略
x300332_g_MissionBook               = "\t找到并消灭那些盗宝客，完成任务后，你将得到相应的回报。"

x300332_g_MonsterTable              = {
                                        { monsterId = 3250, posId = 173500, name = "红云盗宝客", minLevel = 40, maxLevel = 45 }, 
                                        { monsterId = 3251, posId = 173501, name = "大漠盗宝客", minLevel = 45, maxLevel = 50 }, 
                                        { monsterId = 3252, posId = 173502, name = "独行盗宝客", minLevel = 50, maxLevel = 55 }, 
                                        { monsterId = 3253, posId = 173503, name = "黑风盗宝客", minLevel = 55, maxLevel = 60 }, 
                                        { monsterId = 3254, posId = 173504, name = "波斯盗宝客", minLevel = 60, maxLevel = 65 }, 
                                        { monsterId = 3255, posId = 173505, name = "搬山盗宝客", minLevel = 65, maxLevel = 70 }, 
                                        { monsterId = 3256, posId = 173506, name = "红头盗宝客", minLevel = 70, maxLevel = 75 }, 
                                        { monsterId = 3257, posId = 173507, name = "铁履盗宝客", minLevel = 75, maxLevel = 80 }, 
                                        { monsterId = 3258, posId = 173508, name = "金刚盗宝客", minLevel = 80, maxLevel = 161}, 
}

-- 杀怪计数
x300332_g_KillTargetCount           = 1
x300332_g_MaxTimes                  = 10
x300332_g_strOverMaxTimes           = format( "每天只能接#R%d#cffcf00次这个任务", x300332_g_MaxTimes)

--**********************************
--列举事件
--**********************************
function x300332_ProcEnumEvent( sceneId, selfId, NPCId, MissionId )
	local level = GetLevel( sceneId, selfId)
	if( level < x300332_g_PlayerMinLevel) then
		 return 1
	end

    local bHaveMission	= IsHaveQuestNM( sceneId, selfId, x300332_g_MissionId)
    if( bHaveMission <= 0 and level >= x300332_g_PlayerMinLevel) then
        local state = GetQuestStateNM( sceneId, selfId, NPCId, x300332_g_MissionId)
        AddQuestNumText( sceneId, x300332_g_MissionId, x300332_g_MissionName, state)
    end
end

--**********************************
--任务入口函数
--**********************************
function x300332_ProcEventEntry(sceneId, selfId, NPCId, MissionId, nExtIdx)	--点击该任务后执行此脚本
	local bHaveMission	= IsHaveQuestNM(sceneId, selfId, x300332_g_MissionId)
	if( bHaveMission > 0) then
		local bDone = x300332_CheckSubmit(sceneId, selfId, NPCId)
		if( bDone > 0) then
			if nExtIdx ~= -1 then
				x300332_DispatchCompletedInfo( sceneId, selfId, NPCId ) --完成任务显示
			end
		else
			if nExtIdx ~= -1 then
				x300332_DispatchContinueInfo( sceneId, selfId, NPCId ) --未完成任务显示
			end
		end
	else
		x300332_DispatchMissionInfo( sceneId, selfId, NPCId )	--任务信息显示
	end
end

---------------------------------------------------------------------------------------------------
--检测接受条件
---------------------------------------------------------------------------------------------------
function x300332_ProcAcceptCheck( sceneId, selfId, npcId )
	local bHaveMission	= IsHaveQuestNM(sceneId, selfId, x300332_g_MissionId);
	if(bHaveMission > 0) then
		return 0;
	else
		return 1;
	end
end

-- 是否处于任务放弃后的惩罚时间内
-- function x300332_IsPunish( sceneId, selfId)
    -- if x300332_GetDate( sceneId, selfId) == GetDayOfYear() then
        -- if abs( GetMinOfDay() - x300332_GetAbandonTime( sceneId, selfId) ) >= x300332_g_PunishTime then
            -- return 0
        -- else
            -- return 1
        -- end
    -- else
        -- if GetMinOfDay() + 1440 - x300332_GetAbandonTime( sceneId, selfId) >= x300332_g_PunishTime then
            -- return 0
        -- else
            -- return 1
        -- end
    -- end
-- end

---------------------------------------------------------------------------------------------------
--接受条件
---------------------------------------------------------------------------------------------------
function x300332_ProcQuestAccept( sceneId, selfId, targetId, missionId )
	if IsHaveQuestNM(sceneId, selfId, x300332_g_MissionId) > 0 then
    else
        -- 检查是否处于任务放弃后的惩罚时间内
        -- if x300332_IsPunish( sceneId, selfId) > 0 then
            -- Msg2Player( sceneId, selfId, "距你上次放弃任务不足"..x300332_g_PunishTime.."分钟，不能领取任务", 8, 3)
            -- return
        -- end
        local today = GetDayOfYear()
        -- 检查当日完成次数
        if x300332_GetDate( sceneId, selfId) == today then
            if x300332_GetTimes( sceneId, selfId) >= x300332_g_MaxTimes then
                Msg2Player( sceneId, selfId, x300332_g_strOverMaxTimes, 8, 3)
                Msg2Player( sceneId, selfId, x300332_g_strOverMaxTimes, 8, 2)
                return
            end
        else
            -- 清除当日完成次数
            x300332_SetTimes( sceneId, selfId, 0)
            x300332_SetDate( sceneId, selfId, today)
        end

    	local ret	= AddQuest( sceneId, selfId, x300332_g_MissionId, x300332_g_ScriptId, 1, 0, 0, 1)
    	if( ret == 0) then
    		BeginQuestEvent( sceneId)
    		AddQuestText( sceneId, "任务已满，任务接受失败！" )
    		EndQuestEvent( sceneId)
    		DispatchQuestTips( sceneId, selfId)
    		return 0;
    	end

        -- 根据玩家等级设置任务目标怪
    	local level = GetLevel( sceneId, selfId)
        local monsterId = 0
        local name = "盗宝客"
        for i, item in x300332_g_MonsterTable do
            if level >= item.minLevel and level < item.maxLevel then
                monsterId = item.monsterId
                name = item.name
                break
            end
        end

        local misIndex = GetQuestIndexByID( sceneId, selfId, x300332_g_MissionId)
        SetQuestByIndex( sceneId, selfId, misIndex, x300332_MP_TARGET1, monsterId)
    	SetQuestByIndex( sceneId, selfId, misIndex, x300332_MP_TARGET4, 0)
        -- 设置任务完成标记
        SetQuestByIndex( sceneId, selfId, misIndex, x300332_MP_ISCOMPLETE, 0)
        SetQuestByIndex( sceneId, selfId, misIndex, x300332_MP_FINISH, 0)

        BeginQuestEvent( sceneId)
            AddQuestText( sceneId, "#Y"..x300332_g_MissionName)
            AddQuestText( sceneId, "#r" )
            AddQuestText( sceneId, "#Y任务目标:" )
    		AddQuestText( sceneId, format( "消灭3名%s。", name) )
        EndQuestEvent( sceneId)
        DispatchQuestTips( sceneId, selfId)

        -- 显示提示信息
        BeginQuestEvent( sceneId)
        AddQuestText( sceneId, x300332_g_strAcceptMission)
        EndQuestEvent( sceneId)
        DispatchQuestTips( sceneId, selfId)
        -- 系统消息
        Msg2Player( sceneId, selfId, x300332_g_strAcceptMission, 8, 2)

    	x300332_QuestLogRefresh( sceneId, selfId, x300332_g_MissionId )

        -- 显示任务信息
        x300332_ShowMissionInfo( sceneId, selfId, targetId)

        -- 写日志
        GamePlayScriptLog( sceneId, selfId, 731)
	end
end

---------------------------------------------------------------------------------------------------
--放弃任务
---------------------------------------------------------------------------------------------------
function x300332_ProcQuestAbandon( sceneId, selfId, MissionId)
	local bHaveMission	= IsHaveQuestNM(sceneId, selfId, x300332_g_MissionId);
	if bHaveMission > 0 then
		local misIndex = GetQuestIndexByID(sceneId, selfId, x300332_g_MissionId); 
		DelQuest(sceneId, selfId, x300332_g_MissionId);

        BeginQuestEvent( sceneId)
        AddQuestText( sceneId, x300332_g_strAbandonMission)
        EndQuestEvent( sceneId)
        DispatchQuestTips( sceneId, selfId)
        Msg2Player( sceneId, selfId, x300332_g_strAbandonMission, 8, 2)

        -- 更新任务日期
        --x300332_SetDate( sceneId, selfId, GetDayOfYear() )
        -- 更新放弃任务时间
        --x300332_SetAbandonTime( sceneId, selfId, GetMinOfDay() )
        x300332_SetTimes( sceneId, selfId, x300332_GetTimes( sceneId, selfId) + 1)
	end
end

---------------------------------------------------------------------------------------------------
--检查任务是否可提交
---------------------------------------------------------------------------------------------------
function x300332_CheckSubmit( sceneId, selfId, NPCId)
	local misIndex = GetQuestIndexByID(sceneId, selfId, x300332_g_MissionId);
	return GetQuestParam(sceneId, selfId, misIndex, x300332_MP_ISCOMPLETE);
end

---------------------------------------------------------------------------------------------------
--获得奖励
---------------------------------------------------------------------------------------------------
function x300332_GetBonus( sceneId, selfId,NpcID, SelectId )
    local misIndex = GetQuestIndexByID( sceneId, selfId, x300332_g_MissionId)
	--奖励经验
	-- local level = GetLevel( sceneId, selfId)
	-- local exp =( 1000 * 0.01 * level * 50)
    -- if exp > 0 then
		-- AddExp( sceneId, selfId, exp)
  		-- Msg2Player( sceneId, selfId, format( "获得#R经验%d点#cffcf00的奖励", exp), 8, 2)
        -- BeginQuestEvent( sceneId)
        -- AddQuestText( sceneId, format( "获得#R经验%d点#cffcf00的奖励", exp) )
        -- EndQuestEvent( sceneId)
        -- DispatchQuestTips( sceneId, selfId)
	-- end

	--奖励金钱1
	if x300332_g_BonusMoney1 > 0 then
	    AddMoney( sceneId, selfId, 1, x300332_g_BonusMoney1 )
	    Msg2Player(sceneId,selfId,format("获得#R银卡#{_MONEY%d}#W的奖励。", x300332_g_BonusMoney1),4,2)
	end

	--奖励金钱2
	if x300332_g_BonusMoney2 > 0 then
	    AddMoney( sceneId, selfId, 0, x300332_g_BonusMoney2 )
	    Msg2Player(sceneId,selfId,format("获得银币#{_MONEY%d}的奖励。", x300332_g_BonusMoney2),4,2)
	end

	--奖励金钱1
	if x300332_g_BonusMoney3 > 0 then
	    AddMoney( sceneId, selfId, 3, x300332_g_BonusMoney3 )
	    Msg2Player(sceneId,selfId,format("获得金卡#{_MONEY%d}的奖励。", x300332_g_BonusMoney3),4,2)
	end

	--江湖声望
	if x300332_g_BonusMoney4 > 0 then
		local nRongYu = GetRongYu( sceneId, selfId )
		nRongYu = nRongYu + x300332_g_BonusMoney4
		SetRongYu( sceneId, selfId, nRongYu )
		Msg2Player(sceneId,selfId,format("获得江湖声望%d的奖励。", x300332_g_BonusMoney4),4,2)
	end

	--朝廷声望
	if x300332_g_BonusMoney5 > 0 then
		local nShengWang = GetShengWang( sceneId, selfId )
		nShengWang = nShengWang + x300332_g_BonusMoney5
		SetShengWang( sceneId, selfId, nShengWang )
		Msg2Player(sceneId,selfId,format("获得朝廷声望%d的奖励。", x300332_g_BonusMoney5),4,2)
	end

	--朝廷声望
	if x300332_g_BonusMoney6 > 0 then
		AddHonor(sceneId,selfId,x300332_g_BonusMoney6)
		Msg2Player(sceneId,selfId,format("获得荣誉值%d的奖励。", x300332_g_BonusMoney6),4,2)
	end

 	--奖励固定物品
		for i, item in x300332_g_BonusItem do
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
	for i, item in x300332_g_BonusChoiceItem do
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
function x300332_ProcQuestSubmit( sceneId, selfId, NPCId, selectRadioId, MissionId)
	--判断是否有任务
	local bHaveMission = IsHaveQuestNM(sceneId, selfId, x300332_g_MissionId);
	if bHaveMission > 0 then
		local today = GetDayOfYear()
        -- 检查当日完成次数
		if x300332_GetDate( sceneId, selfId) == today then
            if x300332_GetTimes( sceneId, selfId) >= x300332_g_MaxTimes then
                return
            end
        end
        
		local misIndex = GetQuestIndexByID(sceneId, selfId, x300332_g_MissionId)
		local completed = GetQuestParam(sceneId, selfId, misIndex, x300332_MP_ISCOMPLETE)

		if completed == 1 then
            BeginAddItem( sceneId)
            if IsHaveSpecificImpact( sceneId, selfId, 9011) == 1 or IsHaveSpecificImpact( sceneId, selfId, 9012) == 1 or IsHaveSpecificImpact( sceneId, selfId, 9013) == 1 then
                AddItem( sceneId, selectRadioId, 5)
            else
                AddBindItem( sceneId, selectRadioId, 5)
            end
            local ret = EndAddItem( sceneId, selfId)
            if ret > 0 then
                DelQuest( sceneId, selfId, x300332_g_MissionId)

                local today = GetDayOfYear()
                if x300332_GetDate( sceneId, selfId) == today then
                    -- 更新当日完成次数
                    x300332_SetTimes( sceneId, selfId, x300332_GetTimes( sceneId, selfId) + 1)
                else
                    -- 更新任务日期
                    x300332_SetDate( sceneId, selfId, today)
                    -- 清除当日完成次数
                    x300332_SetTimes( sceneId, selfId, 1)
                end
                -- 更新任务日期
                --x300332_SetDate( sceneId, selfId, GetDayOfYear() )

                BeginQuestEvent( sceneId)
                AddQuestText( sceneId, x300332_g_strFinishMission)
                EndQuestEvent( sceneId)
                DispatchQuestTips( sceneId, selfId)
                Msg2Player( sceneId, selfId, x300332_g_strFinishMission, 8, 2)

		    	x300332_GetBonus( sceneId, selfId, NPCId, selectRadioId)
				
			--	x300332_UpdateTopList(sceneId,selfId)

                AddItemListToPlayer( sceneId, selfId)
                local str = format( "你获得了@item_%d", selectRadioId)
                BeginQuestEvent( sceneId)
                AddQuestText( sceneId, str)
                EndQuestEvent( sceneId)
                DispatchQuestTips( sceneId, selfId)
            else
                BeginQuestEvent( sceneId)
                AddQuestText( sceneId, "背包已满，无法得到物品！" )
                EndQuestEvent( sceneId)
                DispatchQuestTips( sceneId, selfId)
            end
            -- 写日志
            GamePlayScriptLog( sceneId, selfId, 732)
		else
			BeginQuestEvent( sceneId )
				AddQuestText( sceneId,"任务没有完成！")
			EndQuestEvent()
			DispatchQuestTips(sceneId, selfId);
		end
	else
		BeginQuestEvent( sceneId )
			AddQuestText( sceneId,"任务不存在，获取任务信息失败！")
		EndQuestEvent()
		DispatchQuestTips(sceneId, selfId);
		return
	end
end

---------------------------------------------------------------------------------------------------
--检查玩家包裹已满
---------------------------------------------------------------------------------------------------
function x300332_CheckPlayerBagFull( sceneId ,selfId)
	local result = 1

	local j = 0

	local bAdd = 0 --是否已经在固定物品奖励添加检测中已经检查出包裹已满

	--普通的奖励检查
	BeginAddItem(sceneId)
	for j, item in x300332_g_BonusItem do
		AddItem( sceneId, item.item, item.n )
    end

    --奖励可选物品
	for j, item in x300332_g_BonusChoiceItem do
		AddItem( sceneId, item.item, item.n )
    end
		
	local ret = EndAddItem(sceneId,selfId)
	if(ret > 0) then
		result = 1;
	else
		result = 0;
	end

	return result
end

-- 接受任务后显示任务信息
function x300332_ShowMissionInfo( sceneId, selfId, targetId)
	BeginQuestEvent( sceneId)
        -- 任务名称
		AddQuestText( sceneId, "#Y"..x300332_g_MissionName)
		AddQuestText( sceneId, x300332_g_MissionBook)
		AddQuestText( sceneId, " " )

		--任务目标
		AddQuestText( sceneId, "#Y任务目标：")
        local misIndex = GetQuestIndexByID( sceneId, selfId, x300332_g_MissionId)
        local Pos1 = 0
        local mon1   = GetQuestParam( sceneId, selfId, misIndex, x300332_MP_TARGET1)
        local m1Kill = GetQuestParam( sceneId, selfId, misIndex, x300332_MP_TARGET4)

        for i, item in x300332_g_MonsterTable do
            if item.monsterId == mon1 then
                Pos1 = item.posId
                break
            end
        end
        AddQuestText( sceneId, format( x300332_g_MissionTarget, Pos1, m1Kill) )
		AddQuestText( sceneId, " " )

		--提示信息
		if x300332_g_MissionTips ~= "" then
			AddQuestText( sceneId, "#Y任务提示：" )
			AddQuestText( sceneId, x300332_g_MissionTips)
			AddQuestText( sceneId, " ")
		end
	EndQuestEvent()
    DispatchQuestEventList( sceneId, selfId, targetId)
end

---------------------------------------------------------------------------------------------------
--向客户端发送任务信息
---------------------------------------------------------------------------------------------------
function x300332_DispatchMissionInfo( sceneId, selfId, NPCId)
	local level = GetLevel( sceneId, selfId)
	
	BeginQuestEvent( sceneId)
		--任务信息
		AddQuestText( sceneId, "#Y"..x300332_g_MissionName)
		AddQuestText( sceneId, x300332_g_MissionDescription)
		AddQuestText( sceneId, "#r #r #r#Y奖励内容:#W" )
               
		--任务奖励信息 

		--1、经验
		--if x300332_g_ExpBonus> 0 then
		--local level= GetLevel( sceneId, selfId)
		--local exp =( 1000 * 0.01 * level * 50)
		--if exp > 0 then
			--AddQuestExpBonus( sceneId, exp )
		--end
        AddQuestRadioItemBonus( sceneId, x300332_ItemID_Table[ 1].itemid, 5)
        AddQuestRadioItemBonus( sceneId, x300332_ItemID_Table[ 2].itemid, 5)
        AddQuestRadioItemBonus( sceneId, x300332_ItemID_Table[ 3].itemid, 5)
        AddQuestRadioItemBonus( sceneId, x300332_ItemID_Table[ 4].itemid, 5)

		--2、金钱1
		if x300332_g_BonusMoney1 > 0 then
			AddQuestMoneyBonus1( sceneId, x300332_g_BonusMoney1 )
		end

		--3、金钱2
		if x300332_g_BonusMoney2 > 0 then
			AddQuestMoneyBonus2( sceneId, x300332_g_BonusMoney2 )
		end
		--4、金钱3
		if x300332_g_BonusMoney3 > 0 then
			AddQuestMoneyBonus3( sceneId, x300332_g_BonusMoney3 )
		end

		--江湖声望
		if x300332_g_BonusMoney4 > 0 then
			AddQuestMoneyBonus4( sceneId, x300332_g_BonusMoney4 )
		end

		--朝廷声望
		if x300332_g_BonusMoney5 > 0 then
			AddQuestMoneyBonus5( sceneId, x300332_g_BonusMoney5 )
		end

		--荣誉值
		if x300332_g_BonusMoney6 > 0 then
			AddQuestMoneyBonus6( sceneId, x300332_g_BonusMoney6 )
		end

		--5、固定物品
		for i, item in x300332_g_BonusItem do
		   	AddQuestItemBonus( sceneId, item.item, item.n)
	    end

		--6、可选物品
		for i, item in x300332_g_BonusChoiceItem do
	    	AddQuestRadioItemBonus( sceneId, item.item, item.n)
	    end
	EndQuestEvent()
	DispatchQuestInfoNM( sceneId, selfId, NPCId, x300332_g_ScriptId, x300332_g_MissionId)
	CallScriptFunction( 203794, "FinishDaobaoke", sceneId, selfId)	
end

---------------------------------------------------------------------------------------------------
--向客户端发送任务未完成
---------------------------------------------------------------------------------------------------
function x300332_DispatchContinueInfo( sceneId, selfId, NPCId )
	local misIndex = GetQuestIndexByID( sceneId, selfId, x300332_g_MissionId)
    local Pos1 = 0
    local mon1   = GetQuestParam( sceneId, selfId, misIndex, x300332_MP_TARGET1)
    local m1Kill = GetQuestParam( sceneId, selfId, misIndex, x300332_MP_TARGET4)

    for i, item in x300332_g_MonsterTable do
        if item.monsterId == mon1 then
            Pos1 = item.posId
            break
        end
    end

	BeginQuestEvent( sceneId)
		--任务继续信息
		AddQuestText( sceneId, "#Y"..x300332_g_MissionName)
		AddQuestText( sceneId, format( x300332_g_ContinueInfo, Pos1) )
		AddQuestText( sceneId, " ")

		--任务目标
		AddQuestText( sceneId,"#Y完成情况：")

        AddQuestText( sceneId, format( x300332_g_MissionTarget, Pos1, m1Kill) )

  		--任务奖励信息

		--1、经验
		-- local level= GetLevel(sceneId,selfId)
		-- local exp =( 1000 * 0.01 * level * 50)
		-- if exp > 0 then
			-- AddQuestExpBonus( sceneId, exp)
		-- end

		--2、金钱1
		if x300332_g_BonusMoney1 > 0 then
			AddQuestMoneyBonus1(sceneId, x300332_g_BonusMoney1 )
		end

		--3、金钱2
		if x300332_g_BonusMoney2 > 0 then
			AddQuestMoneyBonus2(sceneId, x300332_g_BonusMoney2 )
		end
		--4、金钱3
		if x300332_g_BonusMoney3 > 0 then
			AddQuestMoneyBonus3(sceneId, x300332_g_BonusMoney3 )
		end

		--江湖声望
		if x300332_g_BonusMoney4 > 0 then
			AddQuestMoneyBonus4(sceneId, x300332_g_BonusMoney4 )
		end

		--朝廷声望
		if x300332_g_BonusMoney5 > 0 then
			AddQuestMoneyBonus5(sceneId, x300332_g_BonusMoney5 )
		end

		--荣誉值
		if x300332_g_BonusMoney6 > 0 then
			AddQuestMoneyBonus6(sceneId, x300332_g_BonusMoney6 )
		end


		--5、固定物品
		for i, item in x300332_g_BonusItem do
		   	AddQuestItemBonus(sceneId, item.item, item.n)
	    end

		--6、可选物品
		for i, item in x300332_g_BonusChoiceItem do
	    	AddQuestRadioItemBonus(sceneId, item.item, item.n)
	    end

	    --任务提示信息
	EndQuestEvent()
	DispatchQuestInfoNM( sceneId, selfId, NPCId, x300332_g_ScriptId, x300332_g_MissionId)
end

---------------------------------------------------------------------------------------------------
--向客户端发送任务完成信息
---------------------------------------------------------------------------------------------------
function x300332_DispatchCompletedInfo( sceneId, selfId, NPCId )
	BeginQuestEvent(sceneId)
		--任务完成信息
		AddQuestText(sceneId,"#Y"..x300332_g_MissionName)
		AddQuestText(sceneId,x300332_g_MissionCompleted)
		AddQuestText(sceneId," ")

  		--任务奖励信息

		--1、经验
		-- if x300332_g_ExpBonus > 0 then
			-- AddQuestExpBonus(sceneId, x300332_g_ExpBonus)
		-- end
		--local level= GetLevel(sceneId,selfId)
		--local exp =( 1000 * 0.01 * level * 50)
		--if exp > 0 then
			--AddQuestExpBonus(sceneId, exp )
		--end

		--2、金钱1
		if x300332_g_BonusMoney1 > 0 then
			AddQuestMoneyBonus1(sceneId, x300332_g_BonusMoney1 )
		end

		--3、金钱2
		if x300332_g_BonusMoney2 > 0 then
			AddQuestMoneyBonus2(sceneId, x300332_g_BonusMoney2 )
		end
		--4、金钱3
		if x300332_g_BonusMoney3 > 0 then
			AddQuestMoneyBonus3(sceneId, x300332_g_BonusMoney3 )
		end

		--江湖声望
		if x300332_g_BonusMoney4 > 0 then
			AddQuestMoneyBonus4(sceneId, x300332_g_BonusMoney4 )
		end

		--朝廷声望
		if x300332_g_BonusMoney5 > 0 then
			AddQuestMoneyBonus5(sceneId, x300332_g_BonusMoney5 )
		end

		--荣誉值
		if x300332_g_BonusMoney6 > 0 then
			AddQuestMoneyBonus6(sceneId, x300332_g_BonusMoney6 )
		end


		--5、固定物品
		for i, item in x300332_g_BonusItem do
		   	AddQuestItemBonus(sceneId, item.item, item.n)
	    end

		--6、可选物品
		for i, item in x300332_g_BonusChoiceItem do
	    	AddQuestRadioItemBonus(sceneId, item.item, item.n)
	    end
        AddQuestRadioItemBonus( sceneId, x300332_ItemID_Table[ 1].itemid, 5)
        AddQuestRadioItemBonus( sceneId, x300332_ItemID_Table[ 2].itemid, 5)
        AddQuestRadioItemBonus( sceneId, x300332_ItemID_Table[ 3].itemid, 5)
        AddQuestRadioItemBonus( sceneId, x300332_ItemID_Table[ 4].itemid, 5)
	EndQuestEvent()
	DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x300332_g_ScriptId, x300332_g_MissionId);
end

---------------------------------------------------------------------------------------------------
--怪物被杀的消息处理
---------------------------------------------------------------------------------------------------
function x300332_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
    if IsPlayerStateNormal( sceneId, selfId) ~= 1 then
        return
    end

    local misIndex = 0
    local teamSize = GetNearTeamCount( sceneId, selfId)
    -- print( "附近队伍人数："..teamSize)

    if teamSize <= 1 then -- 非组队，单独做任务
        if IsHaveQuest( sceneId, selfId, x300332_g_MissionId) <= 0 then
            return
        end
        misIndex = GetQuestIndexByID( sceneId, selfId, x300332_g_MissionId)
        if GetQuestParam( sceneId, selfId, misIndex, 0) == 1 and GetQuestParam( sceneId, selfId, misIndex, 7) == 1 then
            -- 如果任务已完成
            return
        end
        local mon1   = GetQuestParam( sceneId, selfId, misIndex, x300332_MP_TARGET1)
        local m1Kill = GetQuestParam( sceneId, selfId, misIndex, x300332_MP_TARGET4)

        if objdataId == mon1 and m1Kill < x300332_g_KillTargetCount then
            SetQuestByIndex( sceneId, selfId, misIndex, x300332_MP_TARGET4, m1Kill + 1)
        else
            -- 如果杀死的不是任务目标怪
            return
        end

        x300332_QuestLogRefresh( sceneId, selfId, x300332_g_MissionId)

        -- throw item by some probability
        local randnum = random( 1, 100)
        local itemid = 0
        if randnum >= 1 and randnum < 26 then
            itemid = x300332_ItemID_Table[ 1].itemid
        elseif randnum >= 26 and randnum < 51 then
            itemid = x300332_ItemID_Table[ 2].itemid
        elseif randnum >= 51 and randnum < 76 then
            itemid = x300332_ItemID_Table[ 3].itemid
        elseif randnum >= 76 and randnum < 101 then
            itemid = x300332_ItemID_Table[ 4].itemid
        else
            itemid = 0
        end

        if( itemid > 0) then
            BeginAddItem(sceneId)
            if IsHaveSpecificImpact( sceneId, selfId, 9011) == 1 or IsHaveSpecificImpact( sceneId, selfId, 9012) == 1 or IsHaveSpecificImpact( sceneId, selfId, 9013) == 1 then
                AddItem( sceneId, itemid, 1)
            else
                AddBindItem( sceneId, itemid, 1)
            end
            local ret = EndAddItem(sceneId,selfId)
            if ret > 0 then
                AddItemListToPlayer(sceneId,selfId)
                local str = format( "你获得了@item_%d", itemid)
                BeginQuestEvent( sceneId)
                AddQuestText( sceneId, str)
                EndQuestEvent( sceneId)
                DispatchQuestTips( sceneId, selfId)
            else
                BeginQuestEvent(sceneId)
                AddQuestText(sceneId,"物品栏已满，无法得到物品！")
                EndQuestEvent(sceneId)
                DispatchQuestTips(sceneId,selfId)
            end
        end

    	--检测任务是否完成
        m1Kill = GetQuestParam( sceneId, selfId, misIndex, x300332_MP_TARGET4)
    	if m1Kill >= x300332_g_KillTargetCount then
    		SetQuestByIndex( sceneId, selfId, misIndex, 0, 1)
    		SetQuestByIndex( sceneId, selfId, misIndex, 7, 1)
    	end
    else
        for i = 0, teamSize - 1 do
            local memberId = GetNearTeamMember( sceneId, selfId, i)
            if memberId >= 0 and IsPlayerStateNormal( sceneId, memberId) == 1 then
                if IsHaveQuest( sceneId, memberId, x300332_g_MissionId) > 0 then -- 如果该成员接受了狩猎任务
                    misIndex = GetQuestIndexByID( sceneId, memberId, x300332_g_MissionId)
                    if GetQuestParam( sceneId, memberId, misIndex, 0) == 0 or GetQuestParam( sceneId, memberId, misIndex, 7) == 0 then -- 如果该成员的狩猎任务没完成才按70%的概率掉落物品
                        local mon1   = GetQuestParam( sceneId, memberId, misIndex, x300332_MP_TARGET1)
                        local m1Kill = GetQuestParam( sceneId, memberId, misIndex, x300332_MP_TARGET4)

                        local missionMonster = 1
                        if objdataId == mon1 and m1Kill < x300332_g_KillTargetCount then
                            SetQuestByIndex( sceneId, memberId, misIndex, x300332_MP_TARGET4, m1Kill + 1)
                        else
                            missionMonster = 0
                        end

                        if missionMonster == 1 then
                            x300332_QuestLogRefresh( sceneId, memberId, x300332_g_MissionId)

                            -- throw item by some probability
                            local randnum = random( 1, 100)
                            local itemid = 0
                            if randnum >= 1 and randnum < 26 then
                                itemid = x300332_ItemID_Table[ 1].itemid
                            elseif randnum >= 26 and randnum < 51 then
                                itemid = x300332_ItemID_Table[ 2].itemid
                            elseif randnum >= 51 and randnum < 76 then
                                itemid = x300332_ItemID_Table[ 3].itemid
                            elseif randnum >= 76 and randnum < 101 then
                                itemid = x300332_ItemID_Table[ 4].itemid
                            else
                                itemid = 0
                            end

                            if( itemid > 0) then
                                BeginAddItem( sceneId)
                                if IsHaveSpecificImpact( sceneId, selfId, 9011) == 1 or IsHaveSpecificImpact( sceneId, selfId, 9012) == 1 or IsHaveSpecificImpact( sceneId, selfId, 9013) == 1 then
                                    AddItem( sceneId, itemid, 1)
                                else
                                    AddBindItem( sceneId, itemid, 1)
                                end
                                local ret = EndAddItem( sceneId, memberId)
                                if ret > 0 then
                                    AddItemListToPlayer( sceneId, memberId)
                                    local str = format( "你获得了@item_%d", itemid)
                                    BeginQuestEvent( sceneId)
                                    AddQuestText( sceneId, str)
                                    EndQuestEvent( sceneId)
                                    DispatchQuestTips( sceneId, memberId)
                                else
                                    BeginQuestEvent( sceneId)
                                    AddQuestText( sceneId, "物品栏已满，无法得到物品！" )
                                    EndQuestEvent( sceneId)
                                    DispatchQuestTips( sceneId, memberId)
                                end
                            end

                            --检测任务是否完成
                            m1Kill = GetQuestParam( sceneId, memberId, misIndex, x300332_MP_TARGET4)
                            if m1Kill >= x300332_g_KillTargetCount then
                                SetQuestByIndex( sceneId, memberId, misIndex, 0, 1)
                                SetQuestByIndex( sceneId, memberId, misIndex, 7, 1)
                            end
                        end
                    end
                end
            end
        end
    end
end

---------------------------------------------------------------------------------------------------
--物品改变
---------------------------------------------------------------------------------------------------
function x300332_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end

---------------------------------------------------------------------------------------------------
--单击NPC事件
---------------------------------------------------------------------------------------------------
function x300332_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
	if npcGuid == x300332_SubmitNPCGUID then
		local bHaveMission	= IsHaveQuestNM(sceneId, selfId, x300332_g_MissionId);
		if(bHaveMission > 0) then
			local state = GetQuestStateNM(sceneId,selfId,npcId,x300332_g_MissionId)
			AddQuestNumText(sceneId, x300332_g_MissionId, x300332_g_MissionName,state,32);
		end
	end
end

---------------------------------------------------------------------------------------------------
--任务日志刷新
---------------------------------------------------------------------------------------------------
function x300332_QuestLogRefresh( sceneId, selfId, MissionId)
	local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId)
	local times = x300332_GetTimes( sceneId, selfId)+1
    local Pos1 = 0
    local mon1   = GetQuestParam( sceneId, selfId, misIndex, x300332_MP_TARGET1)
    local m1Kill = GetQuestParam( sceneId, selfId, misIndex, x300332_MP_TARGET4)
    
    for i, item in x300332_g_MonsterTable do
        if item.monsterId == mon1 then
            Pos1 = item.posId
            break
        end
    end

	BeginQuestEvent(sceneId)
        AddQuestLogCustomText( sceneId,
                                "",                             -- 标题
                                "【个人】盗宝客（"..times.."/10）",             -- 任务名字
                                format( x300332_g_MissionTarget, Pos1, m1Kill),
                                "",                             --任务NPC
                                x300332_g_MissionBook,
                                x300332_g_MissionDescription,
                                x300332_g_MissionTips
                                )

        AddQuestRadioItemBonus( sceneId, x300332_ItemID_Table[ 1].itemid, 5)
        AddQuestRadioItemBonus( sceneId, x300332_ItemID_Table[ 2].itemid, 5)
        AddQuestRadioItemBonus( sceneId, x300332_ItemID_Table[ 3].itemid, 5)
        AddQuestRadioItemBonus( sceneId, x300332_ItemID_Table[ 4].itemid, 5)
	EndQuestEvent()
	DispatchQuestLogUpdate( sceneId, selfId, MissionId);
end

function x300332_ProcQuestLogRefresh( sceneId, selfId, MissionId)
    x300332_QuestLogRefresh( sceneId, selfId, MissionId)
end

---------------------------------------------------------------------------------------------------
--强行加任务
---------------------------------------------------------------------------------------------------
function x300332_OnForceAddMission( sceneId, selfId, npcId, MissionId)
end

-- 获得放弃任务时间
function x300332_GetTimes( sceneId, selfId)
    return GetQuestData( sceneId, selfId, MD_DAOBAOKE_TIMES[ 1], MD_DAOBAOKE_TIMES[ 2], MD_DAOBAOKE_TIMES[ 3] )
end

-- 设置放弃任务时间
function x300332_SetTimes( sceneId, selfId, value)
    SetQuestData( sceneId, selfId, MD_DAOBAOKE_TIMES[ 1], MD_DAOBAOKE_TIMES[ 2], MD_DAOBAOKE_TIMES[ 3], value)
end

-- 获得接受任务日期
function x300332_GetDate( sceneId, selfId)
    return GetQuestData( sceneId, selfId, MD_DAOBAOKE_DATE[ 1], MD_DAOBAOKE_DATE[ 2], MD_DAOBAOKE_DATE[ 3] )
end

-- 设置接受任务日期
function x300332_SetDate( sceneId, selfId, value)
    SetQuestData( sceneId, selfId, MD_DAOBAOKE_DATE[ 1], MD_DAOBAOKE_DATE[ 2], MD_DAOBAOKE_DATE[ 3], value)
end