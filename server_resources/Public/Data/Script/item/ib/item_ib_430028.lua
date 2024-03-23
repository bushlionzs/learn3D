--ע�⣺

--��Ʒ���ܵ��߼�ֻ��ʹ�û������ܺͽű���ʵ��

--�ű�:

--�����ǽű�����:


--3001.lua
------------------------------------------------------------------------------------------
--һ����Ʒ��Ĭ�Ͻű�

--�ű���
x430028_g_scriptId = 430028 --��ʱд���,�����õ�ʱ��һ��Ҫ��.

--��Ҫ�ĵȼ�
--**********************************
--�¼��������
--**********************************
function x430028_ProcEventEntry( sceneId, selfId, bagIndex )
-- ����Ҫ����ӿڣ���Ҫ�����պ���
end

--**********************************
--�����Ʒ��ʹ�ù����Ƿ������ڼ��ܣ�
--ϵͳ����ִ�п�ʼʱ�����������ķ���ֵ���������ʧ������Ժ�������Ƽ��ܵ�ִ�С�
--����1���������Ƶ���Ʒ�����Լ������Ƽ��ܵ�ִ�У�����0�����Ժ���Ĳ�����
--**********************************
function x430028_IsSkillLikeScript( sceneId, selfId)
	return 1; --����ű���Ҫ����֧��
end

--**********************************
--ֱ��ȡ��Ч����
--ϵͳ��ֱ�ӵ�������ӿڣ���������������ķ���ֵȷ���Ժ�������Ƿ�ִ�С�
--����1���Ѿ�ȡ����ӦЧ��������ִ�к�������������0��û�м�⵽���Ч��������ִ�С�
--**********************************
function x430028_CancelImpacts( sceneId, selfId )
	return 0; --����Ҫ����ӿڣ���Ҫ�����պ���,����ʼ�շ���0��
end

--**********************************
--���������ڣ�
--ϵͳ���ڼ��ܼ���ʱ����������ӿڣ���������������ķ���ֵȷ���Ժ�������Ƿ�ִ�С�
--����1���������ͨ�������Լ���ִ�У�����0���������ʧ�ܣ��жϺ���ִ�С�
--**********************************
function x430028_OnConditionCheck( sceneId, selfId )
	--У��ʹ�õ���Ʒ
	if(1~=VerifyUsedItem(sceneId, selfId)) then
		return 0
	end

	if GetPlayerVigor(sceneId, selfId) >= GetPlayerMaxVigor(sceneId, selfId) then
		local strText = "���Ļ���ֵ����������Ҫ����Ʒ"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, strText)
		DispatchQuestTips(sceneId, selfId)
		EndQuestEvent(sceneId)
		return 0
	end
	
	--���MD
	local day = GetDayOfYear()
	local rday = GetQuestData(sceneId,selfId,MD_HUOLIDAN_DAY[1],MD_HUOLIDAN_DAY[2],MD_HUOLIDAN_DAY[3])
	if day == rday then
		local strText = "���ϴ�ʹ��ʱ�䲻��һ�죬ʹ��ʧ��"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, strText)
		DispatchQuestTips(sceneId, selfId)
		EndQuestEvent(sceneId)
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
function x430028_OnDeplete( sceneId, selfId )
	if(DepletingUsedItem(sceneId, selfId)) == 1 then
		return 1;
	end
	return 0;
end

--**********************************
--ֻ��ִ��һ����ڣ�
--������˲�����ܻ���������ɺ��������ӿڣ������������Ҹ��������������ʱ�򣩣�������
--����Ҳ����������ɺ��������ӿڣ����ܵ�һ��ʼ�����ĳɹ�ִ��֮�󣩡�
--����1������ɹ�������0������ʧ�ܡ�
--ע�������Ǽ�����Чһ�ε����
--**********************************
function x430028_OnActivateOnce( sceneId, selfId )
	--���MD
	local day = GetDayOfYear()
	local rday = GetQuestData(sceneId,selfId,MD_HUOLIDAN_DAY[1],MD_HUOLIDAN_DAY[2],MD_HUOLIDAN_DAY[3])
	if day ~= rday then
		SetPlayerVigor(sceneId, selfId, GetPlayerVigor(sceneId, selfId) + 2000 )
		SetQuestData(sceneId,selfId,MD_HUOLIDAN_DAY[1],MD_HUOLIDAN_DAY[2],MD_HUOLIDAN_DAY[3],day)
	end
	return 1;
end

--**********************************
--��������������ڣ�
--�������ܻ���ÿ����������ʱ��������ӿڡ�
--���أ�1�����´�������0���ж�������
--ע�������Ǽ�����Чһ�ε����
--**********************************
function x430028_OnActivateEachTick( sceneId, selfId)
	return 1; --���������Խű�, ֻ�����պ���.
end
