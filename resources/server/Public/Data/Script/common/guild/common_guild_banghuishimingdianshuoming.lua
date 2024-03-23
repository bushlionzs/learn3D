--MisDescBegin 
x300789_g_ScriptId 					= 	300789
x300789_g_MissionInfo				= 	"巡按任务信息" 
--MisDescEnd

function x300789_ProcEnumEvent( sceneId, selfId, targetId )
end

function x300789_ProcEventEntry(sceneId, selfId,targetId)	--点击该任务后执行此脚本
		BeginQuestEvent(sceneId)
		local Readme_1 = "#Y【帮会】帮会使命点#r#W"
		local Readme_2 = "  1，#G使命点获得：#W使命点通过帮会募集、帮会暗战、帮会战、世界杯大赛获得。#r"
		local Readme_3 = "  2，#G使命点显示：#W前面数字代表帮会当前使命点，后面数字代表当前帮会等级所需求使命点。#r"
		local Readme_4 = "  3，#G使命点用途：#W每月中、月末会根据帮会等级结算使命点并将剩余使命点清0。#r"
		local Readme_5 = "  4，#G使命点影响：#W若帮会当前使命点达到帮会等级所需求使命点，在结算日（每月15日和每月最后一天的24点），将会获得#G高额帮会经验#W奖励。#r"
		--local Readme_6 = "  5，#G人数增减影响：#W每加入一名成员，使命点+1。每离开（开除）一名成员，使命点-2。#r"
		local Readme = Readme_1..Readme_2..Readme_3..Readme_4..Readme_5
		AddQuestText(sceneId, Readme);EndQuestEvent(sceneId);DispatchQuestInfo( sceneId, selfId, targetId, x300789_g_ScriptId, -1 );
end 

function x300789_ProcAcceptCheck( sceneId, selfId, NPCId )

end



--**********************************
--接受
--**********************************
function x300789_ProcAccept( sceneId, selfId )
end
--**********************************
--放弃
--**********************************
function x300789_ProcQuestAbandon( sceneId, selfId, MissionId )
end
--**********************************
--继续
--**********************************
function x300789_OnContinue( sceneId, selfId, targetId )
end
--**********************************
--检测是否可以提交
--**********************************
function x300789_CheckSubmit( sceneId, selfId )
end
--**********************************
--提交
--**********************************
function x300789_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end
--**********************************
--杀死怪物或玩家
--**********************************
function x300789_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end
--**********************************
--进入区域事件
--**********************************
function x300789_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end
--**********************************
--道具改变
--**********************************
function x300789_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end