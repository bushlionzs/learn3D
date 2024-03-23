--烟花 数字4
------------------------------------------------------------------------------------------
--一般物品的默认脚本

--脚本号

x418096_g_scriptId = 418096
--需要的等级


--**********************************
--事件交互入口
--**********************************
function x418096_ProcEventEntry( sceneId, selfId, bagIndex )
-- 不需要这个接口，但要保留空函数
end

--**********************************
--这个物品的使用过程是否类似于技能：
--系统会在执行开始时检测这个函数的返回值，如果返回失败则忽略后面的类似技能的执行。
--返回1：技能类似的物品，可以继续类似技能的执行；返回0：忽略后面的操作。
--**********************************
function x418096_IsSkillLikeScript( sceneId, selfId)
	return 1; --这个脚本需要动作支持
end

--**********************************
--直接取消效果：
--系统会直接调用这个接口，并根据这个函数的返回值确定以后的流程是否执行。
--返回1：已经取消对应效果，不再执行后续操作；返回0：没有检测到相关效果，继续执行。
--**********************************
function x418096_CancelImpacts( sceneId, selfId )
	return 0; --不需要这个接口，但要保留空函数,并且始终返回0。
end

--**********************************
--条件检测入口：
--系统会在技能检测的时间点调用这个接口，并根据这个函数的返回值确定以后的流程是否执行。
--返回1：条件检测通过，可以继续执行；返回0：条件检测失败，中断后续执行。
--**********************************
function x418096_OnConditionCheck( sceneId, selfId )
	
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
function x418096_OnDeplete( sceneId, selfId )
	return 1;
end

--**********************************
--只会执行一次入口：
--聚气和瞬发技能会在消耗完成后调用这个接口（聚气结束并且各种条件都满足的时候），而引导
--技能也会在消耗完成后调用这个接口（技能的一开始，消耗成功执行之后）。
--返回1：处理成功；返回0：处理失败。
--注：这里是技能生效一次的入口
--**********************************
function x418096_OnActivateOnce( sceneId, selfId, impactId )
	if(DepletingUsedItem(sceneId, selfId)) == 1 then
		SendSpecificImpactToUnit(sceneId, selfId, selfId, selfId,8341, 0);

		--排名相关处理
		x418096_OnTopListYanghua(sceneId,selfId)

		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, "您使用了烟花");
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
		Msg2Player(sceneId,selfId,"您使用了烟花",CHAT_TYPE_SELF,CHAT_RIGHTDOWN)
	end
end	

--**********************************
--引导心跳处理入口：
--引导技能会在每次心跳结束时调用这个接口。
--返回：1继续下次心跳；0：中断引导。
--注：这里是技能生效一次的入口
--**********************************
function x418096_OnActivateEachTick( sceneId, selfId)
	return 1; --不是引导性脚本, 只保留空函数.
end

---------------------------------------------------------------------------------------------------
--烟发触发
---------------------------------------------------------------------------------------------------
function x418096_OnTopListYanghua(mapId,playerId)

	
	--取得上次记录的周和次数
	local lastweek = GetQuestData( mapId, playerId, MD_YANHUA_WEEK[1], MD_YANHUA_WEEK[2], MD_YANHUA_WEEK[3] )
	local curcount = GetQuestData( mapId, playerId, MD_YANHUA_COUNT[1], MD_YANHUA_COUNT[2], MD_YANHUA_COUNT[3] )
	
	--取得当前周，如果当前周与上次记录的周不匹配，先清空数据
	local curweek = CallScriptFunction( 888888, "GetWorldWeek", mapId)
	if lastweek ~= curweek then
		curcount = 0
	end

	
	--次数相关，然后记录
	curcount = curcount + 1
	SetQuestData( mapId, playerId, MD_YANHUA_COUNT[1], MD_YANHUA_COUNT[2], MD_YANHUA_COUNT[3], curcount )
	SetQuestData( mapId, playerId, MD_YANHUA_WEEK[1], MD_YANHUA_WEEK[2], MD_YANHUA_WEEK[3], curweek )

	--传送相关数据到gl
	SendToplistKeyValue2GL(mapId, playerId, YANHUA_TOPLIST, curcount)
	
end