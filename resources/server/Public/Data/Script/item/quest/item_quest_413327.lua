





x413327_g_scriptId = 413327 
x413327_g_Impact1 = 3001 --Ч��ID�������Ӻ���

function x413327_ProcEventEntry( sceneId, selfId, BagIndex )
			CallScriptFunction( MISSION_SCRIPT, "PositionUseItem", sceneId, selfId, BagIndex, x413327_g_Impact1 )
		if GetItemCount(sceneId,selfId,13810252) == 0 then
		BeginAddItem(sceneId)                                                    
		AddItem( sceneId,13810253, 1 )   
		EndAddItem(sceneId,selfId)
		AddItemListToPlayer(sceneId,selfId) 
		end
	

end

function x413327_IsSkillLikeScript( sceneId, selfId)
	return 0; --����ű���Ҫ����֧��    
	--����0���������ProcEventEntry�߼�
	--����1����������߼�
end

function x413327_CancelImpacts( sceneId, selfId )
	return 0; --����Ҫ����ӿڣ���Ҫ�����պ���,����ʼ�շ���0��
end

function x413327_OnConditionCheck( sceneId, selfId )
	return 0
end

function x413327_OnDeplete( sceneId, selfId )

	return 0
end

function x413327_OnActivateOnce( sceneId, selfId )
end

function x413327_OnActivateEachTick( sceneId, selfId)
	return 1; --���������Խű�, ֻ�����պ���.
end
