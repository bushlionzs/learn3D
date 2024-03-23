--帮会跑钱脚本

x300678_g_ScriptId = 300678
x300678_g_MissionName = "【帮会】帮会跑商"
x300678_g_MissionId = 7028

x300678_g_Min_Level = 20

x300678_g_SubmitParamIndex = 0
x300678_g_SubmitMoney = 10000

x300678_Item_Goods = { 13030122, 13030123, 13030124, 13030125, 13030126, 13030127 }
x300678_Item_GoodsCount = 3
x300678_Item_Money = 13030128

x300678_Max_Count = 100
x300678_g_MoneyBuff = 8353
x300678_gameopenid = 1029


function x300678_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	
	if GetGameOpenById(x300678_gameopenid)<=0 then
		return
	end

	
	if GetGuildID(sceneId, selfId) ~= -1 then
		local state = GetQuestStateNM(sceneId, selfId, targetId, MissionId);
		AddQuestNumText(sceneId, MissionId, x300678_g_MissionName, state, -1)
	end
end

function x300678_DispatchMissionInfo( sceneId, selfId, NPCId )
		local level = GetLevel(sceneId,selfId)
		local nExp = level*3000
		local GuildMoney =20
		local maxlevel = GetTopListInfo_MaxLevel(GetWorldID(sceneId, selfId))
		local explevel = maxlevel - 10
	
		if nExp> 0 then
			AddQuestExpBonus(sceneId, nExp )
		end

		
end



--选中任务
function x300678_ProcEventEntry( sceneId, selfId, targetId, MissionId )

	if GetGuildID(sceneId, selfId) == -1 then
		return
	end

		local level = GetLevel(sceneId,selfId)
		local GuildLevel = GetGuildSimpleData(GetGuildID( sceneId, selfId ))
		local nExp = level*3000
		local GuildMoney =20
		local maxlevel = GetTopListInfo_MaxLevel(GetWorldID(sceneId, selfId))
		local explevel = maxlevel - 10
	
		if GetGameOpenById(x300678_gameopenid)<=0 then
			return
		end

	if IsHaveQuestNM( sceneId, selfId, MissionId ) == 1 then	-- 如果有这个任务
	 	if GetGuildID(sceneId, selfId) == -1 then
	 		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"你已经不在帮会中，请加入帮会后再继续本任务！")
			EndQuestEvent()
			DispatchQuestDemandInfo(sceneId, selfId, targetId, x300678_g_ScriptId, MissionId,0);
			return
		end	
		
		local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )
		if GetQuestParam( sceneId, selfId, misIndex, 6) == 0 then	--任务失败，重新领取
		
			if x300678_IsMissionCompleted( sceneId, selfId, MissionId ) == 1 then -- 如果任务可以完成
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"#Y【帮会】帮会跑商")
				AddQuestText(sceneId,"\t这么快就赚回这么多？\n\t不错，帮会不会亏待于你。这是你的奖励。#r")
				AddQuestText(sceneId,"#Y奖励内容：")
					AddQuestText(sceneId,"#W经验值："..nExp)
				AddQuestText(sceneId,"#W帮会金钱：20两")
				--x300678_DispatchMissionInfo( sceneId, selfId, targetId )
				--AddQuestText(sceneId,"#W帮会金钱：20点")
				EndQuestEvent()
				DispatchQuestContinueInfoNM(sceneId, selfId, targetId, x300678_g_ScriptId, MissionId);
			else
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"#Y【帮会】帮会跑商")
				AddQuestText(sceneId,"\t一个帮会的强大，不是靠个人之力，需要所有帮众的努力进取。\n\t你也应该为大家做些事情。#r")
				--AddQuestText(sceneId,"#Y奖励内容：")
				--if level < 60 then
				--	AddQuestText(sceneId,"#W经验值："..nExp)
				--elseif level >= 60 and level <=explevel then
				--AddQuestText(sceneId,"#W经验值："..nExp)
				--end
				--AddQuestText(sceneId,"#W帮会金钱：20两")
				--x300678_DispatchMissionInfo( sceneId, selfId, targetId )
				--AddQuestText(sceneId,"#W帮会金钱：20点")
				EndQuestEvent()
				DispatchQuestContinueInfoNM(sceneId, selfId, targetId, x300678_g_ScriptId, MissionId);		
			end
			return
		end
		
	end

	GetGuildQuestData(sceneId, selfId, GD_GUILD_INDEX_GET_MONEY_COUNT, x300678_g_ScriptId, MissionId, "ProcAcceptMission", targetId );
	
end

function x300678_ProcAcceptMission(sceneId, selfId,MissionData,MissionId,targetId)

	if GetGameOpenById(x300678_gameopenid)<=0 then
		return
	end

	if GetGuildID(sceneId, selfId) == -1 then
		return
	end

	local count = 99-(MissionData)
	local level = GetLevel(sceneId,selfId)
	local nExp = level*3000
	local GuildMoney =20
	local maxlevel = GetTopListInfo_MaxLevel(GetWorldID(sceneId, selfId))
	local explevel = maxlevel - 10
	BeginQuestEvent(sceneId)
	local Readme_1 = ""		
	local Readme_2 = "\t我这里有一些帮会的物资需要出售给商人@npc_129180，@npc_129181，@npc_129182为帮会赚取金钱。另外，在王城内的神秘商人@npc_129183常会以#G高价收购所有货物#W。\n\t每次跑商需要缴纳#R5#W两银卡或现银作为押金，完成任务返还5两银卡，如果任务失败，押金将被#R没收#W！#r"
	local Readme = Readme_1 .. Readme_2
	AddQuestText(sceneId,"#Y【帮会】帮会跑商")
	AddQuestText(sceneId,Readme)
	AddQuestText(sceneId,"#W#G帮会本日跑商剩余次数：#Y"..count.."#G次#r")
	AddQuestText(sceneId,"#Y奖励内容：")
		AddQuestText(sceneId,"#W经验值："..nExp)
	AddQuestText(sceneId,"#W帮会金钱：20两")
	
	--x300678_DispatchMissionInfo( sceneId, selfId, targetId )
	--AddQuestText(sceneId,"#W帮会金钱：20点")
	EndQuestEvent()
	DispatchQuestInfoNM(sceneId, selfId, targetId, x300678_g_ScriptId, MissionId);
	
end

function x300678_ProcQuestAccept( sceneId, selfId, targetId, MissionId )
	if GetGameOpenById(x300678_gameopenid)<=0 then
		return
	end
	
	if GetGuildID(sceneId, selfId) == -1 then
		return
	end
	
	local GuildLevel = GetGuildSimpleData(GetGuildID( sceneId, selfId ))
	if GuildLevel < 3 then
		Msg2Player(sceneId,selfId,"很抱歉，只有帮会等级不低于三级才能接取【帮会】帮会跑商任务",8,3) 
		return 
	end	
	
	
	if GetGameOpenById(x300678_gameopenid)<=0 then
		return
	end
	
	if IsQuestFullNM( sceneId, selfId )==1 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"可接任务数量已满")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return 
	end	

	if GetLevel(sceneId, selfId) < x300678_g_Min_Level then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "\t等级过低，不能接受此任务");
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)	
		Msg2Player(sceneId,selfId,"等级过低，不能接受此任务",8,2)	
		return
	end
	
	if GetGuildID(sceneId, selfId) == -1 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "\t你已经不在帮会中，请加入帮会后再继续本任务！");
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)	
		Msg2Player(sceneId,selfId,"你已经不在帮会中，请加入帮会后再继续本任务！",8,2)	
		return
	end
	
	local subsillertype=1
	if CostMoney(sceneId, selfId, 1, 5000) == -1 then
		subsillertype = 0
		if CostMoney(sceneId, selfId, 0, 5000) == -1 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, "\t现银或银卡不足，不能接受此任务");
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)	
			Msg2Player(sceneId,selfId,"现银或银卡不足，不能接受此任务",8,2)				
			return
		end
	end
	

	--背包中加物品
	x300678_DelMissionItems(sceneId, selfId)
	if x300678_AddMissionItems(sceneId, selfId) == 0 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "\t背包空间不足，不能接受任务！你的背包至少需要4个空格。");
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)	
		Msg2Player(sceneId,selfId,"背包空间不足，不能接受任务！你的背包至少需要4个空格。",8,2)	
		
		AddMoney(sceneId,selfId,subsillertype,5000)
		
		return
	end
	
	AddQuestNM(sceneId, selfId, x300678_g_MissionId);
	--SendSpecificImpactToUnit( sceneId, selfId, selfId, selfId, x300678_g_MoneyBuff, 0)
	
	local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId)
	SetQuestParam(sceneId, selfId, misIndex, 0, 0)
	
	local str = format("您领取了任务：%s", x300678_g_MissionName)
	Msg2Player(sceneId,selfId,"你缴纳了5两银子的押金。",8,2)
	Msg2Player(sceneId,selfId,str,8,2)	
	BeginQuestEvent(sceneId);
	AddQuestText(sceneId, str);
	EndQuestEvent();
	DispatchQuestTips(sceneId, selfId);	
	
	SetQuestByIndex( sceneId, selfId, misIndex, 0, 0)
	SetQuestByIndex( sceneId, selfId, misIndex, 6, 0)
	SetQuestByIndex( sceneId, selfId, misIndex, 7, 0)
	x300678_ProcQuestLogRefresh(sceneId, selfId, MissionId)
	
	--写Log
	GamePlayScriptLog(sceneId, selfId, 1321)

end

--完成任务
--返回1代表成功，0代表交任务失败
function x300678_ProcQuestSubmit( sceneId, selfId, targetId, selectId, MissionId )
    
	if GetGameOpenById(x300678_gameopenid)<=0 then
		return
	end	
	
	if GetGuildID(sceneId, selfId) == -1 then
		return
	end
	
	local GuildLevel = GetGuildSimpleData(GetGuildID( sceneId, selfId ))
	if GuildLevel < 3 then 
		return 
	end		
	
	if MissionId == nil or MissionId < 0 then
        return 0
    end

	if IsHaveQuestNM( sceneId, selfId, MissionId) <= 0 then	-- 如果没这个任务直接退出
		return 0
	end
	
	if IsQuestHaveDoneNM( sceneId, selfId, MissionId ) > 0 then --任务已经完成
		return 0
	end
	
	if HaveItem(sceneId, selfId,x300678_Item_Money) <= 0 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "帮会银票不存在，不能交任务！");
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)	
		Msg2Player(sceneId,selfId,"帮会银票不存在，不能交任务！",8,2)			
		return 0		
	end
	
	if GetGuildID(sceneId, selfId) == -1 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"你已经不在帮会中，请加入帮会后再继续本任务！")
		EndQuestEvent()
		DispatchQuestDemandInfo(sceneId, selfId, targetId, x300678_g_ScriptId, MissionId,0);
		return 0
	end		

	if x300678_IsMissionCompleted(sceneId, selfId, MissionId) ~= 1 then 
		return 0
	end
	
	GetGuildQuestData(sceneId, selfId, GD_GUILD_INDEX_GET_MONEY_COUNT, x300678_g_ScriptId, MissionId, "OnMissionComplete" );
	
end

-- 任务完成
function x300678_OnMissionComplete(sceneId, selfId,MissionData,MissionId,targetId)


	if GetGameOpenById(x300678_gameopenid)<=0 then
		return
	end	
	
	if GetGuildID(sceneId, selfId) == -1 then
		return
	end
	
	local GuildLevel = GetGuildSimpleData(GetGuildID( sceneId, selfId ))
	if GuildLevel < 3 then 
		return 
	end		
	
	if MissionId == nil or MissionId < 0 then
        return 0
    end

	if IsHaveQuestNM( sceneId, selfId, MissionId) <= 0 then	-- 如果没这个任务直接退出
		return 0
	end
	
	if IsQuestHaveDoneNM( sceneId, selfId, MissionId ) > 0 then --任务已经完成
		return 0
	end
	
	if HaveItem(sceneId, selfId,x300678_Item_Money) <= 0 then	
		return 0		
	end
	
	if GetGuildID(sceneId, selfId) == -1 then
		return 0
	end		

	if x300678_IsMissionCompleted(sceneId, selfId, MissionId) ~= 1 then 
		return 0
	end


	if MissionData >= x300678_Max_Count-1 then
		local message = "任务次数已满"
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, message);
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId)
		Msg2Player(sceneId, selfId, message, 8, 2)
		return
	end

	-- 任务完成
	DelQuestNM( sceneId, selfId, MissionId)
	--CancelSpecificImpact( sceneId, selfId,  x300678_g_MoneyBuff)

    -- 增加活跃度
    local id = GetGuildID( sceneId, selfId)
    if id ~= -1 then
        AddGuildActivity( sceneId, selfId, GetGuildCacheFreeParam( id, GD_GUILD_ACTIVITY_PARAM6) )
    end
	
	-- 删除相关任务物品
	x300678_DelMissionItems(sceneId, selfId)
	
	local message = format("您完成了任务：%s", x300678_g_MissionName);
	BeginQuestEvent(sceneId);
	AddQuestText(sceneId, message);
	EndQuestEvent();
	DispatchQuestTips(sceneId, selfId);
	Msg2Player(sceneId, selfId, message, 8, 2);
	
	local guildid = GetGuildID(sceneId,selfId);
	SetGuildQuestData(sceneId, guildid, GD_GUILD_INDEX_GET_MONEY_COUNT, 1, 1 );	
	
	x300678_GiveBonus(sceneId,selfId,99 - MissionData)
	
	--写Log
	GamePlayScriptLog(sceneId, selfId, 1322)
end

--给奖励
function x300678_GiveBonus(sceneId,selfId,count)
	
	-- 个人奖励，经验
	local level = GetLevel(sceneId,selfId)
	local nExp = level*3000
	local money =5000
	local moneymes = "返还跑商押金5两银卡。"
	local name =GetName(sceneId,selfId)
	--local times = 
	local banghuimes = format("#G玩家#Y%s#G成功的完成了#Y【帮会】帮会跑商#G任务，帮会金钱增加了#Y20#G两。帮会本日跑商任务剩余#Y%s#G次。",name,count-1)
	local guildid = GetGuildID(sceneId, selfId)
	local maxlevel = GetTopListInfo_MaxLevel(GetWorldID(sceneId, selfId))
	local explevel = maxlevel - 10
	--个人经验
	AddExp(sceneId,selfId,nExp)
	--返还接任务时的金钱
	AddMoney( sceneId, selfId, 1, money )
	Msg2Player(sceneId, selfId, moneymes, 8, 2);
	Msg2Player(sceneId, selfId,"你获得了#R经验"..nExp.."点#cffcf00的奖励。",8,2)
	-- 帮会奖励，帮会金钱,帮会公告
	AddGuildMoney(sceneId,selfId,20000)
	--Msg2Player(sceneId, selfId, banghuimes, 6, 2);
	LuaAllScenceM2Guild(sceneId, banghuimes, guildid, 0,1)
	
	
	
end

function x300678_ProcQuestAttach( sceneId, selfId, npcId, npcGuid,misIndex, MissionId )
	if IsHaveQuestNM( sceneId, selfId, MissionId) == 0 then	-- 如果没有这个任务
		return
	end
end

function x300678_ProcQuestAbandon( sceneId, selfId, MissionId )
	
	DelQuestNM( sceneId, selfId, MissionId)
	x300678_DelMissionItems(sceneId, selfId)
	
	local message = format("您放弃了任务：%s", x300678_g_MissionName);
	BeginQuestEvent(sceneId);
	AddQuestText(sceneId, message);
	EndQuestEvent();
	DispatchQuestTips(sceneId, selfId);
	Msg2Player(sceneId, selfId, message, 8, 2);
	
end

function x300678_ProcQuestLogRefresh( sceneId, selfId, MissionId)

	local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId)
	local nMoney = GetQuestParam( sceneId, selfId, misIndex, x300678_g_SubmitParamIndex)
	local strTarget = "  在@npc_129181，@npc_129182，@npc_129180处，出售帮会货物赚取足够金钱("..nMoney.."/"..x300678_g_SubmitMoney..")";
	
	if GetQuestParam( sceneId, selfId, misIndex, 6) == 1 then	--任务失败
		strTarget = "  任务失败，请重新领取"
	end
	
	BeginQuestEvent( sceneId)
		local level = GetLevel(sceneId,selfId)
		local nExp = level*3000
		local GuildMoney =20
		local maxlevel = GetTopListInfo_MaxLevel(GetWorldID(sceneId, selfId))
		local explevel = maxlevel - 10
	
	AddQuestLogCustomText( sceneId,
							"",                             -- 标题
							x300678_g_MissionName,          -- 任务名字
							strTarget,
							"",
                             -- 任务NPC
							"\t找到城东商人，城西商人，昆仑猎场商人及王城游商，将身上的帮会货物出售给他们，一定要赚取足够的金钱才能完成任务。#Y\n奖励内容：\n#W经验值："..nExp.."\n#W帮会金钱：20两",
							"\t帮会的发展离不开帮会金钱。\n\t我这里有一些帮会的物资待售，听说城东商人@npc_129181，城西商人@npc_129182，昆仑猎场商人@npc_129180正在收购它们。\n\t你带着这些物资，卖给商人们,为帮会赚取足够的金钱吧。\n\t值得注意的是，王城内有位神秘的商人，名叫@npc_129183，他常常会以#G高价收购所有货物#W。\n\t帮会货物共有以下种类：#G波斯金鞍，大宛马铠，高丽山参，大理灵芝，南洋珍珠和琉球珊瑚。",
							"\t神秘商人会在王城的广场区域游走，要找到王城游商可不是个容易的事。")
		AddQuestText(sceneId,"#Y奖励内容：")
			AddQuestText(sceneId,"#W经验值："..nExp)
		AddQuestText(sceneId,"#W帮会金钱：20两")
	EndQuestEvent()	
	DispatchQuestLogUpdate( sceneId, selfId, MissionId);
	
	-- 任务完成
	if x300678_IsMissionCompleted(sceneId, selfId, MissionId) == 1 then
		SetQuestByIndex( sceneId, selfId, misIndex, 7, 1)
	end
	
end

-- 判断钱够不够了
function x300678_IsMissionCompleted(sceneId, selfId, MissionId)

	local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId)
	local nMoney = GetQuestParam( sceneId, selfId, misIndex, x300678_g_SubmitParamIndex)
	if nMoney > x300678_g_SubmitMoney then
		return 1
	else
		return 0
	end

end

-- 添加任务物品
function x300678_AddMissionItems(sceneId, selfId)
	local item1, item2, item3
	local nTotalNum = getn(x300678_Item_Goods)
	item1 = x300678_Item_Goods[ random(1,nTotalNum) ]
	item2 = x300678_Item_Goods[ random(1,nTotalNum) ]
	while item2 == item1 do
		item2 = x300678_Item_Goods[ random(1,nTotalNum) ]
	end
	item3 = x300678_Item_Goods[ random(1,nTotalNum) ]
	while item3==item2 or item3==item1 do
		item3 = x300678_Item_Goods[ random(1,nTotalNum) ]
	end
	
	BeginAddItem(sceneId)
	AddItem(sceneId, item1, 1)
	AddItem(sceneId, item2, 1)
	AddItem(sceneId, item3, 1)
	AddItem(sceneId, x300678_Item_Money, 1)
    local ret = EndAddItem(sceneId,selfId)
	if ret > 0 then
		AddItemListToPlayer(sceneId,selfId)
	end
	return ret
end

-- 删除任务物品
function x300678_DelMissionItems(sceneId, selfId)
	local i = 0
	for i, item in x300678_Item_Goods do
		if HaveItem(sceneId,selfId,item)>0 then
			DelItem(sceneId,selfId,item,1)
		end
	end
	
	if HaveItem(sceneId,selfId,x300678_Item_Money) > 0 then
		DelItem(sceneId,selfId,x300678_Item_Money,1)
	end
end

-- 离开帮会
function x300678_OnLeaveGuild(sceneId, selfId, MissionId)

	DelQuestNM( sceneId, selfId, MissionId)
	x300678_DelMissionItems(sceneId, selfId)
	
	local message = format("您已经不在帮会中了，删除了任务：%s", x300678_g_MissionName);
	BeginQuestEvent(sceneId);
	AddQuestText(sceneId, message);
	EndQuestEvent();
	DispatchQuestTips(sceneId, selfId);
	Msg2Player(sceneId, selfId, message, 8, 2);	
	
end