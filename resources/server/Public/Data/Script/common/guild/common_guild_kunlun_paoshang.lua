--帮会商人脚本

x300675_g_ScriptId = 300675
x300675_g_MissionId = 7028

-- NPC guid
x300675_g_GUID_Normal_Npcs = {
								129180,		-- 铁骑镇商人
								129181,		-- 灵芝牧场商人
								129182,		-- 咸海湾商人
							}
x300675_g_GUID_Special_Npc = 129183			-- 特殊商人

-- 刷新时间，5分钟
x300675_g_RefreshTime = 60*5*1000

-- 特殊NPC按钮间隔时间
x300675_g_SpecialNpc_Interval = 300
x300675_g_SpecialNpc_Times = {0,0,0,0,0,0}

--价格基准线
x300675_g_Price_BenchMark = {
								{3384,2270,1154},	----  20-50级 (高，中，低)
								{3384,2270,1154},	----  50-70级
								{3384,2270,1154}	----  70级以上
							}
--价格浮动值 正负50
x300675_g_Price_Refix = 100

--实际价格值
x300675_g_Price = 	{
						--normal npc1
						{ 
							npcguid = x300675_g_GUID_Normal_Npcs[1],	-- npc guid，不用配置
							AllPrices = { {}, {}, {} },					-- 价格存储空间，不用配置
							priceflag = {1,1,2,2,3,3},					-- 商品价格等级，1为高价，2为中价，3为低价
						},
						--normal npc2
						{ 
							npcguid = x300675_g_GUID_Normal_Npcs[2], 
							AllPrices = { {}, {}, {} },
							priceflag = {3,3,1,1,2,2},
						},
						--normal npc3
						{ 
							npcguid = x300675_g_GUID_Normal_Npcs[3], 
							AllPrices = { {}, {}, {} },
							priceflag = {2,2,3,3,1,1},
						},
						--special npc
						{ 
							npcguid = x300675_g_GUID_Special_Npc, 
							AllPrices = { {}, {}, {} },
							priceflag = {1,1,1,1,1,1},
						},
					}

--物品信息
x300675_Item_Goods = { 13030122, 13030123, 13030124, 13030125, 13030126, 13030127 }
x300675_Item_GoodsName = { "南洋珍珠", "琉球珊瑚", "波斯金鞍", "大宛马铠", "高丽山参", "大理灵芝", }
x300675_Item_Money = 13030128

x300675_g_FirstActive = 1

--点击（NPC）
function x300675_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	
	if IsHaveQuestNM( sceneId, selfId, x300675_g_MissionId ) ~= 1 then
		return
	end
	
	local NpcGUID = GetMonsterGUID(sceneId,targetId)

	if NpcGUID ~= x300675_g_GUID_Special_Npc then		--普通商人
		for i,item in x300675_Item_Goods do
			if HaveItem(sceneId,selfId,item)>0 then
				AddQuestNumText(sceneId,300675,"【帮会跑商】"..x300675_Item_GoodsName[i],3,i)
			end
		end
	else		-- 特殊商人
		local curTime = GetCurrentTime()
		for i,item in x300675_Item_Goods do
			if curTime - x300675_g_SpecialNpc_Times[i] >= x300675_g_SpecialNpc_Interval then
				if HaveItem(sceneId,selfId,item)>0 then
					AddQuestNumText(sceneId,300675,"【帮会跑商】"..x300675_Item_GoodsName[i],3,i)
				end
			end
		end		
	end
	
	if x300675_g_FirstActive == 1 then
		x300675_g_FirstActive = 0
		SetTimer(sceneId, selfId, 300675, "OnSceneTimer", x300675_g_RefreshTime )
		x300675_Refresh_Price(sceneId)
	end
end

--点击（按钮）点击该任务后执行此脚本
function x300675_ProcEventEntry( sceneId, selfId, targetId,state,index)

	
	if IsHaveQuestNM( sceneId, selfId, x300675_g_MissionId ) ~= 1 then
		return
	end
	
	if index < 10 then
		local Readme = "卖物品:"..x300675_Item_GoodsName[index]..",价格:"..x300675_GetPrice(sceneId, selfId, targetId,index)
		BeginQuestEvent(sceneId);
		AddQuestNumText(sceneId,300675,"确定",3,index + 10 )
		AddQuestText(sceneId,Readme);
		EndQuestEvent(sceneId);
		DispatchQuestEventList(sceneId, selfId, targetId)
		
	elseif index > 10 then
	
		local op = index - 10
		
		if GetMonsterGUID(sceneId,targetId) == x300675_g_GUID_Special_Npc then
			if GetCurrentTime() - x300675_g_SpecialNpc_Times[op] < x300675_g_SpecialNpc_Interval then
				BeginQuestEvent(sceneId);
				AddQuestText(sceneId,"交易失败#r刚才有人在你之前出售过这样货物了。");
				EndQuestEvent(sceneId);
				DispatchQuestEventList(sceneId, selfId, targetId)	
				return
			end
		end
		
		if x300675_SaleItem(sceneId, selfId, targetId,op) == 1 then
		
			local bAllSaled = 1
			local bFailed = 0
			for i,item in x300675_Item_Goods do
				if HaveItem(sceneId, selfId,item)>0 then
					bAllSaled = 0
					break
				end
			end
			if bAllSaled == 1 then
				local misIndex = GetQuestIndexByID( sceneId, selfId, x300675_g_MissionId)
				local nMoney = GetQuestParam( sceneId, selfId, misIndex, 0)
				if nMoney < 10000 then
					bFailed = 1
				end			
			end

			BeginQuestEvent(sceneId);
			if bFailed==0 then
				AddQuestText(sceneId,"\t好吧，这货物不错，我愿意收购。");
			else
				AddQuestText(sceneId,"\t你出售了所有的帮会货物，但得到的金钱#G不足以完成任务#W，去帮会任务发布人处#G重新领取任务#W吧。");
			end
			EndQuestEvent(sceneId);
			DispatchQuestEventList(sceneId, selfId, targetId)	

			if bFailed == 1 then			
				local misIndex = GetQuestIndexByID( sceneId, selfId, x300675_g_MissionId)
				--SetQuestByIndex( sceneId, selfId, misIndex, 0, 0)
				SetQuestByIndex( sceneId, selfId, misIndex, 6, 1)
				CallScriptFunction( 300678, "ProcQuestLogRefresh", sceneId, selfId, x300675_g_MissionId )	
			else 
				local price = x300675_GetPrice(sceneId, selfId, targetId, op)
			    local goodsname = x300675_Item_GoodsName[op]
				local salemsg = format("你出售了#G%s#cffcf00，帮会银票中的金额增加了#G%s#cffcf00。",goodsname,price)
				Msg2Player(sceneId, selfId, salemsg, 8, 3);
				Msg2Player(sceneId, selfId, salemsg, 8, 2);
			end
			
			if GetMonsterGUID(sceneId,targetId) == x300675_g_GUID_Special_Npc then
				x300675_g_SpecialNpc_Times[op] = GetCurrentTime()
			end
			
		end
		
	end

end

--点击（确定）
function x300675_ProcAcceptCheck( sceneId, selfId, NPCId )
end

--**********************************
--接受
--**********************************
function x300675_ProcAccept( sceneId, selfId )
end

--**********************************
--放弃
--**********************************
function x300675_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--继续
--**********************************
function x300675_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--检测是否可以提交
--**********************************
function x300675_CheckSubmit( sceneId, selfId )

end

--**********************************
--提交
--**********************************
function x300675_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--杀死怪物或玩家
--**********************************
function x300675_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--进入区域事件
--**********************************
function x300675_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--道具改变
--**********************************
function x300675_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end


function x300675_OnSceneTimer( sceneId )
	x300675_Refresh_Price(sceneId)
end

function x300675_Refresh_Price(sceneId)

	for i1,item1 in x300675_g_Price do					-- NPC循环
		for i2,item2 in item1.AllPrices do				-- 价格循环1，按人物等级
			for i3,item3 in item1.priceflag do			-- 价格循环2，按价格高低
				item2[i3] = x300675_g_Price_BenchMark[i2][item3] + random(1,x300675_g_Price_Refix) - x300675_g_Price_Refix/2
			end
		end		
	end
	
end

function x300675_GetPrice( sceneId, selfId, targetId, itemIndex )

	local price = 0
	local NpcGUID = GetMonsterGUID(sceneId,targetId)
	for i,item in x300675_g_Price do
		if item.npcguid == NpcGUID then
			local level = GetLevel(sceneId, selfId)
			if level>=70 then
				price = item.AllPrices[3][itemIndex]
			elseif level>=50 then
				price = item.AllPrices[2][itemIndex]
			elseif level>=20 then
				price = item.AllPrices[1][itemIndex]
			end
			break
		end
	end
	
	return floor( price)

end

function x300675_SaleItem(sceneId, selfId, targetId, itemIndex )

	if HaveItem(sceneId,selfId,x300675_Item_Goods[itemIndex])<=0 then
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId,"\t你似乎并没有这样货物。");
		EndQuestEvent(sceneId);
		DispatchQuestEventList(sceneId, selfId, targetId)
		return 0
	end
	
	if HaveItem(sceneId,selfId,x300675_Item_Money)<=0 then
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId,"\t你没有帮会银票，无法交易。");
		EndQuestEvent(sceneId);
		DispatchQuestEventList(sceneId, selfId, targetId)		
		return 0
	end	
	
	local price = x300675_GetPrice(sceneId, selfId, targetId,itemIndex)
	local misIndex = GetQuestIndexByID( sceneId, selfId, x300675_g_MissionId)
	local nMoney = GetQuestParam( sceneId, selfId, misIndex, 0)		

	SetQuestByIndex( sceneId, selfId, misIndex, 0, nMoney+price)
	DelItem(sceneId, selfId, x300675_Item_Goods[itemIndex], 1)
	
	CallScriptFunction( 300678, "ProcQuestLogRefresh", sceneId, selfId, x300675_g_MissionId )	
	
	return 1

end