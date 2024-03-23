
x300637_g_ScriptId          		= 300637
x300637_g_Leader_Index      		= 5
x300637_g_MissionName       		="【国家】领取国民津贴"
x300637_g_HaveBonusThisWeek			="\t您本周已经领取过国民津贴了，每周只能领取一次。"
x300637_g_LevelError				="\t很遗憾，只有不低于60级的玩家才可以领取国民津贴。"
x300637_g_WeekDayError				="\t很遗憾，只有周日才可以领取国民津贴。"
x300637_g_ExploitError				="\t很遗憾，只有本周功勋值不低于18点的玩家才能领取国民津贴。"
x300637_g_BonusTips					="#Y【国家】领取国民津贴\n\t#W国民津贴，是为了奖励国家普通国民对国家做出的贡献。\n\t每天是否能坚持完成#G一整轮内政#W，将直接影响国民津贴的多少。\n\t等级不低于#G60#W，每周功勋值不低于#G18#W点的玩家，每#G周日#W可以在我这里领取国民津贴。#r \n\t您本周的功勋值为#G%d#W\n\t您本周共完成了#G%d#W轮内政任务\n\t按照以上的统计，您共可以领取：\n\t#R%d#W锭#R%d#W两#R%d#W文金卡\n\t#R%d#W锭#R%d#W两#R%d#W文两现银"
x300637_g_GiveBonusTips				="#Y领取国民津贴成功，您获得#R%d#Y锭#R%d#Y两#R%d#Y文金卡的奖励。"
x300637_g_GiveBonusTips1			="#Y领取国民津贴成功，您获得#R%d#Y锭#R%d#Y两#R%d#Y文两现银的奖励。"
x300637_g_GameOpenID				= 1033
x300637_g_GamePlayID				= 1342


----------------------------------------------------------------------------------------------
--取得今天的是第几个周
----------------------------------------------------------------------------------------------
function x300637_GetCurrentWeek()
	
	--取得今天的日期
	local nCurrentTime = (GetCurrentTime()+8*3600)/86400 - 4  --换算成天
	local nWeek = floor(nCurrentTime / 7)		 --换算成周,并取整
	return nWeek
end

----------------------------------------------------------------------------------------------
--取得最后一周0
----------------------------------------------------------------------------------------------
function x300637_GetLastWeek(sceneId,selfId)
	
	return GetQuestData(sceneId,selfId,MD_COUNTRY_PERSON_REDEEM_WEEK[1],MD_COUNTRY_PERSON_REDEEM_WEEK[2],MD_COUNTRY_PERSON_REDEEM_WEEK[3])
	
end

----------------------------------------------------------------------------------------------
--设置最后一周
----------------------------------------------------------------------------------------------
function x300637_SetLastWeek(sceneId,selfId)
	
	SetQuestData(sceneId,selfId,MD_COUNTRY_PERSON_REDEEM_WEEK[1],MD_COUNTRY_PERSON_REDEEM_WEEK[2],MD_COUNTRY_PERSON_REDEEM_WEEK[3],x300637_GetCurrentWeek())
end

----------------------------------------------------------------------------------------------
--枚举
----------------------------------------------------------------------------------------------
function x300637_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	
	--活动是否开启
	if GetGameOpenById(x300637_g_GameOpenID) ~= 1 then
		return
	end
	
	--刷新BUF列表
	AddQuestNumText(sceneId,x300637_g_ScriptId,x300637_g_MissionName,3,-1);
	
end

----------------------------------------------------------------------------------------------
--默认事件
----------------------------------------------------------------------------------------------
function x300637_ProcEventEntry( sceneId, selfId, targetId,scriptId,idExt )

	--活动是否开启
	if GetGameOpenById(x300637_g_GameOpenID) ~= 1 then
		return
	end
--
--	--检查是否领过
--	if x300637_GetCurrentWeek() == x300637_GetLastWeek(sceneId,selfId) then
--		BeginQuestEvent(sceneId)
--			AddQuestText(sceneId,x300637_g_HaveBonusThisWeek)
--	    EndQuestEvent(sceneId)
--		DispatchQuestEventList(sceneId,selfId,targetId)
--		return
--	end
--
--	--检查等级
	local level = GetLevel(sceneId,selfId)
--	if level < 60 then
--		BeginQuestEvent(sceneId)
--			AddQuestText(sceneId,x300637_g_LevelError)
--	    EndQuestEvent(sceneId)
--		DispatchQuestEventList(sceneId,selfId,targetId)
--		return
--	end
--	
--	--检查时间
	local nWeekDay = GetWeek()
--	if nWeekDay ~= 0 then
--		BeginQuestEvent(sceneId)
--			AddQuestText(sceneId,x300637_g_WeekDayError)
--	    EndQuestEvent(sceneId)
--		DispatchQuestEventList(sceneId,selfId,targetId)
--		return
--	end
--	
--	--检查功勋
	local nExploit = GetExploit(sceneId,selfId)
--	if nExploit < 18 then
--		BeginQuestEvent(sceneId)
--			AddQuestText(sceneId,x300637_g_ExploitError)
--	    EndQuestEvent(sceneId)
--		DispatchQuestEventList(sceneId,selfId,targetId)
--		return
--	end
--	
	--计算奖励
	local money1 = 0		--金卡
	local money2 = 0		--现银
	if nExploit >=18 then
		money1 = 2*1000   --金卡
		money2 = 8*1000   --现银
	else
		money1 = 0
		money2 = 0
    end

	local ding = 0
	local liang = 0
	local wen = 0
	local ding1 = 0
	local liang1 = 0
	local wen1 = 0
	
	local lastweek = GetQuestData(sceneId,selfId,MD_NEIZHENG_WEEK[1],MD_NEIZHENG_WEEK[2],MD_NEIZHENG_WEEK[3])
	local round = GetQuestData(sceneId,selfId,MD_NEIZHENG_WEEKCOUNT[1],MD_NEIZHENG_WEEKCOUNT[2],MD_NEIZHENG_WEEKCOUNT[3])
	
	if round < 0 then 
		round = 0 
	end
	
	--如果周不匹配
	if x300637_GetCurrentWeek() ~= lastweek then
		round = 0
	end
	
	money1 = money1 + round*1000
	money2 = money2 + round*4*1000
	 local	ding = floor( money1 / (1000*1000) )
	 local	liang = floor( mod(money1,1000*1000)/ 1000 )
	 local  wen = mod(money1,1000)
	 local	ding1 = floor( money2 / (1000*1000) )
	 local	liang1 = floor( mod(money2,1000*1000)/ 1000 )
	 local  wen1 = mod(money2,1000)
	--格式化相关信息
	local msg = format(x300637_g_BonusTips,nExploit,round,ding,liang,wen,ding1,liang1,wen1)

	--所有检查通过，则显示奖励界面
	BeginQuestEvent(sceneId)
		AddQuestText(sceneId,msg)
    EndQuestEvent(sceneId)
	DispatchQuestInfoNM( sceneId, selfId, targetId, x300637_g_ScriptId, x300637_g_ScriptId)
end

----------------------------------------------------------------------------------------------
--检测接受条件
----------------------------------------------------------------------------------------------
function x300637_ProcAcceptCheck( sceneId, selfId, NPCId )
	
	--活动是否开启
	if GetGameOpenById(x300637_g_GameOpenID) ~= 1 then
		return 0
	end
	
    return 1
end

----------------------------------------------------------------------------------------------
--接受
----------------------------------------------------------------------------------------------
function x300637_ProcAccept( sceneId, selfId )
	
	--活动是否开启
	if GetGameOpenById(x300637_g_GameOpenID) ~= 1 then
		return
	end
	
	--检查是否领过
	if x300637_GetCurrentWeek() == x300637_GetLastWeek(sceneId,selfId) then
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,x300637_g_HaveBonusThisWeek)
	    EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return
	end

	--检查等级
	local level = GetLevel(sceneId,selfId)
	if level < 60 then
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,x300637_g_LevelError)
	    EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return
	end
	
	--检查时间
	local nWeekDay = GetWeek()
	if nWeekDay ~= 0 then
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,x300637_g_WeekDayError)
	    EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return
	end
	
	--检查功勋
	local nExploit = GetExploit(sceneId,selfId)
	if nExploit < 18 then
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,x300637_g_ExploitError)
	    EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return
	end
	
	--计算奖励
	local money1 = 2*1000		--金卡
	local money2 = 8*1000		--现银
	local ding = 0
	local liang = 0
	local wen = 0
	local ding1 = 0
	local liang1 = 0
	local wen1 = 0
	
	
	local lastweek = GetQuestData(sceneId,selfId,MD_NEIZHENG_WEEK[1],MD_NEIZHENG_WEEK[2],MD_NEIZHENG_WEEK[3])
	local round = GetQuestData(sceneId,selfId,MD_NEIZHENG_WEEKCOUNT[1],MD_NEIZHENG_WEEKCOUNT[2],MD_NEIZHENG_WEEKCOUNT[3])
	
	if round < 0 then 
		round = 0 
	end
	
	--如果周不匹配
	if x300637_GetCurrentWeek() ~= lastweek then
		round = 0
	end
	
	money1 = money1 + round*1000
	money2 = money2 + round*4*1000
	
	--添加金卡
	AddMoney(sceneId,selfId,3,money1,x300637_g_ScriptId)
	
	--添加现银
	AddMoney(sceneId,selfId,0,money2,x300637_g_ScriptId)
	
	--设置领取的最后周
	x300637_SetLastWeek(sceneId,selfId)
	
	--记录玩法日志
	GamePlayScriptLog(sceneId,selfId,x300637_g_GamePlayID)

	--获取奖历提示
	 local	ding = floor( money1 / (1000*1000) )
	 local	liang = floor( mod(money1,1000*1000)/ 1000 )
	 local  wen = mod(money1,1000)
	 local	ding1 = floor( money2 / (1000*1000) )
	 local	liang1 = floor( mod(money2,1000*1000)/ 1000 )
	 local  wen1 = mod(money2,1000)
		
	local msg  = format(x300637_g_GiveBonusTips,ding,liang,wen)
	local msg1 = format(x300637_g_GiveBonusTips1,ding1,liang1,wen1)
	Msg2Player(sceneId, selfId, msg, 0, 3)
	Msg2Player(sceneId, selfId, msg1, 0, 3)
end

----------------------------------------------------------------------------------------------
--放弃
----------------------------------------------------------------------------------------------
function x300637_ProcQuestAbandon( sceneId, selfId, MissionId )
end

----------------------------------------------------------------------------------------------
--继续
----------------------------------------------------------------------------------------------
function x300637_OnContinue( sceneId, selfId, targetId )
end

----------------------------------------------------------------------------------------------
--检测是否可以提交
----------------------------------------------------------------------------------------------
function x300637_CheckSubmit( sceneId, selfId )
end

----------------------------------------------------------------------------------------------
--提交
----------------------------------------------------------------------------------------------
function x300637_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end

----------------------------------------------------------------------------------------------
--杀死怪物或玩家
----------------------------------------------------------------------------------------------
function x300637_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end

----------------------------------------------------------------------------------------------
--进入区域事件
----------------------------------------------------------------------------------------------
function x300637_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

----------------------------------------------------------------------------------------------
--道具改变
----------------------------------------------------------------------------------------------
function x300637_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
