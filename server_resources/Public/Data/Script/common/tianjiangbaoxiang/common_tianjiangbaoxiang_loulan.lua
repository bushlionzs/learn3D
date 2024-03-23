
x310010_g_ScriptId = 310010

x310010_g_MissionList = { 8022,8023,8024,8025,8026,8027 }
x310010_g_MissionItem = { {mission=8022,item1=12030051, item2=12030052},
						  {mission=8023,item1=12030051, item2=12030053},
						  {mission=8024,item1=12030052, item2=12030053},
						  {mission=8025,item1=12030051, item2=12030052},
						  {mission=8026,item1=12030051, item2=12030053},
						  {mission=8027,item1=12030052, item2=12030053}
						}

x310010_g_AcceptMessage		= "您接受了任务：%s"
x310010_g_AbandonMessage	= "您放弃了任务：%s"
x310010_g_CompleteMessage	= "您完成了任务：%s"

x310010_g_MissionCommentMessage	=	"不在接任务时间，请关注活动公告"
x310010_g_MissionAcceptFailedMessage_Accepted	=	"你在本日已经做过本任务了，请明日再来"
x310010_g_MissionSubmitFailedMessage_OverTime	=	"你已经错过了交任务的时间，请放弃任务"
x310010_g_MissionAcceptTime1 = { 450, 480 }	--7*60+30, 8*60
x310010_g_MissionAcceptTime2 = { 750, 780 }	--12*60+30,13*60
x310010_g_MissionAcceptTime3 = { 1170, 1200 }	--18*60+30,19*60
x310010_g_AwardItem = 12030028
x310010_g_VirtualMissionId = 1362

x310010_g_RandItem = {11010100, 11010101, 11010102}

function x310010_GetMission()
	local index = random(1, 6);
	return x310010_g_MissionList[index]
end

function x310010_GetMDAccepted(sceneId, selfId, index)
	if index == 1 then
		local value = GetQuestData(sceneId, selfId, MD_TIANJIANG_BAOXIANG_ACCEPTED1[1], MD_TIANJIANG_BAOXIANG_ACCEPTED1[2], MD_TIANJIANG_BAOXIANG_ACCEPTED1[3])
		return value
	elseif index == 2 then
		local value = GetQuestData(sceneId, selfId, MD_TIANJIANG_BAOXIANG_ACCEPTED2[1], MD_TIANJIANG_BAOXIANG_ACCEPTED2[2], MD_TIANJIANG_BAOXIANG_ACCEPTED2[3])
		return value
	elseif index == 3 then
		local value = GetQuestData(sceneId, selfId, MD_TIANJIANG_BAOXIANG_ACCEPTED3[1], MD_TIANJIANG_BAOXIANG_ACCEPTED3[2], MD_TIANJIANG_BAOXIANG_ACCEPTED3[3])
		return value
	end
	
end

function x310010_SetMDAccepted(sceneId, selfId, index, value)
	if index == 1 then
		SetQuestData(sceneId, selfId, MD_TIANJIANG_BAOXIANG_ACCEPTED1[1], MD_TIANJIANG_BAOXIANG_ACCEPTED1[2], MD_TIANJIANG_BAOXIANG_ACCEPTED1[3], value)
	elseif index == 2 then
		SetQuestData(sceneId, selfId, MD_TIANJIANG_BAOXIANG_ACCEPTED2[1], MD_TIANJIANG_BAOXIANG_ACCEPTED2[2], MD_TIANJIANG_BAOXIANG_ACCEPTED2[3], value)
	elseif index == 3 then
		SetQuestData(sceneId, selfId, MD_TIANJIANG_BAOXIANG_ACCEPTED3[1], MD_TIANJIANG_BAOXIANG_ACCEPTED3[2], MD_TIANJIANG_BAOXIANG_ACCEPTED3[3], value)
	end
end

function x310010_GetMDDate(sceneId, selfId)
	local day = GetQuestData(sceneId, selfId, MD_TIANJIANG_BAOXIANG_DATE[1], MD_TIANJIANG_BAOXIANG_DATE[2], MD_TIANJIANG_BAOXIANG_DATE[3])
	return day
end

function x310010_SetMDDate(sceneId, selfId, day)
	SetQuestData(sceneId, selfId, MD_TIANJIANG_BAOXIANG_DATE[1], MD_TIANJIANG_BAOXIANG_DATE[2], MD_TIANJIANG_BAOXIANG_DATE[3], day)
end


function x310010_NextDayReset(sceneId, selfId)
	local today = GetDayOfYear()
	local lastDay = x310010_GetMDDate(sceneId, selfId)

	if today ~= lastDay then
		x310010_SetMDDate(sceneId, selfId, 0)
		--x310010_SetMDAccepted(sceneId, selfId, 1, 0)
		--x310010_SetMDAccepted(sceneId, selfId, 2, 0)
		--x310010_SetMDAccepted(sceneId, selfId, 3, 0)
	end
end

function x310010_IsNextDay(sceneId, selfId)
	
	local today = GetDayOfYear()
	local lastDay = x310010_GetMDDate(sceneId, selfId)

	if today ~= lastDay then
		return 1
	end 
		
	return -1
end


function x310010_HaveAccepted( sceneId, selfId )
	--local minspan = GetMinOfDay()

	--if minspan >= x310010_g_MissionAcceptTime1[1] and minspan <= x310010_g_MissionAcceptTime1[2] then
		--if x310010_GetMDAccepted(sceneId, selfId, 1) > 0 then
			--return 1
		--end
	--elseif  minspan >= x310010_g_MissionAcceptTime2[1] and minspan <= x310010_g_MissionAcceptTime2[2] then
		--if x310010_GetMDAccepted(sceneId, selfId, 2) > 0 then
			--return 2
		--end
	--elseif  minspan >= x310010_g_MissionAcceptTime3[1] and minspan <= x310010_g_MissionAcceptTime3[2] then
		--if x310010_GetMDAccepted(sceneId, selfId, 3) > 0 then
			--return 3
		--end
	--end

	if x310010_GetMDDate(sceneId, selfId) > 0 then
		return 1
	end

	return -1
end

function x310010_ProcAcceptCheckTime(  )

	local minspan = GetMinOfDay()
	
	--if minspan >= x310010_g_MissionAcceptTime1[1] and minspan <= x310010_g_MissionAcceptTime1[2] then
		--return 1
	if  minspan >= x310010_g_MissionAcceptTime2[1] and minspan <= x310010_g_MissionAcceptTime2[2] then
		return 2
	elseif  minspan >= x310010_g_MissionAcceptTime3[1] and minspan <= x310010_g_MissionAcceptTime3[2] then
		return 3
	end
	
	return -1
end

function x310010_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	MissionId = x310010_GetMission();

	for i, item in x310010_g_MissionList do
		if IsHaveQuestNM( sceneId, selfId, item ) > 0 then
			return 0
		end
	end

	if QuestCheckAcceptNM( sceneId, selfId, targetId, MissionId ) > 0 then
		local  missionState = GetQuestStateNM(sceneId, selfId, targetId, MissionId)
		AddQuestTextNM(sceneId, selfId, targetId, MissionId, missionState);
		return 1
	end
    
	return 0
end


function x310010_ProcEventEntry( sceneId, selfId, targetId, MissionId )
	if IsHaveQuestNM( sceneId, selfId, MissionId ) == 0 then	-- 如果没有这个任务
		if x310010_IsNextDay(sceneId, selfId) > 0 then
			x310010_NextDayReset(sceneId, selfId) 
		end
		
		local ret = QuestCheckAcceptNM( sceneId, selfId, targetId, MissionId )
		
		
			if ret > 0 then	-- 如果可以接这个任务
				--AddDispatchQuestInfoNM( sceneId, selfId, targetId, MissionId ) -- 显示接受任务信息
				BeginQuestEvent( sceneId);
				AddQuestText(sceneId, "#Y【个人】天降宝箱#W\n\t我们虔诚的祈祷，终于能得到长生天的感应，每天当所有的萨满信徒向着长生天祈福的时候，长生天就会降下赐福宝箱。\n\t我们现在需要你帮助，去寻找沉睡在宝箱内的圣物，如果你愿意帮我的话，请你在每天我们祈祷的时间来找我吧！\n#R\n【活动时间】#G\n 12：30~13：00\n 19：30~20：00#W\n\t注意：每天只可以接受一次本任务。");
				AddQuestMoneyBonus5(sceneId, 100 )
				AddQuestExpBonus(sceneId, GetLevel(sceneId, selfId)*4500)
				AddQuestItemBonus(sceneId, x310010_g_AwardItem, 1)
				
				EndQuestEvent(sceneId);
				DispatchQuestInfoNM(sceneId, selfId, targetId, x310010_g_ScriptId, MissionId);
			else
				local strText = "未知错误，无法接新的任务"
				if ret == -1 then
					strText = "等级不足，无法接新的任务"
				elseif ret == -2 then
					strText = "等级过高，无法接新的任务"
				elseif ret == -3 then
					strText = "金钱不足，无法接新的任务"
				elseif ret == -4 then
					strText = "您不是本国玩家，无法接新的任务"
				elseif ret == -5 then
					strText = "职业类型不符，无法接新的任务"
				elseif ret == -6 then
					strText = "阵营不符，无法接新的任务"
				elseif ret == -7 then
					strText = "此人无此任务"
				end
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId, strText);
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
			end

	else --如果有这个任务
		local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )
		if QuestCheckSubmitNM( sceneId, selfId, targetId, MissionId, misIndex ) > 0 then -- 如果任务可以完成
			QuestComplateInfoNM( sceneId, selfId, targetId, MissionId ) -- 显示完成信息
		else
			QuestNotComplateInfoNM( sceneId, selfId, targetId, MissionId ) -- 显示任务未完成信息
		end
	end
end

function x310010_ProcQuestAccept( sceneId, selfId, targetId, MissionId )
	if x310010_ProcAcceptCheckTime() < 0 then
		local MissionName = GetQuestNameNM(sceneId, selfId, MissionId);
			BeginQuestEvent(sceneId);
			AddQuestText(sceneId, x310010_g_MissionCommentMessage);
			EndQuestEvent(sceneId);
			DispatchQuestTips(sceneId,selfId);
			Msg2Player(sceneId,selfId,x310010_g_MissionCommentMessage,8,2)
		return 
	end

	if x310010_HaveAccepted( sceneId, selfId ) > 0 then
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, x310010_g_MissionAcceptFailedMessage_Accepted);
		EndQuestEvent(sceneId);
		DispatchQuestTips(sceneId,selfId);
		Msg2Player(sceneId,selfId,x310010_g_MissionAcceptFailedMessage_Accepted,8,2)
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
			QuestCom( sceneId, selfId, x310010_g_VirtualMissionId)
			AddDispatchQuestInfoNM( sceneId, selfId, targetId, MissionId, 1)

			GamePlayScriptLog(sceneId, selfId, 511)

			local day = GetDayOfYear()

			x310010_SetMDDate(sceneId, selfId, day)
			
			--if x310010_ProcAcceptCheckTime(  ) == 1 then
				--x310010_SetMDDate(sceneId, selfId, day)
				--x310010_SetMDAccepted(sceneId, selfId, 1, 1)
			--elseif x310010_ProcAcceptCheckTime(  ) == 2 then
				--x310010_SetMDDate(sceneId, selfId, day)
				--x310010_SetMDAccepted(sceneId, selfId, 2, 1)
			--elseif x310010_ProcAcceptCheckTime(  ) == 3 then
				--x310010_SetMDDate(sceneId, selfId, day)
				--x310010_SetMDAccepted(sceneId, selfId, 3, 1)
			--else
				--BeginQuestEvent(sceneId);
				--AddQuestText(sceneId, "#Y"..GetQuestNameNM(sceneId, selfId, MissionId).."#W\n\t"..x310010_g_MissionCommentMessage);
				--EndQuestEvent(sceneId);
				--DispatchQuestEventList(sceneId,selfId,targetId);
				--Msg2Player(sceneId,selfId,x310010_g_MissionCommentMessage,8,2)
				--return 
			--end

			local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )
			
			local MissionName = GetQuestNameNM( sceneId, selfId, MissionId )
			local message = format(x310010_g_AcceptMessage, MissionName);
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, message);
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
			Msg2Player(sceneId,selfId, message, 4, 2)
			
			for i, item in x310010_g_MissionItem do
				if item.mission == MissionId then
					local Num = GetItemCount( sceneId, selfId, item.item1 )
					if Num > 0 then
						SetQuestByIndex( sceneId, selfId, misIndex, 0, 1 )
					end

					local Num2 = GetItemCount( sceneId, selfId, item.item2 )
					if Num2 > 0 then
						SetQuestByIndex( sceneId, selfId, misIndex, 1, 1 )
					end

					if Num > 0 and Num2 > 0 then
						SetQuestByIndex( sceneId, selfId, misIndex, 7, 1 )
					end
				end
			end
			
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


--任务放弃
function x310010_ProcQuestAbandon( sceneId, selfId, MissionId )
	local ret = 0
	ret = DelQuestNM( sceneId, selfId, MissionId )
	if ret == 1 then
		local day = GetDayOfYear()
		x310010_SetMDDate(sceneId, selfId, day)

		local item1=12030051;
		local item2=12030052;
		local item3=12030053;

		local ItemCnt = GetItemCount( sceneId, selfId, item1 )
		if ItemCnt > 0 then 
			DelItem(sceneId, selfId,item1,ItemCnt)
		end

		ItemCnt = GetItemCount( sceneId, selfId, item2 )
		if ItemCnt > 0 then 
			DelItem(sceneId, selfId,item2,ItemCnt)
		end

		ItemCnt = GetItemCount( sceneId, selfId, item3 )
		if ItemCnt > 0 then 
			DelItem(sceneId, selfId,item3,ItemCnt)
		end

		local MissionName = GetQuestNameNM( sceneId, selfId, MissionId )
		local message = format(x310010_g_AbandonMessage, MissionName);
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, message);
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
		Msg2Player(sceneId,selfId, message, 4, 2)

		QuestUnCom( sceneId, selfId, x310010_g_VirtualMissionId)

	end
end


function x310010_ProcQuestAttach( sceneId, selfId, targetId, npcGuid, misIndex, MissionId )
   
	if IsHaveQuestNM( sceneId, selfId, MissionId ) == 0 then	-- 如果没有这个任务
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

--返回1代表成功，0代表交任务失败
function x310010_ProcQuestSubmit( sceneId, selfId, targetId, selectId, MissionId )
	if IsHaveQuestNM( sceneId, selfId, MissionId ) == 0 then	-- 如果没有这个任务
		return
	end

	local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )
	if QuestCheckSubmitNM( sceneId, selfId, targetId, MissionId, misIndex ) == 0 then 
		return
	end

	if GetBagSpace(sceneId, selfId) < 1 then
		local message = "背包已满，无法完成此任务"
		BeginQuestEvent(sceneId);
			AddQuestText(sceneId, message);
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
		return
	end

	DelQuest(sceneId, selfId, MissionId)
	CallScriptFunction( 203782, "Finishbaoxiang", sceneId, selfId)
	QuestUnCom( sceneId, selfId, x310010_g_VirtualMissionId)
	GamePlayScriptLog(sceneId, selfId, 512)

	local day = GetDayOfYear()
	x310010_SetMDDate(sceneId, selfId, day)

		local item1=12030051;
		local item2=12030052;
		local item3=12030053;
		
		local ItemCnt = GetItemCount( sceneId, selfId, item1 )
		if ItemCnt > 0 then 
			DelItem(sceneId, selfId,item1,ItemCnt)
		end

		ItemCnt = GetItemCount( sceneId, selfId, item2 )
		if ItemCnt > 0 then 
			DelItem(sceneId, selfId,item2,ItemCnt)
		end

		ItemCnt = GetItemCount( sceneId, selfId, item3 )
		if ItemCnt > 0 then 
			DelItem(sceneId, selfId,item3,ItemCnt)
		end

		local MissionName = GetQuestNameNM( sceneId, selfId, MissionId )
		local message = format(x310010_g_CompleteMessage, MissionName);
		BeginQuestEvent(sceneId);
			AddQuestText(sceneId, message);
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
		Msg2Player(sceneId,selfId, message,4,2)

		local level = GetLevel(sceneId, selfId)
		local awardExp = level * 4500
		AddExp( sceneId, selfId, awardExp )
		message = format("#Y获得#R经验%d#Y的奖励", awardExp)
		BeginQuestEvent(sceneId);
			AddQuestText(sceneId, message);
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
		Msg2Player(sceneId,selfId, message,4,2)

		BeginAddItem( sceneId )
		AddItem( sceneId, x310010_g_AwardItem, 1 )
		
		local rndItemid = -1
		if GetLevel(sceneId, selfId) >= 80 and random(1, 100) <= 22 then
			local index = random(1,3)
			if index < 1 then index = 1 end
			if index > 3 then index = 3 end
			rndItemid = x310010_g_RandItem[index]
			AddItem( sceneId, rndItemid, 1)
		end
		
		local ret = EndAddItem( sceneId, selfId )
		if ret > 0 then
	
			AddItemListToPlayer(sceneId,selfId)

			message = format("#Y获得物品#R#{_ITEM%d}#Y的奖励", x310010_g_AwardItem )
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
		
		AddCountryResource(sceneId,selfId,2,2000,1)
		--声望
	
		local nShengWang = GetShengWang( sceneId, selfId )
		nShengWang = nShengWang + 100
		SetShengWang( sceneId, selfId, nShengWang )
		message = format("获得声望%d的奖励。", 100)
		BeginQuestEvent(sceneId);
			AddQuestText(sceneId, message);
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
		Msg2Player(sceneId,selfId,message,4,2)
		
		if rndItemid ~= -1 then
			local str = format("#Y随机获得#G1个#Y#{_ITEM%d}", rndItemid)
			Msg2Player(sceneId, selfId, str, 8, 3)
			--Msg2Player(sceneId, selfId, str, 8, 2)
		end
	--end
end

function x310010_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )

    
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
		
		if Num < NeedNum then --还没有完成任务
			BeginQuestEvent(sceneId)
			local strText = format("#Y获得物品#G#{_ITEM%d}#Y: %d/%d", itemdataId, Num, NeedNum )
			if strText == nil then
				strText = "";
			end
			AddQuestText( sceneId, strText )
			EndQuestEvent( sceneId )
			DispatchQuestTips( sceneId, selfId )
			SetQuestByIndex( sceneId, selfId, misIndex, ObjIndex, Num )         --by zheng
		elseif Num == NeedNum then
			--已经完成任务
			BeginQuestEvent(sceneId)
			local strText = format( "#Y已完成获得物品#G#{_ITEM%d}#Y: %d/%d", itemdataId, Num, NeedNum )
			if strText == nil then
				strText = "";
			end
			AddQuestText( sceneId, strText )
			EndQuestEvent( sceneId )
			DispatchQuestTips( sceneId, selfId )
			SetQuestByIndex( sceneId, selfId, misIndex, ObjIndex, Num )         --by zheng
			if GetQuestParam(sceneId, selfId, misIndex, 0) == NeedNum and GetQuestParam(sceneId, selfId, misIndex, 1) == NeedNum then
				SetQuestByIndex( sceneId, selfId, misIndex, 7, 1 )
			end
		end
	end
end

function x310010_TianJiangBaoXiangDisconnect( sceneId, selfId )

end

function x310010_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox", sceneId, selfId, targetId, gpType, needItemID )
end

function x310010_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle", sceneId, selfId, targetId, gpType, needItemID )
end

function x310010_ProcQuestLogRefresh( sceneId, selfId, MissionId)

	local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )	
	local str;
	str = GetQuestNameNM(sceneId, selfId, MissionId);
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

--打开
function x310010_OnProcOver( sceneId, selfId, targetId )
end

--打开后检查
function x310010_OpenCheck( sceneId, selfId, targetId )
end