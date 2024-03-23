--MisDescBegin 
x300771_g_ScriptId 					= 	300771
x300771_g_MissionName				= 	"仙人谷收集" 
x300771_g_MissionInfo				= 	"巡按任务信息" 
--MisDescEnd

function x300771_ProcEnumEvent( sceneId, selfId, targetId )
end

function x300771_ProcEventEntry(sceneId, selfId,targetId)	--点击该任务后执行此脚本
		BeginQuestEvent(sceneId)
		local Readme_1 = "#Y【帮会图腾说明】#r#W"
		local Readme_2 = "  1.#G接取任务：#W帮会中，等级不低于#G40级#W的帮会成员，每天可以自行接取此任务，会根据等级段不同，给予不同的任务。#r"
		local Readme_3 = "  2.#G任务途中：#W帮会成员间组队前往，可增加个人的安全。#r"
		local Readme_4 = "  3.#G回复成功：#W完成此任务，请务必在当日进行回复，如隔日回复将造成当日无法接取此任务。#r"
		local Readme_5 = "  4.#G任务奖励：#W成功完成此任务，您将获得高额的经验，帮贡奖励。" 
		local Readme = Readme_1..Readme_2..Readme_3..Readme_4..Readme_5
		AddQuestText(sceneId, Readme);EndQuestEvent(sceneId);DispatchQuestInfo( sceneId, selfId, targetId, x300771_g_ScriptId, -1 );
end 

function x300771_ProcAcceptCheck( sceneId, selfId, NPCId )

end



--**********************************
--接受
--**********************************
function x300771_ProcAccept( sceneId, selfId )
end
--**********************************
--放弃
--**********************************
function x300771_ProcQuestAbandon( sceneId, selfId, MissionId )
end
--**********************************
--继续
--**********************************
function x300771_OnContinue( sceneId, selfId, targetId )
end
--**********************************
--检测是否可以提交
--**********************************
function x300771_CheckSubmit( sceneId, selfId )
end
--**********************************
--提交
--**********************************
function x300771_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end
--**********************************
--杀死怪物或玩家
--**********************************
function x300771_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end
--**********************************
--进入区域事件
--**********************************
function x300771_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end
--**********************************
--道具改变
--**********************************
function x300771_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end