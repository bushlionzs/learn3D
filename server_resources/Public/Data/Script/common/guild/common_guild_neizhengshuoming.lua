--MisDescBegin 
x300784_g_ScriptId 					= 	300784
x300784_g_MissionName				= 	"收集黑木"
x300784_g_MissionInfo				= 	"巡按任务信息" 
--MisDescEnd

function x300784_ProcEnumEvent( sceneId, selfId, targetId )
end

function x300784_ProcEventEntry(sceneId, selfId,targetId)	--点击该任务后执行此脚本
		BeginQuestEvent(sceneId)
		local Readme_1 = "#Y【帮会贡品说明】#r#W"
		local Readme_2 = "    帮会贡品任务，分为#G寻物#W和#G送信#W两种，您只需要按照帮会任务发布人的要求完成任务，就可以获得#G经验#W和#G帮贡#W的奖励。#r"
		local Readme = Readme_1..Readme_2
		AddQuestText(sceneId, Readme);EndQuestEvent(sceneId);DispatchQuestInfo( sceneId, selfId, targetId, x300784_g_ScriptId, -1 );
end 

function x300784_ProcAcceptCheck( sceneId, selfId, NPCId )

end



--**********************************
--接受
--**********************************
function x300784_ProcAccept( sceneId, selfId )
end
--**********************************
--放弃
--**********************************
function x300784_ProcQuestAbandon( sceneId, selfId, MissionId )
end
--**********************************
--继续
--**********************************
function x300784_OnContinue( sceneId, selfId, targetId )
end
--**********************************
--检测是否可以提交
--**********************************
function x300784_CheckSubmit( sceneId, selfId )
end
--**********************************
--提交
--**********************************
function x300784_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end
--**********************************
--杀死怪物或玩家
--**********************************
function x300784_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end
--**********************************
--进入区域事件
--**********************************
function x300784_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end
--**********************************
--道具改变
--**********************************
function x300784_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end