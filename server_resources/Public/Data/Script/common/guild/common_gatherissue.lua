
x300620_g_ScriptId =  300620
--帮会采集任务

x300620_g_Leader_Index   = 5

function x300620_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

	local pos = GetGuildOfficial(sceneId, selfId)
	if pos == x300620_g_Leader_Index then			--是帮主  
		if QuestCheckAcceptNM( sceneId, selfId, targetId, MissionId ) > 0 then	-- 如果可以接这个任务
            GetGuildQuestData(sceneId, selfId, GD_GUILD_INDEX_GATHER_ISSUE_TIME, x300620_g_ScriptId,MissionId,"OnCallBackEnumerate",targetId)
			return 0
		end
	end

	return 0
end


function x300620_OnCallBackEnumerate( sceneId, selfId,MissionData,MissionId,targetId )


	local CurDaytime = GetDayTime()
	if MissionData ~= CurDaytime then					--上次发布的时间不是今天
	    --local state = GetQuestStateNM(sceneId,selfId,targetId,MissionId)
		AddQuestTextNM( sceneId, selfId, targetId, MissionId, 3, -1 ) 		-- 显示任务信息
		DispatchQuestEventList(sceneId,selfId,targetId)
		return 0
	end
	
	return 0
end

--选中任务
function x300620_ProcEventEntry( sceneId, selfId, targetId, MissionId )

		local ret = QuestCheckAcceptNM( sceneId, selfId, targetId, MissionId )

		if ret > 0 then	-- 如果可以接这个任务
  			local pos = GetGuildOfficial(sceneId, selfId)
  		
  			if pos ~= x300620_g_Leader_Index then			--不是帮主
  				return 0
 			end
            AddDispatchQuestInfoNM( sceneId, selfId, targetId, MissionId ) -- 显示接受任务信息		
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
			end
			BeginQuestEvent(sceneId)
			--AddQuestText(sceneId, strText);
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
		end
  
end


--**********************************
--接受
--**********************************
function x300620_ProcQuestAccept( sceneId, selfId, targetId, MissionId )
	
 	local level = GetLevel(sceneId,selfId)
	if level < 50 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "很抱歉，50级以后才能发布帮会采集任务！");
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		local Readme = "很抱歉，50级以后才能发布帮会采集任务！" 
		Msg2Player(sceneId,selfId,Readme,8,2)
		return
	end
				
  	GetGuildQuestData(sceneId, selfId, GD_GUILD_INDEX_GATHER_ISSUE_TIME, x300620_g_ScriptId,MissionId,"OnReturn")
end

function x300620_OnReturn(sceneId, selfId,MissionData,MissionId,targetId)

	local CurDaytime = GetDayTime()
	if MissionData == CurDaytime then					--上次发布的时间是今天
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "今天你已发布过帮会采集，请改天在来吧！")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		local Readme = "今天你已发布过帮会采集，请改天在来吧！" 
		Msg2Player(sceneId,selfId,Readme,8,2)
	else
		local title =GetGuildTitle(sceneId, selfId)
		local str = format("%s发布了今天的帮会采集任务,稍候可以到帮战发布人处领取任务",title)
		Msg2Player(sceneId, selfId,str,6,0)
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "您发布了今天的帮会采集任务！")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		local Readme = "您发布了今天的帮会采集任务,稍候可以到帮战发布人处领取任务！" 
		Msg2Player(sceneId,selfId,Readme,8,2)
 		local GuildID = GetGuildID(sceneId,selfId)
		SetGuildQuestData(sceneId, GuildID, GD_GUILD_INDEX_GATHER_ISSUE_TIME, CurDaytime)
	end
	
--DispatchQuestEventList(sceneId, selfId, -1)
	
end



