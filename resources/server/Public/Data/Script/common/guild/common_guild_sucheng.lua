--MisDescBegin
x300683_g_ScriptId =  300683
x300683_g_MissionKind 				= 	1                       --任务类型
x300683_g_LevelLess					= 	40 

x300683_g_ExtTarget					=	{ {type=20,n=10,target="马车"} }
x300683_g_BonusMoney8				=	150 --帮贡
x300683_g_GuildExpBonus				=	4 --帮会经验
--MisDescEnd

--要杀的怪的个数
x300683_g_NeedKilledNum				= 1
x300683_CostGold					= 1000
x300683_g_BonusItemId				= 11990050 	-- 1个回魂丹（绑定）

--任务与玩家等级对应关系
x300683_g_MisMatchingLevel = 	{
									{ sceneId = 5,	monsterId = 9800, level = 50 },
									{ sceneId = 6,	monsterId = 9801, level = 55 },
									{ sceneId = 7,	monsterId = 9802, level = 60 },
									{ sceneId = 8,	monsterId = 9803, level = 65 },
									{ sceneId = 9,	monsterId = 9804, level = 70 },
									{ sceneId = 10,	monsterId = 9805, level = 75 },
									{ sceneId = 11,	monsterId = 9806, level = 75 },
									{ sceneId = 13,	monsterId = 9807, level = 80 },
									{ sceneId = 16,	monsterId = 9808, level = 85 },
									{ sceneId = 17,	monsterId = 9809, level = 85 },
									{ sceneId = 18,	monsterId = 9810, level = 90 },
									{ sceneId = 19,	monsterId = 9811, level = 95 },
									{ sceneId = 20,	monsterId = 9812, level = 95 },
									{ sceneId = 21,	monsterId = 9813, level = 100 },
									{ sceneId = 22,	monsterId = 9814, level = 105 },
									{ sceneId = 23,	monsterId = 9815, level = 105 },
									{ sceneId = 24,	monsterId = 9816, level = 110 },
									{ sceneId = 25,	monsterId = 9817, level = 115 },
								}
x300683_g_SubMissionId				=	{--for all country
                                            --楼兰帮会速成
											{ 
												  { MissionId=7784, MissionName = "【帮会】帮会速成", MissionTarget = "  前往相应等级@npc_31121杀死#G魔君爪牙#W", MissionInfo = "\t帮会速成只适合相对初期的帮会的成员，我会把击杀一些穷凶极恶之徒作为任务目标，你需要前往领地打败不低于自己等级5级以上的任意一个魔君爪牙。\n \n#R\t领取本任务需要花费1两现金/金卡，你确定领取本任务吗？#W\n \n领取本任务的条件有两个：\n \n1：服务器中有1个4级及以上等级帮会。\n2：只有低于全服最高帮会等级2级以上（含2级）的且达到#G40级#W的帮会成员才能领取本任务。",MissionHelp = "\t这些凶徒非常危险，最好本帮成员组队共同前往除之！#G杀死魔君爪牙后，周围本帮成员均可完成任务！", NPCName = "@npc_123723",Completed ="\t很高兴你能顺利完成任务，相信帮会有你的努力会更加的飞速发展。希望早日看到你的帮会成长为众人景仰的大帮。",Missionruse="\t你可通过#G边塞#W的#G领地传送人#W前往领地，可通过#G场景地图（快捷键M）#W找到#G魔君爪牙的标志#W。\n\t#G杀死魔君爪牙后，周围本帮成员均可完成任务！#r\t#R如果您的等级高于魔君爪牙5级以上，将无法完成任务！"}, 							
											},
                                            --天山帮会速成
											{ 
												  { MissionId=7785, MissionName = "【帮会】帮会速成", MissionTarget = "  前往相应等级@npc_31122杀死#G魔君爪牙#W", MissionInfo = "\t帮会速成只适合相对初期的帮会的成员，我会把击杀一些穷凶极恶之徒作为任务目标，你需要前往领地打败不低于自己等级5级以上的任意一个魔君爪牙。\n \n#R\t领取本任务需要花费1两现金/金卡，你确定领取本任务吗？#W\n \n领取本任务的条件有两个：\n \n1：服务器中有1个4级及以上等级帮会。\n2：只有低于全服最高帮会等级2级以上（含2级）的且达到#G40级#W的帮会成员才能领取本任务。",MissionHelp = "\t这些凶徒非常危险，最好本帮成员组队共同前往除之！#G杀死魔君爪牙后，周围本帮成员均可完成任务！", NPCName = "@npc_126020",Completed ="\t很高兴你能顺利完成任务，相信帮会有你的努力会更加的飞速发展。希望早日看到你的帮会成长为众人景仰的大帮。",Missionruse="\t你可通过#G边塞#W的#G领地传送人#W前往领地，可通过#G场景地图（快捷键M）#W找到#G魔君爪牙的标志#W。\n\t#G杀死魔君爪牙后，周围本帮成员均可完成任务！#r\t#R如果您的等级高于魔君爪牙5级以上，将无法完成任务！"}, 							
											},
                                            --昆仑帮会速成
											{ 
												  { MissionId=7786, MissionName = "【帮会】帮会速成", MissionTarget = "  前往相应等级@npc_31123杀死#G魔君爪牙#W", MissionInfo = "\t帮会速成只适合相对初期的帮会的成员，我会把击杀一些穷凶极恶之徒作为任务目标，你需要前往领地打败不低于自己等级5级以上的任意一个魔君爪牙。\n \n#R\t领取本任务需要花费1两现金/金卡，你确定领取本任务吗？#W\n \n领取本任务的条件有两个：\n \n1：服务器中有1个4级及以上等级帮会。\n2：只有低于全服最高帮会等级2级以上（含2级）的且达到#G40级#W的帮会成员才能领取本任务。",MissionHelp = "\t这些凶徒非常危险，最好本帮成员组队共同前往除之！#G杀死魔君爪牙后，周围本帮成员均可完成任务！", NPCName = "@npc_129020",Completed ="\t很高兴你能顺利完成任务，相信帮会有你的努力会更加的飞速发展。希望早日看到你的帮会成长为众人景仰的大帮。",Missionruse="\t你可通过#G边塞#W的#G领地传送人#W前往领地，可通过#G场景地图（快捷键M）#W找到#G魔君爪牙的标志#W。\n\t#G杀死魔君爪牙后，周围本帮成员均可完成任务！#r\t#R如果您的等级高于魔君爪牙5级以上，将无法完成任务！"}, 							
											},
                                            --敦煌帮会速成
											{ 
												  { MissionId=7787, MissionName = "【帮会】帮会速成", MissionTarget = "  前往相应等级@npc_31124杀死#G魔君爪牙#W", MissionInfo = "\t帮会速成只适合相对初期的帮会的成员，我会把击杀一些穷凶极恶之徒作为任务目标，你需要前往领地打败不低于自己等级5级以上的任意一个魔君爪牙。\n \n#R\t领取本任务需要花费1两现金/金卡，你确定领取本任务吗？#W\n \n领取本任务的条件有两个：\n \n1：服务器中有1个4级及以上等级帮会。\n2：只有低于全服最高帮会等级2级以上（含2级）的且达到#G40级#W的帮会成员才能领取本任务。",MissionHelp = "\t这些凶徒非常危险，最好本帮成员组队共同前往除之！#G杀死魔君爪牙后，周围本帮成员均可完成任务！", NPCName = "@npc_132020",Completed ="\t很高兴你能顺利完成任务，相信帮会有你的努力会更加的飞速发展。希望早日看到你的帮会成长为众人景仰的大帮。",Missionruse="\t你可通过#G边塞#W的#G领地传送人#W前往领地，可通过#G场景地图（快捷键M）#W找到#G魔君爪牙的标志#W。\n\t#G杀死魔君爪牙后，周围本帮成员均可完成任务！#r\t#R如果您的等级高于魔君爪牙5级以上，将无法完成任务！"}, 							
											},
										}


function x300683_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

	local nCountry = GetCurCountry( sceneId, selfId )

	if GetGuildID( sceneId, selfId ) == -1 then
		--不在帮会中
		return
	end

	local Level = GetLevel(sceneId, selfId)
	if Level >= x300683_g_LevelLess  then	-- 如果可以接这个任务
		local state = GetQuestStateNM( sceneId, selfId, targetId, x300683_g_SubMissionId[nCountry+1][1].MissionId);
		AddQuestTextNM( sceneId, selfId, targetId, x300683_g_SubMissionId[nCountry+1][1].MissionId, state, 0 ) -- 显示任务信息
		return 1
	end

end

--选中任务
function x300683_ProcEventEntry( sceneId, selfId, targetId, MissionId )

	local nCountry = GetCurCountry( sceneId, selfId )

	local index = 1
	local IsHaveQuest = 0
	
	
	for i,itm in x300683_g_SubMissionId[nCountry+1] do
		if IsHaveQuestNM( sceneId, selfId, itm.MissionId ) > 0 then	-- 如果有这个任务
	
			IsHaveQuest = 1
			MissionId = itm.MissionId
			break
		end
	end

	if(IsHaveQuest > 0) then
		local bDone = x300683_CheckSubmit(sceneId, selfId, MissionId);
		if(bDone > 0) then
			x300683_DispatchCompletedInfo( sceneId, selfId, targetId,index) --完成任务显示
		else
			x300683_DispatchContinueInfo( sceneId, selfId, targetId,index ) --未完成任务显示
		end
	else

		x300683_DispatchMissionInfo( sceneId, selfId, targetId,index )		--任务信息显示
	end

end

---------------------------------------------------------------------------------------------------
--检查任务是否可提交
---------------------------------------------------------------------------------------------------
function x300683_CheckSubmit(sceneId, selfId,MissionId)

	local misIndex = GetQuestIndexByID(sceneId, selfId, MissionId);
	return GetQuestParam(sceneId, selfId, misIndex, 7);
	
end


---------------------------------------------------------------------------------------------------
--向客户端发送任务完成信息
---------------------------------------------------------------------------------------------------
function x300683_DispatchCompletedInfo( sceneId, selfId, targetId,index )
	
	BeginQuestEvent(sceneId)

	    local nCountry = GetCurCountry( sceneId, selfId )

		--任务完成信息
		AddQuestText(sceneId,"#Y"..x300683_g_SubMissionId[nCountry+1][index].MissionName)
		AddQuestText(sceneId,x300683_g_SubMissionId[nCountry+1][index].Completed)
		AddQuestText(sceneId," ")

		--任务奖励信息
		x300683_BonusInfo(sceneId, selfId)
		
	EndQuestEvent(sceneId)
	DispatchQuestContinueInfoNM(sceneId, selfId, targetId, x300683_g_ScriptId, x300683_g_SubMissionId[nCountry+1][index].MissionId);
   
end

---------------------------------------------------------------------------------------------------
--向客户端发送任务未完成
---------------------------------------------------------------------------------------------------
function x300683_DispatchContinueInfo( sceneId, selfId, targetId,index )
	
	BeginQuestEvent(sceneId)

    	local nCountry = GetCurCountry( sceneId, selfId )
    	
		--任务继续信息
		AddQuestText(sceneId,"#Y"..x300683_g_SubMissionId[nCountry+1][index].MissionName)
		AddQuestText(sceneId,format("%s", x300683_g_SubMissionId[nCountry+1][index].MissionInfo))
		AddQuestText(sceneId," ")

		--任务目标
		AddQuestText( sceneId,"#Y完成情况：")
		AddQuestText(sceneId, "未完成");

		--任务奖励信息
		x300683_BonusInfo(sceneId, selfId)
		
	--任务提示信息
	EndQuestEvent()

	--DispatchQuestDemandInfo(sceneId, selfId, targetId, x300683_g_ScriptId, x300683_g_SubMissionId[nCountry+1][index].MissionId,0);
	DispatchQuestInfo(sceneId, selfId, targetId, x300683_g_ScriptId, x300683_g_SubMissionId[nCountry+1][index].MissionId, 1)

end


---------------------------------------------------------------------------------------------------
--向客户端发送任务信息
---------------------------------------------------------------------------------------------------
function x300683_DispatchMissionInfo( sceneId, selfId, NPCId,index )

	BeginQuestEvent(sceneId)

		--任务信息
		local BangExp =x300683_g_BangExp
		local nCountry = GetCurCountry( sceneId, selfId )
		AddQuestText(sceneId,"#Y"..x300683_g_SubMissionId[nCountry+1][index].MissionName)
		AddQuestText(sceneId,format("%s", x300683_g_SubMissionId[nCountry+1][index].MissionInfo))
		AddQuestText(sceneId," ")

		--任务目标
		AddQuestText( sceneId,"#Y任务目标：")
		AddQuestText( sceneId,format("%s", x300683_g_SubMissionId[nCountry+1][index].MissionTarget))
		AddQuestText( sceneId," ")

		--提示信息
		if x300683_g_SubMissionId[nCountry+1][index].MissionHelp ~= "" then

			AddQuestText(sceneId,"#Y任务提示：")
			AddQuestText(sceneId,format("%s", x300683_g_SubMissionId[nCountry+1][index].MissionHelp))
			AddQuestText(sceneId," ")
		end

		--任务奖励信息
		x300683_BonusInfo(sceneId, selfId)
		
	EndQuestEvent(sceneId)
	DispatchQuestInfoNM(sceneId, selfId, NPCId, x300683_g_ScriptId, x300683_g_SubMissionId[nCountry+1][index].MissionId);
		
end


---------------------------------------------------------------------------------------------------
--获得奖励
---------------------------------------------------------------------------------------------------
function x300683_BonusInfo(sceneId, selfId)

	if x300683_g_BonusMoney8 > 0 then
		AddQuestMoneyBonus8(sceneId, x300683_g_BonusMoney8 )	--增加帮贡
	end
	
	if x300683_g_GuildExpBonus>0 then
		AddQuestGuildExpBonus(sceneId,x300683_g_GuildExpBonus)
	end
	
	AddQuestItemBonus(sceneId, x300683_g_BonusItemId, 1)
end

function x300683_GetBonus( sceneId, selfId, joinguildtime)
	--奖励物品
	BeginAddItem( sceneId)
	AddBindItem( sceneId, x300683_g_BonusItemId, 1)
	if EndAddItem( sceneId, selfId) > 0 then
	    AddItemListToPlayer( sceneId, selfId)
	else
	    Msg2Player( sceneId, selfId, "由于你的背包已满，无法获得奖励。", 8, 2)
	end
    
	--奖励帮贡
    if x300683_g_BonusMoney8 > 0 then
		AddGuildUserPoint(sceneId,selfId,x300683_g_BonusMoney8)	--增加帮贡
		local BonusMoney8 = x300683_g_BonusMoney8
		local pointText = "获得#R帮贡"..BonusMoney8.."点#o的奖励"	
  		Msg2Player(sceneId,selfId,pointText,8,3)
  		Msg2Player(sceneId,selfId,pointText,8,2)
	end
	-- 奖励帮会经验
	local bangExp = x300683_g_GuildExpBonus 
	if bangExp > 0 then
		if joinguildtime == -1 or GetCurrentTime()-joinguildtime<24*3600 then
			Msg2Player(sceneId,selfId,"很抱歉，您加入帮会时间低于24小时，不能获得帮会经验。",8,3)
			Msg2Player(sceneId,selfId,"很抱歉，您加入帮会时间低于24小时，不能获得帮会经验。",8,2)
			return
		end
			AddGuildExp(sceneId,selfId,bangExp)
			local name = GetName(sceneId, selfId)			
			Msg2Player(sceneId,selfId,format("获得#R帮会经验"..bangExp.."点#o的奖励"),8,3)
			Msg2Player(sceneId,selfId,format("获得#R帮会经验"..bangExp.."点#o的奖励"),8,2)
			Msg2Player(sceneId,selfId,format("帮会："..name.."完成了【帮会】帮会速成任务，为帮会贡献了"..bangExp.."点帮会经验。"),6,2)
	end
		
end



--**********************************
--接受
--**********************************
function x300683_ProcQuestAccept( sceneId, selfId, targetId, MissionId )

	if IsQuestFullNM( sceneId, selfId )==1 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"可接任务数量已满")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return 
	end

	if GetGuildID( sceneId, selfId ) == -1 then
		--不在帮会中
		Msg2Player(sceneId,selfId,"你不是帮会成员，请先加入帮会再来领取！",8,3)
		Msg2Player(sceneId,selfId,"你不是帮会成员，请先加入帮会再来领取！",8,2)
		return
	end
	
	if x300683_GetDayCount(sceneId, selfId) == 1 then
		local Readme = "你今天已经领取过帮会速成任务了，请明天再来吧！"
		Msg2Player(sceneId,selfId,Readme,8,3)
		Msg2Player(sceneId,selfId,Readme,8,2)
		return
	end


	--检查前置任务
	local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId, MissionId )
	if FrontMissiontId1 ~= -1 then
		if IsQuestHaveDoneNM( sceneId, selfId, FrontMissiontId1 ) == 0 then
			return 
		end
	end
	if FrontMissiontId2 ~= -1 then
		if IsQuestHaveDoneNM( sceneId, selfId, FrontMissiontId2 ) == 0 then
			return 
		end
	end
	if FrontMissiontId3 ~= -1 then
		if IsQuestHaveDoneNM( sceneId, selfId, FrontMissiontId3 ) == 0 then
			return
		end
	end
	
	local maxLevel = GetMaxGuildLevel()
	local GuildLevel = GetGuildSimpleData(GetGuildID( sceneId, selfId ))
	if maxLevel < 4 then
		Msg2Player(sceneId, selfId, "服务器中至少有一个4级帮会才会开启此任务。", 8, 3)
		Msg2Player(sceneId, selfId, "服务器中至少有一个4级帮会才会开启此任务。", 8, 2)
		return
	end
	
	if maxLevel-GuildLevel < 2 then
		local msg = format("很抱歉，%d级及以下帮会才可以领取此任务", maxLevel-2)
		Msg2Player(sceneId, selfId, msg, 8, 3)
		Msg2Player(sceneId, selfId, msg, 8, 2)
		return
	end
	
	--得到玩家现金消费模式
	if GetGoldMode( sceneId, selfId ) == 1 then
		--现金模式
		if CostMoney( sceneId, selfId, 2, x300683_CostGold, 325 ) == -1 and CostMoney( sceneId, selfId, 3, x300683_CostGold, 325 ) == -1  then
			Msg2Player(sceneId,selfId,"很抱歉，接受任务需要花费1两现金(金卡)。",8,3)	
			Msg2Player(sceneId,selfId,"很抱歉，接受任务需要花费1两现金(金卡)。",8,2)	
			return
		end
	else 
		--金卡模式
		if CostMoney( sceneId, selfId, 3, x300683_CostGold, 325 ) == -1 and CostMoney( sceneId, selfId, 2, x300683_CostGold, 325 ) == -1 then
			Msg2Player(sceneId,selfId,"很抱歉，接受任务需要花费1两现金(金卡)。",8,3)	
			Msg2Player(sceneId,selfId,"很抱歉，接受任务需要花费1两现金(金卡)。",8,2)	
			return
		end
	end
		
	AddQuest( sceneId, selfId, MissionId, x300683_g_ScriptId, 0, 0, 0, 0)
	
	BeginQuestEvent(sceneId)
	--接任务写日志
	GamePlayScriptLog(sceneId,selfId,1721)
	
	local Readme = "你接受了任务：【帮会】帮会速成"
	Msg2Player(sceneId,selfId,Readme,8,3)	
	Msg2Player(sceneId,selfId,Readme,8,2)	

	local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )
	SetQuestByIndex(sceneId, selfId, misIndex, 7, 0);
	SetQuestByIndex(sceneId, selfId, misIndex, 0, 0);
	
end


--完成任务
--返回1代表成功，0代表交任务失败
function x300683_ProcQuestSubmit( sceneId, selfId, targetId, selectId, MissionId )
	
	if IsHaveQuestNM( sceneId, selfId, MissionId) == 0 then	-- 如果没这个任务直接退出
		return 0
	end
	
	local bDone = x300683_CheckSubmit(sceneId, selfId, MissionId)
	if bDone <= 0 then
		return 
	end
	
	DelQuest( sceneId, selfId, MissionId )

    -- 增加活跃度
    local id = GetGuildID( sceneId, selfId)
    if id ~= -1 then
        AddGuildActivity( sceneId, selfId, 20 )
        Msg2Player(sceneId,selfId,"帮会活跃度增加#G20#cFFCF00点",8,2)
    end

	--交任务写日志
	GamePlayScriptLog(sceneId,selfId,1722)

	x300683_SetDayCount(sceneId, selfId)
	
	GetJoinGuildTime(sceneId,selfId,x300683_g_ScriptId)
	return 0
end

function x300683_OnMemberJoinTimeReturn( sceneId, selfId, param )
	x300683_GetBonus( sceneId,selfId, param )
end

function x300683_ProcQuestAttach( sceneId, selfId, npcId, npcGuid,misIndex, MissionId )

	local nCountry = GetCurCountry( sceneId, selfId )

	for i,itm in x300683_g_SubMissionId[nCountry+1] do
		local bHaveMission = IsHaveQuestNM(sceneId, selfId,itm.MissionId );

		if bHaveMission > 0 then
			if Needitem >= 1 then
				local state = GetQuestStateNM(sceneId,selfId,npcId,itm.MissionId)
				AddQuestNumText(sceneId, itm.MissionId, itm.MissionName,7,state);
			else
				local state = GetQuestStateNM(sceneId,selfId,npcId,itm.MissionId)
				AddQuestNumText(sceneId, itm.MissionId, itm.MissionName,6,state);
			end
			break
		end
	end

end

--********************************************************************
--放弃
--********************************************************************
function x300683_ProcQuestAbandon( sceneId, selfId,MissionId )

	local nCountry = GetCurCountry( sceneId, selfId )
	MissionId = x300683_g_SubMissionId[nCountry+1][1].MissionId
	
	if IsHaveQuestNM( sceneId, selfId, MissionId) == 0 then	-- 如果没有这个任务
		return
	end

	DelQuest( sceneId, selfId, MissionId)
	local Readme = "你放弃了任务：【帮会】帮会速成"
	Msg2Player(sceneId,selfId,Readme,8,3)
	Msg2Player(sceneId,selfId,Readme,8,2)
	x300683_SetDayCount(sceneId, selfId)
end

--********************************************************************
--接受
--********************************************************************
function x300683_ProcAccept( sceneId, selfId )
end

function x300683_IsValidOnDie( sceneId,objId,killerId )
	
	if killerId == -1 then
		--出错了
		return 0
	end

	if IsObjValid(sceneId,killerId)  == 0 then
		--无效OBJ
		return 0
	end

	if IsPlayerStateNormal( sceneId,killerId ) ~= 1 then
		return 0
	end

	return 1
	
end

function x300683_OnDie( sceneId,objId,killerId )
end

--杀死怪物
function x300683_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
						   --场景ID, 自己的ID, 怪物表位置号, 怪物objId, 任务ID				   
end

---------------------------------------------------------------------------------------------------
--任务日志刷新
---------------------------------------------------------------------------------------------------
function x300683_QuestLogRefresh( sceneId, selfId, MissionId)
	local nCountry = GetCurCountry( sceneId, selfId )
	for i,itm in x300683_g_SubMissionId[nCountry+1] do 
		local bHaveMission = IsHaveQuestNM(sceneId, selfId,itm.MissionId );
		if bHaveMission > 0 then
		
			BeginQuestEvent(sceneId)	

			local misIndex = GetQuestIndexByID(sceneId, selfId, itm.MissionId);
			local num = GetQuestParam(sceneId, selfId,misIndex,0)
			local text = format("(%d/%d)",num,1)
			
			AddQuestLogCustomText( sceneId,
									"",						-- 标题
									itm.MissionName,        -- 任务名字
									itm.MissionTarget..text,		--任务目标
									itm.NPCName,			--任务NPC
									itm.Missionruse,               --任务攻略
									itm.MissionInfo,	--任务描述
									"每张领地地图都有一个魔君的爪牙，请根据自身等级进行选择。"					--任务小提示
									)
									
			--任务奖励信息
			x300683_BonusInfo(sceneId, selfId)
		
			EndQuestEvent(sceneId)
			DispatchQuestLogUpdate(sceneId, selfId, itm.MissionId);
		end
		break
	end
end

function x300683_ProcQuestLogRefresh( sceneId, selfId, MissionId)

	x300683_QuestLogRefresh( sceneId, selfId, MissionId );
end

--物品改变
function x300683_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId, nChangeType )

end

---------------------------------------------------------------------------------------------------
--取得此任务当天当前已完成次数
---------------------------------------------------------------------------------------------------
function x300683_GetDayCount(sceneId, selfId)
	local today = GetDayOfYear()
	local lastday = GetQuestData(sceneId, selfId, MD_GUILD_SUCHENG_DATE[1], MD_GUILD_SUCHENG_DATE[2], MD_GUILD_SUCHENG_DATE[3])

	if lastday ~= today then
		return 0
	end
	return 1
end
---------------------------------------------------------------------------------------------------
--更新当天接任务次数
---------------------------------------------------------------------------------------------------
function x300683_SetDayCount(sceneId, selfId)
	local today = GetDayOfYear()
	SetQuestData(sceneId, selfId, MD_GUILD_SUCHENG_DATE[1], MD_GUILD_SUCHENG_DATE[2], MD_GUILD_SUCHENG_DATE[3], today)
end