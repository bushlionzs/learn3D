x300322_g_scriptId = 300322 

function x300322_ProcEventEntry( sceneId, selfId, BagIndex )

	local lastTime = GetPlayerRuntimeData( sceneId, selfId, RD_TONGQU_CD)
	local curTime = GetCurrentTime()
	local message;

	if curTime - lastTime < 10 then
		message = "真视眼镜每10秒内只能使用一次"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, message)
		DispatchQuestTips(sceneId, selfId)
		EndQuestEvent(sceneId)
		Msg2Player(sceneId,selfId,message, 8, 2)
		return
	end
	
	SetPlayerRuntimeData( sceneId, selfId, RD_TONGQU_CD, curTime)

	SendSpecificImpactToUnit(sceneId, selfId, selfId, selfId, 7515, 0)
	message = "你现在可以看到附近游走的生物了，请赶快进行捕捉吧！"
	BeginQuestEvent(sceneId)
	AddQuestText(sceneId, message)
	DispatchQuestTips(sceneId, selfId)
	EndQuestEvent(sceneId)
	Msg2Player(sceneId,selfId,message, 8, 2)
	DoAction(sceneId, selfId, 100, -1)
	SetViewBeastie( sceneId, selfId, 1 )

	return
end

function x300322_IsSkillLikeScript( sceneId, selfId)
	return 0; --这个脚本需要动作支持    
	--返回0，走上面的ProcEventEntry逻辑
	--返回1，走下面的逻辑
end

function x300322_CancelImpacts( sceneId, selfId )
	return 0; --不需要这个接口，但要保留空函数,并且始终返回0。
end

function x300322_OnConditionCheck( sceneId, selfId )
	return 0
end

function x300322_OnDeplete( sceneId, selfId )

	return 0
end

function x300322_OnActivateOnce( sceneId, selfId )
end

function x300322_OnActivateEachTick( sceneId, selfId)
	return 1; --不是引导性脚本, 只保留空函数.
end