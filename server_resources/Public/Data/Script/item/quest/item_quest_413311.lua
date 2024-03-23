x413311_g_scriptId = 413311 
x413311_g_Impact1 = 3001 --效果ID，先无视好了

function x413311_ProcEventEntry( sceneId, selfId, BagIndex )
--local bCplay =  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem", sceneId, selfId, BagIndex, -1 )
 --if bCplay == 1 then
			CallScriptFunction( MISSION_SCRIPT, "PositionUseItem", sceneId, selfId, BagIndex,x413311_g_Impact1  )
		if GetItemCount(sceneId,selfId,13040030) == 0 then
		NewWorld(sceneId,selfId,2,213,137,413311)
		CallScriptFunction( UTILITY_SCRIPT, "PlayEffect", sceneId, selfId, 15 )
    CallScriptFunction( UTILITY_SCRIPT, "PlayEffect", sceneId, selfId, 16 )
    CallScriptFunction( UTILITY_SCRIPT, "PlayEffect", sceneId, selfId, 17 )
		end
	

end

function x413311_IsSkillLikeScript( sceneId, selfId)
	return 0; --这个脚本需要动作支持    
	--返回0，走上面的ProcEventEntry逻辑
	--返回1，走下面的逻辑
end

function x413311_CancelImpacts( sceneId, selfId )
	return 0; --不需要这个接口，但要保留空函数,并且始终返回0。
end

function x413311_OnConditionCheck( sceneId, selfId )
	return 0
end

function x413311_OnDeplete( sceneId, selfId )

	return 0
end

function x413311_OnActivateOnce( sceneId, selfId )
end

function x413311_OnActivateEachTick( sceneId, selfId)
	return 1; --不是引导性脚本, 只保留空函数.
end
