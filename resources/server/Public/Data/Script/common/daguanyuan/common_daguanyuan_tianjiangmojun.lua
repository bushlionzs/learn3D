-- �ű���
x310365_g_ScriptId          = 310365
-- �����
x310365_g_Name              = "�����ˡ�������ħ"
-- �μӻ����͵ȼ�
x310365_g_MinLevel          = 85
-- ��ʾ�ȼ�����
x310365_g_LessThanMinLevel  = format( "���ֻ��#G%d#cffcc00��������ҿ���", x310365_g_MinLevel)
-- ÿ����ɴ���
x310365_g_MaxTimesInDay     = 20
-- ��ʾ���������������
x310365_g_strOverMaxTimes   = format( "������Ѿ�Ϊ������������#G%d#cffcc00�������ˣ����������ɡ�", x310365_g_MaxTimesInDay)
-- ���ٱ����ռ�
x310365_g_MinBagSpace       = 1
-- ��ʾ�����ռ䲻��
x310365_g_strNotEnoughBag   = format( "���ı����ռ䲻��#G%d#cffcc00�����������������", x310365_g_MinBagSpace)
-- ���ѽ�
x310365_g_CostMoney         = 500
-- ȫ�����ƴ�
x310365_g_GlobalCount       = 0
-- ��Ʒ�������ñ�
x310365_g_ItemTable         = {
                                { itemId = 12041101, name = "���в�" }, 
                                { itemId = 11000300, name = "���ӡ" }, 
                                { itemId = 11990011, name = "������" }, 
                                { itemId = 12041103, name = "������" }, 
                                { itemId = 12030016, name = "�����ټ���" }, 
                                { itemId = 12030031, name = "���з�" }, 
                                { itemId = 11990015, name = "�ر���" }, 
                                { itemId = 12030213, name = "ǿЧ���ֲ�" }, 
                                { itemId = 12030013, name = "֥��ʿ" }, 
                                { itemId = 12030014, name = "����ʫ���" }, 
                                { itemId = 12030017, name = "������ѩ��" }, 
                                { itemId = 11000501, name = "��̴ľ̿" }, 
                                { itemId = 12240002, name = "���ʷ��Ĳ�" }, 
                                { itemId = 11000548, name = "�Ų�ǿ��ʯ" }, 
}
-- �����Ʒʧ��
x310365_g_strAddItemFailed  = "�����Ʒʧ�ܣ���������"
-- СBoss�б�
x310365_g_MonsterTableLittle= {                              
                                { monsterId=	17321	,ai=	1	,aiScript=	902, campId = 21, liveTime = -1 },	
																{ monsterId=	17322	,ai=	1	,aiScript=	902, campId = 21, liveTime = -1 },
																{ monsterId=	17323	,ai=	1	,aiScript=	902, campId = 21, liveTime = -1 },	
																{ monsterId=	17324	,ai=	1	,aiScript=	902, campId = 21, liveTime = -1 },	
																{ monsterId=	17325	,ai=	1	,aiScript=	902, campId = 21, liveTime = -1 },	
																{ monsterId=	17326	,ai=	1	,aiScript=	902, campId = 21, liveTime = -1 },	
																{ monsterId=	17327	,ai=	1	,aiScript=	902, campId = 21, liveTime = -1 },							
																{ monsterId=	17328	,ai=	1	,aiScript=	903, campId = 21, liveTime = -1 },	
																{ monsterId=	17329	,ai=	1	,aiScript=	903, campId = 21, liveTime = -1 },
																{ monsterId=	17330	,ai=	1	,aiScript=	903, campId = 21, liveTime = -1 },	
																{ monsterId=	17331	,ai=	1	,aiScript=	903, campId = 21, liveTime = -1 },	
																{ monsterId=	17332	,ai=	1	,aiScript=	903, campId = 21, liveTime = -1 },	
																{ monsterId=	17333	,ai=	1	,aiScript=	903, campId = 21, liveTime = -1	},	
																{ monsterId=	17320	,ai=	1	,aiScript=	903, campId = 21, liveTime = -1	},
                                
}
-- ��Boss�б�
x310365_g_MonsterTableBig   = {
                                { monsterId = 17340, ai = 1, aiScript = 971, campId = 21, liveTime = -1 }, 
                                { monsterId = 17341, ai = 1, aiScript = 970, campId = 21, liveTime = -1 },
                                { monsterId = 17342, ai = 1, aiScript = 973, campId = 21, liveTime = -1 },
                                { monsterId = 17343, ai = 1, aiScript = 977, campId = 21, liveTime = -1 },
                                { monsterId = 17344, ai = 1, aiScript = 970, campId = 21, liveTime = -1 },
                                
}
x310365_g_BossA             = { monsterId = 17350, ai = 1, aiScript = 973, campId = 21, liveTime = -1 }
x310365_g_BossB             = { monsterId = 17351, ai = 1, aiScript = 973, campId = 21, liveTime = -1 }
-- ����Boss���λ�����ñ�
x310365_g_MonsterPosTable   = {
                                { x = 88 , z = 90  }, 
                                { x = 100, z = 131 }, 
                                { x = 90 , z = 157 }, 
                                { x = 97 , z = 203 }, 
                                { x = 151, z = 197 }, 
                                { x = 192, z = 215 }, 
                                { x = 201, z = 178 }, 
                                { x = 149, z = 160 }, 
                                { x = 170, z = 84  },     
                                { x = 216, z = 120 }, 
                                { x = 127, z = 120 }, 
                                { x = 117, z = 223 }, 
                                { x = 65 , z = 129 }, 
                                { x = 205, z = 50  },     
                                { x = 55 , z = 192 },                                                           
}
-- open flag
x310365_g_IsEnableId        = 1046
-- random reward
x310365_g_RewardTable           = { 11010100, 11010101, 11010102 }

-- ����������˼䡤�������˳���Ϸ����ߣ��ٴν�����Ϸʱ�Ĵ���
function x310365_ProcMapPlayerNewConnectEnter( sceneId, selfId)

	local today = GetDayOfYear()
    local hour = GetHourMinSec()
    
	local lastDay = GetQuestData(sceneId, selfId, MD_DAGUANYUAN_DATE[1], MD_DAGUANYUAN_DATE[2], MD_DAGUANYUAN_DATE[3])
	if hour == 23 or hour < 9 or today ~= lastDay then

		-- �������ϴν�������ֳ�����ʱ��Ͱѽ�ɫ�����ȥ���Żش���
		-- ��һ��T�˱�ǣ���Buff����ɣ�ֱ��T������ɿ�MapServer���ݶ�ʧ
		--CancelSpecificImpact( sceneId, selfId, x310365_g_LanBuff)
		--CancelSpecificImpact( sceneId, selfId, x310365_g_HongBuff)
		--SetPlayerRuntimeData( sceneId, selfId, RD_DANCERY_BODYID, 1)
		SendSpecificImpactToUnit( sceneId, selfId, selfId, selfId, 8400, 0)
	end
end

function x310365_ProcEnumEvent( sceneId, selfId, NPCId, MissionId)
    if GetGameOpenById( x310365_g_IsEnableId) <= 0 then
        return
    end

    AddQuestNumText( sceneId, x310365_g_ScriptId, "��Ҫ����������������", 3, 1)
    AddQuestNumText( sceneId, x310365_g_ScriptId, "��ѯ������������ָ��", 3, 2)
    if x310365_GetMD( sceneId, selfId, MD_TJMJ_DATE) ~= GetDayOfYear() then
        x310365_SetMD( sceneId, selfId, MD_TJMJ_TIMES, 0)
    end
end

function x310365_ProcEventEntry( sceneId, selfId, NPCId, idScript, idExt)
    if GetGameOpenById( x310365_g_IsEnableId) <= 0 then
        return
    end

    if idExt == 1 then
        local exp =GetLevel( sceneId, selfId)*25920
        SetPlayerRuntimeData( sceneId, selfId, RD_COLLECT_HORSE, 1)
        BeginQuestEvent( sceneId)
            AddQuestText( sceneId, "#Y"..x310365_g_Name)
            AddQuestText( sceneId, "\t�������������������������������������ǧ��������\n\t�������������ѡ�������������������ÿ�γɹ��������������������㶼���÷��ľ��齱������ʱҲ��õ�ϡ���ı�����" )
            AddQuestText( sceneId, format("\n#Y��������#W��\n����ֵ��%d��\n�м��ʻ��#G˫������#W��#G���в�#W��#G���ӡ#W��#G������#W��#G������#W��#G�����ټ���#W��#G��λ��#W��#G�ر���#W��#GǿЧ���ֲ�#W��#G֥��ʿ#W��#G����ʫ���#W��#G������ѩ��#W��#G��̴ľ̿#W��#G���ʷ��Ĳ�#W��#G�Ų�ǿ��ʯ#W����ϡ���ߡ�\n \n#GС��ʾ��\nÿ��ÿ���һ�θ�����������������ѣ����ÿ����Ҫ����#R500��#G��/�ֽ���������2�㡣\n \n��������������ָ������#R100#G��#R100#G��������ʱ��ħ�����ᱻ�ͷ��������˼䡤�����ڣ�����ħ�������ô����Ľ�����\n \n��������������ָ������#R400#G��#R400#G��������ʱ�����и��ཱ����ħ�����ᱻ�ͷ��������˼䡤�����ڣ�\n \n��������������ָ������#R10000#Gʱ������#R��������#G��ħ�����ᱻ�ͷ��������˼䡤�����ڣ�\n \n��������������ָ������#R20000#Gʱ������#R��������#G��ħ�����ᱻ�ͷ��������˼䡤�����ڣ���",exp))
        EndQuestEvent()
        DispatchQuestInfo( sceneId, selfId, NPCId, x310365_g_ScriptId, -1)
    elseif idExt == 2 then
        BeginQuestEvent( sceneId)
            AddQuestText( sceneId, "#Y"..x310365_g_Name)
            local rtimes = x310365_g_MaxTimesInDay
            if x310365_GetMD( sceneId, selfId, MD_TJMJ_DATE) == GetDayOfYear() then
                rtimes = x310365_g_MaxTimesInDay - x310365_GetMD( sceneId, selfId, MD_TJMJ_TIMES)
            end
            AddQuestText( sceneId, format( "\t����������������ָ��Ϊ#R%d#W�㣬����컹���Ը�����������#R%d#W��������", x310365_g_GlobalCount, rtimes) )
        EndQuestEvent()
        DispatchQuestEventList( sceneId, selfId, NPCId)
    end
end

function x310365_ProcAcceptCheck( sceneId, selfId, NPCId)
    if GetGameOpenById( x310365_g_IsEnableId) <= 0 then
        return
    end

    local step = GetPlayerRuntimeData( sceneId, selfId, RD_COLLECT_HORSE)
    local today = GetDayOfYear()
    if step == 1 then
        if GetLevel( sceneId, selfId) < x310365_g_MinLevel then
            Msg2Player( sceneId, selfId, x310365_g_LessThanMinLevel, 8, 3)
            return 0
        end

        local times = x310365_GetMD( sceneId, selfId, MD_TJMJ_TIMES)
        -- print( "*-*-*-*-*", times)
        if x310365_GetMD( sceneId, selfId, MD_TJMJ_DATE) == today then
            if times >= x310365_g_MaxTimesInDay then
                Msg2Player( sceneId, selfId, x310365_g_strOverMaxTimes, 8, 3)
                return 0
            end
        else
            x310365_SetMD( sceneId, selfId, MD_TJMJ_TIMES, 0)
            x310365_SetMD( sceneId, selfId, MD_TJMJ_DATE, today)
            local weekIndex = GetWeekIndex()
            if weekIndex ~= x310365_GetMD( sceneId, selfId, MD_MOJUN_WEEK) then
            	x310365_SetMD( sceneId, selfId, MD_MOJUN_DUIHUAN, 0)
            end
            times = 0
        end

        if GetBagSpace( sceneId, selfId) < 1 then
            Msg2Player( sceneId, selfId, x310365_g_strNotEnoughBag, 8, 3)
            return 0
        end

        if times == 0 then
            -- ���
            x310365_GiveReward( sceneId, selfId)
        else
            -- ȷ���Ƿ񻨷ѽ𿨻��ֽ�
            SetPlayerRuntimeData( sceneId, selfId, RD_COLLECT_HORSE, 2)
            BeginQuestEvent( sceneId)
                AddQuestText( sceneId, "#Y"..x310365_g_Name)
                AddQuestText( sceneId, "\t���θ�����������������Ҫ����500�Ľ𿨻��ֽ��Ƿ������" )
            EndQuestEvent()
            DispatchQuestInfo( sceneId, selfId, NPCId, x310365_g_ScriptId, -1)
        end
    elseif step == 2 then
        if GetBagSpace( sceneId, selfId) < 1 then
            Msg2Player( sceneId, selfId, x310365_g_strNotEnoughBag, 8, 3)
            return 0
        end

        if x310365_GetMD( sceneId, selfId, MD_TJMJ_DATE) == today then
            if GetMoney( sceneId, selfId, 2) < x310365_g_CostMoney and GetMoney( sceneId, selfId, 3) < x310365_g_CostMoney then
                Msg2Player( sceneId, selfId, "��Ľ𿨻��ֽ���", 8, 3)
                return 0
            end

            if GetGoldMode( sceneId, selfId) == 1 then
                if CostMoney( sceneId, selfId, 2, x310365_g_CostMoney,323) ~= 1 then
                    if CostMoney( sceneId, selfId, 3, x310365_g_CostMoney) ~= 1 then
                        Msg2Player( sceneId, selfId, "�۳���/�ֽ�ʧ�ܣ����Ժ�����", 8, 3)
                        return 0
                    end
                end
            else
                if CostMoney( sceneId, selfId, 3, x310365_g_CostMoney) ~= 1 then
                    if CostMoney( sceneId, selfId, 2, x310365_g_CostMoney,323) ~= 1 then
                        Msg2Player( sceneId, selfId, "�۳���/�ֽ�ʧ�ܣ����Ժ�����", 8, 3)
                        return 0
                    end
                end
            end
        else
            x310365_SetMD( sceneId, selfId, MD_TJMJ_TIMES, 0)
            x310365_SetMD( sceneId, selfId, MD_TJMJ_DATE, today)
        end

        x310365_GiveReward( sceneId, selfId)
        GamePlayScriptLog(sceneId, selfId, 1681)
    end

    return 1
end

function x310365_GiveReward( sceneId, selfId)
    -- �����ֵ���ʸ�����
    local level = GetLevel( sceneId, selfId)
    local Probability = random( 1, 100)
    local xp = 0
    if Probability <= 75 then
        xp = level*25920
    else
        xp = level*25920*2
    end
    AddExp( sceneId, selfId, xp)
    Msg2Player( sceneId, selfId, format( "���#R%d#cffcc00�㾭�顣", xp), 8, 2)
	if Probability == 100 then
		LuaAllScenceM2Wrold( sceneId, format( "�������ˣ�%s�������˼䡤����������ħ�Ļ������Ļ����%d��ĳ������齱����", GetName( sceneId, selfId), level*25920*3, 1, 1))
	end
    -- �����ֵ���ʸ���Ʒ����

    local index = 0
    local itemId = 0
    Probability = random( 1, 2000)
      if  Probability <=772 then
    		if Probability > 50 and Probability <= 52 then
    		    index = 2
    		elseif Probability > 52 and Probability <= 102 then
    		    index = 3
    		elseif Probability > 102 and Probability <= 152 then
    		    index = 4
    		elseif Probability > 152 and Probability <= 177 then
    		    index = 5
    		elseif Probability > 177 and Probability <= 187 then
    		    index = 6
    		elseif Probability > 187 and Probability <= 287 then
    		    index = 7
    		elseif Probability > 287 and Probability <= 337 then
    		    index = 8
    		elseif Probability > 337 and Probability <= 387 then
    		    index = 9
    		elseif Probability > 387 and Probability <= 412 then
    		    index = 10
    		elseif Probability > 412 and Probability <= 437 then
    		    index = 11
    		elseif Probability > 437 and Probability <= 462 then
    		    index = 12
    		elseif Probability > 462 and Probability <= 512 then
    		    index = 13
    		elseif Probability > 512 and Probability <= 772 then
    		    index = 14
            else
                index = 1
            end
        if index ~= 0 then
            itemId = x310365_g_ItemTable[ index].itemId
        end
    elseif Probability >= 1000 and Probability < 1340 then
        itemId = 11000598
    end
    if itemId ~= 0 then
    		BeginAddItem( sceneId)
        AddItem( sceneId, itemId, 1)
    		local bRes = EndAddItem( sceneId, selfId)
    		if bRes == 0 then
    		    Msg2Player( sceneId, selfId, x310365_g_strAddItemFailed, 8, 3)
    		    return
    		else
    		    AddItemListToPlayer( sceneId, selfId)
    		    if index == 15 then
            LuaThisScenceM2Wrold( sceneId, format( "�������ˣ�%s�������˼䡤����������ħ�Ļ������Ļ����һ��@item_%d��", GetName( sceneId, selfId), itemId), 1, 1)
    		    end
    		end
     end
     
    -- ����ȫ�ּƴ�
    x310365_g_GlobalCount = x310365_g_GlobalCount + 2
    if mod( x310365_g_GlobalCount, 20000) == 0 then
        -- �ٻ�BossB
        local pos = x310365_g_MonsterPosTable[ random( 1, getn( x310365_g_MonsterPosTable) ) ]
        CreateMonster( sceneId, x310365_g_BossB.monsterId, pos.x, pos.z, x310365_g_BossB.ai, x310365_g_BossB.aiScript, x310365_g_ScriptId, -1, x310365_g_BossB.campId, x310365_g_BossB.liveTime)
        LuaThisScenceM2Wrold( sceneId, format( "�ڴ�ҵ�Ŭ���£������ޱȵĴ�ħͷ���������ͷų������������˼䡤�����ڣ�%s��%d�������ˣ���λӢ����ȥ�������", pos.x, pos.z), 1, 1)
        LuaThisScenceM2Wrold( sceneId, format( "��ħͷ���֣���%s��%d��", pos.x, pos.z), 5, 1)
    elseif mod( x310365_g_GlobalCount, 10000) == 0 then
        -- �ٻ�BossA
        local pos = x310365_g_MonsterPosTable[ random( 1, getn( x310365_g_MonsterPosTable) ) ]
        CreateMonster( sceneId, x310365_g_BossA.monsterId, pos.x, pos.z, x310365_g_BossA.ai, x310365_g_BossA.aiScript, x310365_g_ScriptId, -1, x310365_g_BossA.campId, x310365_g_BossA.liveTime)
        LuaThisScenceM2Wrold( sceneId, format( "�ڴ�ҵ�Ŭ���£������ޱȵĴ�ħͷ���������ͷų������������˼䡤�����ڣ�%s��%d�������ˣ���λӢ����ȥ�������", pos.x, pos.z), 1, 1)
        LuaThisScenceM2Wrold( sceneId, format( "��ħͷ���֣���%s��%d��", pos.x, pos.z), 5, 1)
    elseif mod( x310365_g_GlobalCount, 400) == 0 then
        -- �ٻ���Boss
        local boss = x310365_g_MonsterTableBig[ random( 1, getn( x310365_g_MonsterTableBig) ) ]
        local pos = x310365_g_MonsterPosTable[ random( 1, getn( x310365_g_MonsterPosTable) ) ]
        CreateMonster( sceneId, boss.monsterId, pos.x, pos.z, boss.ai, boss.aiScript, x310365_g_ScriptId, -1, boss.campId, boss.liveTime)
        LuaThisScenceM2Wrold( sceneId, format( "�ڴ�ҵ�Ŭ���£������ޱȵĴ�ħͷ���������ͷų������������˼䡤�����ڣ�%s��%d�������ˣ���λӢ����ȥ�������", pos.x, pos.z), 1, 1)
        LuaThisScenceM2Wrold( sceneId, format( "��ħͷ���֣���%s��%d��", pos.x, pos.z), 5, 1)
    elseif mod( x310365_g_GlobalCount, 100) == 0 then
        -- �ٻ�СBoss
        local boss = x310365_g_MonsterTableLittle[ random( 1, getn( x310365_g_MonsterTableLittle) ) ]
        local pos = x310365_g_MonsterPosTable[ random( 1, getn( x310365_g_MonsterPosTable) ) ]
        CreateMonster( sceneId, boss.monsterId, pos.x, pos.z, boss.ai, boss.aiScript, x310365_g_ScriptId, -1, boss.campId, boss.liveTime)
        LuaThisScenceM2Wrold( sceneId, format( "�ڴ�ҵ�Ŭ���£������ޱȵĴ�ħͷ���������ͷų������������˼䡤�����ڣ�%s��%d�������ˣ���λӢ����ȥ�������", pos.x, pos.z), 1, 1)
        LuaThisScenceM2Wrold( sceneId, format( "��ħͷ���֣���%s��%d��", pos.x, pos.z), 5, 1)
    end

    x310365_SetMD( sceneId, selfId, MD_TJMJ_TIMES, x310365_GetMD( sceneId, selfId, MD_TJMJ_TIMES) + 1)

    if random( 1, 100) <= 5 then
        BeginAddItem( sceneId)
        AddItem( sceneId, x310365_g_RewardTable[ random( 1, 3) ], 1)
        if EndAddItem( sceneId, selfId) == 0 then
            Msg2Player( sceneId, selfId, "�����������޷���ö��⽱����Ʒ", 8, 3)
        else
            AddItemListToPlayer( sceneId, selfId)
        end
    end

    Msg2Player( sceneId, selfId, format( "�������ӳɹ�(%d/%d)", x310365_GetMD( sceneId, selfId, MD_TJMJ_TIMES), x310365_g_MaxTimesInDay), 8, 3)
end

function x310365_ProcAccept( sceneId, selfId, NPCId)
end

function x310365_OnDie( sceneId, selfId, killerId)
end

function x310365_GetMD( sceneId, selfId, mdName)
    return GetQuestData( sceneId, selfId, mdName[ 1], mdName[ 2], mdName[ 3] )
end

function x310365_SetMD( sceneId, selfId, mdName, value)
    SetQuestData( sceneId, selfId, mdName[ 1], mdName[ 2], mdName[ 3], value)
end

function x310365_OnTimerDoingStart( sceneId, actId, Param1, Param2, Param3, Param4, Param5)
    if sceneId ~= 40 then
        return
    end

    x310365_g_GlobalCount = 0
end
