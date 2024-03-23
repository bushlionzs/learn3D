
x300171_g_scriptId  = 300171
x300171_g_Impact1   = -1--Ч��ID�������Ӻ���
x300171_g_Impact2   = -1 --����
x300171_g_FarScriptId	= 300160
x300171_g_BuffId        = 7649


--**********************************
--�¼��������
--**********************************
function x300171_ProcEventEntry( sceneId, selfId, bagIndex )
-- ����Ҫ����ӿڣ���Ҫ�����պ���
end

--**********************************
--�����Ʒ��ʹ�ù����Ƿ������ڼ��ܣ�
--ϵͳ����ִ�п�ʼʱ�����������ķ���ֵ���������ʧ������Ժ�������Ƽ��ܵ�ִ�С�
--����1���������Ƶ���Ʒ�����Լ������Ƽ��ܵ�ִ�У�����0�����Ժ���Ĳ�����
--**********************************
function x300171_IsSkillLikeScript( sceneId, selfId)
	return 1; --����ű���Ҫ����֧��
end

--**********************************
--ֱ��ȡ��Ч����
--ϵͳ��ֱ�ӵ�������ӿڣ���������������ķ���ֵȷ���Ժ�������Ƿ�ִ�С�
--����1���Ѿ�ȡ����ӦЧ��������ִ�к�������������0��û�м�⵽���Ч��������ִ�С�
--**********************************
function x300171_CancelImpacts( sceneId, selfId )
	return 0; --����Ҫ����ӿڣ���Ҫ�����պ���,����ʼ�շ���0��
end

--**********************************
--���������ڣ�
--ϵͳ���ڼ��ܼ���ʱ����������ӿڣ���������������ķ���ֵȷ���Ժ�������Ƿ�ִ�С�
--����1���������ͨ�������Լ���ִ�У�����0���������ʧ�ܣ��жϺ���ִ�С�
--**********************************
function x300171_OnConditionCheck( sceneId, selfId )
    -- Buffʣ��ʱ���������2Сʱ50�־ͽ�ֹ����ʹ��
    if GetImpactContinuanceByDataIndex( sceneId, selfId, x300171_g_BuffId) - GetImpactContinuanceElapsed( sceneId, selfId, x300171_g_BuffId) > 35400000 then
        Msg2Player( sceneId, selfId, "�Ѿ��ﵽ�ۼ����ޣ����ܼ���ʹ��·��ʮ����", 8, 3)
        return 0
    end
    if IsHaveSpecificImpact( sceneId, selfId, 7650) == 1 then
        Msg2Player( sceneId, selfId, "����������ͬ���͵�״̬���������ʫ�����ʧ����ʹ�ã�", 8, 3)
        return 0
    end
    if IsHaveSpecificImpact( sceneId, selfId, 7666) == 1 then
        Msg2Player( sceneId, selfId, "����������ͬ���͵�״̬����Ⱦ�Ʒ����ʫ�����ʧ����ʹ�ã�", 8, 3)
        return 0
    end
    if IsHaveSpecificImpact( sceneId, selfId, 7669) == 1 then
        Msg2Player( sceneId, selfId, "����������ͬ���͵�״̬����Ⱦ�Ʒ·��ʮ����ʧ����ʹ�ã�", 8, 3)
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
function x300171_OnDeplete( sceneId, selfId )
 	if DepletingUsedItem(sceneId, selfId) == 1 then
 		CallScriptFunction(x300171_g_FarScriptId, "OnUseItem", sceneId, selfId, 7649)
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
function x300171_OnActivateOnce( sceneId, selfId )
	if(-1~=x300171_g_Impact1) then
		SendSpecificImpactToUnit(sceneId, selfId, selfId, selfId, x300171_g_Impact1, 0);
	end
	return 1;
end

--**********************************
--��������������ڣ�
--�������ܻ���ÿ����������ʱ��������ӿڡ�
--���أ�1�����´�������0���ж�������
--ע�������Ǽ�����Чһ�ε����
--**********************************
function x300171_OnActivateEachTick( sceneId, selfId)
	return 1; --���������Խű�, ֻ�����պ���.
end
