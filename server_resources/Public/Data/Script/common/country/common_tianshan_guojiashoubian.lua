--***********************
--Const
--***********************
-------------------------

--MisDescBegin


x300860_g_MissionId 				= 	7569                     --任务ID
x300860_g_ScriptId 					= 	300860                  --脚本ID
x300860_g_MissionKind 				= 	1                       --任务类型
x300860_g_LevelLess					= 	30                      --场景开放等级  <=0 表示不限制


x300860_g_MissionName				= 	"【国家】国家守边"
x300860_g_MissionTarget				= 	"我国正面临敌国严重的骚扰和威胁，需要大家共同出力，守卫边关。你愿意接受此任务，守卫边关一段时间吗？"
x300860_g_MissionInfo				= 	"您接受任务后，经过一段时间即可向我汇报军情，并完成任务得到奖励。当您的#G计时器#W变成#R红色#W时就可准备找我#G回复#W了，如#G错过#W时间，任务就会#G失败#W，请你注意时间。"
x300860_g_ContinueInfo				= 	"你还在等什么？快去守边"
x300860_g_MissionCompleted			= 	"守边完成"
x300860_g_MissionHelp				=	"  #W任务期间死亡，离线或超时，任务自动置成失败状态，找明安重新领取。"          --任务提示信息

--目标
x300860_g_ExtTarget					=	{ {type=20,n=1,target="守边"}}

--奖励

x300860_g_ExpBonus					= 	0;--x300860_AddExpAward               	--奖励：经验
x300860_g_BonusItem					=	{}	--奖励：物品

x300860_g_BonusMoney1               = 	0
x300860_g_BonusMoney2               =   0
x300860_g_BonusMoney3               =   0

x300860_g_BonusChoiceItem           =   {}


--MisDescEnd

x300860_g_Mission_Id				=	7569

x300860_g_DayCountLimited			=	3
x300860_g_BuffId					=	7765		


function x300860_GetMissionId( sceneId, selfId )
	return x300860_g_Mission_Id
end

function x300860_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	
	local level = GetLevel( sceneId,selfId )
    if level < x300860_g_LevelLess then
       return
    end

	local myMissionId = x300860_GetMissionId( sceneId, selfId )
	
	
	
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) == 0 then
		
		AddQuestNumText(sceneId, myMissionId, x300860_g_MissionName,8,1);
	else
		local state = GetQuestStateNM(sceneId, selfId, targetId, myMissionId);

		
		AddQuestNumText(sceneId, myMissionId, x300860_g_MissionName,state,state);

	end


	
end


---------------------------------------------------------------------------------------------------
--向客户端发送任务未完成
---------------------------------------------------------------------------------------------------
function x300860_ProcEventEntry( sceneId, selfId, targetId, MissionId, nExt )
	local myMissionId = x300860_GetMissionId( sceneId, selfId )	
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) == 0 then
		x300860_DispatchMissionInfo( sceneId, selfId, targetId, myMissionId, 0 )
	else
		if nExt==7 then -- 任务完成
			x300860_DispatchCompletedInfo( sceneId, selfId, targetId,myMissionId )
		
		else
			
			x300860_DispatchContinueInfo( sceneId, selfId, targetId,myMissionId )
		end
	end
end


function x300860_ProcAcceptCheck(sceneId, selfId, targetId, MissionId )

	return 1;

end

function x300860_CheckRequest(sceneId, selfId)
	local myMissionId = x300860_GetMissionId( sceneId, selfId )

	if GetLevel(sceneId, selfId) <x300860_g_LevelLess then
		x300860_ShowTips(sceneId, selfId, "你等级不足")
		return 0
	end

	if IsHaveQuestNM( sceneId, selfId, myMissionId ) > 0 then
		x300860_ShowTips(sceneId, selfId, "你已经有这个任务，接受任务失败")
		return 0;
	end

	if x300860_g_DayCountLimited >0 then
		local nDayCount = x300860_GetDayCount(sceneId, selfId)
		if nDayCount>= x300860_g_DayCountLimited then
			x300860_ShowTips(sceneId, selfId, "很抱歉，您已经接取过了【国家】国家守边任务3次，请明日再来接！")
			return 0;
		end
	end

	return 1;

end

function x300860_ProcQuestAccept(sceneId, selfId, targetId, MissionId)
	
	
	if x300860_CheckRequest(sceneId, selfId)<=0 then
		
		return 0;
	end

	local myMissionId = x300860_GetMissionId( sceneId, selfId )

	--------------------------- add for Mission full check --------------
	local bFullMission = IsQuestFullNM(sceneId,selfId)
	
	if bFullMission>0 then
		x300860_ShowTips(sceneId, selfId, "任务已满，无法接受任务")
		return 0
	end
	---------------------------- add end -------------------------------
	
	--检查前置任务
	local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId, myMissionId )
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

	local ret = AddQuestNM( sceneId, selfId, myMissionId ) -- 给玩家添加任务		
		
	if ret > 0 then
		local str = "您接受了任务:【国家】国家守边";
		x300860_ShowTips(sceneId, selfId, str)
		Msg2Player(sceneId,selfId,str,8,2)

		local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )
		SetQuestByIndex( sceneId, selfId, misIndex, 5, 0 ) --Tick=0

		--CancelSpecificImpact( sceneId, selfId, x300860_g_BuffId)
		SendSpecificImpactToUnit(sceneId, selfId,selfId,selfId, x300860_g_BuffId,0 )

		
		return 1
	else
		
		x300860_ShowTips(sceneId, selfId, "接受任务错误")
	
	end


end

function x300860_ShowTips(sceneId, selfId, str)
	BeginQuestEvent(sceneId);
		AddQuestText(sceneId,str);
	EndQuestEvent();
	DispatchQuestTips(sceneId, selfId);
end

function x300860_ProcQuestAbandon( sceneId, selfId, MissionId )

	local myMissionId = x300860_GetMissionId( sceneId, selfId )
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) <= 0 then	-- 如果有这个任务直接退出
		return 0
	end

	local ret = DelQuestNM( sceneId, selfId, myMissionId )

	if ret>0 then

		local str = "您放弃了任务:【国家】国家守边"
	    x300860_ShowTips(sceneId, selfId, str)
		Msg2Player(sceneId,selfId,str,8,2)

		CancelSpecificImpact(sceneId, selfId, x300860_g_BuffId);
		x300860_SetDayCount(sceneId, selfId)
	else
		x300860_ShowTips(sceneId, selfId, "放弃任务失败")
	end

	
end



function x300860_ProcQuestSubmit( sceneId, selfId, targetId, selectId, MissionId )

	local myMissionId = x300860_GetMissionId( sceneId, selfId )
	
	if x300860_CheckSubmit(sceneId, selfId )>0 then
		
		local ret = DelQuestNM( sceneId, selfId, myMissionId )

		if ret>0 then

			local str = "您完成了任务:【国家】国家守边";
			x300860_ShowTips(sceneId, selfId, str)
			Msg2Player(sceneId,selfId,str,8,2)

			x300860_GiveReward(sceneId,selfId)

			
			x300860_SetDayCount(sceneId, selfId)
			x300860_SetSuccessCount(sceneId, selfId)

			CancelSpecificImpact( sceneId, selfId, x300860_g_BuffId)
			
		else
			x300860_ShowTips(sceneId, selfId, "交任务失败")
		end
		
	end
end

function x300860_GiveReward(sceneId,selfId)
	--奖励经验
	local level = GetLevel(sceneId, selfId)
	local ExpBonus1 = level*15000;
	local ExpBonus2 = level*15000;
	local ExpBonus = 0;
	if GetLevel(sceneId, selfId) >=30 and GetLevel(sceneId, selfId) < 70 then
			ExpBonus = ExpBonus1;
	elseif GetLevel(sceneId, selfId) >=70 then
			ExpBonus = ExpBonus2;
	end 
	local nDayCount = x300860_GetDayCount(sceneId, selfId)
    if nDayCount == 0 then
		local nExpBonus = floor(ExpBonus*0.15*0.3)
		AddExp(sceneId, selfId, nExpBonus);
		AddHonor(sceneId, selfId, 15);
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, "#o获得#R经验"..nExpBonus.."点#o的奖励");
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, "#o获得#R荣誉15点#o的奖励");
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
		local Readme = "#o获得#R经验"..nExpBonus.."点#o的奖励#r#o获得#R荣誉15点#o的奖励"
  		Msg2Player(sceneId,selfId,Readme,4,2)
			if GetLevel(sceneId, selfId) >=80 then
				local tf = 180
				local refixtf = AddInherenceExp( sceneId, selfId, tf)
				Msg2Player( sceneId, selfId, format( "获得#R天赋%s点#o的奖励。", refixtf), 4, 2)
				BeginQuestEvent(sceneId);
				AddQuestText(sceneId, "#o获得#R天赋"..refixtf.."点#o的奖励");
				EndQuestEvent();
				DispatchQuestTips(sceneId, selfId);
			end
		local ret = CountryIsFortuneTime(sceneId,selfId,0)
		if ret == 1 then
			AddExp(sceneId, selfId, nExpBonus);
			--AddHonor(sceneId, selfId, 15);
			BeginQuestEvent(sceneId);
			AddQuestText(sceneId, "#o国运令额外获得#R经验"..nExpBonus.."点#o的奖励");
			EndQuestEvent();
			DispatchQuestTips(sceneId, selfId);
			--BeginQuestEvent(sceneId);
			--AddQuestText(sceneId, "#o额外获得#R荣誉15点#o的奖励");
			--EndQuestEvent();
			--DispatchQuestTips(sceneId, selfId);
			Msg2Player(sceneId,selfId,"#o国运令额外获得#R经验"..nExpBonus.."点#o的奖励",4,2)--#r#o额外获得#R荣誉15点#o的奖励",4,2)
			if GetLevel(sceneId, selfId) >=80 then
				local tf = 180
				local refixtf = AddInherenceExp( sceneId, selfId, tf)
				Msg2Player( sceneId, selfId, format( "国运令额外获得天赋#R%s点#o的奖励。", refixtf), 4, 2)
				BeginQuestEvent(sceneId);
				AddQuestText(sceneId, "#o国运令额外获得#R天赋"..refixtf.."点#o的奖励");
				EndQuestEvent();
				DispatchQuestTips(sceneId, selfId);
			end
			-- local selfGuildId = GetGuildID(sceneId, selfId)
			-- local countryGuildId = GetCountryKingGuildId(sceneId, selfId)
			
			-- if selfGuildId ~= -1 and countryGuildId == selfGuildId then
				-- AddExploit(sceneId,selfId,2)
				-- BeginQuestEvent(sceneId);
				-- AddQuestText(sceneId, "#o获得#R功勋2点#o的奖励");
				-- EndQuestEvent();
				-- DispatchQuestTips(sceneId, selfId);	
				-- Msg2Player(sceneId,selfId,"#o获得#R功勋2点#o的奖励",4,2)
			-- end
			
		end
	elseif nDayCount == 1 then
		local nExpBonus = floor(ExpBonus*0.5*0.3)
		AddExp(sceneId, selfId, nExpBonus);
		AddHonor(sceneId, selfId, 35);
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, "#o获得#R经验"..nExpBonus.."点#o的奖励");
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, "#o获得#R荣誉35点#o的奖励");
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
		local Readme = "#o获得#R经验"..nExpBonus.."点#o的奖励#r#o获得#R荣誉35点#o的奖励"
  		Msg2Player(sceneId,selfId,Readme,4,2)
			if GetLevel(sceneId, selfId) >=80 then
				local tf = 180
				local refixtf = AddInherenceExp( sceneId, selfId, tf)
				Msg2Player( sceneId, selfId, format( "获得#R天赋%s点#o的奖励。", refixtf), 4, 2)
				BeginQuestEvent(sceneId);
				AddQuestText(sceneId, "#o获得#R天赋"..refixtf.."点#o的奖励");
				EndQuestEvent();
				DispatchQuestTips(sceneId, selfId);
			end
		local ret = CountryIsFortuneTime(sceneId,selfId,0)
		if ret == 1 then
			AddExp(sceneId, selfId, nExpBonus);
			--AddHonor(sceneId, selfId, 35);
			BeginQuestEvent(sceneId);
			AddQuestText(sceneId, "#o国运令额外获得#R经验"..nExpBonus.."点#o的奖励");
			EndQuestEvent();
			DispatchQuestTips(sceneId, selfId);
			--BeginQuestEvent(sceneId);
			--AddQuestText(sceneId, "#o额外获得#R荣誉35点#o的奖励");
			--EndQuestEvent();
			--DispatchQuestTips(sceneId, selfId);
			Msg2Player(sceneId,selfId,"#o国运令额外获得#R经验"..nExpBonus.."点#o的奖励",4,2)--#r#o额外获得#R荣誉35点#o的奖励",4,2)
			if GetLevel(sceneId, selfId) >=80 then
				local tf = 180
				local refixtf = AddInherenceExp( sceneId, selfId, tf)
				Msg2Player( sceneId, selfId, format( "国运令额外获得天赋#R%s点#o的奖励。", refixtf), 4, 2)
				BeginQuestEvent(sceneId);
				AddQuestText(sceneId, "#o国运令额外获得#R天赋"..refixtf.."点#o的奖励");
				EndQuestEvent();
				DispatchQuestTips(sceneId, selfId);
			end			
			-- local selfGuildId = GetGuildID(sceneId, selfId)
			-- local countryGuildId = GetCountryKingGuildId(sceneId, selfId)
			
			-- if selfGuildId ~= -1 and countryGuildId == selfGuildId then
				-- AddExploit(sceneId,selfId,2)
				-- BeginQuestEvent(sceneId);
				-- AddQuestText(sceneId, "#o获得#R功勋2点#o的奖励");
				-- EndQuestEvent();
				-- DispatchQuestTips(sceneId, selfId);	
				-- Msg2Player(sceneId,selfId,"#o获得#R功勋2点#o的奖励",4,2)			
			-- end
		end
	elseif nDayCount == 2 then
		local nExpBonus = floor(ExpBonus*0.5*0.7)
		AddExp(sceneId, selfId, nExpBonus);
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, "#o获得#R经验"..nExpBonus.."点#o的奖励");
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
		
		local nExpBonus1 = 0

		
		--write log
		local msg = "guojiashoubian: name="..GetName(sceneId, selfId)..",guid="..GetPlayerGUID( sceneId,selfId )..",nSuccssCount="..x300860_GetSuccessCount(sceneId, selfId)

		WriteLog(1,msg)
		--write end


		if x300860_GetSuccessCount(sceneId, selfId)>=2 then
			nExpBonus1 = floor(ExpBonus*0.05)
			AddExp(sceneId, selfId, nExpBonus1);
			BeginQuestEvent(sceneId);
			AddQuestText(sceneId, "#o额外获得#R经验"..nExpBonus1.."点#o的奖励");
			EndQuestEvent();
			DispatchQuestTips(sceneId, selfId);
		end

		AddHonor(sceneId, selfId, 50);
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, "#o获得#R荣誉50点#o的奖励");
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
		local Readme = ""
		if nExpBonus1==0 then
			Readme = "#o获得#R经验"..nExpBonus.."点#o的奖励#r#o获得#R荣誉50点#o的奖励"
		else
			Readme = "#o获得#R经验"..nExpBonus.."点#o的奖励#r#o获得#R荣誉50点#o的奖励#r额外获得#R经验"..nExpBonus1.."点#o的奖励"
  		
		end
		Msg2Player(sceneId,selfId,Readme,4,2)
			if GetLevel(sceneId, selfId) >=80 then
				local tf = 180
				local refixtf = AddInherenceExp( sceneId, selfId, tf)
				Msg2Player( sceneId, selfId, format( "获得#R天赋%s点#o的奖励。", refixtf), 4, 2)
				BeginQuestEvent(sceneId);
				AddQuestText(sceneId, "#o获得#R天赋"..refixtf.."点#o的奖励");
				EndQuestEvent();
				DispatchQuestTips(sceneId, selfId);
			end
		local ret = CountryIsFortuneTime(sceneId,selfId,0)
		
		if ret == 1 then
			AddExp(sceneId, selfId, nExpBonus);
			--AddExp(sceneId, selfId, nExpBonus1);
			nExpBonus1 = 0;
			if x300860_GetSuccessCount(sceneId, selfId)>=2 then
				nExpBonus1 = floor(ExpBonus*0.05)
				AddExp(sceneId, selfId, nExpBonus1);
				BeginQuestEvent(sceneId);
				AddQuestText(sceneId, "#o国运令额外获得#R经验"..nExpBonus1.."点#o的奖励");
				EndQuestEvent();
				DispatchQuestTips(sceneId, selfId);
			end

			--AddHonor(sceneId, selfId, 50);
			BeginQuestEvent(sceneId);
			AddQuestText(sceneId, "#o国运令额外获得#R经验"..nExpBonus.."点#o的奖励");
			EndQuestEvent();
			DispatchQuestTips(sceneId, selfId);
			
			--BeginQuestEvent(sceneId);
			--AddQuestText(sceneId, "#o额外获得#R荣誉50点#o的奖励");
			--EndQuestEvent();
			--DispatchQuestTips(sceneId, selfId);

			if nExpBonus1==0 then
				Msg2Player(sceneId,selfId,"#o国运令额外获得#R经验"..nExpBonus.."点#o的奖励#o",4,2)--#r#o额外获得#R荣誉50点#o的奖励",4,2)
			else
				Msg2Player(sceneId,selfId,"#o国运令额外获得#R经验"..nExpBonus.."点#o的奖励#o#r国运令额外获得#R经验"..nExpBonus1.."点#o的奖励",4,2)--#r#o额外获得#R荣誉50点#o的奖励",4,2)
			end
			if GetLevel(sceneId, selfId) >=80 then
				local tf = 180
				local refixtf = AddInherenceExp( sceneId, selfId, tf)
				Msg2Player( sceneId, selfId, format( "国运令额外获得天赋#R%s点#o的奖励。", refixtf), 4, 2)
				BeginQuestEvent(sceneId);
				AddQuestText(sceneId, "#o国运令额外获得#R天赋"..refixtf.."点#o的奖励");
				EndQuestEvent();
				DispatchQuestTips(sceneId, selfId);
			end
			-- local selfGuildId = GetGuildID(sceneId, selfId)
			-- local countryGuildId = GetCountryKingGuildId(sceneId, selfId)
			
			-- if selfGuildId ~= -1 and countryGuildId == selfGuildId then
				-- AddExploit(sceneId,selfId,2)
				-- BeginQuestEvent(sceneId);
				-- AddQuestText(sceneId, "#o获得#R功勋2点#o的奖励");
				-- EndQuestEvent();
				-- DispatchQuestTips(sceneId, selfId);	
				-- Msg2Player(sceneId,selfId,"#o获得#R功勋2点#o的奖励",4,2)
			-- end
			
		end
	end
end



function x300860_CheckSubmit(sceneId, selfId )
	local myMissionId = x300860_GetMissionId( sceneId, selfId )
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) <= 0 then	-- 如果有这个任务直接退出
		return 0
	end

	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )
	local bCompleted = GetQuestParam( sceneId, selfId, misIndex, 7 )

	if bCompleted<=0 then
		return 0
	end

	return 1;
end








---------------------------------------------------------------------------------------------------
--取得当前次数
---------------------------------------------------------------------------------------------------
function x300860_GetDayCount(sceneId, selfId)



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
function x300860_SetDayCount(sceneId, selfId)

	local today = GetDayOfYear()

	local lastday = GetQuestData(sceneId, selfId, DQ_SHOUBIAN_DATE[1], DQ_SHOUBIAN_DATE[2], DQ_SHOUBIAN_DATE[3])

	if lastday ~= today then
		SetQuestData(sceneId, selfId, DQ_SHOUBIAN_DATE[1], DQ_SHOUBIAN_DATE[2], DQ_SHOUBIAN_DATE[3], today)
		SetQuestData(sceneId, selfId, DQ_SHOUBIAN_DAYCOUNT[1], DQ_SHOUBIAN_DAYCOUNT[2], DQ_SHOUBIAN_DAYCOUNT[3], 1)
		SetQuestData(sceneId, selfId, DQ_SHOUBIAN_COUNT[1], DQ_SHOUBIAN_COUNT[2], DQ_SHOUBIAN_COUNT[3], 0)
	else
		local daycount = GetQuestData(sceneId, selfId, DQ_SHOUBIAN_DAYCOUNT[1], DQ_SHOUBIAN_DAYCOUNT[2], DQ_SHOUBIAN_DAYCOUNT[3])
		SetQuestData(sceneId, selfId, DQ_SHOUBIAN_DAYCOUNT[1], DQ_SHOUBIAN_DAYCOUNT[2], DQ_SHOUBIAN_DAYCOUNT[3], daycount+1)
	end
	
	
	
end


---------------------------------------------------------------------------------------------------
--取得当前成功次数
---------------------------------------------------------------------------------------------------
function x300860_GetSuccessCount(sceneId, selfId)



	local today = GetDayOfYear()
	local lastday = GetQuestData(sceneId, selfId, DQ_SHOUBIAN_DATE[1], DQ_SHOUBIAN_DATE[2],DQ_SHOUBIAN_DATE[3] );
	
	if lastday ~= today then
		return 0
	end

	local nCount = GetQuestData(sceneId, selfId, DQ_SHOUBIAN_COUNT[1], DQ_SHOUBIAN_COUNT[2],DQ_SHOUBIAN_COUNT[3] );
	return nCount;



	

end

---------------------------------------------------------------------------------------------------
--设置当天成功次数
---------------------------------------------------------------------------------------------------
function x300860_SetSuccessCount(sceneId, selfId)

	local today = GetDayOfYear()

	local lastday = GetQuestData(sceneId, selfId, DQ_SHOUBIAN_DATE[1], DQ_SHOUBIAN_DATE[2], DQ_SHOUBIAN_DATE[3])

	if lastday ~= today then
		--SetQuestData(sceneId, selfId, DQ_SHOUBIAN_DATE[1], DQ_SHOUBIAN_DATE[2], DQ_SHOUBIAN_DATE[3], today)
		SetQuestData(sceneId, selfId, DQ_SHOUBIAN_COUNT[1], DQ_SHOUBIAN_COUNT[2], DQ_SHOUBIAN_COUNT[3], 1)
	else
		local nCount = GetQuestData(sceneId, selfId, DQ_SHOUBIAN_COUNT[1], DQ_SHOUBIAN_COUNT[2], DQ_SHOUBIAN_COUNT[3])
		SetQuestData(sceneId, selfId, DQ_SHOUBIAN_COUNT[1], DQ_SHOUBIAN_COUNT[2], DQ_SHOUBIAN_COUNT[3], nCount+1)
	end
	
	
	
end


---------------------------------------------------------------------------------------------------
--向客户端发送任务信息
---------------------------------------------------------------------------------------------------
function x300860_DispatchMissionInfo( sceneId, selfId, NPCId, MissionId, nExt )

	
	
	BeginQuestEvent(sceneId)

		
	local nDayCount = x300860_GetDayCount(sceneId, selfId)
	--任务信息
	AddQuestText(sceneId,"#Y".."【国家】国家守边")
	AddQuestText(sceneId,"  我国正面临敌国严重的骚扰和威胁，需要大家共同出力，守卫边塞。你愿意接受此任务，守卫边塞一段时间吗？")
	AddQuestText(sceneId," ")

	--任务目标
	AddQuestText( sceneId,"#Y任务目标：")
	AddQuestText( sceneId,"  您接受任务后，守卫边塞，在@npc_128511附近守卫，每隔一段时间，会自动获得经验奖励。经过一段时间即可向我汇报军情，并完成任务得到奖励，当达到80级时可获得天赋值奖励。")
	AddQuestText( sceneId," ")

	if nDayCount == 0 then
		local localexp1 = (GetLevel( sceneId, selfId )) * 15000*0.15*0.3
		local localexp2 = (GetLevel( sceneId, selfId )) * 15000*0.15*0.3
		local localexp = 0
		if GetLevel(sceneId, selfId) >=30 and GetLevel(sceneId, selfId) < 70 then
			localexp = localexp1;
		elseif GetLevel(sceneId, selfId) >=70 then
			localexp = localexp2;
		end 
		if GetLevel(sceneId, selfId) >=80 then
			AddQuestText(sceneId,"#Y任务奖励：")
			AddQuestText(sceneId,"  经验值："..floor(localexp).."点#r  荣誉值：15点#r  天赋值：180点")
			AddQuestText(sceneId," ")	
		else
		AddQuestText(sceneId,"#Y任务奖励：")
		AddQuestText(sceneId,"  经验值："..floor(localexp).."点#r  荣誉值：15点")
		AddQuestText(sceneId," ")
		end	
	elseif nDayCount == 1 then	
		local localexp1 = (GetLevel( sceneId, selfId )) * 15000* 0.3*0.5
		local localexp2 = (GetLevel( sceneId, selfId )) * 15000* 0.3*0.5
		local localexp = 0
		if GetLevel(sceneId, selfId) >=30 and GetLevel(sceneId, selfId) < 70 then
			localexp = localexp1;
		elseif GetLevel(sceneId, selfId) >=70 then
			localexp = localexp2;
		end 
		if GetLevel(sceneId, selfId) >=80 then
			AddQuestText(sceneId,"#Y任务奖励：")
			AddQuestText(sceneId,"  经验值："..floor(localexp).."点#r  荣誉值：35点#r  天赋值：180点")
			AddQuestText(sceneId," ")	
		else
		AddQuestText(sceneId,"#Y任务奖励：")
		AddQuestText(sceneId,"  经验值："..floor(localexp).."点#r  荣誉值：35点")
		AddQuestText(sceneId," ")
		end	
	elseif nDayCount == 2 then
		local localexp1 = (GetLevel( sceneId, selfId )) * 15000*0.5*0.7
		local localexp2 = (GetLevel( sceneId, selfId )) * 15000*0.5*0.7
		local localexp = 0
		if GetLevel(sceneId, selfId) >=30 and GetLevel(sceneId, selfId) < 70 then
			localexp = localexp1;
		elseif GetLevel(sceneId, selfId) >=70 then
			localexp = localexp2;
		end 
		if GetLevel(sceneId, selfId) >=80 then
			AddQuestText(sceneId,"#Y任务奖励：")
			AddQuestText(sceneId,"  经验值："..floor(localexp).."点#r  荣誉值：50点#r  天赋值：180点")
			AddQuestText(sceneId," ")	
		else
		AddQuestText(sceneId,"#Y任务奖励：")
		AddQuestText(sceneId,"  经验值："..floor(localexp).."点#r  荣誉值：50点")
		AddQuestText(sceneId," ")
		end	
	end
		
		

	EndQuestEvent()
	
	DispatchQuestInfoNM(sceneId, selfId, NPCId, x300860_g_ScriptId, MissionId,0);
end


---------------------------------------------------------------------------------------------------
--向客户端发送任务未完成
---------------------------------------------------------------------------------------------------
function x300860_DispatchContinueInfo( sceneId, selfId, NPCId,MissionId )

	BeginQuestEvent(sceneId)
		local nDayCount = x300860_GetDayCount(sceneId, selfId)
		AddQuestText(sceneId,"#Y【国家】国家守边#r")

		AddQuestText( sceneId,"  国家守边时间未到，快去守卫边塞！#r")
	
		AddQuestText(sceneId,"#Y任务小提示：")
		AddQuestText(sceneId,"  在@npc_128511附近守卫，每隔一段时间，会自动获得经验奖励。#r")
		if nDayCount == 0 then
			local localexp1 = (GetLevel( sceneId, selfId ))* 15000 *0.15*0.3
			local localexp2 = (GetLevel( sceneId, selfId ))* 15000 *0.15*0.3
			local localexp = 0
			if GetLevel(sceneId, selfId) >=30 and GetLevel(sceneId, selfId) < 70 then
				localexp = localexp1;
			elseif GetLevel(sceneId, selfId) >=70 then
				localexp = localexp2;
			end 
			if GetLevel(sceneId, selfId) >=80 then
				AddQuestText(sceneId,"#Y任务奖励：")
				AddQuestText(sceneId,"  经验值："..floor(localexp).."点#r  荣誉值：15点#r  天赋值：180点")
				AddQuestText(sceneId," ")	
			else
				AddQuestText(sceneId,"#Y任务奖励：")
				AddQuestText(sceneId,"  经验值："..floor(localexp).."点#r  荣誉值：15点")
				AddQuestText(sceneId," ")
			end	
			elseif nDayCount == 1 then	
			local localexp1 = (GetLevel( sceneId, selfId )) * 15000*0.3*0.5
			local localexp2 = (GetLevel( sceneId, selfId )) * 15000*0.3*0.5
			local localexp = 0
			if GetLevel(sceneId, selfId) >=30 and GetLevel(sceneId, selfId) < 70 then
				localexp = localexp1;
			elseif GetLevel(sceneId, selfId) >=70 then
				localexp = localexp2;
			end 
			if GetLevel(sceneId, selfId) >=80 then
				AddQuestText(sceneId,"#Y任务奖励：")
				AddQuestText(sceneId,"  经验值："..floor(localexp).."点#r  荣誉值：35点#r  天赋值：180点")
				AddQuestText(sceneId," ")	
			else
				AddQuestText(sceneId,"#Y任务奖励：")
				AddQuestText(sceneId,"  经验值："..floor(localexp).."点#r  荣誉值：35点")
				AddQuestText(sceneId," ")
			end	
			
			elseif nDayCount == 2 then
			local localexp1 = (GetLevel( sceneId, selfId ))* 15000*0.5*0.7
			local localexp2 = (GetLevel( sceneId, selfId ))* 15000*0.5*0.7
			local localexp = 0
			if GetLevel(sceneId, selfId) >=30 and GetLevel(sceneId, selfId) < 70 then
				localexp = localexp1;
			elseif GetLevel(sceneId, selfId) >=70 then
				localexp = localexp2;
			end 
			if GetLevel(sceneId, selfId) >=80 then
				AddQuestText(sceneId,"#Y任务奖励：")
				AddQuestText(sceneId,"  经验值："..floor(localexp).."点#r  荣誉值：50点#r  天赋值：180点")
				AddQuestText(sceneId," ")	
			else
				AddQuestText(sceneId,"#Y任务奖励：")
				AddQuestText(sceneId,"  经验值："..floor(localexp).."点#r  荣誉值：50点")
				AddQuestText(sceneId," ")
			end	
				
			
			end
		

	EndQuestEvent()
	DispatchQuestDemandInfo(sceneId, selfId, NPCId, x300860_g_ScriptId, MissionId,0);
	


end

---------------------------------------------------------------------------------------------------
--向客户端发送任务完成信息
---------------------------------------------------------------------------------------------------
function x300860_DispatchCompletedInfo( sceneId, selfId, NPCId,MissionId )
	

	BeginQuestEvent(sceneId)
		local nDayCount = x300860_GetDayCount(sceneId, selfId)
		--任务信息
		AddQuestText(sceneId,"#Y【国家】国家守边")
		AddQuestText(sceneId,"  好的，非常感谢，由于您协助防守边塞，我们的边塞稳定许多。")
		if nDayCount == 0 then
			local localexp1 = (GetLevel( sceneId, selfId )) * 15000*0.15*0.3
			local localexp2 = (GetLevel( sceneId, selfId )) * 15000*0.15*0.3
			local localexp = 0
			if GetLevel(sceneId, selfId) >=30 and GetLevel(sceneId, selfId) < 70 then
				localexp = localexp1;
			elseif GetLevel(sceneId, selfId) >=70 then
				localexp = localexp2;
			end 
			if GetLevel(sceneId, selfId) >=80 then
				AddQuestText(sceneId,"#Y任务奖励：")
				AddQuestText(sceneId,"  经验值："..floor(localexp).."点#r  荣誉值：15点#r  天赋值：180点")
				AddQuestText(sceneId," ")	
			else
			AddQuestText(sceneId,"#Y任务奖励：")
			AddQuestText(sceneId,"  经验值："..floor(localexp).."点#r  荣誉值：15点")
			AddQuestText(sceneId," ")
			end	
	
		elseif nDayCount == 1 then	
			local localexp1 = (GetLevel( sceneId, selfId )) * 15000* 0.3*0.5
			local localexp2 = (GetLevel( sceneId, selfId )) * 15000* 0.3*0.5
			local localexp = 0
			if GetLevel(sceneId, selfId) >=30 and GetLevel(sceneId, selfId) < 70 then
				localexp = localexp1;
			elseif GetLevel(sceneId, selfId) >=70 then
				localexp = localexp2;
			end 
			if GetLevel(sceneId, selfId) >=80 then
				AddQuestText(sceneId,"#Y任务奖励：")
				AddQuestText(sceneId,"  经验值："..floor(localexp).."点#r  荣誉值：35点#r  天赋值：180点")
				AddQuestText(sceneId," ")	
			else
			AddQuestText(sceneId,"#Y任务奖励：")
			AddQuestText(sceneId,"  经验值："..floor(localexp).."点#r  荣誉值：35点")
			AddQuestText(sceneId," ")
			end	
	
		elseif nDayCount == 2 then
			local localexp1 = (GetLevel( sceneId, selfId )) * 15000*0.5*0.7
			local localexp2 = (GetLevel( sceneId, selfId )) * 15000*0.5*0.7
			local localexp = 0
			if GetLevel(sceneId, selfId) >=30 and GetLevel(sceneId, selfId) < 70 then
				localexp = localexp1;
			elseif GetLevel(sceneId, selfId) >=70 then
				localexp = localexp2;
			end
			if GetLevel(sceneId, selfId) >=80 then
				AddQuestText(sceneId,"#Y任务奖励：")
				AddQuestText(sceneId,"  经验值："..floor(localexp).."点#r  荣誉值：50点#r  天赋值：180点")
				AddQuestText(sceneId," ")	
			else
			AddQuestText(sceneId,"#Y任务奖励：")
			AddQuestText(sceneId,"  经验值："..floor(localexp).."点#r  荣誉值：50点")
			AddQuestText(sceneId," ")
			end	
		
	
	end

		--任务目标
		--AddQuestText( sceneId,"#Y任务目标：")
		--AddQuestText( sceneId,"完成提示bbbbbbb")
		--AddQuestText( sceneId," ")

		--AddQuestText(sceneId,"#Y任务提示：")
		--AddQuestText(sceneId,"完成ccccccc" )
		--AddQuestText(sceneId," ")
		
		
	EndQuestEvent()
	DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x300860_g_ScriptId, MissionId);
	CallScriptFunction( 256289, "FinishShoubian", sceneId, selfId)
end





---------------------------------------------------------------------------------------------------
--任务日志刷新
---------------------------------------------------------------------------------------------------
function x300860_QuestLogRefresh( sceneId, selfId, MissionId)
	local ret = x300860_CheckSubmit(sceneId, selfId )
	local str=""
	if ret==1 then
		str = "守边(1/1)"
	else
		str= "守边(0/1)"
	end
	
		
	BeginQuestEvent(sceneId)	
			local level = GetLevel(sceneId, selfId)
			local nExpBonus1 = level*15000
			local nExpBonus2 = level*15000
			local nExpBonus = 0
			if GetLevel(sceneId, selfId) >=30 and GetLevel(sceneId, selfId) < 70 then
				nExpBonus = nExpBonus1;
			elseif GetLevel(sceneId, selfId) >=70 then
				nExpBonus = nExpBonus2;
			end
			local nDayCount = x300860_GetDayCount(sceneId, selfId)
			if nDayCount == 0 then
				local level =GetLevel (sceneId,selfId)
				local ExpBonus = floor(nExpBonus *0.15*0.3)
				if level >=80 then
				AddQuestExpBonus(sceneId,  ExpBonus);
				AddQuestMoneyBonus6(sceneId, 15 )
					AddQuestInherenceExpBonus(sceneId,180)
				else
					AddQuestExpBonus(sceneId,  ExpBonus);
					AddQuestMoneyBonus6(sceneId, 15 )
				end
			elseif nDayCount == 1 then
				local level =GetLevel (sceneId,selfId)
				local ExpBonus = floor(nExpBonus *0.5*0.3)
				if level >=80 then
				AddQuestExpBonus(sceneId,  ExpBonus);
				AddQuestMoneyBonus6(sceneId, 35 )
					AddQuestInherenceExpBonus(sceneId,180)
				else
				AddQuestExpBonus(sceneId,  ExpBonus);
				AddQuestMoneyBonus6(sceneId, 35 )
				end
			elseif nDayCount == 2 then
				local ExpBonus = floor(nExpBonus *0.5*0.7)
				if level >=80 then
				AddQuestExpBonus(sceneId,  ExpBonus);
				AddQuestMoneyBonus6(sceneId, 50 )
					AddQuestInherenceExpBonus(sceneId,180)
				else
				AddQuestExpBonus(sceneId,  ExpBonus);
				AddQuestMoneyBonus6(sceneId, 50 )
			end		
			end		
		
	AddQuestLogCustomText( sceneId,
							"",						-- 标题
							"【国家】国家守边",        -- 任务名字
							"  驻守边塞10分钟",		--任务目标
							"@npc_128510",			--任务NPC
							"",               --任务攻略
							"  您接受任务后，守卫边塞，在@npc_128511附近守卫，每隔一段时间，会自动获得经验奖励。经过一段时间即可向@npc_128510汇报军情，并完成任务得到奖励，当达到80级时可获得天赋值奖励。",	--任务描述
							"  当您在国运令期间回复任务时，你将获得双倍的经验奖励！"					--任务小提示
							)
	EndQuestEvent()
	DispatchQuestLogUpdate(sceneId, selfId, MissionId);
	

end

function x300860_ProcQuestLogRefresh( sceneId, selfId, MissionId)
	
	x300860_QuestLogRefresh( sceneId, selfId, MissionId );
end

--// system function start
function x300860_ProcQuestAttach( sceneId, selfId, npcId, npcGuid,misIndex, MissionId )
	
	
end

function x300860_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end

function x300860_ProcessQuestFail(sceneId, selfId, MissionId)
end

function x300860_OnPlayerRelive(sceneId, selfId, nMode)
	
	local myMissionId = x300860_GetMissionId( sceneId, selfId )
	
	if IsHaveQuestNM(sceneId,selfId,myMissionId) <= 0 then
        return 
    end

	if nMode==nil then
		nMode =0
	end

	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )


	if nMode==0 then
		if IsPlayerStateNormal(sceneId,selfId )<=0 then
			return
		end
	end

	


	

	local bCompleted = GetQuestParam( sceneId, selfId, misIndex, 7 )

	if bCompleted<1  then   --如果任务没有完成
		
		if IsHaveSpecificImpact(sceneId, selfId, x300860_g_BuffId)<=0 then --如果没有buff,设置任务已经完成
		
			SetQuestByIndex( sceneId, selfId, misIndex, 0, 1 )  
			SetQuestByIndex( sceneId, selfId, misIndex, 7, 1 )  
			x300860_QuestLogRefresh( sceneId, selfId, myMissionId)
			
			local msg =GetName(sceneId, selfId).."guojiashoubian: relive and no buff and set to completed"..nMode
			WriteLog(1,msg)
			
		end
	else  --如果任务已完成
		--if IsHaveSpecificImpact(sceneId, selfId, x300860_g_BuffId)>0 then --如果还有这个buff, 说明有异常
		--
		--	SetQuestByIndex( sceneId, selfId, misIndex, 0, 0 )  
		--	SetQuestByIndex( sceneId, selfId, misIndex, 7, 0 )  
		--	x300860_QuestLogRefresh( sceneId, selfId, myMissionId)
		--	
		--end
	end
end

function x300860_OnPlayerLogin(sceneId, selfId)
	x300860_OnPlayerRelive(sceneId, selfId, 1)
end


--// system end




