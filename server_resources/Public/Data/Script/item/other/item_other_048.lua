--�����±����	12030387
------------------------------------------------------------------------------------------
--һ����Ʒ��Ĭ�Ͻű�

--�ű���

x418048_g_scriptId = 418048
x418048_g_ItemList = {}
x418048_g_LevelMin = 1
--��Ҫ�ĵȼ�


--**********************************
--�¼��������
--**********************************
function x418048_ProcEventEntry( sceneId, selfId, bagIndex )
-- ����Ҫ����ӿڣ���Ҫ�����պ���
end

--**********************************
--�����Ʒ��ʹ�ù����Ƿ������ڼ��ܣ�
--ϵͳ����ִ�п�ʼʱ�����������ķ���ֵ���������ʧ������Ժ�������Ƽ��ܵ�ִ�С�
--����1���������Ƶ���Ʒ�����Լ������Ƽ��ܵ�ִ�У�����0�����Ժ���Ĳ�����
--**********************************
function x418048_IsSkillLikeScript( sceneId, selfId)
	return 1; --����ű���Ҫ����֧��
end

--**********************************
--ֱ��ȡ��Ч����
--ϵͳ��ֱ�ӵ�������ӿڣ���������������ķ���ֵȷ���Ժ�������Ƿ�ִ�С�
--����1���Ѿ�ȡ����ӦЧ��������ִ�к�������������0��û�м�⵽���Ч��������ִ�С�
--**********************************
function x418048_CancelImpacts( sceneId, selfId )
	return 0; --����Ҫ����ӿڣ���Ҫ�����պ���,����ʼ�շ���0��
end

--**********************************
--���������ڣ�
--ϵͳ���ڼ��ܼ���ʱ����������ӿڣ���������������ķ���ֵȷ���Ժ�������Ƿ�ִ�С�
--����1���������ͨ�������Լ���ִ�У�����0���������ʧ�ܣ��жϺ���ִ�С�
--**********************************
function x418048_OnConditionCheck( sceneId, selfId )
	
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
function x418048_OnDeplete( sceneId, selfId )
	
	
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
function x418048_OnActivateOnce( sceneId, selfId, impactId )
	
	if GetLevel(sceneId, selfId)< x418048_g_LevelMin then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"�ȼ�����")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return
	end
	
	local itemId =  x418048_Yuebing(sceneId,selfId)	

	
	BeginAddItem(sceneId)
		if itemId ~= -1 then
			AddBindItem( sceneId,itemId,3 )	
		end	

	local ret = EndAddItem(sceneId,selfId)
	if ret > 0 then
		if(DepletingUsedItem(sceneId, selfId)) == 1 then
			AddItemListToPlayer(sceneId,selfId)

			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"������������������ߣ�")
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
		AddQuestText(sceneId,"�����������޷��õ���Ʒ������Ҫ������1�������ռ䣡")
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
function x418048_OnActivateEachTick( sceneId, selfId)
	return 1; --���������Խű�, ֻ�����պ���.
end

function x418048_Yuebing(sceneId,selfId)
	
	local nLevel = GetLevel(sceneId,selfId)
	local yuebing = -1
	if nLevel < 40  then
		yuebing = 12030251
	elseif nLevel >=40 and nLevel < 50 then
		yuebing = 12030252
	elseif nLevel >=50 and nLevel < 60 then	
		yuebing = 12030253
	elseif nLevel >=60 and nLevel < 70 then
		yuebing = 12030254
	elseif nLevel >=70 and nLevel < 80 then
		yuebing = 12030255
	elseif nLevel >=80 and nLevel < 90 then
		yuebing = 12030256
	elseif nLevel >=90 then
		yuebing = 12030257	
	end
	
	return yuebing

end