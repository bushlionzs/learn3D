

--MisDescBegin

x300882_g_ScriptId =  300882 					


x300882_g_MissionKind 				= 	1                       --任务类型
x300882_g_LevelLess					= 	40                      --场景开放等级  <=0 表示不限制





x300882_g_MissionName				= 	"敌国夺旗"
x300882_g_MissionTarget				= 	""
x300882_g_MissionInfo				= 	""
x300882_g_ContinueInfo				= 	""
x300882_g_MissionCompleted			= 	""
x300882_g_MissionHelp				=	""          --任务提示信息

--目标
x300882_g_ExtTarget					=	{ {type=20,n=1,target="敌国夺旗"}}

--奖励

x300882_g_ExpBonus					= 	0;--x300882_AddExpAward               	--奖励：经验
x300882_g_BonusItem					=	{}	--奖励：物品

x300882_g_BonusMoney1               = 	0
x300882_g_BonusMoney2               =   0
x300882_g_BonusMoney3               =   0

x300882_g_BonusChoiceItem           =   {}


--MisDescEnd


x300882_g_CountryDunhuang = 351 --四个国家的场景id
x300882_g_CountryLoulan = 51
x300882_g_CountryKunlun = 251
x300882_g_CountryLaiyin = 151

x300882_g_MissionId1 = 7689
x300882_g_MissionId2 = 7686
x300882_g_MissionId3 = 7688
x300882_g_MissionId4 = 7687


x300882_g_DayCountLimited			= 1


x300882_g_MissionBonusInfo			= 	"#Y获得经验#R%d#Y的奖励。"

function x300882_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	
end

--选中任务
function x300882_ProcEventEntry( sceneId, selfId, targetId, MissionId, index )

	if index ~= -1 then
		MissionId = index
	end

	if IsHaveQuestNM( sceneId, selfId, MissionId ) == 0 then	-- 如果没有这个任务
		local ret = QuestCheckAcceptNM( sceneId, selfId, targetId, MissionId )
		if ret > 0 then	-- 如果可以接这个任务
			--AddDispatchQuestInfoNM( sceneId, selfId, targetId, MissionId ) -- 显示接受任务信息
			x300882_DispatchMissionInfo( sceneId, selfId, targetId, MissionId )
		elseif ret ==-1 then  --等级不够
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
	else --如果有这个任务
		local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )
		if x300882_IsSuccessed( sceneId, selfId, MissionId )>0 then
			--QuestComplateInfoNM( sceneId, selfId, targetId, MissionId ) -- 显示完成信息
			x300882_DispatchCompletedInfo( sceneId, selfId, targetId,MissionId )
		else
			--QuestNotComplateInfoNM( sceneId, selfId, targetId, MissionId ) -- 显示任务未完成信息
			x300882_DispatchContinueInfo( sceneId, selfId, targetId,MissionId )
		end
	end
end


--接受任务
function x300882_ProcQuestAccept( sceneId, selfId, targetId, MissionId )
	if	IsHaveQuestNM( sceneId, selfId, x300882_g_MissionId1 ) > 0 or IsHaveQuestNM( sceneId, selfId, x300882_g_MissionId2 ) > 0 or IsHaveQuestNM( sceneId, selfId, x300882_g_MissionId3 ) > 0 or IsHaveQuestNM( sceneId, selfId, x300882_g_MissionId4 ) > 0 then
			BeginQuestEvent(sceneId)
			local strText = "您已经接过了【国家】敌国夺旗任务，还未完成，不能再接取"
			AddQuestText( sceneId, strText )
			EndQuestEvent( sceneId )
			DispatchQuestTips( sceneId, selfId )
			Msg2Player(sceneId,selfId,"您已经接过了【国家】敌国夺旗任务，还未完成，不能再接取",8,2)
			return
	end

	if IsHaveQuestNM( sceneId, selfId, MissionId ) > 0 then	-- 如果有这个任务直接退出
		return 0
	end
	
	local nDayCount =0;

	if MissionId == x300882_g_MissionId1 then
		nDayCount = x300882_GetDayCount(sceneId, selfId, DQ_DUOQI_DUNHUANG_DATE,DQ_DUOQI_DUNHUANG_DAYCOUNT)
	elseif MissionId == x300882_g_MissionId2 then
		nDayCount = x300882_GetDayCount(sceneId, selfId, DQ_DUOQI_LOULAN_DATE,DQ_DUOQI_LOULAN_DAYCOUNT)
	elseif MissionId == x300882_g_MissionId3 then
		nDayCount = x300882_GetDayCount(sceneId, selfId, DQ_DUOQI_KUNLUN_DATE,DQ_DUOQI_KUNLUN_DAYCOUNT)
	elseif MissionId == x300882_g_MissionId4 then
		nDayCount = x300882_GetDayCount(sceneId, selfId, DQ_DUOQI_LAIYIN_DATE,DQ_DUOQI_LAIYIN_DAYCOUNT)
	else
		return -1;
	end

	if nDayCount>=x300882_g_DayCountLimited then
		BeginQuestEvent(sceneId);
			AddQuestText(sceneId, "当日次数超过1次，请明日来接");
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
		return 0;
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
		ret = AddQuestNM( sceneId, selfId, MissionId ) -- 给玩家添加任务
		if ret > 0 then
			BeginQuestEvent(sceneId);
				AddQuestText(sceneId, "您接受了任务:【国家】敌国夺旗");
			EndQuestEvent();
			DispatchQuestTips(sceneId, selfId);
			Msg2Player(sceneId,selfId,"您接受了任务:【国家】敌国夺旗",8,2)
			GamePlayScriptLog(sceneId, selfId, 141)
			return 1
		elseif ret == 0 then
			local strText = "添加任务失败"
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, strText);
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
		elseif ret == -1 then
			local strText = "背包已满,请整理后再来接任务"
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, strText);
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
		elseif ret == -2 then
			local strText = "任务已满，添加任务失败"
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, strText);
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
		end
	elseif ret ==-1 then  --等级不够
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

--完成任务
--返回1代表成功，0代表交任务失败
function x300882_ProcQuestSubmit( sceneId, selfId, targetId, selectId, MissionId )
	
	if IsHaveQuestNM( sceneId, selfId, MissionId ) == 0 then	-- 如果没这个任务直接退出
		return 0
	end

	local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )
	local ret = x300882_IsSuccessed( sceneId, selfId, MissionId ); --QuestCheckSubmitNM( sceneId, selfId, targetId, MissionId, misIndex ) -- 获取完成任务检查信息
	if ret > 0 then -- 如果可以完成
		
		return x300882_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	end
	return 0
end

--任务完成
function x300882_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
		--提示玩家任务完成
		if MissionId == x300882_g_MissionId1 then
			x300882_SetDayCount(sceneId, selfId, DQ_DUOQI_DUNHUANG_DATE,DQ_DUOQI_DUNHUANG_DAYCOUNT)
		elseif MissionId == x300882_g_MissionId2 then
			x300882_SetDayCount(sceneId, selfId, DQ_DUOQI_LOULAN_DATE,DQ_DUOQI_LOULAN_DAYCOUNT)
		elseif MissionId == x300882_g_MissionId3 then
			x300882_SetDayCount(sceneId, selfId, DQ_DUOQI_KUNLUN_DATE,DQ_DUOQI_KUNLUN_DAYCOUNT)
		elseif MissionId == x300882_g_MissionId4 then
			x300882_SetDayCount(sceneId, selfId, DQ_DUOQI_LAIYIN_DATE,DQ_DUOQI_LAIYIN_DAYCOUNT)
		else
			return -1;
		end

		BeginQuestEvent(sceneId);
			AddQuestText(sceneId, "您完成了任务:【国家】敌国夺旗");
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
		Msg2Player(sceneId,selfId,"您完成了任务:【国家】敌国夺旗",8,2)
		
		
		x300882_GiveReward(sceneId,selfId)
		DelQuestNM( sceneId, selfId, MissionId )
		GamePlayScriptLog(sceneId, selfId, 142)
 
		CancelSpecificImpact(sceneId, selfId, 7702);
	
		--国家实力加1分
		AddCountryStrength(sceneId, selfId, 1)	
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, "恭喜，您为国家实力榜贡献了#R1个#O积分。");
		EndQuestEvent(sceneId);
		DispatchQuestTips(sceneId,selfId);
		Msg2Player(sceneId,selfId,"恭喜，您为国家实力榜贡献了#R1个#O积分。",8,2)		
		
		if CountryIsFortuneTime(sceneId, selfId, 1) > 0 then
			local country = GetCurCountry(sceneId, selfId)
			SetCountryQuestData(sceneId, country, CD_INDEX_CHUGUO_COUNT, 1, 1 )
			
			-- local selfGuildId = GetGuildID(sceneId, selfId)
			-- local countryGuildId = GetCountryKingGuildId(sceneId, selfId)
			
			-- if selfGuildId ~= -1 and countryGuildId == selfGuildId then
				--功勋加1分
				AddExploit(sceneId, selfId, 1)
				BeginQuestEvent(sceneId);
				AddQuestText(sceneId, "#o获得#R功勋1点#o的奖励");
				EndQuestEvent(sceneId);
				DispatchQuestTips(sceneId,selfId);
				Msg2Player(sceneId,selfId,"#o获得#R功勋1点#o的奖励",8,2)			
			-- end	
			
			--记日志
			local strMsg = format("CGL:<Info>x300882_MissionComplate sceneId=%d,country=%d", sceneId, country )
    		WriteLog( 1, strMsg )
		end
		
	return 0
end

function x300882_GiveReward(sceneId,selfId)
	local level = GetLevel(sceneId, selfId)
	local nExpBonus1 = 100*3*level*5;
	local nExpBonus2 = level*2200;
	local nExpBonus = 0;
	if GetLevel(sceneId, selfId) >=40 and GetLevel(sceneId, selfId) < 70 then
		nExpBonus = nExpBonus1;
	elseif GetLevel(sceneId, selfId) >=70 then
		nExpBonus = nExpBonus2;
	end
    if nExpBonus > 0 then
		AddExp(sceneId, selfId, nExpBonus);
		AddHonor(sceneId, selfId, 100);
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, "#o获得#R经验"..nExpBonus.."点#o的奖励");
		EndQuestEvent();		
		DispatchQuestTips(sceneId, selfId);
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, "#o获得#R荣誉100点#o的奖励");
		EndQuestEvent();		
		DispatchQuestTips(sceneId, selfId);
  		Msg2Player(sceneId,selfId,"#o获得#R经验"..nExpBonus.."点#o的奖励#r#o获得#R荣誉100点#o的奖励",4,2)
  		CallScriptFunction( 256271, "Finishduoqi", sceneId, selfId)
		local ret = CountryIsFortuneTime(sceneId,selfId,1)
		if ret == 1 then
			AddExp(sceneId, selfId, nExpBonus);
			--AddHonor(sceneId, selfId,100);
			BeginQuestEvent(sceneId);
			AddQuestText(sceneId, "#o出国令额外获得#R经验"..nExpBonus.."点#o的奖励");
			EndQuestEvent();		
			DispatchQuestTips(sceneId, selfId);
			--BeginQuestEvent(sceneId);
			--AddQuestText(sceneId, "#o额外获得#R荣誉100点#o的奖励");
			--EndQuestEvent();		
			--DispatchQuestTips(sceneId, selfId);
			Msg2Player(sceneId,selfId,"#o出国令额外获得#R经验"..nExpBonus.."点#o的奖励",4,2)
			--CallScriptFunction( 256271, "Finishduoqi", sceneId, selfId)
			
			--据点额外奖励
			local nCountry = GetCurCountry(sceneId,selfId)
			local nLairdCount,nLairdSumLevel =  CallScriptFunction(888888,"GetCountryLairdSceneInfo",sceneId,nCountry)
			if nLairdCount > 0 then
			
				local nLairdExpBonus = floor((nLairdSumLevel*0.02)*nExpBonus)
				local nLairdHornorBonus = floor((nLairdSumLevel*0.02)*100)
				
				
				AddExp(sceneId, selfId, nLairdExpBonus);
				AddHonor(sceneId, selfId, nLairdHornorBonus);
				BeginQuestEvent(sceneId);
				AddQuestText(sceneId, "#o本国领地加成获得#R经验"..nLairdExpBonus.."点#o的奖励");
				EndQuestEvent();
				DispatchQuestTips(sceneId, selfId);
				BeginQuestEvent(sceneId);
				AddQuestText(sceneId, "#o本国领地加成获得#R荣誉"..nLairdHornorBonus.."点#o的奖励");
				EndQuestEvent();
				DispatchQuestTips(sceneId, selfId);
		  		Msg2Player(sceneId,selfId,"#o本国领地加成获得#R经验"..nLairdExpBonus.."点#o的奖励#r#o本国领地加成获得#R荣誉"..nLairdHornorBonus.."点#o的奖励",4,2)
				
			end
		end
	end


end


function x300882_ProcQuestAttach( sceneId, selfId, npcId, npcGuid,misIndex, MissionId )
	if IsHaveQuestNM( sceneId, selfId, MissionId) == 0 then	-- 如果没有这个任务
		return
	end
		
	--local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId)
	--local submitGuid = GetQuestSubmitNPCGUIDNM( sceneId, selfId, misIndex )
	--if npcGuid == submitGuid then	--点击的NPC的名字和任务中NPC的名字相同，场景也判断过了
		--local missionState = GetQuestStateNM(sceneId, selfId, npcId, MissionId)
		--AddQuestTextNM( sceneId, selfId, -1, MissionId, missionState, -1 ) -- 显示任务信息
	--end
end

 

--********************************************************************
--放弃
--********************************************************************
function x300882_ProcQuestAbandon( sceneId, selfId,MissionId )
	if IsHaveQuestNM( sceneId, selfId, MissionId ) <= 0 then
		return -1;
	end

	if MissionId == x300882_g_MissionId1 then
		x300882_SetDayCount(sceneId, selfId, DQ_DUOQI_DUNHUANG_DATE,DQ_DUOQI_DUNHUANG_DAYCOUNT)
	elseif MissionId == x300882_g_MissionId2 then
		x300882_SetDayCount(sceneId, selfId, DQ_DUOQI_LOULAN_DATE,DQ_DUOQI_LOULAN_DAYCOUNT)
	elseif MissionId == x300882_g_MissionId3 then
		x300882_SetDayCount(sceneId, selfId, DQ_DUOQI_KUNLUN_DATE,DQ_DUOQI_KUNLUN_DAYCOUNT)
	elseif MissionId == x300882_g_MissionId4 then
		x300882_SetDayCount(sceneId, selfId, DQ_DUOQI_LAIYIN_DATE,DQ_DUOQI_LAIYIN_DAYCOUNT)
	else
		return -1;
	end

	local ret = 0
	ret = DelQuestNM( sceneId, selfId, MissionId )
	if ret == 1 then
		CancelSpecificImpact(sceneId, selfId, 7702);
		BeginQuestEvent(sceneId);
			AddQuestText(sceneId, "您放弃了任务:【国家】敌国夺旗");
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
		Msg2Player(sceneId,selfId,"您放弃了任务:【国家】敌国夺旗",8,2)
	end
end

--杀死怪物
function x300882_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
	

end

function x300882_IsSuccessed( sceneId, selfId, MissionId )
	if IsHaveQuestNM( sceneId, selfId, MissionId ) > 0 then
		
		local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )
		local iRet = GetQuestParam(sceneId, selfId, misIndex, 0);
		----PrintStr(iRet)
		if iRet>0 then
			if IsHaveSpecificImpact( sceneId, selfId, 7702 ) > 0 then
				return 1;
			end
		end
	end

	return 0
end


--物品改变
function x300882_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
	return 0
end

function x300882_CountryCheck( sceneId, selfId, MissionId )
	if MissionId == x300882_g_MissionId1 then
		if sceneId == x300882_g_CountryDunhuang then
			return 1
		end
	elseif MissionId == x300882_g_MissionId2 then
		if sceneId == x300882_g_CountryLoulan then
			return 1
		end
	elseif MissionId == x300882_g_MissionId3 then
		if sceneId == x300882_g_CountryKunlun then
			return 1
		end
	elseif MissionId == x300882_g_MissionId4 then
		if sceneId == x300882_g_CountryLaiyin then
			return 1
		end
	end
	
	return -1
end


function x300882_OnLogInOrDie( sceneId, selfId )
	local MissionId = x300882_g_MissionId1
	if IsHaveQuestNM( sceneId, selfId,MissionId  ) > 0 then	-- 如果有这个任务
		if IsHaveSpecificImpact( sceneId, selfId, 7702 ) > 0 then
			local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )
			SetQuestByIndex( sceneId, selfId, misIndex, 0, 0 )
			SetQuestByIndex( sceneId, selfId, misIndex, 7, 2 )
			CancelSpecificImpact(sceneId, selfId, 7702);
			x300882_ProcQuestLogRefresh( sceneId,selfId,MissionId)
			BeginQuestEvent(sceneId);AddQuestText(sceneId,"您的敌国夺旗任务已失败，请重新领旗");EndQuestEvent(sceneId);DispatchQuestTips(sceneId,selfId);
			Msg2Player(sceneId,selfId,"您的敌国夺旗任务已失败，请重新领旗",8,2)
			SetQuestParam( sceneId,selfId,MissionId,7,0)
		end
	end
	
	local MissionId = x300882_g_MissionId2
	if IsHaveQuestNM( sceneId, selfId,MissionId  ) > 0 then	-- 如果有这个任务
		if IsHaveSpecificImpact( sceneId, selfId, 7702 ) > 0 then
			local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )
			SetQuestByIndex( sceneId, selfId, misIndex, 0, 0 )
			SetQuestByIndex( sceneId, selfId, misIndex, 7, 2 )
			CancelSpecificImpact(sceneId, selfId, 7702);
			x300882_ProcQuestLogRefresh( sceneId,selfId,MissionId)
			BeginQuestEvent(sceneId);AddQuestText(sceneId,"您的敌国夺旗任务已失败，请重新领旗");EndQuestEvent(sceneId);DispatchQuestTips(sceneId,selfId);
			Msg2Player(sceneId,selfId,"您的敌国夺旗任务已失败，请重新领旗",8,2)
			SetQuestParam( sceneId,selfId,MissionId,7,0)
		end
	end
	
	local MissionId = x300882_g_MissionId3
	if IsHaveQuestNM( sceneId, selfId,MissionId  ) > 0 then	-- 如果有这个任务
		if IsHaveSpecificImpact( sceneId, selfId, 7702 ) > 0 then
			local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )
			SetQuestByIndex( sceneId, selfId, misIndex, 0, 0 )
			SetQuestByIndex( sceneId, selfId, misIndex, 7, 2 )
			CancelSpecificImpact(sceneId, selfId, 7702);
			x300882_ProcQuestLogRefresh( sceneId,selfId,MissionId)
			BeginQuestEvent(sceneId);AddQuestText(sceneId,"您的敌国夺旗任务已失败，请重新领旗");EndQuestEvent(sceneId);DispatchQuestTips(sceneId,selfId);
			Msg2Player(sceneId,selfId,"您的敌国夺旗任务已失败，请重新领旗",8,2)
			SetQuestParam( sceneId,selfId,MissionId,7,0)
		end
	end
	
	local MissionId = x300882_g_MissionId4
	if IsHaveQuestNM( sceneId, selfId,MissionId  ) > 0 then	-- 如果有这个任务
		if IsHaveSpecificImpact( sceneId, selfId, 7702 ) > 0 then
			local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )
			SetQuestByIndex( sceneId, selfId, misIndex, 0, 0 )
			SetQuestByIndex( sceneId, selfId, misIndex, 7, 2 )
			CancelSpecificImpact(sceneId, selfId, 7702);
			x300882_ProcQuestLogRefresh( sceneId,selfId,MissionId)
			BeginQuestEvent(sceneId);AddQuestText(sceneId,"您的敌国夺旗任务已失败，请重新领旗");EndQuestEvent(sceneId);DispatchQuestTips(sceneId,selfId);
			Msg2Player(sceneId,selfId,"您的敌国夺旗任务已失败，请重新领旗",8,2)
			SetQuestParam( sceneId,selfId,MissionId,7,0)
		end
	end
  
end

function x300882_ProcQuestLogRefresh( sceneId,selfId,MissionId)
	--local misIndex = GetQuestIndexByID( sceneId, selfId, missionId )	
	--local instData1 = GetQuestParam( sceneId, selfId, misIndex, 0 )
	--local instDataStr1 = format("(%d/1)", instData1 )

	--local str_npc = "#G本国金盾大元帅"
	--local str_target = "#G敌国夺旗#W"..instDataStr1
	
	local nRet = x300882_IsSuccessed( sceneId, selfId, MissionId )
	local str = "";

	if MissionId == x300882_g_MissionId1 then
		if nRet>0 then
			str = "  从@npc_30015到敦煌边塞夺取@npc_30031（1/1）"
		else
			str = "  从@npc_30015到敦煌边塞夺取@npc_30031（0/1）"
		end
	elseif MissionId == x300882_g_MissionId2 then
		if nRet>0 then
			str = "  从@npc_30012到楼兰边塞夺取@npc_30028（1/1）"
		else
			str = "  从@npc_30012到楼兰边塞夺取@npc_30028（0/1）"
		end
	elseif MissionId == x300882_g_MissionId3 then
		if nRet>0 then
			str = "  从@npc_30014到昆仑边塞夺取@npc_30030（1/1）"
		else
			str = "  从@npc_30014到昆仑边塞夺取@npc_30030（0/1）"
		end
	elseif MissionId == x300882_g_MissionId4 then
		if nRet>0 then
			str = "  从@npc_30013到天山边塞夺取@npc_30029（1/1）"
		else
			str = "  从@npc_30013到天山边塞夺取@npc_30029（0/1）"
		end
	else
		return -1;
	end


	BeginQuestEvent(sceneId)	
		local level = GetLevel(sceneId, selfId)
		local ExpBonus1 = 100*5*3 * level
		local ExpBonus2 = 2200 * level
		local ExpBonus = 0
		if GetLevel(sceneId, selfId) >=40 and GetLevel(sceneId, selfId) < 70 then
			ExpBonus = ExpBonus1;
		elseif GetLevel(sceneId, selfId) >=70 then
			ExpBonus = ExpBonus2;
		end
	    if ExpBonus > 0 then
			AddQuestExpBonus(sceneId,  ExpBonus);
			AddQuestMoneyBonus6(sceneId, 100 )
		end		
		
	AddQuestLogCustomText( sceneId,
							"",						-- 标题
							"【国家】敌国夺旗",        -- 任务名字
							str,		--任务目标
							"@npc_134502",			--任务NPC
							"通过@npc_134511潜入敌国，到边塞（126，123）附近夺取军旗。",               --任务攻略
							"兵者，攻心为上。若想要打击敌人的士气，最好的办法莫过于夺取他们的军旗！",	--任务描述
							"当您在出国令期间回复任务时，你将获得双倍的奖励！当任务失败时，您可以重新去敌国边塞掌旗使处获得战旗！"					--任务小提示
							)
	EndQuestEvent()
	DispatchQuestLogUpdate(sceneId, selfId, MissionId);

end


---------------------------------------------------------------------------------------------------
--最后一次做这个任务是哪天
---------------------------------------------------------------------------------------------------
function x300882_GetLastDay(sceneId, selfId, nMDIndex, nOffset, nSize)
	local lastday = GetQuestData(sceneId, selfId, nMDIndex, nOffset, nSize)
	return lastday
end

---------------------------------------------------------------------------------------------------
--最后一天做这个任务做了几次
---------------------------------------------------------------------------------------------------
function x300882_GetLastDayCount(sceneId, selfId, nMDIndex, nOffset, nSize)
	local daycount =  GetQuestData(sceneId, selfId, nMDIndex, nOffset, nSize)
	return daycount
end

---------------------------------------------------------------------------------------------------
--今天这个任务做了几次
---------------------------------------------------------------------------------------------------
function x300882_GetDayCount(sceneId, selfId, nMDDayIndex, nMDCountIndex)
	local today = GetDayOfYear()
	local lastday = x300882_GetLastDay(sceneId, selfId, nMDDayIndex[1], nMDDayIndex[2], nMDDayIndex[3])

	--不是同一天
	if today ~= lastday then
		return 0
	end

	local daycount = x300882_GetLastDayCount(sceneId, selfId, nMDCountIndex[1], nMDCountIndex[2], nMDCountIndex[3])
	return daycount
end

---------------------------------------------------------------------------------------------------
--设置最后一天做这个任务是哪天
---------------------------------------------------------------------------------------------------
function x300882_SetLastDay(sceneId, selfId, nMDIndex, nOffset, nSize, day)
	SetQuestData(sceneId, selfId, nMDIndex, nOffset, nSize, day)
end

---------------------------------------------------------------------------------------------------
--设置做任务的次数
---------------------------------------------------------------------------------------------------
function x300882_SetLastDayCount(sceneId, selfId, nMDIndex, nOffset, nSize, count)
	SetQuestData(sceneId, selfId, nMDIndex, nOffset, nSize, count)
end

---------------------------------------------------------------------------------------------------
--设置今天做了多少次
---------------------------------------------------------------------------------------------------
function x300882_SetDayCount(sceneId, selfId, nMDDayIndex, nMDCountIndex)
	local today = GetDayOfYear()
	local lastday = x300882_GetLastDay(sceneId, selfId, nMDDayIndex[1], nMDDayIndex[2], nMDDayIndex[3])

	--上次完成的日期不是今天
	if today ~= lastday then
		x300882_SetLastDay(sceneId, selfId, nMDDayIndex[1], nMDDayIndex[2], nMDDayIndex[3], today)
		x300882_SetLastDayCount(sceneId, selfId, nMDCountIndex[1], nMDCountIndex[2], nMDCountIndex[3], 1)
		return
	end

	--上次完成的日期是今天
	local daycount = x300882_GetLastDayCount(sceneId, selfId, nMDDayIndex[1], nMDDayIndex[2], nMDDayIndex[3]) + 1
	x300882_SetLastDayCount(sceneId, selfId, nMDCountIndex[1], nMDCountIndex[2], nMDCountIndex[3], daycount)

end


function x300882_DispatchMissionInfo( sceneId, selfId, NPCId, MissionId)

	BeginQuestEvent(sceneId)
	local localexp1 = (GetLevel( sceneId, selfId )) * 100*5*3
	local localexp2 = (GetLevel( sceneId, selfId )) * 2200
	local localexp = 0
	if GetLevel(sceneId, selfId) >=40 and GetLevel(sceneId, selfId) < 70 then
		localexp = localexp1;
	elseif GetLevel(sceneId, selfId) >=70 then
		localexp = localexp2;
	end
		if MissionId == x300882_g_MissionId1 then
			AddQuestText(sceneId,"#Y【国家】敦煌夺旗")
			--任务信息
			
			AddQuestText(sceneId,"   敦煌边塞的边塞掌旗使，负责掌管象征着敦煌大军的军旗，如果你夺取了敦煌军旗并凯旋而归，不但能强烈动摇敦煌的军心，也能大大鼓舞我军的士气！")
			AddQuestText(sceneId," ")

			--任务目标
			AddQuestText( sceneId,"#Y任务目标：")
			AddQuestText( sceneId,"  在本国边塞找到@npc_134511，传送到敦煌边塞，到边塞掌旗使处夺取敌国军旗。")
			AddQuestText( sceneId," ")

			AddQuestText(sceneId,"#Y任务奖励：")
			AddQuestText(sceneId,"  经验值："..localexp.."点#r  荣誉值：100点")
			AddQuestText(sceneId," ")
			
		elseif MissionId == x300882_g_MissionId2 then
			AddQuestText(sceneId,"#Y【国家】楼兰夺旗")
			--任务信息
			
			AddQuestText(sceneId,"   楼兰边塞的边塞掌旗使，负责掌管象征着楼兰大军的军旗，如果你夺取了楼兰军旗并凯旋而归，不但能强烈动摇楼兰的军心，也能大大鼓舞我军的士气！")
			AddQuestText(sceneId," ")

			--任务目标
			AddQuestText( sceneId,"#Y任务目标：")
			AddQuestText( sceneId,"  在本国边塞找到@npc_134511，传送到楼兰边塞，到边塞掌旗使处夺取敌国军旗。")
			AddQuestText( sceneId," ")

			AddQuestText(sceneId,"#Y任务奖励：")
			AddQuestText(sceneId,"  经验值："..localexp.."点#r  荣誉值：100点")
			AddQuestText(sceneId," ")
			
		elseif MissionId == x300882_g_MissionId3 then
			AddQuestText(sceneId,"#Y【国家】昆仑夺旗")
			--任务信息
			
			AddQuestText(sceneId,"   昆仑边塞的边塞掌旗使，负责掌管象征着昆仑大军的军旗，如果你夺取了昆仑军旗并凯旋而归，不但能强烈动摇昆仑的军心，也能大大鼓舞我军的士气！")
			AddQuestText(sceneId," ")

			--任务目标
			AddQuestText( sceneId,"#Y任务目标：")
			AddQuestText( sceneId,"  在本国边塞找到@npc_134511，传送到昆仑边塞，到边塞掌旗使处夺取敌国军旗。")
			AddQuestText( sceneId," ")

			AddQuestText(sceneId,"#Y任务奖励：")
			AddQuestText(sceneId,"  经验值："..localexp.."点#r  荣誉值：100点")
			AddQuestText(sceneId," ")
			
		elseif MissionId == x300882_g_MissionId4 then
			AddQuestText(sceneId,"#Y【国家】天山夺旗")
			--任务信息
			
			AddQuestText(sceneId,"   天山边塞的边塞掌旗使，负责掌管象征着天山大军的军旗，如果你夺取了天山军旗并凯旋而归，不但能强烈动摇天山的军心，也能大大鼓舞我军的士气！")
			AddQuestText(sceneId," ")

			--任务目标
			AddQuestText( sceneId,"#Y任务目标：")
			AddQuestText( sceneId,"  在本国边塞找到@npc_134511，传送到天山边塞，到边塞掌旗使处夺取敌国军旗。")
			AddQuestText( sceneId," ")

			AddQuestText(sceneId,"#Y任务奖励：")
			AddQuestText(sceneId,"  经验值："..localexp.."点#r  荣誉值：100点")
			AddQuestText(sceneId," ")
			
		else
			return -1;
		end
		
	EndQuestEvent()
	DispatchQuestInfoNM(sceneId, selfId, NPCId, x300882_g_ScriptId, MissionId,0);
end

--向客户端发送任务完成信息
---------------------------------------------------------------------------------------------------
function x300882_DispatchCompletedInfo( sceneId, selfId, NPCId,MissionId )
	

	BeginQuestEvent(sceneId)
	local localexp1 = (GetLevel( sceneId, selfId )) * 100*5*3
	local localexp2 = (GetLevel( sceneId, selfId )) * 2200
	local localexp = 0
	if GetLevel(sceneId, selfId) >=40 and GetLevel(sceneId, selfId) < 70 then
		localexp = localexp1;
	elseif GetLevel(sceneId, selfId) >=70 then
		localexp = localexp2;
	end
		if MissionId == x300882_g_MissionId1 then
			AddQuestText(sceneId,"#Y【国家】敦煌夺旗")
			AddQuestText(sceneId,"   很好！我们夺来的军旗又多了一面。")
			AddQuestText(sceneId," ")

			AddQuestText(sceneId,"#Y任务奖励：")
			AddQuestText(sceneId,"  经验值："..localexp.."点#r  荣誉值：100点")
			AddQuestText(sceneId," ")
			
		elseif MissionId == x300882_g_MissionId2 then
			AddQuestText(sceneId,"#Y【国家】楼兰夺旗")
			AddQuestText(sceneId,"   很好！我们夺来的军旗又多了一面。")
			AddQuestText(sceneId," ")

			AddQuestText(sceneId,"#Y任务奖励：")
			AddQuestText(sceneId,"  经验值："..localexp.."点#r  荣誉值：100点")
			
		elseif MissionId == x300882_g_MissionId3 then
			AddQuestText(sceneId,"#Y【国家】昆仑夺旗")
			AddQuestText(sceneId,"   很好！我们夺来的军旗又多了一面。")
			AddQuestText(sceneId," ")

			AddQuestText(sceneId,"#Y任务奖励：")
			AddQuestText(sceneId,"  经验值："..localexp.."点#r  荣誉值：100点")
			
		elseif MissionId == x300882_g_MissionId4 then
			AddQuestText(sceneId,"#Y【国家】天山夺旗")
			AddQuestText(sceneId,"   很好！我们夺来的军旗又多了一面。")
			AddQuestText(sceneId," ")

			AddQuestText(sceneId,"#Y任务奖励：")
			AddQuestText(sceneId,"  经验值："..localexp.."点#r  荣誉值：100点")
			
		else
			return -1;
		end	
	EndQuestEvent()
	DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x300882_g_ScriptId, MissionId);

end

--向客户端发送任务未完成
---------------------------------------------------------------------------------------------------
function x300882_DispatchContinueInfo( sceneId, selfId, NPCId,MissionId )

	BeginQuestEvent(sceneId)
	local localexp1 = (GetLevel( sceneId, selfId )) * 100*5*3
	local localexp2 = (GetLevel( sceneId, selfId )) * 2200
	local localexp = 0
	if GetLevel(sceneId, selfId) >=40 and GetLevel(sceneId, selfId) < 70 then
		localexp = localexp1;
	elseif GetLevel(sceneId, selfId) >=70 then
		localexp = localexp2;
	end
		if MissionId == x300882_g_MissionId1 then
			AddQuestText(sceneId,"#Y【国家】敦煌夺旗")
		--任务信息
			
			AddQuestText(sceneId,"   怎么？难道你看到那敦煌军旗下的重重守卫，有所胆怯？")
			AddQuestText(sceneId," ")

			AddQuestText(sceneId,"#Y任务奖励：")
			AddQuestText(sceneId,"  经验值："..localexp.."点#r  荣誉值：100点")
			AddQuestText(sceneId," ")
			
		elseif MissionId == x300882_g_MissionId2 then
			AddQuestText(sceneId,"#Y【国家】楼兰夺旗")
		--任务信息
			
			AddQuestText(sceneId,"   怎么？难道你看到那楼兰军旗下的重重守卫，有所胆怯？")
			AddQuestText(sceneId," ")

			AddQuestText(sceneId,"#Y任务奖励：")
			AddQuestText(sceneId,"  经验值："..localexp.."点#r  荣誉值：100点")
			AddQuestText(sceneId," ")
			
		elseif MissionId == x300882_g_MissionId3 then
			AddQuestText(sceneId,"#Y【国家】昆仑夺旗")
		--任务信息
			
			AddQuestText(sceneId,"   怎么？难道你看到那昆仑军旗下的重重守卫，有所胆怯？")
			AddQuestText(sceneId," ")

			AddQuestText(sceneId,"#Y任务奖励：")
			AddQuestText(sceneId,"  经验值："..localexp.."点#r  荣誉值：100点")
			AddQuestText(sceneId," ")
			
		elseif MissionId == x300882_g_MissionId4 then
			AddQuestText(sceneId,"#Y【国家】天山夺旗")
		--任务信息
			
			AddQuestText(sceneId,"   怎么？难道你看到那天山军旗下的重重守卫，有所胆怯？")
			AddQuestText(sceneId," ")

			AddQuestText(sceneId,"#Y任务奖励：")
			AddQuestText(sceneId,"  经验值："..localexp.."点#r  荣誉值：100点")
			AddQuestText(sceneId," ")
			
		else
			return -1;
		end	
	EndQuestEvent()
	DispatchQuestDemandInfo(sceneId, selfId, NPCId, x300882_g_ScriptId, MissionId,0);
	
end