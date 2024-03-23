

--MisDescBegin
x310320_g_ScriptId = 310320
--x310320_g_MissionIdPre ={67,69,70,71}
x310320_g_MissionId = 9045 

x310320_g_MissionName="【个人】暴龙大作战"
x310320_g_MissionTarget				= "选择支持@npc_145001或@npc_145002" 
x310320_g_MissionCompleted			= "\t恩，本次暴龙大作战结束了，你会获得双倍的奖励吗？让我们拭目以待......"
x310320_g_MissionInfo				= "\t嘿，你好！我是这儿的暴龙管理员！\n\t想参加暴龙大作战吗？那你得先了解一下规则：\n\t你可以在暴红或者暴蓝中选择加入一方，在任务时间结束之前，你可以去找另一边的暴龙转换你支持的对象。\n\t最后，我会根据支持的人数来判断胜负。\n\t注意：#G支持人数#R较少#G的暴龙会获得#R胜利#G，获得双倍的奖励！而支持人数较多的暴龙，只会获得普通的奖励！#W任务结束时一定不要离线，否则要等到下次任务结束时才能完成本任务。"            --任务信息
x310320_g_ContinueInfo				= "\t别心急，过一会儿我就会宣布胜负！"  --任务继续信息
  --任务完成信息
x310320_g_MissionHelp				= "#G支持人数较少的暴龙会获得胜利，获得双倍的奖励！而支持人数较多的暴龙，只会获得普通的奖励！"          --任务提示信息
-- 任务放弃提示信息
x300320_g_strMissionAbandon         = "您放弃了任务：【个人】暴龙大作战"


--MisDescEnd
--**********************************
x310320_g_MissionTarget1				= "  选择支持@npc_145001或@npc_145002"       --任务目标
x310320_g_MissionCompleted1			= "\t恭喜你！由于你选择的暴龙支持人数较少，你在本次暴龙大作战中赢得了双倍的奖励！"
x310320_g_MissionCompleted2			= "\t很遗憾！由于你选择的暴龙支持人数太多，你在本次暴龙大作战中获得了普通的奖励！" 
x310320_g_HongNum	= 0
x310320_g_LanNum	= 0
x310320_g_MinLevel	= 65
x310320_g_MaxLevel	= 84

x310320_g_HongBuff		= 7536
x310320_g_LanBuff		= 7537


x310320_g_TotalTime	= 10 * 60  --10分钟

x310320_g_State		= 0

x310320_g_CostGold	= 1000 --1两现金
x310320_g_IsEnableId = 1039

-- 接受任务记录日志ID
x310320_g_AcceptMissionLogID        = 1631
-- 完成任务记录日志ID
x310320_g_FinishMissionLogID        = 1632

x310320_g_SelfId        = 0

-- 经验奖励系数  
x310320_g_CoffExp      =125000

--MD_HONGLAN_DATE		日期			9
--MD_HONGLAN_COUNT      次数			4


-- 玩家在天上人间·麒麟里退出游戏或掉线，再次进入游戏时的处理
function x310320_ProcMapPlayerNewConnectEnter( sceneId, selfId)
	local today = GetDayOfYear()
    local hour = GetHourMinSec()
    
	local lastDay = GetQuestData(sceneId, selfId, MD_YOULECHANG_DATE[1], MD_YOULECHANG_DATE[2], MD_YOULECHANG_DATE[3])
	if hour == 23 or hour < 9 or today ~= lastDay then
		-- 超过了上次进入的游乐场开放时间就把角色变身回去并放回大都南
		-- 做一个T人标记，在Buff里完成，直接T可能造成跨MapServer数据丢失
		CancelSpecificImpact( sceneId, selfId, x310320_g_LanBuff)
		CancelSpecificImpact( sceneId, selfId, x310320_g_HongBuff)
		--SetPlayerRuntimeData( sceneId, selfId, RD_DANCERY_BODYID, 1)
		SendSpecificImpactToUnit( sceneId, selfId, selfId, selfId, 8400, 0)
	end
end



function x310320_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
	x310320_g_SelfId        = selfId
	if IsHaveQuest(sceneId,selfId, x310320_g_MissionId) <= 0 then
		if GetLevel( sceneId, selfId) < x310320_g_MinLevel then 
	 		return 0
		end
	end	
	--local n = CostMoney(sceneId,selfId,2,1000)
	--print("x310320_ProcEnumEvent",n)
	--if GetGameOpenById( x310320_g_IsEnableId) <= 0  then
       --return 0
   -- end
    
    --if IsHaveQuest(sceneId,selfId, x310320_g_MissionId) <= 0 then
		local state = GetQuestStateNM(sceneId,selfId,NPCId,x310320_g_MissionId)
		AddQuestTextNM( sceneId, selfId, NPCId, x310320_g_MissionId, state, 0 )
	--end
	AddQuestNumText(sceneId,x310320_g_MissionId,"【暴龙大作战说明】" ,0,1)
	--AddQuestNumText(sceneId,x310320_g_MissionId,"领取奖励" ,3,2)
end
function x310320_ProcQuestAttach( sceneId, selfId, NPCId, npcGuid, misIndex, MissionId)
	--print("x310320_ProcQuestAttach")
end

function x310320_GetHongNum(sceneId ,selfId)
	return x310320_g_HongNum
end

function x310320_SetHongNumInc(sceneId ,selfId, inc)
	x310320_g_HongNum = x310320_g_HongNum + inc
	if x310320_g_HongNum <= 0 then
		x310320_g_HongNum = 0
	end
	return x310320_g_HongNum
end

function x310320_GetLanNum(sceneId ,selfId)
	--print("x310320_GetLanNum",x310320_g_LanNum)
	return x310320_g_LanNum
end

function x310320_SetLanNumInc(sceneId ,selfId, inc)
	x310320_g_LanNum = x310320_g_LanNum + inc
	if x310320_g_LanNum <= 0 then
		x310320_g_LanNum = 0
	end
	--print("x310320_SetLanNumInc",x310320_g_LanNum)
	return x310320_g_LanNum
end



function x310320_CheckTime(sceneId ,selfId, npcId)
	local hour,minute,sec =GetHourMinSec();
	if hour >= 12 and hour <= 22 and minute >= 0 and minute < 10 then
		return 1
	end
	return 0
end

function x310320_GetCountMD(sceneId ,selfId)
	local today = GetDayOfYear()
	local lastDay = GetQuestData(sceneId, selfId, MD_HONGLAN_DATE[1], MD_HONGLAN_DATE[2], MD_HONGLAN_DATE[3])
	if today == lastDay then
		local count = GetQuestData(sceneId, selfId, MD_HONGLAN_COUNT[1], MD_HONGLAN_COUNT[2], MD_HONGLAN_COUNT[3])
		return count
	else
		SetQuestData(sceneId,selfId,MD_HONGLAN_DATE[1],MD_HONGLAN_DATE[2],MD_HONGLAN_DATE[3], today)
       	SetQuestData(sceneId,selfId,MD_HONGLAN_COUNT[1],MD_HONGLAN_COUNT[2],MD_HONGLAN_COUNT[3], 0)    
		return 0
    end  
end

function x310320_IncCountMD(sceneId ,selfId)
	local today = GetDayOfYear()
	local lastDay = GetQuestData(sceneId, selfId, MD_HONGLAN_DATE[1], MD_HONGLAN_DATE[2], MD_HONGLAN_DATE[3])
	if today == lastDay then
		local count = GetQuestData(sceneId, selfId, MD_HONGLAN_COUNT[1], MD_HONGLAN_COUNT[2], MD_HONGLAN_COUNT[3])
		count = count + 1
		SetQuestData(sceneId,selfId,MD_HONGLAN_COUNT[1],MD_HONGLAN_COUNT[2],MD_HONGLAN_COUNT[3], count)
		return count
	else
		SetQuestData(sceneId,selfId,MD_HONGLAN_DATE[1],MD_HONGLAN_DATE[2],MD_HONGLAN_DATE[3], today)
       	SetQuestData(sceneId,selfId,MD_HONGLAN_COUNT[1],MD_HONGLAN_COUNT[2],MD_HONGLAN_COUNT[3], 1)    
       	return 1
    end  
end
function x310320_GetHonglanState(sceneId ,selfId)
	return x310320_g_State
end

function x310320_DecCountMD(sceneId ,selfId)
	local count = GetQuestData(sceneId, selfId, MD_HONGLAN_COUNT[1], MD_HONGLAN_COUNT[2], MD_HONGLAN_COUNT[3])
	count = count - 1
	if count <= 0 then
		count = 0
	end
	SetQuestData(sceneId,selfId,MD_HONGLAN_COUNT[1],MD_HONGLAN_COUNT[2],MD_HONGLAN_COUNT[3], count)
	return count
end

function x310320_IsWinner(sceneId ,selfId )	--是否赢方
	if x310320_g_HongNum > x310320_g_LanNum then
		if IsHaveSpecificImpact( sceneId, selfId, x310320_g_LanBuff) == 1 then
			return 1
		else
			return 0
		end
	elseif x310320_g_HongNum < x310320_g_LanNum then
		if IsHaveSpecificImpact( sceneId, selfId, x310320_g_HongBuff) == 1 then
			return 1
		else
			return 0
		end
	else
		return 0
	end
	
end


---------------------------------------------------------------------------------------------------
--检查任务是否可提交
---------------------------------------------------------------------------------------------------
function x310320_CheckSubmit( sceneId, selfId, NPCId)
	local misIndex = GetQuestIndexByID( sceneId, selfId, x310320_g_MissionId)

    if GetQuestParam( sceneId, selfId, misIndex, 0) == 1 and GetQuestParam( sceneId, selfId, misIndex, 7) == 1 then
        return 1
    else
        return 0
    end
end


function x310320_ProcEventEntry(sceneId ,selfId, NPCId,idScript,idExt )	--点击该任务后执行此脚本
	local level = GetLevel( sceneId, selfId)
	local exp   = level * x310320_g_CoffExp
	--print("x310320_ProcEventEntry")
	if idExt == 0 then
		if IsQuestHaveDone(sceneId, selfId, x310320_g_MissionId) > 0 then
			BeginQuestEvent(sceneId)
        	AddQuestText(sceneId,"你所参与的暴龙大作战已经结束，快去找暴龙大作战任务发布人提交任务吧！")
        	EndQuestEvent(sceneId)
        	DispatchQuestEventList(sceneId,selfId,NPCId)
			return
		end
		
		if IsHaveQuest(sceneId,selfId, x310320_g_MissionId) > 0 then
			local bDone = x310320_CheckSubmit( sceneId, selfId, NPCId)
            if bDone > 0 then
                x310320_DispatchCompletedInfo( sceneId, selfId, NPCId) --完成任务显示
            else
                x310320_DispatchContinueInfo( sceneId, selfId, NPCId) --未完成任务显示
            end
            
            
--			BeginQuestEvent(sceneId)
--        	AddQuestText(sceneId,"你已有此任务")
--        	EndQuestEvent(sceneId)
--        	DispatchQuestEventList(sceneId,selfId,NPCId)
			return
		end
		
		
		
		
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"#Y"..x310320_g_MissionName)
        AddQuestText(sceneId,x310320_g_MissionInfo)
        AddQuestText( sceneId,"#Y任务目标:")
        AddQuestText( sceneId,x310320_g_MissionTarget)
        --AddQuestItemBonus(sceneId,10011001,1)
        AddQuestExpBonus(sceneId, exp )
        --6、可选物品
		--AddQuestRadioItemBonus(sceneId, item.item, item.n)
        --AddQuestText(sceneId,format("经验值：%d",10000))
        EndQuestEvent(sceneId)
        --DispatchQuestEventList(sceneId,selfId,NPCId)
        DispatchQuestInfoNM(sceneId, selfId, NPCId, x310320_g_ScriptId, x310320_g_MissionId)
        

	elseif idExt == 1 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"#Y【暴龙大作战任务说明】")
        AddQuestText(sceneId,"#Y接取任务：\n\t#W65级以上的玩家，每周六、日12：00-晚上22：00每逢整点可以接取任务，每次开放#Y10分钟#W，共开启10次任务。\n\t每个玩家每天最多可以接取三次任务。第一次接取任务免费，其后的两次均要花费#R1两现金/金卡#W。")
        AddQuestText(sceneId,"#Y玩法过程：\n\t#W接取任务后，你需要先在暴红或暴蓝两只暴龙中选择支持一方，在任务时间结束之前（整点开放后10分钟内），可以随时找另一只暴龙转换你的支持对象。\n\t在任务时间结束后，#G支持人数#R较少#G的暴龙会获得胜利，获得#R双倍的奖励#G！而支持人数#R较多#G的暴龙，只会获得普通的奖励！")
        EndQuestEvent(sceneId)
        DispatchQuestEventList(sceneId,selfId,NPCId)
    elseif idExt == 2 then
    	if x310320_CheckSubmit( sceneId, selfId, NPCId) ~= 1 then
    		BeginQuestEvent(sceneId)
	        AddQuestText(sceneId,"任务未结束")
	        EndQuestEvent(sceneId)
	        DispatchQuestEventList(sceneId,selfId,NPCId)
    		return
    	end
    	if x310320_IsWinner(sceneId ,selfId ) == 1 then
    		BeginQuestEvent(sceneId)
	        AddQuestText(sceneId,"赢方")
	        EndQuestEvent(sceneId)
	        DispatchQuestEventList(sceneId,selfId,NPCId)
    	else
	    	BeginQuestEvent(sceneId)
	        AddQuestText(sceneId,"输方")
	        EndQuestEvent(sceneId)
	        DispatchQuestEventList(sceneId,selfId,NPCId)
    	end
	end
	

end


---------------------------------------------------------------------------------------------------
--向客户端发送任务未完成
---------------------------------------------------------------------------------------------------
function x310320_DispatchContinueInfo( sceneId, selfId, NPCId)
	BeginQuestEvent( sceneId)
    AddQuestText( sceneId, "#Y"..x310320_g_MissionName)
    AddQuestText( sceneId, x310320_g_ContinueInfo)
    AddQuestText( sceneId, " ")
 
    DispatchQuestEventList( sceneId, selfId, NPCId)
	
end

---------------------------------------------------------------------------------------------------
--向客户端发送任务完成信息
---------------------------------------------------------------------------------------------------
function x310320_DispatchCompletedInfo( sceneId, selfId, NPCId)
	BeginQuestEvent( sceneId)
    AddQuestText( sceneId, "#Y"..x310320_g_MissionName)
    AddQuestText( sceneId, x310320_g_MissionCompleted)
    AddQuestText( sceneId, " ")
    local level = GetLevel( sceneId, selfId)
    
	EndQuestEvent( sceneId)
    DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x310320_g_ScriptId, x310320_g_MissionId)
end

function x310320_DispatchMissionInfo( sceneId, selfId, NPCId)
	
	BeginQuestEvent( sceneId)

    --任务信息
    AddQuestText( sceneId, "#Y"..x310320_g_MissionName)
    AddQuestText( sceneId, x310320_g_MissionInfo)
    AddQuestText( sceneId, " ")
           
    --任务目标
    AddQuestText( sceneId, "#Y任务目标：")
    AddQuestText( sceneId, x310320_g_MissionTarget)
    AddQuestText( sceneId, " ")

    --提示信息
    if x310320_g_MissionHelp ~= "" then
        AddQuestText( sceneId, "#Y任务提示：")
        AddQuestText( sceneId, x310320_g_MissionHelp)
        AddQuestText( sceneId, " ")
    end                 

	EndQuestEvent()
	DispatchQuestInfoNM( sceneId, selfId, NPCId, x310320_g_ScriptId, x310320_g_MissionId)
end

function x310320_OnTimerDoingStart( sceneId, TimerId, Param1, Param2, Param3, Param4, Param5)
	--print("x310320_OnTimerDoingStart")
    SetSystemTimerTick( sceneId, 310320, "OnTimer", TimerId, 10000)
    LuaAllScenceM2Wrold (sceneId, "新一轮暴龙大作战开始了！各位玩家可以通过大都南的#G天上人间传送人（128，70）#R进入天上人间·麒麟，找到#G暴龙大作战发布人（70，59）#R参加！", 1, 1)
    
end

function x310320_OnMissionFinish( sceneId )
		
	local nHumanCount = GetScenePlayerCount( sceneId)
    if nHumanCount > 0 then
        for i = 0, nHumanCount do
            local objId = GetScenePlayerObjId( sceneId,i)
            if objId >= 0 then
            	if IsHaveQuest(sceneId,objId, x310320_g_MissionId) > 0 then
	                CancelSpecificImpact( sceneId, objId, x310320_g_LanBuff)
	                CancelSpecificImpact( sceneId, objId, x310320_g_HongBuff)
                local misIndex = GetQuestIndexByID( sceneId, objId, x310320_g_MissionId)               
                if x310320_IsWinner(sceneId,objId) == 1 then   --6标识为输或赢方
                	SetQuestByIndex( sceneId, objId, misIndex, 6, 1)
                else
                	SetQuestByIndex( sceneId, objId, misIndex, 6, 0)                	
                end
                if x310320_g_HongNum > x310320_g_LanNum then
                	Msg2Player( sceneId, objId, format("本轮暴龙大作战已经结束，#G暴红与暴蓝#R的支持人数比是#G%d比%d#R。",x310320_g_HongNum,x310320_g_LanNum), 0, 1)
        					Msg2Player( sceneId, objId, format("本轮暴龙大作战已经结束，暴红与暴蓝的支持人数比是#G%d比%d#cffcf00。",x310320_g_HongNum,x310320_g_LanNum), 0, 2)
        					Msg2Player( sceneId, objId, format("所有#G暴蓝#R的支持者可以获得双倍的奖励！",x310320_g_HongNum,x310320_g_LanNum), 0, 1)
        					Msg2Player( sceneId, objId, format("所有#G暴蓝#cffcf00的支持者可以获得双倍的奖励！",x310320_g_HongNum,x310320_g_LanNum), 0, 2)
                elseif  x310320_g_LanNum > x310320_g_HongNum then
                	Msg2Player( sceneId, objId, format("本轮暴龙大作战已经结束，#G暴红与暴蓝#R的支持人数比是#G%d比%d#R。",x310320_g_HongNum,x310320_g_LanNum), 0, 1)
        					Msg2Player( sceneId, objId, format("本轮暴龙大作战已经结束，暴红与暴蓝的支持人数比是#G%d比%d#cffcf00。",x310320_g_HongNum,x310320_g_LanNum), 0, 2)
        					Msg2Player( sceneId, objId, format("所有#G暴红#R的支持者可以获得双倍的奖励！",x310320_g_HongNum,x310320_g_LanNum), 0, 1)
        					Msg2Player( sceneId, objId, format("所有#G暴红#cffcf00的支持者可以获得双倍的奖励！",x310320_g_HongNum,x310320_g_LanNum), 0, 2)
        				else
        					Msg2Player( sceneId, objId, format("本轮暴龙大作战已经结束，#G暴红与暴蓝#R的支持人数比是#G%d比%d#R。",x310320_g_HongNum,x310320_g_LanNum), 0, 1)
        					Msg2Player( sceneId, objId, format("本轮暴龙大作战已经结束，暴红与暴蓝的支持人数比是#G%d比%d#cffcf00。",x310320_g_HongNum,x310320_g_LanNum), 0, 2)
        					Msg2Player( sceneId, objId, format("双方支持者都只能获得普通的奖励！",x310320_g_HongNum,x310320_g_LanNum), 0, 1)
        					Msg2Player( sceneId, objId, format("双方支持者都只能获得普通的奖励！",x310320_g_HongNum,x310320_g_LanNum), 0, 2)
        				end	
                SetQuestByIndex( sceneId, objId, misIndex, 0, 1)
        		SetQuestByIndex( sceneId, objId, misIndex, 7, 1)
        		
        		--Msg2Player(sceneId, objId, "任务已完成", 0, 3)
	        	end
            end
        end
    end
    
    if x310320_g_HongNum > x310320_g_LanNum then
       LuaThisScenceM2Wrold( sceneId, format("暴蓝获胜！",x310320_g_HongNum,x310320_g_LanNum), 5, 1)
    elseif  x310320_g_LanNum > x310320_g_HongNum then
      LuaThisScenceM2Wrold( sceneId, format("暴红获胜！",x310320_g_HongNum,x310320_g_LanNum), 5, 1)
    else
      LuaThisScenceM2Wrold( sceneId, format("暴蓝暴红未分胜负！",x310320_g_HongNum,x310320_g_LanNum), 5, 1)
    end	
    
  x310320_g_HongNum	= 0
	x310320_g_LanNum	= 0
end

function x310320_OnTimer( sceneId, TimerId, uTime)
	--print("x310320_OnTimer", uTime,x310320_g_State)
	local hour,minute,sec =GetHourMinSec();
	if hour >= 12 and hour <= 22 and minute >= 0 and minute <= 10 then
		x310320_g_State = 1
	else
		x310320_g_State = 0
	end
	
	local msg = format("start timer minute =%d sec =%d",minute,sec)
	--Msg2Player(sceneId, x310320_g_SelfId, msg, 0, 2)
	local nHumanCount = GetScenePlayerCount( sceneId)
    if nHumanCount > 0 then
        for i = 0, nHumanCount do
            local objId = GetScenePlayerObjId( sceneId,i)
            if objId >= 0 then
               --Msg2Player(sceneId, objId, msg , 0, 3)
            end
        end
    end
    
	--print("hour",hour)
	--print("minute",minute)
	if hour >= 12 and hour <= 22 and minute == 10 then
		--if x310320_g_State == 1 then
		--	print("x310320_OnMissionFinish")
			
			--print("------------------2")
			x310320_OnMissionFinish( sceneId )
			x310320_g_State = 0
			return
		--end
	end
	
	SetSystemTimerTick( sceneId, 310320, "OnTimer", TimerId, 1000)
end

function x310320_ProcQuestLogRefresh( sceneId, selfId, MissionId)
	local level =GetLevel(sceneId, selfId)
	local exp   =level *x310320_g_CoffExp
	BeginQuestEvent( sceneId)
	AddQuestLogCustomText( sceneId,
                                   x310320_g_MissionName,               -- 标题
                                   x310320_g_MissionName,               -- 任务名字
                                   x310320_g_MissionTarget1,                   				 -- 任务目标
                                   "@npc_145000",              -- 任务NPC
                                   "任务攻略",               -- 任务攻略
                                   x310320_g_MissionInfo,    -- 任务描述
                                   "") 
                                                -- 任务提示
                                                
    AddQuestExpBonus( sceneId, exp)
    --AddQuestItemBonus(sceneId,10018001,1)
    --AddQuestMoneyBonus1( sceneId, money)                                            
    EndQuestEvent()
	DispatchQuestLogUpdate( sceneId, selfId, MissionId)
end


function x310320_ProcAcceptCheck(sceneId, selfId, NPCId)
	return 1
end


-------------------------------------------------------------------------------
--检查状态是否正常
-------------------------------------------------------------------------------
function x310320_CheckPlayerState( sceneId,selfId )
    

    local state
    local ErrorMsg

    state = IsPlayerStateNormal(sceneId,selfId )
    if state == 0 then
        ErrorMsg = "状态异常"
        return 1,ErrorMsg
    end

    state = IsPlayerMutexState(sceneId,selfId,PLAYER_STATE_MENTALGAME )
    if state == 1 then
        ErrorMsg = "处于答题状态，不能接受任务"
        return 1,ErrorMsg
    end

    state = IsPlayerMutexState(sceneId,selfId,PLAYER_STATE_STALL )
    if state == 1 then
        ErrorMsg = "处于摆摊状态，不能接受任务"
        return 1,ErrorMsg
    end

    state = IsPlayerMutexState(sceneId,selfId,PLAYER_STATE_DIE )
    if state == 1 then
        ErrorMsg = "处于死亡状态，不能接受任务"
        return 1,ErrorMsg
    end

    state = IsPlayerMutexState(sceneId,selfId,PLAYER_STATE_CRASHBOX )
    if state == 1 then
        ErrorMsg = "处于运镖状态，不能接受任务"
        return 1,ErrorMsg
    end

    state = IsPlayerMutexState(sceneId,selfId,PLAYER_STATE_AUTOPLAY )
    if state == 1 then
        ErrorMsg = "处于挂机状态，不能接受任务"
        return 1,ErrorMsg
    end

    state = IsPlayerMutexState(sceneId,selfId,PLAYER_STATE_SUBTRAIN )
    if state == 1 then
        ErrorMsg = "处于代练状态，不能接受任务"
        return 1,ErrorMsg
    end

    state = IsPlayerMutexState(sceneId,selfId,PLAYER_STATE_BUS )
    if state == 1 then
        ErrorMsg = "处于BUS状态，不能接受任务"
        return 1,ErrorMsg
    end

--    state = IsPlayerMutexState(sceneId,selfId,PLAYER_STATE_PKMODE )
--    if state == 1 then
--        ErrorMsg = "PK值过高或处于狂暴模式，不能接受任务"
--        return 1,ErrorMsg
--    end

    return 0

end


function x310320_ProcQuestAccept( sceneId, selfId, NPCId, MissionId )
	local misIndex = GetQuestIndexByID( sceneId, selfId, x310320_g_MissionId)
   	SetQuestByIndex( sceneId, selfId, misIndex, 0, 1)
    SetQuestByIndex( sceneId, selfId, misIndex, 7, 1)
        		
        		
	--print("x310320_ProcQuestAccept")
	if IsQuestHaveDone(sceneId, selfId, x310320_g_MissionId) > 0 then
		BeginQuestEvent(sceneId)
        AddQuestText(sceneId,"\t你已经接受【个人】暴龙大作战任务了。")
        EndQuestEvent(sceneId)
        DispatchQuestEventList(sceneId,selfId,NPCId)
        return 
    end

	local state,msg = x310320_CheckPlayerState( sceneId,selfId )
    if state == 1 then
       	BeginQuestEvent(sceneId)
    	AddQuestText( sceneId, msg );
    	EndQuestEvent(sceneId)
    	DispatchQuestTips(sceneId,selfId)
    	return
    end	

	
    
    local level = GetLevel(sceneId, selfId)
	if GetLevel( sceneId, selfId) > x310320_g_MaxLevel then
    	Msg2Player(sceneId, selfId, "只有低于85级的玩家才能接受本任务", 0, 2)
   		Msg2Player(sceneId, selfId, "只有低于85级的玩家才能接受本任务", 0, 3)   
		return
	end
		
		
    if IsQuestFullNM(sceneId,selfId)==1 then
 				Msg2Player(sceneId, selfId, "任务已满，添加任务失败", 0, 2)
   			Msg2Player(sceneId, selfId, "任务已满，添加任务失败", 0, 3)  
        return 
    end
	local level = GetLevel(sceneId, selfId)
	if GetLevel( sceneId, selfId) < x310320_g_MinLevel or GetLevel( sceneId, selfId) > x310320_g_MaxLevel then
 				Msg2Player(sceneId, selfId, "只有低于85级的玩家才能接受任务", 0, 2)
   			Msg2Player(sceneId, selfId, "只不低于85级的玩家才能接受任务", 0, 3)      	
		return
	end
	
	local weekDay = GetWeek()
	if weekDay ~= 0 and weekDay ~= 6 then
 				Msg2Player(sceneId, selfId, "很抱歉，【个人】暴龙大作战在每周六、日开放", 0, 2)
   			Msg2Player(sceneId, selfId, "很抱歉，【个人】暴龙大作战在每周六、日开放", 0, 3)   	
		return --TEST
	end
	if x310320_CheckTime(sceneId ,selfId, npcId) < 1 then
 				Msg2Player(sceneId, selfId, "很抱歉，【个人】暴龙大作战在中午12：00-晚上22：00之间，每逢整点开放", 0, 2)
   			Msg2Player(sceneId, selfId, "很抱歉，【个人】暴龙大作战在中午12：00-晚上22：00之间，每逢整点开放", 0, 3)     	
		return --TEST
	end
	
	local count = x310320_GetCountMD(sceneId ,selfId)
	if count >= 3 then
 				Msg2Player(sceneId, selfId, "你今天已经做了3次【个人】暴龙大作战了，请改天再来", 0, 2)
   			Msg2Player(sceneId, selfId, "你今天已经做了3次【个人】暴龙大作战了，请改天再来", 0, 3)
		return
	end
		
	if count >= 1 then  --不是第一次则要扣钱
		if CostMoney(sceneId,selfId,3,x310320_g_CostGold) ~= -1 then
			Msg2Player(sceneId, selfId, "领取任务成功，扣除1两金卡！", 0, 3)
			Msg2Player(sceneId, selfId, "领取任务成功，扣除1两金卡！", 0, 2)
			Msg2Player(sceneId, selfId, "扣除1两金币！", 0, 2)
		else
			if CostMoney(sceneId,selfId,2,x310320_g_CostGold,324) ~= -1 then
				Msg2Player(sceneId, selfId, "领取任务成功，扣除1两现金！", 0, 3)
				Msg2Player(sceneId, selfId, "领取任务成功，扣除1两现金！", 0, 2)
				Msg2Player(sceneId, selfId, "扣除1两金币！", 0, 2)
			else
				BeginQuestEvent(sceneId)
	    	Msg2Player(sceneId, selfId, "很遗憾，你的现金/金卡不足1两", 0, 3)
				Msg2Player(sceneId, selfId, "很遗憾，你的现金/金卡不足1两", 0, 2)
	    		return
			end
		end
	end
	
	local retmiss = AddQuest( sceneId, selfId, x310320_g_MissionId, x310320_g_ScriptId, 0, 0, 0, 1)
   	if retmiss ==0 then
       Msg2Player(sceneId, selfId, "接受任务失败！", 0, 3)
       return 0
   	end
   	
	
   	x310320_IncCountMD(sceneId ,selfId)  
   	local hour,minute,sec =GetHourMinSec()   	
    BeginQuestEvent(sceneId)
   	AddQuestText(sceneId,"\t你成功的接受了【个人】暴龙大作战！你可以去选择支持暴蓝或者暴红这两头暴龙之一，它们就在我的两边。\n\t我要再次提醒你：#G支持人数较少的暴龙会获得胜利！#W本次任务于#Y"..hour.."点10分".."#W结束，请掌控好你的时间。")
   	EndQuestEvent(sceneId)
   	DispatchQuestEventList(sceneId,selfId,NPCId)
	
	x310320_ProcQuestLogRefresh( sceneId, selfId, x310320_g_MissionId)
	
	-- 写日志
    GamePlayScriptLog( sceneId, selfId, x310320_g_AcceptMissionLogID)
end

function x310320_ProcQuestAbandon(sceneId, selfId, MissionId)
    if IsHaveQuest(sceneId,selfId, x310320_g_MissionId) <= 0 then
        return 
    end
    
    DelQuest( sceneId, selfId, x310320_g_MissionId)
    Msg2Player(sceneId, selfId, format("您放弃了任务:%s",x310320_g_MissionName), 0, 2)
    Msg2Player(sceneId, selfId, format("您放弃了任务:%s",x310320_g_MissionName), 0, 3) 
     
   	--x310320_DecCountMD(sceneId ,selfId)   --放弃也计次
    
   	if IsHaveSpecificImpact( sceneId, selfId, x310320_g_HongBuff ) == 1 then
   		CancelSpecificImpact( sceneId, selfId, x310320_g_HongBuff)
		x310320_g_HongNum	= x310320_g_HongNum	- 1
	elseif IsHaveSpecificImpact( sceneId, selfId, x310320_g_LanBuff) == 1 then
		CancelSpecificImpact( sceneId, selfId, x310320_g_LanBuff)
		x310320_g_LanNum	= x310320_g_LanNum - 1
	end   		
end




function x310320_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)
	local level =GetLevel( sceneId, selfId)
	local exp 	=x310320_g_CoffExp * level
	if IsHaveQuest(sceneId,selfId, x310320_g_MissionId) <= 0 then
        BeginQuestEvent(sceneId)
        AddQuestText(sceneId,"您没有这个任务！")
        EndQuestEvent(sceneId)
        DispatchQuestTips(sceneId,selfId)
        return 0
	else
		local misIndex = GetQuestIndexByID( sceneId, selfId, x310320_g_MissionId)
   		local IsWin = GetQuestParam( sceneId, selfId, misIndex, 6)
		if DelQuest(sceneId, selfId, x310320_g_MissionId) > 0 then
			if IsWin == 1 then
				exp =exp*2
    		BeginQuestEvent(sceneId)
	        AddQuestText(sceneId,x310320_g_MissionCompleted1)
	        EndQuestEvent(sceneId)
	        DispatchQuestEventList(sceneId,selfId,NPCId)
	        AddExp(sceneId, selfId, exp)
	      EndQuestEvent()
    	else
	    	BeginQuestEvent(sceneId)
	        AddQuestText(sceneId,x310320_g_MissionCompleted2)
	        EndQuestEvent(sceneId)
	        DispatchQuestEventList(sceneId,selfId,NPCId)
	        AddExp(sceneId, selfId, exp)
	      EndQuestEvent()  
    	end
    	Msg2Player( sceneId, selfId, format( "获得#R经验%d点#cffcf00的奖励", exp).."。", 8, 2)
			Msg2Player( sceneId, selfId, format( "获得#R经验%d点#cffcf00的奖励", exp), 8, 3)
       end
	
       -- AddItemListToPlayer(sceneId,selfId)
   end
   
   GamePlayScriptLog( sceneId, selfId, x310320_g_FinishMissionLogID)
   --CallScriptFunction( MISSION_SCRIPT, "ProcEventEntry", sceneId, selfId, NPCId, x310320_g_MissionIdNext )	
end

 