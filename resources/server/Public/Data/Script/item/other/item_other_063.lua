--���ΰ׽�10����� 
------------------------------------------------------------------------------------------
--һ����Ʒ��Ĭ�Ͻű�

--�ű���

x418063_g_scriptId = 418063
x418063_g_ItemList = {}
x418063_g_LevelMin = 10	
x418063_g_ItemList = {10200020,10230020,10240020,10250020,10260020,10270020}--ͷ��
--��Ҫ�ĵȼ�


--**********************************
--�¼��������
--**********************************
function x418063_ProcEventEntry( sceneId, selfId, bagIndex )
-- ����Ҫ����ӿڣ���Ҫ�����պ���
end

--**********************************
--�����Ʒ��ʹ�ù����Ƿ������ڼ��ܣ�
--ϵͳ����ִ�п�ʼʱ�����������ķ���ֵ���������ʧ������Ժ�������Ƽ��ܵ�ִ�С�
--����1���������Ƶ���Ʒ�����Լ������Ƽ��ܵ�ִ�У�����0�����Ժ���Ĳ�����
--**********************************
function x418063_IsSkillLikeScript( sceneId, selfId)
	return 1; --����ű���Ҫ����֧��
end

--**********************************
--ֱ��ȡ��Ч����
--ϵͳ��ֱ�ӵ�������ӿڣ���������������ķ���ֵȷ���Ժ�������Ƿ�ִ�С�
--����1���Ѿ�ȡ����ӦЧ��������ִ�к�������������0��û�м�⵽���Ч��������ִ�С�
--**********************************
function x418063_CancelImpacts( sceneId, selfId )
	return 0; --����Ҫ����ӿڣ���Ҫ�����պ���,����ʼ�շ���0��
end

--**********************************
--���������ڣ�
--ϵͳ���ڼ��ܼ���ʱ����������ӿڣ���������������ķ���ֵȷ���Ժ�������Ƿ�ִ�С�
--����1���������ͨ�������Լ���ִ�У�����0���������ʧ�ܣ��жϺ���ִ�С�
--**********************************
function x418063_OnConditionCheck( sceneId, selfId )
	
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
function x418063_OnDeplete( sceneId, selfId )
	
	
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
function x418063_OnActivateOnce( sceneId, selfId, impactId )
	
	if GetLevel(sceneId, selfId)< x418063_g_LevelMin then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"�ȼ�����")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return
	end

	local nZhiYe = GetZhiye( sceneId, selfId);
	local itemId = 0;

	if nZhiYe==0 then
		itemId = 10010020	--����
	elseif nZhiYe==1 then
		itemId = 10020020
	elseif nZhiYe==2 then
		itemId = 10030020
	elseif nZhiYe==3 then
		itemId = 10040020
	elseif nZhiYe==4 then
		itemId = 10050020
	elseif nZhiYe==5 then
		itemId = 10060020
	elseif nZhiYe==6 then
		itemId = 10350002
	elseif nZhiYe==7 then
		itemId = 10360002
	elseif nZhiYe==8 then
		itemId = 10370002
	elseif nZhiYe==9 then
		itemId = 10380002
	elseif nZhiYe==10 then
		itemId = 10390002
	elseif nZhiYe==11 then
		itemId = 10400002
	end

	if itemId==0 then
		return
	end
	
	local i = random(1,6)
	local j = random(1,6)
	while(i==j) do
		j = random(1,6)
	end
	
	local itemId2 = 0
	if i<=6 then
		itemId2 = x418063_g_ItemList[i]
	else
		return
	end

	local itemId3 = 0
	if j<=6 then
		itemId3 = x418063_g_ItemList[j]
	else
		return
	end
	
	BeginAddItem(sceneId)
	AddBindItem( sceneId, itemId2, 1 )	--��װ1
	AddBindItem( sceneId, itemId3, 1 )	--��װ2
--	AddBindItem( sceneId, itemId, 1 )	--��װ����1
	AddBindItem( sceneId, 12110206, 1 )	--����һ��1
	AddBindItem( sceneId, 12030319, 1 )	--����5��
	AddBindItem( sceneId, 11000600, 3 )	--������ˮ��3
	AddBindItem( sceneId, 11000200, 5 )	--����ˮ��5
	AddBindItem( sceneId, 10300103, 1 )	--������װ1
	

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
		AddQuestText(sceneId,"�����������޷��õ���Ʒ������Ҫ������7�������ռ䣡")
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
function x418063_OnActivateEachTick( sceneId, selfId)
	return 1; --���������Խű�, ֻ�����պ���.
end
