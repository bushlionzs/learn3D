
x400202_g_scriptId = 400202
x400202_g_Impact1 = 7528 --Ч��ID�������Ӻ���

function x400202_ProcEventEntry( sceneId, selfId, bagIndex )
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"��ʪ�ĺ�������")
						AddQuestText(sceneId,"\n\t��������ľ�����£����۴���������������������ȡ����������������۵����������������ʦ���ӵ������кܴ����������ϣ������˳���ذ������˻������ң������Ǹ���ԣ����ۣ����еĶ����������ǵġ�\n \n\t�����Ǵ���������Ҫ�Ķ�����һ�������и����ı��꣬���������ܲ����ƽ������Ļ���Ŀǰ��û�б���֤������ܹ��ɹ����������������Ǽ�����֮�⣬���еı��ﶼ����ġ�\n \n\t���������һ֧���ӣ��ڲ�˹����Ҳȡ���˲����ս���������ڴ��ٱ�ͬ������ӡ�\n \n \n\t\t\t\t����")
						EndQuestEvent()
						DispatchQuestEventList(sceneId, selfId, selfId, 400202, 2700);
		
end

function x400202_IsSkillLikeScript( sceneId, selfId)
	return 0; --����ű���Ҫ����֧��    
	--����0���������ProcEventEntry�߼�
	--����1����������߼�

end

function x400202_CancelImpacts( sceneId, selfId )
	return 0; --����Ҫ����ӿڣ���Ҫ�����պ���,����ʼ�շ���0��
end

function x400202_OnConditionCheck( sceneId, selfId )
	return 0
end

function x400202_OnDeplete( sceneId, selfId )
	return 1
end

function x400202_OnActivateOnce( sceneId, selfId )
end

function x400202_OnActivateEachTick( sceneId, selfId)
	return 1; --���������Խű�, ֻ�����պ���.
end
