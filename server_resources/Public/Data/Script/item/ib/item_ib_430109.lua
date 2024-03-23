------------------------------------------------------------------------------------------
--20���±���Ĭ�Ͻű�

--�ű���

x430109_g_scriptId 		= 430109 

--**********************************
--�¼��������
--**********************************
function x430109_ProcEventEntry( sceneId, selfId, bagIndex)
-- ����Ҫ����ӿڣ���Ҫ�����պ���
end

--**********************************
--�����Ʒ��ʹ�ù����Ƿ������ڼ��ܣ�
--ϵͳ����ִ�п�ʼʱ�����������ķ���ֵ���������ʧ������Ժ�������Ƽ��ܵ�ִ�С�
--����1���������Ƶ���Ʒ�����Լ������Ƽ��ܵ�ִ�У�����0�����Ժ���Ĳ�����
--**********************************
function x430109_IsSkillLikeScript( sceneId, selfId)
	return 1; --����ű���Ҫ����֧��
end

--**********************************
--ֱ��ȡ��Ч����
--ϵͳ��ֱ�ӵ�������ӿڣ���������������ķ���ֵȷ���Ժ�������Ƿ�ִ�С�
--����1���Ѿ�ȡ����ӦЧ��������ִ�к�������������0��û�м�⵽���Ч��������ִ�С�
--**********************************
function x430109_CancelImpacts( sceneId, selfId)
	return 0; --����Ҫ����ӿڣ���Ҫ�����պ���,����ʼ�շ���0��
end

--**********************************
--���������ڣ�
--ϵͳ���ڼ��ܼ���ʱ����������ӿڣ���������������ķ���ֵȷ���Ժ�������Ƿ�ִ�С�
--����1���������ͨ�������Լ���ִ�У�����0���������ʧ�ܣ��жϺ���ִ�С�
--**********************************
function x430109_OnConditionCheck( sceneId, selfId)
	--У��ʹ�õ���Ʒ
	if( 1~=VerifyUsedItem( sceneId, selfId) ) then
		return 0
	end
    -- local level = GetLevel( sceneId, selfId)
    -- if level < x430109_g_LevelMin then
        -- Msg2Player( sceneId, selfId, "���ĵȼ�����ʹ�ô���Ʒ����ͼ���", 8, 3)
        -- return 0
    -- end
    -- if level >= x430109_g_LevelMax then
        -- Msg2Player( sceneId, selfId, "���ĵȼ�����ʹ�ô���Ʒ����߼���", 8, 3)
        -- return 0
    -- end
    if GetTiredTime( sceneId, selfId) >= 480 then
        Msg2Player( sceneId, selfId, "������ƣ��״̬���޷��ٴ�ʹ���±�", 8, 3)
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
function x430109_OnDeplete( sceneId, selfId)
    if DepletingUsedItem( sceneId, selfId) == 1 then
        return 1;
    end

    return 0
end

--**********************************
--ֻ��ִ��һ����ڣ�
--������˲�����ܻ���������ɺ��������ӿڣ������������Ҹ��������������ʱ�򣩣�������
--����Ҳ����������ɺ��������ӿڣ����ܵ�һ��ʼ�����ĳɹ�ִ��֮�󣩡�
--����1������ɹ�������0������ʧ�ܡ�
--ע�������Ǽ�����Чһ�ε����
--**********************************
function x430109_OnActivateOnce( sceneId, selfId, impactId)
	local level=GetLevel(sceneId, selfId)
	if level > 0 and level < 10 then
	nExpBonus = 50000
    AddExp( sceneId, selfId, nExpBonus)
    IncreaseTiredTime( sceneId, selfId, 120)
	end
	if level > 9 and level < 20 then
	nExpBonus = 50000
    AddExp( sceneId, selfId, nExpBonus)
    IncreaseTiredTime( sceneId, selfId, 120)
	end
	if level > 19 and level < 30 then
	nExpBonus = 50000
    AddExp( sceneId, selfId, nExpBonus)
    IncreaseTiredTime( sceneId, selfId, 120)
	end
	if level > 29 and level < 40 then
	nExpBonus = 270000
    AddExp( sceneId, selfId, nExpBonus)
    IncreaseTiredTime( sceneId, selfId, 120)
	end
	if level > 39 and level < 50 then
	nExpBonus = 400000
    AddExp( sceneId, selfId, nExpBonus)
    IncreaseTiredTime( sceneId, selfId, 120)
	end
	if level > 49 and level < 60 then
	nExpBonus = 550000
    AddExp( sceneId, selfId, nExpBonus)
    IncreaseTiredTime( sceneId, selfId, 120)
	end
	if level > 59 and level < 70 then
	nExpBonus = 720000
    AddExp( sceneId, selfId, nExpBonus)
    IncreaseTiredTime( sceneId, selfId, 120)
	end
	if level > 69 and level < 80 then
	nExpBonus = 910000
    AddExp( sceneId, selfId, nExpBonus)
    IncreaseTiredTime( sceneId, selfId, 120)
	end
	if level > 79 and level < 90 then
	nExpBonus = 1120000
    AddExp( sceneId, selfId, nExpBonus)
    IncreaseTiredTime( sceneId, selfId, 120)
	end
	if level > 89 and level < 100 then
	nExpBonus = 1350000
    AddExp( sceneId, selfId, nExpBonus)
    IncreaseTiredTime( sceneId, selfId, 120)
	end
	if level > 99 then
	nExpBonus = 1580000
    AddExp( sceneId, selfId, nExpBonus)
    IncreaseTiredTime( sceneId, selfId, 120)
	end
end

--**********************************
--��������������ڣ�
--�������ܻ���ÿ����������ʱ��������ӿڡ�
--���أ�1�����´�������0���ж�������
--ע�������Ǽ�����Чһ�ε����
--**********************************
function x430109_OnActivateEachTick( sceneId, selfId)
	return 1; --���������Խű�, ֻ�����պ���.
end

