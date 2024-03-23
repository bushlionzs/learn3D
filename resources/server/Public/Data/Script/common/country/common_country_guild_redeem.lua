 x300638_g_ScriptId = 300638
x300638_LevelLess		=	60
x300638_NeedExploit		= 28
x300638_g_DayLimited	=	1
x300638_g_GameId		=	1034
x300638_g_MissionName = "【国家】领取帮会津贴"
x300638_g_TalkContent = "\t帮会津贴，是每一个为帮会作出贡献的帮众都可以领取的奖励。\n\t参与#G成功护送神兽#W的次数，#G帮会战的战果#W，将直接影响每周帮会津贴的多少。\n\t等级不低于#G60#W，每周功勋值不低于#G28点#W的玩家，每#G周日#W可以在我这里领取一周的帮会津贴。\n\t确定要领取帮会津贴吗？#r"

--**********************************
--列举事件
--**********************************

function x300638_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
	if GetGameOpenById(x300638_g_GameId)<=0 then
		return
	end
	
	--if GetLevel(sceneId, selfId) < x300638_LevelLess then
	--	return
	--end
	
	
	
	AddQuestNumText(sceneId, x300638_g_ScriptId, x300638_g_MissionName,3)
			
end

function x300638_ProcEventEntry(sceneId, selfId, NPCId, MissionId)	--点击该任务后执行此脚本
	
	if GetGameOpenById(x300638_g_GameId)<=0 then
		return
	end

	BeginQuestEvent(sceneId)

		--任务信息
		local nGold = 2*1000
	local nSilver = 10*1000

	-- 帮会战
		local nCount1 = GetQuestData(sceneId, selfId, MD_GUILD_BHZ_WIN_COUNT[1], MD_GUILD_BHZ_WIN_COUNT[2], MD_GUILD_BHZ_WIN_COUNT[3])
		local nCount2 = GetQuestData(sceneId, selfId, MD_GUILD_BHZ_LOSE_COUNT[1], MD_GUILD_BHZ_LOSE_COUNT[2], MD_GUILD_BHZ_LOSE_COUNT[3])
		local nCount3 = GetQuestData(sceneId, selfId, MD_GUILD_BHZ_PING_COUNT[1], MD_GUILD_BHZ_PING_COUNT[2], MD_GUILD_BHZ_PING_COUNT[3])

		if x300638_IsNewPeroid(sceneId, selfId,MD_GUILD_BHZ_DATE)>0 then
			nCount1 = 0
			nCount2 = 0
			nCount3 = 0
		end

	--x300638_ShowTips(sceneId, selfId,format("nCount2 = %d, nCount3 = %d",nCount2,nCount3))

		nGold = nGold + nCount1*4*1000+(nCount2+nCount3)*2*1000
		nSilver = nSilver + nCount1*20*1000+ (nCount2+nCount3)*10*1000

	--帮会战 end

	--帮会运镖 start
		local nCount4 = GetQuestData(sceneId, selfId, MD_GUILD_YB_WEEK_COUNT[1], MD_GUILD_YB_WEEK_COUNT[2], MD_GUILD_YB_WEEK_COUNT[3])
	
		if x300638_IsNewPeroid(sceneId, selfId,MD_GUILD_YB_DATE)>0 then
		
			nCount4 = 0
		end
		local nExploit = GetExploit(sceneId,selfId)
		local award1 = "您现在拥有#G"..nExploit.."点#W功勋值";
		local award2 = "您本周参加了#G"..(nCount1+nCount2+nCount3).."次#W帮会战";
		local award3 = "您本周成功护送了#G"..nCount4.."次#W神兽";
		nGold = nGold + nCount4*1*1000
		nSilver = nSilver + nCount4*5*1000
		local ding=0
		local liang=0
		local wen=0
		ding = floor( nGold / (1000*1000) )
		liang = floor( mod(nGold,1000*1000)/ 1000 )
		wen = mod(nGold,1000)
		local award4 = format("您将获得#R%d锭%d两%d文#W金卡奖励", ding,liang,wen);
		ding = floor( nSilver / (1000*1000) )
		liang = floor( mod(nSilver,1000*1000)/ 1000 )
		wen = mod(nSilver,1000)
		local award5 = format("您将获得#R%d锭%d两%d文#W银卡奖励", ding,liang,wen);
		AddQuestText(sceneId,"#Y"..x300638_g_MissionName)
		local blank=" #r";
		AddQuestText(sceneId,x300638_g_TalkContent..blank..award1..blank..award2..blank..award3..blank..award4..blank..award5)
		EndQuestEvent()
		DispatchQuestInfo(sceneId, selfId, NPCId, x300638_g_ScriptId, -1);
		if  nExploit < 28 then
			local Readme_1 = "您将获得#R0锭0两0文#W金卡奖励"
			local Readme_2 = "您将获得#R0锭0两0文#W银卡奖励"
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,x300638_g_TalkContent..blank..award1..blank..award2..blank..award3..blank..Readme_1..blank..Readme_2)
			EndQuestEvent()
			DispatchQuestInfo(sceneId, selfId, NPCId, x300638_g_ScriptId, -1);
		end
	
end

---------------------------------------------------------------------------------------------------
--申请进入副本
---------------------------------------------------------------------------------------------------
function x300638_ProcAcceptCheck( sceneId, selfId, NPCId )
	if GetGameOpenById(x300638_g_GameId)<=0 then
		return
	end
	if GetGuildID(sceneId, selfId)<0 then
		x300638_ShowTips(sceneId, selfId, "很抱歉，您还没有加入帮会，不能领取。")
		return 0;
	end

	if GetLevel(sceneId, selfId) < x300638_LevelLess then
		x300638_ShowTips(sceneId, selfId, format("很抱歉，等级未达到%d级，不能领取。",x300638_LevelLess))
		return 0;
	end

	if GetWeek() ~=0 then
		x300638_ShowTips(sceneId, selfId, "很抱歉，只能在周日领取。")
		return 0;
	end

	if GetExploit(sceneId,selfId) < x300638_NeedExploit then
		x300638_ShowTips(sceneId, selfId, format("很抱歉，您的功勋值不足%d，不能领取。",x300638_NeedExploit))
		return 0;
	end

	if x300638_GetDayCount(sceneId, selfId)>=x300638_g_DayLimited then
		x300638_ShowTips(sceneId, selfId,"很抱歉，您本周已领取过帮会津贴了，请下周日再来")
		return 0;
	end

    return 1
end

----------------------------------------------------------------------------------------------
--点确定后
----------------------------------------------------------------------------------------------
function x300638_ProcAccept( sceneId, selfId )
	if GetGameOpenById(x300638_g_GameId)<=0 then
		return
	end

	x300638_OnGiveReward( sceneId, selfId)
	
end

function x300638_OnGiveReward( sceneId, selfId)

	
	
	local nGold = 2*1000
	local nSilver = 10*1000

	-- 帮会战
	local nCount1 = GetQuestData(sceneId, selfId, MD_GUILD_BHZ_WIN_COUNT[1], MD_GUILD_BHZ_WIN_COUNT[2], MD_GUILD_BHZ_WIN_COUNT[3])
	local nCount2 = GetQuestData(sceneId, selfId, MD_GUILD_BHZ_LOSE_COUNT[1], MD_GUILD_BHZ_LOSE_COUNT[2], MD_GUILD_BHZ_LOSE_COUNT[3])
	local nCount3 = GetQuestData(sceneId, selfId, MD_GUILD_BHZ_PING_COUNT[1], MD_GUILD_BHZ_PING_COUNT[2], MD_GUILD_BHZ_PING_COUNT[3])

	if x300638_IsNewPeroid(sceneId, selfId,MD_GUILD_BHZ_DATE)>0 then
		nCount1 = 0
		nCount2 = 0
		nCount3 = 0
	end

	--x300638_ShowTips(sceneId, selfId,format("nCount2 = %d, nCount3 = %d",nCount2,nCount3))

	nGold = nGold + nCount1*4*1000+(nCount2+nCount3)*2*1000
	nSilver = nSilver + nCount1*20*1000+ (nCount2+nCount3)*10*1000

	--帮会战 end

	--帮会运镖 start
	local nCount4 = GetQuestData(sceneId, selfId, MD_GUILD_YB_WEEK_COUNT[1], MD_GUILD_YB_WEEK_COUNT[2], MD_GUILD_YB_WEEK_COUNT[3])
	
	if x300638_IsNewPeroid(sceneId, selfId,MD_GUILD_YB_DATE)>0 then
		
		nCount4 = 0
	end

	--x300638_ShowTips(sceneId, selfId,format("nCount2 = %d, nCount3 = %d nCount4 =%d",nCount2,nCount3,nCount4))

	nGold = nGold + nCount4*1*1000
	nSilver = nSilver + nCount4*5*1000
	--帮会运镖 end



	AddMoney(sceneId, selfId, 3, nGold)
	AddMoney(sceneId, selfId, 1, nSilver)

	x300638_ShowTips(sceneId, selfId,format("获得%d两金卡",nGold/1000))
	x300638_ShowTips(sceneId, selfId,format("获得%d两银卡",nSilver/1000))

	x300638_SetDayCount(sceneId, selfId)

	-- write log
	GamePlayScriptLog(sceneId, selfId, 1351)  --玩法Log

	local str = format("x300638_OnGiveReward guid = %x, name=%s, nGold= %d, nSilver=%d, nCount1 = %d, nCount2 = %d, nCount3 = %d nCount4 =%d",GetPlayerGUID( sceneId,selfId ),GetName(sceneId, selfId),nGold,nSilver,nCount1,nCount2,nCount3,nCount4)
	WriteLog(1, str)
	
end



function x300638_SaveGuildWeekResult(sceneId,guildId, nValue)
-------------------------------------------
--@param nValue: 0:负， 1：平， 2：胜利
-------------------------------------------
	if GetGameOpenById(x300638_g_GameId)<=0 then
		return
	end
	if nValue ~=0 and nValue ~=1 and nValue ~=2 then
		return
	end

	local sceneType = GetSceneType(sceneId) ;
	if sceneType~=2 then
		local str = format("x300638_SaveGuildWeekResult not Banghuizhan Scene= %d",sceneId)
		WriteLog(1, str)
		return
	end

	local nHumanCount = GetScenePlayerCount( sceneId )
    local i = 0
    for i = 0,nHumanCount-1 do
        local selfId = GetScenePlayerObjId( sceneId,i)
        if selfId >= 0 then
            local nGuildId = GetGuildID( sceneId,selfId )
            if nGuildId == guildId then
				
				local nCount1 = GetQuestData(sceneId, selfId, MD_GUILD_BHZ_WIN_COUNT[1], MD_GUILD_BHZ_WIN_COUNT[2], MD_GUILD_BHZ_WIN_COUNT[3])
				local nCount2 = GetQuestData(sceneId, selfId, MD_GUILD_BHZ_LOSE_COUNT[1], MD_GUILD_BHZ_LOSE_COUNT[2], MD_GUILD_BHZ_LOSE_COUNT[3])
				local nCount3 = GetQuestData(sceneId, selfId, MD_GUILD_BHZ_PING_COUNT[1], MD_GUILD_BHZ_PING_COUNT[2], MD_GUILD_BHZ_PING_COUNT[3])
				if x300638_IsNewPeroid(sceneId, selfId,MD_GUILD_BHZ_DATE)>0 then
					SetQuestData(sceneId, selfId, MD_GUILD_BHZ_DATE[1], MD_GUILD_BHZ_DATE[2], MD_GUILD_BHZ_DATE[3], GetDayOfYear())
					SetQuestData(sceneId, selfId, MD_GUILD_BHZ_WIN_COUNT[1], MD_GUILD_BHZ_WIN_COUNT[2], MD_GUILD_BHZ_WIN_COUNT[3], 0)
					SetQuestData(sceneId, selfId, MD_GUILD_BHZ_LOSE_COUNT[1], MD_GUILD_BHZ_LOSE_COUNT[2], MD_GUILD_BHZ_LOSE_COUNT[3], 0)
					SetQuestData(sceneId, selfId, MD_GUILD_BHZ_PING_COUNT[1], MD_GUILD_BHZ_PING_COUNT[2], MD_GUILD_BHZ_PING_COUNT[3], 0)
					nCount1 = 0
					nCount2 = 0
					nCount3 = 0
				end
				
				if nValue==2 then
					nCount1 = nCount1 + 1
					SetQuestData(sceneId, selfId, MD_GUILD_BHZ_WIN_COUNT[1], MD_GUILD_BHZ_WIN_COUNT[2], MD_GUILD_BHZ_WIN_COUNT[3], nCount1)
				elseif nValue==1 then
					nCount2 = nCount2 + 1
					SetQuestData(sceneId, selfId, MD_GUILD_BHZ_LOSE_COUNT[1], MD_GUILD_BHZ_LOSE_COUNT[2], MD_GUILD_BHZ_LOSE_COUNT[3], nCount2)
				elseif nValue==0 then
					nCount3 = nCount3 + 1
					SetQuestData(sceneId, selfId, MD_GUILD_BHZ_PING_COUNT[1], MD_GUILD_BHZ_PING_COUNT[2], MD_GUILD_BHZ_PING_COUNT[3], nCount3)
				end
            end
        end
    end

end

function x300638_SaveGuildYunBiaoMD(sceneId, selfId)
	if GetGameOpenById(x300638_g_GameId)<=0 then
		return
	end
	
	local nCount1 = GetQuestData(sceneId, selfId, MD_GUILD_YB_WEEK_COUNT[1], MD_GUILD_YB_WEEK_COUNT[2], MD_GUILD_YB_WEEK_COUNT[3])
	
	if x300638_IsNewPeroid(sceneId, selfId,MD_GUILD_YB_DATE)>0 then
		SetQuestData(sceneId, selfId, MD_GUILD_YB_DATE[1], MD_GUILD_YB_DATE[2], MD_GUILD_YB_DATE[3], GetDayOfYear())
		SetQuestData(sceneId, selfId, MD_GUILD_YB_WEEK_COUNT[1], MD_GUILD_YB_WEEK_COUNT[2], MD_GUILD_YB_WEEK_COUNT[3], 0)
		nCount1 = 0
	end
	
	nCount1 = nCount1 + 1
	SetQuestData(sceneId, selfId, MD_GUILD_YB_WEEK_COUNT[1], MD_GUILD_YB_WEEK_COUNT[2], MD_GUILD_YB_WEEK_COUNT[3], nCount1)
	
end




---------------------------------------------------------------------------------------------------
--取得当前次数
---------------------------------------------------------------------------------------------------
function x300638_IsNewPeroid(sceneId, selfId, md_date)



	local today = GetDayOfYear()

	local lastday = GetQuestData(sceneId, selfId, md_date[1], md_date[2],md_date[3] );
	
	if today>=lastday then
		local nWeek = GetWeek()
		if nWeek==0 then
			nWeek =7
		end
		if (today-lastday)>=nWeek then  --如果在周期之外
			return 1
		end
	else
		return 1
	end

	return 0


end


function x300638_ShowTips(sceneId, selfId, str)
	BeginQuestEvent(sceneId);
		AddQuestText(sceneId,str);
	EndQuestEvent();
	DispatchQuestTips(sceneId, selfId);
end

---------------------------------------------------------------------------------------------------
--取得当前次数
---------------------------------------------------------------------------------------------------
function x300638_GetDayCount(sceneId, selfId)
	local today = GetDayOfYear()
	local lastday = GetQuestData(sceneId, selfId, MD_GUILD_JINTIE_DATE[1], MD_GUILD_JINTIE_DATE[2],MD_GUILD_JINTIE_DATE[3] );
	
	if lastday ~= today then
		return 0
	end

	local daycount = GetQuestData(sceneId, selfId, MD_GUILD_JINTIE_DAYCOUNT[1], MD_GUILD_JINTIE_DAYCOUNT[2],MD_GUILD_JINTIE_DAYCOUNT[3] );
	return daycount;
end

---------------------------------------------------------------------------------------------------
--设置当天次数
---------------------------------------------------------------------------------------------------
function x300638_SetDayCount(sceneId, selfId)

	local today = GetDayOfYear()

	local lastday = GetQuestData(sceneId, selfId, MD_GUILD_JINTIE_DATE[1], MD_GUILD_JINTIE_DATE[2], MD_GUILD_JINTIE_DATE[3])

	if lastday ~= today then
		SetQuestData(sceneId, selfId, MD_GUILD_JINTIE_DATE[1], MD_GUILD_JINTIE_DATE[2], MD_GUILD_JINTIE_DATE[3], today)
		SetQuestData(sceneId, selfId, MD_GUILD_JINTIE_DAYCOUNT[1], MD_GUILD_JINTIE_DAYCOUNT[2], MD_GUILD_JINTIE_DAYCOUNT[3], 1)
	else
		local daycount = GetQuestData(sceneId, selfId, MD_GUILD_JINTIE_DAYCOUNT[1], MD_GUILD_JINTIE_DAYCOUNT[2], MD_GUILD_JINTIE_DAYCOUNT[3])
		SetQuestData(sceneId, selfId, MD_GUILD_JINTIE_DAYCOUNT[1], MD_GUILD_JINTIE_DAYCOUNT[2], MD_GUILD_JINTIE_DAYCOUNT[3], daycount+1)
	end

	SetQuestData(sceneId, selfId, MD_GUILD_BHZ_DATE[1], MD_GUILD_BHZ_DATE[2], MD_GUILD_BHZ_DATE[3], 0)
	SetQuestData(sceneId, selfId, MD_GUILD_BHZ_WIN_COUNT[1], MD_GUILD_BHZ_WIN_COUNT[2], MD_GUILD_BHZ_WIN_COUNT[3], 0)
	SetQuestData(sceneId, selfId, MD_GUILD_BHZ_LOSE_COUNT[1], MD_GUILD_BHZ_LOSE_COUNT[2], MD_GUILD_BHZ_LOSE_COUNT[3], 0)
	SetQuestData(sceneId, selfId, MD_GUILD_BHZ_PING_COUNT[1], MD_GUILD_BHZ_PING_COUNT[2], MD_GUILD_BHZ_PING_COUNT[3], 0)
	SetQuestData(sceneId, selfId, MD_GUILD_YB_DATE[1], MD_GUILD_YB_DATE[2], MD_GUILD_YB_DATE[3], 0)
	SetQuestData(sceneId, selfId, MD_GUILD_YB_WEEK_COUNT[1], MD_GUILD_YB_WEEK_COUNT[2], MD_GUILD_YB_WEEK_COUNT[3], 0)
end