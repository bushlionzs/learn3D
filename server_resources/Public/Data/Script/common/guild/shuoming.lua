--点击（NPC）
x300766_g_ScriptId 					= 	300766   
x300766_g_MissionName0= "【帮会神兽说明】"
x300766_g_MissionName1= "【帮会暗战说明】"
--x300766_g_MissionName2= "【介绍】粮仓除妖"
-- x300766_g_MissionName3= "【介绍】收集黑木" 
x300766_g_MissionName4= "【帮会除魔说明】"
x300766_g_MissionName5= "【帮会图腾说明】"
x300766_g_MissionName6= "【帮会跑商说明】" 
--x300766_g_MissionName7= "【介绍】帮会跑环"
x300766_g_MissionName8= "【帮务任务说明】"
x300766_g_MissionName9= "【帮会贡品说明】"	
x300766_g_MissionName10= "【帮会速成说明】"									  

							   
function x300766_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	AddQuestNumText(sceneId,300766,"【帮会任务说明】",1)	
end



--点击（按钮）点击该任务后执行此脚本
function x300766_ProcEventEntry( sceneId, selfId, targetId)		
		--local MissionName = x300767_g_MissionName;
		BeginQuestEvent(sceneId)
			local Readme_1 = "#Y【帮会任务说明】#r#W #r"			
			
			local Readme_2 = "\t如果您想在成吉思汗的世界里建立宏图霸业，创建或加入一个强大的帮会是您梦想成真的基础。 #r"
			
			local Readme_3 = "\t请点击下列对应按钮，您可以查询帮会相关信息:"
			
			
			local Readme = Readme_1..Readme_2..Readme_3
		AddQuestNumText(sceneId,300774 ,x300766_g_MissionName0,1);
		AddQuestNumText(sceneId,300767 ,x300766_g_MissionName1,1);
		-- AddQuestNumText(sceneId,300768 ,x300766_g_MissionName2,1);
		-- AddQuestNumText(sceneId,300769 ,x300766_g_MissionName3,1);
		AddQuestNumText(sceneId,300770 ,x300766_g_MissionName4,1);
		AddQuestNumText(sceneId,300771 ,x300766_g_MissionName5,1);
		AddQuestNumText(sceneId,300704 ,x300766_g_MissionName6,1);
		--AddQuestNumText(sceneId,300804 ,x300766_g_MissionName7,1);
		AddQuestNumText(sceneId,300773 ,x300766_g_MissionName8,1);
		AddQuestNumText(sceneId,300784 ,x300766_g_MissionName9,1);
		AddQuestNumText(sceneId,300830 ,x300766_g_MissionName10,1);
		AddQuestText( sceneId,Readme)
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId);
		
		
end



--点击（确定）
function x300766_ProcAcceptCheck( sceneId, selfId, NPCId )

end



--**********************************
--接受
--**********************************
function x300766_ProcAccept( sceneId, selfId )
end
--**********************************
--放弃
--**********************************
function x300766_ProcQuestAbandon( sceneId, selfId, MissionId )
end
--**********************************
--继续
--**********************************
function x300766_OnContinue( sceneId, selfId, targetId )
end
--**********************************
--检测是否可以提交
--**********************************
function x300766_CheckSubmit( sceneId, selfId )
end
--**********************************
--提交
--**********************************
function x300766_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end
--**********************************
--杀死怪物或玩家
--**********************************
function x300766_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end
--**********************************
--进入区域事件
--**********************************
function x300766_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end
--**********************************
--道具改变
--**********************************
function x300766_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end