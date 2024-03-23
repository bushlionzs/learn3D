--MisDescBegin 
x300791_g_ScriptId 					= 	300791
x300791_g_MissionInfo				= 	"巡按任务信息" 
--MisDescEnd

function x300791_ProcEnumEvent( sceneId, selfId, targetId )
end

function x300791_ProcEventEntry(sceneId, selfId,targetId)	--点击该任务后执行此脚本
		BeginQuestEvent(sceneId)
		local Readme_1 = "#Y【帮会】帮会功德#r#W"
		local Readme_2 = "  1，#G功德获得：#W功德可以通过完成帮会任务（帮会内政除外）、帮会建设、帮会募集、帮会战获得。#r"
		local Readme_3 = "  2，#G功德影响：#W功德小于5的帮会成员，在完成帮会任务后，不会增加帮会经验。#r"
		local Readme_4 = "  3, #G功德用途：#W功德值越高,完成护送神兽、帮会暗战、收集黑木、收集丹木、粮仓除妖、仙人谷除妖任务时所获得的经验加成越多,接受帮会跑环任务时共可完成的环数上限越高。#r"
		local Readme = Readme_1..Readme_2..Readme_3..Readme_4
		AddQuestText(sceneId, Readme);EndQuestEvent(sceneId);DispatchQuestInfo( sceneId, selfId, targetId, x300791_g_ScriptId, -1 );
end 

function x300791_ProcAcceptCheck( sceneId, selfId, NPCId )

end



--**********************************
--接受
--**********************************
function x300791_ProcAccept( sceneId, selfId )
end
--**********************************
--放弃
--**********************************
function x300791_ProcQuestAbandon( sceneId, selfId, MissionId )
end
--**********************************
--继续
--**********************************
function x300791_OnContinue( sceneId, selfId, targetId )
end
--**********************************
--检测是否可以提交
--**********************************
function x300791_CheckSubmit( sceneId, selfId )
end
--**********************************
--提交
--**********************************
function x300791_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end
--**********************************
--杀死怪物或玩家
--**********************************
function x300791_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end
--**********************************
--进入区域事件
--**********************************
function x300791_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end
--**********************************
--道具改变
--**********************************
function x300791_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end