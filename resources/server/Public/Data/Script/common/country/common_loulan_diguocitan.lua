
--敌国除奸
 
--MisDescBegin



--MisDescBegin

x300732_g_ScriptId 					= 	300732                  --脚本ID


x300732_g_MissionKind 				= 	1                       --任务类型
x300732_g_LevelLess					= 	40                      --场景开放等级  <=0 表示不限制





x300732_g_MissionName				= 	"敌国除奸"
x300732_g_MissionTarget				= 	""
x300732_g_MissionInfo				= 	""
x300732_g_ContinueInfo				= 	""
x300732_g_MissionCompleted			= 	""
x300732_g_MissionHelp				=	""          --任务提示信息

--目标
x300732_g_ExtTarget					=	{ {type=20,n=1,target="杀死张五常"}}

--奖励

x300732_g_ExpBonus					= 	0;--x300732_AddExpAward               	--奖励：经验
x300732_g_BonusItem					=	{}	--奖励：物品

x300732_g_BonusMoney1               = 	0
x300732_g_BonusMoney2               =   0
x300732_g_BonusMoney3               =   0

x300732_g_BonusChoiceItem           =   {}


--MisDescEnd

x300732_g_CountryDunhuang = 351 --四个国家的场景id
x300732_g_CountryLoulan = 51
x300732_g_CountryKunlun = 251
x300732_g_CountryLaiyin = 151

x300732_g_MissionId1 = 7579		-- 敦煌
x300732_g_MissionId2 = 7561		-- 楼兰
x300732_g_MissionId3 = 7573		-- 昆仑
x300732_g_MissionId4 = 7567		-- 天山

x300732_g_DayCountLimited			= 1


x300732_g_MissionBonusInfo			= 	"#Y获得经验#R%d#Y的奖励。"

function x300732_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	
end

--选中任务
function x300732_ProcEventEntry( sceneId, selfId, targetId, MissionId, index )

	if index ~= -1 then
		MissionId = index
	end

	if IsHaveQuestNM( sceneId, selfId, MissionId ) == 0 then	-- 如果没有这个任务
		
		local ret = QuestCheckAcceptNM( sceneId, selfId, targetId, MissionId )
		if ret > 0 then	-- 如果可以接这个任务
			--AddDispatchQuestInfoNM( sceneId, selfId, targetId, MissionId ) -- 显示接受任务信息
			x300732_DispatchMissionInfo( sceneId, selfId, targetId, MissionId )
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
		--if QuestCheckSubmitNM( sceneId, selfId, targetId, MissionId, misIndex ) > 0 then -- 如果任务可以完成
		if x300732_IsSuccessed( sceneId, selfId, MissionId )>0 then
			--QuestComplateInfoNM( sceneId, selfId, targetId, MissionId ) -- 显示完成信息
			x300732_DispatchCompletedInfo( sceneId, selfId, targetId,MissionId )
		else
			--QuestNotComplateInfoNM( sceneId, selfId, targetId, MissionId ) -- 显示任务未完成信息
			x300732_DispatchContinueInfo( sceneId, selfId, targetId,MissionId )
		end
	end
end


--接受任务
function x300732_ProcQuestAccept( sceneId, selfId, targetId, MissionId )
	if IsHaveQuestNM( sceneId, selfId, MissionId ) > 0 then	-- 如果有这个任务直接退出
		return 0
	end

	if	IsHaveQuestNM( sceneId, selfId, x300732_g_MissionId1 ) > 0 or IsHaveQuestNM( sceneId, selfId, x300732_g_MissionId2 ) > 0 or IsHaveQuestNM( sceneId, selfId, x300732_g_MissionId3 ) > 0 or IsHaveQuestNM( sceneId, selfId, x300732_g_MissionId4 ) > 0 then
		BeginQuestEvent(sceneId)
		local strText = "您已经接过了【国家】敌国除奸任务，还未完成，不能再接取！"
		AddQuestText( sceneId, strText )
		EndQuestEvent( sceneId )
		DispatchQuestTips( sceneId, selfId )
		Msg2Player(sceneId,selfId,"您已经接过了【国家】敌国除奸任务，还未完成，不能再接取！",8,2)
		return
	end

	local nDayCount =0;

	if MissionId == x300732_g_MissionId1 then
		nDayCount = x300732_GetDayCount(sceneId, selfId, DQ_CITAN_DUNHUANG_DATE,DQ_CITAN_DUNHUANG_DAYCOUNT)
	elseif MissionId == x300732_g_MissionId2 then
		nDayCount = x300732_GetDayCount(sceneId, selfId, DQ_CITAN_LOULAN_DATE,DQ_CITAN_LOULAN_DAYCOUNT)
	elseif MissionId == x300732_g_MissionId3 then
		nDayCount = x300732_GetDayCount(sceneId, selfId, DQ_CITAN_KUNLUN_DATE,DQ_CITAN_KUNLUN_DAYCOUNT)
	elseif MissionId == x300732_g_MissionId4 then
		nDayCount = x300732_GetDayCount(sceneId, selfId, DQ_CITAN_LAIYIN_DATE,DQ_CITAN_LAIYIN_DAYCOUNT)
	else
		return -1;
	end

	if nDayCount>=x300732_g_DayCountLimited then
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
			return 0
		end
		---------------------------- add end -------------------------------
		
		ret = AddQuestNM( sceneId, selfId, MissionId ) -- 给玩家添加任务
		
		if ret > 0 then
			BeginQuestEvent(sceneId);
				AddQuestText(sceneId, "您接受了任务:【国家】敌国除奸");
			EndQuestEvent();
			DispatchQuestTips(sceneId, selfId);
			Msg2Player(sceneId,selfId,"您接受了任务:【国家】敌国除奸",8,2)
			return 1
		else
			BeginQuestEvent(sceneId);
				AddQuestText(sceneId, "接受任务错误");
			EndQuestEvent();		
			DispatchQuestTips(sceneId, selfId);
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
function x300732_ProcQuestSubmit( sceneId, selfId, targetId, selectId, MissionId )
	
	if IsHaveQuestNM( sceneId, selfId, MissionId ) == 0 then	-- 如果没这个任务直接退出
		return 0
	end

	local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )
	local ret = x300732_IsSuccessed( sceneId, selfId, MissionId ); --QuestCheckSubmitNM( sceneId, selfId, targetId, MissionId, misIndex ) -- 获取完成任务检查信息
	if ret > 0 then -- 如果可以完成
		
		return x300732_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	end
	return 0
end

--任务完成
function x300732_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
    
    if MissionId == nil or MissionId < 0 then
        return 0
    end

    if IsHaveQuestNM( sceneId,selfId,MissionId )<= 0 then
        return 0
    end

	local ret = QuestComplateNM( sceneId, selfId, targetId, MissionId, selectId ) -- 获取完成任务信息
	if ret == 1 then -- 如果成功完成
		--提示玩家任务完成
		if MissionId == x300732_g_MissionId1 then
			x300732_SetDayCount(sceneId, selfId, DQ_CITAN_DUNHUANG_DATE,DQ_CITAN_DUNHUANG_DAYCOUNT)
		elseif MissionId == x300732_g_MissionId2 then
			x300732_SetDayCount(sceneId, selfId, DQ_CITAN_LOULAN_DATE,DQ_CITAN_LOULAN_DAYCOUNT)
		elseif MissionId == x300732_g_MissionId3 then
			x300732_SetDayCount(sceneId, selfId, DQ_CITAN_KUNLUN_DATE,DQ_CITAN_KUNLUN_DAYCOUNT)
		elseif MissionId == x300732_g_MissionId4 then
			x300732_SetDayCount(sceneId, selfId, DQ_CITAN_LAIYIN_DATE,DQ_CITAN_LAIYIN_DAYCOUNT)
		else
			return -1;
		end

		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, "您完成了任务:【国家】敌国除奸");
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
		Msg2Player(sceneId,selfId,"您完成了任务:【国家】敌国除奸",8,2)

		x300732_GiveReward(sceneId,selfId)
		DelQuestNM( sceneId, selfId, MissionId )

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
			local strMsg = format("CGL:<Info>x300732_MissionComplate sceneId=%d,country=%d", sceneId, country )
    		WriteLog( 1, strMsg )
		end
		
		return 1 -- 返回成功
	else -- 如果未成功完成
		BeginQuestEvent(sceneId);
			AddQuestText(sceneId, "完成任务错误");
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
		return 0
	end
	return 0
end

function x300732_GiveReward(sceneId,selfId)

	local level = GetLevel(sceneId, selfId)
	local nExpBonus1 = 100*5*level*3;
	local nExpBonus2 = level*2200;
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
  		CallScriptFunction( 256268, "Finishchujian", sceneId, selfId)
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
			Msg2Player(sceneId,selfId,"#o出国令额外获得#R经验"..nExpBonus.."点#o的奖励",4,2)--#r#o额外获得#R荣誉75点#o的奖励",4,2)
			--CallScriptFunction( 256268, "Finishchujian", sceneId, selfId)
			
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


function x300732_ProcQuestAttach( sceneId, selfId, npcId, npcGuid,misIndex, MissionId )
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
function x300732_ProcQuestAbandon( sceneId, selfId,MissionId )
	if IsHaveQuestNM( sceneId, selfId, MissionId ) <= 0 then
		return -1;
	end

	if MissionId == x300732_g_MissionId1 then
		x300732_SetDayCount(sceneId, selfId, DQ_CITAN_DUNHUANG_DATE,DQ_CITAN_DUNHUANG_DAYCOUNT)
	elseif MissionId == x300732_g_MissionId2 then
		x300732_SetDayCount(sceneId, selfId, DQ_CITAN_LOULAN_DATE,DQ_CITAN_LOULAN_DAYCOUNT)
	elseif MissionId == x300732_g_MissionId3 then
		x300732_SetDayCount(sceneId, selfId, DQ_CITAN_KUNLUN_DATE,DQ_CITAN_KUNLUN_DAYCOUNT)
	elseif MissionId == x300732_g_MissionId4 then
		x300732_SetDayCount(sceneId, selfId, DQ_CITAN_LAIYIN_DATE,DQ_CITAN_LAIYIN_DAYCOUNT)
	else
		return -1;
	end

	local ret = 0
	ret = DelQuestNM( sceneId, selfId, MissionId )
	if ret == 1 then
		BeginQuestEvent(sceneId);
			AddQuestText(sceneId, "您放弃了任务:【国家】敌国除奸");
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
		Msg2Player(sceneId,selfId,"您放弃了任务:【国家】敌国除奸",8,2)
	end
end

--杀死怪物
function x300732_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
	
	
	if x300732_CountryCheck( sceneId, selfId, MissionId ) < 0 then
		return -1;
	end

	if objdataId ~= 9525 then
		return -1;
	end

	--if x300732_IsSuccessed( sceneId, selfId, MissionId )>0 then
	--	return -1;
	--end

	local x,z = GetWorldPos(sceneId,selfId)
	local KilledNum =  GetNearCountryCount(sceneId, selfId,x,z,20)  

	--local KilledNum = GetMonsterOwnerCount( sceneId, objId )

	----PrintNum(KilledNum)
	----PrintNum(selfId)
	
	for i = 0, KilledNum-1 do
		local humanObjId = GetNearCountryMember(sceneId, selfId,i);--GetMonsterOwnerID( sceneId, objId, i )
		----PrintNum(humanObjId)
		if humanObjId ~= -1 then
			if IsPlayerStateNormal(sceneId, humanObjId) > 0 then
				if GetHp(sceneId, humanObjId) > 0 then
					if IsHaveQuestNM( sceneId, humanObjId, MissionId ) > 0 then	--如果这个人拥有任务
						x300732_OnKillTheNpc( sceneId, humanObjId, MissionId )
					end
				end
			end
		end
	end

	
end

function x300732_IsSuccessed( sceneId, selfId, MissionId )
	if IsHaveQuestNM( sceneId, selfId, MissionId ) > 0 then
		
		local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )
		local iRet = GetQuestParam(sceneId, selfId, misIndex, 0);
		----PrintStr(iRet)
		if iRet>0 then
			return 1;
		end
		return 0;
	else
		return 0;
	end
end

function x300732_OnKillTheNpc(sceneId, selfId, MissionId)
	if IsHaveQuestNM( sceneId, selfId, MissionId ) > 0 then
	--已经完成任务
		if x300732_IsSuccessed( sceneId, selfId, MissionId ) >0 then
			return 0;
		end
		local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )
		BeginQuestEvent(sceneId)
		local strText = "您杀死了张五常：1/1";
		if strText == nil then
			strText = "";
		end
		AddQuestText( sceneId, strText )
		EndQuestEvent( sceneId )
		DispatchQuestTips( sceneId, selfId )
		Msg2Player(sceneId,selfId,"您杀死了张五常。",8,2)
		SetQuestByIndex( sceneId, selfId, misIndex, 0, 1 )
		
		SetQuestByIndex( sceneId, selfId, misIndex, 7, 1 )
		x300732_QuestLogRefresh( sceneId, selfId, MissionId)
	end	

end


--物品改变
function x300732_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
	return 0
end

function x300732_CountryCheck( sceneId, selfId, MissionId )
	if MissionId == x300732_g_MissionId1 then
		if sceneId == x300732_g_CountryDunhuang then
			return 1
		end
	elseif MissionId == x300732_g_MissionId2 then
		if sceneId == x300732_g_CountryLoulan then
			return 1
		end
	elseif MissionId == x300732_g_MissionId3 then
		if sceneId == x300732_g_CountryKunlun then
			return 1
		end
	elseif MissionId == x300732_g_MissionId4 then
		if sceneId == x300732_g_CountryLaiyin then
			return 1
		end
	end
	
	return -1
end


function x300732_OnLogInOrDie( sceneId, selfId )
	
   x300732_OnMissionFailed( sceneId, selfId )
end



function x300732_OnMissionFailed( sceneId, selfId )
	
	x300732_DiGuoCiTanOnDie(sceneId, selfId)


end


function x300732_DiGuoCiTanOnDie(sceneId, selfId)
	
	if 0==0 then
		return
	end

	local MissionId = x300732_g_MissionId1
	if IsHaveQuestNM( sceneId, selfId,MissionId  ) > 0 then	-- 如果有这个任务
		local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )
		
		SetQuestByIndex( sceneId, selfId, misIndex, 0, 0 )
		SetQuestByIndex( sceneId, selfId, misIndex, 7, 2 )
	end
	
	MissionId = x300732_g_MissionId2
	if IsHaveQuestNM( sceneId, selfId,MissionId  ) > 0 then	-- 如果有这个任务
		local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )
		SetQuestByIndex( sceneId, selfId, misIndex, 0, 0 )
		SetQuestByIndex( sceneId, selfId, misIndex, 7, 2 )
	end
	
	MissionId = x300732_g_MissionId3
	if IsHaveQuestNM( sceneId, selfId,MissionId  ) > 0 then	-- 如果有这个任务
		local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )

		SetQuestByIndex( sceneId, selfId, misIndex, 0, 0 )
		SetQuestByIndex( sceneId, selfId, misIndex, 7, 2 )
	end
	
	MissionId = x300732_g_MissionId4
	if IsHaveQuestNM( sceneId, selfId,MissionId  ) > 0 then	-- 如果有这个任务
		local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )
		SetQuestByIndex( sceneId, selfId, misIndex, 0, 0 )
		SetQuestByIndex( sceneId, selfId, misIndex, 7, 2 )
	end
end




---------------------------------------------------------------------------------------------------
--取得当前次数
---------------------------------------------------------------------------------------------------
function x300732_GetDayCount(sceneId, selfId, nDayIndex, nDayCountIndex)


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
function x300732_SetDayCount(sceneId, selfId, nDayIndex, nDayCountIndex)

	

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
function x300732_ProcAcceptCheck(sceneId, selfId, NPCId)
	return 1
end

---------------------------------------------------------------------------------------------------
--向客户端发送任务信息
---------------------------------------------------------------------------------------------------
function x300732_DispatchMissionInfo( sceneId, selfId, NPCId, MissionId)

	BeginQuestEvent(sceneId)
	local localexp1 = (GetLevel( sceneId, selfId )) * 100*5*3	
	local localexp2 = (GetLevel( sceneId, selfId )) * 2200
	local localexp = 0
	if GetLevel(sceneId, selfId) >=40 and GetLevel(sceneId, selfId) < 70 then
		localexp = localexp1;
	elseif GetLevel(sceneId, selfId) >=70 then
		localexp = localexp2;
	end
		if MissionId == x300732_g_MissionId1 then
			AddQuestText(sceneId,"#Y【国家】敦煌除奸")
			--任务信息
			
			AddQuestText(sceneId,"   经过我们的多番打探，这叛贼张五常，化装成了一家商会的大掌柜，藏匿在敦煌王国边塞。此事宜早不宜迟，你立刻出发，干掉那叛徒！")
			AddQuestText(sceneId," ")

			--任务目标
			AddQuestText( sceneId,"#Y任务目标：")
			AddQuestText( sceneId,"  在本国边塞找到@npc_125509，传送到敦煌边塞，杀死敦煌边塞的大掌柜张五常。")
			AddQuestText( sceneId," ")

			AddQuestText(sceneId,"#Y任务奖励：")
			AddQuestText(sceneId,"  经验值："..localexp.."点#r  荣誉值：75点")
			AddQuestText(sceneId," ")
			
		elseif MissionId == x300732_g_MissionId2 then
			AddQuestText(sceneId,"#Y【国家】楼兰除奸")
			--任务信息
			
			AddQuestText(sceneId,"   经过我们的多番打探，这叛贼张五常，化装成了一家商会的大掌柜，藏匿在楼兰王国边塞。此事宜早不宜迟，你立刻出发，干掉那叛徒！")
			AddQuestText(sceneId," ")

			--任务目标
			AddQuestText( sceneId,"#Y任务目标：")
			AddQuestText( sceneId,"  在本国边塞找到@npc_125509，传送到楼兰边塞，杀死楼兰边塞的大掌柜张五常。")
			AddQuestText( sceneId," ")

			AddQuestText(sceneId,"#Y任务奖励：")
			AddQuestText(sceneId,"  经验值："..localexp.."点#r  荣誉值：75点")
			AddQuestText(sceneId," ")
			
		elseif MissionId == x300732_g_MissionId3 then
			AddQuestText(sceneId,"#Y【国家】昆仑除奸")
			--任务信息
			
			AddQuestText(sceneId,"   经过我们的多番打探，这叛贼张五常，化装成了一家商会的大掌柜，藏匿在昆仑王国边塞。此事宜早不宜迟，你立刻出发，干掉那叛徒！")
			AddQuestText(sceneId," ")

			--任务目标
			AddQuestText( sceneId,"#Y任务目标：")
			AddQuestText( sceneId,"  在本国边塞找到@npc_125509，传送到昆仑边塞，杀死昆仑边塞的大掌柜张五常。")
			AddQuestText( sceneId," ")

			AddQuestText(sceneId,"#Y任务奖励：")
			AddQuestText(sceneId,"  经验值："..localexp.."点#r  荣誉值：75点")
			AddQuestText(sceneId," ")
			
		elseif MissionId == x300732_g_MissionId4 then
			AddQuestText(sceneId,"#Y【国家】天山除奸")
			--任务信息
			
			AddQuestText(sceneId,"   经过我们的多番打探，这叛贼张五常，化装成了一家商会的大掌柜，藏匿在天山王国边塞。此事宜早不宜迟，你立刻出发，干掉那叛徒！")
			AddQuestText(sceneId," ")

			--任务目标
			AddQuestText( sceneId,"#Y任务目标：")
			AddQuestText( sceneId,"  在本国边塞找到@npc_125509，传送到天山边塞，杀死天山边塞的大掌柜张五常。")
			AddQuestText( sceneId," ")

			AddQuestText(sceneId,"#Y任务奖励：")
			AddQuestText(sceneId,"  经验值："..localexp.."点#r  荣誉值：75点")
			AddQuestText(sceneId," ")
			
		else
			return -1;
		end
		
			
		
		

	EndQuestEvent()
	DispatchQuestInfoNM(sceneId, selfId, NPCId, x300732_g_ScriptId, MissionId,0);
end

---------------------------------------------------------------------------------------------------
--向客户端发送任务未完成
---------------------------------------------------------------------------------------------------
function x300732_DispatchContinueInfo( sceneId, selfId, NPCId,MissionId )

	

	BeginQuestEvent(sceneId)
	local localexp1 = (GetLevel( sceneId, selfId )) * 100*5*3
	local localexp2 = (GetLevel( sceneId, selfId )) * 2200
	local localexp = 0
	if GetLevel(sceneId, selfId) >=40 and GetLevel(sceneId, selfId) < 70 then
		localexp = localexp1;
	elseif GetLevel(sceneId, selfId) >=70 then
		localexp = localexp2;
	end
		if MissionId == x300732_g_MissionId1 then
			AddQuestText(sceneId,"#Y【国家】敦煌除奸")
		--任务信息
			
			AddQuestText(sceneId,"   时间紧迫，你还是快去敦煌王国吧。")
			AddQuestText(sceneId," ")

			AddQuestText(sceneId,"#Y任务奖励：")
			AddQuestText(sceneId,"  经验值："..localexp.."点#r  荣誉值：75点")
			AddQuestText(sceneId," ")
		elseif MissionId == x300732_g_MissionId2 then
			AddQuestText(sceneId,"#Y【国家】楼兰除奸")
		--任务信息
			
			AddQuestText(sceneId,"   时间紧迫，你还是快去楼兰王国吧。")
			AddQuestText(sceneId," ")

			AddQuestText(sceneId,"#Y任务奖励：")
			AddQuestText(sceneId,"  经验值："..localexp.."点#r  荣誉值：75点")
			AddQuestText(sceneId," ")
		elseif MissionId == x300732_g_MissionId3 then
			AddQuestText(sceneId,"#Y【国家】昆仑除奸")
		--任务信息
			
			AddQuestText(sceneId,"   时间紧迫，你还是快去昆仑王国吧。")
			AddQuestText(sceneId," ")

			AddQuestText(sceneId,"#Y任务奖励：")
			AddQuestText(sceneId,"  经验值："..localexp.."点#r  荣誉值：75点")
			AddQuestText(sceneId," ")
		elseif MissionId == x300732_g_MissionId4 then
			AddQuestText(sceneId,"#Y【国家】天山除奸")
		--任务信息
			
			AddQuestText(sceneId,"   时间紧迫，你还是快去天山王国吧。")
			AddQuestText(sceneId," ")

			AddQuestText(sceneId,"#Y任务奖励：")
			AddQuestText(sceneId,"  经验值："..localexp.."点#r  荣誉值：75点")
			AddQuestText(sceneId," ")
		else
			return -1;
		end
		

	EndQuestEvent()
	DispatchQuestDemandInfo(sceneId, selfId, NPCId, x300732_g_ScriptId, MissionId,0);
	


end

---------------------------------------------------------------------------------------------------
--向客户端发送任务完成信息
---------------------------------------------------------------------------------------------------
function x300732_DispatchCompletedInfo( sceneId, selfId, NPCId,MissionId )
	

	BeginQuestEvent(sceneId)
	local localexp1 = (GetLevel( sceneId, selfId )) * 100*5*3
	local localexp2 = (GetLevel( sceneId, selfId )) * 2200
	local localexp = 0
	if GetLevel(sceneId, selfId) >=40 and GetLevel(sceneId, selfId) < 70 then
		localexp = localexp1;
	elseif GetLevel(sceneId, selfId) >=70 then
		localexp = localexp2;
	end
		if MissionId == x300732_g_MissionId1 then
			--任务信息
			AddQuestText(sceneId,"#Y【国家】敦煌除奸")
			AddQuestText(sceneId,"   这就是叛徒应有的下场，你又为我们国家立下一功！")
			AddQuestText(sceneId," ")

			AddQuestText(sceneId,"#Y任务奖励：")
			AddQuestText(sceneId,"  经验值："..localexp.."点#r  荣誉值：75点")
			AddQuestText(sceneId," ")
		elseif MissionId == x300732_g_MissionId2 then
			--任务信息
			AddQuestText(sceneId,"#Y【国家】楼兰除奸")
			AddQuestText(sceneId,"   这就是叛徒应有的下场，你又为我们国家立下一功！")
			AddQuestText(sceneId," ")

			AddQuestText(sceneId,"#Y任务奖励：")
			AddQuestText(sceneId,"  经验值："..localexp.."点#r  荣誉值：75点")
			AddQuestText(sceneId," ")
		elseif MissionId == x300732_g_MissionId3 then
			--任务信息
			AddQuestText(sceneId,"#Y【国家】昆仑除奸")
			AddQuestText(sceneId,"   这就是叛徒应有的下场，你又为我们国家立下一功！")
			AddQuestText(sceneId," ")

			AddQuestText(sceneId,"#Y任务奖励：")
			AddQuestText(sceneId,"  经验值："..localexp.."点#r  荣誉值：75点")
			AddQuestText(sceneId," ")
		elseif MissionId == x300732_g_MissionId4 then
			--任务信息
			AddQuestText(sceneId,"#Y【国家】天山除奸")
			AddQuestText(sceneId,"   这就是叛徒应有的下场，你又为我们国家立下一功！")
			AddQuestText(sceneId," ")

			AddQuestText(sceneId,"#Y任务奖励：")
			AddQuestText(sceneId,"  经验值："..localexp.."点#r  荣誉值：75点")
			AddQuestText(sceneId," ")
		else
			return -1;
		end

		
		
		
	EndQuestEvent()
	DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x300732_g_ScriptId, MissionId);

end


---------------------------------------------------------------------------------------------------
--任务日志刷新
---------------------------------------------------------------------------------------------------
function x300732_QuestLogRefresh( sceneId, selfId, MissionId)

	local nRet = x300732_IsSuccessed( sceneId, selfId, MissionId )
	local str = "";

	if MissionId == x300732_g_MissionId1 then
		if nRet>0 then
			str = "  从@npc_30003到敦煌边塞杀死@npc_30019（1/1）"
		else
			str = "  从@npc_30003到敦煌边塞杀死@npc_30019（0/1）"
		end
	elseif MissionId == x300732_g_MissionId2 then
		if nRet>0 then
			str = "  从@npc_30000到楼兰边塞杀死@npc_30016（1/1）"
		else
			str = "  从@npc_30000到楼兰边塞杀死@npc_30016（0/1）"
		end
	elseif MissionId == x300732_g_MissionId3 then
		if nRet>0 then
			str = "  从@npc_30002到昆仑边塞杀死@npc_30018（1/1）"
		else
			str = "  从@npc_30002到昆仑边塞杀死@npc_30018（0/1）"
		end
	elseif MissionId == x300732_g_MissionId4 then
		if nRet>0 then
			str = "  从@npc_30001到天山边塞杀死@npc_30017（1/1）"
		else
			str = "  从@npc_30001到天山边塞杀死@npc_30017（0/1）"
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
			AddQuestMoneyBonus6(sceneId, 75 )
		end		
		
	AddQuestLogCustomText( sceneId,
							"",						-- 标题
							"【国家】敌国除奸",        -- 任务名字
							str,		--任务目标
							"@npc_125501",			--任务NPC
							"通过@npc_125509潜入敌国，将边塞大掌柜张五常杀死。\n楼兰边塞大掌柜坐标（36，203）\n天山边塞大掌柜坐标（215，216）\n昆仑边塞大掌柜坐标（43，45）\n敦煌边塞大掌柜坐标（225，35）",               --任务攻略
							"想不到我们派往敌国的密探统领张五常，被敌人俘虏后竟然背叛了我们！他的手中掌握着我们大量密探的信息，看来只有干掉此人，才能防止我们苦心经营多年的密探网被彻底摧毁。",	--任务描述
							"当您在出国令期间回复任务时，你将获得双倍的奖励！"					--任务小提示
							)
	EndQuestEvent()
	DispatchQuestLogUpdate(sceneId, selfId, MissionId);
		

end

function x300732_ProcQuestLogRefresh( sceneId, selfId, MissionId)
	
	x300732_QuestLogRefresh( sceneId, selfId, MissionId );
end