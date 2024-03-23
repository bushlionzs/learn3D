--����ܳ��ʰ�		
------------------------------------------------------------------------------------------
--һ����Ʒ��Ĭ�Ͻű�

--�ű���

x418129_g_scriptId = 418129
x418129_g_ItemList = {}
x418129_g_LevelMin = 1	
--��Ҫ�ĵȼ�


--**********************************
--�¼��������
--**********************************
function x418129_ProcEventEntry( sceneId, selfId, bagIndex )
-- ����Ҫ����ӿڣ���Ҫ�����պ���
end

--**********************************
--�����Ʒ��ʹ�ù����Ƿ������ڼ��ܣ�
--ϵͳ����ִ�п�ʼʱ�����������ķ���ֵ���������ʧ������Ժ�������Ƽ��ܵ�ִ�С�
--����1���������Ƶ���Ʒ�����Լ������Ƽ��ܵ�ִ�У�����0�����Ժ���Ĳ�����
--**********************************
function x418129_IsSkillLikeScript( sceneId, selfId)
	return 1; --����ű���Ҫ����֧��
end

--**********************************
--ֱ��ȡ��Ч����
--ϵͳ��ֱ�ӵ�������ӿڣ���������������ķ���ֵȷ���Ժ�������Ƿ�ִ�С�
--����1���Ѿ�ȡ����ӦЧ��������ִ�к�������������0��û�м�⵽���Ч��������ִ�С�
--**********************************
function x418129_CancelImpacts( sceneId, selfId )
	return 0; --����Ҫ����ӿڣ���Ҫ�����պ���,����ʼ�շ���0��
end

--**********************************
--���������ڣ�
--ϵͳ���ڼ��ܼ���ʱ����������ӿڣ���������������ķ���ֵȷ���Ժ�������Ƿ�ִ�С�
--����1���������ͨ�������Լ���ִ�У�����0���������ʧ�ܣ��жϺ���ִ�С�
--**********************************
function x418129_OnConditionCheck( sceneId, selfId )
	
	--У��ʹ�õ���Ʒ
	
	if(1~=VerifyUsedItem(sceneId, selfId)) then
		return 0
	end
	return 1; --����Ҫ�κ�����������ʼ�շ���1��
end

--**********************************
--���ļ�⼰������ڣ�
--ϵͳ���ڼ������ĵ�ʱ����������ӿڣ���������������ķ���ֵȷ���Ժ�������Ƿ�ִ�С�
--����1�����Ĵ���ͨ�������Լ���ִ�У�����0�����ļ��ʧ�ܣ��жϺ���ִ�С�
--ע�⣺�ⲻ�⸺�����ĵļ��Ҳ�������ĵ�ִ�С�
--**********************************
function x418129_OnDeplete( sceneId, selfId )
	
	
	--if(DepletingUsedItem(sceneId, selfId)) == 1 then
	--	return 1;
	--end
	--return 0;
	
	return 1;
end

--**********************************
--ֻ��ִ��һ����ڣ�
--������˲�����ܻ���������ɺ��������ӿڣ������������Ҹ��������������ʱ�򣩣�������
--����Ҳ����������ɺ��������ӿڣ����ܵ�һ��ʼ�����ĳɹ�ִ��֮�󣩡�
--����1������ɹ�������0������ʧ�ܡ�
--ע�������Ǽ�����Чһ�ε����
--**********************************
function x418129_OnActivateOnce( sceneId, selfId, impactId )
	
	if GetLevel(sceneId, selfId)< x418129_g_LevelMin then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"�ȼ�����")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return
	end

--	local i = random(1,3)
	
--	local itemId = 0
--	if i<=3 then
--		itemId = x418129_g_ItemList[i]
--	end
	
	local  nZhiYe = GetZhiye( sceneId, selfId);	--0��1��2��3��4��5��6��7��8��9��10��11
	local itemId1 = 0

	if nZhiYe == 0 or nZhiYe == 1 or nZhiYe == 6 or nZhiYe == 7 then
		itemId1 = 11000905  --��ʦ��ϴʯ��
		itemId2 = 12041211	--����
		itemId3 = 12041110	--һ�������
	elseif nZhiYe == 2 or nZhiYe == 3 or nZhiYe == 8 or nZhiYe == 9 then
		itemId1 = 11000905  --��ʦ��ϴʯ��
		itemId2 = 12041213 	--׷Ӱ
		itemId3 = 12041111 	--һ��������
	elseif nZhiYe ==4 or nZhiYe == 5 or nZhiYe == 10 or nZhiYe == 11 then
		itemId1 = 11000905  --��ʦ��ϴʯ��
		itemId2 = 12041212	--�ϻ�
		itemId3 = 12041112	--һ���ܼ���
	end
	
--	local  nZhiYe = GetZhiye( sceneId, selfId);
--	local itemId2 = 0
--	if nZhiYe == 0 or nZhiYe == 1 then
--		itemId2 = 12041211	--����
--	elseif nZhiYe == 2 or nZhiYe == 3 then
--		itemId2 = 12041213 	--׷Ӱ
--	elseif nZhiYe ==4 or nZhiYe == 5 then
--		itemId2 = 12041212	--�ϻ�
--	end

--	local  nZhiYe = GetZhiye( sceneId, selfId);
--	local itemId3 = 0
--	if nZhiYe == 0 or nZhiYe == 1 then
--		itemId3 = 12041110	--һ�������
--	elseif nZhiYe == 2 or nZhiYe == 3 then
--		itemId3 = 12041111 	--һ��������
--	elseif nZhiYe ==4 or nZhiYe == 5 then
--		itemId3 = 12041112	--һ���ܼ���
--	end	
	
	BeginAddItem(sceneId)
	AddBindItem( sceneId, 12010203, 10 )	--�ɷ�������10��
	AddBindItem( sceneId, 11970021, 3 )	--��ʿ��3��
	AddBindItem( sceneId, itemId1, 1 )	--һ��ʦ��ϴʯ��1��
	AddBindItem( sceneId, itemId2, 1 )	--����ǿ����1��
	AddBindItem( sceneId, itemId3, 1 )	--һ��������ҩ1��
	
	local ret = EndAddItem(sceneId,selfId)
	if ret > 0 then
		if(DepletingUsedItem(sceneId, selfId)) == 1 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"�������������������")
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
			AddItemListToPlayer(sceneId,selfId)
		else
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"ʹ����Ʒ�쳣��")
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
		end

	else
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"�����������޷��õ���Ʒ������Ҫ������5�������ռ䣡")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
	end

end

--**********************************
--��������������ڣ�
--�������ܻ���ÿ����������ʱ��������ӿڡ�
--���أ�1�����´�������0���ж�������
--ע�������Ǽ�����Чһ�ε����
--**********************************
function x418129_OnActivateEachTick( sceneId, selfId)
	return 1; --���������Խű�, ֻ�����պ���.
end
