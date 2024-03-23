--MisDescBegin 
x300773_g_ScriptId 					= 	300786
x300773_g_MissionName				= 	"帮会等级" 
x300773_g_MissionInfo				= 	"巡按任务信息" 
--MisDescEnd

function x300786_ProcEnumEvent( sceneId, selfId, targetId )
end

function x300786_ProcEventEntry(sceneId, selfId,targetId)	--点击该任务后执行此脚本
		BeginQuestEvent(sceneId)
		local Readme_1 = "#Y【帮会】帮会等级#r#W"
		local Readme_2 = "\t#G帮会等级：#W提升帮会等级需要一定的帮会令、现银及帮会经验。等级越高，帮会人数上限越高，帮会任务也将获得更多的奖励#r"
		local Readme = Readme_1..Readme_2
		AddQuestText(sceneId, Readme);EndQuestEvent(sceneId);DispatchQuestInfo( sceneId, selfId, targetId, x300773_g_ScriptId, -1 );
end 

function x300786_ProcAcceptCheck( sceneId, selfId, NPCId )

end



--**********************************
--接受
--**********************************
function x300786_ProcAccept( sceneId, selfId )
end
--**********************************
--放弃
--**********************************
function x300786_ProcQuestAbandon( sceneId, selfId, MissionId )
end
--**********************************
--继续
--**********************************
function x300786_OnContinue( sceneId, selfId, targetId )
end
--**********************************
--检测是否可以提交
--**********************************
function x300786_CheckSubmit( sceneId, selfId )
end
--**********************************
--提交
--**********************************
function x300786_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end
--**********************************
--杀死怪物或玩家
--**********************************
function x300786_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end
--**********************************
--进入区域事件
--**********************************
function x300786_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end
--**********************************
--道具改变
--**********************************
function x300786_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end