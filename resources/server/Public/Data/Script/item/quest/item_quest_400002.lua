x400002_g_scriptId  = 400002--���ڵ��ű�
x400002_g_Impact1   = 7520--Ч��ID�������Ӻ���
x400002_g_Impact2   = -1 --����
--**********************************
--�¼��������
--**********************************
function x400002_ProcEventEntry( sceneId, selfId, bagIndex )
			CallScriptFunction( 200501, "useitem", sceneId, selfId)
end


function x400002_IsSkillLikeScript( sceneId, selfId)
 
	return 0; --����ű���Ҫ����֧��    
	--����0���������ProcEventEntry�߼�
	--����1����������߼�
end

function x400002_CancelImpacts( sceneId, selfId )
	return 0; --����Ҫ����ӿڣ���Ҫ�����պ���,����ʼ�շ���0��
end

function x400002_OnConditionCheck( sceneId, selfId )
	return 0
end

function x400002_OnDeplete( sceneId, selfId )

	return 1
end

function x400002_OnActivateOnce( sceneId, selfId )
end

function x400002_OnActivateEachTick( sceneId, selfId)
	return 1; --���������Խű�, ֻ�����պ���.
end
