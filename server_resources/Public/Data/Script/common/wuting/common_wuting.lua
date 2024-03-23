
-------------------------
--***********************
--Const
--***********************
-------------------------

--MisDescBegin

x300160_g_ScriptId 				= 300160
x300160_g_MissionName			= "【美】大都美丽会"
x300160_g_MissionAbandonName	= "离开【美丽会】"

x300160_g_LevelLess				= 40

x300160_g_AimSceneList	= {
							{ sceneId = 14, x = 31, z = 49, cenx = 32, cenz = 35, r = 9 }
}
-- 美丽会开放时间2，从0点起的第N分钟
x300160_g_OpenTime2 = 1380
-- 美丽会关闭时间2，从0点起的第N分钟
x300160_g_EndTime2  = 540
-- 美丽会开放时间2，小时。
x300160_g_OpenTimeStartH2 = 23
-- 美丽会开放时间2，分钟。
x300160_g_OpenTimeStartM2 = 0
-- 美丽会关闭时间2，小时。
x300160_g_OpenTimeEndH2 = 9
-- 美丽会关闭时间2，分钟。
x300160_g_OpenTimeEndM2 = 0
-- 美丽会禁入时间，在美丽会关闭之前多长时间禁止玩家禁入(单位：分钟)
x300160_g_CloseTime     = 5
--MisDescEnd

x300160_g_MissionInfo           = "\t美丽会是大都的一大特色，在这里浪漫与激情并存！本场所在每天#G23：00-09:00#W开放。#W\n\t您在开放时间进入美丽会时将会收取您#G#{_MONEY%d}#W现银或银卡的入场费！您可以在美丽会服务员，酒保或小兔侍女处购买美酒提高您获得的奖励！\n\t点击以下按钮选择形象进入美丽会，在美丽会关闭前#G5分钟#W您将不能进入！尊贵的客人，是否需要我引领您进入美丽会？"
x300160_g_MissionContinueInfo   = "\t尊贵的来宾，非常感谢您的光临，如果您选择离开，您在本场结束前可以免费再次进入，您需要离开美丽会吗？"
-- 美丽会入场费系数
x300160_g_EnterFeeRate		= 200

x300160_g_BackSceneId	=	0
-- x300160_g_BackX	= 193
-- x300160_g_BackZ	= 247
x300160_g_PosTable              = {
                                    { x =94 , z =67}, 
                                    { x =157 , z =73}, 
                                    { x = 50, z = 95}, 
                                    { x = 127, z =58 }, 
									{ x = 206, z =77 },
}

x300160_g_ErrorMessage			= "\t条件不符！"
x300160_g_ErrorMessage_Money	= "\t你没有足够现银或银卡！"
x300160_g_ErrorMessage_Level	= format("很抱歉，您的等级不足%d级，不能进入美丽会", x300160_g_LevelLess)

x300160_g_ErrorMessage_OutRange	= "请进入舞池跳舞！"
x300160_g_ErrorMessage_Close	= "\t很抱歉，美丽会开放时间为每天23:00-09:00，请在开放时间内入场！"
x300160_g_ErrorMessage_ProtectCar = "\t很抱歉，运镖状态不能进入美丽会！"
x300160_g_ErrorMessage_HaveBuff = "很抱歉，变身状态不能进入美丽会！"
x300160_g_ErrorMessage_Dress    = "您在穿着时装状态下不能进入美丽会！"
x300160_g_ErrorMessage_HideFace = "您在蒙面状态下不能进入美丽会！"

x300160_g_AddExpMessage = "您获得#R经验%d点#cEFC800的奖励"
x300160_g_AddExpMessage1 = "您获得#R声望%d点#cEFC800的奖励"
x300160_g_AddExpMessage2 = "您获得#R威望%d点#cEFC800的奖励"
x300160_g_ActiveMessage	= "尽情的跳舞吧！"
x300160_g_FadeOutMessage= "奖励状态消失，您需要购买相应道具继续获得奖励"

-- 基础Buff
x300160_g_BaseBuffId        = 7646
-- 2倍经验
x300160_g_XPBuffId          = 7647
-- 4倍经验
x300160_g_DoubleXPBuffId    = 7648
-- 2倍声望
x300160_g_CreditBuffId      = 7649
-- 4倍声望
x300160_g_DoubleCreditBuffId= 7650
-- 4倍威望
x300160_g_4ManaBuffId       = 7644
-- 8倍威望
x300160_g_8ManaBuffId       = 7645
-- 8倍经验 X 10小时
x300160_g_10H8XP            = 7667
-- 8倍声望 X 10小时
x300160_g_10H8Credit        = 7666
-- 8倍威望 X 10小时
x300160_g_10H8Mana          = 7665
-- 4倍经验 X 10小时
x300160_g_10H4XP            = 7668
-- 4倍声望 X 10小时
x300160_g_10H4Credit        = 7669

-------------------------
--Define
-------------------------

x300160_OK					= 0
x300160_OK_ABANDON			= 1
x300160_ERROR_UNKNOWN		= -1

x300160_FAILED_LEVEL		= 10
x300160_FAILED_OPEN			= 11
x300160_FAILED_YUNBIAO      = 14
x300160_FAILED_CHANGEBODY   = 15
x300160_FAILED_DRESS        = 16
x300160_FAILED_HIDEFACE     = 17

x300160_g_actionId			= 180

x300160_g_DressEquip_Pos    = 14

-- 禁止进入美丽会的Buff队列，具体Buff编号定义在Public\Config\std_impact.tab
x300160_g_ForbidArray = {
                            7606, -- 划船_男_楼兰
                            7605, -- 自行车_男_楼兰
							7607, --长跑_男_楼兰
							7608, --自行车_女_楼兰
							7609, --划船_女_楼兰
							7610, --长跑_女_楼兰
							7611, --自行车_男_天山
							7612, --划船_男_天山
							7613, --长跑_男_天山
							7614, --自行车_女_天山
							7615, --划船_女_天山
							7616, --长跑_女_天山
							7617, --自行车_男_昆仑
							7618, --划船_男_昆仑
							7619, --长跑_男_昆仑
							7620, --自行车_女_昆仑
							7621, --划船_女_昆仑
							7622, --长跑_女_昆仑
							7623, --自行车_男_敦煌
							7624, --划船_男_敦煌
							7625, --长跑_男_敦煌
							7626, --自行车_女_敦煌
							7627, --划船_女_敦煌
							7628, --长跑_女_敦煌
                            7516, -- 童趣变身Buff
                            7517, -- 童趣变身Buff
}

-- 变身Buff的ID
x300160_g_Dancer1_Male      = 7651
x300160_g_Dancer2_Male      = 7652
x300160_g_Dancer3_Male      = 7653
x300160_g_Dancer1_Female    = 7654
x300160_g_Dancer2_Female    = 7655
x300160_g_Dancer3_Female    = 7656

-- Buff最大持续时间上限
x300160_g_BuffMaxTime       = 36000000

-- 最大间隔时间（分钟），超过这个间隔进入美丽会就要再次扣费
x300160_g_MaxInverval       = 840

-- 舞厅T人每批人数
x300160_g_KickNumber        = 100

x300160_g_AdditionalLevel   = 90

--buff
function x300160_OnUseItem( sceneId, selfId, buffId)
    -- 获得Buff持续总时间
    local amountTime = GetImpactContinuanceByDataIndex( sceneId, selfId, buffId)
    if amountTime > 0 then
        -- 计算剩余时间
        local remainTime = amountTime - GetImpactContinuanceElapsed( sceneId, selfId, buffId)
        -- 在剩余的基础上叠加30分钟
        local newTime = 1800000 + remainTime
        if newTime > x300160_g_BuffMaxTime then
            newTime = x300160_g_BuffMaxTime
        end
        SetImpactContinuanceByDataIndex( sceneId, selfId, buffId, newTime)
        ResetImpactContinuanceElapsed( sceneId, selfId, buffId)
        RefreshImpactByDataIndex( sceneId, selfId,buffId)
        return
    else
        SendSpecificImpactToUnit( sceneId, selfId, selfId, selfId, buffId, 0)
    end
end

-- 到美丽会关闭时间把所有美丽会内玩家全部踢回大都
function x300160_OnTimerDoingStart( sceneId, actId, Param1, Param2, Param3, Param4, Param5)
    SetSystemTimerTick( sceneId, 300160, "BroadCast", actId, 10 * 1000)
end

function x300160_BroadCast( sceneId, actId, uTime)
    local curTime = GetMinOfDay()

    if curTime > x300160_g_OpenTime2 or curTime < x300160_g_EndTime2 then
        LuaThisScenceM2Wrold( sceneId, "#R营业时间将在09：00结束", 1, 1)
        SetSystemTimerTick( sceneId, 300160, "BroadCast", actId, 10 * 1000)
    else
    	local nHumanCount = GetScenePlayerCount( sceneId)
        local bContinue = 0

        if nHumanCount > 0 then
            -- 每次最多T出x300160_g_KickNumber人
            if nHumanCount > x300160_g_KickNumber then
                nHumanCount = x300160_g_KickNumber
                bContinue = 1
            end
            for i = 0, nHumanCount do
                local objId = GetScenePlayerObjId( sceneId,i)
                if objId >= 0 then
                    --清除禁止骑马状态
                    SetPlayerMutexState( sceneId, objId, PLAYER_STATE_DANCERY, 0)
                    GamePlayScriptLog( sceneId, objId, 42)

                    x300160_ChangeBody( sceneId, objId, 0, 0)

                    local strLog = format( "WTL: %s has been kick out dancery with sw(%d), ww(%d), xp=", GetName( sceneId, objId), GetShengWang( sceneId, objId), GetPlayerGoodBadValue( sceneId, objId) )
                    strLog = strLog..GetExp( sceneId, objId)
                    WriteLog( 1, strLog)

                    local r1 = random( -5, 5)
                    local r2 = random( -5, 5)
                    local index = random( 1, getn( x300160_g_PosTable) )
                    NewWorld( sceneId, objId, 0, x300160_g_PosTable[ index].x+r1, x300160_g_PosTable[ index].z+r2, 300160)
                end
            end
            -- 如果没清除完毕过5秒再次清除
            if bContinue == 1 then
                SetSystemTimerTick( sceneId, 300160, "BroadCast", actId, 5 * 1000)
            end
        end
    end
end

-- 检查上次进入时间距现在是否在同一开放时间内，如果是返回1，否则返回0
function x300160_IsSameTime( sceneId, selfId)
    -- 获得上次进入美丽会时间
    local lastTime = x300160_GetEnterMinute( sceneId, selfId)
    local curTime = GetMinOfYear()
    local costEnter = 1
    if curTime < lastTime then
        -- 跨年情况
        local year, month, day = GetYearMonthDay()
        if mod( year, 4) == 0 then
            -- 闰年
            if curTime + 527040 - lastTime >= x300160_g_MaxInverval then
                costEnter = 0
            end
        else
            if curTime + 525600 - lastTime >= x300160_g_MaxInverval then
                costEnter = 0
            end
        end
    else
        if curTime - lastTime >= x300160_g_MaxInverval then
            costEnter = 0
        end
    end

    return costEnter
end

-- 玩家在美丽会里退出游戏或掉线，再次进入游戏时的处理
function x300160_ProcMapPlayerNewConnectEnter( sceneId, selfId)
    if x300160_IsOpenTime( 1) == 0 or x300160_IsSameTime( sceneId, selfId) == 0 then
        -- 超过了上次进入的美丽会开放时间就把角色变身回去并放回大都
        -- x300160_ChangeBody( sceneId, selfId, 0, 0)
        -- SetPlayerMutexState( sceneId, selfId, PLAYER_STATE_DANCERY, 0)
        -- local index = random( 1, getn( x300160_g_PosTable) )
        -- NewWorld( sceneId, selfId, 0, x300160_g_PosTable[ index].x, x300160_g_PosTable[ index].z, 300160)
        -- 做一个T人标记，在Buff里完成，直接T可能造成跨MapServer数据丢失
        SetPlayerRuntimeData( sceneId, selfId, RD_DANCERY_BODYID, 1)
        SendSpecificImpactToUnit( sceneId, selfId, selfId, selfId, 8401, 0)
    else
        -- 恢复变身
        x300160_ChangeBody( sceneId, selfId, x300160_GetChangeID( sceneId, selfId), 1)
        -- 恢复互斥状态
        SetPlayerMutexState( sceneId, selfId, PLAYER_STATE_DANCERY, 1)
    end
    if GetQuestData( sceneId, selfId, MD_WUTING_OFFLINE_FLAG[ 1], MD_WUTING_OFFLINE_FLAG[ 2], MD_WUTING_OFFLINE_FLAG[ 3] ) == 1 then
        CallScriptFunction( 300178, "ProcMapPlayerNewConnectEnter", sceneId, selfId)
    end
end

function x300160_ChangeBody( sceneId, selfId, changeID, op)
    local sex = GetSex( sceneId, selfId)
    if op == 1 then
        if changeID == 2 then
            if sex == 1 then
                SendSpecificImpactToUnit( sceneId, selfId, selfId, selfId, x300160_g_Dancer1_Male, 0)
            else
                SendSpecificImpactToUnit( sceneId, selfId, selfId, selfId, x300160_g_Dancer1_Female, 0)
            end
        elseif changeID == 3 then
            if sex == 1 then
                SendSpecificImpactToUnit( sceneId, selfId, selfId, selfId, x300160_g_Dancer2_Male, 0)
            else
                SendSpecificImpactToUnit( sceneId, selfId, selfId, selfId, x300160_g_Dancer2_Female, 0)
            end
        elseif changeID == 4 then
            if sex == 1 then
                SendSpecificImpactToUnit( sceneId, selfId, selfId, selfId, x300160_g_Dancer3_Male, 0)
            else
                SendSpecificImpactToUnit( sceneId, selfId, selfId, selfId, x300160_g_Dancer3_Female, 0)
            end
        end
    else
        if IsHaveSpecificImpact( sceneId, selfId, x300160_g_Dancer1_Male) == 1 then
            CancelSpecificImpact( sceneId, selfId, x300160_g_Dancer1_Male)
        elseif IsHaveSpecificImpact( sceneId, selfId, x300160_g_Dancer1_Female) == 1 then
            CancelSpecificImpact( sceneId, selfId, x300160_g_Dancer1_Female)
        elseif IsHaveSpecificImpact( sceneId, selfId, x300160_g_Dancer2_Male) == 1 then
            CancelSpecificImpact( sceneId, selfId, x300160_g_Dancer2_Male)
        elseif IsHaveSpecificImpact( sceneId, selfId, x300160_g_Dancer2_Female) == 1 then
            CancelSpecificImpact( sceneId, selfId, x300160_g_Dancer2_Female)
        elseif IsHaveSpecificImpact( sceneId, selfId, x300160_g_Dancer3_Male) == 1 then
            CancelSpecificImpact( sceneId, selfId, x300160_g_Dancer3_Male)
        elseif IsHaveSpecificImpact( sceneId, selfId, x300160_g_Dancer3_Female) == 1 then
            CancelSpecificImpact( sceneId, selfId, x300160_g_Dancer3_Female)
        end
    end
end

function x300160_OnIntervalOverEvent( sceneId, selfId, buffId)
	if x300160_IsOpenTime( 1) == 0 then
        return 0
	end

	if sceneId == 14 then
		local x = GetPlayerWorldX(sceneId, selfId)
		local z = GetPlayerWorldZ(sceneId, selfId)
		local item = x300160_g_AimSceneList[ 1]
        local level = GetLevel( sceneId, selfId)
        -- 设置互斥状态
        if IsPlayerMutexState( sceneId, selfId, PLAYER_STATE_DANCERY) ~= 1 then
            SetPlayerMutexState( sceneId, selfId, PLAYER_STATE_DANCERY, 1)
        end

        if buffId == x300160_g_BaseBuffId then
            if IsHaveSpecificImpact( sceneId, selfId, x300160_g_XPBuffId) ~= 1 and 
                IsHaveSpecificImpact( sceneId, selfId, x300160_g_DoubleXPBuffId) ~= 1 and 
                IsHaveSpecificImpact( sceneId, selfId, x300160_g_10H4XP) ~= 1 and 
                IsHaveSpecificImpact( sceneId, selfId, x300160_g_10H8XP) ~= 1 then
                if level >= x300160_g_AdditionalLevel then
                    x300160_AddExp( sceneId, selfId, 0.65)
                else
                    x300160_AddExp(sceneId, selfId, 0.5)
                end
            end
            if IsHaveSpecificImpact( sceneId, selfId, x300160_g_CreditBuffId) ~= 1 and 
                IsHaveSpecificImpact( sceneId, selfId, x300160_g_DoubleCreditBuffId) ~= 1 and 
                IsHaveSpecificImpact( sceneId, selfId, x300160_g_10H4Credit) ~= 1 and 
                IsHaveSpecificImpact( sceneId, selfId, x300160_g_10H8Credit) ~= 1 then
                x300160_AddCredit( sceneId, selfId, 1)
            end
            -- if IsHaveSpecificImpact( sceneId, selfId, x300160_g_4ManaBuffId) ~= 1 and IsHaveSpecificImpact( sceneId, selfId, x300160_g_8ManaBuffId) ~= 1 then
                -- x300160_AddMana( sceneId, selfId, 1)
            -- end
        elseif buffId == x300160_g_XPBuffId then
            if level >= x300160_g_AdditionalLevel then
                x300160_AddExp(sceneId, selfId, 2.6)
            else
                x300160_AddExp(sceneId, selfId, 2)
            end
        elseif buffId == x300160_g_DoubleXPBuffId or buffId == x300160_g_10H8XP then
            if level >= x300160_g_AdditionalLevel then
                x300160_AddExp(sceneId, selfId, 5.2)
            else
                x300160_AddExp(sceneId, selfId, 4)
            end
        elseif buffId == x300160_g_CreditBuffId then
            x300160_AddCredit( sceneId, selfId, 4)
        elseif buffId == x300160_g_DoubleCreditBuffId then
            x300160_AddCredit( sceneId, selfId, 8)
        elseif buffId == x300160_g_10H8Credit then
            x300160_AddCredit( sceneId, selfId, 8)
        elseif buffId == x300160_g_8ManaBuffId then
            x300160_AddMana( sceneId, selfId, 8)
        elseif buffId == x300160_g_10H8Mana then
            x300160_AddMana( sceneId, selfId, 8)
        elseif buffId == x300160_g_10H4XP then
            if level >= x300160_g_AdditionalLevel then
                x300160_AddExp(sceneId, selfId, 2.6)
            else
                x300160_AddExp(sceneId, selfId, 2)
            end
        elseif buffId == x300160_g_10H4Credit then
            x300160_AddCredit( sceneId, selfId, 4)
        end
        --DoAction(sceneId, selfId, x300160_g_actionId, -1)
        ReCallHorse( sceneId, selfId)
	end
end

function x300160_OnActiveEvent(sceneId, selfId)
    if sceneId == 14 then
        Msg2Player( sceneId, selfId, x300160_g_ActiveMessage, 8, 3)
    end
end

function x300160_OnFadeOutEvent(sceneId, selfId, buff)
    if sceneId == 14 then
		if buff == 7646 then
	    	local str = x300160_g_FadeOutMessage;
	        BeginQuestEvent( sceneId);
	            AddQuestText( sceneId, str);
	        EndQuestEvent( sceneId);
	        DispatchQuestTips( sceneId, selfId);
	    	local Readme = "您身上的基础奖励状态消失！"
	    	Msg2Player(sceneId,selfId,Readme,8,2)
		end
		if buff == 7647 then
	    	local str = x300160_g_FadeOutMessage;
	        BeginQuestEvent( sceneId);
	            AddQuestText( sceneId, str);
	        EndQuestEvent( sceneId);
	        DispatchQuestTips( sceneId, selfId);
	    	local Readme = "您身上的4倍经验状态消失，您可以在在美丽会内的酒保或小兔侍女处购买杰克丹尼来继续获得奖励！"
	    	Msg2Player(sceneId,selfId,Readme,8,2)
		end
		if buff == 7648 or buff == x300160_g_10H8XP then
	    	local str = x300160_g_FadeOutMessage;
	        BeginQuestEvent( sceneId);
	            AddQuestText( sceneId, str);
	        EndQuestEvent( sceneId);
	        DispatchQuestTips( sceneId, selfId);
	    	local Readme = "您身上的8倍经验状态消失，您可以在美丽会内的酒保或小兔侍女处购买芝华士来继续获得奖励！"
	    	Msg2Player(sceneId,selfId,Readme,8,2)
		end
		if buff == 7649 then
			local str = x300160_g_FadeOutMessage;
	        BeginQuestEvent( sceneId);
	        AddQuestText( sceneId, str);
	        EndQuestEvent( sceneId);
	        DispatchQuestTips( sceneId, selfId);
	    	local Readme = "您身上的4倍声望状态消失，您可以在美丽会内的酒保或小兔侍女处购买路易十三来继续获得奖励！"
	    	Msg2Player(sceneId,selfId,Readme,8,2)
		end
		if buff == 7650 or buff == x300160_g_10H8Credit then
	    	local str = x300160_g_FadeOutMessage;
	        BeginQuestEvent( sceneId);
	            AddQuestText( sceneId, str);
	        EndQuestEvent( sceneId);
	        DispatchQuestTips( sceneId, selfId);
	    	local Readme = "您身上的8倍声望状态消失，您可以在美丽会内的酒保或小兔侍女处购买轩尼诗理查来继续获得奖励！"
	    	Msg2Player(sceneId,selfId,Readme,8,2)
		end
        if buff == x300160_g_4ManaBuffId then
            Msg2Player( sceneId, selfId, x300160_g_FadeOutMessage, 8, 3)
	    	Msg2Player( sceneId, selfId, "您身上的威望状态消失，您可以在美丽会内的酒保或小兔侍女处购买黑雪茄来继续获得奖励！", 8, 2)
        end
        if buff == x300160_g_8ManaBuffId or buff == x300160_g_10H8Mana then
            Msg2Player( sceneId, selfId, x300160_g_FadeOutMessage, 8, 3)
	    	Msg2Player( sceneId, selfId, "您身上的威望状态消失，您可以在美丽会内的酒保或小兔侍女处购买哈瓦那雪茄来继续获得奖励！", 8, 2)
        end
	end
	 if sceneId ~= 14 then
		if buff == 7646 then
			BeginQuestEvent( sceneId);
	        AddQuestText( sceneId, "您身上的跳舞基础奖励状态已经消失！");
	        EndQuestEvent( sceneId);
	        DispatchQuestTips( sceneId, selfId);
	    	local Readme = "您身上的跳舞基础奖励状态已经消失！"
	    	Msg2Player(sceneId,selfId,Readme,8,2)
		end
		
		if buff == 7647 then
			BeginQuestEvent( sceneId);
	        AddQuestText( sceneId, "您身上的跳舞4倍经验状态已经消失！");
	        EndQuestEvent( sceneId);
	        DispatchQuestTips( sceneId, selfId);
	    	local Readme = "您身上的跳舞4倍经验状态已经消失！"
	    	Msg2Player(sceneId,selfId,Readme,8,2)
		end
		if buff == 7648 or buff == x300160_g_10H8XP then
			BeginQuestEvent( sceneId);
	        AddQuestText( sceneId, "您身上的跳舞8倍经验状态已经消失！");
	        EndQuestEvent( sceneId);
	        DispatchQuestTips( sceneId, selfId);
	    	local Readme = "您身上的跳舞8倍经验状态已经消失！"
	    	Msg2Player(sceneId,selfId,Readme,8,2)
		end
		if buff == 7649 then
			BeginQuestEvent( sceneId);
	        AddQuestText( sceneId, "您身上的跳舞4倍声望状态已经消失！");
	        EndQuestEvent( sceneId);
	        DispatchQuestTips( sceneId, selfId);
	    	local Readme = "您身上的跳舞4倍声望状态已经消失！"
	    	Msg2Player(sceneId,selfId,Readme,8,2)
		end
		if buff == 7650 or buff == x300160_g_10H8Credit then
			BeginQuestEvent( sceneId);
	        AddQuestText( sceneId, "您身上的跳舞8倍声望状态已经消失！");
	        EndQuestEvent( sceneId);
	        DispatchQuestTips( sceneId, selfId);
	    	local Readme = "您身上的跳舞8倍声望状态已经消失！"
	    	Msg2Player(sceneId,selfId,Readme,8,2)
		end
        if buff == x300160_g_4ManaBuffId then
            Msg2Player( sceneId, selfId, "您身上的威望状态消失！", 8, 3)
	    	Msg2Player( sceneId, selfId, "您身上的威望状态消失！", 8, 2)
        end
        if buff == x300160_g_8ManaBuffId or buff == x300160_g_10H8Mana then
            Msg2Player( sceneId, selfId, "您身上的威望状态消失！", 8, 3)
	    	Msg2Player( sceneId, selfId, "您身上的威望状态消失！", 8, 2)
        end
    end
end

-------------------------
--IsInDancery 如果在美丽会内返回1，否则返回0
-------------------------
function x300160_IsInDancery(sceneId, selfId)

	for i, item in x300160_g_AimSceneList do
		if sceneId == item.sceneId then
			return i;
		end
	end
	return 0;

end

-------------------------
--AddExp
-------------------------
function x300160_AddExp(sceneId, selfId, times)
    -- 获得玩家等级
    local level = GetLevel( sceneId, selfId)
	-- 计算增加经验值。经验计算公式：( 1000 * 0.1 * 玩家等级) * 系数 / 6（每10秒钟）
	if level < 70 then
		local xp = 100 * 1.5 * level / 6 * times
		-- 增加经验
		AddExp( sceneId, selfId, xp)
		-- 显示提示消息
		Msg2Player( sceneId, selfId, format( x300160_g_AddExpMessage, xp), 8, 3)
	end
	if level >=70 and level < 80 then
		local xp = 100 * 2.7 * level / 6 * times
		-- 增加经验
		AddExp( sceneId, selfId, xp)
		-- 显示提示消息
		Msg2Player( sceneId, selfId, format( x300160_g_AddExpMessage, xp), 8, 3)
	end
	if level >=80 then
		local xp = 100 * 5.4 * level / 6 * times
		-- 增加经验
		AddExp( sceneId, selfId, xp)
		-- 显示提示消息
		Msg2Player( sceneId, selfId, format( x300160_g_AddExpMessage, xp), 8, 3)
	end
end

function x300160_AddCredit( sceneId, selfId, times)
    local credits = 1 * times
    SetShengWang( sceneId, selfId, GetShengWang( sceneId, selfId) + credits)
    Msg2Player( sceneId, selfId, format( x300160_g_AddExpMessage1, credits), 8, 3)
    --print( format( x300160_g_AddExpMessage1, credits) )
end

function x300160_AddMana( sceneId, selfId, times)
    SetPlayerGoodBadValue( sceneId, selfId, GetPlayerGoodBadValue( sceneId, selfId) + times)
    Msg2Player( sceneId, selfId, format( x300160_g_AddExpMessage2, times), 8, 3)
end

-- 081224（齐亮）是否处于美丽会开放时间内，返回1表示目前处于开放时间，返回0表示不在开放时间内
-- bInDanceRoom：1表示在美丽会内，0表示不在
function x300160_IsOpenTime( bInDanceRoom)
    if bInDanceRoom == 1 then
        local curTime = GetMinOfDay()
        if curTime >= x300160_g_OpenTime2 or curTime < x300160_g_EndTime2 then
            return 1
        end
    else
        local curTime = GetMinOfDay()
        if curTime >= x300160_g_OpenTime2 or curTime < x300160_g_EndTime2 - x300160_g_CloseTime then
            return 1
        end
    end

    return 0
end

-------------------------
--SafeNPCCheck
-------------------------
function x300160_SafeNPCCheck( sceneId, selfId)

	if x300160_IsInDancery(sceneId, selfId) > 0 then
        -- 如果在美丽会内
		return x300160_OK_ABANDON
	end
	-- 检查玩家等级
	if GetLevel(sceneId, selfId) < x300160_g_LevelLess then
		return x300160_FAILED_LEVEL, x300160_g_ErrorMessage_Level
	end
	-- 检查当前是否处于美丽会开放时间
    if x300160_IsOpenTime( 0) == 0 then
        local strOpenTime = "非常抱歉，官府规定我们的营业时间为#G%02d: %02d—%02d: %02d#cffcf00，请在营业时间前来光临！"
        local str = format( strOpenTime, 
                                    x300160_g_OpenTimeStartH2, x300160_g_OpenTimeStartM2, x300160_g_OpenTimeEndH2, x300160_g_OpenTimeEndM2)
        return x300160_FAILED_OPEN, str
    end
    -- 检查是否处于运镖状态
    if IsBusMember( sceneId, selfId) == 1 then
        return x300160_FAILED_YUNBIAO, x300160_g_ErrorMessage_ProtectCar
    end
    -- 处于其它变身状态不允许进入
    if x300160_IsSpecialImpace( sceneId, selfId) == 1 then
        return x300160_FAILED_CHANGEBODY, x300160_g_ErrorMessage_HaveBuff
    end
    -- 穿衣状态也不允许进入
    if GetEquipItemID(sceneId, selfId, x300160_g_DressEquip_Pos) ~= -1 then
        return x300160_FAILED_DRESS, x300160_g_ErrorMessage_Dress
    end
    -- 蒙面状态不能进
    if IsHideName( sceneId, selfId) > 0 then
        return x300160_FAILED_HIDEFACE, x300160_g_ErrorMessage_HideFace
    end

    return x300160_OK

end

-------------------------
--ProcEnumEvent
-------------------------
function x300160_ProcEnumEvent( sceneId, selfId, NPCId, MissionId)
    local str
    --SendSpecificImpactToUnit( sceneId, selfId, selfId, selfId, 7652, 0)
    if x300160_IsInDancery( sceneId, selfId) > 0 then
        str = x300160_g_MissionAbandonName;
    else
        str = x300160_g_MissionName;
    end
    AddQuestNumText( sceneId, x300160_g_ScriptId, str, 14, 1)
end

-- 进入美丽会时的操作
function x300160_EnterScene( sceneId, selfId)
    if sceneId == 14 then
        x300160_ChangeBody( sceneId, selfId, x300160_GetChangeID( sceneId, selfId), 1)
    end
end

-------------------------
--GetEnterFee：根据玩家等级返回进入美丽会所需的费用
-------------------------
function x300160_GetEnterFee( sceneId, selfId)

	return GetLevel( sceneId, selfId) * x300160_g_EnterFeeRate;

end

-------------------------
--ProcEventEntry
-------------------------
function x300160_ProcEventEntry( sceneId, selfId, NPCId, idScript, idExt)

	local str = "#Y"..x300160_g_MissionName.."#W\n";

	if x300160_IsInDancery( sceneId, selfId) > 0 then
		str = str..x300160_g_MissionContinueInfo;
		BeginQuestEvent( sceneId);
			AddQuestText( sceneId, str);
		EndQuestEvent( sceneId);
        DispatchQuestInfo( sceneId, selfId, NPCId, x300160_g_ScriptId, -1)
	else
        if idExt == 1 then
            str = str..format( x300160_g_MissionInfo, x300160_GetEnterFee( sceneId, selfId) )
            BeginQuestEvent( sceneId);
                AddQuestText( sceneId, str);

                if x300160_IsSameTime( sceneId, selfId) == 0 then
                    AddQuestNumText( sceneId, x300160_g_ScriptId, format( "变换天舞者（#{_MONEY%d}）", x300160_GetEnterFee( sceneId, selfId) ),  3, 2)
                    AddQuestNumText( sceneId, x300160_g_ScriptId, format( "变换狂舞者（#{_MONEY%d}）", x300160_GetEnterFee( sceneId, selfId) ),  3, 3)
                    AddQuestNumText( sceneId, x300160_g_ScriptId, format( "变换风舞者（#{_MONEY%d}）", x300160_GetEnterFee( sceneId, selfId) ),  3, 4)
                else                                                 
                    AddQuestNumText( sceneId, x300160_g_ScriptId, "变换天舞者",  3, 2)
                    AddQuestNumText( sceneId, x300160_g_ScriptId, "变换狂舞者",  3, 3)
                    AddQuestNumText( sceneId, x300160_g_ScriptId, "变换风舞者",  3, 4)
                end
            EndQuestEvent( sceneId);
            DispatchQuestEventList( sceneId, selfId, NPCId)
        else
            x300160_EnterDancery( sceneId, selfId)
            x300160_SetChangeID( sceneId, selfId, idExt)
        end
	end

end

function x300160_EnterDancery( sceneId, selfId)
    local checkResult, strCheck = x300160_SafeNPCCheck( sceneId, selfId)
    if checkResult ~= x300160_OK then
        Msg2Player( sceneId, selfId, strCheck, 8, 3)
        return
    end

    -- 获得当天日期
    local curDay = GetDayOfYear()
    -- 获得当前时间(分钟)
    local curMinute = GetMinOfYear()
    -- 扣费标记，交钱设1
    local costEnter = 0
    -- 时间检查处理
    if x300160_IsSameTime( sceneId, selfId) == 0 then
        -- 扣费
        if x300160_CostFee( sceneId, selfId) <= 0 then
            -- 如果扣费失败
            Msg2Player( sceneId, selfId, x300160_g_ErrorMessage_Money, 8, 3)
            return
        end
        costEnter = 1
        -- 更新进入时间
        x300160_SetEnterMinute( sceneId, selfId, curMinute)
    end

    -- 下马
    --ReCallHorse( sceneId, selfId)

    local strLog = format( "WTL: %s enter dancery with sw(%d), ww(%d), xp=", GetName( sceneId, selfId), GetShengWang( sceneId, selfId), GetPlayerGoodBadValue( sceneId, selfId) )
    strLog = strLog..GetExp( sceneId, selfId)
    WriteLog( 1, strLog)

    -- 进美丽会
	local aimscene, aimx, aimz = x300160_GetAimSceneInfo(sceneId, selfId);
	NewWorld(sceneId, selfId, aimscene, aimx, aimz, 300160)

    -- 设置禁止骑马状态
    -- 091106因为舞厅和大都不在同一个MapServer，所以加互斥放到core中ProcMapPlayerEnter
    -- SetPlayerMutexState( sceneId, selfId, PLAYER_STATE_DANCERY, 1)

    -- 加基础Buff
    --SendSpecificImpactToUnit( sceneId, selfId, selfId, selfId, x300160_g_BaseBuffId, 0)

	GamePlayScriptLog( sceneId, selfId, 41)
end

function x300160_IsSpecialImpace( sceneId, selfId)
    for i, buff in x300160_g_ForbidArray do
        if IsHaveSpecificImpact( sceneId, selfId, buff) == 1 then
            return 1
        end
    end

    return 0
end

-------------------------
--ProcAcceptCheck
-------------------------
function x300160_ProcAcceptCheck( sceneId, selfId, NPCId)
	return 1
end

-------------------------
--CostFee
-------------------------
function x300160_CostFee( sceneId, selfId)

	local money = x300160_GetEnterFee(sceneId, selfId);
	-- if GetMoney(sceneId, selfId, 0) < money then
		-- return 0;
	-- end
	-- if CostMoney(sceneId, selfId, 0, money,306) ~= 1 then
		-- return 0;
	-- end
    if GetSillerMode( sceneId, selfId ) == 1 then
        if CostMoney( sceneId, selfId, 0, money) ~= 1 then
            if CostMoney(sceneId, selfId, 1, money) ~= 1 then
                Msg2Player( sceneId, selfId, "扣费失败，请稍候再试", 8, 3)
                return 0
            end
        end
    else
        if CostMoney( sceneId, selfId, 1, money) ~= 1 then
            if CostMoney(sceneId, selfId, 0, money, 306) ~= 1 then
                Msg2Player( sceneId, selfId, "扣费失败，请稍候再试", 8, 3)
                return 0
            end
        end
    end

    -- 扣费之后立即加基础Buff
    SendSpecificImpactToUnit( sceneId, selfId, selfId, selfId, x300160_g_BaseBuffId, 0)

    return 1;

end

-------------------------
--GetAimSceneInfo
-------------------------
function x300160_GetAimSceneInfo(sceneId, selfId)

	local pAimScene = x300160_g_AimSceneList[1];
	return pAimScene.sceneId, pAimScene.x, pAimScene.z;

end

-------------------------
--ProcAccept
-------------------------
function x300160_ProcAccept( sceneId, selfId, NPCId)
end

function x300160_GetEnterMinute( sceneId, selfId)
    return GetQuestData( sceneId, selfId, MD_WUTING_ENTERMINUTE[ 1], MD_WUTING_ENTERMINUTE[ 2], MD_WUTING_ENTERMINUTE[ 3] )
end

function x300160_SetEnterMinute( sceneId, selfId, value)
    SetQuestData( sceneId, selfId, MD_WUTING_ENTERMINUTE[ 1], MD_WUTING_ENTERMINUTE[ 2], MD_WUTING_ENTERMINUTE[ 3], value)
end

function x300160_GetChangeID( sceneId, selfId)
    return GetQuestData( sceneId, selfId, MD_WUTING_CHANGEID[ 1], MD_WUTING_CHANGEID[ 2], MD_WUTING_CHANGEID[ 3] )
end

function x300160_SetChangeID( sceneId, selfId, value)
    SetQuestData( sceneId, selfId, MD_WUTING_CHANGEID[ 1], MD_WUTING_CHANGEID[ 2], MD_WUTING_CHANGEID[ 3], value)
end

-------------------------
--TransferBack
-------------------------
function x300160_TransferBack(sceneId, selfId)
    --清除禁止骑马状态
    SetPlayerMutexState( sceneId, selfId, PLAYER_STATE_DANCERY, 0)

    -- 恢复变身
    x300160_ChangeBody( sceneId, selfId, 0, 0)

	local aimscene = x300160_g_BackSceneId;
	local index = random( 1, getn( x300160_g_PosTable) )

    local strLog = format( "WTL: %s leave dancery with sw(%d), ww(%d), xp=", GetName( sceneId, selfId), GetShengWang( sceneId, selfId), GetPlayerGoodBadValue( sceneId, selfId) )
    strLog = strLog..GetExp( sceneId, selfId)
    WriteLog( 1, strLog)

    NewWorld( sceneId, selfId, 0, x300160_g_PosTable[ index].x, x300160_g_PosTable[ index].z, 300160)

	GamePlayScriptLog( sceneId, selfId, 42)
end

-------------------------
--ProcQuestSubmit
-------------------------
function x300160_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
end

function x300160_ProcAcceptCheck( sceneId, selfId, targetId)
	x300160_TransferBack(sceneId, selfId);
end

-------------------------
--杀死怪物或玩家
-------------------------
function x300160_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
end

-------------------------
--进入区域事件
-------------------------
function x300160_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)
end

-------------------------
--道具改变
-------------------------
function x300160_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
end


