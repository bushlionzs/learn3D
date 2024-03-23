
x300353_g_scriptId = 300353
x300353_g_Impact1 = 7519 --效果ID，先无视好了

function x300353_ProcEventEntry( sceneId, selfId, bagIndex )
		local bCplay =  CallScriptFunction( 300352, "PositionUseItem", sceneId, selfId, bagIndex, x300353_g_Impact1 )
    
    if bCplay == 1 then
        SendSpecificImpactToUnit(sceneId, selfId, selfId, selfId, x300353_g_Impact1, 0);
    end

    return bCplay
end

function x300353_IsSkillLikeScript( sceneId, selfId)
	return 0; --这个脚本需要动作支持    
	--返回0，走上面的ProcEventEntry逻辑
	--返回1，走下面的逻辑

 end

function x300353_CancelImpacts( sceneId, selfId )
	return 0; --不需要这个接口，但要保留空函数,并且始终返回0。
 
end

function x300353_OnConditionCheck( sceneId, selfId )
	return 0
end

function x300353_OnDeplete( sceneId, selfId )
	return 0
end

function x300353_OnActivateOnce( sceneId, selfId )
end

function x300353_OnActivateEachTick( sceneId, selfId)
	return 1; --不是引导性脚本, 只保留空函数.
end
