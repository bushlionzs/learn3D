--ϲ��
------------------------------------------------------------------------------------------
--һ����Ʒ��Ĭ�Ͻű�

--�ű���

x300390_g_scriptId = 300390 
x300390_g_ItemList = {
{11000200,11050001},
{11000201,11050002},
{11000202,11050003},
{11000203,11050004},
}
--��Ҫ�ĵȼ�


--**********************************
--�¼��������
--**********************************
function x300390_ProcEventEntry( sceneId, selfId, bagIndex )
-- ����Ҫ����ӿڣ���Ҫ�����պ���
end

--**********************************
--�����Ʒ��ʹ�ù����Ƿ������ڼ��ܣ�
--ϵͳ����ִ�п�ʼʱ�����������ķ���ֵ���������ʧ������Ժ�������Ƽ��ܵ�ִ�С�
--����1���������Ƶ���Ʒ�����Լ������Ƽ��ܵ�ִ�У�����0�����Ժ���Ĳ�����
--**********************************
function x300390_IsSkillLikeScript( sceneId, selfId)
	return 1; --����ű���Ҫ����֧��
end

--**********************************
--ֱ��ȡ��Ч����
--ϵͳ��ֱ�ӵ�������ӿڣ���������������ķ���ֵȷ���Ժ�������Ƿ�ִ�С�
--����1���Ѿ�ȡ����ӦЧ��������ִ�к�������������0��û�м�⵽���Ч��������ִ�С�
--**********************************
function x300390_CancelImpacts( sceneId, selfId )
	return 0; --����Ҫ����ӿڣ���Ҫ�����պ���,����ʼ�շ���0��
end

--**********************************
--���������ڣ�
--ϵͳ���ڼ��ܼ���ʱ����������ӿڣ���������������ķ���ֵȷ���Ժ�������Ƿ�ִ�С�
--����1���������ͨ�������Լ���ִ�У�����0���������ʧ�ܣ��жϺ���ִ�С�
--**********************************
function x300390_OnConditionCheck( sceneId, selfId )
	
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
function x300390_OnDeplete( sceneId, selfId )
	return 1;
end

function x300390_OnAddMoney(sceneId, selfId)
	local level = GetLevel(sceneId, selfId)
	local money = 5000; 
	if(DepletingUsedItem(sceneId, selfId)) == 1 then
	
		AddMoney( sceneId , selfId ,0, money )
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"��ʹ����ϲ��")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		
	end
	
end

function x300390_OnAddItemByLevel(sceneId, selfId)

	local i = random(1,2)
	
	if GetLevel(sceneId,selfId) < 40 then
		x300390_OnAddItem(sceneId, selfId, x300390_g_ItemList[1][i])
		
	elseif (GetLevel(sceneId,selfId) >=40 and GetLevel(sceneId,selfId) < 60) then
		x300390_OnAddItem(sceneId, selfId, x300390_g_ItemList[2][i])
		
	elseif (GetLevel(sceneId,selfId) >= 60 and GetLevel(sceneId,selfId) < 80) then
		x300390_OnAddItem(sceneId, selfId, x300390_g_ItemList[3][i]) 
	elseif GetLevel(sceneId,selfId) >= 80 then
		x300390_OnAddItem(sceneId, selfId, x300390_g_ItemList[4][i]) 
	end
	
end

function x300390_OnAddItem(sceneId, selfId, itemId)

	BeginAddItem(sceneId)
	AddBindItem( sceneId,itemId, 1 )	--IB��Ʒ1
	local ret = EndAddItem(sceneId,selfId)
	if ret > 0 then
		if(DepletingUsedItem(sceneId, selfId)) == 1 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"��ʹ����ϲ��")
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
			AddItemListToPlayer(sceneId,selfId)
		end

	else
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"�����������޷��õ���Ʒ������Ҫ������1�������ռ䣡")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
	end
	
end

--**********************************
--ֻ��ִ��һ����ڣ�
--������˲�����ܻ���������ɺ��������ӿڣ������������Ҹ��������������ʱ�򣩣�������
--����Ҳ����������ɺ��������ӿڣ����ܵ�һ��ʼ�����ĳɹ�ִ��֮�󣩡�
--����1������ɹ�������0������ʧ�ܡ�
--ע�������Ǽ�����Чһ�ε����
--**********************************
function x300390_OnActivateOnce( sceneId, selfId, impactId )

	local j = random(1,2)
	
	if j < 2 then
		x300390_OnAddMoney(sceneId, selfId)
	else
		x300390_OnAddItemByLevel(sceneId, selfId)
	end
	
end

--**********************************
--��������������ڣ�
--�������ܻ���ÿ����������ʱ��������ӿڡ�
--���أ�1�����´�������0���ж�������
--ע�������Ǽ�����Чһ�ε����
--**********************************
function x300390_OnActivateEachTick( sceneId, selfId)
	return 1; --���������Խű�, ֻ�����պ���.
end
