





x400203_g_scriptId = 400203 
x400203_g_Impact1 = 3001 --Ч��ID�������Ӻ���

function x400203_ProcEventEntry( sceneId, selfId, BagIndex )
			CallScriptFunction( MISSION_SCRIPT, "PositionUseItem", sceneId, selfId, BagIndex, x400203_g_Impact1 )
		if GetItemCount(sceneId,selfId,13020301) == 0 then
		BeginAddItem(sceneId)                                                    
		AddItem( sceneId,13020302, 1 )   
		EndAddItem(sceneId,selfId)
		AddItemListToPlayer(sceneId,selfId) 
		end
	

end

function x400203_IsSkillLikeScript( sceneId, selfId)
	return 0; --����ű���Ҫ����֧��    
	--����0���������ProcEventEntry�߼�
	--����1����������߼�
end

function x400203_CancelImpacts( sceneId, selfId )
	return 0; --����Ҫ����ӿڣ���Ҫ�����պ���,����ʼ�շ���0��
end

function x400203_OnConditionCheck( sceneId, selfId )
	return 0
end

function x400203_OnDeplete( sceneId, selfId )

	return 0
end

function x400203_OnActivateOnce( sceneId, selfId )
end

function x400203_OnActivateEachTick( sceneId, selfId)
	return 1; --���������Խű�, ֻ�����պ���.
end
