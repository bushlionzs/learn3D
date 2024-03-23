--功能：战车的默认脚本
--帮会镖车发布

x300760_g_ScriptId = 300760
x300760_g_MissionName = "创建飞行器"

--无敌impact在表中的索引,玩家进入BUS后获得一个无敌impact,
x300760_g_GodIndex = 1210
x300760_g_Carinfo = {
						{ CarType = 3,BaseAI = 3,AIScript = 3,Script = 300760 },
						{ CarType = 5,BaseAI = 3,AIScript = 3,Script = 300760 },
						{ CarType = 6,BaseAI = 3,AIScript = 3,Script = 300760 },
						{ CarType = 35,BaseAI = 3,AIScript = 3,Script = 300760 },
						{ CarType = 36,BaseAI = 3,AIScript = 3,Script = 300760 },
						{ CarType = 37,BaseAI = 3,AIScript = 3,Script = 300760 },
					}

x300760_g_MissionId = {
						{ ID = 7556,iCostMoney =5000 ,AcceptId = 281 },
						{ ID = 7557,iCostMoney = 10000, AcceptId = 291 },
						{ ID = 7558, iCostMoney = 15000, AcceptId = 301 },
						{ ID = 7546, iCostMoney = 30000, AcceptId = 761 },
						{ ID = 7547, iCostMoney = 40000, AcceptId = 771 },
						{ ID = 7548, iCostMoney = 50000, AcceptId = 781 },
					  }

x300760_g_MainScriptId = 300757

--**********************************

--任务入口函数

--**********************************

function x300760_ProcEventEntry(sceneId, selfId, targetId)	--点击该任务后执行此脚本

end

--**********************************

--列举事件

--**********************************
function x300760_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
	--AddQuestNumText(sceneId, x300760_g_ScriptId, x300760_g_MissionName);
end


function x300760_OnCreateBus( sceneId,selfId,MissionId,BusID )

  local PosX,PosZ = GetWorldPos(sceneId, selfId)

	local ObjID = CreateBus(sceneId, x300760_g_Carinfo[BusID].CarType, PosX, PosZ, x300760_g_Carinfo[BusID].BaseAI, x300760_g_Carinfo[BusID].AIScript, x300760_g_Carinfo[BusID].Script, selfId, x300760_g_GodIndex,MissionId,-1)
end

--**********************************

--bus创建成功处理

--**********************************
function x300760_OnCreateBusOK(sceneId,selfId,busId,targetId,MissionId)	

	SetBusTimerTick(sceneId , busId, 1000)
	SetBusWaitTime(sceneId , busId, 300)
	SetBusTimerOpen(sceneId, busId, 0)
	SetBusQuestID(sceneId,busId,MissionId)

	local CarName = GetName( sceneId, selfId ).."的飞行器"
	SetBusTitle(sceneId , busId, CarName)
	local camp = GetCurCamp(sceneId, selfId)
	SetBusCurCamp(sceneId, busId,camp)

end


function x300760_DeleteBus(sceneId, ObjId)

	DeleteBus(sceneId, ObjId,1)

end


--玩家请求进入BUS
--selfId：玩家ID
--targetId：BUSID
function x300760_OnIntoBusEvent(sceneId, selfId,targetId)
	local InBus = IsBusMember(sceneId, selfId)
	if InBus == 1 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"你已经有飞行器了！");
		EndQuestEvent()
		DispatchQuestTips(sceneId,selfId)
		local Readme = "你已经有飞行器了！"
		Msg2Player(sceneId,selfId,Readme,8,2)
		return
	end

	local BusSize = GetBusSize(sceneId,targetId)
	local MemberNum = GetBusMemberCount(sceneId,targetId)

	if BusSize<=MemberNum  then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"这辆飞行器已经有人运了");
		EndQuestEvent()
		DispatchQuestTips(sceneId,selfId)
		local Readme = "这辆飞行器已经有人运了"
		Msg2Player(sceneId,selfId,Readme,8,2)
		return
	end

	local IsOwner = IsTheBusOwner(sceneId, selfId, targetId )
	if IsOwner == 1 then
		--进入BUS
		AddBusMember(sceneId, selfId,targetId)
	end
end

function x300760_OnIntoBusAfter(sceneId, selfId,BusID)

    if IsObjValid (sceneId,BusID) ~= 1 then
        return
    end

	local MissionId = GetBusQuestID(sceneId,BusID)

	for i,itm in x300760_g_MissionId do

		if MissionId == itm.ID then
			local bRet = CallScriptFunction( x300760_g_MainScriptId, "CostMoney", sceneId, selfId, MissionId)
			if bRet == 1 then

				if AddQuest(sceneId, selfId, MissionId,x300760_g_MainScriptId,0,0,0,1) == 1 then
					--接任务写日志
					GamePlayScriptLog(sceneId,selfId,itm.AcceptId)

					--local misIndex = CallScriptFunction( x300760_g_MainScriptId, "GetQuestIndexByID", sceneId, selfId, MissionId)
					local misIndex = GetQuestIndexByID(sceneId, selfId, MissionId);
					SetQuestByIndex(sceneId, selfId, misIndex, 7, 0);
					CallScriptFunction( x300760_g_MainScriptId, "QuestLogRefresh", sceneId, selfId, MissionId)	
					local CarName = GetName( sceneId, selfId ).."的飞行器"
					SetBusTitle(sceneId , BusID, CarName)

					local camp = GetCurCamp(sceneId, selfId)
					SetBusCurCamp(sceneId, BusID,camp)
				end
			end

			break

		end
	end

end

--玩家离开BUS
--selfId：玩家ID
function x300760_OnLeaveBusEvent(sceneId, selfId,BusId)
		BeginQuestEvent(sceneId)
		  AddQuestText(sceneId,"你正在护送中，无法离开");
		EndQuestEvent()
		DispatchQuestTips(sceneId,selfId)
		local Readme = "你正在护送中，无法离开"
		Msg2Player(sceneId,selfId,Readme,8,2)
end


function x300760_OnDie(sceneId,BusId,idKiller)

    if IsObjValid (sceneId,BusId) ~= 1 then
        return
    end

	if idKiller == -1 then
		--自死亡，目前只用于将玩家投入监狱前删除镖车
		local OwnerID = GetBusMemberObjId(sceneId,BusId,0)
		if OwnerID ~= -1 then
			x300760_Abandon( sceneId, OwnerID  )
			local Readme = "#R您的飞行器被摧毁，押运任务失败！"
			BeginQuestEvent(sceneId);AddQuestText(sceneId, "飞行器被摧毁！");EndQuestEvent(sceneId);Msg2Player(sceneId,OwnerID,Readme,8,2)
		end
		return
	end

	if IsObjValid(sceneId,idKiller)  == 0 then
		--无效OBJ
		local OwnerID = GetBusMemberObjId(sceneId,BusId,0)
		if OwnerID ~= -1 then
			x300760_Abandon( sceneId, OwnerID  )
			local Readme = "您的飞行器被摧毁"
			BeginQuestEvent(sceneId);AddQuestText(sceneId, "飞行器被摧毁！");EndQuestEvent(sceneId);DispatchQuestTips(sceneId,OwnerID);Msg2Player(sceneId,OwnerID,Readme,8,2)
		end
		return
	end

	local ObjType = GetObjType(sceneId,idKiller)

	if ObjType == 3 then		-- 被PET杀死
		ObjType = 1
		idKiller = GetOwnerID(sceneId, idKiller)
		if IsPlayerStateNormal(sceneId,idKiller)  == 0 then
			local OwnerID = GetBusMemberObjId(sceneId,BusId,0)
			if OwnerID ~= -1 then
			--状态不正常
				x300760_Abandon( sceneId, OwnerID  )
				local Readme = "您的马车被摧毁"
				BeginQuestEvent(sceneId);AddQuestText(sceneId, "马车被摧毁！");EndQuestEvent(sceneId);DispatchQuestTips(sceneId,OwnerID);Msg2Player(sceneId,OwnerID,Readme,8,2)
			end
			return
		end
	end

	if ObjType == 1 then		--被玩家杀死
	
		local BusMisId = GetBusQuestID( sceneId,BusId )

		local iCostMoney = 10000
		for i,itm in x300760_g_MissionId do
			
			if BusMisId == itm.ID then		-- 如果有这个任务
				iCostMoney = itm.iCostMoney
				break
			end
		end
		local iCostMoney2 =iCostMoney/2
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
				BeginQuestEvent(sceneId);AddQuestText(sceneId, "您摧毁了本国的飞行器，您的PK值增加了");EndQuestEvent(sceneId);DispatchQuestTips(sceneId,idKiller)
				Msg2Player(sceneId,idKiller,"您摧毁了本国的飞行器，您的PK值增加了",8,2)				
			else
				BeginQuestEvent(sceneId);AddQuestText(sceneId, "您摧毁了本国的飞行器");EndQuestEvent(sceneId);DispatchQuestTips(sceneId,idKiller)
				Msg2Player(sceneId,idKiller,"您摧毁了本国的飞行器，您的PK值增加了", 8,2)			
			end			

		else
	        AddMoney(sceneId,idKiller,0,iCostMoney2)
		  	BeginQuestEvent(sceneId);AddQuestText(sceneId, "您摧毁了敌国的飞行器，并获得了奖励！");EndQuestEvent(sceneId);DispatchQuestTips(sceneId,idKiller)
			Msg2Player(sceneId,idKiller,format("您摧毁了敌国的飞行器，并获得了现银#{_MONEY%d}。", iCostMoney2),8,2)

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
			
			x300760_Abandon( sceneId, OwnerID  )

			local GuildTitle = ""
			if GetGuildID(sceneId,idKiller) ~= -1 then
				GuildTitle = GetGuildTitle(sceneId,idKiller)
			end
			local killerName = GetName(sceneId,idKiller)
			local Readme = "您的飞行器被"..Country..GuildTitle.."的玩家"..killerName.."摧毁，黑金押运任务失败！"
			if IsHideName(sceneId,idKiller) > 0 then
				Readme = "您的飞行器被"..HIDE_NAME.."摧毁，黑金押运任务失败！"
			end
		
			BeginQuestEvent(sceneId);AddQuestText(sceneId, "飞行器被摧毁！");EndQuestEvent(sceneId);DispatchQuestTips(sceneId,OwnerID);Msg2Player(sceneId,OwnerID,Readme,8,2)
		end
	else		--被怪杀死
		local OwnerID = GetBusMemberObjId(sceneId,BusId,0)
		if OwnerID ~= -1 then
			x300760_Abandon( sceneId, OwnerID  )
			local Readme = "您的飞行器被怪物摧毁！"
			BeginQuestEvent(sceneId);AddQuestText(sceneId, "飞行器被摧毁！");EndQuestEvent(sceneId);DispatchQuestTips(sceneId,OwnerID);Msg2Player(sceneId,OwnerID,Readme,8,2)
		end
	end

end


function x300760_OnTime(sceneId,BusId)

end

function x300760_OnLifeTimeOut(sceneId,BusId)
    local selfId = GetBusMemberObjId(sceneId,BusId,0)
    if(IsPlayerStateNormal(sceneId, selfId) ~= 0) then
		x300760_Abandon( sceneId, selfId  )
	end
	DeleteBus(sceneId, BusId,1)
end

function x300760_OnWaitTimeOut(sceneId,BusId)

	local selfId = GetBusMemberObjId(sceneId,BusId,0)
	if(IsPlayerStateNormal(sceneId, selfId) ~= 0) then
		x300760_Abandon( sceneId, selfId  )
		local strText = "由于您离开护送目标时间过久或护送目标已被击杀，您的护送目标消失了，任务失败！"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, strText);
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,strText,8,2)
	end
	DeleteBus(sceneId, BusId,1)
end

function x300760_OnBusStopWhenOwnerFarAway(sceneId, ownerId)
	local strText = "很抱歉，由于您离开#G运金飞行器#W#o过远，飞行器迷失方向停止前进！"
	BeginQuestEvent(sceneId)
	AddQuestText(sceneId, strText);
	EndQuestEvent(sceneId)
	DispatchQuestTips(sceneId, ownerId)
	Msg2Player(sceneId,ownerId,strText,8,2)
end




--********************************************************************
--放弃
--********************************************************************
function x300760_Abandon( sceneId, selfId )

	for i,itm in x300760_g_MissionId do
		
		if IsHaveQuestNM( sceneId, selfId, itm.ID) ~= 0 then	-- 如果有这个任务
			
			DelQuestNM( sceneId, selfId, itm.ID)
			x300760_SetDayCount(sceneId, selfId)
			return
		end
	end

end

--********************************************************************
--放弃
--********************************************************************
function x300760_CleaupMission( sceneId, selfId )

	for i,itm in x300760_g_MissionId do
		
		if IsHaveQuestNM( sceneId, selfId, itm.ID) ~= 0 then	-- 如果有这个任务
			
			DelQuestNM( sceneId, selfId, itm.ID)
			local Readme = "由于您离开护送目标时间过久或护送目标已被击杀，您的护送目标消失了，任务失败！"
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, Readme);
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
			Msg2Player(sceneId,selfId,Readme,8,2)
			x300760_SetDayCount(sceneId, selfId)
			return
		end
	end

end

---------------------------------------------------------------------------------------------------
--更新当天接任务次数
---------------------------------------------------------------------------------------------------
function x300760_SetDayCount(sceneId, selfId)
	local today = GetDayOfYear()

	local lastday = GetQuestData(sceneId, selfId, MD_PAO_QIAN_DATE[1], MD_PAO_QIAN_DATE[2], MD_PAO_QIAN_DATE[3])

	if lastday ~= today then
		SetQuestData(sceneId, selfId, MD_PAO_QIAN_DATE[1], MD_PAO_QIAN_DATE[2], MD_PAO_QIAN_DATE[3], today)
		SetQuestData(sceneId, selfId, MD_PAO_QIAN_COUNT[1], MD_PAO_QIAN_COUNT[2], MD_PAO_QIAN_COUNT[3], 1)
	else
		local daycount = GetQuestData(sceneId, selfId, MD_PAO_QIAN_COUNT[1], MD_PAO_QIAN_COUNT[2], MD_PAO_QIAN_COUNT[3])
		SetQuestData(sceneId, selfId, MD_PAO_QIAN_COUNT[1], MD_PAO_QIAN_COUNT[2], MD_PAO_QIAN_COUNT[3], daycount+1)
	end
end