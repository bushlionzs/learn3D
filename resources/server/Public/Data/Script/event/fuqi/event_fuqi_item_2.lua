
x300355_g_scriptId = 300355
x300355_g_Impact1 = -1 --效果ID，先无视好了

function x300355_ProcEventEntry( sceneId, selfId, bagIndex )
		local exp =  1000
		AddExp(sceneId, selfId, exp);

    return 1
end

function x300355_IsSkillLikeScript( sceneId, selfId)
	return 0; --这个脚本需要动作支持    
	--返回0，走上面的ProcEventEntry逻辑
	--返回1，走下面的逻辑

 end

function x300355_CancelImpacts( sceneId, selfId )
	return 0; --不需要这个接口，但要保留空函数,并且始终返回0。
 
end

function x300355_OnConditionCheck( sceneId, selfId )
	return 0
end

function x300355_OnDeplete( sceneId, selfId )
	return 0
end

function x300355_OnActivateOnce( sceneId, selfId )
end

function x300355_OnActivateEachTick( sceneId, selfId)
	return 1; --不是引导性脚本, 只保留空函数.
end
