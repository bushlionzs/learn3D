--屠龙卡礼包礼花特效脚本：蓝色礼花 12030334


x418022_g_scriptId = 418022
x418022_g_Impact1 = 7519 --效果ID，先无视好了
x418022_g_item = 12030334

function x418022_ProcEventEntry( sceneId, selfId, bagIndex )
		
--    if yanhua == 1 then 
--    		DelItem( sceneId,selfId,x418022_g_item,1 )
--    end
    
end

function x418022_IsSkillLikeScript( sceneId, selfId)
	return 1; --这个脚本需要动作支持    
	--返回0，走上面的ProcEventEntry逻辑
	--返回1，走下面的逻辑

end

function x418022_CancelImpacts( sceneId, selfId )
	return 0; --不需要这个接口，但要保留空函数,并且始终返回0。

end

function x418022_OnConditionCheck( sceneId, selfId )
	--校验使用的物品
	
	if(1~=VerifyUsedItem(sceneId, selfId)) then
		return 0
	end
	return 1; --不需要任何条件，并且始终返回1。
	
end

function x418022_OnDeplete( sceneId, selfId )
	return 1
end

function x418022_OnActivateOnce( sceneId, selfId )

	if(DepletingUsedItem(sceneId, selfId)) == 1 then
		local yanhua=   SendSpecificImpactToUnit(sceneId, selfId, selfId, selfId, x418021_g_Impact1, 0);
	else
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"使用物品异常！")
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
	end

end

function x418022_OnActivateEachTick( sceneId, selfId)
	return 1; --不是引导性脚本, 只保留空函数.
end
