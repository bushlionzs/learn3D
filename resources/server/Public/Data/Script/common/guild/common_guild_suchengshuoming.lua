--MisDescBegin 
x300830_g_ScriptId 					= 	300830
x300830_g_MissionName				= 	"帮会速成" 
x300830_g_MissionInfo				= 	"巡按任务信息" 
--MisDescEnd

function x300830_ProcEnumEvent( sceneId, selfId, targetId )
end

function x300830_ProcEventEntry(sceneId, selfId,targetId)	--点击该任务后执行此脚本
		BeginQuestEvent(sceneId)
		local Readme_1 = "#Y【帮会速成说明】#r#W"
		local Readme_2 = "  1.#G接取任务：#W首先服务器中有1个4级及以上的帮会，该任务才会开启。必须为低于最高等级帮会2级（含2级）以下的达到40级的帮会成员，花费1两现金/金卡才可接受任务。#r"
		local Readme_3 = "  2.#G任务途中：#W帮会成员可一同前往完成任务，如果杀死相应的魔君爪牙后，周围同帮会玩家均可完成该任务。#r"
		local Readme_4 = "  3.#G回复成功：#W完成此任务请在当日进行回复，如隔日回复将造成当日无法接取此任务。#r"
		local Readme_5 = "  4.#G任务奖励：#W成功完成此任务，您将获得一颗还魂丹，帮会经验，帮贡奖励。"
		local Readme = Readme_1..Readme_2..Readme_3..Readme_4..Readme_5
		AddQuestText(sceneId, Readme);EndQuestEvent(sceneId);DispatchQuestInfo( sceneId, selfId, targetId, x300830_g_ScriptId, -1 );
end 

function x300830_ProcAcceptCheck( sceneId, selfId, NPCId )

end



--**********************************
--接受
--**********************************
function x300830_ProcAccept( sceneId, selfId )
end
--**********************************
--放弃
--**********************************
function x300830_ProcQuestAbandon( sceneId, selfId, MissionId )
end
--**********************************
--继续
--**********************************
function x300830_OnContinue( sceneId, selfId, targetId )
end
--**********************************
--检测是否可以提交
--**********************************
function x300830_CheckSubmit( sceneId, selfId )
end
--**********************************
--提交
--**********************************
function x300830_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end
--**********************************
--杀死怪物或玩家
--**********************************
function x300830_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end
--**********************************
--进入区域事件
--**********************************
function x300830_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end
--**********************************
--道具改变
--**********************************
function x300830_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end