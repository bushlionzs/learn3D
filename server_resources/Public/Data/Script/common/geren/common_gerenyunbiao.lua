--MisDescBegin
x300622_g_ScriptId 	  = 300622
x300622_g_MissionKind 				= 	1                       --任务类型
x300622_g_Mis_Count   = 1--每天可做的次数
x300622_g_LevelLess					= 	50 
--任务名称
x300622_g_MissionName = "【个人】官府押运"
-- NPC默认对话
x300622_g_NPCDialog = "\t我是官府任命的矿主，负责将这里产出的黄金发往王国各地。但是现在世道太乱，敌对势力经常通过武力抢夺我们的黄金，我看兄台气宇不凡，能否帮助我运送黄金？"
-- 任务信息
x300622_g_MissionInfo = "\t您可以通过矿主哈尔巴拉并花费#G10两现银#W就可以领取一辆#G马车#W，当您将马车安全护送到指定地点，系统将会给与您#G海量经验#W。\n"
-- 任务提示
x300622_g_MissionHelp = "\t#G护送途中如果您离开马车过远，马车会意识到危险而停止前进。\n\t#G如果马车受到袭击并死亡，您的任务将失败，同时押金将被抢走。\n\t#G当您离开马车一段时间或掉线，马车将消失，此时任务失败。"
-- 任务目标
x300622_g_MissionTarget = "  将马车交给@npc_129325"
x300622_g_NPCName = "@npc_129325"
x300622_g_ExtTarget					=	{ {type=20,n=1,target="马车"} }
x300622_g_MissionCompleted = "您已经将官府交给您的马车安全护送到此了？请收下官府给您的奖励！"
--MisDescEnd

-- 任务获取经验系数1
x300622_g_coef1 = 1000
-- 任务获取经验系数2
x300622_g_coef2 = 0.3
-- 任务获取经验系数3
x300622_g_coef3 = 20
x300622_g_coef4 =1 --普通经验倍数
x300622_g_coef5 = 2 -- 国运经验倍数
-- 最终计算公式为 x = x300622_g_coef1 * x300622_g_coef2 * x300622_g_coef3 * 玩家等级；

-- 押金
x300622_g_yajin = 10000
x300622_g_BusScriptId = 300623
-- 任务ID
x300622_g_MissionID = 7010;
-- 接受任务需要的最小等级
x300622_g_MinLevel = 50
-- 接受任务需要的最大等级
x300622_g_MaxLevel = 100
x300622_g_BusIndex = 3


function x300622_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
  	
	if IsHaveQuestNM( sceneId, selfId, MissionId ) == 0 then		-- 如果没有这个任务
		
		local playerLevel = GetLevel( sceneId, selfId);
		if( playerLevel >= x300622_g_MinLevel and playerLevel <= x300622_g_MaxLevel) then
			local state = GetQuestStateNM( sceneId, selfId, targetId, x300622_g_MissionID);
			AddQuestText(sceneId, x300622_g_NPCDialog );
			AddQuestNumText( sceneId, x300622_g_MissionID, x300622_g_MissionName, 5);
		end
		
	end

	return 0
end


--显示任务信息
function x300622_DispatchMissionInfo( sceneId, selfId, NPCId)
	BeginQuestEvent( sceneId);
		--任务信息
		AddQuestText(sceneId, "#Y"..x300622_g_MissionName);
		AddQuestText(sceneId, x300622_g_MissionInfo)

		--任务目标
		AddQuestText( sceneId, "#Y任务目标：")
		AddQuestText( sceneId, x300622_g_MissionTarget)
		--提示信息
		if x300622_g_MissionHelp ~= "" then
			AddQuestText(sceneId, "#Y任务提示：")
			AddQuestText(sceneId, x300622_g_MissionHelp )
		end
		
		--奖励信息
		
		--获得玩家当前等级
		local playerLevel = GetLevel( sceneId, selfId);
		--获取经验
		local experience = x300622_g_coef1 * x300622_g_coef2 * playerLevel * x300622_g_coef3;
		AddQuestExpBonus( sceneId, experience);
		--获取金钱
		--AddQuestMoneyBonus2( sceneId, x300622_g_yajin);
	EndQuestEvent(sceneId);
	DispatchQuestInfoNM(sceneId, selfId, NPCId, x300622_g_ScriptId, x300622_g_MissionID);
end


---------------------------------------------------------------------------------------------------
--向客户端发送任务完成信息
---------------------------------------------------------------------------------------------------
function x300622_DispatchCompletedInfo( sceneId, selfId, targetId )
	
	BeginQuestEvent(sceneId)

	--任务完成信息
	AddQuestText(sceneId,"#Y"..x300622_g_MissionName)
	AddQuestText(sceneId,x300622_g_MissionCompleted)
	AddQuestText(sceneId," ")

	--1、经验
	local level = GetLevel(sceneId, selfId)
	local ExpBonus = ceil ( (1000 * 0.3 * level * 20 ) )
	if ExpBonus> 0 then
		AddQuestExpBonus(sceneId, ExpBonus )
	end
			
	EndQuestEvent(sceneId)
	DispatchQuestContinueInfoNM(sceneId, selfId, targetId, x300622_g_ScriptId , x300622_g_MissionID);

end

--点击（按钮）点击该任务后执行此脚本
function x300622_ProcEventEntry( sceneId, selfId, targetId, MissionId,nExtIdx )

	if IsHaveQuestNM( sceneId, selfId, MissionId ) > 0 then	-- 如果没有这个任务
		x300622_DispatchCompletedInfo( sceneId, selfId, targetId) 	--完成任务显示
	else
		local BusID = IsBusMember(sceneId, selfId);
		if(BusID ~= 1) then
			if nExtIdx ~= x300622_g_ScriptId then
				x300622_DispatchMissionInfo( sceneId, selfId, targetId);
			else
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"你没有此任务！")
				EndQuestEvent()
				DispatchQuestEventList(sceneId,selfId,targetId);
			end
		else
				local strText = "您已处于护送状态，无法领取新的护送任务！"
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId, strText);
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				local Readme = "您已处于护送状态，无法领取新的护送任务！"
				Msg2Player(sceneId,selfId,Readme,8,2)
		end			
	end
		  
end


--**********************************
--接受
--**********************************
function x300622_ProcQuestAccept( sceneId, selfId, targetId, MissionId )

	if IsQuestFullNM( sceneId, selfId )==1 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"可接任务数量已满")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return 
	end

	if x300622_GetDayCount(sceneId, selfId) >= x300622_g_Mis_Count then
		local Readme = "很抱歉，您今天任务次数已满，请明天再来做吧！" 
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, Readme);
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,Readme,8,2)
		return
	end

	if IsTeamFollow(sceneId, selfId) == 1 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "组队跟随状态下不可以接护送任务！");
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		local Readme = "组队跟随状态下不可以接护送任务！"
		Msg2Player(sceneId,selfId,Readme,8,2)
		return 0
	end
		
	local CurrMoney = GetMoney(sceneId , selfId ,0)
	if CurrMoney < x300622_g_yajin then
		local Readme = "很抱歉，您包裹中的现银不够支付押金，无法接取任务！" 
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, Readme);
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,Readme,8,2)
		return
	end			
	CallScriptFunction( x300622_g_BusScriptId, "OnCreateBus", sceneId, selfId ,MissionId,x300622_g_BusIndex)
	
	
	
end


--**********************************
--接受
--**********************************
function x300622_ProcAccept( sceneId, selfId )
	
end

--完成任务
--返回1代表成功，0代表交任务失败
function x300622_ProcQuestSubmit( sceneId, selfId, targetId, selectId, MissionId )

	if IsQuestHaveDoneNM( sceneId, selfId, MissionId ) > 0 then --任务已经完成
		return 0
	end

	if IsHaveQuestNM( sceneId, selfId, MissionId) == 0 then	-- 如果没这个任务直接退出
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
		local ret = QuestCheckSubmitNM( sceneId, selfId, targetId, MissionId, misIndex ) -- 获取完成任务检查信息
		if ret > 0 then -- 如果可以完成
		local ret = DelQuestNM( sceneId, selfId, MissionId ) 
		if ret == 1 then -- 如果成功完成

			--交任务写日志
			GamePlayScriptLog(sceneId,selfId,72)

			x300622_SetDayCount(sceneId, selfId)

			local ret = CountryIsFortuneTime(sceneId,selfId,0)
			if ret == 1  then   -- 国运期间
				local level = GetLevel(sceneId,selfId)
				local exp = ceil (( x300622_g_coef1 * x300622_g_coef2 * level * x300622_g_coef3*x300622_g_coef5 ))
				AddExp(sceneId, selfId,exp)	
				local level = GetLevel(sceneId,selfId)
				local exp1 = ceil (( x300622_g_coef1 * x300622_g_coef2 * level * x300622_g_coef3*x300622_g_coef4 ))
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
			
			else
				local level = GetLevel(sceneId,selfId)
				local exp = ceil (( x300622_g_coef1 * x300622_g_coef2 * level * x300622_g_coef3*x300622_g_coef4 ))
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
		  	    
				if GetBusQuestID(sceneId, BusID) == MissionId then
					--如果BUS还活着
					DeleteBus(sceneId, BusID,1)
				end
		  	end     
		end
	end

	return 0
	
end


--********************************************************************
--放弃
--********************************************************************
function x300622_ProcQuestAbandon( sceneId, selfId,MissionId )

	if IsHaveQuestNM( sceneId, selfId, MissionId) == 0 then	-- 如果没有这个任务
		return
	end

	if IsBusMember(sceneId, selfId) == 1 then
		local BusID  =  GetBusId(sceneId, selfId)
		if BusID ~= -1 and IsObjValid (sceneId,BusID) == 1 then
			--如果BUS还活着
			if GetBusQuestID(sceneId, BusID) == MissionId then
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

	DelQuestNM( sceneId, selfId, MissionId)
	local Readme = "您放弃了任务：【个人】官府押运"
	BeginQuestEvent(sceneId)
	AddQuestText(sceneId, Readme);
    EndQuestEvent(sceneId)
	DispatchQuestTips(sceneId,selfId)
	Msg2Player(sceneId,selfId,Readme,8,2)

	x300622_SetDayCount(sceneId, selfId)
  	
end


function x300622_ProcQuestAttach( sceneId, selfId, npcId, npcGuid,misIndex, MissionId )

	if IsHaveQuestNM( sceneId, selfId, MissionId) == 0 then	-- 如果没有这个任务
		return
	end

	local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId)
	local submitGuid = GetQuestSubmitNPCGUIDNM( sceneId, selfId, misIndex )
	if npcGuid == submitGuid then	--点击的NPC的名字和任务中NPC的名字相同，场景也判断过了
		AddQuestTextNM( sceneId, selfId, -1, MissionId, 7, x300622_g_ScriptId ) -- 显示任务信息
	end
end



---------------------------------------------------------------------------------------------------
--任务日志刷新
---------------------------------------------------------------------------------------------------
function x300622_QuestLogRefresh( sceneId, selfId, MissionId)

		local bHaveMission = IsHaveQuestNM(sceneId, selfId,MissionId );
		if bHaveMission > 0 then
		
			BeginQuestEvent(sceneId)	
			local level = GetLevel(sceneId, selfId)
			local ExpBonus = ceil (( x300622_g_coef1 * x300622_g_coef2 * level * x300622_g_coef3 ))
		    if ExpBonus > 0 then
			AddQuestExpBonus(sceneId,ExpBonus);
			end
		    AddQuestLogCustomText( sceneId,
									"",							-- 标题
									x300622_g_MissionName,      -- 任务名字
									x300622_g_MissionTarget,	--任务目标
									x300622_g_NPCName,			--任务NPC
									x300622_g_MissionHelp,      --任务攻略
									x300622_g_MissionInfo,		--任务描述
									""							--任务小提示
									)
			EndQuestEvent(sceneId)
			DispatchQuestLogUpdate(sceneId, selfId, MissionId);
		end
end

function x300622_ProcQuestLogRefresh( sceneId, selfId, MissionId)
	x300622_QuestLogRefresh( sceneId, selfId, MissionId );
end

---------------------------------------------------------------------------------------------------
--取得此任务当天当前已完成次数
---------------------------------------------------------------------------------------------------
function x300622_GetDayCount(sceneId, selfId)

	if x300622_g_Mis_Count > 0 then

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
function x300622_SetDayCount(sceneId, selfId)
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

