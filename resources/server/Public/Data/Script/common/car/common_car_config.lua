--功能：战车的修改脚本脚本


x911114_g_ScriptId = 911114
x911114_g_MissionName = "进入BUS是否需要司机确认 切换"



--**********************************

--任务入口函数

--**********************************

function x911114_ProcEventEntry(sceneId, selfId, targetId)	--点击该任务后执行此脚本
	local IsDriver = IsBusLeader(sceneId , selfId)
	
	if IsDriver == 1 then
		local BusObjID = GetBusId(sceneId,selfId)
		local BusType  = GetBusType(sceneId, BusObjID)
		local BusIndex = GetBusIndex(sceneId, BusObjID)	
		
		if BusType == 1 and BusIndex == 2 then	
			local AIStr = "进入你的BUS不需要通过你确认"
			if random(1,2) == 1 then
				SetBusLeaderFiatMode(sceneId, BusObjID, 0)
				AIStr = "进入你的BUS不需要通过你确认"
			else
				SetBusLeaderFiatMode(sceneId, BusObjID, 1)
				AIStr = "进入你的BUS需要通过你确认"
			end
			BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"测试用，每次有一半的概率被设置为“进入BUS需要司机确认”，一半的概率被设置为“进入BUS不需要司机确认”。#G目前"..AIStr.."#W。")
			EndQuestEvent( )	
			DispatchQuestEventList(sceneId,selfId,targetId)
			
			BeginQuestEvent(sceneId)
			  AddQuestText(sceneId,AIStr);
			EndQuestEvent()
			DispatchQuestTips(sceneId,selfId)
		elseif BusIndex == 3 then	
			BeginQuestEvent(sceneId)
			  AddQuestText(sceneId,"镖车是很专一的，不会随便让别人上来坐的，所以……");
			EndQuestEvent()
			DispatchQuestTips(sceneId,selfId)
		elseif BusIndex == 1 then	
			BeginQuestEvent(sceneId)
			  AddQuestText(sceneId,"系统BUS都没司机，你让我怎么换，所以……");
			EndQuestEvent()
			DispatchQuestTips(sceneId,selfId)
		end
	end	
end


--**********************************

--列举事件

--**********************************
function x911114_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
	AddQuestNumText(sceneId, x911114_g_ScriptId, x911114_g_MissionName);
end


function x911114_OnDie(sceneId,BusId,idKiller)
end