





x400219_g_scriptId = 400219 
x400219_g_Impact1 = 3001 --Ч��ID�������Ӻ���

function x400219_ProcEventEntry( sceneId, selfId, BagIndex )
			CallScriptFunction( MISSION_SCRIPT, "PositionUseItem", sceneId, selfId, BagIndex, x400219_g_Impact1 )
		if GetItemCount(sceneId,selfId,13810252) == 0 then
		BeginAddItem(sceneId)                                                    
		AddItem( sceneId,13810253, 1 )   
		EndAddItem(sceneId,selfId)
		AddItemListToPlayer(sceneId,selfId) 
		end
	

end

function x400219_IsSkillLikeScript( sceneId, selfId)
	return 0; --����ű���Ҫ����֧��    
	--����0���������ProcEventEntry�߼�
	--����1����������߼�
end

function x400219_CancelImpacts( sceneId, selfId )
	return 0; --����Ҫ����ӿڣ���Ҫ�����պ���,����ʼ�շ���0��
end

function x400219_OnConditionCheck( sceneId, selfId )
	return 0
end

function x400219_OnDeplete( sceneId, selfId )

	return 0
end

function x400219_OnActivateOnce( sceneId, selfId )
end

function x400219_OnActivateEachTick( sceneId, selfId)
	return 1; --���������Խű�, ֻ�����պ���.
end
