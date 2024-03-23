--到演示传送

x550007_g_ScriptId 					= 550007
x550007_g_MissionName				= "演示传送"
-------------------------
--***********************
--ProcEnumEvent
--***********************
-------------------------

function x550007_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
	
	AddQuestNumText(sceneId, x550007_g_ScriptId, x550007_g_MissionName);
	
end

-------------------------
--***********************
--ProcEventEntry
--***********************
-------------------------

function x550007_ProcEventEntry(sceneId, selfId, targetId)

		DispatchTransferType(sceneId, selfId, selfId, 8, -1)
end

-------------------------
--***********************
--ProcAcceptCheck
--***********************
-------------------------

function x550007_ProcAcceptCheck(sceneId, selfId, targetId)

end

-------------------------
--***********************
--ProcAccept
--***********************
-------------------------

function x550007_ProcAccept(sceneId, selfId, targetId)

end
function x550007_IsSkillLikeScript( sceneId, selfId)
	return 0; --这个脚本需要动作支持
end
function x550007_CancelImpacts( sceneId, selfId )
	return 0; --不需要这个接口，但要保留空函数,并且始终返回0。
end
function x550007_OnConditionCheck( sceneId, selfId )
	return 1
end
function x550007_OnDeplete( sceneId, selfId )
	DispatchTransferType(sceneId, selfId, selfId, 2, -1)
	return 0
end