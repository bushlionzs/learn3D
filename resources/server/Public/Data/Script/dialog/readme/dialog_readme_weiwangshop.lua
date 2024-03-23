--点击（NPC）
function x103000_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	AddQuestNumText(sceneId,103000,"【威望说明】",0,0)	
end



--点击（按钮）点击该任务后执行此脚本
function x103000_ProcEventEntry( sceneId, selfId, targetId,state,index)	
		local Readme_1 = "#Y【威望说明】#r"
		local Readme_2 = "#W\t当#G徒弟升级，或完成师徒任务时#W，师傅会获得威望点。#r"
		local Readme_3 = "#W#r\t获得的威望点可以通过威望点商店来换取各种物品。获得威望点的条件如下：#r"
		local Readme_4 = "#W#r1、师傅的徒弟或师傅徒弟的徒弟升级时，师傅会获得一定的威望点。#r"
		local Readme_5 = "#W#r2、师傅和徒弟一起完成师徒任务，师傅会获得大量的威望点。#W#r"
		local Readme = Readme_1..Readme_2..Readme_3..Readme_4..Readme_5
		--BeginQuestEvent(sceneId);AddQuestText(sceneId,"按钮A对应的任务描述");EndQuestEvent(sceneId);DispatchQuestInfo(sceneId, selfId, targetId, 103000, -1)--双按钮
		BeginQuestEvent(sceneId);AddQuestText(sceneId, Readme);EndQuestEvent(sceneId);DispatchQuestEventList(sceneId,selfId,targetId);DispatchQuestInfoNM( sceneId, selfId, targetId, -1, -1,2 )--单按钮
end



--点击（确定）
function x103000_ProcAcceptCheck( sceneId, selfId, NPCId )
	
			BeginQuestEvent(sceneId);AddQuestText(sceneId,"按钮A对应的任务描述");EndQuestEvent(sceneId);DispatchQuestTips(sceneId,selfId)
			
			Msg2Player(sceneId,selfId,"按钮A对应的任务描述",8,2)

end



--**********************************
--接受
--**********************************
function x103000_ProcAccept( sceneId, selfId )
end
--**********************************
--放弃
--**********************************
function x103000_ProcQuestAbandon( sceneId, selfId, MissionId )
end
--**********************************
--继续
--**********************************
function x103000_OnContinue( sceneId, selfId, targetId )
end
--**********************************
--检测是否可以提交
--**********************************
function x103000_CheckSubmit( sceneId, selfId )
end
--**********************************
--提交
--**********************************
function x103000_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end
--**********************************
--杀死怪物或玩家
--**********************************
function x103000_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end
--**********************************
--进入区域事件
--**********************************
function x103000_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end
--**********************************
--道具改变
--**********************************
function x103000_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end