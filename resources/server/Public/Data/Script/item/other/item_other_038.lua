--��Ϧ���˿�	30�����	12030367
------------------------------------------------------------------------------------------
--һ����Ʒ��Ĭ�Ͻű�

--�ű���

x418038_g_scriptId = 418038
x418038_g_ItemList = {}
x418038_g_LevelMin = 30	
--��Ҫ�ĵȼ�


--**********************************
--�¼��������
--**********************************
function x418038_ProcEventEntry( sceneId, selfId, bagIndex )
-- ����Ҫ����ӿڣ���Ҫ�����պ���
end

--**********************************
--�����Ʒ��ʹ�ù����Ƿ������ڼ��ܣ�
--ϵͳ����ִ�п�ʼʱ�����������ķ���ֵ���������ʧ������Ժ�������Ƽ��ܵ�ִ�С�
--����1���������Ƶ���Ʒ�����Լ������Ƽ��ܵ�ִ�У�����0�����Ժ���Ĳ�����
--**********************************
function x418038_IsSkillLikeScript( sceneId, selfId)
	return 1; --����ű���Ҫ����֧��
end

--**********************************
--ֱ��ȡ��Ч����
--ϵͳ��ֱ�ӵ�������ӿڣ���������������ķ���ֵȷ���Ժ�������Ƿ�ִ�С�
--����1���Ѿ�ȡ����ӦЧ��������ִ�к�������������0��û�м�⵽���Ч��������ִ�С�
--**********************************
function x418038_CancelImpacts( sceneId, selfId )
	return 0; --����Ҫ����ӿڣ���Ҫ�����պ���,����ʼ�շ���0��
end

--**********************************
--���������ڣ�
--ϵͳ���ڼ��ܼ���ʱ����������ӿڣ���������������ķ���ֵȷ���Ժ�������Ƿ�ִ�С�
--����1���������ͨ�������Լ���ִ�У�����0���������ʧ�ܣ��жϺ���ִ�С�
--**********************************
function x418038_OnConditionCheck( sceneId, selfId )
	
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
function x418038_OnDeplete( sceneId, selfId )
	
	
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
function x418038_OnActivateOnce( sceneId, selfId, impactId )
	
	if GetLevel(sceneId, selfId)< x418038_g_LevelMin then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"�ȼ�����")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return
	end
	
	BeginAddItem(sceneId)
	AddBindItem( sceneId, 12030321, 1 )	--����15��
	AddBindItem( sceneId, 11000200, 5 )	--����5��
	AddBindItem( sceneId, 11050001, 5 )	--��������5 
	--AddBindItem( sceneId, 12030209, 1 )--�������1�죿	--2009-9-16�����ɾ���˵���
	AddBindItem( sceneId, 14040001, 1 )	--1�����ʱ�ʯ1��
	AddBindItem( sceneId, 11000100, 1 )--��ͭ��1��
	AddBindItem( sceneId, 12010200, 3 )--���ֹѪɢ3��
	AddBindItem( sceneId, 12050000, 1 )--���ֲ�1��

	local HorseNum = GetHorseCount(sceneId,selfId)
	local nLevel = GetLevel(sceneId,selfId)
	local tHNum = 0
	local settrue = 0

	if nLevel < 10 then 
		tHNum = 1
	elseif nLevel >= 10 and nLevel < 20 then
		tHNum = 2
	elseif nLevel >= 20 and nLevel < 30 then
		tHNum = 3
	elseif nLevel >= 30 and nLevel < 40 then
		tHNum = 4
	elseif nLevel >= 40 and nLevel < 50 then
		tHNum = 5
	elseif nLevel >= 50 then
		tHNum = 6
	end

	if tHNum > HorseNum then
		settrue = 1
	else
		settrue = 0
	end

	local ret = EndAddItem(sceneId,selfId)
	if ret > 0 and settrue > 0 then
		
		local a = CreateHorseToPlayer(sceneId,selfId,3630,-1)
		
		if(DepletingUsedItem(sceneId, selfId)) == 1 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"������������������ߣ�")
			AddQuestText(sceneId,"��ϲ�����ϲȵ���")
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
		AddQuestText(sceneId,"�������������������޷��õ���Ʒ������Ҫ������7�������ռ��1������ռ䣡")	--2009-9-16ɾ��һ��������˼�һ��
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
function x418038_OnActivateEachTick( sceneId, selfId)
	return 1; --���������Խű�, ֻ�����պ���.
end
