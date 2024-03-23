--���� ��700�ײ�	12030347

------------------------------------------------------------------------------------------
--һ����Ʒ��Ĭ�Ͻű�

--�ű���

x418035_g_scriptId = 418035
x418035_g_ItemList = {}
x418035_g_LevelMin = 1	
--��Ҫ�ĵȼ�


--**********************************
--�¼��������
--**********************************
function x418035_ProcEventEntry( sceneId, selfId, bagIndex )
-- ����Ҫ����ӿڣ���Ҫ�����պ���
end

--**********************************
--�����Ʒ��ʹ�ù����Ƿ������ڼ��ܣ�
--ϵͳ����ִ�п�ʼʱ�����������ķ���ֵ���������ʧ������Ժ�������Ƽ��ܵ�ִ�С�
--����1���������Ƶ���Ʒ�����Լ������Ƽ��ܵ�ִ�У�����0�����Ժ���Ĳ�����
--**********************************
function x418035_IsSkillLikeScript( sceneId, selfId)
	return 1; --����ű���Ҫ����֧��
end

--**********************************
--ֱ��ȡ��Ч����
--ϵͳ��ֱ�ӵ�������ӿڣ���������������ķ���ֵȷ���Ժ�������Ƿ�ִ�С�
--����1���Ѿ�ȡ����ӦЧ��������ִ�к�������������0��û�м�⵽���Ч��������ִ�С�
--**********************************
function x418035_CancelImpacts( sceneId, selfId )
	return 0; --����Ҫ����ӿڣ���Ҫ�����պ���,����ʼ�շ���0��
end

--**********************************
--���������ڣ�
--ϵͳ���ڼ��ܼ���ʱ����������ӿڣ���������������ķ���ֵȷ���Ժ�������Ƿ�ִ�С�
--����1���������ͨ�������Լ���ִ�У�����0���������ʧ�ܣ��жϺ���ִ�С�
--**********************************
function x418035_OnConditionCheck( sceneId, selfId )
	
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
function x418035_OnDeplete( sceneId, selfId )
	
	
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
function x418035_OnActivateOnce( sceneId, selfId, impactId )
	
	if GetLevel(sceneId, selfId)< x418035_g_LevelMin then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"�ȼ�����")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return
	end
	
	local  nZhiYe = GetZhiye( sceneId, selfId);
	local itemId1 = 0
	local itemId2 = 0
	local itemId3 = 0
	if nZhiYe == 0 then
		itemId1 = 14010003
		itemId2 = 10284003
		itemId3 = 10294003
	elseif nZhiYe == 1 then
		itemId1 = 14010003
		itemId2 = 10284013
		itemId3 = 10294013
	elseif nZhiYe == 2 then
		itemId1 = 14010008
		itemId2 = 10284023
		itemId3 = 10294023
	elseif nZhiYe == 3 then
		itemId1 = 14010008	
		itemId2 = 10284033
		itemId3 = 10294033
	elseif nZhiYe ==4 then
		itemId1 = 14010013
		itemId2 = 10284043
		itemId3 = 10294043
	elseif nZhiYe == 5 then
		itemId1 = 14010013	
		itemId2 = 10284053
		itemId3 = 10294053	
	elseif nZhiYe == 6 then
		itemId1 = 14010003
		itemId2 = 10288020
		itemId3 = 10298020
	elseif nZhiYe == 7 then
		itemId1 = 14010003
		itemId2 = 10288024
		itemId3 = 10298024
	elseif nZhiYe == 8 then
		itemId1 = 14010008
		itemId2 = 10288028
		itemId3 = 10298028
	elseif nZhiYe == 9 then
		itemId1 = 14010008	
		itemId2 = 10288032
		itemId3 = 10298032
	elseif nZhiYe ==10 then
		itemId1 = 14010013
		itemId2 = 10288036
		itemId3 = 10298036
	elseif nZhiYe == 11 then
		itemId1 = 14010013	
		itemId2 = 10288040
		itemId3 = 10298040	
	end
		
	BeginAddItem(sceneId)
	AddBindItem( sceneId, 11000202, 700 )	--��ˮ����11000202��*700 
	AddBindItem( sceneId, 11050003, 700 )	--�߼�����ʯ��11050003��*700
	AddItem( sceneId, 11060003, 50 )	--�۹���Ʊ��11060003��*50
--	AddItem( sceneId, 11000102, 1 )	--�����꣨11000102��*1
	AddItem( sceneId, 11000123, 1 )	--ī���꣨11000123��*1 
	AddItem( sceneId, 14040003, 1 )	--�߼�����解�14040003��*1
	AddItem( sceneId, itemId1, 1 )	--�߼�������ʯ����*1
	AddItem( sceneId, itemId2, 1 )	--�񴫽�ָ����*1
	AddItem( sceneId, itemId3, 1 )	--��������*1
	

	local ret = EndAddItem(sceneId,selfId)
	if ret > 0 then
		if(DepletingUsedItem(sceneId, selfId)) == 1 then
			AddItemListToPlayer(sceneId,selfId)
--			AddMoney( sceneId, selfId, 1, 1000000 )
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"�������������ײ͵��ߣ�")
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
		else
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"ʹ����Ʒ�쳣��")
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
		end
	
	else
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"�����������޷��õ���Ʒ������Ҫ������12�������ռ䣡")
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
function x418035_OnActivateEachTick( sceneId, selfId)
	return 1; --���������Խű�, ֻ�����պ���.
end
