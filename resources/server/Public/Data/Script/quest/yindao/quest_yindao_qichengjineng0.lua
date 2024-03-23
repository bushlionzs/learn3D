--骑乘技能

--MisDescBegin
x203809_g_ScriptId = 203809
x203809_g_MissionIdPre =-1
x203809_g_MissionId = 4248
x203809_g_LevelLess	= 30
x203809_g_MissionIdNext = {4312,4313,4314,4315,4316,4317,4318,4319,4320,4321,4322,4323}
x203809_g_Name	={}
x203809_g_ExtTarget={{type=20,n=1,target="找到@npc_123742"}}
x203809_g_MissionName="【个人】骑乘技能"
x203809_g_MissionInfo="\t看你的样子似乎还不知道啊，你的骑乘也是可以学习技能的，一匹拥有绝佳技能的骑乘，可以让你如虎添翼。王城的@npc_123742可以让你的骑乘学会新的技能，价格也不贵，你可以去他那里看看。"  --任务描述
x203809_g_MissionTarget=""		
x203809_g_MissionCompleted="\t骑乘的技能也有高低之分，要学习更高级的技能，需要有低级技能作为基础。 "					--完成任务npc说话的话
x203809_g_ContinueInfo=""
x203809_g_MissionHelp =	""
x203809_g_DemandItem ={}
x203809_g_ExpBonus = 142000
x203809_g_BonusMoney1 =200
x203809_g_BonusMoney2 =0
x203809_g_BonusMoney3 =0
x203809_g_BonusMoney4 =0
x203809_g_BonusMoney5 =0
x203809_g_BonusMoney6 =0
x203809_g_BonusItem	=	{}
x203809_g_BonusChoiceItem =	{}
x203809_g_NpcGUID ={{ guid = 123742, name = "骑乘技能"} }
--MisDescEnd     
x203809_g_ScriptIdNext =203702
--**********************************
-- 最大等级
x203809_g_MaxLevel      = 49

function x203809_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
    local level = GetLevel(sceneId, selfId)
	if level < x203809_g_LevelLess or level >= x203809_g_MaxLevel then
		return
	end
	

	if IsQuestHaveDone(sceneId, selfId, x203809_g_MissionId) > 0 then
		return 
	end
	--if IsQuestHaveDone(sceneId, selfId, x203809_g_MissionIdPre)> 0 then
		
			if IsHaveQuest(sceneId,selfId, x203809_g_MissionId) <= 0 then						
				local state = GetQuestStateNM(sceneId,selfId,NPCId,x203809_g_MissionId)
				AddQuestTextNM( sceneId, selfId, NPCId, x203809_g_MissionId, state, -1 )
				 CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 5,1 ) 		
			end
	end
		

function x203809_DispatchMissionInfo( sceneId, selfId, NPCId )
		if x203809_g_ExpBonus> 0 then
			AddQuestExpBonus(sceneId, x203809_g_ExpBonus )
		end
		if x203809_g_BonusMoney1 > 0 then
			AddQuestMoneyBonus1(sceneId, x203809_g_BonusMoney1 )
		end
		if x203809_g_BonusMoney2 > 0 then
			AddQuestMoneyBonus2(sceneId, x203809_g_BonusMoney2 )
		end
		if x203809_g_BonusMoney3 > 0 then
			AddQuestMoneyBonus3(sceneId, x203809_g_BonusMoney3 )
		end
		if x203809_g_BonusMoney4 > 0 then
			AddQuestMoneyBonus4(sceneId, x203809_g_BonusMoney4 )
		end
		if x203809_g_BonusMoney5 > 0 then
			AddQuestMoneyBonus5(sceneId, x203809_g_BonusMoney5 )
		end
		if x203809_g_BonusMoney6 > 0 then
			AddQuestMoneyBonus6(sceneId, x203809_g_BonusMoney6 )
		end
		for i, item in x203809_g_BonusItem do
		   	AddQuestItemBonus(sceneId, item.item, item.n)
	  end
		for i, item in x203809_g_BonusChoiceItem do
	    	AddQuestRadioItemBonus(sceneId, item.item, item.n)
	  end
end
--**********************************

function x203809_ProcEventEntry(sceneId, selfId, NPCId, MissionId)	--点击该任务后执行此脚本
	if IsQuestHaveDone(sceneId, selfId, x203809_g_MissionId) > 0 then
		return 
	end
	if IsHaveQuest(sceneId,selfId, x203809_g_MissionId) > 0 then
			if x203809_CheckSubmit(sceneId, selfId, NPCId) <= 0 then
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x203809_g_MissionName)
						AddQuestText(sceneId,x203809_g_MissionCompleted)
						EndQuestEvent()
						DispatchQuestEventList(sceneId, selfId, NPCId, x203809_g_ScriptId, x203809_g_MissionId);
			else
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x203809_g_MissionName)
						AddQuestText(sceneId,x203809_g_MissionCompleted)
						AddQuestText(sceneId," ")
						--CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 3,1 )  
						x203809_DispatchMissionInfo( sceneId, selfId, NPCId )
						EndQuestEvent()
						CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 1,0 )  
						DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x203809_g_ScriptId, x203809_g_MissionId);
			end
  elseif x203809_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
			BeginQuestEvent(sceneId)
	  	AddQuestText(sceneId,"#Y"..x203809_g_MissionName)
			AddQuestText(sceneId,x203809_g_MissionInfo)
			AddQuestText( sceneId,"#Y任务目标：") 		  
			for i, item in x203809_g_ExtTarget do  	
			AddQuestText( sceneId,item.target)		
			end 
			if x203809_g_MissionHelp ~= "" then
				AddQuestText(sceneId,"\n#G小提示:#W")
				AddQuestText(sceneId,x203809_g_MissionHelp )
			end
			x203809_DispatchMissionInfo( sceneId, selfId, NPCId )
	  	EndQuestEvent()
			DispatchQuestInfoNM(sceneId, selfId, NPCId, x203809_g_ScriptId, x203809_g_MissionId);
			CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 5,0 )
			CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 4,1 ) 	
  end
	
end
--**********************************

function x203809_ProcAcceptCheck(sceneId, selfId, NPCId)
		
						return 1
		

end
--**********************************
function x203809_CheckSubmit( sceneId, selfId, NPCId)

	        return 1
	
end
--**********************************
function x203809_ProcQuestAccept( sceneId, selfId, NPCId, MissionId )
		if IsQuestHaveDone(sceneId, selfId, x203809_g_MissionId) > 0 then
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
		local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId,x203809_g_MissionId  )
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
		if x203809_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
					local retmiss = AddQuest( sceneId, selfId, x203809_g_MissionId, x203809_g_ScriptId, 0, 0, 0,1)
					if retmiss ==0 then                                          ------添加失败 ==0 ，1 成功                                                                  
						Msg2Player(sceneId, selfId, "接受任务失败！", 0, 3)
						return 0
					else
		  			x203809_Msg2toplayer( sceneId, selfId,0)
						--if x203809_CheckSubmit(sceneId, selfId, NPCId) > 0 then
								local misIndex = GetQuestIndexByID(sceneId,selfId,x203809_g_MissionId)       ---- 取得任务状态                                               
	    					SetQuestByIndex(sceneId,selfId,misIndex,0,1)                                 ---0，1 控制 0/1
	    					SetQuestByIndex(sceneId,selfId,misIndex,7,1)                                 ---7,1  将任务状态置为完成
	    					CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 1,1 )   
	    					--CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 4,1 )   
	    			--end
		  		end
	 	end                                                                    
	     
end
--**********************************

function x203809_ProcQuestAbandon(sceneId, selfId, MissionId)
		if IsHaveQuest(sceneId,selfId, x203809_g_MissionId) <= 0 then
				return 
		end
		DelQuest(sceneId, selfId, x203809_g_MissionId)
	  x203809_Msg2toplayer( sceneId, selfId,1) 
			
end
--**********************************
function x203809_CheckPlayerBagFull( sceneId ,selfId,selectRadioId )
	local result = 1
	local j = 0
	local bAdd = 0 --是否已经在固定物品奖励添加检测中已经检查出包裹已满
	BeginAddItem(sceneId)
	for j, item in x203809_g_BonusItem do
		AddItem( sceneId, item.item, item.n )
  end
  for j, item in x203809_g_BonusChoiceItem do
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
function x203809_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)
	if IsHaveQuest(sceneId,selfId, x203809_g_MissionId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"您没有这个任务！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x203809_CheckSubmit( sceneId, selfId, NPCId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"您没有达到完成条件！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x203809_CheckPlayerBagFull( sceneId ,selfId,selectRadioId ) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"包裹已满！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif DelQuest(sceneId, selfId, x203809_g_MissionId) > 0 then
				x203809_Msg2toplayer( sceneId, selfId,2)
				QuestCom(sceneId, selfId, x203809_g_MissionId)
				x203809_GetBonus( sceneId, selfId,NPCId)
				BeginAddItem(sceneId)
				for i, item in x203809_g_BonusItem do
 						AddItem( sceneId, item.item, item.n )
				end
				for i, item in x203809_g_BonusChoiceItem do
						if item.item == selectRadioId then
	    			    AddItem( sceneId, item.item, item.n )
						end
    		end
    		EndAddItem(sceneId,selfId)
    		--AddItemListToPlayer(sceneId,selfId)
   end
   local zhiye =GetZhiye( sceneId, selfId)+1
   CallScriptFunction( x203809_g_ScriptIdNext, "ProcEventEntry", sceneId, selfId, NPCId, x203809_g_MissionIdNext[zhiye] )	
end

function x203809_GetBonus( sceneId, selfId,NpcID)
	  if x203809_g_ExpBonus > 0 then
			AddExp(sceneId, selfId, x203809_g_ExpBonus);
  	end
		if x203809_g_BonusMoney1 > 0 then
	    AddMoney( sceneId, selfId, 1, x203809_g_BonusMoney1 )
	  end
		if x203809_g_BonusMoney2 > 0 then
	    AddMoney( sceneId, selfId, 0, x203809_g_BonusMoney2 )
	  end
		if x203809_g_BonusMoney3 > 0 then
	    AddMoney( sceneId, selfId, 3, x203809_g_BonusMoney3 )
		end
		if x203809_g_BonusMoney4 > 0 then
		local nRongYu = GetRongYu( sceneId, selfId )
			nRongYu = nRongYu + x203809_g_BonusMoney4
			SetRongYu( sceneId, selfId, nRongYu )
		end
		if x203809_g_BonusMoney5 > 0 then
			local nShengWang = GetShengWang( sceneId, selfId )
			nShengWang = nShengWang + x203809_g_BonusMoney5
			SetShengWang( sceneId, selfId, nShengWang )
		end
		if x203809_g_BonusMoney6 > 0 then
			AddHonor(sceneId,selfId,x203809_g_BonusMoney6)
		end
end

function x203809_Msg2toplayer( sceneId, selfId,type)
		if type == 0 then
				Msg2Player(sceneId, selfId, "您接受了任务"..x203809_g_MissionName.."！", 0, 2)
		  	Msg2Player(sceneId, selfId, "您接受了任务"..x203809_g_MissionName.."！", 0, 3)
		elseif type == 1 then
				Msg2Player(sceneId, selfId, "您放弃了任务"..x203809_g_MissionName.."！", 0, 2)
				Msg2Player(sceneId, selfId, "您放弃了任务"..x203809_g_MissionName.."！", 0, 3)
		elseif type == 2 then
				Msg2Player(sceneId, selfId, "您完成了任务"..x203809_g_MissionName.."！", 0, 2)
				Msg2Player(sceneId, selfId, "您完成了任务"..x203809_g_MissionName.."！", 0, 3)
				if x203809_g_ExpBonus > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R经验"..x203809_g_ExpBonus.."#Y的奖励", 0, 2)
  			end
				if x203809_g_BonusMoney1 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y获得#R银卡"..x203809_g_BonusMoney1.."文#Y的奖励", 0, 2)
	  		end
				if x203809_g_BonusMoney2 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y获得#R现银"..x203809_g_BonusMoney2.."文#Y的奖励", 0, 2)
	  		end
				if x203809_g_BonusMoney3 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y获得#R金卡"..x203809_g_BonusMoney3.."文#Y的奖励", 0, 2)
				end
				if x203809_g_BonusMoney4 > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R朝廷声望值"..x203809_g_BonusMoney4.."#Y的奖励", 0, 2)
				end
				if x203809_g_BonusMoney5 > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R声望"..x203809_g_BonusMoney5.."#Y的奖励", 0, 2)
				end
				if x203809_g_BonusMoney6 > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R荣誉"..x203809_g_BonusMoney6.."#Y的奖励", 0, 2)
				end
		end
end

function x203809_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
end


function x203809_ProcAreaEntered(sceneId, selfId, zoneId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "ProcAreaEntered",sceneId, selfId, zoneId, MissionId )	

end

function x203809_ProcTiming(sceneId, selfId, ScriptId, MissionId)
	 CallScriptFunction( MISSION_SCRIPT, "ProcTiming",sceneId, selfId, ScriptId, MissionId )
		
end

function x203809_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcAreaLeaved",sceneId, selfId, ScriptId, MissionId)
end

function x203809_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcQuestItemChanged",sceneId, selfId, itemdataId, MissionId )
end


function x203809_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
	  local bFind  = 0
    for i ,item in x203809_g_NpcGUID do
        if item.guid == npcGuid then
            bFind = 1
            break
        end
    end
    if bFind == 0 then
        return
    end
		if IsHaveQuest(sceneId,selfId, x203809_g_MissionId) > 0 then
				local state = GetQuestStateNM(sceneId,selfId,npcId,x203809_g_MissionId)        ---取得任务状态 ，根据状态添加按钮 AddQuestTextNM
				AddQuestTextNM( sceneId, selfId, npcId, x203809_g_MissionId, state, -1 )
		end
end

function x203809_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x203809_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x203809_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x203809_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x203809_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x203809_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end