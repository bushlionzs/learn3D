
x413300_g_scriptId = 413300
x413300_g_Impact1 = 7528 --效果ID，先无视好了

function x413300_ProcEventEntry( sceneId, selfId, bagIndex )

		local bCplay =  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem", sceneId, selfId, bagIndex, x413300_g_Impact1 )
    
    if bCplay == 1 then
        SendSpecificImpactToUnit(sceneId, selfId, selfId, selfId, x413300_g_Impact1, 0);
    end

    return bCplay
end

function x413300_IsSkillLikeScript( sceneId, selfId)
	return 0; --这个脚本需要动作支持    
	--返回0，走上面的ProcEventEntry逻辑
	--返回1，走下面的逻辑

end

function x413300_CancelImpacts( sceneId, selfId )
	return 0; --不需要这个接口，但要保留空函数,并且始终返回0。
end

function x413300_OnConditionCheck( sceneId, selfId )
	return 0
end

function x413300_OnDeplete( sceneId, selfId )
	return 0
end

function x413300_OnActivateOnce( sceneId, selfId )
end

function x413300_OnActivateEachTick( sceneId, selfId)
	return 1; --不是引导性脚本, 只保留空函数.
end
