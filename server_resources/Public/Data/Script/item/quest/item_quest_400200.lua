
x400200_g_scriptId = 400200
x400200_g_Impact1 = 7528 --Ч��ID�������Ӻ���

function x400200_ProcEventEntry( sceneId, selfId, bagIndex )
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"����ĺ�������")
						AddQuestText(sceneId,"\n\t�ƻ��Ѿ���ʼʵʩ���������ڽ������ܵĻ��أ���������������ú����ٻ����ϵ��׵��������ж�����Ĳ�������������Ҳ�Ѿ���ʼ�ж���������Զ�����ǹ¾���ս���³�֮�����ǻ�����ŵ�ԡ�\n \n\tҤ�����زصľ�ʯ��һ��������������ܹ�ʹҰ�����˲���ͬ�������������ǳ���������׷�����������������Ƕ��ֳ�ŵ�ĵ�һ���ɡ�\n \n \n\t\t\t\t��³��")
						EndQuestEvent()
						DispatchQuestEventList(sceneId, selfId, selfId, 400200, 2700);
		
end

function x400200_IsSkillLikeScript( sceneId, selfId)
	return 0; --����ű���Ҫ����֧��    
	--����0���������ProcEventEntry�߼�
	--����1����������߼�

end

function x400200_CancelImpacts( sceneId, selfId )
	return 0; --����Ҫ����ӿڣ���Ҫ�����պ���,����ʼ�շ���0��
end

function x400200_OnConditionCheck( sceneId, selfId )
	return 0
end

function x400200_OnDeplete( sceneId, selfId )
	return 1
end

function x400200_OnActivateOnce( sceneId, selfId )
end

function x400200_OnActivateEachTick( sceneId, selfId)
	return 1; --���������Խű�, ֻ�����պ���.
end
