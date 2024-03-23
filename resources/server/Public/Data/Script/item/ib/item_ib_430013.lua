--׷�ٷ�����
------------------------------------------------------------------------------------------

--�ű���

x430013_g_scriptId 		= 430013 


--**********************************
--�¼��������
--**********************************
function x430013_ProcEventEntry( sceneId, selfId, bagIndex)
-- ����Ҫ����ӿڣ���Ҫ�����պ���
end

--**********************************
--�����Ʒ��ʹ�ù����Ƿ������ڼ��ܣ�
--ϵͳ����ִ�п�ʼʱ�����������ķ���ֵ���������ʧ������Ժ�������Ƽ��ܵ�ִ�С�
--����1���������Ƶ���Ʒ�����Լ������Ƽ��ܵ�ִ�У�����0�����Ժ���Ĳ�����
--**********************************
function x430013_IsSkillLikeScript( sceneId, selfId)
	return 1; --����ű���Ҫ����֧��
end

--**********************************
--ֱ��ȡ��Ч����
--ϵͳ��ֱ�ӵ�������ӿڣ���������������ķ���ֵȷ���Ժ�������Ƿ�ִ�С�
--����1���Ѿ�ȡ����ӦЧ��������ִ�к�������������0��û�м�⵽���Ч��������ִ�С�
--**********************************
function x430013_CancelImpacts( sceneId, selfId)
	return 0; --����Ҫ����ӿڣ���Ҫ�����պ���,����ʼ�շ���0��
end

--**********************************
--���������ڣ�
--ϵͳ���ڼ��ܼ���ʱ����������ӿڣ���������������ķ���ֵȷ���Ժ�������Ƿ�ִ�С�
--����1���������ͨ�������Լ���ִ�У�����0���������ʧ�ܣ��жϺ���ִ�С�
--**********************************
function x430013_OnConditionCheck( sceneId, selfId)
	--У��ʹ�õ���Ʒ
	if( 1~=VerifyUsedItem( sceneId, selfId) ) then
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
function x430013_OnDeplete( sceneId, selfId)
    --if DepletingUsedItem( sceneId, selfId) == 1 then
    --    return 1;
   	--end
	local playerName = GetFindPlayerItemName(sceneId, selfId)

	if GetName(sceneId, selfId) == playerName then	
		Msg2Player(sceneId, selfId,"���ܲ����Լ���", 8, 3)	
		Msg2Player(sceneId, selfId,"���ܲ����Լ���", 8, 2)	
		return 0
	end
	
	local bagIndex = GetBagIndexOfUsedItem( sceneId, selfId)
	local bLock = IsItemLocked(sceneId, selfId, bagIndex)
	if bLock > 0 then
		return 0-- ������ס
	end
	
    local bFlag = GetItemParam( sceneId, selfId, bagIndex, 8, 2)
    if bFlag == 1 then
    	return 0-- ��������ʹ��
	end
	
    SetItemParam( sceneId, selfId, bagIndex, 8, 2, 1)
    LockItem(sceneId, selfId, bagIndex)
    
	UseFindPlayerItem(sceneId, selfId, playerName)
	
	GamePlayScriptLog(sceneId, selfId, 1471)
    return 1
end

--**********************************
--ֻ��ִ��һ����ڣ�
--������˲�����ܻ���������ɺ��������ӿڣ������������Ҹ��������������ʱ�򣩣�������
--����Ҳ����������ɺ��������ӿڣ����ܵ�һ��ʼ�����ĳɹ�ִ��֮�󣩡�
--����1������ɹ�������0������ʧ�ܡ�
--ע�������Ǽ�����Чһ�ε����
--**********************************
function x430013_OnActivateOnce( sceneId, selfId, impactId)
   return 1
end

--**********************************
--��������������ڣ�
--�������ܻ���ÿ����������ʱ��������ӿڡ�
--���أ�1�����´�������0���ж�������
--ע�������Ǽ�����Чһ�ε����
--**********************************
function x430013_OnActivateEachTick( sceneId, selfId)
	return 1; --���������Խű�, ֻ�����պ���.
end
