--�������������Ч�ű�����ɫ�� 12030333


x418021_g_scriptId = 418021
x418021_g_Impact1 = 7518 --Ч��ID�������Ӻ���
x418021_g_item = 12030333

function x418021_ProcEventEntry( sceneId, selfId, bagIndex )
	
--	if yanhua == 1 then 
--		DelItem( sceneId,selfId,x418021_g_item,1 )
--	end

end

function x418021_IsSkillLikeScript( sceneId, selfId)
	return 1; --����ű���Ҫ����֧��    
	--����0���������ProcEventEntry�߼�
	--����1����������߼�

end

function x418021_CancelImpacts( sceneId, selfId )
	return 0; --����Ҫ����ӿڣ���Ҫ�����պ���,����ʼ�շ���0��

end

function x418021_OnConditionCheck( sceneId, selfId )
	--У��ʹ�õ���Ʒ
	
	if(1~=VerifyUsedItem(sceneId, selfId)) then
		return 0
	end
	return 1; --����Ҫ�κ�����������ʼ�շ���1��
end

function x418021_OnDeplete( sceneId, selfId )
	return 1
end

function x418021_OnActivateOnce( sceneId, selfId )

	if(DepletingUsedItem(sceneId, selfId)) == 1 then
		local yanhua=   SendSpecificImpactToUnit(sceneId, selfId, selfId, selfId, x418021_g_Impact1, 0);
	else
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"ʹ����Ʒ�쳣��")
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
	end

end

function x418021_OnActivateEachTick( sceneId, selfId)
	return 1; --���������Խű�, ֻ�����պ���.
end
