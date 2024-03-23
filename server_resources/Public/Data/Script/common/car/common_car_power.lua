--功能：战车的修改脚本脚本


x911115_g_ScriptId = 911115
x911115_g_MissionName = "系统控制"



--**********************************

--任务入口函数

--**********************************

function x911115_ProcEventEntry(sceneId, selfId, targetId)	--点击该任务后执行此脚本
	local IsDriver = IsBusLeader(sceneId , selfId)
		
	if IsDriver == 1 then
		local BusObjID = GetBusId(sceneId,selfId)
		local BusType  = GetBusType(sceneId, BusObjID)
		local BusIndex = GetBusIndex(sceneId, BusObjID)	
	
		if BusType == 1 and BusIndex == 2 then			
				SetBusSysControl(sceneId, BusObjID, 1)
				local AIStr = "系统控制"

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
			  AddQuestText(sceneId,"镖车本来就是跟随你的了哦");
			EndQuestEvent()
			DispatchQuestTips(sceneId,selfId)
		elseif BusIndex == 1 then	
			BeginQuestEvent(sceneId)
			  AddQuestText(sceneId,"系统BUS还要系统控制？不要玩我啊");
			EndQuestEvent()
			DispatchQuestTips(sceneId,selfId)
		end
	end	
end


--**********************************

--列举事件

--**********************************
function x911115_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
	AddQuestNumText(sceneId, x911115_g_ScriptId, x911115_g_MissionName);
end

function x911115_OnDie(sceneId,BusId,idKiller)
end