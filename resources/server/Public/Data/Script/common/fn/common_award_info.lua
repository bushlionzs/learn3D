
x561100_g_ScriptId = 561100
x561100_g_MissionName = "【领取奖励说明】"
x561100_g_AwardInfo = "\t在我这里可以领取活动的奖励以及系统补偿。但是您必须在《成吉思汗》官网进行相关的激活。\n\t当您顺利在官网进行激活后，可以点击#G领取奖励补偿#W按钮进行领取！"

--点击（NPC）
function x561100_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

	AddQuestNumText(sceneId,x561100_g_ScriptId,x561100_g_MissionName,0,-1)
	return 0
	
end



--点击（按钮）点击该任务后执行此脚本
function x561100_ProcEventEntry( sceneId, selfId, targetId,state,index )	
	
	BeginQuestEvent(sceneId)
	AddQuestText(sceneId,"#Y"..x561100_g_MissionName)
	AddQuestText(sceneId,x561100_g_AwardInfo)
	EndQuestEvent(sceneId)
	DispatchQuestEventList( sceneId,selfId,targetId )

	--x561100_DispatchMissionInfo( sceneId, selfId, targetId,index)

end

function x561100_DispatchMissionInfo( sceneId, selfId, targetId,index)


end



--**********************************
--接受
--**********************************
function x561100_ProcAccept( sceneId, selfId )
end

function x561100_ProcAcceptCheck( sceneId, selfId, NPCId )
	return 1
end
--点击（确定）
function x561100_ProcQuestAccept( sceneId, selfId, NPCId )
end

--**********************************
--放弃
--**********************************
function x561100_ProcQuestAbandon( sceneId, selfId, MissionId )
end
--**********************************
--继续
--**********************************
function x561100_OnContinue( sceneId, selfId, targetId )
end
--**********************************
--检测是否可以提交
--**********************************
function x561100_CheckSubmit( sceneId, selfId )
end
--**********************************
--提交
--**********************************
function x561100_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end
--**********************************
--杀死怪物或玩家
--**********************************
function x561100_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end
--**********************************
--进入区域事件