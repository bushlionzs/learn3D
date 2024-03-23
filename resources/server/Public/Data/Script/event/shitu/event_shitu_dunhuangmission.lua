--师徒任务
x310304_g_ScriptId = 310304
x310304_g_MissionType = {
EnterPos = 1,
UseItem = 2,
KillMonster = 3
}
x310304_g_LookAtPosId = 82052
x310304_g_MissionId = {
{id = 9525,type = x310304_g_MissionType.EnterPos},
{id = 9526,type = x310304_g_MissionType.UseItem},
{id = 9527,type = x310304_g_MissionType.KillMonster}
}

x310304_g_UseItemPos = {
{id = 82053, x = 129, z = 228},
{id = 82054, x = 191, z = 220},
{id = 82055, x = 35, z = 162}
}
x310304_g_MissionName = "【师徒】师徒齐心"
x310304_g_areaId = 3
x310304_g_MasterDistance = 15
x310304_g_MissionItem = 12030029
x310304_g_FirstMissionId = x310304_g_MissionId[1].id
x310304_g_SecondMissionId = x310304_g_MissionId[2].id
x310304_g_ThirdMissionId = x310304_g_MissionId[3].id
x310304_g_LimitTimes = 1
x310304_g_Monster = {
{level = 50, monster = 3230},
{level = 55, monster = 3231},
{level = 60, monster = 3232},
{level = 65, monster = 3233},
{level = 70, monster = 3234},
{level = 75, monster = 3235},
{level = 80, monster = 3236}
}

x310304_g_MonsterAI = 6
x310304_g_MonsterAliveTime = 10*60*1000
x310304_g_GoodBadValue = 2000
x310304_g_ExpRate = 30000
function x310304_GetMonsterId(level)
	local id = -1
	for i, item in x310304_g_Monster do
		if level >= item.level then
			id = item.monster
		end
	end
	return id
end

function x310304_GetMissionTimes(sceneId, selfId)
	if GetQuestData(sceneId, selfId, MD_MASTER_PRENTICE_COM_DAY[1], MD_MASTER_PRENTICE_COM_DAY[2], MD_MASTER_PRENTICE_COM_DAY[3]) ~= GetDayOfYear() then
		return 0
	else
		return GetQuestData(sceneId, selfId, MD_MASTER_PRENTICE_COM_TIMES[1], MD_MASTER_PRENTICE_COM_TIMES[2], MD_MASTER_PRENTICE_COM_TIMES[3])
	end
end

function x310304_HaveWhichMission(sceneId, selfId)
	for i, item in x310304_g_MissionId do
		if IsHaveQuestNM( sceneId, selfId, item.id ) == 1 then
			return item.id
		end
	end
	return -1
end

function x310304_HaveDoneWhichMission(sceneId, selfId)
	for i, item in x310304_g_MissionId do
		if IsHaveQuestNM( sceneId, selfId, item.id ) == 1 then
			local misIndex = GetQuestIndexByID( sceneId, selfId, item.id )
			if GetQuestParam( sceneId, selfId, misIndex, 7 ) == 1 then
				return item.id
			end
		end
	end
	return -1
end

function x310304_GetMissionType(sceneId, selfId)
	for i, item in x310304_g_MissionId do
		if IsHaveQuestNM( sceneId, selfId, item.id ) == 1 then
			return item.type
		end
	end
	return -1
end

function x310304_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
	local level = GetLevel(sceneId, selfId)
	
	if level < 20 then
		return
	end
	MissionId = x310304_g_FirstMissionId
	local state = 8
	local haveMissionId = x310304_HaveWhichMission(sceneId, selfId)
	local haveDoneMissionId = x310304_HaveDoneWhichMission(sceneId, selfId)
	if haveMissionId > 0 then
		state = 6
		MissionId = haveMissionId
	end
	
	if haveDoneMissionId > 0 then
		state = 7
	end
	AddQuestNumText(sceneId, MissionId, x310304_g_MissionName, state, -1)
	
end

function x310304_GetMasterObjId(sceneId, selfId)
	if nil ~= x310304_IsMasterHere(sceneId, selfId) then
		return -1
	end
	local teamSize = GetTeamSize(sceneId, selfId)
	local nMasterObjId = -1
	for i = 0, teamSize - 1 do
		local targetId = GetTeamMemberId(sceneId, selfId, i)
		if 1 == IsInDist(sceneId, selfId, targetId, x310304_g_MasterDistance) then
			if 1 == GetObjType(sceneId, targetId) and 1 == IsMaster(sceneId, selfId, targetId) then
				nMasterObjId = targetId
			end
		end
	end
	
	return nMasterObjId
	
end

function x310304_IsMasterHere(sceneId, selfId)
	local teamSize = GetTeamSize(sceneId, selfId)
	if (teamSize < 2) then
		return "你的队伍中不足2人，无法进行本任务。";
	end
	
	local isMasterHere = 0
	for i = 0, teamSize - 1 do
		local targetId = GetTeamMemberId(sceneId, selfId, i)
		if 1 == IsInDist(sceneId, selfId, targetId, x310304_g_MasterDistance) then
			if 1 == GetObjType(sceneId, targetId) and 1 == IsMaster(sceneId, selfId, targetId) then
				isMasterHere = 1
			end
		end
	end
	
	if 0 == isMasterHere then
		return "你的师傅不在队伍中或者不在附近，无法进行本任务。";
	end
	return nil
end

function x310304_IsCanSubmit( sceneId, selfId )
	local teamSize = GetTeamSize(sceneId, selfId)
	if (teamSize < 2) then
		return "你的队伍中不足2人，无法提交本任务。";
	end
	
	local isMasterHere = 0
	for i = 0, teamSize - 1 do
		local targetId = GetTeamMemberId(sceneId, selfId, i)
		if 1 == IsInDist(sceneId, selfId, targetId, x310304_g_MasterDistance) then
			if 1 == GetObjType(sceneId, targetId) and 1 == IsMaster(sceneId, selfId, targetId) then
				isMasterHere = 1
			end
		end
	end
	
	if 0 == isMasterHere then
		return "你的师傅不在队伍中或者不在附近，无法提交本任务。";
	end
	return nil
end

function x310304_ProcEventEntry( sceneId, selfId, targetId, MissionId, index )
	local haveMissionId = x310304_HaveWhichMission(sceneId, selfId)
	local haveDoneMissionId = x310304_HaveDoneWhichMission(sceneId, selfId)
	if haveDoneMissionId > 0 then
		local str = x310304_IsCanSubmit( sceneId, selfId )
		if str ~= nil then
			Msg2Player(sceneId,selfId,str,8,2)
			BeginQuestEvent(sceneId);
			AddQuestText(sceneId, str);
			EndQuestEvent();
			DispatchQuestTips(sceneId, selfId);
			return
		end
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"\t恭喜您，完成了师徒任务！")
		local exp = x310304_CalculateExp(sceneId, selfId)
		local szAward = "\n#Y奖励内容：\n#W经验值:"..exp.."点"
		AddQuestText(sceneId, szAward)
		EndQuestEvent()
		DispatchQuestContinueInfoNM(sceneId, selfId, targetId, x310304_g_ScriptId, MissionId);
		return
	end
	if haveMissionId > 0 then
		BeginQuestEvent(sceneId)
		if x310304_g_MissionType.EnterPos == x310304_GetMissionType(sceneId, selfId) then
			AddQuestText(sceneId,"#Y这么快就回来了？你们一定还没有侦查清楚。")
		else
			AddQuestText(sceneId,"#Y你还没有完成任务。")
		end
		EndQuestEvent()
		DispatchQuestDemandInfo(sceneId, selfId, targetId, x310304_g_ScriptId, MissionId,0);
	  return
	end
	BeginQuestEvent(sceneId)
	AddQuestText(sceneId,"#Y师徒任务")
	local str = format("\t很高兴你们师徒两人能一起来我这里。\n\t最近王国境内有不少盗匪出没，有传言说，这些盗匪其实是受了海都大王的蛊惑才会频频作乱。\n\t为了弄清真相，你们师徒两人前去侦查一番如何？\n\t师傅获得威望奖励，徒弟获得经验奖励，师傅每带1名徒弟完成任务都会获得%s威望。徒弟每天只可接%s次任务，师傅没有任务，但师傅必须在徒弟身边，徒弟才能进行任务。", x310304_g_GoodBadValue, x310304_g_LimitTimes)
	AddQuestText(sceneId,str)
	AddQuestText(sceneId,"#Y任务目标：")
	local target = "\t#W到圣山东麓侦查敌军，然后使用狼烟并杀死头领。"
	AddQuestText(sceneId,target)
	AddQuestText(sceneId,"#Y任务奖励：")
	local exp = x310304_CalculateExp(sceneId, selfId)
	AddQuestText(sceneId,format("\t#W徒弟获得经验：徒弟等级*%s点", x310304_g_ExpRate))
	AddQuestText(sceneId,format("\t#W师傅获得威望：%s点", x310304_g_GoodBadValue))
	EndQuestEvent()

	DispatchQuestInfo(sceneId, selfId, targetId, x310304_g_FirstMissionId, -1)
end

function x310304_ProcQuestAccept( sceneId, selfId, targetId, MissionId )
	local str = x310304_DoAccept( sceneId, selfId )
	if str ~= nil then
		Msg2Player(sceneId,selfId,str,8,2)
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, str);
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
		return
	end
	
	local masterObjId = x310304_GetMasterObjId(sceneId, selfId)
	local szPrenticeName = GetName(sceneId, selfId)
	local szMsg = format("%s接受了师徒任务，请你协助完成任务，会有威望奖励。", szPrenticeName)
	
	Msg2Player(sceneId, masterObjId, szMsg, 8, 2)
	BeginQuestEvent(sceneId);
	AddQuestText(sceneId, szMsg);
	EndQuestEvent();
	DispatchQuestTips(sceneId, masterObjId);
	
end

function x310304_DoAccept( sceneId, selfId )
	
	local level = GetLevel(sceneId, selfId)
	
	if level >= 50 and 0 >= IsHavePrentice(sceneId, selfId) then
		return "你还不是师傅,收了徒弟之后再来找我吧。"
	end
	
	if 1 == IsHavePrentice(sceneId, selfId) then
		return "请让你的徒弟来接取本任务。";
	end
	
	local teamSize = GetTeamSize(sceneId, selfId)
	if (teamSize < 2) then
		return "你的队伍中不足2人，无法接取本任务。";
	end
	
	local isMasterHere = 0
	for i = 0, teamSize - 1 do
		local targetId = GetTeamMemberId(sceneId, selfId, i)
		if 1 == IsInDist(sceneId, selfId, targetId, x310304_g_MasterDistance) then
			if 1 == GetObjType(sceneId, targetId) and 1 == IsMaster(sceneId, selfId, targetId) then
				isMasterHere = 1
			end
		end
	end
	
	if 0 == isMasterHere then
		return "你的师傅不在队伍中或者不在附近，无法接取本任务。";
	end
	
	if IsQuestFullNM(sceneId, selfId) == 1 then
		return "很抱歉，你的任务已经满了，无法领取本任务。"
	end
	
	if x310304_GetMissionTimes(sceneId, selfId) >= x310304_g_LimitTimes then
		return format("很抱歉，本日的任务次数已经达到%s次，无法领取本任务。", x310304_g_LimitTimes)
	end
	local errorCode = AddQuestNM( sceneId, selfId, x310304_g_FirstMissionId )
	if errorCode ~= 1 then
		return "添加任务失败！"
	end
	
	if GetQuestData(sceneId, selfId, MD_MASTER_PRENTICE_COM_DAY[1], MD_MASTER_PRENTICE_COM_DAY[2], MD_MASTER_PRENTICE_COM_DAY[3]) ~= GetDayOfYear() then
		SetQuestData(sceneId, selfId, MD_MASTER_PRENTICE_COM_DAY[1], MD_MASTER_PRENTICE_COM_DAY[2], MD_MASTER_PRENTICE_COM_DAY[3], GetDayOfYear())
		SetQuestData(sceneId, selfId, MD_MASTER_PRENTICE_COM_TIMES[1], MD_MASTER_PRENTICE_COM_TIMES[2], MD_MASTER_PRENTICE_COM_TIMES[3], 1)
	else
		local times = GetQuestData(sceneId, selfId, MD_MASTER_PRENTICE_COM_TIMES[1], MD_MASTER_PRENTICE_COM_TIMES[2], MD_MASTER_PRENTICE_COM_TIMES[3])
		times = times + 1
		SetQuestData(sceneId, selfId, MD_MASTER_PRENTICE_COM_TIMES[1], MD_MASTER_PRENTICE_COM_TIMES[2], MD_MASTER_PRENTICE_COM_TIMES[3], times)
	end
	
	GamePlayScriptLog(sceneId, selfId, 1291)
	return nil
end

function x310304_CalculateExp(sceneId, selfId)
	local level = GetLevel(sceneId, selfId)
	local exp = level * x310304_g_ExpRate
	return exp
end

function x310304_ProcQuestSubmit( sceneId, selfId, targetId, selectId, MissionId )
	local haveMissionId = x310304_HaveWhichMission(sceneId, selfId)
	local missionType = x310304_GetMissionType(sceneId, selfId)
	if missionType < 0 then
		return
	end
	
	local str = x310304_IsCanSubmit( sceneId, selfId )
	if str ~= nil then
		Msg2Player(sceneId,selfId,str,8,2)
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, str);
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
		return
	end
	
	if x310304_g_MissionType.KillMonster == missionType then
		
		if GetQuestData(sceneId, selfId, MD_MASTER_PRENTICE_COM_DAY[1], MD_MASTER_PRENTICE_COM_DAY[2], MD_MASTER_PRENTICE_COM_DAY[3]) ~= GetDayOfYear() then
			SetQuestData(sceneId, selfId, MD_MASTER_PRENTICE_COM_DAY[1], MD_MASTER_PRENTICE_COM_DAY[2], MD_MASTER_PRENTICE_COM_DAY[3], GetDayOfYear())
			SetQuestData(sceneId, selfId, MD_MASTER_PRENTICE_COM_TIMES[1], MD_MASTER_PRENTICE_COM_TIMES[2], MD_MASTER_PRENTICE_COM_TIMES[3], 1)
		end
		
		DelQuestNM( sceneId, selfId, haveMissionId )
		--师傅奖励
		local masterObjId = x310304_GetMasterObjId(sceneId, selfId)
		local value = GetPlayerGoodBadValue(sceneId, masterObjId)
		value = value + x310304_g_GoodBadValue
		SetPlayerGoodBadValue(sceneId, masterObjId, value)
		local str = format("你的徒弟已完成任务你获得%d点威望。", x310304_g_GoodBadValue)
		Msg2Player(sceneId,masterObjId,str,8,2)
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, str);
		EndQuestEvent();
		DispatchQuestTips(sceneId, masterObjId);
		--徒弟奖励
		local exp = x310304_CalculateExp(sceneId, selfId)
		AddExp(sceneId, selfId, exp);
		str = format("你已完成任务你获得%d点经验的奖励。", exp)
		Msg2Player(sceneId,selfId,str,8,2)
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, str);
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
		GamePlayScriptLog(sceneId, selfId, 1292)
	else
		DelQuestNM( sceneId, selfId, haveMissionId )
		AddQuestNM( sceneId, selfId, x310304_g_SecondMissionId )
		local misIndex = GetQuestIndexByID( sceneId, selfId, x310304_g_SecondMissionId )
		SetQuestByIndex( sceneId, selfId, misIndex, 0, 0 )
		SetQuestByIndex( sceneId, selfId, misIndex, 6, random(1,3) )
	end
end

function x310304_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )

	if IsHaveQuestNM( sceneId, selfId, MissionId) == 0 then	-- 如果没有这个任务
		return
	end
	
end

function x310304_ProcAreaEntered( sceneId, selfId, areaId, MissionId )
	if areaId ~= x310304_g_areaId then
		return
	end
	local misIndex
	local missionType = x310304_GetMissionType(sceneId, selfId)
	local missionId = x310304_HaveWhichMission(sceneId, selfId)
	if missionType == x310304_g_MissionType.EnterPos then
		misIndex = GetQuestIndexByID( sceneId, selfId, missionId )
		if 1 == GetQuestParam( sceneId, selfId, misIndex, 7 ) then
			return
		end
		
		local ret = x310304_IsMasterHere(sceneId, selfId)
		if nil ~= ret then
			Msg2Player(sceneId,selfId,ret,8,2)
			BeginQuestEvent(sceneId);
			AddQuestText(sceneId, ret);
			EndQuestEvent();
			DispatchQuestTips(sceneId, selfId);
			return
		end
		SetQuestByIndex( sceneId, selfId, misIndex, 0, 1 )
	else
		return
	end
	
	if missionId > 0 and 1 ~= GetQuestParam( sceneId, selfId, misIndex, 7 ) then
		
		SetQuestByIndex( sceneId, selfId, misIndex, 7, 1 )
		local str = "#Y侦查完毕，可以提交任务了。"
		Msg2Player(sceneId,selfId,str,8,2)
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, str);
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
	end
end

function x310304_ProcTiming( sceneId, selfId )

end

--玩家离开一个 area 时触发
function x310304_ProcAreaLeaved( sceneId, selfId, ScriptId, MissionId )

end

function x310304_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId, nChangeType)
	if MissionId == nil or MissionId < 0 then
      return
  end
  
  if IsHaveQuestNM(sceneId,selfId,MissionId) <= 0 then
      return
  end
  
  if itemdataId ~= x310304_g_MissionItem then
  	return
  end
  
  local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )
  if 1 == nChangeType then --删除物品
  	if x310304_g_MissionType.UseItem == GetQuestParam( sceneId, selfId, misIndex, 6 ) then
			SetQuestByIndex( sceneId, selfId, misIndex, 6, GetQuestParam( sceneId, selfId, misIndex, 6 ) - 1 )
		end
  else
		if x310304_g_MissionType.BuyItem == GetQuestParam( sceneId, selfId, misIndex, 6 ) then
			SetQuestByIndex( sceneId, selfId, misIndex, 6, GetQuestParam( sceneId, selfId, misIndex, 6 ) + 1 )
		end
	end
	
end

function x310304_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	local haveMissionId = x310304_HaveWhichMission(sceneId, selfId)
	local missionType = x310304_GetMissionType(sceneId, selfId)
	
	if haveMissionId <= 0 then
		return
	end
	
	local misIndex = GetQuestIndexByID( sceneId, selfId, haveMissionId )
	
	if x310304_g_MissionType.UseItem ~= missionType and x310304_g_MissionType.KillMonster ~= missionType then
		return
	end
	
	if x310304_g_MissionType.KillMonster == missionType and GetQuestParam( sceneId, selfId, misIndex, 7 ) == 1 then
		return
	end
	
	local scene = 50
	local nCountry = GetCurCountry(sceneId,selfId)
	if 100*nCountry+scene ~= sceneId then --没有找到这个任务信息
		return 0
	end
	local posIndex = GetQuestParam( sceneId, selfId, misIndex, 6 )
	local posx = x310304_g_UseItemPos[posIndex].x
	local posz = x310304_g_UseItemPos[posIndex].z
	local radii = 10
	
	local PlayerPosX,PlayerPosZ = GetWorldPos( sceneId, selfId )
	
	if posx > 0 then --需要检查地点
		local distanceRet = radii * radii - (posx - PlayerPosX) * (posx - PlayerPosX) - (posz - PlayerPosZ) * (posz - PlayerPosZ)
		if distanceRet <= 0 then
			local strText = format("很抱歉，这里不能使用该物品，请到@sceneid_%d(%d,%d)处使用!", sceneId, posx, posz )
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, strText)
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId, selfId)
			return 0
		end
	end
	
	local ret = x310304_IsMasterHere(sceneId, selfId)
	if nil ~= ret then
			Msg2Player(sceneId,selfId,ret,8,2)
			BeginQuestEvent(sceneId);
			AddQuestText(sceneId, ret);
			EndQuestEvent();
			DispatchQuestTips(sceneId, selfId);
			return
	end

	BeginQuestEvent(sceneId)
	AddQuestText(sceneId, "前方出现任务目标")
	EndQuestEvent(sceneId)
	DispatchQuestTips(sceneId, selfId)
	
	local masterObjId = x310304_GetMasterObjId(sceneId, selfId)
	local masterLevel = GetLevel(sceneId, masterObjId)
	local monsterId = x310304_GetMonsterId(masterLevel)
	
	if monsterId > 0 then
	CreateMonster(sceneId, monsterId, PlayerPosX , PlayerPosZ, x310304_g_MonsterAI, -1, -1, -1, 21, x310304_g_MonsterAliveTime);
	end
	--删除物品
	EraseItem(sceneId, selfId, BagIndex)

	--播放效果
	if impactId ~= -1 then
		SendSpecificImpactToUnit(sceneId, selfId, selfId, selfId, impactId, 0);
	end
	
	if x310304_g_MissionType.UseItem == missionType then
		DelQuestNM( sceneId, selfId, haveMissionId )
		AddQuestNM( sceneId, selfId, x310304_g_ThirdMissionId )
		local misIndex = GetQuestIndexByID( sceneId, selfId, x310304_g_ThirdMissionId )
		SetQuestByIndex( sceneId, selfId, misIndex, 5, monsterId )
		SetQuestByIndex( sceneId, selfId, misIndex, 6, posIndex )
	elseif x310304_g_MissionType.KillMonster == missionType then
		SetQuestByIndex( sceneId, selfId, misIndex, 5, monsterId )
	end
	
	return 1
end

function x310304_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
	
	local HumanNum = GetMonsterOwnerCount( sceneId, objId ) --取得这个怪物死后拥有分配权的人数
	for i = 0, HumanNum-1 do
		local humanObjId = GetMonsterOwnerID( sceneId, objId, i ) --取得拥有分配权的人的objId
    if humanObjId ~= -1 then
    	local haveMissionId = x310304_HaveWhichMission(sceneId, humanObjId)
    	local missionType = x310304_GetMissionType(sceneId, humanObjId)
    	if IsPlayerStateNormal(sceneId, humanObjId) > 0 and GetHp(sceneId, humanObjId) > 0 and haveMissionId > 0 and x310304_g_MissionType.KillMonster == missionType then	--如果这个人拥有任务
					local misIndex = GetQuestIndexByID( sceneId, humanObjId, haveMissionId )
					if GetQuestParam( sceneId, humanObjId, misIndex, 5 ) == objdataId then
						local ret = x310304_IsMasterHere(sceneId, humanObjId)
						if nil ~= ret then
							Msg2Player(sceneId,humanObjId,ret,8,2)
							BeginQuestEvent(sceneId);
							AddQuestText(sceneId, ret);
							EndQuestEvent();
							DispatchQuestTips(sceneId, humanObjId);
						else
							SetQuestByIndex( sceneId, humanObjId, misIndex, 0, 1 )
							SetQuestByIndex( sceneId, humanObjId, misIndex, 7, 1 )
						end
					end
			end
    end
  end
	
end

function x310304_ProcQuestLogRefresh( sceneId, selfId, MissionId)
	local szMissionTarget = ""
	local szAward = ""
	local missionType = x310304_GetMissionType(sceneId, selfId)
	local missionId = x310304_HaveWhichMission(sceneId, selfId)
	if missionType == x310304_g_MissionType.EnterPos then
		local misIndex = GetQuestIndexByID( sceneId, selfId, missionId )
		local curNum = GetQuestParam( sceneId, selfId, misIndex, 0 )
		local szTarget1 = format("  到圣山东麓@npc_%s",x310304_g_LookAtPosId)
		szMissionTarget = szTarget1.." ： "..curNum.." / 1"
	elseif missionType == x310304_g_MissionType.UseItem then
		local misIndex = GetQuestIndexByID( sceneId, selfId, missionId )
		local curNum = 0
		local posIndex = GetQuestParam( sceneId, selfId, misIndex, 6 )
		local szTarget1 = format("  到王国#G杂货店#W购买狼烟后去指定地点使用@item_%s@npc_%s",x310304_g_MissionItem,x310304_g_UseItemPos[posIndex].id)
		szMissionTarget = szTarget1.." ： "..curNum.." / 1"
	elseif missionType == x310304_g_MissionType.KillMonster then
		local misIndex = GetQuestIndexByID( sceneId, selfId, missionId )
		local curNum = GetQuestParam( sceneId, selfId, misIndex, 0 )
		local szTarget1 = format("  杀死敌军头目")
		szMissionTarget = szTarget1.." ： "..curNum.." / 1"
	end
	local exp = x310304_CalculateExp(sceneId, selfId)
	szAward = "#W\n#Y奖励内容：\n#W经验值:"..exp.."点"
	BeginQuestEvent(sceneId)

	AddQuestLogCustomText( sceneId,
							"",						-- 标题
							"",        -- 任务名字
							szMissionTarget,		--任务目标
							"",			--任务NPC
							szAward,               --任务攻略
							"",	--任务描述
							""					--任务小提示
							)
	EndQuestEvent()
	DispatchQuestLogUpdate(sceneId, selfId, MissionId);
end

function x310304_ProcQuestAbandon(sceneId, selfId, MissionId)

	DelQuestNM( sceneId, selfId, MissionId )
	
	local message = "您放弃了师徒任务"
	BeginQuestEvent(sceneId);
		AddQuestText(sceneId, message);
	EndQuestEvent();
	DispatchQuestTips(sceneId, selfId);
	Msg2Player(sceneId, selfId, message, 4, 2);
	
	if GetQuestData(sceneId, selfId, MD_MASTER_PRENTICE_COM_DAY[1], MD_MASTER_PRENTICE_COM_DAY[2], MD_MASTER_PRENTICE_COM_DAY[3]) ~= GetDayOfYear() then
		SetQuestData(sceneId, selfId, MD_MASTER_PRENTICE_COM_DAY[1], MD_MASTER_PRENTICE_COM_DAY[2], MD_MASTER_PRENTICE_COM_DAY[3], GetDayOfYear())
		SetQuestData(sceneId, selfId, MD_MASTER_PRENTICE_COM_TIMES[1], MD_MASTER_PRENTICE_COM_TIMES[2], MD_MASTER_PRENTICE_COM_TIMES[3], 1)
	end
end