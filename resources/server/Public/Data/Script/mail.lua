
--�ű��ʼ��Ľű��ļ�

--�ű���
x888889_g_scriptId = 888889


function x888889_ExecuteMail( sceneId, selfId, param0, param1, param2, param3 )
	param0 = tonumber(format("%u",param0))
	param1 = tonumber(format("%u",param1))
	param2 = tonumber(format("%u",param2))
	param3 = tonumber(format("%u",param3))
	
	if param0 == MAIL_REPUDIATE then
		x888889_Mail_Repudiate( sceneId, selfId, param0, param1, param2, param3 )
	elseif param0 == MAIL_BETRAYMASTER then
		x888889_Mail_BetrayMaster( sceneId, selfId, param0, param1, param2, param3 )
	elseif param0 == MAIL_EXPELPRENTICE then
		x888889_Mail_ExpelPrentice( sceneId, selfId, param0, param1, param2, param3 )
	elseif param0 == MAIL_UPDATE_ATTR then
		UpdateAttr(sceneId, selfId, param0, param1, param2, param3)
	elseif param0 == MAIL_UNSWEAR then
		x888889_Mail_Unswear(sceneId, selfId, param0, param1, param2, param3)
	elseif param0 == MAIL_PRENTICE_EXP then
		x888889_Mail_PrenticeProfExp(sceneId, selfId, param0, param1, param2, param3)
	elseif param0 == MAIL_LEAVE_GUILD then
	 	x888889_Mail_LeaveGuild(sceneId, selfId, param0, param1, param2, param3)  
	elseif param0 == MAIL_GIVE_MONEY then	
		x888889_Mail_GiveMoney(sceneId, selfId, param0, param1, param2, param3)  
	elseif param0 == MAIL_GIVE_ITEM then	
		x888889_Mail_GiveItem(sceneId, selfId, param0, param1, param2, param3) 
	elseif param0 == MAIL_DELETE_MISSION then	
		x888889_Mail_DeleteMission(sceneId, selfId, param0, param1, param2, param3) 
	elseif param0 == MAIL_GIVE_MONEY2MASTER then	
		x888889_Mail_GiveMoney2Master(sceneId, selfId, param0, param1, param2, param3) 
	elseif param0 == MAIL_GIVE_EXP then	
		x888889_Mail_GiveExp(sceneId, selfId, param0, param1, param2, param3) 
	elseif param0 == MAIL_MASTER_AWARD then	
		x888889_Mail_MasterAward(sceneId, selfId, param0, param1, param2, param3) 

	
	end

end

--ͽ�ܸ�ʦ������
function x888889_Mail_PrenticeProfExp( sceneId, selfId, command, PrenticeGuid, Exps, zero )
	--PrenticeGuid����selfId��Exps��ô�ྭ��
	if Exps > 0 then
		LuaAddPrenticeProExp( sceneId, selfId, PrenticeGuid, Exps )
	end
end

function x888889_Mail_Unswear( sceneId, selfId, command, betrayerGuid, alldismiss, zero )

	--(1) ���ͺ��Ѷ�
	local FriendPoint = GetFriendPointByGUID( sceneId, selfId, betrayerGuid )
	if FriendPoint > 500 then
		SetFriendPointByGUID( sceneId, selfId, betrayerGuid, 500 )
	end
	
	--(2) ȡ�����
	Unswear( sceneId, selfId, betrayerGuid )
	
	--(3) ���ȫ����ɢ����ɾ���ƺ�
	if tonumber(alldismiss) == 1 then
		AwardJieBaiTitle( sceneId, selfId, "" )
		DispatchAllTitle( sceneId, selfId )
	end
end

function x888889_Mail_Repudiate( sceneId, selfId, param0, param1, param2, param3 )
	
	local TITLE_MARRY = 4
	
	DeleteTitle(sceneId, selfId, TITLE_MARRY)
	
	local SpouseGUID = GetSpouseGUID( sceneId, selfId )
	if param1 ~= SpouseGUID and SpouseGUID ~= tonumber(format("%u",-1)) then --�Ѿ������Լ�����ż ����Ҫ����
		return
	end
	local spouseName = GetFriendName(sceneId, selfId, SpouseGUID)
	
	if spouseName ~= "" then
		local ret = format("%s��������˷��޹�ϵ��", spouseName)
		Msg2Player(sceneId,selfId,ret,8,2)
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, ret);
		EndQuestEvent();
	end
	
	--ɾ�����״̬��
	Divorce( sceneId, selfId )
	
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

function x888889_Mail_BetrayMaster( sceneId, selfId, param0, param1, param2, param3 )
	--����ͽ��
	local Msg
	local PrenticeName	= GetFriendName( sceneId, selfId, param1 )
	if 0 == param2 then
		--IncreaseFinishPrenticeshipNum(sceneId, selfId)
		--if PrenticeName ~= "" then
			--Msg = format("��ϲ������������ͽ�ܳ�ʦ�ˣ�ϵͳ���������ͽ��%s��ʦͽ��ϵ��", PrenticeName);
			--Msg2Player(sceneId,selfId,Msg,8,2)
		--end
	elseif 1 == param2 and PrenticeName ~= "" then
		Msg = format("���ź�������ͽ��%s�����������ʦͽ��ϵ��", PrenticeName);
		Msg2Player(sceneId,selfId,Msg,8,2)
	elseif 2 == param2 and PrenticeName ~= "" then
		Msg = format("���ź�����������ͽ��3��δ��½��Ϸ��ϵͳ���������ͽ��%s��ʦͽ��ϵ��", PrenticeName);
		Msg2Player(sceneId,selfId,Msg,8,2)
	end
	local isPrentice = 0
	local index = 0
	while index < MAX_PRENTICE_NUM do
		if GetPrenticeGUID(sceneId, selfId, index) == param1 then
			isPrentice = 1
			break
		end
		index = index + 1
	end
	if 0 == isPrentice then --�Ѿ������Լ���ͽ�� ������
		return
	end
	local isFinishPrenticeship = 0 --��ʦ
	if 0 == param2 then
		--isFinishPrenticeship = 1
	end
	ExpelPrentice( sceneId, selfId, param1, isFinishPrenticeship )
end

function x888889_Mail_ExpelPrentice( sceneId, selfId, param0, param1, param2, param3 )
	
	local Msg
	local targetGUID = GetMasterGUID(sceneId, selfId);
	if targetGUID == -1 then
		return
	end
	local MasterName = GetFriendName( sceneId, selfId, targetGUID )
	if 0 == param1 then
		Msg = format("���ź�����������ʦ��3��δ��½��Ϸ��ϵͳ���������ʦ��%s��ʦͽ��ϵ��", MasterName);
		Msg2Player(sceneId,selfId,Msg,8,2)
	elseif 1 == param1 then
		Msg = format("���ź�������ʦ��%s�����������ʦͽ��ϵ��", MasterName);
		Msg2Player(sceneId,selfId,Msg,8,2)
	end

	if targetGUID ~= param2 then -- �����Լ���ǰ��ʦ�� ������
		return
	end
	local TITLE_PRENTICE = 5
	DeleteTitle(sceneId, selfId, TITLE_PRENTICE)
	BetrayMaster( sceneId, selfId )
end

function x888889_Mail_GiveMoney(sceneId, selfId, param0, param1, param2, param3)
	AddMoney(sceneId, selfId, param1, param2)
end

--ͽ�ܳ�ʦ���Ľ���
function x888889_Mail_GiveMoney2Master(sceneId, selfId, param0, param1, param2, param3)
	AddMoney(sceneId, selfId, param1, param2)
end

--�뿪��� 
function x888889_Mail_LeaveGuild( sceneId, selfId, param0, param1, param2, param3 )

	CallScriptFunction( SCENE_SCRIPT_ID, "OnLeaveGuild", sceneId, selfId,0 )
	
end

--�����Ʒ
function x888889_Mail_GiveItem(sceneId, selfId, param0, param1, param2, param3)

	BeginAddItem(sceneId)
	AddItem( sceneId, param1, param2 )
	local ret = EndAddItem(sceneId,selfId)
	if ret > 0 then
		AddItemListToPlayer(sceneId,selfId)
	end
	
end

--������
function x888889_Mail_GiveExp(sceneId, selfId, param0, param1, param2, param3)
	AddExp(sceneId, selfId, param1);
end

function x888889_Mail_SetMissionData(sceneId, selfId)
		SetQuestData(sceneId, selfId, MD_SPOUSE_MISSION_DATE[1][1], MD_SPOUSE_MISSION_DATE[1][2], MD_SPOUSE_MISSION_DATE[1][3], GetDayOfYear())
end

--ɾ������ 
--param1 Ϊ����id 
--param2 Ϊ1---�������ֶ����� 0---�������ķ����� ��������ʱ�䵽�ˡ����� ����������������Ҫ�˲�����
function x888889_Mail_DeleteMission(sceneId, selfId, param0, param1, param2, param3)
	 if 1 == IsHaveQuest(sceneId, selfId, param1) then
	 		if tonumber(param1) == tonumber(SPOUSE_TASK[2]) and tonumber(param2) == tonumber(0) then
				local strText = "����������ż�뿪#G̽�׵�С��#W#W#cEFC800ʱ����ã���ͯ��ʧ�ˣ�����ʧ�ܣ�"
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId, strText);
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				Msg2Player(sceneId,selfId,strText,8,2)
				DelQuestNM( sceneId, selfId, param1 )
				x888889_Mail_SetMissionData(sceneId, selfId)
			elseif tonumber(param1) == tonumber(SPOUSE_TASK[2]) and tonumber(param2) == tonumber(1) then
				local strText = "����������ż�����˷�����������ʧ�ܣ�"
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId, strText);
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				Msg2Player(sceneId,selfId,strText,8,2)
				DelQuestNM( sceneId, selfId, param1 )
				x888889_Mail_SetMissionData(sceneId, selfId)
				local BusID  =  GetBusId(sceneId, selfId)
				if BusID ~= -1 and GetSex(sceneId, selfId) == 1 then
			   	--���BUS������ �еĲŸ�����
					DeleteBus(sceneId, BusID,1)
				end
			
			elseif tonumber(param1) == tonumber(SPOUSE_TASK[1]) or tonumber(param1) == tonumber(SPOUSE_TASK[3]) then
				local strText = "����������ż�����˷�����������ʧ�ܣ�"
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId, strText);
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				Msg2Player(sceneId,selfId,strText,8,2)
				DelQuestNM( sceneId, selfId, param1 )
				x888889_Mail_SetMissionData(sceneId, selfId)
				if tonumber(param1) == tonumber(SPOUSE_TASK[3]) then
					DelItem(sceneId, selfId, SPOUSE_TASK_POSITION_USE_ITEM, 1)
				end
			end
		end
end

--��ʦ������
function x888889_Mail_MasterAward(sceneId, selfId, param0, param1, param2, param3)
	AddExp(sceneId, selfId, param1);

	local value = GetPlayerGoodBadValue(sceneId, selfId)
	value = value + param2
	SetPlayerGoodBadValue(sceneId, selfId, value)

	if param3 == 0 then
		local targetGUID = GetMasterGUID(sceneId, selfId);
		if targetGUID == tonumber(-1) then
			return
		end
		
		local MasterName = GetFriendName( sceneId, selfId, targetGUID )
		if MasterName == "" then
			return
		end
	
		local selfName	= GetName( sceneId, selfId )

		local nExp = param1 * 30 / 100
		local nCachet = param2 * 30 / 100
	
		SendScriptMail( sceneId, MasterName, MAIL_MASTER_AWARD, nExp, nCachet, 1, selfId )
		local szMsg = format("��ϲ��!������ͽ��%s��ͽ���������������%d�㾭���%d�������Ľ�����", selfName,nExp,nCachet)
		--SendNormalMail( sceneId, selfId, MasterName, szMsg )
		SendSystemMail( sceneId, MasterName, szMsg )
	end
end
