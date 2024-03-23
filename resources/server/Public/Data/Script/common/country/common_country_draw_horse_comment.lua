
x300651_g_ScriptId 					= 	300651  
 
function x300651_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	AddQuestNumText(sceneId,300651,"【介绍】国王坐骑",1)	
end



--点击（按钮）点击该任务后执行此脚本
function x300651_ProcEventEntry( sceneId, selfId, targetId)		
		--local MissionName = x300767_g_MissionName;
		BeginQuestEvent(sceneId)
			local Readme_1 = "#Y【介绍】国王坐骑#r#W #r"			
			
			local Readme_2 = "\t如果您是#G国王或王后#W，您可以在我这里领取#R国王坐骑#W。#r"
			
			local Readme_3 = "\t领取国王坐骑时，您的#R坐骑栏内#W不能有国王骑乘。如果有，您可以#R选择放生#W。放生后，您可以#G再次领取国王坐骑#W。#r"
			
			local Readme_4 ="\t我们国家的国王坐骑有：#G30级坐骑，40级坐骑，50级坐骑，60级坐骑，70级坐骑，80级坐骑，90级坐骑，100级坐骑#W。#r"
			
			local Readme_5="\t领取时，会根据#R您当前的等级#W在您的坐骑栏内添加相应等级的坐骑。#r"
			
			local Readme = Readme_1..Readme_2..Readme_3..Readme_4..Readme_5
			
		AddQuestText( sceneId,Readme)
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId);
		
		
end



--点击（确定）
function x300651_ProcAcceptCheck( sceneId, selfId, NPCId )

end



--**********************************
--接受
--**********************************
function x300651_ProcAccept( sceneId, selfId )
end
--**********************************
--放弃
--**********************************
function x300651_ProcQuestAbandon( sceneId, selfId, MissionId )
end
--**********************************
--继续
--**********************************
function x300651_OnContinue( sceneId, selfId, targetId )
end
--**********************************
--检测是否可以提交
--**********************************
function x300651_CheckSubmit( sceneId, selfId )
end
--**********************************
--提交
--**********************************
function x300651_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end
--**********************************
--杀死怪物或玩家
--**********************************
function x300651_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end
--**********************************
--进入区域事件
--**********************************
function x300651_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end
--**********************************
--道具改变
--**********************************
function x300651_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end