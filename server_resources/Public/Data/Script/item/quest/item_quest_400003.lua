





x400003_g_scriptId = 400003 
x400003_g_Impact1 = 3001 --Ч��ID�������Ӻ���

function x400003_ProcEventEntry( sceneId, selfId, BagIndex )
			CallScriptFunction( MISSION_SCRIPT, "PositionUseItem", sceneId, selfId, BagIndex, x400003_g_Impact1 )
		if GetItemCount(sceneId,selfId,13020002) == 0 then
		BeginAddItem(sceneId)                                                    
		AddItem( sceneId,13010038, 1 )   
		EndAddItem(sceneId,selfId)
		AddItemListToPlayer(sceneId,selfId) 
		end
	

end

function x400003_IsSkillLikeScript( sceneId, selfId)
	return 0; --����ű���Ҫ����֧��    
	--����0���������ProcEventEntry�߼�
	--����1����������߼�
end

function x400003_CancelImpacts( sceneId, selfId )
	return 0; --����Ҫ����ӿڣ���Ҫ�����պ���,����ʼ�շ���0��
end

function x400003_OnConditionCheck( sceneId, selfId )
	return 0
end

function x400003_OnDeplete( sceneId, selfId )

	return 0
end

function x400003_OnActivateOnce( sceneId, selfId )
end

function x400003_OnActivateEachTick( sceneId, selfId)
	return 1; --���������Խű�, ֻ�����պ���.
end
