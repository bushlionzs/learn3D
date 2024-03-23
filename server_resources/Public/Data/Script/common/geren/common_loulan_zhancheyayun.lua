--MisDescBegin

x300761_g_ScriptId 	  = 300761
x300761_g_MissionKind 				= 	1                       --任务类型
x300761_g_Mis_Count   = 3--每天可做的次数
x300761_g_MissionId = 7031

-- 任务提示
x300761_g_ExtTarget					=	{ {type=20,n=1,target="战车"} }

x300761_g_ContinueInfo				= 	"\t如果不清除这些阿兰人，送往中国的贡品就不会按时完成。"
x300761_g_MissionCompleted			= 	"\t您已经将战车安全护送到此！请收下您应得的奖励！"

x300761_g_MissionName = "【个人】战车护送"
x300761_g_LevelLess = 70

x300761_g_BusScriptId = 300763

x300761_g_MissionTarget = "  将战车交给@npc_123829"
x300761_g_MissionInfo = "\t你知道#G屠城战#W吗？我们正为它的到来而#G备战#W，我急需一批勇士将战车护送到#G楼兰外城#W，交给#G阿鲁图#W，在你将战车成功护送给他之后，会获得#G高额#W的#G经验#W奖励。\n\t每人每天只可护送#G三次#W战车，随着护送#G次数#W的#G增加#W，获得的#G经验#W也会越来越多，当然，#G花费#W的现银也会#G更多#W。本次护送，你需花费#R%d两#W现银。"
x300761_g_MissionHelp = "\t#G护送途中如果你离开战车过远，战车会因无人引导而停止前进！\n\t#G如果战车受到袭击被摧毁，任务失败！#G如果你离开战车超过5分钟，战车将丢失，任务失败！#G领取战车后，所花费的现银不会返还，#R国运期间#G只会增加国家实力榜积分，#R不会获得#G双倍奖励！"
x300761_g_SubmitNPCGUID = 123829
x300761_g_NPCName = "@npc_123829"
x300761_g_Missionruse="将战车送到楼兰外城的@npc_123829处！"

--MisDescEnd
							

function x300761_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

	local level = GetLevel(sceneId,selfId)
	
	if level < x300761_g_LevelLess then
		return
	end

	local bHaveMission = IsHaveQuestNM(sceneId, selfId, x300761_g_MissionId )
	local npcGuid = GetMonsterGUID(sceneId,targetId)
	if bHaveMission <= 0 then
		if x300761_g_SubmitNPCGUID ~= npcGuid then
			local state = GetQuestStateNM(sceneId,selfId,targetId,x300761_g_MissionId)
			AddQuestNumText(sceneId,x300761_g_MissionId,x300761_g_MissionName,state,0);
		end
	end

end

--点击（按钮）点击该任务后执行此脚本
function x300761_ProcEventEntry( sceneId, selfId, targetId, MissionId,nExtIdx )

	local bHaveMission	= IsHaveQuestNM(sceneId, selfId, x300761_g_MissionId)
	local npcGuid = GetMonsterGUID(sceneId,targetId)
	
	if x300761_g_SubmitNPCGUID ~= npcGuid then
	--接任务
		if(bHaveMission > 0) then
			local bDone = x300761_CheckSubmit(sceneId, selfId, targetId);
			if(bDone > 0) then
				if nExtIdx ~= -1 then
					x300761_DispatchCompletedInfo( sceneId, selfId, targetId,0) --完成任务显示
				end
			else
				if nExtIdx ~= -1 then
					x300761_DispatchContinueInfo( sceneId, selfId, targetId,0 ) --未完成任务显示
				end
			end
		else
			if x300761_g_SubmitNPCGUID ~= npcGuid then
				x300761_DispatchMissionInfo( sceneId, selfId, targetId,0 )	--任务信息显示
			else
				

				--任务继续信息
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"你没有此任务！")
				EndQuestEvent()
				DispatchQuestEventList(sceneId,selfId,targetId);
			end
		end
	else
	--交任务
		if(bHaveMission > 0) then
			x300761_DispatchCompletedInfo( sceneId, selfId, targetId,0) --完成任务显示
		-- else
		-- 任务继续信息
			-- BeginQuestEvent(sceneId)
			-- AddQuestText(sceneId,"你没有此任务！")
			-- EndQuestEvent()
			-- DispatchQuestEventList(sceneId,selfId,targetId);
		end
	end
	
end

--显示任务信息
function x300761_DispatchMissionInfo( sceneId, selfId, NPCId,index )
	BeginQuestEvent( sceneId);
		--任务信息
		AddQuestText(sceneId, "#Y"..x300761_g_MissionName);
		AddQuestText(sceneId, format(x300761_g_MissionInfo,x300761_CalcCostMoney(sceneId, selfId)/1000) )
		--任务目标
		AddQuestText( sceneId, "#Y任务目标：")
		AddQuestText( sceneId, x300761_g_MissionTarget)
		AddQuestText( sceneId, " ")
		--提示信息
		if x300761_g_MissionHelp ~= "" then
			AddQuestText(sceneId, "#Y任务提示：")
			AddQuestText(sceneId, x300761_g_MissionHelp )
		end
		
		--奖励信息
		--1、经验
		local experience = x300761_CalcExperience(sceneId, selfId)
		if experience > 0 then
			AddQuestExpBonus( sceneId, experience)
		end

	EndQuestEvent(sceneId);

	DispatchQuestInfoNM(sceneId, selfId, NPCId, x300761_g_ScriptId,  x300761_g_MissionId);
end


---------------------------------------------------------------------------------------------------
--向客户端发送任务未完成
---------------------------------------------------------------------------------------------------
function x300761_DispatchContinueInfo( sceneId, selfId, NPCId,index )
	
	BeginQuestEvent(sceneId)

		--任务继续信息
		AddQuestText(sceneId,"#Y"..x300761_g_MissionName)
		local info = format(x300761_g_MissionInfo,x300761_CalcCostMoney(sceneId, selfId)/1000)
		AddQuestText(sceneId,format("%s", info))
		AddQuestText(sceneId," ")

		--任务目标
		AddQuestText( sceneId,"#Y完成情况：")
		AddQuestText(sceneId, "未完成");

  		--任务奖励信息

		--1、经验
		local experience = x300761_CalcExperience(sceneId, selfId)
		if experience > 0 then
			AddQuestExpBonus( sceneId, experience)
		end

	EndQuestEvent()
	DispatchQuestDemandInfo(sceneId, selfId, NPCId, x300761_g_ScriptId, x300761_g_MissionId,0);

end


---------------------------------------------------------------------------------------------------
--向客户端发送任务完成信息
---------------------------------------------------------------------------------------------------
function x300761_DispatchCompletedInfo( sceneId, selfId, targetId,index )
	
	BeginQuestEvent(sceneId)

		--任务完成信息
		AddQuestText(sceneId,"#Y"..x300761_g_MissionName)
		AddQuestText(sceneId,x300761_g_MissionCompleted)
		AddQuestText(sceneId," ")

		--1、经验
		local experience = x300761_CalcExperience(sceneId, selfId)
		if experience > 0 then
			AddQuestExpBonus( sceneId, experience)
		end
			
	EndQuestEvent(sceneId)
	DispatchQuestContinueInfoNM(sceneId, selfId, targetId, x300761_g_ScriptId , x300761_g_MissionId);

end

--**********************************
--接受
--**********************************
function x300761_ProcQuestAccept( sceneId, selfId, targetId, MissionId )
	if IsHideName(sceneId, selfId) > 0 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"抱歉，蒙面状态不能接此任务。")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return 0
	end
	
	if IsQuestFullNM( sceneId, selfId )==1 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"可接任务数量已满")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return 0
	end

	local level = GetLevel(sceneId, selfId)
	if level < x300761_g_LevelLess then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "您的等级不能领取此任务！");
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		local Readme = "您的等级不能领取此任务！" 
		Msg2Player(sceneId,selfId,Readme,8,2)
		return 0
	end
	
	if GetMoney(sceneId, selfId,0) < x300761_CalcCostMoney(sceneId, selfId) then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "您身上的现银不足，不能领取战车！");
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		local Readme = "您身上的现银不足，不能领取战车！"
		Msg2Player(sceneId,selfId,Readme,8,2)
		return 0;		
	end

	if IsTeamFollow(sceneId, selfId) == 1 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "组队跟随状态下不可以接护送任务");
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		local Readme = "组队跟随状态下不可以接护送任务！"
		Msg2Player(sceneId,selfId,Readme,8,2)
		return 0
	end
	
	if IsBusMember(sceneId,selfId) == 1 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "您已处于护送/押运状态，无法领取新的押运任务！");
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		local Readme = "您已处于护送/押运状态，无法领取新的押运任务！" 
		Msg2Player(sceneId,selfId,Readme,8,2)
		return 0
	end

	if x300761_GetDayCount(sceneId, selfId) >= x300761_g_Mis_Count then
		local Readme = "很抱歉，您今天任务次数已满，请明天再来做吧！" 
	  	BeginQuestEvent(sceneId)
		AddQuestText(sceneId,Readme );
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,Readme,8,2)
		return 0
	end
		
	local bHaveMission	= IsHaveQuestNM(sceneId, selfId, x300761_g_MissionId);
	if(bHaveMission > 0) then
		return 0;
	end
	--接任务日志
	--GamePlayScriptLog(sceneId,selfId,1421)
	local count = x300761_GetDayCount(sceneId, selfId)
	CallScriptFunction( x300761_g_BusScriptId, "OnCreateBus", sceneId, selfId ,x300761_g_MissionId,count+1)

end

---------------------------------------------------------------------------------------------------
--检查任务是否可提交
---------------------------------------------------------------------------------------------------
function x300761_CheckSubmit(sceneId, selfId, targetId)
	
	local npcGuid = GetMonsterGUID(sceneId,targetId)

	if x300761_g_SubmitNPCGUID ~= npcGuid then
		return 0
	end

	return 1;

end

--**********************************
--接受
--**********************************
function x300761_ProcAccept( sceneId, selfId )
	
end

--完成任务
--返回1代表成功，0代表交任务失败
function x300761_ProcQuestSubmit( sceneId, selfId, targetId, selectId, MissionId )

	if IsQuestHaveDoneNM( sceneId, selfId, MissionId ) > 0 then --任务已经完成
		return 0
	end

	if IsHaveQuestNM( sceneId, selfId, MissionId) <= 0 then	-- 如果没这个任务直接退出
		return 0
	end

	--镖车是否在有效距离
	local valid = IsValidMyselfBus(sceneId, selfId,MissionId)

	if valid == 0 then
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "您护送的战车离您太远了，无法提交任务！");
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		local Readme = "您护送的战车离您太远了，无法提交任务！"
		Msg2Player(sceneId,selfId,Readme,8,2)
		return 0
	end
   
	--给奖励
	local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId)
	local ret = DelQuest( sceneId, selfId, MissionId) 
	if ret == 1 then -- 如果成功完成

		--交任务写日志
		GamePlayScriptLog(sceneId,selfId,1422)
		AddCountryStrength(sceneId, selfId, 1)	
		
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, "恭喜，您为国家实力榜贡献了#R1个#O积分。");
		EndQuestEvent(sceneId);
		DispatchQuestTips(sceneId,selfId);
		Msg2Player(sceneId,selfId,"恭喜，您为国家实力榜贡献了#R1个#O积分。",8,2)	
		
		local experience = x300761_CalcExperience(sceneId, selfId)
		if experience > 0 then
			AddExp(sceneId, selfId,experience)
			local exp1 = x300761_CalcExperience(sceneId, selfId)
			local Readme = "您完成了任务：【个人】战车护送#r获得#R经验"..exp1.."点#o的奖励"
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, "您完成了任务：【个人】战车护送");
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, "获得#R经验"..exp1.."点#o的奖励");
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
			Msg2Player(sceneId,selfId,Readme,8,2)
			CallScriptFunction( 256223, "FinishYayun", sceneId, selfId)
		end
		        
		x300761_SetDayCount(sceneId, selfId)
		
		local BusID  =  GetBusId(sceneId, selfId)
		if BusID ~= -1 and IsObjValid (sceneId,BusID) == 1 then
			--如果BUS还活着
			if GetBusQuestID(sceneId, BusID) == MissionId then
				DeleteBus(sceneId, BusID,1)
			end
		end 
		x300761_GuoYun(sceneId, selfId, MissionId)
	end

	return 0
end


--********************************************************************
--放弃
--********************************************************************
function x300761_ProcQuestAbandon( sceneId, selfId,MissionId )

	local bHaveMission = IsHaveQuestNM(sceneId, selfId,x300761_g_MissionId );
	if bHaveMission > 0 then

		if IsBusMember(sceneId, selfId) == 1 then
			local BusID  =  GetBusId(sceneId, selfId)
			if BusID ~= -1 and IsObjValid (sceneId,BusID) == 1 then
				--如果BUS还活着
				if GetBusQuestID(sceneId, BusID) == x300761_g_MissionId then
					DeleteBus(sceneId, BusID,1)
				end
			else
				local Readme = "很抱歉，您与您的护送目标在同一场景才能放弃任务，请先找到您的护送目标再选择放弃！"
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId, "现在不能放弃任务！");
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				Msg2Player(sceneId,selfId,Readme,8,2)
				return
			end				
		end

		local misIndex = GetQuestIndexByID(sceneId, selfId, x300761_g_MissionId); 
		DelQuest(sceneId, selfId, x300761_g_MissionId);
						
		--放弃任务写日志
		GamePlayScriptLog(sceneId,selfId,1424)

		local Readme = "您放弃了任务：【个人】战车护送"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, Readme);
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,Readme,8,2)

		x300761_SetDayCount(sceneId, selfId)
	end

end


function x300761_ProcQuestAttach( sceneId, selfId, npcId, npcGuid,misIndex, MissionId )
	
	local bHaveMission = IsHaveQuestNM(sceneId, selfId,x300761_g_MissionId )

	if bHaveMission > 0 then
		if npcGuid == x300761_g_SubmitNPCGUID then
			local state = GetQuestStateNM(sceneId,selfId,npcId,x300761_g_MissionId)
			AddQuestNumText(sceneId, x300761_g_MissionId, x300761_g_MissionName,7,0);
		end
	end

end

---------------------------------------------------------------------------------------------------
--任务日志刷新
---------------------------------------------------------------------------------------------------
function x300761_QuestLogRefresh( sceneId, selfId, MissionId)

	local bHaveMission = IsHaveQuestNM(sceneId, selfId,x300761_g_MissionId );
	if bHaveMission > 0 then
	
		BeginQuestEvent(sceneId)
		
		local experience = x300761_CalcExperience(sceneId, selfId)
		if experience > 0 then
			AddQuestExpBonus( sceneId, experience)
		end

		AddQuestLogCustomText( sceneId,
								"",						-- 标题
								x300761_g_MissionName,        -- 任务名字
								x300761_g_MissionTarget,		--任务目标
								x300761_g_NPCName,			--任务NPC
								x300761_g_Missionruse,               --任务攻略
								format(x300761_g_MissionInfo,x300761_CalcCostMoney(sceneId, selfId)/1000),	--任务描述
								""					--任务小提示
								)
		EndQuestEvent(sceneId)
		DispatchQuestLogUpdate(sceneId, selfId, x300761_g_MissionId);
	end

end

function x300761_ProcQuestLogRefresh( sceneId, selfId, MissionId)
	x300761_QuestLogRefresh( sceneId, selfId, MissionId );
end

---------------------------------------------------------------------------------------------------
--取得此任务当天当前已完成次数
---------------------------------------------------------------------------------------------------
function x300761_GetDayCount(sceneId, selfId)

	if x300761_g_Mis_Count > 0 then

		local today = GetDayOfYear()

		local lastday = GetQuestData(sceneId, selfId, MD_ZHANCHEYAYUN_DATE[1], MD_ZHANCHEYAYUN_DATE[2], MD_ZHANCHEYAYUN_DATE[3])

		if lastday ~= today then
			return 0
		end

		local daycount =  GetQuestData(sceneId, selfId, MD_ZHANCHEYAYUN_COUNT[1], MD_ZHANCHEYAYUN_COUNT[2], MD_ZHANCHEYAYUN_COUNT[3])
		return daycount

	end

	return 0
end

---------------------------------------------------------------------------------------------------
--更新当天接任务次数
---------------------------------------------------------------------------------------------------
function x300761_SetDayCount(sceneId, selfId)
	local today = GetDayOfYear()

	local lastday = GetQuestData(sceneId, selfId, MD_ZHANCHEYAYUN_DATE[1], MD_ZHANCHEYAYUN_DATE[2], MD_ZHANCHEYAYUN_DATE[3])

	if lastday ~= today then
		SetQuestData(sceneId, selfId, MD_ZHANCHEYAYUN_DATE[1], MD_ZHANCHEYAYUN_DATE[2], MD_ZHANCHEYAYUN_DATE[3], today)
		SetQuestData(sceneId, selfId, MD_ZHANCHEYAYUN_COUNT[1], MD_ZHANCHEYAYUN_COUNT[2], MD_ZHANCHEYAYUN_COUNT[3], 1)
	else
		local daycount = GetQuestData(sceneId, selfId, MD_ZHANCHEYAYUN_COUNT[1], MD_ZHANCHEYAYUN_COUNT[2], MD_ZHANCHEYAYUN_COUNT[3])
		SetQuestData(sceneId, selfId, MD_ZHANCHEYAYUN_COUNT[1], MD_ZHANCHEYAYUN_COUNT[2], MD_ZHANCHEYAYUN_COUNT[3], daycount+1)
	end
end

--计算花多少钱
function x300761_CalcCostMoney(sceneId, selfId)
	local count = x300761_GetDayCount(sceneId, selfId)
	if count == 0 then
		return 75000
	elseif count == 1 then
		return 150000
	elseif count == 2 then
		return 225000
	end
	return 0
end

--计算得多少经验
function x300761_CalcExperience(sceneId, selfId)
	local count = x300761_GetDayCount(sceneId, selfId)
	local level = GetLevel(sceneId,selfId)
	if count == 0 then
		if level < 80 then
			zhancheexp = level*30000
		elseif level >=80 and level < 90 then
			zhancheexp = level*30000*2
		elseif level >=90 and level <200 then
			zhancheexp = level*30000*2.6
		end
		return zhancheexp
	elseif count == 1 then
		if level < 80 then
			zhancheexp = level*60000
		elseif level >=80 and level < 90 then
			zhancheexp = level*60000*2
		elseif level >=90 and level <200 then
			zhancheexp = level*60000*2.6
		end
		return zhancheexp
	elseif count == 2 then
		if level < 80 then
			zhancheexp = level*100000
		elseif level >=80 and level < 90 then
			zhancheexp = level*100000*2
		elseif level >=90 and level <200 then
			zhancheexp = level*100000*2.6
		end
		return zhancheexp
	end
	return 0
end

function x300761_GuoYun(sceneId, selfId, MissionId)
	if CountryIsFortuneTime(sceneId, selfId, 0) > 0 then
		local country = GetCurCountry(sceneId, selfId)
		SetCountryQuestData(sceneId, country, CD_INDEX_GUOYUN_COUNT, 1, 1 )
	end
end
