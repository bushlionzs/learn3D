--MisDescBegin 
x300788_g_ScriptId 					= 	300788
x300788_g_MissionInfo				= 	"巡按任务信息" 
--MisDescEnd

function x300788_ProcEnumEvent( sceneId, selfId, targetId )
end

function x300788_ProcEventEntry(sceneId, selfId,targetId)	--点击该任务后执行此脚本
		BeginQuestEvent(sceneId)
		local Readme_1 = "#Y【帮会】帮会金钱#r#W"
		local Readme_2 = "  1，#G帮会金钱获得：#W帮会金钱通过帮会募集，帮会捐献，帮会跑商任务获得。#r"
		local Readme_3 = "  2，#G帮会金钱用途：#W拥有足够的帮会金钱，可由帮主发布帮务任务，也可以用于属性天赋研究。#r"
		local Readme = Readme_1..Readme_2..Readme_3
		AddQuestText(sceneId, Readme);EndQuestEvent(sceneId);DispatchQuestInfo( sceneId, selfId, targetId, x300788_g_ScriptId, -1 );
end 

function x300788_ProcAcceptCheck( sceneId, selfId, NPCId )

end



--**********************************
--接受
--**********************************
function x300788_ProcAccept( sceneId, selfId )
end
--**********************************
--放弃
--**********************************
function x300788_ProcQuestAbandon( sceneId, selfId, MissionId )
end
--**********************************
--继续
--**********************************
function x300788_OnContinue( sceneId, selfId, targetId )
end
--**********************************
--检测是否可以提交
--**********************************
function x300788_CheckSubmit( sceneId, selfId )
end
--**********************************
--提交
--**********************************
function x300788_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end
--**********************************
--杀死怪物或玩家
--**********************************
function x300788_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end
--**********************************
--进入区域事件
--**********************************
function x300788_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end
--**********************************
--道具改变
--**********************************
function x300788_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end