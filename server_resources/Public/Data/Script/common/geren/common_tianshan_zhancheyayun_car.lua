--功能：战车的默认脚本
--帮会镖车发布

x300917_g_ScriptId = 300917
x300917_g_MissionName = "创建镖车"
x300917_g_Mis_Count   = 3
--无敌impact在表中的索引,玩家进入BUS后获得一个无敌impact,
x300917_g_GodIndex = 1210

x300917_g_Carinfo = {
						{ CarType = 42,BaseAI = 3,AIScript = 3,Script = 300917 },
						{ CarType = 43,BaseAI = 3,AIScript = 3,Script = 300917 },
						{ CarType = 44,BaseAI = 3,AIScript = 3,Script = 300917 }
					}

x300917_g_MissionId = 7034
x300917_g_GameId = 71

--**********************************

--任务入口函数

--**********************************

function x300917_ProcEventEntry(sceneId, selfId, targetId)	--点击该任务后执行此脚本

end

--**********************************

--列举事件

--**********************************
function x300917_ProcEnumEvent(sceneId, selfId, targetId)
	--AddQuestNumText(sceneId, x300917_g_ScriptId, x300917_g_MissionName);
end


function x300917_OnCreateBus( sceneId, selfId,MissionId ,BusID)
  --local PosX,PosZ = GetWorldPos(sceneId, selfId)
    local PosX = 70
	local PosZ = 179
	local ObjID = CreateBus(sceneId, x300917_g_Carinfo[BusID].CarType, PosX, PosZ, x300917_g_Carinfo[BusID].BaseAI, x300917_g_Carinfo[BusID].AIScript, x300917_g_Carinfo[BusID].Script, selfId, x300917_g_GodIndex,MissionId,-1)
	
end
--创建busd成功处理
function x300917_OnCreateBusOK(sceneId, selfId, busId,targetId,MissionId)
		
		SetBusTimerTick(sceneId , busId, 1000)
		SetBusWaitTime(sceneId , busId, 300)
		SetBusTimerOpen(sceneId, busId, 0)
		SetBusQuestID(sceneId,busId,MissionId)

		local CarName = GetName( sceneId, selfId ).."的战车"
		SetBusTitle(sceneId , busId, CarName)
		local camp = GetCurCamp(sceneId, selfId)
		SetBusCurCamp(sceneId, busId,camp)

end


function x300917_DeleteBus(sceneId, ObjId)

	DeleteBus(sceneId, ObjId,1)

end


--玩家请求进入BUS
--selfId：玩家ID
--targetId：BUSID
function x300917_OnIntoBusEvent(sceneId, selfId,targetId)
	local InBus = IsBusMember(sceneId, selfId)
	if InBus == 1 then
		BeginQuestEvent(sceneId)
		  	AddQuestText(sceneId,"你已经有战车了");
		EndQuestEvent()
		DispatchQuestTips(sceneId,selfId)
		local Readme = "你已经有战车了"
		Msg2Player(sceneId,selfId,Readme,8,2)
		return
	end

	local BusSize = GetBusSize(sceneId,targetId)
	local MemberNum = GetBusMemberCount(sceneId,targetId)

	if BusSize<=MemberNum  then
		BeginQuestEvent(sceneId)
		  	AddQuestText(sceneId,"这辆战车已经有人运了");
		EndQuestEvent()
		DispatchQuestTips(sceneId,selfId)
		local Readme = "这辆战车已经有人运了"
		Msg2Player(sceneId,selfId,Readme,8,2)
		return
	end

	local IsOwner = IsTheBusOwner(sceneId, selfId, targetId )
	if IsOwner == 1 then
		--进入BUS
		AddBusMember(sceneId, selfId,targetId)
	end
end

function x300917_OnIntoBusAfter(sceneId, selfId,BusID)

    if IsObjValid (sceneId,BusID) ~= 1 then
        return
    end

	local MissionId = GetBusQuestID(sceneId,BusID)
	
	local iCostMoney = x300917_CalcCostMoney(sceneId, selfId)
	-- local num = CostMoney( sceneId , selfId ,1, iCostMoney,301)--成功返回1 失败返回-1
	-- local num1 = CostMoney( sceneId , selfId ,0, iCostMoney,301)--成功返回1 失败返回-1
	if CostMoney( sceneId , selfId ,0,iCostMoney,301) ~= 1 then
		DispatchQuestTips(sceneId,selfId)
		local Readme = "很抱歉，您包裹中的现银不足，无法接取任务！" 
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
		AddQuestText(sceneId,"您接受了任务：【个人】战车护送")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		local Readme = format("接受战车护送成功，扣除#R现银#{_MONEY%d}。", iCostMoney)
		--local Readme1 = "接受官府押运成功"
		-- BeginQuestEvent(sceneId)
		-- AddQuestText(sceneId, Readme1")
		-- EndQuestEvent(sceneId)
		-- DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,Readme,8,2)
		--接任务日志
		GamePlayScriptLog(sceneId,selfId,1423)
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
		GamePlayScriptLog(sceneId,selfId,1421)

		local misIndex = GetQuestIndexByID(sceneId, selfId, MissionId);
		SetQuestByIndex(sceneId, selfId, misIndex, 7, 0);	
	end

	local CarName = GetName( sceneId, selfId ).."的战车"
	SetBusTitle(sceneId , BusID, CarName)
	local camp = GetCurCamp(sceneId, selfId)
	SetBusCurCamp(sceneId, BusID,camp)

end


--玩家离开BUS
--selfId：玩家ID
function x300917_OnLeaveBusEvent(sceneId, selfId,BusId)
		BeginQuestEvent(sceneId)
		  AddQuestText(sceneId,"你正在护送战车，无法离开");
		EndQuestEvent()
		DispatchQuestTips(sceneId,selfId)
		local Readme = "你正在护送战车，无法离开"
		Msg2Player(sceneId,selfId,Readme,8,2)
end


function x300917_OnDie(sceneId,BusId,idKiller)

    if IsObjValid (sceneId,BusId) ~= 1 then
        return
    end

	if idKiller == -1 then
		--自死亡，目前只用于将玩家投入监狱前删除镖车
		local OwnerID = GetBusMemberObjId(sceneId,BusId,0)
		if OwnerID ~= -1 then
			x300917_Abandon( sceneId, OwnerID  )
			local Readme = "您的战车被摧毁"
			BeginQuestEvent(sceneId);AddQuestText(sceneId, "战车被摧毁！");EndQuestEvent(sceneId);Msg2Player(sceneId,OwnerID,Readme,8,2)
		end
		return
	end

	if IsObjValid(sceneId,idKiller)  == 0 then
		--无效OBJ
		local OwnerID = GetBusMemberObjId(sceneId,BusId,0)
		if OwnerID ~= -1 then
			x300917_Abandon( sceneId, OwnerID  )
			local Readme = "您的战车被摧毁"
			BeginQuestEvent(sceneId);AddQuestText(sceneId, "战车被摧毁！");EndQuestEvent(sceneId);DispatchQuestTips(sceneId,OwnerID);Msg2Player(sceneId,OwnerID,Readme,8,2)
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
				x300917_Abandon( sceneId, OwnerID  )
				local Readme = "您的战车被摧毁"
				BeginQuestEvent(sceneId);AddQuestText(sceneId, "战车被摧毁！");EndQuestEvent(sceneId);DispatchQuestTips(sceneId,OwnerID);Msg2Player(sceneId,OwnerID,Readme,8,2)
			end
			return
		end
	end

	if ObjType == 1 then     --被玩家杀死
		
		local BusMisId = GetBusQuestID( sceneId,BusId )

		local iCostMoney = x300917_CalcAddMoney(sceneId, BusId)
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
				BeginQuestEvent(sceneId);AddQuestText(sceneId, "您击杀了本国的战车，您的PK值增加了");EndQuestEvent(sceneId);DispatchQuestTips(sceneId,idKiller)
				Msg2Player(sceneId,idKiller,format("您击杀了本国的战车，您的PK值增加了"),8,2)				
			else
				BeginQuestEvent(sceneId);AddQuestText(sceneId, "您击杀了本国的战车");EndQuestEvent(sceneId);DispatchQuestTips(sceneId,idKiller)
				Msg2Player(sceneId,idKiller,format("您击杀了本国的战车"),8,2)			
			end

		else
	        AddMoney(sceneId,idKiller,0,iCostMoney)

		  	BeginQuestEvent(sceneId);AddQuestText(sceneId, "您击杀了敌国的战车！");EndQuestEvent(sceneId);DispatchQuestTips(sceneId,idKiller)
			Msg2Player(sceneId,idKiller,format("您击杀了敌国的战车。"),8,2)	
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

			x300917_Abandon( sceneId, OwnerID  )

			local GuildTitle = ""
			if GetGuildID(sceneId,idKiller) ~= -1 then
				GuildTitle = GetGuildTitle(sceneId,idKiller)
			end
			local killerName = GetName(sceneId,idKiller)
			local Readme = "您的战车被"..Country..GuildTitle.."的玩家"..killerName.."摧毁，战车护送任务失败！"
			if IsHideName(sceneId,idKiller) > 0 then
				Readme = "您的战车被"..HIDE_NAME.."摧毁，战车护送任务失败！"
			end
			BeginQuestEvent(sceneId);AddQuestText(sceneId, "战车被摧毁！");EndQuestEvent(sceneId);DispatchQuestTips(sceneId,OwnerID);Msg2Player(sceneId,OwnerID,Readme,8,2)

		end
	else		--被怪杀死
		local OwnerID = GetBusMemberObjId(sceneId,BusId,0)
		if OwnerID ~= -1 then
			x300917_Abandon( sceneId, OwnerID  )
			local Readme = "您的战车被怪物摧毁，战车护送任务失败！"
			BeginQuestEvent(sceneId);AddQuestText(sceneId, "战车被摧毁！");EndQuestEvent(sceneId);Msg2Player(sceneId,OwnerID,Readme,8,2)
		end
	end

end


function x300917_OnTime(sceneId,BusId)

end

function x300917_OnLifeTimeOut(sceneId,BusId)
    local selfId = GetBusMemberObjId(sceneId,BusId,0)
    if(IsPlayerStateNormal(sceneId, selfId) ~= 0) then
		x300917_Abandon( sceneId, selfId  )
	end
	DeleteBus(sceneId, BusId,1)
end

function x300917_OnWaitTimeOut(sceneId,BusId)
	local selfId = GetBusMemberObjId(sceneId,BusId,0)
	if(IsPlayerStateNormal(sceneId, selfId) ~= 0) then
		x300917_Abandon( sceneId, selfId  )
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

function x300917_OnBusStopWhenOwnerFarAway(sceneId, ownerId)
end




--********************************************************************
--放弃
--********************************************************************
function x300917_Abandon( sceneId, selfId )

	if IsHaveQuestNM( sceneId, selfId, x300917_g_MissionId) ~= 0 then	-- 如果有这个任务
		DelQuestNM( sceneId, selfId, x300917_g_MissionId)
		x300917_SetDayCount(sceneId, selfId)
		return
	end

end

function x300917_CleaupMission( sceneId, selfId )

	if IsHaveQuestNM( sceneId, selfId, x300917_g_MissionId) ~= 0 then	-- 如果有这个任务
		DelQuestNM( sceneId, selfId, x300917_g_MissionId)
		local Readme = "由于您离开护送目标时间过久或护送目标已被击杀，您的护送目标消失了，任务失败！"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, Readme);
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,Readme,8,2)
		x300917_SetDayCount(sceneId, selfId)
		return
	end

end

function x300917_OnBusStopWhenOwnerFarAway(sceneId, ownerId)
	local strText = "很抱歉，由于您离开#G战车#W#o过远，战车无人引导停止前进！"
	BeginQuestEvent(sceneId)
	AddQuestText(sceneId, strText);
	EndQuestEvent(sceneId)
	DispatchQuestTips(sceneId, ownerId)
	Msg2Player(sceneId,ownerId,strText,8,2)
end

---------------------------------------------------------------------------------------------------
--取得此任务当天当前已完成次数
---------------------------------------------------------------------------------------------------
function x300917_GetDayCount(sceneId, selfId)

	if x300917_g_Mis_Count > 0 then

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
function x300917_SetDayCount(sceneId, selfId)
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
function x300917_CalcCostMoney(sceneId, selfId)
	local count = x300917_GetDayCount(sceneId, selfId)
	if count == 0 then
		return 75000
	elseif count == 1 then
		return 150000
	elseif count == 2 then
		return 225000
	end
	return 0
end

--计算奖励多少钱
function x300917_CalcAddMoney(sceneId, BusId)
	local nBusIndex = GetBusIndex(sceneId,BusId)
	if nBusIndex == x300917_g_Carinfo[1].CarType then
			return 52500
	elseif nBusIndex == x300917_g_Carinfo[2].CarType then
			return 105000
	elseif nBusIndex == x300917_g_Carinfo[3].CarType then
			return 157500
	end
	return 0
end