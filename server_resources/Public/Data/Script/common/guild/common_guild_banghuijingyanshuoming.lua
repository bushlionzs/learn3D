--MisDescBegin 
x300787_g_ScriptId 					= 	300787
x300787_g_MissionInfo				= 	"巡按任务信息" 
--MisDescEnd

function x300787_ProcEnumEvent( sceneId, selfId, targetId )
end

function x300787_ProcEventEntry(sceneId, selfId,targetId)	--点击该任务后执行此脚本
		BeginQuestEvent(sceneId)
		local Readme_1 = "#Y【帮会】帮会经验#r#W"
		local Readme_2 = "  1，#G帮会经验获得：#W帮会经验可以通过帮会建设、帮会募集、帮会战以及完成帮会任务获得。#r"
		local Readme_3 = "  2，#G帮会经验用途：#W帮会经验用于升级帮会和激活帮会商店的稀有商品。#r"
		local Readme = Readme_1..Readme_2..Readme_3
		AddQuestText(sceneId, Readme);EndQuestEvent(sceneId);DispatchQuestInfo( sceneId, selfId, targetId, x300787_g_ScriptId, -1 );
end 

function x300787_ProcAcceptCheck( sceneId, selfId, NPCId )

end



--**********************************
--接受
--**********************************
function x300787_ProcAccept( sceneId, selfId )
end
--**********************************
--放弃
--**********************************
function x300787_ProcQuestAbandon( sceneId, selfId, MissionId )
end
--**********************************
--继续
--**********************************
function x300787_OnContinue( sceneId, selfId, targetId )
end
--**********************************
--检测是否可以提交
--**********************************
function x300787_CheckSubmit( sceneId, selfId )
end
--**********************************
--提交
--**********************************
function x300787_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end
--**********************************
--杀死怪物或玩家
--**********************************
function x300787_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end
--**********************************
--进入区域事件
--**********************************
function x300787_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end
--**********************************
--道具改变
--**********************************
function x300787_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end