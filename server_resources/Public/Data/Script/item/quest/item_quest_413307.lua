





x413307_g_scriptId = 413307 
x413307_g_Impact1 = 3001 --Ч��ID�������Ӻ���

function x413307_ProcEventEntry( sceneId, selfId, BagIndex )
			CallScriptFunction( MISSION_SCRIPT, "PositionUseItem", sceneId, selfId, BagIndex, x413307_g_Impact1 )
		if GetItemCount(sceneId,selfId,13060008) == 0 then
		BeginAddItem(sceneId)                                                    
		AddItem( sceneId,13060016, 1 )   
		EndAddItem(sceneId,selfId)
		AddItemListToPlayer(sceneId,selfId) 
		end
	

end

function x413307_IsSkillLikeScript( sceneId, selfId)
	return 0; --����ű���Ҫ����֧��    
	--����0���������ProcEventEntry�߼�
	--����1����������߼�
end

function x413307_CancelImpacts( sceneId, selfId )
	return 0; --����Ҫ����ӿڣ���Ҫ�����պ���,����ʼ�շ���0��
end

function x413307_OnConditionCheck( sceneId, selfId )
	return 0
end

function x413307_OnDeplete( sceneId, selfId )

	return 0
end

function x413307_OnActivateOnce( sceneId, selfId )
end

function x413307_OnActivateEachTick( sceneId, selfId)
	return 1; --���������Խű�, ֻ�����պ���.
end
