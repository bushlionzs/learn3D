--【新手】新兵的装备<一>

--MisDescBegin
x203433_g_ScriptId = 203433
x203433_g_MissionIdPre =3411
x203433_g_MissionId = 3443
x203433_g_LevelLess	= 	1
x203433_g_MissionIdNext = 3412
x203433_g_Name	={}
x203433_g_ExtTarget={{type=20,n=1,target="找到@npc_131018"}}
x203433_g_MissionName="【新手】新兵的装备<一>"
x203433_g_MissionInfo="\t有了技能，武器，马匹，剩下的就是一些装备了。我建议你去找找军需官铁武，每一个新兵，都可以从他那里领取一批军需物资。"  --任务描述
x203433_g_MissionTarget="找到@npc_131018"		
x203433_g_MissionCompleted="\t恩，你也是来领取新兵的装备的吗？"					--完成任务npc说话的话
x203433_g_ContinueInfo=""
x203433_g_MissionHelp =	""
x203433_g_DemandItem ={}
x203433_g_ExpBonus = 1800
x203433_g_BonusMoney1 =5
x203433_g_BonusMoney2 =0
x203433_g_BonusMoney3 =0
x203433_g_BonusMoney4 =0
x203433_g_BonusMoney5 =12
x203433_g_BonusMoney6 =0
x203433_g_BonusChoiceItem ={}
x203433_g_BonusItem	=	{}
x203433_g_NpcGUID ={{ guid = 131018, name = "征兵校尉"} }
--MisDescEnd
--**********************************

function x203433_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)


	if IsQuestHaveDone(sceneId, selfId, x203433_g_MissionId) > 0 then
		return 
	end

				if IsQuestHaveDone(sceneId, selfId, x203433_g_MissionIdPre)> 0 then
						if IsHaveQuest(sceneId,selfId, x203433_g_MissionId) <= 0 then
								local state = GetQuestStateNM(sceneId,selfId,NPCId,x203433_g_MissionId)
								AddQuestTextNM( sceneId, selfId, NPCId, x203433_g_MissionId, state, -1 )
						end
			end
	
end

function x203433_DispatchMissionInfo( sceneId, selfId, NPCId )
		if x203433_g_ExpBonus> 0 then
			AddQuestExpBonus(sceneId, x203433_g_ExpBonus )
		end
		if x203433_g_BonusMoney1 > 0 then
			AddQuestMoneyBonus1(sceneId, x203433_g_BonusMoney1 )
		end
		if x203433_g_BonusMoney2 > 0 then
			AddQuestMoneyBonus2(sceneId, x203433_g_BonusMoney2 )
		end
		if x203433_g_BonusMoney3 > 0 then
			AddQuestMoneyBonus3(sceneId, x203433_g_BonusMoney3 )
		end
		if x203433_g_BonusMoney4 > 0 then
			AddQuestMoneyBonus4(sceneId, x203433_g_BonusMoney4 )
		end
		if x203433_g_BonusMoney5 > 0 then
			AddQuestMoneyBonus5(sceneId, x203433_g_BonusMoney5 )
		end
		if x203433_g_BonusMoney6 > 0 then
			AddQuestMoneyBonus6(sceneId, x203433_g_BonusMoney6 )
		end
		for i, item in x203433_g_BonusItem do
		   	AddQuestItemBonus(sceneId, item.item, item.n)
	  end
		for i, item in x203433_g_BonusChoiceItem do
	    	AddQuestRadioItemBonus(sceneId, item.item, item.n)
	  end
end
--**********************************

function x203433_ProcEventEntry(sceneId, selfId, NPCId, MissionId)	--点击该任务后执行此脚本
	if IsQuestHaveDone(sceneId, selfId, x203433_g_MissionId) > 0 then
		return 
	end
	if IsHaveQuest(sceneId,selfId, x203433_g_MissionId) > 0 then
			if x203433_CheckSubmit(sceneId, selfId, NPCId) <= 0 then
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x203433_g_MissionName)
						AddQuestText(sceneId,x203433_g_MissionCompleted)
						EndQuestEvent()
						DispatchQuestEventList(sceneId, selfId, NPCId, x203433_g_ScriptId, x203433_g_MissionId);
			else
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x203433_g_MissionName)
						AddQuestText(sceneId,x203433_g_MissionCompleted)
						AddQuestText(sceneId," ")
						x203433_DispatchMissionInfo( sceneId, selfId, NPCId )
						EndQuestEvent()
						DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x203433_g_ScriptId, x203433_g_MissionId);
			end
  elseif x203433_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
			BeginQuestEvent(sceneId)
	  	AddQuestText(sceneId,"#Y"..x203433_g_MissionName)
			AddQuestText(sceneId,x203433_g_MissionInfo)
			AddQuestText( sceneId,"#Y任务目标：")
			for i, item in x203433_g_ExtTarget do
					AddQuestText( sceneId,item.target)
			end 
			if x203433_g_MissionHelp ~= "" then
				AddQuestText(sceneId,"\n#G小提示:#W")
				AddQuestText(sceneId,x203433_g_MissionHelp )
			end
			x203433_DispatchMissionInfo( sceneId, selfId, NPCId )
	  	EndQuestEvent()
			DispatchQuestInfoNM(sceneId, selfId, NPCId, x203433_g_ScriptId, x203433_g_MissionId);
  end
	
end
--**********************************

function x203433_ProcAcceptCheck(sceneId, selfId, NPCId)
		
						return 1
		

end
--**********************************
function x203433_CheckSubmit( sceneId, selfId, NPCId)

	        return 1
	
end
--**********************************
function x203433_ProcQuestAccept( sceneId, selfId, NPCId, MissionId )
		if IsQuestHaveDone(sceneId, selfId, x203433_g_MissionId) > 0 then
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
		local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId,x203433_g_MissionId  )
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
		
		if x203433_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
					local retmiss = AddQuest( sceneId, selfId, x203433_g_MissionId, x203433_g_ScriptId, 0, 0, 0,1)
					if retmiss ==0 then
						Msg2Player(sceneId, selfId, "接受任务失败！", 0, 3)
						return 0
					else
		  			x203433_Msg2toplayer( sceneId, selfId,0)
						--if x203433_CheckSubmit(sceneId, selfId, NPCId) > 0 then
								local misIndex = GetQuestIndexByID(sceneId,selfId,x203433_g_MissionId)                                                  
	    					SetQuestByIndex(sceneId,selfId,misIndex,0,1)
	    					SetQuestByIndex(sceneId,selfId,misIndex,7,1)
	    					CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId,1,1 )
	    			--end
		  		end
	 	end                                                                    
	     
end
--**********************************

function x203433_ProcQuestAbandon(sceneId, selfId, MissionId)
		if IsHaveQuest(sceneId,selfId, x203433_g_MissionId) <= 0 then
				return 
		end
		DelQuest(sceneId, selfId, x203433_g_MissionId)
	  x203433_Msg2toplayer( sceneId, selfId,1)
			
end
--**********************************
function x203433_CheckPlayerBagFull( sceneId ,selfId,selectRadioId )
	local result = 1
	local j = 0
	local bAdd = 0 --是否已经在固定物品奖励添加检测中已经检查出包裹已满
	BeginAddItem(sceneId)
	for j, item in x203433_g_BonusItem do
		AddBindItem( sceneId, item.item, item.n )
  end
  for j, item in x203433_g_BonusChoiceItem do
        if item.item == selectRadioId then
            AddBindItem( sceneId, item.item, item.n )
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
function x203433_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)
	if IsHaveQuest(sceneId,selfId, x203433_g_MissionId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"您没有这个任务！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x203433_CheckSubmit( sceneId, selfId, NPCId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"您没有达到完成条件！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x203433_CheckPlayerBagFull( sceneId ,selfId,selectRadioId ) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"包裹已满！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif DelQuest(sceneId, selfId, x203433_g_MissionId) > 0 then
				x203433_Msg2toplayer( sceneId, selfId,2)
				CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId,6,0)
				QuestCom(sceneId, selfId, x203433_g_MissionId)
				x203433_GetBonus( sceneId, selfId,NPCId)
				BeginAddItem(sceneId)
				for i, item in x203433_g_BonusItem do
 						AddBindItem( sceneId, item.item, item.n )
				end
				for i, item in x203433_g_BonusChoiceItem do
						if item.item == selectRadioId then
	    			    AddBindItem( sceneId, item.item, item.n )
						end
    		end
    		EndAddItem(sceneId,selfId)
    		--AddItemListToPlayer(sceneId,selfId)
   end
   CallScriptFunction( MISSION_SCRIPT, "ProcEventEntry", sceneId, selfId, NPCId, x203433_g_MissionIdNext )	
end

function x203433_GetBonus( sceneId, selfId,NpcID)
	  if x203433_g_ExpBonus > 0 then
			AddExp(sceneId, selfId, x203433_g_ExpBonus);
  	end
		if x203433_g_BonusMoney1 > 0 then
	    AddMoney( sceneId, selfId, 1, x203433_g_BonusMoney1 )
	  end
		if x203433_g_BonusMoney2 > 0 then
	    AddMoney( sceneId, selfId, 0, x203433_g_BonusMoney2 )
	  end
		if x203433_g_BonusMoney3 > 0 then
	    AddMoney( sceneId, selfId, 3, x203433_g_BonusMoney3 )
		end
		if x203433_g_BonusMoney4 > 0 then
		local nRongYu = GetRongYu( sceneId, selfId )
			nRongYu = nRongYu + x203433_g_BonusMoney4
			SetRongYu( sceneId, selfId, nRongYu )
		end
		if x203433_g_BonusMoney5 > 0 then
			local nShengWang = GetShengWang( sceneId, selfId )
			nShengWang = nShengWang + x203433_g_BonusMoney5
			SetShengWang( sceneId, selfId, nShengWang )
		end
		if x203433_g_BonusMoney6 > 0 then
			AddHonor(sceneId,selfId,x203433_g_BonusMoney6)
		end
end

function x203433_Msg2toplayer( sceneId, selfId,type)
		if type == 0 then
				Msg2Player(sceneId, selfId, "您接受了任务"..x203433_g_MissionName.."！", 0, 2)
		  	Msg2Player(sceneId, selfId, "您接受了任务"..x203433_g_MissionName.."！", 0, 3)
		elseif type == 1 then
				Msg2Player(sceneId, selfId, "您放弃了任务"..x203433_g_MissionName.."！", 0, 2)
				Msg2Player(sceneId, selfId, "您放弃了任务"..x203433_g_MissionName.."！", 0, 3)
		elseif type == 2 then
				Msg2Player(sceneId, selfId, "您完成了任务"..x203433_g_MissionName.."！", 0, 2)
				Msg2Player(sceneId, selfId, "您完成了任务"..x203433_g_MissionName.."！", 0, 3)
				if x203433_g_ExpBonus > 0 then
					Msg2Player(sceneId, selfId, "#cffcf00获得#G经验"..x203433_g_ExpBonus.."#cffcf00的奖励", 0, 2)
  			end
				if x203433_g_BonusMoney1 > 0 then
	  		  Msg2Player(sceneId, selfId, "#cffcf00获得#G银卡"..x203433_g_BonusMoney1.."文#cffcf00的奖励", 0, 2)
	  		end
				if x203433_g_BonusMoney2 > 0 then
	  		  Msg2Player(sceneId, selfId, "#cffcf00获得#G现银"..x203433_g_BonusMoney2.."文#cffcf00的奖励", 0, 2)
	  		end
				if x203433_g_BonusMoney3 > 0 then
	  		  Msg2Player(sceneId, selfId, "#cffcf00获得#G金卡"..x203433_g_BonusMoney3.."文#cffcf00的奖励", 0, 2)
				end
				if x203433_g_BonusMoney4 > 0 then
					Msg2Player(sceneId, selfId, "#cffcf00获得#G朝廷声望值"..x203433_g_BonusMoney4.."#cffcf00的奖励", 0, 2)
				end
				if x203433_g_BonusMoney5 > 0 then
					Msg2Player(sceneId, selfId, "#cffcf00获得#G声望"..x203433_g_BonusMoney5.."#cffcf00的奖励", 0, 2)
				end
				if x203433_g_BonusMoney6 > 0 then
					Msg2Player(sceneId, selfId, "#cffcf00获得#G荣誉"..x203433_g_BonusMoney6.."#cffcf00的奖励", 0, 2)
				end
		end
end

function x203433_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
end


function x203433_ProcAreaEntered(sceneId, selfId, zoneId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "ProcAreaEntered",sceneId, selfId, zoneId, MissionId )	

end

function x203433_ProcTiming(sceneId, selfId, ScriptId, MissionId)
	 CallScriptFunction( MISSION_SCRIPT, "ProcTiming",sceneId, selfId, ScriptId, MissionId )
		
end

function x203433_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcAreaLeaved",sceneId, selfId, ScriptId, MissionId)
end

function x203433_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcQuestItemChanged",sceneId, selfId, itemdataId, MissionId )
end


function x203433_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
	  local bFind  = 0
    for i ,item in x203433_g_NpcGUID do
        if item.guid == npcGuid then
            bFind = 1
            break
        end
    end
    if bFind == 0 then
        return
    end
		if IsHaveQuest(sceneId,selfId, x203433_g_MissionId) > 0 then
				local state = GetQuestStateNM(sceneId,selfId,npcId,x203433_g_MissionId)
				AddQuestTextNM( sceneId, selfId, npcId, x203433_g_MissionId, state, -1 )
		end
end

function x203433_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x203433_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x203433_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x203433_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x203433_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x203433_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end