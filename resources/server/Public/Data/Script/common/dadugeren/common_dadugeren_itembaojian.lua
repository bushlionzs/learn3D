
x300574_g_scriptId = 300574

x300574_g_MissionScriptId 		= 	300573 

function x300574_ProcEventEntry( sceneId, selfId, bagIndex )
		local bCplay =  CallScriptFunction( x300574_g_MissionScriptId, "PositionUseItem", sceneId, selfId, bagIndex )
    
    
end

function x300574_IsSkillLikeScript( sceneId, selfId)
	return 0; --����ű���Ҫ����֧��    
	--����0���������ProcEventEntry�߼�
	--����1����������߼�

 end

function x300574_CancelImpacts( sceneId, selfId )
	return 0; --����Ҫ����ӿڣ���Ҫ�����պ���,����ʼ�շ���0��
 
end

function x300574_OnConditionCheck( sceneId, selfId )
	return 0
end

function x300574_OnDeplete( sceneId, selfId )
	return 0
end

function x300574_OnActivateOnce( sceneId, selfId )
end

function x300574_OnActivateEachTick( sceneId, selfId)
	return 1; --���������Խű�, ֻ�����պ���.
end
