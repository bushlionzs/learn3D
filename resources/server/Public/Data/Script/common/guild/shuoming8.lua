--MisDescBegin 
x300774_g_ScriptId 					= 	300774
x300774_g_MissionName				= 	"护送神兽" 
x300774_g_MissionInfo				= 	"巡按任务信息" 
--MisDescEnd

function x300774_ProcEnumEvent( sceneId, selfId, targetId )
end

function x300774_ProcEventEntry(sceneId, selfId,targetId)	--点击该任务后执行此脚本
		BeginQuestEvent(sceneId)
		local Readme_1  = "#Y【帮会神兽说明】#r#W"
		local Readme_2  = "  1.#G接取任务：#W帮主每天付出押金10两现银就可领取护送任务。#r"
		local Readme_3  = "  2.#G任务共享：#W帮主领取任务时，帮主周围的本帮成员均可收到任务共享确认窗口，帮众可自行决定是否参与到护送任务中。#r"
		local Readme_4  = "  3.#G护送途中：#W神兽只跟随帮主进行移动，帮主离开过远，神兽将停止移动。帮主可通过屏幕下方的成员列表来踢除灰色名字的成员。#r"
		local Readme_5  = "  4.#G途中休息：#W帮主在古道传送处点击神兽驿站按扭，当前在驿站周围的帮众都会获得经验奖励。并且在最后完成护兽任务时都会获得经验加成的奖励。#r" 
		local Readme_6  = "  5.#G途中消失：#W参与护送成员任务失败，无法返还帮主押金。#r"
		local Readme_7  = "  6.#G途中被杀：#W参与护送成员任务失败，帮主押金将被抢走。#r"
		local Readme_8  = "  7.#G放弃任务：#W参与护送成员任务失败，无法返还帮主押金。#r"
		local Readme_9  = "  8.#G回复成功：#W参与护送成员将获得高额经验，帮会经验，帮贡奖励，并且返还帮主押金，参与人数越多经验奖励越多。#r"
		local Readme_10 = "  9.#G惩罚：#W劫杀本国成员镖车将不会获得押金，同时将获得非常严厉的惩罚。"
		local Readme = Readme_1..Readme_2..Readme_3..Readme_4..Readme_5..Readme_6..Readme_7..Readme_8..Readme_9..Readme_10
		AddQuestText(sceneId, Readme);EndQuestEvent(sceneId);DispatchQuestEventList(sceneId,selfId,targetId);DispatchQuestInfo( sceneId, selfId, targetId, 300774, -1 );
end

function x300774_ProcAcceptCheck( sceneId, selfId, NPCId )

end



--**********************************
--接受
--**********************************
function x300774_ProcAccept( sceneId, selfId )
end
--**********************************
--放弃
--**********************************
function x300774_ProcQuestAbandon( sceneId, selfId, MissionId )
end
--**********************************
--继续
--**********************************
function x300774_OnContinue( sceneId, selfId, targetId )
end
--**********************************
--检测是否可以提交
--**********************************
function x300774_CheckSubmit( sceneId, selfId )
end
--**********************************
--提交
--**********************************
function x300774_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end
--**********************************
--杀死怪物或玩家
--**********************************
function x300774_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end
--**********************************
--进入区域事件
--**********************************
function x300774_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end
--**********************************
--道具改变
--**********************************
function x300774_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end