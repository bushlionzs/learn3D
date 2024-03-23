
x418146_g_ScriptId = 418146
x418146_g_MissionName = "幸运密保礼包"

x418146_g_Profession1       = {
                                { lmin =  1, lmax = 30,  itemid = 14030001 }, 
                                { lmin = 31, lmax = 40,  itemid = 14030002 }, 
                                { lmin = 41, lmax = 50,  itemid = 14030003 }, 
                                { lmin = 51, lmax = 60,  itemid = 14030004 }, 
                                { lmin = 61, lmax = 70,  itemid = 14030005 }, 
                                { lmin = 71, lmax = 80,  itemid = 14030031 }, 
                                { lmin = 81, lmax = 160, itemid = 14030032 },
}                                                          
x418146_g_Profession2       = {
                                { lmin =  1, lmax = 30,  itemid = 14030006 }, 
                                { lmin = 31, lmax = 40,  itemid = 14030007 }, 
                                { lmin = 41, lmax = 50,  itemid = 14030008 }, 
                                { lmin = 51, lmax = 60,  itemid = 14030009 }, 
                                { lmin = 61, lmax = 70,  itemid = 14030010 }, 
                                { lmin = 71, lmax = 80,  itemid = 14030035 }, 
                                { lmin = 81, lmax = 160, itemid = 14030036 }, 
}                                                          
x418146_g_Profession3       = {
                                { lmin =  1, lmax = 30,  itemid = 14030011 }, 
                                { lmin = 31, lmax = 40,  itemid = 14030012 }, 
                                { lmin = 41, lmax = 50,  itemid = 14030013 }, 
                                { lmin = 51, lmax = 60,  itemid = 14030014 }, 
                                { lmin = 61, lmax = 70,  itemid = 14030015 }, 
                                { lmin = 71, lmax = 80,  itemid = 14030039 }, 
                                { lmin = 81, lmax = 160, itemid = 14030040 }, 
}                                                          

function x418146_g_Gem( sceneId, selfId)
    local prof = GetZhiye( sceneId, selfId)
    local level = GetLevel( sceneId, selfId)
    local itemid = 14030001
    local tab = nil

    if prof == 0 or prof == 1 or prof == 6 or prof == 7 then
        tab = x418146_g_Profession1
    elseif prof == 2 or prof == 3 or prof == 8 or prof == 9 then
        tab = x418146_g_Profession2
    elseif prof == 4 or prof == 5 or prof == 10 or prof == 11 then
        tab = x418146_g_Profession3
    end
    for i, item in tab do
        if level >= item.lmin and level <= item.lmax then
            itemid = item.itemid
            break
        end
    end

    BeginAddItem( sceneId)
    AddBindItem( sceneId, itemid, 1)
    if EndAddItem( sceneId, selfId) > 0 then
        AddItemListToPlayer( sceneId, selfId)
    else
        Msg2Player( sceneId, selfId, "背包已满，无法获得物品", 8, 3)
    end
end

x418146_g_ItemTable         = {
                                { itemid = 12031019, probability = 157, proc = nil }, 
                                { itemid = 12031013, probability = 157, proc = nil }, 
                                { itemid = 12031007, probability = 157, proc = nil }, 
                                { itemid = 12110206, probability = 157, proc = nil }, 
                                { itemid = 12031000, probability = 100, proc = nil }, 
                                { itemid = 11990011, probability = 100, proc = nil }, 
                                { itemid = 12050009, probability = 100, proc = nil }, 
                                { itemid = 11000501, probability =  50, proc = nil }, 
                                { itemid = 12030200, probability =  20, proc = nil }, 
                                { itemid = 12030200, probability =   2, proc = x418146_g_Gem }, 
}                                                              

x418146_g_ItemList = {}
x418146_g_LevelMin = 1
--需要的等级


--**********************************
--事件交互入口
--**********************************
function x418146_ProcEventEntry( sceneId, selfId, bagIndex )
-- 不需要这个接口，但要保留空函数
end

--**********************************
--这个物品的使用过程是否类似于技能：
--系统会在执行开始时检测这个函数的返回值，如果返回失败则忽略后面的类似技能的执行。
--返回1：技能类似的物品，可以继续类似技能的执行；返回0：忽略后面的操作。
--**********************************
function x418146_IsSkillLikeScript( sceneId, selfId)
	return 1; --这个脚本需要动作支持
end

--**********************************
--直接取消效果：
--系统会直接调用这个接口，并根据这个函数的返回值确定以后的流程是否执行。
--返回1：已经取消对应效果，不再执行后续操作；返回0：没有检测到相关效果，继续执行。
--**********************************
function x418146_CancelImpacts( sceneId, selfId )
	return 0; --不需要这个接口，但要保留空函数,并且始终返回0。
end

--**********************************
--条件检测入口：
--系统会在技能检测的时间点调用这个接口，并根据这个函数的返回值确定以后的流程是否执行。
--返回1：条件检测通过，可以继续执行；返回0：条件检测失败，中断后续执行。
--**********************************
function x418146_OnConditionCheck( sceneId, selfId )
	
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
function x418146_OnDeplete( sceneId, selfId )
    if GetBagSpace( sceneId, selfId) < 1 then
        Msg2Player( sceneId, selfId, format( "背包空间不足#G%d#cffcc00个，无法获得礼包物品", 1), 8, 3)
        return 0
    end
    
	if(DepletingUsedItem(sceneId, selfId) > 0) then
		return 1;
	end
	return 0;
end

--**********************************
--只会执行一次入口：
--聚气和瞬发技能会在消耗完成后调用这个接口（聚气结束并且各种条件都满足的时候），而引导
--技能也会在消耗完成后调用这个接口（技能的一开始，消耗成功执行之后）。
--返回1：处理成功；返回0：处理失败。
--注：这里是技能生效一次的入口
--**********************************
function x418146_OnActivateOnce( sceneId, selfId, impactId )

    if GetBagSpace( sceneId, selfId) < 1 then
        Msg2Player( sceneId, selfId, format( "背包空间不足#G%d#cffcc00个，无法获得礼包物品", 1), 8, 3)
        return
    end

	local r = random( 1, 1000)
    local top = 1
    local bottom = 1
    local index = 1
    for i, item in x418146_g_ItemTable do
        top = top + item.probability
        if r >= bottom and r < top then
            index = i
            break
        end
        bottom = bottom + item.probability
    end
    if x418146_g_ItemTable[ index].proc ~= nil then
        x418146_g_ItemTable[ index].proc( sceneId, selfId)
    else
 		BeginAddItem( sceneId)
		AddBindItem( sceneId, x418146_g_ItemTable[ index].itemid, 1)
		if EndAddItem( sceneId, selfId) > 0 then
			AddItemListToPlayer( sceneId, selfId)
		else
            Msg2Player( sceneId, selfId, "背包已满，无法获得物品", 8, 3)
		end
    end

end

--**********************************
--引导心跳处理入口：
--引导技能会在每次心跳结束时调用这个接口。
--返回：1继续下次心跳；0：中断引导。
--注：这里是技能生效一次的入口
--**********************************
function x418146_OnActivateEachTick( sceneId, selfId)
	return 1; --不是引导性脚本, 只保留空函数.
end


