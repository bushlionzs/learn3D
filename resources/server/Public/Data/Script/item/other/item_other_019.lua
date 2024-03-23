--迎公测银卡礼包 12030326
------------------------------------------------------------------------------------------
--一般物品的默认脚本

--脚本号

x418019_g_scriptId = 418019
x418019_g_ItemList = {}
x418019_g_LevelMin = 20	
x418019_g_ItemList = {12030201,12030202,12041101,12010020,12030200} 
x418019_g_ItemName = {"修理石","江湖请柬","修行草","小生命清露","小喇叭"} 
--12030201修理石
--12030202江湖请柬
--12041101修行草
--12010020小生命清露
--12030200小喇叭

--需要的等级


--**********************************
--事件交互入口
--**********************************
function x418019_ProcEventEntry( sceneId, selfId, bagIndex )
-- 不需要这个接口，但要保留空函数
end

--**********************************
--这个物品的使用过程是否类似于技能：
--系统会在执行开始时检测这个函数的返回值，如果返回失败则忽略后面的类似技能的执行。
--返回1：技能类似的物品，可以继续类似技能的执行；返回0：忽略后面的操作。
--**********************************
function x418019_IsSkillLikeScript( sceneId, selfId)
	return 1; --这个脚本需要动作支持
end

--**********************************
--直接取消效果：
--系统会直接调用这个接口，并根据这个函数的返回值确定以后的流程是否执行。
--返回1：已经取消对应效果，不再执行后续操作；返回0：没有检测到相关效果，继续执行。
--**********************************
function x418019_CancelImpacts( sceneId, selfId )
	return 0; --不需要这个接口，但要保留空函数,并且始终返回0。
end

--**********************************
--条件检测入口：
--系统会在技能检测的时间点调用这个接口，并根据这个函数的返回值确定以后的流程是否执行。
--返回1：条件检测通过，可以继续执行；返回0：条件检测失败，中断后续执行。
--**********************************
function x418019_OnConditionCheck( sceneId, selfId )
	
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
function x418019_OnDeplete( sceneId, selfId )
	
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
function x418019_OnActivateOnce( sceneId, selfId, impactId )
	
	if GetLevel(sceneId, selfId)< x418019_g_LevelMin then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"等级不足")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return
	end

	local j = random(1,5)
	local i = random(1,5)	
	local itemId = 0
	local itemName = 0
	local nCountry = CallScriptFunction(888888,"GetCountryName",sceneId,selfId)
	local nLevel = GetLevel(sceneId,selfId)

	if j < 5 then
		if(DepletingUsedItem(sceneId, selfId)) == 1 then
			AddMoney( sceneId, selfId, 1, 500*nLevel )
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"很遗憾，幸运擦肩而过，祝您下次好运！")
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
		else
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"使用物品异常！")
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
		end
		
	else
		if i<=5 then
			itemId = x418019_g_ItemList[i]
			itemName = 	x418019_g_ItemName[i]
	BeginAddItem(sceneId)
	AddBindItem( sceneId,itemId, 1 )	--IB物品1

	local ret = EndAddItem(sceneId,selfId)
	if ret > 0 then
		if(DepletingUsedItem(sceneId, selfId)) == 1 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"打开礼包，获得了礼包道具")
			EndQuestEvent(sceneId)
			AddMoney( sceneId, selfId, 1, 500*nLevel )
			local nName=GetName(sceneId,selfId)
			local msg = format("#G恭喜%s#Y%s#G获得了#R%s#G幸运奖品，每人都有可能获得这份幸运，马上到领奖大使处去领取吧！",nCountry,nName,itemName)
			LuaAllScenceM2Wrold (sceneId, msg, 0, 1)--全服公告
			DispatchQuestTips(sceneId,selfId)
			AddItemListToPlayer(sceneId,selfId)
		else
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"使用物品异常！")
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
		end

	else
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"背包已满，无法得到物品！您需要至少有1个背包空间！")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
	end
		else
			return
		end
	end


end

--**********************************
--引导心跳处理入口：
--引导技能会在每次心跳结束时调用这个接口。
--返回：1继续下次心跳；0：中断引导。
--注：这里是技能生效一次的入口
--**********************************
function x418019_OnActivateEachTick( sceneId, selfId)
	return 1; --不是引导性脚本, 只保留空函数.
end
