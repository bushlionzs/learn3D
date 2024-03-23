





x280000_g_scriptId = 280000 
--x280000_g_Impact1 = 7528 --效果ID，先无视好了
x280000_g_PROTECTINFO={ScneneTimerIndex = -1,  StartTime = 0}


function x280000_ProcEventEntry( sceneId, selfId, BagIndex )
			local bCplay =  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem", sceneId, selfId, BagIndex, -1 )
    
    if bCplay == 1 then
   -- LuaScenceM2Player (sceneId,  selfId,  "丁磊是很纯洁的！", -1, 5, -1)
    LuaScenceM2Near(sceneId,  selfId, "重汉法，劝农桑，世祖当立为国策。", 5, -1)

			
    end

    return bCplay
		
	

end




function x280000_IsSkillLikeScript( sceneId, selfId)
	return 0; --这个脚本需要动作支持    
	--返回0，走上面的ProcEventEntry逻辑
	--返回1，走下面的逻辑
end

function x280000_CancelImpacts( sceneId, selfId )
	return 0; --不需要这个接口，但要保留空函数,并且始终返回0。
end

function x280000_OnConditionCheck( sceneId, selfId )
	return 0
end

function x280000_OnDeplete( sceneId, selfId )

	return 0
end

function x280000_OnActivateOnce( sceneId, selfId )
end

function x280000_OnActivateEachTick( sceneId, selfId)
	return 1; --不是引导性脚本, 只保留空函数.
end
