x300931_g_ScriptId = 300931
x300931_g_MissionName = "【国家】领地经验"
x300931_g_GameId =1048

function x300931_ProcEnumEvent( sceneId, selfId, targetId, index )
		if GetGuildID( sceneId, selfId ) == -1 then
			--不在帮会中
			return
		end
	if GetGameOpenById(x300931_g_GameId) > 0 then
		AddQuestNumText(sceneId,x300931_g_ScriptId, x300931_g_MissionName, 3)
		
	end
	
end

function x300931_ProcEventEntry( sceneId , selfId , targetId , state , index )
	GetGuildQuestData(sceneId,selfId,GD_GUILD_LAIRDBATTLE_SCENEID, x300931_g_ScriptId,-1,"ProcEventEntry1")		
end

function x300931_ProcEventEntry1(sceneId, selfId,MissionData,MissionId)

	local nGuildID = GetGuildID(sceneId,selfId)
	local nLairdMapId,_,_,_,nLairdLevel = GetGuildLairdSceneId(nGuildID)
	if nLairdMapId <= 0 then
	
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "很抱歉，只有领地帮会成员才能领取领地经验。")
		DispatchQuestTips(sceneId, selfId)
		EndQuestEvent(sceneId)
		Msg2Player(sceneId,selfId,"很抱歉，只有领地帮会成员才能领取领地经验。",8,2)
		
		return
	end

	BeginQuestEvent(sceneId)
	local nGuildID = GetGuildID(sceneId,selfId)
	local pos = GetGuildOfficial(sceneId, selfId)
	local level = GetLevel(sceneId,selfId)
	local ExpBonus = 0
	if pos == 5 then
		if MissionData ==6 then
			 ExpBonus	= format (level*70000*9)
		end
		
		if MissionData ==9 then
			 ExpBonus	= format (level*70000*10)
		end
		
		if MissionData ==13 then
			 ExpBonus	= format (level*70000*11)
		end
		
		if MissionData ==18 then
			 ExpBonus	= format (level*70000*12)
		end
		
		
		if MissionData ==21 then
			 ExpBonus	= format (level*70000*13)
		end
		
		if MissionData ==24 then
			ExpBonus	= format (level*70000*14)
		end
		
		
		if MissionData ==27 then
			ExpBonus	= format (level*70000*15)
		end
		
		
		if MissionData ==31 then
			ExpBonus	= format (level*70000*16)
		end
		
		if MissionData ==34 then
			ExpBonus	= format (level*70000*17)
		end
	else
		if MissionData ==6 then
			 ExpBonus	= format ((level*70000*9)/4)
		end
		
		if MissionData ==9 then
			 ExpBonus	= format ((level*70000*10)/4)
		end
		
		if MissionData ==13 then
			  ExpBonus	= format ((level*70000*11)/4)
		end
		
		if MissionData ==18 then
			 ExpBonus	= format ((level*70000*12)/4)
		end
		
		
		if MissionData ==21 then
			  ExpBonus	= format ((level*70000*13)/4)
		end
		
		
		if MissionData ==24 then
			 ExpBonus	= format ((level*70000*14)/4)
		end
		
		
		if MissionData ==27 then
			 ExpBonus	= format ((level*70000*15)/4)
		end
		
		
		if MissionData ==31 then
			 ExpBonus	= format ((level*70000*16)/4)
		end
		
		if MissionData ==34 then
			 ExpBonus	= format ((level*70000*17)/4)
		end
		
	end
	
	
	
	local nLairdExp =  ExpBonus * nLairdLevel/10
	
	
	local Readme_1 = "#Y【国家】领地经验#r#W"
	local Readme_2 = "\t您好，尊敬的领地占有者，当您的等级达到#R60级#W时，您可以在每#R周六#W的#R0点-16点#W领取本周的领地经验奖励，我们会根据您占有的领地等级不同，给予您相应经验奖励，占领的领地等级越高，获得的奖励越多。 #r"
	local Readme_3 = "\t做为领地的领主，帮主可以领取普通帮会成员四倍的经验奖励。#r #r"
	local Readme_4 = "您本周可以领取的经验奖励如下：#r #r"
	local Readme_5 = "#Y经验："..ExpBonus.."点"
	local Readme = Readme_1..Readme_2..Readme_3..Readme_4..Readme_5
	AddQuestText(sceneId, Readme);EndQuestEvent(sceneId);DispatchQuestInfo( sceneId, selfId, -1, x300931_g_ScriptId, -1 )

end
function x300931_ProcAcceptCheck( sceneId, selfId, NPCId )
	return 1
end

function x300931_ProcAccept( sceneId, selfId)

	local nGuildID = GetGuildID(sceneId,selfId)
	local nLairdMapId,_,_,_,nLairdLevel = GetGuildLairdSceneId(nGuildID)
	if nLairdMapId <= 0 then
	
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "很抱歉，只有领地帮会成员才能领取领地经验。")
		DispatchQuestTips(sceneId, selfId)
		EndQuestEvent(sceneId)
		Msg2Player(sceneId,selfId,"很抱歉，只有领地帮会成员才能领取领地经验。",8,2)
		
		return
	end

	local hour,minute,second = GetHourMinSec()
    local curTime = GetMinOfDay()
	if GetWeek() ~= 6 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "很抱歉，只能在周六领取。")
		DispatchQuestTips(sceneId, selfId)
		EndQuestEvent(sceneId)
		Msg2Player(sceneId,selfId,"很抱歉，只能在周六领取。",8,2)
		return
	end
	if curTime >= 960 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "很抱歉，只能在周六的0点-16点间领取。")
		DispatchQuestTips(sceneId, selfId)
		EndQuestEvent(sceneId)
		Msg2Player(sceneId,selfId,"很抱歉，只能在周六的0点-16点间领取。",8,2)
		return
	end	
	if	GetLevel(sceneId, selfId) < 60 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "很抱歉，达到60级才可以领取领地经验奖励。")
		DispatchQuestTips(sceneId, selfId)
		EndQuestEvent(sceneId)
		Msg2Player(sceneId,selfId,"很抱歉，达到60级才可以领取领地经验奖励。",8,2)
		return
	end
	
	-- local lastDay = GetQuestData(sceneId, selfId, MD_JUDIANEXP_DATE[1], MD_JUDIANEXP_DATE[2], MD_JUDIANEXP_DATE[3])
		-- local lastFortune = GetFortuneLastTime(sceneId, selfId, 1)
		
		-- if lastDay ~= 0 and GetDayOfYear() == lastDay then
			-- BeginQuestEvent(sceneId)
			-- AddQuestText(sceneId, "很抱歉，您已经领过领地经验奖励。")
			-- DispatchQuestTips(sceneId, selfId)
			-- EndQuestEvent(sceneId)
			-- Msg2Player(sceneId,selfId,"很抱歉，您已经领过领地经验奖励。",8,2)
			-- return
		-- end
	GetGuildQuestData(sceneId,selfId,GD_GUILD_LAIRDBATTLE_SCENEID, x300931_g_ScriptId,-1,"GetGuildLairdSceneId")
end

function x300931_GetGuildLairdSceneId(sceneId, selfId,MissionData,MissionId)

	local nGuildID = GetGuildID(sceneId,selfId)
	local nLairdMapId,_,_,_,nLairdLevel = GetGuildLairdSceneId(nGuildID)
	if nLairdMapId <= 0 then
	
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "很抱歉，只有领地帮会成员才能领取领地经验。")
		DispatchQuestTips(sceneId, selfId)
		EndQuestEvent(sceneId)
		Msg2Player(sceneId,selfId,"很抱歉，只有领地帮会成员才能领取领地经验。",8,2)
		
		return
	end

	if MissionData > 0 then
		if MissionData ~= 6 and MissionData ~= 9 and MissionData ~= 13 and 
		   MissionData ~= 18 and MissionData ~= 21 and MissionData ~= 24 and 
		   MissionData ~= 27  and MissionData ~= 31 and MissionData ~= 34then
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, "很抱歉，您不是该领地占领者");
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
		Msg2Player(sceneId,selfId,"很抱歉，您不是该领地占领者",4,2)		
		return
		end
	else
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, "很抱歉，您没有占领任何领地");
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
		Msg2Player(sceneId,selfId,"很抱歉，您没有占领任何领地",4,2)	
		return
	end
		local lastDay = GetQuestData(sceneId, selfId, MD_JUDIANEXP_DATE[1], MD_JUDIANEXP_DATE[2], MD_JUDIANEXP_DATE[3])
		local lastFortune = GetFortuneLastTime(sceneId, selfId, 1)
		
		if lastDay ~= 0 and GetDayOfYear() == lastDay then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, "很抱歉，您已经领过领地经验奖励。")
			DispatchQuestTips(sceneId, selfId)
			EndQuestEvent(sceneId)
			Msg2Player(sceneId,selfId,"很抱歉，您已经领过领地经验奖励。",8,2)
			return
		end
	GetJoinGuildTime(sceneId,selfId,x300931_g_ScriptId)
end

function x300931_OnMemberJoinTimeReturn( sceneId, selfId, param )

	local nGuildID = GetGuildID(sceneId,selfId)
	local nLairdMapId,_,_,_,nLairdLevel = GetGuildLairdSceneId(nGuildID)
	if nLairdMapId <= 0 then
	
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "很抱歉，只有领地帮会成员才能领取领地经验。")
		DispatchQuestTips(sceneId, selfId)
		EndQuestEvent(sceneId)
		Msg2Player(sceneId,selfId,"很抱歉，只有领地帮会成员才能领取领地经验。",8,2)
		
		return
	end
	
	if param == -1 or GetCurrentTime()-param<24*3600 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "很抱歉，您加入该领地占领帮的时间低于24小时，不能领取奖励。")
		DispatchQuestTips(sceneId, selfId)
		EndQuestEvent(sceneId)
		Msg2Player(sceneId,selfId,"很抱歉，您加入该领地占领帮的时间低于24小时，不能领取奖励。",8,2)
		return		
	end
	GetGuildQuestData(sceneId,selfId,GD_GUILD_LAIRDBATTLE_DATE,x300931_g_ScriptId,-1,"Newqinglong")
end

function x300931_Newqinglong(sceneId, selfId,MissionData,MissionId)

	local nGuildID = GetGuildID(sceneId,selfId)
	local nLairdMapId,_,_,_,nLairdLevel = GetGuildLairdSceneId(nGuildID)
	if nLairdMapId <= 0 then
	
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "很抱歉，只有领地帮会成员才能领取领地经验。")
		DispatchQuestTips(sceneId, selfId)
		EndQuestEvent(sceneId)
		Msg2Player(sceneId,selfId,"很抱歉，只有领地帮会成员才能领取领地经验。",8,2)
		
		return
	end

	local curDay = GetDayTime()
		if curDay == MissionData then
			BeginQuestEvent(sceneId);
			AddQuestText(sceneId, "很抱歉，当天上台的领地占领者不能领取工资");
			EndQuestEvent();
			DispatchQuestTips(sceneId, selfId);
			Msg2Player(sceneId,selfId,"很抱歉，当天上台的领地占领者不能领取工资",4,2)
			return
		end
	GetGuildQuestData(sceneId,selfId,GD_GUILD_LAIRDBATTLE_SCENEID, x300931_g_ScriptId,-1,"GetGuildLairdSceneId2")
end

function x300931_GetGuildLairdSceneId2(sceneId, selfId,MissionData,MissionId)

	local nGuildID = GetGuildID(sceneId,selfId)
	local nLairdMapId,_,_,_,nLairdLevel = GetGuildLairdSceneId(nGuildID)
	if nLairdMapId <= 0 then
	
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "很抱歉，只有领地帮会成员才能领取领地经验。")
		DispatchQuestTips(sceneId, selfId)
		EndQuestEvent(sceneId)
		Msg2Player(sceneId,selfId,"很抱歉，只有领地帮会成员才能领取领地经验。",8,2)
		
		return
	end


	local nGuildID = GetGuildID(sceneId,selfId)
	local nLairdMapId,_,_,_,nLairdLevel = GetGuildLairdSceneId(nGuildID)
	if nLairdMapId <= 0 then
		return
	end

	local nGuildID = GetGuildID(sceneId,selfId)
	local pos = GetGuildOfficial(sceneId, selfId)
	local level = GetLevel(sceneId, selfId)
	local ExpBonus = 0
	local ExpBonus1 = 0
	if pos == 5 then
		if MissionData ==6 then
			 ExpBonus1	= format (level*70000*9)
		end
		
		if MissionData ==9 then
			 ExpBonus1	= format (level*70000*10)
		end
		
		if MissionData ==13 then
			 ExpBonus1	= format (level*70000*11)
		end
		
		if MissionData ==18 then
			 ExpBonus1	= format (level*70000*12)
		end
		
		if MissionData ==21 then
			 ExpBonus1	= format (level*70000*13)
		end
		
		if MissionData ==24 then
			 ExpBonus1	= format (level*70000*14)
		end
		
		if MissionData ==27 then
			 ExpBonus1	= format (level*70000*15)
		end
		
		if MissionData ==31 then
			 ExpBonus1	= format (level*70000*16)
		end
		
		if MissionData ==34 then
			 ExpBonus1	= format (level*70000*17)
		end
		
		
		
		AddExp( sceneId, selfId, ExpBonus1 )
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "成功领取领地经验");
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,"获得#R经验"..ExpBonus1.."点#o的奖励",8,2)
		
		local nLairdExpBonus1 =  ExpBonus1 * nLairdLevel/10
		AddExp( sceneId, selfId, nLairdExpBonus1 )
		Msg2Player(sceneId,selfId,"领地等级加成额外获得#R经验"..nLairdExpBonus1.."点#o的奖励",8,2)
		
		SetQuestData(sceneId, selfId, MD_JUDIANEXP_DATE[1], MD_JUDIANEXP_DATE[2], MD_JUDIANEXP_DATE[3], GetDayOfYear())
		GamePlayScriptLog(sceneId,selfId,1491)
	end
	
	if pos ~= 5 then
		if MissionData ==6 then
			 ExpBonus	= format ((level*70000*9)/4)
		end
		
		if MissionData ==9 then
			 ExpBonus	= format ((level*70000*10)/4)
		end
		
		if MissionData ==13 then
			 ExpBonus	= format ((level*70000*11)/4)
		end
		
		if MissionData ==18 then
			 ExpBonus	= format ((level*70000*12)/4)
		end
		
		if MissionData ==21 then
			 ExpBonus	= format ((level*70000*13)/4)
		end
		
		if MissionData ==24 then
			 ExpBonus	= format ((level*70000*14)/4)
		end
		
		if MissionData ==27 then
			 ExpBonus	= format ((level*70000*15)/4)
		end
		
		if MissionData ==31 then
			 ExpBonus	= format ((level*70000*16)/4)
		end
		
		if MissionData ==34 then
			 ExpBonus	= format ((level*70000*17)/4)
		end
		
		AddExp( sceneId, selfId, ExpBonus )
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "成功领取领地经验");
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,"获得#R经验"..ExpBonus.."点#o的奖励",8,2)
		
		local nLairdExpBonus1 =  ExpBonus * nLairdLevel/10
		AddExp( sceneId, selfId, nLairdExpBonus1 )
		Msg2Player(sceneId,selfId,"领地等级加成额外获得#R经验"..nLairdExpBonus1.."点#o的奖励",8,2)
		
		SetQuestData(sceneId, selfId, MD_JUDIANEXP_DATE[1], MD_JUDIANEXP_DATE[2], MD_JUDIANEXP_DATE[3], GetDayOfYear())
		GamePlayScriptLog(sceneId,selfId,1491)
	end
end