





x400207_g_scriptId = 400207 
x400207_g_Impact1 = 3001 --Ч��ID�������Ӻ���

function x400207_ProcEventEntry( sceneId, selfId, BagIndex )
			CallScriptFunction( MISSION_SCRIPT, "PositionUseItem", sceneId, selfId, BagIndex, x400207_g_Impact1 )
			if GetItemCount(sceneId,selfId,13020318) == 0 then
					BeginAddItem(sceneId)                                                    
					AddItem( sceneId,13020319, 1 )   
					EndAddItem(sceneId,selfId)
					AddItemListToPlayer(sceneId,selfId) 
		end

end

function x400207_IsSkillLikeScript( sceneId, selfId)
	return 0; --����ű���Ҫ����֧��    
	--����0���������ProcEventEntry�߼�
	--����1����������߼�
end

function x400207_CancelImpacts( sceneId, selfId )
	return 0; --����Ҫ����ӿڣ���Ҫ�����պ���,����ʼ�շ���0��
end

function x400207_OnConditionCheck( sceneId, selfId )
	return 0
end

function x400207_OnDeplete( sceneId, selfId )

	return 0
end

function x400207_OnActivateOnce( sceneId, selfId )
end

function x400207_OnActivateEachTick( sceneId, selfId)
	return 1; --���������Խű�, ֻ�����պ���.
end
