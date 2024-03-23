-- 铁铲

--物品技能的逻辑只能使用基础技能和脚本来实现

--脚本:

--以下是脚本样例:


------------------------------------------------------------------------------------------
--一般物品的默认脚本

--脚本号
x310366_g_scriptId = 310366

-- 使用铁铲的任务Id
x310366_g_MissionList   = {
                            { missionId = 9060, scriptId = 300364 } --挖宝大作战
}

--需要的等级


--**********************************
--事件交互入口
--**********************************
function x310366_ProcEventEntry( sceneId, selfId, bagIndex )
end

--**********************************
--这个物品的使用过程是否类似于技能：
--系统会在执行开始时检测这个函数的返回值，如果返回失败则忽略后面的类似技能的执行。
--返回1：技能类似的物品，可以继续类似技能的执行；返回0：忽略后面的操作。
--**********************************
function x310366_IsSkillLikeScript( sceneId, selfId)
	return 1; --这个脚本不需要动作支持
end

--**********************************
--直接取消效果：
--系统会直接调用这个接口，并根据这个函数的返回值确定以后的流程是否执行。
--返回1：已经取消对应效果，不再执行后续操作；返回0：没有检测到相关效果，继续执行。
--**********************************
function x310366_CancelImpacts( sceneId, selfId )
	return 0; --不需要这个接口，但要保留空函数,并且始终返回0。
end

--**********************************
--条件检测入口：
--系统会在技能检测的时间点调用这个接口，并根据这个函数的返回值确定以后的流程是否执行。
--返回1：条件检测通过，可以继续执行(call OnDeplete)；返回0：条件检测失败，中断后续执行。
--**********************************
function x310366_OnConditionCheck( sceneId, selfId )
	--校验使用的物品
	if(1~=VerifyUsedItem(sceneId, selfId)) then
		return 0
	end
	
	return 1; --不需要任何条件，并且始终返回1。
end

--**********************************
--消耗检测及处理入口：
--系统会在技能消耗的时间点调用这个接口，并根据这个函数的返回值确定以后的流程是否执行。
--返回1：消耗处理通过，可以继续执行(call OnActivateOnce)；返回0：消耗检测失败，中断后续执行。
--注意：这不光负责消耗的检测也负责消耗的执行。
--**********************************
function x310366_OnDeplete( sceneId, selfId )
    -- 暂时取消消耗
	-- if(DepletingUsedItem(sceneId, selfId)) then
		-- return 1;
	-- end
	return 1
end

--**********************************
--只会执行一次入口：
--聚气和瞬发技能会在消耗完成后调用这个接口（聚气结束并且各种条件都满足的时候），而引导
--技能也会在消耗完成后调用这个接口（技能的一开始，消耗成功执行之后）。
--返回1：处理成功；返回0：处理失败。
--注：这里是技能生效一次的入口
--**********************************
function x310366_OnActivateOnce( sceneId, selfId)
    if IsHaveQuest( sceneId, selfId, 9060) < 1 then
        Msg2Player(sceneId, selfId, "道具使用失败，请先领取挖宝大作战任务", 0, 2)
		Msg2Player(sceneId, selfId, "道具使用失败，请先领取挖宝大作战任务", 0, 3)
        return
    end
    if CallScriptFunction( 310364, "ProcUseShovel", sceneId, selfId, 0) == 1 then
        x310366_LogicDeplete( sceneId, selfId)
    end

	return 1
end

--**********************************
--引导心跳处理入口：
--引导技能会在每次心跳结束时调用这个接口。
--返回：1继续下次心跳；0：中断引导。
--注：这里是技能生效一次的入口
--**********************************
function x310366_OnActivateEachTick( sceneId, selfId)
	return 1; --不是引导性脚本, 只保留空函数.
end

function x310366_LogicDeplete( sceneId, selfId)
    -- print( "*-*-*-*-*-*-*-*-*-*-*-*-*-*" )
    -- 获得铁铲的背包索引值
    local bagIndex = GetBagIndexOfUsedItem( sceneId, selfId)
    local curTimes = GetBagItemMultTimes( sceneId, selfId, bagIndex)
    if curTimes <= 1 then
        -- delete item
        DelItemByIndexInBag( sceneId, selfId, bagIndex, 1)
    else
        -- decrease useful times
        SetBagItemMultTimes( sceneId, selfId, bagIndex, curTimes - 1)
    end
end

