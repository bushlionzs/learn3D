x700104_g_ScriptId 		= 700104

x700104_g_MaxCount		= 5

x700104_g_SubmitItem	= 11990015

x700104_g_TitleInfo		= "在这里你可以用藏宝令兑换一些道具材料。但兑换一次将消耗一次再次进入藏宝洞的机会。"

x700104_g_SelectOpt		= {
							{"藏宝令兑换水晶",11001}, 
							{"藏宝令兑换龙眼石",11002}, 
							{"藏宝令兑换声望",11003}, 
							{"藏宝令兑换银币",11004}, 
							{"藏宝令兑换生活技能材料",11005}
						}
						
x700104_g_SelectPane1	= {
							{"世传水晶", 11011, 11000200, 20, 9},
							{"国传水晶", 11012, 11000201, 40, 9},
							{"神传水晶", 11013, 11000202, 60, 9},
							{"天传水晶", 11014, 11000203, 80, 9}
						}
						
x700104_g_SelectPane2	= {
							{"初级龙眼石", 11021, 11050001, 20, 9},
							{"中级龙眼石", 11022, 11050002, 40, 9},
							{"高级龙眼石", 11023, 11050003, 60, 9},
							{"天之龙眼石", 11024, 11050004, 80, 9},
							{"换冥之龙眼石",11025,11050005, 100,9}
						}
						
x700104_g_SelectPane5	= {
							{"草本精华", 11051, 11020501},
							{"七步蛇", 11052, 11030405},
							{"熔火石", 11053, 11030501}
						}
						
x700104_g_RandItem = {11010100, 11010101, 11010102}
				
function x700104_ProcEventEntry(sceneId, selfId, NPCId, MissionId,idExt)	--点击该任务后执行此脚本

	if idExt == 11000 then
		x700104_Opt( sceneId, selfId, NPCId )
	elseif idExt == x700104_g_SelectOpt[1][2] then
		x700104_ShowPane1( sceneId, selfId, NPCId )
	elseif idExt == x700104_g_SelectOpt[2][2] then
		x700104_ShowPane2( sceneId, selfId, NPCId )
	elseif idExt == x700104_g_SelectOpt[3][2] then
		x700104_ShowPane3( sceneId, selfId, NPCId )
	elseif idExt == x700104_g_SelectOpt[4][2] then
		x700104_ShowPane4( sceneId, selfId, NPCId )
	elseif idExt == x700104_g_SelectOpt[5][2] then
		x700104_ShowPane5( sceneId, selfId, NPCId )
	elseif idExt >= 11010 and idExt <= 11100 then
		x700104_ShowOpt( sceneId, selfId, NPCId, idExt )
	else
		x700104_ShowInit( sceneId, selfId, NPCId )
	end
end

--列举事件
function x700104_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
	x700104_ShowInit( sceneId, selfId, NPCId )
end

function x700104_ProcAcceptCheck( sceneId, selfId, NPCId )
    return 1
end

--点确定后
function x700104_ProcAccept( sceneId, selfId )
end

function x700104_ShowOpt( sceneId, selfId, NPCId, idExt )
	SetPlayerRuntimeData(sceneId, selfId, RD_HUANGJINKUANGDONG_OPT, idExt)
		
	BeginQuestEvent(sceneId)
		local count = 1
		local name = ""
		if idExt >= x700104_g_SelectPane1[1][2] and idExt <= x700104_g_SelectPane1[4][2] then
			local idx = idExt-11010
			name = x700104_g_SelectPane1[idx][1]
			count = x700104_g_SelectPane1[idx][5]
		elseif idExt >= x700104_g_SelectPane2[1][2] and idExt <= x700104_g_SelectPane2[5][2] then
			local idx = idExt-11020
			name = x700104_g_SelectPane2[idx][1]
			count = x700104_g_SelectPane2[idx][5]
		elseif idExt >= x700104_g_SelectPane5[1][2] and idExt <= x700104_g_SelectPane5[3][2] then
			local idx = idExt-11050
			name = x700104_g_SelectPane5[idx][1]
			
			local level = GetLevel(sceneId, selfId)
			if level >= 70 then
				count =35
			elseif level >= 60 then
				count =30
			elseif level >= 50 then
				count =15
			end
		end
		
		local str = format("你确定要用藏宝令兑换%d个%s", count, name)
		AddQuestText(sceneId,str)
		
		AddQuestNumText(sceneId,x700104_g_ScriptId,"确定",3,11000)
	EndQuestEvent()
	DispatchQuestEventList(sceneId, selfId, NPCId)
end

function x700104_Opt( sceneId, selfId, NPCId )

	if x700104_GetDayCount(sceneId, selfId) >= x700104_g_MaxCount then
		return
	end
		
	local opt = GetPlayerRuntimeData(sceneId,selfId,RD_HUANGJINKUANGDONG_OPT)
	
	if opt == x700104_g_SelectOpt[3][2] then
		
		if DelItem( sceneId, selfId, x700104_g_SubmitItem, 1) == 0 then
		    Msg2Player( sceneId, selfId, "没有藏宝令。", 8, 3)
		    Msg2Player( sceneId, selfId, "没有藏宝令。", 8, 2)
		    
		    x700104_ShowInit( sceneId, selfId, NPCId )
		    return
		end
		x700104_SetDayCount(sceneId, selfId)
			
		local bQingjian = x700104_CheckQingjian(sceneId, selfId)
		local nadd = 620*(bQingjian+1)
		local nShengWang = GetShengWang( sceneId, selfId ) + nadd
		SetShengWang( sceneId, selfId, nShengWang )
		
		if GetLevel(sceneId, selfId) >= 80 and random(1, 100) <= 5 then
			local index = random(1,3)
			if index < 1 then index = 1 end
			if index > 3 then index = 3 end
			local rndItemid = x700104_g_RandItem[index]
			
			BeginAddItem( sceneId )
			AddItem( sceneId, rndItemid, 1)
			local ret = EndAddItem( sceneId, selfId )
			if ret > 0 then
				AddItemListToPlayer(sceneId,selfId)
				
				local str = format("#Y随机获得#G1个#Y#{_ITEM%d}", rndItemid)
				Msg2Player(sceneId, selfId, str, 8, 3)
				--Msg2Player(sceneId, selfId, str, 8, 2)
			end
		end
		
		str = format("获得#R声望%d#o的奖励", nadd)
		Msg2Player(sceneId, selfId, str, 8, 3)
		Msg2Player(sceneId, selfId, str, 8, 2)
		
	elseif opt == x700104_g_SelectOpt[4][2] then
		
		if DelItem( sceneId, selfId, x700104_g_SubmitItem, 1) == 0 then
		    Msg2Player( sceneId, selfId, "没有藏宝令。", 8, 3)
		    Msg2Player( sceneId, selfId, "没有藏宝令。", 8, 2)
		    
		    x700104_ShowInit( sceneId, selfId, NPCId )
		    return
		end
		x700104_SetDayCount(sceneId, selfId)
		
		local bQingjian = x700104_CheckQingjian(sceneId, selfId)
		if bQingjian > 0 then
                        local nadd_yinbi_1 = GetLevel(sceneId, selfId)*200
                        local nadd_yinka_1 = GetLevel(sceneId, selfId)*400

			AddMoney(sceneId, selfId, 0, nadd_yinbi_1)
			AddMoney(sceneId, selfId, 1, nadd_yinka_1)
			
			Msg2Player(sceneId,selfId,format("获得#{_MONEY%d}现银与#{_MONEY%d}银卡",nadd_yinbi_1,nadd_yinka_1),8,3)
		else
                        local nadd_yinka = GetLevel(sceneId, selfId)*600
			AddMoney(sceneId, selfId, 1, nadd_yinka)
			Msg2Player(sceneId,selfId,format("获得#{_MONEY%d}银卡。",nadd_yinka),8,3)
		end
		
		if GetLevel(sceneId, selfId) >= 80 and random(1, 100) <= 5 then
			local index = random(1,3)
			if index < 1 then index = 1 end
			if index > 3 then index = 3 end
			local rndItemid = x700104_g_RandItem[index]
			
			BeginAddItem( sceneId )
			AddItem( sceneId, rndItemid, 1)
			local ret = EndAddItem( sceneId, selfId )
			if ret > 0 then
				AddItemListToPlayer(sceneId,selfId)
				
				local str = format("#Y随机获得#G1个#Y#{_ITEM%d}", rndItemid)
				Msg2Player(sceneId, selfId, str, 8, 3)
				--Msg2Player(sceneId, selfId, str, 8, 2)
			end
		end
	
	elseif opt >= x700104_g_SelectPane1[1][2] and opt <= x700104_g_SelectPane1[4][2] then
		local idx = opt-11010
		x700104_AddItem(sceneId, selfId, NPCId, x700104_g_SelectPane1[idx][1], x700104_g_SelectPane1[idx][3], x700104_g_SelectPane1[idx][5])
	elseif opt >= x700104_g_SelectPane2[1][2] and opt <= x700104_g_SelectPane2[5][2] then
		local idx = opt-11020
		x700104_AddItem(sceneId, selfId, NPCId, x700104_g_SelectPane2[idx][1], x700104_g_SelectPane2[idx][3], x700104_g_SelectPane2[idx][5])
	elseif opt >= x700104_g_SelectPane5[1][2] and opt <= x700104_g_SelectPane5[3][2] then
		local idx = opt-11050
		local count = 1
		local level = GetLevel(sceneId, selfId)
		if level >= 70 then
			count =35
		elseif level >= 60 then
			count =30
		elseif level >= 50 then
			count =15
		end
		
		x700104_AddItem(sceneId, selfId, NPCId, x700104_g_SelectPane5[idx][1], x700104_g_SelectPane5[idx][3],count)
	end
	
	x700104_ShowInit( sceneId, selfId, NPCId )
end

-- 显示初始界面
function x700104_ShowInit( sceneId, selfId, NPCId )
	BeginQuestEvent(sceneId)
		--任务信息
		AddQuestText(sceneId,"#Y"..x700104_g_TitleInfo)
		
		-- 检查次数
		local daycount = x700104_GetDayCount(sceneId, selfId)
		if daycount < x700104_g_MaxCount then
			for i, item in x700104_g_SelectOpt do
				if i ~= 3 then
					AddQuestNumText(sceneId,x700104_g_ScriptId,item[1],3,item[2])
				end
			end
		else
			AddQuestText(sceneId,"进入藏宝洞的次数不足无法兑换")
		end
	EndQuestEvent()
	--DispatchQuestInfo(sceneId, selfId, NPCId, x700104_g_ScriptId, -1)
	DispatchQuestEventList(sceneId, selfId, NPCId)
end

--藏宝令兑换水晶
function x700104_ShowPane1( sceneId, selfId, NPCId )
	local level = GetLevel(sceneId, selfId)
	BeginQuestEvent(sceneId)
		--任务信息
		AddQuestText(sceneId,"#Y"..x700104_g_TitleInfo)
		
		for i, item in x700104_g_SelectPane1 do
			if level >= item[4] then
				AddQuestNumText(sceneId,x700104_g_ScriptId,"藏宝令兑换"..item[1],3,item[2])
			end
		end
	EndQuestEvent()
	DispatchQuestEventList(sceneId, selfId, NPCId)
end

--藏宝令兑换龙眼石
function x700104_ShowPane2( sceneId, selfId, NPCId )
	local level = GetLevel(sceneId, selfId)
	BeginQuestEvent(sceneId)
		--任务信息
		AddQuestText(sceneId,"#Y"..x700104_g_TitleInfo)
		
		for i, item in x700104_g_SelectPane2 do
			if level >= item[4] then
				AddQuestNumText(sceneId,x700104_g_ScriptId,"藏宝令兑换"..item[1],3,item[2])
			end
		end
	EndQuestEvent()
	DispatchQuestEventList(sceneId, selfId, NPCId)
end
--藏宝令兑换声望
function x700104_ShowPane3( sceneId, selfId, NPCId )
	SetPlayerRuntimeData(sceneId, selfId, RD_HUANGJINKUANGDONG_OPT, x700104_g_SelectOpt[3][2])
		
	BeginQuestEvent(sceneId)
		
		local bQingjian = x700104_CheckQingjian(sceneId, selfId)
		local nadd = 620*(bQingjian+1)
		
		local str = format("你确定要用藏宝令兑换%d点声望吗？", nadd)
		AddQuestText(sceneId,str)
		
		AddQuestNumText(sceneId,x700104_g_ScriptId,"确定",3,11000)
	EndQuestEvent()
	DispatchQuestEventList(sceneId, selfId, NPCId)
end
--藏宝令兑换银币
function x700104_ShowPane4( sceneId, selfId, NPCId )
	SetPlayerRuntimeData(sceneId, selfId, RD_HUANGJINKUANGDONG_OPT, x700104_g_SelectOpt[4][2])
	
	BeginQuestEvent(sceneId)
		
		local bQingjian = x700104_CheckQingjian(sceneId, selfId)

		local str = ""
		if bQingjian == 1 then
                        local nadd_yinbi_1 = GetLevel(sceneId, selfId)*200
                        local nadd_yinka_1 = GetLevel(sceneId, selfId)*400		
			str = format("你确定要用藏宝令兑换%d文现银与%d文银卡吗", nadd_yinbi_1, nadd_yinka_1)
		else
                        local nadd_yinka  =  GetLevel(sceneId, selfId)*600
			str = format("你确定要用藏宝令兑换%d点银卡吗？", nadd_yinka)
		end

		AddQuestText(sceneId,str)
		
		AddQuestNumText(sceneId,x700104_g_ScriptId,"确定",3,11000)
	EndQuestEvent()
	DispatchQuestEventList(sceneId, selfId, NPCId)
end

--藏宝令兑换生活技能材料
function x700104_ShowPane5( sceneId, selfId, NPCId )
	local level = GetLevel(sceneId, selfId)
	BeginQuestEvent(sceneId)
		--任务信息
		AddQuestText(sceneId,"#Y"..x700104_g_TitleInfo)
		
		if level < 50 then
			AddQuestText(sceneId,"\n\t级别高于50级以后才可以兑换生活技能材料。")
		else
			for i, item in x700104_g_SelectPane5 do
				if level >= 50 then
					AddQuestNumText(sceneId,x700104_g_ScriptId,"藏宝令兑换"..item[1],3,item[2])
				end
			end
		end
	EndQuestEvent()
	DispatchQuestEventList(sceneId, selfId, NPCId)
end

-- 判断江湖请柬
function x700104_CheckQingjian(sceneId, selfId)
    if IsHaveSpecificImpact( sceneId, selfId, 9011 )>0 or IsHaveSpecificImpact( sceneId, selfId, 9013 ) > 0  or IsHaveSpecificImpact( sceneId, selfId, 9012 ) > 0 then
        return 1
    end
    return 0
end

-- 获得物品
function x700104_AddItem( sceneId, selfId, NPCId, itemname, itemid, count )
	BeginAddItem( sceneId )
	AddItem( sceneId, itemid, count)
	
	local rndItemid = -1
	if GetLevel(sceneId, selfId) >= 80 and random(1, 100) <= 5 then
		local index = random(1,3)
		if index < 1 then index = 1 end
		if index > 3 then index = 3 end
		rndItemid = x700104_g_RandItem[index]
		AddItem( sceneId, rndItemid, 1)
	end
	
	local ret = EndAddItem( sceneId, selfId )
	if ret > 0 then
		if DelItem( sceneId, selfId, x700104_g_SubmitItem, 1) == 0 then
		    Msg2Player( sceneId, selfId, "没有藏宝令。", 8, 3)
		    Msg2Player( sceneId, selfId, "没有藏宝令。", 8, 2)
		    
		    x700104_ShowInit( sceneId, selfId, NPCId )
		    return
		end
		x700104_SetDayCount(sceneId, selfId)
		
		AddItemListToPlayer(sceneId,selfId)
		
		local str = "#Y获得#G"..count.."个#Y"..itemname
		Msg2Player(sceneId, selfId, str, 8, 3)
		Msg2Player(sceneId, selfId, str, 8, 2)
		
		if rndItemid ~= -1 then
			local str = format("#Y随机获得#G1个#Y#{_ITEM%d}", rndItemid)
			Msg2Player(sceneId, selfId, str, 8, 3)
			--Msg2Player(sceneId, selfId, str, 8, 2)
		end
	else
		local str = "#Y背包空间不足，请整理背包后再试！"
		Msg2Player(sceneId, selfId, str, 8, 3)
		Msg2Player(sceneId, selfId, str, 8, 2)
	end
end

---------------------------------------------------------------------------------------------------
--取得此任务当天当前已完成次数
---------------------------------------------------------------------------------------------------
function x700104_GetDayCount(sceneId, selfId)
	if x700104_g_MaxCount > 0 then
		local today = GetDayOfYear()
		local lastday = GetQuestData(sceneId, selfId, MD_FUBEN_HUANGJINKUANGDONG_DATE[1], MD_FUBEN_HUANGJINKUANGDONG_DATE[2], MD_FUBEN_HUANGJINKUANGDONG_DATE[3])
		if lastday ~= today then
			return 0
		end

		local daycount =  GetQuestData(sceneId, selfId, MD_FUBEN_HUANGJINKUANGDONG_DAYCOUNT[1], MD_FUBEN_HUANGJINKUANGDONG_DAYCOUNT[2], MD_FUBEN_HUANGJINKUANGDONG_DAYCOUNT[3])
		return daycount

	end
	return 0
end

---------------------------------------------------------------------------------------------------
--更新当天接任务次数
---------------------------------------------------------------------------------------------------
function x700104_SetDayCount(sceneId, selfId)
	local today = GetDayOfYear()
	local lastday = GetQuestData(sceneId, selfId, MD_FUBEN_HUANGJINKUANGDONG_DATE[1], MD_FUBEN_HUANGJINKUANGDONG_DATE[2], MD_FUBEN_HUANGJINKUANGDONG_DATE[3])
	if lastday ~= today then
		SetQuestData(sceneId, selfId, MD_FUBEN_HUANGJINKUANGDONG_DATE[1], MD_FUBEN_HUANGJINKUANGDONG_DATE[2], MD_FUBEN_HUANGJINKUANGDONG_DATE[3], today)
		SetQuestData(sceneId, selfId, MD_FUBEN_HUANGJINKUANGDONG_DAYCOUNT[1], MD_FUBEN_HUANGJINKUANGDONG_DAYCOUNT[2], MD_FUBEN_HUANGJINKUANGDONG_DAYCOUNT[3], 1)
	else
		local daycount = GetQuestData(sceneId, selfId, MD_FUBEN_HUANGJINKUANGDONG_DAYCOUNT[1], MD_FUBEN_HUANGJINKUANGDONG_DAYCOUNT[2], MD_FUBEN_HUANGJINKUANGDONG_DAYCOUNT[3])
		SetQuestData(sceneId, selfId, MD_FUBEN_HUANGJINKUANGDONG_DAYCOUNT[1], MD_FUBEN_HUANGJINKUANGDONG_DAYCOUNT[2], MD_FUBEN_HUANGJINKUANGDONG_DAYCOUNT[3], daycount+1)
	end
end
