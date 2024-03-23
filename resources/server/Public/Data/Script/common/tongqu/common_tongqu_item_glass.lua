x300322_g_scriptId = 300322 

function x300322_ProcEventEntry( sceneId, selfId, BagIndex )

	local lastTime = GetPlayerRuntimeData( sceneId, selfId, RD_TONGQU_CD)
	local curTime = GetCurrentTime()
	local message;

	if curTime - lastTime < 10 then
		message = "�����۾�ÿ10����ֻ��ʹ��һ��"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, message)
		DispatchQuestTips(sceneId, selfId)
		EndQuestEvent(sceneId)
		Msg2Player(sceneId,selfId,message, 8, 2)
		return
	end
	
	SetPlayerRuntimeData( sceneId, selfId, RD_TONGQU_CD, curTime)

	SendSpecificImpactToUnit(sceneId, selfId, selfId, selfId, 7515, 0)
	message = "�����ڿ��Կ����������ߵ������ˣ���Ͽ���в�׽�ɣ�"
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
	return 0; --����ű���Ҫ����֧��    
	--����0���������ProcEventEntry�߼�
	--����1����������߼�
end

function x300322_CancelImpacts( sceneId, selfId )
	return 0; --����Ҫ����ӿڣ���Ҫ�����պ���,����ʼ�շ���0��
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
	return 1; --���������Խű�, ֻ�����պ���.
end