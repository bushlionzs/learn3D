--ϲ��
------------------------------------------------------------------------------------------
--һ����Ʒ��Ĭ�Ͻű�

--�ű���

x300702_g_scriptId = 300702 
x300702_g_ItemID = 12250008
--��Ҫ�ĵȼ�


--**********************************
--�¼��������
--**********************************

function x300702_ProcEventEntry( sceneId, selfId, BagIndex,rorf )
-- ����Ҫ����ӿڣ���Ҫ�����պ���
end

--**********************************
--�����Ʒ��ʹ�ù����Ƿ������ڼ��ܣ�
--ϵͳ����ִ�п�ʼʱ�����������ķ���ֵ���������ʧ������Ժ�������Ƽ��ܵ�ִ�С�
--����1���������Ƶ���Ʒ�����Լ������Ƽ��ܵ�ִ�У�����0�����Ժ���Ĳ�����
--**********************************
function x300702_IsSkillLikeScript( sceneId, selfId)
	return 1; --����ű���Ҫ����֧��
end

--**********************************
--ֱ��ȡ��Ч����
--ϵͳ��ֱ�ӵ�������ӿڣ���������������ķ���ֵȷ���Ժ�������Ƿ�ִ�С�
--����1���Ѿ�ȡ����ӦЧ��������ִ�к�������������0��û�м�⵽���Ч��������ִ�С�
--**********************************
function x300702_CancelImpacts( sceneId, selfId )
	return 0; --����Ҫ����ӿڣ���Ҫ�����պ���,����ʼ�շ���0��
end

--**********************************
--���������ڣ�
--ϵͳ���ڼ��ܼ���ʱ����������ӿڣ���������������ķ���ֵȷ���Ժ�������Ƿ�ִ�С�
--����1���������ͨ�������Լ���ִ�У�����0���������ʧ�ܣ��жϺ���ִ�С�
--**********************************
function x300702_OnConditionCheck( sceneId, selfId, BagIndex)
	
	--У��ʹ�õ���Ʒ
	local level = GetLevel(sceneId, selfId)
	if level < 10 then
		local msg = "10�����ϲ���ʹ�ûسǾ��ᣡ"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, msg);
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,msg,8,2)
		return
	end
	if IsBusMember(sceneId, selfId) == 1 then
		local msg = "���ڡ��������������߻���״̬ʱ����ʹ�ûسǾ��ᣡ"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, msg);
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,msg,8,2)
		return 
	end
	
	if sceneId == 12 then
		local msg = "�����в���ʹ�ûسǾ��ᣡ"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, msg);
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,msg,8,2)
		return 0
	end

	if IsHaveSpecificImpact( sceneId, selfId, 7702 ) > 0 then
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, "�������Ӳ���ʹ�ûسǾ��ᣡ");
		EndQuestEvent(sceneId);
		DispatchQuestTips(sceneId,selfId);
		Msg2Player(sceneId,selfId,"�������Ӳ���ʹ�ûسǾ��ᣡ",8,2)
		return 0
	end
	
	local IsHaveFlag = IsHaveSpecificImpact(sceneId, selfId, 7536  )
    if IsHaveFlag ~= 0 then
    	local msg = "�ڱ�������ս�ڼ䣬���ܴ���"
    	BeginQuestEvent(sceneId)
			AddQuestText(sceneId, msg);
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,msg,8,2)
		return 0
    end
    
    IsHaveFlag = IsHaveSpecificImpact(sceneId, selfId, 7537 )
    if IsHaveFlag ~= 0 then
    	local msg = "�ڱ�������ս�ڼ䣬���ܴ���"
    	BeginQuestEvent(sceneId)
			AddQuestText(sceneId, msg);
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,msg,8,2)
		return 0
    end
	
	local iCount = GetItemCountInBag( sceneId, selfId, 13080024)
    if iCount > 0 then
        DelItem( sceneId, selfId, 13080024, iCount)
    end
	
	local selfType = GetObjType(sceneId, selfId)
	
	if selfType == 1 then 
		------------------------------------------------------
		if IsHaveQuestNM( sceneId, selfId, 7537) ~= 0 or  IsHaveQuestNM( sceneId, selfId, 7538) ~= 0 or IsHaveQuestNM( sceneId, selfId, 7539) ~= 0 then
			Msg2Player(sceneId,selfId,"�ܱ�Ǹ��δ���������������ʱ�޷�ͨ������������",8,2)
			return
		end
		--�����������������ֹ���͵Ĵ���
		------------------------------------------------------
	end
	
	if GetSceneType(sceneId) == 2 then
		local msg = "ս���ڣ����ܴ���"
    	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, msg);
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,msg,8,2)
		return -1
	end
	
	if GetSceneType(sceneId) == 1 then
		local msg = "�����ڣ����ܴ���"
    	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, msg);
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,msg,8,2)
		return -1
	end
	
	if sceneId == 14 then
        	SetPlayerMutexState( sceneId, selfId, PLAYER_STATE_DANCERY, 0)
            -- �ָ�����
            if IsHaveSpecificImpact( sceneId, selfId, 7651) == 1 then
                CancelSpecificImpact( sceneId, selfId, 7651)
            elseif IsHaveSpecificImpact( sceneId, selfId, 7652) == 1 then
                CancelSpecificImpact( sceneId, selfId, 7652)
            elseif IsHaveSpecificImpact( sceneId, selfId, 7653) == 1 then
                CancelSpecificImpact( sceneId, selfId, 7653)
            elseif IsHaveSpecificImpact( sceneId, selfId, 7654) == 1 then
                CancelSpecificImpact( sceneId, selfId, 7654)
            elseif IsHaveSpecificImpact( sceneId, selfId, 7655) == 1 then
                CancelSpecificImpact( sceneId, selfId, 7655)
            elseif IsHaveSpecificImpact( sceneId, selfId, 7656) == 1 then
                CancelSpecificImpact( sceneId, selfId, 7656)
            end
	end
	
	if(1~=VerifyUsedItem(sceneId, selfId)) then
		return 0
	end
	return 1; --����Ҫ�κ�����������ʼ�շ���1��
end


function x300702_OnAddItem(sceneId, selfId, itemId)
end
--**********************************
--���ļ�⼰������ڣ�
--ϵͳ���ڼ������ĵ�ʱ����������ӿڣ���������������ķ���ֵȷ���Ժ�������Ƿ�ִ�С�
--����1�����Ĵ���ͨ�������Լ���ִ�У�����0�����ļ��ʧ�ܣ��жϺ���ִ�С�
--ע�⣺�ⲻ�⸺�����ĵļ��Ҳ�������ĵ�ִ�С�
--**********************************
function x300702_OnDeplete( sceneId, selfId,BagIndex )
	local nCountry = GetCurCountry( sceneId, selfId)
	if  nCountry == 0 then --ȥ¥��
		if sceneId == 50 then
			SetPos(sceneId,selfId,128,103)
		else
			NewWorld(sceneId,selfId,50,128,103, 300702)
		end
    elseif  nCountry == 1 then -- ȥ��ɽ
		if sceneId == 150 then
			SetPos(sceneId,selfId,128,103)
		else
			NewWorld(sceneId,selfId,150,128,103, 300702)
		end
	elseif  nCountry == 2 then -- ȥ����
		if sceneId == 250 then
			SetPos(sceneId,selfId,128,153)
		else
			NewWorld(sceneId,selfId,250,128,153, 300702)
		end
	elseif  nCountry == 3 then -- ȥ�ػ�
		if sceneId == 350 then
			SetPos(sceneId,selfId,128,153)
		else
			NewWorld(sceneId,selfId,350,128,153, 300702)
		end
	end
	if impactId ~= -1 then
		SendSpecificImpactToUnit(sceneId, selfId, selfId, selfId, 7719, 0);
	end
	DepletingUsedItem(sceneId, selfId)
 return 1
end

function x300702_OnAddMoney(sceneId, selfId)
end

function x300702_OnAddItemByLevel(sceneId, selfId)	
end

--**********************************
--ֻ��ִ��һ����ڣ�
--������˲�����ܻ���������ɺ��������ӿڣ������������Ҹ��������������ʱ�򣩣�������
--����Ҳ����������ɺ��������ӿڣ����ܵ�һ��ʼ�����ĳɹ�ִ��֮�󣩡�
--����1������ɹ�������0������ʧ�ܡ�
--ע�������Ǽ�����Чһ�ε����
--**********************************
function x300702_OnActivateOnce( sceneId, selfId, impactId )	
end

--**********************************
--��������������ڣ�
--�������ܻ���ÿ����������ʱ��������ӿڡ�
--���أ�1�����´�������0���ж�������
--ע�������Ǽ�����Чһ�ε����
--**********************************
function x300702_OnActivateEachTick( sceneId, selfId)
	return 1; --���������Խű�, ֻ�����պ���.
end
