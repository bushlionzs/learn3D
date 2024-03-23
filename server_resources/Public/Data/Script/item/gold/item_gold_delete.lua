
-----------------------------------------------------------------------
x405500_g_scriptId = 405500 
function x405500_ProcEventEntry( sceneId, selfId, BagIndex )
	local money = GetMoney(sceneId, selfId, 2)
	if CostMoney(sceneId, selfId, 2, money, 307) == 1 then
		DelItemByIndexInBag(sceneId, selfId, BagIndex, 1, 107)
		local strText = "您使用了道具清除了现金"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, strText)
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId, selfId)
		Msg2Player(sceneId,selfId,strText, 8, 2)
	end
end

function x405500_IsSkillLikeScript( sceneId, selfId)
	return 0; --这个脚本需要动作支持    
	--返回0，走上面的ProcEventEntry逻辑
	--返回1，走下面的逻辑
end

function x405500_CancelImpacts( sceneId, selfId )
	return 0; --不需要这个接口，但要保留空函数,并且始终返回0。
end

function x405500_OnConditionCheck( sceneId, selfId )
	return 0
end

function x405500_OnDeplete( sceneId, selfId )

	return 0
end

function x405500_OnActivateOnce( sceneId, selfId )
end

function x405500_OnActivateEachTick( sceneId, selfId)
	return 1; --不是引导性脚本, 只保留空函数.
end

