-- ʥ����������

x350008_g_ScriptId 					= 350008
-- ��Ʒ�б�
x350008_g_ItemTable                 = {
                                        { { 12030019, 1, 1}, { 12031033, 1, 1}, { 12031034, 1, 1}, { 11010015, 1, 1}, { 12030066, 1, 2}, },
                                        { { 12030067, 1, 1}, { 12041201, 1, 1}, { 12041106, 1, 1}, { 11010015, 1, 1}, { 12031033, 1, 1}, { 12031034, 1, 1} },
                                        { { 12030067, 1, 1}, { 12041201, 1, 1}, { 12041106, 1, 1}, { 11010017, 1, 1}, { 12031033, 1, 1}, { 12031034, 1, 1} },
                                        { { 12030019, 1, 1}, { 12041106, 1, 1}, { 11010015, 1, 1}, { 12030066, 1, 2}, },
}
-- ʱ��Ρ���Ʒ���ñ�
x350008_g_GiftTable                 = {
                                        { tstart = 720,  tend = 730,  }, 
                                        { tstart = 900,  tend = 910,  }, 
                                        { tstart = 1080, tend = 1090,  }, 
                                        { tstart = 1260, tend = 1270,  }, 
}
-- ʥ�����ID
x350008_g_ChristmasPet              = 12050247
-- ʥ����װ10300141
x350008_g_ChristmasItem             = 10300141

--**********************************
--���NPC
--**********************************
function x350008_ProcEnumEvent( sceneId, selfId, targetId, MissionId)
    if GetLevel( sceneId, selfId) < 30 then
        return
    end

    -- �������ָ��ʱ�俪��
    local day = GetDayOfYear()
    local y, m, d = GetYearMonthDay()
    if mod( y, 4) == 0 then
        day = day - 1
    end
    if day > 356 or day < 350 then
        return
    end

    AddQuestNumText( sceneId, x350008_g_ScriptId, "ʥ����������", 3)
end

--**********************************
--ִ��Ĭ���¼�
--**********************************
function x350008_ProcEventEntry( sceneId, selfId, targetId, state, btnindex)
    local curTime = GetMinOfDay()
    local index = 0

    local day = GetDayOfYear()
    if day ~= GetQuestData( sceneId, selfId, MD_GETGIFT_DAY[ 1], MD_GETGIFT_DAY[ 2], MD_GETGIFT_DAY[ 3] ) then
        SetQuestData( sceneId, selfId, MD_GETGIFT1[ 1], MD_GETGIFT1[ 2], MD_GETGIFT1[ 3], 0)
        SetQuestData( sceneId, selfId, MD_GETGIFT2[ 1], MD_GETGIFT2[ 2], MD_GETGIFT2[ 3], 0)
        SetQuestData( sceneId, selfId, MD_GETGIFT3[ 1], MD_GETGIFT3[ 2], MD_GETGIFT3[ 3], 0)
        SetQuestData( sceneId, selfId, MD_GETGIFT4[ 1], MD_GETGIFT4[ 2], MD_GETGIFT4[ 3], 0)
        SetQuestData( sceneId, selfId, MD_GETGIFT_DAY[ 1], MD_GETGIFT_DAY[ 2], MD_GETGIFT_DAY[ 3], day)
    end

    for i, iter in x350008_g_GiftTable do
        if curTime >= iter.tstart and curTime < iter.tend then
            index = i
            break
        end
    end

    if index == 0 then
        BeginQuestEvent( sceneId)
            AddQuestText( sceneId, "#Yʥ����������" )
            AddQuestText( sceneId, "\n\t���ڻ�������ȡʱ�䣬�޷���ȡ��#r" )
            AddQuestText( sceneId, "\t��#G12��17������12��23��#W��ÿ���#G12��00��12��10��15��00��15��10��18��00��18��10��21��00��21��10��#W��λ��ҿ�����������ȡʥ�����\n\t#G��Ը����#W��#G������#W�Ͱ�������Щʥ�������У������ʹ����Ը���ӻ�������ȥʥ��������Ը����" )
        EndQuestEvent()
        DispatchQuestEventList( sceneId, selfId, targetId)
        return
    end

    BeginQuestEvent( sceneId)
        AddQuestText( sceneId, "#Yʥ����������" )
        AddQuestText( sceneId, "\n\t���Ƿ�Ҫ��ȡ���ʱ�ε�ʥ����Ʒ��#r" )
        AddQuestText( sceneId, "\t��#G12��17������12��23��#W��ÿ���#G12��00��12��10��15��00��15��10��18��00��18��10��21��00��21��10��#W��λ��ҿ�����������ȡʥ�����\n\t#G��Ը����#W��#G������#W�Ͱ�������Щʥ�������У������ʹ����Ը���ӻ�������ȥʥ��������Ը����" )
        SetPlayerRuntimeData( sceneId, selfId, RD_COLLECT_HORSE, index)
    EndQuestEvent()
    DispatchQuestInfo( sceneId, selfId, targetId, x350008_g_ScriptId, -1)
end

--**********************************
--���
--**********************************
function x350008_ProcAcceptCheck( sceneId, selfId, targetId)
    local curTime = GetMinOfDay()
    local index = 0
    for i, iter in x350008_g_GiftTable do
        if curTime >= iter.tstart and curTime < iter.tend then
            index = i
            break
        end
    end
    if index == 0 then
        BeginQuestEvent( sceneId)
            AddQuestText( sceneId, "#Yʥ����������" )
            AddQuestText( sceneId, "\t���ڻ�������ȡʱ�䣬�޷���ȡ��#r" )
            AddQuestText( sceneId, "\t��#G12��22������1��4��#W��ÿ���#G12��00��12��10��15��00��15��10��18��00��18��10��21��00��21��10��#W��λ��ҿ�����������ȡʥ�����\n\t#G��Ը����#W��#G������#W�Ͱ�������Щʥ�������У������ʹ����Ը���ӻ�������ȥʥ��������Ը����" )
        EndQuestEvent()
        DispatchQuestEventList( sceneId, selfId, targetId)
        return
    end

    local index = GetPlayerRuntimeData( sceneId, selfId, RD_COLLECT_HORSE)
    if index == 1 then
        if GetQuestData( sceneId, selfId, MD_GETGIFT1[ 1], MD_GETGIFT1[ 2], MD_GETGIFT1[ 3] ) == 1 then
            Msg2Player( sceneId, selfId, "���ʱ��Ľ�Ʒ���Ѿ���ȡ��", 8, 3)
            return
        else
            SetQuestData( sceneId, selfId, MD_GETGIFT1[ 1], MD_GETGIFT1[ 2], MD_GETGIFT1[ 3], 1)
        end
    elseif index == 2 then
        if GetQuestData( sceneId, selfId, MD_GETGIFT2[ 1], MD_GETGIFT2[ 2], MD_GETGIFT2[ 3] ) == 1 then
            Msg2Player( sceneId, selfId, "���ʱ��Ľ�Ʒ���Ѿ���ȡ��", 8, 3)
            return
        else
            SetQuestData( sceneId, selfId, MD_GETGIFT2[ 1], MD_GETGIFT2[ 2], MD_GETGIFT2[ 3], 1)
        end
    elseif index == 3 then
        if GetQuestData( sceneId, selfId, MD_GETGIFT3[ 1], MD_GETGIFT3[ 2], MD_GETGIFT3[ 3] ) == 1 then
            Msg2Player( sceneId, selfId, "���ʱ��Ľ�Ʒ���Ѿ���ȡ��", 8, 3)
            return
        else
            SetQuestData( sceneId, selfId, MD_GETGIFT3[ 1], MD_GETGIFT3[ 2], MD_GETGIFT3[ 3], 1)
        end
    elseif index == 4 then
        if GetQuestData( sceneId, selfId, MD_GETGIFT4[ 1], MD_GETGIFT4[ 2], MD_GETGIFT4[ 3] ) == 1 then
            Msg2Player( sceneId, selfId, "���ʱ��Ľ�Ʒ���Ѿ���ȡ��", 8, 3)
            return
        else
            SetQuestData( sceneId, selfId, MD_GETGIFT4[ 1], MD_GETGIFT4[ 2], MD_GETGIFT4[ 3], 1)
        end
    end

    for i, iter in x350008_g_ItemTable[ index] do
        BeginAddItem( sceneId)
        AddItem( sceneId, iter[ 1], random( iter[ 2], iter[ 3] ) )
        if EndAddItem( sceneId, selfId) > 0 then
            AddItemListToPlayer( sceneId, selfId)
            Msg2Player( sceneId, selfId, format( "������@item_%d#cffcc00��", iter[ 1] ), 8, 2)
            Msg2Player( sceneId, selfId, format( "���ʥ����Ʒ@item_%d", iter[ 1] ), 8, 3)
        else
            Msg2Player( sceneId, selfId, "�޷������Ʒ�������������", 8, 3)
        end
    end

    if index == 3 and random( 1, 100) == 50 then
        BeginAddItem( sceneId)
        AddItem( sceneId, x350008_g_ChristmasPet, 1)
        if EndAddItem( sceneId, selfId) > 0 then
            AddItemListToPlayer( sceneId, selfId)
            Msg2Player( sceneId, selfId, format( "������@item_%d#cffcc00��", x350008_g_ChristmasPet), 8, 2)
            Msg2Player( sceneId, selfId, format( "���ʥ����Ʒ@item_%d", x350008_g_ChristmasPet), 8, 3)
        else
            Msg2Player( sceneId, selfId, "�޷������Ʒ�������������", 8, 3)
        end
    end

    if index == 4 and random( 1, 100) == 50 then
        BeginAddItem( sceneId)
        AddItem( sceneId, x350008_g_ChristmasItem, 1)
        if EndAddItem( sceneId, selfId) > 0 then
            AddItemListToPlayer( sceneId, selfId)
            Msg2Player( sceneId, selfId, format( "������@item_%d#cffcc00��", x350008_g_ChristmasItem), 8, 2)
            Msg2Player( sceneId, selfId, format( "���ʥ����Ʒ@item_%d", x350008_g_ChristmasItem), 8, 3)
        else
            Msg2Player( sceneId, selfId, "�޷������Ʒ�������������", 8, 3)
        end
    end

    local xp = GetLevel( sceneId, selfId) * 2000
    AddExp( sceneId, selfId, xp)
    Msg2Player( sceneId, selfId, format( "������#R%d#cffcc00�㾭�顣", xp), 8, 2)

    BeginQuestEvent( sceneId)
        AddQuestText( sceneId, "����ȡ�����ʱ��εĽ�Ʒ��" )
    EndQuestEvent()
    DispatchQuestEventList( sceneId, selfId, targetId)

    -- write log
    GamePlayScriptLog( sceneId, selfId, 1362)
end

--**********************************
--����
--**********************************
function x350008_ProcAccept( sceneId, selfId)
end

--**********************************
--����
--**********************************
function x350008_ProcQuestAbandon( sceneId, selfId, MissionId)

end

--**********************************
--����
--**********************************
function x350008_OnContinue( sceneId, selfId, targetId)

end

--**********************************
--����Ƿ�����ύ
--**********************************
function x350008_CheckSubmit( sceneId, selfId)

end

--**********************************
--�ύ
--**********************************
function x350008_ProcQuestSubmit( sceneId, selfId, targetId, index, MissionId)

end

--**********************************
--ɱ����������
--**********************************
function x350008_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId)

end

--**********************************
--���������¼�
--**********************************
function x350008_ProcAreaEntered( sceneId, selfId, zoneId, MissionId)
end

