--ע�⣺

--��Ʒ���ܵ��߼�ֻ��ʹ�û������ܺͽű���ʵ��

--�ű�:

--�����ǽű�����:


--3001.lua
------------------------------------------------------------------------------------------
--һ����Ʒ��Ĭ�Ͻű�

--�ű���
x430005_g_scriptId = 430005 --��ʱд���,�����õ�ʱ��һ��Ҫ��.

--��Ҫ�ĵȼ�

--Ч����ID
x430005_g_Impact1 = 7041 --��ʱд���
x430005_g_Impact2 = -1 --����
x430005_SceneList =  {2,3,4,5,6,7,8,9,10,11,86,87,89,186,187,189,286,287,289,386,387,389,73,173,273,373,74,174,274,374,68,168,268,368}

--**********************************
--�¼��������
--**********************************
function x430005_ProcEventEntry( sceneId, selfId, bagIndex )
-- ����Ҫ����ӿڣ���Ҫ�����պ���
end

--**********************************
--�����Ʒ��ʹ�ù����Ƿ������ڼ��ܣ�
--ϵͳ����ִ�п�ʼʱ�����������ķ���ֵ���������ʧ������Ժ�������Ƽ��ܵ�ִ�С�
--����1���������Ƶ���Ʒ�����Լ������Ƽ��ܵ�ִ�У�����0�����Ժ���Ĳ�����
--**********************************
function x430005_IsSkillLikeScript( sceneId, selfId)
	return 1; --����ű���Ҫ����֧��
end

--**********************************
--ֱ��ȡ��Ч����
--ϵͳ��ֱ�ӵ�������ӿڣ���������������ķ���ֵȷ���Ժ�������Ƿ�ִ�С�
--����1���Ѿ�ȡ����ӦЧ��������ִ�к�������������0��û�м�⵽���Ч��������ִ�С�
--**********************************
function x430005_CancelImpacts( sceneId, selfId )
	return 0; --����Ҫ����ӿڣ���Ҫ�����պ���,����ʼ�շ���0��
end

--**********************************
--���������ڣ�
--ϵͳ���ڼ��ܼ���ʱ����������ӿڣ���������������ķ���ֵȷ���Ժ�������Ƿ�ִ�С�
--����1���������ͨ�������Լ���ִ�У�����0���������ʧ�ܣ��жϺ���ִ�С�
--**********************************
function x430005_OnConditionCheck( sceneId, selfId )
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
function x430005_OnDeplete( sceneId, selfId )
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
function x430005_OnActivateOnce( sceneId, selfId )

	if(-1~=x430005_g_Impact1) then

		if IsHaveSpecificImpact(sceneId, selfId,x430005_g_Impact1) > 0 then
			local lastContinuance = GetImpactContinuanceByDataIndex(sceneId, selfId, x430005_g_Impact1) - GetImpactContinuanceElapsed(sceneId, selfId, x430005_g_Impact1) 
			if lastContinuance >= 0 then
				SetImpactContinuanceByDataIndex( sceneId, selfId, x430005_g_Impact1, lastContinuance+60*60*1000 )
				ResetImpactContinuanceElapsed(sceneId, selfId, x430005_g_Impact1)
				RefreshImpactByDataIndex(sceneId, selfId,x430005_g_Impact1)
			end
		else
			SendSpecificImpactToUnit(sceneId, selfId, selfId, selfId, x430005_g_Impact1, 0)
		end
		
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, "������һСʱ��ս��ӻ�");
		EndQuestEvent(sceneId);
		DispatchQuestTips(sceneId,selfId);
		Msg2Player(sceneId,selfId,"������һСʱ��ս��ӻ�",8,2)

		local sign=0;
		for i, item in x430005_SceneList do
			if sceneId == item then sign = 1 break end
		end

		if sign == 1 then
			if IsHaveSpecificImpact( sceneId, selfId, x430005_g_Impact1 ) > 0 then
				--local curMult = GetWanFaExpMult(sceneId, selfId)
				SetWanFaExpMult( sceneId, selfId, 0.5 )
				
			end
		else
			SetWanFaExpMult( sceneId, selfId, 0 )
		end
	
	end
	return 1;
end

--**********************************
--��������������ڣ�
--�������ܻ���ÿ����������ʱ��������ӿڡ�
--���أ�1�����´�������0���ж�������
--ע�������Ǽ�����Чһ�ε����
--**********************************
function x430005_OnActivateEachTick( sceneId, selfId)
	return 1; --���������Խű�, ֻ�����պ���.
end
