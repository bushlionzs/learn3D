
-------------------------
--***********************
--Const
--***********************
-------------------------

x800007_g_ScriptId 					= 800007
x800007_g_MissionName				= "离婚"
x800007_g_CostMoneyUnmarry	= 55555
x800007_g_FriendPointNotify = 100
x800007_SkillId							= 149

-------------------------
--***********************
--Define
--***********************
-------------------------

x800007_CHAT_TYPE_NORMAL	= 0
x800007_CHAT_TYPE_SYSTEM	= 4

x800007_OK							= 0
x800007_ERROR_UNKNOWN		= -1
x800007_FAILED_CAPTAIN	= 1
x800007_FAILED_TEAM			= 2
x800007_FAILED_MARRIGE	= 3
x800007_FAILED_DISTANCE	= 4
x800007_FAILED_MONEY		= 5

-------------------------
--***********************
--IsCanUnmarry
--***********************
-------------------------

function x800007_IsCanUnmarry(sceneId, selfId) 
	
	if (IsCaptain(sceneId, selfId)) ~= 1 then
		return x800007_FAILED_CAPTAIN;
	end

	if (GetTeamSize(sceneId, selfId) ~= 2) then
		return x800007_FAILED_TEAM;		--组队成员不是两人不可离婚
	end
	
	local targetId = GetTeamSceneMember(sceneId, selfId, 0);
	
	if IsSpouses(sceneId, selfId, targetId) ~= 1 then
		return x800007_FAILED_MARRIGE;
	end
	
	if IsInDist(sceneId, selfId,targetId,10) ~= 1 then
		return x800007_FAILED_DISTANCE;		--双方距离大于10米不可以离婚
	end
	
	local money;
	if GetSex(sceneId, selfId) == 0 then		--自己不是男方，对方必是男方
		money = GetMoney(sceneId, targetId);
	else
		money = GetMoney(sceneId, selfId);
	end
	
	if money < x800007_g_CostMoneyUnmarry then
		return x800007_FAILED_MONEY;
	end
	
	return x800007_OK;
	
end

-------------------------
--***********************
--DoUnmarry
--***********************
-------------------------

function x800007_DoUnmarry(sceneId, selfId, NPCId)

	local ret = x800007_SafeUnmarryCheck(sceneId, selfId, NPCId, 1);
	if ret ~= x800007_OK then
		return ret;
	end
	
	local targetId = GetTeamSceneMember(sceneId, selfId, 0);
	
	local ManId;
	if GetSex(sceneId, selfId) == 1 then
		ManId = selfId;
	else
		ManId = targetId;
	end
	
	if CostMoney(sceneId, ManId, x800007_g_CostMoneyUnmarry,305) == -1 then
		return x800007_FAILED_MONEY;
	end
	
	--把双方的好友度都设置成X，X为能够看到对方在线的最低值
	SetFriendPoint(sceneId, selfId, targetId, x800007_g_FriendPointNotify);
	SetFriendPoint(sceneId, targetId, selfId, x800007_g_FriendPointNotify);
	
	--删除夫妻技能,目前没有，暂不添加
	DelSkill(sceneId, selfId, x800007_SkillId);
	DelSkill(sceneId, targetId, x800007_SkillId);
	
	--删除双方的称号"某某的夫君""某某的娘子"
	AwardSpouseTitle(sceneId, selfId, "");
	AwardSpouseTitle(sceneId, targetId, "");
		
	--在聊天窗口给男女方提示：
	local Msg = "你恢复单身了。\n 失去夫妻称号。\n 失去所有夫妻技能。";
	Msg2Player(sceneId, selfId, Msg, x800007_CHAT_TYPE_NORMAL);
	Msg2Player(sceneId, targetId, Msg, x800007_CHAT_TYPE_NORMAL);
	
	--最后一步,双方离婚
	UnMarry(sceneId, selfId, targetId);
	
	return x800007_OK;
end

-------------------------
--***********************
--SafeUnmarryCheck
--***********************
-------------------------

function x800007_SafeUnmarryCheck(sceneId, selfId, targetId, bDirect)

	local ret 	= x800007_IsCanUnmarry(sceneId, selfId);
	local str 	= "已经离婚。";
	
	if ret == x800007_OK then
		str = format("确定要离婚？\n男方需要支付%d金钱。", x800007_g_CostMoneyUnmarry);
	
	elseif ret == x800007_FAILED_CAPTAIN then
		str = "只有队长才能申请结婚。";
	
	elseif ret == x800007_FAILED_TEAM then
		str = "如果想离婚，请男女双方二人组成一队再来找我。";
	
	elseif ret == x800007_FAILED_MARRIGE then
		str = "你们还没结婚呢？为啥要离婚捏？";
	
	elseif ret == x800007_FAILED_DISTANCE then
		str = "只有二人都走到我身边才可以离婚。";
	
	elseif ret == x800007_FAILED_MONEY then
		str = format("男方需要携带%d金钱才能离婚。", x800007_g_CostMoneyUnmarry);
	end
	
	if ret == x800007_OK and bDirect == 1 then
		return ret;
	end
	
	BeginQuestEvent(sceneId);
	
		AddQuestText(sceneId, str);
	
	EndQuestEvent();

	if ret == x800007_OK then
		DispatchQuestInfo(sceneId, selfId, targetId, x800007_g_ScriptId);
	else
		DispatchQuestEventList(sceneId, selfId, targetId);
	end
	
	return ret;
	
end

-------------------------
--***********************
--ProcEnumEvent
--***********************
-------------------------

function x800007_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
	AddQuestNumText(sceneId, x800007_g_ScriptId, x800007_g_MissionName);
end

-------------------------
--***********************
--ProcEventEntry
--***********************
-------------------------

function x800007_ProcEventEntry(sceneId, selfId, targetId)

	x800007_SafeUnmarryCheck(sceneId, selfId, targetId, 0);
	
end

-------------------------
--***********************
--ProcAcceptCheck
--***********************
-------------------------

function x800007_ProcAcceptCheck(sceneId, selfId, targetId)

	return 1;

end

-------------------------
--***********************
--ProcAccept
--***********************
-------------------------

function x800007_ProcAccept(sceneId, selfId, targetId)

	local ret = x800007_DoUnmarry(sceneId, selfId, targetId);
	
	if ret == x800007_OK then
		return
	end
	
	local str = "ERROR。";
	
	if ret == x800007_FAILED_MONEY then
		str = "扣除金钱错误。";
	end
	
	BeginQuestEvent(sceneId);
	
		AddQuestText(sceneId, str);
	
	EndQuestEvent();

	DispatchQuestEventList(sceneId, selfId, targetId);

end