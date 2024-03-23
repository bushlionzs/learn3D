--MisDescBegin 
x300773_g_ScriptId 					= 	300773
x300773_g_MissionName				= 	"收集黑木"
x300773_g_MissionInfo				= 	"巡按任务信息" 
--MisDescEnd

function x300773_ProcEnumEvent( sceneId, selfId, targetId )
end

function x300773_ProcEventEntry(sceneId, selfId,targetId)	--点击该任务后执行此脚本
		BeginQuestEvent(sceneId)
		local Readme_1 = "#Y【帮务任务说明】#r#W"
		local Readme_2 = "  1.#G发布任务：#W帮务任务只有帮主和副帮主可以发布，发布任务后，限时#G2小时#W内完成，超时无效。#r"
		local Readme_3 = "  2.#G发布周期：#W每天可以在帮务任务中选择：#r#Y【帮会】护兽令#r【帮会】收集令#r【帮会】暗战令#r【帮会】除妖令#r【帮会】募集令#r#W其中一种，每周相同的帮务任务只允许发布一次。#r"
		local Readme_4 = "  3.#G任务途中：#W帮会成员间组队前往，可加快任务完成的速度。#r"
		local Readme_5 = "  4.#G回复成功：#W在完成此任务后，务必在时限内回复，否则只能获得基本奖励。#r"
		local Readme_6 = "  5.#G任务奖励：#W帮会成员获得#G双倍#W任务奖励，副帮主获得#G三倍#W任务奖励，帮主获得#G四倍#W任务奖励。#r" 
		local Readme = Readme_1..Readme_2..Readme_3..Readme_4..Readme_5..Readme_6
		AddQuestText(sceneId, Readme);EndQuestEvent(sceneId);DispatchQuestInfo( sceneId, selfId, targetId, x300773_g_ScriptId, -1 );
end 

function x300773_ProcAcceptCheck( sceneId, selfId, NPCId )

end



--**********************************
--接受
--**********************************
function x300773_ProcAccept( sceneId, selfId )
end
--**********************************
--放弃
--**********************************
function x300773_ProcQuestAbandon( sceneId, selfId, MissionId )
end
--**********************************
--继续
--**********************************
function x300773_OnContinue( sceneId, selfId, targetId )
end
--**********************************
--检测是否可以提交
--**********************************
function x300773_CheckSubmit( sceneId, selfId )
end
--**********************************
--提交
--**********************************
function x300773_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end
--**********************************
--杀死怪物或玩家
--**********************************
function x300773_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end
--**********************************
--进入区域事件
--**********************************
function x300773_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end
--**********************************
--道具改变
--**********************************
function x300773_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end