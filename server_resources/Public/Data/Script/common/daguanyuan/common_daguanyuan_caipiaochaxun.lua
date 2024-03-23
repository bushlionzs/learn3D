-- 脚本号
x310361_g_ScriptId                  = 310361
-- 
x310361_g_MissionName               = "乐透大奖"

function x310361_ProcEnumEvent( sceneId, selfId, NPCId, MissionId)
    AddQuestNumText( sceneId, x310361_g_ScriptId, "乐透大奖查询", 3, 1)
end

function x310361_ProcEventEntry( sceneId, selfId, NPCId, idScript, idExt)
    local day, week = GetWeek()
    if idExt == 1 then
        if day ~= 0 and day ~= 6 then
            Msg2Player( sceneId, selfId, "周六、日才能查询", 8, 3)
            return
        end
        BeginQuestEvent( sceneId)
            AddQuestText( sceneId, "#Y"..x310361_g_MissionName)

            local value = GetCountryParam( sceneId, 1, CD_DAGUANYUAN_CAIPIAO1)
            if value ~= -1 then
                local a, b = x310361_GetLuckyNumber( value)
                AddQuestText( sceneId, format( "\t#G10：30#W开出的幸运号码是：#R%d #B%d#W。", a, b) )
            else
                AddQuestText( sceneId, format( "\t#G10：30#W的幸运号码尚未开出。" ) )
            end

            local value = GetCountryParam( sceneId, 2, CD_DAGUANYUAN_CAIPIAO1)
            if value ~= -1 then
                local a, b = x310361_GetLuckyNumber( value)
                AddQuestText( sceneId, format( "\t#G12：30#W开出的幸运号码是：#R%d #B%d#W。", a, b) )
            else
                AddQuestText( sceneId, format( "\t#G12：30#W的幸运号码尚未开出。" ) )
            end

            local value = GetCountryParam( sceneId, 3, CD_DAGUANYUAN_CAIPIAO1)
            if value ~= -1 then
                local a, b = x310361_GetLuckyNumber( value)
                AddQuestText( sceneId, format( "\t#G14：30#W开出的幸运号码是：#R%d #B%d#W。", a, b) )
            else
                AddQuestText( sceneId, format( "\t#G14：30#W的幸运号码尚未开出。" ) )
            end

            local value = GetCountryParam( sceneId, 0, CD_DAGUANYUAN_CAIPIAO2)
            if value ~= -1 then
                local a, b = x310361_GetLuckyNumber( value)
                AddQuestText( sceneId, format( "\t#G16：30#W开出的幸运号码是：#R%d #B%d#W。", a, b) )
            else
                AddQuestText( sceneId, format( "\t#G16：30#W的幸运号码尚未开出。" ) )
            end

            local value = GetCountryParam( sceneId, 1, CD_DAGUANYUAN_CAIPIAO2)
            if value ~= -1 then
                local a, b = x310361_GetLuckyNumber( value)
                AddQuestText( sceneId, format( "\t#G18：30#W开出的幸运号码是：#R%d #B%d#W。", a, b) )
            else
                AddQuestText( sceneId, format( "\t#G18：30#W的幸运号码尚未开出。" ) )
            end

            local value = GetCountryParam( sceneId, 2, CD_DAGUANYUAN_CAIPIAO2)
            if value ~= -1 then
                local a, b = x310361_GetLuckyNumber( value)
                AddQuestText( sceneId, format( "\t#G20：30#W开出的幸运号码是：#R%d #B%d#W。", a, b) )
            else
                AddQuestText( sceneId, format( "\t#G20：30#W的幸运号码尚未开出。" ) )
            end

            local value = GetCountryParam( sceneId, 3, CD_DAGUANYUAN_CAIPIAO2)
            if value ~= -1 then
                local a, b = x310361_GetLuckyNumber( value)
                AddQuestText( sceneId, format( "\t#G10：30#W开出的幸运号码是：#R%d #B%d#W。", a, b) )
            else
                AddQuestText( sceneId, format( "\t#G22：30#W的幸运号码尚未开出。" ) )
            end
        EndQuestEvent()
        DispatchQuestEventList( sceneId, selfId, NPCId)
    end
end

function x310361_GetLuckyNumber( value)
    local first = floor( value / 80)
    local second = mod( value, 80)
    return first, second
end

