x310021_g_scriptId = 310021 
x310021_g_Impact1 = 3001 --效果ID，先无视好了

function x310021_ProcEventEntry( sceneId, selfId, BagIndex )
	local ItemID = GetItemTableIndexByIndex( sceneId, selfId, BagIndex ) --得到物品ID
	local MissionId = GetQuestIDByItemIDNM( sceneId, selfId, ItemID )

	if MissionId == -1 then 	--没有找到这个任务
		return 0
	end

	if IsHaveQuestNM( sceneId, selfId, MissionId ) == 0 then	-- 如果没这个任务直接退出
		return 0
	end

	local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )
	local level = GetQuestParam( sceneId, selfId, misIndex, 2 ) 

	if MissionId>= 8000 and MissionId<=8004 then
		CallScriptFunction( 310020, "PositionUseItem", sceneId, selfId, BagIndex, x310021_g_Impact1 )
	elseif MissionId>=8005 and MissionId<=8009 then
		CallScriptFunction( 310022, "PositionUseItem", sceneId, selfId, BagIndex, x310021_g_Impact1 )
	end

end

function x310021_IsSkillLikeScript( sceneId, selfId)
	return 0; --这个脚本需要动作支持    
	--返回0，走上面的ProcEventEntry逻辑
	--返回1，走下面的逻辑
end

function x310021_CancelImpacts( sceneId, selfId )
	return 0; --不需要这个接口，但要保留空函数,并且始终返回0。
end

function x310021_OnConditionCheck( sceneId, selfId )
	return 0
end

function x310021_OnDeplete( sceneId, selfId )

	return 0
end

function x310021_OnActivateOnce( sceneId, selfId )
end

function x310021_OnActivateEachTick( sceneId, selfId)
	return 1; --不是引导性脚本, 只保留空函数.
end
