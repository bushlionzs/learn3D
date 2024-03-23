
x300579_g_scriptId = 300579

x300579_g_MissionScriptId 		= 	300576 

function x300579_ProcEventEntry( sceneId, selfId, bagIndex )
		local bCplay =  CallScriptFunction( x300579_g_MissionScriptId, "PositionUseItem", sceneId, selfId, bagIndex )
    
    
end

function x300579_IsSkillLikeScript( sceneId, selfId)
	return 0; --这个脚本需要动作支持    
	--返回0，走上面的ProcEventEntry逻辑
	--返回1，走下面的逻辑

 end

function x300579_CancelImpacts( sceneId, selfId )
	return 0; --不需要这个接口，但要保留空函数,并且始终返回0。
 
end

function x300579_OnConditionCheck( sceneId, selfId )
	return 0
end

function x300579_OnDeplete( sceneId, selfId )
	return 0
end

function x300579_OnActivateOnce( sceneId, selfId )
end

function x300579_OnActivateEachTick( sceneId, selfId)
	return 1; --不是引导性脚本, 只保留空函数.
end
