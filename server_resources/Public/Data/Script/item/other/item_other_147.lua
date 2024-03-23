--果汁果乐幸运探索包	12030449
------------------------------------------------------------------------------------------
--一般物品的默认脚本

--脚本号

x418147_g_scriptId = 418147
x418147_g_LevelMin = 30	

x418147_g_ItemTable             = {
                                    { itemId = 11020502, probability = 7200, special = 0, broad = 0, itemname = "水木精华" }, 
                                    { itemId = 11030405, probability = 7200, special = 0, broad = 0, itemname = "七步蛇" }, 
                                    { itemId = 11000201, probability = 7200, special = 0, broad = 0, itemname = "国传水晶" }, 
                                    { itemId = 11050002, probability = 7200, special = 0, broad = 0, itemname = "中级龙眼石" }, 
                                    { itemId = 11000202, probability = 6000, special = 0, broad = 0, itemname = "神传水晶" }, 
                                    { itemId = 11030502, probability = 6000,  special = 0, broad = 0, itemname = "黑曜石" }, 
                                    { itemId = 11050003, probability = 6000,  special = 0, broad = 0, itemname = "高级龙眼石" }, 
                                    { itemId = 12031019, probability = 5500,  special = 0, broad = 0, itemname = "斩" }, 
                                    { itemId = 12030201, probability = 5500,  special = 0, broad = 0, itemname = "修理石" }, 
                                    { itemId = 12031005, probability = 4000,  special = 0, broad = 0, itemname = "心心相印" }, 
                                    { itemId = 12031006, probability = 4000,  special = 0, broad = 0, itemname = "一见钟情" }, 
                                    { itemId = 11990011, probability = 4000,  special = 0, broad = 0, itemname = "三番令" }, 
                                    { itemId = 12030210, probability = 4000,   special = 0, broad = 0, itemname = "威望之星" }, 
                                    { itemId = 12050009, probability = 4000,   special = 0, broad = 0, itemname = "极乐草" }, 
                                    { itemId = 11990012, probability = 3500,   special = 0, broad = 0, itemname = "五番令" }, 
                                    { itemId = 12010020, probability = 3000,  special = 0, broad = 0, itemname = "小生命清露" },
                                    { itemId = 11000800, probability = 3000,  special = 0, broad = 0, itemname = "离石剂" }, 
                                    { itemId = 12054300, probability = 3000,  special = 0, broad = 0, itemname = "还童书" }, 
                                    { itemId = 11000501, probability = 3000,  special = 0, broad = 0, itemname = "紫檀木炭" }, 
                                    { itemId = 11000902, probability = 3000,  special = 0, broad = 0, itemname = "高级洗石剂" }, 
                                    { itemId = 11000800, probability = 3000,  special = 0, broad = 0, itemname = "离石剂" }, 
                                    { itemId = 12030202, probability = 100,  special = 0, broad = 0, itemname = "江湖请柬" }, 
                                    { itemId = 12110207, probability = 100,  special = 0, broad = 0, itemname = "爱无止境" }, 
                                    { itemId = 12030200, probability = 100,  special = 0, broad = 0, itemname = "小喇叭" }, 
                                    { itemId = 11990110, probability = 100,  special = 0, broad = 0, itemname = "募集券" }, 
                                    { itemId = 12054301, probability = 90,  special = 0, broad = 0, itemname = "还龙书" }, 
                                    { itemId = 11000502, probability = 64,  special = 0, broad = 0, itemname = "黄紫水火水银" }, 
                                    { itemId = 11000504, probability = 55,  special = 0, broad = 0, itemname = "黄紫炫彩水银" },
                                    { itemId = 11000500, probability = 54,  special = 0, broad = 0, itemname = "黄紫海蓝水银" },
                                    { itemId = 11000503, probability = 33,  special = 0, broad = 0, itemname = "黄紫晕光水银" },
                                    { itemId = 10310028, probability = 2,  special = 0, broad = 1, itemname = "掌门牌：碰碰胡(30天)" }, 
                                    { itemId = 10310029, probability = 2,  special = 0, broad = 1, itemname = "掌门牌：清一色(30天)" },
}                                                                               
--x418147_g_ItemSpecial           = {
--                                    { itemId = 10287075, itemname = "世传节庆戒指", leveldown = 30, levelup = 40 }, 
--                                    { itemId = 10287076, itemname = "国传节庆戒指", leveldown = 40, levelup = 60 }, 
--                                    { itemId = 10287073, itemname = "神传节庆戒指", leveldown = 60, levelup = 80 }, 
--                                    { itemId = 10287074, itemname = "天传节庆戒指", leveldown = 80, levelup = 999 }, 
--                                    { itemId = 10297075, itemname = "世传节庆手镯", leveldown = 30, levelup = 40 }, 
--                                    { itemId = 10297076, itemname = "国传节庆手镯", leveldown = 40, levelup = 60 }, 
--                                    { itemId = 10297073, itemname = "神传节庆手镯", leveldown = 60, levelup = 80 }, 
--                                    { itemId = 10297074, itemname = "天传节庆手镯", leveldown = 80, levelup = 999 }, 
--}

--**********************************
--事件交互入口
--**********************************
function x418147_ProcEventEntry( sceneId, selfId, bagIndex )
-- 不需要这个接口，但要保留空函数
end

--**********************************
--这个物品的使用过程是否类似于技能：
--系统会在执行开始时检测这个函数的返回值，如果返回失败则忽略后面的类似技能的执行。
--返回1：技能类似的物品，可以继续类似技能的执行；返回0：忽略后面的操作。
--**********************************
function x418147_IsSkillLikeScript( sceneId, selfId)
	return 1; --这个脚本需要动作支持
end

--**********************************
--直接取消效果：
--系统会直接调用这个接口，并根据这个函数的返回值确定以后的流程是否执行。
--返回1：已经取消对应效果，不再执行后续操作；返回0：没有检测到相关效果，继续执行。
--**********************************
function x418147_CancelImpacts( sceneId, selfId )
	return 0; --不需要这个接口，但要保留空函数,并且始终返回0。
end

--**********************************
--条件检测入口：
--系统会在技能检测的时间点调用这个接口，并根据这个函数的返回值确定以后的流程是否执行。
--返回1：条件检测通过，可以继续执行；返回0：条件检测失败，中断后续执行。
--**********************************
function x418147_OnConditionCheck( sceneId, selfId )
	
	--校验使用的物品
	
	if(1~=VerifyUsedItem(sceneId, selfId)) then
		return 0
	end
	return 1; --不需要任何条件，并且始终返回1。
end

--**********************************
--消耗检测及处理入口：
--系统会在技能消耗的时间点调用这个接口，并根据这个函数的返回值确定以后的流程是否执行。
--返回1：消耗处理通过，可以继续执行；返回0：消耗检测失败，中断后续执行。
--注意：这不光负责消耗的检测也负责消耗的执行。
--**********************************
function x418147_OnDeplete( sceneId, selfId )
	
	
	--if(DepletingUsedItem(sceneId, selfId)) == 1 then
	--	return 1;
	--end
	--return 0;
	
	return 1;
end

--**********************************
--只会执行一次入口：
--聚气和瞬发技能会在消耗完成后调用这个接口（聚气结束并且各种条件都满足的时候），而引导
--技能也会在消耗完成后调用这个接口（技能的一开始，消耗成功执行之后）。
--返回1：处理成功；返回0：处理失败。
--注：这里是技能生效一次的入口
--**********************************
function x418147_OnActivateOnce( sceneId, selfId, impactId )
    local day = GetDayOfYear()
    local last = GetQuestData( sceneId, selfId, MD_GUOZHI_DAY[ 1], MD_GUOZHI_DAY[ 2], MD_GUOZHI_DAY[ 3] )
    if day == last then
        if GetQuestData( sceneId, selfId, MD_GUOZHI_DAYCOUNT[ 1], MD_GUOZHI_DAYCOUNT[ 2], MD_GUOZHI_DAYCOUNT[ 3] ) >= 3 then
            Msg2Player(sceneId, selfId, "您今天的使用次数已超过上限！",8,3)
            return
        end
    else
        SetQuestData( sceneId, selfId, MD_GUOZHI_DAYCOUNT[ 1], MD_GUOZHI_DAYCOUNT[ 2], MD_GUOZHI_DAYCOUNT[ 3], 0)
    end

    SetQuestData( sceneId, selfId, MD_GUOZHI_DAYCOUNT[ 1], MD_GUOZHI_DAYCOUNT[ 2], MD_GUOZHI_DAYCOUNT[ 3], GetQuestData( sceneId, selfId, MD_GUOZHI_DAYCOUNT[ 1], MD_GUOZHI_DAYCOUNT[ 2], MD_GUOZHI_DAYCOUNT[ 3] ) + 1)
    SetQuestData( sceneId, selfId, MD_GUOZHI_DAY[ 1], MD_GUOZHI_DAY[ 2], MD_GUOZHI_DAY[ 3], day)
    
	local lv = GetLevel(sceneId, selfId)
		local money = 0
  if lv < 50 and lv >= 30 then
  	money = 5000
  elseif lv < 80 and lv >= 50 then
  	money = 10000
  elseif lv < 150 and lv >= 80 then
  	money = 18000
  else
  	return
  end 
	
	if lv < x418147_g_LevelMin then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"等级不足，无法打开礼包！")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return
	end

  if GetBagSpace(sceneId, selfId) < 1 then
      Msg2Player( sceneId, selfId, "背包空间不足一格，无法打开果汁果乐幸运探索包", 8, 3)
      return
  end

	local rand = random( 1, 100000)
    local index = 1
    local num1 = 1
    local num2 = 1
    local giveitem = 11020502
    for i, item in x418147_g_ItemTable do
        num1 = num1 + item.probability
        if rand >= num2 and rand < num1 then
            index = i
            break
        end
        num2 = num2 + item.probability
    end
    
			giveitem = x418147_g_ItemTable[ index].itemId

	BeginAddItem(sceneId)
		AddBindItem( sceneId, giveitem, 1)
		AddMoney( sceneId, selfId, 1, money )
  	Msg2Player( sceneId, selfId, format( "你获得了#R#{_MONEY%d}银卡。", money), 8, 2)
  	Msg2Player( sceneId, selfId, format( "你获得了#R#{_MONEY%d}银卡。", money), 8, 3)

	local ret = EndAddItem(sceneId,selfId)
	if ret > 0 then
			if(DepletingUsedItem(sceneId, selfId)) == 1 then
					BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"打开果汁果乐幸运探索包，获得了礼品")
					EndQuestEvent(sceneId)
					DispatchQuestTips(sceneId,selfId)
					AddItemListToPlayer(sceneId,selfId)
	
	    -- 世界广播
		    if x418147_g_ItemTable[ index].broad == 1 then
		        LuaAllScenceM2Wrold( sceneId, format( "恭喜玩家%s打开汇源活动礼包获得了#{_ITEM%d}", GetName( sceneId, selfId), giveitem), 5, 1)
		    end
	
			else
					BeginQuestEvent(sceneId)
					AddQuestText(sceneId,"打开果汁果乐幸运探索包异常！")
					EndQuestEvent(sceneId)
					DispatchQuestTips(sceneId,selfId)
				end

	else
				BeginQuestEvent( sceneId)
				AddQuestText( sceneId, "背包已满，无法得到物品！" )
				EndQuestEvent( sceneId)
				DispatchQuestTips( sceneId, selfId)
	end

end

--**********************************
--引导心跳处理入口：
--引导技能会在每次心跳结束时调用这个接口。
--返回：1继续下次心跳；0：中断引导。
--注：这里是技能生效一次的入口
--**********************************
function x418147_OnActivateEachTick( sceneId, selfId)
	return 1; --不是引导性脚本, 只保留空函数.
end
