-- 皇帝密令
--MisDescBegin

x300971_g_ScriptId 					= 300971                  --脚本ID
x300971_g_MissionId 				= 7790                    --任务ID

x300971_g_MissionKind 				= 1                       --任务类型
x300971_g_LevelLess					= 80                      --场景开放等级  <=0 表示不限制

x300971_g_MissionName				= "【国家】皇帝密令"
x300971_g_MissionTarget				= "  到中兴府收集@npc_31131(%d/%d)"      --任务目标
x300971_g_MissionInfo				= "\t各国使者现已在中兴府等候，今使者们带来各国贡品寡人有意将赏赐予你们。这批资源极为重要，有助于你们国力强盛，所以其他三国也对这批外藩贡品虎视眈眈，不要耽误，即刻启程拿取各国贡品！"      --任务信息
x300971_g_ContinueInfo				= "\t不要耽误，即刻启程拿取各国贡品！"	  --任务继续信息
x300971_g_MissionCompleted			= "你为你们国家及帮会的强盛做出了卓越贡献!"	  --任务完成信息
x300971_g_MissionHelp				= "\t贡品在野外场景中兴府城内，各国力量均会抢夺该批贡品!"      --任务提示信息
x300971_g_Missionruse				= "\t每得到一批贡品都会有大量经验奖励，更有可能获得额外高经验奖励。"      --任务攻略

--目标
x300971_g_ExtTarget					= { {type=20,n=1,target=""} }


--奖励
x300971_g_ExpBonus					= 0     --奖励：经验 （数值填0，字符串为空，表示没有该项奖励）
x300971_g_BonusItem					= {}	--奖励：物品

x300971_g_BonusMoney1               = 0  --任务奖励绑定银币
x300971_g_BonusMoney2               = 0  --任务奖励非绑定银币
x300971_g_BonusMoney3               = 0  --任务奖励绑定金币
x300971_g_BonusMoney4               = 0  --任务奖励朝廷声望
x300971_g_BonusMoney5               = 0  --任务奖励江湖声望
x300971_g_BonusMoney6               = 0  --任务奖励荣誉

x300971_g_BonusChoiceItem           = {}

--MisDescEnd

x300971_g_GrowpointId				= 135 --对应生长点ID
x300971_g_Boss						= {type =9880,guid =-1,x = 128, z=128, facedir =3600000, title = ""}

x300971_g_CoffExp					= {120000, 12000, 2400, 1200} -- 采集时经验
x300971_g_InherenceExp				= 770 -- 任务天赋经验奖励
x300971_g_GuildMoney				= 100000 -- 任务帮会金钱奖励
x300971_g_MaxCount					= 5 -- 一共能采集多少次
-- 交任务NPC
x300971_g_TargetNPC                 = 139264

---------------------------------------------------------------------------------------------------
--列举事件
---------------------------------------------------------------------------------------------------
function x300971_ProcEnumEvent(sceneId, selfId, targetId, MissionId)

	local state = GetQuestStateNM(sceneId, selfId, targetId, x300971_g_MissionId)
	AddQuestNumText(sceneId,x300971_g_MissionId,x300971_g_MissionName,state, 0 )
end
---------------------------------------------------------------------------------------------------
--任务入口函数
---------------------------------------------------------------------------------------------------
function x300971_ProcEventEntry(sceneId, selfId, targetId, MissionId, nExtIdx)
	if IsHaveQuest( sceneId, selfId, x300971_g_MissionId) > 0 then
		local misIndex = GetQuestIndexByID( sceneId, selfId, x300971_g_MissionId)
		if GetQuestParam( sceneId, selfId, misIndex, 7) == 0 then
			x300971_DispatchContinueInfo(sceneId, selfId, targetId) --未完成任务显示
        else
            x300971_DispatchCompletedInfo(sceneId, selfId, targetId) --完成任务显示
        end
    else
		x300971_DispatchMissionInfo(sceneId, selfId, targetId)	--任务信息显示
	end
end

---------------------------------------------------------------------------------------------------
--检测接受条件
---------------------------------------------------------------------------------------------------
function x300971_ProcAcceptCheck(sceneId, selfId, targetId)
	local bHaveMission	= IsHaveQuest(sceneId, selfId, x300971_g_MissionId)
	if( bHaveMission > 0) then
		return 0
	else
		return 1
	end
end

---------------------------------------------------------------------------------------------------
--接受条件
---------------------------------------------------------------------------------------------------
function x300971_ProcQuestAccept(sceneId, selfId, targetId, missionId)

    if IsHaveQuest(sceneId, selfId, x300971_g_MissionId) > 0 then
		local misIndex = GetQuestIndexByID(sceneId, selfId, x300971_g_MissionId)
		local count = GetQuestParam( sceneId, selfId, misIndex, 0)
        if GetQuestParam( sceneId, selfId, misIndex, 7) ~= 1 then
			Msg2Player(sceneId, selfId, "任务为未完成状态。", 8, 2)
			Msg2Player(sceneId, selfId, "任务为未完成状态", 8, 3)
			return
		end 

        x300971_SetDayCount(sceneId, selfId)

        DelQuest(sceneId, selfId, x300971_g_MissionId)
        Msg2Player(sceneId, selfId, "您完成了任务:"..x300971_g_MissionName, 8, 3)
        Msg2Player(sceneId, selfId, "您完成了任务:"..x300971_g_MissionName, 8, 2)
        
        AddGuildMoney(sceneId, selfId, x300971_g_GuildMoney)
        Msg2Player(sceneId, selfId, "获得#R帮会金钱100两#cffcf00的奖励", 8, 2)
		Msg2Player(sceneId, selfId, "获得#R帮会金钱100两#cffcf00的奖励", 8, 3)
	 	

		
        local level = GetLevel(sceneId, selfId)
        if level >= 80 then
			local refixInh = AddInherenceExp(sceneId, selfId, x300971_g_InherenceExp)
			local msg = format("获得#R天赋值%d点#cffcf00的奖励。",refixInh)
			Msg2Player(sceneId, selfId, msg, 8, 2)
			Msg2Player(sceneId, selfId, msg, 8, 3)
        end
    else
		if GetLevel( sceneId, selfId) < x300971_g_LevelLess then
			Msg2Player( sceneId, selfId, format("很抱歉，您的等级不足%d级，无法接受【国家】皇帝密令。", x300971_g_LevelLess), 8, 3)
			return
		end
		
		if GetGuildID( sceneId, selfId ) == -1 then
	 		--不在帮会中
			Msg2Player(sceneId, selfId, "很抱歉，没有帮会无法接受任务！", 8, 2)
			Msg2Player(sceneId, selfId, "很抱歉，没有帮会无法接受任务！", 8, 3)
			return
		end 

		if x300971_GetDayCount(sceneId, selfId) == 0 then
			Msg2Player( sceneId, selfId, "你今天领取过该任务，请明天再来吧！", 8, 3)
			return
		end
		
		local ret = AddQuest( sceneId, selfId, x300971_g_MissionId, x300971_g_ScriptId, 0, 0, 0, 0) -- 给玩家添加任务
		if ret == 0 then
			Msg2Player(sceneId,selfId, "任务已满，任务接受失败！",8,3)
			return
		end
		
		-- 显示任务接受信息
		Msg2Player( sceneId, selfId, "您获得了任务："..x300971_g_MissionName, 8, 3)
		Msg2Player( sceneId, selfId, "您获得了任务："..x300971_g_MissionName, 8, 2)
		
	
		local misIndex = GetQuestIndexByID( sceneId, selfId, x300971_g_MissionId)
		SetQuestByIndex( sceneId, selfId, misIndex, 7, 0)
		SetQuestByIndex( sceneId, selfId, misIndex, 0, 0)
		
		-- 更新任务跟踪和Q面板
		x300971_ProcQuestLogRefresh( sceneId, selfId, x300971_g_MissionId)
		return 1
    end
end

---------------------------------------------------------------------------------------------------
--放弃任务
---------------------------------------------------------------------------------------------------
function x300971_ProcQuestAbandon( sceneId, selfId, MissionId)
	if IsHaveQuest( sceneId, selfId, x300971_g_MissionId) > 0 then
		DelQuest( sceneId, selfId, x300971_g_MissionId)
        x300971_SetDayCount(sceneId, selfId)
		Msg2Player( sceneId, selfId, "您放弃了任务："..x300971_g_MissionName, 8, 3)
		Msg2Player( sceneId, selfId, "您放弃了任务："..x300971_g_MissionName, 8, 2)
	end
end

---------------------------------------------------------------------------------------------------
--提交任务，不管任务是否完成或是任务，显示任务继续信息或是任务完成信息
---------------------------------------------------------------------------------------------------
function x300971_ProcQuestSubmit( sceneId, selfId, targetId, selectRadioId, MissionId)
end

function x300971_BonusInfo(sceneId, selfId)

	local level = GetLevel(sceneId, selfId)

    --任务奖励信息
    AddQuestGuildMoneyBonus(sceneId, x300971_g_GuildMoney)
    
	if level >= 80 then
		local refixInhExp = RefixInherenceExp(sceneId, selfId, x300971_g_InherenceExp)
		AddQuestInherenceExpBonus(sceneId,refixInhExp)
	end
end

---------------------------------------------------------------------------------------------------
--向客户端发送任务信息
---------------------------------------------------------------------------------------------------
function x300971_DispatchMissionInfo( sceneId, selfId, targetId)
	BeginQuestEvent( sceneId)

    --任务信息
    AddQuestText( sceneId, "#Y"..x300971_g_MissionName)
    AddQuestText( sceneId, x300971_g_MissionInfo)
    AddQuestText( sceneId, " ")

	local misIndex = GetQuestIndexByID( sceneId, selfId, x300971_g_MissionId)
	local count = GetQuestParam( sceneId, selfId, misIndex, 0)
	
	AddQuestText( sceneId,"#Y任务目标：")
    AddQuestText( sceneId, format(x300971_g_MissionTarget, count, x300971_g_MaxCount))
	AddQuestText( sceneId, " ")
	AddQuestText(sceneId,"#Y任务提示：")
    AddQuestText( sceneId, format(x300971_g_MissionHelp))
    AddQuestText( sceneId, " ")
							
    x300971_BonusInfo(sceneId, selfId)
	EndQuestEvent()
	DispatchQuestInfoNM( sceneId, selfId, targetId, x300971_g_ScriptId, x300971_g_MissionId)
end

---------------------------------------------------------------------------------------------------
--向客户端发送任务未完成
---------------------------------------------------------------------------------------------------
function x300971_DispatchContinueInfo( sceneId, selfId, targetId)
	local misIndex = GetQuestIndexByID( sceneId, selfId, x300971_g_MissionId)
	local rnd = GetQuestParam( sceneId, selfId, misIndex, 1)
		
	BeginQuestEvent( sceneId)
    AddQuestText( sceneId, "#Y"..x300971_g_MissionName)
    AddQuestText( sceneId, format(x300971_g_ContinueInfo, x300971_g_TargetNPC))
	AddQuestText( sceneId, " ")
	
	AddQuestText( sceneId,"#Y完成情况：")
	local misIndex = GetQuestIndexByID( sceneId, selfId, x300971_g_MissionId)
	if GetQuestParam( sceneId, selfId, misIndex, 7) == 0 then
		AddQuestText(sceneId, "未完成")
	else
		AddQuestText(sceneId, "已完成")
	end
	
	x300971_BonusInfo(sceneId, selfId)
    
	EndQuestEvent()
    DispatchQuestDemandInfo( sceneId, selfId, targetId, x300971_g_ScriptId, x300971_g_MissionId,0)
end

---------------------------------------------------------------------------------------------------
--向客户端发送任务完成信息
---------------------------------------------------------------------------------------------------
function x300971_DispatchCompletedInfo( sceneId, selfId, targetId)
	BeginQuestEvent( sceneId)
    AddQuestText( sceneId, "#Y"..x300971_g_MissionName)
    AddQuestText( sceneId, x300971_g_MissionCompleted)
    AddQuestText( sceneId, " ")
    
    x300971_BonusInfo(sceneId, selfId)
    
	EndQuestEvent()
	DispatchQuestInfoNM( sceneId, selfId, targetId, x300971_g_ScriptId, x300971_g_MissionId)
end

---------------------------------------------------------------------------------------------------
--怪物被杀的消息处理
---------------------------------------------------------------------------------------------------
function x300971_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId)
end

---------------------------------------------------------------------------------------------------
--物品改变
---------------------------------------------------------------------------------------------------
function x300971_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId)
end

---------------------------------------------------------------------------------------------------
--单击NPC事件
---------------------------------------------------------------------------------------------------
function x300971_ProcQuestAttach( sceneId, selfId, targetId, npcGuid, misIndex, MissionId)
end

---------------------------------------------------------------------------------------------------
--取得当前次数
---------------------------------------------------------------------------------------------------
function x300971_GetDayCount(sceneId, selfId)

	local today = GetDayOfYear()
	local lastday = GetQuestData(sceneId, selfId, MD_HUANGDIMILING_DATE[1], MD_HUANGDIMILING_DATE[2],MD_HUANGDIMILING_DATE[3])
	
	if today ~= lastday then
		return 1
	end
		
	return 0
end

---------------------------------------------------------------------------------------------------
--设置当天次数
---------------------------------------------------------------------------------------------------
function x300971_SetDayCount(sceneId, selfId)
	local today = GetDayOfYear()
	SetQuestData(sceneId, selfId, MD_HUANGDIMILING_DATE[1], MD_HUANGDIMILING_DATE[2], MD_HUANGDIMILING_DATE[3], today)
end

---------------------------------------------------------------------------------------------------
--任务日志刷新
---------------------------------------------------------------------------------------------------
function x300971_ProcQuestLogRefresh( sceneId, selfId, MissionId)
    
    local misIndex = GetQuestIndexByID( sceneId, selfId, x300971_g_MissionId)
    local count = GetQuestParam( sceneId, selfId, misIndex, 0)
    
	BeginQuestEvent( sceneId)
    AddQuestLogCustomText( sceneId,
							"",									-- 标题
                            x300971_g_MissionName,              -- 任务名字
                            format(x300971_g_MissionTarget, count, x300971_g_MaxCount),            --任务目标
                            "@npc_"..x300971_g_TargetNPC,       --任务NPC
                            format(x300971_g_Missionruse,x300971_g_TargetNPC), 				--任务攻略
                            x300971_g_MissionInfo,              --任务描述
                            x300971_g_MissionHelp			--任务小提示
                            )
                            
    x300971_BonusInfo(sceneId, selfId)
    
	EndQuestEvent()
	DispatchQuestLogUpdate( sceneId, selfId, MissionId)
end

--生成函数开始
function x300971_OnCreate(sceneId,growPointType,x,y)
	local ItemBoxId = ItemBoxEnterScene(x, y, x300971_g_GrowpointId, sceneId, 0, -1)
end

--采集任务
function x300971_OnOpen( sceneId, selfId, targetId, gpType, needItemID)
    if IsHaveQuestNM( sceneId, selfId, x300971_g_MissionId) > 0 then
		local misIndex = GetQuestIndexByID( sceneId, selfId, x300971_g_MissionId)
		local count = GetQuestParam( sceneId, selfId, misIndex, 0)
		if count == x300971_g_MaxCount then
			Msg2Player( sceneId, selfId, "每个人每天只允许收集5份贡品,明天再来吧", 8, 3)
			return 1
		end
		return 0
    end
        Msg2Player( sceneId, selfId, "很抱歉，你没有【国家】皇帝密令任务，无法采集", 8, 3)
    return 1
end

--打开
function x300971_OnProcOver( sceneId, selfId, targetId )
end

--回收
function x300971_OnRecycle( sceneId, selfId, targetId, gpType, needItemID)

    if IsHaveQuestNM( sceneId, selfId, x300971_g_MissionId) > 0 then
		local misIndex = GetQuestIndexByID( sceneId, selfId, x300971_g_MissionId)
		local count = GetQuestParam( sceneId, selfId, misIndex, 0)

		SetQuestByIndex( sceneId, selfId, misIndex, 0, count+1)
		if count+1 == x300971_g_MaxCount then
			SetQuestByIndex( sceneId, selfId, misIndex, 7, 1)
		end
		
		local level = GetLevel(sceneId, selfId)
		local rnd = random(1, 1000)
        local xp = 0
        if rnd == 1 then
			xp = level * x300971_g_CoffExp[1]
			if x300971_g_Boss.title~= "" then
				CreateMonster(sceneId, x300971_g_Boss.type, x300971_g_Boss.x, x300971_g_Boss.z, 1, 977, -1, x300971_g_Boss.guid, 21,-1,x300971_g_Boss.facedir, "", x300971_g_Boss.title)
			else
				CreateMonster(sceneId, x300971_g_Boss.type, x300971_g_Boss.x, x300971_g_Boss.z, 1, 977, -1, x300971_g_Boss.guid, 21,-1,x300971_g_Boss.facedir)
			end
			local killerName = GetName(sceneId,selfId)
			local msg1 = format("%s收集到稀有的外藩贡品，武仙突袭中兴府抢夺贡品资源！",killerName)
			LuaAllScenceM2Wrold(sceneId, msg1, CHAT_PLANE_SCROLL, 1)
			LuaAllScenceM2Wrold(sceneId, msg1, CHAT_LEFTDOWN, 1)
			LuaAllScenceM2Wrold(sceneId, msg1, CHAT_MAIN_RIGHTDOWN, 1)
		elseif rnd <= 101 then
			xp = level * x300971_g_CoffExp[2]
		elseif rnd <= 501 then
			xp = level * x300971_g_CoffExp[3]
		else
			xp = level * x300971_g_CoffExp[4]
		end
		AddExp(sceneId, selfId, xp);
		Msg2Player(sceneId, selfId, format( "收集外藩贡品获得#R经验%d点#cffcf00的奖励", xp), 8, 2)
		Msg2Player(sceneId, selfId, format( "收集外藩贡品获得#R经验%d点#cffcf00的奖励", xp), 8, 3)
	
		x300971_ProcQuestLogRefresh( sceneId, selfId, x300971_g_MissionId)
		return 1
    end

    return 0
end

function x300971_OnDie(sceneId, selfId, killerId)

end
	