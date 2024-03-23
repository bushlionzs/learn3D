
x700096_g_ScriptId = 700096
x700096_g_MissionName = "【队伍】三环副本"

x700096_g_LevelLimited = 20

x700096_g_LimitMember = 1
--三环副本入口
x700096_g_SanHuan_Fuben_Len = 7
x700096_g_SanHuan_Fuben_list = { 
							{name="【队伍】祝家庄",		scriptid = 700030, nlevel = 60},
							{name="【队伍】财神殿",		scriptid = 700003, nlevel = 50},
							{name="【队伍】和氏璧",		scriptid = 700024, nlevel = 40},
							{name="【队伍】囚龙岛",		scriptid = 700028, nlevel = 20},
							{name="【队伍】探索战神墓",	scriptid = 700084, nlevel = 35},
							{name="【队伍】印度河",	    scriptid = 700087, nlevel = 55},
							{name="【队伍】教堂的秘密",	scriptid = 700090, nlevel = 45},
							
						}

function x700096_ProcEnumEvent( sceneId, selfId, targetId, index )
	
	local nLevel = GetLevel(sceneId, selfId)
	if nLevel < x700096_g_LevelLimited then

		return
		
	end	

	AddQuestNumText(sceneId,x700096_g_ScriptId, x700096_g_MissionName, 14, 0)
end

function x700096_ProcEventEntry( sceneId , selfId , targetId , state , nExt )
	
	if nExt == nil then
		return
	end


	x700096_DispatchSanHuanMode(sceneId , selfId , targetId  , nExt)
	
end

function x700096_DispatchSanHuanMode(sceneId , selfId , targetId  , nExt)
	if nExt == nil then
		return
	end

	local nLevel = GetLevel(sceneId, selfId)
	if nLevel < x700096_g_LevelLimited then
		return
	end

	
	if nExt == 0 then
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"\t只要你和几个志同道合的朋友一起组队，我就可以送你们进入三环副本，获得高额经验值，还有可能获得极其稀有的异形坐骑。\n\t此外，我这里还有单人三环副本（试炼）、英雄模式三环副本（高难度）和三番三环副本供你选择。")
			AddQuestNumText(sceneId,x700096_g_ScriptId, "【队伍】普通三环副本", 14, 1)
			AddQuestNumText(sceneId,x700096_g_ScriptId, "【队伍】三番三环副本", 14, 2)
			--AddQuestNumText(sceneId,x700096_g_ScriptId, x700096_g_MissionName.."周三番模式", 14, 3)
		EndQuestEvent()
		DispatchQuestEventList(sceneId, selfId, targetId)
	else
		x700096_DispatchDetailMode(sceneId , selfId , targetId  , nExt)
	end
	
end

function x700096_DispatchDetailMode(sceneId , selfId , targetId  , nExt)

	if nExt == nil then
		return
	end

	BeginQuestEvent(sceneId)
		
		if nExt ==1 then
			AddQuestText(sceneId,"#Y"..x700096_g_MissionName.."普通模式")
		elseif nExt ==2 then
			AddQuestText(sceneId,"#Y"..x700096_g_MissionName.."三番模式")
		elseif nExt ==3 then
			AddQuestText(sceneId,"#Y"..x700096_g_MissionName.."周三番模式")
		else
			return
		end
		--任务信息
		AddQuestText(sceneId,"\n\t每周一共可以进行21次普通三环副本。使用三番令进入三环副本，消耗3次本周的三环副本次数，同时获得3次普通副本的奖励。若本周剩余三环副本次数不足3次，则不可使用三番令。")

		if nExt ==1 then
			AddQuestText(sceneId,"\n#Y开放时间：#W全天开放！\n#Y友情提示：#W3人以上的队伍，才能进入该副本！\n#Y副本说明：#W在这个副本中，你可以获得大量经验奖励！")
		elseif nExt ==2 then
			AddQuestText(sceneId,"\n#Y开放时间：#W全天开放！\n#Y友情提示：#W3人以上的队伍，才能进入该副本！\n#Y副本说明：#W在这个副本中，你可以获得普通三番副本3倍的经验奖励！")
		elseif nExt ==3 then
			AddQuestText(sceneId,"副本说明："..x700096_g_MissionName.."周三番模式")
		else
			return
		end

		x700096_SaveSanhuanFubenTalkMode(sceneId, selfId, nExt)


	EndQuestEvent()

	DispatchQuestInfo(sceneId, selfId, targetId, x700096_g_ScriptId, -1);
end

---------------------------------------------------------------------------------------------------
--申请进入副本
---------------------------------------------------------------------------------------------------
function x700096_ProcAcceptCheck( sceneId, selfId, NPCId )

	local nLevel = GetLevel(sceneId, selfId)
	if nLevel < x700096_g_LevelLimited then
		return 0
	end

    return 1
end

----------------------------------------------------------------------------------------------
--点确定后
----------------------------------------------------------------------------------------------
function x700096_ProcAccept( sceneId, selfId )
	if x700096_CheckCommonTeamCondition(sceneId, selfId)<=0 then
		return
	end

	local nMode = x700096_GetSanhuanFubenTalkMode(sceneId, selfId)

	if nMode<=0 or nMode>3 then
		return
	end

	local nRandom = x700096_GetRandom(sceneId, selfId)

	if nRandom<=0 then
		return
	end

	local nScriptId = x700096_g_SanHuan_Fuben_list[7].scriptid --TEST
	
	nMode = nMode -1
	CallScriptFunction(FUBEN_COMMON_SCRIPT, "OnRequestEnterFuben", sceneId, selfId, nMode, 0, nScriptId, 0);
	
	--写日志
	local msg = format("x700096_ProcAccept 三环, sceneId = %d, name = %s, nMode = %d, nScriptId = %d", sceneId,GetName(sceneId, selfId), nMode,nScriptId);

	WriteLog(1,msg)



end

function x700096_GetRandom(sceneId, selfId)
	local nLevel = x700096_GetTeamMinLevel(sceneId, selfId)
	
	local randomlist = {}
	local nCount = 0
	local nIndex = 0
	for i, item in x700096_g_SanHuan_Fuben_list do
		nIndex = nIndex + 1
		if nLevel>=item.nlevel then
			nCount = nCount +1
			randomlist[nCount] = nIndex
		end
	end

	if nCount ==0 then
		return 0
	end

	return randomlist[random(1,nCount)]
end

function x700096_GetTeamMinLevel(sceneId, selfId)

	if IsTeamLeader(sceneId, selfId) <= 0 then
		local nLevel = GetLevel(sceneId, selfId)
		return nLevel
	end

	local teamid = GetTeamId(sceneId, selfId);
	local teamnum = GetTeamSize(sceneId, selfId);
	local nearteamnum = GetNearTeamCount(sceneId, selfId);
	
	local nMinLevel = 200
	for i = 0, teamnum - 1 do
		local memberId = GetNearTeamMember(sceneId, selfId, i);
		
		local nLevel = GetLevel(sceneId, memberId)

		if nLevel<nMinLevel then
			nMinLevel = nLevel
		end
	end

	return nMinLevel
end

function x700096_CheckCommonTeamCondition(sceneId, selfId)
	local teamid = GetTeamId(sceneId, selfId);
	local teamnum = GetTeamSize(sceneId, selfId);
	local nearteamnum = GetNearTeamCount(sceneId, selfId);

	local str = "";
	local bPassed = 1;

	if IsTeamLeader(sceneId, selfId) <= 0 then
		str	= "你不是队长！"
		bPassed = 0
	elseif x700081_CheckAllMemberNear( sceneId,selfId) <= 0 then
		str	= "需要所有的队友在附近！"
		bPassed = 0
	elseif teamid < 0 then
		str	= "你不在队伍中！"
		bPassed = 0
	elseif teamnum < x700096_g_LimitMember then
		str	= format("你的队伍不足%d人！", x700096_g_LimitMember)
		bPassed = 0
	elseif nearteamnum < x700096_g_LimitMember then
		str	= format("附近队友不足%d人！", x700096_g_LimitMember)
		bPassed = 0
	else

		for i = 0, teamnum - 1 do
			local memberId = GetNearTeamMember(sceneId, selfId, i);
			
			local nLevel = GetLevel(sceneId, memberId)

			if nLevel<x700096_g_LevelLimited then
				local strName = GetName(sceneId, memberId)
				str = format("队友%s等级低于%d级，不能进入副本！", strName,x700096_g_LevelLimited)
				bPassed = 0

				break;
			end
		end
		

	end

	if bPassed == 1 then
		return 1;
	else
		if str ~= "" then
			BeginQuestEvent(sceneId);
				AddQuestText(sceneId, str);
			EndQuestEvent();
			DispatchQuestTips(sceneId, selfId);
			return 0;
		end
	end


	return 1;
end


function x700096_SaveSanhuanFubenTalkMode(sceneId, selfId, nValue)
	SetQuestData(sceneId, selfId, MD_SANHUAN_FUBEN_TALK_MODE[1], MD_SANHUAN_FUBEN_TALK_MODE[2], MD_SANHUAN_FUBEN_TALK_MODE[3], nValue)
end

function x700096_GetSanhuanFubenTalkMode(sceneId, selfId)
	return GetQuestData(sceneId, selfId, MD_SANHUAN_FUBEN_TALK_MODE[1], MD_SANHUAN_FUBEN_TALK_MODE[2], MD_SANHUAN_FUBEN_TALK_MODE[3])
end


