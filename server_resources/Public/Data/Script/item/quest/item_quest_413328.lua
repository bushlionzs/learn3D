


x413328_g_scriptId = 413328 
x413328_g_Impact1 = 3001 --效果ID，先无视好了

function x413328_ProcEventEntry( sceneId, selfId, BagIndex )
		CallScriptFunction( 888894,"OpenWorldDirectory",sceneId,selfId )
		CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 80,1 )
--		local ItemCount = GetItemCount(sceneId,selfId,12030214 )  
--		if ItemCount > 0 then                                               
--			DelItem( sceneId, selfId, 12030214 , 1 )   
--		end
		

end

function x413328_IsSkillLikeScript( sceneId, selfId)
	return 0; --这个脚本需要动作支持    
	--返回0，走上面的ProcEventEntry逻辑
	--返回1，走下面的逻辑
end

function x413328_CancelImpacts( sceneId, selfId )
	return 0; --不需要这个接口，但要保留空函数,并且始终返回0。
end

function x413328_OnConditionCheck( sceneId, selfId )
	return 0
end

function x413328_OnDeplete( sceneId, selfId )

	return 0
end

function x413328_OnActivateOnce( sceneId, selfId )
end

function x413328_OnActivateEachTick( sceneId, selfId)
	return 1; --不是引导性脚本, 只保留空函数.
end
