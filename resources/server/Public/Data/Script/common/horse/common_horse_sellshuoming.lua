--MisDescBegin 
x920008_g_ScriptId 					= 	920008
x920008_g_MissionName				= 	"【收集战马说明】" 
x920008_g_MissionInfo				= 	"巡按任务信息" 
--MisDescEnd

function x920008_ProcEnumEvent( sceneId, selfId, targetId )
	AddQuestNumText(sceneId, x920008_g_ScriptId,x920008_g_MissionName,13,1)
end

function x920008_ProcEventEntry(sceneId, selfId,targetId)	--点击该任务后执行此脚本
		BeginQuestEvent(sceneId)
		local Readme_1 = "#Y【收集战马说明】#r#W"
		local Readme_2 = "  #Y收集战马：#W每位玩家每天可以上缴#G10匹#W战马，每次都会获得银卡奖励。#r"
		local Readme_4 = "  #Y注意事项：#W提交战马的#G携带等级#W越高，所获得的奖励也会越多。#r"
		local Readme_5 = "  #Y特殊奖励：#W在同携带等级下，提交#G良品马#W会获得#G8倍#W于普通马的奖励。" 
		local Readme = Readme_1..Readme_2..Readme_4..Readme_5
		AddQuestText(sceneId, Readme);EndQuestEvent(sceneId);DispatchQuestInfo( sceneId, selfId, targetId, x920008_g_ScriptId, -1 );
		EndQuestEvent()
		DispatchQuestEventList(sceneId, selfId,targetId,x920008_g_ScriptId,x920008_g_MissionName)
end 

function x920008_ProcAcceptCheck( sceneId, selfId, NPCId )

end



--**********************************
--接受
--**********************************
function x920008_ProcAccept( sceneId, selfId )
end
--**********************************
--放弃
--**********************************
function x920008_ProcQuestAbandon( sceneId, selfId, MissionId )
end
--**********************************
--继续
--**********************************
function x920008_OnContinue( sceneId, selfId, targetId )
end
--**********************************
--检测是否可以提交
--**********************************
function x920008_CheckSubmit( sceneId, selfId )
end
--**********************************
--提交
--**********************************
function x920008_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end
--**********************************
--杀死怪物或玩家
--**********************************
function x920008_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end
--**********************************
--进入区域事件
--**********************************
function x920008_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end
--**********************************
--道具改变
--**********************************
function x920008_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end