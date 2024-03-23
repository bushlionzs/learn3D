
x585000_g_ScriptId          		= 585000
x585000_g_BonusItem		       		= 12030424
x585000_g_CostFee								= 50000	--50两金子
x585000_g_MissionName       		= "购买冲星大礼包#R(50两现金)"
x585000_g_NoMoney								= "对不起，您的现金不足，无法购买！"
x585000_g_Readme								= "\n\t“#Y冲星大礼包#W”的销售日期是#R12月1日开始至12月7日#W结束。\n\t#R售价：50两现金#W。\n\t在购买期间内，所有用户都只能购买#R一次#W。\n\t冲星大礼包为#R绑定物品#W。使用右键点击后，将获得#G次生钻石矿2个，原生钻石矿1个和神传水晶50个#W。所获得道具均为#R绑定道具#W！"
x585000_g_DateLimit							= {
																		{y=2009,m=12,d=1},
																		{y=2009,m=12,d=2},
																		{y=2009,m=12,d=3},
																		{y=2009,m=12,d=4},
																		{y=2009,m=12,d=5},
																		{y=2009,m=12,d=6},
																		{y=2009,m=12,d=7},
																	}
x585000_g_GameId								= 2500
----------------------------------------------------------------------------------------------
--检查是否在指定日期内
----------------------------------------------------------------------------------------------																	
																																		
function x585000_CheckDateValid()
	
	local y,m,d = GetYearMonthDay()
	for i,item in x585000_g_DateLimit do
		
		if y == item.y and m == item.m and d == item.d then
			return 1
		end
		
	end
	
	return 0
	
end

----------------------------------------------------------------------------------------------
--取得今天的是第几个周
----------------------------------------------------------------------------------------------
function x585000_GetCurrentWeek()
	
	--取得今天的日期
	local nCurrentTime = (GetCurrentTime()+8*3600)/86400 - 5  --换算成天
	local nWeek = floor(nCurrentTime / 7)		 --换算成周,并取整
	
	return nWeek
end

----------------------------------------------------------------------------------------------
--取得最后一周
----------------------------------------------------------------------------------------------
function x585000_GetLastWeek( sceneId,selfId)
	return GetQuestData(sceneId,selfId,MD_CUXIAOBAO_12_WEEK[1],MD_CUXIAOBAO_12_WEEK[2],MD_CUXIAOBAO_12_WEEK[3])	
end

----------------------------------------------------------------------------------------------
--设置最后一周
----------------------------------------------------------------------------------------------
function x585000_SetLastWeek( sceneId,selfId)
	
	--当前周
	local nCurWeek = x585000_GetCurrentWeek()
	
	--检查当前周是否是最后一周
	if x585000_GetLastWeek(sceneId,selfId ) ~= nCurWeek then
		
		--如果不是最后一周,首先设置周,并且清空数据
		SetQuestData(sceneId,selfId,MD_CUXIAOBAO_12_WEEK[1],MD_CUXIAOBAO_12_WEEK[2],MD_CUXIAOBAO_12_WEEK[3],nCurWeek)
		
		--清空当前数据
		for i,item in MD_CUXIAOBAO_12_WEEK_DAY do
			SetQuestData(sceneId,selfId,item[1],item[2],item[3],0)
		end
	end	
end

----------------------------------------------------------------------------------------------
--取得最后一周里的今天的信息
----------------------------------------------------------------------------------------------
function x585000_GetLastWeek_WD(sceneId,selfId)
	
	--设置最后一周
	local nWeek = GetWeek()+1
	local item = MD_CUXIAOBAO_12_WEEK_DAY[nWeek]
	return GetQuestData(sceneId,selfId,item[1],item[2],item[3])
end

----------------------------------------------------------------------------------------------
--设置最后一周里的今天的信息
----------------------------------------------------------------------------------------------
function x585000_SetLastWeek_WD(sceneId,selfId)
	
	--设置最后一周
	local nWeek = GetWeek()+1
	local item = MD_CUXIAOBAO_12_WEEK_DAY[nWeek]
	SetQuestData(sceneId,selfId,item[1],item[2],item[3],1)
end


----------------------------------------------------------------------------------------------
--枚举
----------------------------------------------------------------------------------------------
function x585000_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

	if x585000_CheckDateValid() == 0 then
		return
	end
	
	if GetGameOpenById(1028 ) == 0 then
		return
	end

	AddQuestNumText(sceneId,x585000_g_ScriptId,x585000_g_MissionName,3,-1);
	
end
----------------------------------------------------------------------------------------------
--扣钱
----------------------------------------------------------------------------------------------
function x585000_PayMoney(sceneId,selfId,value,OP_Type)

	local nGoldMode = GetGoldMode( sceneId,selfId )
	
	if nGoldMode == 1 then		--优先现金结算
		if CostMoney(sceneId, selfId, 2, value,OP_Type) == -1 then
			return 0
		end
	
	elseif nGoldMode == 0 then	--优先金卡结算
--		if CostMoney(sceneId, selfId, 3, value,OP_Type) == -1 then
			if CostMoney(sceneId, selfId, 2, value,OP_Type) == -1 then
				return 0
--			end
		end
	else
		return 0
	end	
	
	return 1

end

----------------------------------------------------------------------------------------------
--本周是否已经给过
----------------------------------------------------------------------------------------------
function x585000_IsWeekGive( sceneId,selfId )
	
	--当前周
	local nCurWeek = x585000_GetCurrentWeek()
	
	--检查当前周是否是最后一周
	if x585000_GetLastWeek(sceneId,selfId ) == nCurWeek then
		
		--查询是否已经给过
		for i,item in MD_CUXIAOBAO_12_WEEK_DAY do
			if GetQuestData(sceneId,selfId,item[1],item[2],item[3]) == 1 then
				return 1
			end
		end
	end	
	
	--其他情况，本周没有处理过
	return 0;
	
end

----------------------------------------------------------------------------------------------
--给奖励
----------------------------------------------------------------------------------------------
function x585000_GiveBonus( sceneId,selfId )

	if x585000_CheckDateValid() == 0 then
		return
	end
	
	if GetGameOpenById( 1028 ) == 0 then
		return
	end


		BeginAddItem(sceneId)
			AddBindItem(sceneId,x585000_g_BonusItem,1)	--12030424 冲星大礼包
		local ret = EndAddItem(sceneId,selfId)
		if ret > 0 then
		
			if x585000_PayMoney(sceneId,selfId,x585000_g_CostFee,308) == 1 then		--308为supersale现金促销ID
		
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,format("恭喜您获得了礼包道具！扣除了%d两现金！",x585000_g_CostFee/1000))
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				AddItemListToPlayer(sceneId,selfId)
				GamePlayScriptLog( sceneId, selfId, x585000_g_GameId)
				return 1			
			else
				BeginQuestEvent(sceneId,selfId)
					AddQuestText(sceneId,x585000_g_NoMoney)	--钱不够
				EndQuestEvent()
				DispatchQuestTips(sceneId,selfId)
			end		

		else
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"背包已满，无法得到物品！您需要至少有1个背包空间！")
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
			return 0
		end	


end

----------------------------------------------------------------------------------------------
--默认事件
----------------------------------------------------------------------------------------------
function x585000_ProcEventEntry( sceneId, selfId, targetId,scriptId,idExt )

		if x585000_CheckDateValid() == 0 then
			return
		end

		--如果已经领过
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"#Y"..x585000_g_MissionName)
		AddQuestText(sceneId,x585000_g_Readme);
		AddQuestItemBonus(sceneId, x585000_g_BonusItem, 1)
	  EndQuestEvent(sceneId)
		DispatchQuestInfoNM(sceneId, selfId, targetId, x585000_g_ScriptId, x585000_g_ScriptId);
		return	
end

----------------------------------------------------------------------------------------------
--检测接受条件
----------------------------------------------------------------------------------------------
function x585000_ProcAcceptCheck( sceneId, selfId, NPCId )
    return 1
end

----------------------------------------------------------------------------------------------
--接受
----------------------------------------------------------------------------------------------
function x585000_ProcAccept( sceneId, selfId )
	
	if x585000_CheckDateValid() == 0 then
		return
	end
	
	if GetGameOpenById(1028 ) == 0 then
		return
	end
	
	--检查周是否有效
	local nCurWeek = x585000_GetCurrentWeek()
	local nLastWeek = x585000_GetLastWeek(sceneId,selfId )
	local nWeekDay = GetWeek() + 1
	
	if nCurWeek == nLastWeek then
		
		--如果当前周就是最后领奖的周
		
		if x585000_GetLastWeek_WD(sceneId,selfId ) == 1 or x585000_IsWeekGive( sceneId,selfId ) == 1 then
			
			--如果已经领过
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"您已经购买了本周礼包，无法进行多次购买！");			
		    EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
			return	
		else
			--如果没有领过,执行领奖操作
			if x585000_GiveBonus( sceneId,selfId ) == 1 then
				x585000_SetLastWeek_WD(sceneId,selfId)
			end
			
			return
		end
		
		
		
	elseif nCurWeek > nLastWeek then
		
		--如果当前周大于最领奖的周,表示跨周了
		--如果没有领过,执行领奖操作
		if x585000_GiveBonus( sceneId,selfId ) == 1 then
			x585000_SetLastWeek(sceneId,selfId)
			x585000_SetLastWeek_WD(sceneId,selfId)
		end
		
		return
		
	else
		return
	end
end

----------------------------------------------------------------------------------------------
--放弃
----------------------------------------------------------------------------------------------
function x585000_ProcQuestAbandon( sceneId, selfId, MissionId )
end

----------------------------------------------------------------------------------------------
--继续
----------------------------------------------------------------------------------------------
function x585000_OnContinue( sceneId, selfId, targetId )
end

----------------------------------------------------------------------------------------------
--检测是否可以提交
----------------------------------------------------------------------------------------------
function x585000_CheckSubmit( sceneId, selfId )
end

----------------------------------------------------------------------------------------------
--提交
----------------------------------------------------------------------------------------------
function x585000_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end

----------------------------------------------------------------------------------------------
--杀死怪物或玩家
----------------------------------------------------------------------------------------------
function x585000_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end

----------------------------------------------------------------------------------------------
--进入区域事件
----------------------------------------------------------------------------------------------
function x585000_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

----------------------------------------------------------------------------------------------
--道具改变
----------------------------------------------------------------------------------------------
function x585000_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
