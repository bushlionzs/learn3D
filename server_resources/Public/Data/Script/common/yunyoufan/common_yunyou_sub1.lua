
x310072_g_SubMission			=	{ 
									{ MissionId=8081, 
										MissionName = "【个人】寿诞采办", 
										MissionTarget = "  把空马车护送到@npc_139109处", 
										MissionInfo = "\t我已经接到上谕，正等着你的到来。这是给你备下的马车，速去@npc_139109处接受贡品吧！",
										MissionHelp = "\t如果你在护送的过程中下线或者远离他超过5分钟，你的任务就会失败。请尽快完成吧，尽早完成的话朝廷会给你更多奖励的。", 
										NpcName="@npc_139109"
									}, 
									{ MissionId=8082, 
										MissionName = "【个人】寿诞采办", 
										MissionTarget = "  把空马车护送到@npc_139110处", 
										MissionInfo = "\t我已经接到上谕，正等着你的到来。这是给你备下的马车，速去@npc_139110处接受贡品吧！",
										MissionHelp = "\t如果你在护送的过程中下线或者远离他超过5分钟，你的任务就会失败。请尽快完成吧，尽早完成的话朝廷会给你更多奖励的。", 
										NpcName="@npc_139110"
									}, 
									{ MissionId=8083, 
										MissionName = "【个人】寿诞采办", 
										MissionTarget = "  把空马车护送到@npc_139111处", 
										MissionInfo = "\t我已经接到上谕，正等着你的到来。这是给你备下的马车，速去@npc_139111处接受贡品吧！",
										MissionHelp = "\t如果你在护送的过程中下线或者远离他超过5分钟，你的任务就会失败。请尽快完成吧，尽早完成的话朝廷会给你更多奖励的。", 
										NpcName="@npc_139111"
									}, 
									{ MissionId=8084, 
										MissionName = "【个人】寿诞采办", 
										MissionTarget = "  把空马车护送到@npc_139112处", 
										MissionInfo = "\t我已经接到上谕，正等着你的到来。这是给你备下的马车，速去@npc_139112处接受贡品吧！",
										MissionHelp = "\t如果你在护送的过程中下线或者远离他超过5分钟，你的任务就会失败。请尽快完成吧，尽早完成的话朝廷会给你更多奖励的。", 
										NpcName="@npc_139112"
									}, 
									{ MissionId=8085, 
										MissionName = "【个人】寿诞采办", 
										MissionTarget = "  把空马车护送到@npc_139113处", 
										MissionInfo = "\t我已经接到上谕，正等着你的到来。这是给你备下的马车，速去@npc_139113处接受贡品吧！",
										MissionHelp = "\t如果你在护送的过程中下线或者远离他超过5分钟，你的任务就会失败。请尽快完成吧，尽早完成的话朝廷会给你更多奖励的。", 
										NpcName="@npc_139113"
									}
								}


 
x310072_g_BusScriptId = 310071

x310072_g_ScriptId = 310072
x310072_g_BusId = { 21,22,23,24,25 }

function x310072_PushAfterMission(sceneId, selfId , target, level, index)

	local isFull = IsQuestFullNM( sceneId, selfId )

	if isFull > 0 then	
		local strText = "任务已满，添加任务失败"
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, strText);
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
		return
	end
	
	local busObjId = CallScriptFunction( x310072_g_BusScriptId, "OnCreateBus", sceneId, selfId ,x310072_g_SubMission[index].MissionId, x310072_g_BusId[index])
end

function x310072_OnCreateBusOK(sceneId, selfId, busObjId,targetId,MissionId,index)

	if busObjId < 0 then
		local strText = "无法创建镖车，添加任务失败"
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, strText);
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
		return
	end
	
	--检查前置任务
	local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId, x310072_g_SubMission[index].MissionId )
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

	local ret = AddQuestNM( sceneId, selfId, x310072_g_SubMission[index].MissionId ) -- 给玩家添加任务

	if ret <0 then
		if (IsObjValid (sceneId,busObjId) ~= 1) or GetBusQuestID(sceneId, busObjId) ~= x310072_g_SubMission[index].MissionId then
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

	GamePlayScriptLog(sceneId, selfId, 371)

	SetQuestParam( sceneId, selfId, x310072_g_SubMission[index].MissionId, 7, 1 )

	local misIndex = GetQuestIndexByID( sceneId, selfId, x310072_g_SubMission[index].MissionId )	
	SetQuestByIndex( sceneId, selfId, misIndex, 1, GetLevel(sceneId, selfId) )

	BeginQuestEvent( sceneId);
		--任务信息
		AddQuestText(sceneId, "#Y"..(x310072_g_SubMission[index].MissionName));
		AddQuestText(sceneId, x310072_g_SubMission[index].MissionInfo)

		--任务目标
		AddQuestText( sceneId, "#Y任务目标：")
		AddQuestText( sceneId, x310072_g_SubMission[index].MissionTarget)
		--提示信息
		if x310072_g_SubMission[index].MissionHelp ~= "" then
			AddQuestText(sceneId, "#Y任务提示：")
			AddQuestText(sceneId, x310072_g_SubMission[index].MissionHelp )
		end

	
		--获取经验
		local experience = level*1680
		AddQuestExpBonus( sceneId, experience);
		--AddQuestItemBonus(sceneId, 12110204, 1)
		AddQuestMoneyBonus2(sceneId, level*100 )

	EndQuestEvent(sceneId);
	DispatchQuestInfoNM(sceneId, selfId, target, x310072_g_ScriptId, x310072_g_SubMission[index].MissionId, 1);

end

function x310072_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
  	
end


--点击（按钮）点击该任务后执行此脚本
function x310072_ProcEventEntry( sceneId, selfId, targetId, MissionId )
	
	if IsHaveQuestNM( sceneId, selfId, MissionId ) > 0 then	-- 如果没有这个任务
		
			local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )
			if QuestCheckSubmitNM( sceneId, selfId, targetId, MissionId, misIndex ) > 0 then 	-- 如果任务可以完成
				--QuestComplateInfoNM( sceneId, selfId, targetId, MissionId ) 					-- 显示完成信息
				x310072_ProcQuestSubmit( sceneId, selfId, targetId, -1, MissionId )
			else
				QuestNotComplateInfoNM( sceneId, selfId, targetId, MissionId ) 				-- 显示任务未完成信息
			end

	end
		  
end


--**********************************
--接受
--**********************************
function x310072_ProcQuestAccept( sceneId, selfId, targetId, MissionId )
	
end


--**********************************
--接受
--**********************************
function x310072_ProcAccept( sceneId, selfId )
	
end

--完成任务
--返回1代表成功，0代表交任务失败
function x310072_ProcQuestSubmit( sceneId, selfId, targetId, selectId, MissionId )

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

	local Readme = "恭喜您完成护送马车任务"
	BeginQuestEvent(sceneId)
	AddQuestText(sceneId, Readme);
	EndQuestEvent(sceneId)
	DispatchQuestTips(sceneId,selfId)
	Msg2Player(sceneId,selfId,Readme,8,2)

	DelQuest( sceneId, selfId, MissionId)
	GamePlayScriptLog(sceneId, selfId, 372)
	
	local BusID  =  GetBusId(sceneId, selfId)
	if BusID ~= -1 then
		--如果BUS还活着
		DeleteBus(sceneId, BusID,1)
	end 
	
	CallScriptFunction( 310073, "PushAfterMission", sceneId, selfId ,targetId, level, index)  
	
	return 0
	
end


--********************************************************************
--放弃
--********************************************************************
function x310072_ProcQuestAbandon( sceneId, selfId,MissionId )

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


function x310072_ProcQuestAttach( sceneId, selfId, npcId, npcGuid,misIndex, MissionId )
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
function x310072_ProcQuestLogRefresh( sceneId, selfId, MissionId)
	local bHaveMission = IsHaveQuestNM(sceneId, selfId,MissionId );
		if bHaveMission > 0 then
			local index = GetQuestData(sceneId, selfId, MD_YUNYOU_RAND[1], MD_YUNYOU_RAND[2], MD_YUNYOU_RAND[3])

			if x310072_g_SubMission[index].MissionId ~= MissionId then
				return
			end

			BeginQuestEvent(sceneId)			
		    AddQuestLogCustomText( sceneId,
									"",							-- 标题
									x310072_g_SubMission[index].MissionName,      -- 任务名字
									x310072_g_SubMission[index].MissionTarget,	--任务目标
									x310072_g_SubMission[index].NpcName,			--任务NPC
									"",      --任务攻略
									x310072_g_SubMission[index].MissionInfo,		--任务描述
									x310072_g_SubMission[index].MissionHelp							--任务小提示
									)
      AddQuestExpBonus(sceneId, GetLevel(sceneId, selfId)*1680)
     -- AddQuestItemBonus(sceneId, 12110204, 1)
	  AddQuestMoneyBonus2(sceneId, GetLevel(sceneId, selfId)*100 )
			EndQuestEvent(sceneId)
			DispatchQuestLogUpdate(sceneId, selfId, MissionId);
		end
end
