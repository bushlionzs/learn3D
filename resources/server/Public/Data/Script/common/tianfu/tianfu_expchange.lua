
x570043_g_ScriptId 					= 570043
x570043_g_ExpRate 					= 10000
x570043_g_MoneyRate 					= 10000
x570043_g_MissionName				= "天赋修炼"

function x570043_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
	AddQuestNumText(sceneId, x570043_g_ScriptId, x570043_g_MissionName,3,0);
end

function x570043_NeedExpAndMoney(sceneId, selfId)
	local nLevel = GetLevel(sceneId, selfId)
	local nExp = GetExp(sceneId, selfId)
	--local nInherenceExp = GetInherenceExp(sceneId, selfId)
	local nInherenceExp = 0
	local nInherenceLevel = GetInherenceLevel(sceneId, selfId)
	local nInherenceLevelUpNeedExp = GetInherenceLevelUpNeedExp(sceneId, selfId)
	local nNeedMoney = GetInherenceLevelUpNeedMoney(sceneId, selfId)
	local nNeedInherenceExp = nInherenceLevelUpNeedExp - nInherenceExp

	if nNeedInherenceExp <= 0 then
		return 0, 0, 0
	end
	
	local nA = nLevel - 69 - nInherenceLevel / 4
	if nA <= 0 then
		return 0, 0, 0
	else nA = 1
	end
	
	--nA = nA / 10
	
	local nM = x570043_g_ExpRate / nA
	local nNeedExp = floor(nNeedInherenceExp * nM)
	
	nNeedMoney = floor(nNeedMoney)
	if nNeedMoney < 0 then
		nNeedMoney = 0
	end
	
	if nNeedExp > 0 and nNeedMoney > 0 then
		return nNeedExp, nNeedMoney, nNeedInherenceExp
	end
	
	return 0, 0, 0
end

function x570043_ProcEventEntry(sceneId, selfId, targetId)
	SetPlayerRuntimeData(sceneId,selfId,RD_COMMON_NPCID,targetId)
	local exp , money, addInherenceExp = x570043_NeedExpAndMoney(sceneId, selfId)
	local nInherenceLevel = GetInherenceLevel(sceneId, selfId)
	if 0 == exp and 0 == money then
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, "#Y【天赋修炼】\n\t#W天赋等级增加，可以提升玩家自身控制技能的命中率，降低对方玩家控制技能的命中率，每级造成的影响为0.5%。70级以上的玩家才可以开始修炼天赋！多多修炼提升天赋等级，您才能拥有万夫不当之勇！\n\t您当前的天赋等级为#R"..nInherenceLevel.."#W级。\n\t#R以您目前的等级，已经无法再提升天赋等级了！请您提升自身等级后，再来升级天赋！");
		EndQuestEvent();
		DispatchQuestEventList(sceneId, selfId, targetId);
		return
	end
	
	local nitem = GetInherenceLevelUpNeedItem(sceneId, selfId)
	local str = ""
	if nitem > 0 then
		str = format("#Y【天赋修炼】\n\t#W天赋等级增加，可以提升玩家自身控制技能的命中率，降低对方玩家控制技能的命中率，每级造成的影响为0.5%%。60级以上的玩家才可以开始修炼天赋！多多修炼提升天赋等级，您才能拥有万夫不当之勇！\n\t您目前的天赋等级为#R%d#W级,每次修炼可提升1级天赋等级。\n \n\t升级需要消耗#R%s#W点经验。\n\t需要消耗#R#{_MONEY%d}#W银子。\n\t需要消耗物品@item_%d. \n \n\t是否确定要升级天赋？",nInherenceLevel, exp, money, nitem)
	else
		str = format("#Y【天赋修炼】\n\t#W天赋等级增加，可以提升玩家自身控制技能的命中率，降低对方玩家控制技能的命中率，每级造成的影响为0.5%%。60级以上的玩家才可以开始修炼天赋！多多修炼提升天赋等级，您才能拥有万夫不当之勇！\n\t您目前的天赋等级为#R%d#W级,每次修炼可提升1级天赋等级。\n \n\t升级需要消耗#R%s#W点经验。\n\t需要消耗#R#{_MONEY%d}#W银子。\n \n\t是否确定要升级天赋？",nInherenceLevel, exp, money)
	end
	BeginQuestEvent(sceneId)
	AddQuestText(sceneId, str)
	EndQuestEvent()
	DispatchQuestInfo(sceneId, selfId, targetId, x570043_g_ScriptId,-1);
	
end

function x570043_ProcAcceptCheck(sceneId, selfId, targetId)

	return 1;

end

function x570043_ProcAccept(sceneId, selfId, targetId)

	local nNeedExp , nNeedMoney, addInherenceExp = x570043_NeedExpAndMoney(sceneId, selfId)
	local nExp = GetExp(sceneId, selfId)
	local str = nil
	local nMoney = GetMoney(sceneId, selfId, 0) + GetMoney(sceneId, selfId, 1)
	if nExp < nNeedExp then
		str = "您的经验不足！"
	elseif nMoney < nNeedMoney then
		str = "您的银子不足！"
	end
	
	if str ~= nil then
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, str);
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
		Msg2Player(sceneId,selfId,str,8,2)
		return
	end

	local nitem = GetInherenceLevelUpNeedItem(sceneId, selfId)
	if nitem > 0 then
		local nItemCount = GetItemCountInBag( sceneId, selfId, nitem)
		if nItemCount < 1 then
			str = format("没有足够的@item_%d",nitem)
			BeginQuestEvent(sceneId);
			AddQuestText(sceneId, str);
			EndQuestEvent();
			DispatchQuestTips(sceneId, selfId);
			Msg2Player(sceneId,selfId,str,8,2)
			return
		end
	end
	
	local nSiller = GetMoney(sceneId, selfId, 0)
	local nBindSiller = GetMoney(sceneId, selfId, 1)
	local nCostSiller = 0
	local nCostBindSiller = 0
	
	local SillerMode = GetSillerMode(sceneId, selfId)
	if 1 == SillerMode then --现银
		if nSiller < nNeedMoney then
			nCostSiller = nSiller
			nCostBindSiller = nNeedMoney - nCostSiller
		else
			nCostSiller = nNeedMoney
		end
	else --银卡
		if nBindSiller < nNeedMoney then
			nCostBindSiller = nBindSiller
			nCostSiller = nNeedMoney - nBindSiller
		else
			nCostBindSiller = nNeedMoney
		end
	end
	
	DecreaseExp(sceneId, selfId, nNeedExp)
	GamePlayScriptLog(sceneId, selfId, 1561)
	CostMoney(sceneId, selfId, 1, nCostBindSiller)
	CostMoney(sceneId, selfId, 0, nCostSiller)
	GamePlayScriptLog(sceneId, selfId, 1571)
	
	if nitem > 0 then
		local Ret = DelItemByIDInBag(sceneId,selfId,nitem,1)
		if Ret <= 0 then
			BeginQuestEvent(sceneId)
				AddQuestText(sceneId,format("#cffcf0删除@item_%d失败",nitem))
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)					
			return
		end
	end

	AddInherenceExp(sceneId, selfId, addInherenceExp)
	GamePlayScriptLog(sceneId, selfId, 1581)
	local nInherenceLevel = GetInherenceLevel(sceneId, selfId)
	local msg = "恭喜你！天赋升级成功！当前天赋等级为#G"..nInherenceLevel.."#Y级！"
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, msg);
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
		Msg2Player(sceneId,selfId,msg,8,2)
	
	local targetId = GetPlayerRuntimeData(sceneId,selfId,RD_COMMON_NPCID)
	local targetGUID = GetMonsterGUID(sceneId, targetId)
	BeginQuestEvent(sceneId)
	local npcType = GetMonsterDataID(sceneId,targetId)

		local strText = "&&"..targetGUID.."&&"

		AddQuestText(sceneId,strText);
		OnNPCClickedQuestNM(sceneId,selfId,targetId, targetGUID)
		ShowNpcQuestEventList(sceneId,selfId,targetId)
	EndQuestEvent(mapId)
	DispatchQuestEventList(sceneId,selfId,targetId)
end