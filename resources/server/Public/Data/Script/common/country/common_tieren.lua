x300703_g_scriptId = 300703  --��������
--MD_TIEREN_ACCEPTTIME = MD_TIEREN_ACCEPTTIME--������ʱ��
--x300703_g_MD_CommitTime = MD_TIEREN_COMMITTIME--������ʱ��
--x300703_g_MD_Abandon = MD_TIEREN_ABANDON	--�Ƿ��������
--x300703_g_MD_Circle =     --��ɻ���
x300703_g_MissionName = "���塿����������"
x300703_g_MissionId = 7538

x300703_g_SubmitNpc = {{0,139100}, {37,139101}, {37,139102}}

x300703_g_MissionTarget = "  ��@npcsp_���ɷ�_139101���μ���������"
x300703_g_MissionTarget1 = "@npc_141544���˶���#G����#W"

x300703_g_AcceptMessage		= "������������:%s"
x300703_g_AbandonMessage	= "������������:%s"
x300703_g_CompleteMessage	= "�����������:%s"

x300703_g_ContinueMissionInfo = 	" \n����������Ŀ�ܲ������Ŀ���򵥵��ܲ���ȴ�����ȫ��õ��˶�������ǿ��������洦��\n"
x300703_g_MissionMiddleCompleted = "\t����������һ�������������Ȥ��һ�����Ŀ����ֻҪ�ҵ��ڶ���@npc_141544��ͣ�ܶ���#G����#W����������������\n\t\������������������У�������������ֲ�ͬģ�������ӣ���������ܻ��úܶ����벻����Ч��Ŷ��\n \n#GС��ʾ#W��\n\t�������#G�ǳ��̵�ʱ��#W����ɽ�������������õ�#R����Ľ���#W��"
x300703_g_MissionCompleted = "\t��ϲ���������������ǵ�����ʵ��ÿ��ҲҪ��һ��ʱ��������壬��ʹ����ӽ������������鵽�˶��Ŀ��֡�"

x300703_g_MissionInfo =  "\t�������ﱨ��������ȥ�μ�����������ı����ˡ�\n#W  ��������ı����ܼ򵥣�ֻҪ�����ҵ�һֱ�ڴ󶼶���@npc_141544���߶��ļ���Ϳ����������\n#Y�����\n#W1.40��������ҲſɲμӴ˻��\n#W2.ÿ��19:30-24:00����ȡ�˻��\n#W3.ÿ��ɽ�ȡһ�δ˻��\n#W4.��ɱ����󽫻��÷������\n#W5.������������������У���������ͬ���ӵ����ӣ���ȥ�����������벻����Ч����"


x300703_g_Missionruse= "\t����������һ�������������Ȥ��һ�����Ŀ����@npcsp_���ɷ�_139101���������ҵ�@npc_141544�ϲ�ͣ�ܶ���#G����#W����������������\n\t\������������������У���������ͬ���ӵ����ӣ���ȥ�����������벻����Ч����"

x300703_g_CompleteInfo		= { day = -1, first = -1, second = -1,third = -1 }

x300703_g_TianfuItems				= {11010100,11010101,11010102}

x300703_g_BackPos = {122,177}

--buff����
x300703_g_ImpactDataIndex_Size = 211
--���ܱ���ɢ��buff�������������ܲ�����buff��˫�������buff
x300703_g_UnDispelImpactDataIndex = {1341,1342,1343,1344,1345,1346,1347,1348,1349,1350,
									 1351,1352,1353,1354,1355,1356,1357,1358,1359,1360,
									 1361,1362,1363,1364,1365,1366,1367,1368,1369,1370,
									 1371,1372,1373,1374,1375,1376,1377,1378,1379,1380,
									 2121,2122,2123,2124,2125,2126,2127,2128,2129,2130,
									 2131,2132,2133,2134,2135,2136,2137,2138,2139,2140,
									 2141,2142,2143,2144,2145,2146,2147,2148,2149,2150,
									 3131,3132,3133,3134,3135,3136,3137,3138,3139,3140,
									 3141,3142,3143,3144,3145,3146,3147,3148,3149,3150,
									 3151,3152,3153,3154,3155,3156,3157,3158,3159,3160,
									 4121,4122,4123,4124,4125,4126,4127,4128,4129,4130,
									 4131,4132,4133,4134,4135,4136,4137,4138,4139,4140,
									 4141,4142,4143,4144,4145,4146,4147,4148,4149,4150,
									 5131,5132,5133,5134,5135,5136,5137,5138,5139,5140,
									 5141,5142,5143,5144,5145,5146,5147,5148,5149,5150,
									 5151,5152,5153,5154,5155,5156,5157,5158,5159,5160,
									 6131,6132,6133,6134,6135,6136,6137,6138,6139,6140,
									 6141,6142,6143,6144,6145,6146,6147,6148,6149,6150,
									 6151,6152,6153,6154,6155,6156,6157,6158,6159,6160,
									 7510,7511,7630,7631,9007,9011,9012,9824,7702,7708,
									 7601,7643, 9013,7646,7647,7648,7649,7650,7709,7710,
									 7711};

x300703_g_StateBuff = {{{7610,7607},{7608,7605}}, {{7616,7613},{7614,7611}}, {{7622,7619},{7620,7617}}, {{7628,7625},{7626,7623}}}
-- �����г�buff
function x300703_SendStateBuff(sceneId, selfId)
	local country = GetCurCountry( sceneId, selfId )
	local sex = GetSex( sceneId, selfId )
	
	local buff = x300703_g_StateBuff[country+1][1][sex+1]
	if IsHaveSpecificImpact( sceneId, selfId, buff ) <= 0 then
		SendSpecificImpactToUnit(sceneId, selfId, selfId, selfId, buff, 0)
	end
	
	buff = x300703_g_StateBuff[country+1][2][sex+1]
	if IsHaveSpecificImpact( sceneId, selfId, buff ) > 0 then
		CancelSpecificImpact(sceneId, selfId, buff)
	end
end

function x300703_CancelStateBuff(sceneId, selfId)
	local country = GetCurCountry( sceneId, selfId )
	local sex = GetSex( sceneId, selfId )
	
	local buff = x300703_g_StateBuff[country+1][1][sex+1]
	
	if IsHaveSpecificImpact( sceneId, selfId, buff ) > 0 then
		CancelSpecificImpact(sceneId, selfId, buff)
	end
	
	buff = x300703_g_StateBuff[country+1][2][sex+1]
	if IsHaveSpecificImpact( sceneId, selfId, buff ) > 0 then
		CancelSpecificImpact(sceneId, selfId, buff)
	end
end

function x300703_AddLog(sceneId, selfId, sign, MissionId)
	 --����д��־
	local gameId=0;
	if sign == 1 then
		gameId = 411
	else
		gameId = 412
	end

	GamePlayScriptLog(sceneId, selfId, gameId)
end

function x300703_AwardTitle( sceneId,selfId )
	


	--���������ںͽ��������ڲ�ƥ�� 
	local min = GetMinOfDay()
	if min < (19*60 + 30 ) or min > (23*60 + 59) then
		return
	end
	

	--������
	local dt = GetDayTime()
	if x300703_g_CompleteInfo.day ~= dt then
		
		x300703_g_CompleteInfo = { day = dt, first = 1, second = -1,third = -1 }
		AwardTitle(sceneId,selfId,18)
		return
		
	else
		
		if x300703_g_CompleteInfo.first == -1 then
			
			x300703_g_CompleteInfo.first = 1
			AwardTitle(sceneId,selfId,18)
			return
		end
		
		if x300703_g_CompleteInfo.second == -1 then
			
			x300703_g_CompleteInfo.second = 1
			AwardTitle(sceneId,selfId,19)
			return
		end
		
		if x300703_g_CompleteInfo.third == -1 then
			
			x300703_g_CompleteInfo.third = 1
			AwardTitle(sceneId,selfId,20)
			return
		end
		
	end
end

function x300703_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

	--if sceneId == 37 then
	--local x, z = GetWorldPos( sceneId, FindMonsterByGUID(sceneId, x300703_g_SubmitNpc[3][2]))
	
	--print ("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx", x, z)
	--end
	
	local npcGuid = GetMonsterGUID(sceneId,targetId)
	if sceneId == x300703_g_SubmitNpc[1][1] and npcGuid == x300703_g_SubmitNpc[1][2] then
		
		if IsHaveQuestNM( sceneId, selfId, x300703_g_MissionId ) <= 0 and QuestCheckAcceptNM( sceneId, selfId, targetId, x300703_g_MissionId ) > 0 then
			local  missionState = GetQuestStateNM(sceneId, selfId, targetId, x300703_g_MissionId)
			AddQuestTextNM(sceneId, selfId, targetId, x300703_g_MissionId, missionState)
		end
	elseif sceneId == x300703_g_SubmitNpc[2][1] and npcGuid == x300703_g_SubmitNpc[2][2] then
	
		if  IsHaveQuestNM( sceneId, selfId, x300703_g_MissionId ) > 0 and QuestCheckAcceptNM( sceneId, selfId, targetId, x300703_g_MissionId ) > 0 then 
			
			local misIndex = GetQuestIndexByID( sceneId, selfId, x300703_g_MissionId )
			if GetQuestParam( sceneId, selfId, misIndex, 6 ) ~= 1 then
				local  missionState = GetQuestStateNM(sceneId, selfId, targetId, x300703_g_MissionId)
				AddQuestTextNM(sceneId, selfId, targetId, x300703_g_MissionId, missionState)
			end
		end
	elseif sceneId == x300703_g_SubmitNpc[3][1] and npcGuid == x300703_g_SubmitNpc[3][2] then
	
		if IsHaveQuestNM( sceneId, selfId, x300703_g_MissionId ) > 0 and IsQuestHaveDoneNM( sceneId, selfId, x300703_g_MissionId ) <= 0 then
			local misIndex = GetQuestIndexByID( sceneId, selfId, x300703_g_MissionId )
			
			if GetQuestParam( sceneId, selfId, misIndex, 6 ) == 1 and GetQuestParam( sceneId, selfId, misIndex, 7 ) ~= 1 then
				SetQuestByIndex( sceneId, selfId, misIndex, 0, 1 )
				SetQuestByIndex( sceneId, selfId, misIndex, 7, 1 )
			end
			 
			local  missionState = GetQuestStateNM(sceneId, selfId, targetId, x300703_g_MissionId)
			AddQuestTextNM(sceneId, selfId, targetId, x300703_g_MissionId, missionState)
		end
	end
    
	return 0
end

--ѡ������
function x300703_ProcEventEntry( sceneId, selfId, targetId, MissionId )

	local npcGuid = GetMonsterGUID(sceneId,targetId)
	if sceneId == x300703_g_SubmitNpc[1][1] and npcGuid == x300703_g_SubmitNpc[1][2] then
		
		if IsHaveQuestNM( sceneId, selfId, MissionId ) == 0 then	-- ���û���������
			x300703_NextDayReset(sceneId, selfId)
			if  IsNpcHaveQuestNM(sceneId, selfId, targetId, MissionId) == 1 then--�����ж�npc�����Ƿ���������񣬷�����bug
			--��Ҫ����npc����û������������ʾ��
				local ret = QuestCheckAcceptNM( sceneId, selfId, targetId, MissionId )
				if ret > 0 then	-- ������Խ��������
					--AddDispatchQuestInfoNM( sceneId, selfId, targetId, MissionId ) -- ��ʾ����������Ϣ
					x300703_DispatchMissionInfo(sceneId, selfId, targetId, MissionId)
				else
					local strText = "δ֪�����޷����µ�����"
					if ret == -1 then
						strText = "�ȼ����㣬�޷����µ�����"
					elseif ret == -2 then
						strText = "�ȼ����ߣ��޷����µ�����"
					elseif ret == -3 then
						strText = "��Ǯ���㣬�޷����µ�����"
					elseif ret == -4 then
						strText = "�����Ǳ�����ң��޷����µ�����"
					elseif ret == -5 then
						strText = "ְҵ���Ͳ������޷����µ�����"
					elseif ret == -6 then
						strText = "��Ӫ�������޷����µ�����"
					elseif ret == -7 then
						strText = "�����޴�����"
					end
					Msg2Player(sceneId,selfId,strText,CHAT_TYPE_SELF,CHAT_PLUMB_SCROLL)
				end
			end
		else --������������
			local misIndex = GetQuestIndexByID( sceneId, selfId, x300703_g_MissionId )
			if QuestCheckSubmitNM( sceneId, selfId, targetId, x300703_g_MissionId, misIndex ) > 0 then -- �������������
				--QuestComplateInfoNM( sceneId, selfId, targetId, MissionId ) -- ��ʾ�����Ϣ
			else
				QuestNotComplateInfoNM( sceneId, selfId, targetId, x300703_g_MissionId ) -- ��ʾ����δ�����Ϣ
			end
		end
	elseif sceneId == x300703_g_SubmitNpc[2][1] and npcGuid == x300703_g_SubmitNpc[2][2] then
		
		x300703_DispatchMissionMiddleCompleted(sceneId, selfId, targetId, x300703_g_MissionId)
	elseif sceneId == x300703_g_SubmitNpc[3][1] and npcGuid == x300703_g_SubmitNpc[3][2] then
	
		local misIndex = GetQuestIndexByID( sceneId, selfId, x300703_g_MissionId )
		if GetQuestParam( sceneId, selfId, misIndex, 7 ) == 1 then
			x300703_DispatchMissionCompleted(sceneId, selfId, targetId, x300703_g_MissionId)
		else
			x300703_DispatchMissionContinueInfo(sceneId, selfId, targetId, x300703_g_MissionId)
		end
	end
end

function x300703_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
	
	local npcid = 139102
	if npcGuid == npcid then
		SetPatrolNoBreak(sceneId,npcId,1)
	end
	if IsHaveQuestNM( sceneId, selfId, x300703_g_MissionId) == 0 then	-- ���û���������
		return
	end
	
end

--ɱ������
function x300703_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end

-- �������
function x300703_DispatchMissionMiddleCompleted(sceneId, selfId,targetId, MissionId)
	
	BeginQuestEvent( sceneId);
		--������Ϣ
		AddQuestText(sceneId, "#Y"..x300703_g_MissionName);
		AddQuestText(sceneId, x300703_g_MissionMiddleCompleted)
		
		--����Ŀ��
		AddQuestText( sceneId, "#Y����Ŀ�꣺")
		AddQuestText( sceneId, "�ҵ�@npc_141544�����˶���#G����#W")
		AddQuestText( sceneId, " ")
		
		--������Ϣ

		--�����ҵ�ǰ�ȼ�
		local playerLevel = GetLevel( sceneId, selfId);
		--��ȡ����
		local experience1 = playerLevel*100*70
		local experience2 = playerLevel*100*70
		local experience = 0
		if GetLevel(sceneId, selfId) >=40 and GetLevel(sceneId, selfId) < 70 then
			experience = experience1;
		elseif GetLevel(sceneId, selfId) >=70 then
			experience = experience2;
		end
		AddQuestExpBonus( sceneId, experience);
		AddQuestMoneyBonus5(sceneId, 200 )

	EndQuestEvent(sceneId);
	DispatchQuestInfoNM(sceneId, selfId, targetId, x300703_g_scriptId, x300703_g_MissionId)
	
end

-- ������
function x300703_DispatchMissionCompleted(sceneId, selfId,targetId, MissionId)
	
	BeginQuestEvent( sceneId);
		--������Ϣ
		AddQuestText(sceneId, "#Y"..x300703_g_MissionName);
		AddQuestText(sceneId, x300703_g_MissionCompleted)
		
		--����Ŀ��
		--AddQuestText( sceneId, "#Y����Ŀ�꣺")
		--AddQuestText( sceneId, x300703_g_MissionTarget)
		--AddQuestText( sceneId, " ")
		
		--������Ϣ

		--�����ҵ�ǰ�ȼ�
		local playerLevel = GetLevel( sceneId, selfId);
		--��ȡ����
		local experience1 = playerLevel*100*70
		local experience2 = playerLevel*100*70
		local experience = 0
		if GetLevel(sceneId, selfId) >=40 and GetLevel(sceneId, selfId) < 70 then
			experience = experience1;
		elseif GetLevel(sceneId, selfId) >=70 then
			experience = experience2;
		end
		AddQuestExpBonus( sceneId, experience);
		AddQuestMoneyBonus5(sceneId, 200 )

	EndQuestEvent(sceneId);
	DispatchQuestInfoNM(sceneId, selfId, targetId, x300703_g_scriptId, x300703_g_MissionId)
	
end

function x300703_DispatchMissionInfo(sceneId, selfId,targetId, MissionId)
	
	BeginQuestEvent( sceneId);
		--������Ϣ
		AddQuestText(sceneId, "#Y"..x300703_g_MissionName);
		AddQuestText(sceneId, x300703_g_MissionInfo)
		--����Ŀ��
		AddQuestText( sceneId, "#Y����Ŀ�꣺")
		AddQuestText( sceneId, x300703_g_MissionTarget)
		AddQuestText( sceneId, " ")

	EndQuestEvent(sceneId);
	DispatchQuestInfoNM(sceneId, selfId, targetId, x300703_g_scriptId, x300703_g_MissionId)
end


function x300703_DispatchMissionContinueInfo(sceneId, selfId, targetId, MissionId)

	BeginQuestEvent( sceneId);
		--������Ϣ
		AddQuestText(sceneId, "#Y"..x300703_g_MissionName)
		AddQuestText(sceneId, x300703_g_ContinueMissionInfo)
		
		--����Ŀ��
		AddQuestText( sceneId, "#Y����Ŀ�꣺")
		AddQuestText( sceneId, x300703_g_MissionTarget)
		AddQuestText( sceneId, " ")
	EndQuestEvent(sceneId);

	DispatchQuestContinueInfoNM(sceneId, selfId, targetId, x300703_g_scriptId, MissionId);
end

--��������
function x300703_ProcQuestAccept( sceneId, selfId, targetId, MissionId )
	
	if x300703_ProcAcceptCheckTime() < 0 then --û�ڽ������ʱ���
		Msg2Player(sceneId,selfId,"�ܱ�Ǹ�������ڹ涨ʱ���ڲ���������ÿ�յ�19��30~24��00��������",CHAT_TYPE_SELF,CHAT_PLUMB_SCROLL)
		Msg2Player(sceneId,selfId,"�ܱ�Ǹ�������ڹ涨ʱ���ڲ���������ÿ�յ�19��30~24��00��������",CHAT_TYPE_SELF,CHAT_RIGHTDOWN)
		return 
	end
	

	if IsHaveSpecificImpact( sceneId, selfId, 7702 ) > 0 then
		Msg2Player(sceneId,selfId,"�ܱ�Ǹ�����������Ӳ���������",CHAT_TYPE_SELF,CHAT_PLUMB_SCROLL)
		Msg2Player(sceneId,selfId,"�ܱ�Ǹ�����������Ӳ���������",CHAT_TYPE_SELF,CHAT_RIGHTDOWN)
		return 
	end
	
	--��ͯȤ���ܽ�
	if IsHaveQuestNM( sceneId, selfId, 8066 ) > 0 or
		IsHaveQuestNM( sceneId, selfId, 8074 ) > 0 or 
		IsHaveQuestNM( sceneId, selfId, 8067 ) > 0 or
		IsHaveQuestNM( sceneId, selfId, 8068 ) > 0 or
		IsHaveQuestNM( sceneId, selfId, 8069 ) > 0 or
		IsHaveQuestNM( sceneId, selfId, 8070 ) > 0 or
		IsHaveQuestNM( sceneId, selfId, 8071 ) > 0 or
		IsHaveQuestNM( sceneId, selfId, 8072 ) > 0 or
		IsHaveQuestNM( sceneId, selfId, 8073 ) > 0 then

		Msg2Player(sceneId,selfId,"�ܱ�Ǹ������ͯȤ������������",CHAT_TYPE_SELF,CHAT_PLUMB_SCROLL)
		Msg2Player(sceneId,selfId,"�ܱ�Ǹ������ͯȤ������������",CHAT_TYPE_SELF,CHAT_RIGHTDOWN)
		return
	end

	if IsBusMember(sceneId, selfId) > 0 then
		Msg2Player(sceneId,selfId,"�ܱ�Ǹ�����Ͳ���������",CHAT_TYPE_SELF,CHAT_PLUMB_SCROLL)
		Msg2Player(sceneId,selfId,"�ܱ�Ǹ�����Ͳ���������",CHAT_TYPE_SELF,CHAT_RIGHTDOWN)
		return 
	end
	
	if IsPlayerStateNormal(sceneId,selfId) == 1 then
		if GetChangeSceneState(sceneId, selfId)==2 then
			return
		end
	else
		return
	end
			
	local npcGuid = GetMonsterGUID(sceneId,targetId)
	
	if sceneId == x300703_g_SubmitNpc[1][1] and npcGuid == x300703_g_SubmitNpc[1][2] then
		local rounds = GetQuestData(sceneId, selfId, MD_TIEREN_COMMITTIME[1], MD_TIEREN_COMMITTIME[2], MD_TIEREN_COMMITTIME[3])

		if rounds >= 1 then
			Msg2Player(sceneId,selfId,"�ܱ�Ǹ���������Ѿ���ȡ������������������������",CHAT_TYPE_SELF,CHAT_PLUMB_SCROLL)
			Msg2Player(sceneId,selfId,"�ܱ�Ǹ���������Ѿ���ȡ������������������������",CHAT_TYPE_SELF,CHAT_RIGHTDOWN)
			return
		end
		
		--���ǰ������
		local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId, x300703_g_MissionId )
		if FrontMissiontId1 ~= -1 then
			if IsQuestHaveDoneNM( sceneId, selfId, FrontMissiontId1 ) == 0 then
				return 0
			end
		end
		if FrontMissiontId2 ~= -1 then
			if IsQuestHaveDoneNM( sceneId, selfId, FrontMissiontId2 ) == 0 then
				return 0
			end
		end
		if FrontMissiontId3 ~= -1 then
			if IsQuestHaveDoneNM( sceneId, selfId, FrontMissiontId3 ) == 0 then
				return 0
			end
		end

		local ret = QuestCheckAcceptNM( sceneId, selfId, targetId, x300703_g_MissionId ) -- ��ȡ������������Ϣ
		if ret > 0 then -- ������Խ��������
			ret = AddQuest( sceneId, selfId, x300703_g_MissionId, x300703_g_scriptId, 0, 0, 0, 1) -- ������������
			if ret > 0 then
				local misIndex = GetQuestIndexByID( sceneId, selfId, x300703_g_MissionId )
				SetQuestByIndex( sceneId, selfId, misIndex, 0, 0 )
				SetQuestByIndex( sceneId, selfId, misIndex, 7, 0 )
				
				x300703_SetAcceptTime(sceneId, selfId)
				return 1
			elseif ret == 0 then
				local strText = "�������ʧ��"
				Msg2Player(sceneId,selfId, strText,CHAT_TYPE_SELF,CHAT_PLUMB_SCROLL)
			elseif ret == -1 then
				local strText = "��������,�����������������"
				Msg2Player(sceneId,selfId, strText,CHAT_TYPE_SELF,CHAT_PLUMB_SCROLL)
			elseif ret == -2 then
				local strText = "�����������������ʧ��"
				Msg2Player(sceneId,selfId, strText,CHAT_TYPE_SELF,CHAT_PLUMB_SCROLL)
			end
		end
	elseif sceneId == x300703_g_SubmitNpc[2][1] and npcGuid == x300703_g_SubmitNpc[2][2] then
	
		local misIndex = GetQuestIndexByID( sceneId, selfId, x300703_g_MissionId )
		
		if GetQuestParam( sceneId, selfId, misIndex, 6 ) ~= 1 then 
			SetQuestByIndex( sceneId, selfId, misIndex, 6, 1 )
		
			x300703_AddLog(sceneId, selfId, 1, MissionId)

			ReCallHorse( sceneId, selfId )--ǿ������
			--x300703_DispelBuff(sceneId, selfId)

			x300703_SendStateBuff(sceneId, selfId)
			
			-- ������buff
			SendSpecificImpactToUnit(sceneId, selfId, selfId, selfId, 7716, 0)
				
			local message = format(x300703_g_AcceptMessage, x300703_g_MissionName)
			Msg2Player(sceneId,selfId, message,CHAT_TYPE_SELF,CHAT_PLUMB_SCROLL)
			Msg2Player(sceneId,selfId, message,CHAT_TYPE_SELF,CHAT_RIGHTDOWN)

			x300703_ProcQuestLogRefresh( sceneId,selfId,x300703_g_MissionId)

			MarkMutexState(sceneId, selfId, 18)
			return 1
		end
	elseif sceneId == x300703_g_SubmitNpc[3][1] and npcGuid == x300703_g_SubmitNpc[3][2] then
		x300703_MissionComplate( sceneId, selfId, targetId, selectId, x300703_g_MissionId )
	end
	return 0
end

--�������
function x300703_ProcQuestAbandon( sceneId, selfId, MissionId )
	local ret = 0
	ret = DelQuestNM( sceneId, selfId, x300703_g_MissionId )
	if ret == 1 then
		--SetImmuneAbsForLater( sceneId, selfId, 0 ) --���þ�������
		x300703_CancelStateBuff(sceneId, selfId)

		x300703_NextDayReset(sceneId, selfId)
		local rounds = GetQuestData(sceneId, selfId, MD_TIEREN_COMMITTIME[1], MD_TIEREN_COMMITTIME[2], MD_TIEREN_COMMITTIME[3])
		SetQuestData(sceneId, selfId, MD_TIEREN_COMMITTIME[1], MD_TIEREN_COMMITTIME[2], MD_TIEREN_COMMITTIME[3], rounds+1)
		local day = GetDayOfYear()
		SetQuestData(sceneId, selfId, MD_TIEREN_ACCEPTTIME_DAY[1], MD_TIEREN_ACCEPTTIME_DAY[2], MD_TIEREN_ACCEPTTIME_DAY[3], day)

		ClearMutexState(sceneId, selfId, 18)

		local message = format(x300703_g_AbandonMessage, x300703_g_MissionName)
		Msg2Player(sceneId,selfId, message,CHAT_TYPE_SELF,CHAT_PLUMB_SCROLL)
		Msg2Player(sceneId,selfId, message,CHAT_TYPE_SELF,CHAT_RIGHTDOWN)
	end
end

--�������
--����1����ɹ���0��������ʧ��
function x300703_ProcQuestSubmit( sceneId, selfId, targetId, selectId, MissionId )

	if IsHaveQuestNM( sceneId, selfId, MissionId ) == 0 then	-- ���û�������ֱ���˳�
		return 0
	end

	local npcGuid = GetMonsterGUID(sceneId,targetId)local npcGuid = GetMonsterGUID(sceneId,targetId)
	if sceneId == x300703_g_SubmitNpc[3][1] and npcGuid == x300703_g_SubmitNpc[3][2] then
	
		--x300703_MissionComplate( sceneId, selfId, targetId, selectId, x300703_g_MissionId )
		return 1
	end
	return 0
end

function x300703_AddTianfuItem( sceneId, selfId)
	local level = GetLevel( sceneId, selfId)
	if level >= 80 then
		if random( 1, 100) <= 22 then
			local nIndex = random(1,3)
			BeginAddItem( sceneId)
	        AddItem( sceneId, x300703_g_TianfuItems[nIndex], 1)
	        if EndAddItem( sceneId, selfId) <= 0 then
	            Msg2Player( sceneId, selfId, "������ı����������޷�����츳���߽�����", 8, 2)
	        else
	            AddItemListToPlayer( sceneId, selfId)
	        end
		end
	end
end
--�������
function x300703_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	--x300703_SetCommitTime(sceneId, selfId, MissionId)
	local ret = DelQuestNM( sceneId, selfId, MissionId )
	if ret == 1 then -- ����ɹ����
		x300703_AddLog(sceneId, selfId, 0, MissionId)
		--SetImmuneAbsForLater( sceneId, selfId, 0 ) --���þ�������
		--������Ľ���δ��
		local level = GetLevel(sceneId, selfId)
		local award1 = floor(100*level*70)
		local award2 = floor(100*level*70)
		local award = 0
		if GetLevel(sceneId, selfId) >=40 and GetLevel(sceneId, selfId) < 70 then
			award = award1;
		elseif GetLevel(sceneId, selfId) >=70 then
			award = award2;
		end
		ClearMutexState(sceneId, selfId, 18)

		local MissionName = GetQuestNameNM( sceneId, selfId, MissionId )
		local message = format(x300703_g_CompleteMessage, MissionName)
		Msg2Player(sceneId,selfId,message,CHAT_TYPE_SELF,CHAT_PLUMB_SCROLL)
		Msg2Player(sceneId,selfId,message,CHAT_TYPE_SELF,CHAT_RIGHTDOWN)

		local level = GetLevel(sceneId, selfId)
		if IsHaveSpecificImpact( sceneId, selfId, 7716 ) > 0 then
			award = award + level*7000
			AddExp(sceneId, selfId, award)
			
			message = format("#Y���#R����%d#Y�Ľ���", award/2)
			message1 = format("#Y���ǳ�Ѹ�ٵ�����ˡ��塿����������⽱��#R����%d��", award/2)
			Msg2Player(sceneId,selfId,message,CHAT_TYPE_SELF,CHAT_PLUMB_SCROLL)
			Msg2Player(sceneId,selfId,message,CHAT_TYPE_SYSTEM,CHAT_RIGHTDOWN)
			Msg2Player(sceneId,selfId,message1,CHAT_TYPE_SELF,CHAT_PLUMB_SCROLL)
			Msg2Player(sceneId,selfId,message1,CHAT_TYPE_SYSTEM,CHAT_RIGHTDOWN)
		else
			AddExp(sceneId, selfId, award)
			
			message = format("#Y���#R����%d#Y�Ľ���", award)
			Msg2Player(sceneId,selfId,message,CHAT_TYPE_SELF,CHAT_PLUMB_SCROLL)
			Msg2Player(sceneId,selfId,message,CHAT_TYPE_SYSTEM,CHAT_RIGHTDOWN)
		end
		
		local nShengWang = GetShengWang( sceneId, selfId )
		nShengWang = nShengWang + 200
		SetShengWang( sceneId, selfId, nShengWang )
		message = format("�������%d�Ľ�����", 200)
		Msg2Player(sceneId,selfId,message,CHAT_TYPE_SELF,CHAT_PLUMB_SCROLL)
		Msg2Player(sceneId,selfId,message,CHAT_TYPE_SYSTEM,CHAT_RIGHTDOWN)
		CallScriptFunction( 256224, "Finishtiesan", sceneId, selfId)	
		x300703_NextDayReset(sceneId, selfId)
		local rounds = GetQuestData(sceneId, selfId, MD_TIEREN_COMMITTIME[1], MD_TIEREN_COMMITTIME[2], MD_TIEREN_COMMITTIME[3])
		SetQuestData(sceneId, selfId, MD_TIEREN_COMMITTIME[1], MD_TIEREN_COMMITTIME[2], MD_TIEREN_COMMITTIME[3], rounds+1)
		local day = GetDayOfYear()
		SetQuestData(sceneId, selfId, MD_TIEREN_ACCEPTTIME_DAY[1], MD_TIEREN_ACCEPTTIME_DAY[2], MD_TIEREN_ACCEPTTIME_DAY[3], day)

        -- ���һö�󶼼��껪���ֱ�
        BeginAddItem( sceneId)
        AddItem( sceneId, 11990117, 10)
        if EndAddItem( sceneId, selfId) <= 0 then
            Msg2Player( sceneId, selfId, "������ˡ��塿�󶼼��껪��������ı����������޷����#{_ITEM11990117}������", CHAT_TYPE_SELF, CHAT_RIGHTDOWN)
        else
            AddItemListToPlayer( sceneId, selfId)
        end
        
        x300703_AddTianfuItem( sceneId, selfId)
	
		--�������
		local hour,minute,second = GetHourMinSec()
		local val = 0;
		val = val + (hour-19)*3600
		val = val + (minute-30)*60
		val = val + second
		SendToplistKeyValue2GL(sceneId,selfId,TIEREN_TOPLIST,val)
		
		--�����ƺ�
		x300703_AwardTitle(sceneId,selfId)

		local j = random(1,5)
		local buff 	=	9011
		local buff1 =	9013
		local buff2 =	9012
		if j ==1 then
			BeginAddItem( sceneId )
			if IsHaveSpecificImpact( sceneId, selfId, buff) == 1 or IsHaveSpecificImpact( sceneId, selfId, buff1) == 1  or IsHaveSpecificImpact( sceneId, selfId, buff2) == 1 then
				AddItem( sceneId, 12030107, 1 )
			else
				AddBindItem( sceneId, 12030107, 1 )
			end
			local result = EndAddItem( sceneId, selfId )
			if result > 0 then
				AddItemListToPlayer(sceneId,selfId)
				local Country = CallScriptFunction(888888, "GetCountryName", sceneId, selfId )
				--local selfName = GetName(sceneId, selfId)
				--local msg = format("#G��ϲ#Y%s#G�����������л��#R�����ر�ͼ#Gһ�š�", selfName)
				--LuaAllScenceM2Wrold(sceneId, msg, 1, 1)
			else
				Msg2Player(sceneId,selfId,"�ܱ�Ǹ�������������޷��õ���Ʒ��",CHAT_TYPE_SELF,CHAT_PLUMB_SCROLL)
			end
		end

		x300703_CancelStateBuff(sceneId, selfId)
		
		return 1 -- ���سɹ�
		
	else -- ���δ�ɹ����
		BeginQuestEvent(sceneId)
		local strText = "δ֪�����޷��������"
		if ret == -2 then
			strText = "��ѡ������Ʒ"
		elseif ret == -3 then
			strText = "��������,�����������������"
		elseif ret == -4 then
			strText = "�۳�������Ʒʧ��"
		end
		Msg2Player(sceneId,selfId,strText,CHAT_TYPE_SELF,CHAT_PLUMB_SCROLL)
		return 0
	end
	return 0
end

function x300703_ProcAcceptCheckTime(  )

	local minute = GetMinOfDay()
	if (minute >= 19*60+30 and minute <24*60) then
		return 1
	end

	return -1
end

function x300703_SetAcceptTime(sceneId, selfId)
	
	local day = GetDayOfYear()
	local minute = GetMinOfDay()
	
	SetQuestData(sceneId, selfId, MD_TIEREN_ACCEPTTIME_DAY[1], MD_TIEREN_ACCEPTTIME_DAY[2], MD_TIEREN_ACCEPTTIME_DAY[3], day)
	SetQuestData(sceneId, selfId, MD_TIEREN_ACCEPTTIME_MINUTE[1], MD_TIEREN_ACCEPTTIME_MINUTE[2], MD_TIEREN_ACCEPTTIME_MINUTE[3], minute)
end

function x300703_TieSanOnDie(sceneId, selfId)
	
	local lastDay = GetQuestData(sceneId, selfId, MD_TIEREN_ACCEPTTIME_DAY[1], MD_TIEREN_ACCEPTTIME_DAY[2], MD_TIEREN_ACCEPTTIME_DAY[3])
	local lastMin = GetQuestData(sceneId, selfId, MD_TIEREN_ACCEPTTIME_MINUTE[1], MD_TIEREN_ACCEPTTIME_MINUTE[2], MD_TIEREN_ACCEPTTIME_MINUTE[3])

	local nowTime = GetDayOfYear()*1440 + GetMinOfDay()
	local lastTime = lastDay*1440 + lastMin

	if IsHaveQuestNM( sceneId, selfId, x300703_g_MissionId ) > 0 then
		if nowTime - lastTime < 120 then
			--SetImmuneAbsForLater( sceneId, selfId, 1 ) --���þ�������
			
			local misIndex = GetQuestIndexByID( sceneId, selfId, x300703_g_MissionId )
			if GetQuestParam( sceneId, selfId, misIndex, 6 ) == 1 then 
			
				ReCallHorse( sceneId, selfId )--ǿ������
				--x300703_DispelBuff(sceneId, selfId)
	
				x300703_SendStateBuff(sceneId, selfId)
	
				MarkMutexState(sceneId, selfId, 18) 
			end
			return 
		end

		--SetImmuneAbsForLater( sceneId, selfId, 0 ) --���þ�������
		x300703_CancelStateBuff(sceneId, selfId)
		
		DelQuestNM( sceneId, selfId, x300703_g_MissionId )
		ClearMutexState(sceneId, selfId, 18)
		Msg2Player(sceneId,selfId,"������������������ʧ�ܣ���������ȡ��",CHAT_TYPE_SELF,CHAT_PLUMB_SCROLL)
		Msg2Player(sceneId,selfId,"������������������ʧ�ܣ���������ȡ��",CHAT_TYPE_SELF,CHAT_RIGHTDOWN)
		x300703_NextDayReset(sceneId, selfId)
		local rounds = GetQuestData(sceneId, selfId, MD_TIEREN_COMMITTIME[1], MD_TIEREN_COMMITTIME[2], MD_TIEREN_COMMITTIME[3])
		SetQuestData(sceneId, selfId, MD_TIEREN_COMMITTIME[1], MD_TIEREN_COMMITTIME[2], MD_TIEREN_COMMITTIME[3], rounds+1)
		local day = GetDayOfYear()
		SetQuestData(sceneId, selfId, MD_TIEREN_ACCEPTTIME_DAY[1], MD_TIEREN_ACCEPTTIME_DAY[2], MD_TIEREN_ACCEPTTIME_DAY[3], day)
		
		if sceneId ~= 0 then
			NewWorld(sceneId, selfId, 0, x300703_g_BackPos[1], x300703_g_BackPos[2], x300703_g_scriptId)
		else
			SetPos(sceneId,selfId, x300703_g_BackPos[1], x300703_g_BackPos[2])
		end
	end

end

function x300703_NextDayReset(sceneId, selfId)
	
	local lastDay = GetQuestData(sceneId, selfId, MD_TIEREN_ACCEPTTIME_DAY[1], MD_TIEREN_ACCEPTTIME_DAY[2], MD_TIEREN_ACCEPTTIME_DAY[3])

	local today = GetDayOfYear()
	if today ~= lastDay then 
		SetQuestData(sceneId, selfId, MD_TIEREN_ACCEPTTIME_DAY[1], MD_TIEREN_ACCEPTTIME_DAY[2], MD_TIEREN_ACCEPTTIME_DAY[3], 0)
		SetQuestData(sceneId, selfId, MD_TIEREN_ACCEPTTIME_MINUTE[1], MD_TIEREN_ACCEPTTIME_MINUTE[2], MD_TIEREN_ACCEPTTIME_MINUTE[3], 0)
		SetQuestData(sceneId, selfId, MD_TIEREN_COMMITTIME[1], MD_TIEREN_COMMITTIME[2], MD_TIEREN_COMMITTIME[3], 0)
	end
end

function x300703_CanDispel(dataIndex)
	for j=0, x300703_g_ImpactDataIndex_Size-1 do
		if dataIndex == x300703_g_UnDispelImpactDataIndex[j+1] then
			return -1
		end
	end
	return 1
end

function x300703_DispelBuff(sceneId, selfId)
	local count = GetImpactListCount( sceneId, selfId )
	for i=0, count-1 do
		local dataIndex = GetImpactDataIndex( sceneId, selfId, i )
		if x300703_CanDispel(dataIndex) > 0 then
			DispelSpecificImpact( sceneId, selfId, dataIndex )
		end
	end
end

function x300703_ProcQuestLogRefresh( sceneId,selfId,missionId)
	
	local target = x300703_g_MissionTarget
	local target1 = x300703_g_MissionTarget1
	local misIndex = GetQuestIndexByID( sceneId, selfId, x300703_g_MissionId )
	if GetQuestParam( sceneId, selfId, misIndex, 6 ) == 1 then
		target = "  �ҵ�����@npc_141544�����˶���#G����#W"
	end
	
    BeginQuestEvent(sceneId)
        AddQuestLogCustomText( sceneId,
                                "",                    -- ����
                                x300703_g_MissionName,                 -- ��������
                                target,               --����Ŀ��
                                target1,                         --����NPC
                                x300703_g_Missionruse,                   --������
                                "\t���Ǵ�Ԫ�Թ����䣬���Ӷ��������ܵ�ѵ������ΰ��ĳɼ�˼��ʱ�ڣ��������ƶ���������ľ����ᣬ������������������������������Ҳ�����ƵĻ���׳ơ�����������������ﱨ��������ȥ�󶼶����μӱ����ˡ�\n#W  ��������ı����ܼ򵥣��������ҵ�Ŀ�������ɡ��˻����֮�������˱˴�֮��ľ��룬�����˱˴˵�Э��������������÷�����������ڵ�ʲô���Ͻ��ж������ɣ�",                --��������
                                ""        --����С��ʾ
                                )

	EndQuestEvent()
	DispatchQuestLogUpdate(sceneId, selfId, x300703_g_MissionId);
end

