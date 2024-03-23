
x413302_g_scriptId = 413302
x413302_g_Impact1 = 7524 --效果ID，先无视好了


function x413302_ProcEventEntry( sceneId, selfId, bagIndex )
	local bCplay =  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem", sceneId, selfId, bagIndex, x413302_g_Impact1 )
    
    if bCplay == 1 then
        SendSpecificImpactToUnit(sceneId, selfId, selfId, selfId, x413302_g_Impact1, 0);
    end

    return bCplay
end

function x413302_IsSkillLikeScript( sceneId, selfId)
	return 0; --这个脚本需要动作支持    
	--返回0，走上面的ProcEventEntry逻辑
	--返回1，走下面的逻辑

end

function x413302_CancelImpacts( sceneId, selfId )
	return 0; --不需要这个接口，但要保留空函数,并且始终返回0。

end

function x413302_OnConditionCheck( sceneId, selfId )
	return 0
end

function x413302_OnDeplete( sceneId, selfId )
	return 0
end

function x413302_OnActivateOnce( sceneId, selfId )
end

function x413302_OnActivateEachTick( sceneId, selfId)
	return 1; --不是引导性脚本, 只保留空函数.
end
