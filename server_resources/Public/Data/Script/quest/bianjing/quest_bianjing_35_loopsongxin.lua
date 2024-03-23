--【主线】催促资金

--MisDescBegin
x260000_g_ScriptId = 260000
x260000_g_MissionIdPre =-1
x260000_g_MissionId = 2116
x260000_g_LevelLess	= 	15 
x260000_g_MissionIdNext = 2117
x260000_g_Name	={}
x260000_g_ExtTarget={{type=20,n=1,target="找到@npc_129228"}}
x260000_g_MissionName="【循环】风紧"
x260000_g_MissionInfo="\t加思加这几天好像手头很紧，想干一票大的。不过最近怪事很多，你帮我通知他一下，不要轻举妄动，免得把自己栽进去。"  --任务描述
x260000_g_MissionTarget=""		
x260000_g_MissionCompleted="\t唉，既然是这样，那还是再忍几天，等风声过了再找“肥羊”吧。 "					--完成任务npc说话的话
x260000_g_ContinueInfo=""
x260000_g_MissionHelp =	""
x260000_g_DemandItem ={}
x260000_g_BonusMoney1 =0
x260000_g_BonusMoney2 =0
x260000_g_BonusMoney3 =0
x260000_g_BonusMoney4 =0
x260000_g_BonusMoney5 =0
x260000_g_BonusMoney6 =0
x260000_g_BonusItem	=	{}
x260000_g_BonusChoiceItem ={}
x260000_g_ExpBonus = 20
x260000_g_NpcGUID ={{ guid = 129228, name = "加思加"} }
--**********************************

function x260000_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)


	if IsQuestHaveDone(sceneId, selfId, x260000_g_MissionId) > 0 then
		return 
	end
	if GetLevel(sceneId, selfId)> 34 then
		if GetLevel(sceneId, selfId)< 46 then
			if IsHaveQuest(sceneId,selfId, x260000_g_MissionId) <= 0 then
				local state = GetQuestStateNM(sceneId,selfId,NPCId,x260000_g_MissionId)
				AddQuestTextNM( sceneId, selfId, NPCId, x260000_g_MissionId, state, -1 )
			end
		end
	end
end

function x260000_DispatchMissionInfo( sceneId, selfId, NPCId )
		if x260000_g_ExpBonus> 0 then
		local addexpture = x260000_g_ExpBonus*GetLevel(sceneId, selfId)
			AddQuestExpBonus(sceneId, addexpture )
		end
		if x260000_g_BonusMoney1 > 0 then
			AddQuestMoneyBonus1(sceneId, x260000_g_BonusMoney1 )
		end
		if x260000_g_BonusMoney2 > 0 then
			AddQuestMoneyBonus2(sceneId, x260000_g_BonusMoney2 )
		end
		if x260000_g_BonusMoney3 > 0 then
			AddQuestMoneyBonus3(sceneId, x260000_g_BonusMoney3 )
		end
		if x260000_g_BonusMoney4 > 0 then
			AddQuestMoneyBonus4(sceneId, x260000_g_BonusMoney4 )
		end
		if x260000_g_BonusMoney5 > 0 then
			AddQuestMoneyBonus5(sceneId, x260000_g_BonusMoney5 )
		end
		if x260000_g_BonusMoney6 > 0 then
			AddQuestMoneyBonus6(sceneId, x260000_g_BonusMoney6 )
		end
		for i, item in x260000_g_BonusItem do
		   	AddQuestItemBonus(sceneId, item.item, item.n)
	  end
		for i, item in x260000_g_BonusChoiceItem do
	    	AddQuestRadioItemBonus(sceneId, item.item, item.n)
	  end
end
--**********************************

function x260000_ProcEventEntry(sceneId, selfId, NPCId, MissionId)	--点击该任务后执行此脚本
	if IsQuestHaveDone(sceneId, selfId, x260000_g_MissionId) > 0 then
		return 
	end
	if IsHaveQuest(sceneId,selfId, x260000_g_MissionId) > 0 then
			if x260000_CheckSubmit(sceneId, selfId, NPCId) <= 0 then
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x260000_g_MissionName)
						AddQuestText(sceneId,x260000_g_MissionCompleted)
						EndQuestEvent()
						DispatchQuestEventList(sceneId, selfId, NPCId, x260000_g_ScriptId, x260000_g_MissionId);
			else
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x260000_g_MissionName)
						AddQuestText(sceneId,x260000_g_MissionCompleted)
						AddQuestText(sceneId," ")
						x260000_DispatchMissionInfo( sceneId, selfId, NPCId )
						EndQuestEvent()
						DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x260000_g_ScriptId, x260000_g_MissionId);
			end
  elseif x260000_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
			BeginQuestEvent(sceneId)
	  	AddQuestText(sceneId,"#Y"..x260000_g_MissionName)
			AddQuestText(sceneId,x260000_g_MissionInfo)
			AddQuestText( sceneId,"#Y任务目标：")
			for i, item in x260000_g_ExtTarget do
					AddQuestText( sceneId,item.target)
			end 
			if x260000_g_MissionHelp ~= "" then
				AddQuestText(sceneId,"\n#G小提示:#W")
				AddQuestText(sceneId,x260000_g_MissionHelp )
			end
			x260000_DispatchMissionInfo( sceneId, selfId, NPCId )
	  	EndQuestEvent()
			DispatchQuestInfoNM(sceneId, selfId, NPCId, x260000_g_ScriptId, x260000_g_MissionId);
  end
	
end
--**********************************

function x260000_ProcAcceptCheck(sceneId, selfId, NPCId)
		--if IsQuestHaveDone(sceneId, selfId, x260000_g_MissionIdPre)> 0 then
					return 1
		--end
		--return 0

end
--**********************************
function x260000_CheckSubmit( sceneId, selfId, NPCId)

	        return 1
	
end
--**********************************
function x260000_ProcQuestAccept( sceneId, selfId, NPCId, MissionId )
		if IsQuestHaveDone(sceneId, selfId, x260000_g_MissionId) > 0 then
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
		local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId,x260000_g_MissionId  )
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
		
		if x260000_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
					local retmiss = AddQuest( sceneId, selfId, x260000_g_MissionId, x260000_g_ScriptId, 0, 0, 0,1)
					if retmiss ==0 then
						Msg2Player(sceneId, selfId, "接受任务失败！", 0, 3)
						return 0
					else
		  			x260000_Msg2toplayer( sceneId, selfId,0)
						--if x260000_CheckSubmit(sceneId, selfId, NPCId) > 0 then
								local misIndex = GetQuestIndexByID(sceneId,selfId,x260000_g_MissionId)                                                  
	    					SetQuestByIndex(sceneId,selfId,misIndex,0,1)
	    					SetQuestByIndex(sceneId,selfId,misIndex,7,1)
	    			--end
		  		end
	 	end                                                                    
	     
end
--**********************************

function x260000_ProcQuestAbandon(sceneId, selfId, MissionId)
		if IsHaveQuest(sceneId,selfId, x260000_g_MissionId) <= 0 then
				return 
		end
		DelQuest(sceneId, selfId, x260000_g_MissionId)
	  x260000_Msg2toplayer( sceneId, selfId,1)
			
end
--**********************************
function x260000_CheckPlayerBagFull( sceneId ,selfId,selectRadioId )
	local result = 1
	local j = 0
	local bAdd = 0 --是否已经在固定物品奖励添加检测中已经检查出包裹已满
	BeginAddItem(sceneId)
	for j, item in x260000_g_BonusItem do
		AddItem( sceneId, item.item, item.n )
  end
  for j, item in x260000_g_BonusChoiceItem do
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
function x260000_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)
	if IsHaveQuest(sceneId,selfId, x260000_g_MissionId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"您没有这个任务！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x260000_CheckSubmit( sceneId, selfId, NPCId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"您没有达到完成条件！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x260000_CheckPlayerBagFull( sceneId ,selfId,selectRadioId ) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"包裹已满！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif DelQuest(sceneId, selfId, x260000_g_MissionId) > 0 then
				x260000_Msg2toplayer( sceneId, selfId,2)
				--QuestCom(sceneId, selfId, x260000_g_MissionId)
				x260000_GetBonus( sceneId, selfId,NPCId)
				BeginAddItem(sceneId)
				for i, item in x260000_g_BonusItem do
 						AddItem( sceneId, item.item, item.n )
				end
				for i, item in x260000_g_BonusChoiceItem do
						if item.item == selectRadioId then
	    			    AddItem( sceneId, item.item, item.n )
						end
    		end
    		EndAddItem(sceneId,selfId)
    		--AddItemListToPlayer(sceneId,selfId)
   end
   --CallScriptFunction( MISSION_SCRIPT, "ProcEventEntry", sceneId, selfId, NPCId, x260000_g_MissionIdNext )	
end

function x260000_GetBonus( sceneId, selfId,NpcID)
	  if x260000_g_ExpBonus > 0 then
	  local addexpture = x260000_g_ExpBonus*GetLevel(sceneId, selfId)
			AddExp(sceneId, selfId, addexpture);
  	end
		if x260000_g_BonusMoney1 > 0 then
	    AddMoney( sceneId, selfId, 1, x260000_g_BonusMoney1 )
	  end
		if x260000_g_BonusMoney2 > 0 then
	    AddMoney( sceneId, selfId, 0, x260000_g_BonusMoney2 )
	  end
		if x260000_g_BonusMoney3 > 0 then
	    AddMoney( sceneId, selfId, 3, x260000_g_BonusMoney3 )
		end
		if x260000_g_BonusMoney4 > 0 then
		local nRongYu = GetRongYu( sceneId, selfId )
			nRongYu = nRongYu + x260000_g_BonusMoney4
			SetRongYu( sceneId, selfId, nRongYu )
		end
		if x260000_g_BonusMoney5 > 0 then
			local nShengWang = GetShengWang( sceneId, selfId )
			nShengWang = nShengWang + x260000_g_BonusMoney5
			SetShengWang( sceneId, selfId, nShengWang )
		end
		if x260000_g_BonusMoney6 > 0 then
			AddHonor(sceneId,selfId,x260000_g_BonusMoney6)
		end
end

function x260000_Msg2toplayer( sceneId, selfId,type)
		if type == 0 then
				Msg2Player(sceneId, selfId, "您接受了任务"..x260000_g_MissionName.."！", 0, 2)
		  	Msg2Player(sceneId, selfId, "您接受了任务"..x260000_g_MissionName.."！", 0, 3)
		elseif type == 1 then
				Msg2Player(sceneId, selfId, "您放弃了任务"..x260000_g_MissionName.."！", 0, 2)
				Msg2Player(sceneId, selfId, "您放弃了任务"..x260000_g_MissionName.."！", 0, 3)
		elseif type == 2 then
				Msg2Player(sceneId, selfId, "您完成了任务"..x260000_g_MissionName.."！", 0, 2)
				Msg2Player(sceneId, selfId, "您完成了任务"..x260000_g_MissionName.."！", 0, 3)
				local expAward =x260000_g_ExpBonus*GetLevel(sceneId, selfId)
				Msg2Player(sceneId, selfId, "#Y获得#R经验"..expAward.."#Y的奖励", 0, 2)
		end
end

function x260000_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
end


function x260000_ProcAreaEntered(sceneId, selfId, zoneId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "ProcAreaEntered",sceneId, selfId, zoneId, MissionId )	

end

function x260000_ProcTiming(sceneId, selfId, ScriptId, MissionId)
	 CallScriptFunction( MISSION_SCRIPT, "ProcTiming",sceneId, selfId, ScriptId, MissionId )
		
end

function x260000_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcAreaLeaved",sceneId, selfId, ScriptId, MissionId)
end

function x260000_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcQuestItemChanged",sceneId, selfId, itemdataId, MissionId )
end


function x260000_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
	  local bFind  = 0
    for i ,item in x260000_g_NpcGUID do
        if item.guid == npcGuid then
            bFind = 1
            break
        end
    end
    if bFind == 0 then
        return
    end
		if IsHaveQuest(sceneId,selfId, x260000_g_MissionId) > 0 then
				local state = GetQuestStateNM(sceneId,selfId,npcId,x260000_g_MissionId)
				AddQuestTextNM( sceneId, selfId, npcId, x260000_g_MissionId, state, -1 )
		end
end

function x260000_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x260000_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x260000_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x260000_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x260000_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x260000_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end

function x260000_ProcQuestLogRefresh( sceneId,selfId,missionId)

    BeginQuestEvent(sceneId)
    AddQuestExpBonus(sceneId, x260000_g_ExpBonus*GetLevel(sceneId, selfId) )
		EndQuestEvent()
		DispatchQuestLogUpdate(sceneId, selfId, x260000_g_MissionId);

end