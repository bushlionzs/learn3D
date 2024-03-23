--�ռ�ս�� add by ������081227��


x300516_g_ScriptId = 300516
x300516_g_MissionName = "�����ˡ���������"
-- �����������ı�
x300516_g_strMissionSubmitContent = "\t�㲶׽����Ҫ��������"
x300516_g_strWrongHorse = "\t�ⲻ����Ҫ����"
x300516_g_strGoodHorse = "\t����һƥǧ���ѷ���������У������Ҫ��������������"
x300516_g_strNormalHorse = "\t��л��������ṩս�������Ҫ��������������"

-- ��������ID
x300516_g_CollectHorse_Mission_ID	= 6430
x300516_g_CollectHorse_Mission_ID_End   = 6446
x300516_g_CollectHorse_Young		= 6445
-- �ύ���Ƿ�����������
x300516_g_IsGoodHorse = 2
-- ���ύ���GUID��32λ(UINT)
x300516_g_CommitedHorseID_HIGH = 4
-- ���ύ���GUID��32λ(UINT)
x300516_g_CommitedHorseID_LOW = 5
--ÿ��ѭ���Ļ���
x300516_OneRoundCount = 10
--ÿ�ո߽�����
x300516_HighBonusCircleCount = 10
x300516_LevelToCapital = 300	--������Ŀ�ʼ�ȼ�
-- ��ʾ�����Ϣ
function x300516_OnCanCompleteMission ( sceneId, selfId, targetId, MissionId )

	local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId)
	
		BeginQuestEvent( sceneId)
		--��������
			AddQuestText(sceneId, "#Y"..x300516_g_MissionName)
			AddQuestText( sceneId, x300516_g_strMissionSubmitContent)
		EndQuestEvent()
		DispatchQuestEventList( sceneId, selfId, targetId)

	    -- ֪ͨ�ͻ�����ʾ�����б���
		BeginUICommand( sceneId);
			UICommand_AddInt( sceneId, x300516_g_ScriptId);
			UICommand_AddInt( sceneId, MissionId);
			UICommand_AddInt( sceneId, targetId);
			DispatchUICommand( sceneId, selfId, 101);
		EndUICommand( sceneId)
		
		return 0
end

-- �����ύ�ĳ���ID�ж��Ƿ��������Ҫ�󣬲����Ϸ���0�����������ɱ��,����,�رճ����б����,���ط�0ֵ
-- ������
--  sceneId������ID
--  selfId�����ID
--  horseTypeID����˵�����ID
--  targetId��NPC��id
--  horseGUID_high����˵�guid�ĸ�32λ��ֵ
--  horseGUID_low����˵�guid�ĵ�32λ��ֵ
--  Reserve1������
function x300516_OnCommitPet( sceneId, selfId, MissionId, targetId, horseGUID_high, horseGUID_low, iHorseIndex)

	--���������������id
	if (x300516_IsCollectHorse(MissionId) == 0) then
		return 0
	end

	local curMissionId = x300516_GetMD(sceneId, selfId, MD_GUOJIARENWU_RANDMISSIONID)
	--�����ǰû�н��������
	if (MissionId ~= curMissionId) then
		return 0
	end

	local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )

	local horseTypeID = GetHorseDataID( sceneId, selfId, iHorseIndex )

	if (x300516_IsNeededHorse(MissionId, horseTypeID) == 0) then
		--�ⲻ����Ҫ����
		BeginQuestEvent( sceneId)
		--��������
			AddQuestText(sceneId, "#Y"..x300516_g_MissionName)
			AddQuestText( sceneId, x300516_g_strWrongHorse)
		EndQuestEvent()
		DispatchQuestEventList( sceneId, selfId, targetId)
		return 0
	end

	local bIsGood = 1
	local kindtype = mod(horseTypeID, 10)
	if (kindtype == 1) then
		bIsGood = 0
	end

	SetQuestByIndex( sceneId, selfId, misIndex, x300516_g_IsGoodHorse, bIsGood)
	--ѡ������ȷ����
	--�������ID
	SetQuestByIndex( sceneId, selfId, misIndex, x300516_g_CommitedHorseID_HIGH, horseGUID_high)
	SetQuestByIndex( sceneId, selfId, misIndex, x300516_g_CommitedHorseID_LOW, horseGUID_low)
	
	BeginQuestEvent(sceneId);
	--��������
	AddQuestText(sceneId, "#Y"..x300516_g_MissionName)
	local str
	if(bIsGood == 0) then
		str = x300516_g_strNormalHorse
	else
		str = x300516_g_strGoodHorse
	end
	AddQuestText( sceneId, str)

	local curlevel = GetLevel(sceneId, selfId)
	local exp = x300516_GetExpAward ( sceneId, selfId, curlevel );
	local money,shengw = x300516_GetMoneyAward ( sceneId, selfId, curlevel );
	if bIsGood == 1 then
		exp = exp * 2
		money = money * 2
		shengw = shengw * 2
	end
	if(exp > 0) then
		AddQuestExpBonus(sceneId, exp)
	end
	if(money > 0) then
		AddQuestMoneyBonus2(sceneId, money)
	end
	if(shengw > 0) then
		AddQuestMoneyBonus5(sceneId, shengw)
	end
	EndQuestEvent();

	DispatchQuestContinueInfoNM( sceneId, selfId, targetId, x300516_g_ScriptId, MissionId )
	return 1
end

--function x300516_ProcQuestAccept( sceneId, selfId, targetId, MissionId )
function x300516_HorseSubmit( sceneId, selfId, MissionId )
	local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId)
	--ȡ�����ID
	local horseGUID_high = GetQuestParam( sceneId, selfId, misIndex, x300516_g_CommitedHorseID_HIGH)
	local horseGUID_low = GetQuestParam( sceneId, selfId, misIndex, x300516_g_CommitedHorseID_LOW)
	-- ����
	local ret = FreeHorse( sceneId, selfId, horseGUID_high, horseGUID_low)
	if (ret <= 0) then
		local strErr
		if (ret == 0) then
			strErr = "��������������ܽ���"
		elseif (ret == -2) then
			strErr = "������ڳ�ս״̬�����ܽ���"
		else
			strErr = "����ѡ�����˲�������"
		end
		Msg2Player(sceneId, selfId, strErr, 8, 3)	
		Msg2Player(sceneId, selfId, strErr, 8, 2)
		return 0, 0
	end

	local bGoodHorse = GetQuestParam( sceneId, selfId, misIndex, x300516_g_IsGoodHorse)
	local awardrate
	if(bGoodHorse == 1) then
		awardrate =  2
	else
		awardrate = 1
	end

	--�������
--	CallScriptFunction (300501, "MissionSubmited", sceneId, selfId, targetId, MissionId )

	-- �رտͻ��˳����б���
	BeginUICommand( sceneId)
		DispatchUICommand( sceneId, selfId, 102)
	EndUICommand( sceneId)

	-- ����������ɱ��
	--SetQuestByIndex( sceneId, selfId, misIndex, x300516_g_MissionFinished, 1)
	return 1, awardrate
end

--���齱��
function x300516_GetExpAward(sceneId, selfId, startlevel)

	x300516_CheckDayChanged(sceneId, selfId)
	local circle = x300516_GetMD(sceneId, selfId, MD_GUOJIARENWU_CIRCLE)
	local highcircle = x300516_GetMD(sceneId, selfId, MD_GUOJIARENWU_HIGH)
	
	circle = circle + 1
	if (circle > x300516_OneRoundCount) then
		circle = 1
	end

	highcircle = highcircle + 1

	local exp_rate
	if GetLevel(sceneId, selfId) >= 60 then
		exp_rate = 3650
	else
		exp_rate = 2800
	end

	local BonusExp = startlevel * exp_rate * (circle * 2 - 1) / 200
	if (highcircle <= x300516_HighBonusCircleCount) then
		BonusExp = BonusExp * 5
	end
    -- �������룬���Ծ��鷭��
    BonusExp = BonusExp * 2
	return BonusExp;

end

--��Ǯ����
function x300516_GetMoneyAward(sceneId, selfId, startlevel)

	x300516_CheckDayChanged(sceneId, selfId)
	local circle = x300516_GetMD(sceneId, selfId, MD_GUOJIARENWU_CIRCLE)
	local highcircle = x300516_GetMD(sceneId, selfId, MD_GUOJIARENWU_HIGH)

	circle = circle + 1
	if (circle > x300516_OneRoundCount) then
		circle = 1
	end

	highcircle = highcircle + 1

	local BonusMoney = startlevel
	local shengw = 5
	if (highcircle <= x300516_HighBonusCircleCount) then
		BonusMoney = BonusMoney * 5
		shengw = 25
	end
	return BonusMoney,shengw;
end

function x300516_SetMD(sceneId, selfId, MDNAME, value)
	SetQuestData(sceneId, selfId, MDNAME[1], MDNAME[2], MDNAME[3], value);
end

function x300516_GetMD(sceneId, selfId, MDNAME)

	return GetQuestData(sceneId, selfId, MDNAME[1], MDNAME[2], MDNAME[3])
end


--���������û�б仯�������ø߽��������������µ�����
function x300516_CheckDayChanged(sceneId, selfId)
	local lastDay = x300516_GetMD(sceneId, selfId, MD_GUOJIARENWU_LASTDAY)
	local today = GetDayOfYear()
	if lastDay ~= today then	--���ڱ仯
		x300516_SetMD(sceneId, selfId, MD_GUOJIARENWU_LASTDAY, today)	
		x300516_SetMD(sceneId, selfId, MD_GUOJIARENWU_HIGH, 0)
	end
end

function x300516_IsNeededHorse(MissionId, horseId)

	if x300516_IsCollectHorse(MissionId) == 0 then
		return 0
	end

	local kindtype = mod(horseId, 10)
	if (MissionId < x300516_g_CollectHorse_Young) then
		if (kindtype >= 5) then
			return 0
		end
		local group = floor(horseId / 100)
		if (group ~= MissionId - x300516_g_CollectHorse_Mission_ID + 2 ) then
			return 0
		end
	else
		if (kindtype > 5) then
			return 0
		end
		local group = floor(horseId / 10)
		if (group > 5) then
			return 0
		end
	end

	return 1
end

--�Ƿ�����������
function x300516_IsCollectHorse(MissionId)
	if MissionId >= x300516_g_CollectHorse_Mission_ID and MissionId <= x300516_g_CollectHorse_Mission_ID_End then
		return 1
	else
		return 0
	end
end





















