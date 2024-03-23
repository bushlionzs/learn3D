--烟花 刺陵
------------------------------------------------------------------------------------------
--一般物品的默认脚本

--脚本号

x300808_g_scriptId = 300808

--12031032

x300808_g_AvaliableScene = {50,150,250,350,
51,151,251,351,
58,158,258,358,
86,186,286,386,
0,3,
}

x300808_g_DayLimited = 5

x300808_g_UseTime					=	{                       --可使用时间段
											{min=0*60+0,  max=23*60+57},
										}

x300808_g_nValidMinute = 2   --持续多少分钟？
--需要的等级


--**********************************
--事件交互入口
--**********************************
function x300808_ProcEventEntry( sceneId, selfId, bagIndex )
-- 不需要这个接口，但要保留空函数
end

--**********************************
--这个物品的使用过程是否类似于技能：
--系统会在执行开始时检测这个函数的返回值，如果返回失败则忽略后面的类似技能的执行。
--返回1：技能类似的物品，可以继续类似技能的执行；返回0：忽略后面的操作。
--**********************************
function x300808_IsSkillLikeScript( sceneId, selfId)
	return 1; --这个脚本需要动作支持
end

--**********************************
--直接取消效果：
--系统会直接调用这个接口，并根据这个函数的返回值确定以后的流程是否执行。
--返回1：已经取消对应效果，不再执行后续操作；返回0：没有检测到相关效果，继续执行。
--**********************************
function x300808_CancelImpacts( sceneId, selfId )
	return 0; --不需要这个接口，但要保留空函数,并且始终返回0。
end

--**********************************
--条件检测入口：
--系统会在技能检测的时间点调用这个接口，并根据这个函数的返回值确定以后的流程是否执行。
--返回1：条件检测通过，可以继续执行；返回0：条件检测失败，中断后续执行。
--**********************************
function x300808_OnConditionCheck( sceneId, selfId )
	
	--校验使用的物品
	--PrintStr("x300808_OnConditionCheck")
    if IsKing(sceneId, selfId) <= 0  then
    	
		x300808_ShowTips(sceneId, selfId, "只有国王才能使用国王召集令!");
		
		return 0
    end

	--if x300808_CheckIsInZhaoJi(sceneId, selfId)>0 then
	--	x300808_ShowTips(sceneId, selfId, "正在召集期间，不可以使用，请过两分钟再试");
	--	
	--	return 0
	--end

	if x300808_IsAvaliableScene(sceneId) <= 0  then
    	
		x300808_ShowTips(sceneId, selfId, "很抱歉，本地图无法使用");
		
		return 0
    end

	if x300808_CheckTime(sceneId, selfId)<=0 then
		x300808_ShowTips(sceneId, selfId, "很抱歉，现在时间不能用召集令");
		
		return 0
	end

	if x300808_GetDayCount(sceneId, selfId)>= x300808_g_DayLimited then
		x300808_ShowTips(sceneId, selfId, format("很抱歉，每天只能使用%d次国王召集令",x300808_g_DayLimited));
		
		return 0
	end
	
	if(1~=VerifyUsedItem(sceneId, selfId)) then
		return 0
	end
	return 1; --不需要任何条件，并且始终返回1。
end


function x300808_IsAvaliableScene(sceneId)
	for i, item in x300808_g_AvaliableScene do
		if item == sceneId then
			return 1
		end
	end

	return 0
end

function x300808_CheckTime(sceneId, selfId)
	

	local hour,minute,sec =GetHourMinSec();

	local nowtime = hour*60+minute
	

	
	for i, item in x300808_g_UseTime do
		if nowtime >= item.min and nowtime <= item.max then
			
			
			return 1;
			
		end
	end

	return 0;
end


function x300808_CheckIsInZhaoJi(sceneId, selfId)
	local nCountry = GetCurCountry(sceneId, selfId)
	local today = GetDayOfYear()

	local lastday = GetCountryParam(sceneId, nCountry, CD_INDEX_ZHAOJILIN_DATE)

	if lastday == today then
		
		local lastMinute = GetCountryParam(sceneId, nCountry, CD_INDEX_ZHAOJILIN_TIME)

		local hour,minute,sec =GetHourMinSec();
		local nowtime = hour*60+minute

		if (nowtime-lastMinute)>= x300808_g_nValidMinute then
			return 0
		else
			return 1
		end

	else
		return 0
	end
end

function x300808_CheckIsOffical(sceneId, selfId)
	local officalIdList = {2,3,4,5,6,7}

	for i,officalId in officalIdList do
		if IsSpecialCountryOffical(sceneId, selfId,officalId)>0 then
			return 1
		end
	end

	return 0
end

function x300808_CheckIsBangZhu(sceneId, selfId)
	local pos = GetGuildOfficial(sceneId, selfId)
	--PrintNum(pos)
	if pos ~= 5 then --不是帮主
				return -1
	end
	return 1
end

function x300808_CheckCommonCondition(sceneId, selfId)
	if IsPlayerStateNormal(sceneId,selfId )<=0 then
		return 0
	end

	if IsPlayerMutexState(sceneId,selfId,PLAYER_STATE_MENTALGAME )>0 then
		x300808_ShowTips(sceneId, selfId, "处于答题状态，不能响应召集");
		return 0
	end

	if IsPlayerMutexState(sceneId,selfId,PLAYER_STATE_STALL )>0 then
		x300808_ShowTips(sceneId, selfId, "处于摆摊状态，不能响应召集");
		return 0
	end

	if IsPlayerMutexState(sceneId,selfId,PLAYER_STATE_DIE )>0 then
		x300808_ShowTips(sceneId, selfId, "处于死亡状态，不能响应召集");
		return 0
	end

	if IsPlayerMutexState(sceneId,selfId,PLAYER_STATE_CRASHBOX )>0 then
		x300808_ShowTips(sceneId, selfId, "处于运镖状态，不能响应召集");
		return 0
	end

	if IsPlayerMutexState(sceneId,selfId,PLAYER_STATE_BUS )>0 then
		x300808_ShowTips(sceneId, selfId, "处于BUS状态，不能响应召集");
		return 0
	end

	if IsPlayerMutexState(sceneId,selfId,PLAYER_STATE_ENJAIL )>0 then
		x300808_ShowTips(sceneId, selfId, "处于监禁状态，不能响应召集");
		return 0
	end

	if IsPlayerMutexState(sceneId,selfId,PLAYER_STATE_WEDDING )>0 then
		x300808_ShowTips(sceneId, selfId, "处于婚礼状态，不能响应召集");
		return 0
	end

	if IsPlayerMutexState(sceneId,selfId,PLAYER_STATE_TONGQUBUFF )>0 then
		x300808_ShowTips(sceneId, selfId, "处于童趣状态，不能响应召集");
		return 0
	end

	if IsPlayerMutexState(sceneId,selfId,PLAYER_STATE_TIESAN )>0 then
		x300808_ShowTips(sceneId, selfId, "处于铁人三项状态，不能响应召集");
		return 0
	end

	return 1
end

function x300808_GetTargetScene(sceneId, selfId)
	local nCountry = GetCurCountry(sceneId, selfId)
	local targetScene = GetCountryParam(sceneId, nCountry, CD_ZHAOJILIN_SCENE)

	local x = GetCountryParam(sceneId, nCountry, CD_ZHAOJILIN_POS_X)
	local z = GetCountryParam(sceneId, nCountry, CD_ZHAOJILIN_POS_Z)

	return targetScene,x,z
end


function x300808_CheckSceneLevel(sceneId, selfId,targetScene)
	local nLevel = GetLevel(sceneId, selfId)
	if nLevel<40 then
		x300808_ShowTips(sceneId, selfId, "等级不足，不能传送到国王所在场景");
		return 0
	end

	return 1
end

function x300808_CheckAgreeZhaoJi(sceneId, selfId)
	
	if x300808_CheckCommonCondition(sceneId, selfId)<=0 then
		return 0
	end

	if x300808_CheckIsOffical(sceneId, selfId)<=0 and x300808_CheckIsBangZhu(sceneId, selfId) <= 0 then
		x300808_ShowTips(sceneId, selfId, "只有国家官员或者本国的帮主才能响应召集");
		
		return 0
	end
	
	if x300808_CheckIsInZhaoJi(sceneId, selfId)<=0 then
		x300808_ShowTips(sceneId, selfId, "有效时间已过，不能响应召集");
		
		return 0
	end

	

	if x300808_IsAvaliableScene(sceneId) <= 0  then
    	
		x300808_ShowTips(sceneId, selfId, "你所在的场景不能响应召集");
		
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
function x300808_OnDeplete( sceneId, selfId )
	return 1;
end

--**********************************
--只会执行一次入口：
--聚气和瞬发技能会在消耗完成后调用这个接口（聚气结束并且各种条件都满足的时候），而引导
--技能也会在消耗完成后调用这个接口（技能的一开始，消耗成功执行之后）。
--返回1：处理成功；返回0：处理失败。
--注：这里是技能生效一次的入口
--**********************************
function x300808_OnActivateOnce( sceneId, selfId, impactId )
	if(DepletingUsedItem(sceneId, selfId)) == 1 then
		--SendSpecificImpactToUnit(sceneId, selfId, selfId, selfId,8348, 0);
		
		local nCountry = GetCurCountry(sceneId, selfId)
		--设置开始召集令时间
		local hour,minute,sec =GetHourMinSec();
		local nowtime = hour*60+minute
		SetCountryParam(sceneId, nCountry, CD_INDEX_ZHAOJILIN_TIME, nowtime)
		
		--保存场景和坐标
		local x,z =GetWorldPos(sceneId,selfId)
		SetCountryParam(sceneId, nCountry, CD_ZHAOJILIN_SCENE, sceneId)
		SetCountryParam(sceneId, nCountry, CD_ZHAOJILIN_POS_X, x)
		SetCountryParam(sceneId, nCountry, CD_ZHAOJILIN_POS_Z, z)

		CountryZhaoJi(sceneId, selfId)
		x300808_SetDayCount(sceneId, selfId);

		x300808_ShowTips(sceneId, selfId, "国王召集令已发送");
		local msg = format("x300808_OnActivateOnce 开始国王召集, guid=%x, name=%s, sceneId=%d, x=%d, z=%d, country=%d",GetPlayerGUID( sceneId,selfId ), GetName(sceneId,selfId ),sceneId,x,z,nCountry)

		WriteLog(1,msg)
	end
end	

--**********************************
--引导心跳处理入口：
--引导技能会在每次心跳结束时调用这个接口。
--返回：1继续下次心跳；0：中断引导。
--注：这里是技能生效一次的入口
--**********************************
function x300808_OnActivateEachTick( sceneId, selfId)
	return 1; --不是引导性脚本, 只保留空函数.
end

function x300808_ShowTips(sceneId, selfId, str)
	BeginQuestEvent(sceneId);
		AddQuestText(sceneId,str);
	EndQuestEvent();
	DispatchQuestTips(sceneId, selfId);
end

---------------------------------------------------------------------------------------------------
--取得当前次数
---------------------------------------------------------------------------------------------------
function x300808_GetDayCount(sceneId, selfId)
	local nCountry = GetCurCountry(sceneId, selfId)

	local today = GetDayOfYear()
	local lastday = GetCountryParam(sceneId, nCountry, CD_INDEX_ZHAOJILIN_DATE)
	
	
	if lastday ~= today then
		return 0
	end

	local daycount = GetCountryParam(sceneId, nCountry, CD_INDEX_ZHAOJILIN_DAYCOUNT)
	print(daycount)
	return daycount;
end

---------------------------------------------------------------------------------------------------
--设置当天次数
---------------------------------------------------------------------------------------------------
function x300808_SetDayCount(sceneId, selfId)
	local nCountry = GetCurCountry(sceneId, selfId)

	local today = GetDayOfYear()

	local lastday = GetCountryParam(sceneId, nCountry, CD_INDEX_ZHAOJILIN_DATE)

	if lastday ~= today then
		SetCountryParam(sceneId, nCountry, CD_INDEX_ZHAOJILIN_DATE, today)
		SetCountryParam(sceneId, nCountry, CD_INDEX_ZHAOJILIN_DAYCOUNT, 1)
	else
		local daycount = GetCountryParam(sceneId, nCountry, CD_INDEX_ZHAOJILIN_DAYCOUNT)
		SetCountryParam(sceneId, nCountry, CD_INDEX_ZHAOJILIN_DAYCOUNT, daycount+1)
	end
end


function x300808_OnAgreeZhaoJi(sceneId, selfId)
	if x300808_CheckAgreeZhaoJi(sceneId, selfId)<=0 then
		return
	end
	
	local targetScene,x,z = x300808_GetTargetScene(sceneId, selfId)

	if x300808_CheckSceneLevel(sceneId, selfId,targetScene)<=0 then
		return
	end

	x = x+random(-5,5)

	z = z+random(-5,5)
	
	if sceneId == targetScene then
		SetPos( sceneId, selfId,x,z)
	else
		if CallScriptFunction(COUNTRY_BATTLE_LITE_SCRIPT,"CheckCountryBattleLiteSceneTrans",sceneId,selfId,Map_ID) == 0 then
			return
		end
		NewWorld(sceneId, selfId, targetScene, x, z, x300808_g_scriptId);
	end
	
	x300808_ShowTips(sceneId, selfId, "您响应了国王召集令");

	local nCountry = GetCurCountry(sceneId, selfId)
	local msg = format("x300808_OnAgreeZhaoJi ok, guid=%x, name=%s, sceneId=%d, targetScene=%d, x=%d, z=%d, country=%d",GetPlayerGUID( sceneId,selfId ), GetName(sceneId,selfId ),sceneId,targetScene,x,z,nCountry)

	WriteLog(1,msg)

end
