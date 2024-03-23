-- �ű���
x310360_g_ScriptId              = 310360
-- item id
x310360_g_Item                  = 12035040

function x310360_ProcEnumEvent( sceneId, selfId, NPCId, MissionId)
    AddQuestNumText( sceneId, x310360_g_ScriptId, "��ȡ��͸����", 3, 1)
end

function x310360_ProcEventEntry( sceneId, selfId, NPCId, idScript, idExt)
    local wday, week = GetWeek()
    if wday ~= 0 and wday ~= 6 then
        Msg2Player( sceneId, selfId, "���������ղ����콱", 8, 3)
        return
    end

    if idExt == 1 then
        -- get own number of item
        local bagIndex = FindFirstBagIndexOfItem( sceneId, selfId, x310360_g_Item)
        if bagIndex < 0 then
            Msg2Player( sceneId, selfId, format( "û��@item_%d#cffcc00�����콱", x310360_g_Item), 8, 3)
            return
        end

        local day = GetItemParam( sceneId, selfId, bagIndex, 4, 2)
        if day ~= GetDayOfYear() then
            Msg2Player( sceneId, selfId, "���ź����������˾���콱�����ѹ�", 8, 3)
            return
        end
        local a = GetItemParam( sceneId, selfId, bagIndex, 8, 1)
        local b = GetItemParam( sceneId, selfId, bagIndex, 10, 1)
        local r = a * 80 + b
        if r == GetCountryParam( sceneId, 1, CD_DAGUANYUAN_CAIPIAO1) or
                r == GetCountryParam( sceneId, 2, CD_DAGUANYUAN_CAIPIAO1) or
                r == GetCountryParam( sceneId, 3, CD_DAGUANYUAN_CAIPIAO1) or
                r == GetCountryParam( sceneId, 0, CD_DAGUANYUAN_CAIPIAO2) or
                r == GetCountryParam( sceneId, 1, CD_DAGUANYUAN_CAIPIAO2) or
                r == GetCountryParam( sceneId, 2, CD_DAGUANYUAN_CAIPIAO2) or
                r == GetCountryParam( sceneId, 3, CD_DAGUANYUAN_CAIPIAO2) then
            BeginQuestEvent( sceneId)
                AddQuestText( sceneId, "#Y��͸��Ʊ" )
                AddQuestText( sceneId, "#Y��ϲ����ñ�����͸��Ʊ��#W���Ƿ���ȡ������" )
                AddQuestMoneyBonus1( sceneId, GetCountryParam( sceneId, 0, CD_DAGUANYUAN_CAIPIAO1) * 1000)
            EndQuestEvent()
            DispatchQuestInfo( sceneId, selfId, NPCId, x310360_g_ScriptId, -1)
        else
            Msg2Player( sceneId, selfId, "���ź���������˾����û���н�", 8, 3)
            return
        end
    end
end

function x310360_ProcAcceptCheck( sceneId, selfId, NPCId)
    local bagIndex = FindFirstBagIndexOfItem( sceneId, selfId, x310360_g_Item)
    if bagIndex < 0 then
        Msg2Player( sceneId, selfId, format( "û��@item_%d#cffcc00�����콱", x310360_g_Item), 8, 3)
        return 0
    end

    local day = GetItemParam( sceneId, selfId, bagIndex, 4, 2)
    if day ~= GetDayOfYear() then
        Msg2Player( sceneId, selfId, "���ź����������˾���콱�����ѹ�", 8, 3)
        return 0
    end

    DelItem( sceneId, selfId, x310360_g_Item, 1)
    GamePlayScriptLog(sceneId, selfId, 1652)
    -- ������
    local reward = GetCountryParam( sceneId, 0, CD_DAGUANYUAN_CAIPIAO1) * 1000
    AddMoney( sceneId, selfId, 1, reward)
    Msg2Player( sceneId, selfId, format( "��ϲ����ñ�����͸��Ʊ�󽱣���ý���#R#{_MONEY%d}#cffcc00������", reward), 8, 2)
    Msg2Player( sceneId, selfId, format( "��ϲ����ñ�����͸��Ʊ�󽱣���ý���#R#{_MONEY%d}#cffcc00����", reward), 8, 3)

    return 1
end

function x310360_ProcAccept( sceneId, selfId, NPCId)
end
