





x400212_g_scriptId = 400212 
x400212_g_Impact1 = 3001 --Ч��ID�������Ӻ���

function x400212_ProcEventEntry( sceneId, selfId, BagIndex )
			CallScriptFunction( MISSION_SCRIPT, "PositionUseItem", sceneId, selfId, BagIndex, x400212_g_Impact1 )
			if GetItemCount(sceneId,selfId,13020206) == 0 then
					BeginAddItem(sceneId)                                                    
					AddItem( sceneId,13020214, 1 )   
					EndAddItem(sceneId,selfId)
					AddItemListToPlayer(sceneId,selfId) 
		end

end

function x400212_IsSkillLikeScript( sceneId, selfId)
	return 0; --����ű���Ҫ����֧��    
	--����0���������ProcEventEntry�߼�
	--����1����������߼�
end

function x400212_CancelImpacts( sceneId, selfId )
	return 0; --����Ҫ����ӿڣ���Ҫ�����պ���,����ʼ�շ���0��
end

function x400212_OnConditionCheck( sceneId, selfId )
	return 0
end

function x400212_OnDeplete( sceneId, selfId )

	return 0
end

function x400212_OnActivateOnce( sceneId, selfId )
end

function x400212_OnActivateEachTick( sceneId, selfId)
	return 1; --���������Խű�, ֻ�����պ���.
end
