x300636_g_ScriptId = 300636
x300636_g_MissionName = "【国家】领取出国津贴"
x300636_g_GameId =1009
x300636_g_Level = 60
function x300636_ProcEnumEvent( sceneId, selfId, targetId, index )
	if GetGameOpenById(x300636_g_GameId) > 0 then
		AddQuestNumText(sceneId,x300636_g_ScriptId, x300636_g_MissionName, 3)
	end
	
end

function x300636_ProcEventEntry( sceneId , selfId , targetId , state , index )
	GetCountryQuestData(sceneId,selfId,CD_INDEX_CHUGUO_COUNT, x300636_g_ScriptId,-1,"OnReturn1")
end

--********************
--检测接受条件
--**********************************
function x300636_ProcAcceptCheck( sceneId, selfId, NPCId )
		return 1
end

--**********************************
--接受
--**********************************
function x300636_Newking(sceneId, selfId,MissionData,MissionId)
	local curDay = GetDayTime()
	if curDay == MissionData then
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, "很抱歉，当天上台的国王帮成员或大臣不能领取工资");
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
		Msg2Player(sceneId,selfId,"很抱歉，当天上台的国王帮成员或大臣不能领取工资",4,2)
		return
	end
	GetCountryQuestData(sceneId,selfId,CD_INDEX_CHUGUO_COUNT, x300636_g_ScriptId,-1,"OnReturn3")
end

function x300636_ProcAccept( sceneId, selfId)
	
	local hour,minute,second = GetHourMinSec()
	if GetWeek() ~= 0 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "很抱歉，只能在周日领取。")
		DispatchQuestTips(sceneId, selfId)
		EndQuestEvent(sceneId)
		Msg2Player(sceneId,selfId,"很抱歉，只能在周日领取。",8,2)
		return
	end

	--if x300636_GetOfficialMissionId(sceneId, selfId)<=0 then
		if GetExploit(sceneId, selfId) < 38 then
			if x300631_GetOfficialMissionId(sceneId, selfId)==-2 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId, "很抱歉，国王帮成员才可以领取国运津贴。")
				DispatchQuestTips(sceneId, selfId)
				EndQuestEvent(sceneId)
				Msg2Player(sceneId,selfId,"很抱歉，国王帮成员才可以领取国运津贴。",8,2)		
				return
			end
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, "很抱歉，您的功勋值不足38，不能领取。")
			DispatchQuestTips(sceneId, selfId)
			EndQuestEvent(sceneId)
			Msg2Player(sceneId,selfId,"很抱歉，您的功勋值不足38，不能领取。",8,2)		
			return
		end	
	--end
	if	GetLevel(sceneId, selfId) < x300636_g_Level then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "很抱歉，达到60级才可以领取出国津贴。")
		DispatchQuestTips(sceneId, selfId)
		EndQuestEvent(sceneId)
		Msg2Player(sceneId,selfId,"很抱歉，达到60级才可以领取出国津贴。",8,2)
		return
	end
	
	if CountryIsFortuneTime(sceneId, selfId, 1) > 0 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "很抱歉，出国期间不能领取。")
		DispatchQuestTips(sceneId, selfId)
		EndQuestEvent(sceneId)
		Msg2Player(sceneId,selfId,"很抱歉，出国期间不能领取。",8,2)
		return
	end

	local lastDay = GetQuestData(sceneId, selfId, MD_CHUGUO_DATE[1], MD_CHUGUO_DATE[2], MD_CHUGUO_DATE[3])
	local lastFortune = GetFortuneLastTime(sceneId, selfId, 1)

	if lastDay ~= 0 and GetDayOfYear() == lastDay then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "很抱歉，已经领过出国津贴。")
		DispatchQuestTips(sceneId, selfId)
		EndQuestEvent(sceneId)
		Msg2Player(sceneId,selfId,"很抱歉，已经领过出国津贴。",8,2)
		return
	end
	
	local Shouhu = GetQuestData(sceneId, selfId, MD_SHOUHU_DATE[1], MD_SHOUHU_DATE[2], MD_SHOUHU_DATE[3])
	if GetDayOfYear() ==Shouhu  then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "很抱歉，您已经领过本周青龙（朱雀）守护津贴。")
		DispatchQuestTips(sceneId, selfId)
		EndQuestEvent(sceneId)
		Msg2Player(sceneId,selfId,"很抱歉，您已经领过本周青龙（朱雀）守护津贴。",8,2)
		return
	end
	if lastFortune > 0 then 
	
		local officalId = x300636_GetOfficialMissionId(sceneId, selfId)
		if officalId == -2 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, "很抱歉，您不能领取津贴。")
			DispatchQuestTips(sceneId, selfId)
			EndQuestEvent(sceneId)
			Msg2Player(sceneId,selfId,"很抱歉，您不能领取津贴。",8,2)
			return
		elseif officalId ~= -1 then
			GetCountryQuestData(sceneId,selfId,officalId, x300636_g_ScriptId,-1,"OnReturn2")
			return
		end	
		
	else
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "还未发布出国令")
		DispatchQuestTips(sceneId, selfId)
		EndQuestEvent(sceneId)
		Msg2Player(sceneId,selfId,"还未发布出国令",8,2)
		return
	end
	
	GetJoinGuildTime(sceneId,selfId,x300636_g_ScriptId)
end

function x300636_OnMemberJoinTimeReturn( sceneId, selfId, param )

	if param == -1 or GetCurrentTime()-param<24*3600 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "很抱歉，您加入国王帮的时间低于24小时，不能领取津贴。")
		DispatchQuestTips(sceneId, selfId)
		EndQuestEvent(sceneId)
		Msg2Player(sceneId,selfId,"很抱歉，您加入国王帮的时间低于24小时，不能领取津贴。",8,2)
		return		
	end
	
	local officalId = x300636_GetOfficialMissionId(sceneId, selfId)
	if officalId == -1 then
		x300636_OnReturn2(sceneId, selfId,-1,MissionId)
		return
	end
	
	GetCountryQuestData(sceneId,selfId,officalId, x300636_g_ScriptId,-1,"OnReturn2")

end

function x300636_GetOfficialMissionId(sceneId, selfId)
	local officalId = -1
	local selfGuildId = GetGuildID(sceneId, selfId)
	local countryGuildId = GetCountryKingGuildId(sceneId, selfId)
	
	if IsKing(sceneId, selfId) > 0 then
		officalId = CD_INDEX_CHUGUO_KING
	elseif IsCountryOffical(sceneId, selfId) > 0 then
		if IsSpecialCountryOffical(sceneId, selfId, 7 ) > 0 then  --王后
			officalId = CD_INDEX_CHUGUO_QUEEN
		elseif IsSpecialCountryOffical(sceneId, selfId, 6 ) > 0 then --大臣
			officalId = CD_INDEX_CHUGUO_GENERAL
		elseif IsSpecialCountryOffical(sceneId, selfId, 5 ) > 0 then -- 右相
			officalId = CD_INDEX_CHUGUO_RMINISTER	
		elseif IsSpecialCountryOffical(sceneId, selfId, 4 ) > 0 then --左相
			officalId = CD_INDEX_CHUGUO_LMINISTER	
		elseif IsSpecialCountryOffical(sceneId, selfId, 3 ) > 0 then  --右捕
			officalId = CD_INDEX_CHUGUO_RGUARD	
		elseif IsSpecialCountryOffical(sceneId, selfId, 2 ) > 0 then --左捕
			officalId = CD_INDEX_CHUGUO_LGUARD
		end
	elseif selfGuildId ~= -1 and countryGuildId == selfGuildId then
		officalId = -1
	else
		officalId = -2
	end
	
	return officalId
end

function x300636_OnReturn1(sceneId, selfId,MissionData,MissionId)
	
	local count = MissionData + 1

	if count < -1 then
		return
	end

	if count == -1 then
		count = 0
	end
				
	if count > 22400 then
		count = 22400
	end
	
	
	local awardRongyu =0;
	local awardExp =0;
	local awardJinKa =0;

	local selfGuildId = GetGuildID(sceneId, selfId)
	local countryGuildId = GetCountryKingGuildId(sceneId, selfId)
	local level = GetLevel(sceneId, selfId)
	
	local toggle = 0

	if IsKing(sceneId, selfId) > 0 then
		awardRongyu =floor(count/10)
		awardExp =floor(level*80*count/10)
		awardJinKa =floor(100*count/10)
	elseif IsCountryOffical(sceneId, selfId) > 0 then
		awardRongyu =floor(count*0.5/10)
		awardExp =floor(level*80*count*0.5/10)
		awardJinKa =floor(100*count*0.5/10)
	elseif selfGuildId ~= -1 and countryGuildId == selfGuildId then
		awardRongyu =floor(count*0.25/10)
		awardExp =floor(level*80*count*0.25/10)
		awardJinKa =floor(100*count*0.25/10)
	else
		toggle =1
	end

	local ding=0
	local liang=0
	local wen=0
	
	BeginQuestEvent(sceneId)
	local nExploit = GetExploit(sceneId,selfId)
	if IsKing(sceneId, selfId) > 0 then
		awardJinKa =floor(100*count/10)
		ding = floor( awardJinKa / (1000*1000) )
		liang = floor( mod(awardJinKa,1000*1000)/ 1000 )
		wen = mod(awardJinKa,1000)
	elseif IsCountryOffical(sceneId, selfId) > 0 then
		awardJinKa =floor(100*count*0.5/10)
		ding = floor( awardJinKa / (1000*1000) )
		liang = floor( mod(awardJinKa,1000*1000)/ 1000 )
		wen = mod(awardJinKa,1000)
	elseif selfGuildId ~= -1 and countryGuildId == selfGuildId then
		awardJinKa =floor(100*count*0.25/10)
		ding = floor( awardJinKa / (1000*1000) )
		liang = floor( mod(awardJinKa,1000*1000)/ 1000 )
		wen = mod(awardJinKa,1000)
	end
	local Readme = "#Y【国家】领取出国津贴#r";
	local Readme2 = "#W    出国津贴是对在出国任务中做出巨大贡献的#G国家官员#W和#G国王帮会成员#W准备的津贴。#r"
	local Readme3 = "    在发布#G出国令#W时间内，每个玩家#G完成出国任务#W的次数将直接影响当天出国任务津贴的多少。#r"
	local Readme4 = "    每周一到周日，每天出国令期间出国任务的成功次数将会累计，在周日，可以领取一周的出国津贴。在功勋值足够的基础上，#G国王#W领取#G四倍#W津贴，#G国家大臣#W领取#G两倍#W的津贴，#G国王帮众#W领取#G一倍#W的津贴。#r"
	local Readme5 = "    达到#G60级#W的王者卫队成员每周的功勋值必须达到#G38#W点以上才可以领取出国津贴，功勋值是每人在出国令期间完成出国任务时获得。#r\t请问您是否要领取？"
	local award1 = format("#W您将获得#R%d#W荣誉奖励#r", awardRongyu);
	local award2 = format("您将获得#R%d#W经验奖励#r", awardExp);
	local award3 = format("您将获得#R%d锭%d两%d#W文金卡奖励", ding,liang,wen);
	local award = "您现在拥有#G"..nExploit.."点#W功勋值";
	local blank=" #r";
	if toggle == 0 then
		AddQuestText(sceneId,Readme..Readme2..Readme3..Readme4..Readme5..blank..award..blank..award1..award2..award3)
	else
		AddQuestText(sceneId,Readme..Readme2..Readme3..Readme4..Readme5)
	end
	EndQuestEvent(sceneId)	
	DispatchQuestInfo(sceneId,selfId,-1,x300636_g_ScriptId,-1)

	return 	
end

function x300636_OnReturn2(sceneId, selfId,MissionData,MissionId)

	if MissionData>=0 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "很抱歉，此职位已经领过出国津贴。")
		DispatchQuestTips(sceneId, selfId)
		EndQuestEvent(sceneId)
		Msg2Player(sceneId,selfId,"很抱歉，此职位已经领过出国津贴。",8,2)
		return		
	end
	GetCountryQuestData(sceneId,selfId,CD_INDEX_CREATEKING_DATE, x300636_g_ScriptId,-1,"Newking")
end

function x300636_OnReturn3(sceneId, selfId,MissionData,MissionId)
	
	local selfGuildId = GetGuildID(sceneId, selfId)
	local countryGuildId = GetCountryKingGuildId(sceneId, selfId)
	local officalId = -1
	local country = GetCurCountry(sceneId, selfId)
	local lastFortune = GetFortuneLastTime(sceneId, selfId, 1)
	
	local count = MissionData + 1
	if count < -1 then
		return
	end
	if count == -1 then
		count = 0
	end
	if count > 22400 then
		count = 22400
	end

	
	--给津贴
		if IsKing(sceneId, selfId) > 0 then

			local level = GetLevel(sceneId, selfId)
			
			AddHonor( sceneId, selfId, floor(count/10) )
			local str=format("#o获得#R荣誉%d点#o的奖励", floor(count/10))
			BeginQuestEvent(sceneId);
			AddQuestText(sceneId, str);
			EndQuestEvent();
			DispatchQuestTips(sceneId, selfId);
			Msg2Player(sceneId,selfId,str,4,2)

			AddExp( sceneId, selfId, floor(level*80*count/10) )
			str=format("#o获得#R经验%d点#o的奖励", floor(level*80*count/10))
			BeginQuestEvent(sceneId);
			AddQuestText(sceneId, str);
			EndQuestEvent();
			DispatchQuestTips(sceneId, selfId);
			Msg2Player(sceneId,selfId,str,4,2)

			local awardMoney = 100*count
			AddMoney( sceneId, selfId,3, floor(awardMoney/10) )
			str = format( "获得#R金卡#{_MONEY%d}#o的奖励", floor(awardMoney/10))
			BeginQuestEvent(sceneId);
			AddQuestText(sceneId, str);
			EndQuestEvent();
			DispatchQuestTips(sceneId, selfId);
			Msg2Player(sceneId,selfId, str,4,2)

			officalId = x300636_GetOfficialMissionId(sceneId, selfId)
			SetQuestData(sceneId, selfId, MD_CHUGUO_DATE[1], MD_CHUGUO_DATE[2], MD_CHUGUO_DATE[3], GetDayOfYear())
			SetCountryQuestData(sceneId, country, officalId, GetDayOfYear() )

			--添加玩法日志
			GamePlayScriptLog( sceneId, selfId, 981)
			
		elseif IsCountryOffical(sceneId, selfId) > 0 then

			local level = GetLevel(sceneId, selfId)

			AddHonor( sceneId, selfId, floor(count*0.5/10) )
			local str=format("#o获得#R荣誉%d点#o的奖励", floor(count*0.5/10))
			BeginQuestEvent(sceneId);
			AddQuestText(sceneId, str);
			EndQuestEvent();
			DispatchQuestTips(sceneId, selfId);
			Msg2Player(sceneId,selfId,str,4,2)

			AddExp( sceneId, selfId, floor(level*40*count/10) )
			str=format("#o获得#R经验%d点#o的奖励", floor(level*40*count/10))
			BeginQuestEvent(sceneId);
			AddQuestText(sceneId, str);
			EndQuestEvent();
			DispatchQuestTips(sceneId, selfId);
			Msg2Player(sceneId,selfId,str,4,2)

			local awardMoney = 50*count
			AddMoney( sceneId, selfId,3, floor(awardMoney/10) )
			str = format( "获得#R金卡#{_MONEY%d}#o的奖励", floor(awardMoney/10) )
			BeginQuestEvent(sceneId);
			AddQuestText(sceneId, str);
			EndQuestEvent();
			DispatchQuestTips(sceneId, selfId);
			Msg2Player(sceneId,selfId, str,4,2)
			
			officalId = x300636_GetOfficialMissionId(sceneId, selfId)
			SetQuestData(sceneId, selfId, MD_CHUGUO_DATE[1], MD_CHUGUO_DATE[2], MD_CHUGUO_DATE[3], GetDayOfYear())
			SetCountryQuestData(sceneId, country, officalId, GetDayOfYear() )
		
			--添加玩法日志
			GamePlayScriptLog( sceneId, selfId, 981)
			
		elseif selfGuildId ~= -1 and countryGuildId == selfGuildId then
		
			local level = GetLevel(sceneId, selfId)

			AddHonor( sceneId, selfId, floor(count*0.25/10) )
			local str=format("#o获得#R荣誉%d点#o的奖励", floor(count*0.25/10))
			BeginQuestEvent(sceneId);
			AddQuestText(sceneId, str);
			EndQuestEvent();
			DispatchQuestTips(sceneId, selfId);
			Msg2Player(sceneId,selfId,str,4,2)

			AddExp( sceneId, selfId, floor(level*20*count/10) )
			str=format("#o获得#R经验%d点#o的奖励", floor(level*20*count/10))
			BeginQuestEvent(sceneId);
			AddQuestText(sceneId, str);
			EndQuestEvent();
			DispatchQuestTips(sceneId, selfId);
			Msg2Player(sceneId,selfId,str,4,2)

			local awardMoney = 25*count
			AddMoney( sceneId, selfId,3, floor(awardMoney/10) )
			str = format( "获得#R金卡#{_MONEY%d}#o的奖励", floor(awardMoney/10) )
			BeginQuestEvent(sceneId);
			AddQuestText(sceneId, str);
			EndQuestEvent();
			DispatchQuestTips(sceneId, selfId);
			Msg2Player(sceneId,selfId, str,4,2)
			SetQuestData(sceneId, selfId, MD_CHUGUO_DATE[1], MD_CHUGUO_DATE[2], MD_CHUGUO_DATE[3], GetDayOfYear())
			
			--添加玩法日志
			GamePlayScriptLog( sceneId, selfId, 981)
			
		else
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, "很抱歉，您不能领取津贴。")
			DispatchQuestTips(sceneId, selfId)
			EndQuestEvent(sceneId)
			Msg2Player(sceneId,selfId,"很抱歉，您不能领取津贴。",8,2)
		end
end