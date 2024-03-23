
x300640_g_ScriptId	= 300640
x300640_g_MissionId	=	{ --for each country
							7020,
							7742,
							7741,
							7740,
						}

x300640_MP_KILLCOUNT	= 0
x300640_g_MissionName = "【帮会】帮会暗战"
x300640_g_LevelUp				=	1
x300640_g_NeedKillMonsterNum			= 200

x300640_g_DayCountUntil = 1	--每天可以进入的次数
x300640_g_GuildExpBonus       = 3
x300640_g_BonusMoney8		=50
x300640_g_SceneList	=	{2,3,5,6,7,8,9,10,11,13,16,17,18,19,20,21,22,23,24,25,26,27,29,30,31,32,33,34,35,104,105,106,107,108,109,110,111,204,205,206,207,208,209,210,211,304,305,306,307,308,309,310,311,404,405,406,407,408,409,410,411}


function x300640_OnLeaveGuild(sceneId, selfId, missionId)
	DelQuestNM( sceneId, selfId, missionId)

	x300640_MarkThisMission(sceneId, selfId, 1)

	local message = format("您已经不在帮会中了，删除了任务：%s", x300640_g_MissionName);
	BeginQuestEvent(sceneId);
	AddQuestText(sceneId, message);
	EndQuestEvent();
	DispatchQuestTips(sceneId, selfId);
	Msg2Player(sceneId, selfId, message, 8, 2);
end
---------------------------------------------------------------------------------------------------
--最后一次做这个任务是哪天
---------------------------------------------------------------------------------------------------
function x300640_GetLastDay(sceneId, selfId)
	local lastday = GetQuestData(sceneId, selfId, MD_GUILD_ANZHAN_DATE[1], MD_GUILD_ANZHAN_DATE[2], MD_GUILD_ANZHAN_DATE[3])
	return lastday
end

---------------------------------------------------------------------------------------------------
--最后一天做这个任务做了几次
---------------------------------------------------------------------------------------------------
function x300640_GetLastDayCount(sceneId, selfId)
	local daycount =  GetQuestData(sceneId, selfId, MD_GUILD_ANZHAN_COUNT[1], MD_GUILD_ANZHAN_COUNT[2], MD_GUILD_ANZHAN_COUNT[3])
	return daycount
end

---------------------------------------------------------------------------------------------------
--今天是否能做此任务
---------------------------------------------------------------------------------------------------
function x300640_CanDoThisMission(sceneId, selfId)
	local today = GetDayOfYear()
	local lastday = x300640_GetLastDay(sceneId, selfId)
	--不是同一天，可做
	if today ~= lastday then
		return 1
	end
	
	local daycount = x300640_GetLastDayCount(sceneId, selfId)
	if daycount < x300640_g_DayCountUntil then
		--次数<最大可接次数，可做
		return 1
	end
	
	return 0
end

function x300640_SetLastDay(sceneId, selfId, day)
	SetQuestData(sceneId, selfId, MD_GUILD_ANZHAN_DATE[1], MD_GUILD_ANZHAN_DATE[2], MD_GUILD_ANZHAN_DATE[3], day)
end

function x300640_SetLastDayCount(sceneId, selfId, count)
	SetQuestData(sceneId, selfId, MD_GUILD_ANZHAN_COUNT[1], MD_GUILD_ANZHAN_COUNT[2], MD_GUILD_ANZHAN_COUNT[3], count)
end

---------------------------------------------------------------------------------------------------
--在MD中标记这个任务，完成任务、放弃任务flag用参数0，接任务用参数1
---------------------------------------------------------------------------------------------------
function x300640_MarkThisMission(sceneId, selfId, flag)
	local today = GetDayOfYear()
	local lastday = x300640_GetLastDay(sceneId, selfId)

	--上次完成的日期不是今天
	if today ~= lastday then
		x300640_SetLastDay(sceneId, selfId, today)
		x300640_SetLastDayCount(sceneId, selfId, 1)
		return
	end
	
	--上次完成的日期是今天
	if flag == 1 then
		local daycount = x300640_GetLastDayCount(sceneId, selfId) + 1
		x300640_SetLastDayCount(sceneId, selfId, daycount)
	end
end

function x300640_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	local level =GetLevel(sceneId,selfId)
	if GetGuildID(sceneId, selfId) ~= -1 and level >= 30then
		local state = GetQuestStateNM(sceneId, selfId, targetId, MissionId);
		AddQuestNumText(sceneId, MissionId, x300640_g_MissionName, state, -1)
	end
end

--选中任务
function x300640_ProcEventEntry( sceneId, selfId, targetId, MissionId )
 	
  if IsHaveQuestNM( sceneId, selfId, MissionId ) == 1 then	-- 如果有这个任务
		
	 	if GetGuildID(sceneId, selfId) == -1 then
	 		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"你已经不在帮会中，请加入帮会后再继续本任务！")
			EndQuestEvent()
			DispatchQuestDemandInfo(sceneId, selfId, targetId, x300640_g_ScriptId, MissionId,0);
			return
		end
		
		local country = GetCurCountry(sceneId, selfId)
		local ret
		local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )
		if QuestCheckSubmitNM( sceneId, selfId, targetId, MissionId, misIndex ) > 0 then -- 如果任务可以完成
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"#Y【帮会】帮会暗战")
			AddQuestText(sceneId,"\t恭喜您，完成了【帮会】帮会暗战！这是给您的奖励，请收下。#r#r#r#r")
			--local gongdezhi =GetMeritInfo_Multiple(sceneId, selfId)
			local level = GetLevel(sceneId, selfId)
			local exp = floor(level * 26000)
			AddQuestText( sceneId, "#Y奖励内容：#W#r帮贡：50点#r帮会经验：3点#r经验值："..exp.."点#r使命点：1点")
			EndQuestEvent()
			DispatchQuestContinueInfoNM(sceneId, selfId, targetId, x300640_g_ScriptId, MissionId);
		else
			BeginQuestEvent(sceneId)
			local Readme_1 = "\t您可以通过帮会任务发布人进行每天一次的帮会暗战任务，在以下地点消灭相应等级的怪物200只。如果您的等级高于目标怪物等级5级以上将不能完成任务。\n\t当帮主发布#G暗战令#W时2小时内回复任务可获得翻倍奖励经验，帮贡和2点使命点！新建帮会和入帮时间低于24小时者，不能获得帮会经验！#r"			
			
			local Readme_2 = "#R 领地     （45-140级）#R（争夺场景）#O#r#G 本国迷宫 （30-110级）#G（和平场景）#W#r"
			
			local Readme_3 = "请选择对应地图完成任务！#r"
			
			local Readme_4 = "#G小提示：随着您所在帮会等级的提升，您获得的奖励也会相应增加。您也可以和非本帮成员组队完成任务。"
			local Readme = Readme_1..Readme_2..Readme_3..Readme_4
			AddQuestText(sceneId,Readme)
			--任务目标
			AddQuestText( sceneId,"#Y完成情况：")
			AddQuestText(sceneId, "未完成#r");
			--local gongdezhi =GetMeritInfo_Multiple(sceneId, selfId)
			local level = GetLevel(sceneId, selfId)
			local exp = floor(level * 26000)
			AddQuestText( sceneId, "#Y奖励内容：#W#r帮贡：50点#r帮会经验：3点#r经验值："..exp.."点#r使命点：1点")
			EndQuestEvent()
			DispatchQuestDemandInfo(sceneId, selfId, targetId, x300640_g_ScriptId, MissionId,0);
		end
		
		country = GetCurCountry(sceneId, selfId)
		if country == 0 then 
			ret = CallScriptFunction( 256264, "Finishanzhan", sceneId, selfId)
		elseif country == 1 then
			ret = CallScriptFunction( 256265, "Finishanzhan", sceneId, selfId)
		elseif country == 2 then
			ret = CallScriptFunction( 256266, "Finishanzhan", sceneId, selfId)
		elseif country == 3 then
			ret = CallScriptFunction( 256267, "Finishanzhan", sceneId, selfId)
		end
			
		return ret
	end
	
	-- if x300640_CanDoThisMission( sceneId, selfId) ~= 1 then
		-- BeginQuestEvent( sceneId)
		-- AddQuestText( sceneId, "很抱歉，您今天已经做过这个任务，明天再来吧。")
		-- EndQuestEvent()
		-- DispatchQuestDemandInfo(sceneId, selfId, targetId, x300640_g_ScriptId, MissionId,0);
		-- BeginQuestEvent(sceneId)
		-- AddQuestText(sceneId, "很抱歉，您今天已经做过这个任务，明天再来吧。");
		-- EndQuestEvent(sceneId)
		-- DispatchQuestTips(sceneId,selfId)	
		-- Msg2Player(sceneId,selfId,"很抱歉，您今天已经做过这个任务，明天再来吧。",8,2)
		
		-- return
	-- end
	BeginQuestEvent(sceneId)
			local Readme_1 = "\t您可以通过帮会任务发布人进行每天一次的帮会暗战任务，在以下地点消灭相应等级的怪物200只，如果您的等级高于目标怪物等级5级以上将不能完成任务。\n\t当帮主发布#G暗战令#W时2小时内回复任务可获得翻倍奖励经验，帮贡和2点使命点！新建帮会和入帮时间低于24小时者，不能获得帮会经验！#r"			
			local Readme_2 = "#R 领地     （45-140级）#R（争夺场景）#O#r#G 本国迷宫 （30-110级）#G（和平场景）#W#r"
			local Readme_3 = "请选择对应地图完成任务！#r"
			local Readme_4 ="#G小提示：随着您所在帮会等级的提升，您获得的奖励也会相应增加，红色地图为PK地图。"
			local Readme = Readme_1..Readme_2..Readme_3..Readme_4
			AddQuestText(sceneId,"#Y【帮会】帮会暗战")
			AddQuestText(sceneId,Readme)
			--local gongdezhi =GetMeritInfo_Multiple(sceneId, selfId)
			local level = GetLevel(sceneId, selfId)
			local exp = floor(level * 26000)
			local 	Readme = "#Y奖励内容：#W#r帮贡：50点#r帮会经验：3点#r经验值："..exp.."点#r使命点：1点"							
			AddQuestText( sceneId,Readme )
			EndQuestEvent()

			local nCountry = GetCurCountry( sceneId, selfId )

			DispatchQuestInfo(sceneId, selfId, targetId, x300640_g_MissionId[nCountry+1], -1)
			return

end

function x300640_DoAccept( sceneId, selfId )
	if GetGuildID(sceneId, selfId) == -1 then
		return "很抱歉，您没有加入帮会，不能领取本任务！"
	end
	if GetLevel(sceneId, selfId) < x300640_g_LevelUp then
		return format("很抱歉，您的等级不足%d级，不能领取本任务！", x300640_g_LevelUp)
	end
	
	if 1 == IsQuestFullNM(sceneId, selfId) then
			return "很抱歉，您的任务已经满了，不能领取本任务！"
	end
	
	--检查前置任务
	local nCountry = GetCurCountry( sceneId, selfId )
	local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId, x300640_g_MissionId[nCountry+1] )
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
	
	AddQuestNM(sceneId, selfId, x300640_g_MissionId[nCountry+1]);

	x300640_MarkThisMission(sceneId, selfId, 1)
	
	-- write log file
	x300640_WriteLog( sceneId, selfId, MissionId, 121);
	local misIndex = GetQuestIndexByID(sceneId, selfId, x300640_g_MissionId[nCountry+1]);
	SetQuestByIndex(sceneId, selfId, misIndex, x300640_MP_KILLCOUNT, 0);
	
	local str = format("您领取了任务：%s", x300640_g_MissionName)
	Msg2Player(sceneId,selfId,str,8,2)
	BeginQuestEvent(sceneId);
	AddQuestText(sceneId, str);
	EndQuestEvent();
	DispatchQuestTips(sceneId, selfId);
	
	return nil
end
--**********************************
--接受
--**********************************
function x300640_ProcQuestAccept( sceneId, selfId, targetId, MissionId )
if x300640_CanDoThisMission( sceneId, selfId) ~= 1 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "很抱歉，您今天已经领取过帮会暗战任务，请明天再来吧。");
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)	
		Msg2Player(sceneId,selfId,"很抱歉，您今天已经领取过帮会暗战任务，请明天再来吧。",8,2)	
		return
	end
	local str = x300640_DoAccept( sceneId, selfId )
	if str ~= nil then
		Msg2Player(sceneId,selfId,str,8,2)
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, str);
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
	end
end
function x300640_OnReturn1(sceneId, selfId,MissionData,MissionId,targetId)
 local curTime = GetCurrentTime()
	local isMultiple = 0
	if curTime - MissionData < 2*60*60 then
		isMultiple = 1
	end
	local joinguildtime = MissionId
	x300640_GetBonus( sceneId,selfId, isMultiple, joinguildtime )
end

function x300640_GetBonus( sceneId, selfId, isMultiple,joinguildtime )

			local guildId = GetGuildID(sceneId, selfId);
			local GuildLevel = GetGuildSimpleData( GetGuildID( sceneId, selfId ) )--得到帮会简单数据(等级) 	
			if guildId ~= -1 then
				--local gongdezhi =GetMeritInfo_Multiple(sceneId, selfId)
				local level = GetLevel(sceneId, selfId)
				local exp = floor(level * 26000)
				AddGuildUserPoint(sceneId,selfId,50)				--增加帮贡
				AddGuildShiMing(sceneId, selfId,1)
				AddExp (sceneId,selfId,(GetLevel(sceneId, selfId)) * 26000)				--增加经验
				local Readme_1 = "您完成了任务：【帮会】帮会暗战 "
				local Readme_2 = "获得#R帮贡50点#o的奖励。"
				local Readme_4 = "获得#R经验值"..exp.."点#o的奖励。"
				--local Readme_5 = "获得#R帮会功德1点#o的奖励。"
				local Readme_6 = "获得#R使命点1点#o的奖励。"
				Msg2Player(sceneId,selfId,Readme_1,8,3)
				Msg2Player(sceneId,selfId,Readme_2,8,3)
				--Msg2Player(sceneId,selfId,Readme_3,8,3)
				Msg2Player(sceneId,selfId,Readme_4,8,3)
				--Msg2Player(sceneId,selfId,Readme_5,8,3)
				Msg2Player(sceneId,selfId,Readme_6,8,3)
				Msg2Player(sceneId,selfId,Readme_1,8,2)
				Msg2Player(sceneId,selfId,Readme_2,8,2)
				--Msg2Player(sceneId,selfId,Readme_3,8,2)
				Msg2Player(sceneId,selfId,Readme_4,8,2)
				--Msg2Player(sceneId,selfId,Readme_5,8,2)
				Msg2Player(sceneId,selfId,Readme_6,8,2)
				if isMultiple == 1 then
					local ExpBonus1 = (GetLevel(sceneId, selfId)) * 26000*3
					local Exp3 = (GetLevel(sceneId, selfId)) *26000*2
					local ExpBonus2 = (GetLevel(sceneId, selfId)) *26000*3
					local pos = GetGuildOfficial(sceneId, selfId)
					local text3 = "额外获得#R使命点2点#o的奖励"
					AddGuildShiMing(sceneId, selfId,2)
					BeginQuestEvent(sceneId)
					AddQuestText(sceneId, text3);
					EndQuestEvent(sceneId)
					DispatchQuestTips(sceneId,selfId)	
					Msg2Player(sceneId,selfId,text3,8,2)
					if  pos == 5 then
						local guildid =GetGuildID(sceneId, selfId)
						if  GetGuildCacheFreeParam(guildid,GD_GUILD_INDEX_CHIEF_MULTIMISSION_DAY) == GetDayOfYear() then
							BeginQuestEvent(sceneId)
							AddQuestText(sceneId, "帮主职位只能领取一次暗战令奖励");
							EndQuestEvent(sceneId)
							DispatchQuestTips(sceneId,selfId)
							Msg2Player(sceneId,selfId,"帮主职位只能领取一次暗战令奖励",8,2)
						else
							AddExp(sceneId, selfId, ExpBonus1);	
							BeginQuestEvent(sceneId)
							AddQuestText(sceneId, "额外获得#R经验"..ExpBonus1.."点#o的奖励");
							EndQuestEvent(sceneId)
							DispatchQuestTips(sceneId,selfId)	
							Msg2Player(sceneId,selfId,"帮会多倍任务额外获得#R经验"..ExpBonus1.."点#o的奖励",8,2)
							SetGuildQuestData(sceneId,GetGuildID(sceneId,selfId),GD_GUILD_INDEX_CHIEF_MULTIMISSION_DAY,GetDayOfYear(),0)
						end
					elseif pos == 4 then
						local guildid =GetGuildID(sceneId, selfId)
						if  GetGuildCacheFreeParam(guildid,GD_GUILD_INDEX_ASSCHIEF_MULTIMISSION_DAY) == GetDayOfYear() then
							BeginQuestEvent(sceneId)
							AddQuestText(sceneId, "副帮主职位只能领取一次暗战令奖励");
							EndQuestEvent(sceneId)
							DispatchQuestTips(sceneId,selfId)
							Msg2Player(sceneId,selfId,"副帮主职位只能领取一次暗战令奖励",8,2)
						else
							AddExp(sceneId, selfId, Exp3);	
							BeginQuestEvent(sceneId)
							AddQuestText(sceneId, "额外获得#R经验"..Exp3.."点#o的奖励");
							EndQuestEvent(sceneId)
							DispatchQuestTips(sceneId,selfId)	
							Msg2Player(sceneId,selfId,"帮会多倍任务额外获得#R经验"..Exp3.."点#o的奖励",8,2)
							SetGuildQuestData(sceneId,GetGuildID(sceneId,selfId),GD_GUILD_INDEX_ASSCHIEF_MULTIMISSION_DAY,GetDayOfYear(),0)
						end
					else
						AddExp(sceneId, selfId, exp);	
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId, "额外获得#R经验"..exp.."点#o的奖励");
						EndQuestEvent(sceneId)
						DispatchQuestTips(sceneId,selfId)	
						Msg2Player(sceneId,selfId,"帮会多倍任务额外获得#R经验"..exp.."点#o的奖励",8,2)
					end
				end
				if 	GuildLevel == 2 then
					local level = GetLevel(sceneId, selfId)
					local exp = ceil (level *26000*0.25 )
					AddExp(sceneId, selfId, exp);
					BeginQuestEvent(sceneId)
					AddQuestText(sceneId, "额外获得#R经验"..exp.."点#o的奖励");
					EndQuestEvent(sceneId)
					DispatchQuestTips(sceneId,selfId)	
					Msg2Player(sceneId,selfId,format("帮会等级2级额外获得#R经验"..exp.."点#o的奖励"),8,2)
				end
				if 	GuildLevel == 3 then
					local level = GetLevel(sceneId, selfId)
					local exp = ceil (level *26000*0.5 )
					AddExp(sceneId, selfId, exp);	
					BeginQuestEvent(sceneId)
					AddQuestText(sceneId, "额外获得#R经验"..exp.."点#o的奖励");
					EndQuestEvent(sceneId)
					DispatchQuestTips(sceneId,selfId)	
					Msg2Player(sceneId,selfId,format("帮会等级3级额外获得#R经验"..exp.."点#o的奖励"),8,2)
				end
				if 	GuildLevel == 4 then
					local level = GetLevel(sceneId, selfId)
					local exp = ceil (level *26000*0.75 )
					AddExp(sceneId, selfId, exp);	
					BeginQuestEvent(sceneId)
					AddQuestText(sceneId, "额外获得#R经验"..exp.."点#o的奖励");
					EndQuestEvent(sceneId)
					DispatchQuestTips(sceneId,selfId)	
					Msg2Player(sceneId,selfId,format("帮会等级4级额外获得#R经验"..exp.."点#o的奖励"),8,2)
				end
				if 	GuildLevel == 5 then
					local level = GetLevel(sceneId, selfId)
					local exp = ceil (level *26000*1 )
					AddExp(sceneId, selfId, exp);	
					BeginQuestEvent(sceneId)
					AddQuestText(sceneId, "额外获得#R经验"..exp.."点#o的奖励");
					EndQuestEvent(sceneId)
					DispatchQuestTips(sceneId,selfId)	
					Msg2Player(sceneId,selfId,format("帮会等级5级额外获得#R经验"..exp.."点#o的奖励"),8,2)
				end
				if 	GuildLevel == 6 then
					local level = GetLevel(sceneId, selfId)
					local exp = ceil (level *26000*1.25 )
					AddExp(sceneId, selfId, exp);	
					BeginQuestEvent(sceneId)
					AddQuestText(sceneId, "额外获得#R经验"..exp.."点#o的奖励");
					EndQuestEvent(sceneId)
					DispatchQuestTips(sceneId,selfId)	
					Msg2Player(sceneId,selfId,format("帮会等级6级额外获得#R经验"..exp.."点#o的奖励"),8,2)
				end
				if 	GuildLevel == 7 then
					local level = GetLevel(sceneId, selfId)
					local exp = ceil (level *26000*1.5 )
					AddExp(sceneId, selfId, exp);	
					BeginQuestEvent(sceneId)
					AddQuestText(sceneId, "额外获得#R经验"..exp.."点#o的奖励");
					EndQuestEvent(sceneId)
					DispatchQuestTips(sceneId,selfId)	
					Msg2Player(sceneId,selfId,format("帮会等级7级额外获得#R经验"..exp.."点#o的奖励"),8,2)
				end
				if isMultiple == 1 then
					local pos = GetGuildOfficial(sceneId, selfId)
					if pos == 5 then
					local guildid =GetGuildID(sceneId, selfId)
						if  GetGuildCacheFreeParam(guildid,GD_GUILD_INDEX_CHIEF_MULTIMISSION_DAY) == GetDayOfYear() then
							BeginQuestEvent(sceneId)
							AddQuestText(sceneId, "帮主职位只能领取一次暗战令奖励");
							EndQuestEvent(sceneId)
							DispatchQuestTips(sceneId,selfId)
							Msg2Player(sceneId,selfId,"帮主职位只能领取一次暗战令奖励",8,2)
						else
							AddGuildUserPoint(sceneId,selfId,150)	--增加帮贡
							BeginQuestEvent(sceneId)
							AddQuestText(sceneId, "额外获得#R帮贡150点#o的奖励");
							EndQuestEvent(sceneId)
							DispatchQuestTips(sceneId,selfId)	
							Msg2Player(sceneId,selfId,"帮会多倍任务额外获得#R帮贡150点#o的奖励",8,2)
							SetGuildQuestData(sceneId,GetGuildID(sceneId,selfId),GD_GUILD_INDEX_CHIEF_MULTIMISSION_DAY,GetDayOfYear(),0)
						end
					elseif pos == 4 then
					local guildid =GetGuildID(sceneId, selfId)
						local guildid =GetGuildID(sceneId, selfId)
						if  GetGuildCacheFreeParam(guildid,GD_GUILD_INDEX_ASSCHIEF_MULTIMISSION_DAY) == GetDayOfYear() then
							BeginQuestEvent(sceneId)
							AddQuestText(sceneId, "副帮主职位只能领取一次暗战令奖励");
							EndQuestEvent(sceneId)
							DispatchQuestTips(sceneId,selfId)
							Msg2Player(sceneId,selfId,"副帮主职位只能领取一次暗战令奖励",8,2)
						else
							AddGuildUserPoint(sceneId,selfId,100)	--增加帮贡
							local BonusMoney8 = x300621_g_BonusMoney8
							BeginQuestEvent(sceneId)
							AddQuestText(sceneId, "额外获得#R帮贡100点#o的奖励");
							EndQuestEvent(sceneId)
							DispatchQuestTips(sceneId,selfId)	
							Msg2Player(sceneId,selfId,"帮会多倍任务额外获得#R帮贡100点#o的奖励",8,2)
							SetGuildQuestData(sceneId,GetGuildID(sceneId,selfId),GD_GUILD_INDEX_ASSCHIEF_MULTIMISSION_DAY,GetDayOfYear(),0)
						end
					else
						AddGuildUserPoint(sceneId,selfId,50)	--增加帮贡
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId, "额外获得#R帮贡50点#o的奖励");
						EndQuestEvent(sceneId)
						DispatchQuestTips(sceneId,selfId)	
						Msg2Player(sceneId,selfId,format("帮会多倍任务额外获得#R帮贡50点#o的奖励", x300621_g_BonusMoney8),8,2)
					end
				end
				if joinguildtime == -1 or GetCurrentTime()-joinguildtime<24*3600 then
					BeginQuestEvent(sceneId)
					AddQuestText( sceneId, "很抱歉，您加入帮会时间低于24小时，不能获得帮会经验。" )
					EndQuestEvent( sceneId )
					DispatchQuestTips( sceneId, selfId )
					Msg2Player(sceneId,selfId,"很抱歉，您加入帮会时间低于24小时，不能获得帮会经验。",8,2)
					return
				end
				local name = GetName(sceneId, selfId)
				--if 	gongde >= 5 then
					AddGuildExp(sceneId, selfId, 3);				--增加帮会经验
				-- else
				BeginQuestEvent(sceneId)
				AddQuestText( sceneId, "获得#R帮会经验3点#o的奖励。" )
				EndQuestEvent( sceneId )
				DispatchQuestTips( sceneId, selfId )
				Msg2Player(sceneId,selfId,"获得#R帮会经验3点#o的奖励。",8,2)
				Msg2Player(sceneId,selfId,"帮会："..name.."完成了【帮会】帮会暗战任务，为帮会贡献了3点帮会经验。",6,2)
				-- end
				--AddGuildMerit(sceneId, selfId,1)
			end		
end

--完成任务
--返回1代表成功，0代表交任务失败
function x300640_ProcQuestSubmit( sceneId, selfId, targetId, selectId, MissionId )

    if MissionId == nil or MissionId < 0 then
        return 0
    end

	if IsQuestHaveDoneNM( sceneId, selfId, MissionId ) > 0 then --任务已经完成
		return 0
	end

	if IsHaveQuestNM( sceneId, selfId, MissionId) <= 0 then	-- 如果没这个任务直接退出
		return 0
	end
	--给奖励 
	local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId)
	local ret = QuestCheckSubmitNM( sceneId, selfId, targetId, MissionId, misIndex ) -- 获取完成任务检查信息
	if ret > 0 then -- 如果可以完成
		local ret = QuestComplateNM( sceneId, selfId, targetId, MissionId, selectId ) -- 获取完成任务信息
		if ret == 1 then -- 如果成功完成

			DelQuestNM( sceneId, selfId, MissionId)

            -- 增加活跃度
            local id = GetGuildID( sceneId, selfId)
            if id ~= -1 then
                AddGuildActivity( sceneId, selfId, GetGuildCacheFreeParam( id, GD_GUILD_ACTIVITY_PARAM3) )
            end

			x300640_MarkThisMission(sceneId, selfId, 1)
	
			-- write log file
			x300640_WriteLog( sceneId, selfId, MissionId, 122);
			--GetGuildQuestData(sceneId, selfId, GD_GUILD_INDEX_MULTI_MISSION_ANZHAN, x300640_g_ScriptId,MissionId,"OnReturn1",targetId)
			GetJoinGuildTime(sceneId,selfId,x300640_g_ScriptId)
		end
	end
    
	return 0
end

function x300640_OnMemberJoinTimeReturn( sceneId, selfId, param )

	GetGuildQuestData(sceneId, selfId, GD_GUILD_INDEX_MULTI_MISSION_ANZHAN, x300640_g_ScriptId,param,"OnReturn1",-1)

end

function x300640_ProcQuestAttach( sceneId, selfId, npcId, npcGuid,misIndex, MissionId )
	if IsHaveQuestNM( sceneId, selfId, MissionId) == 0 then	-- 如果没有这个任务
		return
	end
	
end


--********************************************************************
--放弃
--********************************************************************
function x300640_ProcQuestAbandon( sceneId, selfId, MissionId )
	
	DelQuestNM( sceneId, selfId, MissionId)

	x300640_MarkThisMission(sceneId, selfId, 1)
	
	local message = format("您放弃了任务：%s", x300640_g_MissionName);
	BeginQuestEvent(sceneId);
	AddQuestText(sceneId, message);
	EndQuestEvent();
	DispatchQuestTips(sceneId, selfId);
	Msg2Player(sceneId, selfId, message, 8, 2);
	
end


--写日志
function x300640_WriteLog( sceneId, selfId, MissionId, gameId)
	GamePlayScriptLog(sceneId, selfId, gameId)
end
--杀死怪物
function x300640_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
						   --场景ID, 自己的ID, 怪物表位置号, 怪物objId, 任务ID

end

--杀死怪物
function x300640_OnDie( sceneId, objId, killerId )

							   --场景ID, 自己的ID, 怪物表位置号, 怪物objId, 任务ID
	--判断杀怪地点是否在任务指定的场景
	if IsObjValid( sceneId,killerId ) ~=1 then
		return
	end
	
	local killerType = GetObjType(sceneId, killerId)

	--宠物杀的，记主人身上
	if killerType == 3 then
		killerId = GetOwnerID(sceneId, killerId)
	end	
	
	if IsPlayerStateNormal( sceneId, killerId) ~= 1 then
        return
    end
	
	local bInScene = 0;
	for i, item in x300640_g_SceneList do
		if sceneId == item then
			bInScene = 1;
			break;
		end
	end
	if bInScene <= 0 then
		return 0;
	end
	
	local NeedKilledNum = x300640_g_NeedKillMonsterNum;
	local str = "";
	
	local num = 1;
	local bHasTeam = HasTeam(sceneId, killerId);
	if bHasTeam > 0 then
		num = GetNearTeamCount(sceneId, killerId)
	end
  
	local memberId = killerId;
	local nCountry = GetCurCountry( sceneId, killerId )
	local MissionName = GetQuestNameNM(sceneId, killerId, x300640_g_MissionId[nCountry+1]);
  
	for i=0, num-1 do
		if bHasTeam > 0 then
			memberId = GetNearTeamMember(sceneId, killerId, i);
		end

		local misIndex = GetQuestIndexByID(sceneId, memberId, x300640_g_MissionId[nCountry+1]);
		local curKillNum = GetQuestParam(sceneId, memberId, misIndex, x300640_MP_KILLCOUNT)
		local level = GetLevel(sceneId,killerId)
		if curKillNum < NeedKilledNum and IsPlayerStateNormal( sceneId, memberId) == 1 and GetHp(sceneId, memberId) > 0 and IsHaveQuestNM(sceneId, memberId, x300640_g_MissionId[nCountry+1]) > 0  and GetGuildID(sceneId, memberId) ~= -1 then
			if GetLevel(sceneId, objId) >= GetLevel(sceneId, memberId)-5 then--如果被杀死的怪等级大于或等于玩家等级
				local KilledNum = GetQuestParam(sceneId, memberId, misIndex, x300640_MP_KILLCOUNT);
				if KilledNum < NeedKilledNum then
					SetQuestByIndex(sceneId, memberId, misIndex, x300640_MP_KILLCOUNT, KilledNum+1);
				
					if KilledNum == x300640_g_NeedKillMonsterNum - 1 then
						--完成了～～
						str = format( "#G%s#Y：已经击败: %d/%d个怪物", MissionName, KilledNum+1, x300640_g_NeedKillMonsterNum )
						SetQuestByIndex( sceneId, memberId, misIndex, 7, 1 )
					else
						str = format( "#G%s#Y：已经击败: %d/%d个怪物", MissionName, KilledNum+1, x300640_g_NeedKillMonsterNum )
					end
					BeginQuestEvent(sceneId)
					AddQuestText( sceneId, str )
					EndQuestEvent( sceneId )
					DispatchQuestTips( sceneId, memberId )
				end
		
			elseif GetLevel(sceneId, objId) < GetLevel(sceneId, killerId)-5 then--如果被杀死的怪等级小于玩家等级，显示提示信息
					nlevel = ceil(level/5)
					mlevel =nlevel*5-5
					BeginQuestEvent(sceneId)
					AddQuestText( sceneId, "您的等级过高，请挑战不低于"..mlevel.."级的敌人。" )
					local message = format("您的等级过高，请挑战不低于"..mlevel.."级的敌人。")
					EndQuestEvent( sceneId )
					DispatchQuestTips( sceneId, killerId )
					Msg2Player(sceneId, killerId, message, 8, 2);
			end
		end
	end
end

---------------------------------------------------------------------------------------------------
--任务日志刷新
---------------------------------------------------------------------------------------------------
function x300640_QuestLogRefresh( sceneId, selfId, MissionId)

	local bHaveMission = IsHaveQuestNM(sceneId, selfId,MissionId );
	if bHaveMission > 0 then
	BeginQuestEvent(sceneId)	
		if x300640_g_BonusMoney8 > 0 then
			AddQuestMoneyBonus8(sceneId, x300640_g_BonusMoney8 )	--增加帮贡
		end
		if x300640_g_GuildExpBonus>0 then
			AddQuestGuildExpBonus(sceneId,x300640_g_GuildExpBonus)--帮会经验
		end 
		local level = GetLevel(sceneId, selfId)
		--local gongdezhi =GetMeritInfo_Multiple(sceneId, selfId)
		local ExpBonus = ceil (level * 26000)
		AddQuestExpBonus(sceneId, ExpBonus);

		-- local misIndex = GetQuestIndexByID(sceneId, selfId, MissionId);
		-- local num = GetQuestParam(sceneId, selfId,misIndex,0)
		-- local text = format("(kkkkkkkkkkq%d/%d)",num,5)

		AddQuestLogCustomText( sceneId,
								"",								-- 标题
								"",								-- 任务名字
								"",								--任务目标
								"",								--任务NPC
								"",								--任务攻略
								"",								--任务描述
								"随着您所在帮会等级的提升，您获得的奖励也会相应增加。"								--任务小提示
								)
		EndQuestEvent(sceneId)
		DispatchQuestLogUpdate(sceneId, selfId, MissionId);
	end

end

function x300640_ProcQuestLogRefresh( sceneId, selfId, MissionId)

	local nCountry = GetCurCountry( sceneId, selfId )
	x300640_QuestLogRefresh( sceneId, selfId, x300640_g_MissionId[nCountry+1] );
end 