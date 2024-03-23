--########################################
--##迷宫除恶跑环脚本任务 by rj 2010-9-6 ##
--########################################

--***********************
--Const
--***********************
x562000_g_ScriptId 					= 562000          				--脚本 ID
x562000_g_MissionId 				= 9502            				--任务 ID
x562000_g_CurScriptCountry			= 0								--当前脚本服务国家 0 - 3
x562000_g_SubmitNpcGUID				= 101650						--提交任务 NPC，在 Obj_List.tab 中需要配置，在 Obj_Quest.tab 中无需关联任务
x562000_g_MissionItem 				= 13040040						--怪物掉落任务道具
x562000_g_MissionItemNum 			= 60								--任务道具收集数量		
x562000_g_MissionItemDropRate 		= 100                            --任务道具掉落随即率		
x562000_g_MissionItemDropMaxNum 	= 1								--任务道具掉落最大数量		
x562000_g_MissionRingNum 			= 10								--任务环数，留出 5 位 MD，最多 31 环
x562000_g_AcceptMinLevel 			= 35							--获取任务最小等级，注意：Obj_List.tab 中的最小级如果比这个小将会出现灰色叹号但却可接的情况
x562000_g_AcceptMaxLevel 			= 49							--获取任务最大等级，注意：同上
x562000_g_AcceptLevelDataIdx		= 1								--接受时的角色等级任务数据设置索引

x562000_g_AllBonusItemList 			= 								--完整一轮奖励物品列表，如果用户不在配置级别范围内显示和最终添加都不会处理
{{id = 11050001, num = 40, minlevel = 35, maxlevel = 39}, {id = 11050002, num = 40, minlevel = 40, maxlevel = 44}, {id = 11050002, num = 40, minlevel = 45, maxlevel = 49}}

x562000_g_KillMonsterList 			= 								--用户等级击杀任务怪列表，玩家级别不够怪物不会进行掉落
{{name = "幽蛰之蜂", sceneid = 90066, typeid = 6901, minlevel = 35, maxlevel = 39},
{name = "幽纹之豹", sceneid = 90067, typeid = 6902, minlevel = 40, maxlevel = 44}, 
{name = "幽面之魈", sceneid = 90068, typeid = 6903, minlevel = 45, maxlevel = 49}}

x562000_g_MissionName				= 								--任务名称
"【个人】迷宫除恶"
x562000_g_AcceptDesc				= 								--任务描述(npc)
"\t王国迷宫中的各种怪物横行已有多年，无数勇士试图根除他们，但最后都殒命在于此。\n\t最近一位云游的老者点播根除怪物之法，就是收集怪物的兽首骨聚而焚之，让焚骨之烟充斥迷宫，怪物闻烟既毙。\n\t你愿意完成收集兽首骨的艰巨任务吗？"		
x562000_g_CompleteDesc	 			= 								--完成任务描述(npc)
"\t如此的年纪有这般武艺和胆识着实不易，将来封官授爵必不是难事啊!"	
x562000_g_UnCompleteDesc			= 								--未完成任务描述(npc)
"\t你还没有收集足够的兽首骨，你有什么苦难就直接告诉我，我不会为难你的。"	
x562000_g_MissionFmtName			= x562000_g_MissionName	.. 		--任务格式化名称(player & npc)
"(%d/%d)"
x562000_g_TargetFmtDesc	 			= 								--任务目标(player)
"消灭@npc_%d收集@item_%d#W(%d/%d)"	
x562000_g_BookDesc	 				= 								--任务攻略(player)
"消灭@npc_%d收集@item_%d#W(%d/%d)"
x562000_g_TipDesc	 				= 								--任务提示描述(player)
"\t可以组队完成，加入队伍你也会提高完成任务的速度。"
x562000_g_LevelErrTip				= 								--级别不对无法接受任务提示（点开NPC后再升级的边界保护）
"\您的级别不适合接受此任务!"	
x562000_g_TodayErrTip				= 								--本日已经完成所有环接受任务提示
"今天已经无法领取任务，请明日再来吧！"	
x562000_g_MisFullErrTip				= 								--任务已满，接受任务失败提示
"任务已满，任务接受失败"	
x562000_g_BagFullErrTip1			= 								--添加任务物品背包满提示
"物品栏已满，无法得到任务物品！"	
x562000_g_BagFullErrTip2			= 								--添加奖励物品背包满提示
"物品栏已满，无法得到奖励物品，任务提交失败！"	
x562000_g_GiveupErrTip         		= 								--放弃任务提示
"您放弃了任务：" .. x562000_g_MissionName
x562000_g_AcceptOkTip         		= 								--接受任务成功提示
"您接受了任务：" .. x562000_g_MissionName
x562000_g_FinishTip         		= 								--接受任务成功提示
"您完成了任务：" .. x562000_g_MissionName
x562000_g_GetExpFmtTip         		= 								--完成任务获得经验提示
"完成本环任务获得%d经验"
---------------------------------------------------------------------------------------------------------------------------------

--**********************************
--获得接受时等级，为非法值做了适应
--**********************************
function x562000_GetAcceptLevel(sceneId, selfId)

	acceptLevel = GetQuestParam(sceneId, selfId, GetQuestIndexByID(sceneId, selfId, x562000_g_MissionId), x562000_g_AcceptLevelDataIdx)
	
	--为替换脚本后有此任务但没有接受位内容的玩家适应值
	if acceptLevel == 0 then
		local misIndex = GetQuestIndexByID( sceneId, selfId, x562000_g_MissionId)
		selfLevel = GetLevel(sceneId, selfId)

		if selfLevel > x562000_g_AcceptMaxLevel then
			SetQuestByIndex(sceneId, selfId, misIndex, x562000_g_AcceptLevelDataIdx, x562000_g_AcceptMaxLevel)
			return x562000_g_AcceptMaxLevel
		else
			SetQuestByIndex(sceneId, selfId, misIndex, x562000_g_AcceptLevelDataIdx, selfLevel)
			return selfLevel			
		end
	end
	
	return acceptLevel
end

--**********************************
--获得当前环数，为非法值做了适应
--**********************************
function x562000_GetCurRing(sceneId, selfId)

	local curRingIdx = GetQuestData(sceneId, selfId, MD_QUEST_MIGONGCHUE_CURRING[1], MD_QUEST_MIGONGCHUE_CURRING[2], MD_QUEST_MIGONGCHUE_CURRING[3])
	
	--非法值判定，让其适应为第一环，输出警告
	if curRingIdx < 0 then
		WriteLog(2, format("minggongchue GGetCurRing: GetQuestData curRingIdx(%d)", curRingIdx))
		SetQuestData(sceneId, selfId, MD_QUEST_MIGONGCHUE_CURRING[1], MD_QUEST_MIGONGCHUE_CURRING[2], MD_QUEST_MIGONGCHUE_CURRING[3], 0)
		return 0
	end
	
	--如果调整小总环数后用户当前环大于总环数则重新设置当前环数为新的最大环数
	if curRingIdx >= x562000_g_MissionRingNum then
		SetQuestData(sceneId, selfId, MD_QUEST_MIGONGCHUE_CURRING[1], MD_QUEST_MIGONGCHUE_CURRING[2], MD_QUEST_MIGONGCHUE_CURRING[3], x562000_g_MissionRingNum - 1)
		return x562000_g_MissionRingNum - 1
	end
	
	return curRingIdx
end

--**********************************
--经验计算公式函数，传入角色级别
--**********************************
function x562000_GetThisTimeExp(sceneId, selfId, selfLevel)
	return selfLevel * 220 * (x562000_GetCurRing(sceneId, selfId) + 11) + 46200
end

--**********************************
--接受及交付任务时显示的 NPC 对话框处理
--**********************************
function x562000_ShowNpcContext(sceneId, selfId, npcId, showMainText, isAccept)
	
	local curRingIdx = x562000_GetCurRing(sceneId, selfId)
	
	BeginQuestEvent(sceneId)

	--任务信息
	AddQuestText(sceneId, "#Y" .. x562000_g_MissionName)
	AddQuestText(sceneId, showMainText)
	
	--根据接受及交付不同取得的玩家等级方式是不同的，接受要最新的（接受前显示时还没有记录原始等级）而交付则是要原始的
	local selfLevel = 0
	if isAccept == 1 then
		selfLevel = GetLevel(sceneId, selfId)
	else
		selfLevel = x562000_GetAcceptLevel(sceneId, selfId)
	end
	
	--显示经验奖励
	local getExp = x562000_GetThisTimeExp(sceneId, selfId, selfLevel, curRingIdx)
	if getExp > 0 then
		AddQuestExpBonus(sceneId, getExp)
	end

	--显示最后一环奖励物品
	if curRingIdx + 1 == x562000_g_MissionRingNum then
		for i, item in x562000_g_AllBonusItemList do
		   	if selfLevel >= item.minlevel and selfLevel <= item.maxlevel then
		   		AddQuestItemBonus(sceneId, item.id, item.num)
		   	end
	    end
	end

	EndQuestEvent()
	DispatchQuestInfoNM(sceneId, selfId, npcId, x562000_g_ScriptId, x562000_g_MissionId)
end

--**********************************
--任务日志刷新
--**********************************
function x562000_QuestLogRefresh(sceneId, humanId)

    if IsHaveQuest(sceneId, humanId, x562000_g_MissionId) == 0 then
        return
    end

	local curRingIdx = x562000_GetCurRing(sceneId, humanId)
	
	BeginQuestEvent(sceneId)
   
   	local rawLevel = x562000_GetAcceptLevel(sceneId, humanId)
	local getExp = x562000_GetThisTimeExp(sceneId, humanId, rawLevel, curRingIdx)

	--显示经验奖励
	if getExp > 0 then
		AddQuestExpBonus(sceneId, getExp)
	end
	
	--显示最后一环奖励物品
	if curRingIdx + 1 == x562000_g_MissionRingNum then
		for i, item in x562000_g_AllBonusItemList do
		   	if rawLevel >= item.minlevel and rawLevel <= item.maxlevel then
		   		AddQuestItemBonus(sceneId, item.id, item.num)
		   	end
	    end
	end
	
	local itemNumOnPlayer = GetItemCount(sceneId, humanId, x562000_g_MissionItem)
	local chkFind = 0
	local monsterSceneId = 0
	
	--检查击杀的怪是否符合原始级别的要求
	for i, item in x562000_g_KillMonsterList do
		if rawLevel >= item.minlevel and rawLevel <= item.maxlevel then
			monsterSceneId = item.sceneid
			chkFind = 1
			break
		end
	end
	
	--如果没有合适的等级对应则找到最大等级相近的怪物id，然后进行任务更新（目前记录原始等级的方式只要不是配置错误就不会出现）
	if chkFind == 0 then
		local maxLevel = 0
		for i, item in x562000_g_KillMonsterList do
			if maxLevel < item.maxlevel then
				maxLevel = item.maxlevel
				monsterSceneId = item.sceneid
			end
		end
	end
			
			--更新玩家任务日志该任务显示
			AddQuestLogCustomText
						(
							sceneId,
		"", 																												--任务标题
							format(x562000_g_MissionFmtName, curRingIdx + 1, x562000_g_MissionRingNum), 										--任务名字
		format(x562000_g_TargetFmtDesc, monsterSceneId, x562000_g_MissionItem, itemNumOnPlayer, x562000_g_MissionItemNum), 	--任务目标
							format("@npc_%d", x562000_g_SubmitNpcGUID),	 																		--任务提交 NPC                     
		format(x562000_g_BookDesc, monsterSceneId, x562000_g_MissionItem, itemNumOnPlayer, x562000_g_MissionItemNum),		--任务攻略
							x562000_g_AcceptDesc, 																								--任务描述
							x562000_g_TipDesc 																									--任务小提示
						 )
	
	EndQuestEvent()
	DispatchQuestLogUpdate(sceneId, humanId, x562000_g_MissionId)
end

--**********************************
--列举事件，如果提交 NPC 与接受不同则提交时不会进入
--**********************************
function x562000_ProcEnumEvent(sceneId, selfId, npcId, misId)

	--国家判定
	if x562000_g_CurScriptCountry ~= GetCurCountry(sceneId, selfId) then
		return
	end

	local curRingIdx = x562000_GetCurRing(sceneId, selfId)

	--任务领取级别判定
	local selfLevel = GetLevel(sceneId, selfId)
	if selfLevel < x562000_g_AcceptMinLevel or selfLevel > x562000_g_AcceptMaxLevel then
		 return
	end

    if IsHaveQuestNM(sceneId, selfId, x562000_g_MissionId) == 0 then
        local curState = GetQuestStateNM(sceneId, selfId, npcId, x562000_g_MissionId)
        AddQuestNumText(sceneId, x562000_g_MissionId, x562000_g_MissionName, curState, 0);
    end
end

--**********************************
--点击任务事件
--**********************************
function x562000_ProcEventEntry(sceneId, selfId, npcId, misId, selIndex)
	
	--国家判定
	if x562000_g_CurScriptCountry ~= GetCurCountry(sceneId, selfId) then
		return
	end
	
	--特别注意不能像 C++ 那样不加 == 判定
	if IsHaveQuestNM(sceneId, selfId, x562000_g_MissionId) == 1 then 
		local isFinish = GetQuestParam(sceneId, selfId, GetQuestIndexByID(sceneId, selfId, x562000_g_MissionId), 0)

		--任务完成与未完成描述显示
		if isFinish == 1 then        
	        x562000_ShowNpcContext(sceneId, selfId, npcId, x562000_g_CompleteDesc, 0)
		elseif isFinish == 0 then
			BeginQuestEvent(sceneId)                                                                
			AddQuestText(sceneId, x562000_g_UnCompleteDesc)                  
			EndQuestEvent()                                                                         
			DispatchQuestEventList(sceneId, selfId, npcId, x562000_g_ScriptId, x562000_g_MissionId)
		end
	else
		--任务领取级别判定，防止第一步对话后角色升级的情况。不可接但可提交（上面的流程）
		local selfLevel = GetLevel(sceneId, selfId)
		if selfLevel < x562000_g_AcceptMinLevel or selfLevel > x562000_g_AcceptMaxLevel then
	        Msg2Player(sceneId, selfId, selfLevel, x562000_g_LevelErrTip, 8, 3)		
			return
		end

		x562000_ShowNpcContext(sceneId, selfId, npcId, x562000_g_AcceptDesc, 1)
	end
end

--**********************************
--脚本任务上线、每次打开任务框及点击任务项调用事件（表格任务不走这里）
--**********************************
function x562000_ProcQuestLogRefresh(sceneId, selfId, misId)
    x562000_QuestLogRefresh(sceneId, selfId, x562000_g_MissionId)
end

--**********************************
--接/交任务处理事件
--**********************************
function x562000_ProcQuestAccept(sceneId, selfId, npcId, misId)

	--国家判定
	if x562000_g_CurScriptCountry ~= GetCurCountry(sceneId, selfId) then
		return
	end

	local dayOfYear = GetDayOfYear()

	--如果上次接受任务的时间和本日不是以天则把本日已做环数 MD 设置为 0
	local lastDate = GetQuestData(sceneId, selfId, MD_QUEST_MIGONGCHUE_ACCEPTDATE[1], MD_QUEST_MIGONGCHUE_ACCEPTDATE[2], MD_QUEST_MIGONGCHUE_ACCEPTDATE[3])
	if lastDate ~= dayOfYear then
		SetQuestData(sceneId, selfId, MD_QUEST_MIGONGCHUE_TODAYRING[1], MD_QUEST_MIGONGCHUE_TODAYRING[2], MD_QUEST_MIGONGCHUE_TODAYRING[3], 0)	
		SetQuestData(sceneId, selfId, MD_QUEST_MIGONGCHUE_ACCEPTDATE[1], MD_QUEST_MIGONGCHUE_ACCEPTDATE[2], MD_QUEST_MIGONGCHUE_ACCEPTDATE[3], dayOfYear)
	end
	
	local curRingIdx = x562000_GetCurRing(sceneId, selfId)
		
	local todayRingNum = GetQuestData(sceneId, selfId, MD_QUEST_MIGONGCHUE_TODAYRING[1], MD_QUEST_MIGONGCHUE_TODAYRING[2], MD_QUEST_MIGONGCHUE_TODAYRING[3])
	if todayRingNum < 0 then
		WriteLog(2, format("minggongchue ProcQuestAccept: GetQuestData todayRingNum(%d)", todayRingNum))
		return
	end
	
	--为修改后的总环数做适应性调整
	if todayRingNum > x562000_g_MissionRingNum then
		SetQuestData(sceneId, selfId, MD_QUEST_MIGONGCHUE_TODAYRING[1], MD_QUEST_MIGONGCHUE_TODAYRING[2], MD_QUEST_MIGONGCHUE_TODAYRING[3], x562000_g_MissionRingNum)
		todayRingNum = x562000_g_MissionRingNum
	end

	if IsHaveQuestNM(sceneId, selfId, x562000_g_MissionId) == 0 then
	local selfLevel = GetLevel(sceneId, selfId)
	
		--任务领取级别判定，防止第一步对话后角色升级的情况
		if selfLevel < x562000_g_AcceptMinLevel or selfLevel > x562000_g_AcceptMaxLevel then
			Msg2Player(sceneId, selfId, x562000_g_LevelErrTip, 8, 3)
			return
		end

		--今天是否已经做满环判定
		if todayRingNum >= x562000_g_MissionRingNum then
			Msg2Player(sceneId, selfId, x562000_g_TodayErrTip, 8, 3)
			return
		end

		local retOpt = AddQuest(sceneId, selfId, x562000_g_MissionId, x562000_g_ScriptId, 1, 0, 1, 1)
    	
    	--自身任务满错误提示
    	if retOpt == 0 then
            Msg2Player(sceneId, selfId, x562000_g_MisFullErrTip, 8, 3)
    		return
    	end
    	
    	--更新接受任务的日期 MD
    	SetQuestData(sceneId, selfId, MD_QUEST_MIGONGCHUE_ACCEPTDATE[1], MD_QUEST_MIGONGCHUE_ACCEPTDATE[2], MD_QUEST_MIGONGCHUE_ACCEPTDATE[3], dayOfYear)
 	
        -- 设置任务完成标记
        local misIndex = GetQuestIndexByID( sceneId, selfId, x562000_g_MissionId)
        SetQuestByIndex(sceneId, selfId, misIndex, 0, 0)

        -- 显示提示信息
        Msg2Player(sceneId, selfId, x562000_g_AcceptOkTip, 8, 2)
        Msg2Player(sceneId, selfId, x562000_g_AcceptOkTip, 8, 3)
        
        --更新自身任务显示
        x562000_QuestLogRefresh(sceneId, selfId, x562000_g_MissionId)
		SetQuestByIndex(sceneId, selfId, misIndex, x562000_g_AcceptLevelDataIdx, selfLevel)
    else
		local isFinish = GetQuestParam(sceneId, selfId, GetQuestIndexByID(sceneId, selfId, x562000_g_MissionId), 0)
		local rawLevel = x562000_GetAcceptLevel(sceneId, selfId)
		
		if isFinish == 1 then

			--最后一环奖励物品
			if curRingIdx + 1 == x562000_g_MissionRingNum then
				for i, item in x562000_g_AllBonusItemList do
				   	if rawLevel >= item.minlevel and rawLevel <= item.maxlevel then
					   	BeginAddItem(sceneId)
		                AddBindItem(sceneId, item.id, item.num)
		                
		                if EndAddItem(sceneId, selfId) > 0 then
		                    AddItemListToPlayer(sceneId, selfId)
		                else
	   					 	Msg2Player(sceneId, selfId, x562000_g_BagFullErrTip2, 8, 3)		
	   					 	return --无法奖励物品将不会完成任务
		                end
		            end
			    end
			end

			--奖励本环经验
			local getExp = x562000_GetThisTimeExp(sceneId, selfId, rawLevel, curRingIdx)
			
			--更新当前环数与本日已做环数 MD
			curRingIdx = curRingIdx + 1
			todayRingNum = todayRingNum + 1
			SetQuestData(sceneId, selfId, MD_QUEST_MIGONGCHUE_CURRING[1], MD_QUEST_MIGONGCHUE_CURRING[2], MD_QUEST_MIGONGCHUE_CURRING[3], mod(curRingIdx, x562000_g_MissionRingNum))
			SetQuestData(sceneId, selfId, MD_QUEST_MIGONGCHUE_TODAYRING[1], MD_QUEST_MIGONGCHUE_TODAYRING[2], MD_QUEST_MIGONGCHUE_TODAYRING[3], todayRingNum)			

			DelQuest(sceneId, selfId, x562000_g_MissionId)
			
			--删除任务物品
			local itemNumOnPlayer = GetItemCount(sceneId, selfId, x562000_g_MissionItem)
			if itemNumOnPlayer > 0 then
				DelItem(sceneId, selfId, x562000_g_MissionItem, itemNumOnPlayer)
			end

	   	 	if getExp > 0 then
	   	 		AddExp(sceneId, selfId, getExp)
	    		Msg2Player(sceneId, selfId, format(x562000_g_GetExpFmtTip, getExp), 8 ,2)
	    	end

            Msg2Player(sceneId, selfId, x562000_g_FinishTip, 8, 2)
            Msg2Player(sceneId, selfId, x562000_g_FinishTip, 8, 3)
		end
	end
end

--**********************************
--放弃任务事件
--**********************************
function x562000_ProcQuestAbandon(sceneId, selfId, misId)

	if IsHaveQuestNM(sceneId, selfId, x562000_g_MissionId) == 1 then
		DelQuest(sceneId, selfId, x562000_g_MissionId)
		
		--删除任务物品
		local itemNumOnPlayer = GetItemCount(sceneId, selfId, x562000_g_MissionItem)
		if itemNumOnPlayer > 0 then
			DelItem(sceneId, selfId, x562000_g_MissionItem, itemNumOnPlayer)
		end
        
        Msg2Player(sceneId, selfId, x562000_g_GiveupErrTip, 8, 2)
        Msg2Player(sceneId, selfId, x562000_g_GiveupErrTip, 8, 3)
        
        --放弃任务使用本日满环处理，当前环数清零
        SetQuestData(sceneId, selfId, MD_QUEST_MIGONGCHUE_TODAYRING[1], MD_QUEST_MIGONGCHUE_TODAYRING[2], MD_QUEST_MIGONGCHUE_TODAYRING[3], x562000_g_MissionRingNum)	
        SetQuestData(sceneId, selfId, MD_QUEST_MIGONGCHUE_CURRING[1], MD_QUEST_MIGONGCHUE_CURRING[2], MD_QUEST_MIGONGCHUE_CURRING[3], 0)
	end
end

--**********************************
--单击NPC事件
--**********************************
function x562000_ProcQuestAttach(sceneId, selfId, npcId, npcId, misIndex, misId)
	
	--国家判定
	if x562000_g_CurScriptCountry ~= GetCurCountry(sceneId, selfId) then
		return
	end

	--不论级别符合与否都通过，这里是提交流程
	if npcId == x562000_g_SubmitNpcGUID then
		if IsHaveQuestNM(sceneId, selfId, x562000_g_MissionId) == 1 then
			local curState = GetQuestStateNM(sceneId, selfId, npcId, x562000_g_MissionId)
			local curRingIdx = x562000_GetCurRing(sceneId, selfId)
			
			AddQuestNumText(sceneId, x562000_g_MissionId, x562000_g_MissionName, curState, 0);
		end
	end
end

--**********************************
--任务物品变更事件
--**********************************
function x562000_ProcQuestItemChanged(sceneId, selfId, itemId, misId)

	if itemId ~= x562000_g_MissionItem then
		return
	end

    x562000_QuestLogRefresh(sceneId, selfId, x562000_g_MissionId)

    --检测任务是否完成
	local itemNumOnPlayer = GetItemCount(sceneId, selfId, x562000_g_MissionItem)
    local misIndex = GetQuestIndexByID(sceneId, selfId, x562000_g_MissionId)
    
    --进行任务完成检测（0、7索引对应实际功能与!?显示两种）
	if itemNumOnPlayer >= x562000_g_MissionItemNum then
		SetQuestByIndex(sceneId, selfId, misIndex, 0, 1)
		SetQuestByIndex(sceneId, selfId, misIndex, 7, 1)
	else
		SetQuestByIndex(sceneId, selfId, misIndex, 0, 0)
		SetQuestByIndex(sceneId, selfId, misIndex, 7, 0)
	end
end

--**********************************
--杀死怪物事件，注意：队友(没有该任务)杀怪也会以自己的 selfId 进入
--**********************************
function x562000_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, misId)
		
	--取得这个怪物死后拥有分配权的人数，函数自动处理条件不够（如距离）无法获得的情况
	local numKilled = GetMonsterOwnerCount(sceneId, objId)
	
	for i = 0, numKilled - 1 do
	 	
	 	--取得拥有分配权的人的 objId
		local humanId = GetMonsterOwnerID(sceneId, objId, i)
		
		if IsPlayerStateNormal(sceneId, humanId) == 1 then
			local rawLevel = x562000_GetAcceptLevel(sceneId, humanId)
			local chkPass = 0
			
			--检查击杀的怪是否符合接受任务记录的原始级别的要求
			for j, item in x562000_g_KillMonsterList do
		   		if objdataId == item.typeid and rawLevel >= item.minlevel and rawLevel <= item.maxlevel then
			   		chkPass = 1
			   		break
		   		end
	    	end
	    	
	        if humanId ~= -1 and chkPass == 1 then         
	        	
	        	--如果这个人拥有任务
	            if IsHaveQuestNM(sceneId, humanId, x562000_g_MissionId) == 1 then
	                
	                --配置常量配置非法
	                if x562000_g_MissionItemNum <= 0 or x562000_g_MissionItemDropMaxNum <= 0 then 
	                	return
	                end
	
	                local itemNumOnPlayer = GetItemCount(sceneId, humanId, x562000_g_MissionItem)
	                if itemNumOnPlayer < x562000_g_MissionItemNum then
		                --掉落率处理
		                local dropRand = random(100)
		                if dropRand <= x562000_g_MissionItemDropRate then
		
			                --算出掉落数量
			                local dropNum = random(x562000_g_MissionItemDropMaxNum)
			                if dropNum == 0 then
			                    dropNum = 1
			                end
			                
			                --根据用户当前拥有的数量计算出这次掉落的数量
			                if dropNum > x562000_g_MissionItemNum - itemNumOnPlayer then
			                    dropNum = x562000_g_MissionItemNum - itemNumOnPlayer
			                end
			                
			                BeginAddItem(sceneId)
			                AddBindItem(sceneId, x562000_g_MissionItem, dropNum)
			                
			                if EndAddItem(sceneId, humanId) > 0 then
			                    AddItemListToPlayer(sceneId, humanId)
			                    x562000_QuestLogRefresh(sceneId, humanId, x562000_g_MissionId)
			                else
	       					 	Msg2Player(sceneId, humanId, x562000_g_BagFullErrTip1, 8, 3)		   
			                end
			            end
					end
	            end
	        end
	    end
	end
end


--每个任务都有8个INT，刚接受任务时初始值都是0，其中第一个和最后一个是任务系统需要用来标识任务是否完成的固定字段，不能用作别的。
--剩下6个可以用来保存任务自身属性，例如要收集或使用的物品ID，要消灭的怪物ID和数量等等，完成了任务时把第一个和最后一个QuestParam设置为1后，
--系统会更新任务状态，再去接任务NPC处可以看见NPC头顶问号状态自动变成黄色。

--添加任务函数AddQuest的后四个参数定义任务类型及其事件是否回调触发函数，0表示不触发，1表示触发。第五个参数为打怪任务标记，如果为1调用后角
--色每次杀死一个怪物时都会回调任务脚本的ProcQuestObjectKilled函数；第六个参数为1调用后角色进入指定区域时将回调任务脚本的ProcAreaEntered函数；第七个参数为
--1调用后角色身上或背包里的物品发生变化时将回调任务脚本的ProcQuestItemChanged"函数；最后一个参数为1调用后角色每次点击NPC时将回调任务脚本的ProcQuestAttach函数。