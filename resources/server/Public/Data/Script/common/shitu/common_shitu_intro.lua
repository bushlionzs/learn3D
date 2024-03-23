--点击（NPC）
function x300360_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	AddQuestNumText(sceneId,300360,"【师徒系统说明】",0,0)	
end



--点击（按钮）点击该任务后执行此脚本
function x300360_ProcEventEntry( sceneId, selfId, targetId,state,index)	
		local Readme_1 = "#Y【师徒系统说明】#r"
		local Readme_2 = "#W\t成吉思汗中#G找个师傅#W或#G收个徒弟#W都能给您带来意想不到的好处。#r"
		local Readme_3 = "#W#r\t您可以通过#G查找师傅#W或#G查找徒弟#W来寻找希望成为师傅/徒弟的玩家,也可以通过#G报名功能#W在师傅或者徒弟名单中留下信息。如果有合适的人选，也可以由师傅带队，直接来我这里结为师徒。#r"
		local Readme_4 = "#W#r\t20级以上没有师傅的玩家可以成为徒弟，50级以上的玩家可以成为师傅。收徒时#G师徒等级须相差10级以上#W（含10级）。#r"
		local Readme_5 = "#W#r\t当徒弟每提升一级时，#G师傅#W及#G师傅的师傅#W都会获得#G大量的奖励#W。而徒弟的等级与等级排行榜最后一名玩家的等级相差10级以上时，获得的打怪经验在原基础上#G提升50%#W，如与师傅在同一个队伍打怪且徒弟的等级与等级排行榜最后一名玩家的等级相差10级以上时，获得的打怪经验在原基础上#G提升100%#W。#r"
		local Readme_6 = "#W#r\t师傅在作为队长带领徒弟练级时，如果符合获得威望的规则，师傅将获得#G额外的威望奖励#W。#r"
		local Readme_7 = "#W#r\t每名师傅最多可收取五名徒弟，三天内无法再次收取另一个徒弟。要收取更多的徒弟，需要先在#G威望商人#W处换取更高级的师傅称号。#r"
		local Readme_8 = "#W#r\t成为师傅后可收取一名徒弟，师傅带出两名徒弟出师时，可收取二名徒弟，师傅带出五名徒弟出师时，可收取三名徒弟，师傅带出十名徒弟出师时，可收取四名徒弟，师傅带出二十名徒弟出师时，可收取五名徒弟。根据可以收取不同数量的徒弟，师傅的称号也会随之变化。#r"
		local Readme = Readme_1..Readme_2..Readme_3..Readme_4..Readme_5..Readme_7
		--BeginQuestEvent(sceneId);AddQuestText(sceneId,"按钮A对应的任务描述");EndQuestEvent(sceneId);DispatchQuestInfo(sceneId, selfId, targetId, 300360, -1)--双按钮
		BeginQuestEvent(sceneId);AddQuestText(sceneId, Readme);EndQuestEvent(sceneId);DispatchQuestEventList(sceneId,selfId,targetId);DispatchQuestInfoNM( sceneId, selfId, targetId, -1, -1,2 )--单按钮
end



--点击（确定）
function x300360_ProcAcceptCheck( sceneId, selfId, NPCId )
	
			BeginQuestEvent(sceneId);AddQuestText(sceneId,"按钮A对应的任务描述");EndQuestEvent(sceneId);DispatchQuestTips(sceneId,selfId)
			
			Msg2Player(sceneId,selfId,"按钮A对应的任务描述",8,2)

end



--**********************************
--接受
--**********************************
function x300360_ProcAccept( sceneId, selfId )
end
--**********************************
--放弃
--**********************************
function x300360_ProcQuestAbandon( sceneId, selfId, MissionId )
end
--**********************************
--继续
--**********************************
function x300360_OnContinue( sceneId, selfId, targetId )
end
--**********************************
--检测是否可以提交
--**********************************
function x300360_CheckSubmit( sceneId, selfId )
end
--**********************************
--提交
--**********************************
function x300360_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end
--**********************************
--杀死怪物或玩家
--**********************************
function x300360_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end
--**********************************
--进入区域事件
--**********************************
function x300360_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end
--**********************************
--道具改变
--**********************************
function x300360_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end