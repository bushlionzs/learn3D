--���ΰ׽�50�����	12030341
------------------------------------------------------------------------------------------
--һ����Ʒ��Ĭ�Ͻű�

--�ű���

x418067_g_scriptId = 418067
x418067_g_ItemList = {}
x418067_g_LevelMin = 50	
--��Ҫ�ĵȼ�


--**********************************
--�¼��������
--**********************************
function x418067_ProcEventEntry( sceneId, selfId, bagIndex )
-- ����Ҫ����ӿڣ���Ҫ�����պ���
end

--**********************************
--�����Ʒ��ʹ�ù����Ƿ������ڼ��ܣ�
--ϵͳ����ִ�п�ʼʱ�����������ķ���ֵ���������ʧ������Ժ�������Ƽ��ܵ�ִ�С�
--����1���������Ƶ���Ʒ�����Լ������Ƽ��ܵ�ִ�У�����0�����Ժ���Ĳ�����
--**********************************
function x418067_IsSkillLikeScript( sceneId, selfId)
	return 1; --����ű���Ҫ����֧��
end

--**********************************
--ֱ��ȡ��Ч����
--ϵͳ��ֱ�ӵ�������ӿڣ���������������ķ���ֵȷ���Ժ�������Ƿ�ִ�С�
--����1���Ѿ�ȡ����ӦЧ��������ִ�к�������������0��û�м�⵽���Ч��������ִ�С�
--**********************************
function x418067_CancelImpacts( sceneId, selfId )
	return 0; --����Ҫ����ӿڣ���Ҫ�����պ���,����ʼ�շ���0��
end

--**********************************
--���������ڣ�
--ϵͳ���ڼ��ܼ���ʱ����������ӿڣ���������������ķ���ֵȷ���Ժ�������Ƿ�ִ�С�
--����1���������ͨ�������Լ���ִ�У�����0���������ʧ�ܣ��жϺ���ִ�С�
--**********************************
function x418067_OnConditionCheck( sceneId, selfId )
	
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
function x418067_OnDeplete( sceneId, selfId )
	
	
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
function x418067_OnActivateOnce( sceneId, selfId, impactId )
	
	if GetLevel(sceneId, selfId)< x418067_g_LevelMin then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"�ȼ�����")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return
	end
	
	BeginAddItem(sceneId)
	AddBindItem( sceneId, 11050002, 20 )	--�м�����20
	AddBindItem( sceneId, 12030322, 1 )	--����30��
	AddBindItem( sceneId, 11000201, 25 )	--����25��
	AddBindItem( sceneId, 11000101, 1 )	--������1��
	AddBindItem( sceneId, 12010202, 5 )	--���߸�¶ɢ5��			
	AddBindItem( sceneId, 12010020, 1 )	--С������¶1��
	AddBindItem( sceneId, 12030013, 5 )	--֥��ʿ5��
	AddBindItem( sceneId, 12030014, 5 )	--����ʫ5��

	local ret = EndAddItem(sceneId,selfId)
	if ret > 0 then
		if(DepletingUsedItem(sceneId, selfId)) == 1 then
			AddItemListToPlayer(sceneId,selfId)
			local nShengWang = GetShengWang( sceneId, selfId )
			SetShengWang( sceneId, selfId, nShengWang+10000 )--����10000��
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"������������������ߣ����10000��������")
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
		AddQuestText(sceneId,"�����������޷��õ���Ʒ������Ҫ������8�������ռ䣡")
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
function x418067_OnActivateEachTick( sceneId, selfId)
	return 1; --���������Խű�, ֻ�����պ���.
end
