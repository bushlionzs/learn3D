





x400203_g_scriptId = 400203 
x400203_g_Impact1 = 3001 --效果ID，先无视好了

function x400203_ProcEventEntry( sceneId, selfId, BagIndex )
			CallScriptFunction( MISSION_SCRIPT, "PositionUseItem", sceneId, selfId, BagIndex, x400203_g_Impact1 )
		if GetItemCount(sceneId,selfId,13020301) == 0 then
		BeginAddItem(sceneId)                                                    
		AddItem( sceneId,13020302, 1 )   
		EndAddItem(sceneId,selfId)
		AddItemListToPlayer(sceneId,selfId) 
		end
	

end

function x400203_IsSkillLikeScript( sceneId, selfId)
	return 0; --这个脚本需要动作支持    
	--返回0，走上面的ProcEventEntry逻辑
	--返回1，走下面的逻辑
end

function x400203_CancelImpacts( sceneId, selfId )
	return 0; --不需要这个接口，但要保留空函数,并且始终返回0。
end

function x400203_OnConditionCheck( sceneId, selfId )
	return 0
end

function x400203_OnDeplete( sceneId, selfId )

	return 0
end

function x400203_OnActivateOnce( sceneId, selfId )
end

function x400203_OnActivateEachTick( sceneId, selfId)
	return 1; --不是引导性脚本, 只保留空函数.
end
