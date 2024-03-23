x310051_g_scriptId = 310051 

x310051_g_Missionlist = { 8060, 8061,8062,8063,8064,8065 }
x310051_g_Missionlist2 = { 8054, 8055,8056,8057,8058,8059 }


function x310051_ProcEventEntry( sceneId, selfId, BagIndex )
	local level = GetLevel( sceneId, selfId )
	if level < 40 then
		local strText = "您的等级太低，还无法领悟天龙魂的奥秘"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, strText)
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId, selfId)
		Msg2Player(sceneId,selfId,"您的等级太低，还无法领悟天龙魂的奥秘",8,2)
		return
	end
	
	local rand = random(1,6)
	local ret = 0
	if level >=40 and level<65 then
		for i, item in x310051_g_Missionlist do
			if IsHaveQuestNM( sceneId, selfId, item ) > 0 then	-- 如果没这个任务直接退出
				local strText = "您已经有唤醒天龙魂任务了，无法重复领取"
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId, strText)
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId, selfId)
				Msg2Player(sceneId,selfId,"您已经有唤醒天龙魂任务了，无法重复领取",8,2)
				return 
			end
		
		end

		--检查前置任务
		local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId, x310051_g_Missionlist[rand] )
		if FrontMissiontId1 ~= -1 then
			if IsQuestHaveDoneNM( sceneId, selfId, FrontMissiontId1 ) == 0 then
				return 0--如果前置任务没做直接返回
			end
		end
		if FrontMissiontId2 ~= -1 then
			if IsQuestHaveDoneNM( sceneId, selfId, FrontMissiontId2 ) == 0 then
				return 0--如果前置任务没做直接返回
			end
		end
		if FrontMissiontId3 ~= -1 then
			if IsQuestHaveDoneNM( sceneId, selfId, FrontMissiontId3 ) == 0 then
				return 0--如果前置任务没做直接返回
			end
		end

		ret = AddQuestNM( sceneId, selfId, x310051_g_Missionlist[rand])
	else
		for i, item in x310051_g_Missionlist2 do
			if IsHaveQuestNM( sceneId, selfId, item ) > 0 then	-- 如果没这个任务直接退出
				local strText = "您已经有唤醒天龙魂任务了，无法重复领取"
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId, strText)
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId, selfId)
				Msg2Player(sceneId,selfId,"您已经有唤醒天龙魂任务了，无法重复领取",8,2)
				return 
			end
		
		end

		--检查前置任务
		local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId, x310051_g_Missionlist2[rand] )
		if FrontMissiontId1 ~= -1 then
			if IsQuestHaveDoneNM( sceneId, selfId, FrontMissiontId1 ) == 0 then
				return 0--如果前置任务没做直接返回
			end
		end
		if FrontMissiontId2 ~= -1 then
			if IsQuestHaveDoneNM( sceneId, selfId, FrontMissiontId2 ) == 0 then
				return 0--如果前置任务没做直接返回
			end
		end
		if FrontMissiontId3 ~= -1 then
			if IsQuestHaveDoneNM( sceneId, selfId, FrontMissiontId3 ) == 0 then
				return 0--如果前置任务没做直接返回
			end
		end

		ret = AddQuestNM( sceneId, selfId, x310051_g_Missionlist2[rand])

	end				
	
	if ret < 1 then
		if ret == -2 then
			local strText = "任务已满，添加任务失败"
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, strText)
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId, selfId)
			return
		end

		local strText = "添加任务失败"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, strText)
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId, selfId)
		return 
	else
		EraseItem(sceneId, selfId, BagIndex); --删除物品	
		local strText = "您获得了任务：唤醒天龙魂"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, strText)
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId, selfId)
		Msg2Player(sceneId,selfId,"您获得了任务：唤醒天龙魂",8,2)

		GamePlayScriptLog(sceneId, selfId, 541)
	end

	
end

function x310051_IsSkillLikeScript( sceneId, selfId)
	return 0; --这个脚本需要动作支持    
	--返回0，走上面的ProcEventEntry逻辑
	--返回1，走下面的逻辑
end

function x310051_CancelImpacts( sceneId, selfId )
	return 0; --不需要这个接口，但要保留空函数,并且始终返回0。
end

function x310051_OnConditionCheck( sceneId, selfId )
	return 0
end

function x310051_OnDeplete( sceneId, selfId )

	return 0
end

function x310051_OnActivateOnce( sceneId, selfId )
end

function x310051_OnActivateEachTick( sceneId, selfId)
	return 1; --不是引导性脚本, 只保留空函数.
end
