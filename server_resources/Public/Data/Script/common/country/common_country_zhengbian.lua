--点击（NPC）
x300317_g_ScriptId 					= 	300317   
--x300317_g_MissionName6= "" 
--x300317_g_MissionName7= ""
								  

							   
function x300317_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	AddQuestNumText(sceneId,300317,"【国家】谋国政变",0,1)	
end



--点击（按钮）点击该任务后执行此脚本
function x300317_ProcEventEntry( sceneId, selfId, targetId)		
		--local MissionName = x300767_g_MissionName;
		BeginQuestEvent(sceneId)
		local Readme_1 = "#Y【国家】谋国政变#r#G"
		local Readme_2 = "#Y一，#G如果您所在国家的战神之旗在周一到周六19：30-23：00之间被敌国摧毁，将会导致本国国王下台，国家进入无国王状态。同时当天下台的国王帮将不能申请国王。#r#r"
		local Readme_3 = "#Y二，#G除下台的国王帮外其它帮会可以立即申请国王，同时在一周内战神之旗再次被敌国摧毁时，新国王会继续保持王位。 #r#r"
		local Readme_4 = "#Y三，#G周一到周六19：30-23：00之间，击杀敌国战神之旗，会导致该国国王自动下台。#r#r"
		local Readme_5 = "#Y四，#G如果该国没有国王，则摧毁战神之旗无效。 #r#r"
		local Readme_6 = "#Y五，#G导致该国国王下台后，一周之内如果战神之旗再次被摧毁则不会触发国王下台事件。#r#r"
		local Readme = Readme_1..Readme_2..Readme_3..Readme_4..Readme_5..Readme_6
		--AddQuestNumText(sceneId,300772 ,x300317_g_MissionName6,1);
		--AddQuestNumText(sceneId,300773 ,x300317_g_MissionName7,1);
		AddQuestText( sceneId,Readme)
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId);
		
		
end



--点击（确定）
function x300317_ProcAcceptCheck( sceneId, selfId, NPCId )

end



--**********************************
--接受
--**********************************
function x300317_ProcAccept( sceneId, selfId )
end
--**********************************
--放弃
--**********************************
function x300317_ProcQuestAbandon( sceneId, selfId, MissionId )
end
--**********************************
--继续
--**********************************
function x300317_OnContinue( sceneId, selfId, targetId )
end
--**********************************
--检测是否可以提交
--**********************************
function x300317_CheckSubmit( sceneId, selfId )
end
--**********************************
--提交
--**********************************
function x300317_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end
--**********************************
--杀死怪物或玩家
--**********************************
function x300317_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end
--**********************************
--进入区域事件
--**********************************
function x300317_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end
--**********************************
--道具改变
--**********************************
function x300317_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end