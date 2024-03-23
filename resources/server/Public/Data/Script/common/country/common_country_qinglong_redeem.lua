x300658_g_ScriptId = 300658
x300658_g_MissionName = "【国家】领取青龙守护津贴"
x300658_g_GameId =1037
x300658_g_GongValud = 32

function x300658_ProcEnumEvent( sceneId, selfId, targetId, index )
	if GetGameOpenById(x300658_g_GameId) > 0 then
		-- if IsInCountrySpecialGuild(sceneId, selfId,0) > 0  then
		AddQuestNumText(sceneId,x300658_g_ScriptId, x300658_g_MissionName, 3)
		-- end
	end
	
end

function x300658_ProcEventEntry( sceneId , selfId , targetId , state , index )
	GetCountryQuestData(sceneId,selfId,CD_INDEX_CHUGUO_COUNT, x300658_g_ScriptId,-1,"OnReturn1")
end

function x300658_OnReturn1(sceneId, selfId,MissionData,MissionId)
	local count = MissionData + 1

	if count < -1 then
		return
	end

	if count == -1 then
		count = 0
	end
				
	if count > 10000 then
		count = 10000
	end
	
	local awardExp =0;
	local awardJinKa =0;
	local awardShengWang =0;
	local awardRongyu =0;
	local awardExp1 =0;
	local awardJinKa1 =0;
	local awardShengWang1 =0;
	local awardRongyu1 =0;
	local level = GetLevel(sceneId, selfId)
	local toggle = 0
		if IsQinglongZhuque(sceneId, selfId, 0) > 0 then
			awardRongyu =floor(count*3/10)
			awardExp =floor(level*70*count)
			awardJinKa =floor(100*count*0.5/10)
			awardShengWang =floor(count*3)
		elseif IsInCountrySpecialGuild(sceneId, selfId,0) > 0 then
			awardRongyu1 =floor(count*3/40)
			awardExp1 =floor(level*70/4*count)
			awardShengWang1 =floor(count*3/4)
			awardJinKa1 =floor(100*count*0.5/10/4)
		else 
			toggle = -1
		end
		
		local ding=0
		local liang=0
		local wen=0
		
		local ding1=0
		local liang1=0
		local wen1=0
		
		BeginQuestEvent(sceneId)
		local nExploit = GetExploit(sceneId,selfId)
		if IsQinglongZhuque(sceneId, selfId, 0) > 0 then
			awardJinKa =floor(100*count*0.5/10)
			ding = floor( awardJinKa / (1000*1000) )
			liang = floor( mod(awardJinKa,1000*1000)/ 1000 )
			wen = mod(awardJinKa,1000)
		elseif IsInCountrySpecialGuild(sceneId, selfId,0) > 0 then
			awardJinKa1 =floor(100*count*0.5/10/4)
			ding1 = floor( awardJinKa1 / (1000*1000) )
			liang1 = floor( mod(awardJinKa1,1000*1000)/ 1000 )
			wen1 = mod(awardJinKa1,1000)
		end
		
		local Readme = "#Y【国家】领取青龙守护津贴#r";
		local Readme2 = "\t#W青龙守护津贴，是每一个为守护国家做出贡献的，达到#R60级#W的#G青龙守护帮会成员#W及#G青龙之主#W都可以领取的奖励。#r"
		local Readme3 = "\t在发布#G出国令#W时间内，每个玩家完成#G出国任务的次数#W将直接影响当天守护津贴的多少。#r"
		local Readme4 = "\t每#G周一#W到#G周日#W，每天出国令期间#G出国任务的成功次数#W将会#G累计#W，在#G周日#W，可以领取一周的守护津贴。在功勋值足够的基础上，#G帮众#W领取#G基本#W津贴，#G帮主#W领取#G四倍#W津贴。#r"
		local Readme5 = "\t守护帮会成员每周功勋值不低于#G32#W点，每#G周日#W可以在我这里领取一周的守护津贴，功勋值是每人在出国令期间完成出国任务时获得。#r\t请问您是否要领取？"
		local award1 = format("#W您将获得#R%d#W荣誉奖励#r", awardRongyu);
		local award2 = format("您将获得#R%d#W经验奖励#r", awardExp);
		local award3 = format("您将获得#R%d#W声望奖励#r", awardShengWang);
		local award4 = format("您将获得#R%d#K锭#R%d#K两#R%d#K文金卡奖励", ding,liang,wen);
		local award5 = format("#W您将获得#R%d#W荣誉奖励#r", awardRongyu1);
		local award6 = format("您将获得#R%d#W经验奖励#r", awardExp1);
		local award7 = format("您将获得#R%d#W声望奖励#r", awardShengWang1);
		local award8 = format("您将获得#R%d#K锭#R%d#K两#R%d#K文金卡奖励", ding1,liang1,wen1);
		local award = "您现在拥有#G"..nExploit.."点#W功勋值";
		local blank=" #r";
			AddQuestText(sceneId,Readme..Readme2..Readme3..Readme4..Readme5)
		if toggle == 0 then
			if IsQinglongZhuque(sceneId, selfId, 0) > 0 then
			AddQuestText(sceneId,award..blank..award1..award2..award3..award4)
			elseif IsInCountrySpecialGuild(sceneId, selfId,0) > 0 then
			AddQuestText(sceneId,award..blank..award5..award6..award7..award8)
			end
		end
		EndQuestEvent(sceneId)	
		DispatchQuestInfo(sceneId,selfId,-1,x300658_g_ScriptId,-1)
		return 	
end


function x300658_ProcAcceptCheck( sceneId, selfId, NPCId )
		return 1
end

function x300658_ProcAccept( sceneId, selfId)
	local hour,minute,second = GetHourMinSec()
		if GetWeek() ~= 0 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, "很抱歉，只能在周日领取。")
			DispatchQuestTips(sceneId, selfId)
			EndQuestEvent(sceneId)
			Msg2Player(sceneId,selfId,"很抱歉，只能在周日领取。",8,2)
			return
		end
		if	GetLevel(sceneId, selfId) < 60 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, "很抱歉，达到60级才可以领取青龙守护津贴。")
			DispatchQuestTips(sceneId, selfId)
			EndQuestEvent(sceneId)
			Msg2Player(sceneId,selfId,"很抱歉，达到60级才可以领取青龙守护津贴。",8,2)
			return
		end
		if IsInCountrySpecialGuild(sceneId, selfId,0)~=1 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, "很抱歉，青龙守护帮会成员才可以领取青龙守护津贴。")
			DispatchQuestTips(sceneId, selfId)
			EndQuestEvent(sceneId)
			Msg2Player(sceneId,selfId,"很抱歉，青龙守护帮会成员才可以领取青龙守护津贴。",8,2)		
			return
		end
		
		if GetExploit(sceneId, selfId) < x300658_g_GongValud then
			local msg = format("很抱歉，您的功勋值不足%d点，不能领取。",x300658_g_GongValud)
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, msg)
			DispatchQuestTips(sceneId, selfId)
			EndQuestEvent(sceneId)
			Msg2Player(sceneId,selfId,msg,8,2)		
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
		
		local lastDay = GetQuestData(sceneId, selfId, MD_SHOUHU_DATE[1], MD_SHOUHU_DATE[2], MD_SHOUHU_DATE[3])
		local lastFortune = GetFortuneLastTime(sceneId, selfId, 1)

		if lastDay ~= 0 and GetDayOfYear() == lastDay then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, "很抱歉，已经领过青龙守护津贴。")
			DispatchQuestTips(sceneId, selfId)
			EndQuestEvent(sceneId)
			Msg2Player(sceneId,selfId,"很抱歉，已经领过青龙守护津贴。",8,2)
			return
		end
		
		local chuguo = GetQuestData(sceneId, selfId, MD_CHUGUO_DATE[1], MD_CHUGUO_DATE[2], MD_CHUGUO_DATE[3]) --出国津贴
		if  GetDayOfYear() == chuguo then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, "很抱歉，您已经领过本周出国津贴。")
			DispatchQuestTips(sceneId, selfId)
			EndQuestEvent(sceneId)
			Msg2Player(sceneId,selfId,"很抱歉，您已经领过本周出国津贴。",8,2)
			return
		end
		
		local guoyun = GetQuestData(sceneId, selfId, MD_GUOYUN_DATE[1], MD_GUOYUN_DATE[2], MD_GUOYUN_DATE[3]) --国运津贴
		if  GetDayOfYear() == guoyun  then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, "很抱歉，您已经领过本周国运津贴。")
			DispatchQuestTips(sceneId, selfId)
			EndQuestEvent(sceneId)
			Msg2Player(sceneId,selfId,"很抱歉，您已经领过本周国运津贴。",8,2)
			return
		end
		
		if lastFortune <= 0 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, "还未发布出国令")
			DispatchQuestTips(sceneId, selfId)
			EndQuestEvent(sceneId)
			Msg2Player(sceneId,selfId,"还未发布出国令",8,2)
			return
		end
		
		GetJoinGuildTime(sceneId,selfId,x300658_g_ScriptId)
end

function x300658_OnMemberJoinTimeReturn( sceneId, selfId, param )
	
	if param == -1 or GetCurrentTime()-param<24*3600 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "很抱歉，您加入青龙守护帮的时间低于24小时，不能领取津贴。")
		DispatchQuestTips(sceneId, selfId)
		EndQuestEvent(sceneId)
		Msg2Player(sceneId,selfId,"很抱歉，您加入青龙守护帮的时间低于24小时，不能领取津贴。",8,2)
		return		
	end
	
	GetCountryQuestData(sceneId,selfId,CD_INDEX_CREATE_QINGLONG_DATE, x300658_g_ScriptId,-1,"Newqinglong")
end

function x300658_Newqinglong(sceneId, selfId,MissionData,MissionId)
	local curDay = GetDayTime()
		if curDay == MissionData then
			BeginQuestEvent(sceneId);
			AddQuestText(sceneId, "很抱歉，当天上台的青龙守护成员不能领取工资");
			EndQuestEvent();
			DispatchQuestTips(sceneId, selfId);
			Msg2Player(sceneId,selfId,"很抱歉，当天上台的青龙守护成员不能领取工资",4,2)
			return
		end
	GetCountryQuestData(sceneId,selfId,CD_INDEX_CHUGUO_COUNT, x300658_g_ScriptId,-1,"OnReturn2")
end


function x300658_OnReturn2(sceneId, selfId,MissionData,MissionId)
	local selfGuildId = GetGuildID(sceneId, selfId)
	local country = GetCurCountry(sceneId, selfId)
	local officalId = -1
	local lastFortune = GetFortuneLastTime(sceneId, selfId, 1)
	
	local count = MissionData + 1
	if count < -1 then
		return
	end
	if count == -1 then
		count = 0
	end
	if count > 10000 then
		count = 10000
	end
	--给奖励
	if IsQinglongZhuque(sceneId, selfId, 0) > 0 then
		local level = GetLevel(sceneId, selfId)
		AddHonor( sceneId, selfId, floor(count*3/10) )
		local str=format("#o获得#R荣誉%d点#o的奖励", floor(count*3/10))
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, str);
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
		Msg2Player(sceneId,selfId,str,4,2)

		AddExp( sceneId, selfId, floor(level*70*count) )
		str=format("#o获得#R经验%d点#o的奖励", floor(level*70*count))
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, str);
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
		Msg2Player(sceneId,selfId,str,4,2)

		local awardMoney = floor(100*count*0.5)
		AddMoney( sceneId, selfId,3, floor(awardMoney/10) )
		str = format( "获得#R金卡#{_MONEY%d}#o的奖励", floor(awardMoney/10))
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, str);
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
		Msg2Player(sceneId,selfId, str,4,2)
		
		local nShengWang = GetShengWang( sceneId, selfId )
		local nShengWang1 = floor(3*count)
		nShengWang = nShengWang + nShengWang1
		SetShengWang( sceneId, selfId, nShengWang )
		str=format("#o获得#R声望%d点#o的奖励",nShengWang1)
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, str);
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
		Msg2Player(sceneId,selfId, str,4,2)
		SetQuestData(sceneId, selfId, MD_SHOUHU_DATE[1], MD_SHOUHU_DATE[2], MD_SHOUHU_DATE[3], GetDayOfYear())
		--添加玩法日志
			GamePlayScriptLog( sceneId, selfId, 1441)
			
	elseif IsInCountrySpecialGuild(sceneId, selfId,0) > 0 then --帮众
		local level = GetLevel(sceneId, selfId)
		AddHonor( sceneId, selfId, floor(count*3/10/4) )
		local str=format("#o获得#R荣誉%d点#o的奖励", floor(count*3/10/4))
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, str);
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
		Msg2Player(sceneId,selfId,str,4,2)

		AddExp( sceneId, selfId, floor(level*70*count/4) )
		str=format("#o获得#R经验%d点#o的奖励", floor(level*70*count/4))
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, str);
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
		Msg2Player(sceneId,selfId,str,4,2)

		local nShengWang = GetShengWang( sceneId, selfId )
		local nShengWang1 = floor(count*3/4)
		nShengWang = nShengWang + nShengWang1
		SetShengWang( sceneId, selfId, nShengWang )
		str=format("#o获得#R声望%d点#o的奖励",nShengWang1)
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, str);
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
		Msg2Player(sceneId,selfId,str,4,2)
		SetQuestData(sceneId, selfId, MD_SHOUHU_DATE[1], MD_SHOUHU_DATE[2], MD_SHOUHU_DATE[3], GetDayOfYear())

		local awardMoney = floor(100*count*0.5/4)
		AddMoney( sceneId, selfId,3, floor(awardMoney/10) )
		str = format( "获得#R金卡#{_MONEY%d}#o的奖励", floor(awardMoney/10))
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, str);
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
		Msg2Player(sceneId,selfId, str,4,2)
		
		--添加玩法日志
			GamePlayScriptLog( sceneId, selfId, 1441)
	end
		
end


	
	
	
	
	
	
	
	
	