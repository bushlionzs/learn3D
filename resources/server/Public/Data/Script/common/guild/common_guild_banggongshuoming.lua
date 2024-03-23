--MisDescBegin 
x300790_g_ScriptId 					= 	300790
x300790_g_MissionName				= 	"收集黑木"
x300790_g_MissionInfo				= 	"巡按任务信息" 
--MisDescEnd

function x300790_ProcEnumEvent( sceneId, selfId, targetId )
end

function x300790_ProcEventEntry(sceneId, selfId,targetId)	--点击该任务后执行此脚本
		BeginQuestEvent(sceneId)
		local Readme_1 = "#Y【帮会】帮贡说明#r#W"
		local Readme_2 = "  1，#G帮贡获得：#W帮贡通过完成帮会任务、帮会建设、帮会募集、帮会战获得。#r"
		local Readme_3 = "  2，#G帮贡用途：#W帮贡可以用来在帮会商店购买物品，兑换海蓝钻石也需要帮贡。#r"
		local Readme = Readme_1..Readme_2..Readme_3
		AddQuestText(sceneId, Readme);EndQuestEvent(sceneId);DispatchQuestInfo( sceneId, selfId, targetId, x300790_g_ScriptId, -1 );
end 

function x300790_ProcAcceptCheck( sceneId, selfId, NPCId )

end



--**********************************
--接受
--**********************************
function x300790_ProcAccept( sceneId, selfId )
end
--**********************************
--放弃
--**********************************
function x300790_ProcQuestAbandon( sceneId, selfId, MissionId )
end
--**********************************
--继续
--**********************************
function x300790_OnContinue( sceneId, selfId, targetId )
end
--**********************************
--检测是否可以提交
--**********************************
function x300790_CheckSubmit( sceneId, selfId )
end
--**********************************
--提交
--**********************************
function x300790_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end
--**********************************
--杀死怪物或玩家
--**********************************
function x300790_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end
--**********************************
--进入区域事件
--**********************************
function x300790_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end
--**********************************
--道具改变
--**********************************
function x300790_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end