--功能：战车的修改脚本脚本


x911116_g_ScriptId = 911116
x911116_g_MissionName = "镖车/BUS 切换"



--**********************************

--任务入口函数

--**********************************

function x911116_ProcEventEntry(sceneId, selfId, targetId)	--点击该任务后执行此脚本
	local IsDriver = IsBusLeader(sceneId , selfId)
	
	if IsDriver == 1 then
		local BusObjID = GetBusId(sceneId,selfId)
		local BusType = GetBusType(sceneId, BusObjID)
		local BusIndex = GetBusIndex(sceneId, BusObjID)	
		
		if BusType == 1 and BusIndex == 2 then	
			local AIStr = "你的镖车转变为BUS"
			if BusType == 1 then
				BusChangeState(sceneId, BusObjID)
				AIStr = "你的镖车转变为BUS"
				local CarName = GetName( sceneId, selfId ).." 的BUS"
				SetBusTitle(sceneId , BusObjID, CarName)
			elseif BusType == 0 then 
				BusChangeState(sceneId, BusObjID)
				AIStr = "你的BUS转变为镖车"
				local CarName = GetName( sceneId, selfId ).." 的镖车"
				SetBusTitle(sceneId , BusObjID, CarName)
			end
			BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"测试用，设置你控制的车在镖车和BUS之间切换”。#G目前"..AIStr.."#W。")
			EndQuestEvent( )	
			DispatchQuestEventList(sceneId,selfId,targetId)
			
			BeginQuestEvent(sceneId)
			  AddQuestText(sceneId,AIStr);
			EndQuestEvent()
			DispatchQuestTips(sceneId,selfId)
		end
	end	
end


--**********************************

--列举事件

--**********************************
function x911116_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
	AddQuestNumText(sceneId, x911116_g_ScriptId, x911116_g_MissionName);
end


function x911116_OnDie(sceneId,BusId,idKiller)
end