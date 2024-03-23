x570056_g_ScriptId = 570056

-- 可保存最大值(分钟)
x570056_g_SaveMaxMinute     = 600

-- 冻双
x570056_g_BuffId          = 9015

function x570056_ProcEnumEvent( sceneId, selfId, NPCId, MissionId)
	--SendSpecificImpactToUnit( sceneId, selfId, selfId, selfId, x570056_g_BuffId, 0)

	local nTime = GetQuestData( sceneId, selfId, MD_TIANFU_DONGSHUANG[1], MD_TIANFU_DONGSHUANG[2], MD_TIANFU_DONGSHUANG[3])
	
    AddQuestNumText( sceneId, x570056_g_ScriptId, "冻结天赋丹时间", 3, 1)

	if nTime > 0 then
		AddQuestNumText( sceneId, x570056_g_ScriptId, "解冻天赋丹时间#G("..x570056_GetTimeString(nTime)..")", 3, 2)
	else
		AddQuestNumText( sceneId, x570056_g_ScriptId, "解冻天赋丹时间", 3, 2)
	end

end

function x570056_ProcEventEntry( sceneId, selfId, NPCId, idScript, idExt)
    if idExt == 1 then
        x570056_ShowSaveInfo( sceneId, selfId, NPCId)
    elseif idExt == 2 then
        x570056_ShowLoadInfo( sceneId, selfId, NPCId)
    elseif idExt == 3 then
        BeginQuestEvent( sceneId)
            AddQuestText( sceneId, "#Y冻结天赋丹时间" )
            AddQuestText( sceneId, "\t你要冻结天赋丹时间吗？冻结可以使你的天赋丹不再随时间流逝。\n\t如果你希望重新获得这些冻结的天赋丹时间，可以使用#G解冻功能#W。\n\t注意，天赋丹时间最多可以冻结#R10小时#W！" )
        EndQuestEvent()
        DispatchQuestEventList( sceneId, selfId, NPCId)
    end             
end

function x570056_ProcAcceptCheck( sceneId, selfId, NPCId)
    return 1
end

function x570056_ProcAccept( sceneId, selfId)
    local runtimeData = GetPlayerRuntimeData( sceneId, selfId, RD_COLLECT_HORSE)
    if runtimeData == 1 then
        x570056_SaveBuff( sceneId, selfId )
    elseif runtimeData == 2 then
        x570056_LoadBuff( sceneId, selfId )
    end
end

-- 分钟转换为N小时M分钟
function x570056_GetTimeString( minute)
    local strResult = ""

    if minute >= 60 then
        local h = floor( minute / 60)
        local m = mod( minute, 60)
        if m == 0 then
            strResult = format( "%d小时", h)
        else
            strResult = format( "%d小时%d分", h, m)
        end
    else
        strResult = format( "%d分钟", minute)
    end

    return strResult
end

-- 储存Buff
function x570056_SaveBuff( sceneId, selfId)
    -- 获得Buff持续总时间
    local amountTime = GetImpactContinuanceByDataIndex(sceneId, selfId, x570056_g_BuffId)
    if amountTime > 0 then
        -- 剩余时间(分钟)
        local remainTime = ( amountTime - GetImpactContinuanceElapsed( sceneId, selfId, x570056_g_BuffId) ) / 60000
        -- 已经保存的时间
        local savedTime = GetQuestData( sceneId, selfId, MD_TIANFU_DONGSHUANG[1], MD_TIANFU_DONGSHUANG[2], MD_TIANFU_DONGSHUANG[3] )
        local newTime = savedTime + remainTime
        if newTime > x570056_g_SaveMaxMinute then
            -- 保存Buff
            SetQuestData( sceneId, selfId, MD_TIANFU_DONGSHUANG[1], MD_TIANFU_DONGSHUANG[2], MD_TIANFU_DONGSHUANG[3], x570056_g_SaveMaxMinute)
            
           
            -- 更新身上的Buff时间
            SetImpactContinuanceByDataIndex( sceneId, selfId, x570056_g_BuffId, ( newTime - x570056_g_SaveMaxMinute) * 60000)
            ResetImpactContinuanceElapsed( sceneId, selfId, x570056_g_BuffId)
            RefreshImpactByDataIndex( sceneId, selfId,x570056_g_BuffId)
            Msg2Player( sceneId, selfId, "你已经存满10小时，不能再多存了", 8, 3)
        else
            -- 保存Buff
            SetQuestData( sceneId, selfId, MD_TIANFU_DONGSHUANG[1], MD_TIANFU_DONGSHUANG[2], MD_TIANFU_DONGSHUANG[3], newTime)
            
            -- 清除身上的Buff时间
            CancelSpecificImpact( sceneId, selfId, x570056_g_BuffId)
        end
    else
        Msg2Player( sceneId, selfId, "你身上已经没有可冻结的天赋丹时间了", 8, 3)
    end
end

-- 恢复Buff
function x570056_LoadBuff( sceneId, selfId)

    local savedTime = GetQuestData( sceneId, selfId, MD_TIANFU_DONGSHUANG[1], MD_TIANFU_DONGSHUANG[2], MD_TIANFU_DONGSHUANG[3] )
    if savedTime == 0 then
        Msg2Player( sceneId, selfId, "你没有可以解冻的天赋丹时间", 8, 3)
        return
    end
    
    -- 获得Buff持续总时间
    local amountTime = GetImpactContinuanceByDataIndex( sceneId, selfId, x570056_g_BuffId)
    -- 剩余时间(分钟)
    local remainTime = ( amountTime - GetImpactContinuanceElapsed( sceneId, selfId, x570056_g_BuffId) ) / 60000
    local newTime = remainTime + savedTime
    if newTime > x570056_g_SaveMaxMinute then
    
        if remainTime == 0 then
            SendSpecificImpactToUnit( sceneId, selfId, selfId, selfId, x570056_g_BuffId, 0)
        end
        -- 更新身上的Buff时间
        SetImpactContinuanceByDataIndex( sceneId, selfId, x570056_g_BuffId, newTime * 60000)
        ResetImpactContinuanceElapsed( sceneId, selfId, x570056_g_BuffId)
        RefreshImpactByDataIndex( sceneId, selfId, x570056_g_BuffId)
        -- 更新保存的时间
        SetQuestData( sceneId, selfId, MD_TIANFU_DONGSHUANG[1], MD_TIANFU_DONGSHUANG[2], MD_TIANFU_DONGSHUANG[3], 0)
        
        Msg2Player( sceneId, selfId, format( "成功领取天赋丹时间#G%s", x570056_GetTimeString( x570056_g_SaveMaxMinute) ), 8, 3)
    else
        if remainTime == 0 then
            SendSpecificImpactToUnit( sceneId, selfId, selfId, selfId, x570056_g_BuffId, 0)
        end
        -- 更新身上的Buff时间
        SetImpactContinuanceByDataIndex( sceneId, selfId, x570056_g_BuffId, newTime * 60000)
        ResetImpactContinuanceElapsed( sceneId, selfId, x570056_g_BuffId)
        RefreshImpactByDataIndex( sceneId, selfId, x570056_g_BuffId)
        
        -- 更新保存的时间
        SetQuestData( sceneId, selfId, MD_TIANFU_DONGSHUANG[1], MD_TIANFU_DONGSHUANG[2], MD_TIANFU_DONGSHUANG[3], 0)
        Msg2Player( sceneId, selfId, "你解冻了所有冻结的天赋丹时间", 8, 2)
    end
end

-- 显示保存Buff确认界面
function x570056_ShowSaveInfo( sceneId, selfId, NPCId)
    BeginQuestEvent( sceneId)
        AddQuestText( sceneId, "#Y冻结天赋丹时间" )
        AddQuestText( sceneId, "\t你要冻结天赋丹时间吗？冻结可以使你的天赋丹不再随时间流逝。\n\t如果你希望重新获得这些冻结的天赋丹时间，可以使用#G解冻功能#W。\n\t注意，天赋丹时间最多可以冻结#R10小时#W！" )
    EndQuestEvent()
    SetPlayerRuntimeData( sceneId, selfId, RD_COLLECT_HORSE, 1)
    DispatchQuestInfo( sceneId, selfId, NPCId, x570056_g_ScriptId, -1)
end

-- 显示取回Buff确认界面
function x570056_ShowLoadInfo( sceneId, selfId, NPCId)
    
	local nTime = GetQuestData( sceneId, selfId, MD_TIANFU_DONGSHUANG[1], MD_TIANFU_DONGSHUANG[2], MD_TIANFU_DONGSHUANG[3])
	BeginQuestEvent( sceneId)
        AddQuestText( sceneId, "#Y解冻天赋丹时间" )
        AddQuestText( sceneId, "\t你是否要解冻天赋丹时间？你现在冻结的天赋丹时间为：#G("..x570056_GetTimeString(nTime)..")")
    EndQuestEvent()


    SetPlayerRuntimeData( sceneId, selfId, RD_COLLECT_HORSE, 2)
	DispatchQuestInfo( sceneId, selfId, NPCId, x570056_g_ScriptId, -1)
end


