x413317_g_scriptId  = 413317--���ڵ��ű�
x413317_g_Impact1   = 7520--Ч��ID�������Ӻ���
x413317_g_Impact2   = -1 --����
--**********************************
--�¼��������
--**********************************
function x413317_ProcEventEntry( sceneId, selfId, bagIndex )
			CallScriptFunction( 203315, "useitem", sceneId, selfId)
end


function x413317_IsSkillLikeScript( sceneId, selfId)
 
	return 0; --����ű���Ҫ����֧��    
	--����0���������ProcEventEntry�߼�
	--����1����������߼�
end

function x413317_CancelImpacts( sceneId, selfId )
	return 0; --����Ҫ����ӿڣ���Ҫ�����պ���,����ʼ�շ���0��
end

function x413317_OnConditionCheck( sceneId, selfId )
	return 0
end

function x413317_OnDeplete( sceneId, selfId )

	return 1
end

function x413317_OnActivateOnce( sceneId, selfId )
end

function x413317_OnActivateEachTick( sceneId, selfId)
	return 1; --���������Խű�, ֻ�����պ���.
end
