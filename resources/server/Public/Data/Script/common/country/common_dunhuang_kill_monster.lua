
--MisDescBegin

x300879_g_ScriptId 					= 	300879                  --脚本ID


x300879_g_MissionKind 				= 	1                       --任务类型
x300879_g_LevelLess					= 	40                      --场景开放等级  <=0 表示不限制





x300879_g_MissionName				= 	"敌国刺杀"
x300879_g_MissionTarget				= 	""
x300879_g_MissionInfo				= 	""
x300879_g_ContinueInfo				= 	""
x300879_g_MissionCompleted			= 	""
x300879_g_MissionHelp				=	""          --任务提示信息

--目标
x300879_g_ExtTarget					=	{ {type=20,n=10,target="获得刺杀"}}

--奖励

x300879_g_ExpBonus					= 	0;--x300879_AddExpAward               	--奖励：经验
x300879_g_BonusItem					=	{}	--奖励：物品

x300879_g_BonusMoney1               = 	0
x300879_g_BonusMoney2               =   0
x300879_g_BonusMoney3               =   0

x300879_g_BonusChoiceItem           =   {}


--MisDescEnd


x300879_g_KillMissionId =  7007

x300879_g_DayCountLimited   = 1

x300879_g_Mis_Count = 1
x300879_g_ItemID = 13010021         --合成后的物品ID
x300879_g_NeedItem1 = 13011007 --打怪要掉的物品
x300879_g_NeedItem2 = 13011008
x300879_g_NeedItemID = 13011009
--x300879_g_Fail = MD_COUNTRY_KILLMONSTER_ABANDON
x300879_g_LevelNeeded = 100

x300879_g_MissionId1 = 7659
x300879_g_MissionId2 = 7650
x300879_g_MissionId3 = 7656
x300879_g_MissionId4 = 7653
x300879_g_CountryDunhuang =  351--四个国家的场景id
x300879_g_CountryLouLan =  51
x300879_g_CountryKunlun = 251
x300879_g_CountryLaiYin = 151


x300879_g_NeedItemCount = 1


x300879_g_MissionBonusInfo			= 	"#Y获得经验#R%d#Y的奖励。"
         
function x300879_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

end

--选中任务
function x300879_ProcEventEntry( sceneId, selfId, targetId, MissionId, index )

	----PrintStr("x300879_ProcEventEntry")

	if index ~= -1 then
		MissionId = index
	end

	if IsHaveQuestNM( sceneId, selfId, MissionId ) == 0 then	-- 如果没有这个任务
		
		--不要给出npc身上没有任务的这个提示！
		local ret = QuestCheckAcceptNM( sceneId, selfId, targetId, MissionId )
		if ret > 0 then	-- 如果可以接这个任务
			--AddDispatchQuestInfoNM( sceneId, selfId, targetId, MissionId ) -- 显示接受任务信息
			x300879_DispatchMissionInfo( sceneId, selfId, targetId, MissionId )
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
		if x300879_CheckSubmit( sceneId, selfId, MissionId ) > 0 then -- 如果任务可以完成
			--QuestComplateInfoNM( sceneId, selfId, targetId, MissionId ) -- 显示完成信息
			x300879_DispatchCompletedInfo( sceneId, selfId, targetId,MissionId )
		else
			--QuestNotComplateInfoNM( sceneId, selfId, targetId, MissionId ) -- 显示任务未完成信息
			x300879_DispatchContinueInfo( sceneId, selfId, targetId,MissionId )
		end
	end
				
end

function x300879_ProcQuestAttach( sceneId, selfId, npcId, npcGuid,misIndex, MissionId )

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

--完成任务
--返回1代表成功，0代表交任务失败
function x300879_ProcQuestSubmit( sceneId, selfId, targetId, selectId, MissionId )

	if IsHaveQuestNM( sceneId, selfId, MissionId) == 0 then	-- 如果没这个任务直接退出
		return 0
	end

	local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )
	--if QuestCheckSubmitNM( sceneId, selfId, targetId, MissionId, misIndex ) > 0 then
	if x300879_CheckSubmit( sceneId, selfId, MissionId )>0 then
		x300879_MissionComplate(sceneId, selfId, targetId, selectId, MissionId)
	end

	return 0
end

function x300879_CheckSubmit( sceneId, selfId, MissionId )
	if IsHaveQuestNM( sceneId, selfId, MissionId) == 0 then
		return 0;
	end

	if MissionId ~= x300879_g_MissionId1 and MissionId ~= x300879_g_MissionId2 and MissionId ~= x300879_g_MissionId3 and MissionId ~= x300879_g_MissionId4 then
		return 0;
	end

	local ItemCnt = GetItemCount( sceneId, selfId, x300879_g_NeedItemID )

	if ItemCnt<x300879_g_NeedItemCount then
		return 0;
	end

	return 1;


end

--********************************************************************
--放弃
--********************************************************************
function x300879_ProcQuestAbandon( sceneId, selfId,MissionId )
	
	if IsHaveQuestNM( sceneId, selfId, MissionId ) <= 0 then	-- 如果有这个任务直接退出
		return 0
	end

	local n = GetItemCount( sceneId, selfId, x300879_g_NeedItemID );

	if MissionId == x300879_g_MissionId1 then
		x300879_SetDayCount(sceneId, selfId, DQ_SHAGUAI_DUNHUANG_DATE,DQ_SHAGUAI_DUNHUANG_DAYCOUNT)
	elseif MissionId == x300879_g_MissionId2 then
		x300879_SetDayCount(sceneId, selfId, DQ_SHAGUAI_LOULAN_DATE,DQ_SHAGUAI_LOULAN_DAYCOUNT)
	elseif MissionId == x300879_g_MissionId3 then
		x300879_SetDayCount(sceneId, selfId, DQ_SHAGUAI_KUNLUN_DATE,DQ_SHAGUAI_KUNLUN_DAYCOUNT)
	elseif MissionId == x300879_g_MissionId4 then
		x300879_SetDayCount(sceneId, selfId, DQ_SHAGUAI_LAIYIN_DATE,DQ_SHAGUAI_LAIYIN_DAYCOUNT)
	else
		return -1;
	end
	
	if n > 0 then
		DelItem(sceneId, selfId,x300879_g_NeedItemID,n)
		
	end


	DelQuestNM( sceneId, selfId, MissionId )
	    BeginQuestEvent(sceneId);
		AddQuestText(sceneId, "您放弃了任务:【国家】敌国刺杀");
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
		Msg2Player(sceneId,selfId,"您放弃了任务:【国家】敌国刺杀",8,2)


end


--********************************************************************
--接受
--********************************************************************
function x300879_ProcQuestAccept( sceneId, selfId, targetId, MissionId )

	
	if IsHaveQuestNM( sceneId, selfId, MissionId ) > 0 then	-- 如果有这个任务直接退出
		return 0
	end


	if	IsHaveQuestNM( sceneId, selfId, x300879_g_MissionId1 ) > 0 or IsHaveQuestNM( sceneId, selfId, x300879_g_MissionId2 ) > 0 or IsHaveQuestNM( sceneId, selfId, x300879_g_MissionId3 ) > 0 or IsHaveQuestNM( sceneId, selfId, x300879_g_MissionId4 ) > 0 then
		BeginQuestEvent(sceneId)
		local strText = "您已经接过了【国家】敌国刺杀任务，还未完成，不能再接取"
		AddQuestText( sceneId, strText )
		EndQuestEvent( sceneId )
		DispatchQuestTips( sceneId, selfId )
		Msg2Player(sceneId,selfId,"您已经接过了【国家】敌国刺杀任务，还未完成，不能再接取",8,2)
		return
	end

	local nDayCount =0;

	if MissionId == x300879_g_MissionId1 then
		nDayCount = x300879_GetDayCount(sceneId, selfId, DQ_SHAGUAI_DUNHUANG_DATE,DQ_SHAGUAI_DUNHUANG_DAYCOUNT)
	elseif MissionId == x300879_g_MissionId2 then
		nDayCount = x300879_GetDayCount(sceneId, selfId, DQ_SHAGUAI_LOULAN_DATE,DQ_SHAGUAI_LOULAN_DAYCOUNT)
	elseif MissionId == x300879_g_MissionId3 then
		nDayCount = x300879_GetDayCount(sceneId, selfId, DQ_SHAGUAI_KUNLUN_DATE,DQ_SHAGUAI_KUNLUN_DAYCOUNT)
	elseif MissionId == x300879_g_MissionId4 then
		nDayCount = x300879_GetDayCount(sceneId, selfId, DQ_SHAGUAI_LAIYIN_DATE,DQ_SHAGUAI_LAIYIN_DAYCOUNT)
	else
		return -1;
	end

	if nDayCount>=x300879_g_DayCountLimited then
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
			--hf_MissionAfterAccept(sceneId, selfId, MissionId);
			--hf_DisplayAcceptMessage(sceneId, selfId, MissionId);
			BeginQuestEvent(sceneId);
			AddQuestText(sceneId, "您接受了任务:【国家】敌国刺杀");
			EndQuestEvent();
			DispatchQuestTips(sceneId, selfId);
			Msg2Player(sceneId,selfId,"您接受了任务:【国家】敌国刺杀",8,2)
			return 1
		else
			--hf_DisplayMissionAcceptErrorMessage(sceneId, selfId, ret);
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



--杀死怪物
function x300879_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
	
	----PrintStr(objdataId)
	if x300879_CountryCheck( sceneId, selfId, MissionId ) < 0 then
		return -1;
	end

	if objdataId ~= 9510 then
		return -1;
	end

	local sign = 0;
	local ItemCount=0;
	local ItemID=0;
	local ItemRand=0;
	local ItemDropNum=0;
	local droprand = 0;
	--场景ID, 自己的ID, 怪物表位置号, 怪物objId, 任务ID
	local NeedKilledNum, InstIndex, ObjName = GetQuestNeedKillObjInfoNM( sceneId, selfId, MissionId, objdataId, objId )
	
	----PrintNum(NeedKilledNum)
	----PrintNum(InstIndex)
	----PrintStr(ObjName)


		if NeedKilledNum >= 0 then
			local x,z = GetWorldPos(sceneId,selfId)
			
			local KilledNum =  GetNearCountryCount(sceneId, selfId,x,z,20)  
			
			
			for i = 0, KilledNum-1 do
				local humanObjId = GetNearCountryMember(sceneId, selfId,i) --取得拥有分配权的人的objId
				--PrintNum(humanObjId)
				if humanObjId ~= -1 then
					if IsPlayerStateNormal(sceneId, humanObjId) > 0 then
						if GetHp(sceneId, humanObjId) > 0 then
							if IsHaveQuestNM( sceneId, humanObjId, MissionId ) > 0 then	--如果这个人拥有任务
								------PrintNum(77)
								if InstIndex >= 0 then
									if sign == 0 then
										------PrintNum(88)
										ItemCount, ItemID, ItemRand, ItemDropNum = GetQuestItemNM( sceneId, humanObjId, MissionId, InstIndex )
										----PrintNum(ItemCount)
										----PrintNum(ItemID)
										----PrintNum(ItemRand)
										----PrintNum(ItemDropNum)
										droprand = random(100)
										sign = 1;
									end
									
											--要收集的个数，物品ID，掉落率，一次最大掉落
									if HaveItem( sceneId, humanObjId, ItemID ) <  x300879_g_NeedItemCount then --如果没有这个物品 
									
										if ItemCount > 0 then
											
											if droprand<= ItemRand then
											
												BeginAddItem(sceneId)
												AddItem( sceneId, ItemID, 1 )
												local ret = EndAddItem(sceneId,humanObjId)
												if ret > 0 then
													--AddItemListToPlayer(sceneId,selfId)
													AddItemListToPlayer(sceneId,humanObjId)
													
												else
													BeginQuestEvent(sceneId)
													AddQuestText(sceneId,"物品栏已满，无法得到任务物品！")
													EndQuestEvent(sceneId)
													DispatchQuestTips(sceneId,humanObjId)
												end
											end
												
										end
										
									end
								end
							end
						end
					end
				end
			end
		end

	return 0
	
end


--物品改变
function x300879_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )--寻找材料的任务完成后再添加合成任务

	----PrintStr("x300879_ProcQuestItemChanged")
	----PrintNum(itemdataId)
	----PrintNum(MissionId)
	--if x300879_CountryCheck( sceneId, selfId, MissionId ) < 0 then
	--	return 
	--end

	if IsPlayerStateNormal(sceneId, selfId) == 0 then
		return 
	end

	if GetHp(sceneId, selfId) <= 0 then
		return
	end

	
	if MissionId == nil or MissionId < 0 then
        return 
    end
    
    if IsHaveQuestNM(sceneId,selfId,MissionId) <= 0 then
        return 
    end

	local NeedNum, ObjIndex = GetQuestNeedItemNumNM( sceneId, selfId, MissionId, itemdataId )
	--
	local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )

	if NeedNum > 0 then
		local Num = GetItemCount( sceneId, selfId, itemdataId ) 
		if Num < x300879_g_NeedItemCount then --还没有完成任务
			--BeginQuestEvent(sceneId)
			local strText = format("您杀死了边塞主将: %d/%d#r获得了物品：将军令", Num, NeedNum)
			if strText == nil then
				strText = "";
			end
			--AddQuestText( sceneId, strText )
			--EndQuestEvent( sceneId )
			--DispatchQuestTips( sceneId, selfId )
   			SetQuestByIndex( sceneId, selfId, misIndex, ObjIndex, Num )         --by zheng
			SetQuestByIndex( sceneId, selfId, misIndex, 7, 0 )
			x300879_QuestLogRefresh( sceneId, selfId, MissionId)
		elseif Num >= x300879_g_NeedItemCount then
			--已经完成任务
			BeginQuestEvent(sceneId)
			local strText = format( "您杀死了边塞主将: %d/%d", Num, NeedNum )
			if strText == nil then
				strText = "";
			end
			AddQuestText( sceneId, strText )
			EndQuestEvent( sceneId )
			DispatchQuestTips( sceneId, selfId )
			BeginQuestEvent(sceneId)
			AddQuestText( sceneId, "获得了物品：将军令" )
			EndQuestEvent( sceneId )
			DispatchQuestTips( sceneId, selfId )
			--PrintNum(ObjIndex)
			SetQuestByIndex( sceneId, selfId, misIndex, ObjIndex, x300879_g_NeedItemCount )         --by zheng

			SetQuestByIndex( sceneId, selfId, misIndex, 7, 1 )
			x300879_QuestLogRefresh( sceneId, selfId, MissionId)
		end
	end
	return 0
	
end


function x300879_MissionComplate(sceneId, selfId, targetId, selectId, MissionId)

    if MissionId == nil or MissionId < 0 then
        return 0
    end
    
    if IsHaveQuestNM( sceneId,selfId,MissionId )<= 0 then
        return 0
    end
    

	local ret = QuestComplateNM( sceneId, selfId, targetId, MissionId, selectId ) -- 获取完成任务信息
	if ret == 1 then -- 如果成功完成
		if MissionId == x300879_g_MissionId1 then
			x300879_SetDayCount(sceneId, selfId, DQ_SHAGUAI_DUNHUANG_DATE,DQ_SHAGUAI_DUNHUANG_DAYCOUNT)
		elseif MissionId == x300879_g_MissionId2 then
			x300879_SetDayCount(sceneId, selfId, DQ_SHAGUAI_LOULAN_DATE,DQ_SHAGUAI_LOULAN_DAYCOUNT)
		elseif MissionId == x300879_g_MissionId3 then
			x300879_SetDayCount(sceneId, selfId, DQ_SHAGUAI_KUNLUN_DATE,DQ_SHAGUAI_KUNLUN_DAYCOUNT)
		elseif MissionId == x300879_g_MissionId4 then
			x300879_SetDayCount(sceneId, selfId, DQ_SHAGUAI_LAIYIN_DATE,DQ_SHAGUAI_LAIYIN_DAYCOUNT)
		else
			return -1;
		end
		
		local ItemCnt = GetItemCount( sceneId, selfId, x300879_g_NeedItemID )
		if ItemCnt > 0 then --双倍奖励
			DelItem(sceneId, selfId,x300879_g_NeedItemID,ItemCnt)	
		else	
		end	
		--提示玩家任务完成
		--hf_DisplayCompleteMessage(sceneId, selfId, MissionId);
		--hf_DisplayAwardInfo(sceneId, selfId, targetId, MissionId, selectId)--提示玩家金钱经验声望的奖励信息
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, "您完成了任务:【国家】敌国刺杀");
		EndQuestEvent();
		Msg2Player(sceneId,selfId,"您完成了任务:【国家】敌国刺杀",8,2)

		DispatchQuestTips(sceneId, selfId);


		x300879_GiveReward(sceneId,selfId)
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
			local strMsg = format("CGL:<Info>x300879_MissionComplate sceneId=%d,country=%d", sceneId, country )
    		WriteLog( 1, strMsg )
		end
		
		return 1 -- 返回成功
	else -- 如果未成功完成
		--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(sceneId, selfId, ret);
		BeginQuestEvent(sceneId);
			AddQuestText(sceneId, "任务完成错误");
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
		return 0
	end
	return 0

end

function x300879_GiveReward(sceneId,selfId)

	local level = GetLevel(sceneId, selfId)
	local nExpBonus1 = 100*2.6*level*5;
	local nExpBonus2 = 1750*level;
	local nExpBonus = 0;
	if GetLevel(sceneId, selfId) >=40 and GetLevel(sceneId, selfId) < 70 then
		nExpBonus = nExpBonus1;
	elseif GetLevel(sceneId, selfId) >=70 then
		nExpBonus = nExpBonus2;
	end
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
  		Msg2Player(sceneId,selfId,"#o获得#R经验"..nExpBonus.."点#o的奖励#r#o获得#R荣誉50点#o的奖励",4,2)
  			CallScriptFunction( 256271, "Finishcisha", sceneId, selfId)
		local ret = CountryIsFortuneTime(sceneId,selfId,1)
		if ret == 1 then
			AddExp(sceneId, selfId, nExpBonus);
			--AddHonor(sceneId, selfId, 50);
			BeginQuestEvent(sceneId);
			AddQuestText(sceneId, "#o出国令额外获得#R经验"..nExpBonus.."点#o的奖励");
			EndQuestEvent();
			DispatchQuestTips(sceneId, selfId);
			--BeginQuestEvent(sceneId);
			--AddQuestText(sceneId, "#o额外获得#R荣誉50点#o的奖励");
			--EndQuestEvent();
			--DispatchQuestTips(sceneId, selfId);
			Msg2Player(sceneId,selfId,"#o出国令额外获得#R经验"..nExpBonus.."点#o的奖励",4,2)--#r#o额外获得#R荣誉50点#o的奖励",4,2)
			
			--据点额外奖励
			local nCountry = GetCurCountry(sceneId,selfId)
			local nLairdCount,nLairdSumLevel =  CallScriptFunction(888888,"GetCountryLairdSceneInfo",sceneId,nCountry)
			if nLairdCount > 0 then
			
				local nLairdExpBonus = floor((nLairdSumLevel*0.02)*nExpBonus)
				local nLairdHornorBonus = floor((nLairdSumLevel*0.02)*50)
				
				
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

function x300879_OnLogInOrDie( sceneId, selfId )
	
   x300879_OnMissionFailed( sceneId, selfId )
end



function x300879_OnMissionFailed( sceneId, selfId )
	
	x300879_CountryKillOnDie(sceneId, selfId)

end

function x300879_CountryKillOnDie( sceneId, selfId )
	
	if 0==0 then
		return
	end
	

	
	local MissionId = -1
	if IsHaveQuestNM( sceneId, selfId, x300879_g_MissionId1 ) > 0 then
		MissionId = x300879_g_MissionId1
	elseif IsHaveQuestNM( sceneId, selfId, x300879_g_MissionId2 ) > 0 then
		MissionId = x300879_g_MissionId2
	elseif IsHaveQuestNM( sceneId, selfId, x300879_g_MissionId3 ) > 0 then
		MissionId = x300879_g_MissionId3
	elseif IsHaveQuestNM( sceneId, selfId, x300879_g_MissionId4 ) > 0 then
		MissionId = x300879_g_MissionId4
	end
	if MissionId  ~= -1 then
		if GetItemCount( sceneId, selfId,x300879_g_NeedItemID ) > 0 then  --//如果任务完成
			return 0;
		end
		local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )
		SetQuestByIndex( sceneId, selfId, misIndex, 0, 0 )
		SetQuestByIndex( sceneId, selfId, misIndex, 1, 0 )
	end
	
end

function x300879_CountryCheck( sceneId, selfId, MissionId )
	if MissionId == x300879_g_MissionId1 then
		if sceneId == x300879_g_CountryDunhuang then
			return 1
		end
	elseif MissionId == x300879_g_MissionId2 then
		if sceneId == x300879_g_CountryLouLan then
			return 1
		end
	elseif MissionId == x300879_g_MissionId3 then
		if sceneId == x300879_g_CountryKunlun then
			return 1
		end
	elseif MissionId == x300879_g_MissionId4 then
		if sceneId == x300879_g_CountryLaiYin then
			return 1
		end
	end
	return -1
end

function x300879_ProcQuestLogRefresh( sceneId,selfId,missionId)
	--local sceneName = CallScriptFunction( 300700, "GetSceneName", sceneId, selfId )
	local str = "#G本国金盾大元帅"
    BeginQuestEvent(sceneId)
        AddQuestLogCustomText( sceneId,
                                "",                    -- 标题
                                "",                 -- 任务名字
                                "",               --任务目标
                                str,                         --任务NPC
                                "",                   --任务攻略
                                "",                --任务描述
                                ""        --任务小提示
                                )

	EndQuestEvent()
	DispatchQuestLogUpdate(sceneId, selfId, missionId);
end


---------------------------------------------------------------------------------------------------
--取得当前次数
---------------------------------------------------------------------------------------------------
function x300879_GetDayCount(sceneId, selfId, nDayIndex, nDayCountIndex)



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
function x300879_SetDayCount(sceneId, selfId, nDayIndex, nDayCountIndex)

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
function x300879_ProcAcceptCheck(sceneId, selfId, NPCId)
	return 1
end

---------------------------------------------------------------------------------------------------
--向客户端发送任务信息
---------------------------------------------------------------------------------------------------
function x300879_DispatchMissionInfo( sceneId, selfId, NPCId, MissionId)

	BeginQuestEvent(sceneId)
	local localexp1 = (GetLevel( sceneId, selfId )) * 100*2.6*5	
	local localexp2 = (GetLevel( sceneId, selfId )) * 1750
	local localexp = 0
	if GetLevel(sceneId, selfId) >=40 and GetLevel(sceneId, selfId) < 70 then
		localexp = localexp1;
	elseif GetLevel(sceneId, selfId) >=70 then
		localexp = localexp2;
	end
		if MissionId == x300879_g_MissionId1 then
			AddQuestText(sceneId,"#Y【国家】敦煌刺杀")
			--任务信息
			
			AddQuestText(sceneId,"   敦煌的边塞主将，正带领着他的手下们，在敦煌边塞的（36，53）处巡查。趁此良机，你悄悄潜入那里，干掉边塞主将！当然，别忘了把他随身携带的那枚#G将军令#W带回来！")
			AddQuestText(sceneId," ")

			--任务目标
			AddQuestText( sceneId,"#Y任务目标：")
			AddQuestText( sceneId,"  在本国边塞找到@npc_134511，传送到敦煌边塞，杀死敦煌边塞（36，53）处的边塞主将，获得将军令。")
			AddQuestText( sceneId," ")

			AddQuestText(sceneId,"#Y任务奖励：")
			AddQuestText(sceneId,"  经验值："..localexp.."点#r  荣誉值：50点")
			AddQuestText(sceneId," ")
			
		elseif MissionId == x300879_g_MissionId2 then
			AddQuestText(sceneId,"#Y【国家】楼兰刺杀")
			--任务信息
			
			AddQuestText(sceneId,"   楼兰的边塞主将，正带领着他的手下们，在楼兰边塞的（211，173）处巡查。趁此良机，你悄悄潜入那里，干掉边塞主将！当然，别忘了把他随身携带的那枚#G将军令#W带回来！")
			AddQuestText(sceneId," ")

			--任务目标
			AddQuestText( sceneId,"#Y任务目标：")
			AddQuestText( sceneId,"  在本国边塞找到@npc_134511，传送到楼兰边塞，杀死楼兰边塞（211，173）处的边塞主将，获得将军令。")
			AddQuestText( sceneId," ")

			AddQuestText(sceneId,"#Y任务奖励：")
			AddQuestText(sceneId,"  经验值："..localexp.."点#r  荣誉值：50点")
			AddQuestText(sceneId," ")
			
		elseif MissionId == x300879_g_MissionId3 then
			AddQuestText(sceneId,"#Y【国家】昆仑刺杀")
			--任务信息
			
			AddQuestText(sceneId,"   昆仑的边塞主将，正带领着他的手下们，在昆仑边塞的（212，58）处巡查。趁此良机，你悄悄潜入那里，干掉边塞主将！当然，别忘了把他随身携带的那枚#G将军令#W带回来！")
			AddQuestText(sceneId," ")

			--任务目标
			AddQuestText( sceneId,"#Y任务目标：")
			AddQuestText( sceneId,"  在本国边塞找到@npc_134511，传送到昆仑边塞，杀死昆仑边塞（212，58）处的边塞主将，获得将军令。")
			AddQuestText( sceneId," ")

			AddQuestText(sceneId,"#Y任务奖励：")
			AddQuestText(sceneId,"  经验值："..localexp.."点#r  荣誉值：50点")
			AddQuestText(sceneId," ")
			
		elseif MissionId == x300879_g_MissionId4 then
			AddQuestText(sceneId,"#Y【国家】天山刺杀")
			--任务信息
			
			AddQuestText(sceneId,"   天山的边塞主将，正带领着他的手下们，在天山边塞的（36，201）处巡查。趁此良机，你悄悄潜入那里，干掉边塞主将！当然，别忘了把他随身携带的那枚#G将军令#W带回来！")
			AddQuestText(sceneId," ")

			--任务目标
			AddQuestText( sceneId,"#Y任务目标：")
			AddQuestText( sceneId,"  在本国边塞找到@npc_134511，传送到天山边塞，杀死天山边塞（36，201）处的边塞主将，获得将军令。")
			AddQuestText( sceneId," ")

			AddQuestText(sceneId,"#Y任务奖励：")
			AddQuestText(sceneId,"  经验值："..localexp.."点#r  荣誉值：50点")
			AddQuestText(sceneId," ")

		else
			return -1;
		end
		
			
		
		

	EndQuestEvent()
	DispatchQuestInfoNM(sceneId, selfId, NPCId, x300879_g_ScriptId, MissionId,0);
end

---------------------------------------------------------------------------------------------------
--向客户端发送任务未完成
---------------------------------------------------------------------------------------------------
function x300879_DispatchContinueInfo( sceneId, selfId, NPCId,MissionId )

	

	BeginQuestEvent(sceneId)
	local localexp1 = (GetLevel( sceneId, selfId )) * 100*2.6*5
	local localexp2 = (GetLevel( sceneId, selfId )) * 1750
	local localexp = 0
	if GetLevel(sceneId, selfId) >=40 and GetLevel(sceneId, selfId) < 70 then
		localexp = localexp1;
	elseif GetLevel(sceneId, selfId) >=70 then
		localexp = localexp2;
	end
		if MissionId == x300879_g_MissionId1 then
			AddQuestText(sceneId,"#Y【国家】敦煌刺杀")
		--任务信息
			
			AddQuestText(sceneId,"   你还在磨蹭什么？别让那敦煌边塞的主将跑了！")
			AddQuestText(sceneId," ")

			AddQuestText(sceneId,"#Y任务奖励：")
			AddQuestText(sceneId,"  经验值："..localexp.."点#r  荣誉值：50点")
			AddQuestText(sceneId," ")
		elseif MissionId == x300879_g_MissionId2 then
			AddQuestText(sceneId,"#Y【国家】楼兰刺杀")
		--任务信息
			
			AddQuestText(sceneId,"   你还在磨蹭什么？别让那楼兰边塞的主将跑了！")
			AddQuestText(sceneId," ")

			AddQuestText(sceneId,"#Y任务奖励：")
			AddQuestText(sceneId,"  经验值："..localexp.."点#r  荣誉值：50点")
			AddQuestText(sceneId," ")
		elseif MissionId == x300879_g_MissionId3 then
			AddQuestText(sceneId,"#Y【国家】昆仑刺杀")
		--任务信息
			
			AddQuestText(sceneId,"   你还在磨蹭什么？别让那昆仑边塞的主将跑了！")
			AddQuestText(sceneId," ")

			AddQuestText(sceneId,"#Y任务奖励：")
			AddQuestText(sceneId,"  经验值："..localexp.."点#r  荣誉值：50点")
			AddQuestText(sceneId," ")
		elseif MissionId == x300879_g_MissionId4 then
			AddQuestText(sceneId,"#Y【国家】天山刺杀")
		--任务信息
			
			AddQuestText(sceneId,"   你还在磨蹭什么？别让那天山边塞的主将跑了！")
			AddQuestText(sceneId," ")

			AddQuestText(sceneId,"#Y任务奖励：")
			AddQuestText(sceneId,"  经验值："..localexp.."点#r  荣誉值：50点")
			AddQuestText(sceneId," ")
		else
			return -1;
		end
		

	EndQuestEvent()
	DispatchQuestDemandInfo(sceneId, selfId, NPCId, x300879_g_ScriptId, MissionId,0);
	


end

---------------------------------------------------------------------------------------------------
--向客户端发送任务完成信息
---------------------------------------------------------------------------------------------------
function x300879_DispatchCompletedInfo( sceneId, selfId, NPCId,MissionId )
	

	BeginQuestEvent(sceneId)
	local localexp1 = (GetLevel( sceneId, selfId )) * 100*2.6*5
	local localexp2 = (GetLevel( sceneId, selfId )) * 1750
	local localexp = 0
	if GetLevel(sceneId, selfId) >=40 and GetLevel(sceneId, selfId) < 70 then
		localexp = localexp1;
	elseif GetLevel(sceneId, selfId) >=70 then
		localexp = localexp2;
	end	
		if MissionId == x300879_g_MissionId1 then
			--任务信息
			AddQuestText(sceneId,"#Y【国家】敦煌刺杀")
			AddQuestText(sceneId,"   多谢你干掉了这敦煌的边塞主将！此次你对国家做出的贡献极大，我定会为你表功。")
			AddQuestText(sceneId," ")

			AddQuestText(sceneId,"#Y任务奖励：")
			AddQuestText(sceneId,"  经验值："..localexp.."点#r  荣誉值：50点")
			AddQuestText(sceneId," ")
		elseif MissionId == x300879_g_MissionId2 then
			--任务信息
			AddQuestText(sceneId,"#Y【国家】楼兰刺杀")
			AddQuestText(sceneId,"   多谢你干掉了这楼兰的边塞主将！此次你对国家做出的贡献极大，我定会为你表功。")
			AddQuestText(sceneId," ")

			AddQuestText(sceneId,"#Y任务奖励：")
			AddQuestText(sceneId,"  经验值："..localexp.."点#r  荣誉值：50点")
		elseif MissionId == x300879_g_MissionId3 then
			--任务信息
			AddQuestText(sceneId,"#Y【国家】昆仑刺杀")
			AddQuestText(sceneId,"   多谢你干掉了这昆仑的边塞主将！此次你对国家做出的贡献极大，我定会为你表功。")
			AddQuestText(sceneId," ")

			AddQuestText(sceneId,"#Y任务奖励：")
			AddQuestText(sceneId,"  经验值："..localexp.."点#r  荣誉值：50点")
		elseif MissionId == x300879_g_MissionId4 then
			--任务信息
			AddQuestText(sceneId,"#Y【国家】天山刺杀")
			AddQuestText(sceneId,"   多谢你干掉了这天山的边塞主将！此次你对国家做出的贡献极大，我定会为你表功。")
			AddQuestText(sceneId," ")

			AddQuestText(sceneId,"#Y任务奖励：")
			AddQuestText(sceneId,"  经验值："..localexp.."点#r  荣誉值：50点")
		else
			return -1;
		end

		
		
		
	EndQuestEvent()
	DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x300879_g_ScriptId, MissionId);

end


---------------------------------------------------------------------------------------------------
--任务日志刷新
---------------------------------------------------------------------------------------------------
function x300879_QuestLogRefresh( sceneId, selfId, MissionId)

	
	local ret = x300879_CheckSubmit( sceneId, selfId, MissionId )

	
	
	local str = "";

	if MissionId == x300879_g_MissionId1 then
		if ret>0 then
			str = "  从@npc_30015到敦煌边塞杀死@npc_30023（1/1）"
		else
			str = "  从@npc_30015到敦煌边塞杀死@npc_30023（0/1）"
		end
	elseif MissionId == x300879_g_MissionId2 then
		if ret>0 then
			str = "  从@npc_30012到楼兰边塞杀死@npc_30020（1/1）"
		else
			str = "  从@npc_30012到楼兰边塞杀死@npc_30020（0/1）"
		end
	elseif MissionId == x300879_g_MissionId3 then
		if ret>0 then
			str = "  从@npc_30014到昆仑边塞杀死@npc_30022（1/1）"
		else
			str = "  从@npc_30014到昆仑边塞杀死@npc_30022（0/1）"
		end
	elseif MissionId == x300879_g_MissionId4 then
		if ret>0 then
			str = "  从@npc_30013到天山边塞杀死@npc_30021（1/1）"
		else
			str = "  从@npc_30013到天山边塞杀死@npc_30021（0/1）"
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
			AddQuestMoneyBonus6(sceneId, 50 )
		end		
	AddQuestLogCustomText( sceneId,
							"",						-- 标题
							"【国家】敌国刺杀",        -- 任务名字
							str,		--任务目标
							"@npc_134505",			--任务NPC
							"通过@npc_134511潜入敌国，刺杀边塞的主将。\n楼兰边塞主将坐标（211，173）\n天山边塞主将坐标（36，201）\n昆仑边塞主将坐标（212，58）\n敦煌边塞主将坐标（36，53）",               --任务攻略
							"\t近日，敌国的边塞主将突然增派了大量人手巡查他们整个边塞地区，我国暗探损失惨重。\n\t绝不能让这种情况继续下去！你立刻潜入敌国，刺杀他们的主将，如果得手，定能让他们整个边塞军务陷入混乱！",	--任务描述
							"当您在出国令期间回复任务时，你将获得双倍的奖励！"					--任务小提示
							)
	EndQuestEvent()
	DispatchQuestLogUpdate(sceneId, selfId, MissionId);
		

end

function x300879_ProcQuestLogRefresh( sceneId, selfId, MissionId)
	
	x300879_QuestLogRefresh( sceneId, selfId, MissionId );
end
