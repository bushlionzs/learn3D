--点击（NPC）
x300785_g_ScriptId 					= 	300785   
x300785_g_MissionName0= "【介绍】帮贡"
x300785_g_MissionName1= "【介绍】帮会等级" 
x300785_g_MissionName2= "【介绍】帮会经验"
x300785_g_MissionName3= "【介绍】帮会金钱"
--x300785_g_MissionName4= "【介绍】帮会功德"	
x300785_g_MissionName5= "【介绍】帮会使命点"
x300785_g_MissionName6= "【介绍】帮会属性天赋"					  
					   
function x300785_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	AddQuestNumText(sceneId,300785,"【介绍】帮会说明",1)	
end



--点击（按钮）点击该任务后执行此脚本
function x300785_ProcEventEntry( sceneId, selfId, targetId)		
		--local MissionName = x300785_g_MissionName;
		BeginQuestEvent(sceneId)
			local Readme_1 = "#Y【介绍】帮会说明#r#W #r"			
			
			local Readme_2 = "\t如果您想在成吉思汗的世界里建立宏图霸业，创建或加入一个强大的帮会是您梦想成真的基础。 #r"
			
			local Readme_3 = "\t请点击下列对应按钮，您可以查询帮会相关信息:"
			
			
			local Readme = Readme_1..Readme_2..Readme_3
		AddQuestNumText(sceneId,300790 ,x300785_g_MissionName0,1);
		AddQuestNumText(sceneId,300786 ,x300785_g_MissionName1,1);
		AddQuestNumText(sceneId,300787 ,x300785_g_MissionName2,1);
		AddQuestNumText(sceneId,300788 ,x300785_g_MissionName3,1);
		--AddQuestNumText(sceneId,300791 ,x300785_g_MissionName4,1);		
		AddQuestNumText(sceneId,300789 ,x300785_g_MissionName5,1);
		AddQuestNumText(sceneId,300719 ,x300785_g_MissionName6,1);
		AddQuestText( sceneId,Readme)
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId);
		
		
end



--点击（确定）
function x300785_ProcAcceptCheck( sceneId, selfId, NPCId )

end



--**********************************
--接受
--**********************************
function x300785_ProcAccept( sceneId, selfId )
end
--**********************************
--放弃
--**********************************
function x300785_ProcQuestAbandon( sceneId, selfId, MissionId )
end
--**********************************
--继续
--**********************************
function x300785_OnContinue( sceneId, selfId, targetId )
end
--**********************************
--检测是否可以提交
--**********************************
function x300785_CheckSubmit( sceneId, selfId )
end
--**********************************
--提交
--**********************************
function x300785_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end
--**********************************
--杀死怪物或玩家
--**********************************
function x300785_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end
--**********************************
--进入区域事件
--**********************************
function x300785_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end
--**********************************
--道具改变
--**********************************
function x300785_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end