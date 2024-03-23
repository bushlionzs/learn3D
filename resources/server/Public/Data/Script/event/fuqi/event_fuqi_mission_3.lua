
--MisDescBegin
x300352_g_ScriptId = 300352
x300352_g_LevelLess = 40
--MisDescEnd

x300352_g_FatherMissionId = SPOUSE_TASK[2]
x300352_g_FatherMissionName = "【夫妻任务】"
x300352_g_MissionId = SPOUSE_TASK[3]
x300352_g_MissionName ="【夫妻任务】"
x300352_g_MissionItem = 13080010

function x300352_IsMissionComplete(sceneId, selfId, MissionId) 
  local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )
  return GetQuestParam( sceneId, selfId, misIndex, 7 )
end

function x300352_SetMissionComplete(sceneId, selfId, MissionId) 
  local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )
  SetQuestByIndex( sceneId, selfId, misIndex, 7, 1 )
end


function x300352_SetMissionData(sceneId, selfId)
		SetQuestData(sceneId, selfId, MD_SPOUSE_MISSION_DATE[1][1], MD_SPOUSE_MISSION_DATE[1][2], MD_SPOUSE_MISSION_DATE[1][3], GetDayOfYear())
end

function x300352_SubmitFatherMissionCheck(sceneId, selfId, NPCId)
	local teamSize = GetTeamSize(sceneId, selfId)
	local targetId = GetTeamSceneMember(sceneId, selfId, 0);
	
	if HasTeam(sceneId, selfId) ~= 1 then
		return "很抱歉，您还未进行组队无法提交本任务。"
	end
	
	if (GetTeamSize(sceneId, selfId) < 2) then
		return "很抱歉，您所在的队伍中成员小于2人，无法提交本任务。";
	end
	
	if (GetTeamSize(sceneId, selfId) > 2) then
		return "很抱歉，您所在的队伍中成员大于2人，无法提交本任务。";
	end
	
	if IsInDist(sceneId, selfId, targetId, 10) ~= 1 then
		return "很抱歉，您与配偶不在有效的距离内，无法进行本任务。";
	end
	
	if IsSpouses(sceneId, selfId, targetId) ~= 1 then
		return "很抱歉，您所在的队伍中成员不是夫妻关系，无法提交本任务。";
	end		
	
	if IsHaveQuestNM( sceneId, selfId, x300352_g_FatherMissionId ) ~= 1 then
		return "您没有本任务，无法提交本任务。"
	end
	
	if IsHaveQuestNM( sceneId, targetId, x300352_g_FatherMissionId ) ~= 1 then
		return "您的配偶没有本任务，无法提交本任务。"
	end
	
	if GetSex(sceneId, selfId) == 0 then
		return "很抱歉，只有男性才能提交本任务。";
	end
	
	local BusID  =  GetBusId(sceneId, selfId)
	if BusID == -1 then
		return "您的配偶负责护送，请让您的配偶来提交。";
	end
	if IsInDist(sceneId, selfId, BusID, 10) ~= 1 then
		return "您距离您护送的孩童太远了，他迷路了，正在原地等您！";
	end
		
	return nil
end

function x300352_DoUseItem( sceneId, selfId )
	if HasTeam(sceneId, selfId) ~= 1 then
		return "很抱歉，您还未和您的配偶组队无法使用本物品。"
	end
	
	if (GetTeamSize(sceneId, selfId) < 2) then
		return "很抱歉，您所在的队伍中成员小于2人，无法使用本物品。";
	end
	
	if (GetTeamSize(sceneId, selfId) > 2) then
		return "很抱歉，您所在的队伍中成员大于2人，无法使用本物品。";
	end

	local targetId = GetTeamSceneMember(sceneId, selfId, 0);
	
	if IsInDist(sceneId, selfId, targetId, 10) ~= 1 then
		return "很抱歉，您的另一半不在附近，不能使用该物品。";
	end
	
	if IsSpouses(sceneId, selfId, targetId) ~= 1 then
		return "很抱歉，您所在的队伍中成员不是夫妻关系，无法使用本物品。";
	end		
	
	return nil
end

function x300352_AcceptCheck( sceneId, selfId )
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
		return "很抱歉，您与配偶不在有效的距离内，无法进行本任务。";
	end
	
	if IsSpouses(sceneId, selfId, targetId) ~= 1 then
		return "很抱歉，您所在的队伍中成员不是夫妻关系，无法领取本任务。";
	end		
	
	local bHaveMission = IsHaveQuest(sceneId, targetId, x300352_g_MissionId)
	if bHaveMission == 1 then
		return "您的配偶有" .. x300352_g_MissionName .. "，无法接取本任务。"
	end
	
	bHaveMission = IsHaveQuest(sceneId, selfId, x300352_g_MissionId)
	if bHaveMission == 1 then
		return "您有" .. x300352_g_MissionName .. "，无法接取本任务。"
	end
	
	local BusID  =  GetBusId(sceneId, selfId)
	if BusID == -1 then
		return "您不负责护送，所以无法领取任务：" .. x300352_g_MissionName
	else
		if 0 >= IsValidMyselfBus(sceneId, selfId, x300352_g_FatherMissionId) then
			return "您护送的目标不在附近，无法接取本任务。"
		end
	end
	
	
	
	
	
	BeginAddItem(sceneId)
  AddItem( sceneId, x300352_g_MissionItem, 1 )
  local ret = EndAddItem(sceneId,selfId)
  if ret <= 0 then
  		return "您物品栏已满，请整理。"
  end
  
  BeginAddItem(sceneId)
  AddItem( sceneId, x300352_g_MissionItem, 1 )
  ret = EndAddItem(sceneId,targetId)
  if ret <= 0 then
  		return "您配偶的物品栏已满，您的配偶需要整理物品栏。"
  end                 
  
	return nil
end

function x300352_DoAccept( sceneId, selfId )
	
	local week = GetWeek()
	
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
		return "很抱歉，您与配偶不在有效的距离内，无法进行本任务。";
	end
	
	if IsSpouses(sceneId, selfId, targetId) ~= 1 then
		return "很抱歉，您所在的队伍中成员不是夫妻关系，无法领取本任务。";
	end		
	
	local today = GetDayOfYear()
	
	for i = 0, teamSize - 1 do
		local targetId = GetNearTeamMember(sceneId, selfId, i)
		local completeDay = GetQuestData(sceneId, targetId, MD_SPOUSE_MISSION_DATE[1][1], MD_SPOUSE_MISSION_DATE[1][2],MD_SPOUSE_MISSION_DATE[1][3])
		if( completeDay == today) then
			return "您队伍中有人领取了本任务，今天无法接取本任务。"
		end
	end
	
	local bHaveMission = IsHaveQuest(sceneId, selfId, x300352_g_MissionId)
	if bHaveMission == 1 then
		return "您已经接取了本任务，快去完成吧。"
	end
	
	for i = 0, teamSize - 1 do
		local targetId = GetNearTeamMember(sceneId, selfId, i)
		local bHaveMission = IsHaveQuest(sceneId, targetId, x300352_g_MissionId)
		if bHaveMission == 1 then
			return "您队伍中有人有本任务，无法接取本任务。"
		end
	end

	for i = 0, teamSize - 1 do
		local aId = GetNearTeamMember(sceneId, selfId, i)
		local aName = GetName(sceneId, aId)
		local errorCode = AddQuestNM( sceneId, aId, x300352_g_MissionId )
		if errorCode ~= 1 then
			Msg2Player(sceneId,selfId,"添加任务失败！",8,2)
		end
	end

	return nil
end

--**********************************

--任务入口函数

--**********************************

function x300352_ProcEventEntry( sceneId, selfId, targetId, MissionId, index )
	local retCode = x300352_SubmitFatherMissionCheck(sceneId, selfId, targetId)
	if retCode ~= nil then
		Msg2Player(sceneId,selfId,retCode,8,2)
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, retCode);
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return
		--BeginQuestEvent(sceneId)
		--AddQuestText(sceneId,retCode)
		--EndQuestEvent()
		--DispatchQuestDemandInfo(sceneId, selfId, targetId, x300352_g_ScriptId, MissionId,0);
		--return
	end
	
	BeginQuestEvent(sceneId)
--任务信息
	AddQuestText(sceneId,"")
	AddQuestText(sceneId,"")

	--任务目标
	AddQuestText(sceneId,"")
	AddQuestText(sceneId,"#Y【夫妻】护送孩童#W#r\t谢谢你们把阿离送回来，一路上辛苦了。#r\t我这里没有什么稀罕东西，这是我从波斯带来的：@item_13080010#W。拿着它去大都中间点燃，您的另一半一定会喜欢的！")

	EndQuestEvent()
  DispatchQuestContinueInfoNM(sceneId, selfId, targetId, x300352_g_ScriptId, x300352_g_MissionId);
end

--**********************************

--列举事件

--**********************************
--5	非循环任务	未接	1
--6	非循环/循环任务	未完成	2
--7	非循环任务	已完成	3
function x300352_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
	if IsMarried(sceneId, selfId) ~= 1 then
		return
	end
	if IsHaveQuestNM( sceneId, selfId, x300352_g_FatherMissionId ) == 1 then
		AddQuestNumText(sceneId, x300352_g_ScriptId, x300352_g_FatherMissionName, 7, -1)
	end
	
end



--**********************************

--检测接受条件

--**********************************

function x300352_ProcAcceptCheck(sceneId, selfId, NPCId)

	--if HasTeam(sceneId, selfId) == 1 then
		return 1
	--end
end

--**********************************

--接受

--**********************************
function x300352_ProcQuestAccept( sceneId, selfId, targetId, MissionId )
	local str = x300352_DoAccept( sceneId, selfId )
	if str ~= nil then
		Msg2Player(sceneId,selfId,str,8,2)
	end
	
end



--**********************************

--放弃

--**********************************

function x300352_ProcQuestAbandon(sceneId, selfId, MissionId)
	DelQuestNM( sceneId, selfId, MissionId )
	
	--local MissionName = GetQuestNameNM( sceneId, selfId, MissionId )
	local message = "您放弃了夫妻任务"
	BeginQuestEvent(sceneId);
		AddQuestText(sceneId, message);
	EndQuestEvent();
	DispatchQuestTips(sceneId, selfId);
	Msg2Player(sceneId, selfId, message, 4, 2);
	
	DelItem(sceneId, selfId,x300352_g_MissionItem,1)
	
	x300352_SetMissionData(sceneId, selfId)
	
	--发可执行邮件给配偶
	local spouseGuid = GetSpouseGUID( sceneId, selfId )
	local spouseName = GetFriendName( sceneId, selfId, tonumber(spouseGuid) )
	SendScriptMail( sceneId, spouseName, MAIL_DELETE_MISSION, x300352_g_MissionId, 0, 0, selfId )
	
end



--**********************************

--检测是否可以提交

--**********************************

function x300352_CheckSubmit( sceneId, selfId, MissionId )
	if IsHaveQuestNM( sceneId, selfId, MissionId) == 0 then
		return 0;
	end
	return 1
end



--**********************************

--提交

--**********************************
function x300352_ProcQuestSubmit( sceneId, selfId, targetId, selectId, MissionId )
	
	local submitRetCode = x300352_SubmitFatherMissionCheck(sceneId, selfId, targetId)
	if submitRetCode ~= nil then
		Msg2Player(sceneId,selfId,submitRetCode,8,2)
		return
	end
	
	local retCode = x300352_AcceptCheck(sceneId, selfId)
	if retCode ~= nil then
		Msg2Player(sceneId,selfId,retCode,8,2)
		return
	end

	local spouseId = GetTeamSceneMember(sceneId, selfId, 0);
	
	x300352_SetMissionComplete(sceneId, selfId, x300352_g_FatherMissionId )
	x300352_SetMissionComplete(sceneId, spouseId, x300352_g_FatherMissionId )
	local ret = x300352_IsMissionComplete( sceneId, selfId, x300352_g_FatherMissionId )
	if ret > 0 then
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, "您完成了任务:【夫妻】护送孩童");
		EndQuestEvent();
		Msg2Player(sceneId,selfId,"您完成了任务:【夫妻】护送孩童",8,2)
		DispatchQuestTips(sceneId, selfId);
		
		DelQuestNM( sceneId, selfId, x300352_g_FatherMissionId )
		local errorCode = AddQuestNM( sceneId, selfId, x300352_g_MissionId )
		if errorCode ~= 1 then
			Msg2Player(sceneId,selfId,"添加任务失败！",8,2)
		end
	end

	ret = x300352_IsMissionComplete( sceneId, spouseId, x300352_g_FatherMissionId )
	if ret > 0 then
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, "您完成了任务:【夫妻】护送孩童");
		EndQuestEvent();
		Msg2Player(sceneId,spouseId,"您完成了任务:【夫妻】护送孩童",8,2)
		DispatchQuestTips(sceneId, spouseId);
		
		DelQuestNM( sceneId, spouseId, x300352_g_FatherMissionId )
		local errorCode = AddQuestNM( sceneId, spouseId, x300352_g_MissionId )
		if errorCode ~= 1 then
			Msg2Player(sceneId,spouseId,"添加任务失败！",8,2)
		end
	end

	local BusID  =  GetBusId(sceneId, selfId)
	if BusID ~= -1 then
		if (IsObjValid (sceneId,BusID) == 1) and x300352_g_FatherMissionId == GetBusQuestID(sceneId, BusID ) then
			DeleteBus(sceneId, BusID,1)
		end
	end

	BeginAddItem(sceneId)
  AddItem( sceneId, x300352_g_MissionItem, 1 )
  local ret = EndAddItem(sceneId,selfId)
  if ret > 0 then
      AddItemListToPlayer(sceneId,selfId)
  end
  
  BeginAddItem(sceneId)
  AddItem( sceneId, x300352_g_MissionItem, 1 )
  ret = EndAddItem(sceneId,spouseId)
  if ret > 0 then
      AddItemListToPlayer(sceneId,spouseId)
  end
  
	return 0
	
end



--**********************************

--杀死怪物或玩家

--**********************************

function x300352_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
end

--**********************************

--道具改变

--**********************************

function x300352_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
end

function x300352_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )

	if IsHaveQuestNM( sceneId, selfId, MissionId) == 0 then	-- 如果没有这个任务
		return
	end
	
end

function x300352_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	if IsHaveQuestNM( sceneId, selfId, x300352_g_MissionId ) == 0 then	-- 如果没这个任务直接退出
		return 0
	end
	local misIndex = GetQuestIndexByID( sceneId, selfId, x300352_g_MissionId )
	if GetQuestParam( sceneId, selfId, misIndex, 1 ) == 1 then
		return 0
	end
	
	local scene = 0
	local posx = 127
	local posz = 127
	local radii = 10
	if scene == -1 or sceneId ~= scene then --没有找到这个任务信息
		return 0
	end
	
	if posx > 0 then --需要检查地点
		local PlayerPosX,PlayerPosZ = GetWorldPos( sceneId, selfId )

		local distanceRet = radii * radii - (posx - PlayerPosX) * (posx - PlayerPosX) - (posz - PlayerPosZ) * (posz - PlayerPosZ)
		if distanceRet <= 0 then
			local strText = format("很抱歉，这里不能使用该物品，请到@sceneid_%d(%d,%d)处使用!", scene, posx, posz )
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, strText)
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId, selfId)
			return 0
		end
	end
	
	local retCode = x300352_DoUseItem(sceneId, selfId)
	if retCode ~= nil then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, retCode)
			DispatchQuestTips(sceneId, selfId)
			EndQuestEvent(sceneId)
			return
	end

	BeginQuestEvent(sceneId)
	AddQuestText(sceneId, "天空绽放出美丽的烟花")
	EndQuestEvent(sceneId)
	DispatchQuestTips(sceneId, selfId)
	
	--删除物品
	EraseItem(sceneId, selfId, BagIndex)

	--播放效果
	if impactId ~= -1 then
		SendSpecificImpactToUnit(sceneId, selfId, selfId, selfId, impactId, 0);
	end
	
	SetQuestByIndex( sceneId, selfId, misIndex, 1, 1 )
	
	local misIndex = GetQuestIndexByID( sceneId, selfId, x300352_g_MissionId )
	SetQuestByIndex( sceneId, selfId, misIndex, 7, 1 )

	return 1
	
end

function x300352_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x300352_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x300352_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x300352_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end

function x300352_QuestLogRefresh( sceneId, selfId, MissionId)

	BeginQuestEvent(sceneId)	
	local level = GetLevel(sceneId, selfId)
	local ExpBonus = 1000 *0.4*10* level
	    if ExpBonus > 0 then
			AddQuestExpBonus(sceneId,  ExpBonus);
		end	
	AddQuestLogCustomText( sceneId,
							"标题",						-- 标题
							"" .. x300352_g_MissionName,        -- 任务名字
							"  去@npc_72049点燃礼花",		--任务目标
							"@npc_139117",			--任务NPC
							"",               --任务攻略
							"到达大都@npc_72049处，和您的爱人一起观赏心心相映礼花后，到@npc_139117那里领取任务奖励",	--任务描述
							""					--任务小提示
							)
	EndQuestEvent()
	DispatchQuestLogUpdate(sceneId, selfId, MissionId);
end

function x300352_ProcQuestLogRefresh( sceneId, selfId, MissionId)

	x300352_QuestLogRefresh( sceneId, selfId, MissionId );
end

function x300352_CheckSubmitNPC( sceneId,selfId,idScript,idMission,npcGUID )
	if IsHaveQuestNM( sceneId, selfId, x300352_g_FatherMissionId ) == 0 then
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