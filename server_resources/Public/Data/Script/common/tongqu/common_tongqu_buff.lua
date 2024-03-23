--ע�⣺

--��Ʒ���ܵ��߼�ֻ��ʹ�û������ܺͽű���ʵ��

--�ű�:

--�����ǽű�����:

--3001.lua
------------------------------------------------------------------------------------------
--һ����Ʒ��Ĭ�Ͻű�

--�ű���
x300321_g_scriptId = 300321 --��ʱд���,�����õ�ʱ��һ��Ҫ��.
x300321_g_MissionList = { 8066, 8074, 8067, 8068, 8069,8070, 8071, 8072, 8073 }
--**********************************
--�¼��������
--**********************************
function x300321_ProcEventEntry( sceneId, selfId, Index, sign )
	if sign==1 then
		CancelSpecificImpact(sceneId, selfId,7534)
		ClearMutexState(sceneId, selfId, 21)

		local MissionId = -1
		for i, item in x300321_g_MissionList do
			if IsHaveQuestNM( sceneId, selfId, item ) > 0 then
				MissionId = item
				break
			end
		end

		if MissionId == -1 then
			return
		end

		local ret = 0
		ret = DelQuestNM( sceneId, selfId, MissionId )
		if ret == 1 then
			--ɾ����Ʒ
			local ItemCnt = GetItemCount( sceneId, selfId, 13013500 )
			if ItemCnt > 0 then 
				DelItem(sceneId, selfId,13013500, 1)
			end

			ItemCnt = GetItemCount( sceneId, selfId, 13013501 )
			if ItemCnt > 0 then 
				DelItem(sceneId, selfId,13013501, 1)
			end

			local message ="�����Ѿ�ʧЧ������ʧ��"
			BeginQuestEvent(sceneId);
			AddQuestText(sceneId, message);
			EndQuestEvent(sceneId);
			DispatchQuestTips(sceneId,selfId);
		end
	end
end

--**********************************
--�����Ʒ��ʹ�ù����Ƿ������ڼ��ܣ�
--ϵͳ����ִ�п�ʼʱ�����������ķ���ֵ���������ʧ������Ժ�������Ƽ��ܵ�ִ�С�
--����1���������Ƶ���Ʒ�����Լ������Ƽ��ܵ�ִ�У�����0�����Ժ���Ĳ�����
--**********************************
function x300321_IsSkillLikeScript( sceneId, selfId)
	return 1; --����ű���Ҫ����֧��
end

--**********************************
--ֱ��ȡ��Ч����
--ϵͳ��ֱ�ӵ�������ӿڣ���������������ķ���ֵȷ���Ժ�������Ƿ�ִ�С�
--����1���Ѿ�ȡ����ӦЧ��������ִ�к�������������0��û�м�⵽���Ч��������ִ�С�
--**********************************
function x300321_CancelImpacts( sceneId, selfId )
	return 0; --����Ҫ����ӿڣ���Ҫ�����պ���,����ʼ�շ���0��
end

--**********************************
--���������ڣ�
--ϵͳ���ڼ��ܼ���ʱ����������ӿڣ���������������ķ���ֵȷ���Ժ�������Ƿ�ִ�С�
--����1���������ͨ�������Լ���ִ�У�����0���������ʧ�ܣ��жϺ���ִ�С�
--**********************************
function x300321_OnConditionCheck( sceneId, selfId )
	--У��ʹ�õ���Ʒ
	--if(1~=VerifyUsedItem(sceneId, selfId)) then
		--return 0
	--end
	return 1; --����Ҫ�κ�����������ʼ�շ���1��
end

--**********************************
--���ļ�⼰������ڣ�
--ϵͳ���ڼ������ĵ�ʱ����������ӿڣ���������������ķ���ֵȷ���Ժ�������Ƿ�ִ�С�
--����1�����Ĵ���ͨ�������Լ���ִ�У�����0�����ļ��ʧ�ܣ��жϺ���ִ�С�
--ע�⣺�ⲻ�⸺�����ĵļ��Ҳ�������ĵ�ִ�С�
--**********************************
function x300321_OnDeplete( sceneId, selfId )
	--if(DepletingUsedItem(sceneId, selfId)) then
		--return 1;
	--end
	return 1;
end

--**********************************
--ֻ��ִ��һ����ڣ�
--������˲�����ܻ���������ɺ��������ӿڣ������������Ҹ��������������ʱ�򣩣�������
--����Ҳ����������ɺ��������ӿڣ����ܵ�һ��ʼ�����ĳɹ�ִ��֮�󣩡�
--����1������ɹ�������0������ʧ�ܡ�
--ע�������Ǽ�����Чһ�ε����
--**********************************
function x300321_OnActivateOnce( sceneId, selfId )
	--if(-1~=x300321_g_Impact1) then
		--SendSpecificImpactToUnit(sceneId, selfId, selfId, selfId, x300321_g_Impact1, 0);
	--end
	return 1;
end

--**********************************
--��������������ڣ�
--�������ܻ���ÿ����������ʱ��������ӿڡ�
--���أ�1�����´�������0���ж�������
--ע�������Ǽ�����Чһ�ε����
--**********************************
function x300321_OnActivateEachTick( sceneId, selfId)
	return 1; --���������Խű�, ֻ�����պ���.
end
