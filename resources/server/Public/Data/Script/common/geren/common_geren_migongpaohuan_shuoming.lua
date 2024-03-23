--MisDescBegin 
x562004_g_ScriptId 					= 	562004
x562004_g_MissionName				= 	"【迷宫除恶说明】" 
x562004_g_MissionInfo				= 	"巡按任务信息" 
--MisDescEnd

function x562004_ProcEnumEvent( sceneId, selfId, targetId )
	AddQuestNumText(sceneId, x562004_g_ScriptId,x562004_g_MissionName,13,1)
end

function x562004_ProcEventEntry(sceneId, selfId,targetId)	--点击该任务后执行此脚本
		BeginQuestEvent(sceneId)
		local Readme_1 = "#Y【迷宫除恶说明】#r#W"
		local Readme_2 = "  #Y接取任务：#W#G35级到49级#W的玩家可以接取任务，每天可完成#G一轮共10环#W任务！#r"
		local Readme_4 = "  #Y注意事项：#W放弃任务后本日就不能再次接取任务了，且#G环数将被清零#W。#r"
		local Readme_5 = "  #Y特殊提示：#W在10环的任务中，结交好友组建队伍会大大提高你完成速度，完成整轮任务会获得额外奖励#W。" 
		local Readme = Readme_1..Readme_2..Readme_4..Readme_5
		AddQuestText(sceneId, Readme);EndQuestEvent(sceneId);DispatchQuestInfo( sceneId, selfId, targetId, x562004_g_ScriptId, -1 );
		EndQuestEvent()
		DispatchQuestEventList(sceneId, selfId,targetId,x562004_g_ScriptId,x562004_g_MissionName)
end 

function x562004_ProcAcceptCheck( sceneId, selfId, NPCId )

end



--**********************************
--接受
--**********************************
function x562004_ProcAccept( sceneId, selfId )
end
--**********************************
--放弃
--**********************************
function x562004_ProcQuestAbandon( sceneId, selfId, MissionId )
end
--**********************************
--继续
--**********************************
function x562004_OnContinue( sceneId, selfId, targetId )
end
--**********************************
--检测是否可以提交
--**********************************
function x562004_CheckSubmit( sceneId, selfId )
end
--**********************************
--提交
--**********************************
function x562004_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end
--**********************************
--杀死怪物或玩家
--**********************************
function x562004_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end
--**********************************
--进入区域事件
--**********************************
function x562004_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end
--**********************************
--道具改变
--**********************************
function x562004_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end