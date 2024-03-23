--敌国抢粮脚本
--MisDescBegin

x300733_g_ScriptId 					= 	300733                  --脚本ID


x300733_g_MissionKind 				= 	1                       --任务类型
x300733_g_LevelLess					= 	40                      --场景开放等级  <=0 表示不限制





x300733_g_MissionName				= 	"敌国情报"
x300733_g_MissionTarget				= 	""
x300733_g_MissionInfo				= 	""
x300733_g_ContinueInfo				= 	""
x300733_g_MissionCompleted			= 	""
x300733_g_MissionHelp				=	""          --任务提示信息

--目标
x300733_g_ExtTarget					=	{ {type=20,n=10,target="获得情报"}}

--奖励

x300733_g_ExpBonus					= 	0;--x300733_AddExpAward               	--奖励：经验
x300733_g_BonusItem					=	{}	--奖励：物品

x300733_g_BonusMoney1               = 	0
x300733_g_BonusMoney2               =   0
x300733_g_BonusMoney3               =   0

x300733_g_BonusChoiceItem           =   {}


--MisDescEnd

x300733_g_LevelNeeded = 65

x300733_g_DayCountLimited	=  1

x300733_g_MissionId1 = 7580  
x300733_g_MissionId2 = 7562
x300733_g_MissionId3 = 7574
x300733_g_MissionId4 = 7568
x300733_g_CountryDunhuang =  351--四个国家的场景id
x300733_g_CountryLouLan =  51
x300733_g_CountryKunlun = 251
x300733_g_CountryLaiYin = 151

x300733_g_NeedItemID = 13011006
x300733_g_NeedItemCount = 1

x300733_g_MissionBonusInfo  = 	"#Y获得经验#R%d#Y的奖励。"
              
function x300733_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	
end


function x300733_CheckSubmit( sceneId, selfId, MissionId )
	if IsHaveQuestNM( sceneId, selfId, MissionId) == 0 then
		return 0;
	end

	if MissionId ~= x300733_g_MissionId1 and MissionId ~= x300733_g_MissionId2 and MissionId ~= x300733_g_MissionId3 and MissionId ~= x300733_g_MissionId4 then
		return 0;
	end

	local ItemCnt = GetItemCount( sceneId, selfId, x300733_g_NeedItemID )

	if ItemCnt<x300733_g_NeedItemCount then
		return 0;
	end

	return 1;


end

--选中任务
function x300733_ProcEventEntry( sceneId, selfId, targetId, MissionId, index )
	
	if index ~= -1 then
		MissionId = index
	end

	if IsHaveQuestNM( sceneId, selfId, MissionId ) == 0 then	-- 如果没有这个任务
	
		if	IsHaveQuestNM( sceneId, selfId, x300733_g_MissionId1 ) > 0 or IsHaveQuestNM( sceneId, selfId, x300733_g_MissionId2 ) > 0 or IsHaveQuestNM( sceneId, selfId, x300733_g_MissionId3 ) > 0 or IsHaveQuestNM( sceneId, selfId, x300733_g_MissionId4 ) > 0 then
			--BeginQuestEvent(sceneId)
			--local strText = "您已经接过了【国家】敌国情报任务，还未完成，不能再接取！"
			--AddQuestText( sceneId, strText )
			--EndQuestEvent( sceneId )
			--DispatchQuestTips( sceneId, selfId )
			--Msg2Player(sceneId,selfId,"您已经接过了【国家】敌国情报任务，还未完成，不能再接取！",8,2)
			--return
		end
		--不要给出npc身上没有任务的这个提示！
			local ret = QuestCheckAcceptNM( sceneId, selfId, targetId, MissionId )
			if ret > 0 then	-- 如果可以接这个任务
				--AddDispatchQuestInfoNM( sceneId, selfId, targetId, MissionId ) -- 显示接受任务信息
				x300733_DispatchMissionInfo( sceneId, selfId, targetId, MissionId )
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
	else --如果有这个任务
		local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )
		--if QuestCheckSubmitNM( sceneId, selfId, targetId, MissionId, misIndex ) > 0 then -- 如果任务可以完成
		if x300733_CheckSubmit( sceneId, selfId, MissionId )>0 then
			--QuestComplateInfoNM( sceneId, selfId, targetId, MissionId ) -- 显示完成信息
			x300733_DispatchCompletedInfo( sceneId, selfId, targetId,MissionId )
		else
			--QuestNotComplateInfoNM( sceneId, selfId, targetId, MissionId ) -- 显示任务未完成信息
			x300733_DispatchContinueInfo( sceneId, selfId, targetId,MissionId )
		end
	end
		
end

--接受任务
function x300733_ProcQuestAccept( sceneId, selfId, targetId, MissionId )
	if IsHaveQuestNM( sceneId, selfId, MissionId ) > 0 then	-- 如果有这个任务直接退出
		return 0
	end

	--PrintStr(MissionId)

	if	IsHaveQuestNM( sceneId, selfId, x300733_g_MissionId1 ) > 0 or IsHaveQuestNM( sceneId, selfId, x300733_g_MissionId2 ) > 0 or IsHaveQuestNM( sceneId, selfId, x300733_g_MissionId3 ) > 0 or IsHaveQuestNM( sceneId, selfId, x300733_g_MissionId4 ) > 0 then
			BeginQuestEvent(sceneId)
			local strText = "您已经接过了【国家】敌国情报任务，还未完成，不能再接取！"
			AddQuestText( sceneId, strText )
			EndQuestEvent( sceneId )
			DispatchQuestTips( sceneId, selfId )
			Msg2Player(sceneId,selfId,"您已经接过了【国家】敌国情报任务，还未完成，不能再接取！",8,2)
			return
	end

	local nDayCount =0;

	if MissionId == x300733_g_MissionId1 then
		nDayCount = x300733_GetDayCount(sceneId, selfId, DQ_MIBAO_DUNHUANG_DATE,DQ_MIBAO_DUNHUANG_DAYCOUNT)
	elseif MissionId == x300733_g_MissionId2 then
		nDayCount = x300733_GetDayCount(sceneId, selfId, DQ_MIBAO_LOULAN_DATE,DQ_MIBAO_LOULAN_DAYCOUNT)
	elseif MissionId == x300733_g_MissionId3 then
		nDayCount = x300733_GetDayCount(sceneId, selfId, DQ_MIBAO_KUNLUN_DATE,DQ_MIBAO_KUNLUN_DAYCOUNT)
	elseif MissionId == x300733_g_MissionId4 then
		nDayCount = x300733_GetDayCount(sceneId, selfId, DQ_MIBAO_LAIYIN_DATE,DQ_MIBAO_LAIYIN_DAYCOUNT)
	else
		return -1;
	end

	if nDayCount>=x300733_g_DayCountLimited then
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
			--hf_MissionAfterAccept(sceneId, selfId, MissionId);
			--hf_DisplayAcceptMessage(sceneId, selfId, MissionId);
			BeginQuestEvent(sceneId);
				AddQuestText(sceneId, "您接受了任务:【国家】敌国情报");
			EndQuestEvent();
			DispatchQuestTips(sceneId, selfId);
			Msg2Player(sceneId,selfId,"您接受了任务:【国家】敌国情报",8,2)

			return 1
		else
			--hf_DisplayAddMissionErrorMessage(sceneId, selfId, ret);
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

--完成任务
--返回1代表成功，0代表交任务失败
function x300733_ProcQuestSubmit( sceneId, selfId, targetId, selectId, MissionId )
	
	if IsHaveQuestNM( sceneId, selfId, MissionId ) == 0 then	-- 如果没这个任务直接退出
		return 0
	end

	local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )
	local ret = x300733_CheckSubmit( sceneId, selfId, MissionId ) --QuestCheckSubmitNM( sceneId, selfId, targetId, MissionId, misIndex ) -- 获取完成任务检查信息
	if ret > 0 then -- 如果可以完成
		return x300733_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	end
	return 0
end

--任务完成
function x300733_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
    
    if MissionId == nil or MissionId < 0 then
        return 0
    end
    
    if IsHaveQuestNM( sceneId,selfId,MissionId )<= 0 then
        return 0
    end
    
	local ret = QuestComplateNM( sceneId, selfId, targetId, MissionId, selectId ) -- 获取完成任务信息
	if ret == 1 then -- 如果成功完成
		--提示玩家任务完成


		local ItemCnt = GetItemCount( sceneId, selfId, x300733_g_NeedItemID )
		if ItemCnt > 0 then --奖励
			DelItem(sceneId, selfId,x300733_g_NeedItemID,ItemCnt)	
		else	
		end	
		--提示玩家任务完成

		if MissionId == x300733_g_MissionId1 then
			x300733_SetDayCount(sceneId, selfId, DQ_MIBAO_DUNHUANG_DATE,DQ_MIBAO_DUNHUANG_DAYCOUNT)
		elseif MissionId == x300733_g_MissionId2 then
			x300733_SetDayCount(sceneId, selfId, DQ_MIBAO_LOULAN_DATE,DQ_MIBAO_LOULAN_DAYCOUNT)
		elseif MissionId == x300733_g_MissionId3 then
			x300733_SetDayCount(sceneId, selfId, DQ_MIBAO_KUNLUN_DATE,DQ_MIBAO_KUNLUN_DAYCOUNT)
		elseif MissionId == x300733_g_MissionId4 then
			x300733_SetDayCount(sceneId, selfId, DQ_MIBAO_LAIYIN_DATE,DQ_MIBAO_LAIYIN_DAYCOUNT)
		else
			return -1;
		end

		--hf_DisplayCompleteMessage(sceneId, selfId, MissionId);
		BeginQuestEvent(sceneId);
			AddQuestText(sceneId, "您完成了任务:【国家】敌国情报");
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
		Msg2Player(sceneId,selfId,"您完成了任务:【国家】敌国情报",8,2)
		
		x300733_GiveReward(sceneId,selfId)
		DelQuestNM( sceneId, selfId, MissionId )
	
		--国家实力加1分
		AddCountryStrength(sceneId, selfId, 1)	
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, "恭喜，您为国家实力榜贡献了#R1个#o积分。");
		EndQuestEvent(sceneId);
		DispatchQuestTips(sceneId,selfId);
		Msg2Player(sceneId,selfId,"恭喜，您为国家实力榜贡献了#R1个#o积分。",8,2)		
		
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
		
			local strMsg = format("CGL:<Info>x300733_MissionComplate sceneId=%d,country=%d", sceneId, country )
    		WriteLog( 1, strMsg )
		end
		
		--hf_DisplayAwardInfo(sceneId, selfId, targetId, MissionId, selectId)--提示玩家金钱经验声望的奖励信息
		return 1 -- 返回成功
	else -- 如果未成功完成
		--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(sceneId, selfId, ret);
		BeginQuestEvent(sceneId);
			AddQuestText(sceneId, "完成任务错误");
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
		return 0
	end
	return 0
end


function x300733_GiveReward(sceneId,selfId)

	local level = GetLevel(sceneId, selfId)
	local nExpBonus1 = 100*2.6*level*5;
	local nExpBonus2 = level*1750;
	local nExpBonus = 0;
	if GetLevel(sceneId, selfId) >=40 and GetLevel(sceneId, selfId) < 70 then
		nExpBonus = nExpBonus1;
	elseif GetLevel(sceneId, selfId) >=70 then
		nExpBonus = nExpBonus2;
	end
    if nExpBonus > 0 then
		AddExp(sceneId, selfId, nExpBonus);
		AddHonor(sceneId, selfId, 75);
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, "#o获得#R经验"..nExpBonus.."点#o的奖励");
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, "#o获得#R荣誉75点#o的奖励");
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
  		Msg2Player(sceneId,selfId,"#o获得#R经验"..nExpBonus.."点#o的奖励#r#o获得#R荣誉75点#o的奖励",4,2)
  		CallScriptFunction( 256268, "Finishqingbao", sceneId, selfId)
		local ret = CountryIsFortuneTime(sceneId,selfId,1)
		if ret == 1 then
			AddExp(sceneId, selfId, nExpBonus);
			--AddHonor(sceneId, selfId, 75);
			BeginQuestEvent(sceneId);
			AddQuestText(sceneId, "#o出国令额外获得#R经验"..nExpBonus.."点#o的奖励");
			EndQuestEvent();
			DispatchQuestTips(sceneId, selfId);
			--BeginQuestEvent(sceneId);
			--AddQuestText(sceneId, "#o额外获得#R荣誉75点#o的奖励");
			--EndQuestEvent();
			--DispatchQuestTips(sceneId, selfId);
			Msg2Player(sceneId,selfId,"#o出国令额外获得#R经验"..nExpBonus.."点#o的奖励",4,2)
			--CallScriptFunction( 256268, "Finishqingbao", sceneId, selfId)
			
			--据点额外奖励
			local nCountry = GetCurCountry(sceneId,selfId)
			local nLairdCount,nLairdSumLevel =  CallScriptFunction(888888,"GetCountryLairdSceneInfo",sceneId,nCountry)
			if nLairdCount > 0 then
			
				local nLairdExpBonus = floor((nLairdSumLevel*0.02)*nExpBonus)
				local nLairdHornorBonus = floor((nLairdSumLevel*0.02)*75)
				
				
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

function x300733_ProcQuestAttach( sceneId, selfId, npcId, npcGuid,misIndex, MissionId )

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
function x300733_ProcQuestAbandon( sceneId, selfId,MissionId )
	local ret = 0

	if MissionId == x300733_g_MissionId1 then
		x300733_SetDayCount(sceneId, selfId, DQ_MIBAO_DUNHUANG_DATE,DQ_MIBAO_DUNHUANG_DAYCOUNT)
	elseif MissionId == x300733_g_MissionId2 then
		x300733_SetDayCount(sceneId, selfId, DQ_MIBAO_LOULAN_DATE,DQ_MIBAO_LOULAN_DAYCOUNT)
	elseif MissionId == x300733_g_MissionId3 then
		x300733_SetDayCount(sceneId, selfId, DQ_MIBAO_KUNLUN_DATE,DQ_MIBAO_KUNLUN_DAYCOUNT)
	elseif MissionId == x300733_g_MissionId4 then
		x300733_SetDayCount(sceneId, selfId, DQ_MIBAO_LAIYIN_DATE,DQ_MIBAO_LAIYIN_DAYCOUNT)
	else
		return -1;
	end

	ret = DelQuestNM( sceneId, selfId, MissionId )
	if ret == 1 then
		--hf_DisplayAbandonMessage(sceneId, selfId, MissionId);
		BeginQuestEvent(sceneId);
			AddQuestText(sceneId, "您放弃了任务:【国家】敌国情报");
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
		Msg2Player(sceneId,selfId,"您放弃了任务:【国家】敌国情报",8,2)
	end
end

--杀死怪物
function x300733_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end


--物品改变
function x300733_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )--寻找材料的任务完成后再添加合成任务
    
    if MissionId == nil or MissionId < 0 then
        return 0
    end
    
    if IsHaveQuestNM(sceneId,selfId,MissionId) <= 0 then
        return 0
    end
    
	--CallScriptFunction( 888891, "ProcQuestItemChanged", sceneId, selfId, itemdataId, MissionId )
	local NeedNum, ObjIndex = GetQuestNeedItemNumNM( sceneId, selfId, MissionId, itemdataId )
	local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )

	if NeedNum > 0 then
		local Num = GetItemCount( sceneId, selfId, itemdataId )
		--x888891_DisplayMissionGetItemMessage(sceneId, selfId, itemdataId, Num, NeedNum);
		if Num < NeedNum then --还没有完成任务
 			SetQuestByIndex( sceneId, selfId, misIndex, ObjIndex, Num )         --by zheng
			SetQuestByIndex( sceneId, selfId, misIndex, 7, 0 )
			x300733_ProcQuestLogRefresh( sceneId, selfId, MissionId)
		elseif Num >= NeedNum then
			--已经完成任务
			SetQuestByIndex( sceneId, selfId, misIndex, ObjIndex, NeedNum )         --by zheng
			local MisCareNPC = QuestCareNPCNM( sceneId, selfId, misIndex )
			if MisCareNPC == 0 then --任务自动完成
				local ret = QuestCheckSubmitNM( sceneId, selfId, selfId, MissionId, misIndex ) -- 获取完成任务检查信息
				if ret > 0 then -- 如果可以完成
					x300733_ProcQuestLogRefresh( sceneId, selfId, MissionId)
					return x300733_MissionComplate( sceneId, selfId, selfId, -1, MissionId )
				end
			end

			x300733_ProcQuestLogRefresh( sceneId, selfId, MissionId)
		end
	end

end


function x300733_CountryCheck( sceneId, selfId, MissionId )
	if MissionId == x300733_g_MissionId1 then
		if sceneId == x300733_g_CountryDunhuang then
			return 1
		end
	elseif MissionId == x300733_g_MissionId2 then
		if sceneId == x300733_g_CountryLouLan then
			return 1
		end
	elseif MissionId == x300733_g_MissionId3 then
		if sceneId == x300733_g_CountryKunlun then
			return 1
		end
	elseif MissionId == x300733_g_MissionId4 then
		if sceneId == x300733_g_CountryLaiYin then
			return 1
		end
	end

	return -1
	
end

function x300733_OnLogInOrDie( sceneId, selfId )
	
   x300733_OnMissionFailed( sceneId, selfId )
end



function x300733_OnMissionFailed( sceneId, selfId )
	
	x300733_DiGuoQiangLiangOnDie(sceneId, selfId)

end

function x300733_DiGuoQiangLiangOnDie( sceneId, selfId )
	if 0==0 then
		return
	end

	local MissionId = x300733_g_MissionId1
	local itemId = x300733_g_NeedItemID;
	if IsHaveQuestNM( sceneId, selfId,MissionId  ) > 0 then	-- 如果有这个任务
		
		local ItemCnt = GetItemCount( sceneId, selfId, itemId )
		if ItemCnt > 0 then 
			--DelItem(sceneId, selfId,itemId,1)
		else
			local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )
			SetQuestByIndex( sceneId, selfId, misIndex, 0, 0 )
		end
		return
	end
	MissionId = x300733_g_MissionId2
	if IsHaveQuestNM( sceneId, selfId,MissionId  ) > 0 then	-- 如果有这个任务
		
		local ItemCnt = GetItemCount( sceneId, selfId, itemId )
		if ItemCnt > 0 then 
			--DelItem(sceneId, selfId,itemId,1)
		else
			local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )
			SetQuestByIndex( sceneId, selfId, misIndex, 0, 0 )
		end
		return
	end
	MissionId = x300733_g_MissionId3
	if IsHaveQuestNM( sceneId, selfId,MissionId  ) > 0 then	-- 如果有这个任务
		
		local ItemCnt = GetItemCount( sceneId, selfId, itemId )
		if ItemCnt > 0 then 
			--DelItem(sceneId, selfId,itemId,1)
		else
			local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )
			SetQuestByIndex( sceneId, selfId, misIndex, 0, 0 )
		end
		return
	end
	MissionId = x300733_g_MissionId4
	if IsHaveQuestNM( sceneId, selfId,MissionId  ) > 0 then	-- 如果有这个任务
		
		local ItemCnt = GetItemCount( sceneId, selfId, itemId )
		if ItemCnt > 0 then 
			--DelItem(sceneId, selfId,itemId,1)
		else
			local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )
			SetQuestByIndex( sceneId, selfId, misIndex, 0, 0 )
		end
		return
	end
end


---------------------------------------------------------------------------------------------------
--取得当前次数
---------------------------------------------------------------------------------------------------
function x300733_GetDayCount(sceneId, selfId, nDayIndex, nDayCountIndex)



	local today = GetDayOfYear()
	local lastday = GetQuestData(sceneId, selfId, nDayIndex[1], nDayIndex[2],nDayIndex[3] );
	
	if lastday ~= today then
		return 0
	end

	local daycount = GetQuestData(sceneId, selfId, nDayCountIndex[1], nDayCountIndex[2],nDayCountIndex[3] );
	return daycount;

	

end

---------------------------------------------------------------------------------------------------
--设置当天次数
---------------------------------------------------------------------------------------------------
function x300733_SetDayCount(sceneId, selfId, nDayIndex, nDayCountIndex)

	local today = GetDayOfYear()

	local lastday = GetQuestData(sceneId, selfId, nDayIndex[1], nDayIndex[2], nDayIndex[3])

	if lastday ~= today then
		SetQuestData(sceneId, selfId, nDayIndex[1], nDayIndex[2], nDayIndex[3], today)
		SetQuestData(sceneId, selfId, nDayCountIndex[1], nDayCountIndex[2], nDayCountIndex[3], 1)
	else
		local daycount = GetQuestData(sceneId, selfId, nDayCountIndex[1], nDayCountIndex[2], nDayCountIndex[3])
		SetQuestData(sceneId, selfId, nDayCountIndex[1], nDayCountIndex[2], nDayCountIndex[3], daycount+1)
	end
	
	
	
end


---------------------------------------------------------------------------------------------------
--检查任务接受结果
---------------------------------------------------------------------------------------------------
function x300733_ProcAcceptCheck(sceneId, selfId, NPCId)
	return 1
end

---------------------------------------------------------------------------------------------------
--向客户端发送任务信息
---------------------------------------------------------------------------------------------------
function x300733_DispatchMissionInfo( sceneId, selfId, NPCId, MissionId)

	BeginQuestEvent(sceneId)
	local localexp1 = (GetLevel( sceneId, selfId )) * 100*2.6*5
	local localexp2 = (GetLevel( sceneId, selfId )) * 1750
	local localexp = 0
	if GetLevel(sceneId, selfId) >=40 and GetLevel(sceneId, selfId) < 70 then
		localexp = localexp1;
	elseif GetLevel(sceneId, selfId) >=70 then
		localexp = localexp2;
	end
		if MissionId == x300733_g_MissionId1 then
			AddQuestText(sceneId,"#Y【国家】敦煌情报")
			--任务信息
			
			AddQuestText(sceneId,"   我们的一位暗探，不幸在敦煌被人识破了身份，情急之下，他将最重要的情报藏在了敦煌暗道。\n\t这份情报中有着敌国重要军力的调动情况，你这就前往敦煌暗道，将情报秘密的取回来，当然，你要小心行事，我不想再派出另一位勇士去重复同样的使命。")
			AddQuestText(sceneId," ")

			--任务目标
			AddQuestText( sceneId,"#Y任务目标：")
			AddQuestText( sceneId,"  在本国边塞找到@npc_125509，传送到敦煌边塞，到敦煌暗道获取密报。")
			AddQuestText( sceneId," ")

			AddQuestText(sceneId,"#Y任务奖励：")
			AddQuestText(sceneId,"  经验值："..localexp.."点#r  荣誉值：75点")
			AddQuestText(sceneId," ")

		elseif MissionId == x300733_g_MissionId2 then
			AddQuestText(sceneId,"#Y【国家】楼兰情报")
			--任务信息
			
			AddQuestText(sceneId,"   我们的一位暗探，不幸在楼兰被人识破了身份，情急之下，他将最重要的情报藏在了楼兰暗道。\n\t这份情报中有着敌国重要军力的调动情况，你这就前往楼兰暗道，将情报秘密的取回来，当然，你要小心行事，我不想再派出另一位勇士去重复同样的使命。")
			AddQuestText(sceneId," ")

			--任务目标
			AddQuestText( sceneId,"#Y任务目标：")
			AddQuestText( sceneId,"  在本国边塞找到@npc_125509，传送到楼兰边塞，到楼兰暗道获取密报。")
			AddQuestText( sceneId," ")

			AddQuestText(sceneId,"#Y任务奖励：")
			AddQuestText(sceneId,"  经验值："..localexp.."点#r  荣誉值：75点")
			AddQuestText(sceneId," ")
			
		elseif MissionId == x300733_g_MissionId3 then
			AddQuestText(sceneId,"#Y【国家】昆仑情报")
			--任务信息
			
			AddQuestText(sceneId,"   我们的一位暗探，不幸在昆仑被人识破了身份，情急之下，他将最重要的情报藏在了昆仑暗道。\n\t这份情报中有着敌国重要军力的调动情况，你这就前往昆仑暗道，将情报秘密的取回来，当然，你要小心行事，我不想再派出另一位勇士去重复同样的使命。")
			AddQuestText(sceneId," ")

			--任务目标
			AddQuestText( sceneId,"#Y任务目标：")
			AddQuestText( sceneId,"  在本国边塞找到@npc_125509，传送到昆仑边塞，到昆仑暗道获取密报。")
			AddQuestText( sceneId," ")

			AddQuestText(sceneId,"#Y任务奖励：")
			AddQuestText(sceneId,"  经验值："..localexp.."点#r  荣誉值：75点")
			AddQuestText(sceneId," ")
			
		elseif MissionId == x300733_g_MissionId4 then
			AddQuestText(sceneId,"#Y【国家】天山情报")
			--任务信息
			
			AddQuestText(sceneId,"   我们的一位暗探，不幸在天山被人识破了身份，情急之下，他将最重要的情报藏在了天山暗道。\n\t这份情报中有着敌国重要军力的调动情况，你这就前往天山暗道，将情报秘密的取回来，当然，你要小心行事，我不想再派出另一位勇士去重复同样的使命。")
			AddQuestText(sceneId," ")

			--任务目标
			AddQuestText( sceneId,"#Y任务目标：")
			AddQuestText( sceneId,"  在本国边塞找到@npc_125509，传送到天山边塞，到天山暗道获取密报。")
			AddQuestText( sceneId," ")

			AddQuestText(sceneId,"#Y任务奖励：")
			AddQuestText(sceneId,"  经验值："..localexp.."点#r  荣誉值：75点")
			AddQuestText(sceneId," ")
			
		else
			return -1;
		end
		
			
		
		

	EndQuestEvent()
	DispatchQuestInfoNM(sceneId, selfId, NPCId, x300733_g_ScriptId, MissionId,0);
end

---------------------------------------------------------------------------------------------------
--向客户端发送任务未完成
---------------------------------------------------------------------------------------------------
function x300733_DispatchContinueInfo( sceneId, selfId, NPCId,MissionId )

	

	BeginQuestEvent(sceneId)
	local localexp1 = (GetLevel( sceneId, selfId )) * 100*2.6*5
	local localexp2 = (GetLevel( sceneId, selfId )) * 1750
	local localexp = 0
	if GetLevel(sceneId, selfId) >=40 and GetLevel(sceneId, selfId) < 70 then
		localexp = localexp1;
	elseif GetLevel(sceneId, selfId) >=70 then
		localexp = localexp2;
	end
		if MissionId == x300733_g_MissionId1 then
			AddQuestText(sceneId,"#Y【国家】敦煌情报")
		--任务信息
			
			AddQuestText(sceneId,"   时间每过去一分，情报就多一分暴露的危险。")
			AddQuestText(sceneId," ")

			AddQuestText(sceneId,"#Y任务奖励：")
			AddQuestText(sceneId,"  经验值："..localexp.."点#r  荣誉值：75点")
			AddQuestText(sceneId," ")
		elseif MissionId == x300733_g_MissionId2 then
			AddQuestText(sceneId,"#Y【国家】楼兰情报")
		--任务信息
			
			AddQuestText(sceneId,"   时间每过去一分，情报就多一分暴露的危险。")
			AddQuestText(sceneId," ")

			AddQuestText(sceneId,"#Y任务奖励：")
			AddQuestText(sceneId,"  经验值："..localexp.."点#r  荣誉值：75点")
			AddQuestText(sceneId," ")
		elseif MissionId == x300733_g_MissionId3 then
			AddQuestText(sceneId,"#Y【国家】昆仑情报")
		--任务信息
			
			AddQuestText(sceneId,"   时间每过去一分，情报就多一分暴露的危险。")
			AddQuestText(sceneId," ")

			AddQuestText(sceneId,"#Y任务奖励：")
			AddQuestText(sceneId,"  经验值："..localexp.."点#r  荣誉值：75点")
			AddQuestText(sceneId," ")
		elseif MissionId == x300733_g_MissionId4 then
			AddQuestText(sceneId,"#Y【国家】天山情报")
		--任务信息
			
			AddQuestText(sceneId,"   时间每过去一分，情报就多一分暴露的危险。")
			AddQuestText(sceneId," ")

			AddQuestText(sceneId,"#Y任务奖励：")
			AddQuestText(sceneId,"  经验值："..localexp.."点#r  荣誉值：75点")
			AddQuestText(sceneId," ")
		else
			return -1;
		end


	EndQuestEvent()
	DispatchQuestDemandInfo(sceneId, selfId, NPCId, x300733_g_ScriptId, MissionId,0);
	


end

---------------------------------------------------------------------------------------------------
--向客户端发送任务完成信息
---------------------------------------------------------------------------------------------------
function x300733_DispatchCompletedInfo( sceneId, selfId, NPCId,MissionId )
	

	BeginQuestEvent(sceneId)
	local localexp1 = (GetLevel( sceneId, selfId )) * 100*2.6*5	
	local localexp2 = (GetLevel( sceneId, selfId )) * 1750
	local localexp = 0
	if GetLevel(sceneId, selfId) >=40 and GetLevel(sceneId, selfId) < 70 then
		localexp = localexp1;
	elseif GetLevel(sceneId, selfId) >=70 then
		localexp = localexp2;
	end
		if MissionId == x300733_g_MissionId1 then
			--任务信息
			AddQuestText(sceneId,"#Y【国家】敦煌情报")
			AddQuestText(sceneId,"   太好了！有了这份情报，我们就对敦煌边塞的军力部署了如指掌。")
			AddQuestText(sceneId," ")

			AddQuestText(sceneId,"#Y任务奖励：")
			AddQuestText(sceneId,"  经验值："..localexp.."点#r  荣誉值：75点")
			AddQuestText(sceneId," ")
		elseif MissionId == x300733_g_MissionId2 then
			--任务信息
			AddQuestText(sceneId,"#Y【国家】楼兰情报")
			AddQuestText(sceneId,"   太好了！有了这份情报，我们就对楼兰边塞的军力部署了如指掌。")
			AddQuestText(sceneId," ")

			AddQuestText(sceneId,"#Y任务奖励：")
			AddQuestText(sceneId,"  经验值："..localexp.."点#r  荣誉值：75点")
			AddQuestText(sceneId," ")
		elseif MissionId == x300733_g_MissionId3 then
			--任务信息
			AddQuestText(sceneId,"#Y【国家】昆仑情报")
			AddQuestText(sceneId,"   太好了！有了这份情报，我们就对昆仑边塞的军力部署了如指掌。")
			AddQuestText(sceneId," ")

			AddQuestText(sceneId,"#Y任务奖励：")
			AddQuestText(sceneId,"  经验值："..localexp.."点#r  荣誉值：75点")
			AddQuestText(sceneId," ")
		elseif MissionId == x300733_g_MissionId4 then
			--任务信息
			AddQuestText(sceneId,"#Y【国家】天山情报")
			AddQuestText(sceneId,"   太好了！有了这份情报，我们就对天山边塞的军力部署了如指掌。")
			AddQuestText(sceneId," ")

			AddQuestText(sceneId,"#Y任务奖励：")
			AddQuestText(sceneId,"  经验值："..localexp.."点#r  荣誉值：75点")
			AddQuestText(sceneId," ")
		else
			return -1;
		end

		
		
		
	EndQuestEvent()
	DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x300733_g_ScriptId, MissionId);

end


---------------------------------------------------------------------------------------------------
--任务日志刷新
---------------------------------------------------------------------------------------------------
function x300733_QuestLogRefresh( sceneId, selfId, MissionId)

	
	local ret = x300733_CheckSubmit( sceneId, selfId, MissionId )

	
	
	local str = "";

	if MissionId == x300733_g_MissionId1 then
		
		if ret>0 then
			str = "  从@npc_30003到敦煌暗道获取@npc_30027（1/1）"
		else
			str = "  从@npc_30003到敦煌暗道获取@npc_30027（0/1）"
		end
	elseif MissionId == x300733_g_MissionId2 then
		if ret>0 then
			str = "  从@npc_30000到楼兰暗道获取@npc_30024（1/1）"
		else
			str = "  从@npc_30000到楼兰暗道获取@npc_30024（0/1）"
		end
	elseif MissionId == x300733_g_MissionId3 then
		if ret>0 then
			str = "  从@npc_30002到昆仑暗道获取@npc_30026（1/1）"
		else
			str = "  从@npc_30002到昆仑暗道获取@npc_30026（0/1）"
		end
	elseif MissionId == x300733_g_MissionId4 then
		if ret>0 then
			str = "  从@npc_30001到天山暗道获取@npc_30025（1/1）"
		else
			str = "  从@npc_30001到天山暗道获取@npc_30025（0/1）"
		end
	else
		return -1;
	end
		
	BeginQuestEvent(sceneId)	
	local level = GetLevel(sceneId, selfId)
		local ExpBonus1 = 100*2.6*5 * level
		local ExpBonus2 = 1750 * level
		local ExpBonus = 0
		if GetLevel(sceneId, selfId) >=40 and GetLevel(sceneId, selfId) < 70 then
			ExpBonus = ExpBonus1;
		elseif GetLevel(sceneId, selfId) >=70 then
			ExpBonus = ExpBonus2;
		end
	    if ExpBonus > 0 then
			AddQuestExpBonus(sceneId,  ExpBonus);
			AddQuestMoneyBonus6(sceneId, 75 )
		end		
		
	AddQuestLogCustomText( sceneId,
							"",						-- 标题
							"【国家】敌国情报",        -- 任务名字
							str,		--任务目标
							"@npc_125502",			--任务NPC
							"通过@npc_125509潜入敌国，到暗道获取重要敌情并将情报送回本国。\n楼兰暗道情报坐标（156，131）\n天山暗道情报坐标（111，133）\n昆仑暗道情报坐标（152，137）\n敦煌暗道情报坐标（116，134）",               --任务攻略
							"知己知彼，百战不殆。我们的密探常常会送回一些重要的情报。",	--任务描述
							"当您在出国令期间回复任务时，你将获得双倍的奖励！"					--任务小提示
							)
	EndQuestEvent()
	DispatchQuestLogUpdate(sceneId, selfId, MissionId);
		

end

function x300733_ProcQuestLogRefresh( sceneId, selfId, MissionId)
	
	x300733_QuestLogRefresh( sceneId, selfId, MissionId );
end


function x300733_OnGetTargetItem( sceneId, selfId, MissionId)
	
	local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )
	SetQuestByIndex( sceneId, selfId, misIndex, 7, 1 )
	x300733_QuestLogRefresh( sceneId, selfId, MissionId)
end