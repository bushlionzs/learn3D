x413304_g_scriptId = 413304 
x413304_g_Impact1 = 3001 --Ч��ID�������Ӻ���

function x413304_ProcEventEntry( sceneId, selfId, BagIndex )
--local bCplay =  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem", sceneId, selfId, BagIndex, -1 )
 --if bCplay == 1 then
			CallScriptFunction( MISSION_SCRIPT, "PositionUseItem", sceneId, selfId, BagIndex, x413304_g_Impact1 )
		if GetItemCount(sceneId,selfId,13030113) == 0 then
		CallScriptFunction( UTILITY_SCRIPT, "PlayEffect", sceneId, selfId, 12 )
    CallScriptFunction( UTILITY_SCRIPT, "PlayEffect", sceneId, selfId, 13 )
		SetPos(sceneId,selfId,33,73)
		end
	

end

function x413304_IsSkillLikeScript( sceneId, selfId)
	return 0; --����ű���Ҫ����֧��    
	--����0���������ProcEventEntry�߼�
	--����1����������߼�
end

function x413304_CancelImpacts( sceneId, selfId )
	return 0; --����Ҫ����ӿڣ���Ҫ�����պ���,����ʼ�շ���0��
end

function x413304_OnConditionCheck( sceneId, selfId )
	return 0
end

function x413304_OnDeplete( sceneId, selfId )

	return 0
end

function x413304_OnActivateOnce( sceneId, selfId )
end

function x413304_OnActivateEachTick( sceneId, selfId)
	return 1; --���������Խű�, ֻ�����պ���.
end
