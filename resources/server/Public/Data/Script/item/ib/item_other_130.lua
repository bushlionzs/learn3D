--节庆大礼包	11010019
------------------------------------------------------------------------------------------
--一般物品的默认脚本

--脚本号

x418130_g_scriptId = 418130
x418130_g_LevelMin = 30	

x418130_g_ItemTable             = {
                                    { itemId = 12054300, probability = 120, special = 0, broad = 0, itemname = "还童书" }, 
                                    { itemId = 11000501, probability = 120, special = 0, broad = 0, itemname = "紫檀木碳" }, 
                                    { itemId = 11000902, probability = 120, special = 0, broad = 0, itemname = "高级洗石剂" }, 
                                    { itemId = 12010020, probability = 120, special = 0, broad = 0, itemname = "小生命清露" }, 
                                    { itemId = 11000800, probability = 120, special = 0, broad = 0, itemname = "离石剂" }, 
                                    { itemId = 12030202, probability = 70,  special = 0, broad = 0, itemname = "江湖请柬" }, 
                                    { itemId = 12110207, probability = 70,  special = 0, broad = 0, itemname = "爱无止境" }, 
                                    { itemId = 12030200, probability = 70,  special = 0, broad = 0, itemname = "小喇叭" }, 
                                    { itemId = 11990110, probability = 70,  special = 0, broad = 0, itemname = "募集券" }, 
                                    { itemId = 12054301, probability = 50,  special = 0, broad = 0, itemname = "还龙书" }, 
                                    { itemId = 11990114, probability = 16,  special = 0, broad = 0, itemname = "次生钻石" }, 
                                    { itemId = 11000502, probability = 25,  special = 0, broad = 0, itemname = "黄紫水火水银" }, 
                                    { itemId = 11000504, probability = 7,   special = 0, broad = 0, itemname = "黄紫炫彩水银" }, 
                                    { itemId = 11000500, probability = 6,   special = 0, broad = 0, itemname = "黄紫海蓝水银" }, 
                                    { itemId = 11000503, probability = 5,   special = 0, broad = 0, itemname = "黄紫晕光水银" }, 
                                    { itemId = 12050249, probability = 10,  special = 0, broad = 1, itemname = "年兽降世符" }, 
                                    { itemId = 10287075, probability = 1,   special = 1, broad = 1, itemname = "世传节庆戒指" }, 
}                                                                               
x418130_g_ItemSpecial           = {
                                    { itemId = 10287075, itemname = "世传节庆戒指", leveldown = 30, levelup = 40 }, 
                                    { itemId = 10287076, itemname = "国传节庆戒指", leveldown = 40, levelup = 60 }, 
                                    { itemId = 10287073, itemname = "神传节庆戒指", leveldown = 60, levelup = 80 }, 
                                    { itemId = 10287074, itemname = "天传节庆戒指", leveldown = 80, levelup = 999 }, 
                                    { itemId = 10297075, itemname = "世传节庆手镯", leveldown = 30, levelup = 40 }, 
                                    { itemId = 10297076, itemname = "国传节庆手镯", leveldown = 40, levelup = 60 }, 
                                    { itemId = 10297073, itemname = "神传节庆手镯", leveldown = 60, levelup = 80 }, 
                                    { itemId = 10297074, itemname = "天传节庆手镯", leveldown = 80, levelup = 999 }, 
}

--**********************************
--事件交互入口
--**********************************
function x418130_ProcEventEntry( sceneId, selfId, bagIndex )
-- 不需要这个接口，但要保留空函数
end

--**********************************
--这个物品的使用过程是否类似于技能：
--系统会在执行开始时检测这个函数的返回值，如果返回失败则忽略后面的类似技能的执行。
--返回1：技能类似的物品，可以继续类似技能的执行；返回0：忽略后面的操作。
--**********************************
function x418130_IsSkillLikeScript( sceneId, selfId)
	return 1; --这个脚本需要动作支持
end

--**********************************
--直接取消效果：
--系统会直接调用这个接口，并根据这个函数的返回值确定以后的流程是否执行。
--返回1：已经取消对应效果，不再执行后续操作；返回0：没有检测到相关效果，继续执行。
--**********************************
function x418130_CancelImpacts( sceneId, selfId )
	return 0; --不需要这个接口，但要保留空函数,并且始终返回0。
end

--**********************************
--条件检测入口：
--系统会在技能检测的时间点调用这个接口，并根据这个函数的返回值确定以后的流程是否执行。
--返回1：条件检测通过，可以继续执行；返回0：条件检测失败，中断后续执行。
--**********************************
function x418130_OnConditionCheck( sceneId, selfId )
	
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
function x418130_OnDeplete( sceneId, selfId )
	
	
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
function x418130_OnActivateOnce( sceneId, selfId, impactId )

	local lv = GetLevel(sceneId, selfId)
	if lv < x418130_g_LevelMin then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"等级不足")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return
	end

    if GetBagSpace(sceneId, selfId) < 1 then
        Msg2Player( sceneId, selfId, "背包空间不足一格，无法打开节庆大礼包", 8, 3)
        return
    end

	local rand = random( 1, 1000)
    local index = 1
    local num1 = 1
    local num2 = 1
    local giveitem = 12054300
    for i, item in x418130_g_ItemTable do
        num1 = num1 + item.probability
        if rand >= num2 and rand < num1 then
            index = i
            break
        end
        num2 = num2 + item.probability
    end
    local arr = {}
    local count = 0
    if x418130_g_ItemTable[ index].special == 1 then
        for i, item in x418130_g_ItemSpecial do
            if lv >= item.leveldown and lv < item.levelup then
                count = count + 1
                arr[ count] = item
            end
        end
        giveitem = arr[ random( 1, getn( arr) ) ].itemId
    else
        giveitem = x418130_g_ItemTable[ index].itemId
    end

	BeginAddItem(sceneId)
		AddBindItem( sceneId, giveitem, 1)

	local ret = EndAddItem(sceneId,selfId)
	if ret > 0 then
		if(DepletingUsedItem(sceneId, selfId)) == 1 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"打开节庆大礼包，获得了礼品")
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
			AddItemListToPlayer(sceneId,selfId)

            -- 世界广播
            if x418130_g_ItemTable[ index].broad == 1 then
                LuaAllScenceM2Wrold( sceneId, format( "恭喜玩家%s打开节庆大礼包获得了#{_ITEM%d}", GetName( sceneId, selfId), giveitem), 5, 1)
            end

            local xp = random( 60000, 980000)
            AddExp( sceneId, selfId, xp)
            Msg2Player( sceneId, selfId, format( "你获得了#R%d#cffcc00点经验。", xp), 8, 2)
            Msg2Player( sceneId, selfId, format( "你获得了#R%d#cffcc00点经验", xp), 8, 3)
		else
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"打开节庆大礼包异常！")
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
function x418130_OnActivateEachTick( sceneId, selfId)
	return 1; --不是引导性脚本, 只保留空函数.
end
