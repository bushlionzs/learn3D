
x310350_g_ScriptId = 310350
x310350_g_MissionName = "进入钱庄"

x310350_g_STOCK_OP_ASK_REGISTER = 0				--开户
x310350_g_STOCK_OP_ASK_OPEN = 1					--请求打开钱庄系统
x310350_g_STOCK_OP_MONEY_TO_STOCK = 2			--向钱庄账户内充值
x310350_g_STOCK_OP_MONEY_TO_CHAR = 3			--将钱庄账户内的Money转入角色
x310350_g_STOCK_OP_MONEY_TO_CHAR_FAILED = 4		--将钱庄账户内的Money转入角色时失败
x310350_g_STOCK_OP_ASK_WORLD_LIST = 5			--请求大盘信息
x310350_g_STOCK_OP_ASK_AUTO_SALE = 6			--请求挂单出售
x310350_g_STOCK_OP_ASK_AUTO_BUY = 7				--请求挂单购买
x310350_g_STOCK_OP_ASK_FAST_SALE = 8			--请求手动出售
x310350_g_STOCK_OP_ASK_FAST_BUY = 9				--请求手动购买
x310350_g_STOCK_OP_ASK_RECORD = 10				--请求历史记录
x310350_g_STOCK_OP_ASK_MARKET_LIST = 11			--请求上架列表
x310350_g_STOCK_OP_ASK_REPEAL_BUY = 12			--请求撤消买单
x310350_g_STOCK_OP_ASK_REPEAL_SELL = 13			--请求撤消卖单

--与场景匹配的NPC
x310350_g_SceneMatchNPC = 	{ 
								--大都对应的NPC
								{ sceneId = 0, npcGuid = 139086, },
								
								--楼兰对应的NPC
								{ sceneId = 50, npcGuid = 123768, },
								
								--天山(莱茵)对应的NPC
								{ sceneId = 150, npcGuid = 126064, },
																
								--昆仑对应的NPC
								{ sceneId = 250, npcGuid = 129067, },
																
								--敦煌对应的NPC
								{ sceneId = 350, npcGuid = 132064, },		
																			
								--天上人间麒麟对应的NPC
								{ sceneId = 39, npcGuid = 145058, },			
																							
								--天上人间梦聊对应的NPC
								{ sceneId = 40, npcGuid = 145149, },																													
							}


--点击（NPC）
function x310350_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

	AddQuestNumText(sceneId,x310350_g_ScriptId,x310350_g_MissionName,3,-1)
	
end



--点击（按钮）点击该任务后执行此脚本
function x310350_ProcEventEntry( sceneId, selfId, targetId,state,index )	

	if GetMergeDBToggle() == 1 then
		local text = "为配合并服，钱庄系统暂时关闭，并服完成后即可正常使用"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,text );
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId, selfId, targetId);
		return 	
	end
	
	if GetUpdateDBBeforeToggle() == 1 then
		local text = "为配合数据库升级，钱庄系统暂时关闭，升级完成后即可正常使用"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,text );
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId, selfId, targetId);
		return 	
	end

	if IsEnableStockAccount(sceneId, selfId) == 0 then
		local text = "您还未开通钱庄帐户,请先开通您的钱庄帐户！"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,text );
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId, selfId, targetId);
		return
	end
	
	--发送消息请求打开钱庄界面
	OpenStockSystem(sceneId, selfId)
		
end

--判断能否访问钱庄系统
function x310350_OnIsCanAccessStock( sceneId, selfId, opType,gold, siller )
		
	if IsEnableStockAccount(sceneId, selfId) == 0 then
	
		local text = "您还未开通钱庄帐户,请先开通您的钱庄帐户！"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,text );
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,text,8,2)
		return 0
		
	end
	
	if GetMergeDBToggle() == 1 then
	
		local text = "为配合并服，功能暂时关闭，并服完成后即可正常使用"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,text );
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,text,8,2)
		return 	0
		
	end
	
	if GetUpdateDBBeforeToggle() == 1 then
	
		local text = "为配合数据库升级，功能暂时关闭，升级完成后即可正常使用"
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
	
		--超出有效距离
		return 0
		
	end
			
	local nRet = 0
	
	if opType == x310350_g_STOCK_OP_MONEY_TO_STOCK then		--充值
	
		nRet = CallScriptFunction(x310350_g_ScriptId, "OnIsCanTransMoneyToStock", sceneId, selfId, gold, siller);
		
	elseif opType == x310350_g_STOCK_OP_MONEY_TO_CHAR then	--将钱庄账户内的Money转入角色
	
		nRet = CallScriptFunction(x310350_g_ScriptId, "OnIsCanTransMoneyToChar", sceneId, selfId, gold, siller);	
		
	elseif opType == x310350_g_STOCK_OP_ASK_AUTO_BUY or opType == x310350_g_STOCK_OP_ASK_FAST_BUY then	
		
		--请求购买
		nRet = CallScriptFunction(x310350_g_ScriptId, "OnIsCanBuy", sceneId, selfId, gold, siller);	
		
		
	elseif opType == x310350_g_STOCK_OP_ASK_AUTO_SALE or opType == x310350_g_STOCK_OP_ASK_FAST_SALE then	
		
		--请求出售
		nRet = CallScriptFunction(x310350_g_ScriptId, "OnIsCanSale", sceneId, selfId, gold, siller);	
				
	elseif opType == x310350_g_STOCK_OP_ASK_REPEAL_BUY or opType == x310350_g_STOCK_OP_ASK_REPEAL_SELL then		
	
		--撤消挂单
		nRet = CallScriptFunction(x310350_g_ScriptId, "OnIsCanRepeal", sceneId, selfId);		
				
	elseif opType == x310350_g_STOCK_OP_ASK_WORLD_LIST then
	
		--请求大盘信息
		nRet = x310350_IsIntervalEnough(sceneId, selfId,RD_STOCK_ASK_WORLD_LIST_TIME,3) 
			
	elseif opType == x310350_g_STOCK_OP_ASK_RECORD then
	
		--请求历史记录
		nRet = x310350_IsIntervalEnough(sceneId, selfId,RD_STOCK_ASK_RECORD_TIME,1)		
		
	elseif opType == x310350_g_STOCK_OP_ASK_MARKET_LIST then		
		
		--请求上架列表
		nRet = x310350_IsIntervalEnough(sceneId, selfId,RD_STOCK_AASK_MARKET_LIST_TIME,1)
		
	else
		
		--非法消息
		nRet = 0
		
	end
	
	return nRet
	
end

--是否超过冷却时间
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


--判断能否充值
function x310350_OnIsCanTransMoneyToStock( sceneId, selfId, costGold, costSiller )
		
	if IsInLoginProtectTime(sceneId, selfId) == 1 then
	
		local text = "你尚处于安全保护时间内，无法进行此操作！"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,text );
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,text,8,2)
		return 	0
		
	end
	
	--冷却时间判断	
	if x310350_IsIntervalEnough(sceneId, selfId,RD_STOCK_TRANS_MONEY_TIME,2) == 0 then
		--冷却中
		return 0	
	end

	if costGold < 0 or costSiller < 0 then
		--不应该出现的情况
		return 0
	end
	
	if costGold == 0 and costSiller ==0 then
		--不应该出现的情况
		return 0
	end
	
	if costSiller > 0 and IsPasswordProtect(sceneId, selfId, 3, 1) == 0 then
		return 0
	end
	
	if costGold > 0 and IsPasswordProtect(sceneId, selfId, 2, 1) == 0 then
		return 0
	end		
	
	if GetMoney(sceneId, selfId,0) < costSiller then
		
		local text = "你的背包内现银余额不足#{_MONEY"..costSiller.."},充值不成功"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,text );
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,text,8,2)
		return 0
		
	end	
	
	if GetMoney(sceneId, selfId,2) < costGold then
		
		local text = "你的背包内现金余额不足#{_MONEY"..costGold.."},充值不成功"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,text );
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,text,8,2)
		return 0
		
	end

	return 1

end

--判断能否转账到角色
function x310350_OnIsCanTransMoneyToChar( sceneId, selfId, gold, siller )
	
	if IsInLoginProtectTime(sceneId, selfId) == 1 then
	
		local text = "你尚处于安全保护时间内，无法进行此操作！"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,text );
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,text,8,2)
		return 	0
		
	end
	
	--冷却时间判断	
	if x310350_IsIntervalEnough(sceneId, selfId,RD_STOCK_TRANS_MONEY_TIME,2) == 0 then
		--冷却中
		return 0	
	end
	
	if gold < 0 or siller < 0 then
		--不应该出现的情况
		return 0
	end
	
	if gold == 0 and siller ==0 then
		--不应该出现的情况
		return 0
	end
	
	if GetMoney(sceneId, selfId,0) + siller > 999999999 then
		
		local text = "现银超过上限"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,text );
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,text,8,2)
		return 0
		
	end	
	
	if GetMoney(sceneId, selfId,2) + gold > 999999999 then
		
		local text = "现金超过上限"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,text );
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,text,8,2)
		return 0
		
	end

	return 1

end

--判断能否购买
function x310350_OnIsCanBuy( sceneId, selfId, gold, siller )
	
	if IsInLoginProtectTime(sceneId, selfId) == 1 then
		local text = "你尚处于安全保护时间内，无法进行此操作！"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,text );
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,text,8,2)
		return 	0
	end
	
	--冷却时间判断	
	if x310350_IsIntervalEnough(sceneId, selfId,RD_STOCK_BUY_TIME,1) == 0 then
		--冷却中
		return 0	
	end
	
	if gold <= 0 or siller <= 0 then
		--不应该出现的情况
		return 0
	end	
	
	if mod(gold,1000) ~= 0 or mod(siller,1000) ~= 0 then
		--购买的最小单位为两
		return 0
	end
	
	gold = gold / 1000
	siller = siller / 1000
	
	if gold > 999 or siller > 999 then
		--不应该出现的情况
		return 0
	end	
	
	if siller * gold > 999999 then
		--不应该出现的情况
		return 0
	end	
	
	if IsInLoginProtectTime(sceneId, selfId) == 1 then
		local text = "你尚处于安全保护时间内，无法进行此操作！"
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

--判断能否出售
function x310350_OnIsCanSale( sceneId, selfId, gold, siller )
		
	if IsInLoginProtectTime(sceneId, selfId) == 1 then
		local text = "你尚处于安全保护时间内，无法进行此操作！"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,text );
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,text,8,2)
		return 	0
	end
	
	--冷却时间判断	
	if x310350_IsIntervalEnough(sceneId, selfId,RD_STOCK_SALE_TIME,1) == 0 then
		--冷却中
		return 0	
	end
	
	if IsEnableStockAccount(sceneId, selfId) == 0 then
		local text = "请先开通您的钱庄帐户！"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,text );
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,text,8,2)
		return 0
	end
	
	if GetMergeDBToggle() == 1 then
		local text = "为配合并服，功能暂时关闭，并服完成后即可正常使用"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,text );
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,text,8,2)
		return 	0
	end
	
	if GetUpdateDBBeforeToggle() == 1 then
	
		local text = "为配合数据库升级，功能暂时关闭，升级完成后即可正常使用"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,text );
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,text,8,2)
		return 	0
		
	end
	
	if gold <= 0 or siller <= 0 then
		--不应该出现的情况
		return 0
	end	
	
	if mod(gold,1000) ~= 0 or mod(siller,1000) ~= 0 then
		--购买的最小单位为两
		return 0
	end
	
	gold = gold / 1000
	siller = siller / 1000
	
	if gold > 999 or siller > 999 then
		--不应该出现的情况
		return 0
	end	
	
	if siller * gold > 999999 then
		--不应该出现的情况
		return 0
	end	
	
	if IsInLoginProtectTime(sceneId, selfId) == 1 then
		local text = "你尚处于安全保护时间内，无法进行此操作！"
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

--判断能否撤消挂单
function x310350_OnIsCanRepeal( sceneId, selfId )
		
	if IsInLoginProtectTime(sceneId, selfId) == 1 then
		local text = "你尚处于安全保护时间内，无法进行此操作！"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,text );
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,text,8,2)
		return 	0
	end
	
	--冷却时间判断	
	if x310350_IsIntervalEnough(sceneId, selfId,RD_STOCK_REPEAL_TIME,2) == 0 then
		--冷却中
		return 0	
	end
	
	return 1
	
end

--充值结果
function x310350_OnTransMoneyToStockResult( sceneId, selfId, transGold, transSiller,stockGold,stockSiller,result )
	
	if result == 0 then
		local text = "钱庄帐户充值失败"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,text );
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,text,8,2)
		return 	0
	else
		local text = "钱庄帐户充值成功，账户余额为：现金#{_MONEY"..stockGold.."现银#{_MONEY"..stockSiller
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,text );
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,text,8,2)
		return 	0	
	end
end

--挂卖单结果
function x310350_OnAskAutoSaleResult( sceneId, selfId, transGold, transSiller,result )

	if result == 0 and transGold >= 10000 then
		--操作成功
		local text = "某人在钱庄处委托卖金#{_MONEY"..transGold.."}，每两金子价格为#{_MONEY"..transSiller.."}银子，已成功挂单。"
		LuaAllScenceM2Wrold(sceneId,text,2,1)
	end

end

--挂买单结果
function x310350_OnAskAutoBuyResult( sceneId, selfId, transGold, transSiller,result )
	
	if result == 0 and transGold >= 10000 then
		--操作成功
		local text = "某人在钱庄处委托买金#{_MONEY"..transGold.."}，每两金子价格为#{_MONEY"..transSiller.."}银子，已成功挂单。"
		LuaAllScenceM2Wrold(sceneId,text,2,1)		
	end
	
end


--点击（确定）
function x310350_ProcAcceptCheck( sceneId, selfId, NPCId )
	
	return 1

end


--**********************************
--接受
--**********************************
function x310350_ProcAccept( sceneId, selfId )

end
