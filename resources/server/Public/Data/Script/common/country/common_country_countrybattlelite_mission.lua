--屠城战任务脚本

x310155_g_ScriptId = 310155
x310155_g_BonusScriptId = 310151
x310155_g_MissionId = 7559
x310155_g_LevelLess	= 	40 
x310155_g_MissionName="【国家】屠城战"
x310155_g_TickBuf	= 8727
x310155_g_BufID = {8719,8720,8721,8722,8723,8724,8725,8726,8727}--玩家BUFID,当玩家接受屠城战时,将从此表获取BUFID,此表按顺序为:楼兰,莱茵,昆仑,敦煌


----------------------------------------------------------
--枚举
----------------------------------------------------------
function x310155_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)

		--合服开关
    if GetMergeDBToggle() == 1 then
        return
    end
    
    --升级数据库开关
		local UpdateDBflag = GetUpdateDBBeforeToggle()
		if UpdateDBflag==1 then
			return
		end
    
    --测试服开关
    --if GetTestServerToggle() == 0 then
    --    return
    --end

    --战场自己的开关
    if GetBattleSceneToggle( BATTLESCENE_TYPE_COUNTRYBATTLELITE ) == 0 then
        return
    end
    
    
    --级别不够
    if GetLevel(sceneId,selfId) < x310155_g_LevelLess then
    	return
    end
    
    local str = "【国家】参加屠城战"
    
    --有此任务，则不显示相关对话框
	if IsHaveQuest(sceneId,selfId, x310155_g_MissionId) > 0 then
		
		--是今天接的任务
		local misIndex = GetQuestIndexByID( sceneId, selfId, x310155_g_MissionId)
		local nDay = GetQuestParam( sceneId,selfId,misIndex,4 ) - 100
		local nCurDayTime = GetDayOfYear()
		
		if nDay == nCurDayTime then
			str = "【国家】屠城战奖励领取"
		end 
	end    
    
    --加入战场按钮
    local state = GetQuestStateNM(sceneId,selfId,NPCId,x310155_g_MissionId)
    AddQuestNumText( sceneId, x310155_g_MissionId, str, state );  
end

----------------------------------------------------------
--显示任务信息
----------------------------------------------------------
function x310155_DispatchMissionInfo( sceneId, selfId, NPCId )
end

----------------------------------------------------------
--默认对话框
----------------------------------------------------------
function x310155_ProcEventEntry(sceneId, selfId, NPCId, MissionId,idExt)	
    
    --级别不够
    if GetLevel(sceneId,selfId) < x310155_g_LevelLess then
    	return
    end
    
    if IsHaveQuest(sceneId,selfId, x310155_g_MissionId) > 0 then
		
		--是今天接的任务
		local misIndex = GetQuestIndexByID( sceneId, selfId, x310155_g_MissionId)
		local nDay = GetQuestParam( sceneId,selfId,misIndex,4 ) - 100
		local nCurDayTime = GetDayOfYear()
		
		if nDay == nCurDayTime then
			--检查是否走新流程
			if CallScriptFunction(COUNTRY_BATTLE_LITE_SCRIPT,"IsNewFlow",sceneId,selfId) ~= 1 then
				if CallScriptFunction( COUNTRY_BATTLE_LITE_SCRIPT, "GetCountryBattleLite_CountryCamp", sceneId, selfId)  >= 0 then
					BeginQuestEvent(sceneId)
					AddQuestText(sceneId,"#Y【国家】屠城战奖励领取#W#r\t只能在当天【屠城战】结束之后的21：00-21：20或者屠城战提前结束10分钟内领取奖励！")
					EndQuestEvent(sceneId)
					DispatchQuestEventList(sceneId,selfId,NPCId)
					return
				end
			else
				
				if CallScriptFunction(COUNTRY_BATTLE_LITE_SCRIPT,"IsCanReciveBonus",sceneId,selfId) ~= 1 then
					BeginQuestEvent(sceneId)
					AddQuestText(sceneId,"#Y【国家】屠城战奖励领取#W#r\t由于您的国家提前结束【屠城战】，只能在结束之后的10分钟内领取奖励！")
					EndQuestEvent(sceneId)
					DispatchQuestEventList(sceneId,selfId,NPCId)
					return
				end
				
			end
			
			local nCheckResult = CallScriptFunction(x310155_g_BonusScriptId,"CheckValid",sceneId,selfId)
			if nCheckResult ~= 1 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"#Y【国家】屠城战奖励领取#W#r\t只能在当天【屠城战】结束之后的21：00-21：20领取奖励！")
				EndQuestEvent(sceneId)
				DispatchQuestEventList(sceneId,selfId,NPCId)
				return	
			end
	
	    	--屠城战是否开启
		    
	    	--发给奖励
	    	CallScriptFunction(x310155_g_BonusScriptId,"ProcEventEntry",sceneId,selfId,NPCId,x310155_g_BonusScriptId,-1 )	    
		    
		    return
		else
			
				--合服开关
		    if GetMergeDBToggle() == 1 then
		        return
		    end
		    
		    --升级数据库开关
				local UpdateDBflag = GetUpdateDBBeforeToggle()
				if UpdateDBflag==1 then
					return
				end
		    
		    --测试服开关
		    --if GetTestServerToggle() == 0 then
		    --    return
		    --end
		
		    --战场自己的开关
		    if GetBattleSceneToggle( BATTLESCENE_TYPE_COUNTRYBATTLELITE ) == 0 then
		        return
		    end
		    
		    --战场有没有打开
		    if CallScriptFunction(COUNTRY_BATTLE_LITE_SCRIPT,"GetCountryBattleLite_CountryCamp",sceneId,selfId) < 0 then
		    	BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"您现在还不能参加【国家】屠城战！")
				EndQuestEvent(sceneId)
				DispatchQuestEventList(sceneId,selfId,NPCId)
		    	return
		    end
		    
		    --有此任务，则不显示相关对话框
			if IsHaveQuest(sceneId,selfId, x310155_g_MissionId) > 0 then
				
				--是今天接的任务
				local misIndex = GetQuestIndexByID( sceneId, selfId, x310155_g_MissionId)
				local nDay = GetQuestParam( sceneId,selfId,misIndex,4 ) - 100
				local nCurDayTime = GetDayOfYear()
				if nDay == nCurDayTime then
					BeginQuestEvent(sceneId)
					AddQuestText(sceneId,"你已经参加过【国家】屠城战了！")
					EndQuestEvent(sceneId)
					DispatchQuestEventList(sceneId,selfId,NPCId)
					return
				end
			end
	    	
	    	--显示接任务信息（NPC处接任务)，接任务的NPC必须在王城或是边境
	    	BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"#Y【国家】参加屠城战#W#r\t【国家】屠城战已经开启了，要参加吗？您只能在屠城战开启当天的#G20：00-20：20#W之间参加屠城战，参加屠城战后，如果您想要离开#G中兴府，四国的王城，边境和古道#W，您必须先#R放弃屠城战任务#W，才可以进行传送。")
			EndQuestEvent(sceneId)
			DispatchQuestInfoNM(sceneId,selfId,NPCId,x310155_g_ScriptId,x310155_g_MissionId)
			
		end 
	end    
	
	
	--默认处理
		--合服开关
    if GetMergeDBToggle() == 1 then
        return
    end
    
    --升级数据库开关
		local UpdateDBflag = GetUpdateDBBeforeToggle()
		if UpdateDBflag==1 then
			return
		end
    
    --测试服开关
    --if GetTestServerToggle() == 0 then
    --    return
    --end

    --战场自己的开关
    if GetBattleSceneToggle( BATTLESCENE_TYPE_COUNTRYBATTLELITE ) == 0 then
        return
    end
    
    --战场有没有打开
    if CallScriptFunction(COUNTRY_BATTLE_LITE_SCRIPT,"GetCountryBattleLite_CountryCamp",sceneId,selfId) < 0 then
    	BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"#Y【国家】参加屠城战#W#r\t您现在还不能参加【国家】屠城战！")
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,NPCId)
    	return
    end
    
    --有此任务，则不显示相关对话框
	if IsHaveQuest(sceneId,selfId, x310155_g_MissionId) > 0 then
		
		--是今天接的任务
		local misIndex = GetQuestIndexByID( sceneId, selfId, x310155_g_MissionId)
		local nDay = GetQuestParam( sceneId,selfId,misIndex,4 ) - 100
		local nCurDayTime = GetDayOfYear()
		if nDay == nCurDayTime then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"#Y【国家】参加屠城战#W#r\t你已经参加过【国家】屠城战了！")
			EndQuestEvent(sceneId)
			DispatchQuestEventList(sceneId,selfId,NPCId)
			return
		end
	end
	
	--显示接任务信息（NPC处接任务)，接任务的NPC必须在王城或是边境
	BeginQuestEvent(sceneId)
	AddQuestText(sceneId,"#Y【国家】参加屠城战#W#r\t【国家】屠城战已经开启了，要参加吗？您只能在屠城战开启当天的#G20：00-20：20#W之间参加屠城战，参加屠城战后，如果您离开#G中兴府，四国的王城，边境和古道#W，您必须先#R放弃屠城战任务#W，才可以进行传送。。")
	EndQuestEvent(sceneId)
	DispatchQuestInfoNM(sceneId,selfId,NPCId,x310155_g_ScriptId,x310155_g_MissionId)
end


----------------------------------------------------------
--检查接受
----------------------------------------------------------
function x310155_ProcAcceptCheck(sceneId, selfId, NPCId)
	return 1
end

----------------------------------------------------------
--检查交任务
----------------------------------------------------------
function x310155_CheckSubmit( sceneId, selfId, NPCId)
	return 1
end

----------------------------------------------------------
--检查接受任务，接任务的NPC只能在王城或是边境
----------------------------------------------------------
function x310155_ProcQuestAccept( sceneId, selfId, NPCId, MissionId )

		--合服开关
    if GetMergeDBToggle() == 1 then
        return
    end
    
    --升级数据库开关
		local UpdateDBflag = GetUpdateDBBeforeToggle()
		if UpdateDBflag==1 then
			return
		end
    
    --测试服开关
    --if GetTestServerToggle() == 0 then
    --    return
    --end
    
    
    --级别不够
    if GetLevel(sceneId,selfId) < x310155_g_LevelLess then
    	return
    end

    --战场自己的开关
    if GetBattleSceneToggle( BATTLESCENE_TYPE_COUNTRYBATTLELITE ) == 0 then
        return
    end

	--检查是否开启状态
	local campFlag = CallScriptFunction(COUNTRY_BATTLE_LITE_SCRIPT,"GetCountryBattleLite_CountryCamp", sceneId, selfId)
	local nMatchCountry= CallScriptFunction(COUNTRY_BATTLE_LITE_SCRIPT,"GetCountryBattleLite_MatchCountry", sceneId, selfId)
	
	if campFlag < 0 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"【国家】屠城战没有开启！")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return
	end
	
	--检查今天是否已经接过
	if x310155_IsMissionCanAccept( sceneId,selfId ) == 0 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"今天您已经参加过【国家】屠城战了！")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return
	end
	
	local minTime = GetMinOfDay()
    
    --在不在时间段内
    local nFrom = 20*60 + 0
    local nTo   = 20*60 + 20

    if minTime < nFrom or minTime > nTo then
    	BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"参加【国家】屠城战时间已过！")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
        return
    end
    
    --蒙面状态不能参加屠城战
    if IsHideName(sceneId,selfId) ~= 0 then
    	BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"蒙面状态不能参加【国家】屠城战！")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
    	return
    end
	
	--如果没有接过，以后为接任务流程
	if IsHaveQuest(sceneId,selfId, x310155_g_MissionId) == 0 then
		
		--任务满了
		if IsQuestFullNM(sceneId,selfId)==1 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"您的任务已经满了，无法参加【国家】屠城战！")
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
			return 
		end
		
		if sceneId == 89 or sceneId == 189 or sceneId == 289 or sceneId == 389 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"此场景不能接【国家】屠城战任务！")
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
			return
		end
		--添加相关任务
		if AddQuest(sceneId,selfId,x310155_g_MissionId,x310155_g_ScriptId,0,0,0,1) ~= 1 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"参加【国家】屠城战失败，无法添加相关任务！")
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
			return
		end
	end
	
	
	GamePlayScriptLog( sceneId, selfId, 1511)
	
	local nCurDayTime = GetDayOfYear()
	
	--重置任务数据
	local misIndex = GetQuestIndexByID( sceneId, selfId, x310155_g_MissionId )
	
	SetQuestParam( sceneId,selfId,x310155_g_MissionId,3,0)					--设定结束标记
	SetQuestParam( sceneId,selfId,x310155_g_MissionId,4,nCurDayTime+100)		--设定日期
	SetQuestParam( sceneId,selfId,x310155_g_MissionId,5,campFlag)				--设定阵营
	SetQuestParam( sceneId,selfId,x310155_g_MissionId,6,nMatchCountry)		--设定敌对国家
	
	--设置接任务日期
	x310155_SetMissionAcceptDate(sceneId,selfId)
	
	--给玩家添加BUFID
	local nCountry = GetCurCountry(sceneId,selfId)
	local nBufID = x310155_g_BufID[nCountry*2+1]
	if nBufID ~= -1 then
		if GetSex(sceneId,selfId) == 0 then
			nBufID = nBufID + 1
		end
		SendSpecificImpactToUnit(sceneId,selfId,selfId,selfId,nBufID,0)
		SendSpecificImpactToUnit(sceneId,selfId,selfId,selfId,x310155_g_TickBuf,0)
	end
	
	--主动刷新数据
	x310155_ProcQuestLogRefresh	( sceneId,selfId,x310155_g_MissionId)
	
	--给出相关提示
	x310155_Msg2toplayer( sceneId, selfId,0)
    
    local name = GetName(sceneId,selfId)
    if name == nil then
        name = "<ErrorName>"
    end

    local nCountry = GetCurCountry( sceneId,selfId)
    local strMsg = format("CBL:<Info>CountryBattleLiteChangeScene sceneId = %d,name = %s Country = %d,nMatchCountry = %d campFlag = %d",sceneId, name,nCountry,nMatchCountry,campFlag )
    WriteLog( 1, strMsg ) 
	     
end

----------------------------------------------------------
--删除BUF
----------------------------------------------------------
function x310155_CancelBufId( sceneId,selfId )

	for i,item in x310155_g_BufID do
		if IsHaveSpecificImpact(sceneId,selfId,item) == 1 then
			CancelSpecificImpact(sceneId,selfId,item)
		end
	end

end

----------------------------------------------------------
--放弃任务
----------------------------------------------------------
function x310155_ProcQuestAbandon(sceneId, selfId, MissionId)
	if IsHaveQuest(sceneId,selfId, x310155_g_MissionId) <= 0 then
		return 
	end
	DelQuest(sceneId, selfId, x310155_g_MissionId)
  	x310155_Msg2toplayer( sceneId, selfId,1)
  	x310155_CancelBufId( sceneId,selfId )
  	
  	GamePlayScriptLog( sceneId, selfId, 1513)			
end

----------------------------------------------------------
--交任务
----------------------------------------------------------
function x310155_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)
end

----------------------------------------------------------
--消息事件
----------------------------------------------------------
function x310155_Msg2toplayer( sceneId, selfId,type)
		
	if type == 0 then
		--接受任务，给出相关提示
		Msg2Player(sceneId, selfId, "您参加了"..x310155_g_MissionName.."！", 0, 2)
	  	Msg2Player(sceneId, selfId, "您参加了"..x310155_g_MissionName.."！", 0, 3)
	elseif type == 1 then
		--放弃任务，给出相关提示
		Msg2Player(sceneId, selfId, "您退出了"..x310155_g_MissionName.."！", 0, 2)
		Msg2Player(sceneId, selfId, "您退出了"..x310155_g_MissionName.."！", 0, 3)
	elseif type == 2 then
		--完成任务，没有相关提交
	end
end

----------------------------------------------------------
--杀死任务怪事件
----------------------------------------------------------
function x310155_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
end

----------------------------------------------------------
--进入区域事件
----------------------------------------------------------
function x310155_ProcAreaEntered(sceneId, selfId, zoneId, MissionId )
end

----------------------------------------------------------
--定时器事件
----------------------------------------------------------
function x310155_ProcTiming(sceneId, selfId, ScriptId, MissionId)
end

----------------------------------------------------------
--离开区域事件
----------------------------------------------------------
function x310155_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId)
end

----------------------------------------------------------
--物品改变事件
----------------------------------------------------------
function x310155_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
end

----------------------------------------------------------
--和NPC交互任务接口
----------------------------------------------------------
function x310155_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
	
--	local bFind  = 0
--    for i ,item in x310155_g_NpcGUID do
--        if item.guid == npcGuid then
--            bFind = 1
--            break
--        end
--    end
--    
--    if bFind == 0 then
--        return
--    end
--    
--    --有任务的情况下才接受响应
--	if IsHaveQuest(sceneId,selfId, x310155_g_MissionId) > 0 then
--				
--		--没有其他异常情况，则显示交任务对话框
--		local state = GetQuestStateNM(sceneId,selfId,npcId,x310155_g_MissionId)
--		AddQuestTextNM( sceneId, selfId, npcId, x310155_g_MissionId, state, 999 )
--	end
end

----------------------------------------------------------
--任务完成
----------------------------------------------------------
function x310155_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
end

----------------------------------------------------------
--定点使用物品
----------------------------------------------------------
function x310155_PositionUseItem( sceneId, selfId, BagIndex, impactId )
end

----------------------------------------------------------
--打开箱子
----------------------------------------------------------
function x310155_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
end

----------------------------------------------------------
--回收物品
----------------------------------------------------------
function x310155_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
end

----------------------------------------------------------
--采集
----------------------------------------------------------
function x310155_OnProcOver( sceneId, selfId, targetId )
end

----------------------------------------------------------
--采集
----------------------------------------------------------
function x310155_OpenCheck( sceneId, selfId, targetId )
end

----------------------------------------------------------
--任务刷新
----------------------------------------------------------
function x310155_ProcQuestLogRefresh( sceneId,selfId,MissionId)

	if sceneId ~= 3 and 
	   sceneId ~= 50 and sceneId ~= 150 and sceneId ~= 250 and sceneId ~= 350 and
	   sceneId ~= 51 and sceneId ~= 151 and sceneId ~= 251 and sceneId ~= 351 and
	   sceneId ~= 58 and sceneId ~= 158 and sceneId ~= 258 and sceneId ~= 358 and
	   sceneId ~= 68 and sceneId ~= 168 and sceneId ~= 268 and sceneId ~= 368 and
	   sceneId ~= 76 and sceneId ~= 176 and sceneId ~= 276 and sceneId ~= 376 and 
	   sceneId ~= 86 and sceneId ~= 186 and sceneId ~= 286 and sceneId ~= 386 and 
	   sceneId ~= 104 and sceneId ~= 204 and sceneId ~= 304 and sceneId ~= 404 and
	   sceneId ~= 105 and sceneId ~= 205 and sceneId ~= 305 and sceneId ~= 405 and
	   sceneId ~= 106 and sceneId ~= 206 and sceneId ~= 306 and sceneId ~= 406 and
	   sceneId ~= 107 and sceneId ~= 207 and sceneId ~= 307 and sceneId ~= 407 and
	   sceneId ~= 108 and sceneId ~= 208 and sceneId ~= 308 and sceneId ~= 408 and
	   sceneId ~= 109 and sceneId ~= 209 and sceneId ~= 309 and sceneId ~= 409 and
	   sceneId ~= 110 and sceneId ~= 210 and sceneId ~= 310 and sceneId ~= 410 and
	   sceneId ~= 111 and sceneId ~= 211 and sceneId ~= 311 and sceneId ~= 411 and
	   sceneId ~= 91 and sceneId ~= 191 and sceneId ~= 291 and sceneId ~= 391 then 
	   return
	end

	local bHaveMission = IsHaveQuestNM(sceneId, selfId, x310155_g_MissionId );
	if bHaveMission <= 0 then
		return
	end
		
	local misIndex = GetQuestIndexByID( sceneId, selfId, x310155_g_MissionId )
	local nFinished = GetQuestParam( sceneId, selfId, misIndex, 3 )
	local nDay = GetQuestParam( sceneId, selfId, misIndex, 4 ) - 100
	local nCampFlag = GetQuestParam( sceneId, selfId, misIndex, 5 )
	local nMatchCountry = GetQuestParam( sceneId, selfId, misIndex, 6 )
	
	--检查日期
	local nCurDayTime = GetDayOfYear()
	local str = ""
	local nCountryID = GetCurCountry( sceneId, selfId)
	if nCountryID == 0 then
		str ="@npc_123724"
	elseif nCountryID == 1 then
		str ="@npc_126021"
	elseif nCountryID == 2 then
		str ="@npc_129021"
	elseif nCountryID == 3 then
		str ="@npc_132021"
	end
	if nCurDayTime ~= nDay then
		BeginQuestEvent(sceneId)
	    AddQuestLogCustomText( sceneId,
								"",							--标题
								"",      					--任务名字
								"#Y【国家】屠城战#W已经结束，很遗憾您错过了领奖时间，无法领取奖励。（领奖时间为屠城战活动当日21：00-21：20）",			--任务目标
								str,							--任务NPC
								"", 	     				--任务攻略
								"#Y【国家】屠城战#W已经结束，很遗憾您错过了领奖时间，无法领取奖励。（领奖时间为屠城战活动当日21：00-21：20）",				--任务描述
								""							--任务小提示
								)
		EndQuestEvent(sceneId)
		DispatchQuestLogUpdate(sceneId, selfId, x310155_g_MissionId)
		return		
	else
		
		--检查是否走新流程
		if CallScriptFunction(COUNTRY_BATTLE_LITE_SCRIPT,"IsNewFlow",sceneId,selfId) == 1 then
		
			
			--检查是否可以领奖
			if CallScriptFunction(COUNTRY_BATTLE_LITE_SCRIPT,"IsCanReciveBonus",sceneId,selfId) ~= 1 then
				BeginQuestEvent(sceneId)
				AddQuestLogCustomText( sceneId,
										"",							--标题
										"",      					--任务名字
										"#Y【国家】屠城战#W已经提前结束，很遗憾您错过了领奖时间，无法领取奖励。（领奖时间为屠城战状态完成后的10分钟内或21：00-21：20之间）",			--任务目标
										str,							--任务NPC
										"", 	     				--任务攻略
										"#Y【国家】屠城战#W已经提前结束，很遗憾您错过了领奖时间，无法领取奖励。（领奖时间为屠城战状态完成后的10分钟内或21：00-21：20之间）",				--任务描述
										""							--任务小提示
										)
				EndQuestEvent(sceneId)
				DispatchQuestLogUpdate(sceneId, selfId, x310155_g_MissionId)
				return
			else
				--如果已经结束，但是并没过期，则直接显示领奖相关
				BeginQuestEvent(sceneId)
				AddQuestLogCustomText( sceneId,
										"",							--标题
										"",      					--任务名字
										"#Y【国家】屠城战#W已经提前结束，请在10分钟内前往#R国家管理员#W处领取奖励。",			--任务目标
										str,							--任务NPC
										"", 	     				--任务攻略
										"#Y【国家】屠城战#W已经提前结束，请在10分钟内前往#R国家管理员#W处领取奖励。",				--任务描述
										""							--任务小提示
										)
				EndQuestEvent(sceneId)
				DispatchQuestLogUpdate(sceneId, selfId, x310155_g_MissionId)
				return 
			end
			
		else
			--还在当天，但是在不在领奖时间段内
			local nFrom = 21*60 + 1
			local nTo   = 21*60 + 20
			local minTime = GetMinOfDay()
		
			if minTime > nTo then
				BeginQuestEvent(sceneId)
				AddQuestLogCustomText( sceneId,
										"",							--标题
										"",      					--任务名字
										"#Y【国家】屠城战#W已经结束，很遗憾您错过了领奖时间，无法领取奖励。（领奖时间为屠城战活动当日21：00-21：20）",			--任务目标
										str,							--任务NPC
										"", 	     				--任务攻略
										"#Y【国家】屠城战#W已经结束，很遗憾您错过了领奖时间，无法领取奖励。（领奖时间为屠城战活动当日21：00-21：20）",				--任务描述
										""							--任务小提示
										)
				EndQuestEvent(sceneId)
				DispatchQuestLogUpdate(sceneId, selfId, x310155_g_MissionId)
				return		
			end
		end
	end
	
	
	--如果任务记录的没有结束，那么去向GLServer确认
	if nFinished == 0 then
		
		if CallScriptFunction(COUNTRY_BATTLE_LITE_SCRIPT,"IsNewFlow",sceneId,selfId) == 1 then
			
			--检查是否可以领奖
			if CallScriptFunction(COUNTRY_BATTLE_LITE_SCRIPT,"IsCanReciveBonus",sceneId,selfId) ~= 1 then
				BeginQuestEvent(sceneId)
				AddQuestLogCustomText( sceneId,
										"",							--标题
										"",      					--任务名字
										"#Y【国家】屠城战#W已经结束，很遗憾您错过了领奖时间，无法领取奖励。（领奖时间为屠城战活动当日21：00-21：20）",			--任务目标
										str,							--任务NPC
										"", 	     				--任务攻略
										"#Y【国家】屠城战#W已经结束，很遗憾您错过了领奖时间，无法领取奖励。（领奖时间为屠城战活动当日21：00-21：20）",				--任务描述
										""							--任务小提示
										)
				EndQuestEvent(sceneId)
				DispatchQuestLogUpdate(sceneId, selfId, x310155_g_MissionId)
				return
			else
				--如果已经结束，但是并没过期，则直接显示领奖相关
				BeginQuestEvent(sceneId)
				AddQuestLogCustomText( sceneId,
										"",							--标题
										"",      					--任务名字
										"#Y【国家】屠城战#W已经提前结束，请在10分钟内前往#R国家管理员#W处领取奖励。",			--任务目标
										str,							--任务NPC
										"", 	     				--任务攻略
										"#Y【国家】屠城战#W已经提前结束，请在10分钟内前往#R国家管理员#W处领取奖励。",				--任务描述
										""							--任务小提示
										)
				EndQuestEvent(sceneId)
				DispatchQuestLogUpdate(sceneId, selfId, x310155_g_MissionId)
				return 
			end
		end
		
		if CallScriptFunction(COUNTRY_BATTLE_LITE_SCRIPT,"GetCountryBattleLite_CountryCamp",sceneId,selfId) ~= -1 then
	
			--GetCountryQuestData(sceneId,selfId,CD_INDEX_COUNTRYBATTLELITE_FINISHED, x310155_g_ScriptId,-1,"ProcQuestLogRefresh_Finished")
			
			
			--主动刷新数据
			local nFinished = CallScriptFunction(COUNTRY_BATTLE_LITE_SCRIPT,"IsBattleFinished",sceneId,selfId)
			if nFinished == 1 then
				nFinished = 0
			elseif nFinished == 0 then
				nFinished = 1
			end
			x310155_ProcQuestLogRefresh_Finished( sceneId, selfId,nFinished,x310155_g_MissionId )
			
		else
			--如果已经结束，但是并没过期，则直接显示领奖相关
			BeginQuestEvent(sceneId)
			AddQuestLogCustomText( sceneId,
									"",							--标题
									"",      					--任务名字
									"#Y【国家】屠城战#W已经结束，请在本日21：00-21：20间在#R国家管理员#W处领取奖励。",			--任务目标
									str,							--任务NPC
									"", 	     				--任务攻略
									"#Y【国家】屠城战#W已经结束，请在本日21：00-21：20间在#R国家管理员#W处领取奖励。",				--任务描述
									""							--任务小提示
									)
			EndQuestEvent(sceneId)
			DispatchQuestLogUpdate(sceneId, selfId, x310155_g_MissionId)
		end
				
	else
		
		--如果已经结束，但是并没过期，则直接显示领奖相关
		BeginQuestEvent(sceneId)
		AddQuestLogCustomText( sceneId,
								"",							--标题
								"",      					--任务名字
								"#Y【国家】屠城战#W已经结束，请在本日20：00-21：20间在#R国家管理员#W处领取奖励。",			--任务目标
								str,							--任务NPC
								"", 	     				--任务攻略
								"#Y【国家】屠城战#W已经结束，请在本日20：00-21：20间在#R国家管理员#W处领取奖励。",				--任务描述
								""							--任务小提示
								)
		EndQuestEvent(sceneId)
		DispatchQuestLogUpdate(sceneId, selfId, x310155_g_MissionId)
		
	end
end

----------------------------------------------------------
--取得任务完成标记
----------------------------------------------------------
function x310155_ProcQuestLogRefresh_Finished( sceneId, selfId,MissionData,MissionId )

	local bHaveMission = IsHaveQuestNM(sceneId, selfId, x310155_g_MissionId );
	if bHaveMission <= 0 then
		return
	end

	local str = ""	
	local nCountryID = GetCurCountry( sceneId, selfId)
	if nCountryID == 0 then
		str ="@npc_123724"
	elseif nCountryID == 1 then
		str ="@npc_126021"
	elseif nCountryID == 2 then
		str ="@npc_129021"
	elseif nCountryID == 3 then
		str ="@npc_132021"
	end
	
	if MissionData ~= 1 then		
		local misIndex = GetQuestIndexByID( sceneId, selfId, x310155_g_MissionId )
		SetQuestParam( sceneId, selfId, misIndex, 3, 1 )
		--如果已经结束，但是并没过期，则直接显示领奖相关
		BeginQuestEvent(sceneId)
	    AddQuestLogCustomText( sceneId,
								"",							--标题
								"",      					--任务名字
								"\t【国家】屠城战已经结束，请在本日21：00-21：20间在本国#R国家管理员#W处领取奖励。",			--任务目标
								str,							--任务NPC
								"", 	     				--任务攻略
								"【国家】屠城战已经结束，请在本日21：00-21：20间在本国#R国家管理员#W处领取奖励。",				--任务描述
								""							--任务小提示
								)
		EndQuestEvent(sceneId)
		DispatchQuestLogUpdate(sceneId, selfId, x310155_g_MissionId)
		
	else
		
		local misIndex = GetQuestIndexByID( sceneId, selfId, x310155_g_MissionId )
		local nFinished = GetQuestParam( sceneId, selfId, misIndex, 3 )
		local nDay = GetQuestParam( sceneId, selfId, misIndex, 4 ) - 100
		local nCampFlag = GetQuestParam( sceneId, selfId, misIndex, 5 )
		local nMatchCountry = GetQuestParam( sceneId, selfId, misIndex, 6 )
		
		--取得敌对国家
		local strMatchCountry = nil
		if nMatchCountry == 0 then
			strMatchCountry = "楼兰"
		elseif nMatchCountry == 1 then
			strMatchCountry = "天山"
		elseif nMatchCountry == 2 then
			strMatchCountry = "昆仑"
		elseif nMatchCountry == 3 then
			strMatchCountry = "敦煌"
		end
		
		--任务目标，任务描述，任务攻略
		local strTarg,strDesc,strTips
		
		if nCampFlag == 0 then
			
			strTarg = format("\t您的国家今天处于#G防守方#W，您需要抵御#R%s王国#W的侵略者，保护本国的#G国家军力#W。",strMatchCountry)
			strDesc = "敌人可以通过边境拓道直接进入我国边境。他们还可以通过密道到达我国古道和外城来进行偷袭，必须提高警惕，防止敌人偷袭。国王在古道和外城#R王国召集#W处，可以选择#Y【屠城战】国王召集令#W按钮来对本国#G40级#W以上国民进行召唤，该功能在屠城战期间总共可以使用使用3次。"
			strTips = "#G参加屠城战后，您只能在#R中兴府及四国的王城，迷宫，古道和边境#G几个场景内活动，如果您前往#R其它场景#G您必须将任务放弃#G才可以进行传送 #G，并且不能再次参加屠城战活动。通过#R国王召集#G功能可以迅速集结人马，给入侵者迎头痛击。（尽可能的保卫本国王城内的国家军力，您会获得更多奖励）"
			
		else
			
			strTarg = format("\t您的国家今天处于进攻方，您需要进入#R%s王国#W摧毁他们的#G国家军力#W。",strMatchCountry)
			strDesc = "您可以通过边境边境拓道直接进入敌国边境。您也可以通过本国迷宫一层#R屠城战传送石#W进入敌国古道2个不同地点和外城。国王在#R屠城战传送石#W处，可以选择#Y【屠城战】国王召集令#W按钮来对本国#G40级#W以上国民进行召唤，该功能在屠城战期间总共可以使用使用3次。"
			strTips = "#G参加屠城战后，您只能在#R中兴府及四国的王城，迷宫，古道和边境#G几个场景内活动，如果您前往#R其它场景#G您必须将任务放弃#G才可以进行传送 #G，并且不能再次参加屠城战活动。敌国王城内有很多守卫，尽量避开它们，避免无谓的伤亡。您可以从#R本国迷宫屠城战传送石#G进入敌国王城打击敌人。（尽可能的保卫本国王城内的国家军力，您会获得更多奖励）"		
			
		end	
		
		--如果任务目标项为空，那么退出
		if strTarg == nil then
			return
		end
		BeginQuestEvent(sceneId)
	    AddQuestLogCustomText( sceneId,
								"",							--标题
								"",      					--任务名字
								strTarg,					--任务目标
								str,						--任务NPC
								"",		      				--任务攻略
								strDesc,					--任务描述
								strTips						--任务小提示
								)
		EndQuestEvent(sceneId)
		DispatchQuestLogUpdate(sceneId, selfId, x310155_g_MissionId);
		
	end
	
end

----------------------------------------------------------
--检查任务是否可接
----------------------------------------------------------
function x310155_IsMissionCanAccept( sceneId, selfId )
	local nDate   = GetQuestData(sceneId,selfId,MD_COUNTRYBATTLELITE_DATE[1], MD_COUNTRYBATTLELITE_DATE[2], MD_COUNTRYBATTLELITE_DATE[3] )
	local nCurDay = GetDayOfYear()
	if nCurDay == nDate then
		return 0
	end

	return 1
end

----------------------------------------------------------
--设置接任务日期
----------------------------------------------------------
function x310155_SetMissionAcceptDate( sceneId, selfId )
	local nCurDay = GetDayOfYear()
	SetQuestData(sceneId,selfId, MD_COUNTRYBATTLELITE_DATE[1], MD_COUNTRYBATTLELITE_DATE[2], MD_COUNTRYBATTLELITE_DATE[3], nCurDay )
	SetQuestData(sceneId,selfId, MD_COUNTRYBATTLELITE_RONGYU[1], MD_COUNTRYBATTLELITE_RONGYU[2], MD_COUNTRYBATTLELITE_RONGYU[3], 0 )
end