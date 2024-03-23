x300631_g_ScriptId = 300631
x300631_g_MissionName = "【国家】领取国运津贴"
x300631_g_GameId =1008
x300631_g_Level = 60
function x300631_ProcEnumEvent( sceneId, selfId, targetId, index )
	if GetGameOpenById(x300631_g_GameId) > 0 then
		AddQuestNumText(sceneId,x300631_g_ScriptId, x300631_g_MissionName, 3)
	end
	
end

function x300631_ProcEventEntry( sceneId , selfId , targetId , state , index )
	GetCountryQuestData(sceneId,selfId,CD_INDEX_GUOYUN_COUNT, x300631_g_ScriptId,-1,"OnReturn1")	
end

--********************
--检测接受条件
--**********************************
function x300631_ProcAcceptCheck( sceneId, selfId, NPCId )
		return 1
end

function x300631_Newking(sceneId, selfId,MissionData,MissionId)
	local curDay = GetDayTime()
	if curDay == MissionData then
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, "很抱歉，当天上台的国王帮成员或大臣不能领取工资");
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
		Msg2Player(sceneId,selfId,"很抱歉，当天上台的国王帮成员或大臣不能领取工资",4,2)
		return
	end
	GetCountryQuestData(sceneId,selfId,CD_INDEX_GUOYUN_COUNT, x300631_g_ScriptId,-1,"OnReturn3")
end

--**********************************
--接受
--**********************************
function x300631_ProcAccept( sceneId, selfId )

	local hour,minute,second = GetHourMinSec()
	if GetWeek() ~= 0 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "很抱歉，只能在周日领取。")
		DispatchQuestTips(sceneId, selfId)
		EndQuestEvent(sceneId)
		Msg2Player(sceneId,selfId,"很抱歉，只能在周日领取。",8,2)
		return
	end
	
	--if x300631_GetOfficialMissionId(sceneId, selfId)<=0 then
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
	if	GetLevel(sceneId, selfId) < x300631_g_Level then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "很抱歉，达到60级才可以领取国运津贴。")
		DispatchQuestTips(sceneId, selfId)
		EndQuestEvent(sceneId)
		Msg2Player(sceneId,selfId,"很抱歉，达到60级才可以领取国运津贴。",8,2)
		return
	end
		
	if CountryIsFortuneTime(sceneId, selfId, 0) > 0 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "很抱歉，国运期间不能领取。")
		DispatchQuestTips(sceneId, selfId)
		EndQuestEvent(sceneId)
		Msg2Player(sceneId,selfId,"很抱歉，国运期间不能领取。",8,2)
		return
	end

	local lastDay = GetQuestData(sceneId, selfId, MD_GUOYUN_DATE[1], MD_GUOYUN_DATE[2], MD_GUOYUN_DATE[3])
	local lastFortune = GetFortuneLastTime(sceneId, selfId, 0)

	if lastDay ~= 0 and GetDayOfYear() == lastDay then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "很抱歉，已经领过国运津贴。")
		DispatchQuestTips(sceneId, selfId)
		EndQuestEvent(sceneId)
		Msg2Player(sceneId,selfId,"很抱歉，已经领过国运津贴。",8,2)
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
	
	if lastFortune > 0 then --国运次数
	
		local officalId = x300631_GetOfficialMissionId(sceneId, selfId)
		
		if officalId == -2 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, "很抱歉，您不能领取津贴。")
			DispatchQuestTips(sceneId, selfId)
			EndQuestEvent(sceneId)
			Msg2Player(sceneId,selfId,"很抱歉，您不能领取津贴。",8,2)
			return
		elseif officalId ~= -1 then
			GetCountryQuestData(sceneId,selfId,officalId, x300631_g_ScriptId,-1,"OnReturn2")
			return			
		end
		
	else
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "还未发布国运令")
		DispatchQuestTips(sceneId, selfId)
		EndQuestEvent(sceneId)
		Msg2Player(sceneId,selfId,"还未发布国运令",8,2)
		return
	end
		
	GetJoinGuildTime(sceneId,selfId,x300631_g_ScriptId)
end

function x300631_OnMemberJoinTimeReturn( sceneId, selfId, param )

	if param == -1 or GetCurrentTime()-param<24*3600 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "很抱歉，您加入国王帮的时间低于24小时，不能领取津贴。")
		DispatchQuestTips(sceneId, selfId)
		EndQuestEvent(sceneId)
		Msg2Player(sceneId,selfId,"很抱歉，您加入国王帮的时间低于24小时，不能领取津贴。",8,2)
		return		
	end
	
	local officalId = x300631_GetOfficialMissionId(sceneId, selfId)
	if officalId == -1 then
		x300631_OnReturn2(sceneId, selfId,-1,MissionId)
		return
	end
	
	GetCountryQuestData(sceneId,selfId,officalId, x300631_g_ScriptId,-1,"OnReturn2")
end

function x300631_GetOfficialMissionId(sceneId, selfId)
	local officalId = -1
	local selfGuildId = GetGuildID(sceneId, selfId)
	local countryGuildId = GetCountryKingGuildId(sceneId, selfId)
	
	if IsKing(sceneId, selfId) > 0 then
		officalId = CD_INDEX_GUOYUN_KING
	elseif IsCountryOffical(sceneId, selfId) > 0 then
		if IsSpecialCountryOffical(sceneId, selfId, 7 ) > 0 then  --王后
			officalId = CD_INDEX_GUOYUN_QUEEN
		elseif IsSpecialCountryOffical(sceneId, selfId, 6 ) > 0 then --大臣
			officalId = CD_INDEX_GUOYUN_GENERAL
		elseif IsSpecialCountryOffical(sceneId, selfId, 5 ) > 0 then -- 右相
			officalId = CD_INDEX_GUOYUN_RMINISTER	
		elseif IsSpecialCountryOffical(sceneId, selfId, 4 ) > 0 then --左相
			officalId = CD_INDEX_GUOYUN_LMINISTER	
		elseif IsSpecialCountryOffical(sceneId, selfId, 3 ) > 0 then  --右捕
			officalId = CD_INDEX_GUOYUN_RGUARD	
		elseif IsSpecialCountryOffical(sceneId, selfId, 2 ) > 0 then --左捕
			officalId = CD_INDEX_GUOYUN_LGUARD
		end
	elseif selfGuildId ~= -1 and countryGuildId == selfGuildId then
		officalId = -1
	else
		officalId = -2
	end
	
	return officalId
end

function x300631_OnReturn1(sceneId, selfId,MissionData,MissionId)
	local count = MissionData + 1
	
	if count < -1 then
		return
	end

	if count == -1 then
		count = 0
	end
	
	if count > 21000 then
		count = 21000
	end
	
	local awardExp =0;
	local awardShengWang =0;
	local awardYinKa =0;

	local selfGuildId = GetGuildID(sceneId, selfId)
	local countryGuildId = GetCountryKingGuildId(sceneId, selfId)
	local level = GetLevel(sceneId, selfId)
	
	local toggle = 0
	if IsKing(sceneId, selfId) > 0 then
		awardExp =floor(level*12*count)
		awardShengWang =count
		awardYinKa =level*count
	elseif IsCountryOffical(sceneId, selfId) > 0 then
		awardExp =floor(level*12*count*0.5)
		awardShengWang =floor(count*0.5)
		awardYinKa =floor(level*count*0.5)
	elseif selfGuildId ~= -1 and countryGuildId == selfGuildId then
		awardExp =floor(level*12*count*0.25)
		awardShengWang =floor(count*0.25)
		awardYinKa =floor(level*count*0.25)
	else
		toggle =1
	end

	local ding=0
	local liang=0
	local wen=0
	
	BeginQuestEvent(sceneId)
	local nExploit = GetExploit(sceneId,selfId)
	if IsKing(sceneId, selfId) > 0 then
		awardYinKa =floor(level*count)
		ding = floor( awardYinKa / (1000*1000) )
		liang = floor( mod(awardYinKa,1000*1000)/ 1000 )
		wen = mod(awardYinKa,1000)
	elseif IsCountryOffical(sceneId, selfId) > 0 then
		awardYinKa =floor(level*count*0.5)
		ding = floor( awardYinKa / (1000*1000) )
		liang = floor( mod(awardYinKa,1000*1000)/ 1000 )
		wen = mod(awardYinKa,1000)
	elseif selfGuildId ~= -1 and countryGuildId == selfGuildId then
		awardYinKa =floor(level*count*0.25)
		ding = floor( awardYinKa / (1000*1000) )
		liang = floor( mod(awardYinKa,1000*1000)/ 1000 )
		wen = mod(awardYinKa,1000)
	end
	local Readme = "#Y【国家】领取国运津贴#r";
	local Readme2 = "#W    国运津贴是对在国运中做出巨大贡献的#G国家官员#W和#G国王帮会成员#W准备的津贴。#r"
	local Readme3 = "    在发布#G国运令#W时间内，#G官府押运的成功次数#W将直接影响当天国运津贴的多少。#r"
	local Readme4 = "    每周一到周日，每天国运令期间官府押运的成功次数将会累计，在周日，可以领取一周的国运津贴。在功勋值足够的基础上，#G国王#W领取#G四倍#W津贴，#G国家大臣#W领取#G两倍#W的津贴，#G国王帮众#W领取#G一倍#W的津贴。#r"
	local Readme5 = "    达到#G60级#W的王者卫队成员每周的功勋值必须达到#G38#W点以上才可以领取国运津贴，功勋值是每人在出国令期间完成出国任务时获得。#r\t请问您是否要领取？"
	local award1 = format("#W您将获得#R%d#W经验奖励#r", awardExp);
	local award2 = format("您将获得#R%d#W声望奖励#r", awardShengWang);
	local award3 = format("您将获得#R%d锭%d两%d文#W银卡奖励", ding,liang,wen);
	local award = "您现在拥有#G"..nExploit.."点#W功勋值"
	local blank=" #r";
	if toggle == 0 then
		AddQuestText(sceneId,Readme..Readme2..Readme3..Readme4..Readme5..blank..award..blank..award1..award2..award3)
	else
		AddQuestText(sceneId,Readme..Readme2..Readme3..Readme4..Readme5)
	end
	EndQuestEvent(sceneId)	
	DispatchQuestInfo(sceneId,selfId,-1,x300631_g_ScriptId,-1)

	return 

end


function x300631_OnReturn2(sceneId, selfId,MissionData,MissionId)
	
	if MissionData>=0 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "很抱歉，此职位已经领过国运津贴。")
		DispatchQuestTips(sceneId, selfId)
		EndQuestEvent(sceneId)
		Msg2Player(sceneId,selfId,"很抱歉，此职位已经领过国运津贴。",8,2)
		return		
	end
	
	GetCountryQuestData(sceneId,selfId,CD_INDEX_CREATEKING_DATE, x300631_g_ScriptId,-1,"Newking")
	
end


function x300631_OnReturn3(sceneId, selfId,MissionData,MissionId)

	local selfGuildId = GetGuildID(sceneId, selfId)
	local countryGuildId = GetCountryKingGuildId(sceneId, selfId)
	local officalId = -1
	local country = GetCurCountry(sceneId, selfId)
	local lastFortune = GetFortuneLastTime(sceneId, selfId, 0)
	
	local count = MissionData + 1

	if count < -1 then
		return
	end
	if count == -1 then
		count = 0
	end
	if count > 21000 then
		count = 21000
	end
	
	--给津贴
	if IsKing(sceneId, selfId) > 0 then

		local level = GetLevel(sceneId, selfId)
		AddExp( sceneId, selfId, floor(level*12*count) )
		local str=format("#o获得#R经验%d点#o的奖励", floor(level*12*count))
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, str);
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
		Msg2Player(sceneId,selfId,str,4,2)

		local nShengWang = GetShengWang( sceneId, selfId )
		nShengWang = nShengWang + count
		SetShengWang( sceneId, selfId, nShengWang )
		str = format("获得#R声望%d#o的奖励", count)
		BeginQuestEvent(sceneId);
			AddQuestText(sceneId, str);
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
		Msg2Player(sceneId,selfId,str,4,2)
		
		local awardMoney = level*count
		AddMoney( sceneId, selfId,1, awardMoney )
		str = format( "获得#R银卡#{_MONEY%d}#o的奖励", awardMoney)
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, str);
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
		Msg2Player(sceneId,selfId, str,4,2)

		officalId = x300631_GetOfficialMissionId(sceneId, selfId)
		SetQuestData(sceneId, selfId, MD_GUOYUN_DATE[1], MD_GUOYUN_DATE[2], MD_GUOYUN_DATE[3], GetDayOfYear())
		SetCountryQuestData(sceneId, country, officalId, GetDayOfYear() )
		

		--添加玩法日志
		GamePlayScriptLog( sceneId, selfId, 991)
		
	elseif IsCountryOffical(sceneId, selfId) > 0 then

		local level = GetLevel(sceneId, selfId)
		AddExp( sceneId, selfId, floor(level*12*count*0.5) )
		local str=format("#o获得#R经验%d点#o的奖励", floor(level*12*count*0.5))
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, str);
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
		Msg2Player(sceneId,selfId,str,4,2)

		local nShengWang = GetShengWang( sceneId, selfId )
		nShengWang = nShengWang + (count*0.5)
		SetShengWang( sceneId, selfId, floor(nShengWang) )
		str = format("获得#R声望%d#o的奖励", floor(count*0.5))
		BeginQuestEvent(sceneId);
			AddQuestText(sceneId, str);
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
		Msg2Player(sceneId,selfId,str,4,2)

		local awardMoney = level*count*0.5
		AddMoney( sceneId, selfId,1, floor(awardMoney) )
		str = format( "获得#R银卡#{_MONEY%d}#o的奖励", floor(awardMoney))
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, str);
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
		Msg2Player(sceneId,selfId, str,4,2)
		
		officalId = x300631_GetOfficialMissionId(sceneId, selfId)
		SetQuestData(sceneId, selfId, MD_GUOYUN_DATE[1], MD_GUOYUN_DATE[2], MD_GUOYUN_DATE[3], GetDayOfYear())
		SetCountryQuestData(sceneId, country, officalId, GetDayOfYear() )
		
	
		--添加玩法日志
		GamePlayScriptLog( sceneId, selfId, 991)
		
	elseif selfGuildId ~= -1 and countryGuildId == selfGuildId then
	
		local level = GetLevel(sceneId, selfId)
		AddExp( sceneId, selfId, floor(level*12*count*0.25) )
		local str=format("#o获得#R经验%d点#o的奖励", floor(level*12*count*0.25))
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, str);
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
		Msg2Player(sceneId,selfId,str,4,2)

		local nShengWang = GetShengWang( sceneId, selfId )
		nShengWang = nShengWang + (count*0.25)
		SetShengWang( sceneId, selfId, floor(nShengWang) )
		str = format("获得#R声望%d#o的奖励", floor(count*0.25))
		BeginQuestEvent(sceneId);
			AddQuestText(sceneId, str);
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
		Msg2Player(sceneId,selfId,str,4,2)

		local awardMoney = level*count*0.25
		AddMoney( sceneId, selfId,1, floor(awardMoney) )
		str = format( "获得#R银卡#{_MONEY%d}#o的奖励", floor(awardMoney))
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, str);
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
		Msg2Player(sceneId,selfId, str,4,2)
		SetQuestData(sceneId, selfId, MD_GUOYUN_DATE[1], MD_GUOYUN_DATE[2], MD_GUOYUN_DATE[3], GetDayOfYear())
	
		--添加玩法日志
		GamePlayScriptLog( sceneId, selfId, 991)
		
	else
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "很抱歉，您不能领取津贴。")
		DispatchQuestTips(sceneId, selfId)
		EndQuestEvent(sceneId)
		Msg2Player(sceneId,selfId,"很抱歉，您不能领取津贴。",8,2)
	end	
	
end