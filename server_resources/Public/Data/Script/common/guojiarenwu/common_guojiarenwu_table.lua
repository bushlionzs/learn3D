--MD_GUOJIARENWU_RANDMISSIONID	= {2, 0, 18}
--MD_GUOJIARENWU_RANDMISSIONTYPE  = {2, 18, 4}	--��֤ÿ�ι�����������������Ͳ�ͬ
--MD_GUOJIARENWU_LASTDAY	= {2, 22, 9}	--�ϴν��������ڻ�������������

--MD_GUOJIARENWU_CIRCLE		= {3, 0, 6}	--���ֻ����ļ���
--MD_GUOJIARENWU_HIGH		= {3, 6, 8}	--����߶���ļ���
--MD_GUOJIARENWU_ABANDON		= {3, 14, 12}	--���һ�η���ʱ��

x300501_g_ScriptId = 300501
x300501_g_AbandonTime = 5
-- ��������
x300501_g_MissionName = "�����ˡ���������"

x300501_g_MissionCommentId	=	1100
x300501_g_VirtualMissionId_Low	=	1361
x300501_g_VirtualMissionId_High	=	1364
x300501_g_MissionRangeStart	=	6080
x300501_g_MissionRangeEnd		= 6499
x300501_g_MissionCommentMessage	=	"\t������Ϊ25�����ϵ���ҿ��ţ�ÿ��������#G20��#W���񣬵�ѡ����ť���㽫���һ����������񣬽���ͨ���������򵥵�������������ȡ�����ľ��顣\n\tÿ10������Ϊһ�֣�ÿ�յ�#Rǰ10��#W�㽫���#G�߱�����#W��������ÿ�����һ������֮�������һ��#R��ϲ#W��һ���У�ÿ�λ�õľ��鶼Ҳ���ǲ�ͬ�ġ�\n\t��Ȼ��������ÿ��������ô���ɿ�����ɣ�������ò�Ҫ�������񣬷����������󽫻���#R5���Ӳ��ܽ�ȡ����#W�ĳͷ������ң����յ�#R�߱�������������ʧ#W�����ջ��۵�#R������������#W����õĽ����ͻ�һ��ǧ���ˡ�"
x300501_g_MissionCommentWrongPlace =    "\t���㵽���������񷢲��ٴ�������"
x300501_g_MissionCommentCountOver =     "���������������첻���ٽ����������"
x300501_g_MissionNPCObjId_Low		= 138562
x300501_g_MissionNPCObjId_High		= 139127
x300501_g_LevelLess             = 25

x300501_OneRoundCount = 10		--ÿ�ֶ��ٻ�
x300501_HighBonusCircleCount = 10	--ÿ�ռ��ָ߽�

-- ��������ID
x300501_g_CollectHorse_Mission_ID	= 6430
x300501_g_CollectHorse_Mission_ID_End   = 6446
x300501_g_CollectHorse_Young		= 6445
-- �ھ�����ID
x300501_g_DigMissionID              = 6470
x300501_g_DigMissionID_End          = 6479
-- ��������ID
x300501_g_EscortMissionID           = 6450
x300501_g_EscortMissionID_End       = 6461
-- ��������ID
x300501_g_DeliverMissionID           = 6350
x300501_g_DeliverMissionID_End       = 6386
x300501_g_DeliverItemID			= 13011600
x300501_g_DeliverItemCount		= 1
x300501_CountrySceneList	= {50, 150, 250, 350}
x300501_CapitalSceneId		= 0
x300501_LevelToCapital		= 300	--������Ŀ�ʼ�ȼ�

x300501_g_DeliverTargetNPC				= { 
								{missionID=6350, npcID=138540}, {missionID=6351, npcID=138541}, {missionID=6352, npcID=138500}, {missionID=6353, npcID=138502},
								{missionID=6354, npcID=138506}, {missionID=6355, npcID=138005}, {missionID=6356, npcID=138022}, {missionID=6357, npcID=138110},
								{missionID=6358, npcID=138584}, {missionID=6359, npcID=138813}, {missionID=6360, npcID=138605}, {missionID=6361, npcID=138113},
								{missionID=6362, npcID=138114}, {missionID=6363, npcID=138255}, {missionID=6364, npcID=138108}, {missionID=6365, npcID=138116},
								{missionID=6366, npcID=138258},

								}
x300501_g_ItemAwardCertain				=	{
															{levelMin=20, levelMax=30, num=1, maxcount=3, id={11000200}},
															{levelMin=30, levelMax=40, num=1, maxcount=3, id={11000200}},
															{levelMin=40, levelMax=50, num=1, maxcount=3, id={11000201}},
															{levelMin=50, levelMax=60, num=1, maxcount=3, id={11000201}},
															{levelMin=60, levelMax=70, num=1, maxcount=3, id={11000202}},
															{levelMin=70, levelMax=80, num=1, maxcount=3, id={11000202}},
															{levelMin=80, levelMax=90, num=1, maxcount=3, id={11000202}},
															{levelMin=90, levelMax=100, num=1, maxcount=3, id={11000202}},
															{levelMin=100, levelMax=110, num=1, maxcount=3, id={11000202}},
															{levelMin=110, levelMax=9999, num=1, maxcount=3, id={11000202}},
														}

x300501_g_DefaultMissionId	=	6080
--��7��̶�Ϊ����������ע��
x300501_g_MissionIdList	=	{
														{
															level	=	{	min=25,	max=30	},
															rate	=	{	15,	25,	45,	55,	73,	75,	85,	95,	100	},
															MissionId	=	{
																						{	6080,	6081,	6082,	6083,	6084,	6085,	6086,	6087,	6088,	6089,	6090,	6091	},
																						{	6260	},
																						{	6350,	6351,	6352,	6353,	6354,	6355,	6356,	6357,	6358,	6359,	6360	},
																						{	6410,	6412,	6413	},
																						{	6420	},
																						{	6430	},
																						{	6450,	6451	},
																						{	6470,	6471,	6472,	6473,	6474	},
																						{	6445	},
																					}
														},
														{
															level	=	{	min=30,	max=35	},
															rate	=	{	15,	25,	45,	55,	73,	75,	85,	95,	100	},
															MissionId	=	{
																						{	6080,	6081,	6082,	6083,	6084,	6085,	6086,	6087,	6088,	6089,	6090,	6091,	6181	},
																						{	6260,	6263	},
																						{	6350,	6351,	6352,	6353,	6354,	6355,	6356,	6357,	6358,	6359,	6360,	6361,	6362,	6363	},
																						{	6410,	6411,	6412,	6413	},
																						{	6420	},
																						{	6431,	},
																						{	6450,	6451,	6452,	6453	},
																						{	6470,	6471,	6472,	6473,	6474	},
																						{	6445	},
																					}
														},
														{
															level	=	{	min=35,	max=40	},
															rate	=	{	15,	25,	45,	55,	73,	75,	85,	95,	100	},
															MissionId	=	{
																						{	6080,	6081,	6082,	6083,	6084,	6085,	6086,	6087,	6088,	6089,	6090,	6091,	6181	},
																						{	6260,	6263,	6266	},
																						{	6350,	6351,	6352,	6353,	6354,	6355,	6356,	6357,	6358,	6359,	6360,	6361,	6362,	6363,	6364,	6365,	6366	},
																						{	6410,	6411,	6412,	6413	},
																						{	6420	},
																						{	6431,	},
																						{	6450,	6451,	6452,	6453,	6454,	6455	},
																						{	6470,	6471,	6472,	6473,	6474	},
																						{	6445	},
																					}
														},
														{
															level	=	{	min=40,	max=45	},
															rate	=	{	15,	25,	45,	55,	73,	75,	85,	95,	100	},
															MissionId	=	{
																						{	6092,	6093,	6094,	6095,	6096,	6097,	6098,	6099,	6100,	6101,	6102,	6103,	6182	},
																						{	6260,	6263,	6266,	6269	},
																						{	6350,	6351,	6352,	6353,	6354,	6355,	6356,	6357,	6358,	6359,	6360,	6361,	6362,	6363,	6364,	6365,	6366	},
																						{	6410,	6411,	6412,	6413	},
																						{	6420	},
																						{	6432,	},
																						{	6450,	6451,	6452,	6453,	6454,	6455	},
																						{	6470,	6471,	6472,	6473,	6474	},
																						{	6446	},
																					}
														},
														{
															level	=	{	min=45,	max=50	},
															rate	=	{	15,	25,	45,	55,	73,	75,	85,	95,	100	},
															MissionId	=	{
																						{	6092,	6093,	6094,	6095,	6096,	6097,	6098,	6099,	6100,	6101,	6102,	6103,	6182	},
																						{	6260,	6263,	6266,	6269,	6272	},
																						{	6350,	6351,	6352,	6353,	6354,	6355,	6356,	6357,	6358,	6359,	6360,	6361,	6362,	6363,	6364,	6365,	6366	},
																						{	6410,	6411,	6412,	6413	},
																						{	6420	},
																						{	6432,	},
																						{	6450,	6451,	6452,	6453,	6454,	6455	},
																						{	6470,	6471,	6472,	6473,	6474	},
																						{	6446	},
																					}
														},
														{
															level	=	{	min=50,	max=55	},
															rate	=	{	15,	25,	45,	55,	73,	75,	85,	95,	100	},
															MissionId	=	{
																						{	6092,	6093,	6094,	6095,	6096,	6097,	6098,	6099,	6100,	6101,	6102,	6103,	6183	},
																						{	6260,	6263,	6266,	6269,	6272,	6275	},
																						{	6350,	6351,	6352,	6353,	6354,	6355,	6356,	6357,	6358,	6359,	6360,	6361,	6362,	6363,	6364,	6365,	6366	},
																						{	6410,	6411,	6412,	6413	},
																						{	6420	},
																						{	6433,	},
																						{	6450,	6451,	6452,	6453,	6454,	6455	},
																						{	6470,	6471,	6472,	6473,	6474	},
																						{	6446	},
																					}
														},
														{
															level	=	{	min=55,	max=60	},
															rate	=	{	15,	25,	45,	55,	73,	75,	85,	95,	100	},
															MissionId	=	{
																						{	6092,	6093,	6094,	6095,	6096,	6097,	6098,	6099,	6100,	6101,	6102,	6103,	6183	},
																						{	6260,	6263,	6266,	6269,	6272,	6275,	6278	},
																						{	6350,	6351,	6352,	6353,	6354,	6355,	6356,	6357,	6358,	6359,	6360,	6361,	6362,	6363,	6364,	6365,	6366	},
																						{	6410,	6411,	6412,	6413	},
																						{	6420	},
																						{	6433,	},
																						{	6450,	6451,	6452,	6453,	6454,	6455	},
																						{	6470,	6471,	6472,	6473,	6474	},
																						{	6446	},
																					}
														},
														{
															level	=	{	min=60,	max=65	},
															rate	=	{	15,	25,	45,	55,	73,	75,	85,	95,	100	},
															MissionId	=	{
																						{	6092,	6093,	6094,	6095,	6096,	6097,	6098,	6099,	6100,	6101,	6102,	6103,	6183	},
																						{	6260,	6263,	6266,	6269,	6272,	6275,	6278,	6281	},
																						{	6350,	6351,	6352,	6353,	6354,	6355,	6356,	6357,	6358,	6359,	6360,	6361,	6362,	6363,	6364,	6365,	6366	},
																						{	6410,	6411,	6412,	6413	},
																						{	6420	},
																						{	6434,	},
																						{	6450,	6451,	6452,	6453,	6454,	6455	},
																						{	6470,	6471,	6472,	6473,	6474	},
																						{	6446	},
																					}
														},
														{
															level	=	{	min=65,	max=70	},
															rate	=	{	15,	25,	45,	55,	73,	75,	85,	95,	100	},
															MissionId	=	{
																						{	6092,	6093,	6094,	6095,	6096,	6097,	6098,	6099,	6100,	6101,	6102,	6103,	6183	},
																						{	6260,	6263,	6266,	6269,	6272,	6275,	6278,	6281,	6284	},
																						{	6350,	6351,	6352,	6353,	6354,	6355,	6356,	6357,	6358,	6359,	6360,	6361,	6362,	6363,	6364,	6365,	6366	},
																						{	6410,	6411,	6412,	6413	},
																						{	6420	},
																						{	6434,	},
																						{	6450,	6451,	6452,	6453,	6454,	6455	},
																						{	6470,	6471,	6472,	6473,	6474	},
																						{	6446	},
																					}
														},
														{
															level	=	{	min=70,	max=75	},
															rate	=	{	15,	25,	45,	55,	73,	75,	85,	95,	100	},
															MissionId	=	{
																						{	6092,	6093,	6094,	6095,	6096,	6097,	6098,	6099,	6100,	6101,	6102,	6103,	6183	},
																						{	6260,	6263,	6266,	6269,	6272,	6275,	6278,	6281,	6284,	6287	},
																						{	6350,	6351,	6352,	6353,	6354,	6355,	6356,	6357,	6358,	6359,	6360,	6361,	6362,	6363,	6364,	6365,	6366	},
																						{	6410,	6411,	6412,	6413	},
																						{	6420	},
																						{	6435,	},
																						{	6450,	6451,	6452,	6453,	6454,	6455	},
																						{	6470,	6471,	6472,	6473,	6474	},
																						{	6446	},
																					}
														},
														{
															level	=	{	min=75,	max=80	},
															rate	=	{	15,	25,	45,	55,	73,	75,	85,	95,	100	},
															MissionId	=	{
																						{	6092,	6093,	6094,	6095,	6096,	6097,	6098,	6099,	6100,	6101,	6102,	6103,	6183	},
																						{	6260,	6263,	6266,	6269,	6272,	6275,	6278,	6281,	6284,	6287,	6290	},
																						{	6350,	6351,	6352,	6353,	6354,	6355,	6356,	6357,	6358,	6359,	6360,	6361,	6362,	6363,	6364,	6365,	6366	},
																						{	6410,	6411,	6412,	6413	},
																						{	6420	},
																						{	6435,	},
																						{	6450,	6451,	6452,	6453,	6454,	6455	},
																						{	6470,	6471,	6472,	6473,	6474	},
																						{	6446	},
																					}
														},
														{
															level	=	{	min=80,	max=90	},
															rate	=	{	15,	25,	45,	55,	73,	75,	85,	95,	100	},
															MissionId	=	{
																						{	6092,	6093,	6094,	6095,	6096,	6097,	6098,	6099,	6100,	6101,	6102,	6103,	6183	},
																						{	6260,	6263,	6266,	6269,	6272,	6275,	6278,	6281,	6284,	6287,	6290,	6293	},
																						{	6350,	6351,	6352,	6353,	6354,	6355,	6356,	6357,	6358,	6359,	6360,	6361,	6362,	6363,	6364,	6365,	6366	},
																						{	6410,	6411,	6412,	6413	},
																						{	6420	},
																						{	6436,	},
																						{	6450,	6451,	6452,	6453,	6454,	6455	},
																						{	6470,	6471,	6472,	6473,	6474	},
																						{	6446	},
																					}
														},
														{
															level	=	{	min=90,	max=100	},
															rate	=	{	15,	25,	45,	55,	73,	75,	85,	95,	100	},
															MissionId	=	{
																						{	6092,	6093,	6094,	6095,	6096,	6097,	6098,	6099,	6100,	6101,	6102,	6103,	6183	},
																						{	6260,	6263,	6266,	6269,	6272,	6275,	6278,	6281,	6284,	6287,	6290,	6293	},
																						{	6350,	6351,	6352,	6353,	6354,	6355,	6356,	6357,	6358,	6359,	6360,	6361,	6362,	6363,	6364,	6365,	6366	},
																						{	6410,	6411,	6412,	6413	},
																						{	6420	},
																						{	6437,	},
																						{	6450,	6451,	6452,	6453,	6454,	6455	},
																						{	6470,	6471,	6472,	6473,	6474	},
																						{	6446	},
																					}
														},
														{
															level	=	{	min=100, max=110	},
															rate	=	{	15,	25,	45,	55,	73,	75,	85,	95,	100	},
															MissionId	=	{
																						{	6092,	6093,	6094,	6095,	6096,	6097,	6098,	6099,	6100,	6101,	6102,	6103,	6183	},
																						{	6260,	6263,	6266,	6269,	6272,	6275,	6278,	6281,	6284,	6287,	6290,	6293	},
																						{	6350,	6351,	6352,	6353,	6354,	6355,	6356,	6357,	6358,	6359,	6360,	6361,	6362,	6363,	6364,	6365,	6366	},
																						{	6410,	6411,	6412,	6413	},
																						{	6420	},
																						{	6438,	},
																						{	6450,	6451,	6452,	6453,	6454,	6455	},
																						{	6470,	6471,	6472,	6473,	6474	},
																						{	6446	},
																					}
														},
														{
															level	=	{	min=110, max=9999	},
															rate	=	{	15,	25,	45,	55,	73,	75,	85,	95,	100	},
															MissionId	=	{
																						{	6092,	6093,	6094,	6095,	6096,	6097,	6098,	6099,	6100,	6101,	6102,	6103,	6183	},
																						{	6260,	6263,	6266,	6269,	6272,	6275,	6278,	6281,	6284,	6287,	6290,	6293	},
																						{	6350,	6351,	6352,	6353,	6354,	6355,	6356,	6357,	6358,	6359,	6360,	6361,	6362,	6363,	6364,	6365,	6366	},
																						{	6410,	6411,	6412,	6413	},
																						{	6420	},
																						{	6438,	},
																						{	6450,	6451,	6452,	6453,	6454,	6455	},
																						{	6470,	6471,	6472,	6473,	6474	},
																						{	6446	},
																					}
														},
													}

function x300501_GenerateRandomMission(sceneId, selfId, targetId)

	local MissionId = x300501_g_DefaultMissionId;
	local level = GetLevel(sceneId, selfId);
	local oldtype = x300501_GetMD(sceneId, selfId, MD_GUOJIARENWU_RANDMISSIONTYPE)
	local newtype = 0;
	while 1 do
		local randval = random(0, 99);

		for i, setitem in x300501_g_MissionIdList do
			if level >= setitem.level.min and level < setitem.level.max then
				for j, rateitem in setitem.rate do
					if randval < rateitem then
						newtype = j;
						break;
					end
				end
				randval = random(1, getn(setitem.MissionId[newtype]));
				MissionId = setitem.MissionId[newtype][randval];
				break;
			end
		end

		if newtype == 0 then	--δ�ҵ�������ҵȼ�������
			return 0;
		end

		if IsBusMember(sceneId, selfId) == 0 or newtype ~= 7 then	--����Լ��Ѿ����ڳ��������ٽӻ�������
			if newtype ~= oldtype then
				break;
			end
		end
	end

	--local countryplus = GetCurCountry(sceneId, selfId) * x300501_g_MissionIDCountryPlus;
	--MissionId = MissionId + countryplus;
	if MissionId < x300501_g_MissionRangeStart or MissionId > x300501_g_MissionRangeEnd then
		MissionId = x300501_g_MissionRangeStart;
	end
	
--	local GMSetId = GetQuestParam(sceneId, selfId, 19, 6)
--	if (GMSetId >= x300501_g_MissionRangeStart and GMSetId <= x300501_g_MissionRangeEnd) then
--		MissionId = GMSetId
--	end
	--MissionId = 6479	--�ھ�
	--MissionId = 6434	--����
	--MissionId = 6262	--����
	--MissionId = 6456	--����
	--MissionId = 6420	--����
	--MissionId = 6386	--����
	--MissionId = 6100	--����
	--MissionId = 6410	--�ɼ�

	x300501_SetMD (sceneId, selfId, MD_GUOJIARENWU_RANDMISSIONID, MissionId)
	x300501_SetMD (sceneId, selfId, MD_GUOJIARENWU_RANDMISSIONTYPE, newtype)
	return MissionId, newtype;
end

function x300501_GetRandMissionId(sceneId, selfId)
	return x300501_GetMD(sceneId, selfId, MD_GUOJIARENWU_RANDMISSIONID)
end

function x300501_ProcAcceptCheck(sceneId, selfId, targetId, MissionId)

	MissionId = x300501_GetRandMissionId(sceneId, selfId);

	if IsHaveQuestNM(sceneId, selfId, MissionId) > 0 then
		return 0;
	end
	return 1;

end

function x300501_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

	local ret = 0;

	
	--x300501_SetMD(sceneId, selfId, MD_GUOJIARENWU_HIGH, 0)
	--x300501_SetMD(sceneId, selfId, MD_GUOJIARENWU_LASTDAY, 0)
	--x300501_SetMD(sceneId, selfId, MD_GUOJIARENWU_ABANDON, 0)

	--���ڹ涨��С�ȼ�����Ҳ��ܽ�
	local userlevel = GetLevel(sceneId, selfId);
	if userlevel < x300501_g_LevelLess then
		return 0
	end

        -- ��ӡ���������˵����
	AddQuestTextNM(sceneId, selfId, targetId, x300501_g_MissionCommentId, 13, -1)


			
	local randMissionId = x300501_GetRandMissionId(sceneId, selfId)
	if randMissionId > 0 then
		if IsHaveQuestNM(sceneId, selfId, randMissionId) > 0 then
			return 0;	--�Ѿ��ӵ��������񣬲���Ҫ����ʾ�տ�������
		end
	end

	local virtualMisId
	if x300501_CountrySceneList[GetCurCountry(sceneId, selfId)+1] == sceneId then
		virtualMisId = x300501_g_VirtualMissionId_Low;
	elseif sceneId == x300501_CapitalSceneId then
		virtualMisId = x300501_g_VirtualMissionId_High;
	else
		return 0;
	end

	--�����ҵȼ����ߣ���ʾһ���������������ѡ���������ʾ���ȥ�󶼽�����
	if (userlevel >= x300501_LevelToCapital and virtualMisId == x300501_g_VirtualMissionId_Low) then
		AddQuestNumText( sceneId, x300501_g_VirtualMissionId_Low, x300501_g_MissionName, 13)
		return 0;
	end
	--�����û��������������ʾ�տ����������
	--����randMissionId����0��˵���Ѿ�����������񣬵����ڱ����������������������û�гɹ��ӵ�
	if QuestCheckAcceptNM( sceneId, selfId, targetId, virtualMisId ) > 0 then
		x300501_AddMissionTextByState(sceneId, selfId, targetId, virtualMisId);
	end

	return ret;
end

--ѡ������
function x300501_ProcEventEntry( sceneId, selfId, targetId, MissionId)

	if MissionId == x300501_g_MissionCommentId then
	-- ��ʾ��������˵������
		QuestCom(sceneId, selfId, x300501_g_MissionCommentId)
		x300501_DisplayMissionEventMessage (sceneId, selfId, targetId, MissionId, x300501_g_MissionCommentMessage)		
		return 0;
	end

	--�����ҵȼ����ߣ���ʾ���ȥ�󶼽�����
	local userlevel = GetLevel(sceneId, selfId);
	if (userlevel >= x300501_LevelToCapital and MissionId == x300501_g_VirtualMissionId_Low) then
		BeginQuestEvent( sceneId)
			AddQuestText( sceneId, "#Y"..x300501_g_MissionName)
			AddQuestText( sceneId, x300501_g_MissionCommentWrongPlace )
			DispatchQuestInfoNM( sceneId, selfId, targetId, x300501_g_ScriptId, MissionId, 1)
		EndQuestEvent()
		return 0;	
	end

	x300501_CheckDayChanged(sceneId, selfId)
	local ret = 0;
	if MissionId == x300501_g_VirtualMissionId_Low or MissionId == x300501_g_VirtualMissionId_High then	--���տտ�����ʱҪ����Ƿ�ﵽ��������
		local highcircle = x300501_GetMD(sceneId, selfId, MD_GUOJIARENWU_HIGH)
		if highcircle >= x300501_HighBonusCircleCount * 2 then
			BeginQuestEvent( sceneId)
				Msg2Player(sceneId, selfId, x300501_g_MissionCommentCountOver, 8, 3)
				Msg2Player(sceneId, selfId, x300501_g_MissionCommentCountOver, 8, 2)
			EndQuestEvent()
			return 0;
		end
	end

	if x300501_CheckAbandonPenaltyOff (sceneId, selfId, targetId ) <= 0 then
		return 0;
	end

	if MissionId == x300501_g_VirtualMissionId_Low or MissionId == x300501_g_VirtualMissionId_High then	--��ʾ�տ��������
		BeginQuestEvent( sceneId)
		-- ��������
			AddQuestText( sceneId, "#Y"..x300501_g_MissionName)
		--��������
			AddQuestText( sceneId, GetQuestDescNM (sceneId, selfId, MissionId))
			AddQuestText( sceneId, " " )
		--������
			local curlevel = GetLevel(sceneId, selfId)
			local exp = x300501_GetExpAward ( sceneId, selfId, curlevel );
			local money,shengw = x300501_GetMoneyAward ( sceneId, selfId, curlevel );
			local str
			if(exp > 0) then
				AddQuestExpBonus(sceneId, exp)
			end
			if(money > 0) then
				AddQuestMoneyBonus2(sceneId, money)
			end
			if(shengw > 0) then
				AddQuestMoneyBonus5(sceneId, shengw)
			end
		--С��ʾ
			AddQuestText( sceneId, "#c00FF00С��ʾ:" )
			AddQuestText( sceneId, "#c00FF00�����Ҫ�˽Ȿ�����ϸ�ڣ�������������˵����ť��" )
		EndQuestEvent()
		ret = DispatchQuestInfoNM( sceneId, selfId, targetId, x300501_g_ScriptId, MissionId)
		return 0;
	else
		local randMissionId = x300501_GetRandMissionId(sceneId, selfId)
		if randMissionId == 0 or IsHaveQuestNM( sceneId, selfId, randMissionId ) == 0 then	-- ���û�������ֱ���˳�
			return 0
		end
		--������ʾ������Ľ���
		ret = x300501_ShowMissionInfoByState(sceneId, selfId, targetId, randMissionId)
	end
  
	return ret;
end

--�������
--����1����ɹ���0��������ʧ��
function x300501_ProcQuestSubmit( sceneId, selfId, targetId, selectId, MissionId )

	MissionId = x300501_GetRandMissionId(sceneId, selfId);
	
	if MissionId == nil or MissionId <= 0 then
        	return 0
    	end

	if IsHaveQuestNM( sceneId, selfId, MissionId ) == 0 then	-- ���û�������ֱ���˳�
		return 0
	end

	if IsHaveQuestNM( sceneId, selfId, MissionId ) <= 0 then	-- ���û�������ֱ���˳�
		return 0
	end

	local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )

	--�ж�����󻷽ڵ��ύ�����м价�ڵ��ύ
	local ret = 0
	if x300501_IsDig(MissionId) == 1 then
		ret = 1				--�ھ򲻴����м���ύ����
	elseif x300501_IsEscort(MissionId) == 1 then
		ret = CallScriptFunction( 300519, "ProcQuestSubmitOrContinue", sceneId, selfId, targetId, MissionId)	--���ʹ����м���ύ����
	elseif x300501_IsCollectHorse(MissionId) == 1 then	
		ret = 1				--���������м���ύ����
	elseif x300501_IsDeliver(MissionId) == 1 then 
		--local oldTargetId = x300501_CheckMissionNPC(sceneId, selfId, MissionId);
		local targetGuid = GetMonsterGUID( sceneId, targetId)
		local reply_npcid = GetQuestSubmitNPCGUIDNM(sceneId, selfId, misIndex)
		if targetGuid == reply_npcid then		--�ڽ������NPC���ύ
			ret = 1
		else					--�������˴��ύ
			ret = 0
			if 0 == DelItem(sceneId, selfId, x300501_g_DeliverItemID, x300501_g_DeliverItemCount) then
				Msg2Player(sceneId, selfId, "�޷��۳�������ߣ����Ժ�����", 8, 3)
				Msg2Player(sceneId, selfId, "�޷��۳�������ߣ����Ժ�����", 8, 2)
			else
				local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )
				SetQuestByIndex( sceneId, selfId, misIndex, 0, 1)
				SetQuestByIndex( sceneId, selfId, misIndex, 7, 1)
				Msg2Player(sceneId, selfId, "�����Ѿ���ɣ�����ȥ�㱨�ɣ�", 8, 3)
			end
		end
	else
		ret = 1
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
	local exp = x300501_GetExpAward ( sceneId, selfId, curlevel );
	local money,shengw = x300501_GetMoneyAward ( sceneId, selfId, curlevel );

	--������������мӱ�����
	if x300501_IsCollectHorse(MissionId) == 1 then
		local commitret, awardrate = CallScriptFunction (300516 , "HorseSubmit", sceneId, selfId, MissionId)
		if (commitret == 0) then	--û�гɹ�����
			return 0
		end
		exp = exp * awardrate
		money = money * awardrate
		shengw = shengw * awardrate
	end

	--�����������
	ret = CircleQuestComplateNM( sceneId, selfId, targetId, MissionId);

	if ret == 1 then -- ����ɹ����
		
		local circle, highcircle = x300501_SetRounds(sceneId, selfId)
		x300501_DisplayCircleMessage (sceneId, selfId, MissionId)
		QuestUnCom( sceneId, selfId, x300501_g_VirtualMissionId_Low)
		QuestUnCom( sceneId, selfId, x300501_g_VirtualMissionId_High)
		x300501_SetMD(sceneId, selfId, MD_GUOJIARENWU_RANDMISSIONID, 0)
		x300501_DisplayCompleteMessage(sceneId, selfId, targetId, MissionId);
		--��������
		if exp > 0 then
			AddExp(sceneId, selfId, exp)
		end
		--������Ǯ
		if money > 0 then
			AddMoney(sceneId, selfId, moneytype, money)
		end
		--������Ǯ
		if shengw > 0 then
			local oldshengw = GetShengWang(sceneId, selfId)
			SetShengWang(sceneId, selfId, oldshengw + shengw)
		end
		--��ʾ��Ǯ�;���Ľ���
		x300501_DisplayAwardInfo(sceneId, selfId, targetId, -1, -1, moneytype, money, exp, 0, shengw)
		--�����ÿ�����һ���߽�������Ʒ�͹��ҽ��
		if (highcircle == x300501_HighBonusCircleCount) then
			x300501_GetItemAwardDirectly ( sceneId, selfId, curlevel );
			--AddCountryResource (sceneId, selfId, 2, 2000, 1);
		end
        if circle == x300501_HighBonusCircleCount then
            CallScriptFunction( 256216, "FinishNeizheng", sceneId, selfId)
        end

	else -- ���δ�ɹ����
		x300501_DisplayCompleteMissionErrorMessage(sceneId, selfId, ret);
		return 0
	end

	return 1;
end

--****************************��������

--���齱��
function x300501_GetExpAward(sceneId, selfId, startlevel)

	x300501_CheckDayChanged(sceneId, selfId)
	local circle = x300501_GetMD(sceneId, selfId, MD_GUOJIARENWU_CIRCLE)
	local highcircle = x300501_GetMD(sceneId, selfId, MD_GUOJIARENWU_HIGH)
	
	circle = circle + 1
	if (circle > x300501_OneRoundCount) then
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
	if (highcircle <= x300501_HighBonusCircleCount) then
		BonusExp = BonusExp * 5
	end
    -- �������룬���Ծ��鷭��
    BonusExp = BonusExp * 2
	return BonusExp;

end

--��Ǯ����
function x300501_GetMoneyAward(sceneId, selfId, startlevel)

	x300501_CheckDayChanged(sceneId, selfId)	
	local circle = x300501_GetMD(sceneId, selfId, MD_GUOJIARENWU_CIRCLE)	
	local highcircle = x300501_GetMD(sceneId, selfId, MD_GUOJIARENWU_HIGH)	
		
	circle = circle + 1	
	if (circle > x300501_OneRoundCount) then	
		circle = 1
	end	
		
	highcircle = highcircle + 1	
		
	--local BonusMoney = startlevel * 40 * (circle * 2 - 1) / 200	
	local BonusMoney = startlevel	
	local shengw = 5
	if (highcircle <= x300501_HighBonusCircleCount) then	
		BonusMoney = BonusMoney * 5
		shengw = 25
	end	
	return BonusMoney,shengw;	

end
--����ֱ�ӽ���
function x300501_GetItemAwardDirectly(sceneId, selfId, startlevel)

	local spec;
	local ret = 0;

	for i, item in x300501_g_ItemAwardCertain do
		if startlevel >= item.levelMin and startlevel < item.levelMax then
			local rnum = random(1, item.num);
			local count = random(1, item.maxcount);
			ret = x300501_GiveItemToHuman (sceneId, selfId, item.id[rnum], count)
			if (ret > 0) then
				Msg2Player(sceneId, selfId, format("#Y���%d����Ʒ#R#{_ITEM%d}#Y�Ľ���", count, item.id[rnum]), 8, 3);
			end
			break
		end
	end
	return ret
end

--�Ƿ�����������
function x300501_IsCollectHorse(MissionId)
	if MissionId >= x300501_g_CollectHorse_Mission_ID and MissionId <= x300501_g_CollectHorse_Mission_ID_End then
		return 1
	else
		return 0
	end
end

--�Ƿ����ھ�����
function x300501_IsDig(MissionId)
	if MissionId >= x300501_g_DigMissionID and MissionId <= x300501_g_DigMissionID_End then
		return 1
	else
		return 0
	end
end

--�Ƿ��ǻ�������
function x300501_IsEscort(MissionId)
	if MissionId >= x300501_g_EscortMissionID and MissionId <= x300501_g_EscortMissionID_End then
		return 1
	else
		return 0
	end
end

--�Ƿ�����������
function x300501_IsDeliver(MissionId)
	if MissionId >= x300501_g_DeliverMissionID and MissionId <= x300501_g_DeliverMissionID_End then
		return 1
	else
		return 0
	end
end

-- ��ʾ�����Ϣ
function x300501_OnCanCompleteMission ( sceneId, selfId, targetId, MissionId )

	--�������������ύ���ڸ���������һ��
	if x300501_IsCollectHorse(MissionId)==1 then	
		CallScriptFunction( 300516, "OnCanCompleteMission", sceneId, selfId, targetId, MissionId )
		return
	end

	BeginQuestEvent(sceneId);
		--��������
		AddQuestText(sceneId, "#Y"..x300501_g_MissionName)
		--����ύ���ڵ�����
		if x300501_IsDeliver(MissionId) == 1 then --������������ύ���ڵ�����û��д�ڱ����
			AddQuestText(sceneId, "\t���Ѿ��͵��ˣ�")
		else
			AddQuestText(sceneId, GetQuestSuccessNM(sceneId, selfId, MissionId))
		end
		--������
		local curlevel = GetLevel(sceneId, selfId)
		local exp = x300501_GetExpAward ( sceneId, selfId, curlevel );
		local money,shengw = x300501_GetMoneyAward ( sceneId, selfId, curlevel );
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
	DispatchQuestContinueInfoNM( sceneId, selfId, targetId, x300501_g_ScriptId, MissionId )
end

--�Ƿ��ڳͷ�ʱ���ڣ�����0��ʾ��Ȼ�ڳͷ�ʱ����
function x300501_CheckAbandonPenaltyOff ( sceneId, selfId, targetId )

	local curMinute = GetMinOfDay() + 1	--��ɴ�1��ʼ
	local curDay = GetDayOfYear()		

	local lastday =  x300501_GetMD(sceneId, selfId, MD_GUOJIARENWU_LASTDAY)
	local lastMinute =  x300501_GetMD(sceneId, selfId, MD_GUOJIARENWU_ABANDON)

	if (lastMinute == 0) then --û��������
		return 1;
	end

	local bCanAccept = 1
	if (lastday == curDay) then		--��������󣬻�û���ڶ���
		if (curMinute >= lastMinute)  and  (curMinute - lastMinute < x300501_g_AbandonTime) then 
			bCanAccept = 0
		end
	elseif (curDay - lastday == 1) or (lastday == 365 and curDay == 0) then	--��������󣬵��˵ڶ���
		if 1441 - lastMinute + curMinute <= x300501_g_AbandonTime then
			bCanAccept = 0
		end
	end
	--δ��������������������������Գͷ�ʱ��

	if (bCanAccept == 0) then
		--���ܽ�������
		local str = format("#Y"..x300501_g_MissionName.."#W\n\t�����������%d���ӣ����ܽ�������" , x300501_g_AbandonTime);
		BeginQuestEvent(sceneId);
			AddQuestText(sceneId, str);
		EndQuestEvent(sceneId);
		DispatchQuestEventList(sceneId, selfId, targetId);
		return 0
	end

	--���Խ�������
	if( lastMinute ~= 0 ) then 
		x300501_SetMD(sceneId, selfId, MD_GUOJIARENWU_ABANDON, 0)
	end

	return 1;
end

--��������״̬��ʾ������Ϣ
function x300501_ShowMissionInfoByState( sceneId, selfId, targetId, MissionId )

	if IsHaveQuestNM( sceneId, selfId, MissionId ) == 0 then	-- ���û���������
		local ret = QuestCheckAcceptNM( sceneId, selfId, targetId, MissionId )
		if ret > 0 then	-- ������Խ��������
			if IsQuestFullNM(sceneId, selfId)==1 then
				Msg2Player(sceneId, selfId, "#Y���Ѿ�����̫�������", 8, 3)
				Msg2Player(sceneId, selfId, "#Y���Ѿ�����̫�������", 8, 2)
				return 0
			end
			return x300501_AutoAccept ( sceneId, selfId, targetId, MissionId )
		else
			x300501_DisplayMissionAcceptErrorMessage(sceneId, selfId, ret);
			return 0;
		end
	else --������������
		local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )
		local isFinish = GetQuestParam( sceneId, selfId, misIndex, 7)
		if isFinish == 1 then
			x300501_OnCanCompleteMission ( sceneId, selfId, targetId, MissionId )-- ��ʾ�����Ϣ
		else
			x300501_ShowMissionContinueInfo( sceneId, selfId, targetId, MissionId ) -- ��ʾ����δ�����Ϣ
		end
		return 0;
	end
	
	return 0;
end

function x300501_ShowMissionContinueInfo( sceneId, selfId, targetId, MissionId) -- ��ʾ����δ�����Ϣ

	local ret = 0
	if x300501_IsDig(MissionId) == 1 then
		ret = CallScriptFunction( 300518, "ShowMissionContinueInfo", sceneId, selfId, targetId, MissionId)
	elseif x300501_IsEscort(MissionId) == 1 then
		ret = CallScriptFunction( 300519, "ShowMissionContinueInfo", sceneId, selfId, targetId, MissionId)
	else
		--��������������Ŀ��npc��
		if x300501_IsDeliver(MissionId) == 1 then --�����������⴦�� 
			local targetGuid = GetMonsterGUID( sceneId, targetId)
			for i, setitem in x300501_g_DeliverTargetNPC do
				if setitem.missionID == MissionId then
					if setitem.npcID == targetGuid then
						BeginQuestEvent(sceneId);
							--��������
							AddQuestText(sceneId, "#Y"..x300501_g_MissionName)
							--����ɹ����ı�
							AddQuestText(sceneId, GetQuestSuccessNM(sceneId, selfId, MissionId))
						EndQuestEvent();
						DispatchQuestContinueInfoNM( sceneId, selfId, targetId, x300501_g_ScriptId, MissionId )
						return
					end
					break
				end
			end
		end
		QuestNotComplateInfoNM( sceneId, selfId, targetId, MissionId ) -- ��ʾ����δ�����Ϣ
	end
end

--���ܿտ�����
function x300501_ProcQuestAccept( sceneId, selfId, targetId, MissionId)

	--�����ҵȼ����ߣ���ʾ���ȥ�󶼽�����
	local userlevel = GetLevel(sceneId, selfId);
	if (userlevel >= x300501_LevelToCapital and MissionId == x300501_g_VirtualMissionId_Low) then
		BeginQuestEvent( sceneId)
			AddQuestText( sceneId, "#Y"..x300501_g_MissionName)
			AddQuestText( sceneId, x300501_g_MissionCommentWrongPlace )
			DispatchQuestInfoNM( sceneId, selfId, targetId, x300501_g_ScriptId, MissionId, 1)
		EndQuestEvent()
		return 0;	
	end

	local randMissionId = x300501_GetRandMissionId(sceneId, selfId)
	if randMissionId == 0 then
		--���һ��������
		local missionType
		randMissionId, missionType = x300501_GenerateRandomMission ( sceneId, selfId, targetId );
	end

	if (randMissionId == 0) then
		return 0;
	end

	--��ʾ��������Ϣ����
	local ret = x300501_ShowMissionInfoByState(sceneId, selfId, targetId, randMissionId)
	return 1;
end

--�Զ�����������
function x300501_AutoAccept( sceneId, selfId, targetId, MissionId )
	--MissionId��������Ч��������
	if IsHaveQuestNM( sceneId, selfId, MissionId ) > 0 then
		return 1
	end
	
	--���ǰ������
	local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId, MissionId )
	if FrontMissiontId1 ~= -1 then
		if IsQuestHaveDoneNM( sceneId, selfId, FrontMissiontId1 ) == 0 then
			return 0--���ǰ������û��ֱ�ӷ���
		end
	end
	if FrontMissiontId2 ~= -1 then
		if IsQuestHaveDoneNM( sceneId, selfId, FrontMissiontId2 ) == 0 then
			return 0--���ǰ������û��ֱ�ӷ���
		end
	end
	if FrontMissiontId3 ~= -1 then
		if IsQuestHaveDoneNM( sceneId, selfId, FrontMissiontId3 ) == 0 then
			return 0--���ǰ������û��ֱ�ӷ���
		end
	end

	--��������
	local ret = 0
	if x300501_IsDig(MissionId) == 1 then
		ret = AddQuest( sceneId, selfId, MissionId, 300518, 0, 0, 0, 1)
	elseif x300501_IsEscort(MissionId) == 1 then
		ret = AddQuest( sceneId, selfId, MissionId, 300519, 0, 0, 0, 1)
	elseif x300501_IsDeliver(MissionId) == 1 then --�����������⴦�� 
		--����������������������������Ʒ�������������Ʒ���ʧ��������Ҳ�������
			BeginAddItem(sceneId)
				AddItem( sceneId, x300501_g_DeliverItemID, x300501_g_DeliverItemCount )
			ret = EndAddItem(sceneId,selfId)
			if ret > 0 then
				AddItemListToPlayer(sceneId,selfId)
				--ret = AddQuestNM( sceneId, selfId, MissionId ) -- ������������
				ret = AddQuest( sceneId, selfId, MissionId, x300501_g_ScriptId, 0, 0, 0, 1)
			else
				ret = -1	--������
			end 
	else
		ret = AddQuestNM( sceneId, selfId, MissionId ) -- ������������
	end

	if ret > 0 then
		x300501_AfterAccept( sceneId, selfId, targetId, MissionId)
	else
		x300501_DisplayAddMissionErrorMessage(sceneId, selfId, ret);
	end
	return ret
end

function x300501_AfterAccept( sceneId, selfId, targetId, MissionId)

	local misIndex = GetQuestIndexByID(sceneId, selfId, MissionId);
  --ִ�������������õĽ��ܺ���

	--����NPCͷ����ɫ̾��
	local userlevel = GetLevel(sceneId, selfId)
	local virtualMisId;
	if ( userlevel < x300501_LevelToCapital ) then
		virtualMisId = x300501_g_VirtualMissionId_Low
	else
		virtualMisId = x300501_g_VirtualMissionId_High
	end

	QuestCom( sceneId, selfId, x300501_g_VirtualMissionId_Low)
	QuestCom( sceneId, selfId, x300501_g_VirtualMissionId_High)

	x300501_DisplayAcceptMessage(sceneId, selfId, MissionId);
	for i = 0, 4 do
		local SceneID, PosX, PosZ, tips = GetAskWayPosNM(sceneId, selfId, MissionId, i)
		if SceneID ~= -1 then
			CallScriptFunction( UTILITY_SCRIPT, "AskTheWayPos", sceneId, selfId, SceneID, PosX, PosZ, tips )
		end
	end
	
  --��ʾ������Ϣ
	if x300501_IsDig(MissionId) == 1 then
		CallScriptFunction( 300518, "ShowMissionInfo", sceneId, selfId, targetId, MissionId)
	elseif x300501_IsEscort(MissionId) == 1 then
		CallScriptFunction( 300519, "ShowMissionInfo", sceneId, selfId, targetId, MissionId)
	else
		BeginQuestEvent( sceneId)
		-- ��������
			AddQuestText( sceneId, "#Y"..x300501_g_MissionName)
		--��������
			AddQuestText( sceneId, GetQuestDescNM (sceneId, selfId, MissionId))
			AddQuestText( sceneId, " " )
		--����Ŀ��
			AddQuestText( sceneId, "#Y����Ŀ�꣺" )
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
			AddQuestText( sceneId, " ")

		EndQuestEvent()
	       
		DispatchQuestInfoNM( sceneId, selfId, targetId, x300501_g_ScriptId, MissionId, 1)
	end


  --ִ���������ܺ�������
	if x300501_IsDig(MissionId) == 1 then
		CallScriptFunction( 300518, "AfterAccept", sceneId, selfId, targetId, MissionId, misIndex )
	elseif x300501_IsEscort(MissionId) == 1 then
		CallScriptFunction( 300519, "AfterAccept", sceneId, selfId, targetId, MissionId, misIndex )
	elseif x300501_IsCollectHorse(MissionId) == 1 then	
		SetQuestEvent(sceneId, selfId, MissionId, 3 )
	elseif x300501_IsDeliver(MissionId) == 1 then 
	end

  --��������Ƿ��ܹ��ύ����
	local ret = 0
	if x300501_IsDig(MissionId) == 1 then
		ret = QuestCheckSubmitNM( sceneId, selfId, targetId, MissionId, misIndex ) 
	elseif x300501_IsEscort(MissionId) == 1 then
		ret = CallScriptFunction( 300519, "CheckIfCanSubmit", sceneId, selfId, targetId, MissionId, misIndex )
	elseif x300501_IsDeliver(MissionId) == 1 then 
		ret = 0
	elseif x300501_IsCollectHorse(MissionId) == 1 then	
		ret = x300501_IfHaveNeededHorse(sceneId, selfId, MissionId)
	else
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

	local highcircle = x300501_GetMD(sceneId, selfId, MD_GUOJIARENWU_HIGH)
	if (highcircle == 0) then
		GamePlayScriptLog(sceneId, selfId, 451)
	elseif (highcircle == 10) then
		GamePlayScriptLog(sceneId, selfId, 461)
	elseif (highcircle == 19) then
		GamePlayScriptLog(sceneId, selfId, 471)
	end
		
end

function x300501_SetRounds(sceneId, selfId)

	local highcircle = x300501_GetMD(sceneId, selfId, MD_GUOJIARENWU_HIGH)
	local lastCircle = x300501_GetMD(sceneId, selfId, MD_GUOJIARENWU_CIRCLE)

	if (highcircle == 0) then
		GamePlayScriptLog(sceneId, selfId, 452)
	elseif (highcircle == 10) then
		GamePlayScriptLog(sceneId, selfId, 462)
	elseif (highcircle == 19) then
		GamePlayScriptLog(sceneId, selfId, 472)
	end

	highcircle = highcircle + 1
	x300501_SetMD(sceneId, selfId, MD_GUOJIARENWU_HIGH, highcircle)
	
	if lastCircle >= x300501_OneRoundCount then	
		lastCircle = 1;			--��������
	else						--��������
		lastCircle = lastCircle + 1;
	end	

	x300501_SetMD(sceneId, selfId, MD_GUOJIARENWU_CIRCLE, lastCircle)

	return lastCircle,highcircle
end

--function x300501_SetMissionNPC(sceneId, selfId, MissionId, targetId)
--	local startlevel = 0 
--	local misIndex = GetQuestIndexByID(sceneId, selfId, MissionId);
--	SetQuestByIndex(sceneId, selfId, misIndex, x300501_g_NPCandLevelParam, targetId * 1000 + startlevel);
--end

function x300501_GetMP(sceneId, selfId, MissionId, constMP)
	local misIndex = GetQuestIndexByID(sceneId, selfId, MissionId);
	return GetQuestParam(sceneId, selfId, misIndex, constMP);
end

--function x300501_CheckMissionNPC(sceneId, selfId, MissionId)
--	local misIndex = GetQuestIndexByID(sceneId, selfId, MissionId);
--	local targetId = GetQuestParam(sceneId, selfId, misIndex, x300501_g_NPCandLevelParam);  --x300501_GetMP(sceneId, selfId, MissionId, x300501_g_NPCandLevelParam );
--	targetId = floor(targetId / 1000);
--	return targetId;
--end

function x300501_DisplayAcceptMessage(sceneId, selfId, MissionId)
	local str = format("�����������%s", x300501_g_MissionName);
	Msg2Player(sceneId, selfId, str, 8, 3)
	Msg2Player(sceneId, selfId, str, 8, 2)
	return 1;
end

function x300501_DisplayAddMissionErrorMessage(sceneId, selfId, ret)
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

function x300501_DisplayMissionAcceptErrorMessage(sceneId, selfId, ret)

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

function x300501_ProcQuestLogRefresh( sceneId, selfId, MissionId )

	local misIndex = GetQuestIndexByID(sceneId, selfId, MissionId);
	
	if x300501_IsDig(MissionId) == 1 then
		CallScriptFunction( 300518, "ProcQuestLogRefresh", sceneId, selfId, MissionId, misIndex)
		return
	elseif x300501_IsEscort(MissionId) == 1 then
		CallScriptFunction( 300519, "ProcQuestLogRefresh", sceneId, selfId, MissionId, misIndex)
		return
	end

	local strName;
	strName = x300501_g_MissionName;
	local circle = x300501_GetMD(sceneId, selfId, MD_GUOJIARENWU_CIRCLE)
	if (circle >= x300501_OneRoundCount) then
		circle = 1
	else
		circle = circle + 1
	end
	strName = strName.."("..circle;
	strName = strName.."/"..x300501_OneRoundCount;
	strName = strName..")";

	local reply_npcid = GetQuestSubmitNPCGUIDNM(sceneId, selfId, misIndex)
	if (reply_npcid < 0) then
		return
	end
	local strReplyNPC = format("@npc_%d", reply_npcid)
	
	local szMissionTarget =""
	if x300501_IsDeliver(MissionId) == 1 then
		local num = GetQuestParam(sceneId, selfId, misIndex, 0)
		local szTarget1,szTarget2,szTarget3,szTarget4,szTarget5 = GetQuestTargetNM(sceneId, selfId, MissionId)
		szMissionTarget = "  "..szTarget1
	end
	
	BeginQuestEvent(sceneId);
		--MissionTitle, MissionName, MissionTarget, MissionNPC, MissionProcess, MissionComment, MissionTip
		AddQuestLogCustomText(sceneId, "", strName, szMissionTarget, strReplyNPC, "", "", "");
		--������
		local curlevel = GetLevel(sceneId, selfId)
		local exp = x300501_GetExpAward ( sceneId, selfId, curlevel );
		local money,shengw = x300501_GetMoneyAward ( sceneId, selfId, curlevel );
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
	DispatchQuestLogUpdate(sceneId, selfId, MissionId);
end

--ɱ������
function x300501_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
															--����ID, �Լ���ID, �����λ�ú�, ����objId, ����ID
	MissionId = x300501_GetRandMissionId(sceneId, selfId);
	if (MissionId == 0) then
		return 0
	end

	if IsHaveQuestNM(sceneId, selfId, MissionId) == 0 then
		return 0
	end
	local NeedKilledNum, InstIndex, ObjName = GetQuestNeedKillObjInfoNM( sceneId, selfId, MissionId, objdataId, objId )

	if NeedKilledNum == 0 then --ɱ�ֵ���Ʒ���͵�����
		local KilledNum = GetMonsterOwnerCount( sceneId, objId ) --ȡ�������������ӵ�з���Ȩ������
		for i = 0, KilledNum-1 do
			local humanObjId = GetMonsterOwnerID( sceneId, objId, i ) --ȡ��ӵ�з���Ȩ���˵�objId
    			if humanObjId ~= -1 then
    				if IsHaveQuestNM( sceneId, humanObjId, MissionId ) > 0 then	--��������ӵ������
        				local ItemCount, ItemID, ItemRand, ItemDropNum = GetQuestItemNM( sceneId, humanObjId, MissionId, InstIndex )
					--Ҫ�ռ��ĸ�������ƷID�������ʣ�һ��������
					if ItemCount > 0 then
						local ItemNumOnPlayer = GetItemCount( sceneId, humanObjId, ItemID )
						if ItemNumOnPlayer < ItemCount then
							local droprand = random(100)
							if droprand < ItemRand then
								local dropnum = random(ItemDropNum)
									if dropnum == 0 then
										dropnum = 1
									end
								if dropnum > ItemID - ItemNumOnPlayer then
									dropnum = ItemID - ItemNumOnPlayer
								end

								x300501_GiveItemToHuman (sceneId, humanObjId, ItemID, dropnum)
							end
						end
					end
				end
			end
		end
	elseif NeedKilledNum > 0 then --������ɱ������
		local HumenNum = GetMonsterOwnerCount( sceneId, objId ) --ȡ�������������ӵ�з���Ȩ������
		for i = 0, HumenNum-1 do
			local humanObjId = GetMonsterOwnerID( sceneId, objId, i ) --ȡ��ӵ�з���Ȩ���˵�objId
			if humanObjId ~= -1 then
				if IsHaveQuestNM( sceneId, humanObjId, MissionId ) > 0 then	--��������ӵ������
					local str = "";
					local KilledNum = x300501_GetMP(sceneId, humanObjId, MissionId, InstIndex)
					x300501_DisplayMissionKillMonsterMessage(sceneId, humanObjId, ObjName, KilledNum, NeedKilledNum);
					if KilledNum < NeedKilledNum then
						x300501_SetMP(sceneId, humanObjId, MissionId, InstIndex, KilledNum+1);
						if KilledNum == NeedKilledNum - 1 then
							x300501_SetMP(sceneId,humanObjId,MissionId,7,1)
							Msg2Player(sceneId, humanObjId, "�����Ѿ���ɣ�����ȥ�㱨�ɣ�", 8, 3)
							local misIndex = GetQuestIndexByID(sceneId, humanObjId, MissionId);
							local MisCareNPC = QuestCareNPCNM( sceneId, humanObjId, misIndex )
							if MisCareNPC == 0 then --�����Զ����
								local ret = QuestCheckSubmitNM( sceneId, humanObjId, 0, MissionId, misIndex ) -- ��ȡ�����������Ϣ
								if ret > 0 then -- ����������
									return x300501_MissionCanSubmit( sceneId, humanObjId, 0, -1, MissionId )
								end
							end
						else
							x300501_SetMP(sceneId,humanObjId,MissionId,7,0 )
						end
					end
				end
			end
		end
	end
	return 0
end


function x300501_DisplayMissionKillMonsterMessage(sceneId, selfId, ObjName, KilledNum, NeedKilledNum)

	local str = "";
	local ret = 1;
	if KilledNum < NeedKilledNum then
		if KilledNum == NeedKilledNum - 1 then
			if ObjName == "" then
				str = format( "#Y�Ѿ���ɻ��ܹ���: %d/%d", KilledNum+1, NeedKilledNum )
			else
				str = format( "#Y�Ѿ���ɻ���#G%s#Y: %d/%d", ObjName, KilledNum+1, NeedKilledNum )
			end
		 else
			if ObjName == "" then
				str = format( "#Y�Ѿ����ܹ���: %d/%d", KilledNum+1, NeedKilledNum )
			else
				str = format( "#Y�Ѿ�����#G%s#Y: %d/%d", ObjName, KilledNum+1, NeedKilledNum )
			end
			ret = 0;
		end
		if str ~= "" then
			Msg2Player(sceneId, selfId, str, 8, 3)
		end
	end

	return ret;
	
end

--���������ɵ���δ�ύ
function x300501_MissionCanSubmit( sceneId, selfId, targetId, selectId, MissionId )
	local ret = 0;

	if (IsHaveQuestNM(sceneId, selfId, MissionId) == 0) then
		return 0
	end

	local misIndex = GetQuestIndexByID(sceneId, selfId, MissionId);
	ret = QuestComplateNM( sceneId, selfId, targetId, MissionId, selectId ); -- ��ȡ���������Ϣ

	if ret == 1 then -- ����ɹ����

		QuestUnCom( sceneId, selfId, x300501_g_VirtualMissionId_Low)
		QuestUnCom( sceneId, selfId, x300501_g_VirtualMissionId_High)
		x300501_DisplayCompleteMessage(sceneId, selfId, targetId, MissionId);
		x300501_PushAfterMission(sceneId, selfId, targetId, MissionId );
		return 1 -- ���سɹ�

	else -- ���δ�ɹ����
		x300501_DisplayCompleteMissionErrorMessage(sceneId, selfId, ret);
		return 0
	end
	return 0
end

function x300501_DisplayCircleMessage(sceneId, selfId, MissionId )

	local circles = x300501_GetMD(sceneId, selfId, MD_GUOJIARENWU_CIRCLE)
	local highcircle = x300501_GetMD(sceneId, selfId, MD_GUOJIARENWU_HIGH)

	local str = format( "����: %d/%d", circles, x300501_OneRoundCount );
	if highcircle <= x300501_HighBonusCircleCount then
		str = str..format("  ���ո߽�������%d/%d", highcircle, x300501_HighBonusCircleCount);
	end
	Msg2Player(sceneId, selfId, str, 8, 3)

end

function x300501_DisplayCompleteMessage(sceneId, selfId, targetId, MissionId)
	
	local MissionName = x300501_g_MissionName;
	local str = format( "�����������%s", MissionName);

	Msg2Player(sceneId, selfId, str, 8, 3)
	return 1;

end

function x300501_DisplayAwardInfo(sceneId, selfId, targetId, MissionId, selectId, moneyType, money, expAward, honorType, honor)--��ʾ��ҽ�Ǯ���������Ľ�����Ϣ
	
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


function x300501_DisplayCompleteMissionErrorMessage(sceneId, selfId, ret)
	
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

function x300501_PushAfterMission(sceneId, selfId, targetId, MissionId )
	local AfterMissionType, AfterMissionId = GetAfterQuestIdNM( sceneId, selfId, MissionId )
	if AfterMissionId ~= -1 then
		if AfterMissionType == 0 then
			--������һ������Ľ���
			x300501_ProcEventEntry( sceneId, selfId, targetId, AfterMissionId);
		else
			--ֱ��PUSH��һ������
			PushAfterQuestNM( sceneId, selfId, targetId, AfterMissionId )
		end
	end
	return 1;
end

--�������--������Ҫ���÷���ʱ��MissionData
function x300501_ProcQuestAbandon( sceneId, selfId, MissionId )
	MissionId = x300501_GetRandMissionId(sceneId, selfId);
	if (MissionId == 0 or IsHaveQuestNM( sceneId, selfId, MissionId ) == 0 ) then
		--����ͬʱ���˶����������������,��������������ɾ��
		x300501_DelAllWrongMission(sceneId, selfId)
		return 0
	end
	local ret = 0

	if x300501_IsDeliver(MissionId) == 1 then --�����������⴦�� 
		
		local nCount = GetItemCount(sceneId,selfId,x300501_g_DeliverItemID)
		if nCount > x300501_g_DeliverItemCount then
			nCount = x300501_g_DeliverItemCount
		end
		
		if nCount > 0 and 0 == DelItem(sceneId, selfId, x300501_g_DeliverItemID, nCount) then
			Msg2Player(sceneId, selfId, "�޷��۳�������ߣ����Ժ�����", 8, 3)
			Msg2Player(sceneId, selfId, "�޷��۳�������ߣ����Ժ�����", 8, 2)
			return 0
		end
	end
	
	local  misIndex = GetQuestIndexByID(sceneId, selfId, MissionId);
	ret = DelQuestNM( sceneId, selfId, MissionId )
	if ret == 1 then

		QuestUnCom( sceneId, selfId, x300501_g_VirtualMissionId_Low)
		QuestUnCom( sceneId, selfId, x300501_g_VirtualMissionId_High)
		x300501_SetMD(sceneId, selfId, MD_GUOJIARENWU_LASTDAY, GetDayOfYear())
		x300501_SetMD(sceneId, selfId, MD_GUOJIARENWU_ABANDON, GetMinOfDay()+1)
		--�������������
		x300501_SetMD(sceneId, selfId, MD_GUOJIARENWU_RANDMISSIONID, 0)
		--x300501_SetMD(sceneId, selfId, MD_GUOJIARENWU_CIRCLE, 0)
		if x300501_GetMD(sceneId, selfId, MD_GUOJIARENWU_HIGH) < x300501_HighBonusCircleCount then
			x300501_SetMD(sceneId, selfId, MD_GUOJIARENWU_HIGH, x300501_HighBonusCircleCount)
			 --����Ǹ߽�״̬�·�����������ֱ�Ӵ��㿪ʼ
			x300501_SetMD(sceneId, selfId, MD_GUOJIARENWU_CIRCLE, 0)
		else
			
			--�ͽ�״̬������������������
			x300501_SetRounds(sceneId, selfId)
			
		end

		x300501_DisplayAbandonMessage(sceneId, selfId, MissionId);
	end

	return ret;
end

function x300501_DelAllWrongMission(sceneId, selfId)
	--����ͬʱ���˶����������������,��������������ɾ��
	local level = GetLevel(sceneId, selfId)
	for i, setitem in x300501_g_MissionIdList do
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

function x300501_DisplayAbandonMessage(sceneId, selfId, MissionId)
	local MissionName = x300501_g_MissionName;
	local str = format("�����������%s��", MissionName);

	Msg2Player(sceneId, selfId, str, 8, 3)
	Msg2Player(sceneId, selfId, str, 8, 2)
	return 1;
end

function x300501_ProcQuestAttach( sceneId, selfId, targetId, npcGuid, misIndex, MissionId )
	--�ھ򡢻��������񲻻�����������Լ��Ľű�
	MissionId = x300501_GetRandMissionId(sceneId, selfId);
	if (MissionId == 0) then
		return 0
	end

	if IsHaveQuestNM( sceneId, selfId, MissionId ) == 0 then	-- ���û���������
		return 0
	end

	--�������񣬵��������Ŀ��ʱ�������û���ţ���ʾ���������ѡ��
	if x300501_IsDeliver(MissionId) == 1 then --�����������⴦��
		for i, setitem in x300501_g_DeliverTargetNPC do
			if setitem.missionID == MissionId then
				if setitem.npcID == npcGuid then
					local isFinish = GetQuestParam( sceneId, selfId, misIndex, 0)
					if isFinish == 0 then
						AddQuestNumText( sceneId, MissionId, x300501_g_MissionName, 13)
					end
					return 1
				end
				break
			end
		end

	end

	local submitguid = GetQuestSubmitNPCGUIDNM( sceneId, selfId, misIndex )

	--����������ύ�ˣ���ʾѡ��
	if submitguid ~= -1 and submitguid == npcGuid then	
		x300501_AddMissionTextByState(sceneId, selfId, targetId, MissionId);
		return 1
	end

	return 0
end

function x300501_AddMissionTextByState(sceneId, selfId, NPCId, MissionId)
	local state = GetQuestStateNM(sceneId, selfId, NPCId, MissionId);
	return AddQuestTextNM(sceneId, selfId, NPCId, MissionId, state, -1);
end

function x300501_DisplayMissionEventMessage(sceneId, selfId, targetId, MissionId, contentStr)

	local MissionName;
	if MissionId > 0 then
		MissionName = x300501_g_MissionName;
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

function x300501_SetMP(sceneId, selfId, MissionId, constMP, Value)
	local misIndex = GetQuestIndexByID(sceneId, selfId, MissionId);
	return SetQuestByIndex(sceneId, selfId, misIndex, constMP, Value);
end

--��Ʒ�ı�
function x300501_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )

	MissionId = x300501_GetRandMissionId(sceneId, selfId);
	if (MissionId == 0) then
		return 0
	end

	if IsHaveQuestNM(sceneId, selfId, MissionId) == 0 then
		return 0
	end
	local NeedNum, ObjIndex = GetQuestNeedItemNumNM( sceneId, selfId, MissionId, itemdataId )

	if NeedNum > 0 then
		local Num = GetItemCount( sceneId, selfId, itemdataId )
		x300501_DisplayMissionGetItemMessage(sceneId, selfId, itemdataId, MissionId, ObjIndex, Num, NeedNum)
		if Num < NeedNum then --��û���������
			x300501_SetMP(sceneId, selfId, MissionId, ObjIndex, Num);
			x300501_SetMP(sceneId,selfId,MissionId,7,0)
		elseif Num >= NeedNum then
			if x300501_GetMP(sceneId,selfId,MissionId,7) == 1 then	--֮ǰ�Ѿ������
				return 0
			end
			x300501_SetMP(sceneId, selfId, MissionId, ObjIndex, NeedNum);
			x300501_SetMP(sceneId,selfId,MissionId,7,1)
			Msg2Player(sceneId, selfId, "�����Ѿ���ɣ�����ȥ�㱨�ɣ�", 8, 3)
			local misIndex = GetQuestIndexByID(sceneId, selfId, MissionId);
			local MisCareNPC = QuestCareNPCNM( sceneId, selfId, misIndex )
			if MisCareNPC == 0 then --�����Զ����
				local targetId = 0	--������
				local ret = QuestCheckSubmitNM( sceneId, selfId, targetId, MissionId, misIndex ) -- ��ȡ�����������Ϣ
				if ret > 0 then -- ����������
					return x300501_MissionCanSubmit( sceneId, selfId, targetId, -1, MissionId )
				end
			end
		end
	end
	return 0
end

function x300501_DisplayMissionGetItemMessage(sceneId, selfId, itemId, MissionId, ObjIndex, Num, NeedNum)

	local str = "";
	local ret = 1;
	local oldNum = x300501_GetMP(sceneId, selfId, MissionId, ObjIndex);
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

function x300501_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )

	MissionId = x300501_GetRandMissionId(sceneId, selfId);

	if (MissionId == 0) then
		return 0
	end

	if IsHaveQuestNM( sceneId, selfId, MissionId ) == 0 then	-- ���û�������ֱ���˳�
		return 0
	end

	local MissionIdx = GetQuestEnterAreaIndexNM( sceneId, selfId, MissionId, zoneId )
	if MissionIdx == -1 then
		return 0
	end

	if x300501_GetMP(sceneId, selfId, MissionId, MissionIdx) == 0 then
		x300501_SetMP(sceneId, selfId, MissionId, MissionIdx, 1)
		SendQuestEnterAreaTipsNM( sceneId, selfId, -1, MissionId, MissionIdx )
	end

	--�����Զ����
	local misIndex = GetQuestIndexByID(sceneId, selfId, MissionId);
	local MisCareNPC = QuestCareNPCNM( sceneId, selfId, misIndex )
	if MisCareNPC == 0 then --�����Զ����
		local ret = QuestCheckSubmitNM( sceneId, selfId, 0, MissionId, misIndex ) -- ��ȡ�����������Ϣ
		if ret > 0 then -- ����������
			ret = x300501_MissionCanSubmit( sceneId, selfId, 0, -1, MissionId )
			return ret
		end
	end

	return 1
end

--�뿪����
function x300501_ProcAreaLeaved( sceneId, selfId, ScriptId, MissionId )
	return 1;
end

--����ʱ��
function x300501_ProcTiming( sceneId, selfId, ScriptId, MissionId )
	return 1;
end

--**********************************************************************
--�ɼ�����
--��ItemBox
function x300501_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )

	local MissionId = x300501_GetRandMissionId(sceneId, selfId);
	if MissionId < -1 then
		MissionId = x300501_g_DefaultMissionId;
	end

	if IsHaveQuestNM( sceneId, selfId, MissionId ) == 0 then		--û���������
		local MissionName = x300501_g_MissionName;
		local reply_npcid;
		if (GetLevel(sceneId, selfId) >= x300501_LevelToCapital) then
			reply_npcid = x300501_g_MissionNPCObjId_High;
		else
			reply_npcid = x300501_g_MissionNPCObjId_Low;
		end
		Msg2Player(sceneId, selfId, format("#Yȥ��#R@npc_%d����#Y%s����ܲ�����", reply_npcid, MissionName), 8, 3);
		return 1
	end

	local MissionId, needItemCount, collNum = GetItemIdInItemBoxNM( sceneId, selfId, targetId, gpType, needItemID )
	local str
	if MissionId < 0 then
		str = "�㲻��Ҫ�����Ʒ";
		Msg2Player(sceneId, selfId, str, 8, 3);
		return 1 --û���������
	end

	local itemCountNow = GetItemCount( sceneId, selfId, needItemID )
	if itemCountNow >= needItemCount then
		str = "��Ʒ�Ѿ��ռ���ȫ";
		Msg2Player(sceneId, selfId, str, 8, 3);
		return 1
	end
	return 0

end

--����
function x300501_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	local MissionId, needItemCount, collNum = GetItemIdInItemBoxNM( sceneId, selfId, targetId, gpType, needItemID )

    --�ɼ����� Bug fixed by czg 2008-12-2
	if MissionId == -1 then
		MissionId = x300501_GetRandMissionId ( sceneId, selfId);
	end

	local str;
	if IsHaveQuestNM( sceneId, selfId, MissionId ) == 0 then	-- ���û�������ֱ���˳�
		local MissionName = x300501_g_MissionName;
		if MissionName == nil or MissionName == "" then
			str = "��û�н����������"
		else
			str = format("��û�н���#Y%s#W��", MissionName);
		end
		Msg2Player(sceneId, selfId, str, 8, 3);
		return 1
	end

	--����������Ѿ����ֱ���˳�
	if IsQuestHaveDoneNM( sceneId, selfId, MissionId ) > 0 then --�����Ѿ����
		return 0
	end

	local itemCountNow = GetItemCount( sceneId, selfId, needItemID )
	if itemCountNow >= needItemCount then
		local str = "��Ʒ�Ѿ��ռ���ȫ";
		Msg2Player(sceneId, selfId, str, 8, 3);
		return 0
	end

	--����һ�βɼ�����
	local itemAdd = needItemCount - itemCountNow
	if collNum == -1 then
		itemAdd = 1
	else
		if itemAdd > collNum then
			itemAdd = collNum
		end
	end
	if itemAdd > 1 then
		itemAdd = random(itemAdd)
		if itemAdd == 0 then
			itemAdd = 1
		end
	end

	local ret = x300501_GiveItemToHuman (sceneId, selfId, needItemID, itemAdd)
	if ret > 0 then
		return 1
	else
		return 0
	end
end

--��
function x300501_OnProcOver( sceneId, selfId, targetId )
	return 1
end

--�򿪺���
function x300501_OpenCheck( sceneId, selfId, targetId )
	return 1
end

--**********************************************************************
--����ʹ����Ʒ����
function x300501_PositionUseItem( sceneId, selfId, BagIndex, impactId, MissionId )

	MissionId = x300501_GetRandMissionId(sceneId, selfId);

	local ItemID = GetItemTableIndexByIndex( sceneId, selfId, BagIndex ) --�õ���ƷID
	local MissionId = GetQuestIDByItemIDNM( sceneId, selfId, ItemID )

	if MissionId == -1 then 	--û���ҵ��������
		return 0
	end

	if IsHaveQuestNM( sceneId, selfId, MissionId ) == 0 then	-- ���û�������ֱ���˳�
		return 0
	end

	local scene, posx, posz, radii, MissionIdx, dispStr, bDispOther, otherStr = GetQuestUseItemInfoNM( sceneId, selfId, MissionId, ItemID )
	if scene == -1 or sceneId ~= scene then --û���ҵ����������Ϣ
		return 0
	end

	if posx > 0 then --��Ҫ���ص�
		local PlayerPosX,PlayerPosZ = GetWorldPos( sceneId, selfId )

		local distanceRet = radii * radii - (posx - PlayerPosX) * (posx - PlayerPosX) - (posz - PlayerPosZ) * (posz - PlayerPosZ)
		if distanceRet <= 0 then
			local str = format("��Ӧ����@sceneid_%d[%d,%d]ʹ�ô���Ʒ��", scene, posx, posz )
			Msg2Player(sceneId, selfId, str, 8, 3);
			return 0
		end
	end

	if x300501_GetMP(sceneId, selfId, MissionId, MissionIdx) == 1 then
		return 0
	end

	--ɾ����Ʒ
	EraseItem(sceneId, selfId, BagIndex)

	--������ʾ
	x300501_SetMP(sceneId, selfId, MissionId, MissionIdx, 1);
	Msg2Player(sceneId, selfId, dispStr, 8, 3);

	if bDispOther > 0 then
		--����
		Msg2Player(sceneId, selfId, otherStr, 8, 0);
	end

	--����Ч��
	if impactId ~= -1 then
		SendSpecificImpactToUnit(sceneId, selfId, selfId, selfId, impactId, 0);
	end

	--�����Զ����
	local misIndex = GetQuestIndexByID(sceneId, selfId, MissionId);
	local MisCareNPC = QuestCareNPCNM( sceneId, selfId, misIndex )
	if MisCareNPC == 0 then --�����Զ����
		local ret = QuestCheckSubmitNM( sceneId, selfId, 0, MissionId, misIndex ) -- ��ȡ�����������Ϣ
		if ret > 0 then -- ����������
			return x300501_MissionCanSubmit( sceneId, selfId, 0, -1, MissionId )
		end
	end

	return 1
end


function x300501_SetMD(sceneId, selfId, MDNAME, value)
	SetQuestData(sceneId, selfId, MDNAME[1], MDNAME[2], MDNAME[3], value);
end

function x300501_GetMD(sceneId, selfId, MDNAME)

	return GetQuestData(sceneId, selfId, MDNAME[1], MDNAME[2], MDNAME[3])
end

function x300501_GiveItemToHuman(sceneId, selfId, ItemID, count)

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
function x300501_CheckDayChanged(sceneId, selfId)
	local lastDay = x300501_GetMD(sceneId, selfId, MD_GUOJIARENWU_LASTDAY)
	local today = GetDayOfYear()
	if lastDay ~= today then	--���ڱ仯
		x300501_SetMD(sceneId, selfId, MD_GUOJIARENWU_LASTDAY, today)	
		x300501_SetMD(sceneId, selfId, MD_GUOJIARENWU_HIGH, 0)
	end
end

function x300501_ProcQuestHorseChanged(sceneId, selfId, horseId, MissionId)

	if x300501_IsCollectHorse(MissionId) == 0 then
		return
	end

	if (x300501_IsNeededHorse(MissionId, horseId) == 0) then
		return
	end

	if IsHaveHorse(sceneId, selfId, horseId) > 0 then
		--������Խ���
		local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId );
		if (GetQuestParam(sceneId, selfId, misIndex, 7) == 0) then
			Msg2Player(sceneId, selfId, "�����Ѿ���ɣ�����ȥ�㱨�ɣ�", 8, 3)
		end
		SetQuestByIndex(sceneId,selfId,misIndex,7,1)
		SetQuestByIndex(sceneId,selfId,misIndex,0,1)
		return
	end

	--ʧȥ��һƥ��ˣ���Ҫ�ж��Ƿ��ܽ�������
	x300501_IfHaveNeededHorse (sceneId, selfId, MissionId)

end

function x300501_IsNeededHorse(MissionId, horseId)

	if x300501_IsCollectHorse(MissionId) == 0 then
		return 0
	end

	local kindtype = mod(horseId, 10)
	if (MissionId < x300501_g_CollectHorse_Young) then
		if (kindtype >= 5) then
			return 0
		end
		local group = floor(horseId / 100)
		if (group ~= MissionId - x300501_g_CollectHorse_Mission_ID + 2 ) then
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

function x300501_IfHaveNeededHorse(sceneId, selfId, MissionId)

	local cansubmit = 0
	for i=0,5 do
		local horseId = GetHorseDataID(sceneId, selfId, i)
		if (horseId > 0) then
			cansubmit = x300501_IsNeededHorse(MissionId, horseId)
			if (cansubmit == 1) then
				break
			end
		end
	end

	if (cansubmit == 1) then
		--������Խ���
		local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId );
		SetQuestByIndex(sceneId,selfId,misIndex,7,1)
		SetQuestByIndex(sceneId,selfId,misIndex,0,1)
	else
		--���񲻿��Խ���
		local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId );
		SetQuestByIndex(sceneId,selfId,misIndex,7,0)
		SetQuestByIndex(sceneId,selfId,misIndex,0,0)	
	end

	return cansubmit
end

function x300501_CheckSubmitNPC( sceneId,selfId,idScript,idMission,npcGUID )
	
	if IsHaveQuestNM( sceneId, selfId, idMission ) == 0 then
		-- ���û���������
		return 0
	end
	
	if x300501_IsEscort(idMission) == 1 then
		
		--��������Ĵ���
		return CallScriptFunction(300519,"CheckSubmitNPC",sceneId,idMission,npcGUID)
		
	elseif x300501_IsDeliver(idMission) == 1 then
		
		--��������
		for i, setitem in x300501_g_DeliverTargetNPC do
			if setitem.missionID == idMission then
				if setitem.npcID == npcGUID then
					return 1
				else
					return 0
				end
			end
		end
	end
	
	--Ĭ������£���Ϊû�м�鲻ͨ��
	return 0
	
end



