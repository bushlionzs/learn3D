
--MisDescBegin

x300721_g_ScriptId = 300721                 --脚本ID
x300721_g_LevelLess					= 	30

--MisDescEnd

--意气相投

x300721_g_MissionId = 1200

x300721_g_SubMission = {
[0] = 6546,
[1] = 7588,
[2] = 7589,
[3] = 7590,
[4] = 7591,
[5] = 7592,
[6] = 7593,
[7] = 7593,
[8] = 7593,
}

x300721_g_addFriendPoint = 150
x300721_g_MissionName ="【好友】意气相投"
x300721_g_ParamIndexBegin = 2
x300721_g_ParamIndexEnd = 6
function x300721_CalcMissionEXP(sceneId, selfId)
	--return GetLevel(sceneId, selfId) * 100 * 3 * 20
	local haveSubMissionId = x300721_HaveWhichSubMission(sceneId, selfId)
	if haveSubMissionId <= 0 then
		return 0
	end
	
	local misIndex = GetQuestIndexByID( sceneId, selfId, haveSubMissionId )
	
	local totalFriendpoint = 0
	for i=x300721_g_ParamIndexBegin, x300721_g_ParamIndexEnd do
			local guid = GetQuestParam( sceneId, selfId, misIndex, i )
			guid = tonumber(format("%u",guid))
			if guid > 0 and GetFriendName(sceneId, selfId, guid) ~= "" then
				local point = GetFriendPointByGuid(sceneId, selfId, guid)
				totalFriendpoint = totalFriendpoint + point
			end
	end
	totalFriendpoint = floor(totalFriendpoint / 5)
	local level = GetLevel(sceneId, selfId)
	local exp = 0
	if totalFriendpoint >= 0 and totalFriendpoint <= 500 then
		exp = level*2800
	elseif totalFriendpoint >= 501 and totalFriendpoint <= 2000 then
		exp = level*3200
	elseif totalFriendpoint >= 2001 and totalFriendpoint <= 5000 then
		exp = level*3600
	elseif totalFriendpoint >= 5001 and totalFriendpoint <= 10000 then
		exp = level*4000
	elseif totalFriendpoint >= 10001 and totalFriendpoint <= 17000 then
		exp = level*4400
	elseif totalFriendpoint >= 17001 and totalFriendpoint <= 27000 then
		exp = level*4800
	elseif totalFriendpoint >= 27001 and totalFriendpoint <= 40000 then
		exp = level*5200
	elseif totalFriendpoint >= 40001 and totalFriendpoint <= 58000 then
		exp = level*5600
	elseif totalFriendpoint >= 58001 and totalFriendpoint <= 80000 then
		exp = level*6000
	elseif totalFriendpoint >= 80001 and totalFriendpoint <= 99999 then
		exp = level*6400
	end
	return exp
end

function x300721_SetCompleteTimes(sceneId, selfId, times)
	SetQuestData(sceneId, selfId, MD_FRIEND_MISSION_COMPLETE_TIMES[1], MD_FRIEND_MISSION_COMPLETE_TIMES[2], MD_FRIEND_MISSION_COMPLETE_TIMES[3], times)
end

function x300721_SetCompleteDay(sceneId, selfId)
		SetQuestData(sceneId, selfId, MD_FRIEND_MISSION_COMPLETE_DATE[1], MD_FRIEND_MISSION_COMPLETE_DATE[2], MD_FRIEND_MISSION_COMPLETE_DATE[3], GetDayOfYear())
		x300721_SetCompleteTimes(sceneId, selfId, 1)
end

function x300721_GetCompleteDay(sceneId, selfId)
		return GetQuestData(sceneId, selfId, MD_FRIEND_MISSION_COMPLETE_DATE[1], MD_FRIEND_MISSION_COMPLETE_DATE[2], MD_FRIEND_MISSION_COMPLETE_DATE[3] )
end

function x300721_SetKillMonsterNum(sceneId, selfId, num)
		SetQuestData(sceneId, selfId, MD_FRIEND_MISSION_KILLMONSTER_NUM[1], MD_FRIEND_MISSION_KILLMONSTER_NUM[2], MD_FRIEND_MISSION_KILLMONSTER_NUM[3], num)
		x300721_KillMonsterRefresh(sceneId, selfId)
end

function x300721_GetKillMonsterNum(sceneId, selfId)
	return GetQuestData(sceneId, selfId, MD_FRIEND_MISSION_KILLMONSTER_NUM[1], MD_FRIEND_MISSION_KILLMONSTER_NUM[2],MD_FRIEND_MISSION_KILLMONSTER_NUM[3] )
end

function x300721_AddKillMonsterNum(sceneId, selfId, num)
	num = num + x300721_GetKillMonsterNum(sceneId, selfId)
	x300721_SetKillMonsterNum(sceneId, selfId, num)
end
	
function x300721_GetSubMissionId(humanLevel)
	local missionLevel = 0
	if  40  <= humanLevel and  humanLevel <= 50 then
		missionLevel = 1
	elseif 50 < humanLevel and  humanLevel <= 60 then
		missionLevel = 2
	elseif 60 < humanLevel and  humanLevel <= 70 then
		missionLevel = 3
	elseif 70 < humanLevel and  humanLevel <= 80 then
		missionLevel = 4
	elseif 80 < humanLevel and  humanLevel <= 90 then
		missionLevel = 5
	elseif 90 < humanLevel and  humanLevel <= 100 then
		missionLevel = 6
	elseif 100 < humanLevel and  humanLevel <= 110 then
		missionLevel = 7
	elseif 110 < humanLevel then
		missionLevel = 8
	end
	
	return x300721_g_SubMission[missionLevel]
end

function x300721_DeleteAllSubMission( sceneId, selfId )
	for i, mission in x300721_g_SubMission do
		DelQuestNM( sceneId, selfId, mission )
	end
end

function x300721_IsSubMission( sceneId, selfId, MissionId )
	for i, mission in x300721_g_SubMission do
		if tonumber(MissionId) == tonumber(mission) then
			return 1
		end
	end
	return -1
end

function x300721_HaveWhichSubMission(sceneId, selfId)
	for i, mission in x300721_g_SubMission do
		if IsHaveQuestNM( sceneId, selfId, mission ) == 1 then
			return mission
		end
	end
	return -1
end

function x300721_IsHaveSubMission(sceneId, selfId)
	for i, mission in x300721_g_SubMission do
		if IsHaveQuestNM( sceneId, selfId, mission ) == 1 then
			return 1
		end
	end
	return -1
end

function x300721_HaveDoneWhichSubMission(sceneId, selfId, targetId)

	for i, mission in x300721_g_SubMission do
		local misIndex = GetQuestIndexByID( sceneId, selfId, mission )
		if GetQuestParam( sceneId, selfId, misIndex, 7 ) == 1 then
			return mission
		end
		if IsHaveQuestNM( sceneId, selfId, mission ) == 1 and QuestCheckSubmitNM( sceneId, selfId, targetId, mission, misIndex ) > 0 then
			return mission
		end 
	end
	return -1
end

--**********************************

--任务入口函数

--**********************************

function x300721_ProcEventEntry( sceneId, selfId, targetId, MissionId, index )
	local haveSubMissionId = x300721_HaveWhichSubMission(sceneId, selfId)
	local haveDoneMissionId = -1
	if haveSubMissionId > 0 then
		haveDoneMissionId = x300721_HaveDoneWhichSubMission(sceneId, selfId, targetId)
	end
	
	local exp = x300721_CalcMissionEXP(sceneId, selfId)
	
	if haveDoneMissionId > 0 then
		BeginQuestEvent(sceneId)
		--任务信息
		AddQuestText(sceneId,"#Y【好友】意气相投")
		AddQuestText(sceneId,"\t恭喜您，完成了意气相投！#r")

		AddQuestText(sceneId,"#Y任务奖励：")
		AddQuestText(sceneId, "\t好友度:"..x300721_g_addFriendPoint.."点")
		AddQuestText(sceneId, "\t经验值:"..exp.."点")
		EndQuestEvent()
	  DispatchQuestContinueInfoNM(sceneId, selfId, targetId, x300721_g_ScriptId, MissionId);
	  return
	end
	
	if haveSubMissionId > 0 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"#Y【好友】意气相投")
		AddQuestText(sceneId,"\t您还没有杀死200只怪，赶快去完成吧！#r")
		AddQuestText(sceneId,"#Y任务奖励：")
		AddQuestText(sceneId, "\t好友度:"..x300721_g_addFriendPoint.."点")
		AddQuestText(sceneId, "\t经验值:"..exp.."点")
		EndQuestEvent()
		DispatchQuestDemandInfo(sceneId, selfId, targetId, x300721_g_ScriptId, MissionId,0);
		return
	end
	
	BeginQuestEvent(sceneId)
	AddQuestText(sceneId,"#Y【好友】意气相投")
	--AddQuestText(sceneId,"\t意气相投#r")
	
	--AddQuestText(sceneId,"#Y【任务描述】")
	AddQuestText(sceneId,"\t在这个世界上有很多意气相投的人愿意结为好友，为了让大家能够更快地相互了解，更快地增加好友度，您可以组队来我这里领取意气相投任务。即使队伍中有陌生人，只要接了意气相投任务就会把你们自动加为好友。\n\t成功地完成任务，将会增加组队好友之间的好友度。如果组队的好友越多，好友度越高，获得的经验也越多。")
	
	AddQuestText(sceneId,"#Y任务目标：")
	AddQuestText(sceneId,"\t成功领取任务，杀死200只相应的指定怪！#r")
	
	AddQuestText(sceneId,"#Y任务奖励：")
	AddQuestText(sceneId, "\t好友度:"..x300721_g_addFriendPoint.."点")
	AddQuestText(sceneId, "\t经验值:好友度越高，经验值越高。")
	
	EndQuestEvent()

	DispatchQuestInfo(sceneId, selfId, targetId, x300721_g_MissionId, -1)

end

--**********************************

--列举事件

--**********************************
--5	非循环任务	未接	1
--6	非循环/循环任务	未完成	2
--7	非循环任务	已完成	3
function x300721_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
	if GetLevel(sceneId, selfId) < 30 then
		return
	end
	local haveSubMissionId = x300721_HaveWhichSubMission(sceneId, selfId)
	local haveDoneMissionId = -1
	local state = 8
	if haveSubMissionId > 0 then
		haveDoneMissionId = x300721_HaveDoneWhichSubMission(sceneId, selfId, targetId)
	end
	
	if haveDoneMissionId > 0 then
		state = 7
	
	elseif haveSubMissionId > 0 then
		state = 6
	end
	AddQuestNumText(sceneId, x300721_g_MissionId, x300721_g_MissionName, state, -1)
	
end



--**********************************

--检测接受条件

--**********************************

function x300721_ProcAcceptCheck(sceneId, selfId, NPCId)

	--if HasTeam(sceneId, selfId) == 1 then
		return 1
	--end
end


--**********************************

--检测查看条件

--**********************************

function x300721_CheckPushList(sceneId, selfId, NPCId)
	return 1
end

function x300721_DoAccept( sceneId, selfId )
	
	local week = GetWeek()
	if week ~= 1 and week ~= 3 then
		return "只有周一、周三才能领取本任务。"
	end
	
	local bLeader = IsTeamLeader( sceneId, selfId )
	if bLeader ~= 1 then
		return "你不是队长，只有队长才能领取本任务。"
	end
	
	local teamSize = GetTeamSize(sceneId, selfId)
	if (teamSize < 2) then
		return "你的队伍中不足2人，无法接取本任务。";
	end
	
	local nearTeamSize = GetNearTeamCount(sceneId, selfId)
	if teamSize ~= nearTeamSize then
		return "很抱歉，所有队员必须都在附近，否则无法接此任务。"
	end
	
	for i = 0, teamSize - 1 do
		local targetId = GetNearTeamMember(sceneId, selfId, i)
		if IsInDist(sceneId, selfId, targetId, 10) ~= 1 then
			return "很抱歉，所有队员必须都在附近，否则无法接此任务。"
		end
	end
	
	for i = 0, teamSize - 1 do
		local targetId = GetNearTeamMember(sceneId, selfId, i)
		local targetLevel = GetLevel(sceneId, targetId)
		if targetLevel < 30 then
			return "你的队伍中有人不足30级，无法领取本任务。"
		end
	end
	
	local today = GetDayOfYear()
	local completeDay = x300721_GetCompleteDay(sceneId, selfId)
	if( completeDay == today) then
		return "你已经领取了本任务，今天无法接取本任务了。"
	end
	
	for i = 0, teamSize - 1 do
		local targetId = GetNearTeamMember(sceneId, selfId, i)
		local completeDay = x300721_GetCompleteDay(sceneId, targetId)
		if( completeDay == today) then
			return "你队伍中有人领取了本任务，今天无法接取本任务。"
		end
	end
	
	local curLevel = 200
	for i = 0, teamSize - 1 do
		local targetId = GetNearTeamMember(sceneId, selfId, i)
		local targetLevel = GetLevel(sceneId, targetId)
		if targetLevel <= curLevel then
			curLevel = targetLevel
		end
	end
	local averageLevel = curLevel 
	local missionId = x300721_GetSubMissionId(averageLevel)
	
	local bHaveMission = x300721_IsHaveSubMission(sceneId, selfId)
	if bHaveMission == 1 then
		return "你已经接取了本任务，快去完成吧。"
	end
	
	for i = 0, teamSize - 1 do
		local targetId = GetNearTeamMember(sceneId, selfId, i)
		local bHaveMission = x300721_IsHaveSubMission(sceneId, targetId)
		if bHaveMission == 1 then
			return "你队伍中有人有本任务，无法接取本任务。"
		end
	end
	
	for i = 0, teamSize - 1 do
		local targetId = GetNearTeamMember(sceneId, selfId, i)
		if IsQuestFullNM(sceneId, targetId) == 1 then
			return "很抱歉，您队伍中有人任务已经满了，无法领取本任务。"
		end
	end
	
	for i = 0, teamSize - 1 do
	
		local aId = GetNearTeamMember(sceneId, selfId, i)
		local aName = GetName(sceneId, aId)
		
		local str = format("您领取了任务:%s", x300721_g_MissionName)
		Msg2Player(sceneId,aId,str,8,2)
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, str);
		EndQuestEvent();
		DispatchQuestTips(sceneId, aId);
		
		for j = i + 1, teamSize - 1 do
			local bId = GetNearTeamMember(sceneId, selfId, j)
			local bName = GetName(sceneId, bId)
			if IsFriend(sceneId, aId, bId) ~= 1 then
				AddFriend(sceneId, aId, bName, 0)
			else
				local point = GetFriendPoint(sceneId, aId, bId)
				--SetFriendPoint(sceneId, aId, bId, point + x300721_g_addFriendPoint)
			end
			if IsFriend(sceneId, bId, aId) ~= 1 then
				AddFriend(sceneId, bId, aName, 0)
			else
				local point = GetFriendPoint(sceneId, bId, aId)
				--SetFriendPoint(sceneId, bId, aId, point + x300721_g_addFriendPoint)
			end
			--str = format("由于领取任务：%s，你与%s增加了%d好友度", x300721_g_MissionName, bName, x300721_g_addFriendPoint)
			--BeginQuestEvent(sceneId);
			--AddQuestText(sceneId, str);
			--EndQuestEvent();
			--DispatchQuestTips(sceneId, aId);
			--str = format("由于领取任务：%s，你与%s增加了%d好友度", x300721_g_MissionName, aName, x300721_g_addFriendPoint)
			--BeginQuestEvent(sceneId);
			--AddQuestText(sceneId, str);
			--EndQuestEvent();
			--DispatchQuestTips(sceneId, bId);
		end
		
		local errorCode = AddQuestNM( sceneId, aId, missionId )
		if errorCode ~= 1 then
			Msg2Player(sceneId,aId,"添加任务失败！",8,2)
		end
		QuestCom(sceneId,aId,x300721_g_MissionId)
		x300721_SetCompleteDay(sceneId, aId, today)
		x300721_SetKillMonsterNum(sceneId, aId, 0)
		
	end
	
	for i = 0, teamSize - 1 do
		local aId = GetNearTeamMember(sceneId, selfId, i)
		local misIndex = GetQuestIndexByID( sceneId, aId, missionId )
		local aName = GetName(sceneId,aId)
		
		local msg = "FriendLog:accept Name="..aName.." GUID="..GetGUID(sceneId,aId).." MissionID="..missionId.." =>"
		local paramIndex = x300721_g_ParamIndexBegin
		for j = 0, teamSize - 1 do
			local bId = GetNearTeamMember(sceneId, selfId, j)
			if bId ~= aId then
				SetQuestByIndex( sceneId, aId, misIndex, paramIndex, GetGUID(sceneId, bId) )
				
				paramIndex = paramIndex + 1
				
				msg = msg.." ["..(paramIndex-1).."]GUID="..GetGUID(sceneId,bId).." Name="..GetName(sceneId,bId)
			end
		end
		
		WriteLog(1,msg)
	end
	
	
	
	return nil
end

--**********************************

--接受

--**********************************
function x300721_ProcQuestAccept( sceneId, selfId, targetId, MissionId )
	local str = x300721_DoAccept( sceneId, selfId )
	if str ~= nil then
		Msg2Player(sceneId,selfId,str,8,2)
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, str);
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
	end
	
end



--**********************************

--放弃

--**********************************

function x300721_ProcQuestAbandon(sceneId, selfId, MissionId)

	x300721_DeleteAllSubMission( sceneId, selfId )
	QuestUnCom(sceneId,selfId,x300721_g_MissionId)
	local today = GetDayOfYear()
	x300721_SetCompleteDay(sceneId, selfId, today)
	
	local MissionName = GetQuestNameNM( sceneId, selfId, MissionId )
	local message = format("您放弃了任务:%s", MissionName);
	BeginQuestEvent(sceneId);
		AddQuestText(sceneId, message);
	EndQuestEvent();
	DispatchQuestTips(sceneId, selfId);
	Msg2Player(sceneId, selfId, message, 4, 2);
end



--**********************************

--检测是否可以提交

--**********************************

function x300721_CheckSubmit( sceneId, selfId, MissionId )
	local haveSubMissionId = x300721_HaveWhichSubMission(sceneId, selfId)
	local haveDoneMissionId = -1
	if haveSubMissionId > 0 then
		haveDoneMissionId = x300721_HaveDoneWhichSubMission(sceneId, selfId, 1)
	end
	
	if haveDoneMissionId > 0 then
		return 1;
	end
	return 0
end



--**********************************

--提交

--**********************************
function x300721_ProcQuestSubmit( sceneId, selfId, targetId, selectId, MissionId )

	local haveSubMissionId = x300721_HaveWhichSubMission(sceneId, selfId)
	local haveDoneMissionId = -1
	if haveSubMissionId > 0 then
		haveDoneMissionId = x300721_HaveDoneWhichSubMission(sceneId, selfId, 1)
	end
	
	if haveDoneMissionId == nil or haveDoneMissionId < 0 then
        return 0
    end
    
  if IsHaveQuestNM( sceneId,selfId,haveDoneMissionId )<= 0 then
      return 0
  end
  
	local misIndex = GetQuestIndexByID( sceneId, selfId, haveDoneMissionId )
		
	local exp = x300721_CalcMissionEXP(sceneId, selfId)	
	local strTable = {}
	local guidTable = {}
	
	
	local szName =GetName(sceneId,selfId)
	if szName == nil then szName = "Error" end
	local szLogMsg = "FriendLog:submit Name="..GetName(sceneId,selfId).." GUID="..GetGUID(sceneId,selfId).." MissionID="..haveDoneMissionId.." => "
	for i=x300721_g_ParamIndexBegin, x300721_g_ParamIndexEnd do
			local guid = GetQuestParam( sceneId, selfId, misIndex, i )
			guid = tonumber(format("%u",guid))
			if guid > 0 and GetFriendName(sceneId, selfId, guid) ~= "" then
				local str = format("你与%s增加了%d点好友度", GetFriendName(sceneId, selfId, guid), x300721_g_addFriendPoint)
				strTable[i] = str
				guidTable[i] = guid
				szLogMsg = szLogMsg.."["..i.."]GUID="..guid.." Name="..GetFriendName(sceneId, selfId, guid).." "
			else
				szLogMsg = szLogMsg.."["..i.."]GUID="..guid.." "
			end
	end
	
	--记录日志
	WriteLog(1,szLogMsg)
		
	local ret = QuestComplateNM( sceneId, selfId, targetId, haveDoneMissionId, selectId ) -- 获取完成任务信息
	if ret > 0 then -- 如果成功完成
		
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, "您完成了任务:【好友】意气相投");
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
		DispatchQuestTips(sceneId, selfId);
		local msg = "\n获得#R经验"..exp.."点#cEFC800的奖励"
		Msg2Player(sceneId,selfId,"您完成了任务：【好友】意气相投！"..msg,8,2)
		
		AddExp(sceneId, selfId, exp);
		
		for i=x300721_g_ParamIndexBegin, x300721_g_ParamIndexEnd do
			if nil ~= guidTable[i] then
				local guid = guidTable[i]
				local point = GetFriendPointByGuid(sceneId, selfId, guid)
				SetFriendPointByGuid(sceneId, selfId, guid, point + x300721_g_addFriendPoint)
			end
		end
		
		for i=x300721_g_ParamIndexBegin, x300721_g_ParamIndexEnd do
			if nil ~= strTable[i] then
				local str = strTable[i]
				BeginQuestEvent(sceneId);
				AddQuestText(sceneId, str);
				EndQuestEvent();
				DispatchQuestTips(sceneId, selfId);
				Msg2Player(sceneId,selfId,str,8,2)
			end
		end
		
		DelQuestNM( sceneId, selfId, haveDoneMissionId )
		local today = GetDayOfYear()
		x300721_SetCompleteDay(sceneId, selfId, today)
		QuestUnCom(sceneId,selfId,x300721_g_MissionId)
		
	end

	return 0
	
end



--**********************************

--杀死怪物或玩家

--**********************************

function x300721_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

	if x300721_IsSubMission( sceneId, selfId, MissionId ) < 0 then
		return -1;
	end
	
	local NeedKilledNum, InstIndex, ObjName = GetQuestNeedKillObjInfoNM( sceneId, selfId, MissionId, objdataId, objId )
	if NeedKilledNum > 0 then --单纯的杀怪任务
		local HumenNum = GetMonsterOwnerCount( sceneId, objId ) --取得这个怪物死后拥有分配权的人数
		for i = 0, HumenNum-1 do
			local humanObjId = GetMonsterOwnerID( sceneId, objId, i ) --取得拥有分配权的人的objId
        	if humanObjId ~= -1 and IsPlayerStateNormal(sceneId, humanObjId) > 0 and GetHp(sceneId, humanObjId) > 0 and IsHaveQuestNM( sceneId, humanObjId, MissionId ) > 0 then	--如果这个人拥有任务

          		local strText = "";
         	 	local misIndex = GetQuestIndexByID( sceneId, humanObjId, MissionId )
          		local KilledNum = x300721_GetKillMonsterNum(sceneId, humanObjId)

                if KilledNum < NeedKilledNum then

                	x300721_AddKillMonsterNum(sceneId, humanObjId, 1)
                	--NeedKilledNum, InstIndex, ObjName = GetQuestNeedKillObjInfoNM( sceneId, humanObjId, MissionId, objdataId, objId )
                  	--SetQuestByIndex( sceneId, humanObjId, misIndex, InstIndex, KilledNum+1 )

                  	if KilledNum == NeedKilledNum - 1 then

						BeginQuestEvent(sceneId)

						if ObjName == "" then
						  strText = format( "已经杀死全部的怪物: %d/%d", KilledNum+1, NeedKilledNum )
						else
						  strText = format( "已经杀死全部的%s: %d/%d", ObjName, KilledNum+1, NeedKilledNum )
						end

						AddQuestText( sceneId, strText )
						EndQuestEvent( sceneId )
						DispatchQuestTips( sceneId, humanObjId )

						SetQuestByIndex( sceneId, humanObjId, misIndex, 7, 1 )
						x300721_ProcQuestLogRefresh(sceneId, humanObjId, -1)

                    else
                        BeginQuestEvent(sceneId)
                        if ObjName == "" then
                            strText = format( "已经杀死怪物: %d/%d", KilledNum+1, NeedKilledNum )
                        else
                            strText = format( "已经杀死%s: %d/%d", ObjName, KilledNum+1, NeedKilledNum )
                        end
                        AddQuestText( sceneId, strText )
                        EndQuestEvent( sceneId )
                        DispatchQuestTips( sceneId, humanObjId )
                        x300721_ProcQuestLogRefresh(sceneId, humanObjId, -1)
                    end
                end
	       	end
		end
	end
end



--**********************************

--进入区域事件

--**********************************

function x300721_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)
	

end

function x300721_ProcTiming(sceneId, selfId )
	 
		
end

function x300721_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId )
	
end



--**********************************

--道具改变

--**********************************

function x300721_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	
end
function x300721_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )

	if IsHaveQuestNM( sceneId, selfId, MissionId) == 0 then	-- 如果没有这个任务
		return
	end
	
end

function x300721_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x300721_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x300721_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x300721_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x300721_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end

function x300721_KillMonsterRefresh(sceneId, selfId)
	local subMission = x300721_HaveWhichSubMission(sceneId, selfId)
  local szMissionTarget = x300721_GetMissionTarget(sceneId, selfId)
	BeginQuestEvent(sceneId)

	AddQuestLogCustomText( sceneId,
							"",						-- 标题
							x300721_g_MissionName,        -- 任务名字
							szMissionTarget,		--任务目标
							"",			--任务NPC
							"",               --任务攻略
							"",	--任务描述
							""					--任务小提示
							)
	EndQuestEvent()
	DispatchQuestLogUpdate(sceneId, selfId, subMission);
end

function x300721_GetMissionHelp(sceneId, selfId)
	local subMission = x300721_HaveWhichSubMission(sceneId, selfId)
	local szMissionHelp = ""
	if tonumber(6546) == tonumber(subMission) then
		szMissionHelp = "到王国迷宫一层消灭200只@npc_90051后向@npc_123759复命。"
	elseif tonumber(7588) == tonumber(subMission) then
		szMissionHelp = "到王国迷宫二层消灭200只@npc_90053后向@npc_123759复命。"
	elseif tonumber(7589) == tonumber(subMission) then
		szMissionHelp = "到王国迷宫三层消灭200只@npc_90055后向@npc_123759复命。"
	elseif tonumber(7590) == tonumber(subMission) then
		szMissionHelp = "到王国迷宫四层消灭200只@npc_90057后向@npc_123759复命。"
	elseif tonumber(7591) == tonumber(subMission) then
		szMissionHelp = "到王国迷宫五层消灭200只@npc_90059后向@npc_123759复命。"
	elseif tonumber(7592) == tonumber(subMission) then
		szMissionHelp = "到王国迷宫六层消灭200只@npc_90061后向@npc_123759复命。"
	elseif tonumber(7593) == tonumber(subMission) then
		szMissionHelp = "到王国迷宫七层消灭200只@npc_90063后向@npc_123759复命。"
	elseif tonumber(7594) == tonumber(subMission) then
		szMissionHelp = "到王国迷宫八层消灭200只@npc_14004后向@npc_123759复命。"
	elseif tonumber(7595) == tonumber(subMission) then
		szMissionHelp = "到王国迷宫九层消灭200只@npc_14004后向@npc_123759复命。"
	end
	return szMissionHelp
end

function x300721_GetMissionTarget(sceneId, selfId)
	local subMission = x300721_HaveWhichSubMission(sceneId, selfId)
	local curKillMonsterNum = x300721_GetKillMonsterNum(sceneId, selfId)
	local szMonsterNum = "(" .. curKillMonsterNum .. "/200)"
	local szMissionTarget = ""
	if tonumber(6546) == tonumber(subMission) then
		szMissionTarget = "  除掉200只@npc_90051" .. szMonsterNum
	elseif tonumber(7588) == tonumber(subMission) then
		szMissionTarget = "  除掉200只@npc_90053" .. szMonsterNum
	elseif tonumber(7589) == tonumber(subMission) then
		szMissionTarget = "  除掉200只@npc_90055" .. szMonsterNum
	elseif tonumber(7590) == tonumber(subMission) then
		szMissionTarget = "  除掉200只@npc_90057" .. szMonsterNum
	elseif tonumber(7591) == tonumber(subMission) then
		szMissionTarget = "  除掉200只@npc_90059" .. szMonsterNum
	elseif tonumber(7592) == tonumber(subMission) then
		szMissionTarget = "  除掉200只@npc_90061" .. szMonsterNum
	elseif tonumber(7593) == tonumber(subMission) then
		szMissionTarget = "  除掉200只@npc_90063" .. szMonsterNum
	elseif tonumber(7594) == tonumber(subMission) then
		szMissionTarget = "  除掉200只@npc_14004" .. szMonsterNum
	elseif tonumber(7595) == tonumber(subMission) then
		szMissionTarget = "  除掉200只@npc_14004" .. szMonsterNum
	end
	return szMissionTarget
end

function x300721_QuestLogRefresh( sceneId, selfId, MissionId)
	local subMission = x300721_HaveWhichSubMission(sceneId, selfId)
	local szMissionDesc = "\t为了让大家更多的结识朋友，为了让大家更快的增加好友度，"
	.."您可以组队来找我领取意气相投。哪怕队中有陌生人，只要接取意气相投也会把你们自动加为好友。"
	.."成功完成本任务，会增加组队间好友的好友度。"
	
	local szMissionHelp = x300721_GetMissionHelp(sceneId, selfId)
	
	local szMissionTarget = x300721_GetMissionTarget(sceneId, selfId)
	local szMissionNPC = "@npc_123759"
	local exp = x300721_CalcMissionEXP(sceneId, selfId)
	BeginQuestEvent(sceneId)
		local szMissionBonus = "\n#Y\n奖励内容：\n#W好友度:"..x300721_g_addFriendPoint.."点";
		local szMissionExp = "\n#W经验值:"..exp.."点";
	AddQuestLogCustomText( sceneId,
							"标题",						-- 标题
							x300721_g_MissionName,        -- 任务名字
							szMissionTarget,		--任务目标
							szMissionNPC,			--任务NPC
							szMissionHelp..szMissionBonus..szMissionExp,               --任务攻略
							szMissionDesc,	--任务描述
							""					--任务小提示
							)
	EndQuestEvent()
	DispatchQuestLogUpdate(sceneId, selfId, subMission);
end

function x300721_ProcQuestLogRefresh( sceneId, selfId, MissionId)
	x300721_QuestLogRefresh( sceneId, selfId, MissionId );
end