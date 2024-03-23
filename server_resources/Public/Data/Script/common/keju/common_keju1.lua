--MD_KEJU_DAYCOUNT			= 81


-------------------------
--***********************
--Const
--***********************
-------------------------

--MisDescBegin

x300110_g_MissionId					= 5250
x300110_g_ScriptId 					= 300110
x300110_g_MissionName				= "科举"
x300110_g_MissionNameIn			= "继续科举"
x300110_g_MissionKind				= 23
x300110_g_MissionLevel			= 1


x300110_g_MissionTarget			= "请回答问题！"

--MisDescEnd

x300110_g_MissionInfo					=	"是否开始科举？将扣除%d锭%d两%d文银子！"
x300110_g_MissionContinueInfo	=	"请继续答题！"
x300110_g_MissionCompleteInfo	=	"恭喜你回答完全部题目！"
x300110_g_StartMessage				= "开始答题！"

x300110_g_LevelGreat				= 20
x300110_g_RoundLimit				= 3

x300110_g_TotalNum				= 20
x300110_g_AnswerTime			= 20

x300110_g_EnterFeeRate		= 100
x300110_g_GetExpRate			= 200
														
x300110_g_MissionBonusInfo			= "你获得了%d经验！"

x300110_g_ErrorMessage					= "条件不符！"			
x300110_g_ErrorMessage_Money		= "你需要%d锭%d两%d文银子来参加科举！"
x300110_g_ErrorMessage_Round		= format("你今天已经做过%d次科举了！", x300110_g_RoundLimit)

-------------------------
--***********************
--Define
--***********************
-------------------------

x300110_OK							= 0
x300110_OK_MISSION			= 1
--x300110_OK_ALLOVER			=	2
x300110_ERROR_UNKNOWN		= -1

x300110_FAILED_MONEY		= 10
x300110_FAILED_ROUND		= 11

x300110_DISP_TIPS					= 0
x300110_DISP_MISSION			= 1
x300110_DISP_CONTINUE			= 2
x300110_DISP_EVENT				= 3

-------------------------
--***********************
--CheckCountry
--***********************
-------------------------

function x300110_CheckCountry(sceneId, selfId, NPCId)

	local country = GetCurCountry(sceneId, selfId);
	if sceneId == hc_CountrySceneList[country+1] then
		return 1;
	end
	return 1;

end

-------------------------
--***********************
--SafeDisplayCheck
--***********************
-------------------------

function x300110_SafeDisplayCheck(sceneId, selfId, NPCId)

	if x300110_CheckCountry(sceneId, selfId, NPCId) <= 0 then
		return 0;
	end
	if GetLevel(sceneId, selfId) < x300110_g_LevelGreat then
		return 0;
	end
	return 1;

end

-------------------------
--***********************
--ProcEnumEvent
--***********************
-------------------------

function x300110_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)

	if x300110_SafeDisplayCheck(sceneId, selfId, NPCId) > 0 then
		local misname = x300110_g_MissionName;
		if GetQuizGameQuestionIdx(sceneId, selfId) > 0 then
			misname = x300110_g_MissionNameIn;
		end
		AddQuestNumText(sceneId, x300110_g_ScriptId, misname);
	end

end

-------------------------
--***********************
--CheckIsAnswering
--***********************
-------------------------

function x300110_CheckIsAnswering(sceneId, selfId)

	return 0;

end

-------------------------
--***********************
--SafeNPCCheck
--***********************
-------------------------

function x300110_SafeNPCCheck(sceneId, selfId, NPCId)

--	if IsHaveQuest(sceneId, selfId, x300110_g_MissionId) > 0 then
--		local misIndex = GetQuestIndexByID(sceneId, selfId, x300110_g_MissionId);
--		if GetQuestParam(sceneId, selfId, misIndex, x300110_MP_NOWNUM) >= 20 then
--			return x300110_OK_ALLOVER, x300110_DISP_CONTINUE;
--		end
--		return x300110_OK_MISSION, x300110_DISP_EVENT;
--	end
	if x300110_CheckIsAnswering(sceneId, selfId) > 0 then
		return x300110_OK_MISSION, x300110_DISP_EVENT
	end
	if x300110_GetRound(sceneId, selfId) >= x300110_g_RoundLimit then
		return x300110_FAILED_ROUND, x300110_DISP_EVENT;
	end
	local costmoney = x300110_GetEnterFee(sceneId, selfId);
	if GetMoney(sceneId, selfId, 1) < costmoney then
		return x300110_FAILED_MONEY, x300110_DISP_EVENT;
	end
	return x300110_OK, x300110_DISP_MISSION;

end

-------------------------
--***********************
--GetEnterFee
--***********************
-------------------------

function x300110_GetEnterFee(sceneId, selfId)

	return GetLevel(sceneId, selfId) * x300110_g_EnterFeeRate;

end

-------------------------
--***********************
--GetEnterFeeJYT
--***********************
-------------------------

function x300110_GetEnterFeeJYT(sceneId, selfId)

	local money = x300110_GetEnterFee(sceneId, selfId);
	
	local moneyjin = floor(money / 1000000);
	local moneyyin = floor(money / 1000) - moneyjin * 1000;
	local moneytong = money - moneyjin * 1000000 - moneyyin * 1000;
	
	return moneyjin, moneyyin, moneytong;

end

-------------------------
--***********************
--ProcEventEntry
--***********************
-------------------------

function x300110_ProcEventEntry(sceneId, selfId, NPCId)

	local safeCheckRet, dispatchType = x300110_SafeNPCCheck(sceneId, selfId, NPCId);

	local str = x300110_g_MissionName;
	str = str.."\n";

	if safeCheckRet == x300110_OK then
		str = str..format(x300110_g_MissionInfo, x300110_GetEnterFeeJYT(sceneId, selfId));
	elseif safeCheckRet == x300110_OK_MISSION then
		str = str..x300110_g_MissionContinueInfo;
--	elseif safeCheckRet == x300110_OK_ALLOVER then
--		str = str..x300110_g_MissionCompleteInfo;
	elseif safeCheckRet == x300110_FAILED_ROUND then
		str = str..x300110_g_ErrorMessage_Round;
	elseif safeCheckRet == x300110_FAILED_MONEY then
		str = str..format(x300110_g_ErrorMessage_Money, x300110_GetEnterFeeJYT(sceneId, selfId));
	end
	
	BeginQuestEvent(sceneId);
		AddQuestText(sceneId, str);
	EndQuestEvent();

	if dispatchType == x300110_DISP_MISSION then
		DispatchQuestInfo(sceneId, selfId, NPCId, x300110_g_ScriptId, x300110_g_MissionId);
	elseif dispatchType == x300110_DISP_CONTINUE then
		DispatchQuestContinueInfo(sceneId, selfId, NPCId, x300110_g_ScriptId, x300110_g_MissionId);
	elseif dispatchType == x300110_DISP_EVENT then
		DispatchQuestEventList(sceneId, selfId, NPCId);
	else
		DispatchQuestTips(sceneId, selfId);
	end

end

-------------------------
--***********************
--ProcAcceptCheck
--***********************
-------------------------

function x300110_ProcAcceptCheck(sceneId, selfId, NPCId)

	return 1;

end

-------------------------
--***********************
--CostFee
--***********************
-------------------------

function x300110_CostFee(sceneId, selfId)

	local money = x300110_GetEnterFee(sceneId, selfId);
	if CostMoney(sceneId, selfId, 1, money) ~= 1 then
		return 0;
	end
	
	return 1;
	
end

-------------------------
--***********************
--ProcAccept
--***********************
-------------------------

function x300110_ProcAccept(sceneId, selfId, NPCId)

	if x300110_CostFee(sceneId, selfId) <= 0 then
		BeginQuestEvent(sceneId);
			AddQuestText(sceneId, x300110_g_ErrorMessage_Money);
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
		return 0;
	end
	
--	AddQuest(sceneId, selfId, x300110_g_MissionId, x300110_g_ScriptId, 1, 0, 0);
--	local misIndex = GetQuestIndexByID(sceneId, selfId, x300110_g_MissionId);
--	SetQuestByIndex(sceneId, selfId, misIndex, x300110_MP_NOWNUM, 1);
--	SetQuestByIndex(sceneId, selfId, misIndex, x300110_MP_RIGHTNUM, 0);	
	
	local str = x300110_g_StartMessage;
		
	BeginQuestEvent(sceneId);
		AddQuestText(sceneId, str);
	EndQuestEvent();
		
	DispatchQuestTips(sceneId, selfId);
	local idx = GetQuizGameQuestionIdx(sceneId, selfId);
	QuizAsk(sceneId, selfId, idx+1, x300110_g_TotalNum, x300110_g_AnswerTime); 
	x300110_SetRound(sceneId, selfId);

end

-------------------------
--***********************
--SetRound
--***********************
-------------------------
function x300110_SetRound(sceneId, selfId)
	SetQuizCount(sceneId, selfId, GetQuizCount(sceneId, selfId)+1);
end

-------------------------
--***********************
--GetRound
--***********************
-------------------------

function x300110_GetRound(sceneId, selfId)

	return GetQuizCount(sceneId, selfId);

end

-------------------------
--***********************
--OnAnswer
--***********************
-------------------------

function x300110_OnAnswer( sceneId, selfId, nStepIndex, questIndex, answerIndex)
		local nCount;
		local nCode;
		--检查题答案
		nCode = QuizCheck(sceneId, questIndex, answerIndex);
		--得到答对或错几道题
		if (nCode == 0) then
				nCount = GetQuizWrongCount(sceneId, selfId);
				nCount = nCount + 1;
				SetQuizWrongCount( sceneId, selfId, nCount);
		elseif (nCode == 1) then
				nCount = GetQuizRightCount(sceneId, selfId);
				nCount = nCount + 1;
				SetQuizRightCount( sceneId, selfId, nCount);
				x300110_AddExp(sceneId, selfId, nCount);
		end
		--给客户端回传结果
		QuizResult(sceneId, selfId, nStepIndex, nCode, nCount);
		local nStepIndex = nStepIndex + 1;
		if nStepIndex <= x300110_g_TotalNum then
--			QuizAsk(sceneId, selfId, nStepIndex, x300110_g_TotalNum, x300110_g_AnswerTime);
		else
			BeginQuestEvent(sceneId);
				AddQuestText(sceneId, x300110_g_MissionCompleteInfo);
			EndQuestEvent();
			DispatchQuestTips(sceneId, selfId);
		end
end

-------------------------
--***********************
--AddExp
--***********************
-------------------------

function x300110_AddExp(sceneId, selfId, nCount)

	local exp = x300110_GetExp(sceneId, selfId, nCount);
	AddExp(sceneId, selfId, exp);
	
	BeginQuestEvent(sceneId);
		AddQuestText(sceneId, x300110_g_MissionBonusInfo);
	EndQuestEvent();
	DispatchQuestTips(sceneId, selfId);

end

-------------------------
--***********************
--EndMission
--***********************
-------------------------

function x300110_EndMission(sceneId, selfId)

	local misIndex = GetQuestIndexByID(sceneId, selfId, x300110_g_MissionId);
	local exp = x300110_GetExp(sceneId, selfId);
	AddExp(sceneId, selfId, exp);
	
	BeginQuestEvent(sceneId);
		AddQuestText(sceneId, format(x300110_g_MissionBonusInfo, exp));
	EndQuestEvent();
	
	DispatchQuestTips(sceneId, selfId);
	
	DelQuest(sceneId, selfId, x300110_g_MissionId);
		
end

-------------------------
--***********************
--ProcQuestAbandon
--***********************
-------------------------

--function x300110_ProcQuestAbandon(sceneId, selfId, MissionId)

--	DelQuest(sceneId, selfId, x300110_g_MissionId);

--end


-------------------------
--***********************
--ProcQuestSubmit
--***********************
-------------------------

--function x300110_ProcQuestSubmit(sceneId, selfId)

--	x300110_EndMission(sceneId, selfId);

--end

-------------------------
--***********************
--GetExp
--***********************
-------------------------

function x300110_GetExp(sceneId, selfId, nCount)

	local ret;
	ret = GetLevel(sceneId, selfId) * x300110_g_GetExpRate;
	return ret;
			
end


--**********************************

--杀死怪物或玩家

--**********************************

function x300110_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--进入区域事件

--**********************************

function x300110_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--道具改变

--**********************************

function x300110_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end