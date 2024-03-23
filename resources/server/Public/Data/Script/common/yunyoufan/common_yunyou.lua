--MisDescBegin
x310070_g_ScriptId 	  = 310070

--任务名称
x310070_g_MissionName = "【个人】寿诞采办"
-- 任务信息
x310070_g_MissionInfo = "\t@npc_%d采购了一批#G%s#W，请你帮忙去把它们运送到驿站，以便驿站将贡品转运到皇宫内库。不过首先请你#G将这匹御马交给皇宫门口处的大元御卫兵#W，他会把一辆运货马车交给你使用。\n\t在宫内当差诸事都要操心，唯恐办不好差事，辜负了皇恩。\n\t注：本活动于#G每日19：30~24：00#W开放，#G等级在40或以上#W的玩家可以领取任务。\n"
-- 任务提示
x310070_g_MissionHelp = "\t#G如果你在护送的过程中下线或者远离他超过5分钟，你的任务就会失败。\n\t请尽快完成吧，尽早完成的话朝廷会给你更多奖励的。"
-- 任务目标
x310070_g_MissionTarget = "  把马护送到@npc_139235处。"
x310070_g_NPCName = "@npc_139235"
x310070_TargetNPCList	=	{139109, 139110, 139111, 139112, 139113}
x310070_g_MissionComment = "\t下月十五是圣上寿诞之日，我大元皇帝天威远播，十路采办已经纷至踏来，詹事院应接不暇。本总管有一事相请，劳烦你到尚未接待的各路采办处，帮我将他们敬献给皇帝陛下的礼物运送到各大驿站，在由驿站转运到皇宫内库。\n\t注：本活动于#G每日19：30~24：00#W开放，#G等级在40或以上#G的，今日没有接过任务的玩家可以领取任务。"


--MisDescEnd



x310070_g_MinLevel = 40


x310070_TargetList ={ "河南贡米", "金山田黄", "深海玉鲍", "南国龙果", "紫金圣物" }
x310070_g_BusScriptId = 310071

x310070_g_BusId = { 16,17,18,19,20 }
x310070_g_MissionId = 8080
x310070_g_MissionAcceptTime1 = { 1170, 1440 }	

function x310070_ProcAcceptChecked( sceneId, selfId )
	--local week = GetWeek()
	--if week == 0 then
		--local year, month, day = GetYearMonthDay()
		local minspan = GetMinOfDay();
		--if day>7 and day <=14 then
			if minspan >= x310070_g_MissionAcceptTime1[1] and minspan < x310070_g_MissionAcceptTime1[2] then
				return 1
			end
		--end
	--end
	return -1
end

function x310070_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
  	
	if IsHaveQuestNM( sceneId, selfId, MissionId ) == 0 then		-- 如果没有这个任务
		
		local playerLevel = GetLevel( sceneId, selfId);
		if( playerLevel >= x310070_g_MinLevel ) then
			local  missionState = GetQuestStateNM(sceneId, selfId, targetId, MissionId)
			AddQuestTextNM(sceneId, selfId, targetId, MissionId, missionState);
		end
		
	end

	return 0
end


--显示任务信息
function x310070_DispatchMissionInfo( sceneId, selfId, NPCId, index)
	BeginQuestEvent( sceneId);
		--任务信息
		AddQuestText(sceneId, "#Y"..x310070_g_MissionName);
		AddQuestText(sceneId, format(x310070_g_MissionInfo, x310070_TargetNPCList[index], x310070_TargetList[index]))

		--任务目标
		AddQuestText( sceneId, "#Y任务目标：")
		AddQuestText( sceneId, "把马匹安全护送到@npc_139235处")
		--提示信息
		if x310070_g_MissionHelp ~= "" then
			AddQuestText(sceneId, "#Y任务提示：")
			AddQuestText(sceneId, x310070_g_MissionHelp )
		end
		
		--奖励信息
		
		--获得玩家当前等级
		local playerLevel = GetLevel( sceneId, selfId);
		--获取经验
		local experience = playerLevel*1680
		AddQuestExpBonus( sceneId, experience);
      --AddQuestItemBonus(sceneId, 12110204, 1)
	  AddQuestMoneyBonus2(sceneId, playerLevel*100 )

	EndQuestEvent(sceneId);
	DispatchQuestInfoNM(sceneId, selfId, NPCId, x310070_g_ScriptId, x310070_g_MissionId, 1);
end

function x310070_DispatchComment(sceneId, selfId, targetId)
	BeginQuestEvent( sceneId);
		AddQuestText(sceneId, "#Y"..x310070_g_MissionName);
		AddQuestText(sceneId, x310070_g_MissionComment);
		local playerLevel = GetLevel( sceneId, selfId);
		local experience = playerLevel*1680
		AddQuestExpBonus( sceneId, experience);
   -- AddQuestItemBonus(sceneId, 12110204, 1)
	AddQuestMoneyBonus2(sceneId, playerLevel*100 )
	EndQuestEvent(sceneId);
	DispatchQuestInfoNM(sceneId, selfId, targetId, x310070_g_ScriptId, x310070_g_MissionId);
end


--点击（按钮）点击该任务后执行此脚本
function x310070_ProcEventEntry( sceneId, selfId, targetId, MissionId )
	
	if IsHaveQuestNM( sceneId, selfId, MissionId ) == 0 then	-- 如果没有这个任务
		local day = GetQuestData(sceneId, selfId, MD_YUNYOU_DATE[1], MD_YUNYOU_DATE[2], MD_YUNYOU_DATE[3])
	
		if day ~= GetDayOfYear() then
			SetQuestData(sceneId, selfId, MD_YUNYOU_DATE[1], MD_YUNYOU_DATE[2], MD_YUNYOU_DATE[3], 0)
		end
		x310070_DispatchComment(sceneId, selfId, targetId)
	else
			local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )
			if QuestCheckSubmitNM( sceneId, selfId, targetId, MissionId, misIndex ) > 0 then 	-- 如果任务可以完成
				--QuestComplateInfoNM( sceneId, selfId, targetId, MissionId ) 					-- 显示完成信息
				x310070_ProcQuestSubmit( sceneId, selfId, targetId, -1, MissionId )
			else
				QuestNotComplateInfoNM( sceneId, selfId, targetId, MissionId ) 				-- 显示任务未完成信息
			end

	end
		  
end


--**********************************
--接受
--**********************************
function x310070_ProcQuestAccept( sceneId, selfId, targetId, MissionId )
	if IsBusMember(sceneId, selfId) > 0 then
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, "很抱歉，护送中不能来参与活动");
		EndQuestEvent(sceneId);
		DispatchQuestTips(sceneId,selfId);
		Msg2Player(sceneId,selfId,"很抱歉，护送中不能来参与活动",8,2)
		return 
	end

	if IsTeamFollow(sceneId, selfId) == 1 then
		local Readme = "组队跟随状态下不可以接护送任务！"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, Readme);
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,Readme,8,2)
		return 
	end

	if IsPlayerMutexState(sceneId,selfId,PLAYER_STATE_TIESAN ) > 0 then
		local Readme = "您在做铁人三项，不可以接护送任务！"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, Readme);
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,Readme,8,2)
		return 
	end
		
	if x310070_ProcAcceptChecked( sceneId, selfId ) < 0 then
			local strText = "本活动在每日19：30~24：00举办"
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, strText);
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
			Msg2Player(sceneId,selfId,strText,8,2)
			return 
	end	

	local day = GetQuestData(sceneId, selfId, MD_YUNYOU_DATE[1], MD_YUNYOU_DATE[2], MD_YUNYOU_DATE[3])

	if day ~= 0 then

		local strText = "你今日已经接过任务，请明天再来"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, strText);
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,strText,8,2)
		return
	end

	local isFull = IsQuestFullNM( sceneId, selfId )

	if isFull > 0 then	
		local strText = "任务已满，添加任务失败"
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, strText);
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
		return
	end

	local index = random(1, 5)
	SetQuestData(sceneId, selfId, MD_YUNYOU_RAND[1], MD_YUNYOU_RAND[2], MD_YUNYOU_RAND[3], index)
	
	--检查前置任务
	local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId, MissionId )
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
	
	--请求创建bus
	local busObjId = CallScriptFunction( x310070_g_BusScriptId, "OnCreateBus", sceneId, selfId ,MissionId, x310070_g_BusId[index])
		
end

function x310070_OnCreateBusOK(sceneId, selfId, busObjId,targetId,MissionId)

	if busObjId > 0 then
		local ret = AddQuestNM( sceneId, selfId, MissionId ) -- 给玩家添加任务

		if ret > 0 then
			x310070_DispatchMissionInfo( sceneId, selfId, targetId, index);	

			local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )	
			SetQuestByIndex( sceneId, selfId, misIndex, 1, GetLevel(sceneId, selfId) )

			SetQuestData(sceneId, selfId, MD_YUNYOU_DATE[1], MD_YUNYOU_DATE[2], MD_YUNYOU_DATE[3], GetDayOfYear())
			SetQuestParam( sceneId, selfId, MissionId, 7, 1 )

				local message = "您接受了任务：【个人】寿诞采办"
				BeginQuestEvent(sceneId);
				AddQuestText(sceneId, message);
				EndQuestEvent();
				DispatchQuestTips(sceneId, selfId);
				Msg2Player(sceneId,selfId, message,4,2)

				GamePlayScriptLog(sceneId, selfId, 361)

		elseif ret == -2 then
			local strText = "任务已满，添加任务失败"
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, strText);
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
			  	
			if (IsObjValid (sceneId,busObjId) ~= 1) or GetBusQuestID(sceneId, busObjId) ~= MissionId then
				return
			end
			DeleteBus(sceneId, busObjId,1)
		elseif ret == -1 then
			local strText = "背包已满,添加任务失败"
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, strText);
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
			if (IsObjValid (sceneId,busObjId) ~= 1) or GetBusQuestID(sceneId, busObjId) ~= MissionId then
				return
			end
			DeleteBus(sceneId, busObjId,1)
		else
			local strText = "添加任务失败"
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, strText);
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
			if (IsObjValid (sceneId,busObjId) ~= 1) or GetBusQuestID(sceneId, busObjId) ~= MissionId then
				return
			end
			DeleteBus(sceneId, busObjId,1)
		end
	end
		
end

--完成任务
--返回1代表成功，0代表交任务失败
function x310070_ProcQuestSubmit( sceneId, selfId, targetId, selectId, MissionId )

	if IsHaveQuestNM( sceneId, selfId, MissionId) == 0 then	-- 如果没这个任务直接退出
		return 0
	end

	--镖车是否在有效距离
	local valid = IsValidMyselfBus(sceneId, selfId, MissionId)

	if valid == 0 then
		local Readme = "您护送的马车离您太远了，无法提交任务！"
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, Readme);
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,Readme,8,2)
		return 0
	end

	
	local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )
	local level = GetQuestParam( sceneId, selfId, misIndex, 1 )

	local index = GetQuestData(sceneId, selfId, MD_YUNYOU_RAND[1], MD_YUNYOU_RAND[2], MD_YUNYOU_RAND[3])

	local Readme = "恭喜您完成护送马匹任务"
	BeginQuestEvent(sceneId)
	AddQuestText(sceneId, Readme);
	EndQuestEvent(sceneId)
	DispatchQuestTips(sceneId,selfId)
	Msg2Player(sceneId,selfId,Readme,8,2)

	DelQuest( sceneId, selfId, MissionId)

	GamePlayScriptLog(sceneId, selfId, 362)
	
	local BusID  =  GetBusId(sceneId, selfId)
	if BusID ~= -1 then
		--如果BUS还活着
		DeleteBus(sceneId, BusID,1)
	end 
	
	CallScriptFunction( 310072, "PushAfterMission", sceneId, selfId ,targetId, level, index) 
	
	return 0
	
end


--********************************************************************
--放弃
--********************************************************************
function x310070_ProcQuestAbandon( sceneId, selfId,MissionId )

	if IsHaveQuestNM( sceneId, selfId, MissionId) == 0 then	-- 如果没有这个任务
		return
	end
	DelQuest( sceneId, selfId, MissionId)
	local message = "您放弃了任务：【个人】寿诞采办"
	BeginQuestEvent(sceneId);
		AddQuestText(sceneId, message);
	EndQuestEvent();
	DispatchQuestTips(sceneId, selfId);
	Msg2Player(sceneId,selfId, message,4,2)

	SetQuestData(sceneId, selfId, MD_YUNYOU_DATE[1], MD_YUNYOU_DATE[2], MD_YUNYOU_DATE[3], GetDayOfYear())

  	local BusID  =  GetBusId(sceneId, selfId)
	if (IsObjValid (sceneId,BusID) ~= 1) or GetBusQuestID(sceneId, BusID) ~= MissionId then
		return
	end

  	if BusID ~= -1 then
     	--如果BUS还活着
  		DeleteBus(sceneId, BusID,1)
  	end

end


function x310070_ProcQuestAttach( sceneId, selfId, npcId, npcGuid,misIndex, MissionId )
	if IsHaveQuestNM( sceneId, selfId, MissionId) == 0 then	-- 如果没有这个任务
		return
	end

	local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId)
	local submitGuid = GetQuestSubmitNPCGUIDNM( sceneId, selfId, misIndex )
	local  missionState = GetQuestStateNM(sceneId, selfId, npcId, MissionId)
	if npcGuid == submitGuid then	--点击的NPC的名字和任务中NPC的名字相同，场景也判断过了
		AddQuestTextNM( sceneId, selfId, npcId, MissionId, missionState, -1 ) -- 显示任务信息
	end
end



---------------------------------------------------------------------------------------------------
--任务日志刷新
function x310070_ProcQuestLogRefresh( sceneId, selfId, MissionId)
	local bHaveMission = IsHaveQuestNM(sceneId, selfId,MissionId );
		if bHaveMission > 0 then
		
		local index = GetQuestData(sceneId, selfId, MD_YUNYOU_RAND[1], MD_YUNYOU_RAND[2], MD_YUNYOU_RAND[3])	
			BeginQuestEvent(sceneId)			
		    AddQuestLogCustomText( sceneId,
									"",							-- 标题
									x310070_g_MissionName,      -- 任务名字
									x310070_g_MissionTarget,	--任务目标
									x310070_g_NPCName,			--任务NPC
									"",      --任务攻略
									format(x310070_g_MissionInfo, x310070_TargetNPCList[index], x310070_TargetList[index]),		--任务描述
									x310070_g_MissionHelp							--任务小提示
									)
      AddQuestExpBonus(sceneId, GetLevel(sceneId, selfId)*1680)
      --AddQuestItemBonus(sceneId, 12110204, 1)
	  AddQuestMoneyBonus2(sceneId, GetLevel(sceneId, selfId)*100 )
			EndQuestEvent(sceneId)
			DispatchQuestLogUpdate(sceneId, selfId, MissionId);
		end
end
