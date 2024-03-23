--**********************************
--任务入口函数
--**********************************
function x300775_ProcEventEntry( sceneId, selfId, targetId )	--点击该任务后执行此脚本
	BeginQuestEvent(sceneId);
	
	local Readme_1 = "#Y【国家守边之守卫边塞】介绍#W#r"
	
	local Readme_2 = "\t当您达到40级时，您将可以在王城苏儿台接取国家守边任务，我这里是领取和回复国家守边第二步守卫边塞任务的。#r"
	
	local Readme_3 = "\t#W任务期间死亡，离线或超时，任务自动置成失败状态，找我重新领取。" 
	
	local Readme = Readme_1..Readme_2..Readme_3
	
	AddQuestText(sceneId,Readme)
	
	EndQuestEvent(sceneId);DispatchQuestEventList(sceneId,selfId,targetId)
	
end

--**********************************
--列举事件
--**********************************
function x300775_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	local Level = GetLevel(sceneId, selfId)--判断是否大于40级
	if Level >= 40 then
		AddQuestNumText(sceneId,300775,"【国家守边之守卫边塞】介绍",5);
	end
end


--********************
--检测接受条件
--**********************************
function x300775_ProcAcceptCheck( sceneId, selfId, NPCId )
		return 1
end

--**********************************
--接受
--**********************************
function x300775_ProcAccept( sceneId, selfId )

end

--**********************************
--放弃
--**********************************
function x300775_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--继续
--**********************************
function x300775_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--检测是否可以提交
--**********************************
function x300775_CheckSubmit( sceneId, selfId )

end

--**********************************
--提交
--**********************************
function x300775_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--杀死怪物或玩家
--**********************************
function x300775_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--进入区域事件
--**********************************
function x300775_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--道具改变
--**********************************
function x300775_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
