x413317_g_scriptId  = 413317--火炮弹脚本
x413317_g_Impact1   = 7520--效果ID，先无视好了
x413317_g_Impact2   = -1 --不用
--**********************************
--事件交互入口
--**********************************
function x413317_ProcEventEntry( sceneId, selfId, bagIndex )
			CallScriptFunction( 203315, "useitem", sceneId, selfId)
end


function x413317_IsSkillLikeScript( sceneId, selfId)
 
	return 0; --这个脚本需要动作支持    
	--返回0，走上面的ProcEventEntry逻辑
	--返回1，走下面的逻辑
end

function x413317_CancelImpacts( sceneId, selfId )
	return 0; --不需要这个接口，但要保留空函数,并且始终返回0。
end

function x413317_OnConditionCheck( sceneId, selfId )
	return 0
end

function x413317_OnDeplete( sceneId, selfId )

	return 1
end

function x413317_OnActivateOnce( sceneId, selfId )
end

function x413317_OnActivateEachTick( sceneId, selfId)
	return 1; --不是引导性脚本, 只保留空函数.
end
