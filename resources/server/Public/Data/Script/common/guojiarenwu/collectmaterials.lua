--【主线】收集材料
--MD_SHOUJI_MATERIAL_DATE						--收集材料 接任务日期
--MD_SHOUJI_MATERIAL_COUNT          --收集材料当日计数器
--MD_SHOUJI_MATERIAL_CYCLE					--收集材料 环数
--MD_SHOUJI_MATERIAL_CYCLECOUNT			--收集材料 该环次数

--MisDescBegin
x300517_g_ScriptId = 300517
x300517_g_MissionIdPre =-1
x300517_g_MissionId = 8053
x300517_g_LevelLess	= 	30 
x300517_g_Name	={}
x300517_g_MissionName="【个人】收集材料"	
x300517_g_MissionCompleted="\t年轻人，你做的相当不错！给，这是你应得的报酬。"					--完成任务npc说话的话
x300517_g_Mis_Count   = 1								--每天可做的次数
x300517_g_Mis_CollectCount   = 1				--收集材料个数
x300517_g_MaxSigleCycle_Count   = 4
x300517_g_LevelMod   = 10
x300517_g_BonusMoney1 =0
x300517_g_BonusMoney2 =0
x300517_g_BonusMoney3 =0
x300517_g_BonusMoney4 =0
x300517_g_BonusMoney5 =0
x300517_g_BonusMoney6 =0
x300517_g_BonusItem	=	{}
x300517_g_BonusChoiceItem ={}
x300517_g_ExpBonus = 60
x300517_g_ItemMinBonus = 2
x300517_g_ItemMaxBonus = 4
x300517_g_NpcGUID ={}

x300517_g_MissionHelp = "\t#W该任务十环为一轮，每天只能完成一轮。在任务中，也许材料收集人会#G多次向你收集同一物品#W，满足他的需求，你将会获得丰厚的奖励。\n\t#G如果你放弃了任务，当天无法再次领取收集材料任务了。"


x300517_g_MissionTable =    {
                                { maxLevel = 40,  item = {11020001,11020002,11030001}},
                                { maxLevel = 50,  item = {11020001,11020002,11030001,11020006,11020007}},
                                { maxLevel = 60,  item = {11020001,11020002,11030001,11020006,11020007,11020010,11020011,11030003}},
                                { maxLevel = 70,  item = {11020006,11020007,11020010,11020011,11030003,11020014,11020015,11030005}},
                                { maxLevel = 80,  item = {11020006,11020007,11020010,11020011,11030003,11020014,11020015,11030005,11030007}},
                                { maxLevel = 90,  item = {11020006,11020007,11020010,11020011,11030003,11020014,11020015,11030005,11030007}},
                                { maxLevel = 100, item = {11020006,11020007,11020010,11020011,11030003,11020014,11020015,11030005,11030007}},
                                { maxLevel = 110, item = {11020006,11020007,11020010,11020011,11030003,11020014,11020015,11030005,11030007}},
                                { maxLevel = 120, item = {11020006,11020007,11020010,11020011,11030003,11020014,11020015,11030005,11030007}},
                                { maxLevel = 130, item = {11020006,11020007,11020010,11020011,11030003,11020014,11020015,11030005,11030007}},
                                { maxLevel = 140, item = {11020006,11020007,11020010,11020011,11030003,11020014,11020015,11030005,11030007}},
                                { maxLevel = 150, item = {11020006,11020007,11020010,11020011,11030003,11020014,11020015,11030005,11030007}},
                                { maxLevel = 160, item = {11020006,11020007,11020010,11020011,11030003,11020014,11020015,11030005,11030007}},                                
                            }     


x300517_g_ItemTable =    {
                                { maxLevel = 45,  item = 11050001},
                                { maxLevel = 66,  item = 11050002},
                                { maxLevel = 160, item = 11050003},                                
                            } 
--MisDescEnd
--**********************************
--列举任务
function x300517_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
	if IsQuestHaveDoneNM( sceneId, selfId, MissionId ) > 0 then
			return
	end
	if IsHaveQuestNM(sceneId,selfId, MissionId) <= 0 then
			if GetLevel(sceneId, selfId) >= x300517_g_LevelLess then
					local state = GetQuestStateNM(sceneId,selfId,NPCId,x300517_g_MissionId)
					AddQuestTextNM( sceneId, selfId, NPCId, x300517_g_MissionId, state, -1 )
			end
	else
			local state = GetQuestStateNM(sceneId,selfId,NPCId,x300517_g_MissionId)
			AddQuestTextNM( sceneId, selfId, NPCId, x300517_g_MissionId, state, -1 )
	end
end

--**********************************
--选中任务
function x300517_ProcEventEntry(sceneId, selfId, NPCId, MissionId)	--点击该任务后执行此脚本
	if IsQuestHaveDoneNM(sceneId, selfId, x300517_g_MissionId) > 0 then
		return 
	end
	if IsHaveQuestNM(sceneId,selfId, MissionId) > 0 then
			if x300517_CheckSubmit(sceneId, selfId, NPCId) <= 0 then
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x300517_g_MissionName)
						local itemdataId = x300517_GetCurrentItem(sceneId, selfId)
						local circlesCount = GetQuestData(sceneId, selfId, MD_SHOUJI_MATERIAL_CYCLECOUNT[1], MD_SHOUJI_MATERIAL_CYCLECOUNT[2], MD_SHOUJI_MATERIAL_CYCLECOUNT[3])
						local strText = format( "快去收集#G%d#W个#G@itemid_%d#W,，别担心，我会给你奖赏的。", circlesCount, itemdataId )
						AddQuestText(sceneId,strText)
						AddQuestText( sceneId,"\n#Y完成情况：")
						local itemcount = GetItemCount(sceneId,selfId,itemdataId);
						local MissionTarget = format( "收集#G@itemid_%d#W(%d/%d)", itemdataId , itemcount, circlesCount)
						AddQuestText(sceneId,MissionTarget)
						EndQuestEvent()
						DispatchQuestEventList(sceneId, selfId, NPCId, x300517_g_ScriptId, x300517_g_MissionId);
			else
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x300517_g_MissionName)
						AddQuestText(sceneId,x300517_g_MissionCompleted)
						AddQuestText(sceneId," ")
						x300517_DispatchMissionInfo( sceneId, selfId, NPCId, 1)
						EndQuestEvent()
						DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x300517_g_ScriptId, x300517_g_MissionId);
			end
  else
  		if  IsNpcHaveQuestNM(sceneId, selfId, NPCId, MissionId) == 1 then--这里判断npc身上是否有这个任务，否则会出bug
					if x300517_ProcAcceptCheck(sceneId, selfId, NPCId, MissionId) > 0 then
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x300517_g_MissionName)
						AddQuestText(sceneId,"\t我是太子殿下钦命的材料收集官，负责收集各种王国紧缺的材料。凡是上交材料者均有丰厚的赏赐。\n\t嗯，你是来贡献材料的吗？")
						AddQuestText( sceneId,"\n#G小提示：")
						AddQuestText(sceneId,x300517_g_MissionHelp)								
						local level = GetLevel(sceneId, selfId)
						local ExpBonus = x300517_g_ExpBonus*level*2
						AddQuestExpBonus(sceneId, ExpBonus )
		  			EndQuestEvent()
						DispatchQuestInfoNM(sceneId, selfId, NPCId, x300517_g_ScriptId, x300517_g_MissionId);
					end
			end
  end
end

--**********************************
--刷新任务跟踪
function x300517_ProcQuestLogRefresh( sceneId, selfId, MissionId)
	
	if MissionId == nil or MissionId < 0 then
		return
	end
	
	if IsHaveQuestNM(sceneId, selfId, MissionId) <= 0 then
		return
	end
	
	local ModNum = x300517_GetModNum(sceneId, selfId);
	local MissionName;
	MissionName = GetQuestNameNM(sceneId, selfId, MissionId);
	local maxcircle = x300517_GetMaxCircleNum(sceneId, selfId);
	local circle = GetQuestData(sceneId, selfId, MD_SHOUJI_MATERIAL_CYCLE[1], MD_SHOUJI_MATERIAL_CYCLE[2], MD_SHOUJI_MATERIAL_CYCLE[3])
	local circlesCount = GetQuestData(sceneId, selfId, MD_SHOUJI_MATERIAL_CYCLECOUNT[1], MD_SHOUJI_MATERIAL_CYCLECOUNT[2], MD_SHOUJI_MATERIAL_CYCLECOUNT[3])
	
	MissionName = MissionName.."("..circle;
	MissionName = MissionName.."/"..maxcircle;
	MissionName = MissionName..")";
	
	local itemdataId = x300517_GetCurrentItem(sceneId, selfId)
	local itemcount = GetItemCount(sceneId,selfId,itemdataId);
	
	local MissionTarget = format( "  收集#G@itemid_%d#W(%d/%d)", itemdataId , itemcount, circlesCount)
	if MissionTarget == nil then
		MissionTarget = "";
	end
	
	local MissionNPC = "@npc_138559"
	--MissionTitle, MissionName, MissionTarget, MissionNPC, MissionProcess, MissionComment, MissionTip
	
	local MissionProcess = format("你可以通过击败敌人或者与其他玩家交易获得#G@itemid_%d#W", itemdataId)
	local MissionComment = format("\t为了抵御外敌，我们需要更多的材料来进行基础建设。去收集#G@itemid_%d#W给我吧，我会给你奖励的。", itemdataId)
	x300517_QuestLogRefresh(sceneId, selfId, MissionId, "", MissionName, MissionTarget, MissionNPC, MissionProcess, MissionComment, x300517_g_MissionHelp);
end

--**********************************
--检查是否可接
function x300517_ProcAcceptCheck(sceneId, selfId, NPCId, MissionId)
	local level = GetLevel(sceneId,selfId);
	if ( level < x300517_g_LevelLess ) then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "您的等级不够，不能领取任务！");
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return 0;
	end
	
	local bHaveMission	= IsHaveQuestNM(sceneId, selfId, MissionId);
	if(bHaveMission > 0) then
		return 0;
	else
		if IsQuestFullNM(sceneId,selfId)==1 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"可接任务数量已满")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
		end
		local today = GetDayOfYear()
		local lastday = GetQuestData(sceneId, selfId, MD_SHOUJI_MATERIAL_DATE[1], MD_SHOUJI_MATERIAL_DATE[2], MD_SHOUJI_MATERIAL_DATE[3])
		if lastday ~= today then
			return 1
		end
		if x300517_IsAbdon(sceneId, selfId) > 0 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, "放弃任务后当天无法领取收集材料任务");
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
			return 0
		end
		local daycount =  GetQuestData(sceneId, selfId, MD_SHOUJI_MATERIAL_COUNT[1], MD_SHOUJI_MATERIAL_COUNT[2], MD_SHOUJI_MATERIAL_COUNT[3])
		if daycount >= x300517_g_Mis_Count then
			  BeginQuestEvent(sceneId)
				AddQuestText(sceneId, "收集材料任务一天只能做10次");
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				Msg2Player(sceneId, selfId, "收集材料任务一天只能做10次", 0, 2)
				return 0
		end
		return 1;
	end

end

--**********************************
--接任务
function x300517_ProcQuestAccept( sceneId, selfId, NPCId, MissionId )
		if IsHaveQuestNM(sceneId, selfId, MissionId) > 0 then
				return 
		end
		if IsQuestFullNM(sceneId, selfId) > 0 then
			return
		end
		
		--检查前置任务
		local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId,MissionId  )
		if FrontMissiontId1 ~= -1 then
			if IsQuestHaveDoneNM( sceneId, selfId, FrontMissiontId1 ) == 0 then
				return 
			end
		end
		if FrontMissiontId2 ~= -1 then
			if IsQuestHaveDoneNM( sceneId, selfId, FrontMissiontId2 ) == 0 then
				return
			end
		end
		if FrontMissiontId3 ~= -1 then
			if IsQuestHaveDoneNM( sceneId, selfId, FrontMissiontId3 ) == 0 then
				return
			end
		end
		
		local ret = QuestCheckAcceptNM( sceneId, selfId, NPCId, MissionId ) -- 获取接受任务检查信息
		if ret > 0 then -- 如果可以接这个任务
			if x300517_ProcAcceptCheck(sceneId, selfId, NPCId, MissionId) > 0 then
				if DelQuest(sceneId, selfId, x300517_g_MissionId) > 0 then
						if  IsNpcHaveQuestNM(sceneId, selfId, NPCId, MissionId) == 1 then--这里判断npc身上是否有这个任务，否则会出bug
								if x300517_ProcAcceptCheck(sceneId, selfId, NPCId, MissionId) > 0 then
									BeginQuestEvent(sceneId)
						  		local itemdataId = x300517_GetRandItem(sceneId, selfId)
						  		x300517_AcceptThisCycle(sceneId, selfId)
						  		if AddQuest( sceneId, selfId, x300517_g_MissionId, x300517_g_ScriptId, 0, 0, 1) > 0 then
										x300517_SetCurrentItem(sceneId, selfId, itemdataId)
							 			x300517_Msg2toplayer( sceneId, selfId,0)
							  		xx300517_DisplayCircleMessage(sceneId, selfId, MissionId)
										AddQuestText(sceneId,"#Y"..x300517_g_MissionName)
										local strText = format( "\t嗯，我看看，我们现在很需要#G@itemid_%d#W，收集给我吧，我会给你奖励的。", itemdataId )
										AddQuestText(sceneId,strText)
										AddQuestText( sceneId,"\n#Y任务目标：")
										strText = format( "收集一个#G@itemid_%d#W", itemdataId )
										if strText == nil then
											strText = "";
										end
										AddQuestText( sceneId,strText)
						  			EndQuestEvent()
										DispatchQuestEventList(sceneId, selfId, NPCId, x300517_g_ScriptId, x300517_g_MissionId);
										x300517_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
									end
								end
						end
				end
		 	end                                                                    
	  end
end

--**********************************
function xx300517_DisplayCircleMessage(sceneId, selfId, MissionId)

	local circles = GetQuestData(sceneId, selfId, MD_SHOUJI_MATERIAL_CYCLE[1], MD_SHOUJI_MATERIAL_CYCLE[2], MD_SHOUJI_MATERIAL_CYCLE[3])
	local maxcircles = x300517_GetMaxCircleNum( sceneId, selfId )

  local str;
	str = format( "环数: %d/%d", circles, maxcircles );

	Msg2Player(sceneId, selfId, str, 0, 3);
	
	if circles == 1 then
		GamePlayScriptLog(sceneId, selfId, 701)
	end
	
	if circles == 5 then
		GamePlayScriptLog(sceneId, selfId, 711)
	end
	
	if circles == 10 then
		GamePlayScriptLog(sceneId, selfId, 721)
	end
end

--**********************************
--检查是否可提交
function x300517_CheckSubmit( sceneId, selfId, NPCId)
		local itemdataId = x300517_GetCurrentItem(sceneId, selfId)
		local recycleCount = GetQuestData(sceneId, selfId, MD_SHOUJI_MATERIAL_CYCLECOUNT[1], MD_SHOUJI_MATERIAL_CYCLECOUNT[2], MD_SHOUJI_MATERIAL_CYCLECOUNT[3])
		if GetItemCount(sceneId,selfId,itemdataId) >= recycleCount then
					local misIndex = GetQuestIndexByID(sceneId,selfId,x300517_g_MissionId)                                                  
	    		SetQuestByIndex(sceneId,selfId,misIndex,0,1)
	    		SetQuestByIndex(sceneId,selfId,misIndex,7,1)
	    		return 1
	  else
	  			local misIndex = GetQuestIndexByID(sceneId,selfId,x300517_g_MissionId)                                                  
	    		SetQuestByIndex(sceneId,selfId,misIndex,0,0)
	    		SetQuestByIndex(sceneId,selfId,misIndex,7,0)
	  end
	  return 0
end

--**********************************
--提交任务
function x300517_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)
	if IsHaveQuest(sceneId,selfId, x300517_g_MissionId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"您没有这个任务！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x300517_CheckSubmit( sceneId, selfId, NPCId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"您没有达到完成条件！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
  end
	local circlesCount = GetQuestData(sceneId, selfId, MD_SHOUJI_MATERIAL_CYCLECOUNT[1], MD_SHOUJI_MATERIAL_CYCLECOUNT[2], MD_SHOUJI_MATERIAL_CYCLECOUNT[3])
	local circles = GetQuestData(sceneId, selfId, MD_SHOUJI_MATERIAL_CYCLE[1], MD_SHOUJI_MATERIAL_CYCLE[2], MD_SHOUJI_MATERIAL_CYCLE[3])
	if circlesCount < x300517_g_MaxSigleCycle_Count then
		local randnum = random(1, 100)
 		if randnum > 50 then
 			x300517_GetBonus( sceneId, selfId, NPCId)
 			local itemdataId = x300517_GetCurrentItem(sceneId, selfId)
			SetQuestData(sceneId, selfId, MD_SHOUJI_MATERIAL_CYCLECOUNT[1], MD_SHOUJI_MATERIAL_CYCLECOUNT[2], MD_SHOUJI_MATERIAL_CYCLECOUNT[3],circlesCount+1)
			local misIndex = GetQuestIndexByID(sceneId,selfId,x300517_g_MissionId)
	  	DelItem( sceneId,selfId,itemdataId, circlesCount )     
			SetQuestByIndex(sceneId,selfId,misIndex,0,0)
	    SetQuestByIndex(sceneId,selfId,misIndex,7,0)
	    circlesCount = circlesCount + 1
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"#Y"..x300517_g_MissionName)
			local str;
			str = format("\t刚得到的消息，我们对#G@itemid_%d#W的需求又上升了。你能再为国家收集#G%d#W个#G@itemid_%d#W吗？", itemdataId ,circlesCount,itemdataId);
			AddQuestText(sceneId,str)
			AddQuestText(sceneId,"\n#Y任务目标：")
			str = format( "收集#G%d#W个#G@itemid_%d#W", circlesCount, itemdataId )
			AddQuestText(sceneId,str )
			AddQuestText(sceneId,"\n#G小提示:#W")
			str = format( "这是本环的第%d次,最多可能连续做%d次", circlesCount ,x300517_g_MaxSigleCycle_Count);
			AddQuestText(sceneId,str )
			AddQuestText(sceneId,"\n#Y奖励内容：")
			local level = x300517_GetAcceptLevel(sceneId, selfId)
			local ExpBonus = x300517_g_ExpBonus*level*2^circlesCount
			str = format( "经验值: %d", ExpBonus)
			AddQuestText(sceneId,str )
			EndQuestEvent(sceneId)
			--DispatchQuestTips(sceneId,selfId)
			DispatchQuestInfoNM(sceneId, selfId, NPCId, x300517_g_ScriptId, x300517_g_MissionId);
			x300517_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
			return
		end
  end
  local itemdataId = x300517_GetCurrentItem(sceneId, selfId)
  if DelQuest(sceneId, selfId, x300517_g_MissionId) > 0 then
		x300517_Msg2toplayer( sceneId, selfId,2)
		x300517_GetBonus( sceneId, selfId, NPCId)
		local maxcircles = x300517_GetMaxCircleNum( sceneId, selfId )
		if circles >= maxcircles then
			x300517_SetDayComplete(sceneId, selfId)
			local level = x300517_GetAcceptLevel(sceneId, selfId)
			for i, item in x300517_g_ItemTable do
				if level < item.maxLevel then
					 BeginAddItem(sceneId)
					 local nRandNum = random(x300517_g_ItemMinBonus, x300517_g_ItemMaxBonus)
					 AddItem( sceneId, item.item, nRandNum )
					 local ret = EndAddItem( sceneId, selfId )
					 if ret == 1 then
							AddItemListToPlayer( sceneId, selfId )
							Msg2Player(sceneId, selfId, format("你获得了物品#R@itemid_%d#Y的奖励", item.item),4,3)
							Msg2Player(sceneId, selfId, format("你获得了物品#R@itemid_%d#Y的奖励", item.item),4,2)
					 end
					 break
				end
			end
			GamePlayScriptLog(sceneId, selfId, 722)
		end
		if circles == 1 then
			GamePlayScriptLog(sceneId, selfId, 702)
		end 
		if circles == 5 then
			GamePlayScriptLog(sceneId, selfId, 712)
		end
	  DelItem( sceneId,selfId,itemdataId, circlesCount )
		SetQuestData(sceneId, selfId, MD_SHOUJI_MATERIAL_CYCLECOUNT[1], MD_SHOUJI_MATERIAL_CYCLECOUNT[2], MD_SHOUJI_MATERIAL_CYCLECOUNT[3], 0)
	end
end

--**********************************
--获得奖励
function x300517_GetBonus( sceneId, selfId,NpcID)
	  if x300517_g_ExpBonus > 0 then
			local recycleCount = GetQuestData(sceneId, selfId, MD_SHOUJI_MATERIAL_CYCLECOUNT[1], MD_SHOUJI_MATERIAL_CYCLECOUNT[2], MD_SHOUJI_MATERIAL_CYCLECOUNT[3])
			--50 * lv * 2^重复标记
			local level = x300517_GetAcceptLevel(sceneId, selfId)
			local ExpBonus = x300517_g_ExpBonus*level*2^recycleCount
			AddExp(sceneId, selfId, ExpBonus);
			Msg2Player(sceneId, selfId, "#Y获得#R经验"..ExpBonus.."#Y的奖励", 0, 2)
  	end
		if x300517_g_BonusMoney1 > 0 then
	    AddMoney( sceneId, selfId, 1, x300517_g_BonusMoney1 )
	  end
		if x300517_g_BonusMoney2 > 0 then
	    AddMoney( sceneId, selfId, 0, x300517_g_BonusMoney2 )
	  end
		if x300517_g_BonusMoney3 > 0 then
	    AddMoney( sceneId, selfId, 3, x300517_g_BonusMoney3 )
		end
		if x300517_g_BonusMoney4 > 0 then
		local nRongYu = GetRongYu( sceneId, selfId )
			nRongYu = nRongYu + x300517_g_BonusMoney4
			SetRongYu( sceneId, selfId, nRongYu )
		end
		if x300517_g_BonusMoney5 > 0 then
			local nShengWang = GetShengWang( sceneId, selfId )
			nShengWang = nShengWang + x300517_g_BonusMoney5
			SetShengWang( sceneId, selfId, nShengWang )
		end
		if x300517_g_BonusMoney6 > 0 then
			AddHonor(sceneId,selfId,x300517_g_BonusMoney6)
		end
end

--**********************************
--放弃
function x300517_ProcQuestAbandon(sceneId, selfId, MissionId)
		if IsHaveQuest(sceneId,selfId, x300517_g_MissionId) <= 0 then
				return 
		end
		x300517_SetDayComplete( sceneId, selfId)
		SetQuestData(sceneId, selfId, MD_SHOUJI_MATERIAL_ABDON[1], MD_SHOUJI_MATERIAL_ABDON[2], MD_SHOUJI_MATERIAL_ABDON[3], 1)
		DelQuest(sceneId, selfId, x300517_g_MissionId)
	  x300517_Msg2toplayer( sceneId, selfId,1)
end

function x300517_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
end


function x300517_ProcAreaEntered(sceneId, selfId, zoneId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "ProcAreaEntered",sceneId, selfId, zoneId, MissionId )	

end

function x300517_ProcTiming(sceneId, selfId, ScriptId, MissionId)
	 CallScriptFunction( MISSION_SCRIPT, "ProcTiming",sceneId, selfId, ScriptId, MissionId )
end

function x300517_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcAreaLeaved",sceneId, selfId, ScriptId, MissionId)
end

function x300517_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
		x300517_ProcQuestLogRefresh(sceneId, selfId, x300517_g_MissionId)
		local itemdataId = x300517_GetCurrentItem(sceneId, selfId)
		local recycleCount = GetQuestData(sceneId, selfId, MD_SHOUJI_MATERIAL_CYCLECOUNT[1], MD_SHOUJI_MATERIAL_CYCLECOUNT[2], MD_SHOUJI_MATERIAL_CYCLECOUNT[3])
		if GetItemCount(sceneId,selfId,itemdataId) >= recycleCount then
					local misIndex = GetQuestIndexByID(sceneId,selfId,x300517_g_MissionId)                                                  
	    		SetQuestByIndex(sceneId,selfId,misIndex,0,GetItemCount(sceneId,selfId,itemdataId))
	    		SetQuestByIndex(sceneId,selfId,misIndex,7,1)
	    		
	  else
	  			local misIndex = GetQuestIndexByID(sceneId,selfId,x300517_g_MissionId)                                                 
	    		SetQuestByIndex(sceneId,selfId,misIndex,0,GetItemCount(sceneId,selfId,itemdataId))
	    		SetQuestByIndex(sceneId,selfId,misIndex,7,0)
	  end
end


function x300517_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )

end

function x300517_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x300517_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x300517_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x300517_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x300517_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x300517_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end

---------------------------------------------------------------------------------------------------
--获得随机物品
---------------------------------------------------------------------------------------------------
function x300517_GetModNum(sceneId, selfId)
	return 10
end

---------------------------------------------------------------------------------------------------
--获得随机物品
---------------------------------------------------------------------------------------------------
function x300517_GetRandItem(sceneId, selfId)
	local level = GetLevel(sceneId, selfId)
	for i, item in x300517_g_MissionTable do
		if level < item.maxLevel then
			local nCount = getn( item.item )
			local nRandNum = random(1, nCount)
			return item.item[nRandNum]
		end
	end
end

---------------------------------------------------------------------------------------------------
--获得当前物品
---------------------------------------------------------------------------------------------------
function x300517_GetCurrentItem(sceneId, selfId)
	local misIndex = GetQuestIndexByID( sceneId, selfId, x300517_g_MissionId );
	local rst = GetQuestParam( sceneId, selfId, misIndex, 5)
	return rst
end

---------------------------------------------------------------------------------------------------
--设置当前物品
---------------------------------------------------------------------------------------------------
function x300517_SetCurrentItem(sceneId, selfId, itemId)
	local misIndex = GetQuestIndexByID( sceneId, selfId, x300517_g_MissionId );
	SetQuestByIndex(sceneId,selfId,misIndex,5,itemId)
end
---------------------------------------------------------------------------------------------------
--增加奖励信息
---------------------------------------------------------------------------------------------------
function x300517_DispatchMissionInfo( sceneId, selfId, NPCId ,bContinue)
		if x300517_g_ExpBonus> 0 then
			local level = x300517_GetAcceptLevel(sceneId, selfId)
		  if bContinue > 0 then
				local recycleCount = GetQuestData(sceneId, selfId, MD_SHOUJI_MATERIAL_CYCLECOUNT[1], MD_SHOUJI_MATERIAL_CYCLECOUNT[2], MD_SHOUJI_MATERIAL_CYCLECOUNT[3])
				--50 * lv * 2^重复标记
				local ExpBonus = x300517_g_ExpBonus*level*2^recycleCount
				AddQuestExpBonus(sceneId, ExpBonus )
			else
				AddQuestExpBonus(sceneId, x300517_g_ExpBonus*level*2 )
			end
		end
		if x300517_g_BonusMoney1 > 0 then
			AddQuestMoneyBonus1(sceneId, x300517_g_BonusMoney1 )
		end
		if x300517_g_BonusMoney2 > 0 then
			AddQuestMoneyBonus2(sceneId, x300517_g_BonusMoney2 )
		end
		if x300517_g_BonusMoney3 > 0 then
			AddQuestMoneyBonus3(sceneId, x300517_g_BonusMoney3 )
		end
		if x300517_g_BonusMoney4 > 0 then
			AddQuestMoneyBonus4(sceneId, x300517_g_BonusMoney4 )
		end
		if x300517_g_BonusMoney5 > 0 then
			AddQuestMoneyBonus5(sceneId, x300517_g_BonusMoney5 )
		end
		if x300517_g_BonusMoney6 > 0 then
			AddQuestMoneyBonus6(sceneId, x300517_g_BonusMoney6 )
		end
		for i, item in x300517_g_BonusItem do
		   	AddQuestItemBonus(sceneId, item.item, item.n)
	  end
		for i, item in x300517_g_BonusChoiceItem do
	    	AddQuestRadioItemBonus(sceneId, item.item, item.n)
	  end
end

--**********************************
--提示信息
function x300517_Msg2toplayer( sceneId, selfId,type)
		if type == 0 then
				Msg2Player(sceneId, selfId, "您接受了任务："..x300517_g_MissionName.."！", 0, 2)
		  	Msg2Player(sceneId, selfId, "您接受了任务："..x300517_g_MissionName.."！", 0, 3)
		elseif type == 1 then
				Msg2Player(sceneId, selfId, "您放弃了任务："..x300517_g_MissionName.."！", 0, 2)
				Msg2Player(sceneId, selfId, "您放弃了任务："..x300517_g_MissionName.."！", 0, 3)
		elseif type == 2 then
				Msg2Player(sceneId, selfId, "您完成了任务："..x300517_g_MissionName.."！", 0, 2)
				Msg2Player(sceneId, selfId, "您完成了任务："..x300517_g_MissionName.."！", 0, 3)
				if x300517_g_ExpBonus > 0 then
					--Msg2Player(sceneId, selfId, "#Y获得#R经验"..x300517_g_ExpBonus.."#Y的奖励", 0, 2)
  			end
				if x300517_g_BonusMoney1 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y获得#R银卡"..x300517_g_BonusMoney1.."文#Y的奖励", 0, 2)
	  		end
				if x300517_g_BonusMoney2 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y获得#R现银"..x300517_g_BonusMoney2.."文#Y的奖励", 0, 2)
	  		end
				if x300517_g_BonusMoney3 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y获得#R金卡"..x300517_g_BonusMoney3.."文#Y的奖励", 0, 2)
				end
				if x300517_g_BonusMoney4 > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R朝廷声望值"..x300517_g_BonusMoney4.."#Y的奖励", 0, 2)
				end
				if x300517_g_BonusMoney5 > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R声望"..x300517_g_BonusMoney5.."#Y的奖励", 0, 2)
				end
				if x300517_g_BonusMoney6 > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R荣誉"..x300517_g_BonusMoney6.."#Y的奖励", 0, 2)
				end
		end
end

---------------------------------------------------------------------------------------------------
--取得此任务最大环数
---------------------------------------------------------------------------------------------------
function x300517_GetMaxCircleNum(sceneId, selfId)
	return 10;
end

---------------------------------------------------------------------------------------------------
--取得此任务当天是否完成
---------------------------------------------------------------------------------------------------
function x300517_GetDayComplete(sceneId, selfId)

	if x300517_g_Mis_Count > 0 then

		local today = GetDayOfYear()

		local lastday = GetQuestData(sceneId, selfId, MD_SHOUJI_MATERIAL_DATE[1], MD_SHOUJI_MATERIAL_DATE[2], MD_SHOUJI_MATERIAL_DATE[3])

		if lastday ~= today then
			return 0
		end

		local daycount =  GetQuestData(sceneId, selfId, MD_SHOUJI_MATERIAL_COUNT[1], MD_SHOUJI_MATERIAL_COUNT[2], MD_SHOUJI_MATERIAL_COUNT[3])
		return daycount

	end

	return 0
end

---------------------------------------------------------------------------------------------------
--更新当天接任务
---------------------------------------------------------------------------------------------------
function x300517_SetDayComplete(sceneId, selfId)
	local today = GetDayOfYear()
	local lastday = GetQuestData(sceneId, selfId, MD_SHOUJI_MATERIAL_DATE[1], MD_SHOUJI_MATERIAL_DATE[2], MD_SHOUJI_MATERIAL_DATE[3])
	if lastday == today then
		SetQuestData(sceneId, selfId, MD_SHOUJI_MATERIAL_DATE[1], MD_SHOUJI_MATERIAL_DATE[2], MD_SHOUJI_MATERIAL_DATE[3], today)
	end
	SetQuestData(sceneId, selfId, MD_SHOUJI_MATERIAL_COUNT[1], MD_SHOUJI_MATERIAL_COUNT[2], MD_SHOUJI_MATERIAL_COUNT[3], 1)
end
---------------------------------------------------------------------------------------------------
--更新接任务等级
---------------------------------------------------------------------------------------------------
function x300517_GetAcceptLevel(sceneId, selfId)
	local level = GetQuestData(sceneId, selfId, MD_SHOUJI_MATERIAL_LEVEL[1], MD_SHOUJI_MATERIAL_LEVEL[2], MD_SHOUJI_MATERIAL_LEVEL[3])
	return level
end

---------------------------------------------------------------------------------------------------
--重置信息
---------------------------------------------------------------------------------------------------
function x300517_SetAcceptInfo(sceneId, selfId)
	local today = GetDayOfYear()
	local level = GetLevel(sceneId, selfId)

	SetQuestData(sceneId, selfId, MD_SHOUJI_MATERIAL_DATE[1], MD_SHOUJI_MATERIAL_DATE[2], MD_SHOUJI_MATERIAL_DATE[3], today)
	SetQuestData(sceneId, selfId, MD_SHOUJI_MATERIAL_COUNT[1], MD_SHOUJI_MATERIAL_COUNT[2], MD_SHOUJI_MATERIAL_COUNT[3], 0)
	SetQuestData(sceneId, selfId, MD_SHOUJI_MATERIAL_CYCLE[1], MD_SHOUJI_MATERIAL_CYCLE[2], MD_SHOUJI_MATERIAL_CYCLE[3], 1)
	SetQuestData(sceneId, selfId, MD_SHOUJI_MATERIAL_CYCLECOUNT[1], MD_SHOUJI_MATERIAL_CYCLECOUNT[2], MD_SHOUJI_MATERIAL_CYCLECOUNT[3], 1)
	SetQuestData(sceneId, selfId, MD_SHOUJI_MATERIAL_LEVEL[1], MD_SHOUJI_MATERIAL_LEVEL[2], MD_SHOUJI_MATERIAL_LEVEL[3], level)
	SetQuestData(sceneId, selfId, MD_SHOUJI_MATERIAL_ABDON[1], MD_SHOUJI_MATERIAL_ABDON[2], MD_SHOUJI_MATERIAL_ABDON[3], 0)
end

---------------------------------------------------------------------------------------------------
--接受该环任务
---------------------------------------------------------------------------------------------------
function x300517_AcceptThisCycle(sceneId, selfId)
	local today = GetDayOfYear()
	local lastday = GetQuestData(sceneId, selfId, MD_SHOUJI_MATERIAL_DATE[1], MD_SHOUJI_MATERIAL_DATE[2], MD_SHOUJI_MATERIAL_DATE[3])
	if lastday == today then
		local circles = GetQuestData(sceneId, selfId, MD_SHOUJI_MATERIAL_CYCLE[1], MD_SHOUJI_MATERIAL_CYCLE[2], MD_SHOUJI_MATERIAL_CYCLE[3])
		local level = GetLevel(sceneId, selfId)
		circles = circles + 1
		SetQuestData(sceneId, selfId, MD_SHOUJI_MATERIAL_CYCLE[1], MD_SHOUJI_MATERIAL_CYCLE[2], MD_SHOUJI_MATERIAL_CYCLE[3], circles)
		SetQuestData(sceneId, selfId, MD_SHOUJI_MATERIAL_CYCLECOUNT[1], MD_SHOUJI_MATERIAL_CYCLECOUNT[2], MD_SHOUJI_MATERIAL_CYCLECOUNT[3], 1)
		SetQuestData(sceneId, selfId, MD_SHOUJI_MATERIAL_LEVEL[1], MD_SHOUJI_MATERIAL_LEVEL[2], MD_SHOUJI_MATERIAL_LEVEL[3], level)
		SetQuestData(sceneId, selfId, MD_SHOUJI_MATERIAL_ABDON[1], MD_SHOUJI_MATERIAL_ABDON[2], MD_SHOUJI_MATERIAL_ABDON[3], 0)
	else
		x300517_SetAcceptInfo(sceneId, selfId)
	end
end

---------------------------------------------------------------------------------------------------
--玩家是否放弃了该任务
---------------------------------------------------------------------------------------------------
function x300517_IsAbdon(sceneId, selfId)
	local today = GetDayOfYear()
	local lastday = GetQuestData(sceneId, selfId, MD_SHOUJI_MATERIAL_DATE[1], MD_SHOUJI_MATERIAL_DATE[2], MD_SHOUJI_MATERIAL_DATE[3])
	if lastday == today then
		return GetQuestData(sceneId, selfId, MD_SHOUJI_MATERIAL_ABDON[1], MD_SHOUJI_MATERIAL_ABDON[2], MD_SHOUJI_MATERIAL_ABDON[3])
	else
		return 0
	end
end

---------------------------------------------------------------------------------------------------
--更新任务追踪
---------------------------------------------------------------------------------------------------
function x300517_QuestLogRefresh(sceneId, selfId, MissionId, MissionTitle, MissionName, MissionTarget, MissionNPC, MissionProcess, MissionComment, MissionTip)

	if MissionTitle == nil then
		MissionTitle = "";
	end
	if MissionName == nil then
		MissionName = "";
	end
	if MissionTarget == nil then
		MissionTarget = "";
	end
	if MissionNPC == nil then
		MissionNPC = "";
	end
	if MissionProcess == nil then
		MissionProcess = "";
	end
	if MissionComment == nil then
		MissionComment = "";
	end
	if MissionTip == nil then
		MissionTip = "";
	end
	BeginQuestEvent(sceneId);
		local level = x300517_GetAcceptLevel(sceneId, selfId)
		local recycleCount = GetQuestData(sceneId, selfId, MD_SHOUJI_MATERIAL_CYCLECOUNT[1], MD_SHOUJI_MATERIAL_CYCLECOUNT[2], MD_SHOUJI_MATERIAL_CYCLECOUNT[3])
		local ExpBonus = x300517_g_ExpBonus*level*2^recycleCount
		AddQuestExpBonus(sceneId,ExpBonus)
		
		AddQuestLogCustomText(sceneId, MissionTitle, MissionName, MissionTarget, MissionNPC, MissionProcess, MissionComment, MissionTip);
		
	EndQuestEvent();
	DispatchQuestLogUpdate(sceneId, selfId, MissionId);

end
