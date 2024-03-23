--MisDescBegin

x300954_g_ScriptId 					= 300954                  --脚本ID
x300954_g_MissionId 				= 7764                    --任务ID

x300954_g_MissionKind 				= 1                       --任务类型
x300954_g_LevelLess					= 40                      --场景开放等级  <=0 表示不限制

x300954_g_MissionName				= "【国家】罗马帝国进贡"
x300954_g_MissionTarget				= "  找到#{_ITEM%d}(%d/%d)"      --任务目标
x300954_g_MissionInfo				= "\t强大的国家不会满足于这一点点荣誉。不断的升级领地图腾会使得领地工资和完成出国任务的经验，荣誉有更高加成。去带来些升级所缺部件，记住，我们是为了荣誉而战！"      --任务信息
x300954_g_ContinueInfo				= "\t找到#{_ITEM%d}"	  --任务继续信息
x300954_g_MissionCompleted			= "\t感谢你为领地图腾升级所做的贡献！"	  --任务完成信息
x300954_g_MissionHelp				= "\t每天所需部件为随机，部件可以与其他人交换以更快的完成任务。"      --任务提示信息
x300954_g_Missionruse				= "\t使用生活技能，制造1个#{_ITEM%d}"      --任务攻略

--目标
x300954_g_ExtTarget					= { {type=20,n=1,target=""} }


--奖励
x300954_g_ExpBonus					= 0     --奖励：经验 （数值填0，字符串为空，表示没有该项奖励）
x300954_g_BonusItem					= {}	--奖励：物品

x300954_g_BonusMoney1               = 0  --任务奖励绑定银币
x300954_g_BonusMoney2               = 0  --任务奖励非绑定银币
x300954_g_BonusMoney3               = 0  --任务奖励绑定金币
x300954_g_BonusMoney4               = 0  --任务奖励朝廷声望
x300954_g_BonusMoney5               = 0  --任务奖励江湖声望
x300954_g_BonusMoney6               = 0  --任务奖励荣誉

x300954_g_BonusChoiceItem           = {}

--MisDescEnd

x300954_g_MaxCount					= 3

-- 交任务NPC
x300954_g_TargetNPC                 = 400604

-- 任务物品列表
x300954_g_MissionItemTable          = {
                                        { itemId = 11041000, count = 1  }, 
										{ itemId = 11041010, count = 1  }, 
                                        { itemId = 11041020, count = 1  }, 
                                        { itemId = 11041030, count = 1  }, 
                                        { itemId = 11041040, count = 1	}, 
                                        { itemId = 11041050, count = 1	}, 
}

x300954_g_LairdMap					= 21 -- 神圣罗马帝国
-- 经验奖励系数
x300954_g_CoffExp                   = 1500
-- 玩法开关id
x300954_g_IsEnableId                = 1050
-- 玩法开放时间(从0点起的第x分钟)
x300954_g_OpenTime                  = 540
-- 玩法关闭时间(从0点起的第x分钟)
x300954_g_EndTime                   = 1380

x300954_g_SaveItem                   = -1
x300954_g_SaveItemDay                = -1

-- 回调
function x300954_CallbackEnumEvent(sceneId, selfId, targetId, MissionId)
	if GetGameOpenById( x300954_g_IsEnableId) <= 0 then
        return
    end
   
    local country = GetCurCountry(sceneId, selfId)
    local nLairdCountry = GetSceneLairdCountryId(x300954_g_LairdMap)
    if nLairdCountry ~= country then
		return
	end
    
    if MissionId == 0 then
		if IsHaveQuest(sceneId, selfId, x300954_g_MissionId) <= 0 then
			return 
		end
		
		local npcGuid = GetMonsterGUID(sceneId,targetId)
		if npcGuid ~= x300954_g_TargetNPC then
			return
		end 
	else
		if IsHaveQuest(sceneId, selfId, x300954_g_MissionId) > 0 then
			return 
		end
    end
    
    local state = GetQuestStateNM(sceneId, selfId, targetId, x300954_g_MissionId)
	AddQuestNumText(sceneId,x300954_g_MissionId,x300954_g_MissionName,state,MissionId )
end
---------------------------------------------------------------------------------------------------
--列举事件
---------------------------------------------------------------------------------------------------
function x300954_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
end

---------------------------------------------------------------------------------------------------
--任务入口函数
---------------------------------------------------------------------------------------------------
function x300954_ProcEventEntry(sceneId, selfId, targetId, MissionId, nExtIdx)

	if nExtIdx > 0 then
		if IsHaveQuest( sceneId, selfId, x300954_g_MissionId) > 0 then

			x300954_DispatchContinueInfo(sceneId, selfId, targetId) --未完成任务显示
        else
			x300954_DispatchMissionInfo(sceneId, selfId, targetId)	--任务信息显示
		end
	else
		local misIndex = GetQuestIndexByID( sceneId, selfId, x300954_g_MissionId)
		if GetQuestParam( sceneId, selfId, misIndex, 7) == 0 then
            x300954_DispatchContinueInfo(sceneId, selfId, targetId) --未完成任务显示
        else
            x300954_DispatchCompletedInfo(sceneId, selfId, targetId) --完成任务显示
        end
	end
end

---------------------------------------------------------------------------------------------------
--检测接受条件
---------------------------------------------------------------------------------------------------
function x300954_ProcAcceptCheck(sceneId, selfId, targetId)
	local bHaveMission	= IsHaveQuest(sceneId, selfId, x300954_g_MissionId)
	if( bHaveMission > 0) then
		return 0
	else
		return 1
	end
end

---------------------------------------------------------------------------------------------------
--接受条件
---------------------------------------------------------------------------------------------------
function x300954_ProcQuestAccept(sceneId, selfId, targetId, missionId)

    if IsHaveQuest(sceneId, selfId, x300954_g_MissionId) > 0 then
		-- 时间检查
        local nowTime = GetMinOfDay()
        if nowTime < x300954_g_OpenTime or nowTime >= x300954_g_EndTime then
            Msg2Player( sceneId, selfId, "只有在每日的#G9：00--23：00#cffcf00内才可领取任务", 8, 2)
            Msg2Player( sceneId, selfId, "只有在每日的#G9：00--23：00#cffcf00内才可领取任务", 8, 3)
            return
        end
        
        local country = GetCurCountry(sceneId, selfId)
		local nLairdCountry = GetSceneLairdCountryId(x300954_g_LairdMap)
		if nLairdCountry ~= country then
			Msg2Player( sceneId, selfId, "很抱歉，此领地不属于你的国家", 8, 3)
			return
		end
		
		local misIndex = GetQuestIndexByID(sceneId, selfId, x300954_g_MissionId)
		local rnd = GetQuestParam( sceneId, selfId, misIndex, 1)
        if DelItem(sceneId, selfId, x300954_g_MissionItemTable[rnd].itemId, 1) == 0 then
			Msg2Player(sceneId, selfId, "提交物品失败。", 8, 2)
			Msg2Player(sceneId, selfId, "提交物品失败", 8, 3)
			return
		end 

        x300954_SetDayCount(sceneId, selfId)

        DelQuest(sceneId, selfId, x300954_g_MissionId)
        Msg2Player(sceneId, selfId, "您完成了任务:"..x300954_g_MissionName, 8, 3)
        Msg2Player(sceneId, selfId, "您完成了任务:"..x300954_g_MissionName, 8, 2)
       
		local mutli = 1
		-- if CountryIsFortuneTime(sceneId,selfId,0)==1 then -- 国运令
			-- mutli = mutli+1
		-- end
		
		-- if CountryIsFortuneTime(sceneId,selfId,1)==1 then -- 出国令
			-- mutli = mutli+1
		-- end
		
		--奖励图腾经验
		local nGuildID = GetSceneLairdGuildId(x300954_g_LairdMap)
		if nGuildID < 0 then
			--帮会无效
			return
		end
		
		local nLairdLevel = GetSceneLairdLevel(x300954_g_LairdMap)
		
        local level = GetLevel(sceneId, selfId)
        if x300954_g_CoffExp > 0 then
			local xp = level * x300954_g_CoffExp*mutli*nLairdLevel
			AddExp(sceneId, selfId, xp)
			Msg2Player(sceneId, selfId, format( "获得#R经验%d点#cffcf00的奖励", xp), 8, 2)
			Msg2Player(sceneId, selfId, format( "获得#R经验%d点#cffcf00的奖励", xp), 8, 3)
        end
        
        if level >= 80 then
			local refixInh = floor(AddInherenceExp(sceneId, selfId, 2.5*level*mutli))
			local msg = format("你获得了%d点天赋值。",refixInh)
			Msg2Player(sceneId, selfId, msg, 8, 2)
			Msg2Player(sceneId, selfId, msg, 8, 3)
        end
        
		if nLairdLevel > 5 then
			--等级已满,不能再加成了
			return
		end
		
		local nCurLairdExp = GetGuildParam(nGuildID,GD_GUILD_LAIRDBATTLE_CURRENT_EXP) + 1
		SetGuildParam(nGuildID,GD_GUILD_LAIRDBATTLE_CURRENT_EXP,nCurLairdExp)
		
		local nLevelup = 0
		
		--等级没有满,加成经验
		if nLairdLevel == 1 and nCurLairdExp >= 10500 then
			SetSceneLairdLevel(x300954_g_LairdMap,2)
			SetGuildParam(nGuildID,GD_GUILD_LAIRDBATTLE_CURRENT_EXP,nCurLairdExp-10500)
			nLevelup = 1
		elseif nLairdLevel == 2 and nCurLairdExp >= 11667 then
			SetSceneLairdLevel(x300954_g_LairdMap,3)
			SetGuildParam(nGuildID,GD_GUILD_LAIRDBATTLE_CURRENT_EXP,nCurLairdExp-11667)
			nLevelup = 1
		elseif nLairdLevel == 3 and nCurLairdExp >= 12834 then
			SetSceneLairdLevel(x300954_g_LairdMap,4)
			SetGuildParam(nGuildID,GD_GUILD_LAIRDBATTLE_CURRENT_EXP,nCurLairdExp-12834)
			nLevelup = 1
		elseif nLairdLevel == 4 and nCurLairdExp >= 14001 then
			SetSceneLairdLevel(x300954_g_LairdMap,5)
			SetGuildParam(nGuildID,GD_GUILD_LAIRDBATTLE_CURRENT_EXP,0)
			nLevelup = 1
		end
		
		--升级会触发的一些事件
		if nLevelup == 1 then
		
			--触发当前场景天变
			CreateMonster(sceneId, 3059, 36, 166, 24, -1, -1, -1, 21, -1, 0, "", "" )
			
			--触发王国暗道天变
			GameBattleLairdLevelupEvent(x300954_g_LairdMap)
			
			--提示
			local strSceneName = GetSceneInfo(sceneId,"NAME")
			local strLevelMsg = format("%s图腾升为%d级，触发天变，附近出现天龙之魂。",strSceneName,(nLairdLevel + 1) )			
			
			LuaAllScenceM2Wrold(sceneId,strLevelMsg,CHAT_PLANE_SCROLL,1)
			LuaAllScenceM2Wrold(sceneId,strLevelMsg,CHAT_LEFTDOWN,1)
			LuaAllScenceM2Wrold(sceneId,strLevelMsg,CHAT_MAIN_RIGHTDOWN,1)
			
		end
	
    else
		-- 时间检查
        local nowTime = GetMinOfDay()
        if nowTime < x300954_g_OpenTime or nowTime >= x300954_g_EndTime then
            Msg2Player( sceneId, selfId, "只有在每日的#G9：00--23：00#cffcf00内才可领取任务", 8, 2)
            Msg2Player( sceneId, selfId, "只有在每日的#G9：00--23：00#cffcf00内才可领取任务", 8, 3)
            return
        end
        
        if GetLevel( sceneId, selfId) < x300954_g_LevelLess then
			Msg2Player( sceneId, selfId, format("很抱歉，您的等级不足%d级，无法接受【国家】图腾进贡任务。", x300954_g_LevelLess), 8, 3)
			return
		end
		
        local country = GetCurCountry(sceneId, selfId)
		local nLairdCountry = GetSceneLairdCountryId(x300954_g_LairdMap)
		if nLairdCountry ~= country then
			Msg2Player( sceneId, selfId, "没有领地", 8, 3)
			return
		end
        
		if x300954_GetDayCount(sceneId, selfId) == 0 then
			Msg2Player( sceneId, selfId, "同一块领地一天只能完成"..x300954_g_MaxCount.."次任务", 8, 3)
            return
		end
		
		local ret = AddQuest( sceneId, selfId, x300954_g_MissionId, x300954_g_ScriptId, 0, 0, 1, 0) -- 给玩家添加任务
		if ret == 0 then
			Msg2Player(sceneId,selfId, "任务已满，任务接受失败！",8,3)
			return
		end
		
		-- 显示任务接受信息
		Msg2Player( sceneId, selfId, "您获得了任务："..x300954_g_MissionName, 8, 3)
		Msg2Player( sceneId, selfId, "您获得了任务："..x300954_g_MissionName, 8, 2)
		
		x300954_SetSaveItem(sceneId, selfId)
		local rnd = x300954_g_SaveItem
	
		local misIndex = GetQuestIndexByID( sceneId, selfId, x300954_g_MissionId)
			
		local count = GetItemCountInBag(sceneId, selfId, x300954_g_MissionItemTable[rnd].itemId)

		SetQuestByIndex( sceneId, selfId, misIndex, 7, count >= x300954_g_MissionItemTable[rnd].count and 1 or 0)
		SetQuestByIndex( sceneId, selfId, misIndex, 0, count >= x300954_g_MissionItemTable[rnd].count and 1 or 0)
		SetQuestByIndex( sceneId, selfId, misIndex, 1, rnd)
		
		-- 更新任务跟踪和Q面板
		x300954_ProcQuestLogRefresh( sceneId, selfId, x300954_g_MissionId)
		return 1
    end
end

---------------------------------------------------------------------------------------------------
--放弃任务
---------------------------------------------------------------------------------------------------
function x300954_ProcQuestAbandon( sceneId, selfId, MissionId)
	if IsHaveQuest( sceneId, selfId, x300954_g_MissionId) > 0 then
		DelQuest( sceneId, selfId, x300954_g_MissionId)
        x300954_SetDayCount(sceneId, selfId)
		Msg2Player( sceneId, selfId, "很抱歉，您放弃了任务："..x300954_g_MissionName, 8, 3)
		Msg2Player( sceneId, selfId, "很抱歉，您放弃了任务："..x300954_g_MissionName, 8, 2)
	end
end

---------------------------------------------------------------------------------------------------
--提交任务，不管任务是否完成或是任务，显示任务继续信息或是任务完成信息
---------------------------------------------------------------------------------------------------
function x300954_ProcQuestSubmit( sceneId, selfId, targetId, selectRadioId, MissionId)
end

function x300954_BonusInfo(sceneId, selfId)
	local mutli = 1
	-- if CountryIsFortuneTime(sceneId,selfId,0)==1 then -- 国运令
		-- mutli = mutli+1
	-- end
	
	-- if CountryIsFortuneTime(sceneId,selfId,1)==1 then -- 出国令
		-- mutli = mutli+1
	-- end
	
	local level = GetLevel(sceneId, selfId)
	
	--奖励图腾经验
	local nGuildID = GetSceneLairdGuildId(x300954_g_LairdMap)
	if nGuildID < 0 then
		--帮会无效
		return
	end
	
	local nLairdLevel = GetSceneLairdLevel(x300954_g_LairdMap)

    --任务奖励信息
    if x300954_g_CoffExp > 0 then
		local exp = level * x300954_g_CoffExp*mutli*nLairdLevel
        AddQuestExpBonus(sceneId, exp)
    end
	if level >= 80 then
		local refixInhExp = floor(RefixInherenceExp(sceneId, selfId, 2.5*level*mutli))
		AddQuestInherenceExpBonus(sceneId,refixInhExp)
	end
	
end

---------------------------------------------------------------------------------------------------
--向客户端发送任务信息
---------------------------------------------------------------------------------------------------
function x300954_DispatchMissionInfo( sceneId, selfId, targetId)
	BeginQuestEvent( sceneId)

    --任务信息
    AddQuestText( sceneId, "#Y"..x300954_g_MissionName)
    AddQuestText( sceneId, x300954_g_MissionInfo)
    AddQuestText( sceneId, " ")
	
	x300954_SetSaveItem(sceneId, selfId)
	local rnd = x300954_g_SaveItem

	local misIndex = GetQuestIndexByID( sceneId, selfId, x300954_g_MissionId)
	
	local count = GetItemCountInBag(sceneId, selfId, x300954_g_MissionItemTable[rnd].itemId)
	if count > x300954_g_MissionItemTable[rnd].count then
		count = x300954_g_MissionItemTable[rnd].count
	end
	AddQuestText( sceneId,"#Y任务目标：")
    AddQuestText( sceneId, format(x300954_g_MissionTarget, x300954_g_MissionItemTable[rnd].itemId, 
								count, x300954_g_MissionItemTable[rnd].count))
	AddQuestText( sceneId, " ")
	AddQuestText(sceneId,"#Y任务提示：")
    AddQuestText( sceneId, format(x300954_g_MissionHelp, x300954_g_MissionItemTable[rnd].itemId))
    AddQuestText( sceneId, " ")
							
    x300954_BonusInfo(sceneId, selfId)
   
	EndQuestEvent()
	DispatchQuestInfoNM( sceneId, selfId, targetId, x300954_g_ScriptId, x300954_g_MissionId)
end

---------------------------------------------------------------------------------------------------
--向客户端发送任务未完成
---------------------------------------------------------------------------------------------------
function x300954_DispatchContinueInfo( sceneId, selfId, targetId)
	local misIndex = GetQuestIndexByID( sceneId, selfId, x300954_g_MissionId)
	local rnd = GetQuestParam( sceneId, selfId, misIndex, 1)
		
	BeginQuestEvent( sceneId)
    AddQuestText( sceneId, "#Y"..x300954_g_MissionName)
    AddQuestText( sceneId, format(x300954_g_ContinueInfo, x300954_g_MissionItemTable[rnd].itemId))
    AddQuestText( sceneId, " ")
	
	if IsHaveQuest(sceneId, selfId, x300954_g_MissionId) > 0 then

		AddQuestText( sceneId,"#Y完成情况：")
		local misIndex = GetQuestIndexByID( sceneId, selfId, x300954_g_MissionId)
		if GetQuestParam( sceneId, selfId, misIndex, 7) == 0 then
			AddQuestText(sceneId, "未完成")
		else
			AddQuestText(sceneId, "已完成")
		end
	    x300954_BonusInfo(sceneId, selfId)
    end
    
	EndQuestEvent()
    DispatchQuestDemandInfo( sceneId, selfId, targetId, x300954_g_ScriptId, x300954_g_MissionId,0)
end

---------------------------------------------------------------------------------------------------
--向客户端发送任务完成信息
---------------------------------------------------------------------------------------------------
function x300954_DispatchCompletedInfo( sceneId, selfId, targetId)
	BeginQuestEvent( sceneId)
    AddQuestText( sceneId, "#Y"..x300954_g_MissionName)
    AddQuestText( sceneId, x300954_g_MissionCompleted)
    AddQuestText( sceneId, " ")
    
    x300954_BonusInfo(sceneId, selfId)
    
	EndQuestEvent()
	DispatchQuestInfoNM( sceneId, selfId, targetId, x300954_g_ScriptId, x300954_g_MissionId)

end

---------------------------------------------------------------------------------------------------
--怪物被杀的消息处理
---------------------------------------------------------------------------------------------------
function x300954_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId)
end

---------------------------------------------------------------------------------------------------
--物品改变
---------------------------------------------------------------------------------------------------
function x300954_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId)
	
	if IsHaveQuest( sceneId, selfId, x300954_g_MissionId) > 0 then
		local misIndex = GetQuestIndexByID( sceneId, selfId, x300954_g_MissionId)
		local rnd = GetQuestParam( sceneId, selfId, misIndex, 1)
		local count = GetItemCountInBag(sceneId, selfId, x300954_g_MissionItemTable[rnd].itemId)
		SetQuestByIndex( sceneId, selfId, misIndex, 7, count >= x300954_g_MissionItemTable[rnd].count and 1 or 0)
		SetQuestByIndex( sceneId, selfId, misIndex, 0, count >= x300954_g_MissionItemTable[rnd].count and 1 or 0)
		
		x300954_ProcQuestLogRefresh( sceneId, selfId, x300954_g_MissionId)
	end
end

---------------------------------------------------------------------------------------------------
--单击NPC事件
---------------------------------------------------------------------------------------------------
function x300954_ProcQuestAttach( sceneId, selfId, targetId, npcGuid, misIndex, MissionId)
	if IsHaveQuestNM( sceneId, selfId, x300954_g_MissionId) == 0 then	-- 如果没有这个任务
		return
	end
end

---------------------------------------------------------------------------------------------------
--取得当前次数
---------------------------------------------------------------------------------------------------
function x300954_GetDayCount(sceneId, selfId)

	local today = GetDayOfYear()
	local lastday = GetQuestData(sceneId, selfId, MD_LINGDIJINGONG_5_DATE[1], MD_LINGDIJINGONG_5_DATE[2],MD_LINGDIJINGONG_5_DATE[3])
	
	if today ~= lastday then
		return 1
	end
		
	local daycount = GetQuestData(sceneId, selfId, MD_LINGDIJINGONG_5_DAYCOUNT[1], MD_LINGDIJINGONG_5_DAYCOUNT[2],MD_LINGDIJINGONG_5_DAYCOUNT[3])
	return daycount < x300954_g_MaxCount and 1 or 0
end

---------------------------------------------------------------------------------------------------
--设置当天次数
---------------------------------------------------------------------------------------------------
function x300954_SetDayCount(sceneId, selfId)
	local today = GetDayOfYear()
	local lastday = GetQuestData(sceneId, selfId, MD_LINGDIJINGONG_5_DATE[1], MD_LINGDIJINGONG_5_DATE[2],MD_LINGDIJINGONG_5_DATE[3])

	if today ~= lastday then
		SetQuestData(sceneId, selfId, MD_LINGDIJINGONG_5_DATE[1], MD_LINGDIJINGONG_5_DATE[2], MD_LINGDIJINGONG_5_DATE[3], today)
		SetQuestData(sceneId, selfId, MD_LINGDIJINGONG_5_DAYCOUNT[1], MD_LINGDIJINGONG_5_DAYCOUNT[2], MD_LINGDIJINGONG_5_DAYCOUNT[3], 1)
	else
		local count = GetQuestData(sceneId, selfId, MD_LINGDIJINGONG_5_DAYCOUNT[1], MD_LINGDIJINGONG_5_DAYCOUNT[2],MD_LINGDIJINGONG_5_DAYCOUNT[3])
		SetQuestData(sceneId, selfId, MD_LINGDIJINGONG_5_DAYCOUNT[1], MD_LINGDIJINGONG_5_DAYCOUNT[2], MD_LINGDIJINGONG_5_DAYCOUNT[3], count+1)
	end
end

function x300954_SetSaveItem(sceneId, selfId)
	if x300954_g_SaveItem == -1 then
		x300954_g_SaveItem = random(1, getn(x300954_g_MissionItemTable))
		if x300954_g_SaveItem < 1 then x300954_g_SaveItem = 1 end
		if x300954_g_SaveItem > getn(x300954_g_MissionItemTable) then x300954_g_SaveItem = getn(x300954_g_MissionItemTable) end
		x300954_g_SaveItemDay = GetDayOfYear()
	elseif x300954_g_SaveItemDay == -1 or x300954_g_SaveItemDay ~= GetDayOfYear() then
		x300954_g_SaveItem = random(1, getn(x300954_g_MissionItemTable))
		if x300954_g_SaveItem < 1 then x300954_g_SaveItem = 1 end
		if x300954_g_SaveItem > getn(x300954_g_MissionItemTable) then x300954_g_SaveItem = getn(x300954_g_MissionItemTable) end
		x300954_g_SaveItemDay = GetDayOfYear()
	end
end
---------------------------------------------------------------------------------------------------
--任务日志刷新
---------------------------------------------------------------------------------------------------
function x300954_ProcQuestLogRefresh( sceneId, selfId, MissionId)
    
    local misIndex = GetQuestIndexByID( sceneId, selfId, x300954_g_MissionId)
    local rnd = GetQuestParam( sceneId, selfId, misIndex, 1)
	local count = GetItemCountInBag(sceneId, selfId, x300954_g_MissionItemTable[rnd].itemId)
	if count > x300954_g_MissionItemTable[rnd].count then
		count = x300954_g_MissionItemTable[rnd].count
	end
	
	BeginQuestEvent( sceneId)
    AddQuestLogCustomText( sceneId,
							"",									-- 标题
                            x300954_g_MissionName,              -- 任务名字
                            format(x300954_g_MissionTarget, x300954_g_MissionItemTable[rnd].itemId, 
								count, x300954_g_MissionItemTable[rnd].count),            --任务目标
                            "@npc_"..x300954_g_TargetNPC,       --任务NPC
                             format(x300954_g_Missionruse,x300954_g_MissionItemTable[rnd].itemId), 				--任务攻略
                            x300954_g_MissionInfo,              --任务描述
                            x300954_g_MissionHelp			--任务小提示
                            )
                            
    x300954_BonusInfo(sceneId, selfId)
    
	EndQuestEvent()
	DispatchQuestLogUpdate( sceneId, selfId, MissionId)
end