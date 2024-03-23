
x310073_g_SubMission			=	{ 
									{ MissionId=8086, 
										MissionName = "【个人】寿诞采办", 
										MissionTarget = "  把货物安全送到@npc_139001处", 
										MissionInfo = "\t下官正是@npc_139109，前来为大元皇帝寿诞敬献贡品，此次纳贡事宜均由海总管负责，恰逢陛下寿诞宫中事务繁忙，下官一直在等待上差前来接受贺寿的贡品和我们对陛下的祝福。\n\t这些就是下官采办来敬献给陛下的贡品，我已经装上马车，请上差验查。如贡品无误请将此车交到@npc_139001处。\n",
										MissionHelp = "\t如果你在护送的过程中下线或者远离他超过5分钟，你的任务就会失败。请尽快完成吧，尽早完成的话朝廷会给你更多奖励的。", 
										NpcName="@npc_139001"
									}, 
									{ MissionId=8087, 
										MissionName = "【个人】寿诞采办", 
										MissionTarget = "  把货物安全送到@npc_139004处", 
										MissionInfo = "\t下官正是@npc_139110，前来为大元皇帝寿诞敬献贡品，此次纳贡事宜均由海总管负责，恰逢陛下寿诞宫中事务繁忙，下官一直在等待上差前来接受贺寿的贡品和我们对陛下的祝福。\n\t这些就是下官采办来敬献给陛下的贡品，我已经装上马车，请上差验查。如贡品无误请将此车交到@npc_139004处。\n",
										MissionHelp = "\t如果你在护送的过程中下线或者远离他超过5分钟，你的任务就会失败。请尽快完成吧，尽早完成的话朝廷会给你更多奖励的。", 
										NpcName="@npc_139004"
									}, 
									{ MissionId=8088, 
										MissionName = "【个人】寿诞采办", 
										MissionTarget = "  把货物安全送到@npc_139006处", 
										MissionInfo = "\t下官正是@npc_139111，前来为大元皇帝寿诞敬献贡品，此次纳贡事宜均由海总管负责，恰逢陛下寿诞宫中事务繁忙，下官一直在等待上差前来接受贺寿的贡品和我们对陛下的祝福。\n\t这些就是下官采办来敬献给陛下的贡品，我已经装上马车，请上差验查。如贡品无误请将此车交到@npc_139006处。\n",
										MissionHelp = "\t如果你在护送的过程中下线或者远离他超过5分钟，你的任务就会失败。请尽快完成吧，尽早完成的话朝廷会给你更多奖励的。", 
										NpcName="@npc_139006"
									}, 
									{ MissionId=8089, 
										MissionName = "【个人】寿诞采办", 
										MissionTarget = "  把货物安全送到@npc_139000处", 
										MissionInfo = "\t下官正是@npc_139112，前来为大元皇帝寿诞敬献贡品，此次纳贡事宜均由海总管负责，恰逢陛下寿诞宫中事务繁忙，下官一直在等待上差前来接受贺寿的贡品和我们对陛下的祝福。\n\t这些就是下官采办来敬献给陛下的贡品，我已经装上马车，请上差验查。如贡品无误请将此车交到@npc_139000处。\n",
										MissionHelp = "\t如果你在护送的过程中下线或者远离他超过5分钟，你的任务就会失败。请尽快完成吧，尽早完成的话朝廷会给你更多奖励的。", 
										NpcName="@npc_139000"
									}, 
									{ MissionId=8090, 
										MissionName = "【个人】寿诞采办", 
										MissionTarget = "  把货物安全送到@npc_139005处", 
										MissionInfo = "\t下官正是@npc_139113，前来为大元皇帝寿诞敬献贡品，此次纳贡事宜均由海总管负责，恰逢陛下寿诞宫中事务繁忙，下官一直在等待上差前来接受贺寿的贡品和我们对陛下的祝福。\n\t这些就是下官采办来敬献给陛下的贡品，我已经装上马车，请上差验查。如贡品无误请将此车交到@npc_139005处。\n",
										MissionHelp = "\t如果你在护送的过程中下线或者远离他超过5分钟，你的任务就会失败。请尽快完成吧，尽早完成的话朝廷会给你更多奖励的。", 
										NpcName="@npc_139005"
									}
										}


 
x310073_g_BusScriptId = 310071

x310073_g_ScriptId = 310073
x310073_g_BusId = { 26,27,28,29,30 }
x310073_g_AwardItem = 12110204

function x310073_PushAfterMission(sceneId, selfId , target, level, index)
	local isFull = IsQuestFullNM( sceneId, selfId )

	if isFull > 0 then	
		local strText = "任务已满，添加任务失败"
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, strText);
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
		return
	end
	
	local busObjId = CallScriptFunction( x310073_g_BusScriptId, "OnCreateBus", sceneId, selfId ,x310073_g_SubMission[index].MissionId, x310073_g_BusId[index])

end

function x310073_OnCreateBusOK(sceneId, selfId, busObjId,targetId,MissionId,index)
	if busObjId < 0 then
		local strText = "无法创建镖车，添加任务失败"
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, strText);
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
		return
	end
	
	--检查前置任务
	local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId, x310073_g_SubMission[index].MissionId )
	if FrontMissiontId1 ~= -1 then
		if IsQuestHaveDoneNM( sceneId, selfId, FrontMissiontId1 ) == 0 then
			return 
		end
	end
	if FrontMissiontId2 ~= -1 then
		if IsQuestHaveDoneNM( sceneId, selfId, FrontMissiontId2 ) == 0 then
			return 
		end
	end
	if FrontMissiontId3 ~= -1 then
		if IsQuestHaveDoneNM( sceneId, selfId, FrontMissiontId3 ) == 0 then
			return
		end
	end
 
	local ret = AddQuestNM( sceneId, selfId, x310073_g_SubMission[index].MissionId ) -- 给玩家添加任务

	if ret <0 then
		if (IsObjValid (sceneId,busObjId) ~= 1) or GetBusQuestID(sceneId, busObjId) ~= x310073_g_SubMission[index].MissionId then
			return
		end
		DeleteBus(sceneId, busObjId,1)

		if ret == -2 then
			local strText = "任务已满，添加任务失败"
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, strText);
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
		elseif ret == -1 then
			local strText = "背包已满,添加任务失败"
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, strText);
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
		else
			local strText = "添加任务失败"
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, strText);
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
		end
		return
	end

	GamePlayScriptLog(sceneId, selfId, 381)

	SetQuestParam( sceneId, selfId, x310073_g_SubMission[index].MissionId, 7, 1 )

	local misIndex = GetQuestIndexByID( sceneId, selfId, x310073_g_SubMission[index].MissionId )	
	SetQuestByIndex( sceneId, selfId, misIndex, 1, GetLevel(sceneId, selfId) )

	BeginQuestEvent( sceneId);
		--任务信息
		AddQuestText(sceneId, "#Y"..(x310073_g_SubMission[index].MissionName));
		AddQuestText(sceneId, x310073_g_SubMission[index].MissionInfo)

		--任务目标
		AddQuestText( sceneId, "#Y任务目标：")
		AddQuestText( sceneId, x310073_g_SubMission[index].MissionTarget)
		--提示信息
		if x310073_g_SubMission[index].MissionHelp ~= "" then
			AddQuestText(sceneId, "#Y任务提示：")
			AddQuestText(sceneId, x310073_g_SubMission[index].MissionHelp )
		end

	
		--获取经验
		local experience = level*1680
		AddQuestExpBonus( sceneId, experience);
		AddQuestMoneyBonus2(sceneId, level*100 )

	EndQuestEvent(sceneId);
	DispatchQuestInfoNM(sceneId, selfId, target, x310073_g_ScriptId, x310073_g_SubMission[index].MissionId, 1);

end

function x310073_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
  	
end


--点击（按钮）点击该任务后执行此脚本
function x310073_ProcEventEntry( sceneId, selfId, targetId, MissionId )
	
	if IsHaveQuestNM( sceneId, selfId, MissionId ) > 0 then	-- 如果有这个任务
		
			local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )
			if QuestCheckSubmitNM( sceneId, selfId, targetId, MissionId, misIndex ) > 0 then 	-- 如果任务可以完成
				BeginQuestEvent( sceneId);
					--任务信息
					AddQuestText(sceneId, "#Y【个人】寿诞采办#W\n\谢谢你为陛下所做的一切，这是你应得的奖励，请笑纳。");

					local level = GetLevel(sceneId, selfId)
					AddQuestExpBonus(sceneId, level*1680 )
					--AddQuestItemBonus(sceneId, x310073_g_AwardItem, 1)
					AddQuestMoneyBonus2(sceneId, level*100 )
					
				EndQuestEvent(sceneId);
				DispatchQuestContinueInfoNM(sceneId, selfId, targetId, x310073_g_ScriptId, MissionId);
				--QuestComplateInfoNM( sceneId, selfId, targetId, MissionId ) 					-- 显示完成信息
			else
				QuestNotComplateInfoNM( sceneId, selfId, targetId, MissionId ) 				-- 显示任务未完成信息
			end

	end
		  
end


--**********************************
--接受
--**********************************
function x310073_ProcQuestAccept( sceneId, selfId, targetId, MissionId )
	
end


--**********************************
--接受
--**********************************
function x310073_ProcAccept( sceneId, selfId )
	
end

--完成任务
--返回1代表成功，0代表交任务失败
function x310073_ProcQuestSubmit( sceneId, selfId, targetId, selectId, MissionId )

	if IsHaveQuestNM( sceneId, selfId, MissionId) == 0 then	-- 如果没这个任务直接退出
		return 
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
		return 
	end

	
	local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )
	local level = GetLevel( sceneId, selfId )
	local awardMoney = level*100

	local index = GetQuestData(sceneId, selfId, MD_YUNYOU_RAND[1], MD_YUNYOU_RAND[2], MD_YUNYOU_RAND[3])
	
	local message = "您完成了任务：寿诞采办"
	BeginQuestEvent(sceneId);
		AddQuestText(sceneId, message);
	EndQuestEvent();
	DispatchQuestTips(sceneId, selfId);
	Msg2Player(sceneId,selfId, message,4,2)

	DelQuest( sceneId, selfId, MissionId)

	GamePlayScriptLog(sceneId, selfId, 382)
	
	local BusID  =  GetBusId(sceneId, selfId)
	if BusID ~= -1 then
		--如果BUS还活着
		DeleteBus(sceneId, BusID,1)
	end 

	local day = GetQuestData(sceneId, selfId, MD_YUNYOU_DATE[1], MD_YUNYOU_DATE[2], MD_YUNYOU_DATE[3])
	if day ~= GetDayOfYear() then
		local experience = level*1680
		AddExp( sceneId, selfId, experience )

		message = format("#Y获得#R经验%d点#Y奖励。", experience)
		BeginQuestEvent(sceneId);
			AddQuestText(sceneId, message);
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
		Msg2Player(sceneId,selfId, message,4,2)
		
		AddMoney( sceneId, selfId,0, awardMoney )
		message = format( "获得了#R现银#{_MONEY%d}", awardMoney)
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, message);
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
		Msg2Player(sceneId,selfId, message,4,2)

		SetQuestData(sceneId, selfId, MD_YUNYOU_DATE[1], MD_YUNYOU_DATE[2], MD_YUNYOU_DATE[3], GetDayOfYear())
		return 
	end

	SetQuestData(sceneId, selfId, MD_YUNYOU_DATE[1], MD_YUNYOU_DATE[2], MD_YUNYOU_DATE[3], GetDayOfYear())
	--给奖励 
	YUNYOU_COMMIT_NUM = YUNYOU_COMMIT_NUM + 1
	local experience = level*1680
	AddExp( sceneId, selfId, experience )

	message = format("#Y获得#R经验%d点#Y奖励。", experience)
	BeginQuestEvent(sceneId);
		AddQuestText(sceneId, message);
	EndQuestEvent();
	DispatchQuestTips(sceneId, selfId);
	Msg2Player(sceneId,selfId, message,4,2)

	if YUNYOU_COMMIT_NUM == 1 then
	
		AddExp( sceneId, selfId, level*1680*0.5 )
		
		message = format("#Y获得第%d名的#R额外经验%d点#Y奖励", YUNYOU_COMMIT_NUM, level*1680*0.5)
		BeginQuestEvent(sceneId);
			AddQuestText(sceneId, message);
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
		Msg2Player(sceneId,selfId, message,4,2)

		local name = GetName(sceneId, selfId)
		message = "恭喜"..name.."以最快的速度将货物取到并送出城门，前三十名完成任务的玩家将获得额外奖励！"
		LuaAllScenceM2Wrold( sceneId, message, CHAT_PLANE_SCROLL, 1 )
	elseif YUNYOU_COMMIT_NUM > 1 and YUNYOU_COMMIT_NUM <=30 then
		AddExp( sceneId, selfId, level*1680*0.5 )
		
		message = format("#Y获得第%d名的#R额外经验%d点#Y奖励", YUNYOU_COMMIT_NUM, level*1680*0.5)
		BeginQuestEvent(sceneId);
			AddQuestText(sceneId, message);
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
		Msg2Player(sceneId,selfId, message,4,2)
	end

	AddMoney( sceneId, selfId,0, awardMoney )
	message = format( "获得了#R现银#{_MONEY%d}", awardMoney)
	BeginQuestEvent(sceneId);
	AddQuestText(sceneId, message);
	EndQuestEvent();
	DispatchQuestTips(sceneId, selfId);
	Msg2Player(sceneId,selfId, message,4,2)

	return 
	
end


--********************************************************************
--放弃
--********************************************************************
function x310073_ProcQuestAbandon( sceneId, selfId,MissionId )

	if IsHaveQuestNM( sceneId, selfId, MissionId) == 0 then	-- 如果没有这个任务
		return
	end

	DelQuestNM( sceneId, selfId, MissionId)

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


function x310073_ProcQuestAttach( sceneId, selfId, npcId, npcGuid,misIndex, MissionId )
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
function x310073_ProcQuestLogRefresh( sceneId, selfId, MissionId)
	local bHaveMission = IsHaveQuestNM(sceneId, selfId,MissionId );
		if bHaveMission > 0 then
			local index = GetQuestData(sceneId, selfId, MD_YUNYOU_RAND[1], MD_YUNYOU_RAND[2], MD_YUNYOU_RAND[3])

			if x310073_g_SubMission[index].MissionId ~= MissionId then
				return
			end

			BeginQuestEvent(sceneId)			
		    AddQuestLogCustomText( sceneId,
									"",							-- 标题
									x310073_g_SubMission[index].MissionName,      -- 任务名字
									x310073_g_SubMission[index].MissionTarget,	--任务目标
									x310073_g_SubMission[index].NpcName,			--任务NPC
									"",      --任务攻略
									x310073_g_SubMission[index].MissionInfo,		--任务描述
									x310073_g_SubMission[index].MissionHelp							--任务小提示
									)
      AddQuestExpBonus(sceneId, GetLevel(sceneId, selfId)*1680)
	  AddQuestMoneyBonus2(sceneId, GetLevel(sceneId, selfId)*100 )
			EndQuestEvent(sceneId)
			DispatchQuestLogUpdate(sceneId, selfId, MissionId);
		end
end
