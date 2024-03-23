--VIP�±����
------------------------------------------------------------------------------------------
--һ����Ʒ��Ĭ�Ͻű�

--�ű���

x404890_g_scriptId = 404890
x404890_g_ItemList = {}
x404890_g_LevelMin = 30
--��Ҫ�ĵȼ�


--**********************************
--�¼��������
--**********************************
function x404890_ProcEventEntry( sceneId, selfId, bagIndex )
-- ����Ҫ����ӿڣ���Ҫ�����պ���
end

--**********************************
--�����Ʒ��ʹ�ù����Ƿ������ڼ��ܣ�
--ϵͳ����ִ�п�ʼʱ�����������ķ���ֵ���������ʧ������Ժ�������Ƽ��ܵ�ִ�С�
--����1���������Ƶ���Ʒ�����Լ������Ƽ��ܵ�ִ�У�����0�����Ժ���Ĳ�����
--**********************************
function x404890_IsSkillLikeScript( sceneId, selfId)
	return 1; --����ű���Ҫ����֧��
end

--**********************************
--ֱ��ȡ��Ч����
--ϵͳ��ֱ�ӵ�������ӿڣ���������������ķ���ֵȷ���Ժ�������Ƿ�ִ�С�
--����1���Ѿ�ȡ����ӦЧ��������ִ�к�������������0��û�м�⵽���Ч��������ִ�С�
--**********************************
function x404890_CancelImpacts( sceneId, selfId )
	return 0; --����Ҫ����ӿڣ���Ҫ�����պ���,����ʼ�շ���0��
end

--**********************************
--���������ڣ�
--ϵͳ���ڼ��ܼ���ʱ����������ӿڣ���������������ķ���ֵȷ���Ժ�������Ƿ�ִ�С�
--����1���������ͨ�������Լ���ִ�У�����0���������ʧ�ܣ��жϺ���ִ�С�
--**********************************
function x404890_OnConditionCheck( sceneId, selfId )
	
	--У��ʹ�õ���Ʒ
	
	if(1~=VerifyUsedItem(sceneId, selfId)) then
		return 0
	end

    -- ʱ����
    if GetQuestData( sceneId, selfId, MD_YUEBING_BOX_DATE[ 1], MD_YUEBING_BOX_DATE[ 2], MD_YUEBING_BOX_DATE[ 3] ) == GetDayOfYear() then
        Msg2Player( sceneId, selfId, "���ϴο������ʱ�䲻��һ�죬ʹ��ʧ��", 8, 3)
		return 0
    end

    -- �ȼ����
	if GetLevel(sceneId, selfId)< x404890_g_LevelMin then
        Msg2Player( sceneId, selfId, format( "�ȼ�����#R%d#cffcc00�����޷�ʹ�ô���Ʒ", x404890_g_LevelMin), 8, 3)
		return 0
	end

	-- ��Ч�ڼ��
    local bagIndex = GetBagIndexOfUsedItem( sceneId, selfId)
    local firstTime = GetItemParam( sceneId, selfId, bagIndex, 8, 2)
	local currtime = GetCurrentTime()
	if firstTime ~= 0 and currtime - firstTime > 604800 then -- 604800 = 7 * 86400
		Msg2Player( sceneId, selfId, "�ѹ����������޷�ʹ��", 8, 3)
		return 0
	end

	local itemId =  x404890_Yuebing(sceneId,selfId)	

	BeginAddItem(sceneId)
		if itemId ~= -1 then
			AddBindItem( sceneId,itemId,1 )	
		end	

	local ret = EndAddItem(sceneId,selfId)
	if ret > 0 then
		AddItemListToPlayer(sceneId,selfId)
	else
		Msg2Player( sceneId, selfId, "�����������޷��õ���Ʒ������Ҫ������1�������ռ䣡", 8, 3)
		return 0
	end

	SetQuestData( sceneId, selfId, MD_YUEBING_BOX_DATE[ 1], MD_YUEBING_BOX_DATE[ 2], MD_YUEBING_BOX_DATE[ 3], GetDayOfYear() )

	return 1; --����Ҫ�κ�����������ʼ�շ���1��
end

--**********************************
--���ļ�⼰������ڣ�
--ϵͳ���ڼ������ĵ�ʱ����������ӿڣ���������������ķ���ֵȷ���Ժ�������Ƿ�ִ�С�
--����1�����Ĵ���ͨ�������Լ���ִ�У�����0�����ļ��ʧ�ܣ��жϺ���ִ�С�
--ע�⣺�ⲻ�⸺�����ĵļ��Ҳ�������ĵ�ִ�С�
--**********************************
function x404890_OnDeplete( sceneId, selfId)
    local bagIndex = GetBagIndexOfUsedItem( sceneId, selfId)
    local curTimes = GetBagItemMultTimes( sceneId, selfId, bagIndex)
    local result = 1

    -- ��¼��һ��ʹ��ʱ��
    if curTimes == 7 then
        SetItemParam( sceneId, selfId, bagIndex, 8, 2, GetCurrentTime() )
    end

    if curTimes <= 1 then
        -- delete item
        DelItemByIndexInBag( sceneId, selfId, bagIndex, 1)
    else
        -- decrease useful times
        SetBagItemMultTimes( sceneId, selfId, bagIndex, curTimes - 1)
        result = 0
    end

	return result
end

--**********************************
--ֻ��ִ��һ����ڣ�
--������˲�����ܻ���������ɺ��������ӿڣ������������Ҹ��������������ʱ�򣩣�������
--����Ҳ����������ɺ��������ӿڣ����ܵ�һ��ʼ�����ĳɹ�ִ��֮�󣩡�
--����1������ɹ�������0������ʧ�ܡ�
--ע�������Ǽ�����Чһ�ε����
--**********************************
function x404890_OnActivateOnce( sceneId, selfId, impactId )

end

--**********************************
--��������������ڣ�
--�������ܻ���ÿ����������ʱ��������ӿڡ�
--���أ�1�����´�������0���ж�������
--ע�������Ǽ�����Чһ�ε����
--**********************************
function x404890_OnActivateEachTick( sceneId, selfId)
	return 1; --���������Խű�, ֻ�����պ���.
end

function x404890_Yuebing(sceneId,selfId)
	
	local nLevel = GetLevel(sceneId,selfId)
	local yuebing = -1
	if nLevel < 40  then
		yuebing = 12030251
	elseif nLevel >=40 and nLevel < 50 then
		yuebing = 12030252
	elseif nLevel >=50 and nLevel < 60 then	
		yuebing = 12030253
	elseif nLevel >=60 and nLevel < 70 then
		yuebing = 12030254
	elseif nLevel >=70 and nLevel < 80 then
		yuebing = 12030255
	elseif nLevel >=80 and nLevel < 90 then
		yuebing = 12030256
	elseif nLevel >=90 then
		yuebing = 12030257	
	end
	
	return yuebing

end

--**********************************
--��������������ڣ�
--�������ܻ���ÿ����������ʱ��������ӿڡ�
--���أ�1�����´�������0���ж�������
--ע�������Ǽ�����Чһ�ε����
--**********************************
function x404890_OnActivateEachTick( sceneId, selfId)
	return 1; --���������Խű�, ֻ�����պ���.
end

