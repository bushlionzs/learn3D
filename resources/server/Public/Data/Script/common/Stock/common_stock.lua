
x310350_g_ScriptId = 310350
x310350_g_MissionName = "����Ǯׯ"

x310350_g_STOCK_OP_ASK_REGISTER = 0				--����
x310350_g_STOCK_OP_ASK_OPEN = 1					--�����Ǯׯϵͳ
x310350_g_STOCK_OP_MONEY_TO_STOCK = 2			--��Ǯׯ�˻��ڳ�ֵ
x310350_g_STOCK_OP_MONEY_TO_CHAR = 3			--��Ǯׯ�˻��ڵ�Moneyת���ɫ
x310350_g_STOCK_OP_MONEY_TO_CHAR_FAILED = 4		--��Ǯׯ�˻��ڵ�Moneyת���ɫʱʧ��
x310350_g_STOCK_OP_ASK_WORLD_LIST = 5			--���������Ϣ
x310350_g_STOCK_OP_ASK_AUTO_SALE = 6			--����ҵ�����
x310350_g_STOCK_OP_ASK_AUTO_BUY = 7				--����ҵ�����
x310350_g_STOCK_OP_ASK_FAST_SALE = 8			--�����ֶ�����
x310350_g_STOCK_OP_ASK_FAST_BUY = 9				--�����ֶ�����
x310350_g_STOCK_OP_ASK_RECORD = 10				--������ʷ��¼
x310350_g_STOCK_OP_ASK_MARKET_LIST = 11			--�����ϼ��б�
x310350_g_STOCK_OP_ASK_REPEAL_BUY = 12			--��������
x310350_g_STOCK_OP_ASK_REPEAL_SELL = 13			--����������

--�볡��ƥ���NPC
x310350_g_SceneMatchNPC = 	{ 
								--�󶼶�Ӧ��NPC
								{ sceneId = 0, npcGuid = 139086, },
								
								--¥����Ӧ��NPC
								{ sceneId = 50, npcGuid = 123768, },
								
								--��ɽ(����)��Ӧ��NPC
								{ sceneId = 150, npcGuid = 126064, },
																
								--���ض�Ӧ��NPC
								{ sceneId = 250, npcGuid = 129067, },
																
								--�ػͶ�Ӧ��NPC
								{ sceneId = 350, npcGuid = 132064, },		
																			
								--�����˼������Ӧ��NPC
								{ sceneId = 39, npcGuid = 145058, },			
																							
								--�����˼����Ķ�Ӧ��NPC
								{ sceneId = 40, npcGuid = 145149, },																													
							}


--�����NPC��
function x310350_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

	AddQuestNumText(sceneId,x310350_g_ScriptId,x310350_g_MissionName,3,-1)
	
end



--�������ť������������ִ�д˽ű�
function x310350_ProcEventEntry( sceneId, selfId, targetId,state,index )	

	if GetMergeDBToggle() == 1 then
		local text = "Ϊ��ϲ�����Ǯׯϵͳ��ʱ�رգ�������ɺ󼴿�����ʹ��"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,text );
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId, selfId, targetId);
		return 	
	end
	
	if GetUpdateDBBeforeToggle() == 1 then
		local text = "Ϊ������ݿ�������Ǯׯϵͳ��ʱ�رգ�������ɺ󼴿�����ʹ��"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,text );
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId, selfId, targetId);
		return 	
	end

	if IsEnableStockAccount(sceneId, selfId) == 0 then
		local text = "����δ��ͨǮׯ�ʻ�,���ȿ�ͨ����Ǯׯ�ʻ���"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,text );
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId, selfId, targetId);
		return
	end
	
	--������Ϣ�����Ǯׯ����
	OpenStockSystem(sceneId, selfId)
		
end

--�ж��ܷ����Ǯׯϵͳ
function x310350_OnIsCanAccessStock( sceneId, selfId, opType,gold, siller )
		
	if IsEnableStockAccount(sceneId, selfId) == 0 then
	
		local text = "����δ��ͨǮׯ�ʻ�,���ȿ�ͨ����Ǯׯ�ʻ���"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,text );
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,text,8,2)
		return 0
		
	end
	
	if GetMergeDBToggle() == 1 then
	
		local text = "Ϊ��ϲ�����������ʱ�رգ�������ɺ󼴿�����ʹ��"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,text );
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,text,8,2)
		return 	0
		
	end
	
	if GetUpdateDBBeforeToggle() == 1 then
	
		local text = "Ϊ������ݿ�������������ʱ�رգ�������ɺ󼴿�����ʹ��"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,text );
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,text,8,2)
		return 	0
		
	end

	local isInDistance = 0	
	for i,itm in x310350_g_SceneMatchNPC do
		
		if itm.sceneId == sceneId then		
			
			local npcObjId = FindMonsterByGUID(sceneId,itm.npcGuid)		
			if IsInDist(sceneId,selfId,npcObjId,5) == 1 then
				isInDistance = 1				
			end	
			
			break
						
		end
		
	end
	
	if isInDistance ~= 1 then
	
		--������Ч����
		return 0
		
	end
			
	local nRet = 0
	
	if opType == x310350_g_STOCK_OP_MONEY_TO_STOCK then		--��ֵ
	
		nRet = CallScriptFunction(x310350_g_ScriptId, "OnIsCanTransMoneyToStock", sceneId, selfId, gold, siller);
		
	elseif opType == x310350_g_STOCK_OP_MONEY_TO_CHAR then	--��Ǯׯ�˻��ڵ�Moneyת���ɫ
	
		nRet = CallScriptFunction(x310350_g_ScriptId, "OnIsCanTransMoneyToChar", sceneId, selfId, gold, siller);	
		
	elseif opType == x310350_g_STOCK_OP_ASK_AUTO_BUY or opType == x310350_g_STOCK_OP_ASK_FAST_BUY then	
		
		--������
		nRet = CallScriptFunction(x310350_g_ScriptId, "OnIsCanBuy", sceneId, selfId, gold, siller);	
		
		
	elseif opType == x310350_g_STOCK_OP_ASK_AUTO_SALE or opType == x310350_g_STOCK_OP_ASK_FAST_SALE then	
		
		--�������
		nRet = CallScriptFunction(x310350_g_ScriptId, "OnIsCanSale", sceneId, selfId, gold, siller);	
				
	elseif opType == x310350_g_STOCK_OP_ASK_REPEAL_BUY or opType == x310350_g_STOCK_OP_ASK_REPEAL_SELL then		
	
		--�����ҵ�
		nRet = CallScriptFunction(x310350_g_ScriptId, "OnIsCanRepeal", sceneId, selfId);		
				
	elseif opType == x310350_g_STOCK_OP_ASK_WORLD_LIST then
	
		--���������Ϣ
		nRet = x310350_IsIntervalEnough(sceneId, selfId,RD_STOCK_ASK_WORLD_LIST_TIME,3) 
			
	elseif opType == x310350_g_STOCK_OP_ASK_RECORD then
	
		--������ʷ��¼
		nRet = x310350_IsIntervalEnough(sceneId, selfId,RD_STOCK_ASK_RECORD_TIME,1)		
		
	elseif opType == x310350_g_STOCK_OP_ASK_MARKET_LIST then		
		
		--�����ϼ��б�
		nRet = x310350_IsIntervalEnough(sceneId, selfId,RD_STOCK_AASK_MARKET_LIST_TIME,1)
		
	else
		
		--�Ƿ���Ϣ
		nRet = 0
		
	end
	
	return nRet
	
end

--�Ƿ񳬹���ȴʱ��
function x310350_IsIntervalEnough(sceneId, selfId,index,interval)

	local lastTime = GetPlayerRuntimeData( sceneId, selfId, index )
	if lastTime <= 0 then
		
		local currTime = GetCurrentTime()
		SetPlayerRuntimeData( sceneId, selfId, index, currTime)
		
	else
		
		local currTime = GetCurrentTime()
		if currTime - lastTime < interval then		
			return 0
		end
		
		SetPlayerRuntimeData( sceneId, selfId, index, currTime)		
		
	end
	
	return 1
	
end


--�ж��ܷ��ֵ
function x310350_OnIsCanTransMoneyToStock( sceneId, selfId, costGold, costSiller )
		
	if IsInLoginProtectTime(sceneId, selfId) == 1 then
	
		local text = "���д��ڰ�ȫ����ʱ���ڣ��޷����д˲�����"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,text );
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,text,8,2)
		return 	0
		
	end
	
	--��ȴʱ���ж�	
	if x310350_IsIntervalEnough(sceneId, selfId,RD_STOCK_TRANS_MONEY_TIME,2) == 0 then
		--��ȴ��
		return 0	
	end

	if costGold < 0 or costSiller < 0 then
		--��Ӧ�ó��ֵ����
		return 0
	end
	
	if costGold == 0 and costSiller ==0 then
		--��Ӧ�ó��ֵ����
		return 0
	end
	
	if costSiller > 0 and IsPasswordProtect(sceneId, selfId, 3, 1) == 0 then
		return 0
	end
	
	if costGold > 0 and IsPasswordProtect(sceneId, selfId, 2, 1) == 0 then
		return 0
	end		
	
	if GetMoney(sceneId, selfId,0) < costSiller then
		
		local text = "��ı�������������#{_MONEY"..costSiller.."},��ֵ���ɹ�"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,text );
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,text,8,2)
		return 0
		
	end	
	
	if GetMoney(sceneId, selfId,2) < costGold then
		
		local text = "��ı������ֽ�����#{_MONEY"..costGold.."},��ֵ���ɹ�"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,text );
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,text,8,2)
		return 0
		
	end

	return 1

end

--�ж��ܷ�ת�˵���ɫ
function x310350_OnIsCanTransMoneyToChar( sceneId, selfId, gold, siller )
	
	if IsInLoginProtectTime(sceneId, selfId) == 1 then
	
		local text = "���д��ڰ�ȫ����ʱ���ڣ��޷����д˲�����"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,text );
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,text,8,2)
		return 	0
		
	end
	
	--��ȴʱ���ж�	
	if x310350_IsIntervalEnough(sceneId, selfId,RD_STOCK_TRANS_MONEY_TIME,2) == 0 then
		--��ȴ��
		return 0	
	end
	
	if gold < 0 or siller < 0 then
		--��Ӧ�ó��ֵ����
		return 0
	end
	
	if gold == 0 and siller ==0 then
		--��Ӧ�ó��ֵ����
		return 0
	end
	
	if GetMoney(sceneId, selfId,0) + siller > 999999999 then
		
		local text = "������������"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,text );
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,text,8,2)
		return 0
		
	end	
	
	if GetMoney(sceneId, selfId,2) + gold > 999999999 then
		
		local text = "�ֽ𳬹�����"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,text );
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,text,8,2)
		return 0
		
	end

	return 1

end

--�ж��ܷ���
function x310350_OnIsCanBuy( sceneId, selfId, gold, siller )
	
	if IsInLoginProtectTime(sceneId, selfId) == 1 then
		local text = "���д��ڰ�ȫ����ʱ���ڣ��޷����д˲�����"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,text );
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,text,8,2)
		return 	0
	end
	
	--��ȴʱ���ж�	
	if x310350_IsIntervalEnough(sceneId, selfId,RD_STOCK_BUY_TIME,1) == 0 then
		--��ȴ��
		return 0	
	end
	
	if gold <= 0 or siller <= 0 then
		--��Ӧ�ó��ֵ����
		return 0
	end	
	
	if mod(gold,1000) ~= 0 or mod(siller,1000) ~= 0 then
		--�������С��λΪ��
		return 0
	end
	
	gold = gold / 1000
	siller = siller / 1000
	
	if gold > 999 or siller > 999 then
		--��Ӧ�ó��ֵ����
		return 0
	end	
	
	if siller * gold > 999999 then
		--��Ӧ�ó��ֵ����
		return 0
	end	
	
	if IsInLoginProtectTime(sceneId, selfId) == 1 then
		local text = "���д��ڰ�ȫ����ʱ���ڣ��޷����д˲�����"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,text );
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,text,8,2)
		return 	0
	end
	
	if siller > 0 and IsPasswordProtect(sceneId, selfId, 3, 1) == 0 then
		return 0
	end
	
	if gold > 0 and IsPasswordProtect(sceneId, selfId, 2, 1) == 0 then
		return 0
	end	
	
	return 1
	
end

--�ж��ܷ����
function x310350_OnIsCanSale( sceneId, selfId, gold, siller )
		
	if IsInLoginProtectTime(sceneId, selfId) == 1 then
		local text = "���д��ڰ�ȫ����ʱ���ڣ��޷����д˲�����"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,text );
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,text,8,2)
		return 	0
	end
	
	--��ȴʱ���ж�	
	if x310350_IsIntervalEnough(sceneId, selfId,RD_STOCK_SALE_TIME,1) == 0 then
		--��ȴ��
		return 0	
	end
	
	if IsEnableStockAccount(sceneId, selfId) == 0 then
		local text = "���ȿ�ͨ����Ǯׯ�ʻ���"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,text );
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,text,8,2)
		return 0
	end
	
	if GetMergeDBToggle() == 1 then
		local text = "Ϊ��ϲ�����������ʱ�رգ�������ɺ󼴿�����ʹ��"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,text );
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,text,8,2)
		return 	0
	end
	
	if GetUpdateDBBeforeToggle() == 1 then
	
		local text = "Ϊ������ݿ�������������ʱ�رգ�������ɺ󼴿�����ʹ��"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,text );
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,text,8,2)
		return 	0
		
	end
	
	if gold <= 0 or siller <= 0 then
		--��Ӧ�ó��ֵ����
		return 0
	end	
	
	if mod(gold,1000) ~= 0 or mod(siller,1000) ~= 0 then
		--�������С��λΪ��
		return 0
	end
	
	gold = gold / 1000
	siller = siller / 1000
	
	if gold > 999 or siller > 999 then
		--��Ӧ�ó��ֵ����
		return 0
	end	
	
	if siller * gold > 999999 then
		--��Ӧ�ó��ֵ����
		return 0
	end	
	
	if IsInLoginProtectTime(sceneId, selfId) == 1 then
		local text = "���д��ڰ�ȫ����ʱ���ڣ��޷����д˲�����"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,text );
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,text,8,2)
		return 	0
	end
	
	if siller > 0 and IsPasswordProtect(sceneId, selfId, 3, 1) == 0 then
		return 0
	end
	
	if gold > 0 and IsPasswordProtect(sceneId, selfId, 2, 1) == 0 then
		return 0
	end	
	
	return 1
	
end

--�ж��ܷ����ҵ�
function x310350_OnIsCanRepeal( sceneId, selfId )
		
	if IsInLoginProtectTime(sceneId, selfId) == 1 then
		local text = "���д��ڰ�ȫ����ʱ���ڣ��޷����д˲�����"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,text );
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,text,8,2)
		return 	0
	end
	
	--��ȴʱ���ж�	
	if x310350_IsIntervalEnough(sceneId, selfId,RD_STOCK_REPEAL_TIME,2) == 0 then
		--��ȴ��
		return 0	
	end
	
	return 1
	
end

--��ֵ���
function x310350_OnTransMoneyToStockResult( sceneId, selfId, transGold, transSiller,stockGold,stockSiller,result )
	
	if result == 0 then
		local text = "Ǯׯ�ʻ���ֵʧ��"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,text );
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,text,8,2)
		return 	0
	else
		local text = "Ǯׯ�ʻ���ֵ�ɹ����˻����Ϊ���ֽ�#{_MONEY"..stockGold.."����#{_MONEY"..stockSiller
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,text );
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,text,8,2)
		return 	0	
	end
end

--���������
function x310350_OnAskAutoSaleResult( sceneId, selfId, transGold, transSiller,result )

	if result == 0 and transGold >= 10000 then
		--�����ɹ�
		local text = "ĳ����Ǯׯ��ί������#{_MONEY"..transGold.."}��ÿ�����Ӽ۸�Ϊ#{_MONEY"..transSiller.."}���ӣ��ѳɹ��ҵ���"
		LuaAllScenceM2Wrold(sceneId,text,2,1)
	end

end

--���򵥽��
function x310350_OnAskAutoBuyResult( sceneId, selfId, transGold, transSiller,result )
	
	if result == 0 and transGold >= 10000 then
		--�����ɹ�
		local text = "ĳ����Ǯׯ��ί�����#{_MONEY"..transGold.."}��ÿ�����Ӽ۸�Ϊ#{_MONEY"..transSiller.."}���ӣ��ѳɹ��ҵ���"
		LuaAllScenceM2Wrold(sceneId,text,2,1)		
	end
	
end


--�����ȷ����
function x310350_ProcAcceptCheck( sceneId, selfId, NPCId )
	
	return 1

end


--**********************************
--����
--**********************************
function x310350_ProcAccept( sceneId, selfId )

end
