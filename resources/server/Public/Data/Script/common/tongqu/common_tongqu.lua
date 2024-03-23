--童趣
x300320_g_ScriptId = 300320
x300320_g_RoundMax = 1
--x300320_g_MD_Round = MD_TONGQU_ROUND
x300320_g_CircleMax = 6
--x300320_g_MD_Circle = MD_TONGQU_CIRCLE
--x300320_g_MD_LastMissionType = MD_TONGQU_RAND
--x300320_g_MD_AcceptTime = MD_TONGQU_DATE
x300320_g_FirstMissionId = 8066
--x300320_g_LastMissionId = 5180
x300320_g_ReturnMissionId = 8074

x300320_g_Level = 40
--x300320_g_Obj_Issue = 139811
--x300320_g_Obj_Commit = 139810 

x300320_g_AcceptMessage		= "您接受了任务：%s"
x300320_g_AbandonMessage	= "您放弃了任务：%s"
x300320_g_CompleteMessage	= "您完成了任务：%s"

x300320_g_MissionList = {	{mission=8067, transX=115, transZ=123 }, 
							{mission=8068, transX=380, transZ=105 },
							{mission=8069, transX=435, transZ=242 },
							{mission=8070, transX=286, transZ=396 },
							{mission=8071, transX=434, transZ=372 },
							{mission=8072, transX=105, transZ=303 },
							{mission=8073, transX=187, transZ=289 }	}

x300320_g_ItemNeed1 = 13013500 --真视眼睛
x300320_g_ItemNeed2 = 13013501 --传送指环

x300320_g_MissionName="【循环】童趣"
x300320_g_MissionInfo="\t你怀念旧时童年趣事吗，你是否想回到童年，重新与儿时的玩伴一起玩耍？\n\t我听说大都内有一位巫师可以帮你实现愿望，可他却一般不会随意答应人的请求。但，作为他的好朋友，我也有些事情要拜托你到孩童年代去完成。\n\t如果你肯帮助我完成儿时的遗憾，你不仅可以回到儿时，重现儿时快乐，你还可以获得我的重谢。\n\t注：你可以在#G每日19：30~24：00#W找我接取任务。"  --任务描述
x300320_g_MissionHelp = ""
x300320_g_AwardItem = 12110204

x300320_g_ErrorMessage_Time	=	"请在每日19：30~24：00再来"


function x300320_SafeCheck( sceneId, selfId )
	local rounds = GetQuestData(sceneId, selfId, MD_TONGQU_ROUND[1], MD_TONGQU_ROUND[2], MD_TONGQU_ROUND[3])
	
	--local week = GetWeek()
	--if week ~= 0 then
		--local str = x300320_g_ErrorMessage_Time
		--BeginQuestEvent(sceneId);
		--AddQuestText(sceneId, str);
		--EndQuestEvent(sceneId);
		--DispatchQuestTips(sceneId,selfId);
		--Msg2Player(sceneId,selfId,str,8,2)
		--return -3
	--end
	--local year, month, day = GetYearMonthDay()
	--if day > 7 then
		--local str = x300320_g_ErrorMessage_Time
		--BeginQuestEvent(sceneId);
		--AddQuestText(sceneId, str);
		--EndQuestEvent(sceneId);
		--DispatchQuestTips(sceneId,selfId);
		--Msg2Player(sceneId,selfId,str,8,2)
		--return -3
	--end

	local minute = GetMinOfDay()
	if not (minute >= 19*60+30 and minute <24*60) then
		local str = x300320_g_ErrorMessage_Time
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, str);
		EndQuestEvent(sceneId);
		DispatchQuestTips(sceneId,selfId);
		Msg2Player(sceneId,selfId,str,8,2)
		return -4
	end

	if rounds >= x300320_g_RoundMax then
		local str = "你在今天已经参加过本活动，请等待下次活动时间再来"
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, str);
		EndQuestEvent(sceneId);
		DispatchQuestTips(sceneId,selfId);
		Msg2Player(sceneId,selfId,str,8,2)
		return -1
	end

	if GetLevel( sceneId, selfId ) < x300320_g_Level then
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, "你等级不足40");
		EndQuestEvent(sceneId);
		DispatchQuestTips(sceneId,selfId);
		Msg2Player(sceneId,selfId,"你等级不足40",8,2)
		return -2
	end

	return 1
end

function x300320_GetAfterMission( sceneId, selfId, lastMission, param1, param2, param3, param4)

	local circle = GetQuestData(sceneId, selfId, MD_TONGQU_CIRCLE[1], MD_TONGQU_CIRCLE[2], MD_TONGQU_CIRCLE[3])

	if circle == 4 then
		return x300320_g_ReturnMissionId
	else 
		--随机任务
		local mission = {}
		local num =0;

		for i, item in x300320_g_MissionList do 
			if item.mission ~= param1 and item.mission ~= param2 and item.mission ~= param3 and item.mission ~= param4 then
				num = num +1
				mission[num] = item.mission
			end
		end

		local rand = random(1,num)

		return mission[rand]
	end
end

function x300320_NextDayReset(sceneId, selfId)
	local day = GetQuestData(sceneId, selfId, MD_TONGQU_DATE[1], MD_TONGQU_DATE[2], MD_TONGQU_DATE[3])

	if day == GetDayOfYear() then
		return 
	end
	
	SetQuestData(sceneId, selfId, MD_TONGQU_ROUND[1], MD_TONGQU_ROUND[2], MD_TONGQU_ROUND[3], 0)
	SetQuestData(sceneId, selfId, MD_TONGQU_CIRCLE[1], MD_TONGQU_CIRCLE[2], MD_TONGQU_CIRCLE[3], 0)
end

function x300320_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

	if IsHaveQuestNM( sceneId, selfId, x300320_g_ReturnMissionId ) > 0 or IsHaveQuestNM( sceneId, selfId, MissionId ) > 0 then
		return 
	end

	if GetLevel( sceneId, selfId ) < x300320_g_Level then
		return 
	end

	if IsHaveQuestNM( sceneId, selfId, x300320_g_FirstMissionId ) > 0 then
		return
	end

	if IsHaveQuestNM( sceneId, selfId, x300320_g_ReturnMissionId ) > 0 then
		return
	end

	for i, item in x300320_g_MissionList do
		if IsHaveQuestNM( sceneId, selfId, item.mission ) > 0 then
			return 
		end
	end


	if IsHaveQuestNM( sceneId, selfId, MissionId ) == 0 then	-- 如果没有这个任务
		--if QuestCheckAcceptNM( sceneId, selfId, targetId, MissionId ) > 0 then
			local  missionState = GetQuestStateNM( sceneId, selfId, targetId, MissionId )
			AddQuestTextNM(sceneId, selfId, targetId, MissionId, missionState)
		--end
	end
	return 0
end

function x300320_DispatchFirstMissionInfo()
	
end
--选中任务
function x300320_ProcEventEntry( sceneId, selfId, targetId, MissionId )

	if IsHaveQuestNM( sceneId, selfId, MissionId ) == 0 then	-- 如果没有这个任务
		x300320_NextDayReset(sceneId, selfId)

		BeginQuestEvent(sceneId)
	  	AddQuestText(sceneId,"#Y"..x300320_g_MissionName)
			AddQuestText(sceneId,x300320_g_MissionInfo)
			if x300320_g_MissionHelp ~= "" then
				AddQuestText(sceneId,"\n#G小提示:#W")
				AddQuestText(sceneId,x300320_g_MissionHelp )
			end

			local level = GetLevel(sceneId, selfId)

			AddQuestExpBonus(sceneId, level*630 )
			
			AddQuestItemBonus(sceneId, x300320_g_AwardItem, 1)
			AddQuestMoneyBonus5(sceneId, 200 )
			
		
	  	EndQuestEvent()
			DispatchQuestInfoNM(sceneId, selfId, targetId, x300320_g_ScriptId, x300320_g_FirstMissionId);

	else --如果有这个任务
		local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )
		if QuestCheckSubmitNM( sceneId, selfId, targetId, MissionId, misIndex ) > 0 then -- 如果任务可以完成
			QuestComplateInfoNM( sceneId, selfId, targetId, MissionId ) -- 显示完成信息
			--DispatchQuestContinueInfoNM(sceneId, selfId, targetId, x300320_g_ScriptId, x256104_g_MissionId);
		else
			QuestNotComplateInfoNM( sceneId, selfId, targetId, MissionId ) -- 显示任务未完成信息
		end
	end
end

--接受任务
function x300320_ProcQuestAccept( sceneId, selfId, targetId, MissionId )
	
	for i, item in x300320_g_MissionList do
		if item.mission == MissionId then
			if IsHaveQuestNM( sceneId, selfId, MissionId ) > 0 then
				return
			end
		end
	end

	--如果该任务已经完成直接退出(跑环任务例外)
	if IsHaveQuestNM( sceneId, selfId, MissionId ) > 0 then	-- 如果有这个任务直接退出
		return 0
	end
	
	if IsHaveQuestNM(sceneId, selfId, 7537) > 0 or IsHaveQuestNM(sceneId, selfId, 7538) > 0 or IsHaveQuestNM(sceneId, selfId, 7539) > 0 
		or IsHaveQuestNM(sceneId, selfId, 7551) > 0 or IsHaveQuestNM(sceneId, selfId, 7552) > 0 then

		local strText = "你正在进行铁人三项比赛，无法接取任务"
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId, strText);
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return 0;
	end

	if x300320_SafeCheck( sceneId, selfId ) < 0 then
		return
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

			SetQuestData(sceneId, selfId, MD_TONGQU_ROUND[1], MD_TONGQU_ROUND[2], MD_TONGQU_ROUND[3], 1)
			SetQuestData(sceneId, selfId, MD_TONGQU_DATE[1], MD_TONGQU_DATE[2], MD_TONGQU_DATE[3], GetDayOfYear())

			local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )
			SetQuestByIndex( sceneId, selfId, misIndex, 5, GetLevel(sceneId, selfId) )
			SetQuestByIndex( sceneId, selfId, misIndex, 7, 1 )

			for i = 0, 4 do
				local SceneID, PosX, PosZ, tips = GetAskWayPosNM(sceneId, selfId, MissionId, i)
				if SceneID ~= -1 then
					CallScriptFunction( UTILITY_SCRIPT, "AskTheWayPos", sceneId, selfId, SceneID, PosX, PosZ, tips )
				end
			end
			
			local MissionName = GetQuestNameNM( sceneId, selfId, MissionId )
			local message = format(x300320_g_AcceptMessage, MissionName);
			local strText = message

			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, strText);
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
			Msg2Player(sceneId,selfId, strText, 4, 2)
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
	
	end
	
	return 0
end

--任务放弃
function x300320_ProcQuestAbandon( sceneId, selfId, MissionId )
	local ret = 0
	ret = DelQuestNM( sceneId, selfId, MissionId )
	if ret == 1 then
		local sex = GetSex( sceneId, selfId )
		if sex==0 then
			CancelSpecificImpact(sceneId, selfId, 7517)
			SendSpecificImpactToUnit(sceneId, selfId, selfId, selfId, 8314, 0)
		else
			CancelSpecificImpact(sceneId, selfId, 7516)
			SendSpecificImpactToUnit(sceneId, selfId, selfId, selfId, 8314, 0)
		end
		CancelSpecificImpact(sceneId, selfId,7534)
		ClearMutexState(sceneId, selfId, 21)

		--删除物品
		local ItemCnt = GetItemCount( sceneId, selfId, x300320_g_ItemNeed1 )
		if ItemCnt > 0 then 
			DelItem(sceneId, selfId,x300320_g_ItemNeed1, 1)
		end

		ItemCnt = GetItemCount( sceneId, selfId, x300320_g_ItemNeed2 )
		if ItemCnt > 0 then 
			DelItem(sceneId, selfId,x300320_g_ItemNeed2, 1)
		end

		local MissionName = GetQuestNameNM( sceneId, selfId, MissionId )
		local message = format(x300320_g_AbandonMessage, MissionName);
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, message);
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
		Msg2Player(sceneId,selfId, message, 4, 2)

		SetQuestData(sceneId, selfId, MD_TONGQU_DATE[1], MD_TONGQU_DATE[2], MD_TONGQU_DATE[3], GetDayOfYear())
	end
end

function x300320_ProcQuestAttach( sceneId, selfId, targetId, npcGuid, misIndex, MissionId )
	if IsHaveQuestNM( sceneId, selfId, MissionId ) == 0 then	-- 如果没有这个任务
		return
	end

	local npcName = GetName( sceneId, targetId )
	if npcName == "" then	--NPC名字会是空的么
		return
	end

	local guid = GetQuestSubmitNPCGUIDNM( sceneId, selfId, misIndex )
	local  missionState = GetQuestStateNM(sceneId, selfId, targetId, MissionId)
	if guid ~= -1 then --这个任务有完成的NPC
		if guid == npcGuid then	--点击的NPC的名字和任务中NPC的名字相同，场景也判断过了
			AddQuestTextNM( sceneId, selfId, targetId, MissionId, missionState, -1 ) -- 显示任务信息
		end
	else
		AddQuestTextNM( sceneId, selfId, targetId, MissionId, missionState, -1 ) -- 显示任务信息
	end
end

--完成任务
--返回1代表成功，0代表交任务失败
function x300320_ProcQuestSubmit( sceneId, selfId, targetId, selectId, MissionId )
	if IsHaveQuestNM( sceneId, selfId, MissionId ) == 0 then	-- 如果没这个任务直接退出
		return 0
	end

	if x300320_g_FirstMissionId == MissionId then
		if GetBagSpace(sceneId, selfId) < 2 then
			local message = "背包空间不足两格，无法继续此任务"
			BeginQuestEvent(sceneId);
				AddQuestText(sceneId, message);
			EndQuestEvent();
			DispatchQuestTips(sceneId, selfId);
			return
		end
	end

	if MissionId == x300320_g_ReturnMissionId then
		if GetBagSpace(sceneId, selfId) < 1 then
			local message = "背包已满，无法完成此任务"
			BeginQuestEvent(sceneId);
				AddQuestText(sceneId, message);
			EndQuestEvent();
			DispatchQuestTips(sceneId, selfId);
			return
		end
	end

	if IsHaveQuestNM(sceneId, selfId, 7537) > 0 or IsHaveQuestNM(sceneId, selfId, 7538) > 0 or IsHaveQuestNM(sceneId, selfId, 7539) > 0 
	or IsHaveQuestNM(sceneId, selfId, 7551) > 0 or IsHaveQuestNM(sceneId, selfId, 7552) > 0 then
		local strText = "你正在进行铁人三项比赛，无法继续此任务"
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId, strText);
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return 
	end



	local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )
	local ret = QuestCheckSubmitNM( sceneId, selfId, targetId, MissionId, misIndex ) -- 获取完成任务检查信息
	if ret > 0 then -- 如果可以完成
		return x300320_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	end
	return 0
end

--任务完成
function x300320_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )
	local param1 = GetQuestParam( sceneId, selfId, misIndex, 1 ) 
	local param2 = GetQuestParam( sceneId, selfId, misIndex, 2 ) 
	local param3 = GetQuestParam( sceneId, selfId, misIndex, 3 ) 
	local param4 = GetQuestParam( sceneId, selfId, misIndex, 4 ) 
	
	local ret = DelQuestNM( sceneId, selfId, MissionId ) -- 获取完成任务信息
	if ret >0 then -- 如果成功完成
		--提示玩家任务完成
		local MissionName = GetQuestNameNM( sceneId, selfId, MissionId )
		local message = format(x300320_g_CompleteMessage, MissionName);
		BeginQuestEvent(sceneId);
			AddQuestText(sceneId, message);
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);

		x300320_OnSubMissionComplete(sceneId, selfId, targetId, MissionId, param1, param2, param3, param4 )
				
		return 1 -- 返回成功
	end
	return 0
end

function x300320_OnSubMissionComplete(sceneId, selfId, targetId, MissionId, param1, param2, param3, param4)
	local level = GetLevel( sceneId, selfId )
	if MissionId == x300320_g_ReturnMissionId then
		local day = GetQuestData(sceneId, selfId, MD_TONGQU_DATE[1], MD_TONGQU_DATE[2], MD_TONGQU_DATE[3])
		if day ~= GetDayOfYear() then
			AddExp( sceneId, selfId, 630*level )
			local message = format("#Y获得#R经验%d点#Y奖励", 630*level)
			BeginQuestEvent(sceneId);
				AddQuestText(sceneId, message);
			EndQuestEvent();
			DispatchQuestTips(sceneId, selfId);
			Msg2Player(sceneId,selfId, message,4,2)

			local itemId=x300320_g_AwardItem;
			BeginAddItem( sceneId )
			AddItem( sceneId, itemId, 1 )
			local ret = EndAddItem( sceneId, selfId )
			if ret > 0 then
				AddItemListToPlayer(sceneId,selfId)

				local message = format("#Y获得物品#R#{_ITEM%d}#Y的奖励", x300320_g_AwardItem )
				BeginQuestEvent(sceneId);
				AddQuestText(sceneId, message);
				EndQuestEvent();
				DispatchQuestTips(sceneId, selfId);
				--Msg2Player(sceneId,selfId, message,4,2)
			else
				local strText = "背包已满,不能获得奖励物品"
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId, strText);
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
			end

			local nShengWang = GetShengWang( sceneId, selfId )
			nShengWang = nShengWang + 200
			SetShengWang( sceneId, selfId, nShengWang )
			message = format("获得声望%d的奖励。", 200)
			BeginQuestEvent(sceneId);
				AddQuestText(sceneId, message);
			EndQuestEvent();
			DispatchQuestTips(sceneId, selfId);
			Msg2Player(sceneId,selfId,message,4,2)

			SetQuestData(sceneId, selfId, MD_TONGQU_DATE[1], MD_TONGQU_DATE[2], MD_TONGQU_DATE[3], GetDayOfYear())
			return 
		end

		SetQuestData(sceneId, selfId, MD_TONGQU_DATE[1], MD_TONGQU_DATE[2], MD_TONGQU_DATE[3], GetDayOfYear())

		TONGQU_COMMIT_NUM = TONGQU_COMMIT_NUM + 1
		--给特殊奖励
		if TONGQU_COMMIT_NUM == 1 then
			AddExp( sceneId, selfId, 630*level*1.5 )
		
			local message = format("#Y获得#R经验%d点#Y奖励", 630*level)
			BeginQuestEvent(sceneId);
				AddQuestText(sceneId, message);
			EndQuestEvent();
			DispatchQuestTips(sceneId, selfId);
			Msg2Player(sceneId,selfId, message,4,2)
			
			message = format("#Y获得第%d名的#R额外经验%d点#Y奖励", TONGQU_COMMIT_NUM, 630*level*0.5)
			BeginQuestEvent(sceneId);
				AddQuestText(sceneId, message);
			EndQuestEvent();
			DispatchQuestTips(sceneId, selfId);
			Msg2Player(sceneId,selfId, message,4,2)

			local name = GetName(sceneId, selfId)
			message = "恭喜#G"..name.."#R为本次活动首位完成#G【童趣】#R的玩家，#G前三十名#R完成的玩家将获得#G额外的奖励#R！"
			LuaAllScenceM2Wrold( sceneId, message, CHAT_PLANE_SCROLL, 1 )
			LuaAllScenceM2Wrold( sceneId, message, CHAT_LEFTDOWN, 1 )

		elseif TONGQU_COMMIT_NUM <= 30 then
			AddExp( sceneId, selfId, 630*level*1.5 )
			local message = format("#Y获得#R经验%d点#Y的奖励", 630*level)
			BeginQuestEvent(sceneId);
				AddQuestText(sceneId, message);
			EndQuestEvent();
			DispatchQuestTips(sceneId, selfId);
			Msg2Player(sceneId,selfId, message,4,2)
			
			message = format("#Y获得第%d名的#R额外经验%d点#Y奖励", TONGQU_COMMIT_NUM, 630*level*0.5)
			BeginQuestEvent(sceneId);
				AddQuestText(sceneId, message);
			EndQuestEvent();
			DispatchQuestTips(sceneId, selfId);
			Msg2Player(sceneId,selfId, message,4,2)
		else
			AddExp( sceneId, selfId, 630*level )
			local message = format("#Y获得#R经验%d点#Y奖励", 630*level)
			BeginQuestEvent(sceneId);
				AddQuestText(sceneId, message);
			EndQuestEvent();
			DispatchQuestTips(sceneId, selfId);
			Msg2Player(sceneId,selfId, message,4,2)
		end

		local itemId=x300320_g_AwardItem;
	
		BeginAddItem( sceneId )
		AddItem( sceneId, itemId, 1 )
		local ret = EndAddItem( sceneId, selfId )
		if ret > 0 then
			AddItemListToPlayer(sceneId,selfId)

			local message = format("#Y获得物品#R#{_ITEM%d}#Y的奖励", x300320_g_AwardItem )
			BeginQuestEvent(sceneId);
			AddQuestText(sceneId, message);
			EndQuestEvent();
			DispatchQuestTips(sceneId, selfId);
			--Msg2Player(sceneId,selfId, message,4,2)
		else
			local strText = "背包已满,不能获得奖励物品"
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, strText);
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
		end

		local nShengWang = GetShengWang( sceneId, selfId )
			nShengWang = nShengWang + 200
			SetShengWang( sceneId, selfId, nShengWang )
		local message = format("获得声望%d的奖励。", 200)
			BeginQuestEvent(sceneId);
				AddQuestText(sceneId, message);
			EndQuestEvent();
			DispatchQuestTips(sceneId, selfId);
			Msg2Player(sceneId,selfId,message,4,2)

		return 
	end 
	local sex = GetSex( sceneId, selfId )

	local AfterMissionId = x300320_GetAfterMission( sceneId, selfId, MissionId, param1, param2, param3, param4)

	if AfterMissionId == x300320_g_ReturnMissionId then
		if sex==0 then
			CancelSpecificImpact(sceneId, selfId, 7517)
			SendSpecificImpactToUnit(sceneId, selfId, selfId, selfId, 8314, 0)
		else
			CancelSpecificImpact(sceneId, selfId, 7516)
			SendSpecificImpactToUnit(sceneId, selfId, selfId, selfId, 8314, 0)
		end

		CancelSpecificImpact(sceneId, selfId,7534)
		ClearMutexState(sceneId, selfId, 21)

		--删除物品
		local ItemCnt = GetItemCount( sceneId, selfId, x300320_g_ItemNeed1 )
		if ItemCnt > 0 then 
			DelItem(sceneId, selfId,x300320_g_ItemNeed1, 1)
		end

		ItemCnt = GetItemCount( sceneId, selfId, x300320_g_ItemNeed2 )
		if ItemCnt > 0 then 
			DelItem(sceneId, selfId,x300320_g_ItemNeed2, 1)
		end
		 
	end
	
	--检查前置任务
	local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId,AfterMissionId  )
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

	local ret = QuestCheckAcceptNM( sceneId, selfId, targetId, AfterMissionId ) -- 获取接受任务检查信息

	if ret > 0 then -- 如果可以接这个任务
		ret = AddQuestNM( sceneId, selfId, AfterMissionId ) -- 给玩家添加任务
		if ret > 0 then
				if MissionId == x300320_g_FirstMissionId then 
					--ReCallHorse( sceneId, selfId )--强制下马
					BeginAddItem(sceneId)
					AddItem( sceneId, x300320_g_ItemNeed1, 1 )
					local retOther = EndAddItem(sceneId,selfId)
					if retOther > 0 then
						AddItemListToPlayer(sceneId,selfId)
					else
						local strText = "背包已满,不能获得任务道具"
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId, strText);
						EndQuestEvent(sceneId)
						DispatchQuestTips(sceneId,selfId)
						--return
					end

					BeginAddItem(sceneId)
					AddItem( sceneId, x300320_g_ItemNeed2, 1 )
					retOther = EndAddItem(sceneId,selfId)
					if retOther > 0 then
						AddItemListToPlayer(sceneId,selfId)
					else
						local strText = "背包已满,不能获得任务道具"
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId, strText);
						EndQuestEvent(sceneId)
						DispatchQuestTips(sceneId,selfId)
						--return
					end

					ReCallHorse( sceneId, selfId )--强制下马

					local misIndex = GetQuestIndexByID( sceneId, selfId, AfterMissionId )
					local circleNum = GetQuestData(sceneId, selfId, MD_TONGQU_CIRCLE[1], MD_TONGQU_CIRCLE[2], MD_TONGQU_CIRCLE[3])
					if circleNum == 0 then
						SetQuestByIndex( sceneId, selfId, misIndex, 1, AfterMissionId )
					end
				
					if sex==0 then
						SendSpecificImpactToUnit(sceneId, selfId, selfId, selfId, 8314, 0)
						SendSpecificImpactToUnit(sceneId, selfId, selfId, selfId, 7517, 0)	
					else
						SendSpecificImpactToUnit(sceneId, selfId, selfId, selfId, 8314, 0)
						SendSpecificImpactToUnit(sceneId, selfId, selfId, selfId, 7516, 0)
					end
					SendSpecificImpactToUnit(sceneId, selfId, selfId, selfId, 7534, 0)--添加互斥
					MarkMutexState(sceneId, selfId, 21)
					local misIndex = GetQuestIndexByID( sceneId, selfId, AfterMissionId )
					SetQuestByIndex( sceneId, selfId, misIndex, MP_MAXCIRCLE, 5 )
				else
					if AfterMissionId ~= x300320_g_ReturnMissionId then
						local ItemCnt = GetItemCount( sceneId, selfId, x300320_g_ItemNeed2 )
						if ItemCnt == 0 then 
							BeginAddItem(sceneId)
							AddItem( sceneId, x300320_g_ItemNeed2, 1 )
							local retAdd = EndAddItem(sceneId,selfId)
							if retAdd > 0 then
								AddItemListToPlayer(sceneId,selfId)
							else
								local strText = "背包已满,接受物品失败"
								BeginQuestEvent(sceneId)
								AddQuestText(sceneId, strText);
								EndQuestEvent(sceneId)
								DispatchQuestTips(sceneId,selfId)
								--return
							end

						end
					else
						--添加日志
						GamePlayScriptLog(sceneId, selfId, 352)
					end

					AddExp( sceneId, selfId, 450*level )
					
					local expMessage = format("#Y获得#R经验%d#Y的奖励。", 450*level)
					BeginQuestEvent(sceneId);
						AddQuestText(sceneId, expMessage);
					EndQuestEvent();
					DispatchQuestTips(sceneId, selfId);
					Msg2Player(sceneId,selfId, expMessage,4,2)


					local circleNum = GetQuestData(sceneId, selfId, MD_TONGQU_CIRCLE[1], MD_TONGQU_CIRCLE[2], MD_TONGQU_CIRCLE[3])
					SetQuestData(sceneId, selfId, MD_TONGQU_CIRCLE[1], MD_TONGQU_CIRCLE[2], MD_TONGQU_CIRCLE[3], circleNum+1)

					local misIndex = GetQuestIndexByID( sceneId, selfId, AfterMissionId )
					SetQuestByIndex( sceneId, selfId, misIndex, 5, GetLevel(sceneId, selfId) )
					SetQuestByIndex( sceneId, selfId, misIndex, MP_CIRCLE, circleNum+1 )
					SetQuestByIndex( sceneId, selfId, misIndex, MP_MAXCIRCLE, 5 )
					if circleNum == 0 then
						SetQuestByIndex( sceneId, selfId, misIndex, 1, param1 )
						SetQuestByIndex( sceneId, selfId, misIndex, 2, AfterMissionId )
					elseif circleNum == 1 then
						SetQuestByIndex( sceneId, selfId, misIndex, 1, param1 )
						SetQuestByIndex( sceneId, selfId, misIndex, 2, param2 )
						SetQuestByIndex( sceneId, selfId, misIndex, 3, AfterMissionId )
					elseif circleNum == 2 then
						SetQuestByIndex( sceneId, selfId, misIndex, 1, param1 )
						SetQuestByIndex( sceneId, selfId, misIndex, 2, param2 )
						SetQuestByIndex( sceneId, selfId, misIndex, 3, param3 )
						SetQuestByIndex( sceneId, selfId, misIndex, 4, AfterMissionId )
					elseif circleNum == 3 then	
						SetQuestByIndex( sceneId, selfId, misIndex, 1, param1 )
						SetQuestByIndex( sceneId, selfId, misIndex, 2, param2 )
						SetQuestByIndex( sceneId, selfId, misIndex, 3, param3 )
						SetQuestByIndex( sceneId, selfId, misIndex, 4, param4 )
					end

					if AfterMissionId == x300320_g_ReturnMissionId then
						SetQuestByIndex( sceneId, selfId, misIndex, 7, 1 )
					end

					--添加日志
					if circleNum == 0 then
						GamePlayScriptLog(sceneId, selfId, 311)
					elseif circleNum == 1 then
						GamePlayScriptLog(sceneId, selfId, 312)
						GamePlayScriptLog(sceneId, selfId, 321)
					elseif circleNum == 2 then
						GamePlayScriptLog(sceneId, selfId, 322)
						GamePlayScriptLog(sceneId, selfId, 331)
					elseif circleNum == 3 then
						GamePlayScriptLog(sceneId, selfId, 332)
						GamePlayScriptLog(sceneId, selfId, 341)
					elseif circleNum == 4 then
						GamePlayScriptLog(sceneId, selfId, 342)
						GamePlayScriptLog(sceneId, selfId, 351)
					end

					
				end
			
			AddDispatchQuestInfoNM( sceneId, selfId, targetId, AfterMissionId, 0)
			for i = 0, 4 do
				local SceneID, PosX, PosZ, tips = GetAskWayPosNM(sceneId, selfId, AfterMissionId, i)
				if SceneID ~= -1 then
					CallScriptFunction( UTILITY_SCRIPT, "AskTheWayPos", sceneId, selfId, SceneID, PosX, PosZ, tips )
				end
			end
			
			local MissionName = GetQuestNameNM( sceneId, selfId, AfterMissionId )
			local message = format(x300320_g_AcceptMessage, MissionName);
			local strText = message

			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, strText);
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
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

	end

end

--物品改变
function x300320_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
    
    if MissionId == nil or MissionId < 0 then
        return
    end
    
    if IsHaveQuestNM(sceneId,selfId,MissionId) <= 0 then
        return
    end
    
	local NeedNum, ObjIndex = GetQuestNeedItemNumNM( sceneId, selfId, MissionId, itemdataId )
	local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )

	if NeedNum > 0 then
		local Num = GetItemCount( sceneId, selfId, itemdataId )
		--hf_DisplayMissionGetItemMessage(sceneId, selfId, itemdataId, Num, NeedNum);
		if Num < NeedNum then --还没有完成任务
 			SetQuestByIndex( sceneId, selfId, misIndex, ObjIndex, Num )         --by zheng
		elseif Num == NeedNum then
			--已经完成任务
			local strText = format("#Y你成功捕捉到了@item_%d#Y，请使用#G传送指轮#Y完成任务", itemdataId)
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, strText);
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
			SetQuestByIndex( sceneId, selfId, misIndex, ObjIndex, Num )         --by zheng
			SetQuestByIndex( sceneId, selfId, misIndex, 7, 1 )        
		end
	end
end

--定点使用物品任务
function x300320_PositionUseItem( sceneId, selfId, BagIndex, impactId )

	--如果该任务已经完成直接退出

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
			local strText = format("您应该在@sceneid_%d[%d,%d]使用此物品！", scene, posx, posz )
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, strText)
			DispatchQuestTips(sceneId, selfId)
			EndQuestEvent(sceneId)
			return 0
		end
	end

	local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )
	if GetQuestParam( sceneId, selfId, misIndex, MissionIdx ) == 1 then
		return 0
	end

	--删除物品
	EraseItem(sceneId, selfId, BagIndex)

	--发送提示
	SetQuestByIndex( sceneId, selfId, misIndex, MissionIdx, 1 )
	
	BeginQuestEvent(sceneId)
	AddQuestText(sceneId, dispStr);
	EndQuestEvent(sceneId)
	DispatchQuestTips(sceneId,selfId)
	
	if bDispOther > 0 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, otherStr);
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
	end

	--播放效果
	if impactId ~= -1 then
		SendSpecificImpactToUnit(sceneId, selfId, selfId, selfId, impactId, 0);
	end

	return 1
end

--采集任务
--打开ItemBox
function x300320_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )

	local MissionId, needItemCount, collNum = GetItemIdInItemBoxNM( sceneId, selfId, targetId, gpType, needItemID )
	if MissionId == -1 then
		return 1 --没有这个任务
	end

	if IsHaveQuestNM( sceneId, selfId, MissionId ) == 0 then	-- 如果没这个任务直接退出
		local MissionName = GetQuestNameNM(sceneId, selfId, MissionId);
		local str = "您没有接受相关任务！"
		if MissionName == nil or MissionName == "" then
			str = "您没有接受相关任务！"
		else
			str = format("您没有接受#Y%s#W！", MissionName);
		end
		
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, str);
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)

		return 1
	end

	local itemCountNow = GetItemCount( sceneId, selfId, needItemID )
	if itemCountNow >= needItemCount then
		local str = "物品已经收集齐全！";
		if needItemCount > 0 then
			str = "物品已经收集齐全！";
		else
			str = "您不需要这个物品！";
		end

		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, str);
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)

		return 1
	end

	return 0
end

function x300320_ProcQuestLogRefresh( sceneId, selfId, MissionId)

	local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )	
	local str;
	str = GetQuestNameNM(sceneId, selfId, MissionId);
	local maxcircle = 5--GetQuestParam( sceneId, selfId, misIndex, MP_MAXCIRCLE )
	local circle = GetQuestParam( sceneId, selfId, misIndex, MP_CIRCLE )
	
	str = str.."("..circle+1;
	str = str.."/"..maxcircle;
	str = str..")";

	

    BeginQuestEvent(sceneId)
        AddQuestLogCustomText( sceneId,
                                "",                    -- 标题
                                str,                 -- 任务名字
                                "",               --任务目标
                                "",                         --任务NPC
                                "",                   --任务攻略
                                "",                --任务描述
                                ""        --任务小提示
                                )

	EndQuestEvent()
	DispatchQuestLogUpdate(sceneId, selfId, MissionId);

end

function x300320_TongquOnDie(sceneId, selfId)
	if IsHaveSpecificImpact(sceneId, selfId, 7517) > 0 or IsHaveSpecificImpact(sceneId, selfId, 7516) > 0 then
		SendSpecificImpactToUnit(sceneId, selfId, selfId, selfId, 7534, 0)--添加互斥
		MarkMutexState(sceneId, selfId, 21)
	end
end

