--喜糖
------------------------------------------------------------------------------------------
--一般物品的默认脚本

--脚本号

x300930_g_scriptId = 300930 
x300930_g_ItemID = 12030007

--需要的等级


--**********************************
--事件交互入口
--**********************************
function x300930_ProcEventEntry( sceneId, selfId, BagIndex,rorf )
	if IsBusMember(sceneId, selfId) == 1 and rorf == 0 then
		local msg = "运镖、乘坐公交车或者护送状态时不能使用回城卷轴！"
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId, msg);
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,msg,8,2)
		return
	end
-- 不需要这个接口，但要保留空函数
end

--**********************************
--这个物品的使用过程是否类似于技能：
--系统会在执行开始时检测这个函数的返回值，如果返回失败则忽略后面的类似技能的执行。
--返回1：技能类似的物品，可以继续类似技能的执行；返回0：忽略后面的操作。
--**********************************
function x300930_IsSkillLikeScript( sceneId, selfId)
	return 1; --这个脚本需要动作支持
end

--**********************************
--直接取消效果：
--系统会直接调用这个接口，并根据这个函数的返回值确定以后的流程是否执行。
--返回1：已经取消对应效果，不再执行后续操作；返回0：没有检测到相关效果，继续执行。
--**********************************
function x300930_CancelImpacts( sceneId, selfId )
	return 0; --不需要这个接口，但要保留空函数,并且始终返回0。
end

--**********************************
--条件检测入口：
--系统会在技能检测的时间点调用这个接口，并根据这个函数的返回值确定以后的流程是否执行。
--返回1：条件检测通过，可以继续执行；返回0：条件检测失败，中断后续执行。
--**********************************
function x300930_OnConditionCheck( sceneId, selfId, BagIndex)
	
	--校验使用的物品
	if GetGuildID( sceneId, selfId ) == -1 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "很抱歉，您没有帮会");
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,"很抱歉，您没有帮会",8,2)
		return
	end
	
	if IsBusMember(sceneId, selfId) == 1 then
		local msg = "运镖、乘坐公交车或者护送状态时不能使用领地传送石！"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, msg);
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,msg,8,2)
		return 
	end
	
	if sceneId == 12 then
		local msg = "监狱中不能使用领地传送石！"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, msg);
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,msg,8,2)
		return 0
	end

	if IsHaveSpecificImpact( sceneId, selfId, 7702 ) > 0 then
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, "扛着旗子不能使用领地传送石！");
		EndQuestEvent(sceneId);
		DispatchQuestTips(sceneId,selfId);
		Msg2Player(sceneId,selfId,"扛着旗子不能使用领地传送石！",8,2)
		return 0
	end
	
	local IsHaveFlag = IsHaveSpecificImpact(sceneId, selfId, 7536  )
    if IsHaveFlag ~= 0 then
    	local msg = "在暴龙大作战期间，不能传送"
    	BeginQuestEvent(sceneId)
			AddQuestText(sceneId, msg);
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,msg,8,2)
		return 0
    end
    
    IsHaveFlag = IsHaveSpecificImpact(sceneId, selfId, 7537 )
    if IsHaveFlag ~= 0 then
    	local msg = "在暴龙大作战期间，不能传送"
    	BeginQuestEvent(sceneId)
			AddQuestText(sceneId, msg);
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,msg,8,2)
		return 0
    end
	if GetSceneType(sceneId) == 2 then
		local msg = "战场内，不能传送"
    	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, msg);
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,msg,8,2)
		return -1
	end
	
	if GetSceneType(sceneId) == 1 then
		local msg = "副本内，不能传送"
    	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, msg);
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,msg,8,2)
		return -1
	end
	
	local iCount = GetItemCountInBag( sceneId, selfId, 13080024)
    if iCount > 0 then
        DelItem( sceneId, selfId, 13080024, iCount)
    end
	
	local selfType = GetObjType(sceneId, selfId)
	
	if selfType == 1 then 
		------------------------------------------------------
		if IsHaveQuestNM( sceneId, selfId, 7537) ~= 0 or  IsHaveQuestNM( sceneId, selfId, 7538) ~= 0 or IsHaveQuestNM( sceneId, selfId, 7539) ~= 0 then
			Msg2Player(sceneId,selfId,"很抱歉，未完成铁人三项任务时无法通往其他场景！",8,2)
			return
		end
		--以上用于铁人三项禁止传送的处理
		------------------------------------------------------
	end
	
	if sceneId == 14 then
        	SetPlayerMutexState( sceneId, selfId, PLAYER_STATE_DANCERY, 0)
            -- 恢复变身
            if IsHaveSpecificImpact( sceneId, selfId, 7651) == 1 then
                CancelSpecificImpact( sceneId, selfId, 7651)
            elseif IsHaveSpecificImpact( sceneId, selfId, 7652) == 1 then
                CancelSpecificImpact( sceneId, selfId, 7652)
            elseif IsHaveSpecificImpact( sceneId, selfId, 7653) == 1 then
                CancelSpecificImpact( sceneId, selfId, 7653)
            elseif IsHaveSpecificImpact( sceneId, selfId, 7654) == 1 then
                CancelSpecificImpact( sceneId, selfId, 7654)
            elseif IsHaveSpecificImpact( sceneId, selfId, 7655) == 1 then
                CancelSpecificImpact( sceneId, selfId, 7655)
            elseif IsHaveSpecificImpact( sceneId, selfId, 7656) == 1 then
                CancelSpecificImpact( sceneId, selfId, 7656)
            end
	end
	
	if(1~=VerifyUsedItem(sceneId, selfId)) then
		return 0
	end
	return 1; --不需要任何条件，并且始终返回1。
end

function x300930_GuildLairdSceneIdTrans(sceneId, selfId, nLairdMapId)
	if nLairdMapId == 6 then
		TimerCommand( sceneId, selfId, 1, 7010, 3, -1, -1, -1 )
		if sceneId == nLairdMapId then
			SetPos(sceneId,selfId,65,94)
		else
			NewWorld(sceneId,selfId,6,65,94, 300930)
		end
	elseif nLairdMapId == 9 then
		TimerCommand( sceneId, selfId, 1, 7010, 3, -1, -1, -1 )
		if sceneId == nLairdMapId then
			SetPos(sceneId,selfId,163,56)
		else
			NewWorld(sceneId,selfId,9,163,56, 300930)
		end
	elseif nLairdMapId == 13 then
		TimerCommand( sceneId, selfId, 1, 7010, 3, -1, -1, -1 )
		if sceneId == nLairdMapId then
			SetPos(sceneId,selfId,75,193)
		else
			NewWorld(sceneId,selfId,13,75,193, 300930)
		end
	elseif nLairdMapId == 18 then
		TimerCommand( sceneId, selfId, 1, 7010, 3, -1, -1, -1 )
		if sceneId == nLairdMapId then
			SetPos(sceneId,selfId,196,57)
		else
			NewWorld(sceneId,selfId,18,196,57, 300930)
		end
	elseif nLairdMapId == 21 then
		TimerCommand( sceneId, selfId, 1, 7010, 3, -1, -1, -1 )
		if sceneId == nLairdMapId then
			SetPos(sceneId,selfId,222,130)
		else
			NewWorld(sceneId,selfId,21,222,130, 300930)
		end
	elseif nLairdMapId == 24 then
		TimerCommand( sceneId, selfId, 1, 7010, 3, -1, -1, -1 )
		if sceneId == nLairdMapId then
			SetPos(sceneId,selfId,118,101)
		else
			NewWorld(sceneId,selfId,24,118,101, 300930)
		end
	elseif nLairdMapId == 27 then
		TimerCommand( sceneId, selfId, 1, 7010, 3, -1, -1, -1 )
		if sceneId == nLairdMapId then
			SetPos(sceneId,selfId,204,202)
		else
			NewWorld(sceneId,selfId,27,204,202, 300930)
		end
	elseif nLairdMapId == 31 then
		TimerCommand( sceneId, selfId, 1, 7010, 3, -1, -1, -1 )
		if sceneId == nLairdMapId then
			SetPos(sceneId,selfId,204,202)
		else
			NewWorld(sceneId,selfId,31,204,202, 300930)
		end
	elseif nLairdMapId == 34 then
		TimerCommand( sceneId, selfId, 1, 7010, 3, -1, -1, -1 )
		if sceneId == nLairdMapId then
			SetPos(sceneId,selfId,204,202)
		else
			NewWorld(sceneId,selfId,34,204,202, 300930)
		end
	end
	
	if impactId ~= -1 then
		SendSpecificImpactToUnit(sceneId, selfId, selfId, selfId, 7720, 0);
	end
end
--**********************************
--消耗检测及处理入口：
--系统会在技能消耗的时间点调用这个接口，并根据这个函数的返回值确定以后的流程是否执行。
--返回1：消耗处理通过，可以继续执行；返回0：消耗检测失败，中断后续执行。
--注意：这不光负责消耗的检测也负责消耗的执行。
--**********************************
function x300930_OnDeplete( sceneId, selfId )

	--check guild
	local nGuildID = GetGuildID(sceneId,selfId)
	if nGuildID < 0 then
		return 0
	end

	--check laird map
	local nLairdMap0,nLairdMap1,nLairdMap2 = GetGuildLairdSceneId(nGuildID)
	if nLairdMap0 <= 0 then
		Msg2Player(sceneId,selfId,"无法使用，您没有领地",8,3)
		Msg2Player(sceneId,selfId,"目前您的帮会尚未占领任何领地",8,2)
		return 0
	end
	
	--OK
	x300930_GuildLairdSceneIdTrans(sceneId, selfId, nLairdMap0)
	--depleting
	DepletingUsedItem(sceneId, selfId)
	return 1;
end

function x300930_OnAddMoney(sceneId, selfId)
end

function x300930_OnAddItemByLevel(sceneId, selfId)	
end

function x300930_OnAddItem(sceneId, selfId, itemId)
end

--**********************************
--只会执行一次入口：
--聚气和瞬发技能会在消耗完成后调用这个接口（聚气结束并且各种条件都满足的时候），而引导
--技能也会在消耗完成后调用这个接口（技能的一开始，消耗成功执行之后）。
--返回1：处理成功；返回0：处理失败。
--注：这里是技能生效一次的入口
--**********************************
function x300930_OnActivateOnce( sceneId, selfId, impactId )	
end

--**********************************
--引导心跳处理入口：
--引导技能会在每次心跳结束时调用这个接口。
--返回：1继续下次心跳；0：中断引导。
--注：这里是技能生效一次的入口
--**********************************
function x300930_OnActivateEachTick( sceneId, selfId)
	return 1; --不是引导性脚本, 只保留空函数.
end
