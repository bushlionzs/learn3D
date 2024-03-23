--促销 神传700套餐	12030347

------------------------------------------------------------------------------------------
--一般物品的默认脚本

--脚本号

x418035_g_scriptId = 418035
x418035_g_ItemList = {}
x418035_g_LevelMin = 1	
--需要的等级


--**********************************
--事件交互入口
--**********************************
function x418035_ProcEventEntry( sceneId, selfId, bagIndex )
-- 不需要这个接口，但要保留空函数
end

--**********************************
--这个物品的使用过程是否类似于技能：
--系统会在执行开始时检测这个函数的返回值，如果返回失败则忽略后面的类似技能的执行。
--返回1：技能类似的物品，可以继续类似技能的执行；返回0：忽略后面的操作。
--**********************************
function x418035_IsSkillLikeScript( sceneId, selfId)
	return 1; --这个脚本需要动作支持
end

--**********************************
--直接取消效果：
--系统会直接调用这个接口，并根据这个函数的返回值确定以后的流程是否执行。
--返回1：已经取消对应效果，不再执行后续操作；返回0：没有检测到相关效果，继续执行。
--**********************************
function x418035_CancelImpacts( sceneId, selfId )
	return 0; --不需要这个接口，但要保留空函数,并且始终返回0。
end

--**********************************
--条件检测入口：
--系统会在技能检测的时间点调用这个接口，并根据这个函数的返回值确定以后的流程是否执行。
--返回1：条件检测通过，可以继续执行；返回0：条件检测失败，中断后续执行。
--**********************************
function x418035_OnConditionCheck( sceneId, selfId )
	
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
function x418035_OnDeplete( sceneId, selfId )
	
	
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
function x418035_OnActivateOnce( sceneId, selfId, impactId )
	
	if GetLevel(sceneId, selfId)< x418035_g_LevelMin then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"等级不足")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return
	end
	
	local  nZhiYe = GetZhiye( sceneId, selfId);
	local itemId1 = 0
	local itemId2 = 0
	local itemId3 = 0
	if nZhiYe == 0 then
		itemId1 = 14010003
		itemId2 = 10284003
		itemId3 = 10294003
	elseif nZhiYe == 1 then
		itemId1 = 14010003
		itemId2 = 10284013
		itemId3 = 10294013
	elseif nZhiYe == 2 then
		itemId1 = 14010008
		itemId2 = 10284023
		itemId3 = 10294023
	elseif nZhiYe == 3 then
		itemId1 = 14010008	
		itemId2 = 10284033
		itemId3 = 10294033
	elseif nZhiYe ==4 then
		itemId1 = 14010013
		itemId2 = 10284043
		itemId3 = 10294043
	elseif nZhiYe == 5 then
		itemId1 = 14010013	
		itemId2 = 10284053
		itemId3 = 10294053	
	elseif nZhiYe == 6 then
		itemId1 = 14010003
		itemId2 = 10288020
		itemId3 = 10298020
	elseif nZhiYe == 7 then
		itemId1 = 14010003
		itemId2 = 10288024
		itemId3 = 10298024
	elseif nZhiYe == 8 then
		itemId1 = 14010008
		itemId2 = 10288028
		itemId3 = 10298028
	elseif nZhiYe == 9 then
		itemId1 = 14010008	
		itemId2 = 10288032
		itemId3 = 10298032
	elseif nZhiYe ==10 then
		itemId1 = 14010013
		itemId2 = 10288036
		itemId3 = 10298036
	elseif nZhiYe == 11 then
		itemId1 = 14010013	
		itemId2 = 10288040
		itemId3 = 10298040	
	end
		
	BeginAddItem(sceneId)
	AddBindItem( sceneId, 11000202, 700 )	--神传水晶（11000202）*700 
	AddBindItem( sceneId, 11050003, 700 )	--高级龙眼石（11050003）*700
	AddItem( sceneId, 11060003, 50 )	--帝国银票（11060003）*50
--	AddItem( sceneId, 11000102, 1 )	--白玉钻（11000102）*1
	AddItem( sceneId, 11000123, 1 )	--墨玉钻（11000123）*1 
	AddItem( sceneId, 14040003, 1 )	--高级蓝玛瑙（14040003）*1
	AddItem( sceneId, itemId1, 1 )	--高级攻击宝石（）*1
	AddItem( sceneId, itemId2, 1 )	--神传戒指（）*1
	AddItem( sceneId, itemId3, 1 )	--神传手镯（）*1
	

	local ret = EndAddItem(sceneId,selfId)
	if ret > 0 then
		if(DepletingUsedItem(sceneId, selfId)) == 1 then
			AddItemListToPlayer(sceneId,selfId)
--			AddMoney( sceneId, selfId, 1, 1000000 )
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"打开礼包，获得了套餐道具！")
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
		else
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"使用物品异常！")
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
		end
	
	else
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"背包已满，无法得到物品！您需要至少有12个背包空间！")
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
function x418035_OnActivateEachTick( sceneId, selfId)
	return 1; --不是引导性脚本, 只保留空函数.
end
