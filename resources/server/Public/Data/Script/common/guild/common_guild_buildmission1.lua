--MD_BANGHUI_RANDMISSIONID	= {4, 0, 18}
--MD_BANGHUI_RANDMISSIONTYPE	= {4, 18, 4}	--��֤ÿ�ΰ����������������Ͳ�ͬ
--MD_BANGHUI_LASTDAY		= {4, 22, 9}	--���������ڻ�������������
--
--MD_BANGHUI_CIRCLE		= {5, 0, 6}	--���ֻ����ļ���
--MD_BANGHUI_HIGH		= {5, 6, 8}	--����߶���ļ���
--MD_BANGHUI_ABANDON		= {5, 14, 12}	--���һ�η���ʱ��

x300670_g_ScriptId = 300670
x300670_g_AbandonTime = 5
-- ��������
x300670_g_MissionName = "����᡿�������"

x300670_g_MissionCommentId	=	9031	
x300670_g_VirtualMissionId_Low	=	10000
x300670_g_VirtualMissionId_High	=	10000
x300670_g_MissionRangeStart	=	10001
x300670_g_MissionRangeEnd		= 10258
x300670_g_MissionCommentMessage	=	"\t�������������ֻ��Ҫ���հ�����񷢲��˵�Ҫ��������񣬾Ϳ��Ի��#G����#W��#G�ﹱ#W�Ľ�����\n\t#G��������ҵȼ������ӣ��������������Ѷ�Ҳ�����ӣ����ԣ�#Y20-50#G����������������ɴ�����ġ���"
x300670_g_MissionCommentWrongPlace =    "\t���㵽�󶼰�����񷢲��ٴ�������"
x300670_g_MissionNPCObjId_Low		= 138533
x300670_g_MissionNPCObjId_High		= 138533
x300670_g_LevelLess             = 20 

x300670_OneRoundCount = 10		--ÿ�ֶ��ٻ�
x300670_HighBonusCircleCount = 10	--ÿ�ռ����߽�
--x300670_g_DeliverItemID			= 13011600
--x300670_g_DeliverItemCount		= 1
x300670_CountrySceneList	= {50, 150, 250, 350}
x300670_CapitalSceneId		= 0
x300670_LevelToCapital		= 300	--������Ŀ�ʼ�ȼ�
x300670_MisParam_NPCData	= 1	--����N��Ŀ��NPC�����: ÿ4��������λ����һ��NPC, N<=8
x300670_MisParam_FindData	= 2	--����N��Ŀ��NPC�Ľ��: ÿ4��������λ����һ��NPC, N<=8 
x300670_g_DeliverTargetCount	= 3	-- <= 8
x300670_AddGuildExpValue	= 1
x300670_MaxAddGuildExp		= 100
x300670_DeliverMissionTarget	= "�ҵ�"
x300670_DeliverTextFind		= "���Ѿ��ҵ���@npc_%d (%d/3)"
x300670_g_MissionCommentAfterAbandon = "\t�ܱ�Ǹ��������Ѿ����������������������ɡ�"
x300670_g_MissionCommentAfterEnough = "\t������Ѿ�����%d�ΰ�����������Ĺ��׹����ˣ�����������æ�ɡ�"
x300670_g_DeliverTargetNPC	= { 
					{
					    { npcId = 	138516, Dialog = "\t���С����ҲҪ�����ҡ���\n\t�ð�!һ���Ҿʹ���ȥ������"	}, --1
					    { npcId = 	138806, Dialog = "\tû�����⣬�ҵ����ѣ��ܸ����ܰ������ǵ�æ��"	}, --2
					    { npcId = 	138802, Dialog = "\t�������������Ѿ�æ�Ľ�ͷ�ö��ˡ�\n\t�����ɣ��Ҵ��������¾͹�ȥ��"	}, --3
					    { npcId = 	138600, Dialog = "\t�Һ������æ~���������Եȣ�СŮ����ױ��ϣ��Ի�ǰ����"	}, --4
					    { npcId = 	138822, Dialog = "\t����Ҫ��ɹ�ô��Ҫ��Ҫ�Ҵ��ϻ�����"	}, --5
					    { npcId = 	138812, Dialog = "\t�����ᱣ����ģ��ҵĺ��ӣ�����Ͷ���"	}, --6
					    { npcId = 	138800, Dialog = "\t�һ�ȥ�ġ���������Ҫ���ҵ����Ӳ��������ʱ��"	}, --7
					},
					{
					    { npcId = 	138817, Dialog = "\t�ͼ��������ģ��ðɣ�������ȥ�������ϴ����������ﶩ���Ļ����������Ҳû���壡"	}, 
					    { npcId = 	138824, Dialog = "\t�ҽ�����һ���Ӽ�ʮ�������£�һ�����ɼ������¹�ȥ�����С�£��ҾͲ����Գ����ˣ�"	}, 
					    { npcId = 	138588, Dialog = "\tѺ�˹ٵ�ְ�����Ҳ��������뿪�������ҿ�������Щ��Ѻ�˵ļһ���Сæ����"	}, 
					    { npcId = 	138814, Dialog = "\t��æ���б���ô��һ�����ɸ�����ȥ������û��׬ͷ�������Ҵ���������"	}, 
					    { npcId = 	138500, Dialog = "\t����ΪʲôҪ�����ң�"	}, 
					    { npcId = 	138276, Dialog = "\t�����顭����Ҫ����ʾ�����峤��������������һ����ͬ��ġ�"	}, 
					    { npcId = 	138270, Dialog = "\t�ã����ǰ���˶����ҵ��Ϲ˿ͣ���һ��׼ʱ����"	}, 
					},
					{
					    { npcId = 	138190, Dialog = "\t�õĺõģ������һ��Ǽ��������ĺ��ӣ��Ҿ͹�ȥ��"	}, 
					    { npcId = 	138155, Dialog = "\t�ܸ�����Ϊ����æ����׼��һ�����Ͼ͵���"	}, 
					    { npcId = 	138166, Dialog = "\t��Ҫ�ҵİ�����û���⣡������̨�ǳ������ĺ�˵����"	}, 
					    { npcId = 	138170, Dialog = "\t�ܸ�����Ϊ����Щ΢��֮������׼��һ�����Ͼ͵���"	}, 
					    { npcId = 	138655, Dialog = "\t�ҴӲ��ʽ����£��������ǰ����������һ���Ҫ���ġ�\n\t�ðɣ����Ȼ�ȥ�������͵���"	}, 
					    { npcId = 	138000, Dialog = "\t������������æ���ð���������Ҫ�����ҵ�С���~"	}
					},
				}

x300670_g_RewardList		= {
					{ step = 1, exprate = 3000, bangg = 1},
					{ step = 2, exprate = 3000, bangg = 2},
					{ step = 3, exprate = 3000, bangg = 3},
					{ step = 4, exprate = 3000, bangg = 4},
					{ step = 5, exprate = 3000, bangg = 5},
					{ step = 6, exprate = 3000, bangg = 6},
					{ step = 7, exprate = 3000, bangg = 7},
					{ step = 8, exprate = 3000, bangg = 8},
					{ step = 9, exprate = 3000, bangg = 9},
					{ step = 10, exprate = 3000, bangg = 10},
				}
x300670_g_DefaultMissionId	=	9030

x300670_g_MissionIdList	=	{
					{
						level	=	{ min=20, max=29 },
						rate	=	{ 50, 100 },
						MissionId = {
								--����
								{9030},	
								--�ռ�
								{ 10001, 10002, 10003, 10004, 10005, 10006, 10007, 10008, 10009 },
						}
					},
					{
						level	=	{ min=30, max=39 },
						rate	=	{ 50, 100 },
						MissionId = {
								--����
								{9030},	
								--�ռ�
								{ 10015, 10016, 10017, 10018, 10019, 10020, 10021, 10022, 10023, 10024, 10025, 10026, 10027, 10028, 10029 },
						}
					},
					{
						level	=	{ min=40, max=49 },
						rate	=	{ 50, 100 },
						MissionId = {
								--����
								{9030},	
								--�ռ�
								{ 10035, 10036, 10037, 10038, 10039, 10040, 10041, 10042, 10043, 10044, 10045, 10046, 10047, 10048, 10049, 10050, 10051, 10052, 10053, 10054, 10055, 10056, 10057, 10058, 10059, 10060, 10061, 10062, 10063, 10064, 10065, 10066, 10067 },
						}
					},
					{
						level	=	{ min=50, max=59 },
						rate	=	{ 50, 100 },
						MissionId = {
								--����
								{9030},	
								--�ռ�
								{ 10075, 10076, 10077, 10078, 10079, 10080, 10081, 10082, 10083, 10084, 10085, 10086, 10087, 10088, 10089, 10090, 10091, 10092, 10093, 10094, 10095, 10096, 10097, 10098, 10099, 10100, 10101, 10102, 10103, 10104, 10105, 10106, 10107 },
						}
					},
					{
						level	=	{ min=60, max=69 },
						rate	=	{ 50, 100 },
						MissionId = {
								--����
								{9030},	
								--�ռ�
								{ 10205, 10206, 10207, 10208, 10209, 10210, 10211, 10212, 10213, 10214, 10215, 10216, 10217, 10218, 10219, 10220, 10221, 10222, 10223, 10224, 10225, 10226, 10227, 10228 },
						}
					},
					{
						level	=	{ min=70, max=9999 },
						rate	=	{ 50, 100 },
						MissionId = {
								--����
								{9030},	
								--�ռ�
								{ 10235, 10236, 10237, 10238, 10239, 10240, 10241, 10242, 10243, 10244, 10245, 10246, 10247, 10248, 10249, 10250, 10251, 10252, 10253, 10254, 10255, 10256, 10257, 10258 },
						}
					},
				}

function x300670_GenerateRandomMission(sceneId, selfId, targetId)

	local MissionId = x300670_g_DefaultMissionId;
	local level = GetLevel(sceneId, selfId);
 	--local oldtype = x300670_GetMD(sceneId, selfId, MD_BANGHUI_RANDMISSIONTYPE)
	local newtype = 0;
	local randval = random(0, 99);
	for i, setitem in x300670_g_MissionIdList do
	
		
		if level >= setitem.level.min and level <= setitem.level.max then
			--for j, rateitem in setitem.rate do
				--if randval < rateitem then
					--newtype = j;
					--break;
				--end
			--end
			newtype = 2
			randval = random(1, getn(setitem.MissionId[newtype]));
			MissionId = setitem.MissionId[newtype][randval];
			break;
		end
	end

	if newtype == 0 then	--δ�ҵ�������ҵȼ�������
		return 0;
	end

	if MissionId < x300670_g_MissionRangeStart or MissionId > x300670_g_MissionRangeEnd then
		MissionId = x300670_g_MissionRangeStart;
	end
	
--	local GMSetId = GetQuestParam(sceneId, selfId, 19, 6)
--	if (GMSetId >= x300670_g_MissionRangeStart and GMSetId <= x300670_g_MissionRangeEnd) then
--		MissionId = GMSetId
--	end

	--MissionId = 10001	--�ռ�
	--MissionId = 9030	--����
	newtype = 1
	x300670_SetMD (sceneId, selfId, MD_BANGHUI_RANDMISSIONID, MissionId)
	--x300670_SetMD (sceneId, selfId, MD_BANGHUI_RANDMISSIONTYPE, newtype)
	return MissionId, newtype;
end

function x300670_GetRandMissionId(sceneId, selfId)
	return x300670_GetMD(sceneId, selfId, MD_BANGHUI_RANDMISSIONID)
end

function x300670_ProcAcceptCheck(sceneId, selfId, targetId, MissionId)

	MissionId = x300670_GetRandMissionId(sceneId, selfId);

	if IsHaveQuestNM(sceneId, selfId, MissionId) > 0 then
		return 0;
	end
	return 1;

end

function x300670_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

	local ret = 0;

	--x300670_SetMD(sceneId, selfId, MD_BANGHUI_HIGH, 0)
	--x300670_SetMD(sceneId, selfId, MD_BANGHUI_LASTDAY, 0)
	--x300670_SetMD(sceneId, selfId, MD_BANGHUI_ABANDON, 0)

	--���ڹ涨��С�ȼ�����Ҳ��ܽ�
	local userlevel = GetLevel(sceneId, selfId);
	if userlevel < x300670_g_LevelLess then
		return 0
	end
        -- ��ӡ���Ὠ������˵����
	AddQuestTextNM(sceneId, selfId, targetId, x300670_g_MissionCommentId, 13, -1)

	local GuildId = GetGuildID(sceneId, selfId)
	if GuildId < 0 then
		return 0
	end

	local randMissionId = x300670_GetRandMissionId(sceneId, selfId)
	if randMissionId > 0 then
		if IsHaveQuestNM(sceneId, selfId, randMissionId) > 0 then
			return 0;	--�Ѿ��ӵ��������񣬲���Ҫ����ʾ�տ�������
		end
	end

	local virtualMisId
	if x300670_CountrySceneList[GetCurCountry(sceneId, selfId)+1] == sceneId then
		virtualMisId = x300670_g_VirtualMissionId_Low;
	elseif sceneId == x300670_CapitalSceneId then
		virtualMisId = x300670_g_VirtualMissionId_High;
	else
		return 0;
	end

	--�����ҵȼ����ߣ���ʾһ������İ�Ὠ������ѡ���������ʾ���ȥ�󶼽�����
	if (userlevel >= x300670_LevelToCapital and virtualMisId == x300670_g_VirtualMissionId_Low) then
		AddQuestNumText( sceneId, x300670_g_VirtualMissionId_Low, x300670_g_MissionName, 13)
		return 0;
	end
	--�����û�Ӱ�Ὠ����������ʾ�տ����������
	--����randMissionId����0��˵���Ѿ�����������񣬵����ڱ����������������������û�гɹ��ӵ�
	if QuestCheckAcceptNM( sceneId, selfId, targetId, virtualMisId ) > 0 then
		x300670_AddMissionTextByState(sceneId, selfId, targetId, virtualMisId);
	end

	return ret;
end

--ѡ������
function x300670_ProcEventEntry( sceneId, selfId, targetId, MissionId)

	if MissionId == x300670_g_MissionCommentId then
	-- ��ʾ��Ὠ������˵������
		QuestCom(sceneId, selfId, x300670_g_MissionCommentId)
		x300670_DisplayMissionEventMessage (sceneId, selfId, targetId, MissionId, x300670_g_MissionCommentMessage)		
		return 0;
	end

	x300670_CheckDayChanged (sceneId, selfId)
	local highcircle = x300670_GetMD(sceneId, selfId, MD_BANGHUI_HIGH)
	if highcircle == x300670_HighBonusCircleCount + 1 then
		BeginQuestEvent( sceneId)
			AddQuestText( sceneId, "#Y"..x300670_g_MissionName)
			AddQuestText( sceneId, x300670_g_MissionCommentAfterAbandon )
			DispatchQuestInfoNM( sceneId, selfId, targetId, x300670_g_ScriptId, MissionId, 1)
		EndQuestEvent()
		return 0;
	elseif highcircle >= x300670_HighBonusCircleCount then
		BeginQuestEvent( sceneId)
			AddQuestText( sceneId, "#Y"..x300670_g_MissionName)
			local str = format (x300670_g_MissionCommentAfterEnough, x300670_HighBonusCircleCount) 
			AddQuestText( sceneId, str )
			DispatchQuestInfoNM( sceneId, selfId, targetId, x300670_g_ScriptId, MissionId, 1)
		EndQuestEvent()
		return 0;		
	end

	--�����ҵȼ����ߣ���ʾ���ȥ�󶼽�����
	local userlevel = GetLevel(sceneId, selfId);
	if (userlevel >= x300670_LevelToCapital and MissionId == x300670_g_VirtualMissionId_Low) then
		BeginQuestEvent( sceneId)
			AddQuestText( sceneId, "#Y"..x300670_g_MissionName)
			AddQuestText( sceneId, x300670_g_MissionCommentWrongPlace )
			DispatchQuestInfoNM( sceneId, selfId, targetId, x300670_g_ScriptId, MissionId, 1)
		EndQuestEvent()
		return 0;	
	end

	local ret = 0;
	if x300670_CheckAbandonPenaltyOff (sceneId, selfId, targetId ) <= 0 then
		return 0;
	end

	if MissionId == x300670_g_VirtualMissionId_Low or MissionId == x300670_g_VirtualMissionId_High then	--��ʾ�տ��������
		BeginQuestEvent( sceneId)
		-- ��������
			AddQuestText( sceneId, "#Y"..x300670_g_MissionName)
		--��������
			AddQuestText( sceneId, GetQuestDescNM (sceneId, selfId, MissionId))
			AddQuestText( sceneId, " " )
		--������
			local curlevel = GetLevel(sceneId, selfId)
			local exp = x300670_GetExpAward ( sceneId, selfId, curlevel );
			local money,bangg = x300670_GetMoneyAward ( sceneId, selfId, curlevel );
			local str
			if(exp > 0) then
				AddQuestExpBonus(sceneId, exp)
			end
			if(money > 0) then
				AddQuestMoneyBonus2(sceneId, money)
			end
			if(bangg > 0) then
				AddQuestMoneyBonus8(sceneId, bangg)
			end
		--С��ʾ
			AddQuestText( sceneId, "#c00FF00С��ʾ:" )
			AddQuestText( sceneId, "#c00FF00�����Ҫ�˽Ȿ�����ϸ�ڣ����������������˵����ť��" )
		EndQuestEvent()
		ret = DispatchQuestInfoNM( sceneId, selfId, targetId, x300670_g_ScriptId, MissionId)
		return 0;
	else
		local randMissionId = x300670_GetRandMissionId(sceneId, selfId)
		if randMissionId == 0 or IsHaveQuestNM( sceneId, selfId, randMissionId ) == 0 then	-- ���û�������ֱ���˳�
			return 0
		end
		--������ʾ������Ľ���
		ret = x300670_ShowMissionInfoByState(sceneId, selfId, targetId, randMissionId)
	end
  
	return ret;
end

--�������
--����1����ɹ���0��������ʧ��
function x300670_ProcQuestSubmit( sceneId, selfId, targetId, selectId, MissionId )

	MissionId = x300670_GetRandMissionId(sceneId, selfId);
	if MissionId == nil or MissionId <= 0 then
        	return 0
    	end

	if IsHaveQuestNM( sceneId, selfId, MissionId ) == 0 then	-- ���û�������ֱ���˳�
		return 0
	 end

	local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )

	--�ж�����󻷽ڵ��ύ�����м价�ڵ��ύ
	local ret = 0

	local targetGuid = GetMonsterGUID( sceneId, targetId)
	local reply_npcid = GetQuestSubmitNPCGUIDNM(sceneId, selfId, misIndex)
	if targetGuid == reply_npcid then		--�ڽ������NPC���ύ
		ret = 1
	else
		return 
	end
	
	--��������󻷽ڵ��ύ�ż���ִ��
	if ret == 0 then
		return
	end

	local isFinish = GetQuestParam( sceneId, selfId, misIndex, 7)
	if (isFinish ~= 1) then
		return
	end

	--���㾭��ͽ�Ǯ�Ľ���
	local moneytype = 0;
	local curlevel = GetLevel(sceneId, selfId) 
	local exp = x300670_GetExpAward ( sceneId, selfId, curlevel );
	local money,bangg = x300670_GetMoneyAward ( sceneId, selfId, curlevel );

	--�����������
	ret = CircleQuestComplateNM( sceneId, selfId, targetId, MissionId);
	
	if ret == 1 then -- ����ɹ����
		
		local circle, highcircle = x300670_SetRounds(sceneId, selfId)
		x300670_DisplayCircleMessage (sceneId, selfId, MissionId)
		QuestUnCom( sceneId, selfId, x300670_g_VirtualMissionId_Low)
		QuestUnCom( sceneId, selfId, x300670_g_VirtualMissionId_High)
		x300670_SetMD(sceneId, selfId, MD_BANGHUI_RANDMISSIONID, 0)

		x300670_DisplayCompleteMessage(sceneId, selfId, targetId, MissionId);
		--��������
		if exp > 0 then
			AddExp(sceneId, selfId, exp)
		end
		--������Ǯ
		if money > 0 then
			AddMoney(sceneId, selfId, moneytype, money)
		end
		--������Ǯ
		if bangg > 0 then
			AddGuildUserPoint(sceneId, selfId, bangg)
		end
		--��ʾ��Ǯ�;���Ľ���
		moneytype = 1
		local honorType = 4
		x300670_DisplayAwardInfo(sceneId, selfId, targetId, -1, -1, moneytype, money, exp, honorType, bangg)
		--09.05.08ȡ��������ᾭ��
			--ÿ���һ�ֽ�����ᾭ��1��
			--if (circle == x300670_OneRoundCount) then
			--	GetGuildQuestData(sceneId, selfId, GD_GUILD_INDEX_ADDEXP_DATE, x300670_g_ScriptId,MissionId,"OnCallBackGetAddExpDate",0)
				--x300670_GetItemAwardDirectly ( sceneId, selfId, curlevel );
				--AddCountryResource (sceneId, selfId, 2, 2000, 1);
			--end

	else -- ���δ�ɹ����
		x300670_DisplayCompleteMissionErrorMessage(sceneId, selfId, ret);
		return 0
	end

	return 1;
end
--��ȡ������ϴ�ͨ�����ű����Ӿ��������
function x300670_OnCallBackGetAddExpDate( sceneId, selfId, MissionData, MissionId, targetId )
	
	local curDate = GetDayTime()
	if (curDate ~= MissionData) then
		local GuildId = GetGuildID(sceneId, selfId)
		if GuildId < 0 then
			return
		else
			SetGuildQuestData(sceneId,GuildId,GD_GUILD_INDEX_ADDEXP_VALUE,x300670_AddGuildExpValue)
			SetGuildQuestData(sceneId,GuildId,GD_GUILD_INDEX_ADDEXP_DATE, curDate)
		end
		-- AddGuildExp(sceneId, selfId, x300670_AddGuildExpValue)
		-- local str = format("���İ��������%d�㾭��", x300670_AddGuildExpValue)
		-- Msg2Player(sceneId, selfId, str, 8, 3)
		-- Msg2Player(sceneId, selfId, str, 8, 2)
	else
		GetGuildQuestData(sceneId, selfId, GD_GUILD_INDEX_ADDEXP_VALUE, x300670_g_ScriptId,MissionId,"OnCallBackGetAddExpValue",0)
	end
end

--��ȡ����ᵱ���Ѿ�ͨ�����ű����ӵľ���
function x300670_OnCallBackGetAddExpValue( sceneId, selfId, MissionData, MissionId, targetId )
	
	if MissionData + x300670_AddGuildExpValue > x300670_MaxAddGuildExp then
		return
	end

	local GuildId = GetGuildID(sceneId, selfId)
	if GuildId < 0 then
		return
	end

	SetGuildQuestData(sceneId,GuildId,GD_GUILD_INDEX_ADDEXP_VALUE, MissionData + x300670_AddGuildExpValue)
	-- AddGuildExp(sceneId, selfId, x300670_AddGuildExpValue)
	-- local str = format("���İ��������%d�㾭��", x300670_AddGuildExpValue)
	-- Msg2Player(sceneId, selfId, str, 8, 3)
	-- Msg2Player(sceneId, selfId, str, 8, 2)	
end

--���齱��
function x300670_GetExpAward(sceneId, selfId, startlevel)

	x300670_CheckDayChanged(sceneId, selfId)
	local circle = x300670_GetMD(sceneId, selfId, MD_BANGHUI_CIRCLE)
	--	local highcircle = x300670_GetMD(sceneId, selfId, MD_BANGHUI_HIGH)
	
	circle = circle + 1
	if (circle > x300670_OneRoundCount) then
		circle = 1
	end

	local exp_rate = 	x300670_g_RewardList[circle].exprate
	local BonusExp = startlevel * exp_rate
	--	highcircle = highcircle + 1
	--	if (highcircle <= x300670_HighBonusCircleCount) then
	--		BonusExp = BonusExp * 5
	--	end
	return BonusExp;

end

--��Ǯ����
function x300670_GetMoneyAward(sceneId, selfId, startlevel)

	x300670_CheckDayChanged(sceneId, selfId)	
	local circle = x300670_GetMD(sceneId, selfId, MD_BANGHUI_CIRCLE)	
--	local highcircle = x300670_GetMD(sceneId, selfId, MD_BANGHUI_HIGH)	
--		
	circle = circle + 1	
	if (circle > x300670_OneRoundCount) then	
		circle = 1
	end	
--		
		
	local BonusMoney = 0	
	local bangg = x300670_g_RewardList[circle].bangg
	--	highcircle = highcircle + 1	
	--	if (highcircle <= x300670_HighBonusCircleCount) then	
	--		BonusMoney = BonusMoney * 5
	--		shengw = 25
	--	end	
	return BonusMoney,bangg;	

end
----����ֱ�ӽ���
--function x300670_GetItemAwardDirectly(sceneId, selfId, startlevel)
--
--	local spec;
--	local ret = 0;
--
--	for i, item in x300670_g_ItemAwardCertain do
--		if startlevel >= item.levelMin and startlevel < item.levelMax then
--			local rnum = random(1, item.num);
--			local count = random(1, item.maxcount);
--			ret = x300670_GiveItemToHuman (sceneId, selfId, item.id[rnum], count)
--			if (ret > 0) then
--				Msg2Player(sceneId, selfId, format("#Y���%d����Ʒ#R#{_ITEM%d}#Y�Ľ���", count, item.id[rnum]), 8, 3);
--			end
--			break
--		end
--	end
--	return ret
--end

-- ��ʾ�����Ϣ
function x300670_OnCanCompleteMission ( sceneId, selfId, targetId, MissionId )

	BeginQuestEvent(sceneId);
		--��������
		AddQuestText(sceneId, "#Y"..x300670_g_MissionName)
		--����ύ���ڵ�����
		AddQuestText(sceneId, GetQuestSuccessNM(sceneId, selfId, MissionId))
		--������
		local curlevel = GetLevel(sceneId, selfId)
		local exp = x300670_GetExpAward ( sceneId, selfId, curlevel );
		local money,bangg = x300670_GetMoneyAward ( sceneId, selfId, curlevel );
		if(exp > 0) then
			AddQuestExpBonus(sceneId, exp)
		end
		if(money > 0) then
			AddQuestMoneyBonus2(sceneId, money)
		end
		if(bangg > 0) then
			AddQuestMoneyBonus8(sceneId, bangg)
		end
	EndQuestEvent();
	DispatchQuestContinueInfoNM( sceneId, selfId, targetId, x300670_g_ScriptId, MissionId )
end

--�Ƿ��ڳͷ�ʱ���ڣ�����0��ʾ��Ȼ�ڳͷ�ʱ����
function x300670_CheckAbandonPenaltyOff ( sceneId, selfId, targetId )

	local curMinute = GetMinOfDay() + 1	--��ɴ�1��ʼ
	local curDay = GetDayOfYear()		
	
	local lastday =  x300670_GetMD(sceneId, selfId, MD_BANGHUI_LASTDAY)
	local lastMinute =  x300670_GetMD(sceneId, selfId, MD_BANGHUI_ABANDON)

	if (lastMinute == 0) then --û��������
		return 1;
	end

	local bCanAccept = 1
	if (lastday == curDay) then		--��������󣬻�û���ڶ���
		if (curMinute >= lastMinute)  and  (curMinute - lastMinute < x300670_g_AbandonTime) then 
			bCanAccept = 0
		end
	elseif (curDay - lastday == 1) or (lastday == 365 and curDay == 0) then	--��������󣬵��˵ڶ���
		if 1441 - lastMinute + curMinute <= x300670_g_AbandonTime then
			bCanAccept = 0
		end
	end
	--δ��������������������������Գͷ�ʱ��

	if (bCanAccept == 0) then
		--���ܽ�������
		local str = format("#Y"..x300670_g_MissionName.."#W\n\t�����������%d���ӣ����ܽ�������" , x300670_g_AbandonTime);
		BeginQuestEvent(sceneId);
			AddQuestText(sceneId, str);
		EndQuestEvent(sceneId);
		DispatchQuestEventList(sceneId, selfId, targetId);
		return 0
	end

	--���Խ�������
	if( lastMinute ~= 0 ) then 
		x300670_SetMD(sceneId, selfId, MD_BANGHUI_ABANDON, 0)
	end

	return 1;
end

--��������״̬��ʾ������Ϣ
function x300670_ShowMissionInfoByState( sceneId, selfId, targetId, MissionId )

	if IsHaveQuestNM( sceneId, selfId, MissionId ) == 0 then	-- ���û���������
		local ret = QuestCheckAcceptNM( sceneId, selfId, targetId, MissionId )
		if ret > 0 then	-- ������Խ��������
			if IsQuestFullNM(sceneId, selfId)==1 then
				Msg2Player(sceneId, selfId, "#Y���Ѿ�����̫�������", 8, 3)
				Msg2Player(sceneId, selfId, "#Y���Ѿ�����̫�������", 8, 2)
				return 0
			end
			return x300670_AutoAccept ( sceneId, selfId, targetId, MissionId )
		else
			x300670_DisplayMissionAcceptErrorMessage(sceneId, selfId, ret);
			return 0;
		end
	else --������������
		local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )
		local isFinish = GetQuestParam( sceneId, selfId, misIndex, 7)
		if isFinish == 1 then
			x300670_OnCanCompleteMission ( sceneId, selfId, targetId, MissionId )-- ��ʾ�����Ϣ
		else
			x300670_ShowMissionContinueInfo( sceneId, selfId, targetId, MissionId ) -- ��ʾ����δ�����Ϣ
		end
		return 0;
	end
	
	return 0;
end

function x300670_ShowMissionContinueInfo( sceneId, selfId, targetId, MissionId) -- ��ʾ����δ�����Ϣ

	--��������������Ŀ��npc��
	if x300670_IsDeliver(MissionId) == 1 then --����������м价��
		local targetGuid = GetMonsterGUID( sceneId, targetId)
		local misIndex = GetQuestIndexByID(sceneId, selfId, MissionId);
		local npcdata = GetQuestParam( sceneId, selfId, misIndex, x300670_MisParam_NPCData)
		local finddata = GetQuestParam( sceneId, selfId, misIndex, x300670_MisParam_FindData)
		local j =1
		local findnpc = 0
		local findcount = 0
		local dialog = ""
		for i=1, x300670_g_DeliverTargetCount do

			if i > getn(x300670_g_DeliverTargetNPC) then
				break
			end
			
			local npcindex = floor (mod(npcdata , j*16) / j)				--�����i��Npc�����
			local isNotFind = floor (mod(finddata, j*16) / j)
			if isNotFind == 0 then
				findcount = findcount + 1
			else

				if npcindex < 1 or npcindex > getn(x300670_g_DeliverTargetNPC[i]) then		--û�������ţ�˵�����ݿ�洢�˴�������ݣ��������
					finddata = x300670_ComFindingNPC(i, finddata)				--������NPC
					findcount = findcount + 1
				else										
					local npcid = x300670_g_DeliverTargetNPC[i][npcindex].npcId			--��i��NPC��guid
					if npcid == targetGuid then						--�ҵ������NPC
						finddata = x300670_ComFindingNPC(i, finddata)			--������NPC
						findnpc = 1
						findcount = findcount + 1
						dialog = x300670_g_DeliverTargetNPC[i][npcindex].Dialog
					end
				end
			end
			j = j * 16
		end

		if findnpc == 1 then
			SetQuestByIndex( sceneId, selfId, misIndex, x300670_MisParam_FindData, finddata)

			local str = format("#Y"..x300670_DeliverTextFind, targetGuid, findcount);
			Msg2Player(sceneId, selfId, str, 8, 3)

			if finddata == 0 then									--ȫ�����
				SetQuestByIndex( sceneId, selfId, misIndex, 0, 1)
				SetQuestByIndex( sceneId, selfId, misIndex, 7, 1)
				Msg2Player(sceneId, selfId, "��������ɣ��ر�����������Ա�ɣ�", 8, 3)
			end

			BeginQuestEvent(sceneId);
				--��������
				AddQuestText(sceneId, "#Y"..x300670_g_MissionName)
				--����ɹ����ı�
				AddQuestText(sceneId, dialog)
			EndQuestEvent();
			DispatchQuestInfoNM( sceneId, selfId, targetId, x300670_g_ScriptId, MissionId, 1)
			--DispatchQuestContinueInfoNM( sceneId, selfId, targetId, x300670_g_ScriptId, MissionId )
			x300670_ProcQuestLogRefresh(sceneId, selfId, MissionId)
			return
		end
	end
	
	QuestNotComplateInfoNM( sceneId, selfId, targetId, MissionId ) -- ��ʾ����δ�����Ϣ
end

--���ܿտ�����
function x300670_ProcQuestAccept( sceneId, selfId, targetId, MissionId)

	--�����ҵȼ����ߣ���ʾ���ȥ�󶼽�����
	local userlevel = GetLevel(sceneId, selfId);
	if (userlevel >= x300670_LevelToCapital and MissionId == x300670_g_VirtualMissionId_Low) then
		BeginQuestEvent( sceneId)
			AddQuestText( sceneId, "#Y"..x300670_g_MissionName)
			AddQuestText( sceneId, x300670_g_MissionCommentWrongPlace )
			DispatchQuestInfoNM( sceneId, selfId, targetId, x300670_g_ScriptId, MissionId, 1)
		EndQuestEvent()
		return 0;	
	end

	local randMissionId = x300670_GetRandMissionId(sceneId, selfId)
	if randMissionId == 0 then
		--���һ��������
		local missionType
		randMissionId, missionType = x300670_GenerateRandomMission ( sceneId, selfId, targetId );

	end

	if (randMissionId == 0) then
		return 0;
	end

	--��ʾ��������Ϣ����
	local ret = x300670_ShowMissionInfoByState(sceneId, selfId, targetId, randMissionId)
	return 1;
end

--�Զ�����������
function x300670_AutoAccept( sceneId, selfId, targetId, MissionId )
	--MissionId��������Ч��������
	if IsHaveQuestNM( sceneId, selfId, MissionId ) > 0 then
		return 1
	end
	
	--���ǰ������
	local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId, MissionId )
	if FrontMissiontId1 ~= -1 then
		if IsQuestHaveDoneNM( sceneId, selfId, FrontMissiontId1 ) == 0 then
			return 
		end
	end
	if FrontMissiontId2 ~= -1 then
		if IsQuestHaveDoneNM( sceneId, selfId, FrontMissiontId2 ) == 0 then
			return 
		end
	end
	if FrontMissiontId3 ~= -1 then
		if IsQuestHaveDoneNM( sceneId, selfId, FrontMissiontId3 ) == 0 then
			return
		end
	end

	
	--��������
	local ret
	if x300670_IsDeliver( MissionId ) == 1 then
		ret = AddQuest( sceneId, selfId, MissionId, 300670, 0, 0, 0, 1)
	else
		ret = AddQuestNM( sceneId, selfId, MissionId ) -- ������������
	end
	if ret > 0 then
		x300670_AfterAccept( sceneId, selfId, targetId, MissionId)
	else
		x300670_DisplayAddMissionErrorMessage(sceneId, selfId, ret);
	end
	return ret
end

--ִ�������������õĽ��ܺ���
function x300670_AfterAccept( sceneId, selfId, targetId, MissionId)

	local misIndex = GetQuestIndexByID(sceneId, selfId, MissionId);

	--����NPCͷ����ɫ̾��
	local userlevel = GetLevel(sceneId, selfId)
	local virtualMisId;
	if ( userlevel < x300670_LevelToCapital ) then
		virtualMisId = x300670_g_VirtualMissionId_Low
	else
		virtualMisId = x300670_g_VirtualMissionId_High
	end

	QuestCom( sceneId, selfId, x300670_g_VirtualMissionId_Low)
	QuestCom( sceneId, selfId, x300670_g_VirtualMissionId_High)

	x300670_DisplayAcceptMessage(sceneId, selfId, MissionId);
	for i = 0, 4 do
		local SceneID, PosX, PosZ, tips = GetAskWayPosNM(sceneId, selfId, MissionId, i)
		if SceneID ~= -1 then
			CallScriptFunction( UTILITY_SCRIPT, "AskTheWayPos", sceneId, selfId, SceneID, PosX, PosZ, tips )
		end
	end

	--ִ���������ܺ�������
	
	--��ʾ������Ϣ
	BeginQuestEvent( sceneId)
		-- ��������
		AddQuestText( sceneId, "#Y"..x300670_g_MissionName)
		--��������
		AddQuestText( sceneId, GetQuestDescNM (sceneId, selfId, MissionId))
		AddQuestText( sceneId, " " )
		--����Ŀ��
		AddQuestText( sceneId, "#Y����Ŀ�꣺" )

		if x300670_IsDeliver(MissionId) == 1 then						--���������Ŀ�꣨���֧��8����
			local j = 1
			local npcdata = 0
			local finddata = 0
			for i=1, x300670_g_DeliverTargetCount do
				if i > getn(x300670_g_DeliverTargetNPC) then
					break
				end

				local npcindex = random(1, getn(x300670_g_DeliverTargetNPC[i]))		--�����i��Npc�����
				npcdata = npcdata + npcindex * j					
				finddata = finddata + 1 * j						--��Ϊ1��ʾδ���
				local npcid = x300670_g_DeliverTargetNPC[i][npcindex].npcId			--��i��NPC��guid
				local str = x300670_DeliverMissionTarget.."@npc_"..npcid
				AddQuestText( sceneId, str )

				j = j * 16
			end

			SetQuestByIndex( sceneId, selfId, misIndex, x300670_MisParam_NPCData, npcdata)
			SetQuestByIndex( sceneId, selfId, misIndex, x300670_MisParam_FindData, finddata)

		elseif x300670_IsCollect(MissionId) == 1 then
			--��ʾ�ռ������Ŀ��
			local szTarget1,szTarget2,szTarget3,szTarget4,szTarget5 = GetQuestTargetNM(sceneId, selfId, MissionId)
			if (szTarget1 ~= "") then
				AddQuestText( sceneId, szTarget1 )
			end
			if (szTarget2 ~= "") then
				AddQuestText( sceneId, szTarget2 )
			end
			if (szTarget3 ~= "") then
				AddQuestText( sceneId, szTarget3 )
			end
			if (szTarget4 ~= "") then
				AddQuestText( sceneId, szTarget4 )
			end
			if (szTarget5 ~= "") then
				AddQuestText( sceneId, szTarget5 )
			end
		end
		AddQuestText( sceneId, " ")	--��ʾһ������

	EndQuestEvent()
	       
	DispatchQuestInfoNM( sceneId, selfId, targetId, x300670_g_ScriptId, MissionId, 1)

  --��������Ƿ��ܹ��ύ����
	local ret = 0
	if x300670_IsDeliver(MissionId) == 1 then 
		ret = 0
	elseif x300670_IsCollect(MissionId) == 1 then
		ret = QuestCheckSubmitNM( sceneId, selfId, targetId, MissionId, misIndex ) 
	end

  -- ������ɱ��
	if (ret > 0) then
		SetQuestByIndex( sceneId, selfId, misIndex, 0, 1)
		SetQuestByIndex( sceneId, selfId, misIndex, 7, 1)
	else
		SetQuestByIndex( sceneId, selfId, misIndex, 0, 0)
		SetQuestByIndex( sceneId, selfId, misIndex, 7, 0)
	end

--	local highcircle = x300670_GetMD(sceneId, selfId, MD_BANGHUI_HIGH)
--	if (highcircle == 0) then
--		GamePlayScriptLog(sceneId, selfId, 451)
--	elseif (highcircle == 10) then
--		GamePlayScriptLog(sceneId, selfId, 461)
--	elseif (highcircle == 19) then
--		GamePlayScriptLog(sceneId, selfId, 471)
--	end
		
end

function x300670_SetRounds(sceneId, selfId)

	local highcircle = x300670_GetMD(sceneId, selfId, MD_BANGHUI_HIGH)
	local lastCircle = x300670_GetMD(sceneId, selfId, MD_BANGHUI_CIRCLE)

	--if (highcircle == 0) then
	--	GamePlayScriptLog(sceneId, selfId, 452)
	--elseif (highcircle == 10) then
	--	GamePlayScriptLog(sceneId, selfId, 462)
	--elseif (highcircle == 19) then
	--	GamePlayScriptLog(sceneId, selfId, 472)
	--end

	if highcircle < x300670_HighBonusCircleCount then
		highcircle = highcircle + 1
		x300670_SetMD(sceneId, selfId, MD_BANGHUI_HIGH, highcircle)
	end
	
	if lastCircle >= x300670_OneRoundCount then	
		lastCircle = 1;			--��������
	else						--��������
		lastCircle = lastCircle + 1;
	end	

	x300670_SetMD(sceneId, selfId, MD_BANGHUI_CIRCLE, lastCircle)

	return lastCircle,0
end

function x300670_GetMP(sceneId, selfId, MissionId, constMP)
	local misIndex = GetQuestIndexByID(sceneId, selfId, MissionId);
	return GetQuestParam(sceneId, selfId, misIndex, constMP);
end

function x300670_DisplayAcceptMessage(sceneId, selfId, MissionId)
	local str = format("�����������%s", x300670_g_MissionName);
	Msg2Player(sceneId, selfId, str, 8, 3)
	Msg2Player(sceneId, selfId, str, 8, 2)
	return 1;
end

function x300670_DisplayAddMissionErrorMessage(sceneId, selfId, ret)
	local str;
	if ret == 0 then
		str = "�������ʧ�ܣ�"
	elseif ret == -1 then
		str = "��������,�����������������"
	elseif ret == -2 then
		str = "�����Ѵﵽ���ޣ��޷����µ�����"
	elseif ret == -3 then
		str = "��Ǯ���㣬�޷����µ�����"
	end

	Msg2Player(sceneId, selfId, str, 8, 3)
	return ret;
end

function x300670_DisplayMissionAcceptErrorMessage(sceneId, selfId, ret)

	local str = "δ֪�����޷����µ�����"
	if ret == -1 then
		str = "�ȼ����㣬�޷����µ�����"
	elseif ret == -2 then
		str = "�ȼ����ߣ��޷����µ�����"
	elseif ret == -3 then
		str = "��Ǯ���㣬�޷����µ�����"
	elseif ret == -4 then
		str = "�㲻�Ǳ�����ң��޷����µ�����"
	elseif ret == -5 then
		str = "ְҵ���Ͳ������޷����µ�����"
	elseif ret == -6 then
		str = "��Ӫ�������޷����µ�����"
	elseif ret == -7 then
		str = "�����޴�����"
	end
	
	Msg2Player(sceneId, selfId, str, 8, 3)
	return ret;
	
end

function x300670_ProcQuestLogRefresh( sceneId, selfId, MissionId )

	local misIndex = GetQuestIndexByID(sceneId, selfId, MissionId);
	
	local strName;
	strName = x300670_g_MissionName;
	local circle = x300670_GetMD(sceneId, selfId, MD_BANGHUI_CIRCLE)
	if (circle >= x300670_OneRoundCount) then
		circle = 1
	else
		circle = circle + 1
	end
	strName = strName.."("..circle;
	strName = strName.."/"..x300670_OneRoundCount;
	strName = strName..")";

	local reply_npcid = GetQuestSubmitNPCGUIDNM(sceneId, selfId, misIndex)
	if (reply_npcid < 0) then
		return
	end
	local strReplyNPC = format("@npc_%d", reply_npcid)
	
	BeginQuestEvent(sceneId);
		local szMissionTarget = ""
		if x300670_IsDeliver(MissionId) == 1 then
			--��ʾ�������������״̬
			local npcdata = GetQuestParam( sceneId, selfId, misIndex, x300670_MisParam_NPCData)
			local finddata = GetQuestParam( sceneId, selfId, misIndex, x300670_MisParam_FindData)

			local j = 1
			for i=1, x300670_g_DeliverTargetCount do

				if i > getn(x300670_g_DeliverTargetNPC) then
					break
				end

				local npcindex = floor(mod (npcdata , j*16) / j)						--�����i��Npc�����
				local isNotFind = floor(mod (finddata , j*16) / j)						--�������NPC�Ƿ��Ѿ������
				j = j * 16
				if npcindex < 1 or npcindex > getn(x300670_g_DeliverTargetNPC[i]) then		--û�������ţ�˵�����ݿ�洢�˴�������ݣ������
				
				else										
					local npcid = x300670_g_DeliverTargetNPC[i][npcindex].npcId			--��i��NPC��guid
					if isNotFind == 1 then
						szMissionTarget = szMissionTarget.."  #W"..x300670_DeliverMissionTarget.."@npc_"..npcid.."(0/1)"
					else
						szMissionTarget = szMissionTarget.."  #G"..x300670_DeliverMissionTarget.."@npc_"..npcid.."(1/1)"
					end
					if i < x300670_g_DeliverTargetCount then
						szMissionTarget = szMissionTarget.."\n"
					end
				end
			end
		elseif x300670_IsCollect(MissionId) == 1 then
			--��ʾ�ռ����������״̬
		end

		AddQuestLogCustomText(sceneId, "", strName, szMissionTarget, strReplyNPC, "", "", "");

		--������
		local curlevel = GetLevel(sceneId, selfId)
		local exp = x300670_GetExpAward ( sceneId, selfId, curlevel );
		local money,bangg = x300670_GetMoneyAward ( sceneId, selfId, curlevel );
		if(exp > 0) then
			AddQuestExpBonus(sceneId, exp)
		end
		if(money > 0) then
			AddQuestMoneyBonus2(sceneId, money)
		end
		if(bangg > 0) then
			AddQuestMoneyBonus8(sceneId, bangg)
		end
	EndQuestEvent();
	DispatchQuestLogUpdate(sceneId, selfId, MissionId);
end

function x300670_DisplayCircleMessage(sceneId, selfId, MissionId )

	local circles = x300670_GetMD(sceneId, selfId, MD_BANGHUI_CIRCLE)
	--local highcircle = x300670_GetMD(sceneId, selfId, MD_BANGHUI_HIGH)

	local str = format( "����: %d/%d", circles, x300670_OneRoundCount );
	--if highcircle <= x300670_HighBonusCircleCount then
	--	str = str..format("  ���ո߽�������%d/%d", highcircle, x300670_HighBonusCircleCount);
	--end
	Msg2Player(sceneId, selfId, str, 8, 3)

end

function x300670_DisplayCompleteMessage(sceneId, selfId, targetId, MissionId)
	
	local MissionName = x300670_g_MissionName;
	local str = format( "�����������%s", MissionName);

	Msg2Player(sceneId, selfId, str, 8, 3)
	return 1;

end

function x300670_DisplayAwardInfo(sceneId, selfId, targetId, MissionId, selectId, moneyType, money, expAward, honorType, honor)--��ʾ��ҽ�Ǯ���������Ľ�����Ϣ
	
	if MissionId >= 0 then
		moneyType, money, expAward, honorType, honor = AwardMoneyExpHonorNM(sceneId, selfId, targetId, MissionId, selectId)
	end
	local str;

	if expAward > 0 then
		str = format("#Y���#R����%d#Y�Ľ�����", expAward);
		Msg2Player(sceneId, selfId, str, 8, 2)
	end

	if money > 0 then
		if moneyType == 0 then --��
			str = format("#Y���#R����#{_MONEY%d}#Y�Ľ�����", money);
		elseif moneyType == 1 then -- ����
			str = format("#Y���#R����#{_MONEY%d}#Y�Ľ�����", money);
		elseif moneyType == 2 then --��
			str = format("#Y���#R�ֽ�#{_MONEY%d}#Y�Ľ�����", money);
		elseif moneyType == 3 then -- �󶨽�
			str = format("#Y���#R��#{_MONEY%d}#Y�Ľ�����", money);
		end

		Msg2Player(sceneId, selfId, str, 8, 2)
	end

	if honor > 0 then
		if honorType == 0 then --����
			str = format("#Y���#R����%d#Y�Ľ�����", honor);
		elseif honorType == 1 then	--����
			str = format("#Y���#R����%d#Y�Ľ�����", honor);
		elseif honorType == 2 then --PK
			str = format("#Y���#RPKֵ%d#Y�Ľ�����", honor);
		elseif honorType == 3 then --����
			str = format("#Y���#R����%d#Y�Ľ�����", honor);
		elseif honorType == 4 then -- �ﹱ
			str = format("#Y���#R�ﹱ%d#Y�Ľ�����", honor);
		elseif honorType == 5 then -- �Ĳ�
			str = format("#Y���#R�Ĳ�%d#Y�Ľ�����", honor);
		end

		Msg2Player(sceneId, selfId, str, 8, 2)
	end
	return 1;

end


function x300670_DisplayCompleteMissionErrorMessage(sceneId, selfId, ret)
	
	local str = "δ֪�����޷��������"
	if ret == -2 then
		str = "��ѡ������Ʒ��"
	elseif ret == -3 then
		str = "��������,�����������������"
	elseif ret == -4 then
		str = "�۳�������Ʒʧ�ܣ�"
	end

	Msg2Player(sceneId, selfId, str, 8, 3)
	return ret;

end

function x300670_PushAfterMission(sceneId, selfId, targetId, MissionId )
	return 1;
end

--�������--������Ҫ���÷���ʱ��MissionData
function x300670_ProcQuestAbandon( sceneId, selfId, MissionId )

	MissionId = x300670_GetRandMissionId(sceneId, selfId);
	if (MissionId == 0 or IsHaveQuestNM( sceneId, selfId, MissionId ) == 0 ) then
		--����ͬʱ���˶����Ὠ������������,�����а�Ὠ������ɾ��
		x300670_DelAllWrongMission(sceneId, selfId)
		return 0
	end
	local ret = 0

	local  misIndex = GetQuestIndexByID(sceneId, selfId, MissionId);
	ret = DelQuestNM( sceneId, selfId, MissionId )
	if ret == 1 then

		QuestUnCom( sceneId, selfId, x300670_g_VirtualMissionId_Low)
		--QuestUnCom( sceneId, selfId, x300670_g_VirtualMissionId_High)
		x300670_SetMD(sceneId, selfId, MD_BANGHUI_LASTDAY, GetDayOfYear())
		x300670_SetMD(sceneId, selfId, MD_BANGHUI_ABANDON, GetMinOfDay()+1)

		--�������������
		x300670_SetMD(sceneId, selfId, MD_BANGHUI_RANDMISSIONID, 0)
		x300670_SetMD(sceneId, selfId, MD_BANGHUI_CIRCLE, 0)
		x300670_SetMD(sceneId, selfId, MD_BANGHUI_HIGH, x300670_HighBonusCircleCount + 1)
		x300670_DisplayAbandonMessage(sceneId, selfId, MissionId);
	end
	return ret;
end

function x300670_DelAllWrongMission(sceneId, selfId)
	--����ͬʱ���˶����Ὠ������������,�����а�Ὠ������ɾ��
	local level = GetLevel(sceneId, selfId)
	for i, setitem in x300670_g_MissionIdList do
		if level >= setitem.level.min then
			for j, idarray in setitem.MissionId do
				for m, id in idarray do
					if IsHaveQuestNM( sceneId, selfId, id ) > 0 then
						DelQuestNM( sceneId, selfId, id )
					end
				end
			end
		end
	end
end

function x300670_DisplayAbandonMessage(sceneId, selfId, MissionId)
	local MissionName = x300670_g_MissionName;
	local str = format("�����������%s��", MissionName);

	Msg2Player(sceneId, selfId, str, 8, 3)
	Msg2Player(sceneId, selfId, str, 8, 2)
	return 1;
end

function x300670_ProcQuestAttach( sceneId, selfId, targetId, npcGuid, misIndex, MissionId )
	
	--�ھ򡢻��������񲻻�����������Լ��Ľű�
	MissionId = x300670_GetRandMissionId(sceneId, selfId);
	if (MissionId == 0) then
		return 0
	end

	if IsHaveQuestNM( sceneId, selfId, MissionId ) == 0 then	-- ���û���������
		return 0
	end

	local misIndex = GetQuestIndexByID(sceneId, selfId, MissionId);
	--�������񣬵��������Ŀ��ʱ�������û���ˣ���ʾ��Ὠ�������ѡ��
	if x300670_IsDeliver(MissionId) == 1 then --�����������⴦��

		--��ʾ�������������״̬
		local npcdata = GetQuestParam( sceneId, selfId, misIndex, x300670_MisParam_NPCData)
		local finddata = GetQuestParam( sceneId, selfId, misIndex, x300670_MisParam_FindData)
		local j =1
		for i=1, x300670_g_DeliverTargetCount do

			if i > getn(x300670_g_DeliverTargetNPC) then
				break
			end

			local npcindex = floor(mod (npcdata , j*16) / j)					--�����i��Npc�����
			local isNotFind = floor (mod (finddata , j*16) / j)					--�������NPC�Ƿ��Ѿ������
			j = j * 16
			if npcindex < 1 or npcindex > getn(x300670_g_DeliverTargetNPC[i]) then		--û�������ţ�˵�����ݿ�洢�˴�������ݣ������
			
			else										
				local npcid = x300670_g_DeliverTargetNPC[i][npcindex].npcId			--��i��NPC��guid
				if npcid == npcGuid and isNotFind == 1 then				--�Ƿ�Ӧ�ðѱ��������ѡ��
					AddQuestNumText( sceneId, MissionId, x300670_g_MissionName, 13)
					return 1
				end
			end
		end
	end

	local submitguid = GetQuestSubmitNPCGUIDNM( sceneId, selfId, misIndex )

	--����������ύ�ˣ���ʾѡ��
	if submitguid ~= -1 and submitguid == npcGuid then	
		x300670_AddMissionTextByState(sceneId, selfId, targetId, MissionId);
		return 1
	end

	return 0
end

function x300670_AddMissionTextByState(sceneId, selfId, NPCId, MissionId)
	local state = GetQuestStateNM(sceneId, selfId, NPCId, MissionId);
	return AddQuestTextNM(sceneId, selfId, NPCId, MissionId, state, -1);
end

function x300670_DisplayMissionEventMessage(sceneId, selfId, targetId, MissionId, contentStr)

	local MissionName;
	if MissionId > 0 then
		MissionName = x300670_g_MissionName;
	end
	
	local str = "#Y";
	if MissionName ~= nil then
		str = str..MissionName;
	end
	str = str.."#W\n\n"..contentStr;

	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, str)
	EndQuestEvent(sceneId)

	DispatchQuestEventList(sceneId, selfId, targetId);

end

function x300670_SetMP(sceneId, selfId, MissionId, constMP, Value)
	local misIndex = GetQuestIndexByID(sceneId, selfId, MissionId);
	return SetQuestByIndex(sceneId, selfId, misIndex, constMP, Value);
end

--ɱ���¼�����
function x300670_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId)
end

--��Ʒ�ı�
function x300670_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )

	MissionId = x300670_GetRandMissionId(sceneId, selfId);
	if (MissionId == 0) then
		return 0
	end

	if IsHaveQuestNM(sceneId, selfId, MissionId) == 0 then
		return 0
	end
	local NeedNum, ObjIndex = GetQuestNeedItemNumNM( sceneId, selfId, MissionId, itemdataId )

	if NeedNum > 0 then
		local Num = GetItemCount( sceneId, selfId, itemdataId )
		x300670_DisplayMissionGetItemMessage(sceneId, selfId, itemdataId, MissionId, ObjIndex, Num, NeedNum)
		if Num < NeedNum then --��û���������
			x300670_SetMP(sceneId, selfId, MissionId, ObjIndex, Num);
			x300670_SetMP(sceneId,selfId,MissionId,7,0)
		elseif Num >= NeedNum then
			if x300670_GetMP(sceneId,selfId,MissionId,7) == 1 then	--֮ǰ�Ѿ������
				return 0
			end
			x300670_SetMP(sceneId, selfId, MissionId, ObjIndex, NeedNum);
			x300670_SetMP(sceneId,selfId,MissionId,7,1)
			Msg2Player(sceneId, selfId, "�����Ѿ���ɣ�����ȥ�㱨�ɣ�", 8, 3)
		end
	end
	return 0
end

function x300670_DisplayMissionGetItemMessage(sceneId, selfId, itemId, MissionId, ObjIndex, Num, NeedNum)

	local str = "";
	local ret = 1;
	local oldNum = x300670_GetMP(sceneId, selfId, MissionId, ObjIndex);
	if Num < NeedNum then
		if(Num < oldNum) then
			str = "";
		elseif (Num > oldNum) then
			str = format("#Y�����Ʒ#G#{_ITEM%d}#Y: %d/%d", itemId, Num, NeedNum );
		end
		ret = 0;
	elseif Num == NeedNum then
		str = format( "#Y����ɻ����Ʒ#G#{_ITEM%d}#Y: %d/%d", itemId, Num, NeedNum )
	end
	if str ~= "" then
		Msg2Player(sceneId, selfId, str, 8, 3)
	end
	return ret;

end

--����ʱ��
function x300670_ProcTiming( sceneId, selfId, ScriptId, MissionId )
	return 1;
end

--��
function x300670_OnProcOver( sceneId, selfId, targetId )
	return 1
end

--�򿪺���
function x300670_OpenCheck( sceneId, selfId, targetId )
	return 1
end

function x300670_SetMD(sceneId, selfId, MDNAME, value)
	SetQuestData(sceneId, selfId, MDNAME[1], MDNAME[2], MDNAME[3], value);
end

function x300670_GetMD(sceneId, selfId, MDNAME)

	return GetQuestData(sceneId, selfId, MDNAME[1], MDNAME[2], MDNAME[3])
end

function x300670_GiveItemToHuman(sceneId, selfId, ItemID, count)

	BeginAddItem(sceneId)
	AddItem( sceneId, ItemID, count )
	local ret = EndAddItem(sceneId,selfId)
	if ret > 0 then
		AddItemListToPlayer(sceneId,selfId)
	else
		local str = "�����������޷��õ���Ʒ��";
		Msg2Player(sceneId, selfId, str, 8, 3);
		Msg2Player(sceneId, selfId, str, 8, 2)
	end
	return ret
end

--���������û�б仯�������ø߽��������������µ�����
function x300670_CheckDayChanged(sceneId, selfId)
	local lastDay = x300670_GetMD(sceneId, selfId, MD_BANGHUI_LASTDAY)
	local today = GetDayOfYear()
	if lastDay ~= today then	--���ڱ仯
		x300670_SetMD(sceneId, selfId, MD_BANGHUI_LASTDAY, today)	
		x300670_SetMD(sceneId, selfId, MD_BANGHUI_HIGH, 0)
	end
end

function x300670_IsDeliver(MissionId)
	if MissionId == 9030 then
		return 1
	else
		return 0
	end
end

function x300670_IsCollect(MissionId)
	if MissionId >= 10001 and MissionId <=10258 then
		return 1
	else
		return 0
	end	
end

function x300670_ComFindingNPC( TargetIndex, finddata )
	if TargetIndex < 1 or TargetIndex > x300670_g_DeliverTargetCount then
		return finddata
	end

	local time_a = 1
	local time_b = 1
	
	if TargetIndex < 8 then
		for i = 1, TargetIndex do
			time_a = time_a * 16
		end
	end
	for i = 1, TargetIndex - 1 do
		time_b = time_b * 16
	end
	
	local left
	if TargetIndex >= 8 then
		left = 0
	else
		left = finddata - mod (finddata , time_a)
	end

    local right
	if TargetIndex == 1 then
		right = 0
	else
		right = mod (finddata , time_b)
	end
	return left + right
end