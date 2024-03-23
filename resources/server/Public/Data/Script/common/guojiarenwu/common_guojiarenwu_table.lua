--MD_GUOJIARENWU_RANDMISSIONID	= {2, 0, 18}
--MD_GUOJIARENWU_RANDMISSIONTYPE  = {2, 18, 4}	--保证每次国家任务随机到的类型不同
--MD_GUOJIARENWU_LASTDAY	= {2, 22, 9}	--上次接任务日期或放弃任务的日期

--MD_GUOJIARENWU_CIRCLE		= {3, 0, 6}	--当轮环数的技术
--MD_GUOJIARENWU_HIGH		= {3, 6, 8}	--当天高额奖励的计数
--MD_GUOJIARENWU_ABANDON		= {3, 14, 12}	--最后一次放弃时间

x300501_g_ScriptId = 300501
x300501_g_AbandonTime = 5
-- 任务名称
x300501_g_MissionName = "【个人】内政任务"

x300501_g_MissionCommentId	=	1100
x300501_g_VirtualMissionId_Low	=	1361
x300501_g_VirtualMissionId_High	=	1364
x300501_g_MissionRangeStart	=	6080
x300501_g_MissionRangeEnd		= 6499
x300501_g_MissionCommentMessage	=	"\t本任务为25级以上的玩家开放，每天可以完成#G20次#W任务，点选任务按钮后你将获得一个随机的任务，仅仅通过完成这个简单的任务，你便可以领取大量的经验。\n\t每10环任务为一轮，每日的#R前10环#W你将获得#G高倍奖励#W，并且在每日完成一轮任务之后，你会获得一个#R惊喜#W！一轮中，每次获得的经验都也将是不同的。\n\t当然，并不是每个任务都那么轻松可以完成，但你最好不要放弃任务，否则放弃任务后将会有#R5分钟不能接取任务#W的惩罚；并且，本日的#R高倍奖励将即刻消失#W，本日积累的#R环数将被清零#W，获得的奖励就会一落千丈了。"
x300501_g_MissionCommentWrongPlace =    "\t请你到大都内政任务发布官处接任务"
x300501_g_MissionCommentCountOver =     "次数已满，您今天不能再接这个任务了"
x300501_g_MissionNPCObjId_Low		= 138562
x300501_g_MissionNPCObjId_High		= 139127
x300501_g_LevelLess             = 25

x300501_OneRoundCount = 10		--每轮多少环
x300501_HighBonusCircleCount = 10	--每日几轮高奖

-- 收马任务ID
x300501_g_CollectHorse_Mission_ID	= 6430
x300501_g_CollectHorse_Mission_ID_End   = 6446
x300501_g_CollectHorse_Young		= 6445
-- 挖掘任务ID
x300501_g_DigMissionID              = 6470
x300501_g_DigMissionID_End          = 6479
-- 护送任务ID
x300501_g_EscortMissionID           = 6450
x300501_g_EscortMissionID_End       = 6461
-- 送信任务ID
x300501_g_DeliverMissionID           = 6350
x300501_g_DeliverMissionID_End       = 6386
x300501_g_DeliverItemID			= 13011600
x300501_g_DeliverItemCount		= 1
x300501_CountrySceneList	= {50, 150, 250, 350}
x300501_CapitalSceneId		= 0
x300501_LevelToCapital		= 300	--大都任务的开始等级

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
--第7组固定为护送任务，请注意
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

		if newtype == 0 then	--未找到符合玩家等级的任务
			return 0;
		end

		if IsBusMember(sceneId, selfId) == 0 or newtype ~= 7 then	--如果自己已经有镖车，不能再接护送任务
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
	--MissionId = 6479	--挖掘
	--MissionId = 6434	--收马
	--MissionId = 6262	--大内
	--MissionId = 6456	--护送
	--MissionId = 6420	--马奶
	--MissionId = 6386	--送信
	--MissionId = 6100	--购买
	--MissionId = 6410	--采集

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

	--低于规定最小等级的玩家不能接
	local userlevel = GetLevel(sceneId, selfId);
	if userlevel < x300501_g_LevelLess then
		return 0
	end

        -- 添加“内政任务说明”
	AddQuestTextNM(sceneId, selfId, targetId, x300501_g_MissionCommentId, 13, -1)


			
	local randMissionId = x300501_GetRandMissionId(sceneId, selfId)
	if randMissionId > 0 then
		if IsHaveQuestNM(sceneId, selfId, randMissionId) > 0 then
			return 0;	--已经接到了子任务，不需要再显示空壳任务了
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

	--如果玩家等级过高，显示一个特殊的内政任务选项，点击后会提示玩家去大都接任务
	if (userlevel >= x300501_LevelToCapital and virtualMisId == x300501_g_VirtualMissionId_Low) then
		AddQuestNumText( sceneId, x300501_g_VirtualMissionId_Low, x300501_g_MissionName, 13)
		return 0;
	end
	--如果还没接内政子任务，显示空壳任务的名称
	--允许randMissionId不是0，说明已经随机过子任务，但由于背包满、任务数量满等情况没有成功接到
	if QuestCheckAcceptNM( sceneId, selfId, targetId, virtualMisId ) > 0 then
		x300501_AddMissionTextByState(sceneId, selfId, targetId, virtualMisId);
	end

	return ret;
end

--选中任务
function x300501_ProcEventEntry( sceneId, selfId, targetId, MissionId)

	if MissionId == x300501_g_MissionCommentId then
	-- 显示内政任务说明内容
		QuestCom(sceneId, selfId, x300501_g_MissionCommentId)
		x300501_DisplayMissionEventMessage (sceneId, selfId, targetId, MissionId, x300501_g_MissionCommentMessage)		
		return 0;
	end

	--如果玩家等级过高，提示玩家去大都接任务
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
	if MissionId == x300501_g_VirtualMissionId_Low or MissionId == x300501_g_VirtualMissionId_High then	--接收空壳任务时要检查是否达到次数限制
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

	if MissionId == x300501_g_VirtualMissionId_Low or MissionId == x300501_g_VirtualMissionId_High then	--显示空壳任务界面
		BeginQuestEvent( sceneId)
		-- 任务名称
			AddQuestText( sceneId, "#Y"..x300501_g_MissionName)
		--任务描述
			AddQuestText( sceneId, GetQuestDescNM (sceneId, selfId, MissionId))
			AddQuestText( sceneId, " " )
		--任务奖励
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
		--小提示
			AddQuestText( sceneId, "#c00FF00小提示:" )
			AddQuestText( sceneId, "#c00FF00如果想要了解本任务的细节，请点击内政任务说明按钮。" )
		EndQuestEvent()
		ret = DispatchQuestInfoNM( sceneId, selfId, targetId, x300501_g_ScriptId, MissionId)
		return 0;
	else
		local randMissionId = x300501_GetRandMissionId(sceneId, selfId)
		if randMissionId == 0 or IsHaveQuestNM( sceneId, selfId, randMissionId ) == 0 then	-- 如果没这个任务直接退出
			return 0
		end
		--这里显示子任务的界面
		ret = x300501_ShowMissionInfoByState(sceneId, selfId, targetId, randMissionId)
	end
  
	return ret;
end

--完成任务
--返回1代表成功，0代表交任务失败
function x300501_ProcQuestSubmit( sceneId, selfId, targetId, selectId, MissionId )

	MissionId = x300501_GetRandMissionId(sceneId, selfId);
	
	if MissionId == nil or MissionId <= 0 then
        	return 0
    	end

	if IsHaveQuestNM( sceneId, selfId, MissionId ) == 0 then	-- 如果没这个任务直接退出
		return 0
	end

	if IsHaveQuestNM( sceneId, selfId, MissionId ) <= 0 then	-- 如果没这个任务直接退出
		return 0
	end

	local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )

	--判断是最后环节的提交还是中间环节的提交
	local ret = 0
	if x300501_IsDig(MissionId) == 1 then
		ret = 1				--挖掘不存在中间的提交环节
	elseif x300501_IsEscort(MissionId) == 1 then
		ret = CallScriptFunction( 300519, "ProcQuestSubmitOrContinue", sceneId, selfId, targetId, MissionId)	--护送存在中间的提交环节
	elseif x300501_IsCollectHorse(MissionId) == 1 then	
		ret = 1				--收马不存在中间的提交环节
	elseif x300501_IsDeliver(MissionId) == 1 then 
		--local oldTargetId = x300501_CheckMissionNPC(sceneId, selfId, MissionId);
		local targetGuid = GetMonsterGUID( sceneId, targetId)
		local reply_npcid = GetQuestSubmitNPCGUIDNM(sceneId, selfId, misIndex)
		if targetGuid == reply_npcid then		--在接任务的NPC处提交
			ret = 1
		else					--在收信人处提交
			ret = 0
			if 0 == DelItem(sceneId, selfId, x300501_g_DeliverItemID, x300501_g_DeliverItemCount) then
				Msg2Player(sceneId, selfId, "无法扣除任务道具，请稍候重试", 8, 3)
				Msg2Player(sceneId, selfId, "无法扣除任务道具，请稍候重试", 8, 2)
			else
				local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )
				SetQuestByIndex( sceneId, selfId, misIndex, 0, 1)
				SetQuestByIndex( sceneId, selfId, misIndex, 7, 1)
				Msg2Player(sceneId, selfId, "任务已经完成，快点回去汇报吧！", 8, 3)
			end
		end
	else
		ret = 1
	end
	
	--必须是最后环节的提交才继续执行
	if ret == 0 then
		return
	end

	local isFinish = GetQuestParam( sceneId, selfId, misIndex, 7)
	if (isFinish ~= 1) then
		return
	end

	--计算经验和金钱的奖励
	local moneytype = 0;
	local curlevel = GetLevel(sceneId, selfId) 
	local exp = x300501_GetExpAward ( sceneId, selfId, curlevel );
	local money,shengw = x300501_GetMoneyAward ( sceneId, selfId, curlevel );

	--收马任务可能有加倍奖励
	if x300501_IsCollectHorse(MissionId) == 1 then
		local commitret, awardrate = CallScriptFunction (300516 , "HorseSubmit", sceneId, selfId, MissionId)
		if (commitret == 0) then	--没有成功交马
			return 0
		end
		exp = exp * awardrate
		money = money * awardrate
		shengw = shengw * awardrate
	end

	--处理任务完成
	ret = CircleQuestComplateNM( sceneId, selfId, targetId, MissionId);

	if ret == 1 then -- 如果成功完成
		
		local circle, highcircle = x300501_SetRounds(sceneId, selfId)
		x300501_DisplayCircleMessage (sceneId, selfId, MissionId)
		QuestUnCom( sceneId, selfId, x300501_g_VirtualMissionId_Low)
		QuestUnCom( sceneId, selfId, x300501_g_VirtualMissionId_High)
		x300501_SetMD(sceneId, selfId, MD_GUOJIARENWU_RANDMISSIONID, 0)
		x300501_DisplayCompleteMessage(sceneId, selfId, targetId, MissionId);
		--奖励经验
		if exp > 0 then
			AddExp(sceneId, selfId, exp)
		end
		--奖励金钱
		if money > 0 then
			AddMoney(sceneId, selfId, moneytype, money)
		end
		--奖励金钱
		if shengw > 0 then
			local oldshengw = GetShengWang(sceneId, selfId)
			SetShengWang(sceneId, selfId, oldshengw + shengw)
		end
		--显示金钱和经验的奖励
		x300501_DisplayAwardInfo(sceneId, selfId, targetId, -1, -1, moneytype, money, exp, 0, shengw)
		--如果是每日最后一环高奖则奖励物品和国家金库
		if (highcircle == x300501_HighBonusCircleCount) then
			x300501_GetItemAwardDirectly ( sceneId, selfId, curlevel );
			--AddCountryResource (sceneId, selfId, 2, 2000, 1);
		end
        if circle == x300501_HighBonusCircleCount then
            CallScriptFunction( 256216, "FinishNeizheng", sceneId, selfId)
        end

	else -- 如果未成功完成
		x300501_DisplayCompleteMissionErrorMessage(sceneId, selfId, ret);
		return 0
	end

	return 1;
end

--****************************国家任务

--经验奖励
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
    -- 环数减半，所以经验翻倍
    BonusExp = BonusExp * 2
	return BonusExp;

end

--金钱奖励
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
--道具直接奖励
function x300501_GetItemAwardDirectly(sceneId, selfId, startlevel)

	local spec;
	local ret = 0;

	for i, item in x300501_g_ItemAwardCertain do
		if startlevel >= item.levelMin and startlevel < item.levelMax then
			local rnum = random(1, item.num);
			local count = random(1, item.maxcount);
			ret = x300501_GiveItemToHuman (sceneId, selfId, item.id[rnum], count)
			if (ret > 0) then
				Msg2Player(sceneId, selfId, format("#Y获得%d个物品#R#{_ITEM%d}#Y的奖励", count, item.id[rnum]), 8, 3);
			end
			break
		end
	end
	return ret
end

--是否是收马任务
function x300501_IsCollectHorse(MissionId)
	if MissionId >= x300501_g_CollectHorse_Mission_ID and MissionId <= x300501_g_CollectHorse_Mission_ID_End then
		return 1
	else
		return 0
	end
end

--是否是挖掘任务
function x300501_IsDig(MissionId)
	if MissionId >= x300501_g_DigMissionID and MissionId <= x300501_g_DigMissionID_End then
		return 1
	else
		return 0
	end
end

--是否是护送任务
function x300501_IsEscort(MissionId)
	if MissionId >= x300501_g_EscortMissionID and MissionId <= x300501_g_EscortMissionID_End then
		return 1
	else
		return 0
	end
end

--是否是送信任务
function x300501_IsDeliver(MissionId)
	if MissionId >= x300501_g_DeliverMissionID and MissionId <= x300501_g_DeliverMissionID_End then
		return 1
	else
		return 0
	end
end

-- 显示完成信息
function x300501_OnCanCompleteMission ( sceneId, selfId, targetId, MissionId )

	--收马任务的最后提交环节跟其它任务不一样
	if x300501_IsCollectHorse(MissionId)==1 then	
		CallScriptFunction( 300516, "OnCanCompleteMission", sceneId, selfId, targetId, MissionId )
		return
	end

	BeginQuestEvent(sceneId);
		--任务名称
		AddQuestText(sceneId, "#Y"..x300501_g_MissionName)
		--最后提交环节的文字
		if x300501_IsDeliver(MissionId) == 1 then --送信任务最后提交环节的文字没有写在表格里
			AddQuestText(sceneId, "\t信已经送到了？")
		else
			AddQuestText(sceneId, GetQuestSuccessNM(sceneId, selfId, MissionId))
		end
		--任务奖励
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

--是否还在惩罚时间内，返回0表示仍然在惩罚时间内
function x300501_CheckAbandonPenaltyOff ( sceneId, selfId, targetId )

	local curMinute = GetMinOfDay() + 1	--变成从1开始
	local curDay = GetDayOfYear()		

	local lastday =  x300501_GetMD(sceneId, selfId, MD_GUOJIARENWU_LASTDAY)
	local lastMinute =  x300501_GetMD(sceneId, selfId, MD_GUOJIARENWU_ABANDON)

	if (lastMinute == 0) then --没放弃任务
		return 1;
	end

	local bCanAccept = 1
	if (lastday == curDay) then		--放弃任务后，还没到第二天
		if (curMinute >= lastMinute)  and  (curMinute - lastMinute < x300501_g_AbandonTime) then 
			bCanAccept = 0
		end
	elseif (curDay - lastday == 1) or (lastday == 365 and curDay == 0) then	--放弃任务后，到了第二天
		if 1441 - lastMinute + curMinute <= x300501_g_AbandonTime then
			bCanAccept = 0
		end
	end
	--未处理跨非闰年的情况，跨非闰年会忽略惩罚时间

	if (bCanAccept == 0) then
		--不能接受任务
		local str = format("#Y"..x300501_g_MissionName.."#W\n\t你放弃任务不足%d分钟，不能接受任务！" , x300501_g_AbandonTime);
		BeginQuestEvent(sceneId);
			AddQuestText(sceneId, str);
		EndQuestEvent(sceneId);
		DispatchQuestEventList(sceneId, selfId, targetId);
		return 0
	end

	--可以接受任务
	if( lastMinute ~= 0 ) then 
		x300501_SetMD(sceneId, selfId, MD_GUOJIARENWU_ABANDON, 0)
	end

	return 1;
end

--根据任务状态显示任务信息
function x300501_ShowMissionInfoByState( sceneId, selfId, targetId, MissionId )

	if IsHaveQuestNM( sceneId, selfId, MissionId ) == 0 then	-- 如果没有这个任务
		local ret = QuestCheckAcceptNM( sceneId, selfId, targetId, MissionId )
		if ret > 0 then	-- 如果可以接这个任务
			if IsQuestFullNM(sceneId, selfId)==1 then
				Msg2Player(sceneId, selfId, "#Y你已经接了太多的任务", 8, 3)
				Msg2Player(sceneId, selfId, "#Y你已经接了太多的任务", 8, 2)
				return 0
			end
			return x300501_AutoAccept ( sceneId, selfId, targetId, MissionId )
		else
			x300501_DisplayMissionAcceptErrorMessage(sceneId, selfId, ret);
			return 0;
		end
	else --如果有这个任务
		local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )
		local isFinish = GetQuestParam( sceneId, selfId, misIndex, 7)
		if isFinish == 1 then
			x300501_OnCanCompleteMission ( sceneId, selfId, targetId, MissionId )-- 显示完成信息
		else
			x300501_ShowMissionContinueInfo( sceneId, selfId, targetId, MissionId ) -- 显示任务未完成信息
		end
		return 0;
	end
	
	return 0;
end

function x300501_ShowMissionContinueInfo( sceneId, selfId, targetId, MissionId) -- 显示任务未完成信息

	local ret = 0
	if x300501_IsDig(MissionId) == 1 then
		ret = CallScriptFunction( 300518, "ShowMissionContinueInfo", sceneId, selfId, targetId, MissionId)
	elseif x300501_IsEscort(MissionId) == 1 then
		ret = CallScriptFunction( 300519, "ShowMissionContinueInfo", sceneId, selfId, targetId, MissionId)
	else
		--送信任务，在送信目标npc处
		if x300501_IsDeliver(MissionId) == 1 then --送信任务特殊处理 
			local targetGuid = GetMonsterGUID( sceneId, targetId)
			for i, setitem in x300501_g_DeliverTargetNPC do
				if setitem.missionID == MissionId then
					if setitem.npcID == targetGuid then
						BeginQuestEvent(sceneId);
							--任务名称
							AddQuestText(sceneId, "#Y"..x300501_g_MissionName)
							--任务成功的文本
							AddQuestText(sceneId, GetQuestSuccessNM(sceneId, selfId, MissionId))
						EndQuestEvent();
						DispatchQuestContinueInfoNM( sceneId, selfId, targetId, x300501_g_ScriptId, MissionId )
						return
					end
					break
				end
			end
		end
		QuestNotComplateInfoNM( sceneId, selfId, targetId, MissionId ) -- 显示任务未完成信息
	end
end

--接受空壳任务
function x300501_ProcQuestAccept( sceneId, selfId, targetId, MissionId)

	--如果玩家等级过高，提示玩家去大都接任务
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
		--随机一个子任务
		local missionType
		randMissionId, missionType = x300501_GenerateRandomMission ( sceneId, selfId, targetId );
	end

	if (randMissionId == 0) then
		return 0;
	end

	--显示子任务信息界面
	local ret = x300501_ShowMissionInfoByState(sceneId, selfId, targetId, randMissionId)
	return 1;
end

--自动接受子任务
function x300501_AutoAccept( sceneId, selfId, targetId, MissionId )
	--MissionId必须是有效的子任务
	if IsHaveQuestNM( sceneId, selfId, MissionId ) > 0 then
		return 1
	end
	
	--检查前置任务
	local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId, MissionId )
	if FrontMissiontId1 ~= -1 then
		if IsQuestHaveDoneNM( sceneId, selfId, FrontMissiontId1 ) == 0 then
			return 0--如果前置任务没做直接返回
		end
	end
	if FrontMissiontId2 ~= -1 then
		if IsQuestHaveDoneNM( sceneId, selfId, FrontMissiontId2 ) == 0 then
			return 0--如果前置任务没做直接返回
		end
	end
	if FrontMissiontId3 ~= -1 then
		if IsQuestHaveDoneNM( sceneId, selfId, FrontMissiontId3 ) == 0 then
			return 0--如果前置任务没做直接返回
		end
	end

	--接受任务
	local ret = 0
	if x300501_IsDig(MissionId) == 1 then
		ret = AddQuest( sceneId, selfId, MissionId, 300518, 0, 0, 0, 1)
	elseif x300501_IsEscort(MissionId) == 1 then
		ret = AddQuest( sceneId, selfId, MissionId, 300519, 0, 0, 0, 1)
	elseif x300501_IsDeliver(MissionId) == 1 then --送信任务特殊处理 
		--如果是送信任务，在这里给玩家添加物品到背包，如果物品添加失败则任务也不能添加
			BeginAddItem(sceneId)
				AddItem( sceneId, x300501_g_DeliverItemID, x300501_g_DeliverItemCount )
			ret = EndAddItem(sceneId,selfId)
			if ret > 0 then
				AddItemListToPlayer(sceneId,selfId)
				--ret = AddQuestNM( sceneId, selfId, MissionId ) -- 给玩家添加任务
				ret = AddQuest( sceneId, selfId, MissionId, x300501_g_ScriptId, 0, 0, 0, 1)
			else
				ret = -1	--背包满
			end 
	else
		ret = AddQuestNM( sceneId, selfId, MissionId ) -- 给玩家添加任务
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
  --执行所有子任务公用的接受后处理

	--隐藏NPC头顶黄色叹号
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
	
  --显示任务信息
	if x300501_IsDig(MissionId) == 1 then
		CallScriptFunction( 300518, "ShowMissionInfo", sceneId, selfId, targetId, MissionId)
	elseif x300501_IsEscort(MissionId) == 1 then
		CallScriptFunction( 300519, "ShowMissionInfo", sceneId, selfId, targetId, MissionId)
	else
		BeginQuestEvent( sceneId)
		-- 任务名称
			AddQuestText( sceneId, "#Y"..x300501_g_MissionName)
		--任务描述
			AddQuestText( sceneId, GetQuestDescNM (sceneId, selfId, MissionId))
			AddQuestText( sceneId, " " )
		--任务目标
			AddQuestText( sceneId, "#Y任务目标：" )
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


  --执行其它接受后续处理
	if x300501_IsDig(MissionId) == 1 then
		CallScriptFunction( 300518, "AfterAccept", sceneId, selfId, targetId, MissionId, misIndex )
	elseif x300501_IsEscort(MissionId) == 1 then
		CallScriptFunction( 300519, "AfterAccept", sceneId, selfId, targetId, MissionId, misIndex )
	elseif x300501_IsCollectHorse(MissionId) == 1 then	
		SetQuestEvent(sceneId, selfId, MissionId, 3 )
	elseif x300501_IsDeliver(MissionId) == 1 then 
	end

  --检查现在是否能够提交任务
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

  -- 设置完成标记
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
		lastCircle = 1;			--环数重置
	else						--环数增加
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
	local str = format("你接受了任务：%s", x300501_g_MissionName);
	Msg2Player(sceneId, selfId, str, 8, 3)
	Msg2Player(sceneId, selfId, str, 8, 2)
	return 1;
end

function x300501_DisplayAddMissionErrorMessage(sceneId, selfId, ret)
	local str;
	if ret == 0 then
		str = "添加任务失败！"
	elseif ret == -1 then
		str = "背包已满,请整理后再来接任务！"
	elseif ret == -2 then
		str = "任务已达到上限，无法接新的任务！"
	elseif ret == -3 then
		str = "金钱不足，无法接新的任务！"
	end

	Msg2Player(sceneId, selfId, str, 8, 3)
	return ret;
end

function x300501_DisplayMissionAcceptErrorMessage(sceneId, selfId, ret)

	local str = "未知错误，无法接新的任务！"
	if ret == -1 then
		str = "等级不足，无法接新的任务！"
	elseif ret == -2 then
		str = "等级过高，无法接新的任务！"
	elseif ret == -3 then
		str = "金钱不足，无法接新的任务！"
	elseif ret == -4 then
		str = "你不是本国玩家，无法接新的任务！"
	elseif ret == -5 then
		str = "职业类型不符，无法接新的任务！"
	elseif ret == -6 then
		str = "阵营不符，无法接新的任务！"
	elseif ret == -7 then
		str = "此人无此任务！"
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
		--任务奖励
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

--杀死怪物
function x300501_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
															--场景ID, 自己的ID, 怪物表位置号, 怪物objId, 任务ID
	MissionId = x300501_GetRandMissionId(sceneId, selfId);
	if (MissionId == 0) then
		return 0
	end

	if IsHaveQuestNM(sceneId, selfId, MissionId) == 0 then
		return 0
	end
	local NeedKilledNum, InstIndex, ObjName = GetQuestNeedKillObjInfoNM( sceneId, selfId, MissionId, objdataId, objId )

	if NeedKilledNum == 0 then --杀怪得物品类型的任务
		local KilledNum = GetMonsterOwnerCount( sceneId, objId ) --取得这个怪物死后拥有分配权的人数
		for i = 0, KilledNum-1 do
			local humanObjId = GetMonsterOwnerID( sceneId, objId, i ) --取得拥有分配权的人的objId
    			if humanObjId ~= -1 then
    				if IsHaveQuestNM( sceneId, humanObjId, MissionId ) > 0 then	--如果这个人拥有任务
        				local ItemCount, ItemID, ItemRand, ItemDropNum = GetQuestItemNM( sceneId, humanObjId, MissionId, InstIndex )
					--要收集的个数，物品ID，掉落率，一次最大掉落
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
	elseif NeedKilledNum > 0 then --单纯的杀怪任务
		local HumenNum = GetMonsterOwnerCount( sceneId, objId ) --取得这个怪物死后拥有分配权的人数
		for i = 0, HumenNum-1 do
			local humanObjId = GetMonsterOwnerID( sceneId, objId, i ) --取得拥有分配权的人的objId
			if humanObjId ~= -1 then
				if IsHaveQuestNM( sceneId, humanObjId, MissionId ) > 0 then	--如果这个人拥有任务
					local str = "";
					local KilledNum = x300501_GetMP(sceneId, humanObjId, MissionId, InstIndex)
					x300501_DisplayMissionKillMonsterMessage(sceneId, humanObjId, ObjName, KilledNum, NeedKilledNum);
					if KilledNum < NeedKilledNum then
						x300501_SetMP(sceneId, humanObjId, MissionId, InstIndex, KilledNum+1);
						if KilledNum == NeedKilledNum - 1 then
							x300501_SetMP(sceneId,humanObjId,MissionId,7,1)
							Msg2Player(sceneId, humanObjId, "任务已经完成，快点回去汇报吧！", 8, 3)
							local misIndex = GetQuestIndexByID(sceneId, humanObjId, MissionId);
							local MisCareNPC = QuestCareNPCNM( sceneId, humanObjId, misIndex )
							if MisCareNPC == 0 then --任务自动完成
								local ret = QuestCheckSubmitNM( sceneId, humanObjId, 0, MissionId, misIndex ) -- 获取完成任务检查信息
								if ret > 0 then -- 如果可以完成
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
				str = format( "#Y已经完成击败怪物: %d/%d", KilledNum+1, NeedKilledNum )
			else
				str = format( "#Y已经完成击败#G%s#Y: %d/%d", ObjName, KilledNum+1, NeedKilledNum )
			end
		 else
			if ObjName == "" then
				str = format( "#Y已经击败怪物: %d/%d", KilledNum+1, NeedKilledNum )
			else
				str = format( "#Y已经击败#G%s#Y: %d/%d", ObjName, KilledNum+1, NeedKilledNum )
			end
			ret = 0;
		end
		if str ~= "" then
			Msg2Player(sceneId, selfId, str, 8, 3)
		end
	end

	return ret;
	
end

--任务可以完成但还未提交
function x300501_MissionCanSubmit( sceneId, selfId, targetId, selectId, MissionId )
	local ret = 0;

	if (IsHaveQuestNM(sceneId, selfId, MissionId) == 0) then
		return 0
	end

	local misIndex = GetQuestIndexByID(sceneId, selfId, MissionId);
	ret = QuestComplateNM( sceneId, selfId, targetId, MissionId, selectId ); -- 获取完成任务信息

	if ret == 1 then -- 如果成功完成

		QuestUnCom( sceneId, selfId, x300501_g_VirtualMissionId_Low)
		QuestUnCom( sceneId, selfId, x300501_g_VirtualMissionId_High)
		x300501_DisplayCompleteMessage(sceneId, selfId, targetId, MissionId);
		x300501_PushAfterMission(sceneId, selfId, targetId, MissionId );
		return 1 -- 返回成功

	else -- 如果未成功完成
		x300501_DisplayCompleteMissionErrorMessage(sceneId, selfId, ret);
		return 0
	end
	return 0
end

function x300501_DisplayCircleMessage(sceneId, selfId, MissionId )

	local circles = x300501_GetMD(sceneId, selfId, MD_GUOJIARENWU_CIRCLE)
	local highcircle = x300501_GetMD(sceneId, selfId, MD_GUOJIARENWU_HIGH)

	local str = format( "环数: %d/%d", circles, x300501_OneRoundCount );
	if highcircle <= x300501_HighBonusCircleCount then
		str = str..format("  本日高奖环数：%d/%d", highcircle, x300501_HighBonusCircleCount);
	end
	Msg2Player(sceneId, selfId, str, 8, 3)

end

function x300501_DisplayCompleteMessage(sceneId, selfId, targetId, MissionId)
	
	local MissionName = x300501_g_MissionName;
	local str = format( "你完成了任务：%s", MissionName);

	Msg2Player(sceneId, selfId, str, 8, 3)
	return 1;

end

function x300501_DisplayAwardInfo(sceneId, selfId, targetId, MissionId, selectId, moneyType, money, expAward, honorType, honor)--提示玩家金钱经验声望的奖励信息
	
	if MissionId >= 0 then
		moneyType, money, expAward, honorType, honor = AwardMoneyExpHonorNM(sceneId, selfId, targetId, MissionId, selectId)
	end
	local str;

	if expAward > 0 then
		str = format("#Y获得#R经验%d#Y的奖励。", expAward);
		Msg2Player(sceneId, selfId, str, 8, 2)
	end

	if money > 0 then
		if moneyType == 0 then --银
			str = format("#Y获得#R现银#{_MONEY%d}#Y的奖励。", money);
		elseif moneyType == 1 then -- 绑定银
			str = format("#Y获得#R银卡#{_MONEY%d}#Y的奖励。", money);
		elseif moneyType == 2 then --金
			str = format("#Y获得#R现金#{_MONEY%d}#Y的奖励。", money);
		elseif moneyType == 3 then -- 绑定金
			str = format("#Y获得#R金卡#{_MONEY%d}#Y的奖励。", money);
		end

		Msg2Player(sceneId, selfId, str, 8, 2)
	end

	if honor > 0 then
		if honorType == 0 then --声望
			str = format("#Y获得#R声望%d#Y的奖励。", honor);
		elseif honorType == 1 then	--声望
			str = format("#Y获得#R声望%d#Y的奖励。", honor);
		elseif honorType == 2 then --PK
			str = format("#Y获得#RPK值%d#Y的奖励。", honor);
		elseif honorType == 3 then --荣誉
			str = format("#Y获得#R荣誉%d#Y的奖励。", honor);
		elseif honorType == 4 then -- 帮贡
			str = format("#Y获得#R帮贡%d#Y的奖励。", honor);
		elseif honorType == 5 then -- 文采
			str = format("#Y获得#R文采%d#Y的奖励。", honor);
		end

		Msg2Player(sceneId, selfId, str, 8, 2)
	end
	return 1;

end


function x300501_DisplayCompleteMissionErrorMessage(sceneId, selfId, ret)
	
	local str = "未知错误，无法完成任务！"
	if ret == -2 then
		str = "请选择奖励物品！"
	elseif ret == -3 then
		str = "背包已满,请整理后再来交任务！"
	elseif ret == -4 then
		str = "扣除任务物品失败！"
	end

	Msg2Player(sceneId, selfId, str, 8, 3)
	return ret;

end

function x300501_PushAfterMission(sceneId, selfId, targetId, MissionId )
	local AfterMissionType, AfterMissionId = GetAfterQuestIdNM( sceneId, selfId, MissionId )
	if AfterMissionId ~= -1 then
		if AfterMissionType == 0 then
			--呼叫下一个任务的界面
			x300501_ProcEventEntry( sceneId, selfId, targetId, AfterMissionId);
		else
			--直接PUSH下一个任务
			PushAfterQuestNM( sceneId, selfId, targetId, AfterMissionId )
		end
	end
	return 1;
end

--任务放弃--这里需要设置放弃时间MissionData
function x300501_ProcQuestAbandon( sceneId, selfId, MissionId )
	MissionId = x300501_GetRandMissionId(sceneId, selfId);
	if (MissionId == 0 or IsHaveQuestNM( sceneId, selfId, MissionId ) == 0 ) then
		--处理同时接了多个内政子任务的情况,将所有内政任务都删除
		x300501_DelAllWrongMission(sceneId, selfId)
		return 0
	end
	local ret = 0

	if x300501_IsDeliver(MissionId) == 1 then --送信任务特殊处理 
		
		local nCount = GetItemCount(sceneId,selfId,x300501_g_DeliverItemID)
		if nCount > x300501_g_DeliverItemCount then
			nCount = x300501_g_DeliverItemCount
		end
		
		if nCount > 0 and 0 == DelItem(sceneId, selfId, x300501_g_DeliverItemID, nCount) then
			Msg2Player(sceneId, selfId, "无法扣除任务道具，请稍候重试", 8, 3)
			Msg2Player(sceneId, selfId, "无法扣除任务道具，请稍候重试", 8, 2)
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
		--重置随机子任务
		x300501_SetMD(sceneId, selfId, MD_GUOJIARENWU_RANDMISSIONID, 0)
		--x300501_SetMD(sceneId, selfId, MD_GUOJIARENWU_CIRCLE, 0)
		if x300501_GetMD(sceneId, selfId, MD_GUOJIARENWU_HIGH) < x300501_HighBonusCircleCount then
			x300501_SetMD(sceneId, selfId, MD_GUOJIARENWU_HIGH, x300501_HighBonusCircleCount)
			 --如果是高奖状态下放弃任务，则环数直接从零开始
			x300501_SetMD(sceneId, selfId, MD_GUOJIARENWU_CIRCLE, 0)
		else
			
			--低奖状态放弃任务，则新增环数
			x300501_SetRounds(sceneId, selfId)
			
		end

		x300501_DisplayAbandonMessage(sceneId, selfId, MissionId);
	end

	return ret;
end

function x300501_DelAllWrongMission(sceneId, selfId)
	--处理同时接了多个内政子任务的情况,将所有内政任务都删除
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
	local str = format("你放弃了任务：%s！", MissionName);

	Msg2Player(sceneId, selfId, str, 8, 3)
	Msg2Player(sceneId, selfId, str, 8, 2)
	return 1;
end

function x300501_ProcQuestAttach( sceneId, selfId, targetId, npcGuid, misIndex, MissionId )
	--挖掘、护送子任务不会走这里，会走自己的脚本
	MissionId = x300501_GetRandMissionId(sceneId, selfId);
	if (MissionId == 0) then
		return 0
	end

	if IsHaveQuestNM( sceneId, selfId, MissionId ) == 0 then	-- 如果没有这个任务
		return 0
	end

	--送信任务，点击了送信目标时，如果还没送信，显示内政任务的选项
	if x300501_IsDeliver(MissionId) == 1 then --送信任务特殊处理
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

	--如果是任务提交人，显示选项
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

--物品改变
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
		if Num < NeedNum then --还没有完成任务
			x300501_SetMP(sceneId, selfId, MissionId, ObjIndex, Num);
			x300501_SetMP(sceneId,selfId,MissionId,7,0)
		elseif Num >= NeedNum then
			if x300501_GetMP(sceneId,selfId,MissionId,7) == 1 then	--之前已经完成了
				return 0
			end
			x300501_SetMP(sceneId, selfId, MissionId, ObjIndex, NeedNum);
			x300501_SetMP(sceneId,selfId,MissionId,7,1)
			Msg2Player(sceneId, selfId, "任务已经完成，快点回去汇报吧！", 8, 3)
			local misIndex = GetQuestIndexByID(sceneId, selfId, MissionId);
			local MisCareNPC = QuestCareNPCNM( sceneId, selfId, misIndex )
			if MisCareNPC == 0 then --任务自动完成
				local targetId = 0	--无意义
				local ret = QuestCheckSubmitNM( sceneId, selfId, targetId, MissionId, misIndex ) -- 获取完成任务检查信息
				if ret > 0 then -- 如果可以完成
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
			str = format("#Y获得物品#G#{_ITEM%d}#Y: %d/%d", itemId, Num, NeedNum );
		end
		ret = 0;
	elseif Num == NeedNum then
		str = format( "#Y已完成获得物品#G#{_ITEM%d}#Y: %d/%d", itemId, Num, NeedNum )
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

	if IsHaveQuestNM( sceneId, selfId, MissionId ) == 0 then	-- 如果没这个任务直接退出
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

	--任务自动完成
	local misIndex = GetQuestIndexByID(sceneId, selfId, MissionId);
	local MisCareNPC = QuestCareNPCNM( sceneId, selfId, misIndex )
	if MisCareNPC == 0 then --任务自动完成
		local ret = QuestCheckSubmitNM( sceneId, selfId, 0, MissionId, misIndex ) -- 获取完成任务检查信息
		if ret > 0 then -- 如果可以完成
			ret = x300501_MissionCanSubmit( sceneId, selfId, 0, -1, MissionId )
			return ret
		end
	end

	return 1
end

--离开区域
function x300501_ProcAreaLeaved( sceneId, selfId, ScriptId, MissionId )
	return 1;
end

--区域定时器
function x300501_ProcTiming( sceneId, selfId, ScriptId, MissionId )
	return 1;
end

--**********************************************************************
--采集任务
--打开ItemBox
function x300501_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )

	local MissionId = x300501_GetRandMissionId(sceneId, selfId);
	if MissionId < -1 then
		MissionId = x300501_g_DefaultMissionId;
	end

	if IsHaveQuestNM( sceneId, selfId, MissionId ) == 0 then		--没有这个任务
		local MissionName = x300501_g_MissionName;
		local reply_npcid;
		if (GetLevel(sceneId, selfId) >= x300501_LevelToCapital) then
			reply_npcid = x300501_g_MissionNPCObjId_High;
		else
			reply_npcid = x300501_g_MissionNPCObjId_Low;
		end
		Msg2Player(sceneId, selfId, format("#Y去找#R@npc_%d接受#Y%s后才能操作！", reply_npcid, MissionName), 8, 3);
		return 1
	end

	local MissionId, needItemCount, collNum = GetItemIdInItemBoxNM( sceneId, selfId, targetId, gpType, needItemID )
	local str
	if MissionId < 0 then
		str = "你不需要这个物品";
		Msg2Player(sceneId, selfId, str, 8, 3);
		return 1 --没有这个任务
	end

	local itemCountNow = GetItemCount( sceneId, selfId, needItemID )
	if itemCountNow >= needItemCount then
		str = "物品已经收集齐全";
		Msg2Player(sceneId, selfId, str, 8, 3);
		return 1
	end
	return 0

end

--回收
function x300501_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	local MissionId, needItemCount, collNum = GetItemIdInItemBoxNM( sceneId, selfId, targetId, gpType, needItemID )

    --采集任务 Bug fixed by czg 2008-12-2
	if MissionId == -1 then
		MissionId = x300501_GetRandMissionId ( sceneId, selfId);
	end

	local str;
	if IsHaveQuestNM( sceneId, selfId, MissionId ) == 0 then	-- 如果没这个任务直接退出
		local MissionName = x300501_g_MissionName;
		if MissionName == nil or MissionName == "" then
			str = "你没有接受相关任务！"
		else
			str = format("你没有接受#Y%s#W！", MissionName);
		end
		Msg2Player(sceneId, selfId, str, 8, 3);
		return 1
	end

	--如果该任务已经完成直接退出
	if IsQuestHaveDoneNM( sceneId, selfId, MissionId ) > 0 then --任务已经完成
		return 0
	end

	local itemCountNow = GetItemCount( sceneId, selfId, needItemID )
	if itemCountNow >= needItemCount then
		local str = "物品已经收集齐全";
		Msg2Player(sceneId, selfId, str, 8, 3);
		return 0
	end

	--决定一次采集多少
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

--打开
function x300501_OnProcOver( sceneId, selfId, targetId )
	return 1
end

--打开后检查
function x300501_OpenCheck( sceneId, selfId, targetId )
	return 1
end

--**********************************************************************
--定点使用物品任务
function x300501_PositionUseItem( sceneId, selfId, BagIndex, impactId, MissionId )

	MissionId = x300501_GetRandMissionId(sceneId, selfId);

	local ItemID = GetItemTableIndexByIndex( sceneId, selfId, BagIndex ) --得到物品ID
	local MissionId = GetQuestIDByItemIDNM( sceneId, selfId, ItemID )

	if MissionId == -1 then 	--没有找到这个任务
		return 0
	end

	if IsHaveQuestNM( sceneId, selfId, MissionId ) == 0 then	-- 如果没这个任务直接退出
		return 0
	end

	local scene, posx, posz, radii, MissionIdx, dispStr, bDispOther, otherStr = GetQuestUseItemInfoNM( sceneId, selfId, MissionId, ItemID )
	if scene == -1 or sceneId ~= scene then --没有找到这个任务信息
		return 0
	end

	if posx > 0 then --需要检查地点
		local PlayerPosX,PlayerPosZ = GetWorldPos( sceneId, selfId )

		local distanceRet = radii * radii - (posx - PlayerPosX) * (posx - PlayerPosX) - (posz - PlayerPosZ) * (posz - PlayerPosZ)
		if distanceRet <= 0 then
			local str = format("你应该在@sceneid_%d[%d,%d]使用此物品！", scene, posx, posz )
			Msg2Player(sceneId, selfId, str, 8, 3);
			return 0
		end
	end

	if x300501_GetMP(sceneId, selfId, MissionId, MissionIdx) == 1 then
		return 0
	end

	--删除物品
	EraseItem(sceneId, selfId, BagIndex)

	--发送提示
	x300501_SetMP(sceneId, selfId, MissionId, MissionIdx, 1);
	Msg2Player(sceneId, selfId, dispStr, 8, 3);

	if bDispOther > 0 then
		--待调
		Msg2Player(sceneId, selfId, otherStr, 8, 0);
	end

	--播放效果
	if impactId ~= -1 then
		SendSpecificImpactToUnit(sceneId, selfId, selfId, selfId, impactId, 0);
	end

	--任务自动完成
	local misIndex = GetQuestIndexByID(sceneId, selfId, MissionId);
	local MisCareNPC = QuestCareNPCNM( sceneId, selfId, misIndex )
	if MisCareNPC == 0 then --任务自动完成
		local ret = QuestCheckSubmitNM( sceneId, selfId, 0, MissionId, misIndex ) -- 获取完成任务检查信息
		if ret > 0 then -- 如果可以完成
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
		local str = "背包已满，无法得到物品！";
		Msg2Player(sceneId, selfId, str, 8, 3);
		Msg2Player(sceneId, selfId, str, 8, 2)
	end
	return ret
end

--检查日期有没有变化，并重置高奖次数，并保存新的日期
function x300501_CheckDayChanged(sceneId, selfId)
	local lastDay = x300501_GetMD(sceneId, selfId, MD_GUOJIARENWU_LASTDAY)
	local today = GetDayOfYear()
	if lastDay ~= today then	--日期变化
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
		--任务可以交付
		local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId );
		if (GetQuestParam(sceneId, selfId, misIndex, 7) == 0) then
			Msg2Player(sceneId, selfId, "任务已经完成，快点回去汇报吧！", 8, 3)
		end
		SetQuestByIndex(sceneId,selfId,misIndex,7,1)
		SetQuestByIndex(sceneId,selfId,misIndex,0,1)
		return
	end

	--失去了一匹骑乘，需要判断是否还能交付任务
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
		--任务可以交付
		local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId );
		SetQuestByIndex(sceneId,selfId,misIndex,7,1)
		SetQuestByIndex(sceneId,selfId,misIndex,0,1)
	else
		--任务不可以交付
		local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId );
		SetQuestByIndex(sceneId,selfId,misIndex,7,0)
		SetQuestByIndex(sceneId,selfId,misIndex,0,0)	
	end

	return cansubmit
end

function x300501_CheckSubmitNPC( sceneId,selfId,idScript,idMission,npcGUID )
	
	if IsHaveQuestNM( sceneId, selfId, idMission ) == 0 then
		-- 如果没有这个任务
		return 0
	end
	
	if x300501_IsEscort(idMission) == 1 then
		
		--护送任务的处理
		return CallScriptFunction(300519,"CheckSubmitNPC",sceneId,idMission,npcGUID)
		
	elseif x300501_IsDeliver(idMission) == 1 then
		
		--送信任务
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
	
	--默认情况下，认为没有检查不通过
	return 0
	
end



