--author: jiangchao
--desc	: ר�����õ���,ʹ�ñ�����ϴ�����е�ר�������еĵ���

x404911_g_scriptId  = 404911 
x404911_g_MissionID = 9093

function x404911_ProcEventEntry( sceneId, selfId, BagIndex )
	--�����е�ר�������еĵ���ϴ��
	--�˽ӿ���Ҫshangyu�ṩ�ű��ӿ�
	
	local strText = "#Y��ר���츳��ר��ѵ���������ã�#W\n\tʹ��ר������֮�齫����������ר���츳ר��ѵ���������Ƿ�ȷ��ʹ�ã�"
	BeginQuestEvent(sceneId)
	AddQuestText(sceneId, strText)
	EndQuestEvent(sceneId)
	--DispatchQuestTips(sceneId, selfId)
	--DispatchQuestInfo(sceneId, selfId, selfId, x404911_g_scriptId, x404911_g_MissionID,  0)
	DispatchQuestInfoNM(sceneId, selfId, selfId, x404911_g_scriptId, x404911_g_MissionID,  0)
	--Msg2Player(sceneId,selfId,strText, 8, 2)
	return 
	
	
end

function x404911_IsSkillLikeScript( sceneId, selfId)
	return 0; --����ű���Ҫ����֧��    
	--����0���������ProcEventEntry�߼�
	--����1����������߼�
end

function x404911_CancelImpacts( sceneId, selfId )
	return 0; --����Ҫ����ӿڣ���Ҫ�����պ���,����ʼ�շ���0��
end

function x404911_OnConditionCheck( sceneId, selfId )
	return 0
end

function x404911_OnDeplete( sceneId, selfId )

	return 0
end

function x404911_OnActivateOnce( sceneId, selfId )
end

function x404911_OnActivateEachTick( sceneId, selfId)
	return 1; --���������Խű�, ֻ�����պ���.
end

function x404911_OnDie(sceneId, selfId, killerId)--�����������־
		
end



function x404911_ProcQuestAccept( sceneId, selfId, targetId, MissionId )
	local ret = DelItemByIDInBag( sceneId, selfId, 12030219, 1) --ɾ����Ʒ
	ReallocateInherenceZhuanFangPoint( sceneId, selfId )
	Msg2Player(sceneId,selfId,"ר����������", 8, 2)
end



