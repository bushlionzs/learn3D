
-------------------------
--***********************
--Const
--***********************
-------------------------

x300316_g_ScriptId 					= 300316
x300316_g_MissionName				= "【国家】弹劾国王"
x300316_g_NeedMoney = 20000
x300316_g_GameId						= 1023 --十八魔君开关
x300316_g_GameOpenId				= 1031 --玩法开关
-------------------------
--***********************
--ProcEnumEvent
--***********************
-------------------------

function x300316_ProcEnumEvent(sceneId, selfId, targetId, eventId, index)
	if GetGameOpenById(x300316_g_GameOpenId) <= 0 then
		return
	end
	AddQuestNumText(sceneId, x300316_g_ScriptId, x300316_g_MissionName,3);
end

-------------------------
--***********************
--ProcEventEntry
--***********************
-------------------------

function x300316_ProcEventEntry(sceneId, selfId, targetId)
	BeginQuestEvent(sceneId);
	local Readme1 = "#Y【国家】弹劾国王#W#r\t当等级排行榜第一名超过70级时，每周二晚#R20：00-21：00之间#W，在本国#R排名前5名非国王帮帮会#W的#G任意帮主#W可以在我这里发起弹劾国王。"
	local Readme2 =  "如果除#G发起者之外#W的另外#G四位帮主中的二位#W同意发起#R弹劾国王#W。#G40级以#W上在线国民将会收到#G弹劾框#W，如果在线国民低于150人，则弹劾自动失败。#G响应弹劾#W的国民超过#R70%#W，则#R国王自动下台#W，同时#R国王帮自动下台#W，发起弹劾的帮会自动成为#G新国王帮#W，该帮帮主成为#G新的国王#W。"
	local Readme  =  Readme1..Readme2
	AddQuestText(sceneId, Readme);
	EndQuestEvent();
	DispatchQuestInfo(sceneId, selfId, targetId, x300316_g_ScriptId, -1);
end

-------------------------
--***********************
--ProcAcceptCheck
--***********************
-------------------------

function x300316_ProcAcceptCheck(sceneId, selfId, targetId)

	return 1;

end

-------------------------
--***********************
--ProcAccept
--***********************
-------------------------

function x300316_ProcAccept(sceneId, selfId, targetId)
	local str = x300316_DoCountryDelate(sceneId, selfId, targetId)
	if str ~= nil then
		Msg2Player(sceneId,selfId,str,CHAT_TYPE_SELF,CHAT_RIGHTDOWN)
		Msg2Player(sceneId,selfId,str,CHAT_TYPE_SELF,CHAT_PLUMB_SCROLL)
	end
end

function x300316_DoCountryDelate(sceneId, selfId, targetId)
	
	local guildId = GetGuildID(sceneId, selfId)
	if 0 > guildId then
		return "很抱歉，您还没有加入帮会。"
	end
	
	local guildLevel,memNum,guidEXP = GetGuildSimpleData(guildId)
	if 2 > guildLevel then
		return "很抱歉，您的帮会等级太低。"
	end
	
	if 5 ~= GetGuildOfficial(sceneId, selfId) then
		return "很抱歉，只有帮主才能发起弹劾。"
	end
	
	if 30 > GetLevel(sceneId, selfId) then
		return "很抱歉，您的等级太低。"
	end
	
	local week = GetWeek()
	local hour,minute,second = GetHourMinSec()
	if (2 == week and hour >= 20 and hour < 21) then
	else
		return "很抱歉，请在周二20：00-21：00时前来进行弹劾。"
	end
	
	-- if GetGameOpenById(x300316_g_GameId) ~= 1 then
		-- return "十八魔君全部被击杀，才能弹劾国王。"
	-- end
	
	local remainTime = ((20 - hour)*3600 + (59 - minute)*60)*1000
	CountryDelateReq(sceneId, selfId, remainTime)
	
	return nil
	
end

function x300316_OnCountryDelateRet(sceneId, selfId, retCode)
	if 0 == retCode then
		Msg2Player(sceneId,selfId,"弹劾申请成功提交。",8,3)
		Msg2Player(sceneId,selfId,"弹劾申请成功提交。",8,2)
	elseif 1 == retCode then
		Msg2Player(sceneId,selfId,"不能弹劾自己。",8,3)
		Msg2Player(sceneId,selfId,"不能弹劾自己。",8,2)
	elseif 2 == retCode then
		Msg2Player(sceneId,selfId,"已经在弹劾中。",8,3)
		Msg2Player(sceneId,selfId,"已经在弹劾中。",8,2)
	elseif 3 == retCode then
		Msg2Player(sceneId,selfId,"没有足够的帮主在线。",8,3)
		Msg2Player(sceneId,selfId,"没有足够的帮主在线。",8,2)
	elseif 4 == retCode then
		Msg2Player(sceneId,selfId,"没有国王。",8,3)
		Msg2Player(sceneId,selfId,"没有国王。",8,2)
	elseif 5 == retCode then
		Msg2Player(sceneId,selfId,"需要更高的帮会排名。",8,3)
		Msg2Player(sceneId,selfId,"需要更高的帮会排名。",8,2)
	end
	return 1
end

-- 关闭玩法GM指令
function x300316_SetClose( param0, param1, param2)
    SetCountryQuestData( param0, 1, CD_INDEX_MOJUN_KILL_COUNT1, 0)
    SetGameOpenById( 1021, 0)
    SetGameOpenById( 1023, 0)
    SetGameOpenById( 1031, 0)
end
