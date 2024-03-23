x310344_g_scriptId = 310344 


x310344_g_DestSceneName = ""
x310344_g_DestSceneId = {17}
x310344_g_BossType = {17021,17022,17023,17024,17025,17026,17027}

function x310344_ProcEventEntry( sceneId, selfId, BagIndex )
	local PlayerPosX,PlayerPosZ = GetWorldPos( sceneId, selfId )

	--����
	if sceneId == 17 then
	local bossnb = random(1,7)
	local ret = CreateMonster( sceneId, x310344_g_BossType[bossnb], PlayerPosX, PlayerPosZ, 1, -1, x310344_g_scriptId, -1, 21)

		if ret > 0 then
			DelItem( sceneId, selfId, 12035002, 1)--ɾ����Ʒ
			local message = "�������׶��Ĳ��������ˣ�"
			Msg2Player(sceneId,selfId,message, 8, 2)
			Msg2Player(sceneId,selfId,message, 8, 3)
			
		end
	
	
	else
		local strText = format("�����޷��ٳ��������׶���������ǰ��Ī˹�ƹ���" )
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, strText)
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId, selfId)
		Msg2Player(sceneId,selfId,strText, 8, 2)
	end	
end

function x310344_IsSkillLikeScript( sceneId, selfId)
	return 0; --����ű���Ҫ����֧��    
	--����0���������ProcEventEntry�߼�
	--����1����������߼�
end

function x310344_CancelImpacts( sceneId, selfId )
	return 0; --����Ҫ����ӿڣ���Ҫ�����պ���,����ʼ�շ���0��
end

function x310344_OnConditionCheck( sceneId, selfId )
	return 0
end

function x310344_OnDeplete( sceneId, selfId )

	return 0
end

function x310344_OnActivateOnce( sceneId, selfId )
end

function x310344_OnActivateEachTick( sceneId, selfId)
	return 1; --���������Խű�, ֻ�����պ���.
end

function x310344_OnDie(sceneId, selfId, killerId)--�����������־
	
	GamePlayScriptLog(sceneId, killerId, 551)
				
end

