
x300170_g_scriptId  = 300170
x300170_g_Impact1   = -1--Ч��ID�������Ӻ���
x300170_g_Impact2   = -1 --����
x300170_g_FarScriptId	= 300160
x300170_g_BuffId        = 7648


--**********************************
--�¼��������
--**********************************
function x300170_ProcEventEntry( sceneId, selfId, bagIndex )
-- ����Ҫ����ӿڣ���Ҫ�����պ���
end

--**********************************
--�����Ʒ��ʹ�ù����Ƿ������ڼ��ܣ�
--ϵͳ����ִ�п�ʼʱ�����������ķ���ֵ���������ʧ������Ժ�������Ƽ��ܵ�ִ�С�
--����1���������Ƶ���Ʒ�����Լ������Ƽ��ܵ�ִ�У�����0�����Ժ���Ĳ�����
--**********************************
function x300170_IsSkillLikeScript( sceneId, selfId)
	return 1; --����ű���Ҫ����֧��
end

--**********************************
--ֱ��ȡ��Ч����
--ϵͳ��ֱ�ӵ�������ӿڣ���������������ķ���ֵȷ���Ժ�������Ƿ�ִ�С�
--����1���Ѿ�ȡ����ӦЧ��������ִ�к�������������0��û�м�⵽���Ч��������ִ�С�
--**********************************
function x300170_CancelImpacts( sceneId, selfId )
	return 0; --����Ҫ����ӿڣ���Ҫ�����պ���,����ʼ�շ���0��
end

--**********************************
--���������ڣ�
--ϵͳ���ڼ��ܼ���ʱ����������ӿڣ���������������ķ���ֵȷ���Ժ�������Ƿ�ִ�С�
--����1���������ͨ�������Լ���ִ�У�����0���������ʧ�ܣ��жϺ���ִ�С�
--**********************************
function x300170_OnConditionCheck( sceneId, selfId )
    -- Buffʣ��ʱ���������2Сʱ50�־ͽ�ֹ����ʹ��
    if GetImpactContinuanceByDataIndex( sceneId, selfId, x300170_g_BuffId) - GetImpactContinuanceElapsed( sceneId, selfId, x300170_g_BuffId) > 35400000 then
        Msg2Player( sceneId, selfId, "�Ѿ��ﵽ�ۼ����ޣ����ܼ���ʹ��֥��ʿ��", 8, 3)
        return 0
    end
    if IsHaveSpecificImpact( sceneId, selfId, 7647) == 1 then
        Msg2Player( sceneId, selfId, "����������ͬ���͵�״̬����Ƚܿ˵�����ʧ����ʹ�ã�", 8, 3)
        return 0
    end
    if IsHaveSpecificImpact( sceneId, selfId, 7667) == 1 then
        Msg2Player( sceneId, selfId, "����������ͬ���͵�״̬����Ⱦ�Ʒ֥��ʿ��ʧ����ʹ�ã�", 8, 3)
        return 0
    end
    if IsHaveSpecificImpact( sceneId, selfId, 7668) == 1 then
        Msg2Player( sceneId, selfId, "����������ͬ���͵�״̬����Ⱦ�Ʒ�ܿ˵�����ʧ����ʹ�ã�", 8, 3)
        return 0
    end

    return 1
end
--**********************************
--���ļ�⼰������ڣ�
--ϵͳ���ڼ������ĵ�ʱ����������ӿڣ���������������ķ���ֵȷ���Ժ�������Ƿ�ִ�С�
--����1�����Ĵ���ͨ�������Լ���ִ�У�����0�����ļ��ʧ�ܣ��жϺ���ִ�С�
--ע�⣺�ⲻ�⸺�����ĵļ��Ҳ�������ĵ�ִ�С�
--**********************************
function x300170_OnDeplete( sceneId, selfId )
 	if DepletingUsedItem(sceneId, selfId) == 1 then
 		CallScriptFunction(x300170_g_FarScriptId, "OnUseItem", sceneId, selfId, x300170_g_BuffId)
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
function x300170_OnActivateOnce( sceneId, selfId )
	if(-1~=x300170_g_Impact1) then
		SendSpecificImpactToUnit(sceneId, selfId, selfId, selfId, x300170_g_Impact1, 0);
	end
	return 1;
end

--**********************************
--��������������ڣ�
--�������ܻ���ÿ����������ʱ��������ӿڡ�
--���أ�1�����´�������0���ж�������
--ע�������Ǽ�����Чһ�ε����
--**********************************
function x300170_OnActivateEachTick( sceneId, selfId)
	return 1; --���������Խű�, ֻ�����պ���.
end
