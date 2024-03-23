-- �ű���
x310393_g_ScriptId              = 310393
-- ����ID
x310393_g_MissionId             = 9060
-- ������
x310393_g_MissionName           = "����ӡ�һ�"
-- ��ƷID
x310393_g_ItemID                = 11000597
-- ���Ѽ۸�
x310393_g_CostMoney             = 500

function x310393_ProcEnumEvent( sceneId, selfId, NPCId, MissionId)
    AddQuestNumText( sceneId, x310393_g_ScriptId, x310393_g_MissionName, 3, 1)
end

function x310393_ProcEventEntry( sceneId, selfId, NPCId, idScript, idExt)
    if idExt == 1 then
        BeginQuestEvent( sceneId)
            AddQuestText( sceneId, "#Y"..x310393_g_MissionName)
            AddQuestText( sceneId, format( "\t@item_%d#W��ʱװ�����ıر����ߡ�ֻҪ���ܽ��й��ڱ�����ս��������������һ�һ��@item_%d��\n\t#W�Ƿ񻨷�#R500#W�Ľ�/�ֽ�ȡһ��@item_%d#W��", x310393_g_ItemID, x310393_g_ItemID , x310393_g_ItemID) )
        EndQuestEvent()
        DispatchQuestInfo( sceneId, selfId, NPCId, x310393_g_ScriptId, -1)
    end
end

function x310393_ProcAcceptCheck( sceneId, selfId, NPCId)
    local day, week = GetWeek()
    if week ~= x310393_GetMD( sceneId, selfId, MD_WABAO_WEEK) then
        Msg2Player( sceneId, selfId, "��û�н����ڱ�����ս����", 8, 3)
        return 0
    else
        if day == 6 then
            if x310393_GetMD( sceneId, selfId, MD_WABAO_FINISHED) == 0 then
                Msg2Player( sceneId, selfId, "�����û������ڱ�����ս�����ܶһ�", 8, 3)
                return 0
            end
            if x310393_GetMD( sceneId, selfId, MD_WABAO_DUIHUAN1) == 1 then
                Msg2Player( sceneId, selfId, "�㱾���Ѿ��һ���һ�Σ������ٴζһ�", 8, 3)
                return 0
            end
        end
        if day == 0 then
            if x310393_GetMD( sceneId, selfId, MD_WABAO_TIMES) == 0 then
                Msg2Player( sceneId, selfId, "�����û������ڱ�����ս�����ܶһ�", 8, 3)
                return 0
            end
            if x310393_GetMD( sceneId, selfId, MD_WABAO_DUIHUAN1) == 1 then
                Msg2Player( sceneId, selfId, "�㱾���Ѿ��һ���һ�Σ������ٴζһ�", 8, 3)
                return 0
            end
        end
    end

    BeginAddItem( sceneId)
    AddBindItem( sceneId, x310393_g_ItemID, 1)
    if EndAddItem( sceneId, selfId) == 0 then
        Msg2Player( sceneId, selfId, "�����ռ䲻�㣬�޷���ȡ", 8, 3)
        return 0
    end

    if GetGoldMode( sceneId, selfId) == 1 then
        if CostMoney( sceneId, selfId, 2, x310393_g_CostMoney,312) ~= 1 then
            if CostMoney(sceneId, selfId, 3, x310393_g_CostMoney) ~= 1 then
                Msg2Player( sceneId, selfId, format( "�����ϵĽ�/�ֽ���#R%d#cffcc00��", x310393_g_CostMoney), 8, 3)
                return 0
            end
        end
    else
        if CostMoney( sceneId, selfId, 3, x310393_g_CostMoney) ~= 1 then
            if CostMoney(sceneId, selfId, 2, x310393_g_CostMoney,312) ~= 1 then
                Msg2Player( sceneId, selfId, format( "�����ϵĽ�/�ֽ���#R%d#cffcc00��", x310393_g_CostMoney), 8, 3)
                return 0
            end
        end
    end

    AddItemListToPlayer( sceneId, selfId)

        x310393_SetMD( sceneId, selfId, MD_WABAO_DUIHUAN1, 1)

    return 1
end

function x310393_GetMD( sceneId, selfId, mdName)
    return GetQuestData( sceneId, selfId, mdName[ 1], mdName[ 2], mdName[ 3] )
end

function x310393_SetMD( sceneId, selfId, mdName, value)
    SetQuestData( sceneId, selfId, mdName[ 1], mdName[ 2], mdName[ 3], value)
end

function x310393_ProcAccept( sceneId, selfId, NPCId)
end
