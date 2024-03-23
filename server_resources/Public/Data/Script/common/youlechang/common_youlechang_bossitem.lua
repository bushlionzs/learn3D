x310326_g_scriptId = 310326 


x310326_g_DestSceneName = "阿尔金山"
x310326_g_DestSceneId = {8}
x310326_g_BossType = {17007,17008,17009,17010,17011,17012,17013}

function x310326_ProcEventEntry( sceneId, selfId, BagIndex )
	local PlayerPosX,PlayerPosZ = GetWorldPos( sceneId, selfId )

	--秦岭
	if sceneId == 8 then
	local bossnb = random(1,7)
	local ret = CreateMonster( sceneId, x310326_g_BossType[bossnb], PlayerPosX, PlayerPosZ, 1, -1, x310326_g_scriptId, -1, 21)

		if ret > 0 then
			DelItem( sceneId, selfId, 12035000, 1); --删除物品
			local message = "屈出律的部将出现了！"
			Msg2Player(sceneId,selfId,message, 8, 2)
			Msg2Player(sceneId,selfId,message, 8, 3)
			
		end
	
	
	else
		local strText = format("这里无法召出屈出律部将，请前往阿尔金山" )
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, strText)
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId, selfId)
		Msg2Player(sceneId,selfId,strText, 8, 2)
	end	
end

function x310326_IsSkillLikeScript( sceneId, selfId)
	return 0; --这个脚本需要动作支持    
	--返回0，走上面的ProcEventEntry逻辑
	--返回1，走下面的逻辑
end

function x310326_CancelImpacts( sceneId, selfId )
	return 0; --不需要这个接口，但要保留空函数,并且始终返回0。
end

function x310326_OnConditionCheck( sceneId, selfId )
	return 0
end

function x310326_OnDeplete( sceneId, selfId )

	return 0
end

function x310326_OnActivateOnce( sceneId, selfId )
end

function x310326_OnActivateEachTick( sceneId, selfId)
	return 1; --不是引导性脚本, 只保留空函数.
end

function x310326_OnDie(sceneId, selfId, killerId)--怪死亡添加日志
	
	GamePlayScriptLog(sceneId, killerId, 551)
				
end

