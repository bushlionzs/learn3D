x310326_g_scriptId = 310326 


x310326_g_DestSceneName = "������ɽ"
x310326_g_DestSceneId = {8}
x310326_g_BossType = {17007,17008,17009,17010,17011,17012,17013}

function x310326_ProcEventEntry( sceneId, selfId, BagIndex )
	local PlayerPosX,PlayerPosZ = GetWorldPos( sceneId, selfId )

	--����
	if sceneId == 8 then
	local bossnb = random(1,7)
	local ret = CreateMonster( sceneId, x310326_g_BossType[bossnb], PlayerPosX, PlayerPosZ, 1, -1, x310326_g_scriptId, -1, 21)

		if ret > 0 then
			DelItem( sceneId, selfId, 12035000, 1); --ɾ����Ʒ
			local message = "�����ɵĲ��������ˣ�"
			Msg2Player(sceneId,selfId,message, 8, 2)
			Msg2Player(sceneId,selfId,message, 8, 3)
			
		end
	
	
	else
		local strText = format("�����޷��ٳ������ɲ�������ǰ��������ɽ" )
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, strText)
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId, selfId)
		Msg2Player(sceneId,selfId,strText, 8, 2)
	end	
end

function x310326_IsSkillLikeScript( sceneId, selfId)
	return 0; --����ű���Ҫ����֧��    
	--����0���������ProcEventEntry�߼�
	--����1����������߼�
end

function x310326_CancelImpacts( sceneId, selfId )
	return 0; --����Ҫ����ӿڣ���Ҫ�����պ���,����ʼ�շ���0��
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
	return 1; --���������Խű�, ֻ�����պ���.
end

function x310326_OnDie(sceneId, selfId, killerId)--�����������־
	
	GamePlayScriptLog(sceneId, killerId, 551)
				
end

