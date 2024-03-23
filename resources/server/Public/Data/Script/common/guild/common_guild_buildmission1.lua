--MD_BANGHUI_RANDMISSIONID	= {4, 0, 18}
--MD_BANGHUI_RANDMISSIONTYPE	= {4, 18, 4}	--保证每次帮会任务随机到的类型不同
--MD_BANGHUI_LASTDAY		= {4, 22, 9}	--接任务日期或放弃任务的日期
--
--MD_BANGHUI_CIRCLE		= {5, 0, 6}	--当轮环数的计数
--MD_BANGHUI_HIGH		= {5, 6, 8}	--当天高额奖励的计数
--MD_BANGHUI_ABANDON		= {5, 14, 12}	--最后一次放弃时间

x300670_g_ScriptId = 300670
x300670_g_AbandonTime = 5
-- 任务名称
x300670_g_MissionName = "【帮会】帮会内政"

x300670_g_MissionCommentId	=	9031	
x300670_g_VirtualMissionId_Low	=	10000
x300670_g_VirtualMissionId_High	=	10000
x300670_g_MissionRangeStart	=	10001
x300670_g_MissionRangeEnd		= 10258
x300670_g_MissionCommentMessage	=	"\t帮会内政任务，您只需要按照帮会任务发布人的要求完成任务，就可以获得#G经验#W和#G帮贡#W的奖励。\n\t#G（随着玩家等级的增加，帮会内政任务的难度也会增加，所以，#Y20-50#G级的玩家是最合适完成此任务的。）"
x300670_g_MissionCommentWrongPlace =    "\t请你到大都帮会任务发布官处接任务"
x300670_g_MissionNPCObjId_Low		= 138533
x300670_g_MissionNPCObjId_High		= 138533
x300670_g_LevelLess             = 20 

x300670_OneRoundCount = 10		--每轮多少环
x300670_HighBonusCircleCount = 10	--每日几环高奖
--x300670_g_DeliverItemID			= 13011600
--x300670_g_DeliverItemCount		= 1
x300670_CountrySceneList	= {50, 150, 250, 350}
x300670_CapitalSceneId		= 0
x300670_LevelToCapital		= 300	--大都任务的开始等级
x300670_MisParam_NPCData	= 1	--保存N个目标NPC的序号: 每4个二进制位代表一个NPC, N<=8
x300670_MisParam_FindData	= 2	--保存N个目标NPC的结果: 每4个二进制位代表一个NPC, N<=8 
x300670_g_DeliverTargetCount	= 3	-- <= 8
x300670_AddGuildExpValue	= 1
x300670_MaxAddGuildExp		= 100
x300670_DeliverMissionTarget	= "找到"
x300670_DeliverTextFind		= "您已经找到了@npc_%d (%d/3)"
x300670_g_MissionCommentAfterAbandon = "\t很抱歉，你今天已经放弃过本任务，明天再来吧。"
x300670_g_MissionCommentAfterEnough = "\t你今天已经做过%d次帮会任务，做出的贡献够多了，明天再来帮忙吧。"
x300670_g_DeliverTargetNPC	= { 
					{
					    { npcId = 	138516, Dialog = "\t这点小事情也要来找我……\n\t好吧!一会我就带人去看看。"	}, --1
					    { npcId = 	138806, Dialog = "\t没有问题，我的朋友，很高兴能帮上你们的忙。"	}, --2
					    { npcId = 	138802, Dialog = "\t这个……最近我已经忙的焦头烂额了。\n\t这样吧，我处理完这事就过去。"	}, --3
					    { npcId = 	138600, Dialog = "\t我很乐意帮忙~不过，请稍等，小女子梳妆完毕，自会前往。"	}, --4
					    { npcId = 	138822, Dialog = "\t你们要大采购么？要不要我带上货单？"	}, --5
					    { npcId = 	138812, Dialog = "\t真主会保佑你的，我的孩子，我这就动身。"	}, --6
					    { npcId = 	138800, Dialog = "\t我会去的……不过，要等我的主子不在这里的时候。"	}, --7
					},
					{
					    { npcId = 	138817, Dialog = "\t巴吉让你来的？好吧，我正想去找他，上次他从我这里订购的货物，到现在帐也没付清！"	}, 
					    { npcId = 	138824, Dialog = "\t我金算盘一秒钟几十万金币上下，一会我派几个手下过去，这点小事，我就不亲自出马了！"	}, 
					    { npcId = 	138588, Dialog = "\t押运官的职责让我不能轻易离开，不过我可以让那些来押运的家伙帮点小忙……"	}, 
					    { npcId = 	138814, Dialog = "\t帮忙？有报酬么？一会我派个护卫去看看，没有赚头的生意我从来不做！"	}, 
					    { npcId = 	138500, Dialog = "\t啊？为什么要来找我？"	}, 
					    { npcId = 	138276, Dialog = "\t这事情……我要先请示我们族长，不过我相信他一定会同意的。"	}, 
					    { npcId = 	138270, Dialog = "\t好，你们帮的人都是我的老顾客，我一定准时到。"	}, 
					},
					{
					    { npcId = 	138190, Dialog = "\t好的好的，等我找回那几个淘气的孩子，我就过去。"	}, 
					    { npcId = 	138155, Dialog = "\t很高兴能为贵帮帮忙，我准备一下马上就到。"	}, 
					    { npcId = 	138166, Dialog = "\t需要我的帮助？没问题！我术忽台是出了名的好说话。"	}, 
					    { npcId = 	138170, Dialog = "\t很高兴能为贵帮进些微薄之力，我准备一下马上就到。"	}, 
					    { npcId = 	138655, Dialog = "\t我从不问江湖事，不过你们帮主的面子我还是要给的。\n\t好吧，你先回去，我随后就到。"	}, 
					    { npcId = 	138000, Dialog = "\t有人请其其格帮忙？好啊，不过我要带上我的小羊羔~"	}
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
								--找人
								{9030},	
								--收集
								{ 10001, 10002, 10003, 10004, 10005, 10006, 10007, 10008, 10009 },
						}
					},
					{
						level	=	{ min=30, max=39 },
						rate	=	{ 50, 100 },
						MissionId = {
								--找人
								{9030},	
								--收集
								{ 10015, 10016, 10017, 10018, 10019, 10020, 10021, 10022, 10023, 10024, 10025, 10026, 10027, 10028, 10029 },
						}
					},
					{
						level	=	{ min=40, max=49 },
						rate	=	{ 50, 100 },
						MissionId = {
								--找人
								{9030},	
								--收集
								{ 10035, 10036, 10037, 10038, 10039, 10040, 10041, 10042, 10043, 10044, 10045, 10046, 10047, 10048, 10049, 10050, 10051, 10052, 10053, 10054, 10055, 10056, 10057, 10058, 10059, 10060, 10061, 10062, 10063, 10064, 10065, 10066, 10067 },
						}
					},
					{
						level	=	{ min=50, max=59 },
						rate	=	{ 50, 100 },
						MissionId = {
								--找人
								{9030},	
								--收集
								{ 10075, 10076, 10077, 10078, 10079, 10080, 10081, 10082, 10083, 10084, 10085, 10086, 10087, 10088, 10089, 10090, 10091, 10092, 10093, 10094, 10095, 10096, 10097, 10098, 10099, 10100, 10101, 10102, 10103, 10104, 10105, 10106, 10107 },
						}
					},
					{
						level	=	{ min=60, max=69 },
						rate	=	{ 50, 100 },
						MissionId = {
								--找人
								{9030},	
								--收集
								{ 10205, 10206, 10207, 10208, 10209, 10210, 10211, 10212, 10213, 10214, 10215, 10216, 10217, 10218, 10219, 10220, 10221, 10222, 10223, 10224, 10225, 10226, 10227, 10228 },
						}
					},
					{
						level	=	{ min=70, max=9999 },
						rate	=	{ 50, 100 },
						MissionId = {
								--找人
								{9030},	
								--收集
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

	if newtype == 0 then	--未找到符合玩家等级的任务
		return 0;
	end

	if MissionId < x300670_g_MissionRangeStart or MissionId > x300670_g_MissionRangeEnd then
		MissionId = x300670_g_MissionRangeStart;
	end
	
--	local GMSetId = GetQuestParam(sceneId, selfId, 19, 6)
--	if (GMSetId >= x300670_g_MissionRangeStart and GMSetId <= x300670_g_MissionRangeEnd) then
--		MissionId = GMSetId
--	end

	--MissionId = 10001	--收集
	--MissionId = 9030	--找人
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

	--低于规定最小等级的玩家不能接
	local userlevel = GetLevel(sceneId, selfId);
	if userlevel < x300670_g_LevelLess then
		return 0
	end
        -- 添加“帮会建设任务说明”
	AddQuestTextNM(sceneId, selfId, targetId, x300670_g_MissionCommentId, 13, -1)

	local GuildId = GetGuildID(sceneId, selfId)
	if GuildId < 0 then
		return 0
	end

	local randMissionId = x300670_GetRandMissionId(sceneId, selfId)
	if randMissionId > 0 then
		if IsHaveQuestNM(sceneId, selfId, randMissionId) > 0 then
			return 0;	--已经接到了子任务，不需要再显示空壳任务了
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

	--如果玩家等级过高，显示一个特殊的帮会建设任务选项，点击后会提示玩家去大都接任务
	if (userlevel >= x300670_LevelToCapital and virtualMisId == x300670_g_VirtualMissionId_Low) then
		AddQuestNumText( sceneId, x300670_g_VirtualMissionId_Low, x300670_g_MissionName, 13)
		return 0;
	end
	--如果还没接帮会建设子任务，显示空壳任务的名称
	--允许randMissionId不是0，说明已经随机过子任务，但由于背包满、任务数量满等情况没有成功接到
	if QuestCheckAcceptNM( sceneId, selfId, targetId, virtualMisId ) > 0 then
		x300670_AddMissionTextByState(sceneId, selfId, targetId, virtualMisId);
	end

	return ret;
end

--选中任务
function x300670_ProcEventEntry( sceneId, selfId, targetId, MissionId)

	if MissionId == x300670_g_MissionCommentId then
	-- 显示帮会建设任务说明内容
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

	--如果玩家等级过高，提示玩家去大都接任务
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

	if MissionId == x300670_g_VirtualMissionId_Low or MissionId == x300670_g_VirtualMissionId_High then	--显示空壳任务界面
		BeginQuestEvent( sceneId)
		-- 任务名称
			AddQuestText( sceneId, "#Y"..x300670_g_MissionName)
		--任务描述
			AddQuestText( sceneId, GetQuestDescNM (sceneId, selfId, MissionId))
			AddQuestText( sceneId, " " )
		--任务奖励
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
		--小提示
			AddQuestText( sceneId, "#c00FF00小提示:" )
			AddQuestText( sceneId, "#c00FF00如果想要了解本任务的细节，请点击帮会内政任务说明按钮。" )
		EndQuestEvent()
		ret = DispatchQuestInfoNM( sceneId, selfId, targetId, x300670_g_ScriptId, MissionId)
		return 0;
	else
		local randMissionId = x300670_GetRandMissionId(sceneId, selfId)
		if randMissionId == 0 or IsHaveQuestNM( sceneId, selfId, randMissionId ) == 0 then	-- 如果没这个任务直接退出
			return 0
		end
		--这里显示子任务的界面
		ret = x300670_ShowMissionInfoByState(sceneId, selfId, targetId, randMissionId)
	end
  
	return ret;
end

--完成任务
--返回1代表成功，0代表交任务失败
function x300670_ProcQuestSubmit( sceneId, selfId, targetId, selectId, MissionId )

	MissionId = x300670_GetRandMissionId(sceneId, selfId);
	if MissionId == nil or MissionId <= 0 then
        	return 0
    	end

	if IsHaveQuestNM( sceneId, selfId, MissionId ) == 0 then	-- 如果没这个任务直接退出
		return 0
	 end

	local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )

	--判断是最后环节的提交还是中间环节的提交
	local ret = 0

	local targetGuid = GetMonsterGUID( sceneId, targetId)
	local reply_npcid = GetQuestSubmitNPCGUIDNM(sceneId, selfId, misIndex)
	if targetGuid == reply_npcid then		--在接任务的NPC处提交
		ret = 1
	else
		return 
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
	local exp = x300670_GetExpAward ( sceneId, selfId, curlevel );
	local money,bangg = x300670_GetMoneyAward ( sceneId, selfId, curlevel );

	--处理任务完成
	ret = CircleQuestComplateNM( sceneId, selfId, targetId, MissionId);
	
	if ret == 1 then -- 如果成功完成
		
		local circle, highcircle = x300670_SetRounds(sceneId, selfId)
		x300670_DisplayCircleMessage (sceneId, selfId, MissionId)
		QuestUnCom( sceneId, selfId, x300670_g_VirtualMissionId_Low)
		QuestUnCom( sceneId, selfId, x300670_g_VirtualMissionId_High)
		x300670_SetMD(sceneId, selfId, MD_BANGHUI_RANDMISSIONID, 0)

		x300670_DisplayCompleteMessage(sceneId, selfId, targetId, MissionId);
		--奖励经验
		if exp > 0 then
			AddExp(sceneId, selfId, exp)
		end
		--奖励金钱
		if money > 0 then
			AddMoney(sceneId, selfId, moneytype, money)
		end
		--奖励金钱
		if bangg > 0 then
			AddGuildUserPoint(sceneId, selfId, bangg)
		end
		--显示金钱和经验的奖励
		moneytype = 1
		local honorType = 4
		x300670_DisplayAwardInfo(sceneId, selfId, targetId, -1, -1, moneytype, money, exp, honorType, bangg)
		--09.05.08取消奖励帮会经验
			--每完成一轮奖励帮会经验1点
			--if (circle == x300670_OneRoundCount) then
			--	GetGuildQuestData(sceneId, selfId, GD_GUILD_INDEX_ADDEXP_DATE, x300670_g_ScriptId,MissionId,"OnCallBackGetAddExpDate",0)
				--x300670_GetItemAwardDirectly ( sceneId, selfId, curlevel );
				--AddCountryResource (sceneId, selfId, 2, 2000, 1);
			--end

	else -- 如果未成功完成
		x300670_DisplayCompleteMissionErrorMessage(sceneId, selfId, ret);
		return 0
	end

	return 1;
end
--当取到帮会上次通过本脚本增加经验的日期
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
		-- local str = format("您的帮会增加了%d点经验", x300670_AddGuildExpValue)
		-- Msg2Player(sceneId, selfId, str, 8, 3)
		-- Msg2Player(sceneId, selfId, str, 8, 2)
	else
		GetGuildQuestData(sceneId, selfId, GD_GUILD_INDEX_ADDEXP_VALUE, x300670_g_ScriptId,MissionId,"OnCallBackGetAddExpValue",0)
	end
end

--当取到帮会当天已经通过本脚本增加的经验
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
	-- local str = format("您的帮会增加了%d点经验", x300670_AddGuildExpValue)
	-- Msg2Player(sceneId, selfId, str, 8, 3)
	-- Msg2Player(sceneId, selfId, str, 8, 2)	
end

--经验奖励
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

--金钱奖励
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
----道具直接奖励
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
--				Msg2Player(sceneId, selfId, format("#Y获得%d个物品#R#{_ITEM%d}#Y的奖励", count, item.id[rnum]), 8, 3);
--			end
--			break
--		end
--	end
--	return ret
--end

-- 显示完成信息
function x300670_OnCanCompleteMission ( sceneId, selfId, targetId, MissionId )

	BeginQuestEvent(sceneId);
		--任务名称
		AddQuestText(sceneId, "#Y"..x300670_g_MissionName)
		--最后提交环节的文字
		AddQuestText(sceneId, GetQuestSuccessNM(sceneId, selfId, MissionId))
		--任务奖励
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

--是否还在惩罚时间内，返回0表示仍然在惩罚时间内
function x300670_CheckAbandonPenaltyOff ( sceneId, selfId, targetId )

	local curMinute = GetMinOfDay() + 1	--变成从1开始
	local curDay = GetDayOfYear()		
	
	local lastday =  x300670_GetMD(sceneId, selfId, MD_BANGHUI_LASTDAY)
	local lastMinute =  x300670_GetMD(sceneId, selfId, MD_BANGHUI_ABANDON)

	if (lastMinute == 0) then --没放弃任务
		return 1;
	end

	local bCanAccept = 1
	if (lastday == curDay) then		--放弃任务后，还没到第二天
		if (curMinute >= lastMinute)  and  (curMinute - lastMinute < x300670_g_AbandonTime) then 
			bCanAccept = 0
		end
	elseif (curDay - lastday == 1) or (lastday == 365 and curDay == 0) then	--放弃任务后，到了第二天
		if 1441 - lastMinute + curMinute <= x300670_g_AbandonTime then
			bCanAccept = 0
		end
	end
	--未处理跨非闰年的情况，跨非闰年会忽略惩罚时间

	if (bCanAccept == 0) then
		--不能接受任务
		local str = format("#Y"..x300670_g_MissionName.."#W\n\t你放弃任务不足%d分钟，不能接受任务！" , x300670_g_AbandonTime);
		BeginQuestEvent(sceneId);
			AddQuestText(sceneId, str);
		EndQuestEvent(sceneId);
		DispatchQuestEventList(sceneId, selfId, targetId);
		return 0
	end

	--可以接受任务
	if( lastMinute ~= 0 ) then 
		x300670_SetMD(sceneId, selfId, MD_BANGHUI_ABANDON, 0)
	end

	return 1;
end

--根据任务状态显示任务信息
function x300670_ShowMissionInfoByState( sceneId, selfId, targetId, MissionId )

	if IsHaveQuestNM( sceneId, selfId, MissionId ) == 0 then	-- 如果没有这个任务
		local ret = QuestCheckAcceptNM( sceneId, selfId, targetId, MissionId )
		if ret > 0 then	-- 如果可以接这个任务
			if IsQuestFullNM(sceneId, selfId)==1 then
				Msg2Player(sceneId, selfId, "#Y你已经接了太多的任务", 8, 3)
				Msg2Player(sceneId, selfId, "#Y你已经接了太多的任务", 8, 2)
				return 0
			end
			return x300670_AutoAccept ( sceneId, selfId, targetId, MissionId )
		else
			x300670_DisplayMissionAcceptErrorMessage(sceneId, selfId, ret);
			return 0;
		end
	else --如果有这个任务
		local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )
		local isFinish = GetQuestParam( sceneId, selfId, misIndex, 7)
		if isFinish == 1 then
			x300670_OnCanCompleteMission ( sceneId, selfId, targetId, MissionId )-- 显示完成信息
		else
			x300670_ShowMissionContinueInfo( sceneId, selfId, targetId, MissionId ) -- 显示任务未完成信息
		end
		return 0;
	end
	
	return 0;
end

function x300670_ShowMissionContinueInfo( sceneId, selfId, targetId, MissionId) -- 显示任务未完成信息

	--找人任务，在找人目标npc处
	if x300670_IsDeliver(MissionId) == 1 then --找人任务的中间环节
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
			
			local npcindex = floor (mod(npcdata , j*16) / j)				--计算第i个Npc的序号
			local isNotFind = floor (mod(finddata, j*16) / j)
			if isNotFind == 0 then
				findcount = findcount + 1
			else

				if npcindex < 1 or npcindex > getn(x300670_g_DeliverTargetNPC[i]) then		--没有这个序号，说明数据库存储了错误的数据，必须纠正
					finddata = x300670_ComFindingNPC(i, finddata)				--完成这个NPC
					findcount = findcount + 1
				else										
					local npcid = x300670_g_DeliverTargetNPC[i][npcindex].npcId			--第i个NPC的guid
					if npcid == targetGuid then						--找到了这个NPC
						finddata = x300670_ComFindingNPC(i, finddata)			--完成这个NPC
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

			if finddata == 0 then									--全部完成
				SetQuestByIndex( sceneId, selfId, misIndex, 0, 1)
				SetQuestByIndex( sceneId, selfId, misIndex, 7, 1)
				Msg2Player(sceneId, selfId, "任务已完成，回报帮会任务管理员吧！", 8, 3)
			end

			BeginQuestEvent(sceneId);
				--任务名称
				AddQuestText(sceneId, "#Y"..x300670_g_MissionName)
				--任务成功的文本
				AddQuestText(sceneId, dialog)
			EndQuestEvent();
			DispatchQuestInfoNM( sceneId, selfId, targetId, x300670_g_ScriptId, MissionId, 1)
			--DispatchQuestContinueInfoNM( sceneId, selfId, targetId, x300670_g_ScriptId, MissionId )
			x300670_ProcQuestLogRefresh(sceneId, selfId, MissionId)
			return
		end
	end
	
	QuestNotComplateInfoNM( sceneId, selfId, targetId, MissionId ) -- 显示任务未完成信息
end

--接受空壳任务
function x300670_ProcQuestAccept( sceneId, selfId, targetId, MissionId)

	--如果玩家等级过高，提示玩家去大都接任务
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
		--随机一个子任务
		local missionType
		randMissionId, missionType = x300670_GenerateRandomMission ( sceneId, selfId, targetId );

	end

	if (randMissionId == 0) then
		return 0;
	end

	--显示子任务信息界面
	local ret = x300670_ShowMissionInfoByState(sceneId, selfId, targetId, randMissionId)
	return 1;
end

--自动接受子任务
function x300670_AutoAccept( sceneId, selfId, targetId, MissionId )
	--MissionId必须是有效的子任务
	if IsHaveQuestNM( sceneId, selfId, MissionId ) > 0 then
		return 1
	end
	
	--检查前置任务
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

	
	--接受任务
	local ret
	if x300670_IsDeliver( MissionId ) == 1 then
		ret = AddQuest( sceneId, selfId, MissionId, 300670, 0, 0, 0, 1)
	else
		ret = AddQuestNM( sceneId, selfId, MissionId ) -- 给玩家添加任务
	end
	if ret > 0 then
		x300670_AfterAccept( sceneId, selfId, targetId, MissionId)
	else
		x300670_DisplayAddMissionErrorMessage(sceneId, selfId, ret);
	end
	return ret
end

--执行所有子任务公用的接受后处理
function x300670_AfterAccept( sceneId, selfId, targetId, MissionId)

	local misIndex = GetQuestIndexByID(sceneId, selfId, MissionId);

	--隐藏NPC头顶黄色叹号
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

	--执行其它接受后续处理
	
	--显示任务信息
	BeginQuestEvent( sceneId)
		-- 任务名称
		AddQuestText( sceneId, "#Y"..x300670_g_MissionName)
		--任务描述
		AddQuestText( sceneId, GetQuestDescNM (sceneId, selfId, MissionId))
		AddQuestText( sceneId, " " )
		--任务目标
		AddQuestText( sceneId, "#Y任务目标：" )

		if x300670_IsDeliver(MissionId) == 1 then						--找人任务的目标（最多支持8个）
			local j = 1
			local npcdata = 0
			local finddata = 0
			for i=1, x300670_g_DeliverTargetCount do
				if i > getn(x300670_g_DeliverTargetNPC) then
					break
				end

				local npcindex = random(1, getn(x300670_g_DeliverTargetNPC[i]))		--随机第i个Npc的序号
				npcdata = npcdata + npcindex * j					
				finddata = finddata + 1 * j						--设为1表示未完成
				local npcid = x300670_g_DeliverTargetNPC[i][npcindex].npcId			--第i个NPC的guid
				local str = x300670_DeliverMissionTarget.."@npc_"..npcid
				AddQuestText( sceneId, str )

				j = j * 16
			end

			SetQuestByIndex( sceneId, selfId, misIndex, x300670_MisParam_NPCData, npcdata)
			SetQuestByIndex( sceneId, selfId, misIndex, x300670_MisParam_FindData, finddata)

		elseif x300670_IsCollect(MissionId) == 1 then
			--显示收集任务的目标
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
		AddQuestText( sceneId, " ")	--显示一个空行

	EndQuestEvent()
	       
	DispatchQuestInfoNM( sceneId, selfId, targetId, x300670_g_ScriptId, MissionId, 1)

  --检查现在是否能够提交任务
	local ret = 0
	if x300670_IsDeliver(MissionId) == 1 then 
		ret = 0
	elseif x300670_IsCollect(MissionId) == 1 then
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
		lastCircle = 1;			--环数重置
	else						--环数增加
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
	local str = format("你接受了任务：%s", x300670_g_MissionName);
	Msg2Player(sceneId, selfId, str, 8, 3)
	Msg2Player(sceneId, selfId, str, 8, 2)
	return 1;
end

function x300670_DisplayAddMissionErrorMessage(sceneId, selfId, ret)
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

function x300670_DisplayMissionAcceptErrorMessage(sceneId, selfId, ret)

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
			--显示找人任务的任务状态
			local npcdata = GetQuestParam( sceneId, selfId, misIndex, x300670_MisParam_NPCData)
			local finddata = GetQuestParam( sceneId, selfId, misIndex, x300670_MisParam_FindData)

			local j = 1
			for i=1, x300670_g_DeliverTargetCount do

				if i > getn(x300670_g_DeliverTargetNPC) then
					break
				end

				local npcindex = floor(mod (npcdata , j*16) / j)						--计算第i个Npc的序号
				local isNotFind = floor(mod (finddata , j*16) / j)						--计算这个NPC是否已经被完成
				j = j * 16
				if npcindex < 1 or npcindex > getn(x300670_g_DeliverTargetNPC[i]) then		--没有这个序号，说明数据库存储了错误的数据，不理会
				
				else										
					local npcid = x300670_g_DeliverTargetNPC[i][npcindex].npcId			--第i个NPC的guid
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
			--显示收集任务的任务状态
		end

		AddQuestLogCustomText(sceneId, "", strName, szMissionTarget, strReplyNPC, "", "", "");

		--任务奖励
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

	local str = format( "环数: %d/%d", circles, x300670_OneRoundCount );
	--if highcircle <= x300670_HighBonusCircleCount then
	--	str = str..format("  本日高奖环数：%d/%d", highcircle, x300670_HighBonusCircleCount);
	--end
	Msg2Player(sceneId, selfId, str, 8, 3)

end

function x300670_DisplayCompleteMessage(sceneId, selfId, targetId, MissionId)
	
	local MissionName = x300670_g_MissionName;
	local str = format( "你完成了任务%s", MissionName);

	Msg2Player(sceneId, selfId, str, 8, 3)
	return 1;

end

function x300670_DisplayAwardInfo(sceneId, selfId, targetId, MissionId, selectId, moneyType, money, expAward, honorType, honor)--提示玩家金钱经验声望的奖励信息
	
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


function x300670_DisplayCompleteMissionErrorMessage(sceneId, selfId, ret)
	
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

function x300670_PushAfterMission(sceneId, selfId, targetId, MissionId )
	return 1;
end

--任务放弃--这里需要设置放弃时间MissionData
function x300670_ProcQuestAbandon( sceneId, selfId, MissionId )

	MissionId = x300670_GetRandMissionId(sceneId, selfId);
	if (MissionId == 0 or IsHaveQuestNM( sceneId, selfId, MissionId ) == 0 ) then
		--处理同时接了多个帮会建设子任务的情况,将所有帮会建设任务都删除
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

		--重置随机子任务
		x300670_SetMD(sceneId, selfId, MD_BANGHUI_RANDMISSIONID, 0)
		x300670_SetMD(sceneId, selfId, MD_BANGHUI_CIRCLE, 0)
		x300670_SetMD(sceneId, selfId, MD_BANGHUI_HIGH, x300670_HighBonusCircleCount + 1)
		x300670_DisplayAbandonMessage(sceneId, selfId, MissionId);
	end
	return ret;
end

function x300670_DelAllWrongMission(sceneId, selfId)
	--处理同时接了多个帮会建设子任务的情况,将所有帮会建设任务都删除
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
	local str = format("你放弃了任务%s！", MissionName);

	Msg2Player(sceneId, selfId, str, 8, 3)
	Msg2Player(sceneId, selfId, str, 8, 2)
	return 1;
end

function x300670_ProcQuestAttach( sceneId, selfId, targetId, npcGuid, misIndex, MissionId )
	
	--挖掘、护送子任务不会走这里，会走自己的脚本
	MissionId = x300670_GetRandMissionId(sceneId, selfId);
	if (MissionId == 0) then
		return 0
	end

	if IsHaveQuestNM( sceneId, selfId, MissionId ) == 0 then	-- 如果没有这个任务
		return 0
	end

	local misIndex = GetQuestIndexByID(sceneId, selfId, MissionId);
	--找人任务，点击了找人目标时，如果还没找人，显示帮会建设任务的选项
	if x300670_IsDeliver(MissionId) == 1 then --找人任务特殊处理

		--显示找人任务的任务状态
		local npcdata = GetQuestParam( sceneId, selfId, misIndex, x300670_MisParam_NPCData)
		local finddata = GetQuestParam( sceneId, selfId, misIndex, x300670_MisParam_FindData)
		local j =1
		for i=1, x300670_g_DeliverTargetCount do

			if i > getn(x300670_g_DeliverTargetNPC) then
				break
			end

			local npcindex = floor(mod (npcdata , j*16) / j)					--计算第i个Npc的序号
			local isNotFind = floor (mod (finddata , j*16) / j)					--计算这个NPC是否已经被完成
			j = j * 16
			if npcindex < 1 or npcindex > getn(x300670_g_DeliverTargetNPC[i]) then		--没有这个序号，说明数据库存储了错误的数据，不理会
			
			else										
				local npcid = x300670_g_DeliverTargetNPC[i][npcindex].npcId			--第i个NPC的guid
				if npcid == npcGuid and isNotFind == 1 then				--是否应该把本任务加入选单
					AddQuestNumText( sceneId, MissionId, x300670_g_MissionName, 13)
					return 1
				end
			end
		end
	end

	local submitguid = GetQuestSubmitNPCGUIDNM( sceneId, selfId, misIndex )

	--如果是任务提交人，显示选项
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

--杀怪事件处理
function x300670_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId)
end

--物品改变
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
		if Num < NeedNum then --还没有完成任务
			x300670_SetMP(sceneId, selfId, MissionId, ObjIndex, Num);
			x300670_SetMP(sceneId,selfId,MissionId,7,0)
		elseif Num >= NeedNum then
			if x300670_GetMP(sceneId,selfId,MissionId,7) == 1 then	--之前已经完成了
				return 0
			end
			x300670_SetMP(sceneId, selfId, MissionId, ObjIndex, NeedNum);
			x300670_SetMP(sceneId,selfId,MissionId,7,1)
			Msg2Player(sceneId, selfId, "任务已经完成，快点回去汇报吧！", 8, 3)
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

--区域定时器
function x300670_ProcTiming( sceneId, selfId, ScriptId, MissionId )
	return 1;
end

--打开
function x300670_OnProcOver( sceneId, selfId, targetId )
	return 1
end

--打开后检查
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
		local str = "背包已满，无法得到物品！";
		Msg2Player(sceneId, selfId, str, 8, 3);
		Msg2Player(sceneId, selfId, str, 8, 2)
	end
	return ret
end

--检查日期有没有变化，并重置高奖次数，并保存新的日期
function x300670_CheckDayChanged(sceneId, selfId)
	local lastDay = x300670_GetMD(sceneId, selfId, MD_BANGHUI_LASTDAY)
	local today = GetDayOfYear()
	if lastDay ~= today then	--日期变化
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