-- �������콱���ж�����

-- �ű���
x310910_g_ScriptId          = 310910
-- ��͵ȼ�����
x310910_g_MinLevel          = 40

--feast attach
x310910_g_FeastId						= 5
x310910_g_MD_DayCount1				    = MD_JINLINGJIANG_DAY1
--x310910_g_MD_DayCount2				    = MD_JINLINGJIANG_DAY2


x310910_g_RandomItemTable0   = {
                               { itemId = 12030013, probability = 140, itemName = "֥��ʿ",num = 2 }, 
                               { itemId = 12041101, probability = 140, itemName = "���в�" ,num = 2 }, 
                               { itemId = 12110206, probability = 140, itemName = "����һ��" ,num = 2 }, 
                               { itemId = 12110207, probability = 140, itemName = "����ֹ��",num = 1  }, 
                               { itemId = 11990050, probability = 85, itemName = "�ػ굤",num = 3  }, 
                               { itemId = 12041103, probability = 85, itemName = "������",num = 5  }, 
                               { itemId = 11990011, probability = 84, itemName = "������",num = 2  },
                               { itemId = 11000501, probability = 85, itemName = "��̴ľ̿",num = 5  }, 
                               { itemId = 12054300, probability = 85, itemName = "��ͯ��",num = 1  }, 
                               { itemId = 12250002, probability = 10, itemName = "��Ʒ֥��ʿ",num = 1  }, 
                               { itemId = 11000300, probability = 5, itemName = "���ӡ",num = 1  }, 
                               { itemId = 12050258, probability = 1, itemName = "��ܽ�����",num = 1  }
}


x310910_g_RandomItemTable1   = {
                               { itemId = 12030013, probability = 1200, itemName = "֥��ʿ",num = 2 }, 
                               { itemId = 12110206, probability = 1200, itemName = "����һ��" ,num = 2 }, 
                               { itemId = 12110207, probability = 1200, itemName = "����ֹ��",num = 1  }, 
                               { itemId = 11000598, probability = 750, itemName = "���ʯ",num = 1  }, 
                               { itemId = 11000597, probability = 750, itemName = "����ӡ",num = 1  },
                               { itemId = 12041108, probability = 900, itemName = "����֮��",num = 1  }, 
                               { itemId = 11010121, probability = 750, itemName = "�߲�ī",num = 1  }, 
                               { itemId = 12041102, probability = 750, itemName = "�츳��",num = 1  }, 
                               { itemId = 12260001, probability = 900, itemName = "�����ط�",num = 1  }, 
                               { itemId = 11000550, probability = 750, itemName = "΢��ǳ�",num = 2  },
                               { itemId = 11010111, probability = 699, itemName = "һ��ƽ��֮��",num = 1  }, 
                               { itemId = 12250002, probability = 100, itemName = "��Ʒ֥��ʿ",num = 1  }, 
                               { itemId = 11000300, probability = 50, itemName = "���ӡ",num = 1  }, 
                               { itemId = 12050260, probability = 1, itemName = "��è������",num = 1  }
}


--3ѡ1������һ����Ʒ
--x310910_g_OneFromFour       = {
--                                12031002,
--                                12031003,
--                                12031004,
--}

-- ÿ�����ȡ����
x310910_g_MaxTimes          = 1


function x310910_IsFeastActive()
    local day = GetDayOfYear()
	if day < 298 or day > 300 or x310910_g_FeastId ~= MD_CURRENT_FEAST_ID then
				return 0
	end
	return 1
end

function x310910_ProcEnumEvent( sceneId, selfId, targetId, MissionId)

		--check feast active
		if x310910_IsFeastActive() ~= 1 then
				return
		end

    local lv = GetLevel( sceneId, selfId)
    if lv < x310910_g_MinLevel then
        return
    end

    local day = GetDayOfYear()
    if day >= 298 and day <= 300 then
        AddQuestNumText( sceneId, x310910_g_ScriptId, "�������콱���ж�����", 3, 1)
    end
end

function x310910_ProcEventEntry( sceneId, selfId, targetId, MissionId, indexId)

		if x310910_IsFeastActive() ~= 1 then
        Msg2Player( sceneId, selfId, "�û�п���", 8, 3)
        return
    end

    BeginQuestEvent( sceneId)
        AddQuestText( sceneId, "#Y�������콱���ж�����" )
        AddQuestText( sceneId, "\tֵ�˽����ջ�ļ��ڣ����ɼ�˼��2��ϲ��#G���ά#W�󽱡�\n\tΪ�˻��������Ҷԡ��ɼ�˼��2���Ķ���֧�֣�#R��10��26����10��28�գ�ÿ������20��00-20��30#W������#G40��#W���ϵ���Ҷ�������ȡһ��#G�ж�����#W��\n\t��ȷ��Ҫ��ȡ�ж�����������" )
    EndQuestEvent()
    DispatchQuestInfo( sceneId, selfId, targetId, x310910_g_ScriptId, -1)
end

function x310910_ProcAcceptCheck( sceneId, selfId, targetId)

		if x310910_IsFeastActive() ~= 1 then
        Msg2Player( sceneId, selfId, "�û�п���", 8, 3)
        return
    end
    
    
    CallScriptFunction(888894,"Feast_SetCurrentId",sceneId,selfId,x310910_g_FeastId)

    local minute = GetMinOfDay()
    local active = nil
    local today = GetDayOfYear()
    if today < 298 or today > 300 then
    	return
    end
    if minute >= 1200 and minute < 1230 then
    	if GetQuestData( sceneId, selfId, x310910_g_MD_DayCount1[ 1], x310910_g_MD_DayCount1[ 2], x310910_g_MD_DayCount1[ 3] ) ~= today then
    	    active = x310910_g_MD_DayCount1
    	else
	        Msg2Player( sceneId, selfId, "������������Ѿ���ȡ����", 8, 3)
	        return
    	end

    --elseif minute >= 1200 and minute < 1230 then
    --	if GetQuestData( sceneId, selfId, x310910_g_MD_DayCount2[ 1], x310910_g_MD_DayCount2[ 2], x310910_g_MD_DayCount2[ 3] ) ~= today then
    --	    active = x310910_g_MD_DayCount2
    --	else
	  --      Msg2Player( sceneId, selfId, "���ʱ�ε������Ѿ���ȡ����", 8, 3)
	  --      return
    --	end
    else
        Msg2Player( sceneId, selfId, "�ܱ�Ǹ���������ʱ��Ϊ#R20��00��20��30#cffcf00", 8, 3)
        return
    end

    if GetBagSpace( sceneId, selfId) < 2 then
        Msg2Player( sceneId, selfId, format( "�����ռ䲻��2�����޷������Ʒ", 1), 8, 3)
        return
    end
          
    AddMoney( sceneId, selfId, 1, 150000) 
          
    if GetLevel( sceneId, selfId) <80 then      
    		-- ���ѡ�����Ʒ
    		BeginAddItem( sceneId)
    			
    			--first item
	  		  local rseed = random( 1, 1000)
	  		  local index = 1
	  		  local dn = 1
	  		  local up = 1
	  		  for i, item in x310910_g_RandomItemTable0 do
	  		      up = up + item.probability
	  		      if rseed >= dn and rseed < up then
	  		          index = i
	  		          break
	  		      end
	  		      dn = dn + item.probability
	  		  end
	  		  
	  		  AddBindItem( sceneId, x310910_g_RandomItemTable0[ index ].itemId, x310910_g_RandomItemTable0[ index ].num)
	  		  
	  		  --second item
	  		  --index = random(1,3)
	  		  --if index < 1 then index = 1 end
	  		  --if index > 3 then index = 3 end
	  		  
	  		  AddBindItem( sceneId, 12031002, 3)
    		
    		if EndAddItem( sceneId, selfId) == 0 then
    		    Msg2Player( sceneId, selfId, "�����Ʒʧ��", 8, 3)
    		    return
    		end
    		
    		if x310910_g_RandomItemTable0[ index ].itemId ==12250002 then
    			local msg = format( "��ϲ#R%s#cffcc00�ڸж������콱��У����#G��Ʒ֥��ʿ#cffcc00��", GetName( sceneId, selfId) )
    			LuaAllScenceM2Wrold (sceneId , msg , 5, 1)
    		end
    			
    		if x310910_g_RandomItemTable0[ index ].itemId ==11000300 then
    			local msg = format( "��ϲ#R%s#cffcc00�ڸж������콱��У����#G���ӡ#cffcc00��", GetName( sceneId, selfId) )
    			LuaAllScenceM2Wrold (sceneId , msg , 5, 1)
    		end	
    			
    		if x310910_g_RandomItemTable0[ index ].itemId ==12050258 then
    			local msg = format( "��ϲ#R%s#cffcc00�ڸж������콱��У����#G��ܽ�����#cffcc00��", GetName( sceneId, selfId) )
    			LuaAllScenceM2Wrold (sceneId , msg , 5, 1)
    		end	    			
    			
    		Msg2Player( sceneId, selfId, "��ϲ������˸ж��������", 8, 3)    
    		AddItemListToPlayer( sceneId, selfId)
    		
		else
    		BeginAddItem( sceneId)
    			
    			--first item
	  		  local rseed = random( 1, 10000)
	  		  local index = 1
	  		  local dn = 1
	  		  local up = 1
	  		  for i, item in x310910_g_RandomItemTable1 do
	  		      up = up + item.probability
	  		      if rseed >= dn and rseed < up then
	  		          index = i
	  		          break
	  		      end
	  		      dn = dn + item.probability
	  		  end
	  		  
	  		  AddBindItem( sceneId, x310910_g_RandomItemTable1[ index ].itemId, x310910_g_RandomItemTable1[ index ].num)
	  		  
	  		  --second item
	  		  --index = random(1,3)
	  		  --if index < 1 then index = 1 end
	  		  --if index > 3 then index = 3 end
	  		  AddBindItem( sceneId, 12031002, 3)
    		
    		if EndAddItem( sceneId, selfId) == 0 then
    		    Msg2Player( sceneId, selfId, "�����Ʒʧ��", 8, 3)
    		    return
    		end
    		
    		if x310910_g_RandomItemTable1[ index ].itemId ==12250002 then
    			local msg = format( "��ϲ#R%s#cffcc00�ڸж������콱��У����#G��Ʒ֥��ʿ#cffcc00��", GetName( sceneId, selfId) )
    			LuaAllScenceM2Wrold (sceneId , msg , 5, 1)
    		end
    			
    		if x310910_g_RandomItemTable1[ index ].itemId ==11000300 then
    			local msg = format( "��ϲ#R%s#cffcc00�ڸж������콱��У����#G���ӡ#cffcc00��", GetName( sceneId, selfId) )
    			LuaAllScenceM2Wrold (sceneId , msg , 5, 1)
    		end	
    			
    		if x310910_g_RandomItemTable1[ index ].itemId ==12050260 then
    			local msg = format( "��ϲ#R%s#cffcc00�ڸж������콱��У����#G��è������#cffcc00��", GetName( sceneId, selfId) )
    			LuaAllScenceM2Wrold (sceneId , msg , 5, 1)
    		end	  
    		
    		Msg2Player( sceneId, selfId, "��ϲ������˸ж��������", 8, 3)    
    		AddItemListToPlayer( sceneId, selfId)
    end
    					
--    if x310910_g_RandomItemTable[ index].title == 1 then
--        AwardTitle( sceneId, selfId, x310910_g_RandomItemTable[ index].itemId)
--        Msg2Player( sceneId, selfId, format( "�����%s�ƺ�", x310910_g_RandomItemTable[ index].itemName), 8, 2)
--        if x310910_g_RandomItemTable[ index].broadcast == 1 then
--            LuaAllScenceM2Wrold( sceneId, format( "��ϲ%s���������%s�ƺ�", GetName( sceneId, selfId), x310910_g_RandomItemTable[ index].itemName), 5, 1)
--        end
--    else
--        BeginAddItem( sceneId)
--        AddBindItem( sceneId, x310910_g_RandomItemTable[ index].itemId, 1)
--        if EndAddItem( sceneId, selfId) == 0 then
--            Msg2Player( sceneId, selfId, "�����Ʒʧ�ܣ�", 8, 3)
--            return
--        else
--            AddItemListToPlayer( sceneId, selfId)
--        end
--    end

    SetQuestData( sceneId, selfId, active[ 1], active[ 2], active[ 3], today)
end