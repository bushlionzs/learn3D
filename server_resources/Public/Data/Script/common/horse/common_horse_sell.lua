--MisDescBegin
--�ű���
x920006_g_ScriptId = 920006


--�����ı�����
x920006_g_MissionName       = "�����ˡ��ռ�ս��"
-- ��������
x920006_g_strCollectHorse   = "\t������Ҫ�����ս��ȥ#G������#W�����ɹ�����������ɻ�ȡ����һ���ġ�������ܲ�׽�����õ��ɹ�������Ի�ȡ8���ı��ꡣ"

x920006_CountrySceneList	= { 50, 150, 250, 350}
--MisDescEnd

-- ����ID�б�
x920006_g_GoodHorseTable    = {  2,  3,  4,  5, 
                                12, 13, 14, 15, 
                                22, 23, 24, 25, 
                                32, 33, 34, 35, 
                                42, 43, 44, 45, 
                                52, 53, 54, 55 
}
-- ��ͨ��ID�б�
x920006_g_CommonHorseTable  = { 1, 11, 21, 31, 41, 51 }
-- ÿ����ཻ�����
x920006_g_MaxTimes          = 10
x920006_g_strOverMaxTimes   = "�㱾���Ѿ�����ʮƥս�������ٽ���"

--**********************************
--������ں���
--**********************************
function x920006_ProcEventEntry( sceneId, selfId, targetId, scriptid, extid)	--����������ִ�д˽ű�
    --print( "*********************-*"..extid)
    
    -- �ж�����Ƿ������
    if GetHorseCount( sceneId, selfId) > 0 then--
        BeginQuestEvent( sceneId)
            AddQuestText( sceneId, "#Y�����ˡ��ռ�ս��" )
            AddQuestText( sceneId, "\t������Ҫ�����ս��ȥ#G������#W����һƥ��������������ɻ�ȡ����������\n\t������ܲ�׽����Ʒ����������Ի�ȡ8���ı��ꡣ\n\t��Ȼ��ս���Я���ȼ�Խ�ߣ���������н��Ҳ�͸��ߡ�" )
        EndQuestEvent()
        DispatchQuestEventList( sceneId, selfId, targetId, x920006_g_ScriptId, x920006_g_MissionName)

        -- ֪ͨ�ͻ�����ʾ�����б���
        BeginUICommand( sceneId);
            UICommand_AddInt( sceneId, x920006_g_ScriptId);
            UICommand_AddInt( sceneId, 0);	--����ID�����һ������
            UICommand_AddInt( sceneId, targetId);
            DispatchUICommand( sceneId, selfId, 101);
        EndUICommand( sceneId)
    else
        BeginQuestEvent( sceneId)
            AddQuestText( sceneId, "#Y�����ˡ��ռ�ս��" )
            AddQuestText( sceneId, "\t���Լ�����������ô�ܹ���ս��������أ�" )
        EndQuestEvent()
        DispatchQuestEventList( sceneId, selfId, targetId, x920006_g_ScriptId, x920006_g_MissionName)
    end
end

--**********************************
--�о��¼�
--**********************************
function x920006_ProcEnumEvent( sceneId, selfId, targetId, MissionId)
    SetPlayerRuntimeData( sceneId, selfId, RD_COLLECT_HORSE_HIGH, 0)
    SetPlayerRuntimeData( sceneId, selfId, RD_COLLECT_HORSE_LOW, 0)
    SetPlayerRuntimeData( sceneId, selfId, RD_COLLECT_HORSE, 0)

    -- �жϹ��ҳ�������ֹ�������
    if x920006_CountrySceneList[ GetCurCountry( sceneId, selfId) + 1] == sceneId then
        AddQuestNumText( sceneId, x920006_g_ScriptId, x920006_g_MissionName, 3)
        BeginUICommand( sceneId)
            DispatchUICommand( sceneId, selfId, 102)
        EndUICommand( sceneId)
    end
end


--********************
--����������
--**********************************
function x920006_ProcAcceptCheck( sceneId, selfId, NPCId)
    --print( "x920006_ProcAcceptCheck" )
    local high = GetPlayerRuntimeData( sceneId, selfId, RD_COLLECT_HORSE_HIGH)
    local low = GetPlayerRuntimeData( sceneId, selfId, RD_COLLECT_HORSE_LOW)
    local nIndex = GetPlayerRuntimeData( sceneId, selfId, RD_COLLECT_HORSE)
    local PetID = GetHorseDataID( sceneId, selfId, nIndex)
    local takeLevel = GetPet_TakeLevel( sceneId, selfId, nIndex)
    local id = 0
    if PetID < 2000 and PetID >=100 then
        id = mod( PetID, 100)
    end

    -- ����ֹ�����ȷ������ǰ������˵��쳣����¿����쵽Ǯ������
    if IsHaveHorse( sceneId, selfId, PetID) == 0 then
        BeginQuestEvent( sceneId)
            AddQuestText( sceneId, "#Y�����ˡ��ռ�ս��" )
            AddQuestText( sceneId, "\t�Ҳ�����Ҫ������" )
        EndQuestEvent()
        DispatchQuestEventList( sceneId, selfId, NPCId, x920006_g_ScriptId, x920006_g_MissionName)
        return
    end

    -- �ж�������
    local bFindGood = 0
    for i, item in x920006_g_GoodHorseTable do
        if id == item then
            bFindGood = 1
            break
        end
    end
    local bFindCommon = 0
    if bFindGood == 0 then
        for i, item in x920006_g_CommonHorseTable do
            if id == item then
                bFindCommon = 1
                break
            end
        end
    end
    
    if bFindCommon ~= 1 and bFindGood ~= 1 then
        Msg2Player( sceneId, selfId, "������ֻ�ռ���ͨ�����Ʒ��", 8, 3)
        return
    end

    -- �������
    local today = GetDayOfYear()
    if x920006_GetMissionDate( sceneId, selfId) == today then
        local times = x920006_GetMissionTimes( sceneId, selfId)
        if times >= x920006_g_MaxTimes then
            Msg2Player( sceneId, selfId, x920006_g_strOverMaxTimes, 8, 3)
            Msg2Player( sceneId, selfId, x920006_g_strOverMaxTimes, 8, 2)
            return
        end
    end

    -- ����
    if FreeHorse( sceneId, selfId, high, low) ~= 1 then
        Msg2Player( sceneId, selfId, "�ռ�ս��ʧ��", 8, 3)
        return
    end

    local today = GetDayOfYear()
    if x920006_GetMissionDate( sceneId, selfId) ~= today then
        -- ��������
        x920006_SetMissionDate( sceneId, selfId, today)
        x920006_SetMissionTimes( sceneId, selfId, 1)
    else
        local times = x920006_GetMissionTimes( sceneId, selfId)
        if times >= x920006_g_MaxTimes then
            Msg2Player( sceneId, selfId, x920006_g_strOverMaxTimes, 8, 3)
            Msg2Player( sceneId, selfId, x920006_g_strOverMaxTimes, 8, 2)
            return
        else
            -- ���µ��콻�����
            x920006_SetMissionTimes( sceneId, selfId, times + 1)
        end
    end

    -- �ж��ǲ�����Ʒ��
    if bFindGood == 1 then
        -- ��Ʒ��
        local money = takeLevel * 80
        AddMoney( sceneId, selfId, 1, money)
        Msg2Player( sceneId, selfId, format( "������#R����#{_MONEY%d}#cffcf00�Ľ���", money), 8, 3)
        Msg2Player( sceneId, selfId, format( "������#R����#{_MONEY%d}#cffcf00�Ľ���", money), 8, 2)
    elseif bFindCommon == 1 then
        -- ��ͨ��
        local money = takeLevel * 10
        AddMoney( sceneId, selfId, 1, money)
        Msg2Player( sceneId, selfId, format( "������#R����#{_MONEY%d}#cffcf00�Ľ���", money), 8, 3)
        Msg2Player( sceneId, selfId, format( "������#R����#{_MONEY%d}#cffcf00�Ľ���", money), 8, 2)
    end

    SetPlayerRuntimeData( sceneId, selfId, RD_COLLECT_HORSE_HIGH, -1)
    SetPlayerRuntimeData( sceneId, selfId, RD_COLLECT_HORSE_LOW, -1)
    SetPlayerRuntimeData( sceneId, selfId, RD_COLLECT_HORSE, -1)

    -- д��־
    GamePlayScriptLog( sceneId, selfId, 401)
end

--**********************************
--����
--**********************************
function x920006_ProcAccept( sceneId, selfId)
end

--**********************************
--����
--**********************************
function x920006_ProcQuestAbandon( sceneId, selfId, MissionId )
end

--**********************************
--����
--**********************************
function x920006_OnContinue( sceneId, selfId, targetId )
end

--**********************************
--����Ƿ�����ύ
--**********************************
function x920006_CheckSubmit( sceneId, selfId )

end

--**********************************
--�ύ
--**********************************
function x920006_ProcQuestSubmit( sceneId, selfId, targetId, selectRadioId, MissionId )

end

--**********************************
--ɱ����������
--**********************************
function x920006_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--���������¼�
--**********************************
function x920006_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--���߸ı�
--**********************************
function x920006_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end

-- �����ύ�ĳ���ID�ж��Ƿ��������Ҫ�󣬲����Ϸ���0����������رճ����б���桢���ط�0ֵ
-- ������
--  sceneId������ID
--  selfId�����ID
--  PetID�������ģ��ID
--  targetId��NPC��id
--  horseGUID_high��GUID��λ
--  horseGUID_low��GUID��λ
--  nIndex�������б�����ֵ
function x920006_OnCommitPet( sceneId, selfId, MissionId, targetId, horseGUID_high, horseGUID_low, nIndex)
    --print( "ս��Id��"..PetID)
    local id = 0
    local PetID = GetHorseDataID( sceneId, selfId, nIndex)
    if PetID < 2000 and PetID >=100 then
        id = mod( PetID, 100)
    end
    local takeLevel = GetPet_TakeLevel( sceneId, selfId, nIndex)
    -- �ж��ύ�����Ƿ����Ҫ��
    local bFindGood = 0
    for i, item in x920006_g_GoodHorseTable do
        if id == item then
            bFindGood = 1
            break
        end
    end
    local bFindCommon = 0
    if bFindGood == 0 then
        for i, item in x920006_g_CommonHorseTable do
            if id == item then
                bFindCommon = 1
                break
            end
        end
    end
    if bFindGood == 1 or bFindCommon == 1 then--
        -- �ж��ǲ�����Ʒ��
        if bFindGood == 1 then
            -- ��Ʒ��
            BeginQuestEvent( sceneId)
                AddQuestText( sceneId, "#Y�����ˡ��ռ�ս��" )
                AddQuestText( sceneId, "\t��Ȼ������������ƥ�����������ң�����÷��Ļر���" )
                AddQuestText( sceneId, " " )
                AddQuestText( sceneId, "#Y�������ݣ�" )
                AddQuestText( sceneId, format( "������#{_MONEY%d}", takeLevel * 80) )
            EndQuestEvent()
        else
            -- ��ͨ��
            BeginQuestEvent( sceneId)
                AddQuestText( sceneId, "#Y�����ˡ��ռ�ս��" )
                AddQuestText( sceneId, "\t�뽫��ƥս�������𣿷��ģ��Ҳ��������ġ�" )
                AddQuestText( sceneId, " " )
                AddQuestText( sceneId, "#Y�������ݣ�" )
                AddQuestText( sceneId, format( "������#{_MONEY%d}", takeLevel * 10) )
            EndQuestEvent()
        end
        DispatchQuestInfo( sceneId, selfId, targetId, x920006_g_ScriptId, -1)

        SetPlayerRuntimeData( sceneId, selfId, RD_COLLECT_HORSE_HIGH, horseGUID_high)
        SetPlayerRuntimeData( sceneId, selfId, RD_COLLECT_HORSE_LOW, horseGUID_low)
        SetPlayerRuntimeData( sceneId, selfId, RD_COLLECT_HORSE, nIndex)

        -- close horse UI
        BeginUICommand( sceneId)
            DispatchUICommand( sceneId, selfId, 102)
        EndUICommand( sceneId)
    else
        -- ��ʾ������Ҫ��
        BeginQuestEvent( sceneId)
            AddQuestText( sceneId, "���ύ����˲���������" )
        EndQuestEvent()
        DispatchQuestTips( sceneId, selfId)
        -- ��ӿͻ������½���ʾ
        Msg2Player( sceneId, selfId, "���ύ����˲���������", 4, 2)
    end
end

function x920006_ProcQuestAccept( sceneId, selfId, targetId, missionId)
    --print( "****************" )
end

function x920006_GetMissionDate( sceneId, selfId)
    return GetQuestData( sceneId, selfId, MD_COLLECTHORSE_DATE[ 1], MD_COLLECTHORSE_DATE[ 2], MD_COLLECTHORSE_DATE[ 3] )
end

function x920006_SetMissionDate( sceneId, selfId, value)
    SetQuestData( sceneId, selfId, MD_COLLECTHORSE_DATE[ 1], MD_COLLECTHORSE_DATE[ 2], MD_COLLECTHORSE_DATE[ 3], value)
end

function x920006_GetMissionTimes( sceneId, selfId)
    return GetQuestData( sceneId, selfId, MD_COLLECTHORSE_TIMES[ 1], MD_COLLECTHORSE_TIMES[ 2], MD_COLLECTHORSE_TIMES[ 3] )
end

function x920006_SetMissionTimes( sceneId, selfId, value)
    SetQuestData( sceneId, selfId, MD_COLLECTHORSE_TIMES[ 1], MD_COLLECTHORSE_TIMES[ 2], MD_COLLECTHORSE_TIMES[ 3], value)
end


