
x300765_g_ScriptId 					= 	300765  
x300765_g_MissionName0= "【领地介绍】"
x300765_g_MissionName1= "【报名条件】"
x300765_g_MissionName2= "【领地争夺战规则】"

function x300765_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	AddQuestNumText(sceneId,300765,"【领地争夺战说明】",1)	
end



--点击（按钮）点击该任务后执行此脚本
function x300765_ProcEventEntry( sceneId, selfId, targetId)		
			BeginQuestEvent(sceneId)
			local Readme_1 = "#Y【领地争夺战说明】#r#W #r"						
			local Readme_2 = "\t如果您想在成吉思汗的世界里体验攻城掠地的快感，就要对领地具有一定的了解才能得心应手。 #r"			
			local Readme_3 = "\t请点击下列对应按钮，您可以查询领地相关信息:"			
			local Readme = Readme_1..Readme_2..Readme_3
			
			AddQuestNumText(sceneId,300935 ,x300765_g_MissionName0,1);
			AddQuestNumText(sceneId,300936 ,x300765_g_MissionName1,1);		
			AddQuestNumText(sceneId,300937 ,x300765_g_MissionName2,1);			
			AddQuestText( sceneId,Readme)
			EndQuestEvent(sceneId)
			DispatchQuestEventList(sceneId,selfId,targetId);
end



function x300765_ProcAcceptCheck( sceneId, selfId, NPCId )

end



--**********************************
--接受
--**********************************
function x300765_ProcAccept( sceneId, selfId )
end
--**********************************
--放弃
--**********************************
function x300765_ProcQuestAbandon( sceneId, selfId, MissionId )
end
--**********************************
--继续
--**********************************
function x300765_OnContinue( sceneId, selfId, targetId )
end
--**********************************
--检测是否可以提交
--**********************************
function x300765_CheckSubmit( sceneId, selfId )
end
--**********************************
--提交
--**********************************
function x300765_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end
--**********************************
--杀死怪物或玩家
--**********************************
function x300765_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end
--**********************************
--进入区域事件
--**********************************
function x300765_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end
--**********************************
--道具改变
--**********************************
function x300765_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end