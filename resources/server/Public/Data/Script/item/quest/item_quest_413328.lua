


x413328_g_scriptId = 413328 
x413328_g_Impact1 = 3001 --Ч��ID�������Ӻ���

function x413328_ProcEventEntry( sceneId, selfId, BagIndex )
		CallScriptFunction( 888894,"OpenWorldDirectory",sceneId,selfId )
		CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 80,1 )
--		local ItemCount = GetItemCount(sceneId,selfId,12030214 )  
--		if ItemCount > 0 then                                               
--			DelItem( sceneId, selfId, 12030214 , 1 )   
--		end
		

end

function x413328_IsSkillLikeScript( sceneId, selfId)
	return 0; --����ű���Ҫ����֧��    
	--����0���������ProcEventEntry�߼�
	--����1����������߼�
end

function x413328_CancelImpacts( sceneId, selfId )
	return 0; --����Ҫ����ӿڣ���Ҫ�����պ���,����ʼ�շ���0��
end

function x413328_OnConditionCheck( sceneId, selfId )
	return 0
end

function x413328_OnDeplete( sceneId, selfId )

	return 0
end

function x413328_OnActivateOnce( sceneId, selfId )
end

function x413328_OnActivateEachTick( sceneId, selfId)
	return 1; --���������Խű�, ֻ�����պ���.
end
