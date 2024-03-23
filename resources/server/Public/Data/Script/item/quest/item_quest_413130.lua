
x413130_g_scriptId = 413130 
x413130_g_FarScriptId	= 300230

function x413130_ProcEventEntry( sceneId, selfId, bagIndex )
	return CallScriptFunction( x413130_g_FarScriptId, "OnUseItem", sceneId, selfId, bagIndex )
end

function x413130_IsSkillLikeScript( sceneId, selfId)
	return 0; --这个脚本需要动作支持    
	--返回0，走上面的ProcEventEntry逻辑
	--返回1，走下面的逻辑

end

function x413130_CancelImpacts( sceneId, selfId )
	return 0; --不需要这个接口，但要保留空函数,并且始终返回0。

end

function x413130_OnConditionCheck( sceneId, selfId )
	return 0
end

function x413130_OnDeplete( sceneId, selfId )
	return 0
end

function x413130_OnActivateOnce( sceneId, selfId )
end

function x413130_OnActivateEachTick( sceneId, selfId)
	return 1; --不是引导性脚本, 只保留空函数.
end
