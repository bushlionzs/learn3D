--VIP月饼大礼盒
------------------------------------------------------------------------------------------
--一般物品的默认脚本

--脚本号

x404891_g_scriptId = 404891
x404891_g_ItemList = {}
x404891_g_LevelMin = 30
--需要的等级


--**********************************
--事件交互入口
--**********************************
function x404891_ProcEventEntry( sceneId, selfId, bagIndex )
-- 不需要这个接口，但要保留空函数
end

--**********************************
--这个物品的使用过程是否类似于技能：
--系统会在执行开始时检测这个函数的返回值，如果返回失败则忽略后面的类似技能的执行。
--返回1：技能类似的物品，可以继续类似技能的执行；返回0：忽略后面的操作。
--**********************************
function x404891_IsSkillLikeScript( sceneId, selfId)
	return 1; --这个脚本需要动作支持
end

--**********************************
--直接取消效果：
--系统会直接调用这个接口，并根据这个函数的返回值确定以后的流程是否执行。
--返回1：已经取消对应效果，不再执行后续操作；返回0：没有检测到相关效果，继续执行。
--**********************************
function x404891_CancelImpacts( sceneId, selfId )
	return 0; --不需要这个接口，但要保留空函数,并且始终返回0。
end

--**********************************
--条件检测入口：
--系统会在技能检测的时间点调用这个接口，并根据这个函数的返回值确定以后的流程是否执行。
--返回1：条件检测通过，可以继续执行；返回0：条件检测失败，中断后续执行。
--**********************************
function x404891_OnConditionCheck( sceneId, selfId )
	
	--校验使用的物品
	
	if(1~=VerifyUsedItem(sceneId, selfId)) then
		return 0
	end

    -- 时间检查
    if GetQuestData( sceneId, selfId, MD_YUEBING_BOX_DATE[ 1], MD_YUEBING_BOX_DATE[ 2], MD_YUEBING_BOX_DATE[ 3] ) == GetDayOfYear() then
        Msg2Player( sceneId, selfId, "距上次开启礼包时间不到一天，无法使用！", 8, 3)
		return 0
    end

    -- 等级检查
	if GetLevel(sceneId, selfId)< x404891_g_LevelMin then
        Msg2Player( sceneId, selfId, format( "等级不足#R%d#cffcc00级，无法使用此物品", x404891_g_LevelMin), 8, 3)
		return 0
	end

	-- 有效期检查
    local bagIndex = GetBagIndexOfUsedItem( sceneId, selfId)
    local firstTime = GetItemParam( sceneId, selfId, bagIndex, 8, 2)
	local currtime = GetCurrentTime()
	if firstTime ~= 0 and currtime - firstTime > 604800 then -- 604800 = 7 * 86400
		Msg2Player( sceneId, selfId, "已经超过了保质期，无法继续使用,请丢弃此道具！", 8, 3)
		return 0
	end
	
	local itemId =  x404891_Yuebing(sceneId,selfId)	

	BeginAddItem(sceneId)
		if itemId ~= -1 then
			AddBindItem( sceneId,itemId,2 )	
		end	
	local ret = EndAddItem(sceneId,selfId)
	if ret > 0 then
		AddItemListToPlayer(sceneId,selfId)
		
		local nAddExp = 0
		local nExp1 = GetLevel(sceneId,selfId)*1000*0.5
		local nExp2 = GetLevel(sceneId,selfId)*1000
		local nExp3 = GetLevel(sceneId,selfId)*1000*2
		local nExp4 = GetLevel(sceneId,selfId)*1000*5

		local i = random(1,4)
		
		if i == 1 then 
			nAddExp = nExp1
		elseif i == 2 then
			nAddExp = nExp2
		elseif i == 3 then
			nAddExp = nExp3
		elseif i == 4 then
			nAddExp = nExp4
		end
		
		AddExp(sceneId,selfId,nAddExp)
		
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,format("恭喜您获得了茁壮成长包额外经验奖励%d点！",nAddExp))
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)		
		
	else
		Msg2Player( sceneId, selfId, "背包已满，无法得到物品！您需要至少有1个背包空间！", 8, 3)
		return 0
	end

	SetQuestData( sceneId, selfId, MD_YUEBING_BOX_DATE[ 1], MD_YUEBING_BOX_DATE[ 2], MD_YUEBING_BOX_DATE[ 3], GetDayOfYear() )

	return 1; --不需要任何条件，并且始终返回1。
end

--**********************************
--消耗检测及处理入口：
--系统会在技能消耗的时间点调用这个接口，并根据这个函数的返回值确定以后的流程是否执行。
--返回1：消耗处理通过，可以继续执行；返回0：消耗检测失败，中断后续执行。
--注意：这不光负责消耗的检测也负责消耗的执行。
--**********************************
function x404891_OnDeplete( sceneId, selfId )
	
    local bagIndex = GetBagIndexOfUsedItem( sceneId, selfId)
    local curTimes = GetBagItemMultTimes( sceneId, selfId, bagIndex)
    local result = 1

    -- 记录第一次使用时间
    if curTimes == 7 then
        SetItemParam( sceneId, selfId, bagIndex, 8, 2, GetCurrentTime() )
    end

    if curTimes <= 1 then
        -- delete item
        DelItemByIndexInBag( sceneId, selfId, bagIndex, 1)
    else
        -- decrease useful times
        SetBagItemMultTimes( sceneId, selfId, bagIndex, curTimes - 1)
        result = 0
    end

	return result
end

--**********************************
--只会执行一次入口：
--聚气和瞬发技能会在消耗完成后调用这个接口（聚气结束并且各种条件都满足的时候），而引导
--技能也会在消耗完成后调用这个接口（技能的一开始，消耗成功执行之后）。
--返回1：处理成功；返回0：处理失败。
--注：这里是技能生效一次的入口
--**********************************
function x404891_OnActivateOnce( sceneId, selfId, impactId )

end

--**********************************
--引导心跳处理入口：
--引导技能会在每次心跳结束时调用这个接口。
--返回：1继续下次心跳；0：中断引导。
--注：这里是技能生效一次的入口
--**********************************
function x404891_OnActivateEachTick( sceneId, selfId)
	return 1; --不是引导性脚本, 只保留空函数.
end

function x404891_Yuebing(sceneId,selfId)
	
	local nLevel = GetLevel(sceneId,selfId)
	local yuebing = -1
	if nLevel < 40  then
		yuebing = 12030251
	elseif nLevel >=40 and nLevel < 50 then
		yuebing = 12030252
	elseif nLevel >=50 and nLevel < 60 then	
		yuebing = 12030253
	elseif nLevel >=60 and nLevel < 70 then
		yuebing = 12030254
	elseif nLevel >=70 and nLevel < 80 then
		yuebing = 12030255
	elseif nLevel >=80 and nLevel < 90 then
		yuebing = 12030256
	elseif nLevel >=90 then
		yuebing = 12030257	
	end
	
	return yuebing

end

--**********************************
--引导心跳处理入口：
--引导技能会在每次心跳结束时调用这个接口。
--返回：1继续下次心跳；0：中断引导。
--注：这里是技能生效一次的入口
--**********************************
function x404891_OnActivateEachTick( sceneId, selfId)
	return 1; --不是引导性脚本, 只保留空函数.
end