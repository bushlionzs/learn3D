-- �ǹ�

x350007_g_ScriptId 					= 350007


-- ��ͨ��Ը�����������ñ�
x350007_g_OrdinarySeedTable         = {
                                        { useCount = 1,  deplete = 3, scoreDown = 5, scoreUp = 15 }, 
                                        { useCount = 2,  deplete = 3, scoreDown = 5, scoreUp = 15 }, 
                                        { useCount = 3,  deplete = 3, scoreDown = 5, scoreUp = 15 }, 
                                        { useCount = 4,  deplete = 3, scoreDown = 5, scoreUp = 15 }, 
                                        { useCount = 5,  deplete = 3, scoreDown = 5, scoreUp = 15 }, 
                                        { useCount = 6,  deplete = 3, scoreDown = 5, scoreUp = 15 }, 
                                        { useCount = 7,  deplete = 3, scoreDown = 5, scoreUp = 15 }, 
                                        { useCount = 8,  deplete = 3, scoreDown = 5, scoreUp = 15 }, 
                                        { useCount = 9,  deplete = 3, scoreDown = 5, scoreUp = 15 }, 
                                        { useCount = 10, deplete = 3, scoreDown = 5, scoreUp = 15 }, 
                                        { useCount = 11, deplete = 3, scoreDown = 5, scoreUp = 15 }, 
                                        { useCount = 12, deplete = 3, scoreDown = 5, scoreUp = 15 }, 
                                        { useCount = 13, deplete = 3, scoreDown = 5, scoreUp = 15 }, 
                                        { useCount = 14, deplete = 3, scoreDown = 5, scoreUp = 15 }, 
                                        { useCount = 15, deplete = 3, scoreDown = 5, scoreUp = 15 }, 
                                        { useCount = 16, deplete = 3, scoreDown = 5, scoreUp = 15 }, 
}
-- ���������б�
x350007_g_SeedTable					= {
                                        { itemId = 11010015, buttonId = 1, maxTimes = 16, useMode = 0, tableid = x350007_g_OrdinarySeedTable, actName = "��Ը", 
                                          dayMD = MD_HOPESEED_DAY,     timesMD = MD_GOLDHOPESEED_TIMES, name = "�����������Ը" },
                                        { itemId = 11010017, buttonId = 2, maxTimes = 1, useMode = 1, tableid = x350007_g_OrdinarySeedTable, actName = "��", 
                                         dayMD = MD_LUCKSEED_DAY,     timesMD = MD_LUCKSEED_TIMES,     name = "�����������" },
}
-- ���������Ļ����Ʒ���ñ�
x350007_g_LuckySeedTable            = {
                                        { itemId = 12041101, probability = 75000, price = 0.8,  name = "���в�",        }, 
                                        { itemId = 12030202, probability = 25000, price = 1,    name = "�������",          }, 
                                        { itemId = 12030203, probability = 25000, price = 1,    name = "��͢���",          }, 
                                        { itemId = 11990011, probability = 50000, price = 0.99, name = "������",        }, 
                                        { itemId = 12030405, probability = 60000,  price = 2,    name = "�����ػݰ�",        }, 
                                        { itemId = 12030200, probability = 25000,  price = 2,    name = "С����",        },                          
                                        { itemId = 12054300, probability = 25000,  price = 2,    name = "��ͯ��",      }, 
                                        { itemId = 12030201, probability = 50000,  price = 2,    name = "����ʯ",      }, 
                                        { itemId = 12030018, probability = 50000,  price = 4,    name = "�����",          }, 
                                        { itemId = 12030013, probability = 50000,  price = 5,    name = "֥��ʿ",          }, 
                                        { itemId = 11990110, probability = 60000,  price = 5,    name = "ļ����",          }, 
                                        { itemId = 12030031, probability = 50000,  price = 5,    name = "���з�",          }, 
                                        { itemId = 12030016, probability = 50000,   price = 10,   name = "�����ټ���", }, 
                                        { itemId = 12041102, probability = 50000,   price = 10,   name = "�츳��", }, 
                                        { itemId = 12010023, probability = 1000 ,   price = 10,   name = "��������¶", }, 
                                        { itemId = 11990400, probability = 60000,   price = 10,   name = "�ںϼ�", },
                                        { itemId = 12050100, probability = 1000 ,   price = 10,   name = "��Ԫ��", },  
                                     	{ itemId = 12030502, probability = 1000 ,   price = 50,   name = "��͢ʱװ���", },
                                        { itemId = 10340010, probability = 1000 ,   price = 10,   name = "���ʻ����", },
                                     	{ itemId = 12030503, probability = 25000,   price = 50,   name = "������ƽ�����", },
                                        { itemId = 11000300, probability = 1000 ,   price = 10,   name = "���ӡ", },     
                                        { itemId = 11000501, probability = 60000,   price = 10,   name = "��̴ľ̿", }, 
                                        { itemId = 11000902, probability = 50000,   price = 10,   name = "�߼�ϴʯ��", }, 
                                        { itemId = 11000800, probability = 25000,   price = 10,   name = "��ʯ��", }, 
                                        { itemId = 12030018, probability = 25000,   price = 10,   name = "�����", }, 
                                        { itemId = 11000544, probability = 54859,   price = 10,   name = "�����ʯ", }, 
                                        { itemId = 11000598, probability = 25000,   price = 10,   name = "���ʯ", }, 
                                        { itemId = 11010001, probability = 25000,   price = 10,   name = "һ���ʼ�����", }, 
                                        { itemId = 12030504, probability = 14,   price = 50,   name = "��è���������", }, 
                                        { itemId = 12030505, probability = 100,   price = 50,   name = "����ʱװ���", }, 
                                        { itemId = 12030506, probability = 10,   price = 50,   name = "���������������", }, 
                                       	{ itemId = 12030507, probability = 10,   price = 50,   name = "��������һɫ���", }, 
                                       	{ itemId = 12030508, probability = 7,   price = 50,   name = "�����ƴ���Ԫ���", }, 

}
-- �±���
    x350007_g_Yuebing                   = {
                                            { itemId = 12030251, name = "�����±�", lvDown = 30, lvUp = 40       }, 
                                            { itemId = 12030252, name = "��ϲ�±�", lvDown = 40, lvUp = 50       }, 
                                            { itemId = 12030253, name = "�����±�", lvDown = 50, lvUp = 60       }, 
                                            { itemId = 12030254, name = "��ζ�±�", lvDown = 60, lvUp = 70       }, 
                                            { itemId = 12030255, name = "�����±�", lvDown = 70, lvUp = 80       }, 
                                            { itemId = 12030256, name = "�˱��±�", lvDown = 80, lvUp = 90       }, 
}
-- �������ֵ
x350007_g_MaxScore                  = 131072

--**********************************
--���NPC
--**********************************
function x350007_ProcEnumEvent( sceneId, selfId, targetId, MissionId)
    if GetLevel( sceneId, selfId) < 40 then
        return
    end

    local day = GetDayOfYear()
    if day >= 263 and day <= 276 then
	    for i, iter in x350007_g_SeedTable do
	        AddQuestNumText( sceneId, x350007_g_ScriptId, iter.name, 3, iter.buttonId)
	    end
	    AddQuestNumText( sceneId, x350007_g_ScriptId, "��������ֲ�ѯ", 3, 5)
        AddQuestNumText( sceneId, x350007_g_ScriptId, "���ջ����̵�", 10, 6)
        AddQuestNumText( sceneId, x350007_g_ScriptId, "�����̵�", 10, 7)
    end
    -- print( GetQuestData( sceneId, selfId, MD_SEED_SCORE[ 1], MD_SEED_SCORE[ 2], MD_SEED_SCORE[ 3] ) )
end

--**********************************
--ִ��Ĭ���¼�
--**********************************
function x350007_ProcEventEntry( sceneId, selfId, targetId, state, index)
    if index >= 1 and index <= getn( x350007_g_SeedTable) then  
        local strInfo = ""
        local strInfo1 = ""
        local strInfo2 = ""
        local strTitle = "#Y"..x350007_g_SeedTable[ index].name

        if GetDayOfYear() ~= GetQuestData( sceneId, selfId, x350007_g_SeedTable[ index].dayMD[ 1], x350007_g_SeedTable[ index].dayMD[ 2], x350007_g_SeedTable[ index].dayMD[ 3] ) then
            SetQuestData( sceneId, selfId, x350007_g_SeedTable[ index].timesMD[ 1], x350007_g_SeedTable[ index].timesMD[ 2], x350007_g_SeedTable[ index].timesMD[ 3], 0)
            SetQuestData( sceneId, selfId, x350007_g_SeedTable[ index].dayMD[ 1],   x350007_g_SeedTable[ index].dayMD[ 2],   x350007_g_SeedTable[ index].dayMD[ 3], GetDayOfYear() )
        end
        if x350007_g_SeedTable[ index].useMode == 0 then
            local needSeed = GetQuestData( sceneId, selfId, x350007_g_SeedTable[ index].timesMD[ 1], x350007_g_SeedTable[ index].timesMD[ 2], x350007_g_SeedTable[ index].timesMD[ 3] ) + 1
            if  needSeed > x350007_g_SeedTable[ index].maxTimes then
                BeginQuestEvent( sceneId)
                    AddQuestText( sceneId, "#Y��Ը����" )
                    AddQuestText( sceneId, "\n\t��Ը���ӣ���������ϵ���ŵ�����õ�Ը����ʹ����Ը���Ӻ󣬿����ú���һֱ�����������ߡ�" )
                    AddQuestText( sceneId, "\n\t��Ը����ÿ����������Ը#Rʮ��#W�Ρ�#r" )
                    AddQuestText( sceneId, "\t�������Ѿ���Ըʮ�����ˣ�������������" )
                EndQuestEvent()
                DispatchQuestEventList( sceneId, selfId, targetId)
                return
            end
            strInfo = "\t��Ը���ӣ���������ϵ���ŵ�����õ�Ը����ʹ����Ը���Ӻ󣬿����ú���һֱ�����������ߡ�"
            strInfo1 = format( "#GС��ʾ:#G\n\t������Ըÿ��ɽ���ʮ������Ը��ÿ����Ҫ������Ը���ӡ�\t\n\t#W�������ǵ�#R%d#W��ʹ�ã���Ҫ#R3#W��@item_%d#W��", needSeed, x350007_g_SeedTable[ index].itemId)
            strInfo2 = "#Y��������:#W\n\t����� "
        else
            strInfo = "\t�����ӣ����������ĵ����������ף����ʹ��������֮���п��ܻ������ص�����Ŷ��"
            strInfo1 = format( "#GС��ʾ:\n\t#Gÿ�춼���Խ�������ÿ������Ҫһ�������ӣ������ӿ��Դ��콱��ʹ�����á�\t\n\t\n\t#W���Ƿ�Ҫʹ��#R1#W��@item_%d#W?", x350007_g_SeedTable[ index].itemId)
            strInfo2 = "#Y��������:\n\t#W\���ص��� "
        end
        BeginQuestEvent( sceneId)
            --������Ϣ
            AddQuestText( sceneId, strTitle)
            AddQuestText( sceneId, " " )
            AddQuestText( sceneId, strInfo)
            AddQuestText( sceneId, " " )
            AddQuestText( sceneId, strInfo1)
            AddQuestText( sceneId, " " )
            AddQuestText( sceneId, strInfo2)
            AddQuestText( sceneId, " " )
            SetPlayerRuntimeData( sceneId, selfId, RD_COLLECT_HORSE, index)
        EndQuestEvent()
        DispatchQuestInfo( sceneId, selfId, targetId, x350007_g_ScriptId, -1)
    end

    if index == 5 then
        BeginQuestEvent( sceneId)
            AddQuestText( sceneId, "#Y��������ֲ�ѯ" )
            AddQuestText( sceneId, format( "\n\t��Ŀǰ�Ľ��ջ���Ϊ#G%d#W��", GetQuestData( sceneId, selfId, MD_SEED_SCORE[ 1], MD_SEED_SCORE[ 2], MD_SEED_SCORE[ 3] ) ) )
        EndQuestEvent()
        DispatchQuestEventList( sceneId, selfId, targetId)
    end

    if index == 6 then
        DispatchShopItem( sceneId, selfId, targetId, 1104)
    end
    if index == 7 then
        DispatchShopItem( sceneId, selfId, targetId, 1105)
    end
end

-- ����ʹ�ô�������Ƿ���ã�������÷���1�����򷵻�0
function x350007_CheckUseTimes( sceneId, selfId, dayMD, timesMD, maxTimes)
    local result = 1

    if GetDayOfYear() == GetQuestData( sceneId, selfId, dayMD[ 1], dayMD[ 2], dayMD[ 3] ) then
        if GetQuestData( sceneId, selfId, timesMD[ 1], timesMD[ 2], timesMD[ 3] ) >= maxTimes then
            result = 0
        end
    else
        SetQuestData( sceneId, selfId, timesMD[ 1], timesMD[ 2], timesMD[ 3], 0)
    end

    return result
end

--**********************************
--���
--**********************************
function x350007_ProcAcceptCheck( sceneId, selfId, targetId)
    local index = GetPlayerRuntimeData( sceneId, selfId, RD_COLLECT_HORSE)

    for i, iter in x350007_g_SeedTable do
        if index == iter.buttonId then
            -- �������Я������
            local iCount = GetItemCountInBag( sceneId, selfId, iter.itemId)
            if iCount == 0 then
                Msg2Player( sceneId, selfId, format( "��û��@item_%d", iter.itemId), 8, 3)
                return
            end
            -- ��鵱��ʹ�ô���
            if iter.useMode == 0 and x350007_CheckUseTimes( sceneId, selfId, iter.dayMD, iter.timesMD, iter.maxTimes) == 0 then
                Msg2Player( sceneId, selfId, format( "������%s�����Ѵ�ʮ���Σ����ܼ���%s", iter.actName, iter.actName), 8, 3)
                return
            end
            local needSeed = GetQuestData( sceneId, selfId, iter.timesMD[ 1], iter.timesMD[ 2], iter.timesMD[ 3] ) + 1
            if iter.useMode == 0 and iCount < iter.tableid[ needSeed].deplete then
                Msg2Player( sceneId, selfId, format( "����@item_%d#cffcc00����#R%d#cffcc00�ţ��޷�%s", iter.itemId, iter.tableid[ needSeed].deplete, iter.actName), 8, 3)
                return
            end
            local score = GetQuestData( sceneId, selfId, MD_SEED_SCORE[ 1], MD_SEED_SCORE[ 2], MD_SEED_SCORE[ 3] )
            if iter.useMode == 0 and score == x350007_g_MaxScore then
                Msg2Player( sceneId, selfId, format( "���Ļ����Ѵ����ֵ��������ʹ��@item_%d", iter.itemId), 8, 3)
                return
            end
            if iter.useMode == 1 then
                -- ������
                local result = random( 1, 1000000)
                -- print( "*-*-*-*-*"..result)
                local top = 1
                local bottom = 1
                local itemIndex = 1
                for i, item in x350007_g_LuckySeedTable do
                    top = top + item.probability
                    if result >= bottom and result < top then
                        itemIndex = i
                        break
                    end
                    bottom = bottom + item.probability
                end
                local itemId = x350007_g_LuckySeedTable[ itemIndex].itemId
            --- if itemIndex == 1 then
            ---     -- ���ݵȼ�����Ӧ���±�
            ---     local lv = GetLevel( sceneId, selfId)
            ---     for i, item in x350007_g_Yuebing do
            ---         if lv >= item.lvDown and lv < item.lvUp then
            ---             itemId = item.itemId
            ---             break
            ---         end
            ---     end
            --- end
                local isBind = 0
                local bagPos = 0
                for i = 0, 108 do
                	local id = GetItemIDByIndexInBag( sceneId, selfId, i)
                	if id == iter.itemId then
                		if IsItemBind( sceneId, selfId, i) > 0 then
                			isBind = 1
                            bagPos = i
                			break
                		end
                	end
                end
                local broadcast = 0
                local itemname = ""
                if x350007_g_LuckySeedTable[ itemIndex].price >= 45 then
                    broadcast = 1
                    itemname = x350007_g_LuckySeedTable[ itemIndex].name
                end
                BeginAddItem( sceneId) 
                if isBind == 1 then
                	AddBindItem( sceneId, itemId, 1)
                else
	                AddItem( sceneId, itemId, 1)
                end
                if GetBagSpace( sceneId, selfId) > 0 and EndAddItem( sceneId, selfId) > 0 then
                    if isBind == 1 then
                    if DelItemByIndexInBag( sceneId, selfId, bagPos, 1) == 0 then
                        Msg2Player( sceneId, selfId, format( "�ύ@item_%d#cffcc00ʧ��", iter.itemId), 8, 3)
                        return
                        end
                    else
                        if DelItem( sceneId, selfId, iter.itemId, 1) == 0 then
                            Msg2Player( sceneId, selfId, format( "�ύ@item_%d#cffcc00ʧ��", iter.itemId), 8, 3)
                            return
                        end
                    end
                    AddItemListToPlayer( sceneId, selfId)
                    Msg2Player( sceneId, selfId, format( "�������@item_%d#cffcc00��", itemId), 8, 2)
                    BeginQuestEvent( sceneId)
                        AddQuestText( sceneId, "#Y"..iter.name)
                        AddQuestText( sceneId, format( "\n�������@item_%d#W��", itemId) )
                    EndQuestEvent()
                    DispatchQuestEventList( sceneId, selfId, targetId)
                    if broadcast == 1 then
                        LuaAllScenceM2Wrold( sceneId, format( "��ϲ%sʹ�������ӻ����%s", GetName( sceneId, selfId), itemname), 5, 1)
                    end

                    -- write log
                    GamePlayScriptLog( sceneId, selfId, 1372)
                else
                    Msg2Player( sceneId, selfId, "�޷������Ʒ�����������ı���", 8, 3)
                    return
                end
            else
                if DelItem( sceneId, selfId, iter.itemId, iter.tableid[ needSeed].deplete) == 0 then
                    Msg2Player( sceneId, selfId, format( "�ύ@item_%d#cffcc00ʧ��", iter.itemId), 8, 3)
                    return
                end
                -- ��Ը����
                local add = random( iter.tableid[ needSeed].scoreDown, iter.tableid[ needSeed].scoreUp)
                score = score + add
                if score > x350007_g_MaxScore then
                    score = x350007_g_MaxScore
                end
                SetQuestData( sceneId, selfId, MD_SEED_SCORE[ 1], MD_SEED_SCORE[ 2], MD_SEED_SCORE[ 3], score)
                SetFeastScore( sceneId, selfId, GetQuestData( sceneId, selfId, MD_SEED_SCORE[ 1], MD_SEED_SCORE[ 2], MD_SEED_SCORE[ 3] ) )
                Msg2Player( sceneId, selfId, format( "�����#R%d#cffcc00����֣��ܻ���#G%d", add, score), 8, 3)
                BeginQuestEvent( sceneId)
                    AddQuestText( sceneId, "#Y"..iter.name)
                    AddQuestText( sceneId, format( "\n\t��ϲ�����#R%d#W����֣��ܻ���Ϊ#G%d#W�֡�", add, score) )
                EndQuestEvent()
                DispatchQuestEventList( sceneId, selfId, targetId)

                -- write log
                GamePlayScriptLog( sceneId, selfId, 1382)
            end
            local times = GetQuestData( sceneId, selfId, iter.timesMD[ 1], iter.timesMD[ 2], iter.timesMD[ 3] )
            SetQuestData( sceneId, selfId, iter.timesMD[ 1], iter.timesMD[ 2], iter.timesMD[ 3], times + 1)
            break
        end
    end
end

--**********************************
--����
--**********************************
function x350007_ProcAccept( sceneId, selfId)
end

--**********************************
--����
--**********************************
function x350007_ProcQuestAbandon( sceneId, selfId, MissionId)

end

--**********************************
--����
--**********************************
function x350007_OnContinue( sceneId, selfId, targetId)

end

--**********************************
--����Ƿ�����ύ
--**********************************
function x350007_CheckSubmit( sceneId, selfId)

end

--**********************************
--�ύ
--**********************************
function x350007_ProcQuestSubmit( sceneId, selfId, targetId, index, MissionId)

end

--**********************************
--ɱ����������
--**********************************
function x350007_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId)

end

--**********************************
--���������¼�
--**********************************
function x350007_ProcAreaEntered( sceneId, selfId, zoneId, MissionId)
end

--**********************************
--���߸ı�
--**********************************
function x350007_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId)
end

-- ���½��ջ��֣��ڽ��ջ����̵����Ѻ���ô˺�������MD
function x350007_UpdateFeastScore( sceneId, selfId, newScore)
    SetQuestData( sceneId, selfId, MD_SEED_SCORE[ 1], MD_SEED_SCORE[ 2], MD_SEED_SCORE[ 3], newScore)
    SetFeastScore( sceneId, selfId, GetQuestData( sceneId, selfId, MD_SEED_SCORE[ 1], MD_SEED_SCORE[ 2], MD_SEED_SCORE[ 3] ) )
end



