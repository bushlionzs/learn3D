--功能：战车的默认脚本


x911111_g_ScriptId = 911111
x911111_g_MissionName = "创建共乘BUS"

--无敌impact在表中的索引,玩家进入BUS后获得一个无敌impact,
x911111_g_GodIndex = 1210
x911111_g_Carinfo = {CarType = 2,BaseAI = 3,AIScript = 3,Script = 911111 }


--**********************************

--任务入口函数

--**********************************

function x911111_ProcEventEntry(sceneId, selfId, targetId)	--点击该任务后执行此脚本
	
	--创建战车，
	local PosX,PosZ = GetWorldPos(sceneId, selfId)
	
	local ObjID = CreateBus(sceneId, x911111_g_Carinfo.CarType, PosX, PosZ, x911111_g_Carinfo.BaseAI, x911111_g_Carinfo.AIScript, x911111_g_Carinfo.Script, selfId, x911111_g_GodIndex,-1,targetId)
end
	
--**********************************

--bus创建成功处理

--**********************************
function x911111_OnCreateBusOK(sceneId,selfId,busId,targetId,MissionId)
	
	local CarName = GetName( sceneId, selfId ).." 的共乘BUS"
	SetBusTitle(sceneId , busId, CarName)
	SetBusTimerTick(sceneId , busId, 1000)
	SetBusWaitTime(sceneId , busId, 20)
	SetBusLifeTime(sceneId , busId, 300)
	SetBusTimerOpen(sceneId, busId, 0)
	SetBusLeaderFiatMode(sceneId, busId,1)
	
	BeginQuestEvent(sceneId)
	AddQuestText(sceneId,"你创建了一辆共乘BUS，目前可坐2人。5分钟后，将BUS将自动消失。如果空车持续20秒，该BUS也将自动消失。")
	EndQuestEvent()	
	DispatchQuestEventList(sceneId,selfId,targetId)
		
	BeginQuestEvent(sceneId)
	AddQuestText(sceneId,"你创建了一辆共乘BUS");
	EndQuestEvent()
	DispatchQuestTips(sceneId,selfId)
end


--**********************************

--列举事件

--**********************************
function x911111_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
	AddQuestNumText(sceneId, x911111_g_ScriptId, x911111_g_MissionName);
end



--ObjId:BUSID
function x911111_DeleteBus(sceneId, ObjId)
		
	DeleteBus(sceneId, ObjId,1)

end

--玩家请求进入BUS
--selfId：玩家ID
--targetId：BUSID
function x911111_OnIntoBusEvent(sceneId, selfId,targetId)
			
	local InBus = IsBusMember(sceneId, selfId)
	if InBus == 1 then
		BeginQuestEvent(sceneId)
		  	AddQuestText(sceneId,"你已经在BUS里了");
		EndQuestEvent()
		DispatchQuestTips(sceneId,selfId)
		return 
	end
			
	local BusSize = GetBusSize(sceneId,targetId) 
	local MemberNum = GetBusMemberCount(sceneId,targetId)
	
	if BusSize<=MemberNum  then
		BeginQuestEvent(sceneId)
		  	AddQuestText(sceneId,"战车已经人满为患了");
		EndQuestEvent()
		DispatchQuestTips(sceneId,selfId)
		return
	end
	
	local IsOwner = IsTheBusOwner(sceneId, selfId, targetId )	
	if IsOwner == 1 then
		--进入BUS
		AddBusMember(sceneId, selfId,targetId)
	else
		local BusSize = GetBusMemberCount( sceneId, targetId)	
		local BusMemberObjId
		local j = 0
		for i=1,BusSize do
			 BusMemberObjId = GetBusMemberObjId( sceneId,targetId,i-1)
			 if IsTheBusOwner(sceneId, BusMemberObjId, targetId ) == 1 then
			 	j = 1

			 end
		end
		if j == 0 then
			BeginQuestEvent(sceneId)
			  	AddQuestText(sceneId,"共乘BUS的主人还没进去呢，你就想进去？");
			EndQuestEvent()
			DispatchQuestTips(sceneId,selfId)
			return
		else
			--进入BUS
			AddBusMember(sceneId, selfId,targetId)
		end 
	end
end

--玩家离开BUS
--selfId：玩家ID
function x911111_OnLeaveBusEvent(sceneId, selfId,BusId)
	 DelBusMember(sceneId, selfId,BusId)
	--local MemberNum = GetBusMemberCount(sceneId,BusId)
	--if MemberNum == 0 then
	--	DeleteBus(sceneId, BusId,1)
	--end
end



function x911111_OnTime(sceneId,BusId)

end

function x911111_OnLifeTimeOut(sceneId,BusId)
	DeleteBus(sceneId, BusId,1)
end

function x911111_OnWaitTimeOut(sceneId,BusId)
	DeleteBus(sceneId, BusId,1)
end

function x911111_OnBusStopWhenOwnerFarAway(sceneId, ownerId)
end

function x911111_OnDie(sceneId,BusId,idKiller)
end