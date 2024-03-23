x310163_g_scriptId 		= 310163

--灯谜信息
x310163_g_DengmiInfo	= {
							{index=1,npcID=-1,GUID = 141506,Done=0},
							{index=2,npcID=-1,GUID = 141507,Done=0},
							{index=3,npcID=-1,GUID = 141508,Done=0},
							{index=4,npcID=-1,GUID = 141509,Done=0},
						  }
						  
--灯谜编号
x310163_g_DengmiNoMD	= {
							MD_DENGMI_NO1,
							MD_DENGMI_NO2,
							MD_DENGMI_NO3,
							MD_DENGMI_NO4,
						  }



--灯谜时间信息
x310163_g_DengmiTimer	= { nStart = -1,nIndex = -1 }
x310163_g_DengmiArray 	= {}

--出题相关

x310163_g_GameId		= 1007			--玩法ID
x310163_g_LimitLevel	= 40			--最低级别
x310163_g_LimitSceneId	= 0				--玩法所在场景，必须是在玩法场景，否则一切响应皆为非法


x310163_g_GameID_Right	= 961
x310163_g_GameID_Error	= 962


----------------------------------------------------------------------------------------------
--以下奖励相关信息
----------------------------------------------------------------------------------------------
--经验，声望，现银
x310163_g_ExpBonus		= 500	--奖励经验 公式=level*exp
x310163_g_ExpBonus1		= 650 --奖励经验 公式=level*exp
x310163_g_ShengWang		= 0			--奖励声望，固定值
x310163_g_MoneyBonus	= 15	--奖励现银，公式=level*money

--随机物品
x310163_g_ItemRate		= 25			--掉落概率
x310163_g_ItemList		= { 			--物品列表
							{12030107,1}			
						  }

--当有某个任务时的奖励信息
x310163_g_MissionGL		= 50			--掉落概率
x310163_g_MissionId		= 9315			--任务ID
x310163_g_MissionBonus	= 13015012		--掉落奖励

----------------------------------------------------------------------------------------------
--检查有效性
----------------------------------------------------------------------------------------------
function x310163_CheckValid( sceneId,selfId)

	local level = GetLevel(sceneId,selfId)
	if level<x310163_g_LimitLevel then
		return -1
	end
	
	if sceneId ~= x310163_g_LimitSceneId then
		return -2
	end
	
	return 1

end

----------------------------------------------------------------------------------------------
--检查启动时间是否有效
----------------------------------------------------------------------------------------------
function x310163_IsStartTimeValid()
	local h,m = x310163_GetValidTimeHourMin()
	
	local cur  = h*60  + m
	local from = 19*60 + 30
	local to   = 24*60 + 00
	if cur < from or cur > to then
		
		--记日志
		local strMsg = format("DML:<Info>x310163_IsStartTimeValid starttime invalid started  h=%d,m=%d", h, m )
    	WriteLog( 1, strMsg )
		return 0
	end
	
	return 1

end





----------------------------------------------------------------------------------------------
--判断玩家猜灯谜是否次数已满
----------------------------------------------------------------------------------------------
function x310163_IsPlayerGamingFull( sceneId,selfId )

	local nDate   = GetQuestData(sceneId,selfId,MD_QUEST_DENGMI_DATE[1], MD_QUEST_DENGMI_DATE[2], MD_QUEST_DENGMI_DATE[3] )
	local nCount  = GetQuestData(sceneId,selfId,MD_QUEST_DENGMI_COUNT[1],MD_QUEST_DENGMI_COUNT[2],MD_QUEST_DENGMI_COUNT[3])

	local nCurDay = GetDayOfYear()
	if nCurDay == nDate then
		if nCount >= x310163_g_MaxCount then
			return 1
		end
	end

	return 0
end

----------------------------------------------------------------------------------------------
--查找NPC
----------------------------------------------------------------------------------------------
function x310163_FindNpc(sceneId,npcId)
	
	for n,item in x310163_g_DengmiInfo do
		if npcId == item.npcID then
			return n
		end
	end
	
	return -1
							
end

----------------------------------------------------------------------------------------------
--检查并且重置数据
----------------------------------------------------------------------------------------------
function x310163_SaveDateMD( sceneId,selfId,nCurDay )

	SetQuestData(sceneId,selfId,MD_DENGMI_DATE[1],MD_DENGMI_DATE[2],MD_DENGMI_DATE[3],nCurDay)

end

----------------------------------------------------------------------------------------------
--给奖励，答对的情况下，25%机率给藏宝图
----------------------------------------------------------------------------------------------
function x310163_GiveJewMap( sceneId,selfId )
	local name = GetName(sceneId,selfId)
	local buff 	=	9011
	local buff1 =	9013
	local buff2 =	9012
	if name == nil then
		name = "Error"
	end
	local nItemCount = getn(x310163_g_ItemList)
	if nItemCount > 0 and x310163_g_ItemRate > 0  then

		--随机是否可以获得物品
		local bGet = random(1,100)
		if bGet <= x310163_g_ItemRate then
			
			--随机获得的物品
			local nGetItem = random(1,nItemCount)
			
			local itemInfo = x310163_g_ItemList[nGetItem]
			
			BeginAddItem(sceneId)
			if IsHaveSpecificImpact( sceneId, selfId, buff) == 1 or IsHaveSpecificImpact( sceneId, selfId, buff1) == 1  or IsHaveSpecificImpact( sceneId, selfId, buff2) == 1 then
            	AddItem( sceneId, itemInfo[1],itemInfo[2] )
            else
            	AddBindItem( sceneId, itemInfo[1],itemInfo[2] )
            end
            local ret = EndAddItem(sceneId,selfId)
            if ret > 0 then
            	
                AddItemListToPlayer(sceneId,selfId)
                
--                local msg = format("#Y您获得了#G@item_%d#Y的奖励",itemInfo[1],itemInfo[2])
--				LuaScenceM2Player(sceneId, selfId, msg, name , 2,1)
--		       	LuaScenceM2Player(sceneId, selfId, msg, name , 3,1)
--		       	LuaAllScenceM2Wrold( sceneId, format( "#G真是幸运！#Y%s#G在猜灯谜中意外获得了一张#R藏宝图#G！", name ), 1, 1)
		    else
		    	LuaScenceM2Player(sceneId, selfId, "#cffcf00物品栏已满，无法得到奖励物品！", name , 2,1)
		        LuaScenceM2Player(sceneId, selfId, "#cffcf00物品栏已满，无法得到奖励物品！", name , 3,1)
            end
		end
	end
end
----------------------------------------------------------------------------------------------
--给奖励，答对的情况下，才会触发 multi为score
----------------------------------------------------------------------------------------------

function x310163_GetBonusExp( sceneId,selfId )

	--活动未开启
	if GetGameOpenById(x310163_g_GameId) ~= 1 then
		return
	end
	
	--检查玩家有效性
	if x310163_CheckValid( sceneId,selfId ) ~= 1 then
		return
	end
	
	local score = x310163_GetDengmiScore( sceneId ,selfId)
	local level = GetLevel(sceneId,selfId)
	return level*350*score
end


function x310163_GiveBonus( sceneId,selfId, multi )

	--活动未开启
	if GetGameOpenById(x310163_g_GameId) ~= 1 then
		return
	end
	
	--检查玩家有效性
	if x310163_CheckValid( sceneId,selfId ) ~= 1 then
		return
	end
	
	local level = GetLevel(sceneId,selfId)
	return level*875*multi
	
--	local level = GetLevel(sceneId,selfId)
--	local name = GetName(sceneId,selfId)
--	if name == nil then
--		name = "ErrorName"
--	end
--	
--	local bonusExp = 0
--	--给经验
--	if x310163_g_ExpBonus > 0 then
--		local level = GetLevel(sceneId,selfId)
--		if level <70 then
--			bonusExp = level*x310163_g_ExpBonus * multi
--			AddExp(sceneId,selfId,bonusExp)
--			
--			local msg = format("您获得了%d点经验值的奖励",bonusExp)
--			
--			--LuaScenceM2Player(sceneId, selfId, msg, name , 2,1)
--	        --LuaScenceM2Player(sceneId, selfId, msg, name , 3,1)
--		else
--			bonusExp = level*x310163_g_ExpBonus1*multi
--			AddExp(sceneId,selfId,bonusExp)
--					
--			local msg = format("您获得了%d点经验值的奖励",bonusExp)
--			
--			--LuaScenceM2Player(sceneId, selfId, msg, name , 2,1)
--	    	--LuaScenceM2Player(sceneId, selfId, msg, name , 3,1)
--	  	end
--	end
--	
--	--给声望
--	if x310163_g_ShengWang > 0 then
--		local bonusShengWang = GetShengWang( sceneId,selfId) + x310163_g_ShengWang
--		SetShengWang( sceneId,selfId,bonusShengWang)
--		
--		local msg = format("您获得了%d点声望值的奖励",x310163_g_ShengWang*multi)
--		
--		LuaScenceM2Player(sceneId, selfId, msg, name , 2,1)
--        LuaScenceM2Player(sceneId, selfId, msg, name , 3,1)
--	end
--	
--	--给现银
--	if x310163_g_MoneyBonus > 0 then
--		local bonusMoney = level*x310163_g_MoneyBonus*multi
--		local buff 	=	9011
--		local buff1 =	9013
--		if IsHaveSpecificImpact( sceneId, selfId, buff) == 1 or IsHaveSpecificImpact( sceneId, selfId, buff1) == 1 then
--			AddMoney(sceneId,selfId,0,bonusMoney,x310163_g_scriptId)
--		else
--			AddMoney(sceneId,selfId,1,bonusMoney,x310163_g_scriptId)
--		end
--	end
--	
--	
--	-- 添加一枚大都嘉年华娱乐币
--    BeginAddItem( sceneId)
--    AddItem( sceneId, 11990117, 1)
--    if EndAddItem( sceneId, selfId) <= 0 then
--        Msg2Player( sceneId, selfId, "你的背包已满，无法获得#{_ITEM11990117}奖励。", 8, 2)
--    else
--        AddItemListToPlayer( sceneId, selfId)
--    end
--	--给任务物品
--	if IsHaveQuestNM( sceneId, selfId, x310163_g_MissionId) == 1 then
--		
--		--判断任务是否完成
--		local misIndex = GetQuestIndexByID(sceneId,selfId,x310163_g_MissionId)
--		if misIndex < 0 then
--			return
--		end
--		
--		--任务完成，返回
--		if GetQuestParam( sceneId,selfId,misIndex,7) == 1 then
--			return
--		end
--		
--		--给奖励
--		local bGet = random(1,100)
--		if bGet <= x310163_g_MissionGL then
--			
--			BeginAddItem(sceneId)
--            AddItem( sceneId, x310163_g_MissionBonus,1 )
--            local ret = EndAddItem(sceneId,selfId)
--            if ret > 0 then
--                AddItemListToPlayer(sceneId,selfId)
--                
--                --这个不用给提示，任务脚本会给出相关提示
--		    else
--		    	LuaScenceM2Player(sceneId, selfId, "#cffcf00物品栏已满，无法得到任务物品！", name , 2,1)
--		        LuaScenceM2Player(sceneId, selfId, "#cffcf00物品栏已满，无法得到任务物品！", name , 3,1)
--            end
--		end
--	end
--	
--	return bonusExp
end

----------------------------------------------------------------------------------------------
--枚举
----------------------------------------------------------------------------------------------
function x310163_ProcEnumEvent( sceneId, selfId, targetId, MissionId )


	if GetGameOpenById(x310163_g_GameId) ~= 1 then
		return
	end
	
	
	
	local md = GetQuestData(sceneId,selfId,MD_DENGMI_NO1[1],MD_DENGMI_NO1[2],MD_DENGMI_NO1[3])
	
    AddQuestNumText(sceneId,x310163_g_scriptId,"我要猜灯谜",3,x310163_g_scriptId)
        
    
    x310163_InitDengmiArray( sceneId, selfId)
end

----------------------------------------------------------------------------------------------
--添加灯谜答案选项
----------------------------------------------------------------------------------------------
function x310163_AddDengmiAnswerOption( sceneId,strAnswer1,strAnswer2,strAnswer3,strAnswer4)

	--随机添加选项
	local arr_answer = { {strAnswer1,11001,0},{strAnswer2,11002,0},{strAnswer3,11003,0},{strAnswer4,11004,0} }
	for i=1,4 do
		
		local nCount = getn(arr_answer)
		local n = random(1,nCount)
		while arr_answer[n][3] == 1 do
			n = random(1,nCount)
		end
		
		arr_answer[n][3] = 1
		
		AddQuestNumText(sceneId,x310163_g_scriptId,arr_answer[n][1],3,arr_answer[n][2] )
	end
	
end

----------------------------------------------------------------------------------------------
--获点灯谜积分
----------------------------------------------------------------------------------------------
function x310163_SetDengmiScore( sceneId ,selfId, score)
	SetQuestData(sceneId,selfId,MD_DENGMI_SCORE[1],MD_DENGMI_SCORE[2],MD_DENGMI_SCORE[3],score)
end

function x310163_SetDengmiScoreInc( sceneId ,selfId, scoreInc)
	local score = GetQuestData(sceneId,selfId,MD_DENGMI_SCORE[1],MD_DENGMI_SCORE[2],MD_DENGMI_SCORE[3])
	SetQuestData(sceneId,selfId,MD_DENGMI_SCORE[1],MD_DENGMI_SCORE[2],MD_DENGMI_SCORE[3],score + scoreInc)
end
----------------------------------------------------------------------------------------------
--获点灯谜积分
----------------------------------------------------------------------------------------------
function x310163_GetDengmiScore( sceneId ,selfId)
	local score = GetQuestData(sceneId,selfId,MD_DENGMI_SCORE[1],MD_DENGMI_SCORE[2],MD_DENGMI_SCORE[3])
	return score
end
----------------------------------------------------------------------------------------------
--此NPC是否答过
----------------------------------------------------------------------------------------------
function x310163_NPCIsVisited( sceneId ,selfId, NPCindex)
	local Is = 0
	if NPCindex == 1 then
		Is = GetQuestData(sceneId,selfId,MD_DENGMI_NPC1[1],MD_DENGMI_NPC1[2],MD_DENGMI_NPC1[3])
	elseif NPCindex == 2 then
		Is = GetQuestData(sceneId,selfId,MD_DENGMI_NPC2[1],MD_DENGMI_NPC2[2],MD_DENGMI_NPC2[3])
	elseif NPCindex == 3 then
		Is = GetQuestData(sceneId,selfId,MD_DENGMI_NPC3[1],MD_DENGMI_NPC3[2],MD_DENGMI_NPC3[3])
	elseif NPCindex == 4 then
		Is = GetQuestData(sceneId,selfId,MD_DENGMI_NPC4[1],MD_DENGMI_NPC4[2],MD_DENGMI_NPC4[3])
	end
	return Is
end
----------------------------------------------------------------------------------------------
--设置此NPC答过
----------------------------------------------------------------------------------------------
function x310163_SetNPCVisited( sceneId ,selfId, NPCindex)
	if NPCindex == 1 then
		SetQuestData(sceneId,selfId,MD_DENGMI_NPC1[1],MD_DENGMI_NPC1[2],MD_DENGMI_NPC1[3],1)
	elseif NPCindex == 2 then
		SetQuestData(sceneId,selfId,MD_DENGMI_NPC2[1],MD_DENGMI_NPC2[2],MD_DENGMI_NPC2[3],1)
	elseif NPCindex == 3 then
		SetQuestData(sceneId,selfId,MD_DENGMI_NPC3[1],MD_DENGMI_NPC3[2],MD_DENGMI_NPC3[3],1)
	elseif NPCindex == 4 then
		SetQuestData(sceneId,selfId,MD_DENGMI_NPC4[1],MD_DENGMI_NPC4[2],MD_DENGMI_NPC4[3],1)
	end

end

----------------------------------------------------------------------------------------------
--设置此NPC答过
----------------------------------------------------------------------------------------------
function x310163_ResetDengmiMD( sceneId ,selfId)

	SetQuestData(sceneId,selfId,MD_DENGMI_SCORE[1],MD_DENGMI_SCORE[2],MD_DENGMI_SCORE[3],0)
	SetQuestData(sceneId,selfId,MD_DENGMI_NPC1[1],MD_DENGMI_NPC1[2],MD_DENGMI_NPC1[3],0)
	SetQuestData(sceneId,selfId,MD_DENGMI_NPC2[1],MD_DENGMI_NPC2[2],MD_DENGMI_NPC2[3],0)
	SetQuestData(sceneId,selfId,MD_DENGMI_NPC3[1],MD_DENGMI_NPC3[2],MD_DENGMI_NPC3[3],0)
	SetQuestData(sceneId,selfId,MD_DENGMI_NPC4[1],MD_DENGMI_NPC4[2],MD_DENGMI_NPC4[3],0)
	
end
----------------------------------------------------------------------------------------------
--设置此NPC答过
----------------------------------------------------------------------------------------------
function x310163_SetDengmiMD( sceneId ,selfId,NPCindex)
	if NPCindex == 1 then
		SetQuestData(sceneId,selfId,MD_DENGMI_NPC1[1],MD_DENGMI_NPC1[2],MD_DENGMI_NPC1[3],1)
	elseif NPCindex == 2 then
		SetQuestData(sceneId,selfId,MD_DENGMI_NPC2[1],MD_DENGMI_NPC2[2],MD_DENGMI_NPC2[3],1)
	elseif NPCindex == 3 then
		SetQuestData(sceneId,selfId,MD_DENGMI_NPC3[1],MD_DENGMI_NPC3[2],MD_DENGMI_NPC3[3],1)
	elseif NPCindex == 4 then
		SetQuestData(sceneId,selfId,MD_DENGMI_NPC4[1],MD_DENGMI_NPC4[2],MD_DENGMI_NPC4[3],1)
	end

end
----------------------------------------------------------------------------------------------
--初始化题库
----------------------------------------------------------------------------------------------
function x310163_InitDengmiArray( sceneId ,selfId)
	local nDate   = GetQuestData(sceneId,selfId,MD_DENGMI_DATE[1], MD_DENGMI_DATE[2], MD_DENGMI_DATE[3] )
	local nCurDay = GetDayOfYear()
	
	local accDay = x310163_GetAcceptDate( sceneId ,selfId)
	local nCount = QuestDengmi_GetQuestionCount()
	for i,item in x310163_g_DengmiInfo do
		--if item.nDengmi == nil or nDate ~= nCurDay then
		local md = x310163_g_DengmiNoMD[i]
		
		local md1 = GetQuestData(sceneId,selfId,MD_DENGMI_NO1[1],MD_DENGMI_NO1[2],MD_DENGMI_NO1[3])
		local no = GetQuestData(sceneId,selfId,md[1],md[2],md[3]) 
		if no == 0 or accDay ~= nCurDay then 
			local DengmiNo = random(0,nCount-1)
			item.nDengmi = DengmiNo

			
			local id,strDesc,strAnswer1,strAnswer2,strAnswer3,strAnswer4,nAnswer = QuestDengmi_GetQuestionInfo(item.nDengmi)
			
			x310163_g_DengmiArray[DengmiNo] = {}		
			x310163_g_DengmiArray[DengmiNo].id = id + 100000		
			x310163_g_DengmiArray[DengmiNo].strDesc = strDesc
			x310163_g_DengmiArray[DengmiNo].strAnswer1 = strAnswer1
			x310163_g_DengmiArray[DengmiNo].strAnswer2 = strAnswer2
			x310163_g_DengmiArray[DengmiNo].strAnswer3 = strAnswer3
			x310163_g_DengmiArray[DengmiNo].strAnswer4 = strAnswer4
			x310163_g_DengmiArray[DengmiNo].nAnswer = nAnswer + 11000
			SetQuestData(sceneId,selfId,md[1],md[2],md[3], DengmiNo) 
			
		end
		
	end
end	
	

function x310163_IsDengmiFinish( sceneId ,selfId)
	local npc1 = GetQuestData(sceneId,selfId,MD_DENGMI_NPC1[1],MD_DENGMI_NPC1[2],MD_DENGMI_NPC1[3])
	local npc2 = GetQuestData(sceneId,selfId,MD_DENGMI_NPC2[1],MD_DENGMI_NPC2[2],MD_DENGMI_NPC2[3])
	local npc3 = GetQuestData(sceneId,selfId,MD_DENGMI_NPC3[1],MD_DENGMI_NPC3[2],MD_DENGMI_NPC3[3])
	local npc4 = GetQuestData(sceneId,selfId,MD_DENGMI_NPC4[1],MD_DENGMI_NPC4[2],MD_DENGMI_NPC4[3])
	
	if npc1==1 and npc2==1 and npc3==1 and npc4==1 then
		return 1
	end
	return 0
end
----------------------------------------------------------------------------------------------
--脚本默认事件
----------------------------------------------------------------------------------------------
function x310163_ProcEventEntry( sceneId ,selfId, npcId,idScript,idExt )
	----------------------------------------------------------------------------------------------
	--活动未开启
	----------------------------------------------------------------------------------------------
	
	if GetGameOpenById(x310163_g_GameId) ~= 1 then
		
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
	if x310163_CheckValid( sceneId,selfId ) ~= 1 then
		return
	end
	
	if IsHaveQuest(sceneId,selfId, x310163_g_MissionId) <= 0 then
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"\t请先去找【灯谜使官】蔡德楚领取灯谜会任务。\n\t#G（每天晚上的19：30--24：00大都天坛附近【灯谜使官】蔡德楚发布大都灯谜会任务）")				
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,npcId)
		return 
	end
	----------------------------------------------------------------------------------------------
	--当活动没有开始的时候，不允许进行相关其他操作
	----------------------------------------------------------------------------------------------
	if x310163_IsStartTimeValid( sceneId,selfId ) ~= 1 then
		

		
		--给出相关提示
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"\t灯谜会还没开始呢，别心急。\n\t#G（每天晚上的19：30--24：00灯谜会开放）")				
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,npcId)
		return
	end
	
	local nDate   = GetQuestData(sceneId,selfId,MD_DENGMI_DATE[1], MD_DENGMI_DATE[2], MD_DENGMI_DATE[3] )
	local nCurDay = GetDayOfYear()
	if nDate == nCurDay then
		if x310163_IsDengmiFinish( sceneId ,selfId) == 1 then
			--给出相关提示
			BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"\t你已经完成了今天的大都灯谜会，请明天再来。")				
			EndQuestEvent(sceneId)
			DispatchQuestEventList(sceneId,selfId,npcId)
			
			return
		end
		
	--else
		--x310163_SaveDateMD( sceneId,selfId,nCurDay )
		--x310163_ResetDengmiMD(sceneId,selfId)
	end
	----------------------------------------------------------------------------------------------
	--隔天了
	----------------------------------------------------------------------------------------------

	for i,item in x310163_g_DengmiInfo do
		item.npcID = FindMonsterByGUID(sceneId,item.GUID)
	end
	
	
	local nFind = x310163_FindNpc(sceneId,npcId)
	local name = GetName(sceneId,selfId)
	if name == nil then
		name = "Error"
	end
	
	if idExt == x310163_g_scriptId then
		----------------------------------------------------------------------------------------------
		--开始猜谜
		----------------------------------------------------------------------------------------------
		if x310163_NPCIsVisited( sceneId ,selfId, nFind) == 1 then
			BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"\t你今天已经猜过我的灯谜了，请去其他姐妹处完成大都灯谜会。\n\t#G(4个灯谜侍女分别在大都内部东南、西南、东北、西北四个方位内移动。)")				
			EndQuestEvent(sceneId)
			DispatchQuestEventList(sceneId,selfId,npcId)
			
			return
		end
		--在答题库中定位索引
			
		local MD = x310163_g_DengmiNoMD[nFind]
		
		local DengmiNo = GetQuestData(sceneId,selfId,MD[1],MD[2],MD[3])
		local dm = x310163_g_DengmiArray[DengmiNo]
		
		--设置npcid和答题编号

		
		--更新对话框内容
		BeginQuestEvent(sceneId)
			
		AddQuestText(sceneId,dm.strDesc)
		x310163_AddDengmiAnswerOption( sceneId, dm.strAnswer1, dm.strAnswer2, dm.strAnswer3, dm.strAnswer4 )
										
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,npcId)
			
	elseif idExt >= 11001 and idExt <= 11004 then
		
		----------------------------------------------------------------------------------------------
		--玩家选中的某个答题
		----------------------------------------------------------------------------------------------
		if x310163_NPCIsVisited( sceneId ,selfId, nFind) == 1 then
			BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"\t你今天已经猜过我的灯谜了，请去其他姐妹处完成大都灯谜会。\n\t#G(4个灯谜侍女分别在大都内部东南、西南、东北、西北四个方位内移动。)")				
			EndQuestEvent(sceneId)
			DispatchQuestEventList(sceneId,selfId,npcId)
			return
		end
		x310163_SetNPCVisited(sceneId ,selfId, nFind)
			
		
	--	local dm = x310163_g_DengmiArray[nFind]
		local MD = x310163_g_DengmiNoMD[nFind]
		
		local DengmiNo = GetQuestData(sceneId,selfId,MD[1],MD[2],MD[3])
		local dm = x310163_g_DengmiArray[DengmiNo]
		
		
		if dm.nAnswer == idExt then
			--答对了

			
			--相关提示
			local name = GetName(sceneId,selfId)
			LuaScenceM2Player( sceneId,selfId,"\t恭喜你猜对了灯谜",name,3,1)
			LuaScenceM2Player( sceneId,selfId,"\t恭喜你猜对了灯谜",name,2,1)
			LuaScenceM2Player( sceneId,selfId,"\t你获得了5点灯谜积分",name,3,1)
			LuaScenceM2Player( sceneId,selfId,"\t你获得了5点灯谜积分",name,2,1)
			x310163_SetDengmiScoreInc(sceneId,selfId,5)
			--更新对话框内容
			BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"\t恭喜你猜对了灯谜，获得#R5点#W灯谜积分。" )
				if x310163_IsDengmiFinish( sceneId ,selfId) == 1 then
					local score,bonusExp = x310163_OnDengmiFinish(sceneId ,selfId)
					local strMsg = format("\t您今天获得的灯谜积分是：#R%d分#W，奖励给您#R%d经验#W欢迎您明天再来",score, bonusExp)
					local strMsg = "\t您今天完成了灯谜，欢迎您明天再来，先交任务"
					AddQuestText(sceneId,strMsg)
				else
					AddQuestText(sceneId,"\t请前往其他姐妹那里继续猜灯谜。\n\t#G(4个灯谜侍女分别在大都内部东南、西南、东北、西北四个方位内移动。)" )
				end
			EndQuestEvent(sceneId)
			
			DispatchQuestEventList(sceneId,selfId,npcId)
		
			x310163_GiveJewMap(sceneId,selfId)
			
			--给奖励
			--x310163_GiveBonus( sceneId,selfId )
			--CallScriptFunction( 256224, "Finishdengmi", sceneId, selfId)	
			
			--添加玩法日志
			GamePlayScriptLog( sceneId, selfId, x310163_g_GameID_Right)
			 
			 --记录日志
			local name = GetName(sceneId,selfId)
			if name == nil then
				name = "Error"
			end
		else
			--答错了
			--相关提示
			local name = GetName(sceneId,selfId)
			LuaScenceM2Player( sceneId,selfId,"\t很遗憾，你猜错了",name,3,1)
			LuaScenceM2Player( sceneId,selfId,"\t很遗憾，你猜错了",name,2,1)
			LuaScenceM2Player( sceneId,selfId,"\t你获得了1点灯谜积分",name,3,1)
			LuaScenceM2Player( sceneId,selfId,"\t你获得了1点灯谜积分",name,2,1)
			x310163_SetDengmiScoreInc(sceneId,selfId,1)
			--更新对话框内容
			BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"\t很遗憾你猜错了灯谜，获得了#R1点#W灯谜积分。")	
				if x310163_IsDengmiFinish( sceneId ,selfId) == 1 then
					--local score,bonusExp = x310163_OnDengmiFinish(sceneId ,selfId)
					--local strMsg = format("\t您今天获得的灯谜积分是：#R%d分#W，奖励给您#R%d经验#W欢迎您明天再来",score, bonusExp)
					--AddQuestText(sceneId,strMsg)
				else
					AddQuestText(sceneId,"\t请前往其他姐妹那里继续猜灯谜。\n\t#G(4个灯谜侍女分别在大都内部东南、西南、东北、西北四个方位内移动。)" )
				end			
			EndQuestEvent(sceneId)
			DispatchQuestEventList(sceneId,selfId,npcId)
			
			
			--添加玩法日志
			GamePlayScriptLog( sceneId, selfId, x310163_g_GameID_Error)
			
			--记录日志
			local name = GetName(sceneId,selfId)
			if name == nil then
				name = "Error"
			end
			
			if x310163_IsDengmiFinish( sceneId ,selfId) == 1 then
				--x310163_OnDengmiFinish(sceneId ,selfId)
			end
		
		end	
		
		CallScriptFunction( 310164, "OnMissionStep", sceneId, selfId, x310163_g_DengmiInfo[nFind].GUID)	
		
		
	end
		

end
----------------------------------------------------------------------------------------------
--得到接受任务日期
----------------------------------------------------------------------------------------------
function x310163_GetAcceptDate( sceneId,selfId )
	local misIndex = GetQuestIndexByID( sceneId, selfId, x310163_g_MissionId)
	return GetQuestParam( sceneId, selfId, misIndex, 6)
end

function x310163_OnDengmiFinish(sceneId ,selfId)
	local name = GetName(sceneId,selfId)
	if name == nil then
		name = "Error"
	end
			
	--local score = x310163_GetDengmiScore(sceneId ,selfId)

	--local bonusExp = x310163_GiveBonus( sceneId,selfId, score )
	--local bonusExp = x310163_GiveBonus( sceneId,selfId, score )
	local score = x310163_GetDengmiScore(sceneId ,selfId)
	local exp = x310163_GetBonusExp(sceneId ,selfId)
	local strMsg = format("您今天获得的灯谜积分是：%d分，奖励给您%d经验，欢迎您明天再来！",score, exp)
	
	--LuaScenceM2Player( sceneId,selfId,strMsg,name,3,1)
	--LuaScenceM2Player( sceneId,selfId,strMsg,name,2,1)
	
	return score,exp
	
end

function x310163_ProcAcceptCheck( sceneId, selfId, NPCId )
    return 0
end

----------------------------------------------------------------------------------------------
--接受
----------------------------------------------------------------------------------------------
function x310163_ProcAccept( sceneId, selfId )
end

----------------------------------------------------------------------------------------------
--放弃
----------------------------------------------------------------------------------------------
function x310163_ProcQuestAbandon( sceneId, selfId, MissionId )
end

----------------------------------------------------------------------------------------------
--继续
----------------------------------------------------------------------------------------------
function x310163_OnContinue( sceneId, selfId, targetId )
end

----------------------------------------------------------------------------------------------
--检测是否可以提交
----------------------------------------------------------------------------------------------
function x310163_CheckSubmit( sceneId, selfId )
end

----------------------------------------------------------------------------------------------
--提交
----------------------------------------------------------------------------------------------
function x310163_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end

----------------------------------------------------------------------------------------------
--杀死怪物或玩家
----------------------------------------------------------------------------------------------
function x310163_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end

----------------------------------------------------------------------------------------------
--进入区域事件
----------------------------------------------------------------------------------------------
function x310163_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

----------------------------------------------------------------------------------------------
--道具改变
----------------------------------------------------------------------------------------------
function x310163_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end

----------------------------------------------------------------------------------------------
--取得有效的时间,在这里，做时间检查，如果两次取时间的差超过5秒或者小于0，则认定无效，重新取
--帮会战曾在取时间的问题上出过错，所以在这里做相同的检查
----------------------------------------------------------------------------------------------
function x310163_GetValidTime()

	local n1 = GetCurrentTime()
	local n2 = GetCurrentTime()
	
	local nResult = n2 - n1 
	while nResult > 5 or nResult < 0 do
		n1 = GetCurrentTime()
		n2 = GetCurrentTime()
		
		nResult = n2 - n1 
		
		--记录日志
		local strMsg = format("DML:<Error>x310163_GetValidTime n1=%d,n2=%d",n1,n2)
		WriteLog( 1, strMsg )	
		
	end
	
	return n2
end

----------------------------------------------------------------------------------------------
--取得有效的小时分钟
----------------------------------------------------------------------------------------------
function x310163_GetValidTimeHourMin()

	local h,m,s = GetHourMinSec()	
	return h,m

end