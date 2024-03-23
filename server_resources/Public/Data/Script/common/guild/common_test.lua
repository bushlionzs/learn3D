--点击（NPC）
function x300635_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

	--AddQuestNumText(sceneId,300635,"测试按钮A",0,1)
	
end



--点击（按钮）点击该任务后执行此脚本
function x300635_ProcEventEntry( sceneId, selfId, targetId,state,index)	

		if index == 1 then
		
			BeginQuestEvent(sceneId);AddQuestText(sceneId,"按钮A对应的任务描述");EndQuestEvent(sceneId);DispatchQuestInfo(sceneId, selfId, targetId, 300635, -1)
			
		end
	
end



--点击（确定）
function x300635_ProcAcceptCheck( sceneId, selfId, NPCId )
	
			BeginQuestEvent(sceneId);AddQuestText(sceneId,"按钮A对应的任务描述");EndQuestEvent(sceneId);DispatchQuestTips(sceneId,selfId)
			
			Msg2Player(sceneId,selfId,"按钮A对应的任务描述",8,2)

end



--**********************************
--接受
--**********************************
function x300635_ProcAccept( sceneId, selfId )
end
--**********************************
--放弃
--**********************************
function x300635_ProcQuestAbandon( sceneId, selfId, MissionId )
end
--**********************************
--继续
--**********************************
function x300635_OnContinue( sceneId, selfId, targetId )
end
--**********************************
--检测是否可以提交
--**********************************
function x300635_CheckSubmit( sceneId, selfId )
end
--**********************************
--提交
--**********************************
function x300635_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end
--**********************************
--杀死怪物或玩家
--**********************************
function x300635_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end
--**********************************
--进入区域事件
--**********************************
function x300635_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end
--**********************************
--道具改变
--**********************************
function x300635_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end