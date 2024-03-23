function x300741_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	
	--	AddQuestNumText(sceneId,300741,"【个人】夺旗介绍",1);
	
end
function x300741_ProcEventEntry( sceneId, selfId, targetId )	--点击该任务后执行此脚本

	local Readme_1 = "#Y【夺旗】介绍#W#r"
	
	local Readme_2 = "\t当您达到40级时，您将可以接取夺旗系列任务。#r"
	
	local Readme_3 = "\t您可以接取#G国家守边#W，#G异国杀怪#W，#G敌国刺探#W和#G敌国情报#W四个任务。完成这些任务，可以获得#G高额奖励#W。"
	
	local Readme = Readme_1..Readme_2..Readme_3
	
	BeginQuestEvent(sceneId);AddQuestText(sceneId,Readme)
	
	AddQuestNumText(sceneId,300743,"国家守边",0,1)
	
	AddQuestNumText(sceneId,300742,"异国杀怪",0,1)
	
	AddQuestNumText(sceneId,300744,"敌国刺探",0,1)
	
	AddQuestNumText(sceneId,300745,"敌国情报",0,1)
	
	EndQuestEvent(sceneId);DispatchQuestEventList(sceneId,selfId,targetId)
	
end

--**********************************
--列举事件
--**********************************



--********************
--检测接受条件
--**********************************
function x300741_ProcAcceptCheck( sceneId, selfId, NPCId )
		return 1
end

--**********************************
--接受
--**********************************
function x300741_ProcAccept( sceneId, selfId )

end

--**********************************
--放弃
--**********************************
function x300741_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--继续
--**********************************
function x300741_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--检测是否可以提交
--**********************************
function x300741_CheckSubmit( sceneId, selfId )

end

--**********************************
--提交
--**********************************
function x300741_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--杀死怪物或玩家
--**********************************
function x300741_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--进入区域事件
--**********************************
function x300741_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--道具改变
--**********************************
function x300741_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
