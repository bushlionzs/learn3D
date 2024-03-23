--【新手】第一匹马

--MisDescBegin
x310347_g_ScriptId = 310347
x310347_g_MissionIdPre =-1
x310347_g_MissionId = 9090
x310347_g_LevelLess	= 	65 
x310347_g_MissionIdNext = 3709
x310347_g_Name	={}
x310347_g_ExtTarget={{type=20,n=1,target="抓到一匹@npc_134027"}}
x310347_g_MissionName="【新手】白鹿长老的考验"
x310347_g_MissionInfo="\t在成吉思汗的世界中，想要成为真正的英雄，一匹好马是你必不可少的伙伴。\n\t看见我身后的这些马了吧，你只要将鼠标移动到小马驹身上，点击左键就可以捕捉了。\n\t现在，按我教给你的方法，去选择一匹来做为你第一个伙伴吧。"  --任务描述
x310347_g_MissionTarget="抓到一匹@npc_134027"		
x310347_g_MissionCompleted="\t牢记驯服它们的方法，或许今后你将会得到更多更好的坐骑。"					--完成任务npc说话的话
x310347_g_ContinueInfo="\t你驯服它了么？"
x310347_g_MissionHelp =	"#G将鼠标移动至#R马匹#G上，点击#R左键#G一下，耐心等待抓马读条完毕，系统会提示您捕捉#R成功#G，如果失败了，很可能是由于您和马的#R距离过远#G导致的，您只需要#R靠近马匹#G，重新抓一次即可。#W"
x310347_g_DemandItem ={}
x310347_g_ExpBonus = 310
x310347_g_BonusMoney1 =5				
x310347_g_BonusMoney2 =0
x310347_g_BonusMoney3 =0
x310347_g_BonusMoney4 =0
x310347_g_BonusMoney5 =12
x310347_g_BonusMoney6 =0
x310347_g_BonusItem	=	{}
x310347_g_BonusChoiceItem ={}
x310347_g_NpcGUID = {}
--MisDescEnd
--**********************************

function x310347_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)   
print(545)
	if GetLevel( sceneId, selfId)>2 then
		return
	end
end

function x310347_DispatchMissionInfo( sceneId, selfId, NPCId )
		
end
--**********************************

function x310347_ProcEventEntry(sceneId, selfId, NPCId, MissionId)	--点击该任务后执行此脚本
	
end
--**********************************

function x310347_ProcAcceptCheck(sceneId, selfId, NPCId)

end
--**********************************
function x310347_CheckSubmit( sceneId, selfId, NPCId)

end
--**********************************
function x310347_ProcQuestAccept( sceneId, selfId, NPCId, MissionId )

end
--**********************************

function x310347_ProcQuestAbandon(sceneId, selfId, MissionId)

end
--**********************************
function x310347_CheckPlayerBagFull( sceneId ,selfId,selectRadioId )
	
end
--**********************************
function x310347_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)
	
end

function x310347_GetBonus( sceneId, selfId,NpcID)

end

function x310347_Msg2toplayer( sceneId, selfId,type)

end

function x310347_ProcQuestHorseChanged(sceneId, selfId, horseId, MissionId)
	x310347_CheckSubmit( sceneId, selfId)
end

function x310347_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
end


function x310347_ProcAreaEntered(sceneId, selfId, zoneId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "ProcAreaEntered",sceneId, selfId, zoneId, MissionId )	

end

function x310347_ProcTiming(sceneId, selfId, ScriptId, MissionId)
	 CallScriptFunction( MISSION_SCRIPT, "ProcTiming",sceneId, selfId, ScriptId, MissionId )
		
end

function x310347_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcAreaLeaved",sceneId, selfId, ScriptId, MissionId)
end

function x310347_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcQuestItemChanged",sceneId, selfId, itemdataId, MissionId )
end


function x310347_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )

end

function x310347_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x310347_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x310347_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x310347_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x310347_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x310347_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end
