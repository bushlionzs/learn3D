-- ���ж��ڡ������콱

-- �ű���
x310911_g_ScriptId          = 310911
-- ��͵ȼ�����
x310911_g_MinLevel          = 40

--feast attach
x310911_g_FeastId						= 6
x310911_g_MD_DayCount1				    = MD_GANENJIE_DAY1
--x310911_g_MD_DayCount2				    = MD_GANENJIE_DAY2


x310911_g_RandomItemTable0   = {
                               { itemId = 12030013, probability = 160, itemName = "֥��ʿ",num = 2 }, --same10yue
                               { itemId = 12041101, probability = 160, itemName = "���в�" ,num = 2 }, --same10yue
                               { itemId = 12110206, probability = 160, itemName = "����һ��" ,num = 2 }, --same10yue
                               { itemId = 12110207, probability = 160, itemName = "����ֹ��",num = 1  }, --same10yue
                               { itemId = 12034000, probability = 70, itemName = "�̱���",num = 1  }, 
                               { itemId = 12041103, probability = 77, itemName = "������",num = 5  }, --same10yue
                               { itemId = 11990110, probability = 70, itemName = "ļ����",num = 1  },
                               { itemId = 12030211, probability = 70, itemName = "ʦ����л",num = 1  }, 
                               { itemId = 12054300, probability = 70, itemName = "��ͯ��",num = 1  }, --same10yue
                               { itemId = 12250002, probability = 2, itemName = "��Ʒ֥��ʿ",num = 1  }, --same10yue
                               { itemId = 11000300, probability = 1, itemName = "���ӡ",num = 1  }, --same10yue
}


x310911_g_RandomItemTable1   = {
                               { itemId = 12030013, probability = 1600, itemName = "֥��ʿ",num = 2 }, --same10yue
                               { itemId = 12110206, probability = 1600, itemName = "����һ��" ,num = 2 }, --same10yue
                               { itemId = 12110207, probability = 1600, itemName = "����ֹ��",num = 1  }, --same10yue
                               { itemId = 12041101, probability = 1600, itemName = "���в�" ,num = 2 },
                               { itemId = 12034000, probability = 700, itemName = "�̱���",num = 1  }, 
                               { itemId = 12041103, probability = 770, itemName = "������",num = 5  },
                               { itemId = 12030217, probability = 700, itemName = "������ż",num = 4  },
                               { itemId = 12054300, probability = 700, itemName = "��ͯ��",num = 1  }, 
                               { itemId = 11000551, probability = 700, itemName = "����ǳ�",num = 2  },--same10yue
                               { itemId = 12250002, probability = 20, itemName = "��Ʒ֥��ʿ",num = 1  }, --same10yue
                               { itemId = 11000300, probability = 10, itemName = "���ӡ",num = 1  }, --same10yue
}


--3ѡ1������һ����Ʒ
--x310911_g_OneFromFour       = {
--                                12031002,
--                                12031003,
--                                12031004,
--}

-- ÿ�����ȡ����
x310911_g_MaxTimes          = 1


function x310911_IsFeastActive()
    local day = GetDayOfYear()
	if day < 326 or day > 328 or x310911_g_FeastId ~= MD_CURRENT_FEAST_ID then
				return 0
	end
	return 1
end

function x310911_ProcEnumEvent( sceneId, selfId, targetId, MissionId)

		--check feast active
		if x310911_IsFeastActive() ~= 1 then
				return
		end

    local lv = GetLevel( sceneId, selfId)
    if lv < x310911_g_MinLevel then
        return
    end

    local day = GetDayOfYear()
    if day >= 326 and day <= 328 then
        AddQuestNumText( sceneId, x310911_g_ScriptId, "���ж��ڡ������콱", 3, 1)
    end
end

function x310911_ProcEventEntry( sceneId, selfId, targetId, MissionId, indexId)

		if x310911_IsFeastActive() ~= 1 then
        Msg2Player( sceneId, selfId, "�û�п���", 8, 3)
        return
    end

    BeginQuestEvent( sceneId)
        AddQuestText( sceneId, "#Y���ж��ڡ������콱" )
        AddQuestText( sceneId, "\tΪ�˸ж������Ҷԡ��ɼ�˼��2���Ķ���֧�֣�#R��11��23����11��25�գ�ÿ������20��00-20��30#W������#G40��#W���ϵ���Ҷ�������ȡһ��#G�ж�������#W��\n\t��ȷ��Ҫ��ȡ�ж���������" )
    EndQuestEvent()
    DispatchQuestInfo( sceneId, selfId, targetId, x310911_g_ScriptId, -1)
end

function x310911_ProcAcceptCheck( sceneId, selfId, targetId)

		if x310911_IsFeastActive() ~= 1 then
        Msg2Player( sceneId, selfId, "�û�п���", 8, 3)
        return
    end
    
    
    CallScriptFunction(888894,"Feast_SetCurrentId",sceneId,selfId,x310911_g_FeastId)

    local minute = GetMinOfDay()
    local active = nil
    local today = GetDayOfYear()
    if today < 326 or today > 328 then
    	return
    end
    if minute >= 1200 and minute < 1230 then
    	if GetQuestData( sceneId, selfId, x310911_g_MD_DayCount1[ 1], x310911_g_MD_DayCount1[ 2], x310911_g_MD_DayCount1[ 3] ) ~= today then
    	    active = x310911_g_MD_DayCount1
    	else
	        Msg2Player( sceneId, selfId, "������������Ѿ���ȡ����", 8, 3)
	        return
    	end

    --elseif minute >= 1200 and minute < 1230 then
    --	if GetQuestData( sceneId, selfId, x310911_g_MD_DayCount2[ 1], x310911_g_MD_DayCount2[ 2], x310911_g_MD_DayCount2[ 3] ) ~= today then
    --	    active = x310911_g_MD_DayCount2
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
	  		  for i, item in x310911_g_RandomItemTable0 do
	  		      up = up + item.probability
	  		      if rseed >= dn and rseed < up then
	  		          index = i
	  		          break
	  		      end
	  		      dn = dn + item.probability
	  		  end
	  		  
	  		  AddBindItem( sceneId, x310911_g_RandomItemTable0[ index ].itemId, x310911_g_RandomItemTable0[ index ].num)
	  		  
	  		  --second item
	  		  --index = random(1,3)
	  		  --if index < 1 then index = 1 end
	  		  --if index > 3 then index = 3 end
	  		  
	  		  AddBindItem( sceneId, 12030043, 3)
    		
    		if EndAddItem( sceneId, selfId) == 0 then
    		    Msg2Player( sceneId, selfId, "�����Ʒʧ��", 8, 3)
    		    return
    		end
    		
    		if x310911_g_RandomItemTable0[ index ].itemId ==12250002 then
    			local msg = format( "��ϲ#R%s#cffcc00�ڸж��������콱��У����#G��Ʒ֥��ʿ#cffcc00��", GetName( sceneId, selfId) )
    			LuaAllScenceM2Wrold (sceneId , msg , 5, 1)
    		end
    			
    		if x310911_g_RandomItemTable0[ index ].itemId ==11000300 then
    			local msg = format( "��ϲ#R%s#cffcc00�ڸж��������콱��У����#G���ӡ#cffcc00��", GetName( sceneId, selfId) )
    			LuaAllScenceM2Wrold (sceneId , msg , 5, 1)
    		end	
    			
    		Msg2Player( sceneId, selfId, "��ϲ������˸ж������", 8, 3)    
    		AddItemListToPlayer( sceneId, selfId)
    		
		else
    		BeginAddItem( sceneId)
    			
    			--first item
	  		  local rseed = random( 1, 10000)
	  		  local index = 1
	  		  local dn = 1
	  		  local up = 1
	  		  for i, item in x310911_g_RandomItemTable1 do
	  		      up = up + item.probability
	  		      if rseed >= dn and rseed < up then
	  		          index = i
	  		          break
	  		      end
	  		      dn = dn + item.probability
	  		  end
	  		  
	  		  AddBindItem( sceneId, x310911_g_RandomItemTable1[ index ].itemId, x310911_g_RandomItemTable1[ index ].num)
	  		  
	  		  --second item
	  		  --index = random(1,3)
	  		  --if index < 1 then index = 1 end
	  		  --if index > 3 then index = 3 end
	  		  AddBindItem( sceneId, 12030043, 3)
    		
    		if EndAddItem( sceneId, selfId) == 0 then
    		    Msg2Player( sceneId, selfId, "�����Ʒʧ��", 8, 3)
    		    return
    		end
    		
    		if x310911_g_RandomItemTable1[ index ].itemId ==12250002 then
    			local msg = format( "��ϲ#R%s#cffcc00�ڸж��������콱��У����#G��Ʒ֥��ʿ#cffcc00��", GetName( sceneId, selfId) )
    			LuaAllScenceM2Wrold (sceneId , msg , 5, 1)
    		end
    			
    		if x310911_g_RandomItemTable1[ index ].itemId ==11000300 then
    			local msg = format( "��ϲ#R%s#cffcc00�ڸж��������콱��У����#G���ӡ#cffcc00��", GetName( sceneId, selfId) )
    			LuaAllScenceM2Wrold (sceneId , msg , 5, 1)
    		end	
    			 
    		
    		Msg2Player( sceneId, selfId, "��ϲ������˸ж������", 8, 3)    
    		AddItemListToPlayer( sceneId, selfId)
    end
    					
--    if x310911_g_RandomItemTable[ index].title == 1 then
--        AwardTitle( sceneId, selfId, x310911_g_RandomItemTable[ index].itemId)
--        Msg2Player( sceneId, selfId, format( "�����%s�ƺ�", x310911_g_RandomItemTable[ index].itemName), 8, 2)
--        if x310911_g_RandomItemTable[ index].broadcast == 1 then
--            LuaAllScenceM2Wrold( sceneId, format( "��ϲ%s���������%s�ƺ�", GetName( sceneId, selfId), x310911_g_RandomItemTable[ index].itemName), 5, 1)
--        end
--    else
--        BeginAddItem( sceneId)
--        AddBindItem( sceneId, x310911_g_RandomItemTable[ index].itemId, 1)
--        if EndAddItem( sceneId, selfId) == 0 then
--            Msg2Player( sceneId, selfId, "�����Ʒʧ�ܣ�", 8, 3)
--            return
--        else
--            AddItemListToPlayer( sceneId, selfId)
--        end
--    end

    SetQuestData( sceneId, selfId, active[ 1], active[ 2], active[ 3], today)
end