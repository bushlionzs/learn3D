--功能：战车的修改脚本脚本


x911112_g_ScriptId = 911112
x911112_g_MissionName = "可被攻击/无敌 切换"



--**********************************

--任务入口函数

--**********************************

function x911112_ProcEventEntry(sceneId, selfId, targetId)	--点击该任务后执行此脚本

	local IsDriver = IsBusLeader(sceneId , selfId)
	
	if IsDriver == 1 then
		local BusObjID = GetBusId(sceneId,selfId)
		local BusType  = GetBusType(sceneId, BusObjID)
		local BusIndex = GetBusIndex(sceneId, BusObjID)	
		
		if BusType == 1 and BusIndex == 2 then
			local AIStr = "你的战车处于可被攻击状态"
			if random(1,2) == 1 then
				SetBusAIType(sceneId, BusObjID, 7)
				AIStr = "你的战车处于可被攻击状态"
			else
				SetBusAIType(sceneId, BusObjID, 3)
				AIStr = "你的战车处于无敌状态"
			end
			BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"测试用，每次有一半的概率被设置为“无敌状态”，即不可被攻击；一半的概率被设置为“可被攻击状态”，即可受攻击被摧毁。#G目前"..AIStr.."#W。")
			EndQuestEvent( )	
			DispatchQuestEventList(sceneId,selfId,targetId)
			
			BeginQuestEvent(sceneId)
			  AddQuestText(sceneId,AIStr);
			EndQuestEvent()
			DispatchQuestTips(sceneId,selfId)
		elseif BusIndex == 3 then
			BeginQuestEvent(sceneId)
			  AddQuestText(sceneId,"镖车暂时不希望能够更改攻击状态");
			EndQuestEvent()
			DispatchQuestTips(sceneId,selfId)
		elseif BusIndex == 1 then
			BeginQuestEvent(sceneId)
			  AddQuestText(sceneId,"系统BUS暂时不希望能够更改攻击状态");
			EndQuestEvent()
			DispatchQuestTips(sceneId,selfId)
		end
			
	end	
end


--**********************************

--列举事件

--**********************************
function x911112_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
	AddQuestNumText(sceneId, x911112_g_ScriptId, x911112_g_MissionName);
end

function x911112_OnDie(sceneId,BusId,idKiller)
end