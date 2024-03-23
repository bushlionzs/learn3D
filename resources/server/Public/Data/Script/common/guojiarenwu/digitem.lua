--内政挖掘任务 add by 齐亮（090112）

--MisDescBegin

x300518_g_ScriptId = 300518
-- 任务名称
x300518_g_MissionName = "【个人】内政任务"
-- 
x300518_g_MissionHelp   = "\t用@item_12030020#W去#aB#h00CCFF{goto_%d,%d,%d}(%d，%d)#aE#W探索一番，看看有没有#G%s#W"
-- 任务目标
x300518_g_MissionTarget = "  到#aB#h00CCFF{goto_%d,%d,%d}(%d，%d)#aE#W附近使用@item_12030020#W挖掘(%d/1)"
-- 任务信息
x300518_g_MissionInfo   = "\t最近我观察圣山之上灵气异常，其地脉更是有仙龙为照，山中定然有很多鲜为人知的化石材料，请你首先到@npc_138502那里购买一个铁铲，用铁铲去#aB#h00CCFF{goto_%d,%d,%d}(%d，%d)#aE附近探索一番，看看有没有#G%s#W。"
x300518_g_MissionInfo_High   = "\t最近我观察护城河灵气异常，其水源更是有仙龙为照，河畔定然有很多鲜为人知的化石材料，请你首先到@npc_138502那里购买一个铁铲，用铁铲去#aB#h00CCFF{goto_%d,%d,%d}(%d，%d)#aE附近探索一番，看看有没有#G%s#W。"
-- 任务未完成时NPC对话内容
x300518_g_MissionContinue   = "\t你还没有找到#G%s#W呢。"

--MisDescEnd
x300518_LevelToCapital		= 300		--大都任务的开始等级

x300518_OneRoundCount	= 10
x300518_HighBonusCircleCount = 10
-- 
x300518_g_DigNothing    = "这里什么也没有，请在灵气旺盛的(%d，%d)附近使用。"

x300518_g_DigMissionID              = 6470
x300518_g_DigMissionID_End          = 6479

x300518_CountrySceneList	= {50, 150, 250, 350}
x300518_CapitalSceneId		= 0

--mission parameters index
x300518_UserLevelAccept		= 1
x300518_PositionGroup		= 2
x300518_ItemId			= 3
-- 挖掘目标坐标库
x300518_g_CoordinateLib     = 
{
                                { posX = 422, posZ = 50  }, 
                                { posX = 378, posZ = 81  }, 
                                { posX = 428, posZ = 30 }, 
                                { posX = 411, posZ = 32 }, 
                                { posX = 425, posZ = 245 }, 
}

x300518_g_CoordinateLib_Cap     = 
{
                                { posX = 166, posZ = 68  }, 
                                { posX = 158, posZ = 109  }, 
                                { posX = 363, posZ = 271 }, 
                                { posX = 373, posZ = 371 }, 
                                { posX = 419, posZ = 436 }, 
}
-- 挖掘目标
x300518_g_DigTarget         =
{
                                { mission = 6470, id = 13013000, name = "仙灵玉石" }, 
                                { mission = 6471, id = 13013001, name = "仙灵光石" }, 
                                { mission = 6472, id = 13013002, name = "仙灵彩石" }, 
                                { mission = 6473, id = 13013003, name = "仙灵暗石" }, 
                                { mission = 6474, id = 13013004, name = "仙灵玄石" }, 
                                { mission = 6475, id = 13013000, name = "仙灵玉石" }, 
                                { mission = 6476, id = 13013001, name = "仙灵光石" }, 
                                { mission = 6477, id = 13013002, name = "仙灵彩石" }, 
                                { mission = 6478, id = 13013003, name = "仙灵暗石" }, 
                                { mission = 6479, id = 13013004, name = "仙灵玄石" }, 
}                                                   


-- 有效挖掘“半径”，实际是一个正方块
x300518_g_Radius    = 4

function x300518_ProcAcceptCheck( sceneId, selfId, targetId, MissionId)
    return 1
end

function x300518_ProcAccept( sceneId, selfId)
end

-- 显示任务未完成时NPC的对话信息
function x300518_ShowMissionContinueInfo( sceneId, selfId, targetId, MissionId)
    BeginQuestEvent( sceneId)
        -- 任务名称
        AddQuestText( sceneId, "#Y"..x300518_g_MissionName)
        local itemid, itemname = x300518_GetDigItem(MissionId)
       AddQuestText( sceneId, format( x300518_g_MissionContinue, itemname) )
    EndQuestEvent()
    DispatchQuestEventList( sceneId, selfId, targetId)
end

-- 挖掘事件触发此函数调用，参见铁铲道具使用脚本common_cangbaotu_item.lua。返回0表示没有接任务挖掘
function x300518_OnDigbyShovel( sceneId, selfId )

	--判断当前任务是不是挖掘任务
	local MissionId = x300518_GetRandMissionId(sceneId, selfId)
	if (MissionId < x300518_g_DigMissionID or MissionId > x300518_g_DigMissionID_End) then
		return 0
	end

	-- 判断有没有任务及是否完成
	if IsHaveQuestNM( sceneId, selfId, MissionId) <= 0 then
		return 0
	end

	local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId)

	local isFinish = GetQuestParam( sceneId, selfId, misIndex, 0 )
	if isFinish ~= 0 then
		return 0
	end

        -- 得到挖掘目标和坐标
	local userlevelaccept = GetQuestParam( sceneId, selfId, misIndex, x300518_UserLevelAccept )
	local positiongroup = GetQuestParam( sceneId, selfId, misIndex, x300518_PositionGroup )

	local posX,posZ,destSceneId = x300518_GetDigPosition(sceneId, selfId, userlevelaccept, positiongroup)
	if (destSceneId ~= sceneId) then	--所在场景不符合
		return 0
	end
	local itemid,itemname =x300518_GetDigItem(MissionId)
	
	-- 获得当前坐标
        local x, z = GetWorldPos( sceneId, selfId)
	
        if abs( x - posX) > x300518_g_Radius or abs( z - posZ) > x300518_g_Radius then
		--挖掘地点不对
            BeginQuestEvent( sceneId)
                AddQuestText( sceneId, format( x300518_g_DigNothing, posX, posZ) )
            EndQuestEvent()
            DispatchQuestTips( sceneId, selfId)
            Msg2Player( sceneId, selfId, format( x300518_g_DigNothing, posX, posZ), 8, 2)
            return 0
        end

        -- 挖到物品，添加到背包
        BeginAddItem( sceneId)
		AddItem( sceneId, itemid, 1)
        local result = EndAddItem( sceneId, selfId)
        if result == 0 then
            BeginQuestEvent( sceneId)
		AddQuestText( sceneId, "背包已满，无法放入挖到的物品！" )
            EndQuestEvent( sceneId)
            DispatchQuestTips( sceneId, selfId)
            Msg2Player( sceneId, selfId, "背包已满，无法放入挖到的物品！", 8, 2)
            return 1
        end
        BeginQuestEvent( sceneId)
		AddQuestText( sceneId, "你得到了"..itemname.."。" )
		AddItemListToPlayer( sceneId, selfId)
		SetQuestByIndex( sceneId, selfId, misIndex, x300518_ItemId, itemid) -- 存下得到的任务物品
        EndQuestEvent( sceneId)

        DispatchQuestTips( sceneId, selfId)
        Msg2Player( sceneId, selfId, "你得到了"..itemname.."。", 8, 2)
        
	-- 设置任务完成标记
        SetQuestByIndex( sceneId, selfId, misIndex, 0, 1)
        SetQuestByIndex( sceneId, selfId, misIndex, 7, 1)
        Msg2Player(sceneId, selfId, "任务已经完成，快点回去汇报吧！", 8, 3)
	-- 更新Q面板
        x300518_ProcQuestLogRefresh( sceneId, selfId, MissionId, misIndex)

        -- 消耗铁铲可用次数
        CallScriptFunction( 300331, "LogicDeplete", sceneId, selfId)

	return 1
end

-- 提交任务，返回0表示失败，返回1成功
function x300518_ProcQuestSubmit( sceneId, selfId, targetId, selectId, MissionId, farScriptId, constMD_Rand, retMissionId)
    return 1
end

-- 显示任务信息
function x300518_ShowMissionInfo( sceneId, selfId, targetId, MissionId)

	local userlevel = GetLevel(sceneId, selfId);
	
    BeginQuestEvent( sceneId)
        -- 任务名称
        AddQuestText( sceneId, "#Y"..x300518_g_MissionName)
        -- 随机获取挖掘坐标和目标
	local randgroup,posX,posZ,destSceneId
	if (userlevel < x300518_LevelToCapital) then
		randgroup = random( 1, getn( x300518_g_CoordinateLib) )
		posX = x300518_g_CoordinateLib[ randgroup].posX
		posZ = x300518_g_CoordinateLib[ randgroup].posZ
		destSceneId = x300518_CountrySceneList[GetCurCountry(sceneId, selfId)+1];
	else
		randgroup = random( 1, getn( x300518_g_CoordinateLib_Cap) )
		posX = x300518_g_CoordinateLib_Cap[ randgroup].posX
		posZ = x300518_g_CoordinateLib_Cap[ randgroup].posZ
		destSceneId = x300518_CapitalSceneId;
	end

        -- 因为任务已经被添加到MissionList，所以可把这些参数写入Mission Parameter
        local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId)
        SetQuestByIndex( sceneId, selfId, misIndex, 0, 0) -- 完成标记
        SetQuestByIndex( sceneId, selfId, misIndex, x300518_UserLevelAccept, userlevel) -- 接任务时的等级
        SetQuestByIndex( sceneId, selfId, misIndex, x300518_PositionGroup, randgroup) -- 坐标组号
	SetQuestByIndex( sceneId, selfId, misIndex, x300518_ItemId, -1)
        -- 任务描述
        AddQuestText( sceneId, "#Y任务目标：" )
	local itemid, itemName = x300518_GetDigItem(MissionId)

	local strMisInfo
	if (destSceneId == x300518_CapitalSceneId ) then
		strMisInfo = x300518_g_MissionInfo_High
	else
		strMisInfo = x300518_g_MissionInfo
	end

        AddQuestText( sceneId, format( strMisInfo, destSceneId, posX, posZ, posX, posZ, itemName) )

    EndQuestEvent()
    DispatchQuestInfoNM( sceneId, selfId, targetId, x300518_g_ScriptId, MissionId, 1)

--    DispatchQuestEventList( sceneId, selfId, targetId)
end

--接受任务
function x300518_AutoAccept( sceneId, selfId, targetId, MissionId)
	return AddQuest( sceneId, selfId, MissionId, x300518_g_ScriptId, 0, 0, 0, 1)
end

function x300518_AfterAccept(sceneId, selfId, targetId, MissionId, misIndex)
	--刷新Q面板
	x300518_ProcQuestLogRefresh(sceneId, selfId, MissionId, misIndex)
end

function x300518_ProcQuestAttach( sceneId, selfId, targetId, npcGuid, misIndex, MissionId)

	MissionId = x300518_GetRandMissionId(sceneId, selfId)
	if IsHaveQuestNM( sceneId, selfId, MissionId) == 0 then
		return 0
	end

	local misIndex = GetQuestIndexByID(sceneId, selfId, MissionId);

	local submitguid = GetQuestSubmitNPCGUIDNM( sceneId, selfId, misIndex )
	--如果是任务提交人，显示选项
	if submitguid ~= -1 and submitguid == npcGuid then	
		local state = GetQuestStateNM(sceneId, selfId, npcGuid, MissionId);
		return AddQuestTextNM(sceneId, selfId, npcGuid, MissionId, state, -1);
	end

    return 1
end

function x300518_ProcQuestLogRefresh( sceneId, selfId, MissionId, misIndex)

	if (misIndex == nil) then
		misIndex = GetQuestIndexByID(sceneId, selfId, MissionId);
	end
	local finished = GetQuestParam( sceneId, selfId, misIndex, 0)
	local userlevelaccept = GetQuestParam( sceneId, selfId, misIndex, x300518_UserLevelAccept )
	local positiongroup = GetQuestParam( sceneId, selfId, misIndex, x300518_PositionGroup )
	local posX,posZ,destSceneId = x300518_GetDigPosition(sceneId, selfId, userlevelaccept, positiongroup)
	local itemid,itemname =x300518_GetDigItem(MissionId)
	local strName;
	strName = x300518_g_MissionName;
	local circle = x300518_GetMD(sceneId, selfId, MD_GUOJIARENWU_CIRCLE)
	if (circle >= x300518_OneRoundCount) then
		circle = 1
	else
		circle = circle + 1
	end

	strName = strName.."("..circle;
	strName = strName.."/"..x300518_OneRoundCount;
	strName = strName..")";

	local reply_npcid = GetQuestSubmitNPCGUIDNM( sceneId, selfId, misIndex );

	BeginQuestEvent(sceneId)
	
	local strMisInfo
	if (destSceneId == x300518_CapitalSceneId ) then
		strMisInfo = x300518_g_MissionInfo_High
	else
		strMisInfo = x300518_g_MissionInfo
	end
        AddQuestLogCustomText( sceneId,
                                "",                             -- 标题
                                strName,          -- 任务名字
                                format( x300518_g_MissionTarget, destSceneId, posX, posZ, posX, posZ, finished),
                                "@npc_"..reply_npcid,             --任务NPC
                                format( x300518_g_MissionHelp, destSceneId, posX, posZ, posX, posZ, itemname),
                                format( strMisInfo, destSceneId, posX, posZ, posX, posZ, itemname),
                                "@item_12030020在@npc_138502处有售，请先去找他吧！" )

	--任务奖励
	local curlevel = GetLevel(sceneId, selfId)
	local exp = x300518_GetExpAward ( sceneId, selfId, curlevel );
	local money,shengw = x300518_GetMoneyAward ( sceneId, selfId, curlevel );
	if(exp > 0) then
		AddQuestExpBonus(sceneId, exp)
	end
	if(money > 0) then
		AddQuestMoneyBonus2(sceneId, money)
	end
	if(shengw > 0) then
		AddQuestMoneyBonus5(sceneId, shengw)
	end
	EndQuestEvent()
	DispatchQuestLogUpdate( sceneId, selfId, MissionId);
end

-- 放弃任务处理
function x300518_ProcQuestAbandon(sceneId, selfId, MissionId)
	MissionId = x300518_GetRandMissionId(sceneId, selfId)
	if (IsHaveQuestNM(sceneId, selfId, MissionId) == 0) then
		return
	end
	local misIndex = GetQuestIndexByID(sceneId, selfId, MissionId);
	local saveditemid = GetQuestParam( sceneId, selfId, misIndex, x300518_ItemId )
	if saveditemid >= 0 then
		DelItem( sceneId, selfId, saveditemid, 1)
	end

	CallScriptFunction( 300501, "ProcQuestAbandon", sceneId, selfId, MissionId)
end

function x300518_GetRandMissionId(sceneId, selfId)
	return  x300518_GetMD(sceneId, selfId, MD_GUOJIARENWU_RANDMISSIONID)
end

function x300518_SetMD(sceneId, selfId, MDNAME, value)
	SetQuestData(sceneId, selfId, MDNAME[1], MDNAME[2], MDNAME[3], value);
end

function x300518_GetMD(sceneId, selfId, MDNAME)

	return GetQuestData(sceneId, selfId, MDNAME[1], MDNAME[2], MDNAME[3])
end

--检查日期有没有变化，并重置高奖次数，并保存新的日期
function x300518_CheckDayChanged(sceneId, selfId)
	local lastDay = x300518_GetMD(sceneId, selfId, MD_GUOJIARENWU_LASTDAY)
	local today = GetDayOfYear()
	if lastDay ~= today then	--日期变化
		x300518_SetMD(sceneId, selfId, MD_GUOJIARENWU_LASTDAY, today)
		x300518_SetMD(sceneId, selfId, MD_GUOJIARENWU_HIGH, 0)
	end
end

--经验奖励
function x300518_GetExpAward(sceneId, selfId, startlevel)

	x300518_CheckDayChanged(sceneId, selfId)
	local circle = x300518_GetMD(sceneId, selfId, MD_GUOJIARENWU_CIRCLE)
	local highcircle = x300518_GetMD(sceneId, selfId, MD_GUOJIARENWU_HIGH)
	
	circle = circle + 1
	if (circle > x300518_OneRoundCount) then
		circle = 1
	end

	highcircle = highcircle + 1

	local exp_rate
	if GetLevel(sceneId, selfId) >= 60 then
		exp_rate = 3650
	else
		exp_rate = 2800
	end

	local BonusExp = startlevel * exp_rate * (circle * 2 - 1) / 200
	if (highcircle <= x300518_HighBonusCircleCount) then
		BonusExp = BonusExp * 5
	end
    -- 环数减半，所以经验翻倍
    BonusExp = BonusExp * 2
	return BonusExp;

end

--金钱奖励
function x300518_GetMoneyAward(sceneId, selfId, startlevel)

	x300518_CheckDayChanged(sceneId, selfId)
	local circle = x300518_GetMD(sceneId, selfId, MD_GUOJIARENWU_CIRCLE)
	local highcircle = x300518_GetMD(sceneId, selfId, MD_GUOJIARENWU_HIGH)

	circle = circle + 1
	if (circle > x300518_OneRoundCount) then
		circle = 1
	end

	highcircle = highcircle + 1

	local BonusMoney = startlevel
	local shengw = 5
	if (highcircle <= x300518_HighBonusCircleCount) then
		BonusMoney = BonusMoney * 5
		shengw = 25
	end
	return BonusMoney, shengw;
end

function x300518_GetDigPosition(sceneId, selfId, userlevelaccept, positiongroup)

	local posX,posZ,destSceneId
	if (userlevelaccept < x300518_LevelToCapital) then
		if (positiongroup == nil or positiongroup < 1 or positiongroup > getn(x300518_g_CoordinateLib)) then
			return -1,-1,-1
		end
		posX = x300518_g_CoordinateLib[positiongroup].posX;
		posZ = x300518_g_CoordinateLib[positiongroup].posZ;
		destSceneId = x300518_CountrySceneList[GetCurCountry(sceneId, selfId)+1];
	else
		if (positiongroup == nil or positiongroup < 1 or positiongroup > getn(x300518_g_CoordinateLib_Cap)) then
			return -1,-1,-1
		end
		posX = x300518_g_CoordinateLib_Cap[positiongroup].posX;
		posZ = x300518_g_CoordinateLib_Cap[positiongroup].posZ;
		destSceneId = 0
	end

	return posX, posZ, destSceneId
end

function x300518_GetDigItem(MissionId)

	local itemid = -1
	local itemname = ""
	for i, item in x300518_g_DigTarget do
		if item.mission == MissionId then
			itemname = item.name
			itemid = item.id
			break
		end
	end

	return itemid,itemname
end