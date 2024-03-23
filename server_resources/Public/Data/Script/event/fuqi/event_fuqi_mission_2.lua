
--MisDescBegin
x300351_g_ScriptId = 300351
x300351_g_LevelLess = 40
--MisDescEnd
x300351_g_BusScriptId = 300354
x300351_g_FatherMissionId = SPOUSE_TASK[1]
x300351_g_FatherMissionName = "【夫妻任务】"
x300351_g_MissionId = SPOUSE_TASK[2]

x300351_g_MissionName ="【夫妻任务】"

function x300351_IsMissionComplete(sceneId, selfId, MissionId) 
  local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )
  return GetQuestParam( sceneId, selfId, misIndex, 7 )
end

function x300351_SetMissionData(sceneId, selfId)
		SetQuestData(sceneId, selfId, MD_SPOUSE_MISSION_DATE[1][1], MD_SPOUSE_MISSION_DATE[1][2], MD_SPOUSE_MISSION_DATE[1][3], GetDayOfYear())
end

function x300351_SubmitFatherMissionCheck(sceneId, selfId, NPCId)
	local teamSize = GetTeamSize(sceneId, selfId)
	local targetId = GetTeamSceneMember(sceneId, selfId, 0);
	
	local week = GetWeek()
	local today = GetDayOfYear()
	if week ~=4 and week ~= 6 then
		return "很抱歉，只有周四、周六，才能进行本任务！"   
	end
	
	if HasTeam(sceneId, selfId) ~= 1 then
		return "很抱歉，您还未进行组队无法提交本任务。"
	end
	
	if (GetTeamSize(sceneId, selfId) < 2) then
		return "很抱歉，您所在的队伍中成员小于2人，无法提交本任务。";
	end
	
	if (GetTeamSize(sceneId, selfId) > 2) then
		return "很抱歉，您所在的队伍中成员大于2人，无法提交本任务。";
	end
	
	-- if GetSex(sceneId, selfId) == 0 then
		
		-- BeginQuestEvent(sceneId)
		-- AddQuestText(sceneId, "很抱歉，只有男性才能提交此任务！");
		-- EndQuestEvent(sceneId)
		-- DispatchQuestTips(sceneId,selfId)
		-- local Readme = "很抱歉，只有男性才能提交此任务！"
		-- Msg2Player(sceneId,selfId,Readme,8,2);
		-- return 
	-- end
	
	if IsInDist(sceneId, selfId, targetId, 10) ~= 1 then
		return "很抱歉，您与配偶不在有效的距离内，无法进行本任务。";
	end
	
	if IsSpouses(sceneId, selfId, targetId) ~= 1 then
		return "很抱歉，您所在的队伍中成员不是夫妻关系，无法提交本任务。";
	end		
	
	if IsHaveQuestNM( sceneId, selfId, x300351_g_FatherMissionId ) ~= 1 then
		return "您没有本任务，无法提交本任务。"
	end
	
	if IsHaveQuestNM( sceneId, targetId, x300351_g_FatherMissionId ) ~= 1 then
		return "您的配偶没有本任务，无法提交本任务。"
	end
	
	local misIndex = GetQuestIndexByID( sceneId, selfId, x300351_g_FatherMissionId )
	if QuestCheckSubmitNM( sceneId, selfId, NPCId, x300351_g_FatherMissionId, misIndex ) <= 0 then
		return "您未完成本任务，无法提交本任务。"
	end
	
	local misIndex = GetQuestIndexByID( sceneId, targetId, x300351_g_FatherMissionId )
	if QuestCheckSubmitNM( sceneId, targetId, NPCId, x300351_g_FatherMissionId, misIndex ) <= 0 then
		return "您的配偶未完成本任务，无法提交本任务。"
	end
	
	return nil
end

--**********************************

--任务入口函数

--**********************************

function x300351_ProcEventEntry( sceneId, selfId, targetId, MissionId, index )
	local misIndex = GetQuestIndexByID( sceneId, selfId, x300351_g_FatherMissionId )
	if QuestCheckSubmitNM( sceneId, selfId, targetId, x300351_g_FatherMissionId, misIndex ) > 0 then
		local submitRetCode = x300351_SubmitFatherMissionCheck(sceneId, selfId, targetId)
		if submitRetCode ~= nil then
			Msg2Player(sceneId,selfId,submitRetCode,8,2)
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, submitRetCode);
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
			return
			--BeginQuestEvent(sceneId)
			--AddQuestText(sceneId,submitRetCode)
			--EndQuestEvent()
			--DispatchQuestDemandInfo(sceneId, selfId, targetId, x300351_g_ScriptId, x300351_g_MissionId,0);
			--return
		end
		local addNextMissionRetCode = x300351_AcceptCheck(sceneId, selfId)
		if addNextMissionRetCode ~= nil then
			Msg2Player(sceneId,selfId,addNextMissionRetCode,8,2)
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, addNextMissionRetCode);
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
			return
			--BeginQuestEvent(sceneId)
			--AddQuestText(sceneId,addNextMissionRetCode)
			--EndQuestEvent()
			--DispatchQuestDemandInfo(sceneId, selfId, targetId, x300351_g_ScriptId, x300351_g_MissionId,0);
			--return
		end
		BeginQuestEvent(sceneId)
	--任务信息
		-- AddQuestText(sceneId,"#Y【夫妻】爱情紫晶")
		-- AddQuestText(sceneId,"\t夫妻任务一#r")

		--任务目标
		AddQuestText(sceneId,"")
		AddQuestText(sceneId,"#Y【夫妻】爱情水晶#W#r\t我需要很多带有爱意的@item_13080009#W来制作爱之槟榔，看来你们已经帮我采到了！#r\t看你们小两口甜甜蜜蜜的样子，真是羡慕死我了，真不知道何时我也找到疼爱我的娘子？#r\t拜托你们两个帮我把淘气的小孩带到@npc_139818那里吧，他已经很久没见爸爸了。#r\t我会为你们的爱情祈祷，祝福你们幸福美满！")

		EndQuestEvent()
	  DispatchQuestContinueInfoNM(sceneId, selfId, targetId, x300351_g_ScriptId, x300351_g_MissionId);
	  return
	end
	
	local str = "您或您的另一半还未完成任务，加油啊"
	Msg2Player(sceneId,selfId,str,8,2)
	BeginQuestEvent(sceneId)
	AddQuestText(sceneId, str);
	EndQuestEvent(sceneId)
	DispatchQuestTips(sceneId,selfId)

end

--**********************************

--列举事件

--**********************************
--5	非循环任务	未接	1
--6	非循环/循环任务	未完成	2
--7	非循环任务	已完成	3
function x300351_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
	if IsMarried(sceneId, selfId) ~= 1 then
		return
	end
	
	if IsHaveQuestNM( sceneId, selfId, x300351_g_FatherMissionId ) == 1 then
		local misIndex = GetQuestIndexByID( sceneId, selfId, x300351_g_FatherMissionId )
		local state = GetQuestStateNM(sceneId, selfId, targetId, x300351_g_FatherMissionId)
		AddQuestNumText(sceneId, x300351_g_ScriptId, x300351_g_FatherMissionName, state, -1)
		return
	end
	
end



--**********************************

--检测接受条件

--**********************************

function x300351_ProcAcceptCheck(sceneId, selfId, NPCId)

	--if HasTeam(sceneId, selfId) == 1 then
		return 1
	--end
end


--**********************************

--检测查看条件

--**********************************

function x300351_CheckPushList(sceneId, selfId, NPCId)
	return 1
end

function x300351_CreateBus(sceneId, selfId)
  local PosX,PosZ = GetWorldPos(sceneId, selfId)
	local busType = 31
	local AIType = 3
	local AIScript = 3
	local IamGodImpactId = 1210
	local ObjID = CreateBus(sceneId, busType, PosX, PosZ, AIType, AIScript, x300351_g_BusScriptId, selfId, IamGodImpactId,-1,-1)
end

function x300351_DeleteBus(sceneId, selfId)

	local BusID  =  GetBusId(sceneId, selfId)
	if BusID ~= -1 then
		if (IsObjValid (sceneId,BusID) == 1) and x300351_g_MissionId == GetBusQuestID(sceneId, BusID ) then
			DeleteBus(sceneId, BusID,1)
		end
	end
	
end

function x300351_AcceptCheck(sceneId, selfId)
	local week = GetWeek()
	local teamSize = GetTeamSize(sceneId, selfId)
	if week ~= 4 and week ~= 6 then
		return "只有周四、周六，才能进行本任务。"
	end
	
	if HasTeam(sceneId, selfId) ~= 1 then
		return "很抱歉，您还未进行组队无领取本任务。"
	end
	
	if (GetTeamSize(sceneId, selfId) < 2) then
		return "很抱歉，您所在的队伍中成员小于2人，无法领取本任务。";
	end
	
	if (GetTeamSize(sceneId, selfId) > 2) then
		return "很抱歉，您所在的队伍中成员大于2人，无法领取本任务。";
	end

	local targetId = GetTeamSceneMember(sceneId, selfId, 0);
	
	if IsInDist(sceneId, selfId, targetId, 10) ~= 1 then
		return "很抱歉，您与队友不在有效的距离内，无法领取本任务。";
	end
	
	if IsSpouses(sceneId, selfId, targetId) ~= 1 then
		return "很抱歉，您所在的队伍中成员不是夫妻关系，无法领取本任务。";
	end		
	
	if GetSex(sceneId, selfId) == 0 then
		return "很抱歉，请让您的另一半来进行本任务。";
	end
	
	local bHaveMission = IsHaveQuest(sceneId, targetId, x300351_g_MissionId)
	if bHaveMission == 1 then
		return "您的配偶有" .. x300351_g_MissionName .. "，无法接取本任务。"
	end
	
	bHaveMission = IsHaveQuest(sceneId, selfId, x300351_g_MissionId)
	if bHaveMission == 1 then
		return "您有" .. x300351_g_MissionName .. "，无法接取本任务。"
	end
	
	if IsBusMember(sceneId, selfId) == 1 then
		return "您正在护送，无法接取本任务。"
	end
			
	return nil
end
	
function x300351_DoAccept( sceneId, selfId )

	local retCode = x300351_AcceptCheck(sceneId, selfId)
	if retCode ~= nil then
		return retCode
	end
	local teamSize = GetTeamSize(sceneId, selfId)
	for i = 0, teamSize - 1 do
		local aId = GetNearTeamMember(sceneId, selfId, i)
		local aName = GetName(sceneId, aId)
		local errorCode = AddQuestNM( sceneId, aId, x300351_g_MissionId )
		if errorCode ~= 1 then
			Msg2Player(sceneId,aId,"添加任务失败！",8,2)
		end
		
	end
	x300351_CreateBus(sceneId, selfId)
	
	
	return nil
end

--**********************************

--接受

--**********************************
function x300351_ProcQuestAccept( sceneId, selfId, targetId, MissionId )
	local str = x300351_DoAccept( sceneId, selfId )
	if str ~= nil then
		Msg2Player(sceneId,selfId,str,8,2)
	end
	
end



--**********************************

--放弃

--**********************************

function x300351_ProcQuestAbandon(sceneId, selfId, MissionId)
	DelQuestNM( sceneId, selfId, MissionId )
	
	--local MissionName = GetQuestNameNM( sceneId, selfId, MissionId )
	local message = "您放弃了夫妻任务"
	BeginQuestEvent(sceneId);
		AddQuestText(sceneId, message);
	EndQuestEvent();
	DispatchQuestTips(sceneId, selfId);
	Msg2Player(sceneId, selfId, message, 4, 2);
	
	x300351_DeleteBus(sceneId, selfId)
	
	x300351_SetMissionData(sceneId, selfId)
	
	--发可执行邮件给配偶
	local spouseGuid = GetSpouseGUID( sceneId, selfId )
	local spouseName = GetFriendName( sceneId, selfId, tonumber(spouseGuid) )
	SendScriptMail( sceneId, spouseName, MAIL_DELETE_MISSION, x300351_g_MissionId, 1, 0, selfId )
end



--**********************************

--检测是否可以提交

--**********************************

function x300351_CheckSubmit( sceneId, selfId, MissionId )
	if IsHaveQuestNM( sceneId, selfId, MissionId) == 0 then
		return 0;
	end
	return 1
end



--**********************************

--提交

--**********************************
function x300351_ProcQuestSubmit( sceneId, selfId, targetId, selectId, MissionId )
	
	local submitRetCode = x300351_SubmitFatherMissionCheck(sceneId, selfId, targetId)
	if submitRetCode ~= nil then
		Msg2Player(sceneId,selfId,submitRetCode,8,2)
		return
	end
	
	local retCode = x300351_AcceptCheck(sceneId, selfId)
	if retCode ~= nil then
		Msg2Player(sceneId,selfId,retCode,8,2)
		return
	end
	local spouseId = GetTeamSceneMember(sceneId, selfId, 0);
	
	local ret = x300351_IsMissionComplete( sceneId, selfId, x300351_g_FatherMissionId )
	if ret > 0 then
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, "您完成了任务:【夫妻】爱情紫晶");
		EndQuestEvent();
		Msg2Player(sceneId,selfId,"您完成了任务:【夫妻】爱情紫晶",8,2)
		DispatchQuestTips(sceneId, selfId);
		
		DelQuestNM( sceneId, selfId, x300351_g_FatherMissionId )
		local errorCode = AddQuestNM( sceneId, selfId, x300351_g_MissionId )
		if errorCode ~= 1 then
			Msg2Player(sceneId,selfId,"添加任务失败！",8,2)
		end
	end

	ret = x300351_IsMissionComplete( sceneId, spouseId, x300351_g_FatherMissionId )
	if ret > 0 then
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, "您完成了任务:【夫妻】爱情紫晶");
		EndQuestEvent();
		Msg2Player(sceneId,spouseId,"您完成了任务:【夫妻】爱情紫晶",8,2)
		DispatchQuestTips(sceneId, spouseId);
		
		DelQuestNM( sceneId, spouseId, x300351_g_FatherMissionId )
		local errorCode = AddQuestNM( sceneId, spouseId, x300351_g_MissionId )
		if errorCode ~= 1 then
			Msg2Player(sceneId,spouseId,"添加任务失败！",8,2)
		end
	end
	x300351_CreateBus(sceneId, selfId)
	return 0
	
end

--**********************************

--杀死怪物或玩家

--**********************************

function x300351_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
end



--**********************************

--进入区域事件

--**********************************

function x300351_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)
	

end

function x300351_ProcTiming(sceneId, selfId )
	 
		
end

function x300351_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId )
	
end



--**********************************

--道具改变

--**********************************

function x300351_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
    
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
			local strText = format("已得到@itemid_%d: %d/%d", itemdataId, Num, NeedNum )
			if strText == nil then
				strText = "";
			end
			AddQuestText( sceneId, strText )
			EndQuestEvent( sceneId )
			DispatchQuestTips( sceneId, selfId )
   			SetQuestByIndex( sceneId, selfId, misIndex, ObjIndex, Num )
  		elseif Num == NeedNum then
			--已经完成任务
			BeginQuestEvent(sceneId)
			local strText = format( "已得到足够的@itemid_%d: %d/%d", itemdataId, Num, NeedNum )
			if strText == nil then
				strText = "";
			end
			AddQuestText( sceneId, strText )
			EndQuestEvent( sceneId )
			DispatchQuestTips( sceneId, selfId )
			SetQuestByIndex( sceneId, selfId, misIndex, 7, 1 )
		end
	end
end
function x300351_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )

	if IsHaveQuestNM( sceneId, selfId, MissionId) == 0 then	-- 如果没有这个任务
		return
	end
	
end

function x300351_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x300351_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x300351_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x300351_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x300351_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end

function x300351_QuestLogRefresh( sceneId, selfId, MissionId)

	BeginQuestEvent(sceneId)	
		
	AddQuestLogCustomText( sceneId,
							"标题",						-- 标题
							"" .. x300351_g_MissionName,        -- 任务名字
							"  将#G淘气的小孩#W护送到@npc_139818处",		--任务目标
							"@npc_139818",			--任务NPC
							"",               --任务攻略
							"韩山童在等待他的孩子，将小孩安全送到@npc_139818那里。护送途中小孩只会跟随男性玩家移动",	--任务描述
							"护送过程中，夫妻双方不能离开护送目标过远，或时间过久，否则任务会失败！#r护送孩童只有男性才能提交任务"					--任务小提示
							)
	EndQuestEvent()
	DispatchQuestLogUpdate(sceneId, selfId, MissionId);
end

function x300351_ProcQuestLogRefresh( sceneId, selfId, MissionId)
	x300351_QuestLogRefresh( sceneId, selfId, MissionId );
end

function x300351_CheckSubmitNPC( sceneId,selfId,idScript,idMission,npcGUID )
	if IsHaveQuestNM( sceneId, selfId, x300351_g_FatherMissionId ) == 0 then
		-- 如果没有这个任务
		return 0
	end
	for i, npcItem in SPOUSE_NPC do
		if npcItem == npcGUID then
			return 1
		end
	end
	return 0
end