





x400211_g_scriptId = 400211 
x400211_g_Impact1 = 7528 --Ч��ID�������Ӻ���

function x400211_ProcEventEntry( sceneId, selfId, BagIndex )
			local bCplay =  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem", sceneId, selfId, BagIndex, -1 )
    
    if bCplay == 1 then
    		if GetItemCount(sceneId,selfId,13030086) == 0 then
					BeginAddItem(sceneId)                                                    
					AddItem( sceneId,13030087, 1 )   
					EndAddItem(sceneId,selfId)
					AddItemListToPlayer(sceneId,selfId) 
					CallScriptFunction( UTILITY_SCRIPT, "PlayEffect", sceneId, selfId, 1 )
					CallScriptFunction( UTILITY_SCRIPT, "PlayEffect", sceneId, selfId, 2 )
					CallScriptFunction( UTILITY_SCRIPT, "PlayEffect", sceneId, selfId, 3 )
				end
    end

    return bCplay
		
	

end

function x400211_IsSkillLikeScript( sceneId, selfId)
	return 0; --����ű���Ҫ����֧��    
	--����0���������ProcEventEntry�߼�
	--����1����������߼�
end

function x400211_CancelImpacts( sceneId, selfId )
	return 0; --����Ҫ����ӿڣ���Ҫ�����պ���,����ʼ�շ���0��
end

function x400211_OnConditionCheck( sceneId, selfId )
	return 0
end

function x400211_OnDeplete( sceneId, selfId )

	return 0
end

function x400211_OnActivateOnce( sceneId, selfId )
end

function x400211_OnActivateEachTick( sceneId, selfId)
	return 1; --���������Խű�, ֻ�����պ���.
end
