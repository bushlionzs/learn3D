x310151_g_scriptId                      = 310151
x310151_g_MissionId						= 7559
x310151_g_TickBuf						= 8727
x310151_g_BufID 						= {8719,8720,8721,8722,8723,8724,8725,8726,8727}--玩家BUFID,当玩家接受屠城战时,将从此表获取BUFID,此表按顺序为:楼兰,莱茵,昆仑,敦煌
----------------------------------------------------------------------------------------------
--检查有效性
----------------------------------------------------------------------------------------------
function x310151_CheckValid( sceneId, selfId  )
    
    --检查是否是周日
    local nWeek = GetWeek()
    if nWeek ~= 6 then
       return 0
    end
    if IsPlayerStateNormal(sceneId,selfId ) ~= 1 then
		return 0
	end
    
    --检查是否走新流程
    if CallScriptFunction(COUNTRY_BATTLE_LITE_SCRIPT,"IsNewFlow",sceneId,selfId) == 1 then
    	
    	--检查是否可以领奖
    	if CallScriptFunction(COUNTRY_BATTLE_LITE_SCRIPT,"IsCanReciveBonus",sceneId,selfId) ~= 1 then
    		return 0
    	end
    	
    	--可以邻奖
    	return 1
    end
    
    --检查是否是小国战发生时间
    local today = GetDayOfYear()
    local mdtoday = x310151_GetMissionDay( sceneId,selfId)
    if today ~= mdtoday then
        return -1
    end
    
    local minTime = GetMinOfDay()
    
    --在不在时间段内
    local nFrom = 21*60 + 1
    local nTo   = 21*60 + 20

    if minTime < nFrom then
        return -2
    end
    
    if minTime > nTo then
        return -3
    end
    
    return 1
end


----------------------------------------------------------------------------------------------
--枚举
----------------------------------------------------------------------------------------------
function x310151_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

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

    if x310151_CheckValid( sceneId, selfId  ) <= 0 then
        return
    end
    
    AddQuestNumText(sceneId,x310151_g_scriptId,"【国战】奖励领取",3);
end

----------------------------------------------------------------------------------------------
--脚本默认事件
----------------------------------------------------------------------------------------------
function x310151_ProcEventEntry( sceneId ,selfId, npcId,idScript,idExt )

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

    if x310151_CheckValid( sceneId, selfId  ) <= 0 then
        return
    end
    
    --设置当前NPC
    SetPlayerRuntimeData(sceneId,selfId,RD_COMMON_NPCID,npcId)
    
    --守方的话，需要请求GLServer，给奖励
    GetCountryQuestData(sceneId,selfId,CD_INDEX_COUNTRYBATTLELITE_KILLCOUNT,x310151_g_scriptId,-1,"OnGiveBonus")
    
end


----------------------------------------------------------
--删除BUF
----------------------------------------------------------
function x310151_CancelBufId( sceneId,selfId )

		for i,item in x310151_g_BufID do
		if IsHaveSpecificImpact(sceneId,selfId,item) == 1 then
			CancelSpecificImpact(sceneId,selfId,item)
		end
	end

end

----------------------------------------------------------------------------------------------
--给奖励
----------------------------------------------------------------------------------------------
function x310151_OnGiveBonus( sceneId,selfId ,nKillCout,missionId )

    if x310151_CheckValid( sceneId, selfId  ) <= 0 then
        return
    end
    
    if nKillCout < 0 then
        return
    end
    
    local npcId = GetPlayerRuntimeData(sceneId,selfId,RD_COMMON_NPCID)
    
    local nCampFlag = -1
    if IsHaveQuest(sceneId,selfId, x310151_g_MissionId) > 0 then
    	
    	local misIndex = GetQuestIndexByID( sceneId, selfId, x310151_g_MissionId )
    	nCampFlag = GetQuestParam( sceneId,selfId,misIndex,5) 

    	if DelQuest( sceneId,selfId,x310151_g_MissionId) <=0 then
    		BeginQuestEvent(sceneId)
			AddQuestText(sceneId, "任务删除失败！请重试！");
			EndQuestEvent(sceneId)
			DispatchQuestEventList(sceneId,selfId,npcId)
			return    		
    	else
    		BeginQuestEvent(sceneId)
			AddQuestText(sceneId, "您完成了【国家】屠城战！");
			EndQuestEvent(sceneId)
			DispatchQuestEventList(sceneId,selfId,npcId)	
			x310151_CancelBufId( sceneId,selfId )
    	end
    else
    	--如果没有任务,则不能领取奖励
    	return
    end

    
    GamePlayScriptLog( sceneId, selfId, 1512)
    
    local level = GetLevel( sceneId,selfId)
    
    --处理经验值加成    
    local nExpExt = 0
    local n1 = -1
    local n2 = -1
    local n3 = -1
    local nKillCountBak = nKillCout
    
    if nCampFlag == 0  then

    	
    	--防守方的计算
    	n1=5
    	n2=4
    	n3=1

    	while nKillCout >= 10000 do
    		nKillCout = nKillCout - 10000
    		n1 = n1 - 1
    	end

    	while nKillCout >= 1000 do
    		nKillCout = nKillCout - 1000
    		n2 = n2 - 1
    	end

    	while nKillCout >= 100 do
    		nKillCout = nKillCout - 100
    		n3 = n3 - 1
    	end

	elseif nCampFlag == 1 then

		
		--进攻方的计算
		n1 = 0
    	n2 = 0
    	n3 = 0
    	
    	while nKillCout >= 10000 do
    		nKillCout = nKillCout - 10000
    		n1 = n1 + 1
    	end
    	
    	while nKillCout >= 1000 do
    		nKillCout = nKillCout - 1000
    		n2 = n2 + 1
    	end
    	
    	while nKillCout >= 100 do
    		nKillCout = nKillCout - 100
    		n3 = n3 + 1
    	end
	end
	
	
	if n1 > 0 then
    	nExpExt = nExpExt + level * 12178 * n1
    end
    
    if n2 > 0 then
    	nExpExt = nExpExt + level * 12178 * n2
    end
    
    if n3 > 0 then
    	nExpExt = nExpExt + level * 12178 * n3
    end
        
    --计算奖励    
    local exp  = level * 28800
    local rong = nKillCout * 60
	
    if nKillCout == 0 then
        
        --给基本奖励，如果打怪数为0或是守护怪数为0，则给基本奖励
        exp = level * 28800
        rong = 30
        		
    end
    
    exp = exp + (nExpExt*2)
    
    --给经验奖励
    if exp > 0 then
        AddExp( sceneId,selfId,exp )
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "恭喜您获得#R经验"..exp.."点#o的奖励");
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)	
		Msg2Player(sceneId,selfId,format("恭喜您获得#R经验"..exp.."点#o的奖励"),8,2)
    end
    
    
    --给荣誉
    if rong > 0 then
        AddHonor( sceneId,selfId,rong )
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "恭喜您获得#R荣誉"..rong.."点#o的奖励");
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)	
		Msg2Player(sceneId,selfId,format("恭喜您获得#R荣誉"..rong.."点#o的奖励"),8,2)
    end 

    

    --再记日志    
    local name = GetName(sceneId,selfId)
    if name == nil then
        name = "ErrorName"
    end
    
    local nCountry  = GetCurCountry( sceneId,selfId)
    local strMsg = format("CBL:<Info>x310151_OnGiveBonus sceneId=%d, name=%s,level=%d,country=%d,killcount=%d exp=%d, rong=%d n1=%d,n2=%d,n3=%d,nKillCout=%d nCampFlag=%d ", 
    					  sceneId, name,level,nCountry,nKillCout, exp, rong,n1,n2,n3,nKillCountBak,nCampFlag )
    WriteLog( 1, strMsg )
end

----------------------------------------------------------------------------------------------
--接受
----------------------------------------------------------------------------------------------
function x310151_ProcAcceptCheck( sceneId, selfId, NPCId )
    return 1
end

----------------------------------------------------------------------------------------------
--接受
----------------------------------------------------------------------------------------------
function x310151_ProcAccept( sceneId, selfId )
end

----------------------------------------------------------------------------------------------
--放弃
----------------------------------------------------------------------------------------------
function x310151_ProcQuestAbandon( sceneId, selfId, MissionId )
end

----------------------------------------------------------------------------------------------
--继续
----------------------------------------------------------------------------------------------
function x310151_OnContinue( sceneId, selfId, targetId )
end

----------------------------------------------------------------------------------------------
--检测是否可以提交
----------------------------------------------------------------------------------------------
function x310151_CheckSubmit( sceneId, selfId )
end

----------------------------------------------------------------------------------------------
--提交
----------------------------------------------------------------------------------------------
function x310151_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end

----------------------------------------------------------------------------------------------
--杀死怪物或玩家
----------------------------------------------------------------------------------------------
function x310151_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end

----------------------------------------------------------------------------------------------
--进入区域事件
----------------------------------------------------------------------------------------------
function x310151_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

----------------------------------------------------------------------------------------------
--道具改变
----------------------------------------------------------------------------------------------
function x310151_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end

----------------------------------------------------------------------------------------------
--取得任务天数
----------------------------------------------------------------------------------------------
function x310151_GetMissionDay( sceneId,selfId)
	
	--是否有此任务
	if IsHaveQuest(sceneId,selfId, x310151_g_MissionId) <= 0 then
		return -100 
	end
	
	local misIndex = GetQuestIndexByID( sceneId, selfId, 7559)
	if misIndex < 0 then
		return -100
	end
	
	return GetQuestParam( sceneId,selfId,misIndex,4) -100		
end