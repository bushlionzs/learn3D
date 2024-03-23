--【主线】明教惊魂<二>

--MisDescBegin
x203112_g_ScriptId = 203112
x203112_g_MissionIdPre =520
x203112_g_MissionId = 522
x203112_g_LevelLess	= 	60 
x203112_g_MissionIdNext = 523
x203112_g_Name	={}
x203112_g_ExtTarget={{type=20,n=1,target="击杀完颜洪烈"}}
x203112_g_MissionName="【剧场】枭雄的陨落"
x203112_g_MissionInfo="\t完颜洪烈拒绝了你的劝降请求。"  --任务描述
x203112_g_MissionTarget=""		
x203112_g_MissionCompleted="\t没想到一代枭雄完颜洪烈就这样。。。终于结束了，从此以后完颜洪烈与金国将永远的退出历史舞台！"					--完成任务npc说话的话
x203112_g_ContinueInfo="\t一定不能让完颜洪烈走掉。"
x203112_g_MissionHelp =	""
x203112_g_DemandItem ={}
x203112_g_ExpBonus = 93000
x203112_g_BonusMoney1 =376
x203112_g_BonusMoney2 =0
x203112_g_BonusMoney3 =0
x203112_g_BonusMoney4 =0
x203112_g_BonusMoney5 =51
x203112_g_BonusMoney6 =0
x203112_g_BonusItem	=	{}
x203112_g_BonusChoiceItem ={}
x203112_g_doing = 0
x203112_g_acceptid =-1
x203112_g_tuolei = -1
x203112_g_xuliewu = -1
x203112_g_yelvchucai = -1
x203112_g_hedan =-1
x203112_g_chahetai = -1
x203112_g_quchulv = -1
x203112_g_wanyanhonglie = -1
x203112_g_2feiqi = -1
x203112_g_3feiqi = -1
x203112_g_4feiqi = -1
x203112_g_5feiqi = -1
x203112_g_6feiqi = -1
x203112_g_7feiqi = -1
x203112_g_8feiqi =-1
x203112_g_9feiqi =-1
x203112_g_10feiqi =0
x203112_g_11feiqi =0
x203112_g_PROTECTINFO={ScneneTimerIndex = -1,  StartTime = 0}
x203112_g_NpcGUID ={{ guid = 111007, name = "耶律楚材"} }
--MisDescEnd
--**********************************

function x203112_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)


	if IsQuestHaveDone(sceneId, selfId, x203112_g_MissionId) > 0 then
		return 
	end
	if IsQuestHaveDone(sceneId, selfId, x203112_g_MissionIdPre)> 0 then
		if IsHaveQuest(sceneId,selfId, x203112_g_MissionId) <= 0 then
			local state = GetQuestStateNM(sceneId,selfId,NPCId,x203112_g_MissionId)
			AddQuestTextNM( sceneId, selfId, NPCId, x203112_g_MissionId, state, -1 )
		end
	end
end

function x203112_DispatchMissionInfo( sceneId, selfId, NPCId )
		if x203112_g_ExpBonus> 0 then
			AddQuestExpBonus(sceneId, x203112_g_ExpBonus )
		end
		if x203112_g_BonusMoney1 > 0 then
			AddQuestMoneyBonus1(sceneId, x203112_g_BonusMoney1 )
		end
		if x203112_g_BonusMoney2 > 0 then
			AddQuestMoneyBonus2(sceneId, x203112_g_BonusMoney2 )
		end
		if x203112_g_BonusMoney3 > 0 then
			AddQuestMoneyBonus3(sceneId, x203112_g_BonusMoney3 )
		end
		if x203112_g_BonusMoney4 > 0 then
			AddQuestMoneyBonus4(sceneId, x203112_g_BonusMoney4 )
		end
		if x203112_g_BonusMoney5 > 0 then
			AddQuestMoneyBonus5(sceneId, x203112_g_BonusMoney5 )
		end
		if x203112_g_BonusMoney6 > 0 then
			AddQuestMoneyBonus6(sceneId, x203112_g_BonusMoney6 )
		end
		for i, item in x203112_g_BonusItem do
		   	AddQuestItemBonus(sceneId, item.item, item.n)
	  end
		for i, item in x203112_g_BonusChoiceItem do
	    	AddQuestRadioItemBonus(sceneId, item.item, item.n)
	  end
end
--**********************************

function x203112_ProcEventEntry(sceneId, selfId, NPCId, MissionId)	--点击该任务后执行此脚本
	if IsQuestHaveDone(sceneId, selfId, x203112_g_MissionId) > 0 then
		return 
	end
	if IsHaveQuest(sceneId,selfId, x203112_g_MissionId) > 0 then
			if x203112_CheckSubmit(sceneId, selfId, NPCId) <= 0 then
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x203112_g_MissionName)
						AddQuestText(sceneId,x203112_g_ContinueInfo)
						EndQuestEvent()
						DispatchQuestEventList(sceneId, selfId, NPCId, x203112_g_ScriptId, x203112_g_MissionId);
			else
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x203112_g_MissionName)
						AddQuestText(sceneId,x203112_g_MissionCompleted)
						AddQuestText(sceneId," ")
						x203112_DispatchMissionInfo( sceneId, selfId, NPCId )
						EndQuestEvent()
						DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x203112_g_ScriptId, x203112_g_MissionId);
			end
  elseif x203112_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
			BeginQuestEvent(sceneId)
	  	AddQuestText(sceneId,"#Y"..x203112_g_MissionName)
			AddQuestText(sceneId,x203112_g_MissionInfo)
			AddQuestText( sceneId,"#Y任务目标：")
			for i, item in x203112_g_ExtTarget do
					AddQuestText( sceneId,item.target)
			end 
			if x203112_g_MissionHelp ~= "" then
				AddQuestText(sceneId,"\n#G小提示:#W")
				AddQuestText(sceneId,x203112_g_MissionHelp )
			end
			x203112_DispatchMissionInfo( sceneId, selfId, NPCId )
	  	EndQuestEvent()
			DispatchQuestInfoNM(sceneId, selfId, NPCId, x203112_g_ScriptId, x203112_g_MissionId);
	else
			Msg2Player(sceneId, selfId, "您现在的状态无法接受此任务！", 0, 3)
  end
	
end
--**********************************

function x203112_ProcAcceptCheck(sceneId, selfId, NPCId)
		if IsQuestHaveDone(sceneId, selfId, x203112_g_MissionIdPre)> 0 then
				if IsHaveQuest(sceneId,selfId, 7537) > 0 then
						return 0
				elseif IsHaveQuest(sceneId,selfId, 7538) > 0 then
						return 0
				elseif IsHaveQuest(sceneId,selfId, 7539) > 0 then
						return 0
				elseif IsHaveSpecificImpact(sceneId, selfId, 7516) > 0 then
						return 0
				elseif IsHaveSpecificImpact(sceneId, selfId, 7517) > 0 then
						return 0
				end
				return 1
		end
		return 0

end
--**********************************
function x203112_CheckSubmit( sceneId, selfId, NPCId)
		local misIndex = GetQuestIndexByID(sceneId, selfId, x203112_g_MissionId)
		if GetQuestParam(sceneId,selfId,misIndex,0) ==1 then 
	        return 1
	  end
	  return 0
	
end
--**********************************
function x203112_ProcQuestAccept( sceneId, selfId, NPCId, MissionId )
		if IsQuestHaveDone(sceneId, selfId, x203112_g_MissionId) > 0 then
				return 
		end
		if IsQuestFullNM(sceneId,selfId)==1 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"可接任务数量已满")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 
		end
		--检查前置任务
		local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId,x203112_g_MissionId  )
		if FrontMissiontId1 ~= -1 then
			if IsQuestHaveDoneNM( sceneId, selfId, FrontMissiontId1 ) == 0 then
				return 0
			end
		end
		if FrontMissiontId2 ~= -1 then
			if IsQuestHaveDoneNM( sceneId, selfId, FrontMissiontId2 ) == 0 then
				return 0
			end
		end
		if FrontMissiontId3 ~= -1 then
			if IsQuestHaveDoneNM( sceneId, selfId, FrontMissiontId3 ) == 0 then
				return 0
			end
		end
		if x203112_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
				if x203112_g_doing == 0 then
					local retmiss = AddQuest( sceneId, selfId, x203112_g_MissionId, x203112_g_ScriptId, 0, 0, 0,1)
					if retmiss ==0 then
						Msg2Player(sceneId, selfId, "接受任务失败！", 0, 3)
						return 0
					else
		  			x203112_Msg2toplayer( sceneId, selfId,0)
		  			x203112_g_PROTECTINFO.StartTime = GetCurrentTime()
						x203112_g_PROTECTINFO.ScneneTimerIndex = SetTimer(sceneId, selfId, 203112, "OnScneneTimer", 1)
						if x203112_g_PROTECTINFO.ScneneTimerIndex >= 0 then
								x203112_g_doing = 1
								x203112_g_acceptid = selfId
								x203112_g_tuolei=CreateMonster(sceneId, 1407,203.588943,213.748093,3,1,-1,-1,20,38000,180,"拖雷")
								x203112_g_xuliewu=CreateMonster(sceneId, 153,202.679352,215.773346,3,1,-1,-1,20,38000,180,"旭烈兀")
								x203112_g_yelvchucai=CreateMonster(sceneId, 213,204.524567,211.764801,3,1,-1,-1,20,38000,180,"耶律楚材")
								x203112_g_hedan=CreateMonster(sceneId, 153,201.728653,217.573944,3,1,-1,-1,20,38000,180,"合丹")
								x203112_g_chahetai=CreateMonster(sceneId, 153,205.507416,209.875259,3,1,-1,-1,20,38000,180,"察合台")
								SendSpecificImpactToUnit(sceneId, selfId, selfId, selfId, 7712, 0);
								Msg2Player(sceneId, selfId, "你闻到一阵奇异的香气，使你一阵阵头晕无力！", 0, 3)
								--if IsObjValid (sceneId,x203112_g_yelvchucai) == 1 then
								--	MonsterDoAction(sceneId, x203112_g_yelvchucai, 2, -1) 
								--end
						end
		  		end
				else
					Msg2Player(sceneId, selfId, "任务暂时无法接受！", 0, 3)
				end
		else
				Msg2Player(sceneId, selfId, "您现在的状态无法接受此任务！", 0, 3)
	 	end                                                                    
	     
end
--**********************************

function x203112_ProcQuestAbandon(sceneId, selfId, MissionId)
		if IsHaveQuest(sceneId,selfId, x203112_g_MissionId) <= 0 then
				return 
		end
		DelQuest(sceneId, selfId, x203112_g_MissionId)
	  x203112_Msg2toplayer( sceneId, selfId,1)
			
end
--**********************************
function x203112_CheckPlayerBagFull( sceneId ,selfId,selectRadioId )
	local result = 1
	local j = 0
	local bAdd = 0 --是否已经在固定物品奖励添加检测中已经检查出包裹已满
	BeginAddItem(sceneId)
	for j, item in x203112_g_BonusItem do
		AddItem( sceneId, item.item, item.n )
  end
  for j, item in x203112_g_BonusChoiceItem do
        if item.item == selectRadioId then
            AddItem( sceneId, item.item, item.n )
            break
        end
  end
  local ret = EndAddItem(sceneId,selfId)
    if ret <= 0 then
        if result == 1 then
            result = 0
        end
    end
	return result
end
--**********************************
function x203112_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)
	if IsHaveQuest(sceneId,selfId, x203112_g_MissionId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"您没有这个任务！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x203112_CheckSubmit( sceneId, selfId, NPCId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"您没有达到完成条件！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x203112_CheckPlayerBagFull( sceneId ,selfId,selectRadioId ) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"包裹已满！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif DelQuest(sceneId, selfId, x203112_g_MissionId) > 0 then
				x203112_Msg2toplayer( sceneId, selfId,2)
				QuestCom(sceneId, selfId, x203112_g_MissionId)
				x203112_GetBonus( sceneId, selfId,NPCId)
				BeginAddItem(sceneId)
				for i, item in x203112_g_BonusItem do
 						AddItem( sceneId, item.item, item.n )
				end
				for i, item in x203112_g_BonusChoiceItem do
						if item.item == selectRadioId then
	    			    AddItem( sceneId, item.item, item.n )
						end
    		end
    		EndAddItem(sceneId,selfId)
    		--AddItemListToPlayer(sceneId,selfId)
   end
   CallScriptFunction( MISSION_SCRIPT, "ProcEventEntry", sceneId, selfId, NPCId, x203112_g_MissionIdNext )	
end

function x203112_GetBonus( sceneId, selfId,NpcID)
	  if x203112_g_ExpBonus > 0 then
			AddExp(sceneId, selfId, x203112_g_ExpBonus);
  	end
		if x203112_g_BonusMoney1 > 0 then
	    AddMoney( sceneId, selfId, 1, x203112_g_BonusMoney1 )
	  end
		if x203112_g_BonusMoney2 > 0 then
	    AddMoney( sceneId, selfId, 0, x203112_g_BonusMoney2 )
	  end
		if x203112_g_BonusMoney3 > 0 then
	    AddMoney( sceneId, selfId, 3, x203112_g_BonusMoney3 )
		end
		if x203112_g_BonusMoney4 > 0 then
		local nRongYu = GetRongYu( sceneId, selfId )
			nRongYu = nRongYu + x203112_g_BonusMoney4
			SetRongYu( sceneId, selfId, nRongYu )
		end
		if x203112_g_BonusMoney5 > 0 then
			local nShengWang = GetShengWang( sceneId, selfId )
			nShengWang = nShengWang + x203112_g_BonusMoney5
			SetShengWang( sceneId, selfId, nShengWang )
		end
		if x203112_g_BonusMoney6 > 0 then
			AddHonor(sceneId,selfId,x203112_g_BonusMoney6)
		end
end

function x203112_Msg2toplayer( sceneId, selfId,type)
		if type == 0 then
				Msg2Player(sceneId, selfId, "您接受了任务"..x203112_g_MissionName.."！", 0, 2)
		  	Msg2Player(sceneId, selfId, "您接受了任务"..x203112_g_MissionName.."！", 0, 3)
		elseif type == 1 then
				Msg2Player(sceneId, selfId, "您放弃了任务"..x203112_g_MissionName.."！", 0, 2)
				Msg2Player(sceneId, selfId, "您放弃了任务"..x203112_g_MissionName.."！", 0, 3)
		elseif type == 2 then
				Msg2Player(sceneId, selfId, "您完成了任务"..x203112_g_MissionName.."！", 0, 2)
				Msg2Player(sceneId, selfId, "您完成了任务"..x203112_g_MissionName.."！", 0, 3)
				if x203112_g_ExpBonus > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R经验"..x203112_g_ExpBonus.."#Y的奖励", 0, 2)
  			end
				if x203112_g_BonusMoney1 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y获得#R银卡"..x203112_g_BonusMoney1.."文#Y的奖励", 0, 2)
	  		end
				if x203112_g_BonusMoney2 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y获得#R现银"..x203112_g_BonusMoney2.."文#Y的奖励", 0, 2)
	  		end
				if x203112_g_BonusMoney3 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y获得#R金卡"..x203112_g_BonusMoney3.."文#Y的奖励", 0, 2)
				end
				if x203112_g_BonusMoney4 > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R朝廷声望值"..x203112_g_BonusMoney4.."#Y的奖励", 0, 2)
				end
				if x203112_g_BonusMoney5 > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R声望"..x203112_g_BonusMoney5.."#Y的奖励", 0, 2)
				end
				if x203112_g_BonusMoney6 > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R荣誉"..x203112_g_BonusMoney6.."#Y的奖励", 0, 2)
				end
		end
end

function x203112_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
end


function x203112_ProcAreaEntered(sceneId, selfId, zoneId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "ProcAreaEntered",sceneId, selfId, zoneId, MissionId )	

end

function x203112_ProcTiming(sceneId, selfId, ScriptId, MissionId)
	 CallScriptFunction( MISSION_SCRIPT, "ProcTiming",sceneId, selfId, ScriptId, MissionId )
		
end

function x203112_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcAreaLeaved",sceneId, selfId, ScriptId, MissionId)
end

function x203112_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcQuestItemChanged",sceneId, selfId, itemdataId, MissionId )
end


function x203112_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
	  local bFind  = 0
    for i ,item in x203112_g_NpcGUID do
        if item.guid == npcGuid then
            bFind = 1
            break
        end
    end
    if bFind == 0 then
        return
    end
		if IsHaveQuest(sceneId,selfId, x203112_g_MissionId) > 0 then
				local state = GetQuestStateNM(sceneId,selfId,npcId,x203112_g_MissionId)
				AddQuestTextNM( sceneId, selfId, npcId, x203112_g_MissionId, state, -1 )
		end
end

function x203112_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x203112_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x203112_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x203112_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x203112_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x203112_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end

function x203112_OnScneneTimer(sceneId)
	if x203112_g_doing==1   then
		if GetCurrentTime() - x203112_g_PROTECTINFO.StartTime >= 2   then
						x203112_g_doing = 2
						if IsObjValid (sceneId,x203112_g_tuolei) == 1 then
								NpcTalk(sceneId, x203112_g_tuolei, "恶贼休要伤人！", -1)
								x203112_g_wanyanhonglie =FindMonsterByGUID( sceneId,111009)
								SetPatrolId(sceneId, x203112_g_tuolei, 0)
								SetPatrolId(sceneId, x203112_g_xuliewu, 1)  
								SetPatrolId(sceneId, x203112_g_yelvchucai, 2) 
								SetPatrolId(sceneId, x203112_g_hedan, 3)
								SetPatrolId(sceneId, x203112_g_chahetai, 4)
						end
		end
	elseif x203112_g_doing==2   then
		if GetCurrentTime() - x203112_g_PROTECTINFO.StartTime >= 4   then
						x203112_g_doing = 3
						if IsObjValid (sceneId,x203112_g_xuliewu) == 1 then
								NpcTalk(sceneId, x203112_g_xuliewu, "大家小心，前面有恶贼布下的毒。", -1)
								SetPatrolId(sceneId, x203112_g_wanyanhonglie, 5)
						end
		end
	elseif x203112_g_doing == 3   then
			if GetCurrentTime() - x203112_g_PROTECTINFO.StartTime >= 7   then
        		x203112_g_doing =4
						if IsObjValid (sceneId,x203112_g_wanyanhonglie) == 1 then
								NpcTalk(sceneId, x203112_g_wanyanhonglie, "拖雷你果然还是来了，没能让我踏入突厥！", -1)
						end
			end
	elseif x203112_g_doing == 4   then
			if GetCurrentTime() - x203112_g_PROTECTINFO.StartTime >= 15   then
						x203112_g_doing =5
						if IsObjValid (sceneId,x203112_g_wanyanhonglie) == 1 then
								SetMonsterDir(sceneId,x203112_g_wanyanhonglie,120)
								if IsObjValid (sceneId,x203112_g_tuolei) == 1 then
									NpcTalk(sceneId, x203112_g_tuolei, "完颜洪烈你身后已无退路，不要再试图逃跑了！", -1)
								end	
						end
						--x203112_g_hedan =FindMonsterByGUID( sceneId,141317)
						--x203112_g_chahetai =FindMonsterByGUID( sceneId,141318)
						x203112_g_quchulv=CreateMonster(sceneId, 1712,217.006226,205.074417,3,1,-1,-1,20,31000,180,"屈出律")   
						--x203112_g_1feiqi =FindMonsterByGUID( sceneId,141302)
						--x203112_g_2feiqi =FindMonsterByGUID( sceneId,141301)
						--x203112_g_8feiqi =FindMonsterByGUID( sceneId,141322)
						--x203112_g_9feiqi =FindMonsterByGUID( sceneId,141323)
						--x203112_g_10feiqi =FindMonsterByGUID( sceneId,141324)
						--x203112_g_11feiqi =FindMonsterByGUID( sceneId,141325)
						--if IsObjValid (sceneId,x203112_g_hedan) == 1 then
						--		SetPatrolId(sceneId, x203112_g_hedan, 9)
						--end
						--if IsObjValid (sceneId,x203112_g_chahetai) == 1 then
							--	SetPatrolId(sceneId, x203112_g_chahetai, 10)
						--end
						if IsObjValid (sceneId,x203112_g_quchulv) == 1 then
								SetPatrolId(sceneId, x203112_g_quchulv, 6)
						end
						--if IsObjValid (sceneId,x203112_g_1feiqi) == 1 then
						--		SetPatrolId(sceneId, x203112_g_1feiqi, 3)
						--end
						--if IsObjValid (sceneId,x203112_g_2feiqi) == 1 then
						--		SetPatrolId(sceneId, x203112_g_2feiqi, 4)
						--end
						--if IsObjValid (sceneId,x203112_g_8feiqi) == 1 then
						--		SetPatrolId(sceneId, x203112_g_8feiqi, 5)
						--end
						--if IsObjValid (sceneId,x203112_g_9feiqi) == 1 then
						--		SetPatrolId(sceneId, x203112_g_9feiqi, 6)
						--end
						--if IsObjValid (sceneId,x203112_g_10feiqi) == 1 then
						--		SetPatrolId(sceneId, x203112_g_10feiqi, 7)
						--end
						--if IsObjValid (sceneId,x203112_g_11feiqi) == 1 then
						--		SetPatrolId(sceneId, x203112_g_11feiqi, 8)
						--end
			end
	elseif x203112_g_doing == 5   then
			if GetCurrentTime() - x203112_g_PROTECTINFO.StartTime >= 18   then
				x203112_g_doing =6
				if IsObjValid (sceneId,x203112_g_wanyanhonglie) == 1 then
						NpcTalk(sceneId, x203112_g_wanyanhonglie, "突厥之王！屈出律你还真是守信约的来了！", -1)
				end
			end
	elseif x203112_g_doing == 6   then
			if GetCurrentTime() - x203112_g_PROTECTINFO.StartTime >= 21   then
						x203112_g_doing =7
						if IsObjValid (sceneId,x203112_g_quchulv) == 1 then
								NpcTalk(sceneId, x203112_g_quchulv, "你就是完颜洪烈么？早听说你要前往我突厥，我也是前来追杀你献于蒙古的，你不要胡乱说话！", -1)
						end
			end
	elseif x203112_g_doing == 7   then
			if GetCurrentTime() - x203112_g_PROTECTINFO.StartTime >= 24   then
						x203112_g_doing =8
						if IsObjValid (sceneId,x203112_g_wanyanhonglie) == 1 then
								NpcTalk(sceneId, x203112_g_wanyanhonglie, "好，算我完颜洪烈看错人了。我死也不会死于你们手中！", -1)
								SendSpecificImpactToUnit(sceneId, x203112_g_wanyanhonglie, x203112_g_wanyanhonglie, x203112_g_wanyanhonglie, 3060, 0)	
						end
			end
	elseif x203112_g_doing == 8   then
			if GetCurrentTime() - x203112_g_PROTECTINFO.StartTime >= 28   then
						x203112_g_doing =9
						SetPos(sceneId,x203112_g_wanyanhonglie,0,0)
						if IsObjValid (sceneId,x203112_g_tuolei) == 1 then
								NpcTalk(sceneId, x203112_g_tuolei, "！", -1)
						end
						if IsObjValid (sceneId,x203112_g_xuliewu) == 1 then
								NpcTalk(sceneId, x203112_g_xuliewu, "！", -1)
						end
						if IsObjValid (sceneId,x203112_g_yelvchucai) == 1 then
								NpcTalk(sceneId, x203112_g_yelvchucai, "！", -1)
						end
						if IsObjValid (sceneId,x203112_g_hedan) == 1 then
								NpcTalk(sceneId, x203112_g_hedan, "！", -1)
						end
						if IsObjValid (sceneId,x203112_g_chahetai) == 1 then
								NpcTalk(sceneId, x203112_g_chahetai, "！", -1)
						end						
			end
	elseif x203112_g_doing == 9   then
			if GetCurrentTime() - x203112_g_PROTECTINFO.StartTime >= 32   then
						x203112_g_doing =10
				if IsObjValid (sceneId,x203112_g_quchulv) == 1 then
								NpcTalk(sceneId, x203112_g_quchulv, "久闻蒙古勇士们英勇，今日一见果然名不虚传，这是你所中之毒的解药。咱们后会有期了！", -1)
								SetPatrolId(sceneId, x203112_g_quchulv, 7)
						end
						
						--if IsPlayerStateNormal(sceneId,x203112_g_acceptid) ==1 then
						--	if IsHaveQuest(sceneId,x203112_g_acceptid, x203112_g_MissionId) > 0 then
						--		SetPos(sceneId,x203112_g_acceptid,232,50)
						--	end
						--end
						--if IsObjValid (sceneId,x203112_g_yelvchucai) == 1 then
						--		SetPos(sceneId,x203112_g_yelvchucai,231,52)
						--		SetMonsterDir(sceneId,x203112_g_yelvchucai,190)
						--		SetMonsterDir(sceneId,x203112_g_quchulv,140)
						--		SetMonsterDir(sceneId,x203112_g_1feiqi,140)
						--		SetMonsterDir(sceneId,x203112_g_2feiqi,185)
						--		SetMonsterDir(sceneId,x203112_g_8feiqi,140)
						--		SetMonsterDir(sceneId,x203112_g_9feiqi,140)
						--		SetMonsterDir(sceneId,x203112_g_10feiqi,140)
						--		SetMonsterDir(sceneId,x203112_g_11feiqi,120)
						--end
			end
	--elseif x203112_g_doing == 10   then
	--		if GetCurrentTime() - x203112_g_PROTECTINFO.StartTime >= 25   then
	--					x203112_g_doing =11
	--					if IsObjValid (sceneId,x203112_g_3feiqi) == 1 then
	--							NpcTalk(sceneId, x203112_g_3feiqi, "小女子苏多娜给阳教主请安！", -1)
	--					end
	--		end
	--elseif x203112_g_doing == 11   then
	--		if GetCurrentTime() - x203112_g_PROTECTINFO.StartTime >= 28   then
	--					x203112_g_doing =12
	--					if IsObjValid (sceneId,x203112_g_quchulv) == 1 then
	--							NpcTalk(sceneId, x203112_g_quchulv, "废话少说，你们擅闯明教圣地，所为何事？", -1)
	--					end
	--		end
	--elseif x203112_g_doing == 12   then
	--		if GetCurrentTime() - x203112_g_PROTECTINFO.StartTime >= 31   then
	--					x203112_g_doing =13
	--					if IsObjValid (sceneId,x203112_g_3feiqi) == 1 then
	--							NpcTalk(sceneId, x203112_g_3feiqi, "好，教主如此爽快，我就不绕弯子了。我们特地来收回我教圣物“圣火令”的！", -1)
	--					end
	--		end
	--elseif x203112_g_doing == 13   then
	--		if GetCurrentTime() - x203112_g_PROTECTINFO.StartTime >= 34   then
	--					x203112_g_doing =14
	--					if IsObjValid (sceneId,x203112_g_3feiqi) == 1 then
	--							NpcTalk(sceneId, x203112_g_3feiqi, "我们拿到圣火令打开它却发现缺少了一样东西，我想这东西一定在阳教主身上。", -1)
	--					end
	--		end
	--elseif x203112_g_doing == 14   then
	--		if GetCurrentTime() - x203112_g_PROTECTINFO.StartTime >= 37   then
	--					x203112_g_doing =15
	--					if IsObjValid (sceneId,x203112_g_quchulv) == 1 then
	--							NpcTalk(sceneId, x203112_g_quchulv, "什么？这么说本教失踪的圣火令是被你等拿走了，那休怪阳某人不客气了。", -1)
	--					end
	--		end
	--elseif x203112_g_doing == 15   then
	--		if GetCurrentTime() - x203112_g_PROTECTINFO.StartTime >= 40   then
	--					x203112_g_doing =16
	--					if IsObjValid (sceneId,x203112_g_yelvchucai) == 1 then
	--							NpcTalk(sceneId, x203112_g_yelvchucai, "臭娘们，来了你就别想走了。留在这里让我破破戒！", -1)
	--					end
	--		end
	--elseif x203112_g_doing == 16   then
	--		if GetCurrentTime() - x203112_g_PROTECTINFO.StartTime >= 43   then
	--					x203112_g_doing =17
	--					if IsObjValid (sceneId,x203112_g_3feiqi) == 1 then
	--							NpcTalk(sceneId, x203112_g_3feiqi, "哼，还敢嘴硬！你们中毒已深，现在恐怕连站都站不稳了吧。", -1)
	--					end
	--		end
	--elseif x203112_g_doing == 17   then
	--		if GetCurrentTime() - x203112_g_PROTECTINFO.StartTime >= 46   then
	--					x203112_g_doing =18
	--					if IsObjValid (sceneId,x203112_g_quchulv) == 1 then
	--							NpcTalk(sceneId, x203112_g_quchulv, "是吗？你这么确认？", -1)
	--					end
	--		end
	--elseif x203112_g_doing == 18   then
	--		if GetCurrentTime() - x203112_g_PROTECTINFO.StartTime >= 48   then
	--					x203112_g_doing =19
	--					if IsObjValid (sceneId,x203112_g_4feiqi) == 1 then
	--							SendSpecificImpactToUnit(sceneId, x203112_g_4feiqi, x203112_g_4feiqi, x203112_g_4feiqi, 3060, 0);
	--					end
	--					if IsObjValid (sceneId,x203112_g_5feiqi) == 1 then
	--							SendSpecificImpactToUnit(sceneId, x203112_g_5feiqi, x203112_g_5feiqi, x203112_g_5feiqi, 3060, 0);
	--					end
	--		end
	--elseif x203112_g_doing == 19   then
	--		if GetCurrentTime() - x203112_g_PROTECTINFO.StartTime >= 50   then
	--					x203112_g_doing =20
	--					if IsObjValid (sceneId,x203112_g_3feiqi) == 1 then
	--							NpcTalk(sceneId, x203112_g_3feiqi, "什么？难道毒还没有发作？", -1)
	--					end
	--		end
	--elseif x203112_g_doing == 20   then
	--		if GetCurrentTime() - x203112_g_PROTECTINFO.StartTime >= 53   then
	--					x203112_g_doing =21
	--					if IsObjValid (sceneId,x203112_g_3feiqi) == 1 then
	--							NpcTalk(sceneId, x203112_g_3feiqi, "小子，原来你是明教的人！居然被你给骗了，我们走！", -1)
	--					end
	--		end
	--elseif x203112_g_doing == 21   then
	--		if GetCurrentTime() - x203112_g_PROTECTINFO.StartTime >= 56   then
	--					x203112_g_doing =22
	--					if IsObjValid (sceneId,x203112_g_quchulv) == 1 then
	--							NpcTalk(sceneId, x203112_g_quchulv, "看来我们误会这位少侠了，他并不是波斯的人。", -1)
	--					end
	--		end
	--elseif x203112_g_doing == 22   then
	--		if GetCurrentTime() - x203112_g_PROTECTINFO.StartTime >= 60   then
	--					x203112_g_doing =23
	--					if IsObjValid (sceneId,x203112_g_quchulv) == 1 then
	--							NpcTalk(sceneId, x203112_g_quchulv, "少侠！我们误以为你是波斯派来的。现在事情已经澄清了，恰好我明教正逢大难，希望你能助我教渡过难关。", -1)
	--					end
	--		end
	elseif x203112_g_doing==10 then
			if GetCurrentTime() - x203112_g_PROTECTINFO.StartTime >= 34   then
				x203112_g_doing=11
				if IsPlayerStateNormal(sceneId,x203112_g_acceptid) ==1 then
					if IsHaveQuest(sceneId,x203112_g_acceptid, x203112_g_MissionId) > 0 then
									local misIndex = GetQuestIndexByID(sceneId, x203112_g_acceptid, x203112_g_MissionId)
									SetQuestByIndex(sceneId,x203112_g_acceptid,misIndex,0,1)
									SetQuestByIndex(sceneId,x203112_g_acceptid,misIndex,7,1)
									BeginQuestEvent(sceneId)
									AddQuestText(sceneId,format("击杀完颜洪烈   %d/1", GetQuestParam(sceneId,x203112_g_acceptid,misIndex,0) ))
									EndQuestEvent(sceneId)
									DispatchQuestTips(sceneId,x203112_g_acceptid)
									CancelSpecificImpact(sceneId,x203112_g_acceptid,7712)		
									SetPos(sceneId,x203112_g_tuolei,0,0)
									SetPos(sceneId,x203112_g_xuliewu,0,0)
									SetPos(sceneId,x203112_g_yelvchucai,0,0)
									SetPos(sceneId,x203112_g_hedan,0,0)
									SetPos(sceneId,x203112_g_chahetai,0,0)		
									SetPos(sceneId,x203112_g_quchulv,0,0)					
					end
				end
			end
elseif x203112_g_doing==11 then
			if GetCurrentTime() - x203112_g_PROTECTINFO.StartTime >= 38   then
				x203112_g_doing=12
				x203112_CloseTimer(sceneId, x203112_g_PROTECTINFO.ScneneTimerIndex)
			end
	end
end


--**********************************
--关闭计时器
--**********************************
function x203112_CloseTimer( sceneId, TimerIndex )
	StopTimer(sceneId, TimerIndex)
	x203112_g_doing =0
	x203112_g_acceptid =-1
	x203112_g_PROTECTINFO={ScneneTimerIndex = -1,  StartTime = 0}
	--SetPatrolId(sceneId, x203112_g_hedan, -1)
	--SetPatrolId(sceneId, x203112_g_chahetai, -1)
	--SetPatrolId(sceneId, x203112_g_quchulv, -1)
	--SetPatrolId(sceneId, x203112_g_1feiqi, -1)
	--SetPatrolId(sceneId, x203112_g_2feiqi, -1)
	--SetPatrolId(sceneId, x203112_g_8feiqi, -1)
	--SetPatrolId(sceneId, x203112_g_9feiqi, -1)
	SetPatrolId(sceneId, x203112_g_wanyanhonglie, -1)
	--SetPatrolId(sceneId, x203112_g_11feiqi, -1)
	--SetPos(sceneId,x203112_g_yelvchucai,233,35)
	--SetPos(sceneId,x203112_g_hedan,42.8,254.6)
	--SetPos(sceneId,x203112_g_chahetai,47.5,254.7)
	--SetPos(sceneId,x203112_g_quchulv,45.1,255)
	SetPos(sceneId,x203112_g_wanyanhonglie,216,221)
	--SetPos(sceneId,x203112_g_2feiqi,36.6,259.4)
	--SetPos(sceneId,x203112_g_8feiqi,45.7,274.9)
	--SetPos(sceneId,x203112_g_9feiqi,49.7,274.8)
	--SetPos(sceneId,x203112_g_10feiqi,45.4,305.4)
	--SetPos(sceneId,x203112_g_11feiqi,50.3,305.4)
	--SetMonsterDir(sceneId,x203112_g_yelvchucai,90)
	--SetMonsterDir(sceneId,x203112_g_hedan,0)
	--SetMonsterDir(sceneId,x203112_g_chahetai,0)
	--SetMonsterDir(sceneId,x203112_g_quchulv,0)
	--SetMonsterDir(sceneId,x203112_g_1feiqi,0)
	--SetMonsterDir(sceneId,x203112_g_2feiqi,0)
	--SetMonsterDir(sceneId,x203112_g_8feiqi,0)
	--SetMonsterDir(sceneId,x203112_g_9feiqi,0)
	SetMonsterDir(sceneId,x203112_g_wanyanhonglie,320)
	--SetMonsterDir(sceneId,x203112_g_11feiqi,0)
	
end

function x203112_ProcQuestLogRefresh( sceneId,selfId,missionId)

    --BeginQuestEvent(sceneId)
    --EndQuestEvent()
		--DispatchQuestLogUpdate(sceneId, selfId, x203112_g_MissionId);

end