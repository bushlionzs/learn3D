-- 还童丹


-- 宠物通用功能脚本
x404834_g_petCommonId = PETCOMMON

--******************************************************************************
-- 以下部分需要是需要修改的部分
--******************************************************************************

--脚本号 （改成正确脚本号）
x404834_g_scriptId = 404834

--标准效果ID （改成宠物使用驯养道具的特效）
--g_ImpactID = 0

--******************************************************************************
-- 以上部分需要是需要修改的部分
--******************************************************************************

--脚本

--**********************************
--必须返回 1 才能正确执行以下流程
--**********************************
function x404834_IsSkillLikeScript( sceneId, selfId)
	return 1
end

--**********************************
--条件检测入口：
--系统会在技能检测的时间点调用这个接口，并根据这个函数的返回值确定以后的流程是否执行。
--返回1：条件检测通过，可以继续执行；返回0：条件检测失败，中断后续执行。
--**********************************
function x404834_OnConditionCheck( sceneId, selfId )
	--校验使用的物品
	if(1~=VerifyUsedItem(sceneId, selfId)) then
		return 0
	end

	local petGUID_H = GetHighSectionOfTargetPetGuid( sceneId, selfId )
	local petGUID_L = GetLowSectionOfTargetPetGuid( sceneId, selfId )

	if PetCanReturnToChild( sceneId, selfId, petGUID_H, petGUID_L ) == 0 then
		return 0
	end

	return 1
end

--**********************************
--消耗检测及处理入口：
--系统会在技能消耗的时间点调用这个接口，并根据这个函数的返回值确定以后的流程是否执行。
--返回1：消耗处理通过，可以继续执行；返回0：消耗检测失败，中断后续执行。
--注意：这不光负责消耗的检测也负责消耗的执行。
--**********************************
function x404834_OnDeplete( sceneId, selfId )
	if(DepletingUsedItem(sceneId, selfId)) == 1 then
		return 1
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
function x404834_OnActivateOnce( sceneId, selfId )
	local petGUID_H = GetHighSectionOfTargetPetGuid( sceneId, selfId )
	local petGUID_L = GetLowSectionOfTargetPetGuid( sceneId, selfId )

	PetReturnToChild( sceneId, selfId, petGUID_H, petGUID_L )

--	SendSpecificImpactToUnit(sceneId, selfId, selfId, selfId, g_ImpactID, 0)
	return 1
end

--**********************************
--引导心跳处理入口：
--引导技能会在每次心跳结束时调用这个接口。
--返回：1继续下次心跳；0：中断引导。
--注：这里是技能生效一次的入口
--**********************************
function x404834_OnActivateEachTick( sceneId, selfId )
	return 1
end

-- 这个函数没有什么用，但是必须有
function x404834_CancelImpacts( sceneId, selfId )
	return 0
end
