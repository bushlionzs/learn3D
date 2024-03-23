
x310182_g_scriptId = 310182
x310182_g_GameId = 1019
x310182_g_LimitLevel = 20
x310182_g_MaxCount = 20
x310182_g_NextLimitLevel = 40

x310182_g_GameID_Right	= 971
x310182_g_GameID_Error	= 972

function x310182_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	if GetGameOpenById(x310182_g_GameId) ~= 1 then
		return
	end
	
    AddQuestNumText(sceneId,x310182_g_scriptId,"我要参加乌龙词典海选！",3,x310182_g_scriptId);
        
end

function x310182_CheckValid( sceneId,selfId,npcId)
	if GetGameOpenById(x310182_g_GameId) ~= 1 then
		--给出相关提示
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"乌龙词典活动已经关闭！")				
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,npcId)
		return -1
	end

	local level = GetLevel(sceneId,selfId)
	if level<x310182_g_LimitLevel then
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"\t只有20级以上的玩家才能参加乌龙辞典海选赛。")				
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,npcId)
		return -2
	end
	local minute =  GetMinOfDay()
		
	if GetWeek() ~= 0 or minute> 840 then
		
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"\t很遗憾，乌龙辞典王国海选赛在下午14：00已经结束了！")				
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,npcId)
		return -3
	end
	if GetWeek() ~= 0 or minute <780 then
		
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"\t别心急，乌龙辞典海选赛在下午13：00才正式开始！")				
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,npcId)
		return -3
	end
		
	return 1

end

function x310182_AddAnswerOption( sceneId,strAnswer1,strAnswer2,strAnswer3,strAnswer4)
	--随机添加选项
	local answer = { {strAnswer1,12001},{strAnswer2,12002},{strAnswer3,12003},{strAnswer4,12004} }
	local index = {1,2,3,4}
	for i=1, 4 do
		local r = random(1, getn(index))
		AddQuestNumText(sceneId,x310182_g_scriptId,answer[index[r]][1],3,answer[index[r]][2] )

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
end

function x310182_AddAward(sceneId ,selfId)
	local nExpBonus = GetLevel(sceneId ,selfId)*800
	AddExp(sceneId, selfId, nExpBonus);
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, "#o获得#R经验"..nExpBonus.."点#o的奖励");
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
  		Msg2Player(sceneId,selfId,"#o获得#R经验"..nExpBonus.."点#o的奖励",4,2)
end


function x310182_ProcEventEntry( sceneId ,selfId, npcId,idScript,idExt )
	if x310182_CheckValid( sceneId,selfId,npcId) < 0 then
		return
	end

	local step = GetQuestData(sceneId,selfId,MD_WULONG_STEP[1], MD_WULONG_STEP[2], MD_WULONG_STEP[3])

	if idExt == x310182_g_scriptId then 

		local curDay = GetDayOfYear() 
		local nDate   = GetQuestData(sceneId,selfId,MD_WULONG_DATE[1], MD_WULONG_DATE[2], MD_WULONG_DATE[3] )
	
		if curDay ~= nDate then
			SetQuestData(sceneId,selfId,MD_WULONG_DATE[1], MD_WULONG_DATE[2], MD_WULONG_DATE[3],curDay )
			SetQuestData(sceneId,selfId,MD_WULONG_STEP[1], MD_WULONG_STEP[2], MD_WULONG_STEP[3],1 )
			SetQuestData(sceneId,selfId,MD_WULONG_COUNT[1], MD_WULONG_COUNT[2], MD_WULONG_COUNT[3],1 )
			SetQuestData(sceneId,selfId,MD_WULONG_RIGHT_COUNT[1], MD_WULONG_RIGHT_COUNT[2], MD_WULONG_RIGHT_COUNT[3],0 )
			SetQuestData(sceneId,selfId,MD_WULONG_TIME_BEGIN[1], MD_WULONG_TIME_BEGIN[2], MD_WULONG_TIME_BEGIN[3],0 )
			SetQuestData(sceneId,selfId,MD_WULONG_LAST_QUESTION[1], MD_WULONG_LAST_QUESTION[2], MD_WULONG_LAST_QUESTION[3],60000 )
		else
			if step ~= 1 then
				return 
			end

			 local curCount = GetQuestData(sceneId,selfId,MD_WULONG_COUNT[1], MD_WULONG_COUNT[2], MD_WULONG_COUNT[3] )
			 if curCount > x310182_g_MaxCount then --答完
				local resultStr ="\t恭喜你成功通过乌龙辞典海选赛！\n\t请在下午#G2点#W准时前往#G大都#W参加扣人心弦的#G乌龙辞典淘汰赛！\n\t#W您可以前往大都的#G（157，215）（96，222）（66，196）#W中任意一处，找到#G大都一号主持人#W开始比赛。"
				if GetLevel(sceneId,selfId) < x310182_g_NextLimitLevel then
					resultStr = format("很可惜，虽然你参加了乌龙辞典海选赛，但是你的等级不足%d级,无法进入下一轮。", x310182_g_NextLimitLevel)
				elseif GetQuestData(sceneId,selfId,MD_WULONG_RIGHT_COUNT[1], MD_WULONG_RIGHT_COUNT[2], MD_WULONG_RIGHT_COUNT[3]) < 10 then
					resultStr = format("很遗憾,你没能通过乌龙辞典海选。\n\t#G（至少需要回答正确%d道题才能进入下一轮）", 10)
				end

				BeginQuestEvent(sceneId)	
				AddQuestText(sceneId, resultStr)						
				EndQuestEvent(sceneId)
				DispatchQuestEventList(sceneId,selfId,npcId)
				return 
			 end

			 --SetQuestData(sceneId,selfId,MD_WULONG_COUNT[1], MD_WULONG_COUNT[2], MD_WULONG_COUNT[3],curCount+1 )
		end
		
		local lastQuest = GetQuestData(sceneId,selfId,MD_WULONG_LAST_QUESTION[1], MD_WULONG_LAST_QUESTION[2], MD_WULONG_LAST_QUESTION[3] ) 
		if lastQuest ~= 60000 then
			local strDesc,strAnswer1,strAnswer2,strAnswer3,strAnswer4,nAnswer = QuestWulong_GetQuestionInfo(0, 1, lastQuest)
			if nAnswer == 0 then
				return
			end

			 local curCount = GetQuestData(sceneId,selfId,MD_WULONG_COUNT[1], MD_WULONG_COUNT[2], MD_WULONG_COUNT[3] )
			 local rightCount = GetQuestData(sceneId,selfId,MD_WULONG_RIGHT_COUNT[1], MD_WULONG_RIGHT_COUNT[2], MD_WULONG_RIGHT_COUNT[3] )

			SetPlayerRuntimeData(sceneId,selfId,RD_QUEST_WULONG_CUR_ANSWER,nAnswer+12000)
			BeginQuestEvent(sceneId)	
					AddQuestText(sceneId,strDesc)
					x310182_AddAnswerOption( sceneId,strAnswer1,strAnswer2,strAnswer3,strAnswer4)						
					--local msg = format("\t（当前第%d题，已答对%d题）",curCount, rightCount)
					AddQuestText(sceneId,format("\t（当前第#G%d#W题，已答对#G%d#W题）",curCount, rightCount) )						
			EndQuestEvent(sceneId)
			DispatchQuestEventList(sceneId,selfId,npcId)	
		else
		local curCount = GetQuestData(sceneId,selfId,MD_WULONG_COUNT[1], MD_WULONG_COUNT[2], MD_WULONG_COUNT[3] )
		local rightCount = GetQuestData(sceneId,selfId,MD_WULONG_RIGHT_COUNT[1], MD_WULONG_RIGHT_COUNT[2], MD_WULONG_RIGHT_COUNT[3] )
			local strDesc,strAnswer1,strAnswer2,strAnswer3,strAnswer4,nAnswer, lastIndex = QuestWulong_GetQuestionInfo(0)
			SetQuestData(sceneId,selfId,MD_WULONG_LAST_QUESTION[1], MD_WULONG_LAST_QUESTION[2], MD_WULONG_LAST_QUESTION[3],lastIndex )
			SetPlayerRuntimeData(sceneId,selfId,RD_QUEST_WULONG_CUR_ANSWER,nAnswer+12000)
			BeginQuestEvent(sceneId)	
					AddQuestText(sceneId,strDesc)
					x310182_AddAnswerOption( sceneId,strAnswer1,strAnswer2,strAnswer3,strAnswer4)							
					--AddQuestText(sceneId,format("当前第#G%d#W题",curCount))
					--AddQuestText(sceneId,format("已答对#G%d#W题",rightCount))
					--AddQuestNumText(sceneId,x310182_g_scriptId,format("（当前第#G%d#W题, 已答对#G%d#W题）",curCount, rightCount),3 )
						AddQuestText(sceneId,format("\t（当前第#G%d#W题，已答对#G%d#W题）",curCount, rightCount) )		
			EndQuestEvent(sceneId)
			DispatchQuestEventList(sceneId,selfId,npcId)
			
		end
		
		
		
		return
	elseif idExt >= 12001 and idExt <= 12004 then
		if step ~= 1 then
				return 
		end

		 local curCount = GetQuestData(sceneId,selfId,MD_WULONG_COUNT[1], MD_WULONG_COUNT[2], MD_WULONG_COUNT[3] )
		 local lastAnswer = GetPlayerRuntimeData(sceneId,selfId,RD_QUEST_WULONG_CUR_ANSWER)
		 SetQuestData(sceneId,selfId,MD_WULONG_LAST_QUESTION[1], MD_WULONG_LAST_QUESTION[2], MD_WULONG_LAST_QUESTION[3],60000 )

		if lastAnswer == idExt then --答对
			local curRightCount = GetQuestData(sceneId,selfId,MD_WULONG_RIGHT_COUNT[1], MD_WULONG_RIGHT_COUNT[2], MD_WULONG_RIGHT_COUNT[3] )
			SetQuestData(sceneId,selfId,MD_WULONG_RIGHT_COUNT[1], MD_WULONG_RIGHT_COUNT[2], MD_WULONG_RIGHT_COUNT[3], curRightCount+1 )

			BeginQuestEvent(sceneId);
			AddQuestText(sceneId, "回答正确，进入下一题！");
			EndQuestEvent(sceneId);
			DispatchQuestTips(sceneId,selfId);
			Msg2Player(sceneId,selfId,"回答正确！",8,2)

			--给奖励
			x310182_AddAward(sceneId ,selfId)

			--添加玩法日志
				GamePlayScriptLog( sceneId, selfId, x310182_g_GameID_Right)
		else
			BeginQuestEvent(sceneId);
			AddQuestText(sceneId, "很遗憾，你答错了");
			EndQuestEvent(sceneId);
			DispatchQuestTips(sceneId,selfId);
			Msg2Player(sceneId,selfId,"很遗憾，你答错了",8,2)
			--添加玩法日志
				GamePlayScriptLog( sceneId, selfId, x310182_g_GameID_Error)
		end

		local curDay = GetDayOfYear() 
		local nDate   = GetQuestData(sceneId,selfId,MD_WULONG_DATE[1], MD_WULONG_DATE[2], MD_WULONG_DATE[3] )

		if curDay ~= nDate then
			SetQuestData(sceneId,selfId,MD_WULONG_DATE[1], MD_WULONG_DATE[2], MD_WULONG_DATE[3],curDay )
			SetQuestData(sceneId,selfId,MD_WULONG_STEP[1], MD_WULONG_STEP[2], MD_WULONG_STEP[3],1 )
			SetQuestData(sceneId,selfId,MD_WULONG_COUNT[1], MD_WULONG_COUNT[2], MD_WULONG_COUNT[3],1 )
			SetQuestData(sceneId,selfId,MD_WULONG_RIGHT_COUNT[1], MD_WULONG_RIGHT_COUNT[2], MD_WULONG_RIGHT_COUNT[3],0 )
			SetQuestData(sceneId,selfId,MD_WULONG_TIME_BEGIN[1], MD_WULONG_TIME_BEGIN[2], MD_WULONG_TIME_BEGIN[3],0 )
			return 
		else	
			if curCount >= x310182_g_MaxCount then  --答完
				local resultStr ="\t恭喜你成功通过乌龙辞典海选赛！\n\t请在下午#G2点#W准时前往#G大都#W参加扣人心弦的#G乌龙辞典淘汰赛！"
				if GetLevel(sceneId,selfId) < x310182_g_NextLimitLevel then
					resultStr = format("\t表现的不错,不过，可惜你的等级不足%d级,无法参加乌龙辞典第二轮淘汰赛。", x310182_g_NextLimitLevel)
				elseif GetQuestData(sceneId,selfId,MD_WULONG_RIGHT_COUNT[1], MD_WULONG_RIGHT_COUNT[2], MD_WULONG_RIGHT_COUNT[3]) < 10 then
					resultStr = format("\t很遗憾,你没能通过乌龙辞典首轮海选，至少需要答对%d题才能参加乌龙辞典第二轮淘汰赛。", 10)
				end

				BeginQuestEvent(sceneId)	
				AddQuestText(sceneId, resultStr)						
				EndQuestEvent(sceneId)
				DispatchQuestEventList(sceneId,selfId,npcId)
				if AddQuestNM( sceneId, selfId, 9335 ) <= 0 then
					--BeginQuestEvent(sceneId);
					--AddQuestText(sceneId, "");
					--EndQuestEvent(sceneId);
					--DispatchQuestTips(sceneId,selfId);
					--Msg2Player(sceneId,selfId,"",8,2)
				else
					SetQuestParam(sceneId, selfId, 9335, 7, 1)
				end
				SetQuestData(sceneId,selfId,MD_WULONG_COUNT[1], MD_WULONG_COUNT[2], MD_WULONG_COUNT[3],curCount+1 )   
				return 
			end
			 SetQuestData(sceneId,selfId,MD_WULONG_COUNT[1], MD_WULONG_COUNT[2], MD_WULONG_COUNT[3],curCount+1 )
		end

		local strDesc,strAnswer1,strAnswer2,strAnswer3,strAnswer4,nAnswer,lastIndex = QuestWulong_GetQuestionInfo(0)
		SetQuestData(sceneId,selfId,MD_WULONG_LAST_QUESTION[1], MD_WULONG_LAST_QUESTION[2], MD_WULONG_LAST_QUESTION[3],lastIndex )
		SetPlayerRuntimeData(sceneId,selfId,RD_QUEST_WULONG_CUR_ANSWER,nAnswer+12000)
		local lastCount = GetQuestData(sceneId,selfId,MD_WULONG_COUNT[1], MD_WULONG_COUNT[2], MD_WULONG_COUNT[3] )
		local rightCount = GetQuestData(sceneId,selfId,MD_WULONG_RIGHT_COUNT[1], MD_WULONG_RIGHT_COUNT[2], MD_WULONG_RIGHT_COUNT[3] )
		BeginQuestEvent(sceneId)	
				AddQuestText(sceneId,strDesc)
				x310182_AddAnswerOption( sceneId,strAnswer1,strAnswer2,strAnswer3,strAnswer4)							
				--AddQuestText(sceneId,format("当前第#G%d#W题",lastCount))
				--AddQuestText(sceneId,format("已答对#G%d#W题",rightCount))
				--AddQuestNumText(sceneId,x310182_g_scriptId,format("（当前第#G%d#W题, 已答对#G%d#W题）",curCount, rightCount),3 )
					AddQuestText(sceneId,format("\t（当前第#G%d#W题，已答对#G%d#W题）",lastCount, rightCount) )		
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,npcId)

		return
	end

end