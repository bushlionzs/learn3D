x300323_g_scriptId = 300323 

function x300323_ProcEventEntry( sceneId, selfId, BagIndex )

	if IsHaveSpecificImpact(sceneId, selfId, 7517) > 0 or IsHaveSpecificImpact(sceneId, selfId, 7516) > 0 then
		local posX=289
		local posZ =299
		SetPos(sceneId, selfId, posX, posZ)
	else
	end
end

function x300323_IsSkillLikeScript( sceneId, selfId)
	return 0; --����ű���Ҫ����֧��    
	--����0���������ProcEventEntry�߼�
	--����1����������߼�
end

function x300323_CancelImpacts( sceneId, selfId )
	return 0; --����Ҫ����ӿڣ���Ҫ�����պ���,����ʼ�շ���0��
end

function x300323_OnConditionCheck( sceneId, selfId )
	return 0
end

function x300323_OnDeplete( sceneId, selfId )

	return 0
end

function x300323_OnActivateOnce( sceneId, selfId )
end

function x300323_OnActivateEachTick( sceneId, selfId)
	return 1; --���������Խű�, ֻ�����պ���.
end