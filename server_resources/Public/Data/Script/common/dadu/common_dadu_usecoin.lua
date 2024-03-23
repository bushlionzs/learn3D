-- 
x310162_g_scriptId 		= 310162
x310162_g_MissionId     = 9320
x310163_g_DengmiMissionId	= 9315			--任务ID
x310162_g_TianfuItems				= {11010100,11010101,11010102}

function x310162_Yizhesanyou_Reward( sceneId, selfId)
    -- 额外奖励
    local rewardExt = 0
    local itemExt = 0

    SetQuestData( sceneId, selfId, MD_YIZHESANYOU_DATE[ 1], MD_YIZHESANYOU_DATE[ 2], MD_YIZHESANYOU_DATE[ 3], GetDayOfYear() )

    local playerLevel = GetLevel( sceneId, selfId)
	local xp = playerLevel * 7000
    if xp > 0 then
        AddExp( sceneId, selfId, xp)
        Msg2Player( sceneId, selfId, format( "获得#R经验%d点#cffcf00的奖励", xp).."。", 8, 2)
        Msg2Player( sceneId, selfId, format( "获得#R经验%d点#cffcf00的奖励", xp), 8, 3)
    end
    
    SetShengWang( sceneId, selfId, GetShengWang( sceneId, selfId) + 150)
    Msg2Player( sceneId, selfId, format( "获得#R%d点声望#cffcf00的奖励", 150).."。", 8, 2)
    Msg2Player( sceneId, selfId, format( "获得#R%d点声望#cffcf00的奖励", 150), 8, 3)
    -- 更新Daycount
    local count = GetQuestData( sceneId, selfId, MD_YIZHESANYOU_COUNTER[ 1], MD_YIZHESANYOU_COUNTER[ 2], MD_YIZHESANYOU_COUNTER[ 3] )
    SetQuestData( sceneId, selfId, MD_YIZHESANYOU_COUNTER[ 1], MD_YIZHESANYOU_COUNTER[ 2], MD_YIZHESANYOU_COUNTER[ 3], count + 1)
    local value = random( 1, 100)
    if value > 20 and value <= 40 then
        BeginAddItem( sceneId)
        AddItem( sceneId, 12030107, 1)
        if EndAddItem( sceneId, selfId) <= 0 then
            Msg2Player( sceneId, selfId, "你完成了【德】益者三友。由于你的背包已满，无法获得藏宝图奖励。", 8, 2)
        else
            AddItemListToPlayer( sceneId, selfId)
        end
    end
    x310162_AddTianfuItem( sceneId, selfId)
    CallScriptFunction( 256224, "Finishyizhe", sceneId, selfId)
    Msg2Player( sceneId, selfId, format( "你完成了【德】益者三友"), 8, 3)
end

function x310162_Dengmi_Reward( sceneId, selfId)

	local nCurDay = GetDayOfYear()
	SetQuestData(sceneId,selfId,MD_DENGMI_DATE[1],MD_DENGMI_DATE[2],MD_DENGMI_DATE[3],nCurDay)
	
	local level = GetLevel(sceneId,selfId)
	local name = GetName(sceneId,selfId)

	if name == nil then
		name = "ErrorName"
	end
	
	
	
	--给经验
	local score = GetQuestData(sceneId,selfId,MD_DENGMI_SCORE[1],MD_DENGMI_SCORE[2],MD_DENGMI_SCORE[3])
	local bonusExp = level*7000
	AddExp(sceneId,selfId,bonusExp)

	local msg = format("您获得了#R%d点经验值#cffcf00的奖励",bonusExp)

	LuaScenceM2Player(sceneId, selfId, msg, name , 2,1)
    LuaScenceM2Player(sceneId, selfId, msg, name , 3,1)
--	if level < 70 then
--		local bonusExp = level * 500 * 10
--		AddExp(sceneId,selfId,bonusExp)
--
--		local msg = format("您获得了%d点经验值的奖励",bonusExp)
--
--		LuaScenceM2Player(sceneId, selfId, msg, name , 2,1)
--        LuaScenceM2Player(sceneId, selfId, msg, name , 3,1)
--	else
--		local bonusExp = level * 650 * 10
--		AddExp(sceneId,selfId,bonusExp)
--
--		local msg = format("您获得了%d点经验值的奖励",bonusExp)
--
--		LuaScenceM2Player(sceneId, selfId, msg, name , 2,1)
--        LuaScenceM2Player(sceneId, selfId, msg, name , 3,1)
--    end
--
    local bonusMoney = level*300
    local buff 	=	9011
    local buff1 =	9013
    local buff2 =	9012
    if IsHaveSpecificImpact( sceneId, selfId, buff) == 1 or IsHaveSpecificImpact( sceneId, selfId, buff1) == 1  or IsHaveSpecificImpact( sceneId, selfId, buff2) == 1 then
        AddMoney( sceneId, selfId, 0, bonusMoney, x310162_g_scriptId)
    else
        AddMoney( sceneId, selfId, 1, bonusMoney, x310162_g_scriptId)
    end

    BeginAddItem( sceneId)
    AddItem( sceneId, 12030107, 2)
    local res = EndAddItem( sceneId, selfId)
    if res > 0 then
        AddItemListToPlayer( sceneId, selfId)
    else
        LuaScenceM2Player( sceneId, selfId, "#cffcf00物品栏已满，无法得到奖励物品！", name , 2, 1)
        LuaScenceM2Player( sceneId, selfId, "#cffcf00物品栏已满，无法得到奖励物品！", name , 3, 1)
    end
	x310162_AddTianfuItem( sceneId, selfId)
    SetQuestData( sceneId, selfId, MD_QUEST_DENGMI_COUNT[1], MD_QUEST_DENGMI_COUNT[2], MD_QUEST_DENGMI_COUNT[3], 10)
    SetQuestData( sceneId, selfId, MD_QUEST_DENGMI_DATE[1], MD_QUEST_DENGMI_DATE[2], MD_QUEST_DENGMI_DATE[3], GetDayOfYear() )
end

function x310162_Tiesan_Reward( sceneId, selfId)
    local level = GetLevel( sceneId, selfId)
    local award1 = floor(100*70*level)
    local award2 = floor(100*70*level)
    local award = 0
    if GetLevel(sceneId, selfId) >=40 and GetLevel(sceneId, selfId) < 70 then
        award = award1;
    elseif GetLevel(sceneId, selfId) >=70 then
        award = award2;
    end
    AddExp(sceneId, selfId, award)
    Msg2Player( sceneId, selfId, format("#Y获得#R经验%d#Y的奖励", award), 8, 3)
    Msg2Player( sceneId, selfId, format("#Y获得#R经验%d#Y的奖励。", award), 8, 2)

    local nShengWang = GetShengWang( sceneId, selfId)
    nShengWang = nShengWang + 200
    SetShengWang( sceneId, selfId, nShengWang )
    message = format("获得声望%d的奖励。", 200)
    BeginQuestEvent(sceneId);
        AddQuestText(sceneId, message);
    EndQuestEvent();
    DispatchQuestTips(sceneId, selfId);
    Msg2Player(sceneId,selfId,message,4,2)
    local day = GetDayOfYear()
    SetQuestData(sceneId, selfId, MD_TIEREN_ACCEPTTIME_DAY[1], MD_TIEREN_ACCEPTTIME_DAY[2], MD_TIEREN_ACCEPTTIME_DAY[3], day)
    SetQuestData(sceneId, selfId, MD_TIEREN_COMMITTIME[1], MD_TIEREN_COMMITTIME[2], MD_TIEREN_COMMITTIME[3], 1)

	x310162_AddTianfuItem( sceneId, selfId)
    -- 添加一张藏宝图
    BeginAddItem( sceneId)
    AddItem( sceneId, 12030107, 1)
    if EndAddItem( sceneId, selfId) <= 0 then
        Msg2Player( sceneId, selfId, "背包已满，无法获得藏宝图奖励。", 8, 2)
    else
        AddItemListToPlayer( sceneId, selfId)
        Msg2Player( sceneId, selfId, "获得一张藏宝图的奖励。", 8, 2)
    end
end

function x310162_Yizhe_Check( sceneId, selfId)
    local curTime = GetMinOfDay()
    if curTime < 1170 then
        Msg2Player( sceneId, selfId, "益者三友活动尚未开始，请在嘉年华活动时间19：30——24：00内使用", 8, 3)
        return 0
    end

    -- 检查角色身上是不是有这个任务
    if IsHaveQuestNM( sceneId, selfId, 9320) > 0 then
        Msg2Player( sceneId, selfId, "你已经接受这个任务了，快去完成吧。", 8, 3)
        return 0
    end

	local nCurDay = GetDayOfYear()
    if nCurDay == GetQuestData( sceneId, selfId, MD_YIZHESANYOU_DATE[ 1], MD_YIZHESANYOU_DATE[ 2], MD_YIZHESANYOU_DATE[ 3] ) then
        if GetQuestData( sceneId, selfId, MD_YIZHESANYOU_COUNTER[ 1], MD_YIZHESANYOU_COUNTER[ 2], MD_YIZHESANYOU_COUNTER[ 3] ) > 1 then
            Msg2Player( sceneId, selfId, "今天你已经做过这个任务，不能再使用娱乐币", 8, 3)
            return 0
        end
    else
        SetQuestData( sceneId, selfId, MD_YIZHESANYOU_DATE[ 1], MD_YIZHESANYOU_DATE[ 2], MD_YIZHESANYOU_DATE[ 3], GetDayOfYear() )
        SetQuestData( sceneId, selfId, MD_YIZHESANYOU_COUNTER[ 1], MD_YIZHESANYOU_COUNTER[ 2], MD_YIZHESANYOU_COUNTER[ 3], 1)
    end

    return 1
end

function x310162_Dengmi_Check( sceneId, selfId)
    local curTime = GetMinOfDay()
    if curTime < 1170 then
        Msg2Player( sceneId, selfId, "灯谜活动尚未开始，请在嘉年华活动时间19：30——24：00内使用", 8, 3)
        return 0
    end

	if IsHaveQuest(sceneId,selfId, x310163_g_DengmiMissionId) > 0 then
		Msg2Player( sceneId, selfId, "你已经接了天坛灯谜会任务，不能再使用娱乐币", 8, 3)
		return 0
	end
	
	
    if GetQuestData( sceneId, selfId, MD_DENGMI_DATE[1], MD_DENGMI_DATE[2], MD_DENGMI_DATE[3] ) == GetDayOfYear() and 
       GetQuestData( sceneId, selfId, MD_DENGMI_SCORE[1], MD_DENGMI_SCORE[2], MD_DENGMI_SCORE[3] ) > 0 then
        Msg2Player( sceneId, selfId, "你今天已经参加过天坛灯谜会了，不能再使用娱乐币", 8, 3)
        return 0
    end

    return 1
end

function x310162_Tiesan_Check( sceneId, selfId)
    local curTime = GetMinOfDay()
    if curTime < 1170 then
        Msg2Player( sceneId, selfId, "铁人三项活动尚未开始，请在嘉年华活动时间19：30——24：00内使用", 8, 3)
        return 0
    end

    if IsHaveQuestNM( sceneId, selfId, 7537) > 0 or IsHaveQuestNM( sceneId, selfId, 7538) > 0 or IsHaveQuestNM( sceneId, selfId, 7539) > 0 or IsHaveQuestNM( sceneId, selfId, 7551) > 0 or IsHaveQuestNM( sceneId, selfId, 7552) > 0 then
        Msg2Player( sceneId, selfId, "你已经接受这个任务了，快去完成吧", 8, 3)
        return 0
    end

	local nCurDay = GetDayOfYear()
    if nCurDay == GetQuestData( sceneId, selfId, MD_TIEREN_ACCEPTTIME_DAY[ 1], MD_TIEREN_ACCEPTTIME_DAY[ 2], MD_TIEREN_ACCEPTTIME_DAY[ 3] ) then
        if GetQuestData( sceneId, selfId, MD_TIEREN_COMMITTIME[1], MD_TIEREN_COMMITTIME[2], MD_TIEREN_COMMITTIME[3] ) >= 1 then
            Msg2Player( sceneId, selfId, "您今天已经领取过铁人三项活动，不能再使用娱乐币", 8, 3)
            return 0
        end
    end

    return 1
end

-- 
x310162_g_ScriptTable   = {
                            { guid = 139129, costCount = 40, check = x310162_Yizhe_Check,  proc = x310162_Yizhesanyou_Reward, description = "\t你要用#R40#W枚#{_ITEM11990117}完成一次#G益者三友#W么？\n\t使用嘉年华娱乐币完成益者三友和正常完成益者三友共享当天任务计次，经验奖励固定为中等奖励，例如需采集龙雀刀，则默认为采集到玄铁龙雀刀。藏宝图获得几率同正常完成任务。" }, 
                            { guid = 139133, costCount = 40, check = x310162_Dengmi_Check, proc = x310162_Dengmi_Reward,      description = "\t你要用#R40#W枚#{_ITEM11990117}完成今天所有的#G天坛灯谜#W么？\n\t使用嘉年华娱乐币可一次性获得所有灯谜奖励，当日不可再次猜灯谜。" }, 
                            { guid = 139100, costCount = 50, check = x310162_Tiesan_Check, proc = x310162_Tiesan_Reward,      description = "\t你要用#R50#W枚#{_ITEM11990117}完成今天的#G铁人三项#W么？\n\t使用嘉年华娱乐币可以瞬间获得铁人三项的任务奖励，当日不可再次参加铁人三项。" }, 
}
-- 
x310162_g_CurrencyID    = 11990117

----------------------------------------------------------------------------------------------
--枚举
----------------------------------------------------------------------------------------------
function x310162_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
    -- 
  local level = GetLevel( sceneId, selfId)
  if level <40 then
   return
  end
  AddQuestNumText( sceneId, x310162_g_scriptId, "使用嘉年华娱乐币", 3, 1)
end

----------------------------------------------------------------------------------------------
--脚本默认事件
----------------------------------------------------------------------------------------------
function x310162_ProcEventEntry( sceneId ,selfId, npcId, idScript, idExt)
    local id = GetMonsterGUID( sceneId, npcId)
    for i, item in x310162_g_ScriptTable do
    	if id == 139133 then
	    	local nDate   = GetQuestData(sceneId,selfId,MD_DENGMI_DATE[1], MD_DENGMI_DATE[2], MD_DENGMI_DATE[3] )
			local nCurDay = GetDayOfYear()
			if nCurDay == nDate then
				BeginQuestEvent(sceneId)
		        AddQuestText(sceneId,"#Y"..x310164_g_MissionName)
		        AddQuestText(sceneId,"每天只能猜谜一次，请明天再来")
		        EndQuestEvent()
		        DispatchQuestEventList(sceneId, selfId, npcId, x310162_g_ScriptId, x310162_g_MissionId);
		        return
		    end
		    
		    if IsHaveQuest(sceneId,selfId, x310163_g_DengmiMissionId) > 0 then
		    	BeginQuestEvent(sceneId)
		        AddQuestText(sceneId,"#Y"..x310164_g_MissionName)
		        AddQuestText(sceneId,"你已经接了天坛灯谜会任务，不能再使用娱乐币")
		        EndQuestEvent()
		        DispatchQuestEventList(sceneId, selfId, npcId, x310162_g_ScriptId, x310162_g_MissionId);
				--Msg2Player( sceneId, selfId, "你已经接了天坛灯谜会任务，不能再使用娱乐币", 8, 3)
				return 0
			end
	
		  
	    end
    
    
        if id == item.guid then
            BeginQuestEvent( sceneId)
                AddQuestText( sceneId, "#Y嘉年华娱乐币" )
                AddQuestText( sceneId, item.description)
            EndQuestEvent()
            DispatchQuestInfo( sceneId, selfId, npcId, x310162_g_scriptId, -1)
            break
        end
    end
end

function x310162_AddTianfuItem( sceneId, selfId)
	local level = GetLevel( sceneId, selfId)
	if level >= 80 then
		if random( 1, 100) <= 22 then
			local nIndex = random(1,3)
			BeginAddItem( sceneId)
	        AddItem( sceneId, x310162_g_TianfuItems[nIndex], 1)
	        if EndAddItem( sceneId, selfId) <= 0 then
	            Msg2Player( sceneId, selfId, "由于你的背包已满，无法获得天赋道具奖励。", 8, 2)
	        else
	            AddItemListToPlayer( sceneId, selfId)
	        end
		end
	end
end

function x310162_ProcAcceptCheck( sceneId, selfId, NPCId)
    local count = GetItemCount( sceneId, selfId, x310162_g_CurrencyID)
    local id = GetMonsterGUID( sceneId, NPCId)
    
--    if id == 139133 then
--    	local nCurDay = GetDayOfYear()
--		SetQuestData(sceneId,selfId,MD_DENGMI_DATE[1], MD_DENGMI_DATE[2], MD_DENGMI_DATE[3], nCurDay )
--    end
    
    
    local need = 0
    local elem = nil
    for i, item in x310162_g_ScriptTable do
        if id == item.guid then
            need = item.costCount
            elem = item
            break
        end
    end

    if count >= need then
        if elem.check( sceneId, selfId) == 1 then
            if DelItem( sceneId, selfId, 11990117, need) == 1 then
                elem.proc( sceneId, selfId)
            else
                Msg2Player( sceneId, selfId, "扣除#{_ITEM11990117}失败", 8, 3)
                return 0
            end
        end
    else
        Msg2Player( sceneId, selfId, format( "你身上的#{_ITEM11990117}不足%d枚", need), 8, 3)
        return 0
    end

 	
 
    return 1
end

----------------------------------------------------------------------------------------------
--接受
----------------------------------------------------------------------------------------------
function x310162_ProcAccept( sceneId, selfId )
end

----------------------------------------------------------------------------------------------
--放弃
----------------------------------------------------------------------------------------------
function x310162_ProcQuestAbandon( sceneId, selfId, MissionId )
end

----------------------------------------------------------------------------------------------
--继续
----------------------------------------------------------------------------------------------
function x310162_OnContinue( sceneId, selfId, targetId )
end

----------------------------------------------------------------------------------------------
--检测是否可以提交
----------------------------------------------------------------------------------------------
function x310162_CheckSubmit( sceneId, selfId )
end

----------------------------------------------------------------------------------------------
--杀死怪物或玩家
----------------------------------------------------------------------------------------------
function x310162_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end

----------------------------------------------------------------------------------------------
--进入区域事件
----------------------------------------------------------------------------------------------
function x310162_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

----------------------------------------------------------------------------------------------
--道具改变
----------------------------------------------------------------------------------------------
function x310162_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end


