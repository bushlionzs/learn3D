x310343_g_scriptId = 310343 


x310343_g_DestSceneName = "撒马尔罕"
x310343_g_DestSceneId = {11}
x310343_g_BossType = {17014,17015,17016,17017,17018,17019,17020}

function x310343_ProcEventEntry( sceneId, selfId, BagIndex )
	local PlayerPosX,PlayerPosZ = GetWorldPos( sceneId, selfId )

	--秦岭
	if sceneId == 11 then
	local bossnb = random(1,7)
	local ret = CreateMonster( sceneId, x310343_g_BossType[bossnb], PlayerPosX, PlayerPosZ, 1, -1, x310343_g_scriptId, -1, 21)

		if ret > 0 then
			DelItem( sceneId, selfId, 12035001, 1); --删除物品
			local message = "札兰丁的部将出现了！"
			Msg2Player(sceneId,selfId,message, 8, 2)
			Msg2Player(sceneId,selfId,message, 8, 3)
			
		end
	
	
	else
		local strText = format("这里无法召出札兰丁部将，请前往撒马尔罕" )
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, strText)
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId, selfId)
		Msg2Player(sceneId,selfId,strText, 8, 2)
	end	
end

function x310343_IsSkillLikeScript( sceneId, selfId)
	return 0; --这个脚本需要动作支持    
	--返回0，走上面的ProcEventEntry逻辑
	--返回1，走下面的逻辑
end

function x310343_CancelImpacts( sceneId, selfId )
	return 0; --不需要这个接口，但要保留空函数,并且始终返回0。
end

function x310343_OnConditionCheck( sceneId, selfId )
	return 0
end

function x310343_OnDeplete( sceneId, selfId )

	return 0
end

function x310343_OnActivateOnce( sceneId, selfId )
end

function x310343_OnActivateEachTick( sceneId, selfId)
	return 1; --不是引导性脚本, 只保留空函数.
end

function x310343_OnDie(sceneId, selfId, killerId)--怪死亡添加日志
	
	GamePlayScriptLog(sceneId, killerId, 551)
				
end

