--采集雪莲

--MisDescBegin
x203645_g_ScriptId = 203645
x203645_g_MissionIdPre =3343
x203645_g_MissionId =3312
x203645_g_LevelLess	= 	1 
x203645_g_MissionIdNext = 3313
x203645_g_Name	={}
x203645_g_ExtTarget={{type=20,n=1,target="取回@npc_128039"}}
x203645_g_MissionName="【新手】新兵的装备<二>"
x203645_g_MissionInfo="\t装备就堆放在大营外，想要的话，你必须自己去取来！"  --任务描述
x203645_g_MissionTarget="取回@npc_128039"		
x203645_g_MissionCompleted="\t很好，这些装备是你的了！"					--完成任务npc说话的话
x203645_g_ContinueInfo="\t别磨磨蹭蹭的，快去取回自己的装备。\n\t#G（到指定地点后，左键点击闪光的装备，就可以获得你的装备。）#W"
x203645_g_MissionHelp =	""
x203645_g_DemandItem ={13010121}
x203645_g_ExpBonus = 1800
x203645_g_BonusMoney1 =5
x203645_g_BonusMoney2 =0
x203645_g_BonusMoney3 =0
x203645_g_BonusMoney4 =0
x203645_g_BonusMoney5 =12
x203645_g_BonusMoney6 =0
x203645_g_BonusChoiceItem ={}
x203645_g_BonusItem	=	{{item =13010122, n = 1}}
x203645_g_NpcGUID ={{ guid = 128018, name = "那都赞"}}
x203645_g_GroupPoint	=	{ {type=10,id =195,target = "新兵装备"} }--专门用于采集点特效用，与任务相关未必就是完成任务的必要因素，因此，只要相关就可以设置这个属性
--MisDescEnd
--**********************************

function x203645_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
   CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 1,0 )
   CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 17,0 )
   --local zhiye =GetZhiye( sceneId, selfId)
	if IsQuestHaveDone(sceneId, selfId, x203645_g_MissionId) > 0 then
		return 
	end
	if IsQuestHaveDone(sceneId, selfId, x203645_g_MissionIdPre)> 0 then
	  --if zhiye ==0 then
	  if IsHaveQuest(sceneId,selfId, x203645_g_MissionId) <= 0 then
			x203645_CheckSubmit(sceneId, selfId, NPCId)
			local state = GetQuestStateNM(sceneId,selfId,NPCId,x203645_g_MissionId)
			AddQuestTextNM( sceneId, selfId, NPCId, x203645_g_MissionId, state, -1 )
		--end
		end
	end
end

function x203645_DispatchMissionInfo( sceneId, selfId, NPCId )
		if x203645_g_ExpBonus> 0 then
			AddQuestExpBonus(sceneId, x203645_g_ExpBonus )
		end
		if x203645_g_BonusMoney1 > 0 then
			AddQuestMoneyBonus1(sceneId, x203645_g_BonusMoney1 )
		end
		if x203645_g_BonusMoney2 > 0 then
			AddQuestMoneyBonus2(sceneId, x203645_g_BonusMoney2 )
		end
		if x203645_g_BonusMoney3 > 0 then
			AddQuestMoneyBonus3(sceneId, x203645_g_BonusMoney3 )
		end
		if x203645_g_BonusMoney4 > 0 then
			AddQuestMoneyBonus4(sceneId, x203645_g_BonusMoney4 )
		end
		if x203645_g_BonusMoney5 > 0 then
			AddQuestMoneyBonus5(sceneId, x203645_g_BonusMoney5 )
		end
		if x203645_g_BonusMoney6 > 0 then
			AddQuestMoneyBonus6(sceneId, x203645_g_BonusMoney6 )
		end
		for i, item in x203645_g_BonusItem do
		   	AddQuestItemBonus(sceneId, item.item, item.n)
	  end
		for i, item in x203645_g_BonusChoiceItem do
	    	AddQuestRadioItemBonus(sceneId, item.item, item.n)
	  end
end
--**********************************

function x203645_ProcEventEntry(sceneId, selfId, NPCId, MissionId)	--点击该任务后执行此脚本
	if IsQuestHaveDone(sceneId, selfId, x203645_g_MissionId) > 0 then
		return 
	end
	if IsHaveQuest(sceneId,selfId, x203645_g_MissionId) > 0 then
			if x203645_CheckSubmit(sceneId, selfId, NPCId) <= 0 then
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x203645_g_MissionName)
						AddQuestText(sceneId,x203645_g_ContinueInfo)
						EndQuestEvent()
						DispatchQuestEventList(sceneId, selfId, NPCId, x203645_g_ScriptId, x203645_g_MissionId);
			else
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x203645_g_MissionName)
						AddQuestText(sceneId,x203645_g_MissionCompleted)
						AddQuestText(sceneId," ")
						x203645_DispatchMissionInfo( sceneId, selfId, NPCId )
						EndQuestEvent()
						DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x203645_g_ScriptId, x203645_g_MissionId);
			end
  elseif x203645_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
			BeginQuestEvent(sceneId)
	  	AddQuestText(sceneId,"#Y"..x203645_g_MissionName)
			AddQuestText(sceneId,x203645_g_MissionInfo)
			AddQuestText( sceneId,"#Y任务目标：") 
			for i, item in x203645_g_ExtTarget do
					AddQuestText( sceneId,item.target)
			end 
			if x203645_g_MissionHelp ~= "" then
				AddQuestText(sceneId,"\n#G小提示:#W")
				AddQuestText(sceneId,x203645_g_MissionHelp )
			end
			x203645_DispatchMissionInfo( sceneId, selfId, NPCId )
	  	EndQuestEvent()
			DispatchQuestInfoNM(sceneId, selfId, NPCId, x203645_g_ScriptId, x203645_g_MissionId);
  end
	
end
--**********************************

function x203645_ProcAcceptCheck(sceneId, selfId, NPCId)
		if IsQuestHaveDone(sceneId, selfId, x203645_g_MissionIdPre)> 0 then
					return 1
		end
		return 0

end
--**********************************
function x203645_CheckSubmit( sceneId, selfId, NPCId)
		--local zhiye =GetZhiye( sceneId, selfId)+1
		if GetItemCount(sceneId,selfId,x203645_g_DemandItem[1]) >= 1 then
					local misIndex = GetQuestIndexByID(sceneId,selfId,x203645_g_MissionId)                                                  
	    		SetQuestByIndex(sceneId,selfId,misIndex,0,1)
	    		SetQuestByIndex(sceneId,selfId,misIndex,7,1)
	    		CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 18,0 ) 
	    		return 1
	    		
	  else
	  			local misIndex = GetQuestIndexByID(sceneId,selfId,x203645_g_MissionId)                                                  
	    		SetQuestByIndex(sceneId,selfId,misIndex,0,0)
	    		SetQuestByIndex(sceneId,selfId,misIndex,7,0)
	  end
	  return 0
	
end
--**********************************
function x203645_ProcQuestAccept( sceneId, selfId, NPCId, MissionId )
		if IsQuestHaveDone(sceneId, selfId, x203645_g_MissionId) > 0 then
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
		local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId,x203645_g_MissionId  )
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
		if x203645_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
					local retmiss = AddQuest( sceneId, selfId, x203645_g_MissionId, x203645_g_ScriptId, 1, 1, 1,1)
					if retmiss ==0 then
						Msg2Player(sceneId, selfId, "接受任务失败！", 0, 3)
						return 0
					else
		  			--x203645_Msg2toplayer( sceneId, selfId,0)
		 				--x203645_ProcQuestItemChanged(sceneId, selfId, -1, MissionId)
					--	if x203645_CheckSubmit(sceneId, selfId, NPCId) > 0 then
					--			local misIndex = GetQuestIndexByID(sceneId,selfId,x203645_g_MissionId)                                                  
	    		--			SetQuestByIndex(sceneId,selfId,misIndex,0,1)
	    		--			SetQuestByIndex(sceneId,selfId,misIndex,7,1)  
	    		CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 18,1 ) 
	    							for i, item in x203645_g_DemandItem do                                            
	    								if GetItemCount(sceneId,selfId,item) >= 1 then		                              
	    									local misIndex = GetQuestIndexByID(sceneId,selfId,x203645_g_MissionId)        
	    			    					SetQuestByIndex(sceneId,selfId,misIndex,0,1)                                			
	    			    					SetQuestByIndex(sceneId,selfId,misIndex,7,1) 	
	    			    			end                               			
	    					end
	    			end
		  		end
	 	end                                                                    
	     

--**********************************

function x203645_ProcQuestAbandon(sceneId, selfId, MissionId)
		if IsHaveQuest(sceneId,selfId, x203645_g_MissionId) <= 0 then
				return 
		end
		--local zhiye=GetZhiye( sceneId, selfId)+1                                              
			DelItem( sceneId,selfId,x203645_g_DemandItem[1],1 )
		DelQuest(sceneId, selfId, x203645_g_MissionId)
	  x203645_Msg2toplayer( sceneId, selfId,1)
			
end
--**********************************
function x203645_CheckPlayerBagFull( sceneId ,selfId,selectRadioId )
	local result = 1
	local j = 0
	local bAdd = 0 --是否已经在固定物品奖励添加检测中已经检查出包裹已满
	BeginAddItem(sceneId)
	for j, item in x203645_g_BonusItem do
		AddItem( sceneId, item.item, item.n )
  end
  for j, item in x203645_g_BonusChoiceItem do
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
function x203645_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)
	if IsHaveQuest(sceneId,selfId, x203645_g_MissionId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"您没有这个任务！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x203645_CheckSubmit( sceneId, selfId, NPCId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"您没有达到完成条件！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x203645_CheckPlayerBagFull( sceneId ,selfId,selectRadioId ) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"包裹已满！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif DelQuest(sceneId, selfId, x203645_g_MissionId) > 0 then
				x203645_Msg2toplayer( sceneId, selfId,2)			
				QuestCom(sceneId, selfId, x203645_g_MissionId)
				--QuestCom(sceneId, selfId, 3046)
				x203645_GetBonus( sceneId, selfId,NPCId)
				BeginAddItem(sceneId)
				for i, item in x203645_g_BonusItem do
 						AddItem( sceneId, item.item, item.n )
				end
				for i, item in x203645_g_BonusChoiceItem do
						if item.item == selectRadioId then
	    			    AddItem( sceneId, item.item, item.n )
						end
    		end
    		EndAddItem(sceneId,selfId)
    		DelItem( sceneId,selfId,x203645_g_DemandItem[1],1 )
    		AddItemListToPlayer(sceneId,selfId)
   end    
   CallScriptFunction( MISSION_SCRIPT, "ProcEventEntry", sceneId, selfId, NPCId, x203645_g_MissionIdNext )	
end

function x203645_GetBonus( sceneId, selfId,NpcID)
	  if x203645_g_ExpBonus > 0 then
			AddExp(sceneId, selfId, x203645_g_ExpBonus);
  	end
		if x203645_g_BonusMoney1 > 0 then
	    AddMoney( sceneId, selfId, 1, x203645_g_BonusMoney1 )
	  end
		if x203645_g_BonusMoney2 > 0 then
	    AddMoney( sceneId, selfId, 0, x203645_g_BonusMoney2 )
	  end
		if x203645_g_BonusMoney3 > 0 then
	    AddMoney( sceneId, selfId, 3, x203645_g_BonusMoney3 )
		end
		if x203645_g_BonusMoney4 > 0 then
		local nRongYu = GetRongYu( sceneId, selfId )
			nRongYu = nRongYu + x203645_g_BonusMoney4
			SetRongYu( sceneId, selfId, nRongYu )
		end
		if x203645_g_BonusMoney5 > 0 then
			local nShengWang = GetShengWang( sceneId, selfId )
			nShengWang = nShengWang + x203645_g_BonusMoney5
			SetShengWang( sceneId, selfId, nShengWang )
		end
		if x203645_g_BonusMoney6 > 0 then
			AddHonor(sceneId,selfId,x203645_g_BonusMoney6)
		end
end

function x203645_Msg2toplayer( sceneId, selfId,type)
		if type == 0 then
				Msg2Player(sceneId, selfId, "您接受了任务"..x203645_g_MissionName.."！", 0, 2)
		  	Msg2Player(sceneId, selfId, "您接受了任务"..x203645_g_MissionName.."！", 0, 3)
		elseif type == 1 then
				Msg2Player(sceneId, selfId, "您放弃了任务"..x203645_g_MissionName.."！", 0, 2)
				Msg2Player(sceneId, selfId, "您放弃了任务"..x203645_g_MissionName.."！", 0, 3)
		elseif type == 2 then
				Msg2Player(sceneId, selfId, "您完成了任务"..x203645_g_MissionName.."！", 0, 2)
				Msg2Player(sceneId, selfId, "您完成了任务"..x203645_g_MissionName.."！", 0, 3)
				if x203645_g_ExpBonus > 0 then
					Msg2Player(sceneId, selfId, "#cffcf00获得#G经验"..x203645_g_ExpBonus.."#cffcf00的奖励", 0, 2)
  			end
				if x203645_g_BonusMoney1 > 0 then
	  		  Msg2Player(sceneId, selfId, "#cffcf00获得#G银卡"..x203645_g_BonusMoney1.."文#cffcf00的奖励", 0, 2)
	  		end
				if x203645_g_BonusMoney2 > 0 then
	  		  Msg2Player(sceneId, selfId, "#cffcf00获得#G现银"..x203645_g_BonusMoney2.."文#cffcf00的奖励", 0, 2)
	  		end
				if x203645_g_BonusMoney3 > 0 then
	  		  Msg2Player(sceneId, selfId, "#cffcf00获得#G金卡"..x203645_g_BonusMoney3.."文#cffcf00的奖励", 0, 2)
				end
				if x203645_g_BonusMoney4 > 0 then
					Msg2Player(sceneId, selfId, "#cffcf00获得#G朝廷声望值"..x203645_g_BonusMoney4.."#cffcf00的奖励", 0, 2)
				end
				if x203645_g_BonusMoney5 > 0 then
					Msg2Player(sceneId, selfId, "#cffcf00获得#G声望"..x203645_g_BonusMoney5.."#cffcf00的奖励", 0, 2)
				end
				if x203645_g_BonusMoney6 > 0 then
					Msg2Player(sceneId, selfId, "#cffcf00获得#G荣誉"..x203645_g_BonusMoney6.."#cffcf00的奖励", 0, 2)
				end
		end
end

function x203645_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
end


function x203645_ProcAreaEntered(sceneId, selfId, zoneId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "ProcAreaEntered",sceneId, selfId, zoneId, MissionId )	

end

function x203645_ProcTiming(sceneId, selfId, ScriptId, MissionId)
	 CallScriptFunction( MISSION_SCRIPT, "ProcTiming",sceneId, selfId, ScriptId, MissionId )
		
end

function x203645_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcAreaLeaved",sceneId, selfId, ScriptId, MissionId)
end

function x203645_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

		if GetItemCount(sceneId,selfId,x203645_g_DemandItem[1]) >= 1 then
			
					local misIndex = GetQuestIndexByID(sceneId,selfId,x203645_g_MissionId)                                                  
	    		SetQuestByIndex(sceneId,selfId,misIndex,0,1)
	    		SetQuestByIndex(sceneId,selfId,misIndex,7,1)
	    	CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 18,0 ) 	
	    	CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 1,1 )
	  else
	  			local misIndex = GetQuestIndexByID(sceneId,selfId,x203645_g_MissionId)                                                  
	    		SetQuestByIndex(sceneId,selfId,misIndex,0,0)
	    		SetQuestByIndex(sceneId,selfId,misIndex,7,0)
	  end
end

function x203645_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )  
   local bFind  = 0                                                             
  for i ,item in x203645_g_NpcGUID do                                          
     if item.guid == npcGuid then                                             
        bFind = 1                                                            
        break                                                                
     end                                                                      
   end                                                                          
   if bFind == 0 then                                                           
    return                                                                   
    end                                                                          
  if IsHaveQuest(sceneId,selfId, x203645_g_MissionId) > 0 then                 
		local state = GetQuestStateNM(sceneId,selfId,npcId,x203645_g_MissionId)  
		AddQuestTextNM( sceneId, selfId, npcId, x203645_g_MissionId, state, -1 ) 
	end
end    
                                                                      
function x203645_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x203645_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x203645_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x203645_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x203645_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x203645_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end