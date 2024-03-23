
------------------------------------------------------------------------------------------
--一般物品的默认脚本

--脚本号

x418000_g_scriptId = 418000
x418000_g_ItemList = {10200010,10230010,10240010,10250010,10260010,10270010}
--需要的等级


--**********************************
--事件交互入口
--**********************************
function x418000_ProcEventEntry( sceneId, selfId, bagIndex )
-- 不需要这个接口，但要保留空函数
end

--**********************************
--这个物品的使用过程是否类似于技能：
--系统会在执行开始时检测这个函数的返回值，如果返回失败则忽略后面的类似技能的执行。
--返回1：技能类似的物品，可以继续类似技能的执行；返回0：忽略后面的操作。
--**********************************
function x418000_IsSkillLikeScript( sceneId, selfId)
	return 1; --这个脚本需要动作支持
end

--**********************************
--直接取消效果：
--系统会直接调用这个接口，并根据这个函数的返回值确定以后的流程是否执行。
--返回1：已经取消对应效果，不再执行后续操作；返回0：没有检测到相关效果，继续执行。
--**********************************
function x418000_CancelImpacts( sceneId, selfId )
	return 0; --不需要这个接口，但要保留空函数,并且始终返回0。
end

--**********************************
--条件检测入口：
--系统会在技能检测的时间点调用这个接口，并根据这个函数的返回值确定以后的流程是否执行。
--返回1：条件检测通过，可以继续执行；返回0：条件检测失败，中断后续执行。
--**********************************
function x418000_OnConditionCheck( sceneId, selfId )
	
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
function x418000_OnDeplete( sceneId, selfId )
	
	
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
function x418000_OnActivateOnce( sceneId, selfId, impactId )
	
	local nZhiYe = GetZhiye( sceneId, selfId);
	local itemId = 0;



	if nZhiYe==0 then
		itemId = 10010010
	elseif nZhiYe==1 then
		itemId = 10020010
	elseif nZhiYe==2 then
		itemId = 10030010
	elseif nZhiYe==3 then
		itemId = 10040010
	elseif nZhiYe==4 then
		itemId = 10050010
	elseif nZhiYe==5 then
		itemId = 10060010
	elseif nZhiYe==6 then
		itemId = 10350001
	elseif nZhiYe==7 then
		itemId = 10360001
	elseif nZhiYe==8 then
		itemId = 10370001
	elseif nZhiYe==9 then
		itemId = 10380001
	elseif nZhiYe==10 then
		itemId = 10390001
	elseif nZhiYe==11 then
		itemId = 10400001
	end

	if itemId==0 then
		return
	end
	
	local i = random(1,7)
	local j = random(1,7)
	while(i==j) do
		j = random(1,7)
	end
	
	
	local itemId2 = 0
	if i<=6 then
		itemId2 = x418000_g_ItemList[i]
	else
		itemId2 = itemId
	end

	local itemId3 = 0
	if j<=6 then
		itemId3 = x418000_g_ItemList[j]
	else
		itemId3 = itemId
	end
	
	BeginAddItem(sceneId)
	AddBindItem( sceneId, 12010001, 5 )
	AddBindItem( sceneId, itemId2, 1 )
	AddBindItem( sceneId, itemId3, 1 )
	AddBindItem( sceneId, 12010100, 1 )
	--AddBindItem( sceneId, 12010100, 1 )
	AddBindItem( sceneId, 12030306, 1 )
	local ret = EndAddItem(sceneId,selfId)
	if ret > 0 then
		if(DepletingUsedItem(sceneId, selfId)) == 1 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"打开礼包，获得了礼包道具")
			EndQuestEvent(sceneId)
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
		AddQuestText(sceneId,"背包已满，无法得到物品！您需要至少有5个背包空间！")
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
function x418000_OnActivateEachTick( sceneId, selfId)
	return 1; --不是引导性脚本, 只保留空函数.
end
