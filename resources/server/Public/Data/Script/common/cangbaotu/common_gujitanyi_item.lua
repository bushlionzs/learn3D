-- 诱兽炉香


------------------------------------------------------------------------------------------
--一般物品的默认脚本

--脚本号
x300341_g_scriptId = 300341

--需要的等级

--效果的ID
x300341_g_Impact1 = 7210
x300341_g_Impact2 = -1 --不用

-- 使用此物品的任务ID
x300341_g_MissionId = 8051
-- 使用“诱兽炉香”X坐标
x300341_g_MP_PosX               = 2
-- 使用“诱兽炉香”Z坐标
x300341_g_MP_PosZ               = 3
-- 使用“诱兽炉香”时间
x300341_g_MP_UseTime            = 4
-- 任务目标场景
x300341_g_MP_TargetScene        = 5

--**********************************
--事件交互入口
--**********************************
function x300341_ProcEventEntry( sceneId, selfId, bagIndex)
-- 不需要这个接口，但要保留空函数
end

--**********************************
--这个物品的使用过程是否类似于技能：
--系统会在执行开始时检测这个函数的返回值，如果返回失败则忽略后面的类似技能的执行。
--返回1：技能类似的物品，可以继续类似技能的执行；返回0：忽略后面的操作。
--**********************************
function x300341_IsSkillLikeScript( sceneId, selfId)
    --print( "诱兽炉香" )
	return 1; --这个脚本不需要动作支持
end

--**********************************
--直接取消效果：
--系统会直接调用这个接口，并根据这个函数的返回值确定以后的流程是否执行。
--返回1：已经取消对应效果，不再执行后续操作；返回0：没有检测到相关效果，继续执行。
--**********************************
function x300341_CancelImpacts( sceneId, selfId)
    --print( "*****CancelImpacts*****" )
	return 0; --不需要这个接口，但要保留空函数,并且始终返回0。
end

--**********************************
--条件检测入口：
--系统会在技能检测的时间点调用这个接口，并根据这个函数的返回值确定以后的流程是否执行。
--返回1：条件检测通过，可以继续执行(call OnDeplete)；返回0：条件检测失败，中断后续执行。
--**********************************
function x300341_OnConditionCheck( sceneId, selfId)
	--校验使用的物品
	if( 1 ~= VerifyUsedItem( sceneId, selfId) ) then
		return 0
	end

	-- 检查玩家是否接受了草原三宝任务
    if IsHaveQuestNM( sceneId, selfId, x300341_g_MissionId) == 0 then	-- 如果没有这个任务
		BeginQuestEvent( sceneId)
		AddQuestText( sceneId, "你没有接受“草原三宝”任务，不能使用此道具" )
		EndQuestEvent()
		DispatchQuestTips( sceneId, selfId)
        return 0
    end

	-- 有任务但没在任务特定的场景使用此物品
    local misIndex = GetQuestIndexByID( sceneId, selfId, x300341_g_MissionId)
    local missionScene = GetQuestParam( sceneId, selfId, misIndex, x300341_g_MP_TargetScene)
    if sceneId ~= missionScene then
        local baseScene = ( GetCurCountry( sceneId, selfId) ) * 100 + 50
        missionScene = missionScene - baseScene
        local str = "在这里使用也没有效果，还是留到迷宫里面用吧"
        if missionScene == 36 then
            str = "在这里使用也没有效果，还是留到@npcsp_温泉谷_82004用吧"
        elseif missionScene == 37 then
            str = "在这里使用也没有效果，还是留到@npcsp_风陵山_82005用吧"
        elseif missionScene == 39 then
            str = "在这里使用也没有效果，还是留到@npcsp_黄叶林_82006用吧"
        end

		BeginQuestEvent( sceneId)
		AddQuestText( sceneId, str)
		EndQuestEvent()
		DispatchQuestTips( sceneId, selfId)
		return 0
    end

	return 1
end

--**********************************
--消耗检测及处理入口：
--系统会在技能消耗的时间点调用这个接口，并根据这个函数的返回值确定以后的流程是否执行。
--返回1：消耗处理通过，可以继续执行(call OnActivateOnce)；返回0：消耗检测失败，中断后续执行。
--注意：这不光负责消耗的检测也负责消耗的执行。
--**********************************
function x300341_OnDeplete( sceneId, selfId)
	if DepletingUsedItem( sceneId, selfId) == 1 then
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
function x300341_OnActivateOnce( sceneId, selfId)
    -- 放Buff
	-- if( -1 ~= x300341_g_Impact1) then
		-- SendSpecificImpactToUnit( sceneId, selfId, selfId, selfId, x300341_g_Impact1, 0);
	-- end

    -- 创建NPC
    local x, z = GetWorldPos( sceneId, selfId)
    local ObjId = CreateMonster( sceneId, 3120, x, z, 0, 0, -1, -1, 20, 180000)

    -- 记录NPC位置
    local misIndex = GetQuestIndexByID( sceneId, selfId, x300341_g_MissionId)
    SetQuestByIndex( sceneId, selfId, misIndex, x300341_g_MP_PosX, x)
    SetQuestByIndex( sceneId, selfId, misIndex, x300341_g_MP_PosZ, z)
    -- 保存使用物品时间
    local curTime = GetCurrentTime()
    SetQuestByIndex( sceneId, selfId, misIndex, x300341_g_MP_UseTime, curTime)

    -- 提示
    BeginQuestEvent( sceneId)
    AddQuestText( sceneId, "附近的生物都受了炉香引诱，看来从他们身上更容易获得珍宝吧" )
    EndQuestEvent( sceneId)
    DispatchQuestTips( sceneId, selfId)

	return 1;
end

--**********************************
--引导心跳处理入口：
--引导技能会在每次心跳结束时调用这个接口。
--返回：1继续下次心跳；0：中断引导。
--注：这里是技能生效一次的入口
--**********************************
function x300341_OnActivateEachTick( sceneId, selfId)
	return 1; --不是引导性脚本, 只保留空函数.
end
