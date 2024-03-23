





x400216_g_scriptId = 400216 
x400216_g_Impact1 = 3001 --效果ID，先无视好了

function x400216_ProcEventEntry( sceneId, selfId, BagIndex )
			CallScriptFunction( MISSION_SCRIPT, "PositionUseItem", sceneId, selfId, BagIndex, x400216_g_Impact1 )
			if GetItemCount(sceneId,selfId,13020412) == 0 then
						local talknpc =FindMonsterByGUID( sceneId,112027)
						if IsObjValid (sceneId,talknpc) == 1 then
								NpcTalk(sceneId, talknpc, "万岁！！成吉思汗万岁！", -1)
						end
						local talknpc2 =FindMonsterByGUID( sceneId,112028)
						if IsObjValid (sceneId,talknpc2) == 1 then
								NpcTalk(sceneId, talknpc2, "万民之主成吉思汗万岁！", -1)
						end
			end
	

end

function x400216_IsSkillLikeScript( sceneId, selfId)
	return 0; --这个脚本需要动作支持    
	--返回0，走上面的ProcEventEntry逻辑
	--返回1，走下面的逻辑
end

function x400216_CancelImpacts( sceneId, selfId )
	return 0; --不需要这个接口，但要保留空函数,并且始终返回0。
end

function x400216_OnConditionCheck( sceneId, selfId )
	return 0
end

function x400216_OnDeplete( sceneId, selfId )

	return 0
end

function x400216_OnActivateOnce( sceneId, selfId )
end

function x400216_OnActivateEachTick( sceneId, selfId)
	return 1; --不是引导性脚本, 只保留空函数.
end
