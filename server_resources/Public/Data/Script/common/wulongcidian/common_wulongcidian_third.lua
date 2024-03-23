
x310184_g_scriptId = 310184
x310184_g_GameId = 1019
x310184_g_LimitLevel = 40
x310184_g_MaxCount = 20

x310184_g_GameID_Right	= 971
x310184_g_GameID_Error	= 972

function x310184_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	
	if GetGameOpenById(x310184_g_GameId) ~= 1 then
		return
	end
	
    AddQuestNumText(sceneId,x310184_g_scriptId,"我要参加乌龙词典终极挑战！",3,x310184_g_scriptId);
        
end

function x310184_IsInPool(sceneId,selfId)
	local name = GetName(sceneId,selfId)

	for i=1, WULONGCIDIAN_STEPIN_COUNT do
		if WULONGCIDIAN_STEPIN_NAME[i] == name then
			return 1
		end
	end
	return -1
end

function x310184_CheckValid( sceneId,selfId,npcId)
	if GetGameOpenById(x310184_g_GameId) ~= 1 then
		--给出相关提示
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"\t乌龙词典活动已经关闭！")				
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,npcId)
		return -1
	end

	local level = GetLevel(sceneId,selfId)
	if level<x310184_g_LimitLevel then
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"\t你似乎没有取得参加乌龙辞典终极挑战的资格。")				
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,npcId)
		return -2
	end
	local minute =  GetMinOfDay()
		if GetWeek() ~= 0 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"\t乌龙辞典终极挑战赛在周日下午16：30才正式开始，别心急。")				
			EndQuestEvent(sceneId)
			DispatchQuestEventList(sceneId,selfId,npcId)
			return -3
		elseif 	minute>17*60 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"\t很遗憾，乌龙辞典终极挑战赛在下午17：00已经结束了。")				
			EndQuestEvent(sceneId)
			DispatchQuestEventList(sceneId,selfId,npcId)
			return -3
		elseif 	minute <16*60+30 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"\t乌龙辞典终极挑战赛在下午16：30才正式开始，别心急。")				
			EndQuestEvent(sceneId)
			DispatchQuestEventList(sceneId,selfId,npcId)
			return -3
		end

	local curDay = GetDayOfYear() 
	local nDate   = GetQuestData(sceneId,selfId,MD_WULONG_DATE[1], MD_WULONG_DATE[2], MD_WULONG_DATE[3] )
	if curDay ~= nDate then
		BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"\t你似乎没有取得参加乌龙辞典终极挑战的资格。")				
			EndQuestEvent(sceneId)
			DispatchQuestEventList(sceneId,selfId,npcId)
		return -5
	end

	if x310184_IsInPool(sceneId,selfId) < 0 then
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"\t你似乎没有取得参加乌龙辞典终极挑战的资格。")				
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,npcId)
		return -4
	end

	return 1

end

function x310184_AddAnswerOption( sceneId,selfId,strAnswer1,strAnswer2,strAnswer3,strAnswer4)
	--随机添加选项
	local answer = { {strAnswer1,12001},{strAnswer2,12002},{strAnswer3,12003},{strAnswer4,12004} }
	local index = {1,2,3,4}
	for i=1, 4 do
		local r = random(1, getn(index))
		AddQuestNumText(sceneId,x310184_g_scriptId,answer[index[r]][1],3,answer[index[r]][2] )

		local tmp = index;
		index = {}
		local curIndex =1;
		for n=1, getn(tmp) do
			if n ~= r then
				index[curIndex] = tmp[n]
				curIndex = curIndex + 1
			end
		end
	end
	local guoguan = 1 - GetQuestData(sceneId,selfId,MD_WULONG_GUOGUANLING[1], MD_WULONG_GUOGUANLING[2], MD_WULONG_GUOGUANLING[3])
	local heibai = 3 - GetQuestData(sceneId,selfId,MD_WULONG_HEIBAILING[1], MD_WULONG_HEIBAILING[2], MD_WULONG_HEIBAILING[3])
	if guoguan < 0 then
		guoguan = 0
	end
	if heibai < 0 then
		heibai = 0
	end
	AddQuestNumText(sceneId,x310184_g_scriptId, format("过关令（一定正确，剩余%d次）",guoguan),13,12005 )
	AddQuestNumText(sceneId,x310184_g_scriptId, format("黑白令（可能正确，剩余%d次）",heibai),13,12006 )
end

function x310184_AddAward(sceneId ,selfId)
	local nExpBonus = GetLevel(sceneId ,selfId)*2400
	AddExp(sceneId, selfId, nExpBonus);
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, "#o获得#R经验"..nExpBonus.."点#o的奖励");
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
  		Msg2Player(sceneId,selfId,"#o获得#R经验"..nExpBonus.."点#o的奖励",4,2)
end

function x310184_PushToPool(sceneId ,selfId, costTime)
	--------------------
	local name = GetName(sceneId ,selfId)
	if WULONGCIDIAN_AWARD_COUNT == 0 then
		WULONGCIDIAN_AWARD_COUNT = 1
		WULONGCIDIAN_AWARD_NAME[WULONGCIDIAN_AWARD_COUNT] = name
		WULONGCIDIAN_AWARD_TIME[WULONGCIDIAN_AWARD_COUNT] = costTime
		return
	end

	for i=1, WULONGCIDIAN_AWARD_COUNT do
		if WULONGCIDIAN_AWARD_NAME[i] == name then
			if WULONGCIDIAN_AWARD_TIME[i] > costTime then
				WULONGCIDIAN_AWARD_TIME[i] = costTime	
			end
			return
		end
	end
	
	if WULONGCIDIAN_AWARD_COUNT == 30 then
		for i=1, WULONGCIDIAN_AWARD_COUNT do
			if WULONGCIDIAN_AWARD_TIME[i] > costTime then
				
				for j=WULONGCIDIAN_AWARD_COUNT, i, -1 do
					if (j-1>0) then
						WULONGCIDIAN_AWARD_NAME[j] = WULONGCIDIAN_AWARD_NAME[j-1]
						WULONGCIDIAN_AWARD_TIME[j] = WULONGCIDIAN_AWARD_TIME[j-1]
					end
				end

				WULONGCIDIAN_AWARD_NAME[i] = name
				WULONGCIDIAN_AWARD_TIME[i] = costTime
				return
			end
		end
	elseif WULONGCIDIAN_AWARD_COUNT < 30 then
		for i=1, WULONGCIDIAN_AWARD_COUNT do
			if WULONGCIDIAN_AWARD_TIME[i] > costTime then
				
				for j=(WULONGCIDIAN_AWARD_COUNT+1), i, -1 do
					if (j-1>0) then
						WULONGCIDIAN_AWARD_NAME[j] = WULONGCIDIAN_AWARD_NAME[j-1]
						WULONGCIDIAN_AWARD_TIME[j] = WULONGCIDIAN_AWARD_TIME[j-1]
					end
				end

				WULONGCIDIAN_AWARD_NAME[i] = name
				WULONGCIDIAN_AWARD_TIME[i] = costTime
				WULONGCIDIAN_AWARD_COUNT = WULONGCIDIAN_AWARD_COUNT + 1
				return
			end
		end
	end
	
	if WULONGCIDIAN_AWARD_COUNT < 30 then
		WULONGCIDIAN_AWARD_COUNT = WULONGCIDIAN_AWARD_COUNT + 1
		WULONGCIDIAN_AWARD_NAME[WULONGCIDIAN_AWARD_COUNT] = name
		WULONGCIDIAN_AWARD_TIME[WULONGCIDIAN_AWARD_COUNT] = costTime
		return
	end

end

function x310184_GetValidTime()

	local n1 = GetCurrentTime()
	local n2 = GetCurrentTime()
	
	local nResult = n2 - n1 
	while nResult > 5 or nResult < 0 do
		n1 = GetCurrentTime()
		n2 = GetCurrentTime()
		nResult = n2 - n1 
	end
	
	return n2
end

function x310184_AfterAnswer(sceneId ,selfId)
	
	if GetQuestData(sceneId,selfId,MD_WULONG_COUNT[1], MD_WULONG_COUNT[2], MD_WULONG_COUNT[3] )>= x310184_g_MaxCount then
		local costTime = x310184_GetValidTime() - GetQuestData(sceneId,selfId,MD_WULONG_TIME_BEGIN[1], MD_WULONG_TIME_BEGIN[2], MD_WULONG_TIME_BEGIN[3])
		x310184_PushToPool(sceneId ,selfId, costTime)
		return 1
	end
	return -1
end


function x310184_ProcEventEntry( sceneId ,selfId, npcId,idScript,idExt )
	if x310184_CheckValid( sceneId,selfId,npcId) < 0 then
		return
	end

	local step = GetQuestData(sceneId,selfId,MD_WULONG_STEP[1], MD_WULONG_STEP[2], MD_WULONG_STEP[3])
	
	if idExt ==  12005 then
		if step ~= 4 then
				return 
		end

		if GetQuestData(sceneId,selfId,MD_WULONG_GUOGUANLING[1], MD_WULONG_GUOGUANLING[2], MD_WULONG_GUOGUANLING[3]) == 1 then
			BeginQuestEvent(sceneId);
			AddQuestText(sceneId, "\t已经用过过关令！");
			EndQuestEvent(sceneId);
			DispatchQuestTips(sceneId,selfId);
			Msg2Player(sceneId,selfId,"已经用过过关令！",8,2)
			return 
		end

		SetQuestData(sceneId,selfId,MD_WULONG_GUOGUANLING[1], MD_WULONG_GUOGUANLING[2], MD_WULONG_GUOGUANLING[3], 1)
		
		 local lastAnswer = GetPlayerRuntimeData(sceneId,selfId,RD_QUEST_WULONG_CUR_ANSWER)
		 local curCount = GetQuestData(sceneId,selfId,MD_WULONG_COUNT[1], MD_WULONG_COUNT[2], MD_WULONG_COUNT[3] )

		local curRightCount = GetQuestData(sceneId,selfId,MD_WULONG_RIGHT_COUNT[1], MD_WULONG_RIGHT_COUNT[2], MD_WULONG_RIGHT_COUNT[3] )
			SetQuestData(sceneId,selfId,MD_WULONG_RIGHT_COUNT[1], MD_WULONG_RIGHT_COUNT[2], MD_WULONG_RIGHT_COUNT[3], curRightCount+1 )

			BeginQuestEvent(sceneId);
			AddQuestText(sceneId, "恭喜你,回答正确！");
			EndQuestEvent(sceneId);
			DispatchQuestTips(sceneId,selfId);
			Msg2Player(sceneId,selfId,"恭喜你,回答正确！",8,2)

			--给奖励
			x310184_AddAward(sceneId ,selfId)

			--添加玩法日志
				GamePlayScriptLog( sceneId, selfId, x310184_g_GameID_Right)
			if x310184_AfterAnswer(sceneId ,selfId) > 0 then
				Msg2Player(sceneId,selfId,"你成功闯过了乌龙辞典终极挑战。",8,2)
				BeginQuestEvent(sceneId)	
				AddQuestText(sceneId,"\t你成功闯过了乌龙辞典终极挑战。")						
				EndQuestEvent(sceneId)
				DispatchQuestEventList(sceneId,selfId,npcId)
				return
			end

			SetQuestData(sceneId,selfId,MD_WULONG_COUNT[1], MD_WULONG_COUNT[2], MD_WULONG_COUNT[3],curCount+1 )

			local strDesc,strAnswer1,strAnswer2,strAnswer3,strAnswer4,nAnswer, nQuest = QuestWulong_GetQuestionInfo(1)
			SetQuestData(sceneId,selfId,MD_WULONG_LAST_QUESTION[1], MD_WULONG_LAST_QUESTION[2], MD_WULONG_LAST_QUESTION[3], nQuest)
			SetPlayerRuntimeData(sceneId,selfId,RD_QUEST_WULONG_CUR_ANSWER,nAnswer+12000)

			BeginQuestEvent(sceneId)	
					AddQuestText(sceneId,strDesc)
					x310184_AddAnswerOption( sceneId,selfId,strAnswer1,strAnswer2,strAnswer3,strAnswer4)							
			EndQuestEvent(sceneId)
			DispatchQuestEventList(sceneId,selfId,npcId)

		return
	end

	if idExt == 12006 then
		if step ~= 4 then
				return 
		end

		local useHeiBai = GetQuestData(sceneId,selfId,MD_WULONG_HEIBAILING[1], MD_WULONG_HEIBAILING[2], MD_WULONG_HEIBAILING[3]) 
		if useHeiBai>= 3 then
			BeginQuestEvent(sceneId);
			AddQuestText(sceneId, "\t已经用过3次黑白令！");
			EndQuestEvent(sceneId);
			DispatchQuestTips(sceneId,selfId);
			Msg2Player(sceneId,selfId,"已经用过3次黑白令！",8,2)
			return 
		end

		SetQuestData(sceneId,selfId,MD_WULONG_HEIBAILING[1], MD_WULONG_HEIBAILING[2], MD_WULONG_HEIBAILING[3], useHeiBai+1)
		local bRight;
		local r = random(1, 100)
		if r>=1 and r<=50 then
			bRight = 1
		else
			bRight = 0
		end

		local lastAnswer = GetPlayerRuntimeData(sceneId,selfId,RD_QUEST_WULONG_CUR_ANSWER)
		 local curCount = GetQuestData(sceneId,selfId,MD_WULONG_COUNT[1], MD_WULONG_COUNT[2], MD_WULONG_COUNT[3] )

		if bRight == 1 then

			local curRightCount = GetQuestData(sceneId,selfId,MD_WULONG_RIGHT_COUNT[1], MD_WULONG_RIGHT_COUNT[2], MD_WULONG_RIGHT_COUNT[3] )
			SetQuestData(sceneId,selfId,MD_WULONG_RIGHT_COUNT[1], MD_WULONG_RIGHT_COUNT[2], MD_WULONG_RIGHT_COUNT[3], curRightCount+1 )

			BeginQuestEvent(sceneId);
			AddQuestText(sceneId, "恭喜你,回答正确！");
			EndQuestEvent(sceneId);
			DispatchQuestTips(sceneId,selfId);
			Msg2Player(sceneId,selfId,"恭喜你,回答正确！",8,2)

			--给奖励
			x310184_AddAward(sceneId ,selfId)

			--添加玩法日志
				GamePlayScriptLog( sceneId, selfId, x310184_g_GameID_Right)
			if x310184_AfterAnswer(sceneId ,selfId) > 0 then
				Msg2Player(sceneId,selfId,"你成功闯过了乌龙辞典终极挑战。",8,2)
				BeginQuestEvent(sceneId)	
				AddQuestText(sceneId,"\t你成功闯过了乌龙辞典终极挑战。")						
				EndQuestEvent(sceneId)
				DispatchQuestEventList(sceneId,selfId,npcId)
				return
			end

			SetQuestData(sceneId,selfId,MD_WULONG_COUNT[1], MD_WULONG_COUNT[2], MD_WULONG_COUNT[3],curCount+1 )

			local strDesc,strAnswer1,strAnswer2,strAnswer3,strAnswer4,nAnswer, nQuest = QuestWulong_GetQuestionInfo(1)
			SetQuestData(sceneId,selfId,MD_WULONG_LAST_QUESTION[1], MD_WULONG_LAST_QUESTION[2], MD_WULONG_LAST_QUESTION[3], nQuest)
			SetPlayerRuntimeData(sceneId,selfId,RD_QUEST_WULONG_CUR_ANSWER,nAnswer+12000)

			BeginQuestEvent(sceneId)	
					AddQuestText(sceneId,strDesc)
					x310184_AddAnswerOption( sceneId,selfId,strAnswer1,strAnswer2,strAnswer3,strAnswer4)							
			EndQuestEvent(sceneId)
			DispatchQuestEventList(sceneId,selfId,npcId)
			return 
		else
			BeginQuestEvent(sceneId);
			AddQuestText(sceneId, "\t回答错误！你的答题总时间增加了15秒。");
			EndQuestEvent(sceneId);
			DispatchQuestTips(sceneId,selfId);
			Msg2Player(sceneId,selfId,"回答错误！你的答题总时间增加了15秒。",8,2)
			--添加玩法日志
			GamePlayScriptLog( sceneId, selfId, x310184_g_GameID_Error)
			local curTime = GetQuestData(sceneId,selfId,MD_WULONG_TIME_BEGIN[1], MD_WULONG_TIME_BEGIN[2], MD_WULONG_TIME_BEGIN[3])
			SetQuestData(sceneId,selfId,MD_WULONG_TIME_BEGIN[1], MD_WULONG_TIME_BEGIN[2], MD_WULONG_TIME_BEGIN[3], curTime-15 )

			if x310184_AfterAnswer(sceneId ,selfId) > 0 then
				Msg2Player(sceneId,selfId,"你成功闯过了乌龙辞典终极挑战。",8,2)
				BeginQuestEvent(sceneId)	
				AddQuestText(sceneId,"\t你成功闯过了乌龙辞典终极挑战。")						
				EndQuestEvent(sceneId)
				DispatchQuestEventList(sceneId,selfId,npcId)
				return
			end
			SetQuestData(sceneId,selfId,MD_WULONG_COUNT[1], MD_WULONG_COUNT[2], MD_WULONG_COUNT[3],curCount+1 )

			local strDesc,strAnswer1,strAnswer2,strAnswer3,strAnswer4,nAnswer, nQuest = QuestWulong_GetQuestionInfo(1)
			SetQuestData(sceneId,selfId,MD_WULONG_LAST_QUESTION[1], MD_WULONG_LAST_QUESTION[2], MD_WULONG_LAST_QUESTION[3], nQuest)
			SetPlayerRuntimeData(sceneId,selfId,RD_QUEST_WULONG_CUR_ANSWER,nAnswer+12000)

			BeginQuestEvent(sceneId)	
					AddQuestText(sceneId,strDesc)
					x310184_AddAnswerOption( sceneId,selfId,strAnswer1,strAnswer2,strAnswer3,strAnswer4)							
			EndQuestEvent(sceneId)
			DispatchQuestEventList(sceneId,selfId,npcId)
			return
		end

		return
	end

	if idExt == x310184_g_scriptId then 

		if step ~= 4 then
			SetQuestData(sceneId,selfId,MD_WULONG_STEP[1], MD_WULONG_STEP[2], MD_WULONG_STEP[3], 4)
			SetQuestData(sceneId,selfId,MD_WULONG_LAST_QUESTION[1], MD_WULONG_LAST_QUESTION[2], MD_WULONG_LAST_QUESTION[3], 60000 )
			SetQuestData(sceneId,selfId,MD_WULONG_COUNT[1], MD_WULONG_COUNT[2], MD_WULONG_COUNT[3], 1 )
			SetQuestData(sceneId,selfId,MD_WULONG_RIGHT_COUNT[1], MD_WULONG_RIGHT_COUNT[2], MD_WULONG_RIGHT_COUNT[3],0 )
			SetQuestData(sceneId,selfId,MD_WULONG_TIME_BEGIN[1], MD_WULONG_TIME_BEGIN[2], MD_WULONG_TIME_BEGIN[3], x310184_GetValidTime())
		else
			local curCount = GetQuestData(sceneId,selfId,MD_WULONG_COUNT[1], MD_WULONG_COUNT[2], MD_WULONG_COUNT[3] )
			 if curCount >= x310184_g_MaxCount then --答完
				x310184_AfterAnswer(sceneId ,selfId)
				BeginQuestEvent(sceneId)	
				AddQuestText(sceneId,"\t你成功的闯过了终极挑战！请等待名次的公布。")						
				EndQuestEvent(sceneId)
				DispatchQuestEventList(sceneId,selfId,npcId)
				return 
			 end

			--SetQuestData(sceneId,selfId,MD_WULONG_COUNT[1], MD_WULONG_COUNT[2], MD_WULONG_COUNT[3],curCount+1 )

			--local lastTime = GetQuestData(sceneId,selfId,MD_WULONG_TIME_BEGIN[1], MD_WULONG_TIME_BEGIN[2], MD_WULONG_TIME_BEGIN[3])
			--SetQuestData(sceneId,selfId,MD_WULONG_TIME_BEGIN[1], MD_WULONG_TIME_BEGIN[2], MD_WULONG_TIME_BEGIN[3], lastTime-15 )
		end
		 
		local lastquest = GetQuestData(sceneId,selfId,MD_WULONG_LAST_QUESTION[1], MD_WULONG_LAST_QUESTION[2], MD_WULONG_LAST_QUESTION[3])
		if lastquest ~= 60000 then
			local strDesc,strAnswer1,strAnswer2,strAnswer3,strAnswer4,nAnswer = QuestWulong_GetQuestionInfo(1, 1, lastquest)
			SetPlayerRuntimeData(sceneId,selfId,RD_QUEST_WULONG_CUR_ANSWER,nAnswer+12000)
			BeginQuestEvent(sceneId)
				AddQuestText(sceneId,strDesc)
				x310184_AddAnswerOption( sceneId,selfId,strAnswer1,strAnswer2,strAnswer3,strAnswer4)							
			EndQuestEvent(sceneId)
			DispatchQuestEventList(sceneId,selfId,npcId)
		else
			local strDesc,strAnswer1,strAnswer2,strAnswer3,strAnswer4,nAnswer, nQuest = QuestWulong_GetQuestionInfo(1)
			SetQuestData(sceneId,selfId,MD_WULONG_LAST_QUESTION[1], MD_WULONG_LAST_QUESTION[2], MD_WULONG_LAST_QUESTION[3], nQuest)
			SetPlayerRuntimeData(sceneId,selfId,RD_QUEST_WULONG_CUR_ANSWER,nAnswer+12000)

			BeginQuestEvent(sceneId)	
					AddQuestText(sceneId,strDesc)
					x310184_AddAnswerOption( sceneId,selfId,strAnswer1,strAnswer2,strAnswer3,strAnswer4)							
			EndQuestEvent(sceneId)
			DispatchQuestEventList(sceneId,selfId,npcId)
		end

		return
	elseif idExt >= 12001 and idExt <= 12004 then
		if step ~= 4 then
				return 
		end

		 local lastAnswer = GetPlayerRuntimeData(sceneId,selfId,RD_QUEST_WULONG_CUR_ANSWER)
		 local curCount = GetQuestData(sceneId,selfId,MD_WULONG_COUNT[1], MD_WULONG_COUNT[2], MD_WULONG_COUNT[3] )
		 SetQuestData(sceneId,selfId,MD_WULONG_LAST_QUESTION[1], MD_WULONG_LAST_QUESTION[2], MD_WULONG_LAST_QUESTION[3], 60000)

		if lastAnswer == idExt then --答对
			local curRightCount = GetQuestData(sceneId,selfId,MD_WULONG_RIGHT_COUNT[1], MD_WULONG_RIGHT_COUNT[2], MD_WULONG_RIGHT_COUNT[3] )
			SetQuestData(sceneId,selfId,MD_WULONG_RIGHT_COUNT[1], MD_WULONG_RIGHT_COUNT[2], MD_WULONG_RIGHT_COUNT[3], curRightCount+1 )

			BeginQuestEvent(sceneId);
			AddQuestText(sceneId, "\t恭喜你,回答正确！");
			EndQuestEvent(sceneId);
			DispatchQuestTips(sceneId,selfId);
			Msg2Player(sceneId,selfId,"恭喜你,回答正确！",8,2)

			--给奖励
			x310184_AddAward(sceneId ,selfId)

			--添加玩法日志
				GamePlayScriptLog( sceneId, selfId, x310184_g_GameID_Right)
			if x310184_AfterAnswer(sceneId ,selfId) > 0 then
				Msg2Player(sceneId,selfId,"你成功闯过了乌龙辞典终极挑战。",8,2)
				BeginQuestEvent(sceneId)	
				AddQuestText(sceneId,"\t你成功闯过了乌龙辞典终极挑战。")						
				EndQuestEvent(sceneId)
				DispatchQuestEventList(sceneId,selfId,npcId)
				return
			end
		else
			BeginQuestEvent(sceneId);
			AddQuestText(sceneId, "\t回答错误！你的答题总时间增加了15秒。");
			EndQuestEvent(sceneId);
			DispatchQuestTips(sceneId,selfId);
			Msg2Player(sceneId,selfId,"回答错误！你的答题总时间增加了15秒。",8,2)
			--添加玩法日志
			GamePlayScriptLog( sceneId, selfId, x310184_g_GameID_Error)
			local curTime = GetQuestData(sceneId,selfId,MD_WULONG_TIME_BEGIN[1], MD_WULONG_TIME_BEGIN[2], MD_WULONG_TIME_BEGIN[3])
			SetQuestData(sceneId,selfId,MD_WULONG_TIME_BEGIN[1], MD_WULONG_TIME_BEGIN[2], MD_WULONG_TIME_BEGIN[3], curTime-15 )

			if x310184_AfterAnswer(sceneId ,selfId) > 0 then
				Msg2Player(sceneId,selfId,"你成功闯过了乌龙辞典终极挑战。",8,2)
				BeginQuestEvent(sceneId)	
				AddQuestText(sceneId,"\t你成功闯过了乌龙辞典终极挑战。")						
				EndQuestEvent(sceneId)
				DispatchQuestEventList(sceneId,selfId,npcId)
				return
			end
		end

		SetQuestData(sceneId,selfId,MD_WULONG_COUNT[1], MD_WULONG_COUNT[2], MD_WULONG_COUNT[3],curCount+1 )

		local strDesc,strAnswer1,strAnswer2,strAnswer3,strAnswer4,nAnswer, nQuest = QuestWulong_GetQuestionInfo(1)
		SetQuestData(sceneId,selfId,MD_WULONG_LAST_QUESTION[1], MD_WULONG_LAST_QUESTION[2], MD_WULONG_LAST_QUESTION[3], nQuest)
		SetPlayerRuntimeData(sceneId,selfId,RD_QUEST_WULONG_CUR_ANSWER,nAnswer+12000)

		BeginQuestEvent(sceneId)	
				AddQuestText(sceneId,strDesc)
				x310184_AddAnswerOption( sceneId,selfId,strAnswer1,strAnswer2,strAnswer3,strAnswer4)							
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,npcId)

		return
	end

end

