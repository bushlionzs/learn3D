--**********************************
--任务入口函数
--**********************************
function x300744_ProcEventEntry( sceneId, selfId, targetId )	--点击该任务后执行此脚本
		BeginQuestEvent(sceneId);
		local localexp = (GetLevel( sceneId, selfId )) *1000*1*3

		local Readme_1 = "#Y敌国刺探#r#W"
		
		local Readme_2 = "\t出国去杀死敌国指定NPC，完成任务成功回复获得#G"..localexp.."#W点个人经验。#r"
		
		local Readme_3 = "\t由于是到敌国完成任务，您需要处处小心，建议您组队或集体完成本任务。"
		
		local Readme = Readme_1..Readme_2..Readme_3
		
		AddQuestText(sceneId, Readme);EndQuestEvent(sceneId);DispatchQuestEventList(sceneId,selfId,targetId);DispatchQuestInfoNM( sceneId, selfId, targetId, -1, -1,2 );
	
end

--**********************************
--列举事件
--**********************************
function x300744_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

end


--********************
--检测接受条件
--**********************************
function x300744_ProcAcceptCheck( sceneId, selfId, NPCId )
		return 1
end

--**********************************
--接受
--**********************************
function x300744_ProcAccept( sceneId, selfId )

	
end

--**********************************
--放弃
--**********************************
function x300744_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--继续
--**********************************
function x300744_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--检测是否可以提交
--**********************************
function x300744_CheckSubmit( sceneId, selfId )

end

--**********************************
--提交
--**********************************
function x300744_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--杀死怪物或玩家
--**********************************
function x300744_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--进入区域事件
--**********************************
function x300744_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--道具改变
--**********************************
function x300744_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
