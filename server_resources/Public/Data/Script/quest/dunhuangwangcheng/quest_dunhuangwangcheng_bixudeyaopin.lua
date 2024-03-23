--【主线】必须的药品

--MisDescBegin
x256241_g_ScriptId = 256241
x256241_g_MissionIdPre =1541
x256241_g_MissionId = 1542
x256241_g_LevelLess	= 	10
x256241_g_MissionIdNext = {3099,3100,3101,3102,3103,3104}
x256241_g_Name	={}
x256241_g_ExtTarget={{type=20,n=1,target="找到@npc_138539"}}
x256241_g_MissionName="【主线】必须的药品"
x256241_g_MissionInfo="\t如果有需要欢迎随时来找我，我看行走江湖的行头你也置办得差不多了，只是还少一样疗伤的药品，行走江湖，就算你武功再好也难免会挨刀，@npc_138539那里卖的药品价格便宜效果非凡，你不妨去她那里看看。"  --任务描述
x256241_g_MissionTarget=""		
x256241_g_MissionCompleted="优质的疗伤药品是生存的保证！我这里药品的质量绝对是最好的，能够让你大伤变小伤，小伤全治愈，一旦拥有，别无所求！ "					--完成任务npc说话的话
x256241_g_ContinueInfo=""
x256241_g_MissionHelp =	""
x256241_g_DemandItem ={}
x256241_g_BonusMoney1 =200
x256241_g_BonusMoney2 =0
x256241_g_BonusMoney3 =0
x256241_g_BonusMoney4 =0
x256241_g_BonusMoney5 =0
x256241_g_BonusMoney6 =0
x256241_g_BonusItem	=	{{item=12010002,n=5}}
x256241_g_BonusChoiceItem ={}
x256241_g_ExpBonus = 1400
x256241_g_NpcGUID ={{ guid = 138539, name = "药店商人"} }
--MisDescEnd     
x256241_g_ScriptIdNext ={203428,203429,203430,203431,203432,203433}
--**********************************

function x256241_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
	if IsQuestHaveDone(sceneId, selfId, x256241_g_MissionId) > 0 then
		return 
	end
	if IsQuestHaveDone(sceneId, selfId, x256241_g_MissionIdPre)> 0 then
		
			if IsHaveQuest(sceneId,selfId, x256241_g_MissionId) <= 0 then						
				local state = GetQuestStateNM(sceneId,selfId,NPCId,x256241_g_MissionId)
				AddQuestTextNM( sceneId, selfId, NPCId, x256241_g_MissionId, state, -1 )
				 CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 5,1 ) 		
			end
	end
		
end

function x256241_DispatchMissionInfo( sceneId, selfId, NPCId )
		if x256241_g_ExpBonus> 0 then
			AddQuestExpBonus(sceneId, x256241_g_ExpBonus )
		end
		if x256241_g_BonusMoney1 > 0 then
			AddQuestMoneyBonus1(sceneId, x256241_g_BonusMoney1 )
		end
		if x256241_g_BonusMoney2 > 0 then
			AddQuestMoneyBonus2(sceneId, x256241_g_BonusMoney2 )
		end
		if x256241_g_BonusMoney3 > 0 then
			AddQuestMoneyBonus3(sceneId, x256241_g_BonusMoney3 )
		end
		if x256241_g_BonusMoney4 > 0 then
			AddQuestMoneyBonus4(sceneId, x256241_g_BonusMoney4 )
		end
		if x256241_g_BonusMoney5 > 0 then
			AddQuestMoneyBonus5(sceneId, x256241_g_BonusMoney5 )
		end
		if x256241_g_BonusMoney6 > 0 then
			AddQuestMoneyBonus6(sceneId, x256241_g_BonusMoney6 )
		end
		for i, item in x256241_g_BonusItem do
		   	AddQuestItemBonus(sceneId, item.item, item.n)
	  end
		for i, item in x256241_g_BonusChoiceItem do
	    	AddQuestRadioItemBonus(sceneId, item.item, item.n)
	  end
end
--**********************************

function x256241_ProcEventEntry(sceneId, selfId, NPCId, MissionId)	--点击该任务后执行此脚本
	if IsQuestHaveDone(sceneId, selfId, x256241_g_MissionId) > 0 then
		return 
	end
	if IsHaveQuest(sceneId,selfId, x256241_g_MissionId) > 0 then
			if x256241_CheckSubmit(sceneId, selfId, NPCId) <= 0 then
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x256241_g_MissionName)
						AddQuestText(sceneId,x256241_g_MissionCompleted)
						EndQuestEvent()
						DispatchQuestEventList(sceneId, selfId, NPCId, x256241_g_ScriptId, x256241_g_MissionId);
			else
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x256241_g_MissionName)
						AddQuestText(sceneId,x256241_g_MissionCompleted)
						AddQuestText(sceneId," ")
						CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 3,1 )  
						x256241_DispatchMissionInfo( sceneId, selfId, NPCId )
						EndQuestEvent()
						CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 1,0 )  
						DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x256241_g_ScriptId, x256241_g_MissionId);
			end
  elseif x256241_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
			BeginQuestEvent(sceneId)
	  	AddQuestText(sceneId,"#Y"..x256241_g_MissionName)
			AddQuestText(sceneId,x256241_g_MissionInfo)
			AddQuestText( sceneId,"#Y任务目标：") 		  
			for i, item in x256241_g_ExtTarget do  	
			AddQuestText( sceneId,item.target)		
			end 
			if x256241_g_MissionHelp ~= "" then
				AddQuestText(sceneId,"\n#G小提示:#W")
				AddQuestText(sceneId,x256241_g_MissionHelp )
			end
			x256241_DispatchMissionInfo( sceneId, selfId, NPCId )
	  	EndQuestEvent()
			DispatchQuestInfoNM(sceneId, selfId, NPCId, x256241_g_ScriptId, x256241_g_MissionId);
			CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 5,0 )
			CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 4,1 ) 	
  end
	
end
--**********************************

function x256241_ProcAcceptCheck(sceneId, selfId, NPCId)
		
						return 1
		

end
--**********************************
function x256241_CheckSubmit( sceneId, selfId, NPCId)

	        return 1
	
end
--**********************************
function x256241_ProcQuestAccept( sceneId, selfId, NPCId, MissionId )
		if IsQuestHaveDone(sceneId, selfId, x256241_g_MissionId) > 0 then
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
		local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId,x256241_g_MissionId  )
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
		if x256241_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
					local retmiss = AddQuest( sceneId, selfId, x256241_g_MissionId, x256241_g_ScriptId, 0, 0, 0,1)
					if retmiss ==0 then                                          ------添加失败 ==0 ，1 成功                                                                  
						Msg2Player(sceneId, selfId, "接受任务失败！", 0, 3)
						return 0
					else
		  			x256241_Msg2toplayer( sceneId, selfId,0)
						--if x256241_CheckSubmit(sceneId, selfId, NPCId) > 0 then
								local misIndex = GetQuestIndexByID(sceneId,selfId,x256241_g_MissionId)       ---- 取得任务状态                                               
	    					SetQuestByIndex(sceneId,selfId,misIndex,0,1)                                 ---0，1 控制 0/1
	    					SetQuestByIndex(sceneId,selfId,misIndex,7,1)                                 ---7,1  将任务状态置为完成
	    					CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 1,1 )   
	    					--CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 4,1 )   
	    			--end
		  		end
	 	end                                                                    
	     
end
--**********************************

function x256241_ProcQuestAbandon(sceneId, selfId, MissionId)
		if IsHaveQuest(sceneId,selfId, x256241_g_MissionId) <= 0 then
				return 
		end
		DelQuest(sceneId, selfId, x256241_g_MissionId)
	  x256241_Msg2toplayer( sceneId, selfId,1) 
			
end
--**********************************
function x256241_CheckPlayerBagFull( sceneId ,selfId,selectRadioId )
	local result = 1
	local j = 0
	local bAdd = 0 --是否已经在固定物品奖励添加检测中已经检查出包裹已满
	BeginAddItem(sceneId)
	for j, item in x256241_g_BonusItem do
		AddItem( sceneId, item.item, item.n )
  end
  for j, item in x256241_g_BonusChoiceItem do
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
function x256241_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)
	if IsHaveQuest(sceneId,selfId, x256241_g_MissionId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"您没有这个任务！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x256241_CheckSubmit( sceneId, selfId, NPCId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"您没有达到完成条件！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x256241_CheckPlayerBagFull( sceneId ,selfId,selectRadioId ) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"包裹已满！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif DelQuest(sceneId, selfId, x256241_g_MissionId) > 0 then
				x256241_Msg2toplayer( sceneId, selfId,2)
				QuestCom(sceneId, selfId, x256241_g_MissionId)
				x256241_GetBonus( sceneId, selfId,NPCId)
				BeginAddItem(sceneId)
				for i, item in x256241_g_BonusItem do
 						AddItem( sceneId, item.item, item.n )
				end
				for i, item in x256241_g_BonusChoiceItem do
						if item.item == selectRadioId then
	    			    AddItem( sceneId, item.item, item.n )
						end
    		end
    		EndAddItem(sceneId,selfId)
    		--AddItemListToPlayer(sceneId,selfId)
   end
   local zhiye =GetZhiye( sceneId, selfId)+1
   CallScriptFunction( x256241_g_ScriptIdNext[zhiye], "ProcEventEntry", sceneId, selfId, NPCId, x256241_g_MissionIdNext[zhiye] )	
end

function x256241_GetBonus( sceneId, selfId,NpcID)
	  if x256241_g_ExpBonus > 0 then
			AddExp(sceneId, selfId, x256241_g_ExpBonus);
  	end
		if x256241_g_BonusMoney1 > 0 then
	    AddMoney( sceneId, selfId, 1, x256241_g_BonusMoney1 )
	  end
		if x256241_g_BonusMoney2 > 0 then
	    AddMoney( sceneId, selfId, 0, x256241_g_BonusMoney2 )
	  end
		if x256241_g_BonusMoney3 > 0 then
	    AddMoney( sceneId, selfId, 3, x256241_g_BonusMoney3 )
		end
		if x256241_g_BonusMoney4 > 0 then
		local nRongYu = GetRongYu( sceneId, selfId )
			nRongYu = nRongYu + x256241_g_BonusMoney4
			SetRongYu( sceneId, selfId, nRongYu )
		end
		if x256241_g_BonusMoney5 > 0 then
			local nShengWang = GetShengWang( sceneId, selfId )
			nShengWang = nShengWang + x256241_g_BonusMoney5
			SetShengWang( sceneId, selfId, nShengWang )
		end
		if x256241_g_BonusMoney6 > 0 then
			AddHonor(sceneId,selfId,x256241_g_BonusMoney6)
		end
end

function x256241_Msg2toplayer( sceneId, selfId,type)
		if type == 0 then
				Msg2Player(sceneId, selfId, "您接受了任务"..x256241_g_MissionName.."！", 0, 2)
		  	Msg2Player(sceneId, selfId, "您接受了任务"..x256241_g_MissionName.."！", 0, 3)
		elseif type == 1 then
				Msg2Player(sceneId, selfId, "您放弃了任务"..x256241_g_MissionName.."！", 0, 2)
				Msg2Player(sceneId, selfId, "您放弃了任务"..x256241_g_MissionName.."！", 0, 3)
		elseif type == 2 then
				Msg2Player(sceneId, selfId, "您完成了任务"..x256241_g_MissionName.."！", 0, 2)
				Msg2Player(sceneId, selfId, "您完成了任务"..x256241_g_MissionName.."！", 0, 3)
				if x256241_g_ExpBonus > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R经验"..x256241_g_ExpBonus.."#Y的奖励", 0, 2)
  			end
				if x256241_g_BonusMoney1 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y获得#R银卡"..x256241_g_BonusMoney1.."文#Y的奖励", 0, 2)
	  		end
				if x256241_g_BonusMoney2 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y获得#R现银"..x256241_g_BonusMoney2.."文#Y的奖励", 0, 2)
	  		end
				if x256241_g_BonusMoney3 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y获得#R金卡"..x256241_g_BonusMoney3.."文#Y的奖励", 0, 2)
				end
				if x256241_g_BonusMoney4 > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R朝廷声望值"..x256241_g_BonusMoney4.."#Y的奖励", 0, 2)
				end
				if x256241_g_BonusMoney5 > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R声望"..x256241_g_BonusMoney5.."#Y的奖励", 0, 2)
				end
				if x256241_g_BonusMoney6 > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R荣誉"..x256241_g_BonusMoney6.."#Y的奖励", 0, 2)
				end
		end
end

function x256241_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
end


function x256241_ProcAreaEntered(sceneId, selfId, zoneId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "ProcAreaEntered",sceneId, selfId, zoneId, MissionId )	

end

function x256241_ProcTiming(sceneId, selfId, ScriptId, MissionId)
	 CallScriptFunction( MISSION_SCRIPT, "ProcTiming",sceneId, selfId, ScriptId, MissionId )
		
end

function x256241_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcAreaLeaved",sceneId, selfId, ScriptId, MissionId)
end

function x256241_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcQuestItemChanged",sceneId, selfId, itemdataId, MissionId )
end


function x256241_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
	  local bFind  = 0
    for i ,item in x256241_g_NpcGUID do
        if item.guid == npcGuid then
            bFind = 1
            break
        end
    end
    if bFind == 0 then
        return
    end
		if IsHaveQuest(sceneId,selfId, x256241_g_MissionId) > 0 then
				local state = GetQuestStateNM(sceneId,selfId,npcId,x256241_g_MissionId)        ---取得任务状态 ，根据状态添加按钮 AddQuestTextNM
				AddQuestTextNM( sceneId, selfId, npcId, x256241_g_MissionId, state, -1 )
		end
end

function x256241_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x256241_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x256241_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x256241_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x256241_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x256241_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end