-- ����

--��Ʒ���ܵ��߼�ֻ��ʹ�û������ܺͽű���ʵ��

--�ű�:

--�����ǽű�����:


------------------------------------------------------------------------------------------
--һ����Ʒ��Ĭ�Ͻű�

--�ű���
x310366_g_scriptId = 310366

-- ʹ������������Id
x310366_g_MissionList   = {
                            { missionId = 9060, scriptId = 300364 } --�ڱ�����ս
}

--��Ҫ�ĵȼ�


--**********************************
--�¼��������
--**********************************
function x310366_ProcEventEntry( sceneId, selfId, bagIndex )
end

--**********************************
--�����Ʒ��ʹ�ù����Ƿ������ڼ��ܣ�
--ϵͳ����ִ�п�ʼʱ�����������ķ���ֵ���������ʧ������Ժ�������Ƽ��ܵ�ִ�С�
--����1���������Ƶ���Ʒ�����Լ������Ƽ��ܵ�ִ�У�����0�����Ժ���Ĳ�����
--**********************************
function x310366_IsSkillLikeScript( sceneId, selfId)
	return 1; --����ű�����Ҫ����֧��
end

--**********************************
--ֱ��ȡ��Ч����
--ϵͳ��ֱ�ӵ�������ӿڣ���������������ķ���ֵȷ���Ժ�������Ƿ�ִ�С�
--����1���Ѿ�ȡ����ӦЧ��������ִ�к�������������0��û�м�⵽���Ч��������ִ�С�
--**********************************
function x310366_CancelImpacts( sceneId, selfId )
	return 0; --����Ҫ����ӿڣ���Ҫ�����պ���,����ʼ�շ���0��
end

--**********************************
--���������ڣ�
--ϵͳ���ڼ��ܼ���ʱ����������ӿڣ���������������ķ���ֵȷ���Ժ�������Ƿ�ִ�С�
--����1���������ͨ�������Լ���ִ��(call OnDeplete)������0���������ʧ�ܣ��жϺ���ִ�С�
--**********************************
function x310366_OnConditionCheck( sceneId, selfId )
	--У��ʹ�õ���Ʒ
	if(1~=VerifyUsedItem(sceneId, selfId)) then
		return 0
	end
	
	return 1; --����Ҫ�κ�����������ʼ�շ���1��
end

--**********************************
--���ļ�⼰������ڣ�
--ϵͳ���ڼ������ĵ�ʱ����������ӿڣ���������������ķ���ֵȷ���Ժ�������Ƿ�ִ�С�
--����1�����Ĵ���ͨ�������Լ���ִ��(call OnActivateOnce)������0�����ļ��ʧ�ܣ��жϺ���ִ�С�
--ע�⣺�ⲻ�⸺�����ĵļ��Ҳ�������ĵ�ִ�С�
--**********************************
function x310366_OnDeplete( sceneId, selfId )
    -- ��ʱȡ������
	-- if(DepletingUsedItem(sceneId, selfId)) then
		-- return 1;
	-- end
	return 1
end

--**********************************
--ֻ��ִ��һ����ڣ�
--������˲�����ܻ���������ɺ��������ӿڣ������������Ҹ��������������ʱ�򣩣�������
--����Ҳ����������ɺ��������ӿڣ����ܵ�һ��ʼ�����ĳɹ�ִ��֮�󣩡�
--����1������ɹ�������0������ʧ�ܡ�
--ע�������Ǽ�����Чһ�ε����
--**********************************
function x310366_OnActivateOnce( sceneId, selfId)
    if IsHaveQuest( sceneId, selfId, 9060) < 1 then
        Msg2Player(sceneId, selfId, "����ʹ��ʧ�ܣ�������ȡ�ڱ�����ս����", 0, 2)
		Msg2Player(sceneId, selfId, "����ʹ��ʧ�ܣ�������ȡ�ڱ�����ս����", 0, 3)
        return
    end
    if CallScriptFunction( 310364, "ProcUseShovel", sceneId, selfId, 0) == 1 then
        x310366_LogicDeplete( sceneId, selfId)
    end

	return 1
end

--**********************************
--��������������ڣ�
--�������ܻ���ÿ����������ʱ��������ӿڡ�
--���أ�1�����´�������0���ж�������
--ע�������Ǽ�����Чһ�ε����
--**********************************
function x310366_OnActivateEachTick( sceneId, selfId)
	return 1; --���������Խű�, ֻ�����պ���.
end

function x310366_LogicDeplete( sceneId, selfId)
    -- print( "*-*-*-*-*-*-*-*-*-*-*-*-*-*" )
    -- ��������ı�������ֵ
    local bagIndex = GetBagIndexOfUsedItem( sceneId, selfId)
    local curTimes = GetBagItemMultTimes( sceneId, selfId, bagIndex)
    if curTimes <= 1 then
        -- delete item
        DelItemByIndexInBag( sceneId, selfId, bagIndex, 1)
    else
        -- decrease useful times
        SetBagItemMultTimes( sceneId, selfId, bagIndex, curTimes - 1)
    end
end

