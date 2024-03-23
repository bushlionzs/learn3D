x300101_g_ScriptId 		= 300101
x300101_g_MissionKind 	= 	1                       --任务类型
x300101_g_MissionId		= 9251			--任务ID
x300101_g_MissionName	= "【个人】仕官晋级"

--出题相关
x300101_g_MaxCount		= 15			--不能超过31

x300101_g_GameId		= 1038			--玩法ID
x300101_g_LimitLevel	= 50			--最低级别

function x300101_GetTurnCount( sceneId, selfId, daycount )
	local t = 1
	local d = daycount
	while d > 3 do
		t = t + 1
		d = d - 3
	end
	
	return t, d
end

function x300101_GetBonusExp( sceneId, selfId, Right, daycount )
	local t, d = x300101_GetTurnCount( sceneId, selfId, daycount )
	
	local level = GetLevel(sceneId,selfId)
	local bonusExp = 0
	local bonusMoney = 0
	if t == 1 then
		if Right > 0 then

			bonusExp = level*700

		else
			bonusExp = level*350
		end
		bonusMoney = 5000
	elseif t == 2 then
		if Right > 0 then
			bonusExp = level*1400
		else
			bonusExp = level*700
		end
		bonusMoney = 10000
	elseif t == 3 then
		if Right > 0 then
			bonusExp = level*2800
		else
			bonusExp = level*1400
		end
		bonusMoney = 20000
	elseif t == 4 then
		if Right > 0 then
			bonusExp = level*5600
		else
			bonusExp = level*2800
		end
		bonusMoney = 40000
	elseif t == 5 then
		if Right > 0 then
			bonusExp = level*8400
		else
			bonusExp = level*4200
		end
		bonusMoney = 60000
	end

	if level >= 80 and level <90 then
		bonusExp = bonusExp*2
	elseif level >= 90 and level <160 then
		bonusExp = bonusExp*2.6
	end
	
	return t, d, bonusExp, bonusMoney
end

----------------------------------------------------------------------------------------------
--给奖励，答对的情况下，才会触发
----------------------------------------------------------------------------------------------
function x300101_GiveBonus( sceneId,selfId, Right, daycount )

	--活动未开启
	if GetGameOpenById(x300101_g_GameId) ~= 1 then
		return
	end
	
	local t, d, bonusExp, bonusMoney = x300101_GetBonusExp( sceneId, selfId, Right, daycount )
	--给经验
	AddExp(sceneId,selfId,bonusExp)
	
	local msg = format("#cffcf00您获得了#G%d点经验#cffcf00的奖励",bonusExp)
	Msg2Player(sceneId,selfId,msg,8,3)
	Msg2Player(sceneId,selfId,msg,8,2)
end

----------------------------------------------------------------------------------------------
--枚举
----------------------------------------------------------------------------------------------
function x300101_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

	--检查玩家等级
	local level = GetLevel(sceneId,selfId)
	if level<x300101_g_LimitLevel then
		return
	end
	
	local bHaveMission = IsHaveQuestNM(sceneId, selfId, x300101_g_MissionId)
	if bHaveMission <= 0 then
		local state = GetQuestStateNM(sceneId,selfId,targetId,x300101_g_MissionId)
		AddQuestNumText(sceneId,x300101_g_MissionId,x300101_g_MissionName,state,-1)
	end
end

----------------------------------------------------------------------------------------------
--添加灯谜答案选项
----------------------------------------------------------------------------------------------
function x300101_AddDengmiAnswerOption( sceneId,strAnswer1,strAnswer2,strAnswer3,strAnswer4)

	--随机添加选项
	local arr_answer = { {strAnswer1,11001},{strAnswer2,11002},{strAnswer3,11003},{strAnswer4,11004} }
	for j = 1, 2 do
		local n = random(1, 4)
		local m =  random(1, 4)
		if n ~= m then
			local t = arr_answer[n]
			arr_answer[n] = arr_answer[m]
			arr_answer[m] = t
		end
	end
	
	for i=1,4 do
		AddQuestNumText(sceneId,x300101_g_ScriptId,arr_answer[i][1],3,arr_answer[i][2] )
	end
end

-- 显示谜语
function x300101_ShowQuiz(sceneId, selfId, npcId)

	--活动关闭
	if GetGameOpenById(x300101_g_GameId) ~= 1 then
		--记录日志
		local strMsg = format("DML:<Info>x300101_ProcTiming GM close sceneId = %d", sceneId )
    	WriteLog( 1, strMsg )
		return		
	end
	
	local nCount = QuestQuiz_GetQuestionCount()
	local idx = GetQuestData(sceneId, selfId, MD_QUIZ_ANSWER[1], MD_QUIZ_ANSWER[2], MD_QUIZ_ANSWER[3])-1
	if idx < 0 or idx > nCount then
		idx = random(1,nCount)
	end
	
	--得到谜语
	local id,strDesc,strAnswer1,strAnswer2,strAnswer3,strAnswer4,nAnswer = QuestQuiz_GetQuestionInfo(idx-1)
	
	SetQuestData(sceneId, selfId, MD_QUIZ_ANSWER[1], MD_QUIZ_ANSWER[2], MD_QUIZ_ANSWER[3], idx+1)
	
	--更新对话框内容
	BeginQuestEvent(sceneId)
		
		local daycount = x300101_GetDayCount(sceneId, selfId)
		local t, d = x300101_GetTurnCount( sceneId,selfId, daycount+1 )
		AddQuestText(sceneId,format("第%d轮第%d道题目\n", t, d))
		
		AddQuestText(sceneId,strDesc)
		x300101_AddDengmiAnswerOption( sceneId, 
										strAnswer1, 
										strAnswer2, 
										strAnswer3, 
										strAnswer4 )
									
	EndQuestEvent(sceneId)
	DispatchQuestEventList(sceneId,selfId,npcId)	
end

function x300101_AnswerRight( sceneId, selfId, npcId )
	--相关提示
	local daycount = x300101_GetDayCount(sceneId, selfId)+1
	local t, d = x300101_GetTurnCount( sceneId, selfId, daycount )
	local msg = "恭喜你答对了。"
	Msg2Player(sceneId,selfId,msg,8,3)
	Msg2Player(sceneId,selfId,msg,8,2)
	if d ~= 3 then
		x300101_ShowQuiz(sceneId, selfId, npcId)
	else
		if daycount >= x300101_g_MaxCount then
			
			
			--更新对话框内容
			BeginQuestEvent(sceneId)
				--AddQuestText(sceneId,"\t恭喜你答对了。" )
				AddQuestText(sceneId,"恭喜你完成了此轮仕官晋级，你今天已完成了所有的考验。请明天再来挑战，祝您明天有更多的收获。")	
			EndQuestEvent(sceneId)
			DispatchQuestEventList(sceneId,selfId,npcId)
		else
			--local msg = format("\t恭喜你答对了。" )
			--Msg2Player(sceneId,selfId,msg,8,3)
			--Msg2Player(sceneId,selfId,msg,8,2)
			
			BeginQuestEvent(sceneId)
				if x300101_g_MaxCount - daycount <1 then
					AddQuestText(sceneId,format("\t恭喜你完成了此轮仕官晋级，你今天已完成了所有的考验。请明天再来挑战，祝您明天有更多的收获。") )				
				else
					AddQuestText(sceneId,format("\t恭喜你完成了此轮仕官晋级，你今天还可以进行#R%d轮#W。你还想参加下一轮的考验吗？",(x300101_g_MaxCount - daycount)/3 ) )
				end	
			EndQuestEvent(sceneId)
			DispatchQuestEventList(sceneId,selfId,npcId)
		end
	end
	
	--给奖励
	x300101_GiveBonus( sceneId,selfId, 1 , daycount)
	
	--添加玩法日志
	GamePlayScriptLog( sceneId, selfId, 1501)
end

function x300101_AnswerError( sceneId, selfId, npcId )
	local daycount = x300101_GetDayCount(sceneId, selfId)+1
	local t, d = x300101_GetTurnCount( sceneId, selfId, daycount )
	local msg = "很遗憾，你答错了。"
		Msg2Player(sceneId,selfId,msg,8,3)
		Msg2Player(sceneId,selfId,msg,8,2)
			
	if d ~= 3 then
		x300101_ShowQuiz(sceneId, selfId, npcId)		
	else
		if daycount >= x300101_g_MaxCount then

			
			--更新对话框内容
			BeginQuestEvent(sceneId)
				--AddQuestText(sceneId,"\t很遗憾，你答错了。")	
				AddQuestText(sceneId,"\t恭喜你完成了此轮仕官晋级，你今天已完成了所有的考验。请明天再来挑战，祝您明天有更多的收获。")	
			EndQuestEvent(sceneId)
			DispatchQuestEventList(sceneId,selfId,npcId)
		else
			--local msg = format("\t很遗憾，你答错了。",x300101_g_MaxCount - daycount )
			--Msg2Player(sceneId,selfId,msg,8,3)
			--Msg2Player(sceneId,selfId,msg,8,2)
			
			BeginQuestEvent(sceneId)
				if x300101_g_MaxCount - daycount <1 then
					AddQuestText(sceneId,format("\t恭喜你完成了此轮仕官晋级，你今天已完成了所有的考验。请明天再来挑战。祝您明天有更多的收获。") )				
				else
					AddQuestText(sceneId,format("\t恭喜你完成了此轮仕官晋级，你今天还可以进行#R%d轮#W。你还想参加下一轮次的仕官晋级吗？",(x300101_g_MaxCount - daycount)/3 ) )
				end				
			EndQuestEvent(sceneId)
			DispatchQuestEventList(sceneId,selfId,npcId)
		end
	end
	
	--给奖励
	x300101_GiveBonus( sceneId,selfId, 0, daycount )
	
	--添加玩法日志
	GamePlayScriptLog( sceneId, selfId, 1502)
end

----------------------------------------------------------------------------------------------
--脚本默认事件
----------------------------------------------------------------------------------------------
function x300101_ProcEventEntry( sceneId ,selfId, npcId,idScript,idExt )

	--活动未开启
	if GetGameOpenById(x300101_g_GameId) ~= 1 then
		
		--通知客户端清除数据
		QuestDengmi_SendDengmiInfo( sceneId, selfId, -1, -1 )
		
		--给出相关提示
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"仕官晋级任务已经关闭！")				
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,npcId)
		return
	end
	
	-- 检查次数
	local daycount = x300101_GetDayCount(sceneId, selfId)
	if daycount >= x300101_g_MaxCount then
		--更新对话框内容
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"\t今天你已经完成了所有的仕官晋级考验了，请明天再来吧。")				
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,npcId)
		return
	end
	
	local t, d, bonusExp, bonusMoney = x300101_GetBonusExp( sceneId, selfId, 1, daycount+1 )
	
	if idExt == 12000 then
		if d == 1 and GetQuestData(sceneId, selfId, MD_QUIZ_ANSWER[1], MD_QUIZ_ANSWER[2], MD_QUIZ_ANSWER[3]) == 0 then
			-- 检查现银（银卡）
			local ret, type = SpendMoney( sceneId , selfId ,bonusMoney,301)
			if ret ~= 1 then
				local sillerMode
				if GetSillerMode(sceneId,selfId) == 1 then
					sillerMode = "现银"
				else
					sillerMode = "银卡"
				end
				local Readme = "很抱歉，此轮仕官晋级需要"..(bonusMoney/1000).."两"..sillerMode
				Msg2Player(sceneId,selfId,Readme,8,3)
				Msg2Player(sceneId,selfId,Readme,8,2)
				return
			else
				local sillerMode
				if type == 0 then
					sillerMode = "现银"
				else
					sillerMode = "银卡"
				end
				local Readme = format("参与仕官晋级成功，扣除#R%s#{_MONEY%d}。", sillerMode, bonusMoney)
				Msg2Player(sceneId,selfId,Readme,8,3)
				Msg2Player(sceneId,selfId,Readme,8,2)
			end
		end
		x300101_ShowQuiz(sceneId, selfId, npcId)
	elseif idExt >= 11001 and idExt <= 11004 then
		--取得题目信息
		local nCount = QuestQuiz_GetQuestionCount()
		local idx = GetQuestData(sceneId, selfId, MD_QUIZ_ANSWER[1], MD_QUIZ_ANSWER[2], MD_QUIZ_ANSWER[3])-1
		if idx < 0 or idx > nCount then
			return
		end
	
		--得到谜语
		local id,strDesc,strAnswer1,strAnswer2,strAnswer3,strAnswer4,nAnswer = QuestQuiz_GetQuestionInfo(idx-1)
		
		SetQuestData(sceneId, selfId, MD_QUIZ_ANSWER[1], MD_QUIZ_ANSWER[2], MD_QUIZ_ANSWER[3], 0)
	
		--题目编号检查通过了，这里再检查答案是否正确
		if 11000+nAnswer == idExt then
			--答对了
			x300101_AnswerRight( sceneId, selfId, npcId )
		else
			--答错了
			x300101_AnswerError( sceneId, selfId, npcId )
		end	
		
		x300101_SetDayCount(sceneId, selfId)
	else
	
		local daycount = x300101_GetDayCount(sceneId, selfId)
		local t, d = x300101_GetTurnCount( sceneId,selfId, daycount+1 )
		
		--更新对话框内容
		BeginQuestEvent(sceneId)
		
			AddQuestText(sceneId,"【个人】仕官晋级")
			if GetQuestData(sceneId, selfId, MD_QUIZ_ANSWER[1], MD_QUIZ_ANSWER[2], MD_QUIZ_ANSWER[3]) == 0 then
				AddQuestText(sceneId,format("\t我这里每天为每人准备了#G五套#W考题作为仕官晋级的考验，每套题有#G三道#W题目。\n\t答对我出的题会获得高额的经验,如果回答错误，你的经验奖励将会减半。\n\t今天你还可以参加#R%d轮#W考验，只要交付我#R%d两#W银币，就可以参加本轮的仕官晋级，共三题，每答对一题你会得到#R%d经验#W。", 6-t, bonusMoney/1000, bonusExp))
				AddQuestNumText(sceneId,x300101_g_ScriptId,"开始考验",0,12000)
			else
				AddQuestText(sceneId,format("\t我这里每天为每人准备了#G五套#W考题作为仕官晋级的考验，每套题有#G三道#W题目。答对我出的题会获得高额经验；如果回答错误，你的经验奖励将会减半。\n\t请继续本轮的考验，每答对一题你会得到%d经验。", bonusExp))
				AddQuestNumText(sceneId,x300101_g_ScriptId,"继续本轮考验",0,12000)
		  end						
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,npcId)	
	end
		    
end

function x300101_ProcAcceptCheck( sceneId, selfId, NPCId )
    return 0
end

----------------------------------------------------------------------------------------------
--接受
----------------------------------------------------------------------------------------------
function x300101_ProcAccept( sceneId, selfId )
end

----------------------------------------------------------------------------------------------
--放弃
----------------------------------------------------------------------------------------------
function x300101_ProcQuestAbandon( sceneId, selfId, MissionId )
end

----------------------------------------------------------------------------------------------
--继续
----------------------------------------------------------------------------------------------
function x300101_OnContinue( sceneId, selfId, targetId )
end

----------------------------------------------------------------------------------------------
--检测是否可以提交
----------------------------------------------------------------------------------------------
function x300101_CheckSubmit( sceneId, selfId )
end

----------------------------------------------------------------------------------------------
--提交
----------------------------------------------------------------------------------------------
function x300101_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end

----------------------------------------------------------------------------------------------
--杀死怪物或玩家
----------------------------------------------------------------------------------------------
function x300101_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end

----------------------------------------------------------------------------------------------
--进入区域事件
----------------------------------------------------------------------------------------------
function x300101_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

----------------------------------------------------------------------------------------------
--道具改变
----------------------------------------------------------------------------------------------
function x300101_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end

---------------------------------------------------------------------------------------------------
--取得此任务当天当前已完成次数
---------------------------------------------------------------------------------------------------
function x300101_GetDayCount(sceneId, selfId)
	if x300101_g_MaxCount > 0 then
		local today = GetDayOfYear()
		local lastday = GetQuestData(sceneId, selfId, MD_QUIZ_DATE[1], MD_QUIZ_DATE[2], MD_QUIZ_DATE[3])
		if lastday ~= today then
			return 0
		end

		local daycount =  GetQuestData(sceneId, selfId, MD_QUIZ_COUNT[1], MD_QUIZ_COUNT[2], MD_QUIZ_COUNT[3])
		return daycount

	end
	return 0
end

---------------------------------------------------------------------------------------------------
--更新当天接任务次数
---------------------------------------------------------------------------------------------------
function x300101_SetDayCount(sceneId, selfId)
	local today = GetDayOfYear()
	local lastday = GetQuestData(sceneId, selfId, MD_QUIZ_DATE[1], MD_QUIZ_DATE[2], MD_QUIZ_DATE[3])
	if lastday ~= today then
		SetQuestData(sceneId, selfId, MD_QUIZ_DATE[1], MD_QUIZ_DATE[2], MD_QUIZ_DATE[3], today)
		SetQuestData(sceneId, selfId, MD_QUIZ_COUNT[1], MD_QUIZ_COUNT[2], MD_QUIZ_COUNT[3], 1)
	else
		local daycount = GetQuestData(sceneId, selfId, MD_QUIZ_COUNT[1], MD_QUIZ_COUNT[2], MD_QUIZ_COUNT[3])
		SetQuestData(sceneId, selfId, MD_QUIZ_COUNT[1], MD_QUIZ_COUNT[2], MD_QUIZ_COUNT[3], daycount+1)
	end
end
