

x310071_g_ScriptId = 310071

x310071_g_GodIndex = 1210

x310071_g_MainScriptId = 310070

x310071_g_MissionList = {8080,8081,8082,8083,8084,8085,8086,8087,8088,8089,8090}

--**********************************

--任务入口函数

--**********************************

function x310071_ProcEventEntry(sceneId, selfId, targetId)	--点击该任务后执行此脚本

end

--**********************************

--列举事件

--**********************************
function x310071_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
	--AddQuestNumText(sceneId, x310071_g_ScriptId, x310071_g_MissionName);
end


function x310071_OnCreateBus( sceneId, selfId,MissionId,BusID )

  local PosX,PosZ = GetWorldPos(sceneId, selfId)

	local ObjID = CreateBus(sceneId, BusID, PosX, PosZ, 3, 3, 310071, selfId, x310071_g_GodIndex,MissionId,targetId)
end

function x310071_OnCreateBusOK(sceneId, selfId,busId,targetId,MissionId)	

	SetBusTimerTick(sceneId , busId, 1000)
	SetBusWaitTime(sceneId , busId, 300)
	SetBusTimerOpen(sceneId, busId, 0)
	SetBusCurCamp(sceneId, busId,20)
	SetBusQuestID(sceneId,busId,MissionId)
	
	--回调原来的脚本
	local index = -1
		
	if MissionId == 8080 then
		CallScriptFunction( 310070, "OnCreateBusOK", sceneId, selfId ,busId,targetId,MissionId)	
	elseif MissionId >= 8081 and  MissionId <= 8085 then
		index = MissionId - 8081 + 1
		CallScriptFunction( 310072, "OnCreateBusOK", sceneId, selfId ,busId,targetId,MissionId,index)
	elseif MissionId >= 8086 and  MissionId <= 8090 then
		index = MissionId - 8086 + 1
		CallScriptFunction( 310073, "OnCreateBusOK", sceneId, selfId ,busId,targetId,MissionId,index)
	end
end


function x310071_DeleteBus(sceneId, ObjId)

	DeleteBus(sceneId, ObjId,1)

end


--玩家请求进入BUS
--selfId：玩家ID
--targetId：BUSID
function x310071_OnIntoBusEvent(sceneId, selfId,targetId)
	local IsOwner = IsTheBusOwner(sceneId, selfId, targetId )
	if IsOwner == 1 then
		--进入BUS
		AddBusMember(sceneId, selfId,targetId)
	end
end

function x310071_OnIntoBusAfter(sceneId, selfId,BusID)

end

--玩家离开BUS
--selfId：玩家ID
function x310071_OnLeaveBusEvent(sceneId, selfId,BusId)
		
end


function x310071_OnDie(sceneId,BusId,idKiller)

    if(IsObjValid (sceneId,BusId) ~= 1)then
        return
    end

	if idKiller == -1 then
		--自死亡，目前只用于将玩家投入监狱前删除镖车
		local OwnerID = GetBusMemberObjId(sceneId,BusId,0)
		if OwnerID ~= -1 then
			local Readme = "#R您的护送目标被杀死，护送任务失败！"
			BeginQuestEvent(sceneId);
			AddQuestText(sceneId, Readme);
			EndQuestEvent(sceneId);
			DispatchQuestTips(sceneId,OwnerID)
			Msg2Player(sceneId,OwnerID,Readme,8,2)
			
			for i, item in x310071_g_MissionList do
				if IsHaveQuestNM( sceneId, OwnerID, item ) > 0 then
					DelQuestNM( sceneId, OwnerID, item)
					break;
				end
			end
		end
		return
	end

	if GetObjType(sceneId,idKiller) == 1 then     --被玩家杀死
	
		local BusMisId = GetBusQuestID( sceneId,BusId )


		local OwnerCountry = GetBusCountryID(sceneId,BusId)
		local KillerCountry = GetCurCountry(sceneId,idKiller)
		
		local OwnerID = GetBusMemberObjId(sceneId,BusId,0)

		if OwnerID ~= -1 then
			if(IsPlayerStateNormal(sceneId, OwnerID) ~= 0) then
				local Readme = "您的护送目标杀死，任务失败！"
				BeginQuestEvent(sceneId);
				AddQuestText(sceneId, "您的护送目标杀死，任务失败！");
				EndQuestEvent(sceneId);
				DispatchQuestTips(sceneId,OwnerID);
				Msg2Player(sceneId,OwnerID,Readme,8,2)

				for i, item in x310071_g_MissionList do
					if IsHaveQuestNM( sceneId, OwnerID, item ) > 0 then
						DelQuestNM( sceneId, OwnerID, item)
						break;
					end
				end
			end
		end
	else		--被怪杀死
		local OwnerID = GetBusMemberObjId(sceneId,BusId,0)
		if OwnerID ~= -1 then
			if(IsPlayerStateNormal(sceneId, OwnerID) ~= 0) then
				local Readme = "您的护送目标杀死，任务失败！"
				BeginQuestEvent(sceneId);
				AddQuestText(sceneId, "您的护送目标杀死，任务失败！");
				EndQuestEvent(sceneId);
				DispatchQuestTips(sceneId,OwnerID);
				Msg2Player(sceneId,OwnerID,Readme,8,2)

				for i, item in x310071_g_MissionList do
					if IsHaveQuestNM( sceneId, OwnerID, item ) > 0 then
						DelQuestNM( sceneId, OwnerID, item)
						break;
					end
				end
			end
		end
	end

end


function x310071_OnTime(sceneId,BusId)

end

function x310071_OnLifeTimeOut(sceneId,BusId)
    local selfId = GetBusMemberObjId(sceneId,BusId,0)
    
	DeleteBus(sceneId, BusId,1)

	if(IsPlayerStateNormal(sceneId, selfId) ~= 0) then
		local strText = "您的护送目标消失了，任务失败！"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, strText);
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,strText,8,2)
		

		for i, item in x310071_g_MissionList do
			if IsHaveQuestNM( sceneId, selfId, item ) > 0 then
				DelQuestNM( sceneId, selfId, item)
				break;
			end
		end
	end

end

function x310071_OnWaitTimeOut(sceneId,BusId)
	local selfId = GetBusMemberObjId(sceneId,BusId,0)
	if(IsPlayerStateNormal(sceneId, selfId) ~= 0) then
		local strText = "由于您离开护送目标时间过久，您的护送目标消失了，任务失败！"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, strText);
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,strText,8,2)
		

		for i, item in x310071_g_MissionList do
			if IsHaveQuestNM( sceneId, selfId, item ) > 0 then
				DelQuestNM( sceneId, selfId, item)
				break;
			end
		end
	end
	DeleteBus(sceneId, BusId,1)
end

function x310071_OnBusStopWhenOwnerFarAway(sceneId, ownerId)
	local strText = "很抱歉，您的护送目标离您过远，护送目标停止移动！"
	BeginQuestEvent(sceneId)
	AddQuestText(sceneId, strText);
	EndQuestEvent(sceneId)
	DispatchQuestTips(sceneId, ownerId)
	Msg2Player(sceneId,ownerId,strText,8,2)
end

function x310071_OnLogInOrDie(sceneId, selfId)
	
	for i, item in x310071_g_MissionList do
		if IsHaveQuestNM( sceneId, selfId, item ) > 0 then
			local strText = "您的护送目标消失了，任务失败！"
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, strText);
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
			Msg2Player(sceneId,selfId,strText,8,2)
			DelQuestNM( sceneId, selfId, item)
			break;
		end
	end
	
end
