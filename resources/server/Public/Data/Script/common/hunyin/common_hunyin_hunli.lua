
-------------------------
--***********************
--Const
--***********************
-------------------------

x800049_g_ScriptId 					= 800049
x800049_g_MissionName				= "【婚姻】举办婚礼"
x800049_g_NeedGold					= 18888

-------------------------
--***********************
--ProcEnumEvent
--***********************
-------------------------

function x800049_ProcEnumEvent(sceneId, selfId, targetId, eventId, index)
	AddQuestNumText(sceneId, x800049_g_ScriptId, x800049_g_MissionName,3);
end

-------------------------
--***********************
--ProcEventEntry
--***********************
-------------------------

function x800049_ProcEventEntry(sceneId, selfId, targetId)
	BeginQuestEvent(sceneId);
	local Readme_1 = "#Y【婚姻】举办婚礼#W#r"
	local Readme_2 = "\t成吉思汗中，夫妻们可以通过举办婚礼来召唤亲朋好友，与他们欢聚一堂并能获得他们祝福。#r #r"
	local Readme_3 = "如果您要结婚需要满足四个条件：#r #r"
	local Readme_4 = "1.您必须与您的配偶组成#G2人队伍#W。#r #r"
	local Readme_5 = "2.您必须与您的配偶互相#G在一起#W。#r #r"
	local Readme_6 = "3.您与同一配偶只能举办#G一次婚礼#W。#r #r"
	local Readme_7 = format("4.您只须拥有#Y#{_MONEY%d}金卡（现金）#W便可举办#G一次婚礼#W。#r #r", x800049_g_NeedGold)
	local Readme_8 = "\t一切都准备好了就可以举行婚礼了。"
	local Readme = Readme_1..Readme_2..Readme_3..Readme_4..Readme_5..Readme_6..Readme_7..Readme_8
	AddQuestText(sceneId, Readme);
	EndQuestEvent();
	DispatchQuestInfo(sceneId, selfId, targetId, x800049_g_ScriptId, -1);
end

-------------------------
--***********************
--ProcAcceptCheck
--***********************
-------------------------

function x800049_ProcAcceptCheck(sceneId, selfId, targetId)

	return 1;

end

-------------------------
--***********************
--ProcAccept
--***********************
-------------------------

function x800049_ProcAccept(sceneId, selfId, targetId)
	local str = x800049_DoWedding(sceneId, selfId, targetId)
	if str ~= nil then
		Msg2Player(sceneId,selfId,str,CHAT_TYPE_SELF,CHAT_RIGHTDOWN)
		Msg2Player(sceneId,selfId,str,CHAT_TYPE_SELF,CHAT_PLUMB_SCROLL)
	end
end

function x800049_DoWedding(sceneId, selfId, targetId)
	
	if 0 >= IsEnoughGold(sceneId, selfId, x800049_g_NeedGold) then
		return format("很抱歉，需要#{_MONEY%d}金卡（现金）才可以举办婚礼。", x800049_g_NeedGold)
	end
	if IsMarried(sceneId, selfId) ~= 1 then
		return "很抱歉，您还未结婚，无法选择婚礼。"
	end
	if HasTeam(sceneId, selfId) ~= 1 then
		return "很抱歉，您还未进行组队无法选择婚礼。"
	end
	
	if (GetTeamSize(sceneId, selfId) < 2) then
		return "很抱歉，您所在的队伍中成员小于2人，无法选择婚礼。";
	end
	
	if (GetTeamSize(sceneId, selfId) > 2) then
		return "很抱歉，您所在的队伍中成员大于2人，无法选择婚礼。";
	end

	local targetId = GetTeamSceneMember(sceneId, selfId, 0);
	
	if IsInDist(sceneId, selfId, targetId, 10) ~= 1 then
		return "很抱歉，您的队友不在附近，无法选择婚礼。";
	end
	
	if IsSpouses(sceneId, selfId, targetId) ~= 1 then
		return "很抱歉，您所在的队伍中成员不是夫妻关系，无法选择婚礼。";
	end		
	
	if IsHaveWedding(sceneId, selfId) == 1 then
		return "很抱歉，您已经举办过婚礼，不可以再次举办。";
	end
	local nEvent = 46 --举办婚礼
	local bMutex, errCode = IsMutex(sceneId, selfId, nEvent) 
	if bMutex == 1 then
		return "很抱歉，您当前的状态不可以举办婚礼。";
	end 
	
	bMutex, errCode = IsMutex(sceneId, targetId, nEvent) 
	if bMutex == 1 then
		return "很抱歉，您配偶当前的状态不可以举办婚礼。";
	end
	local IsSelfMan = GetSex(sceneId, selfId);
	local ManId;
	local WomanId;
	if IsSelfMan > 0 then
		ManId = selfId;
		WomanId = targetId;
	else
		ManId = targetId;
		WomanId = selfId;
	end
	
	if 0 >= x800049_CostGold(sceneId, selfId) then
		return "扣钱错误";
	end
	
	DoWedding(sceneId, selfId)
	DoWedding(sceneId, targetId)
	
	local szMsg = format("今日是%s和%s的大喜之日，希望您能参加，并带来你的祝福。", GetName( sceneId, WomanId ), GetName(sceneId, ManId));
	local MoneyReceiver = GetName( sceneId, WomanId )
	WeddingInvite(sceneId, selfId, MoneyReceiver, szMsg)
	WeddingInvite(sceneId, targetId, MoneyReceiver, szMsg)
	
	DispelImpact(sceneId, ManId)
	DispelImpact(sceneId, WomanId)
	
	SetPlayerPatrolId(sceneId, ManId, 0);
	SetPlayerPatrolId(sceneId, WomanId, 0);

	Teleport(sceneId, WomanId, 123, 58)
	Teleport(sceneId, ManId, 123, 64)
	SendSpecificImpactToUnit(sceneId, ManId, ManId, ManId, 7642, 0);--巡逻
	SendSpecificImpactToUnit(sceneId, WomanId, WomanId, WomanId, 7642, 0);--巡逻
	SendSpecificImpactToUnit(sceneId, ManId, ManId, ManId, 7641, 0);--车
	SendSpecificImpactToUnit(sceneId, WomanId, WomanId, WomanId, 7640, 0);--马
	local mamName = GetName(sceneId, ManId)
	local womamName = GetName(sceneId, WomanId)
	local str = format("恭喜%s与%s举办了别开生面的婚礼，并收到了亲朋好友的祝福。", mamName, womamName);
	LuaAllScenceM2Wrold (sceneId, str, CHAT_MAIN_WINDOW, 1)
	
	SendSpecificImpactToUnit(sceneId, ManId, ManId, ManId, 8537, 0);--掉落物品
	
	return nil
	
end

function x800049_CostGold(sceneId, selfId)
	local nGoldMode = GetGoldMode( sceneId, selfId )
	
	if nGoldMode == 1 then		--优先现金结算
		if CostMoney(sceneId, selfId, 2, x800049_g_NeedGold,305) == -1 then
			return 0
		end
	
	elseif nGoldMode == 0 then	--优先金卡结算
		if CostMoney(sceneId, selfId, 3, x800049_g_NeedGold,305) == -1 then
			if CostMoney(sceneId, selfId, 2, x800049_g_NeedGold,305) == -1 then
				return 0
			end
		end
	else						--未知的结算模式
		return 0
	end
	return 1
end
function DispelImpact(sceneId, selfId)
	DispelSpecificImpact(sceneId, selfId, 7902)
	DispelSpecificImpact(sceneId, selfId, 10330)
	for i = 4211, 4220 do
		DispelSpecificImpact(sceneId, selfId, i)
	end
end