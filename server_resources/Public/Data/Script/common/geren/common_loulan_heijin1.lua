--MisDescBegin

x300759_g_ScriptId 	  = 300759
x300759_g_MissionKind 				= 	1                       --任务类型
x300759_g_Mis_Count   = 3--每天可做的次数
x300759_g_MissionId = 7001;
x300759_g_LevelLess	=	30
x300759_g_MissionKind 				= 	1                        --任务类型
-- NPC默认对话
x300759_g_NPCDialog = "\t我是官府任命的矿主，负责将这里产出的黄金发往王国各地。但是现在世道太乱，敌对势力经常通过武力抢夺我们的黄金，我看兄台气宇不凡，能否帮助我运送黄金？"
-- 任务信息
x300759_g_ContinueInfo				= 	"\t如果不清除这些阿兰人，送往中国的贡品就不会按时完成。"
x300759_g_MissionCompleted			= 	"\t您已经将官府交给您的马车安全护送到此了？请收下官府给您的奖励！"

-- 任务提示
x300759_g_ExtTarget					=	{ {type=20,n=1,target="马车"} }
--MisDescEnd

x300759_g_BusScriptId = 300623

--子任务																	   
x300759_g_SubMissionID = {	  { MissionId=7001, MissionName = "【个人】官府押运", MissionTarget = "  将马车交给@npc_123829", MissionInfo = "\t您可以通过王国押运官并花费#G1两现银（银卡）#W就可以领取一辆#G马车#W，当您将马车安全护送到指定地点，系统将会给与您#G海量经验#W。\n",MissionHelp = "\t#G护送途中如果您离开马车过远，马车会意识到危险而停止前进。\n\t#G如果马车受到袭击并死亡，您的任务将失败，同时押金将被抢走。\n\t#G当您离开马车一段时间或掉线，马车将消失，此时任务失败。\n\t如果您身上同时拥有#G银卡和现银，则优先扣除银卡。", SubmitNPCGUID = 123829, iCostMoney =1000, coef1 = 100,coef2 = 2.5,coef3 = 20,coef4 =1,coef5 =2,NPCName = "@npc_123829",Missionruse="将马车送到楼兰外城的@npc_123829处！",AcceptId = 51,SubmitId = 52,LevelLess = 30,LevelMax = 40 }, 
							  {	MissionId=7009, MissionName = "【个人】官府押运", MissionTarget = "  将马车交给@npc_125513", MissionInfo = "\t您可以通过王国押运官并花费#G2两现银（银卡）#W就可以领取一匹#G马车#W，当您将马车安全护送到指定地点，系统将会给与您#G海量经验#W。\n",MissionHelp = "\t#G护送途中如果您离开马车过远，马车会意识到危险而停止前进。\n\t#G如果马车受到袭击并死亡，您的任务将失败，同时押金将被抢走。\n\t#G当您离开马车一段时间或掉线，马车将消失，此时任务失败。\n\t如果您身上同时拥有#G银卡和现银，则优先扣除银卡。", SubmitNPCGUID = 125513, iCostMoney = 2000, coef1 = 100,coef2 = 2.5,coef3 = 20,coef4 =1,coef5 =2,NPCName = "@npc_125513",Missionruse="将马车送到楼兰古道的@npc_125513处！",AcceptId = 61,SubmitId = 62,LevelLess = 40,LevelMax = 50 },
							  {	MissionId=7010, MissionName = "【个人】官府押运", MissionTarget = "  将马车交给@npc_125512", MissionInfo = "\t您可以通过王国押运官并花费#G3两现银（银卡）#W就可以领取一辆#G马车#W，当您将马车安全护送到指定地点，系统将会给与您#G海量经验#W。\n",MissionHelp = "\t#G护送途中如果您离开马车过远，马车会意识到危险而停止前进。\n\t#G如果马车受到袭击并死亡，您的任务将失败，同时押金将被抢走。\n\t#G当您离开马车一段时间或掉线，马车将消失，此时任务失败。\n\t如果您身上同时拥有#G银卡和现银，则优先扣除银卡。",SubmitNPCGUID = 125512, iCostMoney = 3000,coef1 = 100,coef2 = 2.5,coef3 = 20,coef4 =1,coef5 =2,NPCName = "@npc_125512",Missionruse="将马车送到边塞的@npc_125512处！",AcceptId = 71,SubmitId = 72,LevelLess = 50,LevelMax = 60 },
							  {	MissionId=7543, MissionName = "【个人】官府押运", MissionTarget = "  将马车交给@npc_125512", MissionInfo = "\t您可以通过王国押运官并花费#G5两现银（银卡）#W就可以领取一辆#G马车#W，当您将马车安全护送到指定地点，系统将会给与您#G海量经验#W。\n",MissionHelp = "\t#G护送途中如果您离开马车过远，马车会意识到危险而停止前进。\n\t#G如果马车受到袭击并死亡，您的任务将失败，同时押金将被抢走。\n\t#G当您离开马车一段时间或掉线，马车将消失，此时任务失败。\n\t如果您身上同时拥有#G银卡和现银，则优先扣除银卡。",SubmitNPCGUID = 125512, iCostMoney = 5000,coef1 = 100,coef2 = 2.5,coef3 = 20,coef4 =1,coef5 =2,NPCName = "@npc_125512",Missionruse="将马车送到边塞的@npc_125512处！",AcceptId = 81,SubmitId = 82,LevelLess = 60,LevelMax = 70 },
							  { MissionId=7544, MissionName = "【个人】官府押运", MissionTarget = "  将马车交给@npc_125512", MissionInfo = "\t您可以通过王国押运官并花费#G6两现银（银卡）#W就可以领取一辆#G马车#W，当您将马车安全护送到指定地点，系统将会给与您#G海量经验#W。\n",MissionHelp = "\t#G护送途中如果您离开马车过远，马车会意识到危险而停止前进。\n\t#G如果马车受到袭击并死亡，您的任务将失败，同时押金将被抢走。\n\t#G当您离开马车一段时间或掉线，马车将消失，此时任务失败。\n\t如果您身上同时拥有#G银卡和现银，则优先扣除银卡。",SubmitNPCGUID = 125512, iCostMoney = 6000,coef1 = 100,coef2 = 2.5,coef3 = 20,coef4 =1,coef5 =2,NPCName = "@npc_125512",Missionruse="将马车送到边塞的@npc_125512处！",AcceptId = 741,SubmitId = 742,LevelLess = 70,LevelMax = 80 },
							  { MissionId=7545, MissionName = "【个人】官府押运", MissionTarget = "  将马车交给@npc_125512", MissionInfo = "\t您可以通过王国押运官并花费#G7两500文现银（银卡）#W就可以领取一辆#G马车#W，当您将马车安全护送到指定地点，系统将会给与您#G海量经验#W。\n",MissionHelp = "\t#G护送途中如果您离开马车过远，马车会意识到危险而停止前进。\n\t#G如果马车受到袭击并死亡，您的任务将失败，同时押金将被抢走。\n\t#G当您离开马车一段时间或掉线，马车将消失，此时任务失败\n\t如果您身上同时拥有#G银卡和现银，则优先扣除银卡。",SubmitNPCGUID = 125512, iCostMoney = 7500,coef1 = 100,coef2 = 2.5,coef3 = 20,coef4 =1,coef5 =2,NPCName = "@npc_125512",Missionruse="将马车送到边塞的@npc_125512处！",AcceptId = 751,SubmitId = 752,LevelLess = 80,LevelMax = 150 },
						}


function x300759_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
end


--点击（按钮）点击该任务后执行此脚本
function x300759_ProcEventEntry( sceneId, selfId, targetId, MissionId,nExtIdx )
	
	local index = 1
	for i,itm in x300759_g_SubMissionID do
		if i == nExtIdx then
			MissionId = itm.MissionId
			index = i
			break
		end
	end

	local bHaveMission	= IsHaveQuestNM(sceneId, selfId, MissionId);
	if(bHaveMission > 0) then
		local bDone = x300759_CheckSubmit(sceneId, selfId, targetId,index);
		if(bDone > 0) then
			if nExtIdx ~= -1 then
				x300759_DispatchCompletedInfo( sceneId, selfId, targetId,index) --完成任务显示
			end
		else
			if nExtIdx ~= -1 then
				x300759_DispatchContinueInfo( sceneId, selfId, targetId,index ) --未完成任务显示
			end
		end
	else
		local npcGuid = GetMonsterGUID(sceneId,targetId)
		if x300759_g_SubMissionID[index].SubmitNPCGUID ~= npcGuid then
			x300759_DispatchMissionInfo( sceneId, selfId, targetId,index )	--任务信息显示
		else
			BeginQuestEvent(sceneId)

			--任务继续信息
			AddQuestText(sceneId,"你没有此任务！")
			EndQuestEvent()
			DispatchQuestEventList(sceneId,selfId,targetId);
		end
	end
		  
end


--显示任务信息
function x300759_DispatchMissionInfo( sceneId, selfId, NPCId,index )
	BeginQuestEvent( sceneId);
		--任务信息
		AddQuestText(sceneId, "#Y"..x300759_g_SubMissionID[index].MissionName);
		AddQuestText(sceneId, x300759_g_SubMissionID[index].MissionInfo)
		--任务目标
		AddQuestText( sceneId, "#Y任务目标：")
		AddQuestText( sceneId, x300759_g_SubMissionID[index].MissionTarget)
		AddQuestText( sceneId, " ")
		--提示信息
		if x300759_g_SubMissionID[index].MissionHelp ~= "" then
			AddQuestText(sceneId, "#Y任务提示：")
			AddQuestText(sceneId, x300759_g_SubMissionID[index].MissionHelp )
		end
		
		--奖励信息
		--1、经验
		local level = GetLevel( sceneId, selfId);
		local experience = x300759_g_SubMissionID[index].coef1 * x300759_g_SubMissionID[index].coef2 * level * x300759_g_SubMissionID[index].coef3;
		if level >= 70 then
			experience = level*9000
		end
		AddQuestExpBonus( sceneId, experience);

	EndQuestEvent(sceneId);

	DispatchQuestInfoNM(sceneId, selfId, NPCId, x300759_g_ScriptId,  x300759_g_SubMissionID[index].MissionId);
end


---------------------------------------------------------------------------------------------------
--向客户端发送任务未完成
---------------------------------------------------------------------------------------------------
function x300759_DispatchContinueInfo( sceneId, selfId, NPCId,index )
	
	BeginQuestEvent(sceneId)

		--任务继续信息
		AddQuestText(sceneId,"#Y"..x300759_g_SubMissionID[index].MissionName)
		AddQuestText(sceneId,format("%s", x300759_g_SubMissionID[index].MissionInfo))
		AddQuestText(sceneId," ")

		--任务目标
		AddQuestText( sceneId,"#Y完成情况：")
		AddQuestText(sceneId, "未完成");

  		--任务奖励信息

		--1、经验
		local level = GetLevel( sceneId, selfId);
		local experience = x300759_g_SubMissionID[index].coef1 * x300759_g_SubMissionID[index].coef2 * level * x300759_g_SubMissionID[index].coef3;
		if level >= 70 then
			experience = level*9000
		end
		AddQuestExpBonus( sceneId, experience);

	EndQuestEvent()
	DispatchQuestDemandInfo(sceneId, selfId, NPCId, x300759_g_ScriptId, x300759_g_SubMissionID[index].MissionId,0);

end


---------------------------------------------------------------------------------------------------
--向客户端发送任务完成信息
---------------------------------------------------------------------------------------------------
function x300759_DispatchCompletedInfo( sceneId, selfId, targetId,index )
	
	BeginQuestEvent(sceneId)

	--任务完成信息
	AddQuestText(sceneId,"#Y"..x300759_g_SubMissionID[index].MissionName)
	AddQuestText(sceneId,x300759_g_MissionCompleted)
	AddQuestText(sceneId," ")

	--1、经验
	local level = GetLevel(sceneId, selfId)
	local ExpBonus = ceil ( (x300759_g_SubMissionID[index].coef1 * x300759_g_SubMissionID[index].coef2 * level * x300759_g_SubMissionID[index].coef3 ) )
	if level >= 70 then
		ExpBonus = level*9000
	end
	if ExpBonus> 0 then
		AddQuestExpBonus(sceneId, ExpBonus )
	end
			
	EndQuestEvent(sceneId)
	DispatchQuestContinueInfoNM(sceneId, selfId, targetId, x300759_g_ScriptId , x300759_g_SubMissionID[index].MissionId);

end

--**********************************
--接受
--**********************************
function x300759_ProcQuestAccept( sceneId, selfId, targetId, MissionId )
	if IsHideName(sceneId, selfId) > 0 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"抱歉，蒙面状态不能接此任务。")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return 
	end
	
	if IsQuestFullNM( sceneId, selfId )==1 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"可接任务数量已满")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return 0
	end
	local iCostMoney = 1000
	local LevelLess = x300759_g_SubMissionID[1].LevelLess
	local LevelMax = x300759_g_SubMissionID[1].LevelMax
	for i,itm in x300759_g_SubMissionID do
		if itm.MissionId == MissionId then
			iCostMoney = itm.iCostMoney
			LevelLess = itm.LevelLess
			LevelMax = itm.LevelMax
			break
		end
	end

	if IsEnoughMoney(sceneId, selfId,iCostMoney) ~=1 then
		local Readme = "很抱歉，您包裹中的现银（银卡）不够支付押金，无法接取任务！" 
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, Readme);
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,Readme,8,2)
		return
	end

	local level = GetLevel(sceneId,selfId);
	if ( level < LevelLess or level >= LevelMax ) then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "您的等级不能领取此任务！");
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		local Readme = "您的等级不能领取此任务！" 
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

	if x300759_GetDayCount(sceneId, selfId) >= x300759_g_Mis_Count then
		local Readme = "很抱歉，您今天任务次数已满，请明天再来做吧！" 
	  	BeginQuestEvent(sceneId)
		AddQuestText(sceneId,Readme );
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,Readme,8,2)
		return 0
	end
		
	local bHaveMission	= IsHaveQuestNM(sceneId, selfId, MissionId);
	if(bHaveMission > 0) then
		return 0;
	end

	for i,itm in x300759_g_SubMissionID do
		if MissionId == itm.MissionId then
			CallScriptFunction( x300759_g_BusScriptId, "OnCreateBus", sceneId, selfId ,MissionId,i)
			break
		end
	end

end

---------------------------------------------------------------------------------------------------
--检查任务是否可提交
---------------------------------------------------------------------------------------------------
function x300759_CheckSubmit(sceneId, selfId, targetId,index)
	
	local npcGuid = GetMonsterGUID(sceneId,targetId)

	if x300759_g_SubMissionID[index].SubmitNPCGUID ~= npcGuid then
		return 0
	end

	return 1;

end

--**********************************
--接受
--**********************************
function x300759_ProcAccept( sceneId, selfId )
	
end

--完成任务
--返回1代表成功，0代表交任务失败
function x300759_ProcQuestSubmit( sceneId, selfId, targetId, selectId, MissionId )

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
		AddQuestText(sceneId, "您护送的马车离您太远了，无法提交任务！");
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		local Readme = "您护送的马车离您太远了，无法提交任务！"
		Msg2Player(sceneId,selfId,Readme,8,2)
		return 0
	end
   
	--给奖励
	local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId)
	local ret = DelQuest( sceneId, selfId, MissionId) 

	if ret == 1 then -- 如果成功完成
  CallScriptFunction( 256288, "FinishYayun", sceneId, selfId)
		--国家实力加1分
		AddCountryStrength(sceneId, selfId, 1)	
		
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, "恭喜，您为国家实力榜贡献了#R1个#O积分。");
		EndQuestEvent(sceneId);
		DispatchQuestTips(sceneId,selfId);
		Msg2Player(sceneId,selfId,"恭喜，您为国家实力榜贡献了#R1个#O积分。",8,2)		
		
		local index = 1
		for i,itm in x300759_g_SubMissionID do
			if MissionId == itm.MissionId then
				--交任务写日志
				GamePlayScriptLog(sceneId,selfId,itm.SubmitId)
				index = i
				break;			
			end
		end

		x300759_SetDayCount(sceneId, selfId)
		local ret = CountryIsFortuneTime(sceneId,selfId,0)
		if ret == 1  then   -- 国运期间
			local level = GetLevel(sceneId,selfId)
			local exp = ceil (( x300759_g_SubMissionID[index].coef1 * x300759_g_SubMissionID[index].coef2 * level * x300759_g_SubMissionID[index].coef3*x300759_g_SubMissionID[index].coef5 ))	
			local exp1 = ceil ((  x300759_g_SubMissionID[index].coef1 * x300759_g_SubMissionID[index].coef2 * level * x300759_g_SubMissionID[index].coef3*x300759_g_SubMissionID[index].coef4 ))
			if level >= 70 then
				exp =level*9000*2
				exp1=level*9000
			end
			AddExp(sceneId, selfId,exp)	
			local Readme = "您完成了任务：【个人】官府押运#r获得#R经验"..exp1.."点#o的奖励#r国运额外获得#R经验"..exp1.."点#o的奖励"
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, "您完成了任务：【个人】官府押运");
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, "获得#R经验"..exp1.."点#o的奖励");
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, "国运额外获得#R经验"..exp1.."点#o的奖励");
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
			Msg2Player(sceneId,selfId,Readme,8,2)
			--CallScriptFunction( 256288, "FinishYayun", sceneId, selfId)
		else
			local level = GetLevel(sceneId,selfId)
			
			local exp = ceil ((  x300759_g_SubMissionID[index].coef1 * x300759_g_SubMissionID[index].coef2 * level * x300759_g_SubMissionID[index].coef3*x300759_g_SubMissionID[index].coef4 ))
			
			if level >= 70 then
				exp = level*9000
			end
			
			AddExp(sceneId, selfId,exp)	
			local Readme =  "您完成了任务：【个人】官府押运#r获得#R经验"..exp.."点#o的奖励"
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, "您完成了任务：【个人】官府押运");
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, "获得#R经验"..exp.."点#o的奖励");
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
			Msg2Player(sceneId,selfId,Readme,8,2)
		end         
		
		local BusID  =  GetBusId(sceneId, selfId)
		if BusID ~= -1 and IsObjValid (sceneId,BusID) == 1 then
			--如果BUS还活着
			if GetBusQuestID(sceneId, BusID) == MissionId then
				DeleteBus(sceneId, BusID,1)
			end
		end 
		
		x300759_GuoYun(sceneId, selfId, MissionId)
	end

	return 0
	
end


--********************************************************************
--放弃
--********************************************************************
function x300759_ProcQuestAbandon( sceneId, selfId,MissionId )

	for i,itm in x300759_g_SubMissionID do
		local bHaveMission = IsHaveQuestNM(sceneId, selfId,itm.MissionId );
		if bHaveMission > 0 then

			if IsBusMember(sceneId, selfId) == 1 then
				local BusID  =  GetBusId(sceneId, selfId)
				if BusID ~= -1 and IsObjValid (sceneId,BusID) == 1 then
					--如果BUS还活着
					if GetBusQuestID(sceneId, BusID) == itm.MissionId then
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

			local misIndex = GetQuestIndexByID(sceneId, selfId, itm.MissionId); 
			DelQuest(sceneId, selfId, itm.MissionId);
							
			--放弃任务写日志
			GamePlayScriptLog(sceneId,selfId,itm.SubmitId+1)

			local Readme = "您放弃了任务：【个人】官府押运"
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, Readme);
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
			Msg2Player(sceneId,selfId,Readme,8,2)

			x300759_SetDayCount(sceneId, selfId)

			break
		end
	end
  	
end


function x300759_ProcQuestAttach( sceneId, selfId, npcId, npcGuid,misIndex, MissionId )
	
	for i,itm in x300759_g_SubMissionID do
		local bHaveMission = IsHaveQuestNM(sceneId, selfId,itm.MissionId );

		if bHaveMission > 0 then
			if npcGuid == itm.SubmitNPCGUID then
				local state = GetQuestStateNM(sceneId,selfId,npcId,itm.MissionId)
				AddQuestNumText(sceneId, itm.MissionId, itm.MissionName,7,i);
				return
			end
		end
	end

end

---------------------------------------------------------------------------------------------------
--任务日志刷新
---------------------------------------------------------------------------------------------------
function x300759_QuestLogRefresh( sceneId, selfId, MissionId)

	for i,itm in x300759_g_SubMissionID do 
		local bHaveMission = IsHaveQuestNM(sceneId, selfId,itm.MissionId );
		if bHaveMission > 0 then
		
			BeginQuestEvent(sceneId)	
			local level = GetLevel(sceneId, selfId)
			local ExpBonus = ceil (( itm.coef1 * itm.coef2 * level * itm.coef3 ))
			if level >= 70 then
				ExpBonus = level*9000
			end
		    if ExpBonus > 0 then
				AddQuestExpBonus(sceneId,ExpBonus);
			end

			AddQuestLogCustomText( sceneId,
									"",						-- 标题
									itm.MissionName,        -- 任务名字
									itm.MissionTarget,		--任务目标
									itm.NPCName,			--任务NPC
									itm.Missionruse,               --任务攻略
									itm.MissionInfo,	--任务描述
									""					--任务小提示
									)
			EndQuestEvent(sceneId)
			DispatchQuestLogUpdate(sceneId, selfId, itm.MissionId);
			break
		end
	end

end

function x300759_ProcQuestLogRefresh( sceneId, selfId, MissionId)
	x300759_QuestLogRefresh( sceneId, selfId, MissionId );
end

---------------------------------------------------------------------------------------------------
--取得此任务当天当前已完成次数
---------------------------------------------------------------------------------------------------
function x300759_GetDayCount(sceneId, selfId)

	if x300759_g_Mis_Count > 0 then

		local today = GetDayOfYear()

		local lastday = GetQuestData(sceneId, selfId, MD_MYSELF_CONVOY_DATE[1], MD_MYSELF_CONVOY_DATE[2], MD_MYSELF_CONVOY_DATE[3])

		if lastday ~= today then
			return 0
		end

		local daycount =  GetQuestData(sceneId, selfId, MD_MYSELF_CONVOY_COUNT[1], MD_MYSELF_CONVOY_COUNT[2], MD_MYSELF_CONVOY_COUNT[3])
		return daycount

	end

	return 0
end

---------------------------------------------------------------------------------------------------
--更新当天接任务次数
---------------------------------------------------------------------------------------------------
function x300759_SetDayCount(sceneId, selfId)
	local today = GetDayOfYear()

	local lastday = GetQuestData(sceneId, selfId, MD_MYSELF_CONVOY_DATE[1], MD_MYSELF_CONVOY_DATE[2], MD_MYSELF_CONVOY_DATE[3])

	if lastday ~= today then
		SetQuestData(sceneId, selfId, MD_MYSELF_CONVOY_DATE[1], MD_MYSELF_CONVOY_DATE[2], MD_MYSELF_CONVOY_DATE[3], today)
		SetQuestData(sceneId, selfId, MD_MYSELF_CONVOY_COUNT[1], MD_MYSELF_CONVOY_COUNT[2], MD_MYSELF_CONVOY_COUNT[3], 1)
	else
		local daycount = GetQuestData(sceneId, selfId, MD_MYSELF_CONVOY_COUNT[1], MD_MYSELF_CONVOY_COUNT[2], MD_MYSELF_CONVOY_COUNT[3])
		SetQuestData(sceneId, selfId, MD_MYSELF_CONVOY_COUNT[1], MD_MYSELF_CONVOY_COUNT[2], MD_MYSELF_CONVOY_COUNT[3], daycount+1)
	end
end

function x300759_GuoYun(sceneId, selfId, MissionId)
	if CountryIsFortuneTime(sceneId, selfId, 0) > 0 then
		local country = GetCurCountry(sceneId, selfId)
		SetCountryQuestData(sceneId, country, CD_INDEX_GUOYUN_COUNT, 1, 1 )
	end
end






