--�̻� ����
------------------------------------------------------------------------------------------
--һ����Ʒ��Ĭ�Ͻű�

--�ű���

x300808_g_scriptId = 300808

--12031032

x300808_g_AvaliableScene = {50,150,250,350,
51,151,251,351,
58,158,258,358,
86,186,286,386,
0,3,
}

x300808_g_DayLimited = 5

x300808_g_UseTime					=	{                       --��ʹ��ʱ���
											{min=0*60+0,  max=23*60+57},
										}

x300808_g_nValidMinute = 2   --�������ٷ��ӣ�
--��Ҫ�ĵȼ�


--**********************************
--�¼��������
--**********************************
function x300808_ProcEventEntry( sceneId, selfId, bagIndex )
-- ����Ҫ����ӿڣ���Ҫ�����պ���
end

--**********************************
--�����Ʒ��ʹ�ù����Ƿ������ڼ��ܣ�
--ϵͳ����ִ�п�ʼʱ�����������ķ���ֵ���������ʧ������Ժ�������Ƽ��ܵ�ִ�С�
--����1���������Ƶ���Ʒ�����Լ������Ƽ��ܵ�ִ�У�����0�����Ժ���Ĳ�����
--**********************************
function x300808_IsSkillLikeScript( sceneId, selfId)
	return 1; --����ű���Ҫ����֧��
end

--**********************************
--ֱ��ȡ��Ч����
--ϵͳ��ֱ�ӵ�������ӿڣ���������������ķ���ֵȷ���Ժ�������Ƿ�ִ�С�
--����1���Ѿ�ȡ����ӦЧ��������ִ�к�������������0��û�м�⵽���Ч��������ִ�С�
--**********************************
function x300808_CancelImpacts( sceneId, selfId )
	return 0; --����Ҫ����ӿڣ���Ҫ�����պ���,����ʼ�շ���0��
end

--**********************************
--���������ڣ�
--ϵͳ���ڼ��ܼ���ʱ����������ӿڣ���������������ķ���ֵȷ���Ժ�������Ƿ�ִ�С�
--����1���������ͨ�������Լ���ִ�У�����0���������ʧ�ܣ��жϺ���ִ�С�
--**********************************
function x300808_OnConditionCheck( sceneId, selfId )
	
	--У��ʹ�õ���Ʒ
	--PrintStr("x300808_OnConditionCheck")
    if IsKing(sceneId, selfId) <= 0  then
    	
		x300808_ShowTips(sceneId, selfId, "ֻ�й�������ʹ�ù����ټ���!");
		
		return 0
    end

	--if x300808_CheckIsInZhaoJi(sceneId, selfId)>0 then
	--	x300808_ShowTips(sceneId, selfId, "�����ټ��ڼ䣬������ʹ�ã��������������");
	--	
	--	return 0
	--end

	if x300808_IsAvaliableScene(sceneId) <= 0  then
    	
		x300808_ShowTips(sceneId, selfId, "�ܱ�Ǹ������ͼ�޷�ʹ��");
		
		return 0
    end

	if x300808_CheckTime(sceneId, selfId)<=0 then
		x300808_ShowTips(sceneId, selfId, "�ܱ�Ǹ������ʱ�䲻�����ټ���");
		
		return 0
	end

	if x300808_GetDayCount(sceneId, selfId)>= x300808_g_DayLimited then
		x300808_ShowTips(sceneId, selfId, format("�ܱ�Ǹ��ÿ��ֻ��ʹ��%d�ι����ټ���",x300808_g_DayLimited));
		
		return 0
	end
	
	if(1~=VerifyUsedItem(sceneId, selfId)) then
		return 0
	end
	return 1; --����Ҫ�κ�����������ʼ�շ���1��
end


function x300808_IsAvaliableScene(sceneId)
	for i, item in x300808_g_AvaliableScene do
		if item == sceneId then
			return 1
		end
	end

	return 0
end

function x300808_CheckTime(sceneId, selfId)
	

	local hour,minute,sec =GetHourMinSec();

	local nowtime = hour*60+minute
	

	
	for i, item in x300808_g_UseTime do
		if nowtime >= item.min and nowtime <= item.max then
			
			
			return 1;
			
		end
	end

	return 0;
end


function x300808_CheckIsInZhaoJi(sceneId, selfId)
	local nCountry = GetCurCountry(sceneId, selfId)
	local today = GetDayOfYear()

	local lastday = GetCountryParam(sceneId, nCountry, CD_INDEX_ZHAOJILIN_DATE)

	if lastday == today then
		
		local lastMinute = GetCountryParam(sceneId, nCountry, CD_INDEX_ZHAOJILIN_TIME)

		local hour,minute,sec =GetHourMinSec();
		local nowtime = hour*60+minute

		if (nowtime-lastMinute)>= x300808_g_nValidMinute then
			return 0
		else
			return 1
		end

	else
		return 0
	end
end

function x300808_CheckIsOffical(sceneId, selfId)
	local officalIdList = {2,3,4,5,6,7}

	for i,officalId in officalIdList do
		if IsSpecialCountryOffical(sceneId, selfId,officalId)>0 then
			return 1
		end
	end

	return 0
end

function x300808_CheckIsBangZhu(sceneId, selfId)
	local pos = GetGuildOfficial(sceneId, selfId)
	--PrintNum(pos)
	if pos ~= 5 then --���ǰ���
				return -1
	end
	return 1
end

function x300808_CheckCommonCondition(sceneId, selfId)
	if IsPlayerStateNormal(sceneId,selfId )<=0 then
		return 0
	end

	if IsPlayerMutexState(sceneId,selfId,PLAYER_STATE_MENTALGAME )>0 then
		x300808_ShowTips(sceneId, selfId, "���ڴ���״̬��������Ӧ�ټ�");
		return 0
	end

	if IsPlayerMutexState(sceneId,selfId,PLAYER_STATE_STALL )>0 then
		x300808_ShowTips(sceneId, selfId, "���ڰ�̯״̬��������Ӧ�ټ�");
		return 0
	end

	if IsPlayerMutexState(sceneId,selfId,PLAYER_STATE_DIE )>0 then
		x300808_ShowTips(sceneId, selfId, "��������״̬��������Ӧ�ټ�");
		return 0
	end

	if IsPlayerMutexState(sceneId,selfId,PLAYER_STATE_CRASHBOX )>0 then
		x300808_ShowTips(sceneId, selfId, "��������״̬��������Ӧ�ټ�");
		return 0
	end

	if IsPlayerMutexState(sceneId,selfId,PLAYER_STATE_BUS )>0 then
		x300808_ShowTips(sceneId, selfId, "����BUS״̬��������Ӧ�ټ�");
		return 0
	end

	if IsPlayerMutexState(sceneId,selfId,PLAYER_STATE_ENJAIL )>0 then
		x300808_ShowTips(sceneId, selfId, "���ڼ��״̬��������Ӧ�ټ�");
		return 0
	end

	if IsPlayerMutexState(sceneId,selfId,PLAYER_STATE_WEDDING )>0 then
		x300808_ShowTips(sceneId, selfId, "���ڻ���״̬��������Ӧ�ټ�");
		return 0
	end

	if IsPlayerMutexState(sceneId,selfId,PLAYER_STATE_TONGQUBUFF )>0 then
		x300808_ShowTips(sceneId, selfId, "����ͯȤ״̬��������Ӧ�ټ�");
		return 0
	end

	if IsPlayerMutexState(sceneId,selfId,PLAYER_STATE_TIESAN )>0 then
		x300808_ShowTips(sceneId, selfId, "������������״̬��������Ӧ�ټ�");
		return 0
	end

	return 1
end

function x300808_GetTargetScene(sceneId, selfId)
	local nCountry = GetCurCountry(sceneId, selfId)
	local targetScene = GetCountryParam(sceneId, nCountry, CD_ZHAOJILIN_SCENE)

	local x = GetCountryParam(sceneId, nCountry, CD_ZHAOJILIN_POS_X)
	local z = GetCountryParam(sceneId, nCountry, CD_ZHAOJILIN_POS_Z)

	return targetScene,x,z
end


function x300808_CheckSceneLevel(sceneId, selfId,targetScene)
	local nLevel = GetLevel(sceneId, selfId)
	if nLevel<40 then
		x300808_ShowTips(sceneId, selfId, "�ȼ����㣬���ܴ��͵��������ڳ���");
		return 0
	end

	return 1
end

function x300808_CheckAgreeZhaoJi(sceneId, selfId)
	
	if x300808_CheckCommonCondition(sceneId, selfId)<=0 then
		return 0
	end

	if x300808_CheckIsOffical(sceneId, selfId)<=0 and x300808_CheckIsBangZhu(sceneId, selfId) <= 0 then
		x300808_ShowTips(sceneId, selfId, "ֻ�й��ҹ�Ա���߱����İ���������Ӧ�ټ�");
		
		return 0
	end
	
	if x300808_CheckIsInZhaoJi(sceneId, selfId)<=0 then
		x300808_ShowTips(sceneId, selfId, "��Чʱ���ѹ���������Ӧ�ټ�");
		
		return 0
	end

	

	if x300808_IsAvaliableScene(sceneId) <= 0  then
    	
		x300808_ShowTips(sceneId, selfId, "�����ڵĳ���������Ӧ�ټ�");
		
		return 0
    end

	return 1
end




--**********************************
--���ļ�⼰������ڣ�
--ϵͳ���ڼ������ĵ�ʱ����������ӿڣ���������������ķ���ֵȷ���Ժ�������Ƿ�ִ�С�
--����1�����Ĵ���ͨ�������Լ���ִ�У�����0�����ļ��ʧ�ܣ��жϺ���ִ�С�
--ע�⣺�ⲻ�⸺�����ĵļ��Ҳ�������ĵ�ִ�С�
--**********************************
function x300808_OnDeplete( sceneId, selfId )
	return 1;
end

--**********************************
--ֻ��ִ��һ����ڣ�
--������˲�����ܻ���������ɺ��������ӿڣ������������Ҹ��������������ʱ�򣩣�������
--����Ҳ����������ɺ��������ӿڣ����ܵ�һ��ʼ�����ĳɹ�ִ��֮�󣩡�
--����1������ɹ�������0������ʧ�ܡ�
--ע�������Ǽ�����Чһ�ε����
--**********************************
function x300808_OnActivateOnce( sceneId, selfId, impactId )
	if(DepletingUsedItem(sceneId, selfId)) == 1 then
		--SendSpecificImpactToUnit(sceneId, selfId, selfId, selfId,8348, 0);
		
		local nCountry = GetCurCountry(sceneId, selfId)
		--���ÿ�ʼ�ټ���ʱ��
		local hour,minute,sec =GetHourMinSec();
		local nowtime = hour*60+minute
		SetCountryParam(sceneId, nCountry, CD_INDEX_ZHAOJILIN_TIME, nowtime)
		
		--���泡��������
		local x,z =GetWorldPos(sceneId,selfId)
		SetCountryParam(sceneId, nCountry, CD_ZHAOJILIN_SCENE, sceneId)
		SetCountryParam(sceneId, nCountry, CD_ZHAOJILIN_POS_X, x)
		SetCountryParam(sceneId, nCountry, CD_ZHAOJILIN_POS_Z, z)

		CountryZhaoJi(sceneId, selfId)
		x300808_SetDayCount(sceneId, selfId);

		x300808_ShowTips(sceneId, selfId, "�����ټ����ѷ���");
		local msg = format("x300808_OnActivateOnce ��ʼ�����ټ�, guid=%x, name=%s, sceneId=%d, x=%d, z=%d, country=%d",GetPlayerGUID( sceneId,selfId ), GetName(sceneId,selfId ),sceneId,x,z,nCountry)

		WriteLog(1,msg)
	end
end	

--**********************************
--��������������ڣ�
--�������ܻ���ÿ����������ʱ��������ӿڡ�
--���أ�1�����´�������0���ж�������
--ע�������Ǽ�����Чһ�ε����
--**********************************
function x300808_OnActivateEachTick( sceneId, selfId)
	return 1; --���������Խű�, ֻ�����պ���.
end

function x300808_ShowTips(sceneId, selfId, str)
	BeginQuestEvent(sceneId);
		AddQuestText(sceneId,str);
	EndQuestEvent();
	DispatchQuestTips(sceneId, selfId);
end

---------------------------------------------------------------------------------------------------
--ȡ�õ�ǰ����
---------------------------------------------------------------------------------------------------
function x300808_GetDayCount(sceneId, selfId)
	local nCountry = GetCurCountry(sceneId, selfId)

	local today = GetDayOfYear()
	local lastday = GetCountryParam(sceneId, nCountry, CD_INDEX_ZHAOJILIN_DATE)
	
	
	if lastday ~= today then
		return 0
	end

	local daycount = GetCountryParam(sceneId, nCountry, CD_INDEX_ZHAOJILIN_DAYCOUNT)
	print(daycount)
	return daycount;
end

---------------------------------------------------------------------------------------------------
--���õ������
---------------------------------------------------------------------------------------------------
function x300808_SetDayCount(sceneId, selfId)
	local nCountry = GetCurCountry(sceneId, selfId)

	local today = GetDayOfYear()

	local lastday = GetCountryParam(sceneId, nCountry, CD_INDEX_ZHAOJILIN_DATE)

	if lastday ~= today then
		SetCountryParam(sceneId, nCountry, CD_INDEX_ZHAOJILIN_DATE, today)
		SetCountryParam(sceneId, nCountry, CD_INDEX_ZHAOJILIN_DAYCOUNT, 1)
	else
		local daycount = GetCountryParam(sceneId, nCountry, CD_INDEX_ZHAOJILIN_DAYCOUNT)
		SetCountryParam(sceneId, nCountry, CD_INDEX_ZHAOJILIN_DAYCOUNT, daycount+1)
	end
end


function x300808_OnAgreeZhaoJi(sceneId, selfId)
	if x300808_CheckAgreeZhaoJi(sceneId, selfId)<=0 then
		return
	end
	
	local targetScene,x,z = x300808_GetTargetScene(sceneId, selfId)

	if x300808_CheckSceneLevel(sceneId, selfId,targetScene)<=0 then
		return
	end

	x = x+random(-5,5)

	z = z+random(-5,5)
	
	if sceneId == targetScene then
		SetPos( sceneId, selfId,x,z)
	else
		if CallScriptFunction(COUNTRY_BATTLE_LITE_SCRIPT,"CheckCountryBattleLiteSceneTrans",sceneId,selfId,Map_ID) == 0 then
			return
		end
		NewWorld(sceneId, selfId, targetScene, x, z, x300808_g_scriptId);
	end
	
	x300808_ShowTips(sceneId, selfId, "����Ӧ�˹����ټ���");

	local nCountry = GetCurCountry(sceneId, selfId)
	local msg = format("x300808_OnAgreeZhaoJi ok, guid=%x, name=%s, sceneId=%d, targetScene=%d, x=%d, z=%d, country=%d",GetPlayerGUID( sceneId,selfId ), GetName(sceneId,selfId ),sceneId,targetScene,x,z,nCountry)

	WriteLog(1,msg)

end
