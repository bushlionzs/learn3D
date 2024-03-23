------------------------------------------------------------------------------------------
--20级月饼的默认脚本

--脚本号

x430109_g_scriptId 		= 430109 

--**********************************
--事件交互入口
--**********************************
function x430109_ProcEventEntry( sceneId, selfId, bagIndex)
-- 不需要这个接口，但要保留空函数
end

--**********************************
--这个物品的使用过程是否类似于技能：
--系统会在执行开始时检测这个函数的返回值，如果返回失败则忽略后面的类似技能的执行。
--返回1：技能类似的物品，可以继续类似技能的执行；返回0：忽略后面的操作。
--**********************************
function x430109_IsSkillLikeScript( sceneId, selfId)
	return 1; --这个脚本需要动作支持
end

--**********************************
--直接取消效果：
--系统会直接调用这个接口，并根据这个函数的返回值确定以后的流程是否执行。
--返回1：已经取消对应效果，不再执行后续操作；返回0：没有检测到相关效果，继续执行。
--**********************************
function x430109_CancelImpacts( sceneId, selfId)
	return 0; --不需要这个接口，但要保留空函数,并且始终返回0。
end

--**********************************
--条件检测入口：
--系统会在技能检测的时间点调用这个接口，并根据这个函数的返回值确定以后的流程是否执行。
--返回1：条件检测通过，可以继续执行；返回0：条件检测失败，中断后续执行。
--**********************************
function x430109_OnConditionCheck( sceneId, selfId)
	--校验使用的物品
	if( 1~=VerifyUsedItem( sceneId, selfId) ) then
		return 0
	end
    -- local level = GetLevel( sceneId, selfId)
    -- if level < x430109_g_LevelMin then
        -- Msg2Player( sceneId, selfId, "您的等级低于使用此物品的最低级别", 8, 3)
        -- return 0
    -- end
    -- if level >= x430109_g_LevelMax then
        -- Msg2Player( sceneId, selfId, "您的等级高于使用此物品的最高级别", 8, 3)
        -- return 0
    -- end
    if GetTiredTime( sceneId, selfId) >= 480 then
        Msg2Player( sceneId, selfId, "您处于疲劳状态，无法再次使用月饼", 8, 3)
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
function x430109_OnDeplete( sceneId, selfId)
    if DepletingUsedItem( sceneId, selfId) == 1 then
        return 1;
    end

    return 0
end

--**********************************
--只会执行一次入口：
--聚气和瞬发技能会在消耗完成后调用这个接口（聚气结束并且各种条件都满足的时候），而引导
--技能也会在消耗完成后调用这个接口（技能的一开始，消耗成功执行之后）。
--返回1：处理成功；返回0：处理失败。
--注：这里是技能生效一次的入口
--**********************************
function x430109_OnActivateOnce( sceneId, selfId, impactId)
	local level=GetLevel(sceneId, selfId)
	if level > 0 and level < 10 then
	nExpBonus = 50000
    AddExp( sceneId, selfId, nExpBonus)
    IncreaseTiredTime( sceneId, selfId, 120)
	end
	if level > 9 and level < 20 then
	nExpBonus = 50000
    AddExp( sceneId, selfId, nExpBonus)
    IncreaseTiredTime( sceneId, selfId, 120)
	end
	if level > 19 and level < 30 then
	nExpBonus = 50000
    AddExp( sceneId, selfId, nExpBonus)
    IncreaseTiredTime( sceneId, selfId, 120)
	end
	if level > 29 and level < 40 then
	nExpBonus = 270000
    AddExp( sceneId, selfId, nExpBonus)
    IncreaseTiredTime( sceneId, selfId, 120)
	end
	if level > 39 and level < 50 then
	nExpBonus = 400000
    AddExp( sceneId, selfId, nExpBonus)
    IncreaseTiredTime( sceneId, selfId, 120)
	end
	if level > 49 and level < 60 then
	nExpBonus = 550000
    AddExp( sceneId, selfId, nExpBonus)
    IncreaseTiredTime( sceneId, selfId, 120)
	end
	if level > 59 and level < 70 then
	nExpBonus = 720000
    AddExp( sceneId, selfId, nExpBonus)
    IncreaseTiredTime( sceneId, selfId, 120)
	end
	if level > 69 and level < 80 then
	nExpBonus = 910000
    AddExp( sceneId, selfId, nExpBonus)
    IncreaseTiredTime( sceneId, selfId, 120)
	end
	if level > 79 and level < 90 then
	nExpBonus = 1120000
    AddExp( sceneId, selfId, nExpBonus)
    IncreaseTiredTime( sceneId, selfId, 120)
	end
	if level > 89 and level < 100 then
	nExpBonus = 1350000
    AddExp( sceneId, selfId, nExpBonus)
    IncreaseTiredTime( sceneId, selfId, 120)
	end
	if level > 99 then
	nExpBonus = 1580000
    AddExp( sceneId, selfId, nExpBonus)
    IncreaseTiredTime( sceneId, selfId, 120)
	end
end

--**********************************
--引导心跳处理入口：
--引导技能会在每次心跳结束时调用这个接口。
--返回：1继续下次心跳；0：中断引导。
--注：这里是技能生效一次的入口
--**********************************
function x430109_OnActivateEachTick( sceneId, selfId)
	return 1; --不是引导性脚本, 只保留空函数.
end

