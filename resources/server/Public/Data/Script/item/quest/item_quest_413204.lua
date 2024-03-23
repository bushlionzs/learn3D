
x413204_g_scriptId = 413204 
x413204_g_Impact1 = 8314 --效果ID，先无视好了

function x413204_ProcEventEntry( sceneId, selfId, bagIndex )
	return CallScriptFunction( MISSION_SCRIPT, "PositionUseItem", sceneId, selfId, bagIndex, x413204_g_Impact1 )
end

function x413204_IsSkillLikeScript( sceneId, selfId)
	return 0; --这个脚本需要动作支持    
	--返回0，走上面的ProcEventEntry逻辑
	--返回1，走下面的逻辑

end

function x413204_CancelImpacts( sceneId, selfId )
	return 0; --不需要这个接口，但要保留空函数,并且始终返回0。

end

function x413204_OnConditionCheck( sceneId, selfId )
	return 0
end

function x413204_OnDeplete( sceneId, selfId )
	return 0
end

function x413204_OnActivateOnce( sceneId, selfId )
end

function x413204_OnActivateEachTick( sceneId, selfId)
	return 1; --不是引导性脚本, 只保留空函数.
end
