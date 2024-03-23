
--MisDescBegin
x300619_g_ScriptId =  300619
x300619_g_MissionKind 				= 	1                       --任务类型
x300619_g_Mis_Count = 1
x300619_g_LevelLess					= 	40 

x300619_g_ExtTarget					=	{ {type=20,n=10,target="马车"} }
x300619_g_BonusMoney8				=	100
x300619_g_GuildExpBonus				=	1
--MisDescEnd

--x300619_g_BangExp 					=	1

--要杀的怪的个数
x300619_g_NeedKilledNum				= 1

--任务与玩家等级对应关系
x300619_g_MisMatchingLevel = 	{
									{ sceneId = 5,monsterId = 1, level = 50 },
									{ sceneId = 6,monsterId = 0, level = 55 },
									{ sceneId = 7,monsterId = 1, level = 60 },
									{ sceneId = 8,monsterId = 1, level = 65 },
									{ sceneId = 9,monsterId = 0, level = 70 },
									{ sceneId = 10,monsterId = 1, level = 75 },
									{ sceneId = 11,monsterId = 1, level = 75 },
									{ sceneId = 13,monsterId = 0, level = 80 },
									{ sceneId = 16,monsterId = 1, level = 85 },
									{ sceneId = 17,monsterId = 0, level = 85 },
									{ sceneId = 18,monsterId = 0, level = 90 },
									{ sceneId = 19,monsterId = 0, level = 95 },
									{ sceneId = 20,monsterId = 0, level = 95 },
									{ sceneId = 21,monsterId = 0, level = 100 },
									{ sceneId = 22,monsterId = 0, level = 105 },
									{ sceneId = 23,monsterId = 0, level = 105 },
									{ sceneId = 24,monsterId = 0, level = 110 },
									{ sceneId = 25,monsterId = 0, level = 115 },
								}
x300619_g_SubMissionId				=	{--for all country
                                            --楼兰帮会除魔
											{ 
												  { MissionId=7004, MissionName = "【帮会】帮会除魔", MissionTarget = "  前往相应等级@npc_31121获得@item_13011603#W", MissionInfo = "\t我们通常会挑选一些帮众去完成除魔任务，前往领地打败不低于自己等级5级以上的任意一个魔君爪牙，夺回@item_13011603#W。\n\t此任务每天只能接取一次，放弃任务后只能在次日再次领取。\n\t当帮主发布#G除魔令#W时2小时内回复任务可获得翻倍奖励（经验，帮贡）和2点使命点，建帮时间低于24小时或入帮时间低于24小时，不能获得帮会经验！",MissionHelp = "\t这些凶徒非常危险，最好本帮成员组队共同前往除之！随着你所在帮会等级的提高，你获得的奖励也会相应增加。", SubmitNPCGUID = 123723,	ExpBonus = 0,NPCName = "@npc_123723",Completed ="你已经夺回了@item_13011603#W？太好了，这是你应得的报酬，请收下。",Missionruse="\t你可通过#G边塞#W的#G领地传送人#W前往领地，可通过#G场景地图（快捷键M）#W找到#G魔君爪牙的标志#W，杀死他带回恶魔面具吧！#G杀死魔君爪牙后，周围本帮成员均可获得恶魔面具！#r\t#R如果您的等级高于魔君爪牙5级以上，将无法完成任务！"}, 							
											},
                                            --天山帮会除魔
											{ 
												  { MissionId=7716, MissionName = "【帮会】帮会除魔", MissionTarget = "  前往相应等级@npc_31122获得@item_13011603#W", MissionInfo = "\t我们通常会挑选一些帮众去完成除魔任务，前往领地打败不低于自己等级5级以上的任意一个魔君爪牙，夺回@item_13011603#W。\n\t此任务每天只能接取一次，放弃任务后只能在次日再次领取。\n\t当帮主发布#G除魔令#W时2小时内回复任务可获得翻倍奖励（经验，帮贡）和2点使命点，建帮时间低于24小时或入帮时间低于24小时，不能获得帮会经验！",MissionHelp = "\t这些凶徒非常危险，最好本帮成员组队共同前往除之！随着你所在帮会等级的提高，你获得的奖励也会相应增加。", SubmitNPCGUID = 126020,	ExpBonus = 0,NPCName = "@npc_126020",Completed ="你已经夺回了@item_13011603#W？太好了，这是你应得的报酬，请收下。",Missionruse="\t你可通过#G边塞#W的#G领地传送人#W前往领地，可通过#G场景地图（快捷键M）#W找到#G魔君爪牙的标志#W，杀死他带回恶魔面具吧！#G杀死魔君爪牙后，周围本帮成员均可获得恶魔面具！#r\t#R如果您的等级高于魔君爪牙5级以上，将无法完成任务！"}, 							
											},
                                            --昆仑帮会除魔
											{ 
												  { MissionId=7710, MissionName = "【帮会】帮会除魔", MissionTarget = "  前往相应等级@npc_31123获得@item_13011603#W", MissionInfo = "\t我们通常会挑选一些帮众去完成除魔任务，前往领地打败不低于自己等级5级以上的任意一个魔君爪牙，夺回@item_13011603#W。\n\t此任务每天只能接取一次，放弃任务后只能在次日再次领取。\n\t当帮主发布#G除魔令#W时2小时内回复任务可获得翻倍奖励（经验，帮贡）和2点使命点，建帮时间低于24小时或入帮时间低于24小时，不能获得帮会经验！",MissionHelp = "\t这些凶徒非常危险，最好本帮成员组队共同前往除之！随着你所在帮会等级的提高，你获得的奖励也会相应增加。", SubmitNPCGUID = 129020,	ExpBonus = 0,NPCName = "@npc_129020",Completed ="你已经夺回了@item_13011603#W？太好了，这是你应得的报酬，请收下。",Missionruse="\t你可通过#G边塞#W的#G领地传送人#W前往领地，可通过#G场景地图（快捷键M）#W找到#G魔君爪牙的标志#W，杀死他带回恶魔面具吧！#G杀死魔君爪牙后，周围本帮成员均可获得恶魔面具！#r\t#R如果您的等级高于魔君爪牙5级以上，将无法完成任务！"}, 							
											},
                                            --敦煌帮会除魔
											{ 
												  { MissionId=7704, MissionName = "【帮会】帮会除魔", MissionTarget = "  前往相应等级@npc_31124获得@item_13011603#W", MissionInfo = "\t我们通常会挑选一些帮众去完成除魔任务，前往领地打败不低于自己等级5级以上的任意一个魔君爪牙，夺回@item_13011603#W。\n\t此任务每天只能接取一次，放弃任务后只能在次日再次领取。\n\t当帮主发布#G除魔令#W时2小时内回复任务可获得翻倍奖励（经验，帮贡）和2点使命点，建帮时间低于24小时或入帮时间低于24小时，不能获得帮会经验！",MissionHelp = "\t这些凶徒非常危险，最好本帮成员组队共同前往除之！随着你所在帮会等级的提高，你获得的奖励也会相应增加。", SubmitNPCGUID = 132020,	ExpBonus = 0,NPCName = "@npc_132020",Completed ="你已经夺回了@item_13011603#W？太好了，这是你应得的报酬，请收下。",Missionruse="\t你可通过#G边塞#W的#G领地传送人#W前往领地，可通过#G场景地图（快捷键M）#W找到#G魔君爪牙的标志#W，杀死他带回恶魔面具吧！#G杀死魔君爪牙后，周围本帮成员均可获得恶魔面具！#r\t#R如果您的等级高于魔君爪牙5级以上，将无法完成任务！"}, 							
											},
										}

-- 帮会速成任务
x300619_g_SuchengMissionId = {7784, 7785, 7786, 7787}


function x300619_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

	local nCountry = GetCurCountry( sceneId, selfId )

	for i,itm in x300619_g_SubMissionId[nCountry+1] do
		if IsHaveQuestNM( sceneId, selfId, itm.MissionId ) > 0 then	-- 如果有这个任务
			return 0
		end
	end
	if GetGuildID( sceneId, selfId ) == -1 then
		--不在帮会中
		return
	end
	local Level = GetLevel(sceneId, selfId)
	if Level >= 40  then	-- 如果可以接这个任务
		local state = GetQuestStateNM( sceneId, selfId, targetId, MissionId);
		AddQuestTextNM( sceneId, selfId, targetId, MissionId, 8, state ) -- 显示任务信息
		--AddQuestNumText( sceneId, MissionId, "【帮会】帮会除魔", state);
		return 1
	end
	
end


--选中任务
function x300619_ProcEventEntry( sceneId, selfId, targetId, MissionId )

	local nCountry = GetCurCountry( sceneId, selfId )

	local index = 1
	local IsHaveQuest = 0
	
	
	for i,itm in x300619_g_SubMissionId[nCountry+1] do
		if IsHaveQuestNM( sceneId, selfId, itm.MissionId ) > 0 then	-- 如果有这个任务
	
			IsHaveQuest = 1
			MissionId = itm.MissionId
			--index = i
			break
		end
	end

	if(IsHaveQuest > 0) then
		local bDone = x300619_CheckSubmit(sceneId, selfId, MissionId);
		if(bDone > 0) then
			x300619_DispatchCompletedInfo( sceneId, selfId, targetId,index) --完成任务显示
		else
			x300619_DispatchContinueInfo( sceneId, selfId, targetId,index ) --未完成任务显示
		end
	else
	
		local day =  mod(GetDayTime(),1000) + GetGuildID( sceneId, selfId )

		if day < 0 then
			day = 0
		end

		-- index =  mod(day,6)
		-- index = index + 1

--		 local num = random(1,60)
--		 if num <= 10 then
--			 index = 1
--		 elseif num <= 20 then
--			 index = 2
--		 elseif num <= 30 then
--			 index = 3
--		 elseif num <= 40 then
--			 index = 4
--		 elseif num <= 50 then
--			 index = 5
--		 else  
--			index = 6
--		 end

		x300619_DispatchMissionInfo( sceneId, selfId, targetId,index )		--任务信息显示
	end

end

---------------------------------------------------------------------------------------------------
--检查任务是否可提交
---------------------------------------------------------------------------------------------------
function x300619_CheckSubmit(sceneId, selfId,MissionId)

	local misIndex = GetQuestIndexByID(sceneId, selfId, MissionId);
	local Needitem = GetItemCountInBag(sceneId,selfId,13011603)
	return GetQuestParam(sceneId, selfId, misIndex, 7);
	

end


---------------------------------------------------------------------------------------------------
--向客户端发送任务完成信息
---------------------------------------------------------------------------------------------------
function x300619_DispatchCompletedInfo( sceneId, selfId, targetId,index )
	
	BeginQuestEvent(sceneId)

	    local nCountry = GetCurCountry( sceneId, selfId )

		--任务完成信息
		AddQuestText(sceneId,"#Y"..x300619_g_SubMissionId[nCountry+1][index].MissionName)
		AddQuestText(sceneId,x300619_g_SubMissionId[nCountry+1][index].Completed)
		AddQuestText(sceneId," ")

		--1、经验
		local level = GetLevel(sceneId, selfId)
		--local gongdezhi =GetMeritInfo_Multiple(sceneId, selfId)
		local ExpBonus = ceil ( (100 * 3 * level * 15*1*1 ) )
		ExpBonus =floor(ExpBonus+0.5)
		if ExpBonus> 0 then
			AddQuestExpBonus(sceneId, ExpBonus )
		end
		--2 帮供
		if x300619_g_BonusMoney8>0 then
			AddQuestMoneyBonus8(sceneId,x300619_g_BonusMoney8)
		end
		--3 帮会经验
		if x300619_g_GuildExpBonus>0 then
			AddQuestGuildExpBonus(sceneId,x300619_g_GuildExpBonus)
		end
		EndQuestEvent(sceneId)
		DispatchQuestContinueInfoNM(sceneId, selfId, targetId, x300619_g_ScriptId, x300619_g_SubMissionId[nCountry+1][index].MissionId);
   
end



---------------------------------------------------------------------------------------------------
--向客户端发送任务未完成
---------------------------------------------------------------------------------------------------
function x300619_DispatchContinueInfo( sceneId, selfId, targetId,index )
	
	BeginQuestEvent(sceneId)

    	local nCountry = GetCurCountry( sceneId, selfId )
    	
		--任务继续信息
		AddQuestText(sceneId,"#Y"..x300619_g_SubMissionId[nCountry+1][index].MissionName)
		AddQuestText(sceneId,format("%s", x300619_g_SubMissionId[nCountry+1][index].MissionInfo))
		AddQuestText(sceneId," ")

		--任务目标
		AddQuestText( sceneId,"#Y完成情况：")
		AddQuestText(sceneId, "未完成");

		--1、经验
		local level = GetLevel(sceneId, selfId)
		--local gongdezhi =GetMeritInfo_Multiple(sceneId, selfId)
		local ExpBonus = ceil ( (100 * 3 * level * 15*1*1 ) )
		ExpBonus =floor(ExpBonus+0.5)
		if ExpBonus> 0 then
			AddQuestExpBonus(sceneId, ExpBonus )
		end
		
		--2 经验
		if x300619_g_BonusMoney8>0 then
			AddQuestMoneyBonus8(sceneId,x300619_g_BonusMoney8)
		end
		--3 帮会经验
		if x300619_g_GuildExpBonus>0 then
			AddQuestGuildExpBonus(sceneId,x300619_g_GuildExpBonus)
		end

		
	--任务提示信息
	EndQuestEvent()

	DispatchQuestDemandInfo(sceneId, selfId, targetId, x300619_g_ScriptId, x300619_g_SubMissionId[nCountry+1][index].MissionId,0);

end


---------------------------------------------------------------------------------------------------
--向客户端发送任务信息
---------------------------------------------------------------------------------------------------
function x300619_DispatchMissionInfo( sceneId, selfId, NPCId,index )

	BeginQuestEvent(sceneId)

		--任务信息
		local BangExp =x300619_g_BangExp
		local nCountry = GetCurCountry( sceneId, selfId )
		AddQuestText(sceneId,"#Y"..x300619_g_SubMissionId[nCountry+1][index].MissionName)
		AddQuestText(sceneId,format("%s", x300619_g_SubMissionId[nCountry+1][index].MissionInfo))
		AddQuestText(sceneId," ")

		--任务目标
		AddQuestText( sceneId,"#Y任务目标：")
		AddQuestText( sceneId,format("%s", x300619_g_SubMissionId[nCountry+1][index].MissionTarget))
		AddQuestText( sceneId," ")

		--提示信息
		if x300619_g_SubMissionId[nCountry+1][index].MissionHelp ~= "" then

			AddQuestText(sceneId,"#Y任务提示：")
			AddQuestText(sceneId,format("%s", x300619_g_SubMissionId[nCountry+1][index].MissionHelp))
			AddQuestText(sceneId," ")
		end

		--任务奖励信息

		--1、经验
		local level = GetLevel(sceneId, selfId)
		--local gongdezhi =GetMeritInfo_Multiple(sceneId, selfId)
		local ExpBonus = ceil ( (100 * 3 * level * 15*1*1 ) )
		ExpBonus =floor(ExpBonus+0.5)
		if ExpBonus > 0 then
			AddQuestExpBonus(sceneId, ExpBonus )
		end
		
		--2 帮供
		if x300619_g_BonusMoney8>0 then
			AddQuestMoneyBonus8(sceneId,x300619_g_BonusMoney8)
		end
		--3 帮会经验
		if x300619_g_GuildExpBonus>0 then
			AddQuestGuildExpBonus(sceneId,x300619_g_GuildExpBonus)
		end
		EndQuestEvent(sceneId)
		DispatchQuestInfoNM(sceneId, selfId, NPCId, x300619_g_ScriptId, x300619_g_SubMissionId[nCountry+1][index].MissionId);
		
end


---------------------------------------------------------------------------------------------------
--获得奖励
---------------------------------------------------------------------------------------------------
function x300619_OnReturn1(sceneId, selfId,MissionData,MissionId,targetId)
	local curTime = GetCurrentTime()
	local isMultiple = 0
	if curTime - MissionData < 2*60*60 then
		isMultiple = 1
	end
	
	local joinguildtime = MissionId
	
	x300619_GetBonus( sceneId,selfId, isMultiple, joinguildtime )
end

function x300619_GetBonus( sceneId, selfId,isMultiple,joinguildtime)
	--奖励经验
	local level = GetLevel(sceneId, selfId)
	--local gongdezhi =GetMeritInfo_Multiple(sceneId, selfId)
	local ExpBonus = ceil ( (100 * 3 * level * 15*1*1 ) )
	ExpBonus =floor(ExpBonus+0.5)
	local GuildLevel = GetGuildSimpleData(GetGuildID( sceneId, selfId ))--得到帮会简单数据(等级) 
    if ExpBonus > 0 then
        local text1 = "你完成了任务：【帮会】帮会除魔"
    	local text2 = "获得#R经验"..ExpBonus.."点#o的奖励"
		local text3 = "获得#R帮会功德1点#o的奖励"
    	--AddGuildMerit(sceneId, selfId,1)   
		AddExp(sceneId, selfId, ExpBonus);
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, text1);
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)	
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, text2);
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		-- BeginQuestEvent(sceneId)
		-- AddQuestText(sceneId, text3);
		-- EndQuestEvent(sceneId)
		-- DispatchQuestTips(sceneId,selfId)
  		Msg2Player(sceneId,selfId,text1,8,2)
  		Msg2Player(sceneId,selfId,text2,8,2)
		--Msg2Player(sceneId,selfId,text3,8,2)
		if isMultiple == 1 then
			local ExpBonus1 = ceil (100 * 3 * level * 15*1*1 *3)
			local Exp3 = ceil (100 * 3 * level * 15*1*1*3 )
			local ExpBonus2 = ceil (100 * 3 * level * 15*1*1 *2)
			local pos = GetGuildOfficial(sceneId, selfId)
			local text3 = "获得#R使命点2点#o的奖励"
				AddGuildShiMing(sceneId, selfId,2)
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId, text3);
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)	
				Msg2Player(sceneId,selfId,text3,8,2)
			if pos == 5 then
				local guildid =GetGuildID(sceneId, selfId)
				if  GetGuildCacheFreeParam(guildid,GD_GUILD_INDEX_CHIEF_MULTIMISSION_DAY) == GetDayOfYear() then
					BeginQuestEvent(sceneId)
					AddQuestText(sceneId, "帮主职位只能领取一次除魔令奖励");
					EndQuestEvent(sceneId)
					DispatchQuestTips(sceneId,selfId)
					Msg2Player(sceneId,selfId,"帮主职位只能领取一次除魔令奖励",8,2)
				else
					AddExp(sceneId, selfId, ExpBonus1);	
					BeginQuestEvent(sceneId)
					AddQuestText(sceneId, "额外获得#R经验"..Exp3.."点#o的奖励");
					EndQuestEvent(sceneId)
					DispatchQuestTips(sceneId,selfId)	
					Msg2Player(sceneId,selfId,"帮会多倍任务额外获得#R经验"..Exp3.."点#o的奖励",8,2)
					SetGuildQuestData(sceneId,GetGuildID(sceneId,selfId),GD_GUILD_INDEX_CHIEF_MULTIMISSION_DAY,GetDayOfYear(),0)
				end
			elseif pos == 4 then
				local guildid =GetGuildID(sceneId, selfId)
				if  GetGuildCacheFreeParam(guildid,GD_GUILD_INDEX_ASSCHIEF_MULTIMISSION_DAY) == GetDayOfYear() then
					BeginQuestEvent(sceneId)
					AddQuestText(sceneId, "副帮主职位只能领取一次除魔令奖励");
					EndQuestEvent(sceneId)
					DispatchQuestTips(sceneId,selfId)
					Msg2Player(sceneId,selfId,"副帮主职位只能领取一次除魔令奖励",8,2)
				else
					AddExp(sceneId, selfId, ExpBonus2);	
					BeginQuestEvent(sceneId)
					AddQuestText(sceneId, "额外获得#R经验"..ExpBonus2.."点#o的奖励");
					EndQuestEvent(sceneId)
					DispatchQuestTips(sceneId,selfId)	
					Msg2Player(sceneId,selfId,"帮会多倍任务额外获得#R经验"..ExpBonus2.."点#o的奖励",8,2)
					SetGuildQuestData(sceneId,GetGuildID(sceneId,selfId),GD_GUILD_INDEX_ASSCHIEF_MULTIMISSION_DAY,GetDayOfYear(),0)
				end
			else
				AddExp(sceneId, selfId, ExpBonus);	
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId, "额外获得#R经验"..ExpBonus.."点#o的奖励");
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)	
				Msg2Player(sceneId,selfId,"帮会多倍任务额外获得#R经验"..ExpBonus.."点#o的奖励",8,2)
			end
		end
		if 	GuildLevel == 2 then
			local level = GetLevel(sceneId, selfId)
			local exp = ceil (100 * 3 * level * 15*0.25*1 )
			AddExp(sceneId, selfId, exp);
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, "额外获得#R经验"..exp.."点#o的奖励");
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)	
			Msg2Player(sceneId,selfId,"帮会等级2级额外获得#R经验"..exp.."点#o的奖励",8,2)
		end
		if 	GuildLevel == 3 then
			local level = GetLevel(sceneId, selfId)
			local exp = ceil (100 * 3 * level * 15*0.5*1 )
			AddExp(sceneId, selfId, exp);	
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, "额外获得#R经验"..exp.."点#o的奖励");
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)	
			Msg2Player(sceneId,selfId,"帮会等级3级额外获得#R经验"..exp.."点#o的奖励",8,2)
		end
		if 	GuildLevel == 4 then
			local level = GetLevel(sceneId, selfId)
			local exp = ceil (100 * 3 * level * 15*0.75*1 )
			AddExp(sceneId, selfId, exp);	
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, "额外获得#R经验"..exp.."点#o的奖励");
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)	
			Msg2Player(sceneId,selfId,"帮会等级4级额外获得#R经验"..exp.."点#o的奖励",8,2)
		end
		if 	GuildLevel == 5 then
			local level = GetLevel(sceneId, selfId)
			local exp = ceil (100 * 3 * level * 15*1*1 )
			AddExp(sceneId, selfId, exp);	
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, "额外获得#R经验"..exp.."点#o的奖励");
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)	
			Msg2Player(sceneId,selfId,"帮会等级5级额外获得#R经验"..exp.."点#o的奖励",8,2)
		end
		if 	GuildLevel == 6 then
			local level = GetLevel(sceneId, selfId)
			local exp = ceil (100 * 3 * level * 20*1.25*1 )
			AddExp(sceneId, selfId, exp);	
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, "额外获得#R经验"..exp.."点#o的奖励");
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)	
			Msg2Player(sceneId,selfId,"帮会等级6级额外获得#R经验"..exp.."点#o的奖励",8,2)
		end
		if 	GuildLevel == 7 then
			local level = GetLevel(sceneId, selfId)
			local exp = ceil (100 * 3 * level * 20*1.5*1 )
			AddExp(sceneId, selfId, exp);	
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, "额外获得#R经验"..exp.."点#o的奖励");
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)	
			Msg2Player(sceneId,selfId,"帮会等级7级额外获得#R经验"..exp.."点#o的奖励",8,2)
		end
	end
--奖励帮贡
    if x300619_g_BonusMoney8 > 0 then
		AddGuildUserPoint(sceneId,selfId,x300619_g_BonusMoney8)	--增加帮贡
		local BonusMoney8 = x300619_g_BonusMoney8
		local pointText = "获得#R帮贡"..BonusMoney8.."点#o的奖励"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, pointText);
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)			
  		Msg2Player(sceneId,selfId,pointText,8,2)
		if isMultiple == 1 then
			local pos = GetGuildOfficial(sceneId, selfId)
			if pos == 5 then
				local guildid =GetGuildID(sceneId, selfId)
				if  GetGuildCacheFreeParam(guildid,GD_GUILD_INDEX_CHIEF_MULTIMISSION_DAY) == GetDayOfYear() then
					BeginQuestEvent(sceneId)
					AddQuestText(sceneId, "帮主职位只能领取一次除魔令奖励");
					EndQuestEvent(sceneId)
					DispatchQuestTips(sceneId,selfId)
					Msg2Player(sceneId,selfId,"帮主职位只能领取一次除魔令奖励",8,2)
				else
					AddGuildUserPoint(sceneId,selfId,300)	--增加帮贡
					BeginQuestEvent(sceneId)
					AddQuestText(sceneId, "额外获得#R帮贡300点#o的奖励");
					EndQuestEvent(sceneId)
					DispatchQuestTips(sceneId,selfId)	
					Msg2Player(sceneId,selfId,"帮会多倍任务额外获得#R帮贡300点#o的奖励",8,2)
					SetGuildQuestData(sceneId,GetGuildID(sceneId,selfId),GD_GUILD_INDEX_CHIEF_MULTIMISSION_DAY,GetDayOfYear(),0)
				end
			elseif pos == 4 then
				local guildid =GetGuildID(sceneId, selfId)
				if  GetGuildCacheFreeParam(guildid,GD_GUILD_INDEX_ASSCHIEF_MULTIMISSION_DAY) == GetDayOfYear() then
					BeginQuestEvent(sceneId)
					AddQuestText(sceneId, "副帮主职位只能领取一次除魔令奖励");
					EndQuestEvent(sceneId)
					DispatchQuestTips(sceneId,selfId)
					Msg2Player(sceneId,selfId,"副帮主职位只能领取一次除魔令奖励",8,2)
				else
					AddGuildUserPoint(sceneId,selfId,200)	--增加帮贡
					BeginQuestEvent(sceneId)
					AddQuestText(sceneId, "额外获得#R帮贡200点#o的奖励");
					EndQuestEvent(sceneId)
					DispatchQuestTips(sceneId,selfId)	
					Msg2Player(sceneId,selfId,"帮会多倍任务额外获得#R帮贡200点#o的奖励",8,2)
					SetGuildQuestData(sceneId,GetGuildID(sceneId,selfId),GD_GUILD_INDEX_ASSCHIEF_MULTIMISSION_DAY,GetDayOfYear(),0)
				end
			else
				AddGuildUserPoint(sceneId,selfId,100)	--增加帮贡
				local BonusMoney8 = x300619_g_BonusMoney8
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId, "额外获得#R帮贡"..BonusMoney8.."点#o的奖励");
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)	
				Msg2Player(sceneId,selfId,format("帮会多倍任务额外获得#R帮贡"..BonusMoney8.."点#o的奖励", x300619_g_BonusMoney8),8,2)
			end
		end
	end
-- 奖励帮会经验
	local bangExp = x300619_g_GuildExpBonus 
	if bangExp > 0 then
		if joinguildtime == -1 or GetCurrentTime()-joinguildtime<24*3600 then
			BeginQuestEvent(sceneId)
			AddQuestText( sceneId, "很抱歉，您加入帮会时间低于24小时，不能获得帮会经验。" )
			EndQuestEvent( sceneId )
			DispatchQuestTips( sceneId, selfId )
			Msg2Player(sceneId,selfId,"很抱歉，您加入帮会时间低于24小时，不能获得帮会经验。",8,2)
			return
		end
		--local gongde = GetGuildMerit(sceneId, selfId)
			local name = GetName(sceneId, selfId)
		--if 	gongde >= 5 then
			AddGuildExp(sceneId,selfId,bangExp)
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, "获得#R帮会经验"..bangExp.."点#o的奖励");
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)			
			Msg2Player(sceneId,selfId,format("获得#R帮会经验"..bangExp.."点#o的奖励"),8,2)
			Msg2Player(sceneId,selfId,format("帮会："..name.."完成了【帮会】帮会除魔任务，为帮会贡献了"..bangExp.."点帮会经验。"),6,2)
		-- else
			-- BeginQuestEvent(sceneId)
			-- AddQuestText( sceneId, "很抱歉，帮会功德低于5点，不能获得帮会经验。" )
			-- EndQuestEvent( sceneId )
			-- DispatchQuestTips( sceneId, selfId )
			-- Msg2Player(sceneId,selfId,"很抱歉，帮会功德低于5点，不能获得帮会经验。",8,2)
		-- end
	end
		
end



--**********************************
--接受
--**********************************
function x300619_ProcQuestAccept( sceneId, selfId, targetId, MissionId )

	if IsQuestFullNM( sceneId, selfId )==1 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"可接任务数量已满")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return 
	end

	if GetGuildID( sceneId, selfId ) == -1 then
		--不在帮会中
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "你不是帮会成员，请先加入帮会再来领取！");
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)	
		Msg2Player(sceneId,selfId,"你不是帮会成员，请先加入帮会再来领取！",8,2)
		return
	end
	
	local guildid = GetGuildID( sceneId, selfId )
	local GuildLevel = GetGuildSimpleData(guildid)--得到帮会简单数据(等级)
	if 	GuildLevel < 1 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "很抱歉，帮会等级到达3级才可以接取帮会除魔任务！");
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)	
		Msg2Player(sceneId,selfId,"很抱歉，帮会等级到达3级才可以接取帮会除魔任务！",8,2)
	return 
	end
	
	if x300619_GetDayCount(sceneId, selfId) >= x300619_g_Mis_Count then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "你今天已经领取过帮会除魔任务了，请明天再来吧！");
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		local Readme = "你今天已经领取过帮会除魔任务了，请明天再来吧！"
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
	
	if AddQuestNM( sceneId, selfId,MissionId) == 1 then
 
		BeginQuestEvent(sceneId)
		--接任务写日志
		GamePlayScriptLog(sceneId,selfId,111)

 		AddQuestText(sceneId, "你接受了任务：【帮会】帮会除魔")
 		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		local Readme = "你接受了任务：【帮会】帮会除魔"
		Msg2Player(sceneId,selfId,Readme,8,2)	

		local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )
		SetQuestByIndex(sceneId, selfId, misIndex, 7, 0);
		SetQuestByIndex(sceneId, selfId, misIndex, 0, 0);
	end
	
end


--完成任务
--返回1代表成功，0代表交任务失败
function x300619_ProcQuestSubmit( sceneId, selfId, targetId, selectId, MissionId )
	
	if IsHaveQuestNM( sceneId, selfId, MissionId) == 0 then	-- 如果没这个任务直接退出
		return 0
	end
	local Needitem = GetItemCountInBag(sceneId,selfId,13011603)
	if Needitem < 1 then
	BeginQuestEvent(sceneId)
 	AddQuestText(sceneId, "很抱歉，您身上没有@item_13011603")
 	EndQuestEvent(sceneId)
	DispatchQuestTips(sceneId,selfId)
	local Readme = "很抱歉，您身上没有@item_13011603"
	Msg2Player(sceneId,selfId,Readme,8,2)
	return
	end
	if DelQuestNM( sceneId, selfId, MissionId) < 1 then
		return 
	end

    -- 增加活跃度
    local id = GetGuildID( sceneId, selfId)
    if id ~= -1 then
        AddGuildActivity( sceneId, selfId, GetGuildCacheFreeParam( id, GD_GUILD_ACTIVITY_PARAM2) )
    end

	 local country = GetCurCountry(sceneId, selfId)
			if country == 0 then 
				CallScriptFunction( 256264, "Finishchuyao", sceneId, selfId)
			elseif country == 1 then
				CallScriptFunction( 256265, "Finishchuyao", sceneId, selfId)
			elseif country == 2 then
				CallScriptFunction( 256266, "Finishchuyao", sceneId, selfId)
			elseif country == 3 then
				CallScriptFunction( 256267, "Finishchuyao", sceneId, selfId)
			end
	--交任务写日志
	GamePlayScriptLog(sceneId,selfId,112)

	x300619_SetDayCount(sceneId, selfId)
	BeginQuestEvent(sceneId)
	AddQuestText(sceneId, "");
	EndQuestEvent(sceneId)
	DispatchQuestTips(sceneId,selfId)
	--GetGuildQuestData(sceneId, selfId, GD_GUILD_INDEX_MULTI_MISSION_CHUYAO, x300619_g_ScriptId,MissionId,"OnReturn1",targetId)
	GetJoinGuildTime(sceneId,selfId,x300619_g_ScriptId)
	DelItem(sceneId, selfId, 13011603, 1)
	return 0
end

function x300619_OnMemberJoinTimeReturn( sceneId, selfId, param )

	GetGuildQuestData(sceneId, selfId, GD_GUILD_INDEX_MULTI_MISSION_CHUYAO, x300619_g_ScriptId,param,"OnReturn1",-1)

end

function x300619_ProcQuestAttach( sceneId, selfId, npcId, npcGuid,misIndex, MissionId )

	local nCountry = GetCurCountry( sceneId, selfId )

	for i,itm in x300619_g_SubMissionId[nCountry+1] do
		local bHaveMission = IsHaveQuestNM(sceneId, selfId,itm.MissionId );

		if bHaveMission > 0 then
			if npcGuid == itm.SubmitNPCGUID then
				local Needitem = GetItemCountInBag(sceneId,selfId,13011603)
				if Needitem >= 1 then
					local state = GetQuestStateNM(sceneId,selfId,npcId,itm.MissionId)
					AddQuestNumText(sceneId, itm.MissionId, itm.MissionName,7,state);
				else
					local state = GetQuestStateNM(sceneId,selfId,npcId,itm.MissionId)
					AddQuestNumText(sceneId, itm.MissionId, itm.MissionName,6,state);
				end
				break;
			end
		end
	end

end




--********************************************************************
--放弃
--********************************************************************
function x300619_ProcQuestAbandon( sceneId, selfId,MissionId )

	if IsHaveQuestNM( sceneId, selfId, MissionId) == 0 then	-- 如果没有这个任务
		return
	end

	DelQuestNM( sceneId, selfId, MissionId)
	local Readme = "你放弃了任务：【帮会】帮会除魔"
	BeginQuestEvent(sceneId)
	AddQuestText(sceneId, Readme);
    EndQuestEvent(sceneId)
	DispatchQuestTips(sceneId,selfId)
	Msg2Player(sceneId,selfId,Readme,8,2)
	x300619_SetDayCount(sceneId, selfId)
	DelItem(sceneId, selfId, 13011603,1)
end


function x300619_OnReturn(sceneId, selfId,MissionData,MissionId,targetId)

	local CurDaytime = GetDayTime()						--当前时间(天)

 		                                                  --可以做任务
 		BeginQuestEvent(sceneId)
 		AddQuestText(sceneId, "接受帮会除魔任务成功，快去做吧！")
 		EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
			local Readme = "接受帮会除魔任务成功，快去做吧！"
			Msg2Player(sceneId,selfId,Readme,8,2)
		AddQuestNM( sceneId, selfId,MissionId)
	--else
	    --BeginQuestEvent(sceneId)
		--AddQuestText(sceneId, "帮会今天还没有发布该任务！")
		--EndQuestEvent(sceneId)
		--	DispatchQuestTips(sceneId,selfId)
			--local Readme = "帮会今天还没有发布该任务！"
			--Msg2Player(sceneId,selfId,Readme,8,2)
		--DispatchQuestTips(sceneId,selfId)
	--end

  --  DispatchQuestEventList(sceneId, selfId, -1)
end


--********************************************************************
--接受
--********************************************************************
function x300619_ProcAccept( sceneId, selfId )
end

function x300619_IsValidOnDie( sceneId,objId,killerId )
	
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

function x300619_DoMySelfMisState( sceneId,objId,killerId )

	local MissionId = -1
	local nCountry = GetCurCountry( sceneId, killerId )
 	for i,itm in x300619_g_SubMissionId[nCountry+1] do
		if IsHaveQuestNM( sceneId, killerId, itm.MissionId ) > 0 then	-- 如果有这个任务
			MissionId = itm.MissionId
			break
		end
	end

	local SuchengMissionId = -1;
	if IsHaveQuestNM( sceneId, killerId, x300619_g_SuchengMissionId[nCountry+1] ) > 0 then 
		SuchengMissionId = x300619_g_SuchengMissionId[nCountry+1]
	end
	
	local strText = "";
	if MissionId == -1 and SuchengMissionId == -1  then
		
		return
		
	end

	local isOk = 0
	
	for i,itm in x300619_g_MisMatchingLevel do
		if sceneId == itm.sceneId and GetLevel(sceneId,killerId) <= itm.level and objId == itm.monsterId then
			isOk = 1
		end		
	end
	
	if isOk == 0 then
		--不是要杀的怪
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"您的等级过高");
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,killerId)
		Msg2Player(sceneId,killerId,"很抱歉，您的等级过高，请到更高等级的地图完成任务",8,2)
		return
	end
	
	--先算自己的任务数据qq
	if SuchengMissionId ~= -1 then
		local MemberMisIndex2 = GetQuestIndexByID( sceneId, killerId, SuchengMissionId )
		SetQuestByIndex(sceneId, killerId, MemberMisIndex2, 0, 1)
		SetQuestByIndex(sceneId, killerId, MemberMisIndex2, 7, 1)
	end
	
	if MissionId == -1 then
		return
	end
	
	--先算自己的任务数据qq
	local MemberMisIndex = GetQuestIndexByID( sceneId, killerId, MissionId )
	local MemberKilledNum = GetQuestParam( sceneId, killerId, MemberMisIndex, 0 )
	local Needitem = GetItemCountInBag(sceneId,killerId,13011603)
	local item = 0
	if Needitem < 1 then	
		BeginAddItem(sceneId)
		AddItem( sceneId, 13011603 , 1 )
		local ret = EndAddItem(sceneId,killerId)
		if ret > 0 then
			AddItemListToPlayer(sceneId,killerId)
			local Name = GetName(sceneId,killerId)
			local Readme = "#G"..Name.."#o获得了恶魔面具！"
			LuaScenceM2Near(sceneId,killerId,Readme,CHAT_RIGHTDOWN,1)	
			x300619_QuestLogRefresh( sceneId, killerId, MissionId)
			SetQuestByIndex(sceneId, killerId, MemberMisIndex, 7, 1);
		else
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"物品栏已满，无法获得恶魔面具！");
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,killerId)
			Msg2Player(sceneId,killerId,"物品栏已满，无法获得恶魔面具！",8,2)
		end	
	else
		Msg2Player(sceneId,killerId,"您已经获得恶魔面具！",8,2)
	end

end

function x300619_DoOtherMisState( sceneId,objId,member )

	local nLevel = GetLevel(sceneId, member)
	local MissionId = -1
	local nCountry = GetCurCountry( sceneId, member )
	
	for n,itm in x300619_g_SubMissionId[nCountry+1] do
	
		if IsHaveQuestNM( sceneId, member, itm.MissionId ) > 0 then	-- 如果有这个任务
			MissionId = itm.MissionId
			break
		end
		
	end
	
	local SuchengMissionId = -1;
	print ("x300619_g_SuchengMissionId[nCountry+1]", x300619_g_SuchengMissionId[nCountry+1])
	if IsHaveQuestNM( sceneId, member, x300619_g_SuchengMissionId[nCountry+1] ) > 0 then 
		SuchengMissionId = x300619_g_SuchengMissionId[nCountry+1]
	end
	
	if  MissionId == -1 and SuchengMissionId == -1 then
		return
	end
	
	if GetHp(sceneId, member) <= 0 then
		return
	end
	
	local isOk = 0
	
	for i,itm in x300619_g_MisMatchingLevel do
		if sceneId == itm.sceneId and GetLevel(sceneId,member) <= itm.level and objId == itm.monsterId then
			isOk = 1
		end		
	end
	
	if isOk == 0 then
		--不是要杀的怪
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"您的等级过高");
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,member)
		Msg2Player(sceneId,member,"很抱歉，您的等级过高，请到更高等级的地图完成任务",8,2)
		return
	end
	
	if SuchengMissionId ~= -1 then
		local MemberMisIndex2 = GetQuestIndexByID( sceneId, member, SuchengMissionId )
		SetQuestByIndex(sceneId, member, MemberMisIndex2, 0, 1)
		SetQuestByIndex(sceneId, member, MemberMisIndex2, 7, 1)
	end
	
	if MissionId == -1 then
		return
	end
	
	local MemberMisIndex = GetQuestIndexByID( sceneId, member, MissionId )
	local MemberKilledNum = GetQuestParam( sceneId, member, MemberMisIndex, 0 )
	local Needitem = GetItemCountInBag(sceneId,member,13011603)
	
	if Needitem < 1 then
	
		BeginAddItem(sceneId)
		AddItem( sceneId, 13011603 , 1 )
		local ret = EndAddItem(sceneId,member)
		if ret > 0 then
			AddItemListToPlayer(sceneId,member)
			local Name = GetName(sceneId,member)
			local Readme = "#G"..Name.."#o获得了恶魔面具！"
			LuaScenceM2Near(sceneId,member,Readme,CHAT_RIGHTDOWN,1)
			SetQuestByIndex(sceneId, member, MemberMisIndex, 7, 1);
		else
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"物品栏已满，无法获得恶魔面具！");
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,member)
			Msg2Player(sceneId,member,"物品栏已满，无法获得恶魔面具！",8,2)
		end
	else
		Msg2Player(sceneId,member,"您已经获得恶魔面具！",8,2)
	end
		
end

function x300619_OnDie( sceneId,objId,killerId )

	local ObjType = GetObjType(sceneId,killerId)
	if ObjType == 3 then		-- 被PET杀死
		ObjType = 1
		killerId = GetOwnerID(sceneId, killerId)
	end

	if x300619_IsValidOnDie( sceneId,objId,killerId ) == 0 then
		
		--不合法
		return
		
	end

	x300619_DoMySelfMisState( sceneId,objId,killerId )
	
	if GetGuildID(sceneId, killerId) == -1  then		--不在帮会或中，只判断自己是否有任务
		return 
	end

	--算同帮同队成员任务数
	local x,z = GetWorldPos(sceneId,killerId)
	local num =  GetNearPlayerCount(sceneId, killerId,x,z,30)
	if num <= 0 then
		return
	end
	
	for	i=0,num-1 do
			
		local member = GetNearPlayerMember(sceneId, killerId,i)	
		if member ~= -1 and member ~= killerId and GetGuildID(sceneId, member) == GetGuildID(sceneId, killerId) and IsPlayerStateNormal( sceneId,member ) == 1 then
			if member ~= killerId then
				x300619_DoOtherMisState( sceneId,objId,member )
			end
		end 
	end
	
end


--杀死怪物
function x300619_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
						   --场景ID, 自己的ID, 怪物表位置号, 怪物objId, 任务ID

end



---------------------------------------------------------------------------------------------------
--任务日志刷新
---------------------------------------------------------------------------------------------------
function x300619_QuestLogRefresh( sceneId, selfId, MissionId)
	local nCountry = GetCurCountry( sceneId, selfId )
	for i,itm in x300619_g_SubMissionId[nCountry+1] do 
		local bHaveMission = IsHaveQuestNM(sceneId, selfId,itm.MissionId );
		if bHaveMission > 0 then
		
			BeginQuestEvent(sceneId)	
			local level = GetLevel(sceneId, selfId)
			--local gongdezhi =GetMeritInfo_Multiple(sceneId, selfId)
			local ExpBonus = ceil ( (100 * 3 * level * 15*1*1 ) )
			ExpBonus =floor(ExpBonus+0.5)
			if ExpBonus > 0 then
			AddQuestExpBonus(sceneId, ExpBonus);		
			end
			if x300619_g_BonusMoney8 > 0 then
			AddQuestMoneyBonus8(sceneId, x300619_g_BonusMoney8 )	--增加帮贡
			end
			if x300619_g_GuildExpBonus>0 then
			AddQuestGuildExpBonus(sceneId,x300619_g_GuildExpBonus)
			end

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
									"每张领地地图都有一个魔君的爪牙，请根据自身等级进行选择。随着你所在帮会等级的提高，你获得的奖励也会相应增加。"					--任务小提示
									)
			EndQuestEvent(sceneId)
			DispatchQuestLogUpdate(sceneId, selfId, itm.MissionId);
		end
		break
	end
end

function x300619_ProcQuestLogRefresh( sceneId, selfId, MissionId)

	x300619_QuestLogRefresh( sceneId, selfId, MissionId );
end

---------------------------------------------------------------------------------------------------
--取得此任务当天当前已完成次数
---------------------------------------------------------------------------------------------------
function x300619_GetDayCount(sceneId, selfId)

	if x300619_g_Mis_Count > 0 then

		local today = GetDayOfYear()

		local lastday = GetQuestData(sceneId, selfId, MD_GUILD_KILLMONSTER_DATE[1], MD_GUILD_KILLMONSTER_DATE[2], MD_GUILD_KILLMONSTER_DATE[3])

		if lastday ~= today then
			return 0
		end

		local daycount =  GetQuestData(sceneId, selfId, MD_GUILD_KILLMONSTER_COUNT[1], MD_GUILD_KILLMONSTER_COUNT[2], MD_GUILD_KILLMONSTER_COUNT[3])
		return daycount

	end

	return 0
end
--物品改变
function x300619_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId, nChangeType )
	local NeedNum, ObjIndex = GetQuestNeedItemNumNM( sceneId, selfId, MissionId, itemdataId )
	local MemberMisIndex = GetQuestIndexByID( sceneId, selfId, MissionId )
	if nChangeType ==1 then
		--删除道具
		local itemNum = GetItemCount( sceneId, selfId, itemdataId )
		if itemNum < NeedNum then
	       	SetQuestByIndex( sceneId, selfId, MemberMisIndex, 0, itemNum )
			SetQuestByIndex( sceneId, selfId, MemberMisIndex, 7, 0 )
			x300619_QuestLogRefresh( sceneId, selfId, MissionId );
		end
		return
	end
	
	if NeedNum > 0 then
      	local Num = GetItemCount( sceneId, selfId, itemdataId )
		if Num > 0 then
		SetQuestByIndex( sceneId, selfId, MemberMisIndex, 7, 1 )
		SetQuestByIndex( sceneId, selfId, MemberMisIndex, 0, Num )
		x300619_QuestLogRefresh( sceneId, selfId, MissionId );
		end
	end
end
---------------------------------------------------------------------------------------------------
--更新当天接任务次数
---------------------------------------------------------------------------------------------------
function x300619_SetDayCount(sceneId, selfId)
	local today = GetDayOfYear()

	local lastday = GetQuestData(sceneId, selfId, MD_GUILD_KILLMONSTER_DATE[1], MD_GUILD_KILLMONSTER_DATE[2], MD_GUILD_KILLMONSTER_DATE[3])

	if lastday ~= today then
		SetQuestData(sceneId, selfId, MD_GUILD_KILLMONSTER_DATE[1], MD_GUILD_KILLMONSTER_DATE[2], MD_GUILD_KILLMONSTER_DATE[3], today)
		SetQuestData(sceneId, selfId, MD_GUILD_KILLMONSTER_COUNT[1], MD_GUILD_KILLMONSTER_COUNT[2], MD_GUILD_KILLMONSTER_COUNT[3], 1)
	else
		local daycount = GetQuestData(sceneId, selfId, MD_GUILD_KILLMONSTER_COUNT[1], MD_GUILD_KILLMONSTER_COUNT[2], MD_GUILD_KILLMONSTER_COUNT[3])
		SetQuestData(sceneId, selfId, MD_GUILD_KILLMONSTER_COUNT[1], MD_GUILD_KILLMONSTER_COUNT[2], MD_GUILD_KILLMONSTER_COUNT[3], daycount+1)
	end
end