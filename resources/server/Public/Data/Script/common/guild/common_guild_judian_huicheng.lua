--ϲ��
------------------------------------------------------------------------------------------
--һ����Ʒ��Ĭ�Ͻű�

--�ű���

x300930_g_scriptId = 300930 
x300930_g_ItemID = 12030007

--��Ҫ�ĵȼ�


--**********************************
--�¼��������
--**********************************
function x300930_ProcEventEntry( sceneId, selfId, BagIndex,rorf )
	if IsBusMember(sceneId, selfId) == 1 and rorf == 0 then
		local msg = "���ڡ��������������߻���״̬ʱ����ʹ�ûسǾ��ᣡ"
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId, msg);
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,msg,8,2)
		return
	end
-- ����Ҫ����ӿڣ���Ҫ�����պ���
end

--**********************************
--�����Ʒ��ʹ�ù����Ƿ������ڼ��ܣ�
--ϵͳ����ִ�п�ʼʱ�����������ķ���ֵ���������ʧ������Ժ�������Ƽ��ܵ�ִ�С�
--����1���������Ƶ���Ʒ�����Լ������Ƽ��ܵ�ִ�У�����0�����Ժ���Ĳ�����
--**********************************
function x300930_IsSkillLikeScript( sceneId, selfId)
	return 1; --����ű���Ҫ����֧��
end

--**********************************
--ֱ��ȡ��Ч����
--ϵͳ��ֱ�ӵ�������ӿڣ���������������ķ���ֵȷ���Ժ�������Ƿ�ִ�С�
--����1���Ѿ�ȡ����ӦЧ��������ִ�к�������������0��û�м�⵽���Ч��������ִ�С�
--**********************************
function x300930_CancelImpacts( sceneId, selfId )
	return 0; --����Ҫ����ӿڣ���Ҫ�����պ���,����ʼ�շ���0��
end

--**********************************
--���������ڣ�
--ϵͳ���ڼ��ܼ���ʱ����������ӿڣ���������������ķ���ֵȷ���Ժ�������Ƿ�ִ�С�
--����1���������ͨ�������Լ���ִ�У�����0���������ʧ�ܣ��жϺ���ִ�С�
--**********************************
function x300930_OnConditionCheck( sceneId, selfId, BagIndex)
	
	--У��ʹ�õ���Ʒ
	if GetGuildID( sceneId, selfId ) == -1 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "�ܱ�Ǹ����û�а��");
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,"�ܱ�Ǹ����û�а��",8,2)
		return
	end
	
	if IsBusMember(sceneId, selfId) == 1 then
		local msg = "���ڡ��������������߻���״̬ʱ����ʹ����ش���ʯ��"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, msg);
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,msg,8,2)
		return 
	end
	
	if sceneId == 12 then
		local msg = "�����в���ʹ����ش���ʯ��"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, msg);
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,msg,8,2)
		return 0
	end

	if IsHaveSpecificImpact( sceneId, selfId, 7702 ) > 0 then
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, "�������Ӳ���ʹ����ش���ʯ��");
		EndQuestEvent(sceneId);
		DispatchQuestTips(sceneId,selfId);
		Msg2Player(sceneId,selfId,"�������Ӳ���ʹ����ش���ʯ��",8,2)
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

function x300930_GuildLairdSceneIdTrans(sceneId, selfId, nLairdMapId)
	if nLairdMapId == 6 then
		TimerCommand( sceneId, selfId, 1, 7010, 3, -1, -1, -1 )
		if sceneId == nLairdMapId then
			SetPos(sceneId,selfId,65,94)
		else
			NewWorld(sceneId,selfId,6,65,94, 300930)
		end
	elseif nLairdMapId == 9 then
		TimerCommand( sceneId, selfId, 1, 7010, 3, -1, -1, -1 )
		if sceneId == nLairdMapId then
			SetPos(sceneId,selfId,163,56)
		else
			NewWorld(sceneId,selfId,9,163,56, 300930)
		end
	elseif nLairdMapId == 13 then
		TimerCommand( sceneId, selfId, 1, 7010, 3, -1, -1, -1 )
		if sceneId == nLairdMapId then
			SetPos(sceneId,selfId,75,193)
		else
			NewWorld(sceneId,selfId,13,75,193, 300930)
		end
	elseif nLairdMapId == 18 then
		TimerCommand( sceneId, selfId, 1, 7010, 3, -1, -1, -1 )
		if sceneId == nLairdMapId then
			SetPos(sceneId,selfId,196,57)
		else
			NewWorld(sceneId,selfId,18,196,57, 300930)
		end
	elseif nLairdMapId == 21 then
		TimerCommand( sceneId, selfId, 1, 7010, 3, -1, -1, -1 )
		if sceneId == nLairdMapId then
			SetPos(sceneId,selfId,222,130)
		else
			NewWorld(sceneId,selfId,21,222,130, 300930)
		end
	elseif nLairdMapId == 24 then
		TimerCommand( sceneId, selfId, 1, 7010, 3, -1, -1, -1 )
		if sceneId == nLairdMapId then
			SetPos(sceneId,selfId,118,101)
		else
			NewWorld(sceneId,selfId,24,118,101, 300930)
		end
	elseif nLairdMapId == 27 then
		TimerCommand( sceneId, selfId, 1, 7010, 3, -1, -1, -1 )
		if sceneId == nLairdMapId then
			SetPos(sceneId,selfId,204,202)
		else
			NewWorld(sceneId,selfId,27,204,202, 300930)
		end
	elseif nLairdMapId == 31 then
		TimerCommand( sceneId, selfId, 1, 7010, 3, -1, -1, -1 )
		if sceneId == nLairdMapId then
			SetPos(sceneId,selfId,204,202)
		else
			NewWorld(sceneId,selfId,31,204,202, 300930)
		end
	elseif nLairdMapId == 34 then
		TimerCommand( sceneId, selfId, 1, 7010, 3, -1, -1, -1 )
		if sceneId == nLairdMapId then
			SetPos(sceneId,selfId,204,202)
		else
			NewWorld(sceneId,selfId,34,204,202, 300930)
		end
	end
	
	if impactId ~= -1 then
		SendSpecificImpactToUnit(sceneId, selfId, selfId, selfId, 7720, 0);
	end
end
--**********************************
--���ļ�⼰������ڣ�
--ϵͳ���ڼ������ĵ�ʱ����������ӿڣ���������������ķ���ֵȷ���Ժ�������Ƿ�ִ�С�
--����1�����Ĵ���ͨ�������Լ���ִ�У�����0�����ļ��ʧ�ܣ��жϺ���ִ�С�
--ע�⣺�ⲻ�⸺�����ĵļ��Ҳ�������ĵ�ִ�С�
--**********************************
function x300930_OnDeplete( sceneId, selfId )

	--check guild
	local nGuildID = GetGuildID(sceneId,selfId)
	if nGuildID < 0 then
		return 0
	end

	--check laird map
	local nLairdMap0,nLairdMap1,nLairdMap2 = GetGuildLairdSceneId(nGuildID)
	if nLairdMap0 <= 0 then
		Msg2Player(sceneId,selfId,"�޷�ʹ�ã���û�����",8,3)
		Msg2Player(sceneId,selfId,"Ŀǰ���İ����δռ���κ����",8,2)
		return 0
	end
	
	--OK
	x300930_GuildLairdSceneIdTrans(sceneId, selfId, nLairdMap0)
	--depleting
	DepletingUsedItem(sceneId, selfId)
	return 1;
end

function x300930_OnAddMoney(sceneId, selfId)
end

function x300930_OnAddItemByLevel(sceneId, selfId)	
end

function x300930_OnAddItem(sceneId, selfId, itemId)
end

--**********************************
--ֻ��ִ��һ����ڣ�
--������˲�����ܻ���������ɺ��������ӿڣ������������Ҹ��������������ʱ�򣩣�������
--����Ҳ����������ɺ��������ӿڣ����ܵ�һ��ʼ�����ĳɹ�ִ��֮�󣩡�
--����1������ɹ�������0������ʧ�ܡ�
--ע�������Ǽ�����Чһ�ε����
--**********************************
function x300930_OnActivateOnce( sceneId, selfId, impactId )	
end

--**********************************
--��������������ڣ�
--�������ܻ���ÿ����������ʱ��������ӿڡ�
--���أ�1�����´�������0���ж�������
--ע�������Ǽ�����Чһ�ε����
--**********************************
function x300930_OnActivateEachTick( sceneId, selfId)
	return 1; --���������Խű�, ֻ�����պ���.
end
