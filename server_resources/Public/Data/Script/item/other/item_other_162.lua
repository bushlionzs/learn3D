--���견��
------------------------------------------------------------------------------------------
--һ����Ʒ��Ĭ�Ͻű�

--�ű���

x418162_g_scriptId 		= 418162 

x418162_g_LevelMin		=	-1
--��Ҫ�ĵȼ�


--**********************************
--�¼��������
--**********************************
function x418162_ProcEventEntry( sceneId, selfId, bagIndex )
-- ����Ҫ����ӿڣ���Ҫ�����պ���
end

--**********************************
--�����Ʒ��ʹ�ù����Ƿ������ڼ��ܣ�
--ϵͳ����ִ�п�ʼʱ�����������ķ���ֵ���������ʧ������Ժ�������Ƽ��ܵ�ִ�С�
--����1���������Ƶ���Ʒ�����Լ������Ƽ��ܵ�ִ�У�����0�����Ժ���Ĳ�����
--**********************************
function x418162_IsSkillLikeScript( sceneId, selfId)
	return 1; --����ű���Ҫ����֧��
end

--**********************************
--ֱ��ȡ��Ч����
--ϵͳ��ֱ�ӵ�������ӿڣ���������������ķ���ֵȷ���Ժ�������Ƿ�ִ�С�
--����1���Ѿ�ȡ����ӦЧ��������ִ�к�������������0��û�м�⵽���Ч��������ִ�С�
--**********************************
function x418162_CancelImpacts( sceneId, selfId )
	return 0; --����Ҫ����ӿڣ���Ҫ�����պ���,����ʼ�շ���0��
end

--**********************************
--���������ڣ�
--ϵͳ���ڼ��ܼ���ʱ����������ӿڣ���������������ķ���ֵȷ���Ժ�������Ƿ�ִ�С�
--����1���������ͨ�������Լ���ִ�У�����0���������ʧ�ܣ��жϺ���ִ�С�
--**********************************
function x418162_OnConditionCheck( sceneId, selfId )
	
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

--**********************************
--������
--**********************************
function x418162_GiveBonus( sceneId,selfId)
	
end

--**********************************
--ֻ��ִ��һ����ڣ�
--������˲�����ܻ���������ɺ��������ӿڣ������������Ҹ��������������ʱ�򣩣�������
--����Ҳ����������ɺ��������ӿڣ����ܵ�һ��ʼ�����ĳɹ�ִ��֮�󣩡�
--����1������ɹ�������0������ʧ�ܡ�
--ע�������Ǽ�����Чһ�ε����
--**********************************
function x418162_OnActivateOnce( sceneId, selfId, impactId )

    local bagIndex = GetBagIndexOfUsedItem( sceneId, selfId)
    -- ����ϴ�ʹ��ʱ��
    local lastUseTime = GetItemParam( sceneId, selfId, bagIndex, 8, 2)
    local curTime = GetCurrentTime()
    if lastUseTime > 0 and curTime - lastUseTime < 2592000 then -- 2592000 = 86400 * 30
        Msg2Player( sceneId, selfId, "�����ϴ�ʹ�ò���30��", 8, 3)
        return
    end
    local curTimes = GetBagItemMultTimes( sceneId, selfId, bagIndex)
	local uMoney = 0
	if curTimes == 4 then
		uMoney = 200*1000
	elseif curTimes==3 then
		uMoney = 250*1000
	elseif curTimes== 2 then
		uMoney = 300*1000
	elseif curTimes== 1 then
		uMoney = 350*1000
	end
	AddMoney(sceneId, selfId, 3, uMoney)
	GamePlayScriptLog( sceneId, selfId, 1951)
	local str = format("�����#{_MONEY%d}�𿨵Ľ�����", uMoney)
    Msg2Player(sceneId,selfId,str,8,2)
    Msg2Player(sceneId,selfId,str,8,3)
    SetItemParam( sceneId, selfId, bagIndex, 8, 2, curTime)
	
	if curTimes <= 1 then
        -- delete item
        DelItemByIndexInBag( sceneId, selfId, bagIndex, 1)
    else
        -- decrease useful times
        SetBagItemMultTimes( sceneId, selfId, bagIndex, curTimes - 1)
    end
end

--**********************************
--��������������ڣ�
--�������ܻ���ÿ����������ʱ��������ӿڡ�
--���أ�1�����´�������0���ж�������
--ע�������Ǽ�����Чһ�ε����
--**********************************
function x418162_OnActivateEachTick( sceneId, selfId)
	return 1; --���������Խű�, ֻ�����պ���.
end

function x418162_OnDeplete( sceneId, selfId)
	return 1
end