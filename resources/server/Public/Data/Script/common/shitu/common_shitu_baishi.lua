
x300361_g_ScriptId 					= 300361
x300361_g_MissionName				= "【师徒】收徒"
x300361_g_MasterLevelMin		= 50
x300361_g_PrenticeLevelMin	= 20
x300361_g_MasterPrenticeLevelConfine	= 10

function x300361_IsCanBaiShi(sceneId, selfId)

	if (IsCaptain(sceneId, selfId)) ~= 1 then
		return "只有队长才能申请收徒。";
	end
	--是否是组队 并且队伍人数是2人
	if (GetTeamSize(sceneId, selfId) ~= 2) then
		return "需要师徒二人组队来找我。";
	end
	
	--得到徒弟的objID
	local targetId = GetTeamSceneMember(sceneId, selfId, 0);
	
	if IsInDist(sceneId, selfId, targetId, 10) ~= 1 then
		return "师徒二人必须都在此附近。";
	end
	
	--师傅的等级要求
	if GetLevel(sceneId, selfId) < x300361_g_MasterLevelMin then
		return format("师傅等级必须达到%d级。", x300361_g_MasterLevelMin);
	end
	
	--徒弟的等级要求
	if GetLevel(sceneId, targetId) < x300361_g_PrenticeLevelMin then
		return format("徒弟等级达到%d级才能拜师。", x300361_g_PrenticeLevelMin);
	end
	
	--师徒等级差的要求
	if GetLevel(sceneId, selfId) - GetLevel(sceneId, targetId) < x300361_g_MasterPrenticeLevelConfine then
		return format("师傅必须比徒弟高%d级才能拜师。", x300361_g_MasterPrenticeLevelConfine);
	end

	--是否现在有师傅
	if IsHaveMaster(sceneId, targetId) == 1 then
		return "对方已经有师傅，无法拜师。";
	end
	
	--是否大于3天 得到最后一次添加徒弟的时间,得到的是时间差（秒数）
	local iTime = GetPrenticeBetrayTime(sceneId, selfId);
	iTime = iTime/3600;
	if iTime > 0 and iTime < MASTER_PRENTICE_TIME_LIMIT then
		return format("师傅%.1f小时后才能再次收徒。", MASTER_PRENTICE_TIME_LIMIT - iTime);
	end
	
	--是否大于3天 得到最后一次跟师傅解除关系的时间,得到的是时间差（秒数）
	iTime = GetMasterBetrayTime(sceneId, targetId);
	iTime = iTime/3600;	--将秒转为小时
	if iTime > 0 and iTime < MASTER_PRENTICE_TIME_LIMIT then
		return format("徒弟%.1f小时后才能再次拜师。", MASTER_PRENTICE_TIME_LIMIT - iTime);
	end
	
	--徒弟的数量
	if IsPrenticeFull(sceneId, selfId) == 1 then
		return "徒弟已经满了。";
	end

	--必须是好友
	if IsFriend(sceneId, selfId, targetId) ~= 1 or IsFriend(sceneId, targetId, selfId) ~= 1 then
		return "相互加为好友才能拜师。";
	end	

	--是否是夫妻
	if IsSpouses(sceneId, selfId, targetId) == 1 then
		return  "夫妻关系不能拜师。";
	end
	
	--对方是否是你的师傅
	if IsMaster(sceneId, selfId, targetId) == 1 then
		return "对方是你的师傅，无法拜师。";
	end

	return nil;

end

function x300361_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
	AddQuestNumText(sceneId,x300361_g_ScriptId,x300361_g_MissionName,3,0);
end

function x300361_ProcEventEntry(sceneId, selfId, targetId)

	BeginQuestEvent(sceneId);
	AddQuestText(sceneId, "#Y【师徒】收徒#W\n\t当你满足成为师傅的条件时，可以与你想收为弟子的玩家组队来到我这里（师傅必须为队长），我帮助你们结成师徒关系。\n\t建立师徒关系后，师徒双方都能够获得#G各种好处#W，不要错过哦！");
	EndQuestEvent();
	DispatchQuestInfo(sceneId, selfId, targetId, x300361_g_ScriptId,-1);
	
end

function x300361_ProcAcceptCheck(sceneId, selfId, targetId)

	return 1;

end

function x300361_ProcAccept(sceneId, selfId, targetId)

	local ret = x300361_IsCanBaiShi(sceneId, selfId);
	
	if ret ~= nil then
		Msg2Player(sceneId,selfId,ret,8,2)
		Msg2Player(sceneId,selfId,ret,8,3)
	else
		--得到徒弟的objID
		local targetId = GetTeamSceneMember(sceneId, selfId, 0);
		Aprentice(sceneId, targetId, selfId);		--拜师
		Msg2Player(sceneId, selfId, "恭喜收徒成功！师傅要努力教好你的徒儿。",8,2);
		Msg2Player(sceneId, targetId, "恭喜拜师成功！",8,2);
		Msg2Player(sceneId, selfId, "恭喜收徒成功！师傅要努力教好你的徒儿。",8,3);
		Msg2Player(sceneId, targetId, "恭喜拜师成功！",8,3);
	end

end