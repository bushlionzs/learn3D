
x300172_g_ScriptId = 300172
x300172_g_FarScriptId = 300160

-- 2������ �ܿ˵���
x300172_g_XPBuffId          = 7647
-- 4������ ֥��ʿ
x300172_g_DoubleXPBuffId    = 7648
-- 2������ ·��ʮ��
x300172_g_CreditBuffId      = 7649
-- 4������ ����ʫ���
x300172_g_DoubleCreditBuffId= 7650
-- 8������ ������ѩ��
x300172_g_Mana8             = 7645
-- �ɱ������ֵ(����)
x300172_g_SaveMaxMinute     = 600
-- 8������ X 10Сʱ
x300172_g_10H8XP            = 7667
-- 8������ X 10Сʱ
x300172_g_10H8Credit        = 7666
-- 8������ X 10Сʱ
x300172_g_10H8Mana          = 7665
-- 4������ X 10Сʱ
x300172_g_10H4XP            = 7668
-- 4������ X 10Сʱ
x300172_g_10H4Credit        = 7669


function x300172_GetExp2( sceneId, selfId)
    return GetQuestData( sceneId, selfId, MD_WUTING_EXP_2[ 1], MD_WUTING_EXP_2[ 2], MD_WUTING_EXP_2[ 3] )
end

function x300172_SetExp2( sceneId, selfId, value)
    SetQuestData( sceneId, selfId, MD_WUTING_EXP_2[ 1], MD_WUTING_EXP_2[ 2], MD_WUTING_EXP_2[ 3], value)
end

function x300172_GetExp4( sceneId, selfId)
    return GetQuestData( sceneId, selfId, MD_WUTING_EXP_4[ 1], MD_WUTING_EXP_4[ 2], MD_WUTING_EXP_4[ 3] )
end

function x300172_SetExp4( sceneId, selfId, value)
    SetQuestData( sceneId, selfId, MD_WUTING_EXP_4[ 1], MD_WUTING_EXP_4[ 2], MD_WUTING_EXP_4[ 3], value)
end

function x300172_GetCredit4( sceneId, selfId)
    return GetQuestData( sceneId, selfId, MD_WUTING_CREDIT_4[ 1], MD_WUTING_CREDIT_4[ 2], MD_WUTING_CREDIT_4[ 3] )
end

function x300172_SetCredit4( sceneId, selfId, value)
    SetQuestData( sceneId, selfId, MD_WUTING_CREDIT_4[ 1], MD_WUTING_CREDIT_4[ 2], MD_WUTING_CREDIT_4[ 3], value)
end

function x300172_GetCredit8( sceneId, selfId)
    return GetQuestData( sceneId, selfId, MD_WUTING_CREDIT_8[ 1], MD_WUTING_CREDIT_8[ 2], MD_WUTING_CREDIT_8[ 3] )
end

function x300172_SetCredit8( sceneId, selfId, value)
    SetQuestData( sceneId, selfId, MD_WUTING_CREDIT_8[ 1], MD_WUTING_CREDIT_8[ 2], MD_WUTING_CREDIT_8[ 3], value)
end

function x300172_GetMana8( sceneId, selfId)
    return GetQuestData( sceneId, selfId, MD_DANCERY_8MANA[ 1], MD_DANCERY_8MANA[ 2], MD_DANCERY_8MANA[ 3] )
end

function x300172_SetMana8( sceneId, selfId, value)
    SetQuestData( sceneId, selfId, MD_DANCERY_8MANA[ 1], MD_DANCERY_8MANA[ 2], MD_DANCERY_8MANA[ 3], value)
end

function x300172_GetXP8X10( sceneId, selfId)
    return GetQuestData( sceneId, selfId, MD_DANCERY_XP8X10[ 1], MD_DANCERY_XP8X10[ 2], MD_DANCERY_XP8X10[ 3] )
end

function x300172_SetXP8X10( sceneId, selfId, value)
    SetQuestData( sceneId, selfId, MD_DANCERY_XP8X10[ 1], MD_DANCERY_XP8X10[ 2], MD_DANCERY_XP8X10[ 3], value)
end

function x300172_GetXP4X10( sceneId, selfId)
    return GetQuestData( sceneId, selfId, MD_DANCERY_XP4X10[ 1], MD_DANCERY_XP4X10[ 2], MD_DANCERY_XP4X10[ 3] )
end

function x300172_SetXP4X10( sceneId, selfId, value)
    SetQuestData( sceneId, selfId, MD_DANCERY_XP4X10[ 1], MD_DANCERY_XP4X10[ 2], MD_DANCERY_XP4X10[ 3], value)
end

function x300172_GetCredit8X10( sceneId, selfId)
    return GetQuestData( sceneId, selfId, MD_DANCERY_CREDIT8X10[ 1], MD_DANCERY_CREDIT8X10[ 2], MD_DANCERY_CREDIT8X10[ 3] )
end

function x300172_SetCredit8X10( sceneId, selfId, value)
    SetQuestData( sceneId, selfId, MD_DANCERY_CREDIT8X10[ 1], MD_DANCERY_CREDIT8X10[ 2], MD_DANCERY_CREDIT8X10[ 3], value)
end

function x300172_GetCredit4X10( sceneId, selfId)
    return GetQuestData( sceneId, selfId, MD_DANCERY_CREDIT4X10[ 1], MD_DANCERY_CREDIT4X10[ 2], MD_DANCERY_CREDIT4X10[ 3] )
end

function x300172_SetCredit4X10( sceneId, selfId, value)
    SetQuestData( sceneId, selfId, MD_DANCERY_CREDIT4X10[ 1], MD_DANCERY_CREDIT4X10[ 2], MD_DANCERY_CREDIT4X10[ 3], value)
end

function x300172_GetMana8X10( sceneId, selfId)
    return GetQuestData( sceneId, selfId, MD_DANCERY_MANA8X10[ 1], MD_DANCERY_MANA8X10[ 2], MD_DANCERY_MANA8X10[ 3] )
end

function x300172_SetMana8X10( sceneId, selfId, value)
    SetQuestData( sceneId, selfId, MD_DANCERY_MANA8X10[ 1], MD_DANCERY_MANA8X10[ 2], MD_DANCERY_MANA8X10[ 3], value)
end

-- BuffID���ƶ�Ӧ��
x300172_g_BuffTable         = {
                                { buffId = 7647, name = "�ܿ˵���",     Get = x300172_GetExp2,       Set = x300172_SetExp2 }, 
                                { buffId = 7648, name = "֥��ʿ",       Get = x300172_GetExp4,       Set = x300172_SetExp4 }, 
                                { buffId = 7649, name = "·��ʮ��",     Get = x300172_GetCredit4,    Set = x300172_SetCredit4 }, 
                                { buffId = 7650, name = "����ʫ���",   Get = x300172_GetCredit8,    Set = x300172_SetCredit8 }, 
                                { buffId = 7645, name = "������ѩ��",   Get = x300172_GetMana8,      Set = x300172_SetMana8 }, 
                                { buffId = 7667, name = "��Ʒ֥��ʿ",   Get = x300172_GetXP8X10,     Set = x300172_SetXP8X10 }, 
                                { buffId = 7666, name = "��Ʒ����ʫ���",   Get = x300172_GetCredit8X10, Set = x300172_SetCredit8X10 }, 
                                { buffId = 7665, name = "��Ʒ������ѩ��",   Get = x300172_GetMana8X10,   Set = x300172_SetMana8X10 }, 
                                { buffId = 7668, name = "��Ʒ�ܿ˵���",   Get = x300172_GetXP4X10,     Set = x300172_SetXP4X10 }, 
                                { buffId = 7669, name = "��Ʒ·��ʮ��",   Get = x300172_GetCredit4X10, Set = x300172_SetCredit4X10 }, 
}
-- �������
x300172_g_MutexTable        = {
                                { buffId = 7647, check = { { buffId = 7648, name = "֥��ʿ" },     { buffId = 7667, name = "��Ʒ֥��ʿ" }, { buffId = 7668, name = "��Ʒ�ܿ˵���" } } },
                                { buffId = 7648, check = { { buffId = 7647, name = "�ܿ˵���" },   { buffId = 7667, name = "��Ʒ֥��ʿ" }, { buffId = 7668, name = "��Ʒ�ܿ˵���" } } },
                                { buffId = 7649, check = { { buffId = 7650, name = "����ʫ���" }, { buffId = 7666, name = "��Ʒ����ʫ���" }, { buffId = 7669, name = "��Ʒ·��ʮ��" } } },
                                { buffId = 7650, check = { { buffId = 7649, name = "·��ʮ��" },   { buffId = 7666, name = "��Ʒ����ʫ���" }, { buffId = 7669, name = "��Ʒ·��ʮ��" } } },
                                { buffId = 7645, check = { { buffId = 7665, name = "��Ʒ������ѩ��" } } },
                                { buffId = 7667, check = { { buffId = 7648, name = "֥��ʿ" },     { buffId = 7647, name = "�ܿ˵���" }, { buffId = 7668, name = "��Ʒ�ܿ˵���" } } },
                                { buffId = 7666, check = { { buffId = 7650, name = "����ʫ���" }, { buffId = 7649, name = "·��ʮ��" }, { buffId = 7669, name = "��Ʒ·��ʮ��" } } },
                                { buffId = 7665, check = { { buffId = 7645, name = "������ѩ��" } } },
                                { buffId = 7668, check = { { buffId = 7648, name = "֥��ʿ" },     { buffId = 7647, name = "�ܿ˵���" }, { buffId = 7667, name = "��Ʒ֥��ʿ" } } },
                                { buffId = 7669, check = { { buffId = 7650, name = "����ʫ���" }, { buffId = 7649, name = "·��ʮ��" }, { buffId = 7666, name = "��Ʒ����ʫ���" } } },
}

function x300172_ProcEnumEvent( sceneId, selfId, NPCId, MissionId)
    AddQuestNumText( sceneId, x300172_g_ScriptId, "�������᡿�洢", 3, 1)
    AddQuestNumText( sceneId, x300172_g_ScriptId, "�������᡿ȡ��", 3, 2)
    AddQuestNumText( sceneId, x300172_g_ScriptId, "�������᡿�棨ȡ��˵��", 13, 3)
end

function x300172_ProcEventEntry( sceneId, selfId, NPCId, idScript, idExt)
    -- print( "*-*-*-*-*-*-*-*-*-*-*" )
    if idExt == 1 then
        BeginQuestEvent( sceneId)
            AddQuestText( sceneId, "#Y��������������" )
            AddQuestText( sceneId, "\t��Ҫ����������Ʒ��" )
            AddQuestNumText( sceneId, x300172_g_ScriptId, "�ܿ˵���", 3, 4)
            AddQuestNumText( sceneId, x300172_g_ScriptId, "֥��ʿ", 3, 5)
            AddQuestNumText( sceneId, x300172_g_ScriptId, "·��ʮ��", 3, 6)
            AddQuestNumText( sceneId, x300172_g_ScriptId, "����ʫ���", 3, 7)
            AddQuestNumText( sceneId, x300172_g_ScriptId, "������ѩ��", 3, 13)
            AddQuestNumText( sceneId, x300172_g_ScriptId, "��Ʒ֥��ʿ", 3, 14)
            AddQuestNumText( sceneId, x300172_g_ScriptId, "��Ʒ����ʫ���", 3, 15)
            AddQuestNumText( sceneId, x300172_g_ScriptId, "��Ʒ������ѩ��", 3, 16)
            AddQuestNumText( sceneId, x300172_g_ScriptId, "��Ʒ�ܿ˵���", 3, 20)
            AddQuestNumText( sceneId, x300172_g_ScriptId, "��Ʒ·��ʮ��", 3, 21)
        EndQuestEvent()
        DispatchQuestEventList( sceneId, selfId, NPCId)
    elseif idExt == 2 then
        BeginQuestEvent( sceneId)
            AddQuestText( sceneId, "#Y��������������" )
            AddQuestText( sceneId, "\t��Ҫȡ��������Ʒ��" )
            local remainTime = x300172_GetExp2( sceneId, selfId)
            AddQuestNumText( sceneId, x300172_g_ScriptId, format( "�ܿ˵���#G��%s��", x300172_GetTimeString( remainTime) ), 3, 8)
            remainTime = x300172_GetExp4( sceneId, selfId)
            AddQuestNumText( sceneId, x300172_g_ScriptId, format( "֥��ʿ#G��%s��", x300172_GetTimeString( remainTime) ), 3, 9)
            remainTime = x300172_GetCredit4( sceneId, selfId)
            AddQuestNumText( sceneId, x300172_g_ScriptId, format( "·��ʮ��#G��%s��", x300172_GetTimeString( remainTime) ), 3, 10)
            remainTime = x300172_GetCredit8( sceneId, selfId)
            AddQuestNumText( sceneId, x300172_g_ScriptId, format( "����ʫ���#G��%s��", x300172_GetTimeString( remainTime) ), 3, 11)
            remainTime = x300172_GetMana8( sceneId, selfId)
            AddQuestNumText( sceneId, x300172_g_ScriptId, format( "������ѩ��#G��%s��", x300172_GetTimeString( remainTime) ), 3, 12)
            remainTime = x300172_GetXP8X10( sceneId, selfId)
            AddQuestNumText( sceneId, x300172_g_ScriptId, format( "��Ʒ֥��ʿ#G��%s��", x300172_GetTimeString( remainTime) ), 3, 17)
            remainTime = x300172_GetCredit8X10( sceneId, selfId)
            AddQuestNumText( sceneId, x300172_g_ScriptId, format( "��Ʒ����ʫ���#G��%s��", x300172_GetTimeString( remainTime) ), 3, 18)
            remainTime = x300172_GetMana8X10( sceneId, selfId)
            AddQuestNumText( sceneId, x300172_g_ScriptId, format( "��Ʒ������ѩ��#G��%s��", x300172_GetTimeString( remainTime) ), 3, 19)
            remainTime = x300172_GetXP4X10( sceneId, selfId)
            AddQuestNumText( sceneId, x300172_g_ScriptId, format( "��Ʒ�ܿ˵���#G��%s��", x300172_GetTimeString( remainTime) ), 3, 22)
            remainTime = x300172_GetCredit4X10( sceneId, selfId)
            AddQuestNumText( sceneId, x300172_g_ScriptId, format( "��Ʒ·��ʮ��#G��%s��", x300172_GetTimeString( remainTime) ), 3, 23)
        EndQuestEvent()
        DispatchQuestEventList( sceneId, selfId, NPCId)
    elseif idExt == 3 then
        BeginQuestEvent( sceneId)
            AddQuestText( sceneId, "#Y��������������" )
            AddQuestText( sceneId, "\t���������뿪�����ᣬ�ֵ����Լ��ľƣ�ѩ�ѣ��˷ѵ���������ͨ���������棬����ÿ����Ʒ��ֻ�ܰ����������10��СʱŶ��" )
        EndQuestEvent()
        DispatchQuestEventList( sceneId, selfId, NPCId)
    elseif idExt == 4 then
        x300172_ShowSaveInfo( sceneId, selfId, NPCId, x300172_g_XPBuffId)
    elseif idExt == 5 then
        x300172_ShowSaveInfo( sceneId, selfId, NPCId, x300172_g_DoubleXPBuffId)
    elseif idExt == 6 then
        x300172_ShowSaveInfo( sceneId, selfId, NPCId, x300172_g_CreditBuffId)
    elseif idExt == 7 then
        x300172_ShowSaveInfo( sceneId, selfId, NPCId, x300172_g_DoubleCreditBuffId)
    elseif idExt == 13 then
        x300172_ShowSaveInfo( sceneId, selfId, NPCId, x300172_g_Mana8)
    elseif idExt == 14 then
        x300172_ShowSaveInfo( sceneId, selfId, NPCId, x300172_g_10H8XP)
    elseif idExt == 15 then
        x300172_ShowSaveInfo( sceneId, selfId, NPCId, x300172_g_10H8Credit)
    elseif idExt == 16 then
        x300172_ShowSaveInfo( sceneId, selfId, NPCId, x300172_g_10H8Mana)
    elseif idExt == 20 then
        x300172_ShowSaveInfo( sceneId, selfId, NPCId, x300172_g_10H4XP)
    elseif idExt == 21 then
        x300172_ShowSaveInfo( sceneId, selfId, NPCId, x300172_g_10H4Credit)
    elseif idExt == 8 then
        x300172_ShowLoadInfo( sceneId, selfId, NPCId, x300172_g_XPBuffId)
    elseif idExt == 9 then
        x300172_ShowLoadInfo( sceneId, selfId, NPCId, x300172_g_DoubleXPBuffId)
    elseif idExt == 10 then
        x300172_ShowLoadInfo( sceneId, selfId, NPCId, x300172_g_CreditBuffId)
    elseif idExt == 11 then
        x300172_ShowLoadInfo( sceneId, selfId, NPCId, x300172_g_DoubleCreditBuffId)
    elseif idExt == 12 then
        x300172_ShowLoadInfo( sceneId, selfId, NPCId, x300172_g_Mana8)
    elseif idExt == 17 then
        x300172_ShowLoadInfo( sceneId, selfId, NPCId, x300172_g_10H8XP)
    elseif idExt == 18 then
        x300172_ShowLoadInfo( sceneId, selfId, NPCId, x300172_g_10H8Credit)
    elseif idExt == 19 then
        x300172_ShowLoadInfo( sceneId, selfId, NPCId, x300172_g_10H8Mana)
    elseif idExt == 22 then
        x300172_ShowLoadInfo( sceneId, selfId, NPCId, x300172_g_10H4XP)
    elseif idExt == 23 then
        x300172_ShowLoadInfo( sceneId, selfId, NPCId, x300172_g_10H4Credit)
    end             
end

function x300172_ProcAcceptCheck( sceneId, selfId, NPCId)
    return 1
end

function x300172_ProcAccept( sceneId, selfId)
    local runtimeData = GetPlayerRuntimeData( sceneId, selfId, RD_COLLECT_HORSE)
    if mod( runtimeData, 10) == 0 then
        x300172_SaveBuff( sceneId, selfId, runtimeData / 10)
    else
        x300172_LoadBuff( sceneId, selfId, floor( runtimeData / 10) )
    end
end

-- ����ת��ΪNСʱM����
function x300172_GetTimeString( minute)
    local strResult = ""

    if minute >= 60 then
        local h = floor( minute / 60)
        local m = mod( minute, 60)
        if m == 0 then
            strResult = format( "%dСʱ", h)
        else
            strResult = format( "%dСʱ%d��", h, m)
        end
    else
        strResult = format( "%d����", minute)
    end

    return strResult
end

-- ����Buff
function x300172_SaveBuff( sceneId, selfId, buffId)
    local saveItem = nil
    for i, item in x300172_g_BuffTable do
        if item.buffId == buffId then
            saveItem = item
            break
        end
    end
    -- ���Buff������ʱ��
    local amountTime = GetImpactContinuanceByDataIndex( sceneId, selfId, buffId)
    if amountTime > 0 then
        -- ʣ��ʱ��(����)
        local remainTime = ( amountTime - GetImpactContinuanceElapsed( sceneId, selfId, buffId) ) / 60000
        -- �Ѿ������ʱ��
        local savedTime = saveItem.Get( sceneId, selfId)
        local newTime = savedTime + remainTime
        if newTime > x300172_g_SaveMaxMinute then
            -- ����Buff
            saveItem.Set( sceneId, selfId, x300172_g_SaveMaxMinute)
            -- �������ϵ�Buffʱ��
            SetImpactContinuanceByDataIndex( sceneId, selfId, buffId, ( newTime - x300172_g_SaveMaxMinute) * 60000)
            ResetImpactContinuanceElapsed( sceneId, selfId, buffId)
            RefreshImpactByDataIndex( sceneId, selfId,buffId)
            Msg2Player( sceneId, selfId, "���Ѿ�����10Сʱ�������ٶ����", 8, 3)
        else
            -- ����Buff
            saveItem.Set( sceneId, selfId, newTime)
            -- ������ϵ�Buffʱ��
            CancelSpecificImpact( sceneId, selfId, buffId)
        end
    else
        Msg2Player( sceneId, selfId, format( "�������Ѿ�û��%s��", saveItem.name), 8, 3)
    end
end

-- �ָ�Buff
function x300172_LoadBuff( sceneId, selfId, buffId)
    local loadItem = nil
    for i, item in x300172_g_BuffTable do
        if item.buffId == buffId then
            loadItem = item
            break
        end
    end

    -- ������
    for i, item in x300172_g_MutexTable do
        if buffId == item.buffId then
            for j, iter in item.check do
                if IsHaveSpecificImpact( sceneId, selfId, iter.buffId) == 1 then
                    Msg2Player( sceneId, selfId, format( "����������#G%s#cffcc00����ȡ��#G%s", iter.name, loadItem.name), 8, 3)
                    return
                end
            end
        end
    end

    local savedTime = loadItem.Get( sceneId, selfId)
    if savedTime == 0 then
        Msg2Player( sceneId, selfId, format( "��û��%s", loadItem.name), 8, 3)
        return
    end
    -- ���Buff������ʱ��
    local amountTime = GetImpactContinuanceByDataIndex( sceneId, selfId, buffId)
    -- ʣ��ʱ��(����)
    local remainTime = ( amountTime - GetImpactContinuanceElapsed( sceneId, selfId, buffId) ) / 60000
    local newTime = remainTime + savedTime
    if newTime > x300172_g_SaveMaxMinute then
        if remainTime == 0 then
            SendSpecificImpactToUnit( sceneId, selfId, selfId, selfId, buffId, 0)
        end
        -- �������ϵ�Buffʱ��
        SetImpactContinuanceByDataIndex( sceneId, selfId, buffId, x300172_g_SaveMaxMinute * 60000)
        ResetImpactContinuanceElapsed( sceneId, selfId, buffId)
        RefreshImpactByDataIndex( sceneId, selfId, buffId)
        -- ���±����ʱ��
        loadItem.Set( sceneId, selfId, newTime - x300172_g_SaveMaxMinute)
        Msg2Player( sceneId, selfId, format( "�����ϵ�%s�Ѵ����ֵ����ʣ��洢#G%s", loadItem.name, x300172_GetTimeString( newTime - x300172_g_SaveMaxMinute) ), 8, 3)
    else
        if remainTime == 0 then
            SendSpecificImpactToUnit( sceneId, selfId, selfId, selfId, buffId, 0)
        end
        -- �������ϵ�Buffʱ��
        SetImpactContinuanceByDataIndex( sceneId, selfId, buffId, newTime * 60000)
        ResetImpactContinuanceElapsed( sceneId, selfId, buffId)
        RefreshImpactByDataIndex( sceneId, selfId, buffId)
        -- ���±����ʱ��
        loadItem.Set( sceneId, selfId, 0)
        Msg2Player( sceneId, selfId, format( "��ȡ�������е�%s", loadItem.name), 8, 2)
    end
end

-- ��ʾ����Buffȷ�Ͻ���
function x300172_ShowSaveInfo( sceneId, selfId, NPCId, buffId)
    BeginQuestEvent( sceneId)
        AddQuestText( sceneId, "#Y��������������" )
        if buffId == x300172_g_XPBuffId then
            AddQuestText( sceneId, "���Ƿ�Ҫ����ܿ˵��᣿" )
        elseif buffId == x300172_g_DoubleXPBuffId then
            AddQuestText( sceneId, "���Ƿ�Ҫ����֥��ʿ��" )
        elseif buffId == x300172_g_CreditBuffId then
            AddQuestText( sceneId, "���Ƿ�Ҫ����·��ʮ����" )
        elseif buffId == x300172_g_DoubleCreditBuffId then
            AddQuestText( sceneId, "���Ƿ�Ҫ��������ʫ��飿" )
        elseif buffId == x300172_g_Mana8 then
            AddQuestText( sceneId, "���Ƿ�Ҫ���������ѩ�ѣ�" )
        elseif buffId == x300172_g_10H8XP then
            AddQuestText( sceneId, "���Ƿ�Ҫ���澫Ʒ֥��ʿ��" )
        elseif buffId == x300172_g_10H4XP then
            AddQuestText( sceneId, "���Ƿ�Ҫ���澫Ʒ�ܿ˵��᣿" )
        elseif buffId == x300172_g_10H8Credit then
            AddQuestText( sceneId, "���Ƿ�Ҫ���澫Ʒ����ʫ��飿" )
        elseif buffId == x300172_g_10H4Credit then
            AddQuestText( sceneId, "���Ƿ�Ҫ���澫Ʒ·��ʮ����" )
        elseif buffId == x300172_g_10H8Mana then
            AddQuestText( sceneId, "���Ƿ�Ҫ���澫Ʒ������ѩ�ѣ�" )
        end
    EndQuestEvent()
    SetPlayerRuntimeData( sceneId, selfId, RD_COLLECT_HORSE, buffId * 10)
    DispatchQuestInfo( sceneId, selfId, NPCId, x300172_g_ScriptId, -1)
end

-- ��ʾȡ��Buffȷ�Ͻ���
function x300172_ShowLoadInfo( sceneId, selfId, NPCId, buffId)
    BeginQuestEvent( sceneId)
        AddQuestText( sceneId, "#Y��������������" )
        if buffId == x300172_g_XPBuffId then
            AddQuestText( sceneId, "���Ƿ�Ҫȡ�ؽܿ˵��᣿" )
        elseif buffId == x300172_g_DoubleXPBuffId then
            AddQuestText( sceneId, "���Ƿ�Ҫȡ��֥��ʿ��" )
        elseif buffId == x300172_g_CreditBuffId then
            AddQuestText( sceneId, "���Ƿ�Ҫȡ��·��ʮ����" )
        elseif buffId == x300172_g_DoubleCreditBuffId then
            AddQuestText( sceneId, "���Ƿ�Ҫȡ������ʫ��飿" )
        elseif buffId == x300172_g_Mana8 then
            AddQuestText( sceneId, "���Ƿ�Ҫȡ�ع�����ѩ�ѣ�" )
        elseif buffId == x300172_g_10H8XP then
            AddQuestText( sceneId, "���Ƿ�Ҫȡ�ؾ�Ʒ֥��ʿ��" )
        elseif buffId == x300172_g_10H4XP then
            AddQuestText( sceneId, "���Ƿ�Ҫȡ�ؾ�Ʒ�ܿ˵��᣿" )
        elseif buffId == x300172_g_10H8Credit then
            AddQuestText( sceneId, "���Ƿ�Ҫȡ�ؾ�Ʒ����ʫ��飿" )
        elseif buffId == x300172_g_10H4Credit then
            AddQuestText( sceneId, "���Ƿ�Ҫȡ�ؾ�Ʒ·��ʮ����" )
        elseif buffId == x300172_g_10H8Mana then
            AddQuestText( sceneId, "���Ƿ�Ҫȡ�ؾ�Ʒ������ѩ�ѣ�" )
        end
    EndQuestEvent()
    SetPlayerRuntimeData( sceneId, selfId, RD_COLLECT_HORSE, buffId * 10 + 1)
	DispatchQuestInfo( sceneId, selfId, NPCId, x300172_g_ScriptId, -1)
end


