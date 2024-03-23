--***********************
--Const
--***********************
x310401_g_ScriptId 				= 310401

--常量显示文本
x310401_g_NoMoneyErrText		= 
"您的金钱不足，无法领取"
x310401_g_GetExpLevelErrText	= 
"您的等级不足#R%d级#o，无法领取该档次的离线经验"
x310401_g_OfflineLevelErrText	= 
"您的等级不足#R%d级#o，无法离线代练"
x310401_g_TimeMaxErrText		= 
"您的累积时间已到达上限，请领取离线经验后再开启离线代练"
x310401_g_TimeZeroErrText		= 
"您的离线代练累积时间为0，没有可领取的离线经验"
x310401_g_ShowDemoText			= 
"\t只有不低于#G40#W级的玩家才可以使用离线代练。\n\t开始离线代练后您的离线代练时间将累积计算到您下次上线为止，之后您可花费一定的金钱领取对应的离线经验，离线代练时间最多可累积7天。\n"
x310401_g_CurTrainTimeText		= 
"\t您当前的离线代练累积时间为#G%d天%d小时%d分#W。\n"
x310401_g_OfflineAcceptText		= 
"\t选择确认后将立即以代练状态离线，并开始累积离线代练时间，是否立即开始离线代练？"
x310401_g_GetExpText			= 
"\t请选择您要领取的离线经验档次，不同的档次需要花费不同数量的金钱。\n"..
"\t#G低档#W：普通经验效率，需要花费#G银币#W，#G%d#W级可使用\n"..
"\t#G中档#W：双倍经验效率，需要花费#G金币#W，#G%d#W级可使用\n"..
"\t#G高档#W：三倍经验效率，需要花费#G金币#W，#G%d#W级可使用"
x310401_g_GetExpAcceptText	= 
"#Y离线代练#W\n\t您当前的离线代练累积时间为#G%d天%d小时%d分#W。\n\t您选择的领取离线经验档次为#G%s#W\n\t将可以获得经验值#G%d点#W\n\t需要花费#G%s#{_MONEY%d}#W\n\t是否立即领取？"
x310401_g_GetExpTipText			= 
"获得了%d经验"

--最长保存离线代练时间 7 * 24 * 60
x310401_g_MaxTrainTime   		= 10080

--AddQuestNumText分支
x310401_g_SwitchLogout 			= 1
x310401_g_SwitchGetExp 			= 2
x310401_g_SwitchLow 			= 3
x310401_g_SwitchMiddle 			= 4
x310401_g_SwitchHigh 			= 5

--各个档次消费的钱类型 0 银子 1 金子
x310401_g_LowCostType	 		= 0
x310401_g_MiddleCostType		= 1
x310401_g_HighCostType	 		= 1

--领取不同等级经验时对应个人等级
x310401_g_LowRoleLevel	 		= 40
x310401_g_MiddleRoleLevel 		= 60
x310401_g_HighRoleLevel 		= 70

--***********************
--Variable
--***********************

--计算出所花费的金钱及获得的经验
x310401_g_curGetExpTbl = {}
x310401_g_curNeedMoneyTbl = {}
--当前所选择的接受页面 0 因重载脚本丢失；1 领取确认；2 下线确认
x310401_g_curAcceptTypeTbl = {}
--消费类型的中转变量
x310401_g_curCostTypeTbl = {}

function x310401_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
	AddQuestNumText(sceneId, x310401_g_ScriptId, "离线代练", 3, x310401_g_SwitchLogout)
 	AddQuestNumText(sceneId, x310401_g_ScriptId, "领取离线代练经验", 3, x310401_g_SwitchGetExp)
end

function x310401_ProcEventEntry(sceneId, selfId, targetId, idScript, idExt)

	--防止重刷丢失数据，不可由全局变量保存当前代练时间
	local selfTrainTime = GetQuestData(sceneId, selfId, MD_OFFLINE_TRAIN_MIN[1], MD_OFFLINE_TRAIN_MIN[2], MD_OFFLINE_TRAIN_MIN[3])

	if selfTrainTime < 0 or selfTrainTime > x310401_g_MaxTrainTime then
		WriteLog(2, format("OfflineTrain ProcEventEntry: GetQuestData Exception TimeValue(%d)", selfTrainTime))
		return
	end

	if idExt == x310401_g_SwitchLogout then
		--代练时间达到上限，无法离线代练提示
		if selfTrainTime >= x310401_g_MaxTrainTime then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, x310401_g_TimeMaxErrText)
			EndQuestEvent()
			DispatchQuestTips(sceneId, selfId)
			return
		end
   		
		--设置下线确认接受页面类型中转变量
		x310401_g_curAcceptTypeTbl[GetName(sceneId, selfId)] = 2

   		--显示最后的下线确认接受显示本文
       	BeginQuestEvent(sceneId)
       	AddQuestText(sceneId, "#Y离线代练#W\n")
 		AddQuestText(sceneId, format(x310401_g_ShowDemoText .. x310401_g_CurTrainTimeText .. x310401_g_OfflineAcceptText, selfTrainTime / 60 / 24, 
 			mod(selfTrainTime / 60, 24), mod(selfTrainTime, 60)))
   	 	EndQuestEvent()
   		DispatchQuestInfo(sceneId, selfId, targetId, x310401_g_ScriptId, -1)  
   		 		
	elseif idExt == x310401_g_SwitchGetExp then
	
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y领取离线代练经验#W\n")
		AddQuestText(sceneId, format(x310401_g_CurTrainTimeText .. x310401_g_GetExpText, selfTrainTime / 60 / 24, 
			mod(selfTrainTime / 60, 24), mod(selfTrainTime, 60), x310401_g_LowRoleLevel, x310401_g_MiddleRoleLevel, x310401_g_HighRoleLevel))
        AddQuestNumText(sceneId, x310401_g_ScriptId, "低档（40级以上）", 3, x310401_g_SwitchLow)
        AddQuestNumText(sceneId, x310401_g_ScriptId, "中档（60级以上）", 3, x310401_g_SwitchMiddle)
        AddQuestNumText(sceneId, x310401_g_ScriptId, "高档（70级以上）", 3, x310401_g_SwitchHigh)
        EndQuestEvent()
        DispatchQuestEventList(sceneId, selfId, targetId) 
         
   elseif idExt == x310401_g_SwitchLow or idExt == x310401_g_SwitchMiddle or idExt == x310401_g_SwitchHigh then	
		--无代练时间的错误提示
		if selfTrainTime == 0 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, x310401_g_TimeZeroErrText)
			EndQuestEvent()
			DispatchQuestTips(sceneId, selfId)
			return
		end

   		local selLevel = ""
   		local roleLevel = GetLevel(sceneId, selfId)
   		local errRoleLevel = 0
   		
   		--对当前选择档次进行自身级别判定
   		if idExt == x310401_g_SwitchLow then
   			if roleLevel < x310401_g_LowRoleLevel then
   				errRoleLevel = x310401_g_LowRoleLevel
   			end
   			selLevel = "低档"
   		elseif idExt == x310401_g_SwitchMiddle then
   			if roleLevel < x310401_g_MiddleRoleLevel then
   				errRoleLevel = x310401_g_MiddleRoleLevel
   			end
   			selLevel = "中档"
   		elseif idExt == x310401_g_SwitchHigh then
   			if roleLevel < x310401_g_HighRoleLevel then
   				errRoleLevel = x310401_g_HighRoleLevel
   			end
   			selLevel = "高档"
		end

		if errRoleLevel ~= 0 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, format(x310401_g_GetExpLevelErrText, errRoleLevel))
			EndQuestEvent()
			DispatchQuestTips(sceneId, selfId)
			return
		end
	
   		--消费公式，根据选择档次及自身等级的不同算出获取经验权重---------------------------------
   		local numPower = 0
   		if idExt == x310401_g_SwitchLow then
   			x310401_g_curCostTypeTbl[GetName(sceneId, selfId)] = x310401_g_LowCostType
   			x310401_g_curNeedMoneyTbl[GetName(sceneId, selfId)] = 313 * selfTrainTime
   			
   			if roleLevel >= x310401_g_HighRoleLevel then
   				numPower = 135
   			else
   				numPower = 75
   			end
   		elseif idExt == x310401_g_SwitchMiddle then
   			x310401_g_curCostTypeTbl[GetName(sceneId, selfId)] = x310401_g_MiddleCostType
   			x310401_g_curNeedMoneyTbl[GetName(sceneId, selfId)] = 9 * selfTrainTime
   			
   			if roleLevel >= x310401_g_HighRoleLevel then
   				numPower = 270
   			else
   				numPower = 150
   			end
   		elseif idExt == x310401_g_SwitchHigh then
   			x310401_g_curCostTypeTbl[GetName(sceneId, selfId)] = x310401_g_HighCostType
   			x310401_g_curNeedMoneyTbl[GetName(sceneId, selfId)] = 17 * selfTrainTime
   			
   			if roleLevel >= x310401_g_HighRoleLevel then
   				numPower = 405
   			else
   				numPower = 225
   			end
		end
   		
   		x310401_g_curGetExpTbl[GetName(sceneId, selfId)] = roleLevel * numPower * selfTrainTime
		-----------------------------------------------------------------------------------------
		
		--设置获取经验接受页面类型中转变量
		x310401_g_curAcceptTypeTbl[GetName(sceneId, selfId)] = 1
		
		-- 根据当前选择档次所对应的花费类型设置显示的货币种类文字内容
   		local curCostString = ""
		if x310401_g_curCostTypeTbl[GetName(sceneId, selfId)] == 1 then
			curCostString = "金币"
		else
			curCostString = "银币"
		end

   		--显示最后的获取经验接受显示本文
       	BeginQuestEvent(sceneId)
    	AddQuestText(sceneId, format(x310401_g_GetExpAcceptText, selfTrainTime / 60 / 24, mod(selfTrainTime / 60, 24), mod(selfTrainTime, 60), 
    		selLevel, x310401_g_curGetExpTbl[GetName(sceneId, selfId)], curCostString, x310401_g_curNeedMoneyTbl[GetName(sceneId, selfId)]))
   	 	EndQuestEvent()
   		DispatchQuestInfo(sceneId, selfId, targetId, x310401_g_ScriptId, -1)
    end
end

function x310401_ProcAcceptCheck(sceneId, selfId, targetId)

	--根据中转变量来确定是经验获取确认或下线确认页面，操作中重载脚本清除变量将不会产生影响（忽略这次接受）
	if 	x310401_g_curAcceptTypeTbl[GetName(sceneId, selfId)] == 1 then
	
		if x310401_g_curCostTypeTbl[GetName(sceneId, selfId)] ~= 0 and x310401_g_curCostTypeTbl[GetName(sceneId, selfId)] ~= 1 then
			return
		end

		--根据货币类型拿出自由与绑定的这种货币数目
		local freeMoney = GetMoney(sceneId, selfId, x310401_g_curCostTypeTbl[GetName(sceneId, selfId)] * 2)
		local bindMoney = GetMoney(sceneId, selfId, x310401_g_curCostTypeTbl[GetName(sceneId, selfId)] * 2 + 1)
	
		--对应消费金额检查
		if freeMoney + bindMoney < x310401_g_curNeedMoneyTbl[GetName(sceneId, selfId)] then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, x310401_g_NoMoneyErrText)
			EndQuestEvent()
			DispatchQuestTips(sceneId, selfId)
			return
		end
		
		local payType = 0 --0 绑定卡 1 现金
		if x310401_g_curCostTypeTbl[GetName(sceneId, selfId)] == 0 then
			payType = GetSillerMode(sceneId, selfId)
		else
			payType = GetGoldMode(sceneId, selfId)
		end
		
	    if payType == 1 then
	    	--如果现金不够则接着扣绑定卡的钱
	    	if freeMoney < x310401_g_curNeedMoneyTbl[GetName(sceneId, selfId)] then
	    		CostMoney(sceneId, selfId, x310401_g_curCostTypeTbl[GetName(sceneId, selfId)] * 2, freeMoney, 309)
	    		CostMoney(sceneId, selfId, x310401_g_curCostTypeTbl[GetName(sceneId, selfId)] * 2 + 1, x310401_g_curNeedMoneyTbl[GetName(sceneId, selfId)] - freeMoney, 309)
	    	else
	    		CostMoney(sceneId, selfId, x310401_g_curCostTypeTbl[GetName(sceneId, selfId)] * 2, x310401_g_curNeedMoneyTbl[GetName(sceneId, selfId)], 309)
	    	end
	    else
	    	--如果绑定卡不够则接着扣现金的钱
	    	if bindMoney < x310401_g_curNeedMoneyTbl[GetName(sceneId, selfId)] then
	    		CostMoney(sceneId, selfId, x310401_g_curCostTypeTbl[GetName(sceneId, selfId)] * 2 + 1, bindMoney, 309)
	    		CostMoney(sceneId, selfId, x310401_g_curCostTypeTbl[GetName(sceneId, selfId)] * 2, x310401_g_curNeedMoneyTbl[GetName(sceneId, selfId)] - bindMoney, 309)
	    	else
	    		CostMoney(sceneId, selfId, x310401_g_curCostTypeTbl[GetName(sceneId, selfId)] * 2 + 1, x310401_g_curNeedMoneyTbl[GetName(sceneId, selfId)], 309)
	    	end
	    end
		
		--加经验并清除离线代练时间
	    AddExp(sceneId, selfId, x310401_g_curGetExpTbl[GetName(sceneId, selfId)])
	    SetQuestData(sceneId, selfId, MD_OFFLINE_TRAIN_MIN[1], MD_OFFLINE_TRAIN_MIN[2], MD_OFFLINE_TRAIN_MIN[3], 0)
	    
	    --在客户端右下方显示经验获取提示
	    Msg2Player(sceneId, selfId, format(x310401_g_GetExpTipText, x310401_g_curGetExpTbl[GetName(sceneId, selfId)]), 8 ,2)
	    --写调试日志
	    WriteLog(1, format("OfflineTrain ProcAcceptCheck GetExp OK: Name(%s) GUID(%d) NeedMoney(%d) GetExp(%d)", 
	    	GetName(sceneId, selfId), GetGUID(sceneId, selfId), x310401_g_curNeedMoneyTbl[GetName(sceneId, selfId)], x310401_g_curGetExpTbl[GetName(sceneId, selfId)]))		    	
	
	elseif 	x310401_g_curAcceptTypeTbl[GetName(sceneId, selfId)] == 2 then
		
		--离线挂机对应角色等级检查
		if GetLevel(sceneId, selfId) < x310401_g_LowRoleLevel then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, format(x310401_g_OfflineLevelErrText, x310401_g_LowRoleLevel))
			EndQuestEvent()
			DispatchQuestTips(sceneId, selfId)
			return
		end

		--设置离线代练标志并提示下线
    	SetQuestData(sceneId, selfId, MD_OFFLINE_TRAIN_FLAG[1], MD_OFFLINE_TRAIN_FLAG[2], MD_OFFLINE_TRAIN_FLAG[3], 1)
   	 	KickPlayer(sceneId, selfId, 1)

    	--写调试日志
	    WriteLog(1, format("OfflineTrain ProcEventEntry Offline OK: Name(%s) GUID(%d)", GetName(sceneId, selfId), GetGUID(sceneId, selfId)))
	end
end

function x310401_ProcMapPlayerNewConnectEnter(sceneId, selfId)
	
	local lastLogoutTime = GetLastLogoutTime(sceneId, selfId)

	--自架服务无上次离线时间需要开启这行进行测试
	--lastLogoutTime = GetCurrentTime() - 4444

	if lastLogoutTime <= 0 then
		return
	end
	
	--取得自己之前的离线代练时间和标志
	local selfTrainTime = GetQuestData(sceneId, selfId, MD_OFFLINE_TRAIN_MIN[1], MD_OFFLINE_TRAIN_MIN[2], MD_OFFLINE_TRAIN_MIN[3])
	local selfTrainFlag = GetQuestData(sceneId, selfId, MD_OFFLINE_TRAIN_FLAG[1], MD_OFFLINE_TRAIN_FLAG[2], MD_OFFLINE_TRAIN_FLAG[3])

	if selfTrainTime < 0 or selfTrainTime > x310401_g_MaxTrainTime or (selfTrainFlag ~= 0 and selfTrainFlag ~= 1) then
		WriteLog(2, format("OfflineTrain ProcMapPlayerNewConnectEnter: GetQuestData Exception TimeValue(%d) FlagValue(%d)", selfTrainTime, selfTrainFlag))
		return
	end

	--对上次是离线代练标志进行离线代练时间更新
	if selfTrainFlag == 1 then
		--取得本次上线后的代练时间，单位秒
		local thisTrainTime = GetCurrentTime() - lastLogoutTime
		
		--时间容错判定，防止测试时向前修改日期导致的 thisTrainTime 为负的情况
		if thisTrainTime > 0 then
   			selfTrainTime = selfTrainTime + thisTrainTime / 60
			
		    if selfTrainTime > x310401_g_MaxTrainTime then
		    	selfTrainTime = x310401_g_MaxTrainTime
		    end
		
			--更新自己的离线代练时间
		    SetQuestData(sceneId, selfId, MD_OFFLINE_TRAIN_MIN[1], MD_OFFLINE_TRAIN_MIN[2], MD_OFFLINE_TRAIN_MIN[3], selfTrainTime)
    	else
			WriteLog(2, format("OfflineTrain ProcMapPlayerNewConnectEnter: get this traintime error for modify system time"))    		
    	end
    	
    	--清除离线代练标志
	    SetQuestData(sceneId, selfId, MD_OFFLINE_TRAIN_FLAG[1], MD_OFFLINE_TRAIN_FLAG[2], MD_OFFLINE_TRAIN_FLAG[3], 0)
	end
end
