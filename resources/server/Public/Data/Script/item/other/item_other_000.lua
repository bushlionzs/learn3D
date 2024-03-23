
------------------------------------------------------------------------------------------
--һ����Ʒ��Ĭ�Ͻű�

--�ű���

x418000_g_scriptId = 418000
x418000_g_ItemList = {10200010,10230010,10240010,10250010,10260010,10270010}
--��Ҫ�ĵȼ�


--**********************************
--�¼��������
--**********************************
function x418000_ProcEventEntry( sceneId, selfId, bagIndex )
-- ����Ҫ����ӿڣ���Ҫ�����պ���
end

--**********************************
--�����Ʒ��ʹ�ù����Ƿ������ڼ��ܣ�
--ϵͳ����ִ�п�ʼʱ�����������ķ���ֵ���������ʧ������Ժ�������Ƽ��ܵ�ִ�С�
--����1���������Ƶ���Ʒ�����Լ������Ƽ��ܵ�ִ�У�����0�����Ժ���Ĳ�����
--**********************************
function x418000_IsSkillLikeScript( sceneId, selfId)
	return 1; --����ű���Ҫ����֧��
end

--**********************************
--ֱ��ȡ��Ч����
--ϵͳ��ֱ�ӵ�������ӿڣ���������������ķ���ֵȷ���Ժ�������Ƿ�ִ�С�
--����1���Ѿ�ȡ����ӦЧ��������ִ�к�������������0��û�м�⵽���Ч��������ִ�С�
--**********************************
function x418000_CancelImpacts( sceneId, selfId )
	return 0; --����Ҫ����ӿڣ���Ҫ�����պ���,����ʼ�շ���0��
end

--**********************************
--���������ڣ�
--ϵͳ���ڼ��ܼ���ʱ����������ӿڣ���������������ķ���ֵȷ���Ժ�������Ƿ�ִ�С�
--����1���������ͨ�������Լ���ִ�У�����0���������ʧ�ܣ��жϺ���ִ�С�
--**********************************
function x418000_OnConditionCheck( sceneId, selfId )
	
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
function x418000_OnDeplete( sceneId, selfId )
	
	
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
function x418000_OnActivateOnce( sceneId, selfId, impactId )
	
	local nZhiYe = GetZhiye( sceneId, selfId);
	local itemId = 0;



	if nZhiYe==0 then
		itemId = 10010010
	elseif nZhiYe==1 then
		itemId = 10020010
	elseif nZhiYe==2 then
		itemId = 10030010
	elseif nZhiYe==3 then
		itemId = 10040010
	elseif nZhiYe==4 then
		itemId = 10050010
	elseif nZhiYe==5 then
		itemId = 10060010
	elseif nZhiYe==6 then
		itemId = 10350001
	elseif nZhiYe==7 then
		itemId = 10360001
	elseif nZhiYe==8 then
		itemId = 10370001
	elseif nZhiYe==9 then
		itemId = 10380001
	elseif nZhiYe==10 then
		itemId = 10390001
	elseif nZhiYe==11 then
		itemId = 10400001
	end

	if itemId==0 then
		return
	end
	
	local i = random(1,7)
	local j = random(1,7)
	while(i==j) do
		j = random(1,7)
	end
	
	
	local itemId2 = 0
	if i<=6 then
		itemId2 = x418000_g_ItemList[i]
	else
		itemId2 = itemId
	end

	local itemId3 = 0
	if j<=6 then
		itemId3 = x418000_g_ItemList[j]
	else
		itemId3 = itemId
	end
	
	BeginAddItem(sceneId)
	AddBindItem( sceneId, 12010001, 5 )
	AddBindItem( sceneId, itemId2, 1 )
	AddBindItem( sceneId, itemId3, 1 )
	AddBindItem( sceneId, 12010100, 1 )
	--AddBindItem( sceneId, 12010100, 1 )
	AddBindItem( sceneId, 12030306, 1 )
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
function x418000_OnActivateEachTick( sceneId, selfId)
	return 1; --���������Խű�, ֻ�����պ���.
end
