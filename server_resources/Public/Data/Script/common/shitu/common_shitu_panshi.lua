-------------------------
--***********************
--Const
--***********************
-------------------------

x800012_g_ScriptId 					= 800012
x800012_g_MissionName				= "【师徒】离开师门"
x800012_g_CostMoneyPanShi		= 5000
x800012_g_CostMoneyType			=	2
-------------------------
--***********************
--ProcEnumEvent
--***********************
-------------------------

function x800012_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
	AddQuestNumText(sceneId, x800012_g_ScriptId, x800012_g_MissionName,3,0);
end

-------------------------
--***********************
--ProcEventEntry
--***********************
-------------------------

function x800012_ProcEventEntry(sceneId, selfId, targetId)
	local Readme_1 = "#Y【师徒】离开师门#r"
	local Readme_2 = "\t#W我可以帮您解除与师傅的关系。#r您是否要与师傅解除师徒关系？"
	local Readme = Readme_1..Readme_2
	BeginQuestEvent(sceneId);AddQuestText(sceneId, Readme);EndQuestEvent();DispatchQuestInfo(sceneId, selfId, targetId, x800012_g_ScriptId,-1);
	
end

-------------------------
--***********************
--ProcAcceptCheck
--***********************
-------------------------

function x800012_ProcAcceptCheck(sceneId, selfId, targetId)

	return 1;

end

-------------------------
--***********************
--ProcAccept
--***********************
-------------------------

function x800012_ProcAccept(sceneId, selfId)

	
	if IsHaveMaster(sceneId, selfId) ~= 1 then
		Msg2Player(sceneId,selfId,"很抱歉，您不是徒弟，无法解除师徒。",8,2)
		Msg2Player(sceneId,selfId,"很抱歉，您不是徒弟，无法解除师徒。",8,3)
		return
	end
	
	--发普通邮件给师傅
	--得到师父GUID
	local targetGUID = GetMasterGUID(sceneId, selfId);
	if targetGUID == -1 then
		return
	end
	local MasterName = GetFriendName( sceneId, selfId, targetGUID )
	
	local mail = format("很遗憾，您的徒弟%s与您解除了师徒关系。", GetName(sceneId, selfId));
	SendSystemMail(sceneId, MasterName, mail);
	
	--发可执行邮件给师傅
	local MyGUID = GetGUID( sceneId, selfId )
	SendScriptMail( sceneId, MasterName, MAIL_BETRAYMASTER, MyGUID, 1, 0, selfId )
		--叛师
	BetrayMaster(sceneId, selfId);
	--给徒弟的提示信息
	local Msg = format("很遗憾，您解除了与师傅%s的师徒关系", MasterName);
	Msg2Player(sceneId,selfId,Msg,8,2)
	Msg2Player(sceneId,selfId,Msg,8,3)
end