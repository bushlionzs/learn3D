--点击（NPC）
x300792_g_ScriptId 					= 	300792   
x300792_g_MissionName0= "【介绍】国民津贴"
x300792_g_MissionName1= "【介绍】帮会津贴"
x300792_g_MissionName2= "【介绍】出国津贴"
x300792_g_MissionName3= "【介绍】国运津贴" 
x300792_g_MissionName4= "【介绍】守护津贴" 							   
function x300792_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	AddQuestNumText(sceneId,300792,"【介绍】津贴介绍",1)	
end



--点击（按钮）点击该任务后执行此脚本
function x300792_ProcEventEntry( sceneId, selfId, targetId)		
		--local MissionName = x300792_g_MissionName;
		BeginQuestEvent(sceneId)
			local Readme_1 = "#Y【介绍】津贴介绍#r#W"			
			
			local Readme_2 = "\t津贴是给予为国家做出贡献的国民的一种奖励。 #r"
			
			local Readme_3 = "\t请点击下列对应按钮，您可以查询津贴相关信息:"
			
			
			local Readme = Readme_1..Readme_2..Readme_3
		AddQuestNumText(sceneId,300793 ,x300792_g_MissionName0,1);
		AddQuestNumText(sceneId,300794 ,x300792_g_MissionName1,1);
		AddQuestNumText(sceneId,300795 ,x300792_g_MissionName2,1);
		AddQuestNumText(sceneId,300796 ,x300792_g_MissionName3,1);
		AddQuestNumText(sceneId,300799 ,x300792_g_MissionName4,1);
		AddQuestText( sceneId,Readme)
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId);
end



--点击（确定）
function x300792_ProcAcceptCheck( sceneId, selfId, NPCId )

end



--**********************************
--接受
--**********************************
function x300792_ProcAccept( sceneId, selfId )
end
--**********************************
--放弃
--**********************************
function x300792_ProcQuestAbandon( sceneId, selfId, MissionId )
end
--**********************************
--继续
--**********************************
function x300792_OnContinue( sceneId, selfId, targetId )
end
--**********************************
--检测是否可以提交
--**********************************
function x300792_CheckSubmit( sceneId, selfId )
end
--**********************************
--提交
--**********************************
function x300792_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end
--**********************************
--杀死怪物或玩家
--**********************************
function x300792_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end
--**********************************
--进入区域事件
--**********************************
function x300792_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end
--**********************************
--道具改变
--**********************************
function x300792_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end