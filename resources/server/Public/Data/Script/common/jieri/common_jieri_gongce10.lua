
x350009_g_ScriptId = 350009
x350009_g_MissionName = "关于圣诞许愿和圣诞祈福"
x350009_g_AwardInfo = "\n#Y许愿种子：#W\n\t许愿种子，代表着真诚的许诺和美好的愿望，使用许愿种子后，可以让好运一直伴随在你的身边。\n\t在活动期间每天可以许愿十六次，每次许愿需要3个许愿种子。"
x350009_g_AwardInfo1 ="\n#Y祈福种子，#W\n\t祈福种子，代表着衷心的祈祷和善意的祝福，使用祈福种子后，有可能会获得神秘的礼物哦。\n\t在活动期间每天都可以祈福，祈福后会获得神秘礼品。"
--点击（NPC）
function x350009_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

	AddQuestNumText(sceneId,x350009_g_ScriptId,x350009_g_MissionName,0,-1)
	return 0
	
end



--点击（按钮）点击该任务后执行此脚本
function x350009_ProcEventEntry( sceneId, selfId, targetId,state,index )	
	
	BeginQuestEvent(sceneId)
	AddQuestText(sceneId,x350009_g_AwardInfo)
	AddQuestText(sceneId,x350009_g_AwardInfo1)
	EndQuestEvent(sceneId)
	DispatchQuestEventList( sceneId,selfId,targetId )

	--x350009_DispatchMissionInfo( sceneId, selfId, targetId,index)

end

function x350009_DispatchMissionInfo( sceneId, selfId, targetId,index)


end



--**********************************
--接受
--**********************************
function x350009_ProcAccept( sceneId, selfId )
end

function x350009_ProcAcceptCheck( sceneId, selfId, NPCId )
	return 1
end
--点击（确定）
function x350009_ProcQuestAccept( sceneId, selfId, NPCId )
end

--**********************************
--放弃
--**********************************
function x350009_ProcQuestAbandon( sceneId, selfId, MissionId )
end
--**********************************
--继续
--**********************************
function x350009_OnContinue( sceneId, selfId, targetId )
end
--**********************************
--检测是否可以提交
--**********************************
function x350009_CheckSubmit( sceneId, selfId )
end
--**********************************
--提交
--**********************************
function x350009_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end
--**********************************
--杀死怪物或玩家
--**********************************
function x350009_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end
--**********************************
--进入区域