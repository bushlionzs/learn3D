-- 征税任务说明
x300100_g_MissionCommentId			= 1101
-- 玩家接受任务所需的最小等级
x300100_g_LevelLess            = 25
-- x300100_g_MISSION_LIST_LENGTH = 20
-- x300100_g_MissionIDCountryPlus	= 0
-- x300100_g_MissionReturnId				= 6520
-- 脚本Id
x300100_g_ScriptId = 300100
-- 任务ID
x300100_g_MissionId = 6500
-- 任务名称
x300100_g_MissionName = "【个人】征税权"
-- 征税任务说明文字
x300100_g_MissionCommentMessage	= "\t本任务为#G25级#W以上的玩家开放，每天可以完成#G10次#W，#R前5次将获得多倍奖励#W。\n\t点选任务按钮后你将获得向指定商人征税的权力，前往三名指定商人征税后回来向我报道，即可获得你应得的奖励。\n\t当然，并不是每个商人都在附近，也有可能是云游在外的行商，但您最好#G不要放弃任务#W，否则将会受到惩罚。当你每日完成5次任务时，本国还将#G增长1两的国库金钱储备#W，以及你将获得一些#G额外奖励#W，感谢你对国家的贡献！"
-- 处于惩罚时间内接受任务失败提示
x300100_g_strInPunishTime       = "你放弃任务不足5分钟，不能接受本任务"
-- 任务描述文字表
x300100_g_MissionInfoTable      = {
                                    "\t@npc_%d、@npc_%d和@npc_%d长期以各种理由拖欠税资，我觉得以你的才干一定能够胜任这份工作，去帮我收回他拖欠的税款，我会给你相应的报酬。", 
                                    "\t@npc_%d、@npc_%d和@npc_%d长期偷税漏税，我们的税差去了几次都没有收到税金，大家都说你对付这一类人很有一套，看来这次要拜托你了。", 
                                    "\t最近我的几个手下都病倒了，很多人的税金都没有及时收缴上来，我想请你帮我征收@npc_%d、@npc_%d和@npc_%d的税金"
}
-- 任务描述
x300100_g_MissionInfo           = "\t@npc_%d、@npc_%d和@npc_%d长期偷税漏税、违法经营，拜托你代我去收回欠税吧，我不会忘记给你好处的！"
-- 任务回复NPC
x300100_g_MissionReply          = "@npc_138523"
x300100_g_MissionReplyGuid      = 138523
-- 交任务NPC文字
x300100_g_strFinish             = "\t交给你的事情都办完了？"
-- 任务目标
x300100_g_MissionTarget			=	"  向@npc_%d征税(%d/1)"
-- 小提示
x300100_g_MissionHelp           = "#G每天的前5次任务，可以获得多倍奖励"
-- 最大奖励等级，任务奖励与等级成正比，大于这个等级的玩家与此等级奖励一样
x300100_g_MaxLevel              = 80
-- 高奖系数，高奖状态下完成任务用这个系数乘以此系数
x300100_g_HighCofficient        = 75
-- 征税人数
x300100_g_TargetCount           = 3
-- 低奖系数，低奖状态下完成任务用这个系数乘以此系数
x300100_g_LowCofficient         = 15
x300100_g_FinishOne             = "你已完成向@npc_%s的征税（%d/3）"
-- 为了节省MD，要在MP中保存更多的数据，就是把征税任务NPC的Id和是否征税标记都放在MP中，具体就是用NPC的Id乘这个系数表示已经征税
x300100_g_HasTaxCoff            = 100
-- 完成征税保存的MP大于此值表示已经征过税
x300100_g_HasTaxValue           = 10000000
-- 任务完成MP索引，设置为1后任务管理器更新
x300100_g_Complete              = 7
-- 任务完成后NPC对话按钮更新MP索引，设置为1后NPC任务按钮变为黄色问号
x300100_g_ButtonNPC             = 0
-- 任务描述
x300100_g_MissionDescription    = "\t国家税收关乎国计民生，是头等的大事。虽然本官日夜奔忙，各地的偷税漏税情况却依旧严重，看来人手是实在不足了。\n\t阁下是否想为国效力，帮助我向各地的商人征税？如果你能成功完成任务，我也会给你一定的奖赏。"
-- NPC被征税文字，可以在这里添加多种，玩家看到的是随机抽取的一句
x300100_g_strNPCTax             = {
                                    "\t好吧，没想到征税官竟然找你来征税，王子都不敢怠慢你，何况是我们这些普通百姓。", 
                                    "\t啊，你就是大家都在议论的#Y@myname#W？真没想到征税官竟然请到了你，看来我那套上有八十老母下有待哺小儿的话也没有什么用了。好，我交！",
                                    "\t啊？！来了新的税官啊，我还以为可以不用交了呢！这是税款……"
}
-- 征税目标NPC列表
x300100_g_TaxTargetList         = {
                                    { npcId = 	138538	}, 
                                    { npcId = 	138539	}, 
                                    { npcId = 	138540	}, 
                                    { npcId = 	138541	}, 
                                    { npcId = 	138594	}, 
                                    { npcId = 	138545	}, 
                                    { npcId = 	138563	}, 
                                    { npcId = 	138584	}, 
                                    { npcId = 	138556	}, 
                                    { npcId = 	138500	}, 
                                    { npcId = 	138550	}, 
                                    { npcId = 	138504	}, 
                                    { npcId = 	138505	}, 
                                    { npcId = 	138506	}, 
                                    { npcId = 	138551	}, 
                                    { npcId = 	138552	}, 
                                    { npcId = 	138553	}, 
                                    { npcId = 	138554	}, 
                                    { npcId = 	138555	}, 
                                    { npcId = 	138557	}
}

x300100_g_ItemAwardCertain	= {
					{levelMin=20, levelMax=30, num=1, id={12110201}},
					{levelMin=30, levelMax=40, num=1, id={12110202}},
					{levelMin=40, levelMax=50, num=1, id={12110203}},
					{levelMin=50, levelMax=60, num=1, id={12110204}},
					{levelMin=60, levelMax=70, num=1, id={12110205}},
					{levelMin=70, levelMax=80, num=1, id={12110206}},
					{levelMin=80, levelMax=90, num=1, id={12110207}},
					{levelMin=90, levelMax=100, num=1, id={12110208}},
					{levelMin=100, levelMax=110, num=1, id={12110209}},
					{levelMin=110, levelMax=9999, num=1, id={12110210}},
}
x300100_g_MaxTimes                  = 10
x300100_g_strOverMaxTimes           = "很抱歉，您本日征税次数已经达到上限，请明日再来领取任务。"

function x300100_ProcQuestLogRefresh( sceneId, selfId, MissionId)
    local misIndex = GetQuestIndexByID( sceneId, selfId, x300100_g_MissionId)
    local mFinished = GetQuestParam( sceneId, selfId, misIndex, 7)
    local F1 = GetQuestParam( sceneId, selfId, misIndex, 1)
    if F1 > x300100_g_HasTaxValue then
        F1 = 1
    else
        F1 = 0
    end
    local F2 = GetQuestParam( sceneId, selfId, misIndex, 2)
    if F2 > x300100_g_HasTaxValue then
        F2 = 1
    else
        F2 = 0
    end
    local F3 = GetQuestParam( sceneId, selfId, misIndex, 3)
    if F3 > x300100_g_HasTaxValue then
        F3 = 1
    else
        F3 = 0
    end
    local round = x300100_GetCircle( sceneId, selfId) + 1
    if round > 5 then
        round = round - 5
    end
    local npc1, npc2, npc3 = x300100_GetNPCID( sceneId, selfId)
    local strMissionInfo = ""

    if mFinished == 0 then
    		if F1 > 0 then
    			strMissionInfo = strMissionInfo.."#G";
    		else
    			strMissionInfo = strMissionInfo.."#W";
    		end
    		strMissionInfo = strMissionInfo..format(x300100_g_MissionTarget, npc1, F1);
    		strMissionInfo = strMissionInfo.."\n"
    		
    		if F2 > 0 then
    			strMissionInfo = strMissionInfo.."#G";
    		else
    			strMissionInfo = strMissionInfo.."#W";
    		end
    		strMissionInfo = strMissionInfo..format(x300100_g_MissionTarget, npc2, F2);
    		strMissionInfo = strMissionInfo.."\n"
    		
    		if F3 > 0 then
    			strMissionInfo = strMissionInfo.."#G";
    		else
    			strMissionInfo = strMissionInfo.."#W";
    		end
    		strMissionInfo = strMissionInfo..format(x300100_g_MissionTarget, npc3, F3);
    else
        strMissionInfo = "任务已经完成，请回去向@npc_138523汇报！"
    end

    BeginQuestEvent( sceneId)
        AddQuestLogCustomText( sceneId,
                               format( "【个人】征税权(%d/5)", round),                             -- 标题
                               format( "【个人】征税权(%d/5)", round),          -- 任务名字
                               strMissionInfo,     -- 任务目标
                               x300100_g_MissionReply,         -- 任务NPC
                               "找到欠税的人，让他们知道偷税漏税的害处",
                               format( x300100_g_MissionInfo, npc1, npc2, npc3),   -- 任务描述
                               x300100_g_MissionHelp)          -- 任务提示

        local money = x300100_GetMissionMoney( sceneId, selfId)
       
        if x300100_GetHighReward( sceneId, selfId) ~= 4 then
			 AddQuestMoneyBonus( sceneId, money)
	    else
            AddQuestMoneyBonus1( sceneId, money*3)
        end
    EndQuestEvent()
    DispatchQuestLogUpdate( sceneId, selfId, MissionId);
end

function x300100_ProcEnumEvent( sceneId, selfId, targetId, MissionId)
    -- print( targetId)
    -- 检查玩家等级是否符合要求
    if GetLevel( sceneId, selfId) >= x300100_g_LevelLess then
        AddQuestTextNM(sceneId, selfId, targetId, x300100_g_MissionCommentId, 13, -1)

        local state = GetQuestStateNM( sceneId, selfId, targetId, x300100_g_MissionId)
        AddQuestNumText( sceneId, x300100_g_MissionId, x300100_g_MissionName, state)
    end
end

-- 选中任务
function x300100_ProcEventEntry( sceneId, selfId, targetId, MissionId, switchId)
    -- print( MissionId)
    -- 显示征税任务说明
	if MissionId == x300100_g_MissionCommentId then
		QuestCom(sceneId, selfId, x300100_g_MissionCommentId)
		local contentStr = x300100_g_MissionCommentMessage
		BeginQuestEvent( sceneId)
            AddQuestText( sceneId, "#Y"..x300100_g_MissionName)
			AddQuestText( sceneId, contentStr)
		EndQuestEvent( sceneId)

		DispatchQuestEventList( sceneId, selfId, targetId)
		return
	end

    if GetLevel( sceneId, selfId) < x300100_g_LevelLess then
		return
    end

    -- 点击征税任务
    if MissionId == x300100_g_MissionId then
        -- 检查是否处于放弃任务的惩罚时间内
        if x300100_IsPunishTime( sceneId, selfId) == 1 then
    		BeginQuestEvent( sceneId)
                AddQuestText( sceneId, "#Y"..x300100_g_MissionName)
    			AddQuestText( sceneId, x300100_g_strInPunishTime)
    		EndQuestEvent( sceneId)
            DispatchQuestEventList( sceneId, selfId, targetId)
            return
        end
        if IsHaveQuestNM( sceneId, selfId, x300100_g_MissionId) == 0 then
            -- 没有任务
            x300100_DisplayMissionInfo( sceneId, selfId, targetId)
        else
            -- 已经接受过任务
            local npcGuid = GetMonsterGUID( sceneId, targetId)
            if npcGuid == x300100_g_MissionReplyGuid then
                -- 交任务NPC
                local misIndex = GetQuestIndexByID( sceneId, selfId, x300100_g_MissionId)
                local isFinish = GetQuestParam( sceneId, selfId, misIndex, 7)
                BeginQuestEvent( sceneId)
                AddQuestText( sceneId, "#Y"..x300100_g_MissionName)
                AddQuestText( sceneId, x300100_g_strFinish)
                if isFinish == 0 then
                    EndQuestEvent( sceneId)
                    DispatchQuestEventList( sceneId, selfId, targetId)
                else
                    -- 任务完成
                    local money = x300100_GetMissionMoney( sceneId, selfId)
                    AddQuestText( sceneId, " " )
                    AddQuestText( sceneId, "#Y奖励内容：" )
                    AddQuestText( sceneId, format("银卡：#{_MONEY%d}#Y",money) )
                    AddQuestText( sceneId, " " )
                    if x300100_GetHighReward( sceneId, selfId) == 4 then
                        AddQuestText( sceneId, "#Y额外奖励：" )
                        AddQuestText( sceneId, format( "银卡：#{_MONEY%d}#Y", money*2) )
                        AddQuestText( sceneId, " " )
                    end
                    EndQuestEvent( sceneId)
                    --DispatchQuestEventList( sceneId, selfId, targetId)
                    DispatchQuestInfoNM( sceneId, selfId, targetId, x300100_g_ScriptId, x300100_g_MissionId)
                end
            else
                -- 征税任务NPC
                local misIndex = GetQuestIndexByID( sceneId, selfId, x300100_g_MissionId)
                local npc1, npc2, npc3 = x300100_GetNPCID( sceneId, selfId)
                local count = GetQuestParam( sceneId, selfId, misIndex, 6)
                BeginQuestEvent( sceneId)
                local rand = random( 1, getn( x300100_g_strNPCTax) )
                AddQuestText( sceneId, "#Y"..x300100_g_MissionName)
                AddQuestText( sceneId, x300100_g_strNPCTax[ rand] )
                EndQuestEvent( sceneId)
                DispatchQuestEventList( sceneId, selfId, targetId)
                -- 在玩家人数很多的时候，点击NPC的征税按钮后可能反应比较慢，玩家如果此时多次点击会多次执行到这里，所以必须加入新判断条件，否则任务直接就完成了
                if npcGuid == npc1 and GetQuestParam( sceneId, selfId, misIndex, 1) < x300100_g_HasTaxValue then
                    SetQuestByIndex( sceneId, selfId, misIndex, 1, npc1 * x300100_g_HasTaxCoff)
                    count = count + 1
                end
                if npcGuid == npc2 and GetQuestParam( sceneId, selfId, misIndex, 2) < x300100_g_HasTaxValue then
                    SetQuestByIndex( sceneId, selfId, misIndex, 2, npc2 * x300100_g_HasTaxCoff)
                    count = count + 1
                end
                if npcGuid == npc3 and GetQuestParam( sceneId, selfId, misIndex, 3) < x300100_g_HasTaxValue then
                    SetQuestByIndex( sceneId, selfId, misIndex, 3, npc3 * x300100_g_HasTaxCoff)
                    count = count + 1
                end
                local strTip = format( x300100_g_FinishOne, npcGuid, count)
                BeginQuestEvent( sceneId)
                AddQuestText( sceneId, strTip)
                EndQuestEvent( sceneId)
                DispatchQuestTips( sceneId, selfId)
                if count >= x300100_g_TargetCount then
                    SetQuestByIndex( sceneId, selfId, misIndex, x300100_g_Complete, 1)
                    SetQuestByIndex( sceneId, selfId, misIndex, x300100_g_ButtonNPC, 1)
                    Msg2Player( sceneId, selfId, "任务已经完成，快点回去汇报吧！", 8, 2)
                    Msg2Player( sceneId, selfId, "任务已经完成，快点回去汇报吧！", 8, 3)
                end
                -- 更新已征税人数
                SetQuestByIndex( sceneId, selfId, misIndex, 6, count)
                -- 更新任务面板
                x300100_ProcQuestLogRefresh( sceneId, selfId, x300100_g_MissionId)
            end
        end
    end
end

-- 获得征税任务3个NPC的Id
function x300100_GetNPCID( sceneId, selfId)
    local misIndex = GetQuestIndexByID( sceneId, selfId, x300100_g_MissionId)
    local F1 = GetQuestParam( sceneId, selfId, misIndex, 1)
    local F2 = GetQuestParam( sceneId, selfId, misIndex, 2)
    local F3 = GetQuestParam( sceneId, selfId, misIndex, 3)
    local npc1 = F1
    local npc2 = F2
    local npc3 = F3
    if npc1 > x300100_g_HasTaxValue then
        npc1 = npc1 / x300100_g_HasTaxCoff
    end
    if npc2 > x300100_g_HasTaxValue then
        npc2 = npc2 / x300100_g_HasTaxCoff
    end
    if npc3 > x300100_g_HasTaxValue then
        npc3 = npc3 / x300100_g_HasTaxCoff
    end

    return npc1, npc2, npc3
end

-- 根据玩家当前等级和高奖状态返回奖励值
function x300100_GetMissionMoney( sceneId, selfId)
    local level = GetLevel( sceneId, selfId)
    if level >= x300100_g_MaxLevel then
        level = x300100_g_MaxLevel
    end

    local money = 0
    if x300100_GetHighReward( sceneId, selfId) < 5 or GetDayOfYear() ~= x300100_GetDayofYear( sceneId, selfId) then
        -- 高奖
        money = level * x300100_g_HighCofficient
    else
        money = level * x300100_g_LowCofficient
    end

    return money
end

-- 检查是否处于放弃任务的惩罚时间（5分钟）内，处于惩罚时间内返回1，否则返回0
function x300100_IsPunishTime( sceneId, selfId)
    local curTime = GetMinOfDay()
    local today = GetDayOfYear()
    local lastTime = x300100_GetAbandonTime( sceneId, selfId)
    if today == x300100_GetAbandonDate( sceneId, selfId) then
        if abs( curTime - lastTime) <= 5 then
            return 1
        end
    else
        if curTime + 1440 - lastTime <= 5 then
            return 1
        end
    end

    return 0
end

-- 显示任务信息
function x300100_DisplayMissionInfo( sceneId, selfId, targetId)
    BeginQuestEvent( sceneId)
        -- 任务名称
        AddQuestText( sceneId, "#Y"..x300100_g_MissionName)
        AddQuestText( sceneId, x300100_g_MissionDescription)
        local money = 0
        -- 等级
        local level = GetLevel( sceneId, selfId)
        if level >= x300100_g_MaxLevel then
            level = x300100_g_MaxLevel
        end
        -- 是否是当天第一次做任务
        local today = GetDayOfYear()
        local lastDay = x300100_GetDayofYear( sceneId, selfId)
        if today ~= lastDay then
            -- 设置高奖状态
            x300100_SetHighReward( sceneId, selfId, 0)
        end
        if x300100_GetHighReward( sceneId, selfId) < 5 then
            -- 高奖
            money = level * x300100_g_HighCofficient
        else
            money = level * x300100_g_LowCofficient
        end

        AddQuestText( sceneId, "#Y奖励内容：" )
        AddQuestText( sceneId, format( "银卡：#{_MONEY%d}#Y", money) )
        AddQuestText( sceneId, " " )

        if x300100_GetHighReward( sceneId, selfId) == 4 then
            AddQuestText( sceneId, "#Y额外奖励：" )
            AddQuestText( sceneId, format( "银卡：#{_MONEY%d}#Y", money*2) )
            AddQuestText( sceneId, " " )
        end
    EndQuestEvent( sceneId)
    DispatchQuestInfo( sceneId, selfId, targetId, x300100_g_MissionId, x300100_g_MissionId)
end

-- 显示并添加任务
function x300100_DisplayAndAccept( sceneId, selfId, targetId)
    if GetLevel( sceneId, selfId) < x300100_g_LevelLess then
		return
    end

    local today = GetDayOfYear()
    if today == x300100_GetDayofYear( sceneId, selfId) then
        if x300100_GetTimes( sceneId, selfId) >= x300100_g_MaxTimes then
            Msg2Player( sceneId, selfId, x300100_g_strOverMaxTimes, 8, 3)
            Msg2Player( sceneId, selfId, x300100_g_strOverMaxTimes, 8, 2)
            return 0
        end
    else
        x300100_SetDayofYear( sceneId, selfId, today)
        x300100_SetTimes( sceneId, selfId, 0)
    end
    -- 直接添加任务，不走ProcQuestAccept
    local ret	= AddQuest( sceneId, selfId, x300100_g_MissionId, x300100_g_ScriptId, 1, 0, 0, 1) -- 最后一个参数1开启ProcQuestAttach回调函数
    if( ret == 0) then
        BeginQuestEvent( sceneId)
        AddQuestText( sceneId, "任务已满，任务接受失败！" )
        EndQuestEvent( sceneId)
        DispatchQuestTips( sceneId, selfId)
        return 0
    end

	BeginQuestEvent( sceneId)
        -- 任务名称
        AddQuestText( sceneId, "#Y"..x300100_g_MissionName)

        -- 随机选中5个NPC
        local size = floor( getn( x300100_g_TaxTargetList) / x300100_g_TargetCount)
        local npcList = {}
        for i = 1, x300100_g_TargetCount do
            local rand = random( ( i - 1) * size + 1, i * size)
            npcList[ i] = x300100_g_TaxTargetList[ rand].npcId
        end
        AddQuestText( sceneId, "\n#Y任务目标：" )
        -- 格式化任务描述信息
        local rand = random( 1, getn( x300100_g_MissionInfoTable) )
        AddQuestText( sceneId, format( x300100_g_MissionInfoTable[ rand], npcList[ 1], npcList[ 2], npcList[ 3] ) )
        AddQuestText( sceneId, " " )

        -- 任务回复
        AddQuestText( sceneId, "#Y任务回复：" )
        AddQuestText( sceneId, x300100_g_MissionReply)
        AddQuestText( sceneId, " " )

        AddQuestText( sceneId, "#Y小提示：" )
        AddQuestText( sceneId, x300100_g_MissionHelp)
        AddQuestText( sceneId, " " )

        -- 金钱奖励
        local money = 0
        -- 等级
        local level = GetLevel( sceneId, selfId)
        if level >= x300100_g_MaxLevel then
            level = x300100_g_MaxLevel
        end
        local highReward = x300100_GetHighReward( sceneId, selfId)
        if highReward < 5 then
            -- 高奖
            money = level * x300100_g_HighCofficient
            -- 高奖日志
            GamePlayScriptLog( sceneId, selfId, ( highReward + 1) * 10 + 651)
        else
            money = level * x300100_g_LowCofficient
        end

        AddQuestText( sceneId, "#Y奖励内容：" )
		AddQuestText( sceneId, format( "银卡：#{_MONEY%d}#Y", money) )
        AddQuestText( sceneId, " " )
        if x300100_GetHighReward( sceneId, selfId) == 4 then
            AddQuestText( sceneId, "#Y额外奖励：" )
            AddQuestText( sceneId, format( "银卡：#{_MONEY%d}#Y", money*2) )
            AddQuestText( sceneId, " " )
        end

    EndQuestEvent( sceneId)
    DispatchQuestEventList( sceneId, selfId, targetId)

    -- 保存征税目标
    local misIndex = GetQuestIndexByID( sceneId, selfId, x300100_g_MissionId)
    SetQuestByIndex( sceneId, selfId, misIndex, 0, 0)
    SetQuestByIndex( sceneId, selfId, misIndex, 1, npcList[ 1] )
    SetQuestByIndex( sceneId, selfId, misIndex, 2, npcList[ 2] )
    SetQuestByIndex( sceneId, selfId, misIndex, 3, npcList[ 3] )
    SetQuestByIndex( sceneId, selfId, misIndex, 6, 0)
    SetQuestByIndex( sceneId, selfId, misIndex, 7, 0)

    -- 显示任务接受信息
    Msg2Player( sceneId, selfId, "你接受了任务："..x300100_g_MissionName, 8, 2)
    Msg2Player( sceneId, selfId, "你接受了任务："..x300100_g_MissionName, 8, 3)
end

-- 杀死怪物
function x300100_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
								--场景ID, 自己的ID, 怪物表位置号, 怪物objId, 任务ID
end


--任务放弃--这里需要设置放弃时间MissionData
function x300100_ProcQuestAbandon( sceneId, selfId, MissionId)
    -- 显示任务放弃信息
    Msg2Player( sceneId, selfId, "你放弃了任务："..x300100_g_MissionName, 8, 2)
    Msg2Player( sceneId, selfId, "你放弃了任务："..x300100_g_MissionName, 8, 3)

    -- 放弃任务
    DelQuest( sceneId, selfId, x300100_g_MissionId)
    -- 更新放弃时间
    x300100_SetAbandonTime( sceneId, selfId, GetMinOfDay() )
    -- 环数还原
    x300100_SetCircle( sceneId, selfId, 0)
    -- 取消高奖
    x300100_SetHighReward( sceneId, selfId, 6)
    -- 更新放弃任务日期
    x300100_SetAbandonDate( sceneId, selfId, GetDayOfYear() )
    x300100_SetDayofYear( sceneId, selfId, GetDayOfYear() )
    local times = x300100_GetTimes( sceneId, selfId)
    if times < 5 then
        x300100_SetTimes( sceneId, selfId, 5)
    else
        x300100_SetTimes( sceneId, selfId, times + 1)
    end
end


function x300100_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId)
    if GetLevel( sceneId, selfId) < x300100_g_LevelLess then
		return
    end

    local misIndex = GetQuestIndexByID( sceneId, selfId, x300100_g_MissionId)
    local npc1 = GetQuestParam( sceneId, selfId, misIndex, 1)
    if npc1 > x300100_g_HasTaxValue then
        npc1 = npc1 / x300100_g_HasTaxCoff
    end
    local npc2 = GetQuestParam( sceneId, selfId, misIndex, 2)
    if npc2 > x300100_g_HasTaxValue then
        npc2 = npc2 / x300100_g_HasTaxCoff
    end
    local npc3 = GetQuestParam( sceneId, selfId, misIndex, 3)
    if npc3 > x300100_g_HasTaxValue then
        npc3 = npc3 / x300100_g_HasTaxCoff
    end
    if npcGuid == npc1 then
        local isFinish = GetQuestParam( sceneId, selfId, misIndex, 1)
        if isFinish < x300100_g_HasTaxValue then
            AddQuestNumText( sceneId, x300100_g_MissionId, x300100_g_MissionName, 13)
        end
        return
    end
    if npcGuid == npc2 then
        local isFinish = GetQuestParam( sceneId, selfId, misIndex, 2)
        if isFinish < x300100_g_HasTaxValue then
            AddQuestNumText( sceneId, x300100_g_MissionId, x300100_g_MissionName, 13)
        end
        return
    end
    if npcGuid == npc3 then
        local isFinish = GetQuestParam( sceneId, selfId, misIndex, 3)
        if isFinish < x300100_g_HasTaxValue then
            AddQuestNumText( sceneId, x300100_g_MissionId, x300100_g_MissionName, 13)
        end
        return
    end
end

-- --完成任务 返回1代表成功，0代表交任务失败
function x300100_ProcQuestSubmit( sceneId, selfId, targetId, selectId, MissionId )
end

-- --物品改变
function x300100_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end

function x300100_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

-- --离开区域
function x300100_ProcAreaLeaved( sceneId, selfId, ScriptId, MissionId )
end

-- --区域定时器
function x300100_ProcTiming( sceneId, selfId, ScriptId, MissionId )
end

-- 设置高奖状态
function x300100_SetHighReward( sceneId, selfId, value)
    SetQuestData( sceneId, selfId, MD_ZHENGSHUI_HIGHREWARD[ 1], MD_ZHENGSHUI_HIGHREWARD[ 2], MD_ZHENGSHUI_HIGHREWARD[ 3], value)
end

-- 获得高奖计数
function x300100_GetHighReward( sceneId, selfId)
    return GetQuestData( sceneId, selfId, MD_ZHENGSHUI_HIGHREWARD[ 1], MD_ZHENGSHUI_HIGHREWARD[ 2], MD_ZHENGSHUI_HIGHREWARD[ 3] )
end

-- 返回当前环数
function x300100_GetCircle( sceneId, selfId)
    return GetQuestData( sceneId, selfId, MD_ZHENGSHUI_ROUND[ 1], MD_ZHENGSHUI_ROUND[ 2], MD_ZHENGSHUI_ROUND[ 3] )
end

-- 设置环数，注意：value不能大于8
function x300100_SetCircle( sceneId, selfId, value)
    SetQuestData( sceneId, selfId, MD_ZHENGSHUI_ROUND[ 1], MD_ZHENGSHUI_ROUND[ 2], MD_ZHENGSHUI_ROUND[ 3], value)
end

function x300100_GetDayofYear( sceneId, selfId)
    return GetQuestData( sceneId, selfId, MD_ZHENGSHUI_DATE[ 1], MD_ZHENGSHUI_DATE[ 2], MD_ZHENGSHUI_DATE[ 3] )
end

function x300100_SetDayofYear( sceneId, selfId, value)
    SetQuestData( sceneId, selfId, MD_ZHENGSHUI_DATE[ 1], MD_ZHENGSHUI_DATE[ 2], MD_ZHENGSHUI_DATE[ 3], value)
end

function x300100_GetTimes( sceneId, selfId)
    return GetQuestData( sceneId, selfId, MD_ZHENGSHUI_TIMES[ 1], MD_ZHENGSHUI_TIMES[ 2], MD_ZHENGSHUI_TIMES[ 3] )
end

function x300100_SetTimes( sceneId, selfId, value)
    SetQuestData( sceneId, selfId, MD_ZHENGSHUI_TIMES[ 1], MD_ZHENGSHUI_TIMES[ 2], MD_ZHENGSHUI_TIMES[ 3], value)
end

-- 获得放弃征税任务时间（从0点起的第N分钟）
function x300100_GetAbandonTime( sceneId, selfId)
    return GetQuestData( sceneId, selfId, MD_ZHENGSHUI_ABANDON[ 1], MD_ZHENGSHUI_ABANDON[ 2], MD_ZHENGSHUI_ABANDON[ 3] )
end

-- 设置放弃征税任务时间（从0点起的第N分钟）
function x300100_SetAbandonTime( sceneId, selfId, value)
    SetQuestData( sceneId, selfId, MD_ZHENGSHUI_ABANDON[ 1], MD_ZHENGSHUI_ABANDON[ 2], MD_ZHENGSHUI_ABANDON[ 3], value)
end

-- 获得最后一次放弃征税任务日期（0--365）
function x300100_GetAbandonDate( sceneId, selfId)
    return GetQuestData( sceneId, selfId, MD_ZHENGSHUI_ABANDONDATE[ 1], MD_ZHENGSHUI_ABANDONDATE[ 2], MD_ZHENGSHUI_ABANDONDATE[ 3] )
end

-- 设置最后一次放弃征税任务日期（0--365）
function x300100_SetAbandonDate( sceneId, selfId, value)
    SetQuestData( sceneId, selfId, MD_ZHENGSHUI_ABANDONDATE[ 1], MD_ZHENGSHUI_ABANDONDATE[ 2], MD_ZHENGSHUI_ABANDONDATE[ 3], value)
end

function x300100_ProcAccept( sceneId, selfId)
    -- print( "x300100_ProcAccept" )
end

function x300100_ProcAcceptCheck( sceneId, selfId)
    -- print( "x300100_ProcAcceptCheck" )
end

function x300100_ProcQuestAccept( sceneId, selfId, targetId, MissionId)
    if GetLevel( sceneId, selfId) < x300100_g_LevelLess then
		return
    end

    -- 接任务日期
    local getMission = x300100_GetDayofYear( sceneId, selfId)
    local today = GetDayOfYear()
    local reward = x300100_GetHighReward( sceneId, selfId)
    if IsHaveQuestNM( sceneId, selfId, x300100_g_MissionId) > 0 then -- 交任务
    	
    	local misIndex = GetQuestIndexByID( sceneId, selfId, x300100_g_MissionId)
        local isFinish = GetQuestParam( sceneId, selfId, misIndex, 7)
        
        --任务未完成，忽略相关处理
        if isFinish ~= 1 then
        	return
        end
    	
        -- 玩家确认任务完成
        local money = x300100_GetMissionMoney( sceneId, selfId)
        AddMoney( sceneId, selfId, 1, money)
        DelQuest( sceneId, selfId, x300100_g_MissionId)

        local round = x300100_GetCircle( sceneId, selfId) + 1
        BeginQuestEvent( sceneId)
            if getMission ~= today then -- 如果不是当天接的任务，把高奖次数重置
                reward = 0
                x300100_SetHighReward( sceneId, selfId, 1)
            end
            reward = reward + 1
            if round > 5 then
                round = round - 5
            end
            if reward < 6 then
                AddQuestText( sceneId, format( "环数：%d/5    本日高奖环数  %d/5", round, reward) )
                if reward == 5 then
                    x300100_SetHighReward( sceneId, selfId, 6)
                end
            else
                AddQuestText( sceneId, "环数："..round.."/5" )
            end
        EndQuestEvent( sceneId)
        DispatchQuestTips( sceneId, selfId)

        BeginQuestEvent( sceneId)
        AddQuestText( sceneId, "你完成了任务："..x300100_g_MissionName )
        EndQuestEvent( sceneId)
        DispatchQuestTips( sceneId, selfId)
        Msg2Player( sceneId, selfId, "你完成了任务："..x300100_g_MissionName, 8, 2)

        local str_money = format( "获得#R银卡#{_MONEY%d}#cffcf00的奖励。", money)
        Msg2Player(sceneId, selfId, str_money, 8, 2)

        if getMission == today then -- 当天接的任务
            if round > 5 then
                round = 0
            end
            if reward < 6 then
                if reward == 5 then
                    x300100_GetItemAwardDirectly( sceneId, selfId)
                    x300100_AdditionalReward( sceneId, selfId)
                    AddCountryResource( sceneId, selfId, 2, 1000, 1)
                end
                -- 更新高奖次数
                x300100_SetHighReward( sceneId, selfId, reward)
                -- 高奖日志
                GamePlayScriptLog( sceneId, selfId, reward * 10 + 651 + 1)
            end
        else    -- 今天以前接的任务
            -- 更新任务日期
            x300100_SetDayofYear( sceneId, selfId, today)
            -- 更新计次
            x300100_SetTimes( sceneId, selfId, 0)
        end
        -- 内务任务
        if round == 5 then
            CallScriptFunction( 256216, "FinishTax", sceneId, selfId)
        end

        -- 更新环数
        x300100_SetCircle( sceneId, selfId, round)
        -- 更新任务完成次数
        x300100_SetTimes( sceneId, selfId, x300100_GetTimes( sceneId, selfId) + 1)
    else -- 接任务
        x300100_DisplayAndAccept( sceneId, selfId, targetId)
    end
end

-- 额外的现银奖励
function x300100_AdditionalReward( sceneId, selfId)
    local level = GetLevel( sceneId, selfId)
    if level > 80 then
        level = 80
    end

    local money = x300100_g_HighCofficient * level * 2
    AddMoney( sceneId, selfId, 1, money)
    local str_money = format( "获得#R银卡#{_MONEY%d}#cffcf00的额外奖励。", money)
    Msg2Player(sceneId, selfId, str_money, 8, 2)
end

--道具直接奖励
function x300100_GetItemAwardDirectly(sceneId, selfId)

	-- local spec;
	-- local ret = 0;
	-- local playerlevel = GetLevel(sceneId, selfId)
	-- for i, item in x300100_g_ItemAwardCertain do
		-- if playerlevel >= item.levelMin and playerlevel < item.levelMax then

			-- local rnum = random(1, item.num);
			-- BeginAddItem(sceneId)
				-- AddItem(sceneId, item.id[rnum], 1);
			-- if EndAddItem(sceneId, selfId) > 0 then
				-- AddItemListToPlayer(sceneId, selfId);
				-- ret = 1
			-- end
			
			-- local str = format("#Y获得物品#R#{_ITEM%d}#Y的奖励", item.id[rnum]);
			-- BeginQuestEvent(sceneId)
				-- AddQuestText(sceneId, str)
			-- EndQuestEvent()
			-- DispatchQuestTips(sceneId, selfId)
			-- Msg2Player(sceneId, selfId, str, 8, 2)
			
			-- break
		-- end
	-- end
	-- return ret

end


