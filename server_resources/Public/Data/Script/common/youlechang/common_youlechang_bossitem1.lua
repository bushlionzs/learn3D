x310343_g_scriptId = 310343 


x310343_g_DestSceneName = "�������"
x310343_g_DestSceneId = {11}
x310343_g_BossType = {17014,17015,17016,17017,17018,17019,17020}

function x310343_ProcEventEntry( sceneId, selfId, BagIndex )
	local PlayerPosX,PlayerPosZ = GetWorldPos( sceneId, selfId )

	--����
	if sceneId == 11 then
	local bossnb = random(1,7)
	local ret = CreateMonster( sceneId, x310343_g_BossType[bossnb], PlayerPosX, PlayerPosZ, 1, -1, x310343_g_scriptId, -1, 21)

		if ret > 0 then
			DelItem( sceneId, selfId, 12035001, 1); --ɾ����Ʒ
			local message = "�������Ĳ��������ˣ�"
			Msg2Player(sceneId,selfId,message, 8, 2)
			Msg2Player(sceneId,selfId,message, 8, 3)
			
		end
	
	
	else
		local strText = format("�����޷��ٳ���������������ǰ���������" )
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, strText)
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId, selfId)
		Msg2Player(sceneId,selfId,strText, 8, 2)
	end	
end

function x310343_IsSkillLikeScript( sceneId, selfId)
	return 0; --����ű���Ҫ����֧��    
	--����0���������ProcEventEntry�߼�
	--����1����������߼�
end

function x310343_CancelImpacts( sceneId, selfId )
	return 0; --����Ҫ����ӿڣ���Ҫ�����պ���,����ʼ�շ���0��
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
	return 1; --���������Խű�, ֻ�����պ���.
end

function x310343_OnDie(sceneId, selfId, killerId)--�����������־
	
	GamePlayScriptLog(sceneId, killerId, 551)
				
end

