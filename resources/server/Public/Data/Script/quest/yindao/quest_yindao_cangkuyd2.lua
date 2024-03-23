--有存有取

--MisDescBegin
x203776_g_ScriptId = 203776
x203776_g_MissionIdPre =2697
x203776_g_MissionId = 4242
x203776_g_LevelLess	= 	20
x203776_g_MissionIdNext = 4206
x203776_g_Name	={}
x203776_g_ExtTarget={{type=20,n=1,target="找到@npc_129062"}}
x203776_g_MissionName="【个人】有存有取"
x203776_g_MissionInfo="\t看你的行囊已经被撑得变了形，把东西全带在身上，是不是很不方便？去找@npc_129062吧，他能够帮你解决这一系列的问题！"  --任务描述
x203776_g_MissionTarget=""		
x203776_g_MissionCompleted="\t我这里提供寄存服务，你可以储存一些不必时刻随身携带的东西，比如宝石或者平常不用的装备和材料等。当然，如果你想拥有足够大的空间的话，我还可以为你开启更大的仓库，不过这要你有足够的现金才行。 "					--完成任务npc说话的话
x203776_g_ContinueInfo=""
x203776_g_MissionHelp =	""
x203776_g_DemandItem ={}
x203776_g_ExpBonus = 11000
x203776_g_BonusMoney1 =500
x203776_g_BonusMoney2 =0
x203776_g_BonusMoney3 =0
x203776_g_BonusMoney4 =0
x203776_g_BonusMoney5 =0
x203776_g_BonusMoney6 =0
x203776_g_BonusItem	=	{}
x203776_g_BonusChoiceItem ={}
x203776_g_NpcGUID ={{ guid = 129062, name = "巴图存"} }
--MisDescEnd
--**********************************
x203776_g_MaxLevel   = 40

function x203776_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
    local level = GetLevel(sceneId, selfId)
	if level < x203776_g_LevelLess or level >= x203776_g_MaxLevel then
		return
	end

	if IsQuestHaveDone(sceneId, selfId, x203776_g_MissionId) > 0 then
		return 
	end
	if IsQuestHaveDone(sceneId, selfId, x203776_g_MissionIdPre)> 0 then
						if IsHaveQuest(sceneId,selfId, x203776_g_MissionId) <= 0 then
								local state = GetQuestStateNM(sceneId,selfId,NPCId,x203776_g_MissionId)
								AddQuestTextNM( sceneId, selfId, NPCId, x203776_g_MissionId, state, -1 )
						end
	end
end

function x203776_DispatchMissionInfo( sceneId, selfId, NPCId )
		if x203776_g_ExpBonus> 0 then
			AddQuestExpBonus(sceneId, x203776_g_ExpBonus )
		end
		if x203776_g_BonusMoney1 > 0 then
			AddQuestMoneyBonus1(sceneId, x203776_g_BonusMoney1 )
		end
		if x203776_g_BonusMoney2 > 0 then
			AddQuestMoneyBonus2(sceneId, x203776_g_BonusMoney2 )
		end
		if x203776_g_BonusMoney3 > 0 then
			AddQuestMoneyBonus3(sceneId, x203776_g_BonusMoney3 )
		end
		if x203776_g_BonusMoney4 > 0 then
			AddQuestMoneyBonus4(sceneId, x203776_g_BonusMoney4 )
		end
		if x203776_g_BonusMoney5 > 0 then
			AddQuestMoneyBonus5(sceneId, x203776_g_BonusMoney5 )
		end
		if x203776_g_BonusMoney6 > 0 then
			AddQuestMoneyBonus6(sceneId, x203776_g_BonusMoney6 )
		end
		for i, item in x203776_g_BonusItem do
		   	AddQuestItemBonus(sceneId, item.item, item.n)
	  end
		for i, item in x203776_g_BonusChoiceItem do
	    	AddQuestRadioItemBonus(sceneId, item.item, item.n)
	  end
end
--**********************************

function x203776_ProcEventEntry(sceneId, selfId, NPCId, MissionId)	--点击该任务后执行此脚本
	if IsQuestHaveDone(sceneId, selfId, x203776_g_MissionId) > 0 then
		return 
	end
	if IsHaveQuest(sceneId,selfId, x203776_g_MissionId) > 0 then
			if x203776_CheckSubmit(sceneId, selfId, NPCId) <= 0 then
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x203776_g_MissionName)
						AddQuestText(sceneId,x203776_g_MissionCompleted)
						EndQuestEvent()
						DispatchQuestEventList(sceneId, selfId, NPCId, x203776_g_ScriptId, x203776_g_MissionId);
			else
						CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 39,0 )
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x203776_g_MissionName)
						AddQuestText(sceneId,x203776_g_MissionCompleted)
						AddQuestText(sceneId," ")
						x203776_DispatchMissionInfo( sceneId, selfId, NPCId )
						EndQuestEvent()
						DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x203776_g_ScriptId, x203776_g_MissionId);
			end
  elseif x203776_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
			BeginQuestEvent(sceneId)
	  	AddQuestText(sceneId,"#Y"..x203776_g_MissionName)
			AddQuestText(sceneId,x203776_g_MissionInfo)
			AddQuestText( sceneId,"#Y任务目标：")
			for i, item in x203776_g_ExtTarget do
					AddQuestText( sceneId,item.target)
			end 
			if x203776_g_MissionHelp ~= "" then
				AddQuestText(sceneId,"\n#G小提示:#W")
				AddQuestText(sceneId,x203776_g_MissionHelp )
			end
			x203776_DispatchMissionInfo( sceneId, selfId, NPCId )
	  	EndQuestEvent()
			DispatchQuestInfoNM(sceneId, selfId, NPCId, x203776_g_ScriptId, x203776_g_MissionId);
  end
	
end
--**********************************

function x203776_ProcAcceptCheck(sceneId, selfId, NPCId)
		
						return 1
		

end
--**********************************
function x203776_CheckSubmit( sceneId, selfId, NPCId)

	        return 1
	
end
--**********************************
function x203776_ProcQuestAccept( sceneId, selfId, NPCId, MissionId )
		if IsQuestHaveDone(sceneId, selfId, x203776_g_MissionId) > 0 then
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
		local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId,x203776_g_MissionId  )
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
		
		if x203776_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
					local retmiss = AddQuest( sceneId, selfId, x203776_g_MissionId, x203776_g_ScriptId, 0, 0, 0,1)
					if retmiss ==0 then
						Msg2Player(sceneId, selfId, "接受任务失败！", 0, 3)
						return 0
					else
		  			x203776_Msg2toplayer( sceneId, selfId,0)
						--if x203776_CheckSubmit(sceneId, selfId, NPCId) > 0 then
								local misIndex = GetQuestIndexByID(sceneId,selfId,x203776_g_MissionId)                                                  
	    					SetQuestByIndex(sceneId,selfId,misIndex,0,1)
	    					SetQuestByIndex(sceneId,selfId,misIndex,7,1)
	    			
	    			--end
		  		end
	 	end                                                                    
	     
end
--**********************************

function x203776_ProcQuestAbandon(sceneId, selfId, MissionId)
		if IsHaveQuest(sceneId,selfId, x203776_g_MissionId) <= 0 then
				return 
		end
		DelQuest(sceneId, selfId, x203776_g_MissionId)
	  x203776_Msg2toplayer( sceneId, selfId,1)
	  CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 39,0 )
			
end
--**********************************
function x203776_CheckPlayerBagFull( sceneId ,selfId,selectRadioId )
	local result = 1
	local j = 0
	local bAdd = 0 --是否已经在固定物品奖励添加检测中已经检查出包裹已满
	BeginAddItem(sceneId)
	for j, item in x203776_g_BonusItem do
		AddItem( sceneId, item.item, item.n )
  end
  for j, item in x203776_g_BonusChoiceItem do
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
function x203776_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)
	if IsHaveQuest(sceneId,selfId, x203776_g_MissionId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"您没有这个任务！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x203776_CheckSubmit( sceneId, selfId, NPCId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"您没有达到完成条件！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x203776_CheckPlayerBagFull( sceneId ,selfId,selectRadioId ) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"包裹已满！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif DelQuest(sceneId, selfId, x203776_g_MissionId) > 0 then
				x203776_Msg2toplayer( sceneId, selfId,2)
				QuestCom(sceneId, selfId, x203776_g_MissionId)
				x203776_GetBonus( sceneId, selfId,NPCId)
				BeginAddItem(sceneId)
				for i, item in x203776_g_BonusItem do
 						AddItem( sceneId, item.item, item.n )
				end
				for i, item in x203776_g_BonusChoiceItem do
						if item.item == selectRadioId then
	    			    AddItem( sceneId, item.item, item.n )
						end
    		end
    		EndAddItem(sceneId,selfId)
    		--AddItemListToPlayer(sceneId,selfId)
   end
  		CallScriptFunction( MISSION_SCRIPT, "ProcEventEntry", sceneId, selfId, NPCId, x203776_g_MissionIdNext )	
end

function x203776_GetBonus( sceneId, selfId,NpcID)
	  if x203776_g_ExpBonus > 0 then
			AddExp(sceneId, selfId, x203776_g_ExpBonus);
  	end
		if x203776_g_BonusMoney1 > 0 then
	    AddMoney( sceneId, selfId, 1, x203776_g_BonusMoney1 )
	  end
		if x203776_g_BonusMoney2 > 0 then
	    AddMoney( sceneId, selfId, 0, x203776_g_BonusMoney2 )
	  end
		if x203776_g_BonusMoney3 > 0 then
	    AddMoney( sceneId, selfId, 3, x203776_g_BonusMoney3 )
		end
		if x203776_g_BonusMoney4 > 0 then
		local nRongYu = GetRongYu( sceneId, selfId )
			nRongYu = nRongYu + x203776_g_BonusMoney4
			SetRongYu( sceneId, selfId, nRongYu )
		end
		if x203776_g_BonusMoney5 > 0 then
			local nShengWang = GetShengWang( sceneId, selfId )
			nShengWang = nShengWang + x203776_g_BonusMoney5
			SetShengWang( sceneId, selfId, nShengWang )
		end
		if x203776_g_BonusMoney6 > 0 then
			AddHonor(sceneId,selfId,x203776_g_BonusMoney6)
		end
end

function x203776_Msg2toplayer( sceneId, selfId,type)
		if type == 0 then
				Msg2Player(sceneId, selfId, "您接受了任务"..x203776_g_MissionName.."！", 0, 2)
		  	Msg2Player(sceneId, selfId, "您接受了任务"..x203776_g_MissionName.."！", 0, 3)
		elseif type == 1 then
				Msg2Player(sceneId, selfId, "您放弃了任务"..x203776_g_MissionName.."！", 0, 2)
				Msg2Player(sceneId, selfId, "您放弃了任务"..x203776_g_MissionName.."！", 0, 3)
		elseif type == 2 then
				Msg2Player(sceneId, selfId, "您完成了任务"..x203776_g_MissionName.."！", 0, 2)
				Msg2Player(sceneId, selfId, "您完成了任务"..x203776_g_MissionName.."！", 0, 3)
				if x203776_g_ExpBonus > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R经验"..x203776_g_ExpBonus.."#Y的奖励", 0, 2)
  			end
				if x203776_g_BonusMoney1 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y获得#R银卡"..x203776_g_BonusMoney1.."文#Y的奖励", 0, 2)
	  		end
				if x203776_g_BonusMoney2 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y获得#R现银"..x203776_g_BonusMoney2.."文#Y的奖励", 0, 2)
	  		end
				if x203776_g_BonusMoney3 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y获得#R金卡"..x203776_g_BonusMoney3.."文#Y的奖励", 0, 2)
				end
				if x203776_g_BonusMoney4 > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R朝廷声望值"..x203776_g_BonusMoney4.."#Y的奖励", 0, 2)
				end
				if x203776_g_BonusMoney5 > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R声望"..x203776_g_BonusMoney5.."#Y的奖励", 0, 2)
				end
				if x203776_g_BonusMoney6 > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R荣誉"..x203776_g_BonusMoney6.."#Y的奖励", 0, 2)
				end
		end
end

function x203776_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
end


function x203776_ProcAreaEntered(sceneId, selfId, zoneId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "ProcAreaEntered",sceneId, selfId, zoneId, MissionId )	

end

function x203776_ProcTiming(sceneId, selfId, ScriptId, MissionId)
	 CallScriptFunction( MISSION_SCRIPT, "ProcTiming",sceneId, selfId, ScriptId, MissionId )
		
end

function x203776_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcAreaLeaved",sceneId, selfId, ScriptId, MissionId)
end

function x203776_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcQuestItemChanged",sceneId, selfId, itemdataId, MissionId )
end


function x203776_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
	  local bFind  = 0
    for i ,item in x203776_g_NpcGUID do
        if item.guid == npcGuid then
            bFind = 1
            break
        end
    end
    if bFind == 0 then
        return
    end
		if IsHaveQuest(sceneId,selfId, x203776_g_MissionId) > 0 then
				local state = GetQuestStateNM(sceneId,selfId,npcId,x203776_g_MissionId)
				AddQuestTextNM( sceneId, selfId, npcId, x203776_g_MissionId, state, -1 )
				CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 39,1 )
		end
end

function x203776_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x203776_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x203776_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x203776_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x203776_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x203776_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end