
--脚本邮件的脚本文件

--脚本号
x888889_g_scriptId = 888889


function x888889_ExecuteMail( sceneId, selfId, param0, param1, param2, param3 )
	param0 = tonumber(format("%u",param0))
	param1 = tonumber(format("%u",param1))
	param2 = tonumber(format("%u",param2))
	param3 = tonumber(format("%u",param3))
	
	if param0 == MAIL_REPUDIATE then
		x888889_Mail_Repudiate( sceneId, selfId, param0, param1, param2, param3 )
	elseif param0 == MAIL_BETRAYMASTER then
		x888889_Mail_BetrayMaster( sceneId, selfId, param0, param1, param2, param3 )
	elseif param0 == MAIL_EXPELPRENTICE then
		x888889_Mail_ExpelPrentice( sceneId, selfId, param0, param1, param2, param3 )
	elseif param0 == MAIL_UPDATE_ATTR then
		UpdateAttr(sceneId, selfId, param0, param1, param2, param3)
	elseif param0 == MAIL_UNSWEAR then
		x888889_Mail_Unswear(sceneId, selfId, param0, param1, param2, param3)
	elseif param0 == MAIL_PRENTICE_EXP then
		x888889_Mail_PrenticeProfExp(sceneId, selfId, param0, param1, param2, param3)
	elseif param0 == MAIL_LEAVE_GUILD then
	 	x888889_Mail_LeaveGuild(sceneId, selfId, param0, param1, param2, param3)  
	elseif param0 == MAIL_GIVE_MONEY then	
		x888889_Mail_GiveMoney(sceneId, selfId, param0, param1, param2, param3)  
	elseif param0 == MAIL_GIVE_ITEM then	
		x888889_Mail_GiveItem(sceneId, selfId, param0, param1, param2, param3) 
	elseif param0 == MAIL_DELETE_MISSION then	
		x888889_Mail_DeleteMission(sceneId, selfId, param0, param1, param2, param3) 
	elseif param0 == MAIL_GIVE_MONEY2MASTER then	
		x888889_Mail_GiveMoney2Master(sceneId, selfId, param0, param1, param2, param3) 
	elseif param0 == MAIL_GIVE_EXP then	
		x888889_Mail_GiveExp(sceneId, selfId, param0, param1, param2, param3) 
	elseif param0 == MAIL_MASTER_AWARD then	
		x888889_Mail_MasterAward(sceneId, selfId, param0, param1, param2, param3) 

	
	end

end

--徒弟给师傅经验
function x888889_Mail_PrenticeProfExp( sceneId, selfId, command, PrenticeGuid, Exps, zero )
	--PrenticeGuid给了selfId，Exps这么多经验
	if Exps > 0 then
		LuaAddPrenticeProExp( sceneId, selfId, PrenticeGuid, Exps )
	end
end

function x888889_Mail_Unswear( sceneId, selfId, command, betrayerGuid, alldismiss, zero )

	--(1) 降低好友度
	local FriendPoint = GetFriendPointByGUID( sceneId, selfId, betrayerGuid )
	if FriendPoint > 500 then
		SetFriendPointByGUID( sceneId, selfId, betrayerGuid, 500 )
	end
	
	--(2) 取消结拜
	Unswear( sceneId, selfId, betrayerGuid )
	
	--(3) 如果全部解散，则删除称号
	if tonumber(alldismiss) == 1 then
		AwardJieBaiTitle( sceneId, selfId, "" )
		DispatchAllTitle( sceneId, selfId )
	end
end

function x888889_Mail_Repudiate( sceneId, selfId, param0, param1, param2, param3 )
	
	local TITLE_MARRY = 4
	
	DeleteTitle(sceneId, selfId, TITLE_MARRY)
	
	local SpouseGUID = GetSpouseGUID( sceneId, selfId )
	if param1 ~= SpouseGUID and SpouseGUID ~= tonumber(format("%u",-1)) then --已经不是自己的配偶 不需要处理
		return
	end
	local spouseName = GetFriendName(sceneId, selfId, SpouseGUID)
	
	if spouseName ~= "" then
		local ret = format("%s与您解除了夫妻关系。", spouseName)
		Msg2Player(sceneId,selfId,ret,8,2)
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, ret);
		EndQuestEvent();
	end
	
	--删除结婚状态；
	Divorce( sceneId, selfId )
	
	for i , missionId in SPOUSE_TASK do
		if missionId == SPOUSE_TASK[2] and 1 == IsHaveQuest(sceneId, selfId, missionId) and GetSex(sceneId, selfId) == 1 then			
			local BusID  =  GetBusId(sceneId, selfId)
			if BusID ~= -1 then
				DeleteBus(sceneId, BusID,1)
			end
		end
		if missionId == SPOUSE_TASK[3] and 1 == IsHaveQuest(sceneId, selfId, missionId) then
			DelItem(sceneId, selfId, SPOUSE_TASK_POSITION_USE_ITEM, 1)
		end
		if 1 == IsHaveQuest(sceneId, selfId, missionId) then
			DelQuestNM( sceneId, selfId, missionId )
		end
	end

end

function x888889_Mail_BetrayMaster( sceneId, selfId, param0, param1, param2, param3 )
	--开除徒弟
	local Msg
	local PrenticeName	= GetFriendName( sceneId, selfId, param1 )
	if 0 == param2 then
		--IncreaseFinishPrenticeshipNum(sceneId, selfId)
		--if PrenticeName ~= "" then
			--Msg = format("恭喜您，由于您的徒弟出师了，系统解除了您与徒弟%s的师徒关系。", PrenticeName);
			--Msg2Player(sceneId,selfId,Msg,8,2)
		--end
	elseif 1 == param2 and PrenticeName ~= "" then
		Msg = format("很遗憾，您的徒弟%s解除了与您的师徒关系。", PrenticeName);
		Msg2Player(sceneId,selfId,Msg,8,2)
	elseif 2 == param2 and PrenticeName ~= "" then
		Msg = format("很遗憾，由于您的徒弟3天未登陆游戏，系统解除了您与徒弟%s的师徒关系。", PrenticeName);
		Msg2Player(sceneId,selfId,Msg,8,2)
	end
	local isPrentice = 0
	local index = 0
	while index < MAX_PRENTICE_NUM do
		if GetPrenticeGUID(sceneId, selfId, index) == param1 then
			isPrentice = 1
			break
		end
		index = index + 1
	end
	if 0 == isPrentice then --已经不是自己的徒弟 不处理
		return
	end
	local isFinishPrenticeship = 0 --出师
	if 0 == param2 then
		--isFinishPrenticeship = 1
	end
	ExpelPrentice( sceneId, selfId, param1, isFinishPrenticeship )
end

function x888889_Mail_ExpelPrentice( sceneId, selfId, param0, param1, param2, param3 )
	
	local Msg
	local targetGUID = GetMasterGUID(sceneId, selfId);
	if targetGUID == -1 then
		return
	end
	local MasterName = GetFriendName( sceneId, selfId, targetGUID )
	if 0 == param1 then
		Msg = format("很遗憾，由于您的师傅3天未登陆游戏，系统解除了您与师傅%s的师徒关系。", MasterName);
		Msg2Player(sceneId,selfId,Msg,8,2)
	elseif 1 == param1 then
		Msg = format("很遗憾，您的师傅%s解除了与您的师徒关系。", MasterName);
		Msg2Player(sceneId,selfId,Msg,8,2)
	end

	if targetGUID ~= param2 then -- 不是自己当前的师傅 不处理
		return
	end
	local TITLE_PRENTICE = 5
	DeleteTitle(sceneId, selfId, TITLE_PRENTICE)
	BetrayMaster( sceneId, selfId )
end

function x888889_Mail_GiveMoney(sceneId, selfId, param0, param1, param2, param3)
	AddMoney(sceneId, selfId, param1, param2)
end

--徒弟出师给的奖励
function x888889_Mail_GiveMoney2Master(sceneId, selfId, param0, param1, param2, param3)
	AddMoney(sceneId, selfId, param1, param2)
end

--离开帮会 
function x888889_Mail_LeaveGuild( sceneId, selfId, param0, param1, param2, param3 )

	CallScriptFunction( SCENE_SCRIPT_ID, "OnLeaveGuild", sceneId, selfId,0 )
	
end

--添加物品
function x888889_Mail_GiveItem(sceneId, selfId, param0, param1, param2, param3)

	BeginAddItem(sceneId)
	AddItem( sceneId, param1, param2 )
	local ret = EndAddItem(sceneId,selfId)
	if ret > 0 then
		AddItemListToPlayer(sceneId,selfId)
	end
	
end

--给经验
function x888889_Mail_GiveExp(sceneId, selfId, param0, param1, param2, param3)
	AddExp(sceneId, selfId, param1);
end

function x888889_Mail_SetMissionData(sceneId, selfId)
		SetQuestData(sceneId, selfId, MD_SPOUSE_MISSION_DATE[1][1], MD_SPOUSE_MISSION_DATE[1][2], MD_SPOUSE_MISSION_DATE[1][3], GetDayOfYear())
end

--删除任务 
--param1 为任务id 
--param2 为1---代表是手动放弃 0---代表被动的放弃的 比如任务时间到了。。。 并不是所有任务都需要此参数的
function x888889_Mail_DeleteMission(sceneId, selfId, param0, param1, param2, param3)
	 if 1 == IsHaveQuest(sceneId, selfId, param1) then
	 		if tonumber(param1) == tonumber(SPOUSE_TASK[2]) and tonumber(param2) == tonumber(0) then
				local strText = "由于您的配偶离开#G探亲的小孩#W#W#cEFC800时间过久，孩童走失了，任务失败！"
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId, strText);
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				Msg2Player(sceneId,selfId,strText,8,2)
				DelQuestNM( sceneId, selfId, param1 )
				x888889_Mail_SetMissionData(sceneId, selfId)
			elseif tonumber(param1) == tonumber(SPOUSE_TASK[2]) and tonumber(param2) == tonumber(1) then
				local strText = "由于您的配偶放弃了夫妻任务，任务失败！"
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId, strText);
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				Msg2Player(sceneId,selfId,strText,8,2)
				DelQuestNM( sceneId, selfId, param1 )
				x888889_Mail_SetMissionData(sceneId, selfId)
				local BusID  =  GetBusId(sceneId, selfId)
				if BusID ~= -1 and GetSex(sceneId, selfId) == 1 then
			   	--如果BUS还活着 男的才负责护送
					DeleteBus(sceneId, BusID,1)
				end
			
			elseif tonumber(param1) == tonumber(SPOUSE_TASK[1]) or tonumber(param1) == tonumber(SPOUSE_TASK[3]) then
				local strText = "由于您的配偶放弃了夫妻任务，任务失败！"
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId, strText);
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				Msg2Player(sceneId,selfId,strText,8,2)
				DelQuestNM( sceneId, selfId, param1 )
				x888889_Mail_SetMissionData(sceneId, selfId)
				if tonumber(param1) == tonumber(SPOUSE_TASK[3]) then
					DelItem(sceneId, selfId, SPOUSE_TASK_POSITION_USE_ITEM, 1)
				end
			end
		end
end

--给师傅奖励
function x888889_Mail_MasterAward(sceneId, selfId, param0, param1, param2, param3)
	AddExp(sceneId, selfId, param1);

	local value = GetPlayerGoodBadValue(sceneId, selfId)
	value = value + param2
	SetPlayerGoodBadValue(sceneId, selfId, value)

	if param3 == 0 then
		local targetGUID = GetMasterGUID(sceneId, selfId);
		if targetGUID == tonumber(-1) then
			return
		end
		
		local MasterName = GetFriendName( sceneId, selfId, targetGUID )
		if MasterName == "" then
			return
		end
	
		local selfName	= GetName( sceneId, selfId )

		local nExp = param1 * 30 / 100
		local nCachet = param2 * 30 / 100
	
		SendScriptMail( sceneId, MasterName, MAIL_MASTER_AWARD, nExp, nCachet, 1, selfId )
		local szMsg = format("恭喜您!由于您徒弟%s的徒弟升级，您获得了%d点经验和%d点威望的奖励。", selfName,nExp,nCachet)
		--SendNormalMail( sceneId, selfId, MasterName, szMsg )
		SendSystemMail( sceneId, MasterName, szMsg )
	end
end
