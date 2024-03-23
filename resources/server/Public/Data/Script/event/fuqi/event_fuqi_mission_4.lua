
x300354_g_ScriptId = 300354

function x300354_SetMissionData(sceneId, selfId)
		SetQuestData(sceneId, selfId, MD_SPOUSE_MISSION_DATE[1][1], MD_SPOUSE_MISSION_DATE[1][2], MD_SPOUSE_MISSION_DATE[1][3], GetDayOfYear())
end

function x300354_OnTime(sceneId,BusId)

end

--人下线 护送目标被删除 人上线 删除任务
function x300354_Abandon( sceneId, selfId )
	local strText = "由于您离开#G淘气的小孩#W#o时间过久，孩童走失了，任务失败！"
	BeginQuestEvent(sceneId)
	AddQuestText(sceneId, strText);
	EndQuestEvent(sceneId)
	DispatchQuestTips(sceneId,selfId)
	Msg2Player(sceneId,selfId,strText,8,2)
	DelQuestNM( sceneId, selfId, SPOUSE_TASK[2] )
	
	x300354_SetMissionData(sceneId, selfId)
	
	--发可执行邮件给配偶
	local spouseGuid = GetSpouseGUID( sceneId, selfId )
	local spouseName = GetFriendName( sceneId, selfId, tonumber(spouseGuid) )
	SendScriptMail( sceneId, spouseName, MAIL_DELETE_MISSION, SPOUSE_TASK[2], 0, 0, selfId )
end

function x300354_OnLifeTimeOut(sceneId,BusId)
	x300354_OnWaitTimeOut(sceneId,BusId)
end

function x300354_OnWaitTimeOut(sceneId,BusId)
	local selfId = GetBusMemberObjId(sceneId,BusId,0)
	if(IsPlayerStateNormal(sceneId, selfId) ~= 0) then

		local strText = "由于您离开#G淘气的小孩#W#o时间过久，孩童走失了，任务失败！"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, strText);
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,strText,8,2)
		DelQuestNM( sceneId, selfId, SPOUSE_TASK[2] )	
		
		x300354_SetMissionData(sceneId, selfId)
		
		--发可执行邮件给配偶
		local spouseGuid = GetSpouseGUID( sceneId, selfId )
		local spouseName = GetFriendName( sceneId, selfId, tonumber(spouseGuid) )
		SendScriptMail( sceneId, spouseName, MAIL_DELETE_MISSION, SPOUSE_TASK[2], 0, 0, selfId )
	
	end
	DeleteBus(sceneId, BusId,1)
end

function x300354_OnBusStopWhenOwnerFarAway(sceneId, ownerId)
	local strText = "很抱歉，由于您离开#G淘气的小孩#o过远，迷路的他留在原地哇哇大哭！"
	BeginQuestEvent(sceneId)
	AddQuestText(sceneId, strText);
	EndQuestEvent(sceneId)
	DispatchQuestTips(sceneId, ownerId)
	Msg2Player(sceneId,ownerId,strText,8,2)
end

function x300354_OnIntoBusEvent(sceneId, selfId, targetId)
	local IsOwner = IsTheBusOwner(sceneId, selfId, targetId )
	if IsOwner == 1 then
		--进入BUS
		AddBusMember(sceneId, selfId,targetId)
	end
end

function x300354_OnIntoBusAfter(sceneId, selfId,BusID)

    if(IsObjValid (sceneId,BusID) ~= 1)then
        return
    end

	local MissionId = GetBusQuestID(sceneId,BusID)

	local CarName = GetName( sceneId, selfId ).."护送的孩童"
	SetBusTitle(sceneId , BusID, CarName)

	local camp = GetCurCamp(sceneId, selfId)
	SetBusCurCamp(sceneId, BusID,camp)
	
end

function x300354_OnLeaveBusEvent(sceneId, selfId,BusId)
end

function x300354_OnDie(sceneId,BusId,idKiller)
end

function x300354_ProcEventEntry( sceneId, selfId, targetId, MissionId, index )
end

function x300354_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
	
end

function x300354_OnCreateBusOK(sceneId,selfId,busId,targetId,MissionId)	
	
	SetBusTimerTick(sceneId , busId, 1000)
	SetBusWaitTime(sceneId , busId, 300)
	SetBusLifeTime(sceneId , busId, 30000)
	SetBusTimerOpen(sceneId, busId, 0)
	--SetBusCurCamp(sceneId, busId,20)
	SetBusQuestID(sceneId,busId,SPOUSE_TASK[2])
end