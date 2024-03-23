--***********************
--Const
--***********************
-------------------------

--MisDescBegin


x350005_g_ScriptId = 350005
x350005_g_MissionName = "【国家】国王争霸赛奖励领取"
x350005_g_LevelLess = 30
x350005_g_DayCountLimited = 1

function x350005_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	
	local week = GetWeek()
	local hour,minute,second = GetHourMinSec()
	if (week == 0 and hour >= 21 and hour < 23) then
		AddQuestNumText(sceneId, x350005_g_ScriptId, x350005_g_MissionName,3);
	else
		return
	end


	
end


---------------------------------------------------------------------------------------------------
--向客户端发送任务未完成
---------------------------------------------------------------------------------------------------
function x350005_ProcEventEntry( sceneId, selfId, targetId, MissionId, nExt )
	local experience = 0
	local name = ""
	local nCountry = GetCurCountry(sceneId, selfId)
	local nRank = GetCountryRank(nCountry)
	local Rank = nRank + 1
	local level = GetLevel(sceneId, selfId)
	if  nRank == 0 then
		experience = level*30000*1
	elseif nRank == 1 then
		experience = level*30000*0.9
	elseif nRank == 2 then
		experience = level*30000*0.8
	elseif nRank == 3 then
		experience = level*30000*0.7
	end
	if  nCountry == 0 then
		name = "楼兰王国"
	elseif nCountry == 1 then
		name = "天山王国"
	elseif nCountry == 2 then
		name = "昆仑王国"
	elseif nCountry == 3 then
		name = "敦煌王国"
	end
	
	BeginQuestEvent(sceneId);
	local Readme1 = format("\t#G所属国家：#Y%s#r", name)
	local Readme2 = format("\t#G上周排名：第#Y%s#G名#r", Rank)
	local Readme3 = " #r"
	local Readme4 = format("\t#G由于#Y%s#G在上周的出色表现，您可以领取到丰厚奖励，希望您为国家多做贡献，提升国家实力。#r", name)
	local Readme5 = " #r"
	local Readme6 = "\t#G您获得的国王争霸赛的奖励如下：#r"
	local Readme7 = " #r"
	local Readme8 = " #r"
	local Readme9 = format( "\t#Y经验：%d", experience)
	local Readme  =  Readme1..Readme2..Readme3..Readme4..Readme5..Readme6..Readme7..Readme8..Readme9
	AddQuestText(sceneId, Readme);
	EndQuestEvent();
	DispatchQuestInfo(sceneId, selfId, targetId, x350005_g_ScriptId, -1);
end


function x350005_ProcAcceptCheck(sceneId, selfId, targetId, MissionId )
	local level = GetLevel(sceneId, selfId)
	if level < 30 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "30级以下不能领取国王争霸赛奖励！");
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		local Readme = "30级以下不能领取国王争霸赛奖励！"
		Msg2Player(sceneId,selfId,Readme,8,2)
		return 0
	end
	return 1;

end

function x350005_CheckRequest(sceneId, selfId)
	-- local level = GetLevel(sceneId, selfId)
	-- if level < 30 then
		-- BeginQuestEvent(sceneId)
		-- AddQuestText(sceneId, "30级以下不能领取国王争霸赛奖励！");
		-- EndQuestEvent(sceneId)
		-- DispatchQuestTips(sceneId,selfId)
		-- local Readme = "30级以下不能领取国王争霸赛奖励！"
		-- Msg2Player(sceneId,selfId,Readme,8,2)
		-- return 0
	-- end

	if x350005_g_DayCountLimited >0 then
		local nDayCount = x350005_GetDayCount(sceneId, selfId)
		if nDayCount >= x350005_g_DayCountLimited then
			x350005_ShowTips(sceneId, selfId, "很抱歉，【国家】国王争霸赛的奖励每周只能领取一次。")
			return 0;
		end
	end

	return 1;

end

function x350005_ShowTips(sceneId, selfId, str)
	BeginQuestEvent(sceneId);
	AddQuestText(sceneId,str);
	EndQuestEvent();
	DispatchQuestTips(sceneId, selfId);
end

function x350005_ProcAccept( sceneId, selfId )
	x350005_CheckRequest(sceneId, selfId)
	x350005_GiveReward(sceneId,selfId)	
end


function x350005_GiveReward(sceneId,selfId)
	--奖励经验
	local experience = 0
	local nCountry = GetCurCountry(sceneId, selfId)
	local nRank = GetCountryRank(nCountry)
	local level = GetLevel(sceneId, selfId)
	if  nRank == 0 then
		experience = level*30000*1
	elseif nRank == 1 then
		experience = level*30000*0.9
	elseif nRank == 2 then
		experience = level*30000*0.8
	elseif nRank == 3 then
		experience = level*30000*0.7
	end
	
	local nDayCount = x350005_GetDayCount(sceneId, selfId)
	if nDayCount < x350005_g_DayCountLimited then
		AddExp(sceneId, selfId, experience);
		
		local str = "#o获得#R经验"..experience.."点#o的奖励"
		x350005_ShowTips(sceneId, selfId, str)
		Msg2Player(sceneId,selfId,str,4,2)
		
		x350005_SetDayCount(sceneId,selfId)
	end
		
end

---------------------------------------------------------------------------------------------------
--取得当前次数
---------------------------------------------------------------------------------------------------
function x350005_GetDayCount(sceneId, selfId)

	local today = GetDayOfYear() + 1	--排除0的情况
	local lastday = GetQuestData(sceneId, selfId, MD_COUNTRY_TOPLIST_PRISE_DATE[1], MD_COUNTRY_TOPLIST_PRISE_DATE[2],MD_COUNTRY_TOPLIST_PRISE_DATE[3] );
	
	if lastday ~= today then
		return 0
	end
	
	return 1;

end

---------------------------------------------------------------------------------------------------
--设置当天次数
---------------------------------------------------------------------------------------------------
function x350005_SetDayCount(sceneId, selfId)

	local today = GetDayOfYear() + 1
	SetQuestData(sceneId, selfId, MD_COUNTRY_TOPLIST_PRISE_DATE[1], MD_COUNTRY_TOPLIST_PRISE_DATE[2], MD_COUNTRY_TOPLIST_PRISE_DATE[3], today)
end