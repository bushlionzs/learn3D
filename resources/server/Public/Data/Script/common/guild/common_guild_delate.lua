
-------------------------
--***********************
--Const
--***********************
-------------------------

x300828_g_ScriptId 					= 300828
x300828_g_MissionName				= "【帮会】弹劾帮主"
x300828_g_NeedMoney = 20000
x300828_g_GameId					= 1032
-------------------------
--***********************
--ProcEnumEvent
--***********************
-------------------------

function x300828_ProcEnumEvent(sceneId, selfId, targetId, eventId, index)
	if 0 > GetGuildID(sceneId, selfId) then
		return
	end
	if GetGameOpenById(x300828_g_GameId) <= 0 then
		return
	end
	AddQuestNumText(sceneId, x300828_g_ScriptId, x300828_g_MissionName,3);
end

-------------------------
--***********************
--ProcEventEntry
--***********************
-------------------------

function x300828_ProcEventEntry(sceneId, selfId, targetId)
	BeginQuestEvent(sceneId);
	local Readme = "#Y【帮会】弹劾帮主#W#r\t每周日的21：00-22：00之间，30级以上的帮会成员可以在我这里可以发起#R弹劾帮主#W。\n\t发起者需要花费#Y20两现银#W发起对#G本帮帮主#W的弹劾，#G在线本帮成员#W将会收到#G弹劾框#W，响应弹劾的帮众#R超过90%#W，则#R帮主自动下台#W成为帮会成员，同时#R发起者自动成为帮主#W。\n\t您是否要发起弹劾？"
	AddQuestText(sceneId, Readme);
	EndQuestEvent();
	DispatchQuestInfo(sceneId, selfId, targetId, x300828_g_ScriptId, -1);
end

-------------------------
--***********************
--ProcAcceptCheck
--***********************
-------------------------

function x300828_ProcAcceptCheck(sceneId, selfId, targetId)

	return 1;

end

-------------------------
--***********************
--ProcAccept
--***********************
-------------------------

function x300828_ProcAccept(sceneId, selfId, targetId)
	local str = x300828_DoGuildDelate(sceneId, selfId, targetId)
	if str ~= nil then
		Msg2Player(sceneId,selfId,str,CHAT_TYPE_SELF,CHAT_RIGHTDOWN)
		Msg2Player(sceneId,selfId,str,CHAT_TYPE_SELF,CHAT_PLUMB_SCROLL)
	end
end

function x300828_DoGuildDelate(sceneId, selfId, targetId)
	
	if 30 > GetLevel(sceneId, selfId) then
		return "很抱歉，您的等级太低。"
	end
	
	if 0 > GetGuildID(sceneId, selfId) then
		return "很抱歉，您还没有加入帮会。"
	end
	
	local week = GetWeek()
	local hour,minute,second = GetHourMinSec()
	if 0 == week and hour == 21 then
	else
		return "很抱歉，请在周日21：00-22：00时前来进行弹劾。"
	end
	
	if 0 >= IsEnoughMoney(sceneId, selfId, x300828_g_NeedMoney) then
		return "很抱歉，您的现银不足，不能进行弹劾。"
	end
	
	local nLairdMapId = GetGuildLairdSceneId(GetGuildID(sceneId, selfId))
	if nLairdMapId > 0 then
		return "很抱歉，领地占领帮会，不能进行弹劾帮主。"
	end
	
	local remainTime = ( 59 - minute) * 60 * 1000
	GuildDelateReq(sceneId, selfId, remainTime)
	return nil
	
end

function x300828_OnGuildDelateRet(sceneId, selfId, retCode)
	
	if 0 == retCode then
		Msg2Player(sceneId,selfId,"弹劾申请成功提交",8,3)
		Msg2Player(sceneId,selfId,"弹劾申请成功提交",8,2)
	elseif 1 == retCode then
		Msg2Player(sceneId,selfId,"不能弹劾自己",8,3)
		Msg2Player(sceneId,selfId,"不能弹劾自己",8,2)
	elseif 2 == retCode then
		Msg2Player(sceneId,selfId,"已经在弹劾中",8,3)
		Msg2Player(sceneId,selfId,"已经在弹劾中",8,2)
	elseif 3 == retCode then
		Msg2Player(sceneId,selfId,"不能弹劾国王",8,3)
		Msg2Player(sceneId,selfId,"不能弹劾国王",8,2)
	elseif 4 == retCode then
		Msg2Player(sceneId,selfId,"帮会成员的在线人数太少",8,3)
		Msg2Player(sceneId,selfId,"帮会成员的在线人数太少",8,2)
	elseif 5 == retCode then
		Msg2Player(sceneId,selfId,"不能弹劾青龙之主",8,3)
		Msg2Player(sceneId,selfId,"不能弹劾青龙之主",8,2)
	elseif 6 == retCode then
		Msg2Player(sceneId,selfId,"不能弹劾朱雀之主",8,3)
		Msg2Player(sceneId,selfId,"不能弹劾朱雀之主",8,2)
	end
	
	if 0 == retCode then
		if 0 >= SpendMoney(sceneId, selfId, x300828_g_NeedMoney) then
			return -1;
		end
	end
	
	return 1
end