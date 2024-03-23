--功能：战车的默认脚本


x911117_g_ScriptId = 911117
x911117_g_MissionName = "创建镖车"

--无敌impact在表中的索引,玩家进入BUS后获得一个无敌impact,
x911117_g_GodIndex = 1210
x911117_g_Carinfo = {CarType = 3,BaseAI = 3,AIScript = 3,Script = 911117 }


--**********************************

--任务入口函数

--**********************************

function x911117_ProcEventEntry(sceneId, selfId, targetId)	--点击该任务后执行此脚本
	
	--请求创建战车，
	local PosX,PosZ = GetWorldPos(sceneId, selfId)

	local ObjID = CreateBus(sceneId, x911117_g_Carinfo.CarType, PosX, PosZ, x911117_g_Carinfo.BaseAI, x911117_g_Carinfo.AIScript, x911117_g_Carinfo.Script, selfId, x911117_g_GodIndex,-1,targetId)
	
end

--**********************************

--bus创建成功处理

--**********************************
function x911117_OnCreateBusOK(sceneId,selfId,busId,targetId,MissionId)
	
	local CarName = GetName( sceneId, selfId ).." 的镖车"
	SetBusTitle(sceneId , busId, CarName)
	SetBusTimerTick(sceneId ,busId, 1000)
	SetBusWaitTime(sceneId , busId, 5)
	SetBusLifeTime(sceneId , busId, 120)
	SetBusTimerOpen(sceneId, busId, 0)
	
	BeginQuestEvent(sceneId)
	AddQuestText(sceneId,"你创建了一辆镖车，它将自动跟随你移动。如果你离开它超过15米持续5秒钟，该镖车将会自动消失。2分钟后，该镖车也将会自动消失。")
	EndQuestEvent( )	
	DispatchQuestEventList(sceneId,selfId,targetId)
	
	BeginQuestEvent(sceneId)
	AddQuestText(sceneId,"你创建了一辆镖车");
	EndQuestEvent()
	DispatchQuestTips(sceneId,selfId)
end



function x911117_DeleteBus(sceneId, ObjId)
		
	DeleteBus(sceneId, ObjId,1)

end


--**********************************

--列举事件

--**********************************
function x911117_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
	AddQuestNumText(sceneId, x911117_g_ScriptId, x911117_g_MissionName);
end



--ObjId:BUSID
function x911117_DeleteBus(sceneId, ObjId)
		
	DeleteBus(sceneId, ObjId,1)

end

--玩家请求进入BUS
--selfId：玩家ID
--targetId：BUSID
function x911117_OnIntoBusEvent(sceneId, selfId,targetId)
--	print("123")
	local InBus = IsBusMember(sceneId, selfId)
	if InBus == 1 then
		BeginQuestEvent(sceneId)
		  	AddQuestText(sceneId,"你已经有镖车了");
		EndQuestEvent()
		DispatchQuestTips(sceneId,selfId)
		return 
	end
			
	local BusSize = GetBusSize(sceneId,targetId) 
	local MemberNum = GetBusMemberCount(sceneId,targetId)
	
	if BusSize<=MemberNum  then
		BeginQuestEvent(sceneId)
		  	AddQuestText(sceneId,"这辆镖车已经有人运了");
		EndQuestEvent()
		DispatchQuestTips(sceneId,selfId)
		return
	end
	
	local IsOwner = IsTheBusOwner(sceneId, selfId, targetId )	
	if IsOwner == 1 then
		--进入BUS
		AddBusMember(sceneId, selfId,targetId)
	end
end

--玩家离开BUS
--selfId：玩家ID
function x911117_OnLeaveBusEvent(sceneId, selfId,BusId)
		BeginQuestEvent(sceneId)
		  AddQuestText(sceneId,"你正在运镖，无法离开");
		EndQuestEvent()
		DispatchQuestTips(sceneId,selfId)
end


function x911117_OnTime(sceneId,BusId)

end

function x911117_OnLifeTimeOut(sceneId,BusId)
	DeleteBus(sceneId, BusId,1)
end

function x911117_OnWaitTimeOut(sceneId,BusId)
	DeleteBus(sceneId, BusId,1)
end

function x911117_OnBusStopWhenOwnerFarAway(sceneId, ownerId)
end

function x911117_OnDie(sceneId,BusId,idKiller)
end