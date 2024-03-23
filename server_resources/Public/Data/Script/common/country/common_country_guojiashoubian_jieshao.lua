--**********************************
--任务入口函数
--**********************************
function x300743_ProcEventEntry( sceneId, selfId, targetId )	--点击该任务后执行此脚本
		BeginQuestEvent(sceneId);
		local localexp = (GetLevel( sceneId, selfId )) * 1000*0.5*5		
		
		local Readme_1 = "#Y国家守边#W#r"
		
		local Readme_2 = "\t到本国边境守边，防止外族入侵，在规定时间内完成，成功回复任务会获得守边奖励#G"..localexp.."#W点个人经验。#r"
		
		local Readme_3 = "\t在守边期间，您可以杀死侵犯我方的敌人。"
		
		local Readme = Readme_1 .. Readme_2 .. Readme_3
				
		AddQuestText(sceneId, Readme);EndQuestEvent(sceneId);DispatchQuestEventList(sceneId,selfId,targetId);DispatchQuestInfoNM( sceneId, selfId, targetId, -1, -1,2 );
	
	
end

--**********************************
--列举事件
--**********************************
function x300743_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

end


--********************
--检测接受条件
--**********************************
function x300743_ProcAcceptCheck( sceneId, selfId, NPCId )
		return 1
end

--**********************************
--接受
--**********************************
function x300743_ProcAccept( sceneId, selfId )

	
end

--**********************************
--放弃
--**********************************
function x300743_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--继续
--**********************************
function x300743_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--检测是否可以提交
--**********************************
function x300743_CheckSubmit( sceneId, selfId )

end

--**********************************
--提交
--**********************************
function x300743_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--杀死怪物或玩家
--**********************************
function x300743_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--进入区域事件
--**********************************
function x300743_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--道具改变
--**********************************
function x300743_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
