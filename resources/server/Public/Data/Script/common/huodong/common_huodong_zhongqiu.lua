-- ���������콱

-- �ű���
x310900_g_ScriptId          = 310900
-- ��͵ȼ�����
x310900_g_MinLevel          = 40

--feast attach
x310900_g_FeastId						= 4
x310900_g_MD_DayCount1				    = MD_ZHONGQIU_DAY1
x310900_g_MD_DayCount2				    = MD_ZHONGQIU_DAY2


-- �����Ʒ��
x310900_g_RandomItemTable   = {
                                { itemId = 11010017, probability = 10, itemName = "������",num = 1 }, 
                                { itemId = 11010015, probability = 40, itemName = "��Ը����" ,num = 3 }, 
                                { itemId = 11990011, probability = 10, itemName = "������" ,num = 1 }, 
                                { itemId = 12041101, probability = 10, itemName = "���в�",num = 1  }, 
                                { itemId = 12030258, probability = 10, itemName = "ȫ���±�",num = 1  }, 
                                { itemId = 12030320, probability = 20, itemName = "СǮ��",num = 2  } 
}

--3ѡ1������һ����Ʒ
x310900_g_OneFromFour       = {
                                12031002,
                                12031003,
                                12031004,
}

-- ÿ�����ȡ����
x310900_g_MaxTimes          = 2


function x310900_IsFeastActive()
    local day = GetDayOfYear()
	if day < 263 or day > 270 or x310900_g_FeastId ~= MD_CURRENT_FEAST_ID then
				return 0
	end
	return 1
end

function x310900_ProcEnumEvent( sceneId, selfId, targetId, MissionId)

		--check feast active
		if x310900_IsFeastActive() ~= 1 then
				return
		end

    local lv = GetLevel( sceneId, selfId)
    if lv < x310900_g_MinLevel then
        return
    end

    local day = GetDayOfYear()
    if day >= 263 and day <= 269 then
        AddQuestNumText( sceneId, x310900_g_ScriptId, "�����콱", 3, 1)
    end
end

function x310900_ProcEventEntry( sceneId, selfId, targetId, MissionId, indexId)

		if x310900_IsFeastActive() ~= 1 then
        Msg2Player( sceneId, selfId, "�û�п���", 8, 3)
        return
    end

    BeginQuestEvent( sceneId)
        AddQuestText( sceneId, "#Y�����콱" )
        AddQuestText( sceneId, "\tֵ������ѽ�֮�ʣ����ɼ�˼��������һ�𻶶������9��21����9��27�գ�ÿ������12��00-12��30������20��00-20��30������������ȡһ��#G����#W��\n\t��ȷ��Ҫ��ȡ�����������" )
    EndQuestEvent()
    DispatchQuestInfo( sceneId, selfId, targetId, x310900_g_ScriptId, -1)
end

function x310900_ProcAcceptCheck( sceneId, selfId, targetId)

		if x310900_IsFeastActive() ~= 1 then
        Msg2Player( sceneId, selfId, "�û�п���", 8, 3)
        return
    end
    
    
    CallScriptFunction(888894,"Feast_SetCurrentId",sceneId,selfId,x310900_g_FeastId)

    local minute = GetMinOfDay()
    local active = nil
    local today = GetDayOfYear()
    if today < 263 or today > 270 then
    	return
    end
    if minute >= 720 and minute < 750 then
    	if GetQuestData( sceneId, selfId, x310900_g_MD_DayCount1[ 1], x310900_g_MD_DayCount1[ 2], x310900_g_MD_DayCount1[ 3] ) ~= today then
    	    active = x310900_g_MD_DayCount1
    	else
	        Msg2Player( sceneId, selfId, "���ʱ�ε������Ѿ���ȡ����", 8, 3)
	        return
    	end

    elseif minute >= 1200 and minute < 1230 then
    	if GetQuestData( sceneId, selfId, x310900_g_MD_DayCount2[ 1], x310900_g_MD_DayCount2[ 2], x310900_g_MD_DayCount2[ 3] ) ~= today then
    	    active = x310900_g_MD_DayCount2
    	else
	        Msg2Player( sceneId, selfId, "���ʱ�ε������Ѿ���ȡ����", 8, 3)
	        return
    	end
    else
        Msg2Player( sceneId, selfId, "���ڲ��ǻʱ��", 8, 3)
        return
    end

    if GetBagSpace( sceneId, selfId) < 3 then
        Msg2Player( sceneId, selfId, format( "�����ռ䲻��3�����޷������Ʒ", 1), 8, 3)
        return
    end

    -- ���ѡ�����Ʒ
    BeginAddItem( sceneId)
    	
    	--first item
	    local rseed = random( 1, 100)
	    local index = 1
	    local dn = 1
	    local up = 1
	    for i, item in x310900_g_RandomItemTable do
	        up = up + item.probability
	        if rseed >= dn and rseed < up then
	            index = i
	            break
	        end
	        dn = dn + item.probability
	    end
	    
	    AddBindItem( sceneId, x310900_g_RandomItemTable[ index ].itemId, x310900_g_RandomItemTable[ index ].num)
	    
	    --second item
	    index = random(1,3)
	    if index < 1 then index = 1 end
	    if index > 3 then index = 3 end
	    AddBindItem( sceneId, x310900_g_OneFromFour[ index ], 3)
    
    if EndAddItem( sceneId, selfId) == 0 then
        Msg2Player( sceneId, selfId, "�����Ʒʧ��", 8, 3)
        return
    end
    Msg2Player( sceneId, selfId, "��ϲ�������������", 8, 3)    
    AddItemListToPlayer( sceneId, selfId)

--    if x310900_g_RandomItemTable[ index].title == 1 then
--        AwardTitle( sceneId, selfId, x310900_g_RandomItemTable[ index].itemId)
--        Msg2Player( sceneId, selfId, format( "�����%s�ƺ�", x310900_g_RandomItemTable[ index].itemName), 8, 2)
--        if x310900_g_RandomItemTable[ index].broadcast == 1 then
--            LuaAllScenceM2Wrold( sceneId, format( "��ϲ%s���������%s�ƺ�", GetName( sceneId, selfId), x310900_g_RandomItemTable[ index].itemName), 5, 1)
--        end
--    else
--        BeginAddItem( sceneId)
--        AddBindItem( sceneId, x310900_g_RandomItemTable[ index].itemId, 1)
--        if EndAddItem( sceneId, selfId) == 0 then
--            Msg2Player( sceneId, selfId, "�����Ʒʧ�ܣ�", 8, 3)
--            return
--        else
--            AddItemListToPlayer( sceneId, selfId)
--        end
--    end

    SetQuestData( sceneId, selfId, active[ 1], active[ 2], active[ 3], today)
end