--ʹ�ô���װˮ�Ľű�
x413313_g_scriptId = 413313 
x413313_g_Impact1 = 3001 --Ч��ID�������Ӻ���

function x413313_ProcEventEntry( sceneId, selfId, BagIndex )
			CallScriptFunction( MISSION_SCRIPT, "PositionUseItem", sceneId, selfId, BagIndex, x413313_g_Impact1 )
		if GetItemCount(sceneId,selfId,13060023) == 0 then
		BeginAddItem(sceneId)                                                    
		AddItem( sceneId,13060024, 1 )   
		EndAddItem(sceneId,selfId)
		AddItemListToPlayer(sceneId,selfId) 
		end
	

end

function x413313_IsSkillLikeScript( sceneId, selfId)
	return 0; --����ű���Ҫ����֧��    
	--����0���������ProcEventEntry�߼�
	--����1����������߼�
end

function x413313_CancelImpacts( sceneId, selfId )
	return 0; --����Ҫ����ӿڣ���Ҫ�����պ���,����ʼ�շ���0��
end

function x413313_OnConditionCheck( sceneId, selfId )
	return 0
end

function x413313_OnDeplete( sceneId, selfId )

	return 0
end

function x413313_OnActivateOnce( sceneId, selfId )
end

function x413313_OnActivateEachTick( sceneId, selfId)
	return 1; --���������Խű�, ֻ�����պ���.
end
