--帮会镖车任务发布
--MisDescBegin
x300607_g_ScriptId =  300607
x300607_g_MissionName = "【帮会】召集"
--MisDescEnd


x300607_g_Leader_Index = 5


function x300607_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
 	  	local pos = GetGuildOfficial(sceneId, selfId)
      	if pos == x300607_g_Leader_Index then			--是帮主
  			if QuestCheckAcceptNM( sceneId, selfId, targetId, MissionId ) > 0 then	-- 如果没有这个任务	-- 如果可以接这个任务
  				--GetGuildQuestData(sceneId, selfId, GD_GUILD_INDEX_YUNBIAO_SSUE_TIME, x300607_g_ScriptId,MissionId,"OnCallBackEnumerate",targetId)
				AddQuestTextNM( sceneId, selfId, targetId, MissionId, 3, -1 )	 -- 显示任务信息
				return 1
			end
		end
end

--function x300607_OnCallBackEnumerate( sceneId, selfId,MissionData,MissionId,targetId )
--
--	local CurDaytime = GetDayTime()
--	if MissionData ~= CurDaytime then					--上次发布的时间不是今天
--	    --local state = GetQuestStateNM(sceneId,selfId,targetId,MissionId)
--		AddQuestTextNM( sceneId, selfId, targetId, MissionId, 3, -1 ) 		-- 显示任务信息
--		DispatchQuestEventList(sceneId,selfId,targetId)
--		return 0
--	end
--
--	return 0
--end

--选中任务
function x300607_ProcEventEntry( sceneId, selfId, targetId, MissionId )
                                   
		local ret = QuestCheckAcceptNM( sceneId, selfId, targetId, MissionId )
		if ret > 0 then	-- 如果可以接这个任务
  			local pos = GetGuildOfficial(sceneId, selfId)
  			if pos ~= x300607_g_Leader_Index then			--不是帮主
  				return 0
 			end         
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"#Y【帮会】帮会召集")
			AddQuestText(sceneId,"\t您可以通过我，向全体帮会成员发送召集信息，若对方同意则会出现在您的身边；若对方处于特殊状态或不同意则不会出现在您的身边。\n\t此功能每天只能使用一次。")
			AddQuestText( sceneId, "")
			EndQuestEvent()
			DispatchQuestInfo(sceneId, selfId, targetId, MissionId, -1)
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
function x300607_ProcQuestAccept( sceneId, selfId, targetId, MissionId )
  			GetGuildQuestData(sceneId, selfId, GD_GUILD_INDEX_YUNBIAO_SSUE_TIME, x300607_g_ScriptId,MissionId,"OnReturn")
end


function x300607_OnReturn(sceneId, selfId,MissionData,MissionId,targetId)
	local CurDaytime = GetDayTime()
	if MissionData == CurDaytime then					--上次发布的时间是今天
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "很抱歉，【帮会】帮会召集每天只能进行一次！")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		local Readme = "很抱歉，【帮会】帮会召集每天只能进行一次！"
		Msg2Player(sceneId,selfId,Readme,8,2)
	else
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "【帮会】帮会召集发布成功，您的兄弟们会尽快赶来！")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		local Readme = "【帮会】帮会召集发布成功，您的兄弟们会尽快赶来！"
		Msg2Player(sceneId,selfId,Readme,8,2)
		
		--接任务写日志
		GamePlayScriptLog(sceneId,selfId,871)

 		local GuildID = GetGuildID(sceneId,selfId)
		SetGuildQuestData(sceneId, GuildID, GD_GUILD_INDEX_YUNBIAO_SSUE_TIME, CurDaytime)
		RecruitGuildConvoy(sceneId, selfId)
	end	
	
	--DispatchQuestEventList(sceneId, selfId, -1)
end



