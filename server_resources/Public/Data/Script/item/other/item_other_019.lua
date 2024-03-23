--ӭ����������� 12030326
------------------------------------------------------------------------------------------
--һ����Ʒ��Ĭ�Ͻű�

--�ű���

x418019_g_scriptId = 418019
x418019_g_ItemList = {}
x418019_g_LevelMin = 20	
x418019_g_ItemList = {12030201,12030202,12041101,12010020,12030200} 
x418019_g_ItemName = {"����ʯ","�������","���в�","С������¶","С����"} 
--12030201����ʯ
--12030202�������
--12041101���в�
--12010020С������¶
--12030200С����

--��Ҫ�ĵȼ�


--**********************************
--�¼��������
--**********************************
function x418019_ProcEventEntry( sceneId, selfId, bagIndex )
-- ����Ҫ����ӿڣ���Ҫ�����պ���
end

--**********************************
--�����Ʒ��ʹ�ù����Ƿ������ڼ��ܣ�
--ϵͳ����ִ�п�ʼʱ�����������ķ���ֵ���������ʧ������Ժ�������Ƽ��ܵ�ִ�С�
--����1���������Ƶ���Ʒ�����Լ������Ƽ��ܵ�ִ�У�����0�����Ժ���Ĳ�����
--**********************************
function x418019_IsSkillLikeScript( sceneId, selfId)
	return 1; --����ű���Ҫ����֧��
end

--**********************************
--ֱ��ȡ��Ч����
--ϵͳ��ֱ�ӵ�������ӿڣ���������������ķ���ֵȷ���Ժ�������Ƿ�ִ�С�
--����1���Ѿ�ȡ����ӦЧ��������ִ�к�������������0��û�м�⵽���Ч��������ִ�С�
--**********************************
function x418019_CancelImpacts( sceneId, selfId )
	return 0; --����Ҫ����ӿڣ���Ҫ�����պ���,����ʼ�շ���0��
end

--**********************************
--���������ڣ�
--ϵͳ���ڼ��ܼ���ʱ����������ӿڣ���������������ķ���ֵȷ���Ժ�������Ƿ�ִ�С�
--����1���������ͨ�������Լ���ִ�У�����0���������ʧ�ܣ��жϺ���ִ�С�
--**********************************
function x418019_OnConditionCheck( sceneId, selfId )
	
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
function x418019_OnDeplete( sceneId, selfId )
	
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
function x418019_OnActivateOnce( sceneId, selfId, impactId )
	
	if GetLevel(sceneId, selfId)< x418019_g_LevelMin then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"�ȼ�����")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return
	end

	local j = random(1,5)
	local i = random(1,5)	
	local itemId = 0
	local itemName = 0
	local nCountry = CallScriptFunction(888888,"GetCountryName",sceneId,selfId)
	local nLevel = GetLevel(sceneId,selfId)

	if j < 5 then
		if(DepletingUsedItem(sceneId, selfId)) == 1 then
			AddMoney( sceneId, selfId, 1, 500*nLevel )
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"���ź������˲��������ף���´κ��ˣ�")
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
		else
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"ʹ����Ʒ�쳣��")
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
		end
		
	else
		if i<=5 then
			itemId = x418019_g_ItemList[i]
			itemName = 	x418019_g_ItemName[i]
	BeginAddItem(sceneId)
	AddBindItem( sceneId,itemId, 1 )	--IB��Ʒ1

	local ret = EndAddItem(sceneId,selfId)
	if ret > 0 then
		if(DepletingUsedItem(sceneId, selfId)) == 1 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"�������������������")
			EndQuestEvent(sceneId)
			AddMoney( sceneId, selfId, 1, 500*nLevel )
			local nName=GetName(sceneId,selfId)
			local msg = format("#G��ϲ%s#Y%s#G�����#R%s#G���˽�Ʒ��ÿ�˶��п��ܻ��������ˣ����ϵ��콱��ʹ��ȥ��ȡ�ɣ�",nCountry,nName,itemName)
			LuaAllScenceM2Wrold (sceneId, msg, 0, 1)--ȫ������
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
		AddQuestText(sceneId,"�����������޷��õ���Ʒ������Ҫ������1�������ռ䣡")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
	end
		else
			return
		end
	end


end

--**********************************
--��������������ڣ�
--�������ܻ���ÿ����������ʱ��������ӿڡ�
--���أ�1�����´�������0���ж�������
--ע�������Ǽ�����Чһ�ε����
--**********************************
function x418019_OnActivateEachTick( sceneId, selfId)
	return 1; --���������Խű�, ֻ�����պ���.
end
