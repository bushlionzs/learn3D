
-------------------------
--***********************
--Const
--***********************
-------------------------

--MisDescBegin

x300160_g_ScriptId 				= 300160
x300160_g_MissionName			= "��������������"
x300160_g_MissionAbandonName	= "�뿪�������᡿"

x300160_g_LevelLess				= 40

x300160_g_AimSceneList	= {
							{ sceneId = 14, x = 31, z = 49, cenx = 32, cenz = 35, r = 9 }
}
-- �����Ὺ��ʱ��2����0����ĵ�N����
x300160_g_OpenTime2 = 1380
-- ������ر�ʱ��2����0����ĵ�N����
x300160_g_EndTime2  = 540
-- �����Ὺ��ʱ��2��Сʱ��
x300160_g_OpenTimeStartH2 = 23
-- �����Ὺ��ʱ��2�����ӡ�
x300160_g_OpenTimeStartM2 = 0
-- ������ر�ʱ��2��Сʱ��
x300160_g_OpenTimeEndH2 = 9
-- ������ر�ʱ��2�����ӡ�
x300160_g_OpenTimeEndM2 = 0
-- ���������ʱ�䣬��������ر�֮ǰ�೤ʱ���ֹ��ҽ���(��λ������)
x300160_g_CloseTime     = 5
--MisDescEnd

x300160_g_MissionInfo           = "\t�������Ǵ󶼵�һ����ɫ�������������뼤�鲢�棡��������ÿ��#G23��00-09:00#W���š�#W\n\t���ڿ���ʱ�����������ʱ������ȡ��#G#{_MONEY%d}#W�������������볡�ѣ������������������Ա���Ʊ���С����Ů�����������������õĽ�����\n\t������°�ťѡ��������������ᣬ��������ر�ǰ#G5����#W�������ܽ��룡���Ŀ��ˣ��Ƿ���Ҫ�����������������᣿"
x300160_g_MissionContinueInfo   = "\t�����������ǳ���л���Ĺ��٣������ѡ���뿪�����ڱ�������ǰ��������ٴν��룬����Ҫ�뿪��������"
-- �������볡��ϵ��
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

x300160_g_ErrorMessage			= "\t����������"
x300160_g_ErrorMessage_Money	= "\t��û���㹻������������"
x300160_g_ErrorMessage_Level	= format("�ܱ�Ǹ�����ĵȼ�����%d�������ܽ���������", x300160_g_LevelLess)

x300160_g_ErrorMessage_OutRange	= "�����������裡"
x300160_g_ErrorMessage_Close	= "\t�ܱ�Ǹ�������Ὺ��ʱ��Ϊÿ��23:00-09:00�����ڿ���ʱ�����볡��"
x300160_g_ErrorMessage_ProtectCar = "\t�ܱ�Ǹ������״̬���ܽ��������ᣡ"
x300160_g_ErrorMessage_HaveBuff = "�ܱ�Ǹ������״̬���ܽ��������ᣡ"
x300160_g_ErrorMessage_Dress    = "���ڴ���ʱװ״̬�²��ܽ��������ᣡ"
x300160_g_ErrorMessage_HideFace = "��������״̬�²��ܽ��������ᣡ"

x300160_g_AddExpMessage = "�����#R����%d��#cEFC800�Ľ���"
x300160_g_AddExpMessage1 = "�����#R����%d��#cEFC800�Ľ���"
x300160_g_AddExpMessage2 = "�����#R����%d��#cEFC800�Ľ���"
x300160_g_ActiveMessage	= "���������ɣ�"
x300160_g_FadeOutMessage= "����״̬��ʧ������Ҫ������Ӧ���߼�����ý���"

-- ����Buff
x300160_g_BaseBuffId        = 7646
-- 2������
x300160_g_XPBuffId          = 7647
-- 4������
x300160_g_DoubleXPBuffId    = 7648
-- 2������
x300160_g_CreditBuffId      = 7649
-- 4������
x300160_g_DoubleCreditBuffId= 7650
-- 4������
x300160_g_4ManaBuffId       = 7644
-- 8������
x300160_g_8ManaBuffId       = 7645
-- 8������ X 10Сʱ
x300160_g_10H8XP            = 7667
-- 8������ X 10Сʱ
x300160_g_10H8Credit        = 7666
-- 8������ X 10Сʱ
x300160_g_10H8Mana          = 7665
-- 4������ X 10Сʱ
x300160_g_10H4XP            = 7668
-- 4������ X 10Сʱ
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

-- ��ֹ�����������Buff���У�����Buff��Ŷ�����Public\Config\std_impact.tab
x300160_g_ForbidArray = {
                            7606, -- ����_��_¥��
                            7605, -- ���г�_��_¥��
							7607, --����_��_¥��
							7608, --���г�_Ů_¥��
							7609, --����_Ů_¥��
							7610, --����_Ů_¥��
							7611, --���г�_��_��ɽ
							7612, --����_��_��ɽ
							7613, --����_��_��ɽ
							7614, --���г�_Ů_��ɽ
							7615, --����_Ů_��ɽ
							7616, --����_Ů_��ɽ
							7617, --���г�_��_����
							7618, --����_��_����
							7619, --����_��_����
							7620, --���г�_Ů_����
							7621, --����_Ů_����
							7622, --����_Ů_����
							7623, --���г�_��_�ػ�
							7624, --����_��_�ػ�
							7625, --����_��_�ػ�
							7626, --���г�_Ů_�ػ�
							7627, --����_Ů_�ػ�
							7628, --����_Ů_�ػ�
                            7516, -- ͯȤ����Buff
                            7517, -- ͯȤ����Buff
}

-- ����Buff��ID
x300160_g_Dancer1_Male      = 7651
x300160_g_Dancer2_Male      = 7652
x300160_g_Dancer3_Male      = 7653
x300160_g_Dancer1_Female    = 7654
x300160_g_Dancer2_Female    = 7655
x300160_g_Dancer3_Female    = 7656

-- Buff������ʱ������
x300160_g_BuffMaxTime       = 36000000

-- �����ʱ�䣨���ӣ������������������������Ҫ�ٴο۷�
x300160_g_MaxInverval       = 840

-- ����T��ÿ������
x300160_g_KickNumber        = 100

x300160_g_AdditionalLevel   = 90

--buff
function x300160_OnUseItem( sceneId, selfId, buffId)
    -- ���Buff������ʱ��
    local amountTime = GetImpactContinuanceByDataIndex( sceneId, selfId, buffId)
    if amountTime > 0 then
        -- ����ʣ��ʱ��
        local remainTime = amountTime - GetImpactContinuanceElapsed( sceneId, selfId, buffId)
        -- ��ʣ��Ļ����ϵ���30����
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

-- ��������ر�ʱ������������������ȫ���߻ش�
function x300160_OnTimerDoingStart( sceneId, actId, Param1, Param2, Param3, Param4, Param5)
    SetSystemTimerTick( sceneId, 300160, "BroadCast", actId, 10 * 1000)
end

function x300160_BroadCast( sceneId, actId, uTime)
    local curTime = GetMinOfDay()

    if curTime > x300160_g_OpenTime2 or curTime < x300160_g_EndTime2 then
        LuaThisScenceM2Wrold( sceneId, "#RӪҵʱ�佫��09��00����", 1, 1)
        SetSystemTimerTick( sceneId, 300160, "BroadCast", actId, 10 * 1000)
    else
    	local nHumanCount = GetScenePlayerCount( sceneId)
        local bContinue = 0

        if nHumanCount > 0 then
            -- ÿ�����T��x300160_g_KickNumber��
            if nHumanCount > x300160_g_KickNumber then
                nHumanCount = x300160_g_KickNumber
                bContinue = 1
            end
            for i = 0, nHumanCount do
                local objId = GetScenePlayerObjId( sceneId,i)
                if objId >= 0 then
                    --�����ֹ����״̬
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
            -- ���û�����Ϲ�5���ٴ����
            if bContinue == 1 then
                SetSystemTimerTick( sceneId, 300160, "BroadCast", actId, 5 * 1000)
            end
        end
    end
end

-- ����ϴν���ʱ��������Ƿ���ͬһ����ʱ���ڣ�����Ƿ���1�����򷵻�0
function x300160_IsSameTime( sceneId, selfId)
    -- ����ϴν���������ʱ��
    local lastTime = x300160_GetEnterMinute( sceneId, selfId)
    local curTime = GetMinOfYear()
    local costEnter = 1
    if curTime < lastTime then
        -- �������
        local year, month, day = GetYearMonthDay()
        if mod( year, 4) == 0 then
            -- ����
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

-- ��������������˳���Ϸ����ߣ��ٴν�����Ϸʱ�Ĵ���
function x300160_ProcMapPlayerNewConnectEnter( sceneId, selfId)
    if x300160_IsOpenTime( 1) == 0 or x300160_IsSameTime( sceneId, selfId) == 0 then
        -- �������ϴν���������Ὺ��ʱ��Ͱѽ�ɫ�����ȥ���Żش�
        -- x300160_ChangeBody( sceneId, selfId, 0, 0)
        -- SetPlayerMutexState( sceneId, selfId, PLAYER_STATE_DANCERY, 0)
        -- local index = random( 1, getn( x300160_g_PosTable) )
        -- NewWorld( sceneId, selfId, 0, x300160_g_PosTable[ index].x, x300160_g_PosTable[ index].z, 300160)
        -- ��һ��T�˱�ǣ���Buff����ɣ�ֱ��T������ɿ�MapServer���ݶ�ʧ
        SetPlayerRuntimeData( sceneId, selfId, RD_DANCERY_BODYID, 1)
        SendSpecificImpactToUnit( sceneId, selfId, selfId, selfId, 8401, 0)
    else
        -- �ָ�����
        x300160_ChangeBody( sceneId, selfId, x300160_GetChangeID( sceneId, selfId), 1)
        -- �ָ�����״̬
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
        -- ���û���״̬
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
	    	local Readme = "�����ϵĻ�������״̬��ʧ��"
	    	Msg2Player(sceneId,selfId,Readme,8,2)
		end
		if buff == 7647 then
	    	local str = x300160_g_FadeOutMessage;
	        BeginQuestEvent( sceneId);
	            AddQuestText( sceneId, str);
	        EndQuestEvent( sceneId);
	        DispatchQuestTips( sceneId, selfId);
	    	local Readme = "�����ϵ�4������״̬��ʧ�������������������ڵľƱ���С����Ů������ܿ˵�����������ý�����"
	    	Msg2Player(sceneId,selfId,Readme,8,2)
		end
		if buff == 7648 or buff == x300160_g_10H8XP then
	    	local str = x300160_g_FadeOutMessage;
	        BeginQuestEvent( sceneId);
	            AddQuestText( sceneId, str);
	        EndQuestEvent( sceneId);
	        DispatchQuestTips( sceneId, selfId);
	    	local Readme = "�����ϵ�8������״̬��ʧ�����������������ڵľƱ���С����Ů������֥��ʿ��������ý�����"
	    	Msg2Player(sceneId,selfId,Readme,8,2)
		end
		if buff == 7649 then
			local str = x300160_g_FadeOutMessage;
	        BeginQuestEvent( sceneId);
	        AddQuestText( sceneId, str);
	        EndQuestEvent( sceneId);
	        DispatchQuestTips( sceneId, selfId);
	    	local Readme = "�����ϵ�4������״̬��ʧ�����������������ڵľƱ���С����Ů������·��ʮ����������ý�����"
	    	Msg2Player(sceneId,selfId,Readme,8,2)
		end
		if buff == 7650 or buff == x300160_g_10H8Credit then
	    	local str = x300160_g_FadeOutMessage;
	        BeginQuestEvent( sceneId);
	            AddQuestText( sceneId, str);
	        EndQuestEvent( sceneId);
	        DispatchQuestTips( sceneId, selfId);
	    	local Readme = "�����ϵ�8������״̬��ʧ�����������������ڵľƱ���С����Ů����������ʫ�����������ý�����"
	    	Msg2Player(sceneId,selfId,Readme,8,2)
		end
        if buff == x300160_g_4ManaBuffId then
            Msg2Player( sceneId, selfId, x300160_g_FadeOutMessage, 8, 3)
	    	Msg2Player( sceneId, selfId, "�����ϵ�����״̬��ʧ�����������������ڵľƱ���С����Ů�������ѩ����������ý�����", 8, 2)
        end
        if buff == x300160_g_8ManaBuffId or buff == x300160_g_10H8Mana then
            Msg2Player( sceneId, selfId, x300160_g_FadeOutMessage, 8, 3)
	    	Msg2Player( sceneId, selfId, "�����ϵ�����״̬��ʧ�����������������ڵľƱ���С����Ů�����������ѩ����������ý�����", 8, 2)
        end
	end
	 if sceneId ~= 14 then
		if buff == 7646 then
			BeginQuestEvent( sceneId);
	        AddQuestText( sceneId, "�����ϵ������������״̬�Ѿ���ʧ��");
	        EndQuestEvent( sceneId);
	        DispatchQuestTips( sceneId, selfId);
	    	local Readme = "�����ϵ������������״̬�Ѿ���ʧ��"
	    	Msg2Player(sceneId,selfId,Readme,8,2)
		end
		
		if buff == 7647 then
			BeginQuestEvent( sceneId);
	        AddQuestText( sceneId, "�����ϵ�����4������״̬�Ѿ���ʧ��");
	        EndQuestEvent( sceneId);
	        DispatchQuestTips( sceneId, selfId);
	    	local Readme = "�����ϵ�����4������״̬�Ѿ���ʧ��"
	    	Msg2Player(sceneId,selfId,Readme,8,2)
		end
		if buff == 7648 or buff == x300160_g_10H8XP then
			BeginQuestEvent( sceneId);
	        AddQuestText( sceneId, "�����ϵ�����8������״̬�Ѿ���ʧ��");
	        EndQuestEvent( sceneId);
	        DispatchQuestTips( sceneId, selfId);
	    	local Readme = "�����ϵ�����8������״̬�Ѿ���ʧ��"
	    	Msg2Player(sceneId,selfId,Readme,8,2)
		end
		if buff == 7649 then
			BeginQuestEvent( sceneId);
	        AddQuestText( sceneId, "�����ϵ�����4������״̬�Ѿ���ʧ��");
	        EndQuestEvent( sceneId);
	        DispatchQuestTips( sceneId, selfId);
	    	local Readme = "�����ϵ�����4������״̬�Ѿ���ʧ��"
	    	Msg2Player(sceneId,selfId,Readme,8,2)
		end
		if buff == 7650 or buff == x300160_g_10H8Credit then
			BeginQuestEvent( sceneId);
	        AddQuestText( sceneId, "�����ϵ�����8������״̬�Ѿ���ʧ��");
	        EndQuestEvent( sceneId);
	        DispatchQuestTips( sceneId, selfId);
	    	local Readme = "�����ϵ�����8������״̬�Ѿ���ʧ��"
	    	Msg2Player(sceneId,selfId,Readme,8,2)
		end
        if buff == x300160_g_4ManaBuffId then
            Msg2Player( sceneId, selfId, "�����ϵ�����״̬��ʧ��", 8, 3)
	    	Msg2Player( sceneId, selfId, "�����ϵ�����״̬��ʧ��", 8, 2)
        end
        if buff == x300160_g_8ManaBuffId or buff == x300160_g_10H8Mana then
            Msg2Player( sceneId, selfId, "�����ϵ�����״̬��ʧ��", 8, 3)
	    	Msg2Player( sceneId, selfId, "�����ϵ�����״̬��ʧ��", 8, 2)
        end
    end
end

-------------------------
--IsInDancery ������������ڷ���1�����򷵻�0
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
    -- �����ҵȼ�
    local level = GetLevel( sceneId, selfId)
	-- �������Ӿ���ֵ��������㹫ʽ��( 1000 * 0.1 * ��ҵȼ�) * ϵ�� / 6��ÿ10���ӣ�
	if level < 70 then
		local xp = 100 * 1.5 * level / 6 * times
		-- ���Ӿ���
		AddExp( sceneId, selfId, xp)
		-- ��ʾ��ʾ��Ϣ
		Msg2Player( sceneId, selfId, format( x300160_g_AddExpMessage, xp), 8, 3)
	end
	if level >=70 and level < 80 then
		local xp = 100 * 2.7 * level / 6 * times
		-- ���Ӿ���
		AddExp( sceneId, selfId, xp)
		-- ��ʾ��ʾ��Ϣ
		Msg2Player( sceneId, selfId, format( x300160_g_AddExpMessage, xp), 8, 3)
	end
	if level >=80 then
		local xp = 100 * 5.4 * level / 6 * times
		-- ���Ӿ���
		AddExp( sceneId, selfId, xp)
		-- ��ʾ��ʾ��Ϣ
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

-- 081224���������Ƿ��������Ὺ��ʱ���ڣ�����1��ʾĿǰ���ڿ���ʱ�䣬����0��ʾ���ڿ���ʱ����
-- bInDanceRoom��1��ʾ���������ڣ�0��ʾ����
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
        -- �������������
		return x300160_OK_ABANDON
	end
	-- �����ҵȼ�
	if GetLevel(sceneId, selfId) < x300160_g_LevelLess then
		return x300160_FAILED_LEVEL, x300160_g_ErrorMessage_Level
	end
	-- ��鵱ǰ�Ƿ��������Ὺ��ʱ��
    if x300160_IsOpenTime( 0) == 0 then
        local strOpenTime = "�ǳ���Ǹ���ٸ��涨���ǵ�Ӫҵʱ��Ϊ#G%02d: %02d��%02d: %02d#cffcf00������Ӫҵʱ��ǰ�����٣�"
        local str = format( strOpenTime, 
                                    x300160_g_OpenTimeStartH2, x300160_g_OpenTimeStartM2, x300160_g_OpenTimeEndH2, x300160_g_OpenTimeEndM2)
        return x300160_FAILED_OPEN, str
    end
    -- ����Ƿ�������״̬
    if IsBusMember( sceneId, selfId) == 1 then
        return x300160_FAILED_YUNBIAO, x300160_g_ErrorMessage_ProtectCar
    end
    -- ������������״̬���������
    if x300160_IsSpecialImpace( sceneId, selfId) == 1 then
        return x300160_FAILED_CHANGEBODY, x300160_g_ErrorMessage_HaveBuff
    end
    -- ����״̬Ҳ���������
    if GetEquipItemID(sceneId, selfId, x300160_g_DressEquip_Pos) ~= -1 then
        return x300160_FAILED_DRESS, x300160_g_ErrorMessage_Dress
    end
    -- ����״̬���ܽ�
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

-- ����������ʱ�Ĳ���
function x300160_EnterScene( sceneId, selfId)
    if sceneId == 14 then
        x300160_ChangeBody( sceneId, selfId, x300160_GetChangeID( sceneId, selfId), 1)
    end
end

-------------------------
--GetEnterFee��������ҵȼ����ؽ�������������ķ���
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
                    AddQuestNumText( sceneId, x300160_g_ScriptId, format( "�任�����ߣ�#{_MONEY%d}��", x300160_GetEnterFee( sceneId, selfId) ),  3, 2)
                    AddQuestNumText( sceneId, x300160_g_ScriptId, format( "�任�����ߣ�#{_MONEY%d}��", x300160_GetEnterFee( sceneId, selfId) ),  3, 3)
                    AddQuestNumText( sceneId, x300160_g_ScriptId, format( "�任�����ߣ�#{_MONEY%d}��", x300160_GetEnterFee( sceneId, selfId) ),  3, 4)
                else                                                 
                    AddQuestNumText( sceneId, x300160_g_ScriptId, "�任������",  3, 2)
                    AddQuestNumText( sceneId, x300160_g_ScriptId, "�任������",  3, 3)
                    AddQuestNumText( sceneId, x300160_g_ScriptId, "�任������",  3, 4)
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

    -- ��õ�������
    local curDay = GetDayOfYear()
    -- ��õ�ǰʱ��(����)
    local curMinute = GetMinOfYear()
    -- �۷ѱ�ǣ���Ǯ��1
    local costEnter = 0
    -- ʱ���鴦��
    if x300160_IsSameTime( sceneId, selfId) == 0 then
        -- �۷�
        if x300160_CostFee( sceneId, selfId) <= 0 then
            -- ����۷�ʧ��
            Msg2Player( sceneId, selfId, x300160_g_ErrorMessage_Money, 8, 3)
            return
        end
        costEnter = 1
        -- ���½���ʱ��
        x300160_SetEnterMinute( sceneId, selfId, curMinute)
    end

    -- ����
    --ReCallHorse( sceneId, selfId)

    local strLog = format( "WTL: %s enter dancery with sw(%d), ww(%d), xp=", GetName( sceneId, selfId), GetShengWang( sceneId, selfId), GetPlayerGoodBadValue( sceneId, selfId) )
    strLog = strLog..GetExp( sceneId, selfId)
    WriteLog( 1, strLog)

    -- ��������
	local aimscene, aimx, aimz = x300160_GetAimSceneInfo(sceneId, selfId);
	NewWorld(sceneId, selfId, aimscene, aimx, aimz, 300160)

    -- ���ý�ֹ����״̬
    -- 091106��Ϊ�����ʹ󶼲���ͬһ��MapServer�����Լӻ���ŵ�core��ProcMapPlayerEnter
    -- SetPlayerMutexState( sceneId, selfId, PLAYER_STATE_DANCERY, 1)

    -- �ӻ���Buff
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
                Msg2Player( sceneId, selfId, "�۷�ʧ�ܣ����Ժ�����", 8, 3)
                return 0
            end
        end
    else
        if CostMoney( sceneId, selfId, 1, money) ~= 1 then
            if CostMoney(sceneId, selfId, 0, money, 306) ~= 1 then
                Msg2Player( sceneId, selfId, "�۷�ʧ�ܣ����Ժ�����", 8, 3)
                return 0
            end
        end
    end

    -- �۷�֮�������ӻ���Buff
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
    --�����ֹ����״̬
    SetPlayerMutexState( sceneId, selfId, PLAYER_STATE_DANCERY, 0)

    -- �ָ�����
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
--ɱ����������
-------------------------
function x300160_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
end

-------------------------
--���������¼�
-------------------------
function x300160_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)
end

-------------------------
--���߸ı�
-------------------------
function x300160_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
end


