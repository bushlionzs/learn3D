------------------------------------------------------------------------------------------
--帮会召集令脚本
--脚本号
x300818_g_scriptId 		= 300818 
--物品号
x300818_g_ItemID		= 12030015
--需要的等级
x300818_g_LevelMin		= 20

--可召集场景列表
x300818_g_SceneList 	= { 50,		--楼兰王城
							51,		--楼兰边境
							58,    --楼兰外城
							150,	--天山王城
							151,	--天山边境
							158,    --天山外城
							250,	--昆仑王城
							251,	--昆仑边境
							258,    --昆仑外城
							350,	--敦煌王城
							351,	--敦煌边境
							358,    --敦煌外城
							76,		--楼兰古道
							176,	--天山古道
							276,	--昆仑古道
							376,	--敦煌古道
							86,		--楼兰古道
							186,	--天山古道
							286,	--昆仑古道
							386,	--敦煌古道
							2,		--泰山
							3,		--中兴图
							4,		--太行山
							5,		--凤翔府
							6,		--蔡州城
							7,		--秦岭
							8,		--阿尔泰山
							9,		--碎叶城
							10,     --红沙漠
							11,     --撒马尔罕
							13,		--巴格达
							16,		--波斯高原
							17,		--莫斯科公国
							18,		--基辅公国
							19,		--波兰王国
							20,		--匈牙利
							21,		--神圣罗马帝国
							22,		--拜占庭帝国
							23,		--大马士革
							24,		--耶路撒冷
							25,		--西奈半岛
							26,		--对马岛
							27,		--福冈
							29,		--九州岛
							30,		--大理
							31,		--缅甸
							33,		--印度河
							32,		--婆罗洲
							34,		--爪哇岛
							35,		--苏门答腊
							}
--领地争夺战期间地图中范围禁用检查
x300818_g_lingdicheck 	= {							
							  { sceneId= 6,	time1 = 960,time2 = 1020,x1 = 28,x2 = 107,z1 =41,z2 =123},	--蔡州城
							  { sceneId= 9,	time1 = 960,time2 = 1020,x1 = 132,x2 = 187,z1 =15,z2 =97},	--碎叶城
							  { sceneId= 13,time1 = 960,time2 = 1020,x1 = 31,x2 = 126,z1 =165,z2 =236},   --巴格达
							  { sceneId= 18,time1 = 960,time2 = 1020,x1 = 180,x2 = 210,z1 =28,z2 =60},  	--基辅公国
							  { sceneId= 21,time1 = 960,time2 = 1020,x1 = 130,x2 = 288,z1 =70,z2 =191},	--神圣罗马帝国
							  { sceneId= 24,time1 = 960,time2 = 1020,x1 = 84,x2 = 174,z1 =55,z2 =136},	--耶路撒冷
							  --{ sceneId= 27,time1 = 960,time2 = 1020,x1 = 100,x2 = 100,z1 =100,z2 =100},   --福冈
							  --{ sceneId= 31,time1 = 960,time2 = 1020,x1 = 100,x2 = 100,z1 =100,z2 =100},	--缅甸
							  --{ sceneId= 34,time1 = 960,time2 = 1020,x1 = 100,x2 = 100,z1 =100,z2 =100},	--爪哇岛
							}
--**********************************
--事件交互入口
--**********************************
function x300818_ProcEventEntry( sceneId, selfId, bagIndex )
end

function x300818_IsSkillLikeScript( sceneId, selfId)
	return 1; --这个脚本需要动作支持
end

--GL回调
function x300818_OnReturn1(sceneId, selfId,MissionData,MissionId,targetId)
	if MissionData >=24 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "很抱歉，每小时只能使用25次帮会召集令。")
		DispatchQuestTips(sceneId, selfId)
		EndQuestEvent(sceneId)
		Msg2Player(sceneId,selfId,"很抱歉，每小时只能使用25次帮会召集令。",8,2)			
		return
	end
	if HaveItem(sceneId, selfId,x300818_g_ItemID)>0 then
			DelItem(sceneId, selfId,x300818_g_ItemID,1)
		else
			return	--异常情况
		end
	local posX,posZ = GetWorldPos(sceneId, selfId)
	SendGuildConvokeMsg(sceneId, selfId,posX,posZ)
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "您已成功使用帮会召集令")
		DispatchQuestTips(sceneId, selfId)
		EndQuestEvent(sceneId)
		Msg2Player(sceneId,selfId,"您已成功使用帮会召集令",8,2)	
	local guildid = GetGuildID(sceneId, selfId)
	SetGuildQuestData(sceneId,guildid,GD_GUILD_INDEX_CONVOKE_COUNT,1,1)
end
	
	--所有检查通过 
	--删除物品
function x300818_OnActivateOnce( sceneId, selfId )
	-- 检查是否帮主
	local offcial = GetGuildOfficial(sceneId, selfId)
	if offcial~=5 and offcial~=4 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "很抱歉，您当前不是帮主或副帮主无法使用帮会召集令。")
		DispatchQuestTips(sceneId, selfId)
		EndQuestEvent(sceneId)
		Msg2Player(sceneId,selfId,"很抱歉，您当前不是帮主或副帮主无法使用帮会召集令。",8,2)		
		return		
	end
	
	-- 检查场景是否有效场景

		if x300818_checkscene(sceneId, selfId) == 0 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, "很抱歉，您当前所在地图无法使用帮会召集令。")
			DispatchQuestTips(sceneId, selfId)
			EndQuestEvent(sceneId)
			Msg2Player(sceneId,selfId,"很抱歉，您当前所在地图无法使用帮会召集令。",8,2)		
			return		
		end

	--检查是否在领地争夺战期间且在禁止召集范围内
	if  GetWeek() == 6 then
		if x300818_lingdicheck(sceneId, selfId) == 1 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, "很抱歉，在领地争夺战期间，您无法在领地图腾附近使用帮会召集令。")
			DispatchQuestTips(sceneId, selfId)
			EndQuestEvent(sceneId)
			Msg2Player(sceneId,selfId,"很抱歉，在领地争夺战期间，您无法在领地图腾附近使用帮会召集令。",8,2)		
			return		
		end	
	end

	-- 检查位置附近的可用传送点
	if x300818_checkposition(sceneId, selfId) == 0 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "很抱歉，您所在位置的可用传送点太少，请重新选择位置发布召集令。")
		DispatchQuestTips(sceneId, selfId)
		EndQuestEvent(sceneId)
		Msg2Player(sceneId,selfId,"很抱歉，您所在位置的可用传送点太少，请重新选择位置发布召集令。",8,2)		
		return
	end
	
	-- 检查每小时使用次数
	GetGuildQuestData(sceneId, selfId, GD_GUILD_INDEX_CONVOKE_COUNT, x300818_g_scriptId, -1, "OnReturn1", -1 )
end

--**********************************
--直接取消效果：
--系统会直接调用这个接口，并根据这个函数的返回值确定以后的流程是否执行。
--返回1：已经取消对应效果，不再执行后续操作；返回0：没有检测到相关效果，继续执行。
--**********************************
function x300818_CancelImpacts( sceneId, selfId )
	return 0; --不需要这个接口，但要保留空函数,并且始终返回0。
end

--**********************************
--条件检测入口：
--系统会在技能检测的时间点调用这个接口，并根据这个函数的返回值确定以后的流程是否执行。
--返回1：条件检测通过，可以继续执行；返回0：条件检测失败，中断后续执行。
--**********************************
function x300818_OnConditionCheck( sceneId, selfId )
	return 1; --不需要任何条件，并且始终返回1。
end

--**********************************
--消耗检测及处理入口：
--系统会在技能消耗的时间点调用这个接口，并根据这个函数的返回值确定以后的流程是否执行。
--返回1：消耗处理通过，可以继续执行；返回0：消耗检测失败，中断后续执行。
--注意：这不光负责消耗的检测也负责消耗的执行。
--**********************************
function x300818_OnDeplete( sceneId, selfId )
	return 1;
end

--**********************************
--引导心跳处理入口：
--引导技能会在每次心跳结束时调用这个接口。
--返回：1继续下次心跳；0：中断引导。
--注：这里是技能生效一次的入口
--**********************************
function x300818_OnActivateEachTick( sceneId, selfId)
	return 1; --不是引导性脚本, 只保留空函数.
end

-- 检查位置合法性
function x300818_checkposition( sceneId, selfId)
	
	local posX,posZ = GetWorldPos(sceneId, selfId)
	local selfposX = floor(posX)
	local selfposZ = floor(posZ)
	
	if IsPosCanGo(sceneId,selfposX,selfposZ)==0 then
		return 0
	end
	
	return 1
end

--检查场景
function x300818_checkscene( sceneId, selfId )
	
	local ret = 0
	for i,item in x300818_g_SceneList do
		if sceneId == item then
			ret = 1
			break
		end
	end
	
	return ret
	
end

--检查是否在领地争夺战期间且在禁止召集范围内
function x300818_lingdicheck( sceneId, selfId )
	local ret = 0
    local minute = GetMinOfDay()
	local posX,posZ = GetWorldPos(sceneId, selfId)
	for i,itm in x300818_g_lingdicheck do
		if sceneId == itm.sceneId and minute >=itm.time1 and minute <= itm.time2 and posX >=itm.x1 and posX <=itm.x2 and posZ >=itm.z1 and posZ <=itm.z2 then
			ret = 1
			break
		end
	end
	return ret
end	
