--收集战马 add by 齐亮（081227）


x300516_g_ScriptId = 300516
x300516_g_MissionName = "【个人】内政任务"
-- 交任务描述文本
x300516_g_strMissionSubmitContent = "\t你捕捉到我要的马了吗？"
x300516_g_strWrongHorse = "\t这不是我要的马。"
x300516_g_strGoodHorse = "\t这是一匹千载难逢的良马幼仔，你真的要把它交给国家吗？"
x300516_g_strNormalHorse = "\t感谢你给我们提供战马，你真的要把它交给国家吗？"

-- 收马任务ID
x300516_g_CollectHorse_Mission_ID	= 6430
x300516_g_CollectHorse_Mission_ID_End   = 6446
x300516_g_CollectHorse_Young		= 6445
-- 提交的是否是良种马标记
x300516_g_IsGoodHorse = 2
-- 所提交马的GUID高32位(UINT)
x300516_g_CommitedHorseID_HIGH = 4
-- 所提交马的GUID低32位(UINT)
x300516_g_CommitedHorseID_LOW = 5
--每个循环的环数
x300516_OneRoundCount = 10
--每日高奖次数
x300516_HighBonusCircleCount = 10
x300516_LevelToCapital = 300	--大都任务的开始等级
-- 显示完成信息
function x300516_OnCanCompleteMission ( sceneId, selfId, targetId, MissionId )

	local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId)
	
		BeginQuestEvent( sceneId)
		--任务名称
			AddQuestText(sceneId, "#Y"..x300516_g_MissionName)
			AddQuestText( sceneId, x300516_g_strMissionSubmitContent)
		EndQuestEvent()
		DispatchQuestEventList( sceneId, selfId, targetId)

	    -- 通知客户端显示宠物列表窗口
		BeginUICommand( sceneId);
			UICommand_AddInt( sceneId, x300516_g_ScriptId);
			UICommand_AddInt( sceneId, MissionId);
			UICommand_AddInt( sceneId, targetId);
			DispatchUICommand( sceneId, selfId, 101);
		EndUICommand( sceneId)
		
		return 0
end

-- 根据提交的宠物ID判断是否符合任务要求，不符合返回0，否则更新完成标记,扣马,关闭宠物列表界面,返回非0值
-- 参数：
--  sceneId：场景ID
--  selfId：玩家ID
--  horseTypeID：骑乘的类型ID
--  targetId：NPC的id
--  horseGUID_high：骑乘的guid的高32位数值
--  horseGUID_low：骑乘的guid的低32位数值
--  Reserve1：保留
function x300516_OnCommitPet( sceneId, selfId, MissionId, targetId, horseGUID_high, horseGUID_low, iHorseIndex)

	--如果不是收马任务id
	if (x300516_IsCollectHorse(MissionId) == 0) then
		return 0
	end

	local curMissionId = x300516_GetMD(sceneId, selfId, MD_GUOJIARENWU_RANDMISSIONID)
	--如果当前没有接这个任务
	if (MissionId ~= curMissionId) then
		return 0
	end

	local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )

	local horseTypeID = GetHorseDataID( sceneId, selfId, iHorseIndex )

	if (x300516_IsNeededHorse(MissionId, horseTypeID) == 0) then
		--这不是我要的马
		BeginQuestEvent( sceneId)
		--任务名称
			AddQuestText(sceneId, "#Y"..x300516_g_MissionName)
			AddQuestText( sceneId, x300516_g_strWrongHorse)
		EndQuestEvent()
		DispatchQuestEventList( sceneId, selfId, targetId)
		return 0
	end

	local bIsGood = 1
	local kindtype = mod(horseTypeID, 10)
	if (kindtype == 1) then
		bIsGood = 0
	end

	SetQuestByIndex( sceneId, selfId, misIndex, x300516_g_IsGoodHorse, bIsGood)
	--选择了正确的马
	--保存马的ID
	SetQuestByIndex( sceneId, selfId, misIndex, x300516_g_CommitedHorseID_HIGH, horseGUID_high)
	SetQuestByIndex( sceneId, selfId, misIndex, x300516_g_CommitedHorseID_LOW, horseGUID_low)
	
	BeginQuestEvent(sceneId);
	--任务名称
	AddQuestText(sceneId, "#Y"..x300516_g_MissionName)
	local str
	if(bIsGood == 0) then
		str = x300516_g_strNormalHorse
	else
		str = x300516_g_strGoodHorse
	end
	AddQuestText( sceneId, str)

	local curlevel = GetLevel(sceneId, selfId)
	local exp = x300516_GetExpAward ( sceneId, selfId, curlevel );
	local money,shengw = x300516_GetMoneyAward ( sceneId, selfId, curlevel );
	if bIsGood == 1 then
		exp = exp * 2
		money = money * 2
		shengw = shengw * 2
	end
	if(exp > 0) then
		AddQuestExpBonus(sceneId, exp)
	end
	if(money > 0) then
		AddQuestMoneyBonus2(sceneId, money)
	end
	if(shengw > 0) then
		AddQuestMoneyBonus5(sceneId, shengw)
	end
	EndQuestEvent();

	DispatchQuestContinueInfoNM( sceneId, selfId, targetId, x300516_g_ScriptId, MissionId )
	return 1
end

--function x300516_ProcQuestAccept( sceneId, selfId, targetId, MissionId )
function x300516_HorseSubmit( sceneId, selfId, MissionId )
	local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId)
	--取出马的ID
	local horseGUID_high = GetQuestParam( sceneId, selfId, misIndex, x300516_g_CommitedHorseID_HIGH)
	local horseGUID_low = GetQuestParam( sceneId, selfId, misIndex, x300516_g_CommitedHorseID_LOW)
	-- 收马
	local ret = FreeHorse( sceneId, selfId, horseGUID_high, horseGUID_low)
	if (ret <= 0) then
		local strErr
		if (ret == 0) then
			strErr = "骑乘已锁定，不能交付"
		elseif (ret == -2) then
			strErr = "骑乘正在出战状态，不能交付"
		else
			strErr = "您所选择的骑乘并不存在"
		end
		Msg2Player(sceneId, selfId, strErr, 8, 3)	
		Msg2Player(sceneId, selfId, strErr, 8, 2)
		return 0, 0
	end

	local bGoodHorse = GetQuestParam( sceneId, selfId, misIndex, x300516_g_IsGoodHorse)
	local awardrate
	if(bGoodHorse == 1) then
		awardrate =  2
	else
		awardrate = 1
	end

	--完成任务
--	CallScriptFunction (300501, "MissionSubmited", sceneId, selfId, targetId, MissionId )

	-- 关闭客户端宠物列表窗口
	BeginUICommand( sceneId)
		DispatchUICommand( sceneId, selfId, 102)
	EndUICommand( sceneId)

	-- 设置任务完成标记
	--SetQuestByIndex( sceneId, selfId, misIndex, x300516_g_MissionFinished, 1)
	return 1, awardrate
end

--经验奖励
function x300516_GetExpAward(sceneId, selfId, startlevel)

	x300516_CheckDayChanged(sceneId, selfId)
	local circle = x300516_GetMD(sceneId, selfId, MD_GUOJIARENWU_CIRCLE)
	local highcircle = x300516_GetMD(sceneId, selfId, MD_GUOJIARENWU_HIGH)
	
	circle = circle + 1
	if (circle > x300516_OneRoundCount) then
		circle = 1
	end

	highcircle = highcircle + 1

	local exp_rate
	if GetLevel(sceneId, selfId) >= 60 then
		exp_rate = 3650
	else
		exp_rate = 2800
	end

	local BonusExp = startlevel * exp_rate * (circle * 2 - 1) / 200
	if (highcircle <= x300516_HighBonusCircleCount) then
		BonusExp = BonusExp * 5
	end
    -- 环数减半，所以经验翻倍
    BonusExp = BonusExp * 2
	return BonusExp;

end

--金钱奖励
function x300516_GetMoneyAward(sceneId, selfId, startlevel)

	x300516_CheckDayChanged(sceneId, selfId)
	local circle = x300516_GetMD(sceneId, selfId, MD_GUOJIARENWU_CIRCLE)
	local highcircle = x300516_GetMD(sceneId, selfId, MD_GUOJIARENWU_HIGH)

	circle = circle + 1
	if (circle > x300516_OneRoundCount) then
		circle = 1
	end

	highcircle = highcircle + 1

	local BonusMoney = startlevel
	local shengw = 5
	if (highcircle <= x300516_HighBonusCircleCount) then
		BonusMoney = BonusMoney * 5
		shengw = 25
	end
	return BonusMoney,shengw;
end

function x300516_SetMD(sceneId, selfId, MDNAME, value)
	SetQuestData(sceneId, selfId, MDNAME[1], MDNAME[2], MDNAME[3], value);
end

function x300516_GetMD(sceneId, selfId, MDNAME)

	return GetQuestData(sceneId, selfId, MDNAME[1], MDNAME[2], MDNAME[3])
end


--检查日期有没有变化，并重置高奖次数，并保存新的日期
function x300516_CheckDayChanged(sceneId, selfId)
	local lastDay = x300516_GetMD(sceneId, selfId, MD_GUOJIARENWU_LASTDAY)
	local today = GetDayOfYear()
	if lastDay ~= today then	--日期变化
		x300516_SetMD(sceneId, selfId, MD_GUOJIARENWU_LASTDAY, today)	
		x300516_SetMD(sceneId, selfId, MD_GUOJIARENWU_HIGH, 0)
	end
end

function x300516_IsNeededHorse(MissionId, horseId)

	if x300516_IsCollectHorse(MissionId) == 0 then
		return 0
	end

	local kindtype = mod(horseId, 10)
	if (MissionId < x300516_g_CollectHorse_Young) then
		if (kindtype >= 5) then
			return 0
		end
		local group = floor(horseId / 100)
		if (group ~= MissionId - x300516_g_CollectHorse_Mission_ID + 2 ) then
			return 0
		end
	else
		if (kindtype > 5) then
			return 0
		end
		local group = floor(horseId / 10)
		if (group > 5) then
			return 0
		end
	end

	return 1
end

--是否是收马任务
function x300516_IsCollectHorse(MissionId)
	if MissionId >= x300516_g_CollectHorse_Mission_ID and MissionId <= x300516_g_CollectHorse_Mission_ID_End then
		return 1
	else
		return 0
	end
end





















