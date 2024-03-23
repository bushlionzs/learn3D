x310160_g_scriptId 		= 310160

--灯谜信息
x310160_g_DengmiInfo	= {
							{npcID=-1,GUID = 141506,nDengmi=-1},
							{npcID=-1,GUID = 141507,nDengmi=-1},
							{npcID=-1,GUID = 141508,nDengmi=-1},
							{npcID=-1,GUID = 141509,nDengmi=-1},
							{npcID=-1,GUID = 141510,nDengmi=-1},
						  }
--灯谜时间信息
x310160_g_DengmiTimer	= { nStart = -1,nIndex = -1 }
x310160_g_DengmiArray 	= {}

--出题相关
x310160_g_TimerInterval	= 59*1000 		--毫秒
x310160_g_MaxCount		= 10			--不能超过31

x310160_g_GameId		= 1007			--玩法ID
x310160_g_LimitLevel	= 40			--最低级别
x310160_g_LimitSceneId	= 0				--玩法所在场景，必须是在玩法场景，否则一切响应皆为非法

x310160_g_StartDay		= -1			--启动日期，答题触发，启动日期必须一致才可继续

x310160_g_GameID_Right	= 961
x310160_g_GameID_Error	= 962

----------------------------------------------------------------------------------------------
--以下奖励相关信息
----------------------------------------------------------------------------------------------
--经验，声望，现银
x310160_g_ExpBonus		= 500	--奖励经验 公式=level*exp
x310160_g_ExpBonus1		= 650 --奖励经验 公式=level*exp
x310160_g_ShengWang		= 0			--奖励声望，固定值
x310160_g_MoneyBonus	= 15	--奖励现银，公式=level*money

--随机物品
x310160_g_ItemGL		= 20			--掉落概率
x310160_g_ItemList		= { 			--物品列表
							{12030107,1}			
						  }

--当有某个任务时的奖励信息
x310160_g_MissionGL		= 50			--掉落概率
x310160_g_MissionId		= 1482			--任务ID
x310160_g_MissionBonus	= 13015012		--掉落奖励

----------------------------------------------------------------------------------------------
--检查有效性
----------------------------------------------------------------------------------------------
function x310160_CheckValid( sceneId,selfId)

	local level = GetLevel(sceneId,selfId)
	if level<x310160_g_LimitLevel then
		return -1
	end
	
	if sceneId ~= x310160_g_LimitSceneId then
		return -2
	end
	
	return 1

end

----------------------------------------------------------------------------------------------
--检查启动时间是否有效
----------------------------------------------------------------------------------------------
function x310160_IsStartTimeValid()

	local h,m = x310160_GetValidTimeHourMin()
	
	local cur  = h*60  + m
	local from = 19*60 + 00
	local to   = 20*60 + 00
	
	if cur < from or cur > to then
		
		--记日志
		local strMsg = format("DML:<Info>x310160_IsStartTimeValid starttime invalid started  h=%d,m=%d", h, m )
    	WriteLog( 1, strMsg )
		return 0
	end
	
	return 1

end

----------------------------------------------------------------------------------------------
--设置开始日期
----------------------------------------------------------------------------------------------
function x310160_SetStartDay( nDay )

	if x310160_g_StartDay ~= -1 then
		return
	end
	
	x310160_g_StartDay = nDay

end

----------------------------------------------------------------------------------------------
--清除开始的日期
----------------------------------------------------------------------------------------------
function x310160_ClearStartDay()
	x310160_g_StartDay = -1
end

----------------------------------------------------------------------------------------------
--是否隔天了
----------------------------------------------------------------------------------------------
function x310160_IsNextDay()
	
	local curDay = GetDayOfYear()
	
	if x310160_g_StartDay ~= curDay then
		return 1
	end
	
	return 0
	
end

----------------------------------------------------------------------------------------------
--判断玩家是否在猜灯谜
----------------------------------------------------------------------------------------------
function x310160_IsPlayerGaming( sceneId,selfId )
	
	local nNpcID = GetPlayerRuntimeData(sceneId,selfId,RD_QUEST_DENGMI_NPC_FLAG)
	if nNpcID <= 0 then
		return -1
	end
	
	--检查有效距离
	if GetDist( sceneId, selfId, nNpcID,3 ) > 3 then
		
		--当发现距离无效的时候，清空相关数据
		QuestDengmi_SendDengmiInfo( sceneId, selfId, -1, -1 )
		
		SetPlayerRuntimeData(sceneId,selfId,RD_QUEST_DENGMI_NPC_FLAG,0)
		SetPlayerRuntimeData(sceneId,selfId,RD_QUEST_DENGMI_CUR_DENGMI,0)
		
		return -1
	end 
	
	return 1
end

----------------------------------------------------------------------------------------------
--判断玩家猜灯谜是否次数已满
----------------------------------------------------------------------------------------------
function x310160_IsPlayerGamingFull( sceneId,selfId )

	local nDate   = GetQuestData(sceneId,selfId,MD_QUEST_DENGMI_DATE[1], MD_QUEST_DENGMI_DATE[2], MD_QUEST_DENGMI_DATE[3] )
	local nCount  = GetQuestData(sceneId,selfId,MD_QUEST_DENGMI_COUNT[1],MD_QUEST_DENGMI_COUNT[2],MD_QUEST_DENGMI_COUNT[3])

	local nCurDay = GetDayOfYear()
	if nCurDay == nDate then
		if nCount >= x310160_g_MaxCount then
			return 1
		end
	end

	return 0
end

----------------------------------------------------------------------------------------------
--查找NPC
----------------------------------------------------------------------------------------------
function x310160_FindNpc(sceneId,npcId)
	
	for n,item in x310160_g_DengmiInfo do
		if npcId == item.npcID then
			return n
		end
	end
	
	return -1
							
end

----------------------------------------------------------------------------------------------
--检查并且重置数据
----------------------------------------------------------------------------------------------
function x310160_CheckAndResetPlayerGameInfo( sceneId,selfId )

	local nDay = GetQuestData(sceneId,selfId,MD_QUEST_DENGMI_DATE[1],MD_QUEST_DENGMI_DATE[2],MD_QUEST_DENGMI_DATE[3])	
	local nCurDay = GetDayOfYear()
	if nCurDay ~= nDay then
		--设置今天猜灯谜信息
		SetQuestData(sceneId,selfId,MD_QUEST_DENGMI_DATE[1],MD_QUEST_DENGMI_DATE[2],MD_QUEST_DENGMI_DATE[3],nCurDay)
		SetQuestData(sceneId,selfId,MD_QUEST_DENGMI_COUNT[1],MD_QUEST_DENGMI_COUNT[2],MD_QUEST_DENGMI_COUNT[3],0)	
		
		SetQuestData(sceneId,selfId,MD_QUEST_DENGMI_NPC[1][1],MD_QUEST_DENGMI_NPC[1][2],MD_QUEST_DENGMI_NPC[1][3],-1)
		SetQuestData(sceneId,selfId,MD_QUEST_DENGMI_NPC[2][1],MD_QUEST_DENGMI_NPC[2][2],MD_QUEST_DENGMI_NPC[2][3],-1)
		SetQuestData(sceneId,selfId,MD_QUEST_DENGMI_NPC[3][1],MD_QUEST_DENGMI_NPC[3][2],MD_QUEST_DENGMI_NPC[3][3],-1)
		SetQuestData(sceneId,selfId,MD_QUEST_DENGMI_NPC[4][1],MD_QUEST_DENGMI_NPC[4][2],MD_QUEST_DENGMI_NPC[4][3],-1)
		SetQuestData(sceneId,selfId,MD_QUEST_DENGMI_NPC[5][1],MD_QUEST_DENGMI_NPC[5][2],MD_QUEST_DENGMI_NPC[5][3],-1)
	end
end

----------------------------------------------------------------------------------------------
--给奖励，答对的情况下，才会触发
----------------------------------------------------------------------------------------------
function x310160_GiveBonus( sceneId,selfId )

	--活动未开启
	if GetGameOpenById(x310160_g_GameId) ~= 1 then
		return
	end
	
	--检查玩家有效性
	if x310160_CheckValid( sceneId,selfId ) ~= 1 then
		return
	end
	
	local level = GetLevel(sceneId,selfId)
	local name = GetName(sceneId,selfId)
	if name == nil then
		name = "ErrorName"
	end
	
	--给经验
	if x310160_g_ExpBonus > 0 then
		local level = GetLevel(sceneId,selfId)
	if level <70 then
		local bonusExp = level*x310160_g_ExpBonus
		AddExp(sceneId,selfId,bonusExp)
		
		local msg = format("#Y获得#R经验%d点#Y的奖励",bonusExp)
		
		LuaScenceM2Player(sceneId, selfId, msg, name , 2,1)
        LuaScenceM2Player(sceneId, selfId, msg, name , 3,1)
	else
		local bonusExp = level*x310160_g_ExpBonus1
		AddExp(sceneId,selfId,bonusExp)
				
		local msg = format("#Y获得#R经验%d点#Y的奖励",bonusExp)
		
		LuaScenceM2Player(sceneId, selfId, msg, name , 2,1)
    LuaScenceM2Player(sceneId, selfId, msg, name , 3,1)
  end
	end
	
	--给声望
	if x310160_g_ShengWang > 0 then
		local bonusShengWang = GetShengWang( sceneId,selfId) + x310160_g_ShengWang
		SetShengWang( sceneId,selfId,bonusShengWang)
		
		local msg = format("您获得了%d点声望值的奖励",x310160_g_ShengWang)
		
		LuaScenceM2Player(sceneId, selfId, msg, name , 2,1)
        LuaScenceM2Player(sceneId, selfId, msg, name , 3,1)
	end
	
	--给现银
	if x310160_g_MoneyBonus > 0 then
		local bonusMoney = level*x310160_g_MoneyBonus
		local buff 	=	9011
		local buff1 =	9013
		local buff2 =	9012
		if IsHaveSpecificImpact( sceneId, selfId, buff) == 1 or IsHaveSpecificImpact( sceneId, selfId, buff1) == 1  or IsHaveSpecificImpact( sceneId, selfId, buff2) == 1 then
			AddMoney(sceneId,selfId,0,bonusMoney,x310160_g_scriptId)
		else
			AddMoney(sceneId,selfId,1,bonusMoney,x310160_g_scriptId)
		end
	end
	
	--给物品
	local nItemCount = getn(x310160_g_ItemList)
	if nItemCount > 0 and x310160_g_ItemGL > 0  then

		--随机是否可以获得物品
		local bGet = random(1,100)
		if bGet <= x310160_g_ItemGL then
			
			--随机获得的物品
			local bGetItem = random(1,nItemCount)
			
			local itemInfo = x310160_g_ItemList[bGetItem]
			
			BeginAddItem(sceneId)
			if IsHaveSpecificImpact( sceneId, selfId, buff) == 1 or IsHaveSpecificImpact( sceneId, selfId, buff1) == 1 or IsHaveSpecificImpact( sceneId, selfId, buff2) == 1 then
            AddItem( sceneId, itemInfo[1],itemInfo[2] )
            else
            AddBindItem( sceneId, itemInfo[1],itemInfo[2] )
            end
            local ret = EndAddItem(sceneId,selfId)
            if ret > 0 then
            	
                AddItemListToPlayer(sceneId,selfId)
                
                --local msg = format("#Y您获得了#G@item_%d#Y的奖励",itemInfo[1],itemInfo[2])
			--	LuaScenceM2Player(sceneId, selfId, msg, name , 2,1)
		       -- LuaScenceM2Player(sceneId, selfId, msg, name , 3,1)
		       -- LuaAllScenceM2Wrold( sceneId, format( "#G真是幸运！#Y%s#G在猜灯谜中意外获得了一张#R藏宝图#G！", name ), 1, 1)
		    else
		    	LuaScenceM2Player(sceneId, selfId, "#cffcf00物品栏已满，无法得到奖励物品！", name , 2,1)
		        LuaScenceM2Player(sceneId, selfId, "#cffcf00物品栏已满，无法得到奖励物品！", name , 3,1)
            end
		end
	end
	-- 添加一枚大都嘉年华娱乐币
    BeginAddItem( sceneId)
    AddItem( sceneId, 11990117, 1)
    if EndAddItem( sceneId, selfId) <= 0 then
        Msg2Player( sceneId, selfId, "你的背包已满，无法获得#{_ITEM11990117}奖励。", 8, 2)
    else
        AddItemListToPlayer( sceneId, selfId)
    end
	--给任务物品
	if IsHaveQuestNM( sceneId, selfId, x310160_g_MissionId) == 1 then
		
		--判断任务是否完成
		local misIndex = GetQuestIndexByID(sceneId,selfId,x310160_g_MissionId)
		if misIndex < 0 then
			return
		end
		
		--任务完成，返回
		if GetQuestParam( sceneId,selfId,misIndex,7) == 1 then
			return
		end
		
		--给奖励
		local bGet = random(1,100)
		if bGet <= x310160_g_MissionGL then
			
			BeginAddItem(sceneId)
            AddItem( sceneId, x310160_g_MissionBonus,1 )
            local ret = EndAddItem(sceneId,selfId)
            if ret > 0 then
                AddItemListToPlayer(sceneId,selfId)
                
                --这个不用给提示，任务脚本会给出相关提示
		    else
		    	LuaScenceM2Player(sceneId, selfId, "#cffcf00物品栏已满，无法得到任务物品！", name , 2,1)
		        LuaScenceM2Player(sceneId, selfId, "#cffcf00物品栏已满，无法得到任务物品！", name , 3,1)
            end
		end
	end
end

----------------------------------------------------------------------------------------------
--启动定时器
----------------------------------------------------------------------------------------------
function x310160_OnTimerDoingStart( sceneId, actId, Param1, Param2, Param3, Param4, Param5 )

	--活动关闭
	if GetGameOpenById(x310160_g_GameId) ~= 1 then
		return		
	end
	
	--如果活动已经开始，但是还没有结束，那么不作为，只记日志
	if x310160_g_DengmiTimer.nStart >= 0 then
		--记日志
		local strMsg = format("DML:<Info>x310160_OnTimerDoingStart already started sceneId = %d, actId=%d", sceneId,actId )
    	WriteLog( 1, strMsg )		
		return
	end
	
	--检查活动的开始时间是否有效
	if x310160_IsStartTimeValid() == 0 then
		
		--记日志
		local strMsg = format("DML:<Info>x310160_OnTimerDoingStart starttime invalid sceneId = %d, actId=%d", sceneId,actId )
    	WriteLog( 1, strMsg )		
		return
	end

	--取得灯谜个数
	local nCount = QuestDengmi_GetQuestionCount()
	if nCount > 0 then

		--初始化
		for i,item in x310160_g_DengmiInfo do
			item.nDengmi = -1
			item.npcID = FindMonsterByGUID(sceneId,item.GUID)
			
			--记日志
			local strMsg = format("DML:<Info>x310160_OnTimerDoingStart Initialise npc npcId = %d,GUID=%d", item.npcID, item.GUID )
		    WriteLog( 1, strMsg )		
			
		end
		
		x310160_g_DengmiTimer.nStart = -1
		x310160_g_DengmiTimer.nIndex = 0
		
		--设置启动日期
		x310160_SetStartDay( GetDayOfYear() )
		
		SetSystemTimerTick( sceneId, x310160_g_scriptId, "ProcTiming", actId, 1000 ) --5秒后开始
	end
	
	--记日志
	local strMsg = format("DML:<Info>x310160_OnTimerDoingStart sceneId = %d, count=%d, actId=%d", sceneId, nCount,actId )
    WriteLog( 1, strMsg )
	
end

----------------------------------------------------------------------------------------------
--清除灯谜
----------------------------------------------------------------------------------------------
function x310160_ClearDengmi(sceneId)

	--灯谜信息
	x310160_g_DengmiInfo	= {
								{npcID=-1,GUID = 141506,nDengmi=-1},
								{npcID=-1,GUID = 141507,nDengmi=-1},
								{npcID=-1,GUID = 141508,nDengmi=-1},
								{npcID=-1,GUID = 141509,nDengmi=-1},
								{npcID=-1,GUID = 141510,nDengmi=-1},
						  	  }
	
	x310160_g_DengmiTimer	= { nStart = -1,nIndex = -1 }
	x310160_g_DengmiArray 	= {}
	
	x310160_ClearStartDay()

	local nHumanCount = GetScenePlayerCount( sceneId )
	for i=0,nHumanCount do

		local objId = GetScenePlayerObjId(sceneId,i)
		if IsPlayerStateNormal(sceneId,objId) == 1 and x310160_IsPlayerGaming(sceneId,objId) == 1 then
		
			--通知客户端清数据
			QuestDengmi_SendDengmiInfo( sceneId, objId, -1, -1 )
			
			SetPlayerRuntimeData(sceneId,objId,RD_QUEST_DENGMI_NPC_FLAG,0)
			SetPlayerRuntimeData(sceneId,objId,RD_QUEST_DENGMI_CUR_DENGMI,0)
			
			--更新对话框内容
			BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"今天的天坛灯谜会结束了！")				
			EndQuestEvent(sceneId)
			DispatchQuestEventList(sceneId,objId,objId)
			
		end
	end
	
end

----------------------------------------------------------------------------------------------
--活动的Tick
----------------------------------------------------------------------------------------------
function x310160_ProcTiming( sceneId, actId, uTime )


	----------------------------------------------------------------------------------------------
	--活动关闭
	----------------------------------------------------------------------------------------------
	if GetGameOpenById(x310160_g_GameId) ~= 1 then
		
		--清除相关信息
		x310160_ClearDengmi(sceneId)		
		
		--记录日志
		local strMsg = format("DML:<Info>x310160_ProcTiming GM close sceneId = %d", sceneId )
    	WriteLog( 1, strMsg )			

		return		
	end
	
	----------------------------------------------------------------------------------------------
	--隔天了
	----------------------------------------------------------------------------------------------
	if x310160_IsNextDay() == 1 then
		
		--清除相关信息
		x310160_ClearDengmi(sceneId)
		
		--记日志
		local strMsg = format("DML:<Info>x310160_ProcTiming nextday close sceneId = %d", sceneId )
    	WriteLog( 1, strMsg )
    	
    	return 
	end
	
	----------------------------------------------------------------------------------------------
	--出题已满
	----------------------------------------------------------------------------------------------
	local nCount = QuestDengmi_GetQuestionCount()
	if x310160_g_DengmiTimer.nIndex >= 370 then
		
		--清除相关信息
		x310160_ClearDengmi(sceneId)
		
		--活动自然结束
		local strMsg = format("DML:<Info>x310160_ProcTiming party close sceneId = %d", sceneId )
    	WriteLog( 1, strMsg )			
				
		return
	end

	----------------------------------------------------------------------------------------------
	--设置倒计时和当前题号信息
	----------------------------------------------------------------------------------------------
	x310160_g_DengmiTimer.nStart = x310160_GetValidTime()
	x310160_g_DengmiTimer.nIndex = x310160_g_DengmiTimer.nIndex + 1
	
	for i,item in x310160_g_DengmiInfo do
		
		item.nDengmi = random(0,nCount-1)
		local id,strDesc,strAnswer1,strAnswer2,strAnswer3,strAnswer4,nAnswer = QuestDengmi_GetQuestionInfo(item.nDengmi)
		
		x310160_g_DengmiArray[i] = {}		
		x310160_g_DengmiArray[i].id = id + 100000		
		x310160_g_DengmiArray[i].strDesc = strDesc
		x310160_g_DengmiArray[i].strAnswer1 = strAnswer1
		x310160_g_DengmiArray[i].strAnswer2 = strAnswer2
		x310160_g_DengmiArray[i].strAnswer3 = strAnswer3
		x310160_g_DengmiArray[i].strAnswer4 = strAnswer4
		x310160_g_DengmiArray[i].nAnswer = nAnswer + 11000
		
		--活动自然结束
		local strMsg = format("DML:<Info>x310160_ProcTiming new dengmi sceneId=%d,i=%d,dengmi=%d,<%s>,<%s>,<%s>,<%s>,<%s>,%d", 
							  sceneId,i,id,strDesc,strAnswer1,strAnswer2,strAnswer3,strAnswer4,nAnswer )
    	WriteLog( 1, strMsg )
	end
	
	----------------------------------------------------------------------------------------------
	--开始同步
	----------------------------------------------------------------------------------------------
	local nHumanCount = GetScenePlayerCount( sceneId )
	for i=0,nHumanCount do

		local objId = GetScenePlayerObjId(sceneId,i)
		if IsPlayerStateNormal(sceneId,objId) == 1 and x310160_IsPlayerGaming(sceneId,objId) == 1 then

			--验证玩家是否是今天参与答题的人
			local nDate   = GetQuestData(sceneId,objId,MD_QUEST_DENGMI_DATE[1],MD_QUEST_DENGMI_DATE[2],MD_QUEST_DENGMI_DATE[3])
			local nCount  = GetQuestData(sceneId,objId,MD_QUEST_DENGMI_COUNT[1],MD_QUEST_DENGMI_COUNT[2],MD_QUEST_DENGMI_COUNT[3])
			local nNpcID  = GetPlayerRuntimeData(sceneId,objId,RD_QUEST_DENGMI_NPC_FLAG)
			local nCurDay = GetDayOfYear()
			
			
			if x310160_IsPlayerGamingFull(sceneId,objId) == 1 then
					
				--通知客户端清数据
				QuestDengmi_SendDengmiInfo( sceneId, objId, -1, -1 )
				
				SetPlayerRuntimeData(sceneId,objId,RD_QUEST_DENGMI_NPC_FLAG,0)
				SetPlayerRuntimeData(sceneId,objId,RD_QUEST_DENGMI_CUR_DENGMI,0)
				
				--更新对话框内容
				BeginQuestEvent(sceneId)
					AddQuestText(sceneId,"\t今天你已经猜完10次灯谜了，明天这个时候再来吧。")				
				EndQuestEvent(sceneId)
				DispatchQuestEventList(sceneId,objId,nNpcID)
				
			else
				
				for n,item in x310160_g_DengmiInfo do
					--找到玩家交互的NPC
					if nNpcID == item.npcID then
							
						--在答题库中定位索引
						local dm = x310160_g_DengmiArray[n]
						
						--向客户端同步题目索引和题目倒计时
						local nTime = x310160_g_TimerInterval/1000 - (x310160_GetValidTime() - x310160_g_DengmiTimer.nStart)
						if nTime > 0 then
							QuestDengmi_SendDengmiInfo( sceneId, objId, x310160_g_DengmiTimer.nIndex, nTime )
						end
						
						
						SetPlayerRuntimeData(sceneId,objId,RD_QUEST_DENGMI_NPC_FLAG,nNpcID)
						SetPlayerRuntimeData(sceneId,objId,RD_QUEST_DENGMI_CUR_DENGMI,dm.id)
						
						--更新对话框内容
						BeginQuestEvent(sceneId)
							
							AddQuestText(sceneId,dm.strDesc)
							x310160_AddDengmiAnswerOption( sceneId, 
										   				   dm.strAnswer1, 
										   				   dm.strAnswer2, 
										   				   dm.strAnswer3, 
										   				   dm.strAnswer4 )
														
						EndQuestEvent(sceneId)
						DispatchQuestEventList(sceneId,objId,nNpcID)
						
						break
					end
				end
			end
		end
	end
	
	----------------------------------------------------------------------------------------------
	--设置下一个Tick
	----------------------------------------------------------------------------------------------
	SetSystemTimerTick( sceneId, x310160_g_scriptId, "ProcTiming", actId, x310160_g_TimerInterval )
end


----------------------------------------------------------------------------------------------
--枚举
----------------------------------------------------------------------------------------------
function x310160_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

	--通知客户端清除数据
	QuestDengmi_SendDengmiInfo( sceneId, selfId, -1, -1 )
				
	SetPlayerRuntimeData(sceneId,selfId,RD_QUEST_DENGMI_NPC_FLAG,0)
	SetPlayerRuntimeData(sceneId,selfId,RD_QUEST_DENGMI_CUR_DENGMI,0)
	
	if GetGameOpenById(x310160_g_GameId) ~= 1 then
		return
	end
	
    AddQuestNumText(sceneId,x310160_g_scriptId,"我要猜灯谜",3,x310160_g_scriptId);
        
end

----------------------------------------------------------------------------------------------
--添加灯谜答案选项
----------------------------------------------------------------------------------------------
function x310160_AddDengmiAnswerOption( sceneId,strAnswer1,strAnswer2,strAnswer3,strAnswer4)

	--随机添加选项
	local arr_answer = { {strAnswer1,11001,0},{strAnswer2,11002,0},{strAnswer3,11003,0},{strAnswer4,11004,0} }
	for i=1,4 do
		
		local nCount = getn(arr_answer)
		local n = random(1,nCount)
		while arr_answer[n][3] == 1 do
			n = random(1,nCount)
		end
		
		arr_answer[n][3] = 1
		
		AddQuestNumText(sceneId,x310160_g_scriptId,arr_answer[n][1],3,arr_answer[n][2] )
	end
	
end

----------------------------------------------------------------------------------------------
--脚本默认事件
----------------------------------------------------------------------------------------------
function x310160_ProcEventEntry( sceneId ,selfId, npcId,idScript,idExt )

	----------------------------------------------------------------------------------------------
	--活动未开启
	----------------------------------------------------------------------------------------------
	if GetGameOpenById(x310160_g_GameId) ~= 1 then
		
		--通知客户端清除数据
		QuestDengmi_SendDengmiInfo( sceneId, selfId, -1, -1 )
					
		SetPlayerRuntimeData(sceneId,selfId,RD_QUEST_DENGMI_NPC_FLAG,0)
		SetPlayerRuntimeData(sceneId,selfId,RD_QUEST_DENGMI_CUR_DENGMI,0)
		
		--给出相关提示
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"灯谜会已经关闭！")				
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,npcId)
		return
	end
	
	----------------------------------------------------------------------------------------------
	--检查玩家有效性
	----------------------------------------------------------------------------------------------
	if x310160_CheckValid( sceneId,selfId ) ~= 1 then
		return
	end
	
	----------------------------------------------------------------------------------------------
	--当活动没有开始的时候，不允许进行相关其他操作
	----------------------------------------------------------------------------------------------
	if x310160_g_DengmiTimer.nStart < 0 then
		
		--通知客户端清除数据
		QuestDengmi_SendDengmiInfo( sceneId, selfId, -1, -1 )
					
		SetPlayerRuntimeData(sceneId,selfId,RD_QUEST_DENGMI_NPC_FLAG,0)
		SetPlayerRuntimeData(sceneId,selfId,RD_QUEST_DENGMI_CUR_DENGMI,0)
		
		--给出相关提示
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"\t灯谜会还没开始呢，别心急。\n\t#G（每天晚上的19：30--24：00灯谜会开放）")				
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,npcId)
		return
	end
	
	----------------------------------------------------------------------------------------------
	--隔天了
	----------------------------------------------------------------------------------------------
	if x310160_IsNextDay() == 1 then
		
		--通知客户端清除数据
		QuestDengmi_SendDengmiInfo( sceneId, selfId, -1, -1 )
					
		SetPlayerRuntimeData(sceneId,selfId,RD_QUEST_DENGMI_NPC_FLAG,0)
		SetPlayerRuntimeData(sceneId,selfId,RD_QUEST_DENGMI_CUR_DENGMI,0)
		
		--给出相关提示
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"\t灯谜会还没开始呢，别心急。\n\t#G（每天晚上的19：30--24：00灯谜会开放）")				
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,npcId)
		return
	end
	

	if idExt == x310160_g_scriptId then
		
		
		----------------------------------------------------------------------------------------------
		--开始猜谜
		----------------------------------------------------------------------------------------------
		
		local nFind = x310160_FindNpc(sceneId,npcId)
		if nFind > 0 then
			
			--验证是否答过题
			if x310160_IsPlayerGamingFull( sceneId,selfId ) == 1 then
					
				--通知客户端清数据
				QuestDengmi_SendDengmiInfo( sceneId, selfId, -1, -1 )
							
				SetPlayerRuntimeData(sceneId,selfId,RD_QUEST_DENGMI_NPC_FLAG,0)
				SetPlayerRuntimeData(sceneId,selfId,RD_QUEST_DENGMI_CUR_DENGMI,0)
				
				--更新对话框内容
				BeginQuestEvent(sceneId)
					AddQuestText(sceneId,"\t今天你已经猜完10次灯谜了，明天再来吧。")				
				EndQuestEvent(sceneId)
				DispatchQuestEventList(sceneId,selfId,npcId)
				return
			end
				
			--当前索引的题是否已经在这个NPC处答过了
			local nPreIndex = GetQuestData(sceneId,selfId,MD_QUEST_DENGMI_NPC[nFind][1],MD_QUEST_DENGMI_NPC[nFind][2],MD_QUEST_DENGMI_NPC[nFind][3])
			if nPreIndex == x310160_g_DengmiTimer.nIndex then
				
				--设置答题信息
				SetPlayerRuntimeData(sceneId,selfId,RD_QUEST_DENGMI_NPC_FLAG,npcId)
				SetPlayerRuntimeData(sceneId,selfId,RD_QUEST_DENGMI_CUR_DENGMI,x310160_g_DengmiTimer.nIndex)
				
				--向客户端同步题目索引和题日倒计时
				local nTime = x310160_g_TimerInterval/1000 - (x310160_GetValidTime() - x310160_g_DengmiTimer.nStart)
				if nTime > 0 then
					QuestDengmi_SendDengmiInfo( sceneId, selfId, x310160_g_DengmiTimer.nIndex, nTime )
				end
				
				
				--更新对话框内容
				BeginQuestEvent(sceneId)
					AddQuestText(sceneId,"你可以先去我的姐妹那里猜灯谜，或者在我这里等待下一个灯谜！")				
				EndQuestEvent(sceneId)
				DispatchQuestEventList(sceneId,selfId,npcId)
				
				--记录日志
				local name = GetName(sceneId,selfId)
				if name == nil then
					name = "Error"
				end
				local strMsg = format("DML:<Info>x310160_ProcEventEntry 000 sceneId=%d,name=%s,npcIndex=%d,preIndex=%d,index=%d", 
							  		   sceneId, name, nFind, nPreIndex, x310160_g_DengmiTimer.nIndex)
    			WriteLog( 1, strMsg )
				return
			end			
			
			
			--检查并且重置玩家数据
			x310160_CheckAndResetPlayerGameInfo( sceneId,selfId )
			

			--在答题库中定位索引
			local dm = x310160_g_DengmiArray[nFind]
			
			--设置npcid和答题编号
			SetPlayerRuntimeData(sceneId,selfId,RD_QUEST_DENGMI_NPC_FLAG,npcId)
			SetPlayerRuntimeData(sceneId,selfId,RD_QUEST_DENGMI_CUR_DENGMI,dm.id)

			
			--向客户端同步题目索引和题日倒计时
			local nTime = x310160_g_TimerInterval / 1000 - ( x310160_GetValidTime() - x310160_g_DengmiTimer.nStart )
			if nTime > 0 then
				QuestDengmi_SendDengmiInfo( sceneId, selfId, x310160_g_DengmiTimer.nIndex, nTime )
			end
			
			
			--更新对话框内容
			BeginQuestEvent(sceneId)
				
				AddQuestText(sceneId,dm.strDesc)
				x310160_AddDengmiAnswerOption( sceneId, 
											   dm.strAnswer1, 
											   dm.strAnswer2, 
											   dm.strAnswer3, 
											   dm.strAnswer4 )
											
			EndQuestEvent(sceneId)
			DispatchQuestEventList(sceneId,selfId,npcId)
			
		end
		
	elseif idExt >= 11001 and idExt <= 11004 then
		
		----------------------------------------------------------------------------------------------
		--玩家选中的某个答题
		----------------------------------------------------------------------------------------------
		
		--验证是否答过题
		local nPreDate  = GetQuestData(sceneId,selfId,MD_QUEST_DENGMI_DATE[1],MD_QUEST_DENGMI_DATE[2],MD_QUEST_DENGMI_DATE[3])
		local nPreCount = GetQuestData(sceneId,selfId,MD_QUEST_DENGMI_COUNT[1],MD_QUEST_DENGMI_COUNT[2],MD_QUEST_DENGMI_COUNT[3])
		
		local nDate = GetDayOfYear()
		if nDate == nPreDate then
			
			--检查今日猜灯谜次数是否已满
			if nPreCount >= x310160_g_MaxCount then
				
				--通知客户端清除数据
				QuestDengmi_SendDengmiInfo( sceneId, selfId, -1, -1 )
							
				SetPlayerRuntimeData(sceneId,selfId,RD_QUEST_DENGMI_NPC_FLAG,0)
				SetPlayerRuntimeData(sceneId,selfId,RD_QUEST_DENGMI_CUR_DENGMI,0)
				
				--更新对话框内容
				BeginQuestEvent(sceneId)
					AddQuestText(sceneId,"\t今天你已经猜完10次灯谜了，明天再来吧。")				
				EndQuestEvent(sceneId)
				DispatchQuestEventList(sceneId,selfId,npcId)
				return
			end
			
			--取得NPC的Index
			local nFind = 0
			for i,item in x310160_g_DengmiInfo do
				if item.npcID == npcId then
					nFind = i
					break
				end
			end
			
			if nFind <= 0 or nFind >= 6 then
				return
			end
			
			--取得题目信息
			local dm = x310160_g_DengmiArray[nFind]
			
			--检查对话NPC
			local preNpcId= GetPlayerRuntimeData(sceneId,selfId,RD_QUEST_DENGMI_NPC_FLAG)
			if npcId ~= preNpcId then
				
				--通知客户端清除数据
				QuestDengmi_SendDengmiInfo( sceneId, selfId, -1, -1 )
							
				SetPlayerRuntimeData(sceneId,selfId,RD_QUEST_DENGMI_NPC_FLAG,0)
				SetPlayerRuntimeData(sceneId,selfId,RD_QUEST_DENGMI_CUR_DENGMI,0)
				
				--对话NPC没有验证通过
				BeginQuestEvent(sceneId)
					AddQuestText(sceneId,"\t灯谜会已经结束啦，明天再来吧。")				
				EndQuestEvent(sceneId)
				DispatchQuestEventList(sceneId,selfId,npcId)
				return
			end
			
			--如果NPC题目已经答过，则不能再答
			local nPreIndex = GetQuestData(sceneId,selfId,MD_QUEST_DENGMI_NPC[nFind][1],MD_QUEST_DENGMI_NPC[nFind][2],MD_QUEST_DENGMI_NPC[nFind][3])
			if nPreIndex == x310160_g_DengmiTimer.nIndex then
				return
			end
			
			
			--向客户端同步题目索引和题日倒计时
			local nTime = x310160_g_TimerInterval / 1000 - ( x310160_GetValidTime() - x310160_g_DengmiTimer.nStart )
			if nTime > 0 then
				QuestDengmi_SendDengmiInfo( sceneId, selfId, x310160_g_DengmiTimer.nIndex, nTime )
			end
			
			
			--检查题目号码是否与这一致
			local nId = GetPlayerRuntimeData(sceneId,selfId,RD_QUEST_DENGMI_CUR_DENGMI)
			if nId ~= dm.id then
				
				local nSelfPreCount = GetQuestData(sceneId,selfId,MD_QUEST_DENGMI_COUNT[1],MD_QUEST_DENGMI_COUNT[2],MD_QUEST_DENGMI_COUNT[3]) + 1
				SetQuestData(sceneId,selfId,MD_QUEST_DENGMI_COUNT[1],MD_QUEST_DENGMI_COUNT[2],MD_QUEST_DENGMI_COUNT[3],nSelfPreCount)
				SetQuestData(sceneId,selfId,MD_QUEST_DENGMI_NPC[nFind][1],MD_QUEST_DENGMI_NPC[nFind][2],MD_QUEST_DENGMI_NPC[nFind][3],x310160_g_DengmiTimer.nIndex)
				
				--相关提示
				if x310160_IsPlayerGamingFull(sceneId,selfId) == 1 then
					
					--通知客户端清数据
					QuestDengmi_SendDengmiInfo( sceneId, selfId, -1, -1 )
					
					SetPlayerRuntimeData(sceneId,selfId,RD_QUEST_DENGMI_NPC_FLAG,0)
					SetPlayerRuntimeData(sceneId,selfId,RD_QUEST_DENGMI_CUR_DENGMI,0)
					
					local name = GetName(sceneId,selfId)
					LuaScenceM2Player( sceneId,selfId,"\t很遗憾，你猜错了哦。",name,3,1)
					LuaScenceM2Player( sceneId,selfId,"\t很遗憾，你猜错了哦。",name,2,1)
					
					--更新对话框内容
					BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"\t很遗憾，你猜错了哦。" )
						AddQuestText(sceneId,"\t今天你已经猜完10次灯谜了，明天这个时候再来吧。")
					EndQuestEvent(sceneId)
					DispatchQuestEventList(sceneId,selfId,npcId)
				else
					
					local name = GetName(sceneId,selfId)
					LuaScenceM2Player( sceneId,selfId,format("\t很遗憾，你猜错了哦，今天你还可以猜%d次。",x310160_g_MaxCount - nSelfPreCount ),name,3,1)
					LuaScenceM2Player( sceneId,selfId,format("\t很遗憾，你猜错了哦，今天你还可以猜%d次。",x310160_g_MaxCount - nSelfPreCount ),name,2,1)
					
					BeginQuestEvent(sceneId)
					AddQuestText(sceneId,format("\t很遗憾，你猜错了哦，今天你还可以猜%d次。\n\t你可以继续在我这里等待灯谜更新，或者去我的其他姐妹那里继续猜灯谜。",x310160_g_MaxCount - nSelfPreCount ) )				
					EndQuestEvent(sceneId)
					DispatchQuestEventList(sceneId,selfId,npcId)
					
				end
				
				--添加玩法日志
				GamePlayScriptLog( sceneId, selfId, x310160_g_GameID_Error)
				
				--记录日志
				local name = GetName(sceneId,selfId)
				if name == nil then
					name = "Error"
				end
				local strMsg = format("DML:<Info>x310160_ProcEventEntry 001 name=%s,npcIndex=%d,index=%d",name,nFind,x310160_g_DengmiTimer.nIndex)
				WriteLog( 1, strMsg )
				return
			end
			
			
			--题目编号检查通过了，这里再检查答案是否正确
			if dm.nAnswer == idExt then
				
				
				--答对了
				
				local nSelfPreCount = GetQuestData(sceneId,selfId,MD_QUEST_DENGMI_COUNT[1],MD_QUEST_DENGMI_COUNT[2],MD_QUEST_DENGMI_COUNT[3]) + 1
				SetQuestData(sceneId,selfId,MD_QUEST_DENGMI_COUNT[1],MD_QUEST_DENGMI_COUNT[2],MD_QUEST_DENGMI_COUNT[3],nSelfPreCount)
				SetQuestData(sceneId,selfId,MD_QUEST_DENGMI_NPC[nFind][1],MD_QUEST_DENGMI_NPC[nFind][2],MD_QUEST_DENGMI_NPC[nFind][3],x310160_g_DengmiTimer.nIndex)
				
				--相关提示
				if x310160_IsPlayerGamingFull(sceneId,selfId) == 1 then
					
					--通知客户端清数据
					QuestDengmi_SendDengmiInfo( sceneId, selfId, -1, -1 )
					
					SetPlayerRuntimeData(sceneId,selfId,RD_QUEST_DENGMI_NPC_FLAG,0)
					SetPlayerRuntimeData(sceneId,selfId,RD_QUEST_DENGMI_CUR_DENGMI,0)
					
					--相关提示
					local name = GetName(sceneId,selfId)
					LuaScenceM2Player( sceneId,selfId,"\t恭喜你猜对了灯谜。",name,3,1)
					LuaScenceM2Player( sceneId,selfId,"\t恭喜你猜对了灯谜。",name,2,1)
					
					--更新对话框内容
					BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"\t恭喜你猜对了灯谜。" )
						AddQuestText(sceneId,"\t今天你已经猜完10次灯谜了，明天这个时候再来吧。")	
					EndQuestEvent(sceneId)
					DispatchQuestEventList(sceneId,selfId,npcId)
				else
				
					--相关提示
					local name = GetName(sceneId,selfId)
					LuaScenceM2Player( sceneId,selfId,format("\t恭喜你猜对了灯谜，你今天还可以猜%d次。",x310160_g_MaxCount - nSelfPreCount ),name,3,1)
					LuaScenceM2Player( sceneId,selfId,format("\t恭喜你猜对了灯谜，你今天还可以猜%d次。",x310160_g_MaxCount - nSelfPreCount ),name,2,1)
					
					BeginQuestEvent(sceneId)
					AddQuestText(sceneId,format("\t恭喜你猜对了灯谜，你今天还可以猜%d次。\n\t你可以继续在我这里等待灯谜更新，或者去我的其他姐妹那里继续猜灯谜。",x310160_g_MaxCount - nSelfPreCount ) )				
					EndQuestEvent(sceneId)
					DispatchQuestEventList(sceneId,selfId,npcId)
				
				end
				
				--给奖励
				x310160_GiveBonus( sceneId,selfId )
				CallScriptFunction( 256224, "Finishdengmi", sceneId, selfId)	
				
				--添加玩法日志
				GamePlayScriptLog( sceneId, selfId, x310160_g_GameID_Right)
				 
				 --记录日志
				local name = GetName(sceneId,selfId)
				if name == nil then
					name = "Error"
				end
				local strMsg = format("DML:<Info>x310160_ProcEventEntry 002 name=%s,npcIndex=%d,index=%d",name,nFind,x310160_g_DengmiTimer.nIndex)
				WriteLog( 1, strMsg )
				
				return
				
			else
				
				--答错了
				
				local nSelfPreCount = GetQuestData(sceneId,selfId,MD_QUEST_DENGMI_COUNT[1],MD_QUEST_DENGMI_COUNT[2],MD_QUEST_DENGMI_COUNT[3]) + 1
				SetQuestData(sceneId,selfId,MD_QUEST_DENGMI_COUNT[1],MD_QUEST_DENGMI_COUNT[2],MD_QUEST_DENGMI_COUNT[3],nSelfPreCount)
				SetQuestData(sceneId,selfId,MD_QUEST_DENGMI_NPC[nFind][1],MD_QUEST_DENGMI_NPC[nFind][2],MD_QUEST_DENGMI_NPC[nFind][3],x310160_g_DengmiTimer.nIndex)
				
				--相关提示
				if x310160_IsPlayerGamingFull(sceneId,selfId) == 1 then
					
					--通知客户端清数据
					QuestDengmi_SendDengmiInfo( sceneId, selfId, -1, -1 )
					
					SetPlayerRuntimeData(sceneId,selfId,RD_QUEST_DENGMI_NPC_FLAG,0)
					SetPlayerRuntimeData(sceneId,selfId,RD_QUEST_DENGMI_CUR_DENGMI,0)
					
					--相关提示
					local name = GetName(sceneId,selfId)
					LuaScenceM2Player( sceneId,selfId,"\t很遗憾，你猜错了哦。",name,3,1)
					LuaScenceM2Player( sceneId,selfId,"\t很遗憾，你猜错了哦。",name,2,1)
					
					--更新对话框内容
					BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"\t很遗憾，你猜错了哦。")	
						AddQuestText(sceneId,"\t今天你已经猜完10次灯谜了，明天这个时候再来吧。")				
					EndQuestEvent(sceneId)
					DispatchQuestEventList(sceneId,selfId,npcId)
				else
				
					--相关提示
					local name = GetName(sceneId,selfId)
					LuaScenceM2Player( sceneId,selfId,format("\t很遗憾，你猜错了哦，今天你还可以猜%d次。",x310160_g_MaxCount - nSelfPreCount ),name,3,1)
					LuaScenceM2Player( sceneId,selfId,format("\t很遗憾，你猜错了哦，今天你还可以猜%d次。",x310160_g_MaxCount - nSelfPreCount ),name,2,1)
					
					BeginQuestEvent(sceneId)
					AddQuestText(sceneId,format("\t很遗憾，你猜错了哦，今天你还可以猜%d次。\n\t你可以继续在我这里等待灯谜更新，或者去我的其他姐妹那里继续猜灯谜。",x310160_g_MaxCount - nSelfPreCount ) )				
					EndQuestEvent(sceneId)
					DispatchQuestEventList(sceneId,selfId,npcId)
					
				end
				
				--添加玩法日志
				GamePlayScriptLog( sceneId, selfId, x310160_g_GameID_Error)
				
				--记录日志
				local name = GetName(sceneId,selfId)
				if name == nil then
					name = "Error"
				end
				local strMsg = format("DML:<Info>x310160_ProcEventEntry 003 name=%s,npcIndex=%d,index=%d",name,nFind,x310160_g_DengmiTimer.nIndex)
				WriteLog( 1, strMsg )
				return
				
			end			
			
		else
			
			--如果日期不对的话，但是玩家在答题，说明什么情况?在这里不响应
			return
			
		end
		
	end
		    
end


function x310160_ProcAcceptCheck( sceneId, selfId, NPCId )
    return 0
end

----------------------------------------------------------------------------------------------
--接受
----------------------------------------------------------------------------------------------
function x310160_ProcAccept( sceneId, selfId )
end

----------------------------------------------------------------------------------------------
--放弃
----------------------------------------------------------------------------------------------
function x310160_ProcQuestAbandon( sceneId, selfId, MissionId )
end

----------------------------------------------------------------------------------------------
--继续
----------------------------------------------------------------------------------------------
function x310160_OnContinue( sceneId, selfId, targetId )
end

----------------------------------------------------------------------------------------------
--检测是否可以提交
----------------------------------------------------------------------------------------------
function x310160_CheckSubmit( sceneId, selfId )
end

----------------------------------------------------------------------------------------------
--提交
----------------------------------------------------------------------------------------------
function x310160_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end

----------------------------------------------------------------------------------------------
--杀死怪物或玩家
----------------------------------------------------------------------------------------------
function x310160_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end

----------------------------------------------------------------------------------------------
--进入区域事件
----------------------------------------------------------------------------------------------
function x310160_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

----------------------------------------------------------------------------------------------
--道具改变
----------------------------------------------------------------------------------------------
function x310160_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end

----------------------------------------------------------------------------------------------
--取得有效的时间,在这里，做时间检查，如果两次取时间的差超过5秒或者小于0，则认定无效，重新取
--帮会战曾在取时间的问题上出过错，所以在这里做相同的检查
----------------------------------------------------------------------------------------------
function x310160_GetValidTime()

	local n1 = GetCurrentTime()
	local n2 = GetCurrentTime()
	
	local nResult = n2 - n1 
	while nResult > 5 or nResult < 0 do
		n1 = GetCurrentTime()
		n2 = GetCurrentTime()
		
		nResult = n2 - n1 
		
		--记录日志
		local strMsg = format("DML:<Error>x310160_GetValidTime n1=%d,n2=%d",n1,n2)
		WriteLog( 1, strMsg )	
		
	end
	
	return n2
end

----------------------------------------------------------------------------------------------
--取得有效的小时分钟
----------------------------------------------------------------------------------------------
function x310160_GetValidTimeHourMin()

	local h,m,s = GetHourMinSec()	
	return h,m

end