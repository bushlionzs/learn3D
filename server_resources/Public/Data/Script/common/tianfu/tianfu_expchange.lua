
x570043_g_ScriptId 					= 570043
x570043_g_ExpRate 					= 10000
x570043_g_MoneyRate 					= 10000
x570043_g_MissionName				= "�츳����"

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
		AddQuestText(sceneId, "#Y���츳������\n\t#W�츳�ȼ����ӣ������������������Ƽ��ܵ������ʣ����ͶԷ���ҿ��Ƽ��ܵ������ʣ�ÿ����ɵ�Ӱ��Ϊ0.5%��70�����ϵ���Ҳſ��Կ�ʼ�����츳��������������츳�ȼ���������ӵ����򲻵�֮�£�\n\t����ǰ���츳�ȼ�Ϊ#R"..nInherenceLevel.."#W����\n\t#R����Ŀǰ�ĵȼ����Ѿ��޷��������츳�ȼ��ˣ�������������ȼ������������츳��");
		EndQuestEvent();
		DispatchQuestEventList(sceneId, selfId, targetId);
		return
	end
	
	local nitem = GetInherenceLevelUpNeedItem(sceneId, selfId)
	local str = ""
	if nitem > 0 then
		str = format("#Y���츳������\n\t#W�츳�ȼ����ӣ������������������Ƽ��ܵ������ʣ����ͶԷ���ҿ��Ƽ��ܵ������ʣ�ÿ����ɵ�Ӱ��Ϊ0.5%%��60�����ϵ���Ҳſ��Կ�ʼ�����츳��������������츳�ȼ���������ӵ����򲻵�֮�£�\n\t��Ŀǰ���츳�ȼ�Ϊ#R%d#W��,ÿ������������1���츳�ȼ���\n \n\t������Ҫ����#R%s#W�㾭�顣\n\t��Ҫ����#R#{_MONEY%d}#W���ӡ�\n\t��Ҫ������Ʒ@item_%d. \n \n\t�Ƿ�ȷ��Ҫ�����츳��",nInherenceLevel, exp, money, nitem)
	else
		str = format("#Y���츳������\n\t#W�츳�ȼ����ӣ������������������Ƽ��ܵ������ʣ����ͶԷ���ҿ��Ƽ��ܵ������ʣ�ÿ����ɵ�Ӱ��Ϊ0.5%%��60�����ϵ���Ҳſ��Կ�ʼ�����츳��������������츳�ȼ���������ӵ����򲻵�֮�£�\n\t��Ŀǰ���츳�ȼ�Ϊ#R%d#W��,ÿ������������1���츳�ȼ���\n \n\t������Ҫ����#R%s#W�㾭�顣\n\t��Ҫ����#R#{_MONEY%d}#W���ӡ�\n \n\t�Ƿ�ȷ��Ҫ�����츳��",nInherenceLevel, exp, money)
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
		str = "���ľ��鲻�㣡"
	elseif nMoney < nNeedMoney then
		str = "�������Ӳ��㣡"
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
			str = format("û���㹻��@item_%d",nitem)
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
	if 1 == SillerMode then --����
		if nSiller < nNeedMoney then
			nCostSiller = nSiller
			nCostBindSiller = nNeedMoney - nCostSiller
		else
			nCostSiller = nNeedMoney
		end
	else --����
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
				AddQuestText(sceneId,format("#cffcf0ɾ��@item_%dʧ��",nitem))
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)					
			return
		end
	end

	AddInherenceExp(sceneId, selfId, addInherenceExp)
	GamePlayScriptLog(sceneId, selfId, 1581)
	local nInherenceLevel = GetInherenceLevel(sceneId, selfId)
	local msg = "��ϲ�㣡�츳�����ɹ�����ǰ�츳�ȼ�Ϊ#G"..nInherenceLevel.."#Y����"
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