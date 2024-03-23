
x800008_g_ScriptId 					= 800008
x800008_g_MissionName				= "【婚姻】我要离婚"
x800008_g_CostMoneyDivorce  = 50000
x800008_g_CostMoneyType  		= 0
x800008_g_FriendPointNotify	= 100
x800008_g_SkillID						= 149
x800008_g_Impact						= 7642

function x800008_DoDivorce(sceneId, selfId, NPCId)

	local ret = x800008_SafeDivorceCheck(sceneId, selfId);
	if ret ~= nil then
		Msg2Player(sceneId,selfId,ret,8,2)
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, ret);
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
		return
	end
	
	if CostMoney(sceneId, selfId, x800008_g_CostMoneyType, x800008_g_CostMoneyDivorce,305) == -1 then
		return
	end
	--得到配偶GUID
	local targetGUId = GetSpouseGUID(sceneId, selfId);
	local spouseName = GetFriendName(sceneId, selfId, targetGUId)
	--发送mail给对方
	local mail = format("%s与您解除了夫妻关系。",GetName(sceneId, selfId));
	SendSystemMail(sceneId, spouseName, mail);
	
	--发可执行邮件给配偶来执行离婚
	SendScriptMail( sceneId, spouseName, MAIL_REPUDIATE, GetGUID(sceneId, selfId), 0, 0, selfId )
	
	ret = format("您解除了与%s的夫妻关系。", spouseName)
	Msg2Player(sceneId,selfId,ret,8,2)
	BeginQuestEvent(sceneId);
	AddQuestText(sceneId, ret);
	EndQuestEvent();
	DispatchQuestTips(sceneId, selfId);
		
	--最后一步,离婚
	Divorce(sceneId, selfId);
	--删除夫妻任务
	for i , missionId in SPOUSE_TASK do
		if missionId == SPOUSE_TASK[2] and 1 == IsHaveQuest(sceneId, selfId, missionId) and GetSex(sceneId, selfId) == 1 then			
			local BusID  =  GetBusId(sceneId, selfId)
			if BusID ~= -1 then
				DeleteBus(sceneId, BusID,1)
			end
		end
		if missionId == SPOUSE_TASK[3] and 1 == IsHaveQuest(sceneId, selfId, missionId) then
			DelItem(sceneId, selfId, SPOUSE_TASK_POSITION_USE_ITEM, 1)
		end
		if 1 == IsHaveQuest(sceneId, selfId, missionId) then
			DelQuestNM( sceneId, selfId, missionId )
		end
	end
	
end

-------------------------
--***********************
--SafeDivorceCheck
--***********************
-------------------------

function x800008_SafeDivorceCheck(sceneId, selfId)

	if IsMarried(sceneId, selfId) ~= 1 then
		return "你没有结婚，就想离婚么？"
	end
	
	if GetMoney(sceneId, selfId, x800008_g_CostMoneyType) < x800008_g_CostMoneyDivorce then
		return format("很抱歉，您包裹中的银子不足%d两现银，无法进行离婚。", tonumber(x800008_g_CostMoneyDivorce/1000))
	end	
	
	if IsHaveSpecificImpact(sceneId, selfId, x800008_g_Impact) == 1 then
		return "很抱歉，您正在举行婚礼中，您的离婚请求被终止。"
	end
		
	return nil
end

-------------------------
--***********************
--ProcEnumEvent
--***********************
-------------------------

function x800008_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
	AddQuestNumText(sceneId, x800008_g_ScriptId, x800008_g_MissionName,3);
end

-------------------------
--***********************
--ProcEventEntry
--***********************
-------------------------

function x800008_ProcEventEntry(sceneId, selfId, targetId)
	
	BeginQuestEvent(sceneId);
		AddQuestText(sceneId, "#Y【婚姻】我要离婚");
		AddQuestText(sceneId, "\t十年修得同船渡，百年修得共枕眠。请珍惜你们的缘分，但是如果真的无法挽回，给我#G50两现银#W我可以帮您解除婚姻关系！#r你确定要离婚吗？");
	EndQuestEvent();
	DispatchQuestInfo(sceneId, selfId, targetId, x800008_g_ScriptId,-1);
	
end

-------------------------
--***********************
--ProcAcceptCheck
--***********************
-------------------------

function x800008_ProcAcceptCheck(sceneId, selfId, targetId)

	return 1;

end

-------------------------
--***********************
--ProcAccept
--***********************
-------------------------

function x800008_ProcAccept(sceneId, selfId, targetId)

	x800008_DoDivorce(sceneId, selfId, targetId);

end