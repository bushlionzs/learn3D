-- 【感恩节】线上领奖

-- 脚本号
x310911_g_ScriptId          = 310911
-- 最低等级限制
x310911_g_MinLevel          = 40

--feast attach
x310911_g_FeastId						= 6
x310911_g_MD_DayCount1				    = MD_GANENJIE_DAY1
--x310911_g_MD_DayCount2				    = MD_GANENJIE_DAY2


x310911_g_RandomItemTable0   = {
                               { itemId = 12030013, probability = 160, itemName = "芝华士",num = 2 }, --same10yue
                               { itemId = 12041101, probability = 160, itemName = "修行草" ,num = 2 }, --same10yue
                               { itemId = 12110206, probability = 160, itemName = "钟情一生" ,num = 2 }, --same10yue
                               { itemId = 12110207, probability = 160, itemName = "爱无止境",num = 1  }, --same10yue
                               { itemId = 12034000, probability = 70, itemName = "固本丹",num = 1  }, 
                               { itemId = 12041103, probability = 77, itemName = "活力丹",num = 5  }, --same10yue
                               { itemId = 11990110, probability = 70, itemName = "募集卷",num = 1  },
                               { itemId = 12030211, probability = 70, itemName = "师恩难谢",num = 1  }, 
                               { itemId = 12054300, probability = 70, itemName = "还童书",num = 1  }, --same10yue
                               { itemId = 12250002, probability = 2, itemName = "精品芝华士",num = 1  }, --same10yue
                               { itemId = 11000300, probability = 1, itemName = "灵魂印",num = 1  }, --same10yue
}


x310911_g_RandomItemTable1   = {
                               { itemId = 12030013, probability = 1600, itemName = "芝华士",num = 2 }, --same10yue
                               { itemId = 12110206, probability = 1600, itemName = "钟情一生" ,num = 2 }, --same10yue
                               { itemId = 12110207, probability = 1600, itemName = "爱无止境",num = 1  }, --same10yue
                               { itemId = 12041101, probability = 1600, itemName = "修行草" ,num = 2 },
                               { itemId = 12034000, probability = 700, itemName = "固本丹",num = 1  }, 
                               { itemId = 12041103, probability = 770, itemName = "活力丹",num = 5  },
                               { itemId = 12030217, probability = 700, itemName = "练功人偶",num = 4  },
                               { itemId = 12054300, probability = 700, itemName = "还童书",num = 1  }, 
                               { itemId = 11000551, probability = 700, itemName = "无瑕星辰",num = 2  },--same10yue
                               { itemId = 12250002, probability = 20, itemName = "精品芝华士",num = 1  }, --same10yue
                               { itemId = 11000300, probability = 10, itemName = "灵魂印",num = 1  }, --same10yue
}


--3选1给其中一个物品
--x310911_g_OneFromFour       = {
--                                12031002,
--                                12031003,
--                                12031004,
--}

-- 每日最大换取次数
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
        AddQuestNumText( sceneId, x310911_g_ScriptId, "【感恩节】线上领奖", 3, 1)
    end
end

function x310911_ProcEventEntry( sceneId, selfId, targetId, MissionId, indexId)

		if x310911_IsFeastActive() ~= 1 then
        Msg2Player( sceneId, selfId, "活动没有开启", 8, 3)
        return
    end

    BeginQuestEvent( sceneId)
        AddQuestText( sceneId, "#Y【感恩节】线上领奖" )
        AddQuestText( sceneId, "\t为了感恩广大玩家对《成吉思汗2》的鼎力支持，#R从11月23日至11月25日，每天晚上20：00-20：30#W，所有#G40级#W以上的玩家都可以领取一份#G感恩节礼物#W。\n\t您确定要领取感恩节礼物吗？" )
    EndQuestEvent()
    DispatchQuestInfo( sceneId, selfId, targetId, x310911_g_ScriptId, -1)
end

function x310911_ProcAcceptCheck( sceneId, selfId, targetId)

		if x310911_IsFeastActive() ~= 1 then
        Msg2Player( sceneId, selfId, "活动没有开启", 8, 3)
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
	        Msg2Player( sceneId, selfId, "您今天的礼物已经领取过了", 8, 3)
	        return
    	end

    --elseif minute >= 1200 and minute < 1230 then
    --	if GetQuestData( sceneId, selfId, x310911_g_MD_DayCount2[ 1], x310911_g_MD_DayCount2[ 2], x310911_g_MD_DayCount2[ 3] ) ~= today then
    --	    active = x310911_g_MD_DayCount2
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
    		    Msg2Player( sceneId, selfId, "添加物品失败", 8, 3)
    		    return
    		end
    		
    		if x310911_g_RandomItemTable0[ index ].itemId ==12250002 then
    			local msg = format( "恭喜#R%s#cffcc00在感恩节线上领奖活动中，获得#G精品芝华士#cffcc00！", GetName( sceneId, selfId) )
    			LuaAllScenceM2Wrold (sceneId , msg , 5, 1)
    		end
    			
    		if x310911_g_RandomItemTable0[ index ].itemId ==11000300 then
    			local msg = format( "恭喜#R%s#cffcc00在感恩节线上领奖活动中，获得#G灵魂印#cffcc00！", GetName( sceneId, selfId) )
    			LuaAllScenceM2Wrold (sceneId , msg , 5, 1)
    		end	
    			
    		Msg2Player( sceneId, selfId, "恭喜您获得了感恩节礼物！", 8, 3)    
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
    		    Msg2Player( sceneId, selfId, "添加物品失败", 8, 3)
    		    return
    		end
    		
    		if x310911_g_RandomItemTable1[ index ].itemId ==12250002 then
    			local msg = format( "恭喜#R%s#cffcc00在感恩节线上领奖活动中，获得#G精品芝华士#cffcc00！", GetName( sceneId, selfId) )
    			LuaAllScenceM2Wrold (sceneId , msg , 5, 1)
    		end
    			
    		if x310911_g_RandomItemTable1[ index ].itemId ==11000300 then
    			local msg = format( "恭喜#R%s#cffcc00在感恩节线上领奖活动中，获得#G灵魂印#cffcc00！", GetName( sceneId, selfId) )
    			LuaAllScenceM2Wrold (sceneId , msg , 5, 1)
    		end	
    			 
    		
    		Msg2Player( sceneId, selfId, "恭喜您获得了感恩节礼物！", 8, 3)    
    		AddItemListToPlayer( sceneId, selfId)
    end
    					
--    if x310911_g_RandomItemTable[ index].title == 1 then
--        AwardTitle( sceneId, selfId, x310911_g_RandomItemTable[ index].itemId)
--        Msg2Player( sceneId, selfId, format( "您获得%s称号", x310911_g_RandomItemTable[ index].itemName), 8, 2)
--        if x310911_g_RandomItemTable[ index].broadcast == 1 then
--            LuaAllScenceM2Wrold( sceneId, format( "恭喜%s获得周年庆%s称号", GetName( sceneId, selfId), x310911_g_RandomItemTable[ index].itemName), 5, 1)
--        end
--    else
--        BeginAddItem( sceneId)
--        AddBindItem( sceneId, x310911_g_RandomItemTable[ index].itemId, 1)
--        if EndAddItem( sceneId, selfId) == 0 then
--            Msg2Player( sceneId, selfId, "添加物品失败！", 8, 3)
--            return
--        else
--            AddItemListToPlayer( sceneId, selfId)
--        end
--    end

    SetQuestData( sceneId, selfId, active[ 1], active[ 2], active[ 3], today)
end