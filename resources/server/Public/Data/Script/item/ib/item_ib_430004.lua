--С���ȿ۳�����

--����ֵ˵��������۳�ʧ�� 0 ������ 1
------------------------------------------------------------------------------------------
--�¼��������
--**********************************
function x430004_OnChatDeplete( sceneId, selfId, bChatType, bagIndex )
	local iMultTimes = IsBagItemMultTimes( sceneId, selfId, bagIndex )
	if iMultTimes <= 0 then
		return 0;
	end

	local itimes = GetBagItemMultTimes( sceneId, selfId, bagIndex );
	itimes = itimes - 1;
	if itimes <= 0 then
		--ɾ������
		EraseItem( sceneId, selfId, bagIndex );
	else
		--����
		SetBagItemMultTimes( sceneId, selfId, bagIndex, itimes );
	end
	return 1;
end
