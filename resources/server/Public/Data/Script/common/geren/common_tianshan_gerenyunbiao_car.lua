--功能：战车的默认脚本
--帮会镖车发布

x300854_g_ScriptId = 300854
x300854_g_MissionName = "创建镖车"

--无敌impact在表中的索引,玩家进入BUS后获得一个无敌impact,
x300854_g_GodIndex = 1210

x300854_g_Carinfo = {
						{ CarType = 7,BaseAI = 3,AIScript = 3,Script = 300854 },
						{ CarType = 8,BaseAI = 3,AIScript = 3,Script = 300854 },
						{ CarType = 9,BaseAI = 3,AIScript = 3,Script = 300854 },
						{ CarType = 38,BaseAI = 3,AIScript = 3,Script = 300854 },
						{ CarType = 39,BaseAI = 3,AIScript = 3,Script = 300854 },
						{ CarType = 40,BaseAI = 3,AIScript = 3,Script = 300854 },



					}

x300854_g_MissionId = {
						{ ID = 7620,iCostMoney = 1000, GameId = 51 },
						{ ID = 7621,iCostMoney = 2000, GameId = 61 },
						{ ID = 7622,iCostMoney = 3000,GameId = 71 },
						{ ID = 7623,iCostMoney = 5000,GameId = 81 },
						{ ID = 7624,iCostMoney = 6000,GameId = 741 },
						{ ID = 7625,iCostMoney = 7500,GameId = 751 },
					  }

--**********************************

--任务入口函数

--**********************************

function x300854_ProcEventEntry(sceneId, selfId, targetId)	--点击该任务后执行此脚本

end

--**********************************

--列举事件

--**********************************
function x300854_ProcEnumEvent(sceneId, selfId, targetId)
	--AddQuestNumText(sceneId, x300854_g_ScriptId, x300854_g_MissionName);
end


function x300854_OnCreateBus( sceneId, selfId,MissionId ,BusID)

    local PosX = 67
    local PosZ = 170
	local ObjID = CreateBus(sceneId, x300854_g_Carinfo[BusID].CarType, PosX, PosZ, x300854_g_Carinfo[BusID].BaseAI, x300854_g_Carinfo[BusID].AIScript, x300854_g_Carinfo[BusID].Script, selfId, x300854_g_GodIndex,MissionId,-1)
end

--创建busd成功处理
function x300854_OnCreateBusOK(sceneId, selfId, busId,targetId,MissionId)			
		SetBusTimerTick(sceneId , busId, 1000)
		SetBusWaitTime(sceneId , busId, 300)
		SetBusTimerOpen(sceneId, busId, 0)
		SetBusQuestID(sceneId,busId,MissionId)

		local CarName = GetName( sceneId, selfId ).."的马车"
		SetBusTitle(sceneId , busId, CarName)
		local camp = GetCurCamp(sceneId, selfId)
		SetBusCurCamp(sceneId, busId,camp)
end


function x300854_DeleteBus(sceneId, ObjId)

	DeleteBus(sceneId, ObjId,1)

end


--玩家请求进入BUS
--selfId：玩家ID
--targetId：BUSID
function x300854_OnIntoBusEvent(sceneId, selfId,targetId)
	local InBus = IsBusMember(sceneId, selfId)
	if InBus == 1 then
		BeginQuestEvent(sceneId)
		  	AddQuestText(sceneId,"你已经有马车了");
		EndQuestEvent()
		DispatchQuestTips(sceneId,selfId)
		local Readme = "你已经有马车了"
		Msg2Player(sceneId,selfId,Readme,8,2)
		return
	end

	local BusSize = GetBusSize(sceneId,targetId)
	local MemberNum = GetBusMemberCount(sceneId,targetId)

	if BusSize<=MemberNum  then
		BeginQuestEvent(sceneId)
		  	AddQuestText(sceneId,"这辆马车已经有人运了");
		EndQuestEvent()
		DispatchQuestTips(sceneId,selfId)
		local Readme = "这辆马车已经有人运了"
		Msg2Player(sceneId,selfId,Readme,8,2)
		return
	end

	local IsOwner = IsTheBusOwner(sceneId, selfId, targetId )
	if IsOwner == 1 then
		--进入BUS
		AddBusMember(sceneId, selfId,targetId)
	end
end

function x300854_OnIntoBusAfter(sceneId, selfId,BusID)

    if IsObjValid (sceneId,BusID) ~= 1 then
        return
    end

	local MissionId = GetBusQuestID(sceneId,BusID)

	local GameId = 71
	local iCostMoney = 1000
	for i,itm in x300854_g_MissionId do
		if itm.ID == MissionId then
			iCostMoney = itm.iCostMoney
			GameId 	= itm.GameId 
			break
		end
	end
	
	-- local num = CostMoney( sceneId , selfId ,1, iCostMoney,301)--成功返回1 失败返回-1
	-- local num1 = CostMoney( sceneId , selfId ,0, iCostMoney,301)--成功返回1 失败返回-1
	if SpendMoney( sceneId , selfId ,iCostMoney,301) ~= 1 then
		DispatchQuestTips(sceneId,selfId)
		local Readme = "很抱歉，您包裹中的现银（银卡）不够支付押金，无法接取任务！" 
		Msg2Player(sceneId,selfId,Readme,8,2)
		return
		-- else
		-- BeginQuestEvent(sceneId)
		-- AddQuestText(sceneId,"您接受了任务：【个人】官府押运")
		-- EndQuestEvent(sceneId)
		-- DispatchQuestTips(sceneId,selfId)
		-- local Readme = format("接受官府押运成功，扣除押金#R现银#{_MONEY%d}。", iCostMoney)
		--local Readme1 = "接受官府押运成功"
		-- BeginQuestEvent(sceneId)
		-- AddQuestText(sceneId, Readme1")
		-- EndQuestEvent(sceneId)
		-- DispatchQuestTips(sceneId,selfId)
		--Msg2Player(sceneId,selfId,Readme,8,2)
	else
		--local Readme1 = "接受官府押运成功"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"您接受了任务：【个人】官府押运")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		local Readme = format("接受官府押运成功，扣除押金#R现银（银卡）#{_MONEY%d}。", iCostMoney)
		--local Readme1 = "接受官府押运成功"
		-- BeginQuestEvent(sceneId)
		-- AddQuestText(sceneId, Readme1")
		-- EndQuestEvent(sceneId)
		-- DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,Readme,8,2)
	end
	
	--检查前置任务
	local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId, MissionId )
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

	if AddQuestNM( sceneId, selfId,MissionId) == 1 then
		
		--接任务写日志
		GamePlayScriptLog(sceneId,selfId,GameId)

		local misIndex = GetQuestIndexByID(sceneId, selfId, MissionId);
		SetQuestByIndex(sceneId, selfId, misIndex, 7, 0);	
	end

	local CarName = GetName( sceneId, selfId ).."的马车"
	SetBusTitle(sceneId , BusID, CarName)
	local camp = GetCurCamp(sceneId, selfId)
	SetBusCurCamp(sceneId, BusID,camp)

end


--玩家离开BUS
--selfId：玩家ID
function x300854_OnLeaveBusEvent(sceneId, selfId,BusId)
		BeginQuestEvent(sceneId)
		  AddQuestText(sceneId,"你正在运镖，无法离开");
		EndQuestEvent()
		DispatchQuestTips(sceneId,selfId)
		local Readme = "你正在运镖，无法离开"
		Msg2Player(sceneId,selfId,Readme,8,2)
end


function x300854_OnDie(sceneId,BusId,idKiller)

    if IsObjValid (sceneId,BusId) ~= 1 then
        return
    end

	if idKiller == -1 then
		--自死亡，目前只用于将玩家投入监狱前删除镖车
		local OwnerID = GetBusMemberObjId(sceneId,BusId,0)
		if OwnerID ~= -1 then
			x300854_Abandon( sceneId, OwnerID  )
			local Readme = "您的马车被摧毁"
			BeginQuestEvent(sceneId);AddQuestText(sceneId, "马车被摧毁！");EndQuestEvent(sceneId);Msg2Player(sceneId,OwnerID,Readme,8,2)
		end
		return
	end

	if IsObjValid(sceneId,idKiller)  == 0 then
		--无效OBJ
		local OwnerID = GetBusMemberObjId(sceneId,BusId,0)
		if OwnerID ~= -1 then
			x300854_Abandon( sceneId, OwnerID  )
			local Readme = "您的马车被摧毁"
			BeginQuestEvent(sceneId);AddQuestText(sceneId, "马车被摧毁！");EndQuestEvent(sceneId);DispatchQuestTips(sceneId,OwnerID);Msg2Player(sceneId,OwnerID,Readme,8,2)
		end
		return
	end

	local ObjType = GetObjType(sceneId,idKiller)	

	if ObjType == 3 then		-- 被PET杀死
		ObjType = 1
		idKiller = GetOwnerID(sceneId, idKiller)
		if IsPlayerStateNormal(sceneId,idKiller)  == 0 then
			--主人状态不正常
			local OwnerID = GetBusMemberObjId(sceneId,BusId,0)
			if OwnerID ~= -1 then
				x300854_Abandon( sceneId, OwnerID  )
				local Readme = "您的马车被摧毁"
				BeginQuestEvent(sceneId);AddQuestText(sceneId, "马车被摧毁！");EndQuestEvent(sceneId);DispatchQuestTips(sceneId,OwnerID);Msg2Player(sceneId,OwnerID,Readme,8,2)
			end
			return
		end
	end

	if ObjType == 1 then     --被玩家杀死
		
		local BusMisId = GetBusQuestID( sceneId,BusId )

		local iCostMoney = 1000
		for i,itm in x300854_g_MissionId do
			if BusMisId == itm.ID then 
				iCostMoney = itm.iCostMoney
				break
			end
		end

		local OwnerCountry = GetBusCountryID(sceneId,BusId)
		local KillerCountry = GetCurCountry(sceneId,idKiller)
		if OwnerCountry == KillerCountry then	
					
			--PK惩罚
			local IsPunish = 0
			local OwnerId = GetBusMemberObjId(sceneId,BusId,0)
			if OwnerId ~= -1 then
				IsPunish = CallScriptFunction( SCENE_SCRIPT_ID, "CashboxComputePKPunish", sceneId, OwnerId, idKiller )
				if IsKing( sceneId, idKiller ) ~= 1 and IsPunish == 1 then
					--非国王并且PK惩罚值大于0
					CallScriptFunction( SCENE_SCRIPT_ID, "KillerEnterPrison", sceneId, idKiller )
					IsPunish = 1
				else
					IsPunish = 0
				end			
			end
			
			if IsPunish==1 then
				BeginQuestEvent(sceneId);AddQuestText(sceneId, "您击杀了本国的马车，您的PK值增加了");EndQuestEvent(sceneId);DispatchQuestTips(sceneId,idKiller)
				Msg2Player(sceneId,idKiller,format("您击杀了本国的马车，您的PK值增加了"),8,2)				
			else
				BeginQuestEvent(sceneId);AddQuestText(sceneId, "您击杀了本国的马车");EndQuestEvent(sceneId);DispatchQuestTips(sceneId,idKiller)
				Msg2Player(sceneId,idKiller,format("您击杀了本国的马车"),8,2)			
			end

		else
	        --AddMoney(sceneId,idKiller,0,iCostMoney)

		  	BeginQuestEvent(sceneId);AddQuestText(sceneId, "您击杀了敌国的马车！");EndQuestEvent(sceneId);DispatchQuestTips(sceneId,idKiller)
			Msg2Player(sceneId,idKiller,format("您击杀了敌国的马车。"),8,2)	
		end

		local Country = "楼兰王国"
		if KillerCountry == 0 then
			Country = "楼兰王国"
		elseif KillerCountry == 1 then
			Country = "天山王国"
		elseif KillerCountry == 2 then
			Country = "昆仑王国"
		elseif KillerCountry == 3 then
			Country = "敦煌王国"
		else
			return
		end


		local OwnerID = GetBusMemberObjId(sceneId,BusId,0)
		if OwnerID ~= -1 then

			x300854_Abandon( sceneId, OwnerID  )

			local GuildTitle = ""
			if GetGuildID(sceneId,idKiller) ~= -1 then
				GuildTitle = GetGuildTitle(sceneId,idKiller)
			end
			local killerName = GetName(sceneId,idKiller)
			local Readme = "您的马车被"..Country..GuildTitle.."的玩家"..killerName.."摧毁，官府押运任务失败！"
			if IsHideName(sceneId,idKiller) > 0 then
				Readme = "您的马车被"..HIDE_NAME.."摧毁，官府押运任务失败！"
			end
			BeginQuestEvent(sceneId);AddQuestText(sceneId, "马车被摧毁！");EndQuestEvent(sceneId);DispatchQuestTips(sceneId,OwnerID);Msg2Player(sceneId,OwnerID,Readme,8,2)

		end
	else		--被怪杀死
		local OwnerID = GetBusMemberObjId(sceneId,BusId,0)
		if OwnerID ~= -1 then
			x300854_Abandon( sceneId, OwnerID  )
			local Readme = "您的马车被怪物摧毁，官府押运任务失败！"
			BeginQuestEvent(sceneId);AddQuestText(sceneId, "马车被摧毁！");EndQuestEvent(sceneId);Msg2Player(sceneId,OwnerID,Readme,8,2)
		end
	end

end


function x300854_OnTime(sceneId,BusId)

end

function x300854_OnLifeTimeOut(sceneId,BusId)
    local selfId = GetBusMemberObjId(sceneId,BusId,0)
    if(IsPlayerStateNormal(sceneId, selfId) ~= 0) then
		x300854_Abandon( sceneId, selfId  )
	end
	DeleteBus(sceneId, BusId,1)
end

function x300854_OnWaitTimeOut(sceneId,BusId)
	local selfId = GetBusMemberObjId(sceneId,BusId,0)
	if(IsPlayerStateNormal(sceneId, selfId) ~= 0) then
		x300854_Abandon( sceneId, selfId  )
		local strText = "由于您离开护送目标时间过久或护送目标已被击杀，您的护送目标消失了，任务失败！"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, strText);
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		local Readme = "由于您离开护送目标时间过久或护送目标已被击杀，您的护送目标消失了，任务失败！"
		Msg2Player(sceneId,selfId,Readme,8,2)
	end
	DeleteBus(sceneId, BusId,1)
end

function x300854_OnBusStopWhenOwnerFarAway(sceneId, ownerId)
end




--********************************************************************
--放弃
--********************************************************************
function x300854_Abandon( sceneId, selfId )

	for i,itm in x300854_g_MissionId do
		if IsHaveQuestNM( sceneId, selfId, itm.ID) ~= 0 then	-- 如果有这个任务
			DelQuestNM( sceneId, selfId, itm.ID)
			x300854_SetDayCount(sceneId, selfId)
			return
		end
	end

end

function x300854_CleaupMission( sceneId, selfId )

	for i,itm in x300854_g_MissionId do
		if IsHaveQuestNM( sceneId, selfId, itm.ID) ~= 0 then	-- 如果有这个任务
			DelQuestNM( sceneId, selfId, itm.ID)
			local Readme = "由于您离开护送目标时间过久或护送目标已被击杀，您的护送目标消失了，任务失败！"
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, Readme);
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
			Msg2Player(sceneId,selfId,Readme,8,2)
			x300854_SetDayCount(sceneId, selfId)
			return
		end
	end

end

function x300854_OnBusStopWhenOwnerFarAway(sceneId, ownerId)
	local strText = "很抱歉，由于您离开#G官府马车#W#o过远，官府马车迷失方向停止前进！"
	BeginQuestEvent(sceneId)
	AddQuestText(sceneId, strText);
	EndQuestEvent(sceneId)
	DispatchQuestTips(sceneId, ownerId)
	Msg2Player(sceneId,ownerId,strText,8,2)
end
---------------------------------------------------------------------------------------------------
--更新当天接任务次数
---------------------------------------------------------------------------------------------------
function x300854_SetDayCount(sceneId, selfId)
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
