
------------------------------------------------------------------------------------------
--一般物品的默认脚本
--"威望金钱包"

--脚本号

x404899_g_scriptId 		= 404899 

x404899_g_LevelMin		=	20
--需要的等级


--**********************************
--事件交互入口
--**********************************
function x404899_ProcEventEntry( sceneId, selfId, bagIndex )
-- 不需要这个接口，但要保留空函数
end

--**********************************
--这个物品的使用过程是否类似于技能：
--系统会在执行开始时检测这个函数的返回值，如果返回失败则忽略后面的类似技能的执行。
--返回1：技能类似的物品，可以继续类似技能的执行；返回0：忽略后面的操作。
--**********************************
function x404899_IsSkillLikeScript( sceneId, selfId)
	return 1; --这个脚本需要动作支持
end

--**********************************
--直接取消效果：
--系统会直接调用这个接口，并根据这个函数的返回值确定以后的流程是否执行。
--返回1：已经取消对应效果，不再执行后续操作；返回0：没有检测到相关效果，继续执行。
--**********************************
function x404899_CancelImpacts( sceneId, selfId )
	return 0; --不需要这个接口，但要保留空函数,并且始终返回0。
end

--**********************************
--条件检测入口：
--系统会在技能检测的时间点调用这个接口，并根据这个函数的返回值确定以后的流程是否执行。
--返回1：条件检测通过，可以继续执行；返回0：条件检测失败，中断后续执行。
--**********************************
function x404899_OnConditionCheck( sceneId, selfId )
	
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
function x404899_OnDeplete( sceneId, selfId )
	
	
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
function x404899_OnActivateOnce( sceneId, selfId, impactId )
	
	
	if x404899_IsOneWeekPassed(sceneId, selfId)<=0 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"本威望包一周只能开启一次,请您尝试其他威望包")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return
	end

	if(DepletingUsedItem(sceneId, selfId)) == 1 then
		local nMoney = 150*1000
		AddMoney(sceneId, selfId, 1, nMoney)
		
		local str = format("获得了#{_MONEY%d}银卡的奖励。", nMoney)

		Msg2Player(sceneId,selfId,str,8,2)

		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,str)
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)

		x404899_SaveDoTime(sceneId, selfId)
		
	else
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"使用物品异常！")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
	end

end

--**********************************
--引导心跳处理入口：
--引导技能会在每次心跳结束时调用这个接口。
--返回：1继续下次心跳；0：中断引导。
--注：这里是技能生效一次的入口
--**********************************
function x404899_OnActivateEachTick( sceneId, selfId)
	return 1; --不是引导性脚本, 只保留空函数.
end


---------------------------------------------------------------------------------------------------
--判断时间有没有到
---------------------------------------------------------------------------------------------------
function x404899_IsOneWeekPassed(sceneId, selfId)

	local curWeek = GetWeekIndex();

	local lastWeek = GetQuestData(sceneId, selfId, MD_WEIWANG_MONEY_WEEK[1], MD_WEIWANG_MONEY_WEEK[2],MD_WEIWANG_MONEY_WEEK[3] );

	if curWeek ~= lastWeek then
		return 1
	else
		return 0;
	end
	

end

---------------------------------------------------------------------------------------------------
--保存do 的时间
---------------------------------------------------------------------------------------------------
function x404899_SaveDoTime(sceneId, selfId)

	local curWeek = GetWeekIndex();
	SetQuestData(sceneId, selfId, MD_WEIWANG_MONEY_WEEK[1], MD_WEIWANG_MONEY_WEEK[2], MD_WEIWANG_MONEY_WEEK[3], curWeek)
	
	
	
end