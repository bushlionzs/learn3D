------------------------------------------------------------------------------------------
--������� 60����69��

--�ű���

x430151_g_scriptId 		= 430151 

--��Ҫ�ĵȼ�
x430151_g_LevelMin		= 60
x430151_g_LevelMax		= 161
-- ʹ����Ʒ��õľ���ֵ
x430151_g_Exp           = 250000
x430151_g_Money					=	75	
--**********************************
--�¼��������
--**********************************
function x430151_ProcEventEntry( sceneId, selfId, bagIndex)
-- ����Ҫ����ӿڣ���Ҫ�����պ���
end

--**********************************
--�����Ʒ��ʹ�ù����Ƿ������ڼ��ܣ�
--ϵͳ����ִ�п�ʼʱ�����������ķ���ֵ���������ʧ������Ժ�������Ƽ��ܵ�ִ�С�
--����1���������Ƶ���Ʒ�����Լ������Ƽ��ܵ�ִ�У�����0�����Ժ���Ĳ�����
--**********************************
function x430151_IsSkillLikeScript( sceneId, selfId)
	return 1; --����ű���Ҫ����֧��
end

--**********************************
--ֱ��ȡ��Ч����
--ϵͳ��ֱ�ӵ�������ӿڣ���������������ķ���ֵȷ���Ժ�������Ƿ�ִ�С�
--����1���Ѿ�ȡ����ӦЧ��������ִ�к�������������0��û�м�⵽���Ч��������ִ�С�
--**********************************
function x430151_CancelImpacts( sceneId, selfId)
	return 0; --����Ҫ����ӿڣ���Ҫ�����պ���,����ʼ�շ���0��
end

--**********************************
--���������ڣ�
--ϵͳ���ڼ��ܼ���ʱ����������ӿڣ���������������ķ���ֵȷ���Ժ�������Ƿ�ִ�С�
--����1���������ͨ�������Լ���ִ�У�����0���������ʧ�ܣ��жϺ���ִ�С�
--**********************************
function x430151_OnConditionCheck( sceneId, selfId)
	--У��ʹ�õ���Ʒ
	if( 1~=VerifyUsedItem( sceneId, selfId) ) then
		return 0
	end
    local level = GetLevel( sceneId, selfId)
    if level < x430151_g_LevelMin then
        Msg2Player( sceneId, selfId, "��ĵȼ�����ʹ�ô���Ʒ����ͼ���", 8, 3)
        return 0
    end
    if level >= x430151_g_LevelMax then
        Msg2Player( sceneId, selfId, "��ĵȼ�����ʹ�ô���Ʒ����߼���", 8, 3)
        return 0
    end
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
function x430151_OnDeplete( sceneId, selfId)
    if DepletingUsedItem( sceneId, selfId) == 1 then
        return 1;
    end

    return 0
end

--**********************************
--ֻ��ִ��һ����ڣ�
--������˲�����ܻ���������ɺ��������ӿڣ������������Ҹ��������������ʱ�򣩣�������
--����Ҳ����������ɺ��������ӿڣ����ܵ�һ��ʼ�����ĳɹ�ִ��֮�󣩡�
--����1�������ɹ�������0������ʧ�ܡ�
--ע�������Ǽ�����Чһ�ε����
--**********************************
function x430151_OnActivateOnce( sceneId, selfId, impactId)
		local level =GetLevel( sceneId, selfId)
		local exp =level * x430151_g_Exp
    AddExp( sceneId, selfId, exp)
    AddMoney( sceneId, selfId, 1, x430151_g_Money*1000)
    Msg2Player(sceneId, selfId, "#Y���#R����"..exp.."#Y�Ľ���", 0, 2)
    Msg2Player(sceneId, selfId, "�������"..x430151_g_Money.."��", 0, 3)
end

--**********************************
--��������������ڣ�
--�������ܻ���ÿ����������ʱ��������ӿڡ�
--���أ�1�����´�������0���ж�������
--ע�������Ǽ�����Чһ�ε����
--**********************************
function x430151_OnActivateEachTick( sceneId, selfId)
	return 1; --���������Խű�, ֻ�����պ���.
end
