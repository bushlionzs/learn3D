
x800008_g_ScriptId 					= 800008
x800008_g_MissionName				= "����������Ҫ���"
x800008_g_CostMoneyDivorce  = 50000
x800008_g_CostMoneyType  		= 0
x800008_g_FriendPointNotify	= 100
x800008_g_SkillID						= 149
x800008_g_Impact						= 7642

function x800008_DoDivorce(sceneId, selfId, NPCId)

	local ret = x800008_SafeDivorceCheck(sceneId, selfId);
	if ret ~= nil then
		Msg2Player(sceneId,selfId,ret,8,2)
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, ret);
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
		return
	end
	
	if CostMoney(sceneId, selfId, x800008_g_CostMoneyType, x800008_g_CostMoneyDivorce,305) == -1 then
		return
	end
	--�õ���żGUID
	local targetGUId = GetSpouseGUID(sceneId, selfId);
	local spouseName = GetFriendName(sceneId, selfId, targetGUId)
	--����mail���Է�
	local mail = format("%s��������˷��޹�ϵ��",GetName(sceneId, selfId));
	SendSystemMail(sceneId, spouseName, mail);
	
	--����ִ���ʼ�����ż��ִ�����
	SendScriptMail( sceneId, spouseName, MAIL_REPUDIATE, GetGUID(sceneId, selfId), 0, 0, selfId )
	
	ret = format("���������%s�ķ��޹�ϵ��", spouseName)
	Msg2Player(sceneId,selfId,ret,8,2)
	BeginQuestEvent(sceneId);
	AddQuestText(sceneId, ret);
	EndQuestEvent();
	DispatchQuestTips(sceneId, selfId);
		
	--���һ��,���
	Divorce(sceneId, selfId);
	--ɾ����������
	for i , missionId in SPOUSE_TASK do
		if missionId == SPOUSE_TASK[2] and 1 == IsHaveQuest(sceneId, selfId, missionId) and GetSex(sceneId, selfId) == 1 then			
			local BusID  =  GetBusId(sceneId, selfId)
			if BusID ~= -1 then
				DeleteBus(sceneId, BusID,1)
			end
		end
		if missionId == SPOUSE_TASK[3] and 1 == IsHaveQuest(sceneId, selfId, missionId) then
			DelItem(sceneId, selfId, SPOUSE_TASK_POSITION_USE_ITEM, 1)
		end
		if 1 == IsHaveQuest(sceneId, selfId, missionId) then
			DelQuestNM( sceneId, selfId, missionId )
		end
	end
	
end

-------------------------
--***********************
--SafeDivorceCheck
--***********************
-------------------------

function x800008_SafeDivorceCheck(sceneId, selfId)

	if IsMarried(sceneId, selfId) ~= 1 then
		return "��û�н�飬�������ô��"
	end
	
	if GetMoney(sceneId, selfId, x800008_g_CostMoneyType) < x800008_g_CostMoneyDivorce then
		return format("�ܱ�Ǹ���������е����Ӳ���%d���������޷�������顣", tonumber(x800008_g_CostMoneyDivorce/1000))
	end	
	
	if IsHaveSpecificImpact(sceneId, selfId, x800008_g_Impact) == 1 then
		return "�ܱ�Ǹ�������ھ��л����У��������������ֹ��"
	end
		
	return nil
end

-------------------------
--***********************
--ProcEnumEvent
--***********************
-------------------------

function x800008_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
	AddQuestNumText(sceneId, x800008_g_ScriptId, x800008_g_MissionName,3);
end

-------------------------
--***********************
--ProcEventEntry
--***********************
-------------------------

function x800008_ProcEventEntry(sceneId, selfId, targetId)
	
	BeginQuestEvent(sceneId);
		AddQuestText(sceneId, "#Y����������Ҫ���");
		AddQuestText(sceneId, "\tʮ���޵�ͬ���ɣ������޵ù����ߡ�����ϧ���ǵ�Ե�֣������������޷���أ�����#G50������#W�ҿ��԰������������ϵ��#r��ȷ��Ҫ�����");
	EndQuestEvent();
	DispatchQuestInfo(sceneId, selfId, targetId, x800008_g_ScriptId,-1);
	
end

-------------------------
--***********************
--ProcAcceptCheck
--***********************
-------------------------

function x800008_ProcAcceptCheck(sceneId, selfId, targetId)

	return 1;

end

-------------------------
--***********************
--ProcAccept
--***********************
-------------------------

function x800008_ProcAccept(sceneId, selfId, targetId)

	x800008_DoDivorce(sceneId, selfId, targetId);

end