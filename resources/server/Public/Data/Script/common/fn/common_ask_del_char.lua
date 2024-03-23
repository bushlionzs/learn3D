
x561102_g_ScriptId = 561102
x561102_g_MissionName = "删除角色"

--点击（NPC）
function x561102_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

	AddQuestNumText(sceneId,561102,x561102_g_MissionName,0,-1)
	
end



--点击（按钮）点击该任务后执行此脚本
function x561102_ProcEventEntry( sceneId, selfId, targetId,state,index )	

	BeginQuestEvent(sceneId)
	AddQuestText(sceneId,"\t你确定要删除吗？")
	EndQuestEvent(sceneId)
	DispatchQuestEventList(sceneId,selfId,targetId)
	DispatchQuestInfo(sceneId, selfId, targetId, 561102, -1);

end


--点击（确定）
function x561102_ProcAcceptCheck( sceneId, selfId, NPCId )
	
	return 1

end


--**********************************
--接受
--**********************************
function x561102_ProcAccept( sceneId, selfId )

	if x561102_IsCanDeleteChar( sceneId, selfId ) == 1 then
		AskDeleteChar( sceneId, selfId )
	end

end

--超级密码验证通过后的处理
function x561102_OnDeleteChar( sceneId, selfId )

	if x561102_IsCanDeleteChar( sceneId, selfId ) == 1 then
		DeleteChar( sceneId, selfId )
	end

end

function x561102_IsCanDeleteChar( sceneId, selfId )

	if CountryGetOfficial( sceneId, selfId ) > 0 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"删除角色前请先解除国家内的一切职务。")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return 0		
	end

	--判断是否在帮会中
	if GetGuildID( sceneId, selfId ) ~= -1 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"删除角色前请先退出帮会。")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return 0
	end

	--是否结婚
	if IsMarried( sceneId, selfId ) > 0 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"删除角色前请先离婚。")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return 0
	end

	--是否解除师徒关系
	if IsHaveMaster( sceneId, selfId ) > 0 or IsHavePrentice( sceneId, selfId ) > 0 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"删除角色前请先解除师徒关系。")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return 0
	end

	--是否还有好友
	if IsHaveFriend( sceneId, selfId ) > 0 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"删除角色前请先删除所有好友。")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return 0
	end	
	
	return 1

end


--**********************************
--放弃
--**********************************
function x561102_ProcQuestAbandon( sceneId, selfId, MissionId )
end
--**********************************
--继续
--**********************************
function x561102_OnContinue( sceneId, selfId, targetId )
end
--**********************************
--检测是否可以提交
--**********************************
function x561102_CheckSubmit( sceneId, selfId )
end
--**********************************
--提交
--**********************************
function x561102_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end
--**********************************
--杀死怪物或玩家
--**********************************
function x561102_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end
--**********************************
--进入区域事件
--**********************************
function x561102_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end
--**********************************
--道具改变
--**********************************
function x561102_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end