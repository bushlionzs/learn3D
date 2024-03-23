--���������
------------------------------------------------------------------------------------------
--һ����Ʒ��Ĭ�Ͻű�

--�ű���

x418197_g_scriptId = 418197
x418197_g_ItemList = {}
x418197_g_LevelMin = 1	
--��Ҫ�ĵȼ�


--**********************************
--�¼��������
--**********************************
function x418197_ProcEventEntry( sceneId, selfId, bagIndex )
-- ����Ҫ����ӿڣ���Ҫ�����պ���
end

--**********************************
--�����Ʒ��ʹ�ù����Ƿ������ڼ��ܣ�
--ϵͳ����ִ�п�ʼʱ�����������ķ���ֵ���������ʧ������Ժ�������Ƽ��ܵ�ִ�С�
--����1���������Ƶ���Ʒ�����Լ������Ƽ��ܵ�ִ�У�����0�����Ժ���Ĳ�����
--**********************************
function x418197_IsSkillLikeScript( sceneId, selfId)
	return 1; --����ű���Ҫ����֧��
end

--**********************************
--ֱ��ȡ��Ч����
--ϵͳ��ֱ�ӵ�������ӿڣ���������������ķ���ֵȷ���Ժ�������Ƿ�ִ�С�
--����1���Ѿ�ȡ����ӦЧ��������ִ�к�������������0��û�м�⵽���Ч��������ִ�С�
--**********************************
function x418197_CancelImpacts( sceneId, selfId )
	return 0; --����Ҫ����ӿڣ���Ҫ�����պ���,����ʼ�շ���0��
end

--**********************************
--���������ڣ�
--ϵͳ���ڼ��ܼ���ʱ����������ӿڣ���������������ķ���ֵȷ���Ժ�������Ƿ�ִ�С�
--����1���������ͨ�������Լ���ִ�У�����0���������ʧ�ܣ��жϺ���ִ�С�
--**********************************
function x418197_OnConditionCheck( sceneId, selfId )
	
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
function x418197_OnDeplete( sceneId, selfId )
	
	
	--if(DepletingUsedItem(sceneId, selfId)) == 1 then
	--	return 1;
	--end
	--return 0;
	
	return 1;
end

--**********************************
--ֻ��ִ��һ����ڣ�
--������˲�����ܻ���������ɺ��������ӿڣ������������Ҹ��������������ʱ�򣩣�������
--����Ҳ����������ɺ��������ӿڣ����ܵ�һ��ʼ�����ĳɹ�ִ��֮�󣩡�
--����1������ɹ�������0������ʧ�ܡ�
--ע�������Ǽ�����Чһ�ε����
--**********************************
function x418197_OnActivateOnce( sceneId, selfId, impactId )
	
	local bagIndex = GetBagIndexOfUsedItem( sceneId, selfId)
	
	local today = GetDayOfYear() 
	local lastday = GetQuestData(sceneId, selfId, MD_ITEM_OTHER_197_DATE[1], MD_ITEM_OTHER_197_DATE[2],MD_ITEM_OTHER_197_DATE[3])
	
	if lastday ~= 0 then
		local daycount = 0
		if today < lastday-1 then
			daycount = today + 366 - lastday
		else
			daycount = today + 1 - lastday
		end
		 
		if daycount < 30 then
			local msg = format("����%d�����ʹ�����������", 30-daycount)
			Msg2Player(sceneId,selfId,msg,8,3)
			Msg2Player(sceneId,selfId,msg,8,2)
			return
		end
	end
	
	SetQuestData(sceneId, selfId, MD_ITEM_OTHER_197_DATE[1], MD_ITEM_OTHER_197_DATE[2], MD_ITEM_OTHER_197_DATE[3], today+1)

    local curTimes = GetBagItemMultTimes( sceneId, selfId, bagIndex)
    SetBagItemMultTimes( sceneId, selfId, bagIndex, curTimes - 1)
	
	if curTimes == 1 then
		BeginAddItem(sceneId)
		EndAddItem(sceneId,selfId)
		DepletingUsedItem(sceneId, selfId)
	end
	
	AddMoney(sceneId, selfId, 3, 2000000, 327)
	Msg2Player(sceneId, selfId, "ʹ����������𿨣����#G2000����#W", 8, 3)
	Msg2Player(sceneId, selfId, "ʹ����������𿨣����#G2000����#W", 8, 2)
	return 1
end

--**********************************
--��������������ڣ�
--�������ܻ���ÿ����������ʱ��������ӿڡ�
--���أ�1�����´�������0���ж�������
--ע�������Ǽ�����Чһ�ε����
--**********************************
function x418197_OnActivateEachTick( sceneId, selfId)
	return 1; --���������Խű�, ֻ�����պ���.
end
