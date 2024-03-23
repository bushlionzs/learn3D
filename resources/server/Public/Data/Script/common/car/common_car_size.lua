--功能：战车的修改脚本脚本


x911113_g_ScriptId = 911113
x911113_g_MissionName = "可乘人数 切换"



--**********************************

--任务入口函数

--**********************************

function x911113_ProcEventEntry(sceneId, selfId, targetId)	--点击该任务后执行此脚本
	local IsDriver = IsBusLeader(sceneId , selfId)
	
	if IsDriver == 1 then
		local BusObjID = GetBusId(sceneId,selfId)
		local Size = GetBusSize(sceneId, BusObjID)
		local MemCount = GetBusMemberCount(sceneId, BusObjID)
		local BusType  = GetBusType(sceneId, BusObjID)
		local BusIndex = GetBusIndex(sceneId, BusObjID)	
		
		if BusType == 1 and BusIndex == 2 then	
			Size = Size + 1
			if Size > 10 then
				Size = MemCount
				if Size == 0 then
					Size = 1
				end
			end
			SetBusMemberNum(sceneId, BusObjID, Size)
			local AIStr = "你的BUS可以乘坐"..Size.."人"
			
			BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"测试用，每次你的BUS可以乘坐的人数会#R＋1#W，当超过10人时，会返回到你当前BUS内的人数，重新计数。#G目前"..AIStr.."#W。")
			EndQuestEvent()	
			DispatchQuestEventList(sceneId,selfId,targetId)
			
			BeginQuestEvent(sceneId)
			  AddQuestText(sceneId,AIStr);
			EndQuestEvent()
			DispatchQuestTips(sceneId,selfId)
		elseif BusIndex == 3 then	
			BeginQuestEvent(sceneId)
			  AddQuestText(sceneId,"镖车是很专一的，可没有改变人数一说，所以……");
			EndQuestEvent()
			DispatchQuestTips(sceneId,selfId)
		elseif BusIndex == 1 then	
			BeginQuestEvent(sceneId)
			  AddQuestText(sceneId,"系统BUS不准超载行驶");
			EndQuestEvent()
			DispatchQuestTips(sceneId,selfId)
		end
	end
end


--**********************************

--列举事件

--**********************************
function x911113_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
	AddQuestNumText(sceneId, x911113_g_ScriptId, x911113_g_MissionName);
end

function x911113_OnDie(sceneId,BusId,idKiller)
end