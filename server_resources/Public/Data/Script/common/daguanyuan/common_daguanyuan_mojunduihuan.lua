-- �ű���
x310392_g_ScriptId              = 310392
-- ����ID
x310392_g_MissionId             = 9060
-- ������
x310392_g_MissionName           = "����ӡ�һ�"
-- ��ƷID
x310392_g_ItemID                = 11000597
-- ���Ѽ۸�
x310392_g_CostMoney             = 500

function x310392_ProcEnumEvent( sceneId, selfId, NPCId, MissionId)
    AddQuestNumText( sceneId, x310392_g_ScriptId, x310392_g_MissionName, 3, 1)
end

function x310392_ProcEventEntry( sceneId, selfId, NPCId, idScript, idExt)
    if idExt == 1 then
        BeginQuestEvent( sceneId)
            AddQuestText( sceneId, "#Y"..x310392_g_MissionName)
            AddQuestText( sceneId, format( "\t@item_%d#W��ʱװ�����ıر����ߡ�ֻҪ���ܽ��й��콵ħ����������������һ�һ��@item_%d��\n\t#W�Ƿ񻨷�#R500#W�Ľ�/�ֽ�ȡһ��@item_%d#W��", x310392_g_ItemID, x310392_g_ItemID, x310392_g_ItemID) )
        EndQuestEvent()
        DispatchQuestInfo( sceneId, selfId, NPCId, x310392_g_ScriptId, -1)
    end
end

function x310392_ProcAcceptCheck( sceneId, selfId, NPCId)
    local day, week = GetWeek()
    local weekIndex = GetWeekIndex()
    if GetDayOfYear() ~= x310392_GetMD( sceneId, selfId, MD_TJMJ_DATE) then
        Msg2Player( sceneId, selfId, "����컹û�вμ��콵ħ��������ܶһ�", 8, 3)
        return 0
    else
        if x310392_GetMD( sceneId, selfId, MD_MOJUN_WEEK) == weekIndex and x310392_GetMD( sceneId, selfId, MD_MOJUN_DUIHUAN) == 1 then
            Msg2Player( sceneId, selfId, "�㱾���Ѿ��һ���һ�Σ������ٴζһ�", 8, 3)
            return 0
        end

        if x310392_GetMD( sceneId, selfId, MD_TJMJ_TIMES) == 0 then
            Msg2Player( sceneId, selfId, "����컹û�вμ��콵ħ��������ܶһ�", 8, 3)
            return 0
        end
    end

    BeginAddItem( sceneId)
    AddBindItem( sceneId, x310392_g_ItemID, 1)
    if EndAddItem( sceneId, selfId) == 0 then
        Msg2Player( sceneId, selfId, "�����ռ䲻�㣬�޷��һ�", 8, 3)
        return 0
    end

    if GetGoldMode( sceneId, selfId) == 1 then
        if CostMoney( sceneId, selfId, 2, x310392_g_CostMoney,311) ~= 1 then
            if CostMoney(sceneId, selfId, 3, x310392_g_CostMoney) ~= 1 then
                Msg2Player( sceneId, selfId, format( "�����ϵĽ�/�ֽ���#R%d#cffcc00��", x310392_g_CostMoney), 8, 3)
                return 0
            end
        end
    else
        if CostMoney( sceneId, selfId, 3, x310392_g_CostMoney) ~= 1 then
            if CostMoney(sceneId, selfId, 2, x310392_g_CostMoney,311) ~= 1 then
                Msg2Player( sceneId, selfId, format( "�����ϵĽ�/�ֽ���#R%d#cffcc00��", x310392_g_CostMoney), 8, 3)
                return 0
            end
        end
    end

    AddItemListToPlayer( sceneId, selfId)

    x310392_SetMD( sceneId, selfId, MD_MOJUN_DUIHUAN, 1)
    x310392_SetMD( sceneId, selfId, MD_MOJUN_WEEK, weekIndex)

    return 1
end

function x310392_GetMD( sceneId, selfId, mdName)
    return GetQuestData( sceneId, selfId, mdName[ 1], mdName[ 2], mdName[ 3] )
end

function x310392_SetMD( sceneId, selfId, mdName, value)
    SetQuestData( sceneId, selfId, mdName[ 1], mdName[ 2], mdName[ 3], value)
end

function x310392_ProcAccept( sceneId, selfId, NPCId)
end
