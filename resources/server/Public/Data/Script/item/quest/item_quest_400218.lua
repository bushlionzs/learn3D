





x400218_g_scriptId = 400218 
x400218_g_Impact1 = 3001 --效果ID，先无视好了

function x400218_ProcEventEntry( sceneId, selfId, BagIndex )
		CallScriptFunction( 203311, "useitem", sceneId, selfId)
	

end

function x400218_IsSkillLikeScript( sceneId, selfId)
	return 0; --这个脚本需要动作支持    
	--返回0，走上面的ProcEventEntry逻辑
	--返回1，走下面的逻辑
end

function x400218_CancelImpacts( sceneId, selfId )
	return 0; --不需要这个接口，但要保留空函数,并且始终返回0。
end

function x400218_OnConditionCheck( sceneId, selfId )
	return 0
end

function x400218_OnDeplete( sceneId, selfId )

	return 0
end

function x400218_OnActivateOnce( sceneId, selfId )
end

function x400218_OnActivateEachTick( sceneId, selfId)
	return 1; --不是引导性脚本, 只保留空函数.
end
