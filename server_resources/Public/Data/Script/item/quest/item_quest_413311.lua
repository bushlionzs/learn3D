x413311_g_scriptId = 413311 
x413311_g_Impact1 = 3001 --Ч��ID�������Ӻ���

function x413311_ProcEventEntry( sceneId, selfId, BagIndex )
--local bCplay =  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem", sceneId, selfId, BagIndex, -1 )
 --if bCplay == 1 then
			CallScriptFunction( MISSION_SCRIPT, "PositionUseItem", sceneId, selfId, BagIndex,x413311_g_Impact1  )
		if GetItemCount(sceneId,selfId,13040030) == 0 then
		NewWorld(sceneId,selfId,2,213,137,413311)
		CallScriptFunction( UTILITY_SCRIPT, "PlayEffect", sceneId, selfId, 15 )
    CallScriptFunction( UTILITY_SCRIPT, "PlayEffect", sceneId, selfId, 16 )
    CallScriptFunction( UTILITY_SCRIPT, "PlayEffect", sceneId, selfId, 17 )
		end
	

end

function x413311_IsSkillLikeScript( sceneId, selfId)
	return 0; --����ű���Ҫ����֧��    
	--����0���������ProcEventEntry�߼�
	--����1����������߼�
end

function x413311_CancelImpacts( sceneId, selfId )
	return 0; --����Ҫ����ӿڣ���Ҫ�����պ���,����ʼ�շ���0��
end

function x413311_OnConditionCheck( sceneId, selfId )
	return 0
end

function x413311_OnDeplete( sceneId, selfId )

	return 0
end

function x413311_OnActivateOnce( sceneId, selfId )
end

function x413311_OnActivateEachTick( sceneId, selfId)
	return 1; --���������Խű�, ֻ�����պ���.
end
