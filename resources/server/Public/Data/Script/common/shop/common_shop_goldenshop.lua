--功能：金币商店

x560888_g_ScriptId = 560888

--静态商店数量
x560888_g_StaticShopNum = 142

--动态商店数量
x560888_g_DynamicShopNum = 60

--静态商店
x560888_g_StaticShopList = { 								
								401,402,403,404,405,406,407,408,409,410,411,412,413,414,415,416,417,418,419,420,
								421,422,423,424,425,426,427,428,429,430,431,432,433,434,435,436,437,438,439,440,
								441,442,443,444,445,446,447,448,449,450,451,452,453,454,455,456,457,458,459,460,
								461,462,463,464,465,466,467,468,469,470,471,472,473,474,475,476,477,478,479,480,
								481,482,483,484,485,486,487,488,489,490,491,492,493,494,495,496,497,498,499,500,
								501,502,503,504,505,506,507,508,509,510,511,512,513,514,515,516,517,518,519,520,
								521,522,523,524,525,526,527,528,529,530,531,532,533,534,535,536,537,538,539,540,
								541,542,543,
							}

--基于职业、等级类的动态商店，优先级最高
x560888_g_DynamicShopList3= {								
								{544,545,546,547,548,549,550,551,552,553,},				--zhiye=0武士
								{554,555,556,557,558,559,560,561,562,563,},				--zhiye=1剑侠
								{564,565,566,567,568,569,570,571,572,573,},				--zhiye=2骑射
								{574,575,576,577,578,579,580,581,582,583,},				--zhiye=3火枪
								{584,585,586,587,588,589,590,591,592,593,},				--zhiye=4先知
								{594,595,596,597,598,599,600,601,602,603,},				--zhiye=5萨满
								{1544,1545,1546,1547,1548,1549,1550,1551,1552,1553,},	--zhiye=6十字军
								{1554,1555,1556,1557,1558,1559,1560,1561,1562,1563,},	--zhiye=7圣火使
								{1564,1565,1566,1567,1568,1569,1570,1571,1572,1573,},	--zhiye=8刺客
								{1574,1575,1576,1577,1578,1579,1580,1581,1582,1583,},	--zhiye=9近卫军
								{1584,1585,1586,1587,1588,1589,1590,1591,1592,1593,},	--zhiye=10隐修士
								{1594,1595,1596,1597,1598,1599,1600,1601,1602,1603,},	--zhiye=11僧侣
							}

--基于职业、等级类的动态商店，优先级较高 
x560888_g_DynamicShopList2= {								
								{604,605,606,607,608,609,610,611,612,613,},	
								{614,615,616,617,618,619,620,621,622,623,},	
								{624,625,626,627,628,629,630,631,632,633,},	
								{634,635,636,637,638,639,640,641,642,643,},	
								{644,645,646,647,648,649,650,651,652,653,},	
								{654,655,656,657,658,659,660,661,662,663,},	
								{1604,1605,1606,1607,1608,1609,1610,1611,1612,1613,},	
								{1614,1615,1616,1617,1618,1619,1620,1621,1622,1623,},	
								{1624,1625,1626,1627,1628,1629,1630,1631,1632,1633,},	
								{1634,1635,1636,1637,1638,1639,1640,1641,1642,1643,},	
								{1644,1645,1646,1647,1648,1649,1650,1651,1652,1653,},	
								{1654,1655,1656,1657,1658,1659,1660,1661,1662,1663,},
							}

--基于职业、等级类的动态商店，优先级最低 
x560888_g_DynamicShopList1= {								
								{664,665,666,667,668,669,670,671,672,673,},	
								{674,675,676,677,678,679,680,681,682,683,},
								{684,685,686,687,688,689,690,691,692,693,},
								{694,695,696,697,698,699,700,701,702,703,},	
								{704,705,706,707,708,709,710,711,712,713,},	
								{714,715,716,717,718,719,720,721,722,723,},
								{1664,1665,1666,1667,1668,1669,1670,1671,1672,1673,},	
								{1674,1675,1676,1677,1678,1679,1680,1681,1682,1683,},
								{1684,1685,1686,1687,1688,1689,1690,1691,1692,1693,},
								{1694,1695,1696,1697,1698,1699,1700,1701,1702,1703,},	
								{1704,1705,1706,1707,1708,1709,1710,1711,1712,1713,},	
								{1714,1715,1716,1717,1718,1719,1720,1721,1722,1723,},
							}


--基于职业的动态等级分段
x560888_g_DynamicLevelList ={
								{30,40,50,60,70,80,90,100,110,161,},		--zhiye=0武士
								{30,40,50,60,70,80,90,100,110,161,},		--zhiye=1剑侠
								{30,40,50,60,70,80,90,100,110,161,},		--zhiye=2骑射
								{30,40,50,60,70,80,90,100,110,161,},		--zhiye=3火枪
								{30,40,50,60,70,80,90,100,110,161,},		--zhiye=4先知
								{30,40,50,60,70,80,90,100,110,161,},		--zhiye=5萨满
								{30,40,50,60,70,80,90,100,110,161,},		--zhiye=6十字军
								{30,40,50,60,70,80,90,100,110,161,},		--zhiye=7圣火使
								{30,40,50,60,70,80,90,100,110,161,},		--zhiye=8刺客
								{30,40,50,60,70,80,90,100,110,161,},		--zhiye=9近卫军
								{30,40,50,60,70,80,90,100,110,161,},		--zhiye=10隐修士
								{30,40,50,60,70,80,90,100,110,161,},		--zhiye=11僧侣
							}

--今日特卖商店
x560888_g_TodayShopList =	{
								724,725,726,727,728,729,730,
							}

x560888_g_TodayShopIndex = 143

x560888_g_VipLevelNewStar = 999 -- 999 新星麒麟

function x560888_ProcEventEntry(sceneId, selfId, targetId)	--点击该任务后执行此脚本
end


function x560888_ProcEnumEvent(sceneId, selfId, targetId, MissionId)

end


function x560888_OnDispatchGoldShopItem(sceneId, selfId, index,isChangeCurrShop)	--点击该任务后执行此脚本

	if GetLevel(sceneId,selfId) < 10 then
		local text = "您的等级未到10，无法进入金币商城。"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,text)
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,text,8,2)
		return
	end

	--打开静态商店
	if index >= 1 and index <= x560888_g_StaticShopNum then
		if x560888_g_StaticShopList[index] >= 532 and x560888_g_StaticShopList[index] <= 543 then
			--动态的测试商店
			if GetTestGoldShopToggle() == 0 then
				return
			end			
		end
		
		DispatchGoldShopItem( sceneId, selfId, x560888_g_StaticShopList[index],index,isChangeCurrShop )
		return
	end	

	if index == 0 then	
		--打开动态商店
		x560888_OpensDynamicShop(sceneId, selfId,isChangeCurrShop)
		return
	end

	if index == x560888_g_TodayShopIndex then	
		--打开本日特卖商店
		x560888_OpenTodayShop(sceneId, selfId,isChangeCurrShop)
		return
	end


end


--商店是否在有效时间内
function x560888_IsValidShop(sceneId, selfId,shopId)
	
	local hour,minute,second = GetHourMinSec()
	local timeType,startTime,endTime = GetShopConfigInfo(sceneId, selfId,shopId)

	local nowTime = hour*100 + minute

	if timeType == 1 then		--每天执行一次

		startTime = mod(startTime,10000)
		endTime = mod(endTime,10000)	

	elseif timeType == 2 then	--每周执行一次

		startTime = mod(startTime,100000)
		endTime = mod(endTime,100000)	

	elseif timeType == 3 then	--每月执行一次

		startTime = mod(startTime,1000000)
		endTime = mod(endTime,1000000)

	else 
		
		return 0
		
	end

	if nowTime >= startTime and nowTime <= endTime then
		---有效时间内
		return 1
	end

	return 0

end


--打开动态商店
function x560888_OpensDynamicShop(sceneId, selfId,isChangeCurrShop)
		
	local	zhiye = GetZhiye(sceneId, selfId)

	if zhiye < 0 or zhiye >= 12 then
			--出错了
		return
	end

	for i,level in x560888_g_DynamicLevelList[zhiye+1] do

		if GetLevel(sceneId,selfId) < level then

			local shopId = x560888_g_DynamicShopList3[zhiye+1][i]
			if x560888_IsValidShop(sceneId, selfId,shopId) == 1 then
				DispatchGoldShopItem( sceneId, selfId, shopId,0,isChangeCurrShop )
				return
			end

			shopId = x560888_g_DynamicShopList2[zhiye+1][i]
			if x560888_IsValidShop(sceneId, selfId,shopId) == 1 then
				DispatchGoldShopItem( sceneId, selfId, shopId,0,isChangeCurrShop )
				return
			end			

			shopId = x560888_g_DynamicShopList1[zhiye+1][i]
			DispatchGoldShopItem( sceneId, selfId, shopId,0,isChangeCurrShop )

			return
		end

	end

end

--打开本日特卖商店
function x560888_OpenTodayShop(sceneId, selfId,isChangeCurrShop)
	
	--得到今天是星期几
	local nWeek = GetWeek()
	if nWeek >=0 and nWeek < 7 then
		local shopId = x560888_g_TodayShopList[nWeek+1]
		DispatchGoldShopItem( sceneId, selfId, shopId,x560888_g_TodayShopIndex,isChangeCurrShop )
		
	end
end

--判断是否有权限购买商品
function x560888_OnIsCanBuy(sceneId, selfId, shopId)

	if (shopId >= x560888_g_DynamicShopList3[1][1] and shopId <= x560888_g_DynamicShopList1[6][10]) or 
	   (shopId >= x560888_g_DynamicShopList3[7][1] and shopId <= x560888_g_DynamicShopList1[12][10]) then

		--按日期开放的动态商店
		if x560888_IsValidShop(sceneId, selfId,shopId) == 1 then
			return 1
		else
			return 0
		end
		
	end
	
	if shopId >= x560888_g_TodayShopList[1] and shopId <= x560888_g_TodayShopList[7] then
		--本日特卖商店
		local nWeek = GetWeek()
		if nWeek >=0 and nWeek < 7 then
			if x560888_g_TodayShopList[nWeek+1] == shopId then
				return 1
			else
				return 0
			end
	
		end
	end

	if shopId == x560888_g_StaticShopList[120] then

		local nVipLevel = GetVipLevel(sceneId, selfId);
		if nVipLevel < 1 or nVipLevel == x560888_g_VipLevelNewStar then
--			local text = "你的VIP等级未到一星麒麟,不能购买此物品！"
--			BeginQuestEvent(sceneId)
--			AddQuestText(sceneId,text)
--			EndQuestEvent(sceneId)
--			DispatchQuestTips(sceneId,selfId)
--			Msg2Player(sceneId,selfId,text,8,2)

			ShowMsgBoxMibaoka(sceneId, selfId,1)
			
			return 0
		end

		return 1

	end

	if shopId == x560888_g_StaticShopList[121] then

		local nVipLevel = GetVipLevel(sceneId, selfId);
		if nVipLevel < 2 or nVipLevel == x560888_g_VipLevelNewStar then
--			local text = "你的VIP等级未到二星麒麟,不能购买此物品！"
--			BeginQuestEvent(sceneId)
--			AddQuestText(sceneId,text)
--			EndQuestEvent(sceneId)
--			DispatchQuestTips(sceneId,selfId)
--			Msg2Player(sceneId,selfId,text,8,2)
			
			ShowMsgBoxMibaoka(sceneId, selfId,1)

			return 0
		end

		return 1
	
	end
	
	if shopId == x560888_g_StaticShopList[122] then

		local nVipLevel = GetVipLevel(sceneId, selfId);
		if nVipLevel < 3 or nVipLevel == x560888_g_VipLevelNewStar then
			
			ShowMsgBoxMibaoka(sceneId, selfId,1)

			return 0
		end

		return 1
	
	end
	
	return 1
end


function x560888_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--接受

--**********************************

function x560888_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--放弃

--**********************************

function x560888_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--检测是否可以提交

--**********************************

function x560888_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--提交

--**********************************

function x560888_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--杀死怪物或玩家

--**********************************

function x560888_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--进入区域事件

--**********************************

function x560888_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--道具改变

--**********************************

function x560888_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end

--得到商店id
function x560888_GetShopIdByShopIndex(sceneId, selfId, shopindex)

	--静态商店
	if shopindex >= 1 and shopindex <= x560888_g_StaticShopNum then
		return x560888_g_StaticShopList[shopindex]	
	end

	--动态商店
	if shopindex == 0 then	
		return x560888_GetDynamicShopId(sceneId, selfId)
	end
	
	--本日特卖商店	
	if index == x560888_g_TodayShopIndex then	
		--得到今天是星期几
		local nWeek = GetWeek()
		if nWeek >=0 and nWeek < 7 then
			return x560888_g_TodayShopList[nWeek+1]		
		end	
	end
	
	return -1
end

--得到商店的index
function x560888_GetShopIndexByShopId(sceneId, selfId, shopid)

	--静态商店
	if (shopid >= 401) and (shopid <= 543) then
		return (shopid - 401 +1)
	end
	
	--动态商店		
	if (shopid >= 544 and shopid <= 603) or (shopid >= 1544 and shopid <= 1603) or
		 (shopid >= 604 and shopid <= 663) or (shopid >= 1604 and shopid <= 1663) or
		 (shopid >= 664 and shopid <= 723) or (shopid >= 1664 and shopid <= 1723) then	
		if shopid == x560888_GetDynamicShopId (sceneId, selfId) then
			return 0
		end
				
	end
	
	--本日特卖商店	
	if (shopid >= 724) and (shopid <= 730) then
	
		--得到今天是星期几
		local nWeek = GetWeek()
		if nWeek >=0 and nWeek < 7 then
			if shopid == x560888_g_TodayShopList[nWeek+1]	then
				return x560888_g_TodayShopIndex;
			end
		end				
	end
	
	return -1;
	
end

function x560888_GetDynamicShopId(sceneId, selfId)

	local	zhiye = GetZhiye(sceneId, selfId)

	if zhiye < 0 or zhiye >= 12 then
		return -1
	end
	
	for i,level in x560888_g_DynamicLevelList[zhiye+1] do			
		if GetLevel(sceneId,selfId) < level then	
			local shopId = x560888_g_DynamicShopList3[zhiye+1][i]
			if x560888_IsValidShop(sceneId, selfId,shopId) == 1 then					
				return shopId
			end

			shopId = x560888_g_DynamicShopList2[zhiye+1][i]
			if x560888_IsValidShop(sceneId, selfId,shopId) == 1 then
				return shopId
			end			

			shopId = x560888_g_DynamicShopList1[zhiye+1][i]
			return shopId
		end	
	end
	
	return -1
end