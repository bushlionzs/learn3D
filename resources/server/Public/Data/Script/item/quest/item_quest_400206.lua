x400206_g_scriptId  = 400206--���ڵ��ű�
x400206_g_Impact1   = 7520--Ч��ID�������Ӻ���
x400206_g_Impact2   = -1 --����
--**********************************
--�¼��������
--**********************************
function x400206_ProcEventEntry( sceneId, selfId, bagIndex )
			CallScriptFunction( 270010, "useitem", sceneId, selfId)
end


function x400206_IsSkillLikeScript( sceneId, selfId)
 
	return 0; --����ű���Ҫ����֧��    
	--����0���������ProcEventEntry�߼�
	--����1����������߼�
end

function x400206_CancelImpacts( sceneId, selfId )
	return 0; --����Ҫ����ӿڣ���Ҫ�����պ���,����ʼ�շ���0��
end

function x400206_OnConditionCheck( sceneId, selfId )
	return 0
end

function x400206_OnDeplete( sceneId, selfId )

	return 1
end

function x400206_OnActivateOnce( sceneId, selfId )
end

function x400206_OnActivateEachTick( sceneId, selfId)
	return 1; --���������Խű�, ֻ�����պ���.
end
