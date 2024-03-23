-------------------------
--Const
-------------------------

--MisDescBegin

x300738_g_ScriptId 					= 	300738                  --脚本ID


x300738_g_MissionKind 				= 	1                       --任务类型
x300738_g_LevelLess					= 	40                      --场景开放等级  <=0 表示不限制

x300738_g_MissionName				= 	""                --任务名称
x300738_g_MissionTarget				= 	""          --任务目标
x300738_g_MissionInfo				= 	""            --任务信息
x300738_g_ContinueInfo				= 	""  --任务继续信息
x300738_g_MissionCompleted			= 	""  --任务完成信息
x300738_g_MissionHelp				=	""          --任务提示信息

--目标
x300738_g_ExtTarget					=	{}


--奖励
x300738_g_ExpBonus		 			= 	0                    	--奖励：经验
x300738_g_BonusItem					=	{}	--奖励：物品

x300738_g_BonusMoney1               = 	0       --任务奖励绑定银币
x300738_g_BonusMoney2               =   0       --任务奖励非绑定银币
x300738_g_BonusMoney3               =   0       --任务奖励绑定金币
x300738_g_BonusMoney4               =   0     --任务奖励朝廷声望
x300738_g_BonusMoney5               =   0     --任务奖励江湖声望
x300738_g_BonusMoney6               =   0     --任务奖励荣誉



x300738_g_BonusChoiceItem           =   {}


--MisDescEnd


x300738_g_DayCountLimited = 1

x300738_g_MissionBonusInfo			= 	"#Y获得经验#R%d#Y的奖励。"


x300738_g_Shoubian = {7563, 7569,7575,7584}
x300738_g_SendMail1 = {7564, 7570,7576,7585}
x300738_g_SendMail2 = {7565, 7571,7577,7586}

x300738_g_ShouBianCountryScene	= {51,151,251,351};

function x300738_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	----PrintStr("xcvxcsfsdf")
end

--选中任务
function x300738_ProcEventEntry( sceneId, selfId, targetId, MissionId, index )
	--PrintStr("x300738_ProcEventEntry")

	if index ~= -1 then
		MissionId = index
	end

	--PrintNum(MissionId)

	if IsHaveQuestNM( sceneId, selfId, MissionId ) == 0 then	-- 如果没有这个任务
		local missionId1 = 7564
		local missionId2 = 7570
		local missionId3 = 7576
		local missionId4 = 7585

		--local commitMissionId1 = 7565
		--local commitMissionId2 = 7571
		--local commitMissionId3 = 7577
		--local commitMissionId4 = 7586

		--local shoubian1 = 7584
		--local shoubian2 = 7563
		--local shoubian3 = 7575
		--local shoubian4 = 7569

		
		if IsHaveQuestNM( sceneId, selfId, missionId1 ) > 0 or IsHaveQuestNM( sceneId, selfId, missionId2 ) > 0 or IsHaveQuestNM( sceneId, selfId, missionId3 ) > 0 or IsHaveQuestNM( sceneId, selfId, missionId4 ) > 0 then			BeginQuestEvent(sceneId)
			local strText = "您已经接过了【国家】国家守边任务，还未完成，不能再接取"
			AddQuestText( sceneId, strText )
			EndQuestEvent( sceneId )
			DispatchQuestTips( sceneId, selfId )
			Msg2Player(sceneId,selfId,"您已经接过了【国家】国家守边任务，还未完成，不能再接取",8,2)
			return
		end

		local nCurrentDayCount = x300738_GetDayCount(sceneId, selfId)
		--PrintNum(nCurrentDayCount)
		if nCurrentDayCount>=x300738_g_DayCountLimited then
			--BeginQuestEvent(sceneId)
			--local strText = format("超过当日次数限制（当前次数%d），不能再接受任务！", nCurrentDayCount)

			--AddQuestText( sceneId, strText )
			--EndQuestEvent( sceneId )
			--DispatchQuestTips( sceneId, selfId )
			--return
		end

		--不要给出npc身上没有任务的这个提示！
		local ret = QuestCheckAcceptNM( sceneId, selfId, targetId, MissionId )
		if ret > 0 then	-- 如果可以接这个任务
			--AddDispatchQuestInfoNM( sceneId, selfId, targetId, MissionId ) -- 显示接受任务信息
			x300738_DispatchMissionInfo( sceneId, selfId, targetId, MissionId )
		elseif ret ==-1 then  --等级不够
			--hf_DisplayMissionAcceptErrorMessage(sceneId, selfId, ret);
			BeginQuestEvent(sceneId);
				AddQuestText(sceneId, "你等级过低，不能接收任务");
			EndQuestEvent();
			DispatchQuestTips(sceneId, selfId);
		elseif ret ==-2 then
			BeginQuestEvent(sceneId);
				AddQuestText(sceneId, "超过最大等级限制");
			EndQuestEvent();
			DispatchQuestTips(sceneId, selfId);

		end
	else --如果有这个任务( 点击阿鲁太子)
		local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )
		if QuestCheckSubmitNM( sceneId, selfId, targetId, MissionId, misIndex ) > 0 then -- 如果任务可以完成
			--QuestComplateInfoNM( sceneId, selfId, targetId, MissionId ) -- 显示完成信息
			x300738_DispatchCompletedInfo( sceneId, selfId, targetId,MissionId )
		else
			--QuestNotComplateInfoNM( sceneId, selfId, targetId, MissionId ) -- 显示任务未完成信息
			x300738_DispatchContinueInfo( sceneId, selfId, targetId,MissionId )
		end
	end
				
end

--接受任务
function x300738_ProcQuestAccept( sceneId, selfId, targetId, MissionId )
	----PrintStr("sdfsdf")
	if IsHaveQuestNM( sceneId, selfId, MissionId) >0 then
		return 0;
	end

	local nCurrentDayCount = x300738_GetDayCount(sceneId, selfId)

	if nCurrentDayCount>=x300738_g_DayCountLimited then
		BeginQuestEvent(sceneId);
			AddQuestText(sceneId, "很抱歉，您已经接取过了【国家】国家守边任务，请明日来接");
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
		Msg2Player(sceneId,selfId,"很抱歉，您已经接取过了【国家】国家守边任务，请明日来接",8,2)
		return 0;
	end



	local ret = QuestCheckAcceptNM( sceneId, selfId, targetId, MissionId )
	
	--------------------------- add for Mission full check --------------
		local bFullMission = IsQuestFullNM(sceneId,selfId)
		
		if bFullMission>0 then
			BeginQuestEvent(sceneId);
				AddQuestText(sceneId, "任务已满，无法接受任务");
			EndQuestEvent();
			DispatchQuestTips(sceneId, selfId);
			return 0;
		end
		---------------------------- add end -------------------------------
	
	if ret > 0 then	-- 如果可以接
	elseif ret ==-1 then  --等级不够
		--hf_DisplayMissionAcceptErrorMessage(sceneId, selfId, ret);
		BeginQuestEvent(sceneId);
			AddQuestText(sceneId, "你等级过低，不能接收任务");
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
		return 0;
	elseif ret ==-2 then
		BeginQuestEvent(sceneId);
			AddQuestText(sceneId, "超过最大等级限制");
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);

		return 0;

	end

	--CallScriptFunction(888891, "ProcQuestAccept", sceneId, selfId, targetId, MissionId)  --// 接受国家守边送信一 

	if IsHaveQuestNM( sceneId, selfId, MissionId ) > 0 then	-- 如果有这个任务直接退出
		return 0
	end
	
	--检查前置任务
	local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId, MissionId )
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

	local ret = QuestCheckAcceptNM( sceneId, selfId, targetId, MissionId ) -- 获取接受任务检查信息
	if ret > 0 then -- 如果可以接这个任务
	
		--------------------------- add for Mission full check --------------
		local bFullMission = IsQuestFullNM(sceneId,selfId)
		
		if bFullMission>0 then
			BeginQuestEvent(sceneId);
				AddQuestText(sceneId, "任务已满，无法接受任务");
			EndQuestEvent();
			DispatchQuestTips(sceneId, selfId);
			return 0;
		end
		---------------------------- add end -------------------------------
	
		ret = AddQuestNM( sceneId, selfId, MissionId ) -- 给玩家添加任务
		if ret > 0 then
			BeginQuestEvent(sceneId);
				AddQuestText(sceneId, "您接受了任务:【国家】国家守边");
			EndQuestEvent();
			DispatchQuestTips(sceneId, selfId);

			Msg2Player(sceneId,selfId,"您接受了任务:【国家】国家守边",8,2)

			local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )
			SetQuestByIndex( sceneId, selfId, misIndex, 7, 1 )
			return 1
		else
			BeginQuestEvent(sceneId);
				AddQuestText(sceneId, "接受任务错误");
			EndQuestEvent();
			DispatchQuestTips(sceneId, selfId);
		end
	elseif ret ==-1 then  --等级不够
		--hf_DisplayMissionAcceptErrorMessage(sceneId, selfId, ret);
		BeginQuestEvent(sceneId);
			AddQuestText(sceneId, "你等级过低，不能接收任务");
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
	elseif ret ==-2 then
		BeginQuestEvent(sceneId);
			AddQuestText(sceneId, "超过最大等级限制");
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);

	end

	return 0
end

function x300738_SceneCheck(sceneId, selfId)


	local country = GetCurCountry(sceneId, selfId)
	if x300738_g_ShouBianCountryScene[country+1] == sceneId then
		return 1
	end
	return -1
end

function x300738_ProcQuestAttach( sceneId, selfId, npcId, npcGuid,misIndex, MissionId )
	
	if  x300738_SceneCheck(sceneId, selfId)<0 then
		return
	end
	
	local missionId1 = 7564
	local missionId2 = 7570
	local missionId3 = 7576
	local missionId4 = 7585

	--PrintStr("sdfsdfcxv")    -- 玩家这时候有任务7564， MissionList这个任务调用300378脚本， 交任务npc为阿鲁太子， 所以点阿鲁太子的时候，会调用这个ProcQuestAttach
	if MissionId ~= missionId1 and MissionId ~= missionId2 and MissionId ~= missionId3 and MissionId ~= missionId4  then
		return
	end


	if IsHaveQuestNM( sceneId, selfId, MissionId ) == 0 then	-- 如果没有这个任务
		return
	end

	local npcName = GetName( sceneId, npcId )
	if npcName == "" then	--NPC名字会是空的么
		return
	end

	local guid = GetQuestSubmitNPCGUIDNM( sceneId, selfId, misIndex )
	local  missionState = GetQuestStateNM(sceneId, selfId, npcId, MissionId)
	
	if guid == npcGuid then	--点击的NPC的名字和任务中NPC的名字相同，场景也判断过了
		AddQuestTextNM( sceneId, selfId, npcId, MissionId, missionState, -1 ) -- 显示任务信息
		
		
	end
	

	
	
	--CallScriptFunction(888891, "ProcQuestAttach", sceneId, selfId, npcId, npcGuid,misIndex, MissionId)
end

--完成任务
--返回1代表成功，0代表交任务失败
function x300738_ProcQuestSubmit( sceneId, selfId, targetId, selectId, MissionId )

	

	if IsHaveQuestNM( sceneId, selfId, MissionId ) == 0 then	-- 如果没这个任务直接退出
		return 0
	end

	
	
	local missionId1 = 7565
	local missionId2 = 7571
	local missionId3 = 7577
	local missionId4 = 7586
	
	if MissionId == missionId1 or MissionId == missionId2 or MissionId == missionId3 or MissionId == missionId4  then  --//如果是国家守边送信任务2
		local ret = x300738_CheckSubmitSongxin2(sceneId, selfId,MissionId )
		if ret<=0 then
			return -1;
		end
		x300738_SetDayCount(sceneId, selfId)
		Msg2Player(sceneId,selfId,"您完成了任务:【国家】国家守边",8,2)
		BeginQuestEvent(sceneId);
			AddQuestText(sceneId, "您完成了任务:【国家】国家守边");
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
		x300738_GiveReward(sceneId,selfId)
		DelQuestNM( sceneId, selfId, MissionId )
		return 1;
	end

	missionId1 = 7564
	missionId2 = 7570
	missionId3 = 7576
	missionId4 = 7585

	--PrintNum(MissionId)
	
	if MissionId == missionId1 or MissionId == missionId2 or MissionId == missionId3 or MissionId == missionId4  then  --//如果是国家守边送信任务2
		
		 --Msg2Player(sceneId,selfId,"守边送信1完成",4,2)

		 
		 --PrintStr("scf")
		 DelQuestNM( sceneId, selfId, MissionId )


		 local country = GetCurCountry(sceneId, selfId);
		 
		 local iMissionID = x300738_g_Shoubian[country+1] ;
			

		 --local ret = AddQuestNM( sceneId, selfId, iMissionID ) ;
		 --if ret <= 0 then
		--	 Msg2Player(sceneId,selfId,"接受守边成功",4,2)
		-- else
		--	Msg2Player(sceneId,selfId,"接受守边失败",4,2)
		-- end

		 CallScriptFunction(300734, "ProcQuestAccept", sceneId, selfId, targetId, iMissionID)
	end
	 

	--CallScriptFunction(888891, "ProcQuestSubmit", sceneId, selfId, targetId, selectId, MissionId )
end

function x300738_CheckSubmitSongxin2(sceneId, selfId,MissionId )
	if IsHaveQuestNM( sceneId, selfId, MissionId ) == 0 then	
		return 0
	end

	return 1;
	
end


function x300738_GiveReward(sceneId,selfId)
	--奖励经验
	local level = GetLevel(sceneId, selfId)
	local nExpBonus = 100*3.6*level*15;
    if nExpBonus > 0 then
		AddExp(sceneId, selfId, nExpBonus);
		AddHonor(sceneId, selfId, 50);
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, "#o获得#R经验"..nExpBonus.."点#o的奖励");
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, "#o获得#R荣誉50点#o的奖励");
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
		local Readme = "#o获得#R经验"..nExpBonus.."点#o的奖励#r#o获得#R荣誉50点#o的奖励"
  		Msg2Player(sceneId,selfId,Readme,4,2)
		local ret = CountryIsFortuneTime(sceneId,selfId,0)
		if ret==1 then
			AddExp(sceneId, selfId, nExpBonus);
			--AddHonor(sceneId, selfId, 50);
			BeginQuestEvent(sceneId);
			AddQuestText(sceneId, "#o国运令额外获得#R经验"..nExpBonus.."点#o的奖励");
			EndQuestEvent();
			DispatchQuestTips(sceneId, selfId);
			--BeginQuestEvent(sceneId);
			--AddQuestText(sceneId, "#o额外获得#R荣誉50点#o的奖励");
			--EndQuestEvent();
			--DispatchQuestTips(sceneId, selfId);
			Msg2Player(sceneId,selfId,"#o国运令额外获得#R经验"..nExpBonus.."点#o的奖励",4,2)--#r#o额外获得#R荣誉50点#o的奖励",4,2)
		end
	end

	
end

--任务放弃
function x300738_ProcQuestAbandon( sceneId, selfId, MissionId )
	--PrintNum(MissionId)
	local missionId1 = 7564
	local missionId2 = 7570
	local missionId3 = 7576
	local missionId4 = 7585
	if IsHaveQuestNM( sceneId, selfId, MissionId ) > 0 then
		DelQuestNM( sceneId, selfId, MissionId )

		local MissionName ="【国家】国家守边"
	
		local str = "你放弃了任务:"..MissionName;
		BeginQuestEvent(sceneId)
		AddQuestText( sceneId, str )
		EndQuestEvent( sceneId )
		DispatchQuestTips( sceneId, selfId )
		Msg2Player( sceneId, selfId, str, 4, 2 )

		x300738_SetDayCount(sceneId, selfId)
		--CallScriptFunction(888891, "ProcQuestAbandon", sceneId, selfId, MissionId)
	end
end

function x300738_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
	CallScriptFunction(MISSION_SCRIPT, "ProcQuestItemChanged", sceneId, selfId, itemdataId, MissionId )
end

---------------------------------------------------------------------------------------------------
--取得当前次数
---------------------------------------------------------------------------------------------------
function x300738_GetDayCount(sceneId, selfId)



	local today = GetDayOfYear()
	local lastday = GetQuestData(sceneId, selfId, DQ_SHOUBIAN_DATE[1], DQ_SHOUBIAN_DATE[2],DQ_SHOUBIAN_DATE[3] );
	
	if lastday ~= today then
		return 0
	end

	local daycount = GetQuestData(sceneId, selfId, DQ_SHOUBIAN_DAYCOUNT[1], DQ_SHOUBIAN_DAYCOUNT[2],DQ_SHOUBIAN_DAYCOUNT[3] );
	return daycount;
	

end

---------------------------------------------------------------------------------------------------
--设置当天次数
---------------------------------------------------------------------------------------------------
function x300738_SetDayCount(sceneId, selfId)

	local today = GetDayOfYear()

	local lastday = GetQuestData(sceneId, selfId, DQ_SHOUBIAN_DATE[1], DQ_SHOUBIAN_DATE[2], DQ_SHOUBIAN_DATE[3])

	if lastday ~= today then
		SetQuestData(sceneId, selfId, DQ_SHOUBIAN_DATE[1], DQ_SHOUBIAN_DATE[2], DQ_SHOUBIAN_DATE[3], today)
		SetQuestData(sceneId, selfId, DQ_SHOUBIAN_DAYCOUNT[1], DQ_SHOUBIAN_DAYCOUNT[2], DQ_SHOUBIAN_DAYCOUNT[3], 1)
	else
		local daycount = GetQuestData(sceneId, selfId, DQ_SHOUBIAN_DAYCOUNT[1], DQ_SHOUBIAN_DAYCOUNT[2], DQ_SHOUBIAN_DAYCOUNT[3])
		SetQuestData(sceneId, selfId, DQ_SHOUBIAN_DAYCOUNT[1], DQ_SHOUBIAN_DAYCOUNT[2], DQ_SHOUBIAN_DAYCOUNT[3], daycount+1)
	end
	
	
	
end


---------------------------------------------------------------------------------------------------
--检查任务接受结果
---------------------------------------------------------------------------------------------------
function x300738_ProcAcceptCheck(sceneId, selfId, NPCId)
	return 1
end

---------------------------------------------------------------------------------------------------
--向客户端发送任务信息
---------------------------------------------------------------------------------------------------
function x300738_DispatchMissionInfo( sceneId, selfId, NPCId, MissionId )

	BeginQuestEvent(sceneId)
		
		AddQuestText(sceneId,"#Y【国家】国家守边")
		AddQuestText( sceneId,"  我国正面临着敌国严重的骚扰和威胁，需要大家共同出力，守卫边塞。你需要到本国边塞的明安处领取国家守边任务，完成后找我回复。你愿意接受此任务？#r")

		AddQuestText(sceneId,"#Y任务目标：")
		AddQuestText(sceneId,"  到本国边塞的明安处领取国家守边任务，成功完成守边后找我回复，完成整个国家守边任务！#r" )
		
		AddQuestText(sceneId,"#Y任务小提示：")
		AddQuestText(sceneId,"  当您在国运令期间回复任务时，你将获得双倍的奖励！")

	EndQuestEvent()
	DispatchQuestInfoNM(sceneId, selfId, NPCId, x300738_g_ScriptId, MissionId);
end

---------------------------------------------------------------------------------------------------
--向客户端发送任务未完成
---------------------------------------------------------------------------------------------------
function x300738_DispatchContinueInfo( sceneId, selfId, NPCId,MissionId )

	BeginQuestEvent(sceneId)

		--任务信息
		AddQuestText(sceneId,"#Y".."国家守边未完成")
		AddQuestText(sceneId,"aaaaaa")
		AddQuestText(sceneId," ")

		--任务目标
		AddQuestText( sceneId,"#Y任务目标：")
		AddQuestText( sceneId,"未完成提示bbbbbbb")
		AddQuestText( sceneId," ")

		AddQuestText(sceneId,"#Y任务提示：")
		AddQuestText(sceneId,"未完成ccccccc" )
		AddQuestText(sceneId," ")
		

	EndQuestEvent()
	DispatchQuestDemandInfo(sceneId, selfId, NPCId, x300738_g_ScriptId, MissionId,0);
	


end

---------------------------------------------------------------------------------------------------
--向客户端发送任务完成信息
---------------------------------------------------------------------------------------------------
function x300738_DispatchCompletedInfo( sceneId, selfId, NPCId,MissionId )
	local bSendMail1 = 0
	for i,item in x300738_g_SendMail1 do
		if item== MissionId then
			bSendMail1 = 1
			break
		end
	end

	BeginQuestEvent(sceneId)
		if bSendMail1 ==1 then
			--任务信息
			AddQuestText(sceneId,"#Y【国家】国家守边#r")

			AddQuestText( sceneId,"  我国正面临敌国严重的骚扰和威胁，需要大家共同出力，守卫边塞。你愿意接受此任务，守卫边塞一段时间吗？#r")

			AddQuestText(sceneId,"#Y任务目标：")
			AddQuestText(sceneId,"  您接受任务后，经过一段时间即可向我汇报军情，并完成任务得到奖励。当您的计时器变成红色时就可准备找我回复了，如错过时间，任务就会失败，请你注意时间。" )
	
			AddQuestText(sceneId,"#Y任务小提示：")
			AddQuestText(sceneId,"  任务期间死亡，离线或超时，任务自动置成失败状态，找明安重新领取。#r")
			
		else
			local localexp = (GetLevel( sceneId, selfId )) * 100*3.6*15
			--任务信息
			AddQuestText(sceneId,"#Y【国家】国家守边#r")
			AddQuestText(sceneId,"  感谢您为国家作出的贡献，你将获得大家的敬仰")
			AddQuestText(sceneId," ")

			AddQuestText(sceneId,"#Y任务奖励：")
			AddQuestText(sceneId,"  经验值："..localexp.."点#r  荣誉值：50点")
			
		end
	EndQuestEvent()
	DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x300738_g_ScriptId, MissionId);

end


---------------------------------------------------------------------------------------------------
--任务日志刷新
---------------------------------------------------------------------------------------------------
function x300738_QuestLogRefresh( sceneId, selfId, MissionId)

	local bSendMail1 = 0
	for i,item in x300738_g_SendMail1 do
		if item== MissionId then
			bSendMail1 = 1
			break
		end
	end
	
		
	BeginQuestEvent(sceneId)
	
		if bSendMail1>0 then
			AddQuestLogCustomText( sceneId,
									"",						-- 标题
									"【国家】国家守边（1/3）",        -- 任务名字
									"  到本国边塞的明安处，他是本国的大将，问问他有什么需要帮忙的！",		--任务目标
									"@npc_129700",			--任务NPC
									"",               --任务攻略
									"  我国正面临着敌国严重的骚扰和威胁，需要大家共同出力，守卫边塞。你先去找本国边塞的明安，看看他有什么要帮忙的！",	--任务描述
									""					--任务小提示
									)
		else
			local level = GetLevel(sceneId, selfId)
			local ExpBonus = 100*3.6*15 * level
			if ExpBonus > 0 then
				AddQuestExpBonus(sceneId,  ExpBonus);
				AddQuestMoneyBonus6(sceneId, 50 )
			end		
			AddQuestLogCustomText( sceneId,
									"",						-- 标题
									"【国家】国家守边（3/3）",        -- 任务名字
									"回报边塞的赫鲁。",		--任务目标
									"@npc_129058",			--任务NPC
									"",               --任务攻略
									"把边塞的情形报告赫鲁。",	--任务描述
									"当您在国运令期间回复任务时，你将获得双倍的奖励！"					--任务小提示
									)
		end
	EndQuestEvent()
	DispatchQuestLogUpdate(sceneId, selfId, MissionId);
		

end

function x300738_ProcQuestLogRefresh( sceneId, selfId, MissionId)
	
	x300738_QuestLogRefresh( sceneId, selfId, MissionId );
end



