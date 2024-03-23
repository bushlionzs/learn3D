
x350011_g_ScriptId = 350011
x350011_g_MissionName = "圣诞上线送礼"
x350011_g_AwardInfo = "\t从#G12月22日起至1月4日#W，每天的#G12：00—12：10、15：00—15：10、18：00—18：10和21：00—21：10，#W各位玩家可以在这里领取圣诞礼物。\n\t#G许愿种子#W和#G祈福种子#W就包含在这些圣诞礼物中，你可以使用许愿种子或祈福种子去圣诞树处许愿祈福。"

--点击（NPC）
function x350011_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

	AddQuestNumText(sceneId,x350011_g_ScriptId,x350011_g_MissionName,0,-1)
	return 0
	
end



--点击（按钮）点击该任务后执行此脚本
function x350011_ProcEventEntry( sceneId, selfId, targetId,state,index )	
	
	BeginQuestEvent(sceneId)
	AddQuestText(sceneId,x350011_g_AwardInfo)
	EndQuestEvent(sceneId)
	DispatchQuestEventList( sceneId,selfId,targetId )

	--x350011_DispatchMissionInfo( sceneId, selfId, targetId,index)

end

function x350011_DispatchMissionInfo( sceneId, selfId, targetId,index)


end



--**********************************
--接受
--**********************************
function x350011_ProcAccept( sceneId, selfId )
end

function x350011_ProcAcceptCheck( sceneId, selfId, NPCId )
	return 1
end
--点击（确定）
function x350011_ProcQuestAccept( sceneId, selfId, NPCId )
end

--**********************************
--放弃
--**********************************
function x350011_ProcQuestAbandon( sceneId, selfId, MissionId )
end
--**********************************
--继续
--**********************************
function x350011_OnContinue( sceneId, selfId, targetId )
end
--**********************************
--检测是否可以提交
--**********************************
function x350011_CheckSubmit( sceneId, selfId )
end
--**********************************
--提交
--**********************************
function x350011_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end
--**********************************
--杀死怪物或玩家
--**********************************
function x350011_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end
--**********************************
--进入区域