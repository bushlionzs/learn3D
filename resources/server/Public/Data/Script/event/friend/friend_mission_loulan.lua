
--MisDescBegin

x300721_g_ScriptId = 300721                 --�ű�ID
x300721_g_LevelLess					= 	30

--MisDescEnd

--������Ͷ

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
x300721_g_MissionName ="�����ѡ�������Ͷ"
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

--������ں���

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
		--������Ϣ
		AddQuestText(sceneId,"#Y�����ѡ�������Ͷ")
		AddQuestText(sceneId,"\t��ϲ���������������Ͷ��#r")

		AddQuestText(sceneId,"#Y��������")
		AddQuestText(sceneId, "\t���Ѷ�:"..x300721_g_addFriendPoint.."��")
		AddQuestText(sceneId, "\t����ֵ:"..exp.."��")
		EndQuestEvent()
	  DispatchQuestContinueInfoNM(sceneId, selfId, targetId, x300721_g_ScriptId, MissionId);
	  return
	end
	
	if haveSubMissionId > 0 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"#Y�����ѡ�������Ͷ")
		AddQuestText(sceneId,"\t����û��ɱ��200ֻ�֣��Ͽ�ȥ��ɰɣ�#r")
		AddQuestText(sceneId,"#Y��������")
		AddQuestText(sceneId, "\t���Ѷ�:"..x300721_g_addFriendPoint.."��")
		AddQuestText(sceneId, "\t����ֵ:"..exp.."��")
		EndQuestEvent()
		DispatchQuestDemandInfo(sceneId, selfId, targetId, x300721_g_ScriptId, MissionId,0);
		return
	end
	
	BeginQuestEvent(sceneId)
	AddQuestText(sceneId,"#Y�����ѡ�������Ͷ")
	--AddQuestText(sceneId,"\t������Ͷ#r")
	
	--AddQuestText(sceneId,"#Y������������")
	AddQuestText(sceneId,"\t������������кܶ�������Ͷ����Ը���Ϊ���ѣ�Ϊ���ô���ܹ�������໥�˽⣬��������Ӻ��Ѷȣ��������������������ȡ������Ͷ���񡣼�ʹ��������İ���ˣ�ֻҪ����������Ͷ����ͻ�������Զ���Ϊ���ѡ�\n\t�ɹ���������񣬽���������Ӻ���֮��ĺ��Ѷȡ������ӵĺ���Խ�࣬���Ѷ�Խ�ߣ���õľ���ҲԽ�ࡣ")
	
	AddQuestText(sceneId,"#Y����Ŀ�꣺")
	AddQuestText(sceneId,"\t�ɹ���ȡ����ɱ��200ֻ��Ӧ��ָ���֣�#r")
	
	AddQuestText(sceneId,"#Y��������")
	AddQuestText(sceneId, "\t���Ѷ�:"..x300721_g_addFriendPoint.."��")
	AddQuestText(sceneId, "\t����ֵ:���Ѷ�Խ�ߣ�����ֵԽ�ߡ�")
	
	EndQuestEvent()

	DispatchQuestInfo(sceneId, selfId, targetId, x300721_g_MissionId, -1)

end

--**********************************

--�о��¼�

--**********************************
--5	��ѭ������	δ��	1
--6	��ѭ��/ѭ������	δ���	2
--7	��ѭ������	�����	3
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

--����������

--**********************************

function x300721_ProcAcceptCheck(sceneId, selfId, NPCId)

	--if HasTeam(sceneId, selfId) == 1 then
		return 1
	--end
end


--**********************************

--���鿴����

--**********************************

function x300721_CheckPushList(sceneId, selfId, NPCId)
	return 1
end

function x300721_DoAccept( sceneId, selfId )
	
	local week = GetWeek()
	if week ~= 1 and week ~= 3 then
		return "ֻ����һ������������ȡ������"
	end
	
	local bLeader = IsTeamLeader( sceneId, selfId )
	if bLeader ~= 1 then
		return "�㲻�Ƕӳ���ֻ�жӳ�������ȡ������"
	end
	
	local teamSize = GetTeamSize(sceneId, selfId)
	if (teamSize < 2) then
		return "��Ķ����в���2�ˣ��޷���ȡ������";
	end
	
	local nearTeamSize = GetNearTeamCount(sceneId, selfId)
	if teamSize ~= nearTeamSize then
		return "�ܱ�Ǹ�����ж�Ա���붼�ڸ����������޷��Ӵ�����"
	end
	
	for i = 0, teamSize - 1 do
		local targetId = GetNearTeamMember(sceneId, selfId, i)
		if IsInDist(sceneId, selfId, targetId, 10) ~= 1 then
			return "�ܱ�Ǹ�����ж�Ա���붼�ڸ����������޷��Ӵ�����"
		end
	end
	
	for i = 0, teamSize - 1 do
		local targetId = GetNearTeamMember(sceneId, selfId, i)
		local targetLevel = GetLevel(sceneId, targetId)
		if targetLevel < 30 then
			return "��Ķ��������˲���30�����޷���ȡ������"
		end
	end
	
	local today = GetDayOfYear()
	local completeDay = x300721_GetCompleteDay(sceneId, selfId)
	if( completeDay == today) then
		return "���Ѿ���ȡ�˱����񣬽����޷���ȡ�������ˡ�"
	end
	
	for i = 0, teamSize - 1 do
		local targetId = GetNearTeamMember(sceneId, selfId, i)
		local completeDay = x300721_GetCompleteDay(sceneId, targetId)
		if( completeDay == today) then
			return "�������������ȡ�˱����񣬽����޷���ȡ������"
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
		return "���Ѿ���ȡ�˱����񣬿�ȥ��ɰɡ�"
	end
	
	for i = 0, teamSize - 1 do
		local targetId = GetNearTeamMember(sceneId, selfId, i)
		local bHaveMission = x300721_IsHaveSubMission(sceneId, targetId)
		if bHaveMission == 1 then
			return "������������б������޷���ȡ������"
		end
	end
	
	for i = 0, teamSize - 1 do
		local targetId = GetNearTeamMember(sceneId, selfId, i)
		if IsQuestFullNM(sceneId, targetId) == 1 then
			return "�ܱ�Ǹ�������������������Ѿ����ˣ��޷���ȡ������"
		end
	end
	
	for i = 0, teamSize - 1 do
	
		local aId = GetNearTeamMember(sceneId, selfId, i)
		local aName = GetName(sceneId, aId)
		
		local str = format("����ȡ������:%s", x300721_g_MissionName)
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
			--str = format("������ȡ����%s������%s������%d���Ѷ�", x300721_g_MissionName, bName, x300721_g_addFriendPoint)
			--BeginQuestEvent(sceneId);
			--AddQuestText(sceneId, str);
			--EndQuestEvent();
			--DispatchQuestTips(sceneId, aId);
			--str = format("������ȡ����%s������%s������%d���Ѷ�", x300721_g_MissionName, aName, x300721_g_addFriendPoint)
			--BeginQuestEvent(sceneId);
			--AddQuestText(sceneId, str);
			--EndQuestEvent();
			--DispatchQuestTips(sceneId, bId);
		end
		
		local errorCode = AddQuestNM( sceneId, aId, missionId )
		if errorCode ~= 1 then
			Msg2Player(sceneId,aId,"�������ʧ�ܣ�",8,2)
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

--����

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

--����

--**********************************

function x300721_ProcQuestAbandon(sceneId, selfId, MissionId)

	x300721_DeleteAllSubMission( sceneId, selfId )
	QuestUnCom(sceneId,selfId,x300721_g_MissionId)
	local today = GetDayOfYear()
	x300721_SetCompleteDay(sceneId, selfId, today)
	
	local MissionName = GetQuestNameNM( sceneId, selfId, MissionId )
	local message = format("������������:%s", MissionName);
	BeginQuestEvent(sceneId);
		AddQuestText(sceneId, message);
	EndQuestEvent();
	DispatchQuestTips(sceneId, selfId);
	Msg2Player(sceneId, selfId, message, 4, 2);
end



--**********************************

--����Ƿ�����ύ

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

--�ύ

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
				local str = format("����%s������%d����Ѷ�", GetFriendName(sceneId, selfId, guid), x300721_g_addFriendPoint)
				strTable[i] = str
				guidTable[i] = guid
				szLogMsg = szLogMsg.."["..i.."]GUID="..guid.." Name="..GetFriendName(sceneId, selfId, guid).." "
			else
				szLogMsg = szLogMsg.."["..i.."]GUID="..guid.." "
			end
	end
	
	--��¼��־
	WriteLog(1,szLogMsg)
		
	local ret = QuestComplateNM( sceneId, selfId, targetId, haveDoneMissionId, selectId ) -- ��ȡ���������Ϣ
	if ret > 0 then -- ����ɹ����
		
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, "�����������:�����ѡ�������Ͷ");
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
		DispatchQuestTips(sceneId, selfId);
		local msg = "\n���#R����"..exp.."��#cEFC800�Ľ���"
		Msg2Player(sceneId,selfId,"����������񣺡����ѡ�������Ͷ��"..msg,8,2)
		
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

--ɱ����������

--**********************************

function x300721_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

	if x300721_IsSubMission( sceneId, selfId, MissionId ) < 0 then
		return -1;
	end
	
	local NeedKilledNum, InstIndex, ObjName = GetQuestNeedKillObjInfoNM( sceneId, selfId, MissionId, objdataId, objId )
	if NeedKilledNum > 0 then --������ɱ������
		local HumenNum = GetMonsterOwnerCount( sceneId, objId ) --ȡ�������������ӵ�з���Ȩ������
		for i = 0, HumenNum-1 do
			local humanObjId = GetMonsterOwnerID( sceneId, objId, i ) --ȡ��ӵ�з���Ȩ���˵�objId
        	if humanObjId ~= -1 and IsPlayerStateNormal(sceneId, humanObjId) > 0 and GetHp(sceneId, humanObjId) > 0 and IsHaveQuestNM( sceneId, humanObjId, MissionId ) > 0 then	--��������ӵ������

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
						  strText = format( "�Ѿ�ɱ��ȫ���Ĺ���: %d/%d", KilledNum+1, NeedKilledNum )
						else
						  strText = format( "�Ѿ�ɱ��ȫ����%s: %d/%d", ObjName, KilledNum+1, NeedKilledNum )
						end

						AddQuestText( sceneId, strText )
						EndQuestEvent( sceneId )
						DispatchQuestTips( sceneId, humanObjId )

						SetQuestByIndex( sceneId, humanObjId, misIndex, 7, 1 )
						x300721_ProcQuestLogRefresh(sceneId, humanObjId, -1)

                    else
                        BeginQuestEvent(sceneId)
                        if ObjName == "" then
                            strText = format( "�Ѿ�ɱ������: %d/%d", KilledNum+1, NeedKilledNum )
                        else
                            strText = format( "�Ѿ�ɱ��%s: %d/%d", ObjName, KilledNum+1, NeedKilledNum )
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

--���������¼�

--**********************************

function x300721_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)
	

end

function x300721_ProcTiming(sceneId, selfId )
	 
		
end

function x300721_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId )
	
end



--**********************************

--���߸ı�

--**********************************

function x300721_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	
end
function x300721_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )

	if IsHaveQuestNM( sceneId, selfId, MissionId) == 0 then	-- ���û���������
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
							"",						-- ����
							x300721_g_MissionName,        -- ��������
							szMissionTarget,		--����Ŀ��
							"",			--����NPC
							"",               --������
							"",	--��������
							""					--����С��ʾ
							)
	EndQuestEvent()
	DispatchQuestLogUpdate(sceneId, selfId, subMission);
end

function x300721_GetMissionHelp(sceneId, selfId)
	local subMission = x300721_HaveWhichSubMission(sceneId, selfId)
	local szMissionHelp = ""
	if tonumber(6546) == tonumber(subMission) then
		szMissionHelp = "�������Թ�һ������200ֻ@npc_90051����@npc_123759������"
	elseif tonumber(7588) == tonumber(subMission) then
		szMissionHelp = "�������Թ���������200ֻ@npc_90053����@npc_123759������"
	elseif tonumber(7589) == tonumber(subMission) then
		szMissionHelp = "�������Թ���������200ֻ@npc_90055����@npc_123759������"
	elseif tonumber(7590) == tonumber(subMission) then
		szMissionHelp = "�������Թ��Ĳ�����200ֻ@npc_90057����@npc_123759������"
	elseif tonumber(7591) == tonumber(subMission) then
		szMissionHelp = "�������Թ��������200ֻ@npc_90059����@npc_123759������"
	elseif tonumber(7592) == tonumber(subMission) then
		szMissionHelp = "�������Թ���������200ֻ@npc_90061����@npc_123759������"
	elseif tonumber(7593) == tonumber(subMission) then
		szMissionHelp = "�������Թ��߲�����200ֻ@npc_90063����@npc_123759������"
	elseif tonumber(7594) == tonumber(subMission) then
		szMissionHelp = "�������Թ��˲�����200ֻ@npc_14004����@npc_123759������"
	elseif tonumber(7595) == tonumber(subMission) then
		szMissionHelp = "�������Թ��Ų�����200ֻ@npc_14004����@npc_123759������"
	end
	return szMissionHelp
end

function x300721_GetMissionTarget(sceneId, selfId)
	local subMission = x300721_HaveWhichSubMission(sceneId, selfId)
	local curKillMonsterNum = x300721_GetKillMonsterNum(sceneId, selfId)
	local szMonsterNum = "(" .. curKillMonsterNum .. "/200)"
	local szMissionTarget = ""
	if tonumber(6546) == tonumber(subMission) then
		szMissionTarget = "  ����200ֻ@npc_90051" .. szMonsterNum
	elseif tonumber(7588) == tonumber(subMission) then
		szMissionTarget = "  ����200ֻ@npc_90053" .. szMonsterNum
	elseif tonumber(7589) == tonumber(subMission) then
		szMissionTarget = "  ����200ֻ@npc_90055" .. szMonsterNum
	elseif tonumber(7590) == tonumber(subMission) then
		szMissionTarget = "  ����200ֻ@npc_90057" .. szMonsterNum
	elseif tonumber(7591) == tonumber(subMission) then
		szMissionTarget = "  ����200ֻ@npc_90059" .. szMonsterNum
	elseif tonumber(7592) == tonumber(subMission) then
		szMissionTarget = "  ����200ֻ@npc_90061" .. szMonsterNum
	elseif tonumber(7593) == tonumber(subMission) then
		szMissionTarget = "  ����200ֻ@npc_90063" .. szMonsterNum
	elseif tonumber(7594) == tonumber(subMission) then
		szMissionTarget = "  ����200ֻ@npc_14004" .. szMonsterNum
	elseif tonumber(7595) == tonumber(subMission) then
		szMissionTarget = "  ����200ֻ@npc_14004" .. szMonsterNum
	end
	return szMissionTarget
end

function x300721_QuestLogRefresh( sceneId, selfId, MissionId)
	local subMission = x300721_HaveWhichSubMission(sceneId, selfId)
	local szMissionDesc = "\tΪ���ô�Ҹ���Ľ�ʶ���ѣ�Ϊ���ô�Ҹ�������Ӻ��Ѷȣ�"
	.."�����������������ȡ������Ͷ�����¶�����İ���ˣ�ֻҪ��ȡ������ͶҲ��������Զ���Ϊ���ѡ�"
	.."�ɹ���ɱ����񣬻�������Ӽ���ѵĺ��Ѷȡ�"
	
	local szMissionHelp = x300721_GetMissionHelp(sceneId, selfId)
	
	local szMissionTarget = x300721_GetMissionTarget(sceneId, selfId)
	local szMissionNPC = "@npc_123759"
	local exp = x300721_CalcMissionEXP(sceneId, selfId)
	BeginQuestEvent(sceneId)
		local szMissionBonus = "\n#Y\n�������ݣ�\n#W���Ѷ�:"..x300721_g_addFriendPoint.."��";
		local szMissionExp = "\n#W����ֵ:"..exp.."��";
	AddQuestLogCustomText( sceneId,
							"����",						-- ����
							x300721_g_MissionName,        -- ��������
							szMissionTarget,		--����Ŀ��
							szMissionNPC,			--����NPC
							szMissionHelp..szMissionBonus..szMissionExp,               --������
							szMissionDesc,	--��������
							""					--����С��ʾ
							)
	EndQuestEvent()
	DispatchQuestLogUpdate(sceneId, selfId, subMission);
end

function x300721_ProcQuestLogRefresh( sceneId, selfId, MissionId)
	x300721_QuestLogRefresh( sceneId, selfId, MissionId );
end