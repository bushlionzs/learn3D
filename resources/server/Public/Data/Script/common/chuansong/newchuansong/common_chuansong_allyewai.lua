--到所有场景

x550005_g_ScriptId 					= 550005
x550005_g_MissionName				= "所有场景"
-------------------------
--***********************
--ProcEnumEvent
--***********************
-------------------------

function x550005_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
	
	AddQuestNumText(sceneId, x550005_g_ScriptId, x550005_g_MissionName);
	
end

-------------------------
--***********************
--ProcEventEntry
--***********************
-------------------------

function x550005_ProcEventEntry(sceneId, selfId, targetId)

		DispatchTransferType(sceneId, selfId, selfId, 2, -1)
end

-------------------------
--***********************
--ProcAcceptCheck
--***********************
-------------------------

function x550005_ProcAcceptCheck(sceneId, selfId, targetId)

end

-------------------------
--***********************
--ProcAccept
--***********************
-------------------------

function x550005_ProcAccept(sceneId, selfId, targetId)

end
function x550005_IsSkillLikeScript( sceneId, selfId)
	return 0; --这个脚本需要动作支持
end
function x550005_CancelImpacts( sceneId, selfId )
	return 0; --不需要这个接口，但要保留空函数,并且始终返回0。
end
function x550005_OnConditionCheck( sceneId, selfId )
	return 1
end
function x550005_OnDeplete( sceneId, selfId )
	DispatchTransferType(sceneId, selfId, selfId, 2, -1)
	return 0
end