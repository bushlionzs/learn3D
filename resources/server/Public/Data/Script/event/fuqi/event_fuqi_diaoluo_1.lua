--喜糖
------------------------------------------------------------------------------------------
--一般物品的默认脚本

--脚本号

x300390_g_scriptId = 300390 
x300390_g_ItemList = {
{11000200,11050001},
{11000201,11050002},
{11000202,11050003},
{11000203,11050004},
}
--需要的等级


--**********************************
--事件交互入口
--**********************************
function x300390_ProcEventEntry( sceneId, selfId, bagIndex )
-- 不需要这个接口，但要保留空函数
end

--**********************************
--这个物品的使用过程是否类似于技能：
--系统会在执行开始时检测这个函数的返回值，如果返回失败则忽略后面的类似技能的执行。
--返回1：技能类似的物品，可以继续类似技能的执行；返回0：忽略后面的操作。
--**********************************
function x300390_IsSkillLikeScript( sceneId, selfId)
	return 1; --这个脚本需要动作支持
end

--**********************************
--直接取消效果：
--系统会直接调用这个接口，并根据这个函数的返回值确定以后的流程是否执行。
--返回1：已经取消对应效果，不再执行后续操作；返回0：没有检测到相关效果，继续执行。
--**********************************
function x300390_CancelImpacts( sceneId, selfId )
	return 0; --不需要这个接口，但要保留空函数,并且始终返回0。
end

--**********************************
--条件检测入口：
--系统会在技能检测的时间点调用这个接口，并根据这个函数的返回值确定以后的流程是否执行。
--返回1：条件检测通过，可以继续执行；返回0：条件检测失败，中断后续执行。
--**********************************
function x300390_OnConditionCheck( sceneId, selfId )
	
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
function x300390_OnDeplete( sceneId, selfId )
	return 1;
end

function x300390_OnAddMoney(sceneId, selfId)
	local level = GetLevel(sceneId, selfId)
	local money = 5000; 
	if(DepletingUsedItem(sceneId, selfId)) == 1 then
	
		AddMoney( sceneId , selfId ,0, money )
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"您使用了喜糖")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		
	end
	
end

function x300390_OnAddItemByLevel(sceneId, selfId)

	local i = random(1,2)
	
	if GetLevel(sceneId,selfId) < 40 then
		x300390_OnAddItem(sceneId, selfId, x300390_g_ItemList[1][i])
		
	elseif (GetLevel(sceneId,selfId) >=40 and GetLevel(sceneId,selfId) < 60) then
		x300390_OnAddItem(sceneId, selfId, x300390_g_ItemList[2][i])
		
	elseif (GetLevel(sceneId,selfId) >= 60 and GetLevel(sceneId,selfId) < 80) then
		x300390_OnAddItem(sceneId, selfId, x300390_g_ItemList[3][i]) 
	elseif GetLevel(sceneId,selfId) >= 80 then
		x300390_OnAddItem(sceneId, selfId, x300390_g_ItemList[4][i]) 
	end
	
end

function x300390_OnAddItem(sceneId, selfId, itemId)

	BeginAddItem(sceneId)
	AddBindItem( sceneId,itemId, 1 )	--IB物品1
	local ret = EndAddItem(sceneId,selfId)
	if ret > 0 then
		if(DepletingUsedItem(sceneId, selfId)) == 1 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"您使用了喜糖")
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
			AddItemListToPlayer(sceneId,selfId)
		end

	else
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"背包已满，无法得到物品！您需要至少有1个背包空间！")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
	end
	
end

--**********************************
--只会执行一次入口：
--聚气和瞬发技能会在消耗完成后调用这个接口（聚气结束并且各种条件都满足的时候），而引导
--技能也会在消耗完成后调用这个接口（技能的一开始，消耗成功执行之后）。
--返回1：处理成功；返回0：处理失败。
--注：这里是技能生效一次的入口
--**********************************
function x300390_OnActivateOnce( sceneId, selfId, impactId )

	local j = random(1,2)
	
	if j < 2 then
		x300390_OnAddMoney(sceneId, selfId)
	else
		x300390_OnAddItemByLevel(sceneId, selfId)
	end
	
end

--**********************************
--引导心跳处理入口：
--引导技能会在每次心跳结束时调用这个接口。
--返回：1继续下次心跳；0：中断引导。
--注：这里是技能生效一次的入口
--**********************************
function x300390_OnActivateEachTick( sceneId, selfId)
	return 1; --不是引导性脚本, 只保留空函数.
end
