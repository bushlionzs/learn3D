
------------------------------------------------------------------------------------------
--һ����Ʒ��Ĭ�Ͻű�

--�ű���

x203400_g_scriptId 		= 203400 
x203400_g_BonusItem     = {{item = 10201001,n=1},{item = 10261001,n=1}}


function x203400_ProcEventEntry( sceneId, selfId, bagIndex )
local bCplay =  DelItem(sceneId, selfId,13010122,1)
    if bCplay == 1 then
      	BeginAddItem(sceneId)
		AddBindItem( sceneId, 10201001, 1 )

		AddBindItem( sceneId, 10261001, 1 )

	local ret = EndAddItem(sceneId,selfId)

	if ret>0 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"������±�װ��������˼Ҵ������ͼҴ�ͷ����")
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
			AddItemListToPlayer(sceneId,selfId)
	else
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"�����������޷��õ���Ʒ��")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
	end
    end
        return bCplay
end

function x203400_IsSkillLikeScript( sceneId, selfId)
	return 0; --����ű���Ҫ����֧��    
	--����0���������ProcEventEntry�߼�
	--����1����������߼�

end

function x203400_CancelImpacts( sceneId, selfId )
	return 0; --����Ҫ����ӿڣ���Ҫ�����պ���,����ʼ�շ���0��

end

function x203400_OnConditionCheck( sceneId, selfId )
	return 0
end

function x203400_OnDeplete( sceneId, selfId )
	return 0
end

function x203400_OnActivateOnce( sceneId, selfId )
end

function x203400_OnActivateEachTick( sceneId, selfId)
	return 1; --���������Խű�, ֻ�����պ���.
end
