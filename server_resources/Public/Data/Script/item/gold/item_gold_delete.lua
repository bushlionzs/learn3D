
-----------------------------------------------------------------------
x405500_g_scriptId = 405500 
function x405500_ProcEventEntry( sceneId, selfId, BagIndex )
	local money = GetMoney(sceneId, selfId, 2)
	if CostMoney(sceneId, selfId, 2, money, 307) == 1 then
		DelItemByIndexInBag(sceneId, selfId, BagIndex, 1, 107)
		local strText = "��ʹ���˵���������ֽ�"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, strText)
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId, selfId)
		Msg2Player(sceneId,selfId,strText, 8, 2)
	end
end

function x405500_IsSkillLikeScript( sceneId, selfId)
	return 0; --����ű���Ҫ����֧��    
	--����0���������ProcEventEntry�߼�
	--����1����������߼�
end

function x405500_CancelImpacts( sceneId, selfId )
	return 0; --����Ҫ����ӿڣ���Ҫ�����պ���,����ʼ�շ���0��
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
	return 1; --���������Խű�, ֻ�����պ���.
end

