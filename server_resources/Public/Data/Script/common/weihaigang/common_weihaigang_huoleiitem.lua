
x300579_g_scriptId = 300579

x300579_g_MissionScriptId 		= 	300576 

function x300579_ProcEventEntry( sceneId, selfId, bagIndex )
		local bCplay =  CallScriptFunction( x300579_g_MissionScriptId, "PositionUseItem", sceneId, selfId, bagIndex )
    
    
end

function x300579_IsSkillLikeScript( sceneId, selfId)
	return 0; --����ű���Ҫ����֧��    
	--����0���������ProcEventEntry�߼�
	--����1����������߼�

 end

function x300579_CancelImpacts( sceneId, selfId )
	return 0; --����Ҫ����ӿڣ���Ҫ�����պ���,����ʼ�շ���0��
 
end

function x300579_OnConditionCheck( sceneId, selfId )
	return 0
end

function x300579_OnDeplete( sceneId, selfId )
	return 0
end

function x300579_OnActivateOnce( sceneId, selfId )
end

function x300579_OnActivateEachTick( sceneId, selfId)
	return 1; --���������Խű�, ֻ�����պ���.
end
