





x400212_g_scriptId = 400212 
x400212_g_Impact1 = 3001 --效果ID，先无视好了

function x400212_ProcEventEntry( sceneId, selfId, BagIndex )
			CallScriptFunction( MISSION_SCRIPT, "PositionUseItem", sceneId, selfId, BagIndex, x400212_g_Impact1 )
			if GetItemCount(sceneId,selfId,13020206) == 0 then
					BeginAddItem(sceneId)                                                    
					AddItem( sceneId,13020214, 1 )   
					EndAddItem(sceneId,selfId)
					AddItemListToPlayer(sceneId,selfId) 
		end

end

function x400212_IsSkillLikeScript( sceneId, selfId)
	return 0; --这个脚本需要动作支持    
	--返回0，走上面的ProcEventEntry逻辑
	--返回1，走下面的逻辑
end

function x400212_CancelImpacts( sceneId, selfId )
	return 0; --不需要这个接口，但要保留空函数,并且始终返回0。
end

function x400212_OnConditionCheck( sceneId, selfId )
	return 0
end

function x400212_OnDeplete( sceneId, selfId )

	return 0
end

function x400212_OnActivateOnce( sceneId, selfId )
end

function x400212_OnActivateEachTick( sceneId, selfId)
	return 1; --不是引导性脚本, 只保留空函数.
end
