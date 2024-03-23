





x400211_g_scriptId = 400211 
x400211_g_Impact1 = 7528 --效果ID，先无视好了

function x400211_ProcEventEntry( sceneId, selfId, BagIndex )
			local bCplay =  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem", sceneId, selfId, BagIndex, -1 )
    
    if bCplay == 1 then
    		if GetItemCount(sceneId,selfId,13030086) == 0 then
					BeginAddItem(sceneId)                                                    
					AddItem( sceneId,13030087, 1 )   
					EndAddItem(sceneId,selfId)
					AddItemListToPlayer(sceneId,selfId) 
					CallScriptFunction( UTILITY_SCRIPT, "PlayEffect", sceneId, selfId, 1 )
					CallScriptFunction( UTILITY_SCRIPT, "PlayEffect", sceneId, selfId, 2 )
					CallScriptFunction( UTILITY_SCRIPT, "PlayEffect", sceneId, selfId, 3 )
				end
    end

    return bCplay
		
	

end

function x400211_IsSkillLikeScript( sceneId, selfId)
	return 0; --这个脚本需要动作支持    
	--返回0，走上面的ProcEventEntry逻辑
	--返回1，走下面的逻辑
end

function x400211_CancelImpacts( sceneId, selfId )
	return 0; --不需要这个接口，但要保留空函数,并且始终返回0。
end

function x400211_OnConditionCheck( sceneId, selfId )
	return 0
end

function x400211_OnDeplete( sceneId, selfId )

	return 0
end

function x400211_OnActivateOnce( sceneId, selfId )
end

function x400211_OnActivateEachTick( sceneId, selfId)
	return 1; --不是引导性脚本, 只保留空函数.
end
