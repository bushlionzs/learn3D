x400006_g_scriptId  = 400006--���ڵ��ű�
x400006_g_Impact1   = 1241--Ч��ID�������Ӻ���
x400006_g_Impact2   = -1 --����


--**********************************
--�¼��������
--**********************************
function x400006_ProcEventEntry( sceneId, selfId, bagIndex )
			BeginQuestEvent(sceneId)
	  	AddQuestText(sceneId,"����뵽��60��������֮����ͻ�������ִ������")
	  	EndQuestEvent()
			DispatchQuestInfoNM(sceneId, selfId, selfId, 270000, 3533);
-- ����Ҫ����ӿڣ���Ҫ�����պ���
end


function x400006_IsSkillLikeScript( sceneId, selfId)
	return 0; --����ű���Ҫ����֧��    
	--����0���������ProcEventEntry�߼�
	--����1����������߼�
end

function x400006_CancelImpacts( sceneId, selfId )
	return 0; --����Ҫ����ӿڣ���Ҫ�����պ���,����ʼ�շ���0��
end

function x400006_OnConditionCheck( sceneId, selfId )
	return 0
end

function x400006_OnDeplete( sceneId, selfId )

	return 1
end

function x400006_OnActivateOnce( sceneId, selfId )
end

function x400006_OnActivateEachTick( sceneId, selfId)
	return 1; --���������Խű�, ֻ�����պ���.
end
