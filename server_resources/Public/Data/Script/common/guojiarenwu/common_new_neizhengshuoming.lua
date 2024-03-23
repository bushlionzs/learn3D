--MisDescBegin 
x300521_g_ScriptId 					= 	300521
x300521_g_MissionName				= 	"【国家内政说明】" 
x300521_g_MissionInfo				= 	"巡按任务信息" 
--MisDescEnd

function x300521_ProcEnumEvent( sceneId, selfId, targetId )
	AddQuestNumText(sceneId, x300521_g_ScriptId,x300521_g_MissionName,13,1)
end

function x300521_ProcEventEntry(sceneId, selfId,targetId)	--点击该任务后执行此脚本
		BeginQuestEvent(sceneId)
		local Readme_1 = "#Y【国家内政说明】#r#W"
		local Readme_2 = "  #Y接取任务：#W不低于#G25级#W的玩家可以接取任务，每天可完成#G一轮共10次#W任务！#r"
		local Readme_4 = "  #Y注意事项：#W放弃任务后本日就不能再次接取任务了，且#G环数将被清零#W。#r"
		local Readme_5 = "  #Y特殊奖励：#W在#G收集马匹#W的任务中，如果你能带来对应的#G良品马#W，会获得#G高额的经验奖励#W。\n  在收集物品的任务中，如果你能按照要求上交一些#G生活技能的原材料#W或#G生活技能制造的部件#W，#G甘醇马奶酒#W等等，你会获得#G海量的奖励#W！" 
		local Readme = Readme_1..Readme_2..Readme_4..Readme_5
		AddQuestText(sceneId, Readme);EndQuestEvent(sceneId);DispatchQuestInfo( sceneId, selfId, targetId, x300521_g_ScriptId, -1 );
		EndQuestEvent()
		DispatchQuestEventList(sceneId, selfId,targetId,x300521_g_ScriptId,x300521_g_MissionName)
end 

function x300521_ProcAcceptCheck( sceneId, selfId, NPCId )

end



--**********************************
--接受
--**********************************
function x300521_ProcAccept( sceneId, selfId )
end
--**********************************
--放弃
--**********************************
function x300521_ProcQuestAbandon( sceneId, selfId, MissionId )
end
--**********************************
--继续
--**********************************
function x300521_OnContinue( sceneId, selfId, targetId )
end
--**********************************
--检测是否可以提交
--**********************************
function x300521_CheckSubmit( sceneId, selfId )
end
--**********************************
--提交
--**********************************
function x300521_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end
--**********************************
--杀死怪物或玩家
--**********************************
function x300521_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end
--**********************************
--进入区域事件
--**********************************
function x300521_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end
--**********************************
--道具改变
--**********************************
function x300521_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end