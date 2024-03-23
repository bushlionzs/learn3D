--MisDescBegin 
x300804_g_ScriptId 					= 	300804
x300804_g_MissionName				= 	"帮会跑环" 
x300804_g_MissionInfo				= 	"巡按任务信息" 
--MisDescEnd

function x300804_ProcEnumEvent( sceneId, selfId, targetId )
end

function x300804_ProcEventEntry(sceneId, selfId,targetId)	--点击该任务后执行此脚本
		BeginQuestEvent(sceneId)
		local Readme_1 = "#Y【帮会】帮会跑环#r#W"
		local Readme_2 = "  1，#G接取任务：#W帮会内#G75级以上#W成员可以接取该任务。从完成整轮任务起计时，#G五天#W后可以再次接取。\n\t放弃任务后，可继续接取任务，直至任务完成。#r"
		local Readme_3 = "  2，#G任务环数：#W玩家的#G帮会功德#W小于50点，每轮跑环任务可以完成#G100环#W子任务。随着自身帮会功德的增加，子任务环数也会增加，最高为每轮可完成#G200环#W子任务。#r"
		local Readme_4 = "  3，#G任务种类：#W跑环任务分为送信、收集物品和杀怪三种形式。#r"
		local Readme_5 = "  4，#G任务奖励：#W成功完成任务，您将获得巨额的#G经验奖励#W。"
		local Readme = Readme_1..Readme_2..Readme_3..Readme_4..Readme_5
		AddQuestText(sceneId, Readme);EndQuestEvent(sceneId);DispatchQuestInfo( sceneId, selfId, targetId, x300804_g_ScriptId, -1 );
end 

function x300804_ProcAcceptCheck( sceneId, selfId, NPCId )

end



--**********************************
--接受
--**********************************
function x300804_ProcAccept( sceneId, selfId )
end
--**********************************
--放弃
--**********************************
function x300804_ProcQuestAbandon( sceneId, selfId, MissionId )
end
--**********************************
--继续
--**********************************
function x300804_OnContinue( sceneId, selfId, targetId )
end
--**********************************
--检测是否可以提交
--**********************************
function x300804_CheckSubmit( sceneId, selfId )
end
--**********************************
--提交
--**********************************
function x300804_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end
--**********************************
--杀死怪物或玩家
--**********************************
function x300804_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end
--**********************************
--进入区域事件
--**********************************
function x300804_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end
--**********************************
--道具改变
--**********************************
function x300804_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end