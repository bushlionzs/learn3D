
------------------------------------------------------------------------------------------
--һ����Ʒ��Ĭ�Ͻű�

--�ű���

x418115_g_scriptId 		= 418115 

x418115_g_LevelMin		=	-1
--��Ҫ�ĵȼ�


--**********************************
--�¼��������
--**********************************
function x418115_ProcEventEntry( sceneId, selfId, bagIndex )
-- ����Ҫ����ӿڣ���Ҫ�����պ���
end

--**********************************
--�����Ʒ��ʹ�ù����Ƿ������ڼ��ܣ�
--ϵͳ����ִ�п�ʼʱ�����������ķ���ֵ���������ʧ������Ժ�������Ƽ��ܵ�ִ�С�
--����1���������Ƶ���Ʒ�����Լ������Ƽ��ܵ�ִ�У�����0�����Ժ���Ĳ�����
--**********************************
function x418115_IsSkillLikeScript( sceneId, selfId)
	return 1; --����ű���Ҫ����֧��
end

--**********************************
--ֱ��ȡ��Ч����
--ϵͳ��ֱ�ӵ�������ӿڣ���������������ķ���ֵȷ���Ժ�������Ƿ�ִ�С�
--����1���Ѿ�ȡ����ӦЧ��������ִ�к�������������0��û�м�⵽���Ч��������ִ�С�
--**********************************
function x418115_CancelImpacts( sceneId, selfId )
	return 0; --����Ҫ����ӿڣ���Ҫ�����պ���,����ʼ�շ���0��
end

--**********************************
--���������ڣ�
--ϵͳ���ڼ��ܼ���ʱ����������ӿڣ���������������ķ���ֵȷ���Ժ�������Ƿ�ִ�С�
--����1���������ͨ�������Լ���ִ�У�����0���������ʧ�ܣ��жϺ���ִ�С�
--**********************************
function x418115_OnConditionCheck( sceneId, selfId )
	
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
function x418115_OnDeplete( sceneId, selfId )

		if x418115_IsOneWeekPassed(sceneId, selfId)<=0 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,format("#Y����#R%d#Y��ſ��ٴ�ʹ��",x418115_GetNextOpenDays(sceneId, selfId)))
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
			return
		end
	
    local bagIndex = GetBagIndexOfUsedItem( sceneId, selfId)
    local curTimes = GetBagItemMultTimes( sceneId, selfId, bagIndex)
    local result = 1

    if curTimes <= 1 then
        -- delete item
        DelItemByIndexInBag( sceneId, selfId, bagIndex, 1)
        
        x418115_GiveBonus( sceneId,selfId)
    else
        -- decrease useful times
        SetBagItemMultTimes( sceneId, selfId, bagIndex, curTimes - 1)
        result = 0
        x418115_GiveBonus( sceneId,selfId)
    end

	return result
end

--**********************************
--������
--**********************************
function x418115_GiveBonus( sceneId,selfId)
	
	if x418115_IsOneWeekPassed(sceneId, selfId)<=0 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,format("����#R%d#Y��ſ��ٴ�ʹ��",x418115_GetNextOpenDays(sceneId, selfId)))
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return
	end
	
	local nMoney = 200*1000
	AddMoney(sceneId, selfId, 3, nMoney)
	
	x418115_SaveDoTime(sceneId, selfId)
	GamePlayScriptLog( sceneId, selfId, 1931)
	
	local str = format("�����#{_MONEY%d}�𿨵Ľ�����", nMoney)
	Msg2Player(sceneId,selfId,str,8,2)
	Msg2Player(sceneId,selfId,str,8,3)	
	
end

--**********************************
--ֻ��ִ��һ����ڣ�
--������˲�����ܻ���������ɺ��������ӿڣ������������Ҹ��������������ʱ�򣩣�������
--����Ҳ����������ɺ��������ӿڣ����ܵ�һ��ʼ�����ĳɹ�ִ��֮�󣩡�
--����1������ɹ�������0������ʧ�ܡ�
--ע�������Ǽ�����Чһ�ε����
--**********************************
function x418115_OnActivateOnce( sceneId, selfId, impactId )

end

--**********************************
--��������������ڣ�
--�������ܻ���ÿ����������ʱ��������ӿڡ�
--���أ�1�����´�������0���ж�������
--ע�������Ǽ�����Чһ�ε����
--**********************************
function x418115_OnActivateEachTick( sceneId, selfId)
	return 1; --���������Խű�, ֻ�����պ���.
end


---------------------------------------------------------------------------------------------------
--�ж�ʱ����û�е�
---------------------------------------------------------------------------------------------------
function x418115_IsOneWeekPassed(sceneId, selfId)

	
	local nowtime = GetCurrentTime();

	local lasttime = GetQuestData(sceneId, selfId, MD_HANLEJUBAOPEN_DAY[1], MD_HANLEJUBAOPEN_DAY[2],MD_HANLEJUBAOPEN_DAY[3] );
	
	nowtime = format("%u", nowtime)	
	lasttime = format("%u", lasttime)
	if (nowtime-lasttime)>=30*24*3600 then
		return 1;
	else
		return 0;
	end

	
	

end

---------------------------------------------------------------------------------------------------
--����do ��ʱ��
---------------------------------------------------------------------------------------------------
function x418115_SaveDoTime(sceneId, selfId)

	local nowtime = GetCurrentTime();
	SetQuestData(sceneId, selfId, MD_HANLEJUBAOPEN_DAY[1], MD_HANLEJUBAOPEN_DAY[2], MD_HANLEJUBAOPEN_DAY[3], nowtime)
	
	
	
end

---------------------------------------------------------------------------------------------------
--�ж�ʱ����û�е�
---------------------------------------------------------------------------------------------------
function x418115_GetNextOpenDays(sceneId, selfId)

	
	local nowtime = GetCurrentTime();

	local lasttime = GetQuestData(sceneId, selfId, MD_HANLEJUBAOPEN_DAY[1], MD_HANLEJUBAOPEN_DAY[2],MD_HANLEJUBAOPEN_DAY[3] );
	
	nowtime = format("%u", nowtime)	
	lasttime = format("%u", lasttime)
	local Days = (nowtime-lasttime)/(24*3600)
	Days = 31 - Days  
	return Days

end