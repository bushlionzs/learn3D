-- 【线上领奖】感恩金翎

-- 脚本号
x310910_g_ScriptId          = 310910
-- 最低等级限制
x310910_g_MinLevel          = 40

--feast attach
x310910_g_FeastId						= 5
x310910_g_MD_DayCount1				    = MD_JINLINGJIANG_DAY1
--x310910_g_MD_DayCount2				    = MD_JINLINGJIANG_DAY2


x310910_g_RandomItemTable0   = {
                               { itemId = 12030013, probability = 140, itemName = "芝华士",num = 2 }, 
                               { itemId = 12041101, probability = 140, itemName = "修行草" ,num = 2 }, 
                               { itemId = 12110206, probability = 140, itemName = "钟情一生" ,num = 2 }, 
                               { itemId = 12110207, probability = 140, itemName = "爱无止境",num = 1  }, 
                               { itemId = 11990050, probability = 85, itemName = "回魂丹",num = 3  }, 
                               { itemId = 12041103, probability = 85, itemName = "活力丹",num = 5  }, 
                               { itemId = 11990011, probability = 84, itemName = "三番令",num = 2  },
                               { itemId = 11000501, probability = 85, itemName = "紫檀木炭",num = 5  }, 
                               { itemId = 12054300, probability = 85, itemName = "还童书",num = 1  }, 
                               { itemId = 12250002, probability = 10, itemName = "精品芝华士",num = 1  }, 
                               { itemId = 11000300, probability = 5, itemName = "灵魂印",num = 1  }, 
                               { itemId = 12050258, probability = 1, itemName = "浣熊降世符",num = 1  }
}


x310910_g_RandomItemTable1   = {
                               { itemId = 12030013, probability = 1200, itemName = "芝华士",num = 2 }, 
                               { itemId = 12110206, probability = 1200, itemName = "钟情一生" ,num = 2 }, 
                               { itemId = 12110207, probability = 1200, itemName = "爱无止境",num = 1  }, 
                               { itemId = 11000598, probability = 750, itemName = "五彩石",num = 1  }, 
                               { itemId = 11000597, probability = 750, itemName = "金龙印",num = 1  },
                               { itemId = 12041108, probability = 900, itemName = "荣誉之星",num = 1  }, 
                               { itemId = 11010121, probability = 750, itemName = "七彩墨",num = 1  }, 
                               { itemId = 12041102, probability = 750, itemName = "天赋丹",num = 1  }, 
                               { itemId = 12260001, probability = 900, itemName = "美容秘方",num = 1  }, 
                               { itemId = 11000550, probability = 750, itemName = "微瑕星辰",num = 2  },
                               { itemId = 11010111, probability = 699, itemName = "一级平衡之书",num = 1  }, 
                               { itemId = 12250002, probability = 100, itemName = "精品芝华士",num = 1  }, 
                               { itemId = 11000300, probability = 50, itemName = "灵魂印",num = 1  }, 
                               { itemId = 12050260, probability = 1, itemName = "熊猫降世符",num = 1  }
}


--3选1给其中一个物品
--x310910_g_OneFromFour       = {
--                                12031002,
--                                12031003,
--                                12031004,
--}

-- 每日最大换取次数
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
        AddQuestNumText( sceneId, x310910_g_ScriptId, "【线上领奖】感恩金翎", 3, 1)
    end
end

function x310910_ProcEventEntry( sceneId, selfId, targetId, MissionId, indexId)

		if x310910_IsFeastActive() ~= 1 then
        Msg2Player( sceneId, selfId, "活动没有开启", 8, 3)
        return
    end

    BeginQuestEvent( sceneId)
        AddQuestText( sceneId, "#Y【线上领奖】感恩金翎" )
        AddQuestText( sceneId, "\t值此金秋收获的季节，《成吉思汗2》喜获#G金翎奖#W大奖。\n\t为了回馈广大玩家对《成吉思汗2》的鼎力支持，#R从10月26日至10月28日，每天晚上20：00-20：30#W，所有#G40级#W以上的玩家都可以领取一份#G感恩礼物#W。\n\t您确定要领取感恩金翎礼物吗？" )
    EndQuestEvent()
    DispatchQuestInfo( sceneId, selfId, targetId, x310910_g_ScriptId, -1)
end

function x310910_ProcAcceptCheck( sceneId, selfId, targetId)

		if x310910_IsFeastActive() ~= 1 then
        Msg2Player( sceneId, selfId, "活动没有开启", 8, 3)
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
	        Msg2Player( sceneId, selfId, "您今天的礼物已经领取过了", 8, 3)
	        return
    	end

    --elseif minute >= 1200 and minute < 1230 then
    --	if GetQuestData( sceneId, selfId, x310910_g_MD_DayCount2[ 1], x310910_g_MD_DayCount2[ 2], x310910_g_MD_DayCount2[ 3] ) ~= today then
    --	    active = x310910_g_MD_DayCount2
    --	else
	  --      Msg2Player( sceneId, selfId, "这个时段的礼物已经领取过了", 8, 3)
	  --      return
    --	end
    else
        Msg2Player( sceneId, selfId, "很抱歉，本活动开放时间为#R20：00至20：30#cffcf00", 8, 3)
        return
    end

    if GetBagSpace( sceneId, selfId) < 2 then
        Msg2Player( sceneId, selfId, format( "背包空间不足2个，无法获得物品", 1), 8, 3)
        return
    end
          
    AddMoney( sceneId, selfId, 1, 150000) 
          
    if GetLevel( sceneId, selfId) <80 then      
    		-- 随机选择绑定物品
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
    		    Msg2Player( sceneId, selfId, "添加物品失败", 8, 3)
    		    return
    		end
    		
    		if x310910_g_RandomItemTable0[ index ].itemId ==12250002 then
    			local msg = format( "恭喜#R%s#cffcc00在感恩金翎领奖活动中，获得#G精品芝华士#cffcc00！", GetName( sceneId, selfId) )
    			LuaAllScenceM2Wrold (sceneId , msg , 5, 1)
    		end
    			
    		if x310910_g_RandomItemTable0[ index ].itemId ==11000300 then
    			local msg = format( "恭喜#R%s#cffcc00在感恩金翎领奖活动中，获得#G灵魂印#cffcc00！", GetName( sceneId, selfId) )
    			LuaAllScenceM2Wrold (sceneId , msg , 5, 1)
    		end	
    			
    		if x310910_g_RandomItemTable0[ index ].itemId ==12050258 then
    			local msg = format( "恭喜#R%s#cffcc00在感恩金翎领奖活动中，获得#G浣熊降世符#cffcc00！", GetName( sceneId, selfId) )
    			LuaAllScenceM2Wrold (sceneId , msg , 5, 1)
    		end	    			
    			
    		Msg2Player( sceneId, selfId, "恭喜您获得了感恩金翎礼物！", 8, 3)    
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
    		    Msg2Player( sceneId, selfId, "添加物品失败", 8, 3)
    		    return
    		end
    		
    		if x310910_g_RandomItemTable1[ index ].itemId ==12250002 then
    			local msg = format( "恭喜#R%s#cffcc00在感恩金翎领奖活动中，获得#G精品芝华士#cffcc00！", GetName( sceneId, selfId) )
    			LuaAllScenceM2Wrold (sceneId , msg , 5, 1)
    		end
    			
    		if x310910_g_RandomItemTable1[ index ].itemId ==11000300 then
    			local msg = format( "恭喜#R%s#cffcc00在感恩金翎领奖活动中，获得#G灵魂印#cffcc00！", GetName( sceneId, selfId) )
    			LuaAllScenceM2Wrold (sceneId , msg , 5, 1)
    		end	
    			
    		if x310910_g_RandomItemTable1[ index ].itemId ==12050260 then
    			local msg = format( "恭喜#R%s#cffcc00在感恩金翎领奖活动中，获得#G熊猫降世符#cffcc00！", GetName( sceneId, selfId) )
    			LuaAllScenceM2Wrold (sceneId , msg , 5, 1)
    		end	  
    		
    		Msg2Player( sceneId, selfId, "恭喜您获得了感恩金翎礼物！", 8, 3)    
    		AddItemListToPlayer( sceneId, selfId)
    end
    					
--    if x310910_g_RandomItemTable[ index].title == 1 then
--        AwardTitle( sceneId, selfId, x310910_g_RandomItemTable[ index].itemId)
--        Msg2Player( sceneId, selfId, format( "您获得%s称号", x310910_g_RandomItemTable[ index].itemName), 8, 2)
--        if x310910_g_RandomItemTable[ index].broadcast == 1 then
--            LuaAllScenceM2Wrold( sceneId, format( "恭喜%s获得周年庆%s称号", GetName( sceneId, selfId), x310910_g_RandomItemTable[ index].itemName), 5, 1)
--        end
--    else
--        BeginAddItem( sceneId)
--        AddBindItem( sceneId, x310910_g_RandomItemTable[ index].itemId, 1)
--        if EndAddItem( sceneId, selfId) == 0 then
--            Msg2Player( sceneId, selfId, "添加物品失败！", 8, 3)
--            return
--        else
--            AddItemListToPlayer( sceneId, selfId)
--        end
--    end

    SetQuestData( sceneId, selfId, active[ 1], active[ 2], active[ 3], today)
end