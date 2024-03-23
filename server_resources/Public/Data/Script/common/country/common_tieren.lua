x300703_g_scriptId = 300703  --铁人三项
--MD_TIEREN_ACCEPTTIME = MD_TIEREN_ACCEPTTIME--接任务时间
--x300703_g_MD_CommitTime = MD_TIEREN_COMMITTIME--交任务时间
--x300703_g_MD_Abandon = MD_TIEREN_ABANDON	--是否放弃任务
--x300703_g_MD_Circle =     --完成环数
x300703_g_MissionName = "【体】新铁人三项"
x300703_g_MissionId = 7538

x300703_g_SubmitNpc = {{0,139100}, {37,139101}, {37,139102}}

x300703_g_MissionTarget = "  到@npcsp_胡巧夫_139101处参加铁人三项"
x300703_g_MissionTarget1 = "@npc_141544上运动的#G简申#W"

x300703_g_AcceptMessage		= "您接受了任务:%s"
x300703_g_AbandonMessage	= "您放弃了任务:%s"
x300703_g_CompleteMessage	= "您完成了任务:%s"

x300703_g_ContinueMissionInfo = 	" \n接下来的项目跑步这个项目。简单的跑步，却让你的全身得到了锻炼，对强身健体大有益处。\n"
x300703_g_MissionMiddleCompleted = "\t铁人三项是一项集健身、竞争、乐趣于一身的项目。你只要找到在东边@npc_141544不停跑动的#G简申#W，就完成了铁人三项。\n\t\在整个铁人三项过程中，如果你遇到各种不同模样的箱子，开启后可能会获得很多意想不到的效果哦。\n \n#G小提示#W：\n\t如果你在#G非常短的时间#W内完成接下来的任务，你得到#R额外的奖励#W。"
x300703_g_MissionCompleted = "\t恭喜你完成了铁人三项，记得在现实中每天也要花一点时间锻炼身体，能使你更加健康，更能体验到运动的快乐。"

x300703_g_MissionInfo =  "\t在我这里报名，就能去参加新铁人三项的比赛了。\n#W  铁人三项的比赛很简单，只要你能找到一直在大都东郊@npc_141544上走动的简申就可以完成任务。\n#Y活动规则：\n#W1.40级以上玩家才可参加此活动。\n#W2.每天19:30-24:00可领取此活动。\n#W3.每天可接取一次此活动。\n#W4.完成比赛后将会获得丰厚奖励！\n#W5.在整个铁人三项过程中，会遇到不同样子的箱子，您去开启会获得意想不到的效果。"


x300703_g_Missionruse= "\t铁人三项是一项集健身、竞争、乐趣于一身的项目。从@npcsp_胡巧夫_139101处出发，找到@npc_141544上不停跑动的#G简申#W，就完成了铁人三项。\n\t\在整个铁人三项过程中，会遇到不同样子的箱子，您去开启会获得意想不到的效果。"

x300703_g_CompleteInfo		= { day = -1, first = -1, second = -1,third = -1 }

x300703_g_TianfuItems				= {11010100,11010101,11010102}

x300703_g_BackPos = {122,177}

--buff个数
x300703_g_ImpactDataIndex_Size = 211
--不能被驱散的buff，包括被动技能产生的buff和双倍经验的buff
x300703_g_UnDispelImpactDataIndex = {1341,1342,1343,1344,1345,1346,1347,1348,1349,1350,
									 1351,1352,1353,1354,1355,1356,1357,1358,1359,1360,
									 1361,1362,1363,1364,1365,1366,1367,1368,1369,1370,
									 1371,1372,1373,1374,1375,1376,1377,1378,1379,1380,
									 2121,2122,2123,2124,2125,2126,2127,2128,2129,2130,
									 2131,2132,2133,2134,2135,2136,2137,2138,2139,2140,
									 2141,2142,2143,2144,2145,2146,2147,2148,2149,2150,
									 3131,3132,3133,3134,3135,3136,3137,3138,3139,3140,
									 3141,3142,3143,3144,3145,3146,3147,3148,3149,3150,
									 3151,3152,3153,3154,3155,3156,3157,3158,3159,3160,
									 4121,4122,4123,4124,4125,4126,4127,4128,4129,4130,
									 4131,4132,4133,4134,4135,4136,4137,4138,4139,4140,
									 4141,4142,4143,4144,4145,4146,4147,4148,4149,4150,
									 5131,5132,5133,5134,5135,5136,5137,5138,5139,5140,
									 5141,5142,5143,5144,5145,5146,5147,5148,5149,5150,
									 5151,5152,5153,5154,5155,5156,5157,5158,5159,5160,
									 6131,6132,6133,6134,6135,6136,6137,6138,6139,6140,
									 6141,6142,6143,6144,6145,6146,6147,6148,6149,6150,
									 6151,6152,6153,6154,6155,6156,6157,6158,6159,6160,
									 7510,7511,7630,7631,9007,9011,9012,9824,7702,7708,
									 7601,7643, 9013,7646,7647,7648,7649,7650,7709,7710,
									 7711};

x300703_g_StateBuff = {{{7610,7607},{7608,7605}}, {{7616,7613},{7614,7611}}, {{7622,7619},{7620,7617}}, {{7628,7625},{7626,7623}}}
-- 加自行车buff
function x300703_SendStateBuff(sceneId, selfId)
	local country = GetCurCountry( sceneId, selfId )
	local sex = GetSex( sceneId, selfId )
	
	local buff = x300703_g_StateBuff[country+1][1][sex+1]
	if IsHaveSpecificImpact( sceneId, selfId, buff ) <= 0 then
		SendSpecificImpactToUnit(sceneId, selfId, selfId, selfId, buff, 0)
	end
	
	buff = x300703_g_StateBuff[country+1][2][sex+1]
	if IsHaveSpecificImpact( sceneId, selfId, buff ) > 0 then
		CancelSpecificImpact(sceneId, selfId, buff)
	end
end

function x300703_CancelStateBuff(sceneId, selfId)
	local country = GetCurCountry( sceneId, selfId )
	local sex = GetSex( sceneId, selfId )
	
	local buff = x300703_g_StateBuff[country+1][1][sex+1]
	
	if IsHaveSpecificImpact( sceneId, selfId, buff ) > 0 then
		CancelSpecificImpact(sceneId, selfId, buff)
	end
	
	buff = x300703_g_StateBuff[country+1][2][sex+1]
	if IsHaveSpecificImpact( sceneId, selfId, buff ) > 0 then
		CancelSpecificImpact(sceneId, selfId, buff)
	end
end

function x300703_AddLog(sceneId, selfId, sign, MissionId)
	 --最终写日志
	local gameId=0;
	if sign == 1 then
		gameId = 411
	else
		gameId = 412
	end

	GamePlayScriptLog(sceneId, selfId, gameId)
end

function x300703_AwardTitle( sceneId,selfId )
	


	--交任务日期和接任务日期不匹配 
	local min = GetMinOfDay()
	if min < (19*60 + 30 ) or min > (23*60 + 59) then
		return
	end
	

	--给奖励
	local dt = GetDayTime()
	if x300703_g_CompleteInfo.day ~= dt then
		
		x300703_g_CompleteInfo = { day = dt, first = 1, second = -1,third = -1 }
		AwardTitle(sceneId,selfId,18)
		return
		
	else
		
		if x300703_g_CompleteInfo.first == -1 then
			
			x300703_g_CompleteInfo.first = 1
			AwardTitle(sceneId,selfId,18)
			return
		end
		
		if x300703_g_CompleteInfo.second == -1 then
			
			x300703_g_CompleteInfo.second = 1
			AwardTitle(sceneId,selfId,19)
			return
		end
		
		if x300703_g_CompleteInfo.third == -1 then
			
			x300703_g_CompleteInfo.third = 1
			AwardTitle(sceneId,selfId,20)
			return
		end
		
	end
end

function x300703_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

	--if sceneId == 37 then
	--local x, z = GetWorldPos( sceneId, FindMonsterByGUID(sceneId, x300703_g_SubmitNpc[3][2]))
	
	--print ("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx", x, z)
	--end
	
	local npcGuid = GetMonsterGUID(sceneId,targetId)
	if sceneId == x300703_g_SubmitNpc[1][1] and npcGuid == x300703_g_SubmitNpc[1][2] then
		
		if IsHaveQuestNM( sceneId, selfId, x300703_g_MissionId ) <= 0 and QuestCheckAcceptNM( sceneId, selfId, targetId, x300703_g_MissionId ) > 0 then
			local  missionState = GetQuestStateNM(sceneId, selfId, targetId, x300703_g_MissionId)
			AddQuestTextNM(sceneId, selfId, targetId, x300703_g_MissionId, missionState)
		end
	elseif sceneId == x300703_g_SubmitNpc[2][1] and npcGuid == x300703_g_SubmitNpc[2][2] then
	
		if  IsHaveQuestNM( sceneId, selfId, x300703_g_MissionId ) > 0 and QuestCheckAcceptNM( sceneId, selfId, targetId, x300703_g_MissionId ) > 0 then 
			
			local misIndex = GetQuestIndexByID( sceneId, selfId, x300703_g_MissionId )
			if GetQuestParam( sceneId, selfId, misIndex, 6 ) ~= 1 then
				local  missionState = GetQuestStateNM(sceneId, selfId, targetId, x300703_g_MissionId)
				AddQuestTextNM(sceneId, selfId, targetId, x300703_g_MissionId, missionState)
			end
		end
	elseif sceneId == x300703_g_SubmitNpc[3][1] and npcGuid == x300703_g_SubmitNpc[3][2] then
	
		if IsHaveQuestNM( sceneId, selfId, x300703_g_MissionId ) > 0 and IsQuestHaveDoneNM( sceneId, selfId, x300703_g_MissionId ) <= 0 then
			local misIndex = GetQuestIndexByID( sceneId, selfId, x300703_g_MissionId )
			
			if GetQuestParam( sceneId, selfId, misIndex, 6 ) == 1 and GetQuestParam( sceneId, selfId, misIndex, 7 ) ~= 1 then
				SetQuestByIndex( sceneId, selfId, misIndex, 0, 1 )
				SetQuestByIndex( sceneId, selfId, misIndex, 7, 1 )
			end
			 
			local  missionState = GetQuestStateNM(sceneId, selfId, targetId, x300703_g_MissionId)
			AddQuestTextNM(sceneId, selfId, targetId, x300703_g_MissionId, missionState)
		end
	end
    
	return 0
end

--选中任务
function x300703_ProcEventEntry( sceneId, selfId, targetId, MissionId )

	local npcGuid = GetMonsterGUID(sceneId,targetId)
	if sceneId == x300703_g_SubmitNpc[1][1] and npcGuid == x300703_g_SubmitNpc[1][2] then
		
		if IsHaveQuestNM( sceneId, selfId, MissionId ) == 0 then	-- 如果没有这个任务
			x300703_NextDayReset(sceneId, selfId)
			if  IsNpcHaveQuestNM(sceneId, selfId, targetId, MissionId) == 1 then--这里判断npc身上是否有这个任务，否则会出bug
			--不要给出npc身上没有任务的这个提示！
				local ret = QuestCheckAcceptNM( sceneId, selfId, targetId, MissionId )
				if ret > 0 then	-- 如果可以接这个任务
					--AddDispatchQuestInfoNM( sceneId, selfId, targetId, MissionId ) -- 显示接受任务信息
					x300703_DispatchMissionInfo(sceneId, selfId, targetId, MissionId)
				else
					local strText = "未知错误，无法接新的任务"
					if ret == -1 then
						strText = "等级不足，无法接新的任务"
					elseif ret == -2 then
						strText = "等级过高，无法接新的任务"
					elseif ret == -3 then
						strText = "金钱不足，无法接新的任务"
					elseif ret == -4 then
						strText = "您不是本国玩家，无法接新的任务"
					elseif ret == -5 then
						strText = "职业类型不符，无法接新的任务"
					elseif ret == -6 then
						strText = "阵营不符，无法接新的任务"
					elseif ret == -7 then
						strText = "此人无此任务"
					end
					Msg2Player(sceneId,selfId,strText,CHAT_TYPE_SELF,CHAT_PLUMB_SCROLL)
				end
			end
		else --如果有这个任务
			local misIndex = GetQuestIndexByID( sceneId, selfId, x300703_g_MissionId )
			if QuestCheckSubmitNM( sceneId, selfId, targetId, x300703_g_MissionId, misIndex ) > 0 then -- 如果任务可以完成
				--QuestComplateInfoNM( sceneId, selfId, targetId, MissionId ) -- 显示完成信息
			else
				QuestNotComplateInfoNM( sceneId, selfId, targetId, x300703_g_MissionId ) -- 显示任务未完成信息
			end
		end
	elseif sceneId == x300703_g_SubmitNpc[2][1] and npcGuid == x300703_g_SubmitNpc[2][2] then
		
		x300703_DispatchMissionMiddleCompleted(sceneId, selfId, targetId, x300703_g_MissionId)
	elseif sceneId == x300703_g_SubmitNpc[3][1] and npcGuid == x300703_g_SubmitNpc[3][2] then
	
		local misIndex = GetQuestIndexByID( sceneId, selfId, x300703_g_MissionId )
		if GetQuestParam( sceneId, selfId, misIndex, 7 ) == 1 then
			x300703_DispatchMissionCompleted(sceneId, selfId, targetId, x300703_g_MissionId)
		else
			x300703_DispatchMissionContinueInfo(sceneId, selfId, targetId, x300703_g_MissionId)
		end
	end
end

function x300703_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
	
	local npcid = 139102
	if npcGuid == npcid then
		SetPatrolNoBreak(sceneId,npcId,1)
	end
	if IsHaveQuestNM( sceneId, selfId, x300703_g_MissionId) == 0 then	-- 如果没有这个任务
		return
	end
	
end

--杀死怪物
function x300703_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end

-- 变身完成
function x300703_DispatchMissionMiddleCompleted(sceneId, selfId,targetId, MissionId)
	
	BeginQuestEvent( sceneId);
		--任务信息
		AddQuestText(sceneId, "#Y"..x300703_g_MissionName);
		AddQuestText(sceneId, x300703_g_MissionMiddleCompleted)
		
		--任务目标
		AddQuestText( sceneId, "#Y任务目标：")
		AddQuestText( sceneId, "找到@npc_141544附近运动的#G简申#W")
		AddQuestText( sceneId, " ")
		
		--奖励信息

		--获得玩家当前等级
		local playerLevel = GetLevel( sceneId, selfId);
		--获取经验
		local experience1 = playerLevel*100*70
		local experience2 = playerLevel*100*70
		local experience = 0
		if GetLevel(sceneId, selfId) >=40 and GetLevel(sceneId, selfId) < 70 then
			experience = experience1;
		elseif GetLevel(sceneId, selfId) >=70 then
			experience = experience2;
		end
		AddQuestExpBonus( sceneId, experience);
		AddQuestMoneyBonus5(sceneId, 200 )

	EndQuestEvent(sceneId);
	DispatchQuestInfoNM(sceneId, selfId, targetId, x300703_g_scriptId, x300703_g_MissionId)
	
end

-- 最后完成
function x300703_DispatchMissionCompleted(sceneId, selfId,targetId, MissionId)
	
	BeginQuestEvent( sceneId);
		--任务信息
		AddQuestText(sceneId, "#Y"..x300703_g_MissionName);
		AddQuestText(sceneId, x300703_g_MissionCompleted)
		
		--任务目标
		--AddQuestText( sceneId, "#Y任务目标：")
		--AddQuestText( sceneId, x300703_g_MissionTarget)
		--AddQuestText( sceneId, " ")
		
		--奖励信息

		--获得玩家当前等级
		local playerLevel = GetLevel( sceneId, selfId);
		--获取经验
		local experience1 = playerLevel*100*70
		local experience2 = playerLevel*100*70
		local experience = 0
		if GetLevel(sceneId, selfId) >=40 and GetLevel(sceneId, selfId) < 70 then
			experience = experience1;
		elseif GetLevel(sceneId, selfId) >=70 then
			experience = experience2;
		end
		AddQuestExpBonus( sceneId, experience);
		AddQuestMoneyBonus5(sceneId, 200 )

	EndQuestEvent(sceneId);
	DispatchQuestInfoNM(sceneId, selfId, targetId, x300703_g_scriptId, x300703_g_MissionId)
	
end

function x300703_DispatchMissionInfo(sceneId, selfId,targetId, MissionId)
	
	BeginQuestEvent( sceneId);
		--任务信息
		AddQuestText(sceneId, "#Y"..x300703_g_MissionName);
		AddQuestText(sceneId, x300703_g_MissionInfo)
		--任务目标
		AddQuestText( sceneId, "#Y任务目标：")
		AddQuestText( sceneId, x300703_g_MissionTarget)
		AddQuestText( sceneId, " ")

	EndQuestEvent(sceneId);
	DispatchQuestInfoNM(sceneId, selfId, targetId, x300703_g_scriptId, x300703_g_MissionId)
end


function x300703_DispatchMissionContinueInfo(sceneId, selfId, targetId, MissionId)

	BeginQuestEvent( sceneId);
		--任务信息
		AddQuestText(sceneId, "#Y"..x300703_g_MissionName)
		AddQuestText(sceneId, x300703_g_ContinueMissionInfo)
		
		--任务目标
		AddQuestText( sceneId, "#Y任务目标：")
		AddQuestText( sceneId, x300703_g_MissionTarget)
		AddQuestText( sceneId, " ")
	EndQuestEvent(sceneId);

	DispatchQuestContinueInfoNM(sceneId, selfId, targetId, x300703_g_scriptId, MissionId);
end

--接受任务
function x300703_ProcQuestAccept( sceneId, selfId, targetId, MissionId )
	
	if x300703_ProcAcceptCheckTime() < 0 then --没在接任务的时间段
		Msg2Player(sceneId,selfId,"很抱歉，您不在规定时间内参与活动，请在每日的19：30~24：00间来参与活动",CHAT_TYPE_SELF,CHAT_PLUMB_SCROLL)
		Msg2Player(sceneId,selfId,"很抱歉，您不在规定时间内参与活动，请在每日的19：30~24：00间来参与活动",CHAT_TYPE_SELF,CHAT_RIGHTDOWN)
		return 
	end
	

	if IsHaveSpecificImpact( sceneId, selfId, 7702 ) > 0 then
		Msg2Player(sceneId,selfId,"很抱歉，您扛着旗子不能来参与活动",CHAT_TYPE_SELF,CHAT_PLUMB_SCROLL)
		Msg2Player(sceneId,selfId,"很抱歉，您扛着旗子不能来参与活动",CHAT_TYPE_SELF,CHAT_RIGHTDOWN)
		return 
	end
	
	--有童趣不能接
	if IsHaveQuestNM( sceneId, selfId, 8066 ) > 0 or
		IsHaveQuestNM( sceneId, selfId, 8074 ) > 0 or 
		IsHaveQuestNM( sceneId, selfId, 8067 ) > 0 or
		IsHaveQuestNM( sceneId, selfId, 8068 ) > 0 or
		IsHaveQuestNM( sceneId, selfId, 8069 ) > 0 or
		IsHaveQuestNM( sceneId, selfId, 8070 ) > 0 or
		IsHaveQuestNM( sceneId, selfId, 8071 ) > 0 or
		IsHaveQuestNM( sceneId, selfId, 8072 ) > 0 or
		IsHaveQuestNM( sceneId, selfId, 8073 ) > 0 then

		Msg2Player(sceneId,selfId,"很抱歉，您有童趣任务不能来参与活动",CHAT_TYPE_SELF,CHAT_PLUMB_SCROLL)
		Msg2Player(sceneId,selfId,"很抱歉，您有童趣任务不能来参与活动",CHAT_TYPE_SELF,CHAT_RIGHTDOWN)
		return
	end

	if IsBusMember(sceneId, selfId) > 0 then
		Msg2Player(sceneId,selfId,"很抱歉，护送不能来参与活动",CHAT_TYPE_SELF,CHAT_PLUMB_SCROLL)
		Msg2Player(sceneId,selfId,"很抱歉，护送不能来参与活动",CHAT_TYPE_SELF,CHAT_RIGHTDOWN)
		return 
	end
	
	if IsPlayerStateNormal(sceneId,selfId) == 1 then
		if GetChangeSceneState(sceneId, selfId)==2 then
			return
		end
	else
		return
	end
			
	local npcGuid = GetMonsterGUID(sceneId,targetId)
	
	if sceneId == x300703_g_SubmitNpc[1][1] and npcGuid == x300703_g_SubmitNpc[1][2] then
		local rounds = GetQuestData(sceneId, selfId, MD_TIEREN_COMMITTIME[1], MD_TIEREN_COMMITTIME[2], MD_TIEREN_COMMITTIME[3])

		if rounds >= 1 then
			Msg2Player(sceneId,selfId,"很抱歉，您今天已经领取过铁人三项活动，请明日再来。",CHAT_TYPE_SELF,CHAT_PLUMB_SCROLL)
			Msg2Player(sceneId,selfId,"很抱歉，您今天已经领取过铁人三项活动，请明日再来。",CHAT_TYPE_SELF,CHAT_RIGHTDOWN)
			return
		end
		
		--检查前置任务
		local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId, x300703_g_MissionId )
		if FrontMissiontId1 ~= -1 then
			if IsQuestHaveDoneNM( sceneId, selfId, FrontMissiontId1 ) == 0 then
				return 0
			end
		end
		if FrontMissiontId2 ~= -1 then
			if IsQuestHaveDoneNM( sceneId, selfId, FrontMissiontId2 ) == 0 then
				return 0
			end
		end
		if FrontMissiontId3 ~= -1 then
			if IsQuestHaveDoneNM( sceneId, selfId, FrontMissiontId3 ) == 0 then
				return 0
			end
		end

		local ret = QuestCheckAcceptNM( sceneId, selfId, targetId, x300703_g_MissionId ) -- 获取接受任务检查信息
		if ret > 0 then -- 如果可以接这个任务
			ret = AddQuest( sceneId, selfId, x300703_g_MissionId, x300703_g_scriptId, 0, 0, 0, 1) -- 给玩家添加任务
			if ret > 0 then
				local misIndex = GetQuestIndexByID( sceneId, selfId, x300703_g_MissionId )
				SetQuestByIndex( sceneId, selfId, misIndex, 0, 0 )
				SetQuestByIndex( sceneId, selfId, misIndex, 7, 0 )
				
				x300703_SetAcceptTime(sceneId, selfId)
				return 1
			elseif ret == 0 then
				local strText = "添加任务失败"
				Msg2Player(sceneId,selfId, strText,CHAT_TYPE_SELF,CHAT_PLUMB_SCROLL)
			elseif ret == -1 then
				local strText = "背包已满,请整理后再来接任务"
				Msg2Player(sceneId,selfId, strText,CHAT_TYPE_SELF,CHAT_PLUMB_SCROLL)
			elseif ret == -2 then
				local strText = "任务已满，添加任务失败"
				Msg2Player(sceneId,selfId, strText,CHAT_TYPE_SELF,CHAT_PLUMB_SCROLL)
			end
		end
	elseif sceneId == x300703_g_SubmitNpc[2][1] and npcGuid == x300703_g_SubmitNpc[2][2] then
	
		local misIndex = GetQuestIndexByID( sceneId, selfId, x300703_g_MissionId )
		
		if GetQuestParam( sceneId, selfId, misIndex, 6 ) ~= 1 then 
			SetQuestByIndex( sceneId, selfId, misIndex, 6, 1 )
		
			x300703_AddLog(sceneId, selfId, 1, MissionId)

			ReCallHorse( sceneId, selfId )--强制下马
			--x300703_DispelBuff(sceneId, selfId)

			x300703_SendStateBuff(sceneId, selfId)
			
			-- 加隐身buff
			SendSpecificImpactToUnit(sceneId, selfId, selfId, selfId, 7716, 0)
				
			local message = format(x300703_g_AcceptMessage, x300703_g_MissionName)
			Msg2Player(sceneId,selfId, message,CHAT_TYPE_SELF,CHAT_PLUMB_SCROLL)
			Msg2Player(sceneId,selfId, message,CHAT_TYPE_SELF,CHAT_RIGHTDOWN)

			x300703_ProcQuestLogRefresh( sceneId,selfId,x300703_g_MissionId)

			MarkMutexState(sceneId, selfId, 18)
			return 1
		end
	elseif sceneId == x300703_g_SubmitNpc[3][1] and npcGuid == x300703_g_SubmitNpc[3][2] then
		x300703_MissionComplate( sceneId, selfId, targetId, selectId, x300703_g_MissionId )
	end
	return 0
end

--任务放弃
function x300703_ProcQuestAbandon( sceneId, selfId, MissionId )
	local ret = 0
	ret = DelQuestNM( sceneId, selfId, x300703_g_MissionId )
	if ret == 1 then
		--SetImmuneAbsForLater( sceneId, selfId, 0 ) --设置绝对免疫
		x300703_CancelStateBuff(sceneId, selfId)

		x300703_NextDayReset(sceneId, selfId)
		local rounds = GetQuestData(sceneId, selfId, MD_TIEREN_COMMITTIME[1], MD_TIEREN_COMMITTIME[2], MD_TIEREN_COMMITTIME[3])
		SetQuestData(sceneId, selfId, MD_TIEREN_COMMITTIME[1], MD_TIEREN_COMMITTIME[2], MD_TIEREN_COMMITTIME[3], rounds+1)
		local day = GetDayOfYear()
		SetQuestData(sceneId, selfId, MD_TIEREN_ACCEPTTIME_DAY[1], MD_TIEREN_ACCEPTTIME_DAY[2], MD_TIEREN_ACCEPTTIME_DAY[3], day)

		ClearMutexState(sceneId, selfId, 18)

		local message = format(x300703_g_AbandonMessage, x300703_g_MissionName)
		Msg2Player(sceneId,selfId, message,CHAT_TYPE_SELF,CHAT_PLUMB_SCROLL)
		Msg2Player(sceneId,selfId, message,CHAT_TYPE_SELF,CHAT_RIGHTDOWN)
	end
end

--完成任务
--返回1代表成功，0代表交任务失败
function x300703_ProcQuestSubmit( sceneId, selfId, targetId, selectId, MissionId )

	if IsHaveQuestNM( sceneId, selfId, MissionId ) == 0 then	-- 如果没这个任务直接退出
		return 0
	end

	local npcGuid = GetMonsterGUID(sceneId,targetId)local npcGuid = GetMonsterGUID(sceneId,targetId)
	if sceneId == x300703_g_SubmitNpc[3][1] and npcGuid == x300703_g_SubmitNpc[3][2] then
	
		--x300703_MissionComplate( sceneId, selfId, targetId, selectId, x300703_g_MissionId )
		return 1
	end
	return 0
end

function x300703_AddTianfuItem( sceneId, selfId)
	local level = GetLevel( sceneId, selfId)
	if level >= 80 then
		if random( 1, 100) <= 22 then
			local nIndex = random(1,3)
			BeginAddItem( sceneId)
	        AddItem( sceneId, x300703_g_TianfuItems[nIndex], 1)
	        if EndAddItem( sceneId, selfId) <= 0 then
	            Msg2Player( sceneId, selfId, "由于你的背包已满，无法获得天赋道具奖励。", 8, 2)
	        else
	            AddItemListToPlayer( sceneId, selfId)
	        end
		end
	end
end
--任务完成
function x300703_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	--x300703_SetCommitTime(sceneId, selfId, MissionId)
	local ret = DelQuestNM( sceneId, selfId, MissionId )
	if ret == 1 then -- 如果成功完成
		x300703_AddLog(sceneId, selfId, 0, MissionId)
		--SetImmuneAbsForLater( sceneId, selfId, 0 ) --设置绝对免疫
		--这里给的奖励未定
		local level = GetLevel(sceneId, selfId)
		local award1 = floor(100*level*70)
		local award2 = floor(100*level*70)
		local award = 0
		if GetLevel(sceneId, selfId) >=40 and GetLevel(sceneId, selfId) < 70 then
			award = award1;
		elseif GetLevel(sceneId, selfId) >=70 then
			award = award2;
		end
		ClearMutexState(sceneId, selfId, 18)

		local MissionName = GetQuestNameNM( sceneId, selfId, MissionId )
		local message = format(x300703_g_CompleteMessage, MissionName)
		Msg2Player(sceneId,selfId,message,CHAT_TYPE_SELF,CHAT_PLUMB_SCROLL)
		Msg2Player(sceneId,selfId,message,CHAT_TYPE_SELF,CHAT_RIGHTDOWN)

		local level = GetLevel(sceneId, selfId)
		if IsHaveSpecificImpact( sceneId, selfId, 7716 ) > 0 then
			award = award + level*7000
			AddExp(sceneId, selfId, award)
			
			message = format("#Y获得#R经验%d#Y的奖励", award/2)
			message1 = format("#Y您非常迅速的完成了【体】铁人三项，额外奖励#R经验%d点", award/2)
			Msg2Player(sceneId,selfId,message,CHAT_TYPE_SELF,CHAT_PLUMB_SCROLL)
			Msg2Player(sceneId,selfId,message,CHAT_TYPE_SYSTEM,CHAT_RIGHTDOWN)
			Msg2Player(sceneId,selfId,message1,CHAT_TYPE_SELF,CHAT_PLUMB_SCROLL)
			Msg2Player(sceneId,selfId,message1,CHAT_TYPE_SYSTEM,CHAT_RIGHTDOWN)
		else
			AddExp(sceneId, selfId, award)
			
			message = format("#Y获得#R经验%d#Y的奖励", award)
			Msg2Player(sceneId,selfId,message,CHAT_TYPE_SELF,CHAT_PLUMB_SCROLL)
			Msg2Player(sceneId,selfId,message,CHAT_TYPE_SYSTEM,CHAT_RIGHTDOWN)
		end
		
		local nShengWang = GetShengWang( sceneId, selfId )
		nShengWang = nShengWang + 200
		SetShengWang( sceneId, selfId, nShengWang )
		message = format("获得声望%d的奖励。", 200)
		Msg2Player(sceneId,selfId,message,CHAT_TYPE_SELF,CHAT_PLUMB_SCROLL)
		Msg2Player(sceneId,selfId,message,CHAT_TYPE_SYSTEM,CHAT_RIGHTDOWN)
		CallScriptFunction( 256224, "Finishtiesan", sceneId, selfId)	
		x300703_NextDayReset(sceneId, selfId)
		local rounds = GetQuestData(sceneId, selfId, MD_TIEREN_COMMITTIME[1], MD_TIEREN_COMMITTIME[2], MD_TIEREN_COMMITTIME[3])
		SetQuestData(sceneId, selfId, MD_TIEREN_COMMITTIME[1], MD_TIEREN_COMMITTIME[2], MD_TIEREN_COMMITTIME[3], rounds+1)
		local day = GetDayOfYear()
		SetQuestData(sceneId, selfId, MD_TIEREN_ACCEPTTIME_DAY[1], MD_TIEREN_ACCEPTTIME_DAY[2], MD_TIEREN_ACCEPTTIME_DAY[3], day)

        -- 添加一枚大都嘉年华娱乐币
        BeginAddItem( sceneId)
        AddItem( sceneId, 11990117, 10)
        if EndAddItem( sceneId, selfId) <= 0 then
            Msg2Player( sceneId, selfId, "你完成了【体】大都嘉年华。由于你的背包已满，无法获得#{_ITEM11990117}奖励。", CHAT_TYPE_SELF, CHAT_RIGHTDOWN)
        else
            AddItemListToPlayer( sceneId, selfId)
        end
        
        x300703_AddTianfuItem( sceneId, selfId)
	
		--添加排名
		local hour,minute,second = GetHourMinSec()
		local val = 0;
		val = val + (hour-19)*3600
		val = val + (minute-30)*60
		val = val + second
		SendToplistKeyValue2GL(sceneId,selfId,TIEREN_TOPLIST,val)
		
		--奖励称号
		x300703_AwardTitle(sceneId,selfId)

		local j = random(1,5)
		local buff 	=	9011
		local buff1 =	9013
		local buff2 =	9012
		if j ==1 then
			BeginAddItem( sceneId )
			if IsHaveSpecificImpact( sceneId, selfId, buff) == 1 or IsHaveSpecificImpact( sceneId, selfId, buff1) == 1  or IsHaveSpecificImpact( sceneId, selfId, buff2) == 1 then
				AddItem( sceneId, 12030107, 1 )
			else
				AddBindItem( sceneId, 12030107, 1 )
			end
			local result = EndAddItem( sceneId, selfId )
			if result > 0 then
				AddItemListToPlayer(sceneId,selfId)
				local Country = CallScriptFunction(888888, "GetCountryName", sceneId, selfId )
				--local selfName = GetName(sceneId, selfId)
				--local msg = format("#G恭喜#Y%s#G在铁人三项活动中获得#R神龙藏宝图#G一张。", selfName)
				--LuaAllScenceM2Wrold(sceneId, msg, 1, 1)
			else
				Msg2Player(sceneId,selfId,"很抱歉，背包已满，无法得到物品！",CHAT_TYPE_SELF,CHAT_PLUMB_SCROLL)
			end
		end

		x300703_CancelStateBuff(sceneId, selfId)
		
		return 1 -- 返回成功
		
	else -- 如果未成功完成
		BeginQuestEvent(sceneId)
		local strText = "未知错误，无法完成任务"
		if ret == -2 then
			strText = "请选择奖励物品"
		elseif ret == -3 then
			strText = "背包已满,请整理后再来交任务"
		elseif ret == -4 then
			strText = "扣除任务物品失败"
		end
		Msg2Player(sceneId,selfId,strText,CHAT_TYPE_SELF,CHAT_PLUMB_SCROLL)
		return 0
	end
	return 0
end

function x300703_ProcAcceptCheckTime(  )

	local minute = GetMinOfDay()
	if (minute >= 19*60+30 and minute <24*60) then
		return 1
	end

	return -1
end

function x300703_SetAcceptTime(sceneId, selfId)
	
	local day = GetDayOfYear()
	local minute = GetMinOfDay()
	
	SetQuestData(sceneId, selfId, MD_TIEREN_ACCEPTTIME_DAY[1], MD_TIEREN_ACCEPTTIME_DAY[2], MD_TIEREN_ACCEPTTIME_DAY[3], day)
	SetQuestData(sceneId, selfId, MD_TIEREN_ACCEPTTIME_MINUTE[1], MD_TIEREN_ACCEPTTIME_MINUTE[2], MD_TIEREN_ACCEPTTIME_MINUTE[3], minute)
end

function x300703_TieSanOnDie(sceneId, selfId)
	
	local lastDay = GetQuestData(sceneId, selfId, MD_TIEREN_ACCEPTTIME_DAY[1], MD_TIEREN_ACCEPTTIME_DAY[2], MD_TIEREN_ACCEPTTIME_DAY[3])
	local lastMin = GetQuestData(sceneId, selfId, MD_TIEREN_ACCEPTTIME_MINUTE[1], MD_TIEREN_ACCEPTTIME_MINUTE[2], MD_TIEREN_ACCEPTTIME_MINUTE[3])

	local nowTime = GetDayOfYear()*1440 + GetMinOfDay()
	local lastTime = lastDay*1440 + lastMin

	if IsHaveQuestNM( sceneId, selfId, x300703_g_MissionId ) > 0 then
		if nowTime - lastTime < 120 then
			--SetImmuneAbsForLater( sceneId, selfId, 1 ) --设置绝对免疫
			
			local misIndex = GetQuestIndexByID( sceneId, selfId, x300703_g_MissionId )
			if GetQuestParam( sceneId, selfId, misIndex, 6 ) == 1 then 
			
				ReCallHorse( sceneId, selfId )--强制下马
				--x300703_DispelBuff(sceneId, selfId)
	
				x300703_SendStateBuff(sceneId, selfId)
	
				MarkMutexState(sceneId, selfId, 18) 
			end
			return 
		end

		--SetImmuneAbsForLater( sceneId, selfId, 0 ) --设置绝对免疫
		x300703_CancelStateBuff(sceneId, selfId)
		
		DelQuestNM( sceneId, selfId, x300703_g_MissionId )
		ClearMutexState(sceneId, selfId, 18)
		Msg2Player(sceneId,selfId,"您的铁人三项任务已失败，请重新领取！",CHAT_TYPE_SELF,CHAT_PLUMB_SCROLL)
		Msg2Player(sceneId,selfId,"您的铁人三项任务已失败，请重新领取！",CHAT_TYPE_SELF,CHAT_RIGHTDOWN)
		x300703_NextDayReset(sceneId, selfId)
		local rounds = GetQuestData(sceneId, selfId, MD_TIEREN_COMMITTIME[1], MD_TIEREN_COMMITTIME[2], MD_TIEREN_COMMITTIME[3])
		SetQuestData(sceneId, selfId, MD_TIEREN_COMMITTIME[1], MD_TIEREN_COMMITTIME[2], MD_TIEREN_COMMITTIME[3], rounds+1)
		local day = GetDayOfYear()
		SetQuestData(sceneId, selfId, MD_TIEREN_ACCEPTTIME_DAY[1], MD_TIEREN_ACCEPTTIME_DAY[2], MD_TIEREN_ACCEPTTIME_DAY[3], day)
		
		if sceneId ~= 0 then
			NewWorld(sceneId, selfId, 0, x300703_g_BackPos[1], x300703_g_BackPos[2], x300703_g_scriptId)
		else
			SetPos(sceneId,selfId, x300703_g_BackPos[1], x300703_g_BackPos[2])
		end
	end

end

function x300703_NextDayReset(sceneId, selfId)
	
	local lastDay = GetQuestData(sceneId, selfId, MD_TIEREN_ACCEPTTIME_DAY[1], MD_TIEREN_ACCEPTTIME_DAY[2], MD_TIEREN_ACCEPTTIME_DAY[3])

	local today = GetDayOfYear()
	if today ~= lastDay then 
		SetQuestData(sceneId, selfId, MD_TIEREN_ACCEPTTIME_DAY[1], MD_TIEREN_ACCEPTTIME_DAY[2], MD_TIEREN_ACCEPTTIME_DAY[3], 0)
		SetQuestData(sceneId, selfId, MD_TIEREN_ACCEPTTIME_MINUTE[1], MD_TIEREN_ACCEPTTIME_MINUTE[2], MD_TIEREN_ACCEPTTIME_MINUTE[3], 0)
		SetQuestData(sceneId, selfId, MD_TIEREN_COMMITTIME[1], MD_TIEREN_COMMITTIME[2], MD_TIEREN_COMMITTIME[3], 0)
	end
end

function x300703_CanDispel(dataIndex)
	for j=0, x300703_g_ImpactDataIndex_Size-1 do
		if dataIndex == x300703_g_UnDispelImpactDataIndex[j+1] then
			return -1
		end
	end
	return 1
end

function x300703_DispelBuff(sceneId, selfId)
	local count = GetImpactListCount( sceneId, selfId )
	for i=0, count-1 do
		local dataIndex = GetImpactDataIndex( sceneId, selfId, i )
		if x300703_CanDispel(dataIndex) > 0 then
			DispelSpecificImpact( sceneId, selfId, dataIndex )
		end
	end
end

function x300703_ProcQuestLogRefresh( sceneId,selfId,missionId)
	
	local target = x300703_g_MissionTarget
	local target1 = x300703_g_MissionTarget1
	local misIndex = GetQuestIndexByID( sceneId, selfId, x300703_g_MissionId )
	if GetQuestParam( sceneId, selfId, misIndex, 6 ) == 1 then
		target = "  找到东方@npc_141544附近运动的#G简申#W"
	end
	
    BeginQuestEvent(sceneId)
        AddQuestLogCustomText( sceneId,
                                "",                    -- 标题
                                x300703_g_MissionName,                 -- 任务名字
                                target,               --任务目标
                                target1,                         --任务NPC
                                x300703_g_Missionruse,                   --任务攻略
                                "\t我们大元自古尚武，重视对自身体能的训练。在伟大的成吉思汗时期，就曾经制定过“赛达木”大会，激励众人重视体育锻炼，我们现在也有类似的活动。俗称“铁人三项”。在我这里报名，就能去大都东郊参加比赛了。\n#W  铁人三项的比赛很简单，出发后找到目标就算完成。此活动娱乐之余拉近了彼此之间的距离，锻炼了彼此的协作能力，还将获得丰厚奖励，您还在等什么，赶紧行动起来吧！",                --任务描述
                                ""        --任务小提示
                                )

	EndQuestEvent()
	DispatchQuestLogUpdate(sceneId, selfId, x300703_g_MissionId);
end

