x570056_g_ScriptId = 570056

-- �ɱ������ֵ(����)
x570056_g_SaveMaxMinute     = 600

-- ��˫
x570056_g_BuffId          = 9015

function x570056_ProcEnumEvent( sceneId, selfId, NPCId, MissionId)
	--SendSpecificImpactToUnit( sceneId, selfId, selfId, selfId, x570056_g_BuffId, 0)

	local nTime = GetQuestData( sceneId, selfId, MD_TIANFU_DONGSHUANG[1], MD_TIANFU_DONGSHUANG[2], MD_TIANFU_DONGSHUANG[3])
	
    AddQuestNumText( sceneId, x570056_g_ScriptId, "�����츳��ʱ��", 3, 1)

	if nTime > 0 then
		AddQuestNumText( sceneId, x570056_g_ScriptId, "�ⶳ�츳��ʱ��#G("..x570056_GetTimeString(nTime)..")", 3, 2)
	else
		AddQuestNumText( sceneId, x570056_g_ScriptId, "�ⶳ�츳��ʱ��", 3, 2)
	end

end

function x570056_ProcEventEntry( sceneId, selfId, NPCId, idScript, idExt)
    if idExt == 1 then
        x570056_ShowSaveInfo( sceneId, selfId, NPCId)
    elseif idExt == 2 then
        x570056_ShowLoadInfo( sceneId, selfId, NPCId)
    elseif idExt == 3 then
        BeginQuestEvent( sceneId)
            AddQuestText( sceneId, "#Y�����츳��ʱ��" )
            AddQuestText( sceneId, "\t��Ҫ�����츳��ʱ���𣿶������ʹ����츳��������ʱ�����š�\n\t�����ϣ�����»����Щ������츳��ʱ�䣬����ʹ��#G�ⶳ����#W��\n\tע�⣬�츳��ʱ�������Զ���#R10Сʱ#W��" )
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

-- ����ת��ΪNСʱM����
function x570056_GetTimeString( minute)
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
function x570056_SaveBuff( sceneId, selfId)
    -- ���Buff������ʱ��
    local amountTime = GetImpactContinuanceByDataIndex(sceneId, selfId, x570056_g_BuffId)
    if amountTime > 0 then
        -- ʣ��ʱ��(����)
        local remainTime = ( amountTime - GetImpactContinuanceElapsed( sceneId, selfId, x570056_g_BuffId) ) / 60000
        -- �Ѿ������ʱ��
        local savedTime = GetQuestData( sceneId, selfId, MD_TIANFU_DONGSHUANG[1], MD_TIANFU_DONGSHUANG[2], MD_TIANFU_DONGSHUANG[3] )
        local newTime = savedTime + remainTime
        if newTime > x570056_g_SaveMaxMinute then
            -- ����Buff
            SetQuestData( sceneId, selfId, MD_TIANFU_DONGSHUANG[1], MD_TIANFU_DONGSHUANG[2], MD_TIANFU_DONGSHUANG[3], x570056_g_SaveMaxMinute)
            
           
            -- �������ϵ�Buffʱ��
            SetImpactContinuanceByDataIndex( sceneId, selfId, x570056_g_BuffId, ( newTime - x570056_g_SaveMaxMinute) * 60000)
            ResetImpactContinuanceElapsed( sceneId, selfId, x570056_g_BuffId)
            RefreshImpactByDataIndex( sceneId, selfId,x570056_g_BuffId)
            Msg2Player( sceneId, selfId, "���Ѿ�����10Сʱ�������ٶ����", 8, 3)
        else
            -- ����Buff
            SetQuestData( sceneId, selfId, MD_TIANFU_DONGSHUANG[1], MD_TIANFU_DONGSHUANG[2], MD_TIANFU_DONGSHUANG[3], newTime)
            
            -- ������ϵ�Buffʱ��
            CancelSpecificImpact( sceneId, selfId, x570056_g_BuffId)
        end
    else
        Msg2Player( sceneId, selfId, "�������Ѿ�û�пɶ�����츳��ʱ����", 8, 3)
    end
end

-- �ָ�Buff
function x570056_LoadBuff( sceneId, selfId)

    local savedTime = GetQuestData( sceneId, selfId, MD_TIANFU_DONGSHUANG[1], MD_TIANFU_DONGSHUANG[2], MD_TIANFU_DONGSHUANG[3] )
    if savedTime == 0 then
        Msg2Player( sceneId, selfId, "��û�п��Խⶳ���츳��ʱ��", 8, 3)
        return
    end
    
    -- ���Buff������ʱ��
    local amountTime = GetImpactContinuanceByDataIndex( sceneId, selfId, x570056_g_BuffId)
    -- ʣ��ʱ��(����)
    local remainTime = ( amountTime - GetImpactContinuanceElapsed( sceneId, selfId, x570056_g_BuffId) ) / 60000
    local newTime = remainTime + savedTime
    if newTime > x570056_g_SaveMaxMinute then
    
        if remainTime == 0 then
            SendSpecificImpactToUnit( sceneId, selfId, selfId, selfId, x570056_g_BuffId, 0)
        end
        -- �������ϵ�Buffʱ��
        SetImpactContinuanceByDataIndex( sceneId, selfId, x570056_g_BuffId, newTime * 60000)
        ResetImpactContinuanceElapsed( sceneId, selfId, x570056_g_BuffId)
        RefreshImpactByDataIndex( sceneId, selfId, x570056_g_BuffId)
        -- ���±����ʱ��
        SetQuestData( sceneId, selfId, MD_TIANFU_DONGSHUANG[1], MD_TIANFU_DONGSHUANG[2], MD_TIANFU_DONGSHUANG[3], 0)
        
        Msg2Player( sceneId, selfId, format( "�ɹ���ȡ�츳��ʱ��#G%s", x570056_GetTimeString( x570056_g_SaveMaxMinute) ), 8, 3)
    else
        if remainTime == 0 then
            SendSpecificImpactToUnit( sceneId, selfId, selfId, selfId, x570056_g_BuffId, 0)
        end
        -- �������ϵ�Buffʱ��
        SetImpactContinuanceByDataIndex( sceneId, selfId, x570056_g_BuffId, newTime * 60000)
        ResetImpactContinuanceElapsed( sceneId, selfId, x570056_g_BuffId)
        RefreshImpactByDataIndex( sceneId, selfId, x570056_g_BuffId)
        
        -- ���±����ʱ��
        SetQuestData( sceneId, selfId, MD_TIANFU_DONGSHUANG[1], MD_TIANFU_DONGSHUANG[2], MD_TIANFU_DONGSHUANG[3], 0)
        Msg2Player( sceneId, selfId, "��ⶳ�����ж�����츳��ʱ��", 8, 2)
    end
end

-- ��ʾ����Buffȷ�Ͻ���
function x570056_ShowSaveInfo( sceneId, selfId, NPCId)
    BeginQuestEvent( sceneId)
        AddQuestText( sceneId, "#Y�����츳��ʱ��" )
        AddQuestText( sceneId, "\t��Ҫ�����츳��ʱ���𣿶������ʹ����츳��������ʱ�����š�\n\t�����ϣ�����»����Щ������츳��ʱ�䣬����ʹ��#G�ⶳ����#W��\n\tע�⣬�츳��ʱ�������Զ���#R10Сʱ#W��" )
    EndQuestEvent()
    SetPlayerRuntimeData( sceneId, selfId, RD_COLLECT_HORSE, 1)
    DispatchQuestInfo( sceneId, selfId, NPCId, x570056_g_ScriptId, -1)
end

-- ��ʾȡ��Buffȷ�Ͻ���
function x570056_ShowLoadInfo( sceneId, selfId, NPCId)
    
	local nTime = GetQuestData( sceneId, selfId, MD_TIANFU_DONGSHUANG[1], MD_TIANFU_DONGSHUANG[2], MD_TIANFU_DONGSHUANG[3])
	BeginQuestEvent( sceneId)
        AddQuestText( sceneId, "#Y�ⶳ�츳��ʱ��" )
        AddQuestText( sceneId, "\t���Ƿ�Ҫ�ⶳ�츳��ʱ�䣿�����ڶ�����츳��ʱ��Ϊ��#G("..x570056_GetTimeString(nTime)..")")
    EndQuestEvent()


    SetPlayerRuntimeData( sceneId, selfId, RD_COLLECT_HORSE, 2)
	DispatchQuestInfo( sceneId, selfId, NPCId, x570056_g_ScriptId, -1)
end


