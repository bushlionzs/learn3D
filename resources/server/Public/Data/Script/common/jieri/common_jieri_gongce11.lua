
x350010_g_ScriptId = 350010
x350010_g_MissionName = "祈福种子介绍"
x350010_g_AwardInfo = "\n\t#Y\n\t#Y祈福种子：\n\t#W每天可以用来祈福1次，祈福后会获得随机金币商城道具的奖励。\n\t#Y黄金祈福种子：\n\t#W黄金祈福种子可以一直进行祈福，每次祈福后都会获得随机金币商城道具的奖励。"

--点击（NPC）
function x350010_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

	AddQuestNumText(sceneId,x350010_g_ScriptId,x350010_g_MissionName,0,-1)
	return 0
	
end



--点击（按钮）点击该任务后执行此脚本
function x350010_ProcEventEntry( sceneId, selfId, targetId,state,index )	
	
	BeginQuestEvent(sceneId)
	AddQuestText(sceneId,x350010_g_AwardInfo)
	EndQuestEvent(sceneId)
	DispatchQuestEventList( sceneId,selfId,targetId )

	--x350010_DispatchMissionInfo( sceneId, selfId, targetId,index)

end

function x350010_DispatchMissionInfo( sceneId, selfId, targetId,index)


end



--**********************************
--接受
--**********************************
function x350010_ProcAccept( sceneId, selfId )
end

function x350010_ProcAcceptCheck( sceneId, selfId, NPCId )
	return 1
end
--点击（确定）
function x350010_ProcQuestAccept( sceneId, selfId, NPCId )
end

--**********************************
--放弃
--**********************************
function x350010_ProcQuestAbandon( sceneId, selfId, MissionId )
end
--**********************************
--继续
--**********************************
function x350010_OnContinue( sceneId, selfId, targetId )
end
--**********************************
--检测是否可以提交
--**********************************
function x350010_CheckSubmit( sceneId, selfId )
end
--**********************************
--提交
--**********************************
function x350010_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end
--**********************************
--杀死怪物或玩家
--**********************************
function x350010_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end
--**********************************
--进入区域