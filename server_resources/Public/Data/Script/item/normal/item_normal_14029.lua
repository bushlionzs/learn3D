x414029_g_scriptId = 414029 

function x414029_ProcEventEntry( sceneId, selfId, BagIndex )
	CallScriptFunction( 270300, "ItemProcEventEntry", sceneId, selfId, BagIndex )
end

function x414029_IsSkillLikeScript( sceneId, selfId)
	return 0; --这个脚本需要动作支持    
	--返回0，走上面的ProcEventEntry逻辑
	--返回1，走下面的逻辑
end

function x414029_CancelImpacts( sceneId, selfId )
	return 0; --不需要这个接口，但要保留空函数,并且始终返回0。
end

function x414029_OnConditionCheck( sceneId, selfId )
	return 0
end

function x414029_OnDeplete( sceneId, selfId )

	return 0
end

function x414029_OnActivateOnce( sceneId, selfId )
end

function x414029_OnActivateEachTick( sceneId, selfId)
	return 1; --不是引导性脚本, 只保留空函数.
end
