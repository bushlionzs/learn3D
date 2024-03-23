--敌营密探

--MisDescBegin
x202002_g_ScriptId = 202002
x202002_g_MissionIdPre = 1012
x202002_g_MissionId = 1020
x202002_g_LevelLess	= 30	 
x202002_g_MissionIdNext = 1013
x202002_g_Name	={}
x202002_g_ExtTarget={{type=20,n=1,target="找到@npcsp_潜伏的忽必来_105191"}}
x202002_g_MissionName="【剧场】敌营密探"
x202002_g_MissionInfo="\t忽必来是很擅长潜伏在敌营之内的，他一定还藏在敌营外的草丛中，去到乃蛮部大营找到他吧！"  --任务描述
x202002_g_MissionTarget=""		
x202002_g_MissionCompleted="\t你怎么会知道我藏在这里？难道是赤老温让你来找我的？ "					--完成任务npc说话的话
x202002_g_ContinueInfo=""
x202002_g_MissionHelp =	""
x202002_g_DemandItem ={}
x202002_g_ExpBonus = 55000
x202002_g_BonusMoney1 =285
x202002_g_BonusMoney2 =0
x202002_g_BonusMoney3 =0
x202002_g_BonusMoney4 =0
x202002_g_BonusMoney5 =49
x202002_g_BonusMoney6 =0
x202002_g_BonusItem	=	{{item = 11000200,n=10}}
x202002_g_BonusChoiceItem ={}
x202002_g_NpcGUID ={{ guid = 105191, name = "忽必来"} }
x202002_g_GroupPoint	={ {type=10,id =312,target = "忽必来"} }
x202002_g_npcid = -1
--MisDescEnd
--**********************************

function x202002_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)


	if IsQuestHaveDone(sceneId, selfId, x202002_g_MissionId) > 0 then
		return 
	end
	if IsQuestHaveDone(sceneId, selfId, x202002_g_MissionIdPre)> 0 then
		--if IsQuestHaveDone(sceneId, selfId, x202002_g_MissionIdPre[2])> 0 then
		--	if IsQuestHaveDone(sceneId, selfId, x202002_g_MissionIdPre[3])> 0 then
				--if IsQuestHaveDone(sceneId, selfId, x202002_g_MissionIdPre[4])> 0 then
						if IsHaveQuest(sceneId,selfId, x202002_g_MissionId) <= 0 then
								local state = GetQuestStateNM(sceneId,selfId,NPCId,x202002_g_MissionId)
								AddQuestTextNM( sceneId, selfId, NPCId, x202002_g_MissionId, state, -1 )
						end
				--end
		--	end
		--end
	end
end

function x202002_DispatchMissionInfo( sceneId, selfId, NPCId )
		if x202002_g_ExpBonus> 0 then
			AddQuestExpBonus(sceneId, x202002_g_ExpBonus )
		end
		if x202002_g_BonusMoney1 > 0 then
			AddQuestMoneyBonus1(sceneId, x202002_g_BonusMoney1 )
		end
		if x202002_g_BonusMoney2 > 0 then
			AddQuestMoneyBonus2(sceneId, x202002_g_BonusMoney2 )
		end
		if x202002_g_BonusMoney3 > 0 then
			AddQuestMoneyBonus3(sceneId, x202002_g_BonusMoney3 )
		end
		if x202002_g_BonusMoney4 > 0 then
			AddQuestMoneyBonus4(sceneId, x202002_g_BonusMoney4 )
		end
		if x202002_g_BonusMoney5 > 0 then
			AddQuestMoneyBonus5(sceneId, x202002_g_BonusMoney5 )
		end
		if x202002_g_BonusMoney6 > 0 then
			AddQuestMoneyBonus6(sceneId, x202002_g_BonusMoney6 )
		end
		for i, item in x202002_g_BonusItem do
		   	AddQuestItemBonus(sceneId, item.item, item.n)
	  end
		for i, item in x202002_g_BonusChoiceItem do
	    	AddQuestRadioItemBonus(sceneId, item.item, item.n)
	  end
end
--**********************************

function x202002_ProcEventEntry(sceneId, selfId, NPCId, MissionId)	--点击该任务后执行此脚本
	if IsQuestHaveDone(sceneId, selfId, x202002_g_MissionId) > 0 then
		return 
	end
	if IsHaveQuest(sceneId,selfId, x202002_g_MissionId) > 0 then
			if x202002_CheckSubmit(sceneId, selfId, NPCId) <= 0 then
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x202002_g_MissionName)
						AddQuestText(sceneId,x202002_g_MissionCompleted)
						EndQuestEvent()
						DispatchQuestEventList(sceneId, selfId, NPCId, x202002_g_ScriptId, x202002_g_MissionId);
			else
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x202002_g_MissionName)
						AddQuestText(sceneId,x202002_g_MissionCompleted)
						AddQuestText(sceneId," ")
						x202002_DispatchMissionInfo( sceneId, selfId, NPCId )
						EndQuestEvent()
						DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x202002_g_ScriptId, x202002_g_MissionId);
			end
  elseif x202002_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
			BeginQuestEvent(sceneId)
	  	AddQuestText(sceneId,"#Y"..x202002_g_MissionName)
			AddQuestText(sceneId,x202002_g_MissionInfo)
			AddQuestText( sceneId,"#Y任务目标：")
			for i, item in x202002_g_ExtTarget do
					AddQuestText( sceneId,item.target)
			end 
			if x202002_g_MissionHelp ~= "" then
				AddQuestText(sceneId,"\n#G小提示:#W")
				AddQuestText(sceneId,x202002_g_MissionHelp )
			end
			x202002_DispatchMissionInfo( sceneId, selfId, NPCId )
	  	EndQuestEvent()
			DispatchQuestInfoNM(sceneId, selfId, NPCId, x202002_g_ScriptId, x202002_g_MissionId);
  end
	
end
--**********************************

function x202002_ProcAcceptCheck(sceneId, selfId, NPCId)
		
						return 1
		

end
--**********************************
function x202002_CheckSubmit( sceneId, selfId, NPCId)

	        return 1
	
end
--**********************************
function x202002_ProcQuestAccept( sceneId, selfId, NPCId, MissionId )
		if IsQuestHaveDone(sceneId, selfId, x202002_g_MissionId) > 0 then
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
		local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId,x202002_g_MissionId  )
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
		
		if x202002_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
					local retmiss = AddQuest( sceneId, selfId, x202002_g_MissionId, x202002_g_ScriptId, 0, 0, 0,1)
					if retmiss ==0 then
						Msg2Player(sceneId, selfId, "接受任务失败！", 0, 3)
						return 0
					else
		  			x202002_Msg2toplayer( sceneId, selfId,0)
						--if x202002_CheckSubmit(sceneId, selfId, NPCId) > 0 then
	    			--end
		  		end
	 	end                                                                    
	     
end
--**********************************

function x202002_ProcQuestAbandon(sceneId, selfId, MissionId)
		if IsHaveQuest(sceneId,selfId, x202002_g_MissionId) <= 0 then
				return 
		end
		DelQuest(sceneId, selfId, x202002_g_MissionId)
	  x202002_Msg2toplayer( sceneId, selfId,1)
			
end
--**********************************
function x202002_CheckPlayerBagFull( sceneId ,selfId,selectRadioId )
	local result = 1
	local j = 0
	local bAdd = 0 --是否已经在固定物品奖励添加检测中已经检查出包裹已满
	BeginAddItem(sceneId)
	for j, item in x202002_g_BonusItem do
		AddBindItem( sceneId, item.item, item.n )
  end
  for j, item in x202002_g_BonusChoiceItem do
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
function x202002_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)
	if IsHaveQuest(sceneId,selfId, x202002_g_MissionId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"您没有这个任务！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x202002_CheckSubmit( sceneId, selfId, NPCId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"您没有达到完成条件！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x202002_CheckPlayerBagFull( sceneId ,selfId,selectRadioId ) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"包裹已满！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif DelQuest(sceneId, selfId, x202002_g_MissionId) > 0 then
				x202002_Msg2toplayer( sceneId, selfId,2)
				QuestCom(sceneId, selfId, x202002_g_MissionId)
				x202002_GetBonus( sceneId, selfId,NPCId)
				BeginAddItem(sceneId)
				for i, item in x202002_g_BonusItem do
 						AddBindItem( sceneId, item.item, item.n )
				end
				for i, item in x202002_g_BonusChoiceItem do
						if item.item == selectRadioId then
	    			    AddItem( sceneId, item.item, item.n )
						end
    		end
    		EndAddItem(sceneId,selfId)
    		AddItemListToPlayer(sceneId,selfId)
   end
   CallScriptFunction( MISSION_SCRIPT, "ProcEventEntry", sceneId, selfId, NPCId, x202002_g_MissionIdNext )	
end

function x202002_GetBonus( sceneId, selfId,NpcID)
	  if x202002_g_ExpBonus > 0 then
			AddExp(sceneId, selfId, x202002_g_ExpBonus);
  	end
		if x202002_g_BonusMoney1 > 0 then
	    AddMoney( sceneId, selfId, 1, x202002_g_BonusMoney1 )
	  end
		if x202002_g_BonusMoney2 > 0 then
	    AddMoney( sceneId, selfId, 0, x202002_g_BonusMoney2 )
	  end
		if x202002_g_BonusMoney3 > 0 then
	    AddMoney( sceneId, selfId, 3, x202002_g_BonusMoney3 )
		end
		if x202002_g_BonusMoney4 > 0 then
		local nRongYu = GetRongYu( sceneId, selfId )
			nRongYu = nRongYu + x202002_g_BonusMoney4
			SetRongYu( sceneId, selfId, nRongYu )
		end
		if x202002_g_BonusMoney5 > 0 then
			local nShengWang = GetShengWang( sceneId, selfId )
			nShengWang = nShengWang + x202002_g_BonusMoney5
			SetShengWang( sceneId, selfId, nShengWang )
		end
		if x202002_g_BonusMoney6 > 0 then
			AddHonor(sceneId,selfId,x202002_g_BonusMoney6)
		end
end

function x202002_Msg2toplayer( sceneId, selfId,type)
		if type == 0 then
				Msg2Player(sceneId, selfId, "您接受了任务"..x202002_g_MissionName.."！", 0, 2)
		  	Msg2Player(sceneId, selfId, "您接受了任务"..x202002_g_MissionName.."！", 0, 3)
		elseif type == 1 then
				Msg2Player(sceneId, selfId, "您放弃了任务"..x202002_g_MissionName.."！", 0, 2)
				Msg2Player(sceneId, selfId, "您放弃了任务"..x202002_g_MissionName.."！", 0, 3)
		elseif type == 2 then
				Msg2Player(sceneId, selfId, "您完成了任务"..x202002_g_MissionName.."！", 0, 2)
				Msg2Player(sceneId, selfId, "您完成了任务"..x202002_g_MissionName.."！", 0, 3)
				if x202002_g_ExpBonus > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R经验"..x202002_g_ExpBonus.."#Y的奖励", 0, 2)
  			end
				if x202002_g_BonusMoney1 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y获得#R银卡"..x202002_g_BonusMoney1.."文#Y的奖励", 0, 2)
	  		end
				if x202002_g_BonusMoney2 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y获得#R现银"..x202002_g_BonusMoney2.."文#Y的奖励", 0, 2)
	  		end
				if x202002_g_BonusMoney3 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y获得#R金卡"..x202002_g_BonusMoney3.."文#Y的奖励", 0, 2)
				end
				if x202002_g_BonusMoney4 > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R朝廷声望值"..x202002_g_BonusMoney4.."#Y的奖励", 0, 2)
				end
				if x202002_g_BonusMoney5 > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R声望"..x202002_g_BonusMoney5.."#Y的奖励", 0, 2)
				end
				if x202002_g_BonusMoney6 > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R荣誉"..x202002_g_BonusMoney6.."#Y的奖励", 0, 2)
				end
		end
end

function x202002_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
end


function x202002_ProcAreaEntered(sceneId, selfId, zoneId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "ProcAreaEntered",sceneId, selfId, zoneId, MissionId )	

end

function x202002_ProcTiming(sceneId, selfId, ScriptId, MissionId)
	 CallScriptFunction( MISSION_SCRIPT, "ProcTiming",sceneId, selfId, ScriptId, MissionId )
		
end

function x202002_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcAreaLeaved",sceneId, selfId, ScriptId, MissionId)
end

function x202002_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcQuestItemChanged",sceneId, selfId, itemdataId, MissionId )
end


function x202002_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
	  local bFind  = 0
    for i ,item in x202002_g_NpcGUID do
        if item.guid == npcGuid then
            bFind = 1
            break
        end
    end
    if bFind == 0 then
        return
    end
		if IsHaveQuest(sceneId,selfId, x202002_g_MissionId) > 0 then
				local state = GetQuestStateNM(sceneId,selfId,npcId,x202002_g_MissionId)
				AddQuestTextNM( sceneId, selfId, npcId, x202002_g_MissionId, state, -1 )
		end
end

function x202002_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x202002_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x202002_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
		if IsQuestHaveDone(sceneId, selfId, x202002_g_MissionIdNext) > 0 then
			if IsHaveQuest( sceneId, selfId, x202002_g_MissionId) == 0 then
  		      Msg2Player( sceneId, selfId, "你没有接受【剧情】敌营密探，不能采集", 8, 3)
  		      return 1
  		  end
  		end	  
    		if IsObjValid (sceneId,x202002_g_npcid) == 1 then
					if GetName(sceneId,x202002_g_npcid)=="忽必来" then
							Msg2Player(sceneId, selfId, "忽必来就站在你对面看着你", 0, 3)
								local misIndex = GetQuestIndexByID(sceneId,selfId,x202002_g_MissionId)                                                  
			    			SetQuestByIndex(sceneId,selfId,misIndex,0,1)
			    			SetQuestByIndex(sceneId,selfId,misIndex,7,1)
							return 1
					else
							return 0
					end
			else
					return 0
			end					
-- return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x202002_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	if IsObjValid (sceneId,x202002_g_npcid) == 1 then
			if GetName(sceneId,x202002_g_npcid)=="忽必来" then
					Msg2Player(sceneId, selfId, "忽必来就站在你对面看着你", 0, 3)
					return 1
			else
					x202002_g_npcid=CreateMonster(sceneId, 153,173,188,3,1,-1,105191,20,30000,0,"忽必来")
					local misIndex = GetQuestIndexByID(sceneId,selfId,x202002_g_MissionId)                                                  
	    			SetQuestByIndex(sceneId,selfId,misIndex,0,1)
	    			SetQuestByIndex(sceneId,selfId,misIndex,7,1)
					return 1
			end
	else
			x202002_g_npcid=CreateMonster(sceneId, 153,173,188,3,1,-1,105191,20,30000,180,"忽必来")
			local misIndex = GetQuestIndexByID(sceneId,selfId,x202002_g_MissionId)                                                  
	    	SetQuestByIndex(sceneId,selfId,misIndex,0,1)
	    	SetQuestByIndex(sceneId,selfId,misIndex,7,1)
			return 1
	end				
end

function x202002_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x202002_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end