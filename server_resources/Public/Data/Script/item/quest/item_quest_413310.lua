





x413310_g_scriptId = 413310 
x413310_g_Impact1 = 3001 --Ч��ID�������Ӻ���

function x413310_ProcEventEntry( sceneId, selfId, BagIndex )
			CallScriptFunction( MISSION_SCRIPT, "PositionUseItem", sceneId, selfId, BagIndex, x413310_g_Impact1 )
		if GetItemCount(sceneId,selfId,13060010) == 0 then
		BeginAddItem(sceneId)                                                    
		AddItem( sceneId,13060012, 1 )   
		EndAddItem(sceneId,selfId)
		AddItemListToPlayer(sceneId,selfId) 
		end
	

end

function x413310_IsSkillLikeScript( sceneId, selfId)
	return 0; --����ű���Ҫ����֧��    
	--����0���������ProcEventEntry�߼�
	--����1����������߼�
end

function x413310_CancelImpacts( sceneId, selfId )
	return 0; --����Ҫ����ӿڣ���Ҫ�����պ���,����ʼ�շ���0��
end

function x413310_OnConditionCheck( sceneId, selfId )
	return 0
end

function x413310_OnDeplete( sceneId, selfId )

	return 0
end

function x413310_OnActivateOnce( sceneId, selfId )
end

function x413310_OnActivateEachTick( sceneId, selfId)
	return 1; --���������Խű�, ֻ�����պ���.
end
