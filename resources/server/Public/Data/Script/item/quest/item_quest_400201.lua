
x400201_g_scriptId = 400201
x400201_g_Impact1 = 7528 --Ч��ID�������Ӻ���

function x400201_ProcEventEntry( sceneId, selfId, bagIndex )
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"մ��Ѫ���ĺ�������")
						AddQuestText(sceneId,"\n\t��л��ļ��룬�����ǵļƻ��ɹ�ʱ������������µ��쵼�ߣ���������Ҳ�Ѿ�������ʼ�ж��������������ʯ��ʹ���ǵ���ʦ���ӵ����������������Щ��ɫ���˶���һȺΨ����ͼ�������ˣ����ǵ���������������Щʧ���˵İ����ˡ�\n \n\t���ܵľۼ����Ѿ����߹�ģ�����žٱ���ף�������Ѿ���Զ�ˡ�\n \n \n\t\t\t\t��³��")
						EndQuestEvent()
						DispatchQuestEventList(sceneId, selfId, selfId, 400201, 2700);
		
end

function x400201_IsSkillLikeScript( sceneId, selfId)
	return 0; --����ű���Ҫ����֧��    
	--����0���������ProcEventEntry�߼�
	--����1����������߼�

end

function x400201_CancelImpacts( sceneId, selfId )
	return 0; --����Ҫ����ӿڣ���Ҫ�����պ���,����ʼ�շ���0��
end

function x400201_OnConditionCheck( sceneId, selfId )
	return 0
end

function x400201_OnDeplete( sceneId, selfId )
	return 1
end

function x400201_OnActivateOnce( sceneId, selfId )
end

function x400201_OnActivateEachTick( sceneId, selfId)
	return 1; --���������Խű�, ֻ�����պ���.
end
